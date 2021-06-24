/*
 * Copyright (c) 2006-2021, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2018-05-07     aozima       the first version
 * 2021-06-24     wangqiang    add pwm interrupt callback
 */

#ifndef __DRV_PWM_H_INCLUDE__
#define __DRV_PWM_H_INCLUDE__

#include <rtthread.h>
#include <rtdevice.h>

#define PWM_CMD_ENABLE          (128 + 0)
#define PWM_CMD_DISABLE         (128 + 1)
#define PWM_CMD_SET             (128 + 2)
#define PWM_CMD_GET             (128 + 3)
#define PWMN_CMD_ENABLE         (128 + 4)
#define PWMN_CMD_DISABLE        (128 + 5)
#define PWM_CMD_INT_REGISTER    (128 + 6)       /* Command for regist interrupt */

struct rt_pwm_configuration
{
    rt_uint32_t channel; /* 0-n */
    rt_uint32_t period;  /* unit:ns 1ns~4.29s:1Ghz~0.23hz */
    rt_uint32_t pulse;   /* unit:ns (pulse<=period) */

    /*
     * RT_TRUE  : The channel of pwm is complememtary.
     * RT_FALSE : The channel of pwm is nomal.
    */
    rt_bool_t  complementary;

    #ifdef RT_USING_PWM_INT
    /* interrupt callback */
    void (*int_callback)(void);
    #endif
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

#ifdef RT_USING_PWM_INT
/**
 * This function will register interrupt callback function to driver
 *
 * @param device pwm device handle
 * @param channel pwm device channel
 * @param action callback function for pwm interrupt
 *
 * @return RT_EOK
 */
rt_err_t rt_pwm_interrupt(struct rt_device_pwm *device, int channel, void (*action)(void));
#endif

#endif /* __DRV_PWM_H_INCLUDE__ */
