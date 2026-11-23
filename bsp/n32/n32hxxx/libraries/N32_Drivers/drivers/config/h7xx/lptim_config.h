/*
 * Copyright (c) 2006-2025, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2026-06-23     ox-horse     first version
 */

#ifndef __LPTIM_CONFIG_H__
#define __LPTIM_CONFIG_H__

#include <rtthread.h>

#ifdef __cplusplus
extern "C" {
#endif

/* LSI through a fixed DIV32, both set in drv_lptim.c's timer_init(), so the
 * tick rate is LSI_VALUE / 32 = 32000 / 32 = 1000 Hz and cannot be
 * programmed -- hence a single-point range.  clock_timer.c scales timeouts by
 * timer->freq, which it takes from here, so a wrong value scales every one.
 */
#ifndef LPTIM_DEV_INFO_CONFIG
#define LPTIM_DEV_INFO_CONFIG              \
    {                                      \
        .maxfreq = 1000,                   \
        .minfreq = 1000,                   \
        .maxcnt = 0xFFFF,                  \
        .cntmode = CLOCK_TIMER_CNTMODE_UP, \
    }
#endif /* LPTIM_DEV_INFO_CONFIG */

#ifdef BSP_USING_LPTIM1
#ifndef LPTIM1_CONFIG
#define LPTIM1_CONFIG                 \
    {                                 \
        .timer = LPTIM1,              \
        .tim_irqn = LPTIM1_WKUP_IRQn, \
        .name = "lptim1",             \
    }
#endif /* LPTIM1_CONFIG */
#endif /* BSP_USING_LPTIM1 */

#ifdef BSP_USING_LPTIM2
#ifndef LPTIM2_CONFIG
#define LPTIM2_CONFIG                 \
    {                                 \
        .timer = LPTIM2,              \
        .tim_irqn = LPTIM2_WKUP_IRQn, \
        .name = "lptim2",             \
    }
#endif /* LPTIM2_CONFIG */
#endif /* BSP_USING_LPTIM2 */

#ifdef BSP_USING_LPTIM3
#ifndef LPTIM3_CONFIG
#define LPTIM3_CONFIG                 \
    {                                 \
        .timer = LPTIM3,              \
        .tim_irqn = LPTIM3_WKUP_IRQn, \
        .name = "lptim3",             \
    }
#endif /* LPTIM3_CONFIG */
#endif /* BSP_USING_LPTIM3 */

#ifdef BSP_USING_LPTIM4
#ifndef LPTIM4_CONFIG
#define LPTIM4_CONFIG                 \
    {                                 \
        .timer = LPTIM4,              \
        .tim_irqn = LPTIM4_WKUP_IRQn, \
        .name = "lptim4",             \
    }
#endif /* LPTIM4_CONFIG */
#endif /* BSP_USING_LPTIM4 */

#ifdef BSP_USING_LPTIM5
#ifndef LPTIM5_CONFIG
#define LPTIM5_CONFIG                 \
    {                                 \
        .timer = LPTIM5,              \
        .tim_irqn = LPTIM5_WKUP_IRQn, \
        .name = "lptim5",             \
    }
#endif /* LPTIM5_CONFIG */
#endif /* BSP_USING_LPTIM5 */

#ifdef __cplusplus
}
#endif

#endif /* __LPTIM_CONFIG_H__ */
