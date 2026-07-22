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

#if defined(SOC_SERIES_N32H7xx)
#define DMA_BLOCK_SIZE (4095)

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
#elif defined(SOC_SERIES_N32H49x) || defined(SOC_SERIES_N32H47x_48x)
struct dma_config
{
    DMA_Module      *DMAy;
    DMA_ChannelType *DMAChx;
    IRQn_Type        dma_irq;
    rt_uint32_t      dma_rcc;
    rt_uint32_t      request;
    rt_uint32_t      channel;
};

#endif

#ifdef __cplusplus
}
#endif

#endif /*__DRV_DMA_H_ */

