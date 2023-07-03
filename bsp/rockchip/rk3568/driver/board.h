/*
 * Copyright (c) 2006-2022, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2017-5-30      Bernard      the first version
 */

#ifndef __BOARD_H__
#define __BOARD_H__

#include <rk3568.h>

extern unsigned char __bss_start;
extern unsigned char __bss_end;

#ifdef RT_USING_SMART
#define RT_HW_HEAP_BEGIN  (void *)RT_ALIGN((unsigned long)&__bss_end, 0x1000) + 0x8000
#define RT_HW_HEAP_END    (rt_size_t)(KERNEL_VADDR_START + 64 * 1024 * 1024)
#define RT_HW_PAGE_START  RT_HW_HEAP_END + 1 * 1024 * 1024
#define RT_HW_PAGE_END    ((rt_size_t)KERNEL_VADDR_START + 128 * 1024 * 1024)

#else
#define RT_HW_HEAP_BEGIN    (void *)RT_ALIGN((unsigned long)&__bss_end, 0x1000)
#define RT_HW_HEAP_END      (void *)(RT_HW_HEAP_BEGIN + 64 * 1024 * 1024)
#define RT_HW_PAGE_START    (rt_size_t)RT_HW_HEAP_END
#define RT_HW_PAGE_END      (rt_size_t)(RT_HW_PAGE_START + 64 * 1024 * 1024)
#endif /*RT_USING_SMART*/


void rt_hw_board_init(void);

#endif /* __BOARD_H__ */
