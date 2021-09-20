/*
 * Copyright (c) 2006-2021, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2021-08-20     BruceOu      first implementation
 */
#include "drv_usart.h"
#include <board.h>

#ifdef RT_USING_SERIAL

#if !defined(BSP_USING_UART0) && !defined(BSP_USING_UART1) && \
    !defined(BSP_USING_UART2) && !defined(BSP_USING_UART3) && \
    !defined(BSP_USING_UART4) && !defined(BSP_USING_UART5) && \
    !defined(BSP_USING_UART6) && !defined(BSP_USING_UART7)
#error "Please define at least one UARTx"

#endif

#include <rtdevice.h>

/* GD32 uart driver */
// Todo: compress uart info
struct gd32_uart
{
    uint32_t uart_periph;           //Todo: 3bits
    IRQn_Type irqn;                 //Todo: 7bits
    rcu_periph_enum per_clk;        //Todo: 5bits

    struct rt_serial_device * serial;
    char *device_name;
};

static void uart_isr(struct rt_serial_device *serial);

#if defined(BSP_USING_UART0)
struct rt_serial_device serial0;

void USART0_IRQHandler(void)
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

void USART1_IRQHandler(void)
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

void USART2_IRQHandler(void)
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

void USART5_IRQHandler(void)
{
    /* enter interrupt */
    rt_interrupt_enter();

    uart_isr(&serial5);

    /* leave interrupt */
    rt_interrupt_leave();
}

#endif /* BSP_USING_UART5 */

#if defined(BSP_USING_UART6)
struct rt_serial_device serial6;

void UART6_IRQHandler(void)
{
    /* enter interrupt */
    rt_interrupt_enter();

    uart_isr(&serial6);

    /* leave interrupt */
    rt_interrupt_leave();
}

#endif /* BSP_USING_UART6 */

#if defined(BSP_USING_UART7)
struct rt_serial_device serial7;

void UART7_IRQHandler(void)
{
    /* enter interrupt */
    rt_interrupt_enter();

    uart_isr(&serial7);

    /* leave interrupt */
    rt_interrupt_leave();
}

#endif /* BSP_USING_UART7 */

static const struct gd32_uart uarts[] = {
    #ifdef BSP_USING_UART0
    {
        USART0,                                 // uart peripheral index
        USART0_IRQn,                            // uart iqrn
        RCU_USART0,
        &serial0,
        "uart0",
    },
    #endif

    #ifdef BSP_USING_UART1
    {
        USART1,                                 // uart peripheral index
        USART1_IRQn,                            // uart iqrn
        RCU_USART1,
        &serial1,
        "uart1",
    },
    #endif

    #ifdef BSP_USING_UART2
    {
        USART2,                                 // uart peripheral index
        USART2_IRQn,                            // uart iqrn
        RCU_USART2,
        &serial2,
        "uart2",
    },
    #endif

    #ifdef BSP_USING_UART3
    {
        UART3,                                 // uart peripheral index
        UART3_IRQn,                            // uart iqrn
        RCU_UART3,
        &serial3,
        "uart3",
    },
    #endif

    #ifdef BSP_USING_UART4
    {
        UART4,                                 // uart peripheral index
        UART4_IRQn,                            // uart iqrn
        RCU_UART4,
        &serial4,
        "uart4",
    },
    #endif

    #ifdef BSP_USING_UART5
    {
        USART5,                                 // uart peripheral index
        USART5_IRQn,                            // uart iqrn
        RCU_USART5,
        &serial5,
        "uart5",
    },
    #endif

    #ifdef BSP_USING_UART6
    {
        UART6,                                 // uart peripheral index
        UART6_IRQn,                            // uart iqrn
        RCU_UART6,
        &serial6,
        "uart6",
    },
    #endif

    #ifdef BSP_USING_UART7
    {
        UART7,                                 // uart peripheral index
        UART7_IRQn,                            // uart iqrn
        RCU_UART7,
        &serial7,
        "uart7",
    },
    #endif
};

static rt_err_t _uart_configure(struct rt_serial_device *serial, struct serial_configure *cfg)
{
    struct gd32_uart *uart;

    RT_ASSERT(serial != RT_NULL);
    RT_ASSERT(cfg != RT_NULL);

    uart = (struct gd32_uart *)serial->parent.user_data;

    rcu_periph_clock_enable(uart->per_clk);

    NVIC_SetPriority(uart->irqn, 0);
    NVIC_EnableIRQ(uart->irqn);

    usart_baudrate_set(uart->uart_periph, cfg->baud_rate);

    switch (cfg->data_bits)
    {
    case DATA_BITS_9:
        usart_word_length_set(uart->uart_periph, USART_WL_9BIT);
        break;

    default:
        usart_word_length_set(uart->uart_periph, USART_WL_8BIT);
        break;
    }

    switch (cfg->stop_bits)
    {
    case STOP_BITS_2:
        usart_stop_bit_set(uart->uart_periph, USART_STB_2BIT);
        break;
    default:
        usart_stop_bit_set(uart->uart_periph, USART_STB_1BIT);
        break;
    }

    switch (cfg->parity)
    {
    case PARITY_ODD:
        usart_parity_config(uart->uart_periph, USART_PM_ODD);
        break;
    case PARITY_EVEN:
        usart_parity_config(uart->uart_periph, USART_PM_EVEN);
        break;
    default:
        usart_parity_config(uart->uart_periph, USART_PM_NONE);
        break;
    }

    usart_receive_config(uart->uart_periph, USART_RECEIVE_ENABLE);
    usart_transmit_config(uart->uart_periph, USART_TRANSMIT_ENABLE);
    usart_enable(uart->uart_periph);

    return RT_EOK;
}

static rt_err_t _uart_control(struct rt_serial_device *serial, int cmd, void *arg)
{
    struct gd32_uart *uart;

    RT_ASSERT(serial != RT_NULL);
    uart = (struct gd32_uart *)serial->parent.user_data;

    switch (cmd)
    {
    case RT_DEVICE_CTRL_CLR_INT:
        /* disable rx irq */
        NVIC_DisableIRQ(uart->irqn);
        /* disable interrupt */
        usart_interrupt_disable(uart->uart_periph, USART_INT_RBNE);

        break;
    case RT_DEVICE_CTRL_SET_INT:
        /* enable rx irq */
        NVIC_EnableIRQ(uart->irqn);
        /* enable interrupt */
        usart_interrupt_enable(uart->uart_periph, USART_INT_RBNE);
        break;
    }

    return RT_EOK;
}

static int _uart_putc(struct rt_serial_device *serial, char ch)
{
    struct gd32_uart *uart;

    RT_ASSERT(serial != RT_NULL);
    uart = (struct gd32_uart *)serial->parent.user_data;

    usart_data_transmit(uart->uart_periph, ch);
    while((usart_flag_get(uart->uart_periph, USART_FLAG_TC) == RESET));

    return RT_EOK;
}

static int _uart_getc(struct rt_serial_device *serial)
{
    int ch;
    struct gd32_uart *uart;

    RT_ASSERT(serial != RT_NULL);
    uart = (struct gd32_uart *)serial->parent.user_data;

    ch = -1;
    if (usart_flag_get(uart->uart_periph, USART_FLAG_RBNE) != RESET)
        ch = usart_data_receive(uart->uart_periph);
    return ch;
}

/**
 * Uart common interrupt process. This need add to uart ISR.
 *
 * @param serial serial device
 */
static void uart_isr(struct rt_serial_device *serial)
{
    struct gd32_uart *uart = (struct gd32_uart *) serial->parent.user_data;

    RT_ASSERT(uart != RT_NULL);

    /* UART in mode Receiver -------------------------------------------------*/
    if ((usart_interrupt_flag_get(uart->uart_periph, USART_INT_FLAG_RBNE) != RESET) &&
            (usart_flag_get(uart->uart_periph, USART_FLAG_RBNE) != RESET))
    {
        rt_hw_serial_isr(serial, RT_SERIAL_EVENT_RX_IND);
        /* Clear RXNE interrupt flag */
        usart_flag_clear(uart->uart_periph, USART_FLAG_RBNE);
    }
}

static const struct rt_uart_ops gd32_uart_ops =
{
    _uart_configure,
    _uart_control,
    _uart_putc,
    _uart_getc,
};

int gd32_hw_usart_init(void)
{
    struct serial_configure config = RT_SERIAL_CONFIG_DEFAULT;
    int i;

      int result;

    for (i = 0; i < sizeof(uarts) / sizeof(uarts[0]); i++)
    {
        uarts[i].serial->ops    = &gd32_uart_ops;
        uarts[i].serial->config = config;

        /* register UART1 device */
        result = rt_hw_serial_register(uarts[i].serial,
                              uarts[i].device_name,
                              RT_DEVICE_FLAG_RDWR | RT_DEVICE_FLAG_INT_RX,
                              (void *)&uarts[i]);
              RT_ASSERT(result == RT_EOK);
    }

    return result;
}
INIT_BOARD_EXPORT(gd32_hw_usart_init);
#endif
