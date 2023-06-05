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

#define RT_HW_PAGE_START    RT_ALIGN((unsigned long)&__bss_end, 0x1000)
#define RT_HW_PAGE_END      (RT_HW_PAGE_START + 0x100000)

#define RT_HW_HEAP_BEGIN    (void *)(RT_HW_PAGE_END)
#define RT_HW_HEAP_END      (void *)(RT_HW_HEAP_BEGIN + 64 * 1024 * 1024)

void rt_hw_board_init(void);

#endif /* __BOARD_H__ */
