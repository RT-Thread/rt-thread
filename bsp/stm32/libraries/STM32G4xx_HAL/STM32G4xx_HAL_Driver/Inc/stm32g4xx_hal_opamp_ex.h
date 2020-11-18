/**
  ******************************************************************************
  * @file    stm32g4xx_hal_opamp_ex.h
  * @author  MCD Application Team
  * @brief   Header file of OPAMP HAL Extended module.
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2019 STMicroelectronics.
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
#ifndef STM32G4xx_HAL_OPAMP_EX_H
#define STM32G4xx_HAL_OPAMP_EX_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "stm32g4xx_hal_def.h"

/** @addtogroup STM32G4xx_HAL_Driver
  * @{
  */

/** @addtogroup OPAMPEx OPAMPEx
  * @{
  */
/* Exported types ------------------------------------------------------------*/
/* Exported constants --------------------------------------------------------*/
/* Exported macro ------------------------------------------------------------*/
/* Exported functions --------------------------------------------------------*/
/** @addtogroup OPAMPEx_Exported_Functions OPAMP Extended Exported Functions
  * @{
  */

/** @addtogroup OPAMPEx_Exported_Functions_Group1 Extended Input and Output operation functions
  * @{
  */

/* I/O operation functions  *****************************************************/

#if defined(STM32G473xx) || defined(STM32G474xx) || defined(STM32G483xx) || defined(STM32G484xx)
HAL_StatusTypeDef HAL_OPAMPEx_SelfCalibrateAll(OPAMP_HandleTypeDef *hopamp1, OPAMP_HandleTypeDef *hopamp2,
                                               OPAMP_HandleTypeDef *hopamp3, OPAMP_HandleTypeDef *hopamp4, OPAMP_HandleTypeDef *hopamp5, OPAMP_HandleTypeDef *hopamp6);
#elif defined(STM32GBK1CB) || defined(STM32G431xx) || defined(STM32G441xx) || defined(STM32G471xx)
HAL_StatusTypeDef HAL_OPAMPEx_SelfCalibrateAll(OPAMP_HandleTypeDef *hopamp1, OPAMP_HandleTypeDef *hopamp2,
                                               OPAMP_HandleTypeDef *hopamp3);
#endif

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


#ifdef __cplusplus
}
#endif


#endif /* STM32G4xx_HAL_OPAMP_EX_H */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
