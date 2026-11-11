/*
 * Copyright (c) 2006-2023, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2018-12-13     BalanceTWK   first version
 * 2026-04-13     wdfk-prog    Unify DMA config descriptors
 */

#ifndef __SDIO_CONFIG_H__
#define __SDIO_CONFIG_H__

#include <rtthread.h>
#include "stm32l4xx_hal.h"

#ifdef __cplusplus
extern "C" {
#endif

#ifdef BSP_USING_SDIO
#ifndef SDIO_RX_DMA_PRIORITY
#define SDIO_RX_DMA_PRIORITY                      DMA_PRIORITY_MEDIUM
#endif /* SDIO_RX_DMA_PRIORITY */

#ifndef SDIO_RX_DMA_PREEMPT_PRIORITY
#define SDIO_RX_DMA_PREEMPT_PRIORITY              0
#endif /* SDIO_RX_DMA_PREEMPT_PRIORITY */

#ifndef SDIO_RX_DMA_SUB_PRIORITY
#define SDIO_RX_DMA_SUB_PRIORITY                  0
#endif /* SDIO_RX_DMA_SUB_PRIORITY */

#ifndef SDIO_TX_DMA_PRIORITY
#define SDIO_TX_DMA_PRIORITY                      DMA_PRIORITY_MEDIUM
#endif /* SDIO_TX_DMA_PRIORITY */

#ifndef SDIO_TX_DMA_PREEMPT_PRIORITY
#define SDIO_TX_DMA_PREEMPT_PRIORITY              0
#endif /* SDIO_TX_DMA_PREEMPT_PRIORITY */

#ifndef SDIO_TX_DMA_SUB_PRIORITY
#define SDIO_TX_DMA_SUB_PRIORITY                  0
#endif /* SDIO_TX_DMA_SUB_PRIORITY */

#define SDIO_BUS_CONFIG                             \
    {                                               \
        .Instance = SDMMC1,                         \
        .dma_rx = STM32_DMA_RX_WORD_CONFIG_INIT_EX( \
            DMA2_Channel4,                          \
            RCC_AHB1ENR_DMA2EN,                     \
            DMA2_Channel4_IRQn,                     \
            0U,                                     \
            DMA_REQUEST_7,                          \
            SDIO_RX_DMA_PRIORITY,                   \
            SDIO_RX_DMA_PREEMPT_PRIORITY,           \
            SDIO_RX_DMA_SUB_PRIORITY),              \
        .dma_tx = STM32_DMA_TX_WORD_CONFIG_INIT_EX( \
            DMA2_Channel5,                          \
            RCC_AHB1ENR_DMA2EN,                     \
            DMA2_Channel5_IRQn,                     \
            0U,                                     \
            DMA_REQUEST_7,                          \
            SDIO_TX_DMA_PRIORITY,                   \
            SDIO_TX_DMA_PREEMPT_PRIORITY,           \
            SDIO_TX_DMA_SUB_PRIORITY),              \
    }

#endif

#ifdef __cplusplus
}
#endif

#endif /*__SDIO_CONFIG_H__ */



