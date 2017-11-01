/*
 * File      : ctype.c
 * This file is part of RT-Thread RTOS
 * COPYRIGHT (C) 2008, RT-Thread Development Team
 *
 * The license and distribution terms for this file may be
 * found in the file LICENSE in this distribution or at
 * http://www.rt-thread.org/license/LICENSE
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
