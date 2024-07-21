/*
 * Copyright (c) 2006-2021, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Email: opensource_embedded@phytium.com.cn
 *
 * Change Logs:
 * Date        Author       Notes
 * 2022-10-26  huanghe      first commit
 * 2022-04-13  zhugengyu    support RT-Smart
 * 2023-07-27  liqiaozhong  add gpio pin definition
 *
 */

#ifndef __BOARD_H__
#define __BOARD_H__

#include "fparameters.h"
#include "phytium_cpu.h"

#include "mmu.h"
#ifdef RT_USING_SMART
    #include "ioremap.h"
#endif

#if defined(__CC_ARM)
    extern int Image$$RW_IRAM1$$ZI$$Limit;
    #define HEAP_BEGIN ((void *)&Image$$RW_IRAM1$$ZI$$Limit)
#elif defined(__GNUC__)
    extern int __bss_end;
    #define HEAP_BEGIN ((void *)&__bss_end)
#endif

#ifdef RT_USING_SMART
    #define HEAP_END        (rt_size_t)((rt_size_t)KERNEL_VADDR_START + 64 * 1024 * 1024)
    #define PAGE_START      HEAP_END + 1 * 1024 * 1024
    #define PAGE_END        (rt_size_t)((rt_size_t)KERNEL_VADDR_START + 128 * 1024 * 1024)
#else
    #define HEAP_END        (rt_size_t)(HEAP_BEGIN + 64*1024*1024)
    #define PAGE_POOL_SIZE  (8ul << 20)
    #define PAGE_START      (rt_size_t)(HEAP_END)
    #define PAGE_END        (PAGE_START +PAGE_POOL_SIZE)
#endif

void rt_hw_board_init(void);

#endif
