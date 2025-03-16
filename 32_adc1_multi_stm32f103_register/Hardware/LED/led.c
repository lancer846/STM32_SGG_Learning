#include "led.h"

// ��ʼ��
void LED_Init(void)
{
    // 1. ʱ������
	RCC->APB2ENR |= RCC_APB2ENR_IOPAEN;
	
	// 2. GPIO����ģʽ����
	GPIOA->CRL &= ~GPIO_CRL_CNF0;
	GPIOA->CRL |= GPIO_CRL_MODE0;
	
	GPIOA->CRL &= ~GPIO_CRL_CNF1;
	GPIOA->CRL |= GPIO_CRL_MODE1;
	
	GPIOA->CRH &= ~GPIO_CRH_CNF8;
	GPIOA->CRH |= GPIO_CRH_MODE8;
	
	
	// 3. PA0��PA1��PA8����ߵ�ƽ��Ĭ�Ϲص�
    LED_Off(LED1);
    LED_Off(LED2);
    LED_Off(LED3);
}

// ����ĳ��LED�Ŀ���
void LED_On(uint16_t led)
{
    GPIOA->ODR &= ~led;
}
void LED_Off(uint16_t led)
{
    GPIOA->ODR |= led;
}

// ��תLED״̬
void LED_Toggle(uint16_t led)
{
    // ��Ҫ���жϵ�ǰLED״̬����ȡIDR��Ӧλ
    if ((GPIOA->IDR & led) == 0)
    {
        LED_Off(led);
    }
    else
    {
        LED_On(led);
    }  
}

// ��һ��LED�ƣ�ȫ��ȫ��
void LED_OnAll(uint16_t leds[], uint8_t size)
{
    for (uint8_t i = 0; i < size; i++)
    {
        LED_On(leds[i]);
    }
}

void LED_OffAll(uint16_t leds[], uint8_t size)
{
    for (uint8_t i = 0; i < size; i++)
    {
        LED_Off(leds[i]);
    }
}
