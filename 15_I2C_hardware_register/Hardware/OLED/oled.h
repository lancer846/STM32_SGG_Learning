#ifndef __OLED_H
#define __OLED_H 

#include "stm32f4xx.h"
#include "stdlib.h"	
//#include "systick.h"
#include "i2c.h"

#define    I2C_WRITE(a,b,c,d)   		I2C0_write_bytes(a,b,c,d)
#define    I2C_WRITE_OFFSET(a,b,c,d,e)  I2C0_write_offset(a,b,c,d,e)
#define    I2C_READ(a,b,c,d)  			I2C0_read_bytes(a,b,c,d)
#define    delay_1us(us)				Delay_us(us)
#define    delay_1ms(ms)				Delay_ms(ms)

#ifndef u8
#define u8 uint8_t
#endif

#ifndef u16
#define u16 uint16_t
#endif

#ifndef u32
#define u32 uint32_t
#endif


//-----------------OLED�˿ڶ���---------------- 


//#define OLED_SCL_Clr() gpio_bit_reset(GPIOB, GPIO_PIN_6) //SCL
//#define OLED_SCL_Set() gpio_bit_set(GPIOB, GPIO_PIN_6)

//#define OLED_SDA_Clr() gpio_bit_reset(GPIOB, GPIO_PIN_7) //SDA
//#define OLED_SDA_Set() gpio_bit_set(GPIOB, GPIO_PIN_7)

//#define OLED_RES_Clr() GPIO_ResetBits(GPIOD,GPIO_Pin_4)//RES
//#define OLED_RES_Set() GPIO_SetBits(GPIOD,GPIO_Pin_4)


#define OLED_CMD  0	//д����
#define OLED_DATA 1	//д����

void OLED_ClearPoint(u8 x,u8 y);
void OLED_ColorTurn(u8 i);
void OLED_DisplayTurn(u8 i);
void I2C_Start(void);
void I2C_Stop(void);
void I2C_WaitAck(void);
void Send_Byte(u8 dat);
void OLED_WR_Byte(u8 dat,u8 mode);
void OLED_DisPlay_On(void);
void OLED_DisPlay_Off(void);
void OLED_Refresh(void);
void OLED_Clear(void);
void OLED_DrawPoint(u8 x,u8 y,u8 t);
void OLED_DrawLine(u8 x1,u8 y1,u8 x2,u8 y2,u8 mode);
void OLED_DrawCircle(u8 x,u8 y,u8 r);
void OLED_ShowChar(u8 x,u8 y,u8 chr,u8 size1,u8 mode);
void OLED_ShowChar6x8(u8 x,u8 y,u8 chr,u8 mode);
void OLED_ShowString(u8 x,u8 y,u8 *chr,u8 size1,u8 mode);
void OLED_ShowNum(u8 x,u8 y,u32 num,u8 len,u8 size1,u8 mode);
void OLED_ShowChinese(u8 x,u8 y,u8 num,u8 size1,u8 mode);
void OLED_ScrollDisplay(u8 num,u8 space,u8 mode);
void OLED_ShowPicture(u8 x,u8 y,u8 sizex,u8 sizey,u8 BMP[],u8 mode);
void OLED_Init(void);

#endif

