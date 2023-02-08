/*
 * Copyright (C) 2018 Shanghai Eastsoft Microelectronics Co., Ltd.
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
 * 2020-01-14     wangyq        the first version
 * 2021-04-20     liuhy         the second version
 * 2021-09-17     shiwa         add uart dma
 */

#include <rthw.h>
#include <rtthread.h>
#include <rtdevice.h>
#include "board.h"
#include "es_conf_info_uart.h"
#include "es_conf_info_dma.h"
#ifdef RT_USING_SERIAL

#define UART_DMA_BUF_SECTIONS 4

/*
 * To use UART DMA,
 * 1. select 'DMA->DMA0'
 * 2. select 'UART->UARTx->DMATX(or DMARX)'
 * 3. add RT_DEVICE_FLAG_DMA_TX(or RT_DEVICE_FLAG_DMA_RX) flag when open serial device
 */
#ifdef BSP_UART0_TX_USING_DMA
#define UART0_DMATX_CHANNEL ES_UART0_DMATX_CHANNEL
#define UART0_DMATX_FLAG RT_DEVICE_FLAG_DMA_TX
#else
#define UART0_DMATX_CHANNEL ES_DMA_INVAILD_CHANNEL
#define UART0_DMATX_FLAG 0
#endif

#ifdef BSP_UART0_RX_USING_DMA
#define UART0_DMARX_CHANNEL ES_UART0_DMARX_CHANNEL
#define UART0_DMARX_FLAG RT_DEVICE_FLAG_DMA_RX
#else
#define UART0_DMARX_CHANNEL ES_DMA_INVAILD_CHANNEL
#define UART0_DMARX_FLAG 0
#endif

#ifdef BSP_UART1_TX_USING_DMA
#define UART1_DMATX_CHANNEL ES_UART1_DMATX_CHANNEL
#define UART1_DMATX_FLAG RT_DEVICE_FLAG_DMA_TX
#else
#define UART1_DMATX_CHANNEL ES_DMA_INVAILD_CHANNEL
#define UART1_DMATX_FLAG 0
#endif

#ifdef BSP_UART1_RX_USING_DMA
#define UART1_DMARX_CHANNEL ES_UART1_DMARX_CHANNEL
#define UART1_DMARX_FLAG RT_DEVICE_FLAG_DMA_RX
#else
#define UART1_DMARX_CHANNEL ES_DMA_INVAILD_CHANNEL
#define UART1_DMARX_FLAG 0
#endif

#ifdef BSP_UART2_TX_USING_DMA
#define UART2_DMATX_CHANNEL ES_UART2_DMATX_CHANNEL
#define UART2_DMATX_FLAG RT_DEVICE_FLAG_DMA_TX
#else
#define UART2_DMATX_CHANNEL ES_DMA_INVAILD_CHANNEL
#define UART2_DMATX_FLAG 0
#endif

#ifdef BSP_UART2_RX_USING_DMA
#define UART2_DMARX_CHANNEL ES_UART2_DMARX_CHANNEL
#define UART2_DMARX_FLAG RT_DEVICE_FLAG_DMA_RX
#else
#define UART2_DMARX_CHANNEL ES_DMA_INVAILD_CHANNEL
#define UART2_DMARX_FLAG 0
#endif

#ifdef BSP_UART3_TX_USING_DMA
#define UART3_DMATX_CHANNEL ES_UART3_DMATX_CHANNEL
#define UART3_DMATX_FLAG RT_DEVICE_FLAG_DMA_TX
#else
#define UART3_DMATX_CHANNEL ES_DMA_INVAILD_CHANNEL
#define UART3_DMATX_FLAG 0
#endif

#ifdef BSP_UART3_RX_USING_DMA
#define UART3_DMARX_CHANNEL ES_UART3_DMARX_CHANNEL
#define UART3_DMARX_FLAG RT_DEVICE_FLAG_DMA_RX
#else
#define UART3_DMARX_CHANNEL ES_DMA_INVAILD_CHANNEL
#define UART3_DMARX_FLAG 0
#endif

#ifdef BSP_UART4_TX_USING_DMA
#define UART4_DMATX_CHANNEL ES_UART4_DMATX_CHANNEL
#define UART4_DMATX_FLAG RT_DEVICE_FLAG_DMA_TX
#else
#define UART4_DMATX_CHANNEL ES_DMA_INVAILD_CHANNEL
#define UART4_DMATX_FLAG 0
#endif

#ifdef BSP_UART4_RX_USING_DMA
#define UART4_DMARX_CHANNEL ES_UART4_DMARX_CHANNEL
#define UART4_DMARX_FLAG RT_DEVICE_FLAG_DMA_RX
#else
#define UART4_DMARX_CHANNEL ES_DMA_INVAILD_CHANNEL
#define UART4_DMARX_FLAG 0
#endif

#ifdef BSP_UART5_TX_USING_DMA
#define UART5_DMATX_CHANNEL ES_UART5_DMATX_CHANNEL
#define UART5_DMATX_FLAG RT_DEVICE_FLAG_DMA_TX
#else
#define UART5_DMATX_CHANNEL ES_DMA_INVAILD_CHANNEL
#define UART5_DMATX_FLAG 0
#endif

#ifdef BSP_UART5_RX_USING_DMA
#define UART5_DMARX_CHANNEL ES_UART5_DMARX_CHANNEL
#define UART5_DMARX_FLAG RT_DEVICE_FLAG_DMA_RX
#else
#define UART5_DMARX_CHANNEL ES_DMA_INVAILD_CHANNEL
#define UART5_DMARX_FLAG 0
#endif

#define UART_INVAILD_DMA_CHANNEL (ES_DMA_INVAILD_CHANNEL)

/* es32 uart driver */
struct es32_uart
{
    uart_handle_t huart;
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
    if ((ald_uart_get_mask_flag_status(&uart->huart, UART_IF_RFTH)) != RESET)
    {
        ald_uart_clear_flag_status(&uart->huart, UART_IF_RFTH);
        rt_hw_serial_isr(uart->serial, RT_SERIAL_EVENT_RX_IND);
    }
    #ifdef RT_SERIAL_USING_DMA
    if ((ald_uart_get_mask_flag_status(&uart->huart, UART_IF_RXTO)) != RESET)
    {
        ald_uart_clear_flag_status(&uart->huart, UART_IF_RXTO);
        _dma_recv_timeout(uart, 0);
    }

    if ((ald_uart_get_mask_flag_status(&uart->huart, UART_IF_TBC)) != RESET)
    {
        uint32_t cnt = 1000;
        ald_uart_clear_flag_status(&uart->huart, UART_IF_TBC);
        ald_uart_interrupt_config(&uart->huart, UART_IT_TBC, DISABLE);
        CLEAR_BIT(uart->huart.state, UART_STATE_TX_MASK);

        while ((uart->huart.perh->STAT & UART_STATUS_TSBUSY) && (cnt--));

        ald_uart_clear_flag_status(&uart->huart, UART_IF_TBC);

        if (uart->huart.tx_cplt_cbk)
            uart->huart.tx_cplt_cbk(&uart->huart);
    }
    #endif /* RT_SERIAL_USING_DMA */
}


#ifdef BSP_USING_UART0

struct rt_serial_device serial0;
/* UART0 device driver structure */
struct es32_uart uart0 =
{
    {UART0},
    &serial0,
    UART0_IRQn,
#ifdef RT_SERIAL_USING_DMA
    UART0_DMATX_CHANNEL,
    UART0_DMARX_CHANNEL
#endif /* RT_SERIAL_USING_DMA */
};
void UART0_Handler(void)
{
    /* enter interrupt */
    rt_interrupt_enter();
    uart_int_handler(&uart0);
    /* leave interrupt */
    rt_interrupt_leave();
}
#endif /* BSP_USING_UART0 */

#ifdef BSP_USING_UART1

struct rt_serial_device serial1;
/* UART1 device driver structure */
struct es32_uart uart1 =
{
    {UART1},
    &serial1,
    UART1_IRQn,
#ifdef RT_SERIAL_USING_DMA
    UART1_DMATX_CHANNEL,
    UART1_DMARX_CHANNEL
#endif /* RT_SERIAL_USING_DMA */
};

void UART1_Handler(void)
{
    /* enter interrupt */
    rt_interrupt_enter();
    uart_int_handler(&uart1);
    /* leave interrupt */
    rt_interrupt_leave();
}
#endif /* BSP_USING_UART1 */

#ifdef BSP_USING_UART2

struct rt_serial_device serial2;
/* UART2 device driver structure */
struct es32_uart uart2 =
{
    {UART2},
    &serial2,
    UART2_IRQn,
#ifdef RT_SERIAL_USING_DMA
    UART2_DMATX_CHANNEL,
    UART2_DMARX_CHANNEL
#endif /* RT_SERIAL_USING_DMA */
};

void UART2_Handler(void)
{
    /* enter interrupt */
    rt_interrupt_enter();
    uart_int_handler(&uart2);
    /* leave interrupt */
    rt_interrupt_leave();
}
#endif /* BSP_USING_UART2 */

#ifdef BSP_USING_UART3

struct rt_serial_device serial3;
/* UART3 device driver structure */
struct es32_uart uart3 =
{
    {UART3},
    &serial3,
    UART3_IRQn,
#ifdef RT_SERIAL_USING_DMA
    UART3_DMATX_CHANNEL,
    UART3_DMARX_CHANNEL
#endif /* RT_SERIAL_USING_DMA */
};

void UART3_Handler(void)
{
    /* enter interrupt */
    rt_interrupt_enter();
    uart_int_handler(&uart3);
    /* leave interrupt */
    rt_interrupt_leave();
}
#endif /* BSP_USING_UART3 */

#ifdef BSP_USING_UART4

struct rt_serial_device serial4;
/* UART4 device driver structure */
struct es32_uart uart4 =
{
    {UART4},
    &serial4,
    UART4_IRQn,
#ifdef RT_SERIAL_USING_DMA
    UART4_DMATX_CHANNEL,
    UART4_DMARX_CHANNEL
#endif /* RT_SERIAL_USING_DMA */
};

void UART4_Handler(void)
{
    /* enter interrupt */
    rt_interrupt_enter();
    uart_int_handler(&uart4);
    /* leave interrupt */
    rt_interrupt_leave();
}
#endif /* BSP_USING_UART4 */

#ifdef BSP_USING_UART5

struct rt_serial_device serial5;
/* UART5 device driver structure */
struct es32_uart uart5 =
{
    {UART5},
    &serial5,
    UART5_IRQn,
#ifdef RT_SERIAL_USING_DMA
    UART5_DMATX_CHANNEL,
    UART5_DMARX_CHANNEL
#endif /* RT_SERIAL_USING_DMA */
};

void UART5_Handler(void)
{
    /* enter interrupt */
    rt_interrupt_enter();
    uart_int_handler(&uart5);
    /* leave interrupt */
    rt_interrupt_leave();
}
#endif /* BSP_USING_UART5 */

static rt_err_t es32f3x_configure(struct rt_serial_device *serial, struct serial_configure *cfg)
{
    gpio_init_t gpio_initstructure;
    struct es32_uart *uart;
    RT_ASSERT(serial != RT_NULL);
    RT_ASSERT(cfg != RT_NULL);
    uart = (struct es32_uart *)serial->parent.user_data;

    /* Initialize tx pin */
    gpio_initstructure.mode = GPIO_MODE_OUTPUT;
    gpio_initstructure.odos = GPIO_PUSH_PULL;
    gpio_initstructure.pupd = GPIO_PUSH_UP;
    gpio_initstructure.podrv = GPIO_OUT_DRIVE_6;
    gpio_initstructure.nodrv = GPIO_OUT_DRIVE_6;
    gpio_initstructure.flt  = GPIO_FILTER_DISABLE;
    gpio_initstructure.type = GPIO_TYPE_TTL;

#ifdef BSP_USING_UART0

    if (uart == (&uart0))
    {
#if  defined(ES_UART0_TX_GPIO_FUNC)&&defined(ES_UART0_TX_GPIO_PORT)&&defined(ES_UART0_TX_GPIO_PIN)
        gpio_initstructure.func = ES_UART0_TX_GPIO_FUNC;
        ald_gpio_init(ES_UART0_TX_GPIO_PORT, ES_UART0_TX_GPIO_PIN, &gpio_initstructure);
#endif

#if  defined(ES_UART0_RX_GPIO_FUNC)&&defined(ES_UART0_RX_GPIO_PORT)&&defined(ES_UART0_RX_GPIO_PIN)
        /* Initialize rx pin ,the same as txpin except mode */
        gpio_initstructure.mode = GPIO_MODE_INPUT;
        gpio_initstructure.func = ES_UART0_RX_GPIO_FUNC;
        ald_gpio_init(ES_UART0_RX_GPIO_PORT, ES_UART0_RX_GPIO_PIN, &gpio_initstructure);
#endif
        ald_cmu_perh_clock_config(CMU_PERH_UART0, ENABLE);
    }

#endif /* uart0 gpio init */

#ifdef BSP_USING_UART1

    if (uart == (&uart1))
    {
#if  defined(ES_UART1_TX_GPIO_FUNC)&&defined(ES_UART1_TX_GPIO_PORT)&&defined(ES_UART1_TX_GPIO_PIN)
        gpio_initstructure.func = ES_UART1_TX_GPIO_FUNC;
        ald_gpio_init(ES_UART1_TX_GPIO_PORT, ES_UART1_TX_GPIO_PIN, &gpio_initstructure);
#endif

#if  defined(ES_UART1_RX_GPIO_FUNC)&&defined(ES_UART1_RX_GPIO_PORT)&&defined(ES_UART1_RX_GPIO_PIN)
        /* Initialize rx pin ,the same as txpin except mode */
        gpio_initstructure.mode = GPIO_MODE_INPUT;
        gpio_initstructure.func = ES_UART1_RX_GPIO_FUNC;
        ald_gpio_init(ES_UART1_RX_GPIO_PORT, ES_UART1_RX_GPIO_PIN, &gpio_initstructure);
#endif

        ald_cmu_perh_clock_config(CMU_PERH_UART1, ENABLE);
    }

#endif /* uart1 gpio init */

#ifdef BSP_USING_UART2

    if (uart == (&uart2))
    {
#if  defined(ES_UART2_TX_GPIO_FUNC)&&defined(ES_UART2_TX_GPIO_PORT)&&defined(ES_UART2_TX_GPIO_PIN)
        gpio_initstructure.func = ES_UART2_TX_GPIO_FUNC;
        ald_gpio_init(ES_UART2_TX_GPIO_PORT, ES_UART2_TX_GPIO_PIN, &gpio_initstructure);
#endif

#if  defined(ES_UART2_RX_GPIO_FUNC)&&defined(ES_UART2_RX_GPIO_PORT)&&defined(ES_UART2_RX_GPIO_PIN)
        /* Initialize rx pin ,the same as txpin except mode */
        gpio_initstructure.mode = GPIO_MODE_INPUT;
        gpio_initstructure.func = ES_UART2_RX_GPIO_FUNC;
        ald_gpio_init(ES_UART2_RX_GPIO_PORT, ES_UART2_RX_GPIO_PIN, &gpio_initstructure);
#endif

        ald_cmu_perh_clock_config(CMU_PERH_UART2, ENABLE);
    }

#endif /* uart2 gpio init */

#ifdef BSP_USING_UART3

    if (uart == (&uart3))
    {
#if  defined(ES_UART3_TX_GPIO_FUNC)&&defined(ES_UART3_TX_GPIO_PORT)&&defined(ES_UART3_TX_GPIO_PIN)
        gpio_initstructure.func = ES_UART3_TX_GPIO_FUNC;
        ald_gpio_init(ES_UART3_TX_GPIO_PORT, ES_UART3_TX_GPIO_PIN, &gpio_initstructure);
#endif

#if  defined(ES_UART3_RX_GPIO_FUNC)&&defined(ES_UART3_RX_GPIO_PORT)&&defined(ES_UART3_RX_GPIO_PIN)
        /* Initialize rx pin ,the same as txpin except mode */
        gpio_initstructure.mode = GPIO_MODE_INPUT;
        gpio_initstructure.func = ES_UART3_RX_GPIO_FUNC;
        ald_gpio_init(ES_UART3_RX_GPIO_PORT, ES_UART3_RX_GPIO_PIN, &gpio_initstructure);
#endif

        ald_cmu_perh_clock_config(CMU_PERH_UART3, ENABLE);
    }

#endif /* uart3 gpio init */

#ifdef BSP_USING_UART4

    if (uart == (&uart4))
    {
#if  defined(ES_UART4_TX_GPIO_FUNC)&&defined(ES_UART4_TX_GPIO_PORT)&&defined(ES_UART4_TX_GPIO_PIN)
        gpio_initstructure.func = ES_UART4_TX_GPIO_FUNC;
        ald_gpio_init(ES_UART4_TX_GPIO_PORT, ES_UART4_TX_GPIO_PIN, &gpio_initstructure);
#endif

#if  defined(ES_UART4_RX_GPIO_FUNC)&&defined(ES_UART4_RX_GPIO_PORT)&&defined(ES_UART4_RX_GPIO_PIN)
        /* Initialize rx pin ,the same as txpin except mode */
        gpio_initstructure.mode = GPIO_MODE_INPUT;
        gpio_initstructure.func = ES_UART4_RX_GPIO_FUNC;
        ald_gpio_init(ES_UART4_RX_GPIO_PORT, ES_UART4_RX_GPIO_PIN, &gpio_initstructure);
#endif

        ald_cmu_perh_clock_config(CMU_PERH_UART4, ENABLE);
    }

#endif /* uart4 gpio init */

#ifdef BSP_USING_UART5

    if (uart == (&uart5))
    {
#if  defined(ES_UART5_TX_GPIO_FUNC)&&defined(ES_UART5_TX_GPIO_PORT)&&defined(ES_UART5_TX_GPIO_PIN)
        gpio_initstructure.func = ES_UART5_TX_GPIO_FUNC;
        ald_gpio_init(ES_UART5_TX_GPIO_PORT, ES_UART5_TX_GPIO_PIN, &gpio_initstructure);
#endif

#if  defined(ES_UART5_RX_GPIO_FUNC)&&defined(ES_UART5_RX_GPIO_PORT)&&defined(ES_UART5_RX_GPIO_PIN)
        /* Initialize rx pin ,the same as txpin except mode */
        gpio_initstructure.mode = GPIO_MODE_INPUT;
        gpio_initstructure.func = ES_UART5_RX_GPIO_FUNC;
        ald_gpio_init(ES_UART5_RX_GPIO_PORT, ES_UART5_RX_GPIO_PIN, &gpio_initstructure);
#endif

        ald_cmu_perh_clock_config(CMU_PERH_UART5, ENABLE);
    }

#endif /* uart5 gpio init */

    ald_uart_tx_fifo_config(&uart->huart, UART_TXFIFO_EMPTY);
    ald_uart_rx_fifo_config(&uart->huart, UART_RXFIFO_1BYTE);

    uart->huart.init.mode        = UART_MODE_UART;
    uart->huart.init.baud        = cfg->baud_rate;
    uart->huart.init.word_length = (uart_word_length_t)(8 - cfg->data_bits);
    uart->huart.init.parity = (uart_parity_t)(cfg->parity == PARITY_EVEN ? UART_PARITY_EVEN : cfg->parity);
    uart->huart.init.fctl        = UART_HW_FLOW_CTL_DISABLE;
    uart->huart.init.stop_bits        = UART_STOP_BITS_1;
    ald_uart_init(&uart->huart);

    if (cfg->bit_order == BIT_ORDER_MSB)
    {
        UART_MSB_FIRST_ENABLE(&uart->huart);
    }
    else
    {
        UART_MSB_FIRST_DISABLE(&uart->huart);
    }

    if (cfg->invert == NRZ_INVERTED)
    {
        UART_DATA_INV_ENABLE(&uart->huart);
    }
    else
    {
        UART_DATA_INV_DISABLE(&uart->huart);
    }

    return RT_EOK;
}



#ifdef RT_SERIAL_USING_DMA

static void _dma_recv_timeout(struct es32_uart *uart, uint32_t dma_end)
{
    DMA_TypeDef *DMAx;
    dma_config_t *dma_cfg;
    dma_descriptor_t *descr;
    uint32_t rx_count_total;
    uint32_t rx_count;


    if (dma_end)
    {
        rx_count = dma_end - uart->last_rx_count;
        uart->last_rx_count = 0;
    }
    else
    {
        DMAx = uart->huart.hdmarx.perh;
        dma_cfg = &uart->huart.hdmarx.config;
        descr = (dma_descriptor_t *)(DMAx->CTRLBASE) + dma_cfg->channel;

        rx_count_total = (dma_cfg->size) - (uint32_t)(descr->ctrl.n_minus_1) - 1;

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
static void _uart_tx_dma_cplt(uart_handle_t *arg)
{
    struct es32_uart *uart;
    uart = rt_container_of(arg, struct es32_uart, huart);
    rt_hw_serial_isr(uart->serial, RT_SERIAL_EVENT_TX_DMADONE);
}
/**
 * DMA RX complete callback
 */
static void _uart_rx_dma_cplt(uart_handle_t *arg)
{
    struct es32_uart *uart;
    uint8_t *dma_dst;
    uart = rt_container_of(arg, struct es32_uart, huart);

    if (uart->buf_select == UART_DMA_BUF_SECTIONS - 1)
    {
        dma_dst = (uint8_t *)uart->huart.hdmarx.config.dst - arg->hdmarx.config.size * (UART_DMA_BUF_SECTIONS - 1);
        uart->buf_select = 0;
    }
    else
    {
        dma_dst = (uint8_t *)arg->hdmarx.config.dst + arg->hdmarx.config.size;
        uart->buf_select += 1;
    }

    ald_uart_recv_by_dma(arg, dma_dst, arg->hdmarx.config.size, arg->hdmarx.config.channel);
    _dma_recv_timeout(uart, arg->hdmarx.config.size);
}
/**
 * Setup DMA
 */
static rt_err_t es32f3x_dma_config(struct rt_serial_device *serial, rt_ubase_t flag)
{
    struct es32_uart *uart;
    struct rt_serial_rx_fifo *rx_fifo;

    RT_ASSERT(serial != RT_NULL);
    uart = (struct es32_uart *)serial->parent.user_data;
    rx_fifo = (struct rt_serial_rx_fifo *)serial->serial_rx;

    if (serial->config.bufsz > 1024)
        return -RT_ERROR;

    if (RT_DEVICE_FLAG_DMA_RX == flag)
    {
        if (uart->dma_rx_channel >= UART_INVAILD_DMA_CHANNEL)
            return -ERROR;

        uart->huart.rx_cplt_cbk = _uart_rx_dma_cplt;
        UART_SET_TIMEOUT_VALUE(&uart->huart, 0xFF);
        UART_RX_TIMEOUT_ENABLE(&uart->huart);
        ald_uart_interrupt_config(&uart->huart, UART_IT_RXTO, ENABLE);
        uart->last_rx_count = 0;

        if (serial->config.bufsz > 0)
        {
            ald_uart_recv_by_dma(&uart->huart, rx_fifo->buffer, serial->config.bufsz / UART_DMA_BUF_SECTIONS, uart->dma_rx_channel);;
        }
    }
    else if (RT_DEVICE_FLAG_DMA_TX == flag)
    {
        if (uart->dma_tx_channel >= UART_INVAILD_DMA_CHANNEL)
            return -ERROR;

        uart->huart.tx_cplt_cbk = _uart_tx_dma_cplt;
    }

    uart->huart.err_code = UART_ERROR_NONE;
    //NVIC_SetPriority(DMA_IRQn,0);
    NVIC_EnableIRQ(uart->irq);
    ald_cmu_perh_clock_config(CMU_PERH_DMA, ENABLE);
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
            NVIC_DisableIRQ(uart->irq);
            /* disable interrupt */
            ald_uart_interrupt_config(&uart->huart, UART_IT_RFTH, DISABLE);
#ifdef RT_SERIAL_USING_DMA

            /* disable DMA */
            if (ctrl_arg == RT_DEVICE_FLAG_DMA_RX)
            {
                ald_uart_dma_req_config(&uart->huart, UART_DMA_REQ_RX, DISABLE);
            }
            else if (ctrl_arg == RT_DEVICE_FLAG_DMA_TX)
            {
                ald_uart_dma_req_config(&uart->huart, UART_DMA_REQ_TX, DISABLE);
            }

#endif
            break;

        case RT_DEVICE_CTRL_SET_INT:
            /* enable rx irq */
            NVIC_EnableIRQ(uart->irq);
            /* enable interrupt */
            ald_uart_interrupt_config(&uart->huart, UART_IT_RFTH, ENABLE);
            break;
#ifdef RT_SERIAL_USING_DMA

        case RT_DEVICE_CTRL_CONFIG:
            /* Setup DMA */
            es32f3x_dma_config(serial, ctrl_arg);
            break;
#endif

        case RT_DEVICE_CTRL_CLOSE:
            while (ald_uart_get_status(&uart->huart, (UART_STATUS_TSBUSY)));

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

    while (ald_uart_get_status(&uart->huart, UART_STATUS_TFEMPTY) == RESET)
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

    if (ald_uart_get_status(&uart->huart, UART_STATUS_RFTH))
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

        if (OK == ald_uart_send_by_dma(&uart->huart, buf, size, uart->dma_tx_channel))
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

        if (OK == ald_uart_recv_by_dma(&uart->huart, buf, size, uart->dma_rx_channel))
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

#ifdef BSP_USING_UART0
    uart = &uart0;
    serial0.ops = &es32f3x_uart_ops;
    serial0.config = (struct serial_configure)ES_UART0_CONFIG;

    /* register UART0 device */
    rt_hw_serial_register(&serial0, ES_DEVICE_NAME_UART0,
                          RT_DEVICE_FLAG_RDWR | RT_DEVICE_FLAG_INT_RX |
                          UART0_DMATX_FLAG | UART0_DMARX_FLAG,
                          uart);
#endif /* BSP_USING_UART0 */

#ifdef BSP_USING_UART1
    uart = &uart1;
    serial1.ops = &es32f3x_uart_ops;
    serial1.config = (struct serial_configure)ES_UART1_CONFIG;

    /* register UART1 device */
    rt_hw_serial_register(&serial1, ES_DEVICE_NAME_UART1,
                          RT_DEVICE_FLAG_RDWR | RT_DEVICE_FLAG_INT_RX |
                          UART1_DMATX_FLAG | UART1_DMARX_FLAG,
                          uart);
#endif /* BSP_USING_UART1 */

#ifdef BSP_USING_UART2
    uart = &uart2;
    serial2.ops = &es32f3x_uart_ops;
    serial2.config = (struct serial_configure)ES_UART2_CONFIG;

    /* register UART2 device */
    rt_hw_serial_register(&serial2, ES_DEVICE_NAME_UART2,
                          RT_DEVICE_FLAG_RDWR | RT_DEVICE_FLAG_INT_RX |
                          UART2_DMATX_FLAG | UART2_DMARX_FLAG,
                          uart);
#endif /* BSP_USING_UART2 */

#ifdef BSP_USING_UART3
    uart = &uart3;
    serial3.ops = &es32f3x_uart_ops;
    serial3.config = (struct serial_configure)ES_UART3_CONFIG;

    /* register UART3 device */
    rt_hw_serial_register(&serial3, ES_DEVICE_NAME_UART3,
                          RT_DEVICE_FLAG_RDWR | RT_DEVICE_FLAG_INT_RX |
                          UART3_DMATX_FLAG | UART3_DMARX_FLAG,
                          uart);
#endif /* BSP_USING_UART3 */

#ifdef BSP_USING_UART4
    uart = &uart4;
    serial4.ops = &es32f3x_uart_ops;
    serial4.config = (struct serial_configure)ES_UART4_CONFIG;

    /* register UART4 device */
    rt_hw_serial_register(&serial4, ES_DEVICE_NAME_UART4,
                          RT_DEVICE_FLAG_RDWR | RT_DEVICE_FLAG_INT_RX |
                          UART4_DMATX_FLAG | UART4_DMARX_FLAG,
                          uart);
#endif /* BSP_USING_UART4 */

#ifdef BSP_USING_UART5
    uart = &uart5;
    serial5.ops = &es32f3x_uart_ops;
    serial5.config = (struct serial_configure)ES_UART5_CONFIG;

    /* register UART5 device */
    rt_hw_serial_register(&serial5, ES_DEVICE_NAME_UART5,
                          RT_DEVICE_FLAG_RDWR | RT_DEVICE_FLAG_INT_RX |
                          UART5_DMATX_FLAG | UART5_DMARX_FLAG,
                          uart);
#endif /* BSP_USING_UART5 */

    return 0;
}
INIT_BOARD_EXPORT(rt_hw_uart_init);

#endif
