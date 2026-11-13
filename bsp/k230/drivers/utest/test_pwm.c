/* Copyright (c) 2023, Canaan Bright Sight Co., Ltd
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 * 1. Redistributions of source code must retain the above copyright
 * notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 * notice, this list of conditions and the following disclaimer in the
 * documentation and/or other materials provided with the distribution.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND
 * CONTRIBUTORS "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES,
 * INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF
 * MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR
 * CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
 * SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING,
 * BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
 * SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
 * INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,
 * WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING
 * NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
 * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

/*
 * Copyright (c) 2006-2025 RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#include <unistd.h>
#include <stdio.h>
#include <drivers/dev_pwm.h>
#include "drv_pwm.h"
#include "drv_pinctrl.h"
#include <rtdbg.h>
#include "utest.h"

/*
 * GPIO52 is connected to the blue LED on the 01Studio CanMV K230.
 * PWM4 is logical channel 1 of pwm1. Check both the visible output and
 * the period/pulse readback, including a period that requires scaling.
 */

#include "sysctl_clk.h"

#define PWM_DEV_NAME         "pwm1"
#define PWM_DEV_CHANNEL      1
#define TEST_GPIO_LED        52
#define PWM_CMP_MAX          0xFFFF

struct pwm_test_point
{
    rt_uint32_t period;
    rt_uint32_t pulse;
};

static rt_uint32_t pwm_readback_tolerance(rt_uint32_t period, rt_uint32_t *scale)
{
    rt_uint32_t clock = sysctl_clk_get_leaf_freq(SYSCTL_CLK_PWM_APB_GATE);
    rt_uint64_t period_count = (rt_uint64_t)period * clock / NSEC_PER_SEC;

    *scale = 0;
    while ((period_count >> *scale) > PWM_CMP_MAX)
    {
        (*scale)++;
    }

    /* One scaled count, one unscaled truncation count, and rounding margin. */
    return NSEC_PER_SEC / (clock >> *scale) + NSEC_PER_SEC / clock + 2;
}

static void pwm_check_readback(struct rt_device_pwm *pwm_dev,
                               const struct pwm_test_point *point)
{
    struct rt_pwm_configuration configuration = { 0 };
    rt_uint32_t period_error, pulse_error, scale, tolerance;
    rt_err_t ret;

    configuration.channel = PWM_DEV_CHANNEL;
    ret = rt_pwm_get(pwm_dev, &configuration);
    uassert_int_equal(ret, RT_EOK);
    if (ret != RT_EOK)
    {
        return;
    }

    tolerance = pwm_readback_tolerance(point->period, &scale);
    period_error = configuration.period > point->period ? configuration.period - point->period : point->period - configuration.period;
    pulse_error = configuration.pulse > point->pulse ? configuration.pulse - point->pulse : point->pulse - configuration.pulse;

    rt_kprintf("PWM readback: scale=%u, requested=%u/%u ns, actual=%u/%u ns, tolerance=%u ns\n",
               scale, point->period, point->pulse,
               configuration.period, configuration.pulse, tolerance);
    uassert_true(period_error <= tolerance);
    uassert_true(pulse_error <= tolerance);
}

static void pwm_check_cross_channel(struct rt_device_pwm *pwm_dev)
{
    struct rt_pwm_configuration configuration = { 0 };
    rt_err_t ret;

    ret = rt_pwm_set(pwm_dev, PWM_DEV_CHANNEL, 100000, 25000);
    uassert_int_equal(ret, RT_EOK);
    if (ret != RT_EOK)
    {
        return;
    }

    /* This shorter shared period leaves channel 1's compare above pwmcmp0. */
    ret = rt_pwm_set(pwm_dev, 0, 50000, 12500);
    uassert_int_equal(ret, RT_EOK);
    if (ret != RT_EOK)
    {
        return;
    }

    configuration.channel = PWM_DEV_CHANNEL;
    ret = rt_pwm_get(pwm_dev, &configuration);
    rt_kprintf("PWM cross-channel readback: ret=%d, actual=%u/%u ns\n",
               ret, configuration.period, configuration.pulse);
    uassert_int_equal(ret, RT_EOK);
    if (ret != RT_EOK)
    {
        return;
    }

    uassert_int_equal(configuration.period, 50000);
    uassert_int_equal(configuration.pulse, 0);
}

void pwm_demo(void)
{
    static const struct pwm_test_point points[] = {
        { 100000, 0 },
        { 100000, 25000 },
        { 100000, 75000 },
        { 100000, 100000 },
        { 10000000, 2500000 },
    };
    struct rt_device_pwm *pwm_dev;
    rt_err_t ret;
    rt_size_t i;

    rt_kprintf("Set GPIO52 to PWM4 (pwm1 channel 1).\n");
    k230_pinctrl_set_function(TEST_GPIO_LED, IOMUX_FUNC3);
    k230_pinctrl_set_oe(TEST_GPIO_LED, 1);
    k230_pinctrl_set_ie(TEST_GPIO_LED, 0);
    k230_pinctrl_set_pu(TEST_GPIO_LED, 0);
    k230_pinctrl_set_pd(TEST_GPIO_LED, 0);
    k230_pinctrl_set_drv(TEST_GPIO_LED, 4);

    pwm_dev = (struct rt_device_pwm *)rt_device_find(PWM_DEV_NAME);
    uassert_not_null(pwm_dev);
    if (pwm_dev == RT_NULL)
    {
        return;
    }

    for (i = 0; i < sizeof(points) / sizeof(points[0]); i++)
    {
        ret = rt_pwm_set(pwm_dev, PWM_DEV_CHANNEL, points[i].period, points[i].pulse);
        uassert_int_equal(ret, RT_EOK);
        if (ret != RT_EOK)
        {
            continue;
        }

        pwm_check_readback(pwm_dev, &points[i]);
        ret = rt_pwm_enable(pwm_dev, PWM_DEV_CHANNEL);
        uassert_int_equal(ret, RT_EOK);
        sleep(1);
    }

    pwm_check_cross_channel(pwm_dev);

    ret = rt_pwm_disable(pwm_dev, PWM_DEV_CHANNEL);
    uassert_int_equal(ret, RT_EOK);
}

static void pwm_testcase(void)
{
    UTEST_UNIT_RUN(pwm_demo);
}

static rt_err_t utest_tc_init(void)
{
    return RT_EOK;
}

static rt_err_t utest_tc_cleanup(void)
{
    return RT_EOK;
}

UTEST_TC_EXPORT(pwm_testcase, "bsp.k230.drivers.pwm", utest_tc_init, utest_tc_cleanup, 30);
