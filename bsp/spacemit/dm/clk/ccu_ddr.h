/*
 * Copyright (c) 2006-2024, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2024-5-1       GuEe-GUI     first version
 */

#ifndef __CCU_DDR_H__
#define __CCU_DDR_H__

#include "ccu.h"
#include "ccu_mix.h"

struct ccu_ddr
{
    struct ccu_common common;
    struct ccu_mux_config *mux;
};

#define MAX_FREQ_LV 7  /* level 0~7 */

#define SPACEMIT_CCU_DDR_FC(_struct, _name, _parents, _base_type, \
                            _reg, _fc, _shift, _width, _flags) \
struct ccu_ddr _struct =                            \
{                                                   \
    .mux = CCU_MUX_INIT(_shift, _width, RT_NULL),   \
    .common =                                       \
    {                                               \
        .reg_sel = _reg,                            \
        .fc = _fc,                                  \
        .base_type = _base_type,                    \
        .cell.name = _name,                         \
        .cell.parent_names = _parents,              \
        .cell.parents_nr = RT_ARRAY_SIZE(_parents), \
        .cell.ops = &ccu_ddr_ops,                   \
        .cell.flags = _flags,                       \
    },                                              \
}

extern const struct rt_clk_ops ccu_ddr_ops;

rt_inline struct ccu_ddr *cell_to_ccu_ddr(struct rt_clk_cell *cell)
{
    struct ccu_common *common = cell_to_ccu_common(cell);

    return rt_container_of(common, struct ccu_ddr, common);
}

#endif /* __CCU_DDR_H__ */
