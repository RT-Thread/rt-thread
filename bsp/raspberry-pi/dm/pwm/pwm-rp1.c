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

#define DBG_TAG "pwm.rp1"
#define DBG_LVL DBG_INFO
#include <rtdbg.h>

#define PWM_GLOBAL_CTRL         0x000
#define PWM_CHANNEL_CTRL(x)     (0x014 + ((x) * 16))
#define PWM_RANGE(x)            (0x018 + ((x) * 16))
#define PWM_DUTY(x)             (0x020 + ((x) * 16))

/* 8:FIFO_POP_MASK + 0:Trailing edge M/S modulation */
#define PWM_CHANNEL_DEFAULT     (RT_BIT(8) + RT_BIT(0))
#define PWM_CHANNEL_ENABLE(x)   RT_BIT(x)
#define PWM_POLARITY            RT_BIT(3)
#define SET_UPDATE              RT_BIT(31)
#define PWM_MODE_MASK           RT_GENMASK(1, 0)
#define PWM_POLARITY_INVERTED   RT_BIT(0)

#define PWM_NUMBER              4

#define NSEC_PER_SEC            1000000000L

struct rp1_pwm
{
    struct rt_device_pwm parent;

    void *base;
    struct rt_clk *clk;

    rt_bool_t inverted[PWM_NUMBER];
    struct rt_pwm_configuration config[PWM_NUMBER];
};

#define raw_to_rp1_pwm(raw) rt_container_of(raw, struct rp1_pwm, parent)

static void rp1_pwm_apply_config(struct rp1_pwm *rpwm)
{
    rt_uint32_t value;

    value = HWREG32(rpwm->base + PWM_GLOBAL_CTRL);
    value |= SET_UPDATE;
    HWREG32(rpwm->base + PWM_GLOBAL_CTRL) = value;
}

static rt_err_t rp1_pwm_enable(struct rp1_pwm *rpwm, int channel, rt_bool_t enable)
{
    rt_uint32_t value;

    if (channel >= PWM_NUMBER)
    {
        return -RT_EINVAL;
    }

    if (enable)
    {
        value = PWM_CHANNEL_DEFAULT;

        if (rpwm->config[channel].complementary || rpwm->inverted[channel])
        {
            value |= PWM_POLARITY;
        }

        HWREG32(rpwm->base + PWM_CHANNEL_CTRL(channel)) = value;

        value = HWREG32(rpwm->base + PWM_GLOBAL_CTRL);
        value |= PWM_CHANNEL_ENABLE(channel);
        HWREG32(rpwm->base + PWM_GLOBAL_CTRL) = value;
    }
    else
    {
        value = HWREG32(rpwm->base + PWM_GLOBAL_CTRL);
        value &= ~PWM_CHANNEL_ENABLE(channel);
        HWREG32(rpwm->base + PWM_GLOBAL_CTRL) = value;
    }

    rp1_pwm_apply_config(rpwm);

    return RT_EOK;
}

static rt_err_t rp1_pwm_config(struct rp1_pwm *rpwm,
        struct rt_pwm_configuration *pwm_cfg)
{
    int channel;
    rt_uint32_t value;
    rt_ubase_t clk_period, clk_rate = rt_clk_get_rate(rpwm->clk);

    if (!clk_rate)
    {
        LOG_E("Failed to get clock rate");

        return -RT_EINVAL;
    }

    channel = pwm_cfg->channel;

    if (channel >= PWM_NUMBER)
    {
        return -RT_EINVAL;
    }

    /* Period */
    clk_period = RT_DIV_ROUND_CLOSEST(NSEC_PER_SEC, clk_rate);

    HWREG32(rpwm->base + PWM_DUTY(channel)) =
        RT_DIV_ROUND_CLOSEST(pwm_cfg->pulse, clk_period);

    /* Duty cycle */
    HWREG32(rpwm->base + PWM_RANGE(channel)) =
        RT_DIV_ROUND_CLOSEST(pwm_cfg->period, clk_period);

    /* Polarity */
    value = HWREG32(rpwm->base + PWM_CHANNEL_CTRL(channel));
    if (!pwm_cfg->complementary && !rpwm->inverted[channel])
    {
        value &= ~PWM_POLARITY;
    }
    else
    {
        value |= PWM_POLARITY;
    }
    HWREG32(rpwm->base + PWM_CHANNEL_CTRL(channel)) = value;

    rp1_pwm_apply_config(rpwm);

    rpwm->config[channel] = *pwm_cfg;
    rpwm->config[channel].complementary =
            pwm_cfg->complementary || rpwm->inverted[channel];

    return RT_EOK;
}

static rt_err_t rp1_pwm_get(struct rp1_pwm *rpwm,
        struct rt_pwm_configuration *pwm_cfg)
{
    int channel = pwm_cfg->channel;

    if (channel >= PWM_NUMBER)
    {
        return -RT_EINVAL;
    }

    *pwm_cfg = rpwm->config[channel];

    return RT_EOK;
}

static rt_err_t rp1_pwm_control(struct rt_device_pwm *pwm, int cmd, void *args)
{
    rt_err_t err = RT_EOK;
    struct rp1_pwm *rpwm = raw_to_rp1_pwm(pwm);
    struct rt_pwm_configuration *pwm_cfg = args;

    switch (cmd)
    {
    case PWM_CMD_ENABLE:
        err = rp1_pwm_enable(rpwm, pwm_cfg->channel, RT_TRUE);
        break;

    case PWM_CMD_DISABLE:
        err = rp1_pwm_enable(rpwm, pwm_cfg->channel, RT_FALSE);
        break;

    case PWM_CMD_SET:
    case PWM_CMD_SET_PERIOD:
    case PWM_CMD_SET_PULSE:
        err = rp1_pwm_config(rpwm, pwm_cfg);
        break;

    case PWM_CMD_GET:
        err = rp1_pwm_get(rpwm, pwm_cfg);
        break;

    default:
        err = -RT_EINVAL;
        break;
    }

    return err;
}

const static struct rt_pwm_ops rp1_pwm_ops =
{
    .control = rp1_pwm_control,
};

static void rp1_pwm_parse_dt_flags(struct rp1_pwm *rpwm,
        struct rt_ofw_node *pwm_np)
{
    struct rt_ofw_node *np;

    rt_ofw_foreach_allnodes(np)
    {
        int index = 0;
        struct rt_ofw_cell_args args;

        while (!rt_ofw_parse_phandle_cells(np, "pwms", "#pwm-cells",
                index++, &args))
        {
            if (args.data == pwm_np && args.args_count >= 3 &&
                args.args[0] < PWM_NUMBER)
            {
                rpwm->inverted[args.args[0]] =
                        !!(args.args[2] & PWM_POLARITY_INVERTED);
            }

            if (args.data)
            {
                rt_ofw_node_put(args.data);
            }
        }
    }
}

static rt_err_t rp1_pwm_probe(struct rt_platform_device *pdev)
{
    rt_err_t err;
    struct rt_device *dev = &pdev->parent;
    struct rp1_pwm *rpwm = rt_calloc(1, sizeof(*rpwm));

    if (!rpwm)
    {
        return -RT_ENOMEM;
    }

    rpwm->base = rt_dm_dev_iomap(dev, 0);

    if (!rpwm->base)
    {
        err = -RT_EIO;
        goto _fail;
    }

    rpwm->clk = rt_clk_get_by_index(dev, 0);

    if (rt_is_err(rpwm->clk))
    {
        err = rt_ptr_err(rpwm->clk);
        goto _fail;
    }

    if ((err = rt_clk_prepare_enable(rpwm->clk)))
    {
        goto _fail;
    }

    dev->user_data = rpwm;

    rpwm->parent.parent.ofw_node = dev->ofw_node;

    rp1_pwm_parse_dt_flags(rpwm, dev->ofw_node);

    for (int channel = 0; channel < PWM_NUMBER; ++channel)
    {
        rp1_pwm_enable(rpwm, channel, RT_FALSE);

        HWREG32(rpwm->base + PWM_CHANNEL_CTRL(channel)) =
                PWM_CHANNEL_DEFAULT |
                (rpwm->inverted[channel] ? PWM_POLARITY : 0);
        rpwm->config[channel].channel = channel;
        rpwm->config[channel].complementary = rpwm->inverted[channel];
    }

    rp1_pwm_apply_config(rpwm);

    rt_dm_dev_set_name_auto(&rpwm->parent.parent, "pwm");
    rt_device_pwm_register(&rpwm->parent, rt_dm_dev_get_name(&rpwm->parent.parent), &rp1_pwm_ops, rpwm);

    rt_dm_dev_bind_fwdata(dev, RT_NULL, rpwm);

    return RT_EOK;

_fail:
    if (rpwm->base)
    {
        rt_iounmap(rpwm->base);
    }

    if (!rt_is_err_or_null(rpwm->clk))
    {
        rt_clk_disable_unprepare(rpwm->clk);
        rt_clk_put(rpwm->clk);
    }

    rt_free(rpwm);

    return err;
}

static rt_err_t rp1_pwm_remove(struct rt_platform_device *pdev)
{
    struct rt_device *dev = &pdev->parent;
    struct rp1_pwm *rpwm = dev->user_data;

    rt_dm_dev_unbind_fwdata(dev, RT_NULL);

    for (int channel = 0; channel < PWM_NUMBER; ++channel)
    {
        rp1_pwm_enable(rpwm, channel, RT_FALSE);
    }

    rt_device_unregister(&rpwm->parent.parent);

    rt_clk_disable_unprepare(rpwm->clk);
    rt_clk_put(rpwm->clk);

    rt_free(rpwm);

    return RT_EOK;
}

static const struct rt_ofw_node_id rp1_pwm_ofw_ids[] =
{
    { .compatible = "raspberrypi,rp1-pwm" },
    { /* sentinel */ }
};

static struct rt_platform_driver rp1_pwm_driver =
{
    .name = "rp1-pwm",
    .ids = rp1_pwm_ofw_ids,

    .probe = rp1_pwm_probe,
    .remove = rp1_pwm_remove,
};
RT_PLATFORM_DRIVER_EXPORT(rp1_pwm_driver);
