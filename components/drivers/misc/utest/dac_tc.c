/*
 * Copyright (c) 2006-2026 RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2026-11-02     usualtreee   add DAC framework utest
 */

/**
 * Test Case Name: DAC Framework Test
 *
 * Test Objectives:
 * - Verify device registration and lookup for a simulated DAC device.
 * - Verify channel enable/disable and value conversion reach the driver ops.
 * - Verify the device control/write paths and resolution query.
 * - Verify conversion errors and missing optional hooks are reported correctly.
 * - Verify the testcase can be run repeatedly using persistent simulated devices.
 *
 * Dependencies:
 * - Requires RT_UTEST_DAC and RT_USING_DAC.
 * - Uses simulated devices, so no DAC hardware is needed.
 */

#include <rtthread.h>
#include <rtdevice.h>
#include "utest.h"

#ifdef RT_UTEST_DAC

#define DAC_TC_NAME       "dac_tc"
#define DAC_TC_MIN_NAME   "dac_min"
#define DAC_TC_CHANNEL    2
#define DAC_TC_RESOLUTION 12

struct dac_tc_context
{
    rt_uint32_t enable_count;
    rt_uint32_t disable_count;
    rt_uint32_t convert_count;
    rt_uint32_t last_channel;
    rt_uint32_t last_value;
    rt_err_t convert_result;
    rt_bool_t enabled;
};

static struct dac_tc_context dac_tc_ctx;
static struct rt_dac_device dac_tc_dev;
static struct rt_dac_device dac_tc_min_dev;

static rt_err_t dac_tc_enabled(struct rt_dac_device *device, rt_uint32_t channel)
{
    struct dac_tc_context *ctx = device->parent.user_data;

    ctx->enable_count++;
    ctx->last_channel = channel;
    ctx->enabled = RT_TRUE;

    return RT_EOK;
}

static rt_err_t dac_tc_disabled(struct rt_dac_device *device, rt_uint32_t channel)
{
    struct dac_tc_context *ctx = device->parent.user_data;

    ctx->disable_count++;
    ctx->last_channel = channel;
    ctx->enabled = RT_FALSE;

    return RT_EOK;
}

static rt_err_t dac_tc_convert(struct rt_dac_device *device, rt_uint32_t channel,
                               rt_uint32_t *value)
{
    struct dac_tc_context *ctx = device->parent.user_data;

    ctx->convert_count++;
    if (ctx->convert_result != RT_EOK)
    {
        return ctx->convert_result;
    }

    ctx->last_channel = channel;
    ctx->last_value = *value;

    return RT_EOK;
}

static rt_uint8_t dac_tc_get_resolution(struct rt_dac_device *device)
{
    return DAC_TC_RESOLUTION;
}

static const struct rt_dac_ops dac_tc_ops = {
    .disabled = dac_tc_disabled,
    .enabled = dac_tc_enabled,
    .convert = dac_tc_convert,
    .get_resolution = dac_tc_get_resolution,
};

static const struct rt_dac_ops dac_tc_min_ops = {
    .convert = dac_tc_convert,
};

static void dac_tc_reset(void)
{
    rt_memset(&dac_tc_ctx, 0, sizeof(dac_tc_ctx));
}

static void dac_tc_register_test(void)
{
    rt_device_t device = rt_device_find(DAC_TC_NAME);

    uassert_not_null(device);
    if (device == RT_NULL)
    {
        return;
    }

    uassert_int_equal(device->type, RT_Device_Class_DAC);
    uassert_ptr_equal(dac_tc_dev.ops, &dac_tc_ops);
    uassert_ptr_equal(device->user_data, &dac_tc_ctx);
}

static void dac_tc_enable_disable_test(void)
{
    rt_dac_device_t device = (rt_dac_device_t)rt_device_find(DAC_TC_NAME);

    uassert_not_null(device);
    if (device == RT_NULL)
    {
        return;
    }

    dac_tc_reset();
    uassert_int_equal(rt_dac_enable(device, DAC_TC_CHANNEL), RT_EOK);
    uassert_int_equal(dac_tc_ctx.enable_count, 1);
    uassert_int_equal(dac_tc_ctx.last_channel, DAC_TC_CHANNEL);
    uassert_true(dac_tc_ctx.enabled);

    uassert_int_equal(rt_dac_disable(device, DAC_TC_CHANNEL), RT_EOK);
    uassert_int_equal(dac_tc_ctx.disable_count, 1);
    uassert_int_equal(dac_tc_ctx.last_channel, DAC_TC_CHANNEL);
    uassert_false(dac_tc_ctx.enabled);
}

static void dac_tc_write_test(void)
{
    rt_dac_device_t device = (rt_dac_device_t)rt_device_find(DAC_TC_NAME);

    uassert_not_null(device);
    if (device == RT_NULL)
    {
        return;
    }

    dac_tc_reset();
    uassert_int_equal(rt_dac_write(device, DAC_TC_CHANNEL, 1234), RT_EOK);
    uassert_int_equal(dac_tc_ctx.convert_count, 1);
    uassert_int_equal(dac_tc_ctx.last_channel, DAC_TC_CHANNEL);
    uassert_int_equal(dac_tc_ctx.last_value, 1234);

    dac_tc_ctx.convert_result = -RT_ERROR;
    uassert_int_equal(rt_dac_write(device, DAC_TC_CHANNEL, 5678), -RT_ERROR);
    uassert_int_equal(dac_tc_ctx.convert_count, 2);
    uassert_int_equal(dac_tc_ctx.last_value, 1234);
}

static void dac_tc_device_ops_test(void)
{
    rt_device_t device = rt_device_find(DAC_TC_NAME);
    rt_uint32_t value = 2048;
    rt_uint8_t resolution = 0;

    uassert_not_null(device);
    if (device == RT_NULL)
    {
        return;
    }

    dac_tc_reset();
    uassert_int_equal(rt_device_control(device, RT_DAC_CMD_ENABLE,
                                        (void *)(rt_ubase_t)DAC_TC_CHANNEL),
                      RT_EOK);
    uassert_int_equal(dac_tc_ctx.enable_count, 1);

    uassert_int_equal(rt_device_control(device, RT_DAC_CMD_GET_RESOLUTION,
                                        &resolution),
                      RT_EOK);
    uassert_int_equal(resolution, DAC_TC_RESOLUTION);

    uassert_int_equal(rt_device_open(device, RT_DEVICE_FLAG_RDWR), RT_EOK);
    uassert_int_equal(rt_device_write(device, DAC_TC_CHANNEL, &value,
                                      sizeof(value)),
                      sizeof(value));
    uassert_int_equal(dac_tc_ctx.convert_count, 1);
    uassert_int_equal(dac_tc_ctx.last_channel, DAC_TC_CHANNEL);
    uassert_int_equal(dac_tc_ctx.last_value, value);
    uassert_int_equal(rt_device_close(device), RT_EOK);

    uassert_int_equal(rt_device_control(device, RT_DAC_CMD_DISABLE,
                                        (void *)(rt_ubase_t)DAC_TC_CHANNEL),
                      RT_EOK);
    uassert_int_equal(dac_tc_ctx.disable_count, 1);
    uassert_false(dac_tc_ctx.enabled);
}

static void dac_tc_missing_hooks_test(void)
{
    rt_dac_device_t device = (rt_dac_device_t)rt_device_find(DAC_TC_MIN_NAME);

    uassert_not_null(device);
    if (device == RT_NULL)
    {
        return;
    }

    dac_tc_reset();
    uassert_int_equal(rt_dac_enable(device, DAC_TC_CHANNEL), -RT_ENOSYS);
    uassert_int_equal(rt_dac_disable(device, DAC_TC_CHANNEL), -RT_ENOSYS);
    uassert_int_equal(dac_tc_ctx.enable_count, 0);
    uassert_int_equal(dac_tc_ctx.disable_count, 0);

    uassert_int_equal(rt_device_control(&device->parent, RT_DAC_CMD_ENABLE,
                                        (void *)(rt_ubase_t)DAC_TC_CHANNEL),
                      -RT_EINVAL);
}

static int dac_tc_device_init(void)
{
    rt_err_t result;

    dac_tc_reset();
    rt_memset(&dac_tc_dev, 0, sizeof(dac_tc_dev));
    rt_memset(&dac_tc_min_dev, 0, sizeof(dac_tc_min_dev));

    result = rt_hw_dac_register(&dac_tc_dev, DAC_TC_NAME, &dac_tc_ops,
                                &dac_tc_ctx);
    if (result != RT_EOK)
    {
        return result;
    }

    result = rt_hw_dac_register(&dac_tc_min_dev, DAC_TC_MIN_NAME,
                                &dac_tc_min_ops, &dac_tc_ctx);
    if (result != RT_EOK)
    {
        rt_device_unregister(&dac_tc_dev.parent);
        return result;
    }

    return RT_EOK;
}
INIT_DEVICE_EXPORT(dac_tc_device_init);

static rt_err_t utest_tc_init(void)
{
    dac_tc_reset();

    return RT_EOK;
}

static rt_err_t utest_tc_cleanup(void)
{
    dac_tc_reset();

    return RT_EOK;
}

static void testcase(void)
{
    UTEST_UNIT_RUN(dac_tc_register_test);
    UTEST_UNIT_RUN(dac_tc_enable_disable_test);
    UTEST_UNIT_RUN(dac_tc_write_test);
    UTEST_UNIT_RUN(dac_tc_device_ops_test);
    UTEST_UNIT_RUN(dac_tc_missing_hooks_test);
}

UTEST_TC_EXPORT(testcase, "components.drivers.dac.framework",
                utest_tc_init, utest_tc_cleanup, 10);

#endif /* RT_UTEST_DAC */
