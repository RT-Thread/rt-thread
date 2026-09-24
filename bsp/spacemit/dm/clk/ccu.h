/*
 * Copyright (c) 2006-2024, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2024-5-1       GuEe-GUI     first version
 */

#ifndef __CCU_H__
#define __CCU_H__

#include <rtthread.h>
#include <rtdevice.h>

#define CLK_DIVIDER_POWER_OF_TWO    RT_BIT(1)
#define CLK_DIVIDER_ALLOW_ZERO      RT_BIT(2)

enum
{
    CLK_DIV_TYPE_1REG_NOFC_V1 = 0,
    CLK_DIV_TYPE_1REG_FC_V2,
    CLK_DIV_TYPE_2REG_NOFC_V3,
    CLK_DIV_TYPE_2REG_FC_V4,
    CLK_DIV_TYPE_1REG_FC_DIV_V5,
    CLK_DIV_TYPE_1REG_FC_MUX_V6,
};

struct ccu_common
{
    void *base;

    rt_bool_t is_pll;
    rt_uint32_t base_type;

    rt_uint32_t reg_type;
    rt_uint32_t reg_ctrl;
    rt_uint32_t reg_sel;
    rt_uint32_t reg_xtc;
    rt_uint32_t fc;

    struct rt_spinlock *lock;

    rt_ubase_t rate;

    struct rt_clk_cell cell;
};

#define cell_to_ccu_common(cell) rt_container_of(cell, struct ccu_common, cell);

#endif /* __CCU_H__ */
