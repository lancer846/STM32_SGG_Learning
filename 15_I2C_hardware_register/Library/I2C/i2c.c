#include "i2c.h"

void I2C0_init(void)
{
    RCC->AHB1ENR |= RCC_AHB1ENR_GPIOBEN;
    RCC->APB1ENR |= RCC_APB1ENR_I2C1EN;
    // 复用模式
    GPIOB->MODER &= ~GPIO_MODER_MODER6_0;
    GPIOB->MODER |= GPIO_MODER_MODER6_1;
    GPIOB->MODER &= ~GPIO_MODER_MODER7_0;
    GPIOB->MODER |= GPIO_MODER_MODER7_1;
    // 开漏
    GPIOB->OTYPER |= GPIO_OTYPER_OT_6;
    GPIOB->OTYPER |= GPIO_OTYPER_OT_7;
    // 速度
    GPIOB->OSPEEDR |= GPIO_OSPEEDER_OSPEEDR6;
    GPIOB->OSPEEDR |= GPIO_OSPEEDER_OSPEEDR7;
    // 上拉
    GPIOB->PUPDR |= GPIO_PUPDR_PUPDR6_0;
    GPIOB->PUPDR &= ~GPIO_PUPDR_PUPDR6_1;
    GPIOB->PUPDR |= GPIO_PUPDR_PUPDR7_0;
    GPIOB->PUPDR &= ~GPIO_PUPDR_PUPDR7_1;
    // 复用 - AF4
    GPIOB->AFR[0] |= 0x44000000;

// I2C1
#if USE_FAST_MODE
    // --------- 快速模式 ---------
    I2C1->CR1 &= ~I2C_CR1_SMBUS;
    // 外设时钟频率配置
    I2C1->CR2 |= 0x28; // 40MHZ
    // 设置从设备地址位数 - 7bit
    // I2C1->OAR1 &= ~I2C_OAR1_ADDMODE;
    // 快速模式还是标准模式 - 快速模式，且 duty 设置为 1
    I2C1->CCR |= (I2C_CCR_FS | I2C_CCR_DUTY);
    // 配置时钟控制寄存器
    I2C1->CCR |= 0x04;
    // 300 / 25 + 1
    I2C1->TRISE |= 0x0D;
    I2C1->CR1 &= ~I2C_CR1_SMBUS;

#else
    // -------- 标准模式 ---------
    // 外设时钟频率配置
    I2C1->CR2 |= 42; // 42MHZ
    // 快速模式还是标准模式 - 标准模式，且 duty 设置为 0
    I2C1->CCR &= ~I2C_CCR_FS;
    // 配置时钟控制寄存器
    I2C1->CCR |= 210;
    // 1 / (1/42) + 1 = 43
    I2C1->TRISE |= 43;
#endif

    // 开启外设使能
    I2C1->CR1 |= I2C_CR1_PE;
}

/*
    I2C 的每个时序
    每个操作的末尾均将 SCL 拉低
 */

int I2C0_start()
{

    uint16_t timeout = 0xFFFF;
    // 检测总线是否忙碌
    while ((I2C1->SR2 & I2C_SR2_BUSY) && timeout)
    {
        timeout--;
    }
    I2C1->CR1 |= I2C_CR1_START;
    timeout = 0xFFFF;
    while ((I2C1->SR1 & I2C_SR1_SB) == 0 && timeout)
    {
        timeout--;
    }
    return timeout ? OK : FAIL;
}

void I2C0_send_ack(uint8_t ack)
{
    if (ack == ACK)
    {
        I2C1->CR1 |= I2C_CR1_ACK;
    }
    else
    {
        I2C1->CR1 &= ~I2C_CR1_ACK;
    }
}
int I2C0_send_addr(uint8_t addr)
{
    // 发送地址
    I2C1->DR = addr;
    uint16_t timeout = 0xFFFF;
    while ((I2C1->SR1 & I2C_SR1_ADDR) == 0 && timeout)
    {
        timeout--;
    }
    // 清除标志位
    I2C1->SR1;
    I2C1->SR2;
    return timeout ? OK : FAIL;
}
int I2C0_send_byte(uint8_t byte)
{
    // 等待 DR 为空
    uint16_t timeout = 0xFFFF;
    while ((I2C1->SR1 & I2C_SR1_TXE) == 0 && timeout)
    {
        timeout--;
    }
    if (!timeout)
        return FAIL;
    I2C1->DR = byte;
    timeout = 0xFFFF;
    // 等待应答
    while ((I2C1->SR1 & I2C_SR1_BTF) == 0 && timeout)
    {
        timeout--;
    }
    // 清空标志位
    I2C1->DR;
    return timeout ? OK : FAIL;
}
int I2C0_receive_byte()
{
    // 等待标志位
    uint16_t timeout = 0xFFFF;
    while ((I2C1->SR1 & I2C_SR1_RXNE) == 0 && timeout)
    {
        timeout--;
    }
    uint8_t byte = I2C1->DR;

    return timeout ? byte : FAIL;
}
// 设置接收完成之后发出停止信号
void I2C0_stop()
{
    I2C1->CR1 |= I2C_CR1_STOP;
}

void I2C0_write_bytes(uint8_t dev_addr, uint8_t reg_addr, uint8_t *buff, uint16_t size)
{
    int res = I2C0_start();
    // printf("res = %d\n", res);
    I2C0_send_addr(dev_addr);

    I2C0_send_byte(reg_addr);

    for (uint16_t i = 0; i < size; i++)
    {
        I2C0_send_byte(buff[i]);
    }

    I2C0_stop();
}

uint8_t I2C0_write_offset(uint8_t dev_addr, uint8_t reg_addr, uint8_t *buff, uint8_t offset, uint16_t size)
{
    // 开始
    if (I2C0_start() == FAIL)
        return 1;
    // 发 设备地址
    if (I2C0_send_addr(dev_addr) == FAIL)
        return 2;

    // 发 寄存器地址
    if (I2C0_send_byte(reg_addr) == FAIL)
        return 3;

    // 循环发数据
    for (uint32_t i = 0; i < size; i++)
    {
        // 发送数据 dat[i]
        I2C0_send_byte(buff[i * offset]);
    }

    // 停止
    I2C0_stop();

    return 0;
}

uint8_t I2C0_read_bytes(uint8_t dev_addr, uint8_t reg_addr, uint8_t *buff, uint16_t size)
{
    I2C0_start();
    I2C0_send_addr(dev_addr);

    I2C0_send_byte(reg_addr);

    I2C0_start();
    I2C0_send_addr(dev_addr | 1);

    I2C0_send_ack(ACK);
    for (uint16_t i = 0; i < size; i++)
    {
        if (i == size - 1)
        {
            I2C0_send_ack(NACK);
        }
        buff[i] = I2C0_receive_byte();
    }
    I2C0_stop();

    return 0;
}
