/*
 * Copyright (c) 2006-2024, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date         Author      Notes
 * 2024-03-19   Evlers      first implementation
 */

#ifndef __DRV_USART_V2_H__
#define __DRV_USART_V2_H__

#include <rthw.h>
#include <rtthread.h>
#include <rtdevice.h>
#include <board.h>
#include "drv_dma.h"

#ifdef __cplusplus
extern "C" {
#endif


/* GD32 uart driver */
struct gd32_uart
{
    char *device_name;
    uint32_t periph;
    IRQn_Type irqn;
    rcu_periph_enum per_clk;
    rcu_periph_enum tx_gpio_clk;
    rcu_periph_enum rx_gpio_clk;
    uint32_t tx_port;
#if defined SOC_SERIES_GD32F4xx
    uint16_t tx_af;
#endif
    uint16_t tx_pin;
    uint32_t rx_port;
#if defined SOC_SERIES_GD32F4xx
    uint16_t rx_af;
#endif
    uint16_t rx_pin;

    struct rt_serial_device serial;

#ifdef RT_SERIAL_USING_DMA
    struct
    {
        struct dma_config rx;
        struct dma_config tx;
        rt_size_t last_index;
        rt_sem_t sem_ftf;
    } dma;
#endif
    rt_uint16_t uart_dma_flag;
};

int rt_hw_usart_init(void);

#ifdef __cplusplus
}
#endif

#endif /* __DRV_USART_V2_H__ */
