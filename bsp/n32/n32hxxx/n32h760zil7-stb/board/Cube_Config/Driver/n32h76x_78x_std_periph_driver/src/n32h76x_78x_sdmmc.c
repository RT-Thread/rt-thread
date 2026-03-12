/**
*     Copyright (c) 2025, Nations Technologies Inc.
* 
*     All rights reserved.
*
*     This software is the exclusive property of Nations Technologies Inc. (Hereinafter 
* referred to as NATIONS). This software, and the product of NATIONS described herein 
* (Hereinafter referred to as the Product) are owned by NATIONS under the laws and treaties
* of the People's Republic of China and other applicable jurisdictions worldwide.
*
*     NATIONS does not grant any license under its patents, copyrights, trademarks, or other 
* intellectual property rights. Names and brands of third party may be mentioned or referred 
* thereto (if any) for identification purposes only.
*
*     NATIONS reserves the right to make changes, corrections, enhancements, modifications, and 
* improvements to this software at any time without notice. Please contact NATIONS and obtain 
* the latest version of this software before placing orders.

*     Although NATIONS has attempted to provide accurate and reliable information, NATIONS assumes 
* no responsibility for the accuracy and reliability of this software.
* 
*     It is the responsibility of the user of this software to properly design, program, and test 
* the functionality and safety of any application made of this information and any resulting product. 
* In no event shall NATIONS be liable for any direct, indirect, incidental, special,exemplary, or 
* consequential damages arising in any way out of the use of this software or the Product.
*
*     NATIONS Products are neither intended nor warranted for usage in systems or equipment, any
* malfunction or failure of which may cause loss of human life, bodily injury or severe property 
* damage. Such applications are deemed, "Insecure Usage".
*
*     All Insecure Usage shall be made at user's risk. User shall indemnify NATIONS and hold NATIONS 
* harmless from and against all claims, costs, damages, and other liabilities, arising from or related 
* to any customer's Insecure Usage.

*     Any express or implied warranty with regard to this software or the Product, including,but not 
* limited to, the warranties of merchantability, fitness for a particular purpose and non-infringement
* are disclaimed to the fullest extent permitted by law.

*     Unless otherwise explicitly permitted by NATIONS, anyone may not duplicate, modify, transcribe
* or otherwise distribute this software for any purposes, in whole or in part.
*
*     NATIONS products and technologies shall not be used for or incorporated into any products or systems
* whose manufacture, use, or sale is prohibited under any applicable domestic or foreign laws or regulations. 
* User shall comply with any applicable export control laws and regulations promulgated and administered by 
* the governments of any countries asserting jurisdiction over the parties or transactions.
**/

/**
 * @file n32h76x_78x_sdmmc.c
 * @author Nations
 * @version v1.0.0
 *
 * @copyright Copyright (c) 2025, Nations Technologies Inc. All rights reserved.
 */
#include "n32h76x_78x_sdmmc.h"
#include "n32h76x_78x_rcc.h"

/**
 *\*\name   SDMMC_DeInit.
 *\*\fun    Reset the SDMMCx peripheral registers to their default reset values.
 *\*\param  SDMMCx :
 *\*\          - SDMMC1
 *\*\          - SDMMC2
 *\*\return none
 */
void SDMMC_DeInit(SDMMC_Module* SDMMCx)
{
    if (SDMMCx == SDMMC1)
    {
        RCC_EnableAXIPeriphReset1(RCC_AXI_PERIPHRST_SDMMC1);
        RCC_EnableAXIPeriphReset1(RCC_AXI_PERIPHRST_SDHOST1);
    }
    else if (SDMMCx == SDMMC2)
    {
        RCC_EnableAHB1PeriphReset1(RCC_AHB1_PERIPHRST_SDMMC2);
        RCC_EnableAHB1PeriphReset1(RCC_AHB1_PERIPHRST_SDHOST2);
    }
    else
    {
        /* no process */
    }
}


/**
 *\*\name   SDMMC_WrapperConfig.
 *\*\fun    Initializes the SDMMC peripheral according to the specified
 *\*\       parameters in the SDMMC_WrapperParam.
 *\*\fun    Configure SDMMC wrapper register values.
 *\*\param  SDMMCx pointer to specified SDMMC,must be one of the following value:
 *\*\          - SDMMC1
 *\*\          - SDMMC2
 *\*\param  SDMMC_WrapperParam: pointer to a SDMMC_WrapperType structure.
 *\*\           - MaxBlockLen  : Maximum Block Length supported by the Core/Device
 *\*\               - SDMMC_MAXBLOCKLEN_512B
 *\*\               - SDMMC_MAXBLOCKLEN_1024B
 *\*\               - SDMMC_MAXBLOCKLEN_2048B
 *\*\           - SDBaseCLKFreq :  xin_clk, Base Clock Frequency for SD Clock
 *\*\               - 0x0A~0x68,Unit MHz
 *\*\           - TimeOutUnit   :  the unit of base clock frequency used to detect Data Timeout Error
 *\*\               - SDMMC_TIMEOUTCLKUNIT_KHZ
 *\*\               - SDMMC_TIMEOUTCLKUNIT_MHZ
 *\*\           - TuningCNT     : the number of delay taps that are supported for tuning the rxclk_in
 *\*\               - 0x00~0x20
 *\*\           - WKUPSignalMode :   Wakeup Signal Generation Mode
 *\*\               - SDMMC_SYNCWKUP
 *\*\               - SDMMC_ASYNCWKUP
 *\*\           - SPIBlockMode  :    SPI Block Mode
 *\*\               - SDMMC_SPIBLOCKMODESUPPORT
 *\*\               - SDMMC_SPIBLOCKMODEUNSUPPORT
 *\*\           - SPIMode       :   SPI Mode Support
 *\*\               - SDMMC_SPIMODESUPPORT
 *\*\               - SDMMC_SPIMODEUNSUPPORT
 *\*\           - DDR50         : DDR50 Support
 *\*\               - SDMMC_DDR50SUPPORT
 *\*\               - SDMMC_DDR50UNSUPPORT
 *\*\           - SDR104        : SDR104 Support
 *\*\               - SDMMC_SDR104SUPPORT
 *\*\               - SDMMC_SDR104UNSUPPORT
 *\*\           - SDR50         : SDR50 Support
 *\*\               - SDMMC_SDR50SUPPORT
 *\*\               - SDMMC_SDR50UNSUPPORT
 *\*\           - SlotType      : Slot Type
 *\*\               - SDMMC_SDTYPE
 *\*\               - SDMMC_EMMCTYPE
 *\*\           - AsyncInt      : Asynchronous Interrupt Support
 *\*\               - SDMMC_ASYNCINTSUPPORT
 *\*\               - SDMMC_ASYNCINTUNSUPPORT
 *\*\           - Suspend_Resume : Suspend/Resume Support
 *\*\               - SDMMC_SUSRESSUPPORT
 *\*\               - SDMMC_SUSRESUNSUPPORT
 *\*\           - SDMA           : SDMA Support
 *\*\               - SDMMC_SDMASUPPORT
 *\*\               - SDMMC_SDMAUNSUPPORT
 *\*\           - HS             : High Speed Support
 *\*\               - SDMMC_HSSUPPORT
 *\*\               - SDMMC_HSUNSUPPORT
 *\*\           - ADMA2          : ADMA2 Support
 *\*\               - SDMMC_ADMA2SUPPORT
 *\*\               - SDMMC_ADMA2UNSUPPORT
 *\*\           - Embedded_8bit   : 8-bit Support for Embedded Device
 *\*\               - SDMMC_EMBEDDEDSUPPORT
 *\*\               - SDMMC_EMBEDDEDUNSUPPORT
 *\*\           - UseTuningSDR50  : Use Tuning for SDR50
 *\*\               - SDMMC_SDR50TUNING
 *\*\               - SDMMC_SDR50UNTUNING
 *\*\           - DSSDCLKFreq      : SDCLK Frequency Select Value for Default Speed
 *\*\               - 0x00~0x3FF ; 2N frequency division
 *\*\           - INITSDCLKFreq    :SDCLK Frequency Select Value for Initialization
 *\*\               - 0x00~0x3FF ; 2N frequency division
 *\*\           - SDR12SDCLKFreq  : SDCLK Frequency Select Value for SDR12
 *\*\               - 0x00~0x3FF ; 2N frequency division
 *\*\           - HSSDCLKFreq     : SDCLK Frequency Select Value for High Speed
 *\*\               - 0x00~0x3FF ; 2N frequency division
 *\*\           - SDR50SDCLKFreq  : SDCLK Frequency Select Value for SDR50
 *\*\               - 0x00~0x3FF ; 2N frequency division
 *\*\           - SDR25SDCLKFreq   : SDCLK Frequency Select Value for SDR25
 *\*\               - 0x00~0x3FF ; 2N frequency division
 *\*\           - SDR104SDCLKFreq  : SDCLK Frequency Select Value for SDR104
 *\*\               - 0x00~0x3FF ; 2N frequency division
 *\*\           - DDR50SDCLKFreq   : SDCLK Frequency Select Value for DDR50
 *\*\               - 0x00~0x3FF ; 2N frequency division
 *\*\return ErrorStatus
 *\*\          - SUCCESS
 *\*\          - ERROR
 *\*\note  This function can only be used when SDMMC is not working.
 *\*       Call configuration support function before SD initialization.
 */
ErrorStatus SDMMC_WrapperConfig(SDMMC_Module* SDMMCx, SDMMC_WrapperType *SDMMC_WrapperParam)
{
    uint32_t tempReg;
    SDHOST_Module* SDHOSTx;

    if(SDMMCx == SDMMC1)
    {
        SDHOSTx = SDHOST1;
    }
    else
    {
        SDHOSTx = SDHOST2;
    }

    /* The SDMMC registers can only be configured when SDMMC is not operational */
    if((SDHOSTx->PRESTS & (SDHOST_PRESTS_RTRANACT | SDHOST_PRESTS_WTRANACT)) != RESET)
    {
        return ERROR;
    }

    /* Configure SDMMC_CFG1, including block length, xin_clk size,Timeout Clock Unit,
       Tuning Count, Wakeup Signal Generation Mode */
    tempReg = SDMMCx->CFG1;
    tempReg &= (~(SDMMC_CFG1_MBL | SDMMC_CFG1_BCLKF | SDMMC_CFG1_TCLKU | SDMMC_CFG1_TCNT | SDMMC_CFG1_WSGM));
    tempReg |= (SDMMC_WrapperParam->MaxBlockLen | (SDMMC_WrapperParam->SDBaseCLKFreq << SDMMC_CFG1_BCLKF_OFFSET) | SDMMC_WrapperParam->TimeOutUnit \
                | (SDMMC_WrapperParam->TuningCNT << SDMMC_CFG1_TCNT_OFFSET) | SDMMC_WrapperParam->WKUPSignalMode);
    SDMMCx->CFG1 = tempReg;

    /* Configure SDMMC_CFG2, including SPI block mode, SPI mode,DDR50,SDR104,SDR50,Slot Type,
       Asynchronous Interrupt,Suspend/Resume Support,SDMA,HS,ADMA2,8-bit Support for Embedded Device */
    tempReg = SDMMCx->CFG2;
    tempReg &= (~(SDMMC_CFG2_SPIBMOD | SDMMC_CFG2_SPIMOD | SDMMC_CFG2_DDR50 | SDMMC_CFG2_SDR104 | SDMMC_CFG2_SDR50 \
                  | SDMMC_CFG2_STYP | SDMMC_CFG2_ASYNCINT | SDMMC_CFG2_SDMA | SDMMC_CFG2_HS | SDMMC_CFG2_ADMA2 | SDMMC_CFG2_EMBUS));
    tempReg |= (SDMMC_WrapperParam->SPIBlockMode | SDMMC_WrapperParam->SPIMode | SDMMC_WrapperParam->DDR50 \
                | SDMMC_WrapperParam->SDR104 | SDMMC_WrapperParam->SDR50 | SDMMC_WrapperParam->SlotType  \
                | SDMMC_WrapperParam->AsyncInt | SDMMC_WrapperParam->Suspend_Resume | SDMMC_WrapperParam->SDMA  \
                | SDMMC_WrapperParam->HS  | SDMMC_WrapperParam->ADMA2 | SDMMC_WrapperParam->Embedded_8bit);
    SDMMCx->CFG2 = tempReg;

    /* Configure SDMMC_CFG3, including Use Tuning for SDR50 */
    tempReg = SDMMCx->CFG3;
    tempReg &= (~SDMMC_CFG3_UTFSDR50);
    tempReg |= SDMMC_WrapperParam->UseTuningSDR50;
    SDMMCx->CFG3 = tempReg;

    /* Configure SDMMC_PV0CTRL, including SDCLK Frequency Select Value for Default Speed and Initialization */
    tempReg = SDMMCx->PV0CTRL;
    tempReg &= (~(SDMMC_PV0CTRL_CLKFS_DS | SDMMC_PV0CTRL_CLKFS_INIT));
    tempReg |= ((SDMMC_WrapperParam->DSSDCLKFreq << SDMMC_PV0CTRL_CLKFS_OFFSET) | SDMMC_WrapperParam->INITSDCLKFreq);
    SDMMCx->PV0CTRL = tempReg;

    /* Configure SDMMC_PV1CTRL, including SDCLK Frequency Select Value for SDR12 and HS */
    tempReg = SDMMCx->PV1CTRL;
    tempReg &= (~(SDMMC_PV1CTRL_CLKFS_SDR12 | SDMMC_PV1CTRL_CLKFS_HS));
    tempReg |= ((SDMMC_WrapperParam->SDR12SDCLKFreq << SDMMC_PV0CTRL_CLKFS_OFFSET) | SDMMC_WrapperParam->HSSDCLKFreq);
    SDMMCx->PV1CTRL = tempReg;

    /* Configure SDMMC_PV2CTRL, including SDCLK Frequency Select Value for SDR50 and SDR25 */
    tempReg = SDMMCx->PV2CTRL;
    tempReg &= (~(SDMMC_PV2CTRL_CLKFS_SDR50 | SDMMC_PV2CTRL_CLKFS_SDR25));
    tempReg |= ((SDMMC_WrapperParam->SDR50SDCLKFreq << SDMMC_PV0CTRL_CLKFS_OFFSET) | SDMMC_WrapperParam->SDR25SDCLKFreq);
    SDMMCx->PV2CTRL = tempReg;

    /* Configure SDMMC_PV3CTRL, including SDCLK Frequency Select Value for DDR50 and SDR104 */
    tempReg = SDMMCx->PV3CTRL;
    tempReg &= (~(SDMMC_PV3CTRL_CLKFS_SDR104 | SDMMC_PV3CTRL_CLKFS_DDR50));
    tempReg |= ((SDMMC_WrapperParam->SDR104SDCLKFreq << SDMMC_PV0CTRL_CLKFS_OFFSET) | SDMMC_WrapperParam->DDR50SDCLKFreq);
    SDMMCx->PV3CTRL = tempReg;

    return SUCCESS;
}


/**
 *\*\name   SDMMC_StructWrapperInit.
 *\*\fun    Fills each SDMMC_WrapperStruct member with its default value.
 *\*\param  SDMMC_WrapperStruct: pointer to a SDMMC_WrapperType structure.
 *\*\           - MaxBlockLen
 *\*\           - SDBaseCLKFreq
 *\*\           - TimeOutUnit
 *\*\           - TuningCNT
 *\*\           - WKUPSignalMode
 *\*\           - SPIBlockMode
 *\*\           - SPIMode
 *\*\           - DDR50
 *\*\           - SDR104
 *\*\           - SDR50
 *\*\           - SlotType
 *\*\           - AsyncInt
 *\*\           - Suspend_Resume
 *\*\           - SDMA
 *\*\           - HS
 *\*\           - ADMA2
 *\*\           - Embedded_8bit
 *\*\           - UseTuningSDR50
 *\*\           - DSSDCLKFreq
 *\*\           - INITSDCLKFreq
 *\*\           - SDR12SDCLKFreq
 *\*\           - HSSDCLKFreq
 *\*\           - SDR50SDCLKFreq
 *\*\           - SDR25SDCLKFreq
 *\*\           - SDR104SDCLKFreq
 *\*\           - DDR50SDCLKFreq
 *\*\return none
 */
void SDMMC_StructWrapperInit(SDMMC_WrapperType *SDMMC_WrapperStruct)
{
    /* SDMMC_WrapperStruct members default value */
    SDMMC_WrapperStruct->MaxBlockLen     = SDMMC_MAXBLOCKLEN_512B;
    SDMMC_WrapperStruct->SDBaseCLKFreq   = 0x68;
    SDMMC_WrapperStruct->TimeOutUnit     = SDMMC_TIMEOUTCLKUNIT_KHZ;
    SDMMC_WrapperStruct->TuningCNT       = 0x20;
    SDMMC_WrapperStruct->WKUPSignalMode  = SDMMC_ASYNCWKUP;
    SDMMC_WrapperStruct->SPIBlockMode    = SDMMC_SPIBLOCKMODEUNSUPPORT;
    SDMMC_WrapperStruct->SPIMode         = SDMMC_SPIMODEUNSUPPORT;
    SDMMC_WrapperStruct->DDR50           = SDMMC_DDR50SUPPORT;
    SDMMC_WrapperStruct->SDR104          = SDMMC_SDR104SUPPORT;
    SDMMC_WrapperStruct->SDR50           = SDMMC_SDR50SUPPORT;
    SDMMC_WrapperStruct->SlotType        = SDMMC_SDTYPE;
    SDMMC_WrapperStruct->AsyncInt        = SDMMC_ASYNCINTSUPPORT;
    SDMMC_WrapperStruct->Suspend_Resume  = SDMMC_SUSRESUNSUPPORT;
    SDMMC_WrapperStruct->SDMA            = SDMMC_SDMASUPPORT;
    SDMMC_WrapperStruct->HS              = SDMMC_HSSUPPORT;
    SDMMC_WrapperStruct->ADMA2           = SDMMC_ADMA2SUPPORT;
    SDMMC_WrapperStruct->Embedded_8bit   = SDMMC_EMBEDDEDUNSUPPORT;
    SDMMC_WrapperStruct->UseTuningSDR50  = SDMMC_SDR50TUNING;
    SDMMC_WrapperStruct->DSSDCLKFreq     = 0x04;
    SDMMC_WrapperStruct->INITSDCLKFreq   = 0x00;
    SDMMC_WrapperStruct->SDR12SDCLKFreq  = 0x04;
    SDMMC_WrapperStruct->HSSDCLKFreq     = 0x02;
    SDMMC_WrapperStruct->SDR50SDCLKFreq  = 0x01;
    SDMMC_WrapperStruct->SDR25SDCLKFreq  = 0x02;
    SDMMC_WrapperStruct->SDR104SDCLKFreq = 0x00;
    SDMMC_WrapperStruct->DDR50SDCLKFreq  = 0x02;
}


/**
 *\*\name   SDMMC_SoftWareReset.
 *\*\fun    Software Reset for DAT/CMD/ALL Line.
 *\*\param  SDHOSTx pointer to specified SDHOST,must be one of the following value:
 *\*\          - SDHOST1
 *\*\          - SDHOST2
 *\*\param  LineMask:
 *\*\          - SDHOST_SOFTWARE_DATALINE
 *\*\          - SDHOST_SOFTWARE_CMDLINE
 *\*\          - SDHOST_SOFTWARE_ALLLINE
 *\*\return ErrorStatus
 *\*\          - SUCCESS
 *\*\          - ERROR
 */
ErrorStatus SDMMC_SoftWareReset(SDHOST_Module* SDHOSTx, uint32_t LineMask)
{
    ErrorStatus stauts_value;
    uint32_t timeout = 0;
    /* Reset ALL SDHOST. */
    SDHOSTx->CTRL2 |= LineMask;

    while((SDHOSTx->CTRL2 & LineMask) != RESET)
    {
        timeout++;

        if(timeout >= SDMMC_TIMEOUT_VALUE)
        {
            break;
        }
    }

    if(timeout >= SDMMC_TIMEOUT_VALUE)
    {
        stauts_value = ERROR;
    }
    else
    {
        stauts_value = SUCCESS;
    }

    return stauts_value;
}


/**
 *\*\name   SDMMC_TransferConfig.
 *\*\fun    Start transfer according to current transfer state.
 *\*\param  SDHOSTx pointer to specified SDHOST,must be one of the following value:
 *\*\          - SDHOST1
 *\*\          - SDHOST2
 *\*\param  transferFlags: transfer flags
 *\*\           - SDMMC_CommandOnly
 *\*\           - SDMMC_CommandAndTxData
 *\*\           - SDMMC_CommandAndRxData
 *\*\           - SDMMC_DataWithAutoCmd12
 *\*\           - SDMMC_DataWithAutoCmd23
 *\*\           - SDMMC_BootData
 *\*\           - SDMMC_BootDataContinuous
 *\*\param  blockCount  :
 *\*\           - The available range is 0 ~ 0xFFFF.
 *\*\param  blockSize  :
 *\*\           - The available range is 0 ~ 0x0800.
 *\*\param  TMODE_struct: pointer to a SDHOST_TMODE_struct structure.
 *\*\           - DMAE
 *\*\                - SDHOST_TMODE_DMADISABLE
 *\*\                - SDHOST_TMODE_DMAENABLE
 *\*\           - BCNTE
 *\*\                - SDHOST_TMODE_BLOCKCNTDISABLE
 *\*\                - SDHOST_TMODE_BLOCKCNTENABLE
 *\*\           - ACMDE
 *\*\                - SDHOST_TMODE_NOACMDEN
 *\*\                - SDHOST_TMODE_AC12EN
 *\*\                - SDHOST_TMODE_AC23EN
 *\*\           - DATDIR
 *\*\                - SDHOST_TMODE_DATDIR_WRITE
 *\*\                - SDHOST_TMODE_DATDIR_READ
 *\*\           - BLKSEL
 *\*\                - SDHOST_TMODE_SINGLEBLK
 *\*\                - SDHOST_TMODE_MULTIBLK
 *\*\return SDMMC_STS
 *\*\           - SDMMC_BusyTransferring
 *\*\           - SDMMC_SUCCESS
 *\*\           - SDMMC_ERROR
 */
static SDMMC_STS SDMMC_TransferConfig(SDHOST_Module* SDHOSTx, uint32_t transferFlags, uint32_t blockSize,
                                      uint32_t blockCount, SDHOST_TMODE_struct *TMODE_struct)
{
    uint32_t tempReg_BLK;

    if((transferFlags & ((uint32_t)SDMMC_CommandOnly)) != 0U)
    {
        /* clear data flags */
        TMODE_struct->DATDIR = SDHOST_TMODE_DATDIR_WRITE;
        TMODE_struct->BCNTE = SDHOST_TMODE_BLOCKCNTDISABLE;
        TMODE_struct->ACMDE = SDHOST_TMODE_NOACMDEN;
        TMODE_struct->BLKSEL = SDHOST_TMODE_SINGLEBLK;

        if((SDHOSTx->PRESTS & SDHOST_PRESTS_CMDINHC) == SDHOST_PRESTS_CMDINHC)
        {
            return SDMMC_BusyTransferring;
        }
    }
    else
    {
        /* if transfer boot continous, only need set the CONTREQ bit, leave others as it is */
        if((transferFlags & ((uint32_t)SDMMC_BootDataContinuous)) != 0U)
        {
            /* clear stop at block gap request */
            SDHOSTx->CTRL1 &= ~SDHOST_CTRL1_SABGREQ;
            /* continous transfer data */
            SDHOSTx->CTRL1 |= SDHOST_CTRL1_CONTREQ;
            return SDMMC_SUCCESS;
        }

        /* check data inhibit flag */
        if((SDHOSTx->PRESTS & SDHOST_PRESTS_CMDINHD) == SDHOST_PRESTS_CMDINHD)
        {
            return SDMMC_BusyTransferring;
        }

        /* check transfer block count */
        if ((blockCount > SDHOST_MAX_BLOCK_COUNT))
        {
            return SDMMC_ERROR;
        }

        /* config mix parameter */
        TMODE_struct->DATDIR = SDHOST_TMODE_DATDIR_WRITE;
        TMODE_struct->BCNTE = SDHOST_TMODE_BLOCKCNTDISABLE;
        TMODE_struct->ACMDE = SDHOST_TMODE_NOACMDEN;
        TMODE_struct->BLKSEL = SDHOST_TMODE_SINGLEBLK;

        if((transferFlags & ((uint32_t)SDMMC_CommandAndRxData)) != 0U)
        {
            TMODE_struct->DATDIR = SDHOST_TMODE_DATDIR_READ;
        }

        if(blockCount > 1U)
        {
            TMODE_struct->BCNTE = SDHOST_TMODE_BLOCKCNTENABLE;
            TMODE_struct->BLKSEL = SDHOST_TMODE_MULTIBLK;

            /* auto command 12 */
            if((transferFlags & ((uint32_t)SDMMC_DataWithAutoCmd12)) != 0U)
            {
                TMODE_struct->ACMDE = SDHOST_TMODE_AC12EN;
            }
        }

        /* auto command 23, auto send set block count cmd before multiple read/write */
        if ((transferFlags & ((uint32_t)SDMMC_DataWithAutoCmd23)) != 0U)
        {
            TMODE_struct->ACMDE = SDHOST_TMODE_AC23EN;
            /* config the block count to DS_ADDR */
            SDHOSTx->DSADD = blockCount;
        }

        /* if transfer boot data, leave the block count to SDMMC_SetMmcBootConfig function */
        if ((transferFlags & ((uint32_t)SDMMC_BootData)) == 0U)
        {
            /* config data block size/block count */
            tempReg_BLK = SDHOSTx->BLKCFG;
            tempReg_BLK &= (~(SDHOST_BLKCFG_CNT | SDHOST_BLKCFG_SIZE));
            tempReg_BLK |= ((blockCount << SDHOST_BLOCK_COUNT_OFFSET) | blockSize);
            SDHOSTx->BLKCFG = tempReg_BLK;
        }
        else
        {
            TMODE_struct->BCNTE = SDHOST_TMODE_BLOCKCNTENABLE;
            TMODE_struct->BLKSEL = SDHOST_TMODE_MULTIBLK;
        }
    }

    return SDMMC_SUCCESS;
}


/**
 *\*\name   SDMMC_ReceiveCommandResponse.
 *\*\fun    Receive command response.
 *\*\param  SDHOSTx pointer to specified SDHOST,must be one of the following value:
 *\*\          - SDHOST1
 *\*\          - SDHOST2
 *\*\param  command: Command to be sent
 *\*\           - index
 *\*\               - 0~63
 *\*\           - argument
 *\*\               - 0x00000000~0xFFFFFFFF
 *\*\           - type
 *\*\               - CARD_CommandTypeNormal
 *\*\               - CARD_CommandTypeSuspend
 *\*\               - CARD_CommandTypeResume
 *\*\               - CARD_CommandTypeAbort
 *\*\               - CARD_CommandTypeEmpty
 *\*\           - responseType
 *\*\               - CARD_ResponseTypeNone
 *\*\               - CARD_ResponseTypeR1
 *\*\               - CARD_ResponseTypeR1b
 *\*\               - CARD_ResponseTypeR2
 *\*\               - CARD_ResponseTypeR3
 *\*\               - CARD_ResponseTypeR4
 *\*\               - CARD_ResponseTypeR5
 *\*\               - CARD_ResponseTypeR5b
 *\*\               - CARD_ResponseTypeR6
 *\*\               - CARD_ResponseTypeR7
 *\*\           - response[4U]: Response for this command.
 *\*\               - 0x00000000~0xFFFFFFFF
 *\*\           - responseErrorFlags: Response error flag, which need to check the command reponse.
 *\*\               - 0x00000000~0xFFFFFFFF
 *\*\           - flags: Cmd flags.
 *\*\               - 0x00000000~0xFFFFFFFF
 *\*\return SDMMC_STS
 *\*\           - SDMMC_SendCommandFailed
 *\*\           - SDMMC_SUCCESS
 */
static SDMMC_STS SDMMC_ReceiveCommandResponse(SDHOST_Module* SDHOSTx, SDMMC_CMD *command)
{
    uint32_t response0 = SDHOSTx->CMDRSP0;
    uint32_t response1 = SDHOSTx->CMDRSP1;
    uint32_t response2 = SDHOSTx->CMDRSP2;

    if (command->responseType != CARD_ResponseTypeNone)
    {
        command->response[0U] = response0;

        if (command->responseType == CARD_ResponseTypeR2)
        {
            /* R3-R2-R1-R0(lowest 8 bit is invalid bit) has the same format as R2 format in SD specification document
            after removed internal CRC7 and end bit. */
            command->response[0U] <<= 8U;
            command->response[1U] = (response1 << 8U) | ((response0 & 0xFF000000U) >> 24U);
            command->response[2U] = (response2 << 8U) | ((response1 & 0xFF000000U) >> 24U);
            command->response[3U] = (SDHOSTx->CMDRSP3 << 8U) | ((response2 & 0xFF000000U) >> 24U);
        }
    }

    /* check response error flag */
    if ((command->responseErrorFlags != 0U) &&
            ((command->responseType == CARD_ResponseTypeR1) || (command->responseType == CARD_ResponseTypeR1b) ||
             (command->responseType == CARD_ResponseTypeR6) || (command->responseType == CARD_ResponseTypeR5)))
    {
        if (((command->responseErrorFlags) & (command->response[0U])) != 0U)
        {
            return SDMMC_SendCommandFailed;
        }
    }

    return SDMMC_SUCCESS;
}


/**
 *\*\name   SDMMC_ReadDataPort.
 *\*\fun    Read DATAPORT when buffer enable bit is set.
 *\*\param  SDHOSTx :
 *\*\          - SDHOST1
 *\*\          - SDHOST2
 *\*\param  data  Data descriptor.
 *\*\          - AutoCommand12_23.
 *\*\              - AutoCommand12
 *\*\              - AutoCommand23
 *\*\              - NoAutoCommand
 *\*\          - enableIgnoreError.
 *\*\              - ENABLE
 *\*\              - DISABLE
 *\*\          - dataType.
 *\*\              - SDHOST_TransferDataNormal
 *\*\              - SDHOST_TransferDataTuning
 *\*\              - SDHOST_TransferDataBoot
 *\*\              - SDHOST_TransferDataBootcontinous
 *\*\           - blockCount  :
 *\*\               - The available range is 0 ~ 0xFFFF.
 *\*\           - blockSize  :
 *\*\               - The available range is 0 ~ 0x0800.
 *\*\           - rxData  :  Buffer to save data read.
 *\*\           - txData  :  Data buffer to write.
 *\*\param  transferredWords  The number of data words have been transferred last time transaction.
 *\*\           - The available range is 0 ~ 0xFFFFFFFF.
 *\*\return transferredWords : The number of total data words have been transferred after this time transaction.
 */
static uint32_t SDMMC_ReadDataPort(SDHOST_Module* SDHOSTx, SDMMC_DATA *data, uint32_t transferredWords)
{
    uint32_t i;
    uint32_t blockWords;
    uint32_t transferredWordsvalue = transferredWords;

    /* If DMA is enable, do not need to polling data port */
    if ((SDHOSTx->TMODE & SDHOST_TMODE_DMAE) == 0U)
    {
        /*
         * Add non aligned access support ,user need make sure your buffer size is big
         * enough to hold the data,in other words,user need make sure the buffer size
         * is 4 byte aligned
         */
        if ((data->blockSize % 4U) != 0U)
        {
            data->blockSize += (4U - (data->blockSize % 4U)); /* make the block size as word-aligned */
        }

        blockWords = data->blockSize / 4U;

        i = 0U;

        while (i < blockWords)
        {
            data->rxData[transferredWordsvalue] = SDMMC_ReadData(SDHOSTx);
            transferredWordsvalue++;
            i++;
        }
    }

    return transferredWordsvalue;
}

/**
 *\*\name   SDMMC_ReadByDataPortBlocking.
 *\*\fun    Read data by using DATAPORT polling way.
 *\*\param  SDHOSTx :
 *\*\          - SDHOST1
 *\*\          - SDHOST2
 *\*\param  data  Data descriptor.
 *\*\          - AutoCommand12_23.
 *\*\              - AutoCommand12
 *\*\              - AutoCommand23
 *\*\              - NoAutoCommand
 *\*\          - enableIgnoreError.
 *\*\              - ENABLE
 *\*\              - DISABLE
 *\*\          - dataType.
 *\*\              - SDHOST_TransferDataNormal
 *\*\              - SDHOST_TransferDataTuning
 *\*\              - SDHOST_TransferDataBoot
 *\*\              - SDHOST_TransferDataBootcontinous
 *\*\           - blockCount  :
 *\*\               - The available range is 0 ~ 0xFFFF.
 *\*\           - blockSize  :
 *\*\               - The available range is 0 ~ 0x0800.
 *\*\           - rxData  :  Buffer to save data read.
 *\*\           - txData  :  Data buffer to write.
 *\*\return error_status.
 *\*\           - SUCCESS
 *\*\           - ERROR
 */
static ErrorStatus SDMMC_ReadByDataPortBlocking(SDHOST_Module* SDHOSTx, SDMMC_DATA *data)
{
    uint32_t totalWords;
    uint32_t transferredWords = 0U, interruptStatus = 0U;
    ErrorStatus error_status = SUCCESS;
    uint32_t timeout = 0xFFFFFF;

    /*
     * Add non aligned access support ,user need make sure your buffer size is big
     * enough to hold the data,in other words,user need make sure the buffer size
     * is 4 byte aligned
     */
    if ((data->blockSize % 4U) != 0U)
    {
        data->blockSize += (4U - (data->blockSize % 4U)); /* make the block size as word-aligned */
    }

    totalWords = (data->blockCount * data->blockSize) / 4U;

    while ((error_status == SUCCESS) && (transferredWords < totalWords))
    {
        timeout = 0xFFFFFF;
        while((interruptStatus & (((uint32_t)SDHOST_BufferReadReadyFlag | (uint32_t)SDHOST_DataErrorFlag))) == 0)
        {
            interruptStatus = SDHOSTx->INTSTS;
            timeout--;

            if(timeout < 2)
            {
                break;
            }
        }

        /* during std tuning process, software do not need to read data, but wait BRR is enough */
        if ((data->dataType == (uint32_t)SDHOST_TransferDataTuning) &&
                ((interruptStatus & ((uint32_t)SDHOST_BufferReadReadyFlag)) != 0))
        {
            SDMMC_ClrFlag(SDHOSTx, (uint32_t)SDHOST_BufferReadReadyFlag);
            return SUCCESS;
        }
        else if ((interruptStatus & ((uint32_t)SDHOST_DataErrorFlag)) != 0)
        {
            if (data->enableIgnoreError == ENABLE)
            {
                error_status = ERROR;
            }

            /* clear data error flag */
            SDMMC_ClrFlag(SDHOSTx, (uint32_t)SDHOST_DataErrorFlag);
        }
        else
        {
            /* Intentional empty */
        }

        if (error_status == SUCCESS)
        {
            /* clear buffer read ready */
            SDMMC_ClrFlag(SDHOSTx, (uint32_t)SDHOST_BufferReadReadyFlag);
            interruptStatus = 0U;
            transferredWords = SDMMC_ReadDataPort(SDHOSTx, data, transferredWords);
        }
    }

    timeout = 0xFFFFFF;
    while((interruptStatus & ((uint32_t)SDHOST_DataCompleteFlag)) == 0)
    {
        interruptStatus = SDHOSTx->INTSTS;
        timeout--;

        if(timeout < 2)
        {
            break;
        }
    }
    /* Clear data complete flag after the last read operation. */
    SDMMC_ClrFlag(SDHOSTx, (uint32_t)SDHOST_DataCompleteFlag);

    return error_status;
}


/**
 *\*\name   SDMMC_WriteDataPort.
 *\*\fun    Write DATAPORT when buffer enable bit is set.
 *\*\param  SDHOSTx :
 *\*\          - SDHOST1
 *\*\          - SDHOST2
 *\*\param  data  Data descriptor.
 *\*\          - AutoCommand12_23.
 *\*\              - AutoCommand12
 *\*\              - AutoCommand23
 *\*\              - NoAutoCommand
 *\*\          - enableIgnoreError.
 *\*\              - ENABLE
 *\*\              - DISABLE
 *\*\          - dataType.
 *\*\              - SDHOST_TransferDataNormal
 *\*\              - SDHOST_TransferDataTuning
 *\*\              - SDHOST_TransferDataBoot
 *\*\              - SDHOST_TransferDataBootcontinous
 *\*\           - blockCount  :
 *\*\               - The available range is 0 ~ 0xFFFF.
 *\*\           - blockSize  :
 *\*\               - The available range is 0 ~ 0x0800.
 *\*\           - rxData  :  Buffer to save data read.
 *\*\           - txData  :  Data buffer to write.
 *\*\param  transferredWords  The number of data words have been transferred last time transaction.
 *\*\           - The available range is 0 ~ 0xFFFFFFFF.
 *\*\return transferredWords : The number of total data words have been transferred after this time transaction.
 */
static uint32_t SDMMC_WriteDataPort(SDHOST_Module* SDHOSTx, SDMMC_DATA *data, uint32_t transferredWords)
{
    uint32_t i;
    uint32_t blockWords;
    uint32_t transferredWordsvalue = transferredWords;

    /* If DMA is enable, do not need to polling data port */
    if ((SDHOSTx->TMODE & SDHOST_TMODE_DMAE) == 0U)
    {
        /*
         * Add non aligned access support ,user need make sure your buffer size is big
         * enough to hold the data,in other words,user need make sure the buffer size
         * is 4 byte aligned
         */
        if ((data->blockSize % sizeof(uint32_t)) != 0U)
        {
            data->blockSize +=
                sizeof(uint32_t) - (data->blockSize % sizeof(uint32_t)); /* make the block size as word-aligned */
        }

        blockWords = data->blockSize / sizeof(uint32_t);

        i = 0U;

        while (i < blockWords)
        {
            SDMMC_WriteData(SDHOSTx, data->txData[transferredWordsvalue]);
            transferredWordsvalue++;
            i++;
        }
    }

    return transferredWordsvalue;
}


/**
 *\*\name   SDMMC_ReadByDataPortBlocking.
 *\*\fun    Write data by using DATAPORT polling way.
 *\*\param  SDHOSTx :
 *\*\          - SDHOST1
 *\*\          - SDHOST2
 *\*\param  data  Data descriptor.
 *\*\          - AutoCommand12_23.
 *\*\              - AutoCommand12
 *\*\              - AutoCommand23
 *\*\              - NoAutoCommand
 *\*\          - enableIgnoreError.
 *\*\              - ENABLE
 *\*\              - DISABLE
 *\*\          - dataType.
 *\*\              - SDHOST_TransferDataNormal
 *\*\              - SDHOST_TransferDataTuning
 *\*\              - SDHOST_TransferDataBoot
 *\*\              - SDHOST_TransferDataBootcontinous
 *\*\           - blockCount  :
 *\*\               - The available range is 0 ~ 0xFFFF.
 *\*\           - blockSize  :
 *\*\               - The available range is 0 ~ 0x0800.
 *\*\           - rxData  :  Buffer to save data read.
 *\*\           - txData  :  Data buffer to write.
 *\*\return error_status.
 *\*\           - SUCCESS
 *\*\           - ERROR
 */
static ErrorStatus SDMMC_WriteByDataPortBlocking(SDHOST_Module* SDHOSTx, SDMMC_DATA *data)
{
    uint32_t totalWords;

    uint32_t transferredWords = 0U, interruptStatus = 0U;
    ErrorStatus error_status = SUCCESS;

    /*
     * Add non aligned access support ,user need make sure your buffer size is big
     * enough to hold the data,in other words,user need make sure the buffer size
     * is 4 byte aligned
     */
    if ((data->blockSize % sizeof(uint32_t)) != 0U)
    {
        data->blockSize +=
            sizeof(uint32_t) - (data->blockSize % sizeof(uint32_t)); /* make the block size as word-aligned */
    }

    totalWords = (data->blockCount * data->blockSize) / sizeof(uint32_t);

    while ((error_status == SUCCESS) && (transferredWords < totalWords))
    {
        while((interruptStatus & (((uint32_t)SDHOST_BufferWriteReadyFlag | (uint32_t)SDHOST_DataErrorFlag))) == 0)
        {
            interruptStatus = SDHOSTx->INTSTS;
        }

        if((interruptStatus & ((uint32_t)SDHOST_DataErrorFlag)) != 0)
        {
            if (data->enableIgnoreError == ENABLE)
            {
                error_status = ERROR;
            }

            /* clear data error flag */
            SDMMC_ClrFlag(SDHOSTx, (uint32_t)SDHOST_DataErrorFlag);
        }
        else
        {
            /* Intentional empty */
        }

        if (error_status == SUCCESS)
        {
            /* clear buffer write ready */
            SDMMC_ClrFlag(SDHOSTx, (uint32_t)SDHOST_BufferWriteReadyFlag);
            interruptStatus = 0U;
            transferredWords = SDMMC_WriteDataPort(SDHOSTx, data, transferredWords);
        }
    }

    /* Wait write data complete or data transfer error after the last writing operation. */
    while((interruptStatus & (((uint32_t)SDHOST_DataCompleteFlag | (uint32_t)SDHOST_DataErrorFlag))) == 0)
    {
        interruptStatus = SDHOSTx->INTSTS;
    }

    if ((interruptStatus & ((uint32_t)SDHOST_DataErrorFlag)) != 0UL)
    {
        if (data->enableIgnoreError == ENABLE)
        {
            error_status = ERROR;
        }
    }

    SDMMC_ClrFlag(SDHOSTx, (((uint32_t)SDHOST_DataCompleteFlag | (uint32_t)SDHOST_DataErrorFlag)));

    return error_status;
}


/**
 *\*\name   SDMMC_SendCommand.
 *\*\fun    send command function.
 *\*\param  SDHOSTx pointer to specified SDHOST,must be one of the following value:
 *\*\          - SDHOST1
 *\*\          - SDHOST2
 *\*\param  command: command configuration
 *\*\           - index
 *\*\               - 0~63
 *\*\           - argument
 *\*\               - 0x00000000~0xFFFFFFFF
 *\*\           - type
 *\*\               - CARD_CommandTypeNormal
 *\*\               - CARD_CommandTypeSuspend
 *\*\               - CARD_CommandTypeResume
 *\*\               - CARD_CommandTypeAbort
 *\*\               - CARD_CommandTypeEmpty
 *\*\           - responseType
 *\*\               - CARD_ResponseTypeNone
 *\*\               - CARD_ResponseTypeR1
 *\*\               - CARD_ResponseTypeR1b
 *\*\               - CARD_ResponseTypeR2
 *\*\               - CARD_ResponseTypeR3
 *\*\               - CARD_ResponseTypeR4
 *\*\               - CARD_ResponseTypeR5
 *\*\               - CARD_ResponseTypeR5b
 *\*\               - CARD_ResponseTypeR6
 *\*\               - CARD_ResponseTypeR7
 *\*\           - response[4U]: Response for this command.
 *\*\               - 0x00000000~0xFFFFFFFF
 *\*\           - responseErrorFlags: Response error flag, which need to check the command reponse.
 *\*\               - 0x00000000~0xFFFFFFFF
 *\*\           - flags: Cmd flags.
 *\*\               - 0x00000000~0xFFFFFFFF
 *\*\param  TMODE_struct: pointer to a SDHOST_TMODE_struct structure.
 *\*\           - DMAE
 *\*\                - SDHOST_TMODE_DMADISABLE
 *\*\                - SDHOST_TMODE_DMAENABLE
 *\*\           - BCNTE
 *\*\                - SDHOST_TMODE_BLOCKCNTDISABLE
 *\*\                - SDHOST_TMODE_BLOCKCNTENABLE
 *\*\           - ACMDE
 *\*\                - SDHOST_TMODE_NOACMDEN
 *\*\                - SDHOST_TMODE_AC12EN
 *\*\                - SDHOST_TMODE_AC23EN
 *\*\           - DATDIR
 *\*\                - SDHOST_TMODE_DATDIR_WRITE
 *\*\                - SDHOST_TMODE_DATDIR_READ
 *\*\           - BLKSEL
 *\*\                - SDHOST_TMODE_SINGLEBLK
 *\*\                - SDHOST_TMODE_MULTIBLK
 *\*\return none
 */
void SDMMC_SendCommand(SDHOST_Module* SDHOSTx, SDMMC_CMD *command, const SDHOST_TMODE_struct *TMODE_struct)
{
    uint32_t xferType;
    uint32_t flags;
    flags = command->flags;

    if (((SDHOSTx->PRESTS & ((uint32_t)SDHOST_CommandInhibitFlag)) == 0UL) && (command->type != CARD_CommandTypeEmpty))
    {
        if ((command->responseType == CARD_ResponseTypeR1) || (command->responseType == CARD_ResponseTypeR5) ||
                (command->responseType == CARD_ResponseTypeR6) || (command->responseType == CARD_ResponseTypeR7))
        {
            flags |= ((uint32_t)SDHOST_ResponseLength48Flag | (uint32_t)SDHOST_EnableCrcCheckFlag |
                      (uint32_t)SDHOST_EnableIndexCheckFlag);
        }
        else if ((command->responseType == CARD_ResponseTypeR1b) || (command->responseType == CARD_ResponseTypeR5b))
        {
            flags |= ((uint32_t)SDHOST_ResponseLength48BusyFlag | (uint32_t)SDHOST_EnableCrcCheckFlag |
                      (uint32_t)SDHOST_EnableIndexCheckFlag);
        }
        else if (command->responseType == CARD_ResponseTypeR2)
        {
            flags |= ((uint32_t)SDHOST_ResponseLength136Flag | (uint32_t)SDHOST_EnableCrcCheckFlag);
        }
        else if ((command->responseType == CARD_ResponseTypeR3) || (command->responseType == CARD_ResponseTypeR4))
        {
            flags |= ((uint32_t)SDHOST_ResponseLength48Flag);
        }
        else
        {
            /* Intentional empty */
        }

        if (command->type == CARD_CommandTypeAbort)
        {
            flags |= (uint32_t)SDHOST_CommandTypeAbortFlag;
        }

        /* config cmd index */
        xferType = 0x00000000U;

        xferType |=
            (((command->index << SDHOST_CMD_INDEX_OFFSET) & SDHOST_TMODE_INDEX) |
             ((flags) & (SDHOST_TMODE_TYPE | SDHOST_TMODE_INDEXCK | SDHOST_TMODE_CRCCK |
                         SDHOST_TMODE_RTYPESEL | SDHOST_TMODE_DPRESEL)));

        xferType |= TMODE_struct->DMAE;
        xferType |= TMODE_struct->BCNTE;
        xferType |= TMODE_struct->ACMDE;
        xferType |= TMODE_struct->DATDIR;
        xferType |= TMODE_struct->BLKSEL;

        /* config the command xfertype and argument */
        SDHOSTx->CMDARG1     = command->argument;
        SDHOSTx->TMODE = xferType;
    }

    if (command->type == CARD_CommandTypeEmpty)
    {
        /* disable CMD done interrupt for empty command */
        SDHOSTx->ISE &= ~SDHOST_ISE_CMDCSE;
    }
}


/**
 *\*\name   SDMMC_WaitCommandDone.
 *\*\fun    wait command done.
 *\*\param  SDHOSTx pointer to specified SDHOST,must be one of the following value:
 *\*\          - SDHOST1
 *\*\          - SDHOST2
 *\*\param  command: command configuration
 *\*\           - index
 *\*\               - 0~63
 *\*\           - argument
 *\*\               - 0x00000000~0xFFFFFFFF
 *\*\           - type
 *\*\               - CARD_CommandTypeNormal
 *\*\               - CARD_CommandTypeSuspend
 *\*\               - CARD_CommandTypeResume
 *\*\               - CARD_CommandTypeAbort
 *\*\               - CARD_CommandTypeEmpty
 *\*\           - responseType
 *\*\               - CARD_ResponseTypeNone
 *\*\               - CARD_ResponseTypeR1
 *\*\               - CARD_ResponseTypeR1b
 *\*\               - CARD_ResponseTypeR2
 *\*\               - CARD_ResponseTypeR3
 *\*\               - CARD_ResponseTypeR4
 *\*\               - CARD_ResponseTypeR5
 *\*\               - CARD_ResponseTypeR5b
 *\*\               - CARD_ResponseTypeR6
 *\*\               - CARD_ResponseTypeR7
 *\*\           - response[4U]: Response for this command.
 *\*\               - 0x00000000~0xFFFFFFFF
 *\*\           - responseErrorFlags: Response error flag, which need to check the command reponse.
 *\*\               - 0x00000000~0xFFFFFFFF
 *\*\           - flags: Cmd flags.
 *\*\               - 0x00000000~0xFFFFFFFF
 *\*\param  pollingCmdDone: polling command done flag
 *\*\           - ENABLE
 *\*\           - DISABLE
 *\*\return SDMMC_STS
 *\*\           - SDMMC_ERROR
 *\*\           - SDMMC_SUCCESS
 *\*\           - SDMMC_SendCommandFailed
 */
SDMMC_STS SDMMC_WaitCommandDone(SDHOST_Module* SDHOSTx, SDMMC_CMD *command, FunctionalState pollingCmdDone)
{
    SDMMC_STS error          = SDMMC_SUCCESS;
    uint32_t interruptStatus = 0U;
    uint32_t timeout_value = 0x20000;

    /* check if need polling command done or not */
    if (pollingCmdDone == ENABLE)
    {
        /* Wait command complete or SDMMC encounters error. */
        while(((interruptStatus & ((uint32_t)SDHOST_CommandFlag)) == 0) && (timeout_value > 0))
        {
            interruptStatus = SDHOSTx->INTSTS;
            timeout_value--;
        }

        if(timeout_value == 0)
        {
            interruptStatus = (uint32_t)SDHOST_CommandTimeoutFlag;
        }

        if ((interruptStatus & ((uint32_t)SDHOST_CommandErrorFlag)) != 0UL)
        {
            error = SDMMC_ERROR;
        }

        /* Receive response when command completes successfully. */
        if (error == SDMMC_SUCCESS)
        {
            error = SDMMC_ReceiveCommandResponse(SDHOSTx, command);
        }

        SDMMC_ClrFlag(SDHOSTx, (uint32_t)SDHOST_CommandFlag);
    }

    return error;
}


/**
 *\*\name   SDMMC_TransferDataBlocking.
 *\*\fun    Transfer data by polling way.
 *\*\param  SDHOSTx :
 *\*\          - SDHOST1
 *\*\          - SDHOST2
 *\*\param  data  Data descriptor.
 *\*\          - AutoCommand12_23.
 *\*\              - AutoCommand12
 *\*\              - AutoCommand23
 *\*\              - NoAutoCommand
 *\*\          - enableIgnoreError.
 *\*\              - ENABLE
 *\*\              - DISABLE
 *\*\          - dataType.
 *\*\              - SDHOST_TransferDataNormal
 *\*\              - SDHOST_TransferDataTuning
 *\*\              - SDHOST_TransferDataBoot
 *\*\              - SDHOST_TransferDataBootcontinous
 *\*\           - blockCount  :
 *\*\               - The available range is 0 ~ 0xFFFF.
 *\*\           - blockSize  :
 *\*\               - The available range is 0 ~ 0x0800.
 *\*\           - rxData  :  Buffer to save data read.
 *\*\           - txData  :  Data buffer to write.
 *\*\param  DMACmd: DMA flag
 *\*\           - ENABLE
 *\*\           - DISABLE
 *\*\return error.
 *\*\           - SDMMC_ERROR
 *\*\           - SDMMC_SUCCESS
 *\*\           - SDMMC_TransferDataFailed
 */
static SDMMC_STS SDMMC_TransferDataBlocking(SDHOST_Module* SDHOSTx, SDMMC_DATA *data, FunctionalState DMACmd)
{
    SDMMC_STS error = SDMMC_SUCCESS;
    ErrorStatus error_status;
    uint32_t interruptStatus = 0U;
    uint32_t SDMA_address;

    if (DMACmd == ENABLE)
    {
        /* Wait data complete or SDMMC encounters error. */
        while((interruptStatus & ((uint32_t)SDHOST_DataDMAFlag)) == 0)
        {
            interruptStatus = SDHOSTx->INTSTS;

            if((interruptStatus & ((uint32_t)SDHOST_DmaCompleteFlag)) == ((uint32_t)SDHOST_DmaCompleteFlag))
            {
                SDMMC_ClrFlag(SDHOSTx, (uint32_t)SDHOST_DmaCompleteFlag);
                SDMA_address = SDHOSTx->DSADD;
                SDHOSTx->DSADD = SDMA_address;
            }
        }

        if((interruptStatus & (((uint32_t)SDHOST_DataErrorFlag | (uint32_t)SDHOST_DmaErrorFlag))) != 0)
        {
            if (((data->enableIgnoreError == ENABLE)) || ((interruptStatus & ((uint32_t)SDHOST_DataTimeoutFlag)) != 0))
            {
                error = SDMMC_TransferDataFailed;
            }
        }
        else
        {
            /* Intentional empty */
        }

        /* load dummy data */
        if ((data->dataType == SDHOST_TransferDataBootcontinous) && (error == SDMMC_SUCCESS))
        {
            *(data->rxData) = SDHOST_BOOTDUMMY;
        }

        SDMMC_ClrFlag(SDHOSTx, (uint32_t)SDHOST_DataDMAFlag);
    }
    else
    {
        if (data->rxData != NULL)
        {
            error_status = SDMMC_ReadByDataPortBlocking(SDHOSTx, data);

            if (error_status != SUCCESS)
            {
                return SDMMC_ERROR;
            }
        }
        else
        {
            error_status = SDMMC_WriteByDataPortBlocking(SDHOSTx, data);

            if (error_status != SUCCESS)
            {
                return SDMMC_ERROR;
            }
        }
    }

    return error;
}


/**
 *\*\name   SDMMC_GetCapability.
 *\*\fun    Get SDHSOT capability structure value.
 *\*\param  SDHOSTx :
 *\*\          - SDHOST1
 *\*\          - SDHOST2
 *\*\param  capability: pointer to a SDHOST_capability structure.
 *\*\           - MaxBlockLen  : Maximum Block Length supported by the Core/Device
 *\*\               - SDMMC_MAXBLOCKLEN_512B
 *\*\               - SDMMC_MAXBLOCKLEN_1024B
 *\*\               - SDMMC_MAXBLOCKLEN_2048B
 *\*\           - SDBaseCLKFreq :  xin_clk, Base Clock Frequency for SD Clock
 *\*\               - 0x0A~0x68,Unit MHz
 *\*\           - TimeOutUnit   :  the unit of base clock frequency used to detect Data Timeout Error
 *\*\               - SDMMC_TIMEOUTCLKUNIT_KHZ
 *\*\               - SDMMC_TIMEOUTCLKUNIT_MHZ
 *\*\           - SPIBlockMode  :    SPI Block Mode
 *\*\               - SDMMC_SPIBLOCKMODESUPPORT
 *\*\               - SDMMC_SPIBLOCKMODEUNSUPPORT
 *\*\           - SPIMode       :   SPI Mode Support
 *\*\               - SDMMC_SPIMODESUPPORT
 *\*\               - SDMMC_SPIMODEUNSUPPORT
 *\*\           - DDR50         : DDR50 Support
 *\*\               - SDMMC_DDR50SUPPORT
 *\*\               - SDMMC_DDR50UNSUPPORT
 *\*\           - SDR104        : SDR104 Support
 *\*\               - SDMMC_SDR104SUPPORT
 *\*\               - SDMMC_SDR104UNSUPPORT
 *\*\           - SDR50         : SDR50 Support
 *\*\               - SDMMC_SDR50SUPPORT
 *\*\               - SDMMC_SDR50UNSUPPORT
 *\*\           - SlotType      : Slot Type
 *\*\               - SDMMC_SDTYPE
 *\*\               - SDMMC_EMMCTYPE
 *\*\           - AsyncInt      : Asynchronous Interrupt Support
 *\*\               - SDMMC_ASYNCINTSUPPORT
 *\*\               - SDMMC_ASYNCINTUNSUPPORT
 *\*\           - Suspend_Resume : Suspend/Resume Support
 *\*\               - SDMMC_SUSRESSUPPORT
 *\*\               - SDMMC_SUSRESUNSUPPORT
 *\*\           - SDMA           : SDMA Support
 *\*\               - SDMMC_SDMASUPPORT
 *\*\               - SDMMC_SDMAUNSUPPORT
 *\*\           - HS             : High Speed Support
 *\*\               - SDMMC_HSSUPPORT
 *\*\               - SDMMC_HSUNSUPPORT
 *\*\           - ADMA2          : ADMA2 Support
 *\*\               - SDMMC_ADMA2SUPPORT
 *\*\               - SDMMC_ADMA2UNSUPPORT
 *\*\           - Embedded_8bit   : 8-bit Support for Embedded Device
 *\*\               - SDMMC_EMBEDDEDSUPPORT
 *\*\               - SDMMC_EMBEDDEDUNSUPPORT
 *\*\           - UseTuningSDR50  : Use Tuning for SDR50
 *\*\               - SDMMC_SDR50TUNING
 *\*\               - SDMMC_SDR50UNTUNING
 *\*\return none
 */
void SDMMC_GetCapability(SDHOST_Module* SDHOSTx, SDHOST_capability *capability)
{
    if((SDHOSTx->CAP0STS & SDHOST_CAP0_ADMA2_MASK) == SDHOST_CAP0_ADMA2_MASK)
    {
        capability->ADMA2 = SDMMC_ADMA2SUPPORT;
    }
    else
    {
        capability->ADMA2 = SDMMC_ADMA2UNSUPPORT;
    }

    if((SDHOSTx->CAP0STS & SDHOST_CAP0_ASYNCINT_MASK) == SDHOST_CAP0_ASYNCINT_MASK)
    {
        capability->AsyncInt = SDMMC_ASYNCINTSUPPORT;
    }
    else
    {
        capability->AsyncInt = SDMMC_ASYNCINTUNSUPPORT;
    }

    if((SDHOSTx->CAP1STS & SDHOST_CAP1_DDR50_MASK) == SDHOST_CAP1_DDR50_MASK)
    {
        capability->DDR50 = SDMMC_DDR50SUPPORT;
    }
    else
    {
        capability->DDR50 = SDMMC_DDR50UNSUPPORT;
    }

    if((SDHOSTx->CAP0STS & SDHOST_CAP0_EMBUS_MASK) == SDHOST_CAP0_EMBUS_MASK)
    {
        capability->Embedded_8bit = SDMMC_EMBEDDEDSUPPORT;
    }
    else
    {
        capability->Embedded_8bit = SDMMC_EMBEDDEDUNSUPPORT;
    }

    if((SDHOSTx->CAP0STS & SDHOST_CAP0_HS_MASK) == SDHOST_CAP0_HS_MASK)
    {
        capability->HS = SDMMC_HSSUPPORT;
    }
    else
    {
        capability->HS = SDMMC_HSUNSUPPORT;
    }

    if((SDHOSTx->CAP0STS & SDHOST_CAP0_MBL_MASK) == SDMMC_MAXBLOCKLEN_512B)
    {
        capability->MaxBlockLen = SDMMC_MAXBLOCKLEN_512B;
    }
    else if((SDHOSTx->CAP0STS & SDHOST_CAP0_MBL_MASK) == SDHOST_CAP0STS_MBL_0)
    {
        capability->MaxBlockLen = SDMMC_MAXBLOCKLEN_1024B;
    }
    else
    {
        capability->MaxBlockLen = SDMMC_MAXBLOCKLEN_2048B;
    }

    capability->SDBaseCLKFreq = ((SDHOSTx->CAP0STS & SDHOST_CAP0_BCLKF_MASK) >> SDHOST_CAP0_BCLKF_OFFSET);

    if((SDHOSTx->CAP0STS & SDHOST_CAP0_SDMA_MASK) == SDHOST_CAP0_SDMA_MASK)
    {
        capability->SDMA = SDMMC_SDMASUPPORT;
    }
    else
    {
        capability->SDMA = SDMMC_SDMAUNSUPPORT;
    }

    if((SDHOSTx->CAP1STS & SDHOST_CAP1_SDR104_MASK) == SDHOST_CAP1_SDR104_MASK)
    {
        capability->SDR104 = SDMMC_SDR104SUPPORT;
    }
    else
    {
        capability->SDR104 = SDMMC_SDR104UNSUPPORT;
    }

    if((SDHOSTx->CAP1STS & SDHOST_CAP1_SDR50_MASK) == SDHOST_CAP1_SDR50_MASK)
    {
        capability->SDR50 = SDMMC_SDR50SUPPORT;
    }
    else
    {
        capability->SDR50 = SDMMC_SDR50UNSUPPORT;
    }

    if((SDHOSTx->CAP0STS & SDHOST_CAP0_SLOTTYPE_MASK) == SDHOST_CAP0STS_STYP_0)
    {
        capability->SlotType = SDMMC_EMMCTYPE;
    }
    else
    {
        capability->SlotType = SDMMC_SDTYPE;
    }

    if((SDHOSTx->CAP1STS & SDHOST_CAP1_SPIBMOD_MASK) == SDHOST_CAP1_SPIBMOD_MASK)
    {
        capability->SPIBlockMode = SDMMC_SPIBLOCKMODESUPPORT;
    }
    else
    {
        capability->SPIBlockMode = SDMMC_SPIBLOCKMODEUNSUPPORT;
    }

    if((SDHOSTx->CAP1STS & SDHOST_CAP1_SPIMOD_MASK) == SDHOST_CAP1_SPIMOD_MASK)
    {
        capability->SPIMode = SDMMC_SPIMODESUPPORT;
    }
    else
    {
        capability->SPIMode = SDMMC_SPIMODEUNSUPPORT;
    }

    if((SDHOSTx->CAP0STS & SDHOST_CAP0_SRS_MASK) == SDHOST_CAP0_SRS_MASK)
    {
        capability->Suspend_Resume = SDMMC_SUSRESSUPPORT;
    }
    else
    {
        capability->Suspend_Resume = SDMMC_SUSRESUNSUPPORT;
    }

    if((SDHOSTx->CAP0STS & SDHOST_CAP0_TCLKU_MASK) == SDHOST_CAP0_TCLKU_MASK)
    {
        capability->TimeOutUnit = SDMMC_TIMEOUTCLKUNIT_MHZ;
    }
    else
    {
        capability->TimeOutUnit = SDMMC_TIMEOUTCLKUNIT_KHZ;
    }

    if((SDHOSTx->CAP1STS & SDHOST_CAP1_UTFSDR50_MASK) == SDHOST_CAP1_UTFSDR50_MASK)
    {
        capability->UseTuningSDR50 = SDMMC_SDR50TUNING;
    }
    else
    {
        capability->UseTuningSDR50 = SDMMC_SDR50UNTUNING;
    }
}


/**
 *\*\name   SDMMC_GetPresetvalue.
 *\*\fun    Get SDHSOT presetvalue structure value.
 *\*\param  SDHOSTx :
 *\*\          - SDHOST1
 *\*\          - SDHOST2
 *\*\param  presetvalue: pointer to a SDHOST_presetvalue structure.
 *\*\           - DSSDCLKFreq      : SDCLK Frequency Select Value for Default Speed
 *\*\               - 0x00~0x3FF ; 2N frequency division
 *\*\           - INITSDCLKFreq    :SDCLK Frequency Select Value for Initialization
 *\*\               - 0x00~0x3FF ; 2N frequency division
 *\*\           - SDR12SDCLKFreq  : SDCLK Frequency Select Value for SDR12
 *\*\               - 0x00~0x3FF ; 2N frequency division
 *\*\           - HSSDCLKFreq     : SDCLK Frequency Select Value for High Speed
 *\*\               - 0x00~0x3FF ; 2N frequency division
 *\*\           - SDR50SDCLKFreq  : SDCLK Frequency Select Value for SDR50
 *\*\               - 0x00~0x3FF ; 2N frequency division
 *\*\           - SDR25SDCLKFreq   : SDCLK Frequency Select Value for SDR25
 *\*\               - 0x00~0x3FF ; 2N frequency division
 *\*\           - SDR104SDCLKFreq  : SDCLK Frequency Select Value for SDR104
 *\*\               - 0x00~0x3FF ; 2N frequency division
 *\*\           - DDR50SDCLKFreq   : SDCLK Frequency Select Value for DDR50
 *\*\               - 0x00~0x3FF ; 2N frequency division
 *\*\return none
 */
void SDMMC_GetPresetvalue(SDHOST_Module* SDHOSTx, SDHOST_presetvalue *presetvalue)
{
    presetvalue->DSSDCLKFreq     = ((SDHOSTx->PV0STS & SDHOST_PV0_DSCLKFS_MASK) >> SDHOST_PV0_DSCLKFS_OFFSET);
    presetvalue->INITSDCLKFreq   = (SDHOSTx->PV0STS & SDHOST_PV0_INITCLKFS_MASK);
    presetvalue->SDR12SDCLKFreq  = ((SDHOSTx->PV1STS & SDHOST_PV1_SDR12CLKFS_MASK) >> SDHOST_PV1_SDR12CLKFS_OFFSET);
    presetvalue->HSSDCLKFreq     = (SDHOSTx->PV1STS & SDHOST_PV1_HSCLKFS_MASK);
    presetvalue->SDR50SDCLKFreq  = ((SDHOSTx->PV2STS & SDHOST_PV2_SDR50CLKFS_MASK) >> SDHOST_PV2_SDR50CLKFS_OFFSET);
    presetvalue->SDR25SDCLKFreq  = (SDHOSTx->PV2STS & SDHOST_PV2_SDR25CLKFS_MASK);
    presetvalue->DDR50SDCLKFreq  = ((SDHOSTx->PV3STS & SDHOST_PV3_DDR50CLKFS_MASK) >> SDHOST_PV3_DDR50CLKFS_OFFSET);
    presetvalue->SDR104SDCLKFreq = (SDHOSTx->PV3STS & SDHOST_PV3_SDR104CLKFS_MASK);
}


/**
 *\*\name    SDMMC_EnableSDCLK
 *\*\fun     Enables or disables SD Clock.
 *\*\param   SDHOSTx :
 *\*\          - SDHOST1
 *\*\          - SDHOST2
 *\*\param   Cmd (The input parameters must be the following values):
 *\*\          - ENABLE
 *\*\          - DISABLE
 *\*\return  none
 */
void SDMMC_EnableSDCLK(SDHOST_Module* SDHOSTx, FunctionalState Cmd)
{
    if (Cmd != DISABLE)
    {
        SDHOSTx->CTRL2 |= (SDHOST_CTRL2_SDCLKE | SDHOST_CTRL2_INCLKE);
    }
    else
    {
        SDHOSTx->CTRL2 &= (~(SDHOST_CTRL2_SDCLKE | SDHOST_CTRL2_INCLKE));
    }
}

/**
 *\*\name    SDMMC_WaitSDCLKStable
 *\*\fun     Waiting for SD clock to stabilize.
 *\*\param   SDHOSTx :
 *\*\          - SDHOST1
 *\*\          - SDHOST2
 *\*\param   Cmd (The input parameters must be the following values):
 *\*\          - ENABLE
 *\*\          - DISABLE
 *\*\return  status_value
 *\*\          - SDMMC_ERROR
 *\*\          - SDMMC_SUCCESS
 */
SDMMC_STS SDMMC_WaitSDCLKStable(SDHOST_Module* SDHOSTx)
{
    SDMMC_STS status_value;
    uint32_t timeout         = 0xFFFFUL;

    /* Wait until the SD clock is stable. */
    while ((SDHOSTx->CTRL2 & SDHOST_CTRL2_INCLKSTS) != SDHOST_CTRL2_INCLKSTS)
    {
        timeout--;

        if(timeout < 2)
        {
            break;
        }
    }

    if(timeout < 2 )
    {
        status_value = SDMMC_ERROR;
    }
    else
    {
        status_value = SDMMC_SUCCESS;
    }

    return status_value;
}


/**
 *\*\name   SDMMC_SetSdClock.
 *\*\fun    Sets the SD bus clock frequency.
 *\*\param  SDHOSTx :
 *\*\          - SDHOST1
 *\*\          - SDHOST2
 *\*\param  PresetCmd: Whether to use preset value settings.
 *\*\           - ENABLE
 *\*\           - DISABLE
 *\*\param  prescaler: SD bus clock prescaler value.
 *\*\           - 0~0x3FF  1/2N frequency division
 *\*\return  status_value
 *\*\          - SDMMC_ERROR
 *\*\          - SDMMC_SUCCESS
 */
SDMMC_STS SDMMC_SetSdClock(SDHOST_Module* SDHOSTx, FunctionalState PresetCmd, uint32_t prescaler)
{
    SDMMC_STS status_value;
    uint32_t temp_value;

    SDMMC_EnableSDCLK(SDHOSTx, DISABLE);

    if(PresetCmd == ENABLE)
    {
        /* Use preset values */
        SDHOSTx->CTRLSTS |= SDHOST_CTRLSTS_PREVE;
    }
    else
    {
        /* Use HD config values */
        SDHOSTx->CTRLSTS &= (~SDHOST_CTRLSTS_PREVE);

        /* set prescaler value */
        temp_value = SDHOSTx->CTRL2;
        temp_value &= (~SDHOST_CTRL2_SDCLKSEL);
        temp_value |= (((prescaler & 0xFFUL) << REG_BIT8_OFFSET) | ((prescaler >> REG_BIT8_OFFSET) << REG_BIT6_OFFSET));
        SDHOSTx->CTRL2 = temp_value;
    }

    SDMMC_EnableSDCLK(SDHOSTx, ENABLE);

    status_value = SDMMC_WaitSDCLKStable(SDHOSTx);
    return status_value;
}


/**
 *\*\name   SDMMC_ConfigemmcBoot.
 *\*\fun    Configures the MMC boot feature.
 *\*\param  SDHOSTx pointer to specified SDHOST,must be one of the following value:
 *\*\          - SDHOST1
 *\*\          - SDHOST2
 *\*\param  config: pointer to a SDHOST_boot_config structure.
 *\*\           - ackTimeoutCount  : Timeout value for the boot ACK
 *\*\               - The available range is 0 ~ 0xFFFFFFFF. unit sd clock.
 *\*\           - bootMode  : Boot mode selection
 *\*\               - SDHOST_BOOTMODENORMAL       Normal boot
 *\*\               - SDHOST_BOOTMODEALIERNATIVE  Alternative boot
 *\*\           - blockCount  :
 *\*\               - The available range is 0 ~ 0xFFFF.
 *\*\           - blockSize  :
 *\*\               - The available range is 0 ~ 0x0800.
 *\*\           - BootAck  :
 *\*\               - SDHOST_BOOTACKCHECK
 *\*\               - SDHOST_BOOTNOACKCHECK
 *\*\return none
 */
void SDMMC_ConfigemmcBoot(SDHOST_Module* SDHOSTx, const SDHOST_boot_config *config)
{
    uint32_t temp_value;
    SDHOSTx->BOOTTCTRL = config->ackTimeoutCount;

    temp_value = SDHOSTx->CTRL1;
    temp_value &= (~(SDHOST_BOOTMODEALIERNATIVE | SDHOST_BOOTACKCHECK));
    temp_value |= (config->BootAck | config->bootMode);
    SDHOSTx->CTRL1 = temp_value;

    temp_value = SDHOSTx->BLKCFG;
    temp_value &= (~(SDHOST_BLKCFG_CNT | SDHOST_BLKCFG_SIZE));
    temp_value |= ((config->blockCount << 16) | config->blockSize);
    SDHOSTx->BLKCFG = temp_value;
}

/**
 *\*\name   SDMMC_ConfigInternalDma.
 *\*\fun    Use to config the Internal DMA related registers.
 *\*\param  SDHOSTx :
 *\*\          - SDHOST1
 *\*\          - SDHOST2
 *\*\param  dmaConfig
 *\*\          - dmaMode.
 *\*\              - DmaModeSimple
 *\*\              - DmaModeAdma2
 *\*\          - admaTable Adma table address.
 *\*\              - The available range is 0 ~ 0xFFFFFFFF.
 *\*\          - admaTableWords Adma table length.
 *\*\               - The available range is 0 ~ 0xFFFF.
 *\*\param  dataAddr  transfer data address, a simple DMA parameter, if ADMA is used, leave it to NULL.
 *\*\               - The available range is 0 ~ 0xFFFFFFFF.
 *\*\param  enAutoCmd23 flag to indicate Auto CMD23 is enable or not, a simple DMA parameter,if ADMA is used, leave it to DISABLE.
 *\*\               - ENABLE
 *\*\               - DISABLE
 *\*\param  TMODE_struct: pointer to a SDHOST_TMODE_struct structure.
 *\*\           - DMAE
 *\*\                - SDHOST_TMODE_DMADISABLE
 *\*\                - SDHOST_TMODE_DMAENABLE
 *\*\           - BCNTE
 *\*\                - SDHOST_TMODE_BLOCKCNTDISABLE
 *\*\                - SDHOST_TMODE_BLOCKCNTENABLE
 *\*\           - ACMDE
 *\*\                - SDHOST_TMODE_NOACMDEN
 *\*\                - SDHOST_TMODE_AC12EN
 *\*\                - SDHOST_TMODE_AC23EN
 *\*\           - DATDIR
 *\*\                - SDHOST_TMODE_DATDIR_WRITE
 *\*\                - SDHOST_TMODE_DATDIR_READ
 *\*\           - BLKSEL
 *\*\                - SDHOST_TMODE_SINGLEBLK
 *\*\                - SDHOST_TMODE_MULTIBLK
 *\*\return SDMMC_STS
 *\*\               - SDMMC_DMADataAddrNotAlign
 *\*\               - SDMMC_SUCCESS
 */
static SDMMC_STS SDMMC_ConfigInternalDma(SDHOST_Module* SDHOSTx, SDHOST_ADMAconfig *dmaConfig, const uint32_t *dataAddr,
        FunctionalState enAutoCmd23, SDHOST_TMODE_struct *TMODE_struct)
{
    if (dmaConfig->dmaMode == DmaModeSimple)
    {
        /* check DMA data buffer address align or not */
        if (((uint32_t)dataAddr % SDHOST_ADMA2_ADDRESS_ALIGN) != 0UL)
        {
            return SDMMC_DMADataAddrNotAlign;
        }

        /* in simple DMA mode if use auto CMD23, address should load to ADMA addr,
             and block count should load to DS_ADD*/
        if (enAutoCmd23 == ENABLE)
        {
            SDHOSTx->ASADD0 = ((uint32_t)dataAddr);
        }
        else
        {
            SDHOSTx->DSADD = ((uint32_t)dataAddr);
        }
    }
    else
    {
        /* When use ADMA, disable simple DMA */
        SDHOSTx->DSADD       = 0UL;
        SDHOSTx->ASADD0 = ((uint32_t)(dmaConfig->admaTable));
    }

    /* select DMA mode */
    SDHOSTx->CTRL1 &= (~SDHOST_CTRL1_DMASEL);
    SDHOSTx->CTRL1 |= (uint32_t)(dmaConfig->dmaMode);

    /* enable DMA */
    TMODE_struct->DMAE = SDHOST_TMODE_DMAENABLE;
    return SDMMC_SUCCESS;
}

/**
 *\*\name   SDMMC_SetAdmaTableConfig.
 *\*\fun    Sets the DMA descriptor table configuration.
 *\*\param  SDHOSTx :
 *\*\          - SDHOST1
 *\*\          - SDHOST2
 *\*\param  dmaConfig
 *\*\          - dmaMode.
 *\*\              - DmaModeSimple
 *\*\              - DmaModeAdma2
 *\*\          - admaTable Adma table address.
 *\*\              - The available range is 0 ~ 0xFFFFFFFF.
 *\*\          - admaTableWords Adma table length.
 *\*\               - The available range is 0 ~ 0xFFFF.
 *\*\param  dataConfig  Data descriptor.
 *\*\          - AutoCommand12_23.
 *\*\              - AutoCommand12
 *\*\              - AutoCommand23
 *\*\              - NoAutoCommand
 *\*\          - enableIgnoreError.
 *\*\              - ENABLE
 *\*\              - DISABLE
 *\*\          - dataType.
 *\*\              - SDHOST_TransferDataNormal
 *\*\              - SDHOST_TransferDataTuning
 *\*\              - SDHOST_TransferDataBoot
 *\*\              - SDHOST_TransferDataBootcontinous
 *\*\           - blockCount  :
 *\*\               - The available range is 0 ~ 0xFFFF.
 *\*\           - blockSize  :
 *\*\               - The available range is 0 ~ 0x0800.
 *\*\           - rxData  :  Buffer to save data read.
 *\*\           - txData  :  Data buffer to write.
 *\*\param  flags  ADAM descriptor flag, used to indicate to create multiple or single descriptor.
 *\*\          - SDHOST_AdmaDescriptorSingleFlag.
 *\*\          - SDHOST_AdmaDescriptorMultipleFlag.
 *\*\param  TMODE_struct: pointer to a SDHOST_TMODE_struct structure.
 *\*\           - DMAE
 *\*\                - SDHOST_TMODE_DMADISABLE
 *\*\                - SDHOST_TMODE_DMAENABLE
 *\*\           - BCNTE
 *\*\                - SDHOST_TMODE_BLOCKCNTDISABLE
 *\*\                - SDHOST_TMODE_BLOCKCNTENABLE
 *\*\           - ACMDE
 *\*\                - SDHOST_TMODE_NOACMDEN
 *\*\                - SDHOST_TMODE_AC12EN
 *\*\                - SDHOST_TMODE_AC23EN
 *\*\           - DATDIR
 *\*\                - SDHOST_TMODE_DATDIR_WRITE
 *\*\                - SDHOST_TMODE_DATDIR_READ
 *\*\           - BLKSEL
 *\*\                - SDHOST_TMODE_SINGLEBLK
 *\*\                - SDHOST_TMODE_MULTIBLK
 *\*\return SDMMC_STS
 *\*\          - SDMMC_ERROR.
 *\*\          - SDMMC_SUCCESS.
 *\*\          - SDMMC_DMADataAddrNotAlign
 *\*\          - SDMMC_OutOfRange
 */
static SDMMC_STS SDMMC_SetAdmaTableConfig(SDHOST_Module* SDHOSTx, SDHOST_ADMAconfig *dmaConfig,
        SDMMC_DATA *dataConfig, SDHOST_TMODE_struct *TMODE_struct)
{
    SDMMC_STS status_value = SDMMC_SUCCESS;
    FunctionalState enAutoCmd23;
    uint32_t bootDummyOffset =
        (dataConfig->dataType == (uint32_t)SDHOST_TransferDataBootcontinous) ? sizeof(uint32_t) : 0UL;
    const uint32_t *data = (const uint32_t *)((uint32_t)(
                               (uint32_t)((dataConfig->rxData == NULL) ? dataConfig->txData : dataConfig->rxData) + bootDummyOffset));

    /* for internal dma, internal DMA configurations should not update the configurations when continous transfer the
     * boot data, only the DMA descriptor need update */
    if ((status_value == SDMMC_SUCCESS) && (dataConfig->dataType != SDHOST_TransferDataBootcontinous))
    {
        if(dataConfig->AutoCommand12_23 == AutoCommand23)
        {
            enAutoCmd23 = ENABLE;
        }
        else
        {
            enAutoCmd23 = DISABLE;
        }

        status_value = SDMMC_ConfigInternalDma(SDHOSTx, dmaConfig, data, enAutoCmd23, TMODE_struct);
    }

    return status_value;
}


/**
 *\*\name   SDMMC_TransferBlocking.
 *\*\fun     Transfers the command/data using a blocking method.
 *\*\param  SDHOSTx :
 *\*\          - SDHOST1
 *\*\          - SDHOST2
 *\*\param  dmaConfig
 *\*\          - dmaMode.
 *\*\              - DmaModeSimple
 *\*\              - DmaModeAdma2
 *\*\          - admaTable Adma table address.
 *\*\              - The available range is 0 ~ 0xFFFFFFFF.
 *\*\          - admaTableWords Adma table length.
 *\*\              - The available range is 0 ~ 0xFFFF.
 *\*\param  transfer
 *\*\          - data  Data descriptor.
 *\*\              - AutoCommand12_23.
 *\*\                 - AutoCommand12
 *\*\                 - AutoCommand23
 *\*\                 - NoAutoCommand
 *\*\              - enableIgnoreError.
 *\*\                 - ENABLE
 *\*\                 - DISABLE
 *\*\              - dataType.
 *\*\                 - SDHOST_TransferDataNormal
 *\*\                 - SDHOST_TransferDataTuning
 *\*\                 - SDHOST_TransferDataBoot
 *\*\                 - SDHOST_TransferDataBootcontinous
 *\*\              - blockCount  :
 *\*\                 - The available range is 0 ~ 0xFFFF.
 *\*\              - blockSize  :
 *\*\                 - The available range is 0 ~ 0x0800.
 *\*\              - rxData  :  Buffer to save data read.
 *\*\              - txData  :  Data buffer to write.
 *\*\         - command: command configuration
 *\*\              - index
 *\*\                 - 0~63
 *\*\              - argument
 *\*\                 - 0x00000000~0xFFFFFFFF
 *\*\              - type
 *\*\                 - CARD_CommandTypeNormal
 *\*\                 - CARD_CommandTypeSuspend
 *\*\                 - CARD_CommandTypeResume
 *\*\                 - CARD_CommandTypeAbort
 *\*\                 - CARD_CommandTypeEmpty
 *\*\              - responseType
 *\*\                 - CARD_ResponseTypeNone
 *\*\                 - CARD_ResponseTypeR1
 *\*\                 - CARD_ResponseTypeR1b
 *\*\                 - CARD_ResponseTypeR2
 *\*\                 - CARD_ResponseTypeR3
 *\*\                 - CARD_ResponseTypeR4
 *\*\                 - CARD_ResponseTypeR5
 *\*\                 - CARD_ResponseTypeR5b
 *\*\                 - CARD_ResponseTypeR6
 *\*\                 - CARD_ResponseTypeR7
 *\*\              - response[4U]: Response for this command.
 *\*\                 - 0x00000000~0xFFFFFFFF
 *\*\              - responseErrorFlags: Response error flag, which need to check the command reponse.
 *\*\                 - 0x00000000~0xFFFFFFFF
 *\*\              - flags: Cmd flags.
 *\*\                 - 0x00000000~0xFFFFFFFF
 *\*\param  TMODE_struct: pointer to a SDHOST_TMODE_struct structure.
 *\*\           - DMAE
 *\*\                - SDHOST_TMODE_DMADISABLE
 *\*\                - SDHOST_TMODE_DMAENABLE
 *\*\           - BCNTE
 *\*\                - SDHOST_TMODE_BLOCKCNTDISABLE
 *\*\                - SDHOST_TMODE_BLOCKCNTENABLE
 *\*\           - ACMDE
 *\*\                - SDHOST_TMODE_NOACMDEN
 *\*\                - SDHOST_TMODE_AC12EN
 *\*\                - SDHOST_TMODE_AC23EN
 *\*\           - DATDIR
 *\*\                - SDHOST_TMODE_DATDIR_WRITE
 *\*\                - SDHOST_TMODE_DATDIR_READ
 *\*\           - BLKSEL
 *\*\                - SDHOST_TMODE_SINGLEBLK
 *\*\                - SDHOST_TMODE_MULTIBLK
 *\*\return SDMMC_STS
 *\*\          - SDMMC_ReTuningRequest
 *\*\          - SDMMC_ERROR.
 *\*\          - SDMMC_SUCCESS.
 *\*\          - SDMMC_DMADataAddrNotAlign
 *\*\          - SDMMC_OutOfRange
 *\*\          - SDMMC_BusyTransferring
 *\*\          - SDMMC_SendCommandFailed
 *\*\          - SDMMC_TransferDataFailed
 */
SDMMC_STS SDMMC_TransferBlocking(SDHOST_Module* SDHOSTx, SDHOST_ADMAconfig *dmaConfig, SDMMC_Transfer *transfer, SDHOST_TMODE_struct *TMODE_struct)
{
    SDMMC_STS status_value   = SDMMC_ERROR;
    SDMMC_CMD *command = &transfer->command;
    SDMMC_DATA *data       = &transfer->data;
    FunctionalState enDMA   = ENABLE;
    FunctionalState CMDdone;
    bool executeTuning       = ((data == NULL) ? false : (data->dataType == (uint32_t)SDHOST_TransferDataTuning));
    uint32_t transferFlags   = (uint32_t)SDMMC_CommandOnly;
    uint32_t blockSize         = 0U;
    uint32_t blockCount        = 0U;
    SDHOST_capability  Capability;

    SDMMC_GetCapability(SDHOSTx, &Capability);

    if(Capability.SDR50 == SDHOST_CAP1_SDR50_MASK)
    {
        /*check re-tuning request*/
        if ((SDMMC_GetFlagStatus(SDHOSTx, (uint32_t)SDHOST_ReTuningEventFlag)) != RESET)
        {
            SDMMC_ClrFlag(SDHOSTx, (uint32_t)SDHOST_ReTuningEventFlag);
            return SDMMC_ReTuningRequest;
        }
        else
        {
            /* no process */
        }
    }
    else
    {
        /* no process */
    }

    if (data != NULL)
    {
        /* Update ADMA descriptor table according to different DMA mode(SDMA, ADMA2).*/
        if ((dmaConfig != NULL) && (!executeTuning))
        {
            status_value = SDMMC_SetAdmaTableConfig(SDHOSTx, dmaConfig, data, TMODE_struct);
        }

        blockSize     = data->blockSize;
        blockCount    = data->blockCount;

        if(data->AutoCommand12_23 == AutoCommand12)
        {
            transferFlags = (uint32_t)SDMMC_DataWithAutoCmd12;
        }
        else if(data->AutoCommand12_23 == AutoCommand23)
        {
            transferFlags = (uint32_t)SDMMC_DataWithAutoCmd23;
        }
        else
        {
            transferFlags = 0;
        }

        transferFlags |= ((data->txData != NULL) ? (uint32_t)SDMMC_CommandAndTxData : (uint32_t)SDMMC_CommandAndRxData);
        transferFlags |= ((data->dataType == (uint8_t)SDHOST_TransferDataBoot) ? (uint32_t)SDMMC_BootData : 0U);
        transferFlags |=
            ((data->dataType == (uint8_t)SDHOST_TransferDataBootcontinous) ? (uint32_t)SDMMC_BootDataContinuous : 0U);

        command->flags |= (uint32_t)SDHOST_DataPresentFlag;
    }

    /* if the DMA desciptor configure fail or not needed , disable it */
    if (status_value != SDMMC_SUCCESS)
    {
        enDMA = DISABLE;
        /* disable DMA, using polling mode in this situation */
        TMODE_struct->DMAE = SDHOST_TMODE_DMADISABLE;
    }

    /* config the data transfer parameter */
    status_value = SDMMC_TransferConfig(SDHOSTx, transferFlags, blockSize, blockCount, TMODE_struct);

    if (status_value != SDMMC_SUCCESS)
    {
        return status_value;
    }

    /* send command first */
    SDMMC_SendCommand(SDHOSTx, command, TMODE_struct);

    /* wait command done */
    if(data->dataType == (uint32_t)SDHOST_TransferDataNormal)
    {
        CMDdone = ENABLE;
    }
    else
    {
        CMDdone = DISABLE;
    }

    status_value = SDMMC_WaitCommandDone(SDHOSTx, command, CMDdone);

    if (SDMMC_SUCCESS != status_value)
    {
        return SDMMC_SendCommandFailed;
    }

    /* wait transfer data finsih */
    if (data != NULL)
    {
        status_value = SDMMC_TransferDataBlocking(SDHOSTx, data, enDMA);

        if (SDMMC_SUCCESS != status_value)
        {
            return status_value;
        }
    }

    return SDMMC_SUCCESS;
}



/**
 *\*\name   SDMMC_EnableManualTuning.
 *\*\fun    Manually adjust SDCLK output delay.
 *\*\param  SDMMCx :
 *\*\          - SDMMC1
 *\*\          - SDMMC2
 *\*\param  delay :
 *\*\          - 0x00~0x0F   1~16 delay tap
 *\*\param  cmd :
 *\*\          - ENABLE
 *\*\          - DISABLE
 *\*\note   When manually adjusting, SDHOST should not be in working state (transmission state).
 *\*\note   After executing this function, it is necessary to call the enable parameter of SDMMC_SampleClockSet API.
 */
void SDMMC_EnableManualTuningOut(SDMMC_Module* SDMMCx, uint32_t delay, FunctionalState cmd)
{
    SDMMCx->DLYCTRL &= (~SDMMC_MANUALTUNOUT_DELAYMASK);
    SDMMCx->DLYCTRL |= (delay << REG_BIT7_OFFSET);

    if (cmd == ENABLE)
    {
        SDMMCx->DLYCTRL |= SDMMC_MANUALTUNOUT_EN;
    }
    else
    {
        SDMMCx->DLYCTRL &= (~SDMMC_MANUALTUNOUT_EN);
    }
}


/**
 *\*\name   SDMMC_EnableManualTuningIN.
 *\*\fun    Manually adjust rxclk input delay.
 *\*\param  SDMMCx :
 *\*\          - SDMMC1
 *\*\          - SDMMC2
 *\*\param  delay :
 *\*\          - 0x00~0x1F   1~32 delay tap
 *\*\param  cmd :
 *\*\          - ENABLE
 *\*\          - DISABLE
 *\*\note   When manually adjusting, SDHOST should not be in working state (transmission state).
 *\*\note   After executing this function, it is necessary to call the enable parameter of SDMMC_SampleClockSet API.
 */
void SDMMC_EnableManualTuningIN(SDMMC_Module* SDMMCx, uint32_t delay, FunctionalState cmd)
{
    SDMMCx->DLYCTRL &= (~SDMMC_MANUALTUNGATE_EN);

    SDMMCx->DLYCTRL &= (~SDMMC_MANUALTUNIN_DELAYMASK);
    SDMMCx->DLYCTRL |= delay;

    if (cmd == ENABLE)
    {
        SDMMCx->DLYCTRL |= SDMMC_MANUALTUNIN_EN;
        SDMMCx->DLYCTRL |= SDMMC_MANUALTUNGATE_EN;
    }
    else
    {
        SDMMCx->DLYCTRL &= (~SDMMC_MANUALTUNIN_EN);
    }
}

/**
 *\*\name   SDMMC_FixedSampleClock.
 *\*\fun    Fixed clock for data sampling.
 *\*\param  SDHOSTx :
 *\*\          - SDHOST1
 *\*\          - SDHOST2
 *\*\return none.
 */
void SDMMC_FixedSampleClock(SDHOST_Module* SDHOSTx)
{
    SDHOSTx->CTRLSTS &= (~SDHOST_SAMPCLKSEL);
}

/**
 *\*\name   SDMMC_EnableAutoTuning.
 *\*\fun    the auto tuning enbale for CMD/DATA line.
 *\*\param  SDHOSTx :
 *\*\          - SDHOST1
 *\*\          - SDHOST2
 *\*\param  cmd :
 *\*\          - ENABLE
 *\*\          - DISABLE
 *\*\return none.
 */
void SDMMC_EnableAutoTuning(SDHOST_Module* SDHOSTx, FunctionalState cmd)
{
    if (cmd == ENABLE)
    {
        SDHOSTx->CTRLSTS |= SDHOST_AUTOTUNE;
    }
    else
    {
        SDHOSTx->CTRLSTS &= (~SDHOST_AUTOTUNE);
    }
}


/**
 *\*\name   SDMMC_ConfigInt.
 *\*\fun    Enables or disables the interrupt signal corresponding to the interrupt status flag.
 *\*\param  SDHOSTx :
 *\*\          - SDHOST1
 *\*\          - SDHOST2
 *\*\param  SDHOST_Flag :
 *\*\          - SDHOST_CommandCompleteFlag
 *\*\          - SDHOST_DataCompleteFlag
 *\*\          - SDHOST_BlockGapEventFlag
 *\*\          - SDHOST_DmaCompleteFlag
 *\*\          - SDHOST_BufferWriteReadyFlag
 *\*\          - SDHOST_BufferReadReadyFlag
 *\*\          - SDHOST_CardInsertionFlag
 *\*\          - SDHOST_CardRemovalFlag
 *\*\          - SDHOST_CardInterruptFlag
 *\*\          - SDHOST_ReTuningEventFlag
 *\*\          - SDHOST_BootACKRcvFlag
 *\*\          - SDHOST_BootTerminateFlag
 *\*\          - SDHOST_CommandTimeoutFlag
 *\*\          - SDHOST_CommandCrcErrorFlag
 *\*\          - SDHOST_CommandEndBitErrorFlag
 *\*\          - SDHOST_CommandIndexErrorFlag
 *\*\          - SDHOST_DataTimeoutFlag
 *\*\          - SDHOST_DataCrcErrorFlag
 *\*\          - SDHOST_DataEndBitErrorFlag
 *\*\          - SDHOST_AutoCommand12ErrorFlag
 *\*\          - SDHOST_DmaErrorFlag
 *\*\          - SDHOST_TargetResErrorFlag
 *\*\param   Cmd (The input parameters must be the following values):
 *\*\          - ENABLE
 *\*\          - DISABLE
 *\*\return none.
 */
void SDMMC_ConfigInt(SDHOST_Module* SDHOSTx, uint32_t SDHOST_Flag, FunctionalState Cmd)
{
    if(Cmd == ENABLE)
    {
        SDHOSTx->ISE |= SDHOST_Flag;
    }
    else
    {
        SDHOSTx->ISE &= (~SDHOST_Flag);
    }
}


/**
 *\*\name   SDMMC_EnableFlagStatus.
 *\*\fun    Can the enable/disable interrupt status be displayed.
 *\*\param  SDHOSTx :
 *\*\          - SDHOST1
 *\*\          - SDHOST2
 *\*\param  SDHOST_Flag :
 *\*\          - SDHOST_CommandCompleteFlag
 *\*\          - SDHOST_DataCompleteFlag
 *\*\          - SDHOST_BlockGapEventFlag
 *\*\          - SDHOST_DmaCompleteFlag
 *\*\          - SDHOST_BufferWriteReadyFlag
 *\*\          - SDHOST_BufferReadReadyFlag
 *\*\          - SDHOST_CardInsertionFlag
 *\*\          - SDHOST_CardRemovalFlag
 *\*\          - SDHOST_CardInterruptFlag
 *\*\          - SDHOST_ReTuningEventFlag
 *\*\          - SDHOST_BootACKRcvFlag
 *\*\          - SDHOST_BootTerminateFlag
 *\*\          - SDHOST_CommandTimeoutFlag
 *\*\          - SDHOST_CommandCrcErrorFlag
 *\*\          - SDHOST_CommandEndBitErrorFlag
 *\*\          - SDHOST_CommandIndexErrorFlag
 *\*\          - SDHOST_DataTimeoutFlag
 *\*\          - SDHOST_DataCrcErrorFlag
 *\*\          - SDHOST_DataEndBitErrorFlag
 *\*\          - SDHOST_AutoCommand12ErrorFlag
 *\*\          - SDHOST_DmaErrorFlag
 *\*\          - SDHOST_TargetResErrorFlag
 *\*\param   Cmd (The input parameters must be the following values):
 *\*\          - ENABLE
 *\*\          - DISABLE
 *\*\return none.
 */
void SDMMC_EnableFlagStatus(SDHOST_Module* SDHOSTx, uint32_t SDHOST_Flag, FunctionalState Cmd)
{
    if(Cmd == ENABLE)
    {
        SDHOSTx->IE |= SDHOST_Flag;
    }
    else
    {
        SDHOSTx->IE &= (~SDHOST_Flag);
    }
}

/**
 *\*\name   SDMMC_GetEnableFlagStatus.
 *\*\fun    Gets the enabled interrupt status.
 *\*\param  SDHOSTx :
 *\*\          - SDHOST1
 *\*\          - SDHOST2
 *\*\param  SDHOST_Flag :
 *\*\          - SDHOST_CommandCompleteFlag
 *\*\          - SDHOST_DataCompleteFlag
 *\*\          - SDHOST_BlockGapEventFlag
 *\*\          - SDHOST_DmaCompleteFlag
 *\*\          - SDHOST_BufferWriteReadyFlag
 *\*\          - SDHOST_BufferReadReadyFlag
 *\*\          - SDHOST_CardInsertionFlag
 *\*\          - SDHOST_CardRemovalFlag
 *\*\          - SDHOST_CardInterruptFlag
 *\*\          - SDHOST_ReTuningEventFlag
 *\*\          - SDHOST_BootACKRcvFlag
 *\*\          - SDHOST_BootTerminateFlag
 *\*\          - SDHOST_CommandTimeoutFlag
 *\*\          - SDHOST_CommandCrcErrorFlag
 *\*\          - SDHOST_CommandEndBitErrorFlag
 *\*\          - SDHOST_CommandIndexErrorFlag
 *\*\          - SDHOST_DataTimeoutFlag
 *\*\          - SDHOST_DataCrcErrorFlag
 *\*\          - SDHOST_DataEndBitErrorFlag
 *\*\          - SDHOST_AutoCommand12ErrorFlag
 *\*\          - SDHOST_DmaErrorFlag
 *\*\          - SDHOST_TargetResErrorFlag
 *\*\return none.
 */
FlagStatus SDMMC_GetEnableFlagStatus(SDHOST_Module* SDHOSTx, uint32_t SDHOST_Flag)
{
    FlagStatus bitstatus;

    if ((SDHOSTx->IE & SDHOST_Flag) != (uint32_t)RESET)
    {
        bitstatus = SET;
    }
    else
    {
        bitstatus = RESET;
    }

    return bitstatus;
}


/**
 *\*\name   SDMMC_GetFlagStatus.
 *\*\fun    Checks whether the specified SDHOST flag is set or not.
 *\*\param  SDHOSTx :
 *\*\          - SDHOST1
 *\*\          - SDHOST2
 *\*\param  SDHOST_Flag :
 *\*\          - SDHOST_CommandCompleteFlag
 *\*\          - SDHOST_DataCompleteFlag
 *\*\          - SDHOST_BlockGapEventFlag
 *\*\          - SDHOST_DmaCompleteFlag
 *\*\          - SDHOST_BufferWriteReadyFlag
 *\*\          - SDHOST_BufferReadReadyFlag
 *\*\          - SDHOST_CardInsertionFlag
 *\*\          - SDHOST_CardRemovalFlag
 *\*\          - SDHOST_CardInterruptFlag
 *\*\          - SDHOST_ReTuningEventFlag
 *\*\          - SDHOST_BootACKRcvFlag
 *\*\          - SDHOST_BootTerminateFlag
 *\*\          - SDHOST_AllErrorFlag
 *\*\          - SDHOST_CommandTimeoutFlag
 *\*\          - SDHOST_CommandCrcErrorFlag
 *\*\          - SDHOST_CommandEndBitErrorFlag
 *\*\          - SDHOST_CommandIndexErrorFlag
 *\*\          - SDHOST_DataTimeoutFlag
 *\*\          - SDHOST_DataCrcErrorFlag
 *\*\          - SDHOST_DataEndBitErrorFlag
 *\*\          - SDHOST_AutoCommand12ErrorFlag
 *\*\          - SDHOST_DmaErrorFlag
 *\*\          - SDHOST_TargetResErrorFlag
 *\*\return bitstatus.
 *\*\          - SET
 *\*\          - RESET
 */
FlagStatus SDMMC_GetFlagStatus(SDHOST_Module* SDHOSTx, uint32_t SDHOST_Flag)
{
    FlagStatus bitstatus;

    if ((SDHOSTx->INTSTS & SDHOST_Flag) != (uint32_t)RESET)
    {
        bitstatus = SET;
    }
    else
    {
        bitstatus = RESET;
    }

    return bitstatus;
}


/**
 *\*\name   SDMMC_ClrFlag.
 *\*\fun    This function is used to clear a specified interrupt status.
 *\*\param  SDHOSTx :
 *\*\          - SDHOST1
 *\*\          - SDHOST2
 *\*\param  SDHOST_Flag :
 *\*\          - SDHOST_CommandCompleteFlag
 *\*\          - SDHOST_DataCompleteFlag
 *\*\          - SDHOST_BlockGapEventFlag
 *\*\          - SDHOST_DmaCompleteFlag
 *\*\          - SDHOST_BufferWriteReadyFlag
 *\*\          - SDHOST_BufferReadReadyFlag
 *\*\          - SDHOST_CardInsertionFlag
 *\*\          - SDHOST_CardRemovalFlag
 *\*\          - SDHOST_ReTuningEventFlag
 *\*\          - SDHOST_BootACKRcvFlag
 *\*\          - SDHOST_BootTerminateFlag
 *\*\          - SDHOST_CommandTimeoutFlag
 *\*\          - SDHOST_CommandCrcErrorFlag
 *\*\          - SDHOST_CommandEndBitErrorFlag
 *\*\          - SDHOST_CommandIndexErrorFlag
 *\*\          - SDHOST_DataTimeoutFlag
 *\*\          - SDHOST_DataCrcErrorFlag
 *\*\          - SDHOST_DataEndBitErrorFlag
 *\*\          - SDHOST_AutoCommand12ErrorFlag
 *\*\          - SDHOST_DmaErrorFlag
 *\*\          - SDHOST_TargetResErrorFlag
 *\*\return none.
 */
void SDMMC_ClrFlag(SDHOST_Module* SDHOSTx, uint32_t SDHOST_Flag)
{
    SDHOSTx->INTSTS = SDHOST_Flag;
}


/**
 *\*\name   SDMMC_EnableForceEvent.
 *\*\fun    Forces generating events according to the given mask.
 *\*\param  SDHOSTx :
 *\*\          - SDHOST1
 *\*\          - SDHOST2
 *\*\param  SDHOST_Flag :
 *\*\          - SDHOST_ForceEventAutoCommand12NotExecuted
 *\*\          - SDHOST_ForceEventAutoCommand12Timeout
 *\*\          - SDHOST_ForceEventAutoCommand12CrcError
 *\*\          - SDHOST_ForceEventAutoCommandEndBitError
 *\*\          - SDHOST_ForceEventAutoCommand12IndexError
 *\*\          - SDHOST_ForceEventAutoCommand12NotIssued
 *\*\          - SDHOST_ForceEventCommandTimeout
 *\*\          - SDHOST_ForceEventCommandCrcError
 *\*\          - SDHOST_ForceEventCommandEndBitError
 *\*\          - SDHOST_ForceEventCommandIndexError
 *\*\          - SDHOST_ForceEventDataTimeout
 *\*\          - SDHOST_ForceEventDataCrcError
 *\*\          - SDHOST_ForceEventDataEndBitError
 *\*\          - SDHOST_ForceEventAutoCommand12Error
 *\*\          - SDHOST_ForceEventAdmaError
 *\*\param   Cmd (The input parameters must be the following values):
 *\*\          - ENABLE
 *\*\          - DISABLE
 *\*\return none.
 */
void SDMMC_EnableForceEvent(SDHOST_Module* SDHOSTx, uint32_t SDHOST_Flag, FunctionalState Cmd)
{
    if(Cmd == ENABLE)
    {
        SDHOSTx->STSFE |= SDHOST_Flag;
    }
    else
    {
        SDHOSTx->STSFE &= (~SDHOST_Flag);
    }
}


/**
 *\*\name   SDMMC_GetPresentFlagStatus.
 *\*\fun    Checks whether the specified SDHOST Present flag is set or not.
 *\*\param  SDHOSTx :
 *\*\          - SDHOST1
 *\*\          - SDHOST2
 *\*\param  SDHOST_PreFlag :
 *\*\          - SDHOST_CommandInhibitFlag
 *\*\          - SDHOST_DataInhibitFlag
 *\*\          - SDHOST_DataLineActiveFlag
 *\*\          - SDHOST_ReTuningRequestFlag
 *\*\          - SDHOST_WriteTransferActiveFlag
 *\*\          - SDHOST_ReadTransferActiveFlag
 *\*\          - SDHOST_BufferWriteEnableFlag
 *\*\          - SDHOST_BufferReadEnableFlag
 *\*\          - SDHOST_CardInsertedFlag
 *\*\          - SDHOST_CardStateStableFlag
 *\*\          - SDHOST_CardDetectPinFlag
 *\*\          - SDHOST_CardWPSwitchPinFlag
 *\*\          - SDHOST_CommandLineLevelFlag
 *\*\          - SDHOST_Data0LineLevelFlag
 *\*\          - SDHOST_Data1LineLevelFlag
 *\*\          - SDHOST_Data2LineLevelFlag
 *\*\          - SDHOST_Data3LineLevelFlag
 *\*\          - SDHOST_Data4LineLevelFlag
 *\*\          - SDHOST_Data5LineLevelFlag
 *\*\          - SDHOST_Data6LineLevelFlag
 *\*\          - SDHOST_Data7LineLevelFlag
 *\*\return bitstatus.
 *\*\          - SET
 *\*\          - RESET
 *\*\return none.
 */
FlagStatus SDMMC_GetPresentFlagStatus(SDHOST_Module* SDHOSTx, uint32_t SDHOST_PreFlag)
{
    FlagStatus bitstatus;

    if ((SDHOSTx->PRESTS & SDHOST_PreFlag) != (uint32_t)RESET)
    {
        bitstatus = SET;
    }
    else
    {
        bitstatus = RESET;
    }

    return bitstatus;
}


/**
 *\*\name   SDMMC_GetACMDErrorStatusFlag.
 *\*\fun    Gets the status of auto command 12/23 error.
 *\*\param  SDHOSTx :
 *\*\          - SDHOST1
 *\*\          - SDHOST2
 *\*\param  SDHOST_PreFlag :
 *\*\          - SDHOST_AutoCommand12NotExecutedFlag
 *\*\          - SDHOST_AutoCommand12TimeoutFlag
 *\*\          - SDHOST_AutoCommand12EndBitErrorFlag
 *\*\          - SDHOST_AutoCommand12CrcErrorFlag
 *\*\          - SDHOST_AutoCommand12IndexErrorFlag
 *\*\          - SDHOST_AutoCommand12NotIssuedFlag
 *\*\return bitstatus.
 *\*\          - SET
 *\*\          - RESET
 *\*\return none.
 */
FlagStatus SDMMC_GetACMDErrorStatusFlag(SDHOST_Module* SDHOSTx, uint32_t SDHOST_ACMDFlag)
{
    FlagStatus bitstatus;

    if ((SDHOSTx->CTRLSTS & SDHOST_ACMDFlag) != (uint32_t)RESET)
    {
        bitstatus = SET;
    }
    else
    {
        bitstatus = RESET;
    }

    return bitstatus;
}


/**
 *\*\name   SDMMC_GetADMAErrorStatusFlag.
 *\*\fun    Gets the status of ADMA error.
 *\*\param  SDHOSTx :
 *\*\          - SDHOST1
 *\*\          - SDHOST2
 *\*\param  SDHOST_PreFlag :
 *\*\          - SDHOST_AdmaLenghMismatchFlag
 *\*\return bitstatus.
 *\*\          - SET
 *\*\          - RESET
 *\*\return none.
 */
FlagStatus SDMMC_GetADMAErrorStatusFlag(SDHOST_Module* SDHOSTx, uint32_t SDHOST_ADMAFlag)
{
    FlagStatus bitstatus;

    if ((SDHOSTx->ADMAESTS & SDHOST_ADMAFlag) != (uint32_t)RESET)
    {
        bitstatus = SET;
    }
    else
    {
        bitstatus = RESET;
    }

    return bitstatus;
}


/**
 *\*\name    SDMMC_EnableHWReset
 *\*\fun     Triggers a hardware reset.
 *\*\param   SDHOSTx :
 *\*\          - SDHOST1
 *\*\          - SDHOST2
 *\*\param   Cmd (The input parameters must be the following values):
 *\*\          - ENABLE
 *\*\          - DISABLE
 *\*\return  none
 */
void SDMMC_EnableHWReset(SDHOST_Module* SDHOSTx, FunctionalState Cmd)
{
    if (Cmd != DISABLE)
    {
        SDHOSTx->CTRL1 |= SDHOST_CTRL1_HWRST;
    }
    else
    {
        SDHOSTx->CTRL1 &= (~SDHOST_CTRL1_HWRST);
    }
}


/**
 *\*\name    SDMMC_ConfigWorkMode
 *\*\fun     Configure working mode.
 *\*\param   SDHOSTx :
 *\*\          - SDHOST1
 *\*\          - SDHOST2
 *\*\param   mode (The input parameters must be the following values):
 *\*\          - SDMMC_DS
 *\*\          - SDMMC_HS
 *\*\          - SDMMC_SDR12
 *\*\          - SDMMC_SDR25
 *\*\          - SDMMC_SDR50
 *\*\          - SDMMC_SDR104
 *\*\          - SDMMC_DDR50
 *\*\          - SDMMC_SPI
 *\*\return  none
 */
void SDMMC_ConfigWorkMode(SDHOST_Module* SDHOSTx, SD_ModeConfig mode)
{
    if(mode == SDMMC_SPI)
    {
        SDHOSTx->CTRL1 |= SDHOST_CTRL1_SPIMODE;
    }
    else
    {
        SDHOSTx->CTRL1 &= (~SDHOST_CTRL1_SPIMODE);

        if (mode == SDMMC_DS)
        {
            SDHOSTx->CTRL1 &= (~SDHOST_CTRL1_HSEN);
        }
        else if (mode == SDMMC_HS)
        {
            SDHOSTx->CTRL1 |= SDHOST_CTRL1_HSEN;
        }
        else if(mode == SDMMC_SDR12)
        {
            SDHOSTx->CTRL1 |= SDHOST_CTRL1_HSEN;
            SDHOSTx->CTRLSTS &= (~SDHOST_CTRLSTS_UHSMOD);
        }
        else if(mode == SDMMC_SDR25)
        {
            SDHOSTx->CTRL1 |= SDHOST_CTRL1_HSEN;
            SDHOSTx->CTRLSTS &= (~SDHOST_CTRLSTS_UHSMOD);
            SDHOSTx->CTRLSTS |= SDHOST_CTRLSTS_UHSMOD_0;
        }
        else if(mode == SDMMC_SDR50)
        {
            SDHOSTx->CTRL1 |= SDHOST_CTRL1_HSEN;
            SDHOSTx->CTRLSTS &= (~SDHOST_CTRLSTS_UHSMOD);
            SDHOSTx->CTRLSTS |= SDHOST_CTRLSTS_UHSMOD_1;
        }
        else if(mode == SDMMC_SDR104)
        {
            SDHOSTx->CTRL1 |= SDHOST_CTRL1_HSEN;
            SDHOSTx->CTRLSTS &= (~SDHOST_CTRLSTS_UHSMOD);
            SDHOSTx->CTRLSTS |= (SDHOST_CTRLSTS_UHSMOD_0 | SDHOST_CTRLSTS_UHSMOD_1);
        }
        else
        {
            SDHOSTx->CTRL1 |= SDHOST_CTRL1_HSEN;
            SDHOSTx->CTRLSTS &= (~SDHOST_CTRLSTS_UHSMOD);
            SDHOSTx->CTRLSTS |= SDHOST_CTRLSTS_UHSMOD_2;
        }
    }
}


/**
 *\*\name    SDMMC_ConfigBusWidth
 *\*\fun     Sets the data transfer width.
 *\*\param   SDHOSTx :
 *\*\          - SDHOST1
 *\*\          - SDHOST2
 *\*\param   Width (The input parameters must be the following values):
 *\*\          - SDHOST_DataBusWidth1Bit
 *\*\          - SDHOST_DataBusWidth4Bit
 *\*\          - SDHOST_DataBusWidth8Bit
 *\*\return  none
 */
void SDMMC_ConfigBusWidth(SDHOST_Module* SDHOSTx, SDHOST_BusWidth Width)
{
    if (Width != SDHOST_DataBusWidth8Bit)
    {
        SDHOSTx->CTRL1 &= (~SDHOST_CTRL1_EDTWIDTH);

        if (Width != SDHOST_DataBusWidth4Bit)
        {
            SDHOSTx->CTRL1 &= (~SDHOST_CTRL1_DTWIDTH);
        }
        else
        {
            SDHOSTx->CTRL1 |= SDHOST_CTRL1_DTWIDTH;
        }
    }
    else
    {
        SDHOSTx->CTRL1 |= SDHOST_CTRL1_EDTWIDTH;
    }
}


/**
 *\*\name   SDMMC_WriteData.
 *\*\fun    This function is used to implement the data transfer by Data Port instead of DMA.
 *\*\param  SDHOSTx :
 *\*\          - SDHOST1
 *\*\          - SDHOST2
 *\*\return none.
 */
void SDMMC_WriteData(SDHOST_Module* SDHOSTx, uint32_t data)
{
    SDHOSTx->BUFDAT = data;
}

/**
 *\*\name   SDMMC_ReadData.
 *\*\fun    This function is used to implement the data transfer by Data Port instead of DMA.
 *\*\param  SDHOSTx :
 *\*\          - SDHOST1
 *\*\          - SDHOST2
 *\*\return The data has been read.
 */
uint32_t SDMMC_ReadData(SDHOST_Module* SDHOSTx)
{
    return SDHOSTx->BUFDAT;
}


/**
 *\*\name    SDMMC_EnableWakeupEvent
 *\*\fun     Enables or disables a wakeup event.
 *\*\param   SDHOSTx :
 *\*\          - SDHOST1
 *\*\          - SDHOST2
 *\*\param   Wakeupevent :
 *\*\          - SDHOST_WakeupEventOnCardInt
 *\*\          - SDHOST_WakeupEventOnCardInsert
 *\*\          - SDHOST_WakeupEventOnCardRemove
 *\*\          - SDHOST_WakeupEventsAll
 *\*\param   Cmd (The input parameters must be the following values):
 *\*\          - ENABLE
 *\*\          - DISABLE
 *\*\return  none
 */
void SDMMC_EnableWakeupEvent(SDHOST_Module* SDHOSTx, uint32_t Wakeupevent, FunctionalState Cmd)
{
    if (Cmd != DISABLE)
    {
        SDHOSTx->CTRL1 |= Wakeupevent;
    }
    else
    {
        SDHOSTx->CTRL1 &= (~Wakeupevent);
    }
}


/**
 *\*\name    SDMMC_EnableSdioControl
 *\*\fun     Enables or disables the SDIO card control.
 *\*\param   SDHOSTx :
 *\*\          - SDHOST1
 *\*\          - SDHOST2
 *\*\param   Wakeupevent :
 *\*\          - SDHOST_StopAtBlockGapFlag
 *\*\          - SDHOST_ReadWaitControlFlag
 *\*\          - SDHOST_InterruptAtBlockGapFlag
 *\*\param   Cmd (The input parameters must be the following values):
 *\*\          - ENABLE
 *\*\          - DISABLE
 *\*\return  none
 */
void SDMMC_EnableSdioControl(SDHOST_Module* SDHOSTx, uint32_t Sdioflag, FunctionalState Cmd)
{
    if (Cmd != DISABLE)
    {
        SDHOSTx->CTRL1 |= Sdioflag;
    }
    else
    {
        SDHOSTx->CTRL1 &= (~Sdioflag);
    }
}


/**
 *\*\name    SDMMC_EnableContinueRequest
 *\*\fun     Restarts a transaction which has stopped at the block GAP for the SDIO card.
 *\*\param   SDHOSTx :
 *\*\          - SDHOST1
 *\*\          - SDHOST2
 *\*\return  none
 */
void SDMMC_EnableContinueRequest(SDHOST_Module* SDHOSTx)
{
    SDHOSTx->CTRL1 |= SDHOST_CTRL1_CONTREQ;
}


/**
 *\*\name    SDMMC_EnableMmcBoot
 *\*\fun     Enables or disables the mmc boot mode.
 *\*\param   SDHOSTx :
 *\*\          - SDHOST1
 *\*\          - SDHOST2
 *\*\param   Cmd (The input parameters must be the following values):
 *\*\          - ENABLE
 *\*\          - DISABLE
 *\*\return  none
 */
void SDMMC_EnableMmcBoot(SDHOST_Module* SDHOSTx, FunctionalState Cmd)
{
    if (Cmd != DISABLE)
    {
        SDHOSTx->CTRL1 |= SDHOST_CTRL1_BOOTEN;
    }
    else
    {
        SDHOSTx->CTRL1 &= (~SDHOST_CTRL1_BOOTEN);
    }
}


/**
 *\*\name    SDMMC_EnableVolSwitch
 *\*\fun     Enables or disables voltage switching, signal voltage will change from 3.3V to 1.8V.
 *\*\param   SDHOSTx :
 *\*\          - SDHOST1
 *\*\          - SDHOST2
 *\*\param   Cmd (The input parameters must be the following values):
 *\*\          - ENABLE
 *\*\          - DISABLE
 *\*\return  none
 */
void SDMMC_EnableVolSwitch(SDHOST_Module* SDHOSTx, FunctionalState Cmd)
{
    if (Cmd != DISABLE)
    {
        SDHOSTx->CTRLSTS |= SDHOST_CTRLSTS_V18SE;
    }
    else
    {
        SDHOSTx->CTRLSTS &= (~SDHOST_CTRLSTS_V18SE);
    }
}


/**
 *\*\name    SDMMC_EnablePower
 *\*\fun     Enables or disables SD Bus Power.
 *\*\param   SDHOSTx :
 *\*\          - SDHOST1
 *\*\          - SDHOST2
 *\*\param   Cmd (The input parameters must be the following values):
 *\*\          - ENABLE
 *\*\          - DISABLE
 *\*\return  none
 */
void SDMMC_EnablePower(SDHOST_Module* SDHOSTx, FunctionalState Cmd)
{
    if (Cmd != DISABLE)
    {
        SDHOSTx->CTRL1 |= SDHOST_CTRL1_SDBVSEL;
        SDHOSTx->CTRL1 |= SDHOST_CTRL1_SDPWR;
    }
    else
    {
        SDHOSTx->CTRL1 &= (~SDHOST_CTRL1_SDPWR);
    }
}


/**
 *\*\name    SDMMC_ConfigSDMABufferSize
 *\*\fun     Config Host SDMA Buffer Size.
 *\*\param   SDHOSTx :
 *\*\          - SDHOST1
 *\*\          - SDHOST2
 *\*\param   Size (The input parameters must be the following values):
 *\*\          - SDHOST_SDMABUFFERSIZE_4KB
 *\*\          - SDHOST_SDMABUFFERSIZE_8KB
 *\*\          - SDHOST_SDMABUFFERSIZE_16KB
 *\*\          - SDHOST_SDMABUFFERSIZE_32KB
 *\*\          - SDHOST_SDMABUFFERSIZE_64KB
 *\*\          - SDHOST_SDMABUFFERSIZE_128KB
 *\*\          - SDHOST_SDMABUFFERSIZE_256KB
 *\*\          - SDHOST_SDMABUFFERSIZE_512KB
 *\*\return  none
 */
void SDMMC_ConfigSDMABufferSize(SDHOST_Module* SDHOSTx, SDHOST_SDMA_Buffer_Size Size)
{
    SDHOSTx->BLKCFG &= (~SDHOST_BLKCFG_HDBS);
    SDHOSTx->BLKCFG |= (uint32_t)Size;
}


/**
 *\*\name   SDMMC_TModeStructInit.
 *\*\fun    Fills each TMODE_struct member with its default value..
 *\*\param  TMODE_struct: pointer to a SDHOST_TMODE_struct structure.
 *\*\           - DMAE
 *\*\                - SDHOST_TMODE_DMADISABLE
 *\*\                - SDHOST_TMODE_DMAENABLE
 *\*\           - BCNTE
 *\*\                - SDHOST_TMODE_BLOCKCNTDISABLE
 *\*\                - SDHOST_TMODE_BLOCKCNTENABLE
 *\*\           - ACMDE
 *\*\                - SDHOST_TMODE_NOACMDEN
 *\*\                - SDHOST_TMODE_AC12EN
 *\*\                - SDHOST_TMODE_AC23EN
 *\*\           - DATDIR
 *\*\                - SDHOST_TMODE_DATDIR_WRITE
 *\*\                - SDHOST_TMODE_DATDIR_READ
 *\*\           - BLKSEL
 *\*\                - SDHOST_TMODE_SINGLEBLK
 *\*\                - SDHOST_TMODE_MULTIBLK
 *\*\return none
 */
void SDMMC_TModeStructInit(SDHOST_TMODE_struct *TMODE_struct)
{
    /* TMODE_struct members default value */
    TMODE_struct->DMAE    = SDHOST_TMODE_DMADISABLE;
    TMODE_struct->BCNTE   = SDHOST_TMODE_BLOCKCNTDISABLE;
    TMODE_struct->ACMDE   = SDHOST_TMODE_NOACMDEN;
    TMODE_struct->DATDIR  = SDHOST_TMODE_DATDIR_WRITE;
    TMODE_struct->BLKSEL  = SDHOST_TMODE_SINGLEBLK;
}


/**
 *\*\name    SDMMC_ConfigCardDetectSignal
 *\*\fun     Config card detect signal source and test level.
 *\*\param   SDHOSTx :
 *\*\          - SDHOST1
 *\*\          - SDHOST2
 *\*\param   Signalsource (The input parameters must be the following values):
 *\*\          - SDMMC_CARDDETECT_NORMAL
 *\*\          - SDMMC_CARDDETECT_TEST
 *\*\param   Signallevel (The input parameters must be the following values):
 *\*\          - SDMMC_CARDTESTLEVEL_LOW
 *\*\          - SDMMC_CARDTESTLEVEL_HIGH
 *\*\return  none
 */
void SDMMC_ConfigCardDetectSignal(SDHOST_Module* SDHOSTx, uint32_t Signalsource, uint32_t Signallevel)
{
    SDHOSTx->CTRL1 &= (~(SDMMC_CARDDETECT_TEST | SDMMC_CARDTESTLEVEL_HIGH));
    SDHOSTx->CTRL1 |= (Signalsource | Signallevel);
}


/**
 *\*\name    SDMMC_EnableLED
 *\*\fun     Enables or disables LED.
 *\*\param   SDHOSTx :
 *\*\          - SDHOST1
 *\*\          - SDHOST2
 *\*\param   Cmd (The input parameters must be the following values):
 *\*\          - ENABLE
 *\*\          - DISABLE
 *\*\return  none
 */
void SDMMC_EnableLED(SDHOST_Module* SDHOSTx, FunctionalState Cmd)
{
    if (Cmd != DISABLE)
    {
        SDHOSTx->CTRL1 |= SDHOST_CTRL1_LEDCTRL;
    }
    else
    {
        SDHOSTx->CTRL1 &= (~SDHOST_CTRL1_LEDCTRL);
    }
}


/**
 *\*\name    SDMMC_EnableAsyncInt
 *\*\fun     Enables or disables Asynchronous Interrupt.
 *\*\param   SDHOSTx :
 *\*\          - SDHOST1
 *\*\          - SDHOST2
 *\*\param   Cmd (The input parameters must be the following values):
 *\*\          - ENABLE
 *\*\          - DISABLE
 *\*\return  none
 */
void SDMMC_EnableAsyncInt(SDHOST_Module* SDHOSTx, FunctionalState Cmd)
{
    if (Cmd != DISABLE)
    {
        SDHOSTx->CTRLSTS |= SDHOST_CTRLSTS_ASYNCIE;
    }
    else
    {
        SDHOSTx->CTRLSTS &= (~SDHOST_CTRLSTS_ASYNCIE);
    }
}


/**
 *\*\name    SDMMC_ConfigDATATimeoutValue
 *\*\fun     Config Data Level Timeout Counter Value.
 *\*\param   SDHOSTx :
 *\*\          - SDHOST1
 *\*\          - SDHOST2
 *\*\param   Count (The input parameters must be the following values):
 *\*\          - 0x0~0xF , The corresponding actual delay value is (1/TMCLK * 2^(Count + 13))
 *\*\return  none
 */
void SDMMC_ConfigDATATimeoutValue(SDHOST_Module* SDHOSTx, uint32_t Count)
{
    SDHOSTx->CTRL2 &= (~SDHOST_CTRL2_DTCNT);
    SDHOSTx->CTRL2 |= (Count << REG_BIT16_OFFSET);
}




