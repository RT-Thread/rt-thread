/**
  ******************************************************************************
  * @file    stm32446e_eval_eeprom.h
  * @author  MCD Application Team
  * @version V1.1.0
  * @date    14-August-2015
  * @brief   This file contains all the functions prototypes for 
  *          the stm32446e_eval_eeprom.c firmware driver.
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
#ifndef __STM32F446E_EVAL_EEPROM_H
#define __STM32F446E_EVAL_EEPROM_H

#ifdef __cplusplus
 extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "stm32446e_eval.h"

/** @addtogroup BSP
  * @{
  */
  
/** @addtogroup STM32446E_EVAL
  * @{
  */ 
  
/** @defgroup STM32446E_EVAL_EEPROM STM32446E-EVAL EEPROM
  * @brief This file includes the I2C EEPROM driver of STM32446E-EVAL evaluation board.
  * @{
  */

/** @defgroup STM32446E_EVAL_EEPROM_Exported_Types STM32446E EVAL EEPROM Exported Types
  * @{
  */ 
/**
  * @}
  */
  
/** @defgroup STM32446E_EVAL_EEPROM_Exported_Constants STM32446E EVAL EEPROM Exported Constants
  * @{
  */
/* EEPROM hardware address and page size */ 
#define EEPROM_PAGESIZE             ((uint8_t)4)
#define EEPROM_MAX_SIZE             ((uint16_t)0x2000) /* 64Kbit */
                                

/* Maximum number of trials for EEPROM_WaitEepromStandbyState() function */
#define EEPROM_MAX_TRIALS           ((uint32_t)3000)
      
#define EEPROM_OK                   ((uint32_t)0)
#define EEPROM_FAIL                 ((uint32_t)1)
#define EEPROM_TIMEOUT              ((uint32_t)2)
/**
  * @}
  */ 
  
/** @defgroup STM32446E_EVAL_EEPROM_Exported_Macros STM32446E EVAL EEPROM Exported Macros
  * @{
  */    
/**
  * @}
  */ 

/** @defgroup STM32446E_EVAL_EEPROM_Exported_Functions STM32446E EVAL EEPROM Exported Functions
  * @{
  */ 
uint32_t BSP_EEPROM_Init(void);
uint8_t BSP_EEPROM_DeInit(void);
uint32_t BSP_EEPROM_ReadBuffer(uint8_t* pBuffer, uint16_t ReadAddr, uint16_t* NumByteToRead);
uint32_t BSP_EEPROM_WritePage(uint8_t* pBuffer, uint16_t WriteAddr, uint8_t* NumByteToWrite);
uint32_t BSP_EEPROM_WriteBuffer(uint8_t* pBuffer, uint16_t WriteAddr, uint16_t NumByteToWrite);
uint32_t BSP_EEPROM_WaitEepromStandbyState(void);

/* USER Callbacks: This function is declared as __weak in EEPROM driver and 
   should be implemented into user application.  
   BSP_EEPROM_TIMEOUT_UserCallback() function is called whenever a timeout condition 
   occurs during communication (waiting on an event that doesn't occur, bus
   errors, busy devices ...). */
void     BSP_EEPROM_TIMEOUT_UserCallback(void);

/* Link function for I2C EEPROM peripheral */
void              EEPROM_IO_Init(void);
HAL_StatusTypeDef EEPROM_IO_WriteData(uint16_t DevAddress, uint16_t MemAddress, uint8_t *pBuffer, uint32_t BufferSize);
HAL_StatusTypeDef EEPROM_IO_ReadData(uint16_t DevAddress, uint16_t MemAddress, uint8_t *pBuffer, uint32_t BufferSize);
HAL_StatusTypeDef EEPROM_IO_IsDeviceReady(uint16_t DevAddress, uint32_t Trials);

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

#endif /* __STM32446E_EVAL_EEPROM_H */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
