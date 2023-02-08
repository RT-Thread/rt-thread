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
#include "api_huart.h"

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
        .fifo_size = BSP_UART0_FIFO_SIZE,
    },
#endif
#ifdef BSP_USING_UART1
    {
        .name = "uart1",
        .instance = UART1_BASE,
        .mode = UART_MODE_TX_RX,
        .fifo_size = BSP_UART1_FIFO_SIZE,
    },
#endif
#ifdef BSP_USING_UART2
    {
        .name = "uart2",
        .instance = UART2_BASE,
        .mode = UART_MODE_TX_RX,
        .fifo_size = BSP_UART2_FIFO_SIZE,
    }
#endif
};

static struct ab32_uart uart_obj[sizeof(uart_config) / sizeof(uart_config[0])] = {0};

#ifdef HUART_ENABLE
static rt_uint8_t huart_dma[512];
#endif

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

    if (!uart->uart_dma_flag) {
        hal_uart_init(&uart->handle);
    }
#ifdef HUART_ENABLE
    else {
        huart_init_do(HUART_TR_PB3, HUART_TR_PB4, uart->handle.init.baud, huart_dma, 512);
    }
#endif

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

    if (!uart->uart_dma_flag) {
        hal_uart_clrflag(uart->handle.instance,  UART_FLAG_TXPND);
        hal_uart_write(uart->handle.instance, ch);
        while(hal_uart_getflag(uart->handle.instance, UART_FLAG_TXPND) == 0);
    }
#ifdef HUART_ENABLE
    else {
        huart_putchar(ch);
    }
#endif

    return 1;
}

static int ab32_getc(struct rt_serial_device *serial)
{
    int ch;
    struct ab32_uart *uart;
    RT_ASSERT(serial != RT_NULL);

    uart = rt_container_of(serial, struct ab32_uart, serial);

    ch = -1;
    switch ((rt_uint32_t)(uart->handle.instance)) {
        case (rt_uint32_t)UART0_BASE:
            if (uart->rx_idx != uart->rx_idx_prev) {
                ch = (int)(uart->rx_buf[uart->rx_idx_prev++ % 10]);
            }
            break;
        case (rt_uint32_t)UART1_BASE:
#ifdef HUART_ENABLE
            if ((uart->uart_dma_flag) && (huart_get_rxcnt())) {
                ch = huart_getchar();
            } else
#endif
            {
                if (uart->rx_idx != uart->rx_idx_prev) {
                    ch = (int)(uart->rx_buf[uart->rx_idx_prev++ % 10]);
                }
            }
            break;
        case (rt_uint32_t)UART2_BASE:
            if (uart->rx_idx != uart->rx_idx_prev) {
                ch = (int)(uart->rx_buf[uart->rx_idx_prev++ % 10]);
            }
            break;
        default:
            break;
    }

    return ch;
}

static rt_ssize_t ab32_dma_transmit(struct rt_serial_device *serial, rt_uint8_t *buf, rt_size_t size, int direction)
{
    return -1;
}

void uart0_irq_process(void)
{
    rt_hw_serial_isr(&(uart_obj[UART0_INDEX].serial), RT_SERIAL_EVENT_RX_IND);
}

#ifdef BSP_USING_UART1
void uart1_irq_process(void)
{
    rt_hw_serial_isr(&(uart_obj[UART1_INDEX].serial), RT_SERIAL_EVENT_RX_IND);
}
#endif

#ifdef BSP_USING_UART2
void uart2_irq_process(void)
{
    rt_hw_serial_isr(&(uart_obj[UART2_INDEX].serial), RT_SERIAL_EVENT_RX_IND);
}
#endif

rt_section(".irq.usart")
static void uart_isr(int vector, void *param)
{
    rt_interrupt_enter();

#ifdef BSP_USING_UART0
    if(hal_uart_getflag(UART0_BASE, UART_FLAG_RXPND))       //RX one byte finish
    {
        uart_obj[0].rx_buf[uart_obj[0].rx_idx++ % 10] = hal_uart_read(UART0_BASE);
        hal_uart_clrflag(UART0_BASE, UART_FLAG_RXPND);
        uart0_irq_post();
    }
#endif
#ifdef BSP_USING_UART1
    if(hal_uart_getflag(UART1_BASE, UART_FLAG_RXPND))       //RX one byte finish
    {
        uart_obj[1].rx_buf[uart_obj[1].rx_idx++ % 10] = hal_uart_read(UART1_BASE);
        hal_uart_clrflag(UART1_BASE, UART_FLAG_RXPND);
        uart1_irq_post();
    }
#endif
#ifdef BSP_USING_UART2
    if(hal_uart_getflag(UART2_BASE, UART_FLAG_RXPND))       //RX one byte finish
    {
        uart_obj[2].rx_buf[uart_obj[2].rx_idx++ % 10] = hal_uart_read(UART2_BASE);
        hal_uart_clrflag(UART2_BASE, UART_FLAG_RXPND);
        uart2_irq_post();
    }
#endif

    rt_interrupt_leave();
}

#ifdef HUART_ENABLE
rt_section(".irq.huart")
void huart_timer_isr(void)
{
    huart_if_rx_ovflow();

    if (0 == huart_get_rxcnt()) {
        return;
    }

    uart1_irq_post();
}
#else
rt_section(".irq.huart")
void huart_timer_isr(void)
{
}
#endif

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
        uart_obj[i].rx_idx          = 0;
        uart_obj[i].rx_idx_prev     = 0;
        uart_obj[i].serial.ops      = &ab32_uart_ops;
        uart_obj[i].serial.config   = config;
        uart_obj[i].serial.config.baud_rate = 1500000;
        uart_obj[i].rx_buf          = rt_malloc(uart_config[i].fifo_size);

        if (uart_obj[i].rx_buf == RT_NULL) {
            LOG_E("uart%d malloc failed!", i);
            continue;
        }

        /* register UART device */
        result = rt_hw_serial_register(&uart_obj[i].serial, uart_obj[i].config->name,
                                       RT_DEVICE_FLAG_RDWR
                                       | RT_DEVICE_FLAG_INT_RX
                                       | RT_DEVICE_FLAG_INT_TX
                                       | uart_obj[i].uart_dma_flag
                                       , RT_NULL);
        RT_ASSERT(result == RT_EOK);
    }

    return result;
}

#endif
