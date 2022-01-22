/*
 * File      : cpuport.c
 * This file is part of RT-Thread RTOS
 * COPYRIGHT (C) 2009 - 2012, RT-Thread Development Team
 *
 * The license and distribution terms for this file may be
 * found in the file LICENSE in this distribution or at
 * http://www.rt-thread.org/license/LICENSE
 *
 * Change Logs:
 * Date           Author       Notes
 * 2011-02-23     Bernard      the first version
 * 2012-09-25     lgnq         save texit address in to thread stack
 */

#include <rtthread.h>

extern volatile rt_uint8_t rt_interrupt_nest;

/* switch flag on interrupt and thread pointer to save switch record */
rt_uint32_t rt_interrupt_from_thread;
rt_uint32_t rt_interrupt_to_thread;
rt_uint8_t rt_thread_switch_interrupt_flag;

/**
 * This function will initialize hardware interrupt
 */
void rt_hw_interrupt_init(void)
{
    /* init interrupt nest, and context in thread sp */
    rt_interrupt_nest               = 0;
    rt_interrupt_from_thread        = 0;
    rt_interrupt_to_thread          = 0;
    rt_thread_switch_interrupt_flag = 0;
}

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
rt_uint8_t *rt_hw_stack_init(void       *tentry,
                             void       *parameter,
                             rt_uint8_t *stack_addr,
                             void       *texit)
{
    rt_uint16_t *pstk16;
    rt_uint16_t  flag;

    flag      = 0x0040;
    pstk16    = (rt_uint16_t *)stack_addr;

    *pstk16-- = (rt_uint32_t)texit >> 16L;
    *pstk16-- = (rt_uint32_t)texit & 0x0000FFFFL;

    /* Simulate ISR entry */
    *pstk16-- = (flag&0x00FF) |                            /* The lowest byte of the FLAG register    */
                (((rt_uint32_t)tentry>>8)&0x00000F00) |    /* The highest nibble of the PC register   */
                ((flag<<4)&0xF000);                        /* The highest nibble of the FLAG register */
    *pstk16-- = (((rt_uint32_t)tentry)&0x0000FFFF);        /* The lowest bytes of the PC register     */

    /* Save registers onto stack frame */
    *pstk16-- = (rt_uint16_t)0xFBFB;                       /* FB register                             */
    *pstk16-- = (rt_uint16_t)0x3B3B;                       /* SB register                             */
    *pstk16-- = (rt_uint16_t)0xA1A1;                       /* A1 register                             */
    *pstk16-- = (rt_uint16_t)0xA0A0;                       /* A0 register                             */
    *pstk16-- = (rt_uint16_t)0x3333;                       /* R3 register                             */
    *pstk16-- = (rt_uint32_t)parameter >> 16L;             /* Pass argument in R2 register            */
    *pstk16-- = (rt_uint32_t)parameter & 0x0000FFFFL;      /* Pass argument in R1 register            */
    *pstk16   = (rt_uint16_t)0x0000;                       /* R0 register                             */

    /* return task's current stack address */
    return (rt_uint8_t *)pstk16;
}

void rt_hw_context_switch(rt_uint32_t from, rt_uint32_t to)
{
    rt_interrupt_from_thread = from;
    rt_interrupt_to_thread   = to;
    asm("INT #0");
}

void rt_hw_context_switch_interrupt(rt_uint32_t from, rt_uint32_t to)
{
    if (rt_thread_switch_interrupt_flag != 1)
    {
        rt_thread_switch_interrupt_flag = 1;
        rt_interrupt_from_thread        = from;
    }
    rt_interrupt_to_thread = to;
}

#if defined(__GNUC__)
rt_base_t rt_hw_interrupt_disable(void)
{
    register rt_uint16_t temp;

    asm("STC  FLG, %0":"=r" (temp));
    asm("FCLR I");

    return (rt_base_t)temp;
}

void rt_hw_interrupt_enable(rt_base_t level)
{
    register rt_uint16_t temp;

    temp = level & 0xffff;
    asm("LDC %0, FLG": :"r" (temp));
}
#endif
