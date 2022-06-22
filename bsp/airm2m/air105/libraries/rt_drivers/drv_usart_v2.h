/*
 * Copyright (c) 2006-2022, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2022-02-22     airm2m       first version
 */


#ifndef __DRV_USART_V2_H__
#define __DRV_USART_V2_H__

#include <rtthread.h>
#include <rtdevice.h>
#include <rthw.h>
#include <drv_common.h>
#include "drv_config.h"

/* renesas config class */
struct air_uart_config
{
    const char *name;
    rt_uint8_t  id;
};

struct air_uart
{
    struct rt_serial_device serial;
    struct air_uart_config *config;
};

int rt_hw_usart_init(void);

#endif  /* __DRV_USART_H__ */
