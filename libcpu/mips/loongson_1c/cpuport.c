/*
 * File      : cpuport.c
 * This file is part of RT-Thread RTOS
 * COPYRIGHT (C) 2006 - 2011, RT-Thread Development Team
 *
 * The license and distribution terms for this file may be
 * found in the file LICENSE in this distribution or at
 * http://www.rt-thread.org/license/LICENSE
 *
 * Change Logs:
 * Date                Author         Notes
 * 2010-07-09     Bernard        first version
 * 2010-09-11     Bernard        add CPU reset implementation
 * 2015-07-06     chinesebear  modified for loongson 1c
 */

#include <rtthread.h>
#include "ls1c.h"

register rt_uint32_t $GP __asm__ ("$28");

/**
 * @addtogroup Loongson LS1B
 */

/*@{*/

/**
 * this function will reset CPU
 *
 */
void rt_hw_cpu_reset(void)
{
	/* open the watch-dog */
	WDT_EN = 0x01; 		/* watch dog enable */
	WDT_TIMER = 0x01;	/* watch dog will be timeout after 1 tick */
	WDT_SET = 0x01;		/* watch dog start */

	rt_kprintf("reboot system...\n");
	while (1);
}

/**
 * this function will shutdown CPU
 *
 */
void rt_hw_cpu_shutdown(void)
{
	rt_kprintf("shutdown...\n");

	while (1);
}

extern rt_uint32_t cp0_get_cause(void);
extern rt_uint32_t cp0_get_status(void);
extern rt_uint32_t cp0_get_hi(void);
extern rt_uint32_t cp0_get_lo(void);

/**
 * This function will initialize thread stack
 *
 * @param tentry the entry of thread
 * @param parameter the parameter of entry
 * @param stack_addr the beginning stack address
 * @param texit the function will be called when thread exit
 *
 * @return stack address
 */
rt_uint8_t *rt_hw_stack_init(void *tentry, void *parameter, rt_uint8_t *stack_addr, void *texit)
{
	rt_uint32_t *stk;
    static rt_uint32_t g_sr = 0;
	static rt_uint32_t g_gp = 0;

    if (g_sr == 0)
    {
    	g_sr = cp0_get_status();
    	g_sr &= 0xfffffffe;
    	g_sr |= 0x8401;

		g_gp = $GP;
    }

    /** Start at stack top */
    stk = (rt_uint32_t *)stack_addr;
	*(stk)   = (rt_uint32_t) tentry;        /* pc: Entry Point */
	*(--stk) = (rt_uint32_t) 0xeeee; 		/* c0_cause */
	*(--stk) = (rt_uint32_t) 0xffff;		/* c0_badvaddr */
	*(--stk) = (rt_uint32_t) cp0_get_lo();	/* lo */
	*(--stk) = (rt_uint32_t) cp0_get_hi();	/* hi */
	*(--stk) = (rt_uint32_t) g_sr; 			/* C0_SR: HW2 = En, IE = En */
	*(--stk) = (rt_uint32_t) texit;	        /* ra */
	*(--stk) = (rt_uint32_t) 0x0000001e;	/* s8 */
	*(--stk) = (rt_uint32_t) stack_addr;	/* sp */
	*(--stk) = (rt_uint32_t) g_gp;	        /* gp */
	*(--stk) = (rt_uint32_t) 0x0000001b;	/* k1 */
	*(--stk) = (rt_uint32_t) 0x0000001a;	/* k0 */
	*(--stk) = (rt_uint32_t) 0x00000019;	/* t9 */
	*(--stk) = (rt_uint32_t) 0x00000018;	/* t8 */
	*(--stk) = (rt_uint32_t) 0x00000017;	/* s7 */
	*(--stk) = (rt_uint32_t) 0x00000016;	/* s6 */
	*(--stk) = (rt_uint32_t) 0x00000015;	/* s5 */
	*(--stk) = (rt_uint32_t) 0x00000014;	/* s4 */
	*(--stk) = (rt_uint32_t) 0x00000013;	/* s3 */
	*(--stk) = (rt_uint32_t) 0x00000012;	/* s2 */
	*(--stk) = (rt_uint32_t) 0x00000011;	/* s1 */
	*(--stk) = (rt_uint32_t) 0x00000010;	/* s0 */
	*(--stk) = (rt_uint32_t) 0x0000000f;	/* t7 */
	*(--stk) = (rt_uint32_t) 0x0000000e;	/* t6 */
	*(--stk) = (rt_uint32_t) 0x0000000d;	/* t5 */
	*(--stk) = (rt_uint32_t) 0x0000000c;	/* t4 */
	*(--stk) = (rt_uint32_t) 0x0000000b;	/* t3 */
	*(--stk) = (rt_uint32_t) 0x0000000a; 	/* t2 */
	*(--stk) = (rt_uint32_t) 0x00000009;	/* t1 */
	*(--stk) = (rt_uint32_t) 0x00000008;	/* t0 */
	*(--stk) = (rt_uint32_t) 0x00000007;	/* a3 */
	*(--stk) = (rt_uint32_t) 0x00000006;	/* a2 */
	*(--stk) = (rt_uint32_t) 0x00000005;	/* a1 */
	*(--stk) = (rt_uint32_t) parameter;	    /* a0 */
	*(--stk) = (rt_uint32_t) 0x00000003;	/* v1 */
	*(--stk) = (rt_uint32_t) 0x00000002;	/* v0 */
	*(--stk) = (rt_uint32_t) 0x00000001;	/* at */
	*(--stk) = (rt_uint32_t) 0x00000000;	/* zero */

	/* return task's current stack address */
	return (rt_uint8_t *)stk;
}

#define cache_op(op,addr)                       \
	    __asm__ __volatile__(                       \
				    "   .set    push                    \n" \
				    "   .set    noreorder               \n" \
				    "   .set    mips3\n\t               \n" \
				    "   cache   %0, %1                  \n" \
				    "   .set    pop                 \n" \
				    :                               \
				    : "i" (op), "R" (*(unsigned char *)(addr)))

#if defined(CONFIG_CPU_LOONGSON2)
#define Hit_Invalidate_I    0x00
#else
#define Hit_Invalidate_I    0x10
#endif
#define Hit_Invalidate_D    0x11
#define CONFIG_SYS_CACHELINE_SIZE   32
#define Hit_Writeback_Inv_D 0x15


void flush_cache(unsigned long start_addr, unsigned long size)
{
	unsigned long lsize = CONFIG_SYS_CACHELINE_SIZE;
	unsigned long addr = start_addr & ~(lsize - 1); 
	unsigned long aend = (start_addr + size - 1) & ~(lsize - 1); 

	while (1) {
		cache_op(Hit_Writeback_Inv_D, addr);
		cache_op(Hit_Invalidate_I, addr);
		if (addr == aend)
			break;
		addr += lsize;
	}   
}


/*@}*/

