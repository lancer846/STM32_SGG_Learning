#include "usart.h"

// 串口引脚使用 PA9、PA10
void USART_init(void) {
    // 时钟使能
    RCC->AHB1ENR |= RCC_AHB1ENR_GPIOAEN;
    RCC->APB2ENR |= RCC_APB2ENR_USART1EN;

    // 配置GPIO引脚 - 复用功能
    GPIOA->MODER |= GPIO_MODER_MODER9_1;
    GPIOA->MODER &= ~GPIO_MODER_MODER9_0;
    GPIOA->MODER |= GPIO_MODER_MODER10_1;
    GPIOA->MODER &= ~GPIO_MODER_MODER10_0;
    // 默认即是推挽输出
    GPIOA->OTYPER &= ~GPIO_OTYPER_OT_9;
    GPIOA->OTYPER &= ~GPIO_OTYPER_OT_10;
    // 配置GPIO引脚 - 复用功能 AF7
    GPIOA->AFR[1] |= (0x7 << 4);
    GPIOA->AFR[1] &= ~(0x1 << 7);

    GPIOA->AFR[1] |= (0x7 << 8);
    GPIOA->AFR[1] &= ~(0x1 << 11);

    // 输出速度 - 设置最大
    GPIOA->OSPEEDR |= GPIO_OSPEEDER_OSPEEDR9;
    GPIOA->OSPEEDR |= GPIO_OSPEEDER_OSPEEDR10;

    // 设置波特率 115200
    #if 1
    USART1->CR1 |= USART_CR1_OVER8;
    #else
    USART1->CR1 |= USART_CR1_OVER8;
    #endif
    // USART1->BRR = 0x2227; // 波特率为 19200
    USART1->BRR = 0x5B1; // 波特率为 115200

    // 接收使能
    USART1->CR1 |= USART_CR1_RE;
    // 发送使能
    USART1->CR1 |= USART_CR1_TE;
    // 设置发送字节位数
    USART1->CR1 &= ~USART_CR1_M;
    // 没有校验位
    USART1->CR1 &= ~USART_CR1_PCE;
    // 默认是一个停止位
    USART1->CR2 &= ~USART_CR2_STOP;
    // 使能串口
    USART1->CR1 |= USART_CR1_UE;

    // 清除空闲标志位 idle
    // USART1->SR;
    // USART1->DR;
}

// 串口发送一个字节
void USART_send_char(uint8_t ch) {
    // 等待当前发送寄存器为空
    while((USART1->SR & USART_SR_TXE) == 0);
    // 当数据写入 USART_DR 寄存器，标志位 USART_SR_TXE 会被自动清除
    USART1->DR = ch;
}
// 串口接收一个字节
uint8_t USART_receive_char(void) {
    uint8_t byte;
    while ((USART1->SR & USART_SR_RXNE) == 0) {
        //USART_send_char(USART1->SR & USART_SR_IDLE);
        /**
         * 需要添加空闲帧 idle 判断，
         * 单个字节不受影响
         * 发送多个字节时：
         * 空闲阶段，idle 的标志位置位需要时间，此时接收寄存器为空，会在死循环里出不来
         */
        // 注意 USART1->SR & USART_SR_IDLE 这个值不是 1，而是 0x10
        if(USART1->SR & USART_SR_IDLE) {
            return 0;
        }
    }
    // 当读取 USART_DR 寄存器，标志位 USART_SR_RXNE 会被自动清除
    byte = USART1->DR;
    return byte;
}

// 发送字符串
void USART_send_string(uint8_t *str, uint8_t size) {
    for (uint8_t i = 0; i < size; i++)
    {
        USART_send_char(str[i]);
    }
    // USART_send_char('\0');
}
// 接收字符串
uint8_t USART_receive_string(uint8_t *str) {
    uint8_t i = 0;
    while((USART1->SR & USART_SR_IDLE) == 0) {
        str[i] = USART_receive_char();
        i++;
    }
    // 清除空闲标志位 idle
    USART1->SR;
    USART1->DR;
    // 因为当空闲时 USART_receive_char() 会返回 0，i 多加了一次，所以需要减 1
    i--;
    return i;
}
