/*
 * Copyright (c) 2020, Shenzhen Academy of Aerospace Technology
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2020-10-16     Dystopia     the first version
 */

#include <rthw.h>
#include <rtthread.h>
#include <rtdevice.h>

#include <board.h>
#include <interrupt.h>
#include "uart.h"
#include "uart_reg.h"

struct bm3803_uart
{
    void *uart_base;
    int irq;
};

static void bm3803_uart_isr(int tt, void *param)
{
    struct bm3803_uart *uart;
    struct rt_serial_device *serial;
    struct uart_reg *uart_base;

    serial = (struct rt_serial_device *)param;
    uart = (struct bm3803_uart *)serial->parent.user_data;
    uart_base = uart->uart_base;

    if (uart_base->uartstatus & 0x1)
    {
        rt_hw_serial_isr(serial, RT_SERIAL_EVENT_RX_IND);
    }
}

#define NOT_IMPLEMENTED() RT_ASSERT(0)

static rt_err_t bm3803_configure(struct rt_serial_device *serial, struct serial_configure *cfg)
{
    struct bm3803_uart *uart;
    struct uart_reg *uart_base;

    RT_ASSERT(serial != RT_NULL);
    uart = (struct bm3803_uart *)serial->parent.user_data;
    RT_ASSERT(uart);
    uart_base = uart->uart_base;

    if (cfg->baud_rate == BAUD_RATE_115200)
    {
        uart_base->uartscaler = ((((CPU_FREQ * 10) / (8 * 115200)) - 5) / 10);
    }
    else if (cfg->baud_rate == BAUD_RATE_9600)
    {
        uart_base->uartscaler = ((((CPU_FREQ * 10) / (8 * 9600)) - 5) / 10);
    }
    else
    {
        NOT_IMPLEMENTED();
    }

    uart_base->uartctrl |= 0x3;

    return RT_EOK;
}

static rt_err_t bm3803_control(struct rt_serial_device *serial, int cmd, void *arg)
{
    struct bm3803_uart *uart;

    RT_ASSERT(serial != RT_NULL);
    uart = (struct bm3803_uart *)serial->parent.user_data;

    switch (cmd)
    {
    case RT_DEVICE_CTRL_CLR_INT:
        /* disable rx irq */
        rt_hw_interrupt_mask(uart->irq);
        break;
    case RT_DEVICE_CTRL_SET_INT:
        /* enable rx irq */
        rt_hw_interrupt_umask(uart->irq);
        break;
    }

    return RT_EOK;
}

static int bm3803_putc(struct rt_serial_device *serial, char c)
{
    struct bm3803_uart *uart;
    struct uart_reg *uart_base;

    RT_ASSERT(serial != RT_NULL);
    uart = (struct bm3803_uart *)serial->parent.user_data;
    uart_base = uart->uart_base;

    while (!(uart_base->uartstatus & 0x4));
    uart_base->uartdata = c;

    return 1;
}

static int bm3803_getc(struct rt_serial_device *serial)
{
    int ch;
    struct bm3803_uart *uart;
    struct uart_reg *uart_base;

    RT_ASSERT(serial != RT_NULL);
    uart = (struct bm3803_uart *)serial->parent.user_data;
    uart_base = uart->uart_base;

    ch = -1;
    if (uart_base->uartstatus & 0x1)
    {
        ch = uart_base->uartdata;
    }

    return ch;
}

static const struct rt_uart_ops bm3803_uart_ops =
{
    bm3803_configure,
    bm3803_control,
    bm3803_putc,
    bm3803_getc,
};

/* UART device driver structure */
#ifdef RT_USING_UART1
struct bm3803_uart uart1 =
{
    (void *)UART1_BASE,
    UART1_TT,
};
struct rt_serial_device serial1;
#endif

int rt_hw_serial_init(void)
{
    struct serial_configure config = RT_SERIAL_CONFIG_DEFAULT;

#ifdef RT_USING_UART1
    volatile struct lregs *regs = (struct lregs *)PREGS;
    serial1.ops = &bm3803_uart_ops;
    serial1.config = config;
    /* configure gpio direction */
    regs->piodir |= (1 << 15);
    regs->piodir &= ~(1 << 14);
    /* enable RX interrupt */
    regs->uartctrl1 = 0;
    regs->uartctrl1 |= 0x4;
    /* install ISR */
    rt_hw_interrupt_install(uart1.irq, bm3803_uart_isr, &serial1, "uart1");
    rt_hw_interrupt_mask(uart1.irq);
    /* register UART1 device */
    rt_hw_serial_register(&serial1, "uart1",
                          RT_DEVICE_FLAG_RDWR | RT_DEVICE_FLAG_INT_RX,
                          &uart1);
#endif
    return 0;
}
INIT_BOARD_EXPORT(rt_hw_serial_init);
