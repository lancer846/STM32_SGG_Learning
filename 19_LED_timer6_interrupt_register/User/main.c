#include "stm32f4xx.h"

#include "delay.h"
#include "led.h"
#include "systick.h"
#include "timer6.h"
/**
 * @brief ʵ�������Ч��
 * PC6 Ϊ PNP ������
 * ���� PD8��PD9��PD10
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

void Timer6_callback(void)
{
	LED_toggle(LED2);
}

int main(void)
{
	Systick_init();
	Timer6_init();
	LED_init();

	while (1)
	{
	}
}
