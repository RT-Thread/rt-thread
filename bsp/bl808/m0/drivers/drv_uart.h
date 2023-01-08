/*
 * Copyright (c) 2006-2023, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2022/12/25     flyingcys    first version
 */

#ifndef __DRV_USART_H__
#define __DRV_USART_H__

#include <rtthread.h>
#include "rtdevice.h"
#include <rthw.h>

#include "bl_uart.h"
#include "bl808_uart.h"

#include "uart_config.h"

int rt_hw_uart_init(void);

#endif  /* __DRV_USART_H__ */
