/*
 * Copyright (c) 2006-2021, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2021-08-15     supperthomas add irq_test
 * 2025-11-09     lhxj         Add standardized utest documentation block
 */

/**
 * Test Case Name: Kernel Core IRQ Test
 *
 * Test Objectives:
 * - Clearly specify the core functional module being validated by this test
 * - Validates the core kernel interrupt handling mechanisms.
 * - List specific functions or APIs to be tested
 * - rt_interrupt_enter_sethook()
 * - rt_interrupt_leave_sethook()
 * - rt_interrupt_get_nest()
 * - rt_hw_interrupt_disable()
 * - rt_hw_interrupt_enable()
 *
 * Test Scenarios:
 * - **Scenario 1 (Hook Test / irq_test):**
 * 1. Set interrupt enter/leave hooks that increment a counter (`irq_count`).
 * 2. Delay the thread (`rt_thread_mdelay`) to allow a SysTick interrupt to occur.
 * 3. Check if the hooks were triggered by the interrupt.
 * - **Scenario 2 (Global Disable Test / interrupt_test):**
 * 1. Set the same interrupt hooks.
 * 2. Globally disable CPU interrupts using `rt_hw_interrupt_disable()`.
 * 3. Execute a busy-wait loop.
 * 4. Check if the hooks were *not* triggered, proving interrupts were masked.
 *
 * Verification Metrics:
 * - List specific pass/fail criteria
 * - Expected return values, state changes, resource usage, etc.
 * - **Pass (Scenario 1):** `uassert_int_not_equal(0, irq_count)`
 * (The hook counter must be non-zero after the delay).
 * - **Pass (Scenario 1):** `uassert_int_not_equal(0, max_get_nest_count)`
 * (The recorded nesting level must be non-zero).
 * - **Pass (Scenario 2):** `uassert_int_equal(0, irq_count)`
 * (The hook counter must remain zero while interrupts are disabled).
 *
 * Dependencies:
 * - Hardware requirements (e.g., specific peripherals)
 * - Requires a hardware timer to generate the SysTick (system tick) interrupt.
 * (This is met by the qemu-virt64-riscv BSP).
 * - Software configuration (e.g., kernel options, driver initialization)
 * - `RT_USING_UTEST` must be enabled (`RT-Thread Utestcases`).
 * - `IRQ Test` must be enabled (`RT-Thread Utestcases` -> `Kernel Core` -> 'IRQ Test').
 * - Environmental assumptions
 * - Assumes the system is idle enough for `rt_thread_mdelay(2)` to
 * be interrupted by at least one SysTick.
 * - Run the test case from the msh prompt:
 * `utest_run core.irq`
 *
 * Expected Results:
 * - System behavior and performance after test execution
 * - The test case completes without errors or failed assertions.
 * - Observable outcomes like console output, log records, etc.
 * - The utest framework prints:
 * `[  PASSED  ] [ result   ] testcase (core.irq)`
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
UTEST_TC_EXPORT(testcase, "core.irq", utest_tc_init, utest_tc_cleanup, 10);
