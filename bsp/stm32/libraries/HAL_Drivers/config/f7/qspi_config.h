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

<<<<<<< HEAD
=======
#ifdef __cplusplus
extern "C" {
#endif

>>>>>>> 49e424905b5922b07aa7166ec7a0eeb90adf58a8
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
<<<<<<< HEAD
    
=======

>>>>>>> 49e424905b5922b07aa7166ec7a0eeb90adf58a8
#ifdef BSP_QSPI_USING_DMA
#ifndef QSPI_DMA_CONFIG
#define QSPI_DMA_CONFIG                                        \
    {                                                          \
<<<<<<< HEAD
        .Instance = DMA2_Stream7,                              \
        .Init.Channel  = DMA_CHANNEL_3,                        \
=======
        .Instance = QSPI_DMA_INSTANCE,                         \
        .Init.Channel  = QSPI_DMA_CHANNEL,                     \
>>>>>>> 49e424905b5922b07aa7166ec7a0eeb90adf58a8
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

<<<<<<< HEAD
#define QSPI_DMA_CLK_ENABLE         __HAL_RCC_DMA2_CLK_ENABLE()
#define QSPI_IRQn                   QUADSPI_IRQn
#define QSPI_DMA_IRQn               DMA2_Stream7_IRQn
#define QSPI_IRQHandler             QUADSPI_IRQHandler
#define QSPI_DMA_IRQHandler         DMA2_Stream7_IRQHandler
=======
#define QSPI_IRQn                   QUADSPI_IRQn
#define QSPI_IRQHandler             QUADSPI_IRQHandler

#ifdef __cplusplus
}
#endif
>>>>>>> 49e424905b5922b07aa7166ec7a0eeb90adf58a8

#endif /* __QSPI_CONFIG_H__ */
