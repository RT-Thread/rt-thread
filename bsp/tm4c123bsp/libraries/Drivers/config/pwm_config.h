/*
 * Copyright (c) 2006-2021, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2020-06-27     AHTYDHD      the first version
 */

#ifndef __PWM_CONFIG_H__
#define __PWM_CONFIG_H__

#ifdef __cplusplus
extern "C" {
#endif

#ifdef BSP_USING_PWM0
#ifndef PWM0_CONFIG
#define PWM0_CONFIG                                       \
    {                                                     \
        .name                    = "pwm0",                \
        .channel                 = 0     ,                \
        .counterMode             = PWM_GEN_MODE_UP_DOWN , \
        .syncMode                = PWM_GEN_MODE_NO_SYNC   \
    }
#endif /* PWM0_CONFIG */
#endif /* BSP_USING_PWM0 */

#ifdef BSP_USING_PWM1
#ifndef PWM1_CONFIG
#define PWM1_CONFIG                                       \
    {                                                     \
        .name                    = "pwm1",                \
        .channel                 = 0     ,                \
        .counterMode             = PWM_GEN_MODE_UP_DOWN , \
        .syncMode                = PWM_GEN_MODE_NO_SYNC   \
    }
#endif /* PWM1_CONFIG */
#endif /* BSP_USING_PWM1 */

#ifdef BSP_USING_PWM2
#ifndef PWM2_CONFIG
#define PWM2_CONFIG                                       \
    {                                                     \
        .name                    = "pwm2",                \
        .channel                 = 0     ,                \
        .counterMode             = PWM_GEN_MODE_UP_DOWN , \
        .syncMode                = PWM_GEN_MODE_NO_SYNC   \
    }
#endif /* PWM2_CONFIG */
#endif /* BSP_USING_PWM2 */

#ifdef BSP_USING_PWM3
#ifndef PWM3_CONFIG
#define PWM3_CONFIG                                       \
    {                                                     \
        .name                    = "pwm3",                \
        .channel                 = 0     ,                \
        .counterMode             = PWM_GEN_MODE_UP_DOWN , \
        .syncMode                = PWM_GEN_MODE_NO_SYNC   \
    }
#endif /* PWM3_CONFIG */
#endif /* BSP_USING_PWM3 */

#ifdef BSP_USING_PWM4
#ifndef PWM4_CONFIG
#define PWM4_CONFIG                                       \
    {                                                     \
        .name                    = "pwm4",                \
        .channel                 = 0     ,                \
        .counterMode             = PWM_GEN_MODE_UP_DOWN , \
        .syncMode                = PWM_GEN_MODE_NO_SYNC   \
    }
#endif /* PWM4_CONFIG */
#endif /* BSP_USING_PWM4 */

#ifdef BSP_USING_PWM5
#ifndef PWM5_CONFIG
#define PWM5_CONFIG                                       \
    {                                                     \
        .name                    = "pwm5",                \
        .channel                 = 0     ,                \
        .counterMode             = PWM_GEN_MODE_UP_DOWN , \
        .syncMode                = PWM_GEN_MODE_NO_SYNC   \
    }
#endif /* PWM5_CONFIG */
#endif /* BSP_USING_PWM5 */

#ifdef BSP_USING_PWM6
#ifndef PWM6_CONFIG
#define PWM6_CONFIG                                       \
    {                                                     \
        .name                    = "pwm6",                \
        .channel                 = 0    ,                 \
        .counterMode             = PWM_GEN_MODE_UP_DOWN , \
        .syncMode                = PWM_GEN_MODE_NO_SYNC   \
    }
#endif /* PWM6_CONFIG */
#endif /* BSP_USING_PWM6 */

#ifdef BSP_USING_PWM7
#ifndef PWM7_CONFIG
#define PWM7_CONFIG                                       \
    {                                                     \
        .name                    = "pwm7",                \
        .channel                 = 0     ,                \
        .counterMode             = PWM_GEN_MODE_UP_DOWN , \
        .syncMode                = PWM_GEN_MODE_NO_SYNC   \
    }
#endif /* PWM7_CONFIG */
#endif /* BSP_USING_PWM7 */

#ifdef __cplusplus
}
#endif

#endif /*__PWM_CONFIG_H__*/

/************************** end of file ******************/
