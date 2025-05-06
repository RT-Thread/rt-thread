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
static struct rt_spinlock lock;
static int cnt = 0;

#define __REG32(x) (*((volatile unsigned int*)((rt_ubase_t)x)))
#define UART_FR(base)   __REG32(base + 0x18)
#define UART_DR(base)   __REG32(base + 0x00)
#define UARTFR_TXFF     0x20

static rt_err_t utest_get_c(struct rt_serial_device* serial, char ch, void* data)
{
    rt_atomic_add(&cnt, 1);
    return RT_EOK;
}

static int utest_getc(struct rt_serial_device* serial)
{
    static int num = 0;

    rt_spin_lock(&lock);
    if (rt_atomic_load(&num) == 10)
    {
        rt_atomic_flag_clear(&num);
        rt_spin_unlock(&lock);
        return -1;
    }
    rt_atomic_add(&num, 1);
    rt_spin_unlock(&lock);
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


static void thread_rx1(void* parameter)
{
    for (int i = 0; i < 10; i++)
    {
        rt_hw_serial_isr(_serial0, RT_SERIAL_EVENT_RX_IND);
    }
}

static void thread_rx2(void* parameter)
{
    for (int i = 0; i < 10; i++)
    {
        rt_workqueue_dowork(_serial0->bypass->lower_workq, &_serial0->bypass->work);
    }
}

static void thread_high_priority(void* parameter)
{
    for (int i = 1; i < 10; i++)
    {
        rt_bypass_upper_register(_serial0, "test", i, utest_get_c, RT_NULL);
        rt_bypass_upper_unregister(_serial0, i);
    }
}

static void thread_low_priority(void* parameter)
{
    for (int i = 0; i < 20; i++)
    {
        rt_hw_serial_isr(_serial0, RT_SERIAL_EVENT_RX_IND);
    }
}

static void bypass_rx_stress_003(void)
{
    const struct rt_uart_ops* tmp = _serial0->ops;

    rt_thread_t high = rt_thread_create("high_prio", thread_high_priority, RT_NULL, 2048, 15, 10);
    rt_thread_t low = rt_thread_create("low_prio", thread_low_priority, RT_NULL, 2048, 20, 10);

    rt_atomic_flag_clear(&cnt);
    _serial0->ops = &_utest_ops;
    rt_bypass_upper_register(_serial0, "test", 0, utest_get_c, RT_NULL);

    rt_thread_startup(high);
    rt_thread_startup(low);

    rt_thread_mdelay(1000);
    _serial0->ops = tmp;
    rt_bypass_upper_unregister(_serial0, 0);
    uassert_true(rt_atomic_load(&cnt) == 200);
}

static void bypass_rx_stress_002(void)
{
    const struct rt_uart_ops* tmp = _serial0->ops;
    rt_thread_t rx2 = rt_thread_create("rx2", thread_rx1, RT_NULL, 2048, RT_THREAD_PRIORITY_MAX - 5, 10);
    rt_thread_t rx3 = rt_thread_create("rx3", thread_rx2, RT_NULL, 2048, RT_THREAD_PRIORITY_MAX - 5, 10);

    rt_atomic_flag_clear(&cnt);
    _serial0->ops = &_utest_ops;
    rt_bypass_lower_register(_serial0, "utest", 0, utest_get_c, RT_NULL);

    rt_thread_startup(rx2);
    rt_thread_startup(rx3);

    rt_thread_mdelay(1000);

    uassert_true(rt_atomic_load(&cnt) == 100);
    _serial0->ops = tmp;
    rt_bypass_lower_unregister(_serial0, 0);
}

static void bypass_rx_stress_001(void)
{
    const struct rt_uart_ops* tmp = _serial0->ops;
    rt_thread_t rx1 = rt_thread_create("rx1", thread_rx1, RT_NULL, 2048, RT_THREAD_PRIORITY_MAX - 5, 10);
    rt_thread_t rx2 = rt_thread_create("rx1", thread_rx1, RT_NULL, 2048, RT_THREAD_PRIORITY_MAX - 5, 10);

    cnt = 0;
    _serial0->ops = &_utest_ops;
    rt_bypass_upper_register(_serial0, "utest", 0, utest_get_c, RT_NULL);

    rt_thread_startup(rx1);
    rt_thread_startup(rx2);

    rt_thread_mdelay(1000);

    uassert_true(rt_atomic_load(&cnt) == 200);
    _serial0->ops = tmp;
    rt_bypass_upper_unregister(_serial0, 0);
}

static rt_err_t utest_tc_init(void)
{
    _serial0 = (struct rt_serial_device*)rt_console_get_device();
    rt_spin_lock_init(&lock);
    return RT_EOK;
}

static rt_err_t utest_tc_cleanup(void)
{
    return RT_EOK;
}

static void _testcase(void)
{
    UTEST_UNIT_RUN(bypass_rx_stress_001);
    UTEST_UNIT_RUN(bypass_rx_stress_002);
    UTEST_UNIT_RUN(bypass_rx_stress_003);
}

UTEST_TC_EXPORT(_testcase, "testcase.bypass.conflict.001", utest_tc_init, utest_tc_cleanup, 10);
