/*
 * Copyright (c) 2006-2021, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2009-01-05     Bernard      the first version
 * 2022-06-09     THEWON       first version for serialX
 */

#ifndef __DRV_USARTX_H__
#define __DRV_USARTX_H__

#include <rthw.h>
#include <rtthread.h>
#include <rtdevice.h>

#define UART_ENABLE_IRQ(n)            NVIC_EnableIRQ((n))
#define UART_DISABLE_IRQ(n)           NVIC_DisableIRQ((n))

/* stm32 config class */
struct gd32_uart_config
{
    const char *name;
    IRQn_Type irqn;
    
    rcu_periph_enum per_clk;
    rcu_periph_enum tx_gpio_clk;
    rcu_periph_enum rx_gpio_clk;
    uint32_t tx_port;
    uint16_t tx_af;
    uint16_t tx_pin;
    uint32_t rx_port;
    uint16_t rx_af;
    uint16_t rx_pin;
};

struct gd32_uart_dma
{
    /* dma channel */
    uint32_t dma_periph;
    dma_channel_enum dma_channel;
    dma_subperipheral_enum dma_subperi;
    /* dma irq channel */
    IRQn_Type dma_irq;
};

/* gd32 uart driver class */
struct gd32_uart
{
    uint32_t uart_periph;
    struct rt_serial_device serial;
    struct gd32_uart_config uart_config;
#ifdef RT_SERIAL_USING_DMA
    rt_bool_t dmaTxing;
    struct gd32_uart_dma dma_rx;
    struct gd32_uart_dma dma_tx;
#endif
};

int rt_hw_usart_init(void);

#endif // __DRV_USARTX_H__
