/*
 * Copyright (c) 2006-2025, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author           Notes
 * 2026-01-24     ox-horse         first version
 */


#include "board.h"
#include "drv_usart.h"
#include "drv_config.h"

#ifdef RT_USING_SERIAL

//#define DRV_DEBUG
#define LOG_TAG             "drv.usart"
#include <drv_log.h>


#if !defined(BSP_USING_UART1) && !defined(BSP_USING_UART2) && !defined(BSP_USING_UART3) && \
    !defined(BSP_USING_UART4) && !defined(BSP_USING_UART5) && !defined(BSP_USING_UART6) && \
    !defined(BSP_USING_UART7) && !defined(BSP_USING_UART8) && !defined(BSP_USING_UART9) && \
    !defined(BSP_USING_UART10) && !defined(BSP_USING_UART11) && !defined(BSP_USING_UART12) && \
    !defined(BSP_USING_UART13) && !defined(BSP_USING_UART14) && !defined(BSP_USING_UART15) && \
    !defined(BSP_USING_LPUART1) && !defined(BSP_USING_LPUART2)
    #error "Please define at least one BSP_USING_UARTx"
    /* this driver can be disabled at menuconfig -> RT-Thread Components -> Device Drivers */
#endif

#ifdef RT_SERIAL_USING_DMA
    static rt_err_t UART_DMA_Transmit(struct n32_uart *uart);
#endif

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
#ifdef BSP_USING_UART10
    UART10_INDEX,
#endif
#ifdef BSP_USING_UART11
    UART11_INDEX,
#endif
#ifdef BSP_USING_UART12
    UART12_INDEX,
#endif
#ifdef BSP_USING_UART13
    UART13_INDEX,
#endif
#ifdef BSP_USING_UART14
    UART14_INDEX,
#endif
#ifdef BSP_USING_UART15
    UART15_INDEX,
#endif
#ifdef BSP_USING_LPUART1
    LPUART1_INDEX,
#endif
#ifdef BSP_USING_LPUART2
    LPUART2_INDEX,
#endif
};

static struct n32_uart_config uart_config[] =
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
#ifdef BSP_USING_UART10
    UART10_CONFIG,
#endif
#ifdef BSP_USING_UART11
    UART11_CONFIG,
#endif
#ifdef BSP_USING_UART12
    UART12_CONFIG,
#endif
#ifdef BSP_USING_UART13
    UART13_CONFIG,
#endif
#ifdef BSP_USING_UART14
    UART14_CONFIG,
#endif
#ifdef BSP_USING_UART15
    UART15_CONFIG,
#endif
#ifdef BSP_USING_LPUART1
    LPUART1_CONFIG,
#endif
#ifdef BSP_USING_LPUART2
    LPUART2_CONFIG,
#endif
};

static struct n32_uart uart_obj[sizeof(uart_config) / sizeof(uart_config[0])] = { 0 };

#ifdef RT_SERIAL_USING_DMA
static void dma_recv_callback(struct rt_serial_device *serial, rt_uint8_t isr_flag)
{
    struct n32_uart *uart;
    rt_base_t level;
    rt_size_t recv_len, read_len;

    RT_ASSERT(serial != RT_NULL);
    uart = rt_container_of(serial, struct n32_uart, serial);

    level = rt_hw_interrupt_disable();
    recv_len = 0;

    read_len = DMA_GetTransferredNumber(uart->config->dma_rx->Instance, uart->config->dma_rx->dma_channel);

    switch (isr_flag)
    {
    case UART_RX_DMA_IT_IDLE_FLAG:
    {
        if (uart->dma.rx_dma.block_has_recv_cnt != 0)
        {
            recv_len = read_len - uart->dma.rx_dma.block_has_recv_cnt;
        }
        else
        {
            recv_len = read_len;
        }
        uart->dma.rx_dma.block_has_recv_cnt = read_len;

        break;
    }
    case UART_RX_DMA_IT_BLOCK_TC_FLAG:
    {
        if (uart->dma.rx_dma.block_has_recv_cnt != 0)
        {
            recv_len = read_len - uart->dma.rx_dma.block_has_recv_cnt;
            uart->dma.rx_dma.block_has_recv_cnt = 0;
        }
        else
        {
            recv_len = DMA_BLOCK_SIZE;
        }
        break;
    }

    default:
        break;
    }

    if (recv_len)
    {
        rt_hw_serial_isr(serial, RT_SERIAL_EVENT_RX_DMADONE | (recv_len << 8));
    }
    rt_hw_interrupt_enable(level);
}


#if defined(BSP_UART1_RX_USING_DMA)  || defined(BSP_UART2_RX_USING_DMA)  || defined(BSP_UART3_RX_USING_DMA)  || \
    defined(BSP_UART4_RX_USING_DMA)  || defined(BSP_UART5_RX_USING_DMA)  || defined(BSP_UART6_RX_USING_DMA)  || \
    defined(BSP_UART7_RX_USING_DMA)  || defined(BSP_UART8_RX_USING_DMA)  || defined(BSP_UART9_RX_USING_DMA)  || \
    defined(BSP_UART10_RX_USING_DMA) || defined(BSP_UART11_RX_USING_DMA) || defined(BSP_UART12_RX_USING_DMA) || \
    defined(BSP_UART13_RX_USING_DMA) || defined(BSP_UART14_RX_USING_DMA) || defined(BSP_UART15_RX_USING_DMA)

static void uart_rx_dma_isr(struct n32_uart *uart_drv)
{
#if defined(SOC_SERIES_N32H7xx)
    if (DMA_GetCombinedStatus(uart_drv->config->dma_rx->Instance))
    {
        if (DMA_GetChannelIntBlockStatus(uart_drv->config->dma_rx->Instance, uart_drv->config->dma_rx->dma_channel) != RESET)
        {
            dma_recv_callback(&uart_drv->serial, UART_RX_DMA_IT_BLOCK_TC_FLAG);

            /* Clear interrupt event status */
            DMA_ClearChannelEventStatus(uart_drv->config->dma_rx->Instance, uart_drv->config->dma_rx->dma_channel, DMA_CH_EVENT_BLOCK_TRANSFER_COMPLETE);
        }
    }
#endif
}
#endif

#if defined(BSP_UART1_TX_USING_DMA)  || defined(BSP_UART2_TX_USING_DMA)  || defined(BSP_UART3_TX_USING_DMA)  || \
    defined(BSP_UART4_TX_USING_DMA)  || defined(BSP_UART5_TX_USING_DMA)  || defined(BSP_UART6_TX_USING_DMA)  || \
    defined(BSP_UART7_TX_USING_DMA)  || defined(BSP_UART8_TX_USING_DMA)  || defined(BSP_UART9_TX_USING_DMA)  || \
    defined(BSP_UART10_TX_USING_DMA) || defined(BSP_UART11_TX_USING_DMA) || defined(BSP_UART12_TX_USING_DMA) || \
    defined(BSP_UART13_TX_USING_DMA) || defined(BSP_UART14_TX_USING_DMA) || defined(BSP_UART15_TX_USING_DMA)

static void uart_tx_dma_isr(struct n32_uart *uart_drv)
{
    rt_base_t level;

    level = rt_hw_interrupt_disable();

#if defined(SOC_SERIES_N32H7xx)
    if (DMA_GetCombinedStatus(uart_drv->config->dma_tx->Instance))
    {
        if (DMA_GetChannelIntTfrStatus(uart_drv->config->dma_tx->Instance, uart_drv->config->dma_tx->dma_channel) == SET)
        {
            DMA_ChannelEventCmd(uart_drv->config->dma_tx->Instance, uart_drv->config->dma_tx->dma_channel, DMA_CH_EVENT_TRANSFER_COMPLETE, DISABLE);

            USART_EnableDMA(uart_drv->config->Instance, USART_DMAREQ_TX, DISABLE);

            DMA_ChannelCmd(uart_drv->config->dma_tx->Instance, uart_drv->config->dma_tx->dma_channel, DISABLE);

            /* Clear interrupt event status */
            DMA_ClearChannelEventStatus(uart_drv->config->dma_tx->Instance, uart_drv->config->dma_tx->dma_channel, DMA_CH_EVENT_TRANSFER_COMPLETE);

            if (uart_drv->dma.tx_dma.already_send_length < uart_drv->dma.tx_dma.record_length)
            {
                UART_DMA_Transmit(uart_drv);
            }
            else
            {
                /* DMA TX Complete
                 * 1. All data has been completely transmitted.
                 */
                rt_hw_serial_isr(&uart_drv->serial, RT_SERIAL_EVENT_TX_DMADONE);
            }
        }
    }
#endif

    rt_hw_interrupt_enable(level);
}
#endif /* RT_SERIAL_USING_DMA */


static void N32_UART_DMA_Config(struct rt_serial_device *serial, rt_ubase_t flag)
{
    rt_size_t i = 0;
    rt_err_t result = RT_EOK;
    struct n32_uart *uart;
    struct rt_serial_rx_fifo *rx_fifo = RT_NULL;

    RT_ASSERT(serial != RT_NULL);
    RT_ASSERT(flag == RT_DEVICE_FLAG_DMA_TX || flag == RT_DEVICE_FLAG_DMA_RX);
    uart = rt_container_of(serial, struct n32_uart, serial);

    /* DMA Initialize */
    if (RT_DEVICE_FLAG_DMA_RX == flag)
    {
        rx_fifo = (struct rt_serial_rx_fifo *)serial->serial_rx;

        uart->dma.RX_DMA_ChInitStr.DstAddr = (uint32_t)rx_fifo->buffer;

        /* Set LLI control information */
        for (i = 0; i < uart->dma.rx_dma.block_num; i++)
        {
            uart->dma.rx_dma.Read_LinkList[i].DstAddr = (uint32_t)(((uint8_t *)rx_fifo->buffer) + i * DMA_BLOCK_SIZE);
        }

        if (!DMA_ControllerIsEnabled(uart->config->dma_rx->Instance))
            DMA_ControllerCmd(uart->config->dma_rx->Instance, ENABLE);

        /* Initialize the specified DMA channel and Whether the specified channel was successfully initialized */
        if (DMA_ChannelInit(uart->config->dma_rx->Instance, &uart->dma.RX_DMA_ChInitStr, uart->config->dma_rx->dma_channel) == 0U)
        {
            /* Enable the specified DMA channel interrupt event */
            DMA_ChannelEventCmd(uart->config->dma_rx->Instance, uart->config->dma_rx->dma_channel, DMA_CH_EVENT_BLOCK_TRANSFER_COMPLETE, ENABLE);

            /* Configure DMAMUX */
            DMAMUX_SetRequestID(DMAMUX1_ID, uart->config->dma_rx->dmamux_channel, uart->config->dma_rx->dmamux_request);

            uart->dma.DMA_Rx_Init = RT_TRUE;

            /* Enable the specified DMA channel */
            DMA_ChannelCmd(uart->config->dma_rx->Instance, uart->config->dma_rx->dma_channel, ENABLE);

            /* enable dma irq */
            NVIC_SetPriority(uart->config->dma_rx->dma_irq, NVIC_EncodePriority(NVIC_GetPriorityGrouping(), 0, 0));
            NVIC_EnableIRQ(uart->config->dma_rx->dma_irq);
        }
        else
        {
            LOG_E("%s RX DMA channel initialization failed!", uart->config->name);
            result = -RT_ERROR;
        }

        RT_ASSERT(result == RT_EOK)

        /* Enable the USART idle interrupts */
        USART_ConfigInt(uart->config->Instance, USART_INT_IDLEF, ENABLE);

        /* Enables the USART's DMA interface */
        USART_EnableDMA(uart->config->Instance, USART_DMAREQ_RX, ENABLE);
    }

    /* enable uart irq */
    NVIC_SetPriority(uart->config->irq_type, NVIC_EncodePriority(NVIC_GetPriorityGrouping(), 1, 0));
    NVIC_EnableIRQ(uart->config->irq_type);
}

static rt_err_t UART_DMA_Transmit(struct n32_uart *uart)
{
    rt_uint16_t send_length;
    rt_size_t already_send_length;
    const rt_uint8_t *send_buf = RT_NULL;

    RT_ASSERT(uart != RT_NULL);

    if (uart->dma.DMA_Tx_Init == RT_TRUE)
    {
#if defined(SOC_SERIES_N32H7xx)
        /* DMA uses a single block, with a maximum of 4095 per block */
        if (uart->dma.tx_dma.total_length > 4095U)
        {
            send_length = 4095U;
            uart->dma.tx_dma.total_length = uart->dma.tx_dma.total_length - 4095U;
        }
        else
        {
            send_length = uart->dma.tx_dma.total_length;
            uart->dma.tx_dma.total_length = 0;
        }

        /* Calculate the length sent after this transmission is complete */
        uart->dma.tx_dma.already_send_length += send_length;
        /* calculate the start address */
        already_send_length = uart->dma.tx_dma.record_length - send_length - uart->dma.tx_dma.total_length;
        send_buf = uart->dma.tx_dma.buf + already_send_length;

        DMA_ChannelCmd(uart->config->dma_tx->Instance, uart->config->dma_tx->dma_channel, DISABLE);

        if (!DMA_ControllerIsEnabled(uart->config->dma_tx->Instance))
            DMA_ControllerCmd(uart->config->dma_tx->Instance, ENABLE);

        uart->dma.TX_DMA_ChInitStr.IntEn      = 1U;
        uart->dma.TX_DMA_ChInitStr.SrcAddr    = (uint32_t)send_buf;
        uart->dma.TX_DMA_ChInitStr.BlkTfrSize = send_length;

        DMA_ControllerCmd(uart->config->dma_tx->Instance, ENABLE);
        if (DMA_ChannelInit(uart->config->dma_tx->Instance, &uart->dma.TX_DMA_ChInitStr, uart->config->dma_tx->dma_channel) == 0U)
        {
            /* Enable transaction complete interrupt event */
            DMA_ChannelEventCmd(uart->config->dma_tx->Instance, uart->config->dma_tx->dma_channel, DMA_CH_EVENT_TRANSFER_COMPLETE, ENABLE);

            /* Enable the specified DMA channel */
            DMA_ChannelCmd(uart->config->dma_tx->Instance, uart->config->dma_tx->dma_channel, ENABLE);

            /* Clears the USARTx's USART_FLAG_TXC flags */
            USART_ClrFlag(uart->config->Instance, USART_FLAG_TXC);

            /* Enables the USART's DMA interface */
            USART_EnableDMA(uart->config->Instance, USART_DMAREQ_TX, ENABLE);

            USART_Enable(uart->config->Instance, ENABLE);
        }
#endif
    }
    else
    {
        LOG_E("UART TX DMA Mode, TX DMA did not complete initialization.");
        return -RT_ERROR;
    }

    return RT_EOK;
}
#endif /* RT_SERIAL_USING_DMA */


rt_uint32_t n32_uart_get_mask(rt_uint32_t word_length, rt_uint32_t parity)
{
    rt_uint32_t mask = 0x00FFU;
    if (word_length == USART_WL_8B)
    {
        if (parity == USART_PE_NO)
        {
            mask = 0x00FFU ;
        }
        else
        {
            mask = 0x007FU ;
        }
    }
#ifdef USART_WL_9B
    else if (word_length == USART_WL_9B)
    {
        if (parity == USART_PE_NO)
        {
            mask = 0x01FFU ;
        }
        else
        {
            mask = 0x00FFU ;
        }
    }
#endif
    return mask;
}

static rt_err_t n32_configure(struct rt_serial_device *serial, struct serial_configure *cfg)
{
    struct n32_uart *uart;
    USART_InitType USART_InitStructure;
    RT_ASSERT(serial != RT_NULL);
    RT_ASSERT(cfg != RT_NULL);

    uart = rt_container_of(serial, struct n32_uart, serial);

    /* Enable UART Clock */
    uart->config->EnablePeriphClk(uart->config->periph, ENABLE);

    USART_StructInit(&USART_InitStructure);
    USART_InitStructure.BaudRate = cfg->baud_rate;
    USART_InitStructure.Mode     = USART_MODE_RX | USART_MODE_TX;

#if defined(SOC_SERIES_N32H7)
#ifdef USART_CTRL1_OSPM
#endif
    USART_InitStructure.OverSampling = cfg->baud_rate > 5000000 ? USART_8OVER : USART_16OVER;
#else
    USART_InitStructure.OverSampling = USART_16OVER;
#endif /* USART_CTRL1_OSPM */

    switch (cfg->flowcontrol)
    {
    case RT_SERIAL_FLOWCONTROL_NONE:
        USART_InitStructure.HardwareFlowControl = USART_HFCTRL_NONE;
        break;
    case RT_SERIAL_FLOWCONTROL_CTSRTS:
        USART_InitStructure.HardwareFlowControl = USART_HFCTRL_RTS_CTS;
        break;
    default:
        USART_InitStructure.HardwareFlowControl = USART_HFCTRL_NONE;
        break;
    }

    switch (cfg->data_bits)
    {
    case DATA_BITS_8:
        if (cfg->parity == PARITY_ODD || cfg->parity == PARITY_EVEN)
            USART_InitStructure.WordLength = USART_WL_9B;
        else
            USART_InitStructure.WordLength = USART_WL_8B;
        break;
    case DATA_BITS_9:
        USART_InitStructure.WordLength = USART_WL_9B;
        break;
    default:
        USART_InitStructure.WordLength = USART_WL_8B;
        break;
    }

    switch (cfg->stop_bits)
    {
    case STOP_BITS_1:
        USART_InitStructure.StopBits = USART_STPB_1;
        break;
    case STOP_BITS_2:
        USART_InitStructure.StopBits = USART_STPB_2;
        break;
    default:
        USART_InitStructure.StopBits = USART_STPB_1;
        break;
    }

    switch (cfg->parity)
    {
    case PARITY_NONE:
        USART_InitStructure.Parity = USART_PE_NO;
        break;
    case PARITY_ODD:
        USART_InitStructure.Parity = USART_PE_ODD;
        break;
    case PARITY_EVEN:
        USART_InitStructure.Parity = USART_PE_EVEN;
        break;
    default:
        USART_InitStructure.Parity = USART_PE_NO;
        break;
    }

#ifdef RT_SERIAL_USING_DMA
    if (!(serial->parent.open_flag & RT_DEVICE_OFLAG_OPEN))
    {
        uart->dma.rx_dma.block_has_recv_cnt = 0;
    }
#endif

    USART_Init(uart->config->Instance, &USART_InitStructure);

    USART_Enable(uart->config->Instance, ENABLE);

    uart->DR_mask = n32_uart_get_mask(USART_InitStructure.WordLength, USART_InitStructure.Parity);

    return RT_EOK;
}


static rt_err_t n32_control(struct rt_serial_device *serial, int cmd, void *arg)
{
    struct n32_uart *uart;
#ifdef RT_SERIAL_USING_DMA
    rt_ubase_t ctrl_arg = (rt_ubase_t)arg;
#endif

    RT_ASSERT(serial != RT_NULL);
    uart = rt_container_of(serial, struct n32_uart, serial);

    switch (cmd)
    {
    /* disable interrupt */
    case RT_DEVICE_CTRL_CLR_INT:
        /* disable rx irq */
        NVIC_DisableIRQ(uart->config->irq_type);
        /* disable interrupt */
        USART_ConfigInt(uart->config->Instance, USART_INT_RXDNE, DISABLE);

#ifdef RT_SERIAL_USING_DMA
        /* disable DMA */
        if (ctrl_arg == RT_DEVICE_FLAG_DMA_RX)
        {
            NVIC_DisableIRQ(uart->config->dma_rx->dma_irq);

            DMA_ChannelCmd(uart->config->dma_rx->Instance, uart->config->dma_rx->dma_channel, DISABLE);

            USART_EnableDMA(uart->config->Instance, USART_DMAREQ_RX, DISABLE);

            rt_free(uart->dma.rx_dma.Read_LinkList);
            uart->dma.rx_dma.Read_LinkList = RT_NULL;
        }
        else if (ctrl_arg == RT_DEVICE_FLAG_DMA_TX)
        {
            NVIC_DisableIRQ(uart->config->dma_tx->dma_irq);

            DMA_ChannelCmd(uart->config->dma_rx->Instance, uart->config->dma_rx->dma_channel, DISABLE);

            USART_EnableDMA(uart->config->Instance, USART_DMAREQ_TX, DISABLE);
        }
#endif
        break;

    /* enable interrupt */
    case RT_DEVICE_CTRL_SET_INT:
        /* enable rx irq */
        NVIC_SetPriority(uart->config->irq_type, NVIC_EncodePriority(NVIC_GetPriorityGrouping(), 1, 0));
        NVIC_EnableIRQ(uart->config->irq_type);
        /* enable interrupt */
        USART_ConfigInt(uart->config->Instance, USART_INT_RXDNE, ENABLE);
        break;

#ifdef RT_SERIAL_USING_DMA
    case RT_DEVICE_CTRL_CONFIG:
        N32_UART_DMA_Config(serial, ctrl_arg);
        break;
#endif

    case RT_DEVICE_CTRL_CLOSE:
        USART_DeInit(uart->config->Instance);
        /* Enable UART Clock */
        uart->config->EnablePeriphClk(uart->config->periph, DISABLE);
        break;

    }
    return RT_EOK;
}

static int n32_putc(struct rt_serial_device *serial, char c)
{
    struct n32_uart *uart;
    RT_ASSERT(serial != RT_NULL);

    uart = rt_container_of(serial, struct n32_uart, serial);

    /* Clear transmission complete flag */
    if (USART_GetFlagStatus(uart->config->Instance, USART_FLAG_TXC) != RESET)
        USART_ClrFlag(uart->config->Instance, USART_FLAG_TXC);

    /* Send data */
    USART_SendData(uart->config->Instance, c);

    while (USART_GetFlagStatus(uart->config->Instance, USART_FLAG_TXC) == RESET)
    {
    }

    return 1;
}

static int n32_getc(struct rt_serial_device *serial)
{
    int ch;
    struct n32_uart *uart;
    RT_ASSERT(serial != RT_NULL);
    uart = rt_container_of(serial, struct n32_uart, serial);

    ch = -1;
    if (USART_GetFlagStatus(uart->config->Instance, USART_FLAG_RXDNE) != RESET)
    {
        ch = USART_ReceiveData(uart->config->Instance);
    }
    return ch;
}

static rt_ssize_t n32_dma_transmit(struct rt_serial_device *serial, rt_uint8_t *buf, rt_size_t size, int direction)
{
    struct n32_uart *uart = RT_NULL;

    RT_ASSERT(serial != RT_NULL);
    RT_ASSERT(buf != RT_NULL);
    uart = rt_container_of(serial, struct n32_uart, serial);

    RT_ASSERT(uart != RT_NULL);
    if (size == 0)
    {
        return 0;
    }

#ifdef RT_SERIAL_USING_DMA
    if (RT_SERIAL_DMA_TX == direction)
    {
        uart->dma.tx_dma.record_length       = size;
        uart->dma.tx_dma.total_length        = size;
        uart->dma.tx_dma.already_send_length = 0U;
        uart->dma.tx_dma.buf                 = buf;

        /* start once data exchange in DMA mode */
        UART_DMA_Transmit(uart);
    }
#endif

    return size;
}

static void uart_isr(struct rt_serial_device *serial)
{
    struct n32_uart *uart;

    RT_ASSERT(serial != RT_NULL);
    uart = rt_container_of(serial, struct n32_uart, serial);

    /* UART in mode Receiver */
    if ((USART_GetFlagStatus(uart->config->Instance, USART_FLAG_RXDNE) != RESET) &&
            (USART_GetIntStatus(uart->config->Instance, USART_INT_RXDNE) != RESET))
    {
        rt_hw_serial_isr(serial, RT_SERIAL_EVENT_RX_IND);
    }
#ifdef RT_SERIAL_USING_DMA
    else if ((uart->uart_dma_flag) &&
             (USART_GetFlagStatus(uart->config->Instance, USART_FLAG_IDLEF) != RESET) &&
             (USART_GetIntStatus(uart->config->Instance, USART_INT_IDLEF) != RESET))
    {
        dma_recv_callback(serial, UART_RX_DMA_IT_IDLE_FLAG);
        USART_GetFlagStatus(uart->config->Instance, USART_FLAG_IDLEF);
        USART_ReceiveData(uart->config->Instance);
    }
    else if ((USART_GetFlagStatus(uart->config->Instance, USART_FLAG_TXC) != RESET) &&
             (USART_GetIntStatus(uart->config->Instance, USART_INT_TXC) != RESET))
    {
        USART_ClrFlag(uart->config->Instance, USART_FLAG_TXC);
    }
#endif
    else
    {
        if ((USART_GetFlagStatus(uart->config->Instance, USART_FLAG_OREF) != RESET) ||
                (USART_GetFlagStatus(uart->config->Instance, USART_FLAG_NEF) != RESET)  ||
                (USART_GetFlagStatus(uart->config->Instance, USART_FLAG_FEF) != RESET)  ||
                (USART_GetFlagStatus(uart->config->Instance, USART_FLAG_PEF) != RESET))
        {
            USART_GetFlagStatus(uart->config->Instance, USART_FLAG_OREF | USART_FLAG_NEF | USART_FLAG_FEF | USART_FLAG_PEF);
            USART_ReceiveData(uart->config->Instance);
        }
        if (USART_GetFlagStatus(uart->config->Instance, USART_FLAG_LINBD) != RESET)
        {
            USART_ClrFlag(uart->config->Instance, USART_FLAG_LINBD);
        }

        if (USART_GetFlagStatus(uart->config->Instance, USART_FLAG_CTSF) != RESET)
        {
            USART_ClrFlag(uart->config->Instance, USART_FLAG_CTSF);
        }

        if (USART_GetFlagStatus(uart->config->Instance, USART_FLAG_TXDE) != RESET)
        {
            USART_ClrFlag(uart->config->Instance, USART_FLAG_CTSF);
        }
        if (USART_GetFlagStatus(uart->config->Instance, USART_FLAG_RXDNE) != RESET)
        {
            USART_ClrFlag(uart->config->Instance, USART_FLAG_RXDNE);
        }
    }
}

#if defined(BSP_USING_UART1)
void USART1_IRQHandler(void)
{
    /* enter interrupt */
    rt_interrupt_enter();

    uart_isr(&(uart_obj[UART1_INDEX].serial));

    /* leave interrupt */
    rt_interrupt_leave();
}
#if defined(RT_SERIAL_USING_DMA) && defined(BSP_UART1_RX_USING_DMA) && defined(UART1_RX_DMA_IRQHandler)
void UART1_RX_DMA_IRQHandler(void)
{
    /* enter interrupt */
    rt_interrupt_enter();

    uart_rx_dma_isr(&uart_obj[UART1_INDEX]);

    /* leave interrupt */
    rt_interrupt_leave();
}
#endif /* defined(RT_SERIAL_USING_DMA) && defined(BSP_UART1_RX_USING_DMA) && defined(UART1_RX_DMA_IRQHandler) */
#if defined(RT_SERIAL_USING_DMA) && defined(BSP_UART1_TX_USING_DMA) && defined(UART1_TX_DMA_IRQHandler)
void UART1_TX_DMA_IRQHandler(void)
{
    /* enter interrupt */
    rt_interrupt_enter();

    uart_tx_dma_isr(&uart_obj[UART1_INDEX]);

    /* leave interrupt */
    rt_interrupt_leave();
}
#endif /* defined(RT_SERIAL_USING_DMA) && defined(BSP_UART1_TX_USING_DMA) && defined(UART1_TX_DMA_IRQHandler) */
#endif /* BSP_USING_UART1 */

#if defined(BSP_USING_UART2)
void USART2_IRQHandler(void)
{
    /* enter interrupt */
    rt_interrupt_enter();

    uart_isr(&(uart_obj[UART2_INDEX].serial));

    /* leave interrupt */
    rt_interrupt_leave();
}
#if defined(RT_SERIAL_USING_DMA) && defined(BSP_UART2_RX_USING_DMA) && defined(UART2_RX_DMA_IRQHandler)
void UART2_RX_DMA_IRQHandler(void)
{
    /* enter interrupt */
    rt_interrupt_enter();

    uart_rx_dma_isr(&uart_obj[UART2_INDEX]);

    /* leave interrupt */
    rt_interrupt_leave();
}
#endif /* defined(RT_SERIAL_USING_DMA) && defined(BSP_UART2_RX_USING_DMA) && defined(UART2_RX_DMA_IRQHandler) */
#if defined(RT_SERIAL_USING_DMA) && defined(BSP_UART2_TX_USING_DMA) && defined(UART2_TX_DMA_IRQHandler)
void UART2_TX_DMA_IRQHandler(void)
{
    /* enter interrupt */
    rt_interrupt_enter();

    uart_tx_dma_isr(&uart_obj[UART2_INDEX]);

    /* leave interrupt */
    rt_interrupt_leave();
}
#endif /* defined(RT_SERIAL_USING_DMA) && defined(BSP_UART2_TX_USING_DMA) && defined(UART2_TX_DMA_IRQHandler) */
#endif /* BSP_USING_UART2 */

#if defined(BSP_USING_UART3)
void USART3_IRQHandler(void)
{
    /* enter interrupt */
    rt_interrupt_enter();

    uart_isr(&(uart_obj[UART3_INDEX].serial));

    /* leave interrupt */
    rt_interrupt_leave();
}
#if defined(RT_SERIAL_USING_DMA) && defined(BSP_UART3_RX_USING_DMA) && defined(UART3_RX_DMA_IRQHandler)
void UART3_RX_DMA_IRQHandler(void)
{
    /* enter interrupt */
    rt_interrupt_enter();

    uart_rx_dma_isr(&uart_obj[UART3_INDEX]);

    /* leave interrupt */
    rt_interrupt_leave();
}
#endif /* defined(RT_SERIAL_USING_DMA) && defined(BSP_UART3_RX_USING_DMA) && defined(UART3_RX_DMA_IRQHandler) */
#if defined(RT_SERIAL_USING_DMA) && defined(BSP_UART3_TX_USING_DMA) && defined(UART3_TX_DMA_IRQHandler)
void UART3_TX_DMA_IRQHandler(void)
{
    /* enter interrupt */
    rt_interrupt_enter();

    uart_tx_dma_isr(&uart_obj[UART3_INDEX]);

    /* leave interrupt */
    rt_interrupt_leave();
}
#endif /* defined(RT_SERIAL_USING_DMA) && defined(BSP_UART3_TX_USING_DMA) && defined(UART3_TX_DMA_IRQHandler) */
#endif /* BSP_USING_UART3 */

#if defined(BSP_USING_UART4)
void USART4_IRQHandler(void)
{
    /* enter interrupt */
    rt_interrupt_enter();

    uart_isr(&(uart_obj[UART4_INDEX].serial));

    /* leave interrupt */
    rt_interrupt_leave();
}
#if defined(RT_SERIAL_USING_DMA) && defined(BSP_UART4_RX_USING_DMA) && defined(UART4_RX_DMA_IRQHandler)
void UART4_RX_DMA_IRQHandler(void)
{
    /* enter interrupt */
    rt_interrupt_enter();

    uart_rx_dma_isr(&uart_obj[UART4_INDEX]);

    /* leave interrupt */
    rt_interrupt_leave();
}
#endif /* defined(RT_SERIAL_USING_DMA) && defined(BSP_UART4_RX_USING_DMA) && defined(UART4_RX_DMA_IRQHandler) */
#if defined(RT_SERIAL_USING_DMA) && defined(BSP_UART4_TX_USING_DMA) && defined(UART4_TX_DMA_IRQHandler)
void UART4_TX_DMA_IRQHandler(void)
{
    /* enter interrupt */
    rt_interrupt_enter();

    uart_tx_dma_isr(&uart_obj[UART4_INDEX]);

    /* leave interrupt */
    rt_interrupt_leave();
}
#endif /* defined(RT_SERIAL_USING_DMA) && defined(BSP_UART4_TX_USING_DMA) && defined(UART4_TX_DMA_IRQHandler) */
#endif /* BSP_USING_UART4 */

#if defined(BSP_USING_UART5)
void USART5_IRQHandler(void)
{
    /* enter interrupt */
    rt_interrupt_enter();

    uart_isr(&(uart_obj[UART5_INDEX].serial));

    /* leave interrupt */
    rt_interrupt_leave();
}
#if defined(RT_SERIAL_USING_DMA) && defined(BSP_UART5_RX_USING_DMA) && defined(UART5_RX_DMA_IRQHandler)
void UART5_RX_DMA_IRQHandler(void)
{
    /* enter interrupt */
    rt_interrupt_enter();

    uart_rx_dma_isr(&uart_obj[UART5_INDEX]);

    /* leave interrupt */
    rt_interrupt_leave();
}
#endif /* defined(RT_SERIAL_USING_DMA) && defined(BSP_UART5_RX_USING_DMA) && defined(UART5_RX_DMA_IRQHandler) */
#if defined(RT_SERIAL_USING_DMA) && defined(BSP_UART5_TX_USING_DMA) && defined(UART5_TX_DMA_IRQHandler)
void UART5_TX_DMA_IRQHandler(void)
{
    /* enter interrupt */
    rt_interrupt_enter();

    uart_tx_dma_isr(&uart_obj[UART5_INDEX]);

    /* leave interrupt */
    rt_interrupt_leave();
}
#endif /* defined(RT_SERIAL_USING_DMA) && defined(BSP_UART5_TX_USING_DMA) && defined(UART5_TX_DMA_IRQHandler) */
#endif /* BSP_USING_UART5 */

#if defined(BSP_USING_UART6)
void USART6_IRQHandler(void)
{
    /* enter interrupt */
    rt_interrupt_enter();

    uart_isr(&(uart_obj[UART6_INDEX].serial));

    /* leave interrupt */
    rt_interrupt_leave();
}
#if defined(RT_SERIAL_USING_DMA) && defined(BSP_UART6_RX_USING_DMA) && defined(UART6_RX_DMA_IRQHandler)
void UART6_RX_DMA_IRQHandler(void)
{
    /* enter interrupt */
    rt_interrupt_enter();

    uart_rx_dma_isr(&uart_obj[UART6_INDEX]);

    /* leave interrupt */
    rt_interrupt_leave();
}
#endif /* defined(RT_SERIAL_USING_DMA) && defined(BSP_UART6_RX_USING_DMA) && defined(UART6_RX_DMA_IRQHandler) */
#if defined(RT_SERIAL_USING_DMA) && defined(BSP_UART6_TX_USING_DMA) && defined(UART6_TX_DMA_IRQHandler)
void UART6_TX_DMA_IRQHandler(void)
{
    /* enter interrupt */
    rt_interrupt_enter();

    uart_tx_dma_isr(&uart_obj[UART6_INDEX]);

    /* leave interrupt */
    rt_interrupt_leave();
}
#endif /* defined(RT_SERIAL_USING_DMA) && defined(BSP_UART6_TX_USING_DMA) && defined(UART6_TX_DMA_IRQHandler) */
#endif /* BSP_USING_UART6 */

#if defined(BSP_USING_UART7)
void USART7_IRQHandler(void)
{
    /* enter interrupt */
    rt_interrupt_enter();

    uart_isr(&(uart_obj[UART7_INDEX].serial));

    /* leave interrupt */
    rt_interrupt_leave();
}
#if defined(RT_SERIAL_USING_DMA) && defined(BSP_UART7_RX_USING_DMA) && defined(UART7_RX_DMA_IRQHandler)
void UART7_RX_DMA_IRQHandler(void)
{
    /* enter interrupt */
    rt_interrupt_enter();

    uart_rx_dma_isr(&uart_obj[UART7_INDEX]);

    /* leave interrupt */
    rt_interrupt_leave();
}
#endif /* defined(RT_SERIAL_USING_DMA) && defined(BSP_UART7_RX_USING_DMA) && defined(UART7_RX_DMA_IRQHandler) */
#if defined(RT_SERIAL_USING_DMA) && defined(BSP_UART7_TX_USING_DMA) && defined(UART7_TX_DMA_IRQHandler)
void UART7_TX_DMA_IRQHandler(void)
{
    /* enter interrupt */
    rt_interrupt_enter();

    uart_tx_dma_isr(&uart_obj[UART7_INDEX]);

    /* leave interrupt */
    rt_interrupt_leave();
}
#endif /* defined(RT_SERIAL_USING_DMA) && defined(BSP_UART7_TX_USING_DMA) && defined(UART7_TX_DMA_IRQHandler) */
#endif /* BSP_USING_UART7 */

#if defined(BSP_USING_UART8)
void USART8_IRQHandler(void)
{
    /* enter interrupt */
    rt_interrupt_enter();

    uart_isr(&(uart_obj[UART8_INDEX].serial));

    /* leave interrupt */
    rt_interrupt_leave();
}
#if defined(RT_SERIAL_USING_DMA) && defined(BSP_UART8_RX_USING_DMA) && defined(UART8_RX_DMA_IRQHandler)
void UART8_RX_DMA_IRQHandler(void)
{
    /* enter interrupt */
    rt_interrupt_enter();

    uart_rx_dma_isr(&uart_obj[UART8_INDEX]);

    /* leave interrupt */
    rt_interrupt_leave();
}
#endif /* defined(RT_SERIAL_USING_DMA) && defined(BSP_UART8_RX_USING_DMA) && defined(UART8_RX_DMA_IRQHandler) */
#if defined(RT_SERIAL_USING_DMA) && defined(BSP_UART8_TX_USING_DMA) && defined(UART8_TX_DMA_IRQHandler)
void UART8_TX_DMA_IRQHandler(void)
{
    /* enter interrupt */
    rt_interrupt_enter();

    uart_tx_dma_isr(&uart_obj[UART8_INDEX]);

    /* leave interrupt */
    rt_interrupt_leave();
}
#endif /* defined(RT_SERIAL_USING_DMA) && defined(BSP_UART8_TX_USING_DMA) && defined(UART8_TX_DMA_IRQHandler) */
#endif /* BSP_USING_UART8 */

#if defined(BSP_USING_UART9)
void UART9_IRQHandler(void)
{
    /* enter interrupt */
    rt_interrupt_enter();

    uart_isr(&(uart_obj[UART9_INDEX].serial));

    /* leave interrupt */
    rt_interrupt_leave();
}
#if defined(RT_SERIAL_USING_DMA) && defined(BSP_UART9_RX_USING_DMA) && defined(UART9_RX_DMA_IRQHandler)
void UART9_RX_DMA_IRQHandler(void)
{
    /* enter interrupt */
    rt_interrupt_enter();

    uart_rx_dma_isr(&uart_obj[UART9_INDEX]);

    /* leave interrupt */
    rt_interrupt_leave();
}
#endif /* defined(RT_SERIAL_USING_DMA) && defined(BSP_UART9_RX_USING_DMA) && defined(UART9_RX_DMA_IRQHandler) */
#if defined(RT_SERIAL_USING_DMA) && defined(BSP_UART9_TX_USING_DMA) && defined(UART9_TX_DMA_IRQHandler)
void UART9_TX_DMA_IRQHandler(void)
{
    /* enter interrupt */
    rt_interrupt_enter();

    uart_tx_dma_isr(&uart_obj[UART9_INDEX]);

    /* leave interrupt */
    rt_interrupt_leave();
}
#endif /* defined(RT_SERIAL_USING_DMA) && defined(BSP_UART9_TX_USING_DMA) && defined(UART9_TX_DMA_IRQHandler) */
#endif /* BSP_USING_UART9 */

#if defined(BSP_USING_UART10)
void UART10_IRQHandler(void)
{
    /* enter interrupt */
    rt_interrupt_enter();

    uart_isr(&(uart_obj[UART10_INDEX].serial));

    /* leave interrupt */
    rt_interrupt_leave();
}
#if defined(RT_SERIAL_USING_DMA) && defined(BSP_UART10_RX_USING_DMA) && defined(UART10_RX_DMA_IRQHandler)
void UART10_RX_DMA_IRQHandler(void)
{
    /* enter interrupt */
    rt_interrupt_enter();

    uart_rx_dma_isr(&uart_obj[UART10_INDEX]);

    /* leave interrupt */
    rt_interrupt_leave();
}
#endif /* defined(RT_SERIAL_USING_DMA) && defined(BSP_UART10_RX_USING_DMA) && defined(UART10_RX_DMA_IRQHandler) */
#if defined(RT_SERIAL_USING_DMA) && defined(BSP_UART10_TX_USING_DMA) && defined(UART10_TX_DMA_IRQHandler)
void UART10_TX_DMA_IRQHandler(void)
{
    /* enter interrupt */
    rt_interrupt_enter();

    uart_tx_dma_isr(&uart_obj[UART10_INDEX]);

    /* leave interrupt */
    rt_interrupt_leave();
}
#endif /* defined(RT_SERIAL_USING_DMA) && defined(BSP_UART10_TX_USING_DMA) && defined(UART10_TX_DMA_IRQHandler) */
#endif /* BSP_USING_UART10 */

#if defined(BSP_USING_UART11)
void UART11_IRQHandler(void)
{
    /* enter interrupt */
    rt_interrupt_enter();

    uart_isr(&(uart_obj[UART11_INDEX].serial));

    /* leave interrupt */
    rt_interrupt_leave();
}
#if defined(RT_SERIAL_USING_DMA) && defined(BSP_UART11_RX_USING_DMA) && defined(UART11_RX_DMA_IRQHandler)
void UART11_RX_DMA_IRQHandler(void)
{
    /* enter interrupt */
    rt_interrupt_enter();

    uart_rx_dma_isr(&uart_obj[UART11_INDEX]);

    /* leave interrupt */
    rt_interrupt_leave();
}
#endif /* defined(RT_SERIAL_USING_DMA) && defined(BSP_UART11_RX_USING_DMA) && defined(UART11_RX_DMA_IRQHandler) */
#if defined(RT_SERIAL_USING_DMA) && defined(BSP_UART11_TX_USING_DMA) && defined(UART11_TX_DMA_IRQHandler)
void UART11_TX_DMA_IRQHandler(void)
{
    /* enter interrupt */
    rt_interrupt_enter();

    uart_tx_dma_isr(&uart_obj[UART11_INDEX]);

    /* leave interrupt */
    rt_interrupt_leave();
}
#endif /* defined(RT_SERIAL_USING_DMA) && defined(BSP_UART11_TX_USING_DMA) && defined(UART11_TX_DMA_IRQHandler) */
#endif /* BSP_USING_UART11 */

#if defined(BSP_USING_UART12)
void UART12_IRQHandler(void)
{
    /* enter interrupt */
    rt_interrupt_enter();

    uart_isr(&(uart_obj[UART12_INDEX].serial));

    /* leave interrupt */
    rt_interrupt_leave();
}
#if defined(RT_SERIAL_USING_DMA) && defined(BSP_UART12_RX_USING_DMA) && defined(UART12_RX_DMA_IRQHandler)
void UART12_RX_DMA_IRQHandler(void)
{
    /* enter interrupt */
    rt_interrupt_enter();

    uart_rx_dma_isr(&uart_obj[UART12_INDEX]);

    /* leave interrupt */
    rt_interrupt_leave();
}
#endif /* defined(RT_SERIAL_USING_DMA) && defined(BSP_UART12_RX_USING_DMA) && defined(UART12_RX_DMA_IRQHandler) */
#if defined(RT_SERIAL_USING_DMA) && defined(BSP_UART12_TX_USING_DMA) && defined(UART12_TX_DMA_IRQHandler)
void UART12_TX_DMA_IRQHandler(void)
{
    /* enter interrupt */
    rt_interrupt_enter();

    uart_tx_dma_isr(&uart_obj[UART12_INDEX]);

    /* leave interrupt */
    rt_interrupt_leave();
}
#endif /* defined(RT_SERIAL_USING_DMA) && defined(BSP_UART12_TX_USING_DMA) && defined(UART12_TX_DMA_IRQHandler) */
#endif /* BSP_USING_UART12 */

#if defined(BSP_USING_UART13)
void UART13_IRQHandler(void)
{
    /* enter interrupt */
    rt_interrupt_enter();

    uart_isr(&(uart_obj[UART13_INDEX].serial));

    /* leave interrupt */
    rt_interrupt_leave();
}
#if defined(RT_SERIAL_USING_DMA) && defined(BSP_UART13_RX_USING_DMA) && defined(UART13_RX_DMA_IRQHandler)
void UART13_RX_DMA_IRQHandler(void)
{
    /* enter interrupt */
    rt_interrupt_enter();

    uart_rx_dma_isr(&uart_obj[UART13_INDEX]);

    /* leave interrupt */
    rt_interrupt_leave();
}
#endif /* defined(RT_SERIAL_USING_DMA) && defined(BSP_UART13_RX_USING_DMA) && defined(UART13_RX_DMA_IRQHandler) */
#if defined(RT_SERIAL_USING_DMA) && defined(BSP_UART13_TX_USING_DMA) && defined(UART13_TX_DMA_IRQHandler)
void UART13_TX_DMA_IRQHandler(void)
{
    /* enter interrupt */
    rt_interrupt_enter();

    uart_tx_dma_isr(&uart_obj[UART13_INDEX]);

    /* leave interrupt */
    rt_interrupt_leave();
}
#endif /* defined(RT_SERIAL_USING_DMA) && defined(BSP_UART13_TX_USING_DMA) && defined(UART13_TX_DMA_IRQHandler) */
#endif /* BSP_USING_UART13 */

#if defined(BSP_USING_UART14)
void UART14_IRQHandler(void)
{
    /* enter interrupt */
    rt_interrupt_enter();

    uart_isr(&(uart_obj[UART14_INDEX].serial));

    /* leave interrupt */
    rt_interrupt_leave();
}
#if defined(RT_SERIAL_USING_DMA) && defined(BSP_UART14_RX_USING_DMA) && defined(UART14_RX_DMA_IRQHandler)
void UART14_RX_DMA_IRQHandler(void)
{
    /* enter interrupt */
    rt_interrupt_enter();

    uart_rx_dma_isr(&uart_obj[UART14_INDEX]);

    /* leave interrupt */
    rt_interrupt_leave();
}
#endif /* defined(RT_SERIAL_USING_DMA) && defined(BSP_UART14_RX_USING_DMA) && defined(UART14_RX_DMA_IRQHandler) */
#if defined(RT_SERIAL_USING_DMA) && defined(BSP_UART14_TX_USING_DMA) && defined(UART14_TX_DMA_IRQHandler)
void UART14_TX_DMA_IRQHandler(void)
{
    /* enter interrupt */
    rt_interrupt_enter();

    uart_tx_dma_isr(&uart_obj[UART14_INDEX]);

    /* leave interrupt */
    rt_interrupt_leave();
}
#endif /* defined(RT_SERIAL_USING_DMA) && defined(BSP_UART14_TX_USING_DMA) && defined(UART14_TX_DMA_IRQHandler) */
#endif /* BSP_USING_UART14 */

#if defined(BSP_USING_UART15)
void UART15_IRQHandler(void)
{
    /* enter interrupt */
    rt_interrupt_enter();

    uart_isr(&(uart_obj[UART15_INDEX].serial));

    /* leave interrupt */
    rt_interrupt_leave();
}
#if defined(RT_SERIAL_USING_DMA) && defined(BSP_UART15_RX_USING_DMA) && defined(UART15_RX_DMA_IRQHandler)
void UART15_RX_DMA_IRQHandler(void)
{
    /* enter interrupt */
    rt_interrupt_enter();

    uart_rx_dma_isr(&uart_obj[UART15_INDEX]);

    /* leave interrupt */
    rt_interrupt_leave();
}
#endif /* defined(RT_SERIAL_USING_DMA) && defined(BSP_UART15_RX_USING_DMA) && defined(UART15_RX_DMA_IRQHandler) */
#if defined(RT_SERIAL_USING_DMA) && defined(BSP_UART15_TX_USING_DMA) && defined(UART15_TX_DMA_IRQHandler)
void UART15_TX_DMA_IRQHandler(void)
{
    /* enter interrupt */
    rt_interrupt_enter();

    uart_tx_dma_isr(&uart_obj[UART15_INDEX]);

    /* leave interrupt */
    rt_interrupt_leave();
}
#endif /* defined(RT_SERIAL_USING_DMA) && defined(BSP_UART15_TX_USING_DMA) && defined(UART15_TX_DMA_IRQHandler) */
#endif /* BSP_USING_UART15 */

static void n32_uart_get_dma_config(void)
{
#ifdef BSP_USING_UART1
    uart_obj[UART1_INDEX].uart_dma_flag = 0;
#ifdef BSP_UART1_RX_USING_DMA
    uart_obj[UART1_INDEX].uart_dma_flag |= RT_DEVICE_FLAG_DMA_RX;
    static struct dma_config uart1_dma_rx = UART1_DMA_RX_CONFIG;
    uart_config[UART1_INDEX].dma_rx = &uart1_dma_rx;
#endif
#ifdef BSP_UART1_TX_USING_DMA
    uart_obj[UART1_INDEX].uart_dma_flag |= RT_DEVICE_FLAG_DMA_TX;
    static struct dma_config uart1_dma_tx = UART1_DMA_TX_CONFIG;
    uart_config[UART1_INDEX].dma_tx = &uart1_dma_tx;
#endif
#endif

#ifdef BSP_USING_UART2
    uart_obj[UART2_INDEX].uart_dma_flag = 0;
#ifdef BSP_UART2_RX_USING_DMA
    uart_obj[UART2_INDEX].uart_dma_flag |= RT_DEVICE_FLAG_DMA_RX;
    static struct dma_config uart2_dma_rx = UART2_DMA_RX_CONFIG;
    uart_config[UART2_INDEX].dma_rx = &uart2_dma_rx;
#endif
#ifdef BSP_UART2_TX_USING_DMA
    uart_obj[UART2_INDEX].uart_dma_flag |= RT_DEVICE_FLAG_DMA_TX;
    static struct dma_config uart2_dma_tx = UART2_DMA_TX_CONFIG;
    uart_config[UART2_INDEX].dma_tx = &uart2_dma_tx;
#endif
#endif

#ifdef BSP_USING_UART3
    uart_obj[UART3_INDEX].uart_dma_flag = 0;
#ifdef BSP_UART3_RX_USING_DMA
    uart_obj[UART3_INDEX].uart_dma_flag |= RT_DEVICE_FLAG_DMA_RX;
    static struct dma_config uart3_dma_rx = UART3_DMA_RX_CONFIG;
    uart_config[UART3_INDEX].dma_rx = &uart3_dma_rx;
#endif
#ifdef BSP_UART3_TX_USING_DMA
    uart_obj[UART3_INDEX].uart_dma_flag |= RT_DEVICE_FLAG_DMA_TX;
    static struct dma_config uart3_dma_tx = UART3_DMA_TX_CONFIG;
    uart_config[UART3_INDEX].dma_tx = &uart3_dma_tx;
#endif
#endif

#ifdef BSP_USING_UART4
    uart_obj[UART4_INDEX].uart_dma_flag = 0;
#ifdef BSP_UART4_RX_USING_DMA
    uart_obj[UART4_INDEX].uart_dma_flag |= RT_DEVICE_FLAG_DMA_RX;
    static struct dma_config uart4_dma_rx = UART4_DMA_RX_CONFIG;
    uart_config[UART4_INDEX].dma_rx = &uart4_dma_rx;
#endif
#ifdef BSP_UART4_TX_USING_DMA
    uart_obj[UART4_INDEX].uart_dma_flag |= RT_DEVICE_FLAG_DMA_TX;
    static struct dma_config uart4_dma_tx = UART4_DMA_TX_CONFIG;
    uart_config[UART4_INDEX].dma_tx = &uart4_dma_tx;
#endif
#endif

#ifdef BSP_USING_UART5
    uart_obj[UART5_INDEX].uart_dma_flag = 0;
#ifdef BSP_UART5_RX_USING_DMA
    uart_obj[UART5_INDEX].uart_dma_flag |= RT_DEVICE_FLAG_DMA_RX;
    static struct dma_config uart5_dma_rx = UART5_DMA_RX_CONFIG;
    uart_config[UART5_INDEX].dma_rx = &uart5_dma_rx;
#endif
#ifdef BSP_UART5_TX_USING_DMA
    uart_obj[UART5_INDEX].uart_dma_flag |= RT_DEVICE_FLAG_DMA_TX;
    static struct dma_config uart5_dma_tx = UART5_DMA_TX_CONFIG;
    uart_config[UART5_INDEX].dma_tx = &uart5_dma_tx;
#endif
#endif

#ifdef BSP_USING_UART6
    uart_obj[UART6_INDEX].uart_dma_flag = 0;
#ifdef BSP_UART6_RX_USING_DMA
    uart_obj[UART6_INDEX].uart_dma_flag |= RT_DEVICE_FLAG_DMA_RX;
    static struct dma_config uart6_dma_rx = UART6_DMA_RX_CONFIG;
    uart_config[UART6_INDEX].dma_rx = &uart6_dma_rx;
#endif
#ifdef BSP_UART6_TX_USING_DMA
    uart_obj[UART6_INDEX].uart_dma_flag |= RT_DEVICE_FLAG_DMA_TX;
    static struct dma_config uart6_dma_tx = UART6_DMA_TX_CONFIG;
    uart_config[UART6_INDEX].dma_tx = &uart6_dma_tx;
#endif
#endif

#ifdef BSP_USING_UART7
    uart_obj[UART7_INDEX].uart_dma_flag = 0;
#ifdef BSP_UART7_RX_USING_DMA
    uart_obj[UART7_INDEX].uart_dma_flag |= RT_DEVICE_FLAG_DMA_RX;
    static struct dma_config uart7_dma_rx = UART7_DMA_RX_CONFIG;
    uart_config[UART7_INDEX].dma_rx = &uart7_dma_rx;
#endif
#ifdef BSP_UART7_TX_USING_DMA
    uart_obj[UART7_INDEX].uart_dma_flag |= RT_DEVICE_FLAG_DMA_TX;
    static struct dma_config uart7_dma_tx = UART7_DMA_TX_CONFIG;
    uart_config[UART7_INDEX].dma_tx = &uart7_dma_tx;
#endif
#endif

#ifdef BSP_USING_UART8
    uart_obj[UART8_INDEX].uart_dma_flag = 0;
#ifdef BSP_UART8_RX_USING_DMA
    uart_obj[UART8_INDEX].uart_dma_flag |= RT_DEVICE_FLAG_DMA_RX;
    static struct dma_config uart8_dma_rx = UART8_DMA_RX_CONFIG;
    uart_config[UART8_INDEX].dma_rx = &uart8_dma_rx;
#endif
#ifdef BSP_UART8_TX_USING_DMA
    uart_obj[UART8_INDEX].uart_dma_flag |= RT_DEVICE_FLAG_DMA_TX;
    static struct dma_config uart8_dma_tx = UART8_DMA_TX_CONFIG;
    uart_config[UART8_INDEX].dma_tx = &uart8_dma_tx;
#endif
#endif

#ifdef BSP_USING_UART9
    uart_obj[UART9_INDEX].uart_dma_flag = 0;
#ifdef BSP_UART9_RX_USING_DMA
    uart_obj[UART9_INDEX].uart_dma_flag |= RT_DEVICE_FLAG_DMA_RX;
    static struct dma_config uart9_dma_rx = UART9_DMA_RX_CONFIG;
    uart_config[UART9_INDEX].dma_rx = &uart9_dma_rx;
#endif
#ifdef BSP_UART9_TX_USING_DMA
    uart_obj[UART9_INDEX].uart_dma_flag |= RT_DEVICE_FLAG_DMA_TX;
    static struct dma_config uart9_dma_tx = UART9_DMA_TX_CONFIG;
    uart_config[UART9_INDEX].dma_tx = &uart9_dma_tx;
#endif
#endif

#ifdef BSP_USING_UART10
    uart_obj[UART10_INDEX].uart_dma_flag = 0;
#ifdef BSP_UART10_RX_USING_DMA
    uart_obj[UART10_INDEX].uart_dma_flag |= RT_DEVICE_FLAG_DMA_RX;
    static struct dma_config uart10_dma_rx = UART10_DMA_RX_CONFIG;
    uart_config[UART10_INDEX].dma_rx = &uart10_dma_rx;
#endif
#ifdef BSP_UART10_TX_USING_DMA
    uart_obj[UART10_INDEX].uart_dma_flag |= RT_DEVICE_FLAG_DMA_TX;
    static struct dma_config uart10_dma_tx = UART10_DMA_TX_CONFIG;
    uart_config[UART10_INDEX].dma_tx = &uart10_dma_tx;
#endif
#endif

#ifdef BSP_USING_UART11
    uart_obj[UART11_INDEX].uart_dma_flag = 0;
#ifdef BSP_UART11_RX_USING_DMA
    uart_obj[UART11_INDEX].uart_dma_flag |= RT_DEVICE_FLAG_DMA_RX;
    static struct dma_config uart11_dma_rx = UART11_DMA_RX_CONFIG;
    uart_config[UART11_INDEX].dma_rx = &uart11_dma_rx;
#endif
#ifdef BSP_UART11_TX_USING_DMA
    uart_obj[UART11_INDEX].uart_dma_flag |= RT_DEVICE_FLAG_DMA_TX;
    static struct dma_config uart11_dma_tx = UART11_DMA_TX_CONFIG;
    uart_config[UART11_INDEX].dma_tx = &uart11_dma_tx;
#endif
#endif

#ifdef BSP_USING_UART12
    uart_obj[UART12_INDEX].uart_dma_flag = 0;
#ifdef BSP_UART12_RX_USING_DMA
    uart_obj[UART12_INDEX].uart_dma_flag |= RT_DEVICE_FLAG_DMA_RX;
    static struct dma_config uart12_dma_rx = UART12_DMA_RX_CONFIG;
    uart_config[UART12_INDEX].dma_rx = &uart12_dma_rx;
#endif
#ifdef BSP_UART12_TX_USING_DMA
    uart_obj[UART12_INDEX].uart_dma_flag |= RT_DEVICE_FLAG_DMA_TX;
    static struct dma_config uart12_dma_tx = UART12_DMA_TX_CONFIG;
    uart_config[UART12_INDEX].dma_tx = &uart12_dma_tx;
#endif
#endif

#ifdef BSP_USING_UART13
    uart_obj[UART13_INDEX].uart_dma_flag = 0;
#ifdef BSP_UART13_RX_USING_DMA
    uart_obj[UART13_INDEX].uart_dma_flag |= RT_DEVICE_FLAG_DMA_RX;
    static struct dma_config uart13_dma_rx = UART13_DMA_RX_CONFIG;
    uart_config[UART13_INDEX].dma_rx = &uart13_dma_rx;
#endif
#ifdef BSP_UART13_TX_USING_DMA
    uart_obj[UART13_INDEX].uart_dma_flag |= RT_DEVICE_FLAG_DMA_TX;
    static struct dma_config uart13_dma_tx = UART13_DMA_TX_CONFIG;
    uart_config[UART13_INDEX].dma_tx = &uart13_dma_tx;
#endif
#endif

#ifdef BSP_USING_UART14
    uart_obj[UART14_INDEX].uart_dma_flag = 0;
#ifdef BSP_UART14_RX_USING_DMA
    uart_obj[UART14_INDEX].uart_dma_flag |= RT_DEVICE_FLAG_DMA_RX;
    static struct dma_config uart14_dma_rx = UART14_DMA_RX_CONFIG;
    uart_config[UART14_INDEX].dma_rx = &uart14_dma_rx;
#endif
#ifdef BSP_UART14_TX_USING_DMA
    uart_obj[UART14_INDEX].uart_dma_flag |= RT_DEVICE_FLAG_DMA_TX;
    static struct dma_config uart14_dma_tx = UART14_DMA_TX_CONFIG;
    uart_config[UART14_INDEX].dma_tx = &uart14_dma_tx;
#endif
#endif

#ifdef BSP_USING_UART15
    uart_obj[UART15_INDEX].uart_dma_flag = 0;
#ifdef BSP_UART15_RX_USING_DMA
    uart_obj[UART15_INDEX].uart_dma_flag |= RT_DEVICE_FLAG_DMA_RX;
    static struct dma_config uart15_dma_rx = UART15_DMA_RX_CONFIG;
    uart_config[UART15_INDEX].dma_rx = &uart15_dma_rx;
#endif
#ifdef BSP_UART15_TX_USING_DMA
    uart_obj[UART15_INDEX].uart_dma_flag |= RT_DEVICE_FLAG_DMA_TX;
    static struct dma_config uart15_dma_tx = UART15_DMA_TX_CONFIG;
    uart_config[UART15_INDEX].dma_tx = &uart15_dma_tx;
#endif
#endif
}



static const struct rt_uart_ops n32_uart_ops =
{
    .configure = n32_configure,
    .control = n32_control,
    .putc = n32_putc,
    .getc = n32_getc,
    .dma_transmit = n32_dma_transmit
};

int rt_hw_usart_init(void)
{
    struct serial_configure config = RT_SERIAL_CONFIG_DEFAULT;
    rt_err_t result = 0;

    n32_uart_get_dma_config();

    for (rt_size_t i = 0; i < sizeof(uart_obj) / sizeof(struct n32_uart); i++)
    {
        /* init UART object */
        uart_obj[i].config        = &uart_config[i];
        uart_obj[i].serial.ops    = &n32_uart_ops;
        uart_obj[i].serial.config = config;

#ifdef RT_SERIAL_USING_DMA
        if (uart_obj[i].uart_dma_flag & RT_DEVICE_FLAG_DMA_TX)
        {
#if defined(SOC_SERIES_N32H7xx)
            /* Configure the UART TX DMA for Transmission process */
            /* Enable DMA clock */
            RCC_EnableAHB1PeriphClk3(uart_obj[i].config->dma_tx->dma_rcc, ENABLE);
            /* Enable DMA MUXclock  */
            RCC_EnableAHB1PeriphClk1(RCC_AHB1_PERIPHEN_M7_DMAMUX1, ENABLE);

            /*  UART TX DMA Channel1 configuration ---------------------------------------------*/
            DMA_ChannelStructInit(&uart_obj[i].dma.TX_DMA_ChInitStr);
            uart_obj[i].dma.TX_DMA_ChInitStr.IntEn              = 0x1U;
            uart_obj[i].dma.TX_DMA_ChInitStr.DstAddr            = (uint32_t)&uart_obj[i].config->Instance->DAT;
            uart_obj[i].dma.TX_DMA_ChInitStr.SrcAddr            = NULL;
            uart_obj[i].dma.TX_DMA_ChInitStr.SrcTfrWidth        = DMA_CH_TRANSFER_WIDTH_8;
            uart_obj[i].dma.TX_DMA_ChInitStr.DstTfrWidth        = DMA_CH_TRANSFER_WIDTH_8;
            uart_obj[i].dma.TX_DMA_ChInitStr.DstAddrCountMode   = DMA_CH_ADDRESS_COUNT_MODE_NO_CHANGE;
            uart_obj[i].dma.TX_DMA_ChInitStr.SrcAddrCountMode   = DMA_CH_ADDRESS_COUNT_MODE_INCREMENT;
            uart_obj[i].dma.TX_DMA_ChInitStr.DstBurstLen        = DMA_CH_BURST_LENGTH_1;
            uart_obj[i].dma.TX_DMA_ChInitStr.SrcBurstLen        = DMA_CH_BURST_LENGTH_1;
            uart_obj[i].dma.TX_DMA_ChInitStr.SrcGatherEn        = 0x0U;
            uart_obj[i].dma.TX_DMA_ChInitStr.DstScatterEn       = 0x0U;
            uart_obj[i].dma.TX_DMA_ChInitStr.TfrTypeFlowCtrl    = DMA_CH_TRANSFER_FLOW_M2P_DMA;
            uart_obj[i].dma.TX_DMA_ChInitStr.BlkTfrSize         = 0U;
            uart_obj[i].dma.TX_DMA_ChInitStr.pLinkListItem      = NULL;
            uart_obj[i].dma.TX_DMA_ChInitStr.SrcGatherInterval  = 0x0U;
            uart_obj[i].dma.TX_DMA_ChInitStr.SrcGatherCount     = 0x0U;
            uart_obj[i].dma.TX_DMA_ChInitStr.DstScatterInterval = 0x0U;
            uart_obj[i].dma.TX_DMA_ChInitStr.DstScatterCount    = 0x0U;
            uart_obj[i].dma.TX_DMA_ChInitStr.TfrType            = DMA_CH_TRANSFER_TYPE_SINGLE_BLOCK;
            uart_obj[i].dma.TX_DMA_ChInitStr.ChannelPriority    = DMA_CH_PRIORITY_7;
            uart_obj[i].dma.TX_DMA_ChInitStr.SrcHandshaking     = DMA_CH_SRC_HANDSHAKING_SOFTWARE;
            uart_obj[i].dma.TX_DMA_ChInitStr.DstHandshaking     = DMA_CH_DST_HANDSHAKING_HARDWARE;
            uart_obj[i].dma.TX_DMA_ChInitStr.DstHsInterface     = uart_obj[i].config->dma_tx->HsInterface;

            /* DMA controller must be enabled before initializing the channel */
            DMA_ControllerCmd(uart_obj[i].config->dma_tx->Instance, ENABLE);

            /* Initialize the specified DMA channel and Whether the specified channel was successfully initialized */
            if (DMA_ChannelInit(uart_obj[i].config->dma_tx->Instance, &uart_obj[i].dma.TX_DMA_ChInitStr, uart_obj[i].config->dma_tx->dma_channel) == 0U)
            {
                /* Configure DMAMUX */
                DMAMUX_SetRequestID(DMAMUX1_ID, uart_obj[i].config->dma_tx->dmamux_channel, uart_obj[i].config->dma_tx->dmamux_request);

                uart_obj[i].dma.DMA_Tx_Init = RT_TRUE;

                /* enable dma irq */
                NVIC_SetPriority(uart_obj[i].config->dma_tx->dma_irq, NVIC_EncodePriority(NVIC_GetPriorityGrouping(), 0, 0));
                NVIC_EnableIRQ(uart_obj[i].config->dma_tx->dma_irq);
            }
            else
            {
                LOG_E("%s TX DMA channel initialization failed!", uart_obj[i].config->name);
                return -RT_ERROR;
            }
#endif
        }

        if (uart_obj[i].uart_dma_flag & RT_DEVICE_FLAG_DMA_RX)
        {
#if defined(SOC_SERIES_N32H7xx)
            /* Calculate the number of blocks */
            if ((uart_obj[i].serial.config.bufsz % DMA_BLOCK_SIZE) != 0)
            {
                uart_obj[i].dma.rx_dma.block_num = uart_obj[i].serial.config.bufsz / DMA_BLOCK_SIZE + 1;

                /* Calculate the remain length */
                uart_obj[i].dma.rx_dma.remain_len = ((uart_obj[i].serial.config.bufsz > DMA_BLOCK_SIZE) ?
                                                     (uart_obj[i].serial.config.bufsz - DMA_BLOCK_SIZE * (uart_obj[i].dma.rx_dma.block_num - 1U)) :
                                                     uart_obj[i].serial.config.bufsz);
            }
            else
            {
                uart_obj[i].dma.rx_dma.block_num = uart_obj[i].serial.config.bufsz / DMA_BLOCK_SIZE;

                /* Calculate the remain length */
                uart_obj[i].dma.rx_dma.remain_len = 0;
            }

            /* Request a LinkList address */
            uart_obj[i].dma.rx_dma.Read_LinkList = (DMA_LinkListItemType *)rt_malloc(sizeof(DMA_LinkListItemType) * uart_obj[i].dma.rx_dma.block_num);
            if (uart_obj[i].dma.rx_dma.Read_LinkList == RT_NULL)
            {
                return -RT_ERROR;
            }

            /* Configure the UART RX DMA for Transmission process */
            /* Enable DMA clock */
            RCC_EnableAHB1PeriphClk3(uart_obj[i].config->dma_rx->dma_rcc, ENABLE);
            /* Enable DMA MUXclock  */
            RCC_EnableAHB1PeriphClk1(RCC_AHB1_PERIPHEN_M7_DMAMUX1, ENABLE);

            /*  UART RX DMA Channel1 configuration ---------------------------------------------*/
            DMA_ChannelStructInit(&uart_obj[i].dma.RX_DMA_ChInitStr);
            uart_obj[i].dma.RX_DMA_ChInitStr.IntEn              = 0x1U;
            uart_obj[i].dma.RX_DMA_ChInitStr.SrcAddr            = (uint32_t)&uart_obj[i].config->Instance->DAT;
            uart_obj[i].dma.RX_DMA_ChInitStr.DstAddr            = NULL;
            uart_obj[i].dma.RX_DMA_ChInitStr.SrcTfrWidth        = DMA_CH_TRANSFER_WIDTH_8;
            uart_obj[i].dma.RX_DMA_ChInitStr.DstTfrWidth        = DMA_CH_TRANSFER_WIDTH_8;
            uart_obj[i].dma.RX_DMA_ChInitStr.DstAddrCountMode   = DMA_CH_ADDRESS_COUNT_MODE_INCREMENT;
            uart_obj[i].dma.RX_DMA_ChInitStr.SrcAddrCountMode   = DMA_CH_ADDRESS_COUNT_MODE_NO_CHANGE;
            uart_obj[i].dma.RX_DMA_ChInitStr.DstBurstLen        = DMA_CH_BURST_LENGTH_1;
            uart_obj[i].dma.RX_DMA_ChInitStr.SrcBurstLen        = DMA_CH_BURST_LENGTH_1;
            uart_obj[i].dma.RX_DMA_ChInitStr.SrcGatherEn        = 0x0U;
            uart_obj[i].dma.RX_DMA_ChInitStr.DstScatterEn       = 0x0U;
            uart_obj[i].dma.RX_DMA_ChInitStr.TfrTypeFlowCtrl    = DMA_CH_TRANSFER_FLOW_P2M_DMA;
            uart_obj[i].dma.RX_DMA_ChInitStr.BlkTfrSize         = DMA_BLOCK_SIZE;
            uart_obj[i].dma.RX_DMA_ChInitStr.pLinkListItem      = uart_obj[i].dma.rx_dma.Read_LinkList;
            uart_obj[i].dma.RX_DMA_ChInitStr.SrcGatherInterval  = 0x0U;
            uart_obj[i].dma.RX_DMA_ChInitStr.SrcGatherCount     = 0x0U;
            uart_obj[i].dma.RX_DMA_ChInitStr.DstScatterInterval = 0x0U;
            uart_obj[i].dma.RX_DMA_ChInitStr.DstScatterCount    = 0x0U;
            uart_obj[i].dma.RX_DMA_ChInitStr.TfrType            = DMA_CH_TRANSFER_TYPE_MULTI_BLOCK_SRCADR_RELOAD_DSTADR_LINKED;
            uart_obj[i].dma.RX_DMA_ChInitStr.ChannelPriority    = DMA_CH_PRIORITY_7;
            uart_obj[i].dma.RX_DMA_ChInitStr.SrcHandshaking     = DMA_CH_SRC_HANDSHAKING_HARDWARE;
            uart_obj[i].dma.RX_DMA_ChInitStr.DstHandshaking     = DMA_CH_DST_HANDSHAKING_SOFTWARE;
            uart_obj[i].dma.RX_DMA_ChInitStr.SrcHsInterface     = uart_obj[i].config->dma_rx->HsInterface;

            /* Set LLI control information */
            for (rt_size_t j = 0; j < uart_obj[i].dma.rx_dma.block_num; j++)
            {
                /* Link List Config */
                uart_obj[i].dma.rx_dma.Read_LinkList[j].IntEn            = 0x1U;
                uart_obj[i].dma.rx_dma.Read_LinkList[j].SrcAddr          = (uint32_t)&uart_obj[i].config->Instance->DAT;
                uart_obj[i].dma.rx_dma.Read_LinkList[j].DstAddr          = NULL;
                uart_obj[i].dma.rx_dma.Read_LinkList[j].SrcTfrWidth      = DMA_CH_TRANSFER_WIDTH_8;
                uart_obj[i].dma.rx_dma.Read_LinkList[j].DstTfrWidth      = DMA_CH_TRANSFER_WIDTH_8;
                uart_obj[i].dma.rx_dma.Read_LinkList[j].DstAddrCountMode = DMA_CH_ADDRESS_COUNT_MODE_INCREMENT;
                uart_obj[i].dma.rx_dma.Read_LinkList[j].SrcAddrCountMode = DMA_CH_ADDRESS_COUNT_MODE_NO_CHANGE;
                uart_obj[i].dma.rx_dma.Read_LinkList[j].DstBurstLen      = DMA_CH_BURST_LENGTH_1;
                uart_obj[i].dma.rx_dma.Read_LinkList[j].SrcBurstLen      = DMA_CH_BURST_LENGTH_1;
                uart_obj[i].dma.rx_dma.Read_LinkList[j].SrcGatherEn      = false;
                uart_obj[i].dma.rx_dma.Read_LinkList[j].DstScatterEn     = false;
                uart_obj[i].dma.rx_dma.Read_LinkList[j].TfrTypeFlowCtrl  = DMA_CH_TRANSFER_FLOW_P2M_DMA;
                uart_obj[i].dma.rx_dma.Read_LinkList[j].BlkTfrSize       = DMA_BLOCK_SIZE;
                uart_obj[i].dma.rx_dma.Read_LinkList[j].DstLinkedListEn  = true;
                uart_obj[i].dma.rx_dma.Read_LinkList[j].SrcLinkedListEn  = false;

                /* The last block, so need to link to first block */
                if ((j + 1U) == uart_obj[i].dma.rx_dma.block_num)
                {
                    uart_obj[i].dma.rx_dma.Read_LinkList[j].pNext = &uart_obj[i].dma.rx_dma.Read_LinkList[0U];
                }
                else
                {
                    uart_obj[i].dma.rx_dma.Read_LinkList[j].pNext = &uart_obj[i].dma.rx_dma.Read_LinkList[j + 1U];
                }

                /* The last block and block size ≠ BLOCK_SIZE */
                if ((j + 1U) == uart_obj[i].dma.rx_dma.block_num && uart_obj[i].dma.rx_dma.remain_len != 0U)
                {
                    uart_obj[i].dma.rx_dma.Read_LinkList[j].BlkTfrSize = uart_obj[i].dma.rx_dma.remain_len;
                }
            }

            /* DMA controller must be enabled before initializing the channel */
            DMA_ControllerCmd(uart_obj[i].config->dma_rx->Instance, ENABLE);
#endif
        }
#endif /* RT_SERIAL_USING_DMA */

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

#endif /* RT_USING_SERIAL */

