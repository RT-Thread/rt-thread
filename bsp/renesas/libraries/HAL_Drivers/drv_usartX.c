/*
 * Copyright (c) 2006-2022, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author            Notes
 * 2021-07-29     KyleChan          first version
 * 2022-06-08     THEWON            first version for serialX
 */

#include <drv_usartX.h>

#ifdef RT_USING_SERIAL_X

//#define DRV_DEBUG
#define DBG_TAG              "drv.usart"
#ifdef DRV_DEBUG
    #define DBG_LVL               DBG_LOG
#else
    #define DBG_LVL               DBG_INFO
#endif /* DRV_DEBUG */
#include <rtdbg.h>

/* SCI SCR register bit masks */
#define SCI_SCR_TEIE_MASK                       (0x04U) ///< Transmit End Interrupt Enable
#define SCI_SCR_RE_MASK                         (0x10U) ///< Receive Enable
#define SCI_SCR_TE_MASK                         (0x20U) ///< Transmit Enable
#define SCI_SCR_RIE_MASK                        (0x40U) ///< Receive Interrupt Enable
#define SCI_SCR_TIE_MASK                        (0x80U) ///< Transmit Interrupt Enable

static struct ra_uart_config uart_config[] =
{
#ifdef BSP_USING_UART0
    UART0_CONFIG,
#endif

#ifdef BSP_USING_UART1
    UART1_CONFIG,
#endif

#ifdef BSP_USING_UART2
    UART2_CONFIG,
#endif

#ifdef BSP_USING_UART3
    UART3_CONFIG,
#endif

#ifdef BSP_USING_UART4
    UART4_CONFIG,
#endif

#ifdef BSP_USING_UART5
    UART5_CONFIG,
#endif

#ifdef BSP_USING_UART6
    UART6_CONFIG,
#endif

#ifdef BSP_USING_UART7
    UART7_CONFIG,
#endif

#ifdef BSP_USING_UART8
    UART8_CONFIG,
#endif

#ifdef BSP_USING_UART9
    UART9_CONFIG,
#endif
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

#ifdef BSP_USING_UART4
    UART4_INDEX,
#endif

#ifdef BSP_USING_UART5
    UART5_INDEX,
#endif

#ifdef BSP_USING_UART6
    UART6_INDEX,
#endif

#ifdef BSP_USING_UART7
    UART7_INDEX,
#endif

#ifdef BSP_USING_UART8
    UART8_INDEX,
#endif

#ifdef BSP_USING_UART9
    UART9_INDEX,
#endif
};

static struct ra_uart uart_obj[sizeof(uart_config) / sizeof(uart_config[0])] = {0};

static void ra_uart_get_config(void)
{
    struct serial_configure config = RT_SERIAL_CONFIG_DEFAULT;

#ifdef BSP_USING_UART0
    uart_obj[UART0_INDEX].serial.config = config;
#endif

#ifdef BSP_USING_UART1
    uart_obj[UART1_INDEX].serial.config = config;
#endif

#ifdef BSP_USING_UART2
    uart_obj[UART2_INDEX].serial.config = config;
#endif

#ifdef BSP_USING_UART3
    uart_obj[UART3_INDEX].serial.config = config;
#endif

#ifdef BSP_USING_UART4
    uart_obj[UART4_INDEX].serial.config = config;
#endif

#ifdef BSP_USING_UART6
    uart_obj[UART6_INDEX].serial.config = config;
#endif

#ifdef BSP_USING_UART7
    uart_obj[UART7_INDEX].serial.config = config;
    uart_config[UART7_INDEX].uart_cfg = g_uart7_cfg;
#endif

#ifdef BSP_USING_UART8
    uart_obj[UART8_INDEX].serial.config = config;
#endif

#ifdef BSP_USING_UART9
    uart_obj[UART9_INDEX].serial.config = config;
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

    if (cfg->data_bits == DATA_BITS_7)
    {
        uart->uart_config->uart_cfg.data_bits = UART_DATA_BITS_7;
    }
    else if (cfg->data_bits == DATA_BITS_8)
    {
        uart->uart_config->uart_cfg.data_bits = UART_DATA_BITS_8;
    }
    else if (cfg->data_bits == DATA_BITS_9)
    {
        uart->uart_config->uart_cfg.data_bits = UART_DATA_BITS_9;
    }

    if (cfg->stop_bits == STOP_BITS_1)
    {
        uart->uart_config->uart_cfg.stop_bits = UART_STOP_BITS_1;
    }
    else if (cfg->stop_bits == STOP_BITS_2)
    {
        uart->uart_config->uart_cfg.stop_bits = UART_STOP_BITS_2;
    }

    if (cfg->parity == PARITY_NONE)
    {
        uart->uart_config->uart_cfg.parity = UART_PARITY_OFF;
    }
    else if (cfg->parity == PARITY_ODD)
    {
        uart->uart_config->uart_cfg.parity = UART_PARITY_ODD;
    }
    else if (cfg->parity == PARITY_EVEN)
    {
        uart->uart_config->uart_cfg.parity = UART_PARITY_EVEN;
    }

    err = R_SCI_UART_Open(uart->uart_config->p_api_ctrl, &uart->uart_config->uart_cfg);
    if (FSP_SUCCESS != err)
    {
        return -RT_ERROR;
    }

    return RT_EOK;
}

/*
 * Initialize UART interface
 */
static rt_err_t ra_uart_init(struct rt_serial_device *serial)
{
    if (ra_uart_configure(serial, &serial->config) != RT_EOK)
    {
        return -RT_ERROR;
    }

    return RT_EOK;
}

static rt_err_t ra_uart_control(struct rt_serial_device *serial, int cmd, void *arg)
{
    struct ra_uart *uart;

    RT_ASSERT(serial != RT_NULL);

    uart = rt_container_of(serial, struct ra_uart, serial);

    switch (cmd) {
    case RT_DEVICE_CTRL_OPEN:
        uart->intTxing = RT_FALSE;
    break;
    case RT_DEVICE_CTRL_CLOSE:
        R_SCI_UART_Close(uart->uart_config->p_api_ctrl);
    break;
    case RT_DEVICE_CTRL_CLR_INT:
        /* disable interrupt */
    break;
    case RT_DEVICE_CTRL_SET_INT:
        /* enable interrupt */
    break;
    /* USART config */
    case RT_DEVICE_CTRL_CONFIG :
    break;
    default :
    break;
    }
    return RT_EOK;
}

static int ra_uart_putc(struct rt_serial_device *serial, char c, rt_bool_t useint)
{
    struct ra_uart *uart;

    RT_ASSERT(serial != RT_NULL);

    uart = rt_container_of(serial, struct ra_uart, serial);

    sci_uart_instance_ctrl_t *p_ctrl = (sci_uart_instance_ctrl_t *)uart->uart_config->p_api_ctrl;

    while ((p_ctrl->p_reg->SSR_b.TDRE) == 0);
    p_ctrl->p_reg->TDR = c;
    if (useint) {
        p_ctrl->p_reg->SCR |= SCI_SCR_TE_MASK;
        p_ctrl->p_reg->SCR |= SCI_SCR_TIE_MASK;
    }

    return RT_EOK;
}

static int ra_uart_getc(struct rt_serial_device *serial)
{
    int ch;
    struct ra_uart *uart;

    RT_ASSERT(serial != RT_NULL);

    uart = rt_container_of(serial, struct ra_uart, serial);

    sci_uart_instance_ctrl_t *p_ctrl = (sci_uart_instance_ctrl_t *)uart->uart_config->p_api_ctrl;

    ch = -1;
    if ((p_ctrl->p_reg->SSR_b.RDRF) == 1) {
        ch = p_ctrl->p_reg->RDR & 0xFF;
        p_ctrl->p_reg->SSR_b.RDRF = 0;
    }

    return ch;
}

static int ra_uart_flush(struct rt_serial_device *serial)
{
    struct ra_uart *uart;

    RT_ASSERT(serial != RT_NULL);

    uart = rt_container_of(serial, struct ra_uart, serial);

    sci_uart_instance_ctrl_t *p_ctrl = (sci_uart_instance_ctrl_t *)uart->uart_config->p_api_ctrl;

    while (!((p_ctrl->p_reg->SSR_b.TEND) == 1 && (p_ctrl->p_reg->SSR_b.TDRE) == 1));

    return 0;
}

rt_bool_t ra_int_txing(struct rt_serial_device *serial)
{
    struct ra_uart *uart;

    RT_ASSERT(serial != RT_NULL);

    uart = rt_container_of(serial, struct ra_uart, serial);

    return uart->intTxing;
}

static void ra_start_tx(struct rt_serial_device *serial, rt_uint8_t ch)
{
    struct ra_uart *uart;

    RT_ASSERT(serial != RT_NULL);

    uart = rt_container_of(serial, struct ra_uart, serial);

    sci_uart_instance_ctrl_t *p_ctrl = (sci_uart_instance_ctrl_t *)uart->uart_config->p_api_ctrl;

    uart->intTxing = RT_TRUE;
    p_ctrl->p_reg->SCR &= ~(SCI_SCR_TIE_MASK | SCI_SCR_TEIE_MASK);
    p_ctrl->p_reg->TDR = ch;
    p_ctrl->p_reg->SCR |= SCI_SCR_TE_MASK;
    /* Trigger a TXI interrupt. This triggers the transfer instance or a TXI interrupt if the transfer instance is
     * not used. */
    p_ctrl->p_reg->SCR |= SCI_SCR_TIE_MASK;
}

static void ra_stop_tx(struct rt_serial_device *serial)
{
    struct ra_uart *uart;

    RT_ASSERT(serial != RT_NULL);

    uart = rt_container_of(serial, struct ra_uart, serial);

    sci_uart_instance_ctrl_t *p_ctrl = (sci_uart_instance_ctrl_t *)uart->uart_config->p_api_ctrl;

    p_ctrl->p_reg->SCR &= ~(SCI_SCR_TIE_MASK | SCI_SCR_TEIE_MASK);
    uart->intTxing = RT_FALSE;
}

#ifdef BSP_USING_UART0
void user_uart0_callback(uart_callback_args_t *p_args)
{
    rt_interrupt_enter();

    struct rt_serial_device *serial = &uart_obj[UART0_INDEX].serial;
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
void user_uart1_callback(uart_callback_args_t *p_args)
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

#ifdef BSP_USING_UART2
void user_uart2_callback(uart_callback_args_t *p_args)
{
    rt_interrupt_enter();

    struct rt_serial_device *serial = &uart_obj[UART2_INDEX].serial;
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

#ifdef BSP_USING_UART3
void user_uart3_callback(uart_callback_args_t *p_args)
{
    rt_interrupt_enter();

    struct rt_serial_device *serial = &uart_obj[UART3_INDEX].serial;
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

#ifdef BSP_USING_UART4
void user_uart4_callback(uart_callback_args_t *p_args)
{
    rt_interrupt_enter();

    struct rt_serial_device *serial = &uart_obj[UART4_INDEX].serial;
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

#ifdef BSP_USING_UART5
void user_uart5_callback(uart_callback_args_t *p_args)
{
    rt_interrupt_enter();

    struct rt_serial_device *serial = &uart_obj[UART5_INDEX].serial;
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

#ifdef BSP_USING_UART6
void user_uart6_callback(uart_callback_args_t *p_args)
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
void user_uart7_callback(uart_callback_args_t *p_args)
{
    rt_interrupt_enter();

    struct rt_serial_device *serial = &uart_obj[UART7_INDEX].serial;
    RT_ASSERT(serial != RT_NULL);

    if (UART_EVENT_RX_CHAR == p_args->event)
    {
        rt_hw_serial_isr(serial, RT_SERIAL_EVENT_RX_IND);
    } else if (UART_EVENT_TX_COMPLETE == p_args->event) {
        rt_hw_serial_isr(serial, RT_SERIAL_EVENT_TX_DONE);
    }

    rt_interrupt_leave();
}
#endif

#ifdef BSP_USING_UART8
void user_uart8_callback(uart_callback_args_t *p_args)
{
    rt_interrupt_enter();

    struct rt_serial_device *serial = &uart_obj[UART8_INDEX].serial;
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

#ifdef BSP_USING_UART9
void user_uart9_callback(uart_callback_args_t *p_args)
{
    rt_interrupt_enter();

    struct rt_serial_device *serial = &uart_obj[UART9_INDEX].serial;
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
    .init = ra_uart_init,
    .configure = ra_uart_configure,
    .control = ra_uart_control,
    .putc = ra_uart_putc,
    .getc = ra_uart_getc,
    .flush = ra_uart_flush,
    .is_int_txing = ra_int_txing,
    .start_tx = ra_start_tx,
    .stop_tx = ra_stop_tx,
};


int rt_hw_usart_init(void)
{
    rt_err_t result = 0;
    rt_size_t obj_num = sizeof(uart_obj) / sizeof(struct ra_uart);

    ra_uart_get_config();
    for (int i = 0; i < obj_num; i++)
    {
        /* init UART object */
        uart_obj[i].uart_config = &uart_config[i];
        uart_obj[i].serial.ops = &ra_uart_ops;
        /* register UART device */
        result = rt_hw_serial_register(&uart_obj[i].serial,
                                       uart_obj[i].uart_config->name,
                                       RT_DEVICE_FLAG_RDWR |
                                       RT_DEVICE_FLAG_INT_RX | RT_DEVICE_FLAG_INT_TX,
                                       NULL);
        RT_ASSERT(result == RT_EOK);
    }

    return result;
}

#endif /* RT_USING_SERIAL_X */
