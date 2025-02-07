#ifndef __TIMER6_H__
#define __TIMER6_H__

/*
    timer6、timer7 均为基础定时器
 */

#include "stm32f4xx.h"

void Timer6_init(void);

extern void Timer6_callback(void);

#endif /* __TIMER6_H__ */
