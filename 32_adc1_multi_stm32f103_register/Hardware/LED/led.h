/*
 * @Author: wushengran
 * @Date: 2024-05-24 15:39:25
 * @Description: 
 * 
 * Copyright (c) 2024 by atguigu, All Rights Reserved. 
 */
#ifndef __LED_H
#define __LED_H

#include "stm32f10x.h"

// �궨��
#define LED1 GPIO_ODR_ODR0
#define LED2 GPIO_ODR_ODR1
#define LED3 GPIO_ODR_ODR8

// ��ʼ��
void LED_Init(void);

// ����ĳ��LED�Ŀ���
void LED_On(uint16_t led);
void LED_Off(uint16_t led);

// ��תLED״̬
void LED_Toggle(uint16_t led);

// ��һ��LED�ƣ�ȫ��ȫ��
void LED_OnAll(uint16_t leds[], uint8_t size);
void LED_OffAll(uint16_t leds[], uint8_t size);

#endif
