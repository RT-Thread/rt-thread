/*
 * Copyright (c) 2006-2025, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author           Notes
 * 2026-01-24     ox-horse         first version
 */

#ifndef __DRV_USART_H__
#define __DRV_USART_H__

#include <rtthread.h>
#include "rtdevice.h"
#include <rthw.h>
#include <drv_common.h>
#include "drv_dma.h"

int rt_hw_usart_init(void);

#if defined(SOC_SERIES_N32H7xx)
#define UART_RX_DMA_IT_IDLE_FLAG     0x00
#define UART_RX_DMA_IT_BLOCK_TC_FLAG 0x01
#elif defined(SOC_SERIES_N32H49x) || defined(SOC_SERIES_N32H47x_48x)
#define UART_RX_DMA_IT_IDLE_FLAG 0x00
#define UART_RX_DMA_IT_HT_FLAG   0x01
#define UART_RX_DMA_IT_TC_FLAG   0x02

#define UART_CTRL_SET_BLOCK_TIMEOUT 0x20
#endif

/* n32 config class */
struct n32_uart_config
{
    const char *name;
    USART_Module *Instance;
    IRQn_Type irq_type;
    uint32_t periph;
    void (*EnablePeriphClk)(uint32_t periph, FunctionalState cmd);
    struct dma_config *dma_rx;
    struct dma_config *dma_tx;
};

/* n32 uart dirver class */
struct n32_uart
{
    struct n32_uart_config *config;
    rt_uint32_t DR_mask;
    rt_uint32_t tx_block_timeout;

#ifdef RT_SERIAL_USING_DMA
#if defined(SOC_SERIES_N32H7xx)
    struct
    {
        rt_bool_t DMA_Tx_Init;
        DMA_ChInitType TX_DMA_ChInitStr;

        struct
        {
            rt_size_t record_length;
            rt_size_t total_length;
            rt_size_t already_send_length;

            rt_uint8_t *buf;
        } tx_dma;


        rt_bool_t DMA_Rx_Init;
        DMA_ChInitType RX_DMA_ChInitStr;

        struct
        {
            rt_uint16_t block_num;
            rt_uint16_t remain_len;
            /* LLI ring accounting (maintained in the TC ISR; BTS is never read
             * here: the hardware wraps BTS the instant a block completes, so
             * reading BTS at TC and diffing it against the last value would
             * underflow and permanently corrupt the FIFO put index):
             *   lli_blk_cnt    number of completed LLI blocks (also used as
             *                  the block index, modulo block_num)
             *   lli_byte_base  actual bytes accumulated for completed blocks.
             *                  NOTE: the last LLI item may be shorter than
             *                  4095B (remain_len; 4B when bufsz = 16384), so
             *                  the TC ISR must add each block's real size.
             *                  Otherwise the counter drifts +4095-remain_len
             *                  bytes per ring turn (e.g. +4091B per turn for
             *                  a 16384B buffer), eventually corrupting the
             *                  FIFO read pointer.
             *   lli_last_cum   cumulative bytes at the last IDLE report (the
             *                  difference between two reports = frame len) */
            rt_uint32_t lli_blk_cnt;
            rt_uint32_t lli_byte_base;
            rt_uint32_t lli_last_cum;
            DMA_LinkListItemType *Read_LinkList;

        } rx_dma;

    } dma;
#elif defined(SOC_SERIES_N32H49x) || defined(SOC_SERIES_N32H47x_48x)
    struct
    {
        DMA_InitType TX_DMA_ChInitStr;
        struct
        {
            rt_size_t total_length;
            rt_uint8_t *buf;
        } tx_dma;

        rt_bool_t tx_dma_inited;

        DMA_InitType RX_DMA_ChInitStr;
        struct
        {
            rt_size_t remaining_cnt;
        } rx_dma;

        rt_bool_t rx_dma_inited;

    } dma;
#endif /* SOC_SERIES_N32H7xx */
#endif /* RT_SERIAL_USING_DMA */
    rt_uint16_t uart_dma_flag;
    struct rt_serial_device serial;
};


#endif  /* __DRV_USART_H__ */
