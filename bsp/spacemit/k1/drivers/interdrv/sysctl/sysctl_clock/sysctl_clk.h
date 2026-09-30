/*
 * Copyright (c) 2006-2025, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author            Notes
 * 2025-10-15     IronsideZhang     first version
 */

#ifndef __SYSCTL_CLK_H__
#define __SYSCTL_CLK_H__
#include <rtdef.h>

/*
 * Clock node definitions are adapted from Linux DTS binding header:
 * dt-bindings/clock/spacemit-k1x-clock.h
 */
typedef enum {
    CLK_UART1, // In DTS, uart0 uses the clock named CLK_UART1
    // Add other clock nodes here in later stages...
} k1_clk_node_e;

void k1_sysctl_clk_init(void);
void k1_sysctl_clk_set_leaf_en(k1_clk_node_e node, int enable);
rt_uint32_t k1_sysctl_clk_get_leaf_freq(k1_clk_node_e node);
#endif