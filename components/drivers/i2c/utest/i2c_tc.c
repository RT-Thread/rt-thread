/*
 * Copyright (c) 2006-2026 RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2026-11-03     usualtreee   add I2C framework utest
 */

/**
 * Test Case Name: I2C Framework Test
 *
 * Test Objectives:
 * - Verify bus registration and lookup for a simulated I2C bus.
 * - Verify message count, addresses, flags, lengths, and buffers reach the ops.
 * - Verify 10-bit addressing and master helper behavior.
 * - Verify transfer errors propagate and do not leave the bus locked.
 * - Verify empty transfers and missing transfer ops follow the API contract.
 * - Verify the testcase can run repeatedly using persistent simulated buses.
 *
 * Dependencies:
 * - Requires RT_UTEST_I2C and RT_USING_I2C.
 * - Uses simulated buses, so no I2C hardware is needed.
 */

#include <rtthread.h>
#include <rtdevice.h>
#include "utest.h"

#ifdef RT_UTEST_I2C

#define I2C_TC_NAME       "i2c_tc"
#define I2C_TC_MIN_NAME   "i2c_min"
#define I2C_TC_MAX_MSGS   2
#define I2C_TC_ADDR       0x50
#define I2C_TC_ADDR_2     0x51
#define I2C_TC_ADDR_10BIT 0x2aa

struct i2c_tc_context
{
    rt_uint32_t xfer_count;
    rt_uint32_t last_num;
    struct rt_i2c_msg last_msgs[I2C_TC_MAX_MSGS];
    rt_ssize_t xfer_result;
};

static struct i2c_tc_context i2c_tc_ctx;
static struct rt_i2c_bus_device i2c_tc_bus;
static struct rt_i2c_bus_device i2c_tc_min_bus;

struct i2c_tc_lock_context
{
    struct rt_i2c_bus_device *bus;
    volatile rt_bool_t completed;
    rt_err_t take_result;
    rt_err_t release_result;
};

static struct i2c_tc_lock_context i2c_tc_lock_ctx;

static void i2c_tc_lock_acquirer(void *parameter)
{
    struct i2c_tc_lock_context *ctx = parameter;

    ctx->take_result = rt_mutex_take(&ctx->bus->lock,
                                     rt_tick_from_millisecond(100));
    if (ctx->take_result == RT_EOK)
    {
        ctx->release_result = rt_mutex_release(&ctx->bus->lock);
    }
    ctx->completed = RT_TRUE;
}

static rt_ssize_t i2c_tc_master_xfer(struct rt_i2c_bus_device *bus,
                                     struct rt_i2c_msg msgs[],
                                     rt_uint32_t num)
{
    struct i2c_tc_context *ctx = bus->priv;
    rt_uint32_t i;

    ctx->xfer_count++;
    ctx->last_num = num;

    for (i = 0; i < num && i < I2C_TC_MAX_MSGS; i++)
    {
        ctx->last_msgs[i] = msgs[i];
    }

    if (ctx->xfer_result < 0)
    {
        return ctx->xfer_result;
    }

    return num;
}

static const struct rt_i2c_bus_device_ops i2c_tc_ops = {
    .master_xfer = i2c_tc_master_xfer,
};

static const struct rt_i2c_bus_device_ops i2c_tc_min_ops = {
    .master_xfer = RT_NULL,
};

static void i2c_tc_reset(void)
{
    rt_memset(&i2c_tc_ctx, 0, sizeof(i2c_tc_ctx));
}

static struct rt_i2c_bus_device *i2c_tc_find_bus(void)
{
    return rt_i2c_bus_device_find(I2C_TC_NAME);
}

static void i2c_tc_register_test(void)
{
    struct rt_i2c_bus_device *bus = i2c_tc_find_bus();

    uassert_not_null(bus);
    if (bus == RT_NULL)
    {
        return;
    }

    uassert_ptr_equal(bus, &i2c_tc_bus);
    uassert_int_equal(bus->parent.type, RT_Device_Class_I2CBUS);
    uassert_ptr_equal(bus->ops, &i2c_tc_ops);
    uassert_ptr_equal(bus->priv, &i2c_tc_ctx);
    uassert_true(bus->timeout > 0);
}

static void i2c_tc_transfer_test(void)
{
    struct rt_i2c_bus_device *bus = i2c_tc_find_bus();
    rt_uint8_t write_buf[] = { 0x12, 0x34, 0x56 };
    rt_uint8_t read_buf[] = { 0x78, 0x9a };
    struct rt_i2c_msg msgs[2];

    uassert_not_null(bus);
    if (bus == RT_NULL)
    {
        return;
    }

    rt_memset(msgs, 0, sizeof(msgs));
    msgs[0].addr = I2C_TC_ADDR;
    msgs[0].flags = RT_I2C_WR;
    msgs[0].len = sizeof(write_buf);
    msgs[0].buf = write_buf;
    msgs[1].addr = I2C_TC_ADDR_2;
    msgs[1].flags = RT_I2C_RD | RT_I2C_NO_STOP;
    msgs[1].len = sizeof(read_buf);
    msgs[1].buf = read_buf;

    i2c_tc_reset();
    uassert_int_equal(rt_i2c_transfer(bus, msgs, 2), 2);
    uassert_int_equal(i2c_tc_ctx.xfer_count, 1);
    uassert_int_equal(i2c_tc_ctx.last_num, 2);

    uassert_int_equal(i2c_tc_ctx.last_msgs[0].addr, I2C_TC_ADDR);
    uassert_int_equal(i2c_tc_ctx.last_msgs[0].flags, RT_I2C_WR);
    uassert_int_equal(i2c_tc_ctx.last_msgs[0].len, sizeof(write_buf));
    uassert_ptr_equal(i2c_tc_ctx.last_msgs[0].buf, write_buf);

    uassert_int_equal(i2c_tc_ctx.last_msgs[1].addr, I2C_TC_ADDR_2);
    uassert_int_equal(i2c_tc_ctx.last_msgs[1].flags, RT_I2C_RD | RT_I2C_NO_STOP);
    uassert_int_equal(i2c_tc_ctx.last_msgs[1].len, sizeof(read_buf));
    uassert_ptr_equal(i2c_tc_ctx.last_msgs[1].buf, read_buf);
}

static void i2c_tc_addr_10bit_test(void)
{
    struct rt_i2c_bus_device *bus = i2c_tc_find_bus();
    rt_uint8_t data[] = { 0xa5, 0x5a };
    struct rt_i2c_msg msg;

    uassert_not_null(bus);
    if (bus == RT_NULL)
    {
        return;
    }

    msg.addr = I2C_TC_ADDR_10BIT;
    msg.flags = RT_I2C_ADDR_10BIT | RT_I2C_WR;
    msg.len = sizeof(data);
    msg.buf = data;

    i2c_tc_reset();
    uassert_int_equal(rt_i2c_transfer(bus, &msg, 1), 1);
    uassert_int_equal(i2c_tc_ctx.last_msgs[0].addr, I2C_TC_ADDR_10BIT);
    uassert_int_equal(i2c_tc_ctx.last_msgs[0].flags,
                      RT_I2C_ADDR_10BIT | RT_I2C_WR);

    uassert_int_equal(rt_i2c_master_recv(bus, I2C_TC_ADDR_10BIT,
                                         RT_I2C_ADDR_10BIT, data, sizeof(data)),
                      sizeof(data));
    uassert_int_equal(i2c_tc_ctx.xfer_count, 2);
    uassert_int_equal(i2c_tc_ctx.last_msgs[0].addr, I2C_TC_ADDR_10BIT);
    uassert_int_equal(i2c_tc_ctx.last_msgs[0].flags,
                      RT_I2C_ADDR_10BIT | RT_I2C_RD);
    uassert_int_equal(i2c_tc_ctx.last_msgs[0].len, sizeof(data));
    uassert_ptr_equal(i2c_tc_ctx.last_msgs[0].buf, data);
}

static void i2c_tc_error_test(void)
{
    struct rt_i2c_bus_device *bus = i2c_tc_find_bus();
    rt_thread_t lock_thread;
    rt_uint8_t data[] = { 0xde, 0xad };
    rt_uint32_t wait_ticks;
    rt_err_t result;
    struct rt_i2c_msg msg;

    uassert_not_null(bus);
    if (bus == RT_NULL)
    {
        return;
    }

    msg.addr = I2C_TC_ADDR;
    msg.flags = RT_I2C_WR;
    msg.len = sizeof(data);
    msg.buf = data;

    i2c_tc_reset();
    i2c_tc_ctx.xfer_result = -RT_EIO;
    uassert_int_equal(rt_i2c_transfer(bus, &msg, 1), -RT_EIO);
    uassert_int_equal(i2c_tc_ctx.xfer_count, 1);

    /* A different thread must be able to acquire the lock after an error. */
    rt_memset(&i2c_tc_lock_ctx, 0, sizeof(i2c_tc_lock_ctx));
    i2c_tc_lock_ctx.bus = bus;
    i2c_tc_lock_ctx.take_result = -RT_ERROR;
    i2c_tc_lock_ctx.release_result = -RT_ERROR;
    lock_thread = rt_thread_create("i2c_tclk", i2c_tc_lock_acquirer,
                                   &i2c_tc_lock_ctx, UTEST_THR_STACK_SIZE,
                                   UTEST_THR_PRIORITY + 1, 10);
    uassert_not_null(lock_thread);
    if (lock_thread == RT_NULL)
    {
        return;
    }

    result = rt_thread_startup(lock_thread);
    if (result != RT_EOK)
    {
        rt_thread_delete(lock_thread);
        uassert_int_equal(result, RT_EOK);
        return;
    }

    for (wait_ticks = 0;
         wait_ticks < RT_TICK_PER_SECOND && !i2c_tc_lock_ctx.completed;
         wait_ticks++)
    {
        rt_thread_mdelay(1);
    }
    uassert_true(i2c_tc_lock_ctx.completed);
    uassert_int_equal(i2c_tc_lock_ctx.take_result, RT_EOK);
    uassert_int_equal(i2c_tc_lock_ctx.release_result, RT_EOK);

    /* Let the lock thread finish exiting before the next repeated test run. */
    rt_thread_mdelay(1);

    /* A successful single-message send returns the byte count, not one. */
    i2c_tc_ctx.xfer_result = RT_EOK;
    uassert_int_equal(rt_i2c_master_send(bus, I2C_TC_ADDR, RT_I2C_WR,
                                         data, sizeof(data)),
                      sizeof(data));
    uassert_int_equal(i2c_tc_ctx.xfer_count, 2);
    uassert_int_equal(i2c_tc_ctx.last_msgs[0].len, sizeof(data));
    uassert_ptr_equal(i2c_tc_ctx.last_msgs[0].buf, data);
}

static void i2c_tc_empty_transfer_test(void)
{
    struct rt_i2c_bus_device *bus = i2c_tc_find_bus();
    struct rt_i2c_msg msg;

    uassert_not_null(bus);
    if (bus == RT_NULL)
    {
        return;
    }

    rt_memset(&msg, 0, sizeof(msg));
    i2c_tc_reset();
    uassert_int_equal(rt_i2c_transfer(bus, &msg, 0), 0);
    uassert_int_equal(i2c_tc_ctx.xfer_count, 1);
    uassert_int_equal(i2c_tc_ctx.last_num, 0);
}

static void i2c_tc_missing_ops_test(void)
{
    struct rt_i2c_msg msg;

    rt_memset(&msg, 0, sizeof(msg));
    i2c_tc_reset();
    uassert_int_equal(rt_i2c_transfer(&i2c_tc_min_bus, &msg, 1), -RT_EINVAL);
    uassert_int_equal(i2c_tc_ctx.xfer_count, 0);
    uassert_null(rt_i2c_bus_device_find("i2c_none"));
}

static int i2c_tc_device_init(void)
{
    rt_err_t result;

    i2c_tc_reset();
    rt_memset(&i2c_tc_bus, 0, sizeof(i2c_tc_bus));
    rt_memset(&i2c_tc_min_bus, 0, sizeof(i2c_tc_min_bus));

    i2c_tc_bus.ops = &i2c_tc_ops;
    i2c_tc_bus.priv = &i2c_tc_ctx;
    result = rt_i2c_bus_device_register(&i2c_tc_bus, I2C_TC_NAME);
    if (result != RT_EOK)
    {
        return result;
    }

    i2c_tc_min_bus.ops = &i2c_tc_min_ops;
    i2c_tc_min_bus.priv = &i2c_tc_ctx;
    result = rt_i2c_bus_device_register(&i2c_tc_min_bus, I2C_TC_MIN_NAME);
    if (result != RT_EOK)
    {
        rt_device_unregister(&i2c_tc_bus.parent);
        return result;
    }

    return RT_EOK;
}
INIT_DEVICE_EXPORT(i2c_tc_device_init);

static rt_err_t utest_tc_init(void)
{
    i2c_tc_reset();

    return RT_EOK;
}

static rt_err_t utest_tc_cleanup(void)
{
    i2c_tc_reset();

    return RT_EOK;
}

static void testcase(void)
{
    UTEST_UNIT_RUN(i2c_tc_register_test);
    UTEST_UNIT_RUN(i2c_tc_transfer_test);
    UTEST_UNIT_RUN(i2c_tc_addr_10bit_test);
    UTEST_UNIT_RUN(i2c_tc_error_test);
    UTEST_UNIT_RUN(i2c_tc_empty_transfer_test);
    UTEST_UNIT_RUN(i2c_tc_missing_ops_test);
}

UTEST_TC_EXPORT(testcase, "components.drivers.i2c.framework",
                utest_tc_init, utest_tc_cleanup, 10);

#endif /* RT_UTEST_I2C */
