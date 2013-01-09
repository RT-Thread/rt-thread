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
* Filename:	CG_port.c
* Abstract:	This file implements device driver for PORT module.
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
#include "CG_port.h"
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

/*
**-----------------------------------------------------------------------------
**
**  Abstract:
**	This function initializes setting for Port I/O.
**
**  Parameters:
**	None
**
**  Returns:
**	None
**
**-----------------------------------------------------------------------------
*/
void PORT_Init(void)
{
	PDLH = _10_Pn4_OUTPUT_1;
	PMDLH = _01_PMn0_MODE_UNUSED | _02_PMn1_MODE_UNUSED | _04_PMn2_MODE_UNUSED | _08_PMn3_MODE_UNUSED | _00_PMn4_MODE_OUTPUT | _20_PMn5_MODE_UNUSED | _40_PMn6_MODE_UNUSED | _80_PMn7_MODE_UNUSED;
	PMCDLH = _00_PMCn4_OPER_PORT;
}

void led_on(void)
{
    PDLH = _10_Pn4_OUTPUT_1;
}

void led_off(void)
{
    PDLH = _00_Pn4_OUTPUT_0;
}

/* Start user code for adding. Do not edit comment generated here */
/* End user code. Do not edit comment generated here */
