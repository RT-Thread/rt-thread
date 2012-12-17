/*
 * File      : usart.c
 * mb9bf506r uart driver
 * This file is part of RT-Thread RTOS
 * COPYRIGHT (C) 2006 - 2012, RT-Thread Development Team
 *
 * The license and distribution terms for this file may be
 * found in the file LICENSE in this distribution or at
 * http://www.rt-thread.org/license/LICENSE
 *
 * Change Logs:
 * Date           Author       Notes
 * 2012-11-30     lgnq         first  version
 */

#include <rtthread.h>
#include <rtdevice.h>
#include "usart.h"
#include "uart_18xx_43xx.h"
#include "scu_18xx_43xx.h"

#if defined(RT_USING_UART0)
/* UART0 device driver structure */
struct serial_ringbuffer uart0_int_rx;
struct uart_device uart0 =
{
    LPC_USART0,
    USART0_IRQn,
};
struct rt_serial_device serial0;

void UART0_IRQHandler(void)
{
    UART_Int_Status status;

    /* enter interrupt */
    rt_interrupt_enter();

    status = Chip_UART_GetIntStatus(LPC_USART0);

    /* error */
    if (status == UART_ERROR)
    {
        return;
    }

    /* ready for Read Data */
    if (status & READY_TO_RECEIVE)
    {
        rt_hw_serial_isr(&serial0);
    }

    /* leave interrupt */
    rt_interrupt_leave();
}
#endif

#if defined(RT_USING_UART1)
/* UART1 device driver structure */
struct serial_ringbuffer uart1_int_rx;
struct uart_device uart1 =
{
    LPC_UART1,
    USART1_IRQn,
};
struct rt_serial_device serial1;

void UART1_IRQHandler(void)
{
    UART_Int_Status status;

    /* enter interrupt */
    rt_interrupt_enter();

    status = Chip_UART_GetIntStatus(LPC_UART1);

    /* error */
    if (status == UART_ERROR)
    {
        return;
    }

    /* ready for Read Data */
    if (status & READY_TO_RECEIVE)
    {
        rt_hw_serial_isr(&serial1);
    }

    /* leave interrupt */
    rt_interrupt_leave();
}
#endif

#if defined(RT_USING_UART2)
/* UART2 device driver structure */
struct serial_ringbuffer uart2_int_rx;
struct uart_device uart2 =
{
    LPC_USART2,
    USART2_IRQn,
};
struct rt_serial_device serial2;

void UART2_IRQHandler(void)
{
    UART_Int_Status status;

    /* enter interrupt */
    rt_interrupt_enter();

    status = Chip_UART_GetIntStatus(LPC_USART2);

    /* error */
    if (status == UART_ERROR)
    {
        return;
    }

    /* ready for Read Data */
    if (status & READY_TO_RECEIVE)
    {
        rt_hw_serial_isr(&serial2);
    }

    /* leave interrupt */
    rt_interrupt_leave();
}
#endif

#if defined(RT_USING_UART3)
/* UART3 device driver structure */
struct serial_ringbuffer uart3_int_rx;
struct uart_device uart3 =
{
    LPC_USART3,
    USART3_IRQn,
};
struct rt_serial_device serial3;

void UART3_IRQHandler(void)
{
    UART_Int_Status status;

    /* enter interrupt */
    rt_interrupt_enter();

    status = Chip_UART_GetIntStatus(LPC_USART3);

    /* error */
    if (status == UART_ERROR)
    {
        return;
    }

    /* ready for Read Data */
    if (status & READY_TO_RECEIVE)
    {
        rt_hw_serial_isr(&serial3);
    }

    /* leave interrupt */
    rt_interrupt_leave();
}
#endif

void uart_pin_setup(void)
{
#if defined(RT_USING_UART0)
    Chip_SCU_PinMux(0x6, 4, MD_PDN, FUNC2);                   /* P6.5 : UART0_TXD */
    Chip_SCU_PinMux(0x6, 5, MD_PLN | MD_EZI | MD_ZI, FUNC2);  /* P6.4 : UART0_RXD */
#endif

#if defined(RT_USING_UART1)
    Chip_SCU_PinMux(0x1, 13, MD_PDN, FUNC2);                  /* P1.13 : UART1_TXD */
    Chip_SCU_PinMux(0x1, 14, MD_PLN | MD_EZI | MD_ZI, FUNC2); /* P1.14 : UART1_RX */
#endif
}

static rt_err_t uart_configure(struct rt_serial_device *serial, struct serial_configure *cfg)
{
    struct uart_device *uart;
    UART_DATABIT_Type   databit;
    UART_STOPBIT_Type   stopbit;
    UART_PARITY_Type    parity;

    /* UART FIFO configuration Struct variable */
    UART_FIFO_CFG_Type UARTFIFOConfigStruct;

    RT_ASSERT(serial != RT_NULL);

    uart = (struct uart_device *)serial->parent.user_data;

    Chip_UART_Init(uart->uart_regs);

    Chip_UART_SetBaud(uart->uart_regs, cfg->baud_rate);

    /* set stop bits */
    switch (cfg->stop_bits)
    {
    case STOP_BITS_1:
        stopbit = UART_STOPBIT_1;
        break;
    case STOP_BITS_2:
        stopbit = UART_STOPBIT_2;
        break;
    default:
        return RT_ERROR;
    }

    /* set data bits */
    switch (cfg->data_bits)
    {
    case DATA_BITS_5:
        databit = UART_DATABIT_5;
        break;
    case DATA_BITS_6:
        databit = UART_DATABIT_6;
        break;
    case DATA_BITS_7:
        databit = UART_DATABIT_7;
        break;
    case DATA_BITS_8:
        databit = UART_DATABIT_8;
        break;
    default:
        return RT_ERROR;
    }

    /* set parity */
    switch (cfg->parity)
    {
    case PARITY_NONE:
        parity = UART_PARITY_NONE;
        break;
    case PARITY_EVEN:
        parity = UART_PARITY_EVEN;
        break;
    case PARITY_ODD:
        parity = UART_PARITY_ODD;
        break;
    default:
        return RT_ERROR;
    }

    Chip_UART_ConfigData(uart->uart_regs, databit, parity, stopbit);

    /* Enable UART Transmit */
    Chip_UART_TxCmd(uart->uart_regs, ENABLE);

    Chip_UART_FIFOConfigStructInit(&UARTFIFOConfigStruct);

    /* Enable DMA mode in UART */
    UARTFIFOConfigStruct.FIFO_DMAMode = ENABLE;
    /* Initialize FIFO for UART0 peripheral */
    Chip_UART_FIFOConfig(uart->uart_regs, &UARTFIFOConfigStruct);

    /* Enable UART Rx interrupt */
    Chip_UART_IntConfig(uart->uart_regs, UART_INTCFG_RBR, ENABLE);
    /* Enable UART line status interrupt */
    Chip_UART_IntConfig(uart->uart_regs, UART_INTCFG_RLS, ENABLE);

    /* Enable Interrupt for UART channel */
    /* Priority = 1 */
    NVIC_SetPriority(uart->irq_num, 1);

    return RT_EOK;
}

static rt_err_t uart_control(struct rt_serial_device *serial, int cmd, void *arg)
{
    struct uart_device *uart;

    RT_ASSERT(serial != RT_NULL);
    uart = (struct uart_device *)serial->parent.user_data;

    switch (cmd)
    {
    case RT_DEVICE_CTRL_CLR_INT:
        /* disable rx irq */
        UART_DISABLE_IRQ(uart->irq_num);
        break;
    case RT_DEVICE_CTRL_SET_INT:
        /* enable rx irq */
        UART_ENABLE_IRQ(uart->irq_num);
        break;
    }

    return (RT_EOK);
}

static int uart_putc(struct rt_serial_device *serial, char c)
{
    struct uart_device *uart;

    RT_ASSERT(serial != RT_NULL);

    uart = (struct uart_device *)serial->parent.user_data;

    /* wait send buffer is empty */
    while (!(uart->uart_regs->LSR & UART_LSR_THRE))
        ;
    /* write to send buffer */
    uart->uart_regs->THR = c & UART_THR_MASKBIT;

    return (1);
}

static int uart_getc(struct rt_serial_device *serial)
{
    struct uart_device *uart;
    uint8_t ch;

    RT_ASSERT(serial != RT_NULL);
    
    uart = (struct uart_device *)serial->parent.user_data;

    /* receive buffer is full */
    if (uart->uart_regs->LSR & UART_LSR_RDR)
    {
        ch = uart->uart_regs->RBR & UART_RBR_MASKBIT;

        return (ch);
    }
    else
        return (-1);
}

static struct rt_uart_ops uart_ops =
{
    uart_configure,
    uart_control,
    uart_putc,
    uart_getc,
};

void rt_hw_serial_init(void)
{
    struct serial_configure config;

    config.baud_rate = BAUD_RATE_115200;
    config.data_bits = DATA_BITS_8;
    config.parity    = PARITY_NONE;
    config.stop_bits = STOP_BITS_1;

    uart_pin_setup();

#if defined(RT_USING_UART0)
    serial0.ops    = &uart_ops;
    serial0.int_rx = &uart0_int_rx;
    serial0.config = config;

    /* register UART0 device */
    rt_hw_serial_register(&serial0,
                          "uart0",
                          RT_DEVICE_FLAG_RDWR | RT_DEVICE_FLAG_INT_RX | RT_DEVICE_FLAG_STREAM,
                          &uart0);
#endif

#if defined(RT_USING_UART1)
    serial1.ops    = &uart_ops;
    serial1.int_rx = &uart1_int_rx;
    serial1.config = config;

    /* register UART1 device */
    rt_hw_serial_register(&serial1,
                          "uart1",
                          RT_DEVICE_FLAG_RDWR | RT_DEVICE_FLAG_INT_RX | RT_DEVICE_FLAG_STREAM,
                          &uart1);
#endif

#if defined(RT_USING_UART2)
    serial2.ops    = &uart_ops;
    serial2.int_rx = &uart2_int_rx;
    serial2.config = config;

    /* register UART2 device */
    rt_hw_serial_register(&serial2,
                          "uart2",
                          RT_DEVICE_FLAG_RDWR | RT_DEVICE_FLAG_INT_RX | RT_DEVICE_FLAG_STREAM,
                          &uart2);
#endif

#if defined(RT_USING_UART3)
    serial3.ops    = &uart_ops;
    serial3.int_rx = &uart3_int_rx;
    serial3.config = config;

    /* register UART3 device */
    rt_hw_serial_register(&serial3,
                          "uart3",
                          RT_DEVICE_FLAG_RDWR | RT_DEVICE_FLAG_INT_RX | RT_DEVICE_FLAG_STREAM,
                          &uart3);
#endif
}
