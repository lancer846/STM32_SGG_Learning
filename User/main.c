#include "stm32f4xx.h"

#include "delay.h"
#include "led.h"
#include "key.h"
#include "usart.h"
/**
 * @brief ʹ�ô����ж�ʵ�����ݽ���
 */
void USART_receive_callback(uint8_t *buff, uint8_t size) {
	// ���յ�������ԭ������
	USART_send_string(buff, size);
}

// ȫ�ֱ�������ʾ��ǰ��ˮ��״̬
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
