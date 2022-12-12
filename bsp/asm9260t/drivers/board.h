/*
 * Copyright (c) 2006-2021, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2011-01-13     weety      add board.h to this bsp
 */

#ifndef __BOARD_H__
#define __BOARD_H__

#include <asm9260t.h>

#if defined(__CC_ARM)
extern int Image$$ER_ZI$$ZI$$Limit;
#define HEAP_BEGIN (&Image$$ER_ZI$$ZI$$Limit)
#elif(defined(__GNUC__))
extern unsigned char __bss_end__;
#define HEAP_BEGIN (&__bss_end__)
#elif(defined(__ICCARM__))
#pragma section = ".noinit"
#define HEAP_BEGIN (__section_end(".noinit"))
#endif

#define HEAP_END (0x22000000)


extern void rt_hw_board_init(void);

#endif
