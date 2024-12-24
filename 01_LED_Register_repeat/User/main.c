#include "stm32f4xx.h"

// 点亮 PB2
void LED_on() {
	// 配置时钟 rcc，GPIO 端口 B 时钟使能
	//*(uint32_t *)(0x40023800 + 0x30) |= (1 << 1);
	//RCC->AHB1ENR |= (1 << 1);
	RCC->AHB1ENR |= RCC_AHB1ENR_GPIOBEN;
	
	// 端口 B 配置输出模式
	//*(uint32_t *)(0x40020400 + 0x00) = 0x00000290;
	//GPIOB->MODER = 0x0290;
	GPIOB->MODER |= GPIO_MODER_MODER2_0;

	// 端口输出推挽模式（默认就是推挽模式）
	//*(uint32_t *)(0x40020400 + 0x04) = 0x00000000;
	//GPIOB->OTYPER = 0x00000000;

	// 端口输出速度，配置速度最大
	//*(uint32_t *)(0x40020400 + 0x08) = 0x000000F0;
	//GPIOB->OSPEEDR = 0x000000F0;
	GPIOB->OSPEEDR |= GPIO_OSPEEDER_OSPEEDR2;
	
	// 端口配置浮空模式（无上拉下拉电阻，默认就是这个模式）
	//*(uint32_t *)(0x40020400 + 0x0C) = 0x00000100;
	//GPIOB->PUPDR = 0x00000100;
	
	// 端口输出高电平
	//*(uint32_t *)(0x40020400 + 0x14) = 0x04;
	//GPIOB->ODR = 0x04;
	GPIOB->ODR |= GPIO_ODR_ODR_2;
}

int main(void) {
	
	LED_on();
	
	while(1);
}
