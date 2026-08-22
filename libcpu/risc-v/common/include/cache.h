/*
 * Copyright (c) 2006-2025 RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2025-04-20     GuEe-GUI     the first version
 */

#ifndef __CACHE_H__
#define __CACHE_H__

#define L1_CACHE_SHIFT  6
#define L1_CACHE_BYTES  (1 << L1_CACHE_SHIFT)

#ifndef __ASSEMBLY__
#include <rtdef.h>

void riscv_cache_set_cbom_block_size(rt_uint32_t size);
rt_uint32_t riscv_cache_get_cbom_block_size(void);

void rt_hw_cpu_icache_invalidate_all(void);
void rt_hw_cpu_icache_invalidate(void *addr, rt_size_t size);
void rt_hw_cpu_dcache_clean_and_invalidate(void *addr, rt_size_t size);

void rt_hw_icache_invalidate_all(void);

void rt_hw_sync_cache_local(void *addr, int size);
#endif /* !__ASSEMBLY__ */

#endif /* __CACHE_H__ */
