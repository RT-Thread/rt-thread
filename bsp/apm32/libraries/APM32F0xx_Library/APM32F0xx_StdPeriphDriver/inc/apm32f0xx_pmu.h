/*!
 * @file        apm32f0xx_pmu.h
 *
 * @brief       This file contains all functions prototype and macros for the PMU peripheral
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

#ifndef __APM32F0XX_PMU_H
#define __APM32F0XX_PMU_H

#ifdef __cplusplus
extern "C" {
#endif

#include "apm32f0xx.h"

/** @addtogroup APM32F0xx_StdPeriphDriver
  @{
*/

/** @addtogroup PMU_Driver PMU Driver
  @{
*/

/** @defgroup PMU_Macros Macros
  @{
*/

/**@} end of group PMU_Macros */

/** @defgroup PMU_Enumerations Enumerations
  @{
*/

/**
 * @brief   PVD detection level (Not for APM32F030 devices)
 */
typedef enum
{
    PMU_PVDLEVEL_0 = ((uint8_t)0x00),    /*!< PVD detection level set to 2.2V */
    PMU_PVDLEVEL_1 = ((uint8_t)0x01),    /*!< PVD detection level set to 2.3V */
    PMU_PVDLEVEL_2 = ((uint8_t)0x02),    /*!< PVD detection level set to 2.4V */
    PMU_PVDLEVEL_3 = ((uint8_t)0x03),    /*!< PVD detection level set to 2.5V */
    PMU_PVDLEVEL_4 = ((uint8_t)0x04),    /*!< PVD detection level set to 2.6V */
    PMU_PVDLEVEL_5 = ((uint8_t)0x05),    /*!< PVD detection level set to 2.7V */
    PMU_PVDLEVEL_6 = ((uint8_t)0x06),    /*!< PVD detection level set to 2.8V */
    PMU_PVDLEVEL_7 = ((uint8_t)0x07),    /*!< PVD detection level set to 2.9V */
} PMU_PVDLEVEL_T;


/**
 * @brief   Wake Up PIN
 */
typedef enum
{
    PMU_WAKEUPPIN_1 = ((uint16_t)0x0100),  /*!< PIN_1 wakeup mcu */
    PMU_WAKEUPPIN_2 = ((uint16_t)0x0200),  /*!< PIN_2 wakeup mcu */
    PMU_WAKEUPPIN_3 = ((uint16_t)0x0400),  /*!< PIN_3 wakeup mcu, only for APM32F072/091 devices */
    PMU_WAKEUPPIN_4 = ((uint16_t)0x0800),  /*!< PIN_4 wakeup mcu, only for APM32F072/091 devices */
    PMU_WAKEUPPIN_5 = ((uint16_t)0x1000),  /*!< PIN_5 wakeup mcu , only for APM32F072/091 devices */
    PMU_WAKEUPPIN_6 = ((uint16_t)0x2000),  /*!< PIN_6, only for APM32F072/091 devices */
    PMU_WAKEUPPIN_7 = ((uint16_t)0x4000),  /*!< PIN_7, only for APM32F072/091 devices */
    PMU_WAKEUPPIN_8 = ((uint16_t)0x8000),  /*!< PIN_8, only for APM32F072/091 devices */
} PMU_WAKEUPPIN_T;

/**
 * @brief   Sleep mode entry
 */
typedef enum
{
    PMU_SLEEPENTRY_WFI = 0x00,  /*!< enter SLEEP mode with WFI instruction */
    PMU_SLEEPENTRY_WFE = 0x01,  /*!< enter SLEEP mode with WFE instruction */
} PMU_SLEEPENTRY_T;

/**
 * @brief   Regulator state is Sleep/Stop mode
 */
typedef enum
{
    PMU_REGULATOR_ON = 0x00,         /*!< STOP mode with regulator ON */
    PMU_REGULATOR_LowPower = 0x01,   /*!< STOP mode with regulator in low power mode */
} PMU_REGULATOR_T;

/**
 * @brief   Stop mode entry
 */
typedef enum
{
    PMU_STOPENTRY_WFI = 0x00,             /*!< Enter STOP mode with WFI instruction */
    PMU_STOPENTRY_WFE = 0x01,             /*!< Enter STOP mode with WFE instruction */
    PMU_STOPENTRY_SLEEPONEXIT = 0x02,     /*!< Enter STOP mode with SLEEPONEXIT instruction */
} PMU_STOPENTRY_T;

/**
 * @brief   Flag
 */
typedef enum
{
    PMU_FLAG_WUPF      = 0x01,  /*!< Wake Up flag */
    PMU_FLAG_STDBYF    = 0x02,  /*!< StandBy flag */
    PMU_FLAG_PVDOF     = 0x04, /*!< Not for APM32F030 devices */
    PMU_FLAG_VREFINTF  = 0x08,  /*!<VREFINT flag */
} PMU_FLAG_T;

/**@} end of group PMU_Enumerations*/

/** @defgroup PMU_Structures Structures
  @{
*/

/**@} end of group PMU_Structures */

/** @defgroup PMU_Variables Variables
  @{
*/

/**@} end of group PMU_Variables */

/** @defgroup PMU_Fuctions Fuctions
  @{
*/

/** Function used to set the PMU configuration to the default reset state */
void PMU_Reset(void);

/** Backup Domain Access function */
void PMU_EnableBackupAccess(void);
void PMU_DisableBackupAccess(void);

/** PVD configuration functions */
void PMU_ConfigPVDLevel(PMU_PVDLEVEL_T level);  /*!< Not for APM32F030 devices */
void PMU_EnablePVD(void);                       /*!< Not for APM32F030 devices */
void PMU_DisablePVD(void);                      /*!< Not for APM32F030 devices */

/** WakeUp pins configuration functions */
void PMU_EnableWakeUpPin(PMU_WAKEUPPIN_T pin);
void PMU_DisableWakeUpPin(PMU_WAKEUPPIN_T pin);

/** Low Power modes configuration functions */
void PMU_EnterSleepMode(PMU_SLEEPENTRY_T entry);
void PMU_EnterSTOPMode(PMU_REGULATOR_T regulator, PMU_STOPENTRY_T entry);
void PMU_EnterSTANDBYMode(void);

/** Flags management functions */
uint8_t PMU_ReadStatusFlag(PMU_FLAG_T flag);
void PMU_ClearStatusFlag(uint8_t flag);

#ifdef __cplusplus
}
#endif

#endif /* __APM32F0XX_PMU_H */

/**@} end of group PMU_Functions */
/**@} end of group PMU_Driver */
/**@} end of group APM32F0xx_StdPeriphDriver */
