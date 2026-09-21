/*
 * Copyright (c) 2006-2025, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2026-08-19     ox-horse     first version
 */

#ifndef __TIM_CONFIG_H__
#define __TIM_CONFIG_H__

#include <rtthread.h>

#ifdef __cplusplus
extern "C" {
#endif

/* The timer clock is 240 MHz and PSC is only 16 bits wide, so 3663 Hz is the
 * lowest frequency that still fits -- 240000000 / 65536 rounds up to 3663.
 * drv_tim.c rejects anything below that, so advertise the same floor here.
 */
#ifndef TIM_DEV_INFO_CONFIG
#define TIM_DEV_INFO_CONFIG                \
    {                                      \
        .maxfreq = 1000000,                \
        .minfreq = 3663,                   \
        .maxcnt = 0xFFFF,                  \
        .cntmode = CLOCK_TIMER_CNTMODE_UP, \
    }
#endif /* TIM_DEV_INFO_CONFIG */

/* Same floor: a 32-bit counter widens CNT/ARR, not PSC. */
#ifndef TIM_32BIT_DEV_INFO_CONFIG
#define TIM_32BIT_DEV_INFO_CONFIG          \
    {                                      \
        .maxfreq = 1000000,                \
        .minfreq = 3663,                   \
        .maxcnt = 0xFFFFFFFFU,             \
        .cntmode = CLOCK_TIMER_CNTMODE_UP, \
    }
#endif /* TIM_32BIT_DEV_INFO_CONFIG */

#ifdef BSP_USING_ATIM1
#ifndef ATIM1_CONFIG
#define ATIM1_CONFIG               \
    {                              \
        .timer = ATIM1,            \
        .tim_irqn = ATIM1_UP_IRQn, \
        .name = "timer1",          \
    }
#endif /* ATIM1_CONFIG */
#endif /* BSP_USING_ATIM1 */

#ifdef BSP_USING_ATIM2
#ifndef ATIM2_CONFIG
#define ATIM2_CONFIG               \
    {                              \
        .timer = ATIM2,            \
        .tim_irqn = ATIM2_UP_IRQn, \
        .name = "timer2",          \
    }
#endif /* ATIM2_CONFIG */
#endif /* BSP_USING_ATIM2 */

#ifdef BSP_USING_ATIM3
#ifndef ATIM3_CONFIG
#define ATIM3_CONFIG               \
    {                              \
        .timer = ATIM3,            \
        .tim_irqn = ATIM3_UP_IRQn, \
        .name = "timer3",          \
    }
#endif /* ATIM3_CONFIG */
#endif /* BSP_USING_ATIM3 */

#ifdef BSP_USING_GTIM1
#ifndef GTIM1_CONFIG
#define GTIM1_CONFIG            \
    {                           \
        .timer = GTIM1,         \
        .tim_irqn = GTIM1_IRQn, \
        .name = "timer5",       \
    }
#endif /* GTIM1_CONFIG */
#endif /* BSP_USING_GTIM1 */

#ifdef BSP_USING_GTIM2
#ifndef GTIM2_CONFIG
#define GTIM2_CONFIG            \
    {                           \
        .timer = GTIM2,         \
        .tim_irqn = GTIM2_IRQn, \
        .name = "timer6",       \
    }
#endif /* GTIM2_CONFIG */
#endif /* BSP_USING_GTIM2 */

#ifdef BSP_USING_GTIM3
#ifndef GTIM3_CONFIG
#define GTIM3_CONFIG            \
    {                           \
        .timer = GTIM3,         \
        .tim_irqn = GTIM3_IRQn, \
        .name = "timer7",       \
    }
#endif /* GTIM3_CONFIG */
#endif /* BSP_USING_GTIM3 */

#ifdef BSP_USING_GTIM4
#ifndef GTIM4_CONFIG
#define GTIM4_CONFIG            \
    {                           \
        .timer = GTIM4,         \
        .tim_irqn = GTIM4_IRQn, \
        .name = "timer8",       \
    }
#endif /* GTIM4_CONFIG */
#endif /* BSP_USING_GTIM4 */

#ifdef BSP_USING_GTIM5
#ifndef GTIM5_CONFIG
#define GTIM5_CONFIG            \
    {                           \
        .timer = GTIM5,         \
        .tim_irqn = GTIM5_IRQn, \
        .name = "timer9",       \
    }
#endif /* GTIM5_CONFIG */
#endif /* BSP_USING_GTIM5 */

#ifdef BSP_USING_GTIM6
#ifndef GTIM6_CONFIG
#define GTIM6_CONFIG            \
    {                           \
        .timer = GTIM6,         \
        .tim_irqn = GTIM6_IRQn, \
        .name = "timer10",      \
    }
#endif /* GTIM6_CONFIG */
#endif /* BSP_USING_GTIM6 */

#ifdef BSP_USING_GTIM7
#ifndef GTIM7_CONFIG
#define GTIM7_CONFIG            \
    {                           \
        .timer = GTIM7,         \
        .tim_irqn = GTIM7_IRQn, \
        .name = "timer11",      \
    }
#endif /* GTIM7_CONFIG */
#endif /* BSP_USING_GTIM7 */

#ifdef BSP_USING_GTIM8
#ifndef GTIM8_CONFIG
#define GTIM8_CONFIG            \
    {                           \
        .timer = GTIM8,         \
        .tim_irqn = GTIM8_IRQn, \
        .name = "timer12",      \
    }
#endif /* GTIM8_CONFIG */
#endif /* BSP_USING_GTIM8 */

#ifdef BSP_USING_GTIM9
#ifndef GTIM9_CONFIG
#define GTIM9_CONFIG            \
    {                           \
        .timer = GTIM9,         \
        .tim_irqn = GTIM9_IRQn, \
        .name = "timer13",      \
    }
#endif /* GTIM9_CONFIG */
#endif /* BSP_USING_GTIM9 */

#ifdef BSP_USING_GTIM10
#ifndef GTIM10_CONFIG
#define GTIM10_CONFIG            \
    {                            \
        .timer = GTIM10,         \
        .tim_irqn = GTIM10_IRQn, \
        .name = "timer14",       \
    }
#endif /* GTIM10_CONFIG */
#endif /* BSP_USING_GTIM10 */

#ifdef BSP_USING_BTIM1
#ifndef BTIM1_CONFIG
#define BTIM1_CONFIG            \
    {                           \
        .timer = BTIM1,         \
        .tim_irqn = BTIM1_IRQn, \
        .name = "timer15",      \
    }
#endif /* BTIM1_CONFIG */
#endif /* BSP_USING_BTIM1 */

#ifdef BSP_USING_BTIM2
#ifndef BTIM2_CONFIG
#define BTIM2_CONFIG            \
    {                           \
        .timer = BTIM2,         \
        .tim_irqn = BTIM2_IRQn, \
        .name = "timer16",      \
    }
#endif /* BTIM2_CONFIG */
#endif /* BSP_USING_BTIM2 */

#ifdef __cplusplus
}
#endif

#endif /* __TIM_CONFIG_H__ */
