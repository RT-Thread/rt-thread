/*!
 * @file        apm32f0xx_dbg.h
 *
 * @brief       This file contains all the functions prototypes for the DBG firmware library
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
#ifndef __APM32F0XX_DBG_H
#define __APM32F0XX_DBG_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes */
#include "apm32f0xx.h"

/** @addtogroup APM32F0xx_StdPeriphDriver
  @{
*/

/** @addtogroup DBG_Driver
  @{
*/

/** @defgroup DBG_Macros Macros
  @{
*/

/**@} end of group DBG_Macros*/

/** @defgroup DBG_Enumerations Enumerations
  @{
*/

/**
 * @brief   MCU Debug mode in the low power mode behavior
 */
typedef enum
{
    DBG_MODE_STOP    = ((uint32_t)0x02), /*!< Keep debugger connection during STOP mode */
    DBG_MODE_STANDBY = ((uint32_t)0x04), /*!< Keep debugger connection during STANDBY mode */
} DBG_MODE_T;

/**
 * @brief   MCU Debug mode in the APB1 peripheral behavior
 */
typedef enum
{
    DBG_APB1_PER_TMR2_STOP  = ((uint32_t)0x01),              /*!< TMR2 counter stopped when Core is halted (Only for APM32F072 and APM32F091 devices) */
    DBG_APB1_PER_TMR3_STOP  = ((uint32_t)0x02),              /*!< TMR3 counter stopped when Core is halted */
    DBG_APB1_PER_TMR6_STOP  = ((uint32_t)0x10),              /*!< TMR6 counter stopped when Core is halted */
    DBG_APB1_PER_TMR7_STOP  = ((uint32_t)0x20),              /*!< TMR7 counter stopped when Core is halted (Only for APM32F072 and APM32F091 devices) */
    DBG_APB1_PER_TMR14_STOP = ((uint32_t)0x100),             /*!< TMR14 counter stopped when Core is halted */
    DBG_APB1_PER_RTC_STOP   = ((uint32_t)0x400),             /*!< RTC counter stopped when Core is halted */
    DBG_APB1_PER_WWDT_STOP  = ((uint32_t)0x800),             /*!< Debug WWDT stopped when Core is halted */
    DBG_APB1_PER_IWDT_STOP  = ((uint32_t)0x1000),            /*!< Debug IWDT stopped when Core is halted */
    DBG_APB1_PER_CAN_STOP   = ((uint32_t)0x2000000),         /*!< Debug CAN stopped when Core is halted (Only for APM32F072 and APM32F091 devices) */
    DBG_APB1_PER_I2C1_SMBUS_TIMEOUT = ((uint32_t)0x200000),  /*!< I2C1 SMBUS timeout mode stopped when Core is halted */
} DBG_APB1_PER_T;

/**
 * @brief   MCU Debug mode in the APB2 peripheral behavior
 */
typedef enum
{
    DBG_APB2_PER_TMR1_STOP   = ((uint32_t)0x00800), /*!< TMR1 counter stopped when Core is halted */
    DBG_APB2_PER_TMR15_STOP  = ((uint32_t)0x10000), /*!< TMR15 counter stopped when Core is halted */
    DBG_APB2_PER_TMR16_STOP  = ((uint32_t)0x20000), /*!< TMR16 counter stopped when Core is halted */
    DBG_APB2_PER_TMR17_STOP  = ((uint32_t)0x40000), /*!< TMR17 counter stopped when Core is halted */
} DBG_APB2_PER_T;

/**@} end of group DBG_Enumerations */

/** @defgroup DBG_Structures Structures
  @{
*/

/**@} end of group DBG_Structures */

/** @defgroup DBG_Variables Variables
  @{
*/

/**@} end of group DBG_Variables */

/** @defgroup DBG_Functions Functions
  @{
*/

/* Read MCU ID Code  */
uint32_t DBG_ReadDevId(void);
uint32_t DBG_ReadRevId(void);

/* Debug Mode */
void DBG_EnableDebugMode(uint32_t mode);
void DBG_DisableDebugMode(uint32_t mode);

/* APB1 peripheral */
void DBG_EnableAPB1Periph(uint32_t peripheral);
void DBG_DisableAPB1Periph(uint32_t peripheral);

/* APB2 peripheral */
void DBG_EnableAPB2Periph(uint32_t peripheral);
void DBG_DisableAPB2Periph(uint32_t peripheral);

#ifdef __cplusplus
}
#endif

#endif /* __APM32F0XX_DBG_H */

/**@} end of group DBG_Functions */
/**@} end of group DBG_Driver */
/**@} end of group APM32F0xx_StdPeriphDriver */
