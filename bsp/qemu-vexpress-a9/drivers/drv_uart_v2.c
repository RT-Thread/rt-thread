/*
 * Copyright (c) 2006-2025 RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2025-04-08     Hydevcode   the first version
 */
#include <rtthread.h>
#include <rtdevice.h>
#include <rtdbg.h>
#include "board.h"
#include "drv_uart_v2.h"
#include "mmu.h"

#ifdef RT_USING_SERIAL_V2

#include <rtdbg.h>

#if !defined(BSP_USING_UART0) && !defined(BSP_USING_UART1) && !defined(BSP_USING_UART2) &&  !defined(BSP_USING_UART3)
    #error "Please define at least one BSP_USING_UARTx"
    /* this driver can be disabled at menuconfig -> RT-Thread Components -> Device Drivers */
#endif

struct hw_uart_device
{
    rt_uint32_t hw_base;
    rt_uint32_t irqno;
    struct rt_serial_device *serial;
    char *device_name;
};

#define UART_DR(base)   __REG32(base + 0x00)
#define UART_FR(base)   __REG32(base + 0x18)
#define UART_CR(base)   __REG32(base + 0x30)
#define UART_IMSC(base) __REG32(base + 0x38)
#define UART_ICR(base)  __REG32(base + 0x44)
#define UART_IFLS(base) __REG32(base + 0x34)
#define UART_TCR(base)  __REG32(base + 0x80)
#define UART_ITOP(base) __REG32(base + 0x88)

#define UART_LCR_H(base)    __REG32(base + 0x2C)
#define UART_DMACR(base)    __REG32(base + 0x48)

#define UARTITOP_RXINTR 0x400

#define UARTLCR_H_FEN     0x10

#define UARTFR_RXFE     0x10
#define UARTFR_TXFF     0x20
#define UARTFR_RXFF     0x40
#define UARTFR_TXFE     0x80
#define UARTFR_BUSY     0x08

#define UARTICR_RXIC    0x10
#define UARTICR_TXIC    0x20

#define UARTIMSC_RXIM   0x10
#define UARTIMSC_RTIM   0x40
#define UARTIMSC_TXIM   0x20

#if defined(BSP_USING_UART0)
struct rt_serial_device serial0;
#endif

#if defined(BSP_USING_UART1)
struct rt_serial_device serial1;
#endif

#if defined(BSP_USING_UART2)
struct rt_serial_device serial2;
#endif


#if defined(BSP_USING_UART3)
struct rt_serial_device serial3;
#endif

static struct hw_uart_device _uart_device[] = {
#if defined(BSP_USING_UART0)
{
    REALVIEW_UART0_BASE,
    IRQ_PBA8_UART0,
    &serial0,
    "uart0",
},
#endif

#if defined(BSP_USING_UART1)
{
    REALVIEW_UART1_BASE,
    IRQ_PBA8_UART1,
    &serial1,
    "uart1",
},
#endif

#if defined(BSP_USING_UART2)
{
    REALVIEW_UART2_BASE,
    IRQ_PBA8_UART2,
    &serial2,
    "uart2",
},
#endif

#if defined(BSP_USING_UART3)
{
    REALVIEW_UART3_BASE,
    IRQ_PBA8_UART3,
    &serial3,
    "uart3",
},
#endif

};

/**
 * @brief UART common interrupt process. This
 *
 * @param serial Serial device
 */

static void rt_hw_uart_isr(int irqno, void *param)
{
    struct rt_serial_device *serial = (struct rt_serial_device *)param;

    RT_ASSERT(serial != RT_NULL);

    struct hw_uart_device *uart;

    uart = (struct hw_uart_device *)serial->parent.user_data;

    RT_ASSERT(uart != RT_NULL);

    if((UART_FR(uart->hw_base) & UARTFR_RXFF) && (UART_IMSC(uart->hw_base) & UARTIMSC_RXIM))
    {

        struct rt_serial_rx_fifo *rx_fifo;

        rx_fifo = (struct rt_serial_rx_fifo *)serial->serial_rx;

        RT_ASSERT(rx_fifo != RT_NULL);

        char rec_ch;
        while (!(UART_FR(uart->hw_base) & UARTFR_RXFE))
        {
            rec_ch = UART_DR(uart->hw_base) & 0xff;
            rt_hw_serial_control_isr(serial, RT_HW_SERIAL_CTRL_PUTC, &rec_ch);

        }
        rt_hw_serial_isr(serial,RT_SERIAL_EVENT_RX_IND);

    }
    else if(UART_IMSC(uart->hw_base) & UARTIMSC_RTIM)
    {
        struct rt_serial_rx_fifo *rx_fifo;

        rx_fifo = (struct rt_serial_rx_fifo *)serial->serial_rx;

        RT_ASSERT(rx_fifo != RT_NULL);

        char rec_ch;

        while (!(UART_FR(uart->hw_base) & UARTFR_RXFE))
        {
            rec_ch = UART_DR(uart->hw_base) & 0xff;
            rt_hw_serial_control_isr(serial, RT_HW_SERIAL_CTRL_PUTC, &rec_ch);

        }
        rt_hw_serial_isr(serial,RT_SERIAL_EVENT_RX_IND);
    }
    else if((UART_IMSC(uart->hw_base) & UARTIMSC_TXIM))
    {
        UART_ICR(uart->hw_base) |= UARTICR_TXIC;

        rt_hw_serial_isr(serial,RT_SERIAL_EVENT_TX_DONE);
    }
}

static rt_err_t uart_configure(struct rt_serial_device *serial, struct serial_configure *cfg)
{
    return RT_EOK;
}

static rt_err_t uart_control(struct rt_serial_device *serial, int cmd, void *arg)
{
    struct hw_uart_device *uart;

    RT_ASSERT(serial != RT_NULL);

    uart = (struct hw_uart_device *)serial->parent.user_data;

    rt_ubase_t ctrl_arg = (rt_ubase_t) arg;

    if(ctrl_arg & (RT_DEVICE_FLAG_RX_BLOCKING | RT_DEVICE_FLAG_RX_NON_BLOCKING))
    {
        ctrl_arg = RT_DEVICE_FLAG_INT_RX;
    }
    else if(ctrl_arg & (RT_DEVICE_FLAG_TX_BLOCKING | RT_DEVICE_FLAG_TX_NON_BLOCKING))
    {
        ctrl_arg = RT_DEVICE_FLAG_INT_TX;
    }

    switch (cmd)
    {
        case RT_DEVICE_CTRL_CLR_INT:
            if (ctrl_arg == RT_DEVICE_FLAG_INT_RX)
            {
                /* disable rx irq */
                UART_IMSC(uart->hw_base) &= ~UARTIMSC_RXIM;
                UART_IMSC(uart->hw_base) &= ~UARTIMSC_RTIM;
            }
            else if (ctrl_arg == RT_DEVICE_FLAG_INT_TX)
            {
                /* disable tx irq */
                UART_IMSC(uart->hw_base) &= ~UARTIMSC_TXIM;
            }
            break;

        case RT_DEVICE_CTRL_SET_INT:
            if (ctrl_arg == RT_DEVICE_FLAG_INT_RX)
            {
                /* enable rx irq */
                UART_IMSC(uart->hw_base) |= UARTIMSC_RXIM;
                UART_IMSC(uart->hw_base) |= UARTIMSC_RTIM;
                rt_hw_interrupt_umask(uart->irqno);

            } else if (ctrl_arg == RT_DEVICE_FLAG_INT_TX)
            {
                /* enable tx irq */
                UART_IMSC(uart->hw_base) |= UARTIMSC_TXIM;
                rt_hw_interrupt_umask(uart->irqno);
            }

            break;
        case RT_DEVICE_CTRL_CONFIG:
            uart_control(serial, RT_DEVICE_CTRL_SET_INT, (void *)ctrl_arg);
            break;
    }
    return RT_EOK;
}

static int uart_putc(struct rt_serial_device *serial, char ch)
{
    struct hw_uart_device *uart;

    RT_ASSERT(serial != RT_NULL);

    uart = (struct hw_uart_device *)serial->parent.user_data;
    while (UART_FR(uart->hw_base) & UARTFR_TXFF);
    UART_DR(uart->hw_base) = ch;

    return 1;
}

static int uart_getc(struct rt_serial_device *serial)
{
    int ch;
    struct hw_uart_device *uart;

    RT_ASSERT(serial != RT_NULL);

    uart = (struct hw_uart_device *)serial->parent.user_data;

    ch = -1;
    if (!(UART_FR(uart->hw_base) & UARTFR_RXFE))
    {
        ch = UART_DR(uart->hw_base) & 0xff;
    }

    return ch;
}
static rt_ssize_t uart_transmit(struct rt_serial_device *serial,
    rt_uint8_t *buf,
    rt_size_t size,
    rt_uint32_t tx_flag)
{
    RT_ASSERT(serial != RT_NULL);
    RT_ASSERT(buf != RT_NULL);
    RT_ASSERT(size);
    struct hw_uart_device *uart = (struct hw_uart_device *)serial->parent.user_data;
    struct rt_serial_tx_fifo *tx_fifo;
    tx_fifo = (struct rt_serial_tx_fifo *) serial->serial_tx;
    uint8_t ch = 0;
    RT_ASSERT(tx_fifo != RT_NULL);

    if (size > 0)
    {
        if (UART_IMSC(uart->hw_base) & UARTIMSC_TXIM)
        {
            UART_IMSC(uart->hw_base) &= ~UARTIMSC_TXIM;
            if(rt_ringbuffer_getchar(&tx_fifo->rb, &ch))
            {
                while (UART_FR(uart->hw_base) & UARTFR_TXFF);
                UART_DR(uart->hw_base) = ch;
            }
            UART_IMSC(uart->hw_base) |= UARTIMSC_TXIM;
        }
    }

    return size;
}

static const struct rt_uart_ops _uart_ops = {
    .configure = uart_configure,
    .control = uart_control,
    .putc = uart_putc,
    .getc = uart_getc,
    .transmit = uart_transmit
};

static int uart_config(void)
{
    struct serial_configure config = RT_SERIAL_CONFIG_DEFAULT;

#ifdef BSP_USING_UART0
    _uart_device[0].serial->config = config;
    _uart_device[0].serial->config.rx_bufsz = BSP_UART0_RX_BUFSIZE;
    _uart_device[0].serial->config.tx_bufsz = BSP_UART0_TX_BUFSIZE;
#endif /* BSP_USING_UART0 */

#ifdef BSP_USING_UART1
    _uart_device[1].serial->config = config;
    _uart_device[1].serial->config.rx_bufsz = BSP_UART1_RX_BUFSIZE;
    _uart_device[1].serial->config.tx_bufsz = BSP_UART1_TX_BUFSIZE;
#endif /* BSP_USING_UART1 */

#ifdef BSP_USING_UART2
    _uart_device[2].serial->config = config;
    _uart_device[2].serial->config.rx_bufsz = BSP_UART2_RX_BUFSIZE;
    _uart_device[2].serial->config.tx_bufsz = BSP_UART2_TX_BUFSIZE;
#endif /* BSP_USING_UART2 */

#ifdef BSP_USING_UART3
    _uart_device[3].serial->config = config;
    _uart_device[3].serial->config.rx_bufsz = BSP_UART3_RX_BUFSIZE;
    _uart_device[3].serial->config.tx_bufsz = BSP_UART3_TX_BUFSIZE;
#endif /* BSP_USING_UART3 */

    return RT_EOK;
}

int rt_hw_uart_init(void)
{

    rt_err_t err = RT_EOK;

    uart_config();

    for (uint32_t i = 0; i < sizeof(_uart_device) / sizeof(_uart_device[0]); i++)
    {

        #ifdef RT_USING_SMART
            _uart_device[i].hw_base = (uint32_t)rt_ioremap((void*)_uart_device[i].hw_base, 0x1000);
        #endif

        _uart_device[i].serial->ops = &_uart_ops;
        /* register UART device */
        err = rt_hw_serial_register(_uart_device[i].serial,
                            _uart_device[i].device_name,
                            RT_DEVICE_FLAG_RDWR,
                            (void*)&_uart_device[i]);
        rt_hw_interrupt_install(_uart_device[i].irqno, rt_hw_uart_isr, _uart_device[i].serial, _uart_device[i].device_name);
        /* enable Rx and Tx of UART */
        UART_CR(_uart_device[i].hw_base) = (1 << 0) | (1 << 8) | (1 << 9);

        UART_LCR_H(_uart_device[i].hw_base) =(1 << 4);

        UART_IFLS(_uart_device[i].hw_base) =0;
        UART_IFLS(_uart_device[i].hw_base) =(1 << 3);

    }

    return err;
}
INIT_BOARD_EXPORT(rt_hw_uart_init);
#endif /* RT_USING_SERIAL_V2 */