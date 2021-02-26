/*
 * File      : cpu.c
 * This file is part of RT-Thread RTOS
 * COPYRIGHT (C) 2006 - 2013, RT-Thread Development Team
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
 * 2013-7-14      Peng Fan     sep6200 implementation
 */

#include <rthw.h>
#include <rtthread.h>
#include <sep6200.h>

/**
 * @addtogroup sep6200
 */
/*@{*/

#ifdef __GNUC__
rt_inline void cache_invalid(void)
{
	__asm__ volatile ("movc	p0.c5, r1, #28\n"
			"nop;nop;nop;nop;nop;nop;nop;nop;\n"
			:
			:
			:"memory", "cc"
			);
}

rt_inline void cache_enable(void)
{
	__asm__ volatile ( "movc r1, p0.c1, #0\n"
			"or r1, r1, #0xc\n"
			"movc p0.c1, r1, #0\n"
			"nop;nop;nop;nop;nop;nop;nop;nop;\n"
			:
			:
			:"r0", "memory", "cc");
}

rt_inline void clean_dcache(void)
{
    __asm__ volatile ( "mov ip, #0\n"
               "movc p0.c5, ip, #10\n"
               "nop; nop; nop; nop; nop; nop; nop; nop\n"
               :
	       :
	       :"ip", "memory", "cc");
}

rt_inline rt_uint32_t icache_status(void)
{
    rt_uint32_t ret;

     __asm__ volatile ( "movc %0, p0.c1, #0\n"
                "and %0, %0, #8\n"
                : "=&r" (ret)
                :
                :"memory", "cc");

    return ret;
}

rt_inline rt_uint32_t dcache_status(void)
{
    rt_uint32_t ret;

    __asm__ volatile ( "movc %0, p0.c1, #0\n"
               "and %0, %0, #4\n"
               : "=&r" (ret)
               :
               :"memory", "cc");

     return ret;
}

rt_inline void dcache_flush(void)
{
	__asm__ volatile ( "mov ip, #0\n"
              "movc p0.c5, ip, #14\n"
              "nop; nop; nop; nop; nop; nop; nop; nop\n"
              :
              :
              : "ip" );
}

rt_inline void icache_invalid(void)
{
	 __asm__ volatile ( "mov r0, #0\n"
               "movc p0.c5, r0, #20\n"
               "nop; nop; nop; nop; nop; nop; nop; nop\n"
               :
               :
               :"r0", "memory", "cc");
}

rt_inline void dcache_invalid(void)
{
    __asm__ volatile ( "mov r0, #0\n"
                "movc p0.c5, r0, #12\n"
               "nop; nop; nop; nop; nop; nop; nop; nop\n"
               :
               :
               :"r0", "memory", "cc");
}

rt_inline void icache_disable(void)
{
	icache_invalid();
	__asm__ volatile ( "movc r0, p0.c1, #0\n"
               "andn r0, r0, #8\n"
               "movc p0.c1, r0, #0\n"
               :
               :
               :"r0", "memory", "cc");
}

rt_inline void dcache_disable(void)
{
	dcache_flush();
	__asm__ volatile ( "movc r0, p0.c1, #0\n"
               "andn r0, r0, #20\n"
               "movc p0.c1, r0, #0\n"
               :
               :
               :"r0", "memory", "cc");

}

rt_inline void icache_enable(void)
{
    __asm__ volatile ( "mov r0, #0\n"
               "movc p0.c5, r0, #20\n"
               "nop; nop; nop; nop; nop; nop; nop; nop\n"
               :
               :
               :"r0", "memory", "cc");

    __asm__ volatile ( "movc r0, p0.c1, #0\n"
               "or r0, r0, #8\n"
               "movc p0.c1, r0, #0\n"
               :
               :
               :"r0", "memory", "cc");
}

rt_inline void dcache_enable(void)
{
    __asm__ volatile ( "mov r0, #0\n"
           "movc p0.c5, r0, #12\n"
           "nop; nop; nop; nop; nop; nop; nop; nop\n"
           :
           :
           :"r0", "memory", "cc");

    __asm__ volatile ( "movc r0, p0.c1, #0\n"
           "or r0, r0, #20\n"
           "movc p0.c1, r0, #0\n"
           :
           :
           :"r0", "memory", "cc");
}
#endif


/**
 * enable I-Cache
 *
 */
void rt_hw_cpu_icache_enable()
{
	icache_enable();
}

/**
 * disable I-Cache
 *
 */
void rt_hw_cpu_icache_disable()
{
	icache_disable();
}

/**
 * return the status of I-Cache
 *
 */
rt_base_t rt_hw_cpu_icache_status()
{
	return icache_status();
}

/**
 * enable D-Cache
 *
 */
void rt_hw_cpu_dcache_enable()
{
	dcache_enable();
}

/**
 * disable D-Cache
 *
 */
void rt_hw_cpu_dcache_disable()
{
	dcache_disable();
}

/**
 * return the status of D-Cache
 *
 */
rt_base_t rt_hw_cpu_dcache_status()
{
	return dcache_status();
}

static void sep6200_reset(rt_uint32_t addr)
{
     __asm__ volatile ( "mov ip, #0\n"
		     "movc p0.c5, ip, #28\n" /*Cache invalidate all*/
		     "movc p0.c6, ip, #6\n" /*TLB invalidate all*/
		     "nop;nop;nop;nop;nop;nop;nop;nop;\n"
		     "movc ip, p0.c1, #0\n" /*ctrl register*/
		     "andn ip, ip, #0x000f\n" /*disable caches and mmu*/
		     "movc p0.c1, ip, #0\n"
		     "nop\n"
		     "mov pc, %0\n"
		     "nop;nop;nop;nop;nop;nop;nop;nop;\n"
		      : "=&r" (addr)
		      :
		      :"memory", "cc");
}

static void sep6200_poweroff(void)
{
	rt_kprintf("sep6200 power off not implemented\n");
  while(1);
}

/**
 * reset cpu by dog's time-out
 *
 */
RT_WEAK void rt_hw_cpu_reset()
{

	rt_kprintf("Soft reset, Restarting system...\n");
	sep6200_reset(0);

	while(1);	/* loop forever and wait for reset to happen */

	/* NEVER REACHED */
}

/**
 *  shutdown CPU
 *
 */
RT_WEAK void rt_hw_cpu_shutdown()
{
	rt_uint32_t level;
	rt_kprintf("shutdown...\n");

	level = rt_hw_interrupt_disable();
	sep6200_poweroff();
	while (level)
	{
		RT_ASSERT(0);
	}
}

/*@}*/
