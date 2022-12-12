/*!
 * @file        apm32f4xx_pmu.h
 *
 * @brief       This file contains all the functions prototypes for the PMU firmware library.
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
#ifndef __APM32F4XX_PMU_H
#define __APM32F4XX_PMU_H

#ifdef __cplusplus
  extern "C" {
#endif

/* Includes */
#include "apm32f4xx.h"

/** @addtogroup APM32F4xx_StdPeriphDriver
  @{
*/

/** @addtogroup PMU_Driver
  @{
*/

/** @defgroup PMU_Enumerations
  @{
*/

/**
 * @brief PMU PVD detection level
 */
typedef enum
{
    PMU_PVD_LEVEL_2V0    = 0x00,    /*!< PVD detection level set to 2.0V */
    PMU_PVD_LEVEL_2V1    = 0x01,    /*!< PVD detection level set to 2.1V */
    PMU_PVD_LEVEL_2V3    = 0x02,    /*!< PVD detection level set to 2.3V */
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
    PMU_REGULATOR_ON       = 0x00,  /*!< STOP mode with regulator ON */
    PMU_REGULATOR_LOWPOWER = 0x01   /*!< STOP mode with regulator in low power mode */
} PMU_REGULATOR_T;

/**
 * @brief PMU STOP mode entry
 */
typedef enum
{
    PMU_STOP_ENTRY_WFI     = 0x01,  /*!< Enter STOP mode with WFI instruction */
    PMU_STOP_ENTRY_WFE     = 0x02   /*!< Enter STOP mode with WFE instruction */
} PMU_STOP_ENTRY_T;

/**
 * @brief PMU Regulator Voltage Scale
 */
typedef enum
{
    PMU_REGULATOR_VOLTAGE_SCALE1 = 0x03,    /*!< Select regulator voltage scale 1 */
    PMU_REGULATOR_VOLTAGE_SCALE2 = 0x02,    /*!< Select regulator voltage scale 2 */
    PMU_REGULATOR_VOLTAGE_SCALE3 = 0x01,    /*!< Select regulator voltage scale 3 */
} PMU_REGULATOR_VOLTAGE_SCALE_T;

/**
 * @brief PMU Flag
 */
typedef enum
{
    PMU_FLAG_WUE,   /*!< Wake Up flag */
    PMU_FLAG_SB,    /*!< StandBy flag */
    PMU_FLAG_PVDO,  /*!< PVD Output */
    PMU_FLAG_BKPR,  /*!< Backup regulator ready flag */
    PMU_FLAG_VOSR   /*!< This flag indicates that the Regulator voltage
                            scaling output selection is ready */
} PMU_FLAG_T;

/**@} end of group PMU_Enumerations*/

/** @defgroup PMU_Functions
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
void PMU_EnableBackupRegulator(void);
void PMU_DisableBackupRegulator(void);
void PMU_ConfigMainRegulatorMode(PMU_REGULATOR_VOLTAGE_SCALE_T scale);
void PMU_EnableFlashPowerDown(void);
void PMU_DisableFlashPowerDown(void);
void PMU_EnterSTOPMode(PMU_REGULATOR_T regulator, PMU_STOP_ENTRY_T entry);
void PMU_EnterSTANDBYMode(void);

/* flags */
uint8_t PMU_ReadStatusFlag(PMU_FLAG_T flag);
void PMU_ClearStatusFlag(PMU_FLAG_T flag);

#ifdef __cplusplus
}
#endif

#endif /* __APM32F4XX_PMU_H */

/**@} end of group PMU_Enumerations */
/**@} end of group PMU_Driver */
/**@} end of group APM32F4xx_StdPeriphDriver */
