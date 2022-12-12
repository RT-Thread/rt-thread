/*
 * Copyright (c) 2006-2022, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author            Notes
 * 2021-01-04     iysheng           first version
 * 2021-09-07     FuC               Suit for V85xx
 * 2021-09-12     ZhuXW             Suit for V85xxP
 */

#include <target.h>
#include <drv_usart.h>
#include <board.h>

#ifdef RT_USING_SERIAL

#if !defined(BSP_USING_UART0) && !defined(BSP_USING_UART1) && \
    !defined(BSP_USING_UART2) && !defined(BSP_USING_UART3) && \
    !defined(BSP_USING_UART4) && !defined(BSP_USING_UART5)
    #error "Please define at least one UARTx"

#endif

#include <rtdevice.h>

static void uart_isr(struct rt_serial_device *serial);

#if defined(BSP_USING_UART0)
struct rt_serial_device serial0;

void UART0_IRQHandler(void)
{
    /* enter interrupt */
    rt_interrupt_enter();

    uart_isr(&serial0);

    /* leave interrupt */
    rt_interrupt_leave();
}

#endif /* BSP_USING_UART0 */

#if defined(BSP_USING_UART1)
struct rt_serial_device serial1;

void UART1_IRQHandler(void)
{
    /* enter interrupt */
    rt_interrupt_enter();

    uart_isr(&serial1);

    /* leave interrupt */
    rt_interrupt_leave();
}

#endif /* BSP_USING_UART1 */

#if defined(BSP_USING_UART2)
struct rt_serial_device serial2;

void UART2_IRQHandler(void)
{
    /* enter interrupt */
    rt_interrupt_enter();

    uart_isr(&serial2);

    /* leave interrupt */
    rt_interrupt_leave();
}

#endif /* BSP_USING_UART2 */

#if defined(BSP_USING_UART3)
struct rt_serial_device serial3;

void UART3_IRQHandler(void)
{
    /* enter interrupt */
    rt_interrupt_enter();

    uart_isr(&serial3);

    /* leave interrupt */
    rt_interrupt_leave();
}

#endif /* BSP_USING_UART3 */

#if defined(BSP_USING_UART4)
struct rt_serial_device serial4;

void UART4_IRQHandler(void)
{
    /* enter interrupt */
    rt_interrupt_enter();

    uart_isr(&serial4);

    /* leave interrupt */
    rt_interrupt_leave();
}
#endif /* BSP_USING_UART4 */

#if defined(BSP_USING_UART5)
struct rt_serial_device serial5;

void UART5_IRQHandler(void)
{
    /* enter interrupt */
    rt_interrupt_enter();

    uart_isr(&serial5);

    /* leave interrupt */
    rt_interrupt_leave();
}
#endif /* BSP_USING_UART4 */

static const struct V85xxP_uart uarts[] =
{
#ifdef BSP_USING_UART0
    {
        UART0,                             /* uart peripheral index */
        UART0_IRQn,                        /* uart iqrn */
        &serial0,
        "uart0",
    },
#endif

#ifdef BSP_USING_UART1
    {
        UART1,                             /* uart peripheral index */
        UART1_IRQn,                        /* uart iqrn */
        &serial1,
        "uart1",
    },
#endif

#ifdef BSP_USING_UART2
    {
        UART2,                             /* uart peripheral index */
        UART2_IRQn,                        /* uart iqrn */
        &serial2,
        "uart2",
    },
#endif

#ifdef BSP_USING_UART3
    {
        UART3,                              /* uart peripheral index */
        UART3_IRQn,                         /* uart iqrn */
        &serial3,
        "uart3",
    },
#endif

#ifdef BSP_USING_UART4
    {
        UART4,                              /* uart peripheral index */
        UART4_IRQn,                         /* uart iqrn */
        &serial4,
        "uart4",
    },
#endif

#ifdef BSP_USING_UART5
    {
        UART5,                              /* uart peripheral index */
        UART5_IRQn,                         /* uart iqrn */
        &serial5,
        "uart5",
    },
#endif
};

static rt_err_t V85xxP_configure(struct rt_serial_device *serial, struct serial_configure *cfg)
{
    struct V85xxP_uart *uart;
    UART_Type *UARTx;
    UART_InitType UART_InitParaStruct = {0};

    UART_StructInit(&UART_InitParaStruct);
    RT_ASSERT(serial != RT_NULL);
    RT_ASSERT(cfg != RT_NULL);

    uart = (struct V85xxP_uart *)serial->parent.user_data;

    UARTx = (UART_Type *)uart->uart_periph;
    UART_InitParaStruct.Baudrate = cfg->baud_rate;

    if (cfg->data_bits == DATA_BITS_8)
    {
        UART_InitParaStruct.Parity = UART_PARITY_NONE;
    }

    switch (cfg->parity)
    {
    case PARITY_ODD:
        UART_InitParaStruct.Parity = UART_PARITY_ODD;
        break;
    case PARITY_EVEN:
        UART_InitParaStruct.Parity = UART_PARITY_EVEN;
        break;
    default:
        UART_InitParaStruct.Parity = UART_PARITY_NONE;
        break;
    }

    UART_InitParaStruct.Mode = UART_MODE_RX | UART_MODE_TX;
    UART_Init(UARTx, &UART_InitParaStruct);
    UART_Cmd(UARTx, UART_InitParaStruct.Mode, ENABLE);

    return RT_EOK;
}

static rt_err_t V85xxP_control(struct rt_serial_device *serial, int cmd, void *arg)
{
    struct V85xxP_uart *uart;
    UART_Type *UARTx;

    RT_ASSERT(serial != RT_NULL);
    uart = (struct V85xxP_uart *)serial->parent.user_data;
    UARTx = (UART_Type *)uart->uart_periph;

    switch (cmd)
    {
    case RT_DEVICE_CTRL_CLR_INT:
        /* disable rx irq */
        NVIC_DisableIRQ(uart->irqn);
        /* disable interrupt */
        UART_INTConfig(UARTx, UART_INT_RX, DISABLE);
        break;
    case RT_DEVICE_CTRL_SET_INT:
        /* enable rx irq */
        NVIC_EnableIRQ(uart->irqn);
        /* enable interrupt */
        UART_INTConfig(UARTx, UART_INT_RX, ENABLE);
        break;
    }

    return RT_EOK;
}

static int V85xxP_putc(struct rt_serial_device *serial, char ch)
{
    struct V85xxP_uart *uart;

    RT_ASSERT(serial != RT_NULL);
    uart = (struct V85xxP_uart *)serial->parent.user_data;

    UART_SendData((UART_Type *)uart->uart_periph, ch);
    while ((UART_GetFlag((UART_Type *)uart->uart_periph, UART_FLAG_TXDONE) == RESET));
    UART_ClearFlag((UART_Type *)uart->uart_periph, UART_FLAG_TXDONE);
    return 1;
}

static int V85xxP_getc(struct rt_serial_device *serial)
{
    int ch;
    struct V85xxP_uart *uart;

    RT_ASSERT(serial != RT_NULL);
    uart = (struct V85xxP_uart *)serial->parent.user_data;

    ch = -1;
    if (UART_GetFlag((UART_Type *)uart->uart_periph, UART_FLAG_RXFULL) != RESET)
        ch = UART_ReceiveData((UART_Type *)uart->uart_periph);
    return ch;
}

/**
 * Uart common interrupt process. This need add to uart ISR.
 *
 * @param serial serial device
 */
static void uart_isr(struct rt_serial_device *serial)
{
    struct V85xxP_uart *uart = (struct V85xxP_uart *) serial->parent.user_data;

    RT_ASSERT(uart != RT_NULL);

    if ((UART_GetINTStatus((UART_Type *)uart->uart_periph, UART_INTSTS_RX) != RESET) &&
            (UART_GetFlag((UART_Type *)uart->uart_periph, UART_FLAG_RXFULL) != RESET))
    {
        rt_hw_serial_isr(serial, RT_SERIAL_EVENT_RX_IND);
        /* Clear RXNE interrupt flag */
        UART_ClearINTStatus((UART_Type *)uart->uart_periph, UART_INTSTS_RX);
    }
}

static const struct rt_uart_ops V85xxP_uart_ops =
{
    V85xxP_configure,
    V85xxP_control,
    V85xxP_putc,
    V85xxP_getc,
};

int V85xxP_hw_usart_init(void)
{
    struct serial_configure config = RT_SERIAL_CONFIG_DEFAULT;
    int i;


    for (i = 0; i < sizeof(uarts) / sizeof(uarts[0]); i++)
    {
        uarts[i].serial->ops    = &V85xxP_uart_ops;
        uarts[i].serial->config = config;

        /* register UART device */
        rt_hw_serial_register(uarts[i].serial,
                              uarts[i].device_name,
                              RT_DEVICE_FLAG_RDWR | RT_DEVICE_FLAG_INT_RX,
                              (void *)&uarts[i]);
    }

    return 0;
}
INIT_BOARD_EXPORT(V85xxP_hw_usart_init);
#endif
