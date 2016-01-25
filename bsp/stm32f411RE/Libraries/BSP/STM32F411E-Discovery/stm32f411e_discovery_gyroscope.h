/**
  ******************************************************************************
  * @file    stm32f411e_discovery_gyroscope.h
  * @author  MCD Application Team
  * @version V1.0.0
  * @date    12-November-2015
  * @brief   This file contains definitions for stm32f411e_discovery_gyroscope.c 
  *          firmware driver.
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
#ifndef __STM32F411E_DISCOVERY_GYROSCOPE_H
#define __STM32F411E_DISCOVERY_GYROSCOPE_H

#ifdef __cplusplus
 extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "stm32f411e_discovery.h"

 /* Include Gyroscope component driver */
#include "../Components/l3gd20/l3gd20.h"   

/** @addtogroup BSP
  * @{
  */
  
/** @addtogroup STM32F411E_DISCOVERY
  * @{
  */ 

/** @addtogroup STM32F411E_DISCOVERY_GYROSCOPE
  * @{
  */
  
/** @defgroup STM32F411E_DISCOVERY_GYROSCOPE_Exported_Types
  * @{
  */
typedef enum 
{
  GYRO_OK = 0,
  GYRO_ERROR = 1,
  GYRO_TIMEOUT = 2
}GYRO_StatusTypeDef;
/**
  * @}
  */
  
/** @defgroup STM32F411E_DISCOVERY_GYROSCOPE_Exported_Constants
  * @{
  */
/**
  * @}
  */
  
/** @defgroup STM32F411E_DISCOVERY_GYROSCOPE_Exported_Macros
  * @{
  */
/**
  * @}
  */
 
/** @defgroup STM32F411E_DISCOVERY_GYROSCOPE_Exported_Functions
  * @{
  */
/* Gyroscope Functions */ 
uint8_t BSP_GYRO_Init(void);
void    BSP_GYRO_Reset(void);
uint8_t BSP_GYRO_ReadID(void);
void    BSP_GYRO_ITConfig(GYRO_InterruptConfigTypeDef *pIntConfigStruct);
void    BSP_GYRO_EnableIT(uint8_t IntPin);
void    BSP_GYRO_DisableIT(uint8_t IntPin);
void    BSP_GYRO_GetXYZ(float *pfData);

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
  
#endif /* __STM32F411E_DISCOVERY_GYROSCOPE_H */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/ 
