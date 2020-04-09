/**
  ******************************************************************************
  * @file    stm32l0xx_hal_comp_ex.h
  * @author  MCD Application Team
  * @brief   Header file of COMP HAL Extended module.
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

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __STM32L0xx_HAL_COMP_EX_H
#define __STM32L0xx_HAL_COMP_EX_H

#ifdef __cplusplus
 extern "C" {
#endif

#if !defined(STM32L010xB) && !defined (STM32L010x8) && !defined (STM32L010x6) && !defined (STM32L010x4)
/* Includes ------------------------------------------------------------------*/
#include "stm32l0xx_hal_def.h"

/** @addtogroup STM32L0xx_HAL_Driver
  * @{
  */

/** @defgroup COMPEx COMPEx
  * @{
  */

/* Exported functions --------------------------------------------------------*/
/** @defgroup COMPEx_Exported_Functions COMPEx Exported Functions
  * @{
  */

/** @defgroup COMPEx_Exported_Functions_Group1 Extended COMP VREFINT setup functions
 * @{
 */
/* COMP specific functions to manage VREFINT *************************************/
void HAL_COMPEx_EnableVREFINT(void);
void HAL_COMPEx_DisableVREFINT(void);
   
/**
  * @}
  */

/**
  * @}
  */

/**
  * @}
  */

/**
  * @}
  */
#endif /* #if !defined(STM32L010xB) && !defined (STM32L010x8) && !defined (STM32L010x6) && !defined (STM32L010x4) */

#ifdef __cplusplus
}
#endif

#endif /* __STM32L0xx_HAL_COMP_EX_H */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/

