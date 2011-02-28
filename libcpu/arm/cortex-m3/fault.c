/******************************************************************//**
 * @file 		fault.c
 * @brief 	This file is part of RT-Thread RTOS
 * 	COPYRIGHT (C) 2011, RT-Thread Development Team
 * @author 	Bernard, onelife
 * @version 	0.4 beta
 **********************************************************************
 * @section License
 * The license and distribution terms for this file may be found in the file LICENSE in this 
 * distribution or at http://www.rt-thread.org/license/LICENSE
 **********************************************************************
 * @section Change Logs
 * Date			Author		Notes
 * 2009-01-05 	Bernard 		first version
 * 2011-02-14	onelife		Modify for EFM32
 *********************************************************************/
 
/******************************************************************//**
* @addtogroup cortex-m3
* @{
*********************************************************************/

/* Includes -------------------------------------------------------------------*/
#include <rtthread.h>

/* Private typedef -------------------------------------------------------------*/
struct stack_contex
{
	rt_uint32_t r0;
	rt_uint32_t r1;
	rt_uint32_t r2;
	rt_uint32_t r3;
	rt_uint32_t r12;
	rt_uint32_t lr;
	rt_uint32_t pc;
	rt_uint32_t psr;
};

/* Private define --------------------------------------------------------------*/
/* Private macro --------------------------------------------------------------*/
/* Private variables ------------------------------------------------------------*/
/* External function prototypes --------------------------------------------------*/
extern void list_thread(void);
extern rt_thread_t rt_current_thread;

/* Private function prototypes ---------------------------------------------------*/
/* Private functions ------------------------------------------------------------*/
void rt_hw_hard_fault_exception(struct stack_contex* contex)
{
	rt_kprintf("psr: 0x%08x\n", contex->psr);
	rt_kprintf(" pc: 0x%08x\n", contex->pc);
	rt_kprintf(" lr: 0x%08x\n", contex->lr);
	rt_kprintf("r12: 0x%08x\n", contex->r12);
	rt_kprintf("r03: 0x%08x\n", contex->r3);
	rt_kprintf("r02: 0x%08x\n", contex->r2);
	rt_kprintf("r01: 0x%08x\n", contex->r1);
	rt_kprintf("r00: 0x%08x\n", contex->r0);

	rt_kprintf("hard fault on thread: %s\n", rt_current_thread->name);
#ifdef RT_USING_FINSH
	list_thread();
#endif
	while (1);
}

/******************************************************************//**
 * @}
*********************************************************************/
