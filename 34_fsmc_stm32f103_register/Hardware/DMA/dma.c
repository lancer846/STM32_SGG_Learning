/*
 * @Author: wushengran
 * @Date: 2024-06-07 11:35:48
 * @Description: 
 * 
 * Copyright (c) 2024 by atguigu, All Rights Reserved. 
 */
#include "dma.h"

// ��ʼ��
void DMA1_Init(void)
{
    // 1. ����ʱ��
    RCC->AHBENR |= RCC_AHBENR_DMA1EN;

    // 2. DMA�������
    // 2.1 ���ݴ��䷽��: �洢�����洢�����������
    DMA1_Channel1->CCR |= DMA_CCR1_MEM2MEM;
    DMA1_Channel1->CCR |= DMA_CCR1_DIR;

    // 2.2 ���ݿ��: 8λ - 00
    DMA1_Channel1->CCR &= ~DMA_CCR1_PSIZE;
    DMA1_Channel1->CCR &= ~DMA_CCR1_MSIZE;

    // 2.3 ��ַ��������������
    DMA1_Channel1->CCR |= DMA_CCR1_PINC;
    DMA1_Channel1->CCR |= DMA_CCR1_MINC;

    // 2.4 �������ݴ�������жϱ�־
    DMA1_Channel1->CCR |= DMA_CCR1_TCIE;

    // 3. NVIC����
    NVIC_SetPriorityGrouping(3);
    NVIC_SetPriority(DMA1_Channel1_IRQn, 2);
    NVIC_EnableIRQ(DMA1_Channel1_IRQn);

}

// ���ݴ���
void DMA1_Transmit(uint32_t srcAddr, uint32_t destAddr, uint16_t dataLen)
{
    // 1. ���������ַ
    DMA1_Channel1->CPAR = destAddr;

    // 2. ���ô洢����ַ
    DMA1_Channel1->CMAR = srcAddr;

    // 3. ���ô����������
    DMA1_Channel1->CNDTR = dataLen;

    // 4. ����ͨ������ʼ��������
    DMA1_Channel1->CCR |= DMA_CCR1_EN;
}

// �жϷ������
void DMA1_Channel1_IRQHandler(void)
{
    // �ж��жϱ�־λ
    if (DMA1->ISR & DMA_ISR_TCIF1)
    {
        // ����жϱ�־λ
        DMA1->IFCR |= DMA_IFCR_CTCIF1;

        // �ر�DMAͨ��
        DMA1_Channel1->CCR &= ~DMA_CCR1_EN;

        // isFinished = 1;
    }
    
}
