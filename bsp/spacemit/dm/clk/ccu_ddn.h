/*
 * Copyright (c) 2006-2024, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2024-5-1       GuEe-GUI     first version
 */

#ifndef __CCU_DDN_H__
#define __CCU_DDN_H__

#include "ccu.h"

struct ccu_ddn_tbl
{
    rt_uint32_t num;
    rt_uint32_t den;
};

struct ccu_ddn_info
{
    rt_uint32_t factor;
    rt_uint32_t num_mask;
    rt_uint32_t den_mask;
    rt_uint32_t num_shift;
    rt_uint32_t den_shift;
};

struct ccu_ddn_config
{
    rt_uint32_t tbl_size;
    struct ccu_ddn_tbl *tbl;
    struct ccu_ddn_info *info;
};

struct ccu_ddn
{
    struct ccu_common common;
    struct ccu_ddn_config ddn;
    rt_uint32_t gate;
};

#define PLL_DDN_TBL(_num, _den) \
{                   \
    .num = (_num),  \
    .den = (_den),  \
}

#define _SPACEMIT_CCU_DDN_CONFIG(_info, _table, _size) \
{                                           \
    .info = (struct ccu_ddn_info *)_info,   \
    .tbl = (struct ccu_ddn_tbl *)_table,    \
    .tbl_size = _size,                      \
}

#define SPACEMIT_CCU_DDN(_struct, _name, _parent, _info, _table, \
                        _size, _base_type, _reg_ctrl, _flags) \
struct ccu_ddn _struct =                \
{                                       \
    .ddn = _SPACEMIT_CCU_DDN_CONFIG(_info, _table, _size), \
    .common =                           \
    {                                   \
        .reg_ctrl = _reg_ctrl,          \
        .base_type = _base_type,        \
        .cell.name = _name,             \
        .cell.parent_name = _parent,    \
        .cell.parents_nr = 1,           \
        .cell.ops = &ccu_ddn_ops,       \
        .cell.flags = _flags,           \
    },                                  \
}

#define SPACEMIT_CCU_DDN_GATE(_struct, _name, _parent, _info, _table, _size, \
                              _base_type, _reg_ddn, _reg_gate, _gate_mask, _flags) \
struct ccu_ddn _struct =                \
{                                       \
    .gate   = _gate_mask,               \
    .ddn    = _SPACEMIT_CCU_DDN_CONFIG(_info, _table, _size), \
    .common =                           \
    {                                   \
        .reg_ctrl = _reg_ddn,           \
        .reg_sel = _reg_gate,           \
        .base_type = _base_type,        \
        .cell.name = _name,             \
        .cell.parent_name = _parent,    \
        .cell.parents_nr = 1,           \
        .cell.ops = &ccu_ddn_ops,       \
        .cell.flags = _flags,           \
    }                                   \
}

extern const struct rt_clk_ops ccu_ddn_ops;

rt_inline struct ccu_ddn *cell_to_ccu_ddn(struct rt_clk_cell *cell)
{
    struct ccu_common *common = cell_to_ccu_common(cell);

    return rt_container_of(common, struct ccu_ddn, common);
}

#endif /* __CCU_DDN_H__ */
