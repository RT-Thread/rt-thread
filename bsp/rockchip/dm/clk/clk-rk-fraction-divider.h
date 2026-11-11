/*
 * Copyright (c) 2006-2022, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2022-3-08      GuEe-GUI     the first version
 */

#ifndef __CLK_RK_FRACTION_DIVIDER_H__
#define __CLK_RK_FRACTION_DIVIDER_H__

#include "clk-rk.h"

struct rockchip_fraction_divider_clk_cell
{
    struct rockchip_clk_cell rk_cell;

    struct rt_clk_ops ops;
    struct rockchip_clk_cell *rk_cell_child;

    int mux_frac_idx;
    int rate_change_idx;
    int rate_change_remuxed;
    struct rt_clk_notifier notifier;
};

#define COMPOSITE_FRAC(_id, cname, pname, f, mo, df, go, gs, gf)\
(void *)&(struct rockchip_fraction_divider_clk_cell)            \
{                                                               \
    .rk_cell.cell.name = cname,                                 \
    .rk_cell.cell.parent_name = pname,                          \
    .rk_cell.cell.parents_nr = 1,                               \
    .rk_cell.cell.flags = f,                                    \
    .rk_cell.id = _id,                                          \
    .rk_cell.muxdiv_offset = mo,                                \
    .rk_cell.div_shift = 16,                                    \
    .rk_cell.div_width = 16,                                    \
    .rk_cell.div_flags = df,                                    \
    .rk_cell.gate_offset = go,                                  \
    .rk_cell.gate_shift = gs,                                   \
    .rk_cell.gate_flags = gf,                                   \
    .rk_cell.init = rockchip_fraction_divider_clk_cell_init,    \
}

#define COMPOSITE_FRACMUX(_id, cname, pname, f, mo, df, go, gs, gf, ch) \
(void *)&(struct rockchip_fraction_divider_clk_cell)            \
{                                                               \
    .rk_cell.cell.name = cname,                                 \
    .rk_cell.cell.parent_name = pname,                          \
    .rk_cell.cell.parents_nr = 1,                               \
    .rk_cell.cell.flags = f,                                    \
    .rk_cell.id = _id,                                          \
    .rk_cell.muxdiv_offset = mo,                                \
    .rk_cell.div_shift = 16,                                    \
    .rk_cell.div_width = 16,                                    \
    .rk_cell.div_flags = df,                                    \
    .rk_cell.gate_offset = go,                                  \
    .rk_cell.gate_shift = gs,                                   \
    .rk_cell.gate_flags = gf,                                   \
    .rk_cell.init = rockchip_fraction_divider_clk_cell_init,    \
    .rk_cell.setup = rockchip_fraction_divider_clk_cell_setup,  \
    .rk_cell_child = ch,                                        \
}

#define COMPOSITE_FRACMUX_NOGATE(_id, cname, pname, f, mo, df, ch) \
(void *)&(struct rockchip_fraction_divider_clk_cell)            \
{                                                               \
    .rk_cell.cell.name = cname,                                 \
    .rk_cell.cell.parent_name = pname,                          \
    .rk_cell.cell.parents_nr = 1,                               \
    .rk_cell.cell.flags = f,                                    \
    .rk_cell.id = _id,                                          \
    .rk_cell.muxdiv_offset = mo,                                \
    .rk_cell.div_shift = 16,                                    \
    .rk_cell.div_width = 16,                                    \
    .rk_cell.div_flags = df,                                    \
    .rk_cell.gate_offset = -1,                                  \
    .rk_cell.init = rockchip_fraction_divider_clk_cell_init,    \
    .rk_cell.setup = rockchip_fraction_divider_clk_cell_setup,  \
    .rk_cell_child = ch,                                        \
}

rt_inline struct rockchip_fraction_divider_clk_cell *cell_to_rockchip_fraction_divider_clk_cell(struct rt_clk_cell *cell)
{
    struct rockchip_clk_cell *rk_cell = cell_to_rockchip_clk_cell(cell);

    return rt_container_of(rk_cell, struct rockchip_fraction_divider_clk_cell, rk_cell);
}

void rockchip_fraction_divider_clk_cell_init(struct rockchip_clk_cell *rk_cell);
void rockchip_fraction_divider_clk_cell_setup(struct rockchip_clk_cell *rk_cell);

#endif /* __CLK_RK_FRACTION_DIVIDER_H__ */
