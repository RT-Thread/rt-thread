/******************************************************************************
* Copyright (C) 2013 - 2020 Xilinx, Inc.  All rights reserved.
* SPDX-License-Identifier: MIT
******************************************************************************/

/*****************************************************************************/
/**
*
* @file xsdps.c
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
* 1.00a hk/sg  10/17/13 Initial release
* 2.0   hk     12/13/13 Added check for arm to use sleep.h and its API's
* 2.1   hk     04/18/14 Add sleep for microblaze designs. CR# 781117.
* 2.2   hk     07/28/14 Make changes to enable use of data cache.
* 2.3   sk     09/23/14 Send command for relative card address
*                       when re-initialization is done.CR# 819614.
*                        Use XSdPs_Change_ClkFreq API whenever changing
*                        clock.CR# 816586.
* 2.4    sk       12/04/14 Added support for micro SD without
*                         WP/CD. CR# 810655.
*                        Checked for DAT Inhibit mask instead of CMD
*                         Inhibit mask in Cmd Transfer API.
*                        Added Support for SD Card v1.0
* 2.5     sg       07/09/15 Added SD 3.0 features
*       kvn    07/15/15 Modified the code according to MISRAC-2012.
* 2.6   sk     10/12/15 Added support for SD card v1.0 CR# 840601.
* 2.7   sk     11/24/15 Considered the slot type befoe checking CD/WP pins.
*       sk     12/10/15 Added support for MMC cards.
*       sk     02/16/16 Corrected the Tuning logic.
*       sk     03/01/16 Removed Bus Width check for eMMC. CR# 938311.
* 2.8   sk     05/03/16 Standard Speed for SD to 19MHz in ZynqMPSoC. CR#951024
* 3.0   sk     06/09/16 Added support for mkfs to calculate sector count.
*       sk     07/16/16 Added support for UHS modes.
*       sk     07/07/16 Used usleep API for both arm and microblaze.
*       sk     07/16/16 Added Tap delays accordingly to different SD/eMMC
*                       operating modes.
* 3.1   mi     09/07/16 Removed compilation warnings with extra compiler flags.
*       sk     10/13/16 Reduced the delay during power cycle to 1ms as per spec
*       sk     10/19/16 Used emmc_hwreset pin to reset eMMC.
*       sk     11/07/16 Enable Rst_n bit in ext_csd reg if not enabled.
* 3.2   sk     11/30/16 Modified the voltage switching sequence as per spec.
*       sk     02/01/17 Added HSD and DDR mode support for eMMC.
*       vns    02/09/17 Added ARMA53_32 support for ZynqMP CR#968397
*       sk     03/20/17 Add support for EL1 non-secure mode.
* 3.3   mn     05/17/17 Add support for 64bit DMA addressing
*       mn     07/17/17 Add support for running SD at 200MHz
*       mn     07/26/17 Fixed compilation warnings
*       mn     08/07/17 Modify driver to support 64-bit DMA in arm64 only
*       mn     08/17/17 Added CCI support for A53 and disabled data cache
*                       operations when it is enabled.
*       mn     08/22/17 Updated for Word Access System support
*       mn     09/06/17 Resolved compilation errors with IAR toolchain
*       mn     09/26/17 Added UHS_MODE_ENABLE macro to enable UHS mode
* 3.4   mn     10/17/17 Use different commands for single and multi block
*                       transfers
*       mn     03/02/18 Move UHS macro check to SD card initialization routine
* 3.5   mn     04/18/18 Resolve compilation warnings for sdps driver
* 3.6   mn     07/06/18 Fix Cppcheck and Doxygen warnings for sdps driver
*       mn     08/01/18 Add support for using 64Bit DMA with 32-Bit Processor
*       mn     08/01/18 Add cache invalidation call before returning from
*                       ReadPolled API
*       mn     08/14/18 Resolve compilation warnings for ARMCC toolchain
*       mn     10/01/18 Change Expected Response for CMD3 to R1 for MMC
*       mus    11/05/18 Support 64 bit DMA addresses for Microblaze-X platform.
* 3.7   mn     02/01/19 Add support for idling of SDIO
*       aru    03/12/19 Modified the code according to MISRAC-2012.
* 3.8   mn     04/12/19 Modified TapDelay code for supporting ZynqMP and Versal
*       mn     09/17/19 Modified ADMA handling API for 32bit and 64bit addresses
* 3.9   sd     02/07/20 Added clock support
*       mn     03/03/20 Restructured the code for more readability and modularity
*       mn     03/30/20 Return XST_DEVICE_IS_STARTED when host is already started
*       mn     03/30/20 Move Clock enabling before checking for Host already started
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
* Initializes a specific XSdPs instance such that the driver is ready to use.
*
*
* @param    InstancePtr is a pointer to the XSdPs instance.
* @param    ConfigPtr is a reference to a structure containing information
*        about a specific SD device. This function initializes an
*        InstancePtr object for a specific device specified by the
*        contents of Config.
* @param    EffectiveAddr is the device base address in the virtual memory
*        address space. The caller is responsible for keeping the address
*        mapping from EffectiveAddr to the device physical base address
*        unchanged once this function is invoked. Unexpected errors may
*        occur if the address mapping changes after this function is
*        called. If address translation is not used, use
*        ConfigPtr->Config.BaseAddress for this device.
*
* @return
*        - XST_SUCCESS if successful.
*        - XST_DEVICE_IS_STARTED if the device is already started.
*        It must be stopped to re-initialize.
*
* @note        This function initializes the host controller.
*        Initial clock of 400KHz is set.
*        Voltage of 3.3V is selected as that is supported by host.
*        Interrupts status is enabled and signal disabled by default.
*        Default data direction is card to host and
*        32 bit ADMA2 is selected. Default Block size is 512 bytes.
*
******************************************************************************/
s32 XSdPs_CfgInitialize(XSdPs *InstancePtr, XSdPs_Config *ConfigPtr,
                u32 EffectiveAddr)
{
    s32 Status;

    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(ConfigPtr != NULL);

#if defined  (XCLOCKING)
    InstancePtr->Config.RefClk = ConfigPtr->RefClk;
    Xil_ClockEnable(InstancePtr->Config.RefClk);
#endif
    /* If this API is getting called twice, return value accordingly */
    if (InstancePtr->IsReady == XIL_COMPONENT_IS_READY) {
        Status = (s32)XST_DEVICE_IS_STARTED;
        goto RETURN_PATH ;
    }

    /* Set some default values. */
    InstancePtr->Config.DeviceId = ConfigPtr->DeviceId;
    InstancePtr->Config.BaseAddress = EffectiveAddr;
    InstancePtr->Config.InputClockHz = ConfigPtr->InputClockHz;
    InstancePtr->Config.CardDetect =  ConfigPtr->CardDetect;
    InstancePtr->Config.WriteProtect =  ConfigPtr->WriteProtect;
    InstancePtr->Config.BusWidth = ConfigPtr->BusWidth;
    InstancePtr->Config.BankNumber = ConfigPtr->BankNumber;
    InstancePtr->Config.HasEMIO = ConfigPtr->HasEMIO;
    InstancePtr->Config.IsCacheCoherent = ConfigPtr->IsCacheCoherent;
    InstancePtr->SectorCount = 0U;
    InstancePtr->Mode = XSDPS_DEFAULT_SPEED_MODE;
    InstancePtr->OTapDelay = 0U;
    InstancePtr->ITapDelay = 0U;
    InstancePtr->Dma64BitAddr = 0U;
    InstancePtr->SlcrBaseAddr = XPS_SYS_CTRL_BASEADDR;

    /* Host Controller version is read. */
    InstancePtr->HC_Version =
            (u8)(XSdPs_ReadReg16(InstancePtr->Config.BaseAddress,
            XSDPS_HOST_CTRL_VER_OFFSET) & XSDPS_HC_SPEC_VER_MASK);

    /*
     * Read capabilities register and update it in Instance pointer.
     * It is sufficient to read this once on power on.
     */
    InstancePtr->Host_Caps = XSdPs_ReadReg(InstancePtr->Config.BaseAddress,
                        XSDPS_CAPS_OFFSET);

    /* Reset the SD bus lines */
    Status = XSdPs_ResetConfig(InstancePtr);
    if (Status != XST_SUCCESS) {
        Status = XST_FAILURE;
        goto RETURN_PATH ;
    }

    /* Configure the SD Host Controller */
    XSdPs_HostConfig(InstancePtr);

    InstancePtr->IsReady = XIL_COMPONENT_IS_READY;

RETURN_PATH:
#if defined  (XCLOCKING)
    Xil_ClockDisable(InstancePtr->Config.RefClk);
#endif
    return Status;

}

/*****************************************************************************/
/**
*
* @brief
* Initialize Card with Identification mode sequence
*
*
* @param    InstancePtr is a pointer to the instance to be worked on.
*
* @return
*         - XST_SUCCESS if initialization was successful
*         - XST_FAILURE if failure - could be because
*             a) SD is already initialized
*             b) There is no card inserted
*             c) One of the steps (commands) in the
*               initialization cycle failed
*
*
******************************************************************************/
s32 XSdPs_CardInitialize(XSdPs *InstancePtr)
{
    s32 Status;

    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    /* Default settings */
    InstancePtr->BusWidth = XSDPS_1_BIT_WIDTH;
    InstancePtr->CardType = XSDPS_CARD_SD;
    InstancePtr->Switch1v8 = 0U;
    InstancePtr->BusSpeed = XSDPS_CLK_400_KHZ;

#if defined  (XCLOCKING)
    Xil_ClockEnable(InstancePtr->Config.RefClk);
#endif

    /* Change the clock frequency to 400 KHz */
    Status = XSdPs_Change_ClkFreq(InstancePtr, InstancePtr->BusSpeed);
    if (Status != XST_SUCCESS) {
        Status = XST_FAILURE;
        goto RETURN_PATH ;
    }

    /* Identify the Card whether it is SD, MMC or eMMC */
    Status = XSdPs_IdentifyCard(InstancePtr);
    if (Status != XST_SUCCESS) {
        Status = XST_FAILURE;
        goto RETURN_PATH;
    }

    /* Initialize the identified card */
    if (InstancePtr->CardType == XSDPS_CARD_SD) {
        Status = XSdPs_SdCardInitialize(InstancePtr);
        if (Status != XST_SUCCESS) {
            Status = XST_FAILURE;
            goto RETURN_PATH;
        }
    } else {
        Status = XSdPs_MmcCardInitialize(InstancePtr);
        if (Status != XST_SUCCESS) {
            Status = XST_FAILURE;
            goto RETURN_PATH;
        }
    }

RETURN_PATH:
#if defined  (XCLOCKING)
    Xil_ClockDisable(InstancePtr->Config.RefClk);
#endif
    return Status;
}

/*****************************************************************************/
/**
* @brief
* This function performs SD read in polled mode.
*
* @param    InstancePtr is a pointer to the instance to be worked on.
* @param    Arg is the address passed by the user that is to be sent as
*         argument along with the command.
* @param    BlkCnt - Block count passed by the user.
* @param    Buff - Pointer to the data buffer for a DMA transfer.
*
* @return
*         - XST_SUCCESS if initialization was successful
*         - XST_FAILURE if failure - could be because another transfer
*         is in progress or command or data inhibit is set
*
******************************************************************************/
s32 XSdPs_ReadPolled(XSdPs *InstancePtr, u32 Arg, u32 BlkCnt, u8 *Buff)
{
    s32 Status;

    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

#if defined  (XCLOCKING)
    Xil_ClockEnable(InstancePtr->Config.RefClk);
#endif

    /* Setup the Read Transfer */
    Status = XSdPs_SetupTransfer(InstancePtr);
    if (Status != XST_SUCCESS) {
        Status = XST_FAILURE;
        goto RETURN_PATH;
    }

    /* Read from the card */
    Status = XSdPs_Read(InstancePtr, Arg, BlkCnt, Buff);
    if (Status != XST_SUCCESS) {
        Status = XST_FAILURE;
        goto RETURN_PATH;
    }

RETURN_PATH:
#if defined  (XCLOCKING)
    Xil_ClockDisable(InstancePtr->Config.RefClk);
#endif
    return Status;
}

/*****************************************************************************/
/**
* @brief
* This function performs SD write in polled mode.
*
* @param    InstancePtr is a pointer to the instance to be worked on.
* @param    Arg is the address passed by the user that is to be sent as
*         argument along with the command.
* @param    BlkCnt - Block count passed by the user.
* @param    Buff - Pointer to the data buffer for a DMA transfer.
*
* @return
*         - XST_SUCCESS if initialization was successful
*         - XST_FAILURE if failure - could be because another transfer
*         is in progress or command or data inhibit is set
*
******************************************************************************/
s32 XSdPs_WritePolled(XSdPs *InstancePtr, u32 Arg, u32 BlkCnt, const u8 *Buff)
{
    s32 Status;

    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

#if defined  (XCLOCKING)
    Xil_ClockEnable(InstancePtr->Config.RefClk);
#endif

    /* Setup the Write Transfer */
    Status = XSdPs_SetupTransfer(InstancePtr);
    if (Status != XST_SUCCESS) {
        Status = XST_FAILURE;
        goto RETURN_PATH;
    }

    /* Write to the card */
    Status = XSdPs_Write(InstancePtr, Arg, BlkCnt, Buff);
    if (Status != XST_SUCCESS) {
        Status = XST_FAILURE;
        goto RETURN_PATH;
    }

RETURN_PATH:
#if defined  (XCLOCKING)
    Xil_ClockDisable(InstancePtr->Config.RefClk);
#endif
    return Status;
}

/*****************************************************************************/
/**
*
* @brief
* API to idle the SDIO Interface
*
*
* @param    InstancePtr is a pointer to the XSdPs instance.
*
* @return    None
*
* @note        None.
*
******************************************************************************/
s32 XSdPs_Idle(XSdPs *InstancePtr)
{
    s32 Status;

    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

#if defined  (XCLOCKING)
    Xil_ClockEnable(InstancePtr->Config.RefClk);
#endif

    /* Check if the bus is idle */
    Status = XSdPs_CheckBusIdle(InstancePtr, XSDPS_PSR_INHIBIT_CMD_MASK
                                        | XSDPS_PSR_INHIBIT_DAT_MASK
                                        | XSDPS_PSR_DAT_ACTIVE_MASK);
    if (Status != XST_SUCCESS) {
        Status = XST_FAILURE;
        goto RETURN_PATH ;
    }

    /* Disable the Bus Power */
    XSdPs_DisableBusPower(InstancePtr);

    /* Reset Command and Data Lines */
    Status = XSdPs_Reset(InstancePtr, XSDPS_SWRST_ALL_MASK);
    if (Status != XST_SUCCESS) {
        Status = XST_FAILURE;
        goto RETURN_PATH ;
    }

    Status = XST_SUCCESS;

RETURN_PATH:
#if defined  (XCLOCKING)
    Xil_ClockDisable(InstancePtr->Config.RefClk);
#endif
    return Status;
}
/** @} */
