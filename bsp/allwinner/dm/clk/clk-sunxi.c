/*
 * Copyright (c) 2006-2026, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#include <rtthread.h>
#include <rtdevice.h>

#define DBG_TAG "clk.sunxi"
#define DBG_LVL DBG_INFO
#include <rtdbg.h>

#include <sunxi_ccu.h>

struct sunxi_ccu;

struct sunxi_clk
{
    struct rt_clk_cell cell;
    struct sunxi_ccu *ccu;

    const struct sunxi_clk_desc *desc;
    rt_ubase_t rate;
};

struct sunxi_ccu
{
    struct rt_clk_node parent;

    void *base;
    struct rt_spinlock lock;

    struct sunxi_clk *clks;
    struct rt_clk_cell **cells;
};

#define to_sunxi_clk(raw) rt_container_of(raw, struct sunxi_clk, cell)

static rt_ubase_t sunxi_clk_recalc_rate(struct rt_clk_cell *cell,
        rt_ubase_t parent_rate)
{
    struct sunxi_clk *clock = to_sunxi_clk(cell);
    const struct sunxi_clk_desc *desc = clock->desc;
    rt_uint32_t value;
    rt_uint32_t mux;
    rt_uint32_t m;
    rt_uint32_t p;

    RT_UNUSED(parent_rate);

    /*
     * A boot loader may leave a module clock at any divider.  Report the
     * divider currently programmed in the CCU so a later set_rate() request
     * is not incorrectly elided by the clock core.
     */
    if (!desc->parent_rates || !desc->parent_rates_nr || !desc->m_width)
    {
        return clock->rate;
    }

    value = HWREG32(clock->ccu->base + desc->gate_reg);
    mux = desc->mux_width ? (value >> desc->mux_shift) &
            (RT_BIT(desc->mux_width) - 1) : 0;
    m = (value >> desc->m_shift) & (RT_BIT(desc->m_width) - 1);
    p = desc->p_width ? (value >> desc->p_shift) &
            (RT_BIT(desc->p_width) - 1) : 0;

    if (mux >= desc->parent_rates_nr)
    {
        return clock->rate;
    }

    return desc->parent_rates[mux] / ((m + 1) * RT_BIT(p));

}

static rt_ubase_t sunxi_clk_find_rate(struct sunxi_clk *clock,
        rt_ubase_t requested, rt_uint32_t *out_value)
{
    rt_ubase_t best = 0;
    rt_ubase_t lowest = ~(rt_ubase_t)0;
    rt_uint32_t best_value = 0;
    rt_uint32_t lowest_value = 0;
    const struct sunxi_clk_desc *desc = clock->desc;
    rt_uint32_t m_max;
    rt_uint32_t p_max;
    rt_uint32_t mux;

    if (!desc->parent_rates || !desc->parent_rates_nr || !desc->m_width)
    {
        return 0;
    }

    m_max = RT_BIT(desc->m_width);
    p_max = desc->p_width ? RT_BIT(desc->p_width) : 1;

    for (mux = 0; mux < desc->parent_rates_nr; ++mux)
    {
        rt_uint32_t m;
        rt_uint32_t p;

        for (m = 0; m < m_max; ++m)
        {
            for (p = 0; p < p_max; ++p)
            {
                rt_ubase_t rate = desc->parent_rates[mux] /
                        ((m + 1) * RT_BIT(p));
                rt_uint32_t value = (m << desc->m_shift) |
                        (p << desc->p_shift) |
                        (mux << desc->mux_shift);

                if (rate < lowest)
                {
                    lowest = rate;
                    lowest_value = value;
                }
                if (rate <= requested && rate > best)
                {
                    best = rate;
                    best_value = value;
                }
            }
        }
    }

    if (!best)
    {
        best = lowest;
        best_value = lowest_value;
    }
    if (out_value)
    {
        *out_value = best_value;
    }

    return best;
}

static rt_base_t sunxi_clk_round_rate(struct rt_clk_cell *cell,
        rt_ubase_t requested, rt_ubase_t *parent_rate)
{
    struct sunxi_clk *clock = to_sunxi_clk(cell);

    RT_UNUSED(parent_rate);

    return sunxi_clk_find_rate(clock, requested, RT_NULL);
}

static rt_err_t sunxi_clk_set_rate(struct rt_clk_cell *cell,
        rt_ubase_t requested, rt_ubase_t parent_rate)
{
    rt_ubase_t level;
    rt_ubase_t rate;
    rt_uint32_t value;
    rt_uint32_t mask;
    struct sunxi_clk *clock = to_sunxi_clk(cell);
    struct sunxi_ccu *ccu = clock->ccu;
    const struct sunxi_clk_desc *desc = clock->desc;

    RT_UNUSED(parent_rate);

    rate = sunxi_clk_find_rate(clock, requested, &value);
    if (!rate)
    {
        return -RT_ENOSYS;
    }

    mask = (RT_BIT(desc->m_width) - 1) << desc->m_shift;
    if (desc->p_width)
    {
        mask |= (RT_BIT(desc->p_width) - 1) << desc->p_shift;
    }
    if (desc->mux_width)
    {
        mask |= (RT_BIT(desc->mux_width) - 1) << desc->mux_shift;
    }

    level = rt_spin_lock_irqsave(&ccu->lock);
    value |= HWREG32(ccu->base + desc->gate_reg) & ~mask;
    HWREG32(ccu->base + desc->gate_reg) = value;
    rt_spin_unlock_irqrestore(&ccu->lock, level);

    clock->rate = rate;
    return RT_EOK;
}

static rt_err_t sunxi_clk_enable(struct rt_clk_cell *cell)
{
    rt_ubase_t level;
    rt_uint32_t value;
    struct sunxi_clk *clock = to_sunxi_clk(cell);
    struct sunxi_ccu *ccu = clock->ccu;

    if (!clock->desc->gate_mask)
    {
        return RT_EOK;
    }

    level = rt_spin_lock_irqsave(&ccu->lock);
    value = HWREG32(ccu->base + clock->desc->gate_reg);
    value |= clock->desc->gate_mask;
    HWREG32(ccu->base + clock->desc->gate_reg) = value;
    rt_spin_unlock_irqrestore(&ccu->lock, level);

    return RT_EOK;
}

static void sunxi_clk_disable(struct rt_clk_cell *cell)
{
    rt_ubase_t level;
    rt_uint32_t value;
    struct sunxi_clk *clock = to_sunxi_clk(cell);
    struct sunxi_ccu *ccu = clock->ccu;

    if (!clock->desc->gate_mask)
    {
        return;
    }

    level = rt_spin_lock_irqsave(&ccu->lock);
    value = HWREG32(ccu->base + clock->desc->gate_reg);
    value &= ~clock->desc->gate_mask;
    HWREG32(ccu->base + clock->desc->gate_reg) = value;
    rt_spin_unlock_irqrestore(&ccu->lock, level);
}

static rt_bool_t sunxi_clk_is_enabled(struct rt_clk_cell *cell)
{
    struct sunxi_clk *clock = to_sunxi_clk(cell);

    return !clock->desc->gate_mask ||
            !!(HWREG32(clock->ccu->base + clock->desc->gate_reg) &
                    clock->desc->gate_mask);
}

static const struct rt_clk_ops sunxi_clk_ops =
{
    .enable = sunxi_clk_enable,
    .disable = sunxi_clk_disable,
    .is_enabled = sunxi_clk_is_enabled,
    .recalc_rate = sunxi_clk_recalc_rate,
    .round_rate = sunxi_clk_round_rate,
    .set_rate = sunxi_clk_set_rate,
};

static rt_ubase_t sunxi_clk_read_rate(struct rt_device *dev,
        const struct sunxi_clk_desc *desc)
{
    rt_uint32_t rate;

    if (desc->rate_property &&
        !rt_dm_dev_prop_read_u32(dev, desc->rate_property, &rate) && rate)
    {
        return rate;
    }

    return desc->rate_default;
}

static void sunxi_ccu_release(struct sunxi_ccu *ccu)
{
    if (ccu->base)
    {
        rt_iounmap(ccu->base);
    }

    rt_free(ccu->cells);
    rt_free(ccu->clks);
    rt_free(ccu);
}

static rt_err_t sunxi_ccu_probe(struct rt_platform_device *pdev)
{
    rt_err_t err;
    rt_size_t index;
    struct rt_device *dev = &pdev->parent;
    const struct sunxi_ccu_data *data = pdev->id ? pdev->id->data : RT_NULL;
    struct sunxi_ccu *ccu;

    if (!data || !data->clks || !data->clks_nr || !data->cells_nr)
    {
        return -RT_EINVAL;
    }

    ccu = rt_calloc(1, sizeof(*ccu));
    if (!ccu)
    {
        return -RT_ENOMEM;
    }

    ccu->clks = rt_calloc(data->clks_nr, sizeof(*ccu->clks));
    ccu->cells = rt_calloc(data->cells_nr, sizeof(*ccu->cells));
    if (!ccu->clks || !ccu->cells)
    {
        err = -RT_ENOMEM;
        goto _fail;
    }

    ccu->base = rt_dm_dev_iomap(dev, 0);
    if (!ccu->base)
    {
        err = -RT_EIO;
        goto _fail;
    }

    ccu->parent.dev = dev;
    ccu->parent.cells_nr = data->cells_nr;
    ccu->parent.cells = ccu->cells;
    rt_spin_lock_init(&ccu->lock);

    for (index = 0; index < data->clks_nr; ++index)
    {
        struct sunxi_clk *clock = &ccu->clks[index];
        const struct sunxi_clk_desc *desc = &data->clks[index];

        if (desc->id < 0 || desc->id >= data->cells_nr || !desc->name ||
            ccu->cells[desc->id])
        {
            err = -RT_EINVAL;
            goto _fail;
        }

        clock->ccu = ccu;
        clock->desc = desc;
        clock->rate = sunxi_clk_read_rate(dev, desc);
        clock->cell.name = desc->name;
        clock->cell.ops = &sunxi_clk_ops;
        ccu->cells[desc->id] = &clock->cell;
    }

    if ((err = rt_clk_register(&ccu->parent)))
    {
        goto _fail;
    }

    return RT_EOK;

_fail:
    sunxi_ccu_release(ccu);

    return err;
}

static const struct rt_ofw_node_id sunxi_ccu_ofw_ids[] =
{
    { .compatible = "allwinner,sun252i-f101-ccu", .data = &sun252i_f101_ccu_data },
    { /* sentinel */ }
};

static struct rt_platform_driver sunxi_ccu_driver =
{
    .name = "sunxi-ccu",
    .ids = sunxi_ccu_ofw_ids,
    .probe = sunxi_ccu_probe,
};

static int sunxi_ccu_register(void)
{
    rt_platform_driver_register(&sunxi_ccu_driver);

    return 0;
}
INIT_SUBSYS_EXPORT(sunxi_ccu_register);
