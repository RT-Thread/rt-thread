/*
 * Copyright (c) 2006-2021, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2017-12-04     Haley        the first version
 */

#ifndef __PWM_H_
#define __PWM_H_

#include <rtthread.h>

/**
 * @brief External function definitions
 *
 */
int rt_hw_pwm_init(void);
void am_pwm_start(int led);
void am_pwm_stop(int led);

#endif // __PWM_H_
