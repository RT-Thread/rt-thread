/*
 * Copyright (c) 2006-2019, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2011-09-23     Bernard      the first version
 * 2011-10-05     Bernard      add thumb mode
 */
#include <rtthread.h>
#include <board.h>

#include <armv8.h>

#define INITIAL_SPSR_EL3 (PSTATE_EL3 | SP_EL0)
#define INITIAL_SPSR_EL2 (PSTATE_EL2 | SP_EL0)
#define INITIAL_SPSR_EL1 (PSTATE_EL1 | SP_EL0)

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
	rt_ubase_t *stk;
	rt_ubase_t current_el;

	stk 	 = (rt_ubase_t*)stack_addr;

	*(--stk) = ( rt_ubase_t ) 11;			/* R1 */
	*(--stk) = ( rt_ubase_t ) parameter; 	/* R0 */
	*(--stk) = ( rt_ubase_t ) 33;			/* R3 */
	*(--stk) = ( rt_ubase_t ) 22;			/* R2 */
	*(--stk) = ( rt_ubase_t ) 55;			/* R5 */
	*(--stk) = ( rt_ubase_t ) 44;			/* R4 */
	*(--stk) = ( rt_ubase_t ) 77;			/* R7 */
	*(--stk) = ( rt_ubase_t ) 66;			/* R6 */
	*(--stk) = ( rt_ubase_t ) 99;			/* R9 */
	*(--stk) = ( rt_ubase_t ) 88;			/* R8 */
	*(--stk) = ( rt_ubase_t ) 11;			/* R11 */
	*(--stk) = ( rt_ubase_t ) 10;			/* R10 */
	*(--stk) = ( rt_ubase_t ) 13;			/* R13 */
	*(--stk) = ( rt_ubase_t ) 12;			/* R12 */
	*(--stk) = ( rt_ubase_t ) 15;			/* R15 */
	*(--stk) = ( rt_ubase_t ) 14;			/* R14 */
	*(--stk) = ( rt_ubase_t ) 17;			/* R17 */
	*(--stk) = ( rt_ubase_t ) 16;			/* R16 */
	*(--stk) = ( rt_ubase_t ) 19;			/* R19 */
	*(--stk) = ( rt_ubase_t ) 18;			/* R18 */
	*(--stk) = ( rt_ubase_t ) 21;			/* R21 */
	*(--stk) = ( rt_ubase_t ) 20;			/* R20 */
	*(--stk) = ( rt_ubase_t ) 23;			/* R23 */
	*(--stk) = ( rt_ubase_t ) 22;			/* R22 */
	*(--stk) = ( rt_ubase_t ) 25;			/* R25 */
	*(--stk) = ( rt_ubase_t ) 24;			/* R24 */
	*(--stk) = ( rt_ubase_t ) 27;			/* R27 */
	*(--stk) = ( rt_ubase_t ) 26;			/* R26 */
	*(--stk) = ( rt_ubase_t ) 29;			/* R29 */
	*(--stk) = ( rt_ubase_t ) 28;			/* R28 */
	*(--stk) = ( rt_ubase_t ) 0;			/* XZR - has no effect, used so there are an even number of registers. */
	*(--stk) = ( rt_ubase_t ) texit;		/* R30 - procedure call link register. */

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

	*(--stk) = ( rt_ubase_t ) tentry; 		/* Exception return address. */

	/* return task's current stack address */
	return (rt_uint8_t *)stk;
}
