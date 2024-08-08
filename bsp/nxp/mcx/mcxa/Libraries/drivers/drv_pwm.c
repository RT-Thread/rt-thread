/*
 * Copyright (c) 2006-2024 RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2024-08-1      hywing       Initial version.
 */

#include <rtthread.h>
#include <rtdevice.h>
#include "fsl_ctimer.h"

#ifdef RT_USING_PWM

typedef struct
{
    struct rt_device_pwm pwm_device;
    CTIMER_Type *ct_instance;
    uint32_t timerClock;
    const ctimer_match_t pwmPeriodChannel;
    ctimer_match_t matchChannel;
    char *name;
} mcx_pwm_obj_t;

static mcx_pwm_obj_t mcx_pwm_list[]=
{
#ifdef BSP_USING_PWM0
    {
        .ct_instance = CTIMER1,
        .timerClock = 0,
        .pwmPeriodChannel = kCTIMER_Match_3,
        .matchChannel = kCTIMER_Match_2,
        .name = "pwm0",
    }
#endif
};

volatile uint32_t g_pwmPeriod   = 0U;
volatile uint32_t g_pulsePeriod = 0U;

static rt_err_t mcx_drv_pwm_get(mcx_pwm_obj_t *pwm, struct rt_pwm_configuration *configuration)
{
    return RT_EOK;
}

status_t CTIMER_GetPwmPeriodValue(uint32_t pwmFreqHz, uint8_t dutyCyclePercent, uint32_t timerClock_Hz)
{
    g_pwmPeriod = (timerClock_Hz / pwmFreqHz) - 1U;
    g_pulsePeriod = (g_pwmPeriod + 1U) * (100 - dutyCyclePercent) / 100;
    return kStatus_Success;
}

static rt_err_t mcx_drv_pwm_set(mcx_pwm_obj_t *pwm, struct rt_pwm_configuration *configuration)
{
    CTIMER_Type *ct = pwm->ct_instance;
    uint32_t pwmFreqHz = 1000000000 / configuration->period;
    uint8_t dutyCyclePercent = configuration->pulse * 100 / configuration->period;
    CTIMER_GetPwmPeriodValue(pwmFreqHz, dutyCyclePercent, pwm->timerClock);
    CTIMER_SetupPwmPeriod(ct, kCTIMER_Match_3, kCTIMER_Match_2, g_pwmPeriod, g_pulsePeriod, false);
    return 0;
}

static rt_err_t mcx_drv_pwm_enable(mcx_pwm_obj_t *pwm, struct rt_pwm_configuration *configuration)
{
    CTIMER_StartTimer(pwm->ct_instance);
    return 0;
}

static rt_err_t mcx_drv_pwm_disable(mcx_pwm_obj_t *pwm, struct rt_pwm_configuration *configuration)
{
    CTIMER_StopTimer(pwm->ct_instance);
    return 0;
}

static rt_err_t mcx_drv_pwm_control(struct rt_device_pwm *device, int cmd, void *args)
{
    mcx_pwm_obj_t *pwm = device->parent.user_data;
    struct rt_pwm_configuration *configuration = (struct rt_pwm_configuration *)args;

    switch (cmd)
    {
    case PWM_CMD_ENABLE:
        return mcx_drv_pwm_enable(pwm, configuration);

    case PWM_CMD_DISABLE:
        return mcx_drv_pwm_disable(pwm, configuration);

    case PWM_CMD_SET:
        return mcx_drv_pwm_set(pwm, configuration);

    case PWM_CMD_GET:
        return mcx_drv_pwm_get(pwm, configuration);

    default:
        return -RT_EINVAL;
    }

    return RT_EOK;
}

static struct rt_pwm_ops mcx_pwm_ops =
{
    .control = mcx_drv_pwm_control,
};

int mcx_pwm_init(void)
{
    rt_err_t ret;
    char name_buf[8];

    ctimer_config_t config;
    CTIMER_GetDefaultConfig(&config);
    for (uint8_t i = 0; i < ARRAY_SIZE(mcx_pwm_list); i++)
    {
        mcx_pwm_list[i].timerClock = CLOCK_GetCTimerClkFreq(1U) / (config.prescale + 1);
        CTIMER_Init(mcx_pwm_list[i].ct_instance, &config);
        ret = rt_device_pwm_register(&mcx_pwm_list[i].pwm_device, mcx_pwm_list[i].name, &mcx_pwm_ops, &mcx_pwm_list[i]);
        if (ret != RT_EOK)
        {
            return ret;
        }
    }
    return RT_EOK;
}

INIT_DEVICE_EXPORT(mcx_pwm_init);

#endif /* RT_USING_PWM */
