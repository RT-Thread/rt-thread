/*
 * @brief LPC18xx/43xx Reset Generator Unit driver
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

#include "rgu_18xx_43xx.h"

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

/* Trigger a peripheral reset for the selected peripheral */
void Chip_RGU_TriggerReset(RGU_RST_TYPE ResetNumber)
{
	volatile uint32_t *p;

	/* To trigger reset- write RESET_CTRLx with a 1 bit */
	p = (volatile uint32_t *) &(LPC_RGU->RESET_CTRL0);

	/* higher numbers are in RESET_CTRL1, RESET_CTRL2, etc. */
	p += ResetNumber / 32;

	/* On the LPC18xx and LPC43xx, most of the reset bits automatically clear
	   after 1 clock cycle, so set the bit and return */
	*p = (1 << (ResetNumber % 32));
}

/* Clears reset for the selected peripheral */
void Chip_RGU_ClearReset(RGU_RST_TYPE ResetNumber)
{
	volatile uint32_t *p;

	/* To trigger reset- write RESET_CTRLx with a 1 bit */
	p = (volatile uint32_t *) &(LPC_RGU->RESET_CTRL0);

	/* higher numbers are in RESET_CTRL1, RESET_CTRL2, etc. */
	p += ResetNumber / 32;

	/* On the LPC18xx and LPC43xx, most of the reset bits automatically clear
	   after 1 clock cycle, so set the bit and return */
	*p = 0;
}

/* Checks the reset status of a peripheral */
bool Chip_RGU_InReset(RGU_RST_TYPE ResetNumber)
{
	volatile uint32_t *read;

	read = (volatile uint32_t *) &(LPC_RGU->RESET_ACTIVE_STATUS0);
	read += ResetNumber / 32;

	/* Reset not asserted if bit is set */
	return (bool) ((*read & (1 << (ResetNumber % 32))) == 0);
}
