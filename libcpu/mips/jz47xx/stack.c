/*
 * File      : stack.c
 * This file is part of RT-Thread RTOS
 * COPYRIGHT (C) 2006, RT-Thread Development Team
 *
 * The license and distribution terms for this file may be
 * found in the file LICENSE in this distribution or at
 * http://www.rt-thread.org/license/LICENSE
 *
 * Change Logs:
 * Date           Author       Notes
 * 2010-05-17     swkyer       first version
 * 2010-07-07     Bernard      porting to Jz47xx
 */
#include <rtthread.h>

/**
 * @addtogroup Jz47xx
 */
/*@{*/

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

    if (g_sr == 0)
    {
    	g_sr = cp0_get_status();
    	g_sr &= 0xfffffffe;
    	g_sr |= 0x0403;
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
	*(--stk) = (rt_uint32_t) 0x0000001c;	/* gp */
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

/*@}*/
