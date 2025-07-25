/*
 * Copyright (c) 2022-2025, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2025-01-22     chasel   first version
 */

#ifndef __BOARD_H__
#define __BOARD_H__
#include <rtthread.h>
#include <rtdevice.h>
#include <rthw.h>
#include "mm32_device.h"
#include <hal_common.h>
#include "mm32_msp.h"

#define SRAM_SIZE 0x1C000

#define SRAM_BASE     (0x30000000)

#define SRAM_END (SRAM_BASE + SRAM_SIZE)
#ifdef __CC_ARM
    extern int Image$$RW_IRAM1$$ZI$$Limit;
    #define HEAP_BEGIN ((void *)&Image$$RW_IRAM1$$ZI$$Limit)
#elif __ICCARM__
    #pragma section = "HEAP"
    #define HEAP_BEGIN (__segment_end("HEAP"))
#else
    extern int __bss_end__;
    #define HEAP_BEGIN ((void *)&__bss_end__)
#endif
#define HEAP_END SRAM_END
#define HEAP_SIZE (HEAP_END - (rt_uint32_t)HEAP_BEGIN)
extern void rt_hw_board_init(void);

#define CLOCK_SYS_FREQ         120000000u
#define CLOCK_SYSTICK_FREQ     (CLOCK_SYS_FREQ/8u)

#endif
