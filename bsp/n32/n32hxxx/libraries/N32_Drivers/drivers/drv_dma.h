/*
 * Copyright (c) 2006-2025, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author           Notes
 * 2026-01-24     ox-horse         first version
 */

#ifndef __DRV_DMA_H_
#define __DRV_DMA_H_

#include <rtthread.h>
#include <board.h>

#ifdef __cplusplus
extern "C" {
#endif

#define DMA_BLOCK_SIZE   (4095)

struct dma_config
{
    DMA_Module *Instance;
    IRQn_Type dma_irq;
    DMA_ChHwHsIfType HsInterface;
    rt_uint32_t dma_rcc;
    DMA_ChNumType dma_channel;
    rt_uint32_t dmamux_channel;
    rt_uint32_t dmamux_request;
};

#ifdef __cplusplus
}
#endif

#endif /*__DRV_DMA_H_ */

