/**
  ******************************************************************************
  * @file    stm32446e_eval_ts.h
  * @author  MCD Application Team
  * @version V1.1.0
  * @date    14-August-2015
  * @brief   This file contains the common defines and functions prototypes for
  *          the stm32446e_eval_ts.c driver.
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
#ifndef __STM32446E_EVAL_TS_H
#define __STM32446E_EVAL_TS_H

#ifdef __cplusplus
 extern "C" {
#endif   
   
/* Includes ------------------------------------------------------------------*/
#include "stm32446e_eval.h"
/* Include IOExpander(MFX) component Driver */ 
#include "../Components/mfxstm32l152/mfxstm32l152.h"
   
/** @addtogroup BSP
  * @{
  */ 

/** @addtogroup STM32446E_EVAL
  * @{
  */
    
/** @defgroup STM32446E_EVAL_TS STM32446E-EVAL TS
  * @{
  */    

/** @defgroup STM32446E_EVAL_TS_Exported_Types STM32446E EVAL TS Exported Types
  * @{
  */
typedef struct
{
  uint16_t TouchDetected;
  uint16_t x;
  uint16_t y;
  uint16_t z;
}TS_StateTypeDef;
/**
  * @}
  */ 

/** @defgroup STM32446E_EVAL_TS_Exported_Constants STM32446E EVAL TS Exported Constants
  * @{
  */
#define TS_SWAP_NONE                    ((uint8_t)0x00)
#define TS_SWAP_X                       ((uint8_t)0x01)
#define TS_SWAP_Y                       ((uint8_t)0x02)
#define TS_SWAP_XY                      ((uint8_t)0x04)

typedef enum 
{
  TS_OK       = 0x00,
  TS_ERROR    = 0x01,
  TS_TIMEOUT  = 0x02
}TS_StatusTypeDef;

/**
  * @}
  */ 

/** @defgroup STM32446E_EVAL_TS_Exported_Macros STM32446E EVAL TS Exported Macros
  * @{
  */ 
/**
  * @}
  */ 

/** @defgroup STM32446E_EVAL_TS_Exported_Functions  STM32446E EVAL TS Exported Functions
  * @{
  */
uint8_t BSP_TS_Init(uint16_t xSize, uint16_t ySize);
uint8_t BSP_TS_DeInit(void);
uint8_t BSP_TS_GetState(TS_StateTypeDef *TS_State);
uint8_t BSP_TS_ITEnable(void);
uint8_t BSP_TS_ITDisable(void);
uint8_t BSP_TS_ITConfig(void);
uint8_t BSP_TS_ITGetStatus(void);
void    BSP_TS_ITClear(void);
void    BSP_TS_FIFOClear(void);

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

#endif /* __STM32446E_EVAL_TS_H */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
