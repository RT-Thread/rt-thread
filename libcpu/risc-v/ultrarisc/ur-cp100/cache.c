/*
 * Copyright (c) 2006-2025 RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2021-01-29     lizhirui     first version
 * 2025-05-29     Zhang Jing   remove redundant code
 */

#include <rthw.h>
#include <rtdef.h>
#include <board.h>
#include <riscv.h>
#include <cache.h>

void rt_hw_cpu_icache_ops(int ops, void *addr, int size)
{
    if (ops == RT_HW_CACHE_INVALIDATE)
    {
        rt_hw_cpu_icache_invalidate(addr, size);
    }
    return;
}

void rt_hw_cpu_dcache_ops(int ops, void *addr, int size)
{
    if (ops == RT_HW_CACHE_FLUSH)
    {
        rt_hw_cpu_dcache_clean(addr, size);
    }
    else
    {
        rt_hw_cpu_dcache_invalidate(addr, size);
    }
    return;
}

void rt_hw_sync_cache_local(void *addr, int size)
{
    rt_hw_cpu_dcache_clean_local(addr, size);
    rt_hw_cpu_icache_invalidate_local(addr, size);
    return;
}