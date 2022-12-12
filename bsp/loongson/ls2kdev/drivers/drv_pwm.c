/*
 * Copyright (c) 2006-2018, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Copyright(c) 2020, Du Huanpeng<548708880@qq.com>
 *
 */

#include <rtthread.h>
#include <rtdevice.h>
#include <ls2k1000.h>

#ifdef RT_USING_PWM

#define PWM0_BASE   (0xFFFFFFFFBFe02000)
#define PWM1_BASE   (0xFFFFFFFFBFe02010)
#define PWM2_BASE   (0xFFFFFFFFBFe02020)
#define PWM3_BASE   (0xFFFFFFFFBFe02030)

#define CTRL_EN     (1UL<<0)
#define CTRL_OE     (1UL<<3)
#define CTRL_SINGL  (1UL<<4)
#define CTRL_INTE   (1UL<<5)
#define CTRL_INT    (1UL<<6)
#define CTRL_RST    (1UL<<7)
#define CTRL_CAPTE  (1UL<<8)
#define CTRL_INVERT (1UL<<9)
#define CTRL_DZONE  (1UL<<10)

struct loongson_pwm
{
    rt_uint32_t __PAD0;
    rt_uint32_t low_buffer;
    rt_uint32_t full_buffer;
    rt_uint32_t ctrl;
};

rt_err_t loongson_pwm_enable(struct rt_device_pwm *device, int channel)
{
    int **priv;
    struct loongson_pwm *chip;
    volatile rt_uint64_t *config0;
    rt_uint64_t m;

    channel %= 4;

    config0 = (void *)GEN_CONFIG0_REG;
    m = 1ULL << 12 << channel;
    *config0 |= m;

    priv = device->parent.user_data;
    chip = (void *)priv[channel];
    chip->ctrl = CTRL_EN;

    return RT_EOK;
}

rt_err_t loongson_pwm_disable(struct rt_device_pwm *device, int channel)
{
    struct loongson_pwm **chip;
    rt_uint64_t m;

    chip = device->parent.user_data;
    channel %= 4;
    chip[channel]->ctrl &= ~CTRL_EN;

    return RT_EOK;
}

rt_err_t loongson_pwm_set(struct rt_device_pwm *device, int channel, rt_uint32_t period, rt_uint32_t pulse)
{
    struct loongson_pwm *chip;
    rt_uint32_t **priv;

    priv = device->parent.user_data;
    channel %= 4;
    chip = (void *)priv[channel];

    chip->ctrl       &= ~CTRL_EN;
    chip->full_buffer =  period;
    chip->low_buffer  =  pulse;
    chip->ctrl       |=  CTRL_EN;

    return RT_EOK;
}

static rt_err_t loongson_pwm_ioctl(struct rt_device_pwm *device, int cmd, void *arg)
{
    rt_err_t rc;
    struct rt_pwm_configuration *cfg;

    cfg = (void *)arg;

    switch (cmd)
    {
    case PWM_CMD_ENABLE:
        rc = loongson_pwm_enable(device, cfg->channel);
        break;
    case PWM_CMD_DISABLE:
        rc = loongson_pwm_disable(device, cfg->channel);
        break;
    case PWM_CMD_SET:
        rc = loongson_pwm_set(device, cfg->channel, cfg->period, cfg->pulse);
        break;
    case PWM_CMD_GET:
        rc = RT_ENOSYS;
        break;
    default:
        rc = RT_EINVAL;
        break;
    }
    return rc;
}

struct rt_pwm_ops loongson_pwm_ops =
{
    .control = loongson_pwm_ioctl,
};

struct rt_device_pwm loongson_pwm =
{
    .ops = &loongson_pwm_ops,
};

int loongson_pwm_init(void)
{
    int rc = RT_EOK;
    static rt_uint32_t *priv[] =
    {
        (void *)PWM0_BASE,
        (void *)PWM1_BASE,
        (void *)PWM2_BASE,
        (void *)PWM3_BASE
    };
    rc = rt_device_pwm_register(&loongson_pwm, "pwm0", &loongson_pwm_ops, &priv);
    return rc;
}
INIT_DEVICE_EXPORT(loongson_pwm_init);

#endif /*RT_USING_PWM*/
