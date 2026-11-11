/*
 * Copyright (c) 2006-2022, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2022-3-08      GuEe-GUI     the first version
 */

#ifndef __CLK_RK_CPU_H__
#define __CLK_RK_CPU_H__

#include "clk-rk.h"

#define ROCKCHIP_CPUCLK_NUM_DIVIDERS    6
#define ROCKCHIP_CPUCLK_MAX_CORES       4

struct rockchip_cpu_clk_clksel
{
    int reg;
    rt_uint32_t val;
};

struct rockchip_cpu_clk_rate_table
{
    rt_ubase_t prate;
    struct rockchip_cpu_clk_clksel divs[ROCKCHIP_CPUCLK_NUM_DIVIDERS];
    struct rockchip_cpu_clk_clksel pre_muxs[ROCKCHIP_CPUCLK_NUM_DIVIDERS];
    struct rockchip_cpu_clk_clksel post_muxs[ROCKCHIP_CPUCLK_NUM_DIVIDERS];
};

struct rockchip_cpu_clk_reg_data
{
    int core_reg[ROCKCHIP_CPUCLK_MAX_CORES];
    rt_uint8_t div_core_shift[ROCKCHIP_CPUCLK_MAX_CORES];
    rt_uint32_t div_core_mask[ROCKCHIP_CPUCLK_MAX_CORES];
    int num_cores;
    int mux_core_reg;
    rt_uint8_t mux_core_alt;
    rt_uint8_t mux_core_main;
    rt_uint8_t mux_core_shift;
    rt_uint32_t mux_core_mask;
    const char *pll_name;
};

struct rockchip_cpu_clk_cell
{
    struct rockchip_clk_cell rk_cell;
    struct rockchip_clk_cell *rk_cell_parent, *rk_cell_alt_parent;

    int rate_count;
    const struct rockchip_cpu_clk_rate_table *rate_table;
    const struct rockchip_cpu_clk_reg_data *reg_data;

    struct rt_clk_notifier notifier;
};

#define CPU(_id, cname, parent, alt_parent, _rates, _nrates, _reg_data) \
(void *)&(struct rockchip_cpu_clk_cell)                     \
{                                                           \
    .rk_cell.cell.name = cname,                             \
    .rk_cell.cell.ops = &rockchip_cpu_clk_ops,              \
    .rk_cell.cell.flags = RT_CLK_F_GET_RATE_NOCACHE,        \
    .rk_cell.id = _id,                                      \
    .rk_cell.init = rockchip_cpu_clk_cell_init,             \
    .rk_cell.setup = rockchip_cpu_clk_cell_setup,           \
    .rk_cell_parent = parent,                               \
    .rk_cell_alt_parent = alt_parent,                       \
    .rate_count = _nrates,                                  \
    .rate_table = _rates,                                   \
    .reg_data = _reg_data,                                  \
}

extern const struct rt_clk_ops rockchip_cpu_clk_ops;

rt_inline struct rockchip_cpu_clk_cell *cell_to_rockchip_cpu_cell(struct rt_clk_cell *cell)
{
    struct rockchip_clk_cell *rk_cell = cell_to_rockchip_clk_cell(cell);

    return rt_container_of(rk_cell, struct rockchip_cpu_clk_cell, rk_cell);
}

void rockchip_cpu_clk_cell_init(struct rockchip_clk_cell *rk_cell);
void rockchip_cpu_clk_cell_setup(struct rockchip_clk_cell *rk_cell);

#endif /* __CLK_RK_cpu_H__ */