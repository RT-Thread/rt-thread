/*
 * Copyright (c) 2006-2026, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2026-11-07     Wooohaaa     add touch framework utest
 */

/**
 * Test Case Name: Touch Framework Test
 *
 * Test Objectives:
 * - Verify registration and lookup for a simulated touch device.
 * - Verify read forwarding, coordinate range updates and interrupt control.
 * - Verify the touch interrupt callback order.
 *
 * Dependencies:
 * - Requires RT_UTEST_TOUCH and RT_USING_TOUCH.
 * - Uses a simulated device, so no touch hardware is needed.
 */

#include <rtthread.h>
#include <rtdevice.h>
#include "utest.h"

#ifdef RT_UTEST_TOUCH

#define TOUCH_TC_NAME "touch_tc"

struct touch_tc_context
{
    rt_size_t read_count;
    rt_uint32_t control_count;
    rt_uint32_t enable_count;
    rt_uint32_t disable_count;
    rt_uint32_t mode_count;
    rt_uint32_t irq_count;
    rt_uint32_t rx_count;
    rt_uint32_t callback_order;
    rt_uint32_t irq_order;
    rt_uint32_t rx_order;
    rt_int32_t last_cmd;
    void *last_arg;
    rt_err_t control_result;
    rt_err_t enable_result;
    rt_err_t disable_result;
    rt_err_t mode_result;
    rt_err_t irq_result;
    struct rt_touch_data read_data;
};

static struct touch_tc_context touch_tc_ctx;
static struct rt_touch_device touch_tc_dev;

static rt_size_t touch_tc_readpoint(struct rt_touch_device *touch, void *buf,
                                    rt_size_t touch_num)
{
    struct touch_tc_context *ctx = touch->parent.user_data;

    ctx->read_count = touch_num;
    if (touch_num > 0)
    {
        rt_memcpy(buf, &ctx->read_data, sizeof(ctx->read_data));
    }

    return touch_num;
}

static rt_err_t touch_tc_control(struct rt_touch_device *touch, int cmd, void *arg)
{
    struct touch_tc_context *ctx = touch->parent.user_data;

    ctx->control_count++;
    ctx->last_cmd = cmd;
    ctx->last_arg = arg;

    switch (cmd)
    {
    case RT_TOUCH_CTRL_ENABLE_INT:
        ctx->enable_count++;
        return ctx->enable_result;
    case RT_TOUCH_CTRL_DISABLE_INT:
        ctx->disable_count++;
        return ctx->disable_result;
    case RT_TOUCH_CTRL_SET_MODE:
        ctx->mode_count++;
        return ctx->mode_result;
    default:
        return ctx->control_result;
    }
}

static rt_err_t touch_tc_irq_handle(rt_touch_t touch)
{
    struct touch_tc_context *ctx = touch->parent.user_data;

    ctx->irq_count++;
    ctx->irq_order = ++ctx->callback_order;

    return ctx->irq_result;
}

static rt_err_t touch_tc_rx_indicate(rt_device_t device, rt_size_t size)
{
    struct touch_tc_context *ctx = device->user_data;

    ctx->rx_count++;
    ctx->rx_order = ++ctx->callback_order;

    return RT_EOK;
}

static const struct rt_touch_ops touch_tc_ops = {
    .touch_readpoint = touch_tc_readpoint,
    .touch_control = touch_tc_control,
};

static void touch_tc_reset(void)
{
    rt_memset(&touch_tc_ctx, 0, sizeof(touch_tc_ctx));
    touch_tc_ctx.control_result = RT_EOK;
    touch_tc_ctx.enable_result = RT_EOK;
    touch_tc_ctx.disable_result = RT_EOK;
    touch_tc_ctx.mode_result = RT_EOK;
    touch_tc_ctx.irq_result = RT_EOK;
    touch_tc_ctx.read_data.event = RT_TOUCH_EVENT_DOWN;
    touch_tc_ctx.read_data.x_coordinate = 123;
    touch_tc_ctx.read_data.y_coordinate = 456;
    touch_tc_dev.info.range_x = 0;
    touch_tc_dev.info.range_y = 0;
}

static void touch_tc_registration_test(void)
{
    rt_device_t device = rt_device_find(TOUCH_TC_NAME);

    uassert_not_null(device);
    if (device == RT_NULL)
    {
        return;
    }

    uassert_int_equal(device->type, RT_Device_Class_Touch);
    uassert_ptr_equal(touch_tc_dev.ops, &touch_tc_ops);
    uassert_ptr_equal(device->user_data, &touch_tc_ctx);
}

static void touch_tc_read_test(void)
{
    rt_device_t device = rt_device_find(TOUCH_TC_NAME);
    struct rt_touch_data data;

    uassert_not_null(device);
    if (device == RT_NULL)
    {
        return;
    }

    touch_tc_reset();
    uassert_int_equal(rt_device_open(device, RT_DEVICE_FLAG_RDWR), RT_EOK);
    uassert_int_equal(rt_device_read(device, 0, RT_NULL, 1), 0);
    uassert_int_equal(rt_device_read(device, 0, &data, 0), 0);
    uassert_int_equal(touch_tc_ctx.read_count, 0);
    uassert_int_equal(rt_device_read(device, 0, &data, 1), 1);
    uassert_int_equal(touch_tc_ctx.read_count, 1);
    uassert_int_equal(data.event, RT_TOUCH_EVENT_DOWN);
    uassert_int_equal(data.x_coordinate, 123);
    uassert_int_equal(data.y_coordinate, 456);
    uassert_int_equal(rt_device_close(device), RT_EOK);
}

static void touch_tc_range_test(void)
{
    rt_device_t device = rt_device_find(TOUCH_TC_NAME);
    rt_int32_t range = 800;

    uassert_not_null(device);
    if (device == RT_NULL)
    {
        return;
    }

    touch_tc_reset();
    uassert_int_equal(rt_device_control(device, RT_TOUCH_CTRL_SET_X_RANGE,
                                        &range),
                      RT_EOK);
    uassert_int_equal(touch_tc_dev.info.range_x, range);
    uassert_int_equal(touch_tc_ctx.last_cmd, RT_TOUCH_CTRL_SET_X_RANGE);
    uassert_ptr_equal(touch_tc_ctx.last_arg, &range);

    range = 600;
    touch_tc_ctx.control_result = -RT_ERROR;
    uassert_int_equal(rt_device_control(device, RT_TOUCH_CTRL_SET_Y_RANGE,
                                        &range),
                      -RT_ERROR);
    uassert_int_equal(touch_tc_dev.info.range_y, 0);
}

static void touch_tc_interrupt_error_test(void)
{
    rt_device_t device = rt_device_find(TOUCH_TC_NAME);
    rt_uint16_t mode = RT_DEVICE_FLAG_INT_RX;

    uassert_not_null(device);
    if (device == RT_NULL)
    {
        return;
    }

    touch_tc_reset();
    touch_tc_ctx.enable_result = -RT_EIO;
    uassert_int_equal(rt_device_control(device, RT_TOUCH_CTRL_ENABLE_INT,
                                        RT_NULL),
                      -RT_EIO);
    uassert_int_equal(touch_tc_ctx.enable_count, 1);

    touch_tc_ctx.disable_result = -RT_EIO;
    uassert_int_equal(rt_device_control(device, RT_TOUCH_CTRL_DISABLE_INT,
                                        RT_NULL),
                      -RT_EIO);
    uassert_int_equal(touch_tc_ctx.disable_count, 1);

    touch_tc_ctx.mode_result = -RT_EINVAL;
    uassert_int_equal(rt_device_control(device, RT_TOUCH_CTRL_SET_MODE,
                                        &mode),
                      -RT_EINVAL);
    uassert_int_equal(touch_tc_ctx.enable_count, 1);

    touch_tc_ctx.mode_result = RT_EOK;
    touch_tc_ctx.enable_result = -RT_EIO;
    uassert_int_equal(rt_device_control(device, RT_TOUCH_CTRL_SET_MODE,
                                        &mode),
                      -RT_EIO);
    uassert_int_equal(touch_tc_ctx.mode_count, 2);
    uassert_int_equal(touch_tc_ctx.enable_count, 2);
}

static void touch_tc_isr_test(void)
{
    touch_tc_reset();
    touch_tc_dev.irq_handle = touch_tc_irq_handle;
    touch_tc_dev.parent.rx_indicate = touch_tc_rx_indicate;

    rt_hw_touch_isr(&touch_tc_dev);

    uassert_int_equal(touch_tc_ctx.irq_count, 1);
    uassert_int_equal(touch_tc_ctx.rx_count, 1);
    uassert_true(touch_tc_ctx.irq_order < touch_tc_ctx.rx_order);

    touch_tc_dev.parent.rx_indicate = RT_NULL;
    rt_hw_touch_isr(&touch_tc_dev);
    uassert_int_equal(touch_tc_ctx.irq_count, 1);
    touch_tc_dev.irq_handle = RT_NULL;
}

static int touch_tc_device_init(void)
{
    touch_tc_reset();
    rt_memset(&touch_tc_dev, 0, sizeof(touch_tc_dev));
    touch_tc_dev.ops = &touch_tc_ops;
    touch_tc_dev.irq_handle = RT_NULL;

    return rt_hw_touch_register(&touch_tc_dev, TOUCH_TC_NAME,
                                RT_DEVICE_FLAG_RDWR, &touch_tc_ctx);
}
INIT_DEVICE_EXPORT(touch_tc_device_init);

static rt_err_t utest_tc_init(void)
{
    touch_tc_reset();

    return RT_EOK;
}

static rt_err_t utest_tc_cleanup(void)
{
    touch_tc_dev.parent.rx_indicate = RT_NULL;
    touch_tc_dev.irq_handle = RT_NULL;
    touch_tc_reset();

    return RT_EOK;
}

static void testcase(void)
{
    UTEST_UNIT_RUN(touch_tc_registration_test);
    UTEST_UNIT_RUN(touch_tc_read_test);
    UTEST_UNIT_RUN(touch_tc_range_test);
    UTEST_UNIT_RUN(touch_tc_interrupt_error_test);
    UTEST_UNIT_RUN(touch_tc_isr_test);
}

UTEST_TC_EXPORT(testcase, "components.drivers.touch.framework",
                utest_tc_init, utest_tc_cleanup, 10);

#endif /* RT_UTEST_TOUCH */
