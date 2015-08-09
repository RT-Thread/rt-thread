/**
  ******************************************************************************
  * @file    stm32f7xx_hal_dcmi_ex.c
  * @author  MCD Application Team
  * @version V1.0.1
  * @date    25-June-2015
  * @brief   DCMI Extension HAL module driver.
  *          This file provides firmware functions to manage the following 
  *          functionalities of DCMI extension peripheral:
  *           + Extension features functions 
  *           
  @verbatim      
  ==============================================================================
               ##### DCMI peripheral extension features  #####
  ==============================================================================
           
  [..]  Support of Black and White cameras 
   
                     ##### How to use this driver #####
  ==============================================================================
  [..] This driver provides functions to manage the Black and White feature
    
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
/** @defgroup DCMIEx DCMIEx
  * @brief DCMI Extended HAL module driver
  * @{
  */

#ifdef HAL_DCMI_MODULE_ENABLED

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
/* Exported functions --------------------------------------------------------*/

/** @defgroup DCMIEx_Exported_Functions DCMIEx Exported Functions
  * @{
  */

/** @defgroup DCMIEx_Exported_Functions_Group1 Initialization and Configuration functions
 *  @brief   Initialization and Configuration functions
 *
@verbatim   
 ===============================================================================
                ##### Initialization and Configuration functions #####
 ===============================================================================  
    [..]  This section provides functions allowing to:
      (+) Initialize and configure the DCMI
      (+) De-initialize the DCMI 

@endverbatim
  * @{
  */
  
/**
  * @brief  Initializes the DCMI according to the specified
  *         parameters in the DCMI_InitTypeDef and create the associated handle.
  * @param  hdcmi: pointer to a DCMI_HandleTypeDef structure that contains
  *                the configuration information for DCMI.
  * @retval HAL status
  */
HAL_StatusTypeDef HAL_DCMI_Init(DCMI_HandleTypeDef *hdcmi)
{     
  /* Check the DCMI peripheral state */
  if(hdcmi == NULL)
  {
     return HAL_ERROR;
  }
  
  /* Check function parameters */
  assert_param(IS_DCMI_ALL_INSTANCE(hdcmi->Instance));
  assert_param(IS_DCMI_PCKPOLARITY(hdcmi->Init.PCKPolarity));
  assert_param(IS_DCMI_VSPOLARITY(hdcmi->Init.VSPolarity));
  assert_param(IS_DCMI_HSPOLARITY(hdcmi->Init.HSPolarity));
  assert_param(IS_DCMI_SYNCHRO(hdcmi->Init.SynchroMode));
  assert_param(IS_DCMI_CAPTURE_RATE(hdcmi->Init.CaptureRate));
  assert_param(IS_DCMI_EXTENDED_DATA(hdcmi->Init.ExtendedDataMode));
  assert_param(IS_DCMI_MODE_JPEG(hdcmi->Init.JPEGMode));

  assert_param(IS_DCMI_BYTE_SELECT_MODE(hdcmi->Init.ByteSelectMode));
  assert_param(IS_DCMI_BYTE_SELECT_START(hdcmi->Init.ByteSelectStart));
  assert_param(IS_DCMI_LINE_SELECT_MODE(hdcmi->Init.LineSelectMode));
  assert_param(IS_DCMI_LINE_SELECT_START(hdcmi->Init.LineSelectStart));
                
  if(hdcmi->State == HAL_DCMI_STATE_RESET)
  {
    /* Init the low level hardware */
    HAL_DCMI_MspInit(hdcmi);
  } 
  
  /* Change the DCMI state */
  hdcmi->State = HAL_DCMI_STATE_BUSY; 
                          /* Configures the HS, VS, DE and PC polarity */
  hdcmi->Instance->CR &= ~(DCMI_CR_PCKPOL | DCMI_CR_HSPOL  | DCMI_CR_VSPOL  | DCMI_CR_EDM_0 |\
                           DCMI_CR_EDM_1  | DCMI_CR_FCRC_0 | DCMI_CR_FCRC_1 | DCMI_CR_JPEG  |\
                           DCMI_CR_ESS | DCMI_CR_BSM_0 | DCMI_CR_BSM_1 | DCMI_CR_OEBS |\
                           DCMI_CR_LSM | DCMI_CR_OELS);

  hdcmi->Instance->CR |=  (uint32_t)(hdcmi->Init.SynchroMode | hdcmi->Init.CaptureRate |\
                                     hdcmi->Init.VSPolarity  | hdcmi->Init.HSPolarity  |\
                                     hdcmi->Init.PCKPolarity | hdcmi->Init.ExtendedDataMode |\
                                     hdcmi->Init.JPEGMode | hdcmi->Init.ByteSelectMode |\
                                     hdcmi->Init.ByteSelectStart | hdcmi->Init.LineSelectMode |\
                                     hdcmi->Init.LineSelectStart);
                                     
  if(hdcmi->Init.SynchroMode == DCMI_SYNCHRO_EMBEDDED)
  {
    DCMI->ESCR = (((uint32_t)hdcmi->Init.SyncroCode.FrameStartCode)    |
                  ((uint32_t)hdcmi->Init.SyncroCode.LineStartCode << 8)|
                  ((uint32_t)hdcmi->Init.SyncroCode.LineEndCode << 16) |
                  ((uint32_t)hdcmi->Init.SyncroCode.FrameEndCode << 24));

  }

  /* Enable the Line interrupt */
  __HAL_DCMI_ENABLE_IT(hdcmi, DCMI_IT_LINE);

  /* Enable the VSYNC interrupt */
  __HAL_DCMI_ENABLE_IT(hdcmi, DCMI_IT_VSYNC);

  /* Enable the Frame capture complete interrupt */
  __HAL_DCMI_ENABLE_IT(hdcmi, DCMI_IT_FRAME);

  /* Enable the Synchronization error interrupt */
  __HAL_DCMI_ENABLE_IT(hdcmi, DCMI_IT_ERR);

  /* Enable the Overflow interrupt */
  __HAL_DCMI_ENABLE_IT(hdcmi, DCMI_IT_OVF);

  /* Enable DCMI by setting DCMIEN bit */
  __HAL_DCMI_ENABLE(hdcmi);

  /* Update error code */
  hdcmi->ErrorCode = HAL_DCMI_ERROR_NONE;
  
  /* Initialize the DCMI state*/
  hdcmi->State  = HAL_DCMI_STATE_READY;

  return HAL_OK;
}


/**
  * @}
  */

/**
  * @}
  */
  
/**
  * @}
  */
#endif /* HAL_DCMI_MODULE_ENABLED */
/**
  * @}
  */

/**
  * @}
  */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
