/******************************************************************************
* Copyright (C) 2013 - 2020 Xilinx, Inc.  All rights reserved.
* SPDX-License-Identifier: MIT
******************************************************************************/

/*****************************************************************************/
/**
*
* @file xsdps_options.c
* @addtogroup sdps_v3_9
* @{
*
* Contains API's for changing the various options in host and card.
* See xsdps.h for a detailed description of the device and driver.
*
* <pre>
* MODIFICATION HISTORY:
*
* Ver   Who    Date     Changes
* ----- ---    -------- -----------------------------------------------
* 1.00a hk/sg  10/17/13 Initial release
* 2.1   hk     04/18/14 Increase sleep for eMMC switch command.
*                       Add sleep for microblaze designs. CR# 781117.
* 2.3   sk     09/23/14 Use XSdPs_Change_ClkFreq API whenever changing
*						clock.CR# 816586.
* 2.5 	sg	   07/09/15 Added SD 3.0 features
*       kvn    07/15/15 Modified the code according to MISRAC-2012.
* 2.7   sk     01/08/16 Added workaround for issue in auto tuning mode
*                       of SDR50, SDR104 and HS200.
*       sk     02/16/16 Corrected the Tuning logic.
*       sk     03/02/16 Configured the Tap Delay values for eMMC HS200 mode.
* 2.8   sk     04/20/16 Added new workaround for auto tuning.
* 3.0   sk     07/07/16 Used usleep API for both arm and microblaze.
*       sk     07/16/16 Added support for UHS modes.
*       sk     07/16/16 Added Tap delays accordingly to different SD/eMMC
*                       operating modes.
* 3.1   mi     09/07/16 Removed compilation warnings with extra compiler flags.
*       sk     11/07/16 Enable Rst_n bit in ext_csd reg if not enabled.
*       sk     11/16/16 Issue DLL reset at 31 iteration to load new zero value.
* 3.2   sk     02/01/17 Added HSD and DDR mode support for eMMC.
*       sk     02/01/17 Consider bus width parameter from design for switching
*       vns    02/09/17 Added ARMA53_32 support for ZynqMP CR#968397
*       vns    03/13/17 Fixed MISRAC mandatory violation
*       sk     03/20/17 Add support for EL1 non-secure mode.
* 3.3   mn     07/25/17 Removed SD0_OTAPDLYENA and SD1_OTAPDLYENA bits
*       mn     08/07/17	Properly set OTAPDLY value by clearing previous bit
* 			settings
*       mn     08/17/17 Added CCI support for A53 and disabled data cache
*                       operations when it is enabled.
*       mn     08/22/17 Updated for Word Access System support
* 3.4   mn     01/22/18 Separated out SDR104 and HS200 clock defines
* 3.6   mn     07/06/18 Fix Cppcheck warnings for sdps driver
* 3.7   aru    03/12/19 Modified the code according to MISRAC-2012.
*       mn     03/27/19 Disable calls to dll_reset API for versal SPP Platforms
* 3.8   mn     04/12/19 Modified TapDelay code for supporting ZynqMP and Versal
*       mn     05/21/19 Set correct tap delays for Versal
*       mn     05/21/19 Disable DLL Reset code for Versal
*       mn     08/29/19 Add call to Cache Invalidation API in XSdPs_Get_BusWidth
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
*
* @brief
* API to change clock freq to given value.
*
*
* @param	InstancePtr is a pointer to the XSdPs instance.
* @param	SelFreq - Clock frequency in Hz.
*
* @return	None
*
* @note		This API will change clock frequency to the value less than
*		or equal to the given value using the permissible dividors.
*
******************************************************************************/
s32 XSdPs_Change_ClkFreq(XSdPs *InstancePtr, u32 SelFreq)
{
	s32 Status;

	Xil_AssertNonvoid(InstancePtr != NULL);
	Xil_AssertNonvoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

	if (InstancePtr->HC_Version == XSDPS_HC_SPEC_V3) {
		/* Program the Tap delays */
		XSdPs_SetTapDelay(InstancePtr);
	}

	Status = XSdPs_SetClock(InstancePtr, SelFreq);
	if (Status != XST_SUCCESS) {
		Status = XST_FAILURE;
	}

	return Status;
}

/*****************************************************************************/
/**
* @brief
* Update Block size for read/write operations.
*
* @param	InstancePtr is a pointer to the instance to be worked on.
* @param	BlkSize - Block size passed by the user.
*
* @return	None
*
******************************************************************************/
s32 XSdPs_SetBlkSize(XSdPs *InstancePtr, u16 BlkSize)
{
	s32 Status;

	Xil_AssertNonvoid(InstancePtr != NULL);
	Xil_AssertNonvoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

	Status = XSdPs_CheckBusIdle(InstancePtr, (XSDPS_PSR_INHIBIT_CMD_MASK
											| XSDPS_PSR_INHIBIT_DAT_MASK
											| XSDPS_PSR_WR_ACTIVE_MASK
											| XSDPS_PSR_RD_ACTIVE_MASK));
	if (Status != XST_SUCCESS) {
		Status = XST_FAILURE;
		goto RETURN_PATH ;
	}

	/* Send block write command */
	Status = XSdPs_CmdTransfer(InstancePtr, CMD16, BlkSize, 0U);
	if (Status != XST_SUCCESS) {
		Status = XST_FAILURE;
		goto RETURN_PATH;
	}

	/* Set block size to the value passed */
	XSdPs_WriteReg16(InstancePtr->Config.BaseAddress, XSDPS_BLK_SIZE_OFFSET,
			 BlkSize & XSDPS_BLK_SIZE_MASK);

RETURN_PATH:
	return Status;
}

/*****************************************************************************/
/**
*
* @brief
* API to get bus width support by card.
*
*
* @param	InstancePtr is a pointer to the XSdPs instance.
* @param	SCR - buffer to store SCR register returned by card.
*
* @return
*		- XST_SUCCESS if successful.
*		- XST_FAILURE if fail.
*
* @note		None.
*
******************************************************************************/
s32 XSdPs_Get_BusWidth(XSdPs *InstancePtr, u8 *ReadBuff)
{
	s32 Status;
	u16 BlkCnt;
	u16 BlkSize;
	s32 LoopCnt;

	Xil_AssertNonvoid(InstancePtr != NULL);
	Xil_AssertNonvoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

	for (LoopCnt = 0; LoopCnt < 8; LoopCnt++) {
		ReadBuff[LoopCnt] = 0U;
	}

	/* Send block write command */
	Status = XSdPs_CmdTransfer(InstancePtr, CMD55,
			InstancePtr->RelCardAddr, 0U);
	if (Status != XST_SUCCESS) {
		Status = XST_FAILURE;
		goto RETURN_PATH;
	}

	BlkCnt = XSDPS_SCR_BLKCNT;
	BlkSize = XSDPS_SCR_BLKSIZE;

	XSdPs_SetupReadDma(InstancePtr, BlkCnt, BlkSize, ReadBuff);

	Status = XSdPs_CmdTransfer(InstancePtr, ACMD51, 0U, BlkCnt);
	if (Status != XST_SUCCESS) {
		Status = XST_FAILURE;
		goto RETURN_PATH;
	}

	/* Check for transfer done */
	Status = XSdps_CheckTransferDone(InstancePtr);
	if (Status != XST_SUCCESS) {
		Status = XST_FAILURE;
	}

	if (InstancePtr->Config.IsCacheCoherent == 0U) {
		Xil_DCacheInvalidateRange((INTPTR)ReadBuff,
				(INTPTR)BlkCnt * BlkSize);
	}

	Status = XST_SUCCESS;

	RETURN_PATH:
		return Status;

}

/*****************************************************************************/
/**
*
* @brief
* API to set bus width to 4-bit in card and host
*
*
* @param	InstancePtr is a pointer to the XSdPs instance.
*
* @return
*		- XST_SUCCESS if successful.
*		- XST_FAILURE if fail.
*
* @note		None.
*
******************************************************************************/
s32 XSdPs_Change_BusWidth(XSdPs *InstancePtr)
{
	s32 Status;
	u32 StatusReg;
	u32 Arg;

	Xil_AssertNonvoid(InstancePtr != NULL);
	Xil_AssertNonvoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

	/*
	 * check for bus width for 3.0 controller and return if
	 * bus width is <4
	 */
	if ((InstancePtr->HC_Version == XSDPS_HC_SPEC_V3) &&
			(InstancePtr->Config.BusWidth < XSDPS_WIDTH_4)) {
		Status = XST_SUCCESS;
		goto RETURN_PATH;
	}

	if (InstancePtr->CardType == XSDPS_CARD_SD) {

		Status = XSdPs_CmdTransfer(InstancePtr, CMD55, InstancePtr->RelCardAddr,
				0U);
		if (Status != XST_SUCCESS) {
			Status = XST_FAILURE;
			goto RETURN_PATH;
		}

		Status = XSdPs_CmdTransfer(InstancePtr, ACMD6, (u32)InstancePtr->BusWidth, 0U);
		if (Status != XST_SUCCESS) {
			Status = XST_FAILURE;
			goto RETURN_PATH;
		}
	} else {
		if (InstancePtr->BusWidth == XSDPS_8_BIT_WIDTH) {
			if (InstancePtr->Mode == XSDPS_DDR52_MODE) {
				Arg = XSDPS_MMC_DDR_8_BIT_BUS_ARG;
			} else {
				Arg = XSDPS_MMC_8_BIT_BUS_ARG;
			}
		} else {
			if (InstancePtr->Mode == XSDPS_DDR52_MODE) {
				Arg = XSDPS_MMC_DDR_4_BIT_BUS_ARG;
			} else {
				Arg = XSDPS_MMC_4_BIT_BUS_ARG;
			}
		}

		Status = XSdPs_Set_Mmc_ExtCsd(InstancePtr, Arg);
		if (Status != XST_SUCCESS) {
			Status = XST_FAILURE;
			goto RETURN_PATH;
		}
	}

	usleep(XSDPS_MMC_DELAY_FOR_SWITCH);

	StatusReg = XSdPs_ReadReg8(InstancePtr->Config.BaseAddress,
					XSDPS_HOST_CTRL1_OFFSET);

	/* Width setting in controller */
	if (InstancePtr->BusWidth == XSDPS_8_BIT_WIDTH) {
		StatusReg |= XSDPS_HC_EXT_BUS_WIDTH;
	} else {
		StatusReg |= XSDPS_HC_WIDTH_MASK;
	}

	XSdPs_WriteReg8(InstancePtr->Config.BaseAddress,
			XSDPS_HOST_CTRL1_OFFSET,
			(u8)StatusReg);

	if (InstancePtr->Mode == XSDPS_DDR52_MODE) {
		StatusReg = XSdPs_ReadReg16(InstancePtr->Config.BaseAddress,
					XSDPS_HOST_CTRL2_OFFSET);
		StatusReg &= (u32)(~XSDPS_HC2_UHS_MODE_MASK);
		StatusReg |= InstancePtr->Mode;
		XSdPs_WriteReg16(InstancePtr->Config.BaseAddress,
					XSDPS_HOST_CTRL2_OFFSET, (u16)StatusReg);
	}

	Status = XST_SUCCESS;

	RETURN_PATH:
		return Status;

}

/*****************************************************************************/
/**
*
* @brief
* API to get bus speed supported by card.
*
*
* @param	InstancePtr is a pointer to the XSdPs instance.
* @param	ReadBuff - buffer to store function group support data
*		returned by card.
*
* @return
*		- XST_SUCCESS if successful.
*		- XST_FAILURE if fail.
*
* @note		None.
*
******************************************************************************/
s32 XSdPs_Get_BusSpeed(XSdPs *InstancePtr, u8 *ReadBuff)
{
	s32 Status;
	u32 Arg;
	u16 BlkCnt;
	u16 BlkSize;
	s32 LoopCnt;

	Xil_AssertNonvoid(InstancePtr != NULL);
	Xil_AssertNonvoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

	for (LoopCnt = 0; LoopCnt < 64; LoopCnt++) {
		ReadBuff[LoopCnt] = 0U;
	}

	BlkCnt = XSDPS_SWITCH_CMD_BLKCNT;
	BlkSize = XSDPS_SWITCH_CMD_BLKSIZE;

	XSdPs_SetupReadDma(InstancePtr, BlkCnt, BlkSize, ReadBuff);

	Arg = XSDPS_SWITCH_CMD_HS_GET;

	Status = XSdPs_CmdTransfer(InstancePtr, CMD6, Arg, 1U);
	if (Status != XST_SUCCESS) {
		Status = XST_FAILURE;
		goto RETURN_PATH;
	}

	/* Check for transfer done */
	Status = XSdps_CheckTransferDone(InstancePtr);
	if (Status != XST_SUCCESS) {
		Status = XST_FAILURE;
	}

	if (InstancePtr->Config.IsCacheCoherent == 0U) {
		Xil_DCacheInvalidateRange((INTPTR)ReadBuff,
				(INTPTR)BlkCnt * BlkSize);
	}

	Status = XST_SUCCESS;

	RETURN_PATH:
		return Status;

}

/*****************************************************************************/
/**
*
* @brief
* API to get SD card status information.
*
*
* @param	InstancePtr is a pointer to the XSdPs instance.
* @param	SdStatReg - buffer to store status data returned by card.
*
* @return
*		- XST_SUCCESS if successful.
*		- XST_FAILURE if fail.
*
* @note		None.
*
******************************************************************************/
s32 XSdPs_Get_Status(XSdPs *InstancePtr, u8 *SdStatReg)
{
	s32 Status;
	u16 BlkCnt;
	u16 BlkSize;

	Xil_AssertNonvoid(InstancePtr != NULL);
	Xil_AssertNonvoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

	/* Send block write command */
	Status = XSdPs_CmdTransfer(InstancePtr, CMD55,
			InstancePtr->RelCardAddr, 0U);
	if (Status != XST_SUCCESS) {
		Status = XST_FAILURE;
		goto RETURN_PATH;
	}

	BlkCnt = XSDPS_SD_STATUS_BLKCNT;
	BlkSize = XSDPS_SD_STATUS_BLKSIZE;

	XSdPs_SetupReadDma(InstancePtr, BlkCnt, BlkSize, SdStatReg);

	Status = XSdPs_CmdTransfer(InstancePtr, ACMD13, 0U, BlkCnt);
	if (Status != XST_SUCCESS) {
		Status = XST_FAILURE;
		goto RETURN_PATH;
	}

	/* Check for transfer done */
	Status = XSdps_CheckTransferDone(InstancePtr);
	if (Status != XST_SUCCESS) {
		Status = XST_FAILURE;
	}

	if (InstancePtr->Config.IsCacheCoherent == 0U) {
		Xil_DCacheInvalidateRange((INTPTR)SdStatReg,
				(INTPTR)BlkCnt * BlkSize);
	}

	Status = XST_SUCCESS;

	RETURN_PATH:
		return Status;
}

/*****************************************************************************/
/**
*
* @brief
* API to set high speed in card and host. Changes clock in host accordingly.
*
*
* @param	InstancePtr is a pointer to the XSdPs instance.
*
* @return
*		- XST_SUCCESS if successful.
*		- XST_FAILURE if fail.
*
* @note		None.
*
******************************************************************************/
s32 XSdPs_Change_BusSpeed(XSdPs *InstancePtr)
{
	s32 Status;
	u32 StatusReg;

	Xil_AssertNonvoid(InstancePtr != NULL);
	Xil_AssertNonvoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

	if (InstancePtr->CardType == XSDPS_CARD_SD) {
		Status = XSdPs_Change_SdBusSpeed(InstancePtr);
		if (Status != XST_SUCCESS) {
			Status = XST_FAILURE;
			goto RETURN_PATH;
		}
	} else {
		Status = XSdPs_Change_MmcBusSpeed(InstancePtr);
		if (Status != XST_SUCCESS) {
			Status = XST_FAILURE;
			goto RETURN_PATH;
		}
	}

	Status = XSdPs_Change_ClkFreq(InstancePtr, InstancePtr->BusSpeed);
	if (Status != XST_SUCCESS) {
		Status = XST_FAILURE;
		goto RETURN_PATH;
	}

	if ((InstancePtr->Mode == XSDPS_HS200_MODE) ||
		(InstancePtr->Mode == XSDPS_UHS_SPEED_MODE_SDR104) ||
		(InstancePtr->Mode == XSDPS_UHS_SPEED_MODE_SDR50)) {
		Status = XSdPs_Execute_Tuning(InstancePtr);
		if (Status != XST_SUCCESS) {
			Status = XST_FAILURE;
			goto RETURN_PATH;
		}
	}

	usleep(XSDPS_MMC_DELAY_FOR_SWITCH);

	StatusReg = (u32)XSdPs_ReadReg8(InstancePtr->Config.BaseAddress,
					XSDPS_HOST_CTRL1_OFFSET);
	StatusReg |= XSDPS_HC_SPEED_MASK;
	XSdPs_WriteReg8(InstancePtr->Config.BaseAddress,
			XSDPS_HOST_CTRL1_OFFSET, (u8)StatusReg);

	Status = XST_SUCCESS;

	RETURN_PATH:
		return Status;

}

/*****************************************************************************/
/**
*
* @brief
* API to get EXT_CSD register of eMMC.
*
*
* @param	InstancePtr is a pointer to the XSdPs instance.
* @param	ReadBuff - buffer to store EXT_CSD
*
* @return
*		- XST_SUCCESS if successful.
*		- XST_FAILURE if fail.
*
* @note		None.
*
******************************************************************************/
s32 XSdPs_Get_Mmc_ExtCsd(XSdPs *InstancePtr, u8 *ReadBuff)
{
	s32 Status;
	u32 Arg = 0U;
	u16 BlkCnt;
	u16 BlkSize;
	s32 LoopCnt;

	Xil_AssertNonvoid(InstancePtr != NULL);
	Xil_AssertNonvoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

	for (LoopCnt = 0; LoopCnt < 512; LoopCnt++) {
		ReadBuff[LoopCnt] = 0U;
	}

	BlkCnt = XSDPS_EXT_CSD_CMD_BLKCNT;
	BlkSize = XSDPS_EXT_CSD_CMD_BLKSIZE;

	XSdPs_SetupReadDma(InstancePtr, BlkCnt, BlkSize, ReadBuff);

	/* Send SEND_EXT_CSD command */
	Status = XSdPs_CmdTransfer(InstancePtr, CMD8, Arg, 1U);
	if (Status != XST_SUCCESS) {
		Status = XST_FAILURE;
		goto RETURN_PATH;
	}

	/* Check for transfer done */
	Status = XSdps_CheckTransferDone(InstancePtr);
	if (Status != XST_SUCCESS) {
		Status = XST_FAILURE;
	}

	if (InstancePtr->Config.IsCacheCoherent == 0U) {
		Xil_DCacheInvalidateRange((INTPTR)ReadBuff,
				(INTPTR)BlkCnt * BlkSize);
	}

	Status = XST_SUCCESS;

	RETURN_PATH:
		return Status;

}

/*****************************************************************************/
/**
*
* @brief
* API to write EXT_CSD register of eMMC.
*
*
* @param	InstancePtr is a pointer to the XSdPs instance.
* @param	Arg is the argument to be sent along with the command
*
* @return
*		- XST_SUCCESS if successful.
*		- XST_FAILURE if fail.
*
* @note		None.
*
******************************************************************************/
s32 XSdPs_Set_Mmc_ExtCsd(XSdPs *InstancePtr, u32 Arg)
{
	s32 Status;

	Xil_AssertNonvoid(InstancePtr != NULL);
	Xil_AssertNonvoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

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
*
* @brief
* API to send pullup command to card before using DAT line 3(using 4-bit bus)
*
*
* @param	InstancePtr is a pointer to the XSdPs instance.
*
* @return
*		- XST_SUCCESS if successful.
*		- XST_FAILURE if fail.
*
* @note		None.
*
******************************************************************************/
s32 XSdPs_Pullup(XSdPs *InstancePtr)
{
	s32 Status;

	Xil_AssertNonvoid(InstancePtr != NULL);
	Xil_AssertNonvoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

	Status = XSdPs_CmdTransfer(InstancePtr, CMD55,
			InstancePtr->RelCardAddr, 0U);
	if (Status != XST_SUCCESS) {
		Status = XST_FAILURE;
		goto RETURN_PATH;
	}

	Status = XSdPs_CmdTransfer(InstancePtr, ACMD42, 0U, 0U);
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
*
* @brief
* Selects card and sets default block size
*
*
* @param	InstancePtr is a pointer to the XSdPs instance.
*
* @return
*		- XST_SUCCESS if successful.
*		- XST_FAILURE if fail.
*		- XSDPS_CT_ERROR if Command Transfer fail.
*
* @note		None.
*
******************************************************************************/
s32 XSdPs_Select_Card (XSdPs *InstancePtr)
{
	s32 Status;

	Xil_AssertNonvoid(InstancePtr != NULL);
	Xil_AssertNonvoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

	/* Send CMD7 - Select card */
	Status = XSdPs_CmdTransfer(InstancePtr, CMD7,
			InstancePtr->RelCardAddr, 0U);

	return Status;
}

/** @} */
