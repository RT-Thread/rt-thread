/*
 * Copyright (c) 2006-2021, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2013-05-18     Bernard      The first version for LPC40xx
 */

#include <rthw.h>
#include <rtthread.h>
#include <rtdevice.h>
#include "board.h"
#include "drv_uart.h"

struct lpc_uart
{
    LPC_USARTn_Type  *USART;
    IRQn_Type USART_IRQn;
};

static rt_err_t lpc_configure(struct rt_serial_device *serial, struct serial_configure *cfg)
{
//    struct lpc_uart *uart;


    RT_ASSERT(serial != RT_NULL);
    //  uart = (struct lpc_uart *)serial->parent.user_data;



    // Initialize FIFO for UART0 peripheral
//    UART_FIFOConfig(uart->USART, &UARTFIFOConfigStruct);

//    UART_TxCmd(uart->USART, ENABLE);

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
        uart->USART->IER &= ~UART_IER_RBRINT_EN;
        break;
    case RT_DEVICE_CTRL_SET_INT:
        /* enable rx irq */
        uart->USART->IER |= UART_IER_RBRINT_EN;
        break;
    }

    return RT_EOK;
}

static int lpc_putc(struct rt_serial_device *serial, char c)
{
    struct lpc_uart *uart;

    uart = (struct lpc_uart *)serial->parent.user_data;
    while (!(uart->USART->LSR & 0x20));
    uart->USART->THR = c;
    return 1;
}

static int lpc_getc(struct rt_serial_device *serial)
{
    struct lpc_uart *uart;

    uart = (struct lpc_uart *)serial->parent.user_data;

    if (uart->USART->LSR & 0x01)
    {
        return (uart->USART->RBR);
    }
    return -1;
}

static const struct rt_uart_ops lpc_uart_ops =
{
    lpc_configure,
    lpc_control,
    lpc_putc,
    lpc_getc,
};

#if defined(RT_USING_UART0)
/* UART0 device driver structure */
struct lpc_uart uart0 =
{
    LPC_USART0,
    USART0_IRQn,
};
struct rt_serial_device serial0;

void UART0_IRQHandler(void)
{
    struct lpc_uart *uart;
   volatile uint32_t intsrc, temp;

    uart = &uart0;

    /* enter interrupt */
    rt_interrupt_enter();

    /* Determine the interrupt source */
    intsrc = uart->USART->IIR & UART_IIR_INTID_MASK;

    switch (intsrc)
    {

    case UART_IIR_INTID_RLS:                                            /* Receive Line Status interrupt*/
        /* read the line status */
        intsrc = uart->USART->LSR;
        /* Receive an error data */
        if (intsrc & UART_LSR_PE)
        {
            temp = LPC_USART0->RBR;
        }
        break;

    case UART_IIR_INTID_RDA:                                            /*  Receive data               */
    case UART_IIR_INTID_CTI:                                            /*  Receive data timeout       */
        /* read the data to buffer  */
        while (uart->USART->LSR & UART_LSR_RDR)
        {
            rt_hw_serial_isr(&serial0, RT_SERIAL_EVENT_RX_IND);
        }
        break;

    default:
        break;
    }

    /* leave interrupt */
    rt_interrupt_leave();
}
#endif
#if defined(RT_USING_UART2)
/* UART2 device driver structure */
struct lpc_uart uart2 =
{
    LPC_USART2,
    USART2_IRQn,
};
struct rt_serial_device serial2;

void UART2_IRQHandler(void)
{
    struct lpc_uart *uart;
    uint32_t intsrc, temp;

    uart = &uart2;

    /* enter interrupt */
    rt_interrupt_enter();

    /* Determine the interrupt source */
    intsrc = uart->USART->IIR & UART_IIR_INTID_MASK;

    switch (intsrc)
    {

    case UART_IIR_INTID_RLS:                                            /* Receive Line Status interrupt*/
        /* read the line status */
        intsrc = uart->USART->LSR;
        /* Receive an error data */
        if (intsrc & UART_LSR_PE)
        {
            temp = LPC_USART0->RBR;
        }
        break;

    case UART_IIR_INTID_RDA:                                            /*  Receive data               */
    case UART_IIR_INTID_CTI:                                            /*  Receive data timeout       */
        /* read the data to buffer  */
        while (uart->USART->LSR & UART_LSR_RDR)
        {
            rt_hw_serial_isr(&serial0, RT_SERIAL_EVENT_RX_IND);
        }
        break;

    default:
        break;
    }

    /* leave interrupt */
    rt_interrupt_leave();
}
#endif
void rt_hw_uart_init(void)
{
    struct lpc_uart *uart;
    struct serial_configure config;

#ifdef RT_USING_UART0
    uart = &uart0;
    config.baud_rate = BAUD_RATE_115200;
    config.bit_order = BIT_ORDER_LSB;
    config.data_bits = DATA_BITS_8;
    config.parity    = PARITY_NONE;
    config.stop_bits = STOP_BITS_1;
    config.invert    = NRZ_NORMAL;
    config.bufsz     = RT_SERIAL_RB_BUFSZ;

    serial0.ops    = &lpc_uart_ops;
    serial0.config = config;

    /* Enable GPIO register interface clock                                     */
    LPC_CCU1->CLK_M4_GPIO_CFG     |= 0x01;
    while (!(LPC_CCU1->CLK_M4_GPIO_STAT  & 0x01));

    /* Enable USART1 peripheral clock                                           */
    LPC_CCU2->CLK_APB0_USART0_CFG |= 0x01;
    while (!(LPC_CCU2->CLK_APB0_USART0_STAT & 0x01));

    /* Enable USART1 register interface clock                                   */
    LPC_CCU1->CLK_M4_USART0_CFG   |= 0x01;
    while (!(LPC_CCU1->CLK_M4_USART0_STAT & 0x01));

    /* Init GPIO pins                                                           */
    LPC_SCU->SFSP6_4 = (1 << 6) |         /* Input buffer enabled               */
                       (1 << 4) |        /* Pull-up disabled                   */
                       (2 << 0) ;        /* Pin P6_4 used as U0_TXD            */

    LPC_SCU->SFSP6_5 = (1 << 6) |         /* Input buffer enabled               */
                       (1 << 4) |        /* Pull-up disabled                   */
                       (2 << 0) ;        /* Pin P6_5 used as U0_RXD            */

    /* Init USART0                                                              */
    LPC_USART0->LCR    = 0x83;            /* 8 bits, no Parity, 1 Stop bit      */
    LPC_USART0->DLL    = 0x06;            /* 115200 Baudrate @ 12 MHz IRC       */
    LPC_USART0->DLM    = 0x00;
    LPC_USART0->FDR    = 0xC1;
    LPC_USART0->LCR    = 0x03;            /* DLAB = 0                           */

    /* preemption = 1, sub-priority = 1 */
    NVIC_SetPriority(uart->USART_IRQn, ((0x01 << 3) | 0x01));

    /* Enable Interrupt for UART channel */
    NVIC_EnableIRQ(uart->USART_IRQn);

    /* register UART1 device */
    rt_hw_serial_register(&serial0, "uart0",
                          RT_DEVICE_FLAG_RDWR | RT_DEVICE_FLAG_INT_RX,
                          uart);
#endif
#ifdef RT_USING_UART2
    uart = &uart2;
    config.baud_rate = BAUD_RATE_115200;
    config.bit_order = BIT_ORDER_LSB;
    config.data_bits = DATA_BITS_8;
    config.parity    = PARITY_NONE;
    config.stop_bits = STOP_BITS_1;
    config.invert    = NRZ_NORMAL;
    config.bufsz     = RT_SERIAL_RB_BUFSZ;

    serial2.ops    = &lpc_uart_ops;
    serial2.config = config;

    /* Enable GPIO register interface clock                                     */
    LPC_CCU1->CLK_M4_GPIO_CFG     |= 0x01;
    while (!(LPC_CCU1->CLK_M4_GPIO_STAT  & 0x01));

    /* Enable USART1 peripheral clock                                           */
    LPC_CCU2->CLK_APB0_USART0_CFG |= 0x01;
    while (!(LPC_CCU2->CLK_APB2_USART2_STAT & 0x01));

    /* Enable USART2 register interface clock                                   */
    LPC_CCU1->CLK_M4_USART0_CFG   |= 0x01;
    while (!(LPC_CCU1->CLK_M4_USART2_STAT & 0x01));

    /* Init GPIO pins                                                           */
    LPC_SCU->SFSP1_15 = (1 << 6) |         /* Input buffer enabled               */
                        (1 << 4) |        /* Pull-up disabled                   */
                        (1 << 0) ;        /* Pin P1_15 used as U2_TXD            */

    LPC_SCU->SFSP1_16 = (1 << 6) |         /* Input buffer enabled               */
                        (1 << 4) |        /* Pull-up disabled                   */
                        (1 << 0) ;        /* Pin P1_16 used as U2_RXD            */

    /* Init USART2                                                              */
    LPC_USART2->LCR    = 0x83;            /* 8 bits, no Parity, 1 Stop bit      */
    LPC_USART2->DLL    = 0x06;            /* 115200 Baudrate @ 12 MHz IRC       */
    LPC_USART2->DLM    = 0x00;
    LPC_USART2->FDR    = 0xC1;
    LPC_USART2->LCR    = 0x03;            /* DLAB = 0                           */
    /* preemption = 1, sub-priority = 1 */
    NVIC_SetPriority(uart->USART_IRQn, ((0x01 << 3) | 0x01));

    /* Enable Interrupt for UART channel */
    NVIC_EnableIRQ(uart->USART_IRQn);

    /* register UART1 device */
    rt_hw_serial_register(&serial2, "uart2",
                          RT_DEVICE_FLAG_RDWR | RT_DEVICE_FLAG_INT_RX,
                          uart);
#endif
}
