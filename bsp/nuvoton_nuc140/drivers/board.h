/*
 * File      : board.h
 * This file is part of RT-Thread RTOS
 * COPYRIGHT (C) 2014, RT-Thread Development Team
 *
 * The license and distribution terms for this file may be
 * found in the file LICENSE in this distribution or at
 * http://www.rt-thread.org/license/LICENSE
 *
 * Change Logs:
 * Date           Author       Notes
 * 2014-11-23     Bright      add board.h to this bsp
 */

// <<< Use Configuration Wizard in Context Menu >>>
#ifndef __BOARD_H__
#define __BOARD_H__

#include "NUC100Series.h"

#define BOARD_PLL_CLOCK           50000000

/* board configuration */

#ifdef __CC_ARM
extern int Image$$RW_IRAM1$$ZI$$Limit;
extern int Image$$RW_IRAM1$$Base;
#define BOARD_SRAM_BEGIN    (&Image$$RW_IRAM1$$ZI$$Limit)
#elif __ICCARM__
#pragma section="HEAP"
#define BOARD_SRAM_BEGIN    (__segment_end("HEAP"))
#else
extern int __bss_end;
#define BOARD_SRAM_BEGIN    (&__bss_end)
#endif

#define BOARD_SRAM_SIZE         16
#define BOARD_SRAM_END          ((char*)(&Image$$RW_IRAM1$$Base) + (BOARD_SRAM_SIZE * 1024))

void rt_hw_board_init(void);

//#define PRINT_RCC_FREQ_INFO

#endif

// <<< Use Configuration Wizard in Context Menu >>>


