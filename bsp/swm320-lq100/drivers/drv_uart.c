/*
 * Copyright (c) 2006-2018, Synwit Technology Co.,Ltd.
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2018-05-31     ZYH          first version
 * 2018-12-10     Zohar_Lee    format file
 */

#include <rtthread.h>
#include <rtdevice.h>
#include <board.h>
#include <SWM320_port.h>
#include <SWM320_uart.h>

struct swm320_uart
{
    UART_TypeDef *uart;
    IRQn_Type irq;
};

static rt_err_t swm320_uart_configure(struct rt_serial_device *serial,
                                      struct serial_configure *cfg)
{
    struct swm320_uart *uart;
    UART_InitStructure UART_initStruct;
    RT_ASSERT(serial != RT_NULL);
    RT_ASSERT(cfg != RT_NULL);
    uart = (struct swm320_uart *)serial->parent.user_data;
    NVIC_DisableIRQ(uart->irq);
    UART_initStruct.Baudrate = cfg->baud_rate;
    UART_initStruct.RXThreshold = 1;
    UART_initStruct.RXThresholdIEn = 1;
    UART_initStruct.TXThresholdIEn = 0;
    UART_initStruct.TimeoutTime = 10;
    UART_initStruct.TimeoutIEn = 0;
    switch (cfg->data_bits)
    {
    case DATA_BITS_9:
        UART_initStruct.DataBits = UART_DATA_9BIT;
        break;
    default:
        UART_initStruct.DataBits = UART_DATA_8BIT;
        break;
    }
    switch (cfg->stop_bits)
    {
    case STOP_BITS_2:
        UART_initStruct.StopBits = UART_STOP_2BIT;
        break;
    default:
        UART_initStruct.StopBits = UART_STOP_1BIT;
        break;
    }
    switch (cfg->parity)
    {
    case PARITY_ODD:
        UART_initStruct.Parity = UART_PARITY_ODD;
        break;
    case PARITY_EVEN:
        UART_initStruct.Parity = UART_PARITY_EVEN;
        break;
    default:
        UART_initStruct.Parity = UART_PARITY_NONE;
        break;
    }
    UART_Init(uart->uart, &UART_initStruct);
    UART_Open(uart->uart);
    return RT_EOK;
}

static rt_err_t swm320_uart_control(struct rt_serial_device *serial,
                                    int cmd, void *arg)
{
    struct swm320_uart *uart;
    RT_ASSERT(serial != RT_NULL);
    uart = (struct swm320_uart *)serial->parent.user_data;
    switch (cmd)
    {
    case RT_DEVICE_CTRL_CLR_INT:
        /* disable rx irq */
        NVIC_DisableIRQ(uart->irq);
        break;
    case RT_DEVICE_CTRL_SET_INT:
        /* enable rx irq */
        NVIC_EnableIRQ(uart->irq);
        break;
    }
    return RT_EOK;
}

static int swm320_uart_putc(struct rt_serial_device *serial, char c)
{
    struct swm320_uart *uart;
    RT_ASSERT(serial != RT_NULL);
    uart = (struct swm320_uart *)serial->parent.user_data;
    while (UART_IsTXBusy(uart->uart));
    uart->uart->DATA = c;
    return 1;
}

static int swm320_uart_getc(struct rt_serial_device *serial)
{
    int ch;
    struct swm320_uart *uart;
    RT_ASSERT(serial != RT_NULL);
    uart = (struct swm320_uart *)serial->parent.user_data;
    ch = -1;
    if (UART_IsRXFIFOEmpty(uart->uart) == 0)
    {
        UART_ReadByte(uart->uart, (uint32_t *)&ch);
    }
    return ch;
}

static const struct rt_uart_ops swm320_uart_ops =
{
    swm320_uart_configure,
    swm320_uart_control,
    swm320_uart_putc,
    swm320_uart_getc,
};

#if defined(BSP_USING_UART0)
/* UART0 device driver structure */
static struct swm320_uart uart0;
static struct rt_serial_device serial0;
void UART0_Handler(void)
{
    /* enter interrupt */
    rt_interrupt_enter();

    /* UART in mode Receiver */
    if (UART_INTRXThresholdStat(uart0.uart) || UART_INTTimeoutStat(uart0.uart))
    {
        rt_hw_serial_isr(&serial0, RT_SERIAL_EVENT_RX_IND);
    }
    /* leave interrupt */
    rt_interrupt_leave();
}
#endif /* BSP_USING_UART0 */

#if defined(BSP_USING_UART1)
/* UART1 device driver structure */
static struct swm320_uart uart1;
static struct rt_serial_device serial1;
void UART1_Handler(void)
{
    /* enter interrupt */
    rt_interrupt_enter();

    /* UART in mode Receiver */
    if (UART_INTRXThresholdStat(uart1.uart) || UART_INTTimeoutStat(uart1.uart))
    {
        rt_hw_serial_isr(&serial1, RT_SERIAL_EVENT_RX_IND);
    }
    /* leave interrupt */
    rt_interrupt_leave();
}
#endif /* BSP_USING_UART1 */

#if defined(BSP_USING_UART2)
/* UART2 device driver structure */
static struct swm320_uart uart2;
static struct rt_serial_device serial2;
void UART2_Handler(void)
{
    /* enter interrupt */
    rt_interrupt_enter();

    /* UART in mode Receiver */
    if (UART_INTRXThresholdStat(uart2.uart) || UART_INTTimeoutStat(uart2.uart))
    {
        rt_hw_serial_isr(&serial2, RT_SERIAL_EVENT_RX_IND);
    }
    /* leave interrupt */
    rt_interrupt_leave();
}
#endif /* BSP_USING_UART2 */

#if defined(BSP_USING_UART3)
/* UART3 device driver structure */
static struct swm320_uart uart3;
static struct rt_serial_device serial3;
void UART3_Handler(void)
{
    /* enter interrupt */
    rt_interrupt_enter();

    /* UART in mode Receiver */
    if (UART_INTRXThresholdStat(uart3.uart) || UART_INTTimeoutStat(uart3.uart))
    {
        rt_hw_serial_isr(&serial3, RT_SERIAL_EVENT_RX_IND);
    }
    /* leave interrupt */
    rt_interrupt_leave();
}
#endif /* BSP_USING_UART3 */

int rt_hw_uart_init(void)
{
    struct swm320_uart *uart;
    struct serial_configure config = RT_SERIAL_CONFIG_DEFAULT;
#ifdef BSP_USING_UART0
    PORT_Init(PORTA, PIN2, FUNMUX0_UART0_RXD, 1);
    PORT_Init(PORTA, PIN3, FUNMUX1_UART0_TXD, 0);
    uart = &uart0;
    uart->uart = UART0;
    uart->irq = UART0_IRQn;
    serial0.ops = &swm320_uart_ops;
    serial0.config = config;
    /* register UART0 device */
    rt_hw_serial_register(&serial0, "uart0",
                          RT_DEVICE_FLAG_RDWR | RT_DEVICE_FLAG_INT_RX,
                          uart);
#endif /* BSP_USING_UART0 */
#ifdef BSP_USING_UART1
    PORT_Init(PORTC, PIN2, FUNMUX0_UART1_RXD, 1);
    PORT_Init(PORTC, PIN3, FUNMUX1_UART1_TXD, 0);
    uart = &uart1;
    uart->uart = UART1;
    uart->irq = UART1_IRQn;
    serial1.ops = &swm320_uart_ops;
    serial1.config = config;
    /* register UART1 device */
    rt_hw_serial_register(&serial1, "uart1",
                          RT_DEVICE_FLAG_RDWR | RT_DEVICE_FLAG_INT_RX,
                          uart);
#endif /* BSP_USING_UART1 */
#ifdef BSP_USING_UART2
    PORT_Init(PORTC, PIN4, FUNMUX0_UART2_RXD, 1);
    PORT_Init(PORTC, PIN5, FUNMUX1_UART2_TXD, 0);
    uart = &uart2;
    uart->uart = UART2;
    uart->irq = UART2_IRQn;
    serial2.ops = &swm320_uart_ops;
    serial2.config = config;
    /* register UART2 device */
    rt_hw_serial_register(&serial2, "uart2",
                          RT_DEVICE_FLAG_RDWR | RT_DEVICE_FLAG_INT_RX,
                          uart);
#endif /* BSP_USING_UART2 */
#ifdef BSP_USING_UART3
    PORT_Init(PORTC, PIN6, FUNMUX0_UART3_RXD, 1);
    PORT_Init(PORTC, PIN7, FUNMUX1_UART3_TXD, 0);
    uart = &uart3;
    uart->uart = UART3;
    uart->irq = UART3_IRQn;
    serial3.ops = &swm320_uart_ops;
    serial3.config = config;
    /* register UART3 device */
    rt_hw_serial_register(&serial3, "uart3",
                          RT_DEVICE_FLAG_RDWR | RT_DEVICE_FLAG_INT_RX,
                          uart);
#endif /* BSP_USING_UART3 */
    return 0;
}
INIT_BOARD_EXPORT(rt_hw_uart_init);
