/*
 * Copyright (c) 2006-2021, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2021-10-25     KevinXu      first version
 */

#include "drv_pwm.h"

#ifdef RT_USING_PWM

/* Declare the control function first */
static rt_err_t drv_pwm_control(struct rt_device_pwm *, int, void *);
static struct rt_pwm_ops drv_ops =
{
    drv_pwm_control
};

static struct ra_pwm ra6m4_pwm_obj[BSP_PWMS_NUM] =
{
#ifdef BSP_USING_PWM0
    [BSP_PWM0_INDEX] = PWM_DRV_INITIALIZER(0),
#endif
#ifdef BSP_USING_PWM1
    [BSP_PWM1_INDEX] = PWM_DRV_INITIALIZER(1),
#endif
#ifdef BSP_USING_PWM2
    [BSP_PWM2_INDEX] = PWM_DRV_INITIALIZER(2),
#endif
#ifdef BSP_USING_PWM3
    [BSP_PWM3_INDEX] = PWM_DRV_INITIALIZER(3),
#endif
#ifdef BSP_USING_PWM4
    [BSP_PWM4_INDEX] = PWM_DRV_INITIALIZER(4),
#endif
#ifdef BSP_USING_PWM5
    [BSP_PWM5_INDEX] = PWM_DRV_INITIALIZER(5),
#endif
#ifdef BSP_USING_PWM6
    [BSP_PWM6_INDEX] = PWM_DRV_INITIALIZER(6),
#endif
#ifdef BSP_USING_PWM7
    [BSP_PWM7_INDEX] = PWM_DRV_INITIALIZER(7),
#endif
#ifdef BSP_USING_PWM8
    [BSP_PWM8_INDEX] = PWM_DRV_INITIALIZER(8),
#endif
#ifdef BSP_USING_PWM9
    [BSP_PWM9_INDEX] = PWM_DRV_INITIALIZER(9),
#endif
};


/* Convert the raw PWM period counts into ns */
static rt_uint32_t _convert_counts_ns(uint32_t source_div, uint32_t raw)
{
    uint32_t pclkd_freq_hz = R_FSP_SystemClockHzGet(FSP_PRIV_CLOCK_PCLKD) >> source_div;
    uint32_t ns = (uint32_t)(((uint64_t)raw * 1000000000ULL) / pclkd_freq_hz);
    return ns;
}

/* Convert ns into raw PWM period counts */
static rt_uint32_t _convert_ns_counts(uint32_t source_div, uint32_t raw)
{
    uint32_t pclkd_freq_hz = R_FSP_SystemClockHzGet(FSP_PRIV_CLOCK_PCLKD) >> source_div;
    uint32_t counts = (uint32_t)(((uint64_t)raw * (uint64_t)pclkd_freq_hz) / 1000000000ULL);
    return counts;
}


/* PWM_CMD_ENABLE or PWM_CMD_DISABLE */
static rt_err_t drv_pwm_enable(struct ra_pwm *device,
                               struct rt_pwm_configuration *configuration,
                               rt_bool_t enable)
{
    fsp_err_t err = FSP_SUCCESS;

    if (enable)
    {
        err = R_GPT_Start(device->g_ctrl);
    }
    else
    {
        err = R_GPT_Stop(device->g_ctrl);
    }

    return (err == FSP_SUCCESS) ? RT_EOK : -RT_ERROR;
}

/* PWM_CMD_GET */
static rt_err_t drv_pwm_get(struct ra_pwm *device,
                            struct rt_pwm_configuration *configuration)
{
    timer_info_t info;
    if (R_GPT_InfoGet(device->g_ctrl, &info) != FSP_SUCCESS)
        return -RT_ERROR;

    configuration->pulse =
        _convert_counts_ns(device->g_cfg->source_div, device->g_cfg->duty_cycle_counts);
    configuration->period =
        _convert_counts_ns(device->g_cfg->source_div, info.period_counts);
    configuration->channel = device->g_cfg->channel;

    return RT_EOK;
}

/* PWM_CMD_SET */
static rt_err_t drv_pwm_set(struct ra_pwm *device,
                            struct rt_pwm_configuration *conf)
{
    uint32_t counts;
    fsp_err_t fsp_erra;
    fsp_err_t fsp_errb;
    rt_err_t rt_err;
    uint32_t pulse;
    uint32_t period;
    struct rt_pwm_configuration orig_conf;

    rt_err = drv_pwm_get(device, &orig_conf);
    if (rt_err != RT_EOK)
    {
        return rt_err;
    }

    /* Pulse cannot last longer than period. */
    period = conf->period;
    pulse = (period >= conf->pulse) ? conf->pulse : period;

    /* Not to set period again if it's not changed. */
    if (period != orig_conf.period)
    {
        counts = _convert_ns_counts(device->g_cfg->source_div, period);
        fsp_erra = R_GPT_PeriodSet(device->g_ctrl, counts);
        if (fsp_erra != FSP_SUCCESS)
        {
            return -RT_ERROR;
        }
    }

    /* Two pins of a channel will not be separated. */
    counts = _convert_ns_counts(device->g_cfg->source_div, pulse);
    fsp_erra = R_GPT_DutyCycleSet(device->g_ctrl, counts, GPT_IO_PIN_GTIOCA);
    fsp_errb = R_GPT_DutyCycleSet(device->g_ctrl, counts, GPT_IO_PIN_GTIOCB);
    if (fsp_erra != FSP_SUCCESS || fsp_errb != FSP_SUCCESS)
    {
        return -RT_ERROR;
    }

    return RT_EOK;
}

/**
 * Implement of control method in struct rt_pwm_ops.
 */
static rt_err_t drv_pwm_control(struct rt_device_pwm *device, int cmd, void *arg)
{
    struct rt_pwm_configuration *configuration = (struct rt_pwm_configuration *)arg;
    struct ra_pwm *pwm_device = (struct ra_pwm *)device->parent.user_data;

    /**
     * There's actually only one GPT timer with 10 channels. In this case, the
     * timer is separated into 10 PWM devices, so each device has only one
     * channel.
     */
    if (configuration->channel != 0)
    {
        return -RT_EINVAL;
    }

    switch (cmd)
    {
    case PWM_CMD_ENABLE:
        return drv_pwm_enable(pwm_device, configuration, RT_TRUE);
    case PWM_CMD_DISABLE:
        return drv_pwm_enable(pwm_device, configuration, RT_FALSE);
    case PWM_CMD_GET:
        return drv_pwm_get(pwm_device, configuration);
    case PWM_CMD_SET:
        return drv_pwm_set(pwm_device, configuration);
    default:
        return -RT_EINVAL;
    }

    return RT_EOK;
}

/**
 * This is to register the PWM device
 *
 * Note that the PWM driver only supports one fixed pin.
 */
int rt_hw_pwm_init(void)
{
    rt_err_t ret = RT_EOK;
    rt_err_t rt_err = RT_EOK;
    fsp_err_t fsp_err = FSP_SUCCESS;

    for (int i = 0; i < BSP_PWMS_NUM; i++)
    {
        fsp_err = R_GPT_Open(ra6m4_pwm_obj[i].g_ctrl,
                             ra6m4_pwm_obj[i].g_cfg);

        rt_err = rt_device_pwm_register(&ra6m4_pwm_obj[i].pwm_device,
                                        ra6m4_pwm_obj[i].name,
                                        &drv_ops,
                                        &ra6m4_pwm_obj[i]);

        if (fsp_err != FSP_SUCCESS || rt_err != RT_EOK)
        {
            ret = -RT_ERROR;
        }
    }

    return ret;
}
INIT_BOARD_EXPORT(rt_hw_pwm_init);
#endif /* RT_USING_PWM */
