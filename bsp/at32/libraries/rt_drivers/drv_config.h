/*
 * Copyright (c) 2006-2021, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2022-11-09     shelton      first version
 * 2023-01-31     shelton      add support f421/f425
 * 2023-04-08     shelton      add support f423
 */

#ifndef __DRV_CONFIG_H__
#define __DRV_CONFIG_H__

#include <rtthread.h>
#include "drv_common.h"

#ifdef __cplusplus
extern "C" {
#endif

#if defined(SOC_SERIES_AT32F403A) || defined (SOC_SERIES_AT32F407)
#include "f403a_407/dma_config.h"
#include "f403a_407/uart_config.h"
#include "f403a_407/spi_config.h"
#include "f403a_407/usb_config.h"
#include "f403a_407/dac_config.h"
#elif defined(SOC_SERIES_AT32F413)
#include "f413/dma_config.h"
#include "f413/uart_config.h"
#include "f413/spi_config.h"
#include "f413/usb_config.h"
#elif defined(SOC_SERIES_AT32F415)
#include "f415/dma_config.h"
#include "f415/uart_config.h"
#include "f415/spi_config.h"
#include "f415/usb_config.h"
#elif defined(SOC_SERIES_AT32F421)
#include "f421/dma_config.h"
#include "f421/uart_config.h"
#include "f421/spi_config.h"
#elif defined(SOC_SERIES_AT32F423)
#include "f423/dma_config.h"
#include "f423/uart_config.h"
#include "f423/spi_config.h"
#include "f423/usb_config.h"
#include "f423/dac_config.h"
#elif defined(SOC_SERIES_AT32F425)
#include "f425/dma_config.h"
#include "f425/uart_config.h"
#include "f425/spi_config.h"
#include "f425/usb_config.h"
#elif defined(SOC_SERIES_AT32F435) || defined (SOC_SERIES_AT32F437)
#include "f435_437/dma_config.h"
#include "f435_437/uart_config.h"
#include "f435_437/spi_config.h"
#include "f435_437/usb_config.h"
#include "f435_437/dac_config.h"
#endif

#ifdef __cplusplus
}
#endif

#endif
