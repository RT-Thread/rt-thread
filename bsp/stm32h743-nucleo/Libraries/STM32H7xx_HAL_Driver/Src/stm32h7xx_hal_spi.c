/**
  ******************************************************************************
  * @file    stm32h7xx_hal_spi.c
  * @author  MCD Application Team
  * @version V1.0.0
  * @date    21-April-2017
  * @brief   SPI HAL module driver.
  *          This file provides firmware functions to manage the following
  *          functionalities of the Serial Peripheral Interface (SPI) peripheral:
  *           + Initialization and de-initialization functions
  *           + IO operation functions
  *           + Peripheral Control functions
  *           + Peripheral State functions
  *
  @verbatim
  ==============================================================================
                        ##### How to use this driver #####
  ==============================================================================
    [..]
      The SPI HAL driver can be used as follows:

      (#) Declare a SPI_HandleTypeDef handle structure, for example:
          SPI_HandleTypeDef  hspi;

      (#)Initialize the SPI low level resources by implementing the HAL_SPI_MspInit() API:
          (##) Enable the SPIx interface clock
          (##) SPI pins configuration
              (+++) Enable the clock for the SPI GPIOs
              (+++) Configure these SPI pins as alternate function push-pull
          (##) NVIC configuration if you need to use interrupt process
              (+++) Configure the SPIx interrupt priority
              (+++) Enable the NVIC SPI IRQ handle
          (##) DMA Configuration if you need to use DMA process
              (+++) Declare a DMA_HandleTypeDef handle structure for the transmit or receive Stream/Channel
              (+++) Enable the DMAx clock
              (+++) Configure the DMA handle parameters
              (+++) Configure the DMA Tx or Rx Stream/Channel
              (+++) Associate the initialized hdma_tx handle to the hspi DMA Tx or Rx handle
              (+++) Configure the priority and enable the NVIC for the transfer complete interrupt on the DMA Tx or Rx Stream/Channel

      (#) Program the Mode, BidirectionalMode , Data size, Baudrate Prescaler, NSS
          management, Clock polarity and phase, FirstBit and CRC configuration in the hspi Init structure.

      (#) Initialize the SPI registers by calling the HAL_SPI_Init() API:
          (++) This API configures also the low level Hardware GPIO, CLOCK, CORTEX...etc)
              by calling the customized HAL_SPI_MspInit() API.

    [..]
      Circular mode restriction:
      (+) The DMA circular mode cannot be used when the SPI is configured in these modes:
          (++) Master 2Lines RxOnly
          (++) Master 1Line Rx
      (+) The CRC feature is not managed when the DMA circular mode is enabled
      (+) When the SPI DMA Pause/Stop features are used, we must use the following APIs
          the HAL_SPI_DMAPause()/ HAL_SPI_DMAStop() only under the SPI callbacks

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

/** @defgroup SPI SPI
  * @brief SPI HAL module driver
  * @{
  */
#ifdef HAL_SPI_MODULE_ENABLED

/* Private typedef -----------------------------------------------------------*/
/* Private defines -----------------------------------------------------------*/
/** @defgroup SPI_Private_Constants SPI Private Constants
  * @{
  */
#define SPI_DEFAULT_TIMEOUT 100U
/**
  * @}
  */

/* Private macros ------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
/** @defgroup SPI_Private_Functions SPI Private Functions
  * @{
  */
static void SPI_DMATransmitCplt(DMA_HandleTypeDef *hdma);
static void SPI_DMAReceiveCplt(DMA_HandleTypeDef *hdma);
static void SPI_DMATransmitReceiveCplt(DMA_HandleTypeDef *hdma);
static void SPI_DMAHalfTransmitCplt(DMA_HandleTypeDef *hdma);
static void SPI_DMAHalfReceiveCplt(DMA_HandleTypeDef *hdma);
static void SPI_DMAHalfTransmitReceiveCplt(DMA_HandleTypeDef *hdma);
static void SPI_DMAError(DMA_HandleTypeDef *hdma);
static void SPI_DMAAbortOnError(DMA_HandleTypeDef *hdma);
static void SPI_DMATxAbortCallback(DMA_HandleTypeDef *hdma);
static void SPI_DMARxAbortCallback(DMA_HandleTypeDef *hdma);
static HAL_StatusTypeDef SPI_WaitFlagStateUntilTimeout(SPI_HandleTypeDef *hspi, uint32_t Flag, uint32_t State,
                                                       uint32_t Timeout, uint32_t Tickstart);
static HAL_StatusTypeDef SPI_WaitFifoStateUntilTimeout(SPI_HandleTypeDef *hspi, uint32_t Fifo, uint32_t State,
                                                       uint32_t Timeout, uint32_t Tickstart);
static void SPI_TxISR_8BIT(struct __SPI_HandleTypeDef *hspi);
static void SPI_TxISR_16BIT(struct __SPI_HandleTypeDef *hspi);
static void SPI_TxISR_32BIT(struct __SPI_HandleTypeDef *hspi);
static void SPI_RxISR_8BIT(struct __SPI_HandleTypeDef *hspi);
static void SPI_RxISR_16BIT(struct __SPI_HandleTypeDef *hspi);
static void SPI_RxISR_32BIT(struct __SPI_HandleTypeDef *hspi);
static void SPI_2linesRxISR_8BIT(struct __SPI_HandleTypeDef *hspi);
static void SPI_2linesTxISR_8BIT(struct __SPI_HandleTypeDef *hspi);
static void SPI_2linesTxISR_16BIT(struct __SPI_HandleTypeDef *hspi);
static void SPI_2linesTxISR_32BIT(struct __SPI_HandleTypeDef *hspi);
static void SPI_2linesRxISR_16BIT(struct __SPI_HandleTypeDef *hspi);
static void SPI_2linesRxISR_32BIT(struct __SPI_HandleTypeDef *hspi);
static void SPI_AbortRx_ISR(SPI_HandleTypeDef *hspi);
static void SPI_AbortTx_ISR(SPI_HandleTypeDef *hspi);
static void SPI_CloseRxTx_ISR(SPI_HandleTypeDef *hspi);
static void SPI_CloseRx_ISR(SPI_HandleTypeDef *hspi);
static void SPI_CloseTx_ISR(SPI_HandleTypeDef *hspi);
static HAL_StatusTypeDef SPI_EndRxTransaction(SPI_HandleTypeDef *hspi, uint32_t Timeout, uint32_t Tickstart);
static HAL_StatusTypeDef SPI_EndRxTxTransaction(SPI_HandleTypeDef *hspi, uint32_t Timeout, uint32_t Tickstart);
/**
  * @}
  */

/* Exported functions --------------------------------------------------------*/
/** @defgroup SPI_Exported_Functions SPI Exported Functions
  * @{
  */

/** @defgroup SPI_Exported_Functions_Group1 Initialization and de-initialization functions
 *  @brief    Initialization and Configuration functions
 *
@verbatim
 ===============================================================================
              ##### Initialization and de-initialization functions #####
 ===============================================================================
    [..]  This subsection provides a set of functions allowing to initialize and
          de-initialize the SPIx peripheral:

      (+) User must implement HAL_SPI_MspInit() function in which he configures
          all related peripherals resources (CLOCK, GPIO, DMA, IT and NVIC ).

      (+) Call the function HAL_SPI_Init() to configure the selected device with
          the selected configuration:
        (++) Mode
        (++) Direction
        (++) Data Size
        (++) Clock Polarity and Phase
        (++) NSS Management
        (++) BaudRate Prescaler
        (++) FirstBit
        (++) TIMode
        (++) CRC Calculation
        (++) CRC Polynomial if CRC enabled
        (++) CRC Length, used only with Data8 and Data16
        (++) FIFO reception threshold
        (++) FIFO transmission threshold

      (+) Call the function HAL_SPI_DeInit() to restore the default configuration
          of the selected SPIx peripheral.

@endverbatim
  * @{
  */

/**
  * @brief  Initialize the SPI according to the specified parameters
  *         in the SPI_InitTypeDef and initialize the associated handle.
  * @param  hspi: pointer to a SPI_HandleTypeDef structure that contains
  *               the configuration information for SPI module.
  * @retval HAL status
  */
HAL_StatusTypeDef HAL_SPI_Init(SPI_HandleTypeDef *hspi)
{
  /* Check the SPI handle allocation */
  if (hspi == NULL)
  {
    return HAL_ERROR;
  }

  /* Check the parameters */
  assert_param(IS_SPI_ALL_INSTANCE(hspi->Instance));
  assert_param(IS_SPI_MODE(hspi->Init.Mode));
  assert_param(IS_SPI_DIRECTION(hspi->Init.Direction));
  assert_param(IS_SPI_DATASIZE(hspi->Init.DataSize));
  assert_param(IS_SPI_FIFOTHRESHOLD(hspi->Init.FifoThreshold));
  assert_param(IS_SPI_NSS(hspi->Init.NSS));
  assert_param(IS_SPI_NSSP(hspi->Init.NSSPMode));
  assert_param(IS_SPI_BAUDRATE_PRESCALER(hspi->Init.BaudRatePrescaler));
  assert_param(IS_SPI_FIRST_BIT(hspi->Init.FirstBit));
  assert_param(IS_SPI_TIMODE(hspi->Init.TIMode));
  if (hspi->Init.TIMode == SPI_TIMODE_DISABLE)
  {
    assert_param(IS_SPI_CPOL(hspi->Init.CLKPolarity));
    assert_param(IS_SPI_CPHA(hspi->Init.CLKPhase));
  }
#ifdef USE_SPI_CRC
  assert_param(IS_SPI_CRC_CALCULATION(hspi->Init.CRCCalculation));
  if (hspi->Init.CRCCalculation == SPI_CRCCALCULATION_ENABLE)
  {
    assert_param(IS_SPI_CRC_POLYNOMIAL(hspi->Init.CRCPolynomial));
    assert_param(IS_SPI_CRC_LENGTH(hspi->Init.CRCLength));
    assert_param(IS_SPI_CRC_INITIALIZATION_PATTERN(hspi->Init.TxCRCInitializationPattern));
    assert_param(IS_SPI_CRC_INITIALIZATION_PATTERN(hspi->Init.RxCRCInitializationPattern));
  }
#else
  hspi->Init.CRCCalculation = SPI_CRCCALCULATION_DISABLE;
#endif /* USE_SPI_CRC */
  
  /* Verify that the SPI instance is supporting Data Size higher than 16bits */
  if ((!IS_SPI_HIGHEND_INSTANCE(hspi->Instance)) && (hspi->Init.DataSize > SPI_DATASIZE_16BIT))
  {
    return HAL_ERROR;
  }

#ifdef USE_SPI_CRC
  /* Verify that the SPI instance is supporting CRC Length higher than 16bits */
  if ((!IS_SPI_HIGHEND_INSTANCE(hspi->Instance)) && (hspi->Init.CRCLength > SPI_CRC_LENGTH_16BIT))
  {
    return HAL_ERROR;
  }

  /* CRC calculation is valid only for 16Bit and 32 Bit */
  if ((hspi->Init.DataSize != SPI_DATASIZE_16BIT) && (hspi->Init.DataSize != SPI_DATASIZE_32BIT))
  {
    /* CRC must be disabled */
    hspi->Init.CRCCalculation = SPI_CRCCALCULATION_DISABLE;
  }

  /* Align the CRC Length on the data size */
  if (hspi->Init.CRCLength == SPI_CRC_LENGTH_DATASIZE)
  {
    /* CRC Length aligned on the data size : value set by default */
    if (hspi->Init.DataSize > SPI_DATASIZE_16BIT)
    {
      hspi->Init.CRCLength = SPI_CRC_LENGTH_32BIT;
    }
    else
    {
      hspi->Init.CRCLength = SPI_CRC_LENGTH_16BIT;
    }
  }
#endif /* USE_SPI_CRC */

  if (hspi->State == HAL_SPI_STATE_RESET)
  {
    /* Allocate lock resource and initialize it */
    hspi->Lock = HAL_UNLOCKED;

    /* Init the low level hardware : GPIO, CLOCK, NVIC... */
    HAL_SPI_MspInit(hspi);
  }

  hspi->State = HAL_SPI_STATE_BUSY;

  /* Disable the selected SPI peripheral */
  __HAL_SPI_DISABLE(hspi);

  /* Unlock the AF configuration to edit CFG2 register */
  HAL_SPIEx_DisableLockConfiguration(hspi);

  /*----------------------- SPIx CR1 & CR2 Configuration ---------------------*/
  /* Configure : SPI Mode, Communication Mode, Clock polarity and phase, NSS management,
  Communication speed, First bit, CRC calculation state, CRC Length */
 
  if ((hspi->Init.NSS == SPI_NSS_SOFT) && (hspi->Init.Mode == SPI_MODE_MASTER) && (hspi->Init.NSSPolarity == SPI_NSS_POLARITY_LOW))
  {
    SET_BIT(hspi->Instance->CR1, SPI_CR1_SSI);
  }

  /* SPIx CFG1 Configuration */
  WRITE_REG(hspi->Instance->CFG1, (hspi->Init.BaudRatePrescaler | hspi->Init.CRCCalculation | hspi->Init.CRCLength |
                                   hspi->Init.FifoThreshold     | hspi->Init.DataSize));

  /* SPIx CFG2 Configuration */
  WRITE_REG(hspi->Instance->CFG2, (hspi->Init.NSSPMode     | hspi->Init.TIMode           | hspi->Init.NSSPolarity             |
                                   hspi->Init.NSS          | hspi->Init.CLKPolarity      | hspi->Init.CLKPhase                |
                                   hspi->Init.FirstBit     | hspi->Init.Mode             | hspi->Init.MasterInterDataIdleness |
                                   hspi->Init.Direction    | hspi->Init.MasterSSIdleness | hspi->Init.IOSwap));

#ifdef USE_SPI_CRC
  /*---------------------------- SPIx CRCPOLY Configuration ------------------*/
  /* Configure : CRC Polynomial */
  if (hspi->Init.CRCCalculation == SPI_CRCCALCULATION_ENABLE)
  {
    /* Initialize TXCRC Pattern Initial Value */
    if (hspi->Init.TxCRCInitializationPattern == SPI_CRC_INITIALIZATION_ALL_ONE_PATTERN)
      SET_BIT(hspi->Instance->CR1, SPI_CR1_TCRCINI);
    else
      CLEAR_BIT(hspi->Instance->CR1, SPI_CR1_TCRCINI);
    
    /* Initialize RXCRC Pattern Initial Value */
    if (hspi->Init.RxCRCInitializationPattern == SPI_CRC_INITIALIZATION_ALL_ONE_PATTERN)
      SET_BIT(hspi->Instance->CR1, SPI_CR1_RCRCINI);
    else
      CLEAR_BIT(hspi->Instance->CR1, SPI_CR1_RCRCINI);
    
    /* Write CRC polynomial in SPI Register */
    if (  ((!IS_SPI_HIGHEND_INSTANCE(hspi->Instance)) && (hspi->Init.CRCLength == SPI_CRC_LENGTH_16BIT)) || \
          ((IS_SPI_HIGHEND_INSTANCE(hspi->Instance))  && (hspi->Init.CRCLength == SPI_CRC_LENGTH_32BIT)) )
    {
      SET_BIT(hspi->Instance->CR1, SPI_CR1_CRC33_17);
      WRITE_REG(hspi->Instance->CRCPOLY, hspi->Init.CRCPolynomial);
    }
  }
#endif /* USE_SPI_CRC */

  /* Insure that Underrun configuration is managed only by Salve */
  if (hspi->Init.Mode == SPI_MODE_SLAVE)
  {
    /* Set Default Underrun configuration */
    MODIFY_REG(hspi->Instance->CFG1, SPI_CFG1_UDRDET, SPI_CFG1_UDRDET_0);
    MODIFY_REG(hspi->Instance->CFG1, SPI_CFG1_UDRCFG, SPI_CFG1_UDRCFG_1);
  }

#if defined(SPI_I2SCFGR_I2SMOD)
  /* Activate the SPI mode (Make sure that I2SMOD bit in I2SCFGR register is reset) */
  CLEAR_BIT(hspi->Instance->I2SCFGR, SPI_I2SCFGR_I2SMOD);
#endif /* SPI_I2SCFGR_I2SMOD */

  /* Insure that AFCNTR is managed only by Master */
  if ((hspi->Init.Mode & SPI_MODE_MASTER) == SPI_MODE_MASTER)
  {
    /* Alternate function GPIOs control */
    MODIFY_REG(hspi->Instance->CFG2, SPI_CFG2_AFCNTR, (hspi->Init.MasterKeepIOState));
  }

  hspi->ErrorCode = HAL_SPI_ERROR_NONE;
  hspi->State     = HAL_SPI_STATE_READY;

  return HAL_OK;
}

/**
  * @brief  De-Initialize the SPI peripheral.
  * @param  hspi: pointer to a SPI_HandleTypeDef structure that contains
  *               the configuration information for SPI module.
  * @retval HAL status
  */
HAL_StatusTypeDef HAL_SPI_DeInit(SPI_HandleTypeDef *hspi)
{
  /* Check the SPI handle allocation */
  if (hspi == NULL)
  {
    return HAL_ERROR;
  }

  /* Check SPI Instance parameter */
  assert_param(IS_SPI_ALL_INSTANCE(hspi->Instance));

  hspi->State = HAL_SPI_STATE_BUSY;

  /* Disable the SPI Peripheral Clock */
  __HAL_SPI_DISABLE(hspi);

  /* DeInit the low level hardware: GPIO, CLOCK, NVIC... */
  HAL_SPI_MspDeInit(hspi);

  hspi->ErrorCode = HAL_SPI_ERROR_NONE;
  hspi->State = HAL_SPI_STATE_RESET;

  /* Release Lock */
  __HAL_UNLOCK(hspi);

  return HAL_OK;
}

/**
  * @brief  Initialize the SPI MSP.
  * @param  hspi: pointer to a SPI_HandleTypeDef structure that contains
  *               the configuration information for SPI module.
  * @retval None
  */
__weak void HAL_SPI_MspInit(SPI_HandleTypeDef *hspi)
{
  /* Prevent unused argument(s) compilation warning */
  UNUSED(hspi);

  /* NOTE : This function should not be modified, when the callback is needed,
            the HAL_SPI_MspInit should be implemented in the user file
   */
}

/**
  * @brief  De-Initialize the SPI MSP.
  * @param  hspi: pointer to a SPI_HandleTypeDef structure that contains
  *               the configuration information for SPI module.
  * @retval None
  */
__weak void HAL_SPI_MspDeInit(SPI_HandleTypeDef *hspi)
{
  /* Prevent unused argument(s) compilation warning */
  UNUSED(hspi);

  /* NOTE : This function should not be modified, when the callback is needed,
            the HAL_SPI_MspDeInit should be implemented in the user file
   */
}

/**
  * @}
  */

/** @defgroup SPI_Exported_Functions_Group2 IO operation functions
 *  @brief   Data transfers functions
 *
@verbatim
  ==============================================================================
                      ##### IO operation functions #####
 ===============================================================================
 [..]
    This subsection provides a set of functions allowing to manage the SPI
    data transfers.

    [..] The SPI supports master and slave mode :

    (#) There are two modes of transfer:
       (##) Blocking mode: The communication is performed in polling mode.
            The HAL status of all data processing is returned by the same function
            after finishing transfer.
       (##) No-Blocking mode: The communication is performed using Interrupts
            or DMA, These APIs return the HAL status.
            The end of the data processing will be indicated through the
            dedicated SPI IRQ when using Interrupt mode or the DMA IRQ when
            using DMA mode.
            The HAL_SPI_TxCpltCallback(), HAL_SPI_RxCpltCallback() and HAL_SPI_TxRxCpltCallback() user callbacks
            will be executed respectively at the end of the transmit or Receive process
            The HAL_SPI_ErrorCallback()user callback will be executed when a communication error is detected

    (#) APIs provided for these 2 transfer modes (Blocking mode or Non blocking mode using either Interrupt or DMA)
        exist for 1Line (simplex) and 2Lines (full duplex) modes.

@endverbatim
  * @{
  */

/**
  * @brief  Transmit an amount of data in blocking mode.
  * @param  hspi: pointer to a SPI_HandleTypeDef structure that contains
  *               the configuration information for SPI module.
  * @param  pData: pointer to data buffer
  * @param  Size: amount of data to be sent
  * @param  Timeout: Timeout duration
  * @retval HAL status
  */
HAL_StatusTypeDef HAL_SPI_Transmit(SPI_HandleTypeDef *hspi, uint8_t *pData, uint16_t Size, uint32_t Timeout)
{
  uint32_t tickstart = 0U;
  HAL_StatusTypeDef errorcode = HAL_OK;

  /* Check Direction parameter */
  assert_param(IS_SPI_DIRECTION_2LINES_OR_1LINE_2LINES_TXONLY(hspi->Init.Direction));

  /* Process Locked */
  __HAL_LOCK(hspi);

  /* Init tickstart for timeout management*/
  tickstart = HAL_GetTick();

  if (hspi->State != HAL_SPI_STATE_READY)
  {
    errorcode = HAL_BUSY;
    __HAL_UNLOCK(hspi);
    return errorcode;
  }

  if ((pData == NULL) || (Size == 0U))
  {
    errorcode = HAL_ERROR;
    __HAL_UNLOCK(hspi);
    return errorcode;
  }

  /* Set the transaction information */
  hspi->State       = HAL_SPI_STATE_BUSY_TX;
  hspi->ErrorCode   = HAL_SPI_ERROR_NONE;
  hspi->pTxBuffPtr  = (uint8_t *)pData;
  hspi->TxXferSize  = Size;
  hspi->TxXferCount = Size;

  /*Init field not used in handle to zero */
  hspi->pRxBuffPtr  = NULL;
  hspi->RxXferSize  = 0U;
  hspi->RxXferCount = 0U;
  hspi->TxISR       = NULL;
  hspi->RxISR       = NULL;

  /* Configure communication direction : 1Line */
  if (hspi->Init.Direction == SPI_DIRECTION_1LINE)
  {
    SPI_1LINE_TX(hspi);
  }

  /* Set the number if data at current transfer */
  MODIFY_REG(hspi->Instance->CR2, SPI_CR2_TSIZE, Size);

  /* Check if the SPI is already enabled */
  if ((hspi->Instance->CR1 & SPI_CR1_SPE) != SPI_CR1_SPE)
  {
    /* Enable SPI peripheral */
    __HAL_SPI_ENABLE(hspi);
  }
  else
  {
    if (__HAL_SPI_GET_FLAG(hspi, SPI_FLAG_UDR))
    {
      *((__IO uint8_t *)&hspi->Instance->TXDR) = 0x01U;
      __HAL_SPI_CLEAR_UDRFLAG(hspi);
      __HAL_SPI_DISABLE(hspi);
      __HAL_SPI_ENABLE(hspi);
    }
  }

  if (hspi->Init.Mode == SPI_MODE_MASTER)
  {
    /* Master transfer start */
    SET_BIT(hspi->Instance->CR1, SPI_CR1_CSTART);
  }

  /* Transmit data in 32 Bit mode */
  if (hspi->Init.DataSize > SPI_DATASIZE_16BIT)
  {
    /* Transmit data in 32 Bit mode */
    while (hspi->TxXferCount > 0U)
    {
      /* Wait until TXE flag is set to send data */
      if (__HAL_SPI_GET_FLAG(hspi, SPI_FLAG_TXE))
      {
        *((__IO uint32_t *)&hspi->Instance->TXDR) = *((uint32_t *)hspi->pTxBuffPtr);
        hspi->pTxBuffPtr += sizeof(uint32_t);
        hspi->TxXferCount--;
      }
      else
      {
        /* Timeout management */
        if ((Timeout == 0U) || ((Timeout != HAL_MAX_DELAY) && ((HAL_GetTick() - tickstart) >=  Timeout)))
        {
          /* Set the error code and execute error callback*/
          SET_BIT(hspi->ErrorCode, HAL_SPI_ERROR_TIMEOUT);
          HAL_SPI_ErrorCallback(hspi);

          /* Set the SPI State ready */
          hspi->State = HAL_SPI_STATE_READY;

          /* Process Unlocked */
          __HAL_UNLOCK(hspi);
          return HAL_ERROR;
        }
      }
    }
  }
  /* Transmit data in 16 Bit mode */
  else if (hspi->Init.DataSize > SPI_DATASIZE_8BIT)
  {
    if (IS_SPI_HIGHEND_INSTANCE(hspi->Instance))
    {
      /* Transmit data in 16 Bit mode */
      while (hspi->TxXferCount > 0U)
      {
        /* Wait until TXE flag is set to send data */
        if (__HAL_SPI_GET_FLAG(hspi, SPI_FLAG_TXE))
        {
          if ( (hspi->TxXferCount > 1U) && (hspi->Init.FifoThreshold > SPI_FIFO_THRESHOLD_01DATA))
          {
            *((__IO uint32_t *)&hspi->Instance->TXDR) = *((uint32_t *)hspi->pTxBuffPtr);
            hspi->pTxBuffPtr += sizeof(uint32_t);
            hspi->TxXferCount-=2;
          }
          else
          {
            *((__IO uint16_t *)&hspi->Instance->TXDR) = *((uint16_t *)hspi->pTxBuffPtr);
            hspi->pTxBuffPtr += sizeof(uint16_t);
            hspi->TxXferCount--;
          }
        }
        else
        {
          /* Timeout management */
          if ((Timeout == 0U) || ((Timeout != HAL_MAX_DELAY) && ((HAL_GetTick() - tickstart) >=  Timeout)))
          {
            /* Set the error code and execute error callback*/
            SET_BIT(hspi->ErrorCode, HAL_SPI_ERROR_TIMEOUT);
            HAL_SPI_ErrorCallback(hspi);
  
            /* Set the SPI State ready */
            hspi->State = HAL_SPI_STATE_READY;
  
            /* Process Unlocked */
            __HAL_UNLOCK(hspi);
            return HAL_ERROR;
          }
        }
      }
    }
  }
  /* Transmit data in 8 Bit mode */
  else
  {
    if (IS_SPI_HIGHEND_INSTANCE(hspi->Instance))
    {
      while (hspi->TxXferCount > 0U)
      {
        /* Wait until TXE flag is set to send data */
        if (__HAL_SPI_GET_FLAG(hspi, SPI_FLAG_TXE))
        {
          if ((hspi->TxXferCount > 3U) && (hspi->Init.FifoThreshold > SPI_FIFO_THRESHOLD_03DATA))
          {
            *((__IO uint32_t *)&hspi->Instance->TXDR) = *((uint32_t *)hspi->pTxBuffPtr);
            hspi->pTxBuffPtr += sizeof(uint32_t);
            hspi->TxXferCount-=4;
          }
          else if ((hspi->TxXferCount > 1U) && (hspi->Init.FifoThreshold > SPI_FIFO_THRESHOLD_01DATA))
          {
            *((__IO uint16_t *)&hspi->Instance->TXDR) = *((uint16_t *)hspi->pTxBuffPtr);
            hspi->pTxBuffPtr += sizeof(uint16_t);
            hspi->TxXferCount-=2;
          }
          else
          {
            *((__IO uint8_t *)&hspi->Instance->TXDR) = *((uint8_t *)hspi->pTxBuffPtr);
            hspi->pTxBuffPtr += sizeof(uint8_t);
            hspi->TxXferCount--;
          }
        }
        else
        {
          /* Timeout management */
          if ((Timeout == 0U) || ((Timeout != HAL_MAX_DELAY) && ((HAL_GetTick() - tickstart) >=  Timeout)))
          {
            /* Set the error code and execute error callback*/
            SET_BIT(hspi->ErrorCode, HAL_SPI_ERROR_TIMEOUT);
            HAL_SPI_ErrorCallback(hspi);
  
            /* Set the SPI State ready */
            hspi->State = HAL_SPI_STATE_READY;
  
            /* Process Unlocked */
            __HAL_UNLOCK(hspi);
            return HAL_ERROR;
          }
        }
      }
    }
  }

  /* Check the end of the transaction */
  if (SPI_EndRxTxTransaction(hspi, Timeout, tickstart) != HAL_OK)
  {
    hspi->ErrorCode = HAL_SPI_ERROR_FLAG;
  }

  /* Clear overrun flag in 2 Lines communication mode because received data is not read */
  if (hspi->Init.Direction == SPI_DIRECTION_2LINES)
  {
    __HAL_SPI_CLEAR_OVRFLAG(hspi);
  }

  if (hspi->ErrorCode != HAL_SPI_ERROR_NONE)
  {
    errorcode = HAL_ERROR;
  }

  hspi->State = HAL_SPI_STATE_READY;
  /* Process Unlocked */
  __HAL_UNLOCK(hspi);
  return errorcode;
}

/**
  * @brief  Receive an amount of data in blocking mode.
  * @param  hspi: pointer to a SPI_HandleTypeDef structure that contains
  *               the configuration information for SPI module.
  * @param  pData: pointer to data buffer
  * @param  Size: amount of data to be received
  * @param  Timeout: Timeout duration
  * @retval HAL status
  */
HAL_StatusTypeDef HAL_SPI_Receive(SPI_HandleTypeDef *hspi, uint8_t *pData, uint16_t Size, uint32_t Timeout)
{
  uint32_t tickstart = 0U;
  HAL_StatusTypeDef errorcode = HAL_OK;

  /* Check Direction parameter */
  assert_param(IS_SPI_DIRECTION_2LINES_OR_1LINE_2LINES_RXONLY(hspi->Init.Direction));

  if ((hspi->Init.Mode == SPI_MODE_MASTER) && (hspi->Init.Direction == SPI_DIRECTION_2LINES))
  {
    hspi->State = HAL_SPI_STATE_BUSY_RX;
    /* Call transmit-receive function to send Dummy data on Tx line and generate clock on CLK line */
    return HAL_SPI_TransmitReceive(hspi, pData, pData, Size, Timeout);
  }

  /* Process Locked */
  __HAL_LOCK(hspi);

  /* Init tickstart for timeout management*/
  tickstart = HAL_GetTick();

  if (hspi->State != HAL_SPI_STATE_READY)
  {
    errorcode = HAL_BUSY;
    __HAL_UNLOCK(hspi);
    return errorcode;
  }

  if ((pData == NULL) || (Size == 0U))
  {
    errorcode = HAL_ERROR;
    __HAL_UNLOCK(hspi);
    return errorcode;
  }

  /* Set the transaction information */
  hspi->State       = HAL_SPI_STATE_BUSY_RX;
  hspi->ErrorCode   = HAL_SPI_ERROR_NONE;
  hspi->pRxBuffPtr  = (uint8_t *)pData;
  hspi->RxXferSize  = Size;
  hspi->RxXferCount = Size;

  /*Init field not used in handle to zero */
  hspi->pTxBuffPtr  = NULL;
  hspi->TxXferSize  = 0U;
  hspi->TxXferCount = 0U;
  hspi->RxISR       = NULL;
  hspi->TxISR       = NULL;

  /* Configure communication direction: 1Line */
  if (hspi->Init.Direction == SPI_DIRECTION_1LINE)
  {
    SPI_1LINE_RX(hspi);
  }

  /* Set the number if data at current transfer */
  MODIFY_REG(hspi->Instance->CR2, SPI_CR2_TSIZE, Size);

  /* Check if the SPI is already enabled */
  if ((hspi->Instance->CR1 & SPI_CR1_SPE) != SPI_CR1_SPE)
  {
    /* Enable SPI peripheral */
    __HAL_SPI_ENABLE(hspi);
  }

  if (hspi->Init.Mode == SPI_MODE_MASTER)
  {
    /* Master transfer start */
    SET_BIT(hspi->Instance->CR1, SPI_CR1_CSTART);
  }

  /* Receive data in 32 Bit mode */
  if (hspi->Init.DataSize > SPI_DATASIZE_16BIT)
  {
    /* Transfer loop */
    while (hspi->RxXferCount > 0U)
    {
      /* Check the RXNE flag */
      if (__HAL_SPI_GET_FLAG(hspi, SPI_FLAG_RXNE))
      {
        *((uint32_t *)hspi->pRxBuffPtr) = *((__IO uint32_t *)&hspi->Instance->RXDR);
        hspi->pRxBuffPtr += sizeof(uint32_t);
        hspi->RxXferCount--;
      }
      else
      {
        /* Timeout management */
        if ((Timeout == 0U) || ((Timeout != HAL_MAX_DELAY) && ((HAL_GetTick() - tickstart) >=  Timeout)))
        {
          /* Set the error code and execute error callback*/
          SET_BIT(hspi->ErrorCode, HAL_SPI_ERROR_TIMEOUT);
          HAL_SPI_ErrorCallback(hspi);

          /* Set the SPI State ready */
          hspi->State = HAL_SPI_STATE_READY;

          /* Process Unlocked */
          __HAL_UNLOCK(hspi);
          return HAL_ERROR;
        }
      }
    }
  }
  /* Receive data in 16 Bit mode */
  else if (hspi->Init.DataSize > SPI_DATASIZE_8BIT)
  {
    if (IS_SPI_HIGHEND_INSTANCE(hspi->Instance))
    {
      /* Transfer loop */
      while (hspi->RxXferCount > 0U)
      {
        /* Check the RXNE flag */
        if (__HAL_SPI_GET_FLAG(hspi, SPI_FLAG_RXNE))
        {
          if (hspi->Instance->SR & SPI_FLAG_RXWNE)
          {
            *((uint32_t *)hspi->pRxBuffPtr) = *((__IO uint32_t *)&hspi->Instance->RXDR);
            hspi->pRxBuffPtr += sizeof(uint32_t);
            hspi->RxXferCount-=2;
          }
          else
          {
            *((uint16_t *)hspi->pRxBuffPtr) = *((__IO uint16_t *)&hspi->Instance->RXDR);
            hspi->pRxBuffPtr += sizeof(uint16_t);
            hspi->RxXferCount--;
          }
        }
        else
        {
          /* Timeout management */
          if ((Timeout == 0U) || ((Timeout != HAL_MAX_DELAY) && ((HAL_GetTick() - tickstart) >=  Timeout)))
          {
            /* Set the error code and execute error callback*/
            SET_BIT(hspi->ErrorCode, HAL_SPI_ERROR_TIMEOUT);
            HAL_SPI_ErrorCallback(hspi);
  
            /* Set the SPI State ready */
            hspi->State = HAL_SPI_STATE_READY;
  
            /* Process Unlocked */
            __HAL_UNLOCK(hspi);
            return HAL_ERROR;
          }
        }
      }
    }
  }
  /* Receive data in 8 Bit mode */
  else
  {
    
    if (IS_SPI_HIGHEND_INSTANCE(hspi->Instance))
    {
      /* Transfer loop */
      while (hspi->RxXferCount > 0U)
      {
        /* Check the RXNE flag */
        if (__HAL_SPI_GET_FLAG(hspi, SPI_FLAG_RXNE))
        {
          if (hspi->Instance->SR & SPI_FLAG_RXWNE)
          {
            *((uint32_t *)hspi->pRxBuffPtr) = *((__IO uint32_t *)&hspi->Instance->RXDR);
            hspi->pRxBuffPtr += sizeof(uint32_t);
            hspi->RxXferCount-=4;
          }
          else if ((hspi->Instance->SR & SPI_FLAG_FRLVL) > SPI_FRLVL_QUARTER_FULL)
          {
            *((uint16_t *)hspi->pRxBuffPtr) = *((__IO uint16_t *)&hspi->Instance->RXDR);
            hspi->pRxBuffPtr += sizeof(uint16_t);
            hspi->RxXferCount-=2;
          }
          else
          {
            (*hspi->pRxBuffPtr) = *((__IO uint8_t *)&hspi->Instance->RXDR);
            hspi->pRxBuffPtr += sizeof(uint8_t);
            hspi->RxXferCount--;
          }
        }
        else
        {
          /* Timeout management */
          if ((Timeout == 0U) || ((Timeout != HAL_MAX_DELAY) && ((HAL_GetTick() - tickstart) >=  Timeout)))
            {
            /* Set the error code and execute error callback*/
            SET_BIT(hspi->ErrorCode, HAL_SPI_ERROR_TIMEOUT);
            HAL_SPI_ErrorCallback(hspi);
  
            /* Set the SPI State ready */
            hspi->State = HAL_SPI_STATE_READY;
  
            /* Process Unlocked */
            __HAL_UNLOCK(hspi);
            return HAL_ERROR;
          }
        }
      }
    }
  }

  /* Check the end of the transaction */
  if (SPI_EndRxTransaction(hspi, Timeout, tickstart) != HAL_OK)
  {
    hspi->ErrorCode = HAL_SPI_ERROR_FLAG;
  }

#ifdef USE_SPI_CRC
  /* Check if CRC error occurred */
  if (__HAL_SPI_GET_FLAG(hspi, SPI_FLAG_CRCERR))
  {
    SET_BIT(hspi->ErrorCode, HAL_SPI_ERROR_CRC);
    __HAL_SPI_CLEAR_CRCERRFLAG(hspi);
  }
#endif /* USE_SPI_CRC */

  if (hspi->ErrorCode != HAL_SPI_ERROR_NONE)
  {
    errorcode = HAL_ERROR;
  }

  hspi->State = HAL_SPI_STATE_READY;
  __HAL_UNLOCK(hspi);
  return errorcode;
}

/**
  * @brief  Transmit and Receive an amount of data in blocking mode.
  * @param  hspi: pointer to a SPI_HandleTypeDef structure that contains
  *               the configuration information for SPI module.
  * @param  pTxData: pointer to transmission data buffer
  * @param  pRxData: pointer to reception data buffer
  * @param  Size: amount of data to be sent and received
  * @param  Timeout: Timeout duration
  * @retval HAL status
  */
HAL_StatusTypeDef HAL_SPI_TransmitReceive(SPI_HandleTypeDef *hspi, uint8_t *pTxData, uint8_t *pRxData, uint16_t Size,
                                          uint32_t Timeout)
{
  uint32_t tickstart = 0U;
  HAL_StatusTypeDef errorcode = HAL_OK;

  /* Check Direction parameter */
  assert_param(IS_SPI_DIRECTION_2LINES(hspi->Init.Direction));

  /* Process Locked */
  __HAL_LOCK(hspi);

  /* Init tickstart for timeout management*/
  tickstart = HAL_GetTick();

  if (!((hspi->State == HAL_SPI_STATE_READY) || \
        ((hspi->Init.Mode == SPI_MODE_MASTER) && (hspi->Init.Direction == SPI_DIRECTION_2LINES) && (hspi->State == HAL_SPI_STATE_BUSY_RX))))
  {
    errorcode = HAL_BUSY;
    __HAL_UNLOCK(hspi);
    return errorcode;
  }

  if ((pTxData == NULL) || (pRxData == NULL) || (Size == 0U))
  {
    errorcode = HAL_ERROR;
    __HAL_UNLOCK(hspi);
    return errorcode;
  }

  /* Don't overwrite in case of HAL_SPI_STATE_BUSY_RX */
  if (hspi->State != HAL_SPI_STATE_BUSY_RX)
  {
    hspi->State = HAL_SPI_STATE_BUSY_TX_RX;
  }

  /* Set the transaction information */
  hspi->ErrorCode   = HAL_SPI_ERROR_NONE;
  hspi->pRxBuffPtr  = (uint8_t *)pRxData;
  hspi->RxXferCount = Size;
  hspi->RxXferSize  = Size;
  hspi->pTxBuffPtr  = (uint8_t *)pTxData;
  hspi->TxXferCount = Size;
  hspi->TxXferSize  = Size;

  /*Init field not used in handle to zero */
  hspi->RxISR       = NULL;
  hspi->TxISR       = NULL;

  /* Set the number if data at current transfer */
  MODIFY_REG(hspi->Instance->CR2, SPI_CR2_TSIZE, Size);

  /* Check if the SPI is already enabled */
  if ((hspi->Instance->CR1 & SPI_CR1_SPE) != SPI_CR1_SPE)
  {
    /* Enable SPI peripheral */
    __HAL_SPI_ENABLE(hspi);
  }

  if (hspi->Init.Mode == SPI_MODE_MASTER)
  {
    /* Master transfer start */
    SET_BIT(hspi->Instance->CR1, SPI_CR1_CSTART);
  }

  /* Transmit and Receive data in 32 Bit mode */
  if (hspi->Init.DataSize > SPI_DATASIZE_16BIT)
  {
    while ((hspi->TxXferCount > 0U) || (hspi->RxXferCount > 0U))
    {
      /* Check TXE flag */
      if ((hspi->TxXferCount > 0U) && (__HAL_SPI_GET_FLAG(hspi, SPI_FLAG_TXE)))
      {
        *((__IO uint32_t *)&hspi->Instance->TXDR) = *((uint32_t *)hspi->pTxBuffPtr);
        hspi->pTxBuffPtr += sizeof(uint32_t);
        hspi->TxXferCount --;
      }

      /* Check RXNE flag */
      if ((hspi->RxXferCount > 0U) && (__HAL_SPI_GET_FLAG(hspi, SPI_FLAG_RXNE)))
      {
        *((uint32_t *)hspi->pRxBuffPtr) = *((__IO uint32_t *)&hspi->Instance->RXDR);
        hspi->pRxBuffPtr += sizeof(uint32_t);
        hspi->RxXferCount --;
      }

      if ((Timeout != HAL_MAX_DELAY) && ((HAL_GetTick() - tickstart) >=  Timeout))
      {
        /* Set the error code and execute error callback*/
        SET_BIT(hspi->ErrorCode, HAL_SPI_ERROR_TIMEOUT);
        HAL_SPI_ErrorCallback(hspi);

        /* Set the SPI State ready */
        hspi->State = HAL_SPI_STATE_READY;

        /* Process Unlocked */
        __HAL_UNLOCK(hspi);
        return HAL_ERROR;
      }
    }
  }
  /* Transmit and Receive data in 16 Bit mode */
  else if (hspi->Init.DataSize > SPI_DATASIZE_8BIT)
  {
    if (IS_SPI_HIGHEND_INSTANCE(hspi->Instance))
    {
      while ((hspi->TxXferCount > 0U) || (hspi->RxXferCount > 0U))
      {
        /* Check TXE flag */
        if ((hspi->TxXferCount > 0U) && (__HAL_SPI_GET_FLAG(hspi, SPI_FLAG_TXE)))
        {
          if ( (hspi->TxXferCount > 1U) && (hspi->Init.FifoThreshold > SPI_FIFO_THRESHOLD_01DATA))
          {
            *((__IO uint32_t *)&hspi->Instance->TXDR) = *((uint32_t *)hspi->pTxBuffPtr);
            hspi->pTxBuffPtr += sizeof(uint32_t);
            hspi->TxXferCount-=2;
          }
          else
          {
            *((__IO uint16_t *)&hspi->Instance->TXDR) = *((uint16_t *)hspi->pTxBuffPtr);
            hspi->pTxBuffPtr += sizeof(uint16_t);
            hspi->TxXferCount--;
          }
        }

        /* Check RXNE flag */
        if ((hspi->RxXferCount > 0U) && (__HAL_SPI_GET_FLAG(hspi, SPI_FLAG_RXNE)))
        {
          if (hspi->Instance->SR & SPI_FLAG_RXWNE)
          {
            *((uint32_t *)hspi->pRxBuffPtr) = *((__IO uint32_t *)&hspi->Instance->RXDR);
            hspi->pRxBuffPtr += sizeof(uint32_t);
            hspi->RxXferCount-=2;
          }
          else
          {
            *((uint16_t *)hspi->pRxBuffPtr) = *((__IO uint16_t *)&hspi->Instance->RXDR);
            hspi->pRxBuffPtr += sizeof(uint16_t);
            hspi->RxXferCount--;
          }
        }

        if ((Timeout != HAL_MAX_DELAY) && ((HAL_GetTick() - tickstart) >=  Timeout))
        {
          /* Set the error code and execute error callback*/
          SET_BIT(hspi->ErrorCode, HAL_SPI_ERROR_TIMEOUT);
          HAL_SPI_ErrorCallback(hspi);

          /* Set the SPI State ready */
          hspi->State = HAL_SPI_STATE_READY;

          /* Process Unlocked */
          __HAL_UNLOCK(hspi);
          return HAL_ERROR;
        }
      }
    }
  }
  /* Transmit and Receive data in 8 Bit mode */
  else
  {
    if (IS_SPI_HIGHEND_INSTANCE(hspi->Instance))
    {
      while ((hspi->TxXferCount > 0U) || (hspi->RxXferCount > 0U))
      {
        /* check TXE flag */
        if ((hspi->TxXferCount > 0U) && (__HAL_SPI_GET_FLAG(hspi, SPI_FLAG_TXE)))
        {
          if ((hspi->TxXferCount > 3U) && (hspi->Init.FifoThreshold > SPI_FIFO_THRESHOLD_03DATA))
          {
            *((__IO uint32_t *)&hspi->Instance->TXDR) = *((uint32_t *)hspi->pTxBuffPtr);
            hspi->pTxBuffPtr += sizeof(uint32_t);
            hspi->TxXferCount-=4;
          }
          else if ((hspi->TxXferCount > 1U) && (hspi->Init.FifoThreshold > SPI_FIFO_THRESHOLD_01DATA))
          {
            *((__IO uint16_t *)&hspi->Instance->TXDR) = *((uint16_t *)hspi->pTxBuffPtr);
            hspi->pTxBuffPtr += sizeof(uint16_t);
            hspi->TxXferCount-=2;
          }
          else
          {
            *((__IO uint8_t *)&hspi->Instance->TXDR) = *((uint8_t *)hspi->pTxBuffPtr);
            hspi->pTxBuffPtr += sizeof(uint8_t);
            hspi->TxXferCount--;
          }
        }

        /* check TXTF flag */
        if (__HAL_SPI_GET_FLAG(hspi, SPI_FLAG_TXTF))
        {
          __HAL_SPI_CLEAR_TXTFFLAG(hspi);
        }

        /* Wait until RXNE flag is reset */
        if ((hspi->RxXferCount > 0U) && (__HAL_SPI_GET_FLAG(hspi, SPI_FLAG_RXNE)))
        {
          if (hspi->Instance->SR & SPI_FLAG_RXWNE)
          {
            *((uint32_t *)hspi->pRxBuffPtr) = *((__IO uint32_t *)&hspi->Instance->RXDR);
            hspi->pRxBuffPtr += sizeof(uint32_t);
            hspi->RxXferCount-=4;
          }
          else if ((hspi->Instance->SR & SPI_FLAG_FRLVL) > SPI_FRLVL_QUARTER_FULL)
          {
            *((uint16_t *)hspi->pRxBuffPtr) = *((__IO uint16_t *)&hspi->Instance->RXDR);
            hspi->pRxBuffPtr += sizeof(uint16_t);
            hspi->RxXferCount-=2;
          }
          else
          {
            (*hspi->pRxBuffPtr) = *((__IO uint8_t *)&hspi->Instance->RXDR);
            hspi->pRxBuffPtr += sizeof(uint8_t);
            hspi->RxXferCount--;
          }
        }

        if ((Timeout != HAL_MAX_DELAY) && ((HAL_GetTick() - tickstart) >=  Timeout))
        {
          /* Set the error code and execute error callback*/
          SET_BIT(hspi->ErrorCode, HAL_SPI_ERROR_TIMEOUT);
          HAL_SPI_ErrorCallback(hspi);

          /* Set the SPI State ready */
          hspi->State = HAL_SPI_STATE_READY;

          /* Process Unlocked */
          __HAL_UNLOCK(hspi);
          return HAL_ERROR;
        }
      }
    }
  }

  /* Check the end of the transaction */
  if (SPI_EndRxTxTransaction(hspi, Timeout, tickstart) != HAL_OK)
  {
    hspi->ErrorCode = HAL_SPI_ERROR_FLAG;
  }

#ifdef USE_SPI_CRC
  /* Check if CRC error occurred */
  if (hspi->Init.CRCCalculation == SPI_CRCCALCULATION_ENABLE)
  {
    if (__HAL_SPI_GET_FLAG(hspi, SPI_FLAG_CRCERR) != RESET)
    {
      SET_BIT(hspi->ErrorCode, HAL_SPI_ERROR_CRC);

      /* Clear CRC Flag */
      __HAL_SPI_CLEAR_CRCERRFLAG(hspi);
    }
  }
#endif /* USE_SPI_CRC */

  if (hspi->ErrorCode != HAL_SPI_ERROR_NONE)
  {
    errorcode = HAL_ERROR;
  }

  hspi->State = HAL_SPI_STATE_READY;
  __HAL_UNLOCK(hspi);
  return errorcode;
}

/**
  * @brief  Transmit an amount of data in non-blocking mode with Interrupt.
  * @param  hspi: pointer to a SPI_HandleTypeDef structure that contains
  *               the configuration information for SPI module.
  * @param  pData: pointer to data buffer
  * @param  Size: amount of data to be sent
  * @retval HAL status
  */
HAL_StatusTypeDef HAL_SPI_Transmit_IT(SPI_HandleTypeDef *hspi, uint8_t *pData, uint16_t Size)
{
  HAL_StatusTypeDef errorcode = HAL_OK;

  /* Check Direction parameter */
  assert_param(IS_SPI_DIRECTION_2LINES_OR_1LINE_2LINES_TXONLY(hspi->Init.Direction));

  /* Process Locked */
  __HAL_LOCK(hspi);

  if ((pData == NULL) || (Size == 0U))
  {
    errorcode = HAL_ERROR;
    __HAL_UNLOCK(hspi);
    return errorcode;
  }

  if (hspi->State != HAL_SPI_STATE_READY)
  {
    errorcode = HAL_BUSY;
    __HAL_UNLOCK(hspi);
    return errorcode;
  }

  /* Set the transaction information */
  hspi->State       = HAL_SPI_STATE_BUSY_TX;
  hspi->ErrorCode   = HAL_SPI_ERROR_NONE;
  hspi->pTxBuffPtr  = (uint8_t *)pData;
  hspi->TxXferSize  = Size;
  hspi->TxXferCount = Size;

  /* Init field not used in handle to zero */
  hspi->pRxBuffPtr  = NULL;
  hspi->RxXferSize  = 0U;
  hspi->RxXferCount = 0U;
  hspi->RxISR       = NULL;

  /* Set the function for IT treatment */
  if (hspi->Init.DataSize > SPI_DATASIZE_16BIT)
  {
    hspi->TxISR = SPI_TxISR_32BIT;
  }
  else if (hspi->Init.DataSize > SPI_DATASIZE_8BIT)
  {
    hspi->TxISR = SPI_TxISR_16BIT;
  }
  else
  {
    hspi->TxISR = SPI_TxISR_8BIT;
  }

  /* Configure communication direction : 1Line */
  if (hspi->Init.Direction == SPI_DIRECTION_1LINE)
  {
    SPI_1LINE_TX(hspi);
  }

  /* Set the number if data at current transfer */
  MODIFY_REG(hspi->Instance->CR2, SPI_CR2_TSIZE, Size);

  /* Check if the SPI is already enabled */
  if ((hspi->Instance->CR1 & SPI_CR1_SPE) != SPI_CR1_SPE)
  {
    /* Enable SPI peripheral */
    __HAL_SPI_ENABLE(hspi);
  }
  else
  {
    if (__HAL_SPI_GET_FLAG(hspi, SPI_FLAG_UDR)) 
    {
      *((__IO uint8_t *)&hspi->Instance->TXDR) = 0x01U;
      __HAL_SPI_CLEAR_UDRFLAG(hspi);
      __HAL_SPI_DISABLE(hspi);
      __HAL_SPI_ENABLE(hspi);
    }
  }

  if (hspi->Init.Mode == SPI_MODE_MASTER)
  {
    /* Master transfer start */
    SET_BIT(hspi->Instance->CR1, SPI_CR1_CSTART);
  }

  /* Enable TXE and ERR interrupt */
  __HAL_SPI_ENABLE_IT(hspi, (SPI_IT_TXE | SPI_IT_ERR));

  __HAL_UNLOCK(hspi);
  return errorcode;
}

/**
  * @brief  Receive an amount of data in non-blocking mode with Interrupt.
  * @param  hspi: pointer to a SPI_HandleTypeDef structure that contains
  *               the configuration information for SPI module.
  * @param  pData: pointer to data buffer
  * @param  Size: amount of data to be sent
  * @retval HAL status
  */
HAL_StatusTypeDef HAL_SPI_Receive_IT(SPI_HandleTypeDef *hspi, uint8_t *pData, uint16_t Size)
{
  HAL_StatusTypeDef errorcode = HAL_OK;

  /* Check Direction parameter */
  assert_param(IS_SPI_DIRECTION_2LINES_OR_1LINE_2LINES_RXONLY(hspi->Init.Direction));

  if ((hspi->Init.Direction == SPI_DIRECTION_2LINES) && (hspi->Init.Mode == SPI_MODE_MASTER))
  {
    hspi->State = HAL_SPI_STATE_BUSY_RX;
    /* Call transmit-receive function to send Dummy data on Tx line and generate clock on CLK line */
    return HAL_SPI_TransmitReceive_IT(hspi, pData, pData, Size);
  }

  /* Process Locked */
  __HAL_LOCK(hspi);

  if (hspi->State != HAL_SPI_STATE_READY)
  {
    errorcode = HAL_BUSY;
    __HAL_UNLOCK(hspi);
    return errorcode;
  }

  if ((pData == NULL) || (Size == 0U))
  {
    errorcode = HAL_ERROR;
    __HAL_UNLOCK(hspi);
    return errorcode;
  }

  /* Set the transaction information */
  hspi->State       = HAL_SPI_STATE_BUSY_RX;
  hspi->ErrorCode   = HAL_SPI_ERROR_NONE;
  hspi->pRxBuffPtr  = (uint8_t *)pData;
  hspi->RxXferSize  = Size;
  hspi->RxXferCount = Size;

  /* Init field not used in handle to zero */
  hspi->pTxBuffPtr  = NULL;
  hspi->TxXferSize  = 0U;
  hspi->TxXferCount = 0U;
  hspi->TxISR       = NULL;

  /* Set the function for IT treatment */
  if (hspi->Init.DataSize > SPI_DATASIZE_16BIT)
  {
    hspi->RxISR = SPI_RxISR_32BIT;
  }
  else if (hspi->Init.DataSize > SPI_DATASIZE_8BIT)
  {
    hspi->RxISR = SPI_RxISR_16BIT;
  }
  else
  {
    hspi->RxISR = SPI_RxISR_8BIT;
  }

  /* Configure communication direction : 1Line */
  if (hspi->Init.Direction == SPI_DIRECTION_1LINE)
  {
    SPI_1LINE_RX(hspi);
  }

  /* Note : The SPI must be enabled after unlocking current process
            to avoid the risk of SPI interrupt handle execution before current
            process unlock */

  /* Set the number if data at current transfer */
  MODIFY_REG(hspi->Instance->CR2, SPI_CR2_TSIZE, Size);

  /* Check if the SPI is already enabled */
  if ((hspi->Instance->CR1 & SPI_CR1_SPE) != SPI_CR1_SPE)
  {
    /* Enable SPI peripheral */
    __HAL_SPI_ENABLE(hspi);
  }

  if (hspi->Init.Mode == SPI_MODE_MASTER)
  {
    /* Master transfer start */
    SET_BIT(hspi->Instance->CR1, SPI_CR1_CSTART);
  }

  /* Enable TXE and ERR interrupt */
  __HAL_SPI_ENABLE_IT(hspi, (SPI_IT_RXNE | SPI_IT_EOT | SPI_IT_ERR));

  /* Process Unlocked */
  __HAL_UNLOCK(hspi);
  return errorcode;
}

/**
  * @brief  Transmit and Receive an amount of data in non-blocking mode with Interrupt.
  * @param  hspi: pointer to a SPI_HandleTypeDef structure that contains
  *               the configuration information for SPI module.
  * @param  pTxData: pointer to transmission data buffer
  * @param  pRxData: pointer to reception data buffer
  * @param  Size: amount of data to be sent and received
  * @retval HAL status
  */
HAL_StatusTypeDef HAL_SPI_TransmitReceive_IT(SPI_HandleTypeDef *hspi, uint8_t *pTxData, uint8_t *pRxData, uint16_t Size)
{
  HAL_StatusTypeDef errorcode = HAL_OK;

  /* Check Direction parameter */
  assert_param(IS_SPI_DIRECTION_2LINES(hspi->Init.Direction));

  /* Process locked */
  __HAL_LOCK(hspi);

  if (!((hspi->State == HAL_SPI_STATE_READY) || \
        ((hspi->Init.Mode == SPI_MODE_MASTER) && (hspi->Init.Direction == SPI_DIRECTION_2LINES) && (hspi->State == HAL_SPI_STATE_BUSY_RX))))
  {
    errorcode = HAL_BUSY;
    __HAL_UNLOCK(hspi);
    return errorcode;
  }

  if ((pTxData == NULL) || (pRxData == NULL) || (Size == 0U))
  {
    errorcode = HAL_ERROR;
    __HAL_UNLOCK(hspi);
    return errorcode;
  }

  /* Don't overwrite in case of HAL_SPI_STATE_BUSY_RX */
  if (hspi->State != HAL_SPI_STATE_BUSY_RX)
  {
    hspi->State = HAL_SPI_STATE_BUSY_TX_RX;
  }

  /* Set the transaction information */
  hspi->ErrorCode   = HAL_SPI_ERROR_NONE;
  hspi->pTxBuffPtr  = (uint8_t *)pTxData;
  hspi->TxXferSize  = Size;
  hspi->TxXferCount = Size;
  hspi->pRxBuffPtr  = (uint8_t *)pRxData;
  hspi->RxXferSize  = Size;
  hspi->RxXferCount = Size;

  /* Set the function for IT treatment */
  if (hspi->Init.DataSize > SPI_DATASIZE_16BIT)
  {
    hspi->RxISR     = SPI_2linesRxISR_32BIT;
    hspi->TxISR     = SPI_2linesTxISR_32BIT;
  }
  else if (hspi->Init.DataSize > SPI_DATASIZE_8BIT)
  {
    hspi->RxISR     = SPI_2linesRxISR_16BIT;
    hspi->TxISR     = SPI_2linesTxISR_16BIT;
  }
  else
  {
    hspi->RxISR     = SPI_2linesRxISR_8BIT;
    hspi->TxISR     = SPI_2linesTxISR_8BIT;
  }

  /* Set the number if data at current transfer */
  MODIFY_REG(hspi->Instance->CR2, SPI_CR2_TSIZE, Size);

  /* Check if the SPI is already enabled */
  if ((hspi->Instance->CR1 & SPI_CR1_SPE) != SPI_CR1_SPE)
  {
    /* Enable SPI peripheral */
    __HAL_SPI_ENABLE(hspi);
  }

  if (hspi->Init.Mode == SPI_MODE_MASTER)
  {
    /* Master transfer start */
    SET_BIT(hspi->Instance->CR1, SPI_CR1_CSTART);
  }

  /* Enable TXE, RXNE and ERR interrupt */
  __HAL_SPI_ENABLE_IT(hspi, (SPI_IT_TXE | SPI_IT_RXNE | SPI_IT_EOT | SPI_IT_ERR));

  /* Process Unlocked */
  __HAL_UNLOCK(hspi);
  return errorcode;
}

/**
  * @brief  Transmit an amount of data in non-blocking mode with DMA.
  * @param  hspi: pointer to a SPI_HandleTypeDef structure that contains
  *               the configuration information for SPI module.
  * @param  pData: pointer to data buffer
  * @param  Size: amount of data to be sent
  * @retval HAL status
  */
HAL_StatusTypeDef HAL_SPI_Transmit_DMA(SPI_HandleTypeDef *hspi, uint8_t *pData, uint16_t Size)
{
  HAL_StatusTypeDef errorcode = HAL_OK;

  /* Check Direction parameter */
  assert_param(IS_SPI_DIRECTION_2LINES_OR_1LINE_2LINES_TXONLY(hspi->Init.Direction));

  /* Process Locked */
  __HAL_LOCK(hspi);

  if (hspi->State != HAL_SPI_STATE_READY)
  {
    errorcode = HAL_BUSY;
    __HAL_UNLOCK(hspi);
    return errorcode;
  }

  if ((pData == NULL) || (Size == 0U))
  {
    errorcode = HAL_ERROR;
    __HAL_UNLOCK(hspi);
    return errorcode;
  }

  /* Set the transaction information */
  hspi->State       = HAL_SPI_STATE_BUSY_TX;
  hspi->ErrorCode   = HAL_SPI_ERROR_NONE;
  hspi->pTxBuffPtr  = (uint8_t *)pData;
  hspi->TxXferSize  = Size;
  hspi->TxXferCount = Size;

  /* Init field not used in handle to zero */
  hspi->pRxBuffPtr  = NULL;
  hspi->TxISR       = NULL;
  hspi->RxISR       = NULL;
  hspi->RxXferSize  = 0U;
  hspi->RxXferCount = 0U;

  /* Configure communication direction : 1Line */
  if (hspi->Init.Direction == SPI_DIRECTION_1LINE)
  {
    SPI_1LINE_TX(hspi);
  }

  /* Packing mode management is enabled by the DMA settings */
  if (((hspi->Init.DataSize > SPI_DATASIZE_16BIT) && (hspi->hdmarx->Init.MemDataAlignment != DMA_MDATAALIGN_WORD))    || \
      ((hspi->Init.DataSize > SPI_DATASIZE_8BIT) && ((hspi->hdmarx->Init.MemDataAlignment != DMA_MDATAALIGN_HALFWORD) && \
                                                         (hspi->hdmarx->Init.MemDataAlignment != DMA_MDATAALIGN_WORD))))
  {
    /* Restriction the DMA data received is not allowed in this mode */
    errorcode = HAL_ERROR;
    __HAL_UNLOCK(hspi);
    return errorcode;
  }

  if (hspi->Init.DataSize > SPI_DATASIZE_8BIT)
  {
    /* Set FifoThreshold according the reception data length: 8bit */
    SET_BIT(hspi->Instance->CFG1, SPI_FIFO_THRESHOLD_08DATA);
  }
  else
  {
    /* Set FifoThreshold according the reception data length: 16bit */
    SET_BIT(hspi->Instance->CFG1, SPI_FIFO_THRESHOLD_16DATA);

    if ((hspi->hdmatx->Init.MemDataAlignment == DMA_MDATAALIGN_HALFWORD) ||\
        (hspi->hdmatx->Init.MemDataAlignment == DMA_MDATAALIGN_WORD))
    {
      if ((hspi->TxXferSize & 0x1U) == 0x0U)
      {
        hspi->TxXferCount = hspi->TxXferCount >> 1U;
      }
      else
      {
        hspi->TxXferCount = (hspi->TxXferCount >> 1U) + 1U;
      }
    }
  }

  /* Set the SPI TxDMA Half transfer complete callback */
  hspi->hdmatx->XferHalfCpltCallback = SPI_DMAHalfTransmitCplt;

  /* Set the SPI TxDMA transfer complete callback */
  hspi->hdmatx->XferCpltCallback = SPI_DMATransmitCplt;

  /* Set the DMA error callback */
  hspi->hdmatx->XferErrorCallback = SPI_DMAError;

  /* Set the DMA AbortCpltCallback */
  hspi->hdmatx->XferAbortCallback = NULL;

  /* Check if the SPI is disabled to edit CFG1 register */
  if ((hspi->Instance->CR1 & SPI_CR1_SPE) == SPI_CR1_SPE)
  {
    /* Disable SPI peripheral */
    __HAL_SPI_DISABLE(hspi);
  }

  /* Clear TXDMAEN bit*/
  CLEAR_BIT(hspi->Instance->CFG1, SPI_CFG1_TXDMAEN);

  /* Enable the Tx DMA Stream/Channel */
  HAL_DMA_Start_IT(hspi->hdmatx, (uint32_t)hspi->pTxBuffPtr, (uint32_t)&hspi->Instance->TXDR, hspi->TxXferCount);

  /* Set the number if data at current transfer */
  MODIFY_REG(hspi->Instance->CR2, SPI_CR2_TSIZE, Size);

  /* Enable Tx DMA Request */
  SET_BIT(hspi->Instance->CFG1, SPI_CFG1_TXDMAEN);

  /* Enable SPI peripheral */
  __HAL_SPI_ENABLE(hspi);

  /* Enable the SPI Error Interrupt Bit */
  __HAL_SPI_ENABLE_IT(hspi, (SPI_IT_ERR));

  if (hspi->Init.Mode == SPI_MODE_MASTER)
  {
    /* Master transfer start */
    SET_BIT(hspi->Instance->CR1, SPI_CR1_CSTART);
  }

  /* Process Unlocked */
  __HAL_UNLOCK(hspi);
  return errorcode;
}

/**
  * @brief  Receive an amount of data in non-blocking mode with DMA.
  * @param  hspi: pointer to a SPI_HandleTypeDef structure that contains
  *               the configuration information for SPI module.
  * @param  pData: pointer to data buffer
  * @note   When the CRC feature is enabled the pData Length must be Size + 1.
  * @param  Size: amount of data to be sent
  * @retval HAL status
  */
HAL_StatusTypeDef HAL_SPI_Receive_DMA(SPI_HandleTypeDef *hspi, uint8_t *pData, uint16_t Size)
{
  HAL_StatusTypeDef errorcode = HAL_OK;

  /* Check Direction parameter */
  assert_param(IS_SPI_DIRECTION_2LINES_OR_1LINE_2LINES_RXONLY(hspi->Init.Direction));

  if ((hspi->Init.Direction == SPI_DIRECTION_2LINES) && (hspi->Init.Mode == SPI_MODE_MASTER))
  {
    hspi->State = HAL_SPI_STATE_BUSY_RX;
    /* Call transmit-receive function to send Dummy data on Tx line and generate clock on CLK line */
    return HAL_SPI_TransmitReceive_DMA(hspi, pData, pData, Size);
  }

  /* Process Locked */
  __HAL_LOCK(hspi);

  if (hspi->State != HAL_SPI_STATE_READY)
  {
    errorcode = HAL_BUSY;
    __HAL_UNLOCK(hspi);
    return errorcode;
  }

  if ((pData == NULL) || (Size == 0U))
  {
    errorcode = HAL_ERROR;
    __HAL_UNLOCK(hspi);
    return errorcode;
  }

  /* Set the transaction information */
  hspi->State       = HAL_SPI_STATE_BUSY_RX;
  hspi->ErrorCode   = HAL_SPI_ERROR_NONE;
  hspi->pRxBuffPtr  = (uint8_t *)pData;
  hspi->RxXferSize  = Size;
  hspi->RxXferCount = Size;

  /*Init field not used in handle to zero */
  hspi->RxISR       = NULL;
  hspi->TxISR       = NULL;
  hspi->TxXferSize  = 0U;
  hspi->TxXferCount = 0U;

  /* Configure communication direction : 1Line */
  if (hspi->Init.Direction == SPI_DIRECTION_1LINE)
  {
    SPI_1LINE_RX(hspi);
  }

  /* Packing mode management is enabled by the DMA settings */
  if (((hspi->Init.DataSize > SPI_DATASIZE_16BIT) && (hspi->hdmarx->Init.MemDataAlignment != DMA_MDATAALIGN_WORD))    || \
      ((hspi->Init.DataSize > SPI_DATASIZE_8BIT) && ((hspi->hdmarx->Init.MemDataAlignment != DMA_MDATAALIGN_HALFWORD) && \
                                                     (hspi->hdmarx->Init.MemDataAlignment != DMA_MDATAALIGN_WORD))))
  {
    /* Restriction the DMA data received is not allowed in this mode */
    errorcode = HAL_ERROR;
    __HAL_UNLOCK(hspi);
    return errorcode;
  }

  /* Check if the SPI is disabled to edit CFG1 register */
  if ((hspi->Instance->CR1 & SPI_CR1_SPE) != SPI_CR1_SPE)
  {
    /* Disable SPI peripheral */
    __HAL_SPI_DISABLE(hspi);
  }

  /* Clear RXDMAEN bit */
  CLEAR_BIT(hspi->Instance->CFG1, SPI_CFG1_RXDMAEN);

  if (hspi->Init.DataSize > SPI_DATASIZE_8BIT)
  {
    /* set FifoThreshold according the reception data length: 16bit */
    SET_BIT(hspi->Instance->CFG1, SPI_FIFO_THRESHOLD_16DATA);
  }
  else
  {
    /* set FifoThreshold according the reception data length: 8bit */
    SET_BIT(hspi->Instance->CFG1, SPI_FIFO_THRESHOLD_08DATA);

    if ((hspi->RxXferCount & 0x1U) == 0x0U)
    {
      hspi->RxXferCount = hspi->RxXferCount >> 1U;
    }
    else
    {
      hspi->RxXferCount = (hspi->RxXferCount >> 1U) + 1U;
     }
  }

  /* Set the SPI RxDMA Half transfer complete callback */
  hspi->hdmarx->XferHalfCpltCallback = SPI_DMAHalfReceiveCplt;

  /* Set the SPI Rx DMA transfer complete callback */
  hspi->hdmarx->XferCpltCallback = SPI_DMAReceiveCplt;

  /* Set the DMA error callback */
  hspi->hdmarx->XferErrorCallback = SPI_DMAError;

  /* Set the DMA AbortCpltCallback */
  hspi->hdmarx->XferAbortCallback = NULL;

  /* Enable the Rx DMA Stream/Channel  */
  HAL_DMA_Start_IT(hspi->hdmarx, (uint32_t)&hspi->Instance->RXDR, (uint32_t)hspi->pRxBuffPtr, hspi->RxXferCount);

  /* Set the number if data at current transfer */
  MODIFY_REG(hspi->Instance->CR2, SPI_CR2_TSIZE, Size);

  /* Enable Rx DMA Request */
  SET_BIT(hspi->Instance->CFG1, SPI_CFG1_RXDMAEN);

  /* Enable SPI peripheral */
  __HAL_SPI_ENABLE(hspi);

  /* Enable the SPI Error Interrupt Bit */
  __HAL_SPI_ENABLE_IT(hspi, (SPI_IT_ERR));

  if (hspi->Init.Mode == SPI_MODE_MASTER)
  {
    /* Master transfer start */
    SET_BIT(hspi->Instance->CR1, SPI_CR1_CSTART);
  }

  /* Process Unlocked */
  __HAL_UNLOCK(hspi);
  return errorcode;
}

/**
  * @brief  Transmit and Receive an amount of data in non-blocking mode with DMA.
  * @param  hspi: pointer to a SPI_HandleTypeDef structure that contains
  *               the configuration information for SPI module.
  * @param  pTxData: pointer to transmission data buffer
  * @param  pRxData: pointer to reception data buffer
  * @note   When the CRC feature is enabled the pRxData Length must be Size + 1
  * @param  Size: amount of data to be sent
  * @retval HAL status
  */
HAL_StatusTypeDef HAL_SPI_TransmitReceive_DMA(SPI_HandleTypeDef *hspi, uint8_t *pTxData, uint8_t *pRxData,
                                              uint16_t Size)
{
  HAL_StatusTypeDef errorcode = HAL_OK;

  /* Check Direction parameter */
  assert_param(IS_SPI_DIRECTION_2LINES(hspi->Init.Direction));

  /* Process locked */
  __HAL_LOCK(hspi);

  if (!((hspi->State == HAL_SPI_STATE_READY) ||
        ((hspi->Init.Mode == SPI_MODE_MASTER) && (hspi->Init.Direction == SPI_DIRECTION_2LINES) && (hspi->State == HAL_SPI_STATE_BUSY_RX))))
  {
    errorcode = HAL_BUSY;
    __HAL_UNLOCK(hspi);
    return errorcode;
  }

  if ((pTxData == NULL) || (pRxData == NULL) || (Size == 0U))
  {
    errorcode = HAL_ERROR;
    __HAL_UNLOCK(hspi);
    return errorcode;
  }

  /* Don't overwrite in case of HAL_SPI_STATE_BUSY_RX */
  if (hspi->State != HAL_SPI_STATE_BUSY_RX)
  {
    hspi->State = HAL_SPI_STATE_BUSY_TX_RX;
  }

  /* Set the transaction information */
  hspi->ErrorCode   = HAL_SPI_ERROR_NONE;
  hspi->pTxBuffPtr  = (uint8_t *)pTxData;
  hspi->TxXferSize  = Size;
  hspi->TxXferCount = Size;
  hspi->pRxBuffPtr  = (uint8_t *)pRxData;
  hspi->RxXferSize  = Size;
  hspi->RxXferCount = Size;

  /* Init field not used in handle to zero */
  hspi->RxISR       = NULL;
  hspi->TxISR       = NULL;

  /* Check if the SPI is disabled to edit CFG1 register */
  if ((hspi->Instance->CR1 & SPI_CR1_SPE) == SPI_CR1_SPE)
  {
    /* Disable SPI peripheral */
    __HAL_SPI_DISABLE(hspi);
  }

  /* Reset the Tx/Rx DMA bits */
  CLEAR_BIT(hspi->Instance->CFG1, SPI_CFG1_TXDMAEN | SPI_CFG1_RXDMAEN);

  /* Packing mode management is enabled by the DMA settings */
  if (((hspi->Init.DataSize > SPI_DATASIZE_16BIT) && (hspi->hdmarx->Init.MemDataAlignment != DMA_MDATAALIGN_WORD))    || \
      ((hspi->Init.DataSize > SPI_DATASIZE_8BIT) && ((hspi->hdmarx->Init.MemDataAlignment != DMA_MDATAALIGN_HALFWORD) && \
                                                         (hspi->hdmarx->Init.MemDataAlignment != DMA_MDATAALIGN_WORD))))
  {
    /* Restriction the DMA data received is not allowed in this mode */
    errorcode = HAL_ERROR;
    /* Process Unlocked */
    __HAL_UNLOCK(hspi);
    return errorcode;
  }
  
  if (hspi->Init.DataSize > SPI_DATASIZE_8BIT)
  {
    /* Set FifoThreshold according the reception data length: 16bit */
    SET_BIT(hspi->Instance->CFG1, SPI_FIFO_THRESHOLD_16DATA);
  }
  else
  {
    /* Set FifoThreshold according the reception data length: 8bit */
    SET_BIT(hspi->Instance->CFG1, SPI_FIFO_THRESHOLD_08DATA);

    if ((hspi->hdmatx->Init.MemDataAlignment == DMA_MDATAALIGN_HALFWORD) ||\
        (hspi->hdmatx->Init.MemDataAlignment == DMA_MDATAALIGN_WORD))

    {
      if ((hspi->TxXferSize & 0x1U) == 0x0U)
      {
        hspi->TxXferCount = hspi->TxXferCount >> 1U;
      }
      else
      {
        hspi->TxXferCount = (hspi->TxXferCount >> 1U) + 1U;
      }
    }

    if ((hspi->hdmarx->Init.MemDataAlignment == DMA_MDATAALIGN_HALFWORD)||\
        (hspi->hdmarx->Init.MemDataAlignment == DMA_MDATAALIGN_WORD))
    {
      /* Set FifoThreshold according the reception data length: 16bit */
      SET_BIT(hspi->Instance->CFG1, SPI_FIFO_THRESHOLD_16DATA);

      if ((hspi->RxXferCount & 0x1U) == 0x0U)
      {
        hspi->RxXferCount = hspi->RxXferCount >> 1U;
      }
      else
      {
        hspi->RxXferCount = (hspi->RxXferCount >> 1U) + 1U;
      }
    }
  }

  /* Check if we are in Rx only or in Rx/Tx Mode and configure the DMA transfer complete callback */
  if (hspi->State == HAL_SPI_STATE_BUSY_RX)
  {
    /* Set the SPI Rx DMA Half transfer complete callback */
    hspi->hdmarx->XferHalfCpltCallback = SPI_DMAHalfReceiveCplt;
    hspi->hdmarx->XferCpltCallback     = SPI_DMAReceiveCplt;
  }
  else
  {
    /* Set the SPI Tx/Rx DMA Half transfer complete callback */
    hspi->hdmarx->XferHalfCpltCallback = SPI_DMAHalfTransmitReceiveCplt;
    hspi->hdmarx->XferCpltCallback     = SPI_DMATransmitReceiveCplt;
  }

  /* Set the DMA error callback */
  hspi->hdmarx->XferErrorCallback = SPI_DMAError;

  /* Set the DMA AbortCpltCallback */
  hspi->hdmarx->XferAbortCallback = NULL;

  /* Enable the Rx DMA Stream/Channel  */
  HAL_DMA_Start_IT(hspi->hdmarx, (uint32_t)&hspi->Instance->RXDR, (uint32_t)hspi->pRxBuffPtr, hspi->RxXferCount);

  /* Enable Rx DMA Request */
  SET_BIT(hspi->Instance->CFG1, SPI_CFG1_RXDMAEN);

  /* Set the SPI Tx DMA transfer complete callback as NULL because the communication closing
  is performed in DMA reception complete callback  */
  hspi->hdmatx->XferHalfCpltCallback = NULL;
  hspi->hdmatx->XferCpltCallback     = NULL;
  hspi->hdmatx->XferErrorCallback    = NULL;
  hspi->hdmatx->XferAbortCallback    = NULL;

  /* Enable the Tx DMA Stream/Channel  */
  HAL_DMA_Start_IT(hspi->hdmatx, (uint32_t)hspi->pTxBuffPtr, (uint32_t)&hspi->Instance->TXDR, hspi->TxXferCount);

  MODIFY_REG(hspi->Instance->CR2, SPI_CR2_TSIZE, Size);

  /* Enable Tx DMA Request */
  SET_BIT(hspi->Instance->CFG1, SPI_CFG1_TXDMAEN);

  /* Enable SPI peripheral */
  __HAL_SPI_ENABLE(hspi);

  /* Enable the SPI Error Interrupt Bit */
  __HAL_SPI_ENABLE_IT(hspi, (SPI_IT_ERR));

  if (hspi->Init.Mode == SPI_MODE_MASTER)
  {
    /* Master transfer start */
    SET_BIT(hspi->Instance->CR1, SPI_CR1_CSTART);
  }

  /* Process Unlocked */
  __HAL_UNLOCK(hspi);
  return errorcode;
}

/**
  * @brief  Abort ongoing transfer (blocking mode).
  * @param  hspi SPI handle.
  * @note   This procedure could be used for aborting any ongoing transfer (Tx and Rx),
  *         started in Interrupt or DMA mode.
  * @note   This procedure performs following operations :
  *          + Disable SPI Interrupts (depending of transfer direction) 
  *          + Disable the DMA transfer in the peripheral register (if enabled) 
  *          + Abort DMA transfer by calling HAL_DMA_Abort (in case of transfer in DMA mode) 
  *          + Set handle State to READY.
  * @note   This procedure is executed in blocking mode : when exiting function, Abort is considered as completed.
  * @retval HAL status
*/
HAL_StatusTypeDef HAL_SPI_Abort(SPI_HandleTypeDef *hspi)
{
  HAL_StatusTypeDef errorcode;
  __IO uint32_t count, resetcount;

  /* Initialized local variable  */
  errorcode = HAL_OK;
  resetcount = SPI_DEFAULT_TIMEOUT * (SystemCoreClock / 24U / 1000U);
  count = resetcount;

  /* Disable TXEIE, RXNEIE and ERRIE(mode fault event, overrun error, TI frame error) interrupts */
  if (HAL_IS_BIT_SET(hspi->Instance->IER, SPI_IT_TXE))
  {
    hspi->TxISR = SPI_AbortTx_ISR;
    /* Wait HAL_SPI_STATE_ABORT state */
    do
    {
      if (count-- == 0U)
      {
        SET_BIT(hspi->ErrorCode, HAL_SPI_ERROR_ABORT);
        break;
      }
    }
    while (hspi->State != HAL_SPI_STATE_ABORT);
    /* Reset Timeout Counter */
    count = resetcount;
  }

  if (HAL_IS_BIT_SET(hspi->Instance->IER, SPI_IT_RXNE))
  {
    hspi->RxISR = SPI_AbortRx_ISR;
    /* Wait HAL_SPI_STATE_ABORT state */
    do
    {
      if (count-- == 0U)
      {
        SET_BIT(hspi->ErrorCode, HAL_SPI_ERROR_ABORT);
        break;
      }
    }
    while (hspi->State != HAL_SPI_STATE_ABORT);
    /* Reset Timeout Counter */
    count = resetcount;
  }

  /* Clear ERRIE interrupts in case of DMA Mode */
  CLEAR_BIT(hspi->Instance->IER, SPI_IT_ERR);

  /* Disable the SPI DMA Tx or SPI DMA Rx request if enabled */
  if ((HAL_IS_BIT_SET(hspi->Instance->CFG1, SPI_CFG1_TXDMAEN)) || (HAL_IS_BIT_SET(hspi->Instance->CFG1, SPI_CFG1_RXDMAEN)))
  {
    /* Abort the SPI DMA Tx Stream/Channel : use blocking DMA Abort API (no callback) */
    if (hspi->hdmatx != NULL)
    {
      /* Set the SPI DMA Abort callback :
      will lead to call HAL_SPI_AbortCpltCallback() at end of DMA abort procedure */
      hspi->hdmatx->XferAbortCallback = NULL;

      /* Abort DMA Tx Handle linked to SPI Peripheral */
      if (HAL_DMA_Abort(hspi->hdmatx) != HAL_OK)
      {
        hspi->ErrorCode = HAL_SPI_ERROR_ABORT;
      }

      /* Disable SPI Peripheral */
      __HAL_SPI_DISABLE(hspi);

      /* Disable Tx DMA Request */
      CLEAR_BIT(hspi->Instance->CFG1, (SPI_CFG1_TXDMAEN));

      if (SPI_EndRxTxTransaction(hspi, SPI_DEFAULT_TIMEOUT, HAL_GetTick()) != HAL_OK)
      {
        hspi->ErrorCode = HAL_SPI_ERROR_ABORT;
      }


      /* Empty the FRLVL fifo */
      if (SPI_WaitFifoStateUntilTimeout(hspi, SPI_FLAG_FRLVL, SPI_FRLVL_EMPTY, SPI_DEFAULT_TIMEOUT, HAL_GetTick()) != HAL_OK)
      {
        hspi->ErrorCode = HAL_SPI_ERROR_ABORT;
      }
    }
    /* Abort the SPI DMA Rx Stream/Channel : use blocking DMA Abort API (no callback) */
    if (hspi->hdmarx != NULL)
    {
      /* Set the SPI DMA Abort callback :
      will lead to call HAL_SPI_AbortCpltCallback() at end of DMA abort procedure */
      hspi->hdmarx->XferAbortCallback = NULL;

      /* Abort DMA Rx Handle linked to SPI Peripheral */
      if (HAL_DMA_Abort(hspi->hdmarx) != HAL_OK)
      {
        hspi->ErrorCode = HAL_SPI_ERROR_ABORT;
      }

      /* Disable peripheral */
      __HAL_SPI_DISABLE(hspi);

      /* Empty the FRLVL fifo */
      if (SPI_WaitFifoStateUntilTimeout(hspi, SPI_FLAG_FRLVL, SPI_FRLVL_EMPTY, SPI_DEFAULT_TIMEOUT, HAL_GetTick()) != HAL_OK)
      {
        hspi->ErrorCode = HAL_SPI_ERROR_ABORT;
      }

      /* Disable Rx DMA Request */
      CLEAR_BIT(hspi->Instance->CFG1, (SPI_CFG1_RXDMAEN));
    }
  }
  /* Reset Tx and Rx transfer counters */
  hspi->RxXferCount = 0U;
  hspi->TxXferCount = 0U;

  /* Check error during Abort procedure */
  if (hspi->ErrorCode == HAL_SPI_ERROR_ABORT)
  {
    /* return HAL_Error in case of error during Abort procedure */
    errorcode = HAL_ERROR;
  }
  else
  {
    /* Reset errorCode */
    hspi->ErrorCode = HAL_SPI_ERROR_NONE;
  }

  /* Clear the Error flags in the SR register */
  __HAL_SPI_CLEAR_OVRFLAG(hspi);
  __HAL_SPI_CLEAR_FREFLAG(hspi);
  __HAL_SPI_CLEAR_UDRFLAG(hspi);

  /* Restore hspi->state to ready */
  hspi->State = HAL_SPI_STATE_READY;

  return errorcode;
}

/**
  * @brief  Abort ongoing transfer (Interrupt mode).
  * @param  hspi SPI handle.
  * @note   This procedure could be used for aborting any ongoing transfer (Tx and Rx),
  *         started in Interrupt or DMA mode.
  * @note   This procedure performs following operations :
  *          + Disable SPI Interrupts (depending of transfer direction) 
  *          + Disable the DMA transfer in the peripheral register (if enabled) 
  *          + Abort DMA transfer by calling HAL_DMA_Abort_IT (in case of transfer in DMA mode) 
  *          + Set handle State to READY 
  *          + At abort completion, call user abort complete callback.
  * @note   This procedure is executed in Interrupt mode, meaning that abort procedure could be
  *         considered as completed only when user abort complete callback is executed (not when exiting function).
  * @retval HAL status
*/
HAL_StatusTypeDef HAL_SPI_Abort_IT(SPI_HandleTypeDef *hspi)
{
  HAL_StatusTypeDef errorcode;
  uint32_t abortcplt ;
  __IO uint32_t count, resetcount;

  /* Initialized local variable  */
  errorcode = HAL_OK;
  abortcplt = 1U;
  resetcount = SPI_DEFAULT_TIMEOUT * (SystemCoreClock / 24U / 1000U);
  count = resetcount;

  /* Change Rx and Tx Irq Handler to Disable TXEIE, RXNEIE and ERRIE interrupts */
  if (HAL_IS_BIT_SET(hspi->Instance->IER, SPI_IT_TXE))
  {
    hspi->TxISR = SPI_AbortTx_ISR;
    /* Wait HAL_SPI_STATE_ABORT state */
    do
    {
      if (count-- == 0U)
      {
        SET_BIT(hspi->ErrorCode, HAL_SPI_ERROR_ABORT);
        break;
      }
    }
    while (hspi->State != HAL_SPI_STATE_ABORT);
    /* Reset Timeout Counter */
    count = resetcount;
  }

  if (HAL_IS_BIT_SET(hspi->Instance->IER, SPI_IT_RXNE))
  {
    hspi->RxISR = SPI_AbortRx_ISR;
    /* Wait HAL_SPI_STATE_ABORT state */
    do
    {
      if (count-- == 0U)
      {
        SET_BIT(hspi->ErrorCode, HAL_SPI_ERROR_ABORT);
        break;
      }
    }
    while (hspi->State != HAL_SPI_STATE_ABORT);
    /* Reset Timeout Counter */
    count = resetcount;
  }

  /* Clear ERRIE interrupts in case of DMA Mode */
  CLEAR_BIT(hspi->Instance->IER, SPI_IT_ERR);

  /* If DMA Tx and/or DMA Rx Handles are associated to SPI Handle, DMA Abort complete callbacks should be initialised
     before any call to DMA Abort functions */
  /* DMA Tx Handle is valid */
  if (hspi->hdmatx != NULL)
  {
    /* Set DMA Abort Complete callback if UART DMA Tx request if enabled.
       Otherwise, set it to NULL */
    if (HAL_IS_BIT_SET(hspi->Instance->CFG1, SPI_CFG1_TXDMAEN))
    {
      hspi->hdmatx->XferAbortCallback = SPI_DMATxAbortCallback;
    }
    else
    {
      hspi->hdmatx->XferAbortCallback = NULL;
    }
  }
  /* DMA Rx Handle is valid */
  if (hspi->hdmarx != NULL)
  {
    /* Set DMA Abort Complete callback if UART DMA Rx request if enabled.
       Otherwise, set it to NULL */
    if (HAL_IS_BIT_SET(hspi->Instance->CFG1, SPI_CFG1_RXDMAEN))
    {
      hspi->hdmarx->XferAbortCallback = SPI_DMARxAbortCallback;
    }
    else
    {
      hspi->hdmarx->XferAbortCallback = NULL;
    }
  }

  /* Disable the SPI DMA Tx or the SPI Rx request if enabled */
  if ((HAL_IS_BIT_SET(hspi->Instance->CFG1, SPI_CFG1_TXDMAEN)) && (HAL_IS_BIT_SET(hspi->Instance->CFG1, SPI_CFG1_RXDMAEN)))
  {
    /* Abort the SPI DMA Tx Stream/Channel */
    if (hspi->hdmatx != NULL)
    {
      /* Abort DMA Tx Handle linked to SPI Peripheral */
      if (HAL_DMA_Abort_IT(hspi->hdmatx) != HAL_OK)
      {
        hspi->hdmatx->XferAbortCallback = NULL;
        hspi->ErrorCode = HAL_SPI_ERROR_ABORT;
      }
      else
      {
        abortcplt = 0U;
      }
    }
    /* Abort the SPI DMA Rx Stream/Channel */
    if (hspi->hdmarx != NULL)
    {
      /* Abort DMA Rx Handle linked to SPI Peripheral */
      if (HAL_DMA_Abort_IT(hspi->hdmarx) !=  HAL_OK)
      {
        hspi->hdmarx->XferAbortCallback = NULL;
        hspi->ErrorCode = HAL_SPI_ERROR_ABORT;
        abortcplt = 1U;
      }
      else
      {
        abortcplt = 0U;
      }
    }
  }

  /* Disable the SPI DMA Tx or the SPI Rx request if enabled */
  if (HAL_IS_BIT_SET(hspi->Instance->CFG1, SPI_CFG1_TXDMAEN))
  {
    /* Abort the SPI DMA Tx Stream/Channel */
    if (hspi->hdmatx != NULL)
    {
      /* Abort DMA Tx Handle linked to SPI Peripheral */
      if (HAL_DMA_Abort_IT(hspi->hdmatx) != HAL_OK)
      {
        hspi->hdmatx->XferAbortCallback = NULL;
        hspi->ErrorCode = HAL_SPI_ERROR_ABORT;
      }
      else
      {
        abortcplt = 0U;
      }
    }
  }
  /* Disable the SPI DMA Tx or the SPI Rx request if enabled */
  if (HAL_IS_BIT_SET(hspi->Instance->CFG1, SPI_CFG1_RXDMAEN))
  {
    /* Abort the SPI DMA Rx Stream/Channel */
    if (hspi->hdmarx != NULL)
    {
      /* Abort DMA Rx Handle linked to SPI Peripheral */
      if (HAL_DMA_Abort_IT(hspi->hdmarx) !=  HAL_OK)
      {
        hspi->hdmarx->XferAbortCallback = NULL;
        hspi->ErrorCode = HAL_SPI_ERROR_ABORT;
      }
      else
      {
        abortcplt = 0U;
      }
    }
  }

  if (abortcplt == 1U)
  {
    /* Reset Tx and Rx transfer counters */
    hspi->RxXferCount = 0U;
    hspi->TxXferCount = 0U;

    /* Check error during Abort procedure */
    if (hspi->ErrorCode == HAL_SPI_ERROR_ABORT)
    {
      /* return HAL_Error in case of error during Abort procedure */
      errorcode = HAL_ERROR;
    }
    else
    {
      /* Reset errorCode */
      hspi->ErrorCode = HAL_SPI_ERROR_NONE;
    }

    /* Clear the Error flags in the SR register */
    __HAL_SPI_CLEAR_OVRFLAG(hspi);
    __HAL_SPI_CLEAR_FREFLAG(hspi);
    __HAL_SPI_CLEAR_UDRFLAG(hspi);

    /* Restore hspi->State to Ready */
    hspi->State = HAL_SPI_STATE_READY;

    /* As no DMA to be aborted, call directly user Abort complete callback */
    HAL_SPI_AbortCpltCallback(hspi);
  }

  return errorcode;
}

/**
  * @brief  Pause the DMA Transfer.
  * @param  hspi: pointer to a SPI_HandleTypeDef structure that contains
  *               the configuration information for the specified SPI module.
  * @retval HAL status
  */
HAL_StatusTypeDef HAL_SPI_DMAPause(SPI_HandleTypeDef *hspi)
{
  /* Process Locked */
  __HAL_LOCK(hspi);

  /* Check if the SPI is disabled to edit CFG1 register */
  if ((hspi->Instance->CR1 & SPI_CR1_SPE) != SPI_CR1_SPE)
  {
    /* Disable the SPI DMA Tx & Rx requests */
    CLEAR_BIT(hspi->Instance->CFG1, SPI_CFG1_TXDMAEN | SPI_CFG1_RXDMAEN);
  }
  else
  {
    /* Disable SPI peripheral */
    __HAL_SPI_DISABLE(hspi);

    /* Disable the SPI DMA Tx & Rx requests */
    CLEAR_BIT(hspi->Instance->CFG1, SPI_CFG1_TXDMAEN | SPI_CFG1_RXDMAEN);

    /* Enable SPI peripheral */
    __HAL_SPI_ENABLE(hspi);
  }

  /* Process Unlocked */
  __HAL_UNLOCK(hspi);

  return HAL_OK;
}

/**
  * @brief  Resume the DMA Transfer.
  * @param  hspi: pointer to a SPI_HandleTypeDef structure that contains
  *               the configuration information for the specified SPI module.
  * @retval HAL status
  */
HAL_StatusTypeDef HAL_SPI_DMAResume(SPI_HandleTypeDef *hspi)
{
  /* Process Locked */
  __HAL_LOCK(hspi);

  /* Check if the SPI is disabled to edit CFG1 register */
  if ((hspi->Instance->CR1 & SPI_CR1_SPE) != SPI_CR1_SPE)
  {
    /* Enable the SPI DMA Tx & Rx requests */
    SET_BIT(hspi->Instance->CFG1, SPI_CFG1_TXDMAEN | SPI_CFG1_RXDMAEN);
  }
  else
  {
    /* Disable SPI peripheral */
    __HAL_SPI_DISABLE(hspi);

    /* Enable the SPI DMA Tx & Rx requests */
    SET_BIT(hspi->Instance->CFG1, SPI_CFG1_TXDMAEN | SPI_CFG1_RXDMAEN);

    /* Enable SPI peripheral */
    __HAL_SPI_ENABLE(hspi);
  }

  /* Process Unlocked */
  __HAL_UNLOCK(hspi);

  return HAL_OK;
}

/**
  * @brief Stop the DMA Transfer.
  * @param  hspi: pointer to a SPI_HandleTypeDef structure that contains
  *               the configuration information for the specified SPI module.
  * @retval HAL status
  */
HAL_StatusTypeDef HAL_SPI_DMAStop(SPI_HandleTypeDef *hspi)
{
  /* The Lock is not implemented on this API to allow the user application
     to call the HAL SPI API under callbacks HAL_SPI_TxCpltCallback() or HAL_SPI_RxCpltCallback() or HAL_SPI_TxRxCpltCallback():
     when calling HAL_DMA_Abort() API the DMA TX/RX Transfer complete interrupt is generated
     and the correspond call back is executed HAL_SPI_TxCpltCallback() or HAL_SPI_RxCpltCallback() or HAL_SPI_TxRxCpltCallback()
     */

  /* Abort the SPI DMA tx Stream/Channel  */
  if (hspi->hdmatx != NULL)
  {
    HAL_DMA_Abort(hspi->hdmatx);
  }
  /* Abort the SPI DMA rx Stream/Channel  */
  if (hspi->hdmarx != NULL)
  {
    HAL_DMA_Abort(hspi->hdmarx);
  }


  /* Check if the SPI is disabled to edit CFG1 register */
  if ((hspi->Instance->CR1 & SPI_CR1_SPE) != SPI_CR1_SPE)
  {
    /* Disable the SPI DMA Tx & Rx requests */
    CLEAR_BIT(hspi->Instance->CFG1, SPI_CFG1_TXDMAEN | SPI_CFG1_RXDMAEN);
  }
  else
  {
    /* Disable SPI peripheral */
    __HAL_SPI_DISABLE(hspi);

    /* Disable the SPI DMA Tx & Rx requests */
    CLEAR_BIT(hspi->Instance->CFG1, SPI_CFG1_TXDMAEN | SPI_CFG1_RXDMAEN);

    /* Enable SPI peripheral */
    __HAL_SPI_ENABLE(hspi);
  }

  hspi->State = HAL_SPI_STATE_READY;
  return HAL_OK;
}

/**
  * @brief  Handle SPI interrupt request.
  * @param  hspi: pointer to a SPI_HandleTypeDef structure that contains
  *               the configuration information for the specified SPI module.
  * @retval None
  */
void HAL_SPI_IRQHandler(SPI_HandleTypeDef *hspi)
{
  uint32_t itsource = hspi->Instance->IER;
  uint32_t itflag   = hspi->Instance->SR;

  /* SPI in mode Receiver ----------------------------------------------------*/
  if (((itflag & SPI_FLAG_OVR) == RESET) &&
      ((itflag & SPI_FLAG_RXNE) != RESET) && ((itsource & SPI_IT_RXNE) != RESET))
  {
    hspi->RxISR(hspi);
    return;
  }
  
    /* SPI in mode Receiver ----------------------------------------------------*/
  if (((itflag & SPI_FLAG_EOT) != RESET) && ((itsource & SPI_IT_EOT) != RESET))
  {
    hspi->RxISR(hspi);
    return;
  }

  /* SPI in mode Transmitter -------------------------------------------------*/
  if(((itflag & SPI_FLAG_UDR) == RESET) &&
     ((itflag & SPI_FLAG_TXE) != RESET) && ((itsource & SPI_IT_TXE) != RESET))
  {
    hspi->TxISR(hspi);
    return;
  }

  /* SPI in Error Treatment --------------------------------------------------*/
  if (((itflag & (SPI_FLAG_MODF | SPI_FLAG_OVR | SPI_FLAG_FRE | SPI_FLAG_UDR)) != RESET) && ((itsource & SPI_IT_ERR) != RESET))
  {
    /* SPI Overrun error interrupt occurred ----------------------------------*/
    if ((itflag & SPI_FLAG_OVR) != RESET)
    {
      if (hspi->State != HAL_SPI_STATE_BUSY_TX)
      {
        SET_BIT(hspi->ErrorCode, HAL_SPI_ERROR_OVR);
        __HAL_SPI_CLEAR_OVRFLAG(hspi);
      }
      else
      {
        __HAL_SPI_CLEAR_OVRFLAG(hspi);
        return;
      }
    }

    /* SPI Mode Fault error interrupt occurred -------------------------------*/
    if ((itflag & SPI_FLAG_MODF) != RESET)
    {
      SET_BIT(hspi->ErrorCode, HAL_SPI_ERROR_MODF);
      __HAL_SPI_CLEAR_MODFFLAG(hspi);
    }

    /* SPI Frame error interrupt occurred ------------------------------------*/
    if ((itflag & SPI_FLAG_FRE) != RESET)
    {
      SET_BIT(hspi->ErrorCode, HAL_SPI_ERROR_FRE);
      __HAL_SPI_CLEAR_FREFLAG(hspi);
    }

    /* SPI Underrun error interrupt occurred ------------------------------------*/
    if ((itflag & SPI_FLAG_UDR) != RESET)
    {
      if (hspi->State != HAL_SPI_STATE_BUSY_RX)
      {
        SET_BIT(hspi->ErrorCode, HAL_SPI_ERROR_UDR);
        *((__IO uint8_t *)&hspi->Instance->TXDR) = 0x01U;
      __HAL_SPI_CLEAR_UDRFLAG(hspi);
      }
      else
      {
        __HAL_SPI_CLEAR_UDRFLAG(hspi);
        return;
      }
    }

    if (hspi->ErrorCode != HAL_SPI_ERROR_NONE)
    {
      /* Disable all interrupts */
      __HAL_SPI_DISABLE_IT(hspi, SPI_IT_RXNE | SPI_IT_TXE | SPI_IT_ERR);

      hspi->State = HAL_SPI_STATE_READY;
      /* Disable the SPI DMA requests if enabled */
      if ((HAL_IS_BIT_SET(itsource, SPI_CFG1_TXDMAEN)) || (HAL_IS_BIT_SET(itsource, SPI_CFG1_RXDMAEN)))
      {
        /* Check if the SPI is disabled to edit CFG1 register */
        if ((hspi->Instance->CR1 & SPI_CR1_SPE) != SPI_CR1_SPE)
        {
          /* Disable the SPI DMA requests */
          CLEAR_BIT(hspi->Instance->CR2, (SPI_CFG1_TXDMAEN | SPI_CFG1_RXDMAEN));
        }
        else
        {
          /* Disable SPI peripheral */
          __HAL_SPI_DISABLE(hspi);

          /* Disable the SPI DMA requests */
          CLEAR_BIT(hspi->Instance->CR2, (SPI_CFG1_TXDMAEN | SPI_CFG1_RXDMAEN));
      
          /* Enable SPI peripheral */
          __HAL_SPI_ENABLE(hspi);
        }

        /* Abort the SPI DMA Rx channel */
        if (hspi->hdmarx != NULL)
        {
          /* Set the SPI DMA Abort callback :
          will lead to call HAL_SPI_ErrorCallback() at end of DMA abort procedure */
          hspi->hdmarx->XferAbortCallback = SPI_DMAAbortOnError;
          HAL_DMA_Abort_IT(hspi->hdmarx);
        }
        /* Abort the SPI DMA Tx channel */
        if (hspi->hdmatx != NULL)
        {
          /* Set the SPI DMA Abort callback :
          will lead to call HAL_SPI_ErrorCallback() at end of DMA abort procedure */
          hspi->hdmatx->XferAbortCallback = SPI_DMAAbortOnError;
          HAL_DMA_Abort_IT(hspi->hdmatx);
        }
      }
      else
      {
        /* Call user error callback */
        HAL_SPI_ErrorCallback(hspi);
      }
    }
    return;
  }
}

/**
  * @brief Tx Transfer completed callback.
  * @param  hspi: pointer to a SPI_HandleTypeDef structure that contains
  *               the configuration information for SPI module.
  * @retval None
  */
__weak void HAL_SPI_TxCpltCallback(SPI_HandleTypeDef *hspi)
{
  /* Prevent unused argument(s) compilation warning */
  UNUSED(hspi);

  /* NOTE : This function should not be modified, when the callback is needed,
            the HAL_SPI_TxCpltCallback should be implemented in the user file
   */
}

/**
  * @brief Rx Transfer completed callback.
  * @param  hspi: pointer to a SPI_HandleTypeDef structure that contains
  *               the configuration information for SPI module.
  * @retval None
  */
__weak void HAL_SPI_RxCpltCallback(SPI_HandleTypeDef *hspi)
{
  /* Prevent unused argument(s) compilation warning */
  UNUSED(hspi);

  /* NOTE : This function should not be modified, when the callback is needed,
            the HAL_SPI_RxCpltCallback should be implemented in the user file
   */
}

/**
  * @brief Tx and Rx Transfer completed callback.
  * @param  hspi: pointer to a SPI_HandleTypeDef structure that contains
  *               the configuration information for SPI module.
  * @retval None
  */
__weak void HAL_SPI_TxRxCpltCallback(SPI_HandleTypeDef *hspi)
{
  /* Prevent unused argument(s) compilation warning */
  UNUSED(hspi);

  /* NOTE : This function should not be modified, when the callback is needed,
            the HAL_SPI_TxRxCpltCallback should be implemented in the user file
   */
}

/**
  * @brief Tx Half Transfer completed callback.
  * @param  hspi: pointer to a SPI_HandleTypeDef structure that contains
  *               the configuration information for SPI module.
  * @retval None
  */
__weak void HAL_SPI_TxHalfCpltCallback(SPI_HandleTypeDef *hspi)
{
  /* Prevent unused argument(s) compilation warning */
  UNUSED(hspi);

  /* NOTE : This function should not be modified, when the callback is needed,
            the HAL_SPI_TxHalfCpltCallback should be implemented in the user file
   */
}

/**
  * @brief Rx Half Transfer completed callback.
  * @param  hspi: pointer to a SPI_HandleTypeDef structure that contains
  *               the configuration information for SPI module.
  * @retval None
  */
__weak void HAL_SPI_RxHalfCpltCallback(SPI_HandleTypeDef *hspi)
{
  /* Prevent unused argument(s) compilation warning */
  UNUSED(hspi);

  /* NOTE : This function should not be modified, when the callback is needed,
            the HAL_SPI_RxHalfCpltCallback() should be implemented in the user file
   */
}

/**
  * @brief Tx and Rx Half Transfer callback.
  * @param  hspi: pointer to a SPI_HandleTypeDef structure that contains
  *               the configuration information for SPI module.
  * @retval None
  */
__weak void HAL_SPI_TxRxHalfCpltCallback(SPI_HandleTypeDef *hspi)
{
  /* Prevent unused argument(s) compilation warning */
  UNUSED(hspi);

  /* NOTE : This function should not be modified, when the callback is needed,
            the HAL_SPI_TxRxHalfCpltCallback() should be implemented in the user file
   */
}

/**
  * @brief SPI error callback.
  * @param  hspi: pointer to a SPI_HandleTypeDef structure that contains
  *               the configuration information for SPI module.
  * @retval None
  */
__weak void HAL_SPI_ErrorCallback(SPI_HandleTypeDef *hspi)
{
  /* Prevent unused argument(s) compilation warning */
  UNUSED(hspi);

  /* NOTE : This function should not be modified, when the callback is needed,
            the HAL_SPI_ErrorCallback should be implemented in the user file
   */
  /* NOTE : The ErrorCode parameter in the hspi handle is updated by the SPI processes
            and user can use HAL_SPI_GetError() API to check the latest error occurred
   */
}

/**
  * @brief  SPI Abort Complete callback.
  * @param  hspi SPI handle.
  * @retval None
  */
__weak void HAL_SPI_AbortCpltCallback(SPI_HandleTypeDef *hspi)
{
  /* Prevent unused argument(s) compilation warning */
  UNUSED(hspi);

  /* NOTE : This function should not be modified, when the callback is needed,
            the HAL_SPI_AbortCpltCallback can be implemented in the user file.
   */
}

/**
  * @}
  */

/** @defgroup SPI_Exported_Functions_Group3 Peripheral State and Errors functions
  * @brief   SPI control functions
  *
@verbatim
 ===============================================================================
                      ##### Peripheral State and Errors functions #####
 ===============================================================================
    [..]
    This subsection provides a set of functions allowing to control the SPI.
     (+) HAL_SPI_GetState() API can be helpful to check in run-time the state of the SPI peripheral
     (+) HAL_SPI_GetError() check in run-time Errors occurring during communication
@endverbatim
  * @{
  */

/**
  * @brief  Return the SPI handle state.
  * @param  hspi: pointer to a SPI_HandleTypeDef structure that contains
  *               the configuration information for SPI module.
  * @retval SPI state
  */
HAL_SPI_StateTypeDef HAL_SPI_GetState(SPI_HandleTypeDef *hspi)
{
  /* Return SPI handle state */
  return hspi->State;
}

/**
  * @brief  Return the SPI error code.
  * @param  hspi: pointer to a SPI_HandleTypeDef structure that contains
  *               the configuration information for SPI module.
  * @retval SPI error code in bitmap format
  */
uint32_t HAL_SPI_GetError(SPI_HandleTypeDef *hspi)
{
  /* Return SPI ErrorCode */
  return hspi->ErrorCode;
}

/**
  * @}
  */

/**
  * @}
  */

/** @addtogroup SPI_Private_Functions
  * @brief   Private functions
  * @{
  */

/**
  * @brief DMA SPI transmit process complete callback.
  * @param  hdma: pointer to a DMA_HandleTypeDef structure that contains
  *               the configuration information for the specified DMA module.
  * @retval None
  */
static void SPI_DMATransmitCplt(DMA_HandleTypeDef *hdma)
{
  SPI_HandleTypeDef *hspi = (SPI_HandleTypeDef *)((DMA_HandleTypeDef *)hdma)->Parent;

  /* DMA Normal Mode */
  if(((((DMA_Stream_TypeDef *)hdma->Instance)->CR) & (uint32_t)(DMA_SxCR_CIRC)) != DMA_SxCR_CIRC)
  {
    /* Disable ERR interrupt */
    __HAL_SPI_DISABLE_IT(hspi, SPI_IT_ERR);

    /* Check if the SPI is disabled to edit CFG1 register */
    if ((hspi->Instance->CR1 & SPI_CR1_SPE) != SPI_CR1_SPE)
    {
      /* Disable Tx DMA Request */
      CLEAR_BIT(hspi->Instance->CFG1, SPI_CFG1_TXDMAEN);
    }
    else
    {
      /* Disable SPI peripheral */
      __HAL_SPI_DISABLE(hspi);

      /* Disable Tx DMA Request */
      CLEAR_BIT(hspi->Instance->CFG1, SPI_CFG1_TXDMAEN);
  
      /* Enable SPI peripheral */
      __HAL_SPI_ENABLE(hspi);
    }

    __HAL_SPI_CLEAR_EOTFLAG(hspi);
    __HAL_SPI_CLEAR_TXTFFLAG(hspi);

    /* Clear overrun flag in 2 Lines communication mode because received data is not read */
    if (hspi->Init.Direction == SPI_DIRECTION_2LINES)
    {
      __HAL_SPI_CLEAR_OVRFLAG(hspi);
    }

    /* Clear underrun flag in 1 Line communication mode because transmitted is not feeded */
    if (hspi->Init.Direction == SPI_DIRECTION_1LINE)
    {
      __HAL_SPI_CLEAR_UDRFLAG(hspi);
    }

    hspi->TxXferCount = 0U;
    hspi->State = HAL_SPI_STATE_READY;

    if (hspi->ErrorCode != HAL_SPI_ERROR_NONE)
    {
      HAL_SPI_ErrorCallback(hspi);
      return;
    }
  }
  HAL_SPI_TxCpltCallback(hspi);
}

/**
  * @brief DMA SPI receive process complete callback.
  * @param  hdma: pointer to a DMA_HandleTypeDef structure that contains
  *               the configuration information for the specified DMA module.
  * @retval None
  */
static void SPI_DMAReceiveCplt(DMA_HandleTypeDef *hdma)
{
  SPI_HandleTypeDef *hspi = (SPI_HandleTypeDef *)((DMA_HandleTypeDef *)hdma)->Parent;

  /* DMA Normal Mode */
  if(((((DMA_Stream_TypeDef *)hdma->Instance)->CR) & (uint32_t)(DMA_SxCR_CIRC)) != DMA_SxCR_CIRC)
  {
    /* Disable ERR interrupt */
    __HAL_SPI_DISABLE_IT(hspi, SPI_IT_ERR);

    /* Check if the SPI is disabled to edit CFG1 register */
    if ((hspi->Instance->CR1 & SPI_CR1_SPE) != SPI_CR1_SPE)
    {
      /* Disable Rx/Tx DMA Request (done by default to handle the case master rx direction 2 lines) */
      CLEAR_BIT(hspi->Instance->CFG1, SPI_CFG1_TXDMAEN | SPI_CFG1_RXDMAEN);
    }
    else
    {
      /* Disable SPI peripheral */
      __HAL_SPI_DISABLE(hspi);

      /* Disable Rx/Tx DMA Request (done by default to handle the case master rx direction 2 lines) */
      CLEAR_BIT(hspi->Instance->CFG1, SPI_CFG1_TXDMAEN | SPI_CFG1_RXDMAEN);
  
      /* Enable SPI peripheral */
      __HAL_SPI_ENABLE(hspi);
    }

    __HAL_SPI_CLEAR_EOTFLAG(hspi);
    __HAL_SPI_CLEAR_TXTFFLAG(hspi);

    hspi->RxXferCount = 0U;
    hspi->State = HAL_SPI_STATE_READY;

#ifdef USE_SPI_CRC
    /* Check if CRC error occurred */
    if (__HAL_SPI_GET_FLAG(hspi, SPI_FLAG_CRCERR))
    {
      SET_BIT(hspi->ErrorCode, HAL_SPI_ERROR_CRC);
      __HAL_SPI_CLEAR_CRCERRFLAG(hspi);
    }
#endif /* USE_SPI_CRC */

    if (hspi->ErrorCode != HAL_SPI_ERROR_NONE)
    {
      HAL_SPI_ErrorCallback(hspi);
      return;
    }
  }
  HAL_SPI_RxCpltCallback(hspi);
}

/**
  * @brief  DMA SPI transmit receive process complete callback.
  * @param  hdma: pointer to a DMA_HandleTypeDef structure that contains
  *               the configuration information for the specified DMA module.
  * @retval None
  */
static void SPI_DMATransmitReceiveCplt(DMA_HandleTypeDef *hdma)
{
  SPI_HandleTypeDef *hspi = (SPI_HandleTypeDef *)((DMA_HandleTypeDef *)hdma)->Parent;
  uint32_t tickstart = 0U;

  /* Init tickstart for timeout management*/
  tickstart = HAL_GetTick();

  /* DMA Normal Mode */
  if(((((DMA_Stream_TypeDef *)hdma->Instance)->CR) & (uint32_t)(DMA_SxCR_CIRC)) != DMA_SxCR_CIRC)
  {
    /* Disable ERR interrupt */
    __HAL_SPI_DISABLE_IT(hspi, SPI_IT_ERR);

    /* Check the end of the transaction */
     if (SPI_EndRxTxTransaction(hspi, SPI_DEFAULT_TIMEOUT, tickstart) != HAL_OK)
    {
      SET_BIT(hspi->ErrorCode, HAL_SPI_ERROR_FLAG);
    }

    /* Check if the SPI is disabled to edit CFG1 register */
    if ((hspi->Instance->CR1 & SPI_CR1_SPE) != SPI_CR1_SPE)
    {
      /* Disable Rx/Tx DMA Request */
      CLEAR_BIT(hspi->Instance->CFG1, SPI_CFG1_TXDMAEN | SPI_CFG1_RXDMAEN);
    }
    else
    {
      /* Disable SPI peripheral */
      __HAL_SPI_DISABLE(hspi);

      /* Disable Rx/Tx DMA Request */
      CLEAR_BIT(hspi->Instance->CFG1, SPI_CFG1_TXDMAEN | SPI_CFG1_RXDMAEN);
  
      /* Enable SPI peripheral */
      __HAL_SPI_ENABLE(hspi);
    }

    hspi->TxXferCount = 0U;
    hspi->RxXferCount = 0U;
    hspi->State = HAL_SPI_STATE_READY;

#ifdef USE_SPI_CRC
    /* Check if CRC error occurred */
    if (__HAL_SPI_GET_FLAG(hspi, SPI_FLAG_CRCERR))
    {
      SET_BIT(hspi->ErrorCode, HAL_SPI_ERROR_CRC);
      __HAL_SPI_CLEAR_CRCERRFLAG(hspi);
    }
#endif /* USE_SPI_CRC */

    if (hspi->ErrorCode != HAL_SPI_ERROR_NONE)
    {
      HAL_SPI_ErrorCallback(hspi);
      return;
    }
  }
  HAL_SPI_TxRxCpltCallback(hspi);
}

/**
  * @brief  DMA SPI half transmit process complete callback.
  * @param  hdma: pointer to a DMA_HandleTypeDef structure that contains
  *               the configuration information for the specified DMA module.
  * @retval None
  */
static void SPI_DMAHalfTransmitCplt(DMA_HandleTypeDef *hdma)
{
  SPI_HandleTypeDef *hspi = (SPI_HandleTypeDef *)((DMA_HandleTypeDef *)hdma)->Parent;

  HAL_SPI_TxHalfCpltCallback(hspi);
}

/**
  * @brief  DMA SPI half receive process complete callback
  * @param  hdma: pointer to a DMA_HandleTypeDef structure that contains
  *               the configuration information for the specified DMA module.
  * @retval None
  */
static void SPI_DMAHalfReceiveCplt(DMA_HandleTypeDef *hdma)
{
  SPI_HandleTypeDef *hspi = (SPI_HandleTypeDef *)((DMA_HandleTypeDef *)hdma)->Parent;

  HAL_SPI_RxHalfCpltCallback(hspi);
}

/**
  * @brief  DMA SPI half transmit receive process complete callback.
  * @param  hdma: pointer to a DMA_HandleTypeDef structure that contains
  *               the configuration information for the specified DMA module.
  * @retval None
  */
static void SPI_DMAHalfTransmitReceiveCplt(DMA_HandleTypeDef *hdma)
{
  SPI_HandleTypeDef *hspi = (SPI_HandleTypeDef *)((DMA_HandleTypeDef *)hdma)->Parent;

  HAL_SPI_TxRxHalfCpltCallback(hspi);
}

/**
  * @brief  DMA SPI communication error callback.
  * @param  hdma: pointer to a DMA_HandleTypeDef structure that contains
  *               the configuration information for the specified DMA module.
  * @retval None
  */
static void SPI_DMAError(DMA_HandleTypeDef *hdma)
{
  SPI_HandleTypeDef *hspi = (SPI_HandleTypeDef *)((DMA_HandleTypeDef *)hdma)->Parent;

  /* Check if the SPI is disabled to edit CFG1 register */
  if ((hspi->Instance->CR1 & SPI_CR1_SPE) != SPI_CR1_SPE)
  {
    /* Stop the disable DMA transfer on SPI side */
    CLEAR_BIT(hspi->Instance->CFG1, SPI_CFG1_TXDMAEN | SPI_CFG1_RXDMAEN);
  }
  else
  {
    /* Disable SPI peripheral */
    __HAL_SPI_DISABLE(hspi);

    /* Stop the disable DMA transfer on SPI side */
    CLEAR_BIT(hspi->Instance->CFG1, SPI_CFG1_TXDMAEN | SPI_CFG1_RXDMAEN);

    /* Enable SPI peripheral */
    __HAL_SPI_ENABLE(hspi);
  }
 
  SET_BIT(hspi->ErrorCode, HAL_SPI_ERROR_DMA);
  hspi->State = HAL_SPI_STATE_READY;
  HAL_SPI_ErrorCallback(hspi);
}

/**
  * @brief  DMA SPI communication abort callback, when initiated by HAL services on Error
  *         (To be called at end of DMA Abort procedure following error occurrence).
  * @param  hdma DMA handle.
  * @retval None
  */
static void SPI_DMAAbortOnError(DMA_HandleTypeDef *hdma)
{
  SPI_HandleTypeDef *hspi = (SPI_HandleTypeDef *)((DMA_HandleTypeDef *)hdma)->Parent;
  hspi->RxXferCount = 0U;
  hspi->TxXferCount = 0U;

  HAL_SPI_ErrorCallback(hspi);
}

/**
  * @brief  DMA SPI Tx communication abort callback, when initiated by user
  *         (To be called at end of DMA Tx Abort procedure following user abort request).
  * @note   When this callback is executed, User Abort complete call back is called only if no
  *         Abort still ongoing for Rx DMA Handle.
  * @param  hdma DMA handle.
  * @retval None
  */
static void SPI_DMATxAbortCallback(DMA_HandleTypeDef *hdma)
{
  SPI_HandleTypeDef *hspi = (SPI_HandleTypeDef *)((DMA_HandleTypeDef *)hdma)->Parent;

  hspi->hdmatx->XferAbortCallback = NULL;

  /* Check if the SPI is disabled to edit CFG1 register */
  if ((hspi->Instance->CR1 & SPI_CR1_SPE) != SPI_CR1_SPE)
  {
    /* Disable Tx DMA Request */
    CLEAR_BIT(hspi->Instance->CFG1, SPI_CFG1_TXDMAEN);
  }
  else
  {
    /* Disable SPI peripheral */
    __HAL_SPI_DISABLE(hspi);

    /* Disable Tx DMA Request */
    CLEAR_BIT(hspi->Instance->CFG1, SPI_CFG1_TXDMAEN);

    /* Enable SPI peripheral */
    __HAL_SPI_ENABLE(hspi);
  }

  if (SPI_EndRxTxTransaction(hspi, SPI_DEFAULT_TIMEOUT, HAL_GetTick()) != HAL_OK)
  {
    hspi->ErrorCode = HAL_SPI_ERROR_ABORT;
  }

  /* Disable SPI Peripheral */
  __HAL_SPI_DISABLE(hspi);

  /* Empty the FRLVL fifo */
  if (SPI_WaitFifoStateUntilTimeout(hspi, SPI_FLAG_FRLVL, SPI_FRLVL_EMPTY, SPI_DEFAULT_TIMEOUT, HAL_GetTick()) != HAL_OK)
  {
    hspi->ErrorCode = HAL_SPI_ERROR_ABORT;
  }

  /* Check if an Abort process is still ongoing */
  if (hspi->hdmarx != NULL)
  {
    if (hspi->hdmarx->XferAbortCallback != NULL)
    {
      return;
    }
  }

  /* No Abort process still ongoing : All DMA Stream/Channel are aborted, call user Abort Complete callback */
  hspi->RxXferCount = 0U;
  hspi->TxXferCount = 0U;

  /* Check no error during Abort procedure */
  if (hspi->ErrorCode != HAL_SPI_ERROR_ABORT)
  {
    /* Reset errorCode */
    hspi->ErrorCode = HAL_SPI_ERROR_NONE;
  }

  /* Clear the Error flags in the SR register */
  __HAL_SPI_CLEAR_OVRFLAG(hspi);
  __HAL_SPI_CLEAR_FREFLAG(hspi);
  __HAL_SPI_CLEAR_UDRFLAG(hspi);

  /* Restore hspi->State to Ready */
  hspi->State  = HAL_SPI_STATE_READY;

  /* Call user Abort complete callback */
  HAL_SPI_AbortCpltCallback(hspi);
}

/**
  * @brief  DMA SPI Rx communication abort callback, when initiated by user
  *         (To be called at end of DMA Rx Abort procedure following user abort request).
  * @note   When this callback is executed, User Abort complete call back is called only if no
  *         Abort still ongoing for Tx DMA Handle.
  * @param  hdma DMA handle.
  * @retval None
  */
static void SPI_DMARxAbortCallback(DMA_HandleTypeDef *hdma)
{
  SPI_HandleTypeDef *hspi = (SPI_HandleTypeDef *)((DMA_HandleTypeDef *)hdma)->Parent;

  /* Disable SPI Peripheral */
  __HAL_SPI_DISABLE(hspi);

  hspi->hdmarx->XferAbortCallback = NULL;

  /* Check if the SPI is disabled to edit CFG1 register */
  if ((hspi->Instance->CR1 & SPI_CR1_SPE) != SPI_CR1_SPE)
  {
    /* Disable Rx DMA Request */
    CLEAR_BIT(hspi->Instance->CFG1, SPI_CFG1_RXDMAEN);
  }
  else
  {
    /* Disable SPI peripheral */
    __HAL_SPI_DISABLE(hspi);

    /* Disable Rx DMA Request */
    CLEAR_BIT(hspi->Instance->CFG1, SPI_CFG1_RXDMAEN);

    /* Enable SPI peripheral */
    __HAL_SPI_ENABLE(hspi);
  }

  /* Empty the FRLVL fifo */
  if (SPI_WaitFifoStateUntilTimeout(hspi, SPI_FLAG_FRLVL, SPI_FRLVL_EMPTY, SPI_DEFAULT_TIMEOUT, HAL_GetTick()) != HAL_OK)
  {
    hspi->ErrorCode = HAL_SPI_ERROR_ABORT;
  }

  /* Check if an Abort process is still ongoing */
  if (hspi->hdmatx != NULL)
  {
    if (hspi->hdmatx->XferAbortCallback != NULL)
    {
      return;
    }
  }

  /* No Abort process still ongoing : All DMA Stream/Channel are aborted, call user Abort Complete callback */
  hspi->RxXferCount = 0U;
  hspi->TxXferCount = 0U;

  /* Check no error during Abort procedure */
  if (hspi->ErrorCode != HAL_SPI_ERROR_ABORT)
  {
    /* Reset errorCode */
    hspi->ErrorCode = HAL_SPI_ERROR_NONE;
  }

  /* Clear the Error flags in the SR register */
  __HAL_SPI_CLEAR_OVRFLAG(hspi);
  __HAL_SPI_CLEAR_FREFLAG(hspi);
  __HAL_SPI_CLEAR_UDRFLAG(hspi);

  /* Restore hspi->State to Ready */
  hspi->State  = HAL_SPI_STATE_READY;

  /* Call user Abort complete callback */
  HAL_SPI_AbortCpltCallback(hspi);
}

/**
  * @brief  Rx 8-bit handler for Transmit and Receive in Interrupt mode.
  * @param  hspi: pointer to a SPI_HandleTypeDef structure that contains
  *               the configuration information for SPI module.
  * @retval None
  */
static void SPI_2linesRxISR_8BIT(struct __SPI_HandleTypeDef *hspi)
{
  /* Receive data in 8 Bit mode */
  if (hspi->RxXferCount > 0U)
  {
    *hspi->pRxBuffPtr = *((__IO uint8_t *)&hspi->Instance->RXDR);
    hspi->pRxBuffPtr += sizeof(uint8_t);
    hspi->RxXferCount--;
  }

  /* check end of the reception */
  if (hspi->RxXferCount == 0U)
  {
    /* Disable RXNE interrupt */
    __HAL_SPI_DISABLE_IT(hspi, (SPI_IT_RXNE));

    if (hspi->TxXferCount == 0U)
    {
      SPI_CloseRxTx_ISR(hspi);
    }
  }
}


/**
  * @brief  Rx 16-bit handler for Transmit and Receive in Interrupt mode.
  * @param  hspi: pointer to a SPI_HandleTypeDef structure that contains
  *               the configuration information for SPI module.
  * @retval None
  */
static void SPI_2linesRxISR_16BIT(struct __SPI_HandleTypeDef *hspi)
{
  /* Receive data in 16 Bit mode */
  *((uint16_t *)hspi->pRxBuffPtr) = hspi->Instance->RXDR;
  hspi->pRxBuffPtr += sizeof(uint16_t);
  hspi->RxXferCount--;

  if (hspi->RxXferCount == 0U)
  {
    /* Disable RXNE interrupt */
    __HAL_SPI_DISABLE_IT(hspi, SPI_IT_RXNE);

    if (hspi->TxXferCount == 0U)
    {
      SPI_CloseRxTx_ISR(hspi);
    }
  }
}


/**
  * @brief  Rx 32-bit handler for Transmit and Receive in Interrupt mode.
  * @param  hspi: pointer to a SPI_HandleTypeDef structure that contains
  *               the configuration information for SPI module.
  * @retval None
  */
static void SPI_2linesRxISR_32BIT(struct __SPI_HandleTypeDef *hspi)
{
  /* Receive data in 32 Bit mode */
  *((uint32_t *)hspi->pRxBuffPtr) = hspi->Instance->RXDR;
  hspi->pRxBuffPtr += sizeof(uint32_t);
  hspi->RxXferCount--;

  if (hspi->RxXferCount == 0U)
  {
    /* Disable RXNE interrupt */
    __HAL_SPI_DISABLE_IT(hspi, SPI_IT_RXNE);

    if (hspi->TxXferCount == 0U)
    {
      SPI_CloseRxTx_ISR(hspi);
    }
  }
}


/**
  * @brief  Tx 8-bit handler for Transmit and Receive in Interrupt mode.
  * @param  hspi: pointer to a SPI_HandleTypeDef structure that contains
  *               the configuration information for SPI module.
  * @retval None
  */
static void SPI_2linesTxISR_8BIT(struct __SPI_HandleTypeDef *hspi)
{
  /* Transmit data in 8 Bit mode */
  if (hspi->TxXferCount > 0U)
  {
    *(__IO uint8_t *)&hspi->Instance->TXDR = *hspi->pTxBuffPtr;
    hspi->pTxBuffPtr += sizeof(uint8_t);
    hspi->TxXferCount--;
  }

  /* check the end of the transmission */
  if (hspi->TxXferCount == 0U)
  {
    /* Disable TXE interrupt */
    __HAL_SPI_DISABLE_IT(hspi, SPI_IT_TXE);

    if (hspi->RxXferCount == 0U)
    {
      SPI_CloseRxTx_ISR(hspi);
    }
  }
}


/**
  * @brief  Tx 16-bit handler for Transmit and Receive in Interrupt mode.
  * @param  hspi: pointer to a SPI_HandleTypeDef structure that contains
  *               the configuration information for SPI module.
  * @retval None
  */
static void SPI_2linesTxISR_16BIT(struct __SPI_HandleTypeDef *hspi)
{
  /* Transmit data in 16 Bit mode */
  *((__IO uint16_t *)&hspi->Instance->TXDR) = *((uint16_t *)hspi->pTxBuffPtr);
  hspi->pTxBuffPtr += sizeof(uint16_t);
  hspi->TxXferCount--;

  /* Enable CRC Transmission */
  if (hspi->TxXferCount == 0U)
  {
    /* Disable TXE interrupt */
    __HAL_SPI_DISABLE_IT(hspi, SPI_IT_TXE);

    if (hspi->RxXferCount == 0U)
    {
      SPI_CloseRxTx_ISR(hspi);
    }
  }
}


/**
  * @brief  Tx 32-bit handler for Transmit and Receive in Interrupt mode.
  * @param  hspi: pointer to a SPI_HandleTypeDef structure that contains
  *               the configuration information for SPI module.
  * @retval None
  */
static void SPI_2linesTxISR_32BIT(struct __SPI_HandleTypeDef *hspi)
{
  /* Transmit data in 32 Bit mode */
  *((__IO uint32_t *)&hspi->Instance->TXDR) = *((uint32_t *)hspi->pTxBuffPtr);
  hspi->pTxBuffPtr += sizeof(uint32_t);
  hspi->TxXferCount--;

  /* Enable CRC Transmission */
  if (hspi->TxXferCount == 0U)
  {
    /* Disable TXE interrupt */
    __HAL_SPI_DISABLE_IT(hspi, SPI_IT_TXE);

    if (hspi->RxXferCount == 0U)
    {
      SPI_CloseRxTx_ISR(hspi);
    }
  }
}


/**
  * @brief  Manage the receive 8-bit in Interrupt context.
  * @param  hspi: pointer to a SPI_HandleTypeDef structure that contains
  *               the configuration information for SPI module.
  * @retval None
  */
static void SPI_RxISR_8BIT(struct __SPI_HandleTypeDef *hspi)
{
  *hspi->pRxBuffPtr = (*(__IO uint8_t *)&hspi->Instance->RXDR);
  hspi->pRxBuffPtr += sizeof(uint8_t);
  hspi->RxXferCount--;

  if (hspi->RxXferCount == 0U)
  {
    SPI_CloseRx_ISR(hspi);
  }
}


/**
  * @brief  Manage the 16-bit receive in Interrupt context.
  * @param  hspi: pointer to a SPI_HandleTypeDef structure that contains
  *               the configuration information for SPI module.
  * @retval None
  */
static void SPI_RxISR_16BIT(struct __SPI_HandleTypeDef *hspi)
{
  *((uint16_t *)hspi->pRxBuffPtr) = hspi->Instance->RXDR;
  hspi->pRxBuffPtr += sizeof(uint16_t);
  hspi->RxXferCount--;

  if (hspi->RxXferCount == 0U)
  {
    SPI_CloseRx_ISR(hspi);
  }
}


/**
  * @brief  Manage the 32-bit receive in Interrupt context.
  * @param  hspi: pointer to a SPI_HandleTypeDef structure that contains
  *               the configuration information for SPI module.
  * @retval None
  */
static void SPI_RxISR_32BIT(struct __SPI_HandleTypeDef *hspi)
{
  *((uint32_t *)hspi->pRxBuffPtr) = hspi->Instance->RXDR;
  hspi->pRxBuffPtr += sizeof(uint32_t);
  hspi->RxXferCount--;

  if (hspi->RxXferCount == 0U)
  {
    SPI_CloseRx_ISR(hspi);
  }
}


/**
  * @brief  Handle the data 8-bit transmit in Interrupt mode.
  * @param  hspi: pointer to a SPI_HandleTypeDef structure that contains
  *               the configuration information for SPI module.
  * @retval None
  */
static void SPI_TxISR_8BIT(struct __SPI_HandleTypeDef *hspi)
{
  *(__IO uint8_t *)&hspi->Instance->TXDR = *((uint8_t *)hspi->pTxBuffPtr);
  hspi->pTxBuffPtr += sizeof(uint8_t);
  hspi->TxXferCount--;

  if (hspi->TxXferCount == 0U)
  {
    SPI_CloseTx_ISR(hspi);
  }
}

/**
  * @brief  Handle the data 16-bit transmit in Interrupt mode.
  * @param  hspi: pointer to a SPI_HandleTypeDef structure that contains
  *               the configuration information for SPI module.
  * @retval None
  */
static void SPI_TxISR_16BIT(struct __SPI_HandleTypeDef *hspi)
{
  /* Transmit data in 16 Bit mode */
  *((__IO uint16_t *)&hspi->Instance->TXDR) = *((uint16_t *)hspi->pTxBuffPtr);
  hspi->pTxBuffPtr += sizeof(uint16_t);
  hspi->TxXferCount--;

  if (hspi->TxXferCount == 0U)
  {
    SPI_CloseTx_ISR(hspi);
  }
}

/**
  * @brief  Handle the data 32-bit transmit in Interrupt mode.
  * @param  hspi: pointer to a SPI_HandleTypeDef structure that contains
  *               the configuration information for SPI module.
  * @retval None
  */
static void SPI_TxISR_32BIT(struct __SPI_HandleTypeDef *hspi)
{
  /* Transmit data in 16 Bit mode */
  *((__IO uint32_t *)&hspi->Instance->TXDR) = *((uint32_t *)hspi->pTxBuffPtr);
  hspi->pTxBuffPtr += sizeof(uint32_t);
  hspi->TxXferCount--;

  if (hspi->TxXferCount == 0U)
  {
    SPI_CloseTx_ISR(hspi);
  }
}


/**
  * @brief Handle SPI Communication Timeout.
  * @param hspi: pointer to a SPI_HandleTypeDef structure that contains
  *              the configuration information for SPI module.
  * @param Flag: SPI flag to check
  * @param State: flag state to check
  * @param Timeout: Timeout duration
  * @param Tickstart: Tick start value
  * @retval HAL status
  */
static HAL_StatusTypeDef SPI_WaitFlagStateUntilTimeout(SPI_HandleTypeDef *hspi, uint32_t Flag, uint32_t State,
                                                       uint32_t Timeout, uint32_t Tickstart)
{
  while ((hspi->Instance->SR & Flag) != State)
  {
    if (Timeout != HAL_MAX_DELAY)
    {
      if ((Timeout == 0U) || ((HAL_GetTick() - Tickstart) >= Timeout))
      {
        /* Disable TXE, RXNE and ERR interrupts for the interrupt process */
        __HAL_SPI_DISABLE_IT(hspi, (SPI_IT_TXE | SPI_IT_RXNE | SPI_IT_ERR));

        if ((hspi->Init.Mode == SPI_MODE_MASTER) && ((hspi->Init.Direction == SPI_DIRECTION_1LINE)
                                                     || (hspi->Init.Direction == SPI_DIRECTION_2LINES_RXONLY)))
        {
          /* Disable SPI peripheral */
          __HAL_SPI_DISABLE(hspi);
        }

        hspi->State = HAL_SPI_STATE_READY;

        /* Process Unlocked */
        __HAL_UNLOCK(hspi);

        return HAL_TIMEOUT;
      }
    }
  }

  return HAL_OK;
}

/**
  * @brief Handle SPI FIFO Communication Timeout.
  * @param hspi: pointer to a SPI_HandleTypeDef structure that contains
  *              the configuration information for SPI module.
  * @param Fifo: Fifo to check
  * @param State: Fifo state to check
  * @param Timeout: Timeout duration
  * @param Tickstart: tick start value
  * @retval HAL status
  */
static HAL_StatusTypeDef SPI_WaitFifoStateUntilTimeout(SPI_HandleTypeDef *hspi, uint32_t Fifo, uint32_t State,
                                                       uint32_t Timeout, uint32_t Tickstart)
{
  while ((hspi->Instance->SR & Fifo) != State)
  {
    if (Timeout != HAL_MAX_DELAY)
    {
      if ((Timeout == 0) || ((HAL_GetTick() - Tickstart) >= Timeout))
      {
        /* Disable the SPI and reset the CRC: the CRC value should be cleared
           on both master and slave sides in order to resynchronize the master
           and slave for their respective CRC calculation */

        /* Disable TXE, RXNE and ERR interrupts for the interrupt process */
        __HAL_SPI_DISABLE_IT(hspi, (SPI_IT_TXE | SPI_IT_RXNE | SPI_IT_ERR));

        if ((hspi->Init.Mode == SPI_MODE_MASTER) && ((hspi->Init.Direction == SPI_DIRECTION_1LINE)
                                                     || (hspi->Init.Direction == SPI_DIRECTION_2LINES_RXONLY)))
        {
          /* Disable SPI peripheral */
          __HAL_SPI_DISABLE(hspi);
        }

        hspi->State = HAL_SPI_STATE_READY;

        /* Process Unlocked */
        __HAL_UNLOCK(hspi);

        return HAL_TIMEOUT;
      }
    }
  }

  return HAL_OK;
}

/**
  * @brief  Handle the check of the RX transaction complete.
  * @param  hspi: pointer to a SPI_HandleTypeDef structure that contains
  *               the configuration information for SPI module.
  * @param  Timeout: Timeout duration
  * @param  Tickstart: tick start value
  * @retval None.
  */
static HAL_StatusTypeDef SPI_EndRxTransaction(SPI_HandleTypeDef *hspi,  uint32_t Timeout, uint32_t Tickstart)
{
    /* wait for Tx data to be sent */
  if (SPI_WaitFlagStateUntilTimeout(hspi, SPI_FLAG_EOT, SPI_FLAG_EOT, SPI_DEFAULT_TIMEOUT, Tickstart) != HAL_OK)
  {
    SET_BIT(hspi->ErrorCode, HAL_SPI_ERROR_FLAG);
    return HAL_TIMEOUT;
  }
  else
  {
    __HAL_SPI_CLEAR_EOTFLAG(hspi);
    __HAL_SPI_CLEAR_TXTFFLAG(hspi);
  }
  
  while ( (hspi->Instance->SR & SPI_FLAG_RXWNE) || ((hspi->Instance->SR & SPI_FLAG_FRLVL) != SPI_FRLVL_EMPTY))
  {
    /* Receive data in 32 Bit mode */
    if (hspi->Init.DataSize > SPI_DATASIZE_16BIT)
    {
      *((uint32_t *)hspi->pRxBuffPtr) = *((__IO uint32_t *)&hspi->Instance->RXDR);
      hspi->pRxBuffPtr += sizeof(uint32_t);
      hspi->RxXferCount--;
    }
    /* Receive data in 16 Bit mode */
    else if (hspi->Init.DataSize > SPI_DATASIZE_8BIT)
    {
      if ((hspi->Instance->SR & SPI_FLAG_RXWNE) && IS_SPI_HIGHEND_INSTANCE(hspi->Instance))
      {
        *((uint32_t *)hspi->pRxBuffPtr) = *((__IO uint32_t *)&hspi->Instance->RXDR);
        hspi->pRxBuffPtr += sizeof(uint32_t);
        hspi->RxXferCount-=2;
      }
      else
      {
        *((uint16_t *)hspi->pRxBuffPtr) = *((__IO uint16_t *)&hspi->Instance->RXDR);
        hspi->pRxBuffPtr += sizeof(uint16_t);
        hspi->RxXferCount--;
      }
    }
    /* Receive data in 8 Bit mode */
    else
    {
      if ((hspi->Instance->SR & SPI_FLAG_RXWNE) && IS_SPI_HIGHEND_INSTANCE(hspi->Instance))
      {
        *((uint32_t *)hspi->pRxBuffPtr) = *((__IO uint32_t *)&hspi->Instance->RXDR);
        hspi->pRxBuffPtr += sizeof(uint32_t);
        hspi->RxXferCount-=4;
      }
      else if ((hspi->Instance->SR & SPI_FLAG_FRLVL) > SPI_FRLVL_QUARTER_FULL)
      {
        *((uint16_t *)hspi->pRxBuffPtr) = *((__IO uint16_t *)&hspi->Instance->RXDR);
        hspi->pRxBuffPtr += sizeof(uint16_t);
        hspi->RxXferCount-=2;
      }
      else
      {
        (*hspi->pRxBuffPtr) = *((__IO uint8_t *)&hspi->Instance->RXDR);
        hspi->pRxBuffPtr += sizeof(uint8_t);
        hspi->RxXferCount--;
      }
    }
  }

  return HAL_OK;
}

/**
  * @brief Handle the check of the RXTX or TX transaction complete.
  * @param hspi: SPI handle
  * @param Timeout: Timeout duration
  * @param Tickstart: tick start value
  */
static HAL_StatusTypeDef SPI_EndRxTxTransaction(SPI_HandleTypeDef *hspi, uint32_t Timeout, uint32_t Tickstart)
{
  /* wait for Tx data to be sent */
  if (SPI_WaitFlagStateUntilTimeout(hspi, SPI_FLAG_EOT, SPI_FLAG_EOT, SPI_DEFAULT_TIMEOUT, Tickstart) != HAL_OK)
  {
    SET_BIT(hspi->ErrorCode, HAL_SPI_ERROR_FLAG);
    return HAL_TIMEOUT;
  }
  else
  {
    __HAL_SPI_CLEAR_EOTFLAG(hspi);
    __HAL_SPI_CLEAR_TXTFFLAG(hspi);
  }

  if (IS_SPI_HIGHEND_INSTANCE(hspi->Instance))
  {
    while ( (hspi->Instance->SR & SPI_FLAG_RXWNE) || ((hspi->Instance->SR & SPI_FLAG_FRLVL) != SPI_FRLVL_EMPTY))
    {
      if (hspi->RxXferCount != 0)
      {
        /* Receive data in 32 Bit mode */
        if (hspi->Init.DataSize > SPI_DATASIZE_16BIT)
        {
          *((uint32_t *)hspi->pRxBuffPtr) = *((__IO uint32_t *)&hspi->Instance->RXDR);
          hspi->pRxBuffPtr += sizeof(uint32_t);
          hspi->RxXferCount--;
        }
        /* Receive data in 16 Bit mode */
        else if (hspi->Init.DataSize > SPI_DATASIZE_8BIT)
        {
          if (hspi->Instance->SR & SPI_FLAG_RXWNE)
          {
            *((uint32_t *)hspi->pRxBuffPtr) = *((__IO uint32_t *)&hspi->Instance->RXDR);
            hspi->pRxBuffPtr += sizeof(uint32_t);
            hspi->RxXferCount-=2;
          }
          else
          {
            *((uint16_t *)hspi->pRxBuffPtr) = *((__IO uint16_t *)&hspi->Instance->RXDR);
            hspi->pRxBuffPtr += sizeof(uint16_t);
            hspi->RxXferCount--;
          }
        }
        /* Receive data in 8 Bit mode */
        else
        {
          if (hspi->Instance->SR & SPI_FLAG_RXWNE)
          {
            *((uint32_t *)hspi->pRxBuffPtr) = *((__IO uint32_t *)&hspi->Instance->RXDR);
            hspi->pRxBuffPtr += sizeof(uint32_t);
            hspi->RxXferCount-=4;
          }
          else if ((hspi->Instance->SR & SPI_FLAG_FRLVL) > SPI_FRLVL_QUARTER_FULL)
          {
            *((uint16_t *)hspi->pRxBuffPtr) = *((__IO uint16_t *)&hspi->Instance->RXDR);
            hspi->pRxBuffPtr += sizeof(uint16_t);
            hspi->RxXferCount-=2;
          }
          else
          {
            (*hspi->pRxBuffPtr) = *((__IO uint8_t *)&hspi->Instance->RXDR);
            hspi->pRxBuffPtr += sizeof(uint8_t);
            hspi->RxXferCount--;
          }
        }
      }
      else
      {
        return  HAL_SPIEx_FlushRxFifo(hspi);
      }
    }
  }

  return HAL_OK;
}

/**
  * @brief  Handle the end of the RXTX transaction.
  * @param  hspi: pointer to a SPI_HandleTypeDef structure that contains
  *               the configuration information for SPI module.
  * @retval None
  */
static void SPI_CloseRxTx_ISR(SPI_HandleTypeDef *hspi)
{
  /* Disable ERR interrupt */
  __HAL_SPI_DISABLE_IT(hspi, SPI_IT_TXE | SPI_IT_RXNE | SPI_IT_ERR);
  
  __HAL_SPI_CLEAR_EOTFLAG(hspi);
  __HAL_SPI_CLEAR_TXTFFLAG(hspi);

#ifdef USE_SPI_CRC
  /* Check if CRC error occurred */
  if (__HAL_SPI_GET_FLAG(hspi, SPI_FLAG_CRCERR) != RESET)
  {
    hspi->State = HAL_SPI_STATE_READY;
    SET_BIT(hspi->ErrorCode, HAL_SPI_ERROR_CRC);
    __HAL_SPI_CLEAR_CRCERRFLAG(hspi);
    HAL_SPI_ErrorCallback(hspi);
  }
  else
  {
#endif /* USE_SPI_CRC */
    if (hspi->ErrorCode == HAL_SPI_ERROR_NONE)
    {
      if (hspi->State == HAL_SPI_STATE_BUSY_RX)
      {
        hspi->State = HAL_SPI_STATE_READY;
        HAL_SPI_RxCpltCallback(hspi);
      }
      else
      {
        hspi->State = HAL_SPI_STATE_READY;
        HAL_SPI_TxRxCpltCallback(hspi);
      }
    }
    else
    {
      hspi->State = HAL_SPI_STATE_READY;
      HAL_SPI_ErrorCallback(hspi);
    }
#ifdef USE_SPI_CRC
  }
#endif /* USE_SPI_CRC */
}

/**
  * @brief  Handle the end of the RX transaction.
  * @param  hspi: pointer to a SPI_HandleTypeDef structure that contains
  *               the configuration information for SPI module.
  * @retval None
  */
static void SPI_CloseRx_ISR(SPI_HandleTypeDef *hspi)
{
  /* Disable RXNE and ERR interrupt */
  __HAL_SPI_DISABLE_IT(hspi, (SPI_IT_RXNE | SPI_IT_ERR));
  
  __HAL_SPI_CLEAR_EOTFLAG(hspi);
  __HAL_SPI_CLEAR_TXTFFLAG(hspi);

  /* Clear underrun flag in 1 Line communication mode because transmitted is not feeded */
  if (hspi->Init.Direction == SPI_DIRECTION_1LINE)
  {
    *((__IO uint8_t *)&hspi->Instance->TXDR) = 0x01U;
    __HAL_SPI_CLEAR_UDRFLAG(hspi);
  }

  hspi->State = HAL_SPI_STATE_READY;

#ifdef USE_SPI_CRC
  /* Check if CRC error occurred */
  if (__HAL_SPI_GET_FLAG(hspi, SPI_FLAG_CRCERR) != RESET)
  {
    SET_BIT(hspi->ErrorCode, HAL_SPI_ERROR_CRC);
    __HAL_SPI_CLEAR_CRCERRFLAG(hspi);
    HAL_SPI_ErrorCallback(hspi);
  }
  else
  {
#endif /* USE_SPI_CRC */
    if (hspi->ErrorCode == HAL_SPI_ERROR_NONE)
    {
      HAL_SPI_RxCpltCallback(hspi);
    }
    else
    {
      HAL_SPI_ErrorCallback(hspi);
    }
#ifdef USE_SPI_CRC
  }
#endif /* USE_SPI_CRC */
}

/**
  * @brief  Handle the end of the TX transaction.
  * @param  hspi: pointer to a SPI_HandleTypeDef structure that contains
  *               the configuration information for SPI module.
  * @retval None
  */
static void SPI_CloseTx_ISR(SPI_HandleTypeDef *hspi)
{
  /* Disable TXE and ERR interrupt */
  __HAL_SPI_DISABLE_IT(hspi, (SPI_IT_TXE | SPI_IT_ERR));
  
  __HAL_SPI_CLEAR_EOTFLAG(hspi);
  __HAL_SPI_CLEAR_TXTFFLAG(hspi);

  /* Clear overrun flag in 2 Lines communication mode because received is not read */
  if (hspi->Init.Direction == SPI_DIRECTION_2LINES)
  {
    __HAL_SPI_CLEAR_OVRFLAG(hspi);
  }

  hspi->State = HAL_SPI_STATE_READY;
  if (hspi->ErrorCode != HAL_SPI_ERROR_NONE)
  {
    HAL_SPI_ErrorCallback(hspi);
  }
  else
  {
    HAL_SPI_TxCpltCallback(hspi);
  }
}

/**
  * @brief  Handle abort a Rx transaction.
  * @param  hspi: pointer to a SPI_HandleTypeDef structure that contains
  *               the configuration information for SPI module.
  * @retval None
  */
static void SPI_AbortRx_ISR(SPI_HandleTypeDef *hspi)
{
  uint32_t tickstart = 0U;

  /* Init tickstart for timeout managment*/
  tickstart = HAL_GetTick();

  /* Disable SPI Peripheral */
  __HAL_SPI_DISABLE(hspi);

  /* Disable TXEIE, RXNEIE and ERRIE(mode fault event, overrun error, TI frame error) interrupts */
  CLEAR_BIT(hspi->Instance->IER, (SPI_IT_TXE | SPI_IT_RXNE | SPI_IT_ERR));

  while (HAL_IS_BIT_SET(hspi->Instance->IER, SPI_IT_RXNE))
  {
    if ((HAL_GetTick() - tickstart) >=  HAL_MAX_DELAY)
    {
      hspi->ErrorCode = HAL_SPI_ERROR_ABORT;
    }
  }

  /* Empty the FRLVL fifo */
  if (SPI_WaitFifoStateUntilTimeout(hspi, SPI_FLAG_FRLVL, SPI_FRLVL_EMPTY, SPI_DEFAULT_TIMEOUT, HAL_GetTick()) != HAL_OK)
  {
    hspi->ErrorCode = HAL_SPI_ERROR_ABORT;
  }

  hspi->State = HAL_SPI_STATE_ABORT;
}

/**
  * @brief  Handle abort a Tx or Rx/Tx transaction.
  * @param  hspi: pointer to a SPI_HandleTypeDef structure that contains
  *               the configuration information for SPI module.
  * @retval None
  */
static void SPI_AbortTx_ISR(SPI_HandleTypeDef *hspi)
{
  uint32_t tickstart = 0U;

  /* Init tickstart for timeout managment*/
  tickstart = HAL_GetTick();

  /* Disable TXEIE, RXNEIE and ERRIE(mode fault event, overrun error, TI frame error) interrupts */
  CLEAR_BIT(hspi->Instance->CR2, (SPI_IT_TXE | SPI_IT_RXNE | SPI_IT_ERR));

  while (HAL_IS_BIT_SET(hspi->Instance->IER, SPI_IT_TXE))
  {
    if ((HAL_GetTick() - tickstart) >=  HAL_MAX_DELAY)
    {
      hspi->ErrorCode = HAL_SPI_ERROR_ABORT;
    }
  }

  if (SPI_EndRxTxTransaction(hspi, SPI_DEFAULT_TIMEOUT, HAL_GetTick()) != HAL_OK)
  {
    hspi->ErrorCode = HAL_SPI_ERROR_ABORT;
  }

  /* Disable SPI Peripheral */
  __HAL_SPI_DISABLE(hspi);

  /* Empty the FRLVL fifo */
  if (SPI_WaitFifoStateUntilTimeout(hspi, SPI_FLAG_FRLVL, SPI_FRLVL_EMPTY, SPI_DEFAULT_TIMEOUT, HAL_GetTick()) != HAL_OK)
  {
    hspi->ErrorCode = HAL_SPI_ERROR_ABORT;
  }

  hspi->State = HAL_SPI_STATE_ABORT;
}

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
