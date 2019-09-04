/**
  ******************************************************************************
  * @file    stm32l1xx_hal_cryp_ex.c
  * @author  MCD Application Team
  * @brief   CRYPEx HAL module driver.
  *    
  *          This file provides firmware functions to manage the following 
  *          functionalities of the Cryptography (CRYP) extension peripheral:
  *           + Computation completed callback.
  *         
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2017 STMicroelectronics.
  * All rights reserved.</center></h2>
  *
  * This software component is licensed by ST under BSD 3-Clause license,
  * the "License"; You may not use this file except in compliance with the
  * License. You may obtain a copy of the License at:
  *                        opensource.org/licenses/BSD-3-Clause
  *
  ******************************************************************************  
  */ 

/* Includes ------------------------------------------------------------------*/
#include "stm32l1xx_hal.h"

#ifdef HAL_CRYP_MODULE_ENABLED

/** @addtogroup STM32L1xx_HAL_Driver
  * @{
  */

/** @defgroup CRYPEx CRYPEx
  * @brief CRYP HAL Extended module driver.
  * @{
  */

#if defined(STM32L162xC) || defined(STM32L162xCA) || defined(STM32L162xD) || defined(STM32L162xE) || defined(STM32L162xDX)

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/

/** @defgroup CRYPEx_Exported_Functions CRYPEx Exported Functions
  * @{
  */


/** @defgroup CRYPEx_Exported_Functions_Group1 Extended features functions 
 *  @brief    Extended features functions. 
 *
@verbatim   
 ===============================================================================
                 ##### Extended features functions #####
 =============================================================================== 
    [..]  This section provides callback functions:
      (+) Computation completed.

@endverbatim
  * @{
  */

/**
  * @brief  Computation completed callbacks.
  * @param  hcryp pointer to a CRYP_HandleTypeDef structure that contains
  *         the configuration information for CRYP module
  * @retval None
  */
__weak void HAL_CRYPEx_ComputationCpltCallback(CRYP_HandleTypeDef *hcryp)
{
  /* Prevent unused argument(s) compilation warning */
  UNUSED(hcryp);

  /* NOTE : This function Should not be modified, when the callback is needed,
            the HAL_CRYPEx_ComputationCpltCallback could be implemented in the user file
   */ 
}

/**
  * @}
  */


/**
  * @}
  */

#endif /* STM32L162xC || STM32L162xCA || STM32L162xD || STM32L162xE || STM32L162xDX*/

/**
  * @}
  */

/**
  * @}
  */

#endif /* HAL_CRYP_MODULE_ENABLED */
/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
