/*
 * Copyright (c) 2006-2022, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2011-02-14     aozima       first implementation for Nios II.
 */

#include <rtthread.h>

/**
 * @addtogroup NIOS_II
 */
/*@{*/

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
rt_uint8_t *rt_hw_stack_init(void *tentry, void *parameter,
    rt_uint8_t *stack_addr, void *texit)
{
    unsigned long *stk;

    stk      = (unsigned long *)stack_addr;
    *(stk)   = 0x01;                        /* status  */
    *(--stk) = (unsigned long)texit;        /* ra  */
    *(--stk) = 0xdeadbeef;                  /* fp  */
    *(--stk) = 0xdeadbeef;                  /* r23 */
    *(--stk) = 0xdeadbeef;                  /* r22 */
    *(--stk) = 0xdeadbeef;                  /* r21 */
    *(--stk) = 0xdeadbeef;                  /* r20 */
    *(--stk) = 0xdeadbeef;                  /* r19 */
    *(--stk) = 0xdeadbeef;                  /* r18 */
    *(--stk) = 0xdeadbeef;                  /* r17 */
    *(--stk) = 0xdeadbeef;                  /* r16 */
//  *(--stk) = 0xdeadbeef;                  /* r15 */
//  *(--stk) = 0xdeadbeef;                  /* r14 */
//  *(--stk) = 0xdeadbeef;                  /* r13 */
//  *(--stk) = 0xdeadbeef;                  /* r12 */
//  *(--stk) = 0xdeadbeef;                  /* r11 */
//  *(--stk) = 0xdeadbeef;                  /* r10 */
//  *(--stk) = 0xdeadbeef;                  /* r9  */
//  *(--stk) = 0xdeadbeef;                  /* r8  */
    *(--stk) = 0xdeadbeef;                  /* r7  */
    *(--stk) = 0xdeadbeef;                  /* r6  */
    *(--stk) = 0xdeadbeef;                  /* r5  */
    *(--stk) = (unsigned long)parameter;    /* r4 argument */
    *(--stk) = 0xdeadbeef;                  /* r3  */
    *(--stk) = 0xdeadbeef;                  /* r2  */
    *(--stk) = (unsigned long)tentry;       /* pc  */

//  *(stk)   = (unsigned long)tentry;       /* thread entry (ra) */
//  *(--stk) = (unsigned long)parameter;    /* thread argument, r4 */

    /* return task's current stack address */
    return (rt_uint8_t *)stk;
}

/*@}*/
