/*
 * Copyright (c) 2006-2021, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
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

