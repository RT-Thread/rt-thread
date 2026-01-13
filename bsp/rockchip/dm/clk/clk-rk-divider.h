/*
 * Copyright (c) 2006-2022, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2022-3-08      GuEe-GUI     the first version
 */

#ifndef __CLK_RK_DIVIDER_H__
#define __CLK_RK_DIVIDER_H__

#include "clk-rk.h"

#define DIV(_id, cname, pname, f, o, s, w, df)  \
(void *)&(struct rockchip_clk_cell)         \
{                                           \
    .cell.name = cname,                     \
    .cell.parent_name = pname,              \
    .cell.parents_nr = 1,                   \
    .cell.flags = f,                        \
    .id = _id,                              \
    .muxdiv_offset = o,                     \
    .div_shift = s,                         \
    .div_width = w,                         \
    .div_flags = df,                        \
    .gate_offset = -1,                      \
    .init = rockchip_divider_clk_cell_init, \
}

#define DIVTBL(_id, cname, pname, f, o, s, w, df, dt) \
(void *)&(struct rockchip_clk_cell)         \
{                                           \
    .cell.name = cname,                     \
    .cell.parent_name = pname,              \
    .cell.parents_nr = 1,                   \
    .cell.flags = f,                        \
    .id = _id,                              \
    .muxdiv_offset = o,                     \
    .div_shift = s,                         \
    .div_width = w,                         \
    .div_flags = df,                        \
    .div_table = dt,                        \
    .init = rockchip_divider_clk_cell_init, \
}

extern const struct rt_clk_ops clk_divider_ops, clk_divider_ro_ops;

void rockchip_divider_clk_cell_init(struct rockchip_clk_cell *rk_cell);

#endif /* __CLK_RK_DIVIDER_H__ */
