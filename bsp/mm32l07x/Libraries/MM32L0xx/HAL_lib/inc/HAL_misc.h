/**
******************************************************************************
* @file  HAL_misc.h
* @author  AE Team
* @version  V2.0.0
* @date  22/08/2017
* @brief  This file contains all the functions prototypes for the 
*         miscellaneous firmware library functions.
******************************************************************************

*/ 

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __HAL_MISC_H
#define __HAL_MISC_H

#ifdef __cplusplus
 extern "C" {
#endif
/* Includes ------------------------------------------------------------------*/
#include "HAL_device.h"

/** @addtogroup StdPeriph_Driver
* @{
*/

/** @addtogroup MISC
* @{
*/

/** @defgroup MISC_Exported_Types
* @{
*/

/** 
* @brief  NVIC Init Structure definition  
*/

typedef struct
{
  uint8_t NVIC_IRQChannel;             /*!< Specifies the IRQ channel to be enabled or disabled.
                                            This parameter can be a value of @ref IRQn_Type 
                                            (For the complete MM32 Devices IRQ Channels list, 
                                            please refer to HAL_device.h file) */

  uint8_t NVIC_IRQChannelPriority;     /*!< Specifies the priority level for the IRQ channel specified
                                            in NVIC_IRQChannel. This parameter can be a value
                                            between 0 and 3.  */

  FunctionalState NVIC_IRQChannelCmd;  /*!< Specifies whether the IRQ channel defined in NVIC_IRQChannel
                                            will be enabled or disabled. 
                                            This parameter can be set either to ENABLE or DISABLE */   
} NVIC_InitTypeDef;

/**
* @}
*/

/** @defgroup MISC_Exported_Constants
* @{
*/

/** @defgroup MISC_System_Low_Power 
  * @{
  */

#define NVIC_LP_SEVONPEND            ((uint8_t)0x10)
#define NVIC_LP_SLEEPDEEP            ((uint8_t)0x04)
#define NVIC_LP_SLEEPONEXIT          ((uint8_t)0x02)
#define IS_NVIC_LP(LP) (((LP) == NVIC_LP_SEVONPEND) || \
((LP) == NVIC_LP_SLEEPDEEP) || \
  ((LP) == NVIC_LP_SLEEPONEXIT))
/**
* @}
*/

/** @defgroup MISC_Preemption_Priority_Group 
  * @{
  */
#define IS_NVIC_PRIORITY(PRIORITY)  ((PRIORITY) < 0x04)

/**
* @}
*/

/** @defgroup SysTick_clock_source 
* @{
*/

#define SysTick_CLKSource_HCLK_Div8    ((uint32_t)0xFFFFFFFB)
#define SysTick_CLKSource_HCLK         ((uint32_t)0x00000004)
#define IS_SYSTICK_CLK_SOURCE(SOURCE) (((SOURCE) == SysTick_CLKSource_HCLK) || \
((SOURCE) == SysTick_CLKSource_HCLK_Div8))
/**
* @}
*/

/**
* @}
*/

/** @defgroup MISC_Exported_Macros
* @{
*/

/**
* @}
*/

/** @defgroup MISC_Exported_Functions
* @{
*/

void NVIC_Init(NVIC_InitTypeDef* NVIC_InitStruct);
void NVIC_SystemLPConfig(uint8_t LowPowerMode, FunctionalState NewState);
void SysTick_CLKSourceConfig(uint32_t SysTick_CLKSource);

#ifdef __cplusplus
}
#endif

#endif /* __HAL_MISC_H */

/**
* @}
*/

/**
* @}
*/

/**
* @}
*/

/*-------------------------(C) COPYRIGHT 2017 MindMotion ----------------------*/
