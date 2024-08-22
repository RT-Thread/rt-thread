/*
 * Copyright (c) 2006-2023, RT-Thread Development Team
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
#define LOG_TAG "drv.pwm"
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

static struct ifx_pwm ifx_pwm_obj[] =
{
#ifdef BSP_USING_PWM0_CH0_PORT0
    PWM0_CH0_PORT0_CONFIG,
#endif

#ifdef BSP_USING_PWM0_CH2_PORT11_COMPL
    PWM0_CH2_PORT11_COMPL_CONFIG,
#endif

#ifdef BSP_USING_PWM0_CH3_PORT11
    PWM0_CH3_PORT11_CONFIG,
#endif

#ifdef BSP_USING_PWM0_CH4_PORT5_COMPL
    PWM0_CH4_PORT5_COMPL_CONFIG,
#endif

#ifdef BSP_USING_PWM0_CH7_PORT2
    PWM0_CH7_PORT2_CONFIG,
#endif

#ifdef BSP_USING_PWM0_CH7_PORT5
    PWM0_CH7_PORT5_CONFIG,
#endif

#ifdef BSP_USING_PWM0_CH7_PORT5_COMPL
    PWM0_CH7_PORT5_COMPL_CONFIG,
#endif

#ifdef BSP_USING_PWM0_CH7_PORT7
    PWM0_CH7_PORT7_CONFIG,
#endif

#ifdef BSP_USING_PWM0_CH7_PORT9
    PWM0_CH7_PORT9_CONFIG,
#endif

#ifdef BSP_USING_PWM0_CH7_PORT10
    PWM0_CH7_PORT10_CONFIG,
#endif

#ifdef BSP_USING_PWM0_CH7_PORT12
    PWM0_CH7_PORT12_CONFIG,
#endif

#ifdef BSP_USING_PWM0_CH7_PORT13
    PWM0_CH3_PORT13_CONFIG,
#endif
};

static rt_err_t drv_pwm_enable(cyhal_pwm_t *htim, struct rt_pwm_configuration *configuration, rt_bool_t enable)
{
    /* get the value of channel */
    rt_uint32_t channel = configuration->channel;

    if (!configuration->complementary || configuration->complementary)
    {
        if (!enable)
        {
						htim->tcpwm.resource.channel_num = channel;
            cyhal_pwm_stop(htim);
        }
        else
        {
						htim->tcpwm.resource.channel_num = channel;
            cyhal_pwm_start(htim);
        }
    }

    return RT_EOK;
}

static rt_err_t drv_pwm_set(cyhal_pwm_t *htim, struct rt_pwm_configuration *configuration)
{
    rt_uint64_t tim_clock;
    rt_uint32_t period, pulse;

    tim_clock = (rt_uint32_t)(htim->tcpwm.clock_hz);

    htim->tcpwm.resource.channel_num = configuration->channel;

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
        return -RT_EINVAL;
    }
}

static struct rt_pwm_ops drv_ops = {drv_pwm_control};

static rt_err_t ifx_hw_pwm_init(struct ifx_pwm *device)
{
    rt_err_t result = RT_EOK;

    RT_ASSERT(device != RT_NULL);

    if (cyhal_pwm_init_adv(device->pwm_obj, device->gpio, NC, CYHAL_PWM_LEFT_ALIGN, true, 0u, false, RT_NULL) != RT_EOK)
    {
        LOG_E("%s channel%d config failed", device->name, device->channel);
        result = -RT_ERROR;
        goto __exit;
    }

__exit:
    return result;
}

static int rt_hw_pwm_init(void)
{
    int i;
    int result = RT_EOK;

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

#define PWM_DEV_NAME "pwm0"
#define PWM_DEV_CHANNEL 4

struct rt_device_pwm *pwm_dev;

static int pwm_sample(int argc, char *argv[])
{
    rt_uint32_t period, pulse, dir;

    period = 1 * 1000 * 1000;
    dir = 1;
    pulse = 0;

    pwm_dev = (struct rt_device_pwm *)rt_device_find(PWM_DEV_NAME);

    if (pwm_dev == RT_NULL)
    {
        rt_kprintf("pwm sample run failed! can't find %s device!\n", PWM_DEV_NAME);
        return -RT_ERROR;
    }

    rt_pwm_set(pwm_dev, PWM_DEV_CHANNEL, period, pulse);
    rt_pwm_enable(pwm_dev, PWM_DEV_CHANNEL);

    rt_kprintf("Now PWM[%s] Channel[%d] Period[%d] Pulse[%d]\n", PWM_DEV_NAME, PWM_DEV_CHANNEL, period, pulse);

    while (1)
    {
        rt_thread_mdelay(50);

        if (dir)
        {
            pulse += 100000;
        }
        else
        {
            pulse -= 100000;
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
