/*
 * Copyright (c) 2006-2021, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2018/5/5       Bernard      The first version
 */

#include <rthw.h>
#include <rtthread.h>
#include <rtdevice.h>

#include "board.h"

#define PL011_UARTDR            0x000
#define PL011_UARTFR            0x018
#define PL011_UARTFR_TXFF_BIT   5

unsigned int readl(volatile void *addr)
{
    return *(volatile unsigned int *)addr;
}

void writel(unsigned int v, volatile void *addr)
{
    *(volatile unsigned int *)addr = v;
}

struct hw_uart_device
{
    rt_ubase_t hw_base;
    rt_uint32_t irqno;
};

static rt_err_t uart_configure(struct rt_serial_device *serial, struct serial_configure *cfg)
{
    return RT_EOK;
}

static rt_err_t uart_control(struct rt_serial_device *serial, int cmd, void *arg)
{
    struct hw_uart_device *uart;
    uint32_t val;

    RT_ASSERT(serial != RT_NULL);
    uart = (struct hw_uart_device *)serial->parent.user_data;

    switch (cmd)
    {
        case RT_DEVICE_CTRL_CLR_INT:
            /* disable rx irq */
            val = readl((volatile void *)(uart->hw_base + 0x38));
            val &= ~0x10;
            writel(val, (volatile void *)(uart->hw_base + 0x38));
            rt_hw_interrupt_mask(uart->irqno);
            break;

        case RT_DEVICE_CTRL_SET_INT:
            /* enable rx irq */
            val = readl((volatile void *)(uart->hw_base + 0x38));
            val |= 0x10;
            writel(val, (volatile void *)(uart->hw_base + 0x38));
            rt_hw_interrupt_umask(uart->irqno);
            break;
    }

    return RT_EOK;
}

static int uart_putc(struct rt_serial_device *serial, char c)
{
    struct hw_uart_device *uart;

    RT_ASSERT(serial != RT_NULL);
    uart = (struct hw_uart_device *)serial->parent.user_data;

    while (readl((volatile void *)(uart->hw_base + PL011_UARTFR)) & (1 << PL011_UARTFR_TXFF_BIT))
    {
    }

    writel(c, (volatile void *)( uart->hw_base + PL011_UARTDR));

    return 1;
}

static int uart_getc(struct rt_serial_device *serial)
{
    int ch = -1;
    struct hw_uart_device *uart;

    RT_ASSERT(serial != RT_NULL);
    uart = (struct hw_uart_device *)serial->parent.user_data;

    if (!(readl((volatile void *)(uart->hw_base + 0x18)) & (1 << 4)))
    {
        ch = readl((volatile void *)(uart->hw_base));
    }

    return ch;
}

static const struct rt_uart_ops _uart_ops =
{
    uart_configure,
    uart_control,
    uart_putc,
    uart_getc,
};

static void rt_hw_uart_isr(int irqno, void *param)
{
    struct rt_serial_device *serial = (struct rt_serial_device*)param;
    rt_hw_serial_isr(serial, RT_SERIAL_EVENT_RX_IND);
}

#ifdef RT_USING_UART0
/* UART device driver structure */
static struct hw_uart_device _uart0_device =
{
    PL011_UART0_BASE,
    PL011_UART0_IRQNUM,
};
static struct rt_serial_device _serial0;
#endif

int rt_hw_uart_init(void)
{
    struct hw_uart_device *uart;
    struct serial_configure config = RT_SERIAL_CONFIG_DEFAULT;

#ifdef RT_USING_UART0
    uart = &_uart0_device;

    _serial0.ops    = &_uart_ops;
    _serial0.config = config;

    /* register UART1 device */
    rt_hw_serial_register(&_serial0, "uart0",
            RT_DEVICE_FLAG_RDWR | RT_DEVICE_FLAG_INT_RX,
            uart);
    rt_hw_interrupt_install(uart->irqno, rt_hw_uart_isr, &_serial0, "uart0");
#endif

    return 0;
}
