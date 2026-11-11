/*
 * Copyright (c) 2006-2023, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2018-12-22     zylx         first version
 * 2026-04-13     wdfk-prog    Unify DMA config descriptors
 */

#ifndef __QSPI_CONFIG_H__
#define __QSPI_CONFIG_H__

#include <rtthread.h>

#ifdef __cplusplus
extern "C" {
#endif

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
#ifndef QSPI_DMA_PRIORITY
#define QSPI_DMA_PRIORITY                         DMA_PRIORITY_LOW
#endif /* QSPI_DMA_PRIORITY */

#ifndef QSPI_DMA_PREEMPT_PRIORITY
#define QSPI_DMA_PREEMPT_PRIORITY                 0
#endif /* QSPI_DMA_PREEMPT_PRIORITY */

#ifndef QSPI_DMA_SUB_PRIORITY
#define QSPI_DMA_SUB_PRIORITY                     0
#endif /* QSPI_DMA_SUB_PRIORITY */

#ifndef QSPI_DMA_CONFIG
#define QSPI_DMA_CONFIG               \
    STM32_DMA_RX_BYTE_CONFIG_INIT_EX( \
        QSPI_DMA_INSTANCE,            \
        QSPI_DMA_RCC,                 \
        QSPI_DMA_IRQ,                 \
        0U,                           \
        QSPI_DMA_REQUEST,             \
        QSPI_DMA_PRIORITY,            \
        QSPI_DMA_PREEMPT_PRIORITY,    \
        QSPI_DMA_SUB_PRIORITY)
#endif /* QSPI_DMA_CONFIG */
#endif /* BSP_QSPI_USING_DMA */

#define QSPI_IRQn                   QUADSPI_IRQn
#define QSPI_IRQHandler             QUADSPI_IRQHandler

#ifdef __cplusplus
}
#endif

#endif /* __QSPI_CONFIG_H__ */
