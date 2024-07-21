/*
 * Copyright (c) 2006-2024 RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date         Author       Notes
 * 2024-07-11   wdfk-prog    first version
 */

#ifndef __LPTIM_CONFIG_H__
#define __LPTIM_CONFIG_H__

#include <rtthread.h>

#ifdef __cplusplus
extern "C" {
#endif

#ifndef LPTIM_DEV_INFO_CONFIG
#define LPTIM_DEV_INFO_CONFIG                   \
    {                                           \
        .maxfreq = 1000000,                     \
        .minfreq = 3000,                        \
        .maxcnt  = 0xFFFF,                      \
        .cntmode = HWTIMER_CNTMODE_UP,          \
    }
#endif /* TIM_DEV_INFO_CONFIG */

#ifdef BSP_USING_LPTIM1
#ifndef LPTIM1_CONFIG
#define LPTIM1_CONFIG                                       \
    {                                                       \
       .tim_handle.Instance     = LPTIM1,                   \
       .tim_irqn                = LPTIM1_IRQn,              \
       .name                    = "lptim1",                 \
    }
#endif /* LPTIM1_CONFIG */
#endif /* BSP_USING_LPTIM1 */

#ifdef BSP_USING_LPTIM2
#ifndef LPTIM2_CONFIG
#define LPTIM2_CONFIG                                       \
    {                                                       \
       .tim_handle.Instance     = LPTIM2,                   \
       .tim_irqn                = LPTIM2_IRQn,              \
       .name                    = "lptim2",                 \
    }
#endif /* LPTIM1_CONFIG */
#endif /* BSP_USING_LPTIM1 */

#ifdef BSP_USING_LPTIM3
#ifndef LPTIM3_CONFIG
#define LPTIM3_CONFIG                                       \
    {                                                       \
       .tim_handle.Instance     = LPTIM3,                   \
       .tim_irqn                = LPTIM3_IRQn,              \
       .name                    = "lptim3",                 \
    }
#endif /* LPTIM3_CONFIG */
#endif /* BSP_USING_LPTIM3 */

#ifdef __cplusplus
}
#endif

#endif /* __LPTIM_CONFIG_H__ */
