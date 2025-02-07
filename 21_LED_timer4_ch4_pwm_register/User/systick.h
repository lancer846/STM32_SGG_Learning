#ifndef __SYSTICK_H__
#define __SYSTICK_H__

#include "stm32f4xx.h"

void Systick_init(void);

extern void systick_interrupt_handler(void);

#endif /* __SYSTICK_H__ */
