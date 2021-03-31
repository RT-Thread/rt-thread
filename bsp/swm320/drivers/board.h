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

#ifndef __BOARD_H__
#define __BOARD_H__

#include <rtthread.h>
#include <rthw.h>
#include <rtdevice.h>
#include <string.h>
#include <SWM320.h>

#ifdef __cplusplus
extern "C"
{
#endif

#define SRAM_BASE 0x20000000
#define SRAM_SIZE 0x20000
#define SRAM_END (SRAM_BASE + SRAM_SIZE)

#ifdef BSP_USING_EXT_SRAM
#define EXT_SRAM_BASE SRAMM_BASE
#define EXT_SRAM_SIZE BSP_EXT_SRAM_SIZE
#define EXT_SRAM_BEGIN EXT_SRAM_BASE
#define EXT_SRAM_END (EXT_SRAM_BASE + EXT_SRAM_SIZE)
#endif

#if defined(__CC_ARM) || defined(__CLANG_ARM)
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

    void rt_hw_board_init(void);

#ifdef __cplusplus
}
#endif

#endif /* __BOARD_H__ */
