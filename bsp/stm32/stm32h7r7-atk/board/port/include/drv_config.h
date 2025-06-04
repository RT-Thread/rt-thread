/*
 * Copyright (c) 2006-2025, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author            Notes
 * 2018-10-30     SummerGift        first version
 */

#ifndef __DRV_CONFIG_H__
#define __DRV_CONFIG_H__

#include <board.h>
#include <rtthread.h>

#ifdef __cplusplus
extern "C" {
#endif

#if defined(SOC_SERIES_STM32F0)
#include "config/dma_config.h"
#include "config/uart_config.h"
#include "config/spi_config.h"
#include "config/tim_config.h"
#include "config/pwm_config.h"
#include "config/adc_config.h"
#elif defined(SOC_SERIES_STM32F1)
#include "config/dma_config.h"
#include "config/uart_config.h"
#include "config/spi_config.h"
#include "config/adc_config.h"
#include "config/tim_config.h"
#include "config/sdio_config.h"
#include "config/pwm_config.h"
#include "config/usbd_config.h"
#include "config/pulse_encoder_config.h"
#elif  defined(SOC_SERIES_STM32F2)
#include "config/dma_config.h"
#include "config/uart_config.h"
#include "config/spi_config.h"
#include "config/adc_config.h"
#include "config/tim_config.h"
#include "config/sdio_config.h"
#include "config/pwm_config.h"
#elif  defined(SOC_SERIES_STM32F4)
#include "config/dma_config.h"
#include "config/uart_config.h"
#include "config/spi_config.h"
#include "config/qspi_config.h"
#include "config/usbd_config.h"
#include "config/adc_config.h"
#include "config/tim_config.h"
#include "config/sdio_config.h"
#include "config/pwm_config.h"
#include "config/pulse_encoder_config.h"
#elif  defined(SOC_SERIES_STM32F7)
#include "config/dma_config.h"
#include "config/uart_config.h"
#include "config/spi_config.h"
#include "config/qspi_config.h"
#include "config/adc_config.h"
#include "config/tim_config.h"
#include "config/sdio_config.h"
#include "config/pwm_config.h"
#elif  defined(SOC_SERIES_STM32L0)
#include "config/dma_config.h"
#include "config/uart_config.h"
#elif  defined(SOC_SERIES_STM32L1)
#include "config/dma_config.h"
#include "config/uart_config.h"
#include "config/spi_config.h"
#include "config/adc_config.h"
#include "config/tim_config.h"
#include "config/sdio_config.h"
#include "config/pwm_config.h"
#include "config/usbd_config.h"
#elif  defined(SOC_SERIES_STM32L4)
#include "config/dma_config.h"
#include "config/uart_config.h"
#include "config/spi_config.h"
#include "config/qspi_config.h"
#include "config/adc_config.h"
#include "config/tim_config.h"
#include "config/sdio_config.h"
#include "config/pwm_config.h"
#include "config/usbd_config.h"
#elif  defined(SOC_SERIES_STM32G0)
#include "config/dma_config.h"
#include "config/uart_config.h"
#include "config/spi_config.h"
#include "config/adc_config.h"
#include "config/tim_config.h"
#include "config/pwm_config.h"
#elif  defined(SOC_SERIES_STM32G4)
#include "config/dma_config.h"
#include "config/uart_config.h"
#include "config/spi_config.h"
#include "config/qspi_config.h"
#include "config/usbd_config.h"
#include "config/adc_config.h"
#include "config/tim_config.h"
#include "config/sdio_config.h"
#include "config/pwm_config.h"
#include "config/pulse_encoder_config.h"
#elif  defined(SOC_SERIES_STM32H7)
#include "config/dma_config.h"
#include "config/uart_config.h"
#include "config/spi_config.h"
#include "config/qspi_config.h"
#include "config/adc_config.h"
#include "config/tim_config.h"
#include "config/sdio_config.h"
#include "config/pwm_config.h"
#include "config/usbd_config.h"
#elif  defined(SOC_SERIES_STM32H7RS)
#include "config/uart_config.h"
#include "config/spi_config.h"
#endif

#ifdef __cplusplus
}
#endif

#endif
