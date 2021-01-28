/*
 * Copyright (c) 2020-2020, BLUETRUM Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#ifndef AB32VG1_HAL_CONF_H__
#define AB32VG1_HAL_CONF_H__

/*  System Configuration  */
#define HAL_GPIO_MODULE_ENABLED
#define HAL_UART_MODULE_ENABLED
#define HAL_RCU_MODULE_ENABLED
#define HAL_WDT_MODULE_ENABLED
// #define HAL_DAC_MODULE_ENABLED
#define HAL_SD_MODULE_ENABLED
#define HAL_TIM_MODULE_ENABLED

/*  Includes  */
#ifdef HAL_GPIO_MODULE_ENABLED
#include "ab32vg1_hal_gpio.h"
#endif

#ifdef HAL_UART_MODULE_ENABLED
#include "ab32vg1_hal_uart.h"
#endif

#ifdef HAL_RCU_MODULE_ENABLED
#include "ab32vg1_hal_rcu.h"
#endif

#ifdef HAL_WDT_MODULE_ENABLED
#include "ab32vg1_hal_wdt.h"
#endif

#ifdef HAL_DAC_MODULE_ENABLED
#include "ab32vg1_hal_dac.h"
#endif

#ifdef HAL_SD_MODULE_ENABLED
#include "ab32vg1_hal_sd.h"
#endif

#ifdef HAL_TIM_MODULE_ENABLED
#include "ab32vg1_hal_tim.h"
#endif

#include <assert.h>

#endif
