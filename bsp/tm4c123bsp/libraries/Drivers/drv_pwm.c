/*
 * Copyright (c) 2006-2021, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2020-06-27     AHTYDHD      the first version
 */

#include "drv_pwm.h"
#include <stdint.h>
#include <stdbool.h>
#include "inc/hw_memmap.h"
#include "driverlib/pwm.h"
#include "driverlib/sysctl.h"

#ifdef  RT_USING_PWM
#include "pwm_config.h"
#include "tm4c123_config.h"
#include <string.h>

#define LOG_TAG             "drv.pwm"
#include <drv_log.h>

enum
{
#ifdef BSP_USING_PWM0
    PWM0_INDEX,
#endif
#ifdef BSP_USING_PWM1
    PWM1_INDEX,
#endif
#ifdef BSP_USING_PWM2
    PWM2_INDEX,
#endif
#ifdef BSP_USING_PWM3
    PWM3_INDEX,
#endif
#ifdef BSP_USING_PWM4
    PWM4_INDEX,
#endif
#ifdef BSP_USING_PWM5
    PWM5_INDEX,
#endif
#ifdef BSP_USING_PWM6
    PWM6_INDEX,
#endif
#ifdef BSP_USING_PWM7
    PWM7_INDEX,
#endif
};

static struct tm4c123_pwm_config pwm_config[] =
{
#ifdef BSP_USING_PWM0
    PWM0_CONFIG,
#endif
#ifdef BSP_USING_PWM1
    PWM1_CONFIG,
#endif
#ifdef BSP_USING_PWM2
    PWM2_CONFIG,
#endif
#ifdef BSP_USING_PWM3
    PWM3_CONFIG,
#endif
#ifdef BSP_USING_PWM4
    PWM4_CONFIG,
#endif
#ifdef BSP_USING_PWM5
    PWM5_CONFIG,
#endif
#ifdef BSP_USING_PWM6
    PWM6_CONFIG,
#endif
#ifdef BSP_USING_PWM7
    PWM7_CONFIG,
#endif
};

static struct tm4c123_pwm pwm_obj[sizeof(pwm_config) / sizeof(pwm_config[0])] = {0};

static rt_err_t tm4c123_pwm_control(struct rt_device_pwm *device, int cmd, void *arg);
static struct rt_pwm_ops drv_ops =
{
    tm4c123_pwm_control
};

static rt_err_t drv_pwm_enable(char *name, struct rt_pwm_configuration *configuration, rt_bool_t enable)
{

    int  num = name[3] - 0x30;

    if (!enable)
    {
        if (num <= 3)
        {
            /* Converts the channel number to the channel number of Hal library */
            PWMOutputState(PWM0_BASE, PWM_OUT_0_BIT << (num * 2 + (configuration->channel - 1)), false);
        }
        else
        {
            PWMOutputState(PWM1_BASE, PWM_OUT_0_BIT << ((num % 4) * 2 + (configuration->channel - 1)), false);
        }
    }
    else
    {
        if (num <= 3)
        {
            PWMOutputState(PWM0_BASE, PWM_OUT_0_BIT << (num * 2 + (configuration->channel - 1)), true);
        }
        else
        {
            PWMOutputState(PWM1_BASE, PWM_OUT_0_BIT << ((num % 4) * 2 + (configuration->channel - 1)), true);
        }
    }

    return RT_EOK;
}

static rt_err_t drv_pwm_get(char *name, struct rt_pwm_configuration *configuration)
{

    switch (name[3])
    {
    case  '0':
        configuration->period = PWMGenPeriodGet(PWM0_BASE, PWM_GEN_0);
        configuration->pulse = PWMPulseWidthGet(PWM0_BASE, PWM_OUT_0 + (uint32_t)(configuration->channel - 1));
        break;
    case  '1':
        configuration->period = PWMGenPeriodGet(PWM0_BASE, PWM_GEN_1);
        configuration->pulse = PWMPulseWidthGet(PWM0_BASE, PWM_OUT_2 + (uint32_t)(configuration->channel - 1));
        break;
    case  '2':
        configuration->period = PWMGenPeriodGet(PWM0_BASE, PWM_GEN_2);
        configuration->pulse = PWMPulseWidthGet(PWM0_BASE, PWM_OUT_4 + (uint32_t)(configuration->channel - 1));
        break;
    case  '3':
        configuration->period = PWMGenPeriodGet(PWM0_BASE, PWM_GEN_3);
        configuration->pulse = PWMPulseWidthGet(PWM0_BASE, PWM_OUT_6 + (uint32_t)(configuration->channel - 1));
        break;
    case  '4':
        configuration->period = PWMGenPeriodGet(PWM1_BASE, PWM_GEN_0);
        configuration->pulse = PWMPulseWidthGet(PWM1_BASE, PWM_OUT_0 + (uint32_t)(configuration->channel - 1));
        break;
    case  '5':
        configuration->period = PWMGenPeriodGet(PWM1_BASE, PWM_GEN_1);
        configuration->pulse = PWMPulseWidthGet(PWM1_BASE, PWM_OUT_2 + (uint32_t)(configuration->channel - 1));
        break;
    case  '6':
        configuration->period = PWMGenPeriodGet(PWM1_BASE, PWM_GEN_2);
        configuration->pulse = PWMPulseWidthGet(PWM1_BASE, PWM_OUT_4 + (uint32_t)(configuration->channel - 1));
        break;
    case  '7':
        configuration->period = PWMGenPeriodGet(PWM1_BASE, PWM_GEN_3);
        configuration->pulse = PWMPulseWidthGet(PWM1_BASE, PWM_OUT_6 + (uint32_t)(configuration->channel - 1));
        break;
    default:
        break;
    }
    return RT_EOK;
}

static rt_err_t drv_pwm_set(char *name, struct rt_pwm_configuration *configuration)
{

    uint32_t  sysPwmClock = SysCtlPWMClockGet();
    switch (name[3])
    {
    case  '0':
        PWMGenPeriodSet(PWM0_BASE, PWM_GEN_0, configuration->period / 1000 * (sysPwmClock / 1000000)); // t(s)/(1/f) = ticks   ns/1000/1000000
        PWMPulseWidthSet(PWM0_BASE, PWM_OUT_0 + (uint32_t)(configuration->channel - 1), configuration->pulse / 1000 * (sysPwmClock / 1000000));
        PWMGenEnable(PWM0_BASE, PWM_GEN_0);
        break;
    case  '1':
        PWMGenPeriodSet(PWM0_BASE, PWM_GEN_1, configuration->period / 1000 * (sysPwmClock / 1000000));
        PWMPulseWidthSet(PWM0_BASE, PWM_OUT_0 + (uint32_t)(configuration->channel - 1), configuration->pulse / 1000 * (sysPwmClock / 1000000));
        PWMGenEnable(PWM0_BASE, PWM_GEN_1);
        break;
    case  '2':
        PWMGenPeriodSet(PWM0_BASE, PWM_GEN_2, configuration->period / 1000 * (sysPwmClock / 1000000));
        PWMPulseWidthSet(PWM0_BASE, PWM_OUT_0 + (uint32_t)(configuration->channel - 1), configuration->pulse / 1000 * (sysPwmClock / 1000000));
        PWMGenEnable(PWM0_BASE, PWM_GEN_2);
        break;
    case  '3':
        PWMGenPeriodSet(PWM0_BASE, PWM_GEN_3, configuration->period / 1000 * (sysPwmClock / 1000000));
        PWMPulseWidthSet(PWM0_BASE, PWM_OUT_0 + (uint32_t)(configuration->channel - 1), configuration->pulse / 1000 * (sysPwmClock / 1000000));
        PWMGenEnable(PWM0_BASE, PWM_GEN_3);
        break;
    case  '4':
        PWMGenPeriodSet(PWM1_BASE, PWM_GEN_0, configuration->period / 1000 * (sysPwmClock / 1000000));
        PWMPulseWidthSet(PWM1_BASE, PWM_OUT_0 + (uint32_t)(configuration->channel - 1), configuration->pulse / 1000 * (sysPwmClock / 1000000));
        PWMGenEnable(PWM1_BASE, PWM_GEN_0);
        break;
    case  '5':
        PWMGenPeriodSet(PWM1_BASE, PWM_GEN_1, configuration->period / 1000 * (sysPwmClock / 1000000));
        PWMPulseWidthSet(PWM1_BASE, PWM_OUT_2 + (uint32_t)(configuration->channel - 1), configuration->pulse / 1000 * (sysPwmClock / 1000000));
        PWMGenEnable(PWM1_BASE, PWM_GEN_1);
        break;
    case  '6':
        PWMGenPeriodSet(PWM1_BASE, PWM_GEN_2, configuration->period / 1000 * (sysPwmClock / 1000000));
        PWMPulseWidthSet(PWM1_BASE, PWM_OUT_4 + (uint32_t)(configuration->channel - 1), configuration->pulse / 1000 * (sysPwmClock / 1000000));
        PWMGenEnable(PWM1_BASE, PWM_GEN_2);
        break;
    case  '7':
        PWMGenPeriodSet(PWM1_BASE, PWM_GEN_3, configuration->period / 1000 * (sysPwmClock / 1000000));
        PWMPulseWidthSet(PWM1_BASE, PWM_OUT_6 + (uint32_t)(configuration->channel - 1), configuration->pulse / 1000 * (sysPwmClock / 1000000));
        PWMGenEnable(PWM1_BASE, PWM_GEN_3);
        break;
    default:
        break;
    }

    return RT_EOK;
}

static rt_err_t tm4c123_pwm_control(struct rt_device_pwm *device, int cmd, void *arg)

{
    struct rt_pwm_configuration *configuration = (struct rt_pwm_configuration *)arg;

    switch (cmd)
    {
    case PWM_CMD_ENABLE:
        return drv_pwm_enable(device->parent.parent.name, configuration, RT_TRUE);
    case PWM_CMD_DISABLE:
        return drv_pwm_enable(device->parent.parent.name, configuration, RT_FALSE);
    case PWM_CMD_SET:
        return drv_pwm_set(device->parent.parent.name, configuration);
    case PWM_CMD_GET:
        return drv_pwm_get(device->parent.parent.name, configuration);
    default:
        return RT_EINVAL;
    }
}

static rt_err_t tm4c123_hw_pwm_init(struct tm4c123_pwm *device)
{
    rt_err_t result = RT_EOK;
    RT_ASSERT(device != RT_NULL);

    pwm_hw_config();
    switch (device->config->name[3])
    {
    case  '0':
        PWMGenConfigure(PWM0_BASE, PWM_GEN_0, device->config->counterMode |
                        device->config->syncMode);
        break;
    case  '1':
        PWMGenConfigure(PWM0_BASE, PWM_GEN_1, device->config->counterMode |
                        device->config->syncMode);
        break;
    case  '2':
        PWMGenConfigure(PWM0_BASE, PWM_GEN_2, device->config->counterMode |
                        device->config->syncMode);
        break;
    case  '3':
        PWMGenConfigure(PWM0_BASE, PWM_GEN_3, device->config->counterMode |
                        device->config->syncMode);
        break;
    case  '4':
        PWMGenConfigure(PWM1_BASE, PWM_GEN_0, device->config->counterMode |
                        device->config->syncMode);
        break;
    case  '5':
        PWMGenConfigure(PWM1_BASE, PWM_GEN_1, device->config->counterMode |
                        device->config->syncMode);
        break;
    case  '6':
        PWMGenConfigure(PWM1_BASE, PWM_GEN_2, device->config->counterMode |
                        device->config->syncMode);
        break;
    case  '7':
        PWMGenConfigure(PWM1_BASE, PWM_GEN_3, device->config->counterMode |
                        device->config->syncMode);
        break;
    default:
        LOG_E("%s PWMGenConfigure failed", device->config->name);
        result = -RT_ERROR;
        return result;
    }

    return result;
}

int rt_hw_pwm_init(void)
{
    int i = 0;
    rt_size_t obj_num = sizeof(pwm_obj) / sizeof(struct tm4c123_pwm);
    rt_err_t result = RT_EOK;

    for (i = 0 ; i < obj_num; i++)
    {
        pwm_obj[i].config = &pwm_config[i];
        pwm_obj[i].pwm_device.ops = &drv_ops;
        /*pwm_init*/
        if (tm4c123_hw_pwm_init(&pwm_obj[i]) != RT_EOK)
        {
            LOG_E("%s init failed", pwm_obj[i].config->name);
            result = -RT_ERROR;
            return result;
        }
        else
        {
            LOG_D("%s init success", pwm_obj[i].config->name);

            /* register pwm device */
            if (rt_device_pwm_register(&pwm_obj[i].pwm_device, pwm_obj[i].config->name, &drv_ops, RT_NULL) == RT_EOK)
            {
                LOG_D("%s register success", pwm_obj[i].config->name);
            }
            else
            {
                LOG_E("%s register failed", pwm_obj[i].config->name);
                result = -RT_ERROR;
            }
        }
    }
    return result;
}

#endif /* RT_USING_PWM */

/************************** end of file ******************/
