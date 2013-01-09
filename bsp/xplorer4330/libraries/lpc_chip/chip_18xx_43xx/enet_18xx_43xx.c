/*
 * @brief LPC18xx/43xx ethernet driver
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

#include "enet_18xx_43xx.h"

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

/* Basic Ethernet interface initialization */
void Chip_ENET_Init(void)
{
	LPC_CREG->CREG6 &= ~0x7;

	/* Enable ethernet clock */
	Chip_Clock_EnableOpts(CLK_MX_ETHERNET, true, true, 1);

	/* PHY TX/RX base clock routing is setup as part of SystemInit() */

#if defined(USE_RMII)
	LPC_CREG->CREG6 |= 0x4;
#endif

	/* Reset ethernet and wait for reset to complete */
	Chip_RGU_TriggerReset(RGU_ETHERNET_RST);
	while (Chip_RGU_InReset(RGU_ETHERNET_RST)) {}

	/* Reset ethernet peripheral */
	Chip_ENET_Reset();

	/* Setup MII link divider to /102 and PHY address 1 */
	Chip_ENET_Setup_MII(4, 1);

	IP_ENET_Init(LPC_ETHERNET);
}

/* Ethernet interface shutdown */
void Chip_ENET_DeInit(void)
{
	IP_ENET_DeInit(LPC_ETHERNET);
	Chip_Clock_Disable(CLK_MX_ETHERNET);
}
