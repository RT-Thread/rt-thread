/*
 * @brief LPC8xx PMU chip driver
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

/* Reserved bits mask for SCR register */
#define SCB_SCR_RESERVED (~(SCB_SCR_SLEEPONEXIT_Msk|SCB_SCR_SLEEPDEEP_Msk|SCB_SCR_SEVONPEND_Msk))

/*****************************************************************************
 * Public types/enumerations/variables
 ****************************************************************************/

/*****************************************************************************
 * Private functions
 ****************************************************************************/

/*****************************************************************************
 * Public functions
 ****************************************************************************/

/* Enter MCU Sleep mode */
void Chip_PMU_SleepState(LPC_PMU_T *pPMU)
{
	SCB->SCR = ~(1UL << SCB_SCR_SLEEPDEEP_Pos) & (SCB->SCR & ~SCB_SCR_RESERVED);
	pPMU->PCON = PMU_PCON_PM_SLEEP;

	/* Enter sleep mode */
	__WFI();
}

/* Enter MCU Deep Sleep mode */
void Chip_PMU_DeepSleepState(LPC_PMU_T *pPMU)
{
	SCB->SCR = (1UL << SCB_SCR_SLEEPDEEP_Pos) | (SCB->SCR & ~SCB_SCR_RESERVED);
	pPMU->PCON = PMU_PCON_PM_DEEPSLEEP;

	/* Enter sleep mode */
	__WFI();
}

/* Enter MCU Power down mode */
void Chip_PMU_PowerDownState(LPC_PMU_T *pPMU)
{
	SCB->SCR = (1UL << SCB_SCR_SLEEPDEEP_Pos) | (SCB->SCR & ~SCB_SCR_RESERVED);
	pPMU->PCON = PMU_PCON_PM_POWERDOWN;

	/* Enter sleep mode */
	__WFI();
}

/* Enter MCU Deep Power down mode */
void Chip_PMU_DeepPowerDownState(LPC_PMU_T *pPMU)
{
	SCB->SCR = (1UL << SCB_SCR_SLEEPDEEP_Pos) | (SCB->SCR & ~SCB_SCR_RESERVED);
	pPMU->PCON = PMU_PCON_PM_DEEPPOWERDOWN;

	/* Enter sleep mode */
	__WFI();
}

/* Put some of the peripheral in sleep mode */
void Chip_PMU_Sleep(LPC_PMU_T *pPMU, CHIP_PMU_MCUPOWER_T SleepMode)
{
	if (SleepMode == PMU_MCU_DEEP_SLEEP) {
		Chip_PMU_DeepSleepState(pPMU);
	}
	else if (SleepMode == PMU_MCU_POWER_DOWN) {
		Chip_PMU_PowerDownState(pPMU);
	}
	else if (SleepMode == PMU_MCU_DEEP_PWRDOWN) {
		Chip_PMU_DeepPowerDownState(pPMU);
	}
	else {
		/* PMU_MCU_SLEEP */
		Chip_PMU_SleepState(pPMU);
	}
}
