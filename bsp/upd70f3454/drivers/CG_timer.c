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
* Filename:	CG_timer.c
* Abstract:	This file implements device driver for Timer module.
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
#include "CG_timer.h"
/* Start user code for include. Do not edit comment generated here */
/* End user code. Do not edit comment generated here */
#include "CG_userdefine.h"

/*
*******************************************************************************
**  Global define
*******************************************************************************
*/
/* Count Clock (TABnCTL0) */
#define	TAB_CNT_CLK				0x00	/* Count Clock fxx */
#define	TAB_CNT_CLK_2			0x01	/* Count Clock fxx/2 */
#define	TAB_CNT_CLK_4			0x02	/* Count Clock fxx/4 */
#define	TAB_CNT_CLK_8			0x03	/* Count Clock fxx/8 */
#define	TAB_CNT_CLK_16			0x04	/* Count Clock fxx/16 */
#define	TAB_CNT_CLK_32			0x05	/* Count Clock fxx/32 */
#define	TAB_CNT_CLK_64			0x06	/* Count Clock fxx/64 */
#define	TAB_CNT_CLK_128			0x07	/* Count Clock fxx/128 */
/* Mode (TABkMD2 + TABkMD1 + TABkMD0) */
#define	TAB_INTERVAL_MODE		0x00	/* Interval Timer Mode */
/* TAB0I/O Control Register (TABmIOC0) */
#define	TAB_TOB00_DISABLE		0x00	/* TOB00 Output Disable */
#define	TAB_TOB00_ENABLE		0x01	/* TOB00 Output Enable */
#define	TAB_TOB00_HI_LEV_ST		0x00	/* TOB00 Output High Level Start */
#define	TAB_TOB00_LO_LEV_ST		0x02	/* TOB00 Output Low Level Start */
#define	TAB_TOB01_DISABLE		0x00	/* TOB01 Output Disable */
#define	TAB_TOB01_ENABLE		0x04	/* TOB01 Output Enable */
#define	TAB_TOB01_HI_LEV_ST		0x00	/* TOB01 Output High Level Start */
#define	TAB_TOB01_LO_LEV_ST		0x08	/* TOB01 Output Low Level Start */
#define	TAB_TOB02_DISABLE		0x00	/* TOB02 Output Disable */
#define	TAB_TOB02_ENABLE		0x10	/* TOB02 Output Enable */
#define	TAB_TOB02_HI_LEV_ST		0x00	/* TOB02 Output High Level Start */
#define	TAB_TOB02_LO_LEV_ST		0x20	/* TOB02 Output Low Level Start */
#define	TAB_TOB03_DISABLE		0x00	/* TOB03 Output Disable */
#define	TAB_TOB03_ENABLE		0x40	/* TOB03 Output Enable */
#define	TAB_TOB03_HI_LEV_ST		0x00	/* TOB03 Output High Level Start */
#define	TAB_TOB03_LO_LEV_ST		0x80	/* TOB03 Output Low Level Start */
/* Start user code for global. Do not edit comment generated here */
/* End user code. Do not edit comment generated here */

void timerab_interval(void)
{
	TAB0CTL0 = TAB_CNT_CLK_32;			/* TAB0CKS2 = 1 + TAB0CKS1 = 0 + TAB0CKS0 = 0 */
										/*  : Clock Count = fxx/32 */
	TAB0CTL1 = TAB_INTERVAL_MODE;		/* TAB0MD2 = 0 + TAB0MD1 = 0 + TAB0MD0 = 0 */
										/*  : Interval Timer Mode */
//	TAB0IOC2 = TAB_TOB03_LO_LEV_ST |	/* TAB0OL3 = 1 : TOB03 Low Level Start */
//			   TAB_TOB03_DISABLE   |	/* TAB0OE3 = 0 : TOB03 Output Disable */
//			   TAB_TOB02_LO_LEV_ST |	/* TAB0OL2 = 1 : TOB02 Low Level Start */
//			   TAB_TOB02_DISABLE   |	/* TAB0OE2 = 0 : TOB02 Output Disable */
//			   TAB_TOB01_HI_LEV_ST |	/* TAB0OL1 = 0 : TOB01 High Level Start */
//			   TAB_TOB01_ENABLE    |	/* TAB0OE1 = 1 : TOB01 Output Enable */
//			   TAB_TOB00_HI_LEV_ST |	/* TAB0OL0 = 0 : TOB00 High Level Start */
//			   TAB_TOB00_ENABLE;		/* TAB0OE0 = 1 : TOB00 Output Enable */
	TAB0CCR0	= 19999;				/* Compare Register */
	TAB0CCR1 = 0xFFFF;					/* Compare Register */
	TAB0CCR2 = 0xFFFF;					/* No Use */
	TAB0CCR3 = 0xFFFF;					/* No Use */
}

/*
**-----------------------------------------------------------------------------
**
**  Abstract:
**	This function initializes the TAB0 module.
**
**  Parameters:
**	None
**
**  Returns:
**	None
**
**-----------------------------------------------------------------------------
*/
void TAB0_Init(void)
{
	TAB0CE = 0;							/* Stop TAB */

	/* Port Definition */
//	PFC1 = 0x00;						/* PFC17 = 0 : TOB00 Output */
										/* PFC10 = 0 : TOB01 Output */
//	PFCE1 = 0x01;						/* PFCE10 = 1 : TOB01 Output */
//	PMC1 = 0x81;						/* PMC17 = 1 : TOB00 Output/INTP09 Input */
										/* PMC10 = 1 : TOB0T1 Output/TIB01 Input/TOB01 Output */

	/* Enable Interrupt */
	TB0CCMK0 = 0;						/* TB0CCMK0 = 0 : INTTB0CC0 Enable */
	TB0CCMK1 = 1;						/* TB0CCMK1 = 0 : INTTB0CC1 Enable */
	TB0CCMK2 = 1;						/* TB0CCMK2 = 1 : INTTB0CC2 Disable */
	TB0CCMK3 = 1;						/* TB0CCMK3 = 1 : INTTB0CC3 Disable */

	timerab_interval();
}
/*
**-----------------------------------------------------------------------------
**
**  Abstract:
**	This function starts TMP0 counter.
**
**  Parameters:
**	None
**
**  Returns:
**	None
**
**-----------------------------------------------------------------------------
*/
void TAB0_Start(void)
{
	TB0CCIF0 = 0U;	/* clear INTTP0CC0 interrupt flag */
	TB0CCMK0 = 0U;	/* enable INTTP0CC0 interrupt */
	TAB0CE = 1U;	/* enable TMP0 operation */
}
/*
**-----------------------------------------------------------------------------
**
**  Abstract:
**	This function stops TMP0 counter.
**
**  Parameters:
**	None
**
**  Returns:
**	None
**
**-----------------------------------------------------------------------------
*/
void TAB0_Stop(void)
{
	TAB0CE = 0U;	/* disable TMP0 operation */
	TB0CCMK0 = 1U;	/* disable INTTP0CC0 interrupt */
	TB0CCIF0 = 0U;	/* clear INTTP0CC0 interrupt flag */
}
/*
**-----------------------------------------------------------------------------
**
**  Abstract:
**	This function changes TMP0 register value.
**
**  Parameters:
**	array_reg: register value buffer
**	array_num: register index to be changed
**
**  Returns:
**	MD_OK
**	MD_ARGERROR
**
**-----------------------------------------------------------------------------
*/
MD_STATUS TAB0_ChangeTimerCondition(USHORT *array_reg, UCHAR array_num)
{
	MD_STATUS status = MD_OK;

	switch (array_num)
	{
		case 1U:
			TAB0CCR0 = array_reg[0U];
			status = MD_OK;
			break;
		case 2U:
			TAB0CCR0 = array_reg[0U];
			TAB0CCR1 = array_reg[1U];
			status = MD_OK;
			break;
		default:
			status = MD_ARGERROR;
			break;
	}
	
	return (status);
}

/* Start user code for adding. Do not edit comment generated here */
/* End user code. Do not edit comment generated here */
