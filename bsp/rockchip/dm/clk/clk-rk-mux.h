/*
 * Copyright (c) 2006-2022, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2022-3-08      GuEe-GUI     the first version
 */

#ifndef __CLK_RK_MUX_H__
#define __CLK_RK_MUX_H__

#include "clk-rk.h"

#define MUX_RAW(_id, cname, pnames, f, o, s, w, mf) \
{                                               \
    .cell.name = cname,                         \
    .cell.parent_names = pnames,                \
    .cell.parents_nr = RT_ARRAY_SIZE(pnames),   \
    .cell.flags = f,                            \
    .id = _id,                                  \
    .muxdiv_offset = o,                         \
    .mux_shift = s,                             \
    .mux_width = w,                             \
    .mux_flags = mf,                            \
    .gate_offset = -1,                          \
    .init = rockchip_mux_clk_cell_init,         \
}

#define MUX(_id, cname, pnames, f, o, s, w, mf) \
    (void *)&(struct rockchip_clk_cell)MUX_RAW(_id, cname, pnames, f, o, s, w, mf)

#define MUXTBL_RAW(_id, cname, pnames, f, o, s, w, mf, mt) \
{                                               \
    .cell.name = cname,                         \
    .cell.parent_names = pname,                 \
    .cell.parents_nr = RT_ARRAY_SIZE(pnames),   \
    .cell.flags = f,                            \
    .id = _id,                                  \
    .muxdiv_offset = o,                         \
    .mux_shift = s,                             \
    .mux_width = w,                             \
    .mux_flags = mf,                            \
    .gate_offset = -1,                          \
    .mux_table = mt,                            \
    .init = rockchip_mux_clk_cell_init,         \
}

#define MUXTBL(_id, cname, pnames, f, o, s, w, mf, mt) \
    (void *)&(struct rockchip_clk_cell)MUXTBL_RAW(_id, cname, pnames, f, o, s, w, mf, mt)

extern const struct rt_clk_ops rockchip_mux_clk_ops, rockchip_mux_ro_clk_ops;

void rockchip_mux_clk_cell_init(struct rockchip_clk_cell *rk_cell);

#endif /* __CLK_RK_MUX_H__ */
