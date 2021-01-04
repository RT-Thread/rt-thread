/******************************************************************************
* Copyright (C) 2013 - 2020 Xilinx, Inc.  All rights reserved.
* SPDX-License-Identifier: MIT
******************************************************************************/

/*****************************************************************************/
/**
*
* @file xsdps_card.c
* @addtogroup sdps_v3_9
* @{
*
* Contains the interface functions of the XSdPs driver.
* See xsdps.h for a detailed description of the device and driver.
*
* <pre>
* MODIFICATION HISTORY:
*
* Ver   Who    Date     Changes
* ----- ---    -------- -----------------------------------------------
* 3.9   mn     03/03/20 Restructured the code for more readability and modularity
*       mn     03/16/20 Move XSdPs_Select_Card API to User APIs
*
* </pre>
*
******************************************************************************/

/***************************** Include Files *********************************/
#include "xsdps_core.h"

/************************** Constant Definitions *****************************/

/**************************** Type Definitions *******************************/

/***************** Macros (Inline Functions) Definitions *********************/

/************************** Function Prototypes ******************************/

/*****************************************************************************/
/**
* @brief
* This function performs SD read in polled mode.
*
* @param	InstancePtr is a pointer to the instance to be worked on.
* @param	Arg is the address passed by the user that is to be sent as
* 		argument along with the command.
* @param	BlkCnt - Block count passed by the user.
* @param	Buff - Pointer to the data buffer for a DMA transfer.
*
* @return
* 		- XST_SUCCESS if initialization was successful
* 		- XST_FAILURE if failure - could be because another transfer
* 		is in progress or command or data inhibit is set
*
******************************************************************************/
s32 XSdPs_Read(XSdPs *InstancePtr, u32 Arg, u32 BlkCnt, u8 *Buff)
{
	s32 Status;
	u16 BlkSize;

	BlkSize = XSDPS_BLK_SIZE_512_MASK;

	XSdPs_SetupReadDma(InstancePtr, BlkCnt, BlkSize, Buff);

	if (BlkCnt == 1U) {
		/* Send single block read command */
		Status = XSdPs_CmdTransfer(InstancePtr, CMD17, Arg, BlkCnt);
		if (Status != XST_SUCCESS) {
			Status = XST_FAILURE;
			goto RETURN_PATH;
		}
	} else {
		/* Send multiple blocks read command */
		Status = XSdPs_CmdTransfer(InstancePtr, CMD18, Arg, BlkCnt);
		if (Status != XST_SUCCESS) {
			Status = XST_FAILURE;
			goto RETURN_PATH;
		}
	}

	/* Check for transfer done */
	Status = XSdps_CheckTransferDone(InstancePtr);
	if (Status != XST_SUCCESS) {
		Status = XST_FAILURE;
	}

	if (InstancePtr->Config.IsCacheCoherent == 0U) {
		Xil_DCacheInvalidateRange((INTPTR)Buff,
				(INTPTR)BlkCnt * BlkSize);
	}

	Status = XST_SUCCESS;

RETURN_PATH:
	return Status;
}

/*****************************************************************************/
/**
* @brief
* This function performs SD write in polled mode.
*
* @param	InstancePtr is a pointer to the instance to be worked on.
* @param	Arg is the address passed by the user that is to be sent as
* 		argument along with the command.
* @param	BlkCnt - Block count passed by the user.
* @param	Buff - Pointer to the data buffer for a DMA transfer.
*
* @return
* 		- XST_SUCCESS if initialization was successful
* 		- XST_FAILURE if failure - could be because another transfer
* 		is in progress or command or data inhibit is set
*
******************************************************************************/
s32 XSdPs_Write(XSdPs *InstancePtr, u32 Arg, u32 BlkCnt, const u8 *Buff)
{
	s32 Status;
	u16 BlkSize;

	BlkSize = XSDPS_BLK_SIZE_512_MASK;

	XSdPs_SetupWriteDma(InstancePtr, BlkCnt, BlkSize, Buff);

	if (BlkCnt == 1U) {
		/* Send single block write command */
		Status = XSdPs_CmdTransfer(InstancePtr, CMD24, Arg, BlkCnt);
		if (Status != XST_SUCCESS) {
			Status = XST_FAILURE;
			goto RETURN_PATH;
		}
	} else {
		/* Send multiple blocks write command */
		Status = XSdPs_CmdTransfer(InstancePtr, CMD25, Arg, BlkCnt);
		if (Status != XST_SUCCESS) {
			Status = XST_FAILURE;
			goto RETURN_PATH;
		}
	}

	/* Check for transfer done */
	Status = XSdps_CheckTransferDone(InstancePtr);
	if (Status != XST_SUCCESS) {
		Status = XST_FAILURE;
	}

	Status = XST_SUCCESS;

	RETURN_PATH:
		return Status;
}
/*****************************************************************************/
/**
*
* @brief
* Identify type of card using CMD0 + CMD1 sequence
*
*
* @param	InstancePtr is a pointer to the XSdPs instance.
*
******************************************************************************/
s32 XSdPs_IdentifyCard(XSdPs *InstancePtr)
{
	s32 Status;

	if ((InstancePtr->HC_Version == XSDPS_HC_SPEC_V3) &&
			((InstancePtr->Host_Caps & XSDPS_CAPS_SLOT_TYPE_MASK)
			== XSDPS_CAPS_EMB_SLOT)) {
		InstancePtr->CardType = XSDPS_CHIP_EMMC;
		Status = XST_SUCCESS;
		goto RETURN_PATH;
	}

	/* 74 CLK delay after card is powered up, before the first command. */
	usleep(XSDPS_INIT_DELAY);

	/* CMD0 no response expected */
	Status = XSdPs_CmdTransfer(InstancePtr, CMD0, 0U, 0U);
	if (Status != XST_SUCCESS) {
		Status = XST_FAILURE;
		goto RETURN_PATH;
	}

	/* Host High Capacity support & High voltage window */
	Status = XSdPs_CmdTransfer(InstancePtr, CMD1,
			XSDPS_ACMD41_HCS | XSDPS_CMD1_HIGH_VOL, 0U);
	if (Status != XST_SUCCESS) {
		InstancePtr->CardType = XSDPS_CARD_SD;
	} else {
		InstancePtr->CardType = XSDPS_CARD_MMC;
	}

	XSdPs_WriteReg16(InstancePtr->Config.BaseAddress,
			XSDPS_NORM_INTR_STS_OFFSET, XSDPS_NORM_INTR_ALL_MASK);
	XSdPs_WriteReg16(InstancePtr->Config.BaseAddress,
			XSDPS_ERR_INTR_STS_OFFSET, XSDPS_ERROR_INTR_ALL_MASK);

	Status = XSdPs_Reset(InstancePtr, XSDPS_SWRST_CMD_LINE_MASK);
	if (Status != XST_SUCCESS) {
		Status = XST_FAILURE;
		goto RETURN_PATH ;
	}

	Status = XST_SUCCESS;

RETURN_PATH:
	return Status;
}

/*****************************************************************************/
/**
* @brief
* SD initialization is done in this function
*
*
* @param	InstancePtr is a pointer to the instance to be worked on.
*
* @return
* 		- XST_SUCCESS if initialization was successful
* 		- XST_FAILURE if failure - could be because
* 			a) SD is already initialized
* 			b) There is no card inserted
* 			c) One of the steps (commands) in the
			   initialization cycle failed
*
* @note		This function initializes the SD card by following its
*		initialization and identification state diagram.
*		CMD0 is sent to reset card.
*		CMD8 and ACDM41 are sent to identify voltage and
*		high capacity support
*		CMD2 and CMD3 are sent to obtain Card ID and
*		Relative card address respectively.
*		CMD9 is sent to read the card specific data.
*
******************************************************************************/
s32 XSdPs_SdCardInitialize(XSdPs *InstancePtr)
{
	s32 Status;

#ifndef UHS_MODE_ENABLE
	InstancePtr->Config.BusWidth = XSDPS_WIDTH_4;
#endif

	Status = XSdPs_SdCardEnum(InstancePtr);
	if (Status != XST_SUCCESS) {
		Status = XST_FAILURE;
		goto RETURN_PATH;
	}

	Status = XSdPs_SdModeInit(InstancePtr);
	if (Status != XST_SUCCESS) {
		Status = XST_FAILURE;
		goto RETURN_PATH;
	}

	Status = XST_SUCCESS;

RETURN_PATH:
	return Status;

}

/*****************************************************************************/
/**
* @brief
* Mmc initialization is done in this function
*
*
* @param	InstancePtr is a pointer to the instance to be worked on.
*
* @return
* 		- XST_SUCCESS if initialization was successful
* 		- XST_FAILURE if failure - could be because
* 			a) MMC is already initialized
* 			b) There is no card inserted
* 			c) One of the steps (commands) in the initialization
*			   cycle failed
* @note 	This function initializes the SD card by following its
*		initialization and identification state diagram.
*		CMD0 is sent to reset card.
*		CMD1 sent to identify voltage and high capacity support
*		CMD2 and CMD3 are sent to obtain Card ID and
*		Relative card address respectively.
*		CMD9 is sent to read the card specific data.
*
******************************************************************************/
s32 XSdPs_MmcCardInitialize(XSdPs *InstancePtr)
{
	s32 Status;

	Status = XSdPs_MmcCardEnum(InstancePtr);
	if (Status != XST_SUCCESS) {
		Status = XST_FAILURE;
		goto RETURN_PATH;
	}

	if (((InstancePtr->CardType == XSDPS_CARD_MMC) &&
				(InstancePtr->Card_Version > CSD_SPEC_VER_3)) &&
				(InstancePtr->HC_Version == XSDPS_HC_SPEC_V2)) {
		Status = XSdPs_MmcModeInit(InstancePtr);
		if (Status != XST_SUCCESS) {
			Status = XST_FAILURE;
			goto RETURN_PATH;
		}
	} else if (InstancePtr->CardType == XSDPS_CHIP_EMMC) {
		Status = XSdPs_EmmcModeInit(InstancePtr);
		if (Status != XST_SUCCESS) {
			Status = XST_FAILURE;
			goto RETURN_PATH;
		}
	} else {
		Status = XST_FAILURE;
		goto RETURN_PATH;

	}

	if (InstancePtr->Mode != XSDPS_DDR52_MODE) {
		Status = XSdPs_SetBlkSize(InstancePtr, XSDPS_BLK_SIZE_512_MASK);
		if (Status != XST_SUCCESS) {
			Status = XST_FAILURE;
			goto RETURN_PATH;
		}
	}

	Status = XST_SUCCESS;

RETURN_PATH:
	return Status;
}

/*****************************************************************************/
/**
* @brief
* This function checks if the card is present or not.
*
* @param	InstancePtr is a pointer to the instance to be worked on.
*
* @return	None
*
******************************************************************************/
s32 XSdPs_CheckCardDetect(XSdPs *InstancePtr)
{
	u32 PresentStateReg;
	s32 Status;

	if ((InstancePtr->HC_Version == XSDPS_HC_SPEC_V3) &&
				((InstancePtr->Host_Caps & XSDPS_CAPS_SLOT_TYPE_MASK)
				== XSDPS_CAPS_EMB_SLOT)) {
		Status = XST_SUCCESS;
		goto RETURN_PATH;
	}

	if(InstancePtr->Config.CardDetect != 0U) {
		/*
		 * Check the present state register to make sure
		 * card is inserted and detected by host controller
		 */
		PresentStateReg = XSdPs_ReadReg(InstancePtr->Config.BaseAddress,
				XSDPS_PRES_STATE_OFFSET);
		if ((PresentStateReg & XSDPS_PSR_CARD_INSRT_MASK) == 0U)	{
			Status = XST_FAILURE;
			goto RETURN_PATH;
		}
	}

	Status = XST_SUCCESS;

RETURN_PATH:
	return Status;
}

/*****************************************************************************/
/**
* @brief
* This function sends CMD0 to reset the card.
*
* @param	InstancePtr is a pointer to the instance to be worked on.
*
* @return	None
*
******************************************************************************/
s32 XSdPs_CardReset(XSdPs *InstancePtr)
{
	s32 Status;

	/* CMD0 no response expected */
	Status = XSdPs_CmdTransfer(InstancePtr, (u32)CMD0, 0U, 0U);
	if (Status != XST_SUCCESS) {
		Status = XST_FAILURE;
	}

	return Status;
}

/*****************************************************************************/
/**
* @brief
* This function sends command to get the card interface details.
*
* @param	InstancePtr is a pointer to the instance to be worked on.
*
* @return	None
*
******************************************************************************/
s32 XSdPs_CardIfCond(XSdPs *InstancePtr)
{
	u32 RespOCR;
	s32 Status;

	/*
	 * CMD8; response expected
	 * 0x1AA - Supply Voltage 2.7 - 3.6V and AA is pattern
	 */
	Status = XSdPs_CmdTransfer(InstancePtr, CMD8,
			XSDPS_CMD8_VOL_PATTERN, 0U);
	if ((Status != XST_SUCCESS) && (Status != XSDPS_CT_ERROR)) {
		Status = XST_FAILURE;
		goto RETURN_PATH;
	}

	if (Status == XSDPS_CT_ERROR) {
		Status = XSdPs_Reset(InstancePtr, XSDPS_SWRST_CMD_LINE_MASK);
		if (Status != XST_SUCCESS) {
			Status = XST_FAILURE;
			goto RETURN_PATH ;
		}
	}

	RespOCR = XSdPs_ReadReg(InstancePtr->Config.BaseAddress,
						XSDPS_RESP0_OFFSET);
	if (RespOCR != XSDPS_CMD8_VOL_PATTERN) {
		InstancePtr->Card_Version = XSDPS_SD_VER_1_0;
	} else {
		InstancePtr->Card_Version = XSDPS_SD_VER_2_0;
	}

	Status = XST_SUCCESS;

RETURN_PATH:
	return Status;
}

/*****************************************************************************/
/**
* @brief
* This function sends command to get the card operating condition.
*
* @param	InstancePtr is a pointer to the instance to be worked on.
*
* @return	None
*
******************************************************************************/
s32 XSdPs_CardOpCond(XSdPs *InstancePtr)
{
	u32 RespOCR;
	s32 Status;
	u32 Arg;

	/* Send ACMD41 while card is still busy with power up */
	do {
		if (InstancePtr->CardType == XSDPS_CARD_SD) {
			Status = XSdPs_CmdTransfer(InstancePtr, CMD55, 0U, 0U);
			if (Status != XST_SUCCESS) {
				Status = XST_FAILURE;
				goto RETURN_PATH;
			}

			Arg = XSDPS_ACMD41_HCS | XSDPS_ACMD41_3V3 | (0x1FFU << 15U);
			if ((InstancePtr->HC_Version == XSDPS_HC_SPEC_V3) &&
				(InstancePtr->Config.BusWidth == XSDPS_WIDTH_8)) {
				Arg |= XSDPS_OCR_S18;
			}

			/* 0x40300000 - Host High Capacity support & 3.3V window */
			Status = XSdPs_CmdTransfer(InstancePtr, ACMD41,
					Arg, 0U);
		} else {
			/* Send CMD1 while card is still busy with power up */
			Status = XSdPs_CmdTransfer(InstancePtr, CMD1,
					XSDPS_ACMD41_HCS | XSDPS_CMD1_HIGH_VOL, 0U);
		}
		if (Status != XST_SUCCESS) {
			Status = XST_FAILURE;
			goto RETURN_PATH;
		}

		/* Response with card capacity */
		RespOCR = XSdPs_ReadReg(InstancePtr->Config.BaseAddress,
				XSDPS_RESP0_OFFSET);
	} while ((RespOCR & XSDPS_RESPOCR_READY) == 0U);

	/* Update HCS support flag based on card capacity response */
	if ((RespOCR & XSDPS_ACMD41_HCS) != 0U) {
		InstancePtr->HCS = 1U;
	}

	if ((RespOCR & XSDPS_OCR_S18) != 0U) {
		InstancePtr->Switch1v8 = 1U;
		Status = XSdPs_Switch_Voltage(InstancePtr);
		if (Status != XST_SUCCESS) {
			Status = XST_FAILURE;
			goto RETURN_PATH;
		}
	}

	Status = XST_SUCCESS;

RETURN_PATH:
	return Status;
}

/*****************************************************************************/
/**
* @brief
* This function is used to get the card ID.
*
* @param	InstancePtr is a pointer to the instance to be worked on.
*
* @return	None
*
******************************************************************************/
s32 XSdPs_GetCardId(XSdPs *InstancePtr)
{
	s32 Status;

	/* CMD2 for Card ID */
	Status = XSdPs_CmdTransfer(InstancePtr, CMD2, 0U, 0U);
	if (Status != XST_SUCCESS) {
		Status = XST_FAILURE;
		goto RETURN_PATH;
	}

	InstancePtr->CardID[0] =
			XSdPs_ReadReg16(InstancePtr->Config.BaseAddress,
			XSDPS_RESP0_OFFSET);
	InstancePtr->CardID[1] =
			XSdPs_ReadReg16(InstancePtr->Config.BaseAddress,
			XSDPS_RESP1_OFFSET);
	InstancePtr->CardID[2] =
			XSdPs_ReadReg16(InstancePtr->Config.BaseAddress,
			XSDPS_RESP2_OFFSET);
	InstancePtr->CardID[3] =
			XSdPs_ReadReg16(InstancePtr->Config.BaseAddress,
			XSDPS_RESP3_OFFSET);

	if(InstancePtr->CardType == XSDPS_CARD_SD) {
		do {
			Status = XSdPs_CmdTransfer(InstancePtr, CMD3, 0U, 0U);
			if (Status != XST_SUCCESS) {
				Status = XST_FAILURE;
				goto RETURN_PATH;
			}

			/*
			 * Relative card address is stored as the upper 16 bits
			 * This is to avoid shifting when sending commands
			 */
			InstancePtr->RelCardAddr =
					XSdPs_ReadReg(InstancePtr->Config.BaseAddress,
						XSDPS_RESP0_OFFSET) & 0xFFFF0000U;
		} while (InstancePtr->RelCardAddr == 0U);
	} else {
		/* Set relative card address */
		InstancePtr->RelCardAddr = 0x12340000U;
		Status = XSdPs_CmdTransfer(InstancePtr, CMD3, (InstancePtr->RelCardAddr), 0U);
		if (Status != XST_SUCCESS) {
			Status = XST_FAILURE;
			goto RETURN_PATH;
		}
	}

	Status = XST_SUCCESS;

RETURN_PATH:
	return Status;
}

/*****************************************************************************/
/**
* @brief
* This function is used to get the CSD register from the card.
*
* @param	InstancePtr is a pointer to the instance to be worked on.
*
* @return	None
*
******************************************************************************/
s32 XSdPs_GetCsd(XSdPs *InstancePtr)
{
	s32 Status;
	u32 CSD[4];
	u32 BlkLen;
	u32 DeviceSize;
	u32 Mult;

	Status = XSdPs_CmdTransfer(InstancePtr, CMD9, (InstancePtr->RelCardAddr), 0U);
	if (Status != XST_SUCCESS) {
		Status = XST_FAILURE;
		goto RETURN_PATH;
	}

	/*
	 * Card specific data is read.
	 * Currently not used for any operation.
	 */
	CSD[0] = XSdPs_ReadReg(InstancePtr->Config.BaseAddress,
			XSDPS_RESP0_OFFSET);
	CSD[1] = XSdPs_ReadReg(InstancePtr->Config.BaseAddress,
			XSDPS_RESP1_OFFSET);
	CSD[2] = XSdPs_ReadReg(InstancePtr->Config.BaseAddress,
			XSDPS_RESP2_OFFSET);
	CSD[3] = XSdPs_ReadReg(InstancePtr->Config.BaseAddress,
			XSDPS_RESP3_OFFSET);

	if (InstancePtr->CardType != XSDPS_CARD_SD) {
		InstancePtr->Card_Version = (u8)((u32)(CSD[3] & CSD_SPEC_VER_MASK) >>18U);
		Status = XST_SUCCESS;
		goto RETURN_PATH;
	}

	if (((CSD[3] & CSD_STRUCT_MASK) >> 22U) == 0U) {
		BlkLen = 1U << ((u32)(CSD[2] & READ_BLK_LEN_MASK) >> 8U);
		Mult = 1U << ((u32)((CSD[1] & C_SIZE_MULT_MASK) >> 7U) + 2U);
		DeviceSize = (CSD[1] & C_SIZE_LOWER_MASK) >> 22U;
		DeviceSize |= (CSD[2] & C_SIZE_UPPER_MASK) << 10U;
		DeviceSize = (DeviceSize + 1U) * Mult;
		DeviceSize =  DeviceSize * BlkLen;
		InstancePtr->SectorCount = (DeviceSize/XSDPS_BLK_SIZE_512_MASK);
	} else if (((CSD[3] & CSD_STRUCT_MASK) >> 22U) == 1U) {
		InstancePtr->SectorCount = (((CSD[1] & CSD_V2_C_SIZE_MASK) >> 8U) +
										1U) * 1024U;
	} else {
		Status = XST_FAILURE;
		goto RETURN_PATH;
	}

	Status = XST_SUCCESS;

RETURN_PATH:
	return Status;
}

/*****************************************************************************/
/**
* @brief
* This function is used to set the card voltage to 1.8V.
*
* @param	InstancePtr is a pointer to the instance to be worked on.
*
* @return	None
*
******************************************************************************/
s32 XSdPs_CardSetVoltage18(XSdPs *InstancePtr)
{
	s32 Status;
	u16 CtrlReg;
	u16 ClockReg;

	/* Stop the clock */
	CtrlReg = XSdPs_ReadReg16(InstancePtr->Config.BaseAddress,
			XSDPS_CLK_CTRL_OFFSET);
	CtrlReg &= ~(XSDPS_CC_SD_CLK_EN_MASK | XSDPS_CC_INT_CLK_EN_MASK);
	XSdPs_WriteReg16(InstancePtr->Config.BaseAddress, XSDPS_CLK_CTRL_OFFSET,
			CtrlReg);

	/* Check for 1.8V signal enable bit is cleared by Host */
	Status = XSdPs_SetVoltage18(InstancePtr);
	if (Status != XST_SUCCESS) {
		Status = XST_FAILURE;
		goto RETURN_PATH;
	}

	ClockReg = XSdPs_ReadReg16(InstancePtr->Config.BaseAddress,
				XSDPS_CLK_CTRL_OFFSET);
	/* Enable the clock in the controller */
	Status = XSdPs_EnableClock(InstancePtr, ClockReg);
	if (Status != XST_SUCCESS) {
		Status = XST_FAILURE;
	}

	/* Wait for 1mSec */
	(void)usleep(1000U);

	Status = XST_SUCCESS;

RETURN_PATH:
	return Status;
}

/*****************************************************************************/
/**
* @brief
* This function is used to do initial Reset Configuration.
*
* @param	InstancePtr is a pointer to the instance to be worked on.
*
* @return	None
*
******************************************************************************/
s32 XSdPs_ResetConfig(XSdPs *InstancePtr)
{
	s32 Status;

	XSdPs_DisableBusPower(InstancePtr);

	Status = XSdPs_Reset(InstancePtr, XSDPS_SWRST_ALL_MASK);
	if (Status != XST_SUCCESS) {
		Status = XST_FAILURE;
		goto RETURN_PATH ;
	}

	XSdPs_EnableBusPower(InstancePtr);

RETURN_PATH:
	return Status;
}

/*****************************************************************************/
/**
* @brief
* This function is used to do initial Host Configuration.
*
* @param	InstancePtr is a pointer to the instance to be worked on.
*
* @return	None
*
******************************************************************************/
void XSdPs_HostConfig(XSdPs *InstancePtr)
{
	XSdPs_ConfigPower(InstancePtr);

	XSdPs_ConfigDma(InstancePtr);

	XSdPs_ConfigInterrupt(InstancePtr);

	/*
	 * Transfer mode register - default value
	 * DMA enabled, block count enabled, data direction card to host(read)
	 */
	InstancePtr->TransferMode = XSDPS_TM_DMA_EN_MASK | XSDPS_TM_BLK_CNT_EN_MASK |
			XSDPS_TM_DAT_DIR_SEL_MASK;

	/* Set block size to 512 by default */
	XSdPs_WriteReg16(InstancePtr->Config.BaseAddress,
			XSDPS_BLK_SIZE_OFFSET, XSDPS_BLK_SIZE_512_MASK);
}

/*****************************************************************************/
/**
* @brief
* This function checks for Reset Done bits to be cleared after a reset assert.
*
* @param	InstancePtr is a pointer to the instance to be worked on.
* @param	Value is the bits to be checked to be cleared.
*
* @return	None
*
******************************************************************************/
s32 XSdPs_CheckResetDone(XSdPs *InstancePtr, u8 Value)
{
	u32 Timeout = 1000000U;
	u32 ReadReg;
	s32 Status;

	/* Proceed with initialization only after reset is complete */
	do {
		ReadReg = XSdPs_ReadReg8(InstancePtr->Config.BaseAddress,
				XSDPS_SW_RST_OFFSET);
		Timeout = Timeout - 1U;
		usleep(1);
	} while (((ReadReg & Value) != 0U)
			&& (Timeout != 0U));

	if (Timeout == 0U) {
		Status = XST_FAILURE;
		goto RETURN_PATH ;
	}

	Status = XST_SUCCESS;

RETURN_PATH:
	return Status;
}

/*****************************************************************************/
/**
* @brief
* This function is used to setup the voltage switch.
*
* @param	InstancePtr is a pointer to the instance to be worked on.
*
* @return	None
*
******************************************************************************/
s32 XSdPs_SetupVoltageSwitch(XSdPs *InstancePtr)
{
	u32 Timeout = 10000;
	s32 Status;
	u32 ReadReg;

	/* Send switch voltage command */
	Status = XSdPs_CmdTransfer(InstancePtr, CMD11, 0U, 0U);
	if (Status != XST_SUCCESS) {
		Status = XST_FAILURE;
		goto RETURN_PATH;
	}

	/* Wait for CMD and DATA line to go low */
	do {
		ReadReg = XSdPs_ReadReg(InstancePtr->Config.BaseAddress,
				XSDPS_PRES_STATE_OFFSET);
		Timeout = Timeout - 1;
		usleep(1);
	} while (((ReadReg & (XSDPS_PSR_CMD_SG_LVL_MASK |
			XSDPS_PSR_DAT30_SG_LVL_MASK)) != 0U)
			&& (Timeout != 0U));

	if (Timeout == 0U) {
		Status = XST_FAILURE;
		goto RETURN_PATH ;
	}

RETURN_PATH:
	return Status;
}

/*****************************************************************************/
/**
* @brief
* This function is used to check if the Cmd and Dat buses are high.
*
* @param	InstancePtr is a pointer to the instance to be worked on.
*
* @return	None
*
******************************************************************************/
s32 XSdPs_CheckBusHigh(XSdPs *InstancePtr)
{
	u32 Timeout = 10000;
	s32 Status;
	u32 ReadReg;

	/* Wait for CMD and DATA line to go high */
	Timeout = MAX_TIMEOUT;
	do {
		ReadReg = XSdPs_ReadReg(InstancePtr->Config.BaseAddress,
				XSDPS_PRES_STATE_OFFSET);
		Timeout = Timeout - 1;
		usleep(1);
	} while (((ReadReg & (XSDPS_PSR_CMD_SG_LVL_MASK | XSDPS_PSR_DAT30_SG_LVL_MASK))
			!= (XSDPS_PSR_CMD_SG_LVL_MASK | XSDPS_PSR_DAT30_SG_LVL_MASK))
			&& (Timeout != 0U));

	if (Timeout == 0U) {
		Status = XST_FAILURE;
		goto RETURN_PATH ;
	}

	Status = XST_SUCCESS;

RETURN_PATH:
	return Status;
}

/*****************************************************************************/
/**
*
* @brief
* API to Identify the supported UHS mode. This API will assign the
* corresponding tap delay API to the Config_TapDelay pointer based on the
* supported bus speed.
*
*
* @param	InstancePtr is a pointer to the XSdPs instance.
* @param	ReadBuff contains the response for CMD6
*
* @return	None.
*
* @note		None.
*
******************************************************************************/
void XSdPs_Identify_UhsMode(XSdPs *InstancePtr, u8 *ReadBuff)
{
	if (((ReadBuff[13] & UHS_SDR104_SUPPORT) != 0U) &&
		(InstancePtr->Config.InputClockHz >= XSDPS_SD_INPUT_MAX_CLK)) {
		InstancePtr->Mode = XSDPS_UHS_SPEED_MODE_SDR104;
		if (InstancePtr->Config.BankNumber == 2U) {
			InstancePtr->OTapDelay = SD_OTAPDLYSEL_HS200_B2;
		} else {
			InstancePtr->OTapDelay = SD_OTAPDLYSEL_HS200_B0;
		}
	} else if (((ReadBuff[13] & UHS_SDR50_SUPPORT) != 0U) &&
		(InstancePtr->Config.InputClockHz >= XSDPS_SD_SDR50_MAX_CLK)) {
		InstancePtr->Mode = XSDPS_UHS_SPEED_MODE_SDR50;
		InstancePtr->OTapDelay = SD_OTAPDLYSEL_SD50;
	} else if (((ReadBuff[13] & UHS_DDR50_SUPPORT) != 0U) &&
		(InstancePtr->Config.InputClockHz >= XSDPS_SD_DDR50_MAX_CLK)) {
		InstancePtr->Mode = XSDPS_UHS_SPEED_MODE_DDR50;
		InstancePtr->OTapDelay = SD_OTAPDLYSEL_SD_DDR50;
		InstancePtr->ITapDelay = SD_ITAPDLYSEL_SD_DDR50;
	} else if (((ReadBuff[13] & UHS_SDR25_SUPPORT) != 0U) &&
		(InstancePtr->Config.InputClockHz >= XSDPS_SD_SDR25_MAX_CLK)) {
		InstancePtr->Mode = XSDPS_UHS_SPEED_MODE_SDR25;
		InstancePtr->OTapDelay = SD_OTAPDLYSEL_SD_HSD;
		InstancePtr->ITapDelay = SD_ITAPDLYSEL_HSD;
	} else {
		InstancePtr->Mode = XSDPS_UHS_SPEED_MODE_SDR12;
	}
}

/*****************************************************************************/
/**
*
* @brief
* API to set Tap Delay w.r.t speed modes
*
*
* @param	InstancePtr is a pointer to the XSdPs instance.
*
* @return	None
*
* @note		None.
*
******************************************************************************/
void XSdPs_SetTapDelay(XSdPs *InstancePtr)
{
	if ((InstancePtr->Mode == XSDPS_DEFAULT_SPEED_MODE) ||
		(InstancePtr->Mode == XSDPS_UHS_SPEED_MODE_SDR12)) {
		return;
	}

#ifndef versal
	/* Issue DLL Reset */
	XSdPs_DllRstCtrl(InstancePtr, 1U);
#endif

	/* Configure the Tap Delay Registers */
	XSdPs_ConfigTapDelay(InstancePtr);

#ifndef versal
	/* Release the DLL out of reset */
	XSdPs_DllRstCtrl(InstancePtr, 0U);
#endif
}

/*****************************************************************************/
/**
* @brief
* This function is used to change the SD Bus Speed.
*
* @param	InstancePtr is a pointer to the instance to be worked on.
*
* @return	None
*
******************************************************************************/
s32 XSdPs_Change_SdBusSpeed(XSdPs *InstancePtr)
{
	s32 Status;
	u32 Arg;
	u16 BlkCnt;
	u16 BlkSize;
	u16 CtrlReg;
	u8 ReadBuff[64] = {0U};

	Status = XSdPs_CalcBusSpeed(InstancePtr, &Arg);
	if (Status != XST_SUCCESS) {
		Status = XST_FAILURE;
		goto RETURN_PATH;
	}

	BlkCnt = XSDPS_SWITCH_CMD_BLKCNT;
	BlkSize = XSDPS_SWITCH_CMD_BLKSIZE;

	XSdPs_SetupReadDma(InstancePtr, BlkCnt, BlkSize, ReadBuff);

	Status = XSdPs_CmdTransfer(InstancePtr, CMD6, Arg, BlkCnt);
	if (Status != XST_SUCCESS) {
		Status = XST_FAILURE;
		goto RETURN_PATH;
	}

	/* Check for transfer done */
	Status = XSdps_CheckTransferDone(InstancePtr);
	if (Status != XST_SUCCESS) {
		Status = XST_FAILURE;
	}

	if (InstancePtr->Switch1v8 != 0U) {
		/* Set UHS mode in controller */
		CtrlReg = XSdPs_ReadReg16(InstancePtr->Config.BaseAddress,
				XSDPS_HOST_CTRL2_OFFSET);
		CtrlReg &= (u16)(~XSDPS_HC2_UHS_MODE_MASK);
		XSdPs_WriteReg16(InstancePtr->Config.BaseAddress,
						XSDPS_HOST_CTRL2_OFFSET,
						CtrlReg | InstancePtr->Mode);
	}

	Status = XST_SUCCESS;

RETURN_PATH:
	return Status;
}

/*****************************************************************************/
/**
* @brief
* This function is used to change the eMMC bus speed.
*
* @param	InstancePtr is a pointer to the instance to be worked on.
*
* @return	None
*
******************************************************************************/
s32 XSdPs_Change_MmcBusSpeed(XSdPs *InstancePtr)
{
	s32 Status;
	u32 Arg;

	Status = XSdPs_CalcBusSpeed(InstancePtr, &Arg);
	if (Status != XST_SUCCESS) {
		Status = XST_FAILURE;
		goto RETURN_PATH;
	}

	Status = XSdPs_CmdTransfer(InstancePtr, CMD6, Arg, 0U);
	if (Status != XST_SUCCESS) {
		Status = XST_FAILURE;
		goto RETURN_PATH;
	}

	/* Check for transfer done */
	Status = XSdps_CheckTransferDone(InstancePtr);
	if (Status != XST_SUCCESS) {
		Status = XST_FAILURE;
	}

	Status = XST_SUCCESS;

RETURN_PATH:
	return Status;
}

/*****************************************************************************/
/**
* @brief
* This function is used to do the Auto tuning.
*
* @param	InstancePtr is a pointer to the instance to be worked on.
*
* @return	None
*
******************************************************************************/
s32 XSdPs_AutoTuning(XSdPs *InstancePtr)
{
	s32 Status;
	u16 BlkSize;
	u8 TuningCount;

	BlkSize = XSDPS_TUNING_CMD_BLKSIZE;
	if(InstancePtr->BusWidth == XSDPS_8_BIT_WIDTH)
	{
		BlkSize = BlkSize*2U;
	}
	BlkSize &= XSDPS_BLK_SIZE_MASK;
	XSdPs_WriteReg16(InstancePtr->Config.BaseAddress, XSDPS_BLK_SIZE_OFFSET,
			BlkSize);

	InstancePtr->TransferMode = XSDPS_TM_DAT_DIR_SEL_MASK;

	XSdPs_SetExecTuning(InstancePtr);
	/*
	 * workaround which can work for 1.0/2.0 silicon for auto tuning.
	 * This can be revisited for 3.0 silicon if necessary.
	 */
	/* Wait for ~60 clock cycles to reset the tap values */
	(void)usleep(1U);

	for (TuningCount = 0U; TuningCount < MAX_TUNING_COUNT; TuningCount++) {

		if (InstancePtr->CardType == XSDPS_CARD_SD) {
			Status = XSdPs_CmdTransfer(InstancePtr, CMD19, 0U, 1U);
		} else {
			Status = XSdPs_CmdTransfer(InstancePtr, CMD21, 0U, 1U);
		}

		if (Status != XST_SUCCESS) {
			Status = XST_FAILURE;
			goto RETURN_PATH;
		}

		if ((XSdPs_ReadReg16(InstancePtr->Config.BaseAddress,
				XSDPS_HOST_CTRL2_OFFSET) & XSDPS_HC2_EXEC_TNG_MASK) == 0U) {
			break;
		}
	}

	if ((XSdPs_ReadReg16(InstancePtr->Config.BaseAddress,
			XSDPS_HOST_CTRL2_OFFSET) & XSDPS_HC2_SAMP_CLK_SEL_MASK) == 0U) {
		Status = XST_FAILURE;
		goto RETURN_PATH;
	}

	/* Wait for ~12 clock cycles to synchronize the new tap values */
	(void)usleep(1U);

	Status = XST_SUCCESS;

RETURN_PATH:
	return Status;
}

/*****************************************************************************/
/**
*
* @brief
* API to setup ADMA2 descriptor table
*
*
* @param	InstancePtr is a pointer to the XSdPs instance.
* @param	BlkCnt - block count.
* @param	Buff pointer to data buffer.
*
* @return	None
*
* @note		None.
*
******************************************************************************/
void XSdPs_SetupADMA2DescTbl(XSdPs *InstancePtr, u32 BlkCnt, const u8 *Buff)
{
	if (InstancePtr->HC_Version == XSDPS_HC_SPEC_V3) {
		XSdPs_Setup64ADMA2DescTbl(InstancePtr, BlkCnt, Buff);
	} else {
		XSdPs_Setup32ADMA2DescTbl(InstancePtr, BlkCnt, Buff);
	}
}

/*****************************************************************************/
/**
*
* @brief
* API to setup ADMA2 descriptor table for 64 Bit DMA
*
*
* @param	InstancePtr is a pointer to the XSdPs instance.
* @param	BlkCnt - block count.
*
* @return	None
*
* @note		None.
*
******************************************************************************/
void XSdPs_SetupADMA2DescTbl64Bit(XSdPs *InstancePtr, u32 BlkCnt)
{
#ifdef __ICCARM__
#pragma data_alignment = 32
	static XSdPs_Adma2Descriptor64 Adma2_DescrTbl[32];
#else
	static XSdPs_Adma2Descriptor64 Adma2_DescrTbl[32] __attribute__ ((aligned(32)));
#endif
	u32 TotalDescLines;
	u64 DescNum;
	u32 BlkSize;

	/* Setup ADMA2 - Write descriptor table and point ADMA SAR to it */
	BlkSize = (u32)XSdPs_ReadReg16(InstancePtr->Config.BaseAddress,
					XSDPS_BLK_SIZE_OFFSET) &
					XSDPS_BLK_SIZE_MASK;

	if((BlkCnt*BlkSize) < XSDPS_DESC_MAX_LENGTH) {

		TotalDescLines = 1U;

	} else {

		TotalDescLines = ((BlkCnt*BlkSize) / XSDPS_DESC_MAX_LENGTH);
		if (((BlkCnt * BlkSize) % XSDPS_DESC_MAX_LENGTH) != 0U) {
			TotalDescLines += 1U;
		}

	}

	for (DescNum = 0U; DescNum < (TotalDescLines-1); DescNum++) {
		Adma2_DescrTbl[DescNum].Address =
				InstancePtr->Dma64BitAddr +
				(DescNum*XSDPS_DESC_MAX_LENGTH);
		Adma2_DescrTbl[DescNum].Attribute =
				XSDPS_DESC_TRAN | XSDPS_DESC_VALID;
		Adma2_DescrTbl[DescNum].Length = 0U;
	}

	Adma2_DescrTbl[TotalDescLines-1].Address =
				InstancePtr->Dma64BitAddr +
				(DescNum*XSDPS_DESC_MAX_LENGTH);

	Adma2_DescrTbl[TotalDescLines-1].Attribute =
			XSDPS_DESC_TRAN | XSDPS_DESC_END | XSDPS_DESC_VALID;

	Adma2_DescrTbl[TotalDescLines-1].Length =
			(u16)((BlkCnt*BlkSize) - (u32)(DescNum*XSDPS_DESC_MAX_LENGTH));

	XSdPs_WriteReg(InstancePtr->Config.BaseAddress, XSDPS_ADMA_SAR_OFFSET,
			(u32)((UINTPTR)&(Adma2_DescrTbl[0]) & (u32)~0x0));

	if (InstancePtr->Config.IsCacheCoherent == 0U) {
		Xil_DCacheFlushRange((INTPTR)&(Adma2_DescrTbl[0]),
			sizeof(XSdPs_Adma2Descriptor64) * 32U);
	}

	/* Clear the 64-Bit Address variable */
	InstancePtr->Dma64BitAddr = 0U;

}

/*****************************************************************************/
/**
*
* @brief
* API to reset the DLL
*
*
* @param	InstancePtr is a pointer to the XSdPs instance.
*
* @return	None
*
* @note		None.
*
******************************************************************************/
s32 XSdPs_DllReset(XSdPs *InstancePtr)
{
	u32 ClockReg;
	s32 Status;

	/* Disable clock */
	ClockReg = XSdPs_ReadReg16(InstancePtr->Config.BaseAddress,
			XSDPS_CLK_CTRL_OFFSET);
	ClockReg &= ~XSDPS_CC_SD_CLK_EN_MASK;
	XSdPs_WriteReg16(InstancePtr->Config.BaseAddress,
			XSDPS_CLK_CTRL_OFFSET, (u16)ClockReg);

	/* Issue DLL Reset to load zero tap values */
	XSdPs_DllRstCtrl(InstancePtr, 1U);

	/* Wait for 2 micro seconds */
	(void)usleep(2U);

	XSdPs_DllRstCtrl(InstancePtr, 0U);

	ClockReg = XSdPs_ReadReg16(InstancePtr->Config.BaseAddress,
				XSDPS_CLK_CTRL_OFFSET);
	/* Enable the clock in the controller */
	Status = XSdPs_EnableClock(InstancePtr, ClockReg);
	if (Status != XST_SUCCESS) {
		Status = XST_FAILURE;
	}

	return Status;
}

/*****************************************************************************/
/**
* @brief
* This function is used to identify the eMMC speed mode.
*
* @param	InstancePtr is a pointer to the instance to be worked on.
* @param	ExtCsd is the extended CSD register from the card
*
* @return	None
*
******************************************************************************/
void XSdPs_IdentifyEmmcMode(XSdPs *InstancePtr, const u8 *ExtCsd)
{
	if (InstancePtr->BusWidth < XSDPS_4_BIT_WIDTH) {
		InstancePtr->Mode = XSDPS_DEFAULT_SPEED_MODE;
	} else {
		/* Check for card supported speed */
		if ((ExtCsd[EXT_CSD_DEVICE_TYPE_BYTE] &
				(EXT_CSD_DEVICE_TYPE_SDR_1V8_HS200 |
				EXT_CSD_DEVICE_TYPE_SDR_1V2_HS200)) != 0U) {
			InstancePtr->Mode = XSDPS_HS200_MODE;
			if (InstancePtr->Config.BankNumber == 2U) {
				InstancePtr->OTapDelay = SD_OTAPDLYSEL_HS200_B2;
			} else {
				InstancePtr->OTapDelay = SD_OTAPDLYSEL_HS200_B0;
			}
		} else if ((ExtCsd[EXT_CSD_DEVICE_TYPE_BYTE] &
				(EXT_CSD_DEVICE_TYPE_DDR_1V8_HIGH_SPEED |
				EXT_CSD_DEVICE_TYPE_DDR_1V2_HIGH_SPEED)) != 0U) {
			InstancePtr->Mode = XSDPS_DDR52_MODE;
			InstancePtr->OTapDelay = SD_ITAPDLYSEL_EMMC_DDR50;
			InstancePtr->ITapDelay = SD_ITAPDLYSEL_EMMC_DDR50;
		} else if ((ExtCsd[EXT_CSD_DEVICE_TYPE_BYTE] &
				EXT_CSD_DEVICE_TYPE_HIGH_SPEED) != 0U) {
			InstancePtr->Mode = XSDPS_HIGH_SPEED_MODE;
			InstancePtr->OTapDelay = SD_OTAPDLYSEL_EMMC_HSD;
			InstancePtr->ITapDelay = SD_ITAPDLYSEL_HSD;
		} else {
			InstancePtr->Mode = XSDPS_DEFAULT_SPEED_MODE;
		}
	}
}

/*****************************************************************************/
/**
* @brief
* This function is used to check the eMMC timing.
*
* @param	InstancePtr is a pointer to the instance to be worked on.
* @param	ExtCsd is the extended CSD register from the card
*
* @return	None
*
******************************************************************************/
s32 XSdPs_CheckEmmcTiming(XSdPs *InstancePtr, u8 *ExtCsd)
{
	s32 Status;

	Status = XSdPs_Get_Mmc_ExtCsd(InstancePtr, ExtCsd);
	if (Status != XST_SUCCESS) {
		Status = XST_FAILURE;
		goto RETURN_PATH;
	}

	if (InstancePtr->Mode == XSDPS_HS200_MODE) {
		if (ExtCsd[EXT_CSD_HS_TIMING_BYTE] != EXT_CSD_HS_TIMING_HS200) {
			Status = XST_FAILURE;
			goto RETURN_PATH;
		}
	} else if ((InstancePtr->Mode == XSDPS_HIGH_SPEED_MODE) ||
			(InstancePtr->Mode == XSDPS_DDR52_MODE)) {
		if (ExtCsd[EXT_CSD_HS_TIMING_BYTE] != EXT_CSD_HS_TIMING_HIGH) {
			Status = XST_FAILURE;
			goto RETURN_PATH;
		}
	} else {
		Status = XST_FAILURE;
	}

RETURN_PATH:
	return Status;
}

/*****************************************************************************/
/**
* @brief
* This function is used to set the clock to the passed frequency.
*
* @param	InstancePtr is a pointer to the instance to be worked on.
* @param	SelFreq is the selected frequency
*
* @return	None
*
******************************************************************************/
s32 XSdPs_SetClock(XSdPs *InstancePtr, u32 SelFreq)
{
	u16 ClockReg;
	s32 Status;

	/* Disable clock */
	XSdPs_WriteReg16(InstancePtr->Config.BaseAddress,
			XSDPS_CLK_CTRL_OFFSET, 0U);

	/* If selected frequency is zero, return from here */
	if (SelFreq == 0U) {
		Status = XST_SUCCESS;
		goto RETURN_PATH ;
	}

	/* Calculate the clock */
	ClockReg = XSdPs_CalcClock(InstancePtr, SelFreq);

	/* Enable the clock in the controller */
	Status = XSdPs_EnableClock(InstancePtr, ClockReg);
	if (Status != XST_SUCCESS) {
		Status = XST_FAILURE;
	}

RETURN_PATH:
	return Status;
}

/*****************************************************************************/
/**
* @brief
* This function checks if the voltage is set to 1.8V or not.
*
* @param	InstancePtr is a pointer to the instance to be worked on.
*
* @return
* 		- XST_SUCCESS if voltage is 1.8V
* 		- XST_FAILURE if voltage is not 1.8V
*
******************************************************************************/
s32 XSdPs_CheckVoltage18(XSdPs *InstancePtr)
{
	u32 Status;

	if ((XSdPs_ReadReg16(InstancePtr->Config.BaseAddress,
			XSDPS_HOST_CTRL2_OFFSET) & XSDPS_HC2_1V8_EN_MASK) == 0U) {
		Status = XST_FAILURE;
		goto RETURN_PATH;
	}

	Status = XST_SUCCESS;

RETURN_PATH:
	return Status;
}

/*****************************************************************************/
/**
* @brief
* This function initializes the command sequence.
*
* @param	InstancePtr is a pointer to the instance to be worked on.
* @param	Arg is the address passed by the user that is to be sent as
* 		argument along with the command.
* @param	BlkCnt - Block count passed by the user.
*
* @return	None
*
******************************************************************************/
s32 XSdPs_SetupCmd(XSdPs *InstancePtr, u32 Arg, u32 BlkCnt)
{
	s32 Status;

	/*
	 * Check the command inhibit to make sure no other
	 * command transfer is in progress
	 */
	Status = XSdPs_CheckBusIdle(InstancePtr, XSDPS_PSR_INHIBIT_CMD_MASK);
	if (Status != XST_SUCCESS) {
		Status = XST_FAILURE;
		goto RETURN_PATH ;
	}

	/* Write block count register */
	XSdPs_WriteReg16(InstancePtr->Config.BaseAddress,
			XSDPS_BLK_CNT_OFFSET, (u16)BlkCnt);

	XSdPs_WriteReg8(InstancePtr->Config.BaseAddress,
			XSDPS_TIMEOUT_CTRL_OFFSET, 0xEU);

	/* Write argument register */
	XSdPs_WriteReg(InstancePtr->Config.BaseAddress,
			XSDPS_ARGMT_OFFSET, Arg);

	XSdPs_WriteReg16(InstancePtr->Config.BaseAddress,
			XSDPS_NORM_INTR_STS_OFFSET, XSDPS_NORM_INTR_ALL_MASK);
	XSdPs_WriteReg16(InstancePtr->Config.BaseAddress,
			XSDPS_ERR_INTR_STS_OFFSET, XSDPS_ERROR_INTR_ALL_MASK);

	Status = XST_SUCCESS;

RETURN_PATH:
	return Status;
}

/*****************************************************************************/
/**
* @brief
* This function initiates the Cmd transfer to SD card.
*
* @param	InstancePtr is a pointer to the instance to be worked on.
* @param	Cmd is the command to be sent
*
* @return
* 		- XST_SUCCESS if initialization was successful
* 		- XST_FAILURE if failure
*
******************************************************************************/
s32 XSdPs_SendCmd(XSdPs *InstancePtr, u32 Cmd)
{
	u32 PresentStateReg;
	u32 CommandReg;
	s32 Status;

	/* Command register is set to trigger transfer of command */
	CommandReg = XSdPs_FrameCmd(InstancePtr, Cmd);

	/*
	 * Mask to avoid writing to reserved bits 31-30
	 * This is necessary because 0x8000 is used  by this software to
	 * distinguish between ACMD and CMD of same number
	 */
	CommandReg = CommandReg & 0x3FFFU;

	/*
	 * Check for data inhibit in case of command using DAT lines.
	 * For Tuning Commands DAT lines check can be ignored.
	 */
	if ((Cmd != CMD21) && (Cmd != CMD19)) {
		PresentStateReg = XSdPs_ReadReg(InstancePtr->Config.BaseAddress,
				XSDPS_PRES_STATE_OFFSET);
		if (((PresentStateReg & XSDPS_PSR_INHIBIT_DAT_MASK) != 0U) &&
				((CommandReg & XSDPS_DAT_PRESENT_SEL_MASK) != 0U)) {
			Status = XST_FAILURE;
			goto RETURN_PATH;
		}
	}

	XSdPs_WriteReg(InstancePtr->Config.BaseAddress, XSDPS_XFER_MODE_OFFSET,
			(CommandReg << 16) | InstancePtr->TransferMode);

	Status = XST_SUCCESS;

RETURN_PATH:
	return Status;

}

/** @} */
