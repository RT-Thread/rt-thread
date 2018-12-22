/*
 * @brief SPI master ROM API declarations and functions
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
#include "hw_spimd.h"

#define DRVVERSION 0x0100

/* Private callback for FIFO push and pop functions. This privately maps
   to the VFIFO for the SPI master, but can be overriden if needed. The driver will
   automatically pick the right implementation at run-time based on the transfer
   size in the transfer descriptor. */
typedef uint16_t (*spiMasterFifoPushFN)(LPC_SPI_T *pSPI, void *data, uint32_t sendBytes, uint32_t curIndex);
typedef uint16_t (*spiMasterFifoPopFN)(LPC_SPI_T *pSPI, void *data, uint32_t bytes, uint32_t curIndex);

/* Private data structure used for the SPI master driver, holds the driver and
   peripheral context */
typedef struct {
	void                        *pUserData;			/*!< Pointer to user data used by driver instance, use NULL if not used */
	LPC_SPI_T                   *base;				/*!< Base address of SPI peripheral to use */
	uint32_t                    baseClockRate;		/*!< SPI base clock rate in Hz, call Init() again if this rate changes */
	spiMasterXferCSAssertCB     pAssertCb;			/*!< SSEL assertion callback */
	spiMasterTransmitCB         pTranCb;			/*!< Transmit data start callback */
	spiMasterReceiveCB          pRecvCb;			/*!< Receive data start callback */
	spiMMasterXferCSDeAssertCB  pDeassertCb;		/*!< SSEL deassertion callback */
	spiMasterFifoPushFN         pPushFN;			/*!< Pointer to current FIFO push function */
	spiMasterFifoPopFN          pPopFN;				/*!< Pointer to current FIFO pop function */
	ROM_SPIM_XFER_T             *pXfer;				/*!< Pointer to current transfer descriptor */
	uint32_t                    sendIdx;			/*!< Current transmit buffer index */
	uint32_t                    recvIdx;			/*!< Current receive buffer index */
	ErrorCode_t                 pendingStatus;		/*!< Pending transfer status */
	uint8_t                     xmitOn;				/*!< Transfer in progress flag */
	uint8_t                     terminate;			/*!< Terminate transfer flag */
	uint8_t                     reserved[2];
} SPIM_DATACONTEXT_T;

/* Maps config registers bits for SPI mode to the transfer descriptor */
static const uint32_t spiModeBits[4] = {
	(SPI_CFG_CPOL_LO | SPI_CFG_CPHA_FIRST),
	(SPI_CFG_CPOL_LO | SPI_CFG_CPHA_SECOND),
	(SPI_CFG_CPOL_HI | SPI_CFG_CPHA_FIRST),
	(SPI_CFG_CPOL_HI | SPI_CFG_CPHA_SECOND)
};

void spim_close_pending_transfer(ROM_SPIM_HANDLE_T pHandle);

/* FIFO push function using standard SPI FIFO for datum >8 bits */
static uint16_t _rom_spimMasterFifoPush16(LPC_SPI_T *pSPI, void *data, uint32_t numData, uint32_t curIndex)
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
static uint16_t _rom_spimMasterFifoPop16(LPC_SPI_T *pSPI, void *data, uint32_t numData, uint32_t curIndex)
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
static uint16_t _rom_spimMasterFifoPush8(LPC_SPI_T *pSPI, void *data, uint32_t numData, uint32_t curIndex)
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
static uint16_t _rom_spimMasterFifoPop8(LPC_SPI_T *pSPI, void *data, uint32_t numData, uint32_t curIndex)
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

/* Assert a SPI select */
static void _rom_spimAssertSSEL(LPC_SPI_T *pSPI, uint8_t sselNum)
{
	/* Assert a SSEL line by driving it low */
	pSPI->TXCTRL &= ~SPI_TXDATCTL_DEASSERTNUM_SSEL(sselNum);
}

static void _rom_spimCloseTransfer(SPIM_DATACONTEXT_T *pDrv)
{
	/* Transfer terminates after this byte */
	pDrv->xmitOn = 0;
	pDrv->base->INTENCLR = SPI_INTENSET_TXDYEN;
}

static void _rom_spimTransmitHandler(ROM_SPIM_HANDLE_T pHandle, ROM_SPIM_XFER_T *pXfer)
{
	SPIM_DATACONTEXT_T *pDrv = (SPIM_DATACONTEXT_T *) pHandle;

	/* Is DMA being used? */
	if ((pXfer->flags & ROM_SPIM_FLAG_DMATX) != 0) {
		/* Call transmit callback, callback is pre-validated by setup */
		if (pDrv->pTranCb) {
			pDrv->pTranCb(pHandle, pXfer);

			pDrv->base->INTENCLR = SPI_INTENSET_TXDYEN;
		}
	}
	else {	/* Transfer without using DMA */
		if ((pXfer->flags & ROM_SPIM_FLAG_TXIGNORE) != 0) {
			/* ROM_SPIM_FLAG_TXIGNORE flag is set. Will send 0xFF and decrement txSz,
			   transfer terminates on last data */
			static const uint16_t sb = 0xFFFF;
			if (pDrv->sendIdx >= pXfer->txSz) {
				/* Transferring last datum, end transfer */
				spim_close_pending_transfer(pHandle);
			}
			else {
				if (pDrv->sendIdx >= (pXfer->txSz - 1)) {
					pDrv->base->TXCTRL |= SPI_TXCTL_EOT;
				}
				pDrv->sendIdx += pDrv->pPushFN(pDrv->base, (void *) &sb, 1, 0);
			}
		}
		else {
			/* Normal data transfer */
			if (pDrv->sendIdx >= pXfer->txSz) {
				/* Ran out of data, so stop */
				spim_close_pending_transfer(pHandle);
			}
			else {
				pDrv->sendIdx += pDrv->pPushFN(pDrv->base, (void *) pXfer->txBuff, 1, pDrv->sendIdx);

				/* Call callback for more data */
				if (pDrv->sendIdx >= pXfer->txSz) {
					if (pDrv->pTranCb) {
						pDrv->pTranCb(pHandle, pXfer);
						pDrv->sendIdx = 0;
					}
					else {
						/* No transmit callback, close transfer */
						spim_close_pending_transfer(pHandle);
					}
				}
			}
		}
	}
}

static void _rom_spimReceiveHandler(ROM_SPIM_HANDLE_T pHandle, ROM_SPIM_XFER_T *pXfer)
{
	SPIM_DATACONTEXT_T *pDrv = (SPIM_DATACONTEXT_T *) pHandle;

	/* Is DMA being used? */
	if ((pXfer->flags & ROM_SPIM_FLAG_DMARX) != 0) {
		/* Call receive callback, callback is pre-validated by setup */
		if (pDrv->pRecvCb) {
			pDrv->pRecvCb(pHandle, pXfer);

			pDrv->base->INTENCLR = SPI_INTENSET_RXDYEN;
		}
	}
	else {	/* Transfer without using DMA */
			/* Normal data transfer */
		if (pDrv->recvIdx >= pXfer->rxSz) {
			uint16_t temp;
			/* Ran out of data, overflowing */
			pDrv->pendingStatus = ERR_SPI_RXOVERRUN;
			pDrv->recvIdx += pDrv->pPopFN(pDrv->base, (void *) &temp, 1, 0);	/* Flush data */
		}
		else {
			pDrv->recvIdx += pDrv->pPopFN(pDrv->base, (void *) pXfer->rxBuff, 1, pDrv->recvIdx);

			/* Call callback for more data */
			if ((pDrv->recvIdx >= pXfer->rxSz) && (pDrv->pRecvCb)) {
				pDrv->pRecvCb(pHandle, pXfer);
				pDrv->recvIdx = 0;
			}
		}
	}
}

// **********************************************************
uint32_t spim_get_mem_size(void)
{
	return sizeof(SPIM_DATACONTEXT_T);
}

ROM_SPIM_HANDLE_T spim_init(void *mem, const ROM_SPIM_INIT_T *pInit)
{
	SPIM_DATACONTEXT_T *pDrv;
	int i;

	/* Verify alignment is at least 4 bytes and clock rate is not 0 */
	if ((((uint32_t) mem & 0x3) != 0) || (pInit->baseClockRate == 0)) {
		return NULL;
	}

	pDrv = (SPIM_DATACONTEXT_T *) mem;
	memset(pDrv, 0, sizeof(SPIM_DATACONTEXT_T));

	/* Save base of peripheral and pointer to user data */
	pDrv->pUserData = pInit->pUserData;
	pDrv->base = (LPC_SPI_T *) pInit->base;
	pDrv->baseClockRate = pInit->baseClockRate;

	/* Enable SPI master interface, deassert all chip selects */
	pDrv->base->CFG = 0;/* Forces state machine reset */
	pDrv->base->CFG = SPI_CFG_SPI_EN | SPI_CFG_MASTER_EN;

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

	/* Deassert all chip selects */
	pDrv->base->TXCTRL = SPI_TXDATCTL_DEASSERT_ALL;

	/* Clear pending master statuses - RXOV, TXUR, SSA, SSD, EOT */
	pDrv->base->STAT = (SPI_STAT_RXOV | SPI_STAT_TXUR | SPI_STAT_SSA |
						SPI_STAT_SSD | SPI_STAT_EOT);

	return (ROM_SPIM_HANDLE_T) pDrv;
}

void spim_register_callback(ROM_SPIM_HANDLE_T pHandle, uint32_t cbIndex, void *pCB)
{
	SPIM_DATACONTEXT_T *pDrv = (SPIM_DATACONTEXT_T *) pHandle;

	switch (cbIndex) {
	case ROM_SPIM_ASSERTSSEL_CB:
		pDrv->pAssertCb = (spiMasterXferCSAssertCB) pCB;
		break;

	case ROM_SPIM_DATATRANSMIT_CB:
		pDrv->pTranCb = (spiMasterTransmitCB) pCB;
		break;

	case ROM_SPIM_DATATRECEIVE_CB:
		pDrv->pRecvCb = (spiMasterReceiveCB) pCB;
		break;

	case ROM_SPIM_DEASSERTSSEL_CB:
		pDrv->pDeassertCb = (spiMMasterXferCSDeAssertCB) pCB;
		break;
	}
}

ErrorCode_t spim_setup_transfer(ROM_SPIM_HANDLE_T pHandle, ROM_SPIM_XFER_CONFIG_T *pCfg)
{
	SPIM_DATACONTEXT_T *pDrv = (SPIM_DATACONTEXT_T *) pHandle;
	uint32_t reg;

	/* Verify config is valid */
	if (pCfg == NULL) {
		return ERR_SPI_PARAM;
	}

	/* Verify data parameters area valid */
	if ((pCfg->dataBits == 0) || (pCfg->dataBits > 16) || (pCfg->dXferBitRate == 0)) {
		return ERR_SPI_PARAM;
	}

	/* Verify mode */
	if (pCfg->mode > ROM_SPI_CLOCK_MODE3) {
		return ERR_SPI_PARAM;
	}

	/* Transfer timing is valid? */
	if ((pCfg->PreDelay > 15) || (pCfg->PostDelay > 15) ||  (pCfg->FrameDelay > 15) ||
		(pCfg->TransferDelay > 16)) {
		return ERR_SPI_PARAM;
	}

	/* Compute real clock rate from desired clock rate */
	reg = pDrv->baseClockRate / pCfg->dXferBitRate;
	if ((pDrv->baseClockRate %  pCfg->dXferBitRate) != 0) {
		reg++;
	}
	if (reg > 0x10000) {
		reg = 0x10000;
	}
	else if (reg == 0) {
		reg = 1;
	}

	/* Save pre-computed divider and set real SPI master bit rate for app */
	pDrv->base->DIV = (reg - 1);
	pCfg->rXferBitRate = pDrv->baseClockRate / reg;

	/* Setup transfer timing */
	if (pCfg->TransferDelay == 0) {
		pCfg->TransferDelay = 1;
	}
	pDrv->base->DLY = (
		SPI_DLY_PRE_DELAY(pCfg->PreDelay) |
		SPI_DLY_POST_DELAY(pCfg->PostDelay) |
		SPI_DLY_FRAME_DELAY(pCfg->FrameDelay) |
		SPI_DLY_TRANSFER_DELAY(pCfg->TransferDelay - 1));

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
	if (pCfg->FrameDelay > 0) {
		reg |= SPI_TXCTL_EOF;
	}
	pDrv->base->TXCTRL = reg | SPI_TXCTL_FLEN(pCfg->dataBits);

	/* Setup FIFO callbacks based on the data transfer width */
	if (pCfg->dataBits > 8) {
		pDrv->pPushFN = &_rom_spimMasterFifoPush16;
		pDrv->pPopFN = &_rom_spimMasterFifoPop16;
	}
	else {
		pDrv->pPushFN = &_rom_spimMasterFifoPush8;
		pDrv->pPopFN = &_rom_spimMasterFifoPop8;
	}

	return LPC_OK;
}

ErrorCode_t spim_transfer(ROM_SPIM_HANDLE_T pHandle, ROM_SPIM_XFER_T *pXfer)
{
	SPIM_DATACONTEXT_T *pDrv = (SPIM_DATACONTEXT_T *) pHandle;
	uint32_t reg;
	uint8_t flen;

	/* Get length of a receive value */
	flen = 1 + (uint8_t) ((pDrv->base->TXCTRL >> 24) & 0xF);

	/* Is transfer descriptor valid? */
	if (pXfer == NULL) {
		return ERR_SPI_PARAM;
	}

	/* Is slave select  valid? */
	if (pXfer->sselNum >= ROM_SPIM_MAXSELECTS) {
		pXfer->status = ERR_SPI_PARAM;
		return ERR_SPI_PARAM;
	}

	/* Verify transmit size, must have at least 1 byte */
	if (pXfer->txSz == 0) {
		pXfer->status = ERR_SPI_INVALID_LENGTH;
		return ERR_SPI_INVALID_LENGTH;
	}

	/* No need to check RX buffer alignment if ROM_SPIM_FLAG_RXIGNORE flag is set */
	if ((pXfer->flags & ROM_SPIM_FLAG_RXIGNORE) == 0) {
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
		if ((pXfer->flags & ROM_SPIM_FLAG_DMARX) != 0) {
			if (pDrv->pRecvCb == NULL) {
				pXfer->status = ERR_SPI_PARAM;
				return ERR_SPI_PARAM;
			}
		}
	}

	/* Check transmit buffer alignment */
	if ((pXfer->flags & ROM_SPIM_FLAG_TXIGNORE) == 0) {
		if ((pXfer->txSz == 0) || (pXfer->txBuff == NULL)) {
			pXfer->status = ERR_SPI_PARAM;
			return ERR_SPI_PARAM;
		}
		if ((flen > 8) && ((((uint32_t) pXfer->txBuff) & 0x1) != 0)) {
			pXfer->status = ERR_SPI_PARAM;
			return ERR_SPI_PARAM;
		}
		/* Is DMA being used? */
		if ((pXfer->flags & ROM_SPIM_FLAG_DMATX) != 0) {
			if (pDrv->pTranCb == NULL) {
				pXfer->status = ERR_SPI_PARAM;
				return ERR_SPI_PARAM;
			}
		}
	}

	/* If in loopback mode, set loopback enable */
	reg = pDrv->base->CFG;
	if ((pXfer->flags & ROM_SPIM_FLAG_LOOPBACK) != 0) {
		reg |= SPI_CFG_LBM_EN;
	}
	else {
		reg &= ~SPI_CFG_LBM_EN;
	}
	pDrv->base->CFG = reg;

	/* ROM_SPIM_FLAG_RXIGNORE flag */
	reg = pDrv->base->TXCTRL & ~SPI_TXCTL_EOT;
	if ((pXfer->flags & ROM_SPIM_FLAG_RXIGNORE) != 0) {
		reg |= SPI_TXCTL_RXIGNORE;
	}
	else {
		reg &= ~SPI_TXCTL_RXIGNORE;
	}
	pDrv->base->TXCTRL = reg;

	/* Save pointer to transfer descriptor and initial status */
	pDrv->pXfer = pXfer;
	pXfer->status = ERR_SPI_BUSY;
	pDrv->pendingStatus = LPC_OK;
	pDrv->sendIdx = pDrv->recvIdx = 0;

	/* Transmit start, no terminate */
	pDrv->xmitOn = 1;
	pDrv->terminate = 0;

	/* Start transfer by asserting selected slave */
	_rom_spimAssertSSEL(pDrv->base, pXfer->sselNum);

	/* Enable SPI interrupts for master */
	pDrv->base->INTENSET = SPI_INTENSET_RXDYEN | SPI_INTENSET_TXDYEN |
						   SPI_INTENSET_SSAEN | SPI_INTENSET_SSDEN;

	/* Is transfer blocking? */
	if ((pXfer->flags & ROM_SPIM_FLAG_BLOCKING) != 0) {
		while (pXfer->status == ERR_SPI_BUSY) {
			spim_transfer_handler(pHandle);
		}
	}

	return pXfer->status;
}

// Otime = "optimize for speed of code execution"
// ...add this pragma 1 line above the interrupt service routine function.
void spim_transfer_handler(ROM_SPIM_HANDLE_T pHandle)
{
	SPIM_DATACONTEXT_T *pDrv = (SPIM_DATACONTEXT_T *) pHandle;
	ROM_SPIM_XFER_T *pXfer = pDrv->pXfer;
	uint32_t status = pDrv->base->STAT;

	/* Master asserts slave */
	if ((status & SPI_STAT_SSA) != 0) {
		pDrv->base->STAT = SPI_STAT_SSA;
		pDrv->base->INTENCLR = SPI_INTENSET_SSAEN;

		/* Master SSEL assertion callback */
		if (pDrv->pAssertCb != NULL) {
			pDrv->pAssertCb(pHandle, pXfer);
		}
	}

	/* Transmit data handler */
	if (((status & SPI_STAT_TXRDY) != 0) && (pDrv->xmitOn == 1)) {
		/* Handle transmit */
		_rom_spimTransmitHandler(pHandle, pXfer);
	}

	/* Receive data handler */
	if ((status & SPI_STAT_RXRDY) != 0) {
		/* Handle receive */
		_rom_spimReceiveHandler(pHandle, pXfer);
	}

	/* If the controller is stalled and the transmit is finished, close the transfer
	   or be stuck in a stalled condition indefinitely. */
	if (((status & SPI_STAT_STALLED) != 0) && (pDrv->xmitOn == 0)) {
		spim_close_pending_transfer(pHandle);
	}

	/* Master SSEL de-assertion callback */
	if ((status & SPI_STAT_SSD) != 0) {
		pDrv->base->STAT = SPI_STAT_SSD;
		pDrv->base->INTENCLR = SPI_INTENSET_SSAEN | SPI_INTENSET_SSDEN |
							   SPI_INTENSET_RXDYEN | SPI_INTENSET_TXDYEN;
		pXfer->status = pDrv->pendingStatus;

		/* De-assetion event */
		if (pDrv->pDeassertCb != NULL) {
			pDrv->pDeassertCb(pHandle, pXfer);
		}
	}
}

void spim_close_pending_transfer(ROM_SPIM_HANDLE_T pHandle)
{
	SPIM_DATACONTEXT_T *pDrv = (SPIM_DATACONTEXT_T *) pHandle;

	/* If stalled, force an EOT */
	if ((pDrv->base->STAT & SPI_STAT_STALLED) != 0) {
		pDrv->base->STAT = SPI_STAT_EOT;
	}
	pDrv->base->TXCTRL |= SPI_TXCTL_EOT;

	_rom_spimCloseTransfer(pDrv);
}

uint32_t spim_get_driver_version(void)
{
	return DRVVERSION;
}

// *********************************************************
