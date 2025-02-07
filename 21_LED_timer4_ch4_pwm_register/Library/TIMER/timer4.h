#ifndef __TIMER4_H__
#define __TIMER4_H__

/*
    timer4 为通用定时器
    此处使用 timer4 ch4 通道
 */

#include "stm32f4xx.h"

// 定时器初始化
void Timer4_init(void);

// 定时器启动
void Timer4_start(void);
// 定时器停止
void Timer4_stop(void);

// PWM 占空比设置
void Timer4_setDutyCircle(uint8_t dutyCircle);

#endif /* __TIMER4_H__ */
