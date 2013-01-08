/*
 * File      : cache.c
 * This file is part of RT-Thread RTOS
 * COPYRIGHT (C) 2010, RT-Thread Development Team
 *
 * The license and distribution terms for this file may be
 * found in the file LICENSE in this distribution or at
 * http://www.rt-thread.org/license/LICENSE
 *
 * Change Logs:
 * Date           Author       Notes
 * 2010-05-17     swkyer       first version
 */
#include <rtthread.h>
#include "mipscfg.h"
#include "cache.h"


extern void cache_init(rt_ubase_t cache_size, rt_ubase_t cache_line_size);
void r4k_cache_init(void)
{
	cache_init(dcache_size, cpu_dcache_line_size());
}

void r4k_cache_flush_all(void)
{
    blast_dcache16();
    blast_icache16();
}

void r4k_icache_flush_all(void)
{
    blast_icache16();
}

void r4k_icache_flush_range(rt_ubase_t addr, rt_ubase_t size)
{
	rt_ubase_t end, a;

    if (size > icache_size)
    {
        blast_icache16();
    }
    else
    {
    	rt_ubase_t ic_lsize = cpu_icache_line_size();

        a = addr & ~(ic_lsize - 1);
        end = ((addr + size) - 1) & ~(ic_lsize - 1);
        while (1)
        {
            flush_icache_line(a);
            if (a == end)
                break;
            a += ic_lsize;
        }
    }
}

void r4k_icache_lock_range(rt_ubase_t addr, rt_ubase_t size)
{
	rt_ubase_t end, a;
	rt_ubase_t ic_lsize = cpu_icache_line_size();

    a = addr & ~(ic_lsize - 1);
    end = ((addr + size) - 1) & ~(ic_lsize - 1);
    while (1)
    {
        lock_icache_line(a);
        if (a == end)
            break;
        a += ic_lsize;
    }
}

void r4k_dcache_inv(rt_ubase_t addr, rt_ubase_t size)
{
	rt_ubase_t end, a;
    rt_ubase_t dc_lsize = cpu_dcache_line_size();

    a = addr & ~(dc_lsize - 1);
    end = ((addr + size) - 1) & ~(dc_lsize - 1);
    while (1)
    {
        invalidate_dcache_line(a);
        if (a == end)
            break;
        a += dc_lsize;
    }
}

void r4k_dcache_wback_inv(rt_ubase_t addr, rt_ubase_t size)
{
	rt_ubase_t end, a;

    if (size >= dcache_size)
    {
        blast_dcache16();
    }
    else
    {
    	rt_ubase_t dc_lsize = cpu_dcache_line_size();

        a = addr & ~(dc_lsize - 1);
        end = ((addr + size) - 1) & ~(dc_lsize - 1);
        while (1)
        {
            flush_dcache_line(a);
            if (a == end)
                break;
            a += dc_lsize;
        }
    }
}
