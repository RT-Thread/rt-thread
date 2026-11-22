/*
 * Copyright (c) 2006-2026, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#include <rthw.h>
#include <rtthread.h>

#include "clint.h"

#define MCAUSE_INT  (1UL << 31)
#define IRQ_M_SOFT  3
#define IRQ_M_TIMER 7

extern int rt_hw_tick_isr(void);

void handle_trap(rt_ubase_t mcause, rt_ubase_t mepc, rt_ubase_t *sp)
{
    RT_UNUSED(mepc);
    RT_UNUSED(sp);

    if ((mcause & MCAUSE_INT) == 0)
    {
        return;
    }

    switch (mcause & 0x7fffffffUL)
    {
    case IRQ_M_SOFT:
        v861_clint_ipi_clear((unsigned int)rt_hw_cpu_id());
#ifdef RT_USING_SMP
        rt_schedule();
#endif
        break;
    case IRQ_M_TIMER:
        rt_hw_tick_isr();
        break;
    default:
        break;
    }
}
