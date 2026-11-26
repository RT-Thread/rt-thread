/*
 * Copyright (c) 2006-2024, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2024-5-1       GuEe-GUI     first version
 */

#ifndef __CCU_MIX_H__
#define __CCU_MIX_H__

#include "ccu.h"

struct ccu_gate_config
{
    rt_uint32_t gate_mask;
    rt_uint32_t val_enable;
    rt_uint32_t val_disable;
#define SPACEMIT_CLK_GATE_NEED_DELAY    RT_BIT(0)
    rt_uint32_t flags;
};

struct ccu_factor_config
{
    rt_uint32_t div;
    rt_uint32_t mul;
};

struct ccu_mux_config
{
    rt_uint8_t shift;
    rt_uint8_t width;
    const rt_uint8_t *table;
};

struct ccu_div_table
{
    rt_uint32_t val;
    rt_uint32_t div;
};

struct ccu_div_config
{
    rt_uint8_t shift;
    rt_uint8_t width;
    rt_uint32_t max;
    rt_uint32_t offset;
    rt_uint32_t clk_flags;
    struct ccu_div_table *table;
};

struct ccu_mix
{
    struct ccu_common common;
    struct ccu_gate_config *gate;
    struct ccu_factor_config *factor;
    struct ccu_div_config *div;
    struct ccu_mux_config *mux;
};

#define CCU_GATE_INIT(_gate_mask, _val_enable, _val_disable, _flags) \
(&(struct ccu_gate_config)          \
{                                   \
    .gate_mask = _gate_mask,        \
    .val_enable = _val_enable,      \
    .val_disable = _val_disable,    \
    .flags = _flags,                \
})

#define CCU_FACTOR_INIT(_div, _mul) \
(&(struct ccu_factor_config)\
{                           \
    .div = _div,            \
    .mul = _mul,            \
})

#define CCU_MUX_INIT(_shift, _width, _table) \
(&(struct ccu_mux_config)   \
{                           \
    .shift = _shift,        \
    .width = _width,        \
    .table = _table,        \
})

#define CCU_DIV_INIT(_shift, _width, _table, _clk_flags) \
(&(struct ccu_div_config)       \
{                               \
    .shift = _shift,            \
    .width = _width,            \
    .table = _table,            \
    .clk_flags = _clk_flags,    \
})

#define SPACEMIT_CCU_GATE(_struct, _name, _parent, _base_type, _reg, \
                          _gate_mask, _val_enable, _val_disable, _flags) \
struct ccu_mix _struct =                \
{                                       \
    .gate = CCU_GATE_INIT(_gate_mask, _val_enable, _val_disable, 0), \
    .common =                           \
    {                                   \
        .reg_ctrl = _reg,               \
        .base_type = _base_type,        \
        .cell.name = _name,             \
        .cell.parent_name = _parent,    \
        .cell.parents_nr = 1,           \
        .cell.ops = &ccu_mix_ops,       \
        .cell.flags = _flags,           \
    },                                  \
}

#define SPACEMIT_CCU_GATE_NO_PARENT(_struct, _name, _parent, _base_type, _reg, \
                                    _gate_mask, _val_enable, _val_disable, _flags) \
struct ccu_mix _struct =                \
{                                       \
    .gate = CCU_GATE_INIT(_gate_mask, _val_enable, _val_disable, 0), \
    .common =                           \
    {                                   \
        .reg_ctrl = _reg,               \
        .base_type = _base_type,        \
        .cell.name = _name,             \
        .cell.parent_name = _parent,    \
        .cell.parents_nr = 1,           \
        .cell.ops = &ccu_mix_ops,       \
        .cell.flags = _flags,           \
    },                                  \
}

#define SPACEMIT_CCU_FACTOR(_struct, _name, _parent, _div, _mul) \
struct ccu_mix _struct =                \
{                                       \
    .factor = CCU_FACTOR_INIT(_div, _mul), \
    .common =                           \
    {                                   \
        .cell.name = _name,             \
        .cell.parent_name = _parent,    \
        .cell.parents_nr = 1,           \
        .cell.ops = &ccu_mix_ops,       \
    },                                  \
}

#define SPACEMIT_CCU_MUX(_struct, _name, _parents, _base_type, _reg, \
                         _shift, _width, _flags) \
struct ccu_mix _struct =                            \
{                                                   \
    .mux    = CCU_MUX_INIT(_shift, _width, RT_NULL),\
    .common =                                       \
    {                                               \
        .reg_ctrl = _reg,                           \
        .base_type = _base_type,                    \
        .cell.name = _name,                         \
        .cell.parent_names = _parents,              \
        .cell.parents_nr = RT_ARRAY_SIZE(_parents), \
        .cell.ops = &ccu_mix_ops,                   \
        .cell.flags = _flags,                       \
    }                                               \
}

#define SPACEMIT_CCU_DIV(_struct, _name, _parent, _base_type, _reg, \
                         _shift, _width, _flags) \
struct ccu_mix _struct =                \
{                                       \
    .div = CCU_DIV_INIT(_shift, _width, RT_NULL, 0), \
    .common =                           \
    {                                   \
        .reg_ctrl = _reg,               \
        .base_type = _base_type,        \
        .cell.name = _name,             \
        .cell.parent_name = _parent,    \
        .cell.parents_nr = 1,           \
        .cell.ops = &ccu_mix_ops,       \
        .cell.flags = _flags,           \
    }                                   \
}

#define SPACEMIT_CCU_DIV_FLAG(_struct, _name, _parent, _base_type, _reg, \
                              _shift, _width, _div_flags, _flags) \
struct ccu_mix _struct =                \
{                                       \
    .div = CCU_DIV_INIT(_shift, _width, RT_NULL, _div_flags), \
    .common =                           \
    {                                   \
        .reg_ctrl = _reg,               \
        .base_type = _base_type,        \
        .cell.name = _name,             \
        .cell.parent_name = _parent,    \
        .cell.parents_nr = 1,           \
        .cell.ops = &ccu_mix_ops,       \
        .cell.flags = _flags,           \
    }                                   \
}

#define SPACEMIT_CCU_GATE_FACTOR(_struct, _name, _parent, _base_type, _reg, \
                                 _gate_mask, _val_enable, _val_disable, _div, _mul, _flags) \
struct ccu_mix _struct =                \
{                                       \
    .gate = CCU_GATE_INIT(_gate_mask, _val_enable, _val_disable, 0), \
    .factor = CCU_FACTOR_INIT(_div, _mul), \
    .common =                           \
    {                                   \
        .reg_ctrl = _reg,               \
        .base_type = _base_type,        \
        .cell.name = _name,             \
        .cell.parent_name = _parent,    \
        .cell.parents_nr = 1,           \
        .cell.ops = &ccu_mix_ops,       \
        .cell.flags = _flags,           \
    }                                   \
}

#define SPACEMIT_CCU_MUX_GATE(_struct, _name, _parents, _base_type, _reg, \
                              _shift, _width, _gate_mask, _val_enable, _val_disable, _flags) \
struct ccu_mix _struct =                            \
{                                                   \
    .gate = CCU_GATE_INIT(_gate_mask, _val_enable, _val_disable, 0), \
    .mux = CCU_MUX_INIT(_shift, _width, RT_NULL),   \
    .common =                                       \
    {                                               \
        .reg_ctrl = _reg,                           \
        .base_type = _base_type,                    \
        .cell.name = _name,                         \
        .cell.parent_names = _parents,              \
        .cell.parents_nr = RT_ARRAY_SIZE(_parents), \
        .cell.ops = &ccu_mix_ops,                   \
        .cell.flags = _flags,                       \
    }                                               \
}

#define SPACEMIT_CCU_DIV_GATE(_struct, _name, _parent, _base_type, _reg, \
                              _shift, _width, _gate_mask, _val_enable, _val_disable, _flags) \
struct ccu_mix _struct =                \
{                                       \
    .gate = CCU_GATE_INIT(_gate_mask, _val_enable, _val_disable, 0), \
    .div = CCU_DIV_INIT(_shift, _width, RT_NULL, 0), \
    .common =                           \
    {                                   \
        .reg_ctrl = _reg,               \
        .base_type = _base_type,        \
        .cell.name = _name,             \
        .cell.parent_name = _parent,    \
        .cell.parents_nr = 1,           \
        .cell.ops = &ccu_mix_ops,       \
        .cell.flags = _flags,           \
    }                                   \
}

#define SPACEMIT_CCU_DIV_MUX_GATE(_struct, _name, _parents, _base_type, _reg_ctrl, \
                                  _mshift, _mwidth, _muxshift, _muxwidth, \
                                  _gate_mask, _val_enable, _val_disable, _flags) \
struct ccu_mix _struct =                            \
{                                                   \
    .gate = CCU_GATE_INIT(_gate_mask, _val_enable, _val_disable, 0), \
    .div = CCU_DIV_INIT(_mshift, _mwidth, RT_NULL, 0), \
    .mux = CCU_MUX_INIT(_muxshift, _muxwidth, RT_NULL), \
    .common =                                       \
    {                                               \
        .reg_ctrl = _reg_ctrl,                      \
        .base_type = _base_type,                    \
        .cell.name = _name,                         \
        .cell.parent_names = _parents,              \
        .cell.parents_nr = RT_ARRAY_SIZE(_parents), \
        .cell.ops = &ccu_mix_ops,                   \
        .cell.flags = _flags,                       \
    },                                              \
}

#define SPACEMIT_CCU_DIV2_FC_MUX_GATE(_struct, _name, _parents, _base_type, _reg_ctrl, _reg_sel, \
                                      _mshift, _mwidth, _fc, _muxshift, _muxwidth, _gate_mask, \
                                      _val_enable, _val_disable, _flags) \
struct ccu_mix _struct =                            \
{                                                   \
    .gate = CCU_GATE_INIT(_gate_mask, _val_enable, _val_disable, 0), \
    .div = CCU_DIV_INIT(_mshift, _mwidth, RT_NULL, 0), \
    .mux = CCU_MUX_INIT(_muxshift, _muxwidth, RT_NULL), \
    .common =                                       \
    {                                               \
        .reg_type = CLK_DIV_TYPE_2REG_FC_V4,        \
        .reg_ctrl = _reg_ctrl,                      \
        .reg_sel = _reg_sel,                        \
        .fc = _fc,                                  \
        .base_type = _base_type,                    \
        .cell.name = _name,                         \
        .cell.parent_names = _parents,              \
        .cell.parents_nr = RT_ARRAY_SIZE(_parents), \
        .cell.ops = &ccu_mix_ops,                   \
        .cell.flags = _flags,                       \
    },                                              \
}


#define SPACEMIT_CCU_DIV_FC_MUX_GATE(_struct, _name, _parents, _base_type, _reg_ctrl, \
                                    _mshift, _mwidth, _fc, _muxshift, _muxwidth, _gate_mask, \
                                    _val_enable, _val_disable, _flags) \
struct ccu_mix _struct =                            \
{                                                   \
    .gate = CCU_GATE_INIT(_gate_mask, _val_enable, _val_disable, 0), \
    .div = CCU_DIV_INIT(_mshift, _mwidth, RT_NULL, 0), \
    .mux = CCU_MUX_INIT(_muxshift, _muxwidth, RT_NULL), \
    .common =                                       \
    {                                               \
        .reg_type = CLK_DIV_TYPE_1REG_FC_V2,        \
        .reg_ctrl = _reg_ctrl,                      \
        .fc = _fc,                                  \
        .base_type = _base_type,                    \
        .cell.name = _name,                         \
        .cell.parent_names = _parents,              \
        .cell.parents_nr = RT_ARRAY_SIZE(_parents), \
        .cell.ops = &ccu_mix_ops,                   \
        .cell.flags = _flags,                       \
    },                                              \
}

#define SPACEMIT_CCU_DIV_MFC_MUX_GATE(_struct, _name, _parents, _base_type, _reg_ctrl, \
                                      _mshift, _mwidth, _fc, _muxshift, _muxwidth, _gate_mask, \
                                      _val_enable, _val_disable, _flags) \
struct ccu_mix _struct =                            \
{                                                   \
    .gate = CCU_GATE_INIT(_gate_mask, _val_enable, _val_disable, 0), \
    .div = CCU_DIV_INIT(_mshift, _mwidth, RT_NULL, 0), \
    .mux = CCU_MUX_INIT(_muxshift, _muxwidth, RT_NULL), \
    .common =                                       \
    {                                               \
        .reg_type = CLK_DIV_TYPE_1REG_FC_MUX_V6,    \
        .reg_ctrl = _reg_ctrl,                      \
        .fc = _fc,                                  \
        .base_type = _base_type,                    \
        .cell.name = _name,                         \
        .cell.parent_names = _parents,              \
        .cell.parents_nr = RT_ARRAY_SIZE(_parents), \
        .cell.ops = &ccu_mix_ops,                   \
        .cell.flags = _flags,                       \
    },                                              \
}

#define SPACEMIT_CCU_DIV_FC_WITH_GATE(_struct, _name, _parent, _base_type, _reg_ctrl, \
                                      _mshift, _mwidth, _fc, _gate_mask, _val_enable, _val_disable, _flags) \
struct ccu_mix _struct =                        \
{                                               \
    .gate = CCU_GATE_INIT(_gate_mask, _val_enable, _val_disable, 0), \
    .div = CCU_DIV_INIT(_mshift, _mwidth, RT_NULL, 0), \
    .common =                                   \
    {                                           \
        .reg_type = CLK_DIV_TYPE_1REG_FC_V2,    \
        .reg_ctrl = _reg_ctrl,                  \
        .fc = _fc,                              \
        .base_type = _base_type,                \
        .cell.name = _name,                     \
        .cell.parent_name = _parent,            \
        .cell.parents_nr = 1,                   \
        .cell.ops = &ccu_mix_ops,               \
        .cell.flags = _flags,                   \
    },                                          \
}

#define SPACEMIT_CCU_DIV_MUX(_struct, _name, _parents, _base_type, _reg_ctrl, \
                             _mshift, _mwidth, _muxshift, _muxwidth, _flags) \
struct ccu_mix _struct =                            \
{                                                   \
    .div = CCU_DIV_INIT(_mshift, _mwidth, RT_NULL, 0),  \
    .mux = CCU_MUX_INIT(_muxshift, _muxwidth, RT_NULL), \
    .common =                                       \
    {                                               \
        .reg_ctrl = _reg_ctrl,                      \
        .base_type = _base_type,                    \
        .cell.name = _name,                         \
        .cell.parent_names = _parents,              \
        .cell.parents_nr = RT_ARRAY_SIZE(_parents), \
        .cell.ops = &ccu_mix_ops,                   \
        .cell.flags = _flags,                       \
    },                                              \
}

#define SPACEMIT_CCU_DIV_FC_MUX(_struct, _name, _parents, _base_type, _reg_ctrl, \
                                _mshift, _mwidth, _fc, _muxshift, _muxwidth, _flags) \
struct ccu_mix _struct =                            \
{                                                   \
    .div = CCU_DIV_INIT(_mshift, _mwidth, RT_NULL, 0), \
    .mux = CCU_MUX_INIT(_muxshift, _muxwidth, RT_NULL), \
    .common =                                       \
    {                                               \
        .reg_type = CLK_DIV_TYPE_1REG_FC_V2,        \
        .reg_ctrl = _reg_ctrl,                      \
        .fc = _fc,                                  \
        .base_type = _base_type,                    \
        .cell.name = _name,                         \
        .cell.parent_names = _parents,              \
        .cell.parents_nr = RT_ARRAY_SIZE(_parents), \
        .cell.ops = &ccu_mix_ops,                   \
        .cell.flags = _flags,                       \
    },                                              \
}

#define SPACEMIT_CCU_MUX_FC(_struct, _name, _parents, _base_type, _reg_ctrl, \
                            _fc, _muxshift, _muxwidth, _flags) \
struct ccu_mix _struct =                            \
{                                                   \
    .mux = CCU_MUX_INIT(_muxshift, _muxwidth, RT_NULL), \
    .common =                                       \
    {                                               \
        .reg_type = CLK_DIV_TYPE_1REG_FC_V2,        \
        .reg_ctrl = _reg_ctrl,                      \
        .fc = _fc,                                  \
        .base_type = _base_type,                    \
        .cell.name = _name,                         \
        .cell.parent_names = _parents,              \
        .cell.parents_nr = RT_ARRAY_SIZE(_parents), \
        .cell.ops = &ccu_mix_ops,                   \
        .cell.flags = _flags,                       \
    },                                              \
}

extern const struct rt_clk_ops ccu_mix_ops;

rt_inline struct ccu_mix *cell_to_ccu_mix(struct rt_clk_cell *cell)
{
    struct ccu_common *common = cell_to_ccu_common(cell);

    return rt_container_of(common, struct ccu_mix, common);
}

#endif /* __CCU_MIX_H__ */
