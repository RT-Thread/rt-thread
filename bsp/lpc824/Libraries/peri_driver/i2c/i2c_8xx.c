/*
 * @brief LPC15xx I2C Common driver
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

/*****************************************************************************
 * Private types/enumerations/variables
 ****************************************************************************/

/*****************************************************************************
 * Public types/enumerations/variables
 ****************************************************************************/

/*****************************************************************************
 * Private functions
 ****************************************************************************/

/* Get the RESET ID corresponding to the given I2C base */
static CHIP_SYSCTL_PERIPH_RESET_T I2C_GetResetID(LPC_I2C_T *pI2C)
{
	uint32_t base = (uint32_t) pI2C;
	switch (base) {
		case LPC_I2C1_BASE:
			return RESET_I2C1;
		case LPC_I2C2_BASE:
			return RESET_I2C2;
		case LPC_I2C3_BASE:
			return RESET_I2C3;
		default:
			return RESET_I2C0;
	}
}

/* Get the CLOCK ID corresponding to the given I2C base */
static CHIP_SYSCTL_CLOCK_T I2C_GetClockID(LPC_I2C_T *pI2C)
{
	uint32_t base = (uint32_t) pI2C;
	switch (base) {
		case LPC_I2C1_BASE:
			return SYSCTL_CLOCK_I2C1;
		case LPC_I2C2_BASE:
			return SYSCTL_CLOCK_I2C2;
		case LPC_I2C3_BASE:
			return SYSCTL_CLOCK_I2C3;
		default:
			return SYSCTL_CLOCK_I2C0;
	}
}

/**
 * @brief	Sets HIGH and LOW duty cycle registers
 * @param	pI2C	: Pointer to selected I2C peripheral
 * @param	sclH	: Number of I2C_PCLK cycles for the SCL HIGH time value between (2 - 9).
 * @param	sclL	: Number of I2C_PCLK cycles for the SCL LOW time value between (2 - 9).
 * @return	Nothing
 * @note	The I2C clock divider should be set to the appropriate value before calling this function
 *				The I2C baud is determined by the following formula: <br>
 *        I2C_bitFrequency = (I2C_PCLK)/(I2C_CLKDIV * (sclH + sclL)) <br>
 *				where I2C_PCLK is the frequency of the System clock and I2C_CLKDIV is I2C clock divider
 */
static void Chip_I2CM_SetDutyCycle(LPC_I2C_T *pI2C, uint16_t sclH, uint16_t sclL)
{
	/* Limit to usable range of timing values */
	if (sclH < 2) {
		sclH = 2;
	}
	else if (sclH > 9) {
		sclH = 9;
	}
	if (sclL < 2) {
		sclL = 2;
	}
	else if (sclL > 9) {
		sclL = 9;
	}

	pI2C->MSTTIME = (((sclH - 2) & 0x07) << 4) | ((sclL - 2) & 0x07);
}

/*****************************************************************************
 * Public functions
 ****************************************************************************/

/* Initializes the LPC_I2C peripheral */
void Chip_I2C_Init(LPC_I2C_T *pI2C)
{
	/* Enable I2C clock */
	Chip_Clock_EnablePeriphClock(I2C_GetClockID(pI2C));

	/* Peripheral reset control to I2C */
	Chip_SYSCTL_PeriphReset(I2C_GetResetID(pI2C));
}

/* Shuts down the I2C controller block */
void Chip_I2C_DeInit(LPC_I2C_T *pI2C)
{
	/* Disable I2C clock */
	Chip_Clock_DisablePeriphClock(I2C_GetClockID(pI2C));
}

/* Set up bus speed for LPC_I2C interface */
void Chip_I2CM_SetBusSpeed(LPC_I2C_T *pI2C, uint32_t busSpeed)
{
	uint32_t scl = Chip_Clock_GetSystemClockRate() / (Chip_I2C_GetClockDiv(pI2C) * busSpeed);
	Chip_I2CM_SetDutyCycle(pI2C, (scl >> 1), (scl - (scl >> 1)));
}

/* Master transfer state change handler handler */
uint32_t Chip_I2CM_XferHandler(LPC_I2C_T *pI2C, I2CM_XFER_T *xfer)
{
	uint32_t status = Chip_I2CM_GetStatus(pI2C);
	/* Master Lost Arbitration */
	if (status & I2C_STAT_MSTRARBLOSS) {
		/* Set transfer status as Arbitration Lost */
		xfer->status = I2CM_STATUS_ARBLOST;
		/* Clear Status Flags */
		Chip_I2CM_ClearStatus(pI2C, I2C_STAT_MSTRARBLOSS);
	}
	/* Master Start Stop Error */
	else if (status & I2C_STAT_MSTSTSTPERR) {
		/* Set transfer status as Bus Error */
		xfer->status = I2CM_STATUS_BUS_ERROR;
		/* Clear Status Flags */
		Chip_I2CM_ClearStatus(pI2C, I2C_STAT_MSTSTSTPERR);
	}
	/* Master is Pending */
	else if (status & I2C_STAT_MSTPENDING) {
		/* Branch based on Master State Code */
		switch (Chip_I2CM_GetMasterState(pI2C)) {
		/* Master idle */
		case I2C_STAT_MSTCODE_IDLE:
			/* Do Nothing */
			break;

		/* Receive data is available */
		case I2C_STAT_MSTCODE_RXREADY:
			/* Read Data */
			*xfer->rxBuff++ = pI2C->MSTDAT;
			xfer->rxSz--;
			if (xfer->rxSz) {
				/* Set Continue if there is more data to read */
				Chip_I2CM_MasterContinue(pI2C);
			}
			else {
				/* Set transfer status as OK */
				xfer->status = I2CM_STATUS_OK;
				/* No data to read send Stop */
				Chip_I2CM_SendStop(pI2C);
			}
			break;

		/* Master Transmit available */
		case I2C_STAT_MSTCODE_TXREADY:
			if (xfer->txSz) {
				/* If Tx data available transmit data and continue */
				pI2C->MSTDAT = *xfer->txBuff++;
				xfer->txSz--;
				Chip_I2CM_MasterContinue(pI2C);
			}
			else {
				/* If receive queued after transmit then initiate master receive transfer*/
				if (xfer->rxSz) {
					/* Write Address and RW bit to data register */
					Chip_I2CM_WriteByte(pI2C, (xfer->slaveAddr << 1) | 0x1);
					/* Enter to Master Transmitter mode */
					Chip_I2CM_SendStart(pI2C);
				}
				else {
					/* If no receive queued then set transfer status as OK */
					xfer->status = I2CM_STATUS_OK;
					/* Send Stop */
					Chip_I2CM_SendStop(pI2C);
				}
			}
			break;

		case I2C_STAT_MSTCODE_NACKADR:
			/* Set transfer status as NACK on address */
			xfer->status = I2CM_STATUS_NAK_ADR;
			Chip_I2CM_SendStop(pI2C);
			break;

		case I2C_STAT_MSTCODE_NACKDAT:
			/* Set transfer status as NACK on data */
			xfer->status = I2CM_STATUS_NAK_DAT;
			Chip_I2CM_SendStop(pI2C);
			break;

		default:
			/* Default case should not occur*/
			xfer->status = I2CM_STATUS_ERROR;
			break;
		}
	}
	else {
		/* Default case should not occur */
		xfer->status = I2CM_STATUS_ERROR;
	}
	return xfer->status != I2CM_STATUS_BUSY;
}

/* Transmit and Receive data in master mode */
void Chip_I2CM_Xfer(LPC_I2C_T *pI2C, I2CM_XFER_T *xfer)
{
	/* set the transfer status as busy */
	xfer->status = I2CM_STATUS_BUSY;
	/* Clear controller state. */
	Chip_I2CM_ClearStatus(pI2C, I2C_STAT_MSTRARBLOSS | I2C_STAT_MSTSTSTPERR);
	/* Write Address and RW bit to data register */
	Chip_I2CM_WriteByte(pI2C, (xfer->slaveAddr << 1) | (xfer->txSz == 0));
	/* Enter to Master Transmitter mode */
	Chip_I2CM_SendStart(pI2C);
}

/* Transmit and Receive data in master mode */
uint32_t Chip_I2CM_XferBlocking(LPC_I2C_T *pI2C, I2CM_XFER_T *xfer)
{
	uint32_t ret = 0;
	/* start transfer */
	Chip_I2CM_Xfer(pI2C, xfer);

	while (ret == 0) {
		/* wait for status change interrupt */
		while (!Chip_I2CM_IsMasterPending(pI2C)) {}
		/* call state change handler */
		ret = Chip_I2CM_XferHandler(pI2C, xfer);
	}
	return ret;
}

/* Slave transfer state change handler */
uint32_t Chip_I2CS_XferHandler(LPC_I2C_T *pI2C, const I2CS_XFER_T *xfers)
{
	uint32_t done = 0;

	uint8_t data;
	uint32_t state;

	/* transfer complete? */
	if ((Chip_I2C_GetPendingInt(pI2C) & I2C_INTENSET_SLVDESEL) != 0) {
		Chip_I2CS_ClearStatus(pI2C, I2C_STAT_SLVDESEL);
		xfers->slaveDone();
	}
	else {
		/* Determine the current I2C slave state */
		state = Chip_I2CS_GetSlaveState(pI2C);

		switch (state) {
		case I2C_STAT_SLVCODE_ADDR:		/* Slave address received */
			/* Get slave address that needs servicing */
			data = Chip_I2CS_GetSlaveAddr(pI2C, Chip_I2CS_GetSlaveMatchIndex(pI2C));

			/* Call address callback */
			xfers->slaveStart(data);
			break;

		case I2C_STAT_SLVCODE_RX:		/* Data byte received */
			/* Get received data */
			data = Chip_I2CS_ReadByte(pI2C);
			done = xfers->slaveRecv(data);
			break;

		case I2C_STAT_SLVCODE_TX:		/* Get byte that needs to be sent */
			/* Get data to send */
			done = xfers->slaveSend(&data);
			Chip_I2CS_WriteByte(pI2C, data);
			break;
		}
	}

	if (done == 0) {
		Chip_I2CS_SlaveContinue(pI2C);
	}
	else {
		Chip_I2CS_SlaveNACK(pI2C);
	}

	return done;
}
