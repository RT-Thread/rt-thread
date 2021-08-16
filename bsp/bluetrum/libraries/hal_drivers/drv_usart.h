/*
 * Copyright (c) 2020-2021, Bluetrum Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author            Notes
 * 2020-11-20     greedyhao         first version
 */

#ifndef DRV_USART_H__
#define DRV_USART_H__

#include "drv_common.h"

#ifdef RT_USING_SERIAL

/* an32 config class */
struct ab32_uart_config
{
    const char *name;
    hal_sfr_t   instance;
    uint8_t     mode;
    uint16_t    fifo_size;
    uint8_t     reserve[1];
    // struct dma_config *dma_rx;
    // struct dma_config *dma_tx;
};

/* ab32 uart driver class */
struct ab32_uart
{
    struct uart_handle handle;
    struct ab32_uart_config *config;

#ifdef RT_SERIAL_USING_DMA
    struct
    {
        DMA_HandleTypeDef handle;
        rt_size_t last_index;
    } dma_rx;
    struct
    {
        DMA_HandleTypeDef handle;
    } dma_tx;
#endif
    rt_uint16_t uart_dma_flag;
    struct rt_serial_device serial;
    rt_uint8_t *rx_buf;
    rt_uint8_t rx_idx;
    rt_uint8_t rx_idx_prev;
};

#endif

int rt_hw_usart_init(void);

#endif
