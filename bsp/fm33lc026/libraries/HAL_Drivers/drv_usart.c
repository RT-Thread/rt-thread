/*
 * Copyright (c) 2006-2022, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2021-08-27     Jiao         first version
*/

#include "drv_usart.h"
#include "drv_config.h"

#ifdef RT_USING_SERIAL

//#define DRV_DEBUG
#define LOG_TAG             "drv.usart"
#include <drv_log.h>

enum
{
#ifdef BSP_USING_UART0
    UART0_INDEX,
#endif
#ifdef BSP_USING_UART1
    UART1_INDEX,
#endif
#ifdef BSP_USING_UART4
    UART4_INDEX,
#endif
#ifdef BSP_USING_UART5
    UART5_INDEX,
#endif
#ifdef BSP_USING_LPUART0
    LPUART0_INDEX,
#endif
#ifdef BSP_USING_LPUART1
    LPUART1_INDEX,
#endif
};

static struct _uart_config uart_config[] =
{
#ifdef BSP_USING_UART0
    UART0_CONFIG,
#endif
#ifdef BSP_USING_UART1
    UART1_CONFIG,
#endif
#ifdef BSP_USING_UART4
    UART4_CONFIG,
#endif
#ifdef BSP_USING_UART5
    UART5_CONFIG,
#endif
#ifdef BSP_USING_LPUART0
    LPUART0_CONFIG,
#endif
#ifdef BSP_USING_LPUART1
    LPUART1_CONFIG,
#endif
};

static struct _uart uart_obj[sizeof(uart_config) / sizeof(uart_config[0])] = {0};

static rt_err_t uart_configure(struct rt_serial_device *serial, struct serial_configure *cfg)
{
    extern FL_ErrorStatus FL_UART_GPIO_Init(UART_Type * UARTx);

    struct _uart *uart;
    RT_ASSERT(serial != RT_NULL);
    RT_ASSERT(cfg != RT_NULL);

    uart = rt_container_of(serial, struct _uart, serial);

    if (FL_UART_GPIO_Init(uart->config->InitTypeDef) != FL_PASS)
    {
        return -RT_ERROR;
    }

    uart->handle.clockSrc          = uart->config->clockSrc;
    uart->handle.baudRate          = cfg->baud_rate;

    switch (cfg->data_bits)
    {
    case DATA_BITS_8:
        uart->handle.dataWidth = FL_UART_DATA_WIDTH_8B;
        break;
    case DATA_BITS_9:
        uart->handle.dataWidth = FL_UART_DATA_WIDTH_9B;
        break;
    default:
        uart->handle.dataWidth = FL_UART_DATA_WIDTH_8B;
        break;
    }

    switch (cfg->stop_bits)
    {
    case STOP_BITS_1:
        uart->handle.stopBits = FL_UART_STOP_BIT_WIDTH_1B;
        break;
    case STOP_BITS_2:
        uart->handle.stopBits = FL_UART_STOP_BIT_WIDTH_2B;
        break;
    default:
        uart->handle.stopBits = FL_UART_STOP_BIT_WIDTH_1B;
        break;
    }
    switch (cfg->parity)
    {
    case PARITY_NONE:
        uart->handle.parity = FL_UART_PARITY_NONE;
        break;
    case PARITY_ODD:
        uart->handle.parity = FL_UART_PARITY_ODD;
        break;
    case PARITY_EVEN:
        uart->handle.parity = FL_UART_PARITY_EVEN;
        break;
    default:
        uart->handle.parity = FL_UART_PARITY_NONE;
        break;
    }

    uart->handle.transferDirection = FL_UART_DIRECTION_TX_RX;

    if (FL_UART_Init(uart->config->InitTypeDef, &uart->handle) != FL_PASS)
    {
        return -RT_ERROR;
    }

    return RT_EOK;
}

static rt_err_t uart_control(struct rt_serial_device *serial, int cmd, void *arg)
{
    struct _uart *uart;
#ifdef RT_SERIAL_USING_DMA
    rt_ubase_t ctrl_arg = (rt_ubase_t)arg;
#endif

    RT_ASSERT(serial != RT_NULL);
    uart = rt_container_of(serial, struct _uart, serial);

    switch (cmd)
    {
    /* disable interrupt */
    case RT_DEVICE_CTRL_CLR_INT:
        /* disable rx irq */
        NVIC_DisableIRQ(uart->config->irq_type);
        /* disable interrupt */
        FL_UART_DisableIT_RXBuffFull(uart->config->InitTypeDef);

        break;

    /* enable interrupt */
    case RT_DEVICE_CTRL_SET_INT:
        /* enable rx irq */
        NVIC_SetPriority(uart->config->irq_type, 1);
        NVIC_EnableIRQ(uart->config->irq_type);
        /* enable interrupt */
        FL_UART_EnableIT_RXBuffFull(uart->config->InitTypeDef);
        break;

#ifdef RT_SERIAL_USING_DMA
    case RT_DEVICE_CTRL_CONFIG:
        stm32_dma_config(serial, ctrl_arg);
        break;
#endif

    case RT_DEVICE_CTRL_CLOSE:
        if (FL_UART_DeInit(uart->config->InitTypeDef) != FL_PASS)
        {
            RT_ASSERT(0)
        }
        break;

    }
    return RT_EOK;
}

static int uart_putc(struct rt_serial_device *serial, char c)
{
    struct _uart *uart;
    RT_ASSERT(serial != RT_NULL);

    uart = rt_container_of(serial, struct _uart, serial);
    FL_UART_WriteTXBuff(uart->config->InitTypeDef, c); //发送一个数据
    while (FL_SET != FL_UART_IsActiveFlag_TXShiftBuffEmpty(uart->config->InitTypeDef));
    return 1;
}

static int uart_getc(struct rt_serial_device *serial)
{
    int ch;
    struct _uart *uart;
    RT_ASSERT(serial != RT_NULL);
    uart = rt_container_of(serial, struct _uart, serial);

    ch = -1;
    if (FL_SET == FL_UART_IsActiveFlag_RXBuffFull(uart->config->InitTypeDef))
    {
        ch = FL_UART_ReadRXBuff(uart->config->InitTypeDef);//接收中断标志可通过读取rxreg寄存器清除
    }
    return ch;
}

/**
 * Uart common interrupt process. This need add to uart ISR.
 *
 * @param serial serial device
 */
static void uart_isr(struct rt_serial_device *serial)
{
    struct _uart *uart;

    RT_ASSERT(serial != RT_NULL);
    uart = rt_container_of(serial, struct _uart, serial);

    /* UART in mode Receiver -------------------------------------------------*/
    if ((FL_ENABLE == FL_UART_IsEnabledIT_RXBuffFull(uart->config->InitTypeDef))
            && (FL_SET == FL_UART_IsActiveFlag_RXBuffFull(uart->config->InitTypeDef)))
    {
        rt_hw_serial_isr(serial, RT_SERIAL_EVENT_RX_IND);
    }
}

#if defined(BSP_USING_UART0)
void UART0_IRQHandler(void)
{
    /* enter interrupt */
    rt_interrupt_enter();

    uart_isr(&(uart_obj[UART0_INDEX].serial));

    /* leave interrupt */
    rt_interrupt_leave();
}
#endif /* BSP_USING_UART1 */

#if defined(BSP_USING_UART1)
void UART1_IRQHandler(void)
{
    /* enter interrupt */
    rt_interrupt_enter();

    uart_isr(&(uart_obj[UART1_INDEX].serial));

    /* leave interrupt */
    rt_interrupt_leave();
}
#endif /* BSP_USING_UART1 */

#if defined(BSP_USING_UART4)
void UART4_IRQHandler(void)
{
    /* enter interrupt */
    rt_interrupt_enter();

    uart_isr(&(uart_obj[UART4_INDEX].serial));

    /* leave interrupt */
    rt_interrupt_leave();
}
#endif /* BSP_USING_UART4 */

#if defined(BSP_USING_UART5)
void UART5_IRQHandler(void)
{
    /* enter interrupt */
    rt_interrupt_enter();

    uart_isr(&(uart_obj[UART5_INDEX].serial));

    /* leave interrupt */
    rt_interrupt_leave();
}
#endif /* BSP_USING_UART5 */

#if defined(BSP_USING_LPUART0)
void LPUART0_IRQHandler(void)
{
    /* enter interrupt */
    rt_interrupt_enter();

    uart_isr(&(uart_obj[LPUART0_INDEX].serial));

    /* leave interrupt */
    rt_interrupt_leave();
}
#endif /* BSP_USING_LPUART0*/

#if defined(BSP_USING_LPUART1)
void LPUART1_IRQHandler(void)
{
    /* enter interrupt */
    rt_interrupt_enter();

    uart_isr(&(uart_obj[LPUART1_INDEX].serial));

    /* leave interrupt */
    rt_interrupt_leave();
}
#endif /* BSP_USING_LPUART1*/

static const struct rt_uart_ops _uart_ops =
{
    .configure = uart_configure,
    .control = uart_control,
    .putc = uart_putc,
    .getc = uart_getc,
    .dma_transmit = 0
};

int rt_hw_usart_init(void)
{
    rt_size_t obj_num = sizeof(uart_obj) / sizeof(struct _uart);
    struct serial_configure config = RT_SERIAL_CONFIG_DEFAULT;
    rt_err_t result = 0;

    for (int i = 0; i < obj_num; i++)
    {
        /* init UART object */
        uart_obj[i].config = &uart_config[i];
        uart_obj[i].serial.ops    = &_uart_ops;
        uart_obj[i].serial.config = config;

        /* register UART device */
        result = rt_hw_serial_register(&uart_obj[i].serial, uart_obj[i].config->name,
                                       RT_DEVICE_FLAG_RDWR
                                       | RT_DEVICE_FLAG_INT_RX
                                       | RT_DEVICE_FLAG_INT_TX
                                       | uart_obj[i].uart_dma_flag
                                       , NULL);
        RT_ASSERT(result == RT_EOK);
    }

    return result;
}

#endif /* RT_USING_SERIAL */
