  /**
  ******************************************************************************
  * @file    stm32h7xx_hal_i2s_ex.c
  * @author  MCD Application Team
  * @version V1.2.0
  * @date   29-December-2017
  * @brief   I2S HAL module driver.
  *          This file provides firmware functions to manage the following
  *          functionalities of I2S extension peripheral:
  *           + IO operation functions
  *           + Peripheral Control functions
  *
  @verbatim
  ==============================================================================
                  ##### I2S Extension features #####
  ==============================================================================
  [..]
     (+) In I2S full duplex mode, SPI2S peripheral is able to manage sending and receiving
         data simultaneously using two data lines.
  @endverbatim

  @verbatim
 ===============================================================================
                  ##### How to use this driver #####
 ===============================================================================
 [..]
   Three operation modes are available within this driver :

   *** Polling mode IO operation ***
   =================================
   [..]
     (+) Send and receive in the same time an amount of data in blocking mode using HAL_I2SEx_TransmitReceive()

   *** Interrupt mode IO operation ***
   ===================================
   [..]
     (+) Send and receive in the same time an amount of data in non blocking mode using HAL_I2SEx_TransmitReceive_IT()
     (+) At full duplex transfer end of half transfer HAL_I2SEx_TxRxHalfCpltCallback is executed and user can
         add his own code by customization of function pointer HAL_I2SEx_TxRxHalfCpltCallback
     (+) At full duplex transfer end of transfer HAL_I2SEx_TxRxCpltCallback is executed and user can
         add his own code by customization of function pointer HAL_I2SEx_TxRxCpltCallback
     (+) In case of transfer Error, HAL_I2S_ErrorCallback() function is executed and user can
         add his own code by customization of function pointer HAL_I2S_ErrorCallback

   *** DMA mode IO operation ***
   ==============================
   [..]
     (+) Send and receive an amount of data in non blocking mode (DMA) using HAL_I2SEx_TransmitReceive_DMA()
     (+) At the end of half transfer HAL_I2SEx_TxRxHalfCpltCallback is executed and user can
         add his own code by customization of function pointer HAL_I2S_TxHalfCpltCallback
     (+) At the end of transfer HAL_I2S_TxRxCpltCallback is executed and user can
         add his own code by customization of function pointer HAL_I2S_TxCpltCallback
     (+) In case of transfer Error, HAL_I2S_ErrorCallback() function is executed and user can
         add his own code by customization of function pointer HAL_I2S_ErrorCallback
     (+) Pause the DMA Transfer using HAL_I2S_DMAPause()
     (+) Resume the DMA Transfer using HAL_I2S_DMAResume()
     (+) Stop the DMA Transfer using HAL_I2S_DMAStop()

  @endverbatim
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

#ifdef HAL_I2S_MODULE_ENABLED
/** @defgroup I2SEx I2SEx
  * @brief I2S Extended HAL module driver
  * @{
  */

/* Private typedef -----------------------------------------------------------*/
/** @defgroup I2SEx_Private_Typedef I2S Extended Private Typedef
  * @{
  */
typedef enum
{
  I2S_USE_I2S      = 0x00U,   /*!< I2Sx should be used      */
  I2S_USE_I2SEXT   = 0x01U,   /*!< I2Sx_ext should be used  */
}I2S_UseTypeDef;
/**
  * @}
  */
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
/** @defgroup I2SEx_Private_Functions I2S Extended Private Functions
  * @{
  */
static void              I2SEx_DMATxRxCplt(DMA_HandleTypeDef *hdma);
static void              I2SEx_DMATxRxHalfCplt(DMA_HandleTypeDef *hdma);
static void              I2SEx_TxRxDMAError(DMA_HandleTypeDef *hdma);

static void              I2SEx_2linesTxISR_16BIT(struct __I2S_HandleTypeDef *hi2s);
static void              I2SEx_2linesTxISR_32BIT(struct __I2S_HandleTypeDef *hi2s);
static void              I2SEx_2linesRxISR_16BIT(struct __I2S_HandleTypeDef *hi2s);
static void              I2SEx_2linesRxISR_32BIT(struct __I2S_HandleTypeDef *hi2s);
static void              I2SEx_CloseRxTx_ISR(I2S_HandleTypeDef *hi2s);

static HAL_StatusTypeDef I2SEx_WaitFlagStateUntilTimeout(I2S_HandleTypeDef *hi2s, uint32_t Flag, uint32_t State, uint32_t Timeout);

/**
  * @}
  */

/* Private functions ---------------------------------------------------------*/
/* Exported functions --------------------------------------------------------*/

/** @addtogroup I2SEx_Exported_Functions I2S Extended Exported Functions
  * @{
  */

/** @defgroup I2SEx_Exported_Functions_Group1 I2S Extended IO operation functions
  *  @brief   I2SEx IO operation functions
  *
@verbatim
 ===============================================================================
                       ##### IO operation functions#####
 ===============================================================================
    [..]
    This subsection provides a set of functions allowing to manage the I2S data
    transfers.

    (#) There are two modes of transfer:
       (++) Blocking mode : The communication is performed in the polling mode.
            The status of all data processing is returned by the same function
            after finishing transfer.
       (++) No-Blocking mode : The communication is performed using Interrupts
            or DMA. These functions return the status of the transfer startup.
            The end of the data processing will be indicated through the
            dedicated I2S IRQ when using Interrupt mode or the DMA IRQ when
            using DMA mode.

    (#) Blocking mode functions are :
        (++) HAL_I2SEx_TransmitReceive()

    (#) No-Blocking mode functions with Interrupt are :
        (++) HAL_I2SEx_TransmitReceive_IT()

    (#) No-Blocking mode functions with DMA are :
        (++) HAL_I2SEx_TransmitReceive_DMA()

    (#) A set of Transfer Complete Callbacks are provided in non Blocking mode:
        (++) HAL_I2SEx_TxRxCpltCallback()
        (++) HAL_I2SEx_TxRxErrorCallback()

@endverbatim
  * @{
  */

/**
  * @brief  Transmit and Receive an amount of data in blocking mode
  * @param  hi2s: pointer to a I2S_HandleTypeDef structure that contains
  *         the configuration information for I2S module
  * @param  pTxData: a 16-bit pointer to the Transmit data buffer
  * @param  pRxData: a 16-bit pointer to the Receive data buffer
  * @param  Size: number of frames to be sent
  * @param  Timeout: Timeout duration
  * @note   The I2S is kept enabled at the end of transaction to avoid the clock de-synchronization 
  *         between Master and Slave(example: audio streaming).
  * @note   This function can use an Audio Frequency up to 48KHz when I2S Clock Source is 32MHz
  * @retval HAL status
  */
HAL_StatusTypeDef HAL_I2SEx_TransmitReceive(I2S_HandleTypeDef *hi2s, uint16_t *pTxData, uint16_t *pRxData, uint16_t Size, uint32_t Timeout)
{
  uint32_t tickstart = 0U;
  uint32_t isDataFormat16B = 2U;

  /* Check Mode parameter */
  assert_param(IS_I2S_FD_MODE(hi2s->Init.Mode));

  if((pTxData == NULL ) || (Size == 0U))
  {
    return  HAL_ERROR;
  }

  /* Process Locked */
  __HAL_LOCK(hi2s);

  /* Init tickstart for timeout management*/
  tickstart = HAL_GetTick();

  if(hi2s->State == HAL_I2S_STATE_READY)
  {
    /* Check the Data Format value */
    if (((hi2s->Instance->I2SCFGR & (SPI_I2SCFGR_DATLEN | SPI_I2SCFGR_CHLEN)) == I2S_DATAFORMAT_24B) ||
        ((hi2s->Instance->I2SCFGR & (SPI_I2SCFGR_DATLEN | SPI_I2SCFGR_CHLEN)) == I2S_DATAFORMAT_32B))
    {
      isDataFormat16B = 0U;
    }
    else
    {
      isDataFormat16B = 1U;
    }

    if(!isDataFormat16B)
    {
      hi2s->TxXferSize  = (Size << 1U);
      hi2s->TxXferCount = (Size << 1U);

      hi2s->RxXferSize  = (Size << 1U);
      hi2s->RxXferCount = (Size << 1U);
    }
    else
    {
      hi2s->TxXferSize  = Size;
      hi2s->TxXferCount = Size;

      hi2s->RxXferSize  = Size;
      hi2s->RxXferCount = Size;
    }

    /* Set state and reset error code */
    hi2s->ErrorCode = HAL_I2S_ERROR_NONE;
    hi2s->State = HAL_I2S_STATE_BUSY_TX_RX;
    hi2s->pTxBuffPtr = pTxData;
    hi2s->pRxBuffPtr = pRxData;

    /* Check if the SPI2S is already enabled */
    if((hi2s->Instance->CR1 & SPI_CR1_SPE) != SPI_CR1_SPE)
    {
      /* Enable I2S peripheral */
      __HAL_I2S_ENABLE(hi2s);
    }

    if(IS_I2S_MASTER(hi2s->Init.Mode))
    {
      hi2s->Instance->CR1 |= SPI_CR1_CSTART;
    }

    /* Transmit and Receive data in 32 Bit mode */
    if (!isDataFormat16B)
    {
      while ((hi2s->TxXferCount > 0U) || (hi2s->RxXferCount > 0U))
      {
        /* Check TXE flag */
        if ((hi2s->TxXferCount > 0U) && (__HAL_I2S_GET_FLAG(hi2s, I2S_FLAG_TXE)))
        {
          *((__IO uint32_t *)&hi2s->Instance->TXDR) = *((uint32_t *)hi2s->pTxBuffPtr);
          hi2s->pTxBuffPtr += sizeof(uint32_t);
          hi2s->TxXferCount --;
        }
  
        /* Check RXNE flag */
        if ((hi2s->RxXferCount > 0U) && (__HAL_I2S_GET_FLAG(hi2s, I2S_FLAG_RXNE)))
        {
          *((uint32_t *)hi2s->pRxBuffPtr) = *((__IO uint32_t *)&hi2s->Instance->RXDR);
          hi2s->pRxBuffPtr += sizeof(uint32_t);
          hi2s->RxXferCount --;
        }

        /* Timeout Management */
        if ((Timeout != HAL_MAX_DELAY) && ((HAL_GetTick() - tickstart) >=  Timeout))
        {
          /* Set the error code and execute error callback*/
          SET_BIT(hi2s->ErrorCode, HAL_I2S_ERROR_TIMEOUT);
          HAL_I2S_ErrorCallback(hi2s);

          /* Set the I2S State ready */
          hi2s->State = HAL_I2S_STATE_READY;

          /* Process Unlocked */
          __HAL_UNLOCK(hi2s);
          return HAL_ERROR;
        }
      }
    }
    /* Transmit and Receive data in 16 Bit mode */
    else 
    {
      while ((hi2s->TxXferCount > 0U) || (hi2s->RxXferCount > 0U))
      {
        /* Check TXE flag */
        if ((hi2s->TxXferCount > 0U) && (__HAL_I2S_GET_FLAG(hi2s, I2S_FLAG_TXE)))
        {
          if ( (hi2s->TxXferCount > 1U) && (hi2s->Init.FifoThreshold > SPI_FIFO_THRESHOLD_01DATA))
          {
            *((__IO uint32_t *)&hi2s->Instance->TXDR) = *((uint32_t *)hi2s->pTxBuffPtr);
            hi2s->pTxBuffPtr += sizeof(uint32_t);
            hi2s->TxXferCount-=2;
          }
          else
          {
            *((__IO uint16_t *)&hi2s->Instance->TXDR) = *((uint16_t *)hi2s->pTxBuffPtr);
            hi2s->pTxBuffPtr += sizeof(uint16_t);
            hi2s->TxXferCount--;
          }
        }

        /* Check RXNE flag */
        if ((hi2s->RxXferCount > 0U) && (__HAL_I2S_GET_FLAG(hi2s, I2S_FLAG_RXNE)))
        {
          if (hi2s->Instance->SR & I2S_FLAG_RXWNE)
          {
            *((uint32_t *)hi2s->pRxBuffPtr) = *((__IO uint32_t *)&hi2s->Instance->RXDR);
            hi2s->pRxBuffPtr += sizeof(uint32_t);
            hi2s->RxXferCount-=2;
          }
          else
          {
            *((uint16_t *)hi2s->pRxBuffPtr) = *((__IO uint16_t *)&hi2s->Instance->RXDR);
            hi2s->pRxBuffPtr += sizeof(uint16_t);
            hi2s->RxXferCount--;
          }
        }

        /* Timeout Management */
        if ((Timeout != HAL_MAX_DELAY) && ((HAL_GetTick() - tickstart) >=  Timeout))
        {
          /* Set the error code and execute error callback*/
          SET_BIT(hi2s->ErrorCode, HAL_I2S_ERROR_TIMEOUT);
          HAL_I2S_ErrorCallback(hi2s);

          /* Set the I2S State ready */
          hi2s->State = HAL_I2S_STATE_READY;

          /* Process Unlocked */
          __HAL_UNLOCK(hi2s);
          return HAL_ERROR;
        }
      }
    }

    /* Wait until TXE flag is set, to confirm the end of the transaction */
    if (I2SEx_WaitFlagStateUntilTimeout(hi2s, I2S_FLAG_TXE, RESET, Timeout) != HAL_OK)
    {
      return HAL_TIMEOUT;
    }

    hi2s->State = HAL_I2S_STATE_READY;

    /* Process Unlocked */
    __HAL_UNLOCK(hi2s);

    return HAL_OK;
  }
  else
  {
    /* Process Unlocked */
    __HAL_UNLOCK(hi2s);
    return HAL_BUSY;
  }
}

/**
  * @brief  Transmit and Receive an amount of data in non-blocking mode with Interrupt
  * @param  hi2s: pointer to a I2S_HandleTypeDef structure that contains
  *         the configuration information for I2S module
  * @param pTxData: a 16-bit pointer to the Transmit data buffer.
  * @param pRxData: a 16-bit pointer to the Receive data buffer.
  * @param Size: number of data sample to be sent:
  * @note When a 16-bit data frame or a 16-bit data frame extended is selected during the I2S
  *       configuration phase, the Size parameter means the number of 16-bit data length 
  *       in the transaction and when a 24-bit data frame or a 32-bit data frame is selected 
  *       the Size parameter means the number of 16-bit data length. 
  * @note The I2S is kept enabled at the end of transaction to avoid the clock de-synchronization 
  *       between Master and Slave(example: audio streaming).
  * @note This function can use an Audio Frequency up to 48KHz when I2S Clock Source is 32MHz  
  * @retval HAL status
  */
HAL_StatusTypeDef HAL_I2SEx_TransmitReceive_IT(I2S_HandleTypeDef *hi2s, uint16_t *pTxData, uint16_t *pRxData, uint16_t Size)
{
  /* Check Mode parameter */
  assert_param(IS_I2S_FD_MODE(hi2s->Init.Mode));

  /* Process Locked */
  __HAL_LOCK(hi2s);

  if((pTxData == NULL) || (pRxData == NULL) || (Size == 0U)) 
  {
    __HAL_UNLOCK(hi2s);
    return  HAL_ERROR;
  }

  if (hi2s->State == HAL_I2S_STATE_READY)
  {
    __HAL_UNLOCK(hi2s);
    return  HAL_BUSY;
  }

  /* Set the transaction information */
  hi2s->State       = HAL_I2S_STATE_BUSY_TX;
  hi2s->ErrorCode   = HAL_I2S_ERROR_NONE;
  hi2s->pTxBuffPtr  = pTxData;
  hi2s->TxXferSize  = Size;
  hi2s->TxXferCount = Size;

  /* Init field not used in handle to zero */
  hi2s->pRxBuffPtr  = pRxData;
  hi2s->RxXferSize  = Size;
  hi2s->RxXferCount = Size;

  /* Set the function for IT treatment */
  if (hi2s->Init.DataFormat > I2S_DATAFORMAT_16B)
  {
    hi2s->RxISR = I2SEx_2linesRxISR_32BIT;
    hi2s->TxISR = I2SEx_2linesTxISR_32BIT;
  }
  else
  {
    hi2s->RxISR = I2SEx_2linesRxISR_16BIT;
    hi2s->TxISR = I2SEx_2linesTxISR_16BIT;
  }

  /* Check if the I2S is already enabled */
  if ((hi2s->Instance->CR1 & SPI_CR1_SPE) != SPI_CR1_SPE)
  {
    /* Enable SPI peripheral */
    __HAL_I2S_ENABLE(hi2s);
  }

  if (IS_I2S_MASTER(hi2s->Init.Mode))
  {
    /* Master transfer start */
    SET_BIT(hi2s->Instance->CR1, SPI_CR1_CSTART);
  }

  /* Enable TXE and ERR interrupt */
  __HAL_I2S_ENABLE_IT(hi2s, (I2S_IT_TXE | I2S_IT_RXNE | I2S_IT_ERR));

  /* Process Unlocked */
  __HAL_UNLOCK(hi2s);

  return HAL_OK;
}

/**
  * @brief  Transmit and Receive an amount of data in non-blocking mode with DMA
  * @param  hi2s: pointer to a I2S_HandleTypeDef structure that contains
  *         the configuration information for I2S module
  * @param  pTxData: a 16-bit pointer to the Transmit data buffer.
  * @param  pRxData: a 16-bit pointer to the Receive data buffer.
  * @param  Size: number of frames to be sent.
  * @note   The I2S is kept enabled at the end of transaction to avoid the clock de-synchronization 
  *         between Master and Slave(example: audio streaming).
  * @retval HAL status
  */
HAL_StatusTypeDef HAL_I2SEx_TransmitReceive_DMA(I2S_HandleTypeDef *hi2s, uint16_t *pTxData, uint16_t *pRxData, uint16_t Size)
{
  /* Check Mode parameter */
  assert_param(IS_I2S_FD_MODE(hi2s->Init.Mode));

  if((pTxData == NULL) || (Size == 0U)) 
  {
    return  HAL_ERROR;
  }

  /* Process Locked */
  __HAL_LOCK(hi2s);

  if(hi2s->State == HAL_I2S_STATE_READY)
  {  
    hi2s->pTxBuffPtr = pTxData;
    hi2s->pRxBuffPtr = pRxData;
    hi2s->State = HAL_I2S_STATE_BUSY_TX_RX;
    hi2s->ErrorCode = HAL_I2S_ERROR_NONE;

    if(((hi2s->Instance->I2SCFGR & (SPI_I2SCFGR_DATLEN | SPI_I2SCFGR_CHLEN)) == I2S_DATAFORMAT_24B)||\
      ((hi2s->Instance->I2SCFGR & (SPI_I2SCFGR_DATLEN | SPI_I2SCFGR_CHLEN)) == I2S_DATAFORMAT_32B))
    {
      hi2s->TxXferSize  = (Size << 1U);
      hi2s->TxXferCount = (Size << 1U);

      hi2s->RxXferSize  = (Size << 1U);
      hi2s->RxXferCount = (Size << 1U);
    }
    else
    {
      hi2s->TxXferSize  = Size;
      hi2s->TxXferCount = Size;

      hi2s->RxXferSize  = Size;
      hi2s->RxXferCount = Size;
    }

    /* Set the I2S Rx DMA Half transfert complete callback */
    hi2s->hdmarx->XferHalfCpltCallback = I2SEx_DMATxRxHalfCplt;

    /* Set the I2S Rx DMA transfert complete callback */
    hi2s->hdmarx->XferCpltCallback = I2SEx_DMATxRxCplt;

    /* Set the DMA error callback */
    hi2s->hdmarx->XferErrorCallback = I2SEx_TxRxDMAError;

    /* Enable the Rx DMA Channel */
    HAL_DMA_Start_IT(hi2s->hdmarx, (uint32_t)&hi2s->Instance->RXDR, (uint32_t)hi2s->pRxBuffPtr, hi2s->RxXferSize);

    /* Check if the I2S Rx requests are already enabled */ 
    if(HAL_IS_BIT_CLR(hi2s->Instance->CFG1, SPI_CFG1_RXDMAEN))
    {
      /* Check if the SPI2S is disabled to edit CFG1 register */
      if ((hi2s->Instance->CR1 & SPI_CR1_SPE) != SPI_CR1_SPE)
      {
        /* Enable Rx DMA Request */
        SET_BIT(hi2s->Instance->CFG1, SPI_CFG1_RXDMAEN);
      }
      else
      {
        /* Disable SPI peripheral */
        __HAL_I2S_DISABLE(hi2s);
    
        /* Enable Rx DMA Request */
        SET_BIT(hi2s->Instance->CFG1, SPI_CFG1_RXDMAEN);

        /* Enable SPI peripheral */
        __HAL_I2S_ENABLE(hi2s);
      }
    }

    /* Set the I2S Tx DMA transfer callbacks as NULL because the communication closing
    is performed in DMA reception callbacks */
    hi2s->hdmatx->XferHalfCpltCallback = NULL;
    hi2s->hdmatx->XferCpltCallback     = NULL;
    hi2s->hdmatx->XferErrorCallback    = NULL;

    /* Enable the Tx DMA Channel */
    HAL_DMA_Start_IT(hi2s->hdmatx, (uint32_t)hi2s->pTxBuffPtr, (uint32_t)&hi2s->Instance->TXDR, hi2s->TxXferSize);

    /* Check if the I2S Tx requests are already enabled */ 
    if(HAL_IS_BIT_CLR(hi2s->Instance->CFG1, SPI_CFG1_TXDMAEN))
    {
      /* Check if the SPI2S is disabled to edit CFG1 register */
      if ((hi2s->Instance->CR1 & SPI_CR1_SPE) != SPI_CR1_SPE)
      {
        /* Enable Tx DMA Request */
        SET_BIT(hi2s->Instance->CFG1, SPI_CFG1_TXDMAEN);
      }
      else
      {
        /* Disable SPI peripheral */
        __HAL_I2S_DISABLE(hi2s);
    
        /* Enable Tx/Rx DMA Request */
        SET_BIT(hi2s->Instance->CFG1, SPI_CFG1_TXDMAEN);

        /* Enable SPI peripheral */
        __HAL_I2S_ENABLE(hi2s);
      }
    }

    /* Process Unlocked */
    __HAL_UNLOCK(hi2s);

    return HAL_OK;
  }
  else
  {
    /* Process Unlocked */
    __HAL_UNLOCK(hi2s);
    return HAL_BUSY;
  }
}

/**
  * @brief  Tx/Rx Transfer half completed callbacks
  * @param  hi2s: pointer to a I2S_HandleTypeDef structure that contains
  *         the configuration information for I2S module
  * @retval None
  */
__weak void HAL_I2SEx_TxRxHalfCpltCallback(I2S_HandleTypeDef *hi2s)
{
  /* Prevent unused argument(s) compilation warning */
  UNUSED(hi2s);

  /* NOTE : This function Should not be modified, when the callback is needed,
            the HAL_I2S_RxHalfCpltCallback could be implemented in the user file
   */
}

/**
  * @brief  Tx/Rx Transfer completed callbacks
  * @param  hi2s: pointer to a I2S_HandleTypeDef structure that contains
  *         the configuration information for I2S module
  * @retval None
  */
__weak void HAL_I2SEx_TxRxCpltCallback(I2S_HandleTypeDef *hi2s)
{
  /* Prevent unused argument(s) compilation warning */
  UNUSED(hi2s);

  /* NOTE : This function Should not be modified, when the callback is needed,
            the HAL_I2S_RxCpltCallback could be implemented in the user file
   */
}

/**
  * @}
  */

/**
  * @}
  */

/** @addtogroup I2SEx_Private_Functions I2S Extended Private Functions
  * @{
  */

/**
  * @brief  DMA I2S transmit receive process complete callback 
  * @param  hdma: pointer to a DMA_HandleTypeDef structure that contains
  *         the configuration information for the specified DMA module.
  * @retval None
  */
static void I2SEx_DMATxRxCplt(DMA_HandleTypeDef *hdma)
{
  I2S_HandleTypeDef* hi2s = (I2S_HandleTypeDef*)((DMA_HandleTypeDef*)hdma)->Parent;

  if(((((DMA_Stream_TypeDef *)hdma->Instance)->CR) & DMA_SxCR_CIRC) == 0U)
  {
    /* Check if the SPI2S is disabled to edit CFG1 register */
    if ((hi2s->Instance->CR1 & SPI_CR1_SPE) != SPI_CR1_SPE)
    {
      /* Disable Tx/Rx DMA Request */
      CLEAR_BIT(hi2s->Instance->CFG1, SPI_CFG1_RXDMAEN | SPI_CFG1_TXDMAEN);
    }
    else
    {
      /* Disable SPI peripheral */
      __HAL_I2S_DISABLE(hi2s);
  
      /* Disable Rx DMA Request */
      CLEAR_BIT(hi2s->Instance->CFG1, SPI_CFG1_RXDMAEN | SPI_CFG1_TXDMAEN);
  
      /* Enable SPI peripheral */
      __HAL_I2S_ENABLE(hi2s);
    }

    hi2s->TxXferCount = 0U;
    hi2s->RxXferCount = 0U;
    hi2s->State = HAL_I2S_STATE_READY;

    if (hi2s->ErrorCode != HAL_I2S_ERROR_NONE)
    {
      HAL_I2S_ErrorCallback(hi2s);
      return;
    }
  }
  HAL_I2SEx_TxRxCpltCallback(hi2s);
}

/**
  * @brief  DMA I2S transmit receive process half complete callback 
  * @param  hdma: pointer to a DMA_HandleTypeDef structure that contains
  *         the configuration information for the specified DMA module.
  * @retval None
  */
static void I2SEx_DMATxRxHalfCplt(DMA_HandleTypeDef *hdma)
{
  I2S_HandleTypeDef* hi2s = (I2S_HandleTypeDef*)((DMA_HandleTypeDef*)hdma)->Parent;

  HAL_I2SEx_TxRxHalfCpltCallback(hi2s);
}

/**
  * @brief  DMA I2S communication error callback
  * @param  hdma: pointer to a DMA_HandleTypeDef structure that contains
  *               the configuration information for the specified DMA module.
  * @retval None
  */
static void I2SEx_TxRxDMAError(DMA_HandleTypeDef *hdma)
{
  I2S_HandleTypeDef* hi2s = (I2S_HandleTypeDef*)((DMA_HandleTypeDef*)hdma)->Parent;

  /* Check if the SPI2S is disabled to edit CFG1 register */
  if ((hi2s->Instance->CR1 & SPI_CR1_SPE) != SPI_CR1_SPE)
  {
    /* Disable Rx and Tx DMA Request */
    CLEAR_BIT(hi2s->Instance->CFG1, (SPI_CFG1_RXDMAEN | SPI_CFG1_TXDMAEN));
  }
  else
  {
    /* Disable SPI peripheral */
    __HAL_I2S_DISABLE(hi2s);

    /* Disable Rx and Tx DMA Request */
    CLEAR_BIT(hi2s->Instance->CFG1, (SPI_CFG1_RXDMAEN | SPI_CFG1_TXDMAEN));

    /* Enable SPI peripheral */
    __HAL_I2S_ENABLE(hi2s);
  }

  hi2s->TxXferCount = 0U;
  hi2s->RxXferCount = 0U;

  hi2s->State= HAL_I2S_STATE_READY;

  /* Set the error code and execute error callback*/
  SET_BIT(hi2s->ErrorCode, HAL_I2S_ERROR_DMA);
  HAL_I2S_ErrorCallback(hi2s);
}

/**
  * @brief  Rx 16-bit handler for Transmit and Receive in Interrupt mode.
  * @param  hi2s: pointer to a I2S_HandleTypeDef structure that contains
  *         the configuration information for I2S module.
  * @retval None
  */
static void I2SEx_2linesRxISR_16BIT(struct __I2S_HandleTypeDef *hi2s)
{
  /* Receive data in 16 Bit mode */
  *((uint16_t *)hi2s->pRxBuffPtr) = hi2s->Instance->RXDR;
  hi2s->pRxBuffPtr += sizeof(uint16_t);
  hi2s->RxXferCount--;

  if (hi2s->RxXferCount == 0U)
  {
    /* Disable RXNE interrupt */
    __HAL_I2S_DISABLE_IT(hi2s, I2S_IT_RXNE);

    if (hi2s->TxXferCount == 0U)
    {
      I2SEx_CloseRxTx_ISR(hi2s);
    }
  }
}

/**
  * @brief  Rx 32-bit handler for Transmit and Receive in Interrupt mode.
  * @param  hi2s: pointer to a I2S_HandleTypeDef structure that contains
  *         the configuration information for I2S module.
  * @retval None
  */
static void I2SEx_2linesRxISR_32BIT(struct __I2S_HandleTypeDef *hi2s)
{
  /* Receive data in 32 Bit mode */
  *((uint32_t *)hi2s->pRxBuffPtr) = hi2s->Instance->RXDR;
  hi2s->pRxBuffPtr += sizeof(uint32_t);
  hi2s->RxXferCount--;

  if (hi2s->RxXferCount == 0U)
  {
    /* Disable RXNE interrupt */
    __HAL_I2S_DISABLE_IT(hi2s, I2S_IT_RXNE);

    if (hi2s->TxXferCount == 0U)
    {
      I2SEx_CloseRxTx_ISR(hi2s);
    }
  }
}

/**
  * @brief  Tx 16-bit handler for Transmit and Receive in Interrupt mode.
  * @param  hi2s: pointer to a I2S_HandleTypeDef structure that contains
  *         the configuration information for I2S module.
  * @retval None
  */
static void I2SEx_2linesTxISR_16BIT(struct __I2S_HandleTypeDef *hi2s)
{
  /* Transmit data in 16 Bit mode */
  *((__IO uint16_t *)&hi2s->Instance->TXDR) = *((uint16_t *)hi2s->pTxBuffPtr);
  hi2s->pTxBuffPtr += sizeof(uint16_t);
  hi2s->TxXferCount--;

  /* Enable CRC Transmission */
  if (hi2s->TxXferCount == 0U)
  {
    /* Disable TXE interrupt */
    __HAL_I2S_DISABLE_IT(hi2s, I2S_IT_TXE);

    if (hi2s->RxXferCount == 0U)
    {
      I2SEx_CloseRxTx_ISR(hi2s);
    }
  }
}

/**
  * @brief  Tx 32-bit handler for Transmit and Receive in Interrupt mode.
  * @param  hi2s: pointer to a I2S_HandleTypeDef structure that contains
  *         the configuration information for I2S module.
  * @retval None
  */
static void I2SEx_2linesTxISR_32BIT(struct __I2S_HandleTypeDef *hi2s)
{
  /* Transmit data in 32 Bit mode */
  *((__IO uint32_t *)&hi2s->Instance->TXDR) = *((uint32_t *)hi2s->pTxBuffPtr);
  hi2s->pTxBuffPtr += sizeof(uint32_t);
  hi2s->TxXferCount--;

  /* Enable CRC Transmission */
  if (hi2s->TxXferCount == 0U)
  {
    /* Disable TXE interrupt */
    __HAL_I2S_DISABLE_IT(hi2s, I2S_IT_TXE);

    if (hi2s->RxXferCount == 0U)
    {
      I2SEx_CloseRxTx_ISR(hi2s);
    }
  }
}

/**
  * @brief  Handle the end of the RXTX transaction.
  * @param  hi2s: pointer to a I2S_HandleTypeDef structure that contains
  *         the configuration information for I2S module.
  * @retval None
  */
static void I2SEx_CloseRxTx_ISR(I2S_HandleTypeDef *hi2s)
{
  /* Disable ERR interrupt */
  __HAL_I2S_DISABLE_IT(hi2s, (I2S_IT_RXNE | I2S_IT_TXE | I2S_IT_ERR));

  if (hi2s->ErrorCode == HAL_I2S_ERROR_NONE)
  {
    if (hi2s->State == HAL_I2S_STATE_BUSY_RX)
    {
      hi2s->State = HAL_I2S_STATE_READY;
      HAL_I2S_RxCpltCallback(hi2s);
    }
    else
    {
      hi2s->State = HAL_I2S_STATE_READY;
      HAL_I2SEx_TxRxCpltCallback(hi2s);
    }
  }
  else
  {
    hi2s->State = HAL_I2S_STATE_READY;
    HAL_I2S_ErrorCallback(hi2s);
  }
}

/**
  * @brief This function handles I2S Communication Timeout.
  * @param  hi2s: pointer to a I2S_HandleTypeDef structure that contains
  *         the configuration information for I2S module
  * @param Flag: Flag checked
  * @param State: Value of the flag expected
  * @param Timeout: Duration of the timeout
  * @retval HAL status
  */
static HAL_StatusTypeDef I2SEx_WaitFlagStateUntilTimeout(I2S_HandleTypeDef *hi2s, uint32_t Flag, uint32_t State, uint32_t Timeout)
{
  uint32_t tickstart = 0U;

  /* Get tick */
  tickstart = HAL_GetTick();

  /* Wait until flag is set */
  if(State == RESET)
  {
    while(__HAL_I2S_GET_FLAG(hi2s, Flag) == RESET)
    {
      if(Timeout != HAL_MAX_DELAY)
      {
        if((Timeout == 0U)||((HAL_GetTick() - tickstart ) > Timeout))
        {
          /* Set the I2S State ready */
          hi2s->State= HAL_I2S_STATE_READY;

          /* Process Unlocked */
          __HAL_UNLOCK(hi2s);

          return HAL_TIMEOUT;
        }
      }
    }
  }
  else
  {
    while(__HAL_I2S_GET_FLAG(hi2s, Flag) != RESET)
    {
      if(Timeout != HAL_MAX_DELAY)
      {
        if((Timeout == 0U)||((HAL_GetTick() - tickstart ) > Timeout))
        {
          /* Set the I2S State ready */
          hi2s->State= HAL_I2S_STATE_READY;

          /* Process Unlocked */
          __HAL_UNLOCK(hi2s);

          return HAL_TIMEOUT;
        }
      }
    }
  }
  return HAL_OK;
}

/**
  * @}
  */
#endif /* HAL_I2S_MODULE_ENABLED */

/**
  * @}
  */
  
/**
  * @}
  */


/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
