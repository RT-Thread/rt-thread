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
#include "drv_uart.h"

#include <rtdevice.h>

#define AUX_BASE            (0x3F000000 + 0x215000)

struct hw_uart_device
{
    rt_uint32_t hw_base;
    rt_uint32_t irqno;
};

static rt_err_t uart_configure(struct rt_serial_device *serial, struct serial_configure *cfg)
{
    struct hw_uart_device *uart;

    RT_ASSERT(serial != RT_NULL);
    uart = (struct hw_uart_device *)serial->parent.user_data;

    if (uart->hw_base == AUX_BASE)
    {
        rt_uint32_t value;

        /* GPIO function set */
        value = BCM283X_GPIO_GPFSEL(1);
        value &= ~(7 << 12); /* GPIO14 */
        value |= 2 << 12 ; /* ALT5 */
        value &= ~(7 << 15); /* GPIO15 */
        value |= 2 << 15 ; /* ALT5 */
        BCM283X_GPIO_GPFSEL(1) = value;

        BCM283X_GPIO_GPPUD = 0;
        BCM283X_GPIO_GPPUDCLK(0) = (1 << 14) | (1 << 15);
        BCM283X_GPIO_GPPUDCLK(0) = 0;

        AUX_ENABLES(uart->hw_base)      = 1;    /* Enable UART1 */
        AUX_MU_IER_REG(uart->hw_base)   = 0;    /* Disable interrupt */
        AUX_MU_CNTL_REG(uart->hw_base)  = 0;    /* Disable Transmitter and Receiver */
        AUX_MU_LCR_REG(uart->hw_base)   = 3;    /* Works in 8-bit mode */
        AUX_MU_MCR_REG(uart->hw_base)   = 0;    /* Disable RTS */
        AUX_MU_IIR_REG(uart->hw_base)   = 0xC6; /* Enable FIFO, Clear FIFO */
        AUX_MU_BAUD_REG(uart->hw_base)  = 270;  /* 115200 = system clock 250MHz / (8 * (baud + 1)), baud = 270 */
        AUX_MU_CNTL_REG(uart->hw_base)  = 3;    /* Enable Transmitter and Receiver */
    }

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
        AUX_MU_IER_REG(uart->hw_base) = 0x0;
        rt_hw_interrupt_mask(uart->irqno);
        break;

    case RT_DEVICE_CTRL_SET_INT:
        /* enable rx irq */
        AUX_MU_IER_REG(uart->hw_base) = 0x1;
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

    while (!(AUX_MU_LSR_REG(uart->hw_base) & 0x20));
    AUX_MU_IO_REG(uart->hw_base) = c;

    return 1;
}

static int uart_getc(struct rt_serial_device *serial)
{
    int ch = -1;
    struct hw_uart_device *uart;

    RT_ASSERT(serial != RT_NULL);
    uart = (struct hw_uart_device *)serial->parent.user_data;

    if ((AUX_MU_LSR_REG(uart->hw_base) & 0x01))
    {
        ch = AUX_MU_IO_REG(uart->hw_base) & 0xff;
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
    RPI_UART0_BASE,
    IRQ_PBA8_UART0,
};
static struct rt_serial_device _serial0;
#endif

#ifdef RT_USING_UART1
/* UART1 device driver structure */
static struct hw_uart_device _uart1_device =
{
    AUX_BASE,
    IRQ_AUX,
};
static struct rt_serial_device _serial1;
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

#ifdef RT_USING_UART1
    uart = &_uart1_device;
    _serial1.ops = &_uart_ops;
    _serial1.config = config;

    /* register UART1 device */
    rt_hw_serial_register(&_serial1, "uart1",
                          RT_DEVICE_FLAG_RDWR | RT_DEVICE_FLAG_INT_RX, uart);
    /* enable Rx and Tx of UART */
    rt_hw_interrupt_install(uart->irqno, rt_hw_uart_isr, &_serial1, "uart1");
#endif

    return 0;
}
