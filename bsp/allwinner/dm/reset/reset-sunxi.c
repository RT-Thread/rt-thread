/*
 * Copyright (c) 2006-2026, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#include <rtthread.h>
#include <rtdevice.h>

#define DBG_TAG "reset.sunxi"
#define DBG_LVL DBG_INFO
#include <rtdbg.h>

#include <sunxi_reset.h>

struct sunxi_reset
{
    struct rt_reset_controller parent;
    const struct sunxi_reset_data *data;

    void *base;
};

static rt_err_t sunxi_reset_update(struct rt_reset_control *rstc,
        rt_bool_t asserted)
{
    rt_ubase_t level;
    rt_uint32_t value;
    struct sunxi_reset *reset = rstc->rstcer->priv;
    const struct sunxi_reset_line *line;

    if (rstc->id < 0 || rstc->id >= reset->data->lines_nr)
    {
        return -RT_EINVAL;
    }

    line = &reset->data->lines[rstc->id];
    if (!line->mask)
    {
        return -RT_EINVAL;
    }

    level = rt_spin_lock_irqsave(&reset->parent.spinlock);
    value = HWREG32(reset->base + line->reg);

    if (asserted)
    {
        value &= ~line->mask;
    }
    else
    {
        value |= line->mask;
    }

    HWREG32(reset->base + line->reg) = value;
    rt_spin_unlock_irqrestore(&reset->parent.spinlock, level);

    return RT_EOK;
}

static rt_err_t sunxi_reset_assert(struct rt_reset_control *rstc)
{
    return sunxi_reset_update(rstc, RT_TRUE);
}

static rt_err_t sunxi_reset_deassert(struct rt_reset_control *rstc)
{
    return sunxi_reset_update(rstc, RT_FALSE);
}

static rt_err_t sunxi_reset_reset(struct rt_reset_control *rstc)
{
    rt_err_t err;
    struct sunxi_reset *reset = rstc->rstcer->priv;

    if ((err = sunxi_reset_assert(rstc)))
    {
        return err;
    }

    if (reset->data->assert_delay_us)
    {
        rt_hw_us_delay(reset->data->assert_delay_us);
    }

    return sunxi_reset_deassert(rstc);
}

static int sunxi_reset_status(struct rt_reset_control *rstc)
{
    struct sunxi_reset *reset = rstc->rstcer->priv;
    const struct sunxi_reset_line *line;

    if (rstc->id < 0 || rstc->id >= reset->data->lines_nr)
    {
        return -RT_EINVAL;
    }

    line = &reset->data->lines[rstc->id];
    if (!line->mask)
    {
        return -RT_EINVAL;
    }

    return !(HWREG32(reset->base + line->reg) & line->mask);
}

static const struct rt_reset_control_ops sunxi_reset_ops =
{
    .reset = sunxi_reset_reset,
    .assert = sunxi_reset_assert,
    .deassert = sunxi_reset_deassert,
    .status = sunxi_reset_status,
};

static rt_err_t sunxi_reset_probe(struct rt_platform_device *pdev)
{
    rt_err_t err;
    struct rt_device *dev = &pdev->parent;
    struct rt_ofw_node *ccu_np;
    const struct sunxi_reset_data *data = pdev->id ? pdev->id->data : RT_NULL;
    struct sunxi_reset *reset;

    if (!data || !data->lines || !data->lines_nr)
    {
        return -RT_EINVAL;
    }

    reset = rt_calloc(1, sizeof(*reset));
    if (!reset)
    {
        return -RT_ENOMEM;
    }

    ccu_np = rt_ofw_parse_phandle(dev->ofw_node, "allwinner,ccu", 0);
    if (!ccu_np)
    {
        err = -RT_EINVAL;
        goto _fail;
    }

    reset->base = rt_ofw_iomap(ccu_np, 0);
    rt_ofw_node_put(ccu_np);
    if (!reset->base)
    {
        err = -RT_EIO;
        goto _fail;
    }

    reset->data = data;
    reset->parent.ofw_node = dev->ofw_node;
    reset->parent.priv = reset;
    reset->parent.ops = &sunxi_reset_ops;

    if ((err = rt_reset_controller_register(&reset->parent)))
    {
        goto _fail;
    }

    return RT_EOK;

_fail:
    if (reset->base)
    {
        rt_iounmap(reset->base);
    }
    rt_free(reset);

    return err;
}

static const struct rt_ofw_node_id sunxi_reset_ofw_ids[] =
{
    { .compatible = "allwinner,sun252i-f101-ccu-reset", .data = &sun252i_f101_reset_data },
    { /* sentinel */ }
};

static struct rt_platform_driver sunxi_reset_driver =
{
    .name = "sunxi-reset",
    .ids = sunxi_reset_ofw_ids,
    .probe = sunxi_reset_probe,
};

static int sunxi_reset_register(void)
{
    rt_platform_driver_register(&sunxi_reset_driver);

    return 0;
}
INIT_SUBSYS_EXPORT(sunxi_reset_register);
