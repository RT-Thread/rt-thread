/*
 * @brief LPC8xx Self Wakeup Timer (WKT) chip driver
 *
 * @note
 * Copyright(C) NXP Semiconductors, 2012
 * All rights reserved.
 *
 * @par
 * Software that is described herein is for illustrative purposes only
 * which provides customers with programming information regarding the
 * LPC products.  This software is supplied "AS IS" without any warranties of
 * any kind, and NXP Semiconductors and its licensor disclaim any and
 * all warranties, express or implied, including all implied warranties of
 * merchantability, fitness for a particular purpose and non-infringement of
 * intellectual property rights.  NXP Semiconductors assumes no responsibility
 * or liability for the use of the software, conveys no license or rights under any
 * patent, copyright, mask work right, or any other intellectual property rights in
 * or to any products. NXP Semiconductors reserves the right to make changes
 * in the software without notification. NXP Semiconductors also makes no
 * representation or warranty that such application will be suitable for the
 * specified use without further testing or modification.
 *
 * @par
 * Permission to use, copy, modify, and distribute this software and its
 * documentation is hereby granted, under NXP Semiconductors' and its
 * licensor's relevant copyrights in the software, without fee, provided that it
 * is used in conjunction with NXP Semiconductors microcontrollers.  This
 * copyright, permission, and disclaimer notice must appear in all copies of
 * this code.
 */
#include "chip.h"

/*****************************************************************************
 * Private types/enumerations/variables
 ****************************************************************************/

/*****************************************************************************
 * Public types/enumerations/variables
 ****************************************************************************/

/*****************************************************************************
 * Private functions
 ****************************************************************************/

/*****************************************************************************
 * Public functions
 ****************************************************************************/

/* Set clock source for WKT */
void Chip_WKT_SetClockSource(LPC_WKT_T *pWKT, WKT_CLKSRC_T clkSrc)
{
	if (clkSrc == WKT_CLKSRC_10KHZ) {
		pWKT->CTRL |= WKT_CTRL_CLKSEL;	/* using Low Power clock 10kHz */
	}
	else {
		pWKT->CTRL &= ~WKT_CTRL_CLKSEL;	/* using Divided IRC clock 750kHz */
	}
}

/* Return approximate rate for the selected clock source */
uint32_t Chip_WKT_GetClockRate(LPC_WKT_T *pWKT)
{
	if (Chip_WKT_GetClockSource(pWKT) == WKT_CLKSRC_DIVIRC) {
		/* Approximately 750KHz */
		return (750 * 1000);
	}
	else {
		/* Approximately 10KHz */
		return (10 * 1000);
	}
}

/* Start wake-up timer interrupt, set clock source, set timer interval */
void Chip_WKT_Start(LPC_WKT_T *pWKT, WKT_CLKSRC_T clkSrc, uint32_t cntVal)
{
	/* Set the WKT clock source */
	Chip_WKT_SetClockSource(pWKT, (WKT_CLKSRC_T) clkSrc);

	/* Set the WKT counter & start it */
	pWKT->COUNT = cntVal;
}
