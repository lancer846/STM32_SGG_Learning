#include "usart.h"

uint8_t receive_buff[RECEIVE_BUFF_MAX_SIZE];
uint8_t receive_size = 0;

// 串口引脚使用 PA9、PA10
void USART_init(void)
{
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
    USART1->BRR = 0x2227; // 波特率为 19200
    // 当使用 115200 时，会存在误差，发送数据过快过多的时候，会导致数据丢失
    // USART1->BRR = 0x5B1; // 波特率为 115200

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

    // 开启接收、空闲中断
    USART1->CR1 |= USART_CR1_RXNEIE;
    USART1->CR1 |= USART_CR1_IDLEIE;

    // 开启串口中断
    NVIC_SetPriority(USART1_IRQn, 3);
    NVIC_EnableIRQ(USART1_IRQn);

    // 清除空闲标志位 idle
    // USART1->SR;
    // USART1->DR;
}

// 串口发送一个字节
void USART_send_char(uint8_t ch)
{
    // 等待当前发送寄存器为空
    while ((USART1->SR & USART_SR_TXE) == 0)
        ;
    // 当数据写入 USART_DR 寄存器，标志位 USART_SR_TXE 会被自动清除
    USART1->DR = ch;
}

// 发送字符串
void USART_send_string(uint8_t *str, uint8_t size)
{
    for (uint8_t i = 0; i < size; i++)
    {
        USART_send_char(str[i]);
    }
}

void USART1_IRQHandler()
{
    // 判断是哪种中断触发
    if (USART1->SR & USART_SR_RXNE)
    {
        // 接收中断
        receive_buff[receive_size++] = USART1->DR;
        // 若数据超出界限，则从头开始
        if(receive_size >= RECEIVE_BUFF_MAX_SIZE - 1) {
            receive_size = 0;
        }
    }
    else if (USART1->SR & USART_SR_IDLE)
    {
        // 空闲中断
        // 清除空闲标志位，上面的判断已经访问过 USART1->SR，所以此处只需再访问 DR 即可
        USART1->DR;

#if USE_RECEIVE_CALLBACK
        // 调用回调函数
        USART_receive_callback(receive_buff, receive_size);
#endif
        // 清空接收缓冲区
        receive_size = 0;
    }
}
