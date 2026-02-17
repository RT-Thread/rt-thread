/*
 * Copyright (c) 2006-2022, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2022-3-08      GuEe-GUI     the first version
 */

#ifndef __CLK_RK_PLL_H__
#define __CLK_RK_PLL_H__

#include "clk-rk.h"

enum rockchip_pll_type
{
    pll_type_rk3036,
    pll_type_rk3066,
    pll_type_rk3328,
    pll_type_rk3399,
    pll_type_rk3588,
    pll_type_rk3588_core,
    pll_type_rk3588_ddr,
};

struct rockchip_pll_rate_table
{
    rt_ubase_t rate;
    union
    {
        struct
        {
            /* For RK3066 */
            rt_uint32_t nr;
            rt_uint32_t nf;
            rt_uint32_t no;
            rt_uint32_t nb;
        };
        struct
        {
            /* For RK3036/RK3399 */
            rt_uint32_t fbdiv;
            rt_uint32_t postdiv1;
            rt_uint32_t refdiv;
            rt_uint32_t postdiv2;
            rt_uint32_t dsmpd;
            rt_uint32_t frac;
        };
        struct
        {
            /* For RK3588 */
            rt_uint32_t m;
            rt_uint32_t p;
            rt_uint32_t s;
            rt_uint32_t k;
        };
    };
};

#define RK3066_PLL_RATE(_rate, _nr, _nf, _no) \
{                                       \
    .rate = _rate##U,                   \
    .nr = _nr,                          \
    .nf = _nf,                          \
    .no = _no,                          \
    .nb = ((_nf) < 2) ? 1 : (_nf) >> 1, \
}

#define RK3036_PLL_RATE(_rate, _refdiv, _fbdiv, _postdiv1, _postdiv2, _dsmpd, _frac) \
{                           \
    .rate = _rate##U,       \
    .fbdiv = _fbdiv,        \
    .postdiv1 = _postdiv1,  \
    .refdiv = _refdiv,      \
    .postdiv2 = _postdiv2,  \
    .dsmpd = _dsmpd,        \
    .frac = _frac,          \
}

#define RK3588_PLL_RATE(_rate, _p, _m, _s, _k) \
{                       \
    .rate = _rate##U,   \
    .p = _p,            \
    .m = _m,            \
    .s = _s,            \
    .k = _k,            \
}

struct rockchip_pll_clk_cell
{
    struct rockchip_clk_cell rk_cell;

    enum rockchip_pll_type type;

    int con_offset;
    int mode_offset;
    int mode_shift;
    int lock_shift;
    int grf_lock_offset;

    int sel;
    rt_ubase_t scaling;

#define ROCKCHIP_PLL_SYNC_RATE          RT_BIT(0)
#define ROCKCHIP_PLL_FIXED_MODE         RT_BIT(1)
#define ROCKCHIP_PLL_ALLOW_POWER_DOWN   RT_BIT(2)
    rt_uint8_t flags;
    struct rockchip_pll_rate_table *rate_table;
};

#define PLL_RAW(_type, _id, _name, _pnames, _pnames_nr, _flags, _con, _mode, _mshift, _lshift, _glock, _pflags, _rtable) \
{                                                               \
    .rk_cell.cell.name = _name,                                 \
    .rk_cell.cell.parent_names = (void *)_pnames,               \
    .rk_cell.cell.parents_nr = _pnames_nr,                      \
    .rk_cell.cell.flags = RT_CLK_F_GET_RATE_NOCACHE | _flags,   \
    .rk_cell.id = _id,                                          \
    .rk_cell.init = rockchip_pll_clk_cell_init,                 \
    .rk_cell.setup = rockchip_pll_clk_cell_setup,               \
    .type = _type,                                              \
    .con_offset = _con,                                         \
    .mode_offset = _mode,                                       \
    .mode_shift = _mshift,                                      \
    .lock_shift = _lshift,                                      \
    .grf_lock_offset = _glock,                                  \
    .flags = _pflags,                                           \
    .rate_table = _rtable,                                      \
}

#define PLL(_type, _id, _name, _pnames, _pnames_nr, _flags, _con, _mode, _mshift, _lshift, _glock, _pflags, _rtable) \
    (void *)&(struct rockchip_pll_clk_cell)PLL_RAW(_type, _id, _name, _pnames, _pnames_nr, _flags, _con, _mode, _mshift, _lshift, _glock, _pflags, _rtable)

rt_inline struct rockchip_pll_clk_cell *cell_to_rockchip_pll_clk_cell(struct rt_clk_cell *cell)
{
    struct rockchip_clk_cell *rk_cell = cell_to_rockchip_clk_cell(cell);

    return rt_container_of(rk_cell, struct rockchip_pll_clk_cell, rk_cell);
}

void rockchip_pll_clk_cell_init(struct rockchip_clk_cell *rk_cell);
void rockchip_pll_clk_cell_setup(struct rockchip_clk_cell *rk_cell);

#endif /* __CLK_RK_PLL_H__ */
