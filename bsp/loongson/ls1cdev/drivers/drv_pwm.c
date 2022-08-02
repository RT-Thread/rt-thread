/*
 * Copyright (c) 2006-2022, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author           Notes
 * 2018-12-04     Sundm75        the first version
 */
#include <stdint.h>
#include <string.h>
#include <stdlib.h>

#include <rtthread.h>
#include <rtdevice.h>

#include "ls1c.h"
#include "../libraries/ls1c_public.h"
#include "../libraries/ls1c_regs.h"
#include "../libraries/ls1c_clock.h"
#include "../libraries/ls1c_pwm.h"
#include "../libraries/ls1c_pin.h"

#define PWM_CHANNEL_MAX     (4) /* 0-3*/

#ifdef RT_USING_PWM

struct rt_ls1c_pwm
{
    struct rt_device_pwm parent;

    rt_uint32_t period[PWM_CHANNEL_MAX];
    rt_uint32_t pulse[PWM_CHANNEL_MAX];
};

static struct rt_ls1c_pwm _ls1c_pwm_device;

static rt_err_t set(struct rt_device_pwm *device, struct rt_pwm_configuration *configuration)
{
    rt_err_t result = RT_EOK;
    struct rt_ls1c_pwm *ls1c_pwm_device = (struct rt_ls1c_pwm *)device;

    if (configuration->channel > (PWM_CHANNEL_MAX - 1))
    {
        result = -RT_EIO;
        goto _exit;
    }

    rt_kprintf("drv_pwm.c set channel %d: period: %d, pulse: %d\n", configuration->channel, configuration->period, configuration->pulse);

    ls1c_pwm_device->period[configuration->channel] = configuration->period;
    ls1c_pwm_device->pulse[configuration->channel] = configuration->pulse;

_exit:
    return result;
}

static rt_err_t get(struct rt_device_pwm *device, struct rt_pwm_configuration *configuration)
{
    rt_err_t result = RT_EOK;
    struct rt_ls1c_pwm *ls1c_pwm_device = (struct rt_ls1c_pwm *)device;

    if (configuration->channel > (PWM_CHANNEL_MAX - 1))
    {
        result = -RT_EIO;
        goto _exit;
    }

    configuration->period = ls1c_pwm_device->period[configuration->channel];
    configuration->pulse = ls1c_pwm_device->pulse[configuration->channel];
    rt_kprintf("drv_pwm.c get channel %d: period: %d, pulse: %d\n", configuration->channel, configuration->period, configuration->pulse);

_exit:
    return result;
}

static rt_err_t control(struct rt_device_pwm *device, int cmd, void *arg)
{
     rt_err_t result = RT_EOK;
    struct rt_pwm_configuration * configuration = (struct rt_pwm_configuration *)arg;

    rt_kprintf("drv_pwm.c control cmd: %d. \n", cmd);

    if (cmd == PWM_CMD_ENABLE)
    {
        rt_kprintf("PWM_CMD_ENABLE\n");

        pwm_info_t pwm_info;
        switch ( configuration->channel)
        {
        case 0:
            pwm_info.gpio = LS1C_PWM0_GPIO06;
            //pwm_info.gpio = LS1C_PWM0_GPIO04;
            break;
        case 1:
            pwm_info.gpio = LS1C_PWM1_GPIO92;
            //pwm_info.gpio = LS1C_PWM1_GPIO05;
            break;
        case 2:
            pwm_info.gpio = LS1C_PWM2_GPIO52;
            //pwm_info.gpio = LS1C_PWM2_GPIO46;
            break;
        case 3:
            pwm_info.gpio = LS1C_PWM3_GPIO47;
            //pwm_info.gpio = LS1C_PWM3_GPIO53;
            break;
        default:
            break;
        }
        pwm_info.mode = PWM_MODE_NORMAL;
        pwm_info.duty =  ( (float)configuration->pulse ) / ((float)configuration->period );
        pwm_info.period_ns = configuration->period;
        pwm_init(&pwm_info);
        pwm_enable(&pwm_info);
    }
    else if (cmd == PWM_CMD_DISABLE)
    {
        rt_kprintf("PWM_CMD_DISABLE\n");
        pwm_info_t pwm_info;
        switch ( configuration->channel)
        {
        case 0:
            pwm_info.gpio = LS1C_PWM0_GPIO06;
            //pwm_info.gpio = LS1C_PWM0_GPIO04;
            break;
        case 1:
            pwm_info.gpio = LS1C_PWM1_GPIO92;
            //pwm_info.gpio = LS1C_PWM1_GPIO05;
            break;
        case 2:
            pwm_info.gpio = LS1C_PWM2_GPIO52;
            //pwm_info.gpio = LS1C_PWM2_GPIO46;
            break;
        case 3:
            pwm_info.gpio = LS1C_PWM3_GPIO47;
            //pwm_info.gpio = LS1C_PWM3_GPIO53;
            break;
        default:
            break;
        }
        pwm_info.mode = PWM_MODE_NORMAL;
        pwm_info.duty =  ( (float)configuration->pulse ) / ((float)configuration->period );
        pwm_info.period_ns = configuration->period;
        pwm_init(&pwm_info);
        pwm_disable(&pwm_info);
    }
    else if (cmd == PWM_CMD_SET)
    {
        rt_kprintf("PWM_CMD_SET\n");
        result = set(device, (struct rt_pwm_configuration *)arg);
    }
    else if (cmd == PWM_CMD_GET)
    {
        rt_kprintf("PWM_CMD_GET\n");
        result = get(device, (struct rt_pwm_configuration *)arg);
    }

    return result;
}

static const struct rt_pwm_ops pwm_ops =
{
    control,
};

int rt_hw_pwm_init(void)
{
    int ret = RT_EOK;

    /* add pwm initial. */

    ret = rt_device_pwm_register(&_ls1c_pwm_device.parent, "pwm", &pwm_ops, RT_NULL);

    return ret;
}
INIT_DEVICE_EXPORT(rt_hw_pwm_init);

#endif /*RT_USING_PWM*/
