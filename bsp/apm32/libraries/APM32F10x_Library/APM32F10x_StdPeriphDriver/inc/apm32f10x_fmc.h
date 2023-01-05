/*!
 * @file        apm32f10x_fmc.h
 *
 * @brief       This file contains all the functions prototypes for the FMC firmware library
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
#ifndef __APM32F10X_FMC_H
#define __APM32F10X_FMC_H

/* Includes */
#include "apm32f10x.h"

#ifdef __cplusplus
extern "C" {
#endif

/** @addtogroup APM32F10x_StdPeriphDriver
  @{
*/

/** @addtogroup FMC_Driver FMC Driver
  @{
*/

/** @defgroup FMC_Macros Macros
  @{
*/

/* Macros description */

/* Values for APM32 Low and Medium density devices */
#define FLASH_WRP_PAGE_0_3               ((uint32_t)BIT0) /*!< Write protection of page 0 to 3 */
#define FLASH_WRP_PAGE_4_7               ((uint32_t)BIT1) /*!< Write protection of page 4 to 7 */
#define FLASH_WRP_PAGE_8_11              ((uint32_t)BIT2) /*!< Write protection of page 8 to 11 */
#define FLASH_WRP_PAGE_12_15             ((uint32_t)BIT3) /*!< Write protection of page 12 to 15 */
#define FLASH_WRP_PAGE_16_19             ((uint32_t)BIT4) /*!< Write protection of page 16 to 19 */
#define FLASH_WRP_PAGE_20_23             ((uint32_t)BIT5) /*!< Write protection of page 20 to 23 */
#define FLASH_WRP_PAGE_24_27             ((uint32_t)BIT6) /*!< Write protection of page 24 to 27 */
#define FLASH_WRP_PAGE_28_31             ((uint32_t)BIT7) /*!< Write protection of page 28 to 31 */

/* Values for APM32 Medium-density devices */
#define FLASH_WRP_PAGE_32_35             ((uint32_t)BIT8)  /*!< Write protection of page 32 to 35 */
#define FLASH_WRP_PAGE_36_39             ((uint32_t)BIT9)  /*!< Write protection of page 36 to 39 */
#define FLASH_WRP_PAGE_40_43             ((uint32_t)BIT10) /*!< Write protection of page 40 to 43 */
#define FLASH_WRP_PAGE_44_47             ((uint32_t)BIT11) /*!< Write protection of page 44 to 47 */
#define FLASH_WRP_PAGE_48_51             ((uint32_t)BIT12) /*!< Write protection of page 48 to 51 */
#define FLASH_WRP_PAGE_52_55             ((uint32_t)BIT13) /*!< Write protection of page 52 to 55 */
#define FLASH_WRP_PAGE_56_59             ((uint32_t)BIT14) /*!< Write protection of page 56 to 59 */
#define FLASH_WRP_PAGE_60_63             ((uint32_t)BIT15) /*!< Write protection of page 60 to 63 */
#define FLASH_WRP_PAGE_64_67             ((uint32_t)BIT16) /*!< Write protection of page 64 to 67 */
#define FLASH_WRP_PAGE_68_71             ((uint32_t)BIT17) /*!< Write protection of page 68 to 71 */
#define FLASH_WRP_PAGE_72_75             ((uint32_t)BIT18) /*!< Write protection of page 72 to 75 */
#define FLASH_WRP_PAGE_76_79             ((uint32_t)BIT19) /*!< Write protection of page 76 to 79 */
#define FLASH_WRP_PAGE_80_83             ((uint32_t)BIT20) /*!< Write protection of page 80 to 83 */
#define FLASH_WRP_PAGE_84_87             ((uint32_t)BIT21) /*!< Write protection of page 84 to 87 */
#define FLASH_WRP_PAGE_88_91             ((uint32_t)BIT22) /*!< Write protection of page 88 to 91 */
#define FLASH_WRP_PAGE_92_95             ((uint32_t)BIT23) /*!< Write protection of page 92 to 95 */
#define FLASH_WRP_PAGE_96_99             ((uint32_t)BIT24) /*!< Write protection of page 96 to 99 */
#define FLASH_WRP_PAGE_100_103           ((uint32_t)BIT25) /*!< Write protection of page 100 to 103 */
#define FLASH_WRP_PAGE_104_107           ((uint32_t)BIT26) /*!< Write protection of page 104 to 107 */
#define FLASH_WRP_PAGE_108_111           ((uint32_t)BIT27) /*!< Write protection of page 108 to 111 */
#define FLASH_WRP_PAGE_112_115           ((uint32_t)BIT28) /*!< Write protection of page 112 to 115 */
#define FLASH_WRP_PAGE_116_119           ((uint32_t)BIT29) /*!< Write protection of page 116 to 119 */
#define FLASH_WRP_PAGE_120_123           ((uint32_t)BIT30) /*!< Write protection of page 120 to 123 */
#define FLASH_WRP_PAGE_124_127           ((uint32_t)BIT31) /*!< Write protection of page 124 to 127 */

/* Values only for APM32 High-density devices */
#define FLASH_WRP_PAGE_0_1             ((uint32_t)BIT0)  /*!< Write protection of page 0 to 1 */
#define FLASH_WRP_PAGE_2_3             ((uint32_t)BIT1)  /*!< Write protection of page 2 to 3 */
#define FLASH_WRP_PAGE_4_5             ((uint32_t)BIT2)  /*!< Write protection of page 4 to 5 */
#define FLASH_WRP_PAGE_6_7             ((uint32_t)BIT3)  /*!< Write protection of page 6 to 7 */
#define FLASH_WRP_PAGE_8_9             ((uint32_t)BIT4)  /*!< Write protection of page 8 to 9 */
#define FLASH_WRP_PAGE_10_11           ((uint32_t)BIT5)  /*!< Write protection of page 10 to 11 */
#define FLASH_WRP_PAGE_12_13           ((uint32_t)BIT6)  /*!< Write protection of page 12 to 13 */
#define FLASH_WRP_PAGE_14_15           ((uint32_t)BIT7)  /*!< Write protection of page 14 to 15 */
#define FLASH_WRP_PAGE_16_17           ((uint32_t)BIT8)  /*!< Write protection of page 16 to 17 */
#define FLASH_WRP_PAGE_18_19           ((uint32_t)BIT9)  /*!< Write protection of page 18 to 19 */
#define FLASH_WRP_PAGE_20_21           ((uint32_t)BIT10) /*!< Write protection of page 20 to 21 */
#define FLASH_WRP_PAGE_22_23           ((uint32_t)BIT11) /*!< Write protection of page 22 to 23 */
#define FLASH_WRP_PAGE_24_25           ((uint32_t)BIT12) /*!< Write protection of page 24 to 25 */
#define FLASH_WRP_PAGE_26_27           ((uint32_t)BIT13) /*!< Write protection of page 26 to 27 */
#define FLASH_WRP_PAGE_28_29           ((uint32_t)BIT14) /*!< Write protection of page 28 to 29 */
#define FLASH_WRP_PAGE_30_31           ((uint32_t)BIT15) /*!< Write protection of page 30 to 31 */
#define FLASH_WRP_PAGE_32_33           ((uint32_t)BIT16) /*!< Write protection of page 32 to 33 */
#define FLASH_WRP_PAGE_34_35           ((uint32_t)BIT17) /*!< Write protection of page 34 to 35 */
#define FLASH_WRP_PAGE_36_37           ((uint32_t)BIT18) /*!< Write protection of page 36 to 37 */
#define FLASH_WRP_PAGE_38_39           ((uint32_t)BIT19) /*!< Write protection of page 38 to 39 */
#define FLASH_WRP_PAGE_40_41           ((uint32_t)BIT20) /*!< Write protection of page 40 to 41 */
#define FLASH_WRP_PAGE_42_43           ((uint32_t)BIT21) /*!< Write protection of page 42 to 43 */
#define FLASH_WRP_PAGE_44_45           ((uint32_t)BIT22) /*!< Write protection of page 44 to 45 */
#define FLASH_WRP_PAGE_46_47           ((uint32_t)BIT23) /*!< Write protection of page 46 to 47 */
#define FLASH_WRP_PAGE_48_49           ((uint32_t)BIT24) /*!< Write protection of page 48 to 49 */
#define FLASH_WRP_PAGE_50_51           ((uint32_t)BIT25) /*!< Write protection of page 50 to 51 */
#define FLASH_WRP_PAGE_52_53           ((uint32_t)BIT26) /*!< Write protection of page 52 to 53 */
#define FLASH_WRP_PAGE_54_55           ((uint32_t)BIT27) /*!< Write protection of page 54 to 55 */
#define FLASH_WRP_PAGE_56_57           ((uint32_t)BIT28) /*!< Write protection of page 56 to 57 */
#define FLASH_WRP_PAGE_58_59           ((uint32_t)BIT29) /*!< Write protection of page 58 to 59 */
#define FLASH_WRP_PAGE_60_61           ((uint32_t)BIT30) /*!< Write protection of page 60 to 61 */
#define FLASH_WRP_PAGE_62_127          ((uint32_t)BIT31) /*!< Write protection of page 62 to 127 */
#define FMC_WRP_PAGE_ALL               ((uint32_t)0xFFFFFFFF) /*!< Write protection of page all */

/**@} end of group FMC_Macros*/

/** @defgroup FMC_Enumerations Enumerations
  @{
*/

/**
 * @brief Flash Latency
 */
typedef enum
{
    FMC_LATENCY_0,
    FMC_LATENCY_1,
    FMC_LATENCY_2
} FMC_LATENCY_T;

/**
 * @brief FMC Status
 */
typedef enum
{
    FMC_STATUS_BUSY = 1,   /*!< flash busy */
    FMC_STATUS_ERROR_PG,   /*!< flash programming error */
    FMC_STATUS_ERROR_WRP,  /*!< flash write protection error */
    FMC_STATUS_COMPLETE,   /*!< flash operation complete */
    FMC_STATUS_TIMEOUT     /*!< flash time out */
} FMC_STATUS_T;

/**
 * @brief Option Bytes IWatchdog
 */
typedef enum
{
    OB_IWDT_HARD   = 0x0000,
    OB_IWDT_SOTF   = 0x0001
} OB_IWDT_T;

/**
 * @brief Option Bytes nRST STOP
 */
typedef enum
{
    OB_STOP_RST    = 0x0000,
    OB_STOP_NORST  = 0x0002
} OB_STOP_T;

/**
 * @brief Option Bytes nRST STDBY
 */
typedef enum
{
    OB_STDBY_RST   = 0x0000,
    OB_STDBY_NORST = 0x0004
} OB_STDBY_T;

/**
 * @brief  FMC Interrupts
 */
typedef enum
{
    FMC_INT_ERR,
    FMC_INT_OC
} FMC_INT_T;

/**
 * @brief FMC flag
 */
typedef enum
{
    FMC_FLAG_BUSY = 0x00000001,  /*!< FMC Busy flag */
    FMC_FLAG_OC   = 0x00000020,  /*!< FMC End of Operation flag */
    FMC_FLAG_PE   = 0x00000004,  /*!< FMC Program error flag */
    FMC_FLAG_WPE  = 0x00000010,  /*!< FMC Write protected error flag */
    FMC_FLAG_OBE  = 0x10000001,  /*!< FMC Option Byte error flag */
} FMC_FLAG_T;

/**@} end of group FMC_Enumerations*/

/** @defgroup FMC_Structures Structures
  @{
*/

/**
 * @brief   User Option byte config struct definition
 */
typedef struct
{
    OB_IWDT_T  iwdtSet;
    OB_STOP_T  stopSet;
    OB_STDBY_T stdbySet;
} FMC_UserConfig_T;

/**@} end of group FMC_Structure*/

/** @defgroup FMC_Functions Functions
  @{
*/

/* Initialization and Configuration */
void FMC_ConfigLatency(FMC_LATENCY_T latency);
void FMC_EnableHalfCycleAccess(void);
void FMC_DisableHalfCycleAccess(void);
void FMC_EnablePrefetchBuffer(void);
void FMC_DisablePrefetchBuffer(void);

/* Lock management */
void FMC_Unlock(void);
void FMC_Lock(void);

/* Erase management */
FMC_STATUS_T FMC_ErasePage(uint32_t pageAddr);
FMC_STATUS_T FMC_EraseAllPage(void);
FMC_STATUS_T FMC_EraseOptionBytes(void);

/* Read Write management */
FMC_STATUS_T FMC_ProgramWord(uint32_t address, uint32_t data);
FMC_STATUS_T FMC_ProgramHalfWord(uint32_t address, uint16_t data);
FMC_STATUS_T FMC_ProgramOptionByteData(uint32_t address, uint8_t data);
FMC_STATUS_T FMC_EnableWriteProtection(uint32_t page);
FMC_STATUS_T FMC_EnableReadOutProtection(void);
FMC_STATUS_T FMC_DisableReadOutProtection(void);
FMC_STATUS_T FMC_ConfigUserOptionByte(FMC_UserConfig_T* userConfig);
uint32_t FMC_ReadUserOptionByte(void);
uint32_t FMC_ReadOptionByteWriteProtection(void);
uint8_t FMC_GetReadProtectionStatus(void);
uint8_t FMC_ReadPrefetchBufferStatus(void);

/* Interrupts and flags */
void FMC_EnableInterrupt(FMC_INT_T interrupt);
void FMC_DisableInterrupt(FMC_INT_T interrupt);
uint8_t FMC_ReadStatusFlag(FMC_FLAG_T flag);
void FMC_ClearStatusFlag(uint32_t flag);

/* Status management */
FMC_STATUS_T FMC_ReadStatus(void);
FMC_STATUS_T FMC_WaitForLastOperation(uint32_t timeOut);

/**@} end of group FMC_Functions*/
/**@} end of group FMC_Driver*/
/**@} end of group APM32F10x_StdPeriphDriver*/

#ifdef __cplusplus
}
#endif

#endif /* __APM32F10X_FMC_H */
