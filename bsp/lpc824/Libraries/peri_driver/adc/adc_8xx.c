/*
 * @brief LPC82x ADC driver
 *
 * @note
 * Copyright(C) NXP Semiconductors, 2014
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
#include "adc_8xx.h"
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

/* Initialize the ADC peripheral */
void Chip_ADC_Init(LPC_ADC_T *pADC, uint32_t flags)
{
	/* Power up ADC and enable ADC base clock */
	Chip_SYSCTL_PowerUp(SYSCTL_SLPWAKE_ADC_PD);
	Chip_Clock_EnablePeriphClock(SYSCTL_CLOCK_ADC);

	/* Disable ADC interrupts */
	pADC->INTEN = 0;

	/* Set ADC control options */
	pADC->CTRL = flags;
}

/* Shutdown ADC */
void Chip_ADC_DeInit(LPC_ADC_T *pADC)
{
	pADC->INTEN = 0;
	pADC->CTRL = 0;

	/* Stop ADC clock and then power down ADC */
	Chip_Clock_DisablePeriphClock(SYSCTL_CLOCK_ADC);
	Chip_SYSCTL_PowerDown(SYSCTL_SLPWAKE_ADC_PD);
}

/* Start ADC calibration */
void Chip_ADC_StartCalibration(LPC_ADC_T *pADC)
{
	/* Set calibration mode */
	pADC->CTRL |= ADC_CR_CALMODEBIT;

	/* Clear ASYNC bit */
	pADC->CTRL &= ~ADC_CR_ASYNMODE;

	/* Setup ADC for about 500KHz (per UM) */
	Chip_ADC_SetClockRate(pADC, 500000);

	/* Clearn low power bit */
	pADC->CTRL &= ~ADC_CR_LPWRMODEBIT;

	/* Calibration is only complete when ADC_CR_CALMODEBIT bit has cleared */
}
