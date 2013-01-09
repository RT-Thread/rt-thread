/*
 * @brief GPIO Interrupt Registers and control functions
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

#include "gpioint_001.h"

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

/* Enable GPIO Interrupt */
void IP_GPIOINT_IntCmd(IP_GPIOINT_001_Type *pGPIOPININT, uint8_t PortNum, uint32_t BitValue, Gpio_Int_Mode_Enum IntMode)
{
	if (PortNum == 0) {
		if (IntMode == IP_GPIOINT_RISING_EDGE) {
			pGPIOPININT->EnR0 = BitValue;
		}
		else {
			pGPIOPININT->EnF0 = BitValue;
		}
	}
	else if (PortNum == 2) {
		if (IntMode == IP_GPIOINT_RISING_EDGE) {
			pGPIOPININT->EnR2 = BitValue;
		}
		else {
			pGPIOPININT->EnF2 = BitValue;
		}
	}
}

/*Get GPIO Interrupt Status */
bool IP_GPIOINT_IntGetStatus(IP_GPIOINT_001_Type *pGPIOPININT,
							 uint8_t PortNum,
							 uint32_t PinNum,
							 Gpio_Int_Mode_Enum IntMode)
{
	if (PortNum == 0) {
		if (IntMode == IP_GPIOINT_RISING_EDGE) {
			return (bool) ((pGPIOPININT->StatR0 >> PinNum) & 0x1);
		}
		else {
			return (bool) ((pGPIOPININT->StatF0 >> PinNum) & 0x1);
		}
	}
	else if (PortNum == 2) {
		if (IntMode == IP_GPIOINT_RISING_EDGE) {
			return (bool) ((pGPIOPININT->StatR2 >> PinNum) & 0x1);
		}
		else {
			return (bool) ((pGPIOPININT->StatF2 >> PinNum) & 0x1);
		}
	}

	return false;
}

/**
 * @brief	Clear GPIO Interrupt (Edge interrupt cases only)
 * @param	PortNum		: GPIO port number interrupt, should be: 0 (port 0) or 2 (port 2)
 * @param	BitValue	: GPIO Bit value that contains all bits on GPIO to enable, should be 0 to 0xFFFFFFFF
 * @return	None
 */
void IP_GPIOINT_IntClear(IP_GPIOINT_001_Type *pGPIOPININT, uint8_t PortNum, uint32_t BitValue)
{
	if (PortNum == 0) {
		pGPIOPININT->Clr0 = BitValue;
	}
	else if (PortNum == 2) {
		pGPIOPININT->Clr2 = BitValue;
	}
}
