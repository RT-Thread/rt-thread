/*
 * Copyright (c) 2006-2023, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author          Notes
 * 2009-02-05     Bernard         first version
 * 2009-10-25     Bernard         fix rt_serial_read bug when there is no data
 *                                in the buffer.
 * 2010-03-29     Bernard         cleanup code.
 * 2010-03-30     Kyle            Ported from STM32 to AVR32.
 * 2023-10-25     Raman Gopalan   UART driver for at32uc3a: Initial version
 * 2023-11-06     Raman Gopalan   Driver abstractions for uc3a and uc3b devices
 */

#include <rthw.h>
#include <rtthread.h>
#include <rtdevice.h>
#include "drv_uart.h"

#ifdef RT_USING_SERIAL

#include "compiler.h"
#include "usart.h"
#include "gpio.h"
#include "intc.h"

#if !defined(BSP_USING_UART0) && !defined(BSP_USING_UART1)
    #error "Please define at least one BSP_USING_UARTx"
    /* this driver can be disabled at menuconfig -> RT-Thread Components -> Device Drivers */
#endif

#ifdef BSP_USING_UART0
    void avr32uc3_uart0_isr(void);
#endif

#ifdef BSP_USING_UART1
    void avr32uc3_uart1_isr(void);
#endif

#ifdef BSP_USING_UART2
    void avr32uc3_uart2_isr(void);
#endif

/* AVR32UC3B uart driver */
struct avr32uc3_uart_dev
{
    rt_serial_t parent;
    avr32_usart_t *instance;
    rt_uint32_t irqno;
    rt_uint32_t irq_level;
    rt_uint32_t tx_pin;
    rt_uint32_t tx_pin_function;
    rt_uint32_t rx_pin;
    rt_uint32_t rx_pin_function;
    void (*uart_isr)(void);
};

static struct avr32uc3_uart_dev uart_dev[] =
{
#ifdef BSP_USING_UART0
    {
        .instance = (avr32_usart_t *)&AVR32_USART0,
        .irqno = AVR32_USART0_IRQ,
        .irq_level = AVR32_INTC_INT0,
        .tx_pin = BSP_UART0_TX_PIN,
        .tx_pin_function = BSP_UART0_TX_PIN_FUNCTION,
        .rx_pin = BSP_UART0_RX_PIN,
        .rx_pin_function = BSP_UART0_RX_PIN_FUNCTION,
        .uart_isr = avr32uc3_uart0_isr,
    },
#endif

#ifdef BSP_USING_UART1
    {
        .instance = (avr32_usart_t *)&AVR32_USART1,
        .irqno = AVR32_USART1_IRQ,
        .irq_level = AVR32_INTC_INT0,
        .tx_pin = BSP_UART1_TX_PIN,
        .tx_pin_function = BSP_UART1_TX_PIN_FUNCTION,
        .rx_pin = BSP_UART1_RX_PIN,
        .rx_pin_function = BSP_UART1_RX_PIN_FUNCTION,
        .uart_isr = avr32uc3_uart1_isr,
    },
#endif

#ifdef BSP_USING_UART2
    {
        .instance = (avr32_usart_t *)&AVR32_USART2,
        .irqno = AVR32_USART2_IRQ,
        .irq_level = AVR32_INTC_INT0,
        .tx_pin = BSP_UART2_TX_PIN,
        .tx_pin_function = BSP_UART2_TX_PIN_FUNCTION,
        .rx_pin = BSP_UART2_RX_PIN,
        .rx_pin_function = BSP_UART2_RX_PIN_FUNCTION,
        .uart_isr = avr32uc3_uart2_isr,
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

#ifdef BSP_USING_UART2
    UART2_INDEX,
#endif
};

#ifdef BSP_USING_UART0
void avr32uc3_uart0_isr(void)
{
    rt_interrupt_enter();
    /* read interrupt status and clear it */
    if (usart_test_hit(&AVR32_USART0)) /* rx ind */
    {
        rt_hw_serial_isr(&uart_dev[UART0_INDEX].parent, RT_SERIAL_EVENT_RX_IND);
    }

    rt_interrupt_leave();
}
#endif

#ifdef BSP_USING_UART1
void avr32uc3_uart1_isr(void)
{
    rt_interrupt_enter();
    /* read interrupt status and clear it */
    if (usart_test_hit(&AVR32_USART1)) /* rx ind */
    {
        rt_hw_serial_isr(&uart_dev[UART1_INDEX].parent, RT_SERIAL_EVENT_RX_IND);
    }

    rt_interrupt_leave();
}
#endif

#ifdef BSP_USING_UART2
void avr32uc3_uart2_isr(void)
{
    rt_interrupt_enter();
    /* read interrupt status and clear it */
    if (usart_test_hit(&AVR32_USART2)) /* rx ind */
    {
        rt_hw_serial_isr(&uart_dev[UART2_INDEX].parent, RT_SERIAL_EVENT_RX_IND);
    }

    rt_interrupt_leave();
}
#endif

/**
 * @addtogroup AVR32UC3
 */
/*@{*/

static rt_err_t avr32uc3_uart_configure(struct rt_serial_device *serial, struct serial_configure *cfg)
{
    struct avr32uc3_uart_dev *uart = RT_NULL;
    unsigned char l_parity;
    unsigned short l_stop;
    unsigned long l_baud;
    unsigned char l_data_bits;

    RT_ASSERT(serial != RT_NULL);
    RT_ASSERT(cfg != RT_NULL);

    uart = rt_container_of(serial, struct avr32uc3_uart_dev, parent);
    // Set the TX and RX pins by using the function select on the GPIO
    // Set datasheet for more information on function select
    gpio_enable_module_pin(uart->tx_pin, uart->tx_pin_function);
    gpio_enable_module_pin(uart->rx_pin, uart->rx_pin_function);

    /* Parity settings */
    if (cfg->parity == PARITY_ODD)
        l_parity = USART_ODD_PARITY;
    else if (cfg->parity == PARITY_EVEN)
        l_parity = USART_EVEN_PARITY;
    else
        l_parity = USART_NO_PARITY;

    /* Stopbit settings */
    if (cfg->stop_bits == STOP_BITS_1)
        l_stop = USART_1_STOPBIT;
    else
        l_stop = USART_2_STOPBITS;

    l_baud = cfg->baud_rate;
    l_data_bits = cfg->data_bits;

    /* Populate */
    usart_options_t usart_options = {
        .baudrate = l_baud,
        .charlength = l_data_bits,
        .paritytype = l_parity,
        .stopbits = l_stop,
        .channelmode = USART_NORMAL_CHMODE
    };

    usart_init_rs232(uart->instance, &usart_options, FPBA);

    return RT_EOK;
}

static rt_err_t avr32uc3_uart_control(struct rt_serial_device *serial, int cmd, void *arg)
{
    struct avr32uc3_uart_dev *uart = RT_NULL;
    RT_ASSERT(serial != RT_NULL);
    uart = rt_container_of(serial, struct avr32uc3_uart_dev, parent);

    switch (cmd)
    {
    /* enable interrupt */
    case RT_DEVICE_CTRL_SET_INT:
        // Set up a RX interrupt
        // We need to set up the handler first
        // And set up and enable the interrupt handlers
        //INTC_init_interrupts();
        INTC_register_interrupt(uart->uart_isr, uart->irqno, uart->irq_level);
        uart->instance->ier = AVR32_USART_IER_RXRDY_MASK;
        break;
    }
    return RT_EOK;
}

static int avr32uc3_uart_putc(struct rt_serial_device *serial, char c)
{
    struct avr32uc3_uart_dev *uart = RT_NULL;
    RT_ASSERT(serial != RT_NULL);
    uart = rt_container_of(serial, struct avr32uc3_uart_dev, parent);
    usart_putchar(uart->instance, c);

    return 1;
}

static int avr32uc3_uart_getc(struct rt_serial_device *serial)
{
    struct avr32uc3_uart_dev *uart = RT_NULL;
    RT_ASSERT(serial != RT_NULL);
    uart = rt_container_of(serial, struct avr32uc3_uart_dev, parent);

    int ch;
    if (usart_read_char(uart->instance, &ch) == USART_SUCCESS)
        return ch;

    return -1;
}

const static struct rt_uart_ops _uart_ops =
{
    avr32uc3_uart_configure,
    avr32uc3_uart_control,
    avr32uc3_uart_putc,
    avr32uc3_uart_getc,
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

#ifdef BSP_USING_UART2
    uart_dev[UART2_INDEX].parent.ops = &_uart_ops;
    uart_dev[UART2_INDEX].parent.config = config;

    ret = rt_hw_serial_register(&uart_dev[UART2_INDEX].parent,
                                "uart2",
                                RT_DEVICE_FLAG_RDWR | RT_DEVICE_FLAG_INT_RX,
                                &uart_dev[UART2_INDEX]);
    RT_ASSERT(ret == RT_EOK);
#endif


    return ret;
}

#endif /* RT_USING_SERIAL */

/*@}*/
