/*
 * Copyright (c) 2006-2021, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2022-03-10     leo          first version
 */

#ifndef __PWM_CONFIG_H__
#define __PWM_CONFIG_H__

#include <rtthread.h>

#ifdef __cplusplus
extern "C" {
#endif

#ifdef BSP_USING_PWM1
#ifndef PWM1_CONFIG
#define PWM1_CONFIG                             \
    {                                           \
       .tmr_x                   = TMR1,         \
       .name                    = "pwm1",       \
       .channel                 = 0             \
    }
#endif /* PWM1_CONFIG */
#endif /* BSP_USING_PWM1 */

#ifdef BSP_USING_PWM2
#ifndef PWM2_CONFIG
#define PWM2_CONFIG                             \
    {                                           \
       .tmr_x                   = TMR2,         \
       .name                    = "pwm2",       \
       .channel                 = 0             \
    }
#endif /* PWM2_CONFIG */
#endif /* BSP_USING_PWM2 */

#ifdef BSP_USING_PWM3
#ifndef PWM3_CONFIG
#define PWM3_CONFIG                             \
    {                                           \
       .tmr_x                   = TMR3,         \
       .name                    = "pwm3",       \
       .channel                 = 0             \
    }
#endif /* PWM3_CONFIG */
#endif /* BSP_USING_PWM3 */

#ifdef BSP_USING_PWM4
#ifndef PWM4_CONFIG
#define PWM4_CONFIG                             \
    {                                           \
       .tmr_x                   = TMR4,         \
       .name                    = "pwm4",       \
       .channel                 = 0             \
    }
#endif /* PWM4_CONFIG */
#endif /* BSP_USING_PWM4 */

#ifdef BSP_USING_PWM5
#ifndef PWM5_CONFIG
#define PWM5_CONFIG                             \
    {                                           \
       .tmr_x                   = TMR5,         \
       .name                    = "pwm5",       \
       .channel                 = 0             \
    }
#endif /* PWM5_CONFIG */
#endif /* BSP_USING_PWM5 */

#ifdef BSP_USING_PWM6
#ifndef PWM6_CONFIG
#define PWM6_CONFIG                             \
    {                                           \
       .tmr_x                   = TMR6,         \
       .name                    = "pwm6",       \
       .channel                 = 0             \
    }
#endif /* PWM6_CONFIG */
#endif /* BSP_USING_PWM6 */

#ifdef BSP_USING_PWM7
#ifndef PWM7_CONFIG
#define PWM7_CONFIG                             \
    {                                           \
       .tmr_x                   = TMR7,         \
       .name                    = "pwm7",       \
       .channel                 = 0             \
    }
#endif /* PWM7_CONFIG */
#endif /* BSP_USING_PWM7 */

#ifdef BSP_USING_PWM8
#ifndef PWM8_CONFIG
#define PWM8_CONFIG                             \
    {                                           \
       .tmr_x                   = TMR8,         \
       .name                    = "pwm8",       \
       .channel                 = 12             \
    }
#endif /* PWM8_CONFIG */
#endif /* BSP_USING_PWM8 */

#ifdef BSP_USING_PWM9
#ifndef PWM9_CONFIG
#define PWM9_CONFIG                             \
    {                                           \
       .tmr_x                   = TMR9,         \
       .name                    = "pwm9",       \
       .channel                 = 0             \
    }
#endif /* PWM9_CONFIG */
#endif /* BSP_USING_PWM9 */

#ifdef BSP_USING_PWM10
#ifndef PWM10_CONFIG
#define PWM10_CONFIG                             \
    {                                           \
       .tmr_x                   = TMR10,         \
       .name                    = "pwm10",       \
       .channel                 = 0             \
    }
#endif /* PWM10_CONFIG */
#endif /* BSP_USING_PWM10 */

#ifdef BSP_USING_PWM11
#ifndef PWM11_CONFIG
#define PWM11_CONFIG                             \
    {                                           \
       .tmr_x                   = TMR11,         \
       .name                    = "pwm11",       \
       .channel                 = 0             \
    }
#endif /* PWM11_CONFIG */
#endif /* BSP_USING_PWM11 */

#ifdef BSP_USING_PWM12
#ifndef PWM12_CONFIG
#define PWM12_CONFIG                             \
    {                                           \
       .tmr_x                   = TMR12,         \
       .name                    = "pwm12",       \
       .channel                 = 0             \
    }
#endif /* PWM12_CONFIG */
#endif /* BSP_USING_PWM12 */

#ifdef BSP_USING_PWM13
#ifndef PWM13_CONFIG
#define PWM13_CONFIG                             \
    {                                           \
       .tmr_x                   = TMR13,         \
       .name                    = "pwm13",       \
       .channel                 = 0             \
    }
#endif /* PWM13_CONFIG */
#endif /* BSP_USING_PWM13 */

#ifdef __cplusplus
}
#endif

#endif /* __PWM_CONFIG_H__ */
