/*
 * Copyright (c) 2006-2022, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2022-3-08      GuEe-GUI     the first version
 */

#include "clk-rk-muxgrf.h"

static rt_err_t rockchip_muxgrf_set_parent_common(struct rt_clk_cell *cell, struct rt_syscon *grf,
        rt_uint8_t index)
{
    rt_uint32_t mask, val;
    struct rockchip_clk_cell *rk_cell = cell_to_rockchip_clk_cell(cell);

    mask = RT_GENMASK(rk_cell->mux_width + rk_cell->mux_shift - 1, rk_cell->mux_shift);

    val = index;
    val <<= rk_cell->mux_shift;

    if (rk_cell->mux_flags & CLK_MUX_HIWORD_MASK)
    {
        return rt_syscon_write(grf, rk_cell->muxdiv_offset, val | (mask << 16));
    }

    return rt_syscon_update_bits(grf, rk_cell->muxdiv_offset, mask, val);
}

static rt_uint8_t rockchip_muxgrf_get_parent_common(struct rt_clk_cell *cell, struct rt_syscon *grf)
{
    rt_uint32_t mask, val;
    struct rockchip_clk_cell *rk_cell = cell_to_rockchip_clk_cell(cell);

    mask = RT_GENMASK(rk_cell->mux_width - 1, 0);

    rt_syscon_read(grf, rk_cell->muxdiv_offset, &val);

    val >>= rk_cell->mux_shift;
    val &= mask;

    return val;
}

static rt_err_t rockchip_muxgrf_set_parent(struct rt_clk_cell *cell, rt_uint8_t index)
{
    struct rockchip_clk_cell *rk_cell = cell_to_rockchip_clk_cell(cell);

    return rockchip_muxgrf_set_parent_common(cell, rk_cell->provider->grf, index);
}

static rt_uint8_t rockchip_muxgrf_get_parent(struct rt_clk_cell *cell)
{
    struct rockchip_clk_cell *rk_cell = cell_to_rockchip_clk_cell(cell);

    return rockchip_muxgrf_get_parent_common(cell, rk_cell->provider->grf);
}

const struct rt_clk_ops rockchip_muxgrf_clk_ops =
{
    .set_parent = rockchip_muxgrf_set_parent,
    .get_parent = rockchip_muxgrf_get_parent,
};

static rt_err_t rockchip_muxpmugrf_set_parent(struct rt_clk_cell *cell, rt_uint8_t index)
{
    struct rockchip_clk_cell *rk_cell = cell_to_rockchip_clk_cell(cell);

    return rockchip_muxgrf_set_parent_common(cell, rk_cell->provider->pmugrf, index);
}

static rt_uint8_t rockchip_muxpmugrf_get_parent(struct rt_clk_cell *cell)
{
    struct rockchip_clk_cell *rk_cell = cell_to_rockchip_clk_cell(cell);

    return rockchip_muxgrf_get_parent_common(cell, rk_cell->provider->pmugrf);
}

const struct rt_clk_ops rockchip_muxpmugrf_clk_ops =
{
    .set_parent = rockchip_muxpmugrf_set_parent,
    .get_parent = rockchip_muxpmugrf_get_parent,
};
