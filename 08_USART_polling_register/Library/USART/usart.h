#ifndef __USART_H__
#define __USART_H__

#include "stm32f4xx.h"

void USART_init(void);

// 发送 / 接收 单个字符
void USART_send_char(uint8_t ch);
uint8_t USART_receive_char(void);

// 发送 / 接收 字符串
void USART_send_string(uint8_t *str, uint8_t size);
uint8_t USART_receive_string(uint8_t *str);

#endif /* __USART_H__ */
