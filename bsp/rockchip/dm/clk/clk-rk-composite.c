/*
 * Copyright (c) 2006-2022, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2022-3-08      GuEe-GUI     the first version
 */

#include "clk-rk-composite.h"
#include "clk-rk-divider.h"
#include "clk-rk-gate.h"
#include "clk-rk-mux.h"

void rockchip_composite_clk_cell_init(struct rockchip_clk_cell *rk_cell)
{
	struct rockchip_composite_clk_cell *composite_cell = cell_to_rockchip_composite_cell(&rk_cell->cell);

    rk_cell->cell.ops = &composite_cell->ops;

	if (rk_cell->cell.parents_nr > 1)
	{
		rockchip_mux_clk_cell_init(rk_cell);

        composite_cell->ops.get_parent = rockchip_mux_clk_ops.get_parent;

        if (!((rk_cell->mux_flags & CLK_MUX_READ_ONLY)))
        {
            composite_cell->ops.set_parent = rockchip_mux_clk_ops.set_parent;
        }
	}

    if (rk_cell->gate_offset >= 0)
    {
        composite_cell->ops.enable = rockchip_gate_clk_ops.enable;
        composite_cell->ops.disable = rockchip_gate_clk_ops.disable;
        composite_cell->ops.is_enabled = rockchip_gate_clk_ops.is_enabled;
    }

    if (rk_cell->div_width > 0)
    {
        composite_cell->ops.recalc_rate = clk_divider_ops.recalc_rate;
        composite_cell->ops.round_rate = clk_divider_ops.round_rate;

        if (!((rk_cell->div_flags & CLK_DIVIDER_READ_ONLY)))
        {
            composite_cell->ops.set_rate = clk_divider_ops.set_rate;
        }
    }
}
