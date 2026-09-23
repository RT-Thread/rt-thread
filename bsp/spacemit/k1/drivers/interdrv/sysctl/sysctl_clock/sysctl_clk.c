/*
 * Copyright (c) 2006-2025, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author            Notes
 * 2025-10-15     IronsideZhang     first version
 */

#include <rtthread.h>
#include <riscv_io.h>
#include "board.h"
#include "sysctl_clk.h"

#ifndef RT_USING_SMART
#define rt_ioremap(addr, size) (addr)
#endif

/*
 * Offset for UART0 is 0x0 within the APBC block.
 */
#define APBC_UART0_CLK_RST_OFFSET   (0x0)
#define APBCLK_EN_BIT               (1 << 0)
#define FNCLK_EN_BIT                (1 << 1)
#define FNCLK_SEL_MASK              (0x7 << 4)
#define FNCLK_SEL_OFFSET            (4)

static volatile void *apbc_base;

void k1_sysctl_clk_init(void) {
    if (!apbc_base) {
        apbc_base = (void *)rt_ioremap((void*)APBC_BASE_ADDR, APBC_IO_SIZE);
    }
}

void k1_sysctl_clk_set_leaf_en(k1_clk_node_e node, int enable) {
    if (!apbc_base) return;

    if (node == CLK_UART1) {
        rt_uint32_t val = readl(apbc_base + APBC_UART0_CLK_RST_OFFSET);
        if (enable) {
            val |= (APBCLK_EN_BIT | FNCLK_EN_BIT);
        } else {
            val &= ~(APBCLK_EN_BIT | FNCLK_EN_BIT);
        }
        writel(val, apbc_base + APBC_UART0_CLK_RST_OFFSET);
    }
}

rt_uint32_t k1_sysctl_clk_get_leaf_freq(k1_clk_node_e node) {
    if (!apbc_base) return 0;

    if (node == CLK_UART1) {
        rt_uint32_t val = readl(apbc_base + APBC_UART0_CLK_RST_OFFSET);
        rt_uint32_t sel = (val & FNCLK_SEL_MASK) >> FNCLK_SEL_OFFSET;

        switch (sel) {
            case 0: return 57600000;   // 57.6 MHz
            case 1: return 14745600;   // 14.7456 MHz
            case 2: return 48000000;   // 48 MHz
            case 3: return 24000000;   // UART_LP, assume 24MHz OSC clock as a safe default
            default: return 57600000;  // Default to 57.6 MHz
        }
    }
    return 0;
}