/*
 * Copyright (c) 2006-2026, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#ifndef DRV_FDT_H__
#define DRV_FDT_H__

#include <stdint.h>

struct v861_uart_fdt
{
    uint32_t reg;
    uint32_t baud;
    uint32_t clk_hz;
    uint32_t gate_reg;
    uint32_t gate_bit;
    uint32_t reset_reg;
    uint32_t reset_bit;
    uint32_t pin_port[2];
    uint32_t pin_num[2];
    uint32_t pin_func[2];
    uint32_t pin_count;
    char compatible[32];
    char stdout_path[64];
    int valid;
};

int rt_hw_fdt_load_uart(struct v861_uart_fdt *out);
void rt_hw_fdt_print_uart(const struct v861_uart_fdt *cfg);

#endif
