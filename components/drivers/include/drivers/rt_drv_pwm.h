/*
 * Copyright (c) 2006-2021, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2018-05-07     aozima       the first version
 */

#ifndef __DRV_PWM_H_INCLUDE__
#define __DRV_PWM_H_INCLUDE__

#include <rtthread.h>

#define PWM_CMD_ENABLE      (RT_DEVICE_CTRL_BASE(PWM) + 0)
#define PWM_CMD_DISABLE     (RT_DEVICE_CTRL_BASE(PWM) + 1)
#define PWM_CMD_SET         (RT_DEVICE_CTRL_BASE(PWM) + 2)
#define PWM_CMD_GET         (RT_DEVICE_CTRL_BASE(PWM) + 3)
#define PWMN_CMD_ENABLE     (RT_DEVICE_CTRL_BASE(PWM) + 4)
#define PWMN_CMD_DISABLE    (RT_DEVICE_CTRL_BASE(PWM) + 5)
#define PWM_CMD_SET_PERIOD  (RT_DEVICE_CTRL_BASE(PWM) + 6)
#define PWM_CMD_SET_PULSE   (RT_DEVICE_CTRL_BASE(PWM) + 7)

struct rt_pwm_configuration
{
    rt_uint32_t channel; /* 1-n or 0-n, which depends on specific MCU requirements */
    rt_uint32_t period;  /* unit:ns 1ns~4.29s:1Ghz~0.23hz */
    rt_uint32_t pulse;   /* unit:ns (pulse<=period) */

    /*
     * RT_TRUE  : The channel of pwm is complememtary.
     * RT_FALSE : The channel of pwm is nomal.
    */
    rt_bool_t  complementary;
};

struct rt_device_pwm;
struct rt_pwm_ops
{
    rt_err_t (*control)(struct rt_device_pwm *device, int cmd, void *arg);
};

struct rt_device_pwm
{
    struct rt_device parent;
    const struct rt_pwm_ops *ops;
};

rt_err_t rt_device_pwm_register(struct rt_device_pwm *device, const char *name, const struct rt_pwm_ops *ops, const void *user_data);

rt_err_t rt_pwm_enable(struct rt_device_pwm *device, int channel);
rt_err_t rt_pwm_disable(struct rt_device_pwm *device, int channel);
rt_err_t rt_pwm_set(struct rt_device_pwm *device, int channel, rt_uint32_t period, rt_uint32_t pulse);
rt_err_t rt_pwm_set_period(struct rt_device_pwm *device, int channel, rt_uint32_t period);
rt_err_t rt_pwm_set_pulse(struct rt_device_pwm *device, int channel, rt_uint32_t pulse);

#endif /* __DRV_PWM_H_INCLUDE__ */
