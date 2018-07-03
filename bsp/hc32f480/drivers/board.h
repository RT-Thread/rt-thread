/*
 * File      : board.h
 * This file is part of RT-Thread RTOS
 * COPYRIGHT (C) 2006 - 2017, RT-Thread Development Team
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
 * 2018-05-29     JasonJia     first implementation
 */

#ifndef __BOARD_H__
#define __BOARD_H__

#include <rtthread.h>

/* board configuration */

/* External sram*/
#ifdef RT_USING_EXT_SRAM
/* The end address of external sram. */
#define EXT_SRAM_END            (EXT_SRAM_BEGIN + EXT_SRAM_SIZE * 1024)
#endif

/* High speed sram. */
#ifdef __CC_ARM
extern int Image$$RW_IRAM1$$ZI$$Limit;
#define HEAP_BEGIN              (&Image$$RW_IRAM1$$ZI$$Limit)
#elif __ICCARM__
#pragma section="HEAP"
#define HEAP_BEGIN              (__segment_end("HEAP"))
#else
extern int __bss_end;
#define HEAP_BEGIN              (&__bss_end)
#endif

#ifdef __ICCARM__
// Use *.icf ram symbal, to avoid hardcode.
extern char __ICFEDIT_region_RAM_end__;
#define HEAP_END                (&__ICFEDIT_region_RAM_end__)
#else
#define HEAP_END                (SRAMHS_BEGIN + SRAMHS_SIZE * 1024)
#endif

/* System sram. */
#define SYS_HEAP_BEGIN          (SRAMSYS_BEGIN)
#define SYS_HEAP_END            (SYS_HEAP_BEGIN + SRAMSYS_SIZE * 1024)

void rt_hw_board_init(void);

#endif

// <<< Use Configuration Wizard in Context Menu >>>
