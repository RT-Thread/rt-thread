/**
  ******************************************************************************
  * @file    stm32u5xx_hal_crc_ex.h
  * @author  MCD Application Team
  * @brief   Header file of CRC HAL extended module.
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2021 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef STM32U5xx_HAL_CRC_EX_H
#define STM32U5xx_HAL_CRC_EX_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "stm32u5xx_hal_def.h"

/** @addtogroup STM32U5xx_HAL_Driver
  * @{
  */

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
/**
  * @}
  */

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
  */
#define __HAL_CRC_POLYNOMIAL_CONFIG(__HANDLE__, __POLYNOMIAL__) ((__HANDLE__)->Instance->POL = (__POLYNOMIAL__))

/**
  * @}
  */

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
/* Initialization and de-initialization functions  ****************************/
HAL_StatusTypeDef HAL_CRCEx_Polynomial_Set(CRC_HandleTypeDef *hcrc, uint32_t Pol, uint32_t PolyLength);
HAL_StatusTypeDef HAL_CRCEx_Input_Data_Reverse(CRC_HandleTypeDef *hcrc, uint32_t InputReverseMode);
HAL_StatusTypeDef HAL_CRCEx_Output_Data_Reverse(CRC_HandleTypeDef *hcrc, uint32_t OutputReverseMode);

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

#endif /* STM32U5xx_HAL_CRC_EX_H */
