/*
 * File      : application.c
 * This file is part of RT-Thread RTOS
 * COPYRIGHT (C) 2006 - 2012, RT-Thread Development Team
 *
 * The license and distribution terms for this file may be
 * found in the file LICENSE in this distribution or at
 * http://www.rt-thread.org/license/LICENSE
 *
 * Change Logs:
 * Date           Author		Notes
 * 2007-11-20     Yi.Qiu		add rtgui application
 * 2008-6-28      Bernard		no rtgui init
 * 2013-7-14      Peng Fan  modified from mini4020
 */

/**
 * @addtogroup sep6200
 */

/*@{*/

#include "board.h"
#include <rtthread.h>

#ifdef RT_USING_DFS
#include <dfs_init.h>
#include <dfs_elm.h>
#include <dfs_fs.h>
#include <dfs_posix.h>
#endif

#ifdef RT_USING_RTGUI
#include <rtgui/rtgui.h>
extern void radio_rtgui_init(void);
#endif

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
