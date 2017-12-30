/*
 * File      : main.c
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
 * 2009-01-05     Bernard      the first version
 * 2014-04-27     Bernard      make code cleanup.
 * 2017-08-25     LongfeiMa    transplantation for stm32h7xx
 */

#include <rthw.h>
#include <rtthread.h>

#include "board.h"
#include <stm32h7xx.h>

#include "lan8742a.h"

#include "netif/ethernetif.h"



int main(void)
{
//	rt_kprintf("here we are in the main \r\n");
	/* LwIP Initialization */
#ifdef RT_USING_LWIP
	{
//		extern void lwip_sys_init(void);
//		eth_system_device_init();

		/* register ethernetif device */
//		rt_hw_lan8742a_init();

		/* init lwip system */
//		lwip_sys_init();
		rt_kprintf("TCP/IP initialized!\n");
	}
#endif
}

