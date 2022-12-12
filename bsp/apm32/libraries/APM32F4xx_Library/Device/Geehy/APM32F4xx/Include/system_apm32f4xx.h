/*!
 * @file        system_apm32f4xx.h
 *
 * @brief       CMSIS Cortex-M4 Device Peripheral Access Layer System Source File
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
#ifndef __SYSTEM_APM32F4XX_H
#define __SYSTEM_APM32F4XX_H

#ifdef __cplusplus
  extern "C" {
#endif

/** @addtogroup CMSIS
  @{
*/

/** @addtogroup APM32F4xx_System
  @{
*/

/** @defgroup System_Variables
  @{
*/

/* System Clock Frequency (Core Clock) */
extern uint32_t SystemCoreClock;

/**
  * @}
  */

/** @defgroup System_Functions
  @{
*/

extern void SystemInit(void);
extern void SystemCoreClockUpdate(void);

#ifdef __cplusplus
}
#endif

#endif /*__SYSTEM_APM32F4XX_H */

/**@} end of group System_Functions */
/**@} end of group APM32F4xx_System */
/**@} end of group CMSIS */
