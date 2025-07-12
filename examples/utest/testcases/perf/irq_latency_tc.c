/*
 * Copyright (c) 2006-2025, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2025-07-03     rcitach      test case for irq latency
 */

#include <rtthread.h>
#include <rtdevice.h>
#include <utest.h>
#include <utest_assert.h>
#include <perf_tc.h>

static rt_device_t hw_dev = RT_NULL;
static rt_sem_t complete_sem = RT_NULL;
static rt_hwtimerval_t timeout_s = {0};
static rt_perf_t *perf_local = RT_NULL;

static rt_uint32_t rt_perf_get_timer_us_local(void)
{
    rt_hwtimerval_t timer_val = {0};
    if (hw_dev && rt_device_read(hw_dev, 0, &timer_val, sizeof(rt_hwtimerval_t)))
    {
        return (rt_uint32_t)(timer_val.sec * 1000000u + timer_val.usec); /* return us */
    }
    return 0;
}

static void rt_perf_start_local(rt_perf_t *perf)
{
    if(hw_dev)
        rt_device_write(hw_dev, 0, &timeout_s, sizeof(rt_hwtimerval_t));

    perf->begin_time = rt_perf_get_timer_us_local();
}

static void rt_perf_stop_local(rt_perf_t *perf)
{
    perf->real_time = rt_perf_get_timer_us_local() - perf->begin_time - 500;  /* Counter value of the triggered interrupt */

    if (perf->real_time > perf->max_time)
    {
        perf->max_time = perf->real_time;
    }

    if (perf->real_time < perf->min_time)
    {
        perf->min_time = perf->real_time;
    }

    perf->count++;
    perf->tot_time += perf->real_time;

    if(hw_dev)
        rt_device_control(hw_dev, HWTIMER_CTRL_STOP, NULL);
}

static rt_err_t timer_callback(rt_device_t dev, rt_size_t size)
{
    rt_perf_stop_local(perf_local);
    if (perf_local->count >= UTEST_SYS_PERF_TC_COUNT)
    {
        rt_sem_release(complete_sem);
        return RT_EOK;
    }
    rt_perf_start_local(perf_local);
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
    rt_hwtimer_mode_t mode = HWTIMER_MODE_PERIOD;

    perf_local = perf;
    hw_dev = rt_device_find(UTEST_HWTIMER_DEV_NAME);
    if (hw_dev == RT_NULL)
    {
        ret = RT_ERROR;
        LOG_E("hwtimer sample run failed! can't find %s device!", UTEST_HWTIMER_DEV_NAME);
        return ret;
    }

    complete_sem = rt_sem_create("complete", 0, RT_IPC_FLAG_FIFO);
    timeout_s.sec = 0;
    timeout_s.usec = 500;   /* No modification is necessary here, use the fixed value */

    rt_device_set_rx_indicate(hw_dev, timer_callback);
    rt_device_control(hw_dev, HWTIMER_CTRL_MODE_SET, (void *)&mode);

    rt_perf_start_local(perf);

    rt_sem_take(complete_sem, RT_WAITING_FOREVER);
    rt_sem_delete(complete_sem);
    rt_device_close(hw_dev);

    return RT_EOK;
}

