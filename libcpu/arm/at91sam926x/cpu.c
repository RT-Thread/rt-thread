/*
 * File      : cpu.c
 * This file is part of RT-Thread RTOS
 * COPYRIGHT (C) 2006, RT-Thread Develop Team
 *
 * The license and distribution terms for this file may be
 * found in the file LICENSE in this distribution or at
 * http://openlab.rt-thread.com/license/LICENSE
 *
 * Change Logs:
 * Date           Author       Notes
 * 2011-01-13     weety      modified from mini2440
 */

#include <rthw.h>
#include <rtthread.h>
#include "at91sam926x.h"

/**
 * @addtogroup AT91SAM926X
 */
/*@{*/

#define ICACHE_MASK	(rt_uint32_t)(1 << 12)
#define DCACHE_MASK	(rt_uint32_t)(1 << 2)

#ifdef __GNUC__
rt_inline rt_uint32_t cp15_rd(void)
{
	rt_uint32_t i;

	asm ("mrc p15, 0, %0, c1, c0, 0":"=r" (i));
	return i;
}

rt_inline void cache_enable(rt_uint32_t bit)
{
	__asm__ __volatile__(			\
		"mrc  p15,0,r0,c1,c0,0\n\t"	\
		"orr  r0,r0,%0\n\t"			\
	   	"mcr  p15,0,r0,c1,c0,0"		\
		:							\
		:"r" (bit)					\
		:"memory");
}

rt_inline void cache_disable(rt_uint32_t bit)
{
	__asm__ __volatile__(			\
		"mrc  p15,0,r0,c1,c0,0\n\t"	\
		"bic  r0,r0,%0\n\t"			\
		"mcr  p15,0,r0,c1,c0,0"		\
		:							\
		:"r" (bit)					\
		:"memory");
}
#endif

#ifdef __CC_ARM
rt_inline rt_uint32_t cp15_rd(void)
{
	rt_uint32_t i;

	__asm
	{
		mrc p15, 0, i, c1, c0, 0
	}

	return i;
}

rt_inline void cache_enable(rt_uint32_t bit)
{
	rt_uint32_t value;

	__asm
	{
		mrc p15, 0, value, c1, c0, 0
		orr value, value, bit
		mcr p15, 0, value, c1, c0, 0
	}
}

rt_inline void cache_disable(rt_uint32_t bit)
{
	rt_uint32_t value;

	__asm
	{
		mrc p15, 0, value, c1, c0, 0
		bic value, value, bit
		mcr p15, 0, value, c1, c0, 0
	}
}
#endif

/**
 * enable I-Cache
 *
 */
void rt_hw_cpu_icache_enable()
{
	cache_enable(ICACHE_MASK);
}

/**
 * disable I-Cache
 *
 */
void rt_hw_cpu_icache_disable()
{
	cache_disable(ICACHE_MASK);
}

/**
 * return the status of I-Cache
 *
 */
rt_base_t rt_hw_cpu_icache_status()
{
	return (cp15_rd() & ICACHE_MASK);
}

/**
 * enable D-Cache
 *
 */
void rt_hw_cpu_dcache_enable()
{
	cache_enable(DCACHE_MASK);
}

/**
 * disable D-Cache
 *
 */
void rt_hw_cpu_dcache_disable()
{
	cache_disable(DCACHE_MASK);
}

/**
 * return the status of D-Cache
 *
 */
rt_base_t rt_hw_cpu_dcache_status()
{
	return (cp15_rd() & DCACHE_MASK);
}

static void at91sam9260_reset(void)
{
	at91_sys_write(AT91_RSTC_CR, AT91_RSTC_KEY | AT91_RSTC_PROCRST | AT91_RSTC_PERRST);
}

static void at91sam9260_poweroff(void)
{
	at91_sys_write(AT91_SHDW_CR, AT91_SHDW_KEY | AT91_SHDW_SHDW);
}

/**
 * reset cpu by dog's time-out
 *
 */
void rt_hw_cpu_reset()
{
	
	rt_kprintf("Restarting system...\n");
	at91sam9260_reset();

	while(1);	/* loop forever and wait for reset to happen */

	/* NEVER REACHED */
}

/**
 *  shutdown CPU
 *
 */
void rt_hw_cpu_shutdown()
{
	rt_uint32_t level;
	rt_kprintf("shutdown...\n");

	level = rt_hw_interrupt_disable();
	at91sam9260_poweroff();
	while (level)
	{
		RT_ASSERT(0);
	}
}

/*@}*/
