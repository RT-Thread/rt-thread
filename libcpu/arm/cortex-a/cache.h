/*
 * Copyright (c) 2006-2021, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2019-03-29     quanzhao     the first version
 */

#ifndef __CACHE_H__
#define __CACHE_H__

void rt_hw_cpu_icache_invalidate(void *addr, int size);
void rt_hw_cpu_dcache_clean_and_invalidate(void *addr, int size);

static inline void rt_hw_icache_invalidate_all(void)
{
    __asm__ volatile("mcr p15, 0, %0, c7, c5, 0"::"r"(0ul));
}

#endif /* __CACHE_H__ */
