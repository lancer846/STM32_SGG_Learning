#ifndef __ADC_H__
#define __ADC_H__

#include "stm32f10x.h"

/**
 * ADC1 单通道转换
 * 
 */

// ADC1 初始化配置
void ADC1_Init(void);
// ADC1 开启转换
void ADC1_StartConvert(void);
// ADC1 读取转换结果
double ADC1_GetResult(void);

#endif /* __ADC_H__ */
