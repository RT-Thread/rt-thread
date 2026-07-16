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
#include "h7xx/dma_config.h"
#include "h7xx/uart_config.h"
#include "h7xx/i2c_hard_config.h"
#include "h7xx/adc_config.h"
#include "h7xx/spi_config.h"
#include "h7xx/tim_config.h"
#include "h7xx/dac_config.h"
#include "h7xx/can_config.h"
#include "h7xx/pwm_config.h"
#include "h7xx/pulse_encoder_config.h"
#include "h7xx/lptim_config.h"
#elif defined(SOC_SERIES_N32H49x)
#include "h49x/dma_config.h"
#include "h49x/uart_config.h"
#elif defined(SOC_SERIES_N32H47x_48x)
#include "h47x_48x/dma_config.h"
#include "h47x_48x/uart_config.h"
#endif /* defined(SOC_SERIES_N32H7xx) */

#ifdef __cplusplus
}
#endif

#endif /*__DRV_CONFIG_H_ */

