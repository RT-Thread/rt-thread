/*
 * Copyright (c) 2006-2024, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2024-5-1       GuEe-GUI     first version
 */

#ifndef __CCU_DPLL_H__
#define __CCU_DPLL_H__

#include "ccu.h"

struct ccu_dpll_rate_tbl
{
    rt_uint64_t rate;
    rt_uint32_t reg0;
    rt_uint32_t reg1;
    rt_uint32_t reg2;
    rt_uint32_t reg3;
    rt_uint32_t reg4;
    rt_uint32_t reg5;
    rt_uint32_t reg6;
    rt_uint32_t reg7;
};

struct ccu_dpll_config
{
    rt_uint32_t tbl_size;
    struct ccu_dpll_rate_tbl *rate_tbl;
};

struct ccu_dpll
{
    struct ccu_common common;
    struct ccu_dpll_config dpll;
};

#define DPLL_RATE(_rate, _reg0, _reg1, _reg2, _reg3, _reg4, _reg5, _reg6, _reg7) \
{                           \
    .rate   =   (_rate),    \
    .reg0   =   (_reg0),    \
    .reg1   =   (_reg1),    \
    .reg2   =   (_reg2),    \
    .reg3   =   (_reg3),    \
    .reg4   =   (_reg4),    \
    .reg5   =   (_reg5),    \
    .reg6   =   (_reg6),    \
    .reg7   =   (_reg7),    \
}

#define _SPACEMIT_CCU_DPLL_CONFIG(_table, _size)    \
{                                                   \
    .rate_tbl = (struct ccu_dpll_rate_tbl *)_table, \
    .tbl_size = _size,                              \
}

#define SPACEMIT_CCU_DPLL(_struct, _name, _table, _size, \
                         _base_type, _reg_ctrl, _reg_sel, _is_pll, _flags) \
struct ccu_dpll _struct =           \
{                                   \
    .dpll = _SPACEMIT_CCU_DPLL_CONFIG(_table, _size), \
    .common =                       \
    {                               \
        .reg_ctrl = _reg_ctrl,      \
        .reg_sel = _reg_sel,        \
        .base_type = _base_type,    \
        .is_pll = RT_FALSE,         \
        .cell.name = _name,         \
        .cell.ops = &ccu_dpll_ops,  \
        .cell.flags = _flags,       \
    },                              \
}

extern const struct rt_clk_ops ccu_dpll_ops;

rt_inline struct ccu_dpll *cell_to_ccu_dpll(struct rt_clk_cell *cell)
{
    struct ccu_common *common = cell_to_ccu_common(cell);

    return rt_container_of(common, struct ccu_dpll, common);
}

#endif /* __CCU_DPLL_H__ */
