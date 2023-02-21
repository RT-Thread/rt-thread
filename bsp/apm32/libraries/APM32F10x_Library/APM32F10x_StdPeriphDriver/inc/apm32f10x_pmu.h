/*!
 * @file        apm32f10x_pmu.h
 *
 * @brief       This file contains all the functions prototypes for the PMU firmware library.
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
#ifndef __APM32F10X_PMU_H
#define __APM32F10X_PMU_H

/* Includes */
#include "apm32f10x.h"

#ifdef __cplusplus
extern "C" {
#endif

/** @addtogroup APM32F10x_StdPeriphDriver
  @{
*/

/** @addtogroup PMU_Driver PMU Driver
  @{
*/

/** @defgroup PMU_Enumerations Enumerations
  @{
*/

/**
 * @brief PMU PVD detection level
 */
typedef enum
{
    PMU_PVD_LEVEL_2V2    = 0x00,    /*!< PVD detection level set to 2.2V */
    PMU_PVD_LEVEL_2V3    = 0x01,    /*!< PVD detection level set to 2.3V */
    PMU_PVD_LEVEL_2V4    = 0x02,    /*!< PVD detection level set to 2.4V */
    PMU_PVD_LEVEL_2V5    = 0x03,    /*!< PVD detection level set to 2.5V */
    PMU_PVD_LEVEL_2V6    = 0x04,    /*!< PVD detection level set to 2.6V */
    PMU_PVD_LEVEL_2V7    = 0x05,    /*!< PVD detection level set to 2.7V */
    PMU_PVD_LEVEL_2V8    = 0x06,    /*!< PVD detection level set to 2.8V */
    PMU_PVD_LEVEL_2V9    = 0x07,    /*!< PVD detection level set to 2.9V */
} PMU_PVD_LEVEL_T;

/**
 * @brief PMU Regulator state in STOP mode
 */
typedef enum
{
    PMU_REGULATOR_ON       = 0x00,
    PMU_REGULATOR_LOWPOWER = 0x01
} PMU_REGULATOR_T;

/**
 * @brief PMU STOP mode entry
 */
typedef enum
{
    PMU_STOP_ENTRY_WFI     = 0x01,
    PMU_STOP_ENTRY_WFE     = 0x02
} PMU_STOP_ENTRY_T;

/**
 * @brief PMU Flag
 */
typedef enum
{
    PMU_FLAG_WUE,
    PMU_FLAG_SB,
    PMU_FLAG_PVDO
} PMU_FLAG_T;

/**@} end of group PMU_Enumerations*/


/** @addtogroup PMU_Functions Functions
  @{
*/

/* PMU Reset */
void PMU_Reset(void);

/* Configuration and Operation modes */
void PMU_EnableBackupAccess(void);
void PMU_DisableBackupAccess(void);
void PMU_EnablePVD(void);
void PMU_DisablePVD(void);
void PMU_ConfigPVDLevel(PMU_PVD_LEVEL_T level);
void PMU_EnableWakeUpPin(void);
void PMU_DisableWakeUpPin(void);
void PMU_EnterSTOPMode(PMU_REGULATOR_T regulator, PMU_STOP_ENTRY_T entry);
void PMU_EnterSTANDBYMode(void);

/* flags */
uint8_t PMU_ReadStatusFlag(PMU_FLAG_T flag);
void PMU_ClearStatusFlag(PMU_FLAG_T flag);

/**@} end of group PMU_Functions*/
/**@} end of group PMU_Driver */
/**@} end of group APM32F10x_StdPeriphDriver*/

#ifdef __cplusplus
}
#endif

#endif /* __APM32F10X_PMU_H */
