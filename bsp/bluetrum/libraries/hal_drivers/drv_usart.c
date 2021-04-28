/*
 * Copyright (c) 2020-2021, Bluetrum Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author            Notes
 * 2020-11-20     greedyhao         first version
 */

#include "board.h"
#include "drv_usart.h"
#include <shell.h>

#ifdef RT_USING_SERIAL

//#define DRV_DEBUG
#define LOG_TAG             "drv.usart"
#include <drv_log.h>

#undef  RT_SERIAL_USING_DMA

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

static rt_err_t ab32_configure(struct rt_serial_device *serial, struct serial_configure *cfg)
{
    struct ab32_uart *uart;
    RT_ASSERT(serial != RT_NULL);
    RT_ASSERT(cfg != RT_NULL);

    uart = rt_container_of(serial, struct ab32_uart, serial);
    uart->handle.instance           = uart->config->instance;
    uart->handle.init.baud          = cfg->baud_rate;
    uart->handle.init.mode          = uart->config->mode;

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

RT_SECTION(".irq.usart")
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

extern struct finsh_shell *shell;

RT_SECTION(".irq.usart")
static rt_err_t shell_rx_ind(void)
{
    RT_ASSERT(shell != RT_NULL);

    /* release semaphore to let finsh thread rx data */
    rt_sem_release(&shell->rx_sem);

    return RT_EOK;
}

RT_SECTION(".irq.usart")
void uart_irq_process(struct rt_serial_device *serial)
{
    int ch = -1;
    rt_base_t level;
    struct rt_serial_rx_fifo* rx_fifo;

    /* interrupt mode receive */
    rx_fifo = (struct rt_serial_rx_fifo*)serial->serial_rx;
    RT_ASSERT(rx_fifo != RT_NULL);

    while (1)
    {
        ch = serial->ops->getc(serial);
        if (ch == -1) break;


        /* disable interrupt */
        level = rt_hw_interrupt_disable();

        rx_fifo->buffer[rx_fifo->put_index] = ch;
        rx_fifo->put_index += 1;
        if (rx_fifo->put_index >= serial->config.bufsz) rx_fifo->put_index = 0;

        /* if the next position is read index, discard this 'read char' */
        if (rx_fifo->put_index == rx_fifo->get_index)
        {
            rx_fifo->get_index += 1;
            rx_fifo->is_full = RT_TRUE;
            if (rx_fifo->get_index >= serial->config.bufsz) rx_fifo->get_index = 0;

            // _serial_check_buffer_size();
        }

        /* enable interrupt */
        rt_hw_interrupt_enable(level);
    }

    rt_size_t rx_length;

    /* get rx length */
    level = rt_hw_interrupt_disable();
    rx_length = (rx_fifo->put_index >= rx_fifo->get_index)? (rx_fifo->put_index - rx_fifo->get_index):
        (serial->config.bufsz - (rx_fifo->get_index - rx_fifo->put_index));
    rt_hw_interrupt_enable(level);

    if ((serial->parent.rx_indicate != RT_NULL) && (rx_length != 0)) {
    #ifdef RT_CONSOLE_DEVICE_NAME
        if (serial == &uart_obj[*(RT_CONSOLE_DEVICE_NAME + 4) - '0'].serial) {
            shell_rx_ind();
        } else
    #endif
        {
            rt_kprintf("rx_indicate must loacted in the .comm section!\n");
            //serial->parent.rx_indicate(&serial->parent, rx_length);
        }
    }

}

RT_SECTION(".irq.usart")
static void uart_isr(int vector, void *param)
{
    rt_interrupt_enter();

#ifdef BSP_USING_UART0
    if(hal_uart_getflag(UART0_BASE, UART_FLAG_RXPND))       //RX one byte finish
    {
        uart_irq_process(&(uart_obj[UART0_INDEX].serial));
    }
#endif
#ifdef BSP_USING_UART1
    if(hal_uart_getflag(UART1_BASE, UART_FLAG_RXPND))       //RX one byte finish
    {
        uart_irq_process(&(uart_obj[UART1_INDEX].serial));
    }
#endif
#ifdef BSP_USING_UART2
    if(hal_uart_getflag(UART2_BASE, UART_FLAG_RXPND))       //RX one byte finish
    {
        uart_irq_process(&(uart_obj[UART2_INDEX].serial));
    }
#endif

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
