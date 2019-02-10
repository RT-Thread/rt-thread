/**
  ******************************************************************************
  * @file    stm32h7xx_hal_spi_ex.c
  * @author  MCD Application Team
  * @version V1.2.0
  * @date   29-December-2017
  * @brief   Extended SPI HAL module driver.
  *          This file provides firmware functions to manage the following
  *          SPI peripheral extended functionalities :
  *           + IO operation functions
  *           + Peripheral Control functions
  *
  ******************************************************************************
  * @attention
  *
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
  *
  ******************************************************************************
  */

/* Includes ------------------------------------------------------------------*/
#include "stm32h7xx_hal.h"

/** @addtogroup STM32H7xx_HAL_Driver
  * @{
  */

/** @defgroup SPIEx SPIEx
  * @brief SPI Extended HAL module driver
  * @{
  */
#ifdef HAL_SPI_MODULE_ENABLED

/* Private typedef -----------------------------------------------------------*/
/* Private defines -----------------------------------------------------------*/
/* Private macros ------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
/* Exported functions --------------------------------------------------------*/

/** @defgroup SPIEx_Exported_Functions SPIEx Exported Functions
  * @{
  */

/** @defgroup SPIEx_Exported_Functions_Group1 IO operation functions
  *  @brief   Data transfers functions
  *
@verbatim
  ==============================================================================
                      ##### IO operation functions #####
 ===============================================================================
 [..]
    This subsection provides a set of extended functions to manage the SPI
    data transfers.

    (#) SPIEx function:
        (++) HAL_SPIEx_FlushRxFifo()
        (++) HAL_SPIEx_FlushRxFifo()
        (++) HAL_SPIEx_EnableLockConfiguration()
        (++) HAL_SPIEx_ConfigureUnderrun()

@endverbatim
  * @{
  */

/**
  * @brief Flush the RX fifo.
  * @param  hspi: pointer to a SPI_HandleTypeDef structure that contains
  *               the configuration information for the specified SPI module.
  * @retval HAL status
  */
HAL_StatusTypeDef HAL_SPIEx_FlushRxFifo(SPI_HandleTypeDef *hspi)
{
  __IO uint32_t tmpreg;
  uint8_t  count = 0;
  while ( ((hspi->Instance->SR & SPI_FLAG_FRLVL) !=  SPI_FRLVL_EMPTY) || ((hspi->Instance->SR & SPI_FLAG_RXWNE) ==  SPI_FLAG_RXWNE))
  {
    count+=4;
    tmpreg = hspi->Instance->RXDR;
    UNUSED(tmpreg); /* To avoid GCC warning */
    
    if (IS_SPI_HIGHEND_INSTANCE(hspi->Instance))
    {
      if(count > SPI_HIGHEND_FIFO_SIZE)
      {
        return HAL_TIMEOUT;
      }
    }
    else
    {
      if(count > SPI_LOWEND_FIFO_SIZE)
      {
        return HAL_TIMEOUT;
      }
    }
  }
  return HAL_OK;
}


/**
  * @brief  Enable the Lock for the AF configuration of associated IOs
  *         and write protect the Content of Configuartion register 2
  *         when SPI is enabled
  * @param  hspi: pointer to a SPI_HandleTypeDef structure that contains
  *               the configuration information for SPI module.
  * @retval None
  */
HAL_StatusTypeDef HAL_SPIEx_EnableLockConfiguration(SPI_HandleTypeDef *hspi)
{
  HAL_StatusTypeDef errorcode = HAL_OK;

  /* Process Locked */
  __HAL_LOCK(hspi);

  if (hspi->State != HAL_SPI_STATE_READY)
  {
    errorcode = HAL_BUSY;
    hspi->State = HAL_SPI_STATE_READY;
    /* Process Unlocked */
    __HAL_UNLOCK(hspi);
    return errorcode;
  }

  /* Check if the SPI is disabled to edit IOLOCK bit */
  if ((hspi->Instance->CR1 & SPI_CR1_SPE) != SPI_CR1_SPE)
  {
    SET_BIT(hspi->Instance->CR1 , SPI_CR1_IOLOCK);
  }
  else
  {
    /* Disable SPI peripheral */
    __HAL_SPI_DISABLE(hspi);

    SET_BIT(hspi->Instance->CR1 , SPI_CR1_IOLOCK);

    /* Enable SPI peripheral */
    __HAL_SPI_ENABLE(hspi);
  }

  hspi->State = HAL_SPI_STATE_READY;
  /* Process Unlocked */
  __HAL_UNLOCK(hspi);
  return errorcode;
}

/**
  * @brief  Configure the UNDERRUN condition and behavior of slave transmitter.
  * @param  hspi: pointer to a SPI_HandleTypeDef structure that contains
  *               the configuration information for SPI module.
  * @param  UnderrunDetection : Detection of underrun condition at slave transmitter
  *                             This parameter can be a value of @ref SPI_Underrun_Detection.
  * @param  UnderrunBehaviour : Behavior of slave transmitter at underrun condition
  *                             This parameter can be a value of @ref SPI_Underrun_Behaviour.
  * @retval None
  */ 
HAL_StatusTypeDef HAL_SPIEx_ConfigureUnderrun(SPI_HandleTypeDef *hspi, uint32_t UnderrunDetection, uint32_t UnderrunBehaviour)
{
  HAL_StatusTypeDef errorcode = HAL_OK;

  /* Process Locked */
  __HAL_LOCK(hspi);

  /* Check State and Insure that Underrun configuration is managed only by Salve */
  if ((hspi->State != HAL_SPI_STATE_READY) || (hspi->Init.Mode != SPI_MODE_SLAVE))
  {
    errorcode = HAL_BUSY;
    hspi->State = HAL_SPI_STATE_READY;
    /* Process Unlocked */
    __HAL_UNLOCK(hspi);
    return errorcode;
  }

  /* Check the parameters */
  assert_param(IS_SPI_UNDERRUN_DETECTION(UnderrunDetection));
  assert_param(IS_SPI_UNDERRUN_BEHAVIOUR(UnderrunBehaviour));

  /* Check if the SPI is disabled to edit CFG1 register */
  if ((hspi->Instance->CR1 & SPI_CR1_SPE) != SPI_CR1_SPE)
  {
    /* Configure Underrun fields */
    MODIFY_REG(hspi->Instance->CFG1, SPI_CFG1_UDRDET, UnderrunDetection);
    MODIFY_REG(hspi->Instance->CFG1, SPI_CFG1_UDRCFG, UnderrunBehaviour);
  }
  else
  {
    /* Disable SPI peripheral */
    __HAL_SPI_DISABLE(hspi);

    /* Configure Underrun fields */
    MODIFY_REG(hspi->Instance->CFG1, SPI_CFG1_UDRDET, UnderrunDetection);
    MODIFY_REG(hspi->Instance->CFG1, SPI_CFG1_UDRCFG, UnderrunBehaviour);

    /* Enable SPI peripheral */
    __HAL_SPI_ENABLE(hspi);
  }


  hspi->State = HAL_SPI_STATE_READY;
  /* Process Unlocked */
  __HAL_UNLOCK(hspi);
  return errorcode;
}

/**
  * @}
  */

/**
  * @}
  */

#endif /* HAL_SPI_MODULE_ENABLED */

/**
  * @}
  */

/**
  * @}
  */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
