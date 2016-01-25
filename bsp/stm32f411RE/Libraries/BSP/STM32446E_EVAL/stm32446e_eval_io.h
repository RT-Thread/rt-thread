/**
  ******************************************************************************
  * @file    stm32446e_eval_io.h
  * @author  MCD Application Team
  * @version V1.1.0
  * @date    14-August-2015
  * @brief   This file contains the common defines and functions prototypes for
  *          the stm32446e_eval_io.c driver.
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
#ifndef __STM32446E_EVAL_IO_H
#define __STM32446E_EVAL_IO_H

#ifdef __cplusplus
 extern "C" {
#endif   
   
/* Includes ------------------------------------------------------------------*/
#include "stm32446e_eval.h"
/* Include IO component driver */
#include "../Components/mfxstm32l152/mfxstm32l152.h"  
   
/** @addtogroup BSP
  * @{
  */ 

/** @addtogroup STM32446E_EVAL
  * @{
  */
    
/** @defgroup STM32446E_EVAL_IO STM32446E-EVAL IO
  * @{
  */    

/** @defgroup STM32446E_EVAL_IO_Exported_Types STM32446E EVAL IO Exported Types
  * @{
  */

typedef enum
{
  BSP_IO_PIN_RESET = 0,
  BSP_IO_PIN_SET   = 1
}BSP_IO_PinStateTypeDef;
 
typedef enum 
{
  IO_OK       = 0,
  IO_ERROR    = 1,
  IO_TIMEOUT  = 2
}IO_StatusTypeDef;

/**
  * @}
  */

/** @defgroup STM32446E_EVAL_IO_Exported_Constants STM32446E EVAL IO Exported Constants
  * @{
  */    
#define IO_PIN_0                  ((uint32_t)0x0001)
#define IO_PIN_1                  ((uint32_t)0x0002)
#define IO_PIN_2                  ((uint32_t)0x0004)
#define IO_PIN_3                  ((uint32_t)0x0008)
#define IO_PIN_4                  ((uint32_t)0x0010)
#define IO_PIN_5                  ((uint32_t)0x0020)
#define IO_PIN_6                  ((uint32_t)0x0040)
#define IO_PIN_7                  ((uint32_t)0x0080)
#define IO_PIN_8                  ((uint32_t)0x0100)
#define IO_PIN_9                  ((uint32_t)0x0200)
#define IO_PIN_10                 ((uint32_t)0x0400)
#define IO_PIN_11                 ((uint32_t)0x0800)
#define IO_PIN_12                 ((uint32_t)0x1000)
#define IO_PIN_13                 ((uint32_t)0x2000)
#define IO_PIN_14                 ((uint32_t)0x4000)
#define IO_PIN_15                 ((uint32_t)0x8000)
#define IO_PIN_16               ((uint32_t)0x010000)
#define IO_PIN_17               ((uint32_t)0x020000)
#define IO_PIN_18               ((uint32_t)0x040000)
#define IO_PIN_19               ((uint32_t)0x080000)
#define IO_PIN_20               ((uint32_t)0x100000)
#define IO_PIN_21               ((uint32_t)0x200000)
#define IO_PIN_22               ((uint32_t)0x400000)
#define IO_PIN_23               ((uint32_t)0x800000)
#define IO_PIN_ALL              ((uint32_t)0xFFFFFF)  
/**
  * @}
  */

/** @defgroup STM32446E_EVAL_IO_Exported_Macro STM32446E EVAL IO Exported Macro
  * @{
  */ 
/**
  * @}
  */

/** @defgroup STM32446E_EVAL_IO_Exported_Functions STM32446E EVAL IO Exported Functions
  * @{
  */
uint8_t  BSP_IO_Init(void);
uint8_t  BSP_IO_DeInit(void);
uint8_t  BSP_IO_ConfigIrqOutPin(uint8_t IoIrqOutPinPolarity, uint8_t IoIrqOutPinType);
uint32_t BSP_IO_ITGetStatus(uint32_t IoPin);
void     BSP_IO_ITClear(void);
uint8_t  BSP_IO_ConfigPin(uint32_t IoPin, IO_ModeTypedef IoMode);
void     BSP_IO_WritePin(uint32_t IoPin, BSP_IO_PinStateTypeDef PinState);
uint32_t BSP_IO_ReadPin(uint32_t IoPin);
void     BSP_IO_TogglePin(uint32_t IoPin);

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

#endif /* __STM32446E_EVAL_IO_H */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
