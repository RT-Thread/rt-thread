/*!
 * @file        apm32f10x_smc.h
 *
 * @brief       This file contains all the functions prototypes for the SMC firmware library
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

/* Define to prevent recursive inclusion */
#ifndef __APM32F10X_SMC_H
#define __APM32F10X_SMC_H

/* Includes */
#include "apm32f10x.h"

#ifdef __cplusplus
extern "C" {
#endif

/** @addtogroup APM32F10x_StdPeriphDriver
  @{
*/

/** @addtogroup SMC_Driver SMC Driver
  @{
*/

/** @defgroup SMC_Enumerations Enumerations
  @{
*/

/**
 * @brief SMC NORSRAM_Bank
 */
typedef enum
{
    SMC_BANK1_NORSRAM_1 = 0x00000000,
    SMC_BANK1_NORSRAM_2 = 0x00000002,
    SMC_BANK1_NORSRAM_3 = 0x00000004,
    SMC_BANK1_NORSRAM_4 = 0x00000006
} SMC_BANK1_NORSRAM_T;

/**
 * @brief SMC NAND and PC Card Bank
 */
typedef enum
{
    SMC_BANK2_NAND   = 0x00000010,
    SMC_BANK3_NAND   = 0x00000100,
    SMC_BANK4_PCCARD = 0x00001000
} SMC_BANK_NAND_T;

/**
 * @brief SMC_Data_Address_Bus_Multiplexing
 */
typedef enum
{
    SMC_DATA_ADDRESS_MUX_DISABLE = 0x00000000,
    SMC_DATA_ADDRESS_MUX_ENABLE  = 0x00000002
} SMC_DATA_ADDRESS_MUX_T;

/**
 * @brief SMC_Memory_Type
 */
typedef enum
{
    SMC_MEMORY_TYPE_SRAM  = 0x00000000,
    SMC_MEMORY_TYPE_PSRAM = 0x00000004,
    SMC_MEMORY_TYPE_NOR   = 0x00000008
} SMC_MEMORY_TYPE_T;

/**
 * @brief SMC_Data_Width
 */
typedef enum
{
    SMC_MEMORY_DATA_WIDTH_8BIT  = 0x00000000,
    SMC_MEMORY_DATA_WIDTH_16BIT = 0x00000010
} SMC_MEMORY_DATA_WIDTH_T;

/**
 * @brief SMC_Burst_Access_Mode
 */
typedef enum
{
    SMC_BURST_ACCESS_MODE_DISABLE = 0x00000000,
    SMC_BURST_ACCESS_MODE_ENABLE  = 0x00000100
} SMC_BURST_ACCESS_MODE_T;

/**
 * @brief SMC_AsynchronousWait
 */
typedef enum
{
    SMC_ASYNCHRONOUS_WAIT_DISABLE = 0x00000000,
    SMC_ASYNCHRONOUS_WAIT_ENABLE  = 0x00008000
} SMC_ASYNCHRONOUS_WAIT_T;

/**
 * @brief SMC_Wait_Signal_Polarity
 */
typedef enum
{
    SMC_WAIT_SIGNAL_POLARITY_LOW  = 0x00000000,
    SMC_WAIT_SIGNAL_POLARITY_HIGH = 0x00000200
} SMC_WAIT_SIGNAL_POLARITY_T;

/**
 * @brief SMC_Wrap_Mode
 */
typedef enum
{
    SMC_WRAP_MODE_DISABLE = 0x00000000,
    SMC_WRAP_MODE_ENABLE  = 0x00000400
} SMC_WRAP_MODE_T;

/**
 * @brief SMC_Wait_Timing
 */
typedef enum
{
    SMC_WAIT_SIGNAL_ACTIVE_BEFORE_WAIT = 0x00000000,
    SMC_WAIT_SIGNAL_ACTIVE_DURING_WAIT = 0x00000800
} SMC_WAIT_SIGNAL_ACTIVE_T;

/**
 * @brief SMC_Write_Operation
 */
typedef enum
{
    SMC_WRITE_OPERATION_DISABLE = 0x00000000,
    SMC_WRITE_OPERATION_ENABLE  = 0x00001000
} SMC_WRITE_OPERATION_T;

/**
 * @brief SMC_Wait_Signal
 */
typedef enum
{
    SMC_WAITE_SIGNAL_DISABLE = 0x00000000,
    SMC_WAITE_SIGNAL_ENABLE  = 0x00002000
} SMC_WAITE_SIGNAL_T;

/**
 * @brief SMC_Extended_Mode
 */
typedef enum
{
    SMC_EXTENDEN_MODE_DISABLE = 0x00000000,
    SMC_EXTENDEN_MODE_ENABLE  = 0x00004000
} SMC_EXTENDEN_MODE_T;

/**
 * @brief SMC_Write_Burst
 */
typedef enum
{
    SMC_WRITE_BURST_DISABLE = 0x00000000,
    SMC_WRITE_BURST_ENABLE  = 0x00080000
} SMC_WRITE_BURST_T;

/**
 * @brief   SMC_WAIT_FEATURE
 */
typedef enum
{
    SMC_WAIT_FEATURE_DISABLE = 0x00000000,
    SMC_WAIT_FEATURE_ENABLE  = 0x00000002
} SMC_WAIT_FEATURE_T;

/**
 * @brief SMC_ECC
 */
typedef enum
{
    SMC_ECC_DISABLE = 0x00000000,
    SMC_ECC_ENABLE  = 0x00000040
} SMC_ECC_T;

/**
 * @brief SMC_ECC_Page_Size
 */
typedef enum
{
    SMC_ECC_PAGE_SIZE_BYTE_256  = 0x00000000,
    SMC_ECC_PAGE_SIZE_BYTE_512  = 0x00020000,
    SMC_ECC_PAGE_SIZE_BYTE_1024 = 0x00040000,
    SMC_ECC_PAGE_SIZE_BYTE_2048 = 0x00060000,
    SMC_ECC_PAGE_SIZE_BYTE_4096 = 0x00080000,
    SMC_ECC_PAGE_SIZE_BYTE_8192 = 0x000A0000
} SMC_ECC_PAGE_SIZE_BYTE_T;

/**
 * @brief SMC_Access_Mode
 */
typedef enum
{
    SMC_ACCESS_MODE_A = 0x00000000,
    SMC_ACCESS_MODE_B = 0x10000000,
    SMC_ACCESS_MODE_C = 0x20000000,
    SMC_ACCESS_MODE_D = 0x30000000
} SMC_ACCESS_MODE_T;

/**
 * @brief  SMC_Interrupt_sources
 */
typedef enum
{
    SMC_INT_EDGE_RISING  = 0x00000008,
    SMC_INT_LEVEL_HIGH   = 0x00000010,
    SMC_INT_EDGE_FALLING = 0x00000020
} SMC_INT_T;

/**
 * @brief  SMC_Flags
 */
typedef enum
{
    SMC_FLAG_EDGE_RISING  = 0x00000001,
    SMC_FLAG_LEVEL_HIGH   = 0x00000002,
    SMC_FLAG_EDGE_FALLING = 0x00000004,
    SMC_FLAG_FIFO_EMPTY   = 0x00000040
} SMC_FLAG_T;

/**@} end of group SMC_Enumerations */

/** @defgroup SMC_Structures Structures
  @{
*/

/**
 * @brief Timing parameters for NOR/SRAM Banks
 */
typedef struct
{
    uint32_t           addressSetupTime;
    uint32_t           addressHodeTime;
    uint32_t           dataSetupTime;
    uint32_t           busTurnaroundTime;
    uint32_t           clockDivision;
    uint32_t           dataLatency;
    SMC_ACCESS_MODE_T accessMode;
} SMC_NORSRAMTimingConfig_T;

/**
 * @brief SMC NOR/SRAM Configure structure
 */
typedef struct
{
    SMC_BANK1_NORSRAM_T        bank;
    SMC_DATA_ADDRESS_MUX_T     dataAddressMux;
    SMC_MEMORY_TYPE_T          memoryType;
    SMC_MEMORY_DATA_WIDTH_T    memoryDataWidth;
    SMC_BURST_ACCESS_MODE_T    burstAcceesMode;
    SMC_ASYNCHRONOUS_WAIT_T    asynchronousWait;
    SMC_WAIT_SIGNAL_POLARITY_T waitSignalPolarity;
    SMC_WRAP_MODE_T            wrapMode;
    SMC_WAIT_SIGNAL_ACTIVE_T   waitSignalActive;
    SMC_WRITE_OPERATION_T      writeOperation;
    SMC_WAITE_SIGNAL_T         waiteSignal;
    SMC_EXTENDEN_MODE_T        extendedMode;
    SMC_WRITE_BURST_T          writeBurst;
    SMC_NORSRAMTimingConfig_T*   readWriteTimingStruct;
    SMC_NORSRAMTimingConfig_T*   writeTimingStruct;
} SMC_NORSRAMConfig_T;

/**
 * @brief Timing parameters for NAND and PCCARD Banks
 */
typedef struct
{
    uint32_t setupTime;
    uint32_t waitSetupTime;
    uint32_t holdSetupTime;
    uint32_t HiZSetupTime;
} SMC_NAND_PCCARDTimingConfig_T;

/**
 * @brief SMC NAND Configure structure
 */
typedef struct
{
    SMC_BANK_NAND_T          bank;
    SMC_WAIT_FEATURE_T       waitFeature;
    SMC_MEMORY_DATA_WIDTH_T  memoryDataWidth;
    SMC_ECC_T                ECC;
    SMC_ECC_PAGE_SIZE_BYTE_T ECCPageSize;
    uint32_t                  TCLRSetupTime;
    uint32_t                  TARSetupTime;
    SMC_NAND_PCCARDTimingConfig_T* commonSpaceTimingStruct;
    SMC_NAND_PCCARDTimingConfig_T* attributeSpaceTimingStruct;
} SMC_NANDConfig_T;

/**
 * @brief SMC PCCARD Configure structure
 */
typedef struct
{
    SMC_WAIT_FEATURE_T waitFeature;
    uint32_t            TCLRSetupTime;
    uint32_t            TARSetupTime;
    SMC_NAND_PCCARDTimingConfig_T* commonSpaceTimingStruct;
    SMC_NAND_PCCARDTimingConfig_T* attributeSpaceTimingStruct;
    SMC_NAND_PCCARDTimingConfig_T* IOSpaceTimingStruct;
} SMC_PCCARDConfig_T;

/**@} end of group SMC_Structures */

/** @defgroup SMC_Functions Functions
  @{
*/

/* SMC reset */
void SMC_ResetNORSRAM(SMC_BANK1_NORSRAM_T bank);
void SMC_ResetNAND(SMC_BANK_NAND_T bank);
void SMC_ResetPCCard(void);

/* SMC Configuration */
void SMC_ConfigNORSRAM(SMC_NORSRAMConfig_T* smcNORSRAMConfig);
void SMC_ConfigNAND(SMC_NANDConfig_T* smcNANDConfig);
void SMC_ConfigPCCard(SMC_PCCARDConfig_T* smcPCCardConfig);
void SMC_ConfigNORSRAMStructInit(SMC_NORSRAMConfig_T* smcNORSRAMConfig);
void SMC_ConfigNANDStructInit(SMC_NANDConfig_T* smcNANDConfig);
void SMC_ConfigPCCardStructInit(SMC_PCCARDConfig_T* smcPCCardConfig);

/* SMC bank control */
void SMC_EnableNORSRAM(SMC_BANK1_NORSRAM_T bank);
void SMC_DisableNORSRAM(SMC_BANK1_NORSRAM_T bank);
void SMC_EnableNAND(SMC_BANK_NAND_T bank);
void SMC_DisableNAND(SMC_BANK_NAND_T bank);
void SMC_EnablePCCARD(void);
void SMC_DisablePCCARD(void);
void SMC_EnableNANDECC(SMC_BANK_NAND_T bank);
void SMC_DisableNANDECC(SMC_BANK_NAND_T bank);
uint32_t SMC_ReadECC(SMC_BANK_NAND_T bank);

/* Interrupt and flag */
void SMC_EnableInterrupt(SMC_BANK_NAND_T bank, uint32_t interrupt);
void SMC_DisableInterrupt(SMC_BANK_NAND_T bank, uint32_t interrupt);
uint8_t SMC_ReadStatusFlag(SMC_BANK_NAND_T bank, SMC_FLAG_T flag);
void SMC_ClearStatusFlag(SMC_BANK_NAND_T bank, uint32_t flag);
uint8_t SMC_ReadIntFlag(SMC_BANK_NAND_T bank, SMC_INT_T flag);
void SMC_ClearIntFlag(SMC_BANK_NAND_T bank, uint32_t flag);

/**@} end of group SMC_Functions */
/**@} end of group SMC_Driver */
/**@} end of group APM32F10x_StdPeriphDriver */

#ifdef __cplusplus
}
#endif

#endif /* __APM32F10X_SMC_H */
