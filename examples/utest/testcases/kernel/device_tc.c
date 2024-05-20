/*
 * Copyright (c) 2006-2024, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2024-05-20     Shell        the first version
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
UTEST_TC_EXPORT(testcase, "testcases.kernel.device.find", utest_tc_init, utest_tc_cleanup, 5);
