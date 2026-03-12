/*
 * Copyright (c) 2006-2022, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2022-3-08      GuEe-GUI     the first version
 */

#include "clk-rk-gate.h"

rt_inline rt_uint32_t clk_gate_readl(struct rockchip_clk_cell *rk_cell)
{
    void *base = rk_cell->provider->reg_base;

    if (rk_cell->gate_flags & CLK_GATE_BIG_ENDIAN)
    {
        return rt_be32_to_cpu(HWREG32(base + rk_cell->gate_offset));
    }

    return HWREG32(base + rk_cell->gate_offset);
}

rt_inline void clk_gate_writel(struct rockchip_clk_cell *rk_cell, rt_uint32_t val)
{
    void *base = rk_cell->provider->reg_base;

    if (rk_cell->gate_flags & CLK_GATE_BIG_ENDIAN)
    {
        HWREG32(base + rk_cell->gate_offset) = rt_cpu_to_be32(val);
    }
    else
    {
        HWREG32(base + rk_cell->gate_offset) = val;
    }
}

static void clk_gate_endisable(struct rt_clk_cell *cell, int enable)
{
    int set;
    rt_uint32_t reg;
    struct rockchip_clk_cell *rk_cell = cell_to_rockchip_clk_cell(cell);

    set = rk_cell->gate_flags & CLK_GATE_SET_TO_DISABLE ? 1 : 0;
    set ^= enable;

    if (rk_cell->gate_flags & CLK_GATE_HIWORD_MASK)
    {
        reg = RT_BIT(rk_cell->gate_shift + 16);

        if (set)
        {
            reg |= RT_BIT(rk_cell->gate_shift);
        }
    }
    else
    {
        reg = clk_gate_readl(rk_cell);

        if (set)
        {
            reg |= RT_BIT(rk_cell->gate_shift);
        }
        else
        {
            reg &= ~RT_BIT(rk_cell->gate_shift);
        }
    }

    clk_gate_writel(rk_cell, reg);
}

static rt_err_t rockchip_gate_clk_enable(struct rt_clk_cell *cell)
{
    clk_gate_endisable(cell, 1);

    return RT_EOK;
}

static void rockchip_gate_clk_disable(struct rt_clk_cell *cell)
{
    clk_gate_endisable(cell, 0);
}

static rt_bool_t rockchip_gate_clk_is_enabled(struct rt_clk_cell *cell)
{
    rt_uint32_t reg;
    struct rockchip_clk_cell *rk_cell = cell_to_rockchip_clk_cell(cell);

    reg = clk_gate_readl(rk_cell);

    /* If a set bit disables this clk, flip it before masking */
    if (rk_cell->gate_flags & CLK_GATE_SET_TO_DISABLE)
    {
        reg ^= RT_BIT(rk_cell->gate_shift);
    }

    reg &= RT_BIT(rk_cell->gate_shift);

    return !!reg;
}

const struct rt_clk_ops rockchip_gate_clk_ops =
{
    .enable = rockchip_gate_clk_enable,
    .disable = rockchip_gate_clk_disable,
    .is_enabled = rockchip_gate_clk_is_enabled,
};
