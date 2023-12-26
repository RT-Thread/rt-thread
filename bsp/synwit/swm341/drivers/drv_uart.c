/*
 * Copyright (c) 2006-2022, Synwit Technology Co.,Ltd.
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2021-07-01     lik          first version
 */

#include "drv_uart.h"

#ifdef RT_USING_SERIAL
#ifdef BSP_USING_UART

//#define DRV_DEBUG
#define LOG_TAG "drv.uart"
#include <drv_log.h>

#if !defined(BSP_USING_UART0) && !defined(BSP_USING_UART1) && !defined(BSP_USING_UART2) && \
    !defined(BSP_USING_UART3)
#error "Please define at least one BSP_USING_UARTx"
/* this driver can be disabled at menuconfig -> RT-Thread Components -> Device Drivers */
#endif

#ifdef BSP_USING_UART0
#ifndef UART0_CFG
#define UART0_CFG                                   \
    {                                               \
        .name = "uart0",                            \
        .UARTx = UART0,                             \
        .irq = UART0_IRQn,                          \
        .uart_initstruct.Baudrate = 115200,         \
        .uart_initstruct.DataBits = UART_DATA_8BIT, \
        .uart_initstruct.Parity = UART_PARITY_NONE, \
        .uart_initstruct.StopBits = UART_STOP_1BIT, \
        .uart_initstruct.RXThreshold = 0,           \
        .uart_initstruct.RXThresholdIEn = 1,        \
        .uart_initstruct.TXThresholdIEn = 0,        \
        .uart_initstruct.TimeoutTime = 10,          \
        .uart_initstruct.TimeoutIEn = 1,            \
    }
#endif /* UART0_CFG */
#endif /* BSP_USING_UART0 */

#ifdef BSP_USING_UART1
#ifndef UART1_CFG
#define UART1_CFG                                   \
    {                                               \
        .name = "uart1",                            \
        .UARTx = UART1,                             \
        .irq = UART1_IRQn,                          \
        .uart_initstruct.Baudrate = 115200,         \
        .uart_initstruct.DataBits = UART_DATA_8BIT, \
        .uart_initstruct.Parity = UART_PARITY_NONE, \
        .uart_initstruct.StopBits = UART_STOP_1BIT, \
        .uart_initstruct.RXThreshold = 0,           \
        .uart_initstruct.RXThresholdIEn = 1,        \
        .uart_initstruct.TXThresholdIEn = 0,        \
        .uart_initstruct.TimeoutTime = 10,          \
        .uart_initstruct.TimeoutIEn = 1,            \
    }
#endif /* UART1_CFG */
#endif /* BSP_USING_UART1 */

#ifdef BSP_USING_UART2
#ifndef UART2_CFG
#define UART2_CFG                                   \
    {                                               \
        .name = "uart2",                            \
        .UARTx = UART2,                             \
        .irq = UART2_IRQn,                          \
        .uart_initstruct.Baudrate = 115200,         \
        .uart_initstruct.DataBits = UART_DATA_8BIT, \
        .uart_initstruct.Parity = UART_PARITY_NONE, \
        .uart_initstruct.StopBits = UART_STOP_1BIT, \
        .uart_initstruct.RXThreshold = 0,           \
        .uart_initstruct.RXThresholdIEn = 1,        \
        .uart_initstruct.TXThresholdIEn = 0,        \
        .uart_initstruct.TimeoutTime = 10,          \
        .uart_initstruct.TimeoutIEn = 1,            \
    }
#endif /* UART2_CFG */
#endif /* BSP_USING_UART2 */

#ifdef BSP_USING_UART3
#ifndef UART3_CFG
#define UART3_CFG                                   \
    {                                               \
        .name = "uart3",                            \
        .UARTx = UART3,                             \
        .irq = UART3_IRQn,                          \
        .uart_initstruct.Baudrate = 115200,         \
        .uart_initstruct.DataBits = UART_DATA_8BIT, \
        .uart_initstruct.Parity = UART_PARITY_NONE, \
        .uart_initstruct.StopBits = UART_STOP_1BIT, \
        .uart_initstruct.RXThreshold = 0,           \
        .uart_initstruct.RXThresholdIEn = 1,        \
        .uart_initstruct.TXThresholdIEn = 0,        \
        .uart_initstruct.TimeoutTime = 10,          \
        .uart_initstruct.TimeoutIEn = 1,            \
    }
#endif /* UART3_CFG */
#endif /* BSP_USING_UART3 */

/* swm config class */
struct swm_uart_cfg
{
    const char *name;
    UART_TypeDef *UARTx;
    IRQn_Type irq;
    UART_InitStructure uart_initstruct;
};

/* swm uart dirver class */
struct swm_uart_device
{
    struct swm_uart_cfg *uart_cfg;
    struct rt_serial_device serial_device;
};

enum
{
#ifdef BSP_USING_UART0
    UART0_INDEX,
#endif
#ifdef BSP_USING_UART1
    UART1_INDEX,
#endif
#ifdef BSP_USING_UART2
    UART2_INDEX,
#endif
#ifdef BSP_USING_UART3
    UART3_INDEX,
#endif
};

static struct swm_uart_cfg swm_uart_cfg[] =
    {
#ifdef BSP_USING_UART0
        UART0_CFG,
#endif
#ifdef BSP_USING_UART1
        UART1_CFG,
#endif
#ifdef BSP_USING_UART2
        UART2_CFG,
#endif
#ifdef BSP_USING_UART3
        UART3_CFG,
#endif
};

static struct swm_uart_device uart_obj[sizeof(swm_uart_cfg) / sizeof(swm_uart_cfg[0])] = {0};

static rt_err_t swm_uart_configure(struct rt_serial_device *serial_device, struct serial_configure *configure)
{
    struct swm_uart_cfg *uart_cfg;
    RT_ASSERT(serial_device != RT_NULL);
    RT_ASSERT(configure != RT_NULL);
    uart_cfg = serial_device->parent.user_data;

    uart_cfg->uart_initstruct.Baudrate = configure->baud_rate;
    switch (configure->data_bits)
    {
    case DATA_BITS_8:
        uart_cfg->uart_initstruct.DataBits = UART_DATA_8BIT;
        break;
    case DATA_BITS_9:
        uart_cfg->uart_initstruct.DataBits = UART_DATA_9BIT;
        break;
    default:
        uart_cfg->uart_initstruct.DataBits = UART_DATA_8BIT;
        break;
    }
    switch (configure->stop_bits)
    {
    case STOP_BITS_1:
        uart_cfg->uart_initstruct.StopBits = UART_STOP_1BIT;
        break;
    case STOP_BITS_2:
        uart_cfg->uart_initstruct.StopBits = UART_STOP_2BIT;
        break;
    default:
        uart_cfg->uart_initstruct.StopBits = UART_STOP_1BIT;
        break;
    }
    switch (configure->parity)
    {
    case PARITY_NONE:
        uart_cfg->uart_initstruct.Parity = UART_PARITY_NONE;
        break;
    case PARITY_ODD:
        uart_cfg->uart_initstruct.Parity = UART_PARITY_ODD;
        break;
    case PARITY_EVEN:
        uart_cfg->uart_initstruct.Parity = UART_PARITY_EVEN;
        break;
    default:
        uart_cfg->uart_initstruct.Parity = UART_PARITY_NONE;
        break;
    }

    UART_Init(uart_cfg->UARTx, &(uart_cfg->uart_initstruct));
    UART_Open(uart_cfg->UARTx);
    return RT_EOK;
}

static rt_err_t swm_uart_control(struct rt_serial_device *serial_device, int cmd, void *arg)
{
    struct swm_uart_cfg *uart_cfg;
    RT_ASSERT(serial_device != RT_NULL);
    uart_cfg = serial_device->parent.user_data;

    switch (cmd)
    {
    case RT_DEVICE_CTRL_CLR_INT:
        /* disable rx irq */
        NVIC_DisableIRQ(uart_cfg->irq);
        break;
    case RT_DEVICE_CTRL_SET_INT:
        /* enable rx irq */
        NVIC_EnableIRQ(uart_cfg->irq);
        break;
    }
    return RT_EOK;
}

static int swm_uart_putc(struct rt_serial_device *serial_device, char c)
{
    struct swm_uart_cfg *uart_cfg;
    RT_ASSERT(serial_device != RT_NULL);
    uart_cfg = serial_device->parent.user_data;

    UART_WriteByte(uart_cfg->UARTx, c);
    while (UART_IsTXBusy(uart_cfg->UARTx))
        ;
    return 1;
}

static int swm_uart_getc(struct rt_serial_device *serial_device)
{
    int ch;
    struct swm_uart_cfg *uart_cfg;
    RT_ASSERT(serial_device != RT_NULL);
    uart_cfg = serial_device->parent.user_data;

    ch = -1;
    if (UART_IsRXFIFOEmpty(uart_cfg->UARTx) == 0)
    {
        UART_ReadByte(uart_cfg->UARTx, (uint32_t *)&ch);
    }
    return ch;
}

static const struct rt_uart_ops swm_uart_ops =
    {
        .configure = swm_uart_configure,
        .control = swm_uart_control,
        .putc = swm_uart_putc,
        .getc = swm_uart_getc,
        .dma_transmit = RT_NULL};

/**
 * Uart common interrupt process. This need add to uart ISR.
 *
 * @param serial serial device
 */
static void swm_uart_isr(struct rt_serial_device *serial_device)
{
    struct swm_uart_cfg *uart_cfg;
    RT_ASSERT(serial_device != RT_NULL);
    uart_cfg = serial_device->parent.user_data;

    /* UART in mode Receiver -------------------------------------------------*/
    if (UART_INTStat(uart_cfg->UARTx, UART_IT_RX_THR) || UART_INTStat(uart_cfg->UARTx, UART_IT_RX_TOUT))
    {
        if(!UART_IsRXFIFOEmpty(uart_cfg->UARTx))
        {
            rt_hw_serial_isr(serial_device, RT_SERIAL_EVENT_RX_IND);
        }

        if(UART_INTStat(uart_cfg->UARTx, UART_IT_RX_TOUT))
        {
            UART_INTClr(uart_cfg->UARTx, UART_IT_RX_TOUT);

            rt_hw_serial_isr(serial_device, RT_SERIAL_EVENT_RX_TIMEOUT);
        }
    }
}

#if defined(BSP_USING_UART0)
void UART0_Handler(void)
{
    rt_interrupt_enter();
    swm_uart_isr(&(uart_obj[UART0_INDEX].serial_device));
    rt_interrupt_leave();
}
#endif /* BSP_USING_UART0 */

#if defined(BSP_USING_UART1)
void UART1_Handler(void)
{
    rt_interrupt_enter();
    swm_uart_isr(&(uart_obj[UART1_INDEX].serial_device));
    rt_interrupt_leave();
}
#endif /* BSP_USING_UART1 */

#if defined(BSP_USING_UART2)
void UART2_Handler(void)
{
    rt_interrupt_enter();
    swm_uart_isr(&(uart_obj[UART2_INDEX].serial_device));
    rt_interrupt_leave();
}
#endif /* BSP_USING_UART2 */

#if defined(BSP_USING_UART3)
void UART3_Handler(void)
{
    rt_interrupt_enter();
    swm_uart_isr(&(uart_obj[UART3_INDEX].serial_device));
    rt_interrupt_leave();
}
#endif /* BSP_USING_UART3 */

int swm_uart_init(void)
{
    struct serial_configure serial_cfg = RT_SERIAL_CONFIG_DEFAULT;
    int i = 0;
    rt_err_t result = RT_EOK;

#ifdef BSP_USING_UART0
    PORT_Init(PORTM, PIN0, PORTM_PIN0_UART0_RX, 1);
    PORT_Init(PORTM, PIN1, PORTM_PIN1_UART0_TX, 0);
#endif
#ifdef BSP_USING_UART1
    PORT_Init(PORTD, PIN4, PORTD_PIN4_UART1_RX, 1);
    PORT_Init(PORTD, PIN3, PORTD_PIN3_UART1_TX, 0);
#endif
#ifdef BSP_USING_UART2
    PORT_Init(PORTC, PIN1, PORTC_PIN1_UART2_RX, 1);
    PORT_Init(PORTC, PIN0, PORTC_PIN0_UART2_TX, 0);
#endif
#ifdef BSP_USING_UART3
    PORT_Init(PORTC, PIN2, PORTC_PIN2_UART3_RX, 1);
    PORT_Init(PORTC, PIN3, PORTC_PIN3_UART3_TX, 0);
#endif

    for (i = 0; i < sizeof(swm_uart_cfg) / sizeof(swm_uart_cfg[0]); i++)
    {
        uart_obj[i].uart_cfg = &swm_uart_cfg[i];
        uart_obj[i].serial_device.ops = &swm_uart_ops;
        uart_obj[i].serial_device.config = serial_cfg;

        result = rt_hw_serial_register(&uart_obj[i].serial_device, uart_obj[i].uart_cfg->name,
                                       RT_DEVICE_FLAG_RDWR | RT_DEVICE_FLAG_INT_RX, uart_obj[i].uart_cfg);
        RT_ASSERT(result == RT_EOK);
    }

    return result;
}

#endif /* BSP_USING_UART */
#endif /* RT_USING_SERIAL */
