/*
 * Copyright (c) 2012-2019, Mobvoi BSP Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2019-11-27     fanming      first version
 */

#ifndef __OSPI_CONFIG_H__
#define __OSPI_CONFIG_H__

#include <rtthread.h>

#ifdef __cplusplus
extern "C" {
#endif

#ifdef BSP_USING_OSPI
#ifndef OSPI_BUS_CONFIG
#define OSPI_BUS_CONFIG                                                                       \
    {                                                                                         \
        .Instance                   = OCTOSPI1,                                               \
        .Init.FifoThreshold         = 4,                                                      \
        .Init.ChipSelectHighTime    = 2,                                                      \
        .Init.DualQuad              = HAL_OSPI_DUALQUAD_DISABLE,                              \
        .Init.MemoryType            = HAL_OSPI_MEMTYPE_MACRONIX,                              \
        .Init.FreeRunningClock      = HAL_OSPI_FREERUNCLK_DISABLE,                            \
        .Init.ClockMode             = HAL_OSPI_CLOCK_MODE_0,                                  \
        .Init.WrapSize              = HAL_OSPI_WRAP_NOT_SUPPORTED,                            \
        .Init.ClockPrescaler        = 2, /* OctoSPI clock = sysclk / ClockPrescaler */        \
        .Init.SampleShifting        = HAL_OSPI_SAMPLE_SHIFTING_NONE,                          \
        .Init.DelayHoldQuarterCycle = HAL_OSPI_DHQC_ENABLE,                                   \
        .Init.ChipSelectBoundary    = 0,                                                      \
    }
#endif /* OSPI_BUS_CONFIG */
#endif /* BSP_USING_OSPI */

#ifdef BSP_OSPI_USING_DMA
#ifndef OSPI1_DMA_CONFIG
#define OSPI1_DMA_CONFIG                                        \
    {                                                          \
        .Instance = OSPI1_DMA_INSTANCE,                         \
        .Init.Request = OSPI1_DMA_REQUEST,                      \
        .Init.Direction = DMA_PERIPH_TO_MEMORY,                \
        .Init.PeriphInc = DMA_PINC_DISABLE,                    \
        .Init.MemInc = DMA_MINC_ENABLE,                        \
        .Init.PeriphDataAlignment = DMA_PDATAALIGN_BYTE,       \
        .Init.MemDataAlignment = DMA_MDATAALIGN_BYTE,          \
        .Init.Mode = DMA_NORMAL,                               \
        .Init.Priority = DMA_PRIORITY_LOW                      \
    }
#endif /* OSPI1_DMA_CONFIG */
#endif /* BSP_OSPI_USING_DMA */

#define OSPI1_IRQn                   OCTOSPI1_IRQn
#define OSPI1_IRQHandler             OCTOSPI1_IRQHandler

#ifdef __cplusplus
}
#endif

#endif /* __QSPI_CONFIG_H__ */
