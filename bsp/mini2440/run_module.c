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
static char buffer[4096];

void run_module(const char* filename)
{
	int fd, length;
	char *module_name;
	
	rt_memset(buffer, 0, 4096);
	fd = open(filename, O_RDONLY, 0);
	length = read(fd, buffer, 4096);
	if (length <= 0)
	{
		rt_kprintf("check: read file failed\n");
		close(fd);
		return;
	}
	rt_kprintf("read %d bytes from file\n", length);
	module_name = strrchr(filename, '/');
	rt_module_load(buffer, ++module_name);
	close(fd);
}

FINSH_FUNCTION_EXPORT(run_module, run module from file);
#endif

