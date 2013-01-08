/*********************************************************************
 *
 *                  Generic Exception Handler
 *
 *********************************************************************
 * FileName:        exceptions.c
 * Dependencies:
 *
 * Processor:       PIC32
 *
 * Complier:        MPLAB C32
 *                  MPLAB IDE
 * Company:         Microchip Technology, Inc.
 * Author:			Darren Wenn
 *
 * Software License Agreement
 *
 * The software supplied herewith by Microchip Technology Incorporated
 * (the “Company”) for its PIC32/PIC24 Microcontroller is intended
 * and supplied to you, the Company’s customer, for use solely and
 * exclusively on Microchip PIC32/PIC24 Microcontroller products.
 * The software is owned by the Company and/or its supplier, and is
 * protected under applicable copyright laws. All rights are reserved.
 * Any use in violation of the foregoing restrictions may subject the
 * user to criminal sanctions under applicable laws, as well as to
 * civil liability for the breach of the terms and conditions of this
 * license.
 *
 * THIS SOFTWARE IS PROVIDED IN AN “AS IS” CONDITION. NO WARRANTIES,
 * WHETHER EXPRESS, IMPLIED OR STATUTORY, INCLUDING, BUT NOT LIMITED
 * TO, IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A
 * PARTICULAR PURPOSE APPLY TO THIS SOFTWARE. THE COMPANY SHALL NOT,
 * IN ANY CIRCUMSTANCES, BE LIABLE FOR SPECIAL, INCIDENTAL OR
 * CONSEQUENTIAL DAMAGES, FOR ANY REASON WHATSOEVER.
 *
 *
 *
 ********************************************************************/

#include <p32xxxx.h>

// declared static in case exception condition would prevent
// auto variable being created
static enum {
	EXCEP_IRQ = 0,			// interrupt
	EXCEP_AdEL = 4,			// address error exception (load or ifetch)
	EXCEP_AdES,				// address error exception (store)
	EXCEP_IBE,				// bus error (ifetch)
	EXCEP_DBE,				// bus error (load/store)
	EXCEP_Sys,				// syscall
	EXCEP_Bp,				// breakpoint
	EXCEP_RI,				// reserved instruction
	EXCEP_CpU,				// coprocessor unusable
	EXCEP_Overflow,			// arithmetic overflow
	EXCEP_Trap,				// trap (possible divide by zero)
	EXCEP_IS1 = 16,			// implementation specfic 1
	EXCEP_CEU,				// CorExtend Unuseable
	EXCEP_C2E				// coprocessor 2
} _excep_code;

static unsigned int _epc_code;
static unsigned int _excep_addr;

#include <rtthread.h>
// this function overrides the normal _weak_ generic handler
void _general_exception_handler(void)
{
	asm volatile("mfc0 %0,$13" : "=r" (_excep_code));
	asm volatile("mfc0 %0,$14" : "=r" (_excep_addr));

	_excep_code = (_excep_code & 0x0000007C) >> 2;

	rt_kprintf("\r\n_excep_code : %08X\r\n",_excep_code);
	rt_kprintf("_excep_addr : %08X\r\n",_excep_addr);
	switch(_excep_code)
	{
	    case EXCEP_IRQ:rt_kprintf("interrupt\r\n");break;
	    case EXCEP_AdEL:rt_kprintf("address error exception (load or ifetch)\r\n");break;
	    case EXCEP_AdES:rt_kprintf("address error exception (store)\r\n");break;
	    case EXCEP_IBE:rt_kprintf("bus error (ifetch)\r\n");break;
	    case EXCEP_DBE:rt_kprintf("bus error (load/store)\r\n");break;
	    case EXCEP_Sys:rt_kprintf("syscall\r\n");break;
	    case EXCEP_Bp:rt_kprintf("breakpoint\r\n");break;
	    case EXCEP_RI:rt_kprintf("reserved instruction\r\n");break;
	    case EXCEP_CpU:rt_kprintf("coprocessor unusable\r\n");break;
	    case EXCEP_Overflow:rt_kprintf("arithmetic overflow\r\n");break;
	    case EXCEP_Trap:rt_kprintf("trap (possible divide by zero)\r\n");break;
	    case EXCEP_IS1:rt_kprintf("implementation specfic 1\r\n");break;
	    case EXCEP_CEU:rt_kprintf("CorExtend Unuseable\r\n");break;
	    case EXCEP_C2E:rt_kprintf("coprocessor 2\r\n");break;
	    default : rt_kprintf("unkown exception\r\n");break;
	}

	while (1) {
		// Examine _excep_code to identify the type of exception
		// Examine _excep_addr to find the address that caused the exception
	}
}
