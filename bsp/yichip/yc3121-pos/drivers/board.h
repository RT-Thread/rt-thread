/*
 * Copyright (c) 2006-2021, YICHIP Technology Co.,Ltd.
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2021-09-09     WSY          first version
 */

#ifndef BOARD_H__
#define BOARD_H__
#include <rtthread.h>
#include <yc3121.h>
#include "yc_gpio.h"
#include "yc_uart.h"
#include "yc_systick.h"
#include "misc.h"

#define SRAM_BASE 0x20000
#define SRAM_SIZE 0x10000

#ifdef BSP_USING_EXT_SRAM
    #define EXT_SRAM_BASE SRAMM_BASE
    #define EXT_SRAM_SIZE BSP_EXT_SRAM_SIZE
    #define EXT_SRAM_BEGIN EXT_SRAM_BASE
    #define EXT_SRAM_END (EXT_SRAM_BASE + EXT_SRAM_SIZE)
#endif

#define SRAM_END (SRAM_BASE + SRAM_SIZE)
#if defined(__ARMCC_VERSION)
    extern int Image$$RW_IRAM1$$ZI$$Limit;
    #define HEAP_BEGIN ((void *)&Image$$RW_IRAM1$$ZI$$Limit)
#elif __ICCARM__
    #pragma section = "HEAP"
    #define HEAP_BEGIN (__segment_end("HEAP"))
#else
    extern int __bss_end;
    #define HEAP_BEGIN ((void *)&__bss_end)
#endif
#define HEAP_END SRAM_END
#define HEAP_SIZE (HEAP_END - (rt_uint32_t)HEAP_BEGIN)
extern void rt_hw_board_init(void);
#endif
