/*
 * File      : led.c
 * This file is part of RT-Thread RTOS
 * COPYRIGHT (C) 2006, RT-Thread Develop Team
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
 * 2011-01-13     weety      first version
 */

#include <rtthread.h>
#include <at91sam926x.h>
#include "led.h"

void led_init(void)
{
	at91_sys_write(AT91_PIOC, (1<<8)|(1<<11)|(1<<6));
	at91_sys_write(AT91_PIOC+0x10, (1<<8)|(1<<11)|(1<<6));
	at91_sys_write(AT91_PIOC+0x64, (1<<8)|(1<<11)|(1<<6));
	at91_sys_write(AT91_PIOC+0x30, (1<<8)|(1<<11)|(1<<6));
}

void led_on(int num)
{
	switch(num)
	{
		case 1:
			at91_sys_write(AT91_PIOC+0x34, 1<<8);
			break;
		case 2:
			at91_sys_write(AT91_PIOC+0x34, 1<<11);
			break;
		case 3:
			at91_sys_write(AT91_PIOC+0x34, 1<<6);
			break;
		default:
			break;
	}
	
}

void led_off(int num)
{
	switch(num)
	{
		case 1:
			at91_sys_write(AT91_PIOC+0x30, 1<<8);
			break;
		case 2:
			at91_sys_write(AT91_PIOC+0x30, 1<<11);
			break;
		case 3:
			at91_sys_write(AT91_PIOC+0x30, 1<<6);
			break;
		default:
			break;
	}
	//at91_sys_write(AT91_PIOC+0x30, 1<<8);
}
