#ifndef __I2C_H__
#define __I2C_H__

#include "delay.h"

/*
    I2C0 软实现
 */

#define I2C0_SCL_PORT GPIOB
#define I2C0_SDA_PORT GPIOB
#define ACK     0
#define NACK    1
// 输出
#define I2C0_SCL_HIGH()     (GPIOB->ODR |= GPIO_ODR_ODR_6)
#define I2C0_SCL_LOW()      (GPIOB->ODR &= ~GPIO_ODR_ODR_6)
#define I2C0_SDA_HIGH()     (GPIOB->ODR |= GPIO_ODR_ODR_7)
#define I2C0_SDA_LOW()      (GPIOB->ODR &= ~GPIO_ODR_ODR_7)
// 读取
#define I2C0_READ_SDA()     (GPIOB->IDR & GPIO_ODR_ODR_7)
// 延时（I2C 快速模式为 400Kbits/s，也就是 2us 传输一位）
#define I2C0_DELAY()        Delay_us(2)

void I2C0_init(void);
void I2C0_write_bytes(uint8_t dev_addr, uint8_t reg_addr, uint8_t* buff, uint16_t size);
uint8_t I2C0_write_offset(uint8_t dev_addr, uint8_t reg_addr, uint8_t* buff, uint8_t offset, uint16_t size);
uint8_t I2C0_read_bytes(uint8_t dev_addr, uint8_t reg_addr, uint8_t *buff, uint16_t size);

#endif /* __I2C_H__ */
