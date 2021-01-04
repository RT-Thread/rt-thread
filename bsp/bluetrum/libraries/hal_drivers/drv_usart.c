/*
 * Copyright (c) 2020-2020, Bluetrum Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author            Notes
 * 2020-11-20     greedyhao         first version
 */

#include "board.h"
#include "drv_usart.h"

#ifdef RT_USING_SERIAL

//#define DRV_DEBUG
#define LOG_TAG             "drv.usart"
#include <drv_log.h>

#undef  RT_SERIAL_USING_DMA

enum
{
    UART0_INDEX,
    UART1_INDEX,
};

static struct ab32_uart_config uart_config[] =
{
    {
        .name = "uart0",
        .instance = UART0_BASE,
    },
    {
        .name = "uart1",
        .instance = UART1_BASE,
    }
};

static struct ab32_uart uart_obj[sizeof(uart_config) / sizeof(uart_config[0])] = {0};

static rt_err_t ab32_configure(struct rt_serial_device *serial, struct serial_configure *cfg)
{
    struct ab32_uart *uart;
    RT_ASSERT(serial != RT_NULL);
    RT_ASSERT(cfg != RT_NULL);

    uart = rt_container_of(serial, struct ab32_uart, serial);
    uart->handle.instance           = uart->config->instance;
    uart->handle.init.baud          = cfg->baud_rate;
    uart->handle.init.mode          = UART_MODE_TX_RX;

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

#ifdef RT_SERIAL_USING_DMA
    uart->dma_rx.last_index = 0;
#endif

    hal_uart_init(&uart->handle);

    return RT_EOK;
}

static rt_err_t ab32_control(struct rt_serial_device *serial, int cmd, void *arg)
{
    struct ab32_uart *uart;
#ifdef RT_SERIAL_USING_DMA
    rt_ubase_t ctrl_arg = (rt_ubase_t)arg;
#endif

    RT_ASSERT(serial != RT_NULL);
    uart = rt_container_of(serial, struct ab32_uart, serial);

    switch (cmd)
    {
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
    hal_uart_clrflag(uart->handle.instance,  UART_FLAG_TXPND);
    hal_uart_write(uart->handle.instance, ch);
    while(hal_uart_getflag(uart->handle.instance, UART_FLAG_TXPND) == 0);

    return 1;
}

static int ab32_getc(struct rt_serial_device *serial)
{
    int ch;
    struct ab32_uart *uart;
    RT_ASSERT(serial != RT_NULL);
    uart = rt_container_of(serial, struct ab32_uart, serial);

    ch = -1;
    if(hal_uart_getflag(uart->handle.instance, UART_FLAG_RXPND) != HAL_RESET) {
        ch = hal_uart_read(uart->handle.instance);
        hal_uart_clrflag(uart->handle.instance, UART_FLAG_RXPND);
    }

    return ch;
}

static rt_size_t ab32_dma_transmit(struct rt_serial_device *serial, rt_uint8_t *buf, rt_size_t size, int direction)
{
    return -1;
}

static void uart_isr(int vector, void *param)
{
    rt_interrupt_enter();

    if(hal_uart_getflag(UART0_BASE, UART_FLAG_RXPND))       //RX one byte finish
    {
        rt_hw_serial_isr(&(uart_obj[UART0_INDEX].serial), RT_SERIAL_EVENT_RX_IND);
    }
    // if(hal_uart_getflag(UART1_BASE, UART_FLAG_RXPND))       //RX one byte finish
    // {
    //     rt_hw_serial_isr(&(uart_obj[UART1_INDEX].serial), RT_SERIAL_EVENT_RX_IND);
    // }

    rt_interrupt_leave();
}

static const struct rt_uart_ops ab32_uart_ops =
{
    .configure = ab32_configure,
    .control = ab32_control,
    .putc = ab32_putc,
    .getc = ab32_getc,
    .dma_transmit = ab32_dma_transmit
};

int rt_hw_usart_init(void)
{
    rt_size_t obj_num = sizeof(uart_obj) / sizeof(struct ab32_uart);
    struct serial_configure config = RT_SERIAL_CONFIG_DEFAULT;
    rt_err_t result = 0;

    rt_hw_interrupt_install(IRQ_UART0_2_VECTOR, uart_isr, RT_NULL, "ut_isr");

    for (int i = 0; i < obj_num; i++)
    {
        /* init UART object */
        uart_obj[i].config          = &uart_config[i];
        uart_obj[i].serial.ops      = &ab32_uart_ops;
        uart_obj[i].serial.config   = config;
        uart_obj[i].serial.config.baud_rate = 1500000;

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

#endif
