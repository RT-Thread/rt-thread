/*
 * Copyright (c) 2006-2022, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2022-11-26     GuEe-GUI     first version
 */

#include <rtthread.h>
#include <rtdevice.h>

#include <drivers/platform.h>

static rt_err_t fixed_clk_ofw_init(struct rt_platform_device *pdev, struct rt_clk_fixed_rate *clk_fixed)
{
    rt_err_t err = RT_EOK;
    rt_uint32_t rate, accuracy;
    struct rt_ofw_node *np = pdev->parent.ofw_node;
    const char *clk_name = np->name;

    if (!rt_ofw_prop_read_u32(np, "clock-frequency", &rate))
    {
        rt_ofw_prop_read_u32(np, "clock-accuracy", &accuracy);
        rt_ofw_prop_read_string(np, "clock-output-names", &clk_name);

        clk_fixed->clk.name = clk_name;
        clk_fixed->clk.rate = rate;
        clk_fixed->clk.min_rate = rate;
        clk_fixed->clk.max_rate = rate;
        clk_fixed->fixed_rate = rate;
        clk_fixed->fixed_accuracy = accuracy;

        rt_ofw_data(np) = &clk_fixed->clk;
    }
    else
    {
        err = -RT_EIO;
    }

    return err;
}

static rt_err_t fixed_clk_probe(struct rt_platform_device *pdev)
{
    rt_err_t err = RT_EOK;
    struct rt_clk_fixed_rate *clk_fixed = rt_calloc(1, sizeof(*clk_fixed));

    if (clk_fixed)
    {
        err = fixed_clk_ofw_init(pdev, clk_fixed);
    }
    else
    {
        err = -RT_ENOMEM;
    }

    if (!err)
    {
        err = rt_clk_register(&clk_fixed->clk, RT_NULL);
    }

    if (err && clk_fixed)
    {
        rt_free(clk_fixed);
    }

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
