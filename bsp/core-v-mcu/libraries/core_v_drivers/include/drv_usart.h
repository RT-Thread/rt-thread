/*
 * Copyright (c) 2006-2022, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2022-12-08     WangShun     the first version
 */
#ifndef __DRV_USART_H__
#define __DRV_USART_H__
#include <rtthread.h>
#include "rtdevice.h"
#include <rthw.h>

/* corev config class */
struct corev_uart_config
{
    const char *name;
};

/* corevs uart dirver class */
struct corev_uart
{
    struct corev_uart_config *config;
    struct rt_serial_device serial;
};

extern void uart_rx_isr (void *id);
int rt_hw_usart_init(void);
#endif
