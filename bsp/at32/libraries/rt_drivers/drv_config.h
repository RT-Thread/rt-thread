/*
 * Copyright (c) 2006-2021, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2022-11-09     shelton      first version
 */

#ifndef __DRV_CONFIG_H__
#define __DRV_CONFIG_H__

#include <board.h>
#include <rtthread.h>

#ifdef __cplusplus
extern "C" {
#endif

#if defined(SOC_SERIES_AT32F403A) || defined (SOC_SERIES_AT32F407)
#include "f403a_407/dma_config.h"
#include "f403a_407/uart_config.h"
#include "f403a_407/spi_config.h"
#elif defined(SOC_SERIES_AT32F413)
#include "f413/dma_config.h"
#include "f413/uart_config.h"
#include "f413/spi_config.h"
#elif defined(SOC_SERIES_AT32F415)
#include "f415/dma_config.h"
#include "f415/uart_config.h"
#include "f415/spi_config.h"
#elif defined(SOC_SERIES_AT32F435) || defined (SOC_SERIES_AT32F437)
#include "f435_437/dma_config.h"
#include "f435_437/uart_config.h"
#include "f435_437/spi_config.h"
#endif

#ifdef __cplusplus
}
#endif

#endif
