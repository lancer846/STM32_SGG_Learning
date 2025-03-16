/*
 * @Author: wushengran
 * @Date: 2024-06-07 11:35:52
 * @Description: 
 * 
 * Copyright (c) 2024 by atguigu, All Rights Reserved. 
 */
#ifndef __DMA_H
#define __DMA_H

#include "stm32f10x.h"

// extern uint8_t isFinished;

// 初始化
void DMA1_Init(void);

// 数据传输
void DMA1_Transmit(uint32_t srcAddr, uint32_t destAddr, uint16_t dataLen);

#endif
