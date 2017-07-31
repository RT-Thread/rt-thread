/*
 * File      : stack.c
 * This file is part of RT-Thread RTOS
 * COPYRIGHT (C) 2006, RT-Thread Development Team
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
 * 2017-07-31     zhangjun      copy from mini2440
 */
#include <rtthread.h>

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
    rt_uint32_t *stk;

    //stk      = (rt_uint32_t*)stack_addr;
    stack_addr += sizeof(rt_uint32_t);
    stack_addr  = (rt_uint8_t *)RT_ALIGN_DOWN((rt_uint32_t)stack_addr, 8);
    stk  = (rt_uint32_t *)stack_addr;

    *(--stk) = (rt_uint32_t)tentry;         /* entry point */
    *(--stk) = (rt_uint32_t)texit;          /* ra */
    *(--stk) = (rt_uint32_t)parameter;      /* a0 */
    *(--stk) = 0xffffffff;          	    /* a1 */
    *(--stk) = 0xffffffff;          	    /* a2 */
    *(--stk) = 0xffffffff;          	    /* a3 */
    *(--stk) = 0xffffffff;          	    /* a4 */
    *(--stk) = 0xffffffff;          	    /* a5 */
    *(--stk) = 0xffffffff;          	    /* a6 */
    *(--stk) = 0xffffffff;          	    /* a7 */
    *(--stk) = 0xffffffff;          	    /* s0/fp */
    *(--stk) = 0xffffffff;          	    /* s1 */
    *(--stk) = 0xffffffff;          	    /* s2 */
    *(--stk) = 0xffffffff;          	    /* s3 */
    *(--stk) = 0xffffffff;          	    /* s4 */
    *(--stk) = 0xffffffff;          	    /* s5 */
    *(--stk) = 0xffffffff;          	    /* s6 */
    *(--stk) = 0xffffffff;          	    /* s7 */
    *(--stk) = 0xffffffff;          	    /* s8 */
    *(--stk) = 0xffffffff;          	    /* s9 */
    *(--stk) = 0xffffffff;          	    /* s10*/
    *(--stk) = 0xffffffff;          	    /* s11*/
    *(--stk) = 0xffffffff;          	    /* t0 */
    *(--stk) = 0xffffffff;          	    /* t1 */
    *(--stk) = 0xffffffff;          	    /* t2 */
    *(--stk) = 0xffffffff;          	    /* t3 */
    *(--stk) = 0xffffffff;          	    /* t4 */
    *(--stk) = 0xffffffff;          	    /* t5 */
    *(--stk) = 0xffffffff;          	    /* t6 */
    *(--stk) = 0xffffffff;          	    /* tp */
    *(--stk) = 0xffffffff;          	    /* gp */
    *(--stk) = 0x880;          	            /* mie */
//    *(--stk) = (rt_uint32_t)parameter;      /* r0 : argument */
    /* return task's current stack address */
    return (rt_uint8_t *)stk;
}
