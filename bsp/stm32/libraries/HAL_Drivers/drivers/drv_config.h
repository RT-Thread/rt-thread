/*
 * Copyright (c) 2006-2023, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author            Notes
 * 2018-10-30     SummerGift        first version
 * 2020-10-14     Dozingfiretruck   Porting for stm32wbxx
 */

#ifndef __DRV_CONFIG_H__
#define __DRV_CONFIG_H__

#include <board.h>
#include <rtdevice.h>

#ifdef __cplusplus
extern "C" {
#endif

#if defined(SOC_SERIES_STM32F0)
#include "f0/dma_config.h"
#include "f0/uart_config.h"
#include "f0/spi_config.h"
#include "f0/tim_config.h"
#include "f0/pwm_config.h"
#include "f0/adc_config.h"
#elif defined(SOC_SERIES_STM32F1)
#include "f1/dma_config.h"
#include "f1/uart_config.h"
#include "f1/spi_config.h"
#include "f1/adc_config.h"
#include "f1/tim_config.h"
#include "f1/sdio_config.h"
#include "f1/pwm_config.h"
#include "f1/usbd_config.h"
#include "f1/pulse_encoder_config.h"
#elif  defined(SOC_SERIES_STM32F2)
#include "f2/dma_config.h"
#include "f2/uart_config.h"
#include "f2/spi_config.h"
#include "f2/adc_config.h"
#include "f2/tim_config.h"
#include "f2/sdio_config.h"
#include "f2/pwm_config.h"
#elif  defined(SOC_SERIES_STM32F3)
#include "f3/uart_config.h"
#include "f3/tim_config.h"
#include "f3/pwm_config.h"
#include "f3/dma_config.h"
#elif  defined(SOC_SERIES_STM32F4)
#include "f4/dma_config.h"
#include "f4/uart_config.h"
#include "f4/spi_config.h"
#include "f4/qspi_config.h"
#include "f4/usbd_config.h"
#include "f4/adc_config.h"
#include "f4/dac_config.h"
#include "f4/tim_config.h"
#include "f4/sdio_config.h"
#include "f4/pwm_config.h"
#include "f4/i2c_hard_config.h"
#include "f4/pulse_encoder_config.h"
#elif  defined(SOC_SERIES_STM32F7)
#include "f7/dma_config.h"
#include "f7/uart_config.h"
#include "f7/spi_config.h"
#include "f7/qspi_config.h"
#include "f7/adc_config.h"
#include "f7/tim_config.h"
#include "f7/sdio_config.h"
#include "f7/pwm_config.h"
#elif  defined(SOC_SERIES_STM32L0)
#include "l0/dma_config.h"
#include "l0/uart_config.h"
#elif  defined(SOC_SERIES_STM32L4)
#include "l4/dma_config.h"
#include "l4/uart_config.h"
#include "l4/spi_config.h"
#include "l4/qspi_config.h"
#include "l4/adc_config.h"
#include "l4/dac_config.h"
#include "l4/tim_config.h"
#include "l4/sdio_config.h"
#include "l4/pwm_config.h"
#include "l4/usbd_config.h"
#elif  defined(SOC_SERIES_STM32L5)
#include "l5/dma_config.h"
#include "l5/uart_config.h"
#include "l5/spi_config.h"
#include "l5/qspi_config.h"
#include "l5/adc_config.h"
#include "l5/dac_config.h"
#include "l5/tim_config.h"
#include "l5/sdio_config.h"
#include "l5/pwm_config.h"
#include "l5/usbd_config.h"
#elif  defined(SOC_SERIES_STM32G0)
#include "g0/dma_config.h"
#include "g0/uart_config.h"
#include "g0/spi_config.h"
#include "g0/adc_config.h"
#include "g0/tim_config.h"
#include "g0/pwm_config.h"
#elif  defined(SOC_SERIES_STM32G4)
#include "g4/dma_config.h"
#include "g4/uart_config.h"
#include "g4/spi_config.h"
#include "g4/qspi_config.h"
#include "g4/usbd_config.h"
#include "g4/adc_config.h"
#include "g4/tim_config.h"
#include "g4/sdio_config.h"
#include "g4/pwm_config.h"
#include "g4/pulse_encoder_config.h"
#elif  defined(SOC_SERIES_STM32H7)
#include "h7/dma_config.h"
#include "h7/uart_config.h"
#include "h7/spi_config.h"
#include "h7/qspi_config.h"
#include "h7/adc_config.h"
#include "h7/dac_config.h"
#include "h7/tim_config.h"
#include "h7/sdio_config.h"
#include "h7/pwm_config.h"
#include "h7/usbd_config.h"

#elif  defined(SOC_SERIES_STM32H7RS)
#include "h7/dma_config.h"
#include "h7/uart_config.h"
#include "h7/spi_config.h"
#include "h7/adc_config.h"
#include "h7/dac_config.h"
#include "h7/tim_config.h"
#include "h7/pwm_config.h"
#include "h7/usbd_config.h"

#elif defined(SOC_SERIES_STM32U5)
#include "u5/dma_config.h"
#include "u5/uart_config.h"
#include "u5/spi_config.h"
#include "u5/qspi_config.h"
#include "u5/adc_config.h"
#include "u5/dac_config.h"
#include "u5/tim_config.h"
#include "u5/sdio_config.h"
#include "u5/pwm_config.h"
#include "u5/usbd_config.h"
#elif defined(SOC_SERIES_STM32H5)
#include "h5/uart_config.h"
#include "h5/pwm_config.h"
#include "h5/adc_config.h"
#elif  defined(SOC_SERIES_STM32MP1)
#include "mp1/dma_config.h"
#include "mp1/uart_config.h"
#include "mp1/qspi_config.h"
#include "mp1/spi_config.h"
#include "mp1/adc_config.h"
#include "mp1/dac_config.h"
#include "mp1/tim_config.h"
#include "mp1/pwm_config.h"
#elif  defined(SOC_SERIES_STM32WL)
#include "wl/dma_config.h"
#include "wl/uart_config.h"
#include "wl/spi_config.h"
#include "wl/tim_config.h"
#elif  defined(SOC_SERIES_STM32WB)
#include "wb/adc_config.h"
#include "wb/dma_config.h"
#include "wb/pwm_config.h"
#include "wb/qspi_config.h"
#include "wb/spi_config.h"
#include "wb/tim_config.h"
#include "wb/uart_config.h"
#include "wb/usbd_config.h"
#endif

#ifdef __cplusplus
}
#endif

#endif
