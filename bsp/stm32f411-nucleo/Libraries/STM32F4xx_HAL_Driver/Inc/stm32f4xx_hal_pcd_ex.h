/**
  ******************************************************************************
  * @file    stm32f4xx_hal_pcd_ex.h
  * @author  MCD Application Team
  * @version V1.4.3
  * @date    11-December-2015
  * @brief   Header file of PCD HAL module.
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; COPYRIGHT(c) 2015 STMicroelectronics</center></h2>
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
#ifndef __STM32F4xx_HAL_PCD_EX_H
#define __STM32F4xx_HAL_PCD_EX_H

#ifdef __cplusplus
 extern "C" {
#endif
#if defined(STM32F405xx) || defined(STM32F415xx) || defined(STM32F407xx) || defined(STM32F417xx) || \
    defined(STM32F427xx) || defined(STM32F437xx) || defined(STM32F429xx) || defined(STM32F439xx) || \
    defined(STM32F401xC) || defined(STM32F401xE) || defined(STM32F411xE) || defined(STM32F446xx) || \
    defined(STM32F469xx) || defined(STM32F479xx)
/* Includes ------------------------------------------------------------------*/
#include "stm32f4xx_hal_def.h"
   
/** @addtogroup STM32F4xx_HAL_Driver
  * @{
  */

/** @addtogroup PCDEx
  * @{
  */
/* Exported types ------------------------------------------------------------*/
#if defined(STM32F446xx) || defined(STM32F469xx) || defined(STM32F479xx)
typedef enum  
{
  PCD_LPM_L0_ACTIVE = 0x00, /* on */
  PCD_LPM_L1_ACTIVE = 0x01, /* LPM L1 sleep */
}PCD_LPM_MsgTypeDef;
#endif /* STM32F446xx || STM32F469xx || STM32F479xx */

/* Exported constants --------------------------------------------------------*/
/* Exported macros -----------------------------------------------------------*/
/* Exported functions --------------------------------------------------------*/
/** @addtogroup PCDEx_Exported_Functions PCD Extended Exported Functions
  * @{
  */
/** @addtogroup PCDEx_Exported_Functions_Group1 Peripheral Control functions
  * @{
  */
HAL_StatusTypeDef HAL_PCDEx_SetTxFiFo(PCD_HandleTypeDef *hpcd, uint8_t fifo, uint16_t size);
HAL_StatusTypeDef HAL_PCDEx_SetRxFiFo(PCD_HandleTypeDef *hpcd, uint16_t size);
#if defined(STM32F446xx) || defined(STM32F469xx) || defined(STM32F479xx)
HAL_StatusTypeDef HAL_PCDEx_ActivateLPM(PCD_HandleTypeDef *hpcd);
HAL_StatusTypeDef HAL_PCDEx_DeActivateLPM(PCD_HandleTypeDef *hpcd);
void HAL_PCDEx_LPM_Callback(PCD_HandleTypeDef *hpcd, PCD_LPM_MsgTypeDef msg);
#endif /* STM32F446xx || STM32F469xx || STM32F479xx */


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
#endif /* STM32F405xx || STM32F415xx || STM32F407xx || STM32F417xx || STM32F427xx || STM32F437xx || STM32F429xx || STM32F439xx ||
          STM32F401xC || STM32F401xE || STM32F411xE || STM32F446xx || STM32F469xx || STM32F479xx */
#ifdef __cplusplus
}
#endif


#endif /* __STM32F4xx_HAL_PCD_EX_H */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
