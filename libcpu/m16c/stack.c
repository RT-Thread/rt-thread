/*
 * File      : stack.c
 * This file is part of RT-Thread RTOS
 * COPYRIGHT (C) 2009, RT-Thread Development Team
 *
 * The license and distribution terms for this file may be
 * found in the file LICENSE in this distribution or at
 * http://www.rt-thread.org/license/LICENSE
 *
 * Change Logs:
 * Date           Author       Notes
 * 2010-04-09     fify         the first version
 *
 * For       : Renesas M16C
 * Toolchain : IAR's EW for M16C v3.401
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
    rt_uint16_t  *pstk16;
    rt_uint16_t   flag;


    flag       = 0x0040;
    pstk16     = (rt_uint16_t *)stack_addr;
    pstk16--;

                                                                /* Simulate ISR entry                                       */
    *pstk16--  = (flag                 &     0x00FF)            /* ... The lowest  byte   of the FLAG register              */
               | (((rt_uint32_t)tentry >>  8) & 0x00000F00)            /* ... The highest nibble of the PC   register              */
               | ((flag         <<  4) &     0xF000);           /* ... The highest nibble of the FLAG register              */
    *pstk16--  = (((rt_uint32_t)tentry      ) & 0x0000FFFF);           /* ... The lowest  bytes  of the PC   register              */

                                                                /* Save registers onto stack frame                          */
    *pstk16--  = (rt_uint16_t)0xFBFB;				                /* ... FB register                                          */
    *pstk16--  = (rt_uint16_t)0x3B3B;                                /* ... SB register                                          */
    *pstk16--  = (rt_uint16_t)0xA1A1;				                /* ... A1 register                                          */
    *pstk16--  = (rt_uint16_t)0xA0A0;				                /* ... A0 register                                          */
    *pstk16--  = (rt_uint16_t)0x3333;				                /* ... R3 register                                          */
    *pstk16--  = (rt_uint32_t)parameter >> 16L;				            /* ... Pass argument in R2 register                         */
    *pstk16--  = (rt_uint32_t)parameter & 0x0000FFFFL;				    /* ... Pass argument in R1 register                         */
    *pstk16    = (rt_uint16_t)0x0000;				                /* ... R0 register                                          */

	/* return task's current stack address */
	return (rt_uint8_t *)pstk16;
}
