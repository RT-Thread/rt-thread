/**
  ******************************************************************************
  * @file    stm32f7xx_hal_sai_ex.c
  * @author  MCD Application Team
  * @version V1.0.1
  * @date    25-June-2015
  * @brief   SAI Extension HAL module driver.
  *          This file provides firmware functions to manage the following 
  *          functionalities of SAI extension peripheral:
  *           + Extension features functions
  *         
  @verbatim
  ==============================================================================
               ##### SAI peripheral extension features  #####
  ==============================================================================
   
                     ##### How to use this driver #####
  ==============================================================================
  [..] This driver provides functions to manage several sources to clock SAI
  
  @endverbatim
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

/* Includes ------------------------------------------------------------------*/
#include "stm32f7xx_hal.h"

/** @addtogroup STM32F7xx_HAL_Driver
  * @{
  */

/** @defgroup SAIEx SAIEx
  * @brief SAI Extension HAL module driver
  * @{
  */

#ifdef HAL_SAI_MODULE_ENABLED

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* SAI registers Masks */
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/

/** @defgroup SAI_Private_Functions  SAI Private Functions
  * @{
  */
 /**
  * @}
  */
  
/* Exported functions --------------------------------------------------------*/
/** @defgroup SAIEx_Exported_Functions SAI Extended Exported Functions
  * @{
  */

/** @defgroup SAIEx_Exported_Functions_Group1 Extension features functions 
  *  @brief   Extension features functions
  *
@verbatim    
 ===============================================================================
                       ##### Extension features Functions #####
 ===============================================================================  
    [..]
    This subsection provides a set of functions allowing to manage the possible 
    SAI clock sources.

@endverbatim
  * @{
  */

/**
  * @brief  Configure SAI Block synchronization mode
  * @param  hsai: pointer to a SAI_HandleTypeDef structure that contains
  *               the configuration information for SAI module.   
  * @retval SAI Clock Input 
  */
void SAI_BlockSynchroConfig(SAI_HandleTypeDef *hsai)
{
  uint32_t tmpregisterGCR = 0;
 
  /* This setting must be done with both audio block (A & B) disabled     */
  switch(hsai->Init.SynchroExt)
  {
  case SAI_SYNCEXT_DISABLE :
    tmpregisterGCR = 0;
    break;
  case SAI_SYNCEXT_IN_ENABLE :
    tmpregisterGCR = SAI_GCR_SYNCIN_0;
    break;
  case SAI_SYNCEXT_OUTBLOCKA_ENABLE :
    tmpregisterGCR = SAI_GCR_SYNCOUT_0;
    break;
  case SAI_SYNCEXT_OUTBLOCKB_ENABLE :
    tmpregisterGCR = SAI_GCR_SYNCOUT_1;
    break;
  default :
    break;
  }
  
  if((hsai->Instance == SAI1_Block_A) || (hsai->Instance == SAI1_Block_B))
  {
    SAI1->GCR = tmpregisterGCR;
  }
  else 
  {
    SAI2->GCR = tmpregisterGCR;
  }
}
  /**
  * @brief  Get SAI Input Clock based on SAI source clock selection
  * @param  hsai: pointer to a SAI_HandleTypeDef structure that contains
  *               the configuration information for SAI module.   
  * @retval SAI Clock Input 
  */
uint32_t SAI_GetInputClock(SAI_HandleTypeDef *hsai)   
{
  /* This variable used to store the SAI_CK_x (value in Hz) */
  uint32_t saiclocksource = 0;

  if ((hsai->Instance == SAI1_Block_A) || (hsai->Instance == SAI1_Block_B))
  {
    saiclocksource = HAL_RCCEx_GetPeriphCLKFreq(RCC_PERIPHCLK_SAI1);
  }
  else /* SAI2_Block_A || SAI2_Block_B*/
  {
    saiclocksource = HAL_RCCEx_GetPeriphCLKFreq(RCC_PERIPHCLK_SAI2); 
  }
  /* the return result is the value of SAI clock */
  return saiclocksource;        
}

/**
  * @}
  */

/**
  * @}
  */

#endif /* HAL_SAI_MODULE_ENABLED */
/**
  * @}
  */

/**
  * @}
  */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
