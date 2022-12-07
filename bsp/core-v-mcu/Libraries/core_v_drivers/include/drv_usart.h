/*
 * Copyright (c) 2006-2018, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2021-09-09     WCH        the first version
 */
#ifndef __DRV_USART_H__
#define __DRV_USART_H__
#include <rtthread.h>
#include "rtdevice.h"
#include <rthw.h>


/* corev config class */
struct ch32_uart_config
{
    const char *name;
};

/* corevs uart dirver class */
struct ch32_uart
{
    struct ch32_uart_config *config;
    struct rt_serial_device serial;
};

extern void uart_rx_isr (void *id);
int rt_hw_usart_init(void);
#endif
