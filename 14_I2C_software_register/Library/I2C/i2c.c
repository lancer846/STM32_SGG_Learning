#include "i2c.h"

void I2C0_init(void)
{
    RCC->AHB1ENR |= RCC_AHB1ENR_GPIOBEN;
    // 输出模式
    GPIOB->MODER |= GPIO_MODER_MODER6_0;
    GPIOB->MODER &= ~GPIO_MODER_MODER6_1;
    GPIOB->MODER |= GPIO_MODER_MODER7_0;
    GPIOB->MODER &= ~GPIO_MODER_MODER7_1;
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
}

/*
    I2C 的每个时序
    每个操作的末尾均将 SCL 拉低
 */

void I2C0_start()
{
		I2C0_SDA_HIGH();
    I2C0_SCL_HIGH();
    I2C0_DELAY();
	
    I2C0_SDA_LOW();
    I2C0_DELAY();
    I2C0_SCL_LOW();
    I2C0_DELAY();
}
uint8_t I2C0_wait_ack()
{
    I2C0_SDA_HIGH();
    I2C0_DELAY();
    I2C0_SCL_HIGH();
    I2C0_DELAY();
    uint8_t ack = I2C0_READ_SDA() ? NACK : ACK;
    I2C0_DELAY();
    I2C0_SCL_LOW();
    I2C0_DELAY();
    return ack;
}
void I2C0_send_ack(uint8_t ack)
{
    uint8_t sign = ack ? NACK : ACK;
    if (sign)
    {
        I2C0_SDA_HIGH();
    }
    else
    {
        I2C0_SDA_LOW();
    }
    I2C0_DELAY();
    I2C0_SCL_HIGH();
    I2C0_DELAY();
    I2C0_SCL_LOW();
    I2C0_DELAY();
}
void I2C0_send_byte(uint8_t byte)
{
    for (uint8_t i = 0; i < 8; i++)
    {
        if (byte & 0x80)
        {
            I2C0_SDA_HIGH();
        }
        else
        {
            I2C0_SDA_LOW();
        }
        I2C0_DELAY();
        I2C0_SCL_HIGH();
        I2C0_DELAY();
        I2C0_SCL_LOW();
        I2C0_DELAY();
        byte <<= 1;
    }
}
uint8_t I2C0_receive_byte()
{
    uint8_t byte = 0;
    for (uint8_t i = 0; i < 8; i++)
    {
        byte <<= 1;
        I2C0_SCL_HIGH();
        I2C0_DELAY();
        if (I2C0_READ_SDA())
        {
            byte |= 1;
        }
        I2C0_DELAY();
        I2C0_SCL_LOW();
        I2C0_DELAY();
    }
    return byte;
}
void I2C0_stop()
{
    I2C0_SDA_LOW();
    I2C0_DELAY();
    I2C0_SCL_HIGH();
    I2C0_DELAY();
    I2C0_SDA_HIGH();
    I2C0_DELAY();
}

void I2C0_write_bytes(uint8_t dev_addr, uint8_t reg_addr, uint8_t *buff, uint16_t size)
{
    I2C0_start();
    I2C0_send_byte(dev_addr);
    uint8_t ack = I2C0_wait_ack();
    if (ack == ACK)
    {
        I2C0_send_byte(reg_addr);
        I2C0_wait_ack();
        for (uint16_t i = 0; i < size; i++)
        {
            I2C0_send_byte(buff[i]);
            I2C0_wait_ack();
        }
    }
    I2C0_stop();
}

uint8_t I2C0_write_offset(uint8_t dev_addr, uint8_t reg_addr, uint8_t *buff, uint8_t offset, uint16_t size)
{
    // 开始
    I2C0_start();
    // 发 设备地址
    I2C0_send_byte(dev_addr);
    // 如果有异常，异常的返回值，本身就>0， 这个返回值本身就是真
    if (I2C0_wait_ack())
        return 1;

    // 发 寄存器地址
    I2C0_send_byte(reg_addr);
    // 等待响应
    if (I2C0_wait_ack())
        return 2;
    // 循环发数据
    for (uint32_t i = 0; i < size; i++)
    {
        // 发送数据 dat[i]
        I2C0_send_byte(buff[i * offset]);
        // 等待响应
        if (I2C0_wait_ack())
            return 3;
    }

    // 停止
    I2C0_stop();

    return 0;
}

uint8_t I2C0_read_bytes(uint8_t dev_addr, uint8_t reg_addr, uint8_t *buff, uint16_t size)
{
    I2C0_start();
    I2C0_send_byte(dev_addr);
    if (I2C0_wait_ack())
        return 1;
    I2C0_send_byte(reg_addr);
    if (I2C0_wait_ack())
        return 2;
    I2C0_start();
    I2C0_send_byte(dev_addr | 1);
    if (I2C0_wait_ack())
        return 3;

    for (uint16_t i = 0; i < size; i++)
    {
        buff[i] = I2C0_receive_byte();
        I2C0_send_ack(i == size - 1 ? NACK : ACK);
    }

    I2C0_stop();
    return 0;
}
