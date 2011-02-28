/******************************************************************//**
 * @file 		fault_gcc.S
 * @brief 	Faults handling functions
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
 * 2009-10-11 	Bernard 		first version
 * 2010-12-29	onelife		Modify for EFM32
 *********************************************************************/
 
/******************************************************************//**
* @addtogroup cortex-m3
* @{
*********************************************************************/

	.cpu cortex-m3
	.fpu softvfp
	.syntax unified
	.thumb
	.text

	.global rt_hw_hard_fault
	.type rt_hw_hard_fault, %function
rt_hw_hard_fault:
    /* get current context */
    MRS     r0, psp                 /* get fault thread stack pointer */
    PUSH    {lr}
    BL      rt_hw_hard_fault_exception
    POP     {lr}

    ORR     lr, lr, #0x04
    BX      lr

/******************************************************************//**
 * @}
*********************************************************************/
