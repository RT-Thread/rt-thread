/*
 * Copyright (c) 2006-2023, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2021-08-20     breo.com     first version
 */

#ifndef __TIM_CONFIG_H__
#define __TIM_CONFIG_H__

#include <rtthread.h>
#include <drivers/hwtimer.h>

#ifdef __cplusplus
extern "C" {
#endif

#ifndef TIM_DEV_INFO_CONFIG
#define TIM_DEV_INFO_CONFIG                     \
    {                                           \
        .maxfreq = 1000000,                     \
        .minfreq = 1000,                        \
        .maxcnt  = 0xFFFF,                      \
        .cntmode = HWTIMER_CNTMODE_UP,          \
    }
#endif /* TIM_DEV_INFO_CONFIG */

#ifdef BSP_USING_HWTIM2
#ifndef TIM2_CONFIG
#define TIM2_CONFIG                   \
    {                                 \
       .tim_handle    = TIM2,         \
       .tim_irqn      = TIM2_IRQn,    \
       .name          = "timer2",     \
    }
#endif /* TIM2_CONFIG */
#endif /* BSP_USING_HWTIM2 */

#ifdef BSP_USING_HWTIM3
#ifndef TIM3_CONFIG
#define TIM3_CONFIG                   \
    {                                 \
       .tim_handle    = TIM3,         \
       .tim_irqn      = TIM3_IRQn,    \
       .name          = "timer3",     \
    }
#endif /* TIM3_CONFIG */
#endif /* BSP_USING_HWTIM3 */

#ifdef BSP_USING_HWTIM4
#ifndef TIM4_CONFIG
#define TIM4_CONFIG                   \
    {                                 \
       .tim_handle    = TIM4,         \
       .tim_irqn      = TIM4_IRQn,    \
       .name          = "timer4",     \
    }
#endif /* TIM4_CONFIG */
#endif /* BSP_USING_HWTIM4 */

#ifdef BSP_USING_HWTIM5
#ifndef TIM5_CONFIG
#define TIM5_CONFIG                   \
    {                                 \
       .tim_handle    = TIM5,         \
       .tim_irqn      = TIM5_IRQn,    \
       .name          = "timer5",     \
    }
#endif /* TIM5_CONFIG */
#endif /* BSP_USING_HWTIM5 */

#ifdef BSP_USING_HWTIM6
#ifndef TIM6_CONFIG
#define TIM6_CONFIG                   \
    {                                 \
       .tim_handle    = TIM6,         \
       .tim_irqn      = TIM6_IRQn,    \
       .name          = "timer6",     \
    }
#endif /* TIM6_CONFIG */
#endif /* BSP_USING_HWTIM6 */

#ifdef BSP_USING_HWTIM7
#ifndef TIM7_CONFIG
#define TIM7_CONFIG                   \
    {                                 \
       .tim_handle    = TIM7,         \
       .tim_irqn      = TIM7_IRQn,    \
       .name          = "timer7",     \
    }
#endif /* TIM7_CONFIG */
#endif /* BSP_USING_HWTIM7 */


#ifdef __cplusplus
}
#endif

#endif /* __TIM_CONFIG_H__ */

