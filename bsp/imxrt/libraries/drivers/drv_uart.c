/*
 * Copyright (c) 2006-2018, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2017-10-10     Tanek        the first version
 * 2019-5-10      misonyo      add DMA TX and RX function
 */

#include <rtthread.h>
#ifdef BSP_USING_LPUART

#include "rthw.h"
#include <rtdevice.h>
#include "drv_uart.h"
#include "board.h"
#include "fsl_lpuart.h"
#include "fsl_lpuart_edma.h"
#include "fsl_dmamux.h"

#define LOG_TAG             "drv.usart"
#include <drv_log.h>

#if defined(FSL_SDK_DISABLE_DRIVER_CLOCK_CONTROL) && FSL_SDK_DISABLE_DRIVER_CLOCK_CONTROL
    #error "Please don't define 'FSL_SDK_DISABLE_DRIVER_CLOCK_CONTROL'!"
#endif

enum
{
#ifdef BSP_USING_LPUART1
    LPUART1_INDEX,
#endif
#ifdef BSP_USING_LPUART2
    LPUART2_INDEX,
#endif
#ifdef BSP_USING_LPUART3
    LPUART3_INDEX,
#endif
#ifdef BSP_USING_LPUART4
    LPUART4_INDEX,
#endif
#ifdef BSP_USING_LPUART5
    LPUART5_INDEX,
#endif
#ifdef BSP_USING_LPUART6
    LPUART6_INDEX,
#endif
#ifdef BSP_USING_LPUART7
    LPUART7_INDEX,
#endif
#ifdef BSP_USING_LPUART8
    LPUART8_INDEX,
#endif
};

#if defined(RT_SERIAL_USING_DMA) && defined(BSP_USING_DMA)
struct dma_rx_config
{
    edma_handle_t edma;
    dma_request_source_t request;
    rt_uint8_t channel;
    rt_uint32_t last_index;
};

struct dma_tx_config
{
    edma_handle_t edma;
    lpuart_edma_handle_t uart_edma;
    dma_request_source_t request;
    rt_uint8_t channel;
};

#endif

struct imxrt_uart
{
    char *name;
    LPUART_Type *uart_base;
    IRQn_Type irqn;
#if defined(RT_SERIAL_USING_DMA) && defined(BSP_USING_DMA)
    struct dma_rx_config *dma_rx;
    struct dma_tx_config *dma_tx;
#endif
    rt_uint16_t dma_flag;
    struct rt_serial_device serial;
};

static struct imxrt_uart uarts[] =
{
#ifdef BSP_USING_LPUART1
    {
        .name = "uart1",
        .uart_base = LPUART1,
        .irqn = LPUART1_IRQn,
#if defined(RT_SERIAL_USING_DMA) && defined(BSP_USING_DMA)
        .dma_rx = RT_NULL,
        .dma_tx = RT_NULL,
#endif
        .dma_flag = 0,
    },
#endif
#ifdef BSP_USING_LPUART2
    {
        .name = "uart2",
        .uart_base = LPUART2,
        .irqn = LPUART2_IRQn,
#if defined(RT_SERIAL_USING_DMA) && defined(BSP_USING_DMA)
        .dma_rx = RT_NULL,
        .dma_tx = RT_NULL,
#endif
        .dma_flag = 0,
    },
#endif
#ifdef BSP_USING_LPUART3
    {
        .name = "uart3",
        .uart_base = LPUART3,
        .irqn = LPUART3_IRQn,
#if defined(RT_SERIAL_USING_DMA) && defined(BSP_USING_DMA)
        .dma_rx = RT_NULL,
        .dma_tx = RT_NULL,
#endif
        .dma_flag = 0,
    },
#endif
#ifdef BSP_USING_LPUART4
    {
        .name = "uart4",
        .uart_base = LPUART4,
        .irqn = LPUART4_IRQn,
#if defined(RT_SERIAL_USING_DMA) && defined(BSP_USING_DMA)
        .dma_rx = RT_NULL,
        .dma_tx = RT_NULL,
#endif
        .dma_flag = 0,
    },
#endif
#ifdef BSP_USING_LPUART5
    {
        .name = "uart5",
        .uart_base = LPUART5,
        .irqn = LPUART5_IRQn,
#if defined(RT_SERIAL_USING_DMA) && defined(BSP_USING_DMA)
        .dma_rx = RT_NULL,
        .dma_tx = RT_NULL,
#endif
        .dma_flag = 0,
    },
#endif
#ifdef BSP_USING_LPUART6
    {
        .name = "uart6",
        .uart_base = LPUART6,
        .irqn = LPUART6_IRQn,
#if defined(RT_SERIAL_USING_DMA) && defined(BSP_USING_DMA)
        .dma_rx = RT_NULL,
        .dma_tx = RT_NULL,
#endif
        .dma_flag = 0,
    },
#endif
#ifdef BSP_USING_LPUART7
    {
        .name = "uart7",
        .uart_base = LPUART7,
        .irqn = LPUART7_IRQn,
#if defined(RT_SERIAL_USING_DMA) && defined(BSP_USING_DMA)
        .dma_rx = RT_NULL,
        .dma_tx = RT_NULL,
#endif
        .dma_flag = 0,
    },
#endif
#ifdef BSP_USING_LPUART8
    {
        .name = "uart8",
        .uart_base = LPUART8,
        .irqn = LPUART8_IRQn,
#if defined(RT_SERIAL_USING_DMA) && defined(BSP_USING_DMA)
        .dma_rx = RT_NULL,
        .dma_tx = RT_NULL,
#endif
        .dma_flag = 0,
    },
#endif
};

static void uart_get_dma_config(void)
{
#ifdef BSP_LPUART1_RX_USING_DMA
    static struct dma_rx_config uart1_dma_rx = {.request = kDmaRequestMuxLPUART1Rx, .channel = BSP_LPUART1_RX_DMA_CHANNEL, .last_index = 0};
    uarts[LPUART1_INDEX].dma_rx = &uart1_dma_rx;
    uarts[LPUART1_INDEX].dma_flag |= RT_DEVICE_FLAG_DMA_RX;
#endif
#ifdef BSP_LPUART1_TX_USING_DMA
    static struct dma_tx_config uart1_dma_tx = {.request = kDmaRequestMuxLPUART1Tx, .channel = BSP_LPUART1_TX_DMA_CHANNEL};
    uarts[LPUART1_INDEX].dma_tx = &uart1_dma_tx;
    uarts[LPUART1_INDEX].dma_flag |= RT_DEVICE_FLAG_DMA_TX;
#endif

#ifdef BSP_LPUART2_RX_USING_DMA
    static struct dma_rx_config uart2_dma_rx = {.request = kDmaRequestMuxLPUART2Rx, .channel = BSP_LPUART2_RX_DMA_CHANNEL, .last_index = 0};
    uarts[LPUART2_INDEX].dma_rx = &uart2_dma_rx;
    uarts[LPUART2_INDEX].dma_flag |= RT_DEVICE_FLAG_DMA_RX;
#endif
#ifdef BSP_LPUART2_TX_USING_DMA
    static struct dma_tx_config uart2_dma_tx = {.request = kDmaRequestMuxLPUART4Tx, .channel = BSP_LPUART2_TX_DMA_CHANNEL};
    uarts[LPUART2_INDEX].dma_tx = &uart2_dma_tx;
    uarts[LPUART2_INDEX].dma_flag |= RT_DEVICE_FLAG_DMA_TX;
#endif

#ifdef BSP_LPUART3_RX_USING_DMA
    static struct dma_rx_config uart3_dma_rx = {.request = kDmaRequestMuxLPUART3Rx, .channel = BSP_LPUART3_RX_DMA_CHANNEL, .last_index = 0};
    uarts[LPUART3_INDEX].dma_rx = &uart3_dma_rx;
    uarts[LPUART3_INDEX].dma_flag |= RT_DEVICE_FLAG_DMA_RX;
#endif
#ifdef BSP_LPUART3_TX_USING_DMA
    static struct dma_tx_config uart3_dma_tx = {.request = kDmaRequestMuxLPUART3Tx, .channel = BSP_LPUART3_TX_DMA_CHANNEL};
    uarts[LPUART3_INDEX].dma_tx = &uart3_dma_tx;
    uarts[LPUART3_INDEX].dma_flag |= RT_DEVICE_FLAG_DMA_TX;
#endif

#ifdef BSP_LPUART4_RX_USING_DMA
    static struct dma_rx_config uart4_dma_rx = {.request = kDmaRequestMuxLPUART4Rx, .channel = BSP_LPUART4_RX_DMA_CHANNEL, .last_index = 0};
    uarts[LPUART4_INDEX].dma_rx = &uart4_dma_rx;
    uarts[LPUART4_INDEX].dma_flag |= RT_DEVICE_FLAG_DMA_RX;
#endif
#ifdef BSP_LPUART4_TX_USING_DMA
    static struct dma_tx_config uart4_dma_tx = {.request = kDmaRequestMuxLPUART4Tx, .channel = BSP_LPUART4_TX_DMA_CHANNEL};
    uarts[LPUART4_INDEX].dma_tx = &uart4_dma_tx;
    uarts[LPUART4_INDEX].dma_flag |= RT_DEVICE_FLAG_DMA_TX;
#endif

#ifdef BSP_LPUART5_RX_USING_DMA
    static struct dma_rx_config uart5_dma_rx = {.request = kDmaRequestMuxLPUART5Rx, .channel = BSP_LPUART5_RX_DMA_CHANNEL, .last_index = 0};
    uarts[LPUART5_INDEX].dma_rx = &uart5_dma_rx;
    uarts[LPUART5_INDEX].dma_flag |= RT_DEVICE_FLAG_DMA_RX;
#endif
#ifdef BSP_LPUART5_TX_USING_DMA
    static struct dma_tx_config uart5_dma_tx = {.request = kDmaRequestMuxLPUART5Tx, .channel = BSP_LPUART5_TX_DMA_CHANNEL};
    uarts[LPUART5_INDEX].dma_tx = &uart5_dma_tx;
    uarts[LPUART5_INDEX].dma_flag |= RT_DEVICE_FLAG_DMA_TX;
#endif

#ifdef BSP_LPUART6_RX_USING_DMA
    static struct dma_rx_config uart6_dma_rx = {.request = kDmaRequestMuxLPUART6Rx, .channel = BSP_LPUART6_RX_DMA_CHANNEL, .last_index = 0};
    uarts[LPUART6_INDEX].dma_rx = &uart6_dma_rx;
    uarts[LPUART6_INDEX].dma_flag |= RT_DEVICE_FLAG_DMA_RX;
#endif
#ifdef BSP_LPUART6_TX_USING_DMA
    static struct dma_tx_config uart6_dma_tx = {.request = kDmaRequestMuxLPUART6Tx, .channel = BSP_LPUART6_TX_DMA_CHANNEL};
    uarts[LPUART6_INDEX].dma_tx = &uart6_dma_tx;
    uarts[LPUART6_INDEX].dma_flag |= RT_DEVICE_FLAG_DMA_TX;
#endif

#ifdef BSP_LPUART7_RX_USING_DMA
    static struct dma_rx_config uart7_dma_rx = {.request = kDmaRequestMuxLPUART7Rx, .channel = BSP_LPUART7_RX_DMA_CHANNEL, .last_index = 0};
    uarts[LPUART7_INDEX].dma_rx = &uart7_dma_rx;
    uarts[LPUART7_INDEX].dma_flag |= RT_DEVICE_FLAG_DMA_RX;
#endif
#ifdef BSP_LPUART7_TX_USING_DMA
    static struct dma_tx_config uart7_dma_tx = {.request = kDmaRequestMuxLPUART7Tx, .channel = BSP_LPUART7_TX_DMA_CHANNEL};
    uarts[LPUART7_INDEX].dma_tx = &uart7_dma_tx;
    uarts[LPUART7_INDEX].dma_flag |= RT_DEVICE_FLAG_DMA_TX;
#endif

#ifdef BSP_LPUART8_RX_USING_DMA
    static struct dma_rx_config uart8_dma_rx = {.request = kDmaRequestMuxLPUART8Rx, .channel = BSP_LPUART8_RX_DMA_CHANNEL, .last_index = 0};
    uarts[LPUART8_INDEX].dma_rx = &uart8_dma_rx;
    uarts[LPUART8_INDEX].dma_flag |= RT_DEVICE_FLAG_DMA_RX;
#endif
#ifdef BSP_LPUART8_TX_USING_DMA
    static struct dma_tx_config uart8_dma_tx = {.request = kDmaRequestMuxLPUART8Tx, .channel = BSP_LPUART8_TX_DMA_CHANNEL};
    uarts[LPUART8_INDEX].dma_tx = &uart8_dma_tx;
    uarts[LPUART8_INDEX].dma_flag |= RT_DEVICE_FLAG_DMA_TX;
#endif
}

static void uart_isr(struct imxrt_uart *uart);

#if defined(BSP_USING_LPUART1)

void LPUART1_IRQHandler(void)
{
    rt_interrupt_enter();

    uart_isr(&uarts[LPUART1_INDEX]);

    rt_interrupt_leave();
}

#endif /* BSP_USING_LPUART1 */

#if defined(BSP_USING_LPUART2)
struct rt_serial_device serial2;

void LPUART2_IRQHandler(void)
{
    rt_interrupt_enter();

    uart_isr(&uarts[LPUART2_INDEX]);

    rt_interrupt_leave();
}

#endif /* BSP_USING_LPUART2 */

#if defined(BSP_USING_LPUART3)
struct rt_serial_device serial3;

void LPUART3_IRQHandler(void)
{
    rt_interrupt_enter();

    uart_isr(&uarts[LPUART3_INDEX]);

    rt_interrupt_leave();
}

#endif /* BSP_USING_LPUART3 */

#if defined(BSP_USING_LPUART4)

void LPUART4_IRQHandler(void)
{
    rt_interrupt_enter();

    uart_isr(&uarts[LPUART4_INDEX]);

    rt_interrupt_leave();
}

#endif /* BSP_USING_LPUART4 */

#if defined(BSP_USING_LPUART5)
struct rt_serial_device serial5;

void LPUART5_IRQHandler(void)
{
    rt_interrupt_enter();

    uart_isr(&uarts[LPUART5_INDEX]);

    rt_interrupt_leave();
}

#endif /* BSP_USING_LPUART5 */

#if defined(BSP_USING_LPUART6)
struct rt_serial_device serial6;

void LPUART6_IRQHandler(void)
{
    rt_interrupt_enter();

    uart_isr(&uarts[LPUART6_INDEX]);

    rt_interrupt_leave();
}

#endif /* BSP_USING_LPUART6 */

#if defined(BSP_USING_LPUART7)
struct rt_serial_device serial7;

void LPUART7_IRQHandler(void)
{
    rt_interrupt_enter();

    uart_isr(&uarts[LPUART7_INDEX]);

    rt_interrupt_leave();
}

#endif /* BSP_USING_LPUART7 */

#if defined(BSP_USING_LPUART8)
struct rt_serial_device serial8;

void LPUART8_IRQHandler(void)
{
    rt_interrupt_enter();

    uart_isr(&uarts[LPUART8_INDEX]);

    rt_interrupt_leave();
}

#endif /* BSP_USING_LPUART8 */

static void uart_isr(struct imxrt_uart *uart)
{
    RT_ASSERT(uart != RT_NULL);
#if defined(RT_SERIAL_USING_DMA) && defined(BSP_USING_DMA)
    rt_size_t total_index, recv_len;
    rt_base_t level;
#endif

    /* kLPUART_RxDataRegFullFlag can only cleared or set by hardware */
    if (LPUART_GetStatusFlags(uart->uart_base) & kLPUART_RxDataRegFullFlag)
    {
        rt_hw_serial_isr(&uart->serial, RT_SERIAL_EVENT_RX_IND);
    }

    if (LPUART_GetStatusFlags(uart->uart_base) & kLPUART_RxOverrunFlag)
    {
        /* Clear overrun flag, otherwise the RX does not work. */
        LPUART_ClearStatusFlags(uart->uart_base, kLPUART_RxOverrunFlag);
    }

#if defined(RT_SERIAL_USING_DMA) && defined(BSP_USING_DMA)
    if ((LPUART_GetStatusFlags(uart->uart_base) & kLPUART_IdleLineFlag) && (uart->dma_rx != RT_NULL))
    {
        LPUART_ClearStatusFlags(uart->uart_base, kLPUART_IdleLineFlag);
        level = rt_hw_interrupt_disable();

        total_index = uart->serial.config.bufsz - EDMA_GetRemainingMajorLoopCount(DMA0, uart->dma_rx->channel);
        if (total_index > uart->dma_rx->last_index)
        {
            recv_len = total_index - uart->dma_rx->last_index;
        }
        else
        {
            recv_len = total_index + (uart->serial.config.bufsz - uart->dma_rx->last_index);
        }

        if ((recv_len > 0) && (recv_len < uart->serial.config.bufsz))
        {
            uart->dma_rx->last_index = total_index;
            rt_hw_interrupt_enable(level);

            rt_hw_serial_isr(&uart->serial, RT_SERIAL_EVENT_RX_DMADONE | (recv_len << 8));
        }
        else
        {
            rt_hw_interrupt_enable(level);
        }
    }
#endif
}

#if defined(RT_SERIAL_USING_DMA) && defined(BSP_USING_DMA)
void edma_rx_callback(struct _edma_handle *handle, void *userData, bool transferDone, uint32_t tcds)
{
    rt_size_t total_index, recv_len;
    rt_base_t level;
    struct imxrt_uart *uart = (struct imxrt_uart *)userData;
    RT_ASSERT(uart != RT_NULL);

    if (transferDone)
    {
        level = rt_hw_interrupt_disable();

        if ((EDMA_GetChannelStatusFlags(DMA0, uart->dma_rx->channel) & kEDMA_DoneFlag) != 0U)
        {
            /* clear full interrupt */
            EDMA_ClearChannelStatusFlags(DMA0, uart->dma_rx->channel,kEDMA_DoneFlag);

            recv_len = uart->serial.config.bufsz - uart->dma_rx->last_index;
            uart->dma_rx->last_index = 0;
        }
        else    
        {
            /* clear half interrupt */
            EDMA_ClearChannelStatusFlags(DMA0, uart->dma_rx->channel,kEDMA_InterruptFlag);

            total_index = uart->serial.config.bufsz - EDMA_GetRemainingMajorLoopCount(DMA0, uart->dma_rx->channel);
            if (total_index > uart->dma_rx->last_index)
            {
                recv_len = total_index - uart->dma_rx->last_index;
            }
            else
            {
                recv_len = total_index + (uart->serial.config.bufsz - uart->dma_rx->last_index);
            }
            uart->dma_rx->last_index = total_index;
        }

        rt_hw_interrupt_enable(level);

        if (recv_len)
        {
            rt_hw_serial_isr(&uart->serial, RT_SERIAL_EVENT_RX_DMADONE | (recv_len << 8));
        }
    }
}

void edma_tx_callback(LPUART_Type *base, lpuart_edma_handle_t *handle, status_t status, void *userData)
{
    struct imxrt_uart *uart = (struct imxrt_uart *)userData;
    RT_ASSERT(uart != RT_NULL);

    if (kStatus_LPUART_TxIdle == status)
    {
        rt_hw_serial_isr(&uart->serial, RT_SERIAL_EVENT_TX_DMADONE);
    }
}

static void imxrt_dma_rx_config(struct imxrt_uart *uart)
{
    RT_ASSERT(uart != RT_NULL);

    edma_transfer_config_t xferConfig;
    struct rt_serial_rx_fifo *rx_fifo;

    DMAMUX_SetSource(DMAMUX, uart->dma_rx->channel, uart->dma_rx->request);
    DMAMUX_EnableChannel(DMAMUX, uart->dma_rx->channel);
    EDMA_CreateHandle(&uart->dma_rx->edma, DMA0, uart->dma_rx->channel);
    EDMA_SetCallback(&uart->dma_rx->edma, edma_rx_callback, uart);

    rx_fifo = (struct rt_serial_rx_fifo *)uart->serial.serial_rx;

    EDMA_PrepareTransfer(&xferConfig,
                         (void *)LPUART_GetDataRegisterAddress(uart->uart_base),
                         sizeof(uint8_t),
                         rx_fifo->buffer,
                         sizeof(uint8_t),
                         sizeof(uint8_t),
                         uart->serial.config.bufsz,
                         kEDMA_PeripheralToMemory);

    EDMA_SubmitTransfer(&uart->dma_rx->edma, &xferConfig);
    EDMA_EnableChannelInterrupts(DMA0, uart->dma_rx->channel, kEDMA_MajorInterruptEnable | kEDMA_HalfInterruptEnable);
    EDMA_EnableAutoStopRequest(DMA0, uart->dma_rx->channel, false);
    /* complement to adjust final destination address */
    uart->dma_rx->edma.base->TCD[uart->dma_rx->channel].DLAST_SGA = -(uart->serial.config.bufsz);
    EDMA_StartTransfer(&uart->dma_rx->edma);
    LPUART_EnableRxDMA(uart->uart_base, true);

    LPUART_EnableInterrupts(uart->uart_base, kLPUART_IdleLineInterruptEnable);
    NVIC_SetPriority(uart->irqn, NVIC_EncodePriority(NVIC_GetPriorityGrouping(), 4, 0));
    EnableIRQ(uart->irqn);

    LOG_D("%s dma rx config done\n", uart->name);
}

static void imxrt_dma_tx_config(struct imxrt_uart *uart)
{
    RT_ASSERT(uart != RT_NULL);

    DMAMUX_SetSource(DMAMUX, uart->dma_tx->channel, uart->dma_tx->request);
    DMAMUX_EnableChannel(DMAMUX, uart->dma_tx->channel);
    EDMA_CreateHandle(&uart->dma_tx->edma, DMA0, uart->dma_tx->channel);

    LPUART_TransferCreateHandleEDMA(uart->uart_base,
                                    &uart->dma_tx->uart_edma,
                                    edma_tx_callback,
                                    uart,
                                    &uart->dma_tx->edma,
                                    RT_NULL);

    LOG_D("%s dma tx config done\n", uart->name);
}

#endif

uint32_t GetUartSrcFreq(void)
{
    uint32_t freq;

    /* To make it simple, we assume default PLL and divider settings, and the only variable
       from application is use PLL3 source or OSC source */
    if (CLOCK_GetMux(kCLOCK_UartMux) == 0) /* PLL3 div6 80M */
    {
        freq = (CLOCK_GetPllFreq(kCLOCK_PllUsb1) / 6U) / (CLOCK_GetDiv(kCLOCK_UartDiv) + 1U);
    }
    else
    {
        freq = CLOCK_GetOscFreq() / (CLOCK_GetDiv(kCLOCK_UartDiv) + 1U);
    }

    return freq;
}

static rt_err_t imxrt_configure(struct rt_serial_device *serial, struct serial_configure *cfg)
{
    struct imxrt_uart *uart;
    lpuart_config_t config;

    RT_ASSERT(serial != RT_NULL);
    RT_ASSERT(cfg != RT_NULL);

    uart = rt_container_of(serial, struct imxrt_uart, serial);

    LPUART_GetDefaultConfig(&config);
    config.baudRate_Bps = cfg->baud_rate;

    switch (cfg->data_bits)
    {
    case DATA_BITS_7:
        config.dataBitsCount = kLPUART_SevenDataBits;
        break;

    default:
        config.dataBitsCount = kLPUART_EightDataBits;
        break;
    }

    switch (cfg->stop_bits)
    {
    case STOP_BITS_2:
        config.stopBitCount = kLPUART_TwoStopBit;
        break;
    default:
        config.stopBitCount = kLPUART_OneStopBit;
        break;
    }

    switch (cfg->parity)
    {
    case PARITY_ODD:
        config.parityMode = kLPUART_ParityOdd;
        break;
    case PARITY_EVEN:
        config.parityMode = kLPUART_ParityEven;
        break;
    default:
        config.parityMode = kLPUART_ParityDisabled;
        break;
    }

    config.enableTx = true;
    config.enableRx = true;

    LPUART_Init(uart->uart_base, &config, GetUartSrcFreq());

    return RT_EOK;
}

static rt_err_t imxrt_control(struct rt_serial_device *serial, int cmd, void *arg)
{
    struct imxrt_uart *uart;

    RT_ASSERT(serial != RT_NULL);
    uart = rt_container_of(serial, struct imxrt_uart, serial);

#if defined(RT_SERIAL_USING_DMA) && defined(BSP_USING_DMA)
    rt_ubase_t ctrl_arg = (rt_ubase_t)arg;
#endif

    switch (cmd)
    {
    case RT_DEVICE_CTRL_CLR_INT:
        DisableIRQ(uart->irqn);
        break;

    case RT_DEVICE_CTRL_SET_INT:
        LPUART_EnableInterrupts(uart->uart_base, kLPUART_RxDataRegFullInterruptEnable);
        NVIC_SetPriority(uart->irqn, NVIC_EncodePriority(NVIC_GetPriorityGrouping(), 4, 0));
        EnableIRQ(uart->irqn);
        break;

#if defined(RT_SERIAL_USING_DMA) && defined(BSP_USING_DMA)
    case RT_DEVICE_CTRL_CONFIG:

        if (RT_DEVICE_FLAG_DMA_RX == ctrl_arg)
        {
            imxrt_dma_rx_config(uart);
        }
        else if (RT_DEVICE_FLAG_DMA_TX == ctrl_arg)
        {
            imxrt_dma_tx_config(uart);
        }
        break;
#endif
    }

    return RT_EOK;
}

static int imxrt_putc(struct rt_serial_device *serial, char ch)
{
    struct imxrt_uart *uart;

    RT_ASSERT(serial != RT_NULL);
    uart = rt_container_of(serial, struct imxrt_uart, serial);

    LPUART_WriteByte(uart->uart_base, ch);
    while (!(LPUART_GetStatusFlags(uart->uart_base) & kLPUART_TxDataRegEmptyFlag));

    return 1;
}

static int imxrt_getc(struct rt_serial_device *serial)
{
    int ch;
    struct imxrt_uart *uart;

    RT_ASSERT(serial != RT_NULL);
    uart = rt_container_of(serial, struct imxrt_uart, serial);

    ch = -1;
    if (LPUART_GetStatusFlags(uart->uart_base) & kLPUART_RxDataRegFullFlag)
    {
        ch = LPUART_ReadByte(uart->uart_base);
    }

    return ch;
}

#if defined(RT_SERIAL_USING_DMA) && defined(BSP_USING_DMA)
rt_size_t dma_tx_xfer(struct rt_serial_device *serial, rt_uint8_t *buf, rt_size_t size, int direction)
{
    struct imxrt_uart *uart;
    lpuart_transfer_t xfer;
    rt_size_t xfer_size = 0;

    RT_ASSERT(serial != RT_NULL);
    uart = rt_container_of(serial, struct imxrt_uart, serial);

    if (0 != size)
    {
        if (RT_SERIAL_DMA_TX == direction)
        {
            xfer.data = buf;
            xfer.dataSize = size;
            if (LPUART_SendEDMA(uart->uart_base, &uart->dma_tx->uart_edma, &xfer) == kStatus_Success)
            {
                xfer_size = size;
            }
        }
    }

    return xfer_size;
}
#endif

static const struct rt_uart_ops imxrt_uart_ops =
{
    imxrt_configure,
    imxrt_control,
    imxrt_putc,
    imxrt_getc,
#if defined(RT_SERIAL_USING_DMA) && defined(BSP_USING_DMA)
    dma_tx_xfer
#else
    RT_NULL
#endif
};

int rt_hw_uart_init(void)
{
    int i;
    rt_uint32_t flag;
    rt_err_t ret = RT_EOK;
    struct serial_configure config = RT_SERIAL_CONFIG_DEFAULT;

    flag = RT_DEVICE_FLAG_RDWR | RT_DEVICE_FLAG_INT_RX;

    uart_get_dma_config();

    for (i = 0; i < sizeof(uarts) / sizeof(uarts[0]); i++)
    {
        uarts[i].serial.ops    = &imxrt_uart_ops;
        uarts[i].serial.config = config;

        ret = rt_hw_serial_register(&uarts[i].serial, uarts[i].name, flag | uarts[i].dma_flag, NULL);
    }

    return ret;
}
INIT_BOARD_EXPORT(rt_hw_uart_init);

#endif /* BSP_USING_LPUART */
