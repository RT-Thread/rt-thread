/*
 * Copyright (c) 2006-2023, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2018-01-05     zylx         first version
 * 2019-01-08     SummerGift   clean up the code
 */

#ifndef __TIM_CONFIG_H__
#define __TIM_CONFIG_H__

#include <rtthread.h>

#ifdef __cplusplus
extern "C" {
#endif

#ifndef TIM_DEV_INFO_CONFIG
#define TIM_DEV_INFO_CONFIG                     \
    {                                           \
        .maxfreq = 1000000,                     \
        .minfreq = 2000,                        \
        .maxcnt  = 0xFFFF,                      \
        .cntmode = HWTIMER_CNTMODE_UP,          \
    }
#endif /* TIM_DEV_INFO_CONFIG */

#ifdef BSP_USING_TIM2
#ifndef TIM2_CONFIG
#define TIM2_CONFIG                             \
    {                                           \
       .tim_handle.Instance     = TIM2,         \
       .tim_irqn                = TIM2_IRQn,    \
       .name                    = "timer2",     \
    }
#endif /* TIM2_CONFIG */
#endif /* BSP_USING_TIM2 */

#ifdef BSP_USING_TIM3
#ifndef TIM3_CONFIG
#if defined(STM32G0B0xx) || defined(STM32G0B1xx) || defined(STM32G0C1xx)
#define TIM3_CONFIG                             \
    {                                           \
       .tim_handle.Instance     = TIM3,         \
       .tim_irqn                = TIM3_TIM4_IRQn, \
       .name                    = "timer3",     \
    }
#else
#define TIM3_CONFIG                             \
    {                                           \
       .tim_handle.Instance     = TIM3,         \
       .tim_irqn                = TIM3_IRQn,    \
       .name                    = "timer3",     \
    }
#endif /* defined(STM32G0B0xx) || defined(STM32G0B1xx) || defined(STM32G0C1xx) */
#endif /* TIM3_CONFIG */
#endif /* BSP_USING_TIM3 */

#ifdef __cplusplus
}
#endif

#endif /* __TIM_CONFIG_H__ */
