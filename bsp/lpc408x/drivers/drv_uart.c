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
#include "lpc_uart.h"
#include "lpc_pinsel.h"

struct lpc_uart
{
    UART_ID_Type UART;
    IRQn_Type UART_IRQn;
};

static rt_err_t lpc_configure(struct rt_serial_device *serial, struct serial_configure *cfg)
{
    struct lpc_uart *uart;
    UART_CFG_Type UARTConfigStruct;
    UART_FIFO_CFG_Type UARTFIFOConfigStruct;

    RT_ASSERT(serial != RT_NULL);
    uart = (struct lpc_uart *)serial->parent.user_data;

    /* Initialize UART Configuration parameter structure to default state:
     * Baudrate = 115200 bps
     * 8 data bit
     * 1 Stop bit
     * None parity
     */
    UART_ConfigStructInit(&UARTConfigStruct);
    UARTConfigStruct.Baud_rate = 115200;

    // Initialize UART0 peripheral with given to corresponding parameter
    UART_Init(uart->UART, &UARTConfigStruct);

    /* Initialize FIFOConfigStruct to default state:
     *              - FIFO_DMAMode = DISABLE
     *              - FIFO_Level = UART_FIFO_TRGLEV0
     *              - FIFO_ResetRxBuf = ENABLE
     *              - FIFO_ResetTxBuf = ENABLE
     *              - FIFO_State = ENABLE
     */
    UART_FIFOConfigStructInit(&UARTFIFOConfigStruct);

    // Initialize FIFO for UART0 peripheral
    UART_FIFOConfig(uart->UART, &UARTFIFOConfigStruct);

    UART_TxCmd(uart->UART, ENABLE);

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
        UART_IntConfig(uart->UART, UART_INTCFG_RBR, DISABLE);
        break;
    case RT_DEVICE_CTRL_SET_INT:
        /* enable rx irq */
        UART_IntConfig(uart->UART, UART_INTCFG_RBR, ENABLE);
        break;
    }

    return RT_EOK;
}

static int lpc_putc(struct rt_serial_device *serial, char c)
{
    struct lpc_uart *uart;

    uart = (struct lpc_uart *)serial->parent.user_data;
    UART_Send(uart->UART, (uint8_t *)&c, 1, BLOCKING);

    return 1;
}

static int lpc_getc(struct rt_serial_device *serial)
{
    uint8_t ch;
    struct lpc_uart *uart;

    uart = (struct lpc_uart *)serial->parent.user_data;
    if (UART_Receive(uart->UART, &ch, 1, NONE_BLOCKING) == 1)
        return (int) ch;

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
struct serial_ringbuffer uart0_int_rx;
struct lpc_uart uart0 =
{
    UART_0,
    UART0_IRQn,
};
struct rt_serial_device serial0;

void UART0_IRQHandler(void)
{
    struct lpc_uart *uart;
    uint32_t intsrc, tmp, tmp1;

    uart = &uart0;

    /* enter interrupt */
    rt_interrupt_enter();

    /* Determine the interrupt source */
    intsrc = UART_GetIntId(uart->UART);
    tmp = intsrc & UART_IIR_INTID_MASK;

    // Receive Line Status
    if (tmp == UART_IIR_INTID_RLS)
    {
        // Check line status
        tmp1 = UART_GetLineStatus(uart->UART);
        // Mask out the Receive Ready and Transmit Holding empty status
        tmp1 &= (UART_LSR_OE | UART_LSR_PE | UART_LSR_FE \
                 | UART_LSR_BI | UART_LSR_RXFE);
        // If any error exist
        if (tmp1)
        {
            //
        }
    }

    // Receive Data Available or Character time-out
    if ((tmp == UART_IIR_INTID_RDA) || (tmp == UART_IIR_INTID_CTI))
    {
        rt_hw_serial_isr(&serial0);
    }

    /* leave interrupt */
    rt_interrupt_leave();
}
#endif
#if defined(RT_USING_UART2)
/* UART2 device driver structure */
struct serial_ringbuffer uart2_int_rx;
struct lpc_uart uart2 =
{
    UART_2,
    UART2_IRQn,
};
struct rt_serial_device serial2;

void UART2_IRQHandler(void)
{
    struct lpc_uart *uart;
    uint32_t intsrc, tmp, tmp1;

    uart = &uart2;

    /* enter interrupt */
    rt_interrupt_enter();

    /* Determine the interrupt source */
    intsrc = UART_GetIntId(uart->UART);
    tmp = intsrc & UART_IIR_INTID_MASK;

    // Receive Line Status
    if (tmp == UART_IIR_INTID_RLS)
    {
        // Check line status
        tmp1 = UART_GetLineStatus(uart->UART);
        // Mask out the Receive Ready and Transmit Holding empty status
        tmp1 &= (UART_LSR_OE | UART_LSR_PE | UART_LSR_FE \
                 | UART_LSR_BI | UART_LSR_RXFE);
        // If any error exist
        if (tmp1)
        {
            //
        }
    }

    // Receive Data Available or Character time-out
    if ((tmp == UART_IIR_INTID_RDA) || (tmp == UART_IIR_INTID_CTI))
    {
        rt_hw_serial_isr(&serial2);
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

    serial0.ops    = &lpc_uart_ops;
    serial0.int_rx = &uart0_int_rx;
    serial0.config = config;

    /*
     * Initialize UART0 pin connect
     * P0.2: U0_TXD
     * P0.3: U0_RXD
     */
    PINSEL_ConfigPin(0, 2, 1);
    PINSEL_ConfigPin(0, 3, 1);

    /* preemption = 1, sub-priority = 1 */
    NVIC_SetPriority(uart->UART_IRQn, ((0x01 << 3) | 0x01));

    /* Enable Interrupt for UART channel */
    NVIC_EnableIRQ(uart->UART_IRQn);

    /* register UART1 device */
    rt_hw_serial_register(&serial0, "uart0",
                          RT_DEVICE_FLAG_RDWR | RT_DEVICE_FLAG_INT_RX | RT_DEVICE_FLAG_STREAM,
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

    serial2.ops    = &lpc_uart_ops;
    serial2.int_rx = &uart2_int_rx;
    serial2.config = config;

    /*
     * Initialize UART2 pin connect
     * P2.8: U2_TXD
     * P0.11: U2_RXD
     */
    PINSEL_ConfigPin(2, 8, 2);
    PINSEL_ConfigPin(0, 11, 1);

    /* preemption = 1, sub-priority = 1 */
    NVIC_SetPriority(uart->UART_IRQn, ((0x01 << 3) | 0x01));

    /* Enable Interrupt for UART channel */
    NVIC_EnableIRQ(uart->UART_IRQn);

    /* register UART1 device */
    rt_hw_serial_register(&serial2, "uart2",
                          RT_DEVICE_FLAG_RDWR | RT_DEVICE_FLAG_INT_RX | RT_DEVICE_FLAG_STREAM,
                          uart);
#endif
}
