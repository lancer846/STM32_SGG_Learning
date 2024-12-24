#ifndef __LED_H__
#define __LED_H__

#include "gpio.h"
#define LED_PORT GPIOD

void LED_on(uint16_t led);
void LED_off(uint16_t led);
void LED_toggle(uint16_t led);

void LED_all_on(uint16_t leds[], uint8_t length);
void LED_all_off(uint16_t leds[], uint8_t length);

#endif /* __LED_H__ */
