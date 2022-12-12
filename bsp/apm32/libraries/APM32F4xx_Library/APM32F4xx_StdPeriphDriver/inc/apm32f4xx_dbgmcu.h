/*!
 * @file        apm324xx_dbgmcu.h
 *
 * @brief       This file contains all the functions prototypes for the DBUGMCU firmware library
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
#ifndef __APM32F4XX_DBGMCU_H
#define __APM32F4XX_DBGMCU_H

#ifdef __cplusplus
  extern "C" {
#endif

/* Includes */
#include "apm32f4xx.h"

/** @addtogroup APM32F4xx_StdPeriphDriver
  @{
*/

/** @addtogroup DBGMCU_Driver
  @{
*/

/** @defgroup DBGMCU_Enumerations
  @{
*/

/**
 * @brief DBGMCU_STOP description
 */
typedef enum
{
    DBGMCU_SLEEP                 = ((uint32_t)0x00000001),  /*!< Keep debugger connection during SLEEP mode */
    DBGMCU_STOP                  = ((uint32_t)0x00000002),  /*!< Keep debugger connection during STOP mode */
    DBGMCU_STANDBY               = ((uint32_t)0x00000004),  /*!< Keep debugger connection during STANDBY mode */
    /** APB1 Peripheral */
    DBGMCU_TMR2_STOP             = ((uint32_t)0x00000001),  /*!< TMR2 counter stopped when Core is halted */
    DBGMCU_TMR3_STOP             = ((uint32_t)0x00000002),  /*!< TMR3 counter stopped when Core is halted */
    DBGMCU_TMR4_STOP             = ((uint32_t)0x00000004),  /*!< TMR4 counter stopped when Core is halted */
    DBGMCU_TMR5_STOP             = ((uint32_t)0x00000008),  /*!< TMR5 counter stopped when Core is halted */
    DBGMCU_TMR6_STOP             = ((uint32_t)0x00000010),  /*!< TMR6 counter stopped when Core is halted */
    DBGMCU_TMR7_STOP             = ((uint32_t)0x00000020),  /*!< TMR7 counter stopped when Core is halted */
    DBGMCU_TMR12_STOP            = ((uint32_t)0x00000040),  /*!< TMR12 counter stopped when Core is halted */
    DBGMCU_TMR13_STOP            = ((uint32_t)0x00000080),  /*!< TMR13 counter stopped when Core is halted */
    DBGMCU_TMR14_STOP            = ((uint32_t)0x00000100),  /*!< TMR14 counter stopped when Core is halted */
    DBGMCU_RTC_STOP              = ((uint32_t)0x00000400),  /*!< RTC Calendar and Wakeup counter stopped when Core is halted */
    DBGMCU_WWDT_STOP             = ((uint32_t)0x00000800),  /*!< Debug WWDG stopped when Core is halted */
    DBGMCU_IWDT_STOP             = ((uint32_t)0x00001000),  /*!< Debug IWDG stopped when Core is halted */
    DBGMCU_I2C1_SMBUS_TIMEOUT    = ((uint32_t)0x00200000),  /*!< I2C1 SMBUS timeout mode stopped when Core is halted */
    DBGMCU_I2C2_SMBUS_TIMEOUT    = ((uint32_t)0x00400000),  /*!< I2C2 SMBUS timeout mode stopped when Core is halted */
    DBGMCU_I2C3_SMBUS_TIMEOUT    = ((uint32_t)0x00800000),  /*!< I2C3 SMBUS timeout mode stopped when Core is halted */
    DBGMCU_CAN1_STOP             = ((uint32_t)0x02000000),  /*!< Debug CAN1 stopped when Core is halted */
    DBGMCU_CAN2_STOP             = ((uint32_t)0x04000000),  /*!< Debug CAN2 stopped when Core is halted */
    /** APB2 Peripheral */
    DBGMCU_TMR1_STOP             = ((uint32_t)0x00000001),  /*!< TMR1 counter stopped when Core is halted */
    DBGMCU_TMR8_STOP             = ((uint32_t)0x00000002),  /*!< TMR8 counter stopped when Core is halted */
    DBGMCU_TMR9_STOP             = ((uint32_t)0x00010000),  /*!< TMR9 counter stopped when Core is halted */
    DBGMCU_TMR10_STOP            = ((uint32_t)0x00020000),  /*!< TMR10 counter stopped when Core is halted */
    DBGMCU_TMR11_STOP            = ((uint32_t)0x00040000)   /*!< TMR11 counter stopped when Core is halted */
} DBGMCU_STOP_T;

/**@} end of group DBGMCU_Enumerations*/

/** @defgroup DBGMCU_Functions
  @{
*/

uint32_t DBGMCU_ReadDEVID(void);
uint32_t DBGMCU_ReadREVID(void);
void DBGMCU_Enable(uint32_t periph);
void DBGMCU_Disable(uint32_t periph);
void DBGMCU_DisableAPB1Periph(uint32_t periph);
void DBGMCU_EnableAPB1Periph(uint32_t periph);
void DBGMCU_DisableAPB2Periph(uint32_t periph);
void DBGMCU_EnableAPB2Periph(uint32_t periph);

#ifdef __cplusplus
}
#endif

#endif /* __APM32F4XX_DBGMCU_H */

/**@} end of group DBGMCU_Enumerations */
/**@} end of group DBGMCU_Driver */
/**@} end of group APM32F4xx_StdPeriphDriver */
