/*
 * Copyright (C) 2022 Shanghai Eastsoft Microelectronics Co., Ltd.
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Licensed under the Apache License, Version 2.0 (the License); you may
 * not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 * www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an AS IS BASIS, WITHOUT
 * WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 *
 * Change Logs:
 * Date           Author        Notes
 * 2023-02-11     liuhy         the first version
 */

#include "drv_uart.h"

#ifdef RT_USING_SERIAL

#define UART_DMA_BUF_SECTIONS 4

/*
 * To use UART DMA,
 * 1. select 'DMA->DMA0'
 * 2. select 'UART->UARTx->DMATX(or DMARX)'
 * 3. add RT_DEVICE_FLAG_DMA_TX(or RT_DEVICE_FLAG_DMA_RX) flag when open serial device
 */
#ifdef BSP_EUART0_TX_USING_DMA
#define EUART0_DMATX_CHANNEL ES_EUART0_DMATX_CHANNEL
#define EUART0_DMATX_FLAG RT_DEVICE_FLAG_DMA_TX
#else
#define EUART0_DMATX_CHANNEL ES_DMA_INVAILD_CHANNEL
#define EUART0_DMATX_FLAG 0
#endif

#ifdef BSP_EUART0_RX_USING_DMA
#define EUART0_DMARX_CHANNEL ES_EUART0_DMARX_CHANNEL
#define EUART0_DMARX_FLAG RT_DEVICE_FLAG_DMA_RX
#else
#define EUART0_DMARX_CHANNEL ES_DMA_INVAILD_CHANNEL
#define EUART0_DMARX_FLAG 0
#endif

#ifdef BSP_EUART1_TX_USING_DMA
#define EUART1_DMATX_CHANNEL ES_EUART1_DMATX_CHANNEL
#define EUART1_DMATX_FLAG RT_DEVICE_FLAG_DMA_TX
#else
#define EUART1_DMATX_CHANNEL ES_DMA_INVAILD_CHANNEL
#define EUART1_DMATX_FLAG 0
#endif

#ifdef BSP_EUART1_RX_USING_DMA
#define EUART1_DMARX_CHANNEL ES_EUART1_DMARX_CHANNEL
#define EUART1_DMARX_FLAG RT_DEVICE_FLAG_DMA_RX
#else
#define EUART1_DMARX_CHANNEL ES_DMA_INVAILD_CHANNEL
#define EUART1_DMARX_FLAG 0
#endif

#ifdef BSP_CUART0_TX_USING_DMA
#define CUART0_DMATX_CHANNEL ES_CUART0_DMATX_CHANNEL
#define CUART0_DMATX_FLAG RT_DEVICE_FLAG_DMA_TX
#else
#define CUART0_DMATX_CHANNEL ES_DMA_INVAILD_CHANNEL
#define CUART0_DMATX_FLAG 0
#endif

#ifdef BSP_CUART0_RX_USING_DMA
#define CUART0_DMARX_CHANNEL ES_CUART0_DMARX_CHANNEL
#define CUART0_DMARX_FLAG RT_DEVICE_FLAG_DMA_RX
#else
#define CUART0_DMARX_CHANNEL ES_DMA_INVAILD_CHANNEL
#define CUART0_DMARX_FLAG 0
#endif

#ifdef BSP_CUART1_TX_USING_DMA
#define CUART1_DMATX_CHANNEL ES_CUART1_DMATX_CHANNEL
#define CUART1_DMATX_FLAG RT_DEVICE_FLAG_DMA_TX
#else
#define CUART1_DMATX_CHANNEL ES_DMA_INVAILD_CHANNEL
#define CUART1_DMATX_FLAG 0
#endif

#ifdef BSP_CUART1_RX_USING_DMA
#define CUART1_DMARX_CHANNEL ES_CUART1_DMARX_CHANNEL
#define CUART1_DMARX_FLAG RT_DEVICE_FLAG_DMA_RX
#else
#define CUART1_DMARX_CHANNEL ES_DMA_INVAILD_CHANNEL
#define CUART1_DMARX_FLAG 0
#endif

#ifdef BSP_CUART2_TX_USING_DMA
#define CUART2_DMATX_CHANNEL ES_CUART2_DMATX_CHANNEL
#define CUART2_DMATX_FLAG RT_DEVICE_FLAG_DMA_TX
#else
#define CUART2_DMATX_CHANNEL ES_DMA_INVAILD_CHANNEL
#define CUART2_DMATX_FLAG 0
#endif

#ifdef BSP_CUART2_RX_USING_DMA
#define CUART2_DMARX_CHANNEL ES_CUART2_DMARX_CHANNEL
#define CUART2_DMARX_FLAG RT_DEVICE_FLAG_DMA_RX
#else
#define CUART2_DMARX_CHANNEL ES_DMA_INVAILD_CHANNEL
#define CUART2_DMARX_FLAG 0
#endif

#define UART_INVAILD_DMA_CHANNEL (ES_DMA_INVAILD_CHANNEL)

/* es32 uart driver */
struct es32_uart
{
    ald_uart_handle_t huart;
    struct rt_serial_device *serial;
    IRQn_Type irq;
#ifdef RT_SERIAL_USING_DMA
    uint16_t dma_tx_channel;
    uint16_t dma_rx_channel;

    uint32_t last_rx_count;
    uint32_t buf_select;
#endif /* RT_SERIAL_USING_DMA */
};

#ifdef RT_SERIAL_USING_DMA
    static void _dma_recv_timeout(struct es32_uart *uart, uint32_t dma_end);
#endif /* RT_SERIAL_USING_DMA */

static void uart_int_handler(struct es32_uart*uart)
{
    if ((ald_uart_get_mask_flag_status(&uart->huart, ALD_UART_IF_RFNEMPTY)) != RESET)
    {
        rt_hw_serial_isr(uart->serial, RT_SERIAL_EVENT_RX_IND);
        ald_uart_clear_flag_status(&uart->huart, ALD_UART_IF_RFNEMPTY);
    }
    #ifdef RT_SERIAL_USING_DMA
    if ((ald_uart_get_mask_flag_status(&uart->huart, ALD_UART_IF_RXTO)) != RESET)
    {
        ald_uart_clear_flag_status(&uart->huart, ALD_UART_IF_RXTO);
        _dma_recv_timeout(uart, 0);
    }

    if ((ald_uart_get_mask_flag_status(&uart->huart, ALD_UART_IF_TBC)) != RESET)
    {
        uint32_t cnt = 1000;
        ald_uart_clear_flag_status(&uart->huart, ALD_UART_IF_TBC);
        ald_uart_interrupt_config(&uart->huart, ALD_UART_IT_TBC, DISABLE);
        CLEAR_BIT(uart->huart.state, ALD_UART_STATE_TX_MASK);

        while ((uart->huart.perh->STAT & ALD_UART_STATUS_TSBUSY) && (cnt--));

        ald_uart_clear_flag_status(&uart->huart, ALD_UART_IF_TBC);

        if (uart->huart.tx_cplt_cbk)
            uart->huart.tx_cplt_cbk(&uart->huart);
    }
    #endif /* RT_SERIAL_USING_DMA */
}


#ifdef BSP_USING_EUART0

struct rt_serial_device serial0;
/* EUART0 device driver structure */
struct es32_uart uart0 =
{
    {EUART0},
    &serial0,
    EUART0_IRQn,
#ifdef RT_SERIAL_USING_DMA
    EUART0_DMATX_CHANNEL,
    EUART0_DMARX_CHANNEL
#endif /* RT_SERIAL_USING_DMA */
};
void __attribute__((interrupt)) EUART0_Handler(void)
{
    /* enter interrupt */
    rt_interrupt_enter();
    uart_int_handler(&uart0);
    /* leave interrupt */
    rt_interrupt_leave();
}
#endif /* BSP_USING_EUART0 */

#ifdef BSP_USING_EUART1

struct rt_serial_device serial1;
/* EUART1 device driver structure */
struct es32_uart uart1 =
{
    {EUART1},
    &serial1,
    EUART1_IRQn,
#ifdef RT_SERIAL_USING_DMA
    EUART1_DMATX_CHANNEL,
    EUART1_DMARX_CHANNEL
#endif /* RT_SERIAL_USING_DMA */
};

void __attribute__((interrupt)) EUART1_Handler(void)
{
    /* enter interrupt */
    rt_interrupt_enter();
    uart_int_handler(&uart1);
    /* leave interrupt */
    rt_interrupt_leave();
}
#endif /* BSP_USING_EUART1 */

#ifdef BSP_USING_CUART0

struct rt_serial_device serial2;
/* CUART0 device driver structure */
struct es32_uart uart2 =
{
    {CUART0},
    &serial2,
    CUART0_IRQn,
#ifdef RT_SERIAL_USING_DMA
    CUART0_DMATX_CHANNEL,
    CUART0_DMARX_CHANNEL
#endif /* RT_SERIAL_USING_DMA */
};

void __attribute__((interrupt)) CUART0_Handler(void)
{
    /* enter interrupt */
    rt_interrupt_enter();
    uart_int_handler(&uart2);
    /* leave interrupt */
    rt_interrupt_leave();
}
#endif /* BSP_USING_CUART0 */

#ifdef BSP_USING_CUART1

struct rt_serial_device serial3;
/* CUART1 device driver structure */
struct es32_uart uart3 =
{
    {CUART1},
    &serial3,
    CUART1_IRQn,
#ifdef RT_SERIAL_USING_DMA
    CUART1_DMATX_CHANNEL,
    CUART1_DMARX_CHANNEL
#endif /* RT_SERIAL_USING_DMA */
};

void __attribute__((interrupt)) CUART1_Handler(void)
{
    /* enter interrupt */
    rt_interrupt_enter();
    uart_int_handler(&uart3);
    /* leave interrupt */
    rt_interrupt_leave();
}
#endif /* BSP_USING_CUART1 */

#ifdef BSP_USING_CUART2

struct rt_serial_device serial4;
/* CUART2 device driver structure */
struct es32_uart uart4 =
{
    {CUART2},
    &serial4,
    CUART2_IRQn,
#ifdef RT_SERIAL_USING_DMA
    CUART2_DMATX_CHANNEL,
    CUART2_DMARX_CHANNEL
#endif /* RT_SERIAL_USING_DMA */
};

void __attribute__((interrupt)) CUART2_Handler(void)
{
    /* enter interrupt */
    rt_interrupt_enter();
    uart_int_handler(&uart4);
    /* leave interrupt */
    rt_interrupt_leave();
}
#endif /* BSP_USING_CUART2 */

static rt_err_t es32f3x_configure(struct rt_serial_device *serial, struct serial_configure *cfg)
{
    ald_gpio_init_t gpio_initstructure;
    struct es32_uart *uart;
    RT_ASSERT(serial != RT_NULL);
    RT_ASSERT(cfg != RT_NULL);
    uart = (struct es32_uart *)serial->parent.user_data;

    /* Initialize tx pin */
    gpio_initstructure.mode = ALD_GPIO_MODE_OUTPUT;
    gpio_initstructure.od = ALD_GPIO_PUSH_PULL;
    gpio_initstructure.pupd = ALD_GPIO_PUSH_UP;
    gpio_initstructure.odrv = ALD_GPIO_OUT_DRIVE_NORMAL;
    gpio_initstructure.flt  = ALD_GPIO_FILTER_DISABLE;
    gpio_initstructure.type = ALD_GPIO_TYPE_CMOS;

#ifdef BSP_USING_EUART0

    if (uart == (&uart0))
    {
#if  defined(ES_EUART0_TX_GPIO_FUNC)&&defined(ES_EUART0_TX_GPIO_PORT)&&defined(ES_EUART0_TX_GPIO_PIN)
        gpio_initstructure.func = ES_EUART0_TX_GPIO_FUNC;
        ald_gpio_init(ES_EUART0_TX_GPIO_PORT, ES_EUART0_TX_GPIO_PIN, &gpio_initstructure);
#endif

#if  defined(ES_EUART0_RX_GPIO_FUNC)&&defined(ES_EUART0_RX_GPIO_PORT)&&defined(ES_EUART0_RX_GPIO_PIN)
        /* Initialize rx pin ,the same as txpin except mode */
        gpio_initstructure.mode = ALD_GPIO_MODE_INPUT;
        gpio_initstructure.func = ES_EUART0_RX_GPIO_FUNC;
        ald_gpio_init(ES_EUART0_RX_GPIO_PORT, ES_EUART0_RX_GPIO_PIN, &gpio_initstructure);
#endif
    }

#endif /* uart0 gpio init */

#ifdef BSP_USING_EUART1

    if (uart == (&uart1))
    {
#if  defined(ES_EUART1_TX_GPIO_FUNC)&&defined(ES_EUART1_TX_GPIO_PORT)&&defined(ES_EUART1_TX_GPIO_PIN)
        gpio_initstructure.func = ES_EUART1_TX_GPIO_FUNC;
        ald_gpio_init(ES_EUART1_TX_GPIO_PORT, ES_EUART1_TX_GPIO_PIN, &gpio_initstructure);
#endif

#if  defined(ES_EUART1_RX_GPIO_FUNC)&&defined(ES_EUART1_RX_GPIO_PORT)&&defined(ES_EUART1_RX_GPIO_PIN)
        /* Initialize rx pin ,the same as txpin except mode */
        gpio_initstructure.mode = ALD_GPIO_MODE_INPUT;
        gpio_initstructure.func = ES_EUART1_RX_GPIO_FUNC;
        ald_gpio_init(ES_EUART1_RX_GPIO_PORT, ES_EUART1_RX_GPIO_PIN, &gpio_initstructure);
#endif
    }

#endif /* uart1 gpio init */

#ifdef BSP_USING_CUART0

    if (uart == (&uart2))
    {
#if  defined(ES_CUART0_TX_GPIO_FUNC)&&defined(ES_CUART0_TX_GPIO_PORT)&&defined(ES_CUART0_TX_GPIO_PIN)
        gpio_initstructure.func = ES_CUART0_TX_GPIO_FUNC;
        ald_gpio_init(ES_CUART0_TX_GPIO_PORT, ES_CUART0_TX_GPIO_PIN, &gpio_initstructure);
#endif

#if  defined(ES_CUART0_RX_GPIO_FUNC)&&defined(ES_CUART0_RX_GPIO_PORT)&&defined(ES_CUART0_RX_GPIO_PIN)
        /* Initialize rx pin ,the same as txpin except mode */
        gpio_initstructure.mode = ALD_GPIO_MODE_INPUT;
        gpio_initstructure.func = ES_CUART0_RX_GPIO_FUNC;
        ald_gpio_init(ES_CUART0_RX_GPIO_PORT, ES_CUART0_RX_GPIO_PIN, &gpio_initstructure);
#endif
    }

#endif /* uart2 gpio init */

#ifdef BSP_USING_CUART1

    if (uart == (&uart3))
    {
#if  defined(ES_CUART1_TX_GPIO_FUNC)&&defined(ES_CUART1_TX_GPIO_PORT)&&defined(ES_CUART1_TX_GPIO_PIN)
        gpio_initstructure.func = ES_CUART1_TX_GPIO_FUNC;
        ald_gpio_init(ES_CUART1_TX_GPIO_PORT, ES_CUART1_TX_GPIO_PIN, &gpio_initstructure);
#endif

#if  defined(ES_CUART1_RX_GPIO_FUNC)&&defined(ES_CUART1_RX_GPIO_PORT)&&defined(ES_CUART1_RX_GPIO_PIN)
        /* Initialize rx pin ,the same as txpin except mode */
        gpio_initstructure.mode = ALD_GPIO_MODE_INPUT;
        gpio_initstructure.func = ES_CUART1_RX_GPIO_FUNC;
        ald_gpio_init(ES_CUART1_RX_GPIO_PORT, ES_CUART1_RX_GPIO_PIN, &gpio_initstructure);
#endif
    }

#endif /* uart3 gpio init */

#ifdef BSP_USING_CUART2

    if (uart == (&uart4))
    {
#if  defined(ES_CUART2_TX_GPIO_FUNC)&&defined(ES_CUART2_TX_GPIO_PORT)&&defined(ES_CUART2_TX_GPIO_PIN)
        gpio_initstructure.func = ES_CUART2_TX_GPIO_FUNC;
        ald_gpio_init(ES_CUART2_TX_GPIO_PORT, ES_CUART2_TX_GPIO_PIN, &gpio_initstructure);
#endif

#if  defined(ES_CUART2_RX_GPIO_FUNC)&&defined(ES_CUART2_RX_GPIO_PORT)&&defined(ES_CUART2_RX_GPIO_PIN)
        /* Initialize rx pin ,the same as txpin except mode */
        gpio_initstructure.mode = ALD_GPIO_MODE_INPUT;
        gpio_initstructure.func = ES_CUART2_RX_GPIO_FUNC;
        ald_gpio_init(ES_CUART2_RX_GPIO_PORT, ES_CUART2_RX_GPIO_PIN, &gpio_initstructure);
#endif
    }

#endif /* uart4 gpio init */

    uart->huart.init.mode        = ALD_UART_MODE_UART;
    uart->huart.init.baud        = cfg->baud_rate;
    uart->huart.init.word_length = (ald_uart_word_length_t)(8 - cfg->data_bits);
    uart->huart.init.parity = (ald_uart_parity_t)(cfg->parity == PARITY_EVEN ? ALD_UART_PARITY_EVEN : cfg->parity);
    uart->huart.init.fctl        = ALD_UART_HW_FLOW_CTL_DISABLE;
    uart->huart.init.stop_bits        = ALD_UART_STOP_BITS_1;
    ald_uart_init(&uart->huart);

    if (cfg->bit_order == BIT_ORDER_MSB)
    {
        ALD_UART_MSB_FIRST_ENABLE(&uart->huart);
    }
    else
    {
        ALD_UART_MSB_FIRST_DISABLE(&uart->huart);
    }

    if (cfg->invert == NRZ_INVERTED)
    {
        ALD_UART_DATA_INV_ENABLE(&uart->huart);
    }
    else
    {
        ALD_UART_DATA_INV_DISABLE(&uart->huart);
    }

    return RT_EOK;
}



#ifdef RT_SERIAL_USING_DMA

static void _dma_recv_timeout(struct es32_uart *uart, uint32_t dma_end)
{
    ald_dma_config_t *dma_cfg;
    uint32_t rx_count_total;
    uint32_t rx_count;
    uint16_t dma_remain_transfer_num;

    if (dma_end)
    {
        rx_count = dma_end - uart->last_rx_count;
        uart->last_rx_count = 0;
    }
    else
    {
        dma_cfg = &uart->huart.hdmarx.config;
        dma_remain_transfer_num = (uint16_t)((DMA->CHANNEL[dma_cfg->channel].NDT) >> 16);
        rx_count_total = (dma_cfg->size) - dma_remain_transfer_num;

        if (rx_count_total)
            rx_count = rx_count_total - uart->last_rx_count;
        else
            return;

        uart->last_rx_count = rx_count_total;
    }

    rt_hw_serial_isr(uart->serial, RT_SERIAL_EVENT_RX_DMADONE | (rx_count << 8));

}

/**
 * DMA TX complete callback
 */
static void _uart_tx_dma_cplt(ald_uart_handle_t *arg)
{
    struct es32_uart *uart;
    uart = rt_container_of(arg, struct es32_uart, huart);
    rt_hw_serial_isr(uart->serial, RT_SERIAL_EVENT_TX_DMADONE);
}
/**
 * DMA RX complete callback
 */
static void _uart_rx_dma_cplt(ald_uart_handle_t *arg)
{
    struct es32_uart *uart;
    uart = rt_container_of(arg, struct es32_uart, huart);

    if (uart->buf_select == UART_DMA_BUF_SECTIONS - 1)
    {
        arg->hdmarx.config.dst = (uint8_t *)arg->hdmarx.config.dst - arg->hdmarx.config.size * (UART_DMA_BUF_SECTIONS - 1);
        uart->buf_select = 0;
    }
    else
    {
        arg->hdmarx.config.dst = (uint8_t *)arg->hdmarx.config.dst + arg->hdmarx.config.size;
        uart->buf_select += 1;
    }

    ald_dma_config_basic(&(arg->hdmarx));
    ald_uart_dma_req_config(arg, ALD_UART_DMA_REQ_RX, ENABLE);
    _dma_recv_timeout(uart, arg->hdmarx.config.size);
}
/**
 * Setup DMA
 */
static rt_err_t es32f3x_dma_config(struct rt_serial_device *serial, rt_ubase_t flag)
{
    struct es32_uart *uart;
    struct rt_serial_rx_fifo *rx_fifo;
    extern ald_dma_call_back_t dma_cbk[];

    RT_ASSERT(serial != RT_NULL);
    uart = (struct es32_uart *)serial->parent.user_data;
    rx_fifo = (struct rt_serial_rx_fifo *)serial->serial_rx;

    if (serial->config.bufsz > 0xFFFF)
        return -RT_ERROR;

    if (RT_DEVICE_FLAG_DMA_RX == flag)
    {
        if (uart->dma_rx_channel >= UART_INVAILD_DMA_CHANNEL)
            return -ALD_ERROR;

        uart->huart.rx_cplt_cbk = _uart_rx_dma_cplt;
        //dma_cbk[uart->dma_rx_channel].cplt_tc_cbk = _uart_rx_dma_cplt;

        ALD_UART_SET_TIMEOUT_VALUE(&uart->huart, 0xFF);
        ALD_UART_RX_TIMEOUT_ENABLE(&uart->huart);
        ald_uart_interrupt_config(&uart->huart, ALD_UART_IT_RFNEMPTY, DISABLE);
        ald_uart_interrupt_config(&uart->huart, ALD_UART_IT_RXTO, ENABLE);
        uart->last_rx_count = 0;

        if (serial->config.bufsz > 0)
        {
            ald_uart_recv_by_dma(&uart->huart, rx_fifo->buffer, serial->config.bufsz / UART_DMA_BUF_SECTIONS, uart->dma_rx_channel);;
        }
    }
    else if (RT_DEVICE_FLAG_DMA_TX == flag)
    {
        if (uart->dma_tx_channel >= UART_INVAILD_DMA_CHANNEL)
            return -ALD_ERROR;

        uart->huart.tx_cplt_cbk = _uart_tx_dma_cplt;
        dma_cbk[uart->dma_tx_channel].cplt_tc_cbk = _uart_tx_dma_cplt;
    }

    uart->huart.err_code = ALD_UART_ERROR_NONE;

    csi_vic_enable_sirq(uart->irq);

    return RT_EOK;
}
#endif /* RT_SERIAL_USING_DMA */

static rt_err_t es32f3x_control(struct rt_serial_device *serial, int cmd, void *arg)
{
    struct es32_uart *uart;
#ifdef RT_SERIAL_USING_DMA
    rt_ubase_t ctrl_arg = (rt_ubase_t)arg;
#endif

    RT_ASSERT(serial != RT_NULL);

    uart = (struct es32_uart *)serial->parent.user_data;

    switch (cmd)
    {
        case RT_DEVICE_CTRL_CLR_INT:
            /* disable rx irq */
            csi_vic_disable_sirq(uart->irq);
            /* disable interrupt */
            ald_uart_interrupt_config(&uart->huart, ALD_UART_IT_RFNEMPTY, DISABLE);
#ifdef RT_SERIAL_USING_DMA

            /* disable DMA */
            if (ctrl_arg == RT_DEVICE_FLAG_DMA_RX)
            {
                ald_uart_dma_req_config(&uart->huart, ALD_UART_DMA_REQ_RX, DISABLE);
            }
            else if (ctrl_arg == RT_DEVICE_FLAG_DMA_TX)
            {
                ald_uart_dma_req_config(&uart->huart, ALD_UART_DMA_REQ_TX, DISABLE);
            }

#endif
            break;

        case RT_DEVICE_CTRL_SET_INT:
            /* enable rx irq */
            csi_vic_enable_sirq(uart->irq);
            /* enable interrupt */
            ald_uart_interrupt_config(&uart->huart, ALD_UART_IT_RFNEMPTY, ENABLE);
            break;
#ifdef RT_SERIAL_USING_DMA

        case RT_DEVICE_CTRL_CONFIG:
            /* Setup DMA */
            es32f3x_dma_config(serial, ctrl_arg);
            break;
#endif

        case RT_DEVICE_CTRL_CLOSE:
            while (ald_uart_get_status(&uart->huart, (ALD_UART_STATUS_TSBUSY)));

#ifdef RT_SERIAL_USING_DMA
            uart->huart.rx_cplt_cbk = NULL;
            uart->huart.tx_cplt_cbk = NULL;
            /* disable DMA */
            ald_uart_dma_stop(&uart->huart);
#endif
            ald_uart_reset(&uart->huart);
            break;
    }

    return RT_EOK;
}

static int es32f3x_putc(struct rt_serial_device *serial, char c)
{
    struct es32_uart *uart;
    RT_ASSERT(serial != RT_NULL);
    uart = (struct es32_uart *)serial->parent.user_data;

    while (ald_uart_get_status(&uart->huart, ALD_UART_STATUS_TFEMPTY) == RESET)
        ;

    WRITE_REG(uart->huart.perh->TXBUF, c);

    return 1;
}

static int es32f3x_getc(struct rt_serial_device *serial)
{
    int ch = -1;
    struct es32_uart *uart;

    RT_ASSERT(serial != RT_NULL);
    uart = (struct es32_uart *)serial->parent.user_data;

    if (ald_uart_get_status(&uart->huart, ALD_UART_STATUS_RFNEMPTY))
    {
        ch = (uint8_t)(uart->huart.perh->RXBUF & 0xFF);
    }

    return ch;
}

#ifdef RT_SERIAL_USING_DMA

/**
 * DMA transmit
 */
static rt_ssize_t es32f3x_dma_transmit(struct rt_serial_device *serial, rt_uint8_t *buf, rt_size_t size, int direction)
{
    struct es32_uart *uart;

    RT_ASSERT(serial != RT_NULL);
    uart = (struct es32_uart *)serial->parent.user_data;

    if (direction == RT_SERIAL_DMA_TX)
    {
        if (uart->dma_tx_channel >= UART_INVAILD_DMA_CHANNEL)
            return 0;

        if (ALD_OK == ald_uart_send_by_dma(&uart->huart, buf, size, uart->dma_tx_channel))
        {
            return size;
        }
        else
        {
            return 0;
        }
    }
    else if (direction == RT_SERIAL_DMA_RX)
    {

        if (uart->dma_rx_channel >= UART_INVAILD_DMA_CHANNEL)
            return 0;

        if (ALD_OK == ald_uart_recv_by_dma(&uart->huart, buf, size, uart->dma_rx_channel))
        {
            return size;
        }
        else
        {
            return 0;
        }

    }

    return 0;
}
#endif
static const struct rt_uart_ops es32f3x_uart_ops =
{
    es32f3x_configure,
    es32f3x_control,
    es32f3x_putc,
    es32f3x_getc,
#ifdef RT_SERIAL_USING_DMA
    es32f3x_dma_transmit
#else
    NULL
#endif
};

int rt_hw_uart_init(void)
{
    struct es32_uart *uart;

#ifdef BSP_USING_EUART0
    uart = &uart0;
    serial0.ops = &es32f3x_uart_ops;
    serial0.config = (struct serial_configure)ES_EUART0_CONFIG;

    /* register EUART0 device */
    rt_hw_serial_register(&serial0, ES_DEVICE_NAME_EUART0,
                          RT_DEVICE_FLAG_RDWR | RT_DEVICE_FLAG_INT_RX |
                          EUART0_DMATX_FLAG | EUART0_DMARX_FLAG,
                          uart);
#endif /* BSP_USING_EUART0 */

#ifdef BSP_USING_EUART1
    uart = &uart1;
    serial1.ops = &es32f3x_uart_ops;
    serial1.config = (struct serial_configure)ES_EUART1_CONFIG;

    /* register EUART1 device */
    rt_hw_serial_register(&serial1, ES_DEVICE_NAME_EUART1,
                          RT_DEVICE_FLAG_RDWR | RT_DEVICE_FLAG_INT_RX |
                          EUART1_DMATX_FLAG | EUART1_DMARX_FLAG,
                          uart);
#endif /* BSP_USING_EUART1 */

#ifdef BSP_USING_CUART0
    uart = &uart2;
    serial2.ops = &es32f3x_uart_ops;
    serial2.config = (struct serial_configure)ES_CUART0_CONFIG;

    /* register CUART0 device */
    rt_hw_serial_register(&serial2, ES_DEVICE_NAME_CUART0,
                          RT_DEVICE_FLAG_RDWR | RT_DEVICE_FLAG_INT_RX |
                          CUART0_DMATX_FLAG | CUART0_DMARX_FLAG,
                          uart);
#endif /* BSP_USING_CUART0 */

#ifdef BSP_USING_CUART1
    uart = &uart3;
    serial3.ops = &es32f3x_uart_ops;
    serial3.config = (struct serial_configure)ES_CUART1_CONFIG;

    /* register CUART1 device */
    rt_hw_serial_register(&serial3, ES_DEVICE_NAME_CUART1,
                          RT_DEVICE_FLAG_RDWR | RT_DEVICE_FLAG_INT_RX |
                          CUART1_DMATX_FLAG | CUART1_DMARX_FLAG,
                          uart);
#endif /* BSP_USING_CUART1 */

#ifdef BSP_USING_CUART2
    uart = &uart4;
    serial4.ops = &es32f3x_uart_ops;
    serial4.config = (struct serial_configure)ES_CUART2_CONFIG;

    /* register CUART2 device */
    rt_hw_serial_register(&serial4, ES_DEVICE_NAME_CUART2,
                          RT_DEVICE_FLAG_RDWR | RT_DEVICE_FLAG_INT_RX |
                          CUART2_DMATX_FLAG | CUART2_DMARX_FLAG,
                          uart);
#endif /* BSP_USING_CUART2 */

    return 0;
}
INIT_BOARD_EXPORT(rt_hw_uart_init);

#endif
