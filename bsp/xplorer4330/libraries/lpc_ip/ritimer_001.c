/*
 * @brief Repetitive Interrupt Timer registers and control functions
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

#include "ritimer_001.h"

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

/* Initialize the RIT */
void IP_RIT_Init(IP_RITIMER_001_Type *RITx)
{
	RITx->COMPVAL = 0xFFFFFFFF;
	RITx->MASK  = 0x00000000;
	RITx->CTRL  = 0x0C;
	RITx->COUNTER   = 0x00000000;
}

/* DeInitialize the RIT */
void IP_RIT_DeInit(IP_RITIMER_001_Type *RITx)
{
	IP_RIT_Init(RITx);
}

/* Enable/Disable Timer */
void IP_RIT_Enable(IP_RITIMER_001_Type *RITx, FunctionalState NewState)
{
	if (NewState == ENABLE) {
		RITx->CTRL |= RIT_CTRL_TEN;
	}
	else {
		RITx->CTRL &= ~RIT_CTRL_TEN;
	}
}

/* Enable or disable timer debug */
void IP_RIT_TimerDebugCmd(IP_RITIMER_001_Type *RITx, FunctionalState NewState)
{
	if (NewState == ENABLE) {
		RITx->CTRL |= RIT_CTRL_ENBR;
	}
	else {
		RITx->CTRL &= ~RIT_CTRL_ENBR;
	}
}

/* Check whether interrupt is pending */
IntStatus IP_RIT_GetIntStatus(IP_RITIMER_001_Type *RITx)
{
	uint8_t result;

	if ((RITx->CTRL & RIT_CTRL_INT) == 1) {
		result = SET;
	}
	else {
		return RESET;
	}

	return (IntStatus) result;
}
