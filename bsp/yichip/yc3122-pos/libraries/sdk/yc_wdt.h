/*
 * Copyright (c) 2006-2020, YICHIP Development Team
 * @file     yc_wdt.h
 * @brief    This file provides all the WDT firmware functions.
 *
 * Change Logs:
 * Date           Author             Version        Notes
 * 2021-01-04     yangzhengfeng      V1.0.0         the first version
 */

#ifndef __YC_WDT_H__
#define __YC_WDT_H__

#ifdef __cplusplus
extern "C" {
#endif

#include "yc3122.h"
#include "system.h"


typedef enum
{
    WDT_CPUReset = 0,
    WDT_Interrupt,
} WDT_ModeTypeDef;

#define  WDTCLKDIV_1                0x00
#define  WDTCLKDIV_2                0x01
#define  WDTCLKDIV_3                0x02
#define  WDTCLKDIV_4                0x03
#define  WDTCLKDIV_5                0x04
#define  WDTCLKDIV_6                0x05
#define  WDTCLKDIV_7                0x06
#define  WDTCLKDIV_8                0x07
#define  WDTCLKDIV_9                0x08
#define  WDTCLKDIV_10               0x09
#define  WDTCLKDIV_11               0x0A
#define  WDTCLKDIV_12               0x0B
#define  WDTCLKDIV_13               0x0c
#define  WDTCLKDIV_14               0x0D
#define  WDTCLKDIV_15               0x0E
#define  WDTCLKDIV_16               0x0F

/**************the value of feed dog************/
#define COUNTER_RELOAD_KEY          0x5937
#define ITSTATUS                    0x01
#define IS_WDT_CLKDI(wdtclkdiv)     (wdtclkdiv < 16)
#define IS_WDT_RELOAD(load)         (load <= 0x1f)
#define IS_WDT_MODE(mode)           ((mode == WDT_CPUReset) || (mode == WDT_Interrupt))

void WDT_CLKDIV(uint32_t Wdtclkdiv);
void WDT_SetReload(uint32_t Reload);
void WDT_ModeConfig(WDT_ModeTypeDef WDT_Mode);
void WDT_ClearITPendingBit(void);
void WDT_Enable(void);
void WDT_ReloadCounter(void);
uint8_t WDT_GetITStatus(void);

#ifdef __cplusplus
}
#endif

#endif /*__YC_WDT_H__*/

/************************ (C) COPYRIGHT Yichip Microelectronics *****END OF FILE****/
