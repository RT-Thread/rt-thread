/*
 * Copyright (c) 2026, Linumiz
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2026-11-18     Parthiban    first version
 */

#include <rtthread.h>
#include <rtdevice.h>
#include "utest.h"

#define UART_NAME "rlin311"

static struct rt_serial_device *serial;
static struct serial_configure saved;

static rt_err_t apply(const struct serial_configure *cfg)
{
    struct serial_configure tmp = *cfg;

    return rt_device_control(&serial->parent, RT_DEVICE_CTRL_CONFIG, &tmp);
}

static void expect_reject(const struct serial_configure *cfg)
{
    struct serial_configure before = serial->config;

    uassert_int_equal(apply(cfg), -RT_EINVAL);
    uassert_true(rt_memcmp(&before, &serial->config, sizeof(before)) == 0);
}

static void test_baud_rates(void)
{
    static const rt_uint32_t good[] = { 9600, 19200, 38400, 57600, 115200 };
    static const rt_uint32_t bad[] = { 10, 1000000, 2000000, 4000000 };
    struct serial_configure cfg;
    rt_size_t i;

    for (i = 0; i < sizeof(good) / sizeof(good[0]); i++)
    {
        cfg = saved;
        cfg.baud_rate = good[i];
        uassert_int_equal(apply(&cfg), RT_EOK);
        uassert_int_equal(serial->config.baud_rate, good[i]);
    }
    uassert_int_equal(apply(&saved), RT_EOK);

    for (i = 0; i < sizeof(bad) / sizeof(bad[0]); i++)
    {
        cfg = saved;
        cfg.baud_rate = bad[i];
        expect_reject(&cfg);
    }
}

static void test_options(void)
{
    struct serial_configure cfg;

    cfg = saved;
    cfg.flowcontrol = RT_SERIAL_FLOWCONTROL_CTSRTS;
    expect_reject(&cfg);

    cfg = saved;
    cfg.bit_order = BIT_ORDER_MSB;
    expect_reject(&cfg);

    cfg = saved;
    cfg.invert = NRZ_INVERTED;
    expect_reject(&cfg);
}

static rt_err_t utest_tc_init(void)
{
    serial = (struct rt_serial_device *)rt_device_find(UART_NAME);
    if (serial == RT_NULL || serial->parent.ref_count == 0)
    {
        return -RT_ERROR;
    }
    saved = serial->config;
    return RT_EOK;
}

/* Runs after the units on pass and on fail, so the console keeps its settings */
static rt_err_t utest_tc_cleanup(void)
{
    if (apply(&saved) != RT_EOK)
    {
        return -RT_ERROR;
    }

    return (rt_memcmp(&saved, &serial->config, sizeof(saved)) == 0) ? RT_EOK : -RT_ERROR;
}

static void testcase(void)
{
    UTEST_UNIT_RUN(test_baud_rates);
    UTEST_UNIT_RUN(test_options);
}
UTEST_TC_EXPORT(testcase, "testcases.bsp.rh850.uart_config", utest_tc_init, utest_tc_cleanup, 10);
