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

/* config class */
struct hbird_uart_config
{
    const char *name;
    UART_TypeDef *uart;
    IRQn_Type irqn;
};

/* hbird uart dirver class */
struct hbird_uart
{
    struct hbird_uart_config *config;
    struct rt_serial_device serial;
};

extern int rt_hw_uart_init(void);

#endif /* __DRV_USART_H__ */

/******************* end of file *******************/
