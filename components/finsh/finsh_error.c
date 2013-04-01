/*
 *  error number for finsh shell.
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
 * 2010-03-22     Bernard      first version
 */
#include "finsh_error.h"

u_char global_errno;

static const char * finsh_error_string_table[] =
{
    "No error",
	"Invalid token",
	"Expect a type",
	"Unknown type",
	"Variable exist",
	"Expect a operater",
	"Memory full",
	"Unknown operator",
	"Unknown node",
	"Expect a character",
	"Unexpect end",
	"Unknown token",
	"Float not supported",
	"Unknown symbol",
	"Null node"
};

int finsh_error_init()
{
	global_errno = FINSH_ERROR_OK;

	return 0;
}

int finsh_error_set(u_char type)
{
	global_errno = type;

	return 0;
}

u_char finsh_errno()
{
	return global_errno;
}

const char* finsh_error_string(u_char type)
{
	return finsh_error_string_table[type];
}
