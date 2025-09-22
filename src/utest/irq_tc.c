/*
 * Copyright (c) 2006-2021, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2021-08-15     supperthomas add irq_test
 */

#include <rtthread.h>
#include "utest.h"
#include "rthw.h"

#define UTEST_NAME "irq_tc"
static volatile uint32_t irq_count = 0;
static volatile uint32_t max_get_nest_count = 0;

static void irq_callback()
{
    if(rt_interrupt_get_nest() >  max_get_nest_count)
    {
        max_get_nest_count = rt_interrupt_get_nest();
    }
    irq_count ++;
}

static void irq_test(void)
{
    irq_count = 0;
    rt_interrupt_enter_sethook(irq_callback);
    rt_interrupt_leave_sethook(irq_callback);
    rt_thread_mdelay(2);
    LOG_D("%s test irq_test! irq_count %d  max_get_nest_count %d\n", UTEST_NAME, irq_count, max_get_nest_count);
    uassert_int_not_equal(0, irq_count);
    uassert_int_not_equal(0, max_get_nest_count);
    rt_interrupt_enter_sethook(RT_NULL);
    rt_interrupt_leave_sethook(RT_NULL);
    LOG_D("irq_test OK!\n");
}

static rt_err_t utest_tc_init(void)
{
    irq_count = 0;
    max_get_nest_count = 0;
    return RT_EOK;
}

static rt_err_t utest_tc_cleanup(void)
{
    return RT_EOK;
}

static void interrupt_test(void)
{
    rt_base_t level;
    uint32_t i = 1000;

    rt_interrupt_enter_sethook(irq_callback);
    rt_interrupt_leave_sethook(irq_callback);
    irq_count = 0;
    level = rt_hw_interrupt_disable();
    while(i)
    {
        i --;
    }
    uassert_int_equal(0, irq_count);
    rt_hw_interrupt_enable(level);
    rt_interrupt_enter_sethook(RT_NULL);
    rt_interrupt_leave_sethook(RT_NULL);

}
static void testcase(void)
{
    UTEST_UNIT_RUN(irq_test);
    UTEST_UNIT_RUN(interrupt_test);
}
UTEST_TC_EXPORT(testcase, "testcases.kernel.irq_tc", utest_tc_init, utest_tc_cleanup, 10);
