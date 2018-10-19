/*
 * Copyright (c) 2006-2018, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 */
#include <rtthread.h>

void init_thread(void *parameter)
{
	rt_components_init();

	return ;
}

int rt_application_init(void)
{
	rt_thread_t tid;

	tid = rt_thread_create("init", init_thread, RT_NULL, 
		4096, RT_THREAD_PRIORITY_MAX/3, 20);
	if (tid) rt_thread_startup(tid);

	return 0;
}
