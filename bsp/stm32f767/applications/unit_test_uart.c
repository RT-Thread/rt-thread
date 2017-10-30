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
static void callback(void * args)
{
	rt_kprintf("read pin 6:%d\n",rt_pin_read(6));
}
int test(void)
{
//    rt_device_t uart_device;
//    uart_device = rt_device_find(UART_TEST_DEVICE);

//    if (uart_device == RT_NULL)
//    {
//        rt_kprintf("No device : %s\n", UART_TEST_DEVICE);
//        return -1;
//    }
//    rt_kprintf("Found device : %s\n", UART_TEST_DEVICE);
//    if (rt_device_open(uart_device, RT_DEVICE_FLAG_STREAM | RT_DEVICE_FLAG_DMA_TX) != RT_EOK)
//    {
//        rt_kprintf("Can not open device : %s\n", UART_TEST_DEVICE);
//        return -1;
//    }
//    rt_kprintf("Open device : %s\n", UART_TEST_DEVICE);

	rt_pin_attach_irq(6,PIN_IRQ_MODE_RISING_FALLING,callback,RT_NULL);
	pin_irq_enable(6,PIN_IRQ_ENABLE);



    return 0;
}
MSH_CMD_EXPORT(test, my command test);











