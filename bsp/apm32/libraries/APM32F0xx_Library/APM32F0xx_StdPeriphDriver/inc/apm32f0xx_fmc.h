/*!
 * @file        apm32f0xx_fmc.h
 *
 * @brief       This file contains all the functions prototypes for the FMC firmware library
 *
 * @version     V1.0.3
 *
 * @date        2022-09-20
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
#ifndef __APM32F0XX_FMC_H
#define __APM32F0XX_FMC_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes */
#include "apm32f0xx.h"

/** @addtogroup APM32F0xx_StdPeriphDriver
  @{
*/

/** @addtogroup FMC_Driver
  @{
*/

/** @defgroup FMC_Macros Macros
  @{
*/

/* Macros description */

/* Flash Read protection key */
#define FMC_RP_KEY            ((uint32_t)0XA5)

/* Flash key definition */
#define FMC_KEY_1             ((uint32_t)0x45670123)
#define FMC_KEY_2             ((uint32_t)0xCDEF89AB)

#define FMC_OB_KEY_1          ((uint32_t)0x45670123)
#define FMC_OB_KEY_2          ((uint32_t)0xCDEF89AB)

/* Delay definition */
#define FMC_DELAY_ERASE       ((uint32_t)0x000B0000)
#define FMC_DELAY_PROGRAM     ((uint32_t)0x00002000)

/* 32K and 64K Flash devices */
#if !defined (APM32F030xC) && !defined (APM32F070xB) && !defined (APM32F071xB) && !defined (APM32F072xB) && !defined (APM32F091)
/* Flash write protect page definition */
#define FLASH_WRP_PAGE_0_3               ((uint32_t)0x00000001) /*!< Write protection of page 0 to 3 */
#define FLASH_WRP_PAGE_4_7               ((uint32_t)0x00000002) /*!< Write protection of page 4 to 7 */
#define FLASH_WRP_PAGE_8_11              ((uint32_t)0x00000004) /*!< Write protection of page 8 to 11 */
#define FLASH_WRP_PAGE_12_15             ((uint32_t)0x00000008) /*!< Write protection of page 12 to 15 */
#define FLASH_WRP_PAGE_16_19             ((uint32_t)0x00000010) /*!< Write protection of page 16 to 19 */
#define FLASH_WRP_PAGE_20_23             ((uint32_t)0x00000020) /*!< Write protection of page 20 to 23 */
#define FLASH_WRP_PAGE_24_27             ((uint32_t)0x00000040) /*!< Write protection of page 24 to 27 */
#define FLASH_WRP_PAGE_28_31             ((uint32_t)0x00000080) /*!< Write protection of page 28 to 31 */
#define FLASH_WRP_PAGE_32_35             ((uint32_t)0x00000100) /*!< Write protection of page 32 to 35 */
#define FLASH_WRP_PAGE_36_39             ((uint32_t)0x00000200) /*!< Write protection of page 36 to 39 */
#define FLASH_WRP_PAGE_40_43             ((uint32_t)0x00000400) /*!< Write protection of page 40 to 43 */
#define FLASH_WRP_PAGE_44_47             ((uint32_t)0x00000800) /*!< Write protection of page 44 to 47 */
#define FLASH_WRP_PAGE_48_51             ((uint32_t)0x00001000) /*!< Write protection of page 48 to 51 */
#define FLASH_WRP_PAGE_52_55             ((uint32_t)0x00002000) /*!< Write protection of page 52 to 55 */
#define FLASH_WRP_PAGE_56_59             ((uint32_t)0x00004000) /*!< Write protection of page 56 to 59 */
#define FLASH_WRP_PAGE_60_63             ((uint32_t)0x00008000) /*!< Write protection of page 60 to 63 */
#define FLASH_WRP_PAGE_ALL               ((uint32_t)0x0000FFFF) /*!< Write protection of all Sectors */

/* 128K and 256K Flash devices */
#else
/* Flash write protect page definition */
#define FMC_WRP_PAGE_0_1               ((uint32_t)0x00000001) /*!< Write protection of page 0 to 1 */
#define FMC_WRP_PAGE_2_3               ((uint32_t)0x00000002) /*!< Write protection of page 2 to 3 */
#define FMC_WRP_PAGE_4_5               ((uint32_t)0x00000004) /*!< Write protection of page 4 to 5 */
#define FMC_WRP_PAGE_6_7               ((uint32_t)0x00000008) /*!< Write protection of page 6 to 7 */
#define FMC_WRP_PAGE_8_9               ((uint32_t)0x00000010) /*!< Write protection of page 8 to 5 */
#define FMC_WRP_PAGE_10_11             ((uint32_t)0x00000020) /*!< Write protection of page 10 to 5 */
#define FMC_WRP_PAGE_12_13             ((uint32_t)0x00000040) /*!< Write protection of page 12 to 5 */
#define FMC_WRP_PAGE_14_15             ((uint32_t)0x00000080) /*!< Write protection of page 14 to 5 */
#define FMC_WRP_PAGE_16_17             ((uint32_t)0x00000100) /*!< Write protection of page 16 to 15 */
#define FMC_WRP_PAGE_18_19             ((uint32_t)0x00000200) /*!< Write protection of page 18 to 19 */
#define FMC_WRP_PAGE_20_21             ((uint32_t)0x00000400) /*!< Write protection of page 20 to 21 */
#define FMC_WRP_PAGE_22_23             ((uint32_t)0x00000800) /*!< Write protection of page 22 to 23 */
#define FMC_WRP_PAGE_24_25             ((uint32_t)0x00001000) /*!< Write protection of page 24 to 25 */
#define FMC_WRP_PAGE_26_27             ((uint32_t)0x00002000) /*!< Write protection of page 26 to 27 */
#define FMC_WRP_PAGE_28_29             ((uint32_t)0x00004000) /*!< Write protection of page 28 to 29 */
#define FMC_WRP_PAGE_30_31             ((uint32_t)0x00008000) /*!< Write protection of page 30 to 31 */
#define FMC_WRP_PAGE_32_33             ((uint32_t)0x00010000) /*!< Write protection of page 32 to 33 */
#define FMC_WRP_PAGE_34_35             ((uint32_t)0x00020000) /*!< Write protection of page 34 to 35 */
#define FMC_WRP_PAGE_36_37             ((uint32_t)0x00040000) /*!< Write protection of page 36 to 37 */
#define FMC_WRP_PAGE_38_39             ((uint32_t)0x00080000) /*!< Write protection of page 38 to 39 */
#define FMC_WRP_PAGE_40_41             ((uint32_t)0x00100000) /*!< Write protection of page 40 to 41 */
#define FMC_WRP_PAGE_42_43             ((uint32_t)0x00200000) /*!< Write protection of page 42 to 43 */
#define FMC_WRP_PAGE_44_45             ((uint32_t)0x00400000) /*!< Write protection of page 44 to 45 */
#define FMC_WRP_PAGE_46_47             ((uint32_t)0x00800000) /*!< Write protection of page 46 to 47 */
#define FMC_WRP_PAGE_48_49             ((uint32_t)0x01000000) /*!< Write protection of page 48 to 49 */
#define FMC_WRP_PAGE_50_51             ((uint32_t)0x02000000) /*!< Write protection of page 50 to 51 */
#define FMC_WRP_PAGE_52_53             ((uint32_t)0x04000000) /*!< Write protection of page 52 to 53 */
#define FMC_WRP_PAGE_54_55             ((uint32_t)0x08000000) /*!< Write protection of page 54 to 55 */
#define FMC_WRP_PAGE_56_57             ((uint32_t)0x10000000) /*!< Write protection of page 56 to 57 */
#define FMC_WRP_PAGE_58_59             ((uint32_t)0x20000000) /*!< Write protection of page 58 to 59 */
#define FMC_WRP_PAGE_60_61             ((uint32_t)0x40000000) /*!< Write protection of page 20 to 21 */
#define FMC_WRP_PAGE_ALL               ((uint32_t)0xFFFFFFFF) /*!< Write protection of page all */

#endif
/**@} end of group FMC_Macros*/


/** @defgroup FMC_Enumerations Enumerations
  @{
*/

/**
 * @brief Flash Latency
 */
typedef enum
{
    FMC_LATENCY_0,                           /*!< Flash zero latency cycle */
    FMC_LATENCY_1                            /*!< Flash one latency cycle */
} FMC_LATENCY_T;

/**
 * @brief   Flash definition
 */
typedef enum
{
    FMC_FLAG_BUSY = ((uint8_t)0x01),         /*!< Busy flag */
    FMC_FLAG_PE   = ((uint8_t)0x04),         /*!< Program error flag */
    FMC_FLAG_WPE  = ((uint8_t)0x10),         /*!< Write protection flag */
    FMC_FLAG_OC   = ((uint8_t)0x20),         /*!< Operation complete flag */
} FMC_FLAG_T;

/**
 * @brief   Flash Status
 */
typedef enum
{
    FMC_STATE_COMPLETE = ((uint8_t)0),       /*!< Operation complete */
    FMC_STATE_BUSY     = ((uint8_t)1),       /*!< Busy */
    FMC_STATE_PG_ERR   = ((uint8_t)2),       /*!< Program error */
    FMC_STATE_WRP_ERR  = ((uint8_t)3),       /*!< Write Protection error */
    FMC_STATE_TIMEOUT  = ((uint8_t)4),       /*!< Time out */
} FMC_STATE_T;

/**
 * @brief   Interrupt source
 */
typedef enum
{
    FMC_INT_ERROR = ((uint32_t)0x400),       /*!< Error interrupt */
    FMC_INT_COMPLETE  = ((uint32_t)0x1000),  /*!< Operation complete interrupt */
} FMC_INT_T;

/**
 * @brief   Protection Level
 */
typedef enum
{
    FMC_RDP_LEVEL_0 = ((uint8_t)0xAA),       /*!< Protection Level 0 */
    FMC_RDP_LEVEL_1 = ((uint8_t)0xBB),       /*!< Protection Level 1 */
} FMC_RDP_T;

/**
 * @brief   Option byte WDG mode activation
 */
typedef enum
{
    FMC_OB_IWDT_HW    = ((uint8_t)0X00),     /*!< activated by hardware */
    FMC_OB_IWDT_SW    = ((uint8_t)0X01),     /*!< activated by software */
} FMC_OB_IWDT_T;

/**
 * @brief   Option byte STOP mode activation
 */
typedef enum
{
    FMC_OB_STOP_RESET = ((uint8_t)0X00),     /*!< Reset generated when entering in STOP */
    FMC_OB_STOP_NRST  = ((uint8_t)0X02),     /*!< No reset generated when entering in STOP */
} FMC_OB_STOP_T;

/**
 * @brief   Option byte STDBY mode activation
 */
typedef enum
{
    FMC_OB_STDBY_RESET = ((uint8_t)0X00),    /*!< Reset generated when entering in STDBY */
    FMC_OB_STDBY_NRST  = ((uint8_t)0X04),    /*!< No reset generated when entering in STDBY */
} FMC_OB_STDBY_T;

/**
 * @brief   Flash Option Bytes BOOT0
 */
typedef enum
{
    FMC_OB_BOOT0_RESET  = ((uint8_t)0X00),   /*!< BOOT0 Reset */
    FMC_OB_BOOT0_SET = ((uint8_t)0X08),      /*!< BOOT0 Set */
} FMC_OB_BOOT0_T;

/**
 * @brief   Flash Option Bytes BOOT1
 */
typedef enum
{
    FMC_OB_BOOT1_RESET    = ((uint8_t)0X00), /*!< BOOT1 Reset */
    FMC_OB_BOOT1_SET      = ((uint8_t)0X10), /*!< BOOT1 Set */
} FMC_OB_BOOT1_T;

/**
 * @brief   Flash Option Bytes VDDA Analog Monitoring
 */
typedef enum
{
    FMC_OB_VDDA_ANALOG_OFF = ((uint8_t)0X00), /*!< Analog monitoring on VDDA Power source OFF */
    FMC_OB_VDDA_ANALOG_ON  = ((uint8_t)0X20), /*!< Analog monitoring on VDDA Power source ON */
} FMC_OB_VDDA_ANALOG_T;

/**
 * @brief   Flash Option Bytes SRAM Parity Enable
 */
typedef enum
{
    FMC_OB_SRAM_PARITY_SET    = ((uint8_t)0X00), /*!< SRAM parity enable Set */
    FMC_OB_SRAM_PARITY_RESET  = ((uint8_t)0X40), /*!< SRAM parity enable reset */
} FMC_OB_SRAM_PARITY_T;

/**
 * @brief   flash Option Bytes BOOT0SW
 */
typedef enum
{
    FMC_OB_BOOT0_SW   = ((uint8_t)0X00),     /*!< BOOT0 pin disabled */
    FMC_OB_BOOT0_HW   = ((uint8_t)0X80),     /*!< BOOT0 pin bonded with GPIO */
} FMC_OB_BOOT0SW_T;

/**@} end of group FMC_Enumerations*/

/** @defgroup FMC_Structures Structures
  @{
*/

/**
 * @brief   User Option byte config struct definition
 */
typedef struct
{
    FMC_OB_IWDT_T  iwdtSw;
    FMC_OB_STOP_T  stopce;
    FMC_OB_STDBY_T stdbyce;
} FMC_UserConfig_T;

/**@} end of group FMC_Structures*/

/** @defgroup FMC_Variables Variables
  @{
*/

/**@} end of group FMC_Variables*/

/** @defgroup FMC_Functions Functions
  @{
*/

/* Function description */

/* Latency */
void FMC_SetLatency(FMC_LATENCY_T latency);

/* Prefetch Buffer */
void FMC_EnablePrefetchBuffer(void);
void FMC_DisablePrefetchBuffer(void);
uint8_t FMC_ReadPrefetchBufferStatus(void);

/* Lock */
void FMC_Unlock(void);
void FMC_Lock(void);

/* Erase and Program */
FMC_STATE_T FMC_ErasePage(uint32_t pageAddr);
FMC_STATE_T FMC_EraseAllPages(void);

FMC_STATE_T FMC_ProgramWord(uint32_t addr, uint32_t data);
FMC_STATE_T FMC_ProgramHalfWord(uint32_t addr, uint16_t data);

/* FMC Option Bytes Programming functions */
void FMC_UnlockOptionByte(void);
void FMC_LockOptionByte(void);
void FMC_LaunchOptionByte(void);
FMC_STATE_T FMC_EraseOptionByte(void);
FMC_STATE_T FMC_EnableWriteProtection(uint32_t page);
FMC_STATE_T FMC_ConfigReadOutProtection(FMC_RDP_T rdp);
FMC_STATE_T FMC_ConfigOptionByteUser(FMC_UserConfig_T* userConfig);
FMC_STATE_T FMC_EnableOptionByteBOOT(void);
FMC_STATE_T FMC_DisableOptionByteBOOT(void);
FMC_STATE_T FMC_EnableOptionByteVDDA(void);
FMC_STATE_T FMC_DisableOptionByteVDDA(void);
FMC_STATE_T FMC_EnableOptionByteSRAMParity(void);
FMC_STATE_T FMC_DisableOptionByteSRAMParity(void);
FMC_STATE_T FMC_WriteOptionByteUser(uint8_t ob_user);
FMC_STATE_T FMC_ProgramOptionByteData(uint32_t addr, uint8_t data);
uint8_t FMC_ReadOptionByteUser(void);
uint32_t FMC_ReadOptionByteWriteProtection(void);
uint8_t FMC_GetReadProtectionStatus(void);

/* Interrupt and Flag */
void FMC_EnableInterrupt(uint32_t interrupt);
void FMC_DisableInterrupt(uint32_t interrupt);
uint8_t FMC_ReadStatusFlag(FMC_FLAG_T flag);
void FMC_ClearStatusFlag(uint8_t flag);

/* State management */
FMC_STATE_T FMC_ReadState(void);
FMC_STATE_T FMC_WaitForReady(uint32_t timeOut);

#ifdef __cplusplus
}
#endif

#endif /* __APM32F0XX_FMC_H */

/**@} end of group FMC_Functions*/
/**@} end of group FMC_Driver*/
/**@} end of group APM32F0xx_StdPeriphDriver*/
