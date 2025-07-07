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

#define IRQ_LATENCY 1000

static rt_device_t hw_dev = RT_NULL;
static rt_sem_t test_sem = RT_NULL;
static rt_hwtimerval_t timeout_s = {0};
volatile static rt_bool_t complete = RT_FALSE;
volatile static uint16_t irq_latency_count = 0;
static rt_hwtimerval_t irq_time[IRQ_LATENCY] = {0};

static rt_size_t get_timer_us(rt_hwtimerval_t *timeout_s)
{
    if (hw_dev)
        return rt_device_read(hw_dev, 0, timeout_s, sizeof(rt_hwtimerval_t));
    return 0;
}

static rt_err_t timer_callback(rt_device_t dev, rt_size_t size)
{
    get_timer_us(&irq_time[irq_latency_count]);
    irq_latency_count++;
    rt_device_control(hw_dev, HWTIMER_CTRL_STOP, RT_NULL);
    if (irq_latency_count >= IRQ_LATENCY)
    {
        complete = RT_TRUE;
        rt_sem_release(test_sem);
        return RT_EOK;
    }

    rt_device_write(hw_dev, 0, &timeout_s, sizeof(rt_hwtimerval_t));
    return RT_EOK;
}

void irq_latency_test(void)
{
    uint32_t total_time = 0;
    timeout_s.sec = 0;
    timeout_s.usec = 1000;
    rt_device_write(hw_dev, 0, &timeout_s, sizeof(rt_hwtimerval_t));

    rt_sem_take(test_sem, RT_WAITING_FOREVER);
    for (int i = 0; i < IRQ_LATENCY; i++)
    {
        total_time += ((irq_time[i].sec - timeout_s.sec) * 1000000) + (irq_time[i].usec - timeout_s.usec);
    }

    LOG_I("Total time for %d interrupts: %u us", IRQ_LATENCY, total_time);
    LOG_I("Average interrupt latency: %u us", total_time / IRQ_LATENCY);
}

static rt_err_t utest_tc_init(void)
{
    rt_hwtimer_mode_t mode = HWTIMER_MODE_PERIOD;

    test_sem = rt_sem_create("irq_test", 0, RT_IPC_FLAG_FIFO);
    if (test_sem == RT_NULL)
    {
        LOG_E("Failed to create semaphore");
        return -RT_ERROR;
    }

    hw_dev = rt_device_find(UTEST_HWTIMER_DEV_NAME);
    if (hw_dev == RT_NULL)
    {
        LOG_E("hwtimer sample run failed! can't find %s device!", UTEST_HWTIMER_DEV_NAME);
        rt_sem_delete(test_sem);
        return -RT_ERROR;
    }

    rt_err_t ret = rt_device_open(hw_dev, RT_DEVICE_OFLAG_RDWR);
    if (ret != RT_EOK)
    {
        LOG_E("open %s device failed!\n", UTEST_HWTIMER_DEV_NAME);
        rt_sem_delete(test_sem);
        return ret;
    }

    rt_device_set_rx_indicate(hw_dev, timer_callback);
    rt_device_control(hw_dev, HWTIMER_CTRL_MODE_SET, (void *)&mode);

    return RT_EOK;
}

static rt_err_t utest_tc_cleanup(void)
{
    complete = RT_FALSE;
    irq_latency_count = 0;
    rt_memset(irq_time, 0, sizeof(irq_time));
    if (test_sem)
    {
        rt_sem_delete(test_sem);
        test_sem = RT_NULL;
    }
#ifdef USING_HWTIME_AS_TIME_REF
    if (hw_dev) rt_device_close(hw_dev);
#endif
    return RT_EOK;
}

static void testcase(void)
{
    UTEST_UNIT_RUN(irq_latency_test);
}

UTEST_TC_EXPORT(testcase, "testcase.pref.irq_latency", utest_tc_init, utest_tc_cleanup, 10);
