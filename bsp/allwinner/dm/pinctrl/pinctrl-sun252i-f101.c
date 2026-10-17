/*
 * Copyright (c) 2006-2026, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#include <rtthread.h>
#include <rtdevice.h>

#include <sunxi_pinctrl.h>

/* F101 uses the D1-style PIO layout with 4-bit-stride drive fields. */
static const struct sunxi_pinctrl_layout sun252i_f101_pio_layout =
{
    .bank_stride = 0x30,
    .mux_reg = 0x00,
    .data_reg = 0x10,
    .drive_reg = 0x14,
    .pull_reg = 0x24,
    .mux_bits = 4,
    .drive_bits = 4,
    .pull_bits = 2,
    .disabled_mux = 0xf,
};

/* Hardware bank address space remains 32 pins wide even when a bank is sparse. */
static const rt_uint8_t sun252i_f101_bank_pins[] =
{
    4, 4, 6, 23, 15, 7,
};

static const struct sunxi_pinctrl_function sun252i_f101_functions[] =
{
    { "uart0", 4, 0, 2, 6 },
    { "uart1", 1, 0, 4, 4 },
    { "tpadc", 0, 0, 4, 2 },
    { "irrx", 3, 7, 1, 3 },
    { "pwm0_0", 4, 2, 1, 10 },
    { "pwm0_1", 4, 3, 1, 10 },
    { "pwm0_2", 4, 4, 1, 10 },
    { "pwm0_3", 4, 5, 1, 10 },
    { "twi2", 1, 2, 2, 3 },
    { "spi0", 2, 0, 6, 3 },
    { "spi1", 3, 0, 7, 3 },
    { "sdc0", 5, 0, 6, 2 },
    { "sdc2", 2, 0, 6, 2 },
    { "lcd0", 3, 0, 22, 2 },
    { "lcd0", 4, 6, 2, 4 },
    { "lvds0", 3, 12, 10, 3 },
    { "dsi0", 3, 12, 10, 4 },
    { "i2s0", 4, 0, 5, 5 },
    { "owa", 4, 6, 1, 6 },
};

const struct sunxi_pinctrl_data sun252i_f101_pinctrl_data =
{
    .layout = &sun252i_f101_pio_layout,
    .bank_pins = sun252i_f101_bank_pins,
    .functions = sun252i_f101_functions,
    .functions_nr = RT_ARRAY_SIZE(sun252i_f101_functions),
    .banks_nr = RT_ARRAY_SIZE(sun252i_f101_bank_pins),
    .irq_banks = RT_ARRAY_SIZE(sun252i_f101_bank_pins),
    .irq_mux = 0xe,
};
