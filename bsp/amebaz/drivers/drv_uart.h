/*
 * File      : drv_uart.h
 * This file is part of RT-Thread RTOS
 * COPYRIGHT (C) 2017, RT-Thread Development Team
 *
 *  This program is free software; you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation; either version 2 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License along
 *  with this program; if not, write to the Free Software Foundation, Inc.,
 *  51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.
 *
 * Change Logs:
 * Date           Author       Notes
 * 2017-05-30     Bernard      the first version
 * 2018-03-15     flyingcys    add amebaz
 */

#ifndef __DRV_UART_H__
#define __DRV_UART_H__

#if defined(CONFIG_PLATFORM_8711B)
// 8710B
#define UART_TX PA_23
#define UART_RX PA_18
#else
// 8711AM
#define UART_TX PA_7
#define UART_RX PA_6
//8711AF
//#define UART_TX PA_4
//#define UART_RX PA_0
#endif

int rt_hw_uart_init(void);

#endif /* __DRV_UART_H__ */
