#include "usart.h"
#include "dma.h"
#include "adc.h"
#include "delay.h"

int main(void)
{
	// 初始化
	USART_Init();
	ADC1_Init();
	ADC1_DMA_Init();

	printf("Hello, world!\n");

	uint16_t buff[2] = {0};
	// 开启 ADC 转换
	ADC1_DMA_StartConvert(buff, 2);

	while (1)
	{
		printf("this voltage is channel10 %.2f, channel12 %.2f\r\n", buff[0] * 3.3 / 4095, buff[1] * 3.3 / 4095);
		Delay_s(1);
	}
}
