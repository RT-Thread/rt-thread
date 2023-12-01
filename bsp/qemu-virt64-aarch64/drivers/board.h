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
#define HEAP_END    ((void *)HEAP_BEGIN + 64 * 1024 * 1024)

void rt_hw_board_init(void);

int rt_hw_uart_init(void);

#endif
