/*
 * Copyright (c) 2006-2024, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2025/01/16     zdtyuiop4444 fix type cast warning
 * 2024/11/26     zdtyuiop4444 The first version
 */

#include "cache.h"

inline void rt_hw_cpu_dcache_enable(void)
{
    asm volatile("csrs mhcr, %0;" ::"rI"(0x2));
}

inline void rt_hw_cpu_dcache_disable(void)
{
    asm volatile("csrc mhcr, %0;" ::"rI"(0x2));
}

inline void inv_dcache_range(uintptr_t start, size_t size) {
    CACHE_OP_RANGE(DCACHE_IPA_A0, start, size);
}

inline void flush_dcache_range(uintptr_t start, size_t size) {
    CACHE_OP_RANGE(DCACHE_CIPA_A0, start, size);
}

inline void rt_hw_cpu_dcache_ops(int ops, void* addr, int size)
{
    switch (ops)
    {
    case RT_HW_CACHE_FLUSH:
        flush_dcache_range((uintptr_t)addr, size);
        break;
    case RT_HW_CACHE_INVALIDATE:
        inv_dcache_range((uintptr_t)addr, size);
        break;
    default:
        break;
    }
}

inline void rt_hw_cpu_icache_enable(void)
{
    asm volatile("csrs mhcr, %0;" ::"rI"(0x1));
}

inline void rt_hw_cpu_icache_disable(void)
{
    asm volatile("csrc mhcr, %0;" ::"rI"(0x1));
}

inline void inv_icache_range(uintptr_t start, size_t size) {
    CACHE_OP_RANGE(ICACHE_IPA_A0, start, size);
}

inline void rt_hw_cpu_icache_ops(int ops, void* addr, int size)
{
    switch (ops)
    {
    case RT_HW_CACHE_INVALIDATE:
        inv_icache_range((uintptr_t)addr, size);
        break;
    default:
        break;
    }
}
