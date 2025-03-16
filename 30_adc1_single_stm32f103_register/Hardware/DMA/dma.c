/*
 * @Author: wushengran
 * @Date: 2024-06-07 11:35:48
 * @Description: 
 * 
 * Copyright (c) 2024 by atguigu, All Rights Reserved. 
 */
#include "dma.h"

// 初始化
void DMA1_Init(void)
{
    // 1. 开启时钟
    RCC->AHBENR |= RCC_AHBENR_DMA1EN;

    // 2. DMA相关配置
    // 2.1 数据传输方向: 存储器到存储器，从外设读
    DMA1_Channel1->CCR |= DMA_CCR1_MEM2MEM;
    DMA1_Channel1->CCR |= DMA_CCR1_DIR;

    // 2.2 数据宽度: 8位 - 00
    DMA1_Channel1->CCR &= ~DMA_CCR1_PSIZE;
    DMA1_Channel1->CCR &= ~DMA_CCR1_MSIZE;

    // 2.3 地址自增：开启自增
    DMA1_Channel1->CCR |= DMA_CCR1_PINC;
    DMA1_Channel1->CCR |= DMA_CCR1_MINC;

    // 2.4 开启数据传输完成中断标志
    DMA1_Channel1->CCR |= DMA_CCR1_TCIE;

    // 3. NVIC配置
    NVIC_SetPriorityGrouping(3);
    NVIC_SetPriority(DMA1_Channel1_IRQn, 2);
    NVIC_EnableIRQ(DMA1_Channel1_IRQn);

}

// 数据传输
void DMA1_Transmit(uint32_t srcAddr, uint32_t destAddr, uint16_t dataLen)
{
    // 1. 设置外设地址
    DMA1_Channel1->CPAR = destAddr;

    // 2. 设置存储器地址
    DMA1_Channel1->CMAR = srcAddr;

    // 3. 设置传输的数据量
    DMA1_Channel1->CNDTR = dataLen;

    // 4. 开启通道，开始传输数据
    DMA1_Channel1->CCR |= DMA_CCR1_EN;
}

// 中断服务程序
void DMA1_Channel1_IRQHandler(void)
{
    // 判断中断标志位
    if (DMA1->ISR & DMA_ISR_TCIF1)
    {
        // 清除中断标志位
        DMA1->IFCR |= DMA_IFCR_CTCIF1;

        // 关闭DMA通道
        DMA1_Channel1->CCR &= ~DMA_CCR1_EN;

        // isFinished = 1;
    }
    
}
