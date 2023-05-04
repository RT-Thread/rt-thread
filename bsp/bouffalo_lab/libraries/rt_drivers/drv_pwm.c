/*
 * Copyright (c) 2006-2023, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date             Author           Notes
 * 2023-03-12       wcx1024979076    first version
 */

#include <rtthread.h>
#include <rtdevice.h>
#include "drv_pwm.h"

#ifdef BSP_USING_PWM

#define DBG_LEVEL   DBG_LOG
#include <rtdbg.h>
#define LOG_TAG "DRV.PWM"

static rt_err_t _pwm_set(rt_uint8_t channel, struct rt_pwm_configuration *configuration)
{
    struct bflb_device_s* pwm = bflb_device_get_by_name("pwm_v2_0");

    uint32_t period_hz = 1000000000 / configuration->period;

    struct bflb_pwm_v2_config_s pwm_config;

    pwm_config.clk_source = BFLB_SYSTEM_XCLK;

    pwm_config.clk_div = 40;

    pwm_config.period = 1000000 / period_hz;

    bflb_pwm_v2_init(pwm, &pwm_config);

    struct bflb_pwm_v2_channel_config_s pwm_ch_config = {
        .positive_polarity = PWM_POLARITY_ACTIVE_HIGH,
        .negative_polarity = PWM_POLARITY_ACTIVE_HIGH,
        .positive_stop_state = PWM_STATE_INACTIVE,
        .negative_stop_state = PWM_STATE_ACTIVE,
        .positive_brake_state = PWM_STATE_INACTIVE,
        .negative_brake_state = PWM_STATE_INACTIVE,
        .dead_time = 0,
    };

    bflb_pwm_v2_channel_init(pwm, channel, &pwm_ch_config);

    bflb_pwm_v2_channel_set_threshold(pwm, channel, 0, configuration->pulse);

    bflb_pwm_v2_channel_positive_stop(pwm, channel);
    bflb_pwm_v2_channel_negative_stop(pwm, channel);
    bflb_pwm_v2_stop(pwm);

    bflb_pwm_v2_channel_positive_start(pwm, channel);
    bflb_pwm_v2_channel_negative_start(pwm, channel);
    bflb_pwm_v2_start(pwm);

    return RT_EOK;
}

static rt_err_t _pwm_get(rt_uint8_t channel, struct rt_pwm_configuration *configuration)
{
    uint32_t reg_base, regval, tmp;
    float period;

    reg_base = bflb_device_get_by_name("pwm_v2_0")->reg_base;
    regval = getreg32(reg_base + PWM_MC0_PERIOD_OFFSET);
    tmp = (regval & PWM_PERIOD_MASK) >> PWM_PERIOD_SHIFT;
    period = (float)tmp;

    uint32_t period_hz = 1000000 / period;

    regval = getreg32(reg_base + PWM_MC0_CH0_THRE_OFFSET + channel * 4);
    uint16_t high_threhold = regval >> 16;
    uint16_t low_threhold = regval;

    configuration->period = 1000000000 / period_hz;

    configuration->pulse = high_threhold;

    return RT_EOK;
}

static rt_err_t _pwm_control(struct rt_device_pwm *device, int cmd, void *arg)
{
    struct rt_pwm_configuration *configuration = (struct rt_pwm_configuration *)arg;

    rt_uint32_t channel = 0;

    channel = configuration->channel;

    if (channel >= 4)
        return -RT_EINVAL;

    struct bflb_device_s* pwm = bflb_device_get_by_name("pwm_v2_0");
    switch (cmd)
    {
    case PWM_CMD_ENABLE:
        bflb_pwm_v2_channel_positive_start(pwm, channel);
        bflb_pwm_v2_channel_negative_start(pwm, channel);
        return RT_EOK;
    case PWM_CMD_DISABLE:
        bflb_pwm_v2_channel_positive_stop(pwm, channel);
        bflb_pwm_v2_channel_negative_stop(pwm, channel);
        return RT_EOK;
    case PWM_CMD_SET:
        return _pwm_set(channel, configuration);
    case PWM_CMD_GET:
        return _pwm_get(channel, configuration);
    default:
        return -RT_EINVAL;
    }
}

static struct rt_pwm_ops _pwm_ops =
{
    _pwm_control
};
static struct rt_device_pwm pwm_device;

int rt_hw_pwm_init(void)
{
    int result = RT_EOK;

    struct bflb_device_s* gpio = bflb_device_get_by_name("gpio");
    bflb_gpio_init(gpio, GPIO_PIN_8, GPIO_FUNC_PWM0 | GPIO_ALTERNATE | GPIO_PULLDOWN | GPIO_SMT_EN | GPIO_DRV_1);
    struct bflb_device_s* pwm = bflb_device_get_by_name("pwm_v2_0");
    bflb_pwm_v2_start(pwm);

    result = rt_device_pwm_register(&pwm_device, "pwm", &_pwm_ops, 0);
    if(result != RT_EOK)
    {
        LOG_E("pwm device register fail.");
    }
    return result;
}
INIT_DEVICE_EXPORT(rt_hw_pwm_init);

#endif /* BSP_USING_PWM */
