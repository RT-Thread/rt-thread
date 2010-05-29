/*
 * File      : module.c
 * This file is part of RT-Thread RTOS
 * COPYRIGHT (C) 2006 - 2010, RT-Thread Development Team
 *
 * The license and distribution terms for this file may be
 * found in the file LICENSE in this distribution or at
 * http://www.rt-thread.org/license/LICENSE
 *
 * Change Logs:
 * Date           Author		Notes
 * 2010-04-12      yi.qiu	first version
 */

#include <rtthread.h>
#include <dfs_posix.h>
#include "string.h"

#if defined(RT_USING_FINSH) && defined(RT_USING_MODULE)
#include <finsh.h>

extern struct rt_module* rt_module_load(void* module_ptr, const rt_uint8_t* name);
extern void rt_module_run(struct rt_module* module);

void run_module(const char* filename)
{
	int fd, length;
	char *module_name;
	struct rt_module* module;
	struct dfs_stat s;
	char *buffer;
	
	stat(filename, &s);
	buffer = (char *)rt_malloc(s.st_size);
	fd = open(filename, O_RDONLY, 0);
	length = read(fd, buffer, s.st_size);
	if (length <= 0)
	{
		rt_kprintf("check: read file failed\n");
		close(fd);
		return;
	}
	rt_kprintf("read %d bytes from file\n", length);
	module_name = strrchr(filename, '/');
	module = rt_module_load((void *)buffer, ++module_name);
	if(module != RT_NULL)
	{
		rt_module_run(module);
	}
	
	close(fd);
}

FINSH_FUNCTION_EXPORT(run_module, run module from file);
#endif

