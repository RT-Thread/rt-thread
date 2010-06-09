/*
 * File      : finsh_error.c
 * This file is part of RT-Thread RTOS
 * COPYRIGHT (C) 2006 - 2010, RT-Thread Development Team
 *
 * The license and distribution terms for this file may be
 * found in the file LICENSE in this distribution or at
 * http://www.rt-thread.org/license/LICENSE
 *
 * Change Logs:
 * Date           Author       Notes
 * 2010-03-22     Bernard      first version
 */
#include "finsh_error.h"

u_char global_errno;

static const char* finsh_error_string_table[] =
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
