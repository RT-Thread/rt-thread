/**
  ******************************************************************************
  * @file    stm32f429i_discovery_eeprom.h
  * @author  MCD Application Team
  * @version V2.1.2
  * @date    02-March-2015
  * @brief   This file contains all the functions prototypes for 
  *          the stm32f429i_discovery_eeprom.c firmware driver.
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
#ifndef __STM32F429I_DISCOVERY_EEPROM_H
#define __STM32F429I_DISCOVERY_EEPROM_H

#ifdef __cplusplus
 extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "stm32f429i_discovery.h"

/** @addtogroup BSP
  * @{
  */

/** @addtogroup STM32F429I_DISCOVERY
  * @{
  */
  
/** @addtogroup STM32F429I_DISCOVERY_EEPROM
  * @{
  */  

/** @defgroup STM32F429I_DISCOVERY_EEPROM_Exported_Types
  * @{
  */ 
/**
  * @}
  */
  
/** @defgroup STM32F429I_DISCOVERY_EEPROM_Exported_Constants
  * @{
  */
/* EEPROM hardware address and page size */ 
#define EEPROM_PAGESIZE             4
#define EEPROM_MAX_SIZE             0x2000 /* 64Kbit*/
                                
/* Maximum Timeout values for flags and events waiting loops. 
This timeout is based on systick set to 1ms*/   
/* Timeout for read based if read all the EEPROM : EEPROM_MAX_SIZE * BSP_I2C_SPEED (640ms)*/
#define EEPROM_READ_TIMEOUT         ((uint32_t)(1000))
/* Timeout for write based on max write which is EEPROM_PAGESIZE bytes: EEPROM_PAGESIZE * BSP_I2C_SPEED (320us)*/
#define EEPROM_WRITE_TIMEOUT         ((uint32_t)(1))

/* Maximum number of trials for EEPROM_WaitEepromStandbyState() function */
#define EEPROM_MAX_TRIALS           300
      
#define EEPROM_OK                   0
#define EEPROM_FAIL                 1
#define EEPROM_TIMEOUT              2
/**
  * @}
  */ 
  
/** @defgroup STM32F429I_DISCOVERY_EEPROM_Exported_Macros
  * @{
  */    
/**
  * @}
  */ 

/** @defgroup STM32F429I_DISCOVERY_EEPROM_Exported_Functions
  * @{
  */ 
uint32_t BSP_EEPROM_Init(void);
uint32_t BSP_EEPROM_ReadBuffer(uint8_t *pBuffer, uint16_t ReadAddr, uint16_t *NumByteToRead);
uint32_t BSP_EEPROM_WritePage(uint8_t *pBuffer, uint16_t WriteAddr, uint8_t *NumByteToWrite);
uint32_t BSP_EEPROM_WriteBuffer(uint8_t *pBuffer, uint16_t WriteAddr, uint16_t NumByteToWrite);
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

#ifdef __cplusplus
}
#endif

#endif /* __STM32F429I_DISCOVERY_EEPROM_H */

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
