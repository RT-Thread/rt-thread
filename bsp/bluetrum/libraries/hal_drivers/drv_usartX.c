/*
 * Copyright (c) 2020-2022, Bluetrum Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author            Notes
 * 2020-11-20     greedyhao         first version
 * 2022-06-08     THEWON            first version for serialX
 */

#include "board.h"
#include <drv_usartX.h>

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
#ifdef BSP_USING_UART2
    UART2_INDEX,
#endif
};

static struct ab32_uart_config uart_config[] =
{
#ifdef BSP_USING_UART0
    {
        .name = "uart0",
        .instance = UART0_BASE,
        .mode = UART_MODE_TX_RX | UART_MODE_1LINE,
    },
#endif
#ifdef BSP_USING_UART1
    {
        .name = "uart1",
        .instance = UART1_BASE,
        .mode = UART_MODE_TX_RX,
    },
#endif
#ifdef BSP_USING_UART2
    {
        .name = "uart2",
        .instance = UART2_BASE,
        .mode = UART_MODE_TX_RX,
    }
#endif
};

static struct ab32_uart uart_obj[sizeof(uart_config) / sizeof(uart_config[0])] = {0};

static rt_err_t ab32_init(struct rt_serial_device *serial)
{
    struct ab32_uart *uart;
    RT_ASSERT(serial != RT_NULL);

    uart = rt_container_of(serial, struct ab32_uart, serial);
    uart->handle.instance           = uart->uart_config->instance;
    uart->handle.init.baud          = serial->config->baud_rate;
    uart->handle.init.mode          = uart->uart_config->mode;

    switch (serial->config->data_bits)
    {
    case DATA_BITS_8:
        uart->handle.init.word_len  = UART_WORDLENGTH_8B;
    break;
    case DATA_BITS_9:
        uart->handle.init.word_len  = UART_WORDLENGTH_9B;
    break;
    default:
        uart->handle.init.word_len  = UART_WORDLENGTH_8B;
    break;
    }

    switch (serial->config->stop_bits)
    {
    case STOP_BITS_1:
        uart->handle.init.stop_bits = UART_STOPBITS_1;
    break;
    case STOP_BITS_2:
        uart->handle.init.stop_bits = UART_STOPBITS_2;
    break;
    default:
        uart->handle.init.stop_bits = UART_STOPBITS_1;
    break;
    }

    hal_uart_init(&uart->handle);

    return RT_EOK;
}

static rt_err_t ab32_configure(struct rt_serial_device *serial, struct serial_configure *cfg)
{
    struct ab32_uart *uart;
    RT_ASSERT(serial != RT_NULL);
    RT_ASSERT(cfg != RT_NULL);

    uart = rt_container_of(serial, struct ab32_uart, serial);
    uart->handle.instance           = uart->uart_config->instance;
    uart->handle.init.baud          = cfg->baud_rate;
    uart->handle.init.mode          = uart->uart_config->mode;

    switch (cfg->data_bits)
    {
    case DATA_BITS_8:
        uart->handle.init.word_len  = UART_WORDLENGTH_8B;
    break;
    case DATA_BITS_9:
        uart->handle.init.word_len  = UART_WORDLENGTH_9B;
    break;
    default:
        uart->handle.init.word_len  = UART_WORDLENGTH_8B;
    break;
    }

    switch (cfg->stop_bits)
    {
    case STOP_BITS_1:
        uart->handle.init.stop_bits = UART_STOPBITS_1;
    break;
    case STOP_BITS_2:
        uart->handle.init.stop_bits = UART_STOPBITS_2;
    break;
    default:
        uart->handle.init.stop_bits = UART_STOPBITS_1;
    break;
    }

    hal_uart_init(&uart->handle);

    return RT_EOK;
}

static rt_err_t ab32_control(struct rt_serial_device *serial, int cmd, void *arg)
{
    struct ab32_uart *uart;

    RT_ASSERT(serial != RT_NULL);
    uart = rt_container_of(serial, struct ab32_uart, serial);

    switch (cmd)
    {
    case RT_DEVICE_CTRL_OPEN:
        uart->intTxing = RT_FALSE;
    break;
    /* disable interrupt */
    case RT_DEVICE_CTRL_CLR_INT:
        hal_uart_control(uart->handle.instance, UART_RXIT_ENABLE, HAL_DISABLE);
    break;
    /* enable interrupt */
    case RT_DEVICE_CTRL_SET_INT:
        hal_uart_clrflag(uart->handle.instance, UART_FLAG_RXPND);
        hal_uart_control(uart->handle.instance, UART_RXIT_ENABLE, HAL_ENABLE);
    break;
    case RT_DEVICE_CTRL_CLOSE:
        hal_uart_deinit(uart->handle.instance);
    break;
    }

    return RT_EOK;
}

static int ab32_putc(struct rt_serial_device *serial, char ch)
{
    struct ab32_uart *uart;

    RT_ASSERT(serial != RT_NULL);

    uart = rt_container_of(serial, struct ab32_uart, serial);

    hal_uart_write(uart->handle.instance, ch);

    return 1;
}

static int ab32_getc(struct rt_serial_device *serial)
{
    int ch;
    struct ab32_uart *uart;

    RT_ASSERT(serial != RT_NULL);

    uart = rt_container_of(serial, struct ab32_uart, serial);

    ch = -1;
    if (hal_uart_getflag(UART0_BASE, UART_FLAG_RXPND)) {
        ch = hal_uart_read(uart->handle.instance);
        hal_uart_clrflag(UART0_BASE, UART_FLAG_RXPND);
    }

    return ch;
}

static int ab32_flush(struct rt_serial_device *serial)
{
    struct ab32_uart *uart;

    RT_ASSERT(serial != RT_NULL);

    uart = rt_container_of(serial, struct ab32_uart, serial);
    while(hal_uart_getflag(uart->handle.instance, UART_FLAG_TXPND) == 0);
}

rt_bool_t ab32_int_txing(struct rt_serial_device *serial)
{
    struct ab32_uart *uart;

    RT_ASSERT(serial != RT_NULL);

    uart = rt_container_of(serial, struct ab32_uart, serial);

    return uart->intTxing;
}

static void ab32_start_tx(struct rt_serial_device *serial, rt_uint8_t ch)
{
    struct ab32_uart *uart;

    RT_ASSERT(serial != RT_NULL);

    uart = rt_container_of(serial, struct ab32_uart, serial);
    uart->intTxing = RT_TRUE;
    hal_uart_control(uart->handle.instance, UART_TXIT_ENABLE, HAL_ENABLE);
    hal_uart_write(uart->handle.instance, ch);
}

static void ab32_stop_tx(struct rt_serial_device *serial)
{
    struct ab32_uart *uart;

    RT_ASSERT(serial != RT_NULL);

    uart = rt_container_of(serial, struct ab32_uart, serial);
    hal_uart_control(uart->handle.instance, UART_TXIT_ENABLE, HAL_DISABLE);
    uart->intTxing = RT_FALSE;
}

RT_SECTION(".irq.usart")
static void uart_isr(int vector, void *param)
{
    rt_interrupt_enter();

#ifdef BSP_USING_UART0
    if(hal_uart_getflag(UART0_BASE, UART_FLAG_RXPND))       //RX one byte finish
    {
        rt_hw_serial_isr(&(uart_obj[UART0_INDEX].serial), RT_SERIAL_EVENT_RX_IND);
        hal_uart_clrflag(UART0_BASE, UART_FLAG_RXPND);
    }
    if(hal_uart_getflag(UART0_BASE, UART_FLAG_TXPND))       //TX one byte finish
    {
        rt_hw_serial_isr(&(uart_obj[UART0INDEX].serial), RT_SERIAL_EVENT_TX_DONE);
        hal_uart_clrflag(UART0_BASE, UART_FLAG_TXPND);
    }
#endif
#ifdef BSP_USING_UART1
    if(hal_uart_getflag(UART1_BASE, UART_FLAG_RXPND))       //RX one byte finish
    {
        rt_hw_serial_isr(&(uart_obj[UART1_INDEX].serial), RT_SERIAL_EVENT_RX_IND);
        hal_uart_clrflag(UART1_BASE, UART_FLAG_RXPND);
    }
    if(hal_uart_getflag(UART1_BASE, UART_FLAG_TXPND))       //TX one byte finish
    {
        rt_hw_serial_isr(&(uart_obj[UART1_INDEX].serial), RT_SERIAL_EVENT_TX_DONE);
        hal_uart_clrflag(UART1_BASE, UART_FLAG_TXPND);
    }
#endif
#ifdef BSP_USING_UART2
    if(hal_uart_getflag(UART2_BASE, UART_FLAG_RXPND))       //RX one byte finish
    {
        rt_hw_serial_isr(&(uart_obj[UART2_INDEX].serial), RT_SERIAL_EVENT_RX_IND);
        hal_uart_clrflag(UART2_BASE, UART_FLAG_RXPND);
    }
    if(hal_uart_getflag(UART2_BASE, UART_FLAG_TXPND))       //TX one byte finish
    {
        rt_hw_serial_isr(&(uart_obj[UART2_INDEX].serial), RT_SERIAL_EVENT_TX_DONE);
        hal_uart_clrflag(UART2_BASE, UART_FLAG_TXPND);
    }
#endif

    rt_interrupt_leave();
}

#ifdef HUART_ENABLE
RT_SECTION(".irq.huart")
void huart_timer_isr(void)
{
    huart_if_rx_ovflow();

    if (0 == huart_get_rxcnt()) {
        return;
    }
}
#else
RT_SECTION(".irq.huart")
void huart_timer_isr(void)
{
}
#endif

static const struct rt_uart_ops ab32_uart_ops =
{
    .init = ab32_init,
    .configure = ab32_configure,
    .control = ab32_control,
    .putc = ab32_putc,
    .getc = ab32_getc,
    .flush = ab32_flush,
    .is_int_txing = ab32_int_txing,
    .start_tx = ab32_start_tx,
    .stop_tx = ab32_stop_tx,
};

int rt_hw_usart_init(void)
{
    rt_size_t obj_num = sizeof(uart_obj) / sizeof(struct ab32_uart);
    rt_err_t result = 0;

    rt_hw_interrupt_install(IRQ_UART0_2_VECTOR, uart_isr, RT_NULL, "ut_isr");

    for (int i = 0; i < obj_num; i++)
    {
        /* init UART object */
        uart_obj[i].uart_config     = &uart_config[i];
        uart_obj[i].serial.ops      = &ab32_uart_ops;

        /* register UART device */
        result = rt_hw_serial_register(&uart_obj[i].serial, uart_obj[i].uart_config->name,
                                       RT_DEVICE_FLAG_RDWR
                                       | RT_DEVICE_FLAG_INT_RX
                                       | RT_DEVICE_FLAG_INT_TX
                                       , RT_NULL);
        RT_ASSERT(result == RT_EOK);
    }

    return result;
}

#endif
