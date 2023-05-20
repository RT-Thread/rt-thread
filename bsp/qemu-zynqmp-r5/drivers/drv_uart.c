/*
 * Copyright (c) 2023, lepustse@gmail.com
 *
 * License-Identifier: MIT
 *
 * Change Logs:
 * Date         Author		Notes
 * 2023-05-03   lepustse	the first version
 */

#include <rthw.h>
#include <rtdevice.h>
#include "drv_uart.h"
#include "interrupt.h"

struct hw_uart_device
{
    rt_uint32_t hw_base;
    rt_uint32_t irqno;
};

static void rt_hw_uart_isr(int irqno, void *param)
{
    struct rt_serial_device *serial = (struct rt_serial_device *)param;

    rt_hw_serial_isr(serial, RT_SERIAL_EVENT_RX_IND);
}

static rt_err_t uart_configure(struct rt_serial_device *serial, struct serial_configure *cfg)
{
    struct hw_uart_device *uart;

    RT_ASSERT(serial != RT_NULL);
    uart = (struct hw_uart_device *)serial->parent.user_data;

    UART_RX_TRIG_LVL(uart->hw_base) = 1;

    return RT_EOK;
}

extern rt_uint32_t rt_interrupt_to_thread;
static rt_err_t uart_control(struct rt_serial_device *serial, int cmd, void *param)
{

    struct hw_uart_device *uart;

    RT_ASSERT(serial != RT_NULL);
    uart = (struct hw_uart_device *)serial->parent.user_data;

    switch (cmd)
    {
    case RT_DEVICE_CTRL_CLR_INT:
        /* disable rx irq */
        UART_IDR(uart->hw_base) |= UART_IXR_DIS_MASK;
        break;

    case RT_DEVICE_CTRL_SET_INT:
        /* enable rx irq */
        UART_IER(uart->hw_base) |= (UART_IXR_RX_TRIG);
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

    while (UART_SR(uart->hw_base) & UART_SR_TXFULL);
    UART_FIFO(uart->hw_base) = c;

    return 1;
}

static int uart_getc(struct rt_serial_device *serial)
{
    int ch;
    struct hw_uart_device *uart;

    RT_ASSERT(serial != RT_NULL);
    uart = (struct hw_uart_device *)serial->parent.user_data;

    ch = -1;
    if (UART_ISR(uart->hw_base) & UART_IXR_RX_TRIG) {
        ch = UART_FIFO(uart->hw_base) & 0xff;
        UART_ISR(uart->hw_base) = (UART_IXR_RX_TRIG);
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


#ifdef BSP_USING_UART0
static struct hw_uart_device _uart0_device =
{
    ZYNQMP_UART0_BASE,
    IRQ_UART_0,
};
static struct rt_serial_device _serial0;
#endif

int rt_hw_uart_init(void)
{
    struct hw_uart_device *uart;
    struct serial_configure config = RT_SERIAL_CONFIG_DEFAULT;
#ifdef BSP_USING_UART0
    uart = &_uart0_device;

    _serial0.ops    = &_uart_ops;
    _serial0.config = config;

    /* register UART0 device */
    rt_hw_serial_register(&_serial0, "uart0", RT_DEVICE_FLAG_RDWR | RT_DEVICE_FLAG_INT_RX, uart);

    /* about gic */
    rt_hw_interrupt_install(uart->irqno, rt_hw_uart_isr, &_serial0, "uart0");

    /* enable Rx and Tx of UART */
    UART_CR(uart->hw_base) &= ~UART_CR_EN_DIS_MASK;
    UART_CR(uart->hw_base) |= (UART_CR_RX_EN | UART_CR_TX_EN);
#endif

    return 0;
}
INIT_BOARD_EXPORT(rt_hw_uart_init);
