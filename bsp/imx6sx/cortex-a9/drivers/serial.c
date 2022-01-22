/*
 * COPYRIGHT (C) 2018, Real-Thread Information Technology Ltd
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2013-03-30     Bernard      the first verion
 */

#include <rthw.h>
#include <registers/regsuart.h>
#include <uart/imx_uart.h>

#include <rtdevice.h>

#include "serial.h"

struct hw_uart_device
{
    uint32_t instance;
    int irqno;
};

static void rt_hw_uart_isr(int irqno, void *param)
{
    struct rt_serial_device *serial = (struct rt_serial_device *)param;

    rt_hw_serial_isr(serial, RT_SERIAL_EVENT_RX_IND);
}

static rt_err_t uart_configure(struct rt_serial_device *serial, struct serial_configure *cfg)
{
    struct hw_uart_device *uart;
    uint32_t baudrate;
    uint8_t parity, stopbits, datasize, flowcontrol;

    RT_ASSERT(serial != RT_NULL);
    uart = (struct hw_uart_device *)serial->parent.user_data;

    baudrate = cfg->baud_rate;
    switch (cfg->data_bits)
    {
    case DATA_BITS_8:
        datasize = EIGHTBITS;
        break;
    case DATA_BITS_7:
        datasize = SEVENBITS;
        break;
    }
    if (cfg->stop_bits == STOP_BITS_1) stopbits = STOPBITS_ONE;
    else if (cfg->stop_bits == STOP_BITS_2) stopbits = STOPBITS_TWO;

    parity = PARITY_NONE;
    flowcontrol = FLOWCTRL_OFF;

    /* initailize UART */
    // uart_init(uart->instance, baudrate, parity, stopbits, datasize, flowcontrol);

    rt_hw_interrupt_install(uart->irqno, rt_hw_uart_isr, serial, "uart");
    rt_hw_interrupt_mask(uart->irqno);

    /* Set the IRQ mode for the Rx FIFO */
    uart_set_FIFO_mode(uart->instance, RX_FIFO, 1, IRQ_MODE);

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
        rt_hw_interrupt_mask(uart->irqno);
        break;

    case RT_DEVICE_CTRL_SET_INT:
        /* enable rx irq */
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

    uart_putchar(uart->instance, (uint8_t*)&c);

    return 1;
}

static int uart_getc(struct rt_serial_device *serial)
{
    int ch;
    struct hw_uart_device *uart;

    RT_ASSERT(serial != RT_NULL);
    uart = (struct hw_uart_device *)serial->parent.user_data;

    ch = uart_getchar(uart->instance);
    if (ch == NONE_CHAR) ch = -1;

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
    HW_UART0,
    IMX_INT_UART0
};
static struct rt_serial_device _serial0;
#endif

#ifdef RT_USING_UART1
/* UART1 device driver structure */
static struct hw_uart_device _uart1_device =
{
    HW_UART1,
    IMX_INT_UART1
};
static struct rt_serial_device _serial1;
#endif

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
#endif

#ifdef RT_USING_UART1
    uart = &_uart1_device;
    _serial1.ops = &_uart_ops;
    _serial1.config = config;

    /* register UART1 device */
    rt_hw_serial_register(&_serial1, "uart1",
                          RT_DEVICE_FLAG_RDWR | RT_DEVICE_FLAG_INT_RX, uart);
#endif

    return 0;
}
INIT_BOARD_EXPORT(rt_hw_uart_init);
