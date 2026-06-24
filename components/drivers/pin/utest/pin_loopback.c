/*
 * Copyright (c) 2006-2026 RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2026-06-08     CYFS         add generic pin loopback utest
 */

/**
 * Test Case Name: Pin Two-wire Loopback Test
 *
 * Test Objectives:
 * - Validate the generic RT-Thread pin APIs with two externally shorted pins.
 * - Verify APIs: rt_device_find, rt_pin_get, rt_pin_mode, rt_pin_write,
 *   rt_pin_read, rt_pin_attach_irq, rt_pin_irq_enable, rt_pin_detach_irq.
 *
 * Test Scenarios:
 * - **Scenario 1 (GPIO level loopback / pin_loopback_level):**
 *   1. Resolve the configured output/input pins.
 *   2. Configure one pin as output and the shorted peer as input.
 *   3. Drive low and high levels from the output pin, then confirm the input
 *      pin follows each level.
 *   4. Reverse direction and repeat the level check to cover both pins.
 * - **Scenario 2 (GPIO IRQ loopback / pin_loopback_irq):**
 *   1. Configure the output pin low and attach an interrupt on the input pin.
 *   2. Toggle the output pin to generate rising, falling, and both-edge events.
 *   3. Wait for the interrupt callback after each generated edge.
 *
 * Dependencies:
 * - Requires `RT_UTEST_PIN` and two physical GPIO pins shorted together.
 * - Set `RT_UTEST_PIN_OUT_NAME`/`RT_UTEST_PIN_IN_NAME` or numeric
 *   `RT_UTEST_PIN_OUT_NUM`/`RT_UTEST_PIN_IN_NUM` for the connected pins.
 * - IRQ scenario requires `RT_UTEST_PIN_IRQ` and pin IRQ support in the BSP.
 *
 * Expected Results:
 * - Input level always matches the driven output level.
 * - If IRQ testing is enabled and supported, all configured edge callbacks
 *   arrive before timeout.
 */

#include <rtthread.h>
#include <rtdevice.h>
#include "utest.h"

#ifdef RT_UTEST_PIN

struct pin_loopback_ctx
{
    rt_base_t out_pin;
    rt_base_t in_pin;
};

static struct pin_loopback_ctx loopback_ctx;
#ifdef RT_UTEST_PIN_IRQ
static volatile rt_uint32_t irq_count;
#endif

static rt_bool_t pin_name_configured(const char *name)
{
    return (name != RT_NULL) && (name[0] != '\0');
}

static rt_base_t pin_resolve(const char *name, rt_base_t number)
{
    if (pin_name_configured(name))
    {
        return rt_pin_get(name);
    }

    return number;
}

static void pin_wait_settle(void)
{
    rt_thread_mdelay(RT_UTEST_PIN_SETTLE_MS);
}

static void pin_prepare_loopback(rt_base_t drive_pin, rt_base_t sense_pin)
{
    rt_pin_mode(sense_pin, PIN_MODE_INPUT);
    rt_pin_mode(drive_pin, PIN_MODE_OUTPUT);

    rt_pin_write(drive_pin, PIN_LOW);
    pin_wait_settle();
}

static void pin_drive_and_check(rt_base_t drive_pin, rt_base_t sense_pin, rt_uint8_t level)
{
    rt_pin_write(drive_pin, level);
    pin_wait_settle();
    uassert_int_equal((int)rt_pin_read(sense_pin), (int)level);
}

static void pin_loopback_level(void)
{
    pin_prepare_loopback(loopback_ctx.out_pin, loopback_ctx.in_pin);
    pin_drive_and_check(loopback_ctx.out_pin, loopback_ctx.in_pin, PIN_LOW);
    pin_drive_and_check(loopback_ctx.out_pin, loopback_ctx.in_pin, PIN_HIGH);

    pin_prepare_loopback(loopback_ctx.in_pin, loopback_ctx.out_pin);
    pin_drive_and_check(loopback_ctx.in_pin, loopback_ctx.out_pin, PIN_LOW);
    pin_drive_and_check(loopback_ctx.in_pin, loopback_ctx.out_pin, PIN_HIGH);

    rt_pin_write(loopback_ctx.in_pin, PIN_LOW);
}

#ifdef RT_UTEST_PIN_IRQ
static rt_tick_t pin_irq_timeout_ticks(void)
{
    rt_tick_t ticks;

    ticks = rt_tick_from_millisecond(RT_UTEST_PIN_IRQ_TIMEOUT_MS);
    if (ticks == 0)
    {
        ticks = 1;
    }

    return ticks;
}

static void pin_irq_handler(void *args)
{
    RT_UNUSED(args);

    irq_count++;
}

static rt_err_t pin_irq_wait_count(rt_uint32_t expected_count)
{
    rt_tick_t tick_start;
    rt_tick_t timeout;

    tick_start = rt_tick_get();
    timeout = pin_irq_timeout_ticks();

    while (irq_count < expected_count)
    {
        if (rt_tick_get_delta(tick_start) >= timeout)
        {
            return -RT_ETIMEOUT;
        }
        rt_thread_mdelay(1);
    }

    return RT_EOK;
}

static rt_err_t pin_irq_cleanup(rt_base_t pin)
{
    rt_err_t ret;

    ret = rt_pin_irq_enable(pin, PIN_IRQ_DISABLE);
    if (ret != RT_EOK)
    {
        return ret;
    }

    return rt_pin_detach_irq(pin);
}

static rt_err_t pin_irq_attach_enable(rt_uint8_t mode)
{
    rt_err_t ret;

    ret = rt_pin_attach_irq(loopback_ctx.in_pin, mode, pin_irq_handler, RT_NULL);
    if (ret != RT_EOK)
    {
        return ret;
    }

    ret = rt_pin_irq_enable(loopback_ctx.in_pin, PIN_IRQ_ENABLE);
    if (ret != RT_EOK)
    {
        rt_pin_detach_irq(loopback_ctx.in_pin);
    }

    return ret;
}

static void pin_trigger_rising(void)
{
    rt_pin_write(loopback_ctx.out_pin, PIN_LOW);
    pin_wait_settle();
    rt_pin_write(loopback_ctx.out_pin, PIN_HIGH);
}

static void pin_trigger_falling(void)
{
    rt_pin_write(loopback_ctx.out_pin, PIN_HIGH);
    pin_wait_settle();
    rt_pin_write(loopback_ctx.out_pin, PIN_LOW);
}

static void pin_loopback_irq_rising(void)
{
    rt_err_t ret;

    pin_prepare_loopback(loopback_ctx.out_pin, loopback_ctx.in_pin);
    irq_count = 0;

    ret = pin_irq_attach_enable(PIN_IRQ_MODE_RISING);
    if (ret == -RT_ENOSYS)
    {
        LOG_W("pin irq is not supported, skip rising-edge irq check");
        return;
    }
    uassert_int_equal(ret, RT_EOK);
    if (ret != RT_EOK)
    {
        return;
    }

    pin_trigger_rising();
    uassert_int_equal(pin_irq_wait_count(1), RT_EOK);
    uassert_int_equal((int)irq_count, 1);
    uassert_int_equal(pin_irq_cleanup(loopback_ctx.in_pin), RT_EOK);
}

static void pin_loopback_irq_falling(void)
{
    rt_err_t ret;

    pin_prepare_loopback(loopback_ctx.out_pin, loopback_ctx.in_pin);
    irq_count = 0;

    ret = pin_irq_attach_enable(PIN_IRQ_MODE_FALLING);
    if (ret == -RT_ENOSYS)
    {
        LOG_W("pin irq is not supported, skip falling-edge irq check");
        return;
    }
    uassert_int_equal(ret, RT_EOK);
    if (ret != RT_EOK)
    {
        return;
    }

    pin_trigger_falling();
    uassert_int_equal(pin_irq_wait_count(1), RT_EOK);
    uassert_int_equal((int)irq_count, 1);
    uassert_int_equal(pin_irq_cleanup(loopback_ctx.in_pin), RT_EOK);
}

static void pin_loopback_irq_both_edges(void)
{
    rt_err_t ret;

    pin_prepare_loopback(loopback_ctx.out_pin, loopback_ctx.in_pin);
    irq_count = 0;

    ret = pin_irq_attach_enable(PIN_IRQ_MODE_RISING_FALLING);
    if (ret == -RT_ENOSYS)
    {
        LOG_W("pin irq is not supported, skip both-edge irq check");
        return;
    }
    uassert_int_equal(ret, RT_EOK);
    if (ret != RT_EOK)
    {
        return;
    }

    pin_trigger_rising();
    uassert_int_equal(pin_irq_wait_count(1), RT_EOK);

    pin_trigger_falling();
    uassert_int_equal(pin_irq_wait_count(2), RT_EOK);

    uassert_int_equal((int)irq_count, 2);
    uassert_int_equal(pin_irq_cleanup(loopback_ctx.in_pin), RT_EOK);
}
#endif /* RT_UTEST_PIN_IRQ */

static rt_err_t utest_tc_init(void)
{
    if ((rt_device_find("pin") == RT_NULL) && (rt_device_find("gpio") == RT_NULL))
    {
        LOG_E("pin/gpio device is not registered");
        return -RT_ERROR;
    }

    loopback_ctx.out_pin = pin_resolve(RT_UTEST_PIN_OUT_NAME, RT_UTEST_PIN_OUT_NUM);
    loopback_ctx.in_pin = pin_resolve(RT_UTEST_PIN_IN_NAME, RT_UTEST_PIN_IN_NUM);

    if ((loopback_ctx.out_pin < 0) || (loopback_ctx.in_pin < 0))
    {
        LOG_E("invalid pin test config: out=%d in=%d", loopback_ctx.out_pin, loopback_ctx.in_pin);
        return -RT_ERROR;
    }

    if (loopback_ctx.out_pin == loopback_ctx.in_pin)
    {
        LOG_E("pin test output and input pins must be different");
        return -RT_ERROR;
    }

    LOG_I("pin loopback test uses output pin %d and input pin %d", loopback_ctx.out_pin, loopback_ctx.in_pin);

    return RT_EOK;
}

static rt_err_t utest_tc_cleanup(void)
{
#ifdef RT_UTEST_PIN_IRQ
    rt_pin_irq_enable(loopback_ctx.in_pin, PIN_IRQ_DISABLE);
    rt_pin_detach_irq(loopback_ctx.in_pin);
#endif
    rt_pin_mode(loopback_ctx.in_pin, PIN_MODE_INPUT);
    rt_pin_mode(loopback_ctx.out_pin, PIN_MODE_OUTPUT);
    rt_pin_write(loopback_ctx.out_pin, PIN_LOW);
    rt_pin_mode(loopback_ctx.out_pin, PIN_MODE_INPUT);

    return RT_EOK;
}

static void testcase(void)
{
    UTEST_UNIT_RUN(pin_loopback_level);
#ifdef RT_UTEST_PIN_IRQ
    UTEST_UNIT_RUN(pin_loopback_irq_rising);
    UTEST_UNIT_RUN(pin_loopback_irq_falling);
    UTEST_UNIT_RUN(pin_loopback_irq_both_edges);
#endif
}

UTEST_TC_EXPORT(testcase, "components.drivers.pin.loopback", utest_tc_init, utest_tc_cleanup, 20);

#endif /* RT_UTEST_PIN */
