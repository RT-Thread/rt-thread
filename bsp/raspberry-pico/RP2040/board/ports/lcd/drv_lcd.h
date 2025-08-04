#ifndef __DRV_LCD_H
#define __DRV_LCD_H

#include <stdint.h>
#include <rtdevice.h>

#include "pico/stdlib.h"
#include "hardware/spi.h"
#include "hardware/i2c.h"
#include "hardware/pwm.h"
#include "hardware/dma.h"

#define LCD_HEIGHT 240
#define LCD_WIDTH 240

#define HORIZONTAL 0
#define VERTICAL   1

/**
 * data
 **/
#define UBYTE uint8_t
#define UWORD uint16_t
#define UDOUBLE uint32_t

/**
 * GPIOI config
 **/
#define LCD_RST_PIN 12
#define LCD_DC_PIN 8
#define LCD_BL_PIN 13

#define LCD_CS_PIN 9
#define LCD_CLK_PIN 10
#define LCD_MOSI_PIN 11

typedef struct
{
    UWORD WIDTH;UWORD HEIGHT;UBYTE SCAN_DIR;
} LCD_ATTRIBUTES;
extern LCD_ATTRIBUTES LCD;

/*------------------------------------------------------------------------------------------------------*/
void DEV_Digital_Write(UWORD Pin, UBYTE Value);
UBYTE DEV_Digital_Read(UWORD Pin);

void DEV_GPIO_Mode(UWORD Pin, UWORD Mode);
void DEV_KEY_Config(UWORD Pin);
void DEV_Digital_Write(UWORD Pin, UBYTE Value);
UBYTE DEV_Digital_Read(UWORD Pin);

void DEV_SPI_WriteByte(UBYTE Value);
void DEV_SPI_Write_nByte(UBYTE *pData, UDOUBLE Len);

void DEV_SET_PWM(UBYTE Value);

UBYTE SPI_Init(void);
UBYTE DEV_Module_Init(void);
void DEV_Module_Exit(void);

/********************************************************************************
 function:
 Macro definition variable name
 ********************************************************************************/
bool initDMA(bool ctrl_cs);
void LCD_Init(UBYTE Scan_dir);
void LCD_Clear(UWORD Color);
void LCD_Display(UWORD *Image);
void LCD_SetWindows(UWORD Xstart, UWORD Ystart, UWORD Xend, UWORD Yend);
void LCD_DisplayWindows(UWORD Xstart, UWORD Ystart, UWORD Xend, UWORD Yend, UWORD *Image);
void pushPixelsDMA(UWORD* image, UDOUBLE len);
void LCD_DisplayPoint(UWORD X, UWORD Y, UWORD Color);
void Handler_LCD(int signo);

#endif
