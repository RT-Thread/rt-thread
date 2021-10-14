/**
  ******************************************************************************
  * @file    stm32l0xx_hal_comp_ex.c
  * @author  MCD Application Team
  * @brief   Extended COMP HAL module driver.
  * @brief   This file provides firmware functions to manage voltage reference
  *          VrefInt that must be specifically controled for comparator
  *          instance COMP2.
  @verbatim 
  ==============================================================================
               ##### COMP peripheral Extended features  #####
  ==============================================================================

  [..] Comparing to other previous devices, the COMP interface for STM32L0XX
       devices contains the following additional features

       (+) Possibility to enable or disable the VREFINT which is used as input
           to the comparator.


  @endverbatim
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright(c) 2016 STMicroelectronics.
  * All rights reserved.</center></h2>
  *
  * This software component is licensed by ST under BSD 3-Clause license,
  * the "License"; You may not use this file except in compliance with the
  * License. You may obtain a copy of the License at:
  *                        opensource.org/licenses/BSD-3-Clause
  *
  ******************************************************************************
  */ 

#if !defined (STM32L010xB) && !defined (STM32L010x8) && !defined (STM32L010x6) && !defined (STM32L010x4)
/* Includes ------------------------------------------------------------------*/
#include "stm32l0xx_hal.h"

/** @addtogroup STM32L0xx_HAL_Driver
  * @{
  */

#ifdef HAL_COMP_MODULE_ENABLED

/** @addtogroup COMPEx
  * @brief Extended COMP HAL module driver
  * @{
  */

/* Private define ------------------------------------------------------------*/
/** @addtogroup COMP_Private_Constants
  * @{
  */

/* Delay for COMP voltage scaler stabilization time (voltage from VrefInt,    */
/* delay based on VrefInt startup time).                                      */
/* Literal set to maximum value (refer to device datasheet,                   */
/* parameter "TVREFINT").                                                     */
/* Unit: us                                                                   */
#define COMP_DELAY_VOLTAGE_SCALER_STAB_US (3000U)  /*!< Delay for COMP voltage scaler stabilization time */

/**
  * @}
  */

/* Exported functions --------------------------------------------------------*/
/** @addtogroup COMPEx_Exported_Functions
  * @{
  */

/** @addtogroup COMPEx_Exported_Functions_Group1
  * @brief  Extended functions to manage VREFINT for the comparator
  *
  * @{
  */

/**
  * @brief  Enable Vrefint and path to comparator, used by comparator
  *         instance COMP2 input based on VrefInt or subdivision of VrefInt.
  * @note   The equivalent of this function is managed automatically when
  *         using function "HAL_COMP_Init()".
  * @note   VrefInt requires a startup time
  *         (refer to device datasheet, parameter "TVREFINT").
  *         This function waits for the startup time
  *         (alternative solution: poll for bit SYSCFG_CFGR3_VREFINT_RDYF set).
  * @note   VrefInt must be disabled before entering in low-power mode.
  *         Refer to description of bit EN_VREFINT in reference manual.
  * @retval None
  */
void HAL_COMPEx_EnableVREFINT(void)
{
  __IO uint32_t wait_loop_index = 0U;
  
  /* Enable VrefInt voltage reference and buffer */
  SYSCFG->CFGR3 |= (SYSCFG_CFGR3_ENBUFLP_VREFINT_COMP | SYSCFG_CFGR3_EN_VREFINT);
  
  /* Wait loop initialization and execution */
  /* Note: Variable divided by 2 to compensate partially              */
  /*       CPU processing cycles.                                     */
  wait_loop_index = (COMP_DELAY_VOLTAGE_SCALER_STAB_US * (SystemCoreClock / (1000000U * 2U)));
  while(wait_loop_index != 0U)
  {
    wait_loop_index--;
  }
}

/**
  * @brief  Disable Vrefint and path to comparator, used by comparator
  *         instance COMP2 input based on VrefInt or subdivision of VrefInt.
  * @note   VrefInt must be disabled before entering in low-power mode.
  *         Refer to description of bit EN_VREFINT in reference manual.
  * @retval None
  */
void HAL_COMPEx_DisableVREFINT(void)
{
  /* Disable VrefInt voltage reference and buffer */
  SYSCFG->CFGR3 &= (uint32_t)~((uint32_t)(SYSCFG_CFGR3_ENBUFLP_VREFINT_COMP | SYSCFG_CFGR3_EN_VREFINT));
}

/**
  * @}
  */

/**
  * @}
  */

/**
  * @}
  */ 

#endif /* HAL_COMP_MODULE_ENABLED */

/**
  * @}
  */ 
#endif /* #if !defined (STM32L010xB) && !defined (STM32L010x8) && !defined (STM32L010x6) && !defined (STM32L010x4) */
/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
