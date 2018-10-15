/*
 * Copyright (c) 2006-2018, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2008-08-14     Bernard      the first version
 */

#include <rtthread.h>
#include <sys/types.h>

#if !defined (RT_USING_NEWLIB) && defined (RT_USING_MINILIBC)
#include "ctype.h"

int isprint (int ch)
{
	ch&=0x7f;
	return (ch>=32 && ch<127);
}

int isalpha(int ch)
{
	return (unsigned int)((ch | 0x20) - 'a') < 26u;
}

int isdigit (int ch)
{
	return (unsigned int)(ch - '0') < 10u;
}

int isspace(int ch)
{
	switch(ch)
	{
	case ' ':
	case '\n':
	case '\f':
	case '\r':
	case '\t':
	case '\v':
		return 1;
	default:
		return 0; 
	}    
}

#endif
