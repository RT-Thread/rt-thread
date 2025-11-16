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
#include <rtservice.h>
#include <utest.h>
#include <utest_assert.h>
#include <perf_tc.h>

#define RET_INT      0
#define RET_DECIMALS 1

#define GET_INT(num)      split_double(num, RET_INT)
#define GET_DECIMALS(num) split_double(num, RET_DECIMALS)

static rt_device_t hw_dev = RT_NULL;
static rt_hwtimerval_t timeout_s = { 0 };

typedef rt_err_t (*testcase_function)(rt_perf_t *perf);
testcase_function test_func_ptrs[] = {
    context_switch_test,
    rt_perf_thread_sem,
    rt_perf_thread_event,
    rt_perf_thread_mq,
    rt_perf_thread_mbox,
    rt_perf_irq_latency,    /* Timer Interrupt Source */
    RT_NULL
};

static rt_uint32_t rt_perf_get_timer_us(void)
{
    rt_hwtimerval_t timer_val = { 0 };
    if (hw_dev && rt_device_read(hw_dev, 0, &timer_val, sizeof(rt_hwtimerval_t)))
    {
        return (rt_uint32_t)(timer_val.sec * 1000000u + timer_val.usec); /* return us */
    }
    return 0;
}

void rt_perf_start_impl(rt_perf_t *perf, rt_hwtimerval_t *timeout)
{
    if (hw_dev)
    {
        if (timeout == RT_NULL)
            timeout = &timeout_s;
        rt_device_write(hw_dev, 0, timeout, sizeof(rt_hwtimerval_t));
    }
    perf->begin_time = rt_perf_get_timer_us();
}

void rt_perf_stop(rt_perf_t *perf)
{
    perf->real_time = rt_perf_get_timer_us() - perf->begin_time;

    if (perf->local_modify)
        perf->local_modify(perf);
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

    if (hw_dev)
        rt_device_control(hw_dev, HWTIMER_CTRL_STOP, NULL);
}

static rt_int32_t split_double(double num, rt_uint32_t type)
{
    if (type == RET_INT)
    {
        return (rt_int32_t)num;
    }
    else if (type == RET_DECIMALS)
    {
        return (rt_int32_t)((num - (rt_int32_t)num) * 10000);
    }
    else
    {
        return (-1);
    }

    return (-1);
}

void rt_perf_dump(rt_perf_t *perf)
{
    static rt_uint32_t test_index = 1;
    char avg_str[10] = { 0 };
    if (perf->dump_head)
    {
        rt_kprintf("Test No | Test Name            | Count | Total Time (us) | Max Time (us) | Min Time (us) | Avg Time (us)\n");
        rt_kprintf("--------|----------------------|-------|-----------------|---------------|---------------|--------------\n");
        perf->dump_head = RT_FALSE;
    }

    if (perf->count)
        perf->avg_time = (double)perf->tot_time / perf->count;
    else
        perf->avg_time = 0.0;

    rt_sprintf(avg_str, "%u.%04u", GET_INT(perf->avg_time), GET_DECIMALS(perf->avg_time));

    rt_kprintf("%7u | %-20s | %5u | %15u | %13u | %13u | %12s\n",
               test_index++,
               perf->name,
               perf->count,
               perf->tot_time,
               perf->max_time,
               perf->min_time,
               avg_str);
}

static void rt_perf_clear(rt_perf_t *perf)
{
    perf->local_modify = NULL;
    perf->begin_time = 0;
    perf->real_time = 0;
    perf->tot_time = 0;
    perf->max_time = 0;
    perf->min_time = RT_UINT32_MAX;
    perf->count = 0;
    perf->avg_time = 0;
    perf->tmp_time = 0;
}

static void rt_perf_all_test(void)
{
    rt_perf_t *perf_data = rt_malloc(sizeof(rt_perf_t));
    if (perf_data == RT_NULL)
    {
        return;
    }
    perf_data->lock = rt_mutex_create("perf", RT_IPC_FLAG_PRIO);
    perf_data->dump_head = RT_TRUE;
    rt_kprintf("\n === Performance Test Results Start ===\n");
    for (int i = 0; test_func_ptrs[i] != RT_NULL; i++)
    {
        rt_perf_clear(perf_data);
        if (test_func_ptrs[i](perf_data) != RT_EOK)
        {
            LOG_E("%s test fail", perf_data->name);
            continue;
        }
    }
    rt_kprintf("\n === Performance Test Results End ===\n");
    rt_mutex_delete(perf_data->lock);
    rt_free(perf_data);
}

static rt_err_t utest_tc_init(void)
{
    int ret = RT_EOK;

    hw_dev = rt_device_find(RT_UTEST_HWTIMER_DEV_NAME);
    if (hw_dev == RT_NULL)
    {
        ret = RT_ERROR;
        LOG_E("hwtimer sample run failed! can't find %s device!", RT_UTEST_HWTIMER_DEV_NAME);
        return ret;
    }
    ret = rt_device_open(hw_dev, RT_DEVICE_OFLAG_RDWR);
    if (ret != RT_EOK)
    {
        LOG_E("open %s device failed!", RT_UTEST_HWTIMER_DEV_NAME);
        return ret;
    }

    timeout_s.sec = 10;      /* No modification is necessary here, use the fixed value */
    timeout_s.usec = 0;

    return ret;
}

static rt_err_t utest_tc_cleanup(void)
{
    if (hw_dev)
        rt_device_close(hw_dev);
    return RT_EOK;
}

static void testcase(void)
{
    UTEST_UNIT_RUN(rt_perf_all_test);
}

UTEST_TC_EXPORT(testcase, "core.perf_test", utest_tc_init, utest_tc_cleanup, 10);

