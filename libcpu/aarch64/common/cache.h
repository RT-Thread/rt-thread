/*
 * Copyright (c) 2006-2022, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2022-12-18     RT-Thread    the first version
 */

#ifndef __CACHE_H__
#define __CACHE_H__

#include <rtdef.h>

void __asm_invalidate_icache_all(void);

void rt_hw_dcache_flush_all(void);
void rt_hw_dcache_invalidate_all(void);
void rt_hw_dcache_flush_range(unsigned long start_addr, unsigned long size);
void rt_hw_cpu_dcache_clean(void *addr, unsigned long size);
void rt_hw_cpu_dcache_invalidate(void *start_addr, unsigned long size);

static inline void rt_hw_icache_invalidate_all(void)
{
    __asm_invalidate_icache_all();
}

void rt_hw_icache_invalidate_range(unsigned long start_addr, int size);
void rt_hw_cpu_icache_invalidate(void *addr, rt_size_t size);
void rt_hw_cpu_dcache_clean_and_invalidate(void *addr, rt_size_t size);

#endif /* __CACHE_H__ */
