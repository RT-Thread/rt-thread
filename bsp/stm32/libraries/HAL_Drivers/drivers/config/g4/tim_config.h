/*
 * Copyright (c) 2006-2023, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2018-12-11     zylx         first version
 * 2023-12-7      supperthomas  add timer
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

#ifdef BSP_USING_TIM1
#ifndef TIM1_CONFIG
#define TIM1_CONFIG                                        \
    {                                                      \
       .tim_handle.Instance     = TIM1,                    \
       .tim_irqn                = TIM1_UP_TIM16_IRQn,                    \
       .name                    = "timer1",                \
    }
#endif /* TIM1_CONFIG */
#endif /* BSP_USING_TIM1 */

#ifdef BSP_USING_TIM2
#ifndef TIM2_CONFIG
#define TIM2_CONFIG                                        \
    {                                                      \
       .tim_handle.Instance     = TIM2,                    \
       .tim_irqn                = TIM2_IRQn,               \
       .name                    = "timer2",                \
    }
#endif /* TIM2_CONFIG */
#endif /* BSP_USING_TIM2 */

#ifdef BSP_USING_TIM3
#ifndef TIM3_CONFIG
#define TIM3_CONFIG                                        \
    {                                                      \
       .tim_handle.Instance     = TIM3,                    \
       .tim_irqn                = TIM3_IRQn,               \
       .name                    = "timer3",                \
    }
#endif /* TIM3_CONFIG */
#endif /* BSP_USING_TIM3 */

#ifdef BSP_USING_TIM4
#ifndef TIM4_CONFIG
#define TIM4_CONFIG                                        \
    {                                                      \
       .tim_handle.Instance     = TIM4,                    \
       .tim_irqn                = TIM4_IRQn,               \
       .name                    = "timer4",                \
    }
#endif /* TIM4_CONFIG */
#endif /* BSP_USING_TIM4 */

#ifdef BSP_USING_TIM6
#ifndef TIM6_CONFIG
#define TIM6_CONFIG                                        \
    {                                                      \
       .tim_handle.Instance     = TIM6,                    \
       .tim_irqn                = TIM6_IRQn,               \
       .name                    = "timer6",                \
    }
#endif /* TIM7_CONFIG */
#endif /* BSP_USING_TIM7 */

#ifdef BSP_USING_TIM7
#ifndef TIM7_CONFIG
#define TIM7_CONFIG                                        \
    {                                                      \
       .tim_handle.Instance     = TIM7,                    \
       .tim_irqn                = TIM7_IRQn,               \
       .name                    = "timer7",                \
    }
#endif /* TIM7_CONFIG */
#endif /* BSP_USING_TIM7 */

#ifdef BSP_USING_TIM8
#ifndef TIM8_CONFIG
#define TIM8_CONFIG                                        \
    {                                                      \
       .tim_handle.Instance     = TIM8,                    \
       .tim_irqn                = TIM8_UP_IRQn,                    \
       .name                    = "timer8",                \
    }
#endif /* TIM8_CONFIG */
#endif /* BSP_USING_TIM8 */

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

#ifdef BSP_USING_TIM15
#ifndef TIM15_CONFIG
#define TIM15_CONFIG                                        \
    {                                                       \
       .tim_handle.Instance     = TIM15,                    \
       .tim_irqn                = TIM1_BRK_TIM15_IRQn,                     \
       .name                    = "timer15",                \
    }
#endif /* TIM16_CONFIG */
#endif /* BSP_USING_TIM16 */

#ifdef BSP_USING_TIM16
#ifndef TIM16_CONFIG
#define TIM16_CONFIG                                        \
    {                                                       \
       .tim_handle.Instance     = TIM16,                    \
       .tim_irqn                = TIM1_UP_TIM16_IRQn,                     \
       .name                    = "timer16",                \
    }
#endif /* TIM16_CONFIG */
#endif /* BSP_USING_TIM16 */

#ifdef BSP_USING_TIM17
#ifndef TIM17_CONFIG
#define TIM17_CONFIG                                        \
    {                                                       \
       .tim_handle.Instance     = TIM17,                    \
       .tim_irqn                = TIM1_TRG_COM_TIM17_IRQn,                     \
       .name                    = "timer17",                \
    }
#endif /* TIM17_CONFIG */
#endif /* BSP_USING_TIM17 */

#ifdef __cplusplus
}
#endif

#endif /* __TIM_CONFIG_H__ */
