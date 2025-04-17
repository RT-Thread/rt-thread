/*
 * Copyright (c) 2006-2021, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2021-01-30     lizhirui     first version
 */

#ifndef BOARD_H__
#define BOARD_H__

#include <rtconfig.h>

extern unsigned int __sram_size;
extern unsigned int __sram_base;
extern unsigned int __sram_end;
#define RAM_END     (rt_size_t)((void *)&__sram_end)

extern unsigned int __bss_start;
extern unsigned int __bss_end;

#define RT_HW_HEAP_BEGIN    ((void *)&__bss_end)
#define RT_HW_HEAP_END      ((void *)(((rt_size_t)RT_HW_HEAP_BEGIN) + 8 * 1024 * 1024))

#define RT_HW_PAGE_START    ((void *)((rt_size_t)RT_HW_HEAP_END + sizeof(rt_size_t)))
#define RT_HW_PAGE_END      ((void *)(RAM_END))

void rt_hw_board_init(void);
void rt_init_user_mem(struct rt_thread *thread, const char *name, unsigned long *entry);

#endif
