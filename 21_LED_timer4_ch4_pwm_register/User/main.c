#include "stm32f4xx.h"

#include "delay.h"
#include "led.h"
#include "systick.h"
#include "timer6.h"
#include "timer4.h"
/**
 * @brief ʵ�������Ч��
 * PC6 Ϊ PNP ������
 * ���� PD8��PD9��PD10
 */

#define UP 0   // ����
#define DOWN 1 // ����

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

	// ��¼�����Ƶķ����ռ�ձȵ�ֵ
	uint8_t dir = UP;
	int dutyVal = 0;

	while (1)
	{
		if (dir == UP)
		{
			// duty ��ֵ��������
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
			// duty ��ֵ���¼���
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
		// ��Ҫ�����ʱ
		Delay_ms(20);
	}
}
