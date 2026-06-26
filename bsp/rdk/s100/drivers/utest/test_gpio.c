/*
 * Copyright (c) 2006-2026, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2026-04-20     rcitach      first version
 */
#include <rtdevice.h>
#include <utest.h>

#include "drv_gpio.h"
#include "drv_pinmux.h"

/*
 * S100 GPIO utest 说明
 *
 * 1. 本文件合并了原先独立的 GPIO 基础功能测试和 GPIO IRQ 测试，统一面向当前
 *    rdk/s100 BSP 的 RT-Thread pin 驱动接口。
 * 2. 测试维度按驱动能力组织：
 *    - driver basic：校验 s100 私有驱动对非法/保留 pin 的拒绝逻辑；
 *    - pin io loopback：校验 rt_pin_mode/write/read 基础输入输出路径；
 *    - pin irq loopback：校验 rt_pin_attach_irq/irq_enable 在上升沿、下降沿、
 *      双边沿模式下的中断分发行为。
 * 3. 为了避免依赖旧板级 LED/KEY 资源，IO/IRQ 测试采用“一个输出脚 + 一个输入脚”
 *    的跳线回环方式。运行前请用杜邦线连接测试输出脚和测试输入脚。
 * 4. 默认使用 GPIO36 作为输出、GPIO37 作为输入；它们在当前 s100 驱动的黑名单和
 *    空洞编号之外。若板级接线需要变更，可在编译时覆盖下面两个宏。
 * 5. IRQ 测试通过切换输出脚电平来触发输入脚中断，因此不需要人工按键操作。
 */

#ifndef S100_GPIO_TEST_OUT_PIN
#define S100_GPIO_TEST_OUT_PIN          36
#endif

#ifndef S100_GPIO_TEST_IN_PIN
#define S100_GPIO_TEST_IN_PIN           37
#endif

#define S100_GPIO_INVALID_PIN           79
#define S100_GPIO_RESERVED_PIN          0
#define S100_GPIO_SETTLE_DELAY_MS       2
#define S100_GPIO_IRQ_TIMEOUT_TICKS     (RT_TICK_PER_SECOND / 2)

static struct rt_completion s100_gpio_irq_completion;
static volatile rt_uint32_t s100_gpio_irq_count;

static void s100_gpio_irq_handler(void *args)
{
    RT_UNUSED(args);
    s100_gpio_irq_count++;
    rt_completion_done(&s100_gpio_irq_completion);
}

static void s100_gpio_prepare_loopback(void)
{
    uassert_true(s100_pin_is_valid(S100_GPIO_TEST_OUT_PIN) == RT_TRUE);
    uassert_true(s100_pin_is_valid(S100_GPIO_TEST_IN_PIN) == RT_TRUE);
    uassert_true(S100_GPIO_TEST_OUT_PIN != S100_GPIO_TEST_IN_PIN);

    rt_pin_mode(S100_GPIO_TEST_OUT_PIN, PIN_MODE_OUTPUT);
    rt_pin_mode(S100_GPIO_TEST_IN_PIN, PIN_MODE_INPUT);

    rt_pin_write(S100_GPIO_TEST_OUT_PIN, PIN_LOW);
    rt_thread_mdelay(S100_GPIO_SETTLE_DELAY_MS);
}

static void s100_gpio_cleanup_irq(rt_base_t pin)
{
    rt_err_t ret;

    ret = rt_pin_irq_enable(pin, PIN_IRQ_DISABLE);
    uassert_int_equal(ret, RT_EOK);

    ret = rt_pin_detach_irq(pin);
    uassert_int_equal(ret, RT_EOK);
}

static void s100_gpio_wait_irq_once(void)
{
    rt_err_t ret;

    ret = rt_completion_wait(&s100_gpio_irq_completion, S100_GPIO_IRQ_TIMEOUT_TICKS);
    uassert_int_equal(ret, RT_EOK);
}

static void s100_gpio_trigger_rising(void)
{
    rt_pin_write(S100_GPIO_TEST_OUT_PIN, PIN_LOW);
    rt_thread_mdelay(S100_GPIO_SETTLE_DELAY_MS);
    rt_pin_write(S100_GPIO_TEST_OUT_PIN, PIN_HIGH);
}

static void s100_gpio_trigger_falling(void)
{
    rt_pin_write(S100_GPIO_TEST_OUT_PIN, PIN_HIGH);
    rt_thread_mdelay(S100_GPIO_SETTLE_DELAY_MS);
    rt_pin_write(S100_GPIO_TEST_OUT_PIN, PIN_LOW);
}

static void gpio_driver_rejects_invalid_pins(void)
{
    rt_err_t ret;

    uassert_true(s100_pin_is_valid(S100_GPIO_INVALID_PIN) == RT_FALSE);
    uassert_true(s100_pin_is_valid(S100_GPIO_RESERVED_PIN) == RT_FALSE);

    ret = s100_gpio_set_direction(S100_GPIO_INVALID_PIN, S100_PIN_DIR_OUT);
    uassert_int_equal(ret, -RT_EINVAL);

    ret = s100_gpio_write_pin(S100_GPIO_INVALID_PIN, S100_PIN_LEVEL_HIGH);
    uassert_int_equal(ret, -RT_EINVAL);

    ret = s100_gpio_set_direction(S100_GPIO_RESERVED_PIN, S100_PIN_DIR_OUT);
    uassert_int_equal(ret, -RT_EINVAL);
}

static void gpio_loopback_io(void)
{
    rt_ssize_t level;

    s100_gpio_prepare_loopback();

    rt_pin_write(S100_GPIO_TEST_OUT_PIN, PIN_LOW);
    rt_thread_mdelay(S100_GPIO_SETTLE_DELAY_MS);
    level = rt_pin_read(S100_GPIO_TEST_IN_PIN);
    uassert_int_equal(level, PIN_LOW);

    rt_pin_write(S100_GPIO_TEST_OUT_PIN, PIN_HIGH);
    rt_thread_mdelay(S100_GPIO_SETTLE_DELAY_MS);
    level = rt_pin_read(S100_GPIO_TEST_IN_PIN);
    uassert_int_equal(level, PIN_HIGH);

    rt_pin_write(S100_GPIO_TEST_OUT_PIN, PIN_LOW);
}

static void gpio_irq_rising_loopback(void)
{
    rt_err_t ret;

    s100_gpio_prepare_loopback();
    rt_completion_init(&s100_gpio_irq_completion);
    s100_gpio_irq_count = 0;

    ret = rt_pin_attach_irq(S100_GPIO_TEST_IN_PIN, PIN_IRQ_MODE_RISING,
                            s100_gpio_irq_handler, RT_NULL);
    uassert_int_equal(ret, RT_EOK);

    ret = rt_pin_irq_enable(S100_GPIO_TEST_IN_PIN, PIN_IRQ_ENABLE);
    uassert_int_equal(ret, RT_EOK);

    s100_gpio_trigger_rising();
    s100_gpio_wait_irq_once();
    uassert_int_equal((int)s100_gpio_irq_count, 1);

    s100_gpio_cleanup_irq(S100_GPIO_TEST_IN_PIN);
}

static void gpio_irq_falling_loopback(void)
{
    rt_err_t ret;

    s100_gpio_prepare_loopback();
    rt_completion_init(&s100_gpio_irq_completion);
    s100_gpio_irq_count = 0;

    ret = rt_pin_attach_irq(S100_GPIO_TEST_IN_PIN, PIN_IRQ_MODE_FALLING,
                            s100_gpio_irq_handler, RT_NULL);
    uassert_int_equal(ret, RT_EOK);

    ret = rt_pin_irq_enable(S100_GPIO_TEST_IN_PIN, PIN_IRQ_ENABLE);
    uassert_int_equal(ret, RT_EOK);

    s100_gpio_trigger_falling();
    s100_gpio_wait_irq_once();
    uassert_int_equal((int)s100_gpio_irq_count, 1);

    s100_gpio_cleanup_irq(S100_GPIO_TEST_IN_PIN);
}

static void gpio_irq_both_edge_loopback(void)
{
    rt_err_t ret;

    s100_gpio_prepare_loopback();
    rt_completion_init(&s100_gpio_irq_completion);
    s100_gpio_irq_count = 0;

    ret = rt_pin_attach_irq(S100_GPIO_TEST_IN_PIN, PIN_IRQ_MODE_RISING_FALLING,
                            s100_gpio_irq_handler, RT_NULL);
    uassert_int_equal(ret, RT_EOK);

    ret = rt_pin_irq_enable(S100_GPIO_TEST_IN_PIN, PIN_IRQ_ENABLE);
    uassert_int_equal(ret, RT_EOK);

    s100_gpio_trigger_rising();
    s100_gpio_wait_irq_once();

    rt_completion_init(&s100_gpio_irq_completion);
    s100_gpio_trigger_falling();
    s100_gpio_wait_irq_once();

    uassert_int_equal((int)s100_gpio_irq_count, 2);

    s100_gpio_cleanup_irq(S100_GPIO_TEST_IN_PIN);
}

static void testcase(void)
{
    UTEST_UNIT_RUN(gpio_driver_rejects_invalid_pins);
    UTEST_UNIT_RUN(gpio_loopback_io);
    UTEST_UNIT_RUN(gpio_irq_rising_loopback);
    UTEST_UNIT_RUN(gpio_irq_falling_loopback);
    UTEST_UNIT_RUN(gpio_irq_both_edge_loopback);
}

static rt_err_t utest_tc_init(void)
{
    return RT_EOK;
}

static rt_err_t utest_tc_cleanup(void)
{
    return RT_EOK;
}

UTEST_TC_EXPORT(testcase, "rdk.s100.drivers.gpio", utest_tc_init, utest_tc_cleanup, 20);

