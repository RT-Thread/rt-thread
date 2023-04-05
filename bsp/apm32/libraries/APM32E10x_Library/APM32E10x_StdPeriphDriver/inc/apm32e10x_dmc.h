/*!
 * @file        apm32e10x_dmc.h
 *
 * @brief       This file contains all the prototypes,enumeration and macros for the DMC peripheral
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
#ifndef __APM32E10X_DMC_H
#define __APM32E10X_DMC_H

/* Includes */
#include "apm32e10x.h"

#ifdef __cplusplus
 extern "C" {
#endif

/** @addtogroup APM32E10x_StdPeriphDriver
  @{
*/

/** @addtogroup DMC_Driver
  @{
*/

/** @defgroup DMC_Enumerations Enumerations
  @{
*/

/**
 * @brief   Bank Address Width
 */
typedef enum
{
    DMC_BANK_WIDTH_1,
    DMC_BANK_WIDTH_2
}DMC_BANK_WIDTH_T;

/**
 * @brief   Row Address Width
 */
typedef enum
{
    DMC_ROW_WIDTH_11 = 0x0A,
    DMC_ROW_WIDTH_12,
    DMC_ROW_WIDTH_13,
    DMC_ROW_WIDTH_14,
    DMC_ROW_WIDTH_15,
    DMC_ROW_WIDTH_16
}DMC_ROW_WIDTH_T;

/**
 * @brief   Column Address Width
 */
typedef enum
{
    DMC_COL_WIDTH_8 = 0x07,
    DMC_COL_WIDTH_9,
    DMC_COL_WIDTH_10,
    DMC_COL_WIDTH_11,
    DMC_COL_WIDTH_12,
    DMC_COL_WIDTH_13,
    DMC_COL_WIDTH_14,
    DMC_COL_WIDTH_15
}DMC_COL_WIDTH_T;

/**
 * @brief   CAS Latency Select
 */
typedef enum
{
    DMC_CAS_LATENCY_1,
    DMC_CAS_LATENCY_2,
    DMC_CAS_LATENCY_3,
    DMC_CAS_LATENCY_4
}DMC_CAS_LATENCY_T;

/**
 * @brief   RAS Minimun Time Select
 */
typedef enum
{
    DMC_RAS_MINIMUM_1,
    DMC_RAS_MINIMUM_2,
    DMC_RAS_MINIMUM_3,
    DMC_RAS_MINIMUM_4,
    DMC_RAS_MINIMUM_5,
    DMC_RAS_MINIMUM_6,
    DMC_RAS_MINIMUM_7,
    DMC_RAS_MINIMUM_8,
    DMC_RAS_MINIMUM_9,
    DMC_RAS_MINIMUM_10,
    DMC_RAS_MINIMUM_11,
    DMC_RAS_MINIMUM_12,
    DMC_RAS_MINIMUM_13,
    DMC_RAS_MINIMUM_14,
    DMC_RAS_MINIMUM_15,
    DMC_RAS_MINIMUM_16
}DMC_RAS_MINIMUM_T;

/**
 * @brief   RAS To CAS Delay Time Select
 */
typedef enum
{
    DMC_DELAY_TIME_1,
    DMC_DELAY_TIME_2,
    DMC_DELAY_TIME_3,
    DMC_DELAY_TIME_4,
    DMC_DELAY_TIME_5,
    DMC_DELAY_TIME_6,
    DMC_DELAY_TIME_7,
    DMC_DELAY_TIME_8
}DMC_DELAY_TIME_T;

/**
 * @brief   Precharge Period Select
 */
typedef enum
{
    DMC_PRECHARGE_1,
    DMC_PRECHARGE_2,
    DMC_PRECHARGE_3,
    DMC_PRECHARGE_4,
    DMC_PRECHARGE_5,
    DMC_PRECHARGE_6,
    DMC_PRECHARGE_7,
    DMC_PRECHARGE_8
}DMC_PRECHARGE_T;

/**
 * @brief   Last Data Next Precharge For Write Time Select 
 */
typedef enum
{
    DMC_NEXT_PRECHARGE_1,
    DMC_NEXT_PRECHARGE_2,
    DMC_NEXT_PRECHARGE_3,
    DMC_NEXT_PRECHARGE_4
}DMC_NEXT_PRECHARGE_T;

/**
 * @brief   Auto-Refresh Period Select
 */
typedef enum
{
    DMC_AUTO_REFRESH_1,
    DMC_AUTO_REFRESH_2,
    DMC_AUTO_REFRESH_3,
    DMC_AUTO_REFRESH_4,
    DMC_AUTO_REFRESH_5,
    DMC_AUTO_REFRESH_6,
    DMC_AUTO_REFRESH_7,
    DMC_AUTO_REFRESH_8,
    DMC_AUTO_REFRESH_9,
    DMC_AUTO_REFRESH_10,
    DMC_AUTO_REFRESH_11,
    DMC_AUTO_REFRESH_12,
    DMC_AUTO_REFRESH_13,
    DMC_AUTO_REFRESH_14,
    DMC_AUTO_REFRESH_15,
    DMC_AUTO_REFRESH_16
}DMC_AUTO_REFRESH_T;

/**
 * @brief   Active-to-active Command Period Select
 */
typedef enum
{
    DMC_ATA_CMD_1,
    DMC_ATA_CMD_2,
    DMC_ATA_CMD_3,
    DMC_ATA_CMD_4,
    DMC_ATA_CMD_5,
    DMC_ATA_CMD_6,
    DMC_ATA_CMD_7,
    DMC_ATA_CMD_8,
    DMC_ATA_CMD_9,
    DMC_ATA_CMD_10,
    DMC_ATA_CMD_11,
    DMC_ATA_CMD_12,
    DMC_ATA_CMD_13,
    DMC_ATA_CMD_14,
    DMC_ATA_CMD_15,
    DMC_ATA_CMD_16
}DMC_ATA_CMD_T;

/**
 * @brief   Clock PHASE
 */
typedef enum
{
    DMC_CLK_PHASE_NORMAL,
    DMC_CLK_PHASE_REVERSE
}DMC_CLK_PHASE_T;

/**
 * @brief   DMC Memory Size
 */
typedef enum
{
    DMC_MEMORY_SIZE_0,
    DMC_MEMORY_SIZE_64KB,
    DMC_MEMORY_SIZE_128KB,
    DMC_MEMORY_SIZE_256KB,
    DMC_MEMORY_SIZE_512KB,
    DMC_MEMORY_SIZE_1MB,
    DMC_MEMORY_SIZE_2MB,
    DMC_MEMORY_SIZE_4MB,
    DMC_MEMORY_SIZE_8MB,
    DMC_MEMORY_SIZE_16MB,
    DMC_MEMORY_SIZE_32MB,
    DMC_MEMORY_SIZE_64MB,
    DMC_MEMORY_SIZE_128MB,
    DMC_MEMORY_SIZE_256MB
}DMC_MEMORY_SIZE_T;

/**
 * @brief    Open Banks Of Number 
 */
typedef enum
{
    DMC_BANK_NUMBER_1,
    DMC_BANK_NUMBER_2,
    DMC_BANK_NUMBER_3,
    DMC_BANK_NUMBER_4,
    DMC_BANK_NUMBER_5,
    DMC_BANK_NUMBER_6,
    DMC_BANK_NUMBER_7,
    DMC_BANK_NUMBER_8,
    DMC_BANK_NUMBER_9,
    DMC_BANK_NUMBER_10,
    DMC_BANK_NUMBER_11,
    DMC_BANK_NUMBER_12,
    DMC_BANK_NUMBER_13,
    DMC_BANK_NUMBER_14,
    DMC_BANK_NUMBER_15,
    DMC_BANK_NUMBER_16
}DMC_BANK_NUMBER_T;

/**
 * @brief   Full refresh type
 */
typedef enum
{
    DMC_REFRESH_ROW_ONE,        /*!< Refresh one row */
    DMC_REFRESH_ROW_ALL         /*!< Refresh all row */
}DMC_REFRESH_T;

/**
 * @brief   Precharge type
 */
typedef enum
{
    DMC_PRECHARGE_IM,        /*!< Immediate precharge */
    DMC_PRECHARGE_DELAY      /*!< Delayed precharge */
}DMC_PRECHARE_T;

/**
 * @brief WRAP Burst Type
 */
typedef enum
{
    DMC_WRAPB_4,
    DMC_WRAPB_8
}DMC_WRPB_T;

/**@} end of group DMC_Enumerations */


/** @defgroup DMC_Structures Structures
  @{
*/

/**
 * @brief   Timing config definition
 */
typedef struct
{
    uint32_t    latencyCAS  : 2;       /*!< DMC_CAS_LATENCY_T */
    uint32_t    tRAS        : 4;       /*!< DMC_RAS_MINIMUM_T */
    uint32_t    tRCD        : 3;       /*!< DMC_DELAY_TIME_T */
    uint32_t    tRP         : 3;       /*!< DMC_PRECHARGE_T */
    uint32_t    tWR         : 2;       /*!< DMC_NEXT_PRECHARGE_T */
    uint32_t    tARP        : 4;       /*!< DMC_AUTO_REFRESH_T */
    uint32_t    tCMD        : 4;       /*!< DMC_ATA_CMD_T */
    uint32_t    tXSR        : 9;       /*!< auto-refresh commands, can be 0x000 to 0x1FF */
    uint16_t    tRFP        : 16;      /*!< Refresh period, can be 0x0000 to 0xFFFF */
}DMC_TimingConfig_T;

/**
 * @brief   Config struct definition
 */
typedef struct
{
    DMC_MEMORY_SIZE_T       memorySize;    /*!< Memory size(byte) */
    DMC_BANK_WIDTH_T        bankWidth;     /*!< Number of bank bits */
    DMC_ROW_WIDTH_T         rowWidth;      /*!< Number of row address bits */
    DMC_COL_WIDTH_T         colWidth;      /*!< Number of col address bits */
    DMC_CLK_PHASE_T         clkPhase;      /*!< Clock phase */
    DMC_TimingConfig_T      timing;        /*!< Timing */
}DMC_Config_T;

/**@} end of group DMC_Structures */


/** @defgroup DMC_Functions
  @{
*/

 /* Enable / Disable */
void DMC_Enable(void);
void DMC_Disable(void);
void DMC_EnableInit(void);

/* Global config */
void DMC_Config(DMC_Config_T *dmcConfig);
void DMC_ConfigStructInit(DMC_Config_T *dmcConfig);

/* Address */
void DMC_ConfigBankWidth(DMC_BANK_WIDTH_T bankWidth);
void DMC_ConfigAddrWidth(DMC_ROW_WIDTH_T rowWidth, DMC_COL_WIDTH_T colWidth);

/* Timing */
void DMC_ConfigTiming(DMC_TimingConfig_T *timingConfig);
void DMC_ConfigTimingStructInit(DMC_TimingConfig_T *timingConfig);
void DMC_ConfigStableTimePowerup(uint16_t stableTime);
void DMC_ConfigAutoRefreshNumDuringInit(DMC_AUTO_REFRESH_T num);
void DMC_ConfigRefreshPeriod(uint16_t period);

/* Refresh mode */
void DMC_EixtSlefRefreshMode(void);
void DMC_EnterSlefRefreshMode(void);

/* Accelerate Module */
void DMC_EnableAccelerateModule(void);
void DMC_DisableAccelerateModule(void);
/* Config */
void DMC_ConfigOpenBank(DMC_BANK_NUMBER_T num);
void DMC_EnableUpdateMode(void);
void DMC_EnterPowerdownMode(void);
void DMC_ConfigFullRefreshBeforeSR(DMC_REFRESH_T refresh);
void DMC_ConfigFullRefreshAfterSR(DMC_REFRESH_T refresh);
void DMC_ConfigPrechargeType(DMC_PRECHARE_T precharge);
void DMC_ConfigMemorySize(DMC_MEMORY_SIZE_T memorySize);
void DMC_ConfigClockPhase(DMC_CLK_PHASE_T clkPhase);
void DMC_ConfigWRAPB(DMC_WRPB_T burst);

/* read flag */
uint8_t DMC_ReadSelfRefreshStatus(void);

/**@} end of group DMC_Functions */
/**@} end of group DMC_Driver*/
/**@} end of group APM32E10x_StdPeriphDriver*/

#ifdef __cplusplus
}
#endif

#endif  /* __APM32E10X_DMC_H */
