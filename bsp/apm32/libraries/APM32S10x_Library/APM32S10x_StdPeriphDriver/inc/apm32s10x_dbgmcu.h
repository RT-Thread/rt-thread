/*!
 * @file        apm32s10x_dbgmcu.h
 *
 * @brief       This file contains all the functions prototypes for the DBUGMCU firmware library
 *
 * @version     V1.0.1
 *
 * @date        2022-12-31
 *
 * @attention
 *
 *  Copyright (C) 2022-2023 Geehy Semiconductor
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
#ifndef __APM32S10X_DBGMCU_H
#define __APM32S10X_DBGMCU_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes */
#include "apm32s10x.h"

/** @addtogroup APM32S10x_StdPeriphDriver
  @{
*/

/** @addtogroup DBGMCU_Driver DBGMCU Driver
  @{
*/

/** @defgroup DBGMCU_Enumerations Enumerations
  @{
*/

enum
{
    DBGMCU_SLEEP                = ((uint32_t)0x00000001),
    DBGMCU_STOP                 = ((uint32_t)0x00000002),
    DBGMCU_STANDBY              = ((uint32_t)0x00000004),
    DBGMCU_IOEN                 = ((uint32_t)0x00000020),
    DBGMCU_IOMODE0              = ((uint32_t)0x00000000),
    DBGMCU_IOMODE1              = ((uint32_t)0x00000040),
    DBGMCU_IOMODE2              = ((uint32_t)0x00000080),
    DBGMCU_IOMODE3              = ((uint32_t)0x000000C0),
    DBGMCU_IWDT_STOP            = ((uint32_t)0x00000100),
    DBGMCU_WWDT_STOP            = ((uint32_t)0x00000200),
    DBGMCU_TMR1_STOP            = ((uint32_t)0x00000400),
    DBGMCU_TMR2_STOP            = ((uint32_t)0x00000800),
    DBGMCU_TMR3_STOP            = ((uint32_t)0x00001000),
    DBGMCU_TMR4_STOP            = ((uint32_t)0x00002000),
    DBGMCU_CAN1_STOP            = ((uint32_t)0x00004000),
    DBGMCU_I2C1_SMBUS_TIMEOUT   = ((uint32_t)0x00008000),
    DBGMCU_I2C2_SMBUS_TIMEOUT   = ((uint32_t)0x00010000),
    DBGMCU_CAN2_STOP            = ((uint32_t)0x00200000)
};

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
/**@} end of group APM32S10x_StdPeriphDriver */

#ifdef __cplusplus
}
#endif

#endif /* __APM32S10X_DBGMCU_H */
