#include "stm32f4xx.h"

#include "delay.h"
#include "led.h"
/**
 * @brief 实现跑马灯效果
 * PC6 为 PNP 三极管
 * 点亮 PD8、PD9、PD10
 */
int main(void)
{

	LED_init();

	uint32_t LED_list[8] = {LED1, LED2, LED3, LED4, LED5, LED6, LED7, LED8};
	while (1)
	{
		for (uint8_t i = 0; i < 8; i++)
		{
			LED_on(LED_list[i]);
			Delay_ms(500);
			LED_off(LED_list[i]);
		}
		
	}
}
