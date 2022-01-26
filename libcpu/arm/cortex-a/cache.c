/*
 * Copyright (c) 2006-2021, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2019-03-29     quanzhao     the first version
 */
#include <rthw.h>
#include <rtdef.h>

rt_inline rt_uint32_t rt_cpu_icache_line_size(void)
{
    rt_uint32_t ctr;
    asm volatile ("mrc p15, 0, %0, c0, c0, 1" : "=r"(ctr));
    return 4 << (ctr & 0xF);
}

rt_inline rt_uint32_t rt_cpu_dcache_line_size(void)
{
    rt_uint32_t ctr;
    asm volatile ("mrc p15, 0, %0, c0, c0, 1" : "=r"(ctr));
    return 4 << ((ctr >> 16) & 0xF);
}

void rt_hw_cpu_icache_invalidate(void *addr, int size)
{
    rt_uint32_t line_size = rt_cpu_icache_line_size();
    rt_uint32_t start_addr = (rt_uint32_t)addr;
    rt_uint32_t end_addr = (rt_uint32_t) addr + size + line_size - 1;

    asm volatile ("dmb":::"memory");
    start_addr &= ~(line_size-1);
    end_addr &= ~(line_size-1);
    while (start_addr < end_addr)
    {
        asm volatile ("mcr p15, 0, %0, c7, c5, 1" :: "r"(start_addr));  /* icimvau */
        start_addr += line_size;
    }
    asm volatile ("dsb\n\tisb":::"memory");
}

void rt_hw_cpu_dcache_invalidate(void *addr, int size)
{
    rt_uint32_t line_size = rt_cpu_dcache_line_size();
    rt_uint32_t start_addr = (rt_uint32_t)addr;
    rt_uint32_t end_addr = (rt_uint32_t) addr + size + line_size - 1;

    asm volatile ("dmb":::"memory");
    start_addr &= ~(line_size-1);
    end_addr &= ~(line_size-1);
    while (start_addr < end_addr)
    {
        asm volatile ("mcr p15, 0, %0, c7, c6, 1" :: "r"(start_addr));  /* dcimvac */
        start_addr += line_size;
    }
    asm volatile ("dsb":::"memory");
}

void rt_hw_cpu_dcache_inv_range(void *addr, int size)
{
    rt_uint32_t line_size = rt_cpu_dcache_line_size();
    rt_uint32_t start_addr = (rt_uint32_t)addr;
    rt_uint32_t end_addr = (rt_uint32_t)addr + size;

    asm volatile ("dmb":::"memory");

    if ((start_addr & (line_size - 1)) != 0)
    {
        start_addr &= ~(line_size - 1);
        asm volatile ("mcr p15, 0, %0, c7, c14, 1" :: "r"(start_addr));
        start_addr += line_size;
        asm volatile ("dsb":::"memory");
    }

    if ((end_addr & (line_size - 1)) != 0)
    {
        end_addr &= ~(line_size - 1);
        asm volatile ("mcr p15, 0, %0, c7, c14, 1" :: "r"(end_addr));
        asm volatile ("dsb":::"memory");
    }

    while (start_addr < end_addr)
    {
        asm volatile ("mcr p15, 0, %0, c7, c6, 1" :: "r"(start_addr));  /* dcimvac */
        start_addr += line_size;
    }
    asm volatile ("dsb":::"memory");
}

void rt_hw_cpu_dcache_clean(void *addr, int size)
{
    rt_uint32_t line_size = rt_cpu_dcache_line_size();
    rt_uint32_t start_addr = (rt_uint32_t)addr;
    rt_uint32_t end_addr = (rt_uint32_t) addr + size + line_size - 1;

    asm volatile ("dmb":::"memory");
    start_addr &= ~(line_size-1);
    end_addr &= ~(line_size-1);
    while (start_addr < end_addr)
    {
        asm volatile ("mcr p15, 0, %0, c7, c10, 1" :: "r"(start_addr)); /* dccmvac */
        start_addr += line_size;
    }
    asm volatile ("dsb":::"memory");
}

void rt_hw_cpu_dcache_clean_inv(void *addr, int size)
{
    rt_uint32_t line_size = rt_cpu_dcache_line_size();
    rt_uint32_t start_addr = (rt_uint32_t)addr;
    rt_uint32_t end_addr = (rt_uint32_t) addr + size + line_size - 1;

    asm volatile ("dmb":::"memory");
    start_addr &= ~(line_size-1);
    end_addr &= ~(line_size-1);
    while (start_addr < end_addr)
    {
        asm volatile ("mcr p15, 0, %0, c7, c14, 1" :: "r"(start_addr));
        start_addr += line_size;
    }
    asm volatile ("dsb":::"memory");
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
