/**
  ******************************************************************************
  * @file    stm32f4xx_hal_fmpi2c_ex.h
  * @author  MCD Application Team
  * @version V1.4.3
  * @date    11-December-2015
  * @brief   Header file of FMPI2C HAL Extension module.
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
#ifndef __STM32F4xx_HAL_FMPI2C_EX_H
#define __STM32F4xx_HAL_FMPI2C_EX_H

#ifdef __cplusplus
 extern "C" {
#endif

#if defined(STM32F410Tx) || defined(STM32F410Cx) || defined(STM32F410Rx) || defined(STM32F446xx)  
   
/* Includes ------------------------------------------------------------------*/
#include "stm32f4xx_hal_def.h"  

/** @addtogroup STM32F4xx_HAL_Driver
  * @{
  */

/** @addtogroup FMPI2CEx
  * @{
  */ 

/* Exported types ------------------------------------------------------------*/ 
/* Exported constants --------------------------------------------------------*/
/** @defgroup FMPI2CEx_Exported_Constants FMPI2C Exported Constants
  * @{
  */

/** @defgroup FMPI2CEx_Analog_Filter FMPI2C Analog Filter
  * @{
  */
#define FMPI2C_ANALOGFILTER_ENABLE        ((uint32_t)0x00000000)
#define FMPI2C_ANALOGFILTER_DISABLE       FMPI2C_CR1_ANFOFF
/**
  * @}
  */

/** @defgroup FMPI2CEx_FastModePlus FMPI2C Fast Mode Plus
  * @{
  */
#define FMPI2C_FASTMODEPLUS_SCL            SYSCFG_CFGR_FMPI2C1_SCL  /*!< Enable Fast Mode Plus on FMPI2C1 SCL pins       */
#define FMPI2C_FASTMODEPLUS_SDA            SYSCFG_CFGR_FMPI2C1_SDA  /*!< Enable Fast Mode Plus on FMPI2C1 SDA pins       */
/**
  * @}
  */
  
/**
  * @}
  */ 
  
/* Exported macro ------------------------------------------------------------*/
/* Exported functions --------------------------------------------------------*/
/** @addtogroup FMPI2CEx_Exported_Functions
  * @{
  */

/** @addtogroup FMPI2CEx_Exported_Functions_Group1
  * @{
  */
/* Peripheral Control functions ************************************************/
HAL_StatusTypeDef HAL_FMPI2CEx_AnalogFilter_Config(FMPI2C_HandleTypeDef *hFMPI2C, uint32_t AnalogFilter);
HAL_StatusTypeDef HAL_FMPI2CEx_DigitalFilter_Config(FMPI2C_HandleTypeDef *hFMPI2C, uint32_t DigitalFilter);
HAL_StatusTypeDef HAL_FMPI2CEx_EnableWakeUp (FMPI2C_HandleTypeDef *hFMPI2C);
HAL_StatusTypeDef HAL_FMPI2CEx_DisableWakeUp (FMPI2C_HandleTypeDef *hFMPI2C);
void HAL_FMPI2CEx_EnableFastModePlus(uint32_t ConfigFastModePlus);
void HAL_FMPI2CEx_DisableFastModePlus(uint32_t ConfigFastModePlus);
/**
  * @}
  */

/**
  * @}
  */ 
/* Private types -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private constants ---------------------------------------------------------*/
/** @defgroup I2CEx_Private_Constants I2C Private Constants
  * @{
  */

/**
  * @}
  */

/* Private macros ------------------------------------------------------------*/
/** @defgroup I2CEx_Private_Macros I2C Private Macros
  * @{
  */
#define IS_FMPI2C_ANALOG_FILTER(FILTER) (((FILTER) == FMPI2C_ANALOGFILTER_ENABLE) || \
                                         ((FILTER) == FMPI2C_ANALOGFILTER_DISABLE))

#define IS_FMPI2C_DIGITAL_FILTER(FILTER)   ((FILTER) <= 0x0000000F)

#define IS_FMPI2C_FASTMODEPLUS(__CONFIG__) ((((__CONFIG__) & (FMPI2C_FASTMODEPLUS_SCL)) == FMPI2C_FASTMODEPLUS_SCL) || \
                                          (((__CONFIG__) & (FMPI2C_FASTMODEPLUS_SDA)) == FMPI2C_FASTMODEPLUS_SDA))
/**
  * @}
  */

/**
  * @}
  */ 

/**
  * @}
  */
#endif /* STM32F410xx || STM32F446xx */  
#ifdef __cplusplus
}
#endif

#endif /* __STM32F4xx_HAL_FMPI2C_EX_H */


/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
