/*
 * @brief GPDMA Registers and control functions
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

#include "gpdma_001.h"

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

/* Initialize the GPDMA */
void IP_GPDMA_Init(IP_GPDMA_001_Type *pGPDMA) {
	uint8_t i;
	/* Reset all channel configuration register */
	for (i = 8; i > 0; i--) {
		pGPDMA->CH[i - 1].CONFIG = 0;
	}

	/* Clear all DMA interrupt and error flag */
	pGPDMA->INTTCCLEAR = 0xFF;
	pGPDMA->INTERRCLR = 0xFF;
}

/* Read the status from different registers according to the type */
IntStatus IP_GPDMA_IntGetStatus(IP_GPDMA_001_Type *pGPDMA, GPDMA_Status_Type type, uint8_t channel) {
	/**
	 * TODO check the channel <=8 type is esxited
	 */
	switch (type) {
	case GPDMA_STAT_INT:/* check status of DMA channel interrupts */
		return (IntStatus) (pGPDMA->INTSTAT & (((1UL << channel) & 0xFF)));

	case GPDMA_STAT_INTTC:	/* check terminal count interrupt request status for DMA */
		return (IntStatus) (pGPDMA->INTTCSTAT & (((1UL << channel) & 0xFF)));

	case GPDMA_STAT_INTERR:	/* check interrupt status for DMA channels */
		return (IntStatus) (pGPDMA->INTERRSTAT & (((1UL << channel) & 0xFF)));

	case GPDMA_STAT_RAWINTTC:	/* check status of the terminal count interrupt for DMA channels */
		return (IntStatus) (pGPDMA->RAWINTTCSTAT & (((1UL << channel) & 0xFF)));

	case GPDMA_STAT_RAWINTERR:	/* check status of the error interrupt for DMA channels */
		return (IntStatus) (pGPDMA->RAWINTERRSTAT & (((1UL << channel) & 0xFF)));

	default:/* check enable status for DMA channels */
		return (IntStatus) (pGPDMA->ENBLDCHNS & (((1UL << channel) & 0xFF)));
	}
}

/* Clear the Interrupt Flag from different registers according to the type */
void IP_GPDMA_ClearIntPending(IP_GPDMA_001_Type *pGPDMA, GPDMA_StateClear_Type type, uint8_t channel) {
	if (type == GPDMA_STATCLR_INTTC) {
		/* clears the terminal count interrupt request on DMA channel */
		pGPDMA->INTTCCLEAR = (((1UL << (channel)) & 0xFF));
	}
	else {
		/* clear the error interrupt request */
		pGPDMA->INTERRCLR = (((1UL << (channel)) & 0xFF));
	}
}

/* Enable or Disable the GPDMA Channel */
void IP_GPDMA_ChannelCmd(IP_GPDMA_001_Type *pGPDMA, uint8_t channelNum, FunctionalState NewState) {
	IP_GPDMA_001_CH_Type *pDMAch;

	/* Get Channel pointer */
	pDMAch = (IP_GPDMA_001_CH_Type *) &(pGPDMA->CH[channelNum]);

	if (NewState == ENABLE) {
		pDMAch->CONFIG |= GPDMA_DMACCxConfig_E;
	}
	else {
		pDMAch->CONFIG &= ~GPDMA_DMACCxConfig_E;
	}
}

/* Set up the DPDMA according to the specification configuration details */
Status IP_GPDMA_Setup(IP_GPDMA_001_Type *pGPDMA,
					  GPDMA_Channel_CFG_Type *GPDMAChannelConfig,
					  uint32_t GPDMA_LUTPerBurstSrcConn,
					  uint32_t GPDMA_LUTPerBurstDstConn,
					  uint32_t GPDMA_LUTPerWidSrcConn,
					  uint32_t GPDMA_LUTPerWidDstConn,
					  uint32_t GPDMA_LUTPerAddrSrcConn,
					  uint32_t GPDMA_LUTPerAddrDstConn,
					  uint8_t SrcPeripheral,
					  uint8_t DstPeripheral)
{
	IP_GPDMA_001_CH_Type *pDMAch;

	if (pGPDMA->ENBLDCHNS & ((((1UL << (GPDMAChannelConfig->ChannelNum)) & 0xFF)))) {
		/* This channel is enabled, return ERROR, need to release this channel first */
		return ERROR;
	}

	/* Get Channel pointer */
	pDMAch = (IP_GPDMA_001_CH_Type *) &(pGPDMA->CH[GPDMAChannelConfig->ChannelNum]);

	/* Reset the Interrupt status */
	pGPDMA->INTTCCLEAR = (((1UL << (GPDMAChannelConfig->ChannelNum)) & 0xFF));
	pGPDMA->INTERRCLR = (((1UL << (GPDMAChannelConfig->ChannelNum)) & 0xFF));

	/* Assign Linker List Item value */
	pDMAch->LLI = 0;/* Fixed to 0 (no link list) */

	/* Enable DMA channels, little endian */
	pGPDMA->CONFIG = GPDMA_DMACConfig_E;
	while (!(pGPDMA->CONFIG & GPDMA_DMACConfig_E)) {}

	pDMAch->SRCADDR = GPDMAChannelConfig->SrcAddr;
	pDMAch->DESTADDR = GPDMAChannelConfig->DstAddr;

	/* Configure DMA Channel, enable Error Counter and Terminate counter */
	pDMAch->CONFIG = GPDMA_DMACCxConfig_IE
					 | GPDMA_DMACCxConfig_ITC		/*| GPDMA_DMACCxConfig_E*/
					 | GPDMA_DMACCxConfig_TransferType((uint32_t) GPDMAChannelConfig->TransferType)
					 | GPDMA_DMACCxConfig_SrcPeripheral(SrcPeripheral)
					 | GPDMA_DMACCxConfig_DestPeripheral(DstPeripheral);

	switch (GPDMAChannelConfig->TransferType) {
	/* Memory to memory */
	case GPDMA_TRANSFERTYPE_M2M_CONTROLLER_DMA:
		pDMAch->CONTROL = GPDMA_DMACCxControl_TransferSize(GPDMAChannelConfig->TransferSize)
						  | GPDMA_DMACCxControl_SBSize((4UL))		/**< Burst size = 32 */
						  | GPDMA_DMACCxControl_DBSize((4UL))		/**< Burst size = 32 */
						  | GPDMA_DMACCxControl_SWidth(GPDMAChannelConfig->TransferWidth)
						  | GPDMA_DMACCxControl_DWidth(GPDMAChannelConfig->TransferWidth)
						  | GPDMA_DMACCxControl_SI
						  | GPDMA_DMACCxControl_DI
						  | GPDMA_DMACCxControl_I;
		break;

	case GPDMA_TRANSFERTYPE_M2P_CONTROLLER_DMA:
	case GPDMA_TRANSFERTYPE_M2P_CONTROLLER_PERIPHERAL:
		pDMAch->CONTROL = GPDMA_DMACCxControl_TransferSize((uint32_t) GPDMAChannelConfig->TransferSize)
						  | GPDMA_DMACCxControl_SBSize(GPDMA_LUTPerBurstDstConn)
						  | GPDMA_DMACCxControl_DBSize(GPDMA_LUTPerBurstDstConn)
						  | GPDMA_DMACCxControl_SWidth(GPDMA_LUTPerWidDstConn)
						  | GPDMA_DMACCxControl_DWidth(GPDMA_LUTPerWidDstConn)
						  | GPDMA_DMACCxControl_DestTransUseAHBMaster1
						  | GPDMA_DMACCxControl_SI
						  | GPDMA_DMACCxControl_I;
		break;

	case GPDMA_TRANSFERTYPE_P2M_CONTROLLER_DMA:
	case GPDMA_TRANSFERTYPE_P2M_CONTROLLER_PERIPHERAL:
		pDMAch->CONTROL = GPDMA_DMACCxControl_TransferSize((uint32_t) GPDMAChannelConfig->TransferSize)
						  | GPDMA_DMACCxControl_SBSize(GPDMA_LUTPerBurstSrcConn)
						  | GPDMA_DMACCxControl_DBSize(GPDMA_LUTPerBurstSrcConn)
						  | GPDMA_DMACCxControl_SWidth(GPDMA_LUTPerWidSrcConn)
						  | GPDMA_DMACCxControl_DWidth(GPDMA_LUTPerWidSrcConn)
						  | GPDMA_DMACCxControl_SrcTransUseAHBMaster1
						  | GPDMA_DMACCxControl_DI
						  | GPDMA_DMACCxControl_I;
		break;

	case GPDMA_TRANSFERTYPE_P2P_CONTROLLER_DMA:
	case GPDMA_TRANSFERTYPE_P2P_CONTROLLER_DestPERIPHERAL:
	case GPDMA_TRANSFERTYPE_P2P_CONTROLLER_SrcPERIPHERAL:
		pDMAch->CONTROL = GPDMA_DMACCxControl_TransferSize((uint32_t) GPDMAChannelConfig->TransferSize)
						  | GPDMA_DMACCxControl_SBSize(GPDMA_LUTPerBurstSrcConn)
						  | GPDMA_DMACCxControl_DBSize(GPDMA_LUTPerBurstDstConn)
						  | GPDMA_DMACCxControl_SWidth(GPDMA_LUTPerWidSrcConn)
						  | GPDMA_DMACCxControl_DWidth(GPDMA_LUTPerWidDstConn)
						  | GPDMA_DMACCxControl_SrcTransUseAHBMaster1
						  | GPDMA_DMACCxControl_DestTransUseAHBMaster1
						  | GPDMA_DMACCxControl_I;

		break;

	/* Do not support any more transfer type, return ERROR */
	default:
		return ERROR;
	}

	return SUCCESS;
}
