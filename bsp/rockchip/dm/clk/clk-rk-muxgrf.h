/*
 * Copyright (c) 2006-2022, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2022-3-08      GuEe-GUI     the first version
 */

#ifndef __CLK_RK_MUXGRF_H__
#define __CLK_RK_MUXGRF_H__

#include "clk-rk.h"

#define MUXGRF(_id, cname, pnames, f, o, s, w, mf) \
(void *)&(struct rockchip_clk_cell)             \
{                                               \
    .cell.name = cname,                         \
    .cell.ops = &rockchip_muxgrf_clk_ops,       \
    .cell.parent_names = pnames,                \
    .cell.parents_nr = RT_ARRAY_SIZE(pnames),   \
    .cell.flags = f,                            \
    .id = _id,                                  \
    .muxdiv_offset = o,                         \
    .mux_shift = s,                             \
    .mux_width = w,                             \
    .mux_flags = mf,                            \
    .gate_offset = -1,                          \
}

#define MUXPMUGRF(_id, cname, pnames, f, o, s, w, mf) \
(void *)&(struct rockchip_clk_cell)             \
{                                               \
    .cell.name = cname,                         \
    .cell.ops = &rockchip_muxpmugrf_clk_ops,    \
    .cell.parent_names = pnames,                \
    .cell.parents_nr = RT_ARRAY_SIZE(pnames),   \
    .cell.flags = f,                            \
    .id = _id,                                  \
    .muxdiv_offset = o,                         \
    .mux_shift = s,                             \
    .mux_width = w,                             \
    .mux_flags = mf,                            \
    .gate_offset = -1,                          \
}

extern const struct rt_clk_ops rockchip_muxgrf_clk_ops, rockchip_muxpmugrf_clk_ops;

#endif /* __CLK_RK_MUXGRF_H__ */
