/*
 * Copyright (c) 2006-2021, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2022-11-09     RT-Thread    The first version
 */
#ifndef __CACHE_H__
#define __CACHE_H__

#ifndef ALWAYS_INLINE
#define ALWAYS_INLINE inline __attribute__((always_inline))
#endif

/**
 * @brief These APIs may not be supported by a specified architecture
 * But we have to include to all the cases to be 'general purpose'
 */

ALWAYS_INLINE void rt_hw_cpu_dcache_clean_local(void *addr, int size) {}
ALWAYS_INLINE void rt_hw_cpu_dcache_invalidate_local(void *addr, int size) {}
ALWAYS_INLINE void rt_hw_cpu_dcache_clean_and_invalidate_local(void *addr, int size) {}

ALWAYS_INLINE void rt_hw_cpu_dcache_clean_all_local() {}
ALWAYS_INLINE void rt_hw_cpu_dcache_invalidate_all_local(void) {}
ALWAYS_INLINE void rt_hw_cpu_dcache_clean_and_invalidate_all_local(void) {}

ALWAYS_INLINE void rt_hw_cpu_icache_invalidate_local(void *addr, int size) {}
ALWAYS_INLINE void rt_hw_cpu_icache_invalidate_all_local() {}

/**
 * @brief Multi-core
 */

#define rt_hw_cpu_dcache_clean rt_hw_cpu_dcache_clean_local
#define rt_hw_cpu_dcache_invalidate rt_hw_cpu_dcache_invalidate_local
#define rt_hw_cpu_dcache_clean_and_invalidate rt_hw_cpu_dcache_clean_and_invalidate_local

#define rt_hw_cpu_dcache_clean_all rt_hw_cpu_dcache_clean_all_local
#define rt_hw_cpu_dcache_invalidate_all rt_hw_cpu_dcache_invalidate_all_local
#define rt_hw_cpu_dcache_clean_and_invalidate_all rt_hw_cpu_dcache_clean_and_invalidate_all_local

#define rt_hw_cpu_icache_invalidate rt_hw_cpu_icache_invalidate_local
#define rt_hw_cpu_icache_invalidate_all rt_hw_cpu_icache_invalidate_all_local

#define rt_hw_icache_invalidate_all rt_hw_cpu_icache_invalidate_all

/** instruction barrier */
static inline void rt_hw_cpu_sync(void) {}

/**
 * @brief local cpu icahce & dcache synchronization
 *
 * @param addr
 * @param size
 */
void rt_hw_sync_cache_local(void *addr, int size);

#endif /* __CACHE_H__ */
