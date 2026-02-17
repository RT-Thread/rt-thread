/*
 * Copyright (c) 2006-2022, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2022-3-08      GuEe-GUI     the first version
 */

#include "clk-rk-factor.h"
#include "clk-rk-gate.h"

static rt_ubase_t clk_factor_recalc_rate(struct rt_clk_cell *cell, rt_ubase_t parent_rate)
{
    rt_uint64_t rate;
    struct rockchip_clk_cell *rk_cell = cell_to_rockchip_clk_cell(cell);

    rate = (rt_uint64_t)parent_rate * rk_cell->div_shift;
    rt_do_div(rate, rk_cell->div_width);

    return (rt_ubase_t)rate;
}

static rt_base_t clk_factor_round_rate(struct rt_clk_cell *cell, rt_ubase_t rate, rt_ubase_t *prate)
{
    struct rockchip_clk_cell *rk_cell = cell_to_rockchip_clk_cell(cell);

    if (cell->flags & RT_CLK_F_SET_RATE_PARENT)
    {
        rt_ubase_t best_parent;

        best_parent = (rate / rk_cell->div_shift) * rk_cell->div_width;
        *prate = rt_clk_cell_round_rate(rt_clk_cell_get_parent(cell), best_parent);
    }

    return (*prate / rk_cell->div_width) * rk_cell->div_shift;
}

static rt_err_t clk_factor_set_rate(struct rt_clk_cell *cell, rt_ubase_t rate, rt_ubase_t parent_rate)
{
    return RT_EOK;
}

void rockchip_factor_clk_cell_init(struct rockchip_clk_cell *rk_cell)
{
    struct rockchip_factor_clk_cell *factor_cell = cell_to_rockchip_factor_clk_cell(&rk_cell->cell);

    rk_cell->cell.ops = &factor_cell->ops;

    factor_cell->ops.recalc_rate = clk_factor_recalc_rate;
    factor_cell->ops.round_rate = clk_factor_round_rate;
    factor_cell->ops.set_rate = clk_factor_set_rate;

    if (rk_cell->gate_offset >= 0)
    {
        factor_cell->ops.enable = rockchip_gate_clk_ops.enable;
        factor_cell->ops.disable = rockchip_gate_clk_ops.disable;
        factor_cell->ops.is_enabled = rockchip_gate_clk_ops.is_enabled;
    }
}
