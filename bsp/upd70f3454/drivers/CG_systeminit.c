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
* Filename:	CG_systeminit.c
* Abstract:	This file implements system initializing function.
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
#include "CG_port.h"
#include "CG_timer.h"
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

UCHAR __low_level_init(void);
void systeminit(void);
/*
**-----------------------------------------------------------------------------
**
**  Abstract:
**	This function initializes each macro.
**
**  Parameters:
**	None
**
**  Returns:
**	None
**
**-----------------------------------------------------------------------------
*/
void systeminit(void)
{
	DI();	/* disable interrupt */
	CG_ReadResetSource();
	PORT_Init();
	TAB0_Init();
	EI();	/* enable interrupt */
}
/*
**-----------------------------------------------------------------------------
**
**  Abstract:
**	This function initializes hardware setting.
**
**  Parameters:
**	None
**
**  Returns:
**	None
**
**-----------------------------------------------------------------------------
*/
UCHAR __low_level_init(void)
{
	VSWC = 0x13U;
	CLOCK_Init();	/* call Clock_Init function */
	systeminit();
	
	return MD_TRUE;
}

/* Start user code for adding. Do not edit comment generated here */
/* End user code. Do not edit comment generated here */
