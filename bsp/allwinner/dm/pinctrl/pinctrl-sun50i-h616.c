/*
 * Copyright (c) 2006-2026, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#include <rtdevice.h>
#include <sunxi_pinctrl.h>

static const struct sunxi_pinctrl_layout h616_layout = {
    .bank_stride = 0x24,
    .mux_reg = 0x00,
    .data_reg = 0x10,
    .drive_reg = 0x14,
    .pull_reg = 0x1c,
    .mux_bits = 4,
    .drive_bits = 2,
    .pull_bits = 2,
    .disabled_mux = 7,
};

/* Preserve hardware bank numbering and the holes between banks. */
static const rt_uint8_t h616_bank_pins[] = { 13, 0, 17, 0, 0, 7, 20, 11, 17 };
static const rt_uint8_t h616_irq_bank_map[] = { 0, 2, 3, 4, 5, 6, 7, 8 };

static const struct sunxi_pinctrl_function h616_functions[] = {
    { "uart0", 7, 0, 2, 2 },
    { "uart0", 5, 2, 1, 3 },
    { "uart0", 5, 4, 1, 3 },
    { "uart1", 6, 6, 4, 2 },
    { "uart2", 6, 15, 4, 2 },
    { "uart2", 7, 5, 4, 2 },
    { "uart2", 8, 5, 4, 3 },
    { "uart3", 8, 9, 4, 3 },
    { "uart4", 8, 13, 4, 3 },
    { "uart5", 7, 2, 2, 2 },
    { "i2c0", 8, 5, 2, 5 },
    { "i2c1", 7, 0, 2, 5 },
    { "i2c1", 8, 7, 2, 5 },
    { "i2c2", 7, 2, 2, 5 },
    { "i2c2", 8, 9, 2, 5 },
    { "i2c3", 6, 17, 2, 5 },
    { "i2c3", 7, 4, 2, 5 },
    { "i2c3", 0, 10, 2, 2 },
    { "i2c4", 6, 15, 2, 5 },
    { "i2c4", 7, 6, 2, 5 },
    { "mmc0", 5, 0, 6, 2 },
    { "mmc1", 6, 0, 6, 2 },
    { "mmc2", 2, 0, 2, 3 },
    { "mmc2", 2, 5, 2, 3 },
    { "mmc2", 2, 8, 4, 3 },
    { "mmc2", 2, 13, 4, 3 },
    { "spi0", 2, 0, 1, 4 },
    { "spi0", 2, 2, 3, 4 },
    { "spi0", 2, 7, 1, 4 },
    { "spi0", 2, 15, 2, 4 },
    { "spi1", 7, 5, 5, 4 },
    { "pwm1", 7, 3, 1, 4 },
    { "pwm2", 7, 2, 1, 4 },
    { "pwm3", 7, 0, 1, 4 },
    { "pwm4", 7, 1, 1, 4 },
    { "pwm0", 6, 19, 1, 4 },
    { "pwm5", 0, 12, 1, 2 },
    { "i2s3", 7, 5, 5, 3 },
    { "ir_rx", 7, 10, 1, 3 },
};

const struct sunxi_pinctrl_data sun50i_h616_pinctrl_data = {
    .layout = &h616_layout,
    .bank_pins = h616_bank_pins,
    .banks_nr = RT_ARRAY_SIZE(h616_bank_pins),
    .functions = h616_functions,
    .functions_nr = RT_ARRAY_SIZE(h616_functions),
    .irq_banks = RT_ARRAY_SIZE(h616_irq_bank_map),
    .irq_bank_map = h616_irq_bank_map,
    .irq_mux = 6,
    .irq_read_needs_mux = RT_TRUE,
};

static const rt_uint8_t h616_r_bank_pins[] = { 2 };
static const struct sunxi_pinctrl_function h616_r_functions[] = {
    { "s_rsb", 0, 0, 2, 2 },
    { "s_i2c", 0, 0, 2, 3 },
};

const struct sunxi_pinctrl_data sun50i_h616_r_pinctrl_data = {
    .layout = &h616_layout,
    .bank_pins = h616_r_bank_pins,
    .bank_base = 11,
    .banks_nr = RT_ARRAY_SIZE(h616_r_bank_pins),
    .functions = h616_r_functions,
    .functions_nr = RT_ARRAY_SIZE(h616_r_functions),
};
