/*!
 * @file        apm32f0xx_iwdt.h
 *
 * @brief       This file contains all the functions prototypes for the IWDT firmware library
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
#ifndef __APM32F0XX_IWDT_H
#define __APM32F0XX_IWDT_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes */
#include "apm32f0xx.h"

/** @addtogroup APM32F0xx_StdPeriphDriver
  @{
*/

/** @addtogroup IWDT_Driver
  @{
*/

/** @defgroup IWDT_Macros Macros
  @{
*/

/**@} end of group IWDT_Macros*/

/** @defgroup IWDT_Enumerations Enumerations
  @{
*/

/**@} end of group IWDT_Enumerations*/

/** @defgroup IWDT_Structures Structures
  @{
*/

/**@} end of group IWDT_Structures*/

/** @defgroup IWDT_Variables Variables
  @{
*/

/**@} end of group IWDT_Variables*/

/** @defgroup IWDT_Functions Functions
  @{
*/

/**
 * @brief   IWDT key definition
 */
typedef enum
{
    IWDT_KEY_REFRESH = ((uint16_t)0xAAAA), /*!< Value of  Reload Register reoload to the counter to prevent the IWDT from resetting */
    IWDT_KEY_ENABLE  = ((uint16_t)0xCCCC), /*!< Enable the IWDT then the counter starts to count down from the reset value */
    IWDT_KEY_ACCESS  = ((uint16_t)0x5555), /*!< Rewrite the value of the Prescaler Register, Reload Register and Window Value Register */
} IWDT_KEY_T;

/**
 * @brief   IWDT divider
 */
typedef enum
{
    IWDT_DIV_4   = ((uint8_t)0x00), /*!< Prescaler divider 4 */
    IWDT_DIV_8   = ((uint8_t)0x01), /*!< Prescaler divider 8 */
    IWDT_DIV_16  = ((uint8_t)0x02), /*!< Prescaler divider 16 */
    IWDT_DIV_32  = ((uint8_t)0x03), /*!< Prescaler divider 32 */
    IWDT_DIV_64  = ((uint8_t)0x04), /*!< Prescaler divider 64 */
    IWDT_DIV_128 = ((uint8_t)0x05), /*!< Prescaler divider 128 */
    IWDT_DIV_256 = ((uint8_t)0x06), /*!< Prescaler divider 256 */
} IWDT_DIV_T;

/**
 * @brief   IWDT flag definition
 */
typedef enum
{
    IWDT_FLAG_DIVU = ((uint8_t)0X01), /*!< Watchdog prescaler value update */
    IWDT_FLAG_CNTU = ((uint8_t)0X02), /*!< Watchdog counter reload value update */
    IWDT_FLAG_WINU = ((uint8_t)0X04), /*!< Watchdog counter window value update */
} IWDT_FLAG_T;

/**@} end of group IWDT_Enumerations*/

/** @defgroup IWDT_Functions
  @{
*/

/* Enable IWDT */
void IWDT_Enable(void);

/* Refresh IWDT */
void IWDT_Refresh(void);

/* Window Value */
void IWDT_ConfigWindowValue(uint16_t windowValue);

/* Set Counter reload */
void IWDT_ConfigReload(uint16_t reload);

/* Write Access */
void IWDT_EnableWriteAccess(void);
void IWDT_DisableWriteAccess(void);

/* divider */
void IWDT_ConfigDivider(IWDT_DIV_T div);

/* flag */
uint8_t IWDT_ReadStatusFlag(uint8_t flag);

#ifdef __cplusplus
}
#endif

#endif /* __APM32F0XX_IWDT_H */

/**@} end of group IWDT_Functions*/
/**@} end of group IWDT_Driver */
/**@} end of group APM32F0xx_StdPeriphDriver*/
