/*
 * Copyright (c) 2006-2024 RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2024/9/12      zhujiale     the first version
 * 2024/10/28     Shell        Added more assertions
 */

#include <rtdevice.h>
#include <utest.h>
#include <utest_assert.h>
#include <smp_call.h>

#define TEST_COUNT 10000

static int                pass_count = 0;
static RT_DEFINE_SPINLOCK(_test_data_lock);

static void _test_smp_cb(void *data)
{
    int *maskp;
    int  oncpu;

    if (!rt_hw_interrupt_is_disabled())
    {
        /* SYNC.004 */
        uassert_true(0);
    }

    rt_spin_lock(&_test_data_lock);

    oncpu   = rt_hw_cpu_id();
    maskp   = (int *)data;
    *maskp  &= ~(1 << oncpu);

    rt_spin_unlock(&_test_data_lock);
}

static void _blocking_call(void)
{
    volatile int cpu_mask;
    rt_ubase_t tested_cpus = 0;

    for (int i = 0; i < TEST_COUNT; i++)
    {
        cpu_mask = rand() % RT_ALL_CPU;
        tested_cpus |= cpu_mask;
        rt_smp_call_cpu_mask(cpu_mask, _test_smp_cb, (void *)&cpu_mask, SMP_CALL_WAIT_ALL);

        if (!cpu_mask)
        {
            pass_count++;
        }
        else
        {
            /* TARG.001, MP.001 */
            uassert_true(0);
            break;
        }
    }
    LOG_D("pass_count %d", pass_count);

    /* TARG.001 */
    uassert_true(pass_count == TEST_COUNT);

    /* TOP.001, TOP.002 */
    uassert_true(tested_cpus == RT_ALL_CPU);
}

static rt_err_t utest_tc_init(void)
{
    pass_count = 0;
    srand(rt_tick_get());
    return RT_EOK;
}

static rt_err_t utest_tc_cleanup(void)
{
    return RT_EOK;
}

static void _testcase(void)
{
    UTEST_UNIT_RUN(_blocking_call);
}

UTEST_TC_EXPORT(_testcase, "testcase.smp.smoke.001", utest_tc_init, utest_tc_cleanup, 10);
