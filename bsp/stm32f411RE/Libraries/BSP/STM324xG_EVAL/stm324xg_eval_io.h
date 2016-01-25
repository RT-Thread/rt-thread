/**
  ******************************************************************************
  * @file    stm324xg_eval_io.h
  * @author  MCD Application Team
  * @version V2.1.0
  * @date    14-August-2015
  * @brief   This file contains the common defines and functions prototypes for
  *          the stm324xg_eval_io.c driver.
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
#ifndef __STM324xG_EVAL_IO_H
#define __STM324xG_EVAL_IO_H

#ifdef __cplusplus
 extern "C" {
#endif   
   
/* Includes ------------------------------------------------------------------*/
#include "stm324xg_eval.h"
/* Include IO component driver */
#include "../Components/stmpe811/stmpe811.h"
   
/** @addtogroup BSP
  * @{
  */ 

/** @addtogroup STM324xG_EVAL
  * @{
  */
    
/** @defgroup STM324xG_EVAL_IO
  * @{
  */    

/** @defgroup STM324xG_EVAL_IO_Exported_Types
  * @{
  */
typedef enum 
{
  IO_OK       = 0x00,
  IO_ERROR    = 0x01,
  IO_TIMEOUT  = 0x02
}IO_StatusTypeDef;
/**
  * @}
  */ 

/** @defgroup STM324xG_EVAL_IO_Exported_Constants
  * @{
  */
#define IO_PIN_0                     0x01
#define IO_PIN_1                     0x02
#define IO_PIN_2                     0x04
#define IO_PIN_3                     0x08
#define IO_PIN_4                     0x10
#define IO_PIN_5                     0x20
#define IO_PIN_6                     0x40
#define IO_PIN_7                     0x80
#define IO_PIN_ALL                   0xFF
/**
  * @}
  */ 

/** @defgroup STM324xG_EVAL_IO_Exported_Macros
  * @{
  */
/**
  * @}
  */ 

/** @defgroup STM324xG_EVAL_IO_Exported_Functions
  * @{
  */
uint8_t  BSP_IO_Init(void);
void     BSP_IO_ITClear(uint16_t IO_Pin);
uint8_t  BSP_IO_ITGetStatus(uint16_t IO_Pin);
uint8_t  BSP_IO_ConfigPin(uint16_t IO_Pin, IO_ModeTypedef IO_Mode);
void     BSP_IO_WritePin(uint16_t IO_Pin, uint8_t PinState);
uint16_t BSP_IO_ReadPin(uint16_t IO_Pin);
void     BSP_IO_TogglePin(uint16_t IO_Pin);

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

#endif /* __STM324xG_EVAL_IO_H */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
