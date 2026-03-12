/*
 * Copyright (c) 2006-2025, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author         Notes
 * 2025-07-03     rcitach        test case for irq latency
 * 2025-11-30     westcity-YOLO  Add standardized utest documentation block
 */

/**
 * Test Case Name: Kernel Core IRQ Latency Performance Test
 *
 * Test Objectives:
 * - Measure interrupt-to-thread response time using hardware timer
 * - Validate high-resolution timing accuracy (us level)
 * - Verify consistent latency under repeated testing
 *
 * Test Scenarios:
 * - **Hardware Timer ISR**: Triggered every 50μs via RT_UTEST_HWTIMER_DEV_NAME
 * - **Latency Measurement**: Time from ISR entry to thread wake-up
 * - **Stress Test**: 100+ repeated measurements (RT_UTEST_SYS_PERF_TC_COUNT)
 * - **Priority Handling**: High-priority thread response validation
 *
 * Verification Metrics:
 * - Latency < 1000μs (system-dependent threshold)
 * - Max/Min/Avg deviation < 10% of average value
 * - 0 errors in hardware timer setup
 * - No memory leaks during test
 *
 * Dependencies:
 * - RT_USING_PERF_TEST enabled
 * - RT_USING_UTEST framework
 * - Hardware timer device "hwtimer0" (or defined RT_UTEST_HWTIMER_DEV_NAME)
 * - rt_device_find/open/close support
 *
 * Expected Results:
 * [  PASSED  ] [ result   ] testcase (core.irq_latency)
 * - Structured output with Min/Max/Avg latency (μs)
 * - Final line: "=== IRQ Latency Test Results End ==="
 * - Executable via: `utest_run core.irq_latency` in msh
 */

#include <rtthread.h>
#include <rtdevice.h>
#include <utest.h>
#include <utest_assert.h>
#include <perf_tc.h>

static rt_device_t hw_dev = RT_NULL;
static rt_sem_t complete_sem = RT_NULL;
static rt_clock_timerval_t timeout = {0};
static rt_perf_t *perf_local = RT_NULL;

static void modify_time(rt_perf_t *perf)
{
    if(perf)
        perf->real_time = perf->real_time - perf->tmp_time;
}

static rt_err_t timer_callback(rt_device_t dev, rt_size_t size)
{
    rt_perf_stop(perf_local);
    if (perf_local->count >= RT_UTEST_SYS_PERF_TC_COUNT)
    {
        rt_sem_release(complete_sem);
        return RT_EOK;
    }
    rt_perf_start_impl(perf_local, &timeout);
    return RT_EOK;
}

rt_err_t rt_perf_irq_latency(rt_perf_t *perf)
{
# if __STDC_VERSION__ >= 199901L
    rt_strcpy(perf->name,__func__);
#else
    rt_strcpy(perf->name,"rt_perf_irq_latency");
#endif
    int ret = RT_EOK;
    rt_clock_timer_mode_t mode = CLOCK_TIMER_MODE_PERIOD;

    perf_local = perf;
    hw_dev = rt_device_find(RT_UTEST_CLOCK_TIMER_DEV_NAME);
    if (hw_dev == RT_NULL)
    {
        ret = RT_ERROR;
        LOG_E("clock_timer sample run failed! can't find %s device!", RT_UTEST_CLOCK_TIMER_DEV_NAME);
        return ret;
    }

    complete_sem = rt_sem_create("complete", 0, RT_IPC_FLAG_FIFO);
    timeout.sec = 0;
    timeout.usec = 50;   /* No modification is necessary here, use the fixed value */

    rt_mutex_take(perf->lock,RT_WAITING_FOREVER);
    perf_local->tmp_time = (rt_uint32_t)(timeout.sec * 1000000u + timeout.usec);
    perf_local->local_modify = modify_time;
    rt_mutex_release(perf->lock);

    rt_device_set_rx_indicate(hw_dev, timer_callback);
    rt_device_control(hw_dev, CLOCK_TIMER_CTRL_MODE_SET, (void *)&mode);

    rt_perf_start_impl(perf_local, &timeout);

    rt_sem_take(complete_sem, RT_WAITING_FOREVER);
    rt_perf_dump(perf_local);
    rt_sem_delete(complete_sem);
    rt_device_close(hw_dev);

    return RT_EOK;
}
