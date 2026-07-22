/*
 * Copyright (c) 2006-2023, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2026-02-26     ox-horse     first version
 */

#ifndef __TIM_CONFIG_H__
#define __TIM_CONFIG_H__

#include <rtthread.h>

#ifdef __cplusplus
extern "C" {
#endif

#ifndef TIM_DEV_INFO_CONFIG
#define TIM_DEV_INFO_CONFIG                \
    {                                      \
        .maxfreq = 1000000,                \
        .minfreq = 3000,                   \
        .maxcnt  = 0xFFFF,                 \
        .cntmode = CLOCK_TIMER_CNTMODE_UP, \
    }
#endif /* TIM_DEV_INFO_CONFIG */

#ifdef BSP_USING_ATIM1
#ifndef ATIM1_CONFIG
#define ATIM1_CONFIG               \
    {                              \
        .timer    = ATIM1,         \
        .tim_irqn = ATIM1_UP_IRQn, \
        .name     = "timer1",      \
    }
#endif /* ATIM1_CONFIG */
#endif /* BSP_USING_ATIM1 */

#ifdef BSP_USING_ATIM2
#ifndef ATIM2_CONFIG
#define ATIM2_CONFIG               \
    {                              \
        .timer    = ATIM2,         \
        .tim_irqn = ATIM2_UP_IRQn, \
        .name     = "timer2",      \
    }
#endif /* ATIM2_CONFIG */
#endif /* BSP_USING_ATIM2 */

#ifdef BSP_USING_ATIM3
#ifndef ATIM3_CONFIG
#define ATIM3_CONFIG               \
    {                              \
        .timer    = ATIM3,         \
        .tim_irqn = ATIM3_UP_IRQn, \
        .name     = "timer3",      \
    }
#endif /* ATIM3_CONFIG */
#endif /* BSP_USING_ATIM3 */

#ifdef BSP_USING_ATIM4
#ifndef ATIM4_CONFIG
#define ATIM4_CONFIG               \
    {                              \
        .timer    = ATIM4,         \
        .tim_irqn = ATIM4_UP_IRQn, \
        .name     = "timer4",      \
    }
#endif /* ATIM4_CONFIG */
#endif /* BSP_USING_ATIM4 */

#ifdef BSP_USING_GTIMA1
#ifndef GTIMA1_CONFIG
#define GTIMA1_CONFIG            \
    {                            \
        .timer    = GTIMA1,      \
        .tim_irqn = GTIMA1_IRQn, \
        .name     = "timer5",    \
    }
#endif /* GTIMA1_CONFIG */
#endif /* BSP_USING_GTIMA1 */

#ifdef BSP_USING_GTIMA2
#ifndef GTIMA2_CONFIG
#define GTIMA2_CONFIG            \
    {                            \
        .timer    = GTIMA2,      \
        .tim_irqn = GTIMA2_IRQn, \
        .name     = "timer6",    \
    }
#endif /* GTIMA2_CONFIG */
#endif /* BSP_USING_GTIMA2 */

#ifdef BSP_USING_GTIMA3
#ifndef GTIMA3_CONFIG
#define GTIMA3_CONFIG            \
    {                            \
        .timer    = GTIMA3,      \
        .tim_irqn = GTIMA3_IRQn, \
        .name     = "timer7",    \
    }
#endif /* GTIMA3_CONFIG */
#endif /* BSP_USING_GTIMA3 */

#ifdef BSP_USING_GTIMA4
#ifndef GTIMA4_CONFIG
#define GTIMA4_CONFIG            \
    {                            \
        .timer    = GTIMA4,      \
        .tim_irqn = GTIMA4_IRQn, \
        .name     = "timer8",    \
    }
#endif /* GTIMA4_CONFIG */
#endif /* BSP_USING_GTIMA4 */

#ifdef BSP_USING_GTIMA5
#ifndef GTIMA5_CONFIG
#define GTIMA5_CONFIG            \
    {                            \
        .timer    = GTIMA5,      \
        .tim_irqn = GTIMA5_IRQn, \
        .name     = "timer9",    \
    }
#endif /* GTIMA5_CONFIG */
#endif /* BSP_USING_GTIMA5 */

#ifdef BSP_USING_GTIMA6
#ifndef GTIMA6_CONFIG
#define GTIMA6_CONFIG            \
    {                            \
        .timer    = GTIMA6,      \
        .tim_irqn = GTIMA6_IRQn, \
        .name     = "timer10",   \
    }
#endif /* GTIMA6_CONFIG */
#endif /* BSP_USING_GTIMA6 */

#ifdef BSP_USING_GTIMA7
#ifndef GTIMA7_CONFIG
#define GTIMA7_CONFIG            \
    {                            \
        .timer    = GTIMA7,      \
        .tim_irqn = GTIMA7_IRQn, \
        .name     = "timer11",   \
    }
#endif /* GTIMA7_CONFIG */
#endif /* BSP_USING_GTIMA7 */

#ifdef BSP_USING_GTIMB1
#ifndef GTIMB1_CONFIG
#define GTIMB1_CONFIG            \
    {                            \
        .timer    = GTIMB1,      \
        .tim_irqn = GTIMB1_IRQn, \
        .name     = "timer12",   \
    }
#endif /* GTIMB1_CONFIG */
#endif /* BSP_USING_GTIMB1 */

#ifdef BSP_USING_GTIMB2
#ifndef GTIMB2_CONFIG
#define GTIMB2_CONFIG            \
    {                            \
        .timer    = GTIMB2,      \
        .tim_irqn = GTIMB2_IRQn, \
        .name     = "timer13",   \
    }
#endif /* GTIMB2_CONFIG */
#endif /* BSP_USING_GTIMB2 */

#ifdef BSP_USING_GTIMB3
#ifndef GTIMB3_CONFIG
#define GTIMB3_CONFIG            \
    {                            \
        .timer    = GTIMB3,      \
        .tim_irqn = GTIMB3_IRQn, \
        .name     = "timer14",   \
    }
#endif /* GTIMB3_CONFIG */
#endif /* BSP_USING_GTIMB3 */

#ifdef BSP_USING_BTIM1
#ifndef BTIM1_CONFIG
#define BTIM1_CONFIG            \
    {                           \
        .timer    = BTIM1,      \
        .tim_irqn = BTIM1_IRQn, \
        .name     = "timer15",  \
    }
#endif /* BTIM1_CONFIG */
#endif /* BSP_USING_BTIM1 */

#ifdef BSP_USING_BTIM2
#ifndef BTIM2_CONFIG
#define BTIM2_CONFIG            \
    {                           \
        .timer    = BTIM2,      \
        .tim_irqn = BTIM2_IRQn, \
        .name     = "timer16",  \
    }
#endif /* BTIM2_CONFIG */
#endif /* BSP_USING_BTIM2 */

#ifdef BSP_USING_BTIM3
#ifndef BTIM3_CONFIG
#define BTIM3_CONFIG            \
    {                           \
        .timer    = BTIM3,      \
        .tim_irqn = BTIM3_IRQn, \
        .name     = "timer17",  \
    }
#endif /* BTIM3_CONFIG */
#endif /* BSP_USING_BTIM3 */

#ifdef BSP_USING_BTIM4
#ifndef BTIM4_CONFIG
#define BTIM4_CONFIG            \
    {                           \
        .timer    = BTIM4,      \
        .tim_irqn = BTIM4_IRQn, \
        .name     = "timer18",  \
    }
#endif /* BTIM4_CONFIG */
#endif /* BSP_USING_BTIM4 */

#ifdef __cplusplus
}
#endif

#endif /* __TIM_CONFIG_H__ */
