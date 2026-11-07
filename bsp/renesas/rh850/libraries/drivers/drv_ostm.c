/*
 * Copyright (c) 2026, Linumiz
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2026-11-06     Parthiban    first version
 */

#include <rthw.h>
#include <rtthread.h>
#include "drv_intc.h"
#include "drv_ostm.h"

#define OSTM_CMP 0x00
#define OSTM_TE  0x10
#define OSTM_TS  0x14
#define OSTM_TT  0x18
#define OSTM_CTL 0x20

#define OSTM_CTL_IE (1 << 7)

static void ostm_stop(rt_ubase_t base)
{
    HWREG8(base + OSTM_TT) = 1;
    while ((HWREG8(base + OSTM_TE) & 1U) != 0U)
    {
    }
}

/* CTL can only be written while the counter is stopped */
void rh850_ostm_start_interval(rt_ubase_t base, rt_uint32_t cmp)
{
    ostm_stop(base);
    HWREG8(base + OSTM_CTL) = OSTM_CTL_IE;
    HWREG32(base + OSTM_CMP) = cmp;
    HWREG8(base + OSTM_TS) = 1;
}

static void rh850_tick_isr(int vector, void *param)
{
    RT_UNUSED(vector);
    RT_UNUSED(param);

    rt_tick_increase();
}

int rh850_tick_init(rt_ubase_t base, int vector, rt_uint32_t clk_hz)
{
    rt_hw_interrupt_install(vector, rh850_tick_isr, RT_NULL, "tick");
    rh850_intc_set_priority(vector, RH850_INTC_PRIO_LOWEST);
    rh850_ostm_start_interval(base, clk_hz / RT_TICK_PER_SECOND - 1U);
    rt_hw_interrupt_umask(vector);

    return RT_EOK;
}
