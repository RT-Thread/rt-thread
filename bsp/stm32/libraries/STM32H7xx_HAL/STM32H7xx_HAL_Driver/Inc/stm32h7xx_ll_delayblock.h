/**
  ******************************************************************************
  * @file    stm32h7xx_ll_delayblock.h
  * @author  MCD Application Team
  * @brief   Header file of Delay Block module.
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2017 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef STM32H7xx_LL_DLYB_H
#define STM32H7xx_LL_DLYB_H

#ifdef __cplusplus
 extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "stm32h7xx_hal_def.h"

/** @addtogroup STM32H7xx_HAL_Driver
  * @{
  */

/** @addtogroup DELAYBLOCK_LL
  * @{
  */ 

/* Exported types ------------------------------------------------------------*/ 
/** @defgroup DELAYBLOCK_LL_Exported_Types DELAYBLOCK_LL Exported Types
  * @{
  */
  

/**
  * @}
  */
  
/* Exported constants --------------------------------------------------------*/
/** @defgroup DLYB_Exported_Constants Delay Block Exported Constants
  * @{
  */


#define DLYB_MAX_UNIT   ((uint32_t)0x00000080U) /*!< Max UNIT value (128)  */
#define DLYB_MAX_SELECT ((uint32_t)0x0000000CU) /*!< Max SELECT value (12)  */

/**
  * @}
  */

/** @addtogroup DelayBlock_LL_Exported_Functions
  * @{
  */
 
/* Peripheral Control functions  ************************************************/
/** @addtogroup HAL_DELAY_LL_Group1
  * @{
  */
HAL_StatusTypeDef DelayBlock_Enable(DLYB_TypeDef *DLYBx);
HAL_StatusTypeDef DelayBlock_Disable(DLYB_TypeDef *DLYBx);
HAL_StatusTypeDef DelayBlock_Configure(DLYB_TypeDef *DLYBx, uint32_t PhaseSel, uint32_t Units);

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

#endif /* STM32H7xx_LL_DLYB_H */

