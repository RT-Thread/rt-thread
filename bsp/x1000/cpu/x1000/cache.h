/*
 * Copyright (c) 2006-2021, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2016-9-19      Urey         the first version
 */

#ifndef _X1000_CACHE_H_
#define _X1000_CACHE_H_

#include "../common/mips.h"
#include "../common/mips_cache.h"


void rt_hw_icache_invalidate_all(void);
void rt_hw_icache_flush_all(void);

void rt_hw_dcache_flush_all(void);
void rt_hw_dcache_flush_range(rt_uint32_t addr, rt_uint32_t size);
void rt_hw_dcache_invalidate_all(void);
void rt_hw_dcache_invalidate_range(rt_uint32_t addr,rt_uint32_t size);

void rt_hw_flush_cache_all(void);
#endif /* _X1000_CACHE_H_ */
