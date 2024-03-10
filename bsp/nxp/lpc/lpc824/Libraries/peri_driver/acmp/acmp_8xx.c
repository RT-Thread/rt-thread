/*
 * @brief LPC8xx Analog comparator driver
 *
 * Copyright(C) NXP Semiconductors, 2012
 * All rights reserved.
 *
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

/* Initializes the ACMP */
void Chip_ACMP_Init(LPC_CMP_T *pACMP)
{
	Chip_SYSCTL_PowerUp(SYSCTL_SLPWAKE_ACMP_PD);
	Chip_Clock_EnablePeriphClock(SYSCTL_CLOCK_ACOMP);
}

/* De-initializes the ACMP */
void Chip_ACMP_Deinit(LPC_CMP_T *pACMP)
{
	Chip_Clock_DisablePeriphClock(SYSCTL_CLOCK_ACOMP);
	Chip_SYSCTL_PowerDown(SYSCTL_SLPWAKE_ACMP_PD);
}

/* Clears the ACMP interrupt (EDGECLR bit) */
void Chip_ACMP_EdgeClear(LPC_CMP_T *pACMP)
{
	uint32_t reg = pACMP->CTRL & ~ACMP_CTRL_RESERVED;

	/* Toggle EDGECLR bit high and then low */
	pACMP->CTRL = reg | ACMP_EDGECLR_BIT;
	pACMP->CTRL = reg & ~ACMP_EDGECLR_BIT;
}

/* Sets up ACMP edge selection */
void Chip_ACMP_SetEdgeSelection(LPC_CMP_T *pACMP, ACMP_EDGESEL_T edgeSel)
{
	uint32_t reg = pACMP->CTRL & ~(ACMP_EDGESEL_MASK | ACMP_CTRL_RESERVED);

	/* Select edge for COMPEDGE */
	pACMP->CTRL = reg | (uint32_t) edgeSel;
}

/* Selects positive voltage input */
void Chip_ACMP_SetPosVoltRef(LPC_CMP_T *pACMP, ACMP_POS_INPUT_T Posinput)
{
	uint32_t reg = pACMP->CTRL & ~(ACMP_COMPVPSEL_MASK | ACMP_CTRL_RESERVED);

	/* Select positive input */
	pACMP->CTRL = reg | (uint32_t) Posinput;
}

/* Selects negative voltage input */
void Chip_ACMP_SetNegVoltRef(LPC_CMP_T *pACMP, ACMP_NEG_INPUT_T Neginput)
{
	uint32_t reg = pACMP->CTRL & ~(ACMP_COMPVMSEL_MASK | ACMP_CTRL_RESERVED);

	/* Select negative input */
	pACMP->CTRL = reg | (uint32_t) Neginput;
}

/* Selects hysteresis level */
void Chip_ACMP_SetHysteresis(LPC_CMP_T *pACMP, ACMP_HYS_T hys)
{
	uint32_t reg = pACMP->CTRL & ~(ACMP_HYSTERESIS_MASK | ACMP_CTRL_RESERVED);

	/* Select negative input */
	pACMP->CTRL = reg | (uint32_t) hys;
}

/* Helper function for setting up ACMP control */
void Chip_ACMP_SetupAMCPRefs(LPC_CMP_T *pACMP, ACMP_EDGESEL_T edgeSel,
							 ACMP_POS_INPUT_T Posinput, ACMP_NEG_INPUT_T Neginput,
							 ACMP_HYS_T hys)
{
	uint32_t reg = pACMP->CTRL & ~(ACMP_HYSTERESIS_MASK | ACMP_CTRL_RESERVED |
								   ACMP_COMPVMSEL_MASK | ACMP_COMPVPSEL_MASK | ACMP_EDGESEL_MASK);

	/* Select negative input */
	pACMP->CTRL = reg | (uint32_t) edgeSel | (uint32_t) Posinput |
				  (uint32_t) Neginput | (uint32_t) hys;
}

/* Sets up voltage ladder */
void Chip_ACMP_SetupVoltLadder(LPC_CMP_T *pACMP, uint32_t ladsel, bool ladrefVDDCMP)
{
	uint32_t reg = pACMP->LAD & ~(ACMP_LADSEL_MASK | ACMP_LADREF_MASK | ACMP_LAD_RESERVED);

	/* Setup voltage ladder and ladder reference */
	if (ladrefVDDCMP) {
		reg |= ACMP_LADREF_MASK;
	}
	pACMP->LAD = reg | (ladsel << 1);
}
