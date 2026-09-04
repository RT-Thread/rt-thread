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
#include <cpuport.h>
#include <isa_ext.h>
#ifdef RT_USING_CLOCK_TIME
#include <drivers/clock_time.h>
#endif

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

rt_weak rt_uint64_t rt_hw_get_clock_timer_freq(void)
{
    rt_uint32_t freq = riscv_timer_get_frequency();

#ifdef CLOCK_TIMER_FREQ
    if (!freq)
    {
        freq = CLOCK_TIMER_FREQ;
    }
#endif

    return freq;
}

rt_weak rt_uint64_t riscv_timer_rdtime(void)
{
#ifdef ARCH_RISCV_M_MODE
    RT_ASSERT(riscv_clint_timer_val != RT_NULL);
    if (!riscv_clint_timer_val)
    {
        return 0;
    }

#if __riscv_xlen == 64
    return HWREG64(riscv_clint_timer_val);
#else
    volatile rt_uint32_t *mtime = riscv_clint_timer_val;
    rt_uint32_t hi, lo;

    do
    {
        hi = HWREG32(mtime + 1);
        lo = HWREG32(mtime);
    } while (hi != HWREG32(mtime + 1));

    return ((rt_uint64_t)hi << 32) | lo;
#endif /* __riscv_xlen == 64 */
#else
#if __riscv_xlen == 64
    uint64_t cycles64;

    __asm__ volatile ("rdtime %0":"=r"(cycles64));

    return cycles64;
#else
    rt_uint32_t hi, lo, hi_check;

    do
    {
        __asm__ volatile ("rdtimeh %0" : "=r"(hi));
        __asm__ volatile ("rdtime %0" : "=r"(lo));
        __asm__ volatile ("rdtimeh %0" : "=r"(hi_check));
    } while (hi != hi_check);

    return ((rt_uint64_t)hi << 32) | lo;
#endif /* __riscv_xlen == 64 */
#endif /* ARCH_RISCV_M_MODE */
}

rt_weak void riscv_timer_set_compare(rt_uint64_t value)
{
#ifdef ARCH_RISCV_M_MODE
    rt_ubase_t hartid = csr_read(CSR_MHARTID);
    volatile rt_uint32_t *mtimecmp;

    RT_ASSERT(riscv_clint_timer_cmp != RT_NULL);
    if (!riscv_clint_timer_cmp)
    {
        return;
    }

    mtimecmp = (void *)((rt_ubase_t)riscv_clint_timer_cmp +
            hartid * sizeof(rt_uint64_t));

#if __riscv_xlen == 64
    HWREG64(mtimecmp) = value;
#else
    HWREG32(mtimecmp + 1) = RT_UINT32_MAX;
    HWREG32(mtimecmp) = value & RT_UINT32_MAX;
    HWREG32(mtimecmp + 1) = value >> 32;
#endif
#else
    if (riscv_sstc_available)
    {
#if __riscv_xlen == 64
        csr_write(CSR_STIMECMP, value);
#else
        csr_write(CSR_STIMECMPH, RT_UINT32_MAX);
        csr_write(CSR_STIMECMP, value & RT_UINT32_MAX);
        csr_write(CSR_STIMECMPH, value >> 32);
#endif
    }
    else
    {
        sbi_set_timer(value);
    }
#endif /* !ARCH_RISCV_M_MODE */
}

static void riscv_timer_next_event(void)
{
    riscv_timer_set_compare(riscv_timer_rdtime() + tick_cycles);
}

void riscv_timer_isr(void)
{
    rt_tick_increase();

    riscv_timer_next_event();
}

int tick_isr(void)
{
    riscv_timer_isr();

    return 0;
}

/* Sets and enable the timer interrupt */
void riscv_timer_init(void)
{
    rt_uint32_t freq = riscv_timer_get_frequency();

#ifdef RT_USING_SMP
    if (rt_hw_cpu_id() == riscv_hartid_to_cpu_id(boot_cpu_hartid))
#endif
    {
        if (!freq && (freq = (rt_uint32_t)rt_hw_get_clock_timer_freq()))
        {
            riscv_timer_set_frequency(freq);
        }

        RT_ASSERT(freq >= RT_TICK_PER_SECOND);
        if (freq < RT_TICK_PER_SECOND)
        {
            return;
        }

    #ifdef RT_USING_CLOCK_TIME
        rt_clock_time_source_init();
    #endif

        /* Calculate the tick cycles */
        tick_cycles = freq / RT_TICK_PER_SECOND;

    #ifndef ARCH_RISCV_M_MODE
        /* Check if timer interrupt in S-mode is available via sstc extension. */
        riscv_sstc_available = riscv_isa_ext_test(SSTC);
    #endif

        rt_hw_wmb();
    }

#ifdef RT_USING_SMP
    rt_hw_rmb();
#endif

    RT_ASSERT(tick_cycles > 0);
    if (!tick_cycles)
    {
        return;
    }

    /* Keep the timer masked while programming its first event. */
    csr_clear(CSR_IE, BIT(RV_IRQ_TIMER));

    /* Set timer */
    riscv_timer_next_event();

    csr_set(CSR_IE, BIT(RV_IRQ_TIMER));
}

rt_weak int rt_hw_tick_init(void)
{
    riscv_timer_init();

    return 0;
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
    rt_uint64_t delay_time;

    delay_time = riscv_timer_rdtime();
    delay_time += (rt_uint64_t)us * (riscv_timer_get_frequency() / 1000000);

    while (riscv_timer_rdtime() < delay_time)
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
