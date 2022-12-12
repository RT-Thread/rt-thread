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
 * 2021-12-28     GuEe-GUI     add fpu support
 */
#include <rtthread.h>
#include <armv8.h>

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
    static const rt_ubase_t initial_spsr[] =
    {
        [1] = PSTATE_EL1 | SP_ELx,
        [2] = PSTATE_EL2 | SP_ELx,
        [3] = PSTATE_EL3 | SP_ELx
    };
    /* The AAPCS64 requires 128-bit (16 byte) stack alignment */
    rt_ubase_t *stk = (rt_ubase_t*)RT_ALIGN_DOWN((rt_ubase_t)stack_addr, 16);

    *(--stk) = (rt_ubase_t) 0;              /* Q0 */
    *(--stk) = (rt_ubase_t) 0;              /* Q0 */
    *(--stk) = (rt_ubase_t) 0;              /* Q1 */
    *(--stk) = (rt_ubase_t) 0;              /* Q1 */
    *(--stk) = (rt_ubase_t) 0;              /* Q2 */
    *(--stk) = (rt_ubase_t) 0;              /* Q2 */
    *(--stk) = (rt_ubase_t) 0;              /* Q3 */
    *(--stk) = (rt_ubase_t) 0;              /* Q3 */
    *(--stk) = (rt_ubase_t) 0;              /* Q4 */
    *(--stk) = (rt_ubase_t) 0;              /* Q4 */
    *(--stk) = (rt_ubase_t) 0;              /* Q5 */
    *(--stk) = (rt_ubase_t) 0;              /* Q5 */
    *(--stk) = (rt_ubase_t) 0;              /* Q6 */
    *(--stk) = (rt_ubase_t) 0;              /* Q6 */
    *(--stk) = (rt_ubase_t) 0;              /* Q7 */
    *(--stk) = (rt_ubase_t) 0;              /* Q7 */
    *(--stk) = (rt_ubase_t) 0;              /* Q8 */
    *(--stk) = (rt_ubase_t) 0;              /* Q8 */
    *(--stk) = (rt_ubase_t) 0;              /* Q9 */
    *(--stk) = (rt_ubase_t) 0;              /* Q9 */
    *(--stk) = (rt_ubase_t) 0;              /* Q10 */
    *(--stk) = (rt_ubase_t) 0;              /* Q10 */
    *(--stk) = (rt_ubase_t) 0;              /* Q11 */
    *(--stk) = (rt_ubase_t) 0;              /* Q11 */
    *(--stk) = (rt_ubase_t) 0;              /* Q12 */
    *(--stk) = (rt_ubase_t) 0;              /* Q12 */
    *(--stk) = (rt_ubase_t) 0;              /* Q13 */
    *(--stk) = (rt_ubase_t) 0;              /* Q13 */
    *(--stk) = (rt_ubase_t) 0;              /* Q14 */
    *(--stk) = (rt_ubase_t) 0;              /* Q14 */
    *(--stk) = (rt_ubase_t) 0;              /* Q15 */
    *(--stk) = (rt_ubase_t) 0;              /* Q15 */

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
    *(--stk) = ( rt_ubase_t ) 0;            /* FPSR */
    *(--stk) = ( rt_ubase_t ) 0;            /* FPCR */
    *(--stk) = ( rt_ubase_t ) 0;            /* XZR - has no effect, used so there are an even number of registers. */
    *(--stk) = ( rt_ubase_t ) texit;        /* X30 - procedure call link register. */

    *(--stk) = initial_spsr[rt_hw_get_current_el()];
    *(--stk) = ( rt_ubase_t ) tentry;       /* Exception return address. */

    /* return task's current stack address */
    return (rt_uint8_t *)stk;
}
