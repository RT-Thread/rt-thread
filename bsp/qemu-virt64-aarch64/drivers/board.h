/*
 * File      : board.h
 * Copyright (c) 2006-2022, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2013-07-06     Bernard    the first version
 */

#ifndef __BOARD_H__
#define __BOARD_H__

#include <virt.h>

extern unsigned char __bss_start;
extern unsigned char __bss_end;

#define HEAP_BEGIN  (void *)&__bss_end

#ifdef RT_USING_SMART
#define HEAP_END    (rt_size_t)(KERNEL_VADDR_START + 64 * 1024 * 1024)
#define PAGE_START  HEAP_END + 1 * 1024 * 1024
#define PAGE_END    ((rt_size_t)KERNEL_VADDR_START + 128 * 1024 * 1024)
#else
#define HEAP_END    ((void *)HEAP_BEGIN + 64 * 1024 * 1024)
#define KERNEL_VADDR_START 0x40000000
#endif

void rt_hw_board_init(void);

int rt_hw_uart_init(void);

#endif
