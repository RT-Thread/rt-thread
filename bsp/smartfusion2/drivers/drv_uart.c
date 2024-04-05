/*
 * Copyright (c) 2006-2020, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2020-08-06     whik         first version
 */
#include <rthw.h>
#include <rtthread.h>
#include <rtdevice.h>

#include "drv_uart.h"

struct sf2_uart
{
    mss_uart_instance_t *uart;
    IRQn_Type irq;
};

struct sf2_uart uart0=
{
    &g_mss_uart0,
    UART0_IRQn,
};
struct rt_serial_device serial0;

void uart0_rx_handler(mss_uart_instance_t *this_uart)
{
    /* enter interrupt */
    rt_interrupt_enter();
    rt_hw_serial_isr(&serial0, RT_SERIAL_EVENT_RX_IND);
    /* leave interrupt */
    rt_interrupt_leave();
}

struct sf2_uart uart1=
{
    &g_mss_uart1,
    UART1_IRQn,
};

struct rt_serial_device serial1;
void uart1_rx_handler(mss_uart_instance_t *this_uart)
{
    /* enter interrupt */
    rt_interrupt_enter();
    rt_hw_serial_isr(&serial1, RT_SERIAL_EVENT_RX_IND);
    /* leave interrupt */
    rt_interrupt_leave();
}

static rt_err_t sf2_uart_configure(struct rt_serial_device *serial,
                                   struct serial_configure *cfg)
{
    uint32_t baudRate;
    uint8_t datBits, parity, stopBits;
    uint8_t config;
    struct sf2_uart *uart;

    RT_ASSERT(serial != RT_NULL);
    RT_ASSERT(cfg != RT_NULL);

    uart = (struct sf2_uart *)serial->parent.user_data;

    switch(cfg->data_bits)
    {
        case DATA_BITS_5: datBits = MSS_UART_DATA_5_BITS; break;
        case DATA_BITS_6: datBits = MSS_UART_DATA_6_BITS; break;
        case DATA_BITS_7: datBits = MSS_UART_DATA_7_BITS; break;
        case DATA_BITS_8: datBits = MSS_UART_DATA_8_BITS; break;
        default:          datBits = MSS_UART_DATA_8_BITS; break;
    }
    switch(cfg->parity)
    {
        case PARITY_NONE: parity = MSS_UART_NO_PARITY;   break;
        case PARITY_EVEN: parity = MSS_UART_EVEN_PARITY; break;
        case PARITY_ODD : parity = MSS_UART_ODD_PARITY;  break;
        default         : parity = MSS_UART_NO_PARITY;   break;
    }
    switch(cfg->stop_bits)
    {
        case STOP_BITS_1: stopBits = MSS_UART_ONE_STOP_BIT; break;
        case STOP_BITS_2: stopBits = MSS_UART_TWO_STOP_BITS; break;
        case STOP_BITS_3: stopBits = MSS_UART_ONEHALF_STOP_BIT; break;
        default         : stopBits = MSS_UART_ONE_STOP_BIT;
    }

    baudRate = cfg->baud_rate;
    config = datBits | parity | stopBits;

    MSS_UART_init(uart->uart, baudRate, config);
    if(uart->uart == &g_mss_uart0)
        MSS_UART_set_rx_handler(uart->uart, uart0_rx_handler, MSS_UART_FIFO_SINGLE_BYTE);
    else
        MSS_UART_set_rx_handler(uart->uart, uart1_rx_handler, MSS_UART_FIFO_SINGLE_BYTE);

    return RT_EOK;
}

static rt_err_t sf2_uart_control(struct rt_serial_device *serial,
                                  int cmd, void *arg)
{
    struct sf2_uart* uart;

    RT_ASSERT(serial != RT_NULL);
    uart = (struct sf2_uart*)serial->parent.user_data;

    switch (cmd)
    {
        case RT_DEVICE_CTRL_CLR_INT:
            NVIC_DisableIRQ(uart->irq);
            break;
        case RT_DEVICE_CTRL_SET_INT:
            NVIC_EnableIRQ(uart->irq);
            break;
    }

    return RT_EOK;
}

static int sf2_uart_putc(struct rt_serial_device *serial, char c)
{
    struct sf2_uart* uart;
    uint32_t tx_ready;

    RT_ASSERT(serial != RT_NULL);

    uart = (struct sf2_uart*)serial->parent.user_data;

    do {
        tx_ready = uart->uart->hw_reg->LSR & 0x20u;
    } while(!tx_ready);
    uart->uart->hw_reg->THR = c;

    return 1;
}

static int sf2_uart_getc(struct rt_serial_device *serial)
{
    int ch = -1;
    uint8_t err_status;
    struct sf2_uart* uart;

    RT_ASSERT(serial != RT_NULL);
    uart = (struct sf2_uart*)serial->parent.user_data;

    err_status = MSS_UART_get_rx_status(uart->uart);
    if(MSS_UART_NO_ERROR == err_status)
        MSS_UART_get_rx(uart->uart, (uint8_t *)&ch, 1);

    return ch;
}

static const struct rt_uart_ops sf2_uart_ops =
{
    sf2_uart_configure,
    sf2_uart_control,
    sf2_uart_putc,
    sf2_uart_getc,
};

int rt_hw_uart_init(void)
{
    rt_err_t result = RT_EOK;
    struct sf2_uart* uart;
    struct serial_configure config = RT_SERIAL_CONFIG_DEFAULT;

#ifdef BSP_USING_UART0
    uart = &uart0;
    serial0.ops = &sf2_uart_ops;
    /* default config: 115200, 8, no, 1 */
    serial0.config = config;
    result = rt_hw_serial_register(&serial0, "uart0", RT_DEVICE_FLAG_RDWR | RT_DEVICE_FLAG_INT_RX, uart);
    RT_ASSERT(result == RT_EOK);
#endif

#ifdef BSP_USING_UART1
    uart = &uart1;
    serial1.ops = &sf2_uart_ops;
    /* default config: 115200, 8, no, 1 */
    serial1.config = config;
    result = rt_hw_serial_register(&serial1, "uart1", RT_DEVICE_FLAG_RDWR | RT_DEVICE_FLAG_INT_RX, uart);
    RT_ASSERT(result == RT_EOK);
#endif
    return result;
}
INIT_BOARD_EXPORT(rt_hw_uart_init);
