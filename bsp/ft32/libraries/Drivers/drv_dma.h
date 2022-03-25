/*
 * Copyright (c) 2006-2022, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2022-03-02     FMD-AE       first version
 */

#ifndef __DRV_DMA_H_
#define __DRV_DMA_H_

#include <rtthread.h>
#include <board.h>

#ifdef __cplusplus
extern "C" {
#endif

#if defined(SOC_SERIES_FT32F0)
#define DMA_INSTANCE_TYPE              DMA_Channel_TypeDef
#endif

struct dma_config {
    DMA_INSTANCE_TYPE *Instance;
    rt_uint32_t dma_rcc;
    IRQn_Type dma_irq;
};

#ifdef __cplusplus
}
#endif

#endif /*__DRV_DMA_H_ */
