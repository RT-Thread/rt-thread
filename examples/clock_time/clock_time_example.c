/*
 * Copyright (c) 2006-2024, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2024-12-04     RT-Thread    clock_time usage examples
 */

/**
 * @file clock_time_example.c
 * @brief Examples demonstrating the unified clock_time subsystem
 * 
 * This file contains various examples showing how to use the clock_time
 * subsystem for different time-related tasks.
 */

#include <rtthread.h>
#include <rtdevice.h>

#ifdef RT_USING_CLOCK_TIME

/**
 * @brief Example 1: Basic time information
 * 
 * Demonstrates how to get clock frequency, resolution, and current counter.
 */
static void clock_time_info_example(void)
{
    rt_kprintf("\n=== Clock Time Info Example ===\n");
    
    /* Get clock frequency */
    rt_uint64_t freq = rt_clock_time_getfreq();
    rt_kprintf("Clock frequency: %u Hz\n", (rt_uint32_t)freq);
    
    /* Get clock resolution (in nanoseconds * RT_CLOCK_TIME_RESMUL) */
    rt_uint64_t res = rt_clock_time_getres();
    rt_kprintf("Clock resolution: %u ns (scaled)\n", 
               (rt_uint32_t)(res / RT_CLOCK_TIME_RESMUL));
    
    /* Get current counter value */
    rt_uint64_t cnt = rt_clock_time_getcnt();
    rt_kprintf("Current counter: %u\n", (rt_uint32_t)cnt);
    
    /* Get device info */
    struct rt_clock_time_device *dev = rt_clock_time_get_default();
    if (dev)
    {
        rt_kprintf("Device name: %s\n", dev->parent.parent.name);
        rt_kprintf("Capabilities: ");
        if (dev->caps & RT_CLOCK_TIME_CAP_CLOCKSOURCE)
            rt_kprintf("CLOCKSOURCE ");
        if (dev->caps & RT_CLOCK_TIME_CAP_CLOCKEVENT)
            rt_kprintf("CLOCKEVENT ");
        rt_kprintf("\n");
    }
}
MSH_CMD_EXPORT(clock_time_info_example, Show clock time information);

/**
 * @brief Example 2: Boottime tracking
 * 
 * Demonstrates how to get system uptime in different formats.
 */
static void clock_boottime_example(void)
{
    struct timespec ts;
    struct timeval tv;
    time_t t;
    
    rt_kprintf("\n=== Boottime Example ===\n");
    
    /* Get boottime in nanoseconds */
    rt_clock_time_boottime_ns(&ts);
    rt_kprintf("Boottime (ns): %d.%09d seconds\n", 
               (rt_uint32_t)ts.tv_sec, (rt_uint32_t)ts.tv_nsec);
    
    /* Get boottime in microseconds */
    rt_clock_time_boottime_us(&tv);
    rt_kprintf("Boottime (us): %d.%06d seconds\n", 
               (rt_uint32_t)tv.tv_sec, (rt_uint32_t)tv.tv_usec);
    
    /* Get boottime in seconds */
    rt_clock_time_boottime_s(&t);
    rt_kprintf("Boottime (s):  %d seconds\n", (rt_uint32_t)t);
}
MSH_CMD_EXPORT(clock_boottime_example, Show system boottime);

/**
 * @brief Example 3: Time conversion
 * 
 * Demonstrates conversion between counter ticks and time units.
 */
static void clock_conversion_example(void)
{
    rt_kprintf("\n=== Time Conversion Example ===\n");
    
    /* Convert 1 second to counter ticks */
    unsigned long cnt_1s = (unsigned long)rt_clock_time_ms_to_cnt(1000);
    rt_kprintf("1 second = %u counter ticks\n", cnt_1s);
    
    /* Convert back to time units */
    rt_uint64_t ms = rt_clock_time_cnt_to_ms(cnt_1s);
    rt_uint64_t us = rt_clock_time_cnt_to_us(cnt_1s);
    rt_uint64_t ns = rt_clock_time_cnt_to_ns(cnt_1s);
    
    rt_kprintf("  = %u ms\n", (rt_uint32_t)ms);
    rt_kprintf("  = %u us\n", (rt_uint32_t)us);
    rt_kprintf("  = %u ns\n", (rt_uint32_t)ns);
}
MSH_CMD_EXPORT(clock_conversion_example, Show time conversion);

/**
 * @brief Example 4: High-precision delay
 * 
 * Demonstrates using high-precision delay functions.
 */
static void clock_delay_example(void)
{
    rt_kprintf("\n=== High-Precision Delay Example ===\n");
    
    /* Measure delay accuracy */
    unsigned long start_cnt = (unsigned long)rt_clock_time_getcnt();
    
    rt_kprintf("Delaying 100 microseconds...\n");
    rt_clock_udelay(100);
    
    unsigned long end_cnt = (unsigned long)rt_clock_time_getcnt();
    unsigned long delta_cnt = end_cnt - start_cnt;
    
    rt_uint64_t actual_us = rt_clock_time_cnt_to_us(delta_cnt);
    rt_kprintf("Actual delay: %u us (target: 100 us)\n", (rt_uint32_t)actual_us);
    
    /* Millisecond delay */
    start_cnt = (unsigned long)rt_clock_time_getcnt();
    rt_kprintf("Delaying 10 milliseconds...\n");
    rt_clock_mdelay(10);
    end_cnt = (unsigned long)rt_clock_time_getcnt();
    delta_cnt = end_cnt - start_cnt;
    
    rt_uint64_t actual_ms = rt_clock_time_cnt_to_ms(delta_cnt);
    rt_kprintf("Actual delay: %u ms (target: 10 ms)\n", (rt_uint32_t)actual_ms);
}
MSH_CMD_EXPORT(clock_delay_example, Demonstrate high-precision delays);

/**
 * @brief Example 5: High-resolution timer (one-shot)
 * 
 * Demonstrates using high-resolution timer for one-shot timeout.
 */
static void hrtimer_callback(void *parameter)
{
    rt_kprintf("High-resolution timer fired! Parameter: %s\n", 
               (char *)parameter);
}

static void clock_hrtimer_oneshot_example(void)
{
    struct rt_clock_hrtimer timer;
    
    rt_kprintf("\n=== High-Resolution Timer (One-Shot) Example ===\n");
    
    /* Initialize one-shot timer */
    rt_clock_hrtimer_init(&timer, "oneshot_timer", 
                         RT_TIMER_FLAG_ONE_SHOT,
                         hrtimer_callback, 
                         (void *)"One-shot timer");
    
    /* Start with 500ms delay */
    unsigned long delay_cnt = (unsigned long)rt_clock_time_ms_to_cnt(500);
    rt_kprintf("Starting timer for 500ms...\n");
    
    rt_err_t result = rt_clock_hrtimer_start(&timer, delay_cnt);
    if (result == RT_EOK)
    {
        rt_kprintf("Timer started successfully\n");
    }
    
    /* Let timer fire, then cleanup */
    rt_thread_mdelay(600);
    rt_clock_hrtimer_detach(&timer);
    
    rt_kprintf("Timer example complete\n");
}
MSH_CMD_EXPORT(clock_hrtimer_oneshot_example, Demonstrate one-shot hrtimer);

/**
 * @brief Example 6: High-resolution timer (periodic)
 * 
 * Demonstrates using high-resolution timer for periodic callbacks.
 */
static volatile int periodic_count = 0;

static void periodic_callback(void *parameter)
{
    periodic_count++;
    rt_kprintf("Periodic timer tick #%d\n", periodic_count);
}

static void clock_hrtimer_periodic_example(void)
{
    struct rt_clock_hrtimer timer;
    
    rt_kprintf("\n=== High-Resolution Timer (Periodic) Example ===\n");
    
    /* Initialize periodic timer */
    rt_clock_hrtimer_init(&timer, "periodic_timer", 
                         RT_TIMER_FLAG_PERIODIC,
                         periodic_callback, 
                         RT_NULL);
    
    /* Start with 200ms period */
    unsigned long period_cnt = (unsigned long)rt_clock_time_ms_to_cnt(200);
    rt_kprintf("Starting periodic timer (200ms period)...\n");
    
    periodic_count = 0;
    rt_err_t result = rt_clock_hrtimer_start(&timer, period_cnt);
    if (result == RT_EOK)
    {
        rt_kprintf("Timer started successfully\n");
    }
    
    /* Let it tick 5 times */
    rt_thread_mdelay(1100);
    
    /* Stop and cleanup */
    rt_clock_hrtimer_stop(&timer);
    rt_clock_hrtimer_detach(&timer);
    
    rt_kprintf("Timer stopped. Total ticks: %d\n", periodic_count);
}
MSH_CMD_EXPORT(clock_hrtimer_periodic_example, Demonstrate periodic hrtimer);

/**
 * @brief Example 7: Benchmark overhead
 * 
 * Measures the overhead of various clock_time operations.
 */
static void clock_benchmark_example(void)
{
    const int iterations = 1000;
    unsigned long start, end;
    int i;
    
    rt_kprintf("\n=== Clock Time Benchmark ===\n");
    
    /* Benchmark get_counter() */
    start = (unsigned long)rt_clock_time_getcnt();
    for (i = 0; i < iterations; i++)
    {
        volatile unsigned long cnt = (unsigned long)rt_clock_time_getcnt();
        (void)cnt;
    }
    end = (unsigned long)rt_clock_time_getcnt();
    rt_kprintf("get_counter() x%d: %u ns per call\n", 
               iterations,
               (rt_uint32_t)(rt_clock_time_cnt_to_ns(end - start) / iterations));
    
    /* Benchmark time conversion */
    start = (unsigned long)rt_clock_time_getcnt();
    for (i = 0; i < iterations; i++)
    {
        volatile rt_uint64_t us = rt_clock_time_cnt_to_us(1000);
        (void)us;
    }
    end = (unsigned long)rt_clock_time_getcnt();
    rt_kprintf("cnt_to_us() x%d: %u ns per call\n", 
               iterations,
               (rt_uint32_t)(rt_clock_time_cnt_to_ns(end - start) / iterations));
}
MSH_CMD_EXPORT(clock_benchmark_example, Benchmark clock_time operations);

/**
 * @brief Run all examples
 */
static void clock_time_examples_all(void)
{
    clock_time_info_example();
    rt_thread_mdelay(100);
    
    clock_boottime_example();
    rt_thread_mdelay(100);
    
    clock_conversion_example();
    rt_thread_mdelay(100);
    
    clock_delay_example();
    rt_thread_mdelay(100);
    
    clock_hrtimer_oneshot_example();
    rt_thread_mdelay(100);
    
    clock_hrtimer_periodic_example();
    rt_thread_mdelay(100);
    
    clock_benchmark_example();
}
MSH_CMD_EXPORT(clock_time_examples_all, Run all clock_time examples);

#else
#warning "RT_USING_CLOCK_TIME is not enabled. Examples will not be compiled."
#endif /* RT_USING_CLOCK_TIME */
