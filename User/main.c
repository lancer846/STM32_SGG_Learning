#include "stm32f4xx.h"

#include "delay.h"
#include "led.h"
#include "key.h"
#include "usart.h"
/**
 * @brief 使用串口中断实现数据交互
 */
void USART_receive_callback(uint8_t *buff, uint8_t size) {
	// 接收到的数据原样返回
	USART_send_string(buff, size);
}

// 全局变量，表示当前流水灯状态
FLOW_LED flow_led = INIT;
int main(void)
{
	USART_init();

	printf("start printf\n");
	int i = 10;
	printf("%d\n", i);
	while (1)
	{
	}
}
