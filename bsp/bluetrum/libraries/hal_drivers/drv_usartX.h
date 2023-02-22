/*
 * Copyright (c) 2020-2022, Bluetrum Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author            Notes
 * 2020-11-20     greedyhao         first version
 * 2022-06-08     THEWON            first version for serialX
 */

#ifndef DRV_USART_H__
#define DRV_USART_H__

#include "drv_common.h"

#ifdef RT_USING_SERIAL

/* an32 config class */
struct ab32_uart_config
{
    const char *name;
    hal_sfr_t   instance;
    uint8_t     mode;
};

/* ab32 uart driver class */
struct ab32_uart
{
    struct uart_handle handle;
    struct rt_serial_device serial;
    struct ab32_uart_config *uart_config;
    rt_bool_t intTxing;
};

#endif

int rt_hw_usart_init(void);

#endif
