/*
 * Copyright (c) 2006-2018, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
<<<<<<< HEAD
 * 2021-09-09     WCH        the first version
=======
 * 2022-12-08     WangShun     the first version
>>>>>>> 1185482745fa76c9094f8cf9227f85d55ed8e2bd
 */
#ifndef __DRV_USART_H__
#define __DRV_USART_H__
#include <rtthread.h>
#include "rtdevice.h"
#include <rthw.h>

<<<<<<< HEAD

/* corev config class */
struct ch32_uart_config
=======
/* corev config class */
struct corev_uart_config
>>>>>>> 1185482745fa76c9094f8cf9227f85d55ed8e2bd
{
    const char *name;
};

/* corevs uart dirver class */
<<<<<<< HEAD
struct ch32_uart
{
    struct ch32_uart_config *config;
=======
struct corev_uart
{
    struct corev_uart_config *config;
>>>>>>> 1185482745fa76c9094f8cf9227f85d55ed8e2bd
    struct rt_serial_device serial;
};

extern void uart_rx_isr (void *id);
int rt_hw_usart_init(void);
#endif
