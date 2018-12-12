/*
 * Copyright (c) 2006-2018, Synwit Technology Co.,Ltd.
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2018-12-10     Zohar_Lee    first version
 */

#include <rthw.h>
#include <rtthread.h>
#include <rtdevice.h>
#include <board.h>

#define SWM320_PWM_DEVICE(pwm) (struct swm320_pwm_dev *)(pwm)

struct swm320_pwm_dev
{
    struct rt_device_pwm parent;
    rt_uint32_t pwm_periph;
};

static rt_err_t swm320_pwm_control(struct rt_device_pwm *device,
                                   int cmd,
                                   void *arg);

const static struct rt_pwm_ops pwm_ops = {swm320_pwm_control};
struct rt_device_pwm swm320_device_pwm0;
struct rt_device_pwm swm320_device_pwm1;
struct rt_device_pwm swm320_device_pwm2;
struct rt_device_pwm swm320_device_pwm3;

static rt_err_t swm320_pwm_control(struct rt_device_pwm *device,
                                   int cmd,
                                   void *arg)
{
    struct rt_pwm_configuration configuration = {0};
    struct rt_device *dev = &device->parent;

    RT_ASSERT(device)

    configuration = *(struct rt_pwm_configuration *)arg;

    switch (cmd)
    {
    case PWM_CMD_ENABLE:
        if (2 == configuration.channel)
        {
            PWM_Start(dev->user_data, 1, 1);
        }
        if (1 == configuration.channel)
        {
            PWM_Start(dev->user_data, 0, 1);
        }
        if (0 == configuration.channel)
        {
            PWM_Start(dev->user_data, 1, 0);
        }
        if (3 == configuration.channel)
        {
            PWM_Start(dev->user_data, 0, 0);
        }
        break;
    case PWM_CMD_DISABLE:
        if (2 == configuration.channel)
        {
            PWM_Stop(dev->user_data, 1, 1);
        }
        if (1 == configuration.channel)
        {
            PWM_Stop(dev->user_data, 0, 1);
        }
        if (0 == configuration.channel)
        {
            PWM_Stop(dev->user_data, 1, 0);
        }
        if (3 == configuration.channel)
        {
            PWM_Stop(dev->user_data, 0, 0);
        }
        break;
    case PWM_CMD_SET:
        PWM_SetHDuty(dev->user_data, configuration.channel, configuration.pulse);
        PWM_SetCycle(dev->user_data, configuration.channel, configuration.period);
        break;
    case PWM_CMD_GET:
        configuration.pulse = PWM_GetHDuty(dev->user_data, configuration.channel);
        break;
    default:
        break;
    }

    return RT_EOK;
}

static int pwm_register(PWM_TypeDef *PWMx, const char *name)
{
    struct rt_device_pwm *device_pwm;
    const struct rt_pwm_ops *ops = &pwm_ops;
    void *user_data = NULL;
    PWM_InitStructure PWM_initStruct;

    PWM_initStruct.clk_div = PWM_CLKDIV_8; /* F_PWM = 20M/8 = 2.5M */
    PWM_initStruct.mode = PWM_MODE_INDEP;  /* A路和B路独立输出 */
    PWM_initStruct.cycleA = 10000;         /* 2.5M/10000 = 250Hz */
    PWM_initStruct.hdutyA = 2500;          /* 2500/10000 = 25% */
    PWM_initStruct.initLevelA = 1;
    PWM_initStruct.cycleB = 10000;
    PWM_initStruct.hdutyB = 5000; /* 5000/10000 = 50% */
    PWM_initStruct.initLevelB = 1;
    PWM_initStruct.HEndAIEn = 0;
    PWM_initStruct.NCycleAIEn = 0;
    PWM_initStruct.HEndBIEn = 0;
    PWM_initStruct.NCycleBIEn = 0;

    if (PWMx == PWM0)
    {
        PWM_Init(PWM0, &PWM_initStruct);
        PORT_Init(PORTA, PIN4, FUNMUX0_PWM0A_OUT, 0);
        PORT_Init(PORTA, PIN10, FUNMUX0_PWM0B_OUT, 0);
        user_data = PWM0;
        device_pwm = &swm320_device_pwm0;
    }
    else if (PWMx == PWM1)
    {
        PWM_Init(PWM1, &PWM_initStruct);
        PORT_Init(PORTA, PIN5, FUNMUX1_PWM1A_OUT, 0);
        PORT_Init(PORTA, PIN9, FUNMUX1_PWM1B_OUT, 0);
        user_data = PWM1;
        device_pwm = &swm320_device_pwm1;
    }
    else if (PWMx == PWM2)
    {
        PWM_Init(PWM2, &PWM_initStruct);
        PORT_Init(PORTP, PIN0, FUNMUX0_PWM2A_OUT, 0);
        PORT_Init(PORTP, PIN2, FUNMUX0_PWM2B_OUT, 0);
        user_data = PWM2;
        device_pwm = &swm320_device_pwm2;
    }
    else if (PWMx == PWM3)
    {
        PWM_Init(PWM3, &PWM_initStruct);
        PORT_Init(PORTP, PIN1, FUNMUX1_PWM3A_OUT, 0);
        PORT_Init(PORTP, PIN3, FUNMUX1_PWM3B_OUT, 0);
        user_data = PWM3;
        device_pwm = &swm320_device_pwm3;
    }
    else
    {
        return -1;
    }

    return rt_device_pwm_register(device_pwm, name,
                                  (struct rt_pwm_ops *)ops,
                                  user_data);
}

int rt_hw_pwm_init(void)
{
    int result = 0;
#ifdef BSP_USING_PWM0
    result = pwm_register(PWM0, "pwm0");
#endif

#ifdef BSP_USING_PWM1
    result = pwm_register(PWM1, "pwm1");
#endif

#ifdef BSP_USING_PWM2
    result = pwm_register(PWM2, "pwm2");
#endif

#ifdef BSP_USING_PWM3
    result = pwm_register(PWM3, "pwm3");
#endif

    return result;
}
INIT_DEVICE_EXPORT(rt_hw_pwm_init);
