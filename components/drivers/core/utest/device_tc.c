/*
 * Copyright (c) 2006-2024, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2024-05-20     Shell        the first version
 * 2025-11-13     ChuanN       Add standardized utest documentation block
 */

/**
* Test Case Name: Drivers Core Test
*
* Test Objectives:
* - Validate the correctness and consistency of the rt_device_find() API in the RT-Thread device management subsystem.
* - Test rt_device_find() and rt_console_get_device().
*
* Test Scenarios:
* - Locate a known console device by its actual name retrieved at runtime.
* - Attempt to find the same device using the predefined macro RT_CONSOLE_DEVICE_NAME.
* - Verify identity consistency when querying the same device through different but equivalent name sources.
*
* Verification Metrics:
* - rt_device_find() must return a non-NULL pointer when a valid device name is provided.
* - Pointers returned for the same logical device (via different name expressions) must be identical.
* - When RT_CONSOLE_DEVICE_NAME differs from the actual console name, two distinct but valid devices must be found.
* - All assertions must pass without triggering test failure.
*
* Dependencies:
* - Hardware requirements: QEMU emulator or any hardware platform that supports RT-Thread with console device registration.
* - Software configuration:
*     - RT_USING_UTEST must be enabled (select "RT-Thread Utestcases" in menuconfig).
*     - BSP_UTEST_DRIVERS_CORE must be enabled (enable via: RT-Thread Utestcases -> Kernel components -> drivers -> Driver core Test).
* - Environmental assumptions: The system has initialized the console device before test execution.
*
* Expected Results:
* - The test will pass silently if all assertions hold.
* - Console will output: "[ PASSED ] [ result ] testcase (components.drivers.core.device_find)".
*/

#include <rtthread.h>
#include <stdlib.h>
#include "utest.h"

static void test_rt_device_find(void)
{
    char _device_name[RT_NAME_MAX + 1] = {0};
    rt_device_t console;
    rt_device_t device1, device2, device3;

    console = rt_console_get_device();
    uassert_not_null(console);
    rt_memcpy(_device_name, console->parent.name, RT_NAME_MAX);

    /* Test finding a device */
    device1 = rt_device_find(_device_name);
    uassert_true(device1 == console);

    /* Test finding another device */
    device2 = rt_device_find(RT_CONSOLE_DEVICE_NAME);
    if (rt_strcmp(RT_CONSOLE_DEVICE_NAME, _device_name) == 0)
    {
        uassert_true(device2 == device1);
    }
    else
    {
        uassert_not_null(device2);
        uassert_true(device2 != device1);
    }

    /* Test finding a device 3 */
    device3 = rt_device_find(console->parent.name);
    uassert_true(device1 == device3);
}

static rt_err_t utest_tc_init(void)
{
    return RT_EOK;
}

static rt_err_t utest_tc_cleanup(void)
{
    return RT_EOK;
}

static void testcase(void)
{
    UTEST_UNIT_RUN(test_rt_device_find);
}
UTEST_TC_EXPORT(testcase, "components.drivers.core.device_find", utest_tc_init, utest_tc_cleanup, 5);
