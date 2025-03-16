/*
 * @Author: wushengran
 * @Date: 2024-05-23 15:14:48
 * @Description: 
 * 
 * Copyright (c) 2024 by atguigu, All Rights Reserved. 
 */
#include "usart.h"
#include "dma.h"
#include "adc.h"
#include "delay.h"

int main(void)
{
	// ≥ı ºªØ
	USART_Init();
	DMA1_Init();
	ADC1_Init();

	printf("Hello, world!\n");

	ADC1_StartConvert();

	double vol = 0;
	while(1)
	{
		vol = ADC1_GetResult();
		printf("this voltage is %.2f\r\n", vol);
		Delay_s(1);
	}
}
