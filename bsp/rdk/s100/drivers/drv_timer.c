/*
 * Copyright (c) 2006-2026, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2026-04-20     rcitach      first version
 */

#include <rthw.h>
#include <rtthread.h>
#include <stdint.h>

#include "board.h"

#define S100_SYSCNT_BASE                 0x23110000U
#define S100_SYSCNT_CTRL_OSCON_MASK      (0x1U)
#define S100_SYSCNT_CLK_HZ               (40000000U)
#define S100_GENERIC_TIMER_PPI           30

#define CNTP_CTL_ENABLE                  (1U << 0)

struct s100_syscnt
{
    volatile rt_uint32_t ctrl;
    volatile rt_uint32_t stat;
    volatile rt_uint32_t cntcvl;
    volatile rt_uint32_t cntcvu;
    rt_uint8_t reserved[16];
    volatile rt_uint32_t cntfid0;
};

static volatile struct s100_syscnt *const s100_syscnt =
    (volatile struct s100_syscnt *)S100_SYSCNT_BASE;

static rt_uint32_t s100_tick_interval;
static rt_uint64_t s100_read_cntpct(void)
{
    rt_uint32_t low;
    rt_uint32_t high;

    __asm volatile ("mrrc p15, 0, %0, %1, c14" : "=r"(low), "=r"(high));

    return (((rt_uint64_t)high) << 32) | low;
}

static void s100_write_cntp_cval(rt_uint64_t value)
{
    rt_uint32_t low = (rt_uint32_t)value;
    rt_uint32_t high = (rt_uint32_t)(value >> 32);

    __asm volatile ("mcrr p15, 2, %0, %1, c14" :: "r"(low), "r"(high));
}

static void s100_write_cntp_ctl(rt_uint32_t value)
{
    __asm volatile ("mcr p15, 0, %0, c14, c2, 1" :: "r"(value));
}

static void s100_program_next_tick(rt_uint32_t delta)
{
    s100_write_cntp_cval(s100_read_cntpct() + delta);
}

static void rt_hw_timer_isr(int vector, void *param)
{
    RT_UNUSED(vector);
    RT_UNUSED(param);

    s100_program_next_tick(s100_tick_interval);
    rt_tick_increase();
}

int rt_hw_timer_init(void)
{
    s100_tick_interval = S100_SYSCNT_CLK_HZ / RT_TICK_PER_SECOND;
    RT_ASSERT(s100_tick_interval > 0U);

    s100_syscnt->cntfid0 = S100_SYSCNT_CLK_HZ;
    s100_syscnt->ctrl |= S100_SYSCNT_CTRL_OSCON_MASK;

    s100_write_cntp_ctl(0U);
    s100_program_next_tick(s100_tick_interval);
    s100_write_cntp_ctl(CNTP_CTL_ENABLE);

    rt_hw_interrupt_install(S100_GENERIC_TIMER_PPI, rt_hw_timer_isr, RT_NULL, "tick");
    rt_hw_interrupt_umask(S100_GENERIC_TIMER_PPI);

    return 0;
}
INIT_BOARD_EXPORT(rt_hw_timer_init);

