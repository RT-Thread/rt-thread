/**
  ******************************************************************************
  * @file    stm32h7xx_ll_delayblock.h
  * @author  MCD Application Team
  * @brief   Header file of Delay Block module.
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
#ifndef __STM32H7xx_LL_DLYB_H
#define __STM32H7xx_LL_DLYB_H

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

/** @defgroup DLYB_Instance DLYB Instance
  * @{
  */
#define IS_DLYB_ALL_INSTANCE(INSTANCE)  (((INSTANCE) == DLYB_SDMMC1) || \
                                         ((INSTANCE) == DLYB_SDMMC2) || \
                                         ((INSTANCE) == DLYB_QUADSPI))
/**
  * @}
  */

/**
  * @}
  */ 
 
/* Peripheral Control functions  ************************************************/
/** @addtogroup HAL_DELAYBLOCK_LL_Group3 Delay Block functions
  * @{
  */
HAL_StatusTypeDef DelayBlock_Enable(DLYB_TypeDef *dlyb);
HAL_StatusTypeDef DelayBlock_Disable(DLYB_TypeDef *dlyb);

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

#endif /* __STM32H7xx_LL_DLYB_H */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
