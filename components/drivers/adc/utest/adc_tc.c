/*
 * Copyright (c) 2006-2026 RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2026-11-02     Yunlk        add ADC framework utest
 */

/**
 * Test Case Name: ADC Framework Test
 *
 * Test Objectives:
 * - Verify that rt_hw_adc_register() installs the expected device class and ops.
 * - Verify the enable/disable/convert/read paths reach the driver callbacks.
 * - Verify rt_adc_read() returns 0 when convert fails.
 * - Verify rt_adc_enable()/rt_adc_disable() return -RT_ENOSYS without an enabled() hook.
 * - Verify rt_adc_voltage() scales the raw value by the resolution and vref.
 *
 * Dependencies:
 * - Requires RT_UTEST_ADC and RT_USING_ADC.
 * - Uses a simulated device, so no ADC hardware is needed.
 *
 * Expected Results:
 * - All checks pass on any target that builds the ADC framework.
 */

#include <rtthread.h>
#include <rtdevice.h>
#include "utest.h"

#ifdef RT_UTEST_ADC

#define ADC_TC_NAME          "adc_tc"
#define ADC_TC_CHANNEL       3
#define ADC_TC_RESOLUTION    12
#define ADC_TC_VREF          3300    /* millivolts */
#define ADC_TC_RAW_VALUE     1000
#define ADC_TC_EXPECTED_MV   805     /* 1000 * 3300 / ((1 << 12) - 1) = 805.8 */

/* Bookkeeping for the simulated device. */
struct adc_tc_context
{
    int      enable_count;
    int      disable_count;
    int      convert_count;
    rt_bool_t enabled;
    rt_uint32_t fail_convert;
};

static struct adc_tc_context adc_tc_ctx;
static struct rt_adc_device  adc_tc_dev;

static rt_err_t adc_tc_enabled(struct rt_adc_device *device, rt_int8_t channel, rt_bool_t enabled)
{
    struct adc_tc_context *ctx = device->parent.user_data;

    RT_ASSERT(channel == ADC_TC_CHANNEL);

    if (enabled)
    {
        ctx->enable_count++;
        ctx->enabled = RT_TRUE;
    }
    else
    {
        ctx->disable_count++;
        ctx->enabled = RT_FALSE;
    }

    return RT_EOK;
}

static rt_err_t adc_tc_convert(struct rt_adc_device *device, rt_int8_t channel, rt_uint32_t *value)
{
    struct adc_tc_context *ctx = device->parent.user_data;

    RT_ASSERT(channel == ADC_TC_CHANNEL);

    ctx->convert_count++;

    if (ctx->fail_convert)
    {
        return -RT_ERROR;
    }

    *value = ADC_TC_RAW_VALUE;

    return RT_EOK;
}

static rt_uint8_t adc_tc_get_resolution(struct rt_adc_device *device)
{
    return ADC_TC_RESOLUTION;
}

static rt_int16_t adc_tc_get_vref(struct rt_adc_device *device)
{
    return ADC_TC_VREF;
}

static const struct rt_adc_ops adc_tc_ops =
{
    .enabled        = adc_tc_enabled,
    .convert        = adc_tc_convert,
    .get_resolution = adc_tc_get_resolution,
    .get_vref       = adc_tc_get_vref,
};

/* A device without the optional hooks, used for the -ENOSYS paths. */
static const struct rt_adc_ops adc_tc_ops_minimal =
{
    .convert = adc_tc_convert,
};

static void adc_tc_reset(void)
{
    rt_memset(&adc_tc_ctx, 0, sizeof(adc_tc_ctx));
    adc_tc_ctx.enabled = RT_FALSE;
}

static void adc_tc_register_test(void)
{
    rt_device_t dev;

    adc_tc_reset();
    rt_memset(&adc_tc_dev, 0, sizeof(adc_tc_dev));

    uassert_int_equal(rt_hw_adc_register(&adc_tc_dev, ADC_TC_NAME, &adc_tc_ops, &adc_tc_ctx),
                      RT_EOK);

    dev = rt_device_find(ADC_TC_NAME);
    uassert_not_null(dev);
    uassert_int_equal(dev->type, RT_Device_Class_ADC);

    /* the framework keeps the caller's ops */
    uassert_ptr_equal(adc_tc_dev.ops, &adc_tc_ops);
}

static void adc_tc_enable_disable_test(void)
{
    rt_adc_device_t dev = (rt_adc_device_t)rt_device_find(ADC_TC_NAME);

    uassert_not_null(dev);
    if (dev == RT_NULL)
    {
        return;
    }

    adc_tc_reset();

    uassert_int_equal(rt_adc_enable(dev, ADC_TC_CHANNEL), RT_EOK);
    uassert_int_equal(adc_tc_ctx.enable_count, 1);
    uassert_true(adc_tc_ctx.enabled == RT_TRUE);

    uassert_int_equal(rt_adc_disable(dev, ADC_TC_CHANNEL), RT_EOK);
    uassert_int_equal(adc_tc_ctx.disable_count, 1);
    uassert_true(adc_tc_ctx.enabled == RT_FALSE);
}

static void adc_tc_read_test(void)
{
    rt_adc_device_t dev = (rt_adc_device_t)rt_device_find(ADC_TC_NAME);

    uassert_not_null(dev);
    if (dev == RT_NULL)
    {
        return;
    }

    adc_tc_reset();
    adc_tc_ctx.fail_convert = RT_FALSE;
    uassert_int_equal(rt_adc_read(dev, ADC_TC_CHANNEL), ADC_TC_RAW_VALUE);
    uassert_int_equal(adc_tc_ctx.convert_count, 1);

    /* a failing convert() must be reported as 0, not as a stale value */
    adc_tc_reset();
    adc_tc_ctx.fail_convert = RT_TRUE;
    uassert_int_equal(rt_adc_read(dev, ADC_TC_CHANNEL), 0);
    uassert_int_equal(adc_tc_ctx.convert_count, 1);
}

static void adc_tc_voltage_test(void)
{
    rt_adc_device_t dev = (rt_adc_device_t)rt_device_find(ADC_TC_NAME);

    uassert_not_null(dev);
    if (dev == RT_NULL)
    {
        return;
    }

    adc_tc_reset();

    /*
     * Hardcoded on purpose: 1000 * 3300 / ((1 << 12) - 1) = 805. Recomputing it
     * from the raw value here would use the same formula as the code under test,
     * so a wrong formula would still "pass".
     */
    uassert_int_equal(rt_adc_voltage(dev, ADC_TC_CHANNEL), ADC_TC_EXPECTED_MV);

    /* rt_adc_voltage() enables, converts and disables exactly once */
    uassert_int_equal(adc_tc_ctx.enable_count, 1);
    uassert_int_equal(adc_tc_ctx.convert_count, 1);
    uassert_int_equal(adc_tc_ctx.disable_count, 1);
    uassert_true(adc_tc_ctx.enabled == RT_FALSE);
}

/* A driver may leave the optional hooks out; the framework has to report that. */
static void adc_tc_missing_hooks_test(void)
{
    static struct rt_adc_device minimal_dev;
    rt_adc_device_t dev;

    rt_memset(&minimal_dev, 0, sizeof(minimal_dev));

    uassert_int_equal(rt_hw_adc_register(&minimal_dev, "adc_tc_min", &adc_tc_ops_minimal,
                                         &adc_tc_ctx),
                      RT_EOK);

    dev = (rt_adc_device_t)rt_device_find("adc_tc_min");
    uassert_not_null(dev);
    if (dev == RT_NULL)
    {
        return;
    }

    adc_tc_reset();
    uassert_int_equal(rt_adc_enable(dev, ADC_TC_CHANNEL), -RT_ENOSYS);
    uassert_int_equal(rt_adc_disable(dev, ADC_TC_CHANNEL), -RT_ENOSYS);
    uassert_int_equal(adc_tc_ctx.enable_count, 0);
    uassert_int_equal(adc_tc_ctx.disable_count, 0);
}

static rt_err_t utest_tc_init(void)
{
    adc_tc_reset();

    return RT_EOK;
}

static rt_err_t utest_tc_cleanup(void)
{
    return RT_EOK;
}

static void testcase(void)
{
    UTEST_UNIT_RUN(adc_tc_register_test);
    UTEST_UNIT_RUN(adc_tc_enable_disable_test);
    UTEST_UNIT_RUN(adc_tc_read_test);
    UTEST_UNIT_RUN(adc_tc_voltage_test);
    UTEST_UNIT_RUN(adc_tc_missing_hooks_test);
}

UTEST_TC_EXPORT(testcase, "components.drivers.adc.framework", utest_tc_init, utest_tc_cleanup, 10);

#endif /* RT_UTEST_ADC */
