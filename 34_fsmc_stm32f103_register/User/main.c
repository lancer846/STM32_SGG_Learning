#include "usart.h"
#include "fsmc.h"
#include "delay.h"

// 也可以使用关键字将变量地址存储在 FSMC 中
// __attribute__ at 只能指定全局变量的地址，并且初始化是不能赋值，而且地址需要 4 个字节对齐（限制较大）
uint16_t v1 __attribute__((at(0x68001000)));
uint8_t v2 __attribute__((at(0x68001004)));

int main(void)
{
	// 初始化
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
