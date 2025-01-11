#ifndef __I2C_H__
#define __I2C_H__

#include <stdio.h>
#include "delay.h"

/*
    I2C0 硬实现
 */

// 使用快速模式还是标准模式
#define USE_FAST_MODE   1

#define OK      0
#define FAIL    -1
#define ACK     0
#define NACK    1

void I2C0_init(void);
void I2C0_write_bytes(uint8_t dev_addr, uint8_t reg_addr, uint8_t* buff, uint16_t size);
uint8_t I2C0_write_offset(uint8_t dev_addr, uint8_t reg_addr, uint8_t* buff, uint8_t offset, uint16_t size);
uint8_t I2C0_read_bytes(uint8_t dev_addr, uint8_t reg_addr, uint8_t *buff, uint16_t size);

#endif /* __I2C_H__ */
