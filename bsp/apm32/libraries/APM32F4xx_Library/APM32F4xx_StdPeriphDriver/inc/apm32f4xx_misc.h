/*!
 * @file        apm32f4xx_misc.h
 *
 * @brief       This file provides all the miscellaneous firmware functions.
 *              Include NVIC,SystemTick and Power management.
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
#ifndef __APM32F4XX_MISC_H
#define __APM32F4XX_MISC_H

#ifdef __cplusplus
  extern "C" {
#endif

/* Includes */
#include "apm32f4xx.h"

/** @addtogroup APM32F4xx_StdPeriphDriver
  @{
*/

/** @addtogroup MISC_Driver
  @{
*/

/** @defgroup MISC_Enumerations
  @{
*/

/**
 * @brief NVIC Vect table
 */
typedef enum
{
    NVIC_VECT_TAB_RAM   = 0x20000000,    /*!< NVIC vector table base address launch from RAM */
    NVIC_VECT_TAB_FLASH = 0x08000000,    /*!< NVIC vector table base address launch from flash */
} NVIC_VECT_TAB_T;

/**
 * @brief System low power mode
 */
typedef enum
{
    NVIC_LOWPOWER_SEVONPEND   = 0x10,    /*!< Wake up according to pending request */
    NVIC_LOWPOWER_SLEEPDEEP   = 0x04,    /*!< Enable sleep deep */
    NVIC_LOWPOWER_SLEEPONEXIT = 0x02     /*!< Sleep after exit ISR */
} NVIC_LOWPOWER_T;

/**
 * @brief NVIC priority group
 */
typedef enum
{
    NVIC_PRIORITY_GROUP_0 = 0x700,  /*!< 0 bits for pre-emption priority,4 bits for subpriority */
    NVIC_PRIORITY_GROUP_1 = 0x600,  /*!< 1 bits for pre-emption priority,3 bits for subpriority */
    NVIC_PRIORITY_GROUP_2 = 0x500,  /*!< 2 bits for pre-emption priority,2 bits for subpriority */
    NVIC_PRIORITY_GROUP_3 = 0x400,  /*!< 3 bits for pre-emption priority,1 bits for subpriority */
    NVIC_PRIORITY_GROUP_4 = 0x300   /*!< 4 bits for pre-emption priority,0 bits for subpriority */
} NVIC_PRIORITY_GROUP_T;

/**
 * @brief SysTick Clock source
 */
typedef enum
{
    SYSTICK_CLK_SOURCE_HCLK_DIV8 = 0x00,    /*!< AHB clock divided by 8 selected as SysTick clock source */
    SYSTICK_CLK_SOURCE_HCLK      = 0x01     /*!< AHB clock selected as SysTick clock source */
} SYSTICK_CLK_SOURCE_T;

/**@} end of group MISC_Enumerations*/

/** @defgroup MISC_Functions
  @{
*/

/* NVIC */
void NVIC_ConfigPriorityGroup(NVIC_PRIORITY_GROUP_T priorityGroup);
void NVIC_EnableIRQRequest(IRQn_Type irq, uint8_t preemptionPriority, uint8_t subPriority);
void NVIC_DisableIRQRequest(IRQn_Type irq);

/* Vector Table */
void NVIC_ConfigVectorTable(NVIC_VECT_TAB_T vectTab, uint32_t offset);

/* Power */
void NVIC_SetSystemLowPower(NVIC_LOWPOWER_T lowPowerMode);
void NVIC_ResetystemLowPower(NVIC_LOWPOWER_T lowPowerMode);

/* Systick */
void SysTick_ConfigCLKSource(SYSTICK_CLK_SOURCE_T clkSource);

#ifdef __cplusplus
}
#endif

#endif /* __APM32F4XX_MISC_H */

/**@} end of group MISC_Enumerations */
/**@} end of group MISC_Driver */
/**@} end of group APM32F4xx_StdPeriphDriver */
