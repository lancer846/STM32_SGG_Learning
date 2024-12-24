#include "stm32f4xx.h"

// ���� PB2
void LED_on() {
	// ����ʱ�� rcc��GPIO �˿� B ʱ��ʹ��
	//*(uint32_t *)(0x40023800 + 0x30) |= (1 << 1);
	//RCC->AHB1ENR |= (1 << 1);
	RCC->AHB1ENR |= RCC_AHB1ENR_GPIOBEN;
	
	// �˿� B �������ģʽ
	//*(uint32_t *)(0x40020400 + 0x00) = 0x00000290;
	//GPIOB->MODER = 0x0290;
	GPIOB->MODER |= GPIO_MODER_MODER2_0;

	// �˿��������ģʽ��Ĭ�Ͼ�������ģʽ��
	//*(uint32_t *)(0x40020400 + 0x04) = 0x00000000;
	//GPIOB->OTYPER = 0x00000000;

	// �˿�����ٶȣ������ٶ����
	//*(uint32_t *)(0x40020400 + 0x08) = 0x000000F0;
	//GPIOB->OSPEEDR = 0x000000F0;
	GPIOB->OSPEEDR |= GPIO_OSPEEDER_OSPEEDR2;
	
	// �˿����ø���ģʽ���������������裬Ĭ�Ͼ������ģʽ��
	//*(uint32_t *)(0x40020400 + 0x0C) = 0x00000100;
	//GPIOB->PUPDR = 0x00000100;
	
	// �˿�����ߵ�ƽ
	//*(uint32_t *)(0x40020400 + 0x14) = 0x04;
	//GPIOB->ODR = 0x04;
	GPIOB->ODR |= GPIO_ODR_ODR_2;
}

int main(void) {
	
	LED_on();
	
	while(1);
}
