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

#define DBG_TAG "clk.dsi"
#define DBG_LVL DBG_INFO
#include <rtdbg.h>

struct dsi_clk
{
    struct rt_clk_node parent;
};

struct dsi_clk_output
{
    struct rt_clk_cell cell;

    rt_ubase_t div;
};

static rt_ubase_t dsi_clk_recalc_rate(struct rt_clk_cell *cell, rt_ubase_t parent_rate)
{
    struct dsi_clk_output *clk = rt_container_of(cell, struct dsi_clk_output, cell);

    return parent_rate / clk->div;
}

static rt_base_t dsi_clk_round_rate(struct rt_clk_cell *cell, rt_ubase_t drate, rt_ubase_t *prate)
{
    struct dsi_clk_output *clk = rt_container_of(cell, struct dsi_clk_output, cell);

    return *prate / clk->div;
}

const struct rt_clk_ops dsi_clk_ops =
{
    .recalc_rate = dsi_clk_recalc_rate,
    .round_rate = dsi_clk_round_rate,
};

#define REGISTER_CLK_DSI(_name, _div) \
(void *)&(struct dsi_clk_output)    \
{                                   \
    .cell.name = _name,             \
    .cell.ops = &dsi_clk_ops,       \
    .div = _div,                    \
}

static struct rt_clk_cell *dsi0_clk_cell[] =
{
    REGISTER_CLK_DSI("dsi0_byte", 8),
    REGISTER_CLK_DSI("dsi0_ddr2", 4),
    REGISTER_CLK_DSI("dsi0_ddr", 2),
};

static struct rt_clk_cell *dsi1_clk_cell[] =
{
    REGISTER_CLK_DSI("dsi1_byte", 8),
    REGISTER_CLK_DSI("dsi1_ddr2", 4),
    REGISTER_CLK_DSI("dsi1_ddr", 2),
};

static rt_err_t dsi_clk_probe(struct rt_platform_device *pdev)
{
    rt_err_t err;
    struct rt_device *dev = &pdev->parent;
    struct rt_clk_cell **dsi_clk_cell = (void *)pdev->id->data;
    struct dsi_clk *dclk = rt_calloc(1, sizeof(*dclk));

    if (!dclk)
    {
        return -RT_ENOMEM;
    }

    for (int i = 0; i < 3; ++i)
    {
        struct dsi_clk_output *clk = rt_container_of(dsi_clk_cell[i], struct dsi_clk_output, cell);

        rt_dm_dev_prop_read_string_index(dev, "clock-output-names", i, &clk->cell.name);
    }

    dclk->parent.dev = dev;
    dclk->parent.cells = dsi_clk_cell;
    dclk->parent.cells_nr = 3;
    dclk->parent.parents_clk = rt_err_ptr(-RT_EEMPTY);

    if ((err = rt_clk_register(&dclk->parent)))
    {
        goto _fail;
    }

    return RT_EOK;
_fail:
    rt_free(dclk);

    return err;
}

static const struct rt_ofw_node_id dsi_clk_ofw_ids[] =
{
    { .compatible = "brcm,bcm2835-dsi0", .data = dsi0_clk_cell },
    { .compatible = "brcm,bcm2835-dsi1", .data = dsi1_clk_cell },
    { .compatible = "brcm,bcm2711-dsi0", .data = dsi0_clk_cell },
    { .compatible = "brcm,bcm2711-dsi1", .data = dsi1_clk_cell },
    { /* sentinel */ }
};

static struct rt_platform_driver dsi_clk_driver =
{
    .name = "clk-dsi",
    .ids = dsi_clk_ofw_ids,

    .probe = dsi_clk_probe,
};

static int dsi_clk_register(void)
{
    struct rt_ofw_node *np = RT_NULL;

    rt_platform_driver_register(&dsi_clk_driver);

    /* Force probing of the DSIx clock */
    while ((np = rt_ofw_find_node_by_ids(np, dsi_clk_ofw_ids)))
    {
        rt_platform_ofw_device_probe_child(np);
    }

    return 0;
}
INIT_SUBSYS_EXPORT(dsi_clk_register);
