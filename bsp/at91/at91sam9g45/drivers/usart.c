/*
 * Copyright (c) 2006-2021, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2011-01-13     weety       first version
 * 2013-07-21     weety       using serial component
 */

#include <rtthread.h>
#include <rthw.h>
#include <at91sam9g45.h>
#include <rtdevice.h>


struct at91_uart {
    AT91S_USART *port;
    int irq;
};


/**
 * This function will handle serial port interrupt
 */
void rt_at91_usart_handler(int vector, void *param)
{
    int status;
    struct at91_uart *uart;
    rt_device_t dev = (rt_device_t)param;
    uart = (struct at91_uart *)dev->user_data;
    status = uart->port->US_CSR;
    if (!(status & uart->port->US_IMR)) /* check actived and enabled interrupt */
    {
        return;
    }
    rt_interrupt_enter();
    rt_hw_serial_isr((struct rt_serial_device *)dev, RT_SERIAL_EVENT_RX_IND);
    rt_interrupt_leave();
}

/**
 * UART device in RT-Thread
 */
static rt_err_t at91_usart_configure(struct rt_serial_device *serial,
                                struct serial_configure *cfg)
{
    int div;
    int mode = 0;
    struct at91_uart *uart;

    RT_ASSERT(serial != RT_NULL);
    RT_ASSERT(cfg != RT_NULL);
    uart = (struct at91_uart *)serial->parent.user_data;

    uart->port->US_CR = AT91C_US_RSTTX | AT91C_US_RSTRX |
           AT91C_US_RXDIS | AT91C_US_TXDIS;
    mode |= AT91C_US_USMODE_NORMAL | AT91C_US_CLKS_CLOCK |
           AT91C_US_CHMODE_NORMAL;
    switch (cfg->data_bits)
    {
    case DATA_BITS_8:
        mode |= AT91C_US_CHRL_8_BITS;
        break;
    case DATA_BITS_7:
        mode |= AT91C_US_CHRL_7_BITS;
        break;
    case DATA_BITS_6:
        mode |= AT91C_US_CHRL_6_BITS;
        break;
    case DATA_BITS_5:
        mode |= AT91C_US_CHRL_5_BITS;
        break;
    default:
        mode |= AT91C_US_CHRL_8_BITS;
        break;
    }

    switch (cfg->stop_bits)
    {
    case STOP_BITS_2:
        mode |= AT91C_US_NBSTOP_2_BIT;
        break;
    case STOP_BITS_1:
    default:
        mode |= AT91C_US_NBSTOP_1_BIT;
        break;
    }

    switch (cfg->parity)
    {
    case PARITY_ODD:
        mode |= AT91C_US_PAR_ODD;
        break;
    case PARITY_EVEN:
        mode |= AT91C_US_PAR_EVEN;
        break;
    case PARITY_NONE:
    default:
        mode |= AT91C_US_PAR_NONE;
        break;
    }

    uart->port->US_MR = mode;
    /* Assume OVER is cleared and fractional baudrate generator is disabled */
    div = (clk_get_rate(clk_get("mck")) / 16 + cfg->baud_rate/2) / cfg->baud_rate;
    uart->port->US_BRGR = div;
    uart->port->US_CR = AT91C_US_RXEN | AT91C_US_TXEN;
    uart->port->US_IER = AT91C_US_RXRDY;

    return RT_EOK;
}

static rt_err_t at91_usart_control(struct rt_serial_device *serial,
                              int cmd, void *arg)
{
    struct at91_uart* uart;

    RT_ASSERT(serial != RT_NULL);
    uart = (struct at91_uart *)serial->parent.user_data;

    switch (cmd)
    {
    case RT_DEVICE_CTRL_CLR_INT:
        /* disable rx irq */
        rt_hw_interrupt_mask(uart->irq);
        break;
    case RT_DEVICE_CTRL_SET_INT:
        /* enable rx irq */
        rt_hw_interrupt_umask(uart->irq);
        break;
    }

    return RT_EOK;
}

static int at91_usart_putc(struct rt_serial_device *serial, char c)
{
    //rt_uint32_t level;
    struct at91_uart *uart = serial->parent.user_data;

    while (!(uart->port->US_CSR & AT91C_US_TXRDY));
    uart->port->US_THR = c;

    return 1;
}

static int at91_usart_getc(struct rt_serial_device *serial)
{
    int result;
    struct at91_uart *uart = serial->parent.user_data;

    if (uart->port->US_CSR & AT91C_US_RXRDY)
    {
        result = uart->port->US_RHR & 0xff;
    }
    else
    {
        result = -1;
    }

    return result;
}

static const struct rt_uart_ops at91_usart_ops =
{
    at91_usart_configure,
    at91_usart_control,
    at91_usart_putc,
    at91_usart_getc,
};

#if defined(RT_USING_DBGU)
static struct rt_serial_device serial_dbgu;
struct at91_uart dbgu = {
    (AT91PS_USART)AT91C_BASE_DBGU,
    AT91C_ID_SYS
};

#endif

#if defined(RT_USING_UART0)
static struct rt_serial_device serial0;
struct at91_uart uart0 = {
    AT91C_BASE_US0,
    AT91C_ID_US0
};
#endif

#if defined(RT_USING_UART1)
static struct rt_serial_device serial1;
struct at91_uart uart1 = {
    AT91C_BASE_US1,
    AT91C_ID_US1
};
#endif

#if defined(RT_USING_UART2)
static struct rt_serial_device serial2;
struct at91_uart uart2 = {
    AT91C_BASE_US2,
    AT91C_ID_US2
};
#endif

#if defined(RT_USING_UART3)
static struct rt_serial_device serial3;
struct at91_uart uart3 = {
    AT91C_BASE_US3,
    AT91C_ID_US3
};
#endif


void at91_usart_gpio_init(void)
{
#ifdef RT_USING_DBGU
#define DRXD    12      // DBGU  rx as Peripheral A on PB12
#define DTXD    13      // DBGU  tx as Peripheral A on PB13
    AT91C_BASE_PIOB->PIO_IDR,   (1<<DRXD)|(1<<DTXD);   // Disables the Input Change Interrupt on the I/O line
    AT91C_BASE_PIOB->PIO_PPUDR, (1<<DRXD)|(1<<DTXD);   // Disables the pull up resistor on the I/O line
    AT91C_BASE_PIOB->PIO_ASR,   (1<<DRXD)|(1<<DTXD);   // Assigns the I/O line to the Peripheral A function
    AT91C_BASE_PIOB->PIO_PDR,   (1<<DRXD)|(1<<DTXD);   // enables peripheral control of the pin
    AT91C_BASE_PMC->PMC_PCER,    1 << AT91C_ID_SYS;
#endif

#ifdef RT_USING_UART0
#define RXD0    18      // UART0 rx as Peripheral A on PB18
#define TXD0    19      // UART0 tx as Peripheral A on PB19
    AT91C_BASE_PMC->PMC_PCER,    1 << AT91C_ID_US0;
    AT91C_BASE_PIOB->PIO_IDR,   (1<<RXD0)|(1<<TXD0);
    AT91C_BASE_PIOB->PIO_PPUER, (1<<RXD0);
    AT91C_BASE_PIOB->PIO_PPUDR, (1<<TXD0);
    AT91C_BASE_PIOB->PIO_ASR,   (1<<RXD0)|(1<<TXD0);
    AT91C_BASE_PIOB->PIO_PDR,   (1<<RXD0)|(1<<TXD0);
#endif

#ifdef RT_USING_UART1
#define TXD1     4      // UART1 tx as Peripheral A on PB4
#define RXD1     5      // UART1 rx as Peripheral A on PB5
    AT91C_BASE_PMC->PMC_PCER,    1 << AT91C_ID_US1;
    AT91C_BASE_PIOB->PIO_IDR,   (1<<RXD1)|(1<<TXD1);
    AT91C_BASE_PIOB->PIO_PPUER, (1<<RXD1);
    AT91C_BASE_PIOB->PIO_PPUDR, (1<<TXD1);
    AT91C_BASE_PIOB->PIO_ASR,   (1<<RXD1)|(1<<TXD1);
    AT91C_BASE_PIOB->PIO_PDR,   (1<<RXD1)|(1<<TXD1);
#endif

#ifdef RT_USING_UART2
#define TXD2     6      // UART2 tx as Peripheral A on PB6
#define RXD2     7      // UART2 rx as Peripheral A on PB7
    AT91C_BASE_PMC->PMC_PCER,    1 << AT91C_ID_US2;
    AT91C_BASE_PIOB->PIO_IDR,   (1<<RXD2)|(1<<TXD2);
    AT91C_BASE_PIOB->PIO_PPUER, (1<<RXD2);
    AT91C_BASE_PIOB->PIO_PPUDR, (1<<TXD2);
    AT91C_BASE_PIOB->PIO_ASR,   (1<<RXD2)|(1<<TXD2);
    AT91C_BASE_PIOB->PIO_PDR,   (1<<RXD2)|(1<<TXD2);
#endif

#ifdef RT_USING_UART3
#define TXD3     8      // UART3 tx as Peripheral A on PB8
#define RXD3     9      // UART3 rx as Peripheral A on PB9
    AT91C_BASE_PMC->PMC_PCER,    1<<AT91C_ID_US3;
    AT91C_BASE_PIOB->PIO_IDR,   (1<<RXD3)|(1<<TXD3);
    AT91C_BASE_PIOB->PIO_PPUER, (1<<RXD3);
    AT91C_BASE_PIOB->PIO_PPUDR, (1<<TXD3);
    AT91C_BASE_PIOB->PIO_ASR,   (1<<RXD3)|(1<<TXD3);
    AT91C_BASE_PIOB->PIO_PDR,   (1<<RXD3)|(1<<TXD3);
#endif
}

/**
 * This function will handle init uart
 */
int rt_hw_uart_init(void)
{
    at91_usart_gpio_init();

#if defined(RT_USING_DBGU)
    serial_dbgu.ops = &at91_usart_ops;
    serial_dbgu.config.baud_rate = BAUD_RATE_115200;
    serial_dbgu.config.bit_order = BIT_ORDER_LSB;
    serial_dbgu.config.data_bits = DATA_BITS_8;
    serial_dbgu.config.parity = PARITY_NONE;
    serial_dbgu.config.stop_bits = STOP_BITS_1;
    serial_dbgu.config.invert = NRZ_NORMAL;
    serial_dbgu.config.bufsz = RT_SERIAL_RB_BUFSZ;

    /* register vcom device */
    rt_hw_serial_register(&serial_dbgu, "dbgu",
                          RT_DEVICE_FLAG_RDWR | RT_DEVICE_FLAG_INT_RX,
                          &dbgu);
#endif

#if defined(RT_USING_UART0)
    serial0.ops = &at91_usart_ops;
    serial0.config.baud_rate = BAUD_RATE_115200;
    serial0.config.bit_order = BIT_ORDER_LSB;
    serial0.config.data_bits = DATA_BITS_8;
    serial0.config.parity = PARITY_NONE;
    serial0.config.stop_bits = STOP_BITS_1;
    serial0.config.invert = NRZ_NORMAL;
    serial0.config.bufsz = RT_SERIAL_RB_BUFSZ;

    /* register vcom device */
    rt_hw_serial_register(&serial0, "uart0",
                          RT_DEVICE_FLAG_RDWR | RT_DEVICE_FLAG_INT_RX | RT_DEVICE_FLAG_STREAM,
                          &uart0);
    rt_hw_interrupt_install(uart0.irq, rt_at91_usart_handler,
                            (void *)&(serial0.parent), "UART0");
    rt_hw_interrupt_umask(uart0.irq);
#endif

#if defined(RT_USING_UART1)
    serial1.ops = &at91_usart_ops;
    serial1.config.baud_rate = BAUD_RATE_115200;
    serial1.config.bit_order = BIT_ORDER_LSB;
    serial1.config.data_bits = DATA_BITS_8;
    serial1.config.parity = PARITY_NONE;
    serial1.config.stop_bits = STOP_BITS_1;
    serial1.config.invert = NRZ_NORMAL;
    serial1.config.bufsz = RT_SERIAL_RB_BUFSZ;

    /* register vcom device */
    rt_hw_serial_register(&serial1, "uart1",
                          RT_DEVICE_FLAG_RDWR | RT_DEVICE_FLAG_INT_RX,
                          &uart1);
    rt_hw_interrupt_install(uart1.irq, rt_at91_usart_handler,
                            (void *)&(serial1.parent), "UART1");
    rt_hw_interrupt_umask(uart1.irq);
#endif

#if defined(RT_USING_UART2)
    serial2.ops = &at91_usart_ops;
    serial2.config.baud_rate = BAUD_RATE_115200;
    serial2.config.bit_order = BIT_ORDER_LSB;
    serial2.config.data_bits = DATA_BITS_8;
    serial2.config.parity = PARITY_NONE;
    serial2.config.stop_bits = STOP_BITS_1;
    serial2.config.invert = NRZ_NORMAL;
    serial2.config.bufsz = RT_SERIAL_RB_BUFSZ;

    /* register vcom device */
    rt_hw_serial_register(&serial2, "uart2",
                          RT_DEVICE_FLAG_RDWR | RT_DEVICE_FLAG_INT_RX,
                          &uart2);
    rt_hw_interrupt_install(uart2.irq, rt_at91_usart_handler,
                            (void *)&(serial2.parent), "UART2");
    rt_hw_interrupt_umask(uart2.irq);
#endif

#if defined(RT_USING_UART3)
    serial3.ops = &at91_usart_ops;
    serial3.config.baud_rate = BAUD_RATE_115200;
    serial3.config.bit_order = BIT_ORDER_LSB;
    serial3.config.data_bits = DATA_BITS_8;
    serial3.config.parity = PARITY_NONE;
    serial3.config.stop_bits = STOP_BITS_1;
    serial3.config.invert = NRZ_NORMAL;
    serial3.config.bufsz = RT_SERIAL_RB_BUFSZ;

    /* register vcom device */
    rt_hw_serial_register(&serial3, "uart3",
                          RT_DEVICE_FLAG_RDWR | RT_DEVICE_FLAG_INT_RX,
                          &uart3);
    rt_hw_interrupt_install(uart3.irq, rt_at91_usart_handler,
                            (void *)&(serial3.parent), "UART3");
    rt_hw_interrupt_umask(uart3.irq);
#endif

    return 0;
}

INIT_BOARD_EXPORT(rt_hw_uart_init);

#ifdef RT_USING_DBGU
void rt_dbgu_isr(void)
{
    rt_at91_usart_handler(dbgu.irq, &(serial_dbgu.parent));
}
#endif


