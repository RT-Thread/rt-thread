/*
 * Copyright (c) 2020-2021, Bluetrum Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author            Notes
 * 2021-01-28     greedyhao         first version
 */

#ifndef __PWM_CONFIG_H__
#define __PWM_CONFIG_H__

#include <rtthread.h>

#ifdef __cplusplus
extern "C" {
#endif

enum
{
    PWMxCON,
    PWMxPR,
    PWMxxDUT,
    PWMyyDUT,
    PWMxCYCNUM,
    PWMxSTEP,
};

#define PWM_BASE    ((hal_sfr_t)&PWMCON)

#ifdef BSP_USING_T3_PWM
#ifndef T3_PWM_CONFIG
#define T3_PWM_CONFIG                         \
    {                                       \
       .pwm_handle          = TIM3_BASE,    \
       .name                = "t3pwm",       \
       .channel             = 0             \
    }
#endif /* T3_PWM_CONFIG */
#endif /* BSP_USING_T3_PWM */

#ifdef BSP_USING_T4_PWM
#ifndef T4_PWM_CONFIG
#define T4_PWM_CONFIG                         \
    {                                       \
       .pwm_handle          = TIM4_BASE,    \
       .name                = "t4pwm",       \
       .channel             = 0             \
    }
#endif /* T4_PWM_CONFIG */
#endif /* BSP_USING_T4_PWM */

#ifdef BSP_USING_T5_PWM
#ifndef T5_PWM_CONFIG
#define T5_PWM_CONFIG                         \
    {                                       \
       .pwm_handle          = TIM5_BASE,    \
       .name                = "t5pwm",       \
       .channel             = 0             \
    }
#endif /* T5_PWM_CONFIG */
#endif /* BSP_USING_T5_PWM */

#ifdef BSP_USING_LPWM0
#ifndef LPWM0_CONFIG
#define LPWM0_CONFIG                        \
    {                                       \
       .pwm_handle          = PWM_BASE,     \
       .name                = "lpwm0",      \
       .channel             = 0             \
    }
#endif /* LPWM0_CONFIG */
#endif /* BSP_USING_LPWM0 */

#ifdef BSP_USING_LPWM1
#ifndef LPWM1_CONFIG
#define LPWM1_CONFIG                        \
    {                                       \
       .pwm_handle          = PWM_BASE,     \
       .name                = "lpwm1",      \
       .channel             = 0             \
    }
#endif /* LPWM1_CONFIG */
#endif /* BSP_USING_LPWM1 */

#ifdef BSP_USING_LPWM2
#ifndef LPWM2_CONFIG
#define LPWM2_CONFIG                        \
    {                                       \
       .pwm_handle          = PWM_BASE,     \
       .name                = "lpwm2",      \
       .channel             = 0             \
    }
#endif /* LPWM2_CONFIG */
#endif /* BSP_USING_LPWM2 */

#ifdef BSP_USING_LPWM3
#ifndef LPWM3_CONFIG
#define LPWM3_CONFIG                        \
    {                                       \
       .pwm_handle          = PWM_BASE,     \
       .name                = "lpwm3",      \
       .channel             = 0             \
    }
#endif /* LPWM3_CONFIG */
#endif /* BSP_USING_LPWM3 */

#ifdef __cplusplus
}
#endif

#endif /* __PWM_CONFIG_H__ */
