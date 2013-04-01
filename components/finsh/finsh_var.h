/*
 *  Variable implementation in finsh shell.
 *
 * COPYRIGHT (C) 2006 - 2013, RT-Thread Development Team
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
 * 2010-03-22     Bernard      first version
 */
#ifndef __FINSH_VAR_H__
#define __FINSH_VAR_H__

#include <finsh.h>

/*
 * The variable in finsh is put in data segment as a global variable.
 * The 'finsh_var' structure presents the structure of variable in data segment.
 */
struct finsh_var
{
	char name[FINSH_NAME_MAX + 1];	/* the name of variable */

	u_char type;					/* the type of variable */

	/* variable value */
	union {
		char 	char_value;
		short 	short_value;
		int		int_value;
		long	long_value;
		void*	ptr;
	}value;
};
extern struct finsh_var global_variable[];

int finsh_var_init(void);
int finsh_var_insert(const char* name, int type);
int finsh_var_delete(const char* name);
struct finsh_var* finsh_var_lookup(const char* name);

#endif
