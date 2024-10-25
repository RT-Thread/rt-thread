/*
 * Copyright (c) 2006-2022, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2021-08-20     BruceOu      first implementation
 */

#ifndef __DRV_USART_H__
#define __DRV_USART_H__

#include <rthw.h>
#include <rtthread.h>
#include <board.h>

#ifdef __cplusplus
extern "C" {
#endif

#define UART_ENABLE_IRQ(n)            NVIC_EnableIRQ((n))
#define UART_DISABLE_IRQ(n)           NVIC_DisableIRQ((n))


/* GD32 uart driver */
// Todo: compress uart info
struct gd32_uart
{
    uint32_t uart_periph;           //Todo: 3bits
    IRQn_Type irqn;                 //Todo: 7bits
    rcu_periph_enum per_clk;        //Todo: 5bits
    rcu_periph_enum tx_gpio_clk;    //Todo: 5bits
    rcu_periph_enum rx_gpio_clk;    //Todo: 5bits
    uint32_t tx_port;               //Todo: 4bits
#if defined SOC_SERIES_GD32F4xx || defined SOC_SERIES_GD32H7xx
    uint16_t tx_af;                 //Todo: 4bits
#elif defined SOC_SERIES_GD32E50x
    uint32_t tx_af;                 //alternate1 cfg
#endif
    uint16_t tx_pin;                //Todo: 4bits
    uint32_t rx_port;               //Todo: 4bits
#if defined SOC_SERIES_GD32F4xx || defined SOC_SERIES_GD32H7xx
    uint16_t rx_af;                 //Todo: 4bits
#elif defined SOC_SERIES_GD32E50x
    uint32_t rx_af;                 //alternate1 cfg
#endif
    uint16_t rx_pin;                //Todo: 4bits
#if defined SOC_SERIES_GD32E50x
    uint32_t uart_remap;            //remap
#endif

    struct rt_serial_device * serial;
    char *device_name;
};

int rt_hw_usart_init(void);

#ifdef __cplusplus
}
#endif

#endif /* __DRV_USART_H__ */
