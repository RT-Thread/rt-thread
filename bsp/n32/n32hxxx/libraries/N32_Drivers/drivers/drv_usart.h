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

#define UART_RX_DMA_IT_IDLE_FLAG             0x00
#define UART_RX_DMA_IT_BLOCK_TC_FLAG         0x01

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

#ifdef RT_SERIAL_USING_DMA
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
            rt_size_t block_has_recv_cnt;
            DMA_LinkListItemType *Read_LinkList;

        } rx_dma;

    } dma;

#endif
    rt_uint16_t uart_dma_flag;
    struct rt_serial_device serial;
};


#endif  /* __DRV_USART_H__ */
