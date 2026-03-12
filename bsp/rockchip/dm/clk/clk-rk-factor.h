/*
 * Copyright (c) 2006-2022, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2022-3-08      GuEe-GUI     the first version
 */

#ifndef __CLK_RK_FACTOR_H__
#define __CLK_RK_FACTOR_H__

#include "clk-rk.h"

struct rockchip_factor_clk_cell
{
    struct rockchip_clk_cell rk_cell;

    struct rt_clk_ops ops;
};

#define FACTOR(_id, cname, pname, f, fm, fd)        \
(void *)&(struct rockchip_factor_clk_cell)          \
{                                                   \
    .rk_cell.cell.name = cname,                     \
    .rk_cell.cell.parent_name = pname,              \
    .rk_cell.cell.parents_nr = 1,                   \
    .rk_cell.cell.flags = f,                        \
    .rk_cell.id = _id,                              \
    .rk_cell.div_shift = fm,                        \
    .rk_cell.div_width = fd,                        \
    .rk_cell.init = rockchip_factor_clk_cell_init,  \
}

#define FACTOR_GATE(_id, cname, pname, f, fm, fd, go, gb, gf) \
(void *)&(struct rockchip_factor_clk_cell)          \
{                                                   \
    .rk_cell.cell.name = cname,                     \
    .rk_cell.cell.parent_name = pname,              \
    .rk_cell.cell.parents_nr = 1,                   \
    .rk_cell.cell.flags = f,                        \
    .rk_cell.id = _id,                              \
    .rk_cell.div_shift = fm,                        \
    .rk_cell.div_width = fd,                        \
    .rk_cell.gate_offset = go,                      \
    .rk_cell.gate_shift = gb,                       \
    .rk_cell.gate_flags = gf,                       \
    .rk_cell.init = rockchip_factor_clk_cell_init,  \
}

#define SGRF_GATE(_id, cname, pname)    FACTOR(_id, cname, pname, 0, 1, 1)

rt_inline struct rockchip_factor_clk_cell *cell_to_rockchip_factor_clk_cell(struct rt_clk_cell *cell)
{
    struct rockchip_clk_cell *rk_cell = cell_to_rockchip_clk_cell(cell);

    return rt_container_of(rk_cell, struct rockchip_factor_clk_cell, rk_cell);
}

void rockchip_factor_clk_cell_init(struct rockchip_clk_cell *rk_cell);

#endif /* __CLK_RK_FACTOR_H__ */
