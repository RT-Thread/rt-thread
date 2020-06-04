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
 * @author Nations Solution Team
 * @version v1.0.0
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

/* --------------------- XFMC registers bit mask ---------------------------- */

/* XFMC BCRx Mask */
#define BCR_MBKEN_Set   ((uint32_t)0x00000001)
#define BCR_MBKEN_Reset ((uint32_t)0x000FFFFE)
#define BCR_FACCEN_Set  ((uint32_t)0x00000040)

/* XFMC PCRx Mask */
#define PCR_PBKEN_Set       ((uint32_t)0x00000004)
#define PCR_PBKEN_Reset     ((uint32_t)0x000FFFFB)
#define PCR_ECCEN_Set       ((uint32_t)0x00000040)
#define PCR_ECCEN_Reset     ((uint32_t)0x000FFFBF)
#define PCR_MemoryType_NAND ((uint32_t)0x00000008)
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
 *     @arg XFMC_BANK1_NORSRAM1 XFMC Bank1 NOR/SRAM1
 *     @arg XFMC_BANK1_NORSRAM2 XFMC Bank1 NOR/SRAM2
 */
void XFMC_DeInitNorSram(uint32_t Bank)
{
    /* Check the parameter */
    assert_param(IS_XFMC_NORSRAM_BANK(Bank));

    /* XFMC_BANK1_NORSRAM1 */
    if (Bank == XFMC_BANK1_NORSRAM1)
    {
        XFMC_BANK1->BK1CSTCTRL[Bank] = 0x000030DB;
    }
    /* XFMC_BANK1_NORSRAM2,  XFMC_BANK1_NORSRAM3 or XFMC_BANK1_NORSRAM4 */
    else
    {
        XFMC_BANK1->BK1CSTCTRL[Bank] = 0x000030D2;
    }
    XFMC_BANK1->BK1CSTCTRL[Bank + 1] = 0x0FFFFFFF;
    XFMC_BANK1E->BK1WRT[Bank]        = 0x0FFFFFFF;
}

/**
 * @brief  Deinitializes the XFMC NAND Banks registers to their default reset values.
 * @param Bank specifies the XFMC Bank to be used
 *   This parameter can be one of the following values:
 *     @arg XFMC_BANK2_NAND XFMC Bank2 NAND
 *     @arg XFMC_BANK3_NAND XFMC Bank3 NAND
 */
void XFMC_DeInitNand(uint32_t Bank)
{
    /* Check the parameter */
    assert_param(IS_XFMC_NAND_BANK(Bank));

    if (Bank == XFMC_BANK2_NAND)
    {
        /* Set the XFMC_BANK2 registers to their reset values */
        XFMC_BANK2->BK2CTRL = 0x00000018;
        XFMC_BANK2->STS2    = 0x00000040;
        XFMC_BANK2->CMEM2   = 0xFCFCFCFC;
        XFMC_BANK2->ATTR2   = 0xFCFCFCFC;
    }
    /* XFMC_BANK3_NAND */
    else
    {
        /* Set the XFMC_BANK3 registers to their reset values */
        XFMC_BANK3->BK3CTRL = 0x00000018;
        XFMC_BANK3->STS3    = 0x00000040;
        XFMC_BANK3->CMEM3   = 0xFCFCFCFC;
        XFMC_BANK3->ATTR3   = 0xFCFCFCFC;
    }
}

/**
 * @brief  Initializes the XFMC NOR/SRAM Banks according to the specified
 *         parameters in the XFMC_NORSRAMInitStruct.
 * @param XFMC_NORSRAMInitStruct pointer to a XFMC_NorSramInitTpye
 *         structure that contains the configuration information for
 *        the XFMC NOR/SRAM specified Banks.
 */
void XFMC_InitNorSram(XFMC_NorSramInitTpye* XFMC_NORSRAMInitStruct)
{
    /* Check the parameters */
    assert_param(IS_XFMC_NORSRAM_BANK(XFMC_NORSRAMInitStruct->Bank));
    assert_param(IS_XFMC_MUX(XFMC_NORSRAMInitStruct->DataAddrMux));
    assert_param(IS_XFMC_MEMORY(XFMC_NORSRAMInitStruct->MemType));
    assert_param(IS_XFMC_MEMORY_WIDTH(XFMC_NORSRAMInitStruct->MemDataWidth));
    assert_param(IS_XFMC_BURSTMODE(XFMC_NORSRAMInitStruct->BurstAccMode));
    assert_param(IS_XFMC_ASYNWAIT(XFMC_NORSRAMInitStruct->AsynchroWait));
    assert_param(IS_XFMC_WAIT_POLARITY(XFMC_NORSRAMInitStruct->WaitSigPolarity));
    assert_param(IS_XFMC_WRAP_MODE(XFMC_NORSRAMInitStruct->WrapMode));
    assert_param(IS_XFMC_WAIT_SIGNAL_ACTIVE(XFMC_NORSRAMInitStruct->WaitSigConfig));
    assert_param(IS_XFMC_WRITE_OPERATION(XFMC_NORSRAMInitStruct->WriteEnable));
    assert_param(IS_XFMC_WAITE_SIGNAL(XFMC_NORSRAMInitStruct->WaitSigEnable));
    assert_param(IS_XFMC_EXTENDED_MODE(XFMC_NORSRAMInitStruct->ExtModeEnable));
    assert_param(IS_XFMC_WRITE_BURST(XFMC_NORSRAMInitStruct->WriteBurstEnable));
    assert_param(IS_XFMC_ADDRESS_SETUP_TIME(XFMC_NORSRAMInitStruct->RWTimingStruct->AddrSetTime));
    assert_param(IS_XFMC_ADDRESS_HOLD_TIME(XFMC_NORSRAMInitStruct->RWTimingStruct->AddrHoldTime));
    assert_param(IS_XFMC_DATASETUP_TIME(XFMC_NORSRAMInitStruct->RWTimingStruct->DataSetTime));
    assert_param(IS_XFMC_TURNAROUND_TIME(XFMC_NORSRAMInitStruct->RWTimingStruct->BusRecoveryCycle));
    assert_param(IS_XFMC_CLK_DIV(XFMC_NORSRAMInitStruct->RWTimingStruct->ClkDiv));
    assert_param(IS_XFMC_DATA_LATENCY(XFMC_NORSRAMInitStruct->RWTimingStruct->DataLatency));
    assert_param(IS_XFMC_ACCESS_MODE(XFMC_NORSRAMInitStruct->RWTimingStruct->AccMode));

    /* Bank1 NOR/SRAM control register configuration */
    XFMC_BANK1->BK1CSTCTRL[XFMC_NORSRAMInitStruct->Bank] =
        (uint32_t)XFMC_NORSRAMInitStruct->DataAddrMux | XFMC_NORSRAMInitStruct->MemType
        | XFMC_NORSRAMInitStruct->MemDataWidth | XFMC_NORSRAMInitStruct->BurstAccMode
        | XFMC_NORSRAMInitStruct->AsynchroWait | XFMC_NORSRAMInitStruct->WaitSigPolarity
        | XFMC_NORSRAMInitStruct->WrapMode | XFMC_NORSRAMInitStruct->WaitSigConfig | XFMC_NORSRAMInitStruct->WriteEnable
        | XFMC_NORSRAMInitStruct->WaitSigEnable | XFMC_NORSRAMInitStruct->ExtModeEnable
        | XFMC_NORSRAMInitStruct->WriteBurstEnable;

    if (XFMC_NORSRAMInitStruct->MemType == XFMC_MEM_TYPE_NOR)
    {
        XFMC_BANK1->BK1CSTCTRL[XFMC_NORSRAMInitStruct->Bank] |= (uint32_t)BCR_FACCEN_Set;
    }

    /* Bank1 NOR/SRAM timing register configuration */
    XFMC_BANK1->BK1CSTCTRL[XFMC_NORSRAMInitStruct->Bank + 1] =
        (uint32_t)XFMC_NORSRAMInitStruct->RWTimingStruct->AddrSetTime
        | (XFMC_NORSRAMInitStruct->RWTimingStruct->AddrHoldTime << 4)
        | (XFMC_NORSRAMInitStruct->RWTimingStruct->DataSetTime << 8)
        | (XFMC_NORSRAMInitStruct->RWTimingStruct->BusRecoveryCycle << 16)
        | (XFMC_NORSRAMInitStruct->RWTimingStruct->ClkDiv << 20)
        | (XFMC_NORSRAMInitStruct->RWTimingStruct->DataLatency << 24) | XFMC_NORSRAMInitStruct->RWTimingStruct->AccMode;

    /* Bank1 NOR/SRAM timing register for write configuration, if extended mode is used */
    if (XFMC_NORSRAMInitStruct->ExtModeEnable == XFMC_EXTENDED_ENABLE)
    {
        assert_param(IS_XFMC_ADDRESS_SETUP_TIME(XFMC_NORSRAMInitStruct->WTimingStruct->AddrSetTime));
        assert_param(IS_XFMC_ADDRESS_HOLD_TIME(XFMC_NORSRAMInitStruct->WTimingStruct->AddrHoldTime));
        assert_param(IS_XFMC_DATASETUP_TIME(XFMC_NORSRAMInitStruct->WTimingStruct->DataSetTime));
        assert_param(IS_XFMC_CLK_DIV(XFMC_NORSRAMInitStruct->WTimingStruct->ClkDiv));
        assert_param(IS_XFMC_DATA_LATENCY(XFMC_NORSRAMInitStruct->WTimingStruct->DataLatency));
        assert_param(IS_XFMC_ACCESS_MODE(XFMC_NORSRAMInitStruct->WTimingStruct->AccMode));
        XFMC_BANK1E->BK1WRT[XFMC_NORSRAMInitStruct->Bank] = (uint32_t)XFMC_NORSRAMInitStruct->WTimingStruct->AddrSetTime
                                                            | (XFMC_NORSRAMInitStruct->WTimingStruct->AddrHoldTime << 4)
                                                            | (XFMC_NORSRAMInitStruct->WTimingStruct->DataSetTime << 8)
                                                            | (XFMC_NORSRAMInitStruct->WTimingStruct->ClkDiv << 20)
                                                            | (XFMC_NORSRAMInitStruct->WTimingStruct->DataLatency << 24)
                                                            | XFMC_NORSRAMInitStruct->WTimingStruct->AccMode;
    }
    else
    {
        XFMC_BANK1E->BK1WRT[XFMC_NORSRAMInitStruct->Bank] = 0x0FFFFFFF;
    }
}

/**
 * @brief  Initializes the XFMC NAND Banks according to the specified
 *         parameters in the XFMC_NANDInitStruct.
 * @param XFMC_NANDInitStruct pointer to a XFMC_NandInitType
 *         structure that contains the configuration information for the XFMC
 *         NAND specified Banks.
 */
void XFMC_InitNand(XFMC_NandInitType* XFMC_NANDInitStruct)
{
    uint32_t tmppcr = 0x00000000, tmppmem = 0x00000000, tmppatt = 0x00000000;

    /* Check the parameters */
    assert_param(IS_XFMC_NAND_BANK(XFMC_NANDInitStruct->Bank));
    assert_param(IS_XFMC_WAIT_FEATURE(XFMC_NANDInitStruct->WaitFeatureEnable));
    assert_param(IS_XFMC_MEMORY_WIDTH(XFMC_NANDInitStruct->MemDataWidth));
    assert_param(IS_XFMC_ECC_STATE(XFMC_NANDInitStruct->EccEnable));
    assert_param(IS_XFMC_ECCPAGE_SIZE(XFMC_NANDInitStruct->EccPageSize));
    assert_param(IS_XFMC_TCLR_TIME(XFMC_NANDInitStruct->TCLRSetTime));
    assert_param(IS_XFMC_TAR_TIME(XFMC_NANDInitStruct->TARSetTime));
    assert_param(IS_XFMC_SETUP_TIME(XFMC_NANDInitStruct->CommSpaceTimingStruct->SetTime));
    assert_param(IS_XFMC_WAIT_TIME(XFMC_NANDInitStruct->CommSpaceTimingStruct->WaitSetTime));
    assert_param(IS_XFMC_HOLD_TIME(XFMC_NANDInitStruct->CommSpaceTimingStruct->HoldSetTime));
    assert_param(IS_XFMC_HIZ_TIME(XFMC_NANDInitStruct->CommSpaceTimingStruct->HiZSetTime));
    assert_param(IS_XFMC_SETUP_TIME(XFMC_NANDInitStruct->AttrSpaceTimingStruct->SetTime));
    assert_param(IS_XFMC_WAIT_TIME(XFMC_NANDInitStruct->AttrSpaceTimingStruct->WaitSetTime));
    assert_param(IS_XFMC_HOLD_TIME(XFMC_NANDInitStruct->AttrSpaceTimingStruct->HoldSetTime));
    assert_param(IS_XFMC_HIZ_TIME(XFMC_NANDInitStruct->AttrSpaceTimingStruct->HiZSetTime));

    /* Set the tmppcr value according to XFMC_NANDInitStruct parameters */
    tmppcr = (uint32_t)XFMC_NANDInitStruct->WaitFeatureEnable | PCR_MemoryType_NAND | XFMC_NANDInitStruct->MemDataWidth
             | XFMC_NANDInitStruct->EccEnable | XFMC_NANDInitStruct->EccPageSize
             | (XFMC_NANDInitStruct->TCLRSetTime << 9) | (XFMC_NANDInitStruct->TARSetTime << 13);

    /* Set tmppmem value according to XFMC_CommonSpaceTimingStructure parameters */
    tmppmem = (uint32_t)XFMC_NANDInitStruct->CommSpaceTimingStruct->SetTime
              | (XFMC_NANDInitStruct->CommSpaceTimingStruct->WaitSetTime << 8)
              | (XFMC_NANDInitStruct->CommSpaceTimingStruct->HoldSetTime << 16)
              | (XFMC_NANDInitStruct->CommSpaceTimingStruct->HiZSetTime << 24);

    /* Set tmppatt value according to XFMC_AttributeSpaceTimingStructure parameters */
    tmppatt = (uint32_t)XFMC_NANDInitStruct->AttrSpaceTimingStruct->SetTime
              | (XFMC_NANDInitStruct->AttrSpaceTimingStruct->WaitSetTime << 8)
              | (XFMC_NANDInitStruct->AttrSpaceTimingStruct->HoldSetTime << 16)
              | (XFMC_NANDInitStruct->AttrSpaceTimingStruct->HiZSetTime << 24);

    if (XFMC_NANDInitStruct->Bank == XFMC_BANK2_NAND)
    {
        /* XFMC_BANK2_NAND registers configuration */
        XFMC_BANK2->BK2CTRL = tmppcr;
        XFMC_BANK2->CMEM2   = tmppmem;
        XFMC_BANK2->ATTR2   = tmppatt;
    }
    else
    {
        /* XFMC_BANK3_NAND registers configuration */
        XFMC_BANK3->BK3CTRL = tmppcr;
        XFMC_BANK3->CMEM3   = tmppmem;
        XFMC_BANK3->ATTR3   = tmppatt;
    }
}

/**
 * @brief  Fills each XFMC_NORSRAMInitStruct member with its default value.
 * @param XFMC_NORSRAMInitStruct pointer to a XFMC_NorSramInitTpye
 *         structure which will be initialized.
 */
void XFMC_InitNorSramStruct(XFMC_NorSramInitTpye* XFMC_NORSRAMInitStruct)
{
    /* Reset NOR/SRAM Init structure parameters values */
    XFMC_NORSRAMInitStruct->Bank                             = XFMC_BANK1_NORSRAM1;
    XFMC_NORSRAMInitStruct->DataAddrMux                      = XFMC_DATA_ADDR_MUX_ENABLE;
    XFMC_NORSRAMInitStruct->MemType                          = XFMC_MEM_TYPE_SRAM;
    XFMC_NORSRAMInitStruct->MemDataWidth                     = XFMC_MEM_DATA_WIDTH_8B;
    XFMC_NORSRAMInitStruct->BurstAccMode                     = XFMC_BURST_ACC_MODE_DISABLE;
    XFMC_NORSRAMInitStruct->AsynchroWait                     = XFMC_ASYNCHRO_WAIT_DISABLE;
    XFMC_NORSRAMInitStruct->WaitSigPolarity                  = XFMC_WAIT_SIGNAL_POLARITY_LOW;
    XFMC_NORSRAMInitStruct->WrapMode                         = XFMC_WRAP_MODE_DISABLE;
    XFMC_NORSRAMInitStruct->WaitSigConfig                    = XFMC_WAIT_SIG_ACTIVE_BEFORE_WAIT_STATE;
    XFMC_NORSRAMInitStruct->WriteEnable                      = XFMC_WRITE_ENABLE;
    XFMC_NORSRAMInitStruct->WaitSigEnable                    = XFMC_WAIT_SIGNAL_ENABLE;
    XFMC_NORSRAMInitStruct->ExtModeEnable                    = XFMC_EXTENDED_DISABLE;
    XFMC_NORSRAMInitStruct->WriteBurstEnable                 = XFMC_WRITE_BURST_DISABLE;
    XFMC_NORSRAMInitStruct->RWTimingStruct->AddrSetTime      = 0xF;
    XFMC_NORSRAMInitStruct->RWTimingStruct->AddrHoldTime     = 0xF;
    XFMC_NORSRAMInitStruct->RWTimingStruct->DataSetTime      = 0xFF;
    XFMC_NORSRAMInitStruct->RWTimingStruct->BusRecoveryCycle = 0xF;
    XFMC_NORSRAMInitStruct->RWTimingStruct->ClkDiv           = 0xF;
    XFMC_NORSRAMInitStruct->RWTimingStruct->DataLatency      = 0xF;
    XFMC_NORSRAMInitStruct->RWTimingStruct->AccMode          = XFMC_ACC_MODE_A;
    XFMC_NORSRAMInitStruct->WTimingStruct->AddrSetTime       = 0xF;
    XFMC_NORSRAMInitStruct->WTimingStruct->AddrHoldTime      = 0xF;
    XFMC_NORSRAMInitStruct->WTimingStruct->DataSetTime       = 0xFF;
    XFMC_NORSRAMInitStruct->WTimingStruct->BusRecoveryCycle  = 0xF;
    XFMC_NORSRAMInitStruct->WTimingStruct->ClkDiv            = 0xF;
    XFMC_NORSRAMInitStruct->WTimingStruct->DataLatency       = 0xF;
    XFMC_NORSRAMInitStruct->WTimingStruct->AccMode           = XFMC_ACC_MODE_A;
}

/**
 * @brief  Fills each XFMC_NANDInitStruct member with its default value.
 * @param XFMC_NANDInitStruct pointer to a XFMC_NandInitType
 *         structure which will be initialized.
 */
void XFMC_InitNandStruct(XFMC_NandInitType* XFMC_NANDInitStruct)
{
    /* Reset NAND Init structure parameters values */
    XFMC_NANDInitStruct->Bank                               = XFMC_BANK2_NAND;
    XFMC_NANDInitStruct->WaitFeatureEnable                  = XFMC_WAIT_FEATURE_DISABLE;
    XFMC_NANDInitStruct->MemDataWidth                       = XFMC_MEM_DATA_WIDTH_8B;
    XFMC_NANDInitStruct->EccEnable                          = XFMC_ECC_DISABLE;
    XFMC_NANDInitStruct->EccPageSize                        = XFMC_ECC_PAGE_SIZE_256BYTES;
    XFMC_NANDInitStruct->TCLRSetTime                        = 0x0;
    XFMC_NANDInitStruct->TARSetTime                         = 0x0;
    XFMC_NANDInitStruct->CommSpaceTimingStruct->SetTime     = 0xFC;
    XFMC_NANDInitStruct->CommSpaceTimingStruct->WaitSetTime = 0xFC;
    XFMC_NANDInitStruct->CommSpaceTimingStruct->HoldSetTime = 0xFC;
    XFMC_NANDInitStruct->CommSpaceTimingStruct->HiZSetTime  = 0xFC;
    XFMC_NANDInitStruct->AttrSpaceTimingStruct->SetTime     = 0xFC;
    XFMC_NANDInitStruct->AttrSpaceTimingStruct->WaitSetTime = 0xFC;
    XFMC_NANDInitStruct->AttrSpaceTimingStruct->HoldSetTime = 0xFC;
    XFMC_NANDInitStruct->AttrSpaceTimingStruct->HiZSetTime  = 0xFC;
}

/**
 * @brief  Enables or disables the specified NOR/SRAM Memory Bank.
 * @param Bank specifies the XFMC Bank to be used
 *   This parameter can be one of the following values:
 *     @arg XFMC_BANK1_NORSRAM1 XFMC Bank1 NOR/SRAM1
 *     @arg XFMC_BANK1_NORSRAM2 XFMC Bank1 NOR/SRAM2
 *     @arg XFMC_BANK1_NORSRAM3 XFMC Bank1 NOR/SRAM3
 *     @arg XFMC_BANK1_NORSRAM4 XFMC Bank1 NOR/SRAM4
 * @param Cmd new state of the Bank. This parameter can be: ENABLE or DISABLE.
 */
void XFMC_EnableNorSram(uint32_t Bank, FunctionalState Cmd)
{
    assert_param(IS_XFMC_NORSRAM_BANK(Bank));
    assert_param(IS_FUNCTIONAL_STATE(Cmd));

    if (Cmd != DISABLE)
    {
        /* Enable the selected NOR/SRAM Bank by setting the PBKEN bit in the BCRx register */
        XFMC_BANK1->BK1CSTCTRL[Bank] |= BCR_MBKEN_Set;
    }
    else
    {
        /* Disable the selected NOR/SRAM Bank by clearing the PBKEN bit in the BCRx register */
        XFMC_BANK1->BK1CSTCTRL[Bank] &= BCR_MBKEN_Reset;
    }
}

/**
 * @brief  Enables or disables the specified NAND Memory Bank.
 * @param Bank specifies the XFMC Bank to be used
 *   This parameter can be one of the following values:
 *     @arg XFMC_BANK2_NAND XFMC Bank2 NAND
 *     @arg XFMC_BANK3_NAND XFMC Bank3 NAND
 * @param Cmd new state of the Bank. This parameter can be: ENABLE or DISABLE.
 */
void XFMC_EnableNand(uint32_t Bank, FunctionalState Cmd)
{
    assert_param(IS_XFMC_NAND_BANK(Bank));
    assert_param(IS_FUNCTIONAL_STATE(Cmd));

    if (Cmd != DISABLE)
    {
        /* Enable the selected NAND Bank by setting the PBKEN bit in the PCRx register */
        if (Bank == XFMC_BANK2_NAND)
        {
            XFMC_BANK2->BK2CTRL |= PCR_PBKEN_Set;
        }
        else
        {
            XFMC_BANK3->BK3CTRL |= PCR_PBKEN_Set;
        }
    }
    else
    {
        /* Disable the selected NAND Bank by clearing the PBKEN bit in the PCRx register */
        if (Bank == XFMC_BANK2_NAND)
        {
            XFMC_BANK2->BK2CTRL &= PCR_PBKEN_Reset;
        }
        else
        {
            XFMC_BANK3->BK3CTRL &= PCR_PBKEN_Reset;
        }
    }
}

/**
 * @brief  Enables or disables the XFMC NAND ECC feature.
 * @param Bank specifies the XFMC Bank to be used
 *   This parameter can be one of the following values:
 *     @arg XFMC_BANK2_NAND XFMC Bank2 NAND
 *     @arg XFMC_BANK3_NAND XFMC Bank3 NAND
 * @param Cmd new state of the XFMC NAND ECC feature.
 *   This parameter can be: ENABLE or DISABLE.
 */
void XFMC_EnableNandEcc(uint32_t Bank, FunctionalState Cmd)
{
    assert_param(IS_XFMC_NAND_BANK(Bank));
    assert_param(IS_FUNCTIONAL_STATE(Cmd));

    if (Cmd != DISABLE)
    {
        /* Enable the selected NAND Bank ECC function by setting the ECCEN bit in the PCRx register */
        if (Bank == XFMC_BANK2_NAND)
        {
            XFMC_BANK2->BK2CTRL |= PCR_ECCEN_Set;
        }
        else
        {
            XFMC_BANK3->BK3CTRL |= PCR_ECCEN_Set;
        }
    }
    else
    {
        /* Disable the selected NAND Bank ECC function by clearing the ECCEN bit in the PCRx register */
        if (Bank == XFMC_BANK2_NAND)
        {
            XFMC_BANK2->BK2CTRL &= PCR_ECCEN_Reset;
        }
        else
        {
            XFMC_BANK3->BK3CTRL &= PCR_ECCEN_Reset;
        }
    }
}

/**
 * @brief  Returns the error correction code register value.
 * @param Bank specifies the XFMC Bank to be used
 *   This parameter can be one of the following values:
 *     @arg XFMC_BANK2_NAND XFMC Bank2 NAND
 *     @arg XFMC_BANK3_NAND XFMC Bank3 NAND
 * @return The Error Correction Code (ECC) value.
 */
uint32_t XFMC_GetEcc(uint32_t Bank)
{
    uint32_t eccval = 0x00000000;

    if (Bank == XFMC_BANK2_NAND)
    {
        /* Get the ECC2 register value */
        eccval = XFMC_BANK2->ECC2;
    }
    else
    {
        /* Get the ECC3 register value */
        eccval = XFMC_BANK3->ECC3;
    }
    /* Return the error correction code value */
    return (eccval);
}

/**
 * @brief  Checks whether the specified XFMC flag is set or not.
 * @param Bank specifies the XFMC Bank to be used
 *   This parameter can be one of the following values:
 *     @arg XFMC_BANK2_NAND XFMC Bank2 NAND
 *     @arg XFMC_BANK3_NAND XFMC Bank3 NAND
 *     @arg XFMC_Bank4_PCCARD XFMC Bank4 PCCARD
 * @param XFMC_FLAG specifies the flag to check.
 *   This parameter can be one of the following values:
 *     @arg XFMC_FLAG_RisingEdge Rising egde detection Flag.
 *     @arg XFMC_FLAG_Level Level detection Flag.
 *     @arg XFMC_FLAG_FallingEdge Falling egde detection Flag.
 *     @arg XFMC_FLAG_FEMPT Fifo empty Flag.
 * @return The new state of XFMC_FLAG (SET or RESET).
 */
FlagStatus XFMC_GetFlag(uint32_t Bank, uint32_t XFMC_FLAG)
{
    FlagStatus bitstatus = RESET;
    uint32_t tmpsr       = 0x00000000;

    /* Check the parameters */
    assert_param(IS_XFMC_GETFLAG_BANK(Bank));
    assert_param(IS_XFMC_GET_FLAG(XFMC_FLAG));

    if (Bank == XFMC_BANK2_NAND)
    {
        tmpsr = XFMC_BANK2->STS2;
    }
    else if (Bank == XFMC_BANK3_NAND)
    {
        tmpsr = XFMC_BANK3->STS3;
    }

    /* Get the flag status */
    if ((tmpsr & XFMC_FLAG) != (uint16_t)RESET)
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
 *     @arg XFMC_BANK2_NAND XFMC Bank2 NAND
 *     @arg XFMC_BANK3_NAND XFMC Bank3 NAND
 * @param XFMC_FLAG specifies the flag to clear.
 */
void XFMC_ClrFlag(uint32_t Bank, uint32_t XFMC_FLAG)
{
    /* Check the parameters */
    assert_param(IS_XFMC_GETFLAG_BANK(Bank));
    assert_param(IS_XFMC_CLEAR_FLAG(XFMC_FLAG));

    if (Bank == XFMC_BANK2_NAND)
    {
        XFMC_BANK2->STS2 &= ~XFMC_FLAG;
    }
    else if (Bank == XFMC_BANK3_NAND)
    {
        XFMC_BANK3->STS3 &= ~XFMC_FLAG;
    }
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
