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
 * 测试 PWM 驱动对板载 LED 的亮度控制功能
 *
 * 1. 查找名为 "pwm" 的 PWM 设备。
 * 2. 使用 pinctrl 将 GPIO52 映射为 PWM4 通道，并配置引脚属性：
 *    - 使能输出（OE）；
 *    - 禁用输入（IE）；
 *    - 禁用上下拉（PU/PD）；
 *    - 设置中等驱动能力（驱动强度为 4）。
 * 3. 设置 PWM 输出周期为 100000ns（对应频率为 10kHz）。
 * 4. 通过逐步增加 PWM 的脉冲宽度（pulse），控制板载 LED 的亮度由暗到亮：
 *    - 从 10% 占空比（10000ns）开始；
 *    - 每次增加 10%，直到 100%（全亮）；
 *    - 每次间隔 2 秒以便观察 LED 亮度变化。
 * 5. 最后禁用 PWM 输出，关闭 LED。
 *
 * 硬件说明：
 * - 本测试基于 K230-01studio 开发板；
 * - GPIO52 已通过电路连接一颗板载 LED；
 * - PWM4 通道控制该 LED 的亮灭和亮度；
 * - 测试过程中，可肉眼观察 LED 明暗变化。
 *
 */

#define PWM_DEV_NAME        "pwm1"    /* PWM设备名称 */
#define PWM_DEV_CHANNEL      1        /* PWM通道 */
#define TEST_GPIO_LED        52

void pwm_demo(void)
{
    LOG_I("set gpio52 in PWM1 start.\n");
    k230_pinctrl_set_function(TEST_GPIO_LED, IOMUX_FUNC3);
    /* 使能输出 */
    k230_pinctrl_set_oe(TEST_GPIO_LED, 1);
    /* 禁止输入 */
    k230_pinctrl_set_ie(TEST_GPIO_LED, 0);
    /* 禁止上拉 */
    k230_pinctrl_set_pu(TEST_GPIO_LED, 0);
    /* 禁止下拉 */
    k230_pinctrl_set_pd(TEST_GPIO_LED, 0);
    /* 设置驱动能力为4（中等强度） */
    k230_pinctrl_set_drv(TEST_GPIO_LED, 4);
    LOG_I("pwm test start.\n");
    struct rt_device_pwm *pwm_dev;       /* PWM设备句柄 */
    rt_uint32_t period;                  /* 周期, 单位为纳秒ns */
    rt_uint32_t pulse;                   /* PWM脉冲宽度值, 单位为纳秒ns */
    rt_err_t ret;
    /* 查找设备 */
    pwm_dev = (struct rt_device_pwm *)rt_device_find(PWM_DEV_NAME);
    uassert_not_null(pwm_dev);
    /* 设置PWM周期和脉冲宽度 */
    period = 100000;                     /* PWM 周期：100000ns = 100us，即 10kHz */
    /* 逐步循环提高PWM脉冲宽度 */
    for(pulse = 10000; pulse <= 100000; pulse+=10000)
    {
        ret = rt_pwm_set(pwm_dev, PWM_DEV_CHANNEL, period, pulse);
        uassert_int_equal(ret, RT_EOK);
        ret = rt_pwm_enable(pwm_dev, PWM_DEV_CHANNEL);
        uassert_int_equal(ret, RT_EOK);
        sleep(2);
    }
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

UTEST_TC_EXPORT(pwm_testcase, "pwm", utest_tc_init, utest_tc_cleanup, 10);