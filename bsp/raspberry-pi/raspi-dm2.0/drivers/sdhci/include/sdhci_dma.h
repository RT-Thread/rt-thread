/*
 * Copyright (c) 2006-2024 RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author        Notes
 * 2024-08-16     zhujiale     first version
 */
#ifndef __SDHCI_DMA_H__
#define __SDHCI_DMA_H__

#include "ioremap.h"
#include <mm_aspace.h>
enum dma_data_direction
{
    DMA_BIDIRECTIONAL = 0,
    DMA_TO_DEVICE     = 1,
    DMA_FROM_DEVICE   = 2,
    DMA_NONE          = 3,
};
#define DMA_BIT_MASK(n) (((n) == 64) ? ~0ULL : ((1ULL << (n)) - 1))

int           dma_set_mask_and_coherent(struct rt_device *dev, rt_uint64_t mask);
unsigned long virt_to_phys(volatile void *address);
void         *dma_alloc_coherent(struct rt_device *dev, size_t size,
                                 rt_uint64_t *dma_handle);
void          dma_free_coherent(struct rt_device *dev, size_t size,
                                void *cpu_addr, unsigned long dma_handle);

#endif
