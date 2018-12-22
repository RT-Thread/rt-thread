/*
 * @brief I2C master ROM API declarations and functions
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

#include <stdint.h>
#include <string.h>
#include "hw_i2cmd.h"

#define DRVVERSION 0x0100

/* Private data structure used for the I2C master driver, holds the driver and
   peripheral context */
typedef struct {
	void                        *pUserData;		/*!< Pointer to user data used by driver instance, use NULL if not used */
	LPC_I2C_T                   *base;			/*!< Base address of I2C peripheral to use */
	i2cMasterCompleteCB         pXferCompCB;	/*!< Transfer complete callback */
	i2cMasterTransmitStartCB    pTranStartCb;	/*!< Transmit data start callback */
	i2cMasterReceiveStartCB     pTranRecvCb;	/*!< Receive data start callback */
	ROM_I2CM_XFER_T             *pXfer;			/*!< Pointer to current transfer */
	ErrorCode_t                 pendingStatus;	/*!< Pending master transfer status before clocking transfer */
	uint16_t                    sendIdx;
	uint16_t                    recvIdx;
} I2CM_DATACONTEXT_T;

#define _rom_i2cmEnable(pI2C)           (pI2C->CFG |= I2C_CFG_MSTEN);
#define _rom_i2cmGetMasterState(pI2C)   ((pI2C->STAT & I2C_STAT_MSTSTATE) >> 1)

/* Sets I2C Clock Divider registers */
static void _rom_i2cmSetClockDiv(LPC_I2C_T *pI2C, uint32_t clkdiv)
{
	if ((clkdiv >= 1) && (clkdiv <= 65536)) {
		pI2C->CLKDIV = clkdiv - 1;
	}
	else {
		pI2C->CLKDIV = 0;
	}
}

/* Sets HIGH and LOW duty cycle registers */
static void _rom_i2cmSetDutyCycle(LPC_I2C_T *pI2C, uint16_t sclH, uint16_t sclL)
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

// **********************************************************
uint32_t i2cm_get_mem_size(void)
{
	return sizeof(I2CM_DATACONTEXT_T);
}

ROM_I2CM_HANDLE_T i2cm_init(void *mem, const ROM_I2CM_INIT_T *pInit)
{
	I2CM_DATACONTEXT_T *pDrv;

	/* Verify alignment is at least 4 bytes */
	if (((uint32_t) mem & 0x3) != 0) {
		return NULL;
	}

	pDrv = (I2CM_DATACONTEXT_T *) mem;
	memset(pDrv, 0, sizeof(I2CM_DATACONTEXT_T));

	/* Save base of peripheral and pointer to user data */
	pDrv->pUserData = pInit->pUserData;
	pDrv->base = (LPC_I2C_T *) pInit->base;

	/* Pick a safe clock divider until clock rate is setup */
	_rom_i2cmSetClockDiv(pDrv->base, 8);

	/* Clear pending master statuses */
	pDrv->base->STAT = (I2C_STAT_MSTRARBLOSS | I2C_STAT_MSTSTSTPERR);

	/* Enable I2C master interface */
	_rom_i2cmEnable(pDrv->base);

	return pDrv;
}

uint32_t i2cm_set_clock_rate(ROM_I2CM_HANDLE_T pHandle, uint32_t inRate, uint32_t i2cRate)
{
	uint32_t scl, div;
	I2CM_DATACONTEXT_T *pDrv = (I2CM_DATACONTEXT_T *) pHandle;

	/* Determine the best I2C clock dividers to generate the target I2C master clock */
	/* The maximum SCL and SCH dividers are 7, for a maximum divider set of 14 */
	/* The I2C master divider is between 1 and 65536. */

	/* Pick a main I2C divider that allows centered SCL/SCH dividers */
	div = inRate / (i2cRate << 3);
	if (div == 0) {
		div = 1;
	}
	_rom_i2cmSetClockDiv(pDrv->base, div);

	/* Determine SCL/SCH dividers */
	scl = inRate / (div * i2cRate);
	_rom_i2cmSetDutyCycle(pDrv->base, (scl >> 1), (scl - (scl >> 1)));

	return inRate / (div * scl);
}

void i2cm_register_callback(ROM_I2CM_HANDLE_T pHandle, uint32_t cbIndex, void *pCB)
{
	I2CM_DATACONTEXT_T *pDrv = (I2CM_DATACONTEXT_T *) pHandle;

	if (cbIndex == ROM_I2CM_DATACOMPLETE_CB) {
		pDrv->pXferCompCB = (i2cMasterCompleteCB) pCB;
	}
	else if (cbIndex == ROM_I2CM_DATATRANSMITSTART_CB) {
		pDrv->pTranStartCb = (i2cMasterTransmitStartCB) pCB;
	}
	else if (cbIndex == ROM_I2CM_DATATRECEIVESTART_CB) {
		pDrv->pTranRecvCb = (i2cMasterReceiveStartCB) pCB;
	}
}

ErrorCode_t i2cm_transfer(ROM_I2CM_HANDLE_T pHandle, ROM_I2CM_XFER_T *pXfer)
{
	I2CM_DATACONTEXT_T *pDrv = (I2CM_DATACONTEXT_T *) pHandle;

	/* Is transfer NULL? */
	if (pXfer == NULL) {
		return ERR_I2C_PARAM;
	}

	/* I2C master controller should be pending and idle */
	if ((pDrv->base->STAT & I2C_STAT_MSTPENDING) == 0) {
		pXfer->status = ERR_I2C_GENERAL_FAILURE;
		return ERR_I2C_GENERAL_FAILURE;
	}
	if (_rom_i2cmGetMasterState(pDrv->base) != I2C_STAT_MSTCODE_IDLE) {
		pXfer->status = ERR_I2C_GENERAL_FAILURE;
		return ERR_I2C_GENERAL_FAILURE;
	}

	/* Save transfer descriptor */
	pDrv->pXfer = pXfer;
	pXfer->status = ERR_I2C_BUSY;
	pDrv->sendIdx = 0;
	pDrv->recvIdx = 0;

	/* Pending status for completion of trasnfer */
	pDrv->pendingStatus = ERR_I2C_GENERAL_FAILURE;

	/* Clear controller state */
	pDrv->base->STAT = (I2C_STAT_MSTRARBLOSS | I2C_STAT_MSTSTSTPERR);

	/* Will always transisiton to idle at start or end of transfer */
	if (pXfer->txSz) {
		/* Call transmit start callback to setup TX DMA if needed */
		if (pDrv->pTranStartCb) {
			pDrv->pTranStartCb(pHandle, pXfer);
		}

		/* Start transmit state */
		pDrv->base->MSTDAT = (uint32_t) (pXfer->slaveAddr << 1);
		pDrv->base->MSTCTL = I2C_MSTCTL_MSTSTART;
	}
	else if (pXfer->rxSz) {
		/* Start receive state with start ot repeat start */
		pDrv->base->MSTDAT = (uint32_t) (pXfer->slaveAddr << 1) | 0x1;
		pDrv->base->MSTCTL = I2C_MSTCTL_MSTSTART;

		/* Call receive start callback to setup RX DMA if needed */
		if (pDrv->pTranRecvCb) {
			pDrv->pTranRecvCb(pHandle, pXfer);
		}
	}
	else {
		/* No data - either via data callbacks or a slave query only */
		pDrv->base->MSTDAT = (uint32_t) (pXfer->slaveAddr << 1);
		pDrv->base->MSTCTL = I2C_MSTCTL_MSTSTART;
	}

	/* Enable supported master interrupts */
	pDrv->base->INTENSET = (I2C_INTENSET_MSTPENDING | I2C_INTENSET_MSTRARBLOSS |
							I2C_INTENSET_MSTSTSTPERR);

	/* Does the driver need to block? */
	if ((pXfer->flags & ROM_I2CM_FLAG_BLOCKING) != 0) {
		while (pXfer->status == ERR_I2C_BUSY) {
			i2cm_transfer_handler(pHandle);
		}
	}

	return pXfer->status;
}

// Otime = "optimize for speed of code execution"
// ...add this pragma 1 line above the interrupt service routine function.
void i2cm_transfer_handler(ROM_I2CM_HANDLE_T pHandle)
{
	I2CM_DATACONTEXT_T *pDrv = (I2CM_DATACONTEXT_T *) pHandle;
	ROM_I2CM_XFER_T *pXfer = pDrv->pXfer;

	uint32_t status = pDrv->base->STAT;

	if (status & I2C_STAT_MSTRARBLOSS) {
		/* Master Lost Arbitration */
		/* Set transfer status as Arbitration Lost */
		pDrv->pendingStatus = ERR_I2C_LOSS_OF_ARBRITRATION;

		/* Clear Status Flags */
		pDrv->base->STAT = I2C_STAT_MSTRARBLOSS;

		pDrv->base->INTENCLR = (I2C_INTENSET_MSTPENDING | I2C_INTENSET_MSTRARBLOSS |
								I2C_INTENSET_MSTSTSTPERR);
		pXfer->status = pDrv->pendingStatus;
		if (pDrv->pXferCompCB != NULL) {
			pDrv->pXferCompCB(pHandle, pXfer);
		}
	}
	else if (status & I2C_STAT_MSTSTSTPERR) {
		/* Master Start Stop Error */
		/* Set transfer status as Bus Error */
		pDrv->pendingStatus = ERR_I2C_GENERAL_FAILURE;

		/* Clear Status Flags */
		pDrv->base->STAT = I2C_STAT_MSTSTSTPERR;

		pDrv->base->INTENCLR = (I2C_INTENSET_MSTPENDING | I2C_INTENSET_MSTRARBLOSS |
								I2C_INTENSET_MSTSTSTPERR);
		pXfer->status = pDrv->pendingStatus;
		if (pDrv->pXferCompCB != NULL) {
			pDrv->pXferCompCB(pHandle, pXfer);
		}
	}
	else if (status & I2C_STAT_MSTPENDING) {
		/* Master is Pending */
		/* Branch based on Master State Code */
		switch (_rom_i2cmGetMasterState(pDrv->base)) {
		case I2C_STAT_MSTCODE_IDLE:	/* Master idle */
			/* Idle state is only called on completion of transfer */
			/* Disable interrupts */
			pDrv->base->INTENCLR = (I2C_INTENSET_MSTPENDING | I2C_INTENSET_MSTRARBLOSS |
									I2C_INTENSET_MSTSTSTPERR);

			/* Update status and call transfer completion callback */
			pXfer->status = pDrv->pendingStatus;
			if (pDrv->pXferCompCB != NULL) {
				pDrv->pXferCompCB(pHandle, pXfer);
			}
			break;

		case I2C_STAT_MSTCODE_RXREADY:	/* Receive data is available */
			if (((pXfer->flags & ROM_I2CM_FLAG_DMARX) != 0) && (pXfer->rxSz > 0)) {
				/* Use DMA for receive */
				pDrv->base->MSTCTL = I2C_MSTCTL_MSTDMA;
				pXfer->flags &= ~ROM_I2CM_FLAG_DMARX;
				pXfer->rxSz = 0;
				return;
			}
			else if (pXfer->rxSz) {
				uint8_t *p8 = pXfer->rxBuff;
				p8[pDrv->recvIdx] = (uint8_t) pDrv->base->MSTDAT & 0xFF;
				pDrv->recvIdx++;
				pXfer->rxSz--;
			}

			if (pXfer->rxSz) {
				pDrv->base->MSTCTL = I2C_MSTCTL_MSTCONTINUE;
			}
			else {
				/* Last byte to receive, send stop after byte received */
				pDrv->base->MSTCTL = I2C_MSTCTL_MSTCONTINUE | I2C_MSTCTL_MSTSTOP;
				pDrv->pendingStatus = LPC_OK;
			}
			break;

		case I2C_STAT_MSTCODE_TXREADY:	/* Master Transmit available */
			if (((pXfer->flags & ROM_I2CM_FLAG_DMATX) != 0) && (pXfer->txSz > 0)) {
				/* Use DMA for transmit */
				pDrv->base->MSTCTL = I2C_MSTCTL_MSTDMA;
				pXfer->flags &= ~ROM_I2CM_FLAG_DMATX;
				pXfer->txSz = 0;
				return;
			}
			else if (pXfer->txSz) {
				uint8_t *p8 = (uint8_t *) pXfer->txBuff;
				/* If Tx data available transmit data and continue */
				pDrv->base->MSTDAT = (uint32_t) p8[pDrv->sendIdx];
				pDrv->base->MSTCTL = I2C_MSTCTL_MSTCONTINUE;
				pDrv->sendIdx++;
				pXfer->txSz--;
			}
			else if (pXfer->rxSz == 0) {
				pDrv->base->MSTCTL = I2C_MSTCTL_MSTSTOP;
				pDrv->pendingStatus = LPC_OK;
			}
			else {
				/* Start receive state with repeat start */
				pDrv->base->MSTDAT = (uint32_t) (pXfer->slaveAddr << 1) | 0x1;
				pDrv->base->MSTCTL = I2C_MSTCTL_MSTSTART;

				/* Call receive start callback to setup RX DMA if needed */
				if (pDrv->pTranRecvCb) {
					pDrv->pTranRecvCb(pHandle, pXfer);
				}
			}
			break;

		case I2C_STAT_MSTCODE_NACKADR:	/* Slave address was NACK'ed */
			/* Set transfer status as NACK on address */
			pDrv->pendingStatus = ERR_I2C_SLAVE_NOT_ADDRESSED;
			pDrv->base->MSTCTL = I2C_MSTCTL_MSTSTOP;
			break;

		case I2C_STAT_MSTCODE_NACKDAT:	/* Slave data was NACK'ed */
			/* Set transfer status as NACK on data */
			pDrv->pendingStatus = ERR_I2C_NAK;
			pDrv->base->MSTCTL = I2C_MSTCTL_MSTSTOP;
			break;

		default:
			/* Illegal I2C master state machine case. This should never happen.
			   Disable and re-enable controller to clear state machine */
			pDrv->pendingStatus = ERR_I2C_GENERAL_FAILURE;
			break;
		}
	}
}

uint32_t i2cm_get_driver_version(void)
{
	return DRVVERSION;
}

// *********************************************************
