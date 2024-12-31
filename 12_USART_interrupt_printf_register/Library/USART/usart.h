#ifndef __USART_H__
#define __USART_H__

#include "stm32f4xx.h"
#include "stdio.h"

#define USE_PRINTF 1

#define USE_RECEIVE_CALLBACK 1
#define RECEIVE_BUFF_MAX_SIZE 128

#if USE_RECEIVE_CALLBACK
// 接收回调函数
extern void USART_receive_callback(uint8_t *buff, uint8_t size);
#endif

void USART_init(void);

// 发送单个字符
void USART_send_char(uint8_t ch);

// 发送字符串
void USART_send_string(uint8_t *str, uint8_t size);

#endif /* __USART_H__ */
