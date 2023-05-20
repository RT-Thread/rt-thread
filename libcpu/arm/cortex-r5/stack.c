/*
 * Copyright (c) 2023, lepustse@gmail.com
 *
 * License-Identifier: MIT
 *
 * Change Logs:
 * Date         Author		Notes
 * 2023-05-03   lepustse	the first version
 */
#include <rtthread.h>
#include <cpuport.h>
#include <board.h>

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

    stack_addr += sizeof(rt_uint32_t);
    stack_addr  = (rt_uint8_t *)RT_ALIGN_DOWN((rt_uint32_t)stack_addr, 8);
    stk      = (rt_uint32_t *)stack_addr;
    *(--stk) = (rt_uint32_t)tentry;         /* entry point */
    *(--stk) = (rt_uint32_t)texit;          /* lr */
    *(--stk) = 0x12121212;                  /* r12 */
    *(--stk) = 0x11111111;                  /* r11 */
    *(--stk) = 0x10101010;                  /* r10 */
    *(--stk) = 0x09090909;                  /* r9 */
    *(--stk) = 0x08080808;                  /* r8 */
    *(--stk) = 0x07070707;                  /* r7 */
    *(--stk) = 0x06060606;                  /* r6 */
    *(--stk) = 0x05050505;                  /* r5 */
    *(--stk) = 0x04040404;                  /* r4 */
    *(--stk) = 0x03030303;                  /* r3 */
    *(--stk) = 0x02020202;                  /* r2 */
    *(--stk) = 0x01010101;                  /* r1 */
    *(--stk) = (rt_uint32_t)parameter;      /* r0 : argument */
    /* cpsr */
    if ((rt_uint32_t)tentry & 0x01)
        *(--stk) = SVCMODE | 0x20;          /* thumb mode */
    else
        *(--stk) = SVCMODE;                 /* arm mode   */

    /* return task's current stack address */
    return (rt_uint8_t *)stk;
}

/*@}*/
