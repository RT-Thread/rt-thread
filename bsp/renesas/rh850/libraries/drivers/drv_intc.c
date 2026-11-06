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
#include "rh850_cpu.h"
#include "drv_intc.h"
#include "soc.h"

/* 8-bit writes to the low byte of EICn keep EIRF */
#define EIC_STRIDE   2
#define EIC_EIP_MASK 0x0f
#define EIC_EITB     (1 << 6)
#define EIC_EIMK     (1 << 7)
#define EIC_EIRF_HI  (1 << 4)

#define EIIC_EIINT 0x1000

struct rh850_isr
{
    rt_isr_handler_t handler;
    void *param;
};

static struct rh850_isr isr_table[SOC_INTC_CHANNELS];

static rt_ubase_t eic_addr(int vector)
{
    rt_ubase_t base =
        (vector < SOC_INTC1_CHANNELS) ? SOC_INTC1_BASE : SOC_INTC2_BASE;

    return base + (rt_ubase_t)vector * EIC_STRIDE;
}

static void eic_update(int vector, rt_uint8_t clear, rt_uint8_t set)
{
    rt_ubase_t addr = eic_addr(vector);
    rt_base_t level = rt_hw_interrupt_disable();
    rt_uint8_t v = HWREG8(addr);

    /* bit 4 is reserved and written as 0 */
    v &= (rt_uint8_t) ~(clear | 0x10U);
    v |= set;
    HWREG8(addr) = v;
    (void)HWREG8(addr);
    rh850_syncp();
    rt_hw_interrupt_enable(level);
}

void rt_hw_interrupt_init(void)
{
}

void rt_hw_interrupt_mask(int vector)
{
    if (vector >= 0 && vector < SOC_INTC_CHANNELS)
    {
        eic_update(vector, 0, EIC_EIMK);
    }
}

void rt_hw_interrupt_umask(int vector)
{
    if (vector >= 0 && vector < SOC_INTC_CHANNELS)
    {
        eic_update(vector, EIC_EIMK, 0);
    }
}

rt_isr_handler_t rt_hw_interrupt_install(int vector, rt_isr_handler_t handler,
                                         void *param, const char *name)
{
    rt_isr_handler_t old = RT_NULL;
    rt_base_t level;

    RT_UNUSED(name);

    if (vector >= 0 && vector < SOC_INTC_CHANNELS)
    {
        level = rt_hw_interrupt_disable();
        old = isr_table[vector].handler;
        isr_table[vector].handler = handler;
        isr_table[vector].param = param;
        rt_hw_interrupt_enable(level);
    }

    return old;
}

void rh850_intc_set_priority(int vector, rt_uint32_t prio)
{
    if (vector >= 0 && vector < SOC_INTC_CHANNELS)
    {
        eic_update(vector, EIC_EIP_MASK | EIC_EITB,
                   (rt_uint8_t)(prio & EIC_EIP_MASK));
    }
}

void rh850_intc_raise(int vector)
{
    rt_ubase_t addr;

    if (vector >= 0 && vector < SOC_INTC_CHANNELS)
    {
        addr = eic_addr(vector) + 1;
        HWREG8(addr) = EIC_EIRF_HI;
        (void)HWREG8(addr);
        rh850_syncp();
    }
}

rt_bool_t rh850_intc_pending(int vector)
{
    return (HWREG8(eic_addr(vector) + 1) & EIC_EIRF_HI) ? RT_TRUE : RT_FALSE;
}

void rh850_intc_clear(int vector)
{
    rt_ubase_t addr = eic_addr(vector) + 1;

    HWREG8(addr) = 0;
    (void)HWREG8(addr);
    rh850_syncp();
}

void rt_hw_interrupt_dispatch(rt_uint32_t eiic)
{
    int vector = (int)(eiic & 0xffffU) - EIIC_EIINT;

    if (vector >= 0 && vector < SOC_INTC_CHANNELS &&
        isr_table[vector].handler != RT_NULL)
    {
        isr_table[vector].handler(vector, isr_table[vector].param);
    }
    else
    {
        rt_kprintf("unhandled interrupt, EIIC 0x%08x\n", eiic);
        rt_hw_interrupt_mask(vector);
    }
}
