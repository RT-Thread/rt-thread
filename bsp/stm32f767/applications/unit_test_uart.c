/*
 * File      : board.c
 * This file is part of RT-Thread RTOS
 * COPYRIGHT (C) 2015, RT-Thread Development Team
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
 * 2017-10-25     ZYH      first implementation
 */
#include <board.h>
#include <rtthread.h>
#include <rtdevice.h>
#include <finsh.h>
#define UART_TEST_DEVICE "uart3"
int test_uart(void)
{
	rt_device_t uart_device;
	rt_uint16_t old_flag; 
	uart_device = rt_device_find(UART_TEST_DEVICE);
	
	if(uart_device == RT_NULL)
	{
		rt_kprintf("No device : %s\n",UART_TEST_DEVICE);
		return -1;
	}
	rt_kprintf("Found device : %s\n",UART_TEST_DEVICE);
	old_flag = uart_device->open_flag;
	if(rt_device_open(uart_device, RT_DEVICE_FLAG_STREAM|RT_DEVICE_FLAG_DMA_TX) != RT_EOK)
	{
		rt_kprintf("Can not open device : %s\n",UART_TEST_DEVICE);
		return -1;
	}
	rt_kprintf("Open device : %s\n",UART_TEST_DEVICE);
	
	
	
	
	
	
	
  return 0;
}
MSH_CMD_EXPORT(test_uart, my command test);











