#include "stm32f4xx.h"

/**
 * @brief 实现跑马灯效果
 * PC6 为 PNP 三极管
 * 点亮 PD8、PD9、PD10
 */

void Delay_us(uint16_t time_us)
{
	/*
		设置滴答定时器，其计数方式为倒计时（--），系统主频为 168MHz，也就是 1/168 us
	*/

	// 设置装载值
	SysTick->LOAD = time_us * 168;
	// 配置系统时钟（1），计数结束不产生中断（0），使能定时器
	SysTick->CTRL |= 0x00000005;
	// 等待计数结束
	while (!(SysTick->CTRL & SysTick_CTRL_COUNTFLAG_Msk))
		;
	// 清除计数标志位
	SysTick->CTRL &= ~SysTick_CTRL_COUNTFLAG_Msk;
	// 关闭定时器
	SysTick->CTRL &= ~SysTick_CTRL_ENABLE_Msk;
}

void GPIO_config()
{
	// 配置时钟 rcc，GPIO 端口 C、D 时钟使能
	RCC->AHB1ENR |= RCC_AHB1ENR_GPIOCEN | RCC_AHB1ENR_GPIODEN;

	// 端口 C、D 配置输出模式
	GPIOC->MODER |= GPIO_MODER_MODER6_0;
	GPIOD->MODER |= GPIO_MODER_MODER8_0 | GPIO_MODER_MODER9_0 | GPIO_MODER_MODER10_0;

	// 端口输出推挽模式（默认就是推挽模式）
	// GPIOB->OTYPER = 0x00000000;

	// 端口输出速度，配置速度最大
	GPIOC->OSPEEDR |= GPIO_OSPEEDER_OSPEEDR6;
	GPIOD->OSPEEDR |= GPIO_OSPEEDER_OSPEEDR8 | GPIO_OSPEEDER_OSPEEDR9 | GPIO_OSPEEDER_OSPEEDR10;

	// 端口配置浮空模式（无上拉下拉电阻，默认就是这个模式）
	// GPIOB->PUPDR = 0x00000100;

	// 端口输出低电平，开通三极管
	GPIOC->ODR |= GPIO_ODR_ODR_6;
	// 熄灭所有 LED
	GPIOD->ODR |= GPIO_ODR_ODR_8 | GPIO_ODR_ODR_9 | GPIO_ODR_ODR_10;
}

int main(void)
{

	GPIO_config();

	while (1)
	{
		// PD8、PD9、PD10 轮流点亮熄灭
		GPIOD->ODR &= ~GPIO_ODR_ODR_8;
		Delay_us(500);
		GPIOD->ODR |= GPIO_ODR_ODR_8;

		GPIOD->ODR &= ~GPIO_ODR_ODR_9;
		Delay_us(500);
		GPIOD->ODR |= GPIO_ODR_ODR_9;

		GPIOD->ODR &= ~GPIO_ODR_ODR_10;
		Delay_us(500);
		GPIOD->ODR |= GPIO_ODR_ODR_10;
	}
}
