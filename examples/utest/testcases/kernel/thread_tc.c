/*
 * Copyright (c) 2006-2021, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2021-09.01     yangjie      the firet version
 * 2021-10.11     mazhiyuan    add idle, yield, suspend, control, priority, delay_until
 */

#include <rtthread.h>
#include <stdlib.h>
#include "utest.h"

#define THREAD_STACK_SIZE  512
#define THREAD_TIMESLICE   10

ALIGN(RT_ALIGN_SIZE)
static char thread2_stack[1024];
static struct rt_thread thread2;
#ifdef RT_USING_HEAP
    static rt_thread_t tid1 = RT_NULL;
    static rt_thread_t tid3 = RT_NULL;
    static rt_thread_t tid4 = RT_NULL;
    static rt_thread_t tid5 = RT_NULL;
    static rt_thread_t tid6 = RT_NULL;
    static rt_thread_t tid7 = RT_NULL;
#endif /* RT_USING_HEAP */

static rt_uint32_t tid3_delay_pass_flag = 0;
static rt_uint32_t tid3_finish_flag = 0;
static rt_uint32_t tid4_finish_flag = 0;
static rt_uint32_t tid6_finish_flag = 0;
static rt_uint32_t thread5_source = 0;

#ifndef RT_USING_SMP
    static rt_uint32_t thread_yield_flag = 0;
#endif
static rt_uint32_t entry_idle_hook_times = 0;
static rt_thread_t __current_thread;
static rt_uint8_t change_priority;
static rt_uint32_t count = 0;

void thread1_entry(void *param)
{
    while (1);
}

static void test_dynamic_thread(void)
{
    rt_err_t ret_startup = -RT_ERROR;
    rt_err_t ret_delete = -RT_ERROR;

    tid1 = rt_thread_create("thread1",
                            thread1_entry,
                            (void *)1,
                            THREAD_STACK_SIZE,
                            __current_thread->current_priority + 1,
                            THREAD_TIMESLICE - 5);
    if (tid1 == RT_NULL)
    {
        uassert_false(tid1 == RT_NULL);
        goto __exit;
    }

    ret_startup = rt_thread_startup(tid1);
    if (ret_startup != RT_EOK)
    {
        uassert_false(ret_startup != RT_EOK);
        goto __exit;
    }

    ret_delete = rt_thread_delete(tid1);
    if (ret_delete != RT_EOK)
    {
        uassert_false(ret_delete != RT_EOK);
        goto __exit;
    }

    uassert_true(tid1 != RT_NULL && ret_startup == RT_EOK && ret_delete == RT_EOK);

__exit:
    if (tid1 != RT_NULL && ret_delete != RT_EOK)
    {
        rt_thread_delete(tid1);
    }
    return;
}

void thread2_entry(void *param)
{
    while (1);
}

static void test_static_thread(void)
{
    rt_err_t ret_init = -RT_ERROR;
    rt_err_t ret_startup = -RT_ERROR;
    rt_err_t ret_detach = - RT_ERROR;

    ret_init = rt_thread_init(&thread2,
                              "thread2",
                              thread2_entry,
                              (void *)2,
                              &thread2_stack[0],
                              sizeof(thread2_stack),
                              __current_thread->current_priority + 1,
                              THREAD_TIMESLICE);
    if (ret_init != RT_EOK)
    {
        uassert_false(ret_init != RT_EOK);
        goto __exit;
    }

    ret_startup = rt_thread_startup(&thread2);
    if (ret_startup != RT_EOK)
    {
        uassert_false(ret_startup != RT_EOK);
        goto __exit;
    }

    ret_detach = rt_thread_detach(&thread2);
    if (ret_detach != RT_EOK)
    {
        uassert_false(ret_detach != RT_EOK);
        goto __exit;
    }

    uassert_true(ret_init == RT_EOK && ret_startup == RT_EOK && ret_detach == RT_EOK);

__exit:
    if (ret_init == RT_EOK && ret_detach != RT_EOK)
    {
        rt_thread_detach(&thread2);
    }
    return;
}

static void thread3_entry(void *parameter)
{
    rt_tick_t tick;
    tick = rt_tick_get();
    rt_thread_delay(15);
    if (rt_tick_get() - tick > 16)
    {
        tid3_finish_flag = 1;
        tid3_delay_pass_flag = 0;
        return;
    }
    tid3_delay_pass_flag = 1;
    tid3_finish_flag = 1;
}

static void test_thread_delay(void)
{
    rt_err_t ret_startup = -RT_ERROR;

    tid3 = rt_thread_create("thread3",
                            thread3_entry,
                            RT_NULL,
                            THREAD_STACK_SIZE,
                            __current_thread->current_priority - 1,
                            THREAD_TIMESLICE);
    if (tid3 == RT_NULL)
    {
        LOG_E("rt_thread_create failed!");
        uassert_false(tid3 == RT_NULL);
        goto __exit;
    }

    ret_startup = rt_thread_startup(tid3);
    if (ret_startup != RT_EOK)
    {
        LOG_E("rt_thread_startup failed!");
        uassert_false(1);
        goto __exit;
    }

    while (tid3_finish_flag != 1);
    uassert_true(tid3_delay_pass_flag == 1);

__exit:
    return;
}

static void idle_hook(void)
{
    entry_idle_hook_times ++;
}

static void thread4_entry(void *parameter)
{
    rt_uint32_t delay_times = 5;
    while (delay_times --)
    {
        rt_thread_mdelay(300);
    }
    rt_thread_idle_delhook(idle_hook);
    tid4_finish_flag = 1;
}

static void test_idle_hook(void)
{
    rt_err_t ret_startup = -RT_ERROR;

    rt_thread_idle_sethook(idle_hook);

    tid4 = rt_thread_create("thread4",
                            thread4_entry,
                            RT_NULL,
                            THREAD_STACK_SIZE,
                            __current_thread->current_priority - 1,
                            THREAD_TIMESLICE);
    if (tid4 == RT_NULL)
    {
        LOG_E("rt_thread_create failed!");
        uassert_false(tid4 == RT_NULL);
        goto __exit;
    }

    ret_startup = rt_thread_startup(tid4);
    if (ret_startup != RT_EOK)
    {
        LOG_E("rt_thread_startup failed!");
        uassert_false(1);
        goto __exit;
    }

    while (tid4_finish_flag != 1)
    {
        rt_thread_mdelay(200);
    }
    uassert_true(entry_idle_hook_times > 0);

__exit:
    return;
}

static void thread5_entry(void *parameter)
{
    while (1)
    {
        thread5_source ++;
        rt_thread_delay(5);
        if (thread5_source == 5)
        {
            rt_thread_yield();
        }
    }
}

static void thread6_entry(void *parameter)
{
    while (++ thread5_source <= 9);
    tid6_finish_flag = 1;
}

static void test_thread_yield(void)
{
    rt_err_t ret_startup = -RT_ERROR;
    tid5 = rt_thread_create("thread5",
                            thread5_entry,
                            RT_NULL,
                            THREAD_STACK_SIZE,
                            __current_thread->current_priority - 1,
                            THREAD_TIMESLICE);
    if (tid5 == RT_NULL)
    {
        LOG_E("rt_thread_create failed!");
        uassert_false(tid5 == RT_NULL);
        goto __exit;
    }
    ret_startup = rt_thread_startup(tid5);
    if (ret_startup != RT_EOK)
    {
        LOG_E("rt_thread_startup failed!");
        uassert_false(1);
        goto __exit;
    }
    tid6 = rt_thread_create("thread6",
                            thread6_entry,
                            RT_NULL,
                            THREAD_STACK_SIZE,
                            __current_thread->current_priority - 1,
                            THREAD_TIMESLICE);
    if (tid6 == RT_NULL)
    {
        LOG_E("rt_thread_create failed!");
        uassert_false(tid6 == RT_NULL);
        goto __exit;
    }
    ret_startup = rt_thread_startup(tid6);
    if (ret_startup != RT_EOK)
    {
        LOG_E("rt_thread_startup failed!");
        uassert_false(1);
        goto __exit;
    }

    while (tid6_finish_flag != 1);
    uassert_true(thread5_source == 10);

__exit:
    if (tid5 != RT_NULL)
    {
        rt_thread_delete(tid5);
    }
    return;
}

static void thread7_entry(void *parameter)
{
    while (1);
}

static void test_thread_control(void)
{
    rt_err_t ret_control = -RT_ERROR;
    rt_err_t rst_delete = -RT_ERROR;

    tid7 = rt_thread_create("thread7",
                            thread7_entry,
                            RT_NULL,
                            THREAD_STACK_SIZE,
                            __current_thread->current_priority + 1,
                            THREAD_TIMESLICE);
    if (tid7 == RT_NULL)
    {
        LOG_E("rt_thread_create failed!");
        uassert_false(tid7 == RT_NULL);
        goto __exit;
    }

    ret_control = rt_thread_control(tid7, RT_THREAD_CTRL_STARTUP, RT_NULL);
    if (ret_control != RT_EOK)
    {
        LOG_E("rt_thread_control failed!");
        uassert_false(1);
        goto __exit;
    }
    rt_thread_mdelay(200);
    rt_thread_control(tid7, RT_THREAD_CTRL_CHANGE_PRIORITY, &change_priority);
    if (tid7->current_priority != change_priority)
    {
        LOG_E("rt_thread_control failed!");
        uassert_false(1);
        goto __exit;
    }
    rst_delete = rt_thread_control(tid7, RT_THREAD_CTRL_CLOSE, RT_NULL);
    if (rst_delete != RT_EOK)
    {
        LOG_E("rt_thread_control failed!");
        uassert_false(rst_delete != RT_EOK);
        goto __exit;
    }

    uassert_true(1);

__exit:
    if (tid7 != RT_NULL && rst_delete != RT_EOK)
    {
        rt_thread_delete(tid7);
    }
    return;
}

static void thread8_entry(void *parameter)
{
    for (; count < 10; count ++);
}

static void test_thread_priority(void)
{
    rt_err_t ret_startup = -RT_ERROR;
    rt_thread_t tid8 = RT_NULL;

    tid8 = rt_thread_create("thread8",
                            thread8_entry,
                            RT_NULL,
                            THREAD_STACK_SIZE,
                            __current_thread->current_priority - 1,
                            THREAD_TIMESLICE);
    if (tid8 == RT_NULL)
    {
        LOG_E("rt_thread_create failed!");
        uassert_false(tid8 == RT_NULL);
        return;
    }
    count = 0;
    ret_startup = rt_thread_startup(tid8);
    if (ret_startup != RT_EOK)
    {
        uassert_false(ret_startup != RT_EOK);
        return ;
    }
    uassert_true(count == 10);

    return;
}

static void test_delay_until(void)
{
    rt_tick_t tick;
    rt_tick_t check_tick = 0;
    rt_tick_t delta = 0;

    tick = rt_tick_get();

    check_tick = tick;
    rt_thread_delay_until(&tick, 100);
    delta = rt_tick_get() - check_tick;
    rt_kprintf("delta[100] -> %d\n", delta);
    uassert_int_equal(delta, 100);

    check_tick = tick;
    rt_thread_delay(2);
    rt_thread_delay_until(&tick, 200);
    delta = rt_tick_get() - check_tick;
    rt_kprintf("delta[200] -> %d\n", delta);
    uassert_int_equal(delta, 200);

    check_tick = tick;
    rt_thread_delay(2);
    rt_thread_delay_until(&tick, 300);
    delta = rt_tick_get() - check_tick;
    rt_kprintf("delta[300] -> %d\n", delta);
    uassert_int_equal(delta, 300);

    check_tick = tick;
    rt_thread_delay(2);
    rt_thread_delay_until(&tick, 100);
    delta = rt_tick_get() - check_tick;
    uassert_int_equal(delta, 100);

    check_tick = tick;
    rt_thread_delay(2);
    rt_thread_delay_until(&tick, 50);
    delta = rt_tick_get() - check_tick;
    rt_kprintf("delta[50] -> %d\n", delta);
    uassert_int_equal(delta, 50);

    check_tick = tick;
    rt_thread_delay(2);
    rt_thread_delay_until(&tick, 20);
    delta = rt_tick_get() - check_tick;
    rt_kprintf("delta[20] -> %d\n", delta);
    uassert_int_equal(delta, 20);

    check_tick = tick;
    rt_thread_delay(2);
    rt_thread_delay_until(&tick, 10);
    delta = rt_tick_get() - check_tick;
    rt_kprintf("delta[10] -> %d\n", delta);
    uassert_int_equal(delta, 10);
}

static rt_thread_t tidA, tidB1, tidB2;
static uint32_t timeslice_cntA, timeslice_cntB1, timeslice_cntB2;

static void test_timeslice_threadA_entry(void *parameter)
{
    while (1)
    {
        rt_thread_delay(2);
        timeslice_cntA++;
        if (timeslice_cntA > 10) return;
    }
}
static void test_timeslice_threadB1_entry(void *parameter)
{
    while (1)
    {
        timeslice_cntB1++;
        if (timeslice_cntA > 10) return;
    }
}
static void test_timeslice_threadB2_entry(void *parameter)
{
    while (1)
    {
        timeslice_cntB2++;
        if (timeslice_cntA > 10) return;
    }
}

void test_timeslice(void)
{
    rt_err_t ret_startup = -RT_ERROR;
    uint32_t diff;

    timeslice_cntA = 0;
    timeslice_cntB1 = 0;
    timeslice_cntB2 = 0;

    tidA = rt_thread_create("timeslice", test_timeslice_threadA_entry, RT_NULL,
                           2048, __current_thread->current_priority + 1, 10);
    if (!tidA)
    {
        LOG_E("rt_thread_create failed!");
        return;
    }

    rt_thread_control(tidA, RT_THREAD_CTRL_BIND_CPU, (void *)1);
    ret_startup = rt_thread_startup(tidA);
    if (ret_startup != RT_EOK)
    {
        LOG_E("rt_thread_startup failed!");
        uassert_false(1);
        return ;
    }

    tidB1 = rt_thread_create("timeslice", test_timeslice_threadB1_entry, RT_NULL,
                           2048, __current_thread->current_priority + 2, 2);
    if (!tidB1)
    {
        LOG_E("rt_thread_create failed!");
        return;
    }

    rt_thread_control(tidB1, RT_THREAD_CTRL_BIND_CPU, (void *)1);
    ret_startup = rt_thread_startup(tidB1);
    if (ret_startup != RT_EOK)
    {
        LOG_E("rt_thread_startup failed!");
        uassert_false(1);
        return ;
    }

    tidB2 = rt_thread_create("timeslice", test_timeslice_threadB2_entry, RT_NULL,
                           2048, __current_thread->current_priority + 2, 2);
    if (!tidB2)
    {
        LOG_E("rt_thread_create failed!");
        return;
    }

    rt_thread_control(tidB2, RT_THREAD_CTRL_BIND_CPU, (void *)1);
    ret_startup = rt_thread_startup(tidB2);
    if (ret_startup != RT_EOK)
    {
        LOG_E("rt_thread_startup failed!");
        uassert_false(1);
        return ;
    }
    do{
        rt_thread_delay(2 * 20);
    }while(timeslice_cntA <= 10);

    rt_kprintf("A:%d,B1:%d,B2:%d\n", timeslice_cntA, timeslice_cntB1, timeslice_cntB2);
    diff = abs(timeslice_cntB1 - timeslice_cntB2);
    uassert_true(diff * 100 / timeslice_cntB1 < 30);
    uassert_true(timeslice_cntA == 11);
}

#ifndef RT_USING_SMP
static volatile rt_uint32_t yield_count;

static void test_thread_yield_inc_entry(void *parameter)
{
    rt_uint32_t loop = 0;

    while (1)
    {
        if (loop++ > 10001)
            break;
        yield_count++;
        rt_thread_yield();
    }
}

static void test_thread_yield_entry(void *parameter)
{
    rt_err_t ret_startup = -RT_ERROR;

    rt_thread_t tid;
    rt_uint32_t loop = 0;
    rt_uint32_t count_before;

    tid = rt_thread_create("inc", test_thread_yield_inc_entry, RT_NULL,
                           2048, 1, 10);
    if (!tid)
    {
        LOG_E("rt_thread_create failed!");
        return;
    }

    ret_startup = rt_thread_startup(tid);
    if (ret_startup != RT_EOK)
    {
        LOG_E("rt_thread_startup failed!");
        uassert_false(1);
        return ;
    }

    while (1)
    {
        if (loop++ > 10000)
            break;

        count_before = yield_count;
        rt_thread_yield();
        if (yield_count == count_before)
        {
            LOG_E("yield error!");
            return;
        }
    }
    thread_yield_flag = 1;
}

void test_thread_yield_nosmp(void)
{
    rt_err_t ret_startup = -RT_ERROR;

    rt_thread_t tid;

    yield_count = 0;

    tid = rt_thread_create("chkcnt", test_thread_yield_entry, RT_NULL,
                           2048, 1, 10);
    if (!tid)
    {
        LOG_E("rt_thread_create failed!");
        return;
    }

    ret_startup = rt_thread_startup(tid);
    if (ret_startup != RT_EOK)
    {
        LOG_E("rt_thread_startup failed!");
        uassert_false(1);
        return ;
    }

    uassert_true(thread_yield_flag == 1);
}

static rt_uint32_t thread9_count = 0;
static void thread9_entry(void *parameter)
{
    while (1)
    {
        thread9_count ++;
    }

}
static void test_thread_suspend(void)
{
    static rt_thread_t tid;
    rt_err_t ret_startup = -RT_ERROR;
    uint32_t count_before_suspend, count_before_resume, count_after_resume;
    tid = rt_thread_create("thread9",
                           thread9_entry,
                           RT_NULL,
                           THREAD_STACK_SIZE,
                           __current_thread->current_priority + 1,
                           THREAD_TIMESLICE);
    if (tid == RT_NULL)
    {
        LOG_E("rt_thread_create failed!");
        uassert_false(tid4 == RT_NULL);
        goto __exit;
    }

    ret_startup = rt_thread_startup(tid);
    if (ret_startup != RT_EOK)
    {
        LOG_E("rt_thread_startup failed!");
        uassert_false(1);
        goto __exit;
    }
    rt_thread_delay(5);
    rt_thread_suspend(tid);
    count_before_suspend = thread9_count;
    uassert_true(count_before_suspend != 0);
    rt_thread_delay(5);
    count_before_resume = thread9_count;
    uassert_true(count_before_suspend == count_before_resume);
    rt_thread_resume(tid);
    rt_thread_delay(5);
    count_after_resume = thread9_count;
    uassert_true(count_after_resume != count_before_resume);

__exit:
    if (tid != RT_NULL)
    {
        rt_thread_delete(tid);
    }
    return;
}
#endif

static rt_err_t utest_tc_init(void)
{
    __current_thread = rt_thread_self();
    change_priority = __current_thread->current_priority + 5;
    tid3_delay_pass_flag = 0;
    tid3_finish_flag = 0;
    tid4_finish_flag = 0;
    tid6_finish_flag = 0;
    entry_idle_hook_times = 0;
    count = 0;
    return RT_EOK;
}

static rt_err_t utest_tc_cleanup(void)
{
    return RT_EOK;
}

static void testcase(void)
{
    /* init, detach */
    UTEST_UNIT_RUN(test_static_thread);
    /* create, delete */
    UTEST_UNIT_RUN(test_dynamic_thread);
    /* delay */
    UTEST_UNIT_RUN(test_thread_delay);
    /* idle_sethook, idle_delhook */
    UTEST_UNIT_RUN(test_idle_hook);
    /* yield */
    UTEST_UNIT_RUN(test_thread_yield);
#ifndef RT_USING_SMP
    /* yield_nosmp */
    UTEST_UNIT_RUN(test_thread_yield_nosmp);
    /* suspend, resume */
    UTEST_UNIT_RUN(test_thread_suspend);
#endif
    /* control */
    UTEST_UNIT_RUN(test_thread_control);
    UTEST_UNIT_RUN(test_thread_priority);
    /* delay_until */
    UTEST_UNIT_RUN(test_delay_until);
    /* timeslice */
    // UTEST_UNIT_RUN(test_timeslice); /* Can not running in Github Action QEMU */
}


UTEST_TC_EXPORT(testcase, "testcases.kernel.thread_tc", utest_tc_init, utest_tc_cleanup, 1000);

/********************* end of file ************************/
