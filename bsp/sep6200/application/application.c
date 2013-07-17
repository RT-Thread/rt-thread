/*
 * File      : application.c
 * This file is part of RT-Thread RTOS
 * COPYRIGHT (C) 2006 - 2013, RT-Thread Development Team
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
 * Date           Author		Notes
 * 2013-7-14      Peng Fan  Simple application
 */

/**
 * @addtogroup sep6200
 */

/*@{*/

#include "board.h"
#include <rtthread.h>

#define RT_INIT_THREAD_STACK_SIZE (2*1024)

void rt_init_thread_entry(void *parameter)
{
  while(1){
    rt_thread_sleep(200);
    rt_hw_console_output("init thread\n");
  }
}

void rt_test1_thread_entry(void *parameter)
{
  while(1){
    rt_thread_sleep(800);
    rt_hw_console_output("test1 thread\n");
  }
}

void rt_test2_thread_entry(void *parameter)
{
  while(1){
    rt_thread_sleep(300);
    rt_hw_console_output("test2 thread\n");
  }
}

int rt_application_init(void)
{
	rt_thread_t init_thread;
	rt_thread_t test1_thread;
	rt_thread_t test2_thread;

	init_thread = rt_thread_create("init",
								rt_init_thread_entry, RT_NULL,
								RT_INIT_THREAD_STACK_SIZE, 8, 20);

	test1_thread = rt_thread_create("test1",
								rt_test1_thread_entry, RT_NULL,
								512, 200, 20);
	test2_thread = rt_thread_create("test2",
								rt_test2_thread_entry, RT_NULL,
								512, 200, 20);

	if (init_thread != RT_NULL)
		rt_thread_startup(init_thread);

	if (test1_thread != RT_NULL)
		rt_thread_startup(test1_thread);

	if (test2_thread != RT_NULL)
		rt_thread_startup(test2_thread);

	return 0;
}

/*@}*/
