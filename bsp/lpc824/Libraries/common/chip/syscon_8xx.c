/*
 * @brief LPC8xx System & Control driver
 *
 * @note
 * Copyright(C) NXP Semiconductors, 2012
 * All rights reserved.
 *
 * @par
 * Software that is described herein is for illustrative purposes only
 * which provides customers with programming information regarding the
 * LPC products.  This software is supplied "AS IS" without any warranties of
 * any kind, and NXP Semiconductors and its licenser disclaim any and
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
#define _CHIP_COMMON_
#include "chip.h"

/*****************************************************************************
 * Private types/enumerations/variables
 ****************************************************************************/

/* PDSLEEPCFG register mask */
#define PDSLEEPWRMASK   (0x0000FFB7)
#define PDSLEEPDATMASK  (0x00000048)

#if defined(CHIP_LPC82X)
/* PDWAKECFG and PDRUNCFG register masks */
#define PDWAKEUPWRMASK  (0x00006D00)
#define PDWAKEUPDATMASK (0x000080FF)

#else
/* PDWAKECFG and PDRUNCFG register masks */
#define PDWAKEUPWRMASK  (0x00006D10)
#define PDWAKEUPDATMASK (0x000080EF)
#endif

/*****************************************************************************
 * Public types/enumerations/variables
 ****************************************************************************/

/*****************************************************************************
 * Private functions
 ****************************************************************************/

/*****************************************************************************
 * Public functions
 ****************************************************************************/

/* Setup deep sleep behaviour for power down */
void Chip_SYSCTL_SetDeepSleepPD(uint32_t sleepmask)
{
	/* Update new value */
	LPC_SYSCTL->PDSLEEPCFG = PDSLEEPWRMASK | (sleepmask & PDSLEEPDATMASK);
}

/* Setup wakeup behaviour from deep sleep */
void Chip_SYSCTL_SetWakeup(uint32_t wakeupmask)
{
	/* Update new value */
	LPC_SYSCTL->PDAWAKECFG = PDWAKEUPWRMASK | (wakeupmask & PDWAKEUPDATMASK);
}

/* Power down one or more blocks or peripherals */
void Chip_SYSCTL_PowerDown(uint32_t powerdownmask)
{
	uint32_t pdrun;

	/* Get current power states */
	pdrun = LPC_SYSCTL->PDRUNCFG & PDWAKEUPDATMASK;

	/* Disable peripheral states by setting high */
	pdrun |= (powerdownmask & PDWAKEUPDATMASK);

	/* Update power states with required register bits */
	LPC_SYSCTL->PDRUNCFG = (PDWAKEUPWRMASK | pdrun);
}

/* Power up one or more blocks or peripherals */
void Chip_SYSCTL_PowerUp(uint32_t powerupmask)
{
	uint32_t pdrun;

	/* Get current power states */
	pdrun = LPC_SYSCTL->PDRUNCFG & PDWAKEUPDATMASK;

	/* Enable peripheral states by setting low */
	pdrun &= ~(powerupmask & PDWAKEUPDATMASK);

	/* Update power states with required register bits */
	LPC_SYSCTL->PDRUNCFG = (PDWAKEUPWRMASK | pdrun);
}
