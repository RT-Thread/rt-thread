/*
 * File      : usart.c
 * This file is part of RT-Thread RTOS
 * COPYRIGHT (C) 2006-2014, RT-Thread Development Team
 *
 * The license and distribution terms for this file may be
 * found in the file LICENSE in this distribution or at
 * http://www.rt-thread.org/license/LICENSE
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
