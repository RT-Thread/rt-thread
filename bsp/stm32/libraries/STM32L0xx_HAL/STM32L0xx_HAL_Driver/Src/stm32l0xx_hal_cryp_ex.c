/**
  ******************************************************************************
  * @file    stm32l0xx_hal_cryp_ex.c
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

#if defined (STM32L021xx) || defined (STM32L041xx) || defined (STM32L062xx) || defined (STM32L063xx) || defined (STM32L081xx) || defined (STM32L082xx) || defined (STM32L083xx)
/* Includes ------------------------------------------------------------------*/
#include "stm32l0xx_hal.h"

/** @addtogroup STM32L0xx_HAL_Driver
  * @{
  */
#ifdef HAL_CRYP_MODULE_ENABLED


/** @addtogroup CRYPEx
  * @brief CRYP HAL Extended module driver.
  * @{
  */


/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/

/** @addtogroup CRYPEx_Exported_Functions
  * @{
  */


/** @addtogroup CRYPEx_Exported_Functions_Group1
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
            the HAL_CRYP_ComputationCpltCallback could be implemented in the user file
   */ 
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

#endif /* HAL_CRYP_MODULE_ENABLED */

/**
  * @}
  */
#endif /* STM32L021xx || STM32L041xx || STM32L062xx || STM32L063xx || STM32L081xx || STM32L082xx || STM32L083xx */
/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/

