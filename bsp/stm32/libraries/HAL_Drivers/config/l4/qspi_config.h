/*
 * Copyright (c) 2006-2018, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2018-12-22     zylx         first version 
 */

#ifndef __QSPI_CONFIG_H__
#define __QSPI_CONFIG_H__

#include <rtthread.h>

#ifdef BSP_USING_QSPI
#ifndef QSPI_BUS_CONFIG
#define QSPI_BUS_CONFIG                                        \
    {                                                          \
        .Instance = QUADSPI,                                   \
        .Init.FifoThreshold = 4,                               \
        .Init.SampleShifting = QSPI_SAMPLE_SHIFTING_HALFCYCLE, \
        .Init.ChipSelectHighTime = QSPI_CS_HIGH_TIME_4_CYCLE,  \
    }
#endif /* QSPI_BUS_CONFIG */
#endif /* BSP_USING_QSPI */
    
#ifdef BSP_QSPI_USING_DMA
#ifndef QSPI_DMA_CONFIG
#define QSPI_DMA_CONFIG                                        \
    {                                                          \
        .Instance = DMA1_Channel5,                             \
        .Init.Request = DMA_REQUEST_5,                         \
        .Init.Direction = DMA_PERIPH_TO_MEMORY,                \
        .Init.PeriphInc = DMA_PINC_DISABLE,                    \
        .Init.MemInc = DMA_MINC_ENABLE,                        \
        .Init.PeriphDataAlignment = DMA_PDATAALIGN_BYTE,       \
        .Init.MemDataAlignment = DMA_MDATAALIGN_BYTE,          \
        .Init.Mode = DMA_NORMAL,                               \
        .Init.Priority = DMA_PRIORITY_LOW                      \
    }
#endif /* QSPI_DMA_CONFIG */
#endif /* BSP_QSPI_USING_DMA */

#define QSPI_DMA_CLK_ENABLE         __HAL_RCC_DMA1_CLK_ENABLE()
#define QSPI_IRQn                   QUADSPI_IRQn
#define QSPI_DMA_IRQn               DMA1_Channel5_IRQn
#define QSPI_IRQHandler             QUADSPI_IRQHandler
#define QSPI_DMA_IRQHandler         DMA1_Channel5_IRQHandler

#endif /* __QSPI_CONFIG_H__ */
