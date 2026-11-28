/*
 * Copyright (c) 2006-2026, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * E907: try the same CLINT window as C907 (hart 0). If the board
 * never ticks, next step is a cycle-based soft tick.
 */

#include <rthw.h>
#include <rtthread.h>

#include "clint.h"

#define MIE_MTIE (1U << 7)

static uint64_t tick_cycles;

static unsigned long csr_read_mie(void)
{
    unsigned long v;
    __asm__ volatile("csrr %0, mie" : "=r"(v));
    return v;
}

static void csr_write_mie(unsigned long v)
{
    __asm__ volatile("csrw mie, %0" ::"r"(v));
}

int rt_hw_tick_isr(void)
{
    v861_clint_set_mtimecmp(0, v861_clint_mtime() + tick_cycles);
    rt_tick_increase();
    return 0;
}

int rt_hw_tick_init(void)
{
    tick_cycles = (uint64_t)V861_CLINT_TIMEBASE_HZ / RT_TICK_PER_SECOND;
    if (tick_cycles == 0)
    {
        tick_cycles = 1;
    }

    csr_write_mie(csr_read_mie() & ~MIE_MTIE);
    v861_clint_set_mtimecmp(0, v861_clint_mtime() + tick_cycles);
    csr_write_mie(csr_read_mie() | MIE_MTIE);
    return 0;
}
