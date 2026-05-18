/*
 * Copyright (c) 2006-2022, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2022-3-08      GuEe-GUI     the first version
 */

#include "clk-rk-half-divider.h"
#include "clk-rk-gate.h"
#include "clk-rk-mux.h"

#define clk_div_mask(width) ((1 << (width)) - 1)

static rt_bool_t _is_best_half_div(rt_ubase_t rate, rt_ubase_t now,
        rt_ubase_t best, rt_ubase_t flags)
{
    if (flags & CLK_DIVIDER_ROUND_CLOSEST)
    {
        return rt_abs(rate - now) <= rt_abs(rate - best);
    }

    return now <= rate && now >= best;
}

rt_inline rt_uint32_t clk_div_readl(struct rockchip_clk_cell *rk_cell)
{
    return HWREG32(rk_cell->provider->reg_base + (rk_cell->div_offset ? : rk_cell->muxdiv_offset));
}

rt_inline void clk_div_writel(struct rockchip_clk_cell *rk_cell, rt_uint32_t val)
{
    HWREG32(rk_cell->provider->reg_base + (rk_cell->div_offset ? : rk_cell->muxdiv_offset)) = val;
}

static rt_ubase_t clk_div_recalc_rate(struct rt_clk_cell *cell, rt_ubase_t parent_rate)
{
    rt_uint32_t val;
    struct rockchip_clk_cell *rk_cell = cell_to_rockchip_clk_cell(cell);

    val = clk_div_readl(rk_cell) >> rk_cell->div_shift;
    val &= clk_div_mask(rk_cell->div_width);
    val = val * 2 + 3;

    return RT_DIV_ROUND_UP_ULL(((rt_uint64_t)parent_rate * 2), val);
}

static int clk_div_bestdiv(struct rt_clk_cell *cell, rt_ubase_t rate,
        rt_ubase_t *best_parent_rate, rt_uint8_t width, rt_ubase_t flags)
{
    rt_uint32_t bestdiv = 0;
    rt_bool_t is_bestdiv = RT_FALSE;
    rt_ubase_t parent_rate, best = 0, now, maxdiv;

    if (!rate)
    {
        rate = 1;
    }

    maxdiv = clk_div_mask(width);

    if (!(cell->flags & RT_CLK_F_SET_RATE_PARENT))
    {
        parent_rate = *best_parent_rate;
        bestdiv = RT_DIV_ROUND_UP_ULL(((rt_uint64_t)parent_rate * 2), rate);

        if (bestdiv < 3)
        {
            bestdiv = 0;
        }
        else
        {
            bestdiv = RT_DIV_ROUND_UP(bestdiv - 3, 2);
        }

        bestdiv = bestdiv > maxdiv ? maxdiv : bestdiv;

        return bestdiv;
    }

    /*
     * The maximum divider we can use without overflowing
     * rt_ubase_t in rate * i below
     */
    maxdiv = rt_min((~0UL) / rate, maxdiv);

    for (int i = 0; i <= maxdiv; ++i)
    {
        parent_rate = rt_clk_cell_round_rate(rt_clk_cell_get_parent(cell),
                ((rt_uint64_t)rate * (i * 2 + 3)) / 2);
        now = RT_DIV_ROUND_UP_ULL(((rt_uint64_t)parent_rate * 2), (i * 2 + 3));

        if (_is_best_half_div(rate, now, best, flags))
        {
            is_bestdiv = RT_TRUE;
            bestdiv = i;
            best = now;
            *best_parent_rate = parent_rate;
        }
    }

    if (!is_bestdiv)
    {
        bestdiv = clk_div_mask(width);
        *best_parent_rate = rt_clk_cell_round_rate(rt_clk_cell_get_parent(cell), 1);
    }

    return bestdiv;
}

static rt_base_t clk_div_round_rate(struct rt_clk_cell *cell,
        rt_ubase_t rate, rt_ubase_t *prate)
{
    int div;
    struct rockchip_clk_cell *rk_cell = cell_to_rockchip_clk_cell(cell);

    div = clk_div_bestdiv(cell, rate, prate, rk_cell->div_width, rk_cell->div_flags);

    return RT_DIV_ROUND_UP_ULL(((rt_uint64_t)*prate * 2), div * 2 + 3);
}

static rt_err_t clk_div_set_rate(struct rt_clk_cell *cell,
        rt_ubase_t rate, rt_ubase_t parent_rate)
{
    rt_uint32_t value, val;
    struct rockchip_clk_cell *rk_cell = cell_to_rockchip_clk_cell(cell);

    value = RT_DIV_ROUND_UP_ULL(((rt_uint64_t)parent_rate * 2), rate);
    value = RT_DIV_ROUND_UP(value - 3, 2);
    value = rt_min_t(rt_uint32_t, value, clk_div_mask(rk_cell->div_width));

    if (rk_cell->div_flags & CLK_DIVIDER_HIWORD_MASK)
    {
        val = clk_div_mask(rk_cell->div_width) << (rk_cell->div_shift + 16);
    }
    else
    {
        val = clk_div_readl(rk_cell);
        val &= ~(clk_div_mask(rk_cell->div_width) << rk_cell->div_shift);
    }

    val |= value << rk_cell->div_shift;
    clk_div_writel(rk_cell, val);

    return RT_EOK;
}

void rockchip_half_divider_clk_cell_init(struct rockchip_clk_cell *rk_cell)
{
    struct rockchip_half_divider_clk_cell *half_divider_cell = cell_to_rockchip_half_divider_clk_cell(&rk_cell->cell);

    rk_cell->cell.ops = &half_divider_cell->ops;

    if (rk_cell->cell.parents_nr > 1)
    {
        rockchip_mux_clk_cell_init(rk_cell);

        half_divider_cell->ops.get_parent = rockchip_mux_clk_ops.get_parent;

        if (!((rk_cell->mux_flags & CLK_MUX_READ_ONLY)))
        {
            half_divider_cell->ops.set_parent = rockchip_mux_clk_ops.set_parent;
        }
    }

    if (rk_cell->gate_offset >= 0)
    {
        half_divider_cell->ops.enable = rockchip_gate_clk_ops.enable;
        half_divider_cell->ops.disable = rockchip_gate_clk_ops.disable;
        half_divider_cell->ops.is_enabled = rockchip_gate_clk_ops.is_enabled;
        half_divider_cell->ops.recalc_rate = clk_div_recalc_rate;
        half_divider_cell->ops.round_rate = clk_div_round_rate;
        half_divider_cell->ops.set_rate = clk_div_set_rate;
    }

    if (rk_cell->div_width > 0)
    {
        half_divider_cell->ops.set_rate = clk_div_set_rate;
    }
}
