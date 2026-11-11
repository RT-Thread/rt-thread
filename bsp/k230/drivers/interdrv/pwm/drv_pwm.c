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
#include <rtthread.h>
#include <rtdevice.h>
#include "riscv_io.h"
#include "board.h"
#include "ioremap.h"
#include <rtdbg.h>
#include <stdbool.h>
#include "sysctl_clk.h"
#include "drv_pwm.h"
#include <sys/ioctl.h>

/**
 *
 * pwm0
 *  ├── channel 0
 *  ├── channel 1
 *  └── channel 2
 * pwm1
 *  ├── channel 0
 *  ├── channel 1
 *  └── channel 2
 *
 * Note:
 * The K230 PWM controller has 4 hardware channels:
 * - Channel 0 (pwmcmp0) is used to set the period and does not generate output.
 * - Channels 1 to 3 (pwmcmp1~3) are used to control the duty cycle and produce output signals.
 * Therefore, the driver maps these output channels (1~3) as logical channels 0~2.
 */

#define PWM_REG_OFFSET       0x40
#define PWM_CFG_BIT_INVERT   (1 << 12)
#define PWM_CFG_DEGLITCH     (1 << 9)
#define PWM_MAX_SCALE        0xF
#define PWM_CMP_WIDTH        16
#define PWM_PERIOD_BITS      16
#define PWM_SCALE_MAX_BITS   15
#define PWM_DEV_NUM          2
#define PWM_MAX_CHANNELS     3

#define PWM0_BASE_ADDR       PWM_BASE_ADDR
#define PWM1_BASE_ADDR       PWM_BASE_ADDR + PWM_REG_OFFSET

struct k230_pwm_dev
{
    struct rt_device_pwm device;
    const char *name;
    rt_ubase_t base;
};

static struct k230_pwm_dev pwm_devs[] = {
#ifdef BSP_USING_PWM0
    {
        .name = "pwm0",
        .base = PWM0_BASE_ADDR,
    },
#endif

#ifdef BSP_USING_PWM1
    {
        .name = "pwm1",
        .base = PWM1_BASE_ADDR,
    },
#endif

#if !defined(BSP_USING_PWM0) && !defined(BSP_USING_PWM1)
#error "No pwm device defined!"
#endif
};

static int check_channel(int channel)
{
    if (channel < 0 || channel >= PWM_MAX_CHANNELS)
    {
        LOG_E("channel %d is not valid\n", channel);
        return -RT_ERROR;
    }
    return channel;
}

static rt_err_t pwm_start(kd_pwm_t *reg, int channel)
{
    rt_err_t ret;
    ret = (rt_err_t)check_channel(channel);
    if (ret < 0)
        return ret;
    reg->pwmcfg |= PWM_CFG_BIT_INVERT;  /* default always mode */
    return RT_EOK;
}

static rt_err_t pwm_stop(kd_pwm_t *reg, int channel)
{
    rt_err_t ret;
    ret = (rt_err_t)check_channel(channel);
    if (ret < 0)
        return ret;
    reg->pwmcfg &= ~PWM_CFG_BIT_INVERT;

    return RT_EOK;
}

static rt_err_t kd_pwm_get(kd_pwm_t *reg, int channel, struct rt_pwm_configuration *configuration)
{
    int ret;
    uint64_t pulse, period;
    uint32_t pwm_pclock, pwmscale;

    ret = check_channel(channel);
    if (ret < 0)
        return ret;

    pwm_pclock = sysctl_clk_get_leaf_freq(SYSCTL_CLK_PWM_APB_GATE);

    pwmscale = reg->pwmcfg & 0xf;
    pwm_pclock >>= pwmscale;
    period = reg->pwmcmp0;
    period = period * NSEC_PER_SEC / pwm_pclock;
    pulse = *((&reg->pwmcmp1) + channel);
    pulse = pulse * NSEC_PER_SEC / pwm_pclock;

    configuration->period = period;
    configuration->pulse = pulse;

    return RT_EOK;
}

static rt_err_t kd_pwm_set(kd_pwm_t *reg, int channel, struct rt_pwm_configuration *configuration)
{
    int ret;
    uint64_t pulse, period, pwmcmpx_max;
    uint32_t pwm_pclock, pwmscale = 0;

    ret = check_channel(channel);
    if (ret < 0)
        return ret;

    pwm_pclock = sysctl_clk_get_leaf_freq(SYSCTL_CLK_PWM_APB_GATE);
    pulse = (uint64_t)configuration->pulse * pwm_pclock / NSEC_PER_SEC;
    period = (uint64_t)configuration->period * pwm_pclock / NSEC_PER_SEC;
    if (pulse > period)
        return -RT_EINVAL;


    /* Calculate duty cycle */
    pwmcmpx_max = (1 << PWM_CMP_WIDTH) - 1;
    if (period > ((1 << (PWM_SCALE_MAX_BITS + PWM_PERIOD_BITS)) - 1LL))
        return -RT_EINVAL;

    while ((period >> pwmscale) > pwmcmpx_max)
        pwmscale++;
    if (pwmscale > PWM_MAX_SCALE)
        return -RT_EINVAL;

    reg->pwmcfg |= PWM_CFG_DEGLITCH;  /* default always mode */
    reg->pwmcfg &= (~PWM_MAX_SCALE);
    reg->pwmcfg |= pwmscale;  /* scale */
    reg->pwmcmp0 = (period >> pwmscale);
    *((&reg->pwmcmp1) + channel) = reg->pwmcmp0 - (pulse >> pwmscale);

    return RT_EOK;
}

static rt_err_t kd_pwm_control(struct rt_device_pwm *device, int cmd, void *arg)
{
    struct rt_pwm_configuration *configuration = (struct rt_pwm_configuration *)arg;
    int channel = 0;
    int ret;

    struct k230_pwm_dev *pwm_dev = rt_container_of(device, struct k230_pwm_dev, device);
    kd_pwm_t *reg = (kd_pwm_t *)pwm_dev->base;
    channel = configuration->channel;

    switch (cmd)
    {
    case PWM_CMD_ENABLE:
        ret = pwm_start(reg, channel);
        break;
    case PWM_CMD_DISABLE:
        ret = pwm_stop(reg, channel);
        break;
    case PWM_CMD_SET:
        ret = kd_pwm_set(reg, channel, configuration);
        break;
    case PWM_CMD_GET:
        ret = kd_pwm_get(reg, channel, configuration);
        break;
    default:
        ret = -RT_EINVAL;
    }

    return ret;
}

static struct rt_pwm_ops drv_ops =
{
    .control = kd_pwm_control
};

int rt_hw_pwm_init(void)
{
    rt_err_t ret;
    for (int i = 0; i < sizeof(pwm_devs)/sizeof(struct k230_pwm_dev); i++)
    {
        struct k230_pwm_dev *dev = &pwm_devs[i];
        dev->base = (rt_ubase_t)rt_ioremap((void *)(dev->base), sizeof(kd_pwm_t));
        ret = rt_device_pwm_register(&dev->device, dev->name, &drv_ops, RT_NULL);
        if (ret != RT_EOK)
        {
            LOG_E("Failed to register PWM device %s, error code: %d\n", dev->name, ret);
            return ret;
        }
    }
    return RT_EOK;
}
INIT_DEVICE_EXPORT(rt_hw_pwm_init);