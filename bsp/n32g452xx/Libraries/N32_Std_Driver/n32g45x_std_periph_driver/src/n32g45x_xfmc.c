/*****************************************************************************
 * Copyright (c) 2019, Nations Technologies Inc.
 *
 * All rights reserved.
 * ****************************************************************************
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *
 * - Redistributions of source code must retain the above copyright notice,
 * this list of conditions and the disclaimer below.
 *
 * Nations' name may not be used to endorse or promote products derived from
 * this software without specific prior written permission.
 *
 * DISCLAIMER: THIS SOFTWARE IS PROVIDED BY NATIONS "AS IS" AND ANY EXPRESS OR
 * IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF
 * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NON-INFRINGEMENT ARE
 * DISCLAIMED. IN NO EVENT SHALL NATIONS BE LIABLE FOR ANY DIRECT, INDIRECT,
 * INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
 * LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA,
 * OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF
 * LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING
 * NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE,
 * EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 * ****************************************************************************/

/**
 * @file n32g45x_xfmc.c
 * @author Nations
 * @version v1.0.1
 *
 * @copyright Copyright (c) 2019, Nations Technologies Inc. All rights reserved.
 */
#include "n32g45x_xfmc.h"
#include "n32g45x_rcc.h"

/** @addtogroup N32G45X_StdPeriph_Driver
 * @{
 */

/** @addtogroup XFMC
 * @brief XFMC driver modules
 * @{
 */

/** @addtogroup XFMC_Private_TypesDefinitions
 * @{
 */
/**
 * @}
 */

/** @addtogroup XFMC_Private_Defines
 * @{
 */

/**
 * @}
 */

/** @addtogroup XFMC_Private_Macros
 * @{
 */

/**
 * @}
 */

/** @addtogroup XFMC_Private_Variables
 * @{
 */

/**
 * @}
 */

/** @addtogroup XFMC_Private_FunctionPrototypes
 * @{
 */

/**
 * @}
 */

/** @addtogroup XFMC_Private_Functions
 * @{
 */

/**
 * @brief  Deinitializes the XFMC NOR/SRAM Banks registers to their default
 *         reset values.
 * @param Bank specifies the XFMC Bank to be used
 *   This parameter can be one of the following values:
 *     @arg XFMC_BANK1_BLOCK1   XFMC Bank1 NOR/SRAM1
 *     @arg XFMC_BANK1_BLOCK2   XFMC Bank1 NOR/SRAM2
 * @retval None
 */
void XFMC_DeInitNorSram(XFMC_Bank1_Block *Block)
{
    /* Check the parameter */
    assert_param(IS_XFMC_NOR_SRAM_BLOCK(Block));

    /* XFMC_BANK1_BLOCK1 */
    if (Block == XFMC_BANK1_BLOCK1)
    {
        Block->CRx = XFMC_NOR_SRAM_CR1_RESET;
    }
    /* XFMC_BANK1_BLOCK2 */
    else
    {
        Block->CRx = XFMC_NOR_SRAM_CR2_RESET;
    }

    Block->TRx   = XFMC_NOR_SRAM_TR_RESET;
    Block->WTRx  = XFMC_NOR_SRAM_WTR_RESET;
}

/**
 * @brief  Deinitializes the XFMC NAND Banks registers to their default reset values.
 * @param Bank specifies the XFMC Bank to be used
 *   This parameter can be one of the following values:
 *     @arg XFMC_BANK2_NAND XFMC Bank2 NAND
 *     @arg XFMC_BANK3_NAND XFMC Bank3 NAND
 * @retval None
 */
void XFMC_DeInitNand(XFMC_Bank23_Module *Bank)
{
    /* Check the parameter */
    assert_param(IS_XFMC_NAND_BANK(Bank));

    Bank->CTRLx     = XFMC_NAND_CTRL_RESET;
    Bank->STSx      = XFMC_NAND_STS_RESET;
    Bank->CMEMTMx   = XFMC_NAND_CMEMTM_RESET;
    Bank->ATTMEMTMx = XFMC_NAND_ATTMEMTM_RESET;
}

/**
 * @brief  Initializes the XFMC NOR/SRAM Banks according to the specified
 *         parameters in the XFMC_NORSRAMInitStruct.
 * @param XFMC_NORSRAMInitStruct pointer to a XFMC_NorSramInitTpye
 *         structure that contains the configuration information for
 *        the XFMC NOR/SRAM specified Banks.
 * @retval None
 */
void XFMC_InitNorSram(XFMC_NorSramInitTpye* XFMC_NORSRAMInitStruct)
{
    /* Check the parameters */
    assert_param(IS_XFMC_NOR_SRAM_BLOCK(XFMC_NORSRAMInitStruct->Block));
    assert_param(IS_XFMC_NOR_SRAM_MUX(XFMC_NORSRAMInitStruct->DataAddrMux));
    assert_param(IS_XFMC_NOR_SRAM_MEMORY(XFMC_NORSRAMInitStruct->MemType));
    assert_param(IS_XFMC_NOR_SRAM_MEMORY_WIDTH(XFMC_NORSRAMInitStruct->MemDataWidth));
    assert_param(IS_XFMC_NOR_SRAM_BURSTMODE(XFMC_NORSRAMInitStruct->BurstAccMode));
    assert_param(IS_XFMC_NOR_SRAM_ASYNWAIT(XFMC_NORSRAMInitStruct->AsynchroWait));
    assert_param(IS_XFMC_NOR_SRAM_WAIT_POLARITY(XFMC_NORSRAMInitStruct->WaitSigPolarity));
    assert_param(IS_XFMC_NOR_SRAM_WRAP_MODE(XFMC_NORSRAMInitStruct->WrapMode));
    assert_param(IS_XFMC_NOR_SRAM_WAIT_SIGNAL_ACTIVE(XFMC_NORSRAMInitStruct->WaitSigConfig));
    assert_param(IS_XFMC_NOR_SRAM_WRITE_OPERATION(XFMC_NORSRAMInitStruct->WriteEnable));
    assert_param(IS_XFMC_NOR_SRAM_WAITE_SIGNAL(XFMC_NORSRAMInitStruct->WaitSigEnable));
    assert_param(IS_XFMC_NOR_SRAM_EXTENDED_MODE(XFMC_NORSRAMInitStruct->ExtModeEnable));
    assert_param(IS_XFMC_NOR_SRAM_WRITE_BURST(XFMC_NORSRAMInitStruct->WriteBurstEnable));
    assert_param(IS_XFMC_NOR_SRAM_ADDR_SETUP_TIME(XFMC_NORSRAMInitStruct->RWTimingStruct->AddrSetTime));
    assert_param(IS_XFMC_NOR_SRAM_ADDR_HOLD_TIME(XFMC_NORSRAMInitStruct->RWTimingStruct->AddrHoldTime));
    assert_param(IS_XFMC_NOR_SRAM_DATASETUP_TIME(XFMC_NORSRAMInitStruct->RWTimingStruct->DataSetTime));
    assert_param(IS_XFMC_NOR_SRAM_BUSRECOVERY_TIME(XFMC_NORSRAMInitStruct->RWTimingStruct->BusRecoveryCycle));
    assert_param(IS_XFMC_NOR_SRAM_CLK_DIV(XFMC_NORSRAMInitStruct->RWTimingStruct->ClkDiv));
    assert_param(IS_XFMC_NOR_SRAM_DATA_LATENCY(XFMC_NORSRAMInitStruct->RWTimingStruct->DataLatency));
    assert_param(IS_XFMC_NOR_SRAM_ACCESS_MODE(XFMC_NORSRAMInitStruct->RWTimingStruct->AccMode));

    /* Bank1 NOR/SRAM control register configuration */
    XFMC_NORSRAMInitStruct->Block->CRx = XFMC_NORSRAMInitStruct->DataAddrMux
                                        | XFMC_NORSRAMInitStruct->MemType
                                        | XFMC_NORSRAMInitStruct->MemDataWidth
                                        | XFMC_NORSRAMInitStruct->BurstAccMode
                                        | XFMC_NORSRAMInitStruct->AsynchroWait
                                        | XFMC_NORSRAMInitStruct->WaitSigPolarity
                                        | XFMC_NORSRAMInitStruct->WrapMode
                                        | XFMC_NORSRAMInitStruct->WaitSigConfig
                                        | XFMC_NORSRAMInitStruct->WriteEnable
                                        | XFMC_NORSRAMInitStruct->WaitSigEnable
                                        | XFMC_NORSRAMInitStruct->ExtModeEnable
                                        | XFMC_NORSRAMInitStruct->WriteBurstEnable;

    if (XFMC_NORSRAMInitStruct->MemType == XFMC_MEM_TYPE_NOR)
    {
        XFMC_NORSRAMInitStruct->Block->CRx |= (uint32_t)XFMC_NOR_SRAM_ACC_ENABLE;
    }

    /* Bank1 NOR/SRAM timing register configuration */
    XFMC_NORSRAMInitStruct->Block->TRx =  XFMC_NORSRAMInitStruct->RWTimingStruct->AddrSetTime
                                        | XFMC_NORSRAMInitStruct->RWTimingStruct->AddrHoldTime
                                        | XFMC_NORSRAMInitStruct->RWTimingStruct->DataSetTime
                                        | XFMC_NORSRAMInitStruct->RWTimingStruct->BusRecoveryCycle
                                        | XFMC_NORSRAMInitStruct->RWTimingStruct->ClkDiv
                                        | XFMC_NORSRAMInitStruct->RWTimingStruct->DataLatency
                                        | XFMC_NORSRAMInitStruct->RWTimingStruct->AccMode;

    /* Bank1 NOR/SRAM timing register for write configuration, if extended mode is used */
    if (XFMC_NORSRAMInitStruct->ExtModeEnable == XFMC_NOR_SRAM_EXTENDED_ENABLE)
    {
        assert_param(IS_XFMC_NOR_SRAM_ADDR_SETUP_TIME(XFMC_NORSRAMInitStruct->WTimingStruct->AddrSetTime));
        assert_param(IS_XFMC_NOR_SRAM_ADDR_HOLD_TIME(XFMC_NORSRAMInitStruct->WTimingStruct->AddrHoldTime));
        assert_param(IS_XFMC_NOR_SRAM_DATASETUP_TIME(XFMC_NORSRAMInitStruct->WTimingStruct->DataSetTime));
        assert_param(IS_XFMC_NOR_SRAM_CLK_DIV(XFMC_NORSRAMInitStruct->WTimingStruct->ClkDiv));
        assert_param(IS_XFMC_NOR_SRAM_DATA_LATENCY(XFMC_NORSRAMInitStruct->WTimingStruct->DataLatency));
        assert_param(IS_XFMC_NOR_SRAM_ACCESS_MODE(XFMC_NORSRAMInitStruct->WTimingStruct->AccMode));
        XFMC_NORSRAMInitStruct->Block->WTRx = XFMC_NORSRAMInitStruct->WTimingStruct->AddrSetTime
                                            | XFMC_NORSRAMInitStruct->WTimingStruct->AddrHoldTime
                                            | (XFMC_NORSRAMInitStruct->WTimingStruct->DataSetTime << XFMC_BANK1_WTR_DATABLD_SHIFT)
                                            | XFMC_NORSRAMInitStruct->WTimingStruct->ClkDiv
                                            | XFMC_NORSRAMInitStruct->WTimingStruct->DataLatency
                                            | XFMC_NORSRAMInitStruct->WTimingStruct->AccMode;
    }
    else
    {
        XFMC_NORSRAMInitStruct->Block->WTRx = XFMC_NOR_SRAM_WTR_RESET;
    }
}

/**
 * @brief  Initializes the XFMC NAND Banks according to the specified
 *         parameters in the XFMC_NANDInitStruct.
 * @param XFMC_NANDInitStruct pointer to a XFMC_NandInitType
 *         structure that contains the configuration information for the XFMC
 *         NAND specified Banks.
 * @retval None
 */
void XFMC_InitNand(XFMC_NandInitType* XFMC_NANDInitStruct)
{
    uint32_t tmppcr = 0x00000000, tmppmem = 0x00000000, tmppatt = 0x00000000;

    /* Check the parameters */
    assert_param(IS_XFMC_NAND_BANK(XFMC_NANDInitStruct->Bank));
    assert_param(IS_XFMC_NAND_WAIT_FEATURE(XFMC_NANDInitStruct->WaitFeatureEnable));
    assert_param(IS_XFMC_NAND_BUS_WIDTH(XFMC_NANDInitStruct->MemDataWidth));
    assert_param(IS_XFMC_ECC_STATE(XFMC_NANDInitStruct->EccEnable));
    assert_param(IS_XFMC_NAND_ECC_PAGE_SIZE(XFMC_NANDInitStruct->EccPageSize));
    assert_param(IS_XFMC_NAND_CLE_DELAY(XFMC_NANDInitStruct->TCLRSetTime));
    assert_param(IS_XFMC_NAND_ALE_DELAY(XFMC_NANDInitStruct->TARSetTime));
    assert_param(IS_XFMC_NAND_SETUP_TIME(XFMC_NANDInitStruct->CommSpaceTimingStruct->SetTime));
    assert_param(IS_XFMC_NAND_WAIT_TIME(XFMC_NANDInitStruct->CommSpaceTimingStruct->WaitSetTime));
    assert_param(IS_XFMC_NAND_HOLD_TIME(XFMC_NANDInitStruct->CommSpaceTimingStruct->HoldSetTime));
    assert_param(IS_XFMC_NAND_HIZ_TIME(XFMC_NANDInitStruct->CommSpaceTimingStruct->HiZSetTime));
    assert_param(IS_XFMC_NAND_SETUP_TIME(XFMC_NANDInitStruct->AttrSpaceTimingStruct->SetTime));
    assert_param(IS_XFMC_NAND_WAIT_TIME(XFMC_NANDInitStruct->AttrSpaceTimingStruct->WaitSetTime));
    assert_param(IS_XFMC_NAND_HOLD_TIME(XFMC_NANDInitStruct->AttrSpaceTimingStruct->HoldSetTime));
    assert_param(IS_XFMC_NAND_HIZ_TIME(XFMC_NANDInitStruct->AttrSpaceTimingStruct->HiZSetTime));

    /* Set the tmppcr value according to XFMC_NANDInitStruct parameters */
    tmppcr =    XFMC_BANK23_MEM_TYPE_NAND
            |   XFMC_NANDInitStruct->WaitFeatureEnable
            |   XFMC_NANDInitStruct->MemDataWidth
            |   XFMC_NANDInitStruct->EccEnable
            |   XFMC_NANDInitStruct->EccPageSize
            |   XFMC_NANDInitStruct->TCLRSetTime
            |   XFMC_NANDInitStruct->TARSetTime;

    /* Set tmppmem value according to XFMC_CommonSpaceTimingStructure parameters */
    tmppmem =   (XFMC_NANDInitStruct->CommSpaceTimingStruct->SetTime << XFMC_CMEMTM_SET_SHIFT)
              | (XFMC_NANDInitStruct->CommSpaceTimingStruct->WaitSetTime << XFMC_CMEMTM_WAIT_SHIFT)
              | (XFMC_NANDInitStruct->CommSpaceTimingStruct->HoldSetTime << XFMC_CMEMTM_HLD_SHIFT)
              | (XFMC_NANDInitStruct->CommSpaceTimingStruct->HiZSetTime << XFMC_CMEMTM_HIZ_SHIFT);

    /* Set tmppatt value according to XFMC_AttributeSpaceTimingStructure parameters */
    tmppatt =   (XFMC_NANDInitStruct->AttrSpaceTimingStruct->SetTime <<XFMC_ATTMEMTM_SET_SHIFT)
              | (XFMC_NANDInitStruct->AttrSpaceTimingStruct->WaitSetTime << XFMC_ATTMEMTM_WAIT_SHIFT)
              | (XFMC_NANDInitStruct->AttrSpaceTimingStruct->HoldSetTime << XFMC_ATTMEMTM_HLD_SHIFT)
              | (XFMC_NANDInitStruct->AttrSpaceTimingStruct->HiZSetTime << XFMC_ATTMEMTM_HIZ_SHIFT);

    XFMC_NANDInitStruct->Bank->CTRLx        = tmppcr;
    XFMC_NANDInitStruct->Bank->CMEMTMx      = tmppmem;
    XFMC_NANDInitStruct->Bank->ATTMEMTMx    = tmppatt;
}

/**
 * @brief  Fills each XFMC_NORSRAMInitStruct member with its default value.
 * @param XFMC_NORSRAMInitStruct pointer to a XFMC_NorSramInitTpye
 *         structure which will be initialized.
 * @retval None
 */
void XFMC_InitNorSramStruct(XFMC_NorSramInitTpye* XFMC_NORSRAMInitStruct)
{
    /* Reset NOR/SRAM Init structure parameters values */
    XFMC_NORSRAMInitStruct->Block                            = XFMC_BANK1_BLOCK1;
    XFMC_NORSRAMInitStruct->DataAddrMux                      = XFMC_NOR_SRAM_MUX_ENABLE;
    XFMC_NORSRAMInitStruct->MemType                          = XFMC_MEM_TYPE_SRAM;
    XFMC_NORSRAMInitStruct->MemDataWidth                     = XFMC_NOR_SRAM_DATA_WIDTH_8B;
    XFMC_NORSRAMInitStruct->BurstAccMode                     = XFMC_NOR_SRAM_BURST_MODE_DISABLE;
    XFMC_NORSRAMInitStruct->AsynchroWait                     = XFMC_NOR_SRAM_ASYNC_NWAIT_DISABLE;
    XFMC_NORSRAMInitStruct->WaitSigPolarity                  = XFMC_NOR_SRAM_WAIT_SIGNAL_LOW;
    XFMC_NORSRAMInitStruct->WrapMode                         = XFMC_NOR_SRAM_WRAP_DISABLE;
    XFMC_NORSRAMInitStruct->WaitSigConfig                    = XFMC_NOR_SRAM_NWAIT_BEFORE_STATE;
    XFMC_NORSRAMInitStruct->WriteEnable                      = XFMC_NOR_SRAM_WRITE_ENABLE;
    XFMC_NORSRAMInitStruct->WaitSigEnable                    = XFMC_NOR_SRAM_NWAIT_ENABLE;
    XFMC_NORSRAMInitStruct->ExtModeEnable                    = XFMC_NOR_SRAM_EXTENDED_DISABLE;
    XFMC_NORSRAMInitStruct->WriteBurstEnable                 = XFMC_NOR_SRAM_BURST_WRITE_DISABLE;
    XFMC_NORSRAMInitStruct->RWTimingStruct->AddrSetTime      = XFMC_NOR_SRAM_ADDR_SETUP_TIME_16HCLK;
    XFMC_NORSRAMInitStruct->RWTimingStruct->AddrHoldTime     = XFMC_NOR_SRAM_ADDR_HOLD_TIME_16HCLK;
    XFMC_NORSRAMInitStruct->RWTimingStruct->DataSetTime      = XFMC_NOR_SRAM_DATA_SETUP_TIME_MAX;
    XFMC_NORSRAMInitStruct->RWTimingStruct->BusRecoveryCycle = XFMC_NOR_SRAM_BUSRECOVERY_TIME_16HCLK;
    XFMC_NORSRAMInitStruct->RWTimingStruct->ClkDiv           = XFMC_NOR_SRAM_CLK_DIV_16;
    XFMC_NORSRAMInitStruct->RWTimingStruct->DataLatency      = XFMC_NOR_SRAM_DATA_LATENCY_17CLK;
    XFMC_NORSRAMInitStruct->RWTimingStruct->AccMode          = XFMC_NOR_SRAM_ACC_MODE_A;
    XFMC_NORSRAMInitStruct->WTimingStruct->AddrSetTime       = XFMC_NOR_SRAM_ADDR_SETUP_TIME_16HCLK;
    XFMC_NORSRAMInitStruct->WTimingStruct->AddrHoldTime      = XFMC_NOR_SRAM_ADDR_HOLD_TIME_16HCLK;
    XFMC_NORSRAMInitStruct->WTimingStruct->DataSetTime       = XFMC_NOR_SRAM_DATA_SETUP_TIME_MAX;
    XFMC_NORSRAMInitStruct->WTimingStruct->BusRecoveryCycle  = XFMC_NOR_SRAM_BUSRECOVERY_TIME_16HCLK;
    XFMC_NORSRAMInitStruct->WTimingStruct->ClkDiv            = XFMC_NOR_SRAM_CLK_DIV_16;
    XFMC_NORSRAMInitStruct->WTimingStruct->DataLatency       = XFMC_NOR_SRAM_DATA_LATENCY_17CLK;
    XFMC_NORSRAMInitStruct->WTimingStruct->AccMode           = XFMC_NOR_SRAM_ACC_MODE_A;
}

/**
 * @brief  Fills each XFMC_NANDInitStruct member with its default value.
 * @param XFMC_NANDInitStruct pointer to a XFMC_NandInitType
 *         structure which will be initialized.
 * @retval None
 */
void XFMC_InitNandStruct(XFMC_NandInitType* XFMC_NANDInitStruct)
{
    /* Reset NAND Init structure parameters values */
    XFMC_NANDInitStruct->Bank                               = XFMC_BANK2;
    XFMC_NANDInitStruct->WaitFeatureEnable                  = XFMC_NAND_NWAIT_DISABLE;
    XFMC_NANDInitStruct->MemDataWidth                       = XFMC_NAND_BUS_WIDTH_8B;
    XFMC_NANDInitStruct->EccEnable                          = XFMC_NAND_ECC_DISABLE;
    XFMC_NANDInitStruct->EccPageSize                        = XFMC_NAND_ECC_PAGE_256BYTES;
    XFMC_NANDInitStruct->TCLRSetTime                        = XFMC_NAND_CLE_DELAY_1HCLK;
    XFMC_NANDInitStruct->TARSetTime                         = XFMC_NAND_ALE_DELAY_1HCLK;
    XFMC_NANDInitStruct->CommSpaceTimingStruct->SetTime     = XFMC_NAND_SETUP_TIME_DEFAULT;
    XFMC_NANDInitStruct->CommSpaceTimingStruct->WaitSetTime = XFMC_NAND_WAIT_TIME_DEFAULT;
    XFMC_NANDInitStruct->CommSpaceTimingStruct->HoldSetTime = XFMC_NAND_HOLD_TIME_DEFAULT;
    XFMC_NANDInitStruct->CommSpaceTimingStruct->HiZSetTime  = XFMC_NAND_HIZ_TIME_DEFAULT;
    XFMC_NANDInitStruct->AttrSpaceTimingStruct->SetTime     = XFMC_NAND_SETUP_TIME_DEFAULT;
    XFMC_NANDInitStruct->AttrSpaceTimingStruct->WaitSetTime = XFMC_NAND_WAIT_TIME_DEFAULT;
    XFMC_NANDInitStruct->AttrSpaceTimingStruct->HoldSetTime = XFMC_NAND_HOLD_TIME_DEFAULT;
    XFMC_NANDInitStruct->AttrSpaceTimingStruct->HiZSetTime  = XFMC_NAND_HIZ_TIME_DEFAULT;
}

/**
 * @brief  Enables or disables the specified NOR/SRAM Memory Bank.
 * @param Bank specifies the XFMC Bank to be used
 *   This parameter can be one of the following values:
 *     @arg XFMC_BANK1_BLOCK1 XFMC Bank1 NOR/SRAM block1
 *     @arg XFMC_BANK1_BLOCK2 XFMC Bank1 NOR/SRAM block2
 * @param Cmd new state of the Bank. This parameter can be: ENABLE or DISABLE.
 * @retval None
 */
void XFMC_EnableNorSram(XFMC_Bank1_Block *Block, FunctionalState Cmd)
{
    assert_param(IS_XFMC_NOR_SRAM_BLOCK(Block));
    assert_param(IS_FUNCTIONAL_STATE(Cmd));

    if (Cmd != DISABLE)
    {
        /* Enable the selected NOR/SRAM Bank by setting the PBKEN bit in the BCRx register */
        Block->CRx |= XFMC_NOR_SRAM_ENABLE;
    }
    else
    {
        /* Disable the selected NOR/SRAM Bank by clearing the PBKEN bit in the BCRx register */
        Block->CRx &= ~XFMC_NOR_SRAM_ENABLE;
    }
}

/**
 * @brief  Enables or disables the specified NAND Memory Bank.
 * @param Bank specifies the XFMC Bank to be used
 *   This parameter can be one of the following values:
 *     @arg XFMC_BANK2  XFMC Bank2 NAND
 *     @arg XFMC_BANK3  XFMC Bank3 NAND
 * @param Cmd new state of the Bank. This parameter can be: ENABLE or DISABLE.
 * @retval None
 */
void XFMC_EnableNand(XFMC_Bank23_Module *Bank, FunctionalState Cmd)
{
    assert_param(IS_XFMC_NAND_BANK(Bank));
    assert_param(IS_FUNCTIONAL_STATE(Cmd));

    if (Cmd != DISABLE)
    {
        /* Enable the selected NAND Bank by setting the PBKEN bit in the PCRx register */
        Bank->CTRLx |= XFMC_NAND_BANK_ENABLE;
    }
    else
    {
        /* Disable the selected NAND Bank by clearing the PBKEN bit in the PCRx register */
        Bank->CTRLx &= ~XFMC_NAND_BANK_ENABLE;
    }
}

/**
 * @brief  Enables or disables the XFMC NAND ECC feature.
 * @param Bank specifies the XFMC Bank to be used
 *   This parameter can be one of the following values:
 *     @arg XFMC_BANK2  XFMC Bank2 NAND
 *     @arg XFMC_BANK3  XFMC Bank3 NAND
 * @param Cmd new state of the XFMC NAND ECC feature.
 *   This parameter can be: ENABLE or DISABLE.
 * @retval None
 */
void XFMC_EnableNandEcc(XFMC_Bank23_Module *Bank, FunctionalState Cmd)
{
    assert_param(IS_XFMC_NAND_BANK(Bank));
    assert_param(IS_FUNCTIONAL_STATE(Cmd));

    if (Cmd != DISABLE)
    {
        /* Enable the selected NAND Bank ECC function by setting the ECCEN bit in the PCRx register */
        Bank->CTRLx |= XFMC_NAND_ECC_ENABLE;
    }
    else
    {
        /* Disable the selected NAND Bank ECC function by clearing the ECCEN bit in the PCRx register */
        Bank->CTRLx &= ~XFMC_NAND_ECC_ENABLE;
    }
}

/**
 * @brief  Clear ECC result and start a new ECC process.
 * @param Bank specifies the XFMC Bank to be used
 *   This parameter can be one of the following values:
 *     @arg XFMC_BANK2  XFMC Bank2 NAND
 *     @arg XFMC_BANK3  XFMC Bank3 NAND
 * @retval None
 */
void XFMC_RestartNandEcc(XFMC_Bank23_Module *Bank)
{
    Bank->CTRLx &= ~XFMC_NAND_ECC_ENABLE;
    Bank->CTRLx |= XFMC_NAND_ECC_ENABLE;
}

/**
 * @brief  Returns the error correction code register value.
 * @param Bank specifies the XFMC Bank to be used
 *   This parameter can be one of the following values:
 *     @arg XFMC_BANK2  XFMC Bank2 NAND
 *     @arg XFMC_BANK3  XFMC Bank3 NAND
 * @retval The Error Correction Code (ECC) value.
 */
uint32_t XFMC_GetEcc(XFMC_Bank23_Module *Bank)
{
    uint32_t tEccPageSize,tECC = 0;

    assert_param(IS_XFMC_NAND_BANK(Bank));

    tEccPageSize = Bank->CTRLx & XFMC_CTRL_ECCPGS_MASK;

    switch(tEccPageSize)
    {
        case XFMC_NAND_ECC_PAGE_256BYTES:
                tECC = Bank->ECCx & XFMC_ECC_PAGE_256BYTE_MASK;
                break;
        case XFMC_NAND_ECC_PAGE_512BYTES:
                tECC = Bank->ECCx & XFMC_ECC_PAGE_512BYTE_MASK;
                break;
        case XFMC_NAND_ECC_PAGE_1024BYTES:
                tECC = Bank->ECCx & XFMC_ECC_PBAE_1024BYTE_MASK;
                break;
        case XFMC_NAND_ECC_PAGE_2048BYTES:
                tECC = Bank->ECCx & XFMC_ECC_PBAE_2048BYTE_MASK;
                break;
        case XFMC_NAND_ECC_PAGE_4096BYTES:
                tECC = Bank->ECCx & XFMC_ECC_PBAE_4096BYTE_MASK;
                break;
        case XFMC_NAND_ECC_PAGE_8192BYTES:
                tECC = Bank->ECCx & XFMC_ECC_PBAE_8192BYTE_MASK;
                break;
        default:
                break;
    }

    /* Return the error correction code value */
    return (tECC);
}

/**
 * @brief  Checks whether the specified XFMC flag is set or not.
 * @param Bank specifies the XFMC Bank to be used
 *   This parameter can be one of the following values:
 *     @arg XFMC_BANK2  XFMC Bank2 NAND
 *     @arg XFMC_BANK3  XFMC Bank3 NAND
 * @param XFMC_FLAG specifies the flag to check.
 *   This parameter can be one of the following values:
 *     @arg XFMC_FLAG_FIFO_EMPTY Fifo empty Flag.
 * @retval The new state of XFMC_FLAG (SET or RESET).
 */
FlagStatus XFMC_GetFlag(XFMC_Bank23_Module *Bank, uint32_t XFMC_FLAG)
{
    FlagStatus bitstatus = RESET;

    /* Check the parameters */
    assert_param(IS_XFMC_NAND_BANK(Bank));
    assert_param(IS_XFMC_NAND_FLAG(XFMC_FLAG));

    /* Get the flag status */
    if ((Bank->STSx & XFMC_FLAG) != (uint16_t)RESET)
    {
        bitstatus = SET;
    }
    else
    {
        bitstatus = RESET;
    }
    /* Return the flag status */
    return bitstatus;
}

/**
 * @brief  Clears the XFMC's pending flags.
 * @param Bank specifies the XFMC Bank to be used
 *   This parameter can be one of the following values:
 *     @arg XFMC_BANK2  XFMC Bank2 NAND
 *     @arg XFMC_BANK3  XFMC Bank3 NAND
 * @param XFMC_FLAG specifies the flag to clear.
 *   This parameter can be one of the following values:
 *     @arg XFMC_FLAG_FIFO_EMPTY Fifo empty Flag.
 * @retval None
 */
void XFMC_ClrFlag(XFMC_Bank23_Module *Bank, uint32_t XFMC_FLAG)
{
    /* Check the parameters */
    assert_param(IS_XFMC_NAND_BANK(Bank));
    assert_param(IS_XFMC_NAND_FLAG(XFMC_FLAG));

    Bank->STSx &= ~XFMC_FLAG;
}

/**
 * @}
 */
/**
 * @}
 */
/**
 * @}
 */
