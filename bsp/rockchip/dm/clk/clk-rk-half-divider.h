/*
 * Copyright (c) 2006-2022, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2022-3-08      GuEe-GUI     the first version
 */

#ifndef __CLK_RK_HALF_DIVIDER_H__
#define __CLK_RK_HALF_DIVIDER_H__

#include "clk-rk.h"

struct rockchip_half_divider_clk_cell
{
    struct rockchip_clk_cell rk_cell;

    struct rt_clk_ops ops;
};

#define COMPOSITE_HALFDIV(_id, cname, pnames, f, mo, ms, mw, mf, ds, dw, df, go, gs, gf) \
(void *)&(struct rockchip_half_divider_clk_cell)        \
{                                                       \
    .rk_cell.cell.name = cname,                         \
    .rk_cell.cell.parent_names = pnames,                \
    .rk_cell.cell.parents_nr = RT_ARRAY_SIZE(pnames),   \
    .rk_cell.cell.flags = f,                            \
    .rk_cell.id = _id,                                  \
    .rk_cell.muxdiv_offset = mo,                        \
    .rk_cell.mux_shift = ms,                            \
    .rk_cell.mux_width = mw,                            \
    .rk_cell.mux_flags = mf,                            \
    .rk_cell.div_shift = ds,                            \
    .rk_cell.div_width = dw,                            \
    .rk_cell.div_flags = df,                            \
    .rk_cell.gate_offset = go,                          \
    .rk_cell.gate_shift = gs,                           \
    .rk_cell.gate_flags = gf,                           \
    .rk_cell.init = rockchip_half_divider_clk_cell_init,\
}

#define COMPOSITE_HALFDIV_OFFSET(_id, cname, pnames, f, mo, ms, mw, mf, do, ds, dw, df, go, gs, gf) \
(void *)&(struct rockchip_half_divider_clk_cell)        \
{                                                       \
    .rk_cell.cell.name = cname,                         \
    .rk_cell.cell.parent_names = pnames,                \
    .rk_cell.cell.parents_nr = RT_ARRAY_SIZE(pnames),   \
    .rk_cell.cell.flags = f,                            \
    .rk_cell.id = _id,                                  \
    .rk_cell.muxdiv_offset = mo,                        \
    .rk_cell.mux_shift = ms,                            \
    .rk_cell.mux_width = mw,                            \
    .rk_cell.mux_flags = mf,                            \
    .rk_cell.div_offset = do,                           \
    .rk_cell.div_shift = ds,                            \
    .rk_cell.div_width = dw,                            \
    .rk_cell.div_flags = df,                            \
    .rk_cell.gate_offset = go,                          \
    .rk_cell.gate_shift = gs,                           \
    .rk_cell.gate_flags = gf,                           \
    .rk_cell.init = rockchip_half_divider_clk_cell_init,\
}

#define COMPOSITE_NOGATE_HALFDIV(_id, cname, pnames, f, mo, ms, mw, mf, ds, dw, df)                            \
(void *)&(struct rockchip_half_divider_clk_cell)        \
{                                                       \
    .rk_cell.cell.name = cname,                         \
    .rk_cell.cell.parent_names = pnames,                \
    .rk_cell.cell.parents_nr = RT_ARRAY_SIZE(pnames),   \
    .rk_cell.cell.flags = f,                            \
    .rk_cell.id = _id,                                  \
    .rk_cell.muxdiv_offset = mo,                        \
    .rk_cell.mux_shift = ms,                            \
    .rk_cell.mux_width = mw,                            \
    .rk_cell.mux_flags = mf,                            \
    .rk_cell.div_shift = ds,                            \
    .rk_cell.div_width = dw,                            \
    .rk_cell.div_flags = df,                            \
    .rk_cell.gate_offset = -1,                          \
    .rk_cell.init = rockchip_half_divider_clk_cell_init,\
}

#define COMPOSITE_NOMUX_HALFDIV(_id, cname, pname, f, mo, ds, dw, df, go, gs, gf)                             \
{                                                       \
    .rk_cell.cell.name = cname,                         \
    .rk_cell.cell.parent_name = pname,                  \
    .rk_cell.cell.parents_nr = 1,                       \
    .rk_cell.cell.flags = f,                            \
    .rk_cell.id = _id,                                  \
    .rk_cell.muxdiv_offset = mo,                        \
    .rk_cell.div_shift = ds,                            \
    .rk_cell.div_width = dw,                            \
    .rk_cell.div_flags = df,                            \
    .rk_cell.gate_offset = go,                          \
    .rk_cell.gate_shift = gs,                           \
    .rk_cell.gate_flags = gf,                           \
    .rk_cell.init = rockchip_half_divider_clk_cell_init,\
}

#define DIV_HALF(_id, cname, pname, f, o, s, w, df)     \
{                                                       \
    .rk_cell.cell.name = cname,                         \
    .rk_cell.cell.parent_name = pname,                  \
    .rk_cell.cell.parents_nr = 1,                       \
    .rk_cell.cell.flags = f,                            \
    .rk_cell.id = _id,                                  \
    .rk_cell.muxdiv_offset = o,                         \
    .rk_cell.div_shift = s,                             \
    .rk_cell.div_width = w,                             \
    .rk_cell.div_flags = df,                            \
    .rk_cell.gate_offset = -1,                          \
    .rk_cell.init = rockchip_half_divider_clk_cell_init,\
}

rt_inline struct rockchip_half_divider_clk_cell *cell_to_rockchip_half_divider_clk_cell(struct rt_clk_cell *cell)
{
    struct rockchip_clk_cell *rk_cell = cell_to_rockchip_clk_cell(cell);

    return rt_container_of(rk_cell, struct rockchip_half_divider_clk_cell, rk_cell);
}

void rockchip_half_divider_clk_cell_init(struct rockchip_clk_cell *rk_cell);

#endif /* __CLK_RK_HALF_DIVIDER_H__ */
