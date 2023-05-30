/*
 * Copyright (c) 2006-2021, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2013-03-30     Bernard      the first verion
 */

#include <rthw.h>
#include <rtdevice.h>

#include "serial.h"

struct hw_uart_device
{
    rt_uint32_t hw_base;
    rt_uint32_t irqno;
};

#define UART_DR(base)   __REG32(base + 0x00)
#define UART_FR(base)   __REG32(base + 0x18)
#define UART_CR(base)   __REG32(base + 0x30)
#define UART_IMSC(base) __REG32(base + 0x38)
#define UART_ICR(base)  __REG32(base + 0x44)

#define UARTFR_RXFE     0x10
#define UARTFR_TXFF     0x20
#define UARTIMSC_RXIM   0x10
#define UARTIMSC_TXIM   0x20
#define UARTICR_RXIC    0x10
#define UARTICR_TXIC    0x20

static void rt_hw_uart_isr(int irqno, void *param)
{
    struct rt_serial_device *serial = (struct rt_serial_device *)param;

    rt_hw_serial_isr(serial, RT_SERIAL_EVENT_RX_IND);
}

static rt_err_t uart_configure(struct rt_serial_device *serial, struct serial_configure *cfg)
{
    return RT_EOK;
}

static rt_err_t uart_control(struct rt_serial_device *serial, int cmd, void *arg)
{
    struct hw_uart_device *uart;

    RT_ASSERT(serial != RT_NULL);
    uart = (struct hw_uart_device *)serial->parent.user_data;

    switch (cmd)
    {
    case RT_DEVICE_CTRL_CLR_INT:
        /* disable rx irq */
        UART_IMSC(uart->hw_base) &= ~UARTIMSC_RXIM;
        break;

    case RT_DEVICE_CTRL_SET_INT:
        /* enable rx irq */
        UART_IMSC(uart->hw_base) |= UARTIMSC_RXIM;
        rt_hw_interrupt_install(uart->irqno, rt_hw_uart_isr, serial, "uart");
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

    while (UART_FR(uart->hw_base) & UARTFR_TXFF);
    UART_DR(uart->hw_base) = c;

    return 1;
}

static int uart_getc(struct rt_serial_device *serial)
{
    int ch;
    struct hw_uart_device *uart;

    RT_ASSERT(serial != RT_NULL);
    uart = (struct hw_uart_device *)serial->parent.user_data;

    ch = -1;
    if (!(UART_FR(uart->hw_base) & UARTFR_RXFE))
    {
        ch = UART_DR(uart->hw_base) & 0xff;
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

#ifdef RT_USING_UART0
/* UART device driver structure */
static struct hw_uart_device _uart0_device =
{
    REALVIEW_UART0_BASE,
    IRQ_PBA8_UART0,
};
static struct rt_serial_device _serial0;
#endif

#ifdef RT_USING_UART1
/* UART1 device driver structure */
static struct hw_uart_device _uart1_device =
{
    REALVIEW_UART1_BASE,
    IRQ_PBA8_UART1,
};
static struct rt_serial_device _serial1;
#endif

int uart_isr_test(void)
{
    return uart_getc(&_serial1);
}

int rt_hw_uart_init(void)
{
    struct hw_uart_device *uart;
    struct serial_configure config;

    config.baud_rate = BAUD_RATE_115200;
    config.bit_order = BIT_ORDER_LSB;
    config.data_bits = DATA_BITS_8;
    config.parity    = PARITY_NONE;
    config.stop_bits = STOP_BITS_1;
    config.invert    = NRZ_NORMAL;
    config.bufsz     = RT_SERIAL_RB_BUFSZ;

#ifdef RT_USING_UART0
    uart = &_uart0_device;

    _serial0.ops    = &_uart_ops;
    _serial0.config = config;

    /* register UART1 device */
    rt_hw_serial_register(&_serial0, "uart0",
                          RT_DEVICE_FLAG_RDWR | RT_DEVICE_FLAG_INT_RX,
                          uart);
    /* enable Rx and Tx of UART */
    UART_CR(uart->hw_base) = (1 << 0) | (1 << 8) | (1 << 9);
#endif

#ifdef RT_USING_UART1
    uart = &_uart1_device;
    _serial1.ops = &_uart_ops;
    _serial1.config = config;

    /* register UART1 device */
    rt_hw_serial_register(&_serial1, "uart1",
                          RT_DEVICE_FLAG_RDWR | RT_DEVICE_FLAG_INT_RX, uart);
    /* enable Rx and Tx of UART */
    UART_CR(uart->hw_base) = (1 << 0) | (1 << 8) | (1 << 9);
#endif

    return 0;
}
INIT_BOARD_EXPORT(rt_hw_uart_init);
