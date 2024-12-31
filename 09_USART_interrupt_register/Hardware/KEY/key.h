#ifndef __KEY_H__
#define __KEY_H__

#include "stm32f4xx.h"
#include "delay.h"
#include "led.h"

/**
 * @brief 使用按键引脚为 PA0
 * 
 */

typedef enum {
    INIT = -1, // 初始状态
    L1, // LED1 亮起
    L2, // LED2 亮起
    L3, // LED3 亮起
    L4, // LED4 亮起
    L5, // LED5 亮起
    L6, // LED6 亮起
    L7, // LED7 亮起
    L8, // LED8 亮起
} FLOW_LED;

extern FLOW_LED flow_led;

void KEY_init(void);

#endif /* __KEY_H__ */
