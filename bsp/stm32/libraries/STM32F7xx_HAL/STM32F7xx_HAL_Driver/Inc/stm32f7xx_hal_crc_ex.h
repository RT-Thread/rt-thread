/**
  ******************************************************************************
  * @file    stm32f7xx_hal_crc_ex.h
  * @author  MCD Application Team
<<<<<<< HEAD
  * @brief   Header file of CRC HAL extension module.
  ******************************************************************************
  * @attention
  *
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
#ifndef __STM32F7xx_HAL_CRC_EX_H
#define __STM32F7xx_HAL_CRC_EX_H

#ifdef __cplusplus
 extern "C" {
=======
  * @brief   Header file of CRC HAL extended module.
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

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef STM32F7xx_HAL_CRC_EX_H
#define STM32F7xx_HAL_CRC_EX_H

#ifdef __cplusplus
extern "C" {
>>>>>>> 49e424905b5922b07aa7166ec7a0eeb90adf58a8
#endif

/* Includes ------------------------------------------------------------------*/
#include "stm32f7xx_hal_def.h"

/** @addtogroup STM32F7xx_HAL_Driver
  * @{
  */

<<<<<<< HEAD
/** @defgroup CRCEx CRCEx
  * @{
  */ 

/* Exported types ------------------------------------------------------------*/ 
/* Exported constants --------------------------------------------------------*/

/** @defgroup CRCEx_Exported_Constants CRC Extended exported constants
 * @{
 */

/** @defgroup CRCEx_Input_Data_Inversion CRC Extended input data inversion modes
  * @{
  */
#define CRC_INPUTDATA_INVERSION_NONE              ((uint32_t)0x00000000U)
#define CRC_INPUTDATA_INVERSION_BYTE              ((uint32_t)CRC_CR_REV_IN_0)
#define CRC_INPUTDATA_INVERSION_HALFWORD          ((uint32_t)CRC_CR_REV_IN_1)
#define CRC_INPUTDATA_INVERSION_WORD              ((uint32_t)CRC_CR_REV_IN)

#define IS_CRC_INPUTDATA_INVERSION_MODE(__MODE__)     (((__MODE__) == CRC_INPUTDATA_INVERSION_NONE) || \
                                                       ((__MODE__) == CRC_INPUTDATA_INVERSION_BYTE) || \
                                                       ((__MODE__) == CRC_INPUTDATA_INVERSION_HALFWORD) || \
                                                       ((__MODE__) == CRC_INPUTDATA_INVERSION_WORD))
=======
/** @addtogroup CRCEx
  * @{
  */

/* Exported types ------------------------------------------------------------*/
/* Exported constants --------------------------------------------------------*/
/** @defgroup CRCEx_Exported_Constants CRC Extended Exported Constants
  * @{
  */

/** @defgroup CRCEx_Input_Data_Inversion Input Data Inversion Modes
  * @{
  */
#define CRC_INPUTDATA_INVERSION_NONE               0x00000000U     /*!< No input data inversion            */
#define CRC_INPUTDATA_INVERSION_BYTE               CRC_CR_REV_IN_0 /*!< Byte-wise input data inversion     */
#define CRC_INPUTDATA_INVERSION_HALFWORD           CRC_CR_REV_IN_1 /*!< HalfWord-wise input data inversion */
#define CRC_INPUTDATA_INVERSION_WORD               CRC_CR_REV_IN   /*!< Word-wise input data inversion     */
>>>>>>> 49e424905b5922b07aa7166ec7a0eeb90adf58a8
/**
  * @}
  */

<<<<<<< HEAD
/** @defgroup CRCEx_Output_Data_Inversion CRC Extended output data inversion modes
  * @{
  */
#define CRC_OUTPUTDATA_INVERSION_DISABLE         ((uint32_t)0x00000000U)
#define CRC_OUTPUTDATA_INVERSION_ENABLE          ((uint32_t)CRC_CR_REV_OUT)

#define IS_CRC_OUTPUTDATA_INVERSION_MODE(__MODE__)    (((__MODE__) == CRC_OUTPUTDATA_INVERSION_DISABLE) || \
                                                       ((__MODE__) == CRC_OUTPUTDATA_INVERSION_ENABLE))
/**                                               
  * @}
  */


/**
 * @}
 */
/* Exported macro ------------------------------------------------------------*/

/** @defgroup CRCEx_Exported_Macros CRC Extended exported macros
  * @{
  */
    
/**
  * @brief  Set CRC output reversal
  * @param  __HANDLE__     CRC handle
  * @retval None.
  */
#define  __HAL_CRC_OUTPUTREVERSAL_ENABLE(__HANDLE__) ((__HANDLE__)->Instance->CR |= CRC_CR_REV_OUT)   

/**
  * @brief  Unset CRC output reversal
  * @param  __HANDLE__     CRC handle
  * @retval None.
  */
#define __HAL_CRC_OUTPUTREVERSAL_DISABLE(__HANDLE__) ((__HANDLE__)->Instance->CR &= ~(CRC_CR_REV_OUT))   

/**
  * @brief  Set CRC non-default polynomial
  * @param  __HANDLE__     CRC handle
  * @param  __POLYNOMIAL__ 7, 8, 16 or 32-bit polynomial  
  * @retval None.
=======
/** @defgroup CRCEx_Output_Data_Inversion Output Data Inversion Modes
  * @{
  */
#define CRC_OUTPUTDATA_INVERSION_DISABLE         0x00000000U       /*!< No output data inversion       */
#define CRC_OUTPUTDATA_INVERSION_ENABLE          CRC_CR_REV_OUT    /*!< Bit-wise output data inversion */
/**
  * @}
  */

/**
  * @}
  */

/* Exported macro ------------------------------------------------------------*/
/** @defgroup CRCEx_Exported_Macros CRC Extended Exported Macros
  * @{
  */

/**
  * @brief  Set CRC output reversal
  * @param  __HANDLE__ CRC handle
  * @retval None
  */
#define  __HAL_CRC_OUTPUTREVERSAL_ENABLE(__HANDLE__) ((__HANDLE__)->Instance->CR |= CRC_CR_REV_OUT)

/**
  * @brief  Unset CRC output reversal
  * @param  __HANDLE__ CRC handle
  * @retval None
  */
#define __HAL_CRC_OUTPUTREVERSAL_DISABLE(__HANDLE__) ((__HANDLE__)->Instance->CR &= ~(CRC_CR_REV_OUT))

/**
  * @brief  Set CRC non-default polynomial
  * @param  __HANDLE__ CRC handle
  * @param  __POLYNOMIAL__ 7, 8, 16 or 32-bit polynomial
  * @retval None
>>>>>>> 49e424905b5922b07aa7166ec7a0eeb90adf58a8
  */
#define __HAL_CRC_POLYNOMIAL_CONFIG(__HANDLE__, __POLYNOMIAL__) ((__HANDLE__)->Instance->POL = (__POLYNOMIAL__))

/**
  * @}
  */

<<<<<<< HEAD

/** @defgroup CRCEx_Exported_Functions CRC Extended Exported Functions
  * @{
  */

/** @defgroup CRCEx_Exported_Functions_Group1 Extended CRC features functions
  * @{
  */
/* Exported functions --------------------------------------------------------*/
=======
/* Private macros --------------------------------------------------------*/
/** @defgroup CRCEx_Private_Macros CRC Extended Private Macros
  * @{
  */

#define IS_CRC_INPUTDATA_INVERSION_MODE(MODE)     (((MODE) == CRC_INPUTDATA_INVERSION_NONE)     || \
                                                   ((MODE) == CRC_INPUTDATA_INVERSION_BYTE)     || \
                                                   ((MODE) == CRC_INPUTDATA_INVERSION_HALFWORD) || \
                                                   ((MODE) == CRC_INPUTDATA_INVERSION_WORD))

#define IS_CRC_OUTPUTDATA_INVERSION_MODE(MODE)    (((MODE) == CRC_OUTPUTDATA_INVERSION_DISABLE) || \
                                                   ((MODE) == CRC_OUTPUTDATA_INVERSION_ENABLE))

/**
  * @}
  */

/* Exported functions --------------------------------------------------------*/

/** @addtogroup CRCEx_Exported_Functions
  * @{
  */

/** @addtogroup CRCEx_Exported_Functions_Group1
  * @{
  */
>>>>>>> 49e424905b5922b07aa7166ec7a0eeb90adf58a8
/* Initialization and de-initialization functions  ****************************/
HAL_StatusTypeDef HAL_CRCEx_Polynomial_Set(CRC_HandleTypeDef *hcrc, uint32_t Pol, uint32_t PolyLength);
HAL_StatusTypeDef HAL_CRCEx_Input_Data_Reverse(CRC_HandleTypeDef *hcrc, uint32_t InputReverseMode);
HAL_StatusTypeDef HAL_CRCEx_Output_Data_Reverse(CRC_HandleTypeDef *hcrc, uint32_t OutputReverseMode);

<<<<<<< HEAD
/* Peripheral Control functions ***********************************************/
/* Peripheral State and Error functions ***************************************/

=======
>>>>>>> 49e424905b5922b07aa7166ec7a0eeb90adf58a8
/**
  * @}
  */

/**
  * @}
  */

<<<<<<< HEAD

/**
  * @}
  */ 
=======
/**
  * @}
  */
>>>>>>> 49e424905b5922b07aa7166ec7a0eeb90adf58a8

/**
  * @}
  */
<<<<<<< HEAD
  
=======

>>>>>>> 49e424905b5922b07aa7166ec7a0eeb90adf58a8
#ifdef __cplusplus
}
#endif

<<<<<<< HEAD
#endif /* __STM32F7xx_HAL_CRC_EX_H */
=======
#endif /* STM32F7xx_HAL_CRC_EX_H */
>>>>>>> 49e424905b5922b07aa7166ec7a0eeb90adf58a8

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
