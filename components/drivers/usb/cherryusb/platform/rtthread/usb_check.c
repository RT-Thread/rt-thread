/*
 * Copyright (c) 2022 ~ 2025, sakumisu
 *
 * SPDX-License-Identifier: Apache-2.0
 */
#include "rtthread.h"
#include "usb_config.h"

#if defined(PKG_CHERRYUSB_HOST) || defined(RT_CHERRYUSB_HOST)

#ifndef RT_USING_TIMER_SOFT
#error must enable RT_USING_TIMER_SOFT to support timer callback in thread
#endif

#if RT_TIMER_THREAD_STACK_SIZE < 1024
#error "RT_TIMER_THREAD_STACK_SIZE must be >= 1024"
#endif
#endif

#if defined(ARCH_ARM_CORTEX_M7) ||                                          \
    defined(SOC_HPM6000) || defined(SOC_HPM6E00) || defined(SOC_HPM6P00) || \
    defined(BSP_USING_BL61X) || defined(BSP_USING_BL808)
#ifndef RT_USING_CACHE
#error RT_USING_CACHE must be enabled in this chip
#endif
#endif

#ifdef RT_USING_CACHE
#ifndef CONFIG_USB_DCACHE_ENABLE
#warning CONFIG_USB_DCACHE_ENABLE must be enabled if you do not config nocache ram
#endif
#endif
