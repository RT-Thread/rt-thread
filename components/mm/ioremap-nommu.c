/*
 * Copyright (c) 2006-2026, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#include <rtthread.h>

#include <ioremap.h>
#include <mm_aspace.h>

void *rt_ioremap_start;
size_t rt_ioremap_size;

const rt_ubase_t rt_kmem_pvoff(void)
{
    return 0;
}

void rt_kmem_pvoff_set(rt_ubase_t pvoff)
{
    RT_UNUSED(pvoff);
}

void *rt_kmem_v2p(void *vaddr)
{
    return vaddr;
}

void *rt_kmem_p2v(void *paddr)
{
    return paddr;
}

void *rt_ioremap_early(void *paddr, size_t size)
{
    return size ? paddr : RT_NULL;
}

void *rt_ioremap(void *paddr, size_t size)
{
    return rt_ioremap_early(paddr, size);
}

void *rt_ioremap_nocache(void *paddr, size_t size)
{
    return rt_ioremap_early(paddr, size);
}

void *rt_ioremap_cached(void *paddr, size_t size)
{
    return rt_ioremap_early(paddr, size);
}

void *rt_ioremap_wt(void *paddr, size_t size)
{
    return rt_ioremap_early(paddr, size);
}

void rt_iounmap(volatile void *addr)
{
    RT_UNUSED(addr);
}
