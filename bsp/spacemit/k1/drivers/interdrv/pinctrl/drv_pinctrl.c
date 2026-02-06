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
#include "drv_pinctrl.h"

#ifndef RT_USING_SMART
#define rt_ioremap(addr, size) ((void *)(addr))
#endif

#define PIN_CONFIG_REG_WIDTH    4 // 32-bit register

/*
 * Bit fields.
 */
#define PIN_FUNC_SEL_MASK       (0x7) // MUX_MODE is 3 bits
#define PIN_FUNC_SEL_OFFSET     (0)   // Assuming MUX_MODE is at bits [2:0] based on manual analysis

#define PIN_PULL_MASK           (0x7 << 13) // PULL state is at bits [15:13]

static volatile void *pinctrl_base;

void k1_pinctrl_init(void) {
    if (!pinctrl_base) {
        pinctrl_base = rt_ioremap((void*)IOMUX_BASE_ADDR, IOMUX_IO_SIZE);
    }
}

/*
 * Sets the function mode for a specific pin.
 */
void k1_pinctrl_set_function(rt_uint32_t pin_id, rt_uint32_t func_mode)
{
    if (!pinctrl_base)
    {
        rt_kprintf("Pinctrl driver not initialized!\n");
        return;
    }

    /* PINID(x) = x + 1, so the actual index is pin_id - 1 */
    rt_ubase_t reg_offset = (pin_id - 1) * PIN_CONFIG_REG_WIDTH;
    volatile void *reg_addr = (void *)((rt_ubase_t)pinctrl_base + reg_offset);

    rt_uint32_t val = readl(reg_addr);

    /*
     * TODO-K1: 
     * The exact bit field for function selection needs to be confirmed.
     * The Linux DTS uses K1X_PADCONF(pin, mode, cfg), suggesting mode and config
     * might be combined. A common hardware design is to have a MUX field.
     * We assume MUX_MODE is at bits [2:0] for now.
     */
    val &= ~PIN_FUNC_SEL_MASK;
    val |= (func_mode << PIN_FUNC_SEL_OFFSET);

    writel(val, reg_addr);
}

/*
 * Sets the pull-up/pull-down state for a specific pin.
 */
void k1_pinctrl_set_pull(rt_uint32_t pin_id, rt_uint32_t pull_state)
{
    if (!pinctrl_base)
    {
        rt_kprintf("Pinctrl driver not initialized!\n");
        return;
    }

    rt_ubase_t reg_offset = (pin_id - 1) * PIN_CONFIG_REG_WIDTH;
    volatile void *reg_addr = (void *)((rt_ubase_t)pinctrl_base + reg_offset);

    rt_uint32_t val = readl(reg_addr);

    /* Clear the pull state bits and set the new state */
    val &= ~PIN_PULL_MASK;
    val |= pull_state; // The pull macros already include the shift

    writel(val, reg_addr);
}