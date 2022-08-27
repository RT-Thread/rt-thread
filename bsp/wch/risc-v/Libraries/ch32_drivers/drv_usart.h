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


/* ch32 config class */
struct ch32_uart_config
{
    const char *name;
    USART_TypeDef *Instance;
    IRQn_Type irq_type;
};


/* ch32 uart dirver class */
struct ch32_uart
{
    struct ch32_uart_config *config;
    USART_InitTypeDef Init;		
    struct rt_serial_device serial;
};


int rt_hw_usart_init(void);
#endif
