#ifndef __FSMC_H__
#define __FSMC_H__

#include "stm32f10x.h"

/*
    该套开发板扩展的是 FSMC bank1 3 区域，起始地址是 0x6800 0000
*/

// 只需要初始化即可
void FSMC_Init(void);

#endif /* __FSMC_H__ */
