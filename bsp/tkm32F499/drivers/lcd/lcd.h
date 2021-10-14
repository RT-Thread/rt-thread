/*
 * Copyright (c) 2006-2021, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2021-10-14    spaceman   first version
 */

#include <board.h>

// #define XSIZE_PHYS 800
// #define YSIZE_PHYS 480
// extern __align(256) rt_uint32_t LTDC_Buf[XSIZE_PHYS*YSIZE_PHYS];
#define LCD_SPI_CS(a)   \
                        if (a)  \
                        GPIOB->BSRR = GPIO_Pin_11;  \
                        else        \
                        GPIOB->BRR  = GPIO_Pin_11;
#define SPI_DCLK(a) \
                        if (a)  \
                        GPIOB->BSRR = GPIO_Pin_9;   \
                        else        \
                        GPIOB->BRR  = GPIO_Pin_9;
#define SPI_SDA(a)  \
                        if (a)  \
                        GPIOB->BSRR = GPIO_Pin_0;   \
                        else        \
                        GPIOB->BRR  = GPIO_Pin_0;

#define LCD_RST(a)  \
                        if (a)  \
                        GPIOD->BSRR = GPIO_Pin_6;   \
                        else        \
                        GPIOD->BRR  = GPIO_Pin_6;
#define Set_Rst         GPIOD->BSRR = GPIO_Pin_6
#define Clr_Rst         GPIOD->BRR  = GPIO_Pin_6
#define Lcd_Light_ON    GPIOD->BSRR = GPIO_Pin_8  //PD8为高电平 背光打开
#define Lcd_Light_OFF   GPIOD->BRR  = GPIO_Pin_8  //PD8为低电平 背光关闭

//*************  24位色（1600万色）定义 *************//
#define White          0xFFFFFF
#define Black          0x000000
#define Blue           0xFF0000
#define Blue2          0xFF3F3F
#define Red            0x0000FF
#define Magenta        0xFF00FF
#define Green          0x00FF00
#define Cyan           0xFFFF00
#define Yellow         0x00FFFF

//*************  16位色定义 *************//
//#define White          0xFFFF
//#define Black          0x0000
//#define Blue           0x001F
//#define Blue2          0x051F
//#define Red            0xF800
//#define Magenta        0xF81F
//#define Green          0x07E0
//#define Cyan           0x7FFF
//#define Yellow         0xFFE0



void LCD_Initial(rt_uint32_t LTDC_Buf1, rt_uint32_t LTDC_Buf2); //LCD初始化函数
// volatile void LCD_delay(volatile int time);
// void WriteComm(unsigned char CMD);
// void WriteData(rt_uint32_t dat);
// void LCD_WR_REG(rt_uint16_t Index,rt_uint16_t CongfigTemp);
// void Lcd_ColorBox(rt_uint16_t xStart,rt_uint16_t yStart,rt_uint16_t xLong,rt_uint16_t yLong,rt_uint32_t Color);
//void SPILCD_DrawLine(unsigned short x1,unsigned short y1,unsigned short x2,unsigned short y2,unsigned short color);
//void SPILCD_ShowChar(unsigned short x,unsigned short y,unsigned char num, unsigned int fColor, unsigned int bColor,unsigned char flag) ;
// void LCD_PutString(unsigned short x, unsigned short y, char *s, unsigned int fColor, unsigned int bColor,unsigned char flag);
// void LCD_Fill_Pic(rt_uint16_t x, rt_uint16_t y,rt_uint16_t pic_H, rt_uint16_t pic_V, rt_uint32_t* pic);
