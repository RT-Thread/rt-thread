/*
 * Copyright (c) 2006-2022, RT-Thread Development Team
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
#include <board.h>

#ifdef __cplusplus
extern "C" {
#endif

#define MAX_PERIOD                      65535

#ifdef BSP_USING_PWM0
#ifndef PWM0_CONFIG
#define PWM0_CONFIG                             \
    {                                           \
        .name                    = "pwm0",       \
                                   .channel                 = 0,            \
                                           .gpio                    = 0,            \
    }
#endif /* PWM0_CONFIG */
#endif /* BSP_USING_PWM0 */

#ifdef __cplusplus
}
#endif

#endif
