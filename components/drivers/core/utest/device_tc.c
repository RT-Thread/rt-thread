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
* - Test rt_device_find(), rt_console_get_device(), and rt_console_set_device().
*
* Test Scenarios:
* - Locate a known console device by its actual name retrieved at runtime.
* - Attempt to find the same device using the predefined macro RT_CONSOLE_DEVICE_NAME.
* - Verify identity consistency when querying the same device through different but equivalent name sources.
* - Switch the console to a device that explicitly supports console-safe output flags.
* - Verify that devices without console-safe output flags are rejected.
*
* Verification Metrics:
* - rt_device_find() must return a non-NULL pointer when a valid device name is provided.
* - Pointers returned for the same logical device (via different name expressions) must be identical.
* - When RT_CONSOLE_DEVICE_NAME differs from the actual console name, two distinct but valid devices must be found.
* - rt_console_set_device() must only switch to devices that provide console open flags.
* - A rejected device must not replace the current console device.
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

struct test_console_context
{
    rt_uint16_t console_oflag;
    rt_uint16_t last_open_oflag;
    rt_err_t control_result;
    rt_uint8_t open_calls;
    rt_uint8_t close_calls;
};

static char _console_name[RT_NAME_MAX + 1];
static rt_atomic_t _device_sequence;

static rt_err_t test_console_open(rt_device_t dev, rt_uint16_t oflag)
{
    struct test_console_context *ctx = (struct test_console_context *)dev->user_data;

    ctx->last_open_oflag = oflag;
    ctx->open_calls++;

    return RT_EOK;
}

static rt_err_t test_console_close(rt_device_t dev)
{
    struct test_console_context *ctx = (struct test_console_context *)dev->user_data;

    ctx->close_calls++;

    return RT_EOK;
}

static rt_err_t test_console_control(rt_device_t dev, int cmd, void *args)
{
    struct test_console_context *ctx = (struct test_console_context *)dev->user_data;

    if (cmd != RT_DEVICE_CTRL_CONSOLE_OFLAG)
    {
        return -RT_ENOSYS;
    }

    if (ctx->control_result == RT_EOK && args != RT_NULL)
    {
        *(rt_uint16_t *)args = ctx->console_oflag;
    }

    return ctx->control_result;
}

#ifdef RT_USING_DEVICE_OPS
static const struct rt_device_ops test_console_ops =
{
    RT_NULL,
    test_console_open,
    test_console_close,
    RT_NULL,
    RT_NULL,
    test_console_control
};
#endif

static void make_test_device_name(char *name, rt_size_t size, const char *prefix)
{
    rt_uint32_t sequence = (rt_uint32_t)rt_atomic_add(&_device_sequence, 1);

    rt_snprintf(name, size, "%s%u", prefix, sequence);
}

static void init_test_console_device(struct rt_device *device,
                                     struct test_console_context *ctx,
                                     const char *name,
                                     rt_uint16_t flags,
                                     rt_err_t control_result,
                                     rt_uint16_t console_oflag)
{
    rt_memset(device, 0, sizeof(*device));
    rt_memset(ctx, 0, sizeof(*ctx));

    device->type = RT_Device_Class_Char;
    device->user_data = ctx;

#ifdef RT_USING_DEVICE_OPS
    device->ops = &test_console_ops;
#else
    device->open = test_console_open;
    device->close = test_console_close;
    device->control = test_console_control;
#endif

    ctx->control_result = control_result;
    ctx->console_oflag = console_oflag;

    uassert_int_equal(rt_device_register(device, name, flags), RT_EOK);
}

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

static void test_rt_console_set_device_accept_console_capable(void)
{
    struct rt_device device = {0};
    struct test_console_context ctx = {0};
    rt_device_t old_console = rt_console_get_device();
    char device_name[RT_NAME_MAX + 1] = {0};

    uassert_not_null(old_console);
    make_test_device_name(device_name, sizeof(device_name), "tcon");
    init_test_console_device(&device, &ctx, device_name,
                             RT_DEVICE_FLAG_RDWR,
                             RT_EOK,
                             RT_DEVICE_FLAG_RDWR | RT_DEVICE_FLAG_STREAM);

    uassert_ptr_equal(rt_console_set_device(device_name), old_console);
    uassert_ptr_equal(rt_console_get_device(), &device);
    uassert_int_equal(ctx.open_calls, 1);
    uassert_int_equal(ctx.last_open_oflag, RT_DEVICE_FLAG_RDWR | RT_DEVICE_FLAG_STREAM);

    uassert_ptr_equal(rt_console_set_device(_console_name), &device);
    uassert_ptr_equal(rt_console_get_device(), old_console);
    uassert_int_equal(ctx.close_calls, 1);

    uassert_int_equal(rt_device_unregister(&device), RT_EOK);
}

static void test_rt_console_set_device_accept_async_tx_device(void)
{
    struct rt_device device = {0};
    struct test_console_context ctx = {0};
    rt_device_t old_console = rt_console_get_device();
    char device_name[RT_NAME_MAX + 1] = {0};

    uassert_not_null(old_console);
    make_test_device_name(device_name, sizeof(device_name), "tint");
    init_test_console_device(&device, &ctx, device_name,
                             RT_DEVICE_FLAG_RDWR | RT_DEVICE_FLAG_INT_TX,
                             -RT_ENOSYS,
                             0);

    uassert_ptr_equal(rt_console_set_device(device_name), old_console);
    uassert_ptr_equal(rt_console_get_device(), &device);
    uassert_int_equal(ctx.open_calls, 1);
    uassert_int_equal(ctx.last_open_oflag,
                      RT_DEVICE_FLAG_RDWR | RT_DEVICE_FLAG_INT_TX | RT_DEVICE_FLAG_STREAM);

    uassert_ptr_equal(rt_console_set_device(_console_name), &device);
    uassert_ptr_equal(rt_console_get_device(), old_console);
    uassert_int_equal(ctx.close_calls, 1);

    uassert_int_equal(rt_device_unregister(&device), RT_EOK);
}

static void test_rt_console_set_device_reject_unsafe_device(void)
{
    struct rt_device device = {0};
    struct test_console_context ctx = {0};
    rt_device_t old_console = rt_console_get_device();
    char device_name[RT_NAME_MAX + 1] = {0};

    uassert_not_null(old_console);
    make_test_device_name(device_name, sizeof(device_name), "tbad");
    init_test_console_device(&device, &ctx, device_name,
                             RT_DEVICE_FLAG_RDWR,
                             -RT_ENOSYS,
                             0);

    uassert_null(rt_console_set_device(device_name));
    uassert_ptr_equal(rt_console_get_device(), old_console);
    uassert_int_equal(ctx.open_calls, 0);
    uassert_int_equal(ctx.close_calls, 0);

    uassert_int_equal(rt_device_unregister(&device), RT_EOK);
}

static rt_err_t utest_tc_init(void)
{
    rt_device_t console = rt_console_get_device();

    if (console != RT_NULL)
    {
        rt_snprintf(_console_name, sizeof(_console_name), "%s", console->parent.name);
    }

    return RT_EOK;
}

static rt_err_t utest_tc_cleanup(void)
{
    rt_device_t console = rt_console_get_device();

    if (_console_name[0] != '\0' && console != RT_NULL &&
        rt_strcmp(console->parent.name, _console_name) != 0)
    {
        if (rt_console_set_device(_console_name) == RT_NULL)
        {
            return -RT_ERROR;
        }
    }

    return RT_EOK;
}

static void testcase(void)
{
    UTEST_UNIT_RUN(test_rt_device_find);
    UTEST_UNIT_RUN(test_rt_console_set_device_accept_console_capable);
    UTEST_UNIT_RUN(test_rt_console_set_device_accept_async_tx_device);
    UTEST_UNIT_RUN(test_rt_console_set_device_reject_unsafe_device);
}
UTEST_TC_EXPORT(testcase, "components.drivers.core.device_find", utest_tc_init, utest_tc_cleanup, 5);
