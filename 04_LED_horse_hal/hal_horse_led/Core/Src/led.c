#include "led.h"


void LED_on(uint16_t led) {
    HAL_GPIO_WritePin(LED_PORT, led, GPIO_PIN_RESET);
}
void LED_off(uint16_t led) {
    HAL_GPIO_WritePin(LED_PORT, led, GPIO_PIN_SET);
}
void LED_toggle(uint16_t led) {
    HAL_GPIO_TogglePin(LED_PORT, led);
}

void LED_all_on(uint16_t leds[], uint8_t length) {
    for (uint8_t i = 0; i < length; i++)
    {
        LED_on(leds[i]);
    }
}
void LED_all_off(uint16_t leds[], uint8_t length) {
    for (uint8_t i = 0; i < length; i++)
    {
        LED_off(leds[i]);
    }
}
