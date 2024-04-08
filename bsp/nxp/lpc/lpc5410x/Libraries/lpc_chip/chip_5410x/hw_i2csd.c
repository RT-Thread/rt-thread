/*
 * @brief I2C slave ROM API declarations and functions
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
#include "hw_i2csd.h"

#define DRVVERSION 0x0100

/* Private data structure used for the I2C slave driver, holds the driver and
   peripheral context */
typedef struct {
	void                    *pUserData;		/*!< Pointer to user data used by driver instance, use NULL if not used */
	LPC_I2C_T               *base;			/*!< Base address of I2C peripheral to use */
	i2cSlaveStartCB         pXferStartCB;	/*!< Transfer start callback */
	i2cSlaveTransmitCB      pTranTranCb;	/*!< Data transmit callback */
	i2cSlaveReceiveCB       pTranRecvCb;	/*!< Data Receive callback */
	i2cSlaveCompleteCB      pXferCompCB;	/*!< Transfer complete callback */
	ROM_I2CS_XFER_T         *pXfer;			/*!< Pointer to current transfer */
	ErrorCode_t             pendingStatus;	/*!< Pending transfer status */
} I2CS_DATACONTEXT_T;

#define _rom_i2csEnable(pI2C)                   (pI2C->CFG |= I2C_CFG_SLVEN);
#define _rom_i2csGetSlaveAddr(pI2C, slvNum)     ((pI2C->SLVADR[slvNum] >> 1) & 0x7F)
#define _rom_i2csGetSlaveMatchIndex(pI2C)       ((pI2C->STAT & I2C_STAT_SLVIDX) >> 12)
#define _rom_i2csGetSlaveState(pI2C)            (((pI2C->STAT & I2C_STAT_SLVSTATE) >> 9) & 0x3)

// **********************************************************
uint32_t i2cs_get_mem_size(void)
{
	return sizeof(I2CS_DATACONTEXT_T);
}

ROM_I2CS_HANDLE_T i2cs_init(void *mem, const ROM_I2CS_INIT_T *pInit)
{
	I2CS_DATACONTEXT_T *pDrv;

	/* Verify alignment is at least 4 bytes */
	if (((uint32_t) mem & 0x3) != 0) {
		return NULL;
	}

	pDrv = (I2CS_DATACONTEXT_T *) mem;
	memset(pDrv, 0, sizeof(I2CS_DATACONTEXT_T));

	/* Save base of peripheral and pointer to user data */
	pDrv->pUserData = pInit->pUserData;
	pDrv->base = (LPC_I2C_T *) pInit->base;

	/* If this needs to be changed, it should be done in the app after
	   this call. */
	pDrv->base->CLKDIV = 2;

	/* Clear controller state */
	pDrv->base->STAT = (I2C_STAT_SLVSEL | I2C_STAT_SLVDESEL);

	/* Enable I2C slave interface */
	_rom_i2csEnable(pDrv->base);

	return pDrv;
}

void i2cs_setup_slave(ROM_I2CS_HANDLE_T pHandle, ROM_I2CS_SLAVE_T *pSlaveSetup)
{
	uint32_t sa, idx;
	I2CS_DATACONTEXT_T *pDrv = (I2CS_DATACONTEXT_T *) pHandle;

	/* Limit usable slave address indexes to the maximum the controller can support */
	if (pSlaveSetup->SlaveIndex <= 3) {
		sa = (uint32_t) (pSlaveSetup->slaveAddr & 0x7F) << 1;
		if (pSlaveSetup->EnableSlave == 0) {
			sa |= I2C_SLVADR_SADISABLE;	/* Disable slave address */
		}

		/* Setup slave address at index */
		pDrv->base->SLVADR[pSlaveSetup->SlaveIndex] = sa;
	}

	/* Check all slave indexes. If any are enabled, then enable the slave interrupts,
	   else disable the slave interrupts. */
	sa = 0;
	for (idx = 0; ((idx <= 3) && (sa == 0)); idx++) {
		if ((pDrv->base->SLVADR[idx] & I2C_SLVADR_SADISABLE) == 0) {
			/* Slave is enabled */
			sa = 1;
		}
	}
	if (sa) {
		pDrv->base->INTENSET = I2C_INTENSET_SLVPENDING;

	}
	else {
		pDrv->base->INTENCLR = (I2C_INTENSET_SLVPENDING | I2C_INTENSET_SLVDESEL);
	}
}

void i2cs_register_callback(ROM_I2CS_HANDLE_T pHandle, uint32_t cbIndex, void *pCB)
{
	I2CS_DATACONTEXT_T *pDrv = (I2CS_DATACONTEXT_T *) pHandle;

	if (cbIndex == ROM_I2CS_START_CB) {
		pDrv->pXferStartCB = (i2cSlaveStartCB) pCB;
	}
	else if (cbIndex == ROM_I2CS_XFERSEND_CB) {
		pDrv->pTranTranCb = (i2cSlaveTransmitCB) pCB;
	}
	else if (cbIndex == ROM_I2CS_XFERRECV_CB) {
		pDrv->pTranRecvCb = (i2cSlaveReceiveCB) pCB;
	}
	else if (cbIndex == ROM_I2CS_DONE_CB) {
		pDrv->pXferCompCB = (i2cSlaveCompleteCB) pCB;
	}
}

ErrorCode_t i2cs_transfer(ROM_I2CS_HANDLE_T pHandle, ROM_I2CS_XFER_T *pXfer)
{
	I2CS_DATACONTEXT_T *pDrv = (I2CS_DATACONTEXT_T *) pHandle;

	/* Is transfer NULL? */
	if (pXfer == NULL) {
		return ERR_I2C_PARAM;
	}

	/* Save transfer descriptor */
	pDrv->pXfer = pXfer;
	pXfer->status = ERR_I2C_BUSY;
	pDrv->pendingStatus = LPC_OK;
	pXfer->bytesSent = 0;
	pXfer->bytesRecv = 0;

	return pXfer->status;
}

// Otime = "optimize for speed of code execution"
// ...add this pragma 1 line above the interrupt service routine function.
void i2cs_transfer_handler(ROM_I2CS_HANDLE_T pHandle)
{
	I2CS_DATACONTEXT_T *pDrv = (I2CS_DATACONTEXT_T *) pHandle;
	ROM_I2CS_XFER_T *pXfer = pDrv->pXfer;

	uint32_t done = 0;
	uint16_t data = 0;

	uint32_t status = pDrv->base->INTSTAT;

	/* Transfer complete? */
	if ((status & I2C_INTENSET_SLVDESEL) != 0) {
		pDrv->base->INTENCLR = I2C_INTENSET_SLVDESEL;
		pDrv->base->STAT = I2C_STAT_SLVDESEL;
		if (pXfer) {
			pXfer->status = pDrv->pendingStatus;
			pDrv->pXfer = NULL;
		}
		if (pDrv->pXferCompCB) {
			pDrv->pXferCompCB(pHandle, pXfer);
		}
		return;
	}
	else if ((status & I2C_INTENSET_SLVPENDING) != 0) {
		/* Determine the current I2C slave state */
		switch (_rom_i2csGetSlaveState(pDrv->base)) {
		case I2C_STAT_SLVCODE_ADDR:
			/* Get slave address that needs servicing */
			data = _rom_i2csGetSlaveAddr(pDrv->base, _rom_i2csGetSlaveMatchIndex(pDrv->base));

			/* Call address callback */
			if (pDrv->pXferStartCB) {
				pDrv->pXferStartCB(pHandle, data);

				/* Update transfer descriptor */
				pXfer = pDrv->pXfer;
			}
			pDrv->base->INTENSET = I2C_INTENSET_SLVDESEL;
			break;

		case I2C_STAT_SLVCODE_RX:
			/* Receive from master */
			/* A byte has been received in thee receive FIFO */
			if ((pXfer == NULL) || (pXfer->bytesRecv >= pXfer->rxSz)) {
				/* No more data, call receive data callback */
				if (pDrv->pTranRecvCb) {
					done = pDrv->pTranRecvCb(pHandle, pXfer);
					if (pDrv->pXfer) {
						pXfer = pDrv->pXfer;
						pXfer->bytesRecv = 0;
					}
				}
			}

			/* Not using DMA */
			if (!(done == ROM_I2CS_DMA)) {
				data = (uint8_t) pDrv->base->SLVDAT;
				if (pXfer == NULL) {
					/* Toss data and NAK, no buffer space */
					done = ROM_I2CS_NAK;
					pDrv->pendingStatus = ERR_I2C_BUFFER_OVERFLOW;
				}
				else {
					uint8_t *p8 = pXfer->rxBuff;
					if ((p8 == NULL) || (pXfer->bytesRecv >= pXfer->rxSz)) {
						/* Toss data and NAK, no buffer space */
						done = ROM_I2CS_NAK;
						pDrv->pendingStatus = ERR_I2C_BUFFER_OVERFLOW;
					}
					else {
						p8[pXfer->bytesRecv] = (uint8_t) data;
						pDrv->pXfer->bytesRecv++;
					}
				}
			}
			break;

		case I2C_STAT_SLVCODE_TX:
			/* Send to master */
			/* A byte needs to be placed into the transmit FIFO */
			if ((pXfer == NULL) || (pXfer->bytesSent >= pXfer->txSz)) {
				/* Does callback exist? */
				if (pDrv->pTranTranCb) {
					done = pDrv->pTranTranCb(pHandle, pXfer);
					/* Can't really NAK on read, so switch to continue */
					if (pDrv->pXfer) {
						pXfer = pDrv->pXfer;
						pXfer->bytesSent = 0;
					}
					if (done == ROM_I2CS_NAK) {
						pDrv->base->SLVDAT = 0;
					}
				}
			}

			/* Continue if not DMA or NAK */
			if (!((done == ROM_I2CS_NAK) || (done == ROM_I2CS_DMA))) {
				if (pXfer == NULL) {
					pDrv->base->SLVDAT = 0;
					pDrv->pendingStatus = ERR_I2C_BUFFER_UNDERFLOW;
					done = 0;
				}
				else {
					uint8_t *p8 = (uint8_t *) pXfer->txBuff;
					/* Not using DMA, so this is a normal transfer */
					if ((p8 == NULL) || (pXfer->bytesSent >= pXfer->txSz)) {
						/* Have to send something, so NAK with 0 */
						pDrv->base->SLVDAT = 0;
						pDrv->pendingStatus = ERR_I2C_BUFFER_UNDERFLOW;
						done = 0;
					}
					else {
						pDrv->base->SLVDAT = (uint32_t) p8[pXfer->bytesSent];
						pDrv->pXfer->bytesSent++;
					}
				}
			}
			break;
		}

		if (done == ROM_I2CS_NAK) {
			pDrv->base->SLVCTL = I2C_SLVCTL_SLVNACK;
		}
		else if (done == ROM_I2CS_DMA) {
			pDrv->base->SLVCTL = I2C_SLVCTL_SLVDMA;
		}
		else {
			pDrv->base->SLVCTL = I2C_SLVCTL_SLVCONTINUE;
		}
	}
}

uint32_t i2cs_get_driver_version(void)
{
	return DRVVERSION;
}

// *********************************************************
