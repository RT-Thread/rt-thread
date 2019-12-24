/*
 * Copyright (c) 2006-2018, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2019-04-28     tyustli      first version
 *
 */

#include <rtthread.h>

#ifdef BSP_USING_PWM

#if !defined(BSP_USING_PWM1_CH0) && !defined(BSP_USING_PWM1_CH1) && !defined(BSP_USING_PWM1_CH2) && !defined(BSP_USING_PWM1_CH3) && \
    !defined(BSP_USING_PWM2_CH0) && !defined(BSP_USING_PWM2_CH1) && !defined(BSP_USING_PWM2_CH2) && !defined(BSP_USING_PWM2_CH3) && \
    !defined(BSP_USING_PWM3_CH0) && !defined(BSP_USING_PWM3_CH1) && !defined(BSP_USING_PWM3_CH2) && !defined(BSP_USING_PWM3_CH3) && \
    !defined(BSP_USING_PWM4_CH0) && !defined(BSP_USING_PWM4_CH1) && !defined(BSP_USING_PWM4_CH2) && !defined(BSP_USING_PWM4_CH3)
#error "Please define at least one BSP_USING_PWMx_CHx"
#endif

#define LOG_TAG             "drv.pwm"
#include <drv_log.h>

#include <rtdevice.h>
#include "fsl_pwm.h"
#include "drv_pwm.h"

#define DEFAULT_PRE                   5
#define DEFAULT_DUTY                  50
#define DEFAULT_FRE                   1000
#define PWM_SRC_CLK_FREQ              CLOCK_GetFreq(kCLOCK_IpgClk)
#define DEFAULT_COMPLEMENTARY_PAIR    kPWM_PwmA
#define DEFAULT_POLARITY              kPWM_HighTrue

static pwm_signal_param_t Pwm_Signal;

static rt_err_t imxrt_drv_pwm_control(struct rt_device_pwm *device, int cmd, void *arg);

static struct rt_pwm_ops imxrt_drv_ops =
{
    .control = imxrt_drv_pwm_control
};

static rt_err_t imxrt_drv_pwm_enable(struct rt_device_pwm *device, struct rt_pwm_configuration *configuration, rt_bool_t enable)
{
    PWM_Type *base;
    pwm_module_control_t pwm_module_control;

    base = (PWM_Type *)device->parent.user_data;
    pwm_module_control = (pwm_module_control_t)(1 << configuration->channel);

    if (!enable)
    {
        PWM_StopTimer(base, pwm_module_control);
    }
    else
    {
        PWM_StartTimer(base, pwm_module_control);
    }

    return RT_EOK;
}

static rt_err_t imxrt_drv_pwm_get(struct rt_device_pwm *device, struct rt_pwm_configuration *configuration)
{
    uint8_t get_duty;
    uint16_t pulseCnt = 0, pwmHighPulse = 0;
    uint32_t get_frequence;
    uint32_t pwmClock;
    PWM_Type *base;
    pwm_submodule_t pwm_submodule;

    base = (PWM_Type *)device->parent.user_data;
    pwm_submodule = (pwm_submodule_t)configuration->channel;

    /* get frequence */
    get_frequence = base->SM[pwm_submodule].VAL1;
    pwmClock = (PWM_SRC_CLK_FREQ / (1U << ((base->SM[pwm_submodule].CTRL & PWM_CTRL_PRSC_MASK) >> PWM_CTRL_PRSC_SHIFT)));
    get_frequence = pwmClock / get_frequence;

    /* get dutycycle */
    pulseCnt = base->SM[pwm_submodule].VAL1;
    pwmHighPulse = pulseCnt - (base->SM[pwm_submodule].VAL2) * 2;
    get_duty = pwmHighPulse * 100 / pulseCnt;

    /* conversion */
    configuration->period = 1000000000 / get_frequence;
    configuration->pulse = get_duty * configuration->period / 100;

    return RT_EOK;
}

static rt_err_t imxrt_drv_pwm_set(struct rt_device_pwm *device, struct rt_pwm_configuration *configuration)
{
    RT_ASSERT(configuration->period > 0);
    RT_ASSERT(configuration->pulse <= configuration->period);

    PWM_Type *base;
    pwm_submodule_t pwm_submodule;
    pwm_module_control_t pwm_module_control;
    uint32_t period = 0;
    uint8_t duty = 0;

    base = (PWM_Type *)device->parent.user_data;
    pwm_submodule = (pwm_submodule_t)configuration->channel;
    pwm_module_control = (pwm_module_control_t)(1 << configuration->channel);

    duty = configuration->pulse * 100 / configuration->period;
    Pwm_Signal.dutyCyclePercent = duty;
    period = (uint32_t)(1000000000 / configuration->period);

    PWM_SetupPwm(base, pwm_submodule, &Pwm_Signal, 1, kPWM_CenterAligned, period, PWM_SRC_CLK_FREQ);
    PWM_UpdatePwmDutycycle(base, pwm_submodule, DEFAULT_COMPLEMENTARY_PAIR, kPWM_CenterAligned, duty);
    PWM_SetPwmLdok(base, pwm_module_control, true);

    return RT_EOK;
}

static rt_err_t imxrt_drv_pwm_control(struct rt_device_pwm *device, int cmd, void *arg)
{
    struct rt_pwm_configuration *configuration = (struct rt_pwm_configuration *)arg;

    switch (cmd)
    {
    case PWM_CMD_ENABLE:
        return imxrt_drv_pwm_enable(device, configuration, RT_TRUE);
    case PWM_CMD_DISABLE:
        return imxrt_drv_pwm_enable(device, configuration, RT_FALSE);
    case PWM_CMD_SET:
        return imxrt_drv_pwm_set(device, configuration);
    case PWM_CMD_GET:
        return imxrt_drv_pwm_get(device, configuration);
    default:
        return RT_EINVAL;
    }
}

static rt_err_t imxrt_drv_pwm_init(PWM_Type *base, pwm_submodule_t pwm_submodule, uint16_t psc, uint32_t fre, uint8_t duty)
{
    pwm_config_t PwmConfig;
    uint8_t fault_input;
    pwm_clock_prescale_t pwm_prescale = (pwm_clock_prescale_t)psc;
    fault_input = (uint8_t)pwm_submodule;
    PWM_GetDefaultConfig(&PwmConfig);

    PwmConfig.prescale = pwm_prescale;
    PwmConfig.reloadLogic = kPWM_ReloadPwmFullCycle;
    PwmConfig.pairOperation = kPWM_Independent;
    PwmConfig.enableDebugMode = true;

    if (PWM_Init(base, pwm_submodule, &PwmConfig) == kStatus_Fail)
    {
        LOG_E("init pwm failed \n");
        return RT_ERROR;
    }

    base->SM[fault_input].DISMAP[0] = 0x00;
    base->SM[fault_input].DISMAP[1] = 0x00;

    Pwm_Signal.pwmChannel = DEFAULT_COMPLEMENTARY_PAIR;
    Pwm_Signal.level = DEFAULT_POLARITY;
    Pwm_Signal.dutyCyclePercent = duty;

    PWM_SetupPwm(base, pwm_submodule, &Pwm_Signal, 1, kPWM_CenterAligned, fre, PWM_SRC_CLK_FREQ);
    PWM_SetPwmLdok(base, pwm_submodule, true);

    return RT_EOK;
}

#ifdef BSP_USING_PWM1

static rt_err_t imxrt_pwm1_init(PWM_Type *base)
{
#ifdef BSP_USING_PWM1_CH0
    if (imxrt_drv_pwm_init(base, kPWM_Module_0, DEFAULT_PRE, DEFAULT_FRE, DEFAULT_DUTY) != RT_EOK)
    {
        return RT_ERROR;
    }
#endif /* BSP_USING_PWM1_CH0 */

#ifdef BSP_USING_PWM1_CH1
    if (imxrt_drv_pwm_init(base, kPWM_Module_1, DEFAULT_PRE, DEFAULT_FRE, DEFAULT_DUTY) != RT_EOK)
    {
        return RT_ERROR;
    }
#endif /* BSP_USING_PWM1_CH1 */

#ifdef BSP_USING_PWM1_CH2
    if (imxrt_drv_pwm_init(base, kPWM_Module_2, DEFAULT_PRE, DEFAULT_FRE, DEFAULT_DUTY) != RT_EOK)
    {
        return RT_ERROR;
    }
#endif /*BSP_USING_PWM1_CH2 */

#ifdef BSP_USING_PWM1_CH3
    if (imxrt_drv_pwm_init(base, kPWM_Module_3, DEFAULT_PRE, DEFAULT_FRE, DEFAULT_DUTY) != RT_EOK)
    {
        return RT_ERROR;
    }
#endif /* BSP_USING_PWM1_CH3 */

    return RT_EOK;
}

#endif /* BSP_USING_PWM1 */

#ifdef BSP_USING_PWM2

static rt_err_t imxrt_pwm2_init(PWM_Type *base)
{
#ifdef BSP_USING_PWM2_CH0
    if (imxrt_drv_pwm_init(base, kPWM_Module_0, DEFAULT_PRE, DEFAULT_FRE, DEFAULT_DUTY) != RT_EOK)
    {
        return RT_ERROR;
    }
#endif /* BSP_USING_PWM2_CH0 */

#ifdef BSP_USING_PWM2_CH1
    if (imxrt_drv_pwm_init(base, kPWM_Module_1, DEFAULT_PRE, DEFAULT_FRE, DEFAULT_DUTY) != RT_EOK)
    {
        return RT_ERROR;
    }
#endif /* BSP_USING_PWM2_CH1 */

#ifdef BSP_USING_PWM2_CH2
    if (imxrt_drv_pwm_init(base, kPWM_Module_2, DEFAULT_PRE, DEFAULT_FRE, DEFAULT_DUTY) != RT_EOK)
    {
        return RT_ERROR;
    }
#endif /*BSP_USING_PWM2_CH2 */

#ifdef BSP_USING_PWM2_CH3
    if (imxrt_drv_pwm_init(base, kPWM_Module_3, DEFAULT_PRE, DEFAULT_FRE, DEFAULT_DUTY) != RT_EOK)
    {
        return RT_ERROR;
    }
#endif /* BSP_USING_PWM2_CH3 */

    return RT_EOK;
}

#endif /* BSP_USING_PWM2 */

#ifdef BSP_USING_PWM3

static rt_err_t imxrt_pwm3_init(PWM_Type *base)
{
#ifdef BSP_USING_PWM3_CH0
    if (imxrt_drv_pwm_init(base, kPWM_Module_0, DEFAULT_PRE, DEFAULT_FRE, DEFAULT_DUTY) != RT_EOK)
    {
        return RT_ERROR;
    }
#endif /* BSP_USING_PWM3_CH0 */

#ifdef BSP_USING_PWM3_CH1
    if (imxrt_drv_pwm_init(base, kPWM_Module_1, DEFAULT_PRE, DEFAULT_FRE, DEFAULT_DUTY) != RT_EOK)
    {
        return RT_ERROR;
    }
#endif /* BSP_USING_PWM3_CH1 */

#ifdef BSP_USING_PWM3_CH2
    if (imxrt_drv_pwm_init(base, kPWM_Module_2, DEFAULT_PRE, DEFAULT_FRE, DEFAULT_DUTY) != RT_EOK)
    {
        return RT_ERROR;
    }
#endif /*BSP_USING_PWM3_CH2 */

#ifdef BSP_USING_PWM3_CH3
    if (imxrt_drv_pwm_init(base, kPWM_Module_3, DEFAULT_PRE, DEFAULT_FRE, DEFAULT_DUTY) != RT_EOK)
    {
        return RT_ERROR;
    }
#endif /* BSP_USING_PWM3_CH3 */

    return RT_EOK;
}

#endif /* BSP_USING_PWM3 */

#ifdef BSP_USING_PWM4

static rt_err_t imxrt_pwm4_init(PWM_Type *base)
{
#ifdef BSP_USING_PWM4_CH0
    if (imxrt_drv_pwm_init(base, kPWM_Module_0, DEFAULT_PRE, DEFAULT_FRE, DEFAULT_DUTY) != RT_EOK)
    {
        return RT_ERROR;
    }
#endif /* BSP_USING_PWM4_CH0 */

#ifdef BSP_USING_PWM4_CH1
    if (imxrt_drv_pwm_init(base, kPWM_Module_1, DEFAULT_PRE, DEFAULT_FRE, DEFAULT_DUTY) != RT_EOK)
    {
        return RT_ERROR;
    }
#endif /* BSP_USING_PWM4_CH1 */

#ifdef BSP_USING_PWM4_CH2
    if (imxrt_drv_pwm_init(base, kPWM_Module_2, DEFAULT_PRE, DEFAULT_FRE, DEFAULT_DUTY) != RT_EOK)
    {
        return RT_ERROR;
    }
#endif /*BSP_USING_PWM4_CH2 */

#ifdef BSP_USING_PWM4_CH3
    if (imxrt_drv_pwm_init(base, kPWM_Module_3, DEFAULT_PRE, DEFAULT_FRE, DEFAULT_DUTY) != RT_EOK)
    {
        return RT_ERROR;
    }
#endif /* BSP_USING_PWM4_CH3 */

    return RT_EOK;
}

#endif /* BSP_USING_PWM4 */

int rt_hw_pwm_init(void)
{
    rt_err_t ret = RT_EOK;

#ifdef BSP_USING_PWM1

    static struct rt_device_pwm pwm1_device;

    if (imxrt_pwm1_init(PWM1) != RT_EOK)
    {
        LOG_E("init pwm1 failed\n");
    }

    ret = rt_device_pwm_register(&pwm1_device, "pwm1", &imxrt_drv_ops, PWM1);

    if (ret != RT_EOK)
    {
        LOG_E("%s register failed", "pwm1");
    }

#endif /* BSP_USING_PWM1 */

#ifdef BSP_USING_PWM2

    static struct rt_device_pwm pwm2_device;

    if (imxrt_pwm2_init(PWM2) != RT_EOK)
    {
        LOG_E("init pwm2 failed\n");
    }

    ret = rt_device_pwm_register(&pwm2_device, "pwm2", &imxrt_drv_ops, PWM2);

    if (ret != RT_EOK)
    {
        LOG_E("%s register failed", "pwm2");
    }
#endif /* BSP_USING_PWM2 */

#ifdef BSP_USING_PWM3

    static struct rt_device_pwm pwm3_device;

    if (imxrt_pwm3_init(PWM3) != RT_EOK)
    {
        LOG_E("init pwm3 failed\n");
    }

    ret = rt_device_pwm_register(&pwm3_device, "pwm3", &imxrt_drv_ops, PWM3);

    if (ret != RT_EOK)
    {
        LOG_E("%s register failed", "pwm3");
    }

#endif /* BSP_USING_PWM3 */

#ifdef BSP_USING_PWM4

    static struct rt_device_pwm pwm4_device;

    if (imxrt_pwm4_init(PWM4) != RT_EOK)
    {
        LOG_E("init pwm4 failed\n");
    }

    ret = rt_device_pwm_register(&pwm4_device, "pwm4", &imxrt_drv_ops, PWM4);

    if (ret != RT_EOK)
    {
        LOG_E("%s register failed", "pwm4");
    }
#endif /* BSP_USING_PWM4 */

    return ret;
}

INIT_DEVICE_EXPORT(rt_hw_pwm_init);

#endif /* BSP_USING_PWM */
