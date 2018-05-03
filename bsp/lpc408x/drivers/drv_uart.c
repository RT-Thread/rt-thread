/*
 * File      : drv_uart.c
 * This file is part of RT-Thread RTOS
 * COPYRIGHT (C) 2009-2013 RT-Thread Develop Team
 *
 * The license and distribution terms for this file may be
 * found in the file LICENSE in this distribution or at
 * http://www.rt-thread.org/license/LICENSE
 *
 * Change Logs:
 * Date           Author       Notes
 * 2013-05-18     Bernard      The first version for LPC40xx
 */

#include <rthw.h>
#include <rtthread.h>
#include <rtdevice.h>

#include "board.h"

struct lpc_uart
{
    LPC_UART_TypeDef *UART;
    IRQn_Type UART_IRQn;
};

static rt_err_t lpc_configure(struct rt_serial_device *serial, struct serial_configure *cfg)
{
    struct lpc_uart *uart;
    uint32_t Fdiv = 0;

    RT_ASSERT(serial != RT_NULL);
    uart = (struct lpc_uart *)serial->parent.user_data;

    /* Initialize UART Configuration parameter structure to default state:
     * Baudrate = 115200 bps
     * 8 data bit
     * 1 Stop bit
     * None parity
     */
    /* set DLAB=1 */
    uart->UART->LCR |= 0x80;
    /* config uart baudrate */
    Fdiv = (PeripheralClock / 16) / cfg->baud_rate;
    uart->UART->DLM = Fdiv / 256;
    uart->UART->DLL = Fdiv % 256;
    /* set DLAB=0 */
    uart->UART->LCR &= ~0x80;
    /* config to 8 data bit,1 Stop bit,None parity */
    uart->UART->LCR |= 0x03;

    /*enable and reset FIFO*/
    uart->UART->FCR = 0x07;


    return RT_EOK;
}

static rt_err_t lpc_control(struct rt_serial_device *serial, int cmd, void *arg)
{
    struct lpc_uart *uart;

    RT_ASSERT(serial != RT_NULL);
    uart = (struct lpc_uart *)serial->parent.user_data;

    switch (cmd)
    {
    case RT_DEVICE_CTRL_CLR_INT:
        /* disable rx irq */
        uart->UART->IER &= ~0x01;
        break;
    case RT_DEVICE_CTRL_SET_INT:
        /* enable rx irq */
        uart->UART->IER |= 0x01;
        break;
    }

    return RT_EOK;
}

static int lpc_putc(struct rt_serial_device *serial, char c)
{
    struct lpc_uart *uart;

    uart = (struct lpc_uart *)serial->parent.user_data;
    while (!(uart->UART->LSR & 0x20));
    uart->UART->THR = c;

    return 1;
}

static int lpc_getc(struct rt_serial_device *serial)
{
    struct lpc_uart *uart;

    uart = (struct lpc_uart *)serial->parent.user_data;
    if (uart->UART->LSR & 0x01)
        return (uart->UART->RBR);
    else
        return -1;
}

static const struct rt_uart_ops lpc_uart_ops =
{
    lpc_configure,
    lpc_control,
    lpc_putc,
    lpc_getc,
};

#ifdef RT_USING_UART0
/* UART0 device driver structure */
#if RTTHREAD_VERSION < 20000 /* RT-Thread 1.x */
struct serial_ringbuffer uart0_int_rx;
#endif

struct lpc_uart uart0 =
{
    LPC_UART0,
    UART0_IRQn,
};
struct rt_serial_device serial0;

void UART0_IRQHandler(void)
{
    volatile  uint32_t IIR, tmp;

    /* enter interrupt */
    rt_interrupt_enter();

    IIR = LPC_UART0->IIR;
    IIR &= 0x0e;
    switch (IIR)
    {

    case 0x04:
    case 0x0C:
    #if RTTHREAD_VERSION < 20000
        rt_hw_serial_isr(&serial0);
    #else
        rt_hw_serial_isr(&serial0, RT_SERIAL_EVENT_RX_IND);
    #endif
        break;
    case 0x06:
        tmp = LPC_UART0->LSR;
        break;
    default :
        tmp = LPC_UART0->LSR;
        break;
    }
    /* leave interrupt */
    rt_interrupt_leave();
}
#endif
#ifdef RT_USING_UART2
/* UART2 device driver structure */
#if RTTHREAD_VERSION < 20000 /* RT-Thread 1.x */
struct serial_ringbuffer uart2_int_rx;
#endif

struct lpc_uart uart2 =
{
    LPC_UART2,
    UART2_IRQn,
};
struct rt_serial_device serial2;

void UART2_IRQHandler(void)
{
    volatile  uint32_t IIR, tmp;

    /* enter interrupt */
    rt_interrupt_enter();

    IIR = LPC_UART2->IIR;
    IIR &= 0x0e;
    switch (IIR)
    {
    case 0x04:
    case 0x0C:
    #if RTTHREAD_VERSION < 20000
        rt_hw_serial_isr(&serial2);
    #else
        rt_hw_serial_isr(&serial2, RT_SERIAL_EVENT_RX_IND);
    #endif
        break;
    case 0x06:
        tmp = LPC_UART2->LSR;
        break;
    default :
        tmp = LPC_UART2->LSR;
        break;
    }

    /* leave interrupt */
    rt_interrupt_leave();
}
#endif

#ifdef RT_USING_UART4
/* UART4 device driver structure */
#if RTTHREAD_VERSION < 20000 /* RT-Thread 1.x */
struct serial_ringbuffer uart4_int_rx;
#endif

struct lpc_uart uart4 =
{
    LPC_UART4,
    UART4_IRQn,
};
struct rt_serial_device serial4;

void UART4_IRQHandler(void)
{
    volatile  uint32_t IIR, tmp;

    /* enter interrupt */
    rt_interrupt_enter();

    IIR = LPC_UART4->IIR;
    IIR &= 0x0e;
    switch (IIR)
    {
    case 0x04:
    case 0x0C:
    #if RTTHREAD_VERSION < 20000
        rt_hw_serial_isr(&serial4);
    #else
        rt_hw_serial_isr(&serial4, RT_SERIAL_EVENT_RX_IND);
    #endif
        break;
    case 0x06:
        tmp = LPC_UART4->LSR;
        break;
    default :
        tmp = LPC_UART4->LSR;
        break;
    }

    /* leave interrupt */
    rt_interrupt_leave();
}
#endif

void rt_hw_uart_init(void)
{
    struct lpc_uart *uart;
    struct serial_configure config = RT_SERIAL_CONFIG_DEFAULT;

#ifdef RT_USING_UART0
    uart = &uart0;

    serial0.ops    = &lpc_uart_ops;
    serial0.config = config;
    #if RTTHREAD_VERSION < 20000
    serial0.int_rx = &uart0_int_rx;
    #endif
    serial0.parent.user_data = uart;
    
    /*
     * Initialize UART0 pin connect
     * P0.2: U0_TXD
     * P0.3: U0_RXD
     */
    LPC_IOCON->P0_2 &= ~0x07;
    LPC_IOCON->P0_2 |= 0x01;
    LPC_IOCON->P0_3 &= ~0x07;
    LPC_IOCON->P0_3 |= 0x01;

    /* enable the uart0 power and clock */
    LPC_SC->PCONP |= 0x01 << 3;

    /* preemption = 1, sub-priority = 1 */
    NVIC_SetPriority(uart->UART_IRQn, ((0x01 << 3) | 0x01));

    /* Enable Interrupt for UART channel */
    NVIC_EnableIRQ(uart->UART_IRQn);

    /* register UART0 device */
    rt_hw_serial_register(&serial0, "uart0",
                          RT_DEVICE_FLAG_RDWR | RT_DEVICE_FLAG_INT_RX | RT_DEVICE_FLAG_STREAM,
                          uart);
#endif

#ifdef RT_USING_UART2
    uart = &uart2;

    serial2.ops    = &lpc_uart_ops;
    serial2.config = config;
    #if RTTHREAD_VERSION < 20000
    serial2.int_rx = &uart2_int_rx;
    #endif
    serial2.parent.user_data = uart;

    /*
     * Initialize UART2 pin connect
     * P2.8: U2_TXD
     * P0.11: U2_RXD
     */
    LPC_IOCON->P2_8 &= ~0x07;
    LPC_IOCON->P0_11 &= ~0x07;
    LPC_IOCON->P2_8 |= 0x02;
    LPC_IOCON->P0_11 |= 0x01;

    /* enable the uart2 power and clock */
    LPC_SC->PCONP |= 0x01 << 24;
    /* preemption = 1, sub-priority = 1 */
    NVIC_SetPriority(uart->UART_IRQn, ((0x01 << 3) | 0x01));

    /* Enable Interrupt for UART channel */
    NVIC_EnableIRQ(uart->UART_IRQn);

    /* register UART2 device */
    rt_hw_serial_register(&serial2, "uart2",
                          RT_DEVICE_FLAG_RDWR | RT_DEVICE_FLAG_INT_RX | RT_DEVICE_FLAG_STREAM,
                          uart);
#endif

#ifdef RT_USING_UART4
    uart = &uart4;

    serial4.ops    = &lpc_uart_ops;
    serial4.config = config;
    #if RTTHREAD_VERSION < 20000
    serial4.int_rx = &uart4_int_rx;
    #endif
    serial4.parent.user_data = uart;
    
    /*
     * Initialize UART2 pin connect
     * P5.4: U2_TXD
     * P5.3: U2_RXD
     */
    LPC_IOCON->P5_4 &= ~0x07;
    LPC_IOCON->P5_3 &= ~0x07;
    LPC_IOCON->P5_4 |= 0x04;
    LPC_IOCON->P5_3 |= 0x04;

    /* enable the uart4 power and clock */
    LPC_SC->PCONP |= 0x01 << 8;
    /* preemption = 1, sub-priority = 1 */
    NVIC_SetPriority(uart->UART_IRQn, ((0x01 << 3) | 0x01));

    /* Enable Interrupt for UART channel */
    NVIC_EnableIRQ(uart->UART_IRQn);

    /* register UART2 device */
    rt_hw_serial_register(&serial4, "uart4",
                          RT_DEVICE_FLAG_RDWR | RT_DEVICE_FLAG_INT_RX | RT_DEVICE_FLAG_STREAM,
                          uart);
#endif
}
