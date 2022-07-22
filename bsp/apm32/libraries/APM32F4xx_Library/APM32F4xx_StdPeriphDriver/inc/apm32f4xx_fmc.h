/*!
 * @file       apm32f4xx_fmc.h
 *
 * @brief      This file contains all the functions prototypes for the FMC firmware library
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

/* Define to prevent recursive inclusion */
#ifndef __APM32F4XX_FMC_H
#define __APM32F4XX_FMC_H

#ifdef __cplusplus
  extern "C" {
#endif

/* Includes */
#include "apm32f4xx.h"

/** @addtogroup APM32F4xx_StdPeriphDriver
  @{
*/

/** @addtogroup FMC_Driver
  @{
*/

/** @defgroup FMC_Enumerations
  @{
*/

/**
 * @brief FMC Status
 */
typedef enum
{
    FMC_BUSY = 1,           /*!< Busy */
    FMC_ERROR_RD,           /*!< Reserved */
    FMC_ERROR_PGS,          /*!< Programming Sequence Error */
    FMC_ERROR_PGP,          /*!< Programming Parallelism Error */
    FMC_ERROR_PGA,          /*!< Programming Alignment Error */
    FMC_ERROR_WRP,          /*!< Write Protection Error */
    FMC_ERROR_PROGRAM,      /*!< Programming Error */
    FMC_ERROR_OPERATION,    /*!< Operation Error */
    FMC_COMPLETE            /*!< Operation Complete */
} FMC_STATUS_T;

/**
 * @brief FMC Latency
 */
typedef enum
{
    FMC_LTNCY_0    = ((uint8_t)0x0000), /*!< FMC 0 Latency cycle */
    FMC_LTNCY_1    = ((uint8_t)0x0001), /*!< FMC 1 Latency cycle */
    FMC_LTNCY_2    = ((uint8_t)0x0002), /*!< FMC 2 Latency cycles */
    FMC_LTNCY_3    = ((uint8_t)0x0003), /*!< FMC 3 Latency cycles */
    FMC_LTNCY_4    = ((uint8_t)0x0004), /*!< FMC 4 Latency cycles */
    FMC_LTNCY_5    = ((uint8_t)0x0005), /*!< FMC 5 Latency cycles */
    FMC_LTNCY_6    = ((uint8_t)0x0006), /*!< FMC 6 Latency cycles */
    FMC_LTNCY_7    = ((uint8_t)0x0007), /*!< FMC 7 Latency cycles */
    FMC_LTNCY_8    = ((uint8_t)0x0008), /*!< FMC 8 Latency cycles */
    FMC_LTNCY_9    = ((uint8_t)0x0009), /*!< FMC 9 Latency cycles */
    FMC_LTNCY_10   = ((uint8_t)0x000A), /*!< FMC 10 Latency cycles */
    FMC_LTNCY_11   = ((uint8_t)0x000B), /*!< FMC 11 Latency cycles */
    FMC_LTNCY_12   = ((uint8_t)0x000C), /*!< FMC 12 Latency cycles */
    FMC_LTNCY_13   = ((uint8_t)0x000D), /*!< FMC 13 Latency cycles */
    FMC_LTNCY_14   = ((uint8_t)0x000E), /*!< FMC 14 Latency cycles */
    FMC_LTNCY_15   = ((uint8_t)0x000F)  /*!< FMC 15 Latency cycles */
} FMC_LATENCY_T;

/**
 * @brief FMC Voltage Range
 */
typedef enum
{
    FMC_VOLTAGE_1  = (uint8_t)0x00, /*!< when the device voltage range is 1.8V to 2.1V,
                                        the operation will be done by byte (8-bit) */
    FMC_VOLTAGE_2  = (uint8_t)0x01, /*!< when the device voltage range is 2.1V to 2.7V,
                                        the operation will be done by half word (16-bit) */
    FMC_VOLTAGE_3  = (uint8_t)0x02, /*!< when the device voltage range is 2.7V to 3.6V,
                                        the operation will be done by word (32-bit) */
    FMC_VOLTAGE_4  = (uint8_t)0x03, /*!< when the device voltage range is 2.7V to 3.6V + External Vpp,
                                        the operation will be done by double word (64-bit) */
} FMC_VOLTAGE_T;

/**
 * @brief FMC Sectors
 */
typedef enum
{
    FMC_SECTOR_0   = ((uint16_t)0x0000),    /*!< Sector number 0 */
    FMC_SECTOR_1   = ((uint16_t)0x0008),    /*!< Sector number 1 */
    FMC_SECTOR_2   = ((uint16_t)0x0010),    /*!< Sector number 2 */
    FMC_SECTOR_3   = ((uint16_t)0x0018),    /*!< Sector number 3 */
    FMC_SECTOR_4   = ((uint16_t)0x0020),    /*!< Sector number 4 */
    FMC_SECTOR_5   = ((uint16_t)0x0028),    /*!< Sector number 5 */
    FMC_SECTOR_6   = ((uint16_t)0x0030),    /*!< Sector number 6 */
    FMC_SECTOR_7   = ((uint16_t)0x0038),    /*!< Sector number 7 */
    FMC_SECTOR_8   = ((uint16_t)0x0040),    /*!< Sector number 8 */
    FMC_SECTOR_9   = ((uint16_t)0x0048),    /*!< Sector number 9 */
    FMC_SECTOR_10  = ((uint16_t)0x0050),    /*!< Sector number 10 */
    FMC_SECTOR_11  = ((uint16_t)0x0058),    /*!< Sector number 11 */
    FMC_SECTOR_12  = ((uint16_t)0x0080),    /*!< Sector number 12 */
    FMC_SECTOR_13  = ((uint16_t)0x0088),    /*!< Sector number 13 */
    FMC_SECTOR_14  = ((uint16_t)0x0090),    /*!< Sector number 14 */
    FMC_SECTOR_15  = ((uint16_t)0x0098),    /*!< Sector number 15 */
    FMC_SECTOR_16  = ((uint16_t)0x00A0),    /*!< Sector number 16 */
    FMC_SECTOR_17  = ((uint16_t)0x00A8),    /*!< Sector number 17 */
    FMC_SECTOR_18  = ((uint16_t)0x00B0),    /*!< Sector number 18 */
    FMC_SECTOR_19  = ((uint16_t)0x00B8),    /*!< Sector number 19 */
    FMC_SECTOR_20  = ((uint16_t)0x00C0),    /*!< Sector number 20 */
    FMC_SECTOR_21  = ((uint16_t)0x00C8),    /*!< Sector number 21 */
    FMC_SECTOR_22  = ((uint16_t)0x00D0),    /*!< Sector number 22 */
    FMC_SECTOR_23  = ((uint16_t)0x00D8)     /*!< Sector number 23 */
} FMC_SECTOR_T;

/**
 * @brief Option Bytes Write Protection
 */
typedef enum
{
    FMC_OPT_WRP_SECTOR_0   = (uint32_t)0x00000001,  /*!< Write protection of sector 0 */
    FMC_OPT_WRP_SECTOR_1   = (uint32_t)0x00000002,  /*!< Write protection of sector 1 */
    FMC_OPT_WRP_SECTOR_2   = (uint32_t)0x00000004,  /*!< Write protection of sector 2 */
    FMC_OPT_WRP_SECTOR_3   = (uint32_t)0x00000008,  /*!< Write protection of sector 3 */
    FMC_OPT_WRP_SECTOR_4   = (uint32_t)0x00000010,  /*!< Write protection of sector 4 */
    FMC_OPT_WRP_SECTOR_5   = (uint32_t)0x00000020,  /*!< Write protection of sector 5 */
    FMC_OPT_WRP_SECTOR_6   = (uint32_t)0x00000040,  /*!< Write protection of sector 6 */
    FMC_OPT_WRP_SECTOR_7   = (uint32_t)0x00000080,  /*!< Write protection of sector 7 */
    FMC_OPT_WRP_SECTOR_8   = (uint32_t)0x00000100,  /*!< Write protection of sector 8 */
    FMC_OPT_WRP_SECTOR_9   = (uint32_t)0x00000200,  /*!< Write protection of sector 9 */
    FMC_OPT_WRP_SECTOR_10  = (uint32_t)0x00000400,  /*!< Write protection of sector 10 */
    FMC_OPT_WRP_SECTOR_11  = (uint32_t)0x00000800,  /*!< Write protection of sector 11 */

    FMC_OPT_WRP_SECTOR_12  = (uint32_t)0x00000001,  /*!< Write protection of sector 12 */
    FMC_OPT_WRP_SECTOR_13  = (uint32_t)0x00000002,  /*!< Write protection of sector 13 */
    FMC_OPT_WRP_SECTOR_14  = (uint32_t)0x00000004,  /*!< Write protection of sector 14 */
    FMC_OPT_WRP_SECTOR_15  = (uint32_t)0x00000008,  /*!< Write protection of sector 15 */
    FMC_OPT_WRP_SECTOR_16  = (uint32_t)0x00000010,  /*!< Write protection of sector 16 */
    FMC_OPT_WRP_SECTOR_17  = (uint32_t)0x00000020,  /*!< Write protection of sector 17 */
    FMC_OPT_WRP_SECTOR_18  = (uint32_t)0x00000040,  /*!< Write protection of sector 18 */
    FMC_OPT_WRP_SECTOR_19  = (uint32_t)0x00000080,  /*!< Write protection of sector 19 */
    FMC_OPT_WRP_SECTOR_20  = (uint32_t)0x00000100,  /*!< Write protection of sector 20 */
    FMC_OPT_WRP_SECTOR_21  = (uint32_t)0x00000200,  /*!< Write protection of sector 21 */
    FMC_OPT_WRP_SECTOR_22  = (uint32_t)0x00000400,  /*!< Write protection of sector 22 */
    FMC_OPT_WRP_SECTOR_23  = (uint32_t)0x00000800,  /*!< Write protection of sector 23 */
    FMC_OPT_WRP_SECTOR_All = (uint32_t)0x00000FFF   /*!< Write protection of sector 24 */
} FMC_OPT_WRP_T;

/**
 * @brief FMC Option Bytes Read Protection
 */
typedef enum
{
    FMC_OPT_RDP_LV0 =(uint8_t)0xAA,     /*!< No protection */
    FMC_OPT_RDP_LV1 =(uint8_t)0x55      /*!< Read protection of the memory */
} FMC_OPT_RDP_T;

/**
 * @brief FMC Option Bytes Independent Watchdog
 */
typedef enum
{
    FMC_OPT_IWDT_SOFT = (uint8_t)0x20,  /*!< Software IWDT selected */
    FMC_OPT_IWDT_HARD = (uint8_t)0x00   /*!< Hardware IWDT selected */
} FMC_OPT_IWDT_T;

/**
 * @brief FMC Option Bytes nRST STOP
 */
typedef enum
{
    FMC_OPT_STOP_NORST = (uint8_t)0x40, /*!< No reset generated when entering in STOP */
    FMC_OPT_STOP_RST   = (uint8_t)0x00  /*!< Reset generated when entering in STOP */
} FMC_OPT_STOP_T;

/**
 * @brief FMC Option Bytes nRST STDBY
 */
typedef enum
{
    FMC_OPT_STDBY_NORST = (uint8_t)0x80,    /*!< No reset generated when entering in STANDBY */
    FMC_OPT_STDBY_RST   = (uint8_t)0x00     /*!< Reset generated when entering in STANDBY */
} FMC_OPT_STDBY_T;

/**
 * @brief FMC BOR Reset Level
 */
typedef enum
{
    FMC_OPT_BOR_LV3 = (uint8_t)0x00,    /*!< Supply voltage ranges from 2.7 to 3.6 V */
    FMC_OPT_BOR_LV2 = (uint8_t)0x04,    /*!< Supply voltage ranges from 2.4 to 2.7 V */
    FMC_OPT_BOR_LV1 = (uint8_t)0x08,    /*!< Supply voltage ranges from 2.1 to 2.4 V */
    FMC_OPT_BOR_OFF = (uint8_t)0x0C     /*!< Supply voltage ranges from 1.62 to 2.1 V */
} FMC_OPT_BOR_T;

/**
 * @brief FMC Dual Boot
 */
typedef enum
{
    FMC_OPT_BOOTEN  = (uint8_t)0x10,    /*!< Dual boot mode enable */
    FMC_OPT_BOOTDIS = (uint8_t)0x00     /*!< Dual boot mode disable */
} FMC_OPT_BOOT_T;

/**
 * @brief FMC Interrupts
 */
typedef enum
{
    FMC_INT_OC  = (uint32_t)0x01000000, /*!< Operation Complete Interrupt */
    FMC_INT_ERR = (uint32_t)0x02000000  /*!< Error Interrupt */
} FMC_INT_T;

/**
 * @brief FMC Flags
 */
typedef enum
{
    FMC_FLAG_ENDOP  = (uint32_t)0x00000001, /*!< FMC End of Operation flag */
    FMC_FLAG_ERROP  = (uint32_t)0x00000002, /*!< FMC operation Error flag */
    FMC_FLAG_ERRWRP = (uint32_t)0x00000010, /*!< FMC Write protected error flag */
    FMC_FLAG_ERRPGA = (uint32_t)0x00000020, /*!< FMC Programming Alignment error flag */
    FMC_FLAG_ERRPGP = (uint32_t)0x00000040, /*!< FMC Programming Parallelism error flag */
    FMC_FLAG_ERRPGS = (uint32_t)0x00000080, /*!< FMC Programming Sequence error flag */
    FMC_FLAG_BUSY   = (uint32_t)0x00010000  /*!< FMC Busy flag */
} FMC_FLAG_T;

/**
 * @brief FMC Program Parallelism
 */
typedef enum
{
    FMC_PSIZE_BYTE        = (uint32_t)0x00000000,   /*!< Set program parallelism to 8-bit */
    FMC_PSIZE_HALF_WORD   = (uint32_t)0x00000100,   /*!< Set program parallelism to 16-bit */
    FMC_PSIZE_WORD        = (uint32_t)0x00000200,   /*!< Set program parallelism to 32-bit */
    FMC_PSIZE_DOUBLE_WORD = (uint32_t)0x00000300    /*!< Set program parallelism to 64-bit */
} FMC_PSIZE_T;

/**@} end of group FMC_Enumerations*/

/** @defgroup FMC_Macros Macros
  @{
*/

#define PMC_RDP_KEY            ((uint16_t)0x00A5)
#define FMC_KEY1               ((uint32_t)0x45670123)
#define FMC_KEY2               ((uint32_t)0xCDEF89AB)
#define FMC_OPT_KEY1           ((uint32_t)0x08192A3B)
#define FMC_OPT_KEY2           ((uint32_t)0x4C5D6E7F)

/* FMC ACCTRL register Bits definition */
#define FMC_ACCTRL_PREFEN      ((uint32_t)0x00000100)
#define FMC_ACCTRL_ICACHEEN    ((uint32_t)0x00000200)
#define FMC_ACCTRL_DCACHEEN    ((uint32_t)0x00000400)
#define FMC_ACCTRL_ICACHERST   ((uint32_t)0x00000800)
#define FMC_ACCTRL_DCACHERST   ((uint32_t)0x00001000)

/* FMC CTRL register Bits definition */
#define FMC_CTRL_PG            ((uint32_t)0x00000001)
#define FMC_CTRL_SERS          ((uint32_t)0x00000002)
#define FMC_CTRL_MERS          ((uint32_t)0x00000004)
#define FMC_CTRL_SNUM          ((uint32_t)0x00000008)
#define FMC_CTRL_START         ((uint32_t)0x00010000)
#define FMC_CTRL_LOCK          ((uint32_t)0x80000000)

/* FMC OPTCTRL register Bits definition */
#define FMC_OPTCTRL_OPTLOCK    ((uint32_t)0x00000001)
#define FMC_OPTCTRL_OPTSTART   ((uint32_t)0x00000002)
#define FMC_OPTCTRL_BORLVL     ((uint32_t)0x0000000C)

/* ACCTRL  register byte 0 (Bits[7:0]) base address */
#define ACCTRL_BYTE0_ADDRESS          ((uint32_t)0x40023C00)

/* OPTCTRL register byte 0 (Bits[7:0]) base address */
#define OPTCTRL_BYTE0_ADDRESS         ((uint32_t)0x40023C14)

/* OPTCTRL register byte 1 (Bits[15:8]) base address */
#define OPTCTRL_BYTE1_ADDRESS         ((uint32_t)0x40023C15)

/* OPTCTRL register byte 2 (Bits[23:16]) base address */
#define OPTCTRL_BYTE2_ADDRESS         ((uint32_t)0x40023C16)

/* OPTCTRL register byte 3 (Bits[31:24]) base address */
#define OPTCTRL_BYTE3_ADDRESS         ((uint32_t)0x40023C17)

/**@} end of group FMC_Macros*/

/** @defgroup FMC_Functions
  @{
*/

/* FMC Interface configuration functions */
void FMC_ConfigLatency(FMC_LATENCY_T latency);
void FMC_EnablePrefetchBuffer(void);
void FMC_DisablePrefetchBuffer(void);
void FMC_EnableInstructionCache(void);
void FMC_DisableInstructionCache(void);
void FMC_EnableDataCache(void);
void FMC_DisableDataCache(void);
void FMC_ResetInstructionCache(void);
void FMC_ResetDataCache(void);

/* FMC Memory Programming functions */
void FMC_Unlock(void);
void FMC_Lock(void);
FMC_STATUS_T FMC_EraseSector(FMC_SECTOR_T sector, FMC_VOLTAGE_T voltageRange);
FMC_STATUS_T FMC_EraseAllSectors(FMC_VOLTAGE_T voltageRange);
FMC_STATUS_T FMC_ProgramDoubleWord(uint32_t address, uint64_t data);
FMC_STATUS_T FMC_ProgramWord(uint32_t address, uint32_t data);
FMC_STATUS_T FMC_ProgramHalfWord(uint32_t address, uint16_t data);
FMC_STATUS_T FMC_ProgramByte(uint32_t address, uint8_t data);

/* Option Bytes Programming functions */
void FMC_UnlockOptionByte(void);
void FMC_LockOptionByte(void);
void FMC_OPT_EnableWriteProtect(FMC_OPT_WRP_T wrp);
void FMC_OPT_DisableWriteProtect(FMC_OPT_WRP_T wrp);
void FMC_OPT_ConfigReadProtect(FMC_OPT_RDP_T rdp);
void FMC_OPT_ConfigUser(FMC_OPT_IWDT_T iwdt, FMC_OPT_STOP_T stop, FMC_OPT_STDBY_T stdby);
void FMC_OPT_ConfigBrownoutReset(FMC_OPT_BOR_T bor);
FMC_STATUS_T FMC_OPT_Launch(void);
uint8_t FMC_OPT_ReadUser(void);
uint16_t FMC_OPT_ReadWriteProtect(void);
uint8_t FMC_OPT_ReadProtectLevel(void);
uint8_t FMC_OPT_ReadBrownoutReset(void);

/* Interrupts and flags management functions */
void FMC_EnableInterrupt(uint32_t interrupt);
void FMC_DisableInterrupt(uint32_t interrupt);
uint8_t FMC_ReadStatusFlag(FMC_FLAG_T flag);
void FMC_ClearStatusFlag(uint32_t flag);
FMC_STATUS_T FMC_ReadStatus(void);
FMC_STATUS_T FMC_WaitForLastOperation(void);

#ifdef __cplusplus
}
#endif

#endif /* __APM32F4XX_FMC_H */

/**@} end of group FMC_Enumerations */
/**@} end of group FMC_Driver */
/**@} end of group APM32F4xx_StdPeriphDriver */
