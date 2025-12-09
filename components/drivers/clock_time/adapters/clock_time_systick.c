/*
 * Copyright (c) 2006-2024, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2024-12-04     RT-Thread    SysTick adapter for clock_time (Cortex-M example)
 */

/**
 * @file clock_time_systick.c
 * @brief ARM Cortex-M SysTick adapter for the unified clock_time subsystem
 * 
 * This file demonstrates how to adapt SysTick timer to the clock_time framework.
 * SysTick is commonly used on ARM Cortex-M processors.
 * 
 * Features:
 * - Uses DWT CYCCNT for high-resolution counter (clocksource)
 * - Falls back to tick counter if DWT is not available
 * - SysTick itself provides system tick, not high-res timeout
 * 
 * Note: This example provides only clocksource capability. For clockevent
 * capability, you would need to use a different hardware timer.
 * 
 * Usage:
 * 1. Enable DWT cycle counter in your board initialization
 * 2. This adapter will automatically register during initialization
 */

#include <rtthread.h>
#include <rtdevice.h>

#if defined(RT_USING_CLOCK_TIME) && defined(ARCH_ARM_CORTEX_M)

/* DWT (Data Watchpoint and Trace) registers */
#define DWT_BASE            0xE0001000UL
#define DWT_CYCCNT          (*(volatile rt_uint32_t *)(DWT_BASE + 0x004))
#define DWT_CTRL            (*(volatile rt_uint32_t *)(DWT_BASE + 0x000))
#define DWT_CTRL_CYCCNTENA  (1 << 0)

/* DEM (Debug Exception and Monitor) registers */
#define DEM_BASE            0xE000EDFC
#define DEM_CR              (*(volatile rt_uint32_t *)(DEM_BASE + 0x000))
#define DEM_CR_TRCENA       (1 << 24)

static rt_bool_t _dwt_available = RT_FALSE;
static rt_uint32_t _cpu_freq_hz = 0;

/**
 * @brief Enable DWT cycle counter
 * 
 * @return RT_TRUE if DWT is available and enabled, RT_FALSE otherwise
 */
static rt_bool_t _dwt_enable(void)
{
    /* Enable DWT */
    DEM_CR |= DEM_CR_TRCENA;
    
    /* Reset counter */
    DWT_CYCCNT = 0;
    
    /* Enable counter */
    DWT_CTRL |= DWT_CTRL_CYCCNTENA;
    
    /* Verify counter is counting */
    rt_uint32_t start = DWT_CYCCNT;
    for (volatile int i = 0; i < 100; i++);
    rt_uint32_t end = DWT_CYCCNT;
    
    return (end > start);
}

static rt_uint64_t _systick_get_freq(void)
{
    if (_dwt_available)
    {
        /* Return CPU frequency (DWT CYCCNT increments at CPU clock rate) */
        return _cpu_freq_hz ? _cpu_freq_hz : SystemCoreClock;
    }
    else
    {
        /* Fall back to tick frequency */
        return RT_TICK_PER_SECOND;
    }
}

static rt_uint64_t _systick_get_counter(void)
{
    if (_dwt_available)
    {
        /* Return DWT cycle counter */
        return DWT_CYCCNT;
    }
    else
    {
        /* Fall back to tick counter */
        return rt_tick_get();
    }
}

static const struct rt_clock_time_ops _systick_ops =
{
    .get_freq = _systick_get_freq,
    .get_counter = _systick_get_counter,
    .set_timeout = RT_NULL,  /* SysTick doesn't support programmable timeout */
};

static struct rt_clock_time_device _systick_device;

/**
 * @brief Initialize SysTick/DWT as clock_time device
 * 
 * @return RT_EOK on success, error code otherwise
 */
int rt_clock_time_systick_init(void)
{
    /* Try to enable DWT cycle counter */
    _dwt_available = _dwt_enable();
    
    _systick_device.ops = &_systick_ops;
    
    /* Register with clocksource capability only */
    rt_err_t result = rt_clock_time_device_register(&_systick_device, 
                                                    "systick",
                                                    RT_CLOCK_TIME_CAP_CLOCKSOURCE);
    
    if (result == RT_EOK)
    {
        if (_dwt_available)
        {
            rt_kprintf("SysTick/DWT: freq=%d Hz (DWT cycle counter enabled)\n", 
                      (rt_uint32_t)_systick_get_freq());
        }
        else
        {
            rt_kprintf("SysTick: freq=%d Hz (DWT not available, using tick counter)\n", 
                      RT_TICK_PER_SECOND);
        }
    }
    
    return result;
}
INIT_DEVICE_EXPORT(rt_clock_time_systick_init);

/**
 * @brief Set CPU frequency for DWT counter
 * 
 * This should be called if SystemCoreClock is not accurate or not available.
 * 
 * @param freq_hz CPU frequency in Hz
 */
void rt_clock_time_systick_set_freq(rt_uint32_t freq_hz)
{
    _cpu_freq_hz = freq_hz;
}

#endif /* RT_USING_CLOCK_TIME && ARCH_ARM_CORTEX_M */
