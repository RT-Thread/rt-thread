/*
 * Copyright (c) 2006-2022, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2022-11-26     GuEe-GUI     first version
 */

#include <rthw.h>
#include <rtthread.h>
#include <rtdevice.h>

#define DBG_TAG "pwm.bcm2835"
#define DBG_LVL DBG_INFO
#include <rtdbg.h>

#define PWM_CONTROL             0x000
#define PWM_CONTROL_SHIFT(x)    ((x) * 8)
#define PWM_CONTROL_MASK        0xff
#define PWM_MODE                0x80    /* Set timer in PWM mode */
#define PWM_ENABLE              (1 << 0)
#define PWM_POLARITY            (1 << 4)

#define PERIOD(x)               (((x) * 0x10) + 0x10)
#define DUTY(x)                 (((x) * 0x10) + 0x14)

#define PERIOD_MIN              0x2
#define PWM_NUMBER              2

#define NSEC_PER_SEC            1000000000L

struct bcm2835_pwm
{
    struct rt_device_pwm parent;

    void *base;
    struct rt_clk *clk;
};

#define raw_to_bcm2835_pwm(raw) rt_container_of(raw, struct bcm2835_pwm, parent)

static rt_err_t bcm2835_pwm_enable(struct bcm2835_pwm *bpwm, int channel, rt_bool_t enable)
{
    rt_uint32_t value;

    if (channel >= PWM_NUMBER)
    {
        return -RT_EINVAL;
    }

    if (enable)
    {
        value = HWREG32(bpwm->base + PWM_CONTROL);
        value &= ~(PWM_CONTROL_MASK << PWM_CONTROL_SHIFT(channel));
        value |= ((PWM_MODE | PWM_ENABLE) << PWM_CONTROL_SHIFT(channel));
        HWREG32(bpwm->base + PWM_CONTROL) = value;
    }
    else
    {
        value = HWREG32(bpwm->base + PWM_CONTROL);
        value &= ~((PWM_CONTROL_MASK | PWM_ENABLE) << PWM_CONTROL_SHIFT(channel));
        HWREG32(bpwm->base + PWM_CONTROL) = value;
    }

    return RT_EOK;
}

static rt_err_t bcm2835_pwm_config(struct bcm2835_pwm *bpwm,
        struct rt_pwm_configuration *pwm_cfg)
{
    int channel;
    rt_uint32_t val;
    rt_uint64_t period_cycles, max_period;
    rt_ubase_t rate = rt_clk_get_rate(bpwm->clk);

    if (!rate)
    {
        LOG_E("Failed to get clock rate");

        return -RT_EINVAL;
    }

    channel = pwm_cfg->channel;

    /*
     * period_cycles must be a 32 bit value, so period * rate / NSEC_PER_SEC
     * must be <= RT_UINT32_MAX. As RT_UINT32_MAX * NSEC_PER_SEC < U64_MAX the
     * multiplication period * rate doesn't overflow.
     * To calculate the maximal possible period that guarantees the
     * above inequality:
     *
     *     round(period * rate / NSEC_PER_SEC) <= RT_UINT32_MAX
     * <=> period * rate / NSEC_PER_SEC < RT_UINT32_MAX + 0.5
     * <=> period * rate < (RT_UINT32_MAX + 0.5) * NSEC_PER_SEC
     * <=> period < ((RT_UINT32_MAX + 0.5) * NSEC_PER_SEC) / rate
     * <=> period < ((RT_UINT32_MAX * NSEC_PER_SEC + NSEC_PER_SEC/2) / rate
     * <=> period <= ceil((RT_UINT32_MAX * NSEC_PER_SEC + NSEC_PER_SEC/2) / rate) - 1
     */
    max_period = RT_DIV_ROUND_UP_ULL(
            (rt_uint64_t)RT_UINT32_MAX * NSEC_PER_SEC + NSEC_PER_SEC / 2, rate) - 1;

    if (pwm_cfg->period > max_period)
    {
        return -RT_EINVAL;
    }

    /* Set period */
    period_cycles = RT_DIV_ROUND_CLOSEST_ULL(pwm_cfg->period * rate, NSEC_PER_SEC);

    /* Don't accept a period that is too small */
    if (period_cycles < PERIOD_MIN)
    {
        return -RT_EINVAL;
    }

    HWREG32(bpwm->base + PERIOD(channel)) = period_cycles;

    /* Set duty cycle */
    val = RT_DIV_ROUND_CLOSEST_ULL(pwm_cfg->pulse * rate, NSEC_PER_SEC);
    HWREG32(bpwm->base + DUTY(channel)) = val;

    /* Set polarity */
    val = HWREG32(bpwm->base + PWM_CONTROL);

    if (!pwm_cfg->complementary)
    {
        val &= ~(PWM_POLARITY << PWM_CONTROL_SHIFT(channel));
    }
    else
    {
        val |= PWM_POLARITY << PWM_CONTROL_SHIFT(channel);
    }

    HWREG32(bpwm->base + PWM_CONTROL) = val;

    return RT_EOK;
}

static rt_err_t bcm2835_pwm_control(struct rt_device_pwm *pwm, int cmd, void *args)
{
    rt_err_t err = RT_EOK;
    struct bcm2835_pwm *bpwm = raw_to_bcm2835_pwm(pwm);
    struct rt_pwm_configuration *pwm_cfg = args;

    switch (cmd)
    {
    case PWM_CMD_ENABLE:
        err = bcm2835_pwm_enable(bpwm, pwm_cfg->channel, RT_TRUE);
        break;

    case PWM_CMD_DISABLE:
        err = bcm2835_pwm_enable(bpwm, pwm_cfg->channel, RT_FALSE);
        break;

    case PWM_CMD_SET:
    case PWM_CMD_SET_PERIOD:
    case PWM_CMD_SET_PULSE:
        err = bcm2835_pwm_config(bpwm, pwm_cfg);
        break;

    default:
        err = -RT_EINVAL;
        break;
    }

    return err;
}

const static struct rt_pwm_ops bcm2835_pwm_ops =
{
    .control = bcm2835_pwm_control,
};

static rt_err_t bcm2835_pwm_probe(struct rt_platform_device *pdev)
{
    rt_err_t err;
    struct rt_device *dev = &pdev->parent;
    struct bcm2835_pwm *bpwm = rt_calloc(1, sizeof(*bpwm));

    if (!bpwm)
    {
        return -RT_ENOMEM;
    }

    bpwm->base = rt_dm_dev_iomap(dev, 0);

    if (!bpwm->base)
    {
        err = -RT_EIO;
        goto _fail;
    }

    bpwm->clk = rt_clk_get_by_index(dev, 0);

    if (rt_is_err(bpwm->clk))
    {
        err = rt_ptr_err(bpwm->clk);
        goto _fail;
    }

    if ((err = rt_clk_prepare_enable(bpwm->clk)))
    {
        goto _fail;
    }

    dev->user_data = bpwm;

    bpwm->parent.parent.ofw_node = dev->ofw_node;

    rt_dm_dev_set_name_auto(&bpwm->parent.parent, "pwm");
    rt_device_pwm_register(&bpwm->parent, rt_dm_dev_get_name(&bpwm->parent.parent), &bcm2835_pwm_ops, bpwm);

    rt_dm_dev_bind_fwdata(dev, RT_NULL, bpwm);

    return RT_EOK;

_fail:
    if (bpwm->base)
    {
        rt_iounmap(bpwm->base);
    }

    if (!rt_is_err_or_null(bpwm->clk))
    {
        rt_clk_disable_unprepare(bpwm->clk);
        rt_clk_put(bpwm->clk);
    }

    rt_free(bpwm);

    return err;
}

static rt_err_t bcm2835_pwm_remove(struct rt_platform_device *pdev)
{
    struct rt_device *dev = &pdev->parent;
    struct bcm2835_pwm *bpwm = dev->user_data;

    rt_dm_dev_unbind_fwdata(dev, RT_NULL);

    for (int channel = 0; channel < PWM_NUMBER; ++channel)
    {
        bcm2835_pwm_enable(bpwm, channel, RT_FALSE);
    }

    rt_device_unregister(&bpwm->parent.parent);

    rt_clk_disable_unprepare(bpwm->clk);
    rt_clk_put(bpwm->clk);

    rt_free(bpwm);

    return RT_EOK;
}

static const struct rt_ofw_node_id bcm2835_pwm_ofw_ids[] =
{
    { .compatible = "brcm,bcm2835-pwm", },
    { /* sentinel */ }
};

static struct rt_platform_driver bcm2835_pwm_driver =
{
    .name = "bcm2835-pwm",
    .ids = bcm2835_pwm_ofw_ids,

    .probe = bcm2835_pwm_probe,
    .remove = bcm2835_pwm_remove,
};
RT_PLATFORM_DRIVER_EXPORT(bcm2835_pwm_driver);
