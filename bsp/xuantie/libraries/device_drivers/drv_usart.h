/*
 * Copyright (c) 2006-2025, RT-Thread Development Team
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

#include <soc.h>
#include <dw_uart_ll.h>
#include <drv/uart.h>

/* xuantie config class */
struct xuantie_uart_config
{
    const char *name;
    uint32_t idx;
    void (*xuantie_uart_rx_isr)(csi_uart_t *uart_handler, csi_uart_event_t event, void *arg);
};

/* xuantie uart dirver class */
struct xuantie_uart
{
    struct xuantie_uart_config *config;
    struct rt_serial_device serial;
    csi_uart_t uart;
};

extern void uart_rx_isr (void *id);
int rt_hw_usart_init(void);
#endif /* __DRV_USART_H__ */
