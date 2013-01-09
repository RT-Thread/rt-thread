/*
 * @brief LPC18xx/43xx System Control Unit (SCU) control functions
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

#include "scu_18xx_43xx.h"

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

/* Configure pin function */
void Chip_SCU_PinMux(uint8_t port, uint8_t pin, uint8_t mode, uint8_t func)
{
	if (port == PINMUX_CLK) {
		LPC_SCU_CLK(((uint32_t) LPC_SCU), pin) = mode + func;
	}
	else {
		LPC_SCU->SFSP[port][pin] = mode + func;
	}
}

/* GPIO Interrupt Pin Select */
void Chip_SCU_GPIOIntPinSel(uint8_t PortSel, uint8_t PortNum, uint8_t PinNum)
{
	uint8_t  pinInt;
	volatile uint32_t pinSel;

	pinInt = ((PortNum & 0x7) << 5) | (PinNum & 0x1F);
	if (PortSel < 4) {
		pinSel = LPC_SCU->PINTSEL0;
		pinSel &= ~(0xFF << (PortSel * 8));
		pinSel |= (pinInt << (PortSel * 8));
		LPC_SCU->PINTSEL0 = pinSel;
	}
	else {
		pinSel = LPC_SCU->PINTSEL1;
		pinSel &= ~(0xFF << ((PortSel - 4) * 8));
		pinSel |= (pinInt << ((PortSel - 4) * 8));
		LPC_SCU->PINTSEL1 = pinSel;
	}
}
