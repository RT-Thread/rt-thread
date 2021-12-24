/*
 * Copyright (c) 2006-2021, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2011-09-23     Bernard      the first version
 * 2011-10-05     Bernard      add thumb mode
 * 2021-11-04     GuEe-GUI     set sp with SP_ELx
 */
#include <rtthread.h>
#include <board.h>

#include <armv8.h>

#define INITIAL_SPSR_EL3 (PSTATE_EL3 | SP_ELx)
#define INITIAL_SPSR_EL2 (PSTATE_EL2 | SP_ELx)
#define INITIAL_SPSR_EL1 (PSTATE_EL1 | SP_ELx)

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
    rt_ubase_t *stk;
    rt_ubase_t current_el;

    stk      = (rt_ubase_t*)stack_addr;

    *(--stk) = ( rt_ubase_t ) 11;           /* X1 */
    *(--stk) = ( rt_ubase_t ) parameter;    /* X0 */
    *(--stk) = ( rt_ubase_t ) 33;           /* X3 */
    *(--stk) = ( rt_ubase_t ) 22;           /* X2 */
    *(--stk) = ( rt_ubase_t ) 55;           /* X5 */
    *(--stk) = ( rt_ubase_t ) 44;           /* X4 */
    *(--stk) = ( rt_ubase_t ) 77;           /* X7 */
    *(--stk) = ( rt_ubase_t ) 66;           /* X6 */
    *(--stk) = ( rt_ubase_t ) 99;           /* X9 */
    *(--stk) = ( rt_ubase_t ) 88;           /* X8 */
    *(--stk) = ( rt_ubase_t ) 11;           /* X11 */
    *(--stk) = ( rt_ubase_t ) 10;           /* X10 */
    *(--stk) = ( rt_ubase_t ) 13;           /* X13 */
    *(--stk) = ( rt_ubase_t ) 12;           /* X12 */
    *(--stk) = ( rt_ubase_t ) 15;           /* X15 */
    *(--stk) = ( rt_ubase_t ) 14;           /* X14 */
    *(--stk) = ( rt_ubase_t ) 17;           /* X17 */
    *(--stk) = ( rt_ubase_t ) 16;           /* X16 */
    *(--stk) = ( rt_ubase_t ) 19;           /* X19 */
    *(--stk) = ( rt_ubase_t ) 18;           /* X18 */
    *(--stk) = ( rt_ubase_t ) 21;           /* X21 */
    *(--stk) = ( rt_ubase_t ) 20;           /* X20 */
    *(--stk) = ( rt_ubase_t ) 23;           /* X23 */
    *(--stk) = ( rt_ubase_t ) 22;           /* X22 */
    *(--stk) = ( rt_ubase_t ) 25;           /* X25 */
    *(--stk) = ( rt_ubase_t ) 24;           /* X24 */
    *(--stk) = ( rt_ubase_t ) 27;           /* X27 */
    *(--stk) = ( rt_ubase_t ) 26;           /* X26 */
    *(--stk) = ( rt_ubase_t ) 29;           /* X29 */
    *(--stk) = ( rt_ubase_t ) 28;           /* X28 */
    *(--stk) = ( rt_ubase_t ) 0;            /* XZR - has no effect, used so there are an even number of registers. */
    *(--stk) = ( rt_ubase_t ) texit;        /* X30 - procedure call link register. */

    current_el = rt_hw_get_current_el();

    if(current_el == 3)
    {
        *(--stk) = INITIAL_SPSR_EL3;
    }
    else if(current_el == 2)
    {
        *(--stk) = INITIAL_SPSR_EL2;
    }
    else
    {
        *(--stk) = INITIAL_SPSR_EL1;
    }

    *(--stk) = ( rt_ubase_t ) tentry;       /* Exception return address. */

    /* return task's current stack address */
    return (rt_uint8_t *)stk;
}
