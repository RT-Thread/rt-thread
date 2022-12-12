/*!
 * @file        apm32f4xx_dmc.h
 *
 * @brief       This file contains all the prototypes,enumeration and macros for the DMC peripheral
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
#ifndef __APM32F4XX_DMC_H
#define __APM32F4XX_DMC_H

#ifdef __cplusplus
  extern "C" {
#endif

/* Includes */
#include "apm32f4xx.h"

/** @addtogroup APM32F4xx_StdPeriphDriver
  @{
*/

/** @addtogroup DMC_Driver
  @{
*/

/** @defgroup DMC_Enumerations
  @{
*/

/**
 * @brief Bank Address Width
 */
typedef enum
{
    DMC_BANK_WIDTH_1,   /*!< Set bank address width to 1-bit */
    DMC_BANK_WIDTH_2    /*!< Set bank address width to 2-bit */
} DMC_BANK_WIDTH_T;

/**
 * @brief Row Address Width
 */
typedef enum
{
    DMC_ROW_WIDTH_11 = 0x0A,    /*!< Set row address width to 11-bit */
    DMC_ROW_WIDTH_12,           /*!< Set row address width to 12-bit */
    DMC_ROW_WIDTH_13,           /*!< Set row address width to 13-bit */
    DMC_ROW_WIDTH_14,           /*!< Set row address width to 14-bit */
    DMC_ROW_WIDTH_15,           /*!< Set row address width to 15-bit */
    DMC_ROW_WIDTH_16            /*!< Set row address width to 16-bit */
} DMC_ROW_WIDTH_T;

/**
 * @brief Column Address Width
 */
typedef enum
{
    DMC_COL_WIDTH_8 = 0x07, /*!< Set column address width to 8-bit */
    DMC_COL_WIDTH_9,        /*!< Set column address width to 9-bit */
    DMC_COL_WIDTH_10,       /*!< Set column address width to 10-bit */
    DMC_COL_WIDTH_11,       /*!< Set column address width to 11-bit */
    DMC_COL_WIDTH_12,       /*!< Set column address width to 12-bit */
    DMC_COL_WIDTH_13,       /*!< Set column address width to 13-bit */
    DMC_COL_WIDTH_14,       /*!< Set column address width to 14-bit */
    DMC_COL_WIDTH_15        /*!< Set column address width to 15-bit */
} DMC_COL_WIDTH_T;

/**
 * @brief CAS Latency Select
 */
typedef enum
{
    DMC_CAS_LATENCY_1,  /*!< Set CAS lantency to 1 clock */
    DMC_CAS_LATENCY_2,  /*!< Set CAS lantency to 2 clock */
    DMC_CAS_LATENCY_3,  /*!< Set CAS lantency to 3 clock */
    DMC_CAS_LATENCY_4   /*!< Set CAS lantency to 4 clock */
} DMC_CAS_LATENCY_T;

/**
 * @brief RAS Minimun Time Select
 */
typedef enum
{
    DMC_RAS_MINIMUM_1,  /*!< Set RAS minimun time to 1 clock */
    DMC_RAS_MINIMUM_2,  /*!< Set RAS minimun time to 2 clock */
    DMC_RAS_MINIMUM_3,  /*!< Set RAS minimun time to 3 clock */
    DMC_RAS_MINIMUM_4,  /*!< Set RAS minimun time to 4 clock */
    DMC_RAS_MINIMUM_5,  /*!< Set RAS minimun time to 5 clock */
    DMC_RAS_MINIMUM_6,  /*!< Set RAS minimun time to 6 clock */
    DMC_RAS_MINIMUM_7,  /*!< Set RAS minimun time to 7 clock */
    DMC_RAS_MINIMUM_8,  /*!< Set RAS minimun time to 8 clock */
    DMC_RAS_MINIMUM_9,  /*!< Set RAS minimun time to 9 clock */
    DMC_RAS_MINIMUM_10, /*!< Set RAS minimun time to 10 clock */
    DMC_RAS_MINIMUM_11, /*!< Set RAS minimun time to 11 clock */
    DMC_RAS_MINIMUM_12, /*!< Set RAS minimun time to 12 clock */
    DMC_RAS_MINIMUM_13, /*!< Set RAS minimun time to 13 clock */
    DMC_RAS_MINIMUM_14, /*!< Set RAS minimun time to 14 clock */
    DMC_RAS_MINIMUM_15, /*!< Set RAS minimun time to 15 clock */
    DMC_RAS_MINIMUM_16  /*!< Set RAS minimun time to 16 clock */
} DMC_RAS_MINIMUM_T;

/**
 * @brief RAS To CAS Delay Time Select
 */
typedef enum
{
    DMC_DELAY_TIME_1,   /*!< Set RAS to CAS delay time to 1 clock */
    DMC_DELAY_TIME_2,   /*!< Set RAS to CAS delay time to 2 clock */
    DMC_DELAY_TIME_3,   /*!< Set RAS to CAS delay time to 3 clock */
    DMC_DELAY_TIME_4,   /*!< Set RAS to CAS delay time to 4 clock */
    DMC_DELAY_TIME_5,   /*!< Set RAS to CAS delay time to 5 clock */
    DMC_DELAY_TIME_6,   /*!< Set RAS to CAS delay time to 6 clock */
    DMC_DELAY_TIME_7,   /*!< Set RAS to CAS delay time to 7 clock */
    DMC_DELAY_TIME_8    /*!< Set RAS to CAS delay time to 8 clock */
} DMC_DELAY_TIME_T;

/**
 * @brief Precharge Period Select
 */
typedef enum
{
    DMC_PRECHARGE_1,    /*!< Set precharge period to 1 clock */
    DMC_PRECHARGE_2,    /*!< Set precharge period to 2 clock */
    DMC_PRECHARGE_3,    /*!< Set precharge period to 3 clock */
    DMC_PRECHARGE_4,    /*!< Set precharge period to 4 clock */
    DMC_PRECHARGE_5,    /*!< Set precharge period to 5 clock */
    DMC_PRECHARGE_6,    /*!< Set precharge period to 6 clock */
    DMC_PRECHARGE_7,    /*!< Set precharge period to 7 clock */
    DMC_PRECHARGE_8     /*!< Set precharge period to 8 clock */
} DMC_PRECHARGE_T;

/**
 * @brief Last Data Next Precharge For Write Time Select
 */
typedef enum
{
    DMC_NEXT_PRECHARGE_1,   /*!< Set time between the last data and
                                next precharge for write to 1 clock */
    DMC_NEXT_PRECHARGE_2,   /*!< Set time between the last data and
                                next precharge for write to 2 clock */
    DMC_NEXT_PRECHARGE_3,   /*!< Set time between the last data and
                                next precharge for write to 3 clock */
    DMC_NEXT_PRECHARGE_4    /*!< Set time between the last data and
                                next precharge for write to 4 clock */
} DMC_NEXT_PRECHARGE_T;

/**
 * @brief Auto-Refresh Period Select
 */
typedef enum
{
    DMC_AUTO_REFRESH_1,     /*!< Set auto-refresh period to 1 clock */
    DMC_AUTO_REFRESH_2,     /*!< Set auto-refresh period to 2 clock */
    DMC_AUTO_REFRESH_3,     /*!< Set auto-refresh period to 3 clock */
    DMC_AUTO_REFRESH_4,     /*!< Set auto-refresh period to 4 clock */
    DMC_AUTO_REFRESH_5,     /*!< Set auto-refresh period to 5 clock */
    DMC_AUTO_REFRESH_6,     /*!< Set auto-refresh period to 6 clock */
    DMC_AUTO_REFRESH_7,     /*!< Set auto-refresh period to 7 clock */
    DMC_AUTO_REFRESH_8,     /*!< Set auto-refresh period to 8 clock */
    DMC_AUTO_REFRESH_9,     /*!< Set auto-refresh period to 9 clock */
    DMC_AUTO_REFRESH_10,    /*!< Set auto-refresh period to 10 clock */
    DMC_AUTO_REFRESH_11,    /*!< Set auto-refresh period to 11 clock */
    DMC_AUTO_REFRESH_12,    /*!< Set auto-refresh period to 12 clock */
    DMC_AUTO_REFRESH_13,    /*!< Set auto-refresh period to 13 clock */
    DMC_AUTO_REFRESH_14,    /*!< Set auto-refresh period to 14 clock */
    DMC_AUTO_REFRESH_15,    /*!< Set auto-refresh period to 15 clock */
    DMC_AUTO_REFRESH_16,    /*!< Set auto-refresh period to 16 clock */
} DMC_AUTO_REFRESH_T;

/**
 * @brief Active-to-active Command Period Select
 */
typedef enum
{
    DMC_ATA_CMD_1,  /*!< Set active to active command period to 1 clock */
    DMC_ATA_CMD_2,  /*!< Set active to active command period to 2 clock */
    DMC_ATA_CMD_3,  /*!< Set active to active command period to 3 clock */
    DMC_ATA_CMD_4,  /*!< Set active to active command period to 4 clock */
    DMC_ATA_CMD_5,  /*!< Set active to active command period to 5 clock */
    DMC_ATA_CMD_6,  /*!< Set active to active command period to 6 clock */
    DMC_ATA_CMD_7,  /*!< Set active to active command period to 7 clock */
    DMC_ATA_CMD_8,  /*!< Set active to active command period to 8 clock */
    DMC_ATA_CMD_9,  /*!< Set active to active command period to 9 clock */
    DMC_ATA_CMD_10, /*!< Set active to active command period to 10 clock */
    DMC_ATA_CMD_11, /*!< Set active to active command period to 11 clock */
    DMC_ATA_CMD_12, /*!< Set active to active command period to 12 clock */
    DMC_ATA_CMD_13, /*!< Set active to active command period to 13 clock */
    DMC_ATA_CMD_14, /*!< Set active to active command period to 14 clock */
    DMC_ATA_CMD_15, /*!< Set active to active command period to 15 clock */
    DMC_ATA_CMD_16, /*!< Set active to active command period to 16 clock */
} DMC_ATA_CMD_T;

/**
 * @brief Clock PHASE
 */
typedef enum
{
    DMC_CLK_PHASE_NORMAL,   /*!< Clock phase is normal */
    DMC_CLK_PHASE_REVERSE   /*!< Clock phase is reverse */
} DMC_CLK_PHASE_T;

/**
 * @brief    Open Banks Of Number
 */
typedef enum
{
    DMC_BANK_NUMBER_1,  /*!< Set 1 bank be opened */
    DMC_BANK_NUMBER_2,  /*!< Set 2 banks be opened */
    DMC_BANK_NUMBER_3,  /*!< Set 3 banks be opened */
    DMC_BANK_NUMBER_4,  /*!< Set 4 banks be opened */
    DMC_BANK_NUMBER_5,  /*!< Set 5 banks be opened */
    DMC_BANK_NUMBER_6,  /*!< Set 6 banks be opened */
    DMC_BANK_NUMBER_7,  /*!< Set 7 banks be opened */
    DMC_BANK_NUMBER_8,  /*!< Set 8 banks be opened */
    DMC_BANK_NUMBER_9,  /*!< Set 9 banks be opened */
    DMC_BANK_NUMBER_10, /*!< Set 10 banks be opened */
    DMC_BANK_NUMBER_11, /*!< Set 11 banks be opened */
    DMC_BANK_NUMBER_12, /*!< Set 12 banks be opened */
    DMC_BANK_NUMBER_13, /*!< Set 13 banks be opened */
    DMC_BANK_NUMBER_14, /*!< Set 14 banks be opened */
    DMC_BANK_NUMBER_15, /*!< Set 15 banks be opened */
    DMC_BANK_NUMBER_16, /*!< Set 16 banks be opened */
} DMC_BANK_NUMBER_T;

/**
 * @brief Full refresh type
 */
typedef enum
{
    DMC_REFRESH_ROW_ONE,        /*!< Refresh one row */
    DMC_REFRESH_ROW_ALL,        /*!< Refresh all row */
} DMC_REFRESH_T;

/**
 * @brief Precharge type
 */
typedef enum
{
    DMC_PRECHARGE_IM,        /*!< Immediate precharge */
    DMC_PRECHARGE_DELAY,     /*!< Delayed precharge */
} DMC_PRECHARE_T;

/**
 * @brief WRAP Burst Type
 */
typedef enum
{
    DMC_WRAPB_4,    /*!< Wrap4 burst transfer */
    DMC_WRAPB_8,    /*!< Wrap8 burst transfer */
} DMC_WRPB_T;

/**@} end of group DMC_Enumerations*/

/** @addtogroup DMC_Structure Data Structure
  @{
*/

/**
 * @brief Timing config definition
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
} DMC_TimingConfig_T;

/**
 * @brief Config struct definition
 */
typedef struct
{
    DMC_BANK_WIDTH_T        bankWidth;     /*!< Number of bank bits */
    DMC_ROW_WIDTH_T         rowWidth;      /*!< Number of row address bits */
    DMC_COL_WIDTH_T         colWidth;      /*!< Number of col address bits */
    DMC_CLK_PHASE_T         clkPhase;      /*!< Clock phase */
    DMC_TimingConfig_T      timing;        /*!< Timing */
} DMC_Config_T;

/**@} end of group DMC_Structure*/

/** @defgroup DMC_Functions
  @{
*/

/* Enable / Disable */
void DMC_Enable(void);
void DMC_Disable(void);
void DMC_EnableInit(void);

/* Global config */
void DMC_Config(DMC_Config_T* dmcConfig);
void DMC_ConfigStructInit(DMC_Config_T* dmcConfig);

/* Address */
void DMC_ConfigBankWidth(DMC_BANK_WIDTH_T bankWidth);
void DMC_ConfigAddrWidth(DMC_ROW_WIDTH_T rowWidth, DMC_COL_WIDTH_T colWidth);

/* Timing */
void DMC_ConfigTiming(DMC_TimingConfig_T* timingConfig);
void DMC_ConfigTimingStructInit(DMC_TimingConfig_T* timingConfig);
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
void DMC_ConfigClockPhase(DMC_CLK_PHASE_T clkPhase);
void DMC_ConfigWRAPB(DMC_WRPB_T burst);

/* read flag */
uint8_t DMC_ReadSelfRefreshStatus(void);

#ifdef __cplusplus
}
#endif

#endif  /* __APM32F4XX_DMC_H */

/**@} end of group DMC_Enumerations */
/**@} end of group DMC_Driver */
/**@} end of group APM32F4xx_StdPeriphDriver */
