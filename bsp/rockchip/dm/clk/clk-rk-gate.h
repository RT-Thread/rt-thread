/*
 * Copyright (c) 2006-2022, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2022-3-08      GuEe-GUI     the first version
 */

#ifndef __CLK_RK_GATE_H__
#define __CLK_RK_GATE_H__

#include "clk-rk.h"

#define GATE(_id, cname, pname, f, o, b, gf)    \
(void *)&(struct rockchip_clk_cell)             \
{                                               \
    .cell.name = cname,                         \
    .cell.ops = &rockchip_gate_clk_ops,         \
    .cell.parent_name = pname,                  \
    .cell.parents_nr = 1,                       \
    .cell.flags = f | RT_CLK_F_SET_RATE_PARENT, \
    .id = _id,                                  \
    .gate_offset = o,                           \
    .gate_shift = b,                            \
    .gate_flags = gf,                           \
}

extern const struct rt_clk_ops rockchip_gate_clk_ops;

#endif /* __CLK_RK_GATE_H__ */
