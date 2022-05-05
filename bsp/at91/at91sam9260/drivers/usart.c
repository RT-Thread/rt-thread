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
#include <at91sam926x.h>
#include <rtdevice.h>

#define RXRDY           0x01
#define TXRDY           (1 << 1)

typedef struct uartport
{
    volatile rt_uint32_t CR;
    volatile rt_uint32_t MR;
    volatile rt_uint32_t IER;
    volatile rt_uint32_t IDR;
    volatile rt_uint32_t IMR;
    volatile rt_uint32_t CSR;
    volatile rt_uint32_t RHR;
    volatile rt_uint32_t THR;
    volatile rt_uint32_t BRGR;
    volatile rt_uint32_t RTOR;
    volatile rt_uint32_t TTGR;
    volatile rt_uint32_t reserved0[5];
    volatile rt_uint32_t FIDI;
    volatile rt_uint32_t NER;
    volatile rt_uint32_t reserved1;
    volatile rt_uint32_t IFR;
    volatile rt_uint32_t reserved2[44];
    volatile rt_uint32_t RPR;
    volatile rt_uint32_t RCR;
    volatile rt_uint32_t TPR;
    volatile rt_uint32_t TCR;
    volatile rt_uint32_t RNPR;
    volatile rt_uint32_t RNCR;
    volatile rt_uint32_t TNPR;
    volatile rt_uint32_t TNCR;
    volatile rt_uint32_t PTCR;
    volatile rt_uint32_t PTSR;
}uartport;

#define CIDR FIDI
#define EXID NER
#define FNR  reserved1

#define DBGU    ((struct uartport *)AT91SAM9260_BASE_DBGU)

#define UART0   ((struct uartport *)AT91SAM9260_BASE_US0)
#define UART1   ((struct uartport *)AT91SAM9260_BASE_US1)
#define UART2   ((struct uartport *)AT91SAM9260_BASE_US2)
#define UART3   ((struct uartport *)AT91SAM9260_BASE_US3)

struct at91_uart {
    uartport *port;
    int irq;
};



/**
 * This function will handle serial
 */
void rt_at91_usart_handler(int vector, void *param)
{
    int status;
    struct at91_uart *uart;
    rt_device_t dev = (rt_device_t)param;
    uart = (struct at91_uart *)dev->user_data;
    status = uart->port->CSR;
    if (!(status & uart->port->IMR))
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

    uart->port->CR = AT91_US_RSTTX | AT91_US_RSTRX |
           AT91_US_RXDIS | AT91_US_TXDIS;
    mode |= AT91_US_USMODE_NORMAL | AT91_US_USCLKS_MCK |
        AT91_US_CHMODE_NORMAL;
    switch (cfg->data_bits)
    {
    case DATA_BITS_8:
        mode |= AT91_US_CHRL_8;
        break;
    case DATA_BITS_7:
        mode |= AT91_US_CHRL_7;
        break;
    case DATA_BITS_6:
        mode |= AT91_US_CHRL_6;
        break;
    case DATA_BITS_5:
        mode |= AT91_US_CHRL_5;
        break;
    default:
        mode |= AT91_US_CHRL_8;
        break;
    }

    switch (cfg->stop_bits)
    {
    case STOP_BITS_2:
        mode |= AT91_US_NBSTOP_2;
        break;
    case STOP_BITS_1:
    default:
        mode |= AT91_US_NBSTOP_1;
        break;
    }

    switch (cfg->parity)
    {
    case PARITY_ODD:
        mode |= AT91_US_PAR_ODD;
        break;
    case PARITY_EVEN:
        mode |= AT91_US_PAR_EVEN;
        break;
    case PARITY_NONE:
    default:
        mode |= AT91_US_PAR_NONE;
        break;
    }

    uart->port->MR = mode;
    div = (clk_get_rate(clk_get("mck")) / 16 + cfg->baud_rate/2) / cfg->baud_rate;
    uart->port->BRGR = div;
    uart->port->CR = AT91_US_RXEN | AT91_US_TXEN;
    uart->port->IER = 0x01;

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
    rt_uint32_t level;
    struct at91_uart *uart = serial->parent.user_data;

    while (!(uart->port->CSR & TXRDY));
    uart->port->THR = c;

    return 1;
}

static int at91_usart_getc(struct rt_serial_device *serial)
{
    int result;
    struct at91_uart *uart = serial->parent.user_data;

    if (uart->port->CSR & RXRDY)
    {
        result = uart->port->RHR & 0xff;
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
    DBGU,
    AT91_ID_SYS
};

#endif

#if defined(RT_USING_UART0)
static struct rt_serial_device serial0;
struct at91_uart uart0 = {
    UART0,
    AT91SAM9260_ID_US0
};
#endif

#if defined(RT_USING_UART1)
static struct rt_serial_device serial1;
struct at91_uart uart1 = {
    UART1,
    AT91SAM9260_ID_US1
};
#endif

#if defined(RT_USING_UART2)
static struct rt_serial_device serial2;
struct at91_uart uart2 = {
    UART2,
    AT91SAM9260_ID_US2
};
#endif

#if defined(RT_USING_UART3)
static struct rt_serial_device serial3;
struct at91_uart uart3 = {
    UART3,
    AT91SAM9260_ID_US3
};
#endif

void at91_usart_gpio_init(void)
{
    rt_uint32_t val;

#ifdef RT_USING_DBGU
    at91_sys_write(AT91_PIOB + PIO_IDR, (1<<14)|(1<<15));
    //at91_sys_write(AT91_PIOB + PIO_PUER, (1<<6));
    at91_sys_write(AT91_PIOB + PIO_PUDR, (1<<14)|(1<<15));
    at91_sys_write(AT91_PIOB + PIO_ASR, (1<<14)|(1<<15));
    at91_sys_write(AT91_PIOB + PIO_PDR, (1<<14)|(1<<15));
    at91_sys_write(AT91_PMC_PCER, 1 << AT91_ID_SYS);
#endif

#ifdef RT_USING_UART0
    at91_sys_write(AT91_PMC_PCER, 1 << AT91SAM9260_ID_US0);
    at91_sys_write(AT91_PIOB + PIO_IDR, (1<<4)|(1<<5));
    at91_sys_write(AT91_PIOB + PIO_PUER, (1<<4));
    at91_sys_write(AT91_PIOB + PIO_PUDR, (1<<5));
    at91_sys_write(AT91_PIOB + PIO_ASR, (1<<4)|(1<<5));
    at91_sys_write(AT91_PIOB + PIO_PDR, (1<<4)|(1<<5));
#endif

#ifdef RT_USING_UART1
    at91_sys_write(AT91_PMC_PCER, 1 << AT91SAM9260_ID_US1);
    at91_sys_write(AT91_PIOB + PIO_IDR, (1<<6)|(1<<7));
    at91_sys_write(AT91_PIOB + PIO_PUER, (1<<6));
    at91_sys_write(AT91_PIOB + PIO_PUDR, (1<<7));
    at91_sys_write(AT91_PIOB + PIO_ASR, (1<<6)|(1<<7));
    at91_sys_write(AT91_PIOB + PIO_PDR, (1<<6)|(1<<7));
#endif

#ifdef RT_USING_UART2
    at91_sys_write(AT91_PMC_PCER, 1 << AT91SAM9260_ID_US2);
    at91_sys_write(AT91_PIOB + PIO_IDR, (1<<8)|(1<<9));
    at91_sys_write(AT91_PIOB + PIO_PUER, (1<<8));
    at91_sys_write(AT91_PIOB + PIO_PUDR, (1<<9));
    at91_sys_write(AT91_PIOB + PIO_ASR, (1<<8)|(1<<9));
    at91_sys_write(AT91_PIOB + PIO_PDR, (1<<8)|(1<<9));
#endif

#ifdef RT_USING_UART3
    at91_sys_write(AT91_PMC_PCER, 1<<AT91SAM9260_ID_US3);
    at91_sys_write(AT91_PIOB + PIO_IDR, (1<<10)|(1<<11));
    at91_sys_write(AT91_PIOB + PIO_PUER, (1<<10));
    at91_sys_write(AT91_PIOB + PIO_PUDR, (1<<11));
    at91_sys_write(AT91_PIOB + PIO_ASR, (1<<10)|(1<<11));
    at91_sys_write(AT91_PIOB + PIO_PDR, (1<<10)|(1<<11));
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
    serial1.int_rx = &uart1_int_rx;
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


