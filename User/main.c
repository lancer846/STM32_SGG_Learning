#include "stm32f4xx.h"

#include "delay.h"
#include "led.h"
#include "key.h"
/**
 * @brief 使用外部中断实现 LED 的切换效果
 */

// 全局变量，表示当前流水灯状态
FLOW_LED flow_led = INIT;
int main(void)
{
	LED_init();
	KEY_init();

	while (1)
	{
		switch (flow_led)
		{
		case L1:
			LED_off(LED8);
			LED_on(LED1);
			break;
		case L2:
			LED_off(LED1);
			LED_on(LED2);
			break;
		case L3:
			LED_off(LED2);
			LED_on(LED3);
			break;
		case L4:
			LED_off(LED3);
			LED_on(LED4);
			break;
		case L5:
			LED_off(LED4);
			LED_on(LED5);
			break;
		case L6:
			LED_off(LED5);
			LED_on(LED6);
			break;
		case L7:
			LED_off(LED6);
			LED_on(LED7);
			break;
		case L8:
			LED_off(LED7);
			LED_on(LED8);
			break;

		default:
			break;
		}
	}
}
