/*
 * Copyright (c) 2006-2026, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#include <rtthread.h>

#include <ioremap.h>

void *rt_ioremap_start;
size_t rt_ioremap_size;

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
