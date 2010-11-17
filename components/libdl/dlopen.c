/*
 * File      : dlopen.c
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

void* dlopen(const char *filename, int flags)
{
	rt_module_t module;
	
	RT_ASSERT(filename != RT_NULL);

	/* find in module list */
	module = rt_module_find(filename);
	
	if(module)
	{
		module->nref++;
		return (void*)module;
	}	
	else
	{
		module = rt_module_open(filename);
	}	
}

RTM_EXPORT(dlopen)

