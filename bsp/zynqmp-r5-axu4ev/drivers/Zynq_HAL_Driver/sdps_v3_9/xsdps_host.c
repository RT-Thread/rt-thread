/******************************************************************************
* Copyright (C) 2013 - 2020 Xilinx, Inc.  All rights reserved.
* SPDX-License-Identifier: MIT
******************************************************************************/

/*****************************************************************************/
/**
*
* @file xsdps_host.c
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
*       mn     03/16/20 Add code to get card ID for MMC/eMMC
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

#if EL1_NONSECURE && defined (__aarch64__)
void XSdps_Smc(XSdPs *InstancePtr, u32 RegOffset, u32 Mask, u32 Val)
{
    (void)Xil_Smc(MMIO_WRITE_SMC_FID, (u64)(InstancePtr->SlcrBaseAddr +
            RegOffset) | ((u64)Mask << 32),
            (u64)Val, 0, 0, 0, 0, 0);
}
#endif

/*****************************************************************************/
/**
*
* @brief
* Switches the SD card voltage from 3v3 to 1v8
*
*
* @param    InstancePtr is a pointer to the XSdPs instance.
*
******************************************************************************/
s32 XSdPs_Switch_Voltage(XSdPs *InstancePtr)
{
    s32 Status;

    /* Setup the voltage switching sequence */
    Status = XSdPs_SetupVoltageSwitch(InstancePtr);
    if (Status != XST_SUCCESS) {
        Status = XST_FAILURE;
        goto RETURN_PATH;
    }

    /* Set the card voltage to 1.8V */
    Status = XSdPs_CardSetVoltage18(InstancePtr);
    if (Status != XST_SUCCESS) {
        Status = XST_FAILURE;
        goto RETURN_PATH;
    }

    /* Check if the bus is high */
    Status = XSdPs_CheckBusHigh(InstancePtr);
    if (Status != XST_SUCCESS) {
        Status = XST_FAILURE;
    }

RETURN_PATH:
    return Status;
}

/*****************************************************************************/
/**
* @brief
* This function initiates the transfer to or from SD card.
*
* @param    InstancePtr is a pointer to the instance to be worked on.
*
* @return
*         - XST_SUCCESS if initialization was successful
*         - XST_FAILURE if failure
*
******************************************************************************/
s32 XSdPs_SetupTransfer(XSdPs *InstancePtr)
{
    u32 PresentStateReg;
    s32 Status;

    if ((InstancePtr->HC_Version != XSDPS_HC_SPEC_V3) ||
                ((InstancePtr->Host_Caps & XSDPS_CAPS_SLOT_TYPE_MASK)
                != XSDPS_CAPS_EMB_SLOT)) {
        if(InstancePtr->Config.CardDetect != 0U) {
            /* Check status to ensure card is initialized */
            PresentStateReg = XSdPs_ReadReg(InstancePtr->Config.BaseAddress,
                    XSDPS_PRES_STATE_OFFSET);
            if ((PresentStateReg & XSDPS_PSR_CARD_INSRT_MASK) == 0x0U) {
                Status = XST_FAILURE;
                goto RETURN_PATH;
            }
        }
    }

    /* Set block size to 512 if not already set */
    if(XSdPs_ReadReg(InstancePtr->Config.BaseAddress,
            XSDPS_BLK_SIZE_OFFSET) != XSDPS_BLK_SIZE_512_MASK ) {
        Status = XSdPs_SetBlkSize(InstancePtr,
            XSDPS_BLK_SIZE_512_MASK);
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
* This function resets the SD card.
*
* @param    InstancePtr is a pointer to the instance to be worked on.
* @param    Value is the type of reset
*
* @return
*         - XST_SUCCESS if initialization was successful
*         - XST_FAILURE if failure
*
******************************************************************************/
s32 XSdPs_Reset(XSdPs *InstancePtr, u8 Value)
{
    s32 Status;

    /* "Software reset for all" is initiated */
    XSdPs_WriteReg8(InstancePtr->Config.BaseAddress, XSDPS_SW_RST_OFFSET,
            Value);

    Status = XSdPs_CheckResetDone(InstancePtr, Value);
    if (Status != XST_SUCCESS) {
        Status = XST_FAILURE;
        goto RETURN_PATH ;
    }

    RETURN_PATH:
        return Status;
}

/*****************************************************************************/
/**
* @brief
* This function sets bit to start execution of tuning.
*
* @param    InstancePtr is a pointer to the instance to be worked on.
*
* @return    None
*
******************************************************************************/
void XSdPs_SetExecTuning(XSdPs *InstancePtr)
{
    u16 CtrlReg;

    CtrlReg = XSdPs_ReadReg16(InstancePtr->Config.BaseAddress,
                XSDPS_HOST_CTRL2_OFFSET);
    CtrlReg |= XSDPS_HC2_EXEC_TNG_MASK;
    XSdPs_WriteReg16(InstancePtr->Config.BaseAddress,
                XSDPS_HOST_CTRL2_OFFSET, CtrlReg);
}

/*****************************************************************************/
/**
* @brief
* This function does SD mode initialization.
*
* @param    InstancePtr is a pointer to the instance to be worked on.
*
* @return
*         - XST_SUCCESS if initialization is successful
*         - XST_FAILURE if failure
*
******************************************************************************/
s32 XSdPs_SdModeInit(XSdPs *InstancePtr)
{
    s32 Status;
#ifdef __ICCARM__
#pragma data_alignment = 32
    static u8 SCR[8] = { 0U };
#else
    static u8 SCR[8] __attribute__ ((aligned(32))) = { 0U };
#endif
    u8 ReadBuff[64] = { 0U };

    Status = XSdPs_Get_BusWidth(InstancePtr, SCR);
    if (Status != XST_SUCCESS) {
        Status = XST_FAILURE;
        goto RETURN_PATH;
    }

    if ((SCR[1] & WIDTH_4_BIT_SUPPORT) != 0U) {
        InstancePtr->BusWidth = XSDPS_4_BIT_WIDTH;
        Status = XSdPs_Change_BusWidth(InstancePtr);
        if (Status != XST_SUCCESS) {
            Status = XST_FAILURE;
            goto RETURN_PATH;
        }
    }

    /* Get speed supported by device */
    Status = XSdPs_Get_BusSpeed(InstancePtr, ReadBuff);
    if (Status != XST_SUCCESS) {
        goto RETURN_PATH;
    }

    if (((SCR[2] & SCR_SPEC_VER_3) != 0U) &&
        (ReadBuff[13] >= UHS_SDR50_SUPPORT) &&
        (InstancePtr->Config.BusWidth == XSDPS_WIDTH_8) &&
        (InstancePtr->Switch1v8 == 0U)) {

        InstancePtr->Switch1v8 = 1U;

        Status = XSdPs_CardSetVoltage18(InstancePtr);
        if (Status != XST_SUCCESS) {
            Status = XST_FAILURE;
            goto RETURN_PATH;
        }
    }

    if (InstancePtr->Switch1v8 != 0U) {

        /* Identify the UHS mode supported by card */
        XSdPs_Identify_UhsMode(InstancePtr, ReadBuff);

        Status = XSdPs_Change_BusSpeed(InstancePtr);
        if (Status != XST_SUCCESS) {
            Status = XST_FAILURE;
            goto RETURN_PATH;
        }
    } else {
        /*
         * card supports CMD6 when SD_SPEC field in SCR register
         * indicates that the Physical Layer Specification Version
         * is 1.10 or later. So for SD v1.0 cmd6 is not supported.
         */
        if (SCR[0] != 0U) {
            /* Check for high speed support */
            if (((ReadBuff[13] & HIGH_SPEED_SUPPORT) != 0U) &&
                    (InstancePtr->BusWidth >= XSDPS_4_BIT_WIDTH)) {
                InstancePtr->Mode = XSDPS_HIGH_SPEED_MODE;
                InstancePtr->OTapDelay = SD_OTAPDLYSEL_SD_HSD;
                InstancePtr->ITapDelay = SD_ITAPDLYSEL_HSD;
                Status = XSdPs_Change_BusSpeed(InstancePtr);
                if (Status != XST_SUCCESS) {
                    Status = XST_FAILURE;
                    goto RETURN_PATH;
                }
            }
        }
    }

    Status = XSdPs_SetBlkSize(InstancePtr, XSDPS_BLK_SIZE_512_MASK);
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
* This function does MMC mode initialization.
*
* @param    InstancePtr is a pointer to the instance to be worked on.
*
* @return
*         - XST_SUCCESS if initialization is successful
*         - XST_FAILURE if failure
*
******************************************************************************/
s32 XSdPs_MmcModeInit(XSdPs *InstancePtr)
{
    s32 Status;
#ifdef __ICCARM__
#pragma data_alignment = 32
    static u8 ExtCsd[512];
#else
    static u8 ExtCsd[512] __attribute__ ((aligned(32)));
#endif

    InstancePtr->BusWidth = XSDPS_4_BIT_WIDTH;
    Status = XSdPs_Change_BusWidth(InstancePtr);
    if (Status != XST_SUCCESS) {
        Status = XST_FAILURE;
        goto RETURN_PATH;
    }

    Status = XSdPs_Get_Mmc_ExtCsd(InstancePtr, ExtCsd);
    if (Status != XST_SUCCESS) {
        Status = XST_FAILURE;
        goto RETURN_PATH;
    }

    InstancePtr->SectorCount = ((u32)ExtCsd[EXT_CSD_SEC_COUNT_BYTE4]) << 24;
    InstancePtr->SectorCount |= (u32)ExtCsd[EXT_CSD_SEC_COUNT_BYTE3] << 16;
    InstancePtr->SectorCount |= (u32)ExtCsd[EXT_CSD_SEC_COUNT_BYTE2] << 8;
    InstancePtr->SectorCount |= (u32)ExtCsd[EXT_CSD_SEC_COUNT_BYTE1];

    if (((ExtCsd[EXT_CSD_DEVICE_TYPE_BYTE] &
            EXT_CSD_DEVICE_TYPE_HIGH_SPEED) != 0U) &&
            (InstancePtr->BusWidth >= XSDPS_4_BIT_WIDTH)) {
        InstancePtr->Mode = XSDPS_HIGH_SPEED_MODE;
        Status = XSdPs_Change_BusSpeed(InstancePtr);
        if (Status != XST_SUCCESS) {
            Status = XST_FAILURE;
            goto RETURN_PATH;
        }

        Status = XSdPs_Get_Mmc_ExtCsd(InstancePtr, ExtCsd);
        if (Status != XST_SUCCESS) {
            Status = XST_FAILURE;
            goto RETURN_PATH;
        }

        if (ExtCsd[EXT_CSD_HS_TIMING_BYTE] != EXT_CSD_HS_TIMING_HIGH) {
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
* This function does eMMC mode initialization.
*
* @param    InstancePtr is a pointer to the instance to be worked on.
*
* @return
*         - XST_SUCCESS if initialization is successful
*         - XST_FAILURE if failure
*
******************************************************************************/
s32 XSdPs_EmmcModeInit(XSdPs *InstancePtr)
{
    s32 Status;

#ifdef __ICCARM__
#pragma data_alignment = 32
    static u8 ExtCsd[512];
#else
    static u8 ExtCsd[512] __attribute__ ((aligned(32)));
#endif

    if ((InstancePtr->HC_Version == XSDPS_HC_SPEC_V3) &&
            (InstancePtr->Config.BusWidth == XSDPS_WIDTH_8)) {
        /* in case of eMMC data width 8-bit */
        InstancePtr->BusWidth = XSDPS_8_BIT_WIDTH;
    } else if (InstancePtr->Config.BusWidth == XSDPS_WIDTH_4) {
        /* in case of eMMC data width 4-bit */
        InstancePtr->BusWidth = XSDPS_4_BIT_WIDTH;
    } else {
        /* in case of eMMC data width 1-bit */
        InstancePtr->BusWidth = XSDPS_1_BIT_WIDTH;
    }

    Status = XSdPs_Change_BusWidth(InstancePtr);
    if (Status != XST_SUCCESS) {
        Status = XST_FAILURE;
        goto RETURN_PATH;
    }

    /* Get Extended CSD */
    Status = XSdPs_Get_Mmc_ExtCsd(InstancePtr, ExtCsd);
    if (Status != XST_SUCCESS) {
        Status = XST_FAILURE;
        goto RETURN_PATH;
    }

    InstancePtr->SectorCount = ((u32)ExtCsd[EXT_CSD_SEC_COUNT_BYTE4]) << 24;
    InstancePtr->SectorCount |= (u32)ExtCsd[EXT_CSD_SEC_COUNT_BYTE3] << 16;
    InstancePtr->SectorCount |= (u32)ExtCsd[EXT_CSD_SEC_COUNT_BYTE2] << 8;
    InstancePtr->SectorCount |= (u32)ExtCsd[EXT_CSD_SEC_COUNT_BYTE1];

    XSdPs_IdentifyEmmcMode(InstancePtr, ExtCsd);

    if (InstancePtr->Mode != XSDPS_DEFAULT_SPEED_MODE) {
        Status = XSdPs_Change_BusSpeed(InstancePtr);
        if (Status != XST_SUCCESS) {
            Status = XST_FAILURE;
            goto RETURN_PATH;
        }

        Status = XSdPs_CheckEmmcTiming(InstancePtr, ExtCsd);
        if (Status != XST_SUCCESS) {
            Status = XST_FAILURE;
            goto RETURN_PATH;
        }
    }

    /* Enable Rst_n_Fun bit if it is disabled */
    if(ExtCsd[EXT_CSD_RST_N_FUN_BYTE] == EXT_CSD_RST_N_FUN_TEMP_DIS) {
        Status = XSdPs_Set_Mmc_ExtCsd(InstancePtr, XSDPS_MMC_RST_FUN_EN_ARG);
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
* This function disables the bus power.
*
* @param    InstancePtr is a pointer to the instance to be worked on.
*
* @return    None
*
******************************************************************************/
void XSdPs_DisableBusPower(XSdPs *InstancePtr)
{
    /* Disable SD bus power and issue eMMC HW reset */
    if (InstancePtr->HC_Version == XSDPS_HC_SPEC_V3) {
        XSdPs_WriteReg8(InstancePtr->Config.BaseAddress,
                XSDPS_POWER_CTRL_OFFSET, XSDPS_PC_EMMC_HW_RST_MASK);
    } else {
        XSdPs_WriteReg8(InstancePtr->Config.BaseAddress,
                XSDPS_POWER_CTRL_OFFSET, 0x0);
    }

    /* 1ms delay to poweroff card */
    (void)usleep(1000U);
}

/*****************************************************************************/
/**
* @brief
* This function enables the bus power.
*
* @param    InstancePtr is a pointer to the instance to be worked on.
*
* @return    None
*
******************************************************************************/
void XSdPs_EnableBusPower(XSdPs *InstancePtr)
{
    /* Select voltage and enable bus power. */
    if (InstancePtr->HC_Version == XSDPS_HC_SPEC_V3) {
        XSdPs_WriteReg8(InstancePtr->Config.BaseAddress,
                XSDPS_POWER_CTRL_OFFSET,
                (XSDPS_PC_BUS_VSEL_3V3_MASK | XSDPS_PC_BUS_PWR_MASK) &
                ~XSDPS_PC_EMMC_HW_RST_MASK);
    } else {
        XSdPs_WriteReg8(InstancePtr->Config.BaseAddress,
                XSDPS_POWER_CTRL_OFFSET,
                XSDPS_PC_BUS_VSEL_3V3_MASK | XSDPS_PC_BUS_PWR_MASK);
    }

    /* 0.2ms Delay after bus power on*/
    usleep(200);
}

/*****************************************************************************/
/**
* @brief
* This function enumerates the SD card.
*
* @param    InstancePtr is a pointer to the instance to be worked on.
*
* @return    None
*
******************************************************************************/
s32 XSdPs_SdCardEnum(XSdPs *InstancePtr)
{
    s32 Status;

    /* Check if the card is present */
    Status = XSdPs_CheckCardDetect(InstancePtr);
    if (Status != XST_SUCCESS) {
        Status = XST_FAILURE;
        goto RETURN_PATH;
    }

    /* Reset the SD card */
    Status = XSdPs_CardReset(InstancePtr);
    if (Status != XST_SUCCESS) {
        Status = XST_FAILURE;
        goto RETURN_PATH;
    }

    /* Get the card interface condition */
    Status = XSdPs_CardIfCond(InstancePtr);
    if (Status != XST_SUCCESS) {
        Status = XST_FAILURE;
        goto RETURN_PATH;
    }

    /* Get the card operating condition */
    Status = XSdPs_CardOpCond(InstancePtr);
    if (Status != XST_SUCCESS) {
        Status = XST_FAILURE;
        goto RETURN_PATH;
    }

    /* Get the card ID */
    Status = XSdPs_GetCardId(InstancePtr);
    if (Status != XST_SUCCESS) {
        Status = XST_FAILURE;
        goto RETURN_PATH;
    }

    /* Get the CSD register */
    Status = XSdPs_GetCsd(InstancePtr);
    if (Status != XST_SUCCESS) {
        Status = XST_FAILURE;
        goto RETURN_PATH;
    }

    /* Change clock to default clock 25MHz */
    /*
     * SD default speed mode timing should be closed at 19 MHz.
     * The reason for this is SD requires a voltage level shifter.
     * This limitation applies to ZynqMPSoC.
     */
    if (InstancePtr->HC_Version == XSDPS_HC_SPEC_V3) {
        InstancePtr->BusSpeed = SD_CLK_19_MHZ;
    } else {
        InstancePtr->BusSpeed = SD_CLK_25_MHZ;
    }
    Status = XSdPs_Change_ClkFreq(InstancePtr, InstancePtr->BusSpeed);
    if (Status != XST_SUCCESS) {
        Status = XST_FAILURE;
        goto RETURN_PATH;
    }

    /* Select the card to transition to transfer state */
    Status = XSdPs_Select_Card(InstancePtr);
    if (Status != XST_SUCCESS) {
        Status = XST_FAILURE;
        goto RETURN_PATH;
    }

    /* Pull-up disconnected during data transfer */
    Status = XSdPs_Pullup(InstancePtr);
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
* This function enumerates the MMC card.
*
* @param    InstancePtr is a pointer to the instance to be worked on.
*
* @return    None
*
******************************************************************************/
s32 XSdPs_MmcCardEnum(XSdPs *InstancePtr)
{
    s32 Status;

    /* Check if the card is preset */
    Status = XSdPs_CheckCardDetect(InstancePtr);
    if (Status != XST_SUCCESS) {
        Status = XST_FAILURE;
        goto RETURN_PATH;
    }

    /* Reset the card */
    Status = XSdPs_CardReset(InstancePtr);
    if (Status != XST_SUCCESS) {
        Status = XST_FAILURE;
        goto RETURN_PATH;
    }

    /* Get the card operating condition */
    Status = XSdPs_CardOpCond(InstancePtr);
    if (Status != XST_SUCCESS) {
        Status = XST_FAILURE;
        goto RETURN_PATH;
    }

    /* Get the card ID */
    Status = XSdPs_GetCardId(InstancePtr);
    if (Status != XST_SUCCESS) {
        Status = XST_FAILURE;
        goto RETURN_PATH;
    }

    /* Get the CSD register */
    Status = XSdPs_GetCsd(InstancePtr);
    if (Status != XST_SUCCESS) {
        Status = XST_FAILURE;
        goto RETURN_PATH;
    }

    /* Change clock to default clock 26MHz */
    InstancePtr->BusSpeed = SD_CLK_26_MHZ;
    Status = XSdPs_Change_ClkFreq(InstancePtr, InstancePtr->BusSpeed);
    if (Status != XST_SUCCESS) {
        Status = XST_FAILURE;
        goto RETURN_PATH;
    }

    /* Send select card command to transition to transfer state */
    Status = XSdPs_Select_Card(InstancePtr);
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
* This function performs SD tuning.
*
* @param    InstancePtr is a pointer to the instance to be worked on.
*
* @return    None
*
******************************************************************************/
s32 XSdPs_Execute_Tuning(XSdPs *InstancePtr)
{
    s32 Status;

#ifndef versal
    /* Issue DLL Reset to load new SDHC tuned tap values */
    Status = XSdPs_DllReset(InstancePtr);
    if (Status != XST_SUCCESS) {
        Status = XST_FAILURE;
        goto RETURN_PATH;
    }

#endif

    /* Perform the auto tuning */
    Status = XSdPs_AutoTuning(InstancePtr);
    if (Status != XST_SUCCESS) {
        Status = XST_FAILURE;
        goto RETURN_PATH;
    }

#ifndef versal
    /* Issue DLL Reset to load new SDHC tuned tap values */
    Status = XSdPs_DllReset(InstancePtr);
    if (Status != XST_SUCCESS) {
        Status = XST_FAILURE;
        goto RETURN_PATH;
    }

#endif

    Status = XST_SUCCESS;

RETURN_PATH:
    return Status;

}

/*****************************************************************************/
/**
* @brief
* This function is used to enable the clock.
*
* @param    InstancePtr is a pointer to the instance to be worked on.
* @param    ClockReg is the clock value to be set.
*
* @return
*         - XST_SUCCESS if success
*         - XST_FAILURE if failure
*
******************************************************************************/
s32 XSdPs_EnableClock(XSdPs *InstancePtr, u16 ClockReg)
{
    u32 Timeout = 150000U;
    s32 Status;
    u16 ReadReg;

    ClockReg |= (u16)XSDPS_CC_INT_CLK_EN_MASK;
    XSdPs_WriteReg16(InstancePtr->Config.BaseAddress,
            XSDPS_CLK_CTRL_OFFSET, ClockReg);

    /* Wait for 150ms for internal clock to stabilize */
    do {
        ReadReg = XSdPs_ReadReg16(InstancePtr->Config.BaseAddress,
                XSDPS_CLK_CTRL_OFFSET);
        Timeout = Timeout - 1U;
        usleep(1);
    } while (((ReadReg & XSDPS_CC_INT_CLK_STABLE_MASK) == 0U)
                && (Timeout != 0U));

    if (Timeout == 0U) {
        Status = XST_FAILURE;
        goto RETURN_PATH ;
    }

    /* Enable SD clock */
    ClockReg |= XSDPS_CC_SD_CLK_EN_MASK;
    XSdPs_WriteReg16(InstancePtr->Config.BaseAddress,
            XSDPS_CLK_CTRL_OFFSET, ClockReg);

    Status = XST_SUCCESS;

RETURN_PATH:
    return Status;
}

/*****************************************************************************/
/**
* @brief
* This function is used to calculate the bus speed.
*
* @param    InstancePtr is a pointer to the instance to be worked on.
* @param    Arg is the argument to be sent along with the command.
*         This could be address or any other information
*
* @return
*         - XST_SUCCESS if success
*         - XST_FAILURE if failure
*
******************************************************************************/
s32 XSdPs_CalcBusSpeed(XSdPs *InstancePtr, u32 *Arg)
{
    s32 Status = XST_SUCCESS;

    if (InstancePtr->CardType == XSDPS_CARD_SD) {
        switch (InstancePtr->Mode) {
        case XSDPS_UHS_SPEED_MODE_SDR12:
            *Arg = XSDPS_SWITCH_CMD_SDR12_SET;
            InstancePtr->BusSpeed = XSDPS_SD_SDR12_MAX_CLK;
            break;
        case XSDPS_UHS_SPEED_MODE_SDR25:
            *Arg = XSDPS_SWITCH_CMD_SDR25_SET;
            InstancePtr->BusSpeed = XSDPS_SD_SDR25_MAX_CLK;
            break;
        case XSDPS_UHS_SPEED_MODE_SDR50:
            *Arg = XSDPS_SWITCH_CMD_SDR50_SET;
            InstancePtr->BusSpeed = XSDPS_SD_SDR50_MAX_CLK;
            break;
        case XSDPS_UHS_SPEED_MODE_SDR104:
            *Arg = XSDPS_SWITCH_CMD_SDR104_SET;
            InstancePtr->BusSpeed = XSDPS_SD_SDR104_MAX_CLK;
            break;
        case XSDPS_UHS_SPEED_MODE_DDR50:
            *Arg = XSDPS_SWITCH_CMD_DDR50_SET;
            InstancePtr->BusSpeed = XSDPS_SD_DDR50_MAX_CLK;
            break;
        case XSDPS_HIGH_SPEED_MODE:
            *Arg = XSDPS_SWITCH_CMD_HS_SET;
            InstancePtr->BusSpeed = XSDPS_CLK_50_MHZ;
            break;
        default:
            Status = XST_FAILURE;
            break;
        }
    } else {
        switch (InstancePtr->Mode) {
        case XSDPS_HS200_MODE:
            *Arg = XSDPS_MMC_HS200_ARG;
            InstancePtr->BusSpeed = XSDPS_MMC_HS200_MAX_CLK;
            break;
        case XSDPS_DDR52_MODE:
            *Arg = XSDPS_MMC_HIGH_SPEED_ARG;
            InstancePtr->BusSpeed = XSDPS_MMC_DDR_MAX_CLK;
            break;
        case XSDPS_HIGH_SPEED_MODE:
            *Arg = XSDPS_MMC_HIGH_SPEED_ARG;
            InstancePtr->BusSpeed = XSDPS_MMC_HSD_MAX_CLK;
            break;
        default:
            Status = XST_FAILURE;
            break;
        }
    }

    return Status;
}

/*****************************************************************************/
/**
* @brief
* This function is used to do the DMA transfer to or from SD card.
*
* @param    InstancePtr is a pointer to the instance to be worked on.
* @param    BlkCnt - Block count passed by the user.
* @param    BlkSize - Block size passed by the user.
* @param    Buff - Pointer to the data buffer for a DMA transfer.
*
* @return
*         - XST_SUCCESS if initialization was successful
*         - XST_FAILURE if failure - could be because another transfer
*             is in progress or command or data inhibit is set
*
******************************************************************************/
void XSdPs_SetupReadDma(XSdPs *InstancePtr, u16 BlkCnt, u16 BlkSize, u8 *Buff)
{
    BlkSize &= XSDPS_BLK_SIZE_MASK;

    XSdPs_WriteReg16(InstancePtr->Config.BaseAddress,
            XSDPS_BLK_SIZE_OFFSET, BlkSize);

    if (InstancePtr->Dma64BitAddr >= ADDRESS_BEYOND_32BIT) {
        XSdPs_SetupADMA2DescTbl64Bit(InstancePtr, BlkCnt);
    } else {
        XSdPs_SetupADMA2DescTbl(InstancePtr, BlkCnt, Buff);
        if (InstancePtr->Config.IsCacheCoherent == 0U) {
            Xil_DCacheInvalidateRange((INTPTR)Buff,
                (INTPTR)BlkCnt * BlkSize);
        }
    }

    if (BlkCnt == 1U) {
        InstancePtr->TransferMode = XSDPS_TM_BLK_CNT_EN_MASK |
            XSDPS_TM_DAT_DIR_SEL_MASK | XSDPS_TM_DMA_EN_MASK;
    } else {
        InstancePtr->TransferMode = XSDPS_TM_AUTO_CMD12_EN_MASK |
            XSDPS_TM_BLK_CNT_EN_MASK | XSDPS_TM_DAT_DIR_SEL_MASK |
            XSDPS_TM_DMA_EN_MASK | XSDPS_TM_MUL_SIN_BLK_SEL_MASK;
    }
}

/*****************************************************************************/
/**
* @brief
* This function is used to do the DMA transfer to or from SD card.
*
* @param    InstancePtr is a pointer to the instance to be worked on.
* @param    BlkCnt - Block count passed by the user.
* @param    BlkSize - Block size passed by the user.
* @param    Buff - Pointer to the data buffer for a DMA transfer.
*
* @return
*         - XST_SUCCESS if initialization was successful
*         - XST_FAILURE if failure - could be because another transfer
*             is in progress or command or data inhibit is set
*
******************************************************************************/
void XSdPs_SetupWriteDma(XSdPs *InstancePtr, u16 BlkCnt, u16 BlkSize, const u8 *Buff)
{
    BlkSize &= XSDPS_BLK_SIZE_MASK;

    XSdPs_WriteReg16(InstancePtr->Config.BaseAddress,
            XSDPS_BLK_SIZE_OFFSET, BlkSize);

    if (InstancePtr->Dma64BitAddr >= ADDRESS_BEYOND_32BIT) {
        XSdPs_SetupADMA2DescTbl64Bit(InstancePtr, BlkCnt);
    } else {
        XSdPs_SetupADMA2DescTbl(InstancePtr, BlkCnt, Buff);
        if (InstancePtr->Config.IsCacheCoherent == 0U) {
            Xil_DCacheFlushRange((INTPTR)Buff,
                (INTPTR)BlkCnt * BlkSize);
        }
    }

    if (BlkCnt == 1U) {
        InstancePtr->TransferMode = XSDPS_TM_BLK_CNT_EN_MASK |
            XSDPS_TM_DMA_EN_MASK;
    } else {
        InstancePtr->TransferMode = XSDPS_TM_AUTO_CMD12_EN_MASK |
            XSDPS_TM_BLK_CNT_EN_MASK |
            XSDPS_TM_MUL_SIN_BLK_SEL_MASK | XSDPS_TM_DMA_EN_MASK;
    }
}

/*****************************************************************************/
/**
*
* @brief
* API to setup ADMA2 descriptor table for 32-bit DMA
*
*
* @param    InstancePtr is a pointer to the XSdPs instance.
* @param    BlkCnt - block count.
* @param    Buff pointer to data buffer.
*
* @return    None
*
* @note        None.
*
******************************************************************************/
void XSdPs_Setup32ADMA2DescTbl(XSdPs *InstancePtr, u32 BlkCnt, const u8 *Buff)
{
#ifdef __ICCARM__
#pragma data_alignment = 32
    static XSdPs_Adma2Descriptor32 Adma2_DescrTbl[32];
#else
    static XSdPs_Adma2Descriptor32 Adma2_DescrTbl[32] __attribute__ ((aligned(32)));
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
                (u32)((UINTPTR)Buff + (DescNum*XSDPS_DESC_MAX_LENGTH));
        Adma2_DescrTbl[DescNum].Attribute =
                XSDPS_DESC_TRAN | XSDPS_DESC_VALID;
        Adma2_DescrTbl[DescNum].Length = 0U;
    }

    Adma2_DescrTbl[TotalDescLines-1].Address =
            (u32)((UINTPTR)Buff + (DescNum*XSDPS_DESC_MAX_LENGTH));

    Adma2_DescrTbl[TotalDescLines-1].Attribute =
            XSDPS_DESC_TRAN | XSDPS_DESC_END | XSDPS_DESC_VALID;

    Adma2_DescrTbl[TotalDescLines-1].Length =
            (u16)((BlkCnt*BlkSize) - (u32)(DescNum*XSDPS_DESC_MAX_LENGTH));

    XSdPs_WriteReg(InstancePtr->Config.BaseAddress, XSDPS_ADMA_SAR_OFFSET,
            (u32)((UINTPTR)&(Adma2_DescrTbl[0]) & (u32)~0x0));

    if (InstancePtr->Config.IsCacheCoherent == 0U) {
        Xil_DCacheFlushRange((INTPTR)&(Adma2_DescrTbl[0]),
            sizeof(XSdPs_Adma2Descriptor32) * 32U);
    }
}

/*****************************************************************************/
/**
*
* @brief
* API to setup ADMA2 descriptor table for 64-bit DMA
*
*
* @param    InstancePtr is a pointer to the XSdPs instance.
* @param    BlkCnt - block count.
* @param    Buff pointer to data buffer.
*
* @return    None
*
* @note        None.
*
******************************************************************************/
void XSdPs_Setup64ADMA2DescTbl(XSdPs *InstancePtr, u32 BlkCnt, const u8 *Buff)
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
                ((UINTPTR)Buff + (DescNum*XSDPS_DESC_MAX_LENGTH));
        Adma2_DescrTbl[DescNum].Attribute =
                XSDPS_DESC_TRAN | XSDPS_DESC_VALID;
        Adma2_DescrTbl[DescNum].Length = 0U;
    }

    Adma2_DescrTbl[TotalDescLines-1].Address =
            (u64)((UINTPTR)Buff + (DescNum*XSDPS_DESC_MAX_LENGTH));

    Adma2_DescrTbl[TotalDescLines-1].Attribute =
            XSDPS_DESC_TRAN | XSDPS_DESC_END | XSDPS_DESC_VALID;

    Adma2_DescrTbl[TotalDescLines-1].Length =
            (u16)((BlkCnt*BlkSize) - (u32)(DescNum*XSDPS_DESC_MAX_LENGTH));

#if defined(__aarch64__) || defined(__arch64__)
    XSdPs_WriteReg(InstancePtr->Config.BaseAddress, XSDPS_ADMA_SAR_EXT_OFFSET,
            (u32)((UINTPTR)(Adma2_DescrTbl)>>32U));
#endif

    XSdPs_WriteReg(InstancePtr->Config.BaseAddress, XSDPS_ADMA_SAR_OFFSET,
            (u32)((UINTPTR)&(Adma2_DescrTbl[0]) & (u32)~0x0));

    if (InstancePtr->Config.IsCacheCoherent == 0U) {
        Xil_DCacheFlushRange((INTPTR)&(Adma2_DescrTbl[0]),
            sizeof(XSdPs_Adma2Descriptor64) * 32U);
    }
}

/*****************************************************************************/
/**
* @brief
* This function is used calculate the clock divisor value.
*
* @param    InstancePtr is a pointer to the instance to be worked on.
* @param    SelFreq is the selected frequency
*
* @return    Clock divisor value
*
******************************************************************************/
u32 XSdPs_CalcClock(XSdPs *InstancePtr, u32 SelFreq)
{
    u16 ClockVal = 0U;
    u16 DivCnt;
    u16 Divisor = 0U;

    if (InstancePtr->HC_Version == XSDPS_HC_SPEC_V3) {
        /* Calculate divisor */
        for (DivCnt = 0x1U; DivCnt <= XSDPS_CC_EXT_MAX_DIV_CNT; DivCnt++) {
            if (((InstancePtr->Config.InputClockHz) / DivCnt) <= SelFreq) {
                Divisor = DivCnt >> 1;
                break;
            }
        }
    } else {
        /* Calculate divisor */
        for (DivCnt = 0x1U; DivCnt <= XSDPS_CC_MAX_DIV_CNT; DivCnt <<= 1U) {
            if (((InstancePtr->Config.InputClockHz) / DivCnt) <= SelFreq) {
                Divisor = DivCnt / 2U;
                break;
            }
        }
    }

    ClockVal |= (Divisor & XSDPS_CC_SDCLK_FREQ_SEL_MASK) << XSDPS_CC_DIV_SHIFT;
    ClockVal |= ((Divisor >> 8U) & XSDPS_CC_SDCLK_FREQ_SEL_EXT_MASK) << XSDPS_CC_EXT_DIV_SHIFT;

    return ClockVal;
}

/*****************************************************************************/
/**
*
* @brief
* API to Set or Reset the DLL
*
*
* @param    InstancePtr is a pointer to the XSdPs instance.
* @param    EnRst is a flag indicating whether to Assert or De-assert Reset.
*
* @return    None
*
* @note        None.
*
******************************************************************************/
void XSdPs_DllRstCtrl(XSdPs *InstancePtr, u8 EnRst)
{
    u32 DeviceId;
    u32 DllCtrl;

    DeviceId = InstancePtr->Config.DeviceId;
#ifdef versal
#ifdef XPAR_PSV_PMC_SD_0_DEVICE_ID
    if (DeviceId == 0U) {
#if EL1_NONSECURE && defined (__aarch64__)
        (void)DllCtrl;

        XSdps_Smc(InstancePtr, SD0_DLL_CTRL, SD_DLL_RST, (EnRst == 1U) ? SD0_DLL_RST : 0U);
#else /* EL1_NONSECURE && defined (__aarch64__) */
        DllCtrl = XSdPs_ReadReg(InstancePtr->SlcrBaseAddr, SD0_DLL_CTRL);
        if (EnRst == 1U) {
            DllCtrl |= SD_DLL_RST;
        } else {
            DllCtrl &= ~SD_DLL_RST;
        }
        XSdPs_WriteReg(InstancePtr->SlcrBaseAddr, SD0_DLL_CTRL, DllCtrl);
#endif /* EL1_NONSECURE && defined (__aarch64__) */
    } else {
#endif /* XPAR_PSV_PMC_SD_0_DEVICE_ID */
        (void) DeviceId;
#if EL1_NONSECURE && defined (__aarch64__)
        (void)DllCtrl;

        XSdps_Smc(InstancePtr, SD1_DLL_CTRL, SD_DLL_RST, (EnRst == 1U) ? SD_DLL_RST : 0U);
#else
        DllCtrl = XSdPs_ReadReg(InstancePtr->SlcrBaseAddr, SD1_DLL_CTRL);
        if (EnRst == 1U) {
            DllCtrl |= SD_DLL_RST;
        } else {
            DllCtrl &= ~SD_DLL_RST;
        }
        XSdPs_WriteReg(InstancePtr->SlcrBaseAddr, SD1_DLL_CTRL, DllCtrl);
#endif
#ifdef XPAR_PSV_PMC_SD_0_DEVICE_ID
    }
#endif /* XPAR_PSV_PMC_SD_0_DEVICE_ID */
#else /* versal */

#ifdef XPAR_PSU_SD_0_DEVICE_ID
    if (DeviceId == 0U) {
#if EL1_NONSECURE && defined (__aarch64__)
        (void)DllCtrl;

        XSdps_Smc(InstancePtr, SD_DLL_CTRL, SD0_DLL_RST, (EnRst == 1U) ? SD0_DLL_RST : 0U);
#else
        DllCtrl = XSdPs_ReadReg(InstancePtr->SlcrBaseAddr, SD_DLL_CTRL);
        if (EnRst == 1U) {
            DllCtrl |= SD0_DLL_RST;
        } else {
            DllCtrl &= ~SD0_DLL_RST;
        }
        XSdPs_WriteReg(InstancePtr->SlcrBaseAddr, SD_DLL_CTRL, DllCtrl);
#endif
    } else {
#endif /* XPAR_PSU_SD_0_DEVICE_ID */
        (void) DeviceId;
#if EL1_NONSECURE && defined (__aarch64__)
        (void)DllCtrl;

        XSdps_Smc(InstancePtr, SD_DLL_CTRL, SD1_DLL_RST, (EnRst == 1U) ? SD1_DLL_RST : 0U);
#else
        DllCtrl = XSdPs_ReadReg(InstancePtr->SlcrBaseAddr, SD_DLL_CTRL);
        if (EnRst == 1U) {
            DllCtrl |= SD1_DLL_RST;
        } else {
            DllCtrl &= ~SD1_DLL_RST;
        }
        XSdPs_WriteReg(InstancePtr->SlcrBaseAddr, SD_DLL_CTRL, DllCtrl);
#endif
#ifdef XPAR_PSU_SD_0_DEVICE_ID
    }
#endif
#endif
}

/*****************************************************************************/
/**
*
* @brief
* Function to configure the Tap Delays.
*
*
* @param    InstancePtr is a pointer to the XSdPs instance.
*
* @return    None
*
* @note        None.
*
******************************************************************************/
void XSdPs_ConfigTapDelay(XSdPs *InstancePtr)
{
    u32 DeviceId;
    u32 TapDelay;
    u32 ITapDelay;
    u32 OTapDelay;

    DeviceId = InstancePtr->Config.DeviceId ;
    TapDelay = 0U;
    ITapDelay = InstancePtr->ITapDelay;
    OTapDelay = InstancePtr->OTapDelay;

#ifdef versal
    (void) DeviceId;
    if (ITapDelay) {
        TapDelay = SD_ITAPCHGWIN;
        XSdPs_WriteReg(InstancePtr->Config.BaseAddress, SD_ITAPDLY, TapDelay);
        /* Program the ITAPDLY */
        TapDelay |= SD_ITAPDLYENA;
        XSdPs_WriteReg(InstancePtr->Config.BaseAddress, SD_ITAPDLY, TapDelay);
        TapDelay |= ITapDelay;
        XSdPs_WriteReg(InstancePtr->Config.BaseAddress, SD_ITAPDLY, TapDelay);
        TapDelay &= ~SD_ITAPCHGWIN;
        XSdPs_WriteReg(InstancePtr->Config.BaseAddress, SD_ITAPDLY, TapDelay);
    }
    if (OTapDelay) {
        /* Program the OTAPDLY */
        TapDelay = SD_OTAPDLYENA;
        XSdPs_WriteReg(InstancePtr->Config.BaseAddress, SD_OTAPDLY, TapDelay);
        TapDelay |= OTapDelay;
        XSdPs_WriteReg(InstancePtr->Config.BaseAddress, SD_OTAPDLY, TapDelay);
    }
#else
#ifdef XPAR_PSU_SD_0_DEVICE_ID
    if (DeviceId == 0U) {
#if EL1_NONSECURE && defined (__aarch64__)
        (void)TapDelay;
        if (ITapDelay) {
            XSdps_Smc(InstancePtr, SD_ITAPDLY, SD0_ITAPCHGWIN, SD0_ITAPCHGWIN);
            XSdps_Smc(InstancePtr, SD_ITAPDLY, SD0_ITAPDLYENA, SD0_ITAPDLYENA);
            XSdps_Smc(InstancePtr, SD_ITAPDLY, SD0_ITAPDLY_SEL_MASK, ITapDelay);
            XSdps_Smc(InstancePtr, SD_ITAPDLY, SD0_ITAPCHGWIN, 0U);
        }
        if (OTapDelay) {
            XSdps_Smc(InstancePtr, SD_OTAPDLY, SD0_OTAPDLY_SEL_MASK, OTapDelay);
        }
#else
        if (ITapDelay) {
            TapDelay = XSdPs_ReadReg(InstancePtr->SlcrBaseAddr, SD_ITAPDLY);
            TapDelay |= SD0_ITAPCHGWIN;
            XSdPs_WriteReg(InstancePtr->SlcrBaseAddr, SD_ITAPDLY, TapDelay);
            /* Program the ITAPDLY */
            TapDelay |= SD0_ITAPDLYENA;
            XSdPs_WriteReg(InstancePtr->SlcrBaseAddr, SD_ITAPDLY, TapDelay);
            TapDelay |= ITapDelay;
            XSdPs_WriteReg(InstancePtr->SlcrBaseAddr, SD_ITAPDLY, TapDelay);
            TapDelay &= ~SD0_ITAPCHGWIN;
            XSdPs_WriteReg(InstancePtr->SlcrBaseAddr, SD_ITAPDLY, TapDelay);
        }
        if (OTapDelay) {
            /* Program the OTAPDLY */
            TapDelay = XSdPs_ReadReg(InstancePtr->SlcrBaseAddr, SD_OTAPDLY);
            TapDelay &= ~SD0_OTAPDLY_SEL_MASK;
            TapDelay |= OTapDelay;
            XSdPs_WriteReg(InstancePtr->SlcrBaseAddr, SD_OTAPDLY, TapDelay);
        }
#endif
    } else {
#endif
        (void) DeviceId;
        ITapDelay = ITapDelay << 16U;
        OTapDelay = OTapDelay << 16U;
#if EL1_NONSECURE && defined (__aarch64__)
        (void)TapDelay;
        if (ITapDelay) {
            XSdps_Smc(InstancePtr, SD_ITAPDLY, SD1_ITAPCHGWIN, SD1_ITAPCHGWIN);
            XSdps_Smc(InstancePtr, SD_ITAPDLY, SD1_ITAPDLYENA, SD1_ITAPDLYENA);
            XSdps_Smc(InstancePtr, SD_ITAPDLY, SD1_ITAPDLY_SEL_MASK, ITapDelay);
            XSdps_Smc(InstancePtr, SD_ITAPDLY, SD1_ITAPCHGWIN, 0U);
        }
        if (OTapDelay) {
            XSdps_Smc(InstancePtr, SD_OTAPDLY, SD1_OTAPDLY_SEL_MASK, OTapDelay);
        }
#else
        if (ITapDelay) {
            TapDelay = XSdPs_ReadReg(InstancePtr->SlcrBaseAddr, SD_ITAPDLY);
            TapDelay |= SD1_ITAPCHGWIN;
            XSdPs_WriteReg(InstancePtr->SlcrBaseAddr, SD_ITAPDLY, TapDelay);
            /* Program the ITAPDLY */
            TapDelay |= SD1_ITAPDLYENA;
            XSdPs_WriteReg(InstancePtr->SlcrBaseAddr, SD_ITAPDLY, TapDelay);
            TapDelay |= ITapDelay;
            XSdPs_WriteReg(InstancePtr->SlcrBaseAddr, SD_ITAPDLY, TapDelay);
            TapDelay &= ~SD1_ITAPCHGWIN;
            XSdPs_WriteReg(InstancePtr->SlcrBaseAddr, SD_ITAPDLY, TapDelay);
        }
        if (OTapDelay) {
            /* Program the OTAPDLY */
            TapDelay = XSdPs_ReadReg(InstancePtr->SlcrBaseAddr, SD_OTAPDLY);
            TapDelay &= ~SD1_OTAPDLY_SEL_MASK;
            TapDelay |= OTapDelay;
            XSdPs_WriteReg(InstancePtr->SlcrBaseAddr, SD_OTAPDLY, TapDelay);
        }
#endif
#ifdef XPAR_PSU_SD_0_DEVICE_ID
    }
#endif
#endif /* versal */
}

/*****************************************************************************/
/**
* @brief
* This function is used to set voltage to 1.8V.
*
* @param    InstancePtr is a pointer to the instance to be worked on.
*
* @return
*         - XST_SUCCESS if successful
*         - XST_FAILURE if failure
*
******************************************************************************/
s32 XSdPs_SetVoltage18(XSdPs *InstancePtr)
{
    s32 Status;
    u16 CtrlReg;

    /* Enabling 1.8V in controller */
    CtrlReg = XSdPs_ReadReg16(InstancePtr->Config.BaseAddress,
            XSDPS_HOST_CTRL2_OFFSET);
    CtrlReg |= XSDPS_HC2_1V8_EN_MASK;
    XSdPs_WriteReg16(InstancePtr->Config.BaseAddress, XSDPS_HOST_CTRL2_OFFSET,
            CtrlReg);

    /* Wait minimum 5mSec */
    (void)usleep(5000U);

    /* Check for 1.8V signal enable bit is cleared by Host */
    Status = XSdPs_CheckVoltage18(InstancePtr);
    if (Status != XST_SUCCESS) {
        Status = XST_FAILURE;
    }

    return Status;
}

/*****************************************************************************/
/**
* @brief
* This function is used configure the Power Level.
*
* @param    InstancePtr is a pointer to the instance to be worked on.
*
* @return    None
*
******************************************************************************/
void XSdPs_ConfigPower(XSdPs *InstancePtr)
{
    u8 PowerLevel;

    if ((InstancePtr->Host_Caps & XSDPS_CAP_VOLT_3V3_MASK) != 0U) {
        PowerLevel = XSDPS_PC_BUS_VSEL_3V3_MASK;
    } else if ((InstancePtr->Host_Caps & XSDPS_CAP_VOLT_3V0_MASK) != 0U) {
        PowerLevel = XSDPS_PC_BUS_VSEL_3V0_MASK;
    } else if ((InstancePtr->Host_Caps & XSDPS_CAP_VOLT_1V8_MASK) != 0U) {
        PowerLevel = XSDPS_PC_BUS_VSEL_1V8_MASK;
    } else {
        PowerLevel = 0U;
    }

    /* Select voltage based on capability and enable bus power. */
    XSdPs_WriteReg8(InstancePtr->Config.BaseAddress,
            XSDPS_POWER_CTRL_OFFSET,
            PowerLevel | XSDPS_PC_BUS_PWR_MASK);
}

/*****************************************************************************/
/**
* @brief
* This function is used configure the DMA.
*
* @param    InstancePtr is a pointer to the instance to be worked on.
*
* @return    None
*
******************************************************************************/
void XSdPs_ConfigDma(XSdPs *InstancePtr)
{
    if (InstancePtr->HC_Version == XSDPS_HC_SPEC_V3) {
        /* Enable ADMA2 in 64bit mode. */
        XSdPs_WriteReg8(InstancePtr->Config.BaseAddress,
                XSDPS_HOST_CTRL1_OFFSET,
                XSDPS_HC_DMA_ADMA2_64_MASK);
    } else {
        /* Enable ADMA2 in 32bit mode. */
        XSdPs_WriteReg8(InstancePtr->Config.BaseAddress,
                XSDPS_HOST_CTRL1_OFFSET,
                XSDPS_HC_DMA_ADMA2_32_MASK);
    }
}

/*****************************************************************************/
/**
* @brief
* This function is used configure the Interrupts.
*
* @param    InstancePtr is a pointer to the instance to be worked on.
*
* @return    None
*
******************************************************************************/
void XSdPs_ConfigInterrupt(XSdPs *InstancePtr)
{
    /* Enable all interrupt status except card interrupt initially */
    XSdPs_WriteReg16(InstancePtr->Config.BaseAddress,
            XSDPS_NORM_INTR_STS_EN_OFFSET,
            XSDPS_NORM_INTR_ALL_MASK & (~XSDPS_INTR_CARD_MASK));

    XSdPs_WriteReg16(InstancePtr->Config.BaseAddress,
            XSDPS_ERR_INTR_STS_EN_OFFSET,
            XSDPS_ERROR_INTR_ALL_MASK);

    /* Disable all interrupt signals by default. */
    XSdPs_WriteReg16(InstancePtr->Config.BaseAddress,
            XSDPS_NORM_INTR_SIG_EN_OFFSET, 0x0U);
    XSdPs_WriteReg16(InstancePtr->Config.BaseAddress,
            XSDPS_ERR_INTR_SIG_EN_OFFSET, 0x0U);

}

/*****************************************************************************/
/**
* This function does SD command generation.
*
* @param    InstancePtr is a pointer to the instance to be worked on.
* @param    Cmd is the command to be sent.
* @param    Arg is the argument to be sent along with the command.
*         This could be address or any other information
* @param    BlkCnt - Block count passed by the user.
*
* @return
*         - XST_SUCCESS if initialization was successful
*         - XST_FAILURE if failure - could be because another transfer
*             is in progress or command or data inhibit is set
*
******************************************************************************/
s32 XSdPs_CmdTransfer(XSdPs *InstancePtr, u32 Cmd, u32 Arg, u32 BlkCnt)
{
    u32 Timeout = 10000000U;
    u32 StatusReg;
    s32 Status;

    Status = XSdPs_SetupCmd(InstancePtr, Arg, BlkCnt);
    if (Status != XST_SUCCESS) {
        Status = XST_FAILURE;
        goto RETURN_PATH;
    }

    Status = XSdPs_SendCmd(InstancePtr, Cmd);
    if (Status != XST_SUCCESS) {
        Status = XST_FAILURE;
        goto RETURN_PATH;
    }

    /* Polling for response for now */
    do {
        StatusReg = XSdPs_ReadReg16(InstancePtr->Config.BaseAddress,
                    XSDPS_NORM_INTR_STS_OFFSET);
        if ((Cmd == CMD21) || (Cmd == CMD19)) {
            if ((XSdPs_ReadReg16(InstancePtr->Config.BaseAddress,
                    XSDPS_NORM_INTR_STS_OFFSET) & XSDPS_INTR_BRR_MASK) != 0U){
                XSdPs_WriteReg16(InstancePtr->Config.BaseAddress,
                    XSDPS_NORM_INTR_STS_OFFSET, XSDPS_INTR_BRR_MASK);
                break;
            }
        }

        if ((StatusReg & XSDPS_INTR_ERR_MASK) != 0U) {
            Status = (s32)XSdPs_ReadReg16(InstancePtr->Config.BaseAddress,
                                    XSDPS_ERR_INTR_STS_OFFSET);
            if (((u32)Status & ~XSDPS_INTR_ERR_CT_MASK) == 0U) {
                Status = XSDPS_CT_ERROR;
            }
             /* Write to clear error bits */
            XSdPs_WriteReg16(InstancePtr->Config.BaseAddress,
                    XSDPS_ERR_INTR_STS_OFFSET,
                    XSDPS_ERROR_INTR_ALL_MASK);
            goto RETURN_PATH;
        }
        Timeout = Timeout - 1U;
    } while (((StatusReg & XSDPS_INTR_CC_MASK) == 0U)
                && (Timeout != 0U));
    /* Write to clear bit */
    XSdPs_WriteReg16(InstancePtr->Config.BaseAddress,
            XSDPS_NORM_INTR_STS_OFFSET,
            XSDPS_INTR_CC_MASK);

    Status = XST_SUCCESS;

RETURN_PATH:
        return Status;

}

/*****************************************************************************/
/**
* This function is used to check if the transfer is completed successfully.
*
* @param    InstancePtr is a pointer to the instance to be worked on.
*
* @return    None
*
******************************************************************************/
s32 XSdps_CheckTransferDone(XSdPs *InstancePtr)
{
    u32 Timeout = 5000000U;
    u16 StatusReg;
    s32 Status;

    /*
     * Check for transfer complete
     * Polling for response for now
     */
    do {
        StatusReg = XSdPs_ReadReg16(InstancePtr->Config.BaseAddress,
                    XSDPS_NORM_INTR_STS_OFFSET);
        if ((StatusReg & XSDPS_INTR_ERR_MASK) != 0U) {
            /* Write to clear error bits */
            XSdPs_WriteReg16(InstancePtr->Config.BaseAddress,
                    XSDPS_ERR_INTR_STS_OFFSET,
                    XSDPS_ERROR_INTR_ALL_MASK);
            Status = XST_FAILURE;
            goto RETURN_PATH;
        }
        Timeout = Timeout - 1U;
        usleep(1);
    } while (((StatusReg & XSDPS_INTR_TC_MASK) == 0U)
            && (Timeout != 0U));

    if (Timeout == 0U) {
        Status = XST_FAILURE;
        goto RETURN_PATH ;
    }

    /* Write to clear bit */
    XSdPs_WriteReg16(InstancePtr->Config.BaseAddress,
            XSDPS_NORM_INTR_STS_OFFSET, XSDPS_INTR_TC_MASK);

    Status = XST_SUCCESS;

RETURN_PATH:
    return Status;
}

/*****************************************************************************/
/**
* @brief
* This function is used to check if the CMD/DATA bus is idle or not.
*
* @param    InstancePtr is a pointer to the instance to be worked on.
* @param    Value is to selct Cmd bus or Dat bus
*
* @return    None
*
******************************************************************************/
s32 XSdPs_CheckBusIdle(XSdPs *InstancePtr, u32 Value)
{
    u32 Timeout = 10000000U;
    u32 PresentStateReg;
    u32 StatusReg;
    s32 Status;

    PresentStateReg = XSdPs_ReadReg(InstancePtr->Config.BaseAddress,
            XSDPS_PRES_STATE_OFFSET);
    /* Check for Card Present */
    if ((PresentStateReg & XSDPS_PSR_CARD_INSRT_MASK) != 0U) {
        /* Check for SD idle */
        do {
            StatusReg = XSdPs_ReadReg(InstancePtr->Config.BaseAddress,
                    XSDPS_PRES_STATE_OFFSET);
            Timeout = Timeout - 1;
            usleep(1);
        } while (((StatusReg & Value) != 0U)
                && (Timeout != 0U));
    }

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
* This function frames the Command register for a particular command.
* Note that this generates only the command register value i.e.
* the upper 16 bits of the transfer mode and command register.
* This value is already shifted to be upper 16 bits and can be directly
* OR'ed with transfer mode register value.
*
* @param    InstancePtr is a pointer to the instance to be worked on.
* @param    Cmd is the Command to be sent.
*
* @return    Command register value complete with response type and
*         data, CRC and index related flags.
*
******************************************************************************/
u32 XSdPs_FrameCmd(XSdPs *InstancePtr, u32 Cmd)
{
    u32 RetVal;

    RetVal = Cmd;
#if 0
    switch(Cmd) {
    case CMD0:
        RetVal |= RESP_NONE;
        break;
    case CMD1:
        RetVal |= RESP_R3;
        break;
    case CMD2:
        RetVal |= RESP_R2;
        break;
    case CMD3:
        if (InstancePtr->CardType == XSDPS_CARD_SD) {
            RetVal |= RESP_R6;
        } else {
            RetVal |= RESP_R1;
        }
        break;
    case CMD4:
        RetVal |= RESP_NONE;
        break;
    case CMD5:
        RetVal |= RESP_R1B;
        break;
    case CMD6:
        if (InstancePtr->CardType == XSDPS_CARD_SD) {
            RetVal |= RESP_R1 | (u32)XSDPS_DAT_PRESENT_SEL_MASK;
        } else {
            RetVal |= RESP_R1B;
        }
        break;
    case ACMD6:
        RetVal |= RESP_R1;
        break;
    case CMD7:
        RetVal |= RESP_R1;
        break;
    case CMD8:
        if (InstancePtr->CardType == XSDPS_CARD_SD) {
            RetVal |= RESP_R1;
        } else {
            RetVal |= RESP_R1 | (u32)XSDPS_DAT_PRESENT_SEL_MASK;
        }
        break;
    case CMD9:
        RetVal |= RESP_R2;
        break;
    case CMD11:
    case CMD10:
    case CMD12:
        RetVal |= RESP_R1;
        break;
    case ACMD13:
        RetVal |= RESP_R1 | (u32)XSDPS_DAT_PRESENT_SEL_MASK;
        break;
    case CMD16:
        RetVal |= RESP_R1;
        break;
    case CMD17:
    case CMD18:
    case CMD19:
    case CMD21:
        RetVal |= RESP_R1 | (u32)XSDPS_DAT_PRESENT_SEL_MASK;
        break;
    case CMD23:
    case ACMD23:
    case CMD24:
    case CMD25:
        RetVal |= RESP_R1 | (u32)XSDPS_DAT_PRESENT_SEL_MASK;
        break;
    case ACMD41:
        RetVal |= RESP_R3;
        break;
    case ACMD42:
        RetVal |= RESP_R1;
        break;
    case ACMD51:
        RetVal |= RESP_R1 | (u32)XSDPS_DAT_PRESENT_SEL_MASK;
        break;
    case CMD52:
    case CMD55:
        RetVal |= RESP_R1;
        break;
    case CMD58:
        break;
    default :
        RetVal |= Cmd;
        break;
    }
#else
    switch(Cmd) {
    case CMD0:
        RetVal |= XSDPS_RESP_NONE;
        break;
    case CMD1:
        RetVal |= XSDPS_RESP_R3;
        break;
    case CMD2:
        RetVal |= XSDPS_RESP_R2;
        break;
    case CMD3:
        if (InstancePtr->CardType == XSDPS_CARD_SD) {
            RetVal |= XSDPS_RESP_R6;
        } else {
            RetVal |= XSDPS_RESP_R1;
        }
        break;
    case CMD4:
        RetVal |= XSDPS_RESP_NONE;
        break;
    case CMD5:
        RetVal |= XSDPS_RESP_R1B;
        break;
    case CMD6:
        if (InstancePtr->CardType == XSDPS_CARD_SD) {
            RetVal |= XSDPS_RESP_R1 | (u32)XSDPS_DAT_PRESENT_SEL_MASK;
        } else {
            RetVal |= XSDPS_RESP_R1B;
        }
        break;
    case ACMD6:
        RetVal |= XSDPS_RESP_R1;
        break;
    case CMD7:
        RetVal |= XSDPS_RESP_R1;
        break;
    case CMD8:
        if (InstancePtr->CardType == XSDPS_CARD_SD) {
            RetVal |= XSDPS_RESP_R1;
        } else {
            RetVal |= XSDPS_RESP_R1 | (u32)XSDPS_DAT_PRESENT_SEL_MASK;
        }
        break;
    case CMD9:
        RetVal |= XSDPS_RESP_R2;
        break;
    case CMD11:
    case CMD10:
    case CMD12:
        RetVal |= XSDPS_RESP_R1;
        break;
    case ACMD13:
        RetVal |= XSDPS_RESP_R1 | (u32)XSDPS_DAT_PRESENT_SEL_MASK;
        break;
    case CMD16:
        RetVal |= XSDPS_RESP_R1;
        break;
    case CMD17:
    case CMD18:
    case CMD19:
    case CMD21:
        RetVal |= XSDPS_RESP_R1 | (u32)XSDPS_DAT_PRESENT_SEL_MASK;
        break;
    case CMD23:
    case ACMD23:
    case CMD24:
    case CMD25:
        RetVal |= XSDPS_RESP_R1 | (u32)XSDPS_DAT_PRESENT_SEL_MASK;
        break;
    case ACMD41:
        RetVal |= XSDPS_RESP_R3;
        break;
    case ACMD42:
        RetVal |= XSDPS_RESP_R1;
        break;
    case ACMD51:
        RetVal |= XSDPS_RESP_R1 | (u32)XSDPS_DAT_PRESENT_SEL_MASK;
        break;
    case CMD52:
    case CMD55:
        RetVal |= XSDPS_RESP_R1;
        break;
    case CMD58:
        break;
    default :
        RetVal |= Cmd;
        break;
    }
#endif
    return RetVal;
}

/** @} */
