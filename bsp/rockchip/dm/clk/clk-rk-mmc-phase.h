/*
 * Copyright (c) 2006-2022, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2022-3-08      GuEe-GUI     the first version
 */

#ifndef __CLK_RK_MMC_PHASE_H__
#define __CLK_RK_MMC_PHASE_H__

#include "clk-rk.h"

struct rockchip_mmc_clk_cell
{
    struct rockchip_clk_cell rk_cell;

    int cached_phase;
    struct rt_clk_notifier notifier;
};

#define MMC(_id, cname, pname, offset, shift)       \
(void *)&(struct rockchip_mmc_clk_cell)             \
{                                                   \
    .rk_cell.cell.name = cname,                     \
    .rk_cell.cell.ops = &rockchip_mmc_clk_ops,      \
    .rk_cell.cell.parent_name = pname,              \
    .rk_cell.cell.parents_nr = 1,                   \
    .rk_cell.id = _id,                              \
    .rk_cell.muxdiv_offset = offset,                \
    .rk_cell.div_shift = shift,                     \
    .rk_cell.setup = rockchip_mmc_clk_cell_setup,   \
}

extern const struct rt_clk_ops rockchip_mmc_clk_ops;

rt_inline struct rockchip_mmc_clk_cell *cell_to_rockchip_mmc_clk_cell(struct rt_clk_cell *cell)
{
    struct rockchip_clk_cell *rk_cell = cell_to_rockchip_clk_cell(cell);

    return rt_container_of(rk_cell, struct rockchip_mmc_clk_cell, rk_cell);
}

void rockchip_mmc_clk_cell_setup(struct rockchip_clk_cell *rk_cell);

#endif /* __CLK_RK_MMC_PHASE_H__ */
