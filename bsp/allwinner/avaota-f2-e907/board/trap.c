/*
 * Copyright (c) 2006-2026, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#include <rthw.h>
#include <rtthread.h>

#include "clint.h"
#include "plic.h"

#define MCAUSE_INT  (1UL << 31)
#define IRQ_M_TIMER 7
#define IRQ_M_EXT   11

extern int rt_hw_tick_isr(void);

void handle_trap(rt_ubase_t mcause, rt_ubase_t mepc, rt_ubase_t *sp)
{
    RT_UNUSED(sp);

    if ((mcause & MCAUSE_INT) == 0)
    {
        rt_kprintf("sync trap mcause=0x%lx mepc=0x%lx\n",
                   (unsigned long)mcause, (unsigned long)mepc);
        while (1)
        {
            __asm__ volatile("ebreak");
        }
    }

    if ((mcause & 0x7fffffffUL) == IRQ_M_EXT)
    {
        v861_plic_handle_irq();
        return;
    }

    if ((mcause & 0x7fffffffUL) == IRQ_M_TIMER)
    {
        rt_hw_tick_isr();
    }
}
