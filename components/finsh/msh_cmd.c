/*
 *  internal commands for RT-Thread module shell
 *
 * COPYRIGHT (C) 2013, Shanghai Real-Thread Technology Co., Ltd
 *
 *  This file is part of RT-Thread (http://www.rt-thread.org)
 *  Maintainer: bernard.xiong <bernard.xiong at gmail.com>
 *
 *  All rights reserved.
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
 * 2013-03-30     Bernard      the first verion for FinSH
 */

#include <rtthread.h>
#include <finsh.h>

#include "msh.h"

#ifdef FINSH_USING_MSH
#ifdef RT_USING_DFS
#include <dfs_posix.h>

#ifdef DFS_USING_WORKDIR
extern char working_directory[];
#endif

int cmd_ls(int argc, char** argv)
{
    extern void ls(const char *pathname);

    if (argc == 1)
    {
#ifdef DFS_USING_WORKDIR
        ls(working_directory);
#else
        ls("/");
#endif
    }
    else 
    {
        ls(argv[1]);
    }

    return 0;
}
FINSH_FUNCTION_EXPORT_ALIAS(cmd_ls, __cmd_ls, "List information about the FILEs.");

int cmd_cp(int argc, char** argv)
{
    void copy(const char *src, const char *dst);

    if (argc != 3)
    {
        rt_kprintf("Usage: cp SOURCE DEST\n");
        rt_kprintf("Copy SOURCE to DEST.\n");
    }
    else
    {
        copy(argv[1], argv[2]);
    }

    return 0;
}
FINSH_FUNCTION_EXPORT_ALIAS(cmd_cp, __cmd_cp, "Copy SOURCE to DEST.");

int cmd_mv(int argc, char** argv)
{
    if (argc != 3)
    {
        rt_kprintf("Usage: mv SOURCE DEST\n");
        rt_kprintf("Rename SOURCE to DEST, or move SOURCE(s) to DIRECTORY.\n");
    }
    else
    {
        rt_kprintf("%s => %s\n", argv[1], argv[2]);
    }

    return 0;
}
FINSH_FUNCTION_EXPORT_ALIAS(cmd_mv, __cmd_mv, "Rename SOURCE to DEST.");

int cmd_cat(int argc, char** argv)
{
    int index;
    extern void cat(const char* filename);

    if (argc == 1)
    {
        rt_kprintf("Usage: cat [FILE]...\n");
        rt_kprintf("Concatenate FILE(s)\n");
		return 0;
    }

    for (index = 1; index < argc; index ++)
    {
        cat(argv[index]);
    }

    return 0;
}
FINSH_FUNCTION_EXPORT_ALIAS(cmd_cat, __cmd_cat, "Concatenate FILE(s)");

int cmd_rm(int argc, char** argv)
{
    int index;

    if (argc == 1)
    {
        rt_kprintf("Usage: rm FILE...\n");
        rt_kprintf("Remove (unlink) the FILE(s).\n");
		return 0;
    }

    for (index = 1; index < argc; index ++)
    {
        unlink(argv[index]);
    }

    return 0;
}
FINSH_FUNCTION_EXPORT_ALIAS(cmd_rm, __cmd_rm, "Remove (unlink) the FILE(s).");

#ifdef DFS_USING_WORKDIR
int cmd_cd(int argc, char** argv)
{
    if (argc == 1)
    {
        rt_kprintf("%s\n", working_directory);
    }
    else if (argc == 2)
    {
        chdir(argv[1]);
    }

    return 0;
}
FINSH_FUNCTION_EXPORT_ALIAS(cmd_cd, __cmd_cd, Change the shell working directory.);

int cmd_pwd(int argc, char** argv)
{
	rt_kprintf("%s\n", working_directory);
	return 0;
}
FINSH_FUNCTION_EXPORT_ALIAS(cmd_pwd, __cmd_pwd, Print the name of the current working directory.);
#endif

int cmd_mkdir(int argc, char** argv)
{
	if (argc == 1)
	{
		rt_kprintf("Usage: mkdir [OPTION] DIRECTORY\n");
		rt_kprintf("Create the DIRECTORY, if they do not already exist.\n");
	}
	else
	{
		mkdir(argv[1], 0);
	}

	return 0;
}
FINSH_FUNCTION_EXPORT_ALIAS(cmd_mkdir, __cmd_mkdir, Create the DIRECTORY.);

#endif

int cmd_ps(int argc, char** argv)
{
    extern long list_thread(void);

    list_thread();
    return 0;
}
FINSH_FUNCTION_EXPORT_ALIAS(cmd_ps, __cmd_ps, "list threads in the system");

int cmd_i(int argc, char** argv)
{
    return cmd_ps(argc, argv);
}
FINSH_FUNCTION_EXPORT_ALIAS(cmd_i, __cmd_i, "list threads in the system");

int cmd_time(int argc, char** argv)
{
    return 0;
}
FINSH_FUNCTION_EXPORT_ALIAS(cmd_time, __cmd_time, "exec command with time");

int cmd_free(int argc, char** argv)
{
    extern void list_mem(void);

    list_mem();
    return 0;
}
FINSH_FUNCTION_EXPORT_ALIAS(cmd_free, __cmd_free, "show the memory usage in the system");

// --------------------------------------------------------------------------
int cli_list(int argc, char **argv)
{
	return msh_help(argc, argv);
}
FINSH_FUNCTION_EXPORT_ALIAS(cli_list, __cmd_list, "list rtt support commands.");

int cli_clear(int argc, char **argv)
{
	rt_kprintf("\33[2J\33[1H");
	return RT_EOK;
}
FINSH_FUNCTION_EXPORT_ALIAS(cli_clear, __cmd_cls, "clear display.");

int cli_show_version(void)
{
	extern void rt_show_version(void);
	rt_show_version();
	return 0;
}
FINSH_FUNCTION_EXPORT_ALIAS(cli_show_version, __cmd_version, "show RT - Thread version information.");

int cli_show_timer(void)
{
	extern long list_timer(void);
	list_timer();
	return 0;
}
FINSH_FUNCTION_EXPORT_ALIAS(cli_show_timer, __cmd_timer, "show timers in RT-Thread OS.");

int cli_show_thread(void)
{
	extern long list_thread(void);
	list_thread();
	return 0;
}
FINSH_FUNCTION_EXPORT_ALIAS(cli_show_thread, __cmd_thread, "show RT-Thread OS Threads.");

#ifdef RT_USING_SEMAPHORE
int cli_show_mem(void)
{
	extern long list_sem(void);
	list_mem();
	return 0;
}
FINSH_FUNCTION_EXPORT_ALIAS(cli_show_mem, __cmd_mem, "show RT-Thread OS memory using.");
#endif

#ifdef RT_USING_EVENT
int cli_show_event(void)
{
	extern long list_event(void);
	list_event();
	return 0;
}
FINSH_FUNCTION_EXPORT_ALIAS(cli_show_event, __cmd_event, "show events in RT-Thread OS.");
#endif

#ifdef RT_USING_MUTEX
int cli_show_metux(void)
{
	extern long list_mutex(void);
	list_mutex();
	return 0;
}
FINSH_FUNCTION_EXPORT_ALIAS(cli_show_metux, __cmd_mutex, "show mutex in RT-Thread OS.");
#endif

#ifdef RT_USING_MAILBOX
int cli_show_mailbox(void)
{
	extern long list_mailbox(void);
	list_mailbox();
	return 0;
}
FINSH_FUNCTION_EXPORT_ALIAS(cli_show_mailbox, __cmd_mailbox, "show mailbox in RT-Thread OS.");
#endif

#ifdef RT_USING_MESSAGEQUEUE
int cli_show_msgqueue(void)
{
	extern long list_msgqueue(void);
	list_msgqueue();
	return 0;
}
FINSH_FUNCTION_EXPORT_ALIAS(cli_show_msgqueue, __cmd_msgqueue, "show message queue in RT-Thread OS.");
#endif

#ifdef RT_USING_MEMHEAP
int cli_show_memheap(void)
{
	extern long list_memheap(void);
	list_memheap();
	return 0;
}
FINSH_FUNCTION_EXPORT_ALIAS(cli_show_memheap, __cmd_memheap, "show memory heap in RT-Thread OS.");
#endif

#ifdef RT_USING_MEMPOOL
int cli_show_mempool(void)
{
	extern long list_mempool(void);
	list_mempool();
	return 0;
}
FINSH_FUNCTION_EXPORT_ALIAS(cli_show_mempool, __cmd_mempool, "show memory pool in RT-Thread OS.");
#endif

#ifdef RT_USING_DEVICE
int cli_show_device(void)
{
	extern long list_device(void);
	list_device();
	return 0;
}
FINSH_FUNCTION_EXPORT_ALIAS(cli_show_device, __cmd_dev, "show devices in RT-Thread OS.");
#endif

#ifdef RT_USING_MODULE
int cli_show_module(int argc, char **argv)
{
	int i;
	extern int list_module(void);
	extern int list_mod_detail(const char *name);

	if (argc == 1)
	{
		list_module();
	}
	else
	{
		for (i = 1; i < argc, ++i)
		{
			list_mod_detail(argv[i]);
		}
	}
	
	return 0;
}
FINSH_FUNCTION_EXPORT_ALIAS(cli_show_module, __cmd_module, "show modules in RT-Thread OS.");
#endif

int cli_debug(int argc, char **argv)
{
	int i;

	for (i = 0; i < argc; ++i)
	{
		rt_kprintf("argv[%d]: %s\n", i, argv[i]);
	}
}
FINSH_FUNCTION_EXPORT_ALIAS(cli_debug, __cmd_debug, "cli function debug.");

#endif
