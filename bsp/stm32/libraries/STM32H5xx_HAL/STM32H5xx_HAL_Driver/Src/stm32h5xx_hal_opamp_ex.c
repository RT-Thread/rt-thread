/**
  **********************************************************************************************************************
  * @file    stm32h5xx_hal_opamp_ex.c
  * @author  MCD Application Team
  * @brief   Extended OPAMP HAL module driver.
  *          This file provides firmware functions to manage the following
  *          functionalities of the operational amplifier(s) peripheral:
  *           + Extended Initialization and de-initialization functions
  *           + Extended Peripheral Control functions
  *
  @verbatim
  **********************************************************************************************************************
  * @attention
  *
  * Copyright (c) 2023 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  **********************************************************************************************************************
  */

/* Includes ----------------------------------------------------------------------------------------------------------*/
#include "stm32h5xx_hal.h"

/** @addtogroup STM32H5xx_HAL_Driver
  * @{
  */

/** @defgroup OPAMPEx OPAMPEx
  * @brief OPAMP Extended HAL module driver
  * @{
  */

#ifdef HAL_OPAMP_MODULE_ENABLED

#if defined (OPAMP1)

/* Private typedef ---------------------------------------------------------------------------------------------------*/
/* Private define ----------------------------------------------------------------------------------------------------*/
/* Private macro -----------------------------------------------------------------------------------------------------*/
/* Private variables -------------------------------------------------------------------------------------------------*/
/* Private function prototypes ---------------------------------------------------------------------------------------*/
/* Exported functions ------------------------------------------------------------------------------------------------*/

/** @defgroup OPAMPEx_Exported_Functions OPAMP Extended Exported Functions
  * @{
  */

/** @defgroup OPAMPEx_Exported_Functions_Group1 Peripheral Control functions
  *  @brief    Peripheral Control functions
  *
@verbatim
 =======================================================================================================================
                                        ##### Peripheral Control functions #####
 =======================================================================================================================
    [..]
      (+) OPAMP unlock.

@endverbatim
  * @{
  */

/**
  * @brief  Unlock the selected OPAMP configuration.
  * @note   This function must be called only when OPAMP is in state "locked".
  * @param  hopamp: OPAMP handle
  * @retval HAL status
  */
HAL_StatusTypeDef HAL_OPAMPEx_Unlock(OPAMP_HandleTypeDef *hopamp)
{
  HAL_StatusTypeDef status = HAL_OK;

  /* Check the OPAMP handle allocation */
  /* Check if OPAMP locked */
  if (hopamp == NULL)
  {
    status = HAL_ERROR;
  }
  /* Check the OPAMP handle allocation */
  /* Check if OPAMP locked */
  else if (hopamp->State == HAL_OPAMP_STATE_BUSYLOCKED)
  {
    /* Check the parameter */
    assert_param(IS_OPAMP_ALL_INSTANCE(hopamp->Instance));

    /* OPAMP state changed to locked */
    hopamp->State = HAL_OPAMP_STATE_BUSY;
  }
  else
  {
    status = HAL_ERROR;
  }

  return status;
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

/**
  * @}
  */

#endif /* OPAMP1 */

#endif /* HAL_OPAMP_MODULE_ENABLED */
