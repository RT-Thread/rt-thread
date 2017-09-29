/*
 * @brief LPC8xx SPI driver
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

#include "chip.h"

/*****************************************************************************
 * Private types/enumerations/variables
 ****************************************************************************/
static volatile bool xmitOn;
static volatile bool deasserted;
/*****************************************************************************
 * Public types/enumerations/variables
 ****************************************************************************/

/*****************************************************************************
 * Private functions
 ****************************************************************************/

STATIC void SPI_Send_Data_RxIgnore(LPC_SPI_T *pSPI,
								   SPI_DATA_SETUP_T *pXfSetup)
{
	if (pXfSetup->TxCnt == (pXfSetup->Length - 1)) {
		Chip_SPI_SendLastFrame_RxIgnore(pSPI, pXfSetup->pTx[pXfSetup->TxCnt], pXfSetup->DataSize);
	}
	else {
		Chip_SPI_SendMidFrame(pSPI, pXfSetup->pTx[pXfSetup->TxCnt]);
	}

	pXfSetup->TxCnt++;
}

STATIC void SPI_Send_Data(LPC_SPI_T *pSPI,
						  SPI_DATA_SETUP_T *pXfSetup)
{
	if (pXfSetup->TxCnt == (pXfSetup->Length - 1)) {
		Chip_SPI_SendLastFrame(pSPI, pXfSetup->pTx[pXfSetup->TxCnt], pXfSetup->DataSize);
	}
	else {
		Chip_SPI_SendMidFrame(pSPI, pXfSetup->pTx[pXfSetup->TxCnt]);
	}

	pXfSetup->TxCnt++;
}

STATIC void SPI_Send_Dummy(LPC_SPI_T *pSPI,
						   SPI_DATA_SETUP_T *pXfSetup)
{
	if (pXfSetup->RxCnt == (pXfSetup->Length - 1)) {
		Chip_SPI_SendLastFrame(pSPI, 0x55, pXfSetup->DataSize);
	}
	else {
		Chip_SPI_SendMidFrame(pSPI, 0x55);
	}
}

STATIC void SPI_Receive_Data(LPC_SPI_T *pSPI,
							 SPI_DATA_SETUP_T *pXfSetup)
{
	pXfSetup->pRx[pXfSetup->RxCnt] = Chip_SPI_ReceiveFrame(pSPI);
	pXfSetup->RxCnt++;
}

/* Determine SSEL associated with the current data value */
STATIC uint8_t Chip_SPIS_FindSSEL(LPC_SPI_T *pSPI, uint32_t data)
{
	int i;
	uint8_t ssel = 0;

	for (i = 0; i <= 3; i++) {
		if ((data & SPI_RXDAT_RXSSELNUM_INACTIVE(i)) == 0) {
			/* Signal is active on low */
			ssel = (uint8_t) i;
		}
	}

	return ssel;
}

/*****************************************************************************
 * Public functions
 ****************************************************************************/

/* Calculate the Clock Rate Divider for SPI Peripheral */
uint32_t Chip_SPI_CalClkRateDivider(LPC_SPI_T *pSPI, uint32_t bitRate)
{
	uint32_t SPIClk;
	uint32_t DivVal = 1;

	/* Get SPI clock rate */
	SPIClk = Chip_Clock_GetSystemClockRate();	/*The peripheral clock for both SPIs is the system clock*/

	DivVal = SPIClk / bitRate;

	return DivVal;
}

/* Configure SPI Delay parameters */
void Chip_SPI_DelayConfig(LPC_SPI_T *pSPI, SPI_DELAY_CONFIG_T *pConfig)
{
	uint32_t delayValue = SPI_DLY_PRE_DELAY(pConfig->PreDelay) |
		SPI_DLY_POST_DELAY(pConfig->PostDelay)                 |
		SPI_DLY_FRAME_DELAY(pConfig->FrameDelay);
	if (pConfig->TransferDelay) {
		delayValue |= SPI_DLY_TRANSFER_DELAY(pConfig->TransferDelay - 1);
	}
	pSPI->DLY = delayValue;
}

/* Disable/Enable Interrupt */
void Chip_SPI_Int_Cmd(LPC_SPI_T *pSPI, uint32_t IntMask, FunctionalState NewState)
{
	if (NewState ==  ENABLE) {
		pSPI->INTENSET = IntMask;
	}
	else {
		pSPI->INTENCLR = IntMask;
	}
}

/*Send and Receive SPI Data  */
uint32_t Chip_SPI_RWFrames_Blocking(LPC_SPI_T *pSPI, SPI_DATA_SETUP_T *pXfSetup)
{
	uint32_t Status;
	/* Clear status */
	Chip_SPI_ClearStatus(pSPI, SPI_STAT_CLR_RXOV | SPI_STAT_CLR_TXUR | SPI_STAT_CLR_SSA | SPI_STAT_CLR_SSD);
	Chip_SPI_SetControlInfo(pSPI, pXfSetup->DataSize, SPI_TXCTL_ASSERT_SSEL | SPI_TXCTL_EOF);
	pXfSetup->TxCnt = pXfSetup->RxCnt = 0;
	while ((pXfSetup->TxCnt < pXfSetup->Length) ||
		   (pXfSetup->RxCnt < pXfSetup->Length)) {
		Status = Chip_SPI_GetStatus(pSPI);

		/* In case of TxReady */
		if ((Status & SPI_STAT_TXRDY) && (pXfSetup->TxCnt < pXfSetup->Length)) {
			SPI_Send_Data(pSPI, pXfSetup);
		}

		/*In case of Rx ready */
		if ((Status & SPI_STAT_RXRDY) && (pXfSetup->RxCnt < pXfSetup->Length)) {
			SPI_Receive_Data(pSPI, pXfSetup);
		}
	}
	/* Check error */
	if (Chip_SPI_GetStatus(pSPI) & (SPI_STAT_CLR_RXOV | SPI_STAT_CLR_TXUR)) {
		return 0;
	}
	return pXfSetup->TxCnt;
}

uint32_t Chip_SPI_WriteFrames_Blocking(LPC_SPI_T *pSPI, SPI_DATA_SETUP_T *pXfSetup)
{
	/* Clear status */
	Chip_SPI_ClearStatus(pSPI, SPI_STAT_CLR_RXOV | SPI_STAT_CLR_TXUR | SPI_STAT_CLR_SSA | SPI_STAT_CLR_SSD);
	Chip_SPI_SetControlInfo(pSPI, pXfSetup->DataSize, SPI_TXCTL_ASSERT_SSEL | SPI_TXCTL_EOF | SPI_TXCTL_RXIGNORE);
	pXfSetup->TxCnt = pXfSetup->RxCnt = 0;
	while (pXfSetup->TxCnt < pXfSetup->Length) {
		/* Wait for TxReady */
		while (!(Chip_SPI_GetStatus(pSPI) & SPI_STAT_TXRDY)) {}

		SPI_Send_Data_RxIgnore(pSPI, pXfSetup);

	}

	/* Make sure the last frame sent completely*/
	while (!(Chip_SPI_GetStatus(pSPI) & SPI_STAT_SSD)) {}
	Chip_SPI_ClearStatus(pSPI, SPI_STAT_CLR_SSD);

	/* Check overrun error */
	if (Chip_SPI_GetStatus(pSPI) & SPI_STAT_CLR_TXUR) {
		return 0;
	}
	return pXfSetup->TxCnt;
}

uint32_t Chip_SPI_ReadFrames_Blocking(LPC_SPI_T *pSPI, SPI_DATA_SETUP_T *pXfSetup)
{
	/* Clear status */
	Chip_SPI_ClearStatus(pSPI, SPI_STAT_CLR_RXOV | SPI_STAT_CLR_TXUR | SPI_STAT_CLR_SSA | SPI_STAT_CLR_SSD);
	Chip_SPI_SetControlInfo(pSPI, pXfSetup->DataSize, SPI_TXCTL_ASSERT_SSEL | SPI_TXCTL_EOF);
	pXfSetup->TxCnt = pXfSetup->RxCnt = 0;
	while (pXfSetup->RxCnt < pXfSetup->Length) {
		/* Wait for TxReady */
		while (!(Chip_SPI_GetStatus(pSPI) & SPI_STAT_TXRDY)) {}

		SPI_Send_Dummy(pSPI, pXfSetup);

		/* Wait for receive data */
		while (!(Chip_SPI_GetStatus(pSPI) & SPI_STAT_RXRDY)) {}

		SPI_Receive_Data(pSPI, pXfSetup);

	}
	/* Check overrun error */
	if (Chip_SPI_GetStatus(pSPI) & (SPI_STAT_CLR_RXOV | SPI_STAT_CLR_TXUR)) {
		return 0;
	}
	return pXfSetup->RxCnt;
}

/* SPI Interrupt Read/Write with 8-bit frame width */
Status Chip_SPI_Int_RWFrames(LPC_SPI_T *pSPI, SPI_DATA_SETUP_T *pXfSetup)
{
	uint32_t Status;

	Status = Chip_SPI_GetStatus(pSPI);
	/* Check  error in INTSTAT register */
	if (Status & (SPI_STAT_RXOV | SPI_STAT_TXUR)) {
		return ERROR;
	}

	if (pXfSetup->TxCnt == 0) {
		Chip_SPI_SetControlInfo(pSPI, pXfSetup->DataSize, SPI_TXCTL_ASSERT_SSEL | SPI_TXCTL_EOF);
	}

	if (pXfSetup->pRx == NULL) {
		if ((Status & SPI_STAT_TXRDY) && (pXfSetup->TxCnt < pXfSetup->Length)) {
			SPI_Send_Data_RxIgnore(pSPI, pXfSetup);
		}
	}
	else {
		/* check if Tx ready */
		if ((Status & SPI_STAT_TXRDY) && (pXfSetup->TxCnt < pXfSetup->Length)) {
			SPI_Send_Data(pSPI, pXfSetup);
		}

		/* check if RX FIFO contains data */
		if ((Status & SPI_STAT_RXRDY) && (pXfSetup->RxCnt < pXfSetup->Length)) {
			SPI_Receive_Data(pSPI, pXfSetup);
		}
	}

	return SUCCESS;
}

/* Get SPI master bit rate */
uint32_t Chip_SPIM_GetClockRate(LPC_SPI_T *pSPI)
{
	return Chip_Clock_GetSystemClockRate() / ((pSPI->DIV & ~SPI_DIV_RESERVED) + 1);
}

/* Set SPI master bit rate */
uint32_t Chip_SPIM_SetClockRate(LPC_SPI_T *pSPI, uint32_t rate)
{
	uint32_t baseClock, div;

	/* Get peripheral base clock rate */
	baseClock = Chip_Clock_GetSystemClockRate();

	/* Compute divider */
	div = baseClock / rate;

	/* Limit values */
	if (div == 0) {
		div = 1;
	}
	else if (div > 0x10000) {
		div = 0x10000;
	}
	pSPI->DIV = div - 1;

	return Chip_SPIM_GetClockRate(pSPI);
}

/* Configure SPI Delay parameters */
void Chip_SPIM_DelayConfig(LPC_SPI_T *pSPI, SPIM_DELAY_CONFIG_T *pConfig)
{
	pSPI->DLY = (SPI_DLY_PRE_DELAY(pConfig->PreDelay) |
				 SPI_DLY_POST_DELAY(pConfig->PostDelay) |
				 SPI_DLY_FRAME_DELAY(pConfig->FrameDelay) |
				 SPI_DLY_TRANSFER_DELAY(pConfig->TransferDelay - 1));
}

/* Assert a SPI select */
void Chip_SPIM_AssertSSEL(LPC_SPI_T *pSPI, uint8_t sselNum)
{
	uint32_t reg;

	reg = pSPI->TXCTRL & SPI_TXDATCTL_CTRLMASK;

	/* Assert a SSEL line by driving it low */
	reg &= ~SPI_TXDATCTL_DEASSERTNUM_SSEL(sselNum);

	pSPI->TXCTRL = reg;
}

/* Deassert a SPI select */
void Chip_SPIM_DeAssertSSEL(LPC_SPI_T *pSPI, uint8_t sselNum)
{
	uint32_t reg;

	reg = pSPI->TXCTRL & SPI_TXDATCTL_CTRLMASK;
	pSPI->TXCTRL = reg | SPI_TXDATCTL_DEASSERTNUM_SSEL(sselNum);
}

/* SPI master transfer state change handler */
void Chip_SPIM_XferHandler(LPC_SPI_T *pSPI, SPIM_XFER_T *xfer)
{
	uint32_t data;
	uint8_t flen;

	/* Get length of a receive value */
	flen = ((pSPI->TXCTRL & ~SPI_TXCTRL_RESERVED) >> 24) & 0xF;

	/* Master asserts slave */
	if ((Chip_SPI_GetStatus(pSPI) & SPI_STAT_SSA) != 0) {
		Chip_SPI_ClearStatus(pSPI, SPI_STAT_SSA);

		/* SSEL assertion callback */
		xfer->pCB->masterXferCSAssert(xfer);
	}

	/* Slave de-assertion */
	if ((Chip_SPI_GetStatus(pSPI) & SPI_STAT_SSD) != 0) {
		Chip_SPI_ClearStatus(pSPI, SPI_STAT_SSD);

		/* If transmitter disabled and deassert happens, the transfer is done */
		if (xmitOn == false) {
			xfer->pCB->mMasterXferDone(xfer);
		}
	}

	/* Transmit data? */
	while (((Chip_SPI_GetStatus(pSPI) & SPI_STAT_TXRDY) != 0) && (xmitOn == true)) {
		if ((xfer->txCount == 1) && (xfer->terminate)) {
			/* Transfer is done, this will be last data */
			Chip_SPIM_ForceEndOfTransfer(pSPI);
			xmitOn = false;
		}
		else if (xfer->txCount == 0) {
			/* Request a new buffer first */
			xfer->pCB->masterXferSend(xfer);
		}

		if (xfer->txCount > 0) {
			/* Send 0 if ignoring transmit */
			if (xfer->pTXData8 == NULL) {
				data = 0;
			}
			else {
				/* Copy buffer to data */
				if (flen > 8) {
					data = (uint32_t) *xfer->pTXData16;
					xfer->pTXData16++;
				}
				else {
					data = (uint32_t) *xfer->pTXData8;
					xfer->pTXData8++;
				}

				xfer->dataTXferred++;
			}

			Chip_SPI_WriteTXData(pSPI, data);
			xfer->txCount--;
		}
	}

	/* Data received? */
	while ((Chip_SPI_GetStatus(pSPI) & SPI_STAT_RXRDY) != 0) {
		/* Get raw data and status */
		data = Chip_SPI_ReadRawRXFifo(pSPI);

		/* Only copy data when not ignoring receive */
		if (xfer->pRXData8 != NULL) {
			/* Enough size in current buffers? */
			if (xfer->rxCount == 0) {
				/* Request a new buffer first */
				xfer->pCB->masterXferRecv(xfer);
			}

			/* Copy data to buffer */
			if (xfer->rxCount > 0) {
				if (flen > 8) {
					*xfer->pRXData16 = (uint16_t) (data & 0xFFFF);
					xfer->pRXData16++;
				}
				else {
					*xfer->pRXData8 = (uint8_t) (data & 0xFF);
					xfer->pRXData8++;
				}

				xfer->dataRXferred++;
				xfer->rxCount--;
			}
		}
	}
}

/* Start non-blocking SPI master transfer */
void Chip_SPIM_Xfer(LPC_SPI_T *pSPI, SPIM_XFER_T *xfer)
{
	/* Setup SPI master select, data length, EOT/EOF timing, and RX data ignore */
	pSPI->TXCTRL = xfer->options | SPI_TXDATCTL_DEASSERT_ALL;
	Chip_SPIM_AssertSSEL(pSPI, xfer->sselNum);

	/* Clear initial transfer states */
	xfer->dataRXferred = xfer->dataTXferred = 0;

	/* Call main handler to start transfer */
	xmitOn = true;
	Chip_SPIM_XferHandler(pSPI, xfer);
}

/* Perform blocking SPI master transfer */
void Chip_SPIM_XferBlocking(LPC_SPI_T *pSPI, SPIM_XFER_T *xfer)
{
	/* Start trasnfer */
	Chip_SPIM_Xfer(pSPI, xfer);

	/* Wait for termination */
	while (xmitOn == true) {
		Chip_SPIM_XferHandler(pSPI, xfer);
	}
}

/* SPI slave transfer state change handler */
uint32_t Chip_SPIS_XferHandler(LPC_SPI_T *pSPI, SPIS_XFER_T *xfer)
{
	uint32_t staterr, data;
	uint8_t flen;

	/* Get length of a receive value */
	flen = ((pSPI->TXCTRL & ~SPI_TXCTRL_RESERVED) >> 24) & 0xF;

	/* Get errors for later, we'll continue even if errors occur, but we notify
	   caller on return */
	staterr = Chip_SPI_GetStatus(pSPI) & (SPI_STAT_RXOV | SPI_STAT_TXUR);
	if (staterr != 0) {
		Chip_SPI_ClearStatus(pSPI, staterr);
	}

	/* Slave assertion */
	if ((Chip_SPI_GetStatus(pSPI) & SPI_STAT_SSA) != 0) {
		Chip_SPI_ClearStatus(pSPI, SPI_STAT_SSA);

		/* Determine SPI select. Read the data FIFO to get the slave number. Data
		   should not be in the receive FIFO yet, only the statuses */
		xfer->sselNum = Chip_SPIS_FindSSEL(pSPI, Chip_SPI_ReadRawRXFifo(pSPI));

		/* SSEL assertion callback */
		xfer->pCB->slaveXferCSAssert(xfer);
	}

	/* Slave de-assertion */
	if ((Chip_SPI_GetStatus(pSPI) & SPI_STAT_SSD) != 0) {
		Chip_SPI_ClearStatus(pSPI, SPI_STAT_SSD);
		deasserted = true;
		xfer->pCB->slaveXferCSDeAssert(xfer);
	}

	/* Transmit data? */
	while ((Chip_SPI_GetStatus(pSPI) & SPI_STAT_TXRDY) != 0) {
		if (xfer->txCount == 0) {
			/* Request a new buffer first */
			xfer->pCB->slaveXferSend(xfer);
		}

		/* Send 0 on empty buffer or count */
		if ((xfer->txCount == 0) || (xfer->pTXData8 == NULL)) {
			data = 0;
		}
		else {
			/* Copy buffer to data */
			if (flen > 8) {
				data = (uint32_t) *xfer->pTXData16;
				xfer->pTXData16++;
			}
			else {
				data = (uint32_t) *xfer->pTXData8;
				xfer->pTXData8++;
			}

			xfer->dataTXferred++;
			xfer->txCount--;
		}

		Chip_SPI_WriteTXData(pSPI, data);
	}

	/* Data received? */
	while ((Chip_SPI_GetStatus(pSPI) & SPI_STAT_RXRDY) != 0) {
		/* Get raw data and status */
		data = Chip_SPI_ReadRawRXFifo(pSPI);

		/* Only copy data when not ignoring receive */
		if (xfer->pRXData8 != NULL) {
			/* Enough size in current buffers? */
			if (xfer->rxCount == 0) {
				/* Request a new buffer first */
				xfer->pCB->slaveXferRecv(xfer);
			}

			/* Copy data to buffer */
			if (flen > 8) {
				*xfer->pRXData16 = (uint16_t) (data & 0xFFFF);
				xfer->pRXData16++;
			}
			else {
				*xfer->pRXData8 = (uint8_t) (data & 0xFF);
				xfer->pRXData8++;
			}

			xfer->dataRXferred++;
			xfer->rxCount--;
		}
	}

	return staterr;
}

/* SPI slave transfer blocking function */
uint32_t Chip_SPIS_XferBlocking(LPC_SPI_T *pSPI, SPIS_XFER_T *xfer)
{
	uint32_t status = 0;

	/* Wait forever until deassertion event */
	deasserted = false;
	while ((!deasserted) && (status == 0)) {
		status = Chip_SPIS_XferHandler(pSPI, xfer);
	}

	return status;
}
