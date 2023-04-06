/**
  ******************************************************************************
  * @file    stm32u5xx_hal_spi_ex.c
  * @author  MCD Application Team
  * @brief   Extended SPI HAL module driver.
  *          This file provides firmware functions to manage the following
  *          SPI peripheral extended functionalities :
  *           + IO operation functions
  *           + Peripheral Control functions
  *
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2021 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */

/* Includes ------------------------------------------------------------------*/
#include "stm32u5xx_hal.h"

/** @addtogroup STM32U5xx_HAL_Driver
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
  uint8_t  count  = 0;
  uint32_t itflag = hspi->Instance->SR;
  __IO uint32_t tmpreg;

  while (((hspi->Instance->SR & SPI_FLAG_FRLVL) !=  SPI_RX_FIFO_0PACKET) || ((itflag & SPI_FLAG_RXWNE) !=  0UL))
  {
    count += (uint8_t)4UL;
    tmpreg = hspi->Instance->RXDR;
    UNUSED(tmpreg); /* To avoid GCC warning */

    if (IS_SPI_FULL_INSTANCE(hspi->Instance))
    {
      if (count > SPI_HIGHEND_FIFO_SIZE)
      {
        return HAL_TIMEOUT;
      }
    }
    else
    {
      if (count > SPI_LOWEND_FIFO_SIZE)
      {
        return HAL_TIMEOUT;
      }
    }
  }
  return HAL_OK;
}


/**
  * @brief  Enable the Lock for the AF configuration of associated IOs
  *         and write protect the Content of Configuration register 2
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
    SET_BIT(hspi->Instance->CR1, SPI_CR1_IOLOCK);
  }
  else
  {
    /* Disable SPI peripheral */
    __HAL_SPI_DISABLE(hspi);

    SET_BIT(hspi->Instance->CR1, SPI_CR1_IOLOCK);

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
  *                             This parameter is not supported in this SPI version.
  *                             It is kept in order to not break the compatibility.
  * @param  UnderrunBehaviour : Behavior of slave transmitter at underrun condition
  *                             This parameter can be a value of @ref SPI_Underrun_Behaviour.
  * @retval None
  */
HAL_StatusTypeDef HAL_SPIEx_ConfigureUnderrun(SPI_HandleTypeDef *hspi, uint32_t UnderrunDetection,
                                              uint32_t UnderrunBehaviour)
{
  /* Prevent unused argument(s) compilation warning */
  UNUSED(UnderrunDetection);

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
  assert_param(IS_SPI_UNDERRUN_BEHAVIOUR(UnderrunBehaviour));

  /* Check if the SPI is disabled to edit CFG1 register */
  if ((hspi->Instance->CR1 & SPI_CR1_SPE) != SPI_CR1_SPE)
  {
    /* Configure Underrun fields */
    MODIFY_REG(hspi->Instance->CFG1, SPI_CFG1_UDRCFG, UnderrunBehaviour);
  }
  else
  {
    /* Disable SPI peripheral */
    __HAL_SPI_DISABLE(hspi);

    /* Configure Underrun fields */
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
  * @brief  Set Autonomous Mode configuration
  * @param  hspi Pointer to a SPI_HandleTypeDef structure that contains
  *                the configuration information for the specified SPIx peripheral.
  * @param  sConfig Pointer to a SPI_HandleTypeDef structure that contains
  *                the configuration information of the autonomous mode for the specified SPIx peripheral.
  * @retval HAL status
  */
HAL_StatusTypeDef HAL_SPIEx_SetConfigAutonomousMode(SPI_HandleTypeDef *hspi, SPI_AutonomousModeConfTypeDef *sConfig)
{
  if (hspi->State == HAL_SPI_STATE_READY)
  {
    /* Process Locked */
    __HAL_LOCK(hspi);

    hspi->State = HAL_SPI_STATE_BUSY;

    /* Check the parameters */
    assert_param(IS_SPI_TRIG_SOURCE(hspi->Instance, sConfig->TriggerSelection));

    assert_param(IS_SPI_AUTO_MODE_TRG_POL(sConfig->TriggerPolarity));

    /* Disable the selected SPI peripheral to be able to configure AUTOCR */
    __HAL_SPI_DISABLE(hspi);

    /* SPIx AUTOCR Configuration */
    WRITE_REG(hspi->Instance->AUTOCR, (sConfig->TriggerState | ((sConfig->TriggerSelection) & SPI_AUTOCR_TRIGSEL_Msk) |
                                       sConfig->TriggerPolarity));

    hspi->State = HAL_SPI_STATE_READY;

    /* Process Unlocked */
    __HAL_UNLOCK(hspi);

    return HAL_OK;
  }
  else
  {
    return HAL_ERROR;
  }
}

/**
  * @brief  Get Autonomous Mode configuration
  * @param  hspi Pointer to a SPI_HandleTypeDef structure that contains
  *                the configuration information for the specified SPIx peripheral.
  * @param  sConfig Pointer to a SPI_HandleTypeDef structure that contains
  *                the configuration information of the autonomous mode for the specified SPIx peripheral.
  * @retval HAL status
  */
HAL_StatusTypeDef HAL_SPIEx_GetConfigAutonomousMode(SPI_HandleTypeDef *hspi, SPI_AutonomousModeConfTypeDef *sConfig)
{
  uint32_t autocr_tmp;

  autocr_tmp = hspi->Instance->AUTOCR;

  sConfig->TriggerState     = (autocr_tmp & SPI_AUTOCR_TRIGEN);
  if (IS_SPI_GRP2_INSTANCE(hspi->Instance))
  {
    sConfig->TriggerSelection = ((autocr_tmp & SPI_AUTOCR_TRIGSEL) | SPI_TRIG_GRP2);
  }
  else
  {
    sConfig->TriggerSelection = ((autocr_tmp & SPI_AUTOCR_TRIGSEL) | SPI_TRIG_GRP1);
  }
  sConfig->TriggerPolarity  = (autocr_tmp & SPI_AUTOCR_TRIGPOL);

  return HAL_OK;
}

/**
  * @brief  Clear Autonomous Mode configuration
  * @param  hspi Pointer to a SPI_HandleTypeDef structure that contains
  *                the configuration information for the specified SPIx peripheral.
  * @retval HAL status
  */
HAL_StatusTypeDef HAL_SPIEx_ClearConfigAutonomousMode(SPI_HandleTypeDef *hspi)
{
  if (hspi->State == HAL_SPI_STATE_READY)
  {
    /* Process Locked */
    __HAL_LOCK(hspi);

    hspi->State = HAL_SPI_STATE_BUSY;

    /* Disable the selected SPI peripheral to be able to clear AUTOCR */
    __HAL_SPI_DISABLE(hspi);

    CLEAR_REG(hspi->Instance->AUTOCR);

    /* Enable the selected SPI peripheral */
    __HAL_SPI_ENABLE(hspi);

    hspi->State = HAL_SPI_STATE_READY;

    /* Process Unlocked */
    __HAL_UNLOCK(hspi);

    return HAL_OK;
  }
  else
  {
    return HAL_ERROR;
  }
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
