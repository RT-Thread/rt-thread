/*
 * Copyright (c) 2006-2018, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 */
 
#ifndef PWM_H_
#define PWM_H_


#include <rtthread.h>
#define ENABLE_PWM                  (0x10)
#define DISABLE_PWM                 (0x11)

#define SET_PWM_DUTY_CYCLE          (0x12)
#define GET_PWM_DUTY_CYCLE          (0x13)

struct pwm_device
{
    int id;
    int working;
    rt_uint32_t period_ns;
    rt_uint32_t counter_ns;
};

struct pwm_driver
{
    //struct clk          *clk;
    struct pwm_device   pwm[3];
    struct pwm_device   *cur;
    void*  priv;

};



#endif /* PWM_H_ */
