/*
 * Copyright (c) 2006-2026, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#ifndef __SUNXI_PINCTRL_H__
#define __SUNXI_PINCTRL_H__

#include <rtthread.h>

struct sunxi_pinctrl_layout
{
    rt_uint16_t bank_stride;
    rt_uint16_t mux_reg;
    rt_uint16_t data_reg;
    rt_uint16_t drive_reg;
    rt_uint16_t pull_reg;
    rt_uint8_t mux_bits;
    rt_uint8_t drive_bits;
    rt_uint8_t pull_bits;
    rt_uint8_t disabled_mux;
};

struct sunxi_pinctrl_function
{
    const char *name;
    rt_uint8_t bank;
    rt_uint8_t first_pin;
    rt_uint8_t pin_count;
    rt_uint8_t mux;
};

struct sunxi_pinctrl_data
{
    const struct sunxi_pinctrl_layout *layout;
    const rt_uint8_t *bank_pins;
    const struct sunxi_pinctrl_function *functions;
    rt_size_t functions_nr;
    rt_uint8_t banks_nr;
    rt_uint8_t irq_banks;
    rt_uint8_t irq_mux;
};

extern const struct sunxi_pinctrl_data sun252i_f101_pinctrl_data;

#endif /* __SUNXI_PINCTRL_H__ */
