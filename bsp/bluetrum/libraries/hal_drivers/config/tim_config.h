/*
 * Copyright (c) 2020-2021, Bluetrum Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author            Notes
 * 2021-01-22     greedyhao         first version
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
        .maxcnt  = 0xFFFFFFFF,                  \
        .cntmode = HWTIMER_CNTMODE_UP,          \
    }
#endif /* TIM_DEV_INFO_CONFIG */

#ifdef BSP_USING_TIM1
#ifndef TIM1_CONFIG
#define TIM1_CONFIG                             \
    {                                           \
       .tim_handle      = TIM1_BASE,            \
       .tim_irqn        = IRQ_TMR1_VECTOR,      \
       .name            = "timer1",             \
    }
#endif /* TIM1_CONFIG */
#endif /* BSP_USING_TIM1 */

#ifdef BSP_USING_TIM2
#ifndef TIM2_CONFIG
#define TIM2_CONFIG                             \
    {                                           \
       .tim_handle      = TIM2_BASE,            \
       .tim_irqn        = IRQ_TMR2_4_5_VECTOR,  \
       .name            = "timer2",             \
    }
#endif /* TIM1_CONFIG */
#endif /* BSP_USING_TIM2 */

#ifdef BSP_USING_TIM3
#ifndef TIM3_CONFIG
#define TIM3_CONFIG                             \
    {                                           \
       .tim_handle      = TIM3_BASE,            \
       .tim_irqn        = IRQ_IRRX_VECTOR,      \
       .name            = "timer3",             \
    }
#endif /* TIM1_CONFIG */
#endif /* BSP_USING_TIM3 */

#ifdef BSP_USING_TIM4
#ifndef TIM4_CONFIG
#define TIM4_CONFIG                             \
    {                                           \
       .tim_handle      = TIM4_BASE,            \
       .tim_irqn        = IRQ_TMR2_4_5_VECTOR,  \
       .name            = "timer4",             \
    }
#endif /* TIM1_CONFIG */
#endif /* BSP_USING_TIM4 */

#ifdef BSP_USING_TIM5
#ifndef TIM5_CONFIG
#define TIM5_CONFIG                             \
    {                                           \
       .tim_handle      = TIM5_BASE,            \
       .tim_irqn        = IRQ_TMR2_4_5_VECTOR,  \
       .name            = "timer5",             \
    }
#endif /* TIM1_CONFIG */
#endif /* BSP_USING_TIM5 */

#ifdef __cplusplus
}
#endif

#endif /* __TIM_CONFIG_H__ */
