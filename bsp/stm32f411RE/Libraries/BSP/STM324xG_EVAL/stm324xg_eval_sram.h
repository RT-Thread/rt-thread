/**
  ******************************************************************************
  * @file    stm324xg_eval_sram.h
  * @author  MCD Application Team
  * @version V2.1.0
  * @date    14-August-2015
  * @brief   This file contains the common defines and functions prototypes for
  *          the stm324xg_eval_sram.c driver.
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
#ifndef __STM324xG_EVAL_SRAM_H
#define __STM324xG_EVAL_SRAM_H

#ifdef __cplusplus
 extern "C" {
#endif 

/* Includes ------------------------------------------------------------------*/
#include "stm32f4xx_hal.h"

/** @addtogroup BSP
  * @{
  */ 

/** @addtogroup STM324xG_EVAL
  * @{
  */
    
/** @defgroup STM324xG_EVAL_SRAM
  * @{
  */    

/** @defgroup STM324xG_EVAL_SRAM_Exported_Types
  * @{
  */
/**
  * @}
  */ 
   
/** @defgroup STM324xG_EVAL_SRAM_Exported_Constants
  * @{
  */
   
/** 
  * @brief  SD status structure definition  
  */     
#define SRAM_OK         0x00
#define SRAM_ERROR      0x01
   
#define SRAM_DEVICE_ADDR  ((uint32_t)0x64000000)
#define SRAM_DEVICE_SIZE  ((uint32_t)0x200000)  /* SRAM device size in MBytes */  
  
/* #define SRAM_MEMORY_WIDTH    FSMC_NORSRAM_MEM_BUS_WIDTH_8 */
#define SRAM_MEMORY_WIDTH    FSMC_NORSRAM_MEM_BUS_WIDTH_16

#define SRAM_BURSTACCESS    FSMC_BURST_ACCESS_MODE_DISABLE  
/* #define SRAM_BURSTACCESS    FSMC_BURST_ACCESS_MODE_ENABLE */
  
#define SRAM_WRITEBURST    FSMC_WRITE_BURST_DISABLE  
/* #define SRAM_WRITEBURST   FSMC_WRITE_BURST_ENABLE */

/* DMA definitions for SRAM DMA transfer */
#define __SRAM_DMAx_CLK_ENABLE            __DMA2_CLK_ENABLE
#define SRAM_DMAx_CHANNEL                 DMA_CHANNEL_0
#define SRAM_DMAx_STREAM                  DMA2_Stream0  
#define SRAM_DMAx_IRQn                    DMA2_Stream0_IRQn
#define SRAM_DMAx_IRQHandler              DMA2_Stream0_IRQHandler
/**
  * @}
  */ 
  
/** @defgroup STM324xG_EVAL_SRAM_Exported_Macro
  * @{
  */  
/**
  * @}
  */ 

/** @defgroup STM324xG_EVAL_SRAM_Exported_Functions
  * @{
  */     
uint8_t BSP_SRAM_Init(void);
uint8_t BSP_SRAM_ReadData(uint32_t uwStartAddress, uint16_t *pData, uint32_t uwDataSize);
uint8_t BSP_SRAM_ReadData_DMA(uint32_t uwStartAddress, uint16_t *pData, uint32_t uwDataSize);
uint8_t BSP_SRAM_WriteData(uint32_t uwStartAddress, uint16_t *pData, uint32_t uwDataSize);
uint8_t BSP_SRAM_WriteData_DMA(uint32_t uwStartAddress, uint16_t *pData, uint32_t uwDataSize);
void    BSP_SRAM_DMA_IRQHandler(void);

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

#endif /* __STM324xG_EVAL_SRAM_H */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
