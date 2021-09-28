/*
 * Copyright (c) 2006-2021, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2019-03-29     quanzhao     the first version
 * 2020-07-26     lizhirui     porting to ls2k
 */

#include <rthw.h>
#include <rtdef.h>

rt_inline rt_uint64_t rt_cpu_icache_line_size(void)
{
    rt_uint64_t ctr;
    return 4 << (ctr & 0xF);
}

rt_inline rt_uint64_t rt_cpu_dcache_line_size(void)
{
    rt_uint64_t ctr;
    return 4 << ((ctr >> 16) & 0xF);
}

void rt_hw_cpu_icache_invalidate(void *addr, int size)
{
    rt_uint64_t line_size = rt_cpu_icache_line_size();
    rt_uint64_t start_addr = (rt_uint64_t)addr;
    rt_uint64_t end_addr = (rt_uint64_t) addr + size + line_size - 1;
}

void rt_hw_cpu_dcache_invalidate(void *addr, int size)
{
    rt_uint64_t line_size = rt_cpu_dcache_line_size();
    rt_uint64_t start_addr = (rt_uint64_t)addr;
    rt_uint64_t end_addr = (rt_uint64_t) addr + size + line_size - 1;
}

void rt_hw_cpu_dcache_clean(void *addr, int size)
{
    rt_uint64_t line_size = rt_cpu_dcache_line_size();
    rt_uint64_t start_addr = (rt_uint64_t)addr;
    rt_uint64_t end_addr = (rt_uint64_t) addr + size + line_size - 1;
}

void rt_hw_cpu_icache_ops(int ops, void *addr, int size)
{
    if (ops == RT_HW_CACHE_INVALIDATE)
        rt_hw_cpu_icache_invalidate(addr, size);
}

void rt_hw_cpu_dcache_ops(int ops, void *addr, int size)
{
    if (ops == RT_HW_CACHE_FLUSH)
        rt_hw_cpu_dcache_clean(addr, size);
    else if (ops == RT_HW_CACHE_INVALIDATE)
        rt_hw_cpu_dcache_invalidate(addr, size);
}

rt_base_t rt_hw_cpu_icache_status(void)
{
    return 0;
}

rt_base_t rt_hw_cpu_dcache_status(void)
{
    return 0;
}
