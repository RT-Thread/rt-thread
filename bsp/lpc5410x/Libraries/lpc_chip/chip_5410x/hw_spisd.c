/*
 * @brief SPI slave ROM API declarations and functions
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
#include "hw_spisd.h"

#define DRVVERSION 0x0100

/* Private callback for FIFO push and pop functions. This privately maps
   to the VFIFO for the SPI slave, but can be overriden if needed. The driver will
   automatically pick the right implementation at run-time based on the transfer
   size in the transfer descriptor. */
typedef uint16_t (*spisSlaveFifoPushFN)(LPC_SPI_T *pSPI, void *data, uint32_t sendBytes, uint32_t curIndex);
typedef uint16_t (*spisSlaveFifoPopFN)(LPC_SPI_T *pSPI, void *data, uint32_t bytes, uint32_t curIndex);

/* Private data structure used for the SPI slave driver, holds the driver and
   peripheral context */
typedef struct {
	void                        *pUserData;			/*!< Pointer to user data used by driver instance, use NULL if not used */
	LPC_SPI_T                   *base;				/*!< Base address of SPI peripheral to use */
	spisSlaveXferCSAssertCB     pAssertCb;			/*!< SSEL assertion callback */
	spisSlaveTransmitCB         pTranCb;			/*!< Transmit data start callback */
	spisSlaveReceiveCB          pRecvCb;			/*!< Receive data start callback */
	spisSlaveXferCSDeAssertCB   pDeassertCb;		/*!< SSEL deassertion callback */
	spisSlaveFifoPushFN         pPushFN;			/*!< Pointer to current FIFO push function */
	spisSlaveFifoPopFN          pPopFN;				/*!< Pointer to current FIFO pop function */
	ROM_SPIS_XFER_T             *pXfer;				/*!< Pointer to current transfer descriptor */
	uint32_t                    sendIdx;			/*!< Current transmit buffer index */
	uint32_t                    recvIdx;			/*!< Current receive buffer index */
	ErrorCode_t                 pendingStatus;		/*!< Pending transfer status */
} SPIS_DATACONTEXT_T;

/* Maps config registers bits for SPI mode to the transfer descriptor */
static const uint32_t spiModeBits[4] = {
	(SPI_CFG_CPOL_LO | SPI_CFG_CPHA_FIRST),
	(SPI_CFG_CPOL_LO | SPI_CFG_CPHA_SECOND),
	(SPI_CFG_CPOL_HI | SPI_CFG_CPHA_FIRST),
	(SPI_CFG_CPOL_HI | SPI_CFG_CPHA_SECOND)
};

/* FIFO push function using standard SPI FIFO for datum >8 bits */
static uint16_t _rom_spisSlaveFifoPush16(LPC_SPI_T *pSPI, void *data, uint32_t numData, uint32_t curIndex)
{
	uint16_t pushed = 0, *p16 = (uint16_t *) data;

	/* Push as 16-bit value */
	while ((numData > 0) && ((pSPI->STAT & SPI_STAT_TXRDY) != 0)) {
		pSPI->TXDAT = (uint32_t) p16[curIndex];
		numData--;
		curIndex++;
		pushed++;
	}

	return pushed;
}

/* FIFO pop function using standard SPI FIFO for datum >8 bits */
static uint16_t _rom_spisSlaveFifoPop16(LPC_SPI_T *pSPI, void *data, uint32_t numData, uint32_t curIndex)
{
	uint16_t popped = 0, *p16 = (uint16_t *) data;

	/* Pop as 16-bit value */
	while ((numData > 0) && ((pSPI->STAT & SPI_STAT_RXRDY) != 0)) {
		p16[curIndex] = (uint16_t) pSPI->RXDAT;
		numData--;
		curIndex++;
		popped++;
	}

	return popped;
}

/* FIFO push function using standard SPI FIFO for datum <=8 bits */
static uint16_t _rom_spisSlaveFifoPush8(LPC_SPI_T *pSPI, void *data, uint32_t numData, uint32_t curIndex)
{
	uint16_t pushed = 0;
	uint8_t *p8 = (uint8_t *) data;

	/* Push as 8-bit value */
	while ((numData > 0) && ((pSPI->STAT & SPI_STAT_TXRDY) != 0)) {
		pSPI->TXDAT = (uint32_t) p8[curIndex];
		numData--;
		curIndex++;
		pushed++;
	}

	return pushed;
}

/* FIFO pop function using standard SPI FIFO for datum <=8 bits */
static uint16_t _rom_spisSlaveFifoPop8(LPC_SPI_T *pSPI, void *data, uint32_t numData, uint32_t curIndex)
{
	uint16_t popped = 0;
	uint8_t *p8 = (uint8_t *) data;

	/* Pop as 16-bit value */
	while ((numData > 0) && ((pSPI->STAT & SPI_STAT_RXRDY) != 0)) {
		p8[curIndex] = (uint8_t) pSPI->RXDAT;
		numData--;
		curIndex++;
		popped++;
	}

	return popped;
}

static void _rom_spisTransmitHandler(ROM_SPIS_HANDLE_T pHandle, ROM_SPIS_XFER_T *pXfer)
{
	SPIS_DATACONTEXT_T *pDrv = (SPIS_DATACONTEXT_T *) pHandle;

	/* This shouldn't be called if there is no transfer descriptor */
	if (!pXfer) {
		pDrv->base->INTENCLR = SPI_INTENSET_TXDYEN;
		return;
	}

	/* Is DMA being used? */
	if ((pXfer->flags & ROM_SPIS_FLAG_DMATX) != 0) {
		/* Call transmit callback, callback is pre-validated by setup */
		if (pDrv->pTranCb) {
			pDrv->pTranCb(pHandle, pXfer);
		}

		pDrv->base->INTENCLR = SPI_INTENSET_TXDYEN;
	}
	else {	/* Transfer without using DMA */
		if ((pXfer->flags & ROM_SPIS_FLAG_TXIGNORE) != 0) {
			/* ROM_SPIS_FLAG_TXIGNORE flag is set. Will send 0xFF */
			static const uint16_t sb = 0xFFFF;
			pDrv->sendIdx += pDrv->pPushFN(pDrv->base, (void *) &sb, 1, 0);
		}
		else {
			uint32_t bs;

			/* Normal data transfer */
			if (pDrv->sendIdx >= pXfer->txSz) {
				/* Ran out of data, get more data */
				if (pDrv->pTranCb) {
					pDrv->pTranCb(pHandle, pXfer);
					pDrv->sendIdx = 0;
				}
			}

			if (pDrv->sendIdx < pXfer->txSz) {
				bs = pDrv->pPushFN(pDrv->base, (void *) pXfer->txBuff, 1, pDrv->sendIdx);
				pDrv->sendIdx += bs;
				pXfer->txSent += bs;
			}
			else {
				/* Out of transmit data and no more is provided via the callback,
				   so disable the transmit interrupt and let the hardware underflow
				   and send 0. It will only underflow if the master requests data
				   beyond what is in the transmit FIFO now. The underflow error code
				   needs to be handled as part of the hardware since this may not be
				   an underflow condition is the master stops on this datum. */
				pDrv->base->INTENCLR = SPI_INTENSET_TXDYEN;
			}
		}
	}
}

static void _rom_spisReceiveHandler(ROM_SPIS_HANDLE_T pHandle, ROM_SPIS_XFER_T *pXfer)
{
	SPIS_DATACONTEXT_T *pDrv = (SPIS_DATACONTEXT_T *) pHandle;

	/* This shouldn't be called if there is no transfer descriptor */
	if (!pXfer) {
		pDrv->base->INTENCLR = SPI_INTENSET_RXDYEN;
		return;
	}

	/* Is DMA being used? */
	if ((pXfer->flags & ROM_SPIS_FLAG_DMARX) != 0) {
		/* Call receive callback, callback is pre-validated by setup */
		if (pDrv->pRecvCb) {
			pDrv->pRecvCb(pHandle, pXfer);
		}

		pDrv->base->INTENCLR = SPI_INTENSET_RXDYEN;
	}
	else {	/* Transfer without using DMA */
		if ((pXfer->flags & ROM_SPIS_FLAG_RXIGNORE) != 0) {
			/* ROM_SPIS_FLAG_RXIGNORE flag is set. Toss data */
			uint16_t temp;
			pDrv->recvIdx += pDrv->pPopFN(pDrv->base, (void *) &temp, 1, 0);
		}
		else {
			uint32_t br;

			/* Normal data transfer */
			if (pDrv->recvIdx >= pXfer->rxSz) {
				uint16_t temp;
				/* Ran out of data, overflowing */
				pDrv->pendingStatus = ERR_SPI_RXOVERRUN;
				br = pDrv->pPopFN(pDrv->base, (void *) &temp, 1, 0);/* Flush data */
			}
			else {
				br = pDrv->pPopFN(pDrv->base, (void *) pXfer->rxBuff, 1, pDrv->recvIdx);
				pXfer->rxRecv += br;
				pDrv->recvIdx += br;

				/* Call callback for more data */
				if ((pDrv->recvIdx >= pXfer->rxSz) && (pDrv->pRecvCb)) {
					pDrv->pRecvCb(pHandle, pXfer);
					pDrv->recvIdx = 0;
				}
			}
		}
	}
}

/* Determine SSEL associated with the current data value */
static uint8_t Chip_SPIS_FindSSEL(LPC_SPI_T *pSPI, uint32_t data)
{
	int i;

	/* Return first active SSEL starting at SSEL0 */
	for (i = 0; i <= 3; i++) {
		if ((data & SPI_RXDAT_RXSSELNUM_INACTIVE(i)) == 0) {
			/* Signal is active on low */
			return (uint8_t) i;
		}
	}

	return 0;
}

// **********************************************************
uint32_t spis_get_mem_size(void)
{
	return sizeof(SPIS_DATACONTEXT_T);
}

ROM_SPIS_HANDLE_T spis_init(void *mem, const ROM_SPIS_INIT_T *pInit)
{
	SPIS_DATACONTEXT_T *pDrv;
	int i;

	/* Verify alignment is at least 4 bytes */
	if (((uint32_t) mem & 0x3) != 0) {
		return NULL;
	}

	pDrv = (SPIS_DATACONTEXT_T *) mem;
	memset(pDrv, 0, sizeof(SPIS_DATACONTEXT_T));

	/* Save base of peripheral and pointer to user data */
	pDrv->pUserData = pInit->pUserData;
	pDrv->base = (LPC_SPI_T *) pInit->base;

	/* Enable SPI slave interface */
	pDrv->base->CFG = 0;
	pDrv->base->CFG = SPI_CFG_SPI_EN;

	/* Set SPI slave select (SSEL) polarity for each slave signal */
	for (i = 0; i <= 3; i++) {
		if (pInit->spiPol[i] == 0) {
			/* Active low select, high during idle */
			pDrv->base->CFG &= ~(1 << (8 + i));
		}
		else {
			/* Active high, low during idle */
			pDrv->base->CFG |= (1 << (8 + i));
		}
	}

	/* Enable SPI slave interface, deassert all chip selects (not needed for slave) */
	pDrv->base->TXCTRL = SPI_TXDATCTL_DEASSERT_ALL;

	/* Clear pending slave statuses - RXOV, TXUR, SSA, SSD, EOT */
	pDrv->base->STAT = (SPI_STAT_RXOV | SPI_STAT_TXUR | SPI_STAT_SSA |
						SPI_STAT_SSD | SPI_STAT_EOT);

	return (ROM_SPIS_HANDLE_T) pDrv;
}

void spis_register_callback(ROM_SPIS_HANDLE_T pHandle, uint32_t cbIndex, void *pCB)
{
	SPIS_DATACONTEXT_T *pDrv = (SPIS_DATACONTEXT_T *) pHandle;

	switch (cbIndex) {
	case ROM_SPIS_ASSERTSSEL_CB:
		pDrv->pAssertCb = (spisSlaveXferCSAssertCB) pCB;
		break;

	case ROM_SPIS_DATATRANSMIT_CB:
		pDrv->pTranCb = (spisSlaveTransmitCB) pCB;
		break;

	case ROM_SPIS_DATATRECEIVE_CB:
		pDrv->pRecvCb = (spisSlaveReceiveCB) pCB;
		break;

	case ROM_SPIS_DEASSERTSSEL_CB:
		pDrv->pDeassertCb = (spisSlaveXferCSDeAssertCB) pCB;
		break;
	}
}

ErrorCode_t spis_setup_slave(ROM_SPIS_HANDLE_T pHandle, ROM_SPIS_SLAVE_T *pCfg)
{
	SPIS_DATACONTEXT_T *pDrv = (SPIS_DATACONTEXT_T *) pHandle;
	uint32_t reg;

	/* Verify config is valid */
	if (pCfg == NULL) {
		return ERR_SPI_PARAM;
	}

	/* Verify data parameters area valid */
	if ((pCfg->dataBits == 0) || (pCfg->dataBits > 16)) {
		return ERR_SPI_PARAM;
	}

	/* Verify mode */
	if (pCfg->mode > ROM_SPI_CLOCK_MODE3) {
		return ERR_SPI_PARAM;
	}

	/* Setup transfer mode and LSB/MSB first */
	reg = pDrv->base->CFG;
	reg &= ~(SPI_CFG_LSB_FIRST_EN | SPI_CFG_CPHA_SECOND |
			 SPI_CFG_CPOL_HI);

	/* Setup SPI transfer configuration (CFG register) */
	reg |= spiModeBits[(int) pCfg->mode];
	if (pCfg->lsbFirst) {
		reg |= SPI_CFG_LSB_FIRST_EN;
	}
	pDrv->base->CFG = reg;

	/* Setup SPI transfer configuration (TXCTRL) for data size, don't alter SPI SSEL states */
	reg = pDrv->base->TXCTRL & ~SPI_TXCTL_FLEN(16);
	pDrv->base->TXCTRL = reg | SPI_TXCTL_FLEN(pCfg->dataBits);

	/* Setup FIFO callbacks based on the data transfer width */
	if (pCfg->dataBits > 8) {
		pDrv->pPushFN = &_rom_spisSlaveFifoPush16;
		pDrv->pPopFN = &_rom_spisSlaveFifoPop16;
	}
	else {
		pDrv->pPushFN = &_rom_spisSlaveFifoPush8;
		pDrv->pPopFN = &_rom_spisSlaveFifoPop8;
	}

	/* Enable SPI interrupts for slave */
	pDrv->base->INTENSET = SPI_INTENSET_SSAEN | SPI_INTENSET_SSDEN |
						   SPI_INTENSET_RXOVEN | SPI_INTENSET_TXUREN;

	return LPC_OK;
}

void spis_transfer_handler(ROM_SPIS_HANDLE_T pHandle)
{
	SPIS_DATACONTEXT_T *pDrv = (SPIS_DATACONTEXT_T *) pHandle;
	ROM_SPIS_XFER_T *pXfer = pDrv->pXfer;

	/* Master asserts slave */
	if ((pDrv->base->INTSTAT & SPI_INTSTAT_SSA) != 0) {
		pDrv->base->STAT = SPI_STAT_SSA;

		/* Slave SSEL assertion callback */
		if (pDrv->pAssertCb != NULL) {
			/* If if takes too long to handle this event, there may also be
			   recevied data with the asserted SSEL status. The best way to prevent
			   this is to have the master provide a SSEL setup delay between the
			   start of the SSEL assertion and the transfer of the first datum, or
			   disable the assertion callback and ignore this event. */
			/* Note that setting up transfer buffers based on the slave address is
			   the assertion callback may result in a transmit underflow. */
			uint32_t data = pDrv->base->RXDAT;
			pDrv->pAssertCb(pHandle, Chip_SPIS_FindSSEL(pDrv->base, data));

			/* Update transfer descriptor */
			pXfer = pDrv->pXfer;
		}

		/* Disable assertion interrupt, enable deassertion interrupt */
		pDrv->base->INTENCLR = SPI_INTENSET_SSAEN;
		pDrv->base->INTENSET = SPI_INTENSET_SSDEN | SPI_INTENSET_RXDYEN | SPI_INTENSET_TXDYEN;
	}

	/* If overrun or underrun errors occured, latch the error */
	if ((pDrv->base->INTSTAT & SPI_INTSTAT_TXUR) != 0) {
		pDrv->pendingStatus = ERR_SPI_TXUNDERRUN;
		pDrv->base->STAT = SPI_STAT_TXUR;
	}

	/* Receive overflow takes precedence over TX */
	if ((pDrv->base->INTSTAT & SPI_INTSTAT_RXOV) != 0) {
		pDrv->pendingStatus = ERR_SPI_RXOVERRUN;
		pDrv->base->STAT = SPI_STAT_RXOV;
	}

	if ((pDrv->base->INTSTAT & SPI_INTSTAT_TXRDY) != 0) {
		/* Handle transmit */
		_rom_spisTransmitHandler(pHandle, pXfer);
	}

	/* Receive data handler */
	if ((pDrv->base->INTSTAT & SPI_INTSTAT_RXRDY) != 0) {
		/* Handle receive */
		_rom_spisReceiveHandler(pHandle, pXfer);
	}

	/* Slave SSEL de-assertion callback */
	if ((pDrv->base->INTSTAT & SPI_INTSTAT_SSD) != 0) {
		pDrv->base->STAT = SPI_STAT_SSD | SPI_STAT_RXOV | SPI_STAT_TXUR;
		pDrv->base->INTENSET = SPI_INTENSET_SSAEN;
		pDrv->base->INTENCLR = SPI_INTENSET_SSDEN | SPI_INTENSET_RXDYEN | SPI_INTENSET_TXDYEN;

		if (pXfer) {
			pXfer->status = pDrv->pendingStatus;
			pDrv->pXfer = NULL;
		}

		/* On de-assertion, flush any data left in the transmmit and receive FIFO.
		   This is needed when streaming data and the size of the transfer isn't
		   known, so data may be left to transmit when the master deasserts. */
		pDrv->base->CFG &= ~SPI_CFG_SPI_EN;
		pDrv->base->CFG |= SPI_CFG_SPI_EN;

		/* De-assetion event */
		if (pDrv->pDeassertCb != NULL) {
			pDrv->pDeassertCb(pHandle, pXfer);
		}
	}
}

ErrorCode_t spis_transfer(ROM_SPIS_HANDLE_T pHandle, ROM_SPIS_XFER_T *pXfer)
{
	SPIS_DATACONTEXT_T *pDrv = (SPIS_DATACONTEXT_T *) pHandle;
	uint8_t flen;

	/* Get length of a receive value */
	flen = 1 + (uint8_t) ((pDrv->base->TXCTRL >> 24) & 0xF);

	/* Is transfer descriptor valid? */
	if (pXfer == NULL) {
		return ERR_SPI_PARAM;
	}

	/* No need to check RX buffer alignment if ROM_SPIS_FLAG_RXIGNORE flag is set */
	if ((pXfer->flags & ROM_SPIS_FLAG_RXIGNORE) == 0) {
		if ((pXfer->rxSz == 0) || (pXfer->rxBuff == NULL)) {
			pXfer->status = ERR_SPI_PARAM;
			return ERR_SPI_PARAM;
		}
		if ((flen > 8) && ((((uint32_t) pXfer->rxBuff) & 0x1) != 0)) {
			/* Receive buffer not 16-bit aligned or not present */
			pXfer->status = ERR_SPI_PARAM;
			return ERR_SPI_PARAM;
		}
		/* Is DMA being used? */
		if ((pXfer->flags & ROM_SPIS_FLAG_DMARX) != 0) {
			if (pDrv->pRecvCb == NULL) {
				pXfer->status = ERR_SPI_PARAM;
				return ERR_SPI_PARAM;
			}
		}
	}

	/* Check transmit buffer alignment */
	if ((pXfer->flags & ROM_SPIS_FLAG_TXIGNORE) == 0) {
		if ((pXfer->txSz == 0) || (pXfer->txBuff == NULL)) {
			pXfer->status = ERR_SPI_PARAM;
			return ERR_SPI_PARAM;
		}
		if ((flen > 8) && ((((uint32_t) pXfer->txBuff) & 0x1) != 0)) {
			pXfer->status = ERR_SPI_PARAM;
			return ERR_SPI_PARAM;
		}
		/* Is DMA being used? */
		if ((pXfer->flags & ROM_SPIS_FLAG_DMATX) != 0) {
			if (pDrv->pTranCb == NULL) {
				pXfer->status = ERR_SPI_PARAM;
				return ERR_SPI_PARAM;
			}
		}
	}

	/* ROM_SPIS_FLAG_RXIGNORE flag */
	if ((pXfer->flags & ROM_SPIS_FLAG_RXIGNORE) != 0) {
		pDrv->base->TXCTRL |= SPI_TXCTL_RXIGNORE;
	}
	else {
		pDrv->base->TXCTRL &= ~SPI_TXCTL_RXIGNORE;
	}

	/* Save pointer to transfer descriptor and initial status */
	pDrv->pXfer = pXfer;
	pXfer->status = ERR_SPI_BUSY;
	pDrv->pendingStatus = LPC_OK;
	pDrv->sendIdx = pDrv->recvIdx = pXfer->txSent = pXfer->rxRecv = 0;

	pDrv->base->INTENSET = SPI_INTENSET_RXDYEN | SPI_INTENSET_TXDYEN;

	return pXfer->status;
}

uint32_t spis_get_driver_version(void)
{
	return DRVVERSION;
}

// *********************************************************
