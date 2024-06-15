/*
 * Copyright (c) 2006-2023, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2018-12-11     zylx         first version
 * 2023-08-21     Donocean     support all timers(except advanced timer)
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
        .minfreq = 3000,                        \
        .maxcnt  = 0xFFFF,                      \
        .cntmode = HWTIMER_CNTMODE_UP,          \
    }
#endif /* TIM_DEV_INFO_CONFIG */

#ifdef BSP_USING_TIM2
#ifndef TIM2_CONFIG
#define TIM2_CONFIG                                         \
    {                                                       \
       .tim_handle.Instance     = TIM2,                     \
       .tim_irqn                = TIM2_IRQn,                \
       .name                    = "timer2",                 \
    }
#endif /* TIM2_CONFIG */
#endif /* BSP_USING_TIM2 */

#ifdef BSP_USING_TIM3
#ifndef TIM3_CONFIG
#define TIM3_CONFIG                                         \
    {                                                       \
       .tim_handle.Instance     = TIM3,                     \
       .tim_irqn                = TIM3_IRQn,                \
       .name                    = "timer3",                 \
    }
#endif /* TIM3_CONFIG */
#endif /* BSP_USING_TIM3 */

#ifdef BSP_USING_TIM4
#ifndef TIM4_CONFIG
#define TIM4_CONFIG                                         \
    {                                                       \
       .tim_handle.Instance     = TIM4,                     \
       .tim_irqn                = TIM4_IRQn,                \
       .name                    = "timer4",                 \
    }
#endif /* TIM4_CONFIG */
#endif /* BSP_USING_TIM4 */

#ifdef BSP_USING_TIM5
#ifndef TIM5_CONFIG
#define TIM5_CONFIG                                         \
    {                                                       \
       .tim_handle.Instance     = TIM5,                     \
       .tim_irqn                = TIM5_IRQn,                \
       .name                    = "timer5",                 \
    }
#endif /* TIM5_CONFIG */
#endif /* BSP_USING_TIM5 */

#ifdef BSP_USING_TIM6
#ifndef TIM6_CONFIG
#if defined(STM32F412Cx) || defined(STM32F412Rx) || defined(STM32F412Vx) || defined(STM32F412Zx)
#define TIM6_CONFIG                                         \
    {                                                       \
       .tim_handle.Instance     = TIM6,                     \
       .tim_irqn                = TIM6_IRQn,                \
       .name                    = "timer6",                 \
    }
#else
#define TIM6_CONFIG                                         \
    {                                                       \
       .tim_handle.Instance     = TIM6,                     \
       .tim_irqn                = TIM6_DAC_IRQn,            \
       .name                    = "timer6",                 \
    }
#endif /* defined(STM32F412Cx) || defined(STM32F412Rx) || defined(STM32F412Vx) || defined(STM32F412Zx) */
#endif /* TIM6_CONFIG */
#endif /* BSP_USING_TIM6 */

#ifdef BSP_USING_TIM7
#ifndef TIM7_CONFIG
#define TIM7_CONFIG                                         \
    {                                                       \
       .tim_handle.Instance     = TIM7,                     \
       .tim_irqn                = TIM7_IRQn,                \
       .name                    = "timer7",                 \
    }
#endif /* TIM7_CONFIG */
#endif /* BSP_USING_TIM7 */

#ifdef BSP_USING_TIM9
#ifndef TIM9_CONFIG
#define TIM9_CONFIG                                         \
    {                                                       \
       .tim_handle.Instance     = TIM9,                     \
       .tim_irqn                = TIM1_BRK_TIM9_IRQn,       \
       .name                    = "timer9",                 \
    }
#endif /* TIM9_CONFIG */
#endif /* BSP_USING_TIM9 */

#ifdef BSP_USING_TIM10
#ifndef TIM10_CONFIG
#define TIM10_CONFIG                                        \
    {                                                       \
       .tim_handle.Instance     = TIM10,                    \
       .tim_irqn                = TIM1_UP_TIM10_IRQn,       \
       .name                    = "timer10",                \
    }
#endif /* TIM10_CONFIG */
#endif /* BSP_USING_TIM10 */

#ifdef BSP_USING_TIM11
#ifndef TIM11_CONFIG
#define TIM11_CONFIG                                        \
    {                                                       \
       .tim_handle.Instance     = TIM11,                    \
       .tim_irqn                = TIM1_TRG_COM_TIM11_IRQn,  \
       .name                    = "timer11",                \
    }
#endif /* TIM11_CONFIG */
#endif /* BSP_USING_TIM11 */

#ifdef BSP_USING_TIM12
#ifndef TIM12_CONFIG
#define TIM12_CONFIG                                        \
    {                                                       \
       .tim_handle.Instance     = TIM12,                    \
       .tim_irqn                = TIM8_BRK_TIM12_IRQn,      \
       .name                    = "timer12",                \
    }
#endif /* TIM12_CONFIG */
#endif /* BSP_USING_TIM12 */

#ifdef BSP_USING_TIM13
#ifndef TIM13_CONFIG
#define TIM13_CONFIG                                        \
    {                                                       \
       .tim_handle.Instance     = TIM13,                    \
       .tim_irqn                = TIM8_UP_TIM13_IRQn,       \
       .name                    = "timer13",                \
    }
#endif /* TIM13_CONFIG */
#endif /* BSP_USING_TIM13 */

#ifdef BSP_USING_TIM14
#ifndef TIM14_CONFIG
#define TIM14_CONFIG                                        \
    {                                                       \
       .tim_handle.Instance     = TIM14,                    \
       .tim_irqn                = TIM8_TRG_COM_TIM14_IRQn,  \
       .name                    = "timer14",                \
    }
#endif /* TIM14_CONFIG */
#endif /* BSP_USING_TIM14 */

#ifdef __cplusplus
}
#endif

#endif /* __TIM_CONFIG_H__ */
