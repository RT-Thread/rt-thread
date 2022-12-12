/*!
 * @file        apm32f10x_emmc.h
 *
 * @brief       This file contains all the functions prototypes for the EMMC firmware library
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

#ifndef __APM32F10X_EMMC_H
#define __APM32F10X_EMMC_H

#ifdef __cplusplus
  extern "C" {
#endif

#include "apm32f10x.h"

/** @addtogroup Peripherals_Library Standard Peripheral Library
  @{
*/

/** @addtogroup EMMC_Driver EMMC Driver
  @{
*/

/** @addtogroup EMMC_Enumerations Enumerations
  @{
*/

/**
 * @brief EMMC NORSRAM_Bank
 */
typedef enum
{
    EMMC_BANK1_NORSRAM_1 = 0x00000000,
    EMMC_BANK1_NORSRAM_2 = 0x00000002,
    EMMC_BANK1_NORSRAM_3 = 0x00000004,
    EMMC_BANK1_NORSRAM_4 = 0x00000006
} EMMC_BANK1_NORSRAM_T;

/**
 * @brief EMMC NAND and PC Card Bank
 */
typedef enum
{
    EMMC_BANK2_NAND   = 0x00000010,
    EMMC_BANK3_NAND   = 0x00000100,
    EMMC_BANK4_PCCARD = 0x00001000
} EMMC_BANK_NAND_T;

/**
 * @brief EMMC_Data_Address_Bus_Multiplexing
 */
typedef enum
{
    EMMC_DATA_ADDRESS_MUX_DISABLE = 0x00000000,
    EMMC_DATA_ADDRESS_MUX_ENABLE  = 0x00000002
} EMMC_DATA_ADDRESS_MUX_T;

/**
 * @brief EMMC_Memory_Type
 */
typedef enum
{
    EMMC_MEMORY_TYPE_SRAM  = 0x00000000,
    EMMC_MEMORY_TYPE_PSRAM = 0x00000004,
    EMMC_MEMORY_TYPE_NOR   = 0x00000008
} EMMC_MEMORY_TYPE_T;

/**
 * @brief EMMC_Data_Width
 */
typedef enum
{
    EMMC_MEMORY_DATA_WIDTH_8BIT  = 0x00000000,
    EMMC_MEMORY_DATA_WIDTH_16BIT = 0x00000010
} EMMC_MEMORY_DATA_WIDTH_T;

/**
 * @brief EMMC_Burst_Access_Mode
 */
typedef enum
{
    EMMC_BURST_ACCESS_MODE_DISABLE = 0x00000000,
    EMMC_BURST_ACCESS_MODE_ENABLE  = 0x00000100
} EMMC_BURST_ACCESS_MODE_T;

/**
 * @brief EMMC_AsynchronousWait
 */
typedef enum
{
    EMMC_ASYNCHRONOUS_WAIT_DISABLE = 0x00000000,
    EMMC_ASYNCHRONOUS_WAIT_ENABLE  = 0x00008000
} EMMC_ASYNCHRONOUS_WAIT_T;

/**
 * @brief EMMC_Wait_Signal_Polarity
 */
typedef enum
{
    EMMC_WAIT_SIGNAL_POLARITY_LOW  = 0x00000000,
    EMMC_WAIT_SIGNAL_POLARITY_HIGH = 0x00000200
} EMMC_WAIT_SIGNAL_POLARITY_T;

/**
 * @brief EMMC_Wrap_Mode
 */
typedef enum
{
    EMMC_WRAP_MODE_DISABLE = 0x00000000,
    EMMC_WRAP_MODE_ENABLE  = 0x00000400
} EMMC_WRAP_MODE_T;

/**
 * @brief EMMC_Wait_Timing
 */
typedef enum
{
    EMMC_WAIT_SIGNAL_ACTIVE_BEFORE_WAIT = 0x00000000,
    EMMC_WAIT_SIGNAL_ACTIVE_DURING_WAIT = 0x00000800
} EMMC_WAIT_SIGNAL_ACTIVE_T;

/**
 * @brief EMMC_Write_Operation
 */
typedef enum
{
    EMMC_WRITE_OPERATION_DISABLE = 0x00000000,
    EMMC_WRITE_OPERATION_ENABLE  = 0x00001000
} EMMC_WRITE_OPERATION_T;

/**
 * @brief EMMC_Wait_Signal
 */
typedef enum
{
    EMMC_WAITE_SIGNAL_DISABLE = 0x00000000,
    EMMC_WAITE_SIGNAL_ENABLE  = 0x00002000
} EMMC_WAITE_SIGNAL_T;

/**
 * @brief EMMC_Extended_Mode
 */
typedef enum
{
    EMMC_EXTENDEN_MODE_DISABLE = 0x00000000,
    EMMC_EXTENDEN_MODE_ENABLE  = 0x00004000
} EMMC_EXTENDEN_MODE_T;

/**
 * @brief EMMC_Write_Burst
 */
typedef enum
{
    EMMC_WRITE_BURST_DISABLE = 0x00000000,
    EMMC_WRITE_BURST_ENABLE  = 0x00080000
} EMMC_WRITE_BURST_T;

/**
 * @brief   EMMC_WAIT_FEATURE
 */
typedef enum
{
    EMMC_WAIT_FEATURE_DISABLE = 0x00000000,
    EMMC_WAIT_FEATURE_ENABLE  = 0x00000002
} EMMC_WAIT_FEATURE_T;

/**
 * @brief EMMC_ECC
 */
typedef enum
{
    EMMC_ECC_DISABLE = 0x00000000,
    EMMC_ECC_ENABLE  = 0x00000040
} EMMC_ECC_T;

/**
 * @brief EMMC_ECC_Page_Size
 */
typedef enum
{
    EMMC_ECC_PAGE_SIZE_BYTE_256  = 0x00000000,
    EMMC_ECC_PAGE_SIZE_BYTE_512  = 0x00020000,
    EMMC_ECC_PAGE_SIZE_BYTE_1024 = 0x00040000,
    EMMC_ECC_PAGE_SIZE_BYTE_2048 = 0x00060000,
    EMMC_ECC_PAGE_SIZE_BYTE_4096 = 0x00080000,
    EMMC_ECC_PAGE_SIZE_BYTE_8192 = 0x000A0000
} EMMC_ECC_PAGE_SIZE_BYTE_T;

/**
 * @brief EMMC_Access_Mode
 */
typedef enum
{
    EMMC_ACCESS_MODE_A = 0x00000000,
    EMMC_ACCESS_MODE_B = 0x10000000,
    EMMC_ACCESS_MODE_C = 0x20000000,
    EMMC_ACCESS_MODE_D = 0x30000000
} EMMC_ACCESS_MODE_T;

/**
 * @brief  EMMC_Interrupt_sources
 */
typedef enum
{
    EMMC_INT_EDGE_RISING  = 0x00000008,
    EMMC_INT_LEVEL_HIGH   = 0x00000010,
    EMMC_INT_EDGE_FALLING = 0x00000020
} EMMC_INT_T;

/**
 * @brief  EMMC_Flags
 */
typedef enum
{
    EMMC_FLAG_EDGE_RISING  = 0x00000001,
    EMMC_FLAG_LEVEL_HIGH   = 0x00000002,
    EMMC_FLAG_EDGE_FALLING = 0x00000004,
    EMMC_FLAG_FIFO_EMPTY   = 0x00000040
} EMMC_FLAG_T;

/**@} end of group EMMC_Enumerations*/


/** @addtogroup EMMC_Structure Data Structure
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
    EMMC_ACCESS_MODE_T accessMode;
} EMMC_NORSRAMTimingConfig_T;

/**
 * @brief EMMC NOR/SRAM Config structure
 */
typedef struct
{
    EMMC_BANK1_NORSRAM_T        bank;
    EMMC_DATA_ADDRESS_MUX_T     dataAddressMux;
    EMMC_MEMORY_TYPE_T          memoryType;
    EMMC_MEMORY_DATA_WIDTH_T    memoryDataWidth;
    EMMC_BURST_ACCESS_MODE_T    burstAcceesMode;
    EMMC_ASYNCHRONOUS_WAIT_T    asynchronousWait;
    EMMC_WAIT_SIGNAL_POLARITY_T waitSignalPolarity;
    EMMC_WRAP_MODE_T            wrapMode;
    EMMC_WAIT_SIGNAL_ACTIVE_T   waitSignalActive;
    EMMC_WRITE_OPERATION_T      writeOperation;
    EMMC_WAITE_SIGNAL_T         waiteSignal;
    EMMC_EXTENDEN_MODE_T        extendedMode;
    EMMC_WRITE_BURST_T          writeBurst;
    EMMC_NORSRAMTimingConfig_T*   readWriteTimingStruct;
    EMMC_NORSRAMTimingConfig_T*   writeTimingStruct;
} EMMC_NORSRAMConfig_T;

/**
 * @brief Timing parameters for NAND and PCCARD Banks
 */
typedef struct
{
    uint32_t setupTime;
    uint32_t waitSetupTime;
    uint32_t holdSetupTime;
    uint32_t HiZSetupTime;
} EMMC_NAND_PCCARDTimingConfig_T;

/**
 * @brief EMMC NAND Config structure
 */
typedef struct
{
    EMMC_BANK_NAND_T          bank;
    EMMC_WAIT_FEATURE_T       waitFeature;
    EMMC_MEMORY_DATA_WIDTH_T  memoryDataWidth;
    EMMC_ECC_T                ECC;
    EMMC_ECC_PAGE_SIZE_BYTE_T ECCPageSize;
    uint32_t                  TCLRSetupTime;
    uint32_t                  TARSetupTime;
    EMMC_NAND_PCCARDTimingConfig_T* commonSpaceTimingStruct;
    EMMC_NAND_PCCARDTimingConfig_T* attributeSpaceTimingStruct;
} EMMC_NANDConfig_T;

/**
 * @brief EMMC PCCARD Config structure
 */
typedef struct
{
    EMMC_WAIT_FEATURE_T waitFeature;
    uint32_t            TCLRSetupTime;
    uint32_t            TARSetupTime;
    EMMC_NAND_PCCARDTimingConfig_T* commonSpaceTimingStruct;
    EMMC_NAND_PCCARDTimingConfig_T* attributeSpaceTimingStruct;
    EMMC_NAND_PCCARDTimingConfig_T* IOSpaceTimingStruct;
} EMMC_PCCARDConfig_T;

/**@} end of group EMMC_Structure*/

/** @addtogroup EMMC_Fuctions Fuctions
  @{
*/

/** EMMC reset */
void EMMC_ResetNORSRAM(EMMC_BANK1_NORSRAM_T bank);
void EMMC_ResetNAND(EMMC_BANK_NAND_T bank);
void EMMC_ResetPCCard(void);

/** EMMC Configuration */
void EMMC_ConfigNORSRAM(EMMC_NORSRAMConfig_T* emmcNORSRAMConfig);
void EMMC_ConfigNAND(EMMC_NANDConfig_T* emmcNANDConfig);
void EMMC_ConfigPCCard(EMMC_PCCARDConfig_T* emmcPCCardConfig);
void EMMC_ConfigNORSRAMStructInit(EMMC_NORSRAMConfig_T* emmcNORSRAMConfig);
void EMMC_ConfigNANDStructInit(EMMC_NANDConfig_T* emmcNANDConfig);
void EMMC_ConfigPCCardStructInit(EMMC_PCCARDConfig_T* emmcPCCardConfig);

/** EMMC bank control */
void EMMC_EnableNORSRAM(EMMC_BANK1_NORSRAM_T bank);
void EMMC_DisableNORSRAM(EMMC_BANK1_NORSRAM_T bank);
void EMMC_EnableNAND(EMMC_BANK_NAND_T bank);
void EMMC_DisableNAND(EMMC_BANK_NAND_T bank);
void EMMC_EnablePCCARD(void);
void EMMC_DisablePCCARD(void);
void EMMC_EnableNANDECC(EMMC_BANK_NAND_T bank);
void EMMC_DisableNANDECC(EMMC_BANK_NAND_T bank);
uint32_t EMMC_ReadECC(EMMC_BANK_NAND_T bank);

/** Interrupt and flag */
void EMMC_EnableInterrupt(EMMC_BANK_NAND_T bank, uint32_t interrupt);
void EMMC_DisableInterrupt(EMMC_BANK_NAND_T bank, uint32_t interrupt);
uint8_t EMMC_ReadStatusFlag(EMMC_BANK_NAND_T bank, EMMC_FLAG_T flag);
void EMMC_ClearStatusFlag(EMMC_BANK_NAND_T bank, uint32_t flag);
uint8_t EMMC_ReadIntFlag(EMMC_BANK_NAND_T bank, EMMC_INT_T flag);
void EMMC_ClearIntFlag(EMMC_BANK_NAND_T bank, uint32_t flag);

/**@} end of group EMMC_Fuctions*/
/**@} end of group EMMC_Driver*/
/**@} end of group Peripherals_Library*/

#ifdef __cplusplus
}
#endif

#endif /* __APM32F10X_EMMC_H */
