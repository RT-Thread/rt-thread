/*
 * Copyright (c) 2006-2022, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2021-08-23     AisinoChip   the first version
 */

#include <rthw.h>
#include <rtthread.h>
#include <rtdevice.h>
#include "rtconfig.h"
#include "board.h"
#include "uart_config.h"

#ifdef RT_USING_SERIAL

#ifdef RT_SERIAL_USING_DMA
struct dma_config
{
    DMA_Channel_TypeDef *Instance;
    rt_uint32_t         dma_rcc;
    IRQn_Type           dma_irq;

    rt_uint32_t         channel;
    rt_uint32_t         request;
};
#endif

#ifdef RT_SERIAL_USING_DMA
    static void DMA_Configuration(struct rt_serial_device *serial, rt_uint32_t flag);
#endif /* RT_SERIAL_USING_DMA */

struct acm32_uart_config
{
    const char          *name;
    UART_TypeDef        *Instance;
    IRQn_Type           irq_type;
    enum_Enable_ID_t    enable_id;

#ifdef RT_SERIAL_USING_DMA
    struct dma_config   *dma_rx;
    struct dma_config   *dma_tx;
#endif

    enum_GPIOx_t        tx_port;
    enum_GPIOx_t        rx_port;
    rt_uint32_t         tx_pin;
    rt_uint32_t         rx_pin;
};

struct acm32_uart
{
    UART_HandleTypeDef          handle;
    struct acm32_uart_config    *config;
#ifdef RT_SERIAL_USING_DMA
    struct
    {
        DMA_HandleTypeDef       handle;
        rt_size_t               last_index;
    } dma_rx;

    struct
    {
        DMA_HandleTypeDef       handle;
    } dma_tx;
#endif

    rt_uint16_t                 uart_dma_flag;
    struct rt_serial_device     serial;
};

static rt_err_t uart_rx_indicate_cb(rt_device_t dev, rt_size_t size)
{
    return RT_EOK;
}

static rt_err_t _uart_configure(struct rt_serial_device *serial, struct serial_configure *cfg)
{
    struct acm32_uart *uart;

    RT_ASSERT(serial != RT_NULL);
    RT_ASSERT(cfg != RT_NULL);

    uart = rt_container_of(serial, struct acm32_uart, serial);

    uart->handle.Instance = uart->config->Instance;

    uart->handle.Init.BaudRate = cfg->baud_rate;
    if (cfg->data_bits == DATA_BITS_8)
    {
        uart->handle.Init.WordLength = UART_WORDLENGTH_8B;
    }
    else     /* not support */
    {
        return -RT_EINVAL;
    }

    if (cfg->stop_bits == STOP_BITS_1)
    {
        uart->handle.Init.StopBits = UART_STOPBITS_1;
    }
    else if (cfg->stop_bits == STOP_BITS_2)
    {
        uart->handle.Init.StopBits = UART_STOPBITS_2;
    }
    else     /* not support */
    {
        return -RT_EINVAL;
    }

    if (cfg->parity == PARITY_NONE)
    {
        uart->handle.Init.Parity = UART_PARITY_NONE;
    }
    else if (cfg->parity == PARITY_ODD)
    {
        uart->handle.Init.Parity = UART_PARITY_ODD;
    }
    else if (cfg->parity == PARITY_EVEN)
    {
        uart->handle.Init.Parity = UART_PARITY_EVEN;
    }
    else     /* not support */
    {
        return -RT_EINVAL;
    }

    uart->handle.Init.Mode       = UART_MODE_TX_RX;
    uart->handle.Init.HwFlowCtl  = UART_HWCONTROL_NONE;

    HAL_UART_Init(&uart->handle);

    uart->handle.Instance->LCRH &= ~UART_LCRH_FEN;
    return RT_EOK;
}

static rt_err_t _uart_control(struct rt_serial_device *serial, int cmd, void *arg)
{
    struct acm32_uart *uart;
#ifdef RT_SERIAL_USING_DMA
    rt_ubase_t ctrl_arg = (rt_ubase_t)arg;
#endif

    RT_ASSERT(serial != RT_NULL);

    uart = rt_container_of(serial, struct acm32_uart, serial);

    switch (cmd)
    {
    /* disable interrupt */
    case RT_DEVICE_CTRL_CLR_INT:
        NVIC_DisableIRQ(uart->config->irq_type);
        /* Disable RX interrupt */
        uart->handle.Instance->IE &= ~UART_IE_RXI;
        break;
    /* enable interrupt */
    case RT_DEVICE_CTRL_SET_INT:
        NVIC_EnableIRQ(uart->config->irq_type);
        /* Enable RX interrupt */
        uart->handle.Instance->IE |= UART_IE_RXI;
        break;
#ifdef RT_SERIAL_USING_DMA
    /* UART config */
    case RT_DEVICE_CTRL_CONFIG :
        DMA_Configuration(serial, (rt_uint32_t)ctrl_arg);
        rt_device_set_rx_indicate((rt_device_t)serial, uart_rx_indicate_cb);
        break;
#endif /* RT_SERIAL_USING_DMA */
    }
    return RT_EOK;
}

static int _uart_putc(struct rt_serial_device *serial, char c)
{
    struct acm32_uart *uart;

    RT_ASSERT(serial != RT_NULL);

    uart = rt_container_of(serial, struct acm32_uart, serial);

    while (uart->handle.Instance->FR & UART_FR_TXFF);    /* wait Tx FIFO not full */
    uart->handle.Instance->DR = c;
    while ((uart->handle.Instance->FR & UART_FR_BUSY)); /* wait TX Complete */

    return 1;
}

static int _uart_getc(struct rt_serial_device *serial)
{
    struct acm32_uart *uart;

    int ch;

    RT_ASSERT(serial != RT_NULL);

    uart = rt_container_of(serial, struct acm32_uart, serial);

    ch = -1;
    if (!(uart->handle.Instance->FR & UART_FR_RXFE))   /* Rx FIFO not empty */
    {
        ch = uart->handle.Instance->DR & 0xff;
    }

    return ch;
}

#ifdef RT_SERIAL_USING_DMA
/**
 * Serial port receive idle process. This need add to uart idle ISR.
 *
 * @param serial serial device
 */
static void dma_uart_rx_idle_isr(struct rt_serial_device *serial)
{
    struct acm32_uart *uart;

    RT_ASSERT(serial != RT_NULL);

    uart = rt_container_of(serial, struct acm32_uart, serial);

    rt_size_t recv_total_index, recv_len;
    rt_base_t level;

    /* disable interrupt */
    level = rt_hw_interrupt_disable();

    recv_total_index = uart->handle.lu32_RxSize - (uart->handle.HDMA_Rx->Instance->CTRL & 0xFFF);
    recv_len = recv_total_index - uart->handle.lu32_RxCount;
    uart->handle.lu32_RxCount = recv_total_index;
    /* enable interrupt */
    rt_hw_interrupt_enable(level);

    if (recv_len)
    {
        rt_hw_serial_isr(serial, RT_SERIAL_EVENT_RX_DMADONE | (recv_len << 8));
    }
}

/*
 DMA receive done process. This need add to DMA receive done ISR.

 @param serial serial device
*/
static void dma_rx_done_isr(struct rt_serial_device *serial)
{
    struct acm32_uart *uart;
    struct rt_serial_rx_fifo *rx_fifo = (struct rt_serial_rx_fifo *)serial->serial_rx;

    RT_ASSERT(serial != RT_NULL);

    uart = rt_container_of(serial, struct acm32_uart, serial);

    rt_size_t recv_len;
    rt_base_t level;

    /* disable interrupt */
    level = rt_hw_interrupt_disable();

    recv_len = serial->config.bufsz - (uart->handle.HDMA_Rx->Instance->CTRL & 0xFFF);
    uart->dma_rx.last_index = 0;

    DMA->INT_TC_CLR |= 1 << (uart->config->dma_rx->channel);      /* clear channel0 TC flag */

    /* enable interrupt */
    rt_hw_interrupt_enable(level);

    if (recv_len)
    {
        rt_hw_serial_isr(serial, RT_SERIAL_EVENT_RX_DMADONE | (recv_len << 8));
    }

    HAL_UART_Receive_DMA(&(uart->handle), &rx_fifo->buffer[rx_fifo->put_index], serial->config.bufsz);
}

static rt_ssize_t _uart_dma_transmit(struct rt_serial_device *serial, rt_uint8_t *buf, rt_size_t size, int direction)
{
    struct acm32_uart *uart;
    RT_ASSERT(serial != RT_NULL);
    uart = rt_container_of(serial, struct acm32_uart, serial);

    if (size == 0)
    {
        return 0;
    }

    if (RT_SERIAL_DMA_TX == direction)
    {
        if (HAL_UART_Transmit_DMA(&uart->handle, buf, size) == HAL_OK)
        {
            rt_hw_serial_isr(serial, RT_SERIAL_EVENT_TX_DMADONE);
            return size;
        }
        else
        {
            return 0;
        }
    }
    return 0;
}

#endif /* RT_SERIAL_USING_DMA */

static const struct rt_uart_ops acm32_uart_ops =
{
    _uart_configure,
    _uart_control,
    _uart_putc,
    _uart_getc,
#ifdef RT_SERIAL_USING_DMA
    _uart_dma_transmit,
#endif
};

#ifdef RT_SERIAL_USING_DMA
static void DMA_Configuration(struct rt_serial_device *serial, rt_uint32_t flag)
{
    struct rt_serial_rx_fifo *rx_fifo;
    DMA_HandleTypeDef *DMA_Handle;
    struct dma_config *dma_config;
    struct acm32_uart *uart;

    RT_ASSERT(serial != RT_NULL);

    uart = rt_container_of(serial, struct acm32_uart, serial);

    if (RT_DEVICE_FLAG_DMA_RX == flag)
    {
        DMA_Handle = &uart->dma_rx.handle;
        dma_config = uart->config->dma_rx;
    }
    else if (RT_DEVICE_FLAG_DMA_TX == flag)
    {
        DMA_Handle = &uart->dma_tx.handle;
        dma_config = uart->config->dma_tx;
    }
    else
    {
        return;
    }

    DMA_Handle->Instance                 = dma_config->Instance;

    if (RT_DEVICE_FLAG_DMA_RX == flag)
    {
        DMA_Handle->Init.Data_Flow          = DMA_DATA_FLOW_P2M;
        DMA_Handle->Init.Mode               = DMA_NORMAL;
        DMA_Handle->Init.Source_Inc         = DMA_SOURCE_ADDR_INCREASE_DISABLE;
        DMA_Handle->Init.Desination_Inc     = DMA_DST_ADDR_INCREASE_ENABLE;

    }
    else if (RT_DEVICE_FLAG_DMA_TX == flag)
    {
        DMA_Handle->Init.Data_Flow          = DMA_DATA_FLOW_M2P;
        DMA_Handle->Init.Mode               = DMA_NORMAL;
        DMA_Handle->Init.Source_Inc         = DMA_SOURCE_ADDR_INCREASE_ENABLE;
        DMA_Handle->Init.Desination_Inc     = DMA_DST_ADDR_INCREASE_DISABLE;
    }

    DMA_Handle->Init.Request_ID             = dma_config->request;
    DMA_Handle->Init.Source_Width           = DMA_SRC_WIDTH_BYTE;
    DMA_Handle->Init.Desination_Width       = DMA_DST_WIDTH_BYTE;

    if (HAL_DMA_Init(DMA_Handle) != HAL_OK)
    {
        RT_ASSERT(0);
    }

    if (RT_DEVICE_FLAG_DMA_RX == flag)
    {
        __HAL_LINK_DMA(uart->handle, HDMA_Rx, uart->dma_rx.handle);
    }
    else if (RT_DEVICE_FLAG_DMA_TX == flag)
    {
        __HAL_LINK_DMA(uart->handle, HDMA_Tx, uart->dma_tx.handle);
    }
    /* enable interrupt */
    if (flag == RT_DEVICE_FLAG_DMA_RX)
    {
        rx_fifo = (struct rt_serial_rx_fifo *)serial->serial_rx;
        /* Start DMA transfer */
        if (HAL_UART_Receive_DMA(&(uart->handle), rx_fifo->buffer, serial->config.bufsz) != HAL_OK)
        {
            /* Transfer error in reception process */
            RT_ASSERT(0);
        }

    }
}
#endif /* RT_SERIAL_USING_DMA */

enum
{
#ifdef BSP_USING_UART1
    UART1_INDEX,
#endif
#ifdef BSP_USING_UART2
    UART2_INDEX,
#endif
#ifdef BSP_USING_UART3
    UART3_INDEX,
#endif
    UART_MAX_INDEX,
};

static struct acm32_uart_config uart_config[] =
{
#ifdef BSP_USING_UART1
    UART1_CONFIG,
#endif
#ifdef BSP_USING_UART2
    UART2_CONFIG,
#endif
#ifdef BSP_USING_UART3
    UART3_CONFIG,
#endif
};

static struct acm32_uart uart_obj[sizeof(uart_config) / sizeof(uart_config[0])] = {0};
#ifdef RT_SERIAL_USING_DMA
static void uart_get_dma_config(void)
{
#if defined(BSP_USING_UART1)
#if defined(BSP_UART1_RX_USING_DMA)
    static struct dma_config uart1_rx_dma_conf = UART1_DMA_RX_CONFIG;
    uart_obj[UART1_INDEX].uart_dma_flag |= RT_DEVICE_FLAG_DMA_RX;
    uart_config[UART1_INDEX].dma_rx = &uart1_rx_dma_conf;
#endif /* BSP_UART1_RX_USING_DMA */
#if defined(BSP_UART1_TX_USING_DMA)
    static struct dma_config uart1_tx_dma_conf = UART1_DMA_TX_CONFIG;
    uart_obj[UART1_INDEX].uart_dma_flag |= RT_DEVICE_FLAG_DMA_TX;
    uart_config[UART1_INDEX].dma_tx = &uart1_tx_dma_conf;
#endif /* BSP_UART1_TX_USING_DMA */
#endif /* BSP_USING_UART1 */

#if defined(BSP_USING_UART2)
#if defined(BSP_UART2_RX_USING_DMA)
    static struct dma_config uart2_rx_dma_conf = UART2_DMA_RX_CONFIG;
    uart_obj[UART2_INDEX].uart_dma_flag |= RT_DEVICE_FLAG_DMA_RX;
    uart_config[UART2_INDEX].dma_rx = &uart2_rx_dma_conf;
#endif /* BSP_UART2_RX_USING_DMA */
#if defined(BSP_UART2_TX_USING_DMA)
    static struct dma_config uart2_tx_dma_conf = UART2_DMA_TX_CONFIG;
    uart_obj[UART2_INDEX].uart_dma_flag |= RT_DEVICE_FLAG_DMA_TX;
    uart_config[UART2_INDEX].dma_tx = &uart2_tx_dma_conf;
#endif /* BSP_UART2_TX_USING_DMA */
#endif /* BSP_USING_UART2 */

#if defined(BSP_USING_UART3)
#if defined(BSP_UART3_RX_USING_DMA)
    static struct dma_config uart3_rx_dma_conf = UART3_DMA_RX_CONFIG;
    uart_obj[UART3_INDEX].uart_dma_flag |= RT_DEVICE_FLAG_DMA_RX;
    uart_config[UART3_INDEX].dma_rx = &uart3_rx_dma_conf;
#endif /* BSP_UART3_RX_USING_DMA */
#if defined(BSP_UART3_TX_USING_DMA)
    static struct dma_config uart3_tx_dma_conf = UART3_DMA_TX_CONFIG;
    uart_obj[UART3_INDEX].uart_dma_flag |= RT_DEVICE_FLAG_DMA_TX;
    uart_config[UART3_INDEX].dma_tx = &uart3_tx_dma_conf;
#endif /* BSP_UART3_TX_USING_DMA */
#endif /* BSP_USING_UART3 */
}
#endif

rt_err_t rt_hw_uart_init(void)
{
    rt_size_t obj_num = sizeof(uart_obj) / sizeof(struct acm32_uart);
    struct serial_configure config = RT_SERIAL_CONFIG_DEFAULT;
    rt_err_t rc = RT_EOK;

#ifdef RT_SERIAL_USING_DMA
    uart_get_dma_config();
#endif

    for (int i = 0; i < obj_num; i++)
    {
        uart_obj[i].config          = &uart_config[i];

        uart_obj[i].serial.ops      = &acm32_uart_ops;
        uart_obj[i].serial.config   = config;

        /* register UART device */
        rc = rt_hw_serial_register(&uart_obj[i].serial, uart_obj[i].config->name,
                                   RT_DEVICE_FLAG_RDWR
                                   | RT_DEVICE_FLAG_INT_RX
                                   | RT_DEVICE_FLAG_INT_TX
                                   | uart_obj[i].uart_dma_flag
                                   , NULL);
        RT_ASSERT(rc == RT_EOK);
    }

    return rc;
}

static void uart_isr(struct rt_serial_device *serial)
{
    struct acm32_uart *uart = rt_container_of(serial, struct acm32_uart, serial);

    RT_ASSERT(serial != RT_NULL);

    /* receive interrupt enabled */
    if (uart->handle.Instance->IE & UART_IE_RXI)
    {
        if (uart->handle.Instance->RIS & UART_RIS_RXI)
        {
            rt_hw_serial_isr(serial, RT_SERIAL_EVENT_RX_IND);
        }
    }

#ifdef RT_SERIAL_USING_DMA
    if (uart->handle.Instance->IE & UART_IE_RTI)   /* Receive TimeOut Interrupt */
    {
        dma_uart_rx_idle_isr(serial);
        /* Clear RTI Status */
        uart->handle.Instance->ICR = UART_ICR_RTI;
    }
#endif /* RT_SERIAL_USING_DMA */

    if (uart->handle.Instance->IE & UART_IE_TXI && \
            uart->handle.Instance->RIS & UART_RIS_TXI)
    {
        /* Clear TXI Status */
        uart->handle.Instance->ICR = UART_ICR_TXI;
        if (serial->parent.open_flag & RT_DEVICE_FLAG_INT_TX)
        {
            rt_hw_serial_isr(serial, RT_SERIAL_EVENT_TX_DONE);
        }
        /* Disable TX interrupt */
        uart->handle.Instance->IE &= ~UART_IE_TXI;
    }
}

#if defined(BSP_USING_UART1)
void UART1_IRQHandler(void)
{
    /* enter interrupt */
    rt_interrupt_enter();

    uart_isr(&uart_obj[UART1_INDEX].serial);

    /* leave interrupt */
    rt_interrupt_leave();
}
#endif /* BSP_USING_UART1 */

#if defined(BSP_USING_UART2)
void UART2_IRQHandler(void)
{
    /* enter interrupt */
    rt_interrupt_enter();

    uart_isr(&uart_obj[UART2_INDEX].serial);

    /* leave interrupt */
    rt_interrupt_leave();
}
#endif /* BSP_USING_UART1 */

#if defined(BSP_USING_UART3)
void UART3_IRQHandler(void)
{
    /* enter interrupt */
    rt_interrupt_enter();

    uart_isr(&uart_obj[UART3_INDEX].serial);

    /* leave interrupt */
    rt_interrupt_leave();
}
#endif /* BSP_USING_UART1 */

#ifdef RT_SERIAL_USING_DMA
void DMA_IRQHandler(void)
{
    /* enter interrupt */
    rt_interrupt_enter();

    for (int i = 0; i < UART_MAX_INDEX; i++)
    {
        if (DMA->RAW_INT_TC_STATUS & (1 << uart_obj[i].config->dma_rx->channel))
        {
            dma_rx_done_isr(&uart_obj[i].serial);
            break;
        }

        if (DMA->RAW_INT_TC_STATUS & (1 << uart_obj[i].config->dma_tx->channel))
        {
            DMA->INT_TC_CLR |= 1 << (uart_obj[i].config->dma_tx->channel);      /* clear channel0 TC flag */
            break;
        }
    }

    /* leave interrupt */
    rt_interrupt_leave();
}
#endif /* RT_SERIAL_USING_DMA */

void HAL_UART_MspInit(UART_HandleTypeDef *huart)
{
    struct acm32_uart *uart;
    GPIO_InitTypeDef  GPIO_Uart;

    RT_ASSERT(huart != RT_NULL);

    /* get uart object */
    uart = rt_container_of(huart, struct acm32_uart, handle);

    /* Enable Clock */
    System_Module_Enable(uart->config->enable_id);

    /* Initialization GPIO */
    GPIO_Uart.Pin       = uart->config->tx_pin;
    GPIO_Uart.Mode      = GPIO_MODE_AF_PP;
    GPIO_Uart.Pull      = GPIO_PULLUP;
    GPIO_Uart.Alternate = GPIO_FUNCTION_2;
    HAL_GPIO_Init(uart->config->tx_port, &GPIO_Uart);

    GPIO_Uart.Pin       = uart->config->rx_pin;
    GPIO_Uart.Mode      = GPIO_MODE_AF_PP;
    GPIO_Uart.Pull      = GPIO_PULLUP;
    GPIO_Uart.Alternate = GPIO_FUNCTION_2;
    HAL_GPIO_Init(uart->config->rx_port, &GPIO_Uart);

    /* NVIC Config */
    NVIC_ClearPendingIRQ(uart->config->irq_type);
    NVIC_SetPriority(uart->config->irq_type, 5);
    NVIC_EnableIRQ(uart->config->irq_type);
}

#endif /* RT_USING_SEARIAL */

