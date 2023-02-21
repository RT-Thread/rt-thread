/*!
 * @file        apm32f0xx_misc.h
 *
 * @brief       This file contains all the functions prototypes for the miscellaneous
 *              firmware library functions (add-on to CMSIS functions).
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
#ifndef __APM32F0XX_MISC_H
#define __APM32F0XX_MISC_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes */
#include "apm32f0xx.h"

/** @addtogroup APM32F0xx_StdPeriphDriver
  @{
*/

/** @addtogroup MISC_Driver
  @{
*/

/** @defgroup MISC_Macros Macros
  @{
*/

/* MISC SysTick clock source */
#define SysTick_CLKSource_HCLK_Div8 ((uint32_t)0xFFFFFFFB)
#define SysTick_CLKSource_HCLK      ((uint32_t)0x00000004)

/**@} end of group MISC_Macros */

/** @defgroup MISC_Enumerations Enumerations
  @{
*/

/**
 * @brief    System low power mode
 */
typedef enum
{
    NVIC_LOWPOER_SEVONPEND   = 0x10, /*!< Wake up according to pending request */
    NVIC_LOWPOER_SLEEPDEEP   = 0x04, /*!< Enable sleep deep */
    NVIC_LOWPOER_SLEEPONEXIT = 0x02  /*!< Sleep after exit ISR */
} NVIC_LOWPOER_T;

/**@} end of group MISC_Enumerations */

/** @defgroup MISC_Structures Structures
  @{
*/

/**@} end of group MISC_Structures */

/** @defgroup MISC_Variables Variables
  @{
*/

/**@} end of group MISC_Variables*/

/** @defgroup MISC_Functions Functions
  @{
*/

/* NVIC */
void NVIC_EnableIRQRequest(IRQn_Type irq, uint8_t priority);
void NVIC_DisableIRQRequest(IRQn_Type irq);

/* Low Power */
void NVIC_EnableSystemLowPower(uint8_t lowPowerMode);
void NVIC_DisableSystemLowPower(uint8_t lowPowerMode);

/* SysTick */
void SysTick_ConfigCLKSource(uint32_t sysTickCLKSource);

/* PMU */
void PMU_EnterWaitMode(void);
void PMU_EnterHaltModeWFI(void);
void PMU_EnterHaltModeWFE(void);

#ifdef __cplusplus
}
#endif

#endif /* __APM32F0XX_MISC_H */

/**@} end of group MISC_Functions */
/**@} end of group MISC_Driver */
/**@} end of group APM32F0xx_StdPeriphDriver */
