/*
 * Copyright (c) 2006-2021, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2016-09-07    Urey         the first version
 */

#include <rtthread.h>
#include "mips.h"

extern void cache_init(rt_ubase_t cache_size, rt_ubase_t cache_line_size);
void r4k_cache_init(void)
{
//  cache_init(dcache_size, cpu_dcache_line_size);
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

    if (size > g_mips_core.icache_size)
    {
        blast_icache16();
    }
    else
    {
        rt_ubase_t ic_lsize = g_mips_core.icache_line_size;

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
    rt_ubase_t ic_lsize = g_mips_core.icache_line_size;

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
    rt_ubase_t dc_lsize = g_mips_core.dcache_line_size;

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

    if (size >= g_mips_core.dcache_size)
    {
        blast_dcache16();
    }
    else
    {
        rt_ubase_t dc_lsize = g_mips_core.dcache_line_size;

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

#define dma_cache_wback_inv(start,size) \
    do { (void) (start); (void) (size); } while (0)
#define dma_cache_wback(start,size) \
    do { (void) (start); (void) (size); } while (0)
#define dma_cache_inv(start,size)   \
    do { (void) (start); (void) (size); } while (0)


void r4k_dma_cache_sync(rt_ubase_t addr, rt_size_t size, enum dma_data_direction direction)
{
    switch (direction)
    {
        case DMA_TO_DEVICE:
            r4k_dcache_wback_inv(addr, size);
        break;

        case DMA_FROM_DEVICE:
            r4k_dcache_wback_inv(addr, size);
        break;

        case DMA_BIDIRECTIONAL:
            dma_cache_wback_inv(addr, size);
        break;
        default:
            RT_ASSERT(0) ;
    }
}

