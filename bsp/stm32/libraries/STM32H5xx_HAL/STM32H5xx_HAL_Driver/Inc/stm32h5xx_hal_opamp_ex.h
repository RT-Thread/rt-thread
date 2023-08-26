/**
  **********************************************************************************************************************
  * @file    stm32h5xx_hal_opamp_ex.h
  * @author  MCD Application Team
  * @brief   Header file of OPAMP HAL Extended module.
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

/* Define to prevent recursive inclusion -----------------------------------------------------------------------------*/
#ifndef STM32H5xx_HAL_OPAMP_EX_H
#define STM32H5xx_HAL_OPAMP_EX_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ----------------------------------------------------------------------------------------------------------*/
#include "stm32h5xx_hal_def.h"

/** @addtogroup STM32H5xx_HAL_Driver
  * @{
  */
#if defined (OPAMP1)

/** @addtogroup OPAMPEx
  * @{
  */
/* Exported types ----------------------------------------------------------------------------------------------------*/
/* Exported constants ------------------------------------------------------------------------------------------------*/
/* Exported macro ----------------------------------------------------------------------------------------------------*/
/* Exported functions ------------------------------------------------------------------------------------------------*/
/** @addtogroup OPAMPEx_Exported_Functions OPAMPEx Exported Functions
  * @{
  */

/* Peripheral Control functions */
/** @addtogroup OPAMPEx_Exported_Functions_Group1
  * @{
  */
HAL_StatusTypeDef HAL_OPAMPEx_Unlock(OPAMP_HandleTypeDef *hopamp);
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

/**
  * @}
  */

#ifdef __cplusplus
}
#endif

#endif /* STM32H5xx_HAL_OPAMP_EX_H */
