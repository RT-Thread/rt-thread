/*
 * File      : __umodsi3.c
 * This file is part of RT-Thread RTOS
 * COPYRIGHT (C) 2006, RT-Thread Develop Team
 *
 * The license and distribution terms for this file may be
 * found in the file LICENSE in this distribution or at
 * http://openlab.rt-thread.com/license/LICENSE
 *
 * Change Logs:
 * Date           Author       Notes
 * 2006-10-09     Bernard      the first version for i386
 */

#include <rtthread.h>

typedef rt_uint32_t uint32_t;
typedef rt_int32_t int32_t;

uint32_t __umodsi3(uint32_t num, uint32_t den)
{
	register uint32_t quot = 0, qbit = 1;

	if (den == 0)
	{
		asm volatile ("int $0");
		return 0;	/* if trap returns... */
	}

	/* left-justify denominator and count shift */
	while ((int32_t) den >= 0)
	{
		den <<= 1;
		qbit <<= 1;
	}

	while (qbit)
	{
		if (den <= num)
		{
			num -= den;
			quot += qbit;
		}
		den >>= 1;
		qbit >>= 1;
	}

	return num;
}
