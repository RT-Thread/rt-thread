/*
 * Copyright (c) 2021 Rockchip Electronics Co., Ltd.
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2021-10-12     Steven Liu   first implementation
 */

#ifndef _HAL_CONF_H_
#define _HAL_CONF_H_

#include "rtconfig.h"

/* HAL CPU config */
#define SOC_RK2108
#define HAL_MCU_CORE
#define SYS_TIMER TIMER5

/* RT-Thread Tick Timer */
#ifdef RT_USING_SYSTICK
#define TICK_IRQn  SysTick_IRQn
#define HAL_SYSTICK_MODULE_ENABLED
#else
#define TICK_TIMER TIMER4
#define TICK_IRQn  TIMER4_IRQn
#endif

#ifdef RT_USING_CACHE
#define HAL_DCACHE_MODULE_ENABLED
#define HAL_ICACHE_MODULE_ENABLED
#endif

#ifdef RT_USING_CRU
#define HAL_CRU_MODULE_ENABLED
#endif

#define HAL_NVIC_MODULE_ENABLED

#ifdef RT_USING_PIN
#define HAL_GPIO_MODULE_ENABLED
#define HAL_PINCTRL_MODULE_ENABLED
#endif

#ifdef RT_USING_PM_RUNTIME
#define HAL_PM_RUNTIME_MODULE_ENABLED
#endif

#define HAL_TIMER_MODULE_ENABLED

#ifdef RT_USING_UART
#define HAL_UART_MODULE_ENABLED
#endif

#endif
