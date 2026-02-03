/*
 * Copyright (c) 2006-2025, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author           Notes
 * 2026-01-24     ox-horse         first version
 */

#ifndef __DRV_CONFIG_H_
#define __DRV_CONFIG_H_

#include <board.h>
#include <rtdevice.h>

#ifdef __cplusplus
extern "C" {
#endif


#if defined(SOC_SERIES_N32H7xx)
#include "h7/dma_config.h"
#include "h7/uart_config.h"
#include "h7/i2c_hard_config.h"
#include "h7/adc_config.h"
#include "h7/spi_config.h"
#endif /* defined(SOC_SERIES_N32H7xx) */

#ifdef __cplusplus
}
#endif

#endif /*__DRV_CONFIG_H_ */

