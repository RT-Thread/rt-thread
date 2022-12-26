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

void rt_hw_dcache_flush_all(void);
void rt_hw_dcache_invalidate_all(void);
void rt_hw_dcache_flush_range(unsigned long start_addr, unsigned long size);
void rt_hw_cpu_dcache_clean(void *addr, int size);
void rt_hw_cpu_dcache_invalidate(unsigned long start_addr,unsigned long size);

void rt_hw_icache_invalidate_all();
void rt_hw_icache_invalidate_range(unsigned long start_addr, int size);

#endif /* __CACHE_H__ */
