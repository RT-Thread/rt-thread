/*
 * Copyright (c) 2006-2025, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2026-01-30     pomin        first version
 */

#ifndef __HWTIMER_CONFIG_H__
#define __HWTIMER_CONFIG_H__

#include <rtthread.h>
#include <board.h>

#ifdef __cplusplus
extern "C" {
#endif

#include "drv_hwtimer.h"

#ifdef BSP_USING_HWTIMER0
#ifndef HWTIMER0_CONFIG
#define HWTIMER0_CONFIG                                 \
    {                                                   \
        "timer0",                                       \
        {                                               \
            TIMER0,                                     \
            TIMER0_UP_IRQn,                             \
            RCU_TIMER0,                                 \
        },                                              \
        {0},                                            \
        {                                               \
            1000000,                                    \
            1000,                                       \
            0xffff,                                     \
            0,         /* count up mode */              \
        }                                               \
    }
#endif /* HWTIMER0_CONFIG */
#endif /* BSP_USING_HWTIMER0 */


#ifdef BSP_USING_HWTIMER1
#ifndef HWTIMER1_CONFIG
#define HWTIMER1_CONFIG                                 \
    {                                                   \
        "timer1",                                       \
        {                                               \
            TIMER1,                                     \
            TIMER1_IRQn,                                \
            RCU_TIMER1,                                 \
        },                                              \
        {0},                                            \
        {                                               \
            1000000,                                    \
            1000,                                       \
            0xffff,                                     \
            0,         /* count up mode */              \
        }                                               \
    }
#endif /* HWTIMER1_CONFIG */
#endif /* BSP_USING_HWTIMER1 */


#ifdef BSP_USING_HWTIMER2
#ifndef HWTIMER2_CONFIG
#define HWTIMER2_CONFIG                                 \
    {                                                   \
        "timer2",                                       \
        {                                               \
            TIMER2,                                     \
            TIMER2_IRQn,                                \
            RCU_TIMER2,                                 \
        },                                              \
        {0},                                            \
        {                                               \
            1000000,                                    \
            1000,                                       \
            0xffff,                                     \
            0,         /* count up mode */              \
        }                                               \
    }
#endif /* HWTIMER2_CONFIG */
#endif /* BSP_USING_HWTIMER2 */


#ifdef BSP_USING_HWTIMER5
#ifndef HWTIMER5_CONFIG
#define HWTIMER5_CONFIG                                 \
    {                                                   \
        "timer5",                                       \
        {                                               \
            TIMER5,                                     \
            TIMER5_IRQn,                                \
            RCU_TIMER5,                                 \
        },                                              \
        {0},                                            \
        {                                               \
            1000000,                                    \
            1000,                                       \
            0xffff,                                     \
            0,         /* count up mode */              \
        }                                               \
    }
#endif /* HWTIMER5_CONFIG */
#endif /* BSP_USING_HWTIMER5 */


#ifdef BSP_USING_HWTIMER15
#ifndef HWTIMER15_CONFIG
#define HWTIMER15_CONFIG                                \
    {                                                   \
        "timer15",                                      \
        {                                               \
            TIMER15,                                    \
            TIMER15_IRQn,                               \
            RCU_TIMER15,                                \
        },                                              \
        {0},                                            \
        {                                               \
            1000000,                                    \
            1000,                                       \
            0xffff,                                     \
            0,         /* count up mode */              \
        }                                               \
    }
#endif /* HWTIMER15_CONFIG */
#endif /* BSP_USING_HWTIMER15 */


#ifdef BSP_USING_HWTIMER16
#ifndef HWTIMER16_CONFIG
#define HWTIMER16_CONFIG                                \
    {                                                   \
        "timer16",                                      \
        {                                               \
            TIMER16,                                    \
            TIMER16_IRQn,                               \
            RCU_TIMER16,                                \
        },                                              \
        {0},                                            \
        {                                               \
            1000000,                                    \
            1000,                                       \
            0xffff,                                     \
            0,         /* count up mode */              \
        }                                               \
    }
#endif /* HWTIMER16_CONFIG */
#endif /* BSP_USING_HWTIMER16 */

#ifdef __cplusplus
}
#endif

#endif /* __HWTIMER_CONFIG_H__ */
