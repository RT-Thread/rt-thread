/*
 * Copyright (c) 2006-2021, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2021-08-05     mazhiyuan   first version
 */
#include <hal_device.h>
#include <rtdevice.h>
#include "drv_uart.h"
#include <hal_gpio.h>
#include <hal_uart.h>
#include <hal_rcc.h>
#include <hal_misc.h>

/* UART1 */
#define UART1_GPIO_TX GPIO_Pin_9
#define UART1_GPIO_TX_SOURCE GPIO_PinSource9
#define UART1_GPIO_RX GPIO_Pin_10
#define UART1_GPIO_RX_SOURCE GPIO_PinSource10
#define UART1_GPIO_AF GPIO_AF_1
#define UART1_GPIO GPIOA

/* UART2 */
#define UART2_GPIO_TX GPIO_Pin_2
#define UART2_GPIO_TX_SOURCE GPIO_PinSource2
#define UART2_GPIO_RX GPIO_Pin_3
#define UART2_GPIO_RX_SOURCE GPIO_PinSource3
#define UART2_GPIO_AF GPIO_AF_1
#define UART2_GPIO GPIOA

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
    UART_InitStructure.UART_BaudRate = cfg->baud_rate;
    if (cfg->data_bits == DATA_BITS_8)
        UART_InitStructure.UART_WordLength = UART_WordLength_8b;
    if (cfg->stop_bits == STOP_BITS_1)
        UART_InitStructure.UART_StopBits = UART_StopBits_1;
    else if (cfg->stop_bits == STOP_BITS_2)
        UART_InitStructure.UART_StopBits = UART_StopBits_2;
    UART_InitStructure.UART_Parity = UART_Parity_No;
    UART_InitStructure.UART_HardwareFlowControl = UART_HardwareFlowControl_None;
    UART_InitStructure.UART_Mode = UART_Mode_Rx | UART_Mode_Tx;
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
        UART_ITConfig(uart->uart, UART_IT_RXIEN, DISABLE);
        break;
    case RT_DEVICE_CTRL_SET_INT:
        /* enable rx irq */
        NVIC_EnableIRQ(uart->irq);
        /* enable interrupt */
        UART_ITConfig(uart->uart, UART_IT_RXIEN, ENABLE);
        break;
    }
    return RT_EOK;
}

static int mm32_uart_putc(struct rt_serial_device *serial, char c)
{
    struct mm32_uart *uart;
    RT_ASSERT(serial != RT_NULL);
    uart = (struct mm32_uart *)serial->parent.user_data;
    while ((uart->uart->CSR & UART_CSR_TXC) == 0)
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
    if (UART_GetITStatus(uart->uart, UART_IT_RXIEN) != RESET)
    {
        UART_ClearITPendingBit(uart->uart, UART_IT_RXIEN);
        rt_hw_serial_isr(&serial1, RT_SERIAL_EVENT_RX_IND);
    }
    if (UART_GetITStatus(uart->uart, UART_IT_TXIEN) != RESET)
    {
        /* clear interrupt */
        UART_ClearITPendingBit(uart->uart, UART_IT_TXIEN);
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
    if (UART_GetITStatus(uart->uart, UART_IT_RXIEN) != RESET)
    {
        UART_ClearITPendingBit(uart->uart, UART_IT_RXIEN);
        rt_hw_serial_isr(&serial2, RT_SERIAL_EVENT_RX_IND);
    }
    if (UART_GetITStatus(uart->uart, UART_IT_TXIEN) != RESET)
    {
        /* clear interrupt */
        UART_ClearITPendingBit(uart->uart, UART_IT_TXIEN);
    }
    /* leave interrupt */
    rt_interrupt_leave();
}
#endif /* BSP_USING_UART2 */

#ifdef BSP_USING_UART1
static void UART1PINconfigStepA(void)
{
    /* Enable UART clock */
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_UART1, ENABLE);
    RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOA, ENABLE);
}

static void UART1PINconfigStepB(void)
{

    GPIO_InitTypeDef GPIO_InitStructure;
    /* Configure USART Rx/tx PIN */
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
    GPIO_Init(GPIOA, &GPIO_InitStructure);
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;
    GPIO_Init(GPIOA, &GPIO_InitStructure);
    GPIO_PinAFConfig(GPIOA, 9, GPIO_AF_7);
    GPIO_PinAFConfig(GPIOA, 10, GPIO_AF_7);
}
#endif

#ifdef BSP_USING_UART2
static void UART2PINconfigStepA(void)
{
    /* Enable UART clock */
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_UART2, ENABLE);
    RCC_AHB2PeriphClockCmd(RCC_AHBPeriph_GPIOA, ENABLE);
}

static void UART2PINconfigStepB(void)
{
    GPIO_InitTypeDef GPIO_InitStructure;
    /* Configure USART Rx/tx PIN */
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
    GPIO_Init(GPIOA, &GPIO_InitStructure);
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_3;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
    GPIO_Init(GPIOA, &GPIO_InitStructure);
    GPIO_PinAFConfig(GPIOA, 2, GPIO_AF_7);
    GPIO_PinAFConfig(GPIOA, 3, GPIO_AF_7);
}
#endif

int rt_hw_uart_init(void)
{
    struct mm32_uart *uart;
    struct serial_configure config = RT_SERIAL_CONFIG_DEFAULT;
#ifdef BSP_USING_UART1
    UART1PINconfigStepA();
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
    UART1PINconfigStepB();
#endif /* BSP_USING_UART1 */

#ifdef BSP_USING_UART2
    UART2PINconfigStepA();
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
    UART2PINconfigStepB();
#endif /* BSP_USING_UART2 */
    return 0;
}
INIT_BOARD_EXPORT(rt_hw_uart_init);
