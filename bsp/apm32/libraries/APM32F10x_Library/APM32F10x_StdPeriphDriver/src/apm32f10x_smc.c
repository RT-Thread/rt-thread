/*!
 * @file        apm32f10x_smc.c
 *
 * @brief       This file provides all the SMC firmware functions
 *
 * @version     V1.0.4
 *
 * @date        2022-12-01
 *
 * @attention
 *
 *  Copyright (C) 2020-2022 Geehy Semiconductor
 *
 *  You may not use this file except in compliance with the
 *  GEEHY COPYRIGHT NOTICE (GEEHY SOFTWARE PACKAGE LICENSE).
 *
 *  The program is only for reference, which is distributed in the hope
 *  that it will be useful and instructional for customers to develop
 *  their software. Unless required by applicable law or agreed to in
 *  writing, the program is distributed on an "AS IS" BASIS, WITHOUT
 *  ANY WARRANTY OR CONDITIONS OF ANY KIND, either express or implied.
 *  See the GEEHY SOFTWARE PACKAGE LICENSE for the governing permissions
 *  and limitations under the License.
 */

#include "apm32f10x_smc.h"
#include "apm32f10x_rcm.h"

/** @addtogroup APM32F10x_StdPeriphDriver
  @{
*/

/** @addtogroup SMC_Driver SMC Driver
  * @brief SMC driver modules
  @{
*/

/** @defgroup SMC_Functions Functions
  @{
*/

/*!
 * @brief     Reset the EMMMC NOR/SRAM Banks registers
 *
 * @param     bank: Select the EMMMC Bank.
 *                  The parameter can be one of following values:
 *                  @arg SMC_BANK1_NORSRAM_1: SMC Bank1 NOR/SRAM1
 *                  @arg SMC_BANK1_NORSRAM_2: SMC Bank1 NOR/SRAM2
 *                  @arg SMC_BANK1_NORSRAM_3: SMC Bank1 NOR/SRAM3
 *                  @arg SMC_BANK1_NORSRAM_4: SMC Bank1 NOR/SRAM4
 *
 * @retval    None
 */
void SMC_ResetNORSRAM(SMC_BANK1_NORSRAM_T bank)
{
    /* SMC_BANK1_NORSRAM_1 */
    if (bank == SMC_BANK1_NORSRAM_1)
    {
        SMC_Bank1->SNCTRL_T[bank] = 0x000030DB;
    }
    /* SMC_BANK1_NORSRAM_2, SMC_BANK1_NORSRAM_3 or SMC_BANK1_NORSRAM_4 */
    else
    {
        SMC_Bank1->SNCTRL_T[bank] = 0x000030D2;
    }
    SMC_Bank1->SNCTRL_T[bank + 1] = 0x0FFFFFFF;
    SMC_Bank1E->WRTTIM[bank] = 0x0FFFFFFF;
}

/*!
 * @brief     Reset the EMMMC NAND Banks registers
 *
 * @param     bank: Select the EMMMC Bank.
 *                  The parameter can be one of following values:
 *                  @arg SMC_BANK2_NAND: FSMC Bank2 NAND
 *                  @arg SMC_BANK3_NAND: FSMC Bank3 NAND
 *
 * @retval    None
 */
void SMC_ResetNAND(SMC_BANK_NAND_T bank)
{
    if (bank == SMC_BANK2_NAND)
    {
        /* Set the SMC_Bank2 registers to their reset values */
        SMC_Bank2->CTRL2   = 0x00000018;
        SMC_Bank2->STSINT2 = 0x00000040;
        SMC_Bank2->CMSTIM2 = 0xFCFCFCFC;
        SMC_Bank2->AMSTIM2 = 0xFCFCFCFC;
    }
    /* SMC BANK3 NAND */
    else
    {
        /* Set the SMC_Bank3 registers to their reset values */
        SMC_Bank3->CTRL3   = 0x00000018;
        SMC_Bank3->STSINT3 = 0x00000040;
        SMC_Bank3->CMSTIM3 = 0xFCFCFCFC;
        SMC_Bank3->AMSTIM3 = 0xFCFCFCFC;
    }
}

/*!
 * @brief     Reset the EMMMC PCCARD Banks registers
 *
 * @param     None
 *
 * @retval    None
 */
void SMC_ResetPCCard(void)
{
    /* Set the SMC_Bank4 registers to their reset values */
    SMC_Bank4->CTRL4   = 0x00000018;
    SMC_Bank4->STSINT4 = 0x00000040;
    SMC_Bank4->CMSTIM4 = 0xFCFCFCFC;
    SMC_Bank4->AMSTIM4 = 0xFCFCFCFC;
    SMC_Bank4->IOSTIM4 = 0xFCFCFCFC;
}

/*!
 * @brief     Configures the SMC NOR/SRAM Banks according to the specified parameters in the smcNORSRAMConfig.
 *
 * @param     smcNORSRAMConfig: Point to a SMC_NORSRAMConfig_T structure
 *
 * @retval    None
 */
void SMC_ConfigNORSRAM(SMC_NORSRAMConfig_T* smcNORSRAMConfig)
{
    /* Bank1 NOR/SRAM control register configuration */
    SMC_Bank1->SNCTRL_T[smcNORSRAMConfig->bank] =
        (uint32_t)smcNORSRAMConfig->dataAddressMux |
        smcNORSRAMConfig->memoryType |
        smcNORSRAMConfig->memoryDataWidth |
        smcNORSRAMConfig->burstAcceesMode |
        smcNORSRAMConfig->asynchronousWait |
        smcNORSRAMConfig->waitSignalPolarity |
        smcNORSRAMConfig->wrapMode |
        smcNORSRAMConfig->waitSignalActive |
        smcNORSRAMConfig->writeOperation |
        smcNORSRAMConfig->waiteSignal |
        smcNORSRAMConfig->extendedMode |
        smcNORSRAMConfig->writeBurst;

    if (smcNORSRAMConfig->memoryType == SMC_MEMORY_TYPE_NOR)
    {
        SMC_Bank1->SNCTRL_T[smcNORSRAMConfig->bank] |= 0x00000040;
    }

    /* Bank1 NOR/SRAM timing register configuration */
    SMC_Bank1->SNCTRL_T[smcNORSRAMConfig->bank + 1] =
        (uint32_t)smcNORSRAMConfig->readWriteTimingStruct->addressSetupTime |
        (smcNORSRAMConfig->readWriteTimingStruct->addressHodeTime << 4) |
        (smcNORSRAMConfig->readWriteTimingStruct->dataSetupTime << 8) |
        (smcNORSRAMConfig->readWriteTimingStruct->busTurnaroundTime << 16) |
        (smcNORSRAMConfig->readWriteTimingStruct->clockDivision << 20) |
        (smcNORSRAMConfig->readWriteTimingStruct->dataLatency << 24) |
        smcNORSRAMConfig->readWriteTimingStruct->accessMode;

    /* Bank1 NOR/SRAM timing register for write configuration, if extended mode is used */
    if (smcNORSRAMConfig->extendedMode == SMC_EXTENDEN_MODE_ENABLE)
    {
        SMC_Bank1E->WRTTIM[smcNORSRAMConfig->bank] =
            (uint32_t)smcNORSRAMConfig->writeTimingStruct->addressSetupTime |
            (smcNORSRAMConfig->writeTimingStruct->addressHodeTime << 4) |
            (smcNORSRAMConfig->writeTimingStruct->dataSetupTime << 8) |
            (smcNORSRAMConfig->writeTimingStruct->clockDivision << 20) |
            (smcNORSRAMConfig->writeTimingStruct->dataLatency << 24) |
            smcNORSRAMConfig->writeTimingStruct->accessMode;
    }
    else
    {
        SMC_Bank1E->WRTTIM[smcNORSRAMConfig->bank] = 0x0FFFFFFF;
    }
}

/*!
 * @brief     Configures the SMC NAND Banks according to the specified parameters in the smcNANDConfig.
 *
 * @param     smcNANDConfig : Point to a SMC_NANDConfig_T structure.
 *
 * @retval    None
 */
void SMC_ConfigNAND(SMC_NANDConfig_T* smcNANDConfig)
{
    uint32_t tmppcr = 0x00000000, tmppmem = 0x00000000, tmppatt = 0x00000000;

    /* Set the tmppcr value according to SMC_NANDInitStruct parameters */
    tmppcr = (uint32_t)smcNANDConfig->waitFeature | 0x00000008 |
             smcNANDConfig->memoryDataWidth |
             smcNANDConfig->ECC |
             smcNANDConfig->ECCPageSize |
             (smcNANDConfig->TCLRSetupTime << 9) |
             (smcNANDConfig->TARSetupTime << 13);

    /* Set tmppmem value according to SMC_CommonSpaceTimingStructure parameters */
    tmppmem = (uint32_t)smcNANDConfig->commonSpaceTimingStruct->setupTime |
              (smcNANDConfig->commonSpaceTimingStruct->waitSetupTime << 8) |
              (smcNANDConfig->commonSpaceTimingStruct->holdSetupTime << 16) |
              (smcNANDConfig->commonSpaceTimingStruct->HiZSetupTime << 24);

    /* Set tmppatt value according to SMC_AttributeSpaceTimingStructure parameters */
    tmppatt = (uint32_t)smcNANDConfig->attributeSpaceTimingStruct->setupTime |
              (smcNANDConfig->attributeSpaceTimingStruct->waitSetupTime << 8) |
              (smcNANDConfig->attributeSpaceTimingStruct->holdSetupTime << 16) |
              (smcNANDConfig->attributeSpaceTimingStruct->HiZSetupTime << 24);

    if (smcNANDConfig->bank == SMC_BANK2_NAND)
    {
        /* SMC_BANK2_NAND registers configuration */
        SMC_Bank2->CTRL2 = tmppcr;
        SMC_Bank2->CMSTIM2 = tmppmem;
        SMC_Bank2->AMSTIM2 = tmppatt;
    }
    else
    {
        /* SMC_BANK3_NAND registers configuration */
        SMC_Bank3->CTRL3 = tmppcr;
        SMC_Bank3->CMSTIM3 = tmppmem;
        SMC_Bank3->AMSTIM3 = tmppatt;
    }

}

/*!
 * @brief     Configures the SMC PCCARD according to the specified parameters in the smcPCCardConfig.
 *
 * @param     smcPCCardConfig: Point to a SMC_PCCARDConfig_T structure.
 *
 * @retval    None
 */
void SMC_ConfigPCCard(SMC_PCCARDConfig_T* smcPCCardConfig)
{
    /* Set the PCR4 register value according to SMC_PCCARDInitStruct parameters */
    SMC_Bank4->CTRL4 = (uint32_t)smcPCCardConfig->waitFeature | SMC_MEMORY_DATA_WIDTH_16BIT |
                       (smcPCCardConfig->TCLRSetupTime << 9) |
                       (smcPCCardConfig->TARSetupTime << 13);

    /* Set PMEM4 register value according to SMC_CommonSpaceTimingStructure parameters */
    SMC_Bank4->CMSTIM4 = (uint32_t)smcPCCardConfig->commonSpaceTimingStruct->setupTime |
                         (smcPCCardConfig->commonSpaceTimingStruct->waitSetupTime << 8) |
                         (smcPCCardConfig->commonSpaceTimingStruct->holdSetupTime << 16) |
                         (smcPCCardConfig->commonSpaceTimingStruct->HiZSetupTime << 24);

    /* Set PATT4 register value according to SMC_AttributeSpaceTimingStructure parameters */
    SMC_Bank4->AMSTIM4 = (uint32_t)smcPCCardConfig->attributeSpaceTimingStruct->setupTime |
                         (smcPCCardConfig->attributeSpaceTimingStruct->waitSetupTime << 8) |
                         (smcPCCardConfig->attributeSpaceTimingStruct->holdSetupTime << 16) |
                         (smcPCCardConfig->attributeSpaceTimingStruct->HiZSetupTime << 24);

    /* Set PIO4 register value according to SMC_IOSpaceTimingStructure parameters */
    SMC_Bank4->IOSTIM4 = (uint32_t)smcPCCardConfig->IOSpaceTimingStruct->setupTime |
                         (smcPCCardConfig->IOSpaceTimingStruct->waitSetupTime << 8) |
                         (smcPCCardConfig->IOSpaceTimingStruct->holdSetupTime << 16) |
                         (smcPCCardConfig->IOSpaceTimingStruct->HiZSetupTime << 24);
}

/*!
 * @brief     Fills each smcNORSRAMConfig member with its default value.
 *
 * @param     smcNORSRAMConfig : Point to a SMC_NORSRAMConfig_T structure.
 *
 * @retval    None
 */
void SMC_ConfigNORSRAMStructInit(SMC_NORSRAMConfig_T* smcNORSRAMConfig)
{
    /* Reset NOR/SRAM Init structure parameters values */
    smcNORSRAMConfig->bank = SMC_BANK1_NORSRAM_1;
    smcNORSRAMConfig->dataAddressMux = SMC_DATA_ADDRESS_MUX_ENABLE;
    smcNORSRAMConfig->memoryType = SMC_MEMORY_TYPE_SRAM;
    smcNORSRAMConfig->memoryDataWidth = SMC_MEMORY_DATA_WIDTH_8BIT;
    smcNORSRAMConfig->burstAcceesMode = SMC_BURST_ACCESS_MODE_DISABLE;
    smcNORSRAMConfig->asynchronousWait = SMC_ASYNCHRONOUS_WAIT_DISABLE;
    smcNORSRAMConfig->waitSignalPolarity = SMC_WAIT_SIGNAL_POLARITY_LOW;
    smcNORSRAMConfig->wrapMode = SMC_WRAP_MODE_DISABLE;
    smcNORSRAMConfig->waitSignalActive = SMC_WAIT_SIGNAL_ACTIVE_BEFORE_WAIT;
    smcNORSRAMConfig->writeOperation = SMC_WRITE_OPERATION_ENABLE;
    smcNORSRAMConfig->waiteSignal = SMC_WAITE_SIGNAL_ENABLE;
    smcNORSRAMConfig->extendedMode = SMC_EXTENDEN_MODE_DISABLE;
    smcNORSRAMConfig->writeBurst = SMC_WRITE_BURST_DISABLE;
    smcNORSRAMConfig->readWriteTimingStruct->addressSetupTime = 0xF;
    smcNORSRAMConfig->readWriteTimingStruct->addressHodeTime = 0xF;
    smcNORSRAMConfig->readWriteTimingStruct->dataSetupTime = 0xFF;
    smcNORSRAMConfig->readWriteTimingStruct->busTurnaroundTime = 0xF;
    smcNORSRAMConfig->readWriteTimingStruct->clockDivision = 0xF;
    smcNORSRAMConfig->readWriteTimingStruct->dataLatency = 0xF;
    smcNORSRAMConfig->readWriteTimingStruct->accessMode = SMC_ACCESS_MODE_A;
    smcNORSRAMConfig->writeTimingStruct->addressSetupTime = 0xF;
    smcNORSRAMConfig->writeTimingStruct->addressHodeTime = 0xF;
    smcNORSRAMConfig->writeTimingStruct->dataSetupTime = 0xFF;
    smcNORSRAMConfig->writeTimingStruct->busTurnaroundTime = 0xF;
    smcNORSRAMConfig->writeTimingStruct->clockDivision = 0xF;
    smcNORSRAMConfig->writeTimingStruct->dataLatency = 0xF;
    smcNORSRAMConfig->writeTimingStruct->accessMode = SMC_ACCESS_MODE_A;
}

/*!
 * @brief     Fills each smcNANDConfig member with its default value.
 *
 * @param     smcNANDConfig : Point to a SMC_NANDConfig_T structure.
 *
 * @retval    None
 */
void SMC_ConfigNANDStructInit(SMC_NANDConfig_T* smcNANDConfig)
{
    /* Reset NAND Init structure parameters values */
    smcNANDConfig->bank = SMC_BANK2_NAND;
    smcNANDConfig->waitFeature = SMC_WAIT_FEATURE_DISABLE;
    smcNANDConfig->memoryDataWidth = SMC_MEMORY_DATA_WIDTH_8BIT;
    smcNANDConfig->ECC = SMC_ECC_DISABLE;
    smcNANDConfig->ECCPageSize = SMC_ECC_PAGE_SIZE_BYTE_256;
    smcNANDConfig->TCLRSetupTime = 0x0;
    smcNANDConfig->TARSetupTime = 0x0;
    smcNANDConfig->commonSpaceTimingStruct->setupTime = 0xFC;
    smcNANDConfig->commonSpaceTimingStruct->waitSetupTime = 0xFC;
    smcNANDConfig->commonSpaceTimingStruct->holdSetupTime = 0xFC;
    smcNANDConfig->commonSpaceTimingStruct->HiZSetupTime = 0xFC;
    smcNANDConfig->attributeSpaceTimingStruct->setupTime = 0xFC;
    smcNANDConfig->attributeSpaceTimingStruct->waitSetupTime = 0xFC;
    smcNANDConfig->attributeSpaceTimingStruct->holdSetupTime = 0xFC;
    smcNANDConfig->attributeSpaceTimingStruct->HiZSetupTime = 0xFC;
}

/*!
 * @brief     Fills each smcPCCardConfig member with its default value.
 *
 * @param     smcPCCardConfig : Point to a SMC_PCCARDConfig_T structure.
 *
 * @retval    None
 */
void SMC_ConfigPCCardStructInit(SMC_PCCARDConfig_T* smcPCCardConfig)
{
    /* Reset PCCARD Init structure parameters values */
    smcPCCardConfig->waitFeature = SMC_WAIT_FEATURE_DISABLE;
    smcPCCardConfig->TCLRSetupTime = 0x0;
    smcPCCardConfig->TARSetupTime = 0x0;
    smcPCCardConfig->commonSpaceTimingStruct->setupTime = 0xFC;
    smcPCCardConfig->commonSpaceTimingStruct->waitSetupTime = 0xFC;
    smcPCCardConfig->commonSpaceTimingStruct->holdSetupTime = 0xFC;
    smcPCCardConfig->commonSpaceTimingStruct->HiZSetupTime = 0xFC;
    smcPCCardConfig->attributeSpaceTimingStruct->setupTime = 0xFC;
    smcPCCardConfig->attributeSpaceTimingStruct->waitSetupTime = 0xFC;
    smcPCCardConfig->attributeSpaceTimingStruct->holdSetupTime = 0xFC;
    smcPCCardConfig->attributeSpaceTimingStruct->HiZSetupTime = 0xFC;
    smcPCCardConfig->IOSpaceTimingStruct->setupTime = 0xFC;
    smcPCCardConfig->IOSpaceTimingStruct->waitSetupTime = 0xFC;
    smcPCCardConfig->IOSpaceTimingStruct->holdSetupTime = 0xFC;
    smcPCCardConfig->IOSpaceTimingStruct->HiZSetupTime = 0xFC;
}

/*!
 * @brief     Enable the specified NOR/SRAM Memory Bank.
 *
 * @param     bank: Select the EMMMC Bank.
 *                  The parameter can be one of following values:
 *                  @arg SMC_BANK1_NORSRAM_1: SMC Bank1 NOR/SRAM1
 *                  @arg SMC_BANK1_NORSRAM_2: SMC Bank1 NOR/SRAM2
 *                  @arg SMC_BANK1_NORSRAM_3: SMC Bank1 NOR/SRAM3
 *                  @arg SMC_BANK1_NORSRAM_4: SMC Bank1 NOR/SRAM4
 *
 * @retval    None
 */
void SMC_EnableNORSRAM(SMC_BANK1_NORSRAM_T bank)
{
    SMC_Bank1->SNCTRL_T[bank] |= 0x00000001;
}

/*!
 * @brief     Disable the specified NOR/SRAM Memory Bank.
 *
 * @param     bank: Select the EMMMC Bank.
 *                  The parameter can be one of following values:
 *                  @arg SMC_BANK1_NORSRAM_1: SMC Bank1 NOR/SRAM1
 *                  @arg SMC_BANK1_NORSRAM_2: SMC Bank1 NOR/SRAM2
 *                  @arg SMC_BANK1_NORSRAM_3: SMC Bank1 NOR/SRAM3
 *                  @arg SMC_BANK1_NORSRAM_4: SMC Bank1 NOR/SRAM4
 *
 * @retval    None
 */
void SMC_DisableNORSRAM(SMC_BANK1_NORSRAM_T bank)
{
    SMC_Bank1->SNCTRL_T[bank] &= 0x000FFFFE;
}

/*!
 * @brief     Enable the specified NAND Memory Bank.
 *
 * @param     bank: Select the EMMMC Bank.
 *                  The parameter can be one of following values:
 *                  @arg SMC_BANK2_NAND: FSMC Bank2 NAND
 *                  @arg SMC_BANK3_NAND: FSMC Bank3 NAND
 *
 * @retval    None
 */
void SMC_EnableNAND(SMC_BANK_NAND_T bank)
{
    if (bank == SMC_BANK2_NAND)
    {
        SMC_Bank2->CTRL2_B.MBKEN = BIT_SET;
    }
    else
    {
        SMC_Bank3->CTRL3_B.MBKEN = BIT_SET;
    }
}

/*!
 * @brief     Disable the specified NAND Memory Bank.
 *
 * @param     bank: Select the EMMMC Bank.
 *                  The parameter can be one of following values:
 *                  @arg SMC_BANK2_NAND: FSMC Bank2 NAND
 *                  @arg SMC_BANK3_NAND: FSMC Bank3 NAND
 *
 * @retval    None
 */
void SMC_DisableNAND(SMC_BANK_NAND_T bank)
{
    if (bank == SMC_BANK2_NAND)
    {
        SMC_Bank2->CTRL2_B.MBKEN = BIT_RESET;
    }
    else
    {
        SMC_Bank3->CTRL3_B.MBKEN = BIT_RESET;
    }
}

/*!
 * @brief     Enable the specified PC Card Memory Bank.
 *
 * @param     None
 *
 * @retval    None
 */
void SMC_EnablePCCARD(void)
{
    SMC_Bank4->CTRL4_B.MBKEN = BIT_SET;
}

/*!
 * @brief     Disable the specified PC Card Memory Bank.
 *
 * @param     None
 *
 * @retval    None
 */
void SMC_DisablePCCARD(void)
{
    SMC_Bank4->CTRL4_B.MBKEN = BIT_RESET;
}

/*!
 * @brief     Enable the SMC NAND ECC feature.
 *
 * @param     bank: Select the EMMMC Bank.
 *                  The parameter can be one of following values:
 *                  @arg SMC_BANK2_NAND: FSMC Bank2 NAND
 *                  @arg SMC_BANK3_NAND: FSMC Bank3 NAND
 *
 * @retval    None
 */
void SMC_EnableNANDECC(SMC_BANK_NAND_T bank)
{
    if (bank == SMC_BANK2_NAND)
    {
        SMC_Bank2->CTRL2 |= 0x00000040;
    }
    else
    {
        SMC_Bank3->CTRL3 |= 0x00000040;
    }
}

/*!
 * @brief     Disable the SMC Bank2 or Bank3 NAND ECC feature.
 *
 * @param     bank: Select the EMMMC Bank.
 *                  The parameter can be one of following values:
 *                  @arg SMC_BANK2_NAND: FSMC Bank2 NAND
 *                  @arg SMC_BANK3_NAND: FSMC Bank3 NAND
 *
 * @retval    None
 *
 */
void SMC_DisableNANDECC(SMC_BANK_NAND_T bank)
{
    if (bank == SMC_BANK2_NAND)
    {
        SMC_Bank2->CTRL2 &= 0x000FFFBF;
    }
    else
    {
        SMC_Bank3->CTRL3 &= 0x000FFFBF;
    }
}

/*!
 * @brief     Read the error correction code register value.
 *
 * @param     bank: Select the EMMMC Bank.
 *                  The parameter can be one of following values:
 *                  @arg SMC_BANK2_NAND: FSMC Bank2 NAND
 *                  @arg SMC_BANK3_NAND: FSMC Bank3 NAND
 *
 * @retval    The value of Error Correction Code (ECC).
 */
uint32_t  SMC_ReadECC(SMC_BANK_NAND_T bank)
{
    uint32_t eccval = 0x00000000;

    if (bank == SMC_BANK2_NAND)
    {
        eccval = SMC_Bank2->ECCRS2;
    }
    else
    {
        eccval = SMC_Bank3->ECCRS3;
    }
    return eccval;
}

/*!
 * @brief    Enable the specified SMC interrupts.
 *
 * @param    bank: Select the EMMMC Bank.
 *                 The parameter can be one of following values:
 *                 @arg SMC_BANK2_NAND  : FSMC Bank2 NAND
 *                 @arg SMC_BANK3_NAND  : FSMC Bank3 NAND
 *                 @arg SMC_BANK4_PCCARD: FSMC Bank4 PCCARD
 *
 * @param    interrupt: Select the SMC interrupt sources.
 *                      This parameter can be any combination of the following values:
 *                      @arg SMC_INT_EDGE_RISING : Rising edge detection interrupt.
 *                      @arg SMC_INT_LEVEL_HIGH  : High level detection interrupt.
 *                      @arg SMC_INT_EDGE_FALLING: Falling edge detection interrupt.
 *
 * @retval   None
 */
void SMC_EnableInterrupt(SMC_BANK_NAND_T bank, uint32_t interrupt)
{
    if (bank == SMC_BANK2_NAND)
    {
        SMC_Bank2->STSINT2 |= interrupt;
    }
    else if (bank == SMC_BANK3_NAND)
    {
        SMC_Bank3->STSINT3 |= interrupt;
    }
    else
    {
        SMC_Bank4->STSINT4 |= interrupt;
    }
}

/*!
 * @brief    Enable the specified SMC interrupts.
 *
 * @param    bank: Select the EMMMC Bank.
 *                 The parameter can be one of following values:
 *                 @arg SMC_BANK2_NAND  : FSMC Bank2 NAND
 *                 @arg SMC_BANK3_NAND  : FSMC Bank3 NAND
 *                 @arg SMC_BANK4_PCCARD: FSMC Bank4 PCCARD
 *
 * @param    interrupt: Select the SMC interrupt sources.
 *                      This parameter can be any combination of the following values:
 *                      @arg SMC_INT_EDGE_RISING : Rising edge detection interrupt.
 *                      @arg SMC_INT_LEVEL_HIGH  : High level edge detection interrupt.
 *                      @arg SMC_INT_EDGE_FALLING: Falling edge detection interrupt.
 *
 * @retval   None
 */
void SMC_DisableInterrupt(SMC_BANK_NAND_T bank, uint32_t interrupt)
{
    if (bank == SMC_BANK2_NAND)
    {
        SMC_Bank2->STSINT2 &= ~interrupt;
    }
    else if (bank == SMC_BANK3_NAND)
    {
        SMC_Bank3->STSINT3 &= ~interrupt;
    }
    else
    {
        SMC_Bank4->STSINT4 &= ~interrupt;
    }
}

/*!
 * @brief    Read the status of specified SMC flag.
 *
 * @param    bank: Select the EMMMC Bank.
 *                 The parameter can be one of following values:
 *                 @arg SMC_BANK2_NAND  : FSMC Bank2 NAND
 *                 @arg SMC_BANK3_NAND  : FSMC Bank3 NAND
 *                 @arg SMC_BANK4_PCCARD: FSMC Bank4 PCCARD
 *
 * @param    flag: Select the SMC interrupt sources.
 *                 This parameter can be one of the following values:
 *                 @arg SMC_FLAG_EDGE_RISING : Rising egde detection Flag.
 *                 @arg SMC_FLAG_LEVEL_HIGH  : High level detection Flag.
 *                 @arg SMC_FLAG_EDGE_FALLING: Falling egde detection Flag.
 *                 @arg SMC_FLAG_FIFO_EMPTY  : FIFO empty Flag.
 *
 * @retval    SET or RESET
 *
 */
uint8_t SMC_ReadStatusFlag(SMC_BANK_NAND_T bank, SMC_FLAG_T flag)
{
    uint32_t tmpsr = 0x00000000;

    if (bank == SMC_BANK2_NAND)
    {
        tmpsr = SMC_Bank2->STSINT2;
    }
    else if (bank == SMC_BANK3_NAND)
    {
        tmpsr = SMC_Bank3->STSINT3;
    }
    else
    {
        tmpsr = SMC_Bank4->STSINT4;
    }
    /* Get the flag status */
    if ((tmpsr & flag) != RESET)
    {
        return SET;
    }
    else
    {
        return RESET;
    }
}

/*!
 * @brief    Clear the SMC's pending flags.
 *
 * @param    bank: Select the EMMMC Bank.
 *                 The parameter can be one of following values:
 *                 @arg SMC_BANK2_NAND  : FSMC Bank2 NAND
 *                 @arg SMC_BANK3_NAND  : FSMC Bank3 NAND
 *                 @arg SMC_BANK4_PCCARD: FSMC Bank4 PCCARD
 *
 * @param    flag: Select the SMC interrupt sources.
 *                 This parameter can be any combination of the following values:
 *                 @arg SMC_FLAG_EDGE_RISING : Rising egde detection Flag.
 *                 @arg SMC_FLAG_LEVEL_HIGH  : High level detection Flag.
 *                 @arg SMC_FLAG_EDGE_FALLING: Falling egde detection Flag.
 *
 * @retval    None
 */
void SMC_ClearStatusFlag(SMC_BANK_NAND_T bank, uint32_t flag)
{
    if (bank == SMC_BANK2_NAND)
    {
        SMC_Bank2->STSINT2 &= ~flag;
    }
    else if (bank == SMC_BANK3_NAND)
    {
        SMC_Bank3->STSINT3 &= ~flag;
    }
    else
    {
        SMC_Bank4->STSINT4 &= ~flag;
    }
}

/*!
 * @brief    Read the specified SMC interrupt has occurred or not.
 *
 * @param    bank: Select the EMMMC Bank.
 *                 The parameter can be one of following values:
 *                 @arg SMC_BANK2_NAND  : FSMC Bank2 NAND
 *                 @arg SMC_BANK3_NAND  : FSMC Bank3 NAND
 *                 @arg SMC_BANK4_PCCARD: FSMC Bank4 PCCARD
 *
 * @param    interrupt: Select the SMC interrupt source.
 *                      This parameter can be one of the following values:
 *                      @arg SMC_INT_EDGE_RISING : Rising edge detection interrupt.
 *                      @arg SMC_INT_LEVEL_HIGH  : High level edge detection interrupt.
 *                      @arg SMC_INT_EDGE_FALLING: Falling edge detection interrupt.
 *
 * @retval   The status of specified SMC interrupt source.
 */
uint8_t SMC_ReadIntFlag(SMC_BANK_NAND_T bank, SMC_INT_T flag)
{
    uint32_t tmpsr = 0x0, itstatus = 0x0, itenable = 0x0;

    if (bank == SMC_BANK2_NAND)
    {
        tmpsr = SMC_Bank2->STSINT2;
    }
    else if (bank == SMC_BANK3_NAND)
    {
        tmpsr = SMC_Bank3->STSINT3;
    }
    else
    {
        tmpsr = SMC_Bank4->STSINT4;
    }

    itstatus = tmpsr & flag;
    itenable = tmpsr & (flag >> 3);

    if ((itstatus != RESET) && (itenable != RESET))
    {
        return SET;
    }
    else
    {
        return RESET;
    }
}

/*!
 * @brief    Clear the SMC's interrupt Flag.
 *
 * @param    bank: Select the EMMMC Bank.
 *                 The parameter can be one of following values:
 *                 @arg SMC_BANK2_NAND  : FSMC Bank2 NAND
 *                 @arg SMC_BANK3_NAND  : FSMC Bank3 NAND
 *                 @arg SMC_BANK4_PCCARD: FSMC Bank4 PCCARD
 *
 * @param    interrupt: Select the SMC interrupt sources.
 *                      This parameter can be any combination of the following values:
 *                      @arg SMC_INT_EDGE_RISING : Rising edge detection interrupt.
 *                      @arg SMC_INT_LEVEL_HIGH  : High level edge detection interrupt.
 *                      @arg SMC_INT_EDGE_FALLING: Falling edge detection interrupt.
 *
 * @retval   None
 */
void SMC_ClearIntFlag(SMC_BANK_NAND_T bank, uint32_t flag)
{
    if (bank == SMC_BANK2_NAND)
    {
        SMC_Bank2->STSINT2 &= ~(flag >> 3);
    }
    else if (bank == SMC_BANK3_NAND)
    {
        SMC_Bank3->STSINT3 &= ~(flag >> 3);
    }
    else
    {
        SMC_Bank4->STSINT4 &= ~(flag >> 3);
    }
}

/**@} end of group SMC_Functions */
/**@} end of group SMC_Driver */
/**@} end of group APM32F10x_StdPeriphDriver */
