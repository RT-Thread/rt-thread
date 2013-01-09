/*
 * File      : newlib_stub.c
 * This file is part of RT-Thread RTOS
 * COPYRIGHT (C) 2009 - 2012, RT-Thread Development Team
 *
 * The license and distribution terms for this file may be
 * found in the file LICENSE in this distribution or at
 * http://www.rt-thread.org/license/LICENSE
 *
 * Change Logs:
 * Date           Author       Notes
 */

#include <rtthread.h>

#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>

/* some newlib leaked function in CodeSourcery G++ Lite for MIPS version */

int getpid(void)
{
	return 0;
}

int gettimeofday(struct timeval *__tp, void *__tzp)
{
	struct timespec tp;

	if (libc_get_time(&tp) == 0)
	{
		if (__tp != RT_NULL)
		{
			__tp->tv_sec  = tp.tv_sec;
			__tp->tv_usec = tp.tv_nsec * 1000UL;
		}

		return tp.tv_sec;
	}

	return 0;
}
