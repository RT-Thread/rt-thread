/*
 * Copyright (c) 2006-2023, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2021-08-20     BruceOu      first implementation
 * 2023-06-17     CX           support DMA TX and RX
 */

#ifndef __DRV_USART_H__
#define __DRV_USART_H__

#include <rthw.h>
#include <rtthread.h>
#include <board.h>

#ifdef __cplusplus
extern "C"
{
#endif

#define UART_ENABLE_IRQ(n) NVIC_EnableIRQ((n))
#define UART_DISABLE_IRQ(n) NVIC_DisableIRQ((n))

#ifdef RT_SERIAL_USING_DMA
    struct dma_config
    {
        rt_uint32_t dma_periph;
        dma_channel_enum channel;
        dma_subperipheral_enum peripheral;
        rt_uint32_t priority;
        rt_size_t remaining_cnt;
        IRQn_Type dma_irqn;
    };

#define UART_RX_DMA_IT_IDLE_FLAG 0x00
#define UART_RX_DMA_IT_HT_FLAG 0x01
#define UART_RX_DMA_IT_TC_FLAG 0x02
#endif

    /* GD32 uart driver */
    // Todo: compress uart info
    struct gd32_uart
    {
        char *device_name;
        uint32_t uart_periph;        // Todo: 3bits
        IRQn_Type irqn;              // Todo: 7bits
        rcu_periph_enum per_clk;     // Todo: 5bits
        rcu_periph_enum tx_gpio_clk; // Todo: 5bits
        rcu_periph_enum rx_gpio_clk; // Todo: 5bits
        uint32_t tx_port;            // Todo: 4bits
#if defined SOC_SERIES_GD32F4xx
        uint16_t tx_af; // Todo: 4bits
#endif
        uint16_t tx_pin;  // Todo: 4bits
        uint32_t rx_port; // Todo: 4bits
#if defined SOC_SERIES_GD32F4xx
        uint16_t rx_af; // Todo: 4bits
#endif
        uint16_t rx_pin; // Todo: 4bits

#ifdef RT_SERIAL_USING_DMA
        rt_uint16_t dma_flag;
        struct dma_config *dma_rx;
        struct dma_config *dma_tx;
#endif
        struct rt_serial_device *serial;
    };

#ifdef __cplusplus
}
#endif

#endif /* __DRV_USART_H__ */
