/**
  ******************************************************************************
  * @file    stm324x9i_eval_nor.h
  * @author  MCD Application Team
  * @version V2.2.1
  * @date    07-October-2015
  * @brief   This file contains the common defines and functions prototypes for
  *          the stm324x9i_eval_nor.c driver.
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
#ifndef __STM324x9I_EVAL_NOR_H
#define __STM324x9I_EVAL_NOR_H

#ifdef __cplusplus
 extern "C" {
#endif 

/* Includes ------------------------------------------------------------------*/
#include "stm32f4xx_hal.h"

/** @addtogroup BSP
  * @{
  */ 

/** @addtogroup STM324x9I_EVAL
  * @{
  */
    
/** @defgroup STM324x9I_EVAL_NOR
  * @{
  */    

/** @defgroup STM324x9I_EVAL_NOR_Exported_Types
  * @{
  */
/**
  * @}
  */ 
    
/** 
  * @brief  NOR status structure definition  
  */     
#define   NOR_STATUS_OK         0x00
#define   NOR_STATUS_ERROR      0x01

/** @defgroup STM324x9I_EVAL_NOR_Exported_Constants
  * @{
  */  
#define NOR_DEVICE_ADDR  ((uint32_t)0x60000000)  
  
/* #define NOR_MEMORY_WIDTH    FMC_NORSRAM_MEM_BUS_WIDTH_8  */
#define NOR_MEMORY_WIDTH    FMC_NORSRAM_MEM_BUS_WIDTH_16

#define NOR_BURSTACCESS    FMC_BURST_ACCESS_MODE_DISABLE  
/* #define NOR_BURSTACCESS    FMC_BURST_ACCESS_MODE_ENABLE*/
  
#define NOR_WRITEBURST    FMC_WRITE_BURST_DISABLE  
/* #define NOR_WRITEBURST   FMC_WRITE_BURST_ENABLE */
 
#define CONTINUOUSCLOCK_FEATURE    FMC_CONTINUOUS_CLOCK_SYNC_ONLY 
/* #define CONTINUOUSCLOCK_FEATURE     FMC_CONTINUOUS_CLOCK_SYNC_ASYNC */ 

/* NOR operations Timeout definitions */
#define BLOCKERASE_TIMEOUT   ((uint32_t)0x00A00000)  /* NOR block erase timeout */
#define CHIPERASE_TIMEOUT    ((uint32_t)0x30000000)  /* NOR chip erase timeout  */ 
#define PROGRAM_TIMEOUT      ((uint32_t)0x00004400)  /* NOR program timeout     */ 

/* NOR Ready/Busy signal GPIO definitions */
#define NOR_READY_BUSY_PIN    GPIO_PIN_6 
#define NOR_READY_BUSY_GPIO   GPIOD
#define NOR_READY_STATE       GPIO_PIN_SET
#define NOR_BUSY_STATE        GPIO_PIN_RESET 
/**
  * @}
  */ 
    
/** @defgroup STM324x9I_EVAL_NOR_Exported_Macro
  * @{
  */ 
/**
  * @}
  */ 
    
/** @defgroup STM324x9I_EVAL_NOR_Exported_Functions
  * @{
  */  
uint8_t BSP_NOR_Init(void);
uint8_t BSP_NOR_ReadData(uint32_t uwStartAddress, uint16_t *pData, uint32_t uwDataSize);
uint8_t BSP_NOR_WriteData(uint32_t uwStartAddress, uint16_t *pData, uint32_t uwDataSize);
uint8_t BSP_NOR_ProgramData(uint32_t uwStartAddress, uint16_t *pData, uint32_t uwDataSize);
uint8_t BSP_NOR_Erase_Block(uint32_t BlockAddress);
uint8_t BSP_NOR_Erase_Chip(void);
uint8_t BSP_NOR_Read_ID(NOR_IDTypeDef *pNOR_ID);
void BSP_NOR_ReturnToReadMode(void);  

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

#endif /* __STM324x9I_EVAL_NOR_H */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
