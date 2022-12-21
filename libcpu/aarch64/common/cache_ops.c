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
void __asm_flush_dcache_range(unsigned long start, unsigned long end);
void __asm_invalidate_dcache_range(unsigned long start, unsigned long end);
void __asm_invalidate_icache_range(unsigned long start, unsigned long end);
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

void rt_hw_cpu_icache_invalidate(void *addr, int size)
{
    __asm_invalidate_icache_range((unsigned long)addr, (unsigned long)addr + size);
}

void rt_hw_cpu_dcache_invalidate(void *addr, int size)
{
    __asm_invalidate_dcache_range((unsigned long)addr, (unsigned long)addr + size);
}

void rt_hw_cpu_dcache_clean(void *addr, int size)
{
    __asm_flush_dcache_range((unsigned long)addr, (unsigned long)addr + size);
}

void rt_hw_cpu_dcache_clean_and_invalidate(void *addr, int size)
{
    __asm_flush_dcache_range((unsigned long)addr, (unsigned long)addr + size);
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

#ifdef RT_USING_LWP
#define ICACHE (1<<0)
#define DCACHE (1<<1)
#define BCACHE (ICACHE|DCACHE)

int sys_cacheflush(void *addr, int size, int cache)
{
    if ((size_t)addr < KERNEL_VADDR_START && (size_t)addr + size <= KERNEL_VADDR_START)
    {
        if ((cache & DCACHE) != 0)
        {
            rt_hw_cpu_dcache_clean_and_invalidate(addr, size);
        }
        if ((cache & ICACHE) != 0)
        {
            rt_hw_cpu_icache_invalidate(addr, size);
        }
        return 0;
    }
    return -1;
}
#endif
