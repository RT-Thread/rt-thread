/*
 * Copyright (c) 2006-2024 RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author        Notes
 * 2024-08-16     zhujiale     first version
 */
#include "sdhci.h"
#include <rtthread.h>


int dma_set_mask_and_coherent(struct rt_device *dev, rt_uint64_t mask)
{
    return 0;
}

unsigned long virt_to_phys(volatile void *address)
{
    return (unsigned long)((rt_uint64_t)address + PV_OFFSET);
}
void *dma_alloc_coherent(struct rt_device *dev, size_t size,
                         rt_uint64_t *dma_handle)
{
    void *v;

    v = rt_malloc_align(size, 2048);
    rt_kprintf("v = %p \n", v);
    if (v)
    {
        *dma_handle = virt_to_phys(v);
        v           = rt_ioremap((void *)*dma_handle, size);
        rt_kprintf("v = %p *dma_handle = %p \n", v, *dma_handle);
    }

    return v;
}

void dma_free_coherent(struct rt_device *dev, size_t size,
                       void *cpu_addr, unsigned long dma_handle)
{
    rt_free(cpu_addr);
}
