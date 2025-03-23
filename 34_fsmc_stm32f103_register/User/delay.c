/*
 * @Author: wushengran
 * @Date: 2024-05-24 15:40:21
 * @Description: 
 * 
 * Copyright (c) 2024 by atguigu, All Rights Reserved. 
 */
#include "delay.h"

// ��ʱ������΢����Ϊ��λ������ϵͳ��શ�ʱ����72MHz��һ����� 1/72 us
void Delay_us(uint16_t us)
{
	// 1. װ��һ������ֵ��72 * us
	SysTick->LOAD = 72 * us;

	// 2. ���ã�ʹ��ϵͳʱ�ӣ�1�������������������жϣ�0����ʹ�ܶ�ʱ����1��
	SysTick->CTRL = 0x05;

	// 3. �ȴ�����ֵ��Ϊ0���ж�CTRL��־λCOUNTFLAG�Ƿ�Ϊ1
	while ((SysTick->CTRL & SysTick_CTRL_COUNTFLAG) == 0)
	{}
	
	// 4. �رն�ʱ��
	SysTick->CTRL &= ~SysTick_CTRL_ENABLE;
}

void Delay_ms(uint16_t ms)
{
	while (ms--)
	{
		Delay_us(1000);
	}
}

void Delay_s(uint16_t s)
{
	while (s--)
	{
		Delay_ms(1000);
	}
}
