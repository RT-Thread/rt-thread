/*!
 * @file        apm32f4xx_smc.c
 *
 * @brief       This file provides all the SMC firmware functions
 *
 * @version     V1.0.2
 *
 * @date        2022-06-23
 *
 * @attention
 *
 *  Copyright (C) 2021-2022 Geehy Semiconductor
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

#include "apm32f4xx_smc.h"
#include "apm32f4xx_rcm.h"

/** @addtogroup APM32F4xx_StdPeriphDriver
  @{
*/

/** @defgroup SMC_Driver
  * @brief SMC driver modules
  @{
*/

/** @defgroup SMC_Functions
  @{
*/

/*!
 * @brief     Rest the SMC NOR/SRAM Banks registers
 *
 * @param     bank: Selects the SMC Bank.
 *                  The parameter can be one of following values:
 *                  @arg SMC_BANK1_NORSRAM_1 : SMC Bank1 NOR/SRAM1
 *                  @arg SMC_BANK1_NORSRAM_2 : SMC Bank1 NOR/SRAM2
 *                  @arg SMC_BANK1_NORSRAM_3 : SMC Bank1 NOR/SRAM3
 *                  @arg SMC_BANK1_NORSRAM_4 : SMC Bank1 NOR/SRAM4
 *
 * @retval    None
 */
void SMC_ResetNORSRAM(SMC_BANK1_NORSRAM_T bank)
{
    if (bank == SMC_BANK1_NORSRAM_1)
    {
        SMC_Bank1->CSCTRL1 = 0x000030DB;
        SMC_Bank1->CSTIM1 = 0x0FFFFFFF;
        SMC_Bank1E->WRTTIM1 = 0x0FFFFFFF;
    }
    else if (bank == SMC_BANK1_NORSRAM_2)
    {
        SMC_Bank1->CSCTRL2 =  0x000030D2;
        SMC_Bank1->CSTIM2 =   0x0FFFFFFF;
        SMC_Bank1E->WRTTIM2 = 0x0FFFFFFF;
    }
    else if (bank == SMC_BANK1_NORSRAM_3)
    {
        SMC_Bank1->CSCTRL3 =  0x000030D2;
        SMC_Bank1->CSTIM3 =   0x0FFFFFFF;
        SMC_Bank1E->WRTTIM3 = 0x0FFFFFFF;
    }
    else if (bank == SMC_BANK1_NORSRAM_4)
    {
        SMC_Bank1->CSCTRL4 =  0x000030D2;
        SMC_Bank1->CSTIM4 =   0x0FFFFFFF;
        SMC_Bank1E->WRTTIM4 = 0x0FFFFFFF;
    }
}

/*!
 * @brief     Rest the SMC NAND Banks registers
 *
 * @param     bank: Selects the SMC Bank.
 *                  The parameter can be one of following values:
 *                  @arg SMC_BANK2_NAND : SMC Bank2 NAND
 *                  @arg SMC_BANK3_NAND : SMC Bank3 NAND
 *
 * @retval    None
 */
void SMC_ResetNAND(SMC_BANK_NAND_T bank)
{
    if (bank == SMC_BANK2_NAND)
    {
        SMC_Bank2->CTRL2 = 0x00000018;
        SMC_Bank2->STSINT2 = 0x00000040;
        SMC_Bank2->CMSTIM2 = 0xFCFCFCFC;
        SMC_Bank2->AMSTIM2 = 0xFCFCFCFC;
    }
    else if (bank == SMC_BANK3_NAND)
    {
        SMC_Bank3->CTRL3 = 0x00000018;
        SMC_Bank3->STSINT3 = 0x00000040;
        SMC_Bank3->CMSTIM3 = 0xFCFCFCFC;
        SMC_Bank3->AMSTIM3 = 0xFCFCFCFC;
    }
}

/*!
 * @brief     Reset the SMC PCCARD Banks registers
 *
 * @param     None
 *
 * @retval    None
 */
void SMC_ResetPCCard(void)
{
    SMC_Bank4->CTRL4 = 0x00000018;
    SMC_Bank4->STSINT4 = 0x00000000;
    SMC_Bank4->CMSTIM4 = 0xFCFCFCFC;
    SMC_Bank4->AMSTIM4 = 0xFCFCFCFC;
    SMC_Bank4->IOSTIM4 = 0xFCFCFCFC;
}

/*!
 * @brief     Config the SMC NOR/SRAM Banks according to the specified parameters in the smcNORSRAMConfig.
 *
 * @param     smcNORSRAMConfig: Point to a SMC_NORSRAMConfig_T structure
 *
 * @retval    None
 */
void SMC_ConfigNORSRAM(SMC_NORSRAMConfig_T* smcNORSRAMConfig)
{
    if (smcNORSRAMConfig->bank == SMC_BANK1_NORSRAM_1)
    {
        SMC_Bank1->CSCTRL1_B.ADMUXEN   = smcNORSRAMConfig->dataAddressMux;
        SMC_Bank1->CSCTRL1_B.MTYPECFG  = smcNORSRAMConfig->memoryType;
        SMC_Bank1->CSCTRL1_B.MDBWIDCFG = smcNORSRAMConfig->memoryDataWidth;
        SMC_Bank1->CSCTRL1_B.BURSTEN = smcNORSRAMConfig->burstAcceesMode;
        SMC_Bank1->CSCTRL1_B.WSASYNCEN = smcNORSRAMConfig->asynchronousWait;
        SMC_Bank1->CSCTRL1_B.WSPOLCFG = smcNORSRAMConfig->waitSignalPolarity;
        SMC_Bank1->CSCTRL1_B.WRAPBEN = smcNORSRAMConfig->wrapMode;
        SMC_Bank1->CSCTRL1_B.WTIMCFG = smcNORSRAMConfig->waitSignalActive;
        SMC_Bank1->CSCTRL1_B.WREN = smcNORSRAMConfig->writeOperation;
        SMC_Bank1->CSCTRL1_B.WAITEN = smcNORSRAMConfig->waiteSignal;
        SMC_Bank1->CSCTRL1_B.EXTMODEEN = smcNORSRAMConfig->extendedMode;
        SMC_Bank1->CSCTRL1_B.WRBURSTEN = smcNORSRAMConfig->writeBurst;

        if (smcNORSRAMConfig->memoryType == SMC_MEMORY_TYPE_NOR)
        {
            SMC_Bank1->CSCTRL1_B.NORFMACCEN = BIT_SET;
        }

        SMC_Bank1->CSTIM1_B.ADDRSETCFG = \
            smcNORSRAMConfig->readWriteTimingStruct->addressSetupTime;
        SMC_Bank1->CSTIM1_B.ADDRHLDCFG = \
            smcNORSRAMConfig->readWriteTimingStruct->addressHodeTime;
        SMC_Bank1->CSTIM1_B.DATASETCFG = \
            smcNORSRAMConfig->readWriteTimingStruct->dataSetupTime;
        SMC_Bank1->CSTIM1_B.BUSTURNCFG = \
            smcNORSRAMConfig->readWriteTimingStruct->busTurnaroundTime;
        SMC_Bank1->CSTIM1_B.CLKDIVCFG = \
            smcNORSRAMConfig->readWriteTimingStruct->clockDivision;
        SMC_Bank1->CSTIM1_B.DATALATCFG = \
            smcNORSRAMConfig->readWriteTimingStruct->dataLatency;
        SMC_Bank1->CSTIM1_B.ASYNCACCCFG = \
            smcNORSRAMConfig->readWriteTimingStruct->accessMode;

        if (smcNORSRAMConfig->extendedMode == SMC_EXTENDEN_MODE_ENABLE)
        {
            SMC_Bank1E->WRTTIM1_B.ADDRSETCFG = \
                smcNORSRAMConfig->writeTimingStruct->addressSetupTime;
            SMC_Bank1E->WRTTIM1_B.ADDRHLDCFG = \
                smcNORSRAMConfig->writeTimingStruct->addressHodeTime;
            SMC_Bank1E->WRTTIM1_B.DATASETCFG = \
                smcNORSRAMConfig->writeTimingStruct->dataSetupTime;
            SMC_Bank1E->WRTTIM1_B.BUSTURNCFG = \
                smcNORSRAMConfig->writeTimingStruct->busTurnaroundTime;
            SMC_Bank1E->WRTTIM1_B.ASYNCACCCFG = \
                smcNORSRAMConfig->writeTimingStruct->accessMode;
        }
        else
        {
            SMC_Bank1E->WRTTIM1 = 0x0FFFFFFF;
        }
    }
    else if (smcNORSRAMConfig->bank == SMC_BANK1_NORSRAM_2)
    {
        SMC_Bank1->CSCTRL2_B.ADMUXEN   = smcNORSRAMConfig->dataAddressMux;
        SMC_Bank1->CSCTRL2_B.MTYPECFG  = smcNORSRAMConfig->memoryType;
        SMC_Bank1->CSCTRL2_B.MDBWIDCFG = smcNORSRAMConfig->memoryDataWidth;
        SMC_Bank1->CSCTRL2_B.BURSTEN = smcNORSRAMConfig->burstAcceesMode;
        SMC_Bank1->CSCTRL2_B.WSASYNCEN = smcNORSRAMConfig->asynchronousWait;
        SMC_Bank1->CSCTRL2_B.WSPOLCFG = smcNORSRAMConfig->waitSignalPolarity;
        SMC_Bank1->CSCTRL2_B.WRAPBEN = smcNORSRAMConfig->wrapMode;
        SMC_Bank1->CSCTRL2_B.WTIMCFG = smcNORSRAMConfig->waitSignalActive;
        SMC_Bank1->CSCTRL2_B.WREN = smcNORSRAMConfig->writeOperation;
        SMC_Bank1->CSCTRL2_B.WAITEN = smcNORSRAMConfig->waiteSignal;
        SMC_Bank1->CSCTRL2_B.EXTMODEEN = smcNORSRAMConfig->extendedMode;
        SMC_Bank1->CSCTRL2_B.WRBURSTEN = smcNORSRAMConfig->writeBurst;

        if (smcNORSRAMConfig->memoryType == SMC_MEMORY_TYPE_NOR)
        {
            SMC_Bank1->CSCTRL2_B.NORFMACCEN = BIT_SET;
        }

        SMC_Bank1->CSTIM2_B.ADDRSETCFG = \
            smcNORSRAMConfig->readWriteTimingStruct->addressSetupTime;
        SMC_Bank1->CSTIM2_B.ADDRHLDCFG = \
            smcNORSRAMConfig->readWriteTimingStruct->addressHodeTime;
        SMC_Bank1->CSTIM2_B.DATASETCFG = \
            smcNORSRAMConfig->readWriteTimingStruct->dataSetupTime;
        SMC_Bank1->CSTIM2_B.BUSTURNCFG = \
            smcNORSRAMConfig->readWriteTimingStruct->busTurnaroundTime;
        SMC_Bank1->CSTIM2_B.CLKDIVCFG = \
            smcNORSRAMConfig->readWriteTimingStruct->clockDivision;
        SMC_Bank1->CSTIM2_B.DATALATCFG = \
            smcNORSRAMConfig->readWriteTimingStruct->dataLatency;
        SMC_Bank1->CSTIM2_B.ASYNCACCCFG = \
            smcNORSRAMConfig->readWriteTimingStruct->accessMode;

        if (smcNORSRAMConfig->extendedMode == SMC_EXTENDEN_MODE_ENABLE)
        {
            SMC_Bank1E->WRTTIM2_B.ADDRSETCFG = \
                smcNORSRAMConfig->writeTimingStruct->addressSetupTime;
            SMC_Bank1E->WRTTIM2_B.ADDRHLDCFG = \
                smcNORSRAMConfig->writeTimingStruct->addressHodeTime;
            SMC_Bank1E->WRTTIM2_B.DATASETCFG = \
                smcNORSRAMConfig->writeTimingStruct->dataSetupTime;
            SMC_Bank1E->WRTTIM2_B.BUSTURNCFG = \
                smcNORSRAMConfig->writeTimingStruct->busTurnaroundTime;
            SMC_Bank1E->WRTTIM2_B.ASYNCACCCFG = \
                smcNORSRAMConfig->writeTimingStruct->accessMode;
        }
        else
        {
            SMC_Bank1E->WRTTIM2 = 0x0FFFFFFF;
        }
    }
    else if (smcNORSRAMConfig->bank == SMC_BANK1_NORSRAM_3)
    {
        SMC_Bank1->CSCTRL3_B.ADMUXEN   = smcNORSRAMConfig->dataAddressMux;
        SMC_Bank1->CSCTRL3_B.MTYPECFG  = smcNORSRAMConfig->memoryType;
        SMC_Bank1->CSCTRL3_B.MDBWIDCFG = smcNORSRAMConfig->memoryDataWidth;
        SMC_Bank1->CSCTRL3_B.BURSTEN = smcNORSRAMConfig->burstAcceesMode;
        SMC_Bank1->CSCTRL3_B.WSASYNCEN = smcNORSRAMConfig->asynchronousWait;
        SMC_Bank1->CSCTRL3_B.WSPOLCFG = smcNORSRAMConfig->waitSignalPolarity;
        SMC_Bank1->CSCTRL3_B.WRAPBEN = smcNORSRAMConfig->wrapMode;
        SMC_Bank1->CSCTRL3_B.WTIMCFG = smcNORSRAMConfig->waitSignalActive;
        SMC_Bank1->CSCTRL3_B.WREN = smcNORSRAMConfig->writeOperation;
        SMC_Bank1->CSCTRL3_B.WAITEN = smcNORSRAMConfig->waiteSignal;
        SMC_Bank1->CSCTRL3_B.EXTMODEEN = smcNORSRAMConfig->extendedMode;
        SMC_Bank1->CSCTRL3_B.WRBURSTEN = smcNORSRAMConfig->writeBurst;

        if (smcNORSRAMConfig->memoryType == SMC_MEMORY_TYPE_NOR)
        {
            SMC_Bank1->CSCTRL3_B.NORFMACCEN = BIT_SET;
        }

        SMC_Bank1->CSTIM3_B.ADDRSETCFG = \
            smcNORSRAMConfig->readWriteTimingStruct->addressSetupTime;
        SMC_Bank1->CSTIM3_B.ADDRHLDCFG = \
            smcNORSRAMConfig->readWriteTimingStruct->addressHodeTime;
        SMC_Bank1->CSTIM3_B.DATASETCFG = \
            smcNORSRAMConfig->readWriteTimingStruct->dataSetupTime;
        SMC_Bank1->CSTIM3_B.BUSTURNCFG = \
            smcNORSRAMConfig->readWriteTimingStruct->busTurnaroundTime;
        SMC_Bank1->CSTIM3_B.CLKDIVCFG = \
            smcNORSRAMConfig->readWriteTimingStruct->clockDivision;
        SMC_Bank1->CSTIM3_B.DATALATCFG = \
            smcNORSRAMConfig->readWriteTimingStruct->dataLatency;
        SMC_Bank1->CSTIM3_B.ASYNCACCCFG = \
            smcNORSRAMConfig->readWriteTimingStruct->accessMode;

        if (smcNORSRAMConfig->extendedMode == SMC_EXTENDEN_MODE_ENABLE)
        {
            SMC_Bank1E->WRTTIM3_B.ADDRSETCFG = \
                smcNORSRAMConfig->writeTimingStruct->addressSetupTime;
            SMC_Bank1E->WRTTIM3_B.ADDRHLDCFG = \
                smcNORSRAMConfig->writeTimingStruct->addressHodeTime;
            SMC_Bank1E->WRTTIM3_B.DATASETCFG = \
                smcNORSRAMConfig->writeTimingStruct->dataSetupTime;
            SMC_Bank1E->WRTTIM3_B.BUSTURNCFG = \
                smcNORSRAMConfig->writeTimingStruct->busTurnaroundTime;
            SMC_Bank1E->WRTTIM3_B.ASYNCACCCFG = \
                smcNORSRAMConfig->writeTimingStruct->accessMode;
        }
        else
        {
            SMC_Bank1E->WRTTIM3 = 0x0FFFFFFF;
        }
    }
    else if (smcNORSRAMConfig->bank == SMC_BANK1_NORSRAM_4)
    {
        SMC_Bank1->CSCTRL4_B.ADMUXEN   = smcNORSRAMConfig->dataAddressMux;
        SMC_Bank1->CSCTRL4_B.MTYPECFG  = smcNORSRAMConfig->memoryType;
        SMC_Bank1->CSCTRL4_B.MDBWIDCFG = smcNORSRAMConfig->memoryDataWidth;
        SMC_Bank1->CSCTRL4_B.BURSTEN = smcNORSRAMConfig->burstAcceesMode;
        SMC_Bank1->CSCTRL4_B.WSASYNCEN = smcNORSRAMConfig->asynchronousWait;
        SMC_Bank1->CSCTRL4_B.WSPOLCFG = smcNORSRAMConfig->waitSignalPolarity;
        SMC_Bank1->CSCTRL4_B.WRAPBEN = smcNORSRAMConfig->wrapMode;
        SMC_Bank1->CSCTRL4_B.WTIMCFG = smcNORSRAMConfig->waitSignalActive;
        SMC_Bank1->CSCTRL4_B.WREN = smcNORSRAMConfig->writeOperation;
        SMC_Bank1->CSCTRL4_B.WAITEN = smcNORSRAMConfig->waiteSignal;
        SMC_Bank1->CSCTRL4_B.EXTMODEEN = smcNORSRAMConfig->extendedMode;
        SMC_Bank1->CSCTRL4_B.WRBURSTEN = smcNORSRAMConfig->writeBurst;

        if (smcNORSRAMConfig->memoryType == SMC_MEMORY_TYPE_NOR)
        {
            SMC_Bank1->CSCTRL4_B.NORFMACCEN = BIT_SET;
        }

        SMC_Bank1->CSTIM4_B.ADDRSETCFG = \
            smcNORSRAMConfig->readWriteTimingStruct->addressSetupTime;
        SMC_Bank1->CSTIM4_B.ADDRHLDCFG = \
            smcNORSRAMConfig->readWriteTimingStruct->addressHodeTime;
        SMC_Bank1->CSTIM4_B.DATASETCFG = \
            smcNORSRAMConfig->readWriteTimingStruct->dataSetupTime;
        SMC_Bank1->CSTIM4_B.BUSTURNCFG = \
            smcNORSRAMConfig->readWriteTimingStruct->busTurnaroundTime;
        SMC_Bank1->CSTIM4_B.CLKDIVCFG = \
            smcNORSRAMConfig->readWriteTimingStruct->clockDivision;
        SMC_Bank1->CSTIM4_B.DATALATCFG = \
            smcNORSRAMConfig->readWriteTimingStruct->dataLatency;
        SMC_Bank1->CSTIM4_B.ASYNCACCCFG = \
            smcNORSRAMConfig->readWriteTimingStruct->accessMode;

        if (smcNORSRAMConfig->extendedMode == SMC_EXTENDEN_MODE_ENABLE)
        {
            SMC_Bank1E->WRTTIM4_B.ADDRSETCFG = \
                smcNORSRAMConfig->writeTimingStruct->addressSetupTime;
            SMC_Bank1E->WRTTIM4_B.ADDRHLDCFG = \
                smcNORSRAMConfig->writeTimingStruct->addressHodeTime;
            SMC_Bank1E->WRTTIM4_B.DATASETCFG = \
                smcNORSRAMConfig->writeTimingStruct->dataSetupTime;
            SMC_Bank1E->WRTTIM4_B.BUSTURNCFG = \
                smcNORSRAMConfig->writeTimingStruct->busTurnaroundTime;
            SMC_Bank1E->WRTTIM4_B.ASYNCACCCFG = \
                smcNORSRAMConfig->writeTimingStruct->accessMode;
        }
        else
        {
            SMC_Bank1E->WRTTIM4 = 0x0FFFFFFF;
        }
    }
}

/*!
 * @brief     Config the SMC NAND Banks according to the specified parameters in the smcNANDConfig.
 *
 * @param     smcNANDConfig : Point to a SMC_NANDConfig_T structure.
 *
 * @retval    None
 */
void SMC_ConfigNAND(SMC_NANDConfig_T* smcNANDConfig)
{
    if (smcNANDConfig->bank == SMC_BANK2_NAND)
    {
        SMC_Bank2->CTRL2_B.WAITFEN = smcNANDConfig->waitFeature;
        SMC_Bank2->CTRL2_B.DBWIDCFG = smcNANDConfig->memoryDataWidth;
        SMC_Bank2->CTRL2_B.ECCEN = smcNANDConfig->ECC;
        SMC_Bank2->CTRL2_B.ECCPSCFG = smcNANDConfig->ECCPageSize;
        SMC_Bank2->CTRL2_B.C2RDCFG = smcNANDConfig->TCLRSetupTime;
        SMC_Bank2->CTRL2_B.A2RDCFG = smcNANDConfig->TARSetupTime;
        SMC_Bank2->CTRL2_B.MTYPECFG = BIT_SET;

        SMC_Bank2->CMSTIM2_B.SET2 = \
            smcNANDConfig->commonSpaceTimingStruct->setupTime;
        SMC_Bank2->CMSTIM2_B.WAIT2 = \
            smcNANDConfig->commonSpaceTimingStruct->waitSetupTime;
        SMC_Bank2->CMSTIM2_B.HLD2 = \
            smcNANDConfig->commonSpaceTimingStruct->holdSetupTime;
        SMC_Bank2->CMSTIM2_B.HIZ2 = \
            smcNANDConfig->commonSpaceTimingStruct->HiZSetupTime;

        SMC_Bank2->AMSTIM2_B.SET2 = \
            smcNANDConfig->attributeSpaceTimingStruct->setupTime;
        SMC_Bank2->AMSTIM2_B.WAIT2 = \
            smcNANDConfig->attributeSpaceTimingStruct->waitSetupTime;
        SMC_Bank2->AMSTIM2_B.HLD2 = \
            smcNANDConfig->attributeSpaceTimingStruct->holdSetupTime;
        SMC_Bank2->AMSTIM2_B.HIZ2 = \
            smcNANDConfig->attributeSpaceTimingStruct->HiZSetupTime;
    }
    else if (smcNANDConfig->bank == SMC_BANK3_NAND)
    {
        SMC_Bank3->CTRL3_B.WAITFEN = smcNANDConfig->waitFeature;
        SMC_Bank3->CTRL3_B.DBWIDCFG = smcNANDConfig->memoryDataWidth;
        SMC_Bank3->CTRL3_B.ECCEN = smcNANDConfig->ECC;
        SMC_Bank3->CTRL3_B.ECCPSCFG = smcNANDConfig->ECCPageSize;
        SMC_Bank3->CTRL3_B.C2RDCFG = smcNANDConfig->TCLRSetupTime;
        SMC_Bank3->CTRL3_B.A2RDCFG = smcNANDConfig->TARSetupTime;
        SMC_Bank3->CTRL3_B.MTYPECFG = BIT_SET;

        SMC_Bank3->CMSTIM3_B.SET3 = \
            smcNANDConfig->commonSpaceTimingStruct->setupTime;
        SMC_Bank3->CMSTIM3_B.WAIT3 = \
            smcNANDConfig->commonSpaceTimingStruct->waitSetupTime;
        SMC_Bank3->CMSTIM3_B.HLD3 = \
            smcNANDConfig->commonSpaceTimingStruct->holdSetupTime;
        SMC_Bank3->CMSTIM3_B.HIZ3 = \
            smcNANDConfig->commonSpaceTimingStruct->HiZSetupTime;

        SMC_Bank3->AMSTIM3_B.SET3 = \
            smcNANDConfig->attributeSpaceTimingStruct->setupTime;
        SMC_Bank3->AMSTIM3_B.WAIT3 = \
            smcNANDConfig->attributeSpaceTimingStruct->waitSetupTime;
        SMC_Bank3->AMSTIM3_B.HLD3 = \
            smcNANDConfig->attributeSpaceTimingStruct->holdSetupTime;
        SMC_Bank3->AMSTIM3_B.HIZ3 = \
            smcNANDConfig->attributeSpaceTimingStruct->HiZSetupTime;
    }
}

/*!
 * @brief     Config the SMC PCCARD according to the specified parameters in the smcPCCardConfig.
 *
 * @param     smcPCCardConfig: Point to a SMC_PCCARDConfig_T structure.
 *
 * @retval    None
 */
void SMC_ConfigPCCard(SMC_PCCARDConfig_T* smcPCCardConfig)
{
    SMC_Bank4->CTRL4_B.WAITFEN = smcPCCardConfig->waitFeature;
    SMC_Bank4->CTRL4_B.C2RDCFG = smcPCCardConfig->TCLRSetupTime;
    SMC_Bank4->CTRL4_B.A2RDCFG = smcPCCardConfig->TARSetupTime;
    SMC_Bank4->CTRL4_B.DBWIDCFG = BIT_SET;

    SMC_Bank4->CMSTIM4_B.SET4 = \
        smcPCCardConfig->commonSpaceTimingStruct->setupTime;
    SMC_Bank4->CMSTIM4_B.WAIT4 = \
        smcPCCardConfig->commonSpaceTimingStruct->waitSetupTime;
    SMC_Bank4->CMSTIM4_B.HLD4 = \
        smcPCCardConfig->commonSpaceTimingStruct->holdSetupTime;
    SMC_Bank4->CMSTIM4_B.HIZ4 = \
        smcPCCardConfig->commonSpaceTimingStruct->HiZSetupTime;

    SMC_Bank4->AMSTIM4_B.SET4 = \
        smcPCCardConfig->attributeSpaceTimingStruct->setupTime;
    SMC_Bank4->AMSTIM4_B.WAIT4 = \
        smcPCCardConfig->attributeSpaceTimingStruct->waitSetupTime;
    SMC_Bank4->AMSTIM4_B.HLD4 = \
        smcPCCardConfig->attributeSpaceTimingStruct->holdSetupTime;
    SMC_Bank4->AMSTIM4_B.HIZ4 = \
        smcPCCardConfig->attributeSpaceTimingStruct->HiZSetupTime;

    SMC_Bank4->IOSTIM4_B.SET = \
        smcPCCardConfig->IOSpaceTimingStruct->setupTime;
    SMC_Bank4->IOSTIM4_B.WAIT = \
        smcPCCardConfig->IOSpaceTimingStruct->waitSetupTime;
    SMC_Bank4->IOSTIM4_B.HLD = \
        smcPCCardConfig->IOSpaceTimingStruct->holdSetupTime;
    SMC_Bank4->IOSTIM4_B.HIZ = \
        smcPCCardConfig->IOSpaceTimingStruct->HiZSetupTime;
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
    smcNORSRAMConfig->bank = SMC_BANK1_NORSRAM_1;
    smcNORSRAMConfig->dataAddressMux = SMC_DATA_ADDRESS_MUX_ENABLE;
    smcNORSRAMConfig->memoryType = SMC_MEMORY_TYPE_SRAM;
    smcNORSRAMConfig->memoryDataWidth = SMC_MEMORY_DATA_WIDTH_8BIT;
    smcNORSRAMConfig->burstAcceesMode = SMC_BURST_ACCESS_MODE_DISABLE;
    smcNORSRAMConfig->asynchronousWait = SMC_ASYNCHRONOUS_WAIT_DISABLE;
    smcNORSRAMConfig->waitSignalPolarity = SMC_WAIT_SIGNAL_POLARITY_LOW;
    smcNORSRAMConfig->wrapMode = SMC_WRAP_MODE_DISABLE;
    smcNORSRAMConfig->waitSignalActive = SMC_WAIT_SIGNAL_ACTIVE_BEFORE_WAIT_STATE;
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
 * @brief     Enables the specified NOR/SRAM Memory Bank.
 *
 * @param     bank: Selects the SMC Bank.
 *                  The parameter can be one of following values:
 *                  @arg SMC_BANK1_NORSRAM_1 : SMC Bank1 NOR/SRAM1
 *                  @arg SMC_BANK1_NORSRAM_2 : SMC Bank1 NOR/SRAM2
 *                  @arg SMC_BANK1_NORSRAM_3 : SMC Bank1 NOR/SRAM3
 *                  @arg SMC_BANK1_NORSRAM_4 : SMC Bank1 NOR/SRAM4
 *
 * @retval    None
 */
void SMC_EnableNORSRAM(SMC_BANK1_NORSRAM_T bank)
{
    if (bank == SMC_BANK1_NORSRAM_1)
    {
        SMC_Bank1->CSCTRL1_B.MBKEN = BIT_SET;
    }
    else if (bank == SMC_BANK1_NORSRAM_2)
    {
        SMC_Bank1->CSCTRL2_B.MBKEN = BIT_SET;
    }
    else if (bank == SMC_BANK1_NORSRAM_3)
    {
        SMC_Bank1->CSCTRL3_B.MBKEN = BIT_SET;
    }
    else if (bank == SMC_BANK1_NORSRAM_4)
    {
        SMC_Bank1->CSCTRL4_B.MBKEN = BIT_SET;
    }
}

/*!
 * @brief     Disbles the specified NOR/SRAM Memory Bank.
 *
 * @param     bank: Selects the SMC Bank.
 *                  The parameter can be one of following values:
 *                  @arg SMC_BANK1_NORSRAM_1 : SMC Bank1 NOR/SRAM1
 *                  @arg SMC_BANK1_NORSRAM_2 : SMC Bank1 NOR/SRAM2
 *                  @arg SMC_BANK1_NORSRAM_3 : SMC Bank1 NOR/SRAM3
 *                  @arg SMC_BANK1_NORSRAM_4 : SMC Bank1 NOR/SRAM4
 *
 * @retval    None
 */
void SMC_DisableNORSRAM(SMC_BANK1_NORSRAM_T bank)
{
    if (bank == SMC_BANK1_NORSRAM_1)
    {
        SMC_Bank1->CSCTRL1_B.MBKEN = BIT_RESET;
    }
    else if (bank == SMC_BANK1_NORSRAM_2)
    {
        SMC_Bank1->CSCTRL2_B.MBKEN = BIT_RESET;
    }
    else if (bank == SMC_BANK1_NORSRAM_3)
    {
        SMC_Bank1->CSCTRL3_B.MBKEN = BIT_RESET;
    }
    else if (bank == SMC_BANK1_NORSRAM_4)
    {
        SMC_Bank1->CSCTRL4_B.MBKEN = BIT_RESET;
    }
}

/*!
 * @brief     Enables the specified NAND Memory Bank.
 *
 * @param     bank: Selects the SMC Bank.
 *                  The parameter can be one of following values:
 *                  @arg SMC_BANK2_NAND : SMC Bank2 NAND
 *                  @arg SMC_BANK3_NAND : SMC Bank3 NAND
 *
 * @retval    None
 */
void SMC_EnableNAND(SMC_BANK_NAND_T bank)
{
    if (bank == SMC_BANK2_NAND)
    {
        SMC_Bank2->CTRL2_B.MBKEN = BIT_SET;
    }
    else if (bank == SMC_BANK3_NAND)
    {
        SMC_Bank3->CTRL3_B.MBKEN = BIT_SET;
    }
}

/*!
 * @brief     Disbles the specified NAND Memory Bank.
 *
 * @param     bank: Selects the SMC Bank.
 *                  The parameter can be one of following values:
 *                  @arg SMC_BANK2_NAND : SMC Bank2 NAND
 *                  @arg SMC_BANK3_NAND : SMC Bank3 NAND
 *
 * @retval    None
 */
void SMC_DisableNAND(SMC_BANK_NAND_T bank)
{
    if (bank == SMC_BANK2_NAND)
    {
        SMC_Bank2->CTRL2_B.MBKEN = BIT_RESET;
    }
    else if (bank == SMC_BANK3_NAND)
    {
        SMC_Bank3->CTRL3_B.MBKEN = BIT_RESET;
    }
}

/*!
 * @brief     Enables the specified PC Card Memory Bank.
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
 * @brief     Disables the specified PC Card Memory Bank.
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
 * @brief     Enbles the SMC NAND ECC feature.
 *
 * @param     bank: Selects the SMC Bank.
 *                  The parameter can be one of following values:
 *                  @arg SMC_BANK2_NAND : SMC Bank2 NAND
 *                  @arg SMC_BANK3_NAND : SMC Bank3 NAND
 *
 * @retval    None
 */
void SMC_EnableNANDECC(SMC_BANK_NAND_T bank)
{
    if (bank == SMC_BANK2_NAND)
    {
        SMC_Bank2->CTRL2_B.ECCEN = BIT_SET;
    }
    else if (bank == SMC_BANK3_NAND)
    {
        SMC_Bank3->CTRL3_B.ECCEN = BIT_SET;
    }
}

/*!
 * @brief     Disbles or disables the SMC NAND ECC feature.
 *
 * @param     bank: Selects the SMC Bank.
 *                  The parameter can be one of following values:
 *                  @arg SMC_BANK2_NAND : SMC Bank2 NAND
 *                  @arg SMC_BANK3_NAND : SMC Bank3 NAND
 *
 * @retval    None
 *
 * @note
 */
void SMC_DisableNANDECC(SMC_BANK_NAND_T bank)
{
    if (bank == SMC_BANK2_NAND)
    {
        SMC_Bank2->CTRL2_B.ECCEN = BIT_RESET;
    }
    else if (bank == SMC_BANK3_NAND)
    {
        SMC_Bank3->CTRL3_B.ECCEN = BIT_RESET;
    }
}

/*!
 * @brief     Read the error correction code register value.
 *
 * @param     bank: Selects the SMC Bank.
 *                  The parameter can be one of following values:
 *                  @arg SMC_BANK2_NAND : SMC Bank2 NAND
 *                  @arg SMC_BANK3_NAND : SMC Bank3 NAND
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
    else if (bank == SMC_BANK3_NAND)
    {
        eccval = SMC_Bank3->ECCRS3;
    }

    return eccval;
}

/*!
 * @brief    Enables the specified SMC interrupts.
 *
 * @param    bank: Selects the SMC Bank.
 *                 The parameter can be one of following values:
 *                 @arg SMC_BANK2_NAND   : SMC Bank2 NAND
 *                 @arg SMC_BANK3_NAND   : SMC Bank3 NAND
 *                 @arg SMC_BANK4_PCCARD : SMC Bank4 PCCARD
 *
 * @param    interrupt: Select the SMC interrupt sources.
 *                      This parameter can be any combination of the following values:
 *                      @arg SMC_INT_EDGE_RISING  : Rising edge detection interrupt.
 *                      @arg SMC_INT_LEVEL_HIGH   : High level detection interrupt.
 *                      @arg SMC_INT_EDGE_FALLING : Falling edge detection interrupt.
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
 * @brief    Enables the specified SMC interrupts.
 *
 * @param    bank: Selects the SMC Bank.
 *                 The parameter can be one of following values:
 *                 @arg SMC_BANK2_NAND   : SMC Bank2 NAND
 *                 @arg SMC_BANK3_NAND   : SMC Bank3 NAND
 *                 @arg SMC_BANK4_PCCARD : SMC Bank4 PCCARD
 *
 * @param    interrupt: Select the SMC interrupt sources.
 *                      This parameter can be any combination of the following values:
 *                      @arg SMC_INT_EDGE_RISING  : Rising edge detection interrupt.
 *                      @arg SMC_INT_LEVEL_HIGH   : High level edge detection interrupt.
 *                      @arg SMC_INT_EDGE_FALLING : Falling edge detection interrupt.
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
 * @brief     Read the status of specified SMC flag.
 *
 * @param    bank: Selects the SMC Bank.
 *                 The parameter can be one of following values:
 *                 @arg SMC_BANK2_NAND   : SMC Bank2 NAND
 *                 @arg SMC_BANK3_NAND   : SMC Bank3 NAND
 *                 @arg SMC_BANK4_PCCARD : SMC Bank4 PCCARD
 *
 * @param    flag: Select the SMC interrupt sources.
 *                 This parameter can be one of the following values:
 *                 @arg SMC_FLAG_EDGE_RISING  : Rising egde detection Flag.
 *                 @arg SMC_FLAG_LEVEL_HIGH   : High level detection Flag.
 *                 @arg SMC_FLAG_EDGE_FALLING : Falling egde detection Flag.
 *                 @arg SMC_FLAG_FIFO_EMPTY   : FIFO empty Flag.
 *
 * @retval    SET or RESET
 *
 * @note
 */
uint16_t SMC_ReadStatusFlag(SMC_BANK_NAND_T bank, SMC_FLAG_T flag)
{
    if (bank == SMC_BANK2_NAND)
    {
        return (SMC_Bank2->STSINT2 & flag) ? SET : RESET;
    }
    else if (bank == SMC_BANK3_NAND)
    {
        return (SMC_Bank3->STSINT3 & flag) ? SET : RESET;
    }
    else
    {
        return (SMC_Bank4->STSINT4 & flag) ? SET : RESET;
    }
}

/*!
 * @brief     Clears the SMC's pending flags.
 *
 * @param    bank: Selects the SMC Bank.
 *                 The parameter can be one of following values:
 *                 @arg SMC_BANK2_NAND   : SMC Bank2 NAND
 *                 @arg SMC_BANK3_NAND   : SMC Bank3 NAND
 *                 @arg SMC_BANK4_PCCARD : SMC Bank4 PCCARD
 *
 * @param    flag: Select the SMC interrupt sources.
 *                 This parameter can be any combination of the following values:
 *                 @arg SMC_FLAG_EDGE_RISING  : Rising egde detection Flag.
 *                 @arg SMC_FLAG_LEVEL_HIGH   : High level detection Flag.
 *                 @arg SMC_FLAG_EDGE_FALLING : Falling egde detection Flag.
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
 * @param    bank: Selects the SMC Bank.
 *                 The parameter can be one of following values:
 *                 @arg SMC_BANK2_NAND   : SMC Bank2 NAND
 *                 @arg SMC_BANK3_NAND   : SMC Bank3 NAND
 *                 @arg SMC_BANK4_PCCARD : SMC Bank4 PCCARD
 *
 * @param    flag: Select the SMC interrupt source.
 *                 This parameter can be one of the following values:
 *                 @arg SMC_INT_EDGE_RISING  : Rising edge detection interrupt.
 *                 @arg SMC_INT_LEVEL_HIGH   : High level edge detection interrupt.
 *                 @arg SMC_INT_EDGE_FALLING : Falling edge detection interrupt.
 *
 * @retval   The status of specified SMC interrupt source.
 */
uint16_t  SMC_ReadIntFlag(SMC_BANK_NAND_T bank, SMC_INT_T flag)
{
    uint32_t tmpStatus = 0x0, itstatus = 0x0, itenable = 0x0;

    if (bank == SMC_BANK2_NAND)
    {
        tmpStatus = SMC_Bank2->STSINT2;
    }
    else if (bank == SMC_BANK3_NAND)
    {
        tmpStatus = SMC_Bank3->STSINT3;
    }
    else
    {
        tmpStatus = SMC_Bank4->STSINT4;
    }

    itstatus = tmpStatus & flag;
    itenable = tmpStatus & (flag >> 3);

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
 * @brief    Clears the SMC's interrupt Flag.
 *
 * @param    bank: Selects the SMC Bank.
 *                 The parameter can be one of following values:
 *                 @arg SMC_BANK2_NAND   : SMC Bank2 NAND
 *                 @arg SMC_BANK3_NAND   : SMC Bank3 NAND
 *                 @arg SMC_BANK4_PCCARD : SMC Bank4 PCCARD
 *
 * @param    interrupt: Select the SMC interrupt sources.
 *                      This parameter can be any combination of the following values:
 *                      @arg SMC_INT_EDGE_RISING  : Rising edge detection interrupt.
 *                      @arg SMC_INT_LEVEL_HIGH   : High level edge detection interrupt.
 *                      @arg SMC_INT_EDGE_FALLING : Falling edge detection interrupt.
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
/**@} end of group APM32F4xx_StdPeriphDriver */
