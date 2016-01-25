/**
  ******************************************************************************
  * @file    exc7200.h
  * @author  MCD Application Team
  * @version V1.0.1
  * @date    21-September-2015
  * @brief   This file contains all the functions prototypes for the
  *          exc7200.c IO expander driver.
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
#ifndef __EXC7200_H
#define __EXC7200_H

#ifdef __cplusplus
 extern "C" {
#endif   
   
/* Includes ------------------------------------------------------------------*/
#include "../Common/ts.h"

/** @addtogroup BSP
  * @{
  */ 

/** @addtogroup Component
  * @{
  */
    
/** @defgroup EXC7200
  * @{
  */    

/* Exported types ------------------------------------------------------------*/

/** @defgroup EXC7200_Exported_Types
  * @{
  */ 

/* Exported constants --------------------------------------------------------*/
  
/** @defgroup EXC7200_Exported_Constants
  * @{
  */ 

/*  */   
#define EXC7200_READ_CMD                             0x09  

/**
  * @}
  */ 
  
/* Exported macro ------------------------------------------------------------*/
   
/** @defgroup exc7200_Exported_Macros
  * @{
  */ 

/* Exported functions --------------------------------------------------------*/
  
/** @defgroup exc7200_Exported_Functions
  * @{
  */

/** 
  * @brief exc7200 Control functions
  */
void     exc7200_Init(uint16_t DeviceAddr);
void     exc7200_Reset(uint16_t DeviceAddr);
uint16_t exc7200_ReadID(uint16_t DeviceAddr);
void     exc7200_TS_Start(uint16_t DeviceAddr);
uint8_t  exc7200_TS_DetectTouch(uint16_t DeviceAddr);
void     exc7200_TS_GetXY(uint16_t DeviceAddr, uint16_t *X, uint16_t *Y);
void     exc7200_TS_EnableIT(uint16_t DeviceAddr);
void     exc7200_TS_DisableIT(uint16_t DeviceAddr);
uint8_t  exc7200_TS_ITStatus (uint16_t DeviceAddr);
void     exc7200_TS_ClearIT (uint16_t DeviceAddr);

void     IOE_Init(void);
void     IOE_Delay(uint32_t delay);
uint8_t  IOE_Read(uint8_t addr, uint8_t reg);
uint16_t IOE_ReadMultiple(uint8_t addr, uint8_t reg, uint8_t *buffer, uint16_t length);
void     IOE_WriteMultiple(uint8_t addr, uint8_t reg, uint8_t *buffer, uint16_t length);

/* Touch screen driver structure */
extern TS_DrvTypeDef exc7200_ts_drv;

#ifdef __cplusplus
}
#endif
#endif /* __EXC7200_H */


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
/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
