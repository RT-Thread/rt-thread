/*
 * Copyright (c) 2006-2026, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2026-08-17     CliffLL      first version
 */

#ifndef __OSPI_CONFIG_H__
#define __OSPI_CONFIG_H__

#include <rtthread.h>

#ifdef __cplusplus
extern "C" {
#endif

#ifdef BSP_USING_OSPI
#ifndef OSPI_INSTANCE
#define OSPI_INSTANCE                  OCTOSPI1
#endif

#ifndef OSPI_MEMORY_TYPE
#define OSPI_MEMORY_TYPE               HAL_OSPI_MEMTYPE_MACRONIX
#endif

#ifndef OSPI_CLK_PORT
#define OSPI_CLK_PORT                  1U
#endif

#ifndef OSPI_DQS_PORT
#define OSPI_DQS_PORT                  1U
#endif

#ifndef OSPI_NCS_PORT
#define OSPI_NCS_PORT                  1U
#endif

#ifndef OSPI_IO_LOW_PORT
#define OSPI_IO_LOW_PORT               HAL_OSPIM_IOPORT_1_LOW
#endif

#ifndef OSPI_IO_HIGH_PORT
#define OSPI_IO_HIGH_PORT              HAL_OSPIM_IOPORT_1_HIGH
#endif

#ifndef OSPI_BUS_CONFIG
#define OSPI_BUS_CONFIG                                        \
    {                                                          \
        .Instance = OSPI_INSTANCE,                             \
        .Init.FifoThreshold = 4,                               \
        .Init.SampleShifting = HAL_OSPI_SAMPLE_SHIFTING_NONE,  \
        .Init.ChipSelectHighTime = 2,                          \
        .Init.DualQuad = HAL_OSPI_DUALQUAD_DISABLE,            \
        .Init.FreeRunningClock = HAL_OSPI_FREERUNCLK_DISABLE,  \
        .Init.ChipSelectBoundary = 0,                          \
        .Init.MemoryType = OSPI_MEMORY_TYPE,                   \
    }
#endif /* OSPI_BUS_CONFIG */
#endif /* BSP_USING_OSPI */

#ifdef __cplusplus
}
#endif

#endif /* __OSPI_CONFIG_H__ */
