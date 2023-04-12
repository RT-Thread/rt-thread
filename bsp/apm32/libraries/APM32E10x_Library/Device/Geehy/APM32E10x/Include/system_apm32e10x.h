/*!
 * @file        system_apm32e10x.h
 *
 * @brief       CMSIS Cortex-M3 Device Peripheral Access Layer System Source File
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
#ifndef __SYSTEM_APM32E10X_H
#define __SYSTEM_APM32E10X_H

#ifdef __cplusplus
 extern "C" {
#endif

/** @addtogroup CMSIS
  @{
*/

/** @addtogroup APM32E10x_System
  @{
*/

/** @defgroup System_Functions
  @{
*/

extern uint32_t SystemCoreClock;

extern void SystemInit(void);
extern void SystemCoreClockUpdate(void);

/**@} end of group System_Functions */
/**@} end of group APM32E10x_System */
/**@} end of group CMSIS */

#ifdef __cplusplus
}
#endif

#endif /*__SYSTEM_APM32E10X_H */
