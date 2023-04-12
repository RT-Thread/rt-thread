/*!
 * @file       apm32e10x_misc.h
 *
 * @brief      This file provides all the miscellaneous firmware functions.
 *             Include NVIC,SystemTick and Power management.
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
#ifndef __APM32E10X_MISC_H
#define __APM32E10X_MISC_H

/* Includes */
#include "apm32e10x.h"

#ifdef __cplusplus
 extern "C" {
#endif

/** @addtogroup APM32E10x_StdPeriphDriver
  @{
*/

/** @addtogroup MISC_Driver
  @{
*/

/** @defgroup MISC_Enumerations Enumerations
  @{
*/

/**
 * @brief   NVIC Vect table
 */
typedef enum
{
   NVIC_VECT_TAB_RAM   = 0x20000000,
   NVIC_VECT_TAB_FLASH = 0x08000000
}NVIC_VECT_TAB_T;

/**
 * @brief   system low power mode
 */
typedef enum
{
   NVIC_LOWPOWER_SEVONPEND   = 0x10,
   NVIC_LOWPOWER_SLEEPDEEP   = 0x04,
   NVIC_LOWPOWER_SLEEPONEXIT = 0x02
}NVIC_LOWPOWER_T;

/**
 * @brief   nvic priority group
 */
typedef enum
{
    NVIC_PRIORITY_GROUP_0 = 0x700,  /*!< 0 bits for pre-emption priority,4 bits for subpriority */
    NVIC_PRIORITY_GROUP_1 = 0x600,  /*!< 1 bits for pre-emption priority,3 bits for subpriority */
    NVIC_PRIORITY_GROUP_2 = 0x500,  /*!< 2 bits for pre-emption priority,2 bits for subpriority */
    NVIC_PRIORITY_GROUP_3 = 0x400,  /*!< 3 bits for pre-emption priority,1 bits for subpriority */
    NVIC_PRIORITY_GROUP_4 = 0x300   /*!< 4 bits for pre-emption priority,0 bits for subpriority */
}NVIC_PRIORITY_GROUP_T;

/**
 * @brief   SysTick Clock source
 */
typedef enum
{
   SYSTICK_CLK_SOURCE_HCLK_DIV8 = 0x00,
   SYSTICK_CLK_SOURCE_HCLK      = 0x01
}SYSTICK_CLK_SOURCE_T;

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

/**@} end of group MISC_Functions */
/**@} end of group MISC_Driver */
/**@} end of group APM32E10x_StdPeriphDriver */

#ifdef __cplusplus
}
#endif

#endif /* __APM32E10X_MISC_H */
