/*
 * Copyright (c) 2006-2022, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2022-11-26     GuEe-GUI     first version
 * 2024-05-01     GuEe-GUI     update for new clk
 */

#include <rtthread.h>
#include <rtdevice.h>

struct clk_fixed
{
    struct rt_clk_node parent;

    struct rt_clk_fixed_rate fcell;
    struct rt_clk_cell *cells[1];
};

static rt_ubase_t fixed_clk_recalc_rate(struct rt_clk_cell *cell, rt_ubase_t parent_rate)
{
    struct rt_clk_fixed_rate *fr = rt_container_of(cell, struct rt_clk_fixed_rate, cell);

    return fr->fixed_rate;
}

static struct rt_clk_ops fixed_clk_ops =
{
    .recalc_rate = fixed_clk_recalc_rate,
};

static rt_err_t fixed_clk_probe(struct rt_platform_device *pdev)
{
    rt_err_t err;
    rt_uint32_t val;
    struct rt_device *dev = &pdev->parent;
    struct clk_fixed *cf = rt_calloc(1, sizeof(*cf));

    if (!cf)
    {
        return -RT_ENOMEM;
    }

    if ((err = rt_dm_dev_prop_read_u32(dev, "clock-frequency", &val)))
    {
        goto _fail;
    }
    cf->fcell.fixed_rate = val;

    val = 0;
    rt_dm_dev_prop_read_u32(dev, "clock-accuracy", &val);
    cf->fcell.fixed_accuracy = val;

    rt_dm_dev_prop_read_string(dev, "clock-output-names", &cf->fcell.cell.name);

    cf->parent.dev = dev;
    cf->parent.cells_nr = 1;
    cf->parent.cells = cf->cells;
    cf->cells[0] = &cf->fcell.cell;
    cf->fcell.cell.ops = &fixed_clk_ops;

    if ((err = rt_clk_register(&cf->parent)))
    {
        goto _fail;
    }

    return RT_EOK;

_fail:
    rt_free(cf);

    return err;
}

static const struct rt_ofw_node_id fixed_clk_ofw_ids[] =
{
    { .compatible = "fixed-clock" },
    { /* sentinel */ }
};

static struct rt_platform_driver fixed_clk_driver =
{
    .name = "clk-fixed-rate",
    .ids = fixed_clk_ofw_ids,

    .probe = fixed_clk_probe,
};

static int fixed_clk_drv_register(void)
{
    rt_platform_driver_register(&fixed_clk_driver);

    return 0;
}
INIT_SUBSYS_EXPORT(fixed_clk_drv_register);
