/*
 * Copyright (c) 2022 OpenLuat & AirM2M
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy of
 * this software and associated documentation files (the "Software"), to deal in
 * the Software without restriction, including without limitation the rights to
 * use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of
 * the Software, and to permit persons to whom the Software is furnished to do so,
 * subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS
 * FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR
 * COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER
 * IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN
 * CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 */


#ifndef __AIR105_LCDI_H
#define __AIR105_LCDI_H

#ifdef __cplusplus
extern "C"
{
#endif


#include "air105.h"


#define  LCDI_CMD                       (0)
#define  LCDI_DAT                       (1)

#define LCDI_MODE_6800                  (0)
#define LCDI_MODE_8080                  (1)

#define LCD_CMD_BUFF_SIZE               (64)
#define LCD_READ_BUFF_SIZE              (512)
#define LCD_WRITE_BUFF_SIZE             (512)

//LCD module
#define LCDI_FIFO_OV_IE                 (1 << 12)
#define LCDI_FIFO_RST                   (1 << 11)
#define LCDI_WR_DMA_EN                  (1 << 10)
#define LCDI_WR_FIFO_EN                 (1 << 9)

#define LCDI_CTRL_AUTO_READ             (1 << 8)
#define LCDI_CTRL_TYPE_8080             (1 << 7)
#define LCDI_CTRL_EN_RD                 (1 << 6)
#define LCDI_CTRL_RW_WR                 (1 << 5)
#define LCDI_CTRL_CD                    (1 << 4)
#define LCDI_CTRL_WIDTH_4BIT            (1 << 3)
#define LCDI_CTRL_AUTO                  (1 << 2)
#define LCDI_CTRL_RD_IE                 (1 << 1)
#define LCDI_CTRL_WR_IE                 (1 << 0)

#define LCDI_STATUS_READY               (1 << 2)
#define LCDI_STATUS_RD_IS               (1 << 1)
#define LCDI_STATUS_WR_IS               (1 << 0)

#define RNG_BUF_IS_FULL(pBuf)           ((pBuf)->u32Tail == (pBuf)->u32Head)
#define RNG_BUF_NEXT_HEAD(pBuf)         (((pBuf)->u32Head + 1) % ((pBuf)->u32BuffSize))
#define RNG_BUF_NEXT_TAIL(pBuf)         (((pBuf)->u32Tail + 1) % ((pBuf)->u32BuffSize))
#define RNG_BUF_LEN(pBuf)               (((pBuf)->u32Tail + (pBuf)->u32BuffSize - 1 - (pBuf)->u32Head) % (pBuf)->u32BuffSize)
#define RNG_BUF_PERI_TAIL(pBuf)         (((pBuf)->u32Tail + (pBuf)->u32BuffSize - 1) % ((pBuf)->u32BuffSize))

typedef struct
{
    uint32_t volatile u32Head;
    uint32_t volatile u32Tail;
    uint32_t volatile u32BuffSize;
    uint32_t volatile u32Stat;
    uint8_t volatile *pu8Buff;
} RNG_BUF8, *RNG_BUF8_ID;

typedef struct
{
    uint32_t volatile u32Head;
    uint32_t volatile u32Tail;
    uint32_t volatile u32BuffSize;
    uint32_t volatile u32Stat;
    uint32_t volatile *pu32Buff;
} RNG_BUF32, *RNG_BUF32_ID;

typedef struct
{
    uint8_t  lcd_ReadBuff[LCD_READ_BUFF_SIZE];
    uint8_t  lcd_WriteBuff[LCD_WRITE_BUFF_SIZE];
    uint32_t lcd_CmdBuff[LCD_CMD_BUFF_SIZE];
    RNG_BUF8 rbRead;
    RNG_BUF8 rbWrite;
    RNG_BUF32 rbCmd;
    RNG_BUF32_ID prbCmd;
    RNG_BUF8_ID prbRead;
    RNG_BUF8_ID prbWrite;
    volatile uint32_t u32OpCount;
} RING_BUF;

typedef struct
{
    uint8_t LCD_BusMode;        //Bus mode(8080/6800)
    uint8_t LCD_IntRead;        //Read interrupt Enable
    uint8_t LCD_IntWrite;       //Read interrupt Enable
    uint8_t fifo_level;
    uint32_t LCD_MaxQTR;        //Max qaurter cylce of read/write.
    uint32_t fifo_ov_ie_enable;
    uint32_t fifo_rst_enable;
    uint32_t wr_dma_enable;
    uint32_t wr_fifo_enable;
    uint32_t  opt;
    RING_BUF ring_buf;
} LCD_InitTypeDef;

//Operate the bus signal
void LCD_BusRead(LCD_TypeDef *LCDx,uint8_t u8CD);
void LCD_BusWrite(LCD_TypeDef *LCDx,uint8_t u8CD, uint8_t value);

void LCD_Read(LCD_TypeDef *LCDx,uint8_t u8CD, uint8_t *dat);
void LCD_Write(LCD_TypeDef *LCDx,uint8_t u8CD, uint8_t u8Value);

//Buffer mode only can used in interrupt mode.
int32_t LCD_ReadBuff(LCD_TypeDef *LCDx, LCD_InitTypeDef *pLcdInit, uint8_t *pu8Buff, uint32_t u32BuffLen);
int32_t LCD_WriteBuff(LCD_TypeDef *LCDx, LCD_InitTypeDef *pLcdInit, uint8_t *pu8Buff, uint32_t u32BuffLen);

void LCD_Init(LCD_TypeDef *LCDx, LCD_InitTypeDef *pLcdInit);
void LCD_FIFODMAconfig(LCD_TypeDef *LCDx, LCD_InitTypeDef *LCD_InitType);


#ifdef __cplusplus
}
#endif

#endif


/**************************      (C) COPYRIGHT Megahunt    *****END OF FILE****/
