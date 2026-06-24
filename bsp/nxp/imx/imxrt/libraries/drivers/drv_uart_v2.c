/*
 * Copyright (c) 2006-2024, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2017-10-10     Tanek        the first version
 * 2019-5-10      misonyo      add DMA TX and RX function
 * 2026-4-29      Ran          add RT1180 support
 * 2026-6-4       shannon      add LPUART10/12, Serial V2, DMA (V2)
 * 2026-6-16      shannon      extract Serial V2 as standalone driver
 */
#include <rtthread.h>
#ifdef RT_USING_SERIAL_V2
#ifdef BSP_USING_LPUART

#include "rthw.h"
#include <rtdevice.h>
#include "drv_uart.h"
#include "board.h"
#include "fsl_lpuart.h"
#include "fsl_lpuart_edma.h"
#ifndef SOC_IMXRT1180_SERIES
#include "fsl_dmamux.h"
#endif

#define LOG_TAG "drv.usart.v2"
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
#ifdef BSP_USING_LPUART10
    LPUART10_INDEX,
#endif
#ifdef BSP_USING_LPUART12
    LPUART12_INDEX,
#endif
};

#if defined(RT_SERIAL_USING_DMA) && defined(BSP_USING_DMA)
struct dma_rx_config
{
    edma_handle_t edma;
    dma_request_source_t request;
    rt_uint8_t channel;
    rt_uint32_t last_index;
    EDMA_Type *edma_base;
};

struct dma_tx_config
{
    edma_handle_t edma;
    lpuart_edma_handle_t uart_edma;
    dma_request_source_t request;
    rt_uint8_t channel;
    EDMA_Type *edma_base;
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

static struct imxrt_uart uarts[] = {
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
#ifdef BSP_USING_LPUART10
    {
        .name = "uart10",
        .uart_base = LPUART10,
        .irqn = LPUART10_IRQn,
#if defined(RT_SERIAL_USING_DMA) && defined(BSP_USING_DMA)
        .dma_rx = RT_NULL,
        .dma_tx = RT_NULL,
#endif
        .dma_flag = 0,
    },
#endif
#ifdef BSP_USING_LPUART12
    {
        .name = "uart12",
        .uart_base = LPUART12,
        .irqn = LPUART12_IRQn,
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
#if defined(RT_SERIAL_USING_DMA) && defined(BSP_USING_DMA)
#ifdef SOC_IMXRT1180_SERIES
#ifdef BSP_LPUART1_RX_USING_DMA
    static struct dma_rx_config uart1_dma_rx = { .request = kDma3RequestMuxLPUART1Rx, .channel = BSP_LPUART1_RX_DMA_CHANNEL, .last_index = 0, .edma_base = (EDMA_Type *)DMA3 };
    uarts[LPUART1_INDEX].dma_rx = &uart1_dma_rx;
    uarts[LPUART1_INDEX].dma_flag |= RT_DEVICE_FLAG_DMA_RX;
#endif
#ifdef BSP_LPUART1_TX_USING_DMA
    static struct dma_tx_config uart1_dma_tx = { .request = kDma3RequestMuxLPUART1Tx, .channel = BSP_LPUART1_TX_DMA_CHANNEL, .edma_base = (EDMA_Type *)DMA3 };
    uarts[LPUART1_INDEX].dma_tx = &uart1_dma_tx;
    uarts[LPUART1_INDEX].dma_flag |= RT_DEVICE_FLAG_DMA_TX;
#endif
#endif

#ifdef BSP_LPUART10_RX_USING_DMA
    static struct dma_rx_config uart10_dma_rx = { .request = kDma4RequestMuxLPUART10Rx, .channel = BSP_LPUART10_RX_DMA_CHANNEL, .last_index = 0, .edma_base = (EDMA_Type *)DMA4 };
    uarts[LPUART10_INDEX].dma_rx = &uart10_dma_rx;
    uarts[LPUART10_INDEX].dma_flag |= RT_DEVICE_FLAG_DMA_RX;
#endif
#ifdef BSP_LPUART10_TX_USING_DMA
    static struct dma_tx_config uart10_dma_tx = { .request = kDma4RequestMuxLPUART10Tx, .channel = BSP_LPUART10_TX_DMA_CHANNEL, .edma_base = (EDMA_Type *)DMA4 };
    uarts[LPUART10_INDEX].dma_tx = &uart10_dma_tx;
    uarts[LPUART10_INDEX].dma_flag |= RT_DEVICE_FLAG_DMA_TX;
#endif

#ifdef BSP_LPUART12_RX_USING_DMA
    static struct dma_rx_config uart12_dma_rx = { .request = kDma3RequestMuxLPUART12Rx, .channel = BSP_LPUART12_RX_DMA_CHANNEL, .last_index = 0, .edma_base = (EDMA_Type *)DMA3 };
    uarts[LPUART12_INDEX].dma_rx = &uart12_dma_rx;
    uarts[LPUART12_INDEX].dma_flag |= RT_DEVICE_FLAG_DMA_RX;
#endif
#ifdef BSP_LPUART12_TX_USING_DMA
    static struct dma_tx_config uart12_dma_tx = { .request = kDma3RequestMuxLPUART12Tx, .channel = BSP_LPUART12_TX_DMA_CHANNEL, .edma_base = (EDMA_Type *)DMA3 };
    uarts[LPUART12_INDEX].dma_tx = &uart12_dma_tx;
    uarts[LPUART12_INDEX].dma_flag |= RT_DEVICE_FLAG_DMA_TX;
#endif
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
#endif

#if defined(BSP_USING_LPUART2)
void LPUART2_IRQHandler(void)
{
    rt_interrupt_enter();
    uart_isr(&uarts[LPUART2_INDEX]);
    rt_interrupt_leave();
}
#endif

#if defined(BSP_USING_LPUART3)
void LPUART3_IRQHandler(void)
{
    rt_interrupt_enter();
    uart_isr(&uarts[LPUART3_INDEX]);
    rt_interrupt_leave();
}
#endif

#if defined(BSP_USING_LPUART4)
void LPUART4_IRQHandler(void)
{
    rt_interrupt_enter();
    uart_isr(&uarts[LPUART4_INDEX]);
    rt_interrupt_leave();
}
#endif

#if defined(BSP_USING_LPUART5)
void LPUART5_IRQHandler(void)
{
    rt_interrupt_enter();
    uart_isr(&uarts[LPUART5_INDEX]);
    rt_interrupt_leave();
}
#endif

#if defined(BSP_USING_LPUART6)
void LPUART6_IRQHandler(void)
{
    rt_interrupt_enter();
    uart_isr(&uarts[LPUART6_INDEX]);
    rt_interrupt_leave();
}
#endif

#if defined(BSP_USING_LPUART7)
void LPUART7_IRQHandler(void)
{
    rt_interrupt_enter();
    uart_isr(&uarts[LPUART7_INDEX]);
    rt_interrupt_leave();
}
#endif

#if defined(BSP_USING_LPUART8)
void LPUART8_IRQHandler(void)
{
    rt_interrupt_enter();
    uart_isr(&uarts[LPUART8_INDEX]);
    rt_interrupt_leave();
}
#endif

#if defined(BSP_USING_LPUART10)
void LPUART10_IRQHandler(void)
{
    rt_interrupt_enter();
    uart_isr(&uarts[LPUART10_INDEX]);
    rt_interrupt_leave();
}
#endif

#if defined(BSP_USING_LPUART12)
void LPUART12_IRQHandler(void)
{
    rt_interrupt_enter();
    uart_isr(&uarts[LPUART12_INDEX]);
    rt_interrupt_leave();
}
#endif

static void uart_isr(struct imxrt_uart *uart)
{
    RT_ASSERT(uart != RT_NULL);

    if (LPUART_GetStatusFlags(uart->uart_base) & kLPUART_RxDataRegFullFlag)
    {
        uint8_t ch = LPUART_ReadByte(uart->uart_base);
        rt_hw_serial_control_isr(&uart->serial, RT_HW_SERIAL_CTRL_PUTC, &ch);
        rt_hw_serial_isr(&uart->serial, RT_SERIAL_EVENT_RX_IND);
    }

    if (LPUART_GetStatusFlags(uart->uart_base) & kLPUART_RxOverrunFlag)
    {
        LPUART_ClearStatusFlags(uart->uart_base, kLPUART_RxOverrunFlag);
    }

    if (LPUART_GetStatusFlags(uart->uart_base) & kLPUART_TxDataRegEmptyFlag)
    {
        LPUART_DisableInterrupts(uart->uart_base, kLPUART_TxDataRegEmptyInterruptEnable);
        rt_hw_serial_isr(&uart->serial, RT_SERIAL_EVENT_TX_DONE);
    }

#if defined(RT_SERIAL_USING_DMA) && defined(BSP_USING_DMA)
    if ((LPUART_GetStatusFlags(uart->uart_base) & kLPUART_IdleLineFlag) && (uart->dma_rx != RT_NULL))
    {
        LPUART_ClearStatusFlags(uart->uart_base, kLPUART_IdleLineFlag);
        rt_size_t recv_len;
        rt_base_t level;
        level = rt_hw_interrupt_disable();
        {
            edma_handle_t *edma_h = &uart->dma_rx->edma;
            rt_size_t total_index = EDMA_TCD_CITER(&edma_h->tcdBase[edma_h->channel], EDMA_TCD_TYPE(edma_h->base)) & 0x7FFFU;
            total_index = uart->serial.config.dma_ping_bufsz - total_index;
            if (total_index > uart->dma_rx->last_index)
                recv_len = total_index - uart->dma_rx->last_index;
            else if (total_index < uart->dma_rx->last_index)
                recv_len = total_index + (uart->serial.config.dma_ping_bufsz - uart->dma_rx->last_index);
            else
                recv_len = 0;
            uart->dma_rx->last_index = total_index;
        }
        rt_hw_interrupt_enable(level);

        if (recv_len > 0)
        {
            if (recv_len > uart->serial.config.dma_ping_bufsz)
                recv_len = uart->serial.config.dma_ping_bufsz;
            rt_hw_serial_isr(&uart->serial, RT_SERIAL_EVENT_RX_DMADONE | (recv_len << 8));
        }
    }
#endif
}

#if defined(RT_SERIAL_USING_DMA) && defined(BSP_USING_DMA)
void edma_rx_callback(struct _edma_handle *handle, void *userData, bool transferDone, uint32_t tcds)
{
    rt_size_t recv_len = 0;
    rt_base_t level;
    struct imxrt_uart *uart = (struct imxrt_uart *)userData;
    RT_ASSERT(uart != RT_NULL);

    if (transferDone)
    {
        level = rt_hw_interrupt_disable();
        if ((EDMA_GetChannelStatusFlags(uart->dma_rx->edma_base, uart->dma_rx->channel) & kEDMA_DoneFlag) != 0U)
        {
            EDMA_ClearChannelStatusFlags(uart->dma_rx->edma_base, uart->dma_rx->channel, kEDMA_DoneFlag);
            recv_len = uart->serial.config.dma_ping_bufsz - uart->dma_rx->last_index;
            uart->dma_rx->last_index = 0;
        }
        else
        {
            EDMA_ClearChannelStatusFlags(uart->dma_rx->edma_base, uart->dma_rx->channel, kEDMA_InterruptFlag);
            rt_size_t total_index = EDMA_TCD_CITER(&handle->tcdBase[handle->channel], EDMA_TCD_TYPE(handle->base)) & 0x7FFFU;
            total_index = uart->serial.config.dma_ping_bufsz - total_index;
            if (total_index > uart->dma_rx->last_index)
                recv_len = total_index - uart->dma_rx->last_index;
            else
                recv_len = total_index + (uart->serial.config.dma_ping_bufsz - uart->dma_rx->last_index);
            uart->dma_rx->last_index = total_index;
        }
        rt_hw_interrupt_enable(level);

        if (recv_len)
        {
            if (recv_len > uart->serial.config.dma_ping_bufsz)
                recv_len = uart->serial.config.dma_ping_bufsz;
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

#ifdef SOC_IMXRT1180_SERIES
static void imxrt_edma_mux_setup(EDMA_Type *base, rt_uint8_t channel, dma_request_source_t request)
{
    EDMA_SetChannelMux(base, channel, request);
}
#else
static void imxrt_edma_mux_setup(EDMA_Type *base, rt_uint8_t channel, dma_request_source_t request)
{
    (void)base;
    DMAMUX_SetSource(DMAMUX, channel, request);
    DMAMUX_EnableChannel(DMAMUX, channel);
}
#endif

static void imxrt_dma_rx_config(struct imxrt_uart *uart)
{
    RT_ASSERT(uart != RT_NULL);
    edma_transfer_config_t xferConfig;
    EDMA_Type *base = uart->dma_rx->edma_base;

    imxrt_edma_mux_setup(base, uart->dma_rx->channel, uart->dma_rx->request);

    EDMA_CreateHandle(&uart->dma_rx->edma, base, uart->dma_rx->channel);
    EDMA_SetCallback(&uart->dma_rx->edma, edma_rx_callback, uart);

    rt_uint8_t *ping_buf;
    rt_hw_serial_control_isr(&uart->serial, RT_HW_SERIAL_CTRL_GET_DMA_PING_BUF, (void *)&ping_buf);

    EDMA_PrepareTransfer(&xferConfig,
                         (void *)LPUART_GetDataRegisterAddress(uart->uart_base),
                         sizeof(uint8_t),
                         ping_buf,
                         sizeof(uint8_t),
                         sizeof(uint8_t),
                         uart->serial.config.dma_ping_bufsz,
                         kEDMA_PeripheralToMemory);

    EDMA_SubmitTransfer(&uart->dma_rx->edma, &xferConfig);
    EDMA_EnableChannelInterrupts(base, uart->dma_rx->channel, kEDMA_MajorInterruptEnable | kEDMA_HalfInterruptEnable);
    EDMA_EnableAutoStopRequest(base, uart->dma_rx->channel, false);
    EDMA_TCD_DLAST_SGA(&uart->dma_rx->edma.tcdBase[uart->dma_rx->edma.channel], EDMA_TCD_TYPE(uart->dma_rx->edma.base)) = -(int32_t)uart->serial.config.dma_ping_bufsz;
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
    EDMA_Type *base = uart->dma_tx->edma_base;

    imxrt_edma_mux_setup(base, uart->dma_tx->channel, uart->dma_tx->request);

    EDMA_CreateHandle(&uart->dma_tx->edma, base, uart->dma_tx->channel);

    LPUART_TransferCreateHandleEDMA(uart->uart_base,
                                    &uart->dma_tx->uart_edma,
                                    edma_tx_callback,
                                    uart,
                                    &uart->dma_tx->edma,
                                    RT_NULL);

    LOG_D("%s dma tx config done\n", uart->name);
}
#endif

uint32_t GetUartSrcFreq(LPUART_Type *uart_base)
{
    uint32_t freq;
#if defined(SOC_IMXRT1170_SERIES)
    uint32_t base = (uint32_t)uart_base;
    switch (base)
    {
    case LPUART1_BASE:
        freq = CLOCK_GetRootClockFreq(kCLOCK_Root_Lpuart1);
        break;
    case LPUART12_BASE:
        freq = CLOCK_GetRootClockFreq(kCLOCK_Root_Lpuart12);
        break;
    default:
        freq = CLOCK_GetRootClockFreq(kCLOCK_Root_Lpuart2);
        break;
    }
#elif defined(SOC_IMXRT1180_SERIES)
    uint32_t base = (uint32_t)uart_base;
    switch (base)
    {
    case LPUART1_BASE:
    case LPUART2_BASE:
        freq = CLOCK_GetRootClockFreq(kCLOCK_Root_Lpuart0102);
        break;
    case LPUART3_BASE:
    case LPUART4_BASE:
        freq = CLOCK_GetRootClockFreq(kCLOCK_Root_Lpuart0304);
        break;
    case LPUART5_BASE:
    case LPUART6_BASE:
        freq = CLOCK_GetRootClockFreq(kCLOCK_Root_Lpuart0506);
        break;
    case LPUART7_BASE:
    case LPUART8_BASE:
        freq = CLOCK_GetRootClockFreq(kCLOCK_Root_Lpuart0708);
        break;
    case LPUART9_BASE:
    case LPUART10_BASE:
        freq = CLOCK_GetRootClockFreq(kCLOCK_Root_Lpuart0910);
        break;
    case LPUART11_BASE:
    case LPUART12_BASE:
        freq = CLOCK_GetRootClockFreq(kCLOCK_Root_Lpuart1112);
        break;
    default:
        freq = CLOCK_GetRootClockFreq(kCLOCK_Root_Lpuart0102);
        break;
    }
#else
    if (CLOCK_GetMux(kCLOCK_UartMux) == 0)
    {
        freq = (CLOCK_GetPllFreq(kCLOCK_PllUsb1) / 6U) / (CLOCK_GetDiv(kCLOCK_UartDiv) + 1U);
    }
    else
    {
        freq = CLOCK_GetOscFreq() / (CLOCK_GetDiv(kCLOCK_UartDiv) + 1U);
    }
#endif
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

    LPUART_Init(uart->uart_base, &config, GetUartSrcFreq(uart->uart_base));

    return RT_EOK;
}

static rt_err_t imxrt_control(struct rt_serial_device *serial, int cmd, void *arg)
{
    struct imxrt_uart *uart;

    RT_ASSERT(serial != RT_NULL);
    uart = rt_container_of(serial, struct imxrt_uart, serial);

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

    case RT_DEVICE_CTRL_CONFIG:
    {
        rt_ubase_t ctrl_arg = (rt_ubase_t)arg;

#if defined(RT_SERIAL_USING_DMA) && defined(BSP_USING_DMA)
        if (RT_DEVICE_FLAG_DMA_RX == ctrl_arg)
        {
            imxrt_dma_rx_config(uart);
            break;
        }
        if (RT_DEVICE_FLAG_DMA_TX == ctrl_arg)
        {
            imxrt_dma_tx_config(uart);
            break;
        }
#endif

        if (RT_DEVICE_FLAG_RX_BLOCKING == ctrl_arg || RT_DEVICE_FLAG_RX_NON_BLOCKING == ctrl_arg)
        {
            LPUART_EnableInterrupts(uart->uart_base, kLPUART_RxDataRegFullInterruptEnable);
            NVIC_SetPriority(uart->irqn, NVIC_EncodePriority(NVIC_GetPriorityGrouping(), 4, 0));
            EnableIRQ(uart->irqn);
            break;
        }
        if (RT_DEVICE_FLAG_TX_BLOCKING == ctrl_arg || RT_DEVICE_FLAG_TX_NON_BLOCKING == ctrl_arg)
        {
            LPUART_EnableInterrupts(uart->uart_base, kLPUART_TxDataRegEmptyInterruptEnable);
            NVIC_SetPriority(uart->irqn, NVIC_EncodePriority(NVIC_GetPriorityGrouping(), 4, 0));
            EnableIRQ(uart->irqn);
            break;
        }
        break;
    }

    case RT_DEVICE_CHECK_OPTMODE:
        if (uart->dma_flag & RT_DEVICE_FLAG_DMA_TX)
            return RT_SERIAL_TX_BLOCKING_NO_BUFFER;
        return RT_SERIAL_TX_BLOCKING_BUFFER;
    }

    return RT_EOK;
}

static int imxrt_putc(struct rt_serial_device *serial, char ch)
{
    struct imxrt_uart *uart;

    RT_ASSERT(serial != RT_NULL);
    uart = rt_container_of(serial, struct imxrt_uart, serial);

    LPUART_WriteByte(uart->uart_base, ch);
    while (!(LPUART_GetStatusFlags(uart->uart_base) & kLPUART_TxDataRegEmptyFlag))
        ;

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
static rt_ssize_t imxrt_transmit(struct rt_serial_device *serial,
                                 rt_uint8_t *buf, rt_size_t size, rt_uint32_t tx_flag)
{
    struct imxrt_uart *uart;

    RT_ASSERT(serial != RT_NULL);
    uart = rt_container_of(serial, struct imxrt_uart, serial);

    if (uart->dma_flag & RT_DEVICE_FLAG_DMA_TX)
    {
        lpuart_transfer_t xfer;
        RT_ASSERT(buf != RT_NULL);
        xfer.data = buf;
        xfer.dataSize = size;
        if (LPUART_SendEDMA(uart->uart_base, &uart->dma_tx->uart_edma, &xfer) == kStatus_Success)
            return (rt_ssize_t)size;
        return -RT_EIO;
    }

    if (size == 0)
    {
        LPUART_EnableInterrupts(uart->uart_base, kLPUART_TxDataRegEmptyInterruptEnable);
        return 0;
    }

    {
        rt_uint8_t *ptr = buf;
        while (size--)
        {
            LPUART_WriteByte(uart->uart_base, *ptr++);
            while (!(LPUART_GetStatusFlags(uart->uart_base) & kLPUART_TxDataRegEmptyFlag))
                ;
        }
        return (rt_ssize_t)(ptr - buf);
    }
}

#endif

static const struct rt_uart_ops imxrt_uart_ops = {
    imxrt_configure,
    imxrt_control,
    imxrt_putc,
    imxrt_getc,
#if defined(RT_SERIAL_USING_DMA) && defined(BSP_USING_DMA)
    imxrt_transmit,
#else
    RT_NULL
#endif
};

int rt_hw_uart_init(void)
{
    int i;
    rt_err_t ret = RT_EOK;
    struct serial_configure config = RT_SERIAL_CONFIG_DEFAULT;

    uart_get_dma_config();

    for (i = 0; i < sizeof(uarts) / sizeof(uarts[0]); i++)
    {
        uarts[i].serial.ops = &imxrt_uart_ops;
        uarts[i].serial.config = config;

        ret = rt_hw_serial_register(&uarts[i].serial, uarts[i].name,
                                    RT_DEVICE_FLAG_RDWR, NULL);
    }

    return ret;
}
INIT_BOARD_EXPORT(rt_hw_uart_init);

#endif /* BSP_USING_LPUART */
#endif /* RT_USING_SERIAL_V2 */
