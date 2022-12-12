/*
 * Copyright (c) 2006-2021, YICHIP Technology Co.,Ltd.
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2021-09-09     WSY          first version
 */

#include <rtthread.h>
#include <rtdevice.h>
#include <board.h>

struct yc3121_uart
{
    UART_TypeDef uart;
    IRQn_Type irq;
};

static rt_err_t yc3121_uart_configure(struct rt_serial_device *serial,
                                struct serial_configure *cfg)
{
    struct yc3121_uart *uart;
    UART_InitTypeDef UART_initStruct;
    RT_ASSERT(serial != RT_NULL);
    RT_ASSERT(cfg != RT_NULL);
    uart = (struct yc3121_uart *)serial->parent.user_data;
    NVIC_DisableIRQ(uart->irq);
    UART_initStruct.BaudRate = cfg->baud_rate;
    UART_initStruct.FlowCtrl = FlowCtrl_None ;
    UART_initStruct.Mode = Mode_duplex;

    switch (cfg->data_bits)
    {
    case DATA_BITS_9:
        UART_initStruct.DataBits = Databits_9b;
        break;
    default:
        UART_initStruct.DataBits = Databits_8b;
        break;
    }
    switch (cfg->stop_bits)
    {
    case STOP_BITS_2:
        UART_initStruct.StopBits = StopBits_2;
        break;
    default:
        UART_initStruct.StopBits = StopBits_1;
        break;
    }
    switch (cfg->parity)
    {
    case PARITY_ODD:
        UART_initStruct.Parity = Parity_Odd;
        break;
    case PARITY_EVEN:
        UART_initStruct.Parity = Parity_Even;
        break;
    default:
        UART_initStruct.Parity = Parity_None;
        break;
    }
    UART_Init(uart->uart, &UART_initStruct);
    return RT_EOK;
}

static rt_err_t yc3121_uart_control(struct rt_serial_device *serial,
                              int cmd, void *arg)
{
    struct yc3121_uart *uart;
    RT_ASSERT(serial != RT_NULL);
    uart = (struct yc3121_uart *)serial->parent.user_data;
    switch (cmd)
    {
    case RT_DEVICE_CTRL_CLR_INT:
        /* disable rx irq */
        UART_SetRxITNum(uart->uart, 0);
        NVIC_DisableIRQ(uart->irq);
        break;
    case RT_DEVICE_CTRL_SET_INT:
        /* enable rx irq */
        UART_SetRxITNum(uart->uart, 1);
        UART_ITConfig(uart->uart, UART_IT_RX, ENABLE);
        NVIC_EnableIRQ(uart->irq);
        break;
    }
    return RT_EOK;
}

static int yc3121_uart_putc(struct rt_serial_device *serial, char c)
{
    struct yc3121_uart *uart;
    RT_ASSERT(serial != RT_NULL);
    uart = (struct yc3121_uart *)serial->parent.user_data;
    while (UART_IsUARTBusy(uart->uart));
    UART_SendData(uart->uart, c);
    return 1;
}

static int yc3121_uart_getc(struct rt_serial_device *serial)
{
    int ch;
    struct yc3121_uart *uart;
    RT_ASSERT(serial != RT_NULL);
    uart = (struct yc3121_uart *)serial->parent.user_data;
    ch = -1;
    if (UART_ReceiveDataLen(uart->uart) != 0)
    {
        ch = UART_ReceiveData(uart->uart);
    }
    return ch;
}

static const struct rt_uart_ops yc3121_uart_ops =
{
    yc3121_uart_configure,
    yc3121_uart_control,
    yc3121_uart_putc,
    yc3121_uart_getc,
};

#if defined(BSP_USING_UART0)
/* UART0 device driver structure */
static struct yc3121_uart uart0;
static struct rt_serial_device serial0;
void UART0_IRQHandler(void)
{
    /* enter interrupt */
    rt_interrupt_enter();

    /* UART in mode Receiver */
    if (UART_GetITIdentity(uart0.uart) == UART_IT_RX)
    {
        rt_hw_serial_isr(&serial0, RT_SERIAL_EVENT_RX_IND);
    }
    /* leave interrupt */
    rt_interrupt_leave();
}
#endif /* BSP_USING_UART0 */

#if defined(BSP_USING_UART1)
/* UART1 device driver structure */
static struct yc3121_uart uart1;
static struct rt_serial_device serial1;
void UART1_IRQHandler(void)
{
    /* enter interrupt */
    rt_interrupt_enter();

    /* UART in mode Receiver */
    if (UART_GetITIdentity(uart1.uart) == UART_IT_RX)
    {
        rt_hw_serial_isr(&serial1, RT_SERIAL_EVENT_RX_IND);
    }
    /* leave interrupt */
    rt_interrupt_leave();
}
#endif /* BSP_USING_UART1 */

int rt_hw_uart_init(void)
{
    struct yc3121_uart *uart;
    struct serial_configure config = RT_SERIAL_CONFIG_DEFAULT;
#ifdef BSP_USING_UART0

    GPIO_CONFIG(1) = UART0_TXD;
    GPIO_CONFIG(0) = UART0_RXD;
    uart = &uart0;
    uart->uart = UART0;
    uart->irq = UART0_IRQn;
    serial0.ops = &yc3121_uart_ops;
    serial0.config = config;
    /* register UART0 device */
    rt_hw_serial_register(&serial0, RT_CONSOLE_DEVICE_NAME,
                          RT_DEVICE_FLAG_RDWR | RT_DEVICE_FLAG_INT_RX,
                          uart);
#endif /* BSP_USING_UART0 */
#ifdef BSP_USING_UART1
    GPIO_CONFIG(1) = UART1_TXD;
    GPIO_CONFIG(0) = UART1_RXD;
    uart = &uart1;
    uart->uart = UART1;
    uart->irq = UART1_IRQn;
    serial1.ops = &yc3121_uart_ops;
    serial1.config = config;
    /* register UART1 device */
    rt_hw_serial_register(&serial1, "uart1",
                          RT_DEVICE_FLAG_RDWR | RT_DEVICE_FLAG_INT_RX,
                          uart);
#endif /* BSP_USING_UART1 */
    return 0;
}
