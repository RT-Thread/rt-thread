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

#define RET_INT             0
#define RET_DECIMALS        1

#define GET_INT(num)        split_double(num, RET_INT)
#define GET_DECIMALS(num)   split_double(num, RET_DECIMALS)

static rt_device_t hw_dev = RT_NULL;
static rt_hwtimerval_t timeout_s = {0};

struct rt_perf_root
{
    struct rt_mutex lock;         /* lock */
    rt_list_t root_data;
};

typedef rt_err_t (*testcase_function)(rt_perf_t *perf);
testcase_function test_func_ptrs[] =
{
    context_switch_test,
    rt_perf_thread_sem,
    rt_perf_thread_event,
    rt_perf_thread_mq,
    rt_perf_thread_mbox,
    /* The interrupt delay test requires modifying the timer and setting the callback to be executed last. */
#ifdef UTEST_SYS_IRQ_LATENCY
    rt_perf_irq_latency,    /* Timer Interrupt Source */
#endif
    RT_NULL
};

static rt_uint32_t rt_perf_get_timer_us(void)
{
    rt_hwtimerval_t timer_val = {0};
    if (hw_dev && rt_device_read(hw_dev, 0, &timer_val, sizeof(rt_hwtimerval_t)))
    {
        return (rt_uint32_t)(timer_val.sec * 1000000u + timer_val.usec); /* return us */
    }
    return 0;
}

void rt_perf_start(rt_perf_t *perf)
{
    if(hw_dev)
        rt_device_write(hw_dev, 0, &timeout_s, sizeof(rt_hwtimerval_t));

    perf->begin_time = rt_perf_get_timer_us();
}

void rt_perf_stop(rt_perf_t *perf)
{
    perf->real_time = rt_perf_get_timer_us() - perf->begin_time;

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

static void rt_perf_dump(struct rt_perf_root *perf_root)
{
    rt_perf_t *perf = RT_NULL, *next = RT_NULL;
    rt_uint32_t test_index = 1;
    char avg_str[10] = {0};
    rt_mutex_take(&perf_root->lock, RT_WAITING_FOREVER);

    rt_kprintf("\n === Performance Test Results Start ===\n");
    rt_kprintf("Test No | Test Name            | Count | Total Time (us) | Max Time (us) | Min Time (us) | Avg Time (us)\n");
    rt_kprintf("--------|----------------------|-------|-----------------|---------------|---------------|--------------\n");

    rt_list_for_each_entry_safe(perf, next, &perf_root->root_data, data_list)
    {
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

        rt_list_remove(&perf->data_list);
        rt_free(perf);
    }
    rt_kprintf("\n === Performance Test Results End ===\n");
    rt_mutex_release(&perf_root->lock);
}

static rt_perf_t *rt_perf_create(void)
{
    rt_perf_t *perf = RT_NULL;

    perf = rt_malloc(sizeof(rt_perf_t));
    if (perf == RT_NULL)
    {
        return RT_NULL;
    }
    perf->begin_time = 0;
    perf->real_time = 0;
    perf->tot_time = 0;
    perf->max_time = 0;
    perf->min_time = RT_UINT32_MAX;
    perf->count = 0;
    perf->avg_time = 0;
    rt_list_init(&perf->data_list);
    return perf;
}

static void rt_perf_all_test(void)
{
    struct rt_perf_root *perf_root = rt_malloc(sizeof(struct rt_perf_root));
    rt_mutex_init(&perf_root->lock, "perf", RT_IPC_FLAG_PRIO);
    rt_list_init(&perf_root->root_data);

    for (int i = 0; test_func_ptrs[i] != RT_NULL; i++)
    {
        rt_perf_t *perf_data = rt_perf_create();
        if (test_func_ptrs[i](perf_data) != RT_EOK)
        {
            LOG_E("%s test fail",perf_data->name);
            continue;
        }
        rt_mutex_take(&perf_root->lock, RT_WAITING_FOREVER);
        rt_list_insert_before(&perf_root->root_data, &perf_data->data_list);
        rt_mutex_release(&perf_root->lock);
    }

    rt_perf_dump(perf_root);

    rt_mutex_detach(&perf_root->lock);
    rt_list_remove(&perf_root->root_data);
    rt_free(perf_root);
}

static rt_err_t utest_tc_init(void)
{
    int ret = RT_EOK;

    hw_dev = rt_device_find(UTEST_HWTIMER_DEV_NAME);
    if (hw_dev == RT_NULL)
    {
        ret = RT_ERROR;
        LOG_E("hwtimer sample run failed! can't find %s device!", UTEST_HWTIMER_DEV_NAME);
        return ret;
    }
    ret = rt_device_open(hw_dev, RT_DEVICE_OFLAG_RDWR);
    if (ret != RT_EOK)
    {
        LOG_E("open %s device failed!", UTEST_HWTIMER_DEV_NAME);
        return ret;
    }

    timeout_s.sec  = 10;      /* No modification is necessary here, use the fixed value */
    timeout_s.usec = 0;

    return ret;
}

static rt_err_t utest_tc_cleanup(void)
{
    if(hw_dev) rt_device_close(hw_dev);
    return RT_EOK;
}

static void testcase(void)
{
    UTEST_UNIT_RUN(rt_perf_all_test);
}

UTEST_TC_EXPORT(testcase, "testcase.pref.all", utest_tc_init, utest_tc_cleanup, 10);

