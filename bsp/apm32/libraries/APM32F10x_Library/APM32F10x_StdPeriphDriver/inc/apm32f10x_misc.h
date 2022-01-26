/*!
 * @file       apm32f10x_misc.h
 *
 * @brief      This file provides all the miscellaneous firmware functions.
 *             Include NVIC,SystemTick and Power management.
 *
 * @version    V1.0.1
 *
 * @date       2021-03-23
 *
 */

#ifndef __APM32F10X_MISC_H
#define __APM32F10X_MISC_H

#include "apm32f10x.h"

#ifdef __cplusplus
 extern "C" {
#endif

/** @addtogroup Peripherals_Library Standard Peripheral Library
  @{
*/

/** @addtogroup MISC_Driver MISC Driver
  @{
*/

/** @addtogroup MISC_Enumerations Enumerations
  @{
*/

/**
 * @brief   NVIC Vect table
 */
typedef enum
{
   NVIC_VECT_TAB_RAM   = 0x20000000,
   NVIC_VECT_TAB_FLASH = 0x08000000,
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
    NVIC_PRIORITY_GROUP_0 = 0x700,  //!< 0 bits for pre-emption priority,4 bits for subpriority
    NVIC_PRIORITY_GROUP_1 = 0x600,  //!< 1 bits for pre-emption priority,3 bits for subpriority
    NVIC_PRIORITY_GROUP_2 = 0x500,  //!< 2 bits for pre-emption priority,2 bits for subpriority
    NVIC_PRIORITY_GROUP_3 = 0x400,  //!< 3 bits for pre-emption priority,1 bits for subpriority
    NVIC_PRIORITY_GROUP_4 = 0x300   //!< 4 bits for pre-emption priority,0 bits for subpriority
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


/** @addtogroup MISC_Fuctions Fuctions
  @{
*/

/** NVIC */
void NVIC_ConfigPriorityGroup(NVIC_PRIORITY_GROUP_T priorityGroup);
void NVIC_EnableIRQRequest(IRQn_Type irq, uint8_t preemptionPriority, uint8_t subPriority);
void NVIC_DisableIRQRequest(IRQn_Type irq);

/** Vector Table */
void NVIC_ConfigVectorTable(NVIC_VECT_TAB_T vectTab, uint32_t offset);

/** Power */
void NVIC_SetSystemLowPower(NVIC_LOWPOWER_T lowPowerMode);
void NVIC_ResetystemLowPower(NVIC_LOWPOWER_T lowPowerMode);

/** Systick */
void SysTick_ConfigCLKSource(SYSTICK_CLK_SOURCE_T clkSource);

#ifdef __cplusplus
}
#endif

#endif /* __APM32F10X_MISC_H */
