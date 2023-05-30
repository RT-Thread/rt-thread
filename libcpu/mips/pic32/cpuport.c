/*
 * File      : cpuport.c
 * This file is part of RT-Thread RTOS
 * COPYRIGHT (C) 2009 - 2011, RT-Thread Development Team
 *
 * The license and distribution terms for this file may be
 * found in the file LICENSE in this distribution or at
 * http://www.rt-thread.org/license/LICENSE
 *
 * Change Logs:
 * Date           Author       Notes
 * 20011-05-23    aozima       the first version for PIC32.
 * 20011-09-05    aozima       merge all of C source code into cpuport.c.
 */
#include <rtthread.h>

/**
 * @addtogroup PIC32
 */
/*@{*/

/* exception and interrupt handler table */
rt_uint32_t rt_interrupt_from_thread, rt_interrupt_to_thread;
rt_uint32_t rt_thread_switch_interrupt_flag;

rt_uint32_t __attribute__((nomips16)) _get_gp(void)
{
    rt_uint32_t result;

    // get the gp reg
    asm volatile("move   %0, $28" : "=r"(result));

    return result;
}

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

    /** Start at stack top */
    stk = (rt_uint32_t *)stack_addr;
    *(stk)   = (rt_uint32_t) tentry;        /* pc: Entry Point */
    *(--stk) = (rt_uint32_t) 0x00800000;    /* c0_cause: IV=1, */
    *(--stk) = (rt_uint32_t) 0;             /* c0_badvaddr */
    *(--stk) = (rt_uint32_t) 0;             /* lo */
    *(--stk) = (rt_uint32_t) 0;             /* hi */
    *(--stk) = (rt_uint32_t) 1;             /* C0_SR: IE = En, */
    *(--stk) = (rt_uint32_t) texit;         /* 31 ra */
    *(--stk) = (rt_uint32_t) 0x0000001e;    /* 30 s8 */
    *(--stk) = (rt_uint32_t) stack_addr;    /* 29 sp */
    *(--stk) = (rt_uint32_t) _get_gp();     /* 28 gp */
    *(--stk) = (rt_uint32_t) 0x0000001b;    /* 27 k1 */
    *(--stk) = (rt_uint32_t) 0x0000001a;    /* 26 k0 */
    *(--stk) = (rt_uint32_t) 0x00000019;    /* 25 t9 */
    *(--stk) = (rt_uint32_t) 0x00000018;    /* 24 t8 */
    *(--stk) = (rt_uint32_t) 0x00000017;    /* 23 s7 */
    *(--stk) = (rt_uint32_t) 0x00000016;    /* 22 s6 */
    *(--stk) = (rt_uint32_t) 0x00000015;    /* 21 s5 */
    *(--stk) = (rt_uint32_t) 0x00000014;    /* 20 s4 */
    *(--stk) = (rt_uint32_t) 0x00000013;    /* 19 s3 */
    *(--stk) = (rt_uint32_t) 0x00000012;    /* 18 s2 */
    *(--stk) = (rt_uint32_t) 0x00000011;    /* 17 s1 */
    *(--stk) = (rt_uint32_t) 0x00000010;    /* 16 s0 */
    *(--stk) = (rt_uint32_t) 0x0000000f;    /* 15 t7 */
    *(--stk) = (rt_uint32_t) 0x0000000e;    /* 14 t6 */
    *(--stk) = (rt_uint32_t) 0x0000000d;    /* 13 t5 */
    *(--stk) = (rt_uint32_t) 0x0000000c;    /* 12 t4 */
    *(--stk) = (rt_uint32_t) 0x0000000b;    /* 11 t3 */
    *(--stk) = (rt_uint32_t) 0x0000000a;    /* 10 t2 */
    *(--stk) = (rt_uint32_t) 0x00000009;    /* 9 t1 */
    *(--stk) = (rt_uint32_t) 0x00000008;    /* 8 t0 */
    *(--stk) = (rt_uint32_t) 0x00000007;    /* 7 a3 */
    *(--stk) = (rt_uint32_t) 0x00000006;    /* 6 a2 */
    *(--stk) = (rt_uint32_t) 0x00000005;    /* 5 a1 */
    *(--stk) = (rt_uint32_t) parameter;     /* 4 a0 */
    *(--stk) = (rt_uint32_t) 0x00000003;    /* 3 v1 */
    *(--stk) = (rt_uint32_t) 0x00000002;    /* 2 v0 */
    *(--stk) = (rt_uint32_t) 0x00000001;    /* 1 at */
    *(--stk) = (rt_uint32_t) 0x00000000;    /* 0 zero */

    /* return task's current stack address */
    return (rt_uint8_t *)stk;
}


/*@}*/
