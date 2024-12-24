#include "stm32f4xx.h"

/**
 * @brief ʵ�������Ч��
 * PC6 Ϊ PNP ������
 * ���� PD8��PD9��PD10
 */

void Delay_us(uint16_t time_us)
{
	/*
		���õδ�ʱ�����������ʽΪ����ʱ��--����ϵͳ��ƵΪ 168MHz��Ҳ���� 1/168 us
	*/

	// ����װ��ֵ
	SysTick->LOAD = time_us * 168;
	// ����ϵͳʱ�ӣ�1�������������������жϣ�0����ʹ�ܶ�ʱ��
	SysTick->CTRL |= 0x00000005;
	// �ȴ���������
	while (!(SysTick->CTRL & SysTick_CTRL_COUNTFLAG_Msk))
		;
	// ���������־λ
	SysTick->CTRL &= ~SysTick_CTRL_COUNTFLAG_Msk;
	// �رն�ʱ��
	SysTick->CTRL &= ~SysTick_CTRL_ENABLE_Msk;
}

void GPIO_config()
{
	// ����ʱ�� rcc��GPIO �˿� C��D ʱ��ʹ��
	RCC->AHB1ENR |= RCC_AHB1ENR_GPIOCEN | RCC_AHB1ENR_GPIODEN;

	// �˿� C��D �������ģʽ
	GPIOC->MODER |= GPIO_MODER_MODER6_0;
	GPIOD->MODER |= GPIO_MODER_MODER8_0 | GPIO_MODER_MODER9_0 | GPIO_MODER_MODER10_0;

	// �˿��������ģʽ��Ĭ�Ͼ�������ģʽ��
	// GPIOB->OTYPER = 0x00000000;

	// �˿�����ٶȣ������ٶ����
	GPIOC->OSPEEDR |= GPIO_OSPEEDER_OSPEEDR6;
	GPIOD->OSPEEDR |= GPIO_OSPEEDER_OSPEEDR8 | GPIO_OSPEEDER_OSPEEDR9 | GPIO_OSPEEDER_OSPEEDR10;

	// �˿����ø���ģʽ���������������裬Ĭ�Ͼ������ģʽ��
	// GPIOB->PUPDR = 0x00000100;

	// �˿�����͵�ƽ����ͨ������
	GPIOC->ODR |= GPIO_ODR_ODR_6;
	// Ϩ������ LED
	GPIOD->ODR |= GPIO_ODR_ODR_8 | GPIO_ODR_ODR_9 | GPIO_ODR_ODR_10;
}

int main(void)
{

	GPIO_config();

	while (1)
	{
		// PD8��PD9��PD10 ��������Ϩ��
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
