/*!
 * @file       apm32e10x_smc.h
 *
 * @brief      This file contains all the functions prototypes for the SMC firmware library
 *
 * @version     V1.0.2
 *
 * @date        2022-12-31
 *
 * @attention
 *
 *  Copyright (C) 2021-2023 Geehy Semiconductor
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
#ifndef __APM32E10X_SMC_H
#define __APM32E10X_SMC_H

/* Includes */
#include "apm32e10x.h"

#ifdef __cplusplus
extern "C" {
#endif

/** @addtogroup APM32E10x_StdPeriphDriver
  @{
*/

/** @addtogroup SMC_Driver
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
    SMC_BANK1_NORSRAM_1,    /*!< SMC Bank1 NOR/SRAM1 */
    SMC_BANK1_NORSRAM_2,    /*!< SMC Bank1 NOR/SRAM2 */
    SMC_BANK1_NORSRAM_3,    /*!< SMC Bank1 NOR/SRAM3 */
    SMC_BANK1_NORSRAM_4     /*!< SMC Bank1 NOR/SRAM4 */
} SMC_BANK1_NORSRAM_T;

/**
 * @brief SMC NAND and PC Card Bank
 */
typedef enum
{
    SMC_BANK2_NAND,     /*!< SMC Bank2 NAND */
    SMC_BANK3_NAND,     /*!< SMC Bank3 NAND */
    SMC_BANK4_PCCARD    /*!< SMC Bank4 PCCARD */
} SMC_BANK_NAND_T;

/**
 * @brief SMC_Data_Address_Bus_Multiplexing
 */
typedef enum
{
    SMC_DATA_ADDRESS_MUX_DISABLE,   /*!< Disable data address multiplexing */
    SMC_DATA_ADDRESS_MUX_ENABLE     /*!< Enable data address multiplexing */
} SMC_DATA_ADDRESS_MUX_T;

/**
 * @brief SMC_Memory_Type
 */
typedef enum
{
    SMC_MEMORY_TYPE_SRAM,   /*!< SRAM memory */
    SMC_MEMORY_TYPE_PSRAM,  /*!< PSRAM memory */
    SMC_MEMORY_TYPE_NOR     /*!< NORFlash memory */
} SMC_MEMORY_TYPE_T;

/**
 * @brief SMC_Data_Width
 */
typedef enum
{
    SMC_MEMORY_DATA_WIDTH_8BIT, /*!< Set memory data width to 8-bit */
    SMC_MEMORY_DATA_WIDTH_16BIT /*!< Set memory data width to 16-bit */
} SMC_MEMORY_DATA_WIDTH_T;

/**
 * @brief SMC_Burst_Access_Mode
 */
typedef enum
{
    SMC_BURST_ACCESS_MODE_DISABLE,  /*!< Disable burst access mode */
    SMC_BURST_ACCESS_MODE_ENABLE    /*!< Enable burst access mode */
} SMC_BURST_ACCESS_MODE_T;

/**
 * @brief SMC_AsynchronousWait
 */
typedef enum
{
    SMC_ASYNCHRONOUS_WAIT_DISABLE,  /*!< Disable asynchronous wait */
    SMC_ASYNCHRONOUS_WAIT_ENABLE    /*!< Enable asynchronous wait */
} SMC_ASYNCHRONOUS_WAIT_T;

/**
 * @brief SMC_Wait_Signal_Polarity
 */
typedef enum
{
    SMC_WAIT_SIGNAL_POLARITY_LOW,   /*!< Set low polarity valid */
    SMC_WAIT_SIGNAL_POLARITY_HIGH   /*!< Set high polarity valid */
} SMC_WAIT_SIGNAL_POLARITY_T;

/**
 * @brief SMC_Wrap_Mode
 */
typedef enum
{
    SMC_WRAP_MODE_DISABLE,  /*!< Disable wrapped burst mode */
    SMC_WRAP_MODE_ENABLE    /*!< Enable wrapped burst mode */
} SMC_WRAP_MODE_T;

/**
 * @brief SMC_Wait_Timing
 */
typedef enum
{
    SMC_WAIT_SIGNAL_ACTIVE_BEFORE_WAIT_STATE,   /*!< Set wait active before wait state */
    SMC_WAIT_SIGNAL_ACTIVE_DURING_WAIT_STATE    /*!< Set wait active during wait state */
} SMC_WAIT_SIGNAL_ACTIVE_T;

/**
 * @brief SMC_Write_Operation
 */
typedef enum
{
    SMC_WRITE_OPERATION_DISABLE,    /*!< Disable write operation */
    SMC_WRITE_OPERATION_ENABLE      /*!< Enable write operation  */
} SMC_WRITE_OPERATION_T;

/**
 * @brief SMC_Wait_Signal
 */
typedef enum
{
    SMC_WAITE_SIGNAL_DISABLE,   /*!< Disable wait signal */
    SMC_WAITE_SIGNAL_ENABLE     /*!< Enable wait signal */
} SMC_WAITE_SIGNAL_T;

/**
 * @brief SMC_Extended_Mode
 */
typedef enum
{
    SMC_EXTENDEN_MODE_DISABLE,  /*!< Disable extended mode */
    SMC_EXTENDEN_MODE_ENABLE    /*!< Enable extended mode */
} SMC_EXTENDEN_MODE_T;
/**
 * @brief SMC_Write_Burst
 */
typedef enum
{
    SMC_WRITE_BURST_DISABLE,    /*!< Disable write PSRAM burst */
    SMC_WRITE_BURST_ENABLE      /*!< Enable write PSRAM burst */
} SMC_WRITE_BURST_T;

/**
 * @brief   SMC_WAIT_FEATURE
 */
typedef enum
{
    SMC_WAIT_FEATURE_DISABLE,   /*!< Disable wait feature */
    SMC_WAIT_FEATURE_ENABLE     /*!< Enable wait feature */
} SMC_WAIT_FEATURE_T;

/**
 * @brief SMC_ECC
 */
typedef enum
{
    SMC_ECC_DISABLE,    /*!< Disable ECC */
    SMC_ECC_ENABLE      /*!< Enable ECC */
} SMC_ECC_T;

/**
 * @brief SMC_ECC_Page_Size
 */
typedef enum
{
    SMC_ECC_PAGE_SIZE_BYTE_256,     /*!< ECC page size = 256 bytes */
    SMC_ECC_PAGE_SIZE_BYTE_512,     /*!< ECC page size = 512 bytes */
    SMC_ECC_PAGE_SIZE_BYTE_1024,    /*!< ECC page size = 1024 bytes */
    SMC_ECC_PAGE_SIZE_BYTE_2048,    /*!< ECC page size = 2048 bytes */
    SMC_ECC_PAGE_SIZE_BYTE_4096,    /*!< ECC page size = 4096 bytes */
    SMC_ECC_PAGE_SIZE_BYTE_8192     /*!< ECC page size = 8192 bytes */
} SMC_ECC_PAGE_SIZE_BYTE_T;

/**
 * @brief SMC_Access_Mode
 */
typedef enum
{
    SMC_ACCESS_MODE_A,  /*!< Access mode A */
    SMC_ACCESS_MODE_B,  /*!< Access mode B */
    SMC_ACCESS_MODE_C,  /*!< Access mode C */
    SMC_ACCESS_MODE_D   /*!< Access mode D */
} SMC_ACCESS_MODE_T;

/**
 * @brief  SMC_Interrupt_sources
 */
typedef enum
{
    SMC_INT_EDGE_RISING  = 0x00000008,  /*!< Rising edge detection interrupt */
    SMC_INT_LEVEL_HIGH   = 0x00000010,  /*!< High level detection interrupt */
    SMC_INT_EDGE_FALLING = 0x00000020   /*!< Falling edge detection interrupt */
} SMC_INT_T;

/**
 * @brief  SMC_Flags
 */
typedef enum
{
    SMC_FLAG_EDGE_RISING  = 0x00000001, /*!< Rising egde detection Flag */
    SMC_FLAG_LEVEL_HIGH   = 0x00000002, /*!< High level detection Flag */
    SMC_FLAG_EDGE_FALLING = 0x00000004, /*!< Falling egde detection Flag */
    SMC_FLAG_FIFO_EMPTY   = 0x00000040  /*!< FIFO empty Flag */
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
    uint8_t           addressSetupTime;     /*!< Set address setup time */
    uint8_t           addressHodeTime;      /*!< Set address-hold setup time */
    uint8_t           dataSetupTime;        /*!< Set data setup time */
    uint8_t           busTurnaroundTime;    /*!< Set bus turnaround time */
    uint8_t           clockDivision;        /*!< Set clock divide radio */
    uint8_t           dataLatency;          /*!< Set data latency */
    SMC_ACCESS_MODE_T accessMode;           /*!< Set access mode */
} SMC_NORSRAMTimingConfig_T;

/**
 * @brief SMC NOR/SRAM Config structure
 */
typedef struct
{
    SMC_BANK1_NORSRAM_T        bank;                    /*!< NORSRAM bank selection */
    SMC_DATA_ADDRESS_MUX_T     dataAddressMux;          /*!< Data address bus multiplexing selection */
    SMC_MEMORY_TYPE_T          memoryType;              /*!< Memory type selection */
    SMC_MEMORY_DATA_WIDTH_T    memoryDataWidth;         /*!< Data width selection */
    SMC_BURST_ACCESS_MODE_T    burstAcceesMode;         /*!< Set burst access mode */
    SMC_ASYNCHRONOUS_WAIT_T    asynchronousWait;        /*!< Set asynchronous wait */
    SMC_WAIT_SIGNAL_POLARITY_T waitSignalPolarity;      /*!< Set wait signal polarity */
    SMC_WRAP_MODE_T            wrapMode;                /*!< Set wrapped burst mode */
    SMC_WAIT_SIGNAL_ACTIVE_T   waitSignalActive;        /*!< Set wait timing */
    SMC_WRITE_OPERATION_T      writeOperation;          /*!< Set write operation */
    SMC_WAITE_SIGNAL_T         waiteSignal;             /*!< Set wait signal */
    SMC_EXTENDEN_MODE_T        extendedMode;            /*!< Set extended mode */
    SMC_WRITE_BURST_T          writeBurst;              /*!< Set write burst */
    SMC_NORSRAMTimingConfig_T* readWriteTimingStruct;   /*!< Read and write timing */
    SMC_NORSRAMTimingConfig_T* writeTimingStruct;       /*!< Write timing */
} SMC_NORSRAMConfig_T;

/**
 * @brief Timing parameters for NAND and PCCARD Banks
 */
typedef struct
{
    uint8_t setupTime;      /*!< Set setup address time( 0x01 ~ 0xFE ) */
    uint8_t waitSetupTime;  /*!< Set assert the command time ( 0x01 ~ 0xFE ) */
    uint8_t holdSetupTime;  /*!< Set hold address time ( 0x01 ~ 0xFE ) */
    uint8_t HiZSetupTime;   /*!< Set the time of keep in HiZ ( 0x00 ~ 0xFE ) */
} SMC_NAND_PCCARDTimingConfig_T;

/**
 * @brief SMC NAND Config structure
 */
typedef struct
{
    SMC_BANK_NAND_T                bank;                        /*!< SMC NAND and PC Card Bank */
    SMC_WAIT_FEATURE_T             waitFeature;                 /*!< Set wait feature */
    SMC_MEMORY_DATA_WIDTH_T        memoryDataWidth;             /*!< Data width selection */
    SMC_ECC_T                      ECC;                         /*!< Set ECC */
    SMC_ECC_PAGE_SIZE_BYTE_T       ECCPageSize;                 /*!< Set ECC page size */
    uint8_t                        TCLRSetupTime;               /*!< Set the delay time of CLE to RE */
    uint8_t                        TARSetupTime;                /*!< Set the delay time of ALE to RE */
    SMC_NAND_PCCARDTimingConfig_T* commonSpaceTimingStruct;     /*!< Common space timing */
    SMC_NAND_PCCARDTimingConfig_T* attributeSpaceTimingStruct;  /*!< Attribute space timing */
} SMC_NANDConfig_T;

/**
 * @brief SMC PCCARD Config structure
 */
typedef struct
{
    SMC_WAIT_FEATURE_T             waitFeature;                 /*!< Set wait feature */
    uint32_t                       TCLRSetupTime;               /*!< Set the delay time of CLE to RE */
    uint32_t                       TARSetupTime;                /*!< Set the delay time of ALE to RE */
    SMC_NAND_PCCARDTimingConfig_T* commonSpaceTimingStruct;     /*!< Common space timing */
    SMC_NAND_PCCARDTimingConfig_T* attributeSpaceTimingStruct;  /*!< Attribute space timing */
    SMC_NAND_PCCARDTimingConfig_T* IOSpaceTimingStruct;         /*!< IO space timing */
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
uint16_t SMC_ReadStatusFlag(SMC_BANK_NAND_T bank, SMC_FLAG_T flag);
void SMC_ClearStatusFlag(SMC_BANK_NAND_T bank, uint32_t flag);
uint16_t SMC_ReadIntFlag(SMC_BANK_NAND_T bank, SMC_INT_T flag);
void SMC_ClearIntFlag(SMC_BANK_NAND_T bank, uint32_t flag);

/**@} end of group SMC_Functions*/
/**@} end of group SMC_Driver */
/**@} end of group APM32E10x_StdPeriphDriver*/

#ifdef __cplusplus
}
#endif

#endif /* __APM32E10X_SMC_H */
