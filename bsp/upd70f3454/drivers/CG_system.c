/*
*******************************************************************************
* Copyright(C) NEC Electronics Corporation 2010
* All rights reserved by NEC Electronics Corporation.
* This program should be used on your own responsibility.
* NEC Electronics Corporation assumes no responsibility for any losses
* incurred by customers or third parties arising from the use of this file.
*
* This device driver was created by Applilet3 for V850ES/Jx3
* 32-Bit Single-Chip Microcontrollers
* Filename:	CG_system.c
* Abstract:	This file implements device driver for System module.
* APIlib:	Applilet3 for V850ES/Jx3 V2.01 [20 Apr 2010]
* Device:	uPD70F3746
* Compiler:	IAR Systems ICCV850
* Creation date:	6/26/2010
*******************************************************************************
*/

/*
*******************************************************************************
** Include files
*******************************************************************************
*/
#include "CG_macrodriver.h"
#include "CG_system.h"
/* Start user code for include. Do not edit comment generated here */
/* End user code. Do not edit comment generated here */
#include "CG_userdefine.h"

/*
*******************************************************************************
**  Global define
*******************************************************************************
*/
/* Start user code for global. Do not edit comment generated here */
/* End user code. Do not edit comment generated here */

void clock_pll_mode(void)
{
	/* CPU operation clock selection */
	/* Set PLL mode. */
	PLLCTL = 0x03;						/* bit 1: CPU clock selection (PLL mode/clock-through mode selection) */
										/* 1: PLL mode, 0: Clock-through mode */
	
	__asm("_loop:	set1	1,0xF82C[r0]");  //__IO_REG8_BIT(  PLLCTL, 0xFFFFF82C,  __READ_WRITE )
	__asm("			tst1	1,0xF82C[r0]");  //__IO_REG8_BIT(  PLLCTL, 0xFFFFF82C,  __READ_WRITE )
	__asm("			bz		_loop");
	
	return;
}

void clock_pcc_mode(void)
{
	/* DMA is forcibly terminated in this sample since DMA transfer must be terminated 
	before data is set to a special register. */
	
	if(TC0 == 0 && E00 == 1){			/* DMA0 transfer judgment */
		INIT0 = 1;						/* DMA0 forcible termination */
	}
	if(TC1 == 0 && E11 == 1){			/* DMA1 transfer judgment */
		INIT1 = 1;						/* DMA1 forcible termination */
	}
	if(TC2 == 0 && E22 == 1){			/* DMA2 transfer judgment */
		INIT2 = 1;						/* DMA2 forcible termination */
	}
	if(TC3 == 0 && E33 == 1){			/* DMA3 transfer judgment */
		INIT3 = 1;						/* DMA3 forcible termination */
	}
	
	/* The PCC register is a special register. Data can be written to this register only in a combination of specific sequences. */
	/* bit 1, bit 0: Clock selection, 11: fxx/8, 10: fxx/4, 01: fxx/2, 00: fxx */
	/* Clock selection: fxx */
	__asm("mov 0x00, r10");				/* Set general-purpose register data to be set to special register. */
	__asm("st.b r10, 0xF1FC[r0]");		/* Write to PRCMD register. */ //__IO_REG8(PRCMD, 0xFFFFF1FC, __WRITE)
	__asm("st.b r10, 0xF828[r0]");		/* Set PCC register. */  //__IO_REG8_BIT(PCC, 0xFFFFF828, __READ_WRITE)
	__asm("nop");						/* Insert five or more NOP instructions. */
	__asm("nop");
	__asm("nop");
	__asm("nop");
	__asm("nop");
	
	return;
}

/*
**-----------------------------------------------------------------------------
**
**  Abstract:
**	This function initializes the clock generator module.
**
**  Parameters:
**	None
**
**  Returns:
**	None
**
**-----------------------------------------------------------------------------
*/
void CLOCK_Init(void)
{
	DI();       						/* Maskable interrupt disabled */
	
	do{
		clock_pll_mode();				/* PLL mode setting function */
		
		clock_pcc_mode();				/* PCC register setting function */
		
	}while(PRERR);						/* Written in correct sequence? */
}

/* Start user code for adding. Do not edit comment generated here */
/* End user code. Do not edit comment generated here */
