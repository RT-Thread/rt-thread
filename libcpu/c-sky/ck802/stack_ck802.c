/*
 * File      : stack_ck802.c
 * This file is part of RT-Thread RTOS
 * COPYRIGHT (C) 2006 - 2017, RT-Thread Development Team
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
 * 2017-01-01     Urey      first version
 */

#include <rtthread.h>

rt_uint8_t *rt_hw_stack_init(void *tentry, void *parameter, rt_uint8_t *stack_addr, void *texit)
{
    rt_uint32_t *stk  = (rt_uint32_t *)stack_addr;

    stk  = (rt_uint32_t *)(stack_addr + sizeof(rt_uint32_t));
    stk  = (rt_uint32_t *)RT_ALIGN_DOWN((rt_uint32_t)stk, 8);

    *(--stk)  = (rt_uint32_t)tentry;            /* Entry Point                                         */
    *(--stk)  = (rt_uint32_t)0x80000150L;       /* PSR                                                 */
    *(--stk)  = (rt_uint32_t)texit;             /* R15 (LR) (init value will cause fault if ever used) */
    *(--stk)  = (rt_uint32_t)0x13131313L;       /* R13                                                 */
    *(--stk)  = (rt_uint32_t)0x12121212L;       /* R12 */
    *(--stk)  = (rt_uint32_t)0x11111111L;       /* R11 */
    *(--stk)  = (rt_uint32_t)0x10101010L;       /* R10 */
    *(--stk)  = (rt_uint32_t)0x09090909L;       /* R9  */
    *(--stk)  = (rt_uint32_t)0x08080808L;       /* R8  */
    *(--stk)  = (rt_uint32_t)0x07070707L;       /* R7  */
    *(--stk)  = (rt_uint32_t)0x06060606L;       /* R6  */
    *(--stk)  = (rt_uint32_t)0x05050505L;       /* R5  */
    *(--stk)  = (rt_uint32_t)0x04040404L;       /* R4  */
    *(--stk)  = (rt_uint32_t)0x03030303L;       /* R3                                                  */
    *(--stk)  = (rt_uint32_t)0x02020202L;       /* R2                                                  */
    *(--stk)  = (rt_uint32_t)0x01010101L;       /* R1                                                  */
    *(--stk)  = (rt_uint32_t)parameter;         /* R0 : argument                                       */

    /* return task's current stack address */
    return (rt_uint8_t *)stk;
}

