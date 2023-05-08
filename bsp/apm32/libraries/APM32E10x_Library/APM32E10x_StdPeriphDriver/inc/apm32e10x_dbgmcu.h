/*!
 * @file        apm32e10x_dbgmcu.h
 *
 * @brief       This file contains all the functions prototypes for the DBUGMCU firmware library
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
#ifndef __APM32E10X_DBGMCU_H
#define __APM32E10X_DBGMCU_H

/* Includes */
#include "apm32e10x.h"

#ifdef __cplusplus
 extern "C" {
#endif

/** @addtogroup APM32E10x_StdPeriphDriver
  @{
*/

/** @addtogroup DBGMCU_Driver
  @{
*/

/** @defgroup DBGMCU_Enumerations Enumerations
  @{
*/

/**
 * @brief DBGMCU_STOP description
 */
typedef enum
{
    DBGMCU_SLEEP                = ((uint32_t)0x00000001),
    DBGMCU_STOP                 = ((uint32_t)0x00000002),
    DBGMCU_STANDBY              = ((uint32_t)0x00000004),
    DBGMCU_IWDT_STOP            = ((uint32_t)0x00000100),
    DBGMCU_WWDT_STOP            = ((uint32_t)0x00000200),
    DBGMCU_TMR1_STOP            = ((uint32_t)0x00000400),
    DBGMCU_TMR2_STOP            = ((uint32_t)0x00000800),
    DBGMCU_TMR3_STOP            = ((uint32_t)0x00001000),
    DBGMCU_TMR4_STOP            = ((uint32_t)0x00002000),
    DBGMCU_CAN1_STOP            = ((uint32_t)0x00004000),
    DBGMCU_I2C1_SMBUS_TIMEOUT   = ((uint32_t)0x00008000),
    DBGMCU_I2C2_SMBUS_TIMEOUT   = ((uint32_t)0x00010000),
    DBGMCU_TMR8_STOP            = ((uint32_t)0x00020000),
    DBGMCU_TMR5_STOP            = ((uint32_t)0x00040000),
    DBGMCU_TMR6_STOP            = ((uint32_t)0x00080000),
    DBGMCU_TMR7_STOP            = ((uint32_t)0x00100000),
    DBGMCU_CAN2_STOP            = ((uint32_t)0x00200000),
    DBGMCU_TMR15_STOP           = ((uint32_t)0x00400000),
    DBGMCU_TMR16_STOP           = ((uint32_t)0x00800000),
    DBGMCU_TMR17_STOP           = ((uint32_t)0x01000000),
    DBGMCU_TMR12_STOP           = ((uint32_t)0x02000000),
    DBGMCU_TMR13_STOP           = ((uint32_t)0x04000000),
    DBGMCU_TMR14_STOP           = ((uint32_t)0x08000000),
    DBGMCU_TMR9_STOP            = ((uint32_t)0x10000000),
    DBGMCU_TMR10_STOP           = ((uint32_t)0x20000000),
    DBGMCU_TMR11_STOP           = ((uint32_t)0x40000000),
} DBGMCU_STOP_T;

/**@} end of group DBGMCU_Enumerations */


/** @defgroup DBGMCU_Functions Functions
  @{
*/

uint32_t DBGMCU_ReadDEVID(void);
uint32_t DBGMCU_ReadREVID(void);
void DBGMCU_Enable(uint32_t periph);
void DBGMCU_Disable(uint32_t periph);

/**@} end of group DBGMCU_Functions */
/**@} end of group DBGMCU_Driver */
/**@} end of group APM32E10x_StdPeriphDriver */

#ifdef __cplusplus
}
#endif

#endif /* __APM32E10X_DBGMCU_H */
