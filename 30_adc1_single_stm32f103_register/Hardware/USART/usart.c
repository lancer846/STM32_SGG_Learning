/*
 * @Author: wushengran
 * @Date: 2024-05-28 15:30:08
 * @Description: 
 * 
 * Copyright (c) 2024 by atguigu, All Rights Reserved. 
 */
#include "usart.h"

// ��ʼ��
void USART_Init(void)
{
    // 1. ����ʱ��
    RCC->APB2ENR |= RCC_APB2ENR_IOPAEN;
    RCC->APB2ENR |= RCC_APB2ENR_USART1EN;

    // 2. GPIO����ģʽ
    // PA9: �������������CNF-10��MODE-11
    // PA10: �������룬CNF-01��MODE-00
    GPIOA->CRH |= GPIO_CRH_MODE9;
    GPIOA->CRH |= GPIO_CRH_CNF9_1;
    GPIOA->CRH &= ~GPIO_CRH_CNF9_0;

    GPIOA->CRH &= ~GPIO_CRH_MODE10;
    GPIOA->CRH &= ~GPIO_CRH_CNF10_1;
    GPIOA->CRH |= GPIO_CRH_CNF10_0;

    // 3. ��������
    // 3.1 ����������
    USART1->BRR = 0x271;

    // 3.2 �շ�ʹ�ܼ�ģ��ʹ��
    USART1->CR1 |= (USART_CR1_UE | USART_CR1_TE | USART_CR1_RE);

    // 3.3 �������ã���������֡��ʽ
    USART1->CR1 &= ~USART_CR1_M;
    USART1->CR1 &= ~USART_CR1_PCE;
    USART1->CR2 &= ~USART_CR2_STOP;
}

// ����һ���ַ�
void USART_SendChar(uint8_t ch)
{
    // �ж�SR��TXE�Ƿ�Ϊ1
    while ((USART1->SR & USART_SR_TXE) == 0)
    {}

    // ��DRд���µ�Ҫ���͵�����
    USART1->DR = ch;
}

// ����һ���ַ�
uint8_t USART_ReceiveChar(void)
{
    while ((USART1->SR & USART_SR_RXNE) == 0)
    {
        // �����жϿ���֡������
        if (USART1->SR & USART_SR_IDLE)
        {
            return 0;
        }    
    }

    // ��ȡ�Ѿ����յ������ݣ��ȴ�������һ������
    return USART1->DR;
}

// �����ַ���
void USART_SendString(uint8_t *str, uint8_t size)
{
    for (uint8_t i = 0; i < size; i++)
    {
        USART_SendChar(str[i]);
    } 
}

// �����ַ���
void USART_ReceiveString(uint8_t buffer[], uint8_t *size)
{
    // ����һ�����������������Ѿ����յ����ַ�����
    uint8_t i = 0;

    while ((USART1->SR & USART_SR_IDLE) == 0)
    {
        buffer[i] = USART_ReceiveChar();
        i++;
    }

    // ���IDLEλ
    // USART1->SR;
    USART1->DR;
    
    *size = --i;
}

// ��дfputc
int fputc(int ch, FILE * file)
{
    // ֱ�ӽ��ַ����͵�����
    USART_SendChar(ch);
    return ch;
}
