/*
 * Copyright (c) 2006-2024 RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author             Notes
 * 2022-07-29     rtthread qiu      first version
 */

#ifndef __DRV_HWTIMER_H__
#define __DRV_HWTIMER_H__

#include <rtthread.h>

#include "cy_pdl.h"
#include "cyhal.h"
#include "cybsp.h"
#include "cy_retarget_io.h"

#ifndef TIM_DEV_INFO_CONFIG
#define TIM_DEV_INFO_CONFIG            \
    {                                  \
        .maxfreq = 1000000,            \
        .minfreq = 2000,               \
        .maxcnt = 0xFFFF,              \
        .cntmode = HWTIMER_CNTMODE_UP, \
    }
#endif /* TIM_DEV_INFO_CONFIG */

#ifdef BSP_USING_TIM1
#ifndef TIM1_CONFIG
#define TIM1_CONFIG                            \
    {                                          \
        .tim_irqn = tcpwm_0_interrupts_0_IRQn, \
        .name = "time1",                       \
    }
#endif /*TIM1_CONFIG*/
#endif /* BSP_USING_TIM1 */

#ifdef BSP_USING_TIM2
#ifndef TIM2_CONFIG
#define TIM2_CONFIG                            \
    {                                          \
        .tim_irqn = tcpwm_1_interrupts_0_IRQn, \
        .name = "time2",                       \
    }
#endif /*TIM2_CONFIG*/
#endif /* BSP_USING_TIM2 */

#endif /* __DRV_HWTIMER_H__ */
