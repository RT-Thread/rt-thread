/*
 * @brief LPC8xx IOCON driver
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

#define PINASSIGN_IDX(movable)  (((movable) >> 4))
#define PINSHIFT(movable)       (((movable) & 0xF) << 3)

/*****************************************************************************
 * Public types/enumerations/variables
 ****************************************************************************/

/*****************************************************************************
 * Private functions
 ****************************************************************************/

/*****************************************************************************
 * Public functions
 ****************************************************************************/

/* Set the pin mode (pull-up/pull-down). */
void Chip_IOCON_PinSetMode(LPC_IOCON_T *pIOCON, CHIP_PINx_T pin, CHIP_PIN_MODE_T mode)
{
	uint32_t reg;

	reg = pIOCON->PIO0[pin] & ~(PIN_MODE_MASK);
	pIOCON->PIO0[pin] = reg | (mode << PIN_MODE_BITNUM);
}

/* Enables/disables the pin hysteresis. */
void Chip_IOCON_PinSetHysteresis(LPC_IOCON_T *pIOCON, CHIP_PINx_T pin, bool enable)
{
	if (enable == true) {
		Chip_IOCON_PinEnableHysteresis(pIOCON, pin);
	}
	else {
		Chip_IOCON_PinDisableHysteresis(pIOCON, pin);
	}
}

/*Inverts (or not) the input seen by a pin. */
void Chip_IOCON_PinSetInputInverted(LPC_IOCON_T *pIOCON, CHIP_PINx_T pin, bool invert)
{
	if (invert == true) {
		Chip_IOCON_PinEnableInputInverted(pIOCON, pin);
	}
	else {
		Chip_IOCON_PinDisableInputInverted(pIOCON, pin);
	}
}

/* Enables/disables Open-Drain mode for a pin. */
void Chip_IOCON_PinSetOpenDrainMode(LPC_IOCON_T *pIOCON, CHIP_PINx_T pin, bool open_drain)
{
	if (open_drain == true) {
		Chip_IOCON_PinEnableOpenDrainMode(pIOCON, pin);
	}
	else {
		Chip_IOCON_PinDisableOpenDrainMode(pIOCON, pin);
	}
}

/* Enable/configure digital filter sample mode for a pin. */
void Chip_IOCON_PinSetSampleMode(LPC_IOCON_T *pIOCON, CHIP_PINx_T pin, CHIP_PIN_SMODE_T smode)
{
	uint32_t reg;

	reg = pIOCON->PIO0[pin] & ~(PIN_SMODE_MASK);
	pIOCON->PIO0[pin] = reg | (smode << PIN_SMODE_BITNUM);
}

/* Set the peripheral clock divisor for a pin. */
void Chip_IOCON_PinSetClockDivisor(LPC_IOCON_T *pIOCON, CHIP_PINx_T pin, CHIP_PIN_CLKDIV_T clkdiv)
{
	uint32_t reg;

	reg = pIOCON->PIO0[pin] & ~(PIN_CLKDIV_MASK);
	pIOCON->PIO0[pin] = reg | (clkdiv << PIN_CLKDIV_BITNUM);
}

/* Set the I2C mode for a pin. */
void Chip_IOCON_PinSetI2CMode(LPC_IOCON_T *pIOCON, CHIP_PINx_T pin, CHIP_PIN_I2CMODE_T mode)
{
	uint32_t reg;

	/* I2C mode bits only for I2C pins */
	reg = pIOCON->PIO0[pin] & ~(PIN_I2CMODE_MASK);
	pIOCON->PIO0[pin] = reg | (mode << PIN_I2CMODE_BITNUM);
}

/* Set all I/O Control pin muxing */
void Chip_IOCON_SetPinMuxing(LPC_IOCON_T *pIOCON, const PINMUX_GRP_T* pinArray, uint32_t arrayLength)
{
	uint32_t ix;

	for (ix = 0; ix < arrayLength; ix++ ) {
		Chip_IOCON_PinMuxSet(pIOCON, pinArray[ix].pin, pinArray[ix].modefunc);
	}
}

/* assign a movable pin function to a physical pin */
void Chip_SWM_MovablePinAssign(CHIP_SWM_PIN_MOVABLE_T movable, uint8_t pin)
{
	uint32_t temp;
	int pinshift = PINSHIFT(movable), regIndex = PINASSIGN_IDX(movable);

	temp = LPC_SWM->PINASSIGN[regIndex] & (~(0xFF << pinshift));
	LPC_SWM->PINASSIGN[regIndex] = temp | (pin << pinshift);
}

/* true enables, false disables a Switch Matrix fixed-pin Function */
void Chip_SWM_FixedPinEnable(CHIP_SWM_PIN_FIXED_T pin, bool enable)
{
	if (enable) {
		Chip_SWM_EnableFixedPin(pin);
	}
	else {
		Chip_SWM_DisableFixedPin(pin);
	}
}
