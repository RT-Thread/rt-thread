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
 * @file n32h76x_78x_femc.c
 * @author Nations
 * @version v1.0.0
 *
 * @copyright Copyright (c) 2025, Nations Technologies Inc. All rights reserved.
 */
#include "n32h76x_78x_femc.h"
#include "n32h76x_78x_rcc.h"
#include "stdio.h"


/**
*\*\name    FEMC_Init.
*\*\fun     Initializes the FEMC according to the specified parameters in the FEMC_InitStruct.
*\*\param   FEMC_InitStruct : pointer to a FEMC_InitType
*\*\        structure that contains the configuration information for
*\*\        the FEMC specified Bank or Blocks.
*\*\return  none
**/
void FEMC_Init(FEMC_InitType *FEMC_InitStruct)
{
    /* Set FEMC timing.*/
    FEMC->FEMC_TCFG = ((( FEMC_InitStruct->TimingCfg.Trc    << (0)) | \
                        (FEMC_InitStruct->TimingCfg.Twc    << (4)) | \
                        (FEMC_InitStruct->TimingCfg.Tcere  << (8)) | \
                        (FEMC_InitStruct->TimingCfg.Twp    << (11)) | \
                        (FEMC_InitStruct->TimingCfg.Tpcclr << (14)) | \
                        (FEMC_InitStruct->TimingCfg.Ttrar  << (17)) | \
                        (FEMC_InitStruct->TimingCfg.Twerr  << (20))) & \
                       (0x00FFFFFF));

    /* Set FEMC chip configuration.*/
    FEMC->FEMC_OMCFG = ((FEMC_InitStruct->ChipCfg.ReadSyncMode | \
                         FEMC_InitStruct->ChipCfg.ReadBurstLen | \
                         FEMC_InitStruct->ChipCfg.WriteSyncMode | \
                         FEMC_InitStruct->ChipCfg.WriteBurstLen | \
                         FEMC_InitStruct->ChipCfg.MemWidth | \
                         FEMC_InitStruct->ChipCfg.BAA | \
                         FEMC_InitStruct->ChipCfg.ADV | \
                         FEMC_InitStruct->ChipCfg.BLSS | \
                         FEMC_InitStruct->ChipCfg.BurstAlign) &
                        (0x0000FFFF));
}

/**
*\*\name    FEMC_InitStruct.
*\*\fun     Fills each FEMC_InitStruct member with its default value.
*\*\param   FEMC_InitStruct pointer to a FEMC_InitType structure which will be initialized.
*\*\return  none
**/
void FEMC_InitStruct(FEMC_InitType* FEMC_InitStruct)
{
    /* Reset NOR/SRAM Init structure parameters values */
    FEMC_InitStruct->TimingCfg.Trc      = 0;
    FEMC_InitStruct->TimingCfg.Twc      = 0;
    FEMC_InitStruct->TimingCfg.Tcere    = 0;
    FEMC_InitStruct->TimingCfg.Twp      = 0;
    FEMC_InitStruct->TimingCfg.Tpcclr   = 0;
    FEMC_InitStruct->TimingCfg.Ttrar    = 0;
    FEMC_InitStruct->TimingCfg.Twerr    = 0;

    FEMC_InitStruct->ChipCfg.ReadSyncMode  = FEMC_MEM_READ_ASYNC;
    FEMC_InitStruct->ChipCfg.ReadBurstLen  = FEMC_MEM_READ_BURST_1;
    FEMC_InitStruct->ChipCfg.WriteSyncMode = FEMC_MEM_WRITE_ASYNC;
    FEMC_InitStruct->ChipCfg.WriteBurstLen = FEMC_MEM_WRITE_BURST_1;
    FEMC_InitStruct->ChipCfg.MemWidth      = FEMC_MEMORY_WIDTH_16BIT;
    FEMC_InitStruct->ChipCfg.BAA           = FEMC_BAA_PORT_DISABLE;
    FEMC_InitStruct->ChipCfg.ADV           = FEMC_ADV_PORT_DISABLE;
    FEMC_InitStruct->ChipCfg.BLSS          = FEMC_BLS_SYNC_CS;
    FEMC_InitStruct->ChipCfg.BurstAlign    = FEMC_BURST_SPLIT_ON_256;
}

/**
*\*\name    FEMC_EnableNorSram.
*\*\fun     Enables or disables the specified NOR/SRAM Memory Bank.
*\*\param   Chip: The chip number.
*\*\          - SRAM_NOR_CHIP_1: SRAM Chip 1
*\*\          - SRAM_NOR_CHIP_2: SRAM Chip 2
*\*\          - SRAM_NOR_CHIP_3: SRAM Chip 3
*\*\          - SRAM_NOR_CHIP_4: SRAM Chip 4
*\*\          - NAND_CHIP_1: NAND Chip 1
*\*\          - NAND_CHIP_2: NAND Chip 2
*\*\param   Cmd: The command
*\*\          - FEMC_CMD_UPDATEREGS_AND_AXI:
*\*\          - FEMC_CMD_MDREGCONFIG: Configure mode register
*\*\          - FEMC_CMD_UPDATEREGS:  Update mode register
*\*\          - FEMC_CMD_MDREGCONFIG_AND_UPDATEREGS: Configure mode register and update
*\*\param   CrePolarity :
*\*\          - FEMC_CRE_POLARITY_LOW:  CRE is LOW
*\*\          - FEMC_CRE_POLARITY_HIGH: CRE is HIGH when ModeReg write occurs
*\*\param   Address:    0~0x000FFFFF
*\*\        The address parameter is valid when CMD type is MdRegConfig or MdRegConfig and UpdateRegs only.
*\*\return  none
**/
void FEMC_SetCommand(uint32_t Chip, uint32_t Cmd, uint32_t CrePolarity, uint32_t Address)
{
    /* Set FEMC_CTRL register for FEMC.*/
    FEMC->FEMC_CTRL = (Address | CrePolarity | Cmd | (Chip << 23));
}

/**
*\*\name    FEMC_CheckChipStatus.
*\*\fun     Check FEMC chip status register value.
*\*\param   Chip: The chip number.
*\*\          - SRAM_NOR_CHIP_1: SRAM Chip 1
*\*\          - SRAM_NOR_CHIP_2: SRAM Chip 2
*\*\          - SRAM_NOR_CHIP_3: SRAM Chip 3
*\*\          - SRAM_NOR_CHIP_4: SRAM Chip 4
*\*\          - NAND_CHIP_1: NAND Chip 1
*\*\          - NAND_CHIP_2: NAND Chip 2
*\*\param  ChipCfg: Pointer to a  FEMC_ChipInitType structure
*\*\return  SUCCESS or ERROR
**/
ErrorStatus FEMC_CheckChipStatus(uint32_t Chip, FEMC_ChipInitType *ChipCfg)
{
    uint32_t temp_value;
    uint32_t FEMC_OPMODE_Value = 0;

    temp_value = ((ChipCfg->ReadSyncMode | \
                   ChipCfg->ReadBurstLen | \
                   ChipCfg->WriteSyncMode | \
                   ChipCfg->WriteBurstLen | \
                   ChipCfg->MemWidth | \
                   ChipCfg->BAA | \
                   ChipCfg->ADV | \
                   ChipCfg->BLSS | \
                   ChipCfg->BurstAlign) & (0x0000FFFF)) ;

    switch(Chip)
    {
        case SRAM_NOR_CHIP_1:
            FEMC_OPMODE_Value = FEMC->block1.FEMC_SNOMSTS;
            temp_value |= (FEMC->FEMC_SNADD1 & (0xFFFF0000));
            break;

        case SRAM_NOR_CHIP_2:
            FEMC_OPMODE_Value = FEMC->block2.FEMC_SNOMSTS;
            temp_value |= (FEMC->FEMC_SNADD2 & (0xFFFF0000));
            break;

        case SRAM_NOR_CHIP_3:
            FEMC_OPMODE_Value = FEMC->block3.FEMC_SNOMSTS;
            temp_value |= (FEMC->FEMC_SNADD3 & (0xFFFF0000));
            break;

        case SRAM_NOR_CHIP_4:
            FEMC_OPMODE_Value = FEMC->block4.FEMC_SNOMSTS;
            temp_value |= (FEMC->FEMC_SNADD4 & (0xFFFF0000));
            break;

        case NAND_CHIP_1:
            FEMC_OPMODE_Value = FEMC->bank1.FEMC_NOMSTS;
            temp_value |= (FEMC->FEMC_NADD1 & (0xFFFF0000));
            break;

        case NAND_CHIP_2:
            FEMC_OPMODE_Value = FEMC->bank2.FEMC_NOMSTS;
            temp_value |= (FEMC->FEMC_NADD2 & (0xFFFF0000));
            break;

        default:
            break;
    }

    return (temp_value == FEMC_OPMODE_Value) ? SUCCESS : ERROR;
}

/**
*\*\name    FEMC_CheckTimingStatus.
*\*\fun     Check FEMC timing status register value.
*\*\param   Chip: The chip number.
*\*\          - SRAM_NOR_CHIP_1: SRAM Chip 1
*\*\          - SRAM_NOR_CHIP_2: SRAM Chip 2
*\*\          - SRAM_NOR_CHIP_3: SRAM Chip 3
*\*\          - SRAM_NOR_CHIP_4: SRAM Chip 4
*\*\          - NAND_CHIP_1: NAND Chip 1
*\*\          - NAND_CHIP_2: NAND Chip 2
*\*\param  ChipCfg: Pointer to a  FEMC_ChipInitType structure
*\*\return  SUCCESS or ERROR
**/
ErrorStatus FEMC_CheckTimingStatus(uint32_t Chip, FEMC_TimingInitType *TimingCfg)
{
    uint32_t temp_value;
    uint32_t FEMC_Timing_Value = 0;

    temp_value = ((TimingCfg->Trc    << (0)) | \
                  (TimingCfg->Twc    << (4)) | \
                  (TimingCfg->Tcere  << (8)) | \
                  (TimingCfg->Twp    << (11)) | \
                  (TimingCfg->Tpcclr << (14)) | \
                  (TimingCfg->Ttrar  << (17)) | \
                  (TimingCfg->Twerr  << (20))) & (0x00FFFFFF);

    switch(Chip)
    {
        case SRAM_NOR_CHIP_1:
            FEMC_Timing_Value = FEMC->block1.FEMC_SNTSTS;
            break;

        case SRAM_NOR_CHIP_2:
            FEMC_Timing_Value = FEMC->block2.FEMC_SNTSTS;
            break;

        case SRAM_NOR_CHIP_3:
            FEMC_Timing_Value = FEMC->block3.FEMC_SNTSTS;
            break;

        case SRAM_NOR_CHIP_4:
            FEMC_Timing_Value = FEMC->block4.FEMC_SNTSTS;
            break;

        case NAND_CHIP_1:
            FEMC_Timing_Value = FEMC->bank1.FEMC_NTSTS;
            break;

        case NAND_CHIP_2:
            FEMC_Timing_Value = FEMC->bank2.FEMC_NTSTS;
            break;

        default:
            break;
    }

    return (temp_value == FEMC_Timing_Value) ? SUCCESS : ERROR;
}

/**
*\*\name    FEMC_SetRefreshPeriod.
*\*\fun     Set FEMC refresh period value.
*\*\param   PeriodVal: 0~0x0F The FEMC refresh period value
*\*\return  none
**/
void FEMC_SetRefreshPeriod(uint32_t PeriodVal)
{
    FEMC->FEMC_RPE = PeriodVal;
}

/**
*\*\name    FEMC_GetRefreshPeriod.
*\*\fun     Get FEMC refresh period value.
*\*\param
*\*\return  The FEMC refresh period value
**/
uint32_t FEMC_GetRefreshPeriod(void)
{
    return (FEMC->FEMC_RPE & 0x0F);
}

/**
*\*\name    FEMC_SetAddressmatch.
*\*\fun     Set address and mask value for specific chip region.
*\*\param   Chip: The chip number.
*\*\          - SRAM_NOR_CHIP_1: SRAM Chip 1
*\*\          - SRAM_NOR_CHIP_2: SRAM Chip 2
*\*\          - SRAM_NOR_CHIP_3: SRAM Chip 3
*\*\          - SRAM_NOR_CHIP_4: SRAM Chip 4
*\*\          - NAND_CHIP_1: NAND Chip 1
*\*\          - NAND_CHIP_2: NAND Chip 2
*\*\param  Address_Match_Value: 0, 0X00010000~ 0xFFFF0000 The address and mask value for specific chip region
*\*\return  SUCCESS or ERROR
**/
void FEMC_SetAddressmatch(uint32_t Chip, uint32_t Address_Match_Value)
{
    switch(Chip)
    {
        case SRAM_NOR_CHIP_1:
            FEMC->FEMC_SNADD1 = Address_Match_Value;
            break;

        case SRAM_NOR_CHIP_2:
            FEMC->FEMC_SNADD2 = Address_Match_Value;
            break;

        case SRAM_NOR_CHIP_3:
            FEMC->FEMC_SNADD3 = Address_Match_Value;
            break;

        case SRAM_NOR_CHIP_4:
            FEMC->FEMC_SNADD4 = Address_Match_Value;
            break;

        case NAND_CHIP_1:
            FEMC->FEMC_NADD1 = Address_Match_Value;
            break;

        case NAND_CHIP_2:
            FEMC->FEMC_NADD2 = Address_Match_Value;
            break;

        default:
            break;
    }

}

/**
*\*\name    SRAM_MuxModeEnable.
*\*\fun     Enable or disable the SRAM interface multiplexed mode.
*\*\param   NewState: new state of the multiplexed mode.
*\*\          - ENABLE
*\*\          - DISABLE
*\*\return  none
**/
void FEMC_SRAMMuxModeEnable(FunctionalState NewState)
{
    if(NewState == ENABLE)
    {
        FEMC->FEMC_SNMOD |= FEMC_SNMOD_MUXEN;
    }
    else
    {
        FEMC->FEMC_SNMOD &= ~FEMC_SNMOD_MUXEN;
    }
}

/**
*\*\name    FEMC_SRAMAGTMEnable.
*\*\fun     Enable or disable aclk faster than SRAM clock.
*\*\param   NewState:
*\*\          - ENABLE
*\*\          - DISABLE
*\*\return  none
**/
void FEMC_SRAMAGTMEnable(FunctionalState NewState)
{
    if(NewState == ENABLE)
    {
        FEMC->FEMC_SNMOD |= FEMC_SNMOD_AGTM;
    }
    else
    {
        FEMC->FEMC_SNMOD &= ~FEMC_SNMOD_AGTM;
    }
}

/**
*\*\name    FEMC_SRAMSYNCEnable.
*\*\fun     Enable or disable the SRAM clock synchronous to aclk.
*\*\param   NewState:
*\*\          - ENABLE
*\*\          - DISABLE
*\*\return  none
**/
void FEMC_SRAMSYNCEnable(FunctionalState NewState)
{
    if(NewState == ENABLE)
    {
        FEMC->FEMC_SNMOD |= FEMC_SNMOD_SYNC;
    }
    else
    {
        FEMC->FEMC_SNMOD &= ~FEMC_SNMOD_SYNC;
    }
}

/**
*\*\name    FEMC_NANDCSLEnable.
*\*\fun     Enable or disable NAND chip select remains asserted between the address phase and data phase.
*\*\param   NewState:
*\*\          - ENABLE
*\*\          - DISABLE
*\*\return  none
**/
void FEMC_NANDCSLEnable(FunctionalState NewState)
{
    if(NewState == ENABLE)
    {
        FEMC->FEMC_NMOD |= FEMC_NMOD_CSL;
    }
    else
    {
        FEMC->FEMC_NMOD &= ~FEMC_NMOD_CSL;
    }
}


/**
*\*\name    FEMC_NANDAGTMEnable.
*\*\fun     Enable or disable aclk faster than NAND clock.
*\*\param   NewState:
*\*\          - ENABLE
*\*\          - DISABLE
*\*\return  none
**/
void FEMC_NANDAGTMEnable(FunctionalState NewState)
{
    if(NewState == ENABLE)
    {
        FEMC->FEMC_NMOD |= FEMC_NMOD_AGTM;
    }
    else
    {
        FEMC->FEMC_NMOD &= ~FEMC_NMOD_AGTM;
    }
}

/**
*\*\name    FEMC_NANDSYNCEnable.
*\*\fun     Enable or disable the NAND clock synchronous to aclk.
*\*\param   NewState:
*\*\          - ENABLE
*\*\          - DISABLE
*\*\return  none
**/
void FEMC_NANDSYNCEnable(FunctionalState NewState)
{
    if(NewState == ENABLE)
    {
        FEMC->FEMC_NMOD |= FEMC_NMOD_SYNC;
    }
    else
    {
        FEMC->FEMC_NMOD &= ~FEMC_NMOD_SYNC;
    }
}

/**
*\*\name    FEMC_RemapEnable.
*\*\fun     Enable or disable the FEMC SRAM interface remap to SDRAM.
*\*\param   NewState:
*\*\          - ENABLE
*\*\          - DISABLE
*\*\return  none
**/
void FEMC_RemapEnable(FunctionalState NewState)
{
    if(NewState == ENABLE)
    {
        FEMC->FEMC_REMAP |= FEMC_REMAP_REMAP;
    }
    else
    {
        FEMC->FEMC_REMAP &= ~FEMC_REMAP_REMAP;
    }
}

/**
*\*\name    FEMC_ClrFlag.
*\*\fun     Clears the FEMC's  flags.
*\*\param   FEMC_FLAG:
*\*\          - FEMC_SRAM_FLAG_CLEAR
*\*\          - FEMC_NAND_FLAG_CLEAR
*\*\return  none
**/
void FEMC_ClrFlag(uint32_t FEMC_FLAG)
{
    FEMC->FEMC_CCFG |= FEMC_FLAG;
}

/**
*\*\name    FEMC_GetFlag.
*\*\fun     Checks whether the specified  flag is set or not.
*\*\param   FEMC_FLAG
*\*\          - FEMC_SRAM_FLAG
*\*\          - FEMC_NAND_FLAG
*\*\          - FEMC_ECC_FLAG
*\*\          - FEMC_SRAM_EN_FLAG
*\*\          - FEMC_NAND_EN_FLAG
*\*\          - FEMC_ECC_EN_FLAG
*\*\return  FlagStatus
*\*\          - SET   : the flag is set
*\*\          - RESET : the flag is reset
**/
FlagStatus FEMC_GetFlag(uint32_t FEMC_FLAG)
{
    FlagStatus bitstatus;

    /* Check the status of the specified I2C flag */
    if ((FEMC->FEMC_STS & FEMC_FLAG) != (uint32_t)RESET)
    {
        /* FEMC_IT is set */
        bitstatus = SET;
    }
    else
    {
        /* FEMC_IT is reset */
        bitstatus = RESET;
    }

    /* Return the FEMC_IT status */
    return  bitstatus;
}

/**
*\*\name    FEMC_ITConfig.
*\*\fun     Enables or disables the specified FEMC interrupts.
*\*\param   FEMC_IT:
*\*\          - FEMC_IT_SRAM_EN
*\*\          - FEMC_IT_NAND_EN
*\*\          - FEMC_IT_ECC_EN
*\*\param   NewState: new state of the multiplexed mode.
*\*\          - ENABLE
*\*\          - DISABLE
*\*\return  none
**/
void FEMC_ITConfig(uint32_t FEMC_IT, FunctionalState NewState)
{
    if (NewState != DISABLE)
    {
        /* Enable the selected FEMC interrupts */
        FEMC->FEMC_CFG |= FEMC_IT;
    }
    else
    {
        /* Disable the selected FEMC interrupts */
        FEMC->FEMC_CCFG |= FEMC_IT;
    }
}

/**
*\*\name    FEMC_ClrITFlag.
*\*\fun     Clears the FEMC's interrupt pending flags.
*\*\param   FEMC_FLAG:
*\*\          - FEMC_IT_SRAM_FLAG_CLEAR
*\*\          - FEMC_IT_NAND_FLAG_CLEAR
*\*\return  none
**/
void FEMC_ClrITFlag(uint32_t FEMC_FLAG)
{
    FEMC->FEMC_CCFG |= FEMC_FLAG;
}

/**
*\*\name    FEMC_GetITFlag.
*\*\fun     Checks whether the specified interrupt flag is set or not.
*\*\param   FEMC_IT_FLAG
*\*\          - FEMC_IT_SRAM_FLAG
*\*\          - FEMC_IT_NAND_FLAG
*\*\          - FEMC_IT_ECC_FLAG
*\*\return  ITStatus
*\*\          - SET   : the interrupt flag is set
*\*\          - RESET : the interrupt flag is reset
**/
ITStatus FEMC_GetITFlag(uint32_t FEMC_IT_FLAG)
{
    ITStatus bitstatus;

    /* Check the status of the specified I2C flag */
    if ((FEMC->FEMC_STS & FEMC_IT_FLAG) != (uint32_t)RESET)
    {
        /* FEMC_IT is set */
        bitstatus = SET;
    }
    else
    {
        /* FEMC_IT is reset */
        bitstatus = RESET;
    }

    /* Return the FEMC_IT status */
    return  bitstatus;
}

/**
*\*\name    FEMC_AsyncADVConfig.
*\*\fun     Enables or disables the ADC singal same as multiplexed mode in asynchronous mode.
*\*\param   NewState: new state of the multiplexed mode.
*\*\          - ENABLE
*\*\          - DISABLE
*\*\return  none
**/
void FEMC_AsyncADVConfig(FunctionalState NewState)
{
    if (NewState != DISABLE)
    {
        /* Enable the selected FEMC interrupts */
        FEMC->FEMC_CFG |= FEMC_CFG_ASYNCADV;
    }
    else
    {
        /* Disable the selected FEMC interrupts */
        FEMC->FEMC_CCFG |= FEMC_CFG_ASYNCADV;
    }
}

/**
*\*\name    FEMC_GetSRAMType.
*\*\fun     Get FEMC SRAM interface type.
*\*\return  none
**/
uint32_t FEMC_GetSRAMType(void)
{
    uint32_t status;
    /* Enable the selected FEMC interrupts */
    status = FEMC->FEMC_STS1 & 0x03;

    return status;
}

/**
*\*\name    FEMC_ECC_Init.
*\*\fun     Initialize FEMC ECC function.
*\*\param   ECCInitType   Pointer to a FEMC_ECCInitType structure
*\*\return  none
**/
void FEMC_ECC_Init(const FEMC_ECCInitType *ECCInitType)
{
    uint32_t temp_value;

    /* Check the pointer pstcInit */

    temp_value = (( ECCInitType->BLKNum   |  \
                    ECCInitType->Mode     |  \
                    ECCInitType->ReadMode |  \
                    ECCInitType->JUMP     |  \
                    ECCInitType->A8OUTMSK |  \
                    ECCInitType->ReadINT  |  \
                    ECCInitType->ABTINT   |  \
                    ECCInitType->EXTBLKEN |  \
                    ECCInitType->EXTBLKSize) & (0x00001FFF));
    FEMC->FEMC_ECCCFG = temp_value;
    FEMC->FEMC_ECCMD0 = ECCInitType->CMD0;
    FEMC->FEMC_ECCMD1 = ECCInitType->CMD1;
}

/**
*\*\name    FEMC_SetECCAddr.
*\*\fun     Set the FEMC ECC data start address.
*\*\param   address0: FEMC ECC data start address 0.
*\*\param   address0: FEMC ECC data start address 1.
*\*\return  none
**/
void FEMC_SetECCAddr(uint32_t address0, uint32_t address1)
{
    FEMC->FEMC_ECCADDR0 = address0;
    FEMC->FEMC_ECCADDR1 = address1;
}

/**
*\*\name    FEMC_GetECCFlag.
*\*\fun     Get the FEMC ECC flag status.
*\*\param   FEMC_ECC_Flag_Index
*\*\          - FEMC_ECC_FLAG_VALUE_VALID
*\*\          - FEMC_ECC_FLAG_FAIL
*\*\          - FEMC_ECC_FLAG_CAN_CORRECT
*\*\          - FEMC_ECC_FLAG_READ
*\*\param   ECC_Block_Index
*\*\          - FEMC_ECC_PAGE_BLOCK_INDEX0
*\*\          - FEMC_ECC_PAGE_BLOCK_INDEX1
*\*\          - FEMC_ECC_PAGE_BLOCK_INDEX2
*\*\          - FEMC_ECC_PAGE_BLOCK_INDEX3
*\*\          - FEMC_ECC_PAGE_BLOCK_EXTRA
*\*\return  FlagStatus
*\*\          - SET   : The state of specific flag is set
*\*\          - RESET : The state of specific flag is reset
**/
FlagStatus FEMC_GetECCFlag(uint32_t FEMC_ECC_Flag_Index, uint32_t ECC_Block_Index)
{
    FlagStatus status = RESET;

    if(FEMC->FEMC_ECCSTS & (FEMC_ECC_Flag_Index << ECC_Block_Index))
    {
        status = SET;
    }
    else
    {
        status = RESET;
    }

    return status;
}

/**
*\*\name    FEMC_GetECCITFlag.
*\*\fun     Get the FEMC ECC interrupt status.
*\*\param   ECC_Block_Index
*\*\          - FEMC_ECC_INT_FLAG_PAGE_BLOCK0
*\*\          - FEMC_ECC_INT_FLAG_PAGE_BLOCK1
*\*\          - FEMC_ECC_INT_FLAG_PAGE_BLOCK2
*\*\          - FEMC_ECC_INT_FLAG_PAGE_BLOCK3
*\*\          - FEMC_ECC_INT_FLAG_PAGE_EXTRA
*\*\          - FEMC_ECC_INT_FLAG_ABORT
*\*\return  FlagStatus
*\*\          - SET   : the flag is set
*\*\          - RESET : the flag is reset
**/
FlagStatus FEMC_GetECCITFlag(uint32_t ECC_Block_Index)
{
    FlagStatus status = RESET;

    if(FEMC->FEMC_ECCSTS & ECC_Block_Index)
    {
        status = SET;
    }
    else
    {
        status = RESET;
    }

    return status;
}

/**
*\*\name    FEMC_ECCClrFlag.
*\*\fun     Clear the FEMC ECC interrupt.
*\*\param   ECC_Block_Index
*\*\          - FEMC_ECC_INT_FLAG_PAGE_BLOCK0
*\*\          - FEMC_ECC_INT_FLAG_PAGE_BLOCK1
*\*\          - FEMC_ECC_INT_FLAG_PAGE_BLOCK2
*\*\          - FEMC_ECC_INT_FLAG_PAGE_BLOCK3
*\*\          - FEMC_ECC_INT_FLAG_PAGE_EXTRA
*\*\          - FEMC_ECC_INT_FLAG_ABORT
*\*\return  none
**/
void FEMC_ECCClrFlag(uint32_t ECC_Block_Index)
{
    FEMC->FEMC_ECCSTS = ECC_Block_Index;
}

/**
*\*\name    FEMC_GetECCStatus.
*\*\fun     Get the FEMC ECC status.
*\*\param   none
*\*\return  FlagStatus
*\*\          - SET   : the ecc status is busy
*\*\          - RESET : the ecc status is idle
**/
FlagStatus FEMC_GetECCBusyFlag(void)
{
    FlagStatus status = RESET;

    if(FEMC->FEMC_ECCSTS & FEMC_ECCSTS_BUSY)
    {
        status = SET;
    }
    else
    {
        status = RESET;
    }

    return status;
}

/**
*\*\name    FEMC_GetECCLastStatus.
*\*\fun     Get the FEMC Last ECC status.
*\*\param   none
*\*\return  ECC_Last_Stats
*\*\          - Completed_Success
*\*\          - Unaligned_Range
*\*\          - Data_Stop
*\*\          - Data_Stop_No_Read
**/
ECC_Last_Stats FEMC_GetECCLastSTS(void)
{
    ECC_Last_Stats status = COMPLETE;

    if((FEMC->FEMC_ECCSTS & FEMC_ECCSTS_LASTS) == FEMC_ECC_LAST_STATUS_COMPLETE)
    {
        status = COMPLETE;
    }
    else if((FEMC->FEMC_ECCSTS & FEMC_ECCSTS_LASTS) == FEMC_ECC_LAST_STATUS_UNALIGNADDR)
    {
        status = UNALIGNADDR;
    }
    else if((FEMC->FEMC_ECCSTS & FEMC_ECCSTS_LASTS) == FEMC_ECC_LAST_STATUS_DATASTOP)
    {
        status = DATASTOP;
    }
    else if((FEMC->FEMC_ECCSTS & FEMC_ECCSTS_LASTS) == FEMC_ECC_LAST_STATUS_DATASTOP_NOREAD)
    {
        status = DATASTOP_NOREAD;
    }

    return status;
}

/**
*\*\name    FEMC_GetECCRWSTS.
*\*\fun     Get the FEMC ECC write or read status.
*\*\param   none
*\*\return  FlagStatus
*\*\          - SET   : the ecc is read status
*\*\          - RESET : the ecc is write status
**/
FlagStatus FEMC_GetECCRWFlag(void)
{
    FlagStatus status = SET;

    if(FEMC->FEMC_ECCSTS & FEMC_ECCSTS_WRF)
    {
        status = SET;
    }
    else
    {
        status = RESET;
    }

    return status;
}

/**
*\*\name    FEMC_GetECCBlockSTS.
*\*\fun     Get the FEMC ECC page block status.
*\*\param   ECC_Block_Index
*\*\          - FEMC_ECC_PAGE_BLOCK_INDEX0
*\*\          - FEMC_ECC_PAGE_BLOCK_INDEX1
*\*\          - FEMC_ECC_PAGE_BLOCK_INDEX2
*\*\          - FEMC_ECC_PAGE_BLOCK_INDEX3
*\*\          - FEMC_ECC_PAGE_BLOCK_EXTRA
*\*\param   FEMC_Block_Flag_Index: specifies which flag status to get.
*\*\          - FEMC_ECC_BLOCK_FLAG_CAN_CORRECT:  Indicates if the detected error is correctablea: 0 = not correctable,1 = correctable.
*\*\          - FEMC_ECC_BLOCK_FLAG_FAIL:  Pass, fail flag for each ECC block:0 = pass,1 = fail.
*\*\          - FEMC_ECC_BLOCK_FLAG_READ:  Read flags for ECC blocks:0 = not read,1 = read.
*\*\          - FEMC_ECC_BLOCK_FLAG_VALUE_VALID:  Valid flag for each ECC block:0 = not valid,1 = valid.
*\*\          - FEMC_ECC_BLOCK_FLAG_INTERRUPT:  Interrupt flag:0 = not set,1 = set.
*\*\return  SET or RESET
**/
FlagStatus FEMC_GetECCBlockSTS(uint32_t ECC_Block_Index, uint32_t FEMC_Block_Flag_Index)
{
    FlagStatus status = RESET;


    if(ECC_Block_Index != FEMC_ECC_PAGE_BLOCK_EXTRA)
    {
        if(FEMC->FEMC_ECCBLK[ECC_Block_Index] & ((uint32_t)((FEMC_Block_Flag_Index) << 27)))
        {
            status = SET;
        }
        else
        {
            status = RESET;
        }
    }
    else if(ECC_Block_Index == FEMC_ECC_PAGE_BLOCK_EXTRA)
    {
        if(FEMC->FEMC_ECCEBLK & ((uint32_t)((FEMC_Block_Flag_Index) << 27)))
        {
            status = SET;
        }
        else
        {
            status = RESET;
        }
    }

    return status;
}

/**
*\*\name    FEMC_GetECCBlockSTS.
*\*\fun     Clear the FEMC ECC page block status.
*\*\param   ECC_Block_Index
*\*\          - FEMC_ECC_PAGE_BLOCK_INDEX0
*\*\          - FEMC_ECC_PAGE_BLOCK_INDEX1
*\*\          - FEMC_ECC_PAGE_BLOCK_INDEX2
*\*\          - FEMC_ECC_PAGE_BLOCK_INDEX3
*\*\          - FEMC_ECC_PAGE_BLOCK_EXTRA
*\*\param   FEMC_Block_Flag_Index: specifies which flag status to get.
*\*\          - FEMC_ECC_BLOCK_FLAG_CAN_CORRECT:  Indicates if the detected error is correctablea: 0 = not correctable,1 = correctable.
*\*\          - FEMC_ECC_BLOCK_FLAG_FAIL:  Pass, fail flag for each ECC block:0 = pass,1 = fail.
*\*\          - FEMC_ECC_BLOCK_FLAG_READ:  Read flags for ECC blocks:0 = not read,1 = read.
*\*\          - FEMC_ECC_BLOCK_FLAG_VALUE_VALID:  Valid flag for each ECC block:0 = not valid,1 = valid.
*\*\          - FEMC_ECC_BLOCK_FLAG_INTERRUPT:  Interrupt flag:0 = not set,1 = set.
*\*\return  None
**/
void FEMC_ClrECCBlockSTS(uint32_t ECC_Block_Index, uint32_t FEMC_Block_Flag_Index)
{
    uint32_t temp;

    if(ECC_Block_Index != FEMC_ECC_PAGE_BLOCK_EXTRA)
    {
        temp = FEMC->FEMC_ECCBLK[ECC_Block_Index];
        temp &= !((uint32_t)((FEMC_Block_Flag_Index) << 27));
        FEMC->FEMC_ECCBLK[ECC_Block_Index] = temp;
    }
    else if(ECC_Block_Index == FEMC_ECC_PAGE_BLOCK_EXTRA)
    {
        temp = FEMC->FEMC_ECCEBLK;
        temp &= !((uint32_t)((FEMC_Block_Flag_Index) << 27));
        FEMC->FEMC_ECCEBLK = temp;
    }
}



/**
*\*\name    FEMC_GetECCvalue.
*\*\fun     Get the FEMC ECC value or result of each page frame.
*\*\param   ECC_Block_Index
*\*\          - FEMC_ECC_PAGE_BLOCK_INDEX0
*\*\          - FEMC_ECC_PAGE_BLOCK_INDEX1
*\*\          - FEMC_ECC_PAGE_BLOCK_INDEX2
*\*\          - FEMC_ECC_PAGE_BLOCK_INDEX3
*\*\          - FEMC_ECC_PAGE_BLOCK_EXTRA
*\*\return  The ecc value of specific page frame.
**/
uint32_t FEMC_GetECCvalue(uint32_t ECC_Block_Index)
{
    uint32_t temp_value = 0;

    if(ECC_Block_Index != FEMC_ECC_PAGE_BLOCK_EXTRA)
    {
        temp_value = FEMC->FEMC_ECCBLK[ECC_Block_Index] & (FEMC_ECCBLK_VAL);
    }
    else if(ECC_Block_Index == FEMC_ECC_PAGE_BLOCK_EXTRA)
    {
        temp_value = FEMC->FEMC_ECCEBLK & (FEMC_ECCBLK_VAL);
    }

    return temp_value;
}

