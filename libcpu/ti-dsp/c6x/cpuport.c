/*
 * Copyright (c) 2021, Shenzhen Academy of Aerospace Technology
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2021-11-16     Dystopia     the first version
 */

#include <rthw.h>
#include <rtthread.h>

#include "trap.h"

/*------------ rt_hw_cpu_shutdown() function ----------------------------------
 * DESCRIPTION: Shutdown CPU
 * ARGUMENTS:
 * None
 * RETURNED VALUE: None
-----------------------------------------------------------------------------*/
RT_WEAK void rt_hw_cpu_shutdown(void)
{
    rt_kprintf("shutdown...\n");

    rt_hw_interrupt_disable();

    RT_ASSERT(0);
}

/*------------ nested_exception_handler() function ---------------------------
 * DESCRIPTION: Function handles Nested Exception
 * ARGUMENTS:
 * None
 * RETURNED VALUE: None
-----------------------------------------------------------------------------*/

void nested_exception_handler(void)
{
    for(;;){}
}

/*------------ hw_nmi_handler() function --------------------------------------
 * DESCRIPTION: Function handles NMI interrupt
 * ARGUMENTS:
 * None
 * RETURNED VALUE: None
-----------------------------------------------------------------------------*/
void hw_nmi_handler(struct rt_hw_exp_stack_register *regs)
{
    for(;;){}
}

/*------------ hw_bad_handler() function --------------------------------------
 * DESCRIPTION: Function handles Bad interrupt
 * ARGUMENTS:
 * None
 * RETURNED VALUE: None
-----------------------------------------------------------------------------*/
void hw_bad_handler(void)
{
    for(;;){}
}

/*------------ hw_int4_handler() function -------------------------------------
 * DESCRIPTION: Function handles INT4 interrupt
 * ARGUMENTS:
 * None
 * RETURNED VALUE: None
-----------------------------------------------------------------------------*/
void hw_int4_handler(void)
{

}

/*------------ hw_int5_handler() function -------------------------------------
 * DESCRIPTION: Function handles INT5 interrupt
 * ARGUMENTS:
 * None
 * RETURNED VALUE: None
-----------------------------------------------------------------------------*/
void hw_int5_handler(void)
{

}

/*------------ hw_int6_handler() function -------------------------------------
 * DESCRIPTION: Function handles INT6 interrupt
 * ARGUMENTS:
 * None
 * RETURNED VALUE: None
-----------------------------------------------------------------------------*/
void hw_int6_handler(void)
{

}

/*------------ hw_int7_handler() function -------------------------------------
 * DESCRIPTION: Function handles INT7 interrupt
 * ARGUMENTS:
 * None
 * RETURNED VALUE: None
-----------------------------------------------------------------------------*/
void hw_int7_handler(void)
{

}

/*------------ hw_int8_handler() function -------------------------------------
 * DESCRIPTION: Function handles INT8 interrupt
 * ARGUMENTS:
 * None
 * RETURNED VALUE: None
-----------------------------------------------------------------------------*/
void hw_int8_handler(void)
{

}

/*------------ hw_int9_handler() function -------------------------------------
 * DESCRIPTION: Function handles INT9 interrupt
 * ARGUMENTS:
 * None
 * RETURNED VALUE: None
-----------------------------------------------------------------------------*/
void hw_int9_handler(void)
{

}

/*------------ hw_int10_handler() function ------------------------------------
 * DESCRIPTION: Function handles INT10 interrupt
 * ARGUMENTS:
 * None
 * RETURNED VALUE: None
-----------------------------------------------------------------------------*/
void hw_int10_handler(void)
{

}

/*------------ hw_int11_handler() function ------------------------------------
 * DESCRIPTION: Function handles INT11 interrupt
 * ARGUMENTS:
 * None
 * RETURNED VALUE: None
-----------------------------------------------------------------------------*/
void hw_int11_handler(void)
{

}

/*------------ hw_int12_handler() function ------------------------------------
 * DESCRIPTION: Function handles INT12 interrupt
 * ARGUMENTS:
 * None
 * RETURNED VALUE: None
-----------------------------------------------------------------------------*/
void hw_int12_handler(void)
{

}

/*------------ hw_int13_handler() function ------------------------------------
 * DESCRIPTION: Function handles INT13 interrupt
 * ARGUMENTS:
 * None
 * RETURNED VALUE: None
-----------------------------------------------------------------------------*/
void hw_int13_handler(void)
{

}

/*------------------ hw_int14_handler() function ------------------------------
 * DESCRIPTION: Function handles INT14 interrupt
 * ARGUMENTS:
 * None
 * RETURNED VALUE:
-----------------------------------------------------------------------------*/
void hw_int14_handler(void)
{
extern void rt_hw_systick_isr();
    rt_hw_systick_isr();
}

/*------------ hw_int15_handler() function ------------------------------------
 * DESCRIPTION: Function handles INT15 interrupt
 * ARGUMENTS:
 * None
 * RETURNED VALUE: None
-----------------------------------------------------------------------------*/
void hw_int15_handler(void)
{

}
