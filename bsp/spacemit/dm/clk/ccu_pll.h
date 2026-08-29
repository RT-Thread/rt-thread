/*
 * Copyright (c) 2006-2024, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2024-5-1       GuEe-GUI     first version
 */

#ifndef __CCU_PLL_H__
#define __CCU_PLL_H__

#include "ccu.h"

struct ccu_pll_rate_tbl
{
    rt_uint64_t rate;
    rt_uint32_t reg5;
    rt_uint32_t reg6;
    rt_uint32_t reg7;
    rt_uint32_t reg8;
    rt_uint32_t div_int;
    rt_uint32_t div_frac;
};

struct ccu_pll_config
{
    rt_uint32_t tbl_size;
    struct ccu_pll_rate_tbl *rate_tbl;

    void *lock_base;
    rt_uint32_t reg_lock;
    rt_uint32_t lock_enable_bit;
};

struct ccu_pll
{
    struct ccu_common common;
    struct ccu_pll_config pll;
};

#define PLL_RATE(_rate, _reg5, _reg6, _reg7, _reg8, _div_int, _div_frac) \
{                               \
    .rate = (_rate),            \
    .reg5 = (_reg5),            \
    .reg6 = (_reg6),            \
    .reg7 = (_reg7),            \
    .reg8 = (_reg8),            \
    .div_int = (_div_int),      \
    .div_frac = (_div_frac),    \
}

#define _SPACEMIT_CCU_PLL_CONFIG(_table, _size, _reg_lock, _lock_enable_bit) \
{                                                   \
    .rate_tbl = (struct ccu_pll_rate_tbl *)_table,  \
    .tbl_size = _size,                              \
    .reg_lock = _reg_lock,                          \
    .lock_enable_bit = _lock_enable_bit,            \
}

#define SPACEMIT_CCU_PLL(_struct, _name, _table, _size, _base_type, \
                        _reg_ctrl, _reg_sel, _reg_xtc, \
                        _reg_lock, _lock_enable_bit, _is_pll, _flags) \
struct ccu_pll _struct =            \
{                                   \
    .pll = _SPACEMIT_CCU_PLL_CONFIG(_table, _size, _reg_lock, _lock_enable_bit), \
    .common =                       \
    {                               \
        .reg_ctrl = _reg_ctrl,      \
        .reg_sel = _reg_sel,        \
        .reg_xtc = _reg_xtc,        \
        .base_type = _base_type,    \
        .is_pll = _is_pll,          \
        .cell.name = _name,         \
        .cell.ops = &ccu_pll_ops,   \
        .cell.flags = _flags,       \
    },                              \
}

extern const struct rt_clk_ops ccu_pll_ops;

rt_inline struct ccu_pll *cell_to_ccu_pll(struct rt_clk_cell *cell)
{
    struct ccu_common *common = cell_to_ccu_common(cell);

    return rt_container_of(common, struct ccu_pll, common);
}

#endif /* __CCU_PLL_H__ */
