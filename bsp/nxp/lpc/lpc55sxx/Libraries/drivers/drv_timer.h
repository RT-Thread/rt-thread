/*
 * Copyright (c) 2006-2023, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
* Change Logs:
* Date           Author       Notes
* 2018-04-17     WangBing     the first version.
*/

#ifndef DRV_CLOCK_TIMER_H__
#define DRV_CLOCK_TIMER_H__

#include <rtthread.h>
#include <rtdevice.h>

#ifdef BSP_USING_CTIMER0
#define TIM1_CONFIG                                         \
    {                                                       \
       .tim_handle              = CTIMER0,                     \
       .tim_irqn                = CTIMER0_IRQn,                \
       .name                    = "timer1",                 \
    }
#endif /* TIM1_CONFIG */

#ifdef BSP_USING_CTIMER3
#define TIM3_CONFIG                                         \
    {                                                       \
       .tim_handle              = CTIMER3,                     \
       .tim_irqn                = CTIMER3_IRQn,                \
       .name                    = "timer2",                 \
    }
#endif /* TIM3_CONFIG */

#ifdef BSP_USING_CTIMER4
#define TIM4_CONFIG                                         \
    {                                                       \
       .tim_handle              = CTIMER4,                     \
       .tim_irqn                = CTIMER4_IRQn,                \
       .name                    = "timer3",                 \
    }
#endif /* TIM4_CONFIG */

int rt_hw_clock_timer_init(void);

#endif /* __DRV_CLOCK_TIMER_H__ */

