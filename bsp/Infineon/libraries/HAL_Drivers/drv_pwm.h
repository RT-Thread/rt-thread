/*
 * Copyright (c) 2006-2023, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2022-07-13     Rbb666       first version
 */

#ifndef __PWM_CONFIG_H__
#define __PWM_CONFIG_H__

#include <rtthread.h>
#include <board.h>

#ifdef __cplusplus
extern "C"
{
#endif

#define MAX_PERIOD 65535

#ifdef BSP_USING_PWM0
#ifndef PWM0_CH0_PORT0_CONFIG
#define PWM0_CH0_PORT0_CONFIG       \
    {                               \
        .name = "pwm0",             \
        .channel = 0,               \
        .gpio = GET_PIN(0, 0),      \
    }
#endif /* PWM0_CH0_PORT2_CONFIG */

#ifndef PWM0_CH2_PORT11_COMPL_CONFIG
#define PWM0_CH2_PORT11_COMPL_CONFIG \
    {                                \
        .name = "pwm0",              \
        .channel = 2,                \
        .gpio = GET_PIN(11, 3),      \
    }
#endif /*PWM0_CH2_PORT11_COMPL_CONFIG*/

#ifndef PWM0_CH3_PORT11_CONFIG
#define PWM0_CH3_PORT11_CONFIG      \
    {                               \
        .name = "pwm0",             \
        .channel = 3,               \
        .gpio = GET_PIN(11, 4),     \
    }
#endif /*PWM0_CH3_PORT11_CONFIG*/

#ifndef PWM0_CH4_PORT5_COMPL_CONFIG
#define PWM0_CH4_PORT5_COMPL_CONFIG \
    {                               \
        .name = "pwm0",             \
        .channel = 4,               \
        .gpio = GET_PIN(5, 1),      \
    }
#endif /*PWM0_CH4_PORT5_COMPL_CONFIG*/

#ifndef PWM0_CH7_PORT2_CONFIG
#define PWM0_CH7_PORT2_CONFIG       \
    {                               \
        .name = "pwm0",             \
        .channel = 7,               \
        .gpio = GET_PIN(2, 2),      \
    }
#endif /* PWM0_CH7_PORT2_CONFIG */

#ifndef PWM0_CH7_PORT5_CONFIG
#define PWM0_CH7_PORT5_CONFIG       \
    {                               \
        .name = "pwm0",             \
        .channel = 7,               \
        .gpio = GET_PIN(5, 6),      \
    }
#endif /* PWM0_CH7_PORT5_CONFIG */

#ifndef PWM0_CH7_PORT5_COMPL_CONFIG
#define PWM0_CH7_PORT5_COMPL_CONFIG \
    {                               \
        .name = "pwm0",             \
        .channel = 7,               \
        .gpio = GET_PIN(5, 7),      \
    }
#endif /*PWM0_CH7_PORT5_COMPL_CONFIG*/

#ifndef PWM0_CH7_PORT7_CONFIG
#define PWM0_CH7_PORT7_CONFIG       \
    {                               \
        .name = "pwm0",             \
        .channel = 7,               \
        .gpio = GET_PIN(7, 7),      \
    }
#endif /* PWM0_CH7_PORT7_CONFIG */

#ifndef PWM0_CH7_PORT9_CONFIG
#define PWM0_CH7_PORT9_CONFIG       \
    {                               \
        .name = "pwm0",             \
        .channel = 7,               \
        .gpio = GET_PIN(9, 4),      \
    }
#endif /* PWM0_CH7_PORT9_CONFIG */

#ifndef PWM0_CH7_PORT10_CONFIG
#define PWM0_CH7_PORT10_CONFIG      \
    {                               \
        .name = "pwm0",             \
        .channel = 7,               \
        .gpio = GET_PIN(10, 2),     \
    }
#endif /* PWM0_CH7_PORT10_CONFIG */

#ifndef PWM0_CH7_PORT12_CONFIG
#define PWM0_CH7_PORT12_CONFIG      \
    {                               \
        .name = "pwm0",             \
        .channel = 7,               \
        .gpio = GET_PIN(12, 6),     \
    }
#endif /* PWM0_CH7_PORT12_CONFIG */

#ifndef PWM0_CH3_PORT13_CONFIG
#define PWM0_CH3_PORT13_CONFIG      \
    {                               \
        .name = "pwm0",             \
        .channel = 3,               \
        .gpio = GET_PIN(13, 7),     \
    }
#endif /* PWM0_CH3_PORT13_CONFIG */
#endif /* BSP_USING_PWM0 */

#ifdef __cplusplus
}
#endif

#endif
