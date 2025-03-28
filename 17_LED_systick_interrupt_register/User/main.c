#include "stm32f4xx.h"

#include "delay.h"
#include "led.h"
#include "systick.h"
/**
 * @brief 实现跑马灯效果
 * PC6 为 PNP 三极管
 * 点亮 PD8、PD9、PD10
 */

uint32_t count = 0;
void systick_interrupt_handler(void)
{
	count++;
	if (count % 500 == 0)
	{
		LED_toggle(LED1);
	}
}

int main(void)
{
	Systick_init();
	LED_init();

	while (1)
	{
	}
}
