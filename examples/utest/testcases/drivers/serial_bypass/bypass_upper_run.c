/*
 * Copyright (c) 2006-2024 RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2024-11-20     zhujiale     the first version
 */
#include <rtthread.h>
#include <rtdevice.h>
#include "utest.h"

static struct rt_serial_device* _serial0;
static int cnt;

#define __REG32(x) (*((volatile unsigned int*)((rt_ubase_t)x)))
#define UART_FR(base)   __REG32(base + 0x18)
#define UART_DR(base)   __REG32(base + 0x00)
#define UARTFR_TXFF     0x20
static rt_err_t utest_upper_run(struct rt_serial_device* serial, char ch, void* data)
{
    uassert_true(ch == 'a');
    cnt++;
    return RT_EOK;
}

static int utest_getc(struct rt_serial_device* serial)
{
    static rt_uint8_t num = 0;
    if (num == 10)
        return -1;
    num++;
    return 'a';
}

struct hw_uart_device
{
    rt_size_t hw_base;
    rt_size_t irqno;
};

static int uart_putc(struct rt_serial_device* serial, char c)
{
    struct hw_uart_device* uart;

    RT_ASSERT(serial != RT_NULL);
    uart = (struct hw_uart_device*)serial->parent.user_data;

    while (UART_FR(uart->hw_base) & UARTFR_TXFF);
    UART_DR(uart->hw_base) = c;

    return 1;
}

static const struct rt_uart_ops _utest_ops =
{
    RT_NULL,
    RT_NULL,
    uart_putc,
    utest_getc,
};

static rt_err_t utest_lower_run_test2(struct rt_serial_device* serial, char ch, void* data)
{
    static rt_uint8_t num = 0;
    num++;
    uassert_true(ch == ('a' + num));
    return RT_EOK;
}

static int utest_getc_2(struct rt_serial_device* serial)
{
    static rt_uint8_t num = 0;
    if (num == 20)
        return -1;
    num++;
    return 'a' + num;
}

static const struct rt_uart_ops _utest_ops2 =
{
    RT_NULL,
    RT_NULL,
    uart_putc,
    utest_getc_2,
};
static void bypass_upper_001(void)
{
    const struct rt_uart_ops* tmp = _serial0->ops;
    _serial0->ops = &_utest_ops;
    rt_bypass_upper_register(_serial0, "utest", RT_BYPASS_LEVEL_1, utest_upper_run, RT_NULL);
    rt_hw_serial_isr(_serial0, RT_SERIAL_EVENT_RX_IND);
    uassert_true(cnt == 10);
    _serial0->ops = tmp;
    rt_bypass_upper_unregister(_serial0, RT_BYPASS_LEVEL_1);
}

static void bypass_upper_002(void)
{
    const struct rt_uart_ops* tmp = _serial0->ops;
    _serial0->ops = &_utest_ops2;
    rt_bypass_upper_register(_serial0, "utest", RT_BYPASS_MAX_LEVEL, utest_lower_run_test2, RT_NULL);

    rt_hw_serial_isr(_serial0, RT_SERIAL_EVENT_RX_IND);
    rt_thread_mdelay(100);
    uassert_true(cnt == 10);
    _serial0->ops = tmp;
    rt_bypass_upper_unregister(_serial0, RT_BYPASS_MAX_LEVEL);
}

static rt_err_t utest_tc_init(void)
{
    _serial0 = (struct rt_serial_device*)rt_console_get_device();
    return RT_EOK;
}

static rt_err_t utest_tc_cleanup(void)
{
    return RT_EOK;
}

static void _testcase(void)
{
    UTEST_UNIT_RUN(bypass_upper_001);
    UTEST_UNIT_RUN(bypass_upper_002);
}

UTEST_TC_EXPORT(_testcase, "testcase.bypass.upper.001", utest_tc_init, utest_tc_cleanup, 10);
