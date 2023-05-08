/*
 * Copyright (c) 2006-2018, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2019-03-29 	  quanzhao 	   the first version
 */
#include <rthw.h>
#include <rtdef.h>

void __asm_invalidate_icache_all(void);
void __asm_flush_dcache_all(void);
void __asm_flush_dcache_range(rt_size_t start, rt_size_t end);
void __asm_invalidate_dcache_range(rt_size_t start, rt_size_t end);
void __asm_invalidate_icache_range(rt_size_t start, rt_size_t end);
void __asm_invalidate_dcache_all(void);
void __asm_invalidate_icache_all(void);

rt_inline rt_uint32_t rt_cpu_icache_line_size(void)
{
    return 0;
}

rt_inline rt_uint32_t rt_cpu_dcache_line_size(void)
{
    return 0;
}

void rt_hw_cpu_icache_invalidate(void *addr, rt_size_t size)
{
    __asm_invalidate_icache_range((rt_size_t)addr, (rt_size_t)addr + size);
}

void rt_hw_cpu_dcache_invalidate(void *addr, rt_size_t size)
{
    __asm_invalidate_dcache_range((rt_size_t)addr, (rt_size_t)addr + size);
}

void rt_hw_cpu_dcache_clean(void *addr, rt_size_t size)
{
    __asm_flush_dcache_range((rt_size_t)addr, (rt_size_t)addr + size);
}

void rt_hw_cpu_dcache_clean_and_invalidate(void *addr, rt_size_t size)
{
    __asm_flush_dcache_range((rt_size_t)addr, (rt_size_t)addr + size);
}

void rt_hw_cpu_icache_ops(int ops, void *addr, int size)
{
    if (ops == RT_HW_CACHE_INVALIDATE)
    {
        rt_hw_cpu_icache_invalidate(addr, size);
    }
}

void rt_hw_cpu_dcache_ops(int ops, void *addr, int size)
{
    if (ops == RT_HW_CACHE_FLUSH)
    {
        rt_hw_cpu_dcache_clean(addr, size);
    }
    else if (ops == RT_HW_CACHE_INVALIDATE)
    {
        rt_hw_cpu_dcache_invalidate(addr, size);
    }
}

rt_base_t rt_hw_cpu_icache_status(void)
{
    return 0;
}

rt_base_t rt_hw_cpu_dcache_status(void)
{
    return 0;
}
