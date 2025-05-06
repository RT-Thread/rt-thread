/*
 * Copyright (c) 2022-2025, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2025-01-22     chasel   first version
 */
#include "board.h"
#include <mm32_device.h>
#include <rtdevice.h>
#include "drv_uart.h"
#include <hal_gpio.h>
#include <hal_uart.h>
#include <hal_rcc.h>
#include <hal_misc.h>

/* uart driver */
struct mm32_uart
{
    UART_TypeDef *uart;
    IRQn_Type irq;
};

static rt_err_t mm32_uart_configure(struct rt_serial_device *serial, struct serial_configure *cfg)
{
    struct mm32_uart *uart;
    UART_InitTypeDef UART_InitStructure;
    RT_ASSERT(serial != RT_NULL);
    RT_ASSERT(cfg != RT_NULL);
    uart = (struct mm32_uart *)serial->parent.user_data;
    UART_InitStructure.BaudRate = cfg->baud_rate;
    if (cfg->data_bits == DATA_BITS_8)
        UART_InitStructure.WordLength = UART_WordLength_8b;
    if (cfg->stop_bits == STOP_BITS_1)
        UART_InitStructure.StopBits = UART_StopBits_1;
    else if (cfg->stop_bits == STOP_BITS_2)
        UART_InitStructure.StopBits = UART_StopBits_2;
    UART_InitStructure.Parity = UART_Parity_No;
    UART_InitStructure.HWFlowControl = UART_HWFlowControl_None;
    UART_InitStructure.Mode = UART_Mode_Rx | UART_Mode_Tx;
    UART_Init(uart->uart, &UART_InitStructure);

    /* Enable UART */
    UART_Cmd(uart->uart, ENABLE);

    return RT_EOK;
}

static rt_err_t mm32_uart_control(struct rt_serial_device *serial, int cmd, void *arg)
{
    struct mm32_uart *uart;
    RT_ASSERT(serial != RT_NULL);
    uart = (struct mm32_uart *)serial->parent.user_data;
    switch (cmd)
    {
    case RT_DEVICE_CTRL_CLR_INT:
        /* disable rx irq */
        NVIC_DisableIRQ(uart->irq);
        UART_ITConfig(uart->uart, UART_IT_RX, DISABLE);
        break;
    case RT_DEVICE_CTRL_SET_INT:
        /* enable rx irq */
        NVIC_EnableIRQ(uart->irq);
        /* enable interrupt */
        UART_ITConfig(uart->uart, UART_IT_RX, ENABLE);
        break;
    }
    return RT_EOK;
}

static int mm32_uart_putc(struct rt_serial_device *serial, char c)
{
    struct mm32_uart *uart;
    RT_ASSERT(serial != RT_NULL);
    uart = (struct mm32_uart *)serial->parent.user_data;
    while ((uart->uart->CSR & UART_CSR_TXC_Msk) == 0)
        ;
    uart->uart->TDR = c;
    return 1;
}

static int mm32_uart_getc(struct rt_serial_device *serial)
{
    int ch;
    struct mm32_uart *uart;
    RT_ASSERT(serial != RT_NULL);
    uart = (struct mm32_uart *)serial->parent.user_data;
    ch = -1;
    if (uart->uart->CSR & UART_FLAG_RXAVL)
    {
        ch = uart->uart->RDR & 0xff;
    }
    return ch;
}

static const struct rt_uart_ops mm32_uart_ops =
{
    mm32_uart_configure,
    mm32_uart_control,
    mm32_uart_putc,
    mm32_uart_getc,
};

#if defined(BSP_USING_UART1)
/* UART1 device driver structure */
static struct mm32_uart uart1;
struct rt_serial_device serial1;
void UART1_IRQHandler(void)
{
    struct mm32_uart *uart;
    uart = &uart1;
    /* enter interrupt */
    rt_interrupt_enter();
    if (UART_GetITStatus(uart->uart, UART_IT_RX) != RESET)
    {
        UART_ClearITPendingBit(uart->uart, UART_IT_RX);
        rt_hw_serial_isr(&serial1, RT_SERIAL_EVENT_RX_IND);
    }
    if (UART_GetITStatus(uart->uart, UART_IT_TX) != RESET)
    {
        /* clear interrupt */
        UART_ClearITPendingBit(uart->uart, UART_IT_TX);
    }
    /* leave interrupt */
    rt_interrupt_leave();
}
#endif /* BSP_USING_UART1 */

#if defined(BSP_USING_UART2)
/* UART2 device driver structure */
static struct mm32_uart uart2;
struct rt_serial_device serial2;
void UART2_IRQHandler(void)
{
    struct mm32_uart *uart;
    uart = &uart2;
    /* enter interrupt */
    rt_interrupt_enter();
    if (UART_GetITStatus(uart->uart, UART_IT_RX) != RESET)
    {
        UART_ClearITPendingBit(uart->uart, UART_IT_RX);
        rt_hw_serial_isr(&serial2, RT_SERIAL_EVENT_RX_IND);
    }
    if (UART_GetITStatus(uart->uart, UART_IT_TX) != RESET)
    {
        /* clear interrupt */
        UART_ClearITPendingBit(uart->uart, UART_IT_TX);
    }
    /* leave interrupt */
    rt_interrupt_leave();
}
#endif /* BSP_USING_UART2 */

#if defined(BSP_USING_UART3)
/* UART3 device driver structure */
static struct mm32_uart uart3;
struct rt_serial_device serial3;
void UART3_IRQHandler(void)
{
    struct mm32_uart *uart;
    uart = &uart3;
    /* enter interrupt */
    rt_interrupt_enter();
    if (UART_GetITStatus(uart->uart, UART_IT_RX) != RESET)
    {
        UART_ClearITPendingBit(uart->uart, UART_IT_RX);
        rt_hw_serial_isr(&serial3, RT_SERIAL_EVENT_RX_IND);
    }
    if (UART_GetITStatus(uart->uart, UART_IT_TX) != RESET)
    {
        /* clear interrupt */
        UART_ClearITPendingBit(uart->uart, UART_IT_TX);
    }
    /* leave interrupt */
    rt_interrupt_leave();
}
#endif /* BSP_USING_UART3 */

int rt_hw_uart_init(void)
{
    struct mm32_uart *uart;
    struct serial_configure config = RT_SERIAL_CONFIG_DEFAULT;
#ifdef BSP_USING_UART1
    mm32_msp_uart_init((void *)UART1);

    uart = &uart1;
    uart->uart = UART1;
    uart->irq = UART1_IRQn;
    config.baud_rate = BAUD_RATE_115200;
    serial1.ops = &mm32_uart_ops;
    serial1.config = config;
    /* register UART1 device */
    rt_hw_serial_register(&serial1, "uart1",
                          RT_DEVICE_FLAG_RDWR | RT_DEVICE_FLAG_INT_RX,
                          uart);
#endif /* BSP_USING_UART1 */

#ifdef BSP_USING_UART2
    mm32_msp_uart_init((void *)UART2);

    uart = &uart2;
    uart->uart = UART2;
    uart->irq = UART2_IRQn;
    config.baud_rate = BAUD_RATE_115200;
    serial2.ops = &mm32_uart_ops;
    serial2.config = config;
    /* register UART2 device */
    rt_hw_serial_register(&serial2, "uart2",
                          RT_DEVICE_FLAG_RDWR | RT_DEVICE_FLAG_INT_RX,
                          uart);
#endif /* BSP_USING_UART2 */

#ifdef BSP_USING_UART3
    mm32_msp_uart_init((void *)UART3);

    uart = &uart3;
    uart->uart = UART3;
    uart->irq = UART3_IRQn;
    config.baud_rate = BAUD_RATE_115200;
    serial3.ops = &mm32_uart_ops;
    serial3.config = config;
    /* register UART2 device */
    rt_hw_serial_register(&serial3, "uart3",
                          RT_DEVICE_FLAG_RDWR | RT_DEVICE_FLAG_INT_RX,
                          uart);
#endif /* BSP_USING_UART3 */

    return 0;
}
