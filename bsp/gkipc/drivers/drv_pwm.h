/*
 * Copyright (c) 2006-2018, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 *  Visit http://www.goke.com to get contact with Goke.
 *
 * Change Logs:
 * Date           Author       Notes
 */

#ifndef PWM_H_
#define PWM_H_

#include <rtthread.h>
#include <rtdef.h>

#define ENABLE_PWM (0x10)
#define DISABLE_PWM (0x11)

#define SET_PWM_DUTY_CYCLE (0x12)
#define GET_PWM_DUTY_CYCLE (0x13)

#define SET_PWM_VSYNC_MODE (0x14)
#define GET_PWM_VSYNC_MODE (0x15)

#define SET_PWM_CLOCK_DIV  (0x16)
#define SET_PWM_ACT_CHANNEL (0x17)

#define PWM_MAX_CHANNEL 8

struct pwm_param_vsync_mode
{
    rt_uint16_t speed;
    rt_uint32_t highLevelCnt;
    rt_uint32_t lowLevelCnt;
};

struct pwm_device
{
    rt_uint32_t freq;
    rt_uint32_t range;
    rt_uint32_t duty;
};

struct gk_pwm_obj
{
    int id;
    rt_uint32_t gpio_id;
};

struct pwm_driver
{
    struct gk_pwm_obj pwm[PWM_MAX_CHANNEL];
};

void rt_hw_pwm_init(void);

#endif /* PWM_H_ */
