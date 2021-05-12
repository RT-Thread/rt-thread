/*
 * Copyright (c) 2006-2021, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author         Notes
 * 2020-04-16     bigmagic       first version
 */

#include <rthw.h>
#include <rtthread.h>
#include <rtdevice.h>

#include "board.h"
#include "drv_uart.h"
#include "drv_gpio.h"

struct hw_uart_device
{
    rt_ubase_t hw_base;
    rt_uint32_t irqno;
};

static rt_err_t uart_configure(struct rt_serial_device *serial, struct serial_configure *cfg)
{
    struct hw_uart_device *uart;
    uint32_t bauddiv = (UART_REFERENCE_CLOCK / cfg->baud_rate)* 1000 / 16;
    uint32_t ibrd = bauddiv / 1000;

    RT_ASSERT(serial != RT_NULL);
    uart = (struct hw_uart_device *)serial->parent.user_data;
    if(uart->hw_base == PL011_BASE)
    {
        uint32_t gpfsel = 0;

        gpfsel &= ~((uint32_t)(0x07 << (4 * 3)));
        gpfsel |= (uint32_t)(ALT0 << (4 * 3));
        GPIO_REG_GPFSEL1(GPIO_BASE) = gpfsel;

        gpfsel &= ~((uint32_t)(0x07 << (5 * 3)));
        gpfsel |= (uint32_t)(ALT0 << (5 * 3));
        GPIO_REG_GPFSEL1(GPIO_BASE) = gpfsel;

        PL011_REG_CR(uart->hw_base) = 0;/*Clear UART setting*/
        PL011_REG_LCRH(uart->hw_base) = 0;/*disable FIFO*/
        PL011_REG_IBRD(uart->hw_base) = ibrd;
        PL011_REG_FBRD(uart->hw_base) = (((bauddiv - ibrd * 1000) * 64 + 500) / 1000);
        PL011_REG_LCRH(uart->hw_base) = PL011_LCRH_WLEN_8;/*FIFO*/
        PL011_REG_CR(uart->hw_base) = PL011_CR_UARTEN | PL011_CR_TXE | PL011_CR_RXE;/*art enable, TX/RX enable*/
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
        PL011_REG_IMSC(uart->hw_base) &= ~((uint32_t)PL011_IMSC_RXIM);
        rt_hw_interrupt_mask(uart->irqno);
        break;

    case RT_DEVICE_CTRL_SET_INT:
        /* enable rx irq */
        PL011_REG_IMSC(uart->hw_base) |= PL011_IMSC_RXIM;
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

    while ((PL011_REG_FR(uart->hw_base) & PL011_FR_TXFF));
    PL011_REG_DR(uart->hw_base) = (uint8_t)c;

    return 1;
}

static int uart_getc(struct rt_serial_device *serial)
{
    int ch = -1;
    struct hw_uart_device *uart;

    RT_ASSERT(serial != RT_NULL);
    uart = (struct hw_uart_device *)serial->parent.user_data;

    if((PL011_REG_FR(uart->hw_base) & PL011_FR_RXFE) == 0)
    {
        ch = PL011_REG_DR(uart->hw_base) & 0xff;
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
    PL011_REG_ICR(UART0_BASE) = PL011_INTERRUPT_RECEIVE;
}


/* UART device driver structure */
static struct hw_uart_device _uart0_device =
{
    PL011_BASE,
    IRQ_PL011,
};

static struct rt_serial_device _serial0;

int rt_hw_uart_init(void)
{
    struct hw_uart_device *uart;
    struct serial_configure config = RT_SERIAL_CONFIG_DEFAULT;

    uart = &_uart0_device;

    _serial0.ops    = &_uart_ops;
    _serial0.config = config;

    /* register UART1 device */
    rt_hw_serial_register(&_serial0, "uart",
                          RT_DEVICE_FLAG_RDWR | RT_DEVICE_FLAG_INT_RX,
                          uart);
    rt_hw_interrupt_install(uart->irqno, rt_hw_uart_isr, &_serial0, "uart");

    return 0;
}
