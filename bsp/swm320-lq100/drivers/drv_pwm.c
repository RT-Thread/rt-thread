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

#define SWM320_PWM_TIMER_SET(time) ((time) / 1000.0 * 120)

struct swm320_pwm_dev
{
    struct rt_device_pwm parent;
    PWM_TypeDef *pwm_periph;
};

static rt_err_t swm320_pwm_enable(void *user_data,
                                  struct rt_pwm_configuration *cfg,
                                  rt_bool_t enable)
{
    rt_err_t ret = RT_EOK;

    if (RT_TRUE == enable)
    {
        if (2 == cfg->channel)
        {
            PWM_Start((PWM_TypeDef *)user_data, 1, 1);
        }
        if (1 == cfg->channel)
        {
            PWM_Start((PWM_TypeDef *)user_data, 0, 1);
        }
        if (0 == cfg->channel)
        {
            PWM_Start((PWM_TypeDef *)user_data, 1, 0);
        }
        if (3 == cfg->channel)
        {
            PWM_Start((PWM_TypeDef *)user_data, 0, 0);
        }
    }
    else if (RT_FALSE == enable)
    {
        if (2 == cfg->channel)
        {
            PWM_Stop((PWM_TypeDef *)user_data, 1, 1);
        }
        if (1 == cfg->channel)
        {
            PWM_Stop((PWM_TypeDef *)user_data, 0, 1);
        }
        if (0 == cfg->channel)
        {
            PWM_Stop((PWM_TypeDef *)user_data, 1, 0);
        }
        if (3 == cfg->channel)
        {
            PWM_Stop((PWM_TypeDef *)user_data, 0, 0);
        }
    }
    else
    {
        ret = RT_ERROR;
    }

    return ret;
}

static rt_err_t swm320_pwm_control(struct rt_device_pwm *device,
                                   int cmd,
                                   void *arg)
{
    rt_err_t ret = RT_EOK;
    struct swm320_pwm_dev *pwm = SWM320_PWM_DEVICE(device->parent.user_data);
    struct rt_pwm_configuration *cfg = (struct rt_pwm_configuration *)arg;

    RT_ASSERT(pwm != RT_NULL);

    switch (cmd)
    {
    case PWM_CMD_ENABLE:

        ret = swm320_pwm_enable((void *)pwm->pwm_periph, cfg, RT_TRUE);
        break;
    case PWM_CMD_DISABLE:

        ret = swm320_pwm_enable((void *)pwm->pwm_periph, cfg, RT_FALSE);
        break;
    case PWM_CMD_SET:
        PWM_SetHDuty(pwm->pwm_periph,
                     cfg->channel,
                     SWM320_PWM_TIMER_SET(cfg->pulse));
        PWM_SetCycle(pwm->pwm_periph,
                     cfg->channel,
                     SWM320_PWM_TIMER_SET(cfg->period));
        break;
    case PWM_CMD_GET:
        cfg->pulse = PWM_GetHDuty(pwm->pwm_periph, cfg->channel);
        break;
    default:
        break;
    }

    return ret;
}

const static struct rt_pwm_ops swm320_pwm_ops =
{
    swm320_pwm_control
};

int rt_hw_pwm_init(void)
{
    rt_err_t ret = RT_EOK;
    PWM_InitStructure PWM_initStruct;

    PWM_initStruct.clk_div = PWM_CLKDIV_1; /* F_PWM = 120M/1 = 120M */
    PWM_initStruct.mode = PWM_MODE_INDEP;  /* A路和B路独立输出 */
    PWM_initStruct.cycleA = SWM320_PWM_TIMER_SET(1000);
    PWM_initStruct.hdutyA = SWM320_PWM_TIMER_SET(500);
    PWM_initStruct.initLevelA = 1;
    PWM_initStruct.cycleB = SWM320_PWM_TIMER_SET(1000);
    PWM_initStruct.hdutyB = SWM320_PWM_TIMER_SET(250);
    PWM_initStruct.initLevelB = 1;
    PWM_initStruct.HEndAIEn = 0;
    PWM_initStruct.NCycleAIEn = 0;
    PWM_initStruct.HEndBIEn = 0;
    PWM_initStruct.NCycleBIEn = 0;

#ifdef BSP_USING_PWM0
    static struct swm320_pwm_dev pwm_dev0;
    pwm_dev0.pwm_periph = PWM0;
    PWM_Init(pwm_dev0.pwm_periph, &PWM_initStruct);
    PORT_Init(PORTA, PIN4, FUNMUX0_PWM0A_OUT, 0);
    PORT_Init(PORTA, PIN10, FUNMUX0_PWM0B_OUT, 0);
    ret = rt_device_pwm_register(&pwm_dev0.parent,
                                 "pwm0",
                                 &swm320_pwm_ops,
                                 &pwm_dev0);

#endif

#ifdef BSP_USING_PWM1
    static struct swm320_pwm_dev pwm_dev1;
    pwm_dev1.pwm_periph = PWM1;
    PWM_Init(pwm_dev1.pwm_periph, &PWM_initStruct);
    PORT_Init(PORTA, PIN5, FUNMUX1_PWM1A_OUT, 0);
    PORT_Init(PORTA, PIN9, FUNMUX1_PWM1B_OUT, 0);
    ret = rt_device_pwm_register(&pwm_dev1.parent,
                                 "pwm1",
                                 &swm320_pwm_ops,
                                 &pwm_dev1);
#endif

#ifdef BSP_USING_PWM2
    static struct swm320_pwm_dev pwm_dev2;
    pwm_dev2.pwm_periph = PWM2;
    PWM_Init(pwm_dev2.pwm_periph, &PWM_initStruct);
    PORT_Init(PORTP, PIN0, FUNMUX0_PWM2A_OUT, 0);
    PORT_Init(PORTP, PIN2, FUNMUX0_PWM2B_OUT, 0);
    ret = rt_device_pwm_register(&pwm_dev2.parent,
                                 "pwm2",
                                 &swm320_pwm_ops,
                                 &pwm_dev2);
#endif

#ifdef BSP_USING_PWM3
    static struct swm320_pwm_dev pwm_dev3;
    pwm_dev3.pwm_periph = PWM3;
    PWM_Init(pwm_dev3.pwm_periph, &PWM_initStruct);
    PORT_Init(PORTP, PIN1, FUNMUX1_PWM3A_OUT, 0);
    PORT_Init(PORTP, PIN3, FUNMUX1_PWM3B_OUT, 0);
    ret = rt_device_pwm_register(&pwm_dev3.parent,
                                 "pwm3",
                                 &swm320_pwm_ops,
                                 &pwm_dev3);
#endif

    return ret;
}
INIT_DEVICE_EXPORT(rt_hw_pwm_init);
