/**
  ******************************************************************************
  * @file    tae32f53xx_ll_cortex.h
  * @author  MCD Application Team
  * @brief   Head file for CORTEX LL module driver.
  *
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2020 Tai-Action.
  * All rights reserved.</center></h2>
  *
  * This software is licensed by Tai-Action under BSD 3-Clause license,
  * the "License"; You may not use this file except in compliance with the
  * License. You may obtain a copy of the License at:
  *                        opensource.org/licenses/BSD-3-Clause
  *
  ******************************************************************************
  */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef _TAE32F53XX_LL_CORTEX_H_
#define _TAE32F53XX_LL_CORTEX_H_

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

/* Includes ------------------------------------------------------------------*/
#include "tae32f53xx_ll_def.h"


/** @addtogroup TAE32F53xx_LL_Driver
  * @{
  */

/** @addtogroup CORTEX_LL
  * @{
  */


/* Exported types ------------------------------------------------------------*/
/* Exported constants --------------------------------------------------------*/
/** @defgroup CORTEX_LL_Exported_Constants CORTEX LL Exported Constants
  * @brief    CORTEX LL Exported Constants
  * @{
  */

/** @defgroup CORTEX_Preemption_Priority_Group CORTEX Preemption Priority Group
  * @{
  */
#define NVIC_PRIORITYGROUP_0            0x00000007U     /*!< 0 bit  for pre-emption priority, 3 bits for subpriority    */
#define NVIC_PRIORITYGROUP_1            0x00000006U     /*!< 1 bit  for pre-emption priority, 2 bits for subpriority    */
#define NVIC_PRIORITYGROUP_2            0x00000005U     /*!< 2 bits for pre-emption priority, 1 bit  for subpriority    */
#define NVIC_PRIORITYGROUP_3            0x00000004U     /*!< 3 bits for pre-emption priority, 0 bit  for subpriority    */
/**
  * @}
  */

/** @defgroup CORTEX_SysTick_Clock_Source CORTEX SysTick Clock Source
  * @brief    CORTEX SysTick Clock Source
  * @{
  */
#define SYSTICK_CLKSOURCE_HCLK_DIV8     0x00000000U     /*!< SYSTICK Clock Source HCLK Div8 */
#define SYSTICK_CLKSOURCE_HCLK          0x00000004U     /*!< SYSTICK Clock Source HCLK      */
/**
  * @}
  */

/**
  * @}
  */

/* Exported macro ------------------------------------------------------------*/
/* Exported functions --------------------------------------------------------*/
/** @addtogroup CORTEX_LL_Exported_Functions
  * @{
  */

/** @addtogroup CORTEX_LL_Exported_Functions_Group1
  * @{
  */
void LL_NVIC_SetPriorityGrouping(uint32_t PriorityGroup);
uint32_t LL_NVIC_GetPriorityGrouping(void);
void LL_NVIC_SetPriority(IRQn_Type IRQn, uint32_t PreemptPriority, uint32_t SubPriority);
void LL_NVIC_GetPriority(IRQn_Type IRQn, uint32_t PriorityGroup, uint32_t *pPreemptPriority, uint32_t *pSubPriority);
/**
  * @}
  */


/** @addtogroup CORTEX_LL_Exported_Functions_Group2
  * @{
  */
void LL_NVIC_EnableIRQ(IRQn_Type IRQn);
void LL_NVIC_DisableIRQ(IRQn_Type IRQn);
void LL_NVIC_SetPendingIRQ(IRQn_Type IRQn);
uint32_t LL_NVIC_GetPendingIRQ(IRQn_Type IRQn);
void LL_NVIC_ClearPendingIRQ(IRQn_Type IRQn);
uint32_t LL_NVIC_GetActive(IRQn_Type IRQn);
void LL_NVIC_SystemReset(void);
/**
  * @}
  */


/** @addtogroup CORTEX_LL_Exported_Functions_Group3
  * @{
  */
void LL_SYSTICK_CLKSourceConfig(uint32_t CLKSource);
uint32_t LL_SYSTICK_Config(uint32_t TicksNumb);
/**
  * @}
  */


/** @addtogroup CORTEX_LL_Exported_Functions_Interrupt
  * @{
  */
void LL_SYSTICK_IRQHandler(void);
void LL_SYSTICK_Callback(void);
/**
  * @}
  */


/**
  * @}
  */

/* Private types -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private constants ---------------------------------------------------------*/
/* Private macros ------------------------------------------------------------*/
/** @defgroup CORTEX_LL_Private_Macros CORTEX LL Private Macros
  * @brief    CORTEX LL Private Macros
  * @{
  */

/**
  * @brief  Judge is NVIC priority group or not
  * @param  GROUP priority group to judge
  * @retval 0 isn't NVIC priority group
  * @retval 1 is NVIC priority group
  */
#define IS_NVIC_PRIORITY_GROUP(GROUP)           (((GROUP) == NVIC_PRIORITYGROUP_0) || \
                                                 ((GROUP) == NVIC_PRIORITYGROUP_1) || \
                                                 ((GROUP) == NVIC_PRIORITYGROUP_2) || \
                                                 ((GROUP) == NVIC_PRIORITYGROUP_3))

/**
  * @brief  Judge is NVIC preemption priority or not
  * @param  PRIORITY preemption priority to judge
  * @retval 0 isn't NVIC preemption priority
  * @retval 1 is NVIC preemption priority
  */
#define IS_NVIC_PREEMPTION_PRIORITY(PRIORITY)   ((PRIORITY) < 0x10U)

/**
  * @brief  Judge is NVIC SubPriority or not
  * @param  PRIORITY SubPriority to judge
  * @retval 0 isn't NVIC SubPriority
  * @retval 1 is NVIC SubPriority
  */
#define IS_NVIC_SUB_PRIORITY(PRIORITY)          ((PRIORITY) < 0x10U)

/**
  * @brief  Judge is NVIC device IRQ or not
  * @param  IRQ IRQ to judge
  * @retval 0 isn't NVIC device IRQ
  * @retval 1 is NVIC device IRQ
  */
#define IS_NVIC_DEVICE_IRQ(IRQ)                 ((IRQ) >= (IRQn_Type)0x00U)

/**
  * @brief  Judge is SYSTICK clock source or not
  * @param  SOURCE clock source to judge
  * @retval 0 isn't SYSTICK clock source
  * @retval 1 is SYSTICK clock source
  */
#define IS_SYSTICK_CLK_SOURCE(SOURCE)           (((SOURCE) == SYSTICK_CLKSOURCE_HCLK) || ((SOURCE) == SYSTICK_CLKSOURCE_HCLK_DIV8))
/**
  * @}
  */


/* Private functions ---------------------------------------------------------*/


/**
  * @}
  */

/**
  * @}
  */


#ifdef __cplusplus
}
#endif /* __cplusplus */


#endif /* _TAE32F53XX_LL_CORTEX_H_ */


/************************* (C) COPYRIGHT Tai-Action *****END OF FILE***********/

