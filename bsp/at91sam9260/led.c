/*
 * File      : led.c
 * This file is part of RT-Thread RTOS
 * COPYRIGHT (C) 2006, RT-Thread Develop Team
 *
 * The license and distribution terms for this file may be
 * found in the file LICENSE in this distribution or at
 * http://openlab.rt-thread.com/license/LICENSE
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
