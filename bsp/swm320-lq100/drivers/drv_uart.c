/*
 * Copyright (c) 2006-2018, Synwit Technology Co.,Ltd.
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2018-05-31     ZYH          first version
 * 2018-12-10     Zohar_Lee    format file
 * 2020-07-10     lik          format file
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

static struct swm_uart_cfg uart_cfg[] =
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

static struct swm_uart uart_drv[sizeof(uart_cfg) / sizeof(uart_cfg[0])] = {0};

static rt_err_t swm_uart_init(struct rt_serial_device *serial_device, struct serial_configure *configure)
{
    struct swm_uart_cfg *cfg;
    RT_ASSERT(serial_device != RT_NULL);
    RT_ASSERT(configure != RT_NULL);
    cfg = serial_device->parent.user_data;

    cfg->uart_initstruct.Baudrate = configure->baud_rate;
    switch (configure->data_bits)
    {
    case DATA_BITS_8:
        cfg->uart_initstruct.DataBits = UART_DATA_8BIT;
        break;
    case DATA_BITS_9:
        cfg->uart_initstruct.DataBits = UART_DATA_9BIT;
        break;
    default:
        cfg->uart_initstruct.DataBits = UART_DATA_8BIT;
        break;
    }
    switch (configure->stop_bits)
    {
    case STOP_BITS_1:
        cfg->uart_initstruct.StopBits = UART_STOP_1BIT;
        break;
    case STOP_BITS_2:
        cfg->uart_initstruct.StopBits = UART_STOP_2BIT;
        break;
    default:
        cfg->uart_initstruct.StopBits = UART_STOP_1BIT;
        break;
    }
    switch (configure->parity)
    {
    case PARITY_NONE:
        cfg->uart_initstruct.Parity = UART_PARITY_NONE;
        break;
    case PARITY_ODD:
        cfg->uart_initstruct.Parity = UART_PARITY_ODD;
        break;
    case PARITY_EVEN:
        cfg->uart_initstruct.Parity = UART_PARITY_EVEN;
        break;
    default:
        cfg->uart_initstruct.Parity = UART_PARITY_NONE;
        break;
    }
    switch ((uint32_t)cfg->UARTx)
    {
    case ((uint32_t)UART0):
        PORT_Init(PORTA, PIN2, FUNMUX0_UART0_RXD, 1);
        PORT_Init(PORTA, PIN3, FUNMUX1_UART0_TXD, 0);
        break;
    case ((uint32_t)UART1):
        PORT_Init(PORTC, PIN2, FUNMUX0_UART1_RXD, 1);
        PORT_Init(PORTC, PIN3, FUNMUX1_UART1_TXD, 0);
        break;
    case ((uint32_t)UART2):
        PORT_Init(PORTC, PIN4, FUNMUX0_UART2_RXD, 1);
        PORT_Init(PORTC, PIN5, FUNMUX1_UART2_TXD, 0);
        break;
    case ((uint32_t)UART3):
        PORT_Init(PORTC, PIN6, FUNMUX0_UART3_RXD, 1);
        PORT_Init(PORTC, PIN7, FUNMUX1_UART3_TXD, 0);
        break;
    default:
        break;
    }
    UART_Init(cfg->UARTx, &(cfg->uart_initstruct));
    UART_Open(cfg->UARTx);
    return RT_EOK;
}

static rt_err_t swm_uart_control(struct rt_serial_device *serial_device, int cmd, void *arg)
{
    struct swm_uart_cfg *cfg;
    RT_ASSERT(serial_device != RT_NULL);
    cfg = serial_device->parent.user_data;

    switch (cmd)
    {
    case RT_DEVICE_CTRL_CLR_INT:
        /* disable rx irq */
        NVIC_DisableIRQ(cfg->irq);
        break;
    case RT_DEVICE_CTRL_SET_INT:
        /* enable rx irq */
        NVIC_EnableIRQ(cfg->irq);
        break;
    }
    return RT_EOK;
}

static int swm_uart_putc(struct rt_serial_device *serial_device, char c)
{
    struct swm_uart_cfg *cfg;
    RT_ASSERT(serial_device != RT_NULL);
    cfg = serial_device->parent.user_data;

    while (UART_IsTXFIFOFull(cfg->UARTx))
        ;
    UART_WriteByte(cfg->UARTx, c);
    while (UART_IsTXBusy(cfg->UARTx))
        ;
    return 1;
}

static int swm_uart_getc(struct rt_serial_device *serial_device)
{
    int ch;
    struct swm_uart_cfg *cfg;
    RT_ASSERT(serial_device != RT_NULL);
    cfg = serial_device->parent.user_data;

    ch = -1;
    if (UART_IsRXFIFOEmpty(cfg->UARTx) == 0)
    {
        UART_ReadByte(cfg->UARTx, (uint32_t *)&ch);
    }
    return ch;
}

static const struct rt_uart_ops swm_uart_ops =
    {
        .configure = swm_uart_init,
        .control = swm_uart_control,
        .putc = swm_uart_putc,
        .getc = swm_uart_getc,
        .dma_transmit = RT_NULL};

/**
 * Uart common interrupt process. This need add to uart ISR.
 *
 * @param serial serial device
 */
static void rt_hw_uart_isr(struct rt_serial_device *serial_device)
{
    struct swm_uart_cfg *cfg;
    RT_ASSERT(serial_device != RT_NULL);
    cfg = serial_device->parent.user_data;

    /* UART in mode Receiver -------------------------------------------------*/
    if (UART_INTRXThresholdStat(cfg->UARTx) || UART_INTTimeoutStat(cfg->UARTx))
    {
        rt_hw_serial_isr(serial_device, RT_SERIAL_EVENT_RX_IND);
    }
}

#if defined(BSP_USING_UART0)
void UART0_Handler(void)
{
    /* enter interrupt */
    rt_interrupt_enter();

    rt_hw_uart_isr(&(uart_drv[UART0_INDEX].serial_device));

    /* leave interrupt */
    rt_interrupt_leave();
}
#endif /* BSP_USING_UART0 */

#if defined(BSP_USING_UART1)
void UART1_Handler(void)
{
    /* enter interrupt */
    rt_interrupt_enter();

    rt_hw_uart_isr(&(uart_drv[UART1_INDEX].serial_device));

    /* leave interrupt */
    rt_interrupt_leave();
}
#endif /* BSP_USING_UART1 */

#if defined(BSP_USING_UART2)
void UART2_Handler(void)
{
    /* enter interrupt */
    rt_interrupt_enter();

    rt_hw_uart_isr(&(uart_drv[UART2_INDEX].serial_device));

    /* leave interrupt */
    rt_interrupt_leave();
}
#endif /* BSP_USING_UART2 */

#if defined(BSP_USING_UART3)
void UART3_Handler(void)
{
    /* enter interrupt */
    rt_interrupt_enter();

    rt_hw_uart_isr(&(uart_drv[UART3_INDEX].serial_device));

    /* leave interrupt */
    rt_interrupt_leave();
}
#endif /* BSP_USING_UART3 */

int rt_hw_uart_init(void)
{
    struct serial_configure cfg = RT_SERIAL_CONFIG_DEFAULT;
    int i = 0;
    rt_err_t result = RT_EOK;

    for (i = 0; i < sizeof(uart_cfg) / sizeof(uart_cfg[0]); i++)
    {
        uart_drv[i].cfg = &uart_cfg[i];
        uart_drv[i].serial_device.ops = &swm_uart_ops;
        uart_drv[i].serial_device.config = cfg;
        /* register UART device */
        result = rt_hw_serial_register(&uart_drv[i].serial_device, uart_drv[i].cfg->name,
                                       RT_DEVICE_FLAG_RDWR | RT_DEVICE_FLAG_INT_RX, uart_drv[i].cfg);
        RT_ASSERT(result == RT_EOK);
    }

    return result;
}
INIT_BOARD_EXPORT(rt_hw_uart_init);

#endif /* BSP_USING_UART */
#endif /* RT_USING_SERIAL */
