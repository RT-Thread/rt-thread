#ifndef __LCD_H
#define __LCD_H

#include <rtthread.h>
#include <rtdevice.h>
#include <board.h>
#include "st7735.h"
#include <stdio.h>

#define WHITE            0xFFFF
#define BLACK            0x0000
#define BLUE             0x001F
#define BRED             0XF81F
#define GRED             0XFFE0
#define GBLUE            0X07FF
#define RED              0xF800
#define MAGENTA          0xF81F
#define GREEN            0x07E0
#define CYAN             0x7FFF
#define YELLOW           0xFFE0
#define BROWN            0XBC40 //棕色
#define BRRED            0XFC07 //棕红色
#define GRAY             0X8430 //灰色
#define DARKBLUE         0X01CF //深蓝色
#define LIGHTBLUE        0X7D7C //浅蓝色
#define GRAYBLUE         0X5458 //灰蓝色

// lcd spi
#define LCD_SPI_DEVICE_NAME     "spi40"
#define LCD_PWM_DEV_NAME        "pwm1"
#define LCD_PWM_DEV_CHANNEL     (2)
#define LCD_PWM_DEV_TIME        (10000)//pwm frequency:100K = 10000ns
#define MAX_BRIGHTNESS          LCD_PWM_DEV_TIME

#define WR_RS_PIN               GET_PIN(E, 13)
#define CS_PIN                  GET_PIN(E, 11)

//lcd display gpio
#define LCD_DISP_GPIO_NUM       GET_PIN(E, 10)

// lcd brush color
#define BRUSH_POINT_COLOR       WHITE
#define BRUSH_BACK_COLOR        BLACK

extern ST7735_Object_t st7735_pObj;
extern uint32_t st7735_id;

void LCD_SetBrightness(uint32_t Brightness);
uint32_t LCD_GetBrightness(void);
void LCD_ShowChar(uint16_t x,uint16_t y,uint8_t num,uint8_t size,uint8_t mode);
void LCD_ShowString(uint16_t x,uint16_t y,uint16_t width,uint16_t height,uint8_t size,uint8_t *p);
void LCD_FillRGBRect(uint32_t Xpos, uint32_t Ypos, uint8_t *pData, uint32_t Width, uint32_t Height);


#endif
