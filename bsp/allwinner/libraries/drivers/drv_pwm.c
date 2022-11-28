/*
 * Copyright (c) 2006-2022, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author           Notes
 * 2021-12-13     JasonHu          the first version
 */

#include <rtthread.h>
#include <rtdevice.h>

#include <sunxi_hal_pwm.h>

#define PWM_CHANNEL_MAX     (8) /* 0-7*/

#if defined(RT_USING_PWM) && defined(BSP_USING_PWM)

struct rt_hal_pwm
{
    struct rt_device_pwm parent;

    rt_uint32_t period[PWM_CHANNEL_MAX];
    rt_uint32_t pulse[PWM_CHANNEL_MAX];
    rt_uint32_t status;
};

static struct rt_hal_pwm _hal_pwm_device;
static struct rt_pwm_configuration configuration = {1, 100000, 100000, RT_TRUE};

static rt_err_t set(struct rt_device_pwm *device, struct rt_pwm_configuration *configuration)
{
    struct rt_hal_pwm *hal_pwm_device = (struct rt_hal_pwm *)device;

    LOG_D("drv_pwm.c set channel %d: period: %d, pulse: %d\n", configuration->channel, configuration->period, configuration->pulse);

    hal_pwm_device->period[configuration->channel] = configuration->period;
    hal_pwm_device->pulse[configuration->channel] = configuration->pulse;

    return RT_EOK;
}

static rt_err_t get(struct rt_device_pwm *device, struct rt_pwm_configuration *configuration)
{
    struct rt_hal_pwm *hal_pwm_device = (struct rt_hal_pwm *)device;

    configuration->period = hal_pwm_device->period[configuration->channel];
    configuration->pulse = hal_pwm_device->pulse[configuration->channel];
    LOG_D("drv_pwm.c get channel %d: period: %d, pulse: %d\n", configuration->channel, configuration->period, configuration->pulse);

    return RT_EOK;
}

static rt_err_t control(struct rt_device_pwm *device, int cmd, void *arg)
{
    rt_err_t result = RT_EOK;
    struct rt_pwm_configuration * configuration = (struct rt_pwm_configuration *)arg;

    struct rt_hal_pwm *hal_pwm_device = (struct rt_hal_pwm *)device;

    LOG_D("drv_pwm.c control cmd: %d. \n", cmd);

    if (configuration->channel > (PWM_CHANNEL_MAX - 1))
    {
        LOG_E("drv_pwm.c control channel: %d not support! \n", configuration->channel);
        return -RT_EIO;
    }

    LOG_D("PWM: channel:%d", configuration->channel);

    if (cmd == PWM_CMD_ENABLE)
    {
        LOG_D("PWM_CMD_ENABLE");
        struct pwm_config pwm_cfg;
        pwm_cfg.polarity = PWM_POLARITY_NORMAL;
        pwm_cfg.duty_ns =  hal_pwm_device->pulse[configuration->channel];
        pwm_cfg.period_ns = hal_pwm_device->period[configuration->channel];
        hal_pwm_device->status = 1;
        if (hal_pwm_control(configuration->channel, &pwm_cfg) != 0)
        {
            result = -RT_EIO;
        }
    }
    else if (cmd == PWM_CMD_DISABLE)
    {
        LOG_D("PWM_CMD_DISABLE");
        struct pwm_config pwm_cfg;
        pwm_cfg.polarity = PWM_POLARITY_NORMAL;
        pwm_cfg.duty_ns =  0; /* set as 0 for no duty */
        pwm_cfg.period_ns = hal_pwm_device->period[configuration->channel];
        hal_pwm_device->status = 0;
        if (hal_pwm_control(configuration->channel, &pwm_cfg) != 0)
        {
            result = -RT_EIO;
        }
        else
        {
            hal_pwm_disable_controller(configuration->channel);
        }
    }
    else if (cmd == PWM_CMD_SET)
    {
        LOG_D("PWM_CMD_SET");
        result = set(device, (struct rt_pwm_configuration *)arg);
        if(hal_pwm_device->status)
        {
            struct pwm_config pwm_cfg;
            pwm_cfg.polarity = PWM_POLARITY_NORMAL;
            pwm_cfg.duty_ns =  hal_pwm_device->pulse[configuration->channel];
            pwm_cfg.period_ns = hal_pwm_device->period[configuration->channel];
            if (hal_pwm_control(configuration->channel, &pwm_cfg) != 0)
            {
                result = -RT_EIO;
            }
        }
    }
    else if (cmd == PWM_CMD_GET)
    {
        LOG_D("PWM_CMD_GET");
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
    /* add pwm initial. */
    if (hal_pwm_init() != 0)
    {
        LOG_E("init pwm failed!");
        return -1;
    }
    _hal_pwm_device.status = 0;
    return rt_device_pwm_register(&_hal_pwm_device.parent, "pwm", &pwm_ops, RT_NULL);
}
INIT_DEVICE_EXPORT(rt_hw_pwm_init);

#endif /* RT_USING_PWM && BSP_USING_PWM */
