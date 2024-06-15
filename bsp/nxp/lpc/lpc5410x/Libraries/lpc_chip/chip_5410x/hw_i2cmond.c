/*
 * @brief I2C monitor ROM API declarations and functions
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
#include "hw_i2cmond.h"

#define DRVVERSION 0x0100

/* Private data structure used for the I2C monitor driver, holds the driver and
   peripheral context */
typedef struct {
	void                        *pUserData;		/*!< Pointer to user data used by driver instance, use NULL if not used */
	LPC_I2C_T                   *base;			/*!< Base address of I2C peripheral to use */
	i2cMonCapReadyCB            pCapCompCB;		/*!< Capture complete callback */
	i2cMonSetupDMACB            pDmaSetupCB;	/*!< DMA setup callback */
	ROM_I2CMON_CAP_T            *pCap;			/*!< Pointer to current capture descriptor */
	ErrorCode_t                 pendingStatus;	/*!< Pending monitor transfer status before clocking transfer */
} I2CMON_DATACONTEXT_T;

void i2cmon_transfer_handler(ROM_I2CMON_HANDLE_T pHandle)
;

// **********************************************************
uint32_t i2cmon_get_mem_size(void)
{
	return sizeof(I2CMON_DATACONTEXT_T);
}

ROM_I2CMON_HANDLE_T i2cmon_init(void *mem, const ROM_I2CMON_INIT_T *pInit)
{
	I2CMON_DATACONTEXT_T *pDrv;
	uint32_t reg;

	/* Verify alignment is at least 4 bytes */
	if (((uint32_t) mem & 0x3) != 0) {
		return NULL;
	}

	pDrv = (I2CMON_DATACONTEXT_T *) mem;
	memset(pDrv, 0, sizeof(I2CMON_DATACONTEXT_T));

	/* Save base of peripheral and pointer to user data */
	pDrv->pUserData = pInit->pUserData;
	pDrv->base = (LPC_I2C_T *) pInit->base;

	/* Clear pending monitor statuses */
	pDrv->base->STAT = (I2C_STAT_MONIDLE | I2C_STAT_MONOV);
	while ((pDrv->base->STAT & I2C_STAT_MONRDY) != 0) {
		/* Toss input data */
		reg = pDrv->base->MONRXDAT;
	}

	/* Enable I2C monitor interface */
	reg = pDrv->base->CFG | I2C_CFG_MONEN;
	if (pInit->stretch != 0) {
		reg |= I2C_CFG_MONCLKSTR;
	}
	pDrv->base->CFG = reg;

	return pDrv;
}

void i2cmom_register_callback(ROM_I2CMON_HANDLE_T pHandle, uint32_t cbIndex, void *pCB)
{
	I2CMON_DATACONTEXT_T *pDrv = (I2CMON_DATACONTEXT_T *) pHandle;

	if (cbIndex == ROM_I2CMON_CAPTUREREADY_CB) {
		pDrv->pCapCompCB = (i2cMonCapReadyCB) pCB;
	}
	else if (cbIndex == ROM_I2CMON_DMASETUP_CB) {
		pDrv->pDmaSetupCB = (i2cMonSetupDMACB) pCB;
	}
}

ErrorCode_t i2cmom_start_log(ROM_I2CMON_HANDLE_T pHandle, ROM_I2CMON_CAP_T *pCap)
{
	I2CMON_DATACONTEXT_T *pDrv = (I2CMON_DATACONTEXT_T *) pHandle;

	/* I2C master controller should be pending and idle */
	if (pCap == NULL) {
		return ERR_I2C_PARAM;
	}

	/* Verify receive buffer alignment */
	if ((pCap->startBuff == NULL) || ((((uint32_t) pCap->startBuff) & 0x1) != 0) || (pCap->startBuffSz == 0)) {
		pCap->status = ERR_I2C_PARAM;
		return ERR_I2C_PARAM;
	}

	pDrv->pCap = pCap;
	pCap->capStartBuffSz = 0;
	pDrv->pendingStatus = LPC_OK;
	pCap->status = ERR_I2C_BUSY;

	if ((pCap->flags & ROM_I2CMON_FLAG_FLUSH) != 0) {
		while ((pDrv->base->STAT & I2C_STAT_MONRDY) != 0) {
			/* Toss input data */
			volatile uint32_t reg = pDrv->base->MONRXDAT;
		}
	}

	/* Clear controller state */
	pDrv->base->STAT = (I2C_STAT_MONIDLE | I2C_STAT_MONOV);

	if (((pCap->flags & ROM_I2CMON_FLAG_DMARX) != 0) && (pDrv->pDmaSetupCB)) {
		pDrv->pDmaSetupCB(pHandle, pCap);

		/* Enable supported monitor interrupts */
		pDrv->base->INTENSET = (I2C_INTENSET_MONOV | I2C_INTENSET_MONIDLE);
	}
	else {
		pCap->flags &= ~ROM_I2CMON_FLAG_DMARX;

		/* Enable supported monitor interrupts */
		pDrv->base->INTENSET = (I2C_INTENSET_MONRDY | I2C_INTENSET_MONOV | I2C_INTENSET_MONIDLE);
	}

	/* Is transfer blocking? */
	if ((pCap->flags & ROM_I2CMON_FLAG_BLOCKING) != 0) {
		while (pCap->status == ERR_I2C_BUSY) {
			i2cmon_transfer_handler(pHandle);
		}
	}

	return pCap->status;
}

// Otime = "optimize for speed of code execution"
// ...add this pragma 1 line above the interrupt service routine function.
void i2cmon_transfer_handler(ROM_I2CMON_HANDLE_T pHandle)
{
	I2CMON_DATACONTEXT_T *pDrv = (I2CMON_DATACONTEXT_T *) pHandle;
	ROM_I2CMON_CAP_T *pCap = pDrv->pCap;
	uint16_t data = 0, *pData;

	uint32_t status = pDrv->base->STAT;

	if (status & I2C_STAT_MONOV) {
		/* Monitor data overflow */
		data = pDrv->base->MONRXDAT;
		pDrv->pendingStatus = ERR_I2C_BUFFER_OVERFLOW;

		/* Clear Status Flags */
		pDrv->base->STAT = I2C_STAT_MONOV;
	}
	else if (status & I2C_STAT_MONRDY) {
		/* Monitor ready */
		data = pDrv->base->MONRXDAT;

		/* Enough room to place this data? */
		if (pCap->capStartBuffSz >= pCap->startBuffSz) {
			/* Data overflow */
			pDrv->pendingStatus = ERR_I2C_BUFFER_OVERFLOW;
		}
		else {
			pData = (uint16_t *) pCap->startBuff;

			pData[pCap->capStartBuffSz] = data;
			pCap->capStartBuffSz++;
		}
	}

	/* Capture complete? */
	if ((status & I2C_INTSTAT_MONIDLE) != 0) {
		pDrv->base->INTENCLR = (I2C_INTENCLR_MONRDY | I2C_INTENCLR_MONOV |
								I2C_INTENCLR_MONIDLE);
		pCap->status = pDrv->pendingStatus;
		if (pDrv->pCapCompCB) {
			pDrv->pCapCompCB(pHandle, pCap);
		}
	}
}

uint32_t i2cmon_get_driver_version(void)
{
	return DRVVERSION;
}

// *********************************************************
