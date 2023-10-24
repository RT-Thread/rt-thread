/*
 * Copyright (c) 2006-2023, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2023-9-25     tangzz98     the first version
 */

#include <rtthread.h>
#include <mprotect.h>

void mprotect_example_exception_hook(rt_mem_exception_info_t *info)
{
    rt_kprintf("Memory manage exception\n");
    rt_kprintf("Faulting thread: %s\n", info->thread->parent.name);
    rt_kprintf("Faulting address: %p\n", info->addr);
    rt_kprintf("Faulting region: %p - %p", info->region.start, (void *)((rt_size_t)info->region.start + info->region.size));
}
