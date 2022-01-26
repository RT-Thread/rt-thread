/*
 * Copyright (c) 2006-2021, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author            Notes
 * 2021-07-29     KyleChan          first version
 */

#include <drv_usart_v2.h>

#ifdef RT_USING_SERIAL_V2

//#define DRV_DEBUG
#define DBG_TAG              "drv.usart"
#ifdef DRV_DEBUG
    #define DBG_LVL               DBG_LOG
#else
    #define DBG_LVL               DBG_INFO
#endif /* DRV_DEBUG */
#include <rtdbg.h>

static struct ra_uart_config uart_config[] =
{
#ifdef BSP_USING_UART6
    UART6_CONFIG,
#endif

#ifdef BSP_USING_UART7
    UART7_CONFIG,
#endif

#ifdef BSP_USING_UART1
    UART1_CONFIG,
#endif
};

enum
{
#ifdef BSP_USING_UART6
    UART6_INDEX,
#endif

#ifdef BSP_USING_UART7
    UART7_INDEX,
#endif

#ifdef BSP_USING_UART1
    UART1_INDEX,
#endif
};

static struct ra_uart uart_obj[sizeof(uart_config) / sizeof(uart_config[0])] = {0};

static void ra_uart_get_config(void)
{
    struct serial_configure config = RT_SERIAL_CONFIG_DEFAULT;

#ifdef BSP_USING_UART6
    uart_obj[UART6_INDEX].serial.config = config;
    uart_obj[UART6_INDEX].uart_dma_flag = 0;

    uart_obj[UART6_INDEX].serial.config.rx_bufsz = BSP_UART6_RX_BUFSIZE;
    uart_obj[UART6_INDEX].serial.config.tx_bufsz = BSP_UART6_TX_BUFSIZE;
#endif

#ifdef BSP_USING_UART7
    uart_obj[UART7_INDEX].serial.config = config;
    uart_obj[UART7_INDEX].uart_dma_flag = 0;

    uart_obj[UART7_INDEX].serial.config.rx_bufsz = BSP_UART7_RX_BUFSIZE;
    uart_obj[UART7_INDEX].serial.config.tx_bufsz = BSP_UART7_TX_BUFSIZE;
#endif

#ifdef BSP_USING_UART1
    uart_obj[UART1_INDEX].serial.config = config;
    uart_obj[UART1_INDEX].uart_dma_flag = 0;

    uart_obj[UART1_INDEX].serial.config.rx_bufsz = BSP_UART1_RX_BUFSIZE;
    uart_obj[UART1_INDEX].serial.config.tx_bufsz = BSP_UART1_TX_BUFSIZE;
#endif
}


/*
 * UART interface
 */
static rt_err_t ra_uart_configure(struct rt_serial_device *serial, struct serial_configure *cfg)
{
    struct ra_uart *uart;
    RT_ASSERT(serial != RT_NULL);
    RT_ASSERT(cfg != RT_NULL);

    fsp_err_t err = FSP_SUCCESS;

    uart = rt_container_of(serial, struct ra_uart, serial);
    RT_ASSERT(uart != RT_NULL);

    err = R_SCI_UART_Open(uart->config->p_api_ctrl, uart->config->p_cfg);
    if (FSP_SUCCESS != err)
    {
        return RT_ERROR;
    }

    return RT_EOK;
}

static rt_err_t ra_uart_control(struct rt_serial_device *serial, int cmd, void *arg)
{
    return RT_EOK;
}

static int ra_uart_putc(struct rt_serial_device *serial, char c)
{
    struct ra_uart *uart;
    RT_ASSERT(serial != RT_NULL);

    uart = rt_container_of(serial, struct ra_uart, serial);
    RT_ASSERT(uart != RT_NULL);

    sci_uart_instance_ctrl_t *p_ctrl = (sci_uart_instance_ctrl_t *)uart->config->p_api_ctrl;

    p_ctrl->p_reg->TDR = c;
    while ((p_ctrl->p_reg->SSR_b.TEND) == 0);

    return RT_EOK;
}

static int ra_uart_getc(struct rt_serial_device *serial)
{
    return RT_EOK;
}

#ifdef BSP_USING_UART6
void uart6_isr_cb(uart_callback_args_t *p_args)
{
    rt_interrupt_enter();

    struct rt_serial_device *serial = &uart_obj[UART6_INDEX].serial;
    RT_ASSERT(serial != RT_NULL);

    if (UART_EVENT_RX_CHAR == p_args->event)
    {
        struct rt_serial_rx_fifo *rx_fifo;
        rx_fifo = (struct rt_serial_rx_fifo *) serial->serial_rx;
        RT_ASSERT(rx_fifo != RT_NULL);

        rt_ringbuffer_putchar(&(rx_fifo->rb), (rt_uint8_t)p_args->data);

        rt_hw_serial_isr(serial, RT_SERIAL_EVENT_RX_IND);
    }

    rt_interrupt_leave();
}
#endif

#ifdef BSP_USING_UART7
void uart7_isr_cb(uart_callback_args_t *p_args)
{
    rt_interrupt_enter();

    struct rt_serial_device *serial = &uart_obj[UART7_INDEX].serial;
    RT_ASSERT(serial != RT_NULL);

    if (UART_EVENT_RX_CHAR == p_args->event)
    {
        struct rt_serial_rx_fifo *rx_fifo;
        rx_fifo = (struct rt_serial_rx_fifo *) serial->serial_rx;
        RT_ASSERT(rx_fifo != RT_NULL);

        rt_ringbuffer_putchar(&(rx_fifo->rb), (rt_uint8_t)p_args->data);

        rt_hw_serial_isr(serial, RT_SERIAL_EVENT_RX_IND);
    }

    rt_interrupt_leave();
}
#endif

#ifdef BSP_USING_UART1
void uart1_isr_cb(uart_callback_args_t *p_args)
{
    rt_interrupt_enter();

    struct rt_serial_device *serial = &uart_obj[UART1_INDEX].serial;
    RT_ASSERT(serial != RT_NULL);

    if (UART_EVENT_RX_CHAR == p_args->event)
    {
        struct rt_serial_rx_fifo *rx_fifo;
        rx_fifo = (struct rt_serial_rx_fifo *) serial->serial_rx;
        RT_ASSERT(rx_fifo != RT_NULL);

        rt_ringbuffer_putchar(&(rx_fifo->rb), (rt_uint8_t)p_args->data);

        rt_hw_serial_isr(serial, RT_SERIAL_EVENT_RX_IND);
    }

    rt_interrupt_leave();
}
#endif


static const struct rt_uart_ops ra_uart_ops =
{
    .configure = ra_uart_configure,
    .control = ra_uart_control,
    .putc = ra_uart_putc,
    .getc = ra_uart_getc,
};


int rt_hw_usart_init(void)
{
    rt_err_t result = 0;
    rt_size_t obj_num = sizeof(uart_obj) / sizeof(struct ra_uart);

    ra_uart_get_config();
    for (int i = 0; i < obj_num; i++)
    {
        /* init UART object */
        uart_obj[i].config = &uart_config[i];
        uart_obj[i].serial.ops = &ra_uart_ops;
        /* register UART device */
        result = rt_hw_serial_register(&uart_obj[i].serial,
                                       uart_obj[i].config->name,
                                       RT_DEVICE_FLAG_RDWR,
                                       NULL);
        RT_ASSERT(result == RT_EOK);
    }

    return result;
}

#endif /* RT_USING_SERIAL_V2 */
