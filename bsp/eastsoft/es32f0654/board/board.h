/*
 * File      : board.h
 * Copyright (C) 2018 Shanghai Eastsoft Microelectronics Co., Ltd.
 *
 * Change Logs:
 * Date           Author       Notes
 * 2019-01-23     wangyq       add board.h to this bsp
 */

// <<< Use Configuration Wizard in Context Menu >>>
#ifndef __BOARD_H__
#define __BOARD_H__

#include <es32f065x.h>

#if \
    defined(SOC_ES32F0653LQ)||\
    defined(SOC_ES32F0653NQ)||\
    defined(SOC_ES32F0654LQ)||\
    defined(SOC_ES32F0654NQ)
    #define ES32F0XX_PIN_NUMBERS 48
#elif \
    defined(SOC_ES32F0653LT)||\
    defined(SOC_ES32F0654LT)
    #define ES32F0XX_PIN_NUMBERS 64
#elif \
    defined(SOC_ES32F0653LX)||\
    defined(SOC_ES32F0654LX)
    #define ES32F0XX_PIN_NUMBERS 100
#endif

#if \
    defined(SOC_ES32F0653LQ)||\
    defined(SOC_ES32F0653LT)||\
    defined(SOC_ES32F0653LX)
    //#define ES32F065xxx
    #define ES32F0XX_SRAM_SIZE 16
#elif \
    defined(SOC_ES32F0654LQ)||\
    defined(SOC_ES32F0654NQ)||\
    defined(SOC_ES32F0654LT)||\
    defined(SOC_ES32F0654LX)
    //#define ES32F065xxx
    #define ES32F0XX_SRAM_SIZE 32
#endif

#ifdef __ICCARM__
    // Use *.icf ram symbal, to avoid hardcode.
    extern char __ICFEDIT_region_RAM_end__;

    #define ES32F0_SRAM_END          &__ICFEDIT_region_RAM_end__
#else
    #define ES32F0_SRAM_END          (0x20000000 + ES32F0XX_SRAM_SIZE * 1024)
#endif

#ifdef __CC_ARM
    extern int Image$$RW_IRAM1$$ZI$$Limit;
    #define HEAP_BEGIN  ((void *)&Image$$RW_IRAM1$$ZI$$Limit)
#elif __ICCARM__
    #pragma section="HEAP"
    #define HEAP_BEGIN  (__segment_end("HEAP"))
#else
    extern int __bss_end;
    #define HEAP_BEGIN  ((void *)&__bss_end)
#endif
#define HEAP_END    ES32F0_SRAM_END
// <o> Console on USART: <0=> no console <1=>USART 1 <2=>USART 2 <3=> USART 3
//  <i>Default: 1
#define ES32F0_CONSOLE_USART    2

void rt_hw_board_init(void);

#if ES32F0_CONSOLE_USART == 0
    #define CONSOLE_DEVICE "no"
#elif ES32F0_CONSOLE_USART == 1
    #define CONSOLE_DEVICE "uart1"
#elif ES32F0_CONSOLE_USART == 2
    #define CONSOLE_DEVICE "uart2"
#elif ES32F0_CONSOLE_USART == 3
    #define CONSOLE_DEVICE "uart3"
#endif

#define FINSH_DEVICE_NAME   CONSOLE_DEVICE

#endif

