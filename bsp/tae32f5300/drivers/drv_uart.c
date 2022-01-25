/*
 * Copyright (c) 2006-2021, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2021-09-05     qinweizhong   first version
 */
#include <rtdevice.h>
#include "drv_uart.h"
#include "tae32f53xx_ll.h"
#include <tae32f53xx_ll_cortex.h>
#include "drv_uart.h"

/* uart driver */
struct tae32_uart
{
    UART_TypeDef *uart;
    IRQn_Type irq;
};

static void uart_init(void)
{
    UART_InitTypeDef uart_init;
    uart_init.baudrate = 115200;
    uart_init.dat_len = UART_DAT_LEN_8b;
    uart_init.stop_len = UART_STOP_LEN_1b;
    uart_init.parity = UART_PARITY_NO;
    uart_init.tx_tl = UART_TX_EMPTY_TRI_LVL_EMPTY;
    uart_init.rx_tl = UART_RX_AVL_TRI_LVL_1CHAR;
    LL_UART_Init(UART0, &uart_init);

    __LL_UART_RxDatAvl_INT_En(UART0);
}

static rt_err_t _uart_configure(struct rt_serial_device *serial, struct serial_configure *cfg)
{
    struct tae32_uart *uart;
    UART_InitTypeDef UART_InitStructure;
    RT_ASSERT(serial != RT_NULL);
    RT_ASSERT(cfg != RT_NULL);
    uart = (struct tae32_uart *)serial->parent.user_data;
    UART_InitStructure.baudrate = cfg->baud_rate;
    if (cfg->data_bits == DATA_BITS_8)
        UART_InitStructure.dat_len = UART_DAT_LEN_8b;
    if (cfg->stop_bits == STOP_BITS_1)
        UART_InitStructure.stop_len = UART_STOP_LEN_1b;
    else if (cfg->stop_bits == STOP_BITS_2)
        UART_InitStructure.stop_len = UART_STOP_LEN_2b;
    UART_InitStructure.parity = UART_PARITY_NO;
    UART_InitStructure.tx_tl = UART_TX_EMPTY_TRI_LVL_EMPTY;
    UART_InitStructure.rx_tl = UART_RX_AVL_TRI_LVL_1CHAR;
    LL_UART_Init(uart->uart, &UART_InitStructure);

    return RT_EOK;
}

static rt_err_t _uart_control(struct rt_serial_device *serial, int cmd, void *arg)
{
    struct tae32_uart *uart;
    RT_ASSERT(serial != RT_NULL);
    uart = (struct tae32_uart *)serial->parent.user_data;
    switch (cmd)
    {
    case RT_DEVICE_CTRL_CLR_INT:
        /* disable rx irq */
        NVIC_DisableIRQ(uart->irq);
        __LL_UART_RxDatAvl_INT_Dis(uart->uart);
        break;
    case RT_DEVICE_CTRL_SET_INT:
        /* enable rx irq */
        NVIC_EnableIRQ(uart->irq);
        /* enable interrupt */
        __LL_UART_RxDatAvl_INT_En(uart->uart);
        break;
    }
    return RT_EOK;
}

static int _uart_putc(struct rt_serial_device *serial, char c)
{
    struct tae32_uart *uart;
    RT_ASSERT(serial != RT_NULL);
    uart = (struct tae32_uart *)serial->parent.user_data;
    while (!__LL_UART_IsTxFIFONotFull(uart->uart)) {};
    __LL_UART_TxBuf9bits_Write(uart->uart, (uint16_t)c);
    return 1;
}

static int _uart_getc(struct rt_serial_device *serial)
{
    int ch;
    struct tae32_uart *uart;
    RT_ASSERT(serial != RT_NULL);
    uart = (struct tae32_uart *)serial->parent.user_data;
    ch = -1;
    if (__LL_UART_IsDatReady(uart->uart))
    {
        ch = __LL_UART_RxBuf9bits_Read(uart->uart);
    }
    else
    {
        rt_thread_mdelay(10);
    }
    return ch;
}

static const struct rt_uart_ops _uart_ops =
{
    _uart_configure,
    _uart_control,
    _uart_putc,
    _uart_getc,
};

#if defined(BSP_USING_UART0)
/* UART0 device driver structure */
static struct tae32_uart uart0;
struct rt_serial_device serial0;
void UART0_IRQHandler(void)
{
    struct tae32_uart *uart;
    uart = &uart0;
    /* enter interrupt */
    rt_interrupt_enter();
    if (__LL_UART_INT_ID_Get(uart->uart) == UART_INT_ID_RX_AVL)
    {
        rt_hw_serial_isr(&serial0, RT_SERIAL_EVENT_RX_IND);
    }
    if (__LL_UART_INT_ID_Get(uart->uart) != UART_INT_ID_RX_AVL)
    {
        /* clear interrupt */
    }
    /* leave interrupt */
    rt_interrupt_leave();
}
#endif /* BSP_USING_UART1 */

#if defined(BSP_USING_UART1)
/* UART2 device driver structure */
static struct tae32_uart uart1;
struct rt_serial_device serial1;
void UART1_IRQHandler(void)
{
    struct tae32_uart *uart;
    uart = &uart1;
    /* enter interrupt */
    rt_interrupt_enter();
    if (__LL_UART_INT_ID_Get(uart->uart) == UART_INT_ID_RX_AVL)
    {
        rt_hw_serial_isr(&serial1, RT_SERIAL_EVENT_RX_IND);
    }
    if (__LL_UART_INT_ID_Get(uart->uart) != UART_INT_ID_RX_AVL)
    {
        /* clear interrupt */
    }
    /* leave interrupt */
    rt_interrupt_leave();
}
#endif /* BSP_USING_UART1 */

int rt_hw_uart_init(void)
{
    struct tae32_uart *uart;
    struct serial_configure config = RT_SERIAL_CONFIG_DEFAULT;
#ifdef BSP_USING_UART0
    uart = &uart0;
    uart->uart = UART0;
    uart->irq = UART0_IRQn;
    config.baud_rate = BAUD_RATE_115200;
    serial0.ops = &_uart_ops;
    serial0.config = config;
    uart_init();

    /* register UART1 device */
    rt_hw_serial_register(&serial0, "uart0",
                          RT_DEVICE_FLAG_RDWR | RT_DEVICE_FLAG_INT_RX,
                          uart);
#endif /* BSP_USING_UART0 */

#ifdef BSP_USING_UART1
    uart = &uart1;
    uart->uart = UART1;
    uart->irq = UART1_IRQn;
    config.baud_rate = BAUD_RATE_115200;
    serial2.ops = &_uart_ops;
    serial2.config = config;
    /* register UART1 device */
    rt_hw_serial_register(&serial1, "uart1",
                          RT_DEVICE_FLAG_RDWR | RT_DEVICE_FLAG_INT_RX,
                          uart);
#endif /* BSP_USING_UART1 */
    return 0;
}
INIT_BOARD_EXPORT(rt_hw_uart_init);
