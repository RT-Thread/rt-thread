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
    RT_ASSERT(serial != RT_NULL);
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

static void _do_uart_isr(struct rt_serial_device *sdev)
{
    struct lpc_uart *uart;
    uint32_t intsrc;

    uart = sdev->parent.user_data;

    /* Determine the interrupt source */
    intsrc = uart->USART->IIR & UART_IIR_INTID_MASK;

    switch (intsrc)
    {
    case UART_IIR_INTID_RLS:
        /* Receive Line Status interrupt */
        /* read the line status */
        intsrc = uart->USART->LSR;
        /* Receive an error data */
        if (intsrc & UART_LSR_PE)
        {
            uart->USART->RBR;
        }
        break;
    case UART_IIR_INTID_RDA:
        /* Receive data */
    case UART_IIR_INTID_CTI:
        /* Receive data timeout */
        /* read the data to buffer  */
        while (uart->USART->LSR & UART_LSR_RDR)
        {
            rt_hw_serial_isr(sdev, RT_SERIAL_EVENT_RX_IND);
        }
        break;

    default:
        break;
    }
}

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
    rt_interrupt_enter();
    _do_uart_isr(&serial0);
    rt_interrupt_leave();
}
#endif

#if defined(RT_USING_UART2)
struct lpc_uart uart2 =
{
    LPC_USART2,
    USART2_IRQn,
};
struct rt_serial_device serial2;

void UART2_IRQHandler(void)
{
    rt_interrupt_enter();
    _do_uart_isr(&serial2);
    rt_interrupt_leave();
}
#endif

#if defined(RT_USING_UART3)
struct lpc_uart uart3 =
{
    LPC_USART3,
    USART3_IRQn,
};
struct rt_serial_device serial3;

void UART3_IRQHandler(void)
{
    rt_interrupt_enter();
    _do_uart_isr(&serial3);
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

    /* Enable USART0 peripheral clock                                           */
    LPC_CCU2->CLK_APB0_USART0_CFG |= 0x01;
    while (!(LPC_CCU2->CLK_APB0_USART0_STAT & 0x01));

    /* Enable USART0 register interface clock                                   */
    LPC_CCU1->CLK_M4_USART0_CFG   |= 0x01;
    while (!(LPC_CCU1->CLK_M4_USART0_STAT & 0x01));

    /* Init GPIO pins                                                           */
    LPC_SCU->SFSP2_0 = (1 << 6) |         /* Input buffer enabled               */
        (1 << 4) |        /* Pull-up disabled                   */
        (1 << 0) ;        /* Pin P2_0 used as U0_TXD            */

    LPC_SCU->SFSP2_1 = (1 << 6) |         /* Input buffer enabled               */
        (1 << 4) |        /* Pull-up disabled                   */
        (1 << 0) ;        /* Pin P2_1 used as U0_RXD            */

    /* Init USART0                                                              */
    uart->USART->LCR    = 0x83;            /* 8 bits, no Parity, 1 Stop bit      */
    uart->USART->DLL    = 0x06;            /* 115200 Baudrate @ 12 MHz IRC       */
    uart->USART->DLM    = 0x00;
    uart->USART->FDR    = 0xC1;
    uart->USART->LCR    = 0x03;            /* DLAB = 0                           */
    /* preemption = 1, sub-priority = 1 */
    NVIC_SetPriority(uart->USART_IRQn, ((0x01 << 3) | 0x01));

    /* Enable Interrupt for UART channel */
    NVIC_EnableIRQ(uart->USART_IRQn);

    /* register UART0 device */
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

    /* Enable USART2 peripheral clock                                           */
    LPC_CCU2->CLK_APB2_USART2_CFG |= 0x01;
    while (!(LPC_CCU2->CLK_APB2_USART2_STAT & 0x01));

    /* Enable USART2 register interface clock                                   */
    LPC_CCU1->CLK_M4_USART2_CFG   |= 0x01;
    while (!(LPC_CCU1->CLK_M4_USART2_STAT & 0x01));

    /* Init GPIO pins                                                           */
    LPC_SCU->SFSP1_15 = (1 << 6) |         /* Input buffer enabled               */
        (1 << 4) |        /* Pull-up disabled                   */
        (1 << 0) ;        /* Pin P1_15 used as U2_TXD            */

    LPC_SCU->SFSP1_16 = (1 << 6) |         /* Input buffer enabled               */
        (1 << 4) |        /* Pull-up disabled                   */
        (1 << 0) ;        /* Pin P1_16 used as U2_RXD            */

    /* Init USART2                                                              */
    uart->USART->LCR    = 0x83;            /* 8 bits, no Parity, 1 Stop bit      */
    uart->USART->DLL    = 0x06;            /* 115200 Baudrate @ 12 MHz IRC       */
    uart->USART->DLM    = 0x00;
    uart->USART->FDR    = 0xC1;
    uart->USART->LCR    = 0x03;            /* DLAB = 0                           */

    /* preemption = 1, sub-priority = 1 */
    NVIC_SetPriority(uart->USART_IRQn, ((0x01 << 3) | 0x01));

    /* Enable Interrupt for UART channel */
    NVIC_EnableIRQ(uart->USART_IRQn);

    /* register UART2 device */
    rt_hw_serial_register(&serial2, "uart2",
                          RT_DEVICE_FLAG_RDWR | RT_DEVICE_FLAG_INT_RX,
                          uart);
#endif
#ifdef RT_USING_UART3
    uart = &uart3;
    config.baud_rate = BAUD_RATE_115200;
    config.bit_order = BIT_ORDER_LSB;
    config.data_bits = DATA_BITS_8;
    config.parity    = PARITY_NONE;
    config.stop_bits = STOP_BITS_1;
    config.invert    = NRZ_NORMAL;
    config.bufsz     = RT_SERIAL_RB_BUFSZ;

    serial3.ops    = &lpc_uart_ops;
    serial3.config = config;

    /* Enable GPIO register interface clock                                     */
    LPC_CCU1->CLK_M4_GPIO_CFG     |= 0x01;
    while (!(LPC_CCU1->CLK_M4_GPIO_STAT  & 0x01));

    /* Enable USART3 peripheral clock                                           */
    LPC_CCU2->CLK_APB2_USART3_CFG |= 0x01;
    while (!(LPC_CCU2->CLK_APB2_USART3_STAT & 0x01));

    /* Enable USART3 register interface clock                                   */
    LPC_CCU1->CLK_M4_USART3_CFG   |= 0x01;
    while (!(LPC_CCU1->CLK_M4_USART3_STAT & 0x01));

    /* Init GPIO pins                                                           */
    LPC_SCU->SFSP2_3 = (1 << 6) |         /* Input buffer enabled               */
        (1 << 4) |        /* Pull-up disabled                   */
        (2 << 0) ;        /* Pin P1_15 used as U2_TXD            */

    LPC_SCU->SFSP2_4 = (1 << 6) |         /* Input buffer enabled               */
        (1 << 4) |        /* Pull-up disabled                   */
        (2 << 0) ;        /* Pin P1_16 used as U2_RXD            */

    /* Init USART3                                                              */
    uart->USART->LCR    = 0x83;            /* 8 bits, no Parity, 1 Stop bit      */
    uart->USART->DLL    = 0x06;            /* 115200 Baudrate @ 12 MHz IRC       */
    uart->USART->DLM    = 0x00;
    uart->USART->FDR    = 0xC1;
    uart->USART->LCR    = 0x03;            /* DLAB = 0                           */

    /* preemption = 1, sub-priority = 1 */
    NVIC_SetPriority(uart->USART_IRQn, ((0x01 << 3) | 0x01));

    /* Enable Interrupt for UART channel */
    NVIC_EnableIRQ(uart->USART_IRQn);

    /* register UART2 device */
    rt_hw_serial_register(&serial3, "uart3",
                          RT_DEVICE_FLAG_RDWR | RT_DEVICE_FLAG_INT_RX,
                          uart);
#endif
}
