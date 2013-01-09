/*
 * @brief SSP Registers and control functions
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

#include "ssp_001.h"

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

/*Set up output clocks per bit for SSP bus*/
void IP_SSP_Set_ClockRate(IP_SSP_001_Type *pSSP, uint32_t clk_rate, uint32_t prescale)
{
	pSSP->CR0 &= ~(SSP_CR0_SCR(0xFF));
	pSSP->CR0 |= SSP_CR0_SCR(clk_rate);
	pSSP->CPSR = prescale;
}

/* Set up the SSP frame format */
void IP_SSP_Set_Format(IP_SSP_001_Type *pSSP, uint32_t bits, uint32_t frameFormat, uint32_t clockFormat)
{
	pSSP->CR0 = (pSSP->CR0 & ~0xFF) | bits | frameFormat | clockFormat;
}

/* Set the SSP working as master or slave mode */
void IP_SSP_Set_Mode(IP_SSP_001_Type *pSSP, uint32_t mode)
{
	pSSP->CR1 = (pSSP->CR1 & ~(1 << 2)) | mode;
}

/* Disable SSP operation */
void IP_SSP_DeInit(IP_SSP_001_Type *pSSP)
{
	pSSP->CR1 &= (~SSP_CR1_SSP_EN) & SSP_CR1_BITMASK;
}

/* Enable/Disable SSP operation */
void IP_SSP_Cmd(IP_SSP_001_Type *pSSP, FunctionalState NewState)
{
	if (NewState == ENABLE) {
		pSSP->CR1 |= SSP_CR1_SSP_EN;
	}
	else {
		pSSP->CR1 &= (~SSP_CR1_SSP_EN) & SSP_CR1_BITMASK;
	}
}

/* Send SSP 16-bit data */
void IP_SSP_SendFrame(IP_SSP_001_Type *pSSP, uint16_t tx_data)
{
	pSSP->DR = SSP_DR_BITMASK(tx_data);
}

/* Get received SSP data */
uint16_t IP_SSP_ReceiveFrame(IP_SSP_001_Type *pSSP)
{
	return (uint16_t) (SSP_DR_BITMASK(pSSP->DR));
}

/* Enable/Disable loopback mode */
void IP_SSP_LoopBackCmd(IP_SSP_001_Type *pSSP, FunctionalState NewState)
{

	if (NewState == ENABLE) {
		pSSP->CR1 |= SSP_CR1_LBM_EN;
	}
	else {
		pSSP->CR1 &= (~SSP_CR1_LBM_EN) & SSP_CR1_BITMASK;
	}
}

/* Get the raw interrupt status */
IntStatus IP_SSP_GetRawIntStatus(IP_SSP_001_Type *pSSP, SSP_Raw_Int_Status_Type RawInt)
{
	return (pSSP->RIS & RawInt) ? SET : RESET;
}

/* Get the masked interrupt status */
uint32_t IP_SSP_GetIntStatus(IP_SSP_001_Type *pSSP)
{
	return pSSP->MIS;
}

/* Clear the corresponding interrupt condition(s) in the SSP controller */
void IP_SSP_ClearIntPending(IP_SSP_001_Type *pSSP, SSP_Int_Clear_Type IntClear)
{
	pSSP->ICR = IntClear;
}

/* Get the current status of SSP controller */
FlagStatus IP_SSP_GetStatus(IP_SSP_001_Type *pSSP, SSP_Status_Type Stat)
{
	return (pSSP->SR & Stat) ? SET : RESET;
}

/* Get the number of bits transferred in each frame */
uint8_t IP_SSP_GetDataSize(IP_SSP_001_Type *pSSP)
{
	return SSP_CR0_DSS(pSSP->CR0);
}

/* Enable/Disable interrupt for the SSP */
void IP_SSP_Int_Enable(IP_SSP_001_Type *pSSP, SSP_Int_Mask_Type IntType, FunctionalState NewState)
{
	if (NewState == ENABLE) {
		pSSP->IMSC |= IntType;
	}
	else {
		pSSP->IMSC &= (~IntType);
	}
}

/* Enable/Disable DMA for SSP */
void IP_SSP_DMA_Cmd(IP_SSP_001_Type *pSSP, SSP_DMA_Type ssp_dma_t, FunctionalState NewState)
{
#if !defined(CHIP_LPC111X_CXX) && !defined(CHIP_LPC11UXX)
	if (NewState == ENABLE) {
		pSSP->DMACR |= ssp_dma_t;
	}
	else {
		pSSP->DMACR &= (~ssp_dma_t);
	}
#endif
}
