/*
 *  RT-Thread module shell implementation.
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

#include "msh.h"
#include <finsh.h>
#include <shell.h>

#define RT_FINSH_ARG_MAX	10
typedef int (*cmd_function_t)(int argc, char** argv);

#ifdef FINSH_USING_MSH
#ifdef FINSH_USING_MSH_DEFAULT
static rt_bool_t __msh_state = RT_TRUE;
#else
static rt_bool_t __msh_state = RT_FALSE;
#endif
rt_bool_t msh_is_used(void)
{
	return __msh_state;
}

static int msh_exit(int argc, char** argv)
{
	/* return to finsh shell mode */
	__msh_state = RT_FALSE;

	return 0;
}
FINSH_FUNCTION_EXPORT_ALIAS(msh_exit, __cmd_exit, return to RT-Thread shell mode.);

static int msh_enter(void)
{
	/* enter module shell mode */
	__msh_state = RT_TRUE;
	return 0;
}
FINSH_FUNCTION_EXPORT_ALIAS(msh_enter, msh, use module shell);

int msh_help(int argc, char** argv)
{
	rt_kprintf("RT-Thread shell commands:\n");
	{
		struct finsh_syscall *index;

		for (index = _syscall_table_begin;
			index < _syscall_table_end;
			FINSH_NEXT_SYSCALL(index))
		{
			if (strncmp(index->name, "__cmd_", 6) != 0) continue;

			rt_kprintf("%s ", &index->name[6]);
		}
	}
	rt_kprintf("\n");

	return 0;
}
FINSH_FUNCTION_EXPORT_ALIAS(msh_help, __cmd_help, "RT-Thread shell help.");

static int msh_split(char* cmd, rt_size_t length, char* argv[RT_FINSH_ARG_MAX])
{
	char *ptr;
	rt_size_t position;
	rt_size_t argc;

	ptr = cmd;
	position = 0; argc = 0;

	while (position < length)
	{
		/* strip bank and tab */
		while ((*ptr == ' ' || *ptr == '\t') && position < length)
		{
			*ptr = '\0';
			ptr ++; position ++;
		}
		if (position >= length) break;

		/* handle string */
		if (*ptr == '"')
		{
			ptr ++; position ++;
			argv[argc] = ptr; argc ++;

			/* skip this string */
			while (*ptr != '"' && position < length)
			{
				if (*ptr == '\\')
				{
					if (*(ptr + 1) == '"')
					{
						ptr ++; position ++;
					}
				}
				ptr ++; position ++;
			}
			if (position >= length) break;

			/* skip '"' */
			*ptr = '\0'; ptr ++; position ++;
		}
		else
		{
			argv[argc] = ptr;
			argc ++;
			while ((*ptr != ' ' && *ptr != '\t') && position < length)
			{
				ptr ++; position ++;
			}
			if (position >= length) break;
		}
	}

	return argc;
}

static cmd_function_t msh_get_cmd(char *cmd)
{
	struct finsh_syscall *index;
	cmd_function_t cmd_func = RT_NULL;

	for (index = _syscall_table_begin;
		index < _syscall_table_end;
		FINSH_NEXT_SYSCALL(index))
	{
		if (strncmp(index->name, "__cmd_", 6) != 0) continue;
		
		if (strcmp(&index->name[6], cmd) == 0)
		{
			cmd_func = (cmd_function_t)index->func;
			break;
		}
	}

	return cmd_func;
}

int msh_exec(char* cmd, rt_size_t length)
{
	int argc;
	char *argv[RT_FINSH_ARG_MAX];

	cmd_function_t cmd_func;

	memset(argv, 0x00, sizeof(argv));
	argc = msh_split(cmd, length, argv);
	if (argc == 0) return -1;

	/* get command in internal commands */
	cmd_func = msh_get_cmd(argv[0]);
	if (cmd_func == RT_NULL) 
	{
		rt_kprintf("%s: command not found\n", argv[0]);
		return -1;
	}

	/* exec this command */
	return cmd_func(argc, argv);
}

static int str_common(const char *str1, const char *str2)
{
	const char *str = str1;

	while ((*str != 0) && (*str2 != 0) && (*str == *str2))
	{
		str ++;
		str2 ++;
	}

	return (str - str1);
}

void msh_auto_complete(char *prefix)
{
	rt_uint16_t func_cnt;
	int length, min_length;
	const char *name_ptr, *cmd_name;
	struct finsh_syscall *index;

	func_cnt = 0;
	min_length = 0;
	name_ptr = RT_NULL;

	if (*prefix == '\0') 
	{
		msh_help(0, RT_NULL);
		return;
	}

	/* checks in internal command */
	{
		for (index = _syscall_table_begin; index < _syscall_table_end; FINSH_NEXT_SYSCALL(index))
		{
			/* skip finsh shell function */
			if (strncmp(index->name, "__cmd_", 6) != 0) continue;

			cmd_name = (const char*) &index->name[6];
			if (strncmp(prefix, cmd_name, strlen(prefix)) == 0)
			{
				if (func_cnt == 0)
				{
					/* set name_ptr */
					name_ptr = cmd_name;

					/* set initial length */
					min_length = strlen(name_ptr);
				}

				func_cnt ++;

				length = str_common(name_ptr, cmd_name);
				if (length < min_length)
					min_length = length;

				rt_kprintf("%s\n", cmd_name);
			}
		}
	}

	/* auto complete string */
	if (name_ptr != NULL)
	{
		rt_strncpy(prefix, name_ptr, min_length);
	}

	return ;
}
#endif
