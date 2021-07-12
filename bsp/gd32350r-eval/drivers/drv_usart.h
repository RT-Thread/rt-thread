/*
 * Copyright (c) 2006-2021, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author            Notes
 * 2021-06-20     RiceChen          the first version
 */

#ifndef __DRV_USART_H__
#define __DRV_USART_H__

#include <rtthread.h>
#include <rtdevice.h>
#include "gd32f3x0.h"
#include "gd32f3x0_usart.h"
#include "gd32f3x0_exti.h"

struct gd32_usart_config
{
    char *dev_name;
    rt_uint32_t periph;
    IRQn_Type irqn;
    rcu_periph_enum per_clk;
    rcu_periph_enum tx_gpio_clk;
    rcu_periph_enum rx_gpio_clk;
    rt_uint32_t tx_port;
    rt_uint32_t tx_pin;
    rt_uint32_t rx_port;
    rt_uint32_t rx_pin;
};

struct gd32_usart_bus
{
    struct rt_serial_device serial;
    struct gd32_usart_config *config;
};

#ifdef BSP_USING_UART0
#define UART0_BUS_CONFIG                \
    {                                   \
        .dev_name    = "uart0",         \
        .periph      = USART0,          \
        .irqn        = USART0_IRQn,     \
        .per_clk     = RCU_USART0,      \
        .tx_gpio_clk = RCU_GPIOA,       \
        .rx_gpio_clk = RCU_GPIOA,       \
        .tx_port     = GPIOA,           \
        .tx_pin      = GPIO_PIN_9,      \
        .rx_port     = GPIOA,           \
        .rx_pin      = GPIO_PIN_10,     \
    }
#endif /* BSP_USING_UART0 */

#ifdef BSP_USING_UART1
#define UART1_BUS_CONFIG                \
    {                                   \
        .dev_name    = "uart1",         \
        .periph      = USART1,          \
        .irqn        = USART1_IRQn,     \
        .per_clk     = RCU_USART1,      \
        .tx_gpio_clk = RCU_GPIOA,       \
        .rx_gpio_clk = RCU_GPIOA,       \
        .tx_port     = GPIOA,           \
        .tx_pin      = GPIO_PIN_2,      \
        .rx_port     = GPIOA,           \
        .rx_pin      = GPIO_PIN_3,      \
    }
#endif /* BSP_USING_UART1 */

#endif
