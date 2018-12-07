/*
 * File      : board.h
 * This file is part of RT-Thread RTOS
 * COPYRIGHT (C) 2006 - 2018, RT-Thread Development Team
 *
 *  This program is free software; you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation; either version 2 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License along
 *  with this program; if not, write to the Free Software Foundation, Inc.,
 *  51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.
 *
 * Change Logs:
 * Date           Author       Notes
 * 2018-05-31     ZYH          first version
 */
#ifndef __BOARD_H__
#define __BOARD_H__
#include <rtthread.h>
#include <SWM320.h>
#define SRAM_BASE 0x20000000
#define SRAM_SIZE 0x20000

#ifdef BSP_USING_EXT_SRAM
#define EXT_SRAM_BASE SRAMM_BASE
#define EXT_SRAM_SIZE BSP_EXT_SRAM_SIZE
#define EXT_SRAM_BEGIN EXT_SRAM_BASE
#define EXT_SRAM_END (EXT_SRAM_BASE + EXT_SRAM_SIZE)
#endif

#define SRAM_END          (SRAM_BASE + SRAM_SIZE * 1024UL)
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
#define HEAP_END    SRAM_END
#define HEAP_SIZE   (HEAP_END - (rt_uint32_t)HEAP_BEGIN)
extern void rt_hw_board_init(void);
#endif
