/*
 * Copyright (c) 2006-2021, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2021-04-24      Juice      the first version
 */

#ifndef __BOARD_H__
#define __BOARD_H__

#include <stdint.h>

extern unsigned int __bss_start;
extern unsigned int __bss_end;

#define RT_HW_HEAP_BEGIN    (void*)&__bss_end
#define RT_HW_HEAP_END      (void*)(0x80000000 + 300 * 1024 * 1024)

void rt_hw_board_init(void);

#endif
