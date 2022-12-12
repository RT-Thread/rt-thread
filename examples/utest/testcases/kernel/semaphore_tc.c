/*
 * Copyright (c) 2006-2019, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2021-08-12     luckyzjq     the first version
 */

#include <rtthread.h>
#include <stdlib.h>
#include "utest.h"

static struct rt_semaphore static_semaphore;
#ifdef RT_USING_HEAP
static rt_sem_t dynamic_semaphore;
#endif /* RT_USING_HEAP */

static void test_static_semaphore_init(void)
{
    rt_err_t result;
    int rand_num = rand() % 0x10000;

    for (int i = 0; i < rand_num; i++)
    {
        result = rt_sem_init(&static_semaphore, "static_sem", i, RT_IPC_FLAG_PRIO);
        if (RT_EOK != result)
        {
            uassert_true(RT_FALSE);
            break;
        }
        rt_sem_detach(&static_semaphore);

        result = rt_sem_init(&static_semaphore, "static_sem", i, RT_IPC_FLAG_FIFO);
        if (RT_EOK != result)
        {
            uassert_true(RT_FALSE);
            break;
        }
        rt_sem_detach(&static_semaphore);
    }

    uassert_true(RT_TRUE);
}

static void test_static_semaphore_detach(void)
{
    rt_err_t result;
    int rand_num = rand() % 0x10000;

    for (int i = 0; i < rand_num; i++)
    {
        result = rt_sem_init(&static_semaphore, "static_sem", i, RT_IPC_FLAG_PRIO);
        if (RT_EOK != result)
        {
            break;
        }

        result = rt_sem_detach(&static_semaphore);
        if (RT_EOK != result)
        {
            uassert_true(RT_FALSE);
            break;
        }

        result = rt_sem_init(&static_semaphore, "static_sem", i, RT_IPC_FLAG_FIFO);
        if (RT_EOK != result)
        {
            break;
        }
        result = rt_sem_detach(&static_semaphore);
        if (RT_EOK != result)
        {
            uassert_true(RT_FALSE);
            break;
        }
    }

    uassert_true(RT_TRUE);
}

static void test_static_semaphore_take(void)
{
    rt_err_t result;
    result = rt_sem_init(&static_semaphore, "static_sem", 1, RT_IPC_FLAG_PRIO);
    if (RT_EOK == result)
    {
        /* first take */
        result = rt_sem_take(&static_semaphore, RT_WAITING_FOREVER);
        if (RT_EOK != result)
            uassert_true(RT_FALSE);
        /* second take */
        result = rt_sem_take(&static_semaphore, 100);
        if (-RT_ETIMEOUT != result)
            uassert_true(RT_FALSE);
    }
    else
    {
        return;
    }

    rt_sem_detach(&static_semaphore);
    uassert_true(RT_TRUE);

    return;
}

static void test_static_semaphore_trytake(void)
{
    rt_err_t result;
    result = rt_sem_init(&static_semaphore, "static_sem", 1, RT_IPC_FLAG_PRIO);
    if (RT_EOK == result)
    {
        /* first take */
        result = rt_sem_trytake(&static_semaphore);
        if (RT_EOK != result)
            uassert_true(RT_FALSE);
        /* second take */
        result = rt_sem_trytake(&static_semaphore);
        if (-RT_ETIMEOUT != result)
            uassert_true(RT_FALSE);
    }
    else
    {
        return;
    }

    rt_sem_detach(&static_semaphore);
    uassert_true(RT_TRUE);

    return;
}

static void test_static_semaphore_release(void)
{
    rt_err_t result;
    result = rt_sem_init(&static_semaphore, "static_sem", 0, RT_IPC_FLAG_PRIO);
    if (RT_EOK == result)
    {
        /* first take */
        result = rt_sem_take(&static_semaphore, 100);
        if (-RT_ETIMEOUT != result)
            uassert_true(RT_FALSE);

        /* release */
        result = rt_sem_release(&static_semaphore);
        if (RT_EOK != result)
            uassert_true(RT_FALSE);

        /* second take */
        result = rt_sem_take(&static_semaphore, RT_WAITING_FOREVER);
        if (RT_EOK != result)
            uassert_true(RT_FALSE);
    }
    else
    {
        return;
    }

    rt_sem_detach(&static_semaphore);
    uassert_true(RT_TRUE);

    return;
}

static void test_static_semaphore_control(void)
{
    rt_err_t result;
    int value = 0;

    value = rand() % 100;
    result = rt_sem_init(&static_semaphore, "static_sem", 1, RT_IPC_FLAG_PRIO);
    if (RT_EOK == result)
    {
        result = rt_sem_control(&static_semaphore, RT_IPC_CMD_RESET, &value);
        if (RT_EOK != result)
        {
            uassert_true(RT_FALSE);
        }
    }
    else
    {
        return;
    }

    for (int i = 0; i < value; i++)
    {
        result = rt_sem_take(&static_semaphore, 10);
        if (RT_EOK != result)
        {
            uassert_true(RT_FALSE);
        }
    }

    rt_sem_detach(&static_semaphore);
    uassert_true(RT_TRUE);
}

static void static_release_isr_hardware_callback(void *param)
{
    rt_err_t result;

    result = rt_sem_release(&static_semaphore);
    if (RT_EOK != result)
    {
        uassert_true(RT_FALSE);
    }
}

static void static_release_isr_software_callback(void *param)
{
    rt_err_t result;

    result = rt_sem_release(&static_semaphore);
    if (RT_EOK != result)
    {
        uassert_true(RT_FALSE);
    }
}

static void test_static_semaphore_release_isr(void)
{
    rt_err_t result;
    rt_timer_t hardware_timer;
    rt_timer_t software_timer;

    /* create timer */
    hardware_timer = rt_timer_create("release_isr",
                                     static_release_isr_hardware_callback,
                                     RT_NULL,
                                     100,
                                     RT_TIMER_FLAG_HARD_TIMER | RT_TIMER_FLAG_ONE_SHOT);
    software_timer = rt_timer_create("release_isr",
                                     static_release_isr_software_callback,
                                     RT_NULL,
                                     100,
                                     RT_TIMER_FLAG_SOFT_TIMER | RT_TIMER_FLAG_ONE_SHOT);
    /* start tiemr */
    if (hardware_timer)
        rt_timer_start(hardware_timer);
    if (software_timer)
        rt_timer_start(software_timer);

    result = rt_sem_init(&static_semaphore, "static_sem", 0, RT_IPC_FLAG_PRIO);
    if (RT_EOK == result)
    {
        for (int i = 0; i < 2; i++)
        {
            result = rt_sem_take(&static_semaphore, 1000);
            if (RT_EOK != result)
            {
                uassert_true(RT_FALSE);
            }
        }
    }
    else
    {
        return;
    }

    rt_sem_detach(&static_semaphore);
    rt_timer_delete(hardware_timer);
    rt_timer_delete(software_timer);

    uassert_true(RT_TRUE);
}

#ifdef RT_USING_HEAP
static void test_dynamic_semaphore_create(void)
{
    int rand_num = rand() % 0x10000;

    for (int i = 0; i < rand_num; i++)
    {
        dynamic_semaphore = rt_sem_create("static_sem", i, RT_IPC_FLAG_PRIO);
        if (RT_NULL == dynamic_semaphore)
        {
            uassert_true(RT_FALSE);
            break;
        }
        rt_sem_delete(dynamic_semaphore);

        dynamic_semaphore = rt_sem_create("static_sem", i, RT_IPC_FLAG_FIFO);
        if (RT_NULL == dynamic_semaphore)
        {
            uassert_true(RT_FALSE);
            break;
        }
        rt_sem_delete(dynamic_semaphore);
    }

    uassert_true(RT_TRUE);
}

static void test_dynamic_semaphore_delete(void)
{
    rt_err_t result;
    int rand_num = rand() % 0x10000;

    for (int i = 0; i < rand_num; i++)
    {
        dynamic_semaphore = rt_sem_create("static_sem", i, RT_IPC_FLAG_PRIO);
        if (RT_NULL == dynamic_semaphore)
        {
            break;
        }

        result = rt_sem_delete(dynamic_semaphore);
        if (RT_EOK != result)
        {
            uassert_true(RT_FALSE);
            break;
        }

        dynamic_semaphore = rt_sem_create("static_sem", i, RT_IPC_FLAG_FIFO);
        if (RT_NULL == dynamic_semaphore)
        {
            break;
        }
        result = rt_sem_delete(dynamic_semaphore);
        if (RT_EOK != result)
        {
            uassert_true(RT_FALSE);
            break;
        }
    }

    uassert_true(RT_TRUE);
}

static void test_dynamic_semaphore_take(void)
{
    rt_err_t result;
    dynamic_semaphore = rt_sem_create("static_sem", 1, RT_IPC_FLAG_PRIO);
    if (RT_NULL != dynamic_semaphore)
    {
        /* first take */
        result = rt_sem_take(dynamic_semaphore, RT_WAITING_FOREVER);
        if (RT_EOK != result)
            uassert_true(RT_FALSE);
        /* second take */
        result = rt_sem_take(dynamic_semaphore, 100);
        if (-RT_ETIMEOUT != result)
            uassert_true(RT_FALSE);
    }
    else
    {
        return;
    }

    rt_sem_delete(dynamic_semaphore);
    uassert_true(RT_TRUE);

    return;
}

static void test_dynamic_semaphore_trytake(void)
{
    rt_err_t result;
    dynamic_semaphore = rt_sem_create("static_sem", 1, RT_IPC_FLAG_PRIO);
    if (RT_NULL != dynamic_semaphore)
    {
        /* first take */
        result = rt_sem_trytake(dynamic_semaphore);
        if (RT_EOK != result)
            uassert_true(RT_FALSE);
        /* second take */
        result = rt_sem_trytake(dynamic_semaphore);
        if (-RT_ETIMEOUT != result)
            uassert_true(RT_FALSE);
    }
    else
    {
        return;
    }

    rt_sem_delete(dynamic_semaphore);
    uassert_true(RT_TRUE);

    return;
}

static void test_dynamic_semaphore_release(void)
{
    rt_err_t result;
    dynamic_semaphore = rt_sem_create("static_sem", 0, RT_IPC_FLAG_PRIO);
    if (RT_NULL != dynamic_semaphore)
    {
        /* first take */
        result = rt_sem_take(dynamic_semaphore, 100);
        if (-RT_ETIMEOUT != result)
            uassert_true(RT_FALSE);

        /* release */
        result = rt_sem_release(dynamic_semaphore);
        if (RT_EOK != result)
            uassert_true(RT_FALSE);

        /* second take */
        result = rt_sem_take(dynamic_semaphore, RT_WAITING_FOREVER);
        if (RT_EOK != result)
            uassert_true(RT_FALSE);
    }
    else
    {
        return;
    }

    rt_sem_delete(dynamic_semaphore);
    uassert_true(RT_TRUE);

    return;
}

static void test_dynamic_semaphore_control(void)
{
    rt_err_t result;
    int value = 0;

    value = rand() % 100;
    dynamic_semaphore = rt_sem_create("static_sem", 1, RT_IPC_FLAG_PRIO);
    if (RT_NULL != dynamic_semaphore)
    {
        result = rt_sem_control(dynamic_semaphore, RT_IPC_CMD_RESET, &value);
        if (RT_EOK != result)
        {
            uassert_true(RT_FALSE);
        }
    }
    else
    {
        return;
    }

    for (int i = 0; i < value; i++)
    {
        result = rt_sem_take(dynamic_semaphore, 10);
        if (RT_EOK != result)
        {
            uassert_true(RT_FALSE);
        }
    }

    rt_sem_delete(dynamic_semaphore);
    uassert_true(RT_TRUE);
}

static void dynamic_release_isr_hardware_callback(void *param)
{
    rt_err_t result;

    result = rt_sem_release(dynamic_semaphore);
    if (RT_EOK != result)
    {
        uassert_true(RT_FALSE);
    }
}

static void dynamic_release_isr_software_callback(void *param)
{
    rt_err_t result;

    result = rt_sem_release(dynamic_semaphore);
    if (RT_EOK != result)
    {
        uassert_true(RT_FALSE);
    }
}

static void test_dynamic_semaphore_release_isr(void)
{
    rt_err_t result;
    rt_timer_t hardware_timer;
    rt_timer_t software_timer;

    /* create timer */
    hardware_timer = rt_timer_create("release_isr",
                                     dynamic_release_isr_hardware_callback,
                                     RT_NULL,
                                     100,
                                     RT_TIMER_FLAG_HARD_TIMER | RT_TIMER_FLAG_ONE_SHOT);
    software_timer = rt_timer_create("release_isr",
                                     dynamic_release_isr_software_callback,
                                     RT_NULL,
                                     100,
                                     RT_TIMER_FLAG_SOFT_TIMER | RT_TIMER_FLAG_ONE_SHOT);
    /* start tiemr */
    if (hardware_timer)
        rt_timer_start(hardware_timer);
    if (software_timer)
        rt_timer_start(software_timer);

    dynamic_semaphore = rt_sem_create("static_sem", 0, RT_IPC_FLAG_PRIO);
    if (RT_NULL != dynamic_semaphore)
    {
        for (int i = 0; i < 2; i++)
        {
            result = rt_sem_take(dynamic_semaphore, 1000);
            if (RT_EOK != result)
            {
                uassert_true(RT_FALSE);
            }
        }
    }
    else
    {
        return;
    }

    rt_sem_delete(dynamic_semaphore);
    rt_timer_delete(hardware_timer);
    rt_timer_delete(software_timer);

    uassert_true(RT_TRUE);
}

#endif /* RT_USING_HEAP */

static rt_err_t utest_tc_init(void)
{
#ifdef RT_USING_HEAP
    dynamic_semaphore = RT_NULL;
#endif /* RT_USING_HEAP */

    return RT_EOK;
}

static rt_err_t utest_tc_cleanup(void)
{
#ifdef RT_USING_HEAP
    dynamic_semaphore = RT_NULL;
#endif /* RT_USING_HEAP */

    return RT_EOK;
}

static void testcase(void)
{
    UTEST_UNIT_RUN(test_static_semaphore_init);
    UTEST_UNIT_RUN(test_static_semaphore_take);
    UTEST_UNIT_RUN(test_static_semaphore_release);
    UTEST_UNIT_RUN(test_static_semaphore_detach);
    UTEST_UNIT_RUN(test_static_semaphore_trytake);
    UTEST_UNIT_RUN(test_static_semaphore_control);
    UTEST_UNIT_RUN(test_static_semaphore_release_isr);

#ifdef RT_USING_HEAP
    UTEST_UNIT_RUN(test_dynamic_semaphore_create);
    UTEST_UNIT_RUN(test_dynamic_semaphore_take);
    UTEST_UNIT_RUN(test_dynamic_semaphore_release);
    UTEST_UNIT_RUN(test_dynamic_semaphore_delete);
    UTEST_UNIT_RUN(test_dynamic_semaphore_trytake);
    UTEST_UNIT_RUN(test_dynamic_semaphore_control);
    UTEST_UNIT_RUN(test_dynamic_semaphore_release_isr);
#endif /* RT_USING_HEAP */
}
UTEST_TC_EXPORT(testcase, "testcases.kernel.semaphore_tc", utest_tc_init, utest_tc_cleanup, 1000);
