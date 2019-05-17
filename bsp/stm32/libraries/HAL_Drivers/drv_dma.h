/*
 * Copyright (c) 2006-2018, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2018-11-10     SummerGift   first version
 */

#ifndef __DRV_DMA_H_
#define __DRV_DMA_H_

#include <rtthread.h>
#include <board.h>

#ifdef __cplusplus
extern "C" {
#endif

#if defined(SOC_SERIES_STM32F0) || defined(SOC_SERIES_STM32F1) || defined(SOC_SERIES_STM32L0) \
	|| defined(SOC_SERIES_STM32L4) || defined(SOC_SERIES_STM32G0)
#define DMA_INSTANCE_TYPE              DMA_Channel_TypeDef
#elif defined(SOC_SERIES_STM32F4) || defined(SOC_SERIES_STM32F7) || defined(SOC_SERIES_STM32H7)
#define DMA_INSTANCE_TYPE              DMA_Stream_TypeDef
#endif /*  defined(SOC_SERIES_STM32F1) || defined(SOC_SERIES_STM32L4) */

struct dma_config {
    DMA_INSTANCE_TYPE *Instance;
    rt_uint32_t dma_rcc;
    IRQn_Type dma_irq;

#if defined(SOC_SERIES_STM32F4) || defined(SOC_SERIES_STM32F7)
    rt_uint32_t channel;
#endif

#if defined(SOC_SERIES_STM32L4) || defined(SOC_SERIES_STM32G0)
    rt_uint32_t request;
#endif
};

#ifdef __cplusplus
}
#endif

#endif /*__DRV_DMA_H_ */
