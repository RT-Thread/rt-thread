/*
 * Copyright (c) 2006-2022, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2022-3-08      GuEe-GUI     the first version
 */

#ifndef __CLK_RK_H__
#define __CLK_RK_H__

#include <rockchip.h>

struct rockchip_clk_provider
{
    void *reg_base;
    struct rt_syscon *grf;
    struct rt_syscon *pmugrf;
};

struct clk_div_table
{
    rt_uint32_t val;
    rt_uint32_t div;
};

struct rockchip_clk_cell
{
    struct rt_clk_cell cell;

    int id;

    int muxdiv_offset;
    rt_uint8_t mux_shift;
    rt_uint8_t mux_width;
#define CLK_MUX_INDEX_ONE                   RT_BIT(0)
#define CLK_MUX_INDEX_BIT                   RT_BIT(1)
#define CLK_MUX_HIWORD_MASK                 RT_BIT(2)
#define CLK_MUX_READ_ONLY                   RT_BIT(3)
#define CLK_MUX_ROUND_CLOSEST               RT_BIT(4)
#define CLK_MUX_BIG_ENDIAN                  RT_BIT(5)
    rt_uint8_t mux_flags;
    rt_uint32_t mux_mask;
    rt_uint32_t *mux_table;

    int div_offset;
    rt_uint8_t div_shift;
    rt_uint8_t div_width;
#define CLK_DIVIDER_ONE_BASED               RT_BIT(0)
#define CLK_DIVIDER_POWER_OF_TWO            RT_BIT(1)
#define CLK_DIVIDER_ALLOW_ZERO              RT_BIT(2)
#define CLK_DIVIDER_HIWORD_MASK             RT_BIT(3)
#define CLK_DIVIDER_ROUND_CLOSEST           RT_BIT(4)
#define CLK_DIVIDER_READ_ONLY               RT_BIT(5)
#define CLK_DIVIDER_MAX_AT_ZERO             RT_BIT(6)
#define CLK_DIVIDER_BIG_ENDIAN              RT_BIT(7)

#define CLK_FRAC_DIVIDER_ZERO_BASED         RT_BIT(0)
#define CLK_FRAC_DIVIDER_BIG_ENDIAN         RT_BIT(1)
#define CLK_FRAC_DIVIDER_POWER_OF_TWO_PS    RT_BIT(2)
#define CLK_FRAC_DIVIDER_NO_LIMIT           RT_BIT(3)
    rt_uint8_t div_flags;
    struct clk_div_table *div_table;

    int gate_offset;
    rt_uint8_t gate_shift;
#define CLK_GATE_SET_TO_DISABLE             RT_BIT(0)
#define CLK_GATE_HIWORD_MASK                RT_BIT(1)
#define CLK_GATE_BIG_ENDIAN                 RT_BIT(2)
    rt_uint8_t gate_flags;

    struct rockchip_clk_provider *provider;
    void (*init)(struct rockchip_clk_cell *cell);
    void (*setup)(struct rockchip_clk_cell *cell);
};

#define cell_to_rockchip_clk_cell(cell) rt_container_of(cell, struct rockchip_clk_cell, cell)

#define PNAME(x)    static const char *const x
#define PNAMES(x)   PNAME(x)[]

void rational_best_approximation(rt_ubase_t given_numerator,
        rt_ubase_t given_denominator,
        rt_ubase_t max_numerator,
        rt_ubase_t max_denominator,
        rt_ubase_t *best_numerator,
        rt_ubase_t *best_denominator);

#define ROCKCHIP_SOFTRST_HIWORD_MASK    RT_BIT(0)

int rockchip_gcd(int m, int n);

void rockchip_clk_init(struct rockchip_clk_provider *provider,
        struct rt_clk_cell **cells, rt_size_t cells_nr);

void rockchip_clk_setup(struct rockchip_clk_provider *provider,
        struct rt_clk_cell **cells, rt_size_t cells_nr);

rt_err_t rockchip_register_softrst(struct rt_reset_controller *rstcer,
        struct rt_ofw_node *np, const int *lookup_table, void *regs, rt_uint8_t flags);

void rockchip_register_restart_notifier(struct rockchip_clk_provider *provider,
        rt_uint32_t reg, void (*callback)(struct rockchip_clk_provider *provider));

#endif /* __CLK_RK_H__ */
