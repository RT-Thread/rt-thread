/*
 * Copyright (c) 2006-2022, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2022-06-06     THEWON       first version for serialX
 */

#ifndef __DRV_USARTX_H__
#define __DRV_USARTX_H__

#include "rtdevice.h"

struct n32_uart_dma
{
    /* dma channel */
    DMA_ChannelType *dma_ch;
    DMA_Module *dma_module;
    /* dma global flag */
    uint32_t dma_flag;
    /* dma irq channel */
    uint8_t dma_irq;
};

struct n32_uart
{
    USART_Module *uart_device;
    struct rt_serial_device serial;
    IRQn_Type irq;
#ifdef RT_SERIAL_USING_DMA
    rt_bool_t dmaTxing;
    struct n32_uart_dma dma_rx;
    struct n32_uart_dma dma_tx;
#endif
};

#endif  /* __DRV_USART_H__ */
