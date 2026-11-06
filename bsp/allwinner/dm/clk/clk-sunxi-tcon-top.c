/*
 * Copyright (c) 2006-2026, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#include <rtthread.h>
#include <rtdevice.h>
#include "sunxi_tcon_top.h"

#define TCON_TOP_PORT_SEL  0x1c
#define TCON_TOP_GATE_SRC  0x20
#define TCON_TOP_TV0_GATE  RT_BIT(20)
#define TCON_TOP_HDMI_MASK (3U << 28)

struct sunxi_tcon_top
{
    struct rt_clk_node node;
    struct rt_clk_cell tv0;
    struct rt_clk_cell *cells[1];
    struct rt_clk *bus, *parent;
    struct rt_reset_control *reset;
    struct rt_spinlock lock;
    void *base;
};

static void tcon_top_update(struct sunxi_tcon_top *top, unsigned int reg,
                            rt_uint32_t mask, rt_uint32_t value)
{
    rt_base_t level = rt_spin_lock_irqsave(&top->lock);

    HWREG32(top->base + reg) = (HWREG32(top->base + reg) & ~mask) | value;
    rt_spin_unlock_irqrestore(&top->lock, level);
}

static rt_err_t tcon_top_enable(struct rt_clk_cell *cell)
{
    tcon_top_update(cell->clk_np->priv, TCON_TOP_GATE_SRC,
                    TCON_TOP_TV0_GATE, TCON_TOP_TV0_GATE);
    return RT_EOK;
}

static void tcon_top_disable(struct rt_clk_cell *cell)
{
    tcon_top_update(cell->clk_np->priv, TCON_TOP_GATE_SRC, TCON_TOP_TV0_GATE, 0);
}

static rt_ubase_t tcon_top_rate(struct rt_clk_cell *cell, rt_ubase_t parent_rate)
{
    return parent_rate;
}

static const struct rt_clk_ops tcon_top_ops = {
    .enable = tcon_top_enable,
    .disable = tcon_top_disable,
    .recalc_rate = tcon_top_rate,
};

rt_err_t sunxi_tcon_top_route(struct rt_ofw_node *node, unsigned int mixer,
                              unsigned int tcon, rt_bool_t hdmi)
{
    struct sunxi_tcon_top *top;
    rt_err_t err;

    /* H6/H616 expose TV0, whose hardware routing index is two. */
    if (!node || mixer > 1 || tcon != 2)
    {
        return -RT_EINVAL;
    }
    if ((err = rt_platform_ofw_request(node)))
    {
        return err;
    }
    if (!node->dev || !(top = node->dev->user_data))
    {
        return -RT_EIO;
    }
    tcon_top_update(top, TCON_TOP_PORT_SEL, 3U << (mixer * 4), tcon << (mixer * 4));
    tcon_top_update(top, TCON_TOP_GATE_SRC, TCON_TOP_HDMI_MASK, hdmi ? 1U << 28 : 0);
    return RT_EOK;
}

static rt_err_t tcon_top_probe(struct rt_platform_device *pdev)
{
    struct sunxi_tcon_top *top = rt_calloc(1, sizeof(*top));
    rt_err_t err = -RT_ENOMEM;

    if (!top)
    {
        return err;
    }
    rt_spin_lock_init(&top->lock);
    top->base = rt_dm_dev_iomap(&pdev->parent, 0);
    top->bus = rt_clk_get_by_name(&pdev->parent, "bus");
    top->parent = rt_clk_get_by_name(&pdev->parent, "tcon-tv0");
    top->reset = rt_reset_control_get_by_index(&pdev->parent, 0);
    if (!top->base || rt_is_err_or_null(top->bus) ||
        rt_is_err_or_null(top->parent) || rt_is_err_or_null(top->reset))
    {
        err = -RT_EIO;
        goto fail;
    }
    if ((err = rt_clk_prepare_enable(top->bus)))
    {
        goto fail;
    }
    if ((err = rt_reset_control_deassert(top->reset)))
    {
        goto disable_bus;
    }
    HWREG32(top->base + TCON_TOP_PORT_SEL) = 0;
    HWREG32(top->base + TCON_TOP_GATE_SRC) = 0;
    top->node.dev = &pdev->parent;
    top->node.priv = top;
    top->node.parents_clk = rt_err_ptr(-RT_ENOSYS);
    top->node.cells = top->cells;
    top->node.cells_nr = RT_ARRAY_SIZE(top->cells);
    top->cells[0] = &top->tv0;
    if (rt_ofw_prop_read_string_index(pdev->parent.ofw_node,
                                      "clock-output-names", 0, &top->tv0.name))
    {
        top->tv0.name = "sunxi-tcon-top-tv0";
    }
    top->tv0.ops = &tcon_top_ops;
    top->tv0.parents_nr = 1;
    top->tv0.parent_name = top->parent->cell->name;
    top->tv0.flags = RT_CLK_F_SET_RATE_PARENT | RT_CLK_F_GET_RATE_NOCACHE;
    if ((err = rt_clk_register(&top->node)))
    {
        rt_reset_control_assert(top->reset);
        goto disable_bus;
    }
    pdev->parent.user_data = top;
    return RT_EOK;

disable_bus:
    rt_clk_disable_unprepare(top->bus);
fail:
    if (!rt_is_err_or_null(top->reset))
    {
        rt_reset_control_put(top->reset);
    }
    if (!rt_is_err_or_null(top->parent))
    {
        rt_clk_put(top->parent);
    }
    if (!rt_is_err_or_null(top->bus))
    {
        rt_clk_put(top->bus);
    }
    if (top->base)
    {
        rt_iounmap(top->base);
    }
    rt_free(top);
    return err;
}

static const struct rt_ofw_node_id tcon_top_ids[] = {
    { .compatible = "allwinner,sun50i-h6-tcon-top" },
    { .compatible = "allwinner,sun50i-h616-tcon-top" },
    {}
};

static struct rt_platform_driver tcon_top_driver = {
    .name = "sunxi-tcon-top",
    .ids = tcon_top_ids,
    .probe = tcon_top_probe,
};

static int tcon_top_register(void)
{
    rt_platform_driver_register(&tcon_top_driver);
    return 0;
}
INIT_SUBSYS_EXPORT(tcon_top_register);
