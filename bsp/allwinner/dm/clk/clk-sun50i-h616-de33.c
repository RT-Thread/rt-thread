/*
 * Copyright (c) 2006-2026, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#include <rtthread.h>
#include <rtdevice.h>

/* DE33 is not register-compatible with the DE2 clock controller. */
#define DE33_RESET    0x00
#define DE33_GATE     0x04
#define DE33_BUS_GATE 0x08

struct de33_ccu
{
    struct rt_clk_node node;
    /* OFW resolves composite clock/reset providers by adjacent headers. */
    struct rt_reset_controller resets;
    struct rt_clk_cell clocks[4];
    struct rt_clk_cell *cells[9];
    struct rt_spinlock lock;
    struct rt_clk *bus, *mod;
    struct rt_reset_control *reset;
    void *base;
};

static void de33_update(struct de33_ccu *ccu, unsigned int reg,
                        rt_uint32_t mask, rt_bool_t enable)
{
    rt_base_t level = rt_spin_lock_irqsave(&ccu->lock);
    rt_uint32_t value = HWREG32(ccu->base + reg);

    HWREG32(ccu->base + reg) = enable ? value | mask : value & ~mask;
    rt_spin_unlock_irqrestore(&ccu->lock, level);
}

static rt_err_t de33_enable(struct rt_clk_cell *cell)
{
    struct de33_ccu *ccu = cell->clk_np->priv;
    unsigned int index = cell - ccu->clocks;

    de33_update(ccu, index ? DE33_GATE : DE33_BUS_GATE,
                RT_BIT(index == 3 ? 4 : (index ? index - 1 : 0)), RT_TRUE);
    return RT_EOK;
}

static void de33_disable(struct rt_clk_cell *cell)
{
    struct de33_ccu *ccu = cell->clk_np->priv;
    unsigned int index = cell - ccu->clocks;

    de33_update(ccu, index ? DE33_GATE : DE33_BUS_GATE,
                RT_BIT(index == 3 ? 4 : (index ? index - 1 : 0)), RT_FALSE);
}

static rt_ubase_t de33_rate(struct rt_clk_cell *cell, rt_ubase_t parent_rate)
{
    return parent_rate;
}

static const struct rt_clk_ops de33_clk_ops = {
    .enable = de33_enable,
    .disable = de33_disable,
    .recalc_rate = de33_rate,
};

static struct rt_clk_cell *de33_parse(struct rt_clk_node *node,
                                      struct rt_ofw_cell_args *args)
{
    unsigned int id;

    if (args->args_count != 1)
    {
        return RT_NULL;
    }
    id = args->args[0];
    /* Legacy trees name three bus clocks; hardware has one shared gate. */
    if (id <= 2)
    {
        id = 0;
    }
    return id < node->cells_nr ? node->cells[id] : RT_NULL;
}

static rt_err_t de33_reset_update(struct rt_reset_control *rst, rt_bool_t release)
{
    if (rst->id < 0 || rst->id > 2)
    {
        return -RT_EINVAL;
    }
    de33_update(rst->rstcer->priv, DE33_RESET,
                RT_BIT(rst->id == 2 ? 4 : rst->id), release);
    return RT_EOK;
}

static rt_err_t de33_assert(struct rt_reset_control *rst)
{
    return de33_reset_update(rst, RT_FALSE);
}

static rt_err_t de33_deassert(struct rt_reset_control *rst)
{
    return de33_reset_update(rst, RT_TRUE);
}

static int de33_status(struct rt_reset_control *rst)
{
    struct de33_ccu *ccu = rst->rstcer->priv;

    if (rst->id < 0 || rst->id > 2)
    {
        return -RT_EINVAL;
    }
    return !(HWREG32(ccu->base + DE33_RESET) & RT_BIT(rst->id == 2 ? 4 : rst->id));
}

static const struct rt_reset_control_ops de33_reset_ops = {
    .assert = de33_assert,
    .deassert = de33_deassert,
    .status = de33_status,
};

static rt_err_t de33_ccu_probe(struct rt_platform_device *pdev)
{
    static const char * const names[] = {
        "de33-bus",
        "de33-mixer0",
        "de33-mixer1",
        "de33-wb",
    };
    struct de33_ccu *ccu = rt_calloc(1, sizeof(*ccu));
    rt_err_t err = -RT_ENOMEM;
    int i;

    if (!ccu)
    {
        return err;
    }
    rt_spin_lock_init(&ccu->lock);
    ccu->base = rt_dm_dev_iomap(&pdev->parent, 0);
    ccu->bus = rt_clk_get_by_name(&pdev->parent, "bus");
    ccu->mod = rt_clk_get_by_name(&pdev->parent, "mod");
    ccu->reset = rt_reset_control_get_by_index(&pdev->parent, 0);
    if (!ccu->base || rt_is_err_or_null(ccu->bus) ||
        rt_is_err_or_null(ccu->mod) || rt_is_err_or_null(ccu->reset))
    {
        err = -RT_EIO;
        goto fail;
    }
    if ((err = rt_clk_prepare_enable(ccu->bus)))
    {
        goto fail;
    }
    if ((err = rt_clk_prepare_enable(ccu->mod)))
    {
        goto disable_bus;
    }
    if ((err = rt_reset_control_deassert(ccu->reset)))
    {
        goto disable_mod;
    }
    ccu->node.dev = &pdev->parent;
    ccu->node.priv = ccu;
    ccu->node.parents_clk = rt_err_ptr(-RT_ENOSYS);
    ccu->node.cells = ccu->cells;
    ccu->node.cells_nr = RT_ARRAY_SIZE(ccu->cells);
    ccu->node.ofw_parse = de33_parse;
    for (i = 0; i < RT_ARRAY_SIZE(ccu->clocks); ++i)
    {
        struct rt_clk_cell *cell = &ccu->clocks[i];

        cell->name = names[i];
        cell->ops = &de33_clk_ops;
        cell->parents_nr = 1;
        cell->parent_name = (i ? ccu->mod : ccu->bus)->cell->name;
        cell->flags = RT_CLK_F_GET_RATE_NOCACHE;
        if (i)
        {
            cell->flags |= RT_CLK_F_SET_RATE_PARENT;
        }
        ccu->cells[i ? i + 5 : 0] = cell;
    }
    if ((err = rt_clk_register(&ccu->node)))
    {
        goto assert_reset;
    }
    ccu->resets.ofw_node = pdev->parent.ofw_node;
    ccu->resets.ops = &de33_reset_ops;
    ccu->resets.priv = ccu;
    if ((err = rt_reset_controller_register(&ccu->resets)))
    {
        if (rt_clk_unregister(&ccu->node))
        {
            return err;
        }
        goto assert_reset;
    }
    pdev->parent.user_data = ccu;
    return RT_EOK;

assert_reset:
    rt_reset_control_assert(ccu->reset);
disable_mod:
    rt_clk_disable_unprepare(ccu->mod);
disable_bus:
    rt_clk_disable_unprepare(ccu->bus);
fail:
    if (!rt_is_err_or_null(ccu->reset))
    {
        rt_reset_control_put(ccu->reset);
    }
    if (!rt_is_err_or_null(ccu->mod))
    {
        rt_clk_put(ccu->mod);
    }
    if (!rt_is_err_or_null(ccu->bus))
    {
        rt_clk_put(ccu->bus);
    }
    if (ccu->base)
    {
        rt_iounmap(ccu->base);
    }
    rt_free(ccu);
    return err;
}

static rt_err_t de33_bus_probe(struct rt_platform_device *pdev)
{
    struct rt_ofw_node *section, *sram, *syscon, *child;
    rt_uint32_t selection;
    void *base;
    rt_err_t err;

    err = rt_ofw_prop_read_u32_index(pdev->parent.ofw_node, "allwinner,sram", 1, &selection);
    if (err || selection != 1)
    {
        return err ? err : -RT_EINVAL;
    }
    section = rt_ofw_parse_phandle(pdev->parent.ofw_node, "allwinner,sram", 0);
    if (!section)
    {
        return -RT_ENOENT;
    }
    if (!rt_ofw_node_is_compatible(section, "allwinner,sun50i-a64-sram-c") &&
        !rt_ofw_node_is_compatible(section, "allwinner,sun50i-h616-sram-c"))
    {
        rt_ofw_node_put(section);
        return -RT_EINVAL;
    }
    sram = rt_ofw_get_parent(section);
    syscon = sram ? rt_ofw_get_parent(sram) : RT_NULL;
    base = syscon ? rt_ofw_iomap(syscon, 0) : RT_NULL;
    rt_ofw_node_put(syscon);
    rt_ofw_node_put(sram);
    rt_ofw_node_put(section);
    if (!base)
    {
        return -RT_EIO;
    }
    /* SRAM C selection: zero routes the SRAM to DE, one to the CPU. */
    HWREG32(base + 4) &= ~RT_BIT(24);
    rt_iounmap(base);
    rt_ofw_foreach_available_child_node(pdev->parent.ofw_node, child)
    {
        if ((err = rt_platform_ofw_request(child)))
        {
            rt_ofw_node_put(child);
            return err;
        }
    }
    return RT_EOK;
}

static const struct rt_ofw_node_id de33_ccu_ids[] = {
    { .compatible = "allwinner,sun50i-h616-de33-clk" },
    {}
};

static const struct rt_ofw_node_id de33_bus_ids[] = {
    { .compatible = "allwinner,sun50i-h616-de33" },
    {}
};

static struct rt_platform_driver de33_ccu_driver = {
    .name = "de33-ccu",
    .ids = de33_ccu_ids,
    .probe = de33_ccu_probe,
};

static struct rt_platform_driver de33_bus_driver = {
    .name = "de33-bus",
    .ids = de33_bus_ids,
    .probe = de33_bus_probe,
};

static int de33_register(void)
{
    rt_platform_driver_register(&de33_ccu_driver);
    rt_platform_driver_register(&de33_bus_driver);
    return 0;
}
INIT_SUBSYS_EXPORT(de33_register);
