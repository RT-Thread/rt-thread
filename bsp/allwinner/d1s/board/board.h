/*
 * Copyright (c) 2006-2022, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2021-01-30     lizhirui     first version
 */

#ifndef BOARD_H__
#define BOARD_H__

#include <rtthread.h>
#include <rtconfig.h>

extern unsigned int __bss_start;
extern unsigned int __bss_end;

#define RAM_SIZE            (64 * 1024 * 1024)
#define RAM_BASE            (0x40000000)
#define RAM_END_VADDR       (KERNEL_VADDR_START + RAM_SIZE)

#define RT_HW_HEAP_BEGIN    ((void *)&__bss_end)
#define RT_HW_HEAP_END      ((void *)(((rt_size_t)RT_HW_HEAP_BEGIN) + 16 * 1024 * 1024))
#define RT_HW_PAGE_START    (RT_HW_HEAP_END)
#define RT_HW_PAGE_END      ((void *)RAM_END_VADDR)

void rt_hw_board_init(void);
void rt_init_user_mem(struct rt_thread *thread, const char *name, unsigned long *entry);

#endif
