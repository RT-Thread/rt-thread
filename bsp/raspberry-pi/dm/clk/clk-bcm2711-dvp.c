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

#define DBG_TAG "clk.bcm2711.dvp"
#define DBG_LVL DBG_INFO
#include <rtdbg.h>

#include "../../reset/reset-simple.h"

#define DVP_HT_RPI_SW_INIT      0x04
#define DVP_HT_RPI_MISC_CONFIG  0x08

struct bcm2711_dvp_clk
{
    struct rt_clk_node clk_parent;
    struct reset_simple reset_parent;

    void *regs;
    struct rt_clk *clk;
};

#define raw_to_bcm2711_dvp_clk(raw) rt_container_of(raw, struct bcm2711_dvp_clk, clk_parent)

struct dvp_clk_gate
{
    struct rt_clk_cell cell;

    rt_uint8_t bit_idx;
};

#define raw_to_dvp_clk_gate(raw) rt_container_of(raw, struct dvp_clk_gate, cell)

static void bcm2711_dvp_clk_endisable(struct rt_clk_cell *cell, int enable)
{
    rt_ubase_t level;
    rt_uint32_t value;
    int set = 1 ^ enable;
    struct dvp_clk_gate *gate = raw_to_dvp_clk_gate(cell);
    struct bcm2711_dvp_clk *dvp_clk = raw_to_bcm2711_dvp_clk(cell->clk_np);

    level = rt_spin_lock_irqsave(&dvp_clk->reset_parent.lock);

    value = HWREG32(dvp_clk->regs + DVP_HT_RPI_MISC_CONFIG);
    if (set)
    {
        value |= RT_BIT(gate->bit_idx);
    }
    else
    {
        value &= ~RT_BIT(gate->bit_idx);
    }
    HWREG32(dvp_clk->regs + DVP_HT_RPI_MISC_CONFIG) = value;

    rt_spin_unlock_irqrestore(&dvp_clk->reset_parent.lock, level);
}

static rt_err_t bcm2711_dvp_clk_enable(struct rt_clk_cell *cell)
{
    bcm2711_dvp_clk_endisable(cell, 1);

    return RT_EOK;
}

static void bcm2711_dvp_clk_disable(struct rt_clk_cell *cell)
{
    bcm2711_dvp_clk_endisable(cell, 0);
}

static rt_bool_t bcm2711_dvp_clk_is_enabled(struct rt_clk_cell *cell)
{
    rt_uint32_t value;
    struct dvp_clk_gate *gate = raw_to_dvp_clk_gate(cell);
    struct bcm2711_dvp_clk *dvp_clk = raw_to_bcm2711_dvp_clk(cell->clk_np);

    value = HWREG32(dvp_clk->regs + DVP_HT_RPI_MISC_CONFIG);
    value ^= RT_BIT(gate->bit_idx);
    value &= RT_BIT(gate->bit_idx);

    return !!value;
}

static rt_ubase_t bcm2711_dvp_clk_recalc_rate(struct rt_clk_cell *cell, rt_ubase_t parent_rate)
{
    struct bcm2711_dvp_clk *dvp_clk = raw_to_bcm2711_dvp_clk(cell->clk_np);

    return rt_clk_cell_get_rate(dvp_clk->clk->cell);
}

const struct rt_clk_ops bcm2711_dvp_clk_ops =
{
    .enable = bcm2711_dvp_clk_enable,
    .disable = bcm2711_dvp_clk_disable,
    .is_enabled = bcm2711_dvp_clk_is_enabled,
    .recalc_rate = bcm2711_dvp_clk_recalc_rate,
};

static struct dvp_clk_gate hdmi0_108mhz =
{
    .cell.name = "hdmi0-108MHz",
    .cell.ops = &bcm2711_dvp_clk_ops,
    .bit_idx = 3,
};

static struct dvp_clk_gate hdmi1_108mhz =
{
    .cell.name = "hdmi1-108MHz",
    .cell.ops = &bcm2711_dvp_clk_ops,
    .bit_idx = 4,
};

static struct rt_clk_cell *dvp_clk_cell[] =
{
    &hdmi0_108mhz.cell,
    &hdmi1_108mhz.cell,
};

static rt_err_t bcm2711_dvp_clk_probe(struct rt_platform_device *pdev)
{
    rt_err_t err;
    struct reset_simple *rsts;
    struct rt_reset_controller *rstcer;
    struct rt_device *dev = &pdev->parent;
    struct bcm2711_dvp_clk *dvp_clk = rt_calloc(1, sizeof(*dvp_clk));

    if (!dvp_clk)
    {
        return -RT_ENOMEM;
    }

    dvp_clk->regs = rt_dm_dev_iomap(dev, 0);

    if (!dvp_clk->regs)
    {
        err = -RT_EIO;
        goto _fail;
    }

    dvp_clk->clk = rt_clk_get_by_index(dev, 0);

    if (rt_is_err(dvp_clk->clk))
    {
        err = rt_ptr_err(dvp_clk->clk);
        goto _fail;
    }

    for (int i = 0; i < RT_ARRAY_SIZE(dvp_clk_cell); ++i)
    {
        struct rt_clk_cell *cell = dvp_clk_cell[i];

        cell->parents_nr = 1;
        cell->parent_name = dvp_clk->clk->cell->name;
    }

    dvp_clk->clk_parent.dev = dev;
    dvp_clk->clk_parent.cells = dvp_clk_cell;
    dvp_clk->clk_parent.cells_nr = RT_ARRAY_SIZE(dvp_clk_cell);

    if ((err = rt_clk_register(&dvp_clk->clk_parent)))
    {
        goto _fail;
    }

    /* Reset */
    rsts = &dvp_clk->reset_parent;

    rt_spin_lock_init(&rsts->lock);
    rsts->mmio_base = dvp_clk->regs + DVP_HT_RPI_SW_INIT;

    rstcer = &rsts->parent;
    rstcer->priv = rsts;
    rstcer->ofw_node = dev->ofw_node;
    rstcer->ops = &reset_simple_ops;

    if ((err = rt_reset_controller_register(rstcer)))
    {
        goto _fail;
    }

    return RT_EOK;

_fail:
    if (dvp_clk->regs)
    {
        rt_iounmap(dvp_clk->regs);
    }

    if (dvp_clk->clk_parent.dev)
    {
        rt_clk_unregister(&dvp_clk->clk_parent);
    }

    if (dvp_clk->reset_parent.parent.ops)
    {
        rt_reset_controller_unregister(&dvp_clk->reset_parent.parent);
    }

    if (rt_is_err_or_null(dvp_clk->clk))
    {
        rt_clk_put(dvp_clk->clk);
    }

    rt_free(dvp_clk);

    return err;
}

static const struct rt_ofw_node_id bcm2711_dvp_clk_ofw_ids[] =
{
    { .compatible = "brcm,brcm2711-dvp", },
    { /* sentinel */ }
};

static struct rt_platform_driver bcm2711_dvp_clk_driver =
{
    .name = "clk-brcm2711-dvp",
    .ids = bcm2711_dvp_clk_ofw_ids,

    .probe = bcm2711_dvp_clk_probe,
};

static int bcm2711_dvp_clk_register(void)
{
    rt_platform_driver_register(&bcm2711_dvp_clk_driver);

    return 0;
}
INIT_SUBSYS_EXPORT(bcm2711_dvp_clk_register);
