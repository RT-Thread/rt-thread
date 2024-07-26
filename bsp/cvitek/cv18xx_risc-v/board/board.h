/*
 * Copyright (c) 2006-2023, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2023/06/25     flyingcys    first version
 */

#ifndef BOARD_H__
#define BOARD_H__

#include <rtconfig.h>
#include "drv_uart.h"
#include "tick.h"

extern unsigned int __bss_start;
extern unsigned int __bss_end;

#ifndef RT_USING_SMART
#define KERNEL_VADDR_START 0x80200000
#endif

#define RT_HW_HEAP_BEGIN ((void *)&__bss_end)
#define RT_HW_HEAP_END   ((void *)(KERNEL_VADDR_START + 16 * 1024 * 1024))
#define RT_HW_PAGE_START RT_HW_HEAP_END
#define RT_HW_PAGE_END   ((void *)(KERNEL_VADDR_START + 32 * 1024 * 1024))

void rt_hw_board_init(void);

#endif
