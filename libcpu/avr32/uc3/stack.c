/*
 * File      : stack.c
 * This file is part of RT-Thread RTOS
 * COPYRIGHT (C) 2010, RT-Thread Development Team
 *
 * The license and distribution terms for this file may be
 * found in the file LICENSE in this distribution or at
 * http://www.rt-thread.org/license/LICENSE
 *
 * Change Logs:
 * Date           Author       Notes
 * 2010-03-30     Kyle         First version
 */
#include <rtthread.h>

/**
 * @addtogroup AVR32UC3
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
rt_uint8_t *rt_hw_stack_init(void *tentry, void *parameter, rt_uint8_t *stack_addr, void *texit)
{
    unsigned long *stk;

    stk      = (unsigned long *)stack_addr;
    *(stk)   = 0;                           /* r8 */
    *(--stk) = 0;                           /* r9 */
    *(--stk) = 0;                           /* r10 */
    *(--stk) = 0;                           /* r11 */
    *(--stk) = 0;                           /* r12 */
    *(--stk) = (unsigned long)texit;        /* lr */
    *(--stk) = (unsigned long)tentry;       /* entry point, pc */
    *(--stk) = 0x00600000;                  /* sr */
    *(--stk) = 0;                           /* r0 */
    *(--stk) = 0;                           /* r1 */
    *(--stk) = 0;                           /* r2 */
    *(--stk) = 0;                           /* r3 */
    *(--stk) = 0;                           /* r4 */
    *(--stk) = 0;                           /* r5 */
    *(--stk) = 0;                           /* r6 */
    *(--stk) = 0;                           /* r7 */

    /* return task's current stack address */
    return (rt_uint8_t *)stk;
}

/*@}*/
