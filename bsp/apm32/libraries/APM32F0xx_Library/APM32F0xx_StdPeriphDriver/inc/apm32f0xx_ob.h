/*!
 * @file        apm32f0xx_ob.h
 *
 * @brief       This file contains all the functions prototypes for the OB firmware library
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
#ifndef __APM32F0XX_OB_H
#define __APM32F0XX_OB_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes */
#include "apm32f0xx.h"

/** @addtogroup APM32F0xx_StdPeriphDriver
  @{
*/

/** @addtogroup OB_Driver
  @{
*/

/** @defgroup OB_Macros Macros
  @{
*/

/**@} end of group OB_Macros*/


/** @defgroup OB_Enumerations Enumerations
  @{
*/

/**
 * @brief   Read protection option byte
 */
typedef enum
{
    OB_READ_PRO_LEVEL0  = 0xAA, /*!< No protection */
    OB_READ_PRO_LEVEL1  = 0xBB, /*!< Read protection of the memory */
} OB_READ_PRO_T;

/**
 * @brief Option Bytes Watchdog
 */
typedef enum
{
    OB_WDG_HW = ((uint8_t)0), /*!< Hardware Watchdog */
    OB_WDG_SW = ((uint8_t)1), /*!< Software Watchdog */
} OB_WDT_T;

/**
 * @brief Option Bytes nRST STOP
 */
typedef enum
{
    OB_STOP_RESET = ((uint8_t)0), /*!< Reset Stop mode */
    OB_STOP_SET = ((uint8_t)1),   /*!< Into Stop mode */
} OB_STOP_T;

/**
 * @brief Option Bytes nRST Standby
 */
typedef enum
{
    OB_STANDBY_RST = ((uint8_t)0), /*!< Reset STANDBY mode */
    OB_STANDBY_SET = ((uint8_t)1), /*!< Into STANDBY mode */
} OB_STANDBY_T;

/**
 * @brief Option Bytes nBOOT1
 */
typedef enum
{
    OB_BOOT1_RST = ((uint8_t)0), /*!< Reset BOOT1 */
    OB_BOOT1_SET = ((uint8_t)1), /*!< Into BOOT1 */
} OB_BOOT1_T;

/**
 * @brief Option Bytes VDDA_Analog_Monitoring
 */
typedef enum
{
    OB_VDDA_OFF = ((uint8_t)0), /*!< VDDA_Analog_Monitoring off */
    OB_VDDA_ON  = ((uint8_t)1), /*!< VDDA_Analog_Monitoring on */
} OB_VDDA_T;

/**
 * @brief Option Bytes RAM PARITY CHECK
 */
typedef enum
{
    OB_RAM_PARITY_CHECK_ENABLE  = ((uint8_t)0), /*!< Enable Option Bytes RAM PARITY CHECK*/
    OB_RAM_PARITY_CHECK_DISABLE = ((uint8_t)1), /*!< Disbale Option Bytes RAM PARITY CHECK */
} OB_RAM_PARITY_CHECK_T;

/**@} end of group OB_Enumerations*/

/** @defgroup OB_Structures Structures
  @{
*/

/**
 * @brief   User Option byte config struct definition
 */
typedef struct
{
    OB_READ_PRO_T  readProtection;         /*!< Read protection option byte */
    OB_WDT_T       wdt;                    /*!< Watch dog activation */
    OB_STOP_T      stop;                   /*!< Option Bytes nRST STOP */
    OB_STANDBY_T   stdby;                  /*!< Option Bytes nRST STDBY */
    OB_BOOT1_T     boot;                   /*!< Option Bytes nBOOT1 */
    OB_VDDA_T      vdda;                   /*!< Option Bytes nRST STOP */
    OB_RAM_PARITY_CHECK_T  ramParityCheck; /*!< Option Bytes RAM PARITY CHECK */
} OB_UserConfig_T;

/**@} end of group OB_Structures*/

/** @defgroup OB_Variables Variables
  @{
*/

/**@} end of group OB_Variables*/

/** @defgroup OB_Functions Functions
  @{
*/

/* Read protection option byte */
void OB_ReadProtectionOptionByte(OB_READ_PRO_T readProtection);

/* Option Bytes Watchdog */
void OB_OptionBytesWatchdog(OB_WDT_T wdt);

/* Option Bytes nRST STOP */
void OB_OptionBytesStop(OB_STOP_T stop);

/* Option Bytes nRST STDBY */
void OB_OptionBytesStandby(OB_STANDBY_T standby);

/* Option Bytes nBOOT1 */
void OB_OptionBytesBoot1(OB_BOOT1_T boot);

/* Option Bytes VDDA_Analog_Monitoring */
void OB_OptionBytesVddaAnalog(OB_VDDA_T vdda);

/* Option Bytes RAM PARITY CHECK  */
void OB_OptionBytesRamParity(OB_RAM_PARITY_CHECK_T ramParityCheck);

#ifdef __cplusplus
}
#endif

#endif /* __APM32F0XX_OB_H */

/**@} end of group OB_Functions*/
/**@} end of group OB_Driver */
/**@} end of group APM32F0xx_StdPeriphDriver*/
