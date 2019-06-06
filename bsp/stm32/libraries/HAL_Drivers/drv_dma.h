/*
 * Copyright (c) 2006-2018, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
<<<<<<< HEAD
 * 2018-11-10      SummerGift   change to new framework
=======
 * 2018-11-10     SummerGift   first version
>>>>>>> 49e424905b5922b07aa7166ec7a0eeb90adf58a8
 */

#ifndef __DRV_DMA_H_
#define __DRV_DMA_H_

#include <rtthread.h>
<<<<<<< HEAD
#include "rtdevice.h"
#include <rthw.h>
#include <drv_common.h>

#if defined(SOC_SERIES_STM32F0) || (SOC_SERIES_STM32F1) || defined(SOC_SERIES_STM32L4)
#define DMA_INSTANCE_TYPE              DMA_Channel_TypeDef
#elif defined(SOC_SERIES_STM32F4) || defined(SOC_SERIES_STM32F7)
=======
#include <board.h>

#ifdef __cplusplus
extern "C" {
#endif

#if defined(SOC_SERIES_STM32F0) || defined(SOC_SERIES_STM32F1) || defined(SOC_SERIES_STM32L0) \
	|| defined(SOC_SERIES_STM32L4) || defined(SOC_SERIES_STM32G0)
#define DMA_INSTANCE_TYPE              DMA_Channel_TypeDef
#elif defined(SOC_SERIES_STM32F4) || defined(SOC_SERIES_STM32F7) || defined(SOC_SERIES_STM32H7)
>>>>>>> 49e424905b5922b07aa7166ec7a0eeb90adf58a8
#define DMA_INSTANCE_TYPE              DMA_Stream_TypeDef
#endif /*  defined(SOC_SERIES_STM32F1) || defined(SOC_SERIES_STM32L4) */

struct dma_config {
    DMA_INSTANCE_TYPE *Instance;
    rt_uint32_t dma_rcc;
    IRQn_Type dma_irq;

#if defined(SOC_SERIES_STM32F4) || defined(SOC_SERIES_STM32F7)
    rt_uint32_t channel;
#endif

<<<<<<< HEAD
#if defined(SOC_SERIES_STM32L4)
=======
#if defined(SOC_SERIES_STM32L4) || defined(SOC_SERIES_STM32G0)
>>>>>>> 49e424905b5922b07aa7166ec7a0eeb90adf58a8
    rt_uint32_t request;
#endif
};

<<<<<<< HEAD
=======
#ifdef __cplusplus
}
#endif
>>>>>>> 49e424905b5922b07aa7166ec7a0eeb90adf58a8

#endif /*__DRV_DMA_H_ */
