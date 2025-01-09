#include "stm32f4xx.h"

#include "delay.h"
#include "led.h"
#include "key.h"
#include "usart.h"
#include "i2c.h"
#include "oled.h"
#include "bmp.h"
/**
 * @brief 使用串口中断实现数据交互
 */
void USART_receive_callback(uint8_t *buff, uint8_t size)
{
	// 接收到的数据原样返回
	USART_send_string(buff, size);
}

// 全局变量，表示当前流水灯状态
FLOW_LED flow_led = INIT;
int main(void)
{
	USART_init();
	I2C0_init();

	printf("start printf\n");
	int i = 10;
	printf("%d\n", i);

	u8 t = ' ';
	OLED_Init(); // 初始化OLED
	while (1)
	{
		OLED_ShowPicture(0, 0, 128, 64, BMP1, 1);
		OLED_Refresh();
		delay_1ms(500);
		OLED_Clear();
		OLED_ShowChinese(0, 0, 0, 16, 1);	// 中
		OLED_ShowChinese(18, 0, 1, 16, 1);	// 景
		OLED_ShowChinese(36, 0, 2, 16, 1);	// 园
		OLED_ShowChinese(54, 0, 3, 16, 1);	// 电
		OLED_ShowChinese(72, 0, 4, 16, 1);	// 子
		OLED_ShowChinese(90, 0, 5, 16, 1);	// 技
		OLED_ShowChinese(108, 0, 6, 16, 1); // 术
		OLED_ShowString(8, 16, (u8 *)"ZHONGJINGYUAN", 16, 1);
		OLED_ShowString(20, 32, (u8 *)"2014/05/01", 16, 1);
		OLED_ShowString(0, 48, (u8 *)"ASCII:", 16, 1);
		OLED_ShowString(63, 48, (u8 *)"CODE:", 16, 1);
		OLED_ShowChar(48, 48, t, 16, 1); // 显示ASCII字符
		t++;
		if (t > '~')
			t = ' ';
		OLED_ShowNum(103, 48, t, 3, 16, 1);
		OLED_Refresh();
		delay_1ms(500);
		OLED_Clear();
		OLED_ShowChinese(0, 0, 0, 16, 1);	// 16*16 中
		OLED_ShowChinese(16, 0, 0, 24, 1);	// 24*24 中
		OLED_ShowChinese(24, 20, 0, 32, 1); // 32*32 中
		OLED_ShowChinese(64, 0, 0, 64, 1);	// 64*64 中
		OLED_Refresh();
		delay_1ms(500);
		OLED_Clear();
		OLED_ShowString(0, 0, (u8 *)"ABC", 8, 1);	// 6*8 “ABC”
		OLED_ShowString(0, 8, (u8 *)"ABC", 12, 1);	// 6*12 “ABC”
		OLED_ShowString(0, 20, (u8 *)"ABC", 16, 1); // 8*16 “ABC”
		OLED_ShowString(0, 36, (u8 *)"ABC", 24, 1); // 12*24 “ABC”
		OLED_Refresh();
		delay_1ms(500);
		OLED_ScrollDisplay(11, 4, 1);
	}
}
