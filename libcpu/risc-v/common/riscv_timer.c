/*
 * Copyright (c) 2006-2025, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2018-10-28     Bernard      The unify RISC-V porting code.
 * 2024-07-08     Shell        Using CPUTIME as tick
 * 2025-04-20     GuEe-GUI     Port to the DM
 */

#include <rtthread.h>

#include <sbi.h>
#include <cpu.h>
#include <csr.h>
#ifdef RT_USING_KTIME
#include <ktime.h>
#endif
#include <cpuport.h>
#include <isa_ext.h>
#include <drivers/cputime.h>

static rt_uint32_t timebase_frequency;
static volatile rt_ubase_t tick_cycles;

static rt_bool_t riscv_sstc_available;

#ifdef ARCH_RISCV_M_MODE
static void *riscv_clint_timer_val, *riscv_clint_timer_cmp;
#endif

void riscv_timer_set_frequency(rt_uint32_t freq)
{
    HWREG32(&timebase_frequency) = freq;
    rt_hw_wmb();
}

rt_uint32_t riscv_timer_get_frequency(void)
{
    rt_hw_rmb();
    return HWREG32(&timebase_frequency);
}

rt_uint64_t riscv_timer_rdtime(void)
{
#ifdef ARCH_RISCV_M_MODE
#ifdef ARCH_CPU_64BIT
    return HWREG64(riscv_clint_timer_val);
#else
    rt_uint32_t hi, lo;

    do {
        hi = HWREG32(riscv_clint_timer_val);
        lo = HWREG32(riscv_clint_timer_val + sizeof(rt_uint32_t));
    } while (hi != HWREG32(riscv_clint_timer_val));

    return ((rt_uint64_t)hi << 32) | lo;
#endif /* ARCH_CPU_64BIT */
#else
    uint64_t cycles64;

    __asm__ volatile ("rdtime %0":"=r"(cycles64));

    return cycles64;
#endif /* ARCH_RISCV_M_MODE */
}

static void riscv_timer_next_event(void)
{
    rt_uint64_t stime_value = clock_cpu_gettime() + tick_cycles;

#ifdef ARCH_RISCV_M_MODE
    HWREG64(riscv_clint_timer_cmp + csr_read(CSR_MHARTID)) = stime_value;
#else
    if (riscv_sstc_available)
    {
    #ifdef ARCH_CPU_64BIT
        csr_write(CSR_STIMECMP, stime_value);
    #else
        csr_write(CSR_STIMECMP, stime_value & RT_UINT32_MAX);
        csr_write(CSR_STIMECMPH, stime_value >> 32);
    #endif
    }
    else
    {
        sbi_set_timer(stime_value);
    }
#endif
}

void riscv_timer_isr(void)
{
    rt_tick_increase();

    riscv_timer_next_event();
}

/* Sets and enable the timer interrupt */
void riscv_timer_init(void)
{
    rt_uint32_t freq = riscv_timer_get_frequency();

#ifdef RT_USING_SMP
    if (rt_hw_cpu_id() == riscv_hartid_to_cpu_id(boot_cpu_hartid))
#endif
    {
        if (!freq && !(freq = CPUTIME_TIMER_FREQ))
        {
            riscv_timer_set_frequency(freq);
        }
        RT_ASSERT(freq > 0);

        /* RISC-V cputime will call init in `rt_components_board_init` */

    #ifdef RT_USING_KTIME
        rt_ktime_cputimer_init();
    #endif

        /* Calculate the tick cycles */
        tick_cycles = freq / RT_TICK_PER_SECOND;

        /* Check if timer interrupt in S-mode is available via sstc extension */
        riscv_sstc_available = riscv_isa_ext_test(SSTC);
    }

    /* Clear the Supervisor-Timer bit in SIE */
    csr_clear(CSR_IE, BIT(IRQ_S_TIMER));

    /* Set timer */
    riscv_timer_next_event();

    /* Enable the Supervisor-Timer bit in SIE */
    csr_set(CSR_IE, BIT(IRQ_S_TIMER));
}

void riscv_timer_probe(void *clint_timer_cmp, void *clint_timer_val)
{
#ifdef ARCH_RISCV_M_MODE
    riscv_clint_timer_cmp = clint_timer_cmp;
    riscv_clint_timer_val = clint_timer_val;
#endif
}

void riscv_timer_us_delay(rt_uint32_t us)
{
    rt_ubase_t delay_time;

    delay_time = clock_cpu_gettime();
    delay_time += us * (riscv_timer_get_frequency() / 1000000);

    while (clock_cpu_gettime() < delay_time)
    {
        rt_hw_cpu_relax();
    }
}

#if !defined(RT_USING_DM) || !defined(RT_USING_HWTIMER)
/**
 * This function will delay for some us.
 *
 * @param us the delay time of us
 */
void rt_hw_us_delay(rt_uint32_t us)
{
    riscv_timer_us_delay(us);
}
#endif /* !RT_USING_DM || !RT_USING_HWTIMER */
