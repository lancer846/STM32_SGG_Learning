#include "led.h"

void LED_init() {
    // 配置时钟 rcc，GPIO 端口 C、D 时钟使能
	RCC->AHB1ENR |= RCC_AHB1ENR_GPIOCEN | RCC_AHB1ENR_GPIODEN;

	// 端口 C、D 配置输出模式
	GPIOC->MODER |= GPIO_MODER_MODER6_0;
	GPIOD->MODER |= GPIO_MODER_MODER8_0 | GPIO_MODER_MODER9_0 | GPIO_MODER_MODER10_0 | GPIO_MODER_MODER11_0 | GPIO_MODER_MODER12_0 | GPIO_MODER_MODER13_0 | GPIO_MODER_MODER14_0 | GPIO_MODER_MODER15_0;

	// 端口输出推挽模式（默认就是推挽模式）
	// GPIOB->OTYPER = 0x00000000;

	// 端口输出速度，配置速度最大
	GPIOC->OSPEEDR |= GPIO_OSPEEDER_OSPEEDR6;
	GPIOD->OSPEEDR |= GPIO_OSPEEDER_OSPEEDR8 | GPIO_OSPEEDER_OSPEEDR9 | GPIO_OSPEEDER_OSPEEDR10 | GPIO_OSPEEDER_OSPEEDR11 | GPIO_OSPEEDER_OSPEEDR12 | GPIO_OSPEEDER_OSPEEDR13 | GPIO_OSPEEDER_OSPEEDR14 | GPIO_OSPEEDER_OSPEEDR15;

	// 端口配置浮空模式（无上拉下拉电阻，默认就是这个模式）
	// GPIOB->PUPDR = 0x00000100;

	// 端口输出低电平，开通三极管
	GPIOC->ODR &= ~GPIO_ODR_ODR_6;
	// 熄灭所有 LED
	LED_off(LED1);
	LED_off(LED2);
	LED_off(LED3);
	LED_off(LED4);
	LED_off(LED5);
	LED_off(LED6);
	LED_off(LED7);
	LED_off(LED8);
}
void LED_on(uint32_t LED) {
    GPIOD->ODR &= ~LED;
}
void LED_off(uint32_t LED) {
    GPIOD->ODR |= LED;
}
void LED_toggle(uint32_t LED) {
    // 先读取当前的 bit 电平
    if(GPIOD->IDR & LED) {
        GPIOD->ODR &= ~LED;
    } else {
        GPIOD->ODR |= LED;
    }
}

void LED_all_on(uint32_t LED_list[], uint8_t len) {
    for (uint8_t i = 0; i < 8; i++)
    {
        LED_on(LED_list[i]);
    }
}
void LED_all_off(uint32_t LED_list[], uint8_t len) {
    for (uint8_t i = 0; i < 8; i++)
    {
        LED_off(LED_list[i]);
    }
}
