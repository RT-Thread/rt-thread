/*
 * @brief LPC18xx/43xx WWDT chip driver
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

#include "wwdt_18xx_43xx.h"

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

/* Initialize the Watchdog timer */
void Chip_WWDT_Init(void)
{
	/* Disable watchdog */
	LPC_WWDT->MOD       = 0;
	LPC_WWDT->TC        = 0xFF;
	LPC_WWDT->WARNINT   = 0xFFFF;
	LPC_WWDT->WINDOW    = 0xFFFFFF;
}

/* Clear WWDT interrupt status flags */
void Chip_WWDT_ClearStatusFlag(uint32_t status)
{
	if (status & WWDT_WDMOD_WDTOF) {
		LPC_WWDT->MOD &= ~WWDT_WDMOD_WDTOF;
	}

	if (status & WWDT_WDMOD_WDINT) {
		LPC_WWDT->MOD |= WWDT_WDMOD_WDINT;
	}
}
