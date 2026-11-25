/*
 * Copyright (c) 2006-2026, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#include <rtthread.h>
#include <rtdevice.h>

#define PWM_PCCR01                 0x020
#define PWM_PCGR                   0x040
#define PWM_PER                    0x080
#define PWM_CH0_CTRL               0x100
#define PWM_CH0_PERIOD             0x104
#define PWM_CH_STEP                0x020

#define PWM_CLK_SRC_SHIFT          7
#define PWM_CLK_SRC_MASK           RT_GENMASK(8, 7)
#define PWM_DIV_M_MASK             RT_GENMASK(3, 0)
#define PWM_PRESCALE_MASK          RT_GENMASK(7, 0)
#define PWM_ACT_STA                RT_BIT(8)
#define PWM_ACT_CYCLES_MASK        RT_GENMASK(15, 0)
#define PWM_PERIOD_CYCLES_MASK     RT_GENMASK(31, 16)
#define PWM_PERIOD_CYCLES_SHIFT    16
#define PWM_CGR_BYPASS_SHIFT       16

#define SUNXI_PWM_CHANNELS_MAX     6
#define SUNXI_PWM_CLK_24M          24000000ULL
#define SUNXI_PWM_CLK_100M         100000000ULL
#define SUNXI_PWM_NSEC_PER_SEC     1000000000ULL
#define SUNXI_PWM_COUNTER_MAX      65536U

static const rt_uint16_t sunxi_pwm_dividers[] =
{
    1, 2, 4, 8, 16, 32, 64, 128, 256,
};

struct sunxi_pwm
{
    struct rt_device_pwm parent;
    void *base;
    struct rt_clk *clk;
    struct rt_reset_control *reset;
    struct rt_spinlock lock;
    rt_uint32_t channels;
};

#define to_sunxi_pwm(raw) rt_container_of(raw, struct sunxi_pwm, parent)

rt_inline rt_uint32_t sunxi_pwm_pccr(int channel)
{
    return PWM_PCCR01 + ((channel >> 1) * sizeof(rt_uint32_t));
}

rt_inline rt_uint32_t sunxi_pwm_ctrl(int channel)
{
    return PWM_CH0_CTRL + channel * PWM_CH_STEP;
}

rt_inline rt_uint32_t sunxi_pwm_period(int channel)
{
    return PWM_CH0_PERIOD + channel * PWM_CH_STEP;
}

rt_inline rt_uint32_t sunxi_pwm_read(struct sunxi_pwm *pwm, rt_uint32_t offset)
{
    return HWREG32(pwm->base + offset);
}

rt_inline void sunxi_pwm_write(struct sunxi_pwm *pwm, rt_uint32_t offset,
        rt_uint32_t value)
{
    HWREG32(pwm->base + offset) = value;
}

static rt_err_t sunxi_pwm_enable(struct sunxi_pwm *pwm, int channel,
        rt_bool_t enabled)
{
    rt_uint32_t value;

    if (channel < 0 || (rt_uint32_t)channel >= pwm->channels)
    {
        return -RT_EINVAL;
    }

    value = sunxi_pwm_read(pwm, PWM_PER);
    if (enabled)
    {
        value |= RT_BIT(channel);
    }
    else
    {
        value &= ~RT_BIT(channel);
    }
    sunxi_pwm_write(pwm, PWM_PER, value);

    value = sunxi_pwm_read(pwm, PWM_PCGR);
    if (enabled)
    {
        value |= RT_BIT(channel);
    }
    else
    {
        value &= ~RT_BIT(channel);
    }
    sunxi_pwm_write(pwm, PWM_PCGR, value);

    return RT_EOK;
}

static rt_err_t sunxi_pwm_config(struct sunxi_pwm *pwm,
        struct rt_pwm_configuration *config)
{
    rt_uint64_t source_rate;
    rt_uint64_t cycles;
    rt_uint32_t pccr;
    rt_uint32_t ctrl;
    rt_uint32_t period;
    rt_uint32_t active;
    rt_uint32_t divider_index;
    rt_uint32_t prescale;
    int channel = config->channel;

    if (channel < 0 || (rt_uint32_t)channel >= pwm->channels || !config->period ||
            config->pulse > config->period)
    {
        return -RT_EINVAL;
    }

    source_rate = config->period <= 334 ? SUNXI_PWM_CLK_100M : SUNXI_PWM_CLK_24M;
    cycles = source_rate * config->period / SUNXI_PWM_NSEC_PER_SEC;
    if (!cycles)
    {
        cycles = 1;
    }

    for (divider_index = 0; divider_index < RT_ARRAY_SIZE(sunxi_pwm_dividers);
            ++divider_index)
    {
        for (prescale = 0; prescale <= RT_UINT8_MAX; ++prescale)
        {
            period = cycles / sunxi_pwm_dividers[divider_index] / (prescale + 1);
            if (period && period <= SUNXI_PWM_COUNTER_MAX)
            {
                goto _configured;
            }
        }
    }

    return -RT_EINVAL;

_configured:
    active = ((rt_uint64_t)period * config->pulse + config->period / 2) /
            config->period;
    active = rt_min(active, period);

    pccr = sunxi_pwm_read(pwm, sunxi_pwm_pccr(channel));
    pccr &= ~(PWM_CLK_SRC_MASK | PWM_DIV_M_MASK);
    pccr |= divider_index;
    if (source_rate == SUNXI_PWM_CLK_100M)
    {
        pccr |= RT_BIT(PWM_CLK_SRC_SHIFT);
    }
    sunxi_pwm_write(pwm, sunxi_pwm_pccr(channel), pccr);

    ctrl = sunxi_pwm_read(pwm, sunxi_pwm_ctrl(channel));
    ctrl &= ~(PWM_PRESCALE_MASK | PWM_ACT_STA);
    ctrl |= prescale;
    if (config->complementary)
    {
        ctrl |= PWM_ACT_STA;
    }
    sunxi_pwm_write(pwm, sunxi_pwm_ctrl(channel), ctrl);

    sunxi_pwm_write(pwm, sunxi_pwm_period(channel),
            (active & PWM_ACT_CYCLES_MASK) |
            ((period - 1) << PWM_PERIOD_CYCLES_SHIFT));

    return RT_EOK;
}

static rt_err_t sunxi_pwm_get(struct sunxi_pwm *pwm,
        struct rt_pwm_configuration *config)
{
    rt_uint64_t source_rate;
    rt_uint64_t scale;
    rt_uint32_t pccr;
    rt_uint32_t ctrl;
    rt_uint32_t value;
    rt_uint32_t cycles;
    rt_uint32_t divider_index;
    int channel = config->channel;

    if (channel < 0 || (rt_uint32_t)channel >= pwm->channels)
    {
        return -RT_EINVAL;
    }

    pccr = sunxi_pwm_read(pwm, sunxi_pwm_pccr(channel));
    ctrl = sunxi_pwm_read(pwm, sunxi_pwm_ctrl(channel));
    value = sunxi_pwm_read(pwm, sunxi_pwm_period(channel));
    cycles = ((value & PWM_PERIOD_CYCLES_MASK) >> PWM_PERIOD_CYCLES_SHIFT) + 1;

    divider_index = pccr & PWM_DIV_M_MASK;
    if (divider_index >= RT_ARRAY_SIZE(sunxi_pwm_dividers))
    {
        return -RT_EIO;
    }

    source_rate = (pccr & RT_BIT(PWM_CLK_SRC_SHIFT)) ?
            SUNXI_PWM_CLK_100M : SUNXI_PWM_CLK_24M;
    scale = sunxi_pwm_dividers[divider_index] *
            ((ctrl & PWM_PRESCALE_MASK) + 1);
    config->period = (rt_uint64_t)cycles * scale * SUNXI_PWM_NSEC_PER_SEC /
            source_rate;
    config->pulse = (rt_uint64_t)(value & PWM_ACT_CYCLES_MASK) * scale *
            SUNXI_PWM_NSEC_PER_SEC / source_rate;
    config->complementary = !!(ctrl & PWM_ACT_STA);

    return RT_EOK;
}

static rt_err_t sunxi_pwm_control(struct rt_device_pwm *device, int cmd,
        void *args)
{
    rt_err_t err;
    rt_base_t level;
    struct rt_pwm_configuration *config = args;
    struct sunxi_pwm *pwm = to_sunxi_pwm(device);

    if (!config)
    {
        return -RT_EINVAL;
    }

    level = rt_spin_lock_irqsave(&pwm->lock);

    switch (cmd)
    {
    case PWM_CMD_ENABLE:
        err = sunxi_pwm_enable(pwm, config->channel, RT_TRUE);
        break;
    case PWM_CMD_DISABLE:
        err = sunxi_pwm_enable(pwm, config->channel, RT_FALSE);
        break;
    case PWM_CMD_SET:
    case PWM_CMD_SET_PERIOD:
    case PWM_CMD_SET_PULSE:
        err = sunxi_pwm_config(pwm, config);
        break;
    case PWM_CMD_GET:
        err = sunxi_pwm_get(pwm, config);
        break;
    default:
        err = -RT_EINVAL;
        break;
    }

    rt_spin_unlock_irqrestore(&pwm->lock, level);
    return err;
}

static const struct rt_pwm_ops sunxi_pwm_ops =
{
    .control = sunxi_pwm_control,
};

static void sunxi_pwm_release(struct sunxi_pwm *pwm)
{
    if (!rt_is_err_or_null(pwm->clk))
    {
        rt_clk_disable_unprepare(pwm->clk);
        rt_clk_put(pwm->clk);
    }
    if (!rt_is_err_or_null(pwm->reset))
    {
        rt_reset_control_assert(pwm->reset);
        rt_reset_control_put(pwm->reset);
    }
    if (pwm->base)
    {
        rt_iounmap(pwm->base);
    }
    rt_free(pwm);
}

static rt_err_t sunxi_pwm_probe(struct rt_platform_device *pdev)
{
    rt_err_t err;
    rt_uint32_t channels = 4;
    const char *name;
    struct rt_device *dev = &pdev->parent;
    struct sunxi_pwm *pwm = rt_calloc(1, sizeof(*pwm));

    if (!pwm)
    {
        return -RT_ENOMEM;
    }

    pwm->base = rt_dm_dev_iomap(dev, 0);
    if (!pwm->base)
    {
        err = -RT_EIO;
        goto _fail;
    }

    rt_ofw_prop_read_u32(dev->ofw_node, "pwm-number", &channels);
    if (!channels || channels > SUNXI_PWM_CHANNELS_MAX)
    {
        err = -RT_EINVAL;
        goto _fail;
    }
    pwm->channels = channels;

    pwm->clk = rt_clk_get_by_index(dev, 0);
    if (rt_is_err(pwm->clk))
    {
        err = rt_ptr_err(pwm->clk);
        goto _fail;
    }

    pwm->reset = rt_reset_control_get_by_index(dev, 0);
    if (rt_is_err(pwm->reset))
    {
        err = rt_ptr_err(pwm->reset);
        goto _fail;
    }

    if ((err = rt_reset_control_deassert(pwm->reset)) ||
            (err = rt_clk_prepare_enable(pwm->clk)))
    {
        goto _fail;
    }

    rt_spin_lock_init(&pwm->lock);
    pwm->parent.parent.ofw_node = dev->ofw_node;
    rt_dm_dev_set_name_auto(&pwm->parent.parent, "pwm");
    name = rt_dm_dev_get_name(&pwm->parent.parent);

    if ((err = rt_device_pwm_register(&pwm->parent, name, &sunxi_pwm_ops, pwm)))
    {
        goto _fail;
    }

    dev->user_data = pwm;
    rt_dm_dev_bind_fwdata(dev, RT_NULL, pwm);

    return RT_EOK;

_fail:
    sunxi_pwm_release(pwm);
    return err;
}

static rt_err_t sunxi_pwm_remove(struct rt_platform_device *pdev)
{
    struct rt_device *dev = &pdev->parent;
    struct sunxi_pwm *pwm = dev->user_data;
    int channel;

    for (channel = 0; (rt_uint32_t)channel < pwm->channels; ++channel)
    {
        sunxi_pwm_enable(pwm, channel, RT_FALSE);
    }

    rt_dm_dev_unbind_fwdata(dev, RT_NULL);
    rt_device_unregister(&pwm->parent.parent);
    sunxi_pwm_release(pwm);

    return RT_EOK;
}

static const struct rt_ofw_node_id sunxi_pwm_ofw_ids[] =
{
    { .compatible = "allwinner,sun252i-f101-pwm" },
    { .compatible = "allwinner,sun50i-h616-pwm" },
    { /* sentinel */ }
};

static struct rt_platform_driver sunxi_pwm_driver =
{
    .name = "sunxi-pwm",
    .ids = sunxi_pwm_ofw_ids,
    .probe = sunxi_pwm_probe,
    .remove = sunxi_pwm_remove,
};
RT_PLATFORM_DRIVER_EXPORT(sunxi_pwm_driver);
