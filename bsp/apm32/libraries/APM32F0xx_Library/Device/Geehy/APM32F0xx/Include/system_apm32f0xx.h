/*!
 * @file        system_apm32f0xx.h
 *
 * @brief      CMSIS Cortex-M0 Device Peripheral Access Layer System Source File
 *
 * @details     This file contains the system clock configuration for APM32F0xx devices.
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
#ifndef __SYSTEM_APM32F0XX_H
#define __SYSTEM_APM32F0XX_H

#ifdef __cplusplus
extern "C" {
#endif

/** @addtogroup CMSIS
  @{
*/

/** @addtogroup APM32F0xx_System
  @{
*/

/** @defgroup System_Macros Macros
  @{
  */

/**@} end of group System_Macros */

/** @defgroup System_Enumerations Enumerations
  @{
  */

/**@} end of group System_Enumerations */

/** @defgroup System_Structures Structures
  @{
  */

/**@} end of group System_Structures */

/** @defgroup System_Variables Variables
  @{
  */

/* System Clock Frequency (Core Clock) */
extern uint32_t SystemCoreClock;

/**@} end of group System_Variables */

/** @defgroup System_Functions Functions
  @{
  */

extern void SystemInit(void);
extern void SystemCoreClockUpdate(void);

#ifdef __cplusplus
}
#endif

#endif /* __SYSTEM_APM32F0XX_H */

/**@} end of group System_Functions */
/**@} end of group APM32F0xx_System */
/**@} end of group CMSIS */
