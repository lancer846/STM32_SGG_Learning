#include "usart.h"
#include "fsmc.h"
#include "delay.h"

// Ҳ����ʹ�ùؼ��ֽ�������ַ�洢�� FSMC ��
// __attribute__ at ֻ��ָ��ȫ�ֱ����ĵ�ַ�����ҳ�ʼ���ǲ��ܸ�ֵ�����ҵ�ַ��Ҫ 4 ���ֽڶ��루���ƽϴ�
uint16_t v1 __attribute__((at(0x68001000)));
uint8_t v2 __attribute__((at(0x68001004)));

int main(void)
{
	// ��ʼ��
	USART_Init();

	printf("Hello, world!\n");

	FSMC_Init();

	v1 = 55555;
	v2 = 22;

	uint16_t *p = (uint16_t *)0x68000000;
	*p = 44444;
	uint8_t *f = (uint8_t *)0x68000002;
	*f = 33;

	while (1)
	{
		printf("v1 = %d, @p = %p\r\n", v1, &v1);
		printf("v2 = %d, @p = %p\r\n", v2, &v2);
		printf("p = %d, @p = %p\r\n", *p, p);
		printf("f = %d, @p = %p\r\n", *f, f);
		Delay_s(1);
	}
}
