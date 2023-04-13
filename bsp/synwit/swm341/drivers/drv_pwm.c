/*
 * Copyright (c) 2006-2022, Synwit Technology Co.,Ltd.
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2021-07-01     lik          first version
 */

#include "drv_pwm.h"

#ifdef RT_USING_PWM
#ifdef BSP_USING_PWM

//#define DRV_DEBUG
#define LOG_TAG "drv.pwm"
#include <drv_log.h>

#if !defined(BSP_USING_PWM0) && !defined(BSP_USING_PWM1) && !defined(BSP_USING_PWM2) && !defined(BSP_USING_PWM3) && !defined(BSP_USING_PWM4)
#error "Please define at least one BSP_USING_PWMx"
/* this driver can be disabled at menuconfig ? RT-Thread Components ? Device Drivers */
#endif

#define MIN_PERIOD 2
#define MIN_PULSE 1

#ifdef BSP_USING_PWM0
#ifndef PWM0_CFG
#define PWM0_CFG                                   \
    {                                              \
        .name = "pwm0",                            \
        .PWMx = PWM0,                              \
        .pwm_initstruct.Mode = PWM_CENTER_ALIGNED, \
        .pwm_initstruct.Clkdiv = 15,               \
        .pwm_initstruct.Period = 10000,            \
        .pwm_initstruct.HdutyA = 5000,             \
        .pwm_initstruct.DeadzoneA = 0,             \
        .pwm_initstruct.IdleLevelA = 0,            \
        .pwm_initstruct.IdleLevelAN = 0,           \
        .pwm_initstruct.OutputInvA = 0,            \
        .pwm_initstruct.OutputInvAN = 1,           \
        .pwm_initstruct.HdutyB = 5000,             \
        .pwm_initstruct.DeadzoneB = 0,             \
        .pwm_initstruct.IdleLevelB = 0,            \
        .pwm_initstruct.IdleLevelBN = 0,           \
        .pwm_initstruct.OutputInvB = 0,            \
        .pwm_initstruct.OutputInvBN = 1,           \
        .pwm_initstruct.UpOvfIE = 0,               \
        .pwm_initstruct.DownOvfIE = 0,             \
        .pwm_initstruct.UpCmpAIE = 0,              \
        .pwm_initstruct.DownCmpAIE = 0,            \
        .pwm_initstruct.UpCmpBIE = 0,              \
        .pwm_initstruct.DownCmpBIE = 0,            \
        .pwm_mask = PWM0_MSK,                      \
    }
#endif /* PWM0_CFG */
#endif /* BSP_USING_PWM0 */

#ifdef BSP_USING_PWM1
#ifndef PWM1_CFG
#define PWM1_CFG                                   \
    {                                              \
        .name = "pwm1",                            \
        .PWMx = PWM1,                              \
        .pwm_initstruct.Mode = PWM_CENTER_ALIGNED, \
        .pwm_initstruct.Clkdiv = 15,               \
        .pwm_initstruct.Period = 10000,            \
        .pwm_initstruct.HdutyA = 5000,             \
        .pwm_initstruct.DeadzoneA = 0,             \
        .pwm_initstruct.IdleLevelA = 0,            \
        .pwm_initstruct.IdleLevelAN = 0,           \
        .pwm_initstruct.OutputInvA = 0,            \
        .pwm_initstruct.OutputInvAN = 1,           \
        .pwm_initstruct.HdutyB = 5000,             \
        .pwm_initstruct.DeadzoneB = 0,             \
        .pwm_initstruct.IdleLevelB = 0,            \
        .pwm_initstruct.IdleLevelBN = 0,           \
        .pwm_initstruct.OutputInvB = 0,            \
        .pwm_initstruct.OutputInvBN = 1,           \
        .pwm_initstruct.UpOvfIE = 0,               \
        .pwm_initstruct.DownOvfIE = 0,             \
        .pwm_initstruct.UpCmpAIE = 0,              \
        .pwm_initstruct.DownCmpAIE = 0,            \
        .pwm_initstruct.UpCmpBIE = 0,              \
        .pwm_initstruct.DownCmpBIE = 0,            \
        .pwm_mask = PWM1_MSK,                      \
    }
#endif /* PWM1_CFG */
#endif /* BSP_USING_PWM1 */

#ifdef BSP_USING_PWM2
#ifndef PWM2_CFG
#define PWM2_CFG                                   \
    {                                              \
        .name = "pwm2",                            \
        .PWMx = PWM2,                              \
        .pwm_initstruct.Mode = PWM_CENTER_ALIGNED, \
        .pwm_initstruct.Clkdiv = 15,               \
        .pwm_initstruct.Period = 10000,            \
        .pwm_initstruct.HdutyA = 5000,             \
        .pwm_initstruct.DeadzoneA = 0,             \
        .pwm_initstruct.IdleLevelA = 0,            \
        .pwm_initstruct.IdleLevelAN = 0,           \
        .pwm_initstruct.OutputInvA = 0,            \
        .pwm_initstruct.OutputInvAN = 1,           \
        .pwm_initstruct.HdutyB = 5000,             \
        .pwm_initstruct.DeadzoneB = 0,             \
        .pwm_initstruct.IdleLevelB = 0,            \
        .pwm_initstruct.IdleLevelBN = 0,           \
        .pwm_initstruct.OutputInvB = 0,            \
        .pwm_initstruct.OutputInvBN = 1,           \
        .pwm_initstruct.UpOvfIE = 0,               \
        .pwm_initstruct.DownOvfIE = 0,             \
        .pwm_initstruct.UpCmpAIE = 0,              \
        .pwm_initstruct.DownCmpAIE = 0,            \
        .pwm_initstruct.UpCmpBIE = 0,              \
        .pwm_initstruct.DownCmpBIE = 0,            \
        .pwm_mask = PWM2_MSK,                      \
    }
#endif /* PWM2_CFG */
#endif /* BSP_USING_PWM2 */

#ifdef BSP_USING_PWM3
#ifndef PWM3_CFG
#define PWM3_CFG                                   \
    {                                              \
        .name = "pwm3",                            \
        .PWMx = PWM3,                              \
        .pwm_initstruct.Mode = PWM_CENTER_ALIGNED, \
        .pwm_initstruct.Clkdiv = 15,               \
        .pwm_initstruct.Period = 10000,            \
        .pwm_initstruct.HdutyA = 5000,             \
        .pwm_initstruct.DeadzoneA = 0,             \
        .pwm_initstruct.IdleLevelA = 0,            \
        .pwm_initstruct.IdleLevelAN = 0,           \
        .pwm_initstruct.OutputInvA = 0,            \
        .pwm_initstruct.OutputInvAN = 1,           \
        .pwm_initstruct.HdutyB = 5000,             \
        .pwm_initstruct.DeadzoneB = 0,             \
        .pwm_initstruct.IdleLevelB = 0,            \
        .pwm_initstruct.IdleLevelBN = 0,           \
        .pwm_initstruct.OutputInvB = 0,            \
        .pwm_initstruct.OutputInvBN = 1,           \
        .pwm_initstruct.UpOvfIE = 0,               \
        .pwm_initstruct.DownOvfIE = 0,             \
        .pwm_initstruct.UpCmpAIE = 0,              \
        .pwm_initstruct.DownCmpAIE = 0,            \
        .pwm_initstruct.UpCmpBIE = 0,              \
        .pwm_initstruct.DownCmpBIE = 0,            \
        .pwm_mask = PWM3_MSK,                      \
    }
#endif /* PWM3_CFG */
#endif /* BSP_USING_PWM3 */

#ifdef BSP_USING_PWM4
#ifndef PWM4_CFG
#define PWM4_CFG                                   \
    {                                              \
        .name = "pwm4",                            \
        .PWMx = PWM4,                              \
        .pwm_initstruct.Mode = PWM_CENTER_ALIGNED, \
        .pwm_initstruct.Clkdiv = 15,               \
        .pwm_initstruct.Period = 10000,            \
        .pwm_initstruct.HdutyA = 5000,             \
        .pwm_initstruct.DeadzoneA = 0,             \
        .pwm_initstruct.IdleLevelA = 0,            \
        .pwm_initstruct.IdleLevelAN = 0,           \
        .pwm_initstruct.OutputInvA = 0,            \
        .pwm_initstruct.OutputInvAN = 1,           \
        .pwm_initstruct.HdutyB = 5000,             \
        .pwm_initstruct.DeadzoneB = 0,             \
        .pwm_initstruct.IdleLevelB = 0,            \
        .pwm_initstruct.IdleLevelBN = 0,           \
        .pwm_initstruct.OutputInvB = 0,            \
        .pwm_initstruct.OutputInvBN = 1,           \
        .pwm_initstruct.UpOvfIE = 0,               \
        .pwm_initstruct.DownOvfIE = 0,             \
        .pwm_initstruct.UpCmpAIE = 0,              \
        .pwm_initstruct.DownCmpAIE = 0,            \
        .pwm_initstruct.UpCmpBIE = 0,              \
        .pwm_initstruct.DownCmpBIE = 0,            \
        .pwm_mask = PWM4_MSK,                      \
    }
#endif /* PWM4_CFG */
#endif /* BSP_USING_PWM4 */

struct swm_pwm_cfg
{
    const char *name;
    PWM_TypeDef *PWMx;
    PWM_InitStructure pwm_initstruct;
    uint32_t pwm_mask;
};

struct swm_pwm_device
{
    struct swm_pwm_cfg *pwm_cfg;
    struct rt_device_pwm pwm_device;
};

static struct swm_pwm_cfg swm_pwm_cfg[] =
    {
#ifdef BSP_USING_PWM0
        PWM0_CFG,
#endif
#ifdef BSP_USING_PWM1
        PWM1_CFG,
#endif
#ifdef BSP_USING_PWM2
        PWM2_CFG,
#endif
#ifdef BSP_USING_PWM3
        PWM3_CFG,
#endif
#ifdef BSP_USING_PWM4
        PWM4_CFG,
#endif
};

static struct swm_pwm_device pwm_obj[sizeof(swm_pwm_cfg) / sizeof(swm_pwm_cfg[0])] = {0};

static rt_err_t swm_pwm_enable(struct rt_device_pwm *pwm_device, struct rt_pwm_configuration *configuration, rt_bool_t enable)
{
    struct swm_pwm_cfg *pwm_cfg = RT_NULL;
    RT_ASSERT(pwm_device != RT_NULL);
    pwm_cfg = pwm_device->parent.user_data;

    if (!enable)
    {
        PWM_Stop(pwm_cfg->pwm_mask);
    }
    else
    {
        PWM_Start(pwm_cfg->pwm_mask);
    }

    return RT_EOK;
}

static rt_err_t swm_pwm_get(struct rt_device_pwm *pwm_device, struct rt_pwm_configuration *configuration)
{
    rt_uint64_t tim_clock;

    struct swm_pwm_cfg *pwm_cfg = RT_NULL;
    RT_ASSERT(pwm_device != RT_NULL);
    pwm_cfg = pwm_device->parent.user_data;

    configuration->period = PWM_GetPeriod(pwm_cfg->PWMx) * 1000UL; //中心对称模式下频率降低一半
    configuration->pulse = PWM_GetHDuty(pwm_cfg->PWMx, configuration->channel) * 1000UL;

    return RT_EOK;
}

static rt_err_t swm_pwm_set(struct rt_device_pwm *pwm_device, struct rt_pwm_configuration *configuration)
{
    rt_uint32_t period, pulse;
    rt_uint64_t tim_clock;

    struct swm_pwm_cfg *pwm_cfg = RT_NULL;
    RT_ASSERT(pwm_device != RT_NULL);
    pwm_cfg = pwm_device->parent.user_data;

    period = (unsigned long long)configuration->period / 1000UL; //中心对称模式下频率降低一半
    pulse = (unsigned long long)configuration->pulse / 1000UL;
    if (period < MIN_PERIOD)
    {
        period = MIN_PERIOD;
    }
    if (pulse < MIN_PULSE)
    {
        pulse = MIN_PULSE;
    }
    PWM_SetPeriod(pwm_cfg->PWMx, period);
    PWM_SetHDuty(pwm_cfg->PWMx, PWM_CH_A, pulse);
    PWM_SetHDuty(pwm_cfg->PWMx, PWM_CH_B, pulse);

    return RT_EOK;
}

static rt_err_t swm_pwm_control(struct rt_device_pwm *pwm_device, int cmd, void *arg)
{
    RT_ASSERT(pwm_device != RT_NULL);

    struct rt_pwm_configuration *configuration = (struct rt_pwm_configuration *)arg;

    switch (cmd)
    {
    case PWM_CMD_ENABLE:
        return swm_pwm_enable(pwm_device, configuration, RT_TRUE);
    case PWM_CMD_DISABLE:
        return swm_pwm_enable(pwm_device, configuration, RT_FALSE);
    case PWM_CMD_SET:
        return swm_pwm_set(pwm_device, configuration);
    case PWM_CMD_GET:
        return swm_pwm_get(pwm_device, configuration);
    default:
        return -RT_EINVAL;
    }
}

static const struct rt_pwm_ops pwm_ops =
    {
        .control = swm_pwm_control};

int swm_pwm_init(void)
{
    int i = 0;
    int result = RT_EOK;

    for (i = 0; i < sizeof(swm_pwm_cfg) / sizeof(swm_pwm_cfg[0]); i++)
    {
        pwm_obj[i].pwm_cfg = &swm_pwm_cfg[i];

        if (pwm_obj[i].pwm_cfg->PWMx == PWM0)
        {
#ifdef BSP_USING_PWM0A
            PORT_Init(PORTM, PIN1, PORTM_PIN1_PWM0A, 0);
#endif
#ifdef BSP_USING_PWM0AN
            PORT_Init(PORTM, PIN4, PORTM_PIN4_PWM0AN, 0);
#endif
#ifdef BSP_USING_PWM0B
            PORT_Init(PORTM, PIN2, PORTM_PIN2_PWM0B, 0);
#endif
#ifdef BSP_USING_PWM0BN
            PORT_Init(PORTM, PIN5, PORTM_PIN5_PWM0BN, 0);
#endif
        }
        else if (pwm_obj[i].pwm_cfg->PWMx == PWM1)
        {
#ifdef BSP_USING_PWM1A
            PORT_Init(PORTM, PIN3, PORTM_PIN3_PWM1A, 0);
#endif
#ifdef BSP_USING_PWM1AN
            PORT_Init(PORTM, PIN6, PORTM_PIN6_PWM1AN, 0);
#endif
#ifdef BSP_USING_PWM1B
            PORT_Init(PORTD, PIN9, PORTD_PIN9_PWM1B, 0);
#endif
#ifdef BSP_USING_PWM1BN
            PORT_Init(PORTD, PIN8, PORTD_PIN8_PWM1BN, 0);
#endif
        }
        else if (pwm_obj[i].pwm_cfg->PWMx == PWM2)
        {
#ifdef BSP_USING_PWM2A
            PORT_Init(PORTM, PIN12, PORTM_PIN12_PWM2A, 0);
#endif
#ifdef BSP_USING_PWM2AN
            PORT_Init(PORTM, PIN9, PORTM_PIN9_PWM2AN, 0);
#endif
#ifdef BSP_USING_PWM2B
            PORT_Init(PORTM, PIN11, PORTM_PIN11_PWM2B, 0);
#endif
#ifdef BSP_USING_PWM2BN
            PORT_Init(PORTM, PIN8, PORTM_PIN8_PWM2BN, 0);
#endif
        }
        else if (pwm_obj[i].pwm_cfg->PWMx == PWM3)
        {
#ifdef BSP_USING_PWM3A
            PORT_Init(PORTC, PIN2, PORTC_PIN2_PWM3A, 0);
#endif
#ifdef BSP_USING_PWM3AN
            PORT_Init(PORTC, PIN3, PORTC_PIN3_PWM3AN, 0);
#endif
#ifdef BSP_USING_PWM3B
            PORT_Init(PORTB, PIN1, PORTB_PIN1_PWM3B, 0);
#endif
#ifdef BSP_USING_PWM3BN
            PORT_Init(PORTB, PIN0, PORTB_PIN0_PWM3BN, 0);
#endif
        }
        else if (pwm_obj[i].pwm_cfg->PWMx == PWM4)
        {
#ifdef BSP_USING_PWM4A
            PORT_Init(PORTB, PIN15, PORTB_PIN15_PWM4A, 0);
#endif
#ifdef BSP_USING_PWM4AN
            // PORT_Init(PORTB, PIN14, PORTB_PIN14_PWM4AN, 0);  //SWDIO
#endif
#ifdef BSP_USING_PWM4B
            PORT_Init(PORTB, PIN13, PORTB_PIN13_PWM4B, 0);
#endif
#ifdef BSP_USING_PWM4BN
            // PORT_Init(PORTB, PIN12, PORTB_PIN12_PWM4BN, 0);  //SWDCK
#endif
        }

        pwm_obj[i].pwm_cfg->pwm_initstruct.Clkdiv = SystemCoreClock / 1000000UL / 2;  //中心对称模式下频率降低一半
        PWM_Init(pwm_obj[i].pwm_cfg->PWMx, &(pwm_obj[i].pwm_cfg->pwm_initstruct));
        result = rt_device_pwm_register(&pwm_obj[i].pwm_device, pwm_obj[i].pwm_cfg->name, &pwm_ops, pwm_obj[i].pwm_cfg);
        if(result != RT_EOK)
        {
            LOG_E("%s register fail.", pwm_obj[i].pwm_cfg->name);
        }
        else
        {
            LOG_D("%s register success.", pwm_obj[i].pwm_cfg->name);
        }
    }
    return result;
}
INIT_DEVICE_EXPORT(swm_pwm_init);

#endif /* BSP_USING_PWM */
#endif /* RT_USING_PWM */
