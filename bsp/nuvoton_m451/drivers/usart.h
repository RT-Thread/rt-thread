/*
 * Copyright (c) 2006-2021, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2016-12-05     Pluto        first implementation
 */

#ifndef __USART_H__
#define __USART_H__

#include "M451Series.h"
#include <rthw.h>
#include <rtthread.h>
#include <rtdevice.h>

#define RT_USING_UART0
//#define RT_USING_UART1

void rt_hw_usart_init(void);

#endif
