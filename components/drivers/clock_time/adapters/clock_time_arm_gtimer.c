/*
 * Copyright (c) 2006-2024, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2024-12-04     RT-Thread    ARM Generic Timer adapter for clock_time
 */

/**
 * @file clock_time_arm_gtimer.c
 * @brief ARM Generic Timer adapter for the unified clock_time subsystem
 * 
 * This file demonstrates how to adapt ARM Generic Timer (ARMv7-A/ARMv8)
 * to the clock_time framework. It can be used as a reference for BSP developers.
 * 
 * Features:
 * - Uses CNTPCT (physical counter) for clocksource
 * - Uses CNTP_TVAL/CVAL for clockevent (timer interrupts)
 * - Provides both clocksource and clockevent capabilities
 * 
 * Usage:
 * 1. Copy this file to your BSP driver directory
 * 2. Adjust register access macros for your platform
 * 3. Call rt_clock_time_arm_gtimer_init() during board initialization
 * 4. Implement timer ISR to call rt_clock_hrtimer_process()
 */

#include <rtthread.h>
#include <rtdevice.h>
#include <rthw.h>

#ifdef RT_USING_CLOCK_TIME

/* ARM Generic Timer system registers (AArch64) */
#if defined(ARCH_ARMV8)

static inline rt_uint64_t arm_gtimer_get_cntfrq(void)
{
    rt_uint64_t val;
    __asm__ volatile("mrs %0, cntfrq_el0" : "=r"(val));
    return val;
}

static inline rt_uint64_t arm_gtimer_get_cntpct(void)
{
    rt_uint64_t val;
    __asm__ volatile("mrs %0, cntpct_el0" : "=r"(val));
    return val;
}

static inline void arm_gtimer_set_cntp_tval(rt_uint32_t val)
{
    __asm__ volatile("msr cntp_tval_el0, %0" : : "r"(val));
}

static inline void arm_gtimer_set_cntp_ctl(rt_uint32_t val)
{
    __asm__ volatile("msr cntp_ctl_el0, %0" : : "r"(val));
}

#elif defined(ARCH_ARM_CORTEX_A)

/* ARMv7-A Generic Timer */
static inline rt_uint32_t arm_gtimer_get_cntfrq(void)
{
    rt_uint32_t val;
    __asm__ volatile("mrc p15, 0, %0, c14, c0, 0" : "=r"(val));
    return val;
}

static inline rt_uint64_t arm_gtimer_get_cntpct(void)
{
    rt_uint32_t low, high;
    __asm__ volatile("mrrc p15, 0, %0, %1, c14" : "=r"(low), "=r"(high));
    return ((rt_uint64_t)high << 32) | low;
}

static inline void arm_gtimer_set_cntp_tval(rt_uint32_t val)
{
    __asm__ volatile("mcr p15, 0, %0, c14, c2, 0" : : "r"(val));
}

static inline void arm_gtimer_set_cntp_ctl(rt_uint32_t val)
{
    __asm__ volatile("mcr p15, 0, %0, c14, c2, 1" : : "r"(val));
}

#else
#error "ARM Generic Timer adapter requires ARCH_ARMV8 or ARCH_ARM_CORTEX_A"
#endif

/* Control register bits */
#define CNTP_CTL_ENABLE     (1 << 0)
#define CNTP_CTL_IMASK      (1 << 1)
#define CNTP_CTL_ISTATUS    (1 << 2)

static rt_uint64_t _arm_gtimer_get_freq(void)
{
    return arm_gtimer_get_cntfrq();
}

static rt_uint64_t _arm_gtimer_get_counter(void)
{
    return arm_gtimer_get_cntpct();
}

static rt_err_t _arm_gtimer_set_timeout(rt_uint64_t delta)
{
    if (delta == 0)
    {
        /* Cancel timeout - disable timer */
        arm_gtimer_set_cntp_ctl(0);
        return RT_EOK;
    }
    
    /* Clamp to 32-bit for TVAL register */
    if (delta > 0xFFFFFFFF)
    {
        delta = 0xFFFFFFFF;
    }
    
    /* Set timer value and enable */
    arm_gtimer_set_cntp_tval((rt_uint32_t)delta);
    arm_gtimer_set_cntp_ctl(CNTP_CTL_ENABLE);
    
    return RT_EOK;
}

static const struct rt_clock_time_ops _arm_gtimer_ops =
{
    .get_freq = _arm_gtimer_get_freq,
    .get_counter = _arm_gtimer_get_counter,
    .set_timeout = _arm_gtimer_set_timeout,
};

static struct rt_clock_time_device _arm_gtimer_device;

/**
 * @brief Initialize ARM Generic Timer as clock_time device
 * 
 * This should be called during board initialization, typically in
 * rt_hw_timer_init() or similar BSP initialization function.
 * 
 * @return RT_EOK on success, error code otherwise
 */
int rt_clock_time_arm_gtimer_init(void)
{
    _arm_gtimer_device.ops = &_arm_gtimer_ops;
    
    /* Register with both clocksource and clockevent capabilities */
    rt_err_t result = rt_clock_time_device_register(&_arm_gtimer_device, 
                                                    "arm_gtimer",
                                                    RT_CLOCK_TIME_CAP_CLOCKSOURCE | 
                                                    RT_CLOCK_TIME_CAP_CLOCKEVENT);
    
    if (result == RT_EOK)
    {
        rt_kprintf("ARM Generic Timer: freq=%d Hz\n", (rt_uint32_t)_arm_gtimer_get_freq());
    }
    
    return result;
}
INIT_DEVICE_EXPORT(rt_clock_time_arm_gtimer_init);

/**
 * @brief ARM Generic Timer interrupt handler
 * 
 * This should be called from the timer IRQ handler in your BSP.
 * Typically registered in the interrupt controller during initialization.
 * 
 * Example:
 * void ARM_GTIMER_IRQHandler(void)
 * {
 *     rt_clock_time_arm_gtimer_isr();
 *     rt_interrupt_leave();
 * }
 */
void rt_clock_time_arm_gtimer_isr(void)
{
    /* Disable timer to clear interrupt */
    arm_gtimer_set_cntp_ctl(0);
    
    /* Process hrtimer timeouts */
    rt_clock_hrtimer_process();
}

#endif /* RT_USING_CLOCK_TIME */
