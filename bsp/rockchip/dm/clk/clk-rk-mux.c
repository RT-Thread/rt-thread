/*
 * Copyright (c) 2006-2022, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2022-3-08      GuEe-GUI     the first version
 */

#include "clk-rk-mux.h"

rt_inline rt_uint32_t clk_mux_readl(struct rockchip_clk_cell *rk_cell)
{
    void *base = rk_cell->provider->reg_base;

    if (rk_cell->mux_flags & CLK_MUX_BIG_ENDIAN)
    {
        return rt_be32_to_cpu(HWREG32(base + rk_cell->muxdiv_offset));
    }

    return HWREG32(base + rk_cell->muxdiv_offset);
}

rt_inline void clk_mux_writel(struct rockchip_clk_cell *rk_cell, rt_uint32_t val)
{
    void *base = rk_cell->provider->reg_base;

    if (rk_cell->mux_flags & CLK_MUX_BIG_ENDIAN)
    {
        HWREG32(base + rk_cell->muxdiv_offset) = rt_cpu_to_be32(val);
    }
    else
    {
        HWREG32(base + rk_cell->muxdiv_offset) = val;
    }
}

static int clk_mux_val_to_index(struct rt_clk_cell *cell,
        const rt_uint32_t *table, rt_uint32_t flags, rt_uint32_t val)
{
    int num_parents = cell->parents_nr;

    if (table)
    {
        for (int i = 0; i < num_parents; ++i)
        {
            if (table[i] == val)
            {
                return i;
            }
        }

        return -RT_EINVAL;
    }

    if (val && (flags & CLK_MUX_INDEX_BIT))
    {
        val = __rt_ffs(val) - 1;
    }

    if (val && (flags & CLK_MUX_INDEX_ONE))
    {
        --val;
    }

    if (val >= num_parents)
    {
        return -RT_EINVAL;
    }

    return val;
}

static rt_uint32_t clk_mux_index_to_val(const rt_uint32_t *table, rt_uint32_t flags, rt_uint8_t index)
{
    rt_uint32_t val = index;

    if (table)
    {
        val = table[index];
    }
    else
    {
        if (flags & CLK_MUX_INDEX_BIT)
        {
            val = 1 << index;
        }

        if (flags & CLK_MUX_INDEX_ONE)
        {
            val++;
        }
    }

    return val;
}

static rt_err_t rockchip_mux_clk_set_parent(struct rt_clk_cell *cell, rt_uint8_t index)
{
    rt_uint32_t val, reg;
    struct rockchip_clk_cell *rk_cell = cell_to_rockchip_clk_cell(cell);

    val = clk_mux_index_to_val(rk_cell->mux_table, rk_cell->mux_flags, index);

    if (rk_cell->mux_flags & CLK_MUX_HIWORD_MASK)
    {
        reg = rk_cell->mux_mask << (rk_cell->mux_shift + 16);
    }
    else
    {
        reg = clk_mux_readl(rk_cell);
        reg &= ~(rk_cell->mux_mask << rk_cell->mux_shift);
    }
    val = val << rk_cell->mux_shift;
    reg |= val;
    clk_mux_writel(rk_cell, reg);

    return RT_EOK;
}

static rt_uint8_t rockchip_mux_clk_get_parent(struct rt_clk_cell *cell)
{
    rt_uint32_t val;
    struct rockchip_clk_cell *rk_cell = cell_to_rockchip_clk_cell(cell);

    val = clk_mux_readl(rk_cell) >> rk_cell->mux_shift;
    val &= rk_cell->mux_mask;

    return clk_mux_val_to_index(cell, rk_cell->mux_table, rk_cell->mux_flags, val);
}

const struct rt_clk_ops rockchip_mux_clk_ops =
{
    .set_parent = rockchip_mux_clk_set_parent,
    .get_parent = rockchip_mux_clk_get_parent,
};

const struct rt_clk_ops rockchip_mux_ro_clk_ops =
{
    .get_parent = rockchip_mux_clk_get_parent,
};

void rockchip_mux_clk_cell_init(struct rockchip_clk_cell *rk_cell)
{
    rk_cell->mux_mask = RT_BIT(rk_cell->mux_width) - 1;

    if (!rk_cell->cell.ops)
    {
        if (!((rk_cell->mux_flags & CLK_MUX_READ_ONLY)))
        {
            rk_cell->cell.ops = &rockchip_mux_clk_ops;
        }
        else
        {
            rk_cell->cell.ops = &rockchip_mux_ro_clk_ops;
        }
    }
}
