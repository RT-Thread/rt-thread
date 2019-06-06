/**
  ******************************************************************************
  * @file    stm32f7xx_hal_smartcard_ex.c
  * @author  MCD Application Team
  * @brief   SMARTCARD HAL module driver.
<<<<<<< HEAD
  *
  *          This file provides extended firmware functions to manage the following 
  *          functionalities of the SmartCard.
  *           + Initialization and de-initialization functions
  *           + Peripheral Control functions
  @verbatim
 ===============================================================================
                        ##### How to use this driver #####
 ===============================================================================
    [..]
    The Extended SMARTCARD HAL driver can be used as follow:

    (#) After having configured the SMARTCARD basic features with HAL_SMARTCARD_Init(), 
        then if required, program SMARTCARD advanced features (TX/RX pins swap, TimeOut, 
        auto-retry counter,...) in the hsc AdvancedInit structure.

=======
  *          This file provides extended firmware functions to manage the following
  *          functionalities of the SmartCard.
  *           + Initialization and de-initialization functions
  *           + Peripheral Control functions
  *
  @verbatim
  =============================================================================
               ##### SMARTCARD peripheral extended features  #####
  =============================================================================
  [..]
  The Extended SMARTCARD HAL driver can be used as follows:

    (#) After having configured the SMARTCARD basic features with HAL_SMARTCARD_Init(),
        then program SMARTCARD advanced features if required (TX/RX pins swap, TimeOut,
        auto-retry counter,...) in the hsmartcard AdvancedInit structure.
>>>>>>> 49e424905b5922b07aa7166ec7a0eeb90adf58a8
  @endverbatim
  ******************************************************************************
  * @attention
  *
<<<<<<< HEAD
  * <h2><center>&copy; COPYRIGHT(c) 2017 STMicroelectronics</center></h2>
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
=======
  * <h2><center>&copy; Copyright (c) 2017 STMicroelectronics.
  * All rights reserved.</center></h2>
  *
  * This software component is licensed by ST under BSD 3-Clause license,
  * the "License"; You may not use this file except in compliance with the
  * License. You may obtain a copy of the License at:
  *                        opensource.org/licenses/BSD-3-Clause
>>>>>>> 49e424905b5922b07aa7166ec7a0eeb90adf58a8
  *
  ******************************************************************************
  */

/* Includes ------------------------------------------------------------------*/
#include "stm32f7xx_hal.h"

/** @addtogroup STM32F7xx_HAL_Driver
  * @{
  */

/** @defgroup SMARTCARDEx SMARTCARDEx
  * @brief SMARTCARD Extended HAL module driver
  * @{
  */
#ifdef HAL_SMARTCARD_MODULE_ENABLED
<<<<<<< HEAD
    
/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/

/** @defgroup SMARTCARDEx_Exported_Functions SMARTCARDEx Exported Functions
  * @{
  */

/** @defgroup SMARTCARDEx_Group1 Extended Peripheral Control functions
  * @brief    Extended control functions
  *
@verbatim   
 ===============================================================================
                      ##### Peripheral Control functions #####
 ===============================================================================
    [..]
    This subsection provides a set of functions allowing to initialize the SMARTCARD.
     (+) HAL_SMARTCARDEx_BlockLength_Config() API allows to configure the Block Length on the fly 
     (+) HAL_SMARTCARDEx_TimeOut_Config() API allows to configure the receiver timeout value on the fly  
=======

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macros ------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
/* Exported functions --------------------------------------------------------*/
/** @defgroup SMARTCARDEx_Exported_Functions  SMARTCARD Extended Exported Functions
  * @{
  */

/** @defgroup SMARTCARDEx_Exported_Functions_Group1 Extended Peripheral Control functions
  * @brief    Extended control functions
  *
@verbatim
  ===============================================================================
                      ##### Peripheral Control functions #####
  ===============================================================================
  [..]
  This subsection provides a set of functions allowing to initialize the SMARTCARD.
     (+) HAL_SMARTCARDEx_BlockLength_Config() API allows to configure the Block Length on the fly
     (+) HAL_SMARTCARDEx_TimeOut_Config() API allows to configure the receiver timeout value on the fly
>>>>>>> 49e424905b5922b07aa7166ec7a0eeb90adf58a8
     (+) HAL_SMARTCARDEx_EnableReceiverTimeOut() API enables the receiver timeout feature
     (+) HAL_SMARTCARDEx_DisableReceiverTimeOut() API disables the receiver timeout feature

@endverbatim
  * @{
  */

<<<<<<< HEAD
/**
  * @brief Update on the fly the SMARTCARD block length in RTOR register
  * @param hsc SMARTCARD handle
  * @param BlockLength SMARTCARD block length (8-bit long at most)  
  * @retval None
  */
void HAL_SMARTCARDEx_BlockLength_Config(SMARTCARD_HandleTypeDef *hsc, uint8_t BlockLength)
{
  MODIFY_REG(hsc->Instance->RTOR, USART_RTOR_BLEN, ((uint32_t)BlockLength << SMARTCARD_RTOR_BLEN_LSB_POS));
}

/**
  * @brief Update on the fly the receiver timeout value in RTOR register
  * @param hsc SMARTCARD handle
  * @param TimeOutValue receiver timeout value in number of baud blocks. The timeout
  *                     value must be less or equal to 0x0FFFFFFFF. 
  * @retval None
  */
void HAL_SMARTCARDEx_TimeOut_Config(SMARTCARD_HandleTypeDef *hsc, uint32_t TimeOutValue)
{
  assert_param(IS_SMARTCARD_TIMEOUT_VALUE(hsc->Init.TimeOutValue));
  MODIFY_REG(hsc->Instance->RTOR, USART_RTOR_RTO, TimeOutValue); 
}

/**
  * @brief Enable the SMARTCARD receiver timeout feature
  * @param hsc SMARTCARD handle
  * @retval HAL status
  */
HAL_StatusTypeDef HAL_SMARTCARDEx_EnableReceiverTimeOut(SMARTCARD_HandleTypeDef *hsc)
{
  /* Process Locked */
  __HAL_LOCK(hsc);

  hsc->gState = HAL_SMARTCARD_STATE_BUSY;

  /* Set the USART RTOEN bit */
  hsc->Instance->CR2 |= USART_CR2_RTOEN;

  hsc->gState = HAL_SMARTCARD_STATE_READY;

  /* Process Unlocked */
  __HAL_UNLOCK(hsc);

  return HAL_OK;
}

/**
  * @brief Disable the SMARTCARD receiver timeout feature
  * @param hsc SMARTCARD handle
  * @retval HAL status
  */
HAL_StatusTypeDef HAL_SMARTCARDEx_DisableReceiverTimeOut(SMARTCARD_HandleTypeDef *hsc)
{
  /* Process Locked */
  __HAL_LOCK(hsc);

  hsc->gState = HAL_SMARTCARD_STATE_BUSY;

  /* Clear the USART RTOEN bit */
  hsc->Instance->CR2 &= ~(USART_CR2_RTOEN);

  hsc->gState = HAL_SMARTCARD_STATE_READY;

  /* Process Unlocked */
  __HAL_UNLOCK(hsc);

  return HAL_OK;
=======
/** @brief Update on the fly the SMARTCARD block length in RTOR register.
  * @param hsmartcard Pointer to a SMARTCARD_HandleTypeDef structure that contains
  *                    the configuration information for the specified SMARTCARD module.
  * @param BlockLength SMARTCARD block length (8-bit long at most)
  * @retval None
  */
void HAL_SMARTCARDEx_BlockLength_Config(SMARTCARD_HandleTypeDef *hsmartcard, uint8_t BlockLength)
{
  MODIFY_REG(hsmartcard->Instance->RTOR, USART_RTOR_BLEN, ((uint32_t)BlockLength << USART_RTOR_BLEN_Pos));
}

/** @brief Update on the fly the receiver timeout value in RTOR register.
  * @param hsmartcard Pointer to a SMARTCARD_HandleTypeDef structure that contains
  *                    the configuration information for the specified SMARTCARD module.
  * @param TimeOutValue receiver timeout value in number of baud blocks. The timeout
  *                     value must be less or equal to 0x0FFFFFFFF.
  * @retval None
  */
void HAL_SMARTCARDEx_TimeOut_Config(SMARTCARD_HandleTypeDef *hsmartcard, uint32_t TimeOutValue)
{
  assert_param(IS_SMARTCARD_TIMEOUT_VALUE(hsmartcard->Init.TimeOutValue));
  MODIFY_REG(hsmartcard->Instance->RTOR, USART_RTOR_RTO, TimeOutValue);
}

/** @brief Enable the SMARTCARD receiver timeout feature.
  * @param hsmartcard Pointer to a SMARTCARD_HandleTypeDef structure that contains
  *                    the configuration information for the specified SMARTCARD module.
  * @retval HAL status
  */
HAL_StatusTypeDef HAL_SMARTCARDEx_EnableReceiverTimeOut(SMARTCARD_HandleTypeDef *hsmartcard)
{
  if (hsmartcard->gState == HAL_SMARTCARD_STATE_READY)
  {
    /* Process Locked */
    __HAL_LOCK(hsmartcard);

    hsmartcard->gState = HAL_SMARTCARD_STATE_BUSY;

    /* Set the USART RTOEN bit */
    SET_BIT(hsmartcard->Instance->CR2, USART_CR2_RTOEN);

    hsmartcard->gState = HAL_SMARTCARD_STATE_READY;

    /* Process Unlocked */
    __HAL_UNLOCK(hsmartcard);

    return HAL_OK;
  }
  else
  {
    return HAL_BUSY;
  }
}

/** @brief Disable the SMARTCARD receiver timeout feature.
  * @param hsmartcard Pointer to a SMARTCARD_HandleTypeDef structure that contains
  *                    the configuration information for the specified SMARTCARD module.
  * @retval HAL status
  */
HAL_StatusTypeDef HAL_SMARTCARDEx_DisableReceiverTimeOut(SMARTCARD_HandleTypeDef *hsmartcard)
{
  if (hsmartcard->gState == HAL_SMARTCARD_STATE_READY)
  {
    /* Process Locked */
    __HAL_LOCK(hsmartcard);

    hsmartcard->gState = HAL_SMARTCARD_STATE_BUSY;

    /* Clear the USART RTOEN bit */
    CLEAR_BIT(hsmartcard->Instance->CR2, USART_CR2_RTOEN);

    hsmartcard->gState = HAL_SMARTCARD_STATE_READY;

    /* Process Unlocked */
    __HAL_UNLOCK(hsmartcard);

    return HAL_OK;
  }
  else
  {
    return HAL_BUSY;
  }
>>>>>>> 49e424905b5922b07aa7166ec7a0eeb90adf58a8
}

/**
  * @}
  */

<<<<<<< HEAD
=======
/** @defgroup SMARTCARDEx_Exported_Functions_Group2 Extended Peripheral IO operation functions
  * @brief   SMARTCARD Transmit and Receive functions
  *
@verbatim
 ===============================================================================
                      ##### IO operation functions #####
 ===============================================================================
    [..]
@endverbatim
  * @{
  */

/**
  * @}
  */

/** @defgroup SMARTCARD_Exported_Functions_Group3 Extended Peripheral Peripheral Control functions
  *  @brief   SMARTCARD control functions
  *
@verbatim
 ===============================================================================
                      ##### Peripheral Control functions #####
 ===============================================================================
    [..]
@endverbatim
  * @{
  */


/**
  * @}
  */

/**
  * @}
  */

/** @defgroup SMARTCARDEx_Private_Functions  SMARTCARD Extended private Functions
  * @{
  */

>>>>>>> 49e424905b5922b07aa7166ec7a0eeb90adf58a8
/**
  * @}
  */

#endif /* HAL_SMARTCARD_MODULE_ENABLED */
<<<<<<< HEAD
=======

>>>>>>> 49e424905b5922b07aa7166ec7a0eeb90adf58a8
/**
  * @}
  */

/**
  * @}
  */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
