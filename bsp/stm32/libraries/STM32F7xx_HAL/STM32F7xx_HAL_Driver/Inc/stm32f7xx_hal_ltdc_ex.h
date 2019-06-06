/**
  ******************************************************************************
  * @file    stm32f7xx_hal_ltdc_ex.h
  * @author  MCD Application Team
  * @brief   Header file of LTDC HAL Extension module.
  ******************************************************************************
  * @attention
  *
<<<<<<< HEAD
  * <h2><center>&copy; COPYRIGHT(c) 2017 STMicroelectronics</center></h2>
  *
  * Redistribution and use in source and binary forms, with or without modification,
  * are permitted provided that the following conditions are met:
  *   1. Redistributions of source code must retain the above copyright notice,
  *      this list of conditions and the following disclaimer.
  *   2. Redistributions in binary form must reproduce the above copyright notice,
  *      this list of conditions and the following disclaimer in the documentation
  *      and/or other materials provided with the distribution.
  *   3. Neither the name of STMicroelectronics nor the names of its contributors
  *      may be used to endorse or promote products derived from this software
  *      without specific prior written permission.
  *
  * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
  * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
  * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
  * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
  * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
  * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
  * SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
  * CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
  * OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
  * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
  *
  ******************************************************************************
  */ 

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __STM32F7xx_HAL_LTDC_EX_H
#define __STM32F7xx_HAL_LTDC_EX_H

#ifdef __cplusplus
 extern "C" {
#endif

#if defined (STM32F769xx) || defined (STM32F779xx)
=======
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

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef STM32F7xx_HAL_LTDC_EX_H
#define STM32F7xx_HAL_LTDC_EX_H

#ifdef __cplusplus
extern "C" {
#endif

#if defined (LTDC) && defined (DSI)

>>>>>>> 49e424905b5922b07aa7166ec7a0eeb90adf58a8
/* Includes ------------------------------------------------------------------*/
#include "stm32f7xx_hal_def.h"
#include "stm32f7xx_hal_dsi.h"

/** @addtogroup STM32F7xx_HAL_Driver
  * @{
  */

/** @addtogroup LTDCEx
  * @{
  */

<<<<<<< HEAD
/* Exported types ------------------------------------------------------------*/ 
/* Exported constants --------------------------------------------------------*/
   
/** @defgroup LTDCEx_Exported_Constants   LTDCEx Exported Constants
  * @{
  */

/**
  * @}
  */

/* Exported macro ------------------------------------------------------------*/
/** @defgroup LTDCEx_Exported_Macros LTDC Exported Macros
  * @{
  */

/**
  * @}
  */

/* Exported functions --------------------------------------------------------*/
/** @defgroup LTDCEx_Exported_Functions LTDC Extended Exported Functions
  * @{
  */
HAL_StatusTypeDef HAL_LTDC_StructInitFromVideoConfig(LTDC_HandleTypeDef* hltdc, DSI_VidCfgTypeDef *VidCfg);
HAL_StatusTypeDef HAL_LTDC_StructInitFromAdaptedCommandConfig(LTDC_HandleTypeDef* hltdc, DSI_CmdCfgTypeDef *CmdCfg);
/**
  * @}
  */ 
 

 /* Private types -------------------------------------------------------------*/
/** @defgroup LTDCEx_Private_Types LTDCEx Private Types
  * @{
  */

/**
  * @}
  */ 

/* Private variables ---------------------------------------------------------*/
/** @defgroup LTDCEx_Private_Variables LTDCEx Private Variables
  * @{
=======
/* Exported types ------------------------------------------------------------*/
/* Exported constants --------------------------------------------------------*/
/* Exported macro ------------------------------------------------------------*/
/* Exported functions --------------------------------------------------------*/
/** @addtogroup LTDCEx_Exported_Functions
  * @{
  */

/** @addtogroup LTDCEx_Exported_Functions_Group1
  * @{
  */
HAL_StatusTypeDef HAL_LTDCEx_StructInitFromVideoConfig(LTDC_HandleTypeDef *hltdc, DSI_VidCfgTypeDef *VidCfg);
HAL_StatusTypeDef HAL_LTDCEx_StructInitFromAdaptedCommandConfig(LTDC_HandleTypeDef *hltdc, DSI_CmdCfgTypeDef *CmdCfg);
/**
  * @}
>>>>>>> 49e424905b5922b07aa7166ec7a0eeb90adf58a8
  */

/**
  * @}
<<<<<<< HEAD
  */ 

/* Private constants ---------------------------------------------------------*/
/** @defgroup LTDCEx_Private_Constants LTDCEx Private Constants
  * @{
  */

/**
  * @}
  */ 

/* Private macros ------------------------------------------------------------*/
/** @defgroup LTDCEx_Private_Macros LTDCEx Private Macros
  * @{
  */

 /**
  * @}
  */ 
  
/* Private functions ---------------------------------------------------------*/
/** @defgroup LTDCEx_Private_Functions LTDCEx Private Functions
  * @{
  */
=======
  */

/* Private types -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private constants ---------------------------------------------------------*/
/* Private macros ------------------------------------------------------------*/
/* Private functions ---------------------------------------------------------*/
>>>>>>> 49e424905b5922b07aa7166ec7a0eeb90adf58a8

/**
  * @}
  */

/**
  * @}
<<<<<<< HEAD
  */ 

/**
  * @}
  */

#endif /*STM32F769xx | STM32F779xx */
  
=======
  */

#endif /* LTDC && DSI */

>>>>>>> 49e424905b5922b07aa7166ec7a0eeb90adf58a8
#ifdef __cplusplus
}
#endif

<<<<<<< HEAD
#endif /* __STM32F7xx_HAL_LTDC_EX_H */
=======
#endif /* STM32F7xx_HAL_LTDC_EX_H */
>>>>>>> 49e424905b5922b07aa7166ec7a0eeb90adf58a8

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
