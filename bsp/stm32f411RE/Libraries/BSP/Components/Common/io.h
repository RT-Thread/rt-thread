/**
  ******************************************************************************
  * @file    io.h
  * @author  MCD Application Team
  * @version V4.0.1
  * @date    21-July-2015
  * @brief   This file contains all the functions prototypes for the IO driver.
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
#ifndef __IO_H
#define __IO_H

#ifdef __cplusplus
 extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include <stdint.h>

/** @addtogroup BSP
  * @{
  */

/** @addtogroup Components
  * @{
  */
    
/** @addtogroup IO
  * @{
  */

/** @defgroup IO_Exported_Types
  * @{
  */

/**
  * @brief  IO Bit SET and Bit RESET enumeration
  */
typedef enum
{
  IO_PIN_RESET = 0,
  IO_PIN_SET
}IO_PinState;

typedef enum
{
   IO_MODE_INPUT = 0,   /* input floating */
   IO_MODE_OUTPUT,      /* output Push Pull */
   IO_MODE_IT_RISING_EDGE,   /* float input - irq detect on rising edge */
   IO_MODE_IT_FALLING_EDGE,  /* float input - irq detect on falling edge */
   IO_MODE_IT_LOW_LEVEL,     /* float input - irq detect on low level */
   IO_MODE_IT_HIGH_LEVEL,    /* float input - irq detect on high level */
   /* following modes only available on MFX*/
   IO_MODE_ANALOG,           /* analog mode */
   IO_MODE_OFF,              /* when pin isn't used*/
   IO_MODE_INPUT_PU,         /* input with internal pull up resistor */
   IO_MODE_INPUT_PD,         /* input with internal pull down resistor */
   IO_MODE_OUTPUT_OD,          /* Open Drain output without internal resistor */
   IO_MODE_OUTPUT_OD_PU,       /* Open Drain output with  internal pullup resistor */
   IO_MODE_OUTPUT_OD_PD,       /* Open Drain output with  internal pulldown resistor */
   IO_MODE_OUTPUT_PP,          /* PushPull output without internal resistor */
   IO_MODE_OUTPUT_PP_PU,       /* PushPull output with  internal pullup resistor */
   IO_MODE_OUTPUT_PP_PD,       /* PushPull output with  internal pulldown resistor */
   IO_MODE_IT_RISING_EDGE_PU,   /* push up resistor input - irq on rising edge  */
   IO_MODE_IT_RISING_EDGE_PD,   /* push dw resistor input - irq on rising edge  */
   IO_MODE_IT_FALLING_EDGE_PU,  /* push up resistor input - irq on falling edge */
   IO_MODE_IT_FALLING_EDGE_PD,  /* push dw resistor input - irq on falling edge */
   IO_MODE_IT_LOW_LEVEL_PU,     /* push up resistor input - irq detect on low level */
   IO_MODE_IT_LOW_LEVEL_PD,     /* push dw resistor input - irq detect on low level */
   IO_MODE_IT_HIGH_LEVEL_PU,    /* push up resistor input - irq detect on high level */
   IO_MODE_IT_HIGH_LEVEL_PD,    /* push dw resistor input - irq detect on high level */

}IO_ModeTypedef;

/** @defgroup IO_Driver_structure  IO Driver structure
  * @{
  */
typedef struct
{  
  void       (*Init)(uint16_t);
  uint16_t   (*ReadID)(uint16_t);
  void       (*Reset)(uint16_t);
  
  void       (*Start)(uint16_t, uint32_t);
  uint8_t    (*Config)(uint16_t, uint32_t, IO_ModeTypedef);
  void       (*WritePin)(uint16_t, uint32_t, uint8_t);
  uint32_t   (*ReadPin)(uint16_t, uint32_t);
  
  void       (*EnableIT)(uint16_t);
  void       (*DisableIT)(uint16_t);
  uint32_t    (*ITStatus)(uint16_t, uint32_t);
  void       (*ClearIT)(uint16_t, uint32_t);
    
}IO_DrvTypeDef;
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

/**
  * @}
  */

#ifdef __cplusplus
}
#endif

#endif /* __IO_H */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
