/*
 * Copyright (c) 2006-2022, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2022-08-04     tangzz98     first version
 *
 */

#ifndef __DRV_UART_H__
#define __DRV_UART_H__

#include <rtconfig.h>

#ifdef RT_USING_SERIAL_V1
int rt_hw_uart_init(void);
#endif

#endif /* __DRV_UART_H__ */
