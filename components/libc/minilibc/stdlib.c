/*
 * File      : stdlib.c
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

#if !defined (RT_USING_NEWLIB) && defined (RT_USING_MINILIBC)
#include "stdlib.h"

int atoi(const char* s)
{
	long int v=0;
	int sign=1;
	while ( *s == ' '  ||  (unsigned int)(*s - 9) < 5u) s++;
	switch (*s)
	{
	case '-':
		sign=-1;
	case '+':
		++s;
	}
	while ((unsigned int) (*s - '0') < 10u)
	{
		v=v*10+*s-'0';
		++s;
	}
	return sign==-1?-v:v;
}

long int atol(const char* s) 
{
	long int v=0;
	int sign=0;
	while ( *s == ' '  ||  (unsigned int)(*s - 9) < 5u) ++s;
	switch (*s) 
	{
		case '-': sign=-1;
		case '+': ++s;
	}
	while ((unsigned int) (*s - '0') < 10u) 
	{
		v=v*10+*s-'0'; ++s;
	}
	return sign?-v:v;
}

void *malloc(size_t size)
{
	return rt_malloc(size);
}

void free(void *ptr)
{
	rt_free(ptr);
}

void *realloc(void *ptr, size_t size)
{
	return rt_realloc(ptr, size);
}

void *calloc(size_t nelem, size_t elsize)
{
	return rt_calloc(nelem, elsize);
}

#endif
