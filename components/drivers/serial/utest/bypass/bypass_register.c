/*
 * Copyright (c) 2006-2024 RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2024-11-20     zhujiale     the first version
 * 2025-11-24     ChuanN-sudo  add standardized utest documentation block
 */

/**
 * Test Case Name: Serial Bypass Register Test
 *
 * Test Objectives:
 * - Validate serial bypass function registration and unregistration mechanisms.
 * - Verify correct ordering of bypass functions by priority level in concurrent scenarios.
 * - Ensure thread-safe registration of upper and lower bypass handlers.
 * - Test core APIs: rt_bypass_upper_register(), rt_bypass_lower_register(),
 *   rt_bypass_upper_unregister(), rt_bypass_lower_unregister()
 *
 * Test Scenarios:
 * - bypass_register_001: Main thread and worker thread concurrently register upper bypass
 *   functions with even/odd priority levels to test insertion ordering and thread safety.
 * - bypass_register_002: Two worker threads simultaneously register upper and lower bypass
 *   functions with levels 1-9 to verify independent queue management.
 * - Tests validate that registered functions maintain strict ascending order by level.
 * - Unregistration operations verify complete cleanup of bypass function chains.
 *
 * Verification Metrics:
 * - Bypass functions are inserted in correct priority order (level 0-9 ascending).
 * - Concurrent registrations from multiple threads maintain list integrity.
 * - Upper and lower bypass chains operate independently without interference.
 * - All registered bypass functions can be successfully unregistered by level.
 * - No memory leaks or list corruption after registration/unregistration cycles.
 *
 * Dependencies:
 * - Hardware requirements: Platform with serial console device (UART) support.
 * - Software configuration:
 *     - RT_USING_UTESTCASES must be enabled (select "RT-Thread Utestcases" in menuconfig).
 *     - RT_UTEST_SERIAL_BYPASS must be enabled (enable via: RT-Thread Utestcases -> Kernel Components -> Drivers -> Serial Test -> Serial Bypass Test).
 * - Environmental Assumptions: Serial device initialized and operational before test execution.
 *
 * Expected Results:
 * - Final output: "[ PASSED ] [ result ] testcase (components.drivers.serial.bypass_register)"
 * - All uassert_true() checks pass, confirming correct level ordering.
 */

#include <rtthread.h>
#include <rtdevice.h>
#include "utest.h"

static struct rt_serial_device* _serial0;
static struct rt_spinlock lock;

static rt_err_t utest_001_run(struct rt_serial_device* serial, char ch, void* data)
{
    return 0;
}

static void thread_serial_register1(void* parameter)
{
    for (int i = 2; i < 10; i += 2)
    {
        rt_bypass_upper_register(_serial0, "test", i, utest_001_run, RT_NULL);
    }
}

static void thread_serial_register_upper(void* parameter)
{
    for (int i = 1; i < 10; i++)
    {
        rt_bypass_upper_register(_serial0, "test", i, utest_001_run, RT_NULL);
    }
}

static void thread_serial_register_lower(void* parameter)
{
    for (int i = 1; i < 10; i++)
    {
        rt_bypass_lower_register(_serial0, "test", i, utest_001_run, RT_NULL);
    }
}

static void bypass_register_001(void)
{
    rt_thread_t t1 = rt_thread_create("serial_register", thread_serial_register1, RT_NULL, 2048, RT_THREAD_PRIORITY_MAX - 5, 10);
    rt_bypass_upper_register(_serial0, "test", 0, utest_001_run, RT_NULL);
    rt_thread_startup(t1);
    for (int i = 1; i < 10; i += 2)
    {
        rt_bypass_upper_register(_serial0, "test", i, utest_001_run, RT_NULL);
    }
    rt_thread_mdelay(1000);
    rt_list_t* node = _serial0->bypass->upper_h->head.next;
    for (int i = 0; i < 10;i++)
    {
        rt_list_t* next = node->next;
        struct rt_serial_bypass_func* temp = rt_container_of(node, struct rt_serial_bypass_func, node);
        uassert_true(temp->level == i);
        rt_bypass_upper_unregister(_serial0, temp->level);
        node = next;
    }

}

static void bypass_register_002(void)
{
    rt_thread_t t1 = rt_thread_create("serial_register", thread_serial_register_upper, RT_NULL, 2048, RT_THREAD_PRIORITY_MAX - 5, 10);
    rt_thread_t t2 = rt_thread_create("serial_register", thread_serial_register_lower, RT_NULL, 2048, RT_THREAD_PRIORITY_MAX - 5, 10);
    rt_bypass_upper_register(_serial0, "test", 0, utest_001_run, RT_NULL);

    rt_thread_startup(t1);
    rt_thread_startup(t2);

    rt_thread_mdelay(1000);
    rt_list_t* node = _serial0->bypass->upper_h->head.next;
    for (int i = 0; i < 10;i++)
    {
        rt_list_t* next = node->next;
        struct rt_serial_bypass_func* temp = rt_container_of(node, struct rt_serial_bypass_func, node);
        uassert_true(temp->level == i);
        rt_bypass_upper_unregister(_serial0, temp->level);
        node = next;
    }
    node = _serial0->bypass->lower_h->head.next;
    for (int i = 1; i < 10;i++)
    {
        rt_list_t* next = node->next;
        struct rt_serial_bypass_func* temp = rt_container_of(node, struct rt_serial_bypass_func, node);
        uassert_true(temp->level == i);
        rt_bypass_lower_unregister(_serial0, temp->level);
        node = next;
    }
}

static rt_err_t utest_tc_init(void)
{
    _serial0 = (struct rt_serial_device*)rt_console_get_device();
    rt_spin_lock_init(&lock);
    return RT_EOK;
}

static rt_err_t utest_tc_cleanup(void)
{
    return RT_EOK;
}

static void _testcase(void)
{
    UTEST_UNIT_RUN(bypass_register_001);
    UTEST_UNIT_RUN(bypass_register_002);
}

UTEST_TC_EXPORT(_testcase, "components.drivers.serial.bypass_register", utest_tc_init, utest_tc_cleanup, 10);
