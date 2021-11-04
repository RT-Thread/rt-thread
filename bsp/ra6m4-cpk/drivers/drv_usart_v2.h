/*
 * Copyright (c) 2006-2021, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2021-07-29     KyleChan     first version
 */

#ifndef __DRV_USART_V2_H__
#define __DRV_USART_V2_H__

#include <rtthread.h>
#include <rtdevice.h>
#include <rthw.h>
#include <drv_common.h>
#include <drv_config.h>
#include <hal_data.h>

/* renesas config class */
struct ra_uart_config
{
    const char *name;
    uart_ctrl_t *const p_api_ctrl;
    uart_cfg_t const *const p_cfg;
};

struct ra_uart
{
    struct rt_serial_device serial;

    rt_uint16_t uart_dma_flag;

    struct ra_uart_config *config;
};

int rt_hw_usart_init(void);

#endif  /* __DRV_USART_H__ */
