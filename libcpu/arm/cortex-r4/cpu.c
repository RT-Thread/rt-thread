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
 * 2008-12-11     XuXinming    first version
 * 2013-05-24     Grissiom     port to RM48x50
 */

#include <rtthread.h>

/**
 * @addtogroup RM48x50
 */
/*@{*/

/**
 * this function will reset CPU
 *
 */
void rt_hw_cpu_reset()
{
}

/**
 * this function will shutdown CPU
 *
 */
void rt_hw_cpu_shutdown()
{
	rt_kprintf("shutdown...\n");

	while (1);
}

#ifdef __TI_COMPILER_VERSION__
#ifdef RT_USING_CPU_FFS
int __rt_ffs(int value)
{
	if (value == 0)
		return value;

	__asm("    rsb r1, r0, #0");
	__asm("    and r1, r1, r0");
	__asm("    clz r1, r1");
	__asm("    rsb r0, r1, #32");
}
#endif

void rt_hw_cpu_icache_enable()
{
    __asm("   MRC p15, #0, r1, c1, c0, #0 ; Read SCTLR configuration data");
    __asm("   ORR r1,  r1, #0x1 <<12 ; instruction cache enable");
    __asm("   MCR p15, #0, r0, c7, c5, #0 ; Invalidate entire instruction cache, r0 is ignored");
    __asm("   MCR p15, #0, r1, c1, c0, #0 ; enabled instruction cache");
    __asm("   ISB");
}

void rt_hw_cpu_icache_disable()
{
    __asm("    MRC p15, #0, r1, c1, c0, #0  ; Read SCTLR configuration data");
    __asm("    BIC r1,  r1, #0x1 <<12  ; instruction cache enable");
    __asm("    MCR p15, #0, r1, c1, c0, #0 ; disabled instruction cache");
    __asm("    ISB");
}

void rt_hw_cpu_dcache_enable()
{
    __asm("    MRC p15, #0, R1, c1, c0, #0 ; Read SCTLR configuration data");
    __asm("    ORR R1, R1, #0x1 <<2");
    __asm("    DSB");
    __asm("    MCR p15, #0, r0, c15, c5, #0 ; Invalidate entire data cache");
    __asm("    MCR p15, #0, R1, c1, c0, #0 ; enabled data cache");
}

void rt_hw_cpu_dcache_disable()
{
    /* FIXME: Clean entire data cache. This routine depends on the data cache
     * size.  It can be omitted if it is known that the data cache has no dirty
     * data. */
    __asm("    MRC p15, #0, r1, c1, c0, #0 ; Read SCTLR configuration data");
    __asm("    BIC r1, r1, #0x1 <<2");
    __asm("    DSB");
    __asm("    MCR p15, #0, r1, c1, c0, #0 ; disabled data cache");
}

#elif __GNUC__
int __rt_ffs(int value)
{
    return __builtin_ffs(value);
}
#endif
/*@}*/
