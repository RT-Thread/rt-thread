/*
 * Copyright (c) 2006-2018, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author            Notes
 * 2018-10-30     SummerGift   change to new framework
 */
 
#ifndef __DRV_CONFIG_H__
#define __DRV_CONFIG_H__

#include <board.h>
#include <rtthread.h>

#if defined(SOC_SERIES_STM32F1)
#include "f1/uart_config.h"
#include "f1/spi_config.h"
#elif  defined(SOC_SERIES_STM32F4)
#include "f4/uart_config.h"
#include "f4/spi_config.h"
#elif  defined(SOC_SERIES_STM32L4)
#include "l4/uart_config.h"
#include "l4/spi_config.h"
#endif

#endif
