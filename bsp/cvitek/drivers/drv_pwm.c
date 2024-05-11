/*
 * Copyright (c) 2006-2024, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2024/02/19     flyingcys    first version
 */
#include <rtthread.h>
#include <rtdevice.h>
#include "drv_pwm.h"

#define DBG_LEVEL   DBG_LOG
#include <rtdbg.h>
#define LOG_TAG "DRV.PWM"

struct cvi_pwm_dev
{
    struct rt_device_pwm device;
    const char *name;
    rt_ubase_t reg_base;
};

static const uint64_t count_unit = 100000000;  // 100M count per second
static const uint64_t NSEC_COUNT = 1000000000;  // ns

static void cvi_pwm_set_config(rt_ubase_t reg_base, struct rt_pwm_configuration *cfg)
{
    unsigned long long duty_clk, period_clk;

    cvi_pwm_set_polarity_high_ch(reg_base, (cfg->channel & PWM_MAX_CH));

    duty_clk = (cfg->pulse * count_unit) / NSEC_COUNT;
    cvi_pwm_set_high_period_ch(reg_base, (cfg->channel & PWM_MAX_CH), duty_clk);

    period_clk = (cfg->period * count_unit) / NSEC_COUNT;
    cvi_pwm_set_period_ch(reg_base, (cfg->channel & PWM_MAX_CH), period_clk);

    cvi_pwm_output_en_ch(reg_base, cfg->channel & PWM_MAX_CH);
}

static void cvi_pwm_get_config(rt_ubase_t reg_base, struct rt_pwm_configuration *cfg)
{
    unsigned long long duty_clk, period_clk;

    duty_clk = cvi_pwm_get_high_period_ch(reg_base, (cfg->channel & PWM_MAX_CH));
    cfg->pulse = duty_clk * NSEC_COUNT / count_unit;

    period_clk = cvi_pwm_get_period_ch(reg_base, (cfg->channel & PWM_MAX_CH));
    cfg->period = period_clk * NSEC_COUNT / count_unit;
}
static rt_err_t _pwm_control(struct rt_device_pwm *device, int cmd, void *arg)
{
    struct rt_pwm_configuration *cfg = (struct rt_pwm_configuration *)arg;
    struct cvi_pwm_dev *pwm_dev = (struct cvi_pwm_dev *)device->parent.user_data;
    unsigned long long duty_clk, period_clk;
    const uint64_t count_unit = 100000000;  // 100M count per second
    const uint64_t NSEC_COUNT = 1000000000;  // ns

    if (cfg->channel > PWM_MAX_CH)
        return -RT_EINVAL;

    switch (cmd)
    {
        case PWM_CMD_ENABLE:
            cvi_pwm_start_en_ch(pwm_dev->reg_base, cfg->channel & PWM_MAX_CH);
        break;

        case PWM_CMD_DISABLE:
            cvi_pwm_start_dis_ch(pwm_dev->reg_base, cfg->channel & PWM_MAX_CH);
        break;

        case PWM_CMD_SET:
            cvi_pwm_set_config(pwm_dev->reg_base, cfg);
        break;

        case PWM_CMD_GET:
            cvi_pwm_get_config(pwm_dev->reg_base, cfg);
        break;

        case PWM_CMD_SET_PERIOD:
            period_clk = (cfg->period * count_unit) / NSEC_COUNT;
            cvi_pwm_set_period_ch(pwm_dev->reg_base, (cfg->channel & PWM_MAX_CH), period_clk);
        break;

        case PWM_CMD_SET_PULSE:
            duty_clk = (cfg->pulse * count_unit) / NSEC_COUNT;
            cvi_pwm_set_high_period_ch(pwm_dev->reg_base, (cfg->channel & PWM_MAX_CH), duty_clk);
        break;

        default:
        LOG_D("cmd: %x channel: %d period: %d pulse: %d", cmd, cfg->channel, cfg->period, cfg->pulse);
        break;
    }

    return RT_EOK;
}

const static struct rt_pwm_ops cvi_pwm_ops =
{
    .control = &_pwm_control
};

static struct cvi_pwm_dev cvi_pwm[] =
{
#ifdef BSP_USING_PWM0
    {
        .name = "pwm0",
        .reg_base = CVI_PWM0_BASE,
    },
#endif

#ifdef BSP_USING_PWM1
    {
        .name = "pwm1",
        .reg_base = CVI_PWM1_BASE,
    },
#endif

#ifdef BSP_USING_PWM2
    {
        .name = "pwm2",
        .reg_base = CVI_PWM2_BASE,
    },
#endif

#ifdef BSP_USING_PWM3
    {
        .name = "pwm3",
        .reg_base = CVI_PWM3_BASE,
    },
#endif
};

int rt_hw_pwm_init(void)
{
    int result = RT_EOK;
    uint8_t i;

    for (i = 0; i < sizeof(cvi_pwm) / sizeof(cvi_pwm[0]); i++)
    {
        result = rt_device_pwm_register(&cvi_pwm[i].device, cvi_pwm[i].name, &cvi_pwm_ops, &cvi_pwm[i]);
        if (result != RT_EOK)
        {
            LOG_E("device %s register failed", cvi_pwm[i].name);
            return -RT_ERROR;
        }
    }
    return RT_EOK;
#if 0
#ifdef BSP_USING_PWM0
    static struct cvi_pwm_dev cvi_pwm0;

    cvi_pwm0.name = "pwm0";
    cvi_pwm0.reg_base = CVI_PWM0_BASE;

    result = rt_device_pwm_register(&cvi_pwm0.device, cvi_pwm0.name, &cvi_pwm_ops, &cvi_pwm0);
    if (result != RT_EOK)
    {
        LOG_E("device %s register failed.", cvi_pwm0.name);
        return result;
    }
#endif

#ifdef BSP_USING_PWM1
    static struct cvi_pwm_dev cvi_pwm1;
    cvi_pwm1.name = "pwm1";
    cvi_pwm1.reg_base = CVI_PWM1_BASE;

    result = rt_device_pwm_register(&cvi_pwm1.device, cvi_pwm1.name, &cvi_pwm_ops, &cvi_pwm1);
    if (result != RT_EOK)
    {
        LOG_E("device %s register failed.", cvi_pwm1.name);
        return result;
    }
#endif

#ifdef BSP_USING_PWM2
    static struct cvi_pwm_dev cvi_pwm2;
    cvi_pwm2.name = "pwm2";
    cvi_pwm2.reg_base = CVI_PWM2_BASE;

    result = rt_device_pwm_register(&cvi_pwm2.device, cvi_pwm2.name, &cvi_pwm_ops, &cvi_pwm2);
    if (result != RT_EOK)
    {
        LOG_E("device %s register failed.", cvi_pwm2.name);
        return result;
    }
#endif

#ifdef BSP_USING_PWM3
    static struct cvi_pwm_dev cvi_pwm3;
    cvi_pwm3.name = "pwm3";
    cvi_pwm3.reg_base = CVI_PWM3_BASE;

    result = rt_device_pwm_register(&cvi_pwm3.device, cvi_pwm3.name, &cvi_pwm_ops, &cvi_pwm3);
    if (result != RT_EOK)
    {
        LOG_E("device %s register failed.",  cvi_pwm3.name);
        return result;
    }
#endif

    return RT_EOK;
#endif
}
INIT_BOARD_EXPORT(rt_hw_pwm_init);
