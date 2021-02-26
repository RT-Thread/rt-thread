/*
 * Copyright (c) 2006-2020, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2020-04-15     hqfang       first version
 */
#ifndef __DRV_UART_H__
#define __DRV_UART_H__

#include <rtthread.h>
#include <rtdevice.h>
#include <drv_config.h>

/* gd32 config class */
struct gd32_uart_config
{
    const char *name;
    uint32_t uart_base;
    IRQn_Type irqn;
};

/* gd32 uart dirver class */
struct gd32_uart
{
    struct rt_serial_device serial;
    struct gd32_uart_config *config;
};

int rt_hw_usart_init(void);

#endif /* __DRV_USART_H__ */

/******************* end of file *******************/
