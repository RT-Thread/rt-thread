/*!
 * @file        apm32f10x_emmc.c
 *
 * @brief       This file provides all the EMMC firmware functions
 *
 * @version     V1.0.2
 *
 * @date        2022-01-05
 *
 * @attention
 *
 *  Copyright (C) 2020-2022 Geehy Semiconductor
 *
 *  You may not use this file except in compliance with the
 *  GEEHY COPYRIGHT NOTICE (GEEHY SOFTWARE PACKAGE LICENSE).
 *
 *  The program is only for reference, which is distributed in the hope
 *  that it will be usefull and instructional for customers to develop
 *  their software. Unless required by applicable law or agreed to in
 *  writing, the program is distributed on an "AS IS" BASIS, WITHOUT
 *  ANY WARRANTY OR CONDITIONS OF ANY KIND, either express or implied.
 *  See the GEEHY SOFTWARE PACKAGE LICENSE for the governing permissions
 *  and limitations under the License.
 */

#include "apm32f10x_emmc.h"
#include "apm32f10x_rcm.h"

/** @addtogroup Peripherals_Library Standard Peripheral Library
  @{
*/

/** @addtogroup EMMC_Driver EMMC Driver
  @{
*/

/** @addtogroup EMMC_Fuctions Fuctions
  @{
*/

/*!
 * @brief     Rest the EMMMC NOR/SRAM Banks registers
 *
 * @param     bank: Selects the EMMMC Bank.
 *                  The parameter can be one of following values:
 *                  @arg EMMC_BANK1_NORSRAM_1: EMMC Bank1 NOR/SRAM1
 *                  @arg EMMC_BANK1_NORSRAM_2: EMMC Bank1 NOR/SRAM2
 *                  @arg EMMC_BANK1_NORSRAM_3: EMMC Bank1 NOR/SRAM3
 *                  @arg EMMC_BANK1_NORSRAM_4: EMMC Bank1 NOR/SRAM4
 *
 * @retval    None
 */
void EMMC_ResetNORSRAM(EMMC_BANK1_NORSRAM_T bank)
{
    /** EMMC_BANK1_NORSRAM_1 */
    if (bank == EMMC_BANK1_NORSRAM_1)
    {
        EMMC_Bank1->SNCTRL_T[bank] = 0x000030DB;
    }
    /** EMMC_BANK1_NORSRAM_2,  EMMC_BANK1_NORSRAM_3 or EMMC_BANK1_NORSRAM_4 */
    else
    {
        EMMC_Bank1->SNCTRL_T[bank] = 0x000030D2;
    }
    EMMC_Bank1->SNCTRL_T[bank + 1] = 0x0FFFFFFF;
    EMMC_Bank1E->WRTTIM[bank] = 0x0FFFFFFF;
}

/*!
 * @brief     Rest the EMMMC NAND Banks registers
 *
 * @param     bank: Selects the EMMMC Bank.
 *                  The parameter can be one of following values:
 *                  @arg EMMC_BANK2_NAND: FSMC Bank2 NAND
 *                  @arg EMMC_BANK3_NAND: FSMC Bank3 NAND
 *
 * @retval    None
 */
void EMMC_ResetNAND(EMMC_BANK_NAND_T bank)
{
    if (bank == EMMC_BANK2_NAND)
    {
        /** Set the EMMC_Bank2 registers to their reset values */
        EMMC_Bank2->CTRL2 = 0x00000018;
        EMMC_Bank2->STSINT2 = 0x00000040;
        EMMC_Bank2->CMSTIM2 = 0xFCFCFCFC;
        EMMC_Bank2->AMSTIM2 = 0xFCFCFCFC;
    }
    /** EMMC_BANK3_NAND */
    else
    {
        /** Set the EMMC_Bank3 registers to their reset values */
        EMMC_Bank3->CTRL3 = 0x00000018;
        EMMC_Bank3->STSINT3 = 0x00000040;
        EMMC_Bank3->CMSTIM3 = 0xFCFCFCFC;
        EMMC_Bank3->AMSTIM3 = 0xFCFCFCFC;
    }
}

/*!
 * @brief     Reset the EMMMC PCCARD Banks registers
 *
 * @param     None
 *
 * @retval    None
 */
void EMMC_ResetPCCard(void)
{
    /** Set the EMMC_Bank4 registers to their reset values */
    EMMC_Bank4->CTRL4 = 0x00000018;
    EMMC_Bank4->STSINT4 = 0x00000040;
    EMMC_Bank4->CMSTIM4 = 0xFCFCFCFC;
    EMMC_Bank4->AMSTIM4 = 0xFCFCFCFC;
    EMMC_Bank4->IOSTIM4 = 0xFCFCFCFC;
}

/*!
 * @brief     Config the EMMC NOR/SRAM Banks according to the specified parameters in the emmcNORSRAMConfig.
 *
 * @param     emmcNORSRAMConfig: Point to a EMMC_NORSRAMConfig_T structure
 *
 * @retval    None
 */
void EMMC_ConfigNORSRAM(EMMC_NORSRAMConfig_T *emmcNORSRAMConfig)
{
    /** Bank1 NOR/SRAM control register configuration */
    EMMC_Bank1->SNCTRL_T[emmcNORSRAMConfig->bank] =
        (uint32_t)emmcNORSRAMConfig->dataAddressMux |
        emmcNORSRAMConfig->memoryType |
        emmcNORSRAMConfig->memoryDataWidth |
        emmcNORSRAMConfig->burstAcceesMode |
        emmcNORSRAMConfig->asynchronousWait |
        emmcNORSRAMConfig->waitSignalPolarity |
        emmcNORSRAMConfig->wrapMode |
        emmcNORSRAMConfig->waitSignalActive |
        emmcNORSRAMConfig->writeOperation |
        emmcNORSRAMConfig->waiteSignal |
        emmcNORSRAMConfig->extendedMode |
        emmcNORSRAMConfig->writeBurst;

    if (emmcNORSRAMConfig->memoryType == EMMC_MEMORY_TYPE_NOR)
    {
        EMMC_Bank1->SNCTRL_T[emmcNORSRAMConfig->bank] |= 0x00000040;
    }

    /** Bank1 NOR/SRAM timing register configuration */
    EMMC_Bank1->SNCTRL_T[emmcNORSRAMConfig->bank + 1] =
        (uint32_t)emmcNORSRAMConfig->readWriteTimingStruct->addressSetupTime |
        (emmcNORSRAMConfig->readWriteTimingStruct->addressHodeTime << 4) |
        (emmcNORSRAMConfig->readWriteTimingStruct->dataSetupTime << 8) |
        (emmcNORSRAMConfig->readWriteTimingStruct->busTurnaroundTime << 16) |
        (emmcNORSRAMConfig->readWriteTimingStruct->clockDivision << 20) |
        (emmcNORSRAMConfig->readWriteTimingStruct->dataLatency << 24) |
        emmcNORSRAMConfig->readWriteTimingStruct->accessMode;

    /** Bank1 NOR/SRAM timing register for write configuration, if extended mode is used */
    if (emmcNORSRAMConfig->extendedMode == EMMC_EXTENDEN_MODE_ENABLE)
    {
        EMMC_Bank1E->WRTTIM[emmcNORSRAMConfig->bank] =
            (uint32_t)emmcNORSRAMConfig->writeTimingStruct->addressSetupTime |
            (emmcNORSRAMConfig->writeTimingStruct->addressHodeTime << 4) |
            (emmcNORSRAMConfig->writeTimingStruct->dataSetupTime << 8) |
            (emmcNORSRAMConfig->writeTimingStruct->clockDivision << 20) |
            (emmcNORSRAMConfig->writeTimingStruct->dataLatency << 24) |
            emmcNORSRAMConfig->writeTimingStruct->accessMode;
    }
    else
    {
        EMMC_Bank1E->WRTTIM[emmcNORSRAMConfig->bank] = 0x0FFFFFFF;
    }
}

/*!
 * @brief     Config the EMMC NAND Banks according to the specified parameters in the emmcNANDConfig.
 *
 * @param     emmcNANDConfig : Point to a EMMC_NANDConfig_T structure.
 *
 * @retval    None
 */
void EMMC_ConfigNAND(EMMC_NANDConfig_T *emmcNANDConfig)
{
    uint32_t tmppcr = 0x00000000, tmppmem = 0x00000000, tmppatt = 0x00000000;

    /** Set the tmppcr value according to EMMC_NANDInitStruct parameters */
    tmppcr = (uint32_t)emmcNANDConfig->waitFeature | 0x00000008 |
             emmcNANDConfig->memoryDataWidth |
             emmcNANDConfig->ECC |
             emmcNANDConfig->ECCPageSize |
             (emmcNANDConfig->TCLRSetupTime << 9) |
             (emmcNANDConfig->TARSetupTime << 13);

    /** Set tmppmem value according to EMMC_CommonSpaceTimingStructure parameters */
    tmppmem = (uint32_t)emmcNANDConfig->commonSpaceTimingStruct->setupTime |
              (emmcNANDConfig->commonSpaceTimingStruct->waitSetupTime << 8) |
              (emmcNANDConfig->commonSpaceTimingStruct->holdSetupTime << 16) |
              (emmcNANDConfig->commonSpaceTimingStruct->HiZSetupTime << 24);

    /** Set tmppatt value according to EMMC_AttributeSpaceTimingStructure parameters */
    tmppatt = (uint32_t)emmcNANDConfig->attributeSpaceTimingStruct->setupTime |
              (emmcNANDConfig->attributeSpaceTimingStruct->waitSetupTime << 8) |
              (emmcNANDConfig->attributeSpaceTimingStruct->holdSetupTime << 16) |
              (emmcNANDConfig->attributeSpaceTimingStruct->HiZSetupTime << 24);

    if (emmcNANDConfig->bank == EMMC_BANK2_NAND)
    {
        /** EMMC_BANK2_NAND registers configuration */
        EMMC_Bank2->CTRL2 = tmppcr;
        EMMC_Bank2->CMSTIM2 = tmppmem;
        EMMC_Bank2->AMSTIM2 = tmppatt;
    }
    else
    {
        /** EMMC_BANK3_NAND registers configuration */
        EMMC_Bank3->CTRL3 = tmppcr;
        EMMC_Bank3->CMSTIM3 = tmppmem;
        EMMC_Bank3->AMSTIM3 = tmppatt;
    }

}

/*!
 * @brief     Config the EMMC PCCARD according to the specified parameters in the emmcPCCardConfig.
 *
 * @param     emmcPCCardConfig: Point to a EMMC_PCCARDConfig_T structure.
 *
 * @retval    None
 */
void EMMC_ConfigPCCard(EMMC_PCCARDConfig_T *emmcPCCardConfig)
{
    /** Set the PCR4 register value according to EMMC_PCCARDInitStruct parameters */
    EMMC_Bank4->CTRL4 = (uint32_t)emmcPCCardConfig->waitFeature | EMMC_MEMORY_DATA_WIDTH_16BIT |
                        (emmcPCCardConfig->TCLRSetupTime << 9) |
                        (emmcPCCardConfig->TARSetupTime << 13);

    /** Set PMEM4 register value according to EMMC_CommonSpaceTimingStructure parameters */
    EMMC_Bank4->CMSTIM4 = (uint32_t)emmcPCCardConfig->commonSpaceTimingStruct->setupTime |
                          (emmcPCCardConfig->commonSpaceTimingStruct->waitSetupTime << 8) |
                          (emmcPCCardConfig->commonSpaceTimingStruct->holdSetupTime << 16) |
                          (emmcPCCardConfig->commonSpaceTimingStruct->HiZSetupTime << 24);

    /** Set PATT4 register value according to EMMC_AttributeSpaceTimingStructure parameters */
    EMMC_Bank4->AMSTIM4 = (uint32_t)emmcPCCardConfig->attributeSpaceTimingStruct->setupTime |
                          (emmcPCCardConfig->attributeSpaceTimingStruct->waitSetupTime << 8) |
                          (emmcPCCardConfig->attributeSpaceTimingStruct->holdSetupTime << 16) |
                          (emmcPCCardConfig->attributeSpaceTimingStruct->HiZSetupTime << 24);

    /** Set PIO4 register value according to EMMC_IOSpaceTimingStructure parameters */
    EMMC_Bank4->IOSTIM4 = (uint32_t)emmcPCCardConfig->IOSpaceTimingStruct->setupTime |
                          (emmcPCCardConfig->IOSpaceTimingStruct->waitSetupTime << 8) |
                          (emmcPCCardConfig->IOSpaceTimingStruct->holdSetupTime << 16) |
                          (emmcPCCardConfig->IOSpaceTimingStruct->HiZSetupTime << 24);
}

/*!
 * @brief     Fills each emmcNORSRAMConfig member with its default value.
 *
 * @param     emmcNORSRAMConfig : Point to a EMMC_NORSRAMConfig_T structure.
 *
 * @retval    None
 */
void EMMC_ConfigNORSRAMStructInit(EMMC_NORSRAMConfig_T *emmcNORSRAMConfig)
{
    /** Reset NOR/SRAM Init structure parameters values */
    emmcNORSRAMConfig->bank = EMMC_BANK1_NORSRAM_1;
    emmcNORSRAMConfig->dataAddressMux = EMMC_DATA_ADDRESS_MUX_ENABLE;
    emmcNORSRAMConfig->memoryType = EMMC_MEMORY_TYPE_SRAM;
    emmcNORSRAMConfig->memoryDataWidth = EMMC_MEMORY_DATA_WIDTH_8BIT;
    emmcNORSRAMConfig->burstAcceesMode = EMMC_BURST_ACCESS_MODE_DISABLE;
    emmcNORSRAMConfig->asynchronousWait = EMMC_ASYNCHRONOUS_WAIT_DISABLE;
    emmcNORSRAMConfig->waitSignalPolarity = EMMC_WAIT_SIGNAL_POLARITY_LOW;
    emmcNORSRAMConfig->wrapMode = EMMC_WRAP_MODE_DISABLE;
    emmcNORSRAMConfig->waitSignalActive = EMMC_WAIT_SIGNAL_ACTIVE_BEFORE_WAIT;
    emmcNORSRAMConfig->writeOperation = EMMC_WRITE_OPERATION_ENABLE;
    emmcNORSRAMConfig->waiteSignal = EMMC_WAITE_SIGNAL_ENABLE;
    emmcNORSRAMConfig->extendedMode = EMMC_EXTENDEN_MODE_DISABLE;
    emmcNORSRAMConfig->writeBurst = EMMC_WRITE_BURST_DISABLE;
    emmcNORSRAMConfig->readWriteTimingStruct->addressSetupTime = 0xF;
    emmcNORSRAMConfig->readWriteTimingStruct->addressHodeTime = 0xF;
    emmcNORSRAMConfig->readWriteTimingStruct->dataSetupTime = 0xFF;
    emmcNORSRAMConfig->readWriteTimingStruct->busTurnaroundTime = 0xF;
    emmcNORSRAMConfig->readWriteTimingStruct->clockDivision = 0xF;
    emmcNORSRAMConfig->readWriteTimingStruct->dataLatency = 0xF;
    emmcNORSRAMConfig->readWriteTimingStruct->accessMode = EMMC_ACCESS_MODE_A;
    emmcNORSRAMConfig->writeTimingStruct->addressSetupTime = 0xF;
    emmcNORSRAMConfig->writeTimingStruct->addressHodeTime = 0xF;
    emmcNORSRAMConfig->writeTimingStruct->dataSetupTime = 0xFF;
    emmcNORSRAMConfig->writeTimingStruct->busTurnaroundTime = 0xF;
    emmcNORSRAMConfig->writeTimingStruct->clockDivision = 0xF;
    emmcNORSRAMConfig->writeTimingStruct->dataLatency = 0xF;
    emmcNORSRAMConfig->writeTimingStruct->accessMode = EMMC_ACCESS_MODE_A;

}

/*!
 * @brief     Fills each emmcNANDConfig member with its default value.
 *
 * @param     emmcNANDConfig : Point to a EMMC_NANDConfig_T structure.
 *
 * @retval    None
 */
void EMMC_ConfigNANDStructInit(EMMC_NANDConfig_T *emmcNANDConfig)
{
    /** Reset NAND Init structure parameters values */
    emmcNANDConfig->bank = EMMC_BANK2_NAND;
    emmcNANDConfig->waitFeature = EMMC_WAIT_FEATURE_DISABLE;
    emmcNANDConfig->memoryDataWidth = EMMC_MEMORY_DATA_WIDTH_8BIT;
    emmcNANDConfig->ECC = EMMC_ECC_DISABLE;
    emmcNANDConfig->ECCPageSize = EMMC_ECC_PAGE_SIZE_BYTE_256;
    emmcNANDConfig->TCLRSetupTime = 0x0;
    emmcNANDConfig->TARSetupTime = 0x0;
    emmcNANDConfig->commonSpaceTimingStruct->setupTime = 0xFC;
    emmcNANDConfig->commonSpaceTimingStruct->waitSetupTime = 0xFC;
    emmcNANDConfig->commonSpaceTimingStruct->holdSetupTime = 0xFC;
    emmcNANDConfig->commonSpaceTimingStruct->HiZSetupTime = 0xFC;
    emmcNANDConfig->attributeSpaceTimingStruct->setupTime = 0xFC;
    emmcNANDConfig->attributeSpaceTimingStruct->waitSetupTime = 0xFC;
    emmcNANDConfig->attributeSpaceTimingStruct->holdSetupTime = 0xFC;
    emmcNANDConfig->attributeSpaceTimingStruct->HiZSetupTime = 0xFC;
}

/*!
 * @brief     Fills each emmcPCCardConfig member with its default value.
 *
 * @param     emmcPCCardConfig : Point to a EMMC_PCCARDConfig_T structure.
 *
 * @retval    None
 */
void EMMC_ConfigPCCardStructInit(EMMC_PCCARDConfig_T *emmcPCCardConfig)
{
    /** Reset PCCARD Init structure parameters values */
    emmcPCCardConfig->waitFeature = EMMC_WAIT_FEATURE_DISABLE;
    emmcPCCardConfig->TCLRSetupTime = 0x0;
    emmcPCCardConfig->TARSetupTime = 0x0;
    emmcPCCardConfig->commonSpaceTimingStruct->setupTime = 0xFC;
    emmcPCCardConfig->commonSpaceTimingStruct->waitSetupTime = 0xFC;
    emmcPCCardConfig->commonSpaceTimingStruct->holdSetupTime = 0xFC;
    emmcPCCardConfig->commonSpaceTimingStruct->HiZSetupTime = 0xFC;
    emmcPCCardConfig->attributeSpaceTimingStruct->setupTime = 0xFC;
    emmcPCCardConfig->attributeSpaceTimingStruct->waitSetupTime = 0xFC;
    emmcPCCardConfig->attributeSpaceTimingStruct->holdSetupTime = 0xFC;
    emmcPCCardConfig->attributeSpaceTimingStruct->HiZSetupTime = 0xFC;
    emmcPCCardConfig->IOSpaceTimingStruct->setupTime = 0xFC;
    emmcPCCardConfig->IOSpaceTimingStruct->waitSetupTime = 0xFC;
    emmcPCCardConfig->IOSpaceTimingStruct->holdSetupTime = 0xFC;
    emmcPCCardConfig->IOSpaceTimingStruct->HiZSetupTime = 0xFC;
}

/*!
 * @brief     Enables the specified NOR/SRAM Memory Bank.
 *
 * @param     bank: Selects the EMMMC Bank.
 *                  The parameter can be one of following values:
 *                  @arg EMMC_BANK1_NORSRAM_1: EMMC Bank1 NOR/SRAM1
 *                  @arg EMMC_BANK1_NORSRAM_2: EMMC Bank1 NOR/SRAM2
 *                  @arg EMMC_BANK1_NORSRAM_3: EMMC Bank1 NOR/SRAM3
 *                  @arg EMMC_BANK1_NORSRAM_4: EMMC Bank1 NOR/SRAM4
 *
 * @retval    None
 */
void EMMC_EnableNORSRAM(EMMC_BANK1_NORSRAM_T bank)
{
    EMMC_Bank1->SNCTRL_T[bank] |= 0x00000001;
}

/*!
 * @brief     Disbles the specified NOR/SRAM Memory Bank.
 *
 * @param     bank: Selects the EMMMC Bank.
 *                  The parameter can be one of following values:
 *                  @arg EMMC_BANK1_NORSRAM_1: EMMC Bank1 NOR/SRAM1
 *                  @arg EMMC_BANK1_NORSRAM_2: EMMC Bank1 NOR/SRAM2
 *                  @arg EMMC_BANK1_NORSRAM_3: EMMC Bank1 NOR/SRAM3
 *                  @arg EMMC_BANK1_NORSRAM_4: EMMC Bank1 NOR/SRAM4
 *
 * @retval    None
 */
void EMMC_DisableNORSRAM(EMMC_BANK1_NORSRAM_T bank)
{
    EMMC_Bank1->SNCTRL_T[bank] &= 0x000FFFFE;
}

/*!
 * @brief     Enables the specified NAND Memory Bank.
 *
 * @param     bank: Selects the EMMMC Bank.
 *                  The parameter can be one of following values:
 *                  @arg EMMC_BANK2_NAND: FSMC Bank2 NAND
 *                  @arg EMMC_BANK3_NAND: FSMC Bank3 NAND
 *
 * @retval    None
 */
void EMMC_EnableNAND(EMMC_BANK_NAND_T bank)
{
    if (bank == EMMC_BANK2_NAND)
    {
        EMMC_Bank2->CTRL2_B.MBKEN = BIT_SET;
    }
    else
    {
        EMMC_Bank3->CTRL3_B.MBKEN = BIT_SET;
    }
}

/*!
 * @brief     Disbles the specified NAND Memory Bank.
 *
 * @param     bank: Selects the EMMMC Bank.
 *                  The parameter can be one of following values:
 *                  @arg EMMC_BANK2_NAND: FSMC Bank2 NAND
 *                  @arg EMMC_BANK3_NAND: FSMC Bank3 NAND
 *
 * @retval    None
 */
void EMMC_DisableNAND(EMMC_BANK_NAND_T bank)
{
    if (bank == EMMC_BANK2_NAND)
    {
        EMMC_Bank2->CTRL2_B.MBKEN = BIT_RESET;
    }
    else
    {
        EMMC_Bank3->CTRL3_B.MBKEN = BIT_RESET;
    }
}

/*!
 * @brief     Enables the specified PC Card Memory Bank.
 *
 * @param     None
 *
 * @retval    None
 */
void EMMC_EnablePCCARD(void)
{
    EMMC_Bank4->CTRL4_B.MBKEN = BIT_SET;
}

/*!
 * @brief     Disables the specified PC Card Memory Bank.
 *
 * @param     None
 *
 * @retval    None
 */
void EMMC_DisablePCCARD(void)
{
    EMMC_Bank4->CTRL4_B.MBKEN = BIT_RESET;
}

/*!
 * @brief     Enbles the EMMC NAND ECC feature.
 *
 * @param     bank: Selects the EMMMC Bank.
 *                  The parameter can be one of following values:
 *                  @arg EMMC_BANK2_NAND: FSMC Bank2 NAND
 *                  @arg EMMC_BANK3_NAND: FSMC Bank3 NAND
 *
 * @retval    None
 */
void EMMC_EnableNANDECC(EMMC_BANK_NAND_T bank)
{
    if (bank == EMMC_BANK2_NAND)
    {
        EMMC_Bank2->CTRL2 |= 0x00000040;
    }
    else
    {
        EMMC_Bank3->CTRL3 |= 0x00000040;
    }
}

/*!
 * @brief     Disbles or disables the EMMC NAND ECC feature.
 *
 * @param     bank: Selects the EMMMC Bank.
 *                  The parameter can be one of following values:
 *                  @arg EMMC_BANK2_NAND: FSMC Bank2 NAND
 *                  @arg EMMC_BANK3_NAND: FSMC Bank3 NAND
 *
 * @retval    None
 *
 */
void EMMC_DisableNANDECC(EMMC_BANK_NAND_T bank)
{
    if (bank == EMMC_BANK2_NAND)
    {
        EMMC_Bank2->CTRL2 &= 0x000FFFBF;
    }
    else
    {
        EMMC_Bank3->CTRL3 &= 0x000FFFBF;
    }
}

/*!
 * @brief     Read the error correction code register value.
 *
 * @param     bank: Selects the EMMMC Bank.
 *                  The parameter can be one of following values:
 *                  @arg EMMC_BANK2_NAND: FSMC Bank2 NAND
 *                  @arg EMMC_BANK3_NAND: FSMC Bank3 NAND
 *
 * @retval    The value of Error Correction Code (ECC).
 */
uint32_t  EMMC_ReadECC(EMMC_BANK_NAND_T bank)
{
    uint32_t eccval = 0x00000000;

    if (bank == EMMC_BANK2_NAND)
    {
        eccval = EMMC_Bank2->ECCRS2;
    }
    else
    {
        eccval = EMMC_Bank3->ECCRS3;
    }
    return eccval;
}

/*!
 * @brief    Enables the specified EMMC interrupts.
 *
 * @param    bank: Selects the EMMMC Bank.
 *                 The parameter can be one of following values:
 *                 @arg EMMC_BANK2_NAND  : FSMC Bank2 NAND
 *                 @arg EMMC_BANK3_NAND  : FSMC Bank3 NAND
 *                 @arg EMMC_BANK4_PCCARD: FSMC Bank4 PCCARD
 *
 * @param    interrupt: Select the EMMC interrupt sources.
 *                      This parameter can be any combination of the following values:
 *                      @arg EMMC_INT_EDGE_RISING : Rising edge detection interrupt.
 *                      @arg EMMC_INT_LEVEL_HIGH  : High level detection interrupt.
 *                      @arg EMMC_INT_EDGE_FALLING: Falling edge detection interrupt.
 *
 * @retval   None
 */
void EMMC_EnableInterrupt(EMMC_BANK_NAND_T bank, uint32_t interrupt)
{
    if (bank == EMMC_BANK2_NAND)
    {
        EMMC_Bank2->STSINT2 |= interrupt;
    }
    else if (bank == EMMC_BANK3_NAND)
    {
        EMMC_Bank3->STSINT3 |= interrupt;
    }
    else
    {
        EMMC_Bank4->STSINT4 |= interrupt;
    }
}

/*!
 * @brief    Enables the specified EMMC interrupts.
 *
 * @param    bank: Selects the EMMMC Bank.
 *                 The parameter can be one of following values:
 *                 @arg EMMC_BANK2_NAND  : FSMC Bank2 NAND
 *                 @arg EMMC_BANK3_NAND  : FSMC Bank3 NAND
 *                 @arg EMMC_BANK4_PCCARD: FSMC Bank4 PCCARD
 *
 * @param    interrupt: Select the EMMC interrupt sources.
 *                      This parameter can be any combination of the following values:
 *                      @arg EMMC_INT_EDGE_RISING : Rising edge detection interrupt.
 *                      @arg EMMC_INT_LEVEL_HIGH  : High level edge detection interrupt.
 *                      @arg EMMC_INT_EDGE_FALLING: Falling edge detection interrupt.
 *
 * @retval   None
 */
void EMMC_DisableInterrupt(EMMC_BANK_NAND_T bank, uint32_t interrupt)
{
    if (bank == EMMC_BANK2_NAND)
    {
        EMMC_Bank2->STSINT2 &= ~interrupt;
    }
    else if (bank == EMMC_BANK3_NAND)
    {
        EMMC_Bank3->STSINT3 &= ~interrupt;
    }
    else
    {
        EMMC_Bank4->STSINT4 &= ~interrupt;
    }
}

/*!
 * @brief    Read the status of specified EMMC flag.
 *
 * @param    bank: Selects the EMMMC Bank.
 *                 The parameter can be one of following values:
 *                 @arg EMMC_BANK2_NAND  : FSMC Bank2 NAND
 *                 @arg EMMC_BANK3_NAND  : FSMC Bank3 NAND
 *                 @arg EMMC_BANK4_PCCARD: FSMC Bank4 PCCARD
 *
 * @param    flag: Select the EMMC interrupt sources.
 *                 This parameter can be one of the following values:
 *                 @arg EMMC_FLAG_EDGE_RISING : Rising egde detection Flag.
 *                 @arg EMMC_FLAG_LEVEL_HIGH  : High level detection Flag.
 *                 @arg EMMC_FLAG_EDGE_FALLING: Falling egde detection Flag.
 *                 @arg EMMC_FLAG_FIFO_EMPTY  : FIFO empty Flag.
 *
 * @retval    SET or RESET
 *
 */
uint8_t EMMC_ReadStatusFlag(EMMC_BANK_NAND_T bank, EMMC_FLAG_T flag)
{
    uint32_t tmpsr = 0x00000000;

    if (bank == EMMC_BANK2_NAND)
    {
        tmpsr = EMMC_Bank2->STSINT2;
    }
    else if (bank == EMMC_BANK3_NAND)
    {
        tmpsr = EMMC_Bank3->STSINT3;
    }
    else
    {
        tmpsr = EMMC_Bank4->STSINT4;
    }
    /** Get the flag status */
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
 * @brief    Clears the EMMC's pending flags.
 *
 * @param    bank: Selects the EMMMC Bank.
 *                 The parameter can be one of following values:
 *                 @arg EMMC_BANK2_NAND  : FSMC Bank2 NAND
 *                 @arg EMMC_BANK3_NAND  : FSMC Bank3 NAND
 *                 @arg EMMC_BANK4_PCCARD: FSMC Bank4 PCCARD
 *
 * @param    flag: Select the EMMC interrupt sources.
 *                 This parameter can be any combination of the following values:
 *                 @arg EMMC_FLAG_EDGE_RISING : Rising egde detection Flag.
 *                 @arg EMMC_FLAG_LEVEL_HIGH  : High level detection Flag.
 *                 @arg EMMC_FLAG_EDGE_FALLING: Falling egde detection Flag.
 *
 * @retval    None
 */
void EMMC_ClearStatusFlag(EMMC_BANK_NAND_T bank, uint32_t flag)
{
    if (bank == EMMC_BANK2_NAND)
    {
        EMMC_Bank2->STSINT2 &= ~flag;
    }
    else if (bank == EMMC_BANK3_NAND)
    {
        EMMC_Bank3->STSINT3 &= ~flag;
    }
    else
    {
        EMMC_Bank4->STSINT4 &= ~flag;
    }
}

/*!
 * @brief    Read the specified EMMC interrupt has occurred or not.
 *
 * @param    bank: Selects the EMMMC Bank.
 *                 The parameter can be one of following values:
 *                 @arg EMMC_BANK2_NAND  : FSMC Bank2 NAND
 *                 @arg EMMC_BANK3_NAND  : FSMC Bank3 NAND
 *                 @arg EMMC_BANK4_PCCARD: FSMC Bank4 PCCARD
 *
 * @param    interrupt: Select the EMMC interrupt source.
 *                      This parameter can be one of the following values:
 *                      @arg EMMC_INT_EDGE_RISING : Rising edge detection interrupt.
 *                      @arg EMMC_INT_LEVEL_HIGH  : High level edge detection interrupt.
 *                      @arg EMMC_INT_EDGE_FALLING: Falling edge detection interrupt.
 *
 * @retval   The status of specified EMMC interrupt source.
 */
uint8_t EMMC_ReadIntFlag(EMMC_BANK_NAND_T bank, EMMC_INT_T flag)
{
    uint32_t tmpsr = 0x0, itstatus = 0x0, itenable = 0x0;

    if (bank == EMMC_BANK2_NAND)
    {
        tmpsr = EMMC_Bank2->STSINT2;
    }
    else if (bank == EMMC_BANK3_NAND)
    {
        tmpsr = EMMC_Bank3->STSINT3;
    }
    else
    {
        tmpsr = EMMC_Bank4->STSINT4;
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
 * @brief    Clears the EMMC's interrupt Flag.
 *
 * @param    bank: Selects the EMMMC Bank.
 *                 The parameter can be one of following values:
 *                 @arg EMMC_BANK2_NAND  : FSMC Bank2 NAND
 *                 @arg EMMC_BANK3_NAND  : FSMC Bank3 NAND
 *                 @arg EMMC_BANK4_PCCARD: FSMC Bank4 PCCARD
 *
 * @param    interrupt: Select the EMMC interrupt sources.
 *                      This parameter can be any combination of the following values:
 *                      @arg EMMC_INT_EDGE_RISING : Rising edge detection interrupt.
 *                      @arg EMMC_INT_LEVEL_HIGH  : High level edge detection interrupt.
 *                      @arg EMMC_INT_EDGE_FALLING: Falling edge detection interrupt.
 *
 * @retval   None
 */
void EMMC_ClearIntFlag(EMMC_BANK_NAND_T bank, uint32_t flag)
{
    if (bank == EMMC_BANK2_NAND)
    {
        EMMC_Bank2->STSINT2 &= ~(flag >> 3);
    }
    else if (bank == EMMC_BANK3_NAND)
    {
        EMMC_Bank3->STSINT3 &= ~(flag >> 3);
    }
    else
    {
        EMMC_Bank4->STSINT4 &= ~(flag >> 3);
    }
}

/**@} end of group EMMC_Fuctions*/
/**@} end of group EMMC_Driver*/
/**@} end of group Peripherals_Library*/
