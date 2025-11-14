/*
 * Copyright (c) 2006-2025, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2021-08-20     BruceOu      first implementation
 * 2025-10-09     WangShun     optimize the serial driver
 * 2025-11-13     kurisaw      general GD driver adaptation
 */

#ifndef __DRV_USART_H__
#define __DRV_USART_H__

#include <rthw.h>
#include <rtthread.h>
#include <board.h>

#ifdef __cplusplus
extern "C" {
#endif

#if !defined(SOC_SERIES_GD32H7xx) || !defined(SOC_SERIES_GD32H75E)
#undef RT_SERIAL_USING_DMA
#endif
#define UART_ENABLE_IRQ(n)            NVIC_EnableIRQ((n))
#define UART_DISABLE_IRQ(n)           NVIC_DisableIRQ((n))

#ifdef RT_SERIAL_USING_DMA

typedef struct
{
    /* dma peripheral */
    uint32_t dma_periph;
    /* dma channel */
    dma_channel_enum dma_ch;
#if defined(SOC_SERIES_GD32H7xx) || defined(SOC_SERIES_GD32H75E)
    /* rx dma request */
    uint32_t dma_mux_req_rx;
#endif
    /* dma flag */
    uint32_t rx_flag;
    /* dma irq channel */
    uint8_t rx_irq_ch;
    /* setting receive len */
    rt_size_t setting_recv_len;
    /* last receive index */
    rt_size_t last_recv_index;
} gd32_uart_dma;

#endif
/* GD32 uart driver */

struct gd32_uart
{
    uint32_t uart_periph;             /* Instance */
    IRQn_Type irqn;                   /* irqn */
    rcu_periph_enum per_clk;          /* uart_clk */

    const char *tx_pin_name;          /* tx pin name */
    const char *rx_pin_name;          /* rx pin name */
    const char *alternate;            /* pin alternate */

#ifdef RT_SERIAL_USING_DMA
    gd32_uart_dma *uart_dma;
#ifdef RT_SERIAL_USING_TX_DMA
    gd32_uart_dma *uart_tx_dma;
#endif
#endif

    struct rt_serial_device * serial; /* serial device */
    char *device_name;
};

int rt_hw_usart_init(void);

#ifdef __cplusplus
}
#endif

#endif /* __DRV_USART_H__ */

