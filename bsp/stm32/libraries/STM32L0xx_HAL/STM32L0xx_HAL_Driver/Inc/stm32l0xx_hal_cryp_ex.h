/**
  ******************************************************************************
  * @file    stm32l0xx_hal_cryp_ex.h
  * @author  MCD Application Team
  * @brief   Header file of CRYPEx HAL module.
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
#ifndef __STM32L0xx_HAL_CRYP_EX_H
#define __STM32L0xx_HAL_CRYP_EX_H

#ifdef __cplusplus
 extern "C" {
#endif
   
#if defined (STM32L021xx) || defined (STM32L041xx) || defined (STM32L061xx) || defined (STM32L062xx) || defined (STM32L063xx) || (STM32L081xx) || defined (STM32L082xx) || defined (STM32L083xx)

/* Includes ------------------------------------------------------------------*/
#include "stm32l0xx_hal_def.h"

/** @addtogroup STM32L0xx_HAL_Driver
  * @{
  */

/** @defgroup CRYPEx CRYPEx
  * @{
  */ 

/* Exported types ------------------------------------------------------------*/ 
/* Exported constants --------------------------------------------------------*/
/* Exported functions --------------------------------------------------------*/

/** @defgroup CRYPEx_Exported_Functions CRYPEx Exported Functions
  * @{
  */

/** @defgroup CRYPEx_Exported_Functions_Group1 Extended features functions
  * @{
  */

/* CallBack functions  ********************************************************/
void HAL_CRYPEx_ComputationCpltCallback(CRYP_HandleTypeDef *hcryp);

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
  
#endif /* STM32L021xx || STM32L041xx || STM32L061xx || STM32L062xx || STM32L063xx || STM32L081xx || STM32L082xx || STM32L083xx */

#ifdef __cplusplus
}
#endif

#endif /* __STM32L0xx_HAL_CRYP_EX_H */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/

