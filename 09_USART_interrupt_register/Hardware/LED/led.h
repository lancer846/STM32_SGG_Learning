#ifndef __LED_H__
#define __LED_H__

#include "stm32f4xx.h"

#define LED1 GPIO_ODR_ODR_8
#define LED2 GPIO_ODR_ODR_9
#define LED3 GPIO_ODR_ODR_10
#define LED4 GPIO_ODR_ODR_11
#define LED5 GPIO_ODR_ODR_12
#define LED6 GPIO_ODR_ODR_13
#define LED7 GPIO_ODR_ODR_14
#define LED8 GPIO_ODR_ODR_15

void LED_init(void);
void LED_on(uint32_t LED);
void LED_off(uint32_t LED);
void LED_toggle(uint32_t LED);

void LED_all_on(uint32_t LED_list[], uint8_t len);
void LED_all_off(uint32_t LED_list[], uint8_t len);

#endif /* __LED_H__ */
