/*
 * Copyright (c) 2006-2026, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#ifndef __SUNXI_CCU_H__
#define __SUNXI_CCU_H__

#include <rtthread.h>

struct sunxi_clk_desc
{
    int id;
    const char *name;
    const char *rate_property;
    rt_uint16_t gate_reg;
    rt_uint32_t gate_mask;
    rt_ubase_t rate_default;

    const rt_ubase_t *parent_rates;
    rt_uint8_t parent_rates_nr;
    rt_uint8_t m_shift;
    rt_uint8_t m_width;
    rt_uint8_t p_shift;
    rt_uint8_t p_width;
    rt_uint8_t mux_shift;
    rt_uint8_t mux_width;
};

struct sunxi_ccu_data
{
    const struct sunxi_clk_desc *clks;
    rt_size_t clks_nr;
    rt_size_t cells_nr;
};

extern const struct sunxi_ccu_data sun252i_f101_ccu_data;

#endif /* __SUNXI_CCU_H__ */
