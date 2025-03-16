#ifndef __ADC_H__
#define __ADC_H__

#include "stm32f10x.h"

/**
 * ADC1 多通道转换，使用 DMA
 * channel10: PC0
 * channel12: PC2
 */

// ADC1 初始化配置
void ADC1_Init(void);
// ADC1 DMA 初始化配置
void ADC1_DMA_Init(void);
// ADC1 开启转换
void ADC1_DMA_StartConvert(uint16_t* buff, uint8_t size);

#endif /* __ADC_H__ */
