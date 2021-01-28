/*
 * Copyright (c) 2006-2018, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 */

#include <rthw.h>
#include <rtthread.h>
#include <rtdevice.h>
#include "board.h"
#include "drv_uart.h"

#include "hardware/uart.h"
#include "hardware/irq.h"

#define UART_ID uart0
#define BAUD_RATE 115200
#define DATA_BITS 8
#define STOP_BITS 1
#define PARITY    UART_PARITY_NONE

// We are using pins 0 and 1, but see the GPIO function select table in the
// datasheet for information on which other pins can be used.
#define UART_TX_PIN 0
#define UART_RX_PIN 1

#define PICO_UART_DEVICE(uart)    (struct pico_uart_dev *)(uart)

static struct pico_uart_dev uart0_dev;

struct pico_uart_dev
{
    struct rt_serial_device parent;
    rt_uint32_t uart_periph;
    rt_uint32_t irqno;
};

void pico_uart_isr(void)
{
    rt_interrupt_enter();
    /* read interrupt status and clear it */
    if (uart_is_readable(uart0)) /* rx ind */
    {
        rt_hw_serial_isr(&uart0_dev.parent, RT_SERIAL_EVENT_RX_IND);
    }

    rt_interrupt_leave();
}

/*
 * UART interface
 */
static rt_err_t pico_uart_configure(struct rt_serial_device *serial, struct serial_configure *cfg)
{
    return RT_EOK;
}

static rt_err_t pico_uart_control(struct rt_serial_device *serial, int cmd, void *arg)
{
    return RT_EOK;
}

static int pico_uart_putc(struct rt_serial_device *serial, char c)
{
    uart_putc_raw(uart0, c);

    return 1;
}

static int pico_uart_getc(struct rt_serial_device *serial)
{
    int ch;

    if (uart_is_readable(uart0))
    {
        ch = uart_get_hw(uart0)->dr;
    }
    else
    {
        ch =-1;
    }

    return ch;
}

const static struct rt_uart_ops _uart_ops =
{
    pico_uart_configure,
    pico_uart_control,
    pico_uart_putc,
    pico_uart_getc,
    RT_NULL,
};

/*
 * UART Initiation
 */
int rt_hw_uart_init(void)
{
    rt_err_t ret = RT_EOK;

    struct serial_configure config = RT_SERIAL_CONFIG_DEFAULT;

    uart_init(UART_ID, 115200);

    // Set the TX and RX pins by using the function select on the GPIO
    // Set datasheet for more information on function select
    gpio_set_function(UART_TX_PIN, GPIO_FUNC_UART);
    gpio_set_function(UART_RX_PIN, GPIO_FUNC_UART);

    // Actually, we want a different speed
    // The call will return the actual baud rate selected, which will be as close as
    // possible to that requested
    uart_set_baudrate(UART_ID, BAUD_RATE);

    // Set UART flow control CTS/RTS, we don't want these, so turn them off
    uart_set_hw_flow(UART_ID, false, false);

    // Set our data format
    uart_set_format(UART_ID, DATA_BITS, STOP_BITS, PARITY);

    // Turn off FIFO's - we want to do this character by character
    uart_set_fifo_enabled(UART_ID, false);

    // Set up a RX interrupt
    // We need to set up the handler first
    // Select correct interrupt for the UART we are using
    int UART_IRQ = UART_ID == uart0 ? UART0_IRQ : UART1_IRQ;

    // And set up and enable the interrupt handlers
    irq_set_exclusive_handler(UART_IRQ, pico_uart_isr);
    irq_set_enabled(UART_IRQ, true);

    // Now enable the UART to send interrupts - RX only
    uart_set_irq_enables(UART_ID, true, false);

    uart0_dev.parent.ops = &_uart_ops;
    uart0_dev.parent.config = config;

    ret = rt_hw_serial_register(&uart0_dev.parent,
                                "uart0",
                                RT_DEVICE_FLAG_RDWR | RT_DEVICE_FLAG_INT_RX,
                                &uart0_dev);

    return ret;
}
// INIT_DEVICE_EXPORT(rt_hw_uart_init);
