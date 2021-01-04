/*
 * Copyright (c) 2006-2021, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author            Notes
 * 2021-01-04     iysheng           first version
 */

#ifndef __USART_H__
#define __USART_H__

#include <rthw.h>
#include <rtthread.h>

/* GD32 uart driver */
struct gd32_uart {
    USART_TypeDef * uart_periph;
    IRQn_Type irqn;
    rcu_periph_enum per_clk;
    rcu_periph_enum tx_gpio_clk;
    rcu_periph_enum rx_gpio_clk;
    GPIO_TypeDef * tx_port;
    GPIO_TypeDef * rx_port;
    uint16_t tx_pin;
    uint16_t rx_pin;

    struct rt_serial_device *serial;
    char *device_name;
};

#endif
