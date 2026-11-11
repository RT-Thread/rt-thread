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
#include "stm32h7xx_hal.h"

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

#define SDIO_BUS_CONFIG                          \
    {                                            \
        .Instance = SDMMC1,                      \
        .dma_rx = STM32_DMA_CONFIG_INIT_FIFO_EX( \
            DMA2_Stream3,                        \
            RCC_AHB1ENR_DMA2EN,                  \
            DMA2_Stream3_IRQn,                   \
            DMA_CHANNEL_4,                       \
            0U,                                  \
            SDIO_RX_DMA_PRIORITY,                \
            SDIO_RX_DMA_PREEMPT_PRIORITY,        \
            SDIO_RX_DMA_SUB_PRIORITY,            \
            DMA_PERIPH_TO_MEMORY,                \
            DMA_PINC_DISABLE,                    \
            DMA_MINC_ENABLE,                     \
            DMA_PDATAALIGN_WORD,                 \
            DMA_MDATAALIGN_WORD,                 \
            DMA_PFCTRL,                          \
            DMA_FIFOMODE_ENABLE,                 \
            DMA_FIFO_THRESHOLD_FULL,             \
            DMA_MBURST_INC4,                     \
            DMA_PBURST_INC4),                    \
        .dma_tx = STM32_DMA_CONFIG_INIT_FIFO_EX( \
            DMA2_Stream6,                        \
            RCC_AHB1ENR_DMA2EN,                  \
            DMA2_Stream6_IRQn,                   \
            DMA_CHANNEL_4,                       \
            0U,                                  \
            SDIO_TX_DMA_PRIORITY,                \
            SDIO_TX_DMA_PREEMPT_PRIORITY,        \
            SDIO_TX_DMA_SUB_PRIORITY,            \
            DMA_MEMORY_TO_PERIPH,                \
            DMA_PINC_DISABLE,                    \
            DMA_MINC_ENABLE,                     \
            DMA_PDATAALIGN_WORD,                 \
            DMA_MDATAALIGN_WORD,                 \
            DMA_PFCTRL,                          \
            DMA_FIFOMODE_ENABLE,                 \
            DMA_FIFO_THRESHOLD_FULL,             \
            DMA_MBURST_INC4,                     \
            DMA_PBURST_INC4),                    \
    }

#endif

#ifdef __cplusplus
}
#endif

#endif /*__SDIO_CONFIG_H__ */



