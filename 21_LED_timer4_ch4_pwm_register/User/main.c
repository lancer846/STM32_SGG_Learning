#include "stm32f4xx.h"

#include "delay.h"
#include "led.h"
#include "systick.h"
#include "timer6.h"
#include "timer4.h"
/**
 * @brief 实现跑马灯效果
 * PC6 为 PNP 三极管
 * 点亮 PD8、PD9、PD10
 */

#define UP 0   // 向上
#define DOWN 1 // 向下

uint32_t count = 0;
void systick_interrupt_handler(void)
{
	count++;
	if (count % 500 == 0)
	{
		LED_toggle(LED1);
	}
}

void Timer6_callback(void)
{
	LED_toggle(LED2);
}

int main(void)
{
	Systick_init();
	// Timer6_init();
	LED_init();
	Timer4_init();

	Timer4_start();

	// 记录呼吸灯的方向和占空比的值
	uint8_t dir = UP;
	int dutyVal = 0;

	while (1)
	{
		if (dir == UP)
		{
			// duty 的值向上增长
			if (dutyVal >= 99)
			{
				dir = DOWN;
			}
			else
			{
				dutyVal += 1;
			}
		}
		else
		{
			// duty 的值向下减少
			if (dutyVal <= 0)
			{
				dir = UP;
			}
			else
			{
				dutyVal -= 1;
			}
		}
		Timer4_setDutyCircle(dutyVal);
		// 需要添加延时
		Delay_ms(20);
	}
}
