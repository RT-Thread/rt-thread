/*
 * Copyright (c) 2006-2020, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 */

#include <rthw.h>
#include <rtdevice.h>
#include <rtthread.h>

#include "board.h"
#include "drv_uart.h"

#include <stdio.h>
#ifdef RT_USING_SMART
#include <ioremap.h>
#endif
#include "sbi.h"

struct device_uart
{
    rt_ubase_t hw_base;
    rt_uint32_t irqno;
};

void *uart0_base = (void*)0x10000000;
struct rt_serial_device serial0;
struct device_uart uart0;

void uart_init(void)
{
    rt_uint32_t div = UART_REFERENCE_CLOCK / (UART_DEFAULT_BAUDRATE * 16);

    write8_uart0(UART_IER, 0x00);
    write8_uart0(UART_LCR, UART_LCR_BAUD_LATCH);

    // LSB
    write8_uart0(0, div & 0xff);
    // MSB
    write8_uart0(1, (div >> 8) & 0xff);

    // set word length to 8 bits, no parity
    write8_uart0(UART_LCR, UART_LCR_EIGHT_BITS);

    write8_uart0(UART_FCR, UART_FCR_FIFO_ENABLE | UART_FCR_FIFO_CLEAR);

    return;
}

static rt_err_t _uart_configure(struct rt_serial_device *serial, struct serial_configure *cfg)
{
    return (RT_EOK);
}

static rt_err_t _uart_control(struct rt_serial_device *serial, int cmd, void *arg)
{
    struct device_uart *uart = (struct device_uart*)serial->parent.user_data;

    switch (cmd)
    {
    case RT_DEVICE_CTRL_CLR_INT:
        if ((size_t)arg == RT_DEVICE_FLAG_INT_RX)
        {
            rt_uint8_t value = read8_uart0(UART_IER);
            write8_uart0(UART_IER, value & ~UART_IER_RX_ENABLE);
        }
        break;

    case RT_DEVICE_CTRL_SET_INT:
        if ((size_t)arg == RT_DEVICE_FLAG_INT_RX)
        {
            rt_uint8_t value = read8_uart0(UART_IER);
            write8_uart0(UART_IER, value | UART_IER_RX_ENABLE);
        }
        break;
    }

    return (RT_EOK);
}

static int _uart_putc(struct rt_serial_device *serial, char c)
{
    struct device_uart *uart;
    uart = (struct device_uart*)serial->parent.user_data;

    // wait for Transmit Holding Empty to be set in LSR.
    while((read8_uart0(UART_LSR) & UART_LSR_TX_IDLE) == 0)
        ;
    write8_uart0(UART_THR, c);

    return (1);
}

static int _uart_getc(struct rt_serial_device *serial)
{
    struct device_uart *uart;
    volatile rt_uint32_t lsr;
    int ch = -1;

    uart = (struct device_uart*)serial->parent.user_data;
    lsr = read8_uart0(UART_LSR);

    if (lsr & UART_LSR_RX_READY)
    {
        ch = read8_uart0(UART_RHR);
    }
    return ch;
}

const struct rt_uart_ops _uart_ops = {
    _uart_configure,
    _uart_control,
    _uart_putc,
    _uart_getc,
    // TODO: add DMA support
    RT_NULL};

static void rt_hw_uart_isr(int irqno, void *param)
{
    rt_ubase_t level = rt_hw_interrupt_disable();

    struct rt_serial_device *serial = (struct rt_serial_device *)param;

    rt_hw_serial_isr(serial, RT_SERIAL_EVENT_RX_IND);

    rt_hw_interrupt_enable(level);
}

/*
 * UART Initiation
 */
int rt_hw_uart_init(void)
{
    struct rt_serial_device *serial;
    struct device_uart *uart;
    struct serial_configure config = RT_SERIAL_CONFIG_DEFAULT;
#ifdef RT_USING_SMART
    uart0_base = rt_ioremap(uart0_base, 4096);
#endif
    // register device
    serial = &serial0;
    uart = &uart0;

    serial->ops = &_uart_ops;
    serial->config = config;
    serial->config.baud_rate = UART_DEFAULT_BAUDRATE;
    uart->hw_base = (rt_ubase_t)uart0_base;
    uart->irqno = 0x0a;

    rt_hw_serial_register(serial,
                          RT_CONSOLE_DEVICE_NAME,
                          RT_DEVICE_FLAG_STREAM | RT_DEVICE_FLAG_RDWR | RT_DEVICE_FLAG_INT_RX,
                          uart);
    rt_hw_interrupt_install(uart->irqno, rt_hw_uart_isr, serial, RT_CONSOLE_DEVICE_NAME);
    rt_hw_interrupt_umask(uart->irqno);
    return 0;
}

/* WEAK for SDK 0.5.6 */
rt_weak void uart_debug_init(int uart_channel)
{
}
