/*
 * File      : stdlib.h
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

#ifndef __STDLIB_H__
#define __STDLIB_H__

#if !defined (RT_USING_NEWLIB) && defined (RT_USING_MINILIBC)
int atoi(const char *nptr);
#endif

#define malloc  rt_malloc
#define free    rt_free
#define realloc rt_realloc
#define calloc  rt_calloc

#endif
