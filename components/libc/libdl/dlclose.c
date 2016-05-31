/*
 * File      : dlclose.c
 * This file is part of RT-Thread RTOS
 * COPYRIGHT (C) 2006 - 2010, RT-Thread Development Team
 *
 * The license and distribution terms for this file may be
 * found in the file LICENSE in this distribution or at
 * http://www.rt-thread.org/license/LICENSE
 *
 * Change Logs:
 * Date           Author		Notes
 * 2010-11-17      yi.qiu	first version
 */

#include <rtthread.h>
#include <rtm.h>

int dlclose (void *handle)
{
	rt_module_t module;
	
	RT_ASSERT(handle != RT_NULL);
	
	module = (rt_module_t)handle;
	module->nref--;
	
	if(module->nref <= 0)
	{
		rt_module_unload(module);
	}	

	return RT_TRUE;
}

RTM_EXPORT(dlclose)

