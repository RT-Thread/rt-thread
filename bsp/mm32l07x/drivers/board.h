/*
 * Copyright (c) 2006-2018, Synwit Technology Co.,Ltd.
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2018-05-31     ZYH          first version
 * 2018-12-10     Zohar_Lee    format file
 */

#ifndef BOARD_H__
#define BOARD_H__
#include <rtthread.h>
#include <hal_device.h>
//#define SRAM_BASE 0x20000000
#define SRAM_SIZE 0x2000



#define SRAM_END (SRAM_BASE + SRAM_SIZE)
#ifdef __CC_ARM
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
