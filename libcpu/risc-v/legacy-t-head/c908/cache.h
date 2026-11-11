/*
 * Copyright (c) 2006-2021, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2021-11-05     JasonHu      The first version
 * 2022-11-09     WangXiaoyao  Distinguish local and broadcast operations
 */

#ifndef CACHE_H__
#define CACHE_H__

#include "opcode.h"

#ifndef ALWAYS_INLINE
#define ALWAYS_INLINE inline __attribute__((always_inline))
#endif

ALWAYS_INLINE void rt_hw_cpu_sync(void)
{
    asm volatile(OPC_SYNC::
                     : "memory");
}

ALWAYS_INLINE void rt_hw_cpu_sync_i(void)
{
    asm volatile(OPC_SYNC_I::
                     : "memory");
}

ALWAYS_INLINE void rt_hw_cpu_sync_s(void)
{
    asm volatile(OPC_SYNC_S::
                     : "memory");
}

ALWAYS_INLINE void rt_hw_cpu_sync_is(void)
{
    asm volatile(OPC_SYNC_IS::
                     : "memory");
}

/**
 * ========================================
 * Local cpu cache maintainence operations
 * ========================================
 */

void rt_hw_cpu_dcache_clean_local(void *addr, int size);
void rt_hw_cpu_dcache_invalidate_local(void *addr, int size);
void rt_hw_cpu_dcache_clean_invalidate_local(void *addr, int size);

void rt_hw_cpu_icache_invalidate_local(void *addr, int size);

ALWAYS_INLINE void rt_hw_cpu_dcache_clean_all_local(void)
{
    __asm__ volatile(OPC_DCACHE_CALL ::
                         : "memory");
    rt_hw_cpu_sync();
}

ALWAYS_INLINE void rt_hw_cpu_dcache_invalidate_all_local(void)
{
    __asm__ volatile(OPC_DCACHE_IALL ::
                         : "memory");
    rt_hw_cpu_sync();
}

ALWAYS_INLINE void rt_hw_cpu_dcache_clean_invalidate_all_local(void)
{
    __asm__ volatile(OPC_DCACHE_CIALL ::
                         : "memory");
    rt_hw_cpu_sync();
}

ALWAYS_INLINE void rt_hw_cpu_icache_invalidate_all_local(void)
{
    __asm__ volatile(OPC_ICACHE_IALL ::
                         : "memory");
    rt_hw_cpu_sync_i();
}

#define rt_hw_icache_invalidate_all rt_hw_cpu_icache_invalidate_all

/**
 * ========================================
 * Multi-core cache maintainence operations
 * ========================================
 */

#define rt_hw_cpu_dcache_clean rt_hw_cpu_dcache_clean_local
#define rt_hw_cpu_dcache_invalidate rt_hw_cpu_dcache_invalidate_local
#define rt_hw_cpu_dcache_clean_and_invalidate rt_hw_cpu_dcache_clean_invalidate_local

#define rt_hw_cpu_dcache_clean_all rt_hw_cpu_dcache_clean_all_local
#define rt_hw_cpu_dcache_invalidate_all rt_hw_cpu_dcache_invalidate_all_local
#define rt_hw_cpu_dcache_clean_invalidate_all rt_hw_cpu_dcache_clean_invalidate_all_local

#define rt_hw_cpu_icache_invalidate rt_hw_cpu_icache_invalidate_local
#define rt_hw_cpu_icache_invalidate_all rt_hw_cpu_icache_invalidate_all_local

/**
 * @brief Synchronize cache to Point of Unification
 */
void rt_hw_sync_cache_local(void *addr, int size);

#endif /* CACHE_H__ */
