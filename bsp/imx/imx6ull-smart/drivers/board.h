/*
 * Copyright (c) 2006-2021, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 */

#ifndef __BOARD_H__
#define __BOARD_H__

#include <rtconfig.h>
#include "imx6ull.h"

#include "mmu.h"

#if defined(__CC_ARM)
extern int Image$$RW_IRAM1$$ZI$$Limit;
#define HEAP_BEGIN      ((void*)&Image$$RW_IRAM1$$ZI$$Limit)
#elif defined(__GNUC__)
extern int __bss_end;
#define HEAP_BEGIN      ((void*)&__bss_end)
#endif

#ifdef RT_USING_SMART
#define HEAP_END        (void*)(KERNEL_VADDR_START + 16 * 1024 * 1024)
#define PAGE_START      HEAP_END
#define PAGE_END        (void*)(KERNEL_VADDR_START + 128 * 1024 * 1024)
#else
#define HEAP_END        (void*)(0x80000000 + 64 * 1024 * 1024)
#endif

/*
 * memory map for peripherals
 */
/*
 start addr  - end addr   , size
 0x0090_0000 - 0x0091_FFFF, 128KB, OCRAM
 0x0200_0000 - 0x020F_FFFF, 1MB,   AIPS-1
 0x0210_0000 - 0x021F_FFFF, 1MB,   AIPS-2
 0x0220_0000 - 0x022F_FFFF, 1MB,   AIPS-3
 */
void rt_hw_board_init(void);

#endif
