/*
 * Copyright (c) 2006-2018, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2023-09-26     1ridic       Integrate with RT-Thread driver framework.
 */

#include <rtdevice.h>
#include <drv_uart.h>
#include <hardware/gpio.h>

#ifdef RT_USING_SERIAL

#include "hardware/uart.h"
#include "hardware/irq.h"

#if !defined(BSP_USING_UART0) && !defined(BSP_USING_UART1)
    #error "Please define at least one BSP_USING_UARTx"
    /* this driver can be disabled at menuconfig -> RT-Thread Components -> Device Drivers */
#endif

#ifdef BSP_USING_UART0
    void pico_uart0_isr(void);
#endif
#ifdef BSP_USING_UART1
    void pico_uart1_isr(void);
#endif

struct pico_uart_dev
{
    rt_serial_t parent;
    uart_inst_t *instance;
    rt_uint32_t irqno;
    rt_uint32_t tx_pin;
    rt_uint32_t rx_pin;
    void (*uart_isr)(void);
};

static struct pico_uart_dev uart_dev[] =
{
#ifdef BSP_USING_UART0
    {
        .instance = uart0,
        .irqno = UART0_IRQ,
        .tx_pin = BSP_UART0_TX_PIN,
        .rx_pin = BSP_UART0_RX_PIN,
        .uart_isr = pico_uart0_isr,
    },
#endif
#ifdef BSP_USING_UART1
    {
        .instance = uart1,
        .irqno = UART1_IRQ,
        .tx_pin = BSP_UART1_TX_PIN,
        .rx_pin = BSP_UART1_RX_PIN,
        .uart_isr = pico_uart1_isr,
    },
#endif
};

enum
{
#ifdef BSP_USING_UART0
    UART0_INDEX,
#endif
#ifdef BSP_USING_UART1
    UART1_INDEX,
#endif
};

#ifdef BSP_USING_UART0
void pico_uart0_isr(void)
{
    rt_interrupt_enter();
    /* read interrupt status and clear it */
    if (uart_is_readable(uart0)) /* rx ind */
    {
        rt_hw_serial_isr(&uart_dev[UART0_INDEX].parent, RT_SERIAL_EVENT_RX_IND);
    }

    rt_interrupt_leave();
}
#endif
#ifdef BSP_USING_UART1
void pico_uart1_isr(void)
{
    rt_interrupt_enter();
    /* read interrupt status and clear it */
    if (uart_is_readable(uart1)) /* rx ind */
    {
        rt_hw_serial_isr(&uart_dev[UART1_INDEX].parent, RT_SERIAL_EVENT_RX_IND);
    }

    rt_interrupt_leave();
}
#endif

/*
 * UART interface
 */
static rt_err_t pico_uart_configure(struct rt_serial_device *serial, struct serial_configure *cfg)
{
    struct pico_uart_dev *uart = RT_NULL;
    RT_ASSERT(serial != RT_NULL);
    RT_ASSERT(cfg != RT_NULL);
    uart = rt_container_of(serial, struct pico_uart_dev, parent);

    uart_init(uart->instance, cfg->baud_rate);

    // Set the TX and RX pins by using the function select on the GPIO
    // Set datasheet for more information on function select
    gpio_set_function(uart->rx_pin, GPIO_FUNC_UART);
    gpio_set_function(uart->tx_pin, GPIO_FUNC_UART);

    // Set UART flow control CTS/RTS
    if (cfg->flowcontrol == RT_SERIAL_FLOWCONTROL_CTSRTS)
        uart_set_hw_flow(uart->instance, true, true);
    else
        uart_set_hw_flow(uart->instance, false, false);

    // Set our data format
    uart_parity_t uart_parity = UART_PARITY_NONE;
    if (cfg->parity == PARITY_ODD)
        uart_parity = UART_PARITY_ODD;
    else if (cfg->parity == PARITY_EVEN)
        uart_parity = UART_PARITY_EVEN;
    uart_set_format(uart->instance, cfg->data_bits, cfg->stop_bits, uart_parity);

    // Turn off FIFO's - we want to do this character by character
    uart_set_fifo_enabled(uart->instance, false);

    return RT_EOK;
}

static rt_err_t pico_uart_control(struct rt_serial_device *serial, int cmd, void *arg)
{
    struct pico_uart_dev *uart = RT_NULL;
    RT_ASSERT(serial != RT_NULL);
    uart = rt_container_of(serial, struct pico_uart_dev, parent);

    switch (cmd)
    {
    /* enable interrupt */
    case RT_DEVICE_CTRL_SET_INT:
        // Set up a RX interrupt
        // We need to set up the handler first
        // And set up and enable the interrupt handlers
        irq_set_exclusive_handler(uart->irqno, uart->uart_isr);
        irq_set_enabled(uart->irqno, true);

        // Now enable the UART to send interrupts - RX only
        uart_set_irq_enables(uart->instance, true, false);
        break;
    }
    return RT_EOK;
}

static int pico_uart_putc(struct rt_serial_device *serial, char c)
{
    struct pico_uart_dev *uart = RT_NULL;
    RT_ASSERT(serial != RT_NULL);
    uart = rt_container_of(serial, struct pico_uart_dev, parent);
    uart_putc_raw(uart->instance, c);

    return 1;
}

static int pico_uart_getc(struct rt_serial_device *serial)
{
    struct pico_uart_dev *uart = RT_NULL;
    RT_ASSERT(serial != RT_NULL);
    uart = rt_container_of(serial, struct pico_uart_dev, parent);

    int ch;

    if (uart_is_readable(uart->instance))
    {
        ch = uart_get_hw(uart->instance)->dr;
    }
    else
    {
        ch = -1;
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

#ifdef BSP_USING_UART0
    uart_dev[UART0_INDEX].parent.ops = &_uart_ops;
    uart_dev[UART0_INDEX].parent.config = config;

    ret = rt_hw_serial_register(&uart_dev[UART0_INDEX].parent,
                                "uart0",
                                RT_DEVICE_FLAG_RDWR | RT_DEVICE_FLAG_INT_RX,
                                &uart_dev[UART0_INDEX]);
    RT_ASSERT(ret == RT_EOK);
#endif

#ifdef BSP_USING_UART1
    uart_dev[UART1_INDEX].parent.ops = &_uart_ops;
    uart_dev[UART1_INDEX].parent.config = config;

    ret = rt_hw_serial_register(&uart_dev[UART1_INDEX].parent,
                                "uart1",
                                RT_DEVICE_FLAG_RDWR | RT_DEVICE_FLAG_INT_RX,
                                &uart_dev[UART1_INDEX]);
    RT_ASSERT(ret == RT_EOK);
#endif

    return ret;
}


#endif /* RT_USING_SERIAL */
