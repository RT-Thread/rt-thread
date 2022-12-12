/*
 * Copyright (c) 2006-2021, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2021-12-28     GuEe-GUI     the first version
 */

#include <rthw.h>
#include <rtdef.h>

void __asm_flush_dcache_all(void);
void __asm_invalidate_dcache_all(void);
void __asm_flush_dcache_range(unsigned long start, unsigned long end);
void __asm_invalidate_dcache_range(unsigned long start, unsigned long end);

void __asm_invalidate_icache_all(void);
void __asm_invalidate_icache_range(unsigned long start, unsigned long end);

void rt_hw_dcache_flush_all(void)
{
    __asm_flush_dcache_all();
}

void rt_hw_dcache_invalidate_all(void)
{
    __asm_invalidate_dcache_all();
}

void rt_hw_dcache_flush_range(unsigned long start_addr, unsigned long size)
{
    __asm_flush_dcache_range(start_addr, start_addr + size);
}

void rt_hw_dcache_invalidate_range(unsigned long start_addr,unsigned long size)
{
    __asm_invalidate_dcache_range(start_addr, start_addr + size);
}

void rt_hw_icache_invalidate_all()
{
    __asm_invalidate_icache_all();
}

void rt_hw_icache_invalidate_range(unsigned long start_addr, int size)
{
    __asm_invalidate_icache_range(start_addr, start_addr + size);
}

void rt_hw_cpu_icache_ops(int ops, void *addr, int size)
{
    if (ops == RT_HW_CACHE_INVALIDATE)
    {
        rt_hw_icache_invalidate_range((unsigned long)addr, size);
    }
}

void rt_hw_cpu_dcache_ops(int ops, void *addr, int size)
{
    if (ops == RT_HW_CACHE_FLUSH)
    {
        rt_hw_dcache_flush_range((unsigned long)addr, size);
    }
    else if (ops == RT_HW_CACHE_INVALIDATE)
    {
        rt_hw_dcache_invalidate_range((unsigned long)addr, size);
    }
}
