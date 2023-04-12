/*
 * Copyright (c) 2006-2022, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2022-02-22     airm2m       first version
 */

#include <rtthread.h>
#include <rtdevice.h>
#include "board.h"
#include "drv_usart.h"

#ifdef RT_USING_SERIAL

#define LOG_TAG             "drv.usart"
#include <drv_log.h>

#if !defined(BSP_USING_UART1) && !defined(BSP_USING_UART2) && !defined(BSP_USING_UART3) && \
    !defined(BSP_USING_UART4) && !defined(BSP_USING_UART5) && !defined(BSP_USING_UART6) && \
    !defined(BSP_USING_UART7) && !defined(BSP_USING_UART8)
#error "Please define at least one BSP_USING_UARTx"
/* this driver can be disabled at menuconfig -> RT-Thread Components -> Device Drivers */
#endif

/* air32 config class */
struct air32_uart_config
{
    const char *name;
    USART_TypeDef *Instance;
    IRQn_Type irq_type;
};

/* air32 uart dirver class */
struct air32_uart
{
    USART_InitTypeDef Init;
    struct air32_uart_config *config;
    struct rt_serial_device serial;
};

#if defined(BSP_USING_UART1)
#ifndef UART1_CONFIG
#define UART1_CONFIG                                                \
    {                                                               \
        .name = "uart1",                                            \
        .Instance = USART1,                                         \
        .irq_type = USART1_IRQn,                                    \
    }
#endif /* UART1_CONFIG */
#endif /* BSP_USING_UART1 */

#if defined(BSP_USING_UART2)
#ifndef UART2_CONFIG
#define UART2_CONFIG                                                \
    {                                                               \
        .name = "uart2",                                            \
        .Instance = USART2,                                         \
        .irq_type = USART2_IRQn,                                    \
    }
#endif /* UART2_CONFIG */
#endif /* BSP_USING_UART2 */

#if defined(BSP_USING_UART3)
#ifndef UART3_CONFIG
#define UART3_CONFIG                                                \
    {                                                               \
        .name = "uart3",                                            \
        .Instance = USART3,                                         \
        .irq_type = USART3_IRQn,                                    \
    }
#endif /* UART3_CONFIG */
#endif /* BSP_USING_UART3 */


enum
{
#ifdef BSP_USING_UART1
    UART1_INDEX,
#endif
#ifdef BSP_USING_UART2
    UART2_INDEX,
#endif
#ifdef BSP_USING_UART3
    UART3_INDEX,
#endif
#ifdef BSP_USING_UART4
    UART4_INDEX,
#endif
#ifdef BSP_USING_UART5
    UART5_INDEX,
#endif
#ifdef BSP_USING_UART6
    UART6_INDEX,
#endif
#ifdef BSP_USING_UART7
    UART7_INDEX,
#endif
#ifdef BSP_USING_UART8
    UART8_INDEX,
#endif
};

static struct air32_uart_config uart_config[] =
{
#ifdef BSP_USING_UART1
    UART1_CONFIG,
#endif
#ifdef BSP_USING_UART2
    UART2_CONFIG,
#endif
#ifdef BSP_USING_UART3
    UART3_CONFIG,
#endif
#ifdef BSP_USING_UART4
    UART4_CONFIG,
#endif
#ifdef BSP_USING_UART5
    UART5_CONFIG,
#endif
#ifdef BSP_USING_UART6
    UART6_CONFIG,
#endif
#ifdef BSP_USING_UART7
    UART7_CONFIG,
#endif
#ifdef BSP_USING_UART8
    UART8_CONFIG,
#endif
};

static struct air32_uart uart_obj[sizeof(uart_config) / sizeof(uart_config[0])] = {0};

static rt_err_t air32_configure(struct rt_serial_device *serial, struct serial_configure *cfg)
{
    struct air32_uart *uart;
    RT_ASSERT(serial != RT_NULL);
    RT_ASSERT(cfg != RT_NULL);

    uart = rt_container_of(serial, struct air32_uart, serial);

    air32_usart_clock_and_io_init(uart->config->Instance);
    USART_StructInit(&uart->Init);

    uart->Init.USART_BaudRate     = cfg->baud_rate;
    uart->Init.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
    uart->Init.USART_Mode         = USART_Mode_Rx | USART_Mode_Tx;

    switch (cfg->flowcontrol)
    {
    case RT_SERIAL_FLOWCONTROL_NONE:
        uart->Init.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
        break;
    case RT_SERIAL_FLOWCONTROL_CTSRTS:
        uart->Init.USART_HardwareFlowControl = USART_HardwareFlowControl_RTS_CTS;
        break;
    default:
        uart->Init.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
        break;
    }

    switch (cfg->data_bits)
    {
    case DATA_BITS_8:
        if (cfg->parity == PARITY_ODD || cfg->parity == PARITY_EVEN)
            uart->Init.USART_WordLength = USART_WordLength_9b;
        else
            uart->Init.USART_WordLength = USART_WordLength_8b;
        break;
    case DATA_BITS_9:
        uart->Init.USART_WordLength = USART_WordLength_9b;
        break;
    default:
        uart->Init.USART_WordLength = USART_WordLength_8b;
        break;
    }

    switch (cfg->stop_bits)
    {
    case STOP_BITS_1:
        uart->Init.USART_StopBits   = USART_StopBits_1;
        break;
    case STOP_BITS_2:
        uart->Init.USART_StopBits   = USART_StopBits_2;
        break;
    default:
        uart->Init.USART_StopBits   = USART_StopBits_1;
        break;
    }

    switch (cfg->parity)
    {
    case PARITY_NONE:
        uart->Init.USART_Parity     = USART_Parity_No;
        break;
    case PARITY_ODD:
        uart->Init.USART_Parity     = USART_Parity_Odd;
        break;
    case PARITY_EVEN:
        uart->Init.USART_Parity     = USART_Parity_Even;
        break;
    default:
        uart->Init.USART_Parity     = USART_Parity_No;
        break;
    }

    USART_Init(uart->config->Instance, &uart->Init);
    USART_Cmd(uart->config->Instance, ENABLE);

    return RT_EOK;
}

static rt_err_t air32_control(struct rt_serial_device *serial, int cmd, void *arg)
{
    struct air32_uart *uart;
    NVIC_InitTypeDef NVIC_InitStruct;

    RT_ASSERT(serial != RT_NULL);
    uart = rt_container_of(serial, struct air32_uart, serial);

    NVIC_InitStruct.NVIC_IRQChannel = uart->config->irq_type;
    NVIC_InitStruct.NVIC_IRQChannelPreemptionPriority = 2;
    NVIC_InitStruct.NVIC_IRQChannelSubPriority = 1;

    switch (cmd)
    {
    /* disable interrupt */
    case RT_DEVICE_CTRL_CLR_INT:
        /* disable rx irq */
        // NVIC_DisableIRQ(uart->config->irq_type);
        NVIC_InitStruct.NVIC_IRQChannelCmd = DISABLE;
        NVIC_Init(&NVIC_InitStruct);
        /* disable interrupt */
        USART_ITConfig(uart->config->Instance,USART_IT_RXNE,DISABLE);

        break;

    /* enable interrupt */
    case RT_DEVICE_CTRL_SET_INT:
        /* enable rx irq */
        // NVIC_EnableIRQ(uart->config->irq_type);
        NVIC_InitStruct.NVIC_IRQChannelCmd = ENABLE;
        NVIC_Init(&NVIC_InitStruct);
        /* enable interrupt */
        USART_ITConfig(uart->config->Instance, USART_IT_RXNE,ENABLE);
        break;
    }

    return RT_EOK;
}

static int air32_putc(struct rt_serial_device *serial, char c)
{
    struct air32_uart *uart;
    RT_ASSERT(serial != RT_NULL);
    uart = rt_container_of(serial, struct air32_uart, serial);
    while (USART_GetFlagStatus(uart->config->Instance, USART_FLAG_TXE) == RESET);
    USART_SendData(uart->config->Instance, (uint8_t)c);
    return 1;
}

static int air32_getc(struct rt_serial_device *serial)
{
    int ch;
    struct air32_uart *uart;
    RT_ASSERT(serial != RT_NULL);
    uart = rt_container_of(serial, struct air32_uart, serial);
    ch = -1;
    if (RESET != USART_GetFlagStatus(uart->config->Instance, USART_FLAG_RXNE))
    {
        ch = USART_ReceiveData(uart->config->Instance) & 0xff;
    }
    return ch;
}

static rt_ssize_t air32_dma_transmit(struct rt_serial_device *serial, rt_uint8_t *buf, rt_size_t size, int direction)
{
    return 0;
}


/**
 * Uart common interrupt process. This need add to uart ISR.
 *
 * @param serial serial device
 */
static void uart_isr(struct rt_serial_device *serial)
{
    struct air32_uart *uart;

    RT_ASSERT(serial != RT_NULL);
    uart = rt_container_of(serial, struct air32_uart, serial);

    /* UART in mode Receiver -------------------------------------------------*/

    if ((USART_GetITStatus(uart->config->Instance, USART_IT_RXNE) != RESET) && (RESET != USART_GetFlagStatus(uart->config->Instance, USART_FLAG_RXNE)))
    {
        rt_hw_serial_isr(serial, RT_SERIAL_EVENT_RX_IND);
        USART_ClearITPendingBit(uart->config->Instance, USART_IT_RXNE);
        USART_ClearFlag(uart->config->Instance, USART_FLAG_RXNE);
    }
    else
    {
        if (USART_GetFlagStatus(uart->config->Instance, USART_FLAG_CTS) != RESET)
        {
            USART_ClearFlag(uart->config->Instance, USART_FLAG_CTS);
        }

        if (USART_GetFlagStatus(uart->config->Instance, USART_FLAG_LBD) != RESET)
        {
            USART_ClearFlag(uart->config->Instance, USART_FLAG_LBD);
        }

        if (USART_GetFlagStatus(uart->config->Instance, USART_FLAG_TC) != RESET)
        {
            USART_ClearFlag(uart->config->Instance, USART_FLAG_TC);
        }
    }

}

#if defined(BSP_USING_UART1)
void USART1_IRQHandler(void)
{
    /* enter interrupt */
    rt_interrupt_enter();

    uart_isr(&(uart_obj[UART1_INDEX].serial));

    /* leave interrupt */
    rt_interrupt_leave();
}
#endif /* BSP_USING_UART1 */

#if defined(BSP_USING_UART2)
void USART2_IRQHandler(void)
{
    /* enter interrupt */
    rt_interrupt_enter();

    uart_isr(&(uart_obj[UART2_INDEX].serial));

    /* leave interrupt */
    rt_interrupt_leave();
}
#endif /* BSP_USING_UART2 */

#if defined(BSP_USING_UART3)
void USART3_IRQHandler(void)
{
    /* enter interrupt */
    rt_interrupt_enter();

    uart_isr(&(uart_obj[UART3_INDEX].serial));

    /* leave interrupt */
    rt_interrupt_leave();
}
#endif /* BSP_USING_UART3*/

#if defined(BSP_USING_UART4)
void UART4_IRQHandler(void)
{
    /* enter interrupt */
    rt_interrupt_enter();

    uart_isr(&(uart_obj[UART4_INDEX].serial));

    /* leave interrupt */
    rt_interrupt_leave();
}
#endif /* BSP_USING_UART4*/

#if defined(BSP_USING_UART5)
void UART5_IRQHandler(void)
{
    /* enter interrupt */
    rt_interrupt_enter();

    uart_isr(&(uart_obj[UART5_INDEX].serial));

    /* leave interrupt */
    rt_interrupt_leave();
}
#endif /* BSP_USING_UART5*/

#if defined(BSP_USING_UART6)
void USART6_IRQHandler(void)
{
    /* enter interrupt */
    rt_interrupt_enter();

    uart_isr(&(uart_obj[UART6_INDEX].serial));

    /* leave interrupt */
    rt_interrupt_leave();
}
#endif /* BSP_USING_UART6*/

#if defined(BSP_USING_UART7)
void UART7_IRQHandler(void)
{
    /* enter interrupt */
    rt_interrupt_enter();

    uart_isr(&(uart_obj[UART7_INDEX].serial));

    /* leave interrupt */
    rt_interrupt_leave();
}
#endif /* BSP_USING_UART7*/

#if defined(BSP_USING_UART8)
void UART8_IRQHandler(void)
{
    /* enter interrupt */
    rt_interrupt_enter();

    uart_isr(&(uart_obj[UART8_INDEX].serial));

    /* leave interrupt */
    rt_interrupt_leave();
}
#endif /* BSP_USING_UART8*/

static const struct rt_uart_ops air32_uart_ops =
{
    .configure = air32_configure,
    .control = air32_control,
    .putc = air32_putc,
    .getc = air32_getc,
    .dma_transmit = air32_dma_transmit
};

int rt_hw_usart_init(void)
{
    struct serial_configure config = RT_SERIAL_CONFIG_DEFAULT;
    rt_err_t result = 0;

    for (rt_size_t i = 0; i < sizeof(uart_obj) / sizeof(struct air32_uart); i++)
    {
        /* init UART object */
        uart_obj[i].config = &uart_config[i];
        uart_obj[i].serial.ops    = &air32_uart_ops;
        uart_obj[i].serial.config = config;

        /* register UART device */
        result = rt_hw_serial_register(&uart_obj[i].serial, uart_obj[i].config->name,
                                       RT_DEVICE_FLAG_RDWR
                                       | RT_DEVICE_FLAG_INT_RX
                                       | RT_DEVICE_FLAG_INT_TX
                                       , RT_NULL);
        RT_ASSERT(result == RT_EOK);
    }

    return result;
}

#endif /* RT_USING_SERIAL */
