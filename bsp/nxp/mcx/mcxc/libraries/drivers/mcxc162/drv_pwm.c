/*
 * Copyright (c) 2006-2026, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2026-09-03     Alex Yang    Add MCXC162 FLEXPWM0 SM0 support
 */

#include <rtthread.h>
#include <rtdevice.h>

#include "fsl_clock.h"
#include "fsl_pwm.h"

#if defined(BSP_USING_PWM) && defined(BSP_USING_PWM0)

#define MCXC162_PWM_CHANNEL_COUNT 2U
#define MCXC162_PWM_NSEC_PER_SEC  1000000000ULL

struct mcxc162_pwm
{
    struct rt_device_pwm device;
    struct rt_pwm_configuration configuration[MCXC162_PWM_CHANNEL_COUNT];
    rt_bool_t configured[MCXC162_PWM_CHANNEL_COUNT];
    rt_bool_t enabled[MCXC162_PWM_CHANNEL_COUNT];
    rt_uint32_t period;
};

static struct mcxc162_pwm mcxc162_pwm;

static pwm_channels_t mcxc162_pwm_channel(rt_uint32_t channel)
{
    return channel == 0U ? kPWM_PwmA : kPWM_PwmB;
}

static rt_bool_t mcxc162_pwm_running(void)
{
    return mcxc162_pwm.enabled[0] || mcxc162_pwm.enabled[1];
}

static uint16_t mcxc162_pwm_duty(rt_uint32_t pulse, rt_uint32_t period)
{
    return (uint16_t)(((uint64_t)pulse * 65535U + period / 2U) / period);
}

static rt_err_t mcxc162_pwm_counts(rt_uint32_t period, pwm_clock_prescale_t *prescale,
                                   uint16_t *counts)
{
    uint32_t source = CLOCK_GetFreq(kCLOCK_BusClk);
    uint32_t shift;

    for (shift = 0U; shift <= (uint32_t)kPWM_Prescale_Divide_128; shift++)
    {
        uint64_t divisor = MCXC162_PWM_NSEC_PER_SEC << shift;
        uint64_t value = ((uint64_t)source * period + divisor / 2U) / divisor;

        if ((value > 0U) && (value <= 0xFFFFU))
        {
            *prescale = (pwm_clock_prescale_t)shift;
            *counts = (uint16_t)value;
            return RT_EOK;
        }
    }

    return -RT_EINVAL;
}

static rt_err_t mcxc162_pwm_reconfigure(rt_uint32_t period)
{
    pwm_clock_prescale_t prescale;
    pwm_config_t config;
    pwm_signal_param_t signals[MCXC162_PWM_CHANNEL_COUNT];
    uint32_t source = CLOCK_GetFreq(kCLOCK_BusClk);
    uint32_t pwm_clock;
    uint32_t setup_frequency;
    uint16_t counts;
    rt_uint32_t index;

    if (mcxc162_pwm_counts(period, &prescale, &counts) != RT_EOK)
    {
        return -RT_EINVAL;
    }

    PWM_StopTimer(FLEXPWM0, kPWM_Control_Module_0);
    PWM_OutputDisable(FLEXPWM0, kPWM_PwmA, kPWM_Module_0);
    PWM_OutputDisable(FLEXPWM0, kPWM_PwmB, kPWM_Module_0);

    PWM_GetDefaultConfig(&config);
    config.prescale = prescale;
    config.pairOperation = kPWM_Independent;
    config.reloadLogic = kPWM_ReloadPwmFullCycle;
    if (PWM_Init(FLEXPWM0, kPWM_Module_0, &config) != kStatus_Success)
    {
        return -RT_ERROR;
    }

    for (index = 0U; index < MCXC162_PWM_CHANNEL_COUNT; index++)
    {
        signals[index].pwmChannel = mcxc162_pwm_channel(index);
        signals[index].dutyCyclePercent = 0U;
        signals[index].level = kPWM_HighTrue;
        signals[index].deadtimeValue = 0U;
        signals[index].faultState = kPWM_PwmFaultState0;
        signals[index].pwmchannelenable = false;
    }

    pwm_clock = source >> (uint32_t)prescale;
    setup_frequency = (pwm_clock + counts - 1U) / counts;
    if (PWM_SetupPwm(FLEXPWM0, kPWM_Module_0, signals,
                     MCXC162_PWM_CHANNEL_COUNT, kPWM_EdgeAligned,
                     setup_frequency, source) != kStatus_Success)
    {
        return -RT_ERROR;
    }

    PWM_UpdatePwmPeriodAndDutycycle(
        FLEXPWM0, kPWM_Module_0, kPWM_PwmA, kPWM_EdgeAligned, counts,
        mcxc162_pwm_duty(mcxc162_pwm.configuration[0].pulse, period));
    PWM_UpdatePwmDutycycleHighAccuracy(
        FLEXPWM0, kPWM_Module_0, kPWM_PwmB, kPWM_EdgeAligned,
        mcxc162_pwm_duty(mcxc162_pwm.configuration[1].pulse, period));

    PWM_SetupFaultDisableMap(FLEXPWM0, kPWM_Module_0, kPWM_PwmA,
                             kPWM_faultchannel_0, 0U);
    PWM_SetupFaultDisableMap(FLEXPWM0, kPWM_Module_0, kPWM_PwmB,
                             kPWM_faultchannel_0, 0U);

    for (index = 0U; index < MCXC162_PWM_CHANNEL_COUNT; index++)
    {
        if (mcxc162_pwm.enabled[index])
        {
            PWM_OutputEnable(FLEXPWM0, mcxc162_pwm_channel(index), kPWM_Module_0);
        }
    }

    PWM_SetPwmLdok(FLEXPWM0, kPWM_Control_Module_0, true);
    if (mcxc162_pwm_running())
    {
        PWM_StartTimer(FLEXPWM0, kPWM_Control_Module_0);
    }

    return RT_EOK;
}

static rt_err_t mcxc162_pwm_set(struct rt_pwm_configuration *configuration)
{
    rt_uint32_t channel = configuration->channel;
    rt_uint32_t other = channel ^ 1U;
    rt_uint32_t index;

    if ((channel >= MCXC162_PWM_CHANNEL_COUNT) || (configuration->period == 0U) ||
        (configuration->pulse > configuration->period) || configuration->complementary ||
        (configuration->dead_time != 0U) || (configuration->phase != 0U))
    {
        return -RT_EINVAL;
    }

    if (mcxc162_pwm.enabled[other] && (mcxc162_pwm.period != configuration->period))
    {
        return -RT_EINVAL;
    }

    if (mcxc162_pwm.period != configuration->period)
    {
        pwm_clock_prescale_t prescale;
        uint16_t counts;

        if (mcxc162_pwm_counts(configuration->period, &prescale, &counts) != RT_EOK)
        {
            return -RT_EINVAL;
        }

        mcxc162_pwm.period = configuration->period;
        for (index = 0U; index < MCXC162_PWM_CHANNEL_COUNT; index++)
        {
            if (mcxc162_pwm.configured[index])
            {
                mcxc162_pwm.configuration[index].period = configuration->period;
                if (mcxc162_pwm.configuration[index].pulse > configuration->period)
                {
                    mcxc162_pwm.configuration[index].pulse = configuration->period;
                }
            }
        }

        mcxc162_pwm.configuration[channel] = *configuration;
        mcxc162_pwm.configured[channel] = RT_TRUE;
        return mcxc162_pwm_reconfigure(configuration->period);
    }

    mcxc162_pwm.configuration[channel] = *configuration;
    mcxc162_pwm.configured[channel] = RT_TRUE;
    PWM_UpdatePwmDutycycleHighAccuracy(
        FLEXPWM0, kPWM_Module_0, mcxc162_pwm_channel(channel), kPWM_EdgeAligned,
        mcxc162_pwm_duty(configuration->pulse, configuration->period));
    PWM_SetPwmLdok(FLEXPWM0, kPWM_Control_Module_0, true);

    return RT_EOK;
}

static rt_err_t mcxc162_pwm_control(struct rt_device_pwm *device, int command, void *argument)
{
    struct rt_pwm_configuration *configuration = argument;
    rt_uint32_t channel = configuration->channel;
    struct rt_pwm_configuration updated;
    rt_bool_t was_running;

    RT_UNUSED(device);

    if (channel >= MCXC162_PWM_CHANNEL_COUNT)
    {
        return -RT_EINVAL;
    }

    switch (command)
    {
    case PWM_CMD_ENABLE:
        if (!mcxc162_pwm.configured[channel])
        {
            return -RT_EINVAL;
        }
        was_running = mcxc162_pwm_running();
        PWM_OutputEnable(FLEXPWM0, mcxc162_pwm_channel(channel), kPWM_Module_0);
        mcxc162_pwm.enabled[channel] = RT_TRUE;
        if (!was_running)
        {
            PWM_StartTimer(FLEXPWM0, kPWM_Control_Module_0);
        }
        return RT_EOK;

    case PWM_CMD_DISABLE:
        PWM_OutputDisable(FLEXPWM0, mcxc162_pwm_channel(channel), kPWM_Module_0);
        mcxc162_pwm.enabled[channel] = RT_FALSE;
        if (!mcxc162_pwm_running())
        {
            PWM_StopTimer(FLEXPWM0, kPWM_Control_Module_0);
        }
        return RT_EOK;

    case PWM_CMD_SET:
        return mcxc162_pwm_set(configuration);

    case PWM_CMD_SET_PERIOD:
        updated = mcxc162_pwm.configuration[channel];
        updated.channel = channel;
        updated.period = configuration->period;
        return mcxc162_pwm_set(&updated);

    case PWM_CMD_SET_PULSE:
        if (!mcxc162_pwm.configured[channel])
        {
            return -RT_EINVAL;
        }
        updated = mcxc162_pwm.configuration[channel];
        updated.pulse = configuration->pulse;
        return mcxc162_pwm_set(&updated);

    case PWM_CMD_GET:
        if (!mcxc162_pwm.configured[channel])
        {
            return -RT_EINVAL;
        }
        *configuration = mcxc162_pwm.configuration[channel];
        return RT_EOK;

    default:
        return -RT_ENOSYS;
    }
}

static const struct rt_pwm_ops mcxc162_pwm_ops = {
    .control = mcxc162_pwm_control,
};

int rt_hw_pwm_init(void)
{
    mcxc162_pwm.configuration[0].channel = 0U;
    mcxc162_pwm.configuration[1].channel = 1U;

    return rt_device_pwm_register(&mcxc162_pwm.device, "pwm0",
                                  &mcxc162_pwm_ops, RT_NULL);
}
INIT_DEVICE_EXPORT(rt_hw_pwm_init);

#endif /* BSP_USING_PWM && BSP_USING_PWM0 */
