/*
 * Copyright (c) 2006-2025, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2026-07-06     ox-horse     first version
 */

#ifndef __PULSE_ENCODER_CONFIG_H__
#define __PULSE_ENCODER_CONFIG_H__

#include <rtthread.h>

#ifdef __cplusplus
extern "C" {
#endif

#ifdef BSP_USING_PULSE_ENCODER1
#ifndef PULSE_ENCODER1_CONFIG
#define PULSE_ENCODER1_CONFIG      \
    {                              \
        .timer    = ATIM1,         \
        .tim_irqn = ATIM1_UP_IRQn, \
        .name     = "pulse1",      \
    }
#endif /* PULSE_ENCODER1_CONFIG */
#endif /* BSP_USING_PULSE_ENCODER1 */

#ifdef BSP_USING_PULSE_ENCODER2
#ifndef PULSE_ENCODER2_CONFIG
#define PULSE_ENCODER2_CONFIG      \
    {                              \
        .timer    = ATIM2,         \
        .tim_irqn = ATIM2_UP_IRQn, \
        .name     = "pulse2",      \
    }
#endif /* PULSE_ENCODER2_CONFIG */
#endif /* BSP_USING_PULSE_ENCODER2 */

#ifdef BSP_USING_PULSE_ENCODER3
#ifndef PULSE_ENCODER3_CONFIG
#define PULSE_ENCODER3_CONFIG      \
    {                              \
        .timer    = ATIM3,         \
        .tim_irqn = ATIM3_UP_IRQn, \
        .name     = "pulse3",      \
    }
#endif /* PULSE_ENCODER3_CONFIG */
#endif /* BSP_USING_PULSE_ENCODER3 */

#ifdef BSP_USING_PULSE_ENCODER4
#ifndef PULSE_ENCODER4_CONFIG
#define PULSE_ENCODER4_CONFIG      \
    {                              \
        .timer    = ATIM4,         \
        .tim_irqn = ATIM4_UP_IRQn, \
        .name     = "pulse4",      \
    }
#endif /* PULSE_ENCODER4_CONFIG */
#endif /* BSP_USING_PULSE_ENCODER4 */

#ifdef BSP_USING_PULSE_ENCODER5
#ifndef PULSE_ENCODER5_CONFIG
#define PULSE_ENCODER5_CONFIG    \
    {                            \
        .timer    = GTIMA1,      \
        .tim_irqn = GTIMA1_IRQn, \
        .name     = "pulse5",    \
    }
#endif /* PULSE_ENCODER5_CONFIG */
#endif /* BSP_USING_PULSE_ENCODER5 */

#ifdef BSP_USING_PULSE_ENCODER6
#ifndef PULSE_ENCODER6_CONFIG
#define PULSE_ENCODER6_CONFIG    \
    {                            \
        .timer    = GTIMA2,      \
        .tim_irqn = GTIMA2_IRQn, \
        .name     = "pulse6",    \
    }
#endif /* PULSE_ENCODER6_CONFIG */
#endif /* BSP_USING_PULSE_ENCODER6 */

#ifdef BSP_USING_PULSE_ENCODER7
#ifndef PULSE_ENCODER7_CONFIG
#define PULSE_ENCODER7_CONFIG    \
    {                            \
        .timer    = GTIMA3,      \
        .tim_irqn = GTIMA3_IRQn, \
        .name     = "pulse7",    \
    }
#endif /* PULSE_ENCODER7_CONFIG */
#endif /* BSP_USING_PULSE_ENCODER7 */

#ifdef BSP_USING_PULSE_ENCODER8
#ifndef PULSE_ENCODER8_CONFIG
#define PULSE_ENCODER8_CONFIG    \
    {                            \
        .timer    = GTIMA4,      \
        .tim_irqn = GTIMA4_IRQn, \
        .name     = "pulse8",    \
    }
#endif /* PULSE_ENCODER8_CONFIG */
#endif /* BSP_USING_PULSE_ENCODER8 */

#ifdef BSP_USING_PULSE_ENCODER9
#ifndef PULSE_ENCODER9_CONFIG
#define PULSE_ENCODER9_CONFIG    \
    {                            \
        .timer    = GTIMA5,      \
        .tim_irqn = GTIMA5_IRQn, \
        .name     = "pulse9",    \
    }
#endif /* PULSE_ENCODER9_CONFIG */
#endif /* BSP_USING_PULSE_ENCODER9 */

#ifdef BSP_USING_PULSE_ENCODER10
#ifndef PULSE_ENCODER10_CONFIG
#define PULSE_ENCODER10_CONFIG   \
    {                            \
        .timer    = GTIMA6,      \
        .tim_irqn = GTIMA6_IRQn, \
        .name     = "pulse10",   \
    }
#endif /* PULSE_ENCODER10_CONFIG */
#endif /* BSP_USING_PULSE_ENCODER10 */

#ifdef BSP_USING_PULSE_ENCODER11
#ifndef PULSE_ENCODER11_CONFIG
#define PULSE_ENCODER11_CONFIG   \
    {                            \
        .timer    = GTIMA7,      \
        .tim_irqn = GTIMA7_IRQn, \
        .name     = "pulse11",   \
    }
#endif /* PULSE_ENCODER11_CONFIG */
#endif /* BSP_USING_PULSE_ENCODER11 */

#ifdef BSP_USING_PULSE_ENCODER12
#ifndef PULSE_ENCODER12_CONFIG
#define PULSE_ENCODER12_CONFIG   \
    {                            \
        .timer    = GTIMB1,      \
        .tim_irqn = GTIMB1_IRQn, \
        .name     = "pulse12",   \
    }
#endif /* PULSE_ENCODER12_CONFIG */
#endif /* BSP_USING_PULSE_ENCODER12 */

#ifdef BSP_USING_PULSE_ENCODER13
#ifndef PULSE_ENCODER13_CONFIG
#define PULSE_ENCODER13_CONFIG   \
    {                            \
        .timer    = GTIMB2,      \
        .tim_irqn = GTIMB2_IRQn, \
        .name     = "pulse13",   \
    }
#endif /* PULSE_ENCODER13_CONFIG */
#endif /* BSP_USING_PULSE_ENCODER13 */

#ifdef BSP_USING_PULSE_ENCODER14
#ifndef PULSE_ENCODER14_CONFIG
#define PULSE_ENCODER14_CONFIG   \
    {                            \
        .timer    = GTIMB3,      \
        .tim_irqn = GTIMB3_IRQn, \
        .name     = "pulse14",   \
    }
#endif /* PULSE_ENCODER14_CONFIG */
#endif /* BSP_USING_PULSE_ENCODER14 */

#ifdef __cplusplus
}
#endif

#endif /* __PULSE_ENCODER_CONFIG_H__ */
