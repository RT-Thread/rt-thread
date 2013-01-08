/*
 * @brief I2S Registers and control functions
 *
 * @note
 * Copyright(C) NXP Semiconductors, 2012
 * All rights reserved.
 *
 * @par
 * Software that is described herein is for illustrative purposes only
 * which provides customers with programming information regarding the
 * LPC products. This software is supplied "AS IS" without any warranties of
 * any kind, and NXP Semiconductors and its licensor disclaim any and
 * all warranties, express or implied, including all implied warranties of
 * merchantability, fitness for a particular purpose and non-infringement of
 * intellectual property rights. NXP Semiconductors assumes no responsibility
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
 * is used in conjunction with NXP Semiconductors microcontrollers. This
 * copyright, permission, and disclaimer notice must appear in all copies of
 * this code.
 */

#include "i2s_001.h"

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

/* Initialize for I2S */
void IP_I2S_Init(IP_I2S_001_Type *pI2S)
{}

/* Shutdown I2S */
void IP_I2S_DeInit(IP_I2S_001_Type *pI2S)
{
	pI2S->DAI = 0x07E1;
	pI2S->DAO = 0x87E1;
	pI2S->IRQ = 0;
	pI2S->TXMODE = 0;
	pI2S->RXMODE = 0;
	pI2S->DMA1 = 0;
	pI2S->DMA2 = 0;
}

/* I2S configuration functions --------*/

/* Selects the number of bytes in data */
void IP_I2S_SetWordWidth(IP_I2S_001_Type *pI2S, uint8_t TRMode, uint32_t wordwidth)
{
	if (TRMode == I2S_TX_MODE) {
		pI2S->DAO &= ~I2S_DAO_WORDWIDTH_MASK;
		pI2S->DAO |= wordwidth;
	}
	else {
		pI2S->DAI &= ~I2S_DAI_WORDWIDTH_MASK;
		pI2S->DAI |= wordwidth;
	}
}

/* Set I2S data format is monaural or stereo */
void IP_I2S_SetMono(IP_I2S_001_Type *pI2S, uint8_t TRMode, uint32_t mono)
{
	if (TRMode == I2S_TX_MODE) {
		pI2S->DAO &= ~I2S_DAO_MONO;
		pI2S->DAO |= mono;
	}
	else {
		pI2S->DAI &= ~I2S_DAI_MONO;
		pI2S->DAI |= mono;
	}
}

/* Set I2S interface in master/slave mode */
void IP_I2S_SetMasterSlaveMode(IP_I2S_001_Type *pI2S, uint8_t TRMode, uint32_t mode)
{
	if (TRMode == I2S_TX_MODE) {
		pI2S->DAO &= ~I2S_DAO_SLAVE;
		pI2S->DAO |= mode;
	}
	else {
		pI2S->DAI &= ~I2S_DAI_SLAVE;
		pI2S->DAI |= mode;
	}
}

/* Set the clock frequency for I2S interface */
void IP_I2S_SetBitRate(IP_I2S_001_Type *pI2S, uint8_t TRMode, uint32_t mclk_divider)
{
	if (TRMode == I2S_TX_MODE) {
		pI2S->TXBITRATE = mclk_divider;
	}
	else {
		pI2S->RXBITRATE = mclk_divider;
	}
}

/* Set the MCLK rate by using a fractional rate generator, dividing down the frequency of PCLK */
void IP_I2S_SetXYDivider(IP_I2S_001_Type *pI2S, uint8_t TRMode, uint8_t x_divider, uint8_t y_divider)
{
	if (TRMode == I2S_TX_MODE) {
		pI2S->TXRATE = y_divider | (x_divider << 8);
	}
	else {
		pI2S->RXRATE = y_divider | (x_divider << 8);
	}
}

/* Set word select (WS) half period */
void IP_I2S_SetWS_Halfperiod(IP_I2S_001_Type *pI2S, uint8_t TRMode, uint32_t ws_halfperiod)
{
	if (TRMode == I2S_TX_MODE) {
		pI2S->DAO &= ~I2S_DAO_WS_HALFPERIOD_MASK;
		pI2S->DAO |= I2S_DAO_WS_HALFPERIOD(ws_halfperiod);
	}
	else {
		pI2S->DAI &= ~I2S_DAI_WS_HALFPERIOD_MASK;
		pI2S->DAI |= I2S_DAI_WS_HALFPERIOD(ws_halfperiod);
	}
}

/* Set the I2S operating modes */
void IP_I2S_ModeConfig(IP_I2S_001_Type *pI2S, uint8_t TRMode, uint32_t clksel, uint32_t fpin, uint32_t mcena)
{
	if (TRMode == I2S_TX_MODE) {
		pI2S->TXMODE = clksel | fpin | mcena;
	}
	else {
		pI2S->RXMODE = clksel | fpin | mcena;
	}
}

/* Get the current level of the Transmit/Receive FIFO */
uint8_t IP_I2S_GetLevel(IP_I2S_001_Type *pI2S, uint8_t TRMode)
{
	if (TRMode == I2S_TX_MODE) {
		return (pI2S->STATE >> 16) & 0xF;
	}
	else {
		return (pI2S->STATE >> 8) & 0xF;
	}
}

/* I2S operate functions -------------*/

/* Send a 32-bit data to TXFIFO for transmition */
void IP_I2S_Send(IP_I2S_001_Type *pI2S, uint32_t data)
{
	pI2S->TXFIFO = data;
}

/* Get received data from RXFIFO */
uint32_t IP_I2S_Receive(IP_I2S_001_Type *pI2S)
{
	return pI2S->RXFIFO;
}

/* Start the  I2S */
void IP_I2S_Start(IP_I2S_001_Type *pI2S, uint8_t TRMode)
{
	if (TRMode == I2S_TX_MODE) {
		pI2S->DAO &= ~(I2S_DAO_RESET | I2S_DAO_STOP | I2S_DAO_MUTE);
	}
	else {
		pI2S->DAI &= ~(I2S_DAI_RESET | I2S_DAI_STOP);
	}
}

/* Disables accesses on FIFOs, places the transmit channel in mute mode */
void IP_I2S_Pause(IP_I2S_001_Type *pI2S, uint8_t TRMode)
{
	if (TRMode == I2S_TX_MODE) {
		pI2S->DAO |= I2S_DAO_STOP;
	}
	else {
		pI2S->DAI |= I2S_DAI_STOP;
	}
}

/* Transmit channel sends only zeroes */
void IP_I2S_Mute(IP_I2S_001_Type *pI2S, FunctionalState NewState)
{
	if (NewState == ENABLE) {
		pI2S->DAO |= I2S_DAO_MUTE;
	}
	else {
		pI2S->DAO &= ~I2S_DAO_MUTE;
	}
}

/* Pause, resets the transmit channel and FIFO asynchronously */
void IP_I2S_Stop(IP_I2S_001_Type *pI2S, uint8_t TRMode)
{
	if (TRMode == I2S_TX_MODE) {
		pI2S->DAO &= ~I2S_DAO_MUTE;
		pI2S->DAO |= I2S_DAO_STOP | I2S_DAO_RESET;
	}
	else {
		pI2S->DAI |= I2S_DAI_STOP | I2S_DAI_RESET;
	}
}

/* I2S DMA functions ----------------*/

/* Set the FIFO level on which to create an DMA request */
void IP_I2S_DMACmd(IP_I2S_001_Type *pI2S, IP_I2S_DMARequestNumber_Type DMANum, uint8_t TRMode, FunctionalState NewState)
{
	if (TRMode == I2S_RX_MODE) {
		if (DMANum == IP_I2S_DMA_REQUEST_NUMBER_1) {
			if (NewState == ENABLE) {
				pI2S->DMA1 |= 0x01;
			}
			else {
				pI2S->DMA1 &= ~0x01;
			}
		}
		else {
			if (NewState == ENABLE) {
				pI2S->DMA2 |= 0x01;
			}
			else {
				pI2S->DMA2 &= ~0x01;
			}
		}
	}
	else {
		if (DMANum == IP_I2S_DMA_REQUEST_NUMBER_1) {
			if (NewState == ENABLE) {
				pI2S->DMA1 |= 0x02;
			}
			else {
				pI2S->DMA1 &= ~0x02;
			}
		}
		else {
			if (NewState == ENABLE) {
				pI2S->DMA2 |= 0x02;
			}
			else {
				pI2S->DMA2 &= ~0x02;
			}
		}
	}
}

/* Enable/Disable DMA for the I2S */
void IP_I2S_SetFIFODepthDMA(IP_I2S_001_Type *pI2S, uint8_t TRMode, IP_I2S_DMARequestNumber_Type DMANum, uint32_t depth)
{
	if (TRMode == I2S_RX_MODE) {
		if (DMANum == IP_I2S_DMA_REQUEST_NUMBER_1) {
			pI2S->DMA1 &= ~(0x0F << 8);
			pI2S->DMA1 |= depth << 8;
		}
		else {
			pI2S->DMA2 &= ~(0x0F << 8);
			pI2S->DMA2 |= depth << 8;
		}
	}
	else {
		if (DMANum == IP_I2S_DMA_REQUEST_NUMBER_1) {
			pI2S->DMA1 &= ~(0x0F << 16);
			pI2S->DMA1 |= depth << 16;
		}
		else {
			pI2S->DMA2 &= ~(0x0F << 16);
			pI2S->DMA2 |= depth << 16;
		}
	}
}

/* I2S IRQ functions ----------------*/

/* Enable/Disable interrupt for the I2S */
void IP_I2S_InterruptCmd(IP_I2S_001_Type *pI2S, uint8_t TRMode, FunctionalState NewState)
{
	if (NewState == ENABLE) {
		pI2S->IRQ |= (TRMode == I2S_RX_MODE) ? 0x01 : 0x02;
	}
	else {
		pI2S->IRQ &= (TRMode == I2S_RX_MODE) ? (~0x01) : (~0x02);
	}
}

/* Set the FIFO level on which to create an irq request */
void IP_I2S_SetFIFODepthIRQ(IP_I2S_001_Type *pI2S, uint8_t TRMode, uint32_t depth)
{
	depth &= 0x0F;
	if (TRMode == I2S_RX_MODE) {
		pI2S->IRQ &= ~I2S_IRQ_RX_DEPTH_MASK;
		pI2S->IRQ |= I2S_IRQ_RX_DEPTH(depth);
	}
	else {
		pI2S->IRQ &= ~I2S_IRQ_TX_DEPTH_MASK;
		pI2S->IRQ |= I2S_IRQ_TX_DEPTH(depth);
	}
}

/* Get the status of I2S interrupt */
Status IP_I2S_GetIntStatus(IP_I2S_001_Type *pI2S, uint8_t TRMode)
{
	if (TRMode == I2S_TX_MODE) {
		return (Status) (((pI2S->IRQ >> 1) & 0x01) & ((pI2S->STATE) & 0x01));
	}
	else {
		return (Status) (((pI2S->IRQ) & 0x01) & ((pI2S->STATE) & 0x01));
	}
}
