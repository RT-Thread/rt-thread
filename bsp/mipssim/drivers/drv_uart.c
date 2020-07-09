/*
 * Copyright (c) 2006-2019, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2019-12-04     Jiaxun Yang  Initial version
 */

/**
 * @addtogroup mipssim
 */

/*@{*/

#include <rtthread.h>
#include <rtdevice.h>
#include <rthw.h>
#include "drv_uart.h"

#define TRUE 1
#define FALSE 0

struct rt_uart_mipssim
{
    void *base;
    rt_uint32_t IRQ;
};

static rt_err_t mipssim_uart_configure(struct rt_serial_device *serial, struct serial_configure *cfg)
{
    struct rt_uart_mipssim *uart_dev = RT_NULL;

    RT_ASSERT(serial != RT_NULL);
    RT_ASSERT(cfg != RT_NULL);

    uart_dev = (struct rt_uart_mipssim *)serial->parent.user_data;

    UART_IER(uart_dev->base) = 0; /* clear interrupt */
    UART_FCR(uart_dev->base) = 0xc1; /* reset UART Rx/Tx */
    /* set databits, stopbits and parity. (8-bit data, 1 stopbit, no parity) */
    UART_LCR(uart_dev->base) = 0x3;
    UART_MCR(uart_dev->base) = 0x3;
    UART_LSR(uart_dev->base) = 0x60;
    UART_MSR(uart_dev->base) = 0xb0;

    return RT_EOK;
}

static rt_err_t mipssim_uart_control(struct rt_serial_device *serial, int cmd, void *arg)
{
    struct rt_uart_mipssim *uart_dev = RT_NULL;

    RT_ASSERT(serial != RT_NULL);
    uart_dev = (struct rt_uart_mipssim *)serial->parent.user_data;

    switch (cmd)
    {
    case RT_DEVICE_CTRL_CLR_INT: /* Disable RX IRQ */
        rt_hw_interrupt_mask(uart_dev->IRQ);
        break;

    case RT_DEVICE_CTRL_SET_INT: /* Enable RX IRQ */
        rt_hw_interrupt_umask(uart_dev->IRQ);
        UART_IER(uart_dev->base) |= (IER_IRxE|IER_ILE);
        break;

    default:
        break;
    }

    return RT_EOK;

}

static rt_bool_t uart_is_transmit_empty(struct rt_uart_mipssim *uart_dev)
{
    unsigned char status = UART_LSR(uart_dev->base);

    if (status & (UARTLSR_TE | UARTLSR_TFE))
    {
        return TRUE;
    }
    else
    {
        return FALSE;
    }
}

static int mipssim_uart_putc(struct rt_serial_device *serial, char c)
{
    struct rt_uart_mipssim *uart_dev = RT_NULL;

    RT_ASSERT(serial != RT_NULL);

    uart_dev = (struct rt_uart_mipssim *)serial->parent.user_data;

    while (FALSE == uart_is_transmit_empty(uart_dev))
        ;

    UART_DAT(uart_dev->base) = c;

    return 1;
}

static int mipssim_uart_getc(struct rt_serial_device *serial)
{
    struct rt_uart_mipssim *uart_dev = RT_NULL;

    RT_ASSERT(serial != RT_NULL);

    uart_dev = (struct rt_uart_mipssim *)serial->parent.user_data;

    if (LSR_RXRDY & UART_LSR(uart_dev->base))
    {
        return UART_DAT(uart_dev->base);
    }

    return -1;
}

/* UART interrupt handler */
static void uart_irq_handler(int vector, void *param)
{
    struct rt_serial_device *serial = (struct rt_serial_device *)param;
    struct rt_uart_mipssim *uart_dev = RT_NULL;

    RT_ASSERT(serial != RT_NULL);

    uart_dev = (struct rt_uart_mipssim *)serial->parent.user_data;
    unsigned char iir = UART_IIR(uart_dev->base);

    /* Find out interrupt reason */
    if ((IIR_RXTOUT & iir) || (IIR_RXRDY & iir))
    {
        rt_interrupt_enter();
        rt_hw_serial_isr(serial, RT_SERIAL_EVENT_RX_IND);
        rt_interrupt_leave();
    }

}

static const struct rt_uart_ops mipssim_uart_ops =
{
    mipssim_uart_configure,
    mipssim_uart_control,
    mipssim_uart_putc,
    mipssim_uart_getc,
};

struct rt_uart_mipssim uart_dev0 =
{
    (void *)UART0_BASE,
    4,
};
struct rt_serial_device serial;


void rt_hw_uart_init(void)
{
    struct rt_uart_mipssim *uart;
    struct serial_configure config = RT_SERIAL_CONFIG_DEFAULT;

    uart = &uart_dev0;

    serial.ops    = &mipssim_uart_ops;
    serial.config = config;

    rt_hw_interrupt_install(uart->IRQ, uart_irq_handler, &serial, "UART");

    /* register UART device */
    rt_hw_serial_register(&serial,
                          "uart",
                          RT_DEVICE_FLAG_RDWR | RT_DEVICE_FLAG_INT_RX,
                          uart);
}
/*@}*/
