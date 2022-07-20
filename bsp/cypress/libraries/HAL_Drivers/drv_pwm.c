/*
 * Copyright (c) 2006-2022, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2022-07-13     Rbb666       first version
 */
#include "drv_pwm.h"

#ifdef RT_USING_PWM

#include <drivers/rt_drv_pwm.h>
#include "drv_gpio.h"

//#define DRV_DEBUG
#define LOG_TAG             "drv.pwm"
#include <drv_log.h>

struct rt_device_pwm pwm_device;

struct ifx_pwm
{
    struct rt_device_pwm pwm_device;
    cyhal_pwm_t *pwm_obj;
    rt_uint8_t channel;
    char *name;
    rt_uint8_t gpio;
};

enum
{
#ifdef BSP_USING_PWM0
    PWM0_INDEX,
#endif
};

static struct ifx_pwm ifx_pwm_obj[] =
{
#ifdef BSP_USING_PWM0
    PWM0_CONFIG,
#endif
};

static void pwm_get_pin_number(void)
{
#ifdef BSP_USING_PWM0_CH7
#ifdef BSP_USING_PWM0_PORT2
    ifx_pwm_obj[PWM0_INDEX].gpio = GET_PIN(2, 2);
#endif
#ifdef BSP_USING_PWM0_PORT5
    ifx_pwm_obj[PWM0_INDEX].gpio = GET_PIN(5, 6);
#endif
#ifdef BSP_USING_PWM0_PORT7
    ifx_pwm_obj[PWM0_INDEX].gpio = GET_PIN(7, 7);
#endif
#ifdef BSP_USING_PWM0_PORT9
    ifx_pwm_obj[PWM0_INDEX].gpio = GET_PIN(9, 4);
#endif
#ifdef BSP_USING_PWM0_PORT10
    ifx_pwm_obj[PWM0_INDEX].gpio = GET_PIN(10, 2);
#endif
#ifdef BSP_USING_PWM0_PORT12
    ifx_pwm_obj[PWM0_INDEX].gpio = GET_PIN(12, 6);
#endif
#endif
}

static void pwm_get_channel(void)
{
#ifdef BSP_USING_PWM0_CH7
    ifx_pwm_obj[PWM0_INDEX].channel = 7;
#endif
}

static rt_err_t drv_pwm_enable(cyhal_pwm_t *htim, struct rt_pwm_configuration *configuration, rt_bool_t enable)
{
    /* get the value of channel */
    rt_uint32_t channel = configuration->channel;

    if (!configuration->complementary || configuration->complementary)
    {
        if (!enable)
        {
            if (channel == 7)
            {
                cyhal_pwm_stop(htim);
            }
        }
        else
        {
            if (channel == 7)
            {
                cyhal_pwm_start(htim);
            }
        }
    }

    return RT_EOK;
}

static rt_err_t drv_pwm_set(cyhal_pwm_t *htim, struct rt_pwm_configuration *configuration)
{
    rt_uint64_t tim_clock;
    rt_uint32_t period, pulse;

    tim_clock = (rt_uint32_t)(htim->tcpwm.clock_hz);

    period = (unsigned long long)configuration->period / 1000ULL;

    pulse = (unsigned long long)configuration->pulse / 1000ULL;

    cyhal_pwm_set_period(htim, period, pulse);

    return RT_EOK;
}

static rt_err_t drv_pwm_get(cyhal_pwm_t *htim, struct rt_pwm_configuration *configuration)
{
    uint32_t Period = Cy_TCPWM_PWM_GetPeriod0(htim->tcpwm.base, _CYHAL_TCPWM_CNT_NUMBER(htim->tcpwm.resource));

    uint32_t Compare = Cy_TCPWM_PWM_GetCounter(htim->tcpwm.base, _CYHAL_TCPWM_CNT_NUMBER(htim->tcpwm.resource));

    configuration->period = Period;

    configuration->pulse = Compare;

    return RT_EOK;
}

static rt_err_t drv_pwm_control(struct rt_device_pwm *device, int cmd, void *arg)
{
    struct rt_pwm_configuration *configuration = (struct rt_pwm_configuration *)arg;
    cyhal_pwm_t *htim = (cyhal_pwm_t *)device->parent.user_data;

    switch (cmd)
    {
    case PWMN_CMD_ENABLE:
        configuration->complementary = RT_TRUE;
    case PWM_CMD_ENABLE:
        return drv_pwm_enable(htim, configuration, RT_TRUE);
    case PWMN_CMD_DISABLE:
        configuration->complementary = RT_FALSE;
    case PWM_CMD_DISABLE:
        return drv_pwm_enable(htim, configuration, RT_FALSE);
    case PWM_CMD_SET:
        return drv_pwm_set(htim, configuration);
    case PWM_CMD_GET:
        return drv_pwm_get(htim, configuration);
    default:
        return RT_EINVAL;
    }
}

static struct rt_pwm_ops drv_ops =
{
    drv_pwm_control
};

static rt_err_t ifx_hw_pwm_init(struct ifx_pwm *device)
{
    rt_err_t result = RT_EOK;

    RT_ASSERT(device != RT_NULL);

    /* config pwm channel */
    if (device->channel == 0x07)
    {
        if (cyhal_pwm_init_adv(device->pwm_obj, device->gpio, NC, CYHAL_PWM_LEFT_ALIGN, true, 0u, false, RT_NULL) != RT_EOK)
        {
            LOG_E("%s channel7 config failed", device->name);
            result = -RT_ERROR;
            goto __exit;
        }
    }

__exit:
    return result;
}

static int rt_hw_pwm_init(void)
{
    int i;
    int result = RT_EOK;

    pwm_get_pin_number();
    pwm_get_channel();

    for (i = 0; i < sizeof(ifx_pwm_obj) / sizeof(ifx_pwm_obj[0]); i++)
    {
        ifx_pwm_obj[i].pwm_obj = rt_malloc(sizeof(cyhal_pwm_t));
        RT_ASSERT(ifx_pwm_obj[i].pwm_obj != RT_NULL);

        /* pwm init */
        if (ifx_hw_pwm_init(&ifx_pwm_obj[i]) != RT_EOK)
        {
            LOG_E("%s init failed", ifx_pwm_obj[i].name);
            result = -RT_ERROR;
            goto __exit;
        }
        else
        {
            if (rt_device_pwm_register(&ifx_pwm_obj[i].pwm_device, ifx_pwm_obj[i].name, &drv_ops, ifx_pwm_obj[i].pwm_obj) == RT_EOK)
            {
                LOG_D("%s register success", ifx_pwm_obj[i].name);
            }
            else
            {
                LOG_D("%s register failed", ifx_pwm_obj[i].name);
                result = -RT_ERROR;
            }
        }
    }

__exit:
    return result;
}
INIT_BOARD_EXPORT(rt_hw_pwm_init);

#define PWM_DEV_NAME        "pwm0"
#define PWM_DEV_CHANNEL     7

struct rt_device_pwm *pwm_dev;

static int pwm_sample(int argc, char *argv[])
{
    rt_uint32_t period, pulse, dir;

    period = 500000;
    dir = 1;
    pulse = 0;

    pwm_dev = (struct rt_device_pwm *)rt_device_find(PWM_DEV_NAME);
    if (pwm_dev == RT_NULL)
    {
        rt_kprintf("pwm sample run failed! can't find %s device!\n", PWM_DEV_NAME);
        return RT_ERROR;
    }

    rt_pwm_set(pwm_dev, PWM_DEV_CHANNEL, period, pulse);
    rt_pwm_enable(pwm_dev, PWM_DEV_CHANNEL);

    while (1)
    {
        rt_thread_mdelay(50);

        if (dir)
        {
            pulse += 5000;
        }
        else
        {
            pulse -= 5000;
        }
        if (pulse >= period)
        {
            dir = 0;
        }
        if (0 == pulse)
        {
            dir = 1;
        }

        rt_pwm_set(pwm_dev, PWM_DEV_CHANNEL, period, pulse);
    }
}
MSH_CMD_EXPORT(pwm_sample, <pwm0> channel7 sample);
#endif
