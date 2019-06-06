/*
 * Copyright (c) 2006-2018, RT-Thread Development Team
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

<<<<<<< HEAD
#if defined(SOC_SERIES_STM32F0)
=======
#ifdef __cplusplus
extern "C" {
#endif

#if defined(SOC_SERIES_STM32F0)
#include "f0/dma_config.h"
>>>>>>> 49e424905b5922b07aa7166ec7a0eeb90adf58a8
#include "f0/uart_config.h"
#include "f0/spi_config.h"
#include "f0/tim_config.h"
#include "f0/pwm_config.h"
#include "f0/adc_config.h"
#elif defined(SOC_SERIES_STM32F1)
<<<<<<< HEAD
=======
#include "f1/dma_config.h"
>>>>>>> 49e424905b5922b07aa7166ec7a0eeb90adf58a8
#include "f1/uart_config.h"
#include "f1/spi_config.h"
#include "f1/adc_config.h"
#include "f1/tim_config.h"
#include "f1/sdio_config.h"
#include "f1/pwm_config.h"
#elif  defined(SOC_SERIES_STM32F4)
<<<<<<< HEAD
#include "f4/uart_config.h"
#include "f4/spi_config.h"
=======
#include "f4/dma_config.h"
#include "f4/uart_config.h"
#include "f4/spi_config.h"
#include "f4/qspi_config.h"
#include "f4/usbd_fs_config.h"
>>>>>>> 49e424905b5922b07aa7166ec7a0eeb90adf58a8
#include "f4/adc_config.h"
#include "f4/tim_config.h"
#include "f4/sdio_config.h"
#include "f4/pwm_config.h"
#elif  defined(SOC_SERIES_STM32F7)
<<<<<<< HEAD
=======
#include "f7/dma_config.h"
>>>>>>> 49e424905b5922b07aa7166ec7a0eeb90adf58a8
#include "f7/uart_config.h"
#include "f7/spi_config.h"
#include "f7/qspi_config.h"
#include "f7/adc_config.h"
#include "f7/tim_config.h"
#include "f7/sdio_config.h"
#include "f7/pwm_config.h"
<<<<<<< HEAD
#elif  defined(SOC_SERIES_STM32L4)
=======
#elif  defined(SOC_SERIES_STM32L0)
#include "l0/dma_config.h"
#include "l0/uart_config.h"
#elif  defined(SOC_SERIES_STM32L4)
#include "l4/dma_config.h"
>>>>>>> 49e424905b5922b07aa7166ec7a0eeb90adf58a8
#include "l4/uart_config.h"
#include "l4/spi_config.h"
#include "l4/qspi_config.h"
#include "l4/adc_config.h"
#include "l4/tim_config.h"
<<<<<<< HEAD
#include "l4/pwm_config.h"
=======
#include "l4/sdio_config.h"
#include "l4/pwm_config.h"
#elif  defined(SOC_SERIES_STM32G0)
#include "g0/dma_config.h"
#include "g0/uart_config.h"
#include "g0/spi_config.h"
#include "g0/adc_config.h"
#include "g0/tim_config.h"
#include "g0/pwm_config.h"
#elif  defined(SOC_SERIES_STM32H7)
#include "h7/dma_config.h"
#include "h7/uart_config.h"
#include "h7/spi_config.h"
#include "h7/qspi_config.h"
#include "h7/adc_config.h"
#include "h7/tim_config.h"
#include "h7/sdio_config.h"
#include "h7/pwm_config.h"
#endif

#ifdef __cplusplus
}
>>>>>>> 49e424905b5922b07aa7166ec7a0eeb90adf58a8
#endif

#endif
