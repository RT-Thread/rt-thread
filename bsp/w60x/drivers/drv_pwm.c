/*
 * Copyright (c) 2019 Winner Microelectronics Co., Ltd.
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2018-11-22     fanwenl      1st version
 */

#include <rtthread.h>
#include <rtdevice.h>
#include "wm_type_def.h"
#include "wm_cpu.h"
#include "wm_pwm.h"
#include "wm_gpio_afsel.h"
#include "drv_pwm.h"
#include "pin_map.h"

#ifdef BSP_USING_PWM
#define MAX_PERIOD 255
#define MIN_PERIOD 2
#define MIN_PULSE 1

#define MAX_CLKDIV 65535

static rt_err_t wm_pwm_set(rt_uint8_t channel, struct rt_pwm_configuration *configuration)
{
    rt_uint32_t period, pulse;
    rt_uint32_t psc;

    pwm_init_param pwm_param;
    int ret = WM_FAILED;
    tls_sys_clk sysclk;

    tls_sys_clk_get(&sysclk);

    rt_memset(&pwm_param, 0, sizeof(pwm_init_param));

    pwm_param.channel = channel;
    pwm_param.cnt_type = WM_PWM_CNT_TYPE_EDGE_ALIGN_OUT;
    pwm_param.loop_type = WM_PWM_LOOP_TYPE_LOOP;
    pwm_param.mode = WM_PWM_OUT_MODE_INDPT;
    pwm_param.inverse_en = DISABLE;
    pwm_param.pnum = 0;
    pwm_param.pnum_int = DISABLE;

    period = (unsigned long long)configuration->period * sysclk.apbclk / 1000ULL;
    psc = period / MAX_PERIOD + 1;
    if (psc > MAX_CLKDIV)
    {
        psc = MAX_CLKDIV;
    }
    pwm_param.clkdiv = psc;

    period = period / psc;

    if (period < MIN_PERIOD)
    {
        period = MIN_PERIOD;
    }
    else if (period > MAX_PERIOD)
    {
        period = MAX_PERIOD;
    }
    pwm_param.period = period - 1;

    pulse = (unsigned long long)configuration->pulse * sysclk.apbclk / psc / 1000ULL;
    if (pulse < MIN_PULSE)
    {
        pulse = MIN_PULSE;
    }
    else if (pulse > period)
    {
        pulse = period;
    }
    pwm_param.duty = pulse - 1;

    ret = tls_pwm_out_init(pwm_param);
    if (ret == WM_SUCCESS)
    {
        return RT_EOK;
    }
    else
    {
        return RT_ERROR;
    }
}

static rt_err_t wm_pwm_get(rt_uint8_t channel, struct rt_pwm_configuration *configuration)
{
    tls_sys_clk sysclk;
    uint32_t clkdiv;
    uint8_t duty, period;

    tls_sys_clk_get(&sysclk);

    tls_pwm_get_info(channel, &clkdiv, &duty, &period);

    configuration->period = (period + 1) * clkdiv * 1000UL / sysclk.apbclk;
    configuration->pulse = (duty + 1) * clkdiv * 1000UL / sysclk.apbclk;

    return RT_EOK;
}

static rt_err_t wm_pwm_control(struct rt_device_pwm *device, int cmd, void *arg)
{
    struct rt_pwm_configuration *configuration = (struct rt_pwm_configuration *)arg;

    int ret = WM_FAILED;
    rt_uint32_t channel = 0;

    channel = configuration->channel - 1;

    if (channel > 4)
        return RT_EINVAL;

    switch (cmd)
    {
    case PWM_CMD_ENABLE:
        ret = tls_pwm_start(channel);
        if (ret == WM_SUCCESS)
            return RT_EOK;
        else
            return RT_ERROR;
    case PWM_CMD_DISABLE:
        ret = tls_pwm_stop(channel);
        if (ret == WM_SUCCESS)
            return RT_EOK;
        else
            return RT_ERROR;
    case PWM_CMD_SET:
        return wm_pwm_set(channel, configuration);
    case PWM_CMD_GET:
        return wm_pwm_get(channel, configuration);
    default:
        return RT_EINVAL;
    }
}

static struct rt_pwm_ops drv_ops =
{
    wm_pwm_control
};
static struct rt_device_pwm wm_pwm;

int wm_hw_pwm_init(void)
{
    rt_int16_t gpio_pin;
    /*io config*/
#ifdef USING_PWM_CH1
    gpio_pin = wm_get_pin(WM_PWM_CH1_PIN);
    if (gpio_pin >= 0)
    {
        wm_pwm1_config((enum tls_io_name)gpio_pin);
    }
#endif
#ifdef USING_PWM_CH2
    gpio_pin = wm_get_pin(WM_PWM_CH2_PIN);
    if (gpio_pin >= 0)
    {
        wm_pwm2_config((enum tls_io_name)gpio_pin);
    }
#endif
#ifdef USING_PWM_CH3
    gpio_pin = wm_get_pin(WM_PWM_CH3_PIN);
    if (gpio_pin >= 0)
    {
        wm_pwm3_config((enum tls_io_name)gpio_pin);
    }
#endif
#ifdef USING_PWM_CH4
    gpio_pin = wm_get_pin(WM_PWM_CH4_PIN);
    if (gpio_pin >= 0)
    {
        wm_pwm4_config((enum tls_io_name)gpio_pin);
    }
#endif
#ifdef USING_PWM_CH5
    gpio_pin = wm_get_pin(WM_PWM_CH5_PIN);
    if (gpio_pin >= 0)
    {
        wm_pwm5_config((enum tls_io_name)gpio_pin);
    }
#endif
#if defined(USING_PWM_CH1) || defined(USING_PWM_CH2) || defined(USING_PWM_CH3) || \
    defined(USING_PWM_CH4) || defined(USING_PWM_CH5)
    rt_device_pwm_register(&wm_pwm, "pwm", &drv_ops, 0);
#endif
    return RT_EOK;
}
INIT_DEVICE_EXPORT(wm_hw_pwm_init);

#endif /* BSP_USING_PWM */
