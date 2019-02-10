/**
  ******************************************************************************
  * @file    stm32h7xx_hal_usart.c
  * @author  MCD Application Team
  * @version V1.2.0
  * @date   29-December-2017
  * @brief   USART HAL module driver.
  *          This file provides firmware functions to manage the following
  *          functionalities of the Universal Synchronous/Asynchronous Receiver Transmitter
  *          Peripheral (USART).
  *           + Initialization and de-initialization functions
  *           + IO operation functions
  *           + Peripheral Control functions
  *           + Peripheral State and Error functions
  *
  @verbatim
 ===============================================================================
                        ##### How to use this driver #####
 ===============================================================================
    [..]
      The USART HAL driver can be used as follows:

      (#) Declare a USART_HandleTypeDef handle structure (eg. USART_HandleTypeDef husart).
      (#) Initialize the USART low level resources by implementing the HAL_USART_MspInit() API:
          (++) Enable the USARTx interface clock.
          (++) USART pins configuration:
            (+++) Enable the clock for the USART GPIOs.
            (+++) Configure these USART pins as alternate function pull-up.
          (++) NVIC configuration if you need to use interrupt process (HAL_USART_Transmit_IT(),
                HAL_USART_Receive_IT() and HAL_USART_TransmitReceive_IT() APIs):
            (+++) Configure the USARTx interrupt priority.
            (+++) Enable the NVIC USART IRQ handle.
            (++) USART interrupts handling:
              -@@-   The specific USART interrupts (Transmission complete interrupt,
                  RXNE interrupt and Error Interrupts) will be managed using the macros
                  __HAL_USART_ENABLE_IT() and __HAL_USART_DISABLE_IT() inside the transmit and receive process.
          (++) DMA Configuration if you need to use DMA process (HAL_USART_Transmit_DMA()
               HAL_USART_Receive_DMA() and HAL_USART_TransmitReceive_DMA() APIs):
            (+++) Declare a DMA handle structure for the Tx/Rx channel.
            (+++) Enable the DMAx interface clock.
            (+++) Configure the declared DMA handle structure with the required Tx/Rx parameters.
            (+++) Configure the DMA Tx/Rx channel.
            (+++) Associate the initialized DMA handle to the USART DMA Tx/Rx handle.
            (+++) Configure the priority and enable the NVIC for the transfer complete interrupt on the DMA Tx/Rx channel.

      (#) Program the Baud Rate, Word Length, Stop Bit, Parity, Hardware
          flow control and Mode (Receiver/Transmitter) in the husart handle Init structure.

      (#) Initialize the USART registers by calling the HAL_USART_Init() API:
          (++) This API configures also the low level Hardware GPIO, CLOCK, CORTEX...etc)
               by calling the customized HAL_USART_MspInit(&husart) API.

    [..]
     (@) To configure and enable/disable the USART to wake up the MCU from stop mode, resort to UART API's
        HAL_UARTEx_StopModeWakeUpSourceConfig(), HAL_UARTEx_EnableStopMode() and
        HAL_UARTEx_DisableStopMode() in casting the USART handle to UART type UART_HandleTypeDef.

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

/** @defgroup USART USART
  * @brief HAL USART Synchronous module driver
  * @{
  */

#ifdef HAL_USART_MODULE_ENABLED

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/** @defgroup USART_Private_Constants USART Private Constants
  * @{
  */
#define USART_DUMMY_DATA          ((uint16_t) 0xFFFF)           /*!< USART transmitted dummy data                     */
#define USART_TEACK_REACK_TIMEOUT ((uint32_t) 1000)             /*!< USART TX or RX enable acknowledge time-out value */
#define USART_CR1_FIELDS          ((uint32_t)(USART_CR1_M | USART_CR1_PCE | USART_CR1_PS | \
                                              USART_CR1_TE | USART_CR1_RE  | USART_CR1_OVER8|\
                                              USART_CR1_FIFOEN ))                       /*!< USART CR1 fields of parameters set by USART_SetConfig API */
#define USART_CR2_FIELDS          ((uint32_t)(USART_CR2_CPHA | USART_CR2_CPOL |USART_CR2_DIS_NSS|\
                                              USART_CR2_CLKEN | USART_CR2_LBCL | USART_CR2_STOP|\
                                              USART_CR2_SLVEN))                         /*!< USART CR2 fields of parameters set by USART_SetConfig API */
#define USART_CR3_FIELDS          ((uint32_t)(USART_CR3_TXFTCFG | USART_CR3_RXFTCFG ))  /*!< USART CR3 fields of parameters set by USART_SetConfig API */

/**
  * @}
  */

/* Private macros ------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
/** @addtogroup USART_Private_Functions
  * @{
  */
static void USART_EndTransfer(USART_HandleTypeDef *husart);
static void USART_DMATransmitCplt(DMA_HandleTypeDef *hdma);
static void USART_DMAReceiveCplt(DMA_HandleTypeDef *hdma);
static void USART_DMATxHalfCplt(DMA_HandleTypeDef *hdma);
static void USART_DMARxHalfCplt(DMA_HandleTypeDef *hdma);
static void USART_DMAError(DMA_HandleTypeDef *hdma);
static void USART_DMAAbortOnError(DMA_HandleTypeDef *hdma);
static void USART_DMATxAbortCallback(DMA_HandleTypeDef *hdma);
static void USART_DMARxAbortCallback(DMA_HandleTypeDef *hdma);
static HAL_StatusTypeDef USART_WaitOnFlagUntilTimeout(USART_HandleTypeDef *husart, uint32_t Flag, FlagStatus Status, uint32_t Tickstart, uint32_t Timeout);
static HAL_StatusTypeDef USART_SetConfig(USART_HandleTypeDef *husart);
static HAL_StatusTypeDef USART_CheckIdleState(USART_HandleTypeDef *husart);
static HAL_StatusTypeDef USART_Transmit_IT(USART_HandleTypeDef *husart);
static HAL_StatusTypeDef USART_EndTransmit_IT(USART_HandleTypeDef *husart);
static HAL_StatusTypeDef USART_Receive_IT(USART_HandleTypeDef *husart);
static HAL_StatusTypeDef USART_TransmitReceive_IT(USART_HandleTypeDef *husart);
/**
  * @}
  */

/* Exported functions --------------------------------------------------------*/

/** @defgroup USART_Exported_Functions USART Exported Functions
  * @{
  */

/** @defgroup USART_Exported_Functions_Group1 Initialization and de-initialization functions
  *  @brief    Initialization and Configuration functions
  *
@verbatim
 ===============================================================================
            ##### Initialization and Configuration functions #####
 ===============================================================================
    [..]
    This subsection provides a set of functions allowing to initialize the USART
    in asynchronous and in synchronous modes.
      (+) For the asynchronous mode only these parameters can be configured:
        (++) Baud Rate
        (++) Word Length
        (++) Stop Bit
        (++) Parity: If the parity is enabled, then the MSB bit of the data written
             in the data register is transmitted but is changed by the parity bit.
        (++) USART polarity
        (++) USART phase
        (++) USART LastBit
        (++) Receiver/transmitter modes

    [..]
    The HAL_USART_Init() function follows the USART  synchronous configuration
    procedure (details for the procedure are available in reference manual).

@endverbatim

  Depending on the frame length defined by the M1 and M0 bits (7-bit,
  8-bit or 9-bit), the possible USART formats are listed in the
  following table.

    Table 1. USART frame format.
    +-----------------------------------------------------------------------+
    |  M1 bit |  M0 bit |  PCE bit  |            USART frame                |
    |---------|---------|-----------|---------------------------------------|
    |    0    |    0    |    0      |    | SB |    8 bit data   | STB |     |
    |---------|---------|-----------|---------------------------------------|
    |    0    |    0    |    1      |    | SB | 7 bit data | PB | STB |     |
    |---------|---------|-----------|---------------------------------------|
    |    0    |    1    |    0      |    | SB |    9 bit data   | STB |     |
    |---------|---------|-----------|---------------------------------------|
    |    0    |    1    |    1      |    | SB | 8 bit data | PB | STB |     |
    |---------|---------|-----------|---------------------------------------|
    |    1    |    0    |    0      |    | SB |    7 bit data   | STB |     |
    |---------|---------|-----------|---------------------------------------|
    |    1    |    0    |    1      |    | SB | 6 bit data | PB | STB |     |
    +-----------------------------------------------------------------------+

  * @{
  */

/**
  * @brief  Initialize the USART mode according to the specified
  *         parameters in the USART_InitTypeDef and initialize the associated handle.
  * @param husart: USART handle.
  * @retval HAL status
  */
HAL_StatusTypeDef HAL_USART_Init(USART_HandleTypeDef *husart)
{
  /* Check the USART handle allocation */
  if(husart == NULL)
  {
    return HAL_ERROR;
  }

  /* Check the parameters */
  assert_param(IS_USART_INSTANCE(husart->Instance));

  if(husart->State == HAL_USART_STATE_RESET)
  {
    /* Allocate lock resource and initialize it */
    husart->Lock = HAL_UNLOCKED;

    /* Init the low level hardware : GPIO, CLOCK */
    HAL_USART_MspInit(husart);
  }

  husart->State = HAL_USART_STATE_BUSY;

  /* Disable the Peripheral */
  __HAL_USART_DISABLE(husart);

  /* Set the Usart Communication parameters */
  if (USART_SetConfig(husart) == HAL_ERROR)
  {
    return HAL_ERROR;
  }

  /* In Synchronous mode, the following bits must be kept cleared:
  - LINEN bit in the USART_CR2 register
  - HDSEL, SCEN and IREN bits in the USART_CR3 register.*/
  CLEAR_BIT(husart->Instance->CR2, USART_CR2_LINEN);
  CLEAR_BIT(husart->Instance->CR3, (USART_CR3_SCEN | USART_CR3_HDSEL | USART_CR3_IREN));

  /* In Synchronous Slave mode, the following bits must be kept cleared:
  - CLKEN bits in the USART_CR2 register, */
  if (husart->Init.SlaveMode)
  {
    CLEAR_BIT(husart->Instance->CR2, USART_CR2_CLKEN);
  }

  /* Enable the Peripheral */
  __HAL_USART_ENABLE(husart);

  /* TEACK and/or REACK to check before moving husart->State to Ready */
  return (USART_CheckIdleState(husart));
}

/**
  * @brief DeInitialize the USART peripheral.
  * @param husart: USART handle.
  * @retval HAL status
  */
HAL_StatusTypeDef HAL_USART_DeInit(USART_HandleTypeDef *husart)
{
  /* Check the USART handle allocation */
  if(husart == NULL)
  {
    return HAL_ERROR;
  }

  /* Check the parameters */
  assert_param(IS_USART_INSTANCE(husart->Instance));

  husart->State = HAL_USART_STATE_BUSY;

  husart->Instance->CR1 = 0x0U;
  husart->Instance->CR2 = 0x0U;
  husart->Instance->CR3 = 0x0U;

  /* DeInit the low level hardware */
  HAL_USART_MspDeInit(husart);

  husart->ErrorCode = HAL_USART_ERROR_NONE;
  husart->State = HAL_USART_STATE_RESET;

  /* Process Unlock */
  __HAL_UNLOCK(husart);

  return HAL_OK;
}

/**
  * @brief Initialize the USART MSP.
  * @param husart: USART handle.
  * @retval None
  */
__weak void HAL_USART_MspInit(USART_HandleTypeDef *husart)
{
  /* Prevent unused argument(s) compilation warning */
  UNUSED(husart);

  /* NOTE : This function should not be modified, when the callback is needed,
            the HAL_USART_MspInit can be implemented in the user file
   */
}

/**
  * @brief DeInitialize the USART MSP.
  * @param husart: USART handle.
  * @retval None
  */
__weak void HAL_USART_MspDeInit(USART_HandleTypeDef *husart)
{
  /* Prevent unused argument(s) compilation warning */
  UNUSED(husart);

  /* NOTE : This function should not be modified, when the callback is needed,
            the HAL_USART_MspDeInit can be implemented in the user file
   */
}

/**
  * @}
  */

/** @defgroup USART_Exported_Functions_Group2 IO operation functions
  *  @brief   USART Transmit and Receive functions
  *
@verbatim
 ===============================================================================
                      ##### IO operation functions #####
 ===============================================================================
    [..] This subsection provides a set of functions allowing to manage the USART synchronous
    data transfers.

    [..] The USART supports master mode only: it cannot receive or send data related to an input
         clock (SCLK is always an output).

    (#) There are two modes of transfer:
       (++) Blocking mode: The communication is performed in polling mode.
            The HAL status of all data processing is returned by the same function
            after finishing transfer.
       (++) No-Blocking mode: The communication is performed using Interrupts
           or DMA, These API's return the HAL status.
           The end of the data processing will be indicated through the
           dedicated USART IRQ when using Interrupt mode or the DMA IRQ when
           using DMA mode.
           The HAL_USART_TxCpltCallback(), HAL_USART_RxCpltCallback() and HAL_USART_TxRxCpltCallback() user callbacks
           will be executed respectively at the end of the transmit or Receive process
           The HAL_USART_ErrorCallback()user callback will be executed when a communication error is detected

    (#) Blocking mode API's are :
        (++) HAL_USART_Transmit()in simplex mode
        (++) HAL_USART_Receive() in full duplex receive only
        (++) HAL_USART_TransmitReceive() in full duplex mode

    (#) Non-Blocking mode API's with Interrupt are :
        (++) HAL_USART_Transmit_IT()in simplex mode
        (++) HAL_USART_Receive_IT() in full duplex receive only
        (++) HAL_USART_TransmitReceive_IT()in full duplex mode
        (++) HAL_USART_IRQHandler()

    (#) No-Blocking mode API's  with DMA are :
        (++) HAL_USART_Transmit_DMA()in simplex mode
        (++) HAL_USART_Receive_DMA() in full duplex receive only
        (++) HAL_USART_TransmitReceive_DMA() in full duplex mode
        (++) HAL_USART_DMAPause()
        (++) HAL_USART_DMAResume()
        (++) HAL_USART_DMAStop()

    (#) A set of Transfer Complete Callbacks are provided in Non_Blocking mode:
        (++) HAL_USART_TxCpltCallback()
        (++) HAL_USART_RxCpltCallback()
        (++) HAL_USART_TxHalfCpltCallback()
        (++) HAL_USART_RxHalfCpltCallback()
        (++) HAL_USART_ErrorCallback()
        (++) HAL_USART_TxRxCpltCallback()

    (#) Non-Blocking mode transfers could be aborted using Abort API's :
        (+) HAL_USART_Abort()
        (+) HAL_USART_Abort_IT()

    (#) For Abort services based on interrupts (HAL_USART_Abort_IT), a Abort Complete Callbacks is provided:
        (+) HAL_USART_AbortCpltCallback()

    (#) In Non-Blocking mode transfers, possible errors are split into 2 categories.
        Errors are handled as follows :
       (+) Error is considered as Recoverable and non blocking : Transfer could go till end, but error severity is
           to be evaluated by user : this concerns Frame Error, Parity Error or Noise Error in Interrupt mode reception .
           Received character is then retrieved and stored in Rx buffer, Error code is set to allow user to identify error type,
           and HAL_USART_ErrorCallback() user callback is executed. Transfer is kept ongoing on USART side.
           If user wants to abort it, Abort services should be called by user.
       (+) Error is considered as Blocking : Transfer could not be completed properly and is aborted.
           This concerns Overrun Error In Interrupt mode reception and all errors in DMA mode.
           Error code is set to allow user to identify error type, and HAL_USART_ErrorCallback() user callback is executed.

@endverbatim
  * @{
  */

/**
  * @brief  Simplex send an amount of data in blocking mode.
  * @param husart: USART handle.
  * @param pTxData: Pointer to data buffer.
  * @param Size: Amount of data to be sent.
  * @param Timeout: Timeout duration.
  * @retval HAL status
  */
HAL_StatusTypeDef HAL_USART_Transmit(USART_HandleTypeDef *husart, uint8_t *pTxData, uint16_t Size, uint32_t Timeout)
{
  uint16_t* tmp;
  uint32_t tickstart = 0U;

  if(husart->State == HAL_USART_STATE_READY)
  {
    if((pTxData == NULL) || (Size == 0U))
    {
      return  HAL_ERROR;
    }

    /* Process Locked */
    __HAL_LOCK(husart);

    husart->ErrorCode = HAL_USART_ERROR_NONE;
    husart->State = HAL_USART_STATE_BUSY_TX;

    /* Init tickstart for timeout managment */
    tickstart = HAL_GetTick();

    husart->TxXferSize = Size;
    husart->TxXferCount = Size;

    /* Check the remaining data to be sent */
    while(husart->TxXferCount > 0U)
    {
      husart->TxXferCount--;
      if(USART_WaitOnFlagUntilTimeout(husart, USART_FLAG_TXE, RESET, tickstart, Timeout) != HAL_OK)
      {
        return HAL_TIMEOUT;
      }
      if((husart->Init.WordLength == USART_WORDLENGTH_9B) && (husart->Init.Parity == USART_PARITY_NONE))
      {
        tmp = (uint16_t*) pTxData;
        husart->Instance->TDR = (*tmp & (uint16_t)0x01FFU);
        pTxData += 2U;
      }
      else
      {
        husart->Instance->TDR = (*pTxData++ & (uint8_t)0xFFU);
      }
    }

    if(USART_WaitOnFlagUntilTimeout(husart, USART_FLAG_TC, RESET, tickstart, Timeout) != HAL_OK)
    {
      return HAL_TIMEOUT;
    }

    /* At end of Tx process, restore husart->State to Ready */
    husart->State = HAL_USART_STATE_READY;

    /* Process Unlocked */
    __HAL_UNLOCK(husart);

    return HAL_OK;
  }
  else
  {
    return HAL_BUSY;
  }
}

/**
  * @brief Receive an amount of data in blocking mode.
  * @note To receive synchronous data, dummy data are simultaneously transmitted.
  * @param husart: USART handle.
  * @param pRxData: Pointer to data buffer.
  * @param Size: Amount of data to be received.
  * @param Timeout: Timeout duration.
  * @retval HAL status
  */
HAL_StatusTypeDef HAL_USART_Receive(USART_HandleTypeDef *husart, uint8_t *pRxData, uint16_t Size, uint32_t Timeout)
{
  uint16_t* tmp;
  uint16_t uhMask;
  uint32_t tickstart = 0U;

  if(husart->State == HAL_USART_STATE_READY)
  {
    if((pRxData == NULL) || (Size == 0U))
    {
      return  HAL_ERROR;
    }
    /* Process Locked */
    __HAL_LOCK(husart);

    husart->ErrorCode = HAL_USART_ERROR_NONE;
    husart->State = HAL_USART_STATE_BUSY_RX;

    /* Init tickstart for timeout managment */
    tickstart = HAL_GetTick();

    husart->RxXferSize = Size;
    husart->RxXferCount = Size;

    /* Computation of USART mask to apply to RDR register */
    USART_MASK_COMPUTATION(husart);
    uhMask = husart->Mask;

    /* as long as data have to be received */
    while(husart->RxXferCount > 0U)
    {
      husart->RxXferCount--;

      if (husart->Init.SlaveMode == USART_SLAVEMODE_DISABLE)
      {
        /* Wait until TC flag is set to send dummy byte in order to generate the
         * clock for the slave to send data.
         * Whatever the frame length (7, 8 or 9-bit long), the same dummy value
         * can be written for all the cases. */
        if(USART_WaitOnFlagUntilTimeout(husart, USART_FLAG_TC, RESET, tickstart, Timeout) != HAL_OK)
        {
          return HAL_TIMEOUT;
        }
        husart->Instance->TDR = (USART_DUMMY_DATA & (uint16_t)0x0FFU);
      }

      /* Wait for RXNE Flag */
      if(USART_WaitOnFlagUntilTimeout(husart, USART_FLAG_RXNE, RESET, tickstart, Timeout) != HAL_OK)
      {
        return HAL_TIMEOUT;
      }

      if((husart->Init.WordLength == USART_WORDLENGTH_9B) && (husart->Init.Parity == USART_PARITY_NONE))
      {
        tmp = (uint16_t*) pRxData ;
        *tmp = (uint16_t)(husart->Instance->RDR & uhMask);
        pRxData +=2U;
      }
      else
      {
        *pRxData++ = (uint8_t)(husart->Instance->RDR & (uint8_t)uhMask);
      }
    }

    /* At end of Rx process, restore husart->State to Ready */
    husart->State = HAL_USART_STATE_READY;

    /* Process Unlocked */
    __HAL_UNLOCK(husart);

    return HAL_OK;
  }
  else
  {
    return HAL_BUSY;
  }
}

/**
  * @brief Full-Duplex Send and Receive an amount of data in blocking mode.
  * @param husart: USART handle.
  * @param pTxData: pointer to TX data buffer.
  * @param pRxData: pointer to RX data buffer.
  * @param Size: amount of data to be sent (same amount to be received).
  * @param Timeout: Timeout duration.
  * @retval HAL status
  */
HAL_StatusTypeDef HAL_USART_TransmitReceive(USART_HandleTypeDef *husart, uint8_t *pTxData, uint8_t *pRxData, uint16_t Size, uint32_t Timeout)
{
  uint16_t* tmp;
  uint16_t uhMask;
  uint32_t tickstart = 0U;

  if(husart->State == HAL_USART_STATE_READY)
  {
    if((pTxData == NULL) || (pRxData == NULL) || (Size == 0U))
    {
      return  HAL_ERROR;
    }
    /* Process Locked */
    __HAL_LOCK(husart);

    husart->ErrorCode = HAL_USART_ERROR_NONE;
    husart->State = HAL_USART_STATE_BUSY_RX;

    /* Init tickstart for timeout managment */
    tickstart = HAL_GetTick();

    husart->RxXferSize = Size;
    husart->TxXferSize = Size;
    husart->TxXferCount = Size;
    husart->RxXferCount = Size;

    /* Computation of USART mask to apply to RDR register */
    USART_MASK_COMPUTATION(husart);
    uhMask = husart->Mask;

    if (husart->Init.SlaveMode == USART_SLAVEMODE_ENABLE)
    {
      husart->TxXferCount--;

      /* Wait until TXE flag is set to send data */
      if(USART_WaitOnFlagUntilTimeout(husart, USART_FLAG_TXE, RESET, tickstart, Timeout) != HAL_OK)
      {
        return HAL_TIMEOUT;
      }
      if((husart->Init.WordLength == USART_WORDLENGTH_9B) && (husart->Init.Parity == USART_PARITY_NONE))
      {
        tmp = (uint16_t*) pTxData;
        husart->Instance->TDR = (*tmp & uhMask);
        pTxData += 2U;
      }
      else
      {
        husart->Instance->TDR = (*pTxData++ & (uint8_t)uhMask);
      }
    }

    /* Check the remain data to be sent */
    while(husart->TxXferCount > 0U)
    {
      husart->TxXferCount--;
      husart->RxXferCount--;

      /* Wait until TXE flag is set to send data */
      if(USART_WaitOnFlagUntilTimeout(husart, USART_FLAG_TXE, RESET, tickstart, Timeout) != HAL_OK)
      {
        return HAL_TIMEOUT;
      }

      if((husart->Init.WordLength == USART_WORDLENGTH_9B) && (husart->Init.Parity == USART_PARITY_NONE))
      {
        tmp = (uint16_t*) pTxData;
        husart->Instance->TDR = (*tmp & uhMask);
        pTxData += 2U;
      }
      else
      {
        husart->Instance->TDR = (*pTxData++ & (uint8_t)uhMask);
      }

      /* Wait for RXNE Flag */
      if(USART_WaitOnFlagUntilTimeout(husart, USART_FLAG_RXNE, RESET, tickstart, Timeout) != HAL_OK)
      {
        return HAL_TIMEOUT;
      }

      if((husart->Init.WordLength == USART_WORDLENGTH_9B) && (husart->Init.Parity == USART_PARITY_NONE))
      {
        tmp = (uint16_t*) pRxData ;
        *tmp = (uint16_t)(husart->Instance->RDR & uhMask);
        pRxData +=2U;
      }
      else
      {
        *pRxData++ = (uint8_t)(husart->Instance->RDR & (uint8_t)uhMask);
      }
    }

    if (husart->Init.SlaveMode == USART_SLAVEMODE_ENABLE)
    {
      husart->RxXferCount--;

      /* Wait for RXNE Flag */
      if(USART_WaitOnFlagUntilTimeout(husart, USART_FLAG_RXNE, RESET, tickstart, Timeout) != HAL_OK)
      {
        return HAL_TIMEOUT;
      }

      if((husart->Init.WordLength == USART_WORDLENGTH_9B) && (husart->Init.Parity == USART_PARITY_NONE))
      {
        tmp = (uint16_t*) pRxData ;
        *tmp = (uint16_t)(husart->Instance->RDR & uhMask);
        pRxData +=2U;
      }
      else
      {
        *pRxData++ = (uint8_t)(husart->Instance->RDR & (uint8_t)uhMask);
      }
    }

    /* At end of TxRx process, restore husart->State to Ready */
    husart->State = HAL_USART_STATE_READY;

    /* Process Unlocked */
    __HAL_UNLOCK(husart);

    return HAL_OK;
  }
  else
  {
    return HAL_BUSY;
  }
}

/**
  * @brief  Send an amount of data in interrupt mode.
  * @param husart: USART handle.
  * @param pTxData: pointer to data buffer.
  * @param Size: amount of data to be sent.
  * @retval HAL status
  */
HAL_StatusTypeDef HAL_USART_Transmit_IT(USART_HandleTypeDef *husart, uint8_t *pTxData, uint16_t Size)
{
  if(husart->State == HAL_USART_STATE_READY)
  {
    if((pTxData == NULL ) || (Size == 0U))
    {
      return HAL_ERROR;
    }

    /* Process Locked */
    __HAL_LOCK(husart);

    husart->pTxBuffPtr = pTxData;
    husart->TxXferSize = Size;
    husart->TxXferCount = Size;

    husart->ErrorCode = HAL_USART_ERROR_NONE;
    husart->State = HAL_USART_STATE_BUSY_TX;

    /* The USART Error Interrupts: (Frame error, noise error, overrun error)
    are not managed by the USART Transmit Process to avoid the overrun interrupt
    when the usart mode is configured for transmit and receive "USART_MODE_TX_RX"
    to benefit for the frame error and noise interrupts the usart mode should be
    configured only for transmit "USART_MODE_TX" */

    /* Process Unlocked */
    __HAL_UNLOCK(husart);

    /* Enable the TX FIFO threshold interrupt (if FIFO mode is enabled) or
       Transmit Data Register Empty interrupt (if FIFO mode is Disabled).
    */
    if (READ_BIT(husart->Instance->CR1, USART_CR1_FIFOEN) != RESET)
    {
      SET_BIT(husart->Instance->CR3, USART_CR3_TXFTIE);
    }
    else
    {
      SET_BIT(husart->Instance->CR1, USART_CR1_TXEIE);
    }

    return HAL_OK;
  }
  else
  {
    return HAL_BUSY;
  }
}

/**
  * @brief Receive an amount of data in interrupt mode.
  * @note  To receive synchronous data, dummy data are simultaneously transmitted.
  * @param husart: USART handle.
  * @param pRxData: pointer to data buffer.
  * @param Size: amount of data to be received.
  * @retval HAL status
  */
HAL_StatusTypeDef HAL_USART_Receive_IT(USART_HandleTypeDef *husart, uint8_t *pRxData, uint16_t Size)
{
  if(husart->State == HAL_USART_STATE_READY)
  {
    if((pRxData == NULL ) || (Size == 0U))
    {
      return HAL_ERROR;
    }

    /* Process Locked */
    __HAL_LOCK(husart);

    husart->pRxBuffPtr = pRxData;
    husart->RxXferSize = Size;
    husart->RxXferCount = Size;

    USART_MASK_COMPUTATION(husart);

    husart->ErrorCode = HAL_USART_ERROR_NONE;
    husart->State = HAL_USART_STATE_BUSY_RX;

    /* Process Unlocked */
    __HAL_UNLOCK(husart);

    /* Enable the USART Error Interrupt: (Frame error, noise error, overrun error) */
    SET_BIT(husart->Instance->CR3, USART_CR3_EIE);

    /* Enable the USART Parity Error interupt and RX FIFO Threshold interrupt
       (if FIFO mode is enabled) or Data Register Not Empty interrupt
       (if FIFO mode is disabled).
    */
    if (READ_BIT(husart->Instance->CR1, USART_CR1_FIFOEN) != RESET)
    {
      SET_BIT(husart->Instance->CR1, USART_CR1_PEIE);
      SET_BIT(husart->Instance->CR3, USART_CR3_RXFTIE);
    }
    else
    {
      SET_BIT(husart->Instance->CR1, USART_CR1_PEIE | USART_CR1_RXNEIE);
    }

    if (husart->Init.SlaveMode == USART_SLAVEMODE_DISABLE)
    {
      /* Send dummy byte in order to generate the clock for the Slave to send the next data */
      if(husart->Init.WordLength == USART_WORDLENGTH_9B)
      {
        husart->Instance->TDR = (USART_DUMMY_DATA & (uint16_t)0x01FFU);
      }
      else
      {
        husart->Instance->TDR = (USART_DUMMY_DATA & (uint16_t)0x00FFU);
      }
    }

    return HAL_OK;
  }
  else
  {
    return HAL_BUSY;
  }
}

/**
  * @brief Full-Duplex Send and Receive an amount of data in interrupt mode.
  * @param husart: USART handle.
  * @param pTxData: pointer to TX data buffer.
  * @param pRxData: pointer to RX data buffer.
  * @param Size: amount of data to be sent (same amount to be received).
  * @retval HAL status
  */
HAL_StatusTypeDef HAL_USART_TransmitReceive_IT(USART_HandleTypeDef *husart, uint8_t *pTxData, uint8_t *pRxData,  uint16_t Size)
{

  if(husart->State == HAL_USART_STATE_READY)
  {
    if((pTxData == NULL) || (pRxData == NULL) || (Size == 0U))
    {
      return HAL_ERROR;
    }
    /* Process Locked */
    __HAL_LOCK(husart);

    husart->pRxBuffPtr = pRxData;
    husart->RxXferSize = Size;
    husart->RxXferCount = Size;
    husart->pTxBuffPtr = pTxData;
    husart->TxXferSize = Size;
    husart->TxXferCount = Size;

    /* Computation of USART mask to apply to RDR register */
    USART_MASK_COMPUTATION(husart);

    husart->ErrorCode = HAL_USART_ERROR_NONE;
    husart->State = HAL_USART_STATE_BUSY_TX_RX;

    /* Process Unlocked */
    __HAL_UNLOCK(husart);

    /* Enable the USART Error Interrupt: (Frame error, noise error, overrun error) */
    SET_BIT(husart->Instance->CR3, USART_CR3_EIE);

    /* Enable the USART Parity Error interupt and RX/TX FIFO Threshold interrupts
       (if FIFO mode is enabled) or Receive Data Register Not Empty and Transmit
       Data Register Empty Interrupts (if FIFO mode is disabled).
    */
    if (READ_BIT(husart->Instance->CR1, USART_CR1_FIFOEN) != RESET)
    {
      SET_BIT(husart->Instance->CR1, USART_CR1_PEIE);
      SET_BIT(husart->Instance->CR3, USART_CR3_RXFTIE | USART_CR3_TXFTIE);
    }
    else
    {
      SET_BIT(husart->Instance->CR1, USART_CR1_PEIE | USART_CR1_RXNEIE | USART_CR1_TXEIE);
    }

    return HAL_OK;
  }
  else
  {
    return HAL_BUSY;
  }

}

/**
  * @brief Send an amount of data in DMA mode.
  * @param husart: USART handle.
  * @param pTxData: pointer to data buffer.
  * @param Size: amount of data to be sent.
  * @retval HAL status
  */
HAL_StatusTypeDef HAL_USART_Transmit_DMA(USART_HandleTypeDef *husart, uint8_t *pTxData, uint16_t Size)
{
  uint32_t *tmp;

  if(husart->State == HAL_USART_STATE_READY)
  {
    if((pTxData == NULL ) || (Size == 0U))
    {
      return HAL_ERROR;
    }
    /* Process Locked */
    __HAL_LOCK(husart);

    husart->pTxBuffPtr = pTxData;
    husart->TxXferSize = Size;
    husart->TxXferCount = Size;

    husart->ErrorCode = HAL_USART_ERROR_NONE;
    husart->State = HAL_USART_STATE_BUSY_TX;

    /* Set the USART DMA transfer complete callback */
    husart->hdmatx->XferCpltCallback = USART_DMATransmitCplt;

    /* Set the USART DMA Half transfer complete callback */
    husart->hdmatx->XferHalfCpltCallback = USART_DMATxHalfCplt;

    /* Set the DMA error callback */
    husart->hdmatx->XferErrorCallback = USART_DMAError;

    /* Enable the USART transmit DMA channel */
    tmp = (uint32_t*)&pTxData;
    HAL_DMA_Start_IT(husart->hdmatx, *(uint32_t*)tmp, (uint32_t)&husart->Instance->TDR, Size);

    /* Clear the TC flag in the ICR register */
    __HAL_USART_CLEAR_FLAG(husart, USART_CLEAR_TCF);

    /* Process Unlocked */
    __HAL_UNLOCK(husart);

    /* Enable the DMA transfer for transmit request by setting the DMAT bit
       in the USART CR3 register */
    SET_BIT(husart->Instance->CR3, USART_CR3_DMAT);

    return HAL_OK;
  }
  else
  {
    return HAL_BUSY;
  }
}

/**
  * @brief Receive an amount of data in DMA mode.
  * @param husart: USART handle.
  * @param pRxData: pointer to data buffer.
  * @param Size: amount of data to be received.
  * @note   When the USART parity is enabled (PCE = 1), the received data contain
  *         the parity bit (MSB position).
  * @note The USART DMA transmit channel must be configured in order to generate the clock for the slave.
  * @retval HAL status
  */
HAL_StatusTypeDef HAL_USART_Receive_DMA(USART_HandleTypeDef *husart, uint8_t *pRxData, uint16_t Size)
{
  uint32_t *tmp;

  /* Check that a Rx process is not already ongoing */
  if(husart->State == HAL_USART_STATE_READY)
  {
    if((pRxData == NULL ) || (Size == 0U))
    {
      return HAL_ERROR;
    }

    /* Process Locked */
    __HAL_LOCK(husart);

    husart->pRxBuffPtr = pRxData;
    husart->RxXferSize = Size;
    husart->pTxBuffPtr = pRxData;
    husart->TxXferSize = Size;

    husart->ErrorCode = HAL_USART_ERROR_NONE;
    husart->State = HAL_USART_STATE_BUSY_RX;

    /* Set the USART DMA Rx transfer complete callback */
    husart->hdmarx->XferCpltCallback = USART_DMAReceiveCplt;

    /* Set the USART DMA Half transfer complete callback */
    husart->hdmarx->XferHalfCpltCallback = USART_DMARxHalfCplt;

    /* Set the USART DMA Rx transfer error callback */
    husart->hdmarx->XferErrorCallback = USART_DMAError;

    /* Enable the USART receive DMA channel */
    tmp = (uint32_t*)&pRxData;
    HAL_DMA_Start_IT(husart->hdmarx, (uint32_t)&husart->Instance->RDR, *(uint32_t*)tmp, Size);

    if (husart->Init.SlaveMode == USART_SLAVEMODE_DISABLE)
    {
      /* Enable the USART transmit DMA channel: the transmit channel is used in order
         to generate in the non-blocking mode the clock to the slave device,
         this mode isn't a simplex receive mode but a full-duplex receive mode */
      /* Set the USART DMA Tx Complete and Error callback to Null */
      husart->hdmatx->XferErrorCallback = NULL;
      husart->hdmatx->XferHalfCpltCallback = NULL;
      husart->hdmatx->XferCpltCallback = NULL;
      HAL_DMA_Start_IT(husart->hdmatx, *(uint32_t*)tmp, (uint32_t)&husart->Instance->TDR, Size);
    }

    /* Process Unlocked */
    __HAL_UNLOCK(husart);

    /* Enable the USART Parity Error Interrupt */
    SET_BIT(husart->Instance->CR1, USART_CR1_PEIE);

    /* Enable the USART Error Interrupt: (Frame error, noise error, overrun error) */
    SET_BIT(husart->Instance->CR3, USART_CR3_EIE);

    /* Enable the DMA transfer for the receiver request by setting the DMAR bit
       in the USART CR3 register */
    SET_BIT(husart->Instance->CR3, USART_CR3_DMAR);

    if (husart->Init.SlaveMode == USART_SLAVEMODE_DISABLE)
    {
      /* Enable the DMA transfer for transmit request by setting the DMAT bit
         in the USART CR3 register */
      SET_BIT(husart->Instance->CR3, USART_CR3_DMAT);
    }

    return HAL_OK;
  }
  else
  {
    return HAL_BUSY;
  }
}

/**
  * @brief Full-Duplex Transmit Receive an amount of data in non-blocking mode.
  * @param husart: USART handle.
  * @param pTxData: pointer to TX data buffer.
  * @param pRxData: pointer to RX data buffer.
  * @param Size: amount of data to be received/sent.
  * @note   When the USART parity is enabled (PCE = 1) the data received contain the parity bit.
  * @retval HAL status
  */
HAL_StatusTypeDef HAL_USART_TransmitReceive_DMA(USART_HandleTypeDef *husart, uint8_t *pTxData, uint8_t *pRxData, uint16_t Size)
{
  uint32_t *tmp;

  if(husart->State == HAL_USART_STATE_READY)
  {
    if((pTxData == NULL) || (pRxData == NULL) || (Size == 0U))
    {
      return HAL_ERROR;
    }
    /* Process Locked */
    __HAL_LOCK(husart);

    husart->pRxBuffPtr = pRxData;
    husart->RxXferSize = Size;
    husart->pTxBuffPtr = pTxData;
    husart->TxXferSize = Size;

    husart->ErrorCode = HAL_USART_ERROR_NONE;
    husart->State = HAL_USART_STATE_BUSY_TX_RX;

    /* Set the USART DMA Rx transfer complete callback */
    husart->hdmarx->XferCpltCallback = USART_DMAReceiveCplt;

    /* Set the USART DMA Half transfer complete callback */
    husart->hdmarx->XferHalfCpltCallback = USART_DMARxHalfCplt;

    /* Set the USART DMA Tx transfer complete callback */
    husart->hdmatx->XferCpltCallback = USART_DMATransmitCplt;

    /* Set the USART DMA Half transfer complete callback */
    husart->hdmatx->XferHalfCpltCallback = USART_DMATxHalfCplt;

    /* Set the USART DMA Tx transfer error callback */
    husart->hdmatx->XferErrorCallback = USART_DMAError;

    /* Set the USART DMA Rx transfer error callback */
    husart->hdmarx->XferErrorCallback = USART_DMAError;

    /* Enable the USART receive DMA channel */
    tmp = (uint32_t*)&pRxData;
    HAL_DMA_Start_IT(husart->hdmarx, (uint32_t)&husart->Instance->RDR, *(uint32_t*)tmp, Size);

    /* Enable the USART transmit DMA channel */
    tmp = (uint32_t*)&pTxData;
    HAL_DMA_Start_IT(husart->hdmatx, *(uint32_t*)tmp, (uint32_t)&husart->Instance->TDR, Size);

    /* Process Unlocked */
    __HAL_UNLOCK(husart);

    /* Enable the USART Parity Error Interrupt */
    SET_BIT(husart->Instance->CR1, USART_CR1_PEIE);

    /* Enable the USART Error Interrupt: (Frame error, noise error, overrun error) */
    SET_BIT(husart->Instance->CR3, USART_CR3_EIE);

    /* Clear the TC flag in the ICR register */
    __HAL_USART_CLEAR_FLAG(husart, USART_CLEAR_TCF);

    /* Enable the DMA transfer for the receiver request by setting the DMAR bit
       in the USART CR3 register */
    SET_BIT(husart->Instance->CR3, USART_CR3_DMAR);

    /* Enable the DMA transfer for transmit request by setting the DMAT bit
       in the USART CR3 register */
    SET_BIT(husart->Instance->CR3, USART_CR3_DMAT);

    return HAL_OK;
  }
  else
  {
    return HAL_BUSY;
  }
}

/**
  * @brief Pause the DMA Transfer.
  * @param husart: USART handle.
  * @retval HAL status
  */
HAL_StatusTypeDef HAL_USART_DMAPause(USART_HandleTypeDef *husart)
{
  /* Process Locked */
  __HAL_LOCK(husart);

  if( (husart->State == HAL_USART_STATE_BUSY_TX) &&
      (HAL_IS_BIT_SET(husart->Instance->CR3, USART_CR3_DMAT)))
  {
    /* Disable the USART DMA Tx request */
    CLEAR_BIT(husart->Instance->CR3, USART_CR3_DMAT);
  }
  else if( (husart->State == HAL_USART_STATE_BUSY_RX) ||
           (husart->State == HAL_USART_STATE_BUSY_TX_RX) )
  {
    if (HAL_IS_BIT_SET(husart->Instance->CR3, USART_CR3_DMAT))
    {
      /* Disable the USART DMA Tx request */
      CLEAR_BIT(husart->Instance->CR3, USART_CR3_DMAT);
    }
    if (HAL_IS_BIT_SET(husart->Instance->CR3, USART_CR3_DMAR))
    {
      /* Disable PE and ERR (Frame error, noise error, overrun error) interrupts */
      CLEAR_BIT(husart->Instance->CR1, USART_CR1_PEIE);
      CLEAR_BIT(husart->Instance->CR3, USART_CR3_EIE);

      /* Disable the USART DMA Rx request */
      CLEAR_BIT(husart->Instance->CR3, USART_CR3_DMAR);
    }
  }

  /* Process Unlocked */
  __HAL_UNLOCK(husart);

  return HAL_OK;
}

/**
  * @brief Resume the DMA Transfer.
  * @param husart: USART handle.
  * @retval HAL status
  */
HAL_StatusTypeDef HAL_USART_DMAResume(USART_HandleTypeDef *husart)
{
  /* Process Locked */
  __HAL_LOCK(husart);

  if(husart->State == HAL_USART_STATE_BUSY_TX)
  {
    /* Enable the USART DMA Tx request */
    SET_BIT(husart->Instance->CR3, USART_CR3_DMAT);
  }
  else if( (husart->State == HAL_USART_STATE_BUSY_RX) ||
           (husart->State == HAL_USART_STATE_BUSY_TX_RX) )
  {
    /* Clear the Overrun flag before resuming the Rx transfer*/
    __HAL_USART_CLEAR_FLAG(husart, USART_CLEAR_OREF);

    /* Reenable PE and ERR (Frame error, noise error, overrun error) interrupts */
    SET_BIT(husart->Instance->CR1, USART_CR1_PEIE);
    SET_BIT(husart->Instance->CR3, USART_CR3_EIE);

    /* Enable the USART DMA Rx request  before the DMA Tx request */
    SET_BIT(husart->Instance->CR3, USART_CR3_DMAR);

    /* Enable the USART DMA Tx request */
    SET_BIT(husart->Instance->CR3, USART_CR3_DMAT);
  }

  /* Process Unlocked */
  __HAL_UNLOCK(husart);

  return HAL_OK;
}

/**
  * @brief Stop the DMA Transfer.
  * @param husart: USART handle.
  * @retval HAL status
  */
HAL_StatusTypeDef HAL_USART_DMAStop(USART_HandleTypeDef *husart)
{
  /* The Lock is not implemented on this API to allow the user application
     to call the HAL USART API under callbacks HAL_USART_TxCpltCallback() / HAL_USART_RxCpltCallback() /
     HAL_USART_TxHalfCpltCallback / HAL_USART_RxHalfCpltCallback:
     indeed, when HAL_DMA_Abort() API is called, the DMA TX/RX Transfer or Half Transfer complete
     interrupt is generated if the DMA transfer interruption occurs at the middle or at the end of
     the stream and the corresponding call back is executed. */

  /* Disable the USART Tx/Rx DMA requests */
  CLEAR_BIT(husart->Instance->CR3, USART_CR3_DMAT);
  CLEAR_BIT(husart->Instance->CR3, USART_CR3_DMAR);

  /* Abort the USART DMA tx channel */
  if(husart->hdmatx != NULL)
  {
    HAL_DMA_Abort(husart->hdmatx);
  }
  /* Abort the USART DMA rx channel */
  if(husart->hdmarx != NULL)
  {
    HAL_DMA_Abort(husart->hdmarx);
  }

  USART_EndTransfer(husart);
  husart->State = HAL_USART_STATE_READY;

  return HAL_OK;
}

/**
  * @brief  Abort ongoing transfers (blocking mode).
  * @param  husart USART handle.
  * @note   This procedure could be used for aborting any ongoing transfer started in Interrupt or DMA mode.
  *         This procedure performs following operations :
  *           - Disable USART Interrupts (Tx and Rx)
  *           - Disable the DMA transfer in the peripheral register (if enabled)
  *           - Abort DMA transfer by calling HAL_DMA_Abort (in case of transfer in DMA mode)
  *           - Set handle State to READY
  * @note   This procedure is executed in blocking mode : when exiting function, Abort is considered as completed.
  * @retval HAL status
*/
HAL_StatusTypeDef HAL_USART_Abort(USART_HandleTypeDef *husart)
{
  /* Disable RXNE, PE, TXE, TC, RXFT, TXFT and ERR (Frame error, noise error, overrun error) interrupts */
  CLEAR_BIT(husart->Instance->CR1, (USART_CR1_RXNEIE | USART_CR1_PEIE | USART_CR1_TXEIE | USART_CR1_TCIE));
  CLEAR_BIT(husart->Instance->CR3, USART_CR3_EIE | USART_CR3_RXFTIE | USART_CR3_TXFTIE);

  /* Disable the USART DMA Tx request if enabled */
  if (HAL_IS_BIT_SET(husart->Instance->CR3, USART_CR3_DMAT))
  {
    CLEAR_BIT(husart->Instance->CR3, USART_CR3_DMAT);

    /* Abort the USART DMA Tx channel : use blocking DMA Abort API (no callback) */
    if(husart->hdmatx != NULL)
    {
      /* Set the USART DMA Abort callback to Null.
         No call back execution at end of DMA abort procedure */
      husart->hdmatx->XferAbortCallback = NULL;

      HAL_DMA_Abort(husart->hdmatx);
    }
  }

  /* Disable the USART DMA Rx request if enabled */
  if (HAL_IS_BIT_SET(husart->Instance->CR3, USART_CR3_DMAR))
  {
    CLEAR_BIT(husart->Instance->CR3, USART_CR3_DMAR);

    /* Abort the USART DMA Rx channel : use blocking DMA Abort API (no callback) */
    if(husart->hdmarx != NULL)
    {
      /* Set the USART DMA Abort callback to Null.
         No call back execution at end of DMA abort procedure */
      husart->hdmarx->XferAbortCallback = NULL;

      HAL_DMA_Abort(husart->hdmarx);
    }
  }

  /* Reset Tx and Rx transfer counters */
  husart->TxXferCount = 0U;
  husart->RxXferCount = 0U;

  /* Clear the Error flags in the ICR register */
  __HAL_USART_CLEAR_FLAG(husart, USART_CLEAR_OREF | USART_CLEAR_NEF | USART_CLEAR_PEF | USART_CLEAR_FEF);

  /* Restore husart->State to Ready */
  husart->State  = HAL_USART_STATE_READY;

  /* Reset Handle ErrorCode to No Error */
  husart->ErrorCode = HAL_USART_ERROR_NONE;

  return HAL_OK;
}

/**
  * @brief  Abort ongoing transfers (Interrupt mode).
  * @param  husart USART handle.
  * @note   This procedure could be used for aborting any ongoing transfer started in Interrupt or DMA mode.
  *         This procedure performs following operations :
  *           - Disable USART Interrupts (Tx and Rx)
  *           - Disable the DMA transfer in the peripheral register (if enabled)
  *           - Abort DMA transfer by calling HAL_DMA_Abort_IT (in case of transfer in DMA mode)
  *           - Set handle State to READY
  *           - At abort completion, call user abort complete callback
  * @note   This procedure is executed in Interrupt mode, meaning that abort procedure could be
  *         considered as completed only when user abort complete callback is executed (not when exiting function).
  * @retval HAL status
*/
HAL_StatusTypeDef HAL_USART_Abort_IT(USART_HandleTypeDef *husart)
{
  uint32_t abortcplt = 1U;

  /* Disable RXNE, PE, TXE, TC, RXFT, TXFT and ERR (Frame error, noise error, overrun error) interrupts */
  CLEAR_BIT(husart->Instance->CR3, USART_CR3_EIE | USART_CR3_RXFTIE | USART_CR3_TXFTIE);
  CLEAR_BIT(husart->Instance->CR1, (USART_CR1_RXNEIE | USART_CR1_PEIE | USART_CR1_TXEIE | USART_CR1_TCIE));

  /* If DMA Tx and/or DMA Rx Handles are associated to USART Handle, DMA Abort complete callbacks should be initialised
     before any call to DMA Abort functions */
  /* DMA Tx Handle is valid */
  if(husart->hdmatx != NULL)
  {
    /* Set DMA Abort Complete callback if USART DMA Tx request if enabled.
       Otherwise, set it to NULL */
    if(HAL_IS_BIT_SET(husart->Instance->CR3, USART_CR3_DMAT))
    {
      husart->hdmatx->XferAbortCallback = USART_DMATxAbortCallback;
    }
    else
    {
      husart->hdmatx->XferAbortCallback = NULL;
    }
  }
  /* DMA Rx Handle is valid */
  if(husart->hdmarx != NULL)
  {
    /* Set DMA Abort Complete callback if USART DMA Rx request if enabled.
       Otherwise, set it to NULL */
    if(HAL_IS_BIT_SET(husart->Instance->CR3, USART_CR3_DMAR))
    {
      husart->hdmarx->XferAbortCallback = USART_DMARxAbortCallback;
    }
    else
    {
      husart->hdmarx->XferAbortCallback = NULL;
    }
  }

  /* Disable the USART DMA Tx request if enabled */
  if(HAL_IS_BIT_SET(husart->Instance->CR3, USART_CR3_DMAT))
  {
    /* Disable DMA Tx at USART level */
    CLEAR_BIT(husart->Instance->CR3, USART_CR3_DMAT);

    /* Abort the USART DMA Tx channel : use non blocking DMA Abort API (callback) */
    if(husart->hdmatx != NULL)
    {
      /* USART Tx DMA Abort callback has already been initialised :
         will lead to call HAL_USART_AbortCpltCallback() at end of DMA abort procedure */

      /* Abort DMA TX */
      if(HAL_DMA_Abort_IT(husart->hdmatx) != HAL_OK)
      {
        husart->hdmatx->XferAbortCallback = NULL;
      }
      else
      {
        abortcplt = 0U;
      }
    }
  }

  /* Disable the USART DMA Rx request if enabled */
  if (HAL_IS_BIT_SET(husart->Instance->CR3, USART_CR3_DMAR))
  {
    CLEAR_BIT(husart->Instance->CR3, USART_CR3_DMAR);

    /* Abort the USART DMA Rx channel : use non blocking DMA Abort API (callback) */
    if(husart->hdmarx != NULL)
    {
      /* USART Rx DMA Abort callback has already been initialised :
         will lead to call HAL_USART_AbortCpltCallback() at end of DMA abort procedure */

      /* Abort DMA RX */
      if(HAL_DMA_Abort_IT(husart->hdmarx) != HAL_OK)
      {
        husart->hdmarx->XferAbortCallback = NULL;
        abortcplt = 1U;
      }
      else
      {
        abortcplt = 0U;
      }
    }
  }

  /* if no DMA abort complete callback execution is required => call user Abort Complete callback */
  if (abortcplt == 1U)
  {
    /* Reset Tx and Rx transfer counters */
    husart->TxXferCount = 0U;
    husart->RxXferCount = 0U;

    /* Reset errorCode */
    husart->ErrorCode = HAL_USART_ERROR_NONE;

    /* Clear the Error flags in the ICR register */
    __HAL_USART_CLEAR_FLAG(husart, USART_CLEAR_OREF | USART_CLEAR_NEF | USART_CLEAR_PEF | USART_CLEAR_FEF);

    /* Restore husart->State to Ready */
    husart->State  = HAL_USART_STATE_READY;

    /* As no DMA to be aborted, call directly user Abort complete callback */
    HAL_USART_AbortCpltCallback(husart);
  }

  return HAL_OK;
}

/**
  * @brief  Handle USART interrupt request.
  * @param  husart USART handle.
  * @retval None
  */
void HAL_USART_IRQHandler(USART_HandleTypeDef *husart)
{
  uint32_t isrflags   = READ_REG(husart->Instance->ISR);
  uint32_t cr1its     = READ_REG(husart->Instance->CR1);
  uint32_t cr3its     = READ_REG(husart->Instance->CR3);
  uint32_t errorflags;

  /* If no error occurs */
  errorflags = (isrflags & (uint32_t)(USART_ISR_PE | USART_ISR_FE | USART_ISR_ORE | USART_ISR_NE | USART_ISR_UDR));
  if (errorflags == RESET)
  {
    /* USART in mode Receiver ---------------------------------------------------*/
    if(((isrflags & USART_ISR_RXNE) != RESET)
       && (((cr1its & USART_CR1_RXNEIE) != RESET) || ((cr3its & USART_CR3_RXFTIE) != RESET)))
    {
      if(husart->State == HAL_USART_STATE_BUSY_RX)
      {
        USART_Receive_IT(husart);
      }
      else
      {
        USART_TransmitReceive_IT(husart);
      }
      return;
    }
  }

  /* If some errors occur */
  if((errorflags != RESET)
     && (((cr3its & (USART_CR3_RXFTIE | USART_CR3_EIE)) != RESET)
          || ((cr1its & (USART_CR1_RXNEIE | USART_CR1_PEIE)) != RESET)))
  {
    /* USART parity error interrupt occurred -------------------------------------*/
    if(((isrflags & USART_ISR_PE) != RESET) && ((cr1its & USART_CR1_PEIE) != RESET))
    {
      __HAL_USART_CLEAR_IT(husart, USART_CLEAR_PEF);

      husart->ErrorCode |= HAL_USART_ERROR_PE;
    }

    /* USART frame error interrupt occurred --------------------------------------*/
    if(((isrflags & USART_ISR_FE) != RESET) && ((cr3its & USART_CR3_EIE) != RESET))
    {
      __HAL_USART_CLEAR_IT(husart, USART_CLEAR_FEF);

      husart->ErrorCode |= HAL_USART_ERROR_FE;
    }

    /* USART noise error interrupt occurred --------------------------------------*/
    if(((isrflags & USART_ISR_NE) != RESET) && ((cr3its & USART_CR3_EIE) != RESET))
    {
      __HAL_USART_CLEAR_IT(husart, USART_CLEAR_NEF);

      husart->ErrorCode |= HAL_USART_ERROR_NE;
    }

    /* USART Over-Run interrupt occurred -----------------------------------------*/
    if(((isrflags & USART_ISR_ORE) != RESET)
       && (((cr1its & USART_CR1_RXNEIE) != RESET)
           || ((cr3its & USART_CR3_RXFTIE) != RESET)
           || ((cr3its & USART_CR3_EIE) != RESET)))
    {
      __HAL_USART_CLEAR_IT(husart, USART_CLEAR_OREF);

      husart->ErrorCode |= HAL_USART_ERROR_ORE;
    }

    /* USART Under-Run interrupt occurred --------------------------------------*/
    if(((isrflags & USART_ISR_UDR) != RESET) && ((cr3its & USART_CR3_EIE) != RESET))
    {
      __HAL_USART_CLEAR_IT(husart, USART_CLEAR_UDRCF);
      husart->ErrorCode |= HAL_USART_ERROR_UDR;
    }

    /* Call USART Error Call back function if need be --------------------------*/
    if(husart->ErrorCode != HAL_USART_ERROR_NONE)
    {
      /* USART in mode Receiver ---------------------------------------------------*/
      if(((isrflags & USART_ISR_RXNE) != RESET)
         && (((cr1its & USART_CR1_RXNEIE) != RESET)
             || ((cr3its & USART_CR3_RXFTIE) != RESET)))
      {
        if(husart->State == HAL_USART_STATE_BUSY_RX)
        {
          USART_Receive_IT(husart);
        }
        else
        {
          USART_TransmitReceive_IT(husart);
        }
      }

      /* If Overrun error occurs, or if any error occurs in DMA mode reception,
         consider error as blocking */
      if (((husart->ErrorCode & HAL_USART_ERROR_ORE) != RESET) ||
          (HAL_IS_BIT_SET(husart->Instance->CR3, USART_CR3_DMAR)))
      {
        /* Blocking error : transfer is aborted
           Set the USART state ready to be able to start again the process,
           Disable Interrupts, and disable DMA requests, if ongoing */
        USART_EndTransfer(husart);

        /* Disable the USART DMA Rx request if enabled */
        if (HAL_IS_BIT_SET(husart->Instance->CR3, USART_CR3_DMAR))
        {
          CLEAR_BIT(husart->Instance->CR3, USART_CR3_DMAR | USART_CR3_DMAR);

          /* Abort the USART DMA Tx channel */
          if(husart->hdmatx != NULL)
          {
            /* Set the USART Tx DMA Abort callback to NULL : no callback
               executed at end of DMA abort procedure */
            husart->hdmatx->XferAbortCallback = NULL;

            /* Abort DMA TX */
            HAL_DMA_Abort_IT(husart->hdmatx);
          }

          /* Abort the USART DMA Rx channel */
          if(husart->hdmarx != NULL)
          {
            /* Set the USART Rx DMA Abort callback :
               will lead to call HAL_USART_ErrorCallback() at end of DMA abort procedure */
            husart->hdmarx->XferAbortCallback = USART_DMAAbortOnError;

            /* Abort DMA RX */
            if(HAL_DMA_Abort_IT(husart->hdmarx) != HAL_OK)
            {
              /* Call Directly husart->hdmarx->XferAbortCallback function in case of error */
              husart->hdmarx->XferAbortCallback(husart->hdmarx);
            }
          }
          else
          {
            /* Call user error callback */
            HAL_USART_ErrorCallback(husart);
          }
        }
        else
        {
          /* Call user error callback */
          HAL_USART_ErrorCallback(husart);
        }
      }
      else
      {
        /* Non Blocking error : transfer could go on.
           Error is notified to user through user error callback */
        HAL_USART_ErrorCallback(husart);
        husart->ErrorCode = HAL_USART_ERROR_NONE;
      }
    }
    return;

  } /* End if some error occurs */


  /* USART in mode Transmitter ------------------------------------------------*/
  if(((isrflags & USART_ISR_TXE) != RESET)
     && (((cr1its & USART_CR1_TXEIE) != RESET)
         || ((cr3its & USART_CR3_TXFTIE) != RESET)))
  {
    if(husart->State == HAL_USART_STATE_BUSY_TX)
    {
      USART_Transmit_IT(husart);
    }
    else
    {
      USART_TransmitReceive_IT(husart);
    }
    return;
  }

  /* USART in mode Transmitter (transmission end) -----------------------------*/
  if(((isrflags & USART_ISR_TC) != RESET) && ((cr1its & USART_CR1_TCIE) != RESET))
  {
    USART_EndTransmit_IT(husart);
    return;
  }

  /* USART TX FIFO Empty  -----------------------------------------------------*/
  if(((isrflags & USART_ISR_TXFE) != RESET) && ((cr1its & USART_CR1_TXFEIE) != RESET))
  {
    CLEAR_BIT(husart->Instance->CR1, USART_CR1_TXFEIE);
  }
}

/**
  * @brief Tx Transfer completed callback.
  * @param husart: USART handle.
  * @retval None
  */
__weak void HAL_USART_TxCpltCallback(USART_HandleTypeDef *husart)
{
  /* Prevent unused argument(s) compilation warning */
  UNUSED(husart);

  /* NOTE : This function should not be modified, when the callback is needed,
            the HAL_USART_TxCpltCallback can be implemented in the user file.
   */
}

/**
  * @brief  Tx Half Transfer completed callback.
  * @param husart: USART handle.
  * @retval None
  */
__weak void HAL_USART_TxHalfCpltCallback(USART_HandleTypeDef *husart)
{
  /* Prevent unused argument(s) compilation warning */
  UNUSED(husart);

  /* NOTE: This function should not be modified, when the callback is needed,
           the HAL_USART_TxHalfCpltCallback can be implemented in the user file.
   */
}

/**
  * @brief  Rx Transfer completed callback.
  * @param husart: USART handle.
  * @retval None
  */
__weak void HAL_USART_RxCpltCallback(USART_HandleTypeDef *husart)
{
  /* Prevent unused argument(s) compilation warning */
  UNUSED(husart);

  /* NOTE: This function should not be modified, when the callback is needed,
           the HAL_USART_RxCpltCallback can be implemented in the user file.
   */
}

/**
  * @brief Rx Half Transfer completed callback.
  * @param husart: USART handle.
  * @retval None
  */
__weak void HAL_USART_RxHalfCpltCallback(USART_HandleTypeDef *husart)
{
  /* Prevent unused argument(s) compilation warning */
  UNUSED(husart);

  /* NOTE : This function should not be modified, when the callback is needed,
            the HAL_USART_RxHalfCpltCallback can be implemented in the user file
   */
}

/**
  * @brief Tx/Rx Transfers completed callback for the non-blocking process.
  * @param husart: USART handle.
  * @retval None
  */
__weak void HAL_USART_TxRxCpltCallback(USART_HandleTypeDef *husart)
{
  /* Prevent unused argument(s) compilation warning */
  UNUSED(husart);

  /* NOTE : This function should not be modified, when the callback is needed,
            the HAL_USART_TxRxCpltCallback can be implemented in the user file
   */
}

/**
  * @brief USART error callback.
  * @param husart: USART handle.
  * @retval None
  */
__weak void HAL_USART_ErrorCallback(USART_HandleTypeDef *husart)
{
  /* Prevent unused argument(s) compilation warning */
  UNUSED(husart);

  /* NOTE : This function should not be modified, when the callback is needed,
            the HAL_USART_ErrorCallback can be implemented in the user file.
   */
}

/**
  * @brief  USART Abort Complete callback.
  * @param  husart USART handle.
  * @retval None
  */
__weak void HAL_USART_AbortCpltCallback (USART_HandleTypeDef *husart)
{
  /* Prevent unused argument(s) compilation warning */
  UNUSED(husart);

  /* NOTE : This function should not be modified, when the callback is needed,
            the HAL_USART_AbortCpltCallback can be implemented in the user file.
   */
}

/**
  * @}
  */

/** @defgroup USART_Exported_Functions_Group4 Peripheral State and Error functions
 *  @brief   USART Peripheral State and Error functions
 *
@verbatim
  ==============================================================================
            ##### Peripheral State and Error functions #####
  ==============================================================================
    [..]
    This subsection provides functions allowing to :
      (+) Return the USART handle state
      (+) Return the USART handle error code

@endverbatim
  * @{
  */


/**
  * @brief Return the USART handle state.
  * @param husart : pointer to a USART_HandleTypeDef structure that contains
  *              the configuration information for the specified USART.
  * @retval USART handle state
  */
HAL_USART_StateTypeDef HAL_USART_GetState(USART_HandleTypeDef *husart)
{
  return husart->State;
}

/**
  * @brief Return the USART error code.
  * @param husart : pointer to a USART_HandleTypeDef structure that contains
  *              the configuration information for the specified USART.
  * @retval USART handle Error Code
  */
uint32_t HAL_USART_GetError(USART_HandleTypeDef *husart)
{
  return husart->ErrorCode;
}

/**
  * @}
  */

/**
  * @}
  */

/** @defgroup USART_Private_Functions USART Private Functions
 * @{
 */

/**
  * @brief  End ongoing transfer on USART peripheral (following error detection or Transfer completion).
  * @param  husart USART handle.
  * @retval None
  */
static void USART_EndTransfer(USART_HandleTypeDef *husart)
{
  /* Disable RXNE, PE, TXE, TC, RXFT, TXFT and ERR (Frame error, noise error, overrun error) interrupts */
  CLEAR_BIT(husart->Instance->CR1, (USART_CR1_RXNEIE | USART_CR1_PEIE | USART_CR1_TXEIE | USART_CR1_TCIE));
  CLEAR_BIT(husart->Instance->CR3, USART_CR3_EIE | USART_CR3_RXFTIE | USART_CR3_TXFTIE);

  /* At end of process, restore husart->State to Ready */
  husart->State = HAL_USART_STATE_READY;
}

/**
  * @brief  DMA USART transmit process complete callback.
  * @param  hdma DMA handle.
  * @retval None
  */
static void USART_DMATransmitCplt(DMA_HandleTypeDef *hdma)
{
  USART_HandleTypeDef* husart = (USART_HandleTypeDef*)(hdma->Parent);

  /* DMA Normal mode */
  if (hdma->Init.Mode != DMA_CIRCULAR)
  {
    husart->TxXferCount = 0U;

    if(husart->State == HAL_USART_STATE_BUSY_TX)
    {
      /* Disable the DMA transfer for transmit request by resetting the DMAT bit
         in the USART CR3 register */
      CLEAR_BIT(husart->Instance->CR3, USART_CR3_DMAT);

      /* Enable the USART Transmit Complete Interrupt */
      SET_BIT(husart->Instance->CR1, USART_CR1_TCIE);
    }
  }
  /* DMA Circular mode */
  else
  {
    if(husart->State == HAL_USART_STATE_BUSY_TX)
    {
    HAL_USART_TxCpltCallback(husart);
   }
 }
}

/**
  * @brief DMA USART transmit process half complete callback.
  * @param hdma : DMA handle.
  * @retval None
  */
static void USART_DMATxHalfCplt(DMA_HandleTypeDef *hdma)
{
  USART_HandleTypeDef* husart = (USART_HandleTypeDef*)(hdma->Parent);

  HAL_USART_TxHalfCpltCallback(husart);
}

/**
  * @brief DMA USART receive process complete callback.
  * @param  hdma: DMA handle.
  * @retval None
  */
static void USART_DMAReceiveCplt(DMA_HandleTypeDef *hdma)
{
  USART_HandleTypeDef* husart = (USART_HandleTypeDef*)(hdma->Parent);

  /* DMA Normal mode */
  if (hdma->Init.Mode != DMA_CIRCULAR)
  {
    husart->RxXferCount = 0U;

    /* Disable PE and ERR (Frame error, noise error, overrun error) interrupts */
    CLEAR_BIT(husart->Instance->CR1, USART_CR1_PEIE);
    CLEAR_BIT(husart->Instance->CR3, USART_CR3_EIE);

    /* Disable the DMA RX transfer for the receiver request by resetting the DMAR bit
       in USART CR3 register */
    CLEAR_BIT(husart->Instance->CR3, USART_CR3_DMAR);
    /* similarly, disable the DMA TX transfer that was started to provide the
       clock to the slave device */
    CLEAR_BIT(husart->Instance->CR3, USART_CR3_DMAT);

    if(husart->State == HAL_USART_STATE_BUSY_RX)
    {
      HAL_USART_RxCpltCallback(husart);
    }
    /* The USART state is HAL_USART_STATE_BUSY_TX_RX */
    else
    {
      HAL_USART_TxRxCpltCallback(husart);
    }
    husart->State= HAL_USART_STATE_READY;
  }
  /* DMA circular mode */
  else
  {
    if(husart->State == HAL_USART_STATE_BUSY_RX)
    {
      HAL_USART_RxCpltCallback(husart);
    }
    /* The USART state is HAL_USART_STATE_BUSY_TX_RX */
    else
    {
      HAL_USART_TxRxCpltCallback(husart);
    }
  }

}

/**
  * @brief DMA USART receive process half complete callback.
  * @param hdma : DMA handle.
  * @retval None
  */
static void USART_DMARxHalfCplt(DMA_HandleTypeDef *hdma)
{
  USART_HandleTypeDef* husart = (USART_HandleTypeDef*)(hdma->Parent);

  HAL_USART_RxHalfCpltCallback(husart);
}

/**
  * @brief DMA USART communication error callback.
  * @param  hdma: DMA handle.
  * @retval None
  */
static void USART_DMAError(DMA_HandleTypeDef *hdma)
{
  USART_HandleTypeDef* husart = (USART_HandleTypeDef*)(hdma->Parent);

  husart->RxXferCount = 0U;
  husart->TxXferCount = 0U;
  USART_EndTransfer(husart);

  husart->ErrorCode |= HAL_USART_ERROR_DMA;
  husart->State= HAL_USART_STATE_READY;

  HAL_USART_ErrorCallback(husart);
}

/**
  * @brief  DMA USART communication abort callback, when initiated by HAL services on Error
  *         (To be called at end of DMA Abort procedure following error occurrence).
  * @param  hdma: DMA handle.
  * @retval None
  */
static void USART_DMAAbortOnError(DMA_HandleTypeDef *hdma)
{
  USART_HandleTypeDef* husart = (USART_HandleTypeDef*)(hdma->Parent);
  husart->RxXferCount = 0U;
  husart->TxXferCount = 0U;

  HAL_USART_ErrorCallback(husart);
}

/**
  * @brief  DMA USART Tx communication abort callback, when initiated by user
  *         (To be called at end of DMA Tx Abort procedure following user abort request).
  * @note   When this callback is executed, User Abort complete call back is called only if no
  *         Abort still ongoing for Rx DMA Handle.
  * @param  hdma DMA handle.
  * @retval None
  */
static void USART_DMATxAbortCallback(DMA_HandleTypeDef *hdma)
{
  USART_HandleTypeDef* husart = (USART_HandleTypeDef* )(hdma->Parent);

  husart->hdmatx->XferAbortCallback = NULL;

  /* Check if an Abort process is still ongoing */
  if(husart->hdmarx != NULL)
  {
    if(husart->hdmarx->XferAbortCallback != NULL)
    {
      return;
    }
  }

  /* No Abort process still ongoing : All DMA channels are aborted, call user Abort Complete callback */
  husart->TxXferCount = 0U;
  husart->RxXferCount = 0U;

  /* Reset errorCode */
  husart->ErrorCode = HAL_USART_ERROR_NONE;

  /* Clear the Error flags in the ICR register */
  __HAL_USART_CLEAR_FLAG(husart, USART_CLEAR_OREF | USART_CLEAR_NEF | USART_CLEAR_PEF | USART_CLEAR_FEF);

  /* Restore husart->State to Ready */
  husart->State  = HAL_USART_STATE_READY;

  /* Call user Abort complete callback */
  HAL_USART_AbortCpltCallback(husart);
}


/**
  * @brief  DMA USART Rx communication abort callback, when initiated by user
  *         (To be called at end of DMA Rx Abort procedure following user abort request).
  * @note   When this callback is executed, User Abort complete call back is called only if no
  *         Abort still ongoing for Tx DMA Handle.
  * @param  hdma DMA handle.
  * @retval None
  */
static void USART_DMARxAbortCallback(DMA_HandleTypeDef *hdma)
{
  USART_HandleTypeDef* husart = (USART_HandleTypeDef* )(hdma->Parent);

  husart->hdmarx->XferAbortCallback = NULL;

  /* Check if an Abort process is still ongoing */
  if(husart->hdmatx != NULL)
  {
    if(husart->hdmatx->XferAbortCallback != NULL)
    {
      return;
    }
  }

  /* No Abort process still ongoing : All DMA channels are aborted, call user Abort Complete callback */
  husart->TxXferCount = 0U;
  husart->RxXferCount = 0U;

  /* Reset errorCode */
  husart->ErrorCode = HAL_USART_ERROR_NONE;

  /* Clear the Error flags in the ICR register */
  __HAL_USART_CLEAR_FLAG(husart, USART_CLEAR_OREF | USART_CLEAR_NEF | USART_CLEAR_PEF | USART_CLEAR_FEF);

  /* Restore husart->State to Ready */
  husart->State  = HAL_USART_STATE_READY;

  /* Call user Abort complete callback */
  HAL_USART_AbortCpltCallback(husart);
}


/**
  * @brief  Handle USART Communication Timeout.
  * @param husart: USART handle.
  * @param  Flag: specifies the USART flag to check.
  * @param  Status: the Flag status (SET or RESET).
  * @param  Tickstart: tick start value.
  * @param  Timeout: timeout duration.
  * @retval HAL status
  */
static HAL_StatusTypeDef USART_WaitOnFlagUntilTimeout(USART_HandleTypeDef *husart, uint32_t Flag, FlagStatus Status, uint32_t Tickstart, uint32_t Timeout)
{
  /* Wait until flag is set */
  while((__HAL_USART_GET_FLAG(husart, Flag) ? SET : RESET) == Status)
  {
    /* Check for the Timeout */
    if(Timeout != HAL_MAX_DELAY)
    {
      if((Timeout == 0U) || ((HAL_GetTick() - Tickstart) > Timeout))
      {
        /* Disable TXE, RXNE, PE and ERR (Frame error, noise error, overrun error) interrupts for the interrupt process */
        CLEAR_BIT(husart->Instance->CR1, (USART_CR1_RXNEIE | USART_CR1_PEIE | USART_CR1_TXEIE));
        CLEAR_BIT(husart->Instance->CR3, USART_CR3_EIE);

        husart->State= HAL_USART_STATE_READY;

        /* Process Unlocked */
        __HAL_UNLOCK(husart);

        return HAL_TIMEOUT;
      }
    }
  }

  return HAL_OK;
}

/**
  * @brief Configure the USART peripheral.
  * @param husart: USART handle.
  * @retval HAL status
  */
static HAL_StatusTypeDef USART_SetConfig(USART_HandleTypeDef *husart)
{
  uint32_t tmpreg                      = 0x0U;
  USART_ClockSourceTypeDef clocksource = USART_CLOCKSOURCE_UNDEFINED;
  HAL_StatusTypeDef ret                = HAL_OK;
  uint16_t brrtemp                     = 0x0000U;
  uint16_t usartdiv                    = 0x0000U;
  PLL2_ClocksTypeDef pll2_clocks;
  PLL3_ClocksTypeDef pll3_clocks;

  /* Check the parameters */
  assert_param(IS_USART_POLARITY(husart->Init.CLKPolarity));
  assert_param(IS_USART_PHASE(husart->Init.CLKPhase));
  assert_param(IS_USART_LASTBIT(husart->Init.CLKLastBit));
  assert_param(IS_USART_BAUDRATE(husart->Init.BaudRate));
  assert_param(IS_USART_WORD_LENGTH(husart->Init.WordLength));
  assert_param(IS_USART_STOPBITS(husart->Init.StopBits));
  assert_param(IS_USART_PARITY(husart->Init.Parity));
  assert_param(IS_USART_MODE(husart->Init.Mode));
  assert_param(IS_USART_PRESCALER(husart->Init.Prescaler));
  assert_param(IS_USART_NSS(husart->Init.NSS));
  assert_param(IS_USART_SLAVEMODE(husart->Init.SlaveMode));
  assert_param(IS_USART_FIFO_MODE_STATE(husart->Init.FIFOMode));
  if (husart->Init.FIFOMode == USART_FIFOMODE_ENABLE)
  {
    assert_param(IS_USART_TXFIFO_THRESHOLD(husart->Init.TXFIFOThreshold));
    assert_param(IS_USART_RXFIFO_THRESHOLD(husart->Init.RXFIFOThreshold));
  }

  /*-------------------------- USART CR1 Configuration -----------------------*/
   /* Clear M, PCE, PS, TE and RE bits and configure
   *  the USART Word Length, Parity and Mode:
   *  set the M bits according to husart->Init.WordLength value
   *  set PCE and PS bits according to husart->Init.Parity value
   *  set TE and RE bits according to husart->Init.Mode value
   *  force OVER8 to 1 to allow to reach the maximum speed (Fclock/8)  */
  tmpreg = (uint32_t)husart->Init.WordLength | husart->Init.Parity | husart->Init.Mode | USART_CR1_OVER8;
  tmpreg |=  (uint32_t)husart->Init.FIFOMode;
  MODIFY_REG(husart->Instance->CR1, USART_CR1_FIELDS, tmpreg);

  /*---------------------------- USART CR2 Configuration ---------------------*/
  /* Clear and configure the USART Clock, CPOL, CPHA, LBCL and STOP bits:
   * set CPOL bit according to husart->Init.CLKPolarity value
   * set CPHA bit according to husart->Init.CLKPhase value
   * set DIS_NSS bit according to husart->Init.NSS value
   * set LBCL bit according to husart->Init.CLKLastBit value
   * set STOP[13:12] bits according to husart->Init.StopBits value
   * set SlaveMode bit according to husart->Init.SlaveMode value */
  tmpreg = (uint32_t)(USART_CLOCK_ENABLE);
  tmpreg |= ((uint32_t)husart->Init.CLKPolarity | (uint32_t)husart->Init.CLKPhase | (uint32_t)husart->Init.NSS);
  tmpreg |= ((uint32_t)husart->Init.CLKLastBit | (uint32_t)husart->Init.StopBits | (uint32_t)husart->Init.SlaveMode);
  MODIFY_REG(husart->Instance->CR2, USART_CR2_FIELDS, tmpreg);

  /*-------------------------- USART CR3 Configuration -----------------------*/
  /* Clear and configure the TXFTCFG & RXFTCFG bits:
   * set TXFTCFG bit according to husart->Init.TXFIFOThreshold value
   * set RXFTCFG bit according to husart->Init.RXFIFOThreshold value */
  if (husart->Init.FIFOMode == USART_FIFOMODE_ENABLE)
  {
    tmpreg = ((uint32_t)husart->Init.TXFIFOThreshold | (uint32_t)husart->Init.RXFIFOThreshold );
    MODIFY_REG(husart->Instance->CR3, USART_CR3_FIELDS, tmpreg);
  }

  /*-------------------------- USART PRESC Configuration -----------------------*/
  /* Configure
   * - USART Clock Prescaler : set PRESCALER according to husart->Init.Prescaler value */
  MODIFY_REG(husart->Instance->PRESC, USART_PRESC_PRESCALER, husart->Init.Prescaler);

  /*-------------------------- USART BRR Configuration -----------------------*/
  /* BRR is filled-up according to OVER8 bit setting which is forced to 1     */
  USART_GETCLOCKSOURCE(husart, clocksource);
  switch (clocksource)
  {
    case USART_CLOCKSOURCE_D2PCLK1:
      usartdiv = (uint16_t)(USART_DIV_SAMPLING8(HAL_RCC_GetPCLK1Freq(), husart->Init.BaudRate, husart->Init.Prescaler));
      break;
    case USART_CLOCKSOURCE_D2PCLK2:
      usartdiv = (uint16_t)(USART_DIV_SAMPLING8(HAL_RCC_GetPCLK2Freq(), husart->Init.BaudRate, husart->Init.Prescaler));
      break;
    case USART_CLOCKSOURCE_PLL2:
      HAL_RCCEx_GetPLL2ClockFreq(&pll2_clocks);
      usartdiv = (uint16_t)(USART_DIV_SAMPLING8(pll2_clocks.PLL2_Q_Frequency, husart->Init.BaudRate, husart->Init.Prescaler));
      break;
    case USART_CLOCKSOURCE_PLL3:
      HAL_RCCEx_GetPLL3ClockFreq(&pll3_clocks);
      usartdiv = (uint16_t)(USART_DIV_SAMPLING8(pll3_clocks.PLL3_Q_Frequency, husart->Init.BaudRate, husart->Init.Prescaler));
      break;
    case USART_CLOCKSOURCE_HSI:
      if (__HAL_RCC_GET_FLAG(RCC_FLAG_HSIDIV) != 0U)
      {
        usartdiv = (uint16_t)(USART_DIV_SAMPLING8((HSI_VALUE >> (__HAL_RCC_GET_HSI_DIVIDER()>> 3)), husart->Init.BaudRate, husart->Init.Prescaler));
      }
      else
      {
        usartdiv = (uint16_t)(USART_DIV_SAMPLING8(HSI_VALUE, husart->Init.BaudRate, husart->Init.Prescaler));
      }
      break;
    case USART_CLOCKSOURCE_CSI:
      usartdiv = (uint16_t)(USART_DIV_SAMPLING8(CSI_VALUE, husart->Init.BaudRate, husart->Init.Prescaler));
      break;
    case USART_CLOCKSOURCE_LSE:
      usartdiv = (uint16_t)(USART_DIV_SAMPLING8(LSE_VALUE, husart->Init.BaudRate, husart->Init.Prescaler));
      break;
    case USART_CLOCKSOURCE_UNDEFINED:
    default:
      ret = HAL_ERROR;
      break;
  }

  brrtemp = usartdiv & 0xFFF0U;
  brrtemp |= (uint16_t)((usartdiv & (uint16_t)0x000FU) >> 1U);
  husart->Instance->BRR = brrtemp;

  return ret;
}

/**
  * @brief Check the USART Idle State.
  * @param husart: USART handle.
  * @retval HAL status
  */
static HAL_StatusTypeDef USART_CheckIdleState(USART_HandleTypeDef *husart)
{
  uint32_t tickstart = 0U;

  /* Initialize the USART ErrorCode */
  husart->ErrorCode = HAL_USART_ERROR_NONE;

  /* Init tickstart for timeout managment */
  tickstart = HAL_GetTick();

  /* Check if the Transmitter is enabled */
  if((husart->Instance->CR1 & USART_CR1_TE) == USART_CR1_TE)
  {
    /* Wait until TEACK flag is set */
    if(USART_WaitOnFlagUntilTimeout(husart, USART_ISR_TEACK, RESET, tickstart, USART_TEACK_REACK_TIMEOUT) != HAL_OK)
    {
      /* Timeout occurred */
      return HAL_TIMEOUT;
    }
  }
  /* Check if the Receiver is enabled */
  if((husart->Instance->CR1 & USART_CR1_RE) == USART_CR1_RE)
  {
    /* Wait until REACK flag is set */
    if(USART_WaitOnFlagUntilTimeout(husart, USART_ISR_REACK, RESET, tickstart, USART_TEACK_REACK_TIMEOUT) != HAL_OK)
    {
      /* Timeout occurred */
      return HAL_TIMEOUT;
    }
  }

  /* Initialize the USART state*/
  husart->State= HAL_USART_STATE_READY;

  /* Process Unlocked */
  __HAL_UNLOCK(husart);

  return HAL_OK;
}

/**
  * @brief  Simplex send an amount of data in non-blocking mode.
  * @note   Function called under interruption only, once
  *         interruptions have been enabled by HAL_USART_Transmit_IT().
  * @note   The USART errors are not managed to avoid the overrun error.
  * @param husart: USART handle.
  * @retval HAL status
  */
static HAL_StatusTypeDef USART_Transmit_IT(USART_HandleTypeDef *husart)
{
  uint16_t* tmp;

  if(husart->TxXferCount == 0U)
  {
    /* Disable the TX FIFO threshold interrupt (if FIFO mode is enabled) or
       Transmit Data Register Empty interrupt (if FIFO mode is Disabled).
    */
    if (READ_BIT(husart->Instance->CR1, USART_CR1_FIFOEN) != RESET)
    {
      CLEAR_BIT(husart->Instance->CR3, USART_CR3_TXFTIE);
    }
    else
    {
      CLEAR_BIT(husart->Instance->CR1, USART_CR1_TXEIE);
    }

    /* Enable the USART Transmit Complete Interrupt */
    SET_BIT(husart->Instance->CR1, USART_CR1_TCIE);

    return HAL_OK;
  }
  else
  {
    if((husart->Init.WordLength == USART_WORDLENGTH_9B) && (husart->Init.Parity == USART_PARITY_NONE))
    {
      tmp = (uint16_t*) husart->pTxBuffPtr;
      husart->Instance->TDR = (*tmp & (uint16_t)0x01FFU);
      husart->pTxBuffPtr += 2U;
    }
    else
    {
      husart->Instance->TDR = (uint8_t)(*husart->pTxBuffPtr++ & (uint8_t)0xFFU);
    }

    husart->TxXferCount--;

    return HAL_OK;
  }
}


/**
  * @brief  Wraps up transmission in non-blocking mode.
  * @param  husart: pointer to a USART_HandleTypeDef structure that contains
  *                the configuration information for the specified USART module.
  * @retval HAL status
  */
static HAL_StatusTypeDef USART_EndTransmit_IT(USART_HandleTypeDef *husart)
{
  /* Disable the USART Transmit Complete Interrupt */
  CLEAR_BIT(husart->Instance->CR1, USART_CR1_TCIE);

  /* Disable the USART Error Interrupt: (Frame error, noise error, overrun error) */
  CLEAR_BIT(husart->Instance->CR3, USART_CR3_EIE);

  /* Tx process is ended, restore husart->State to Ready */
  husart->State = HAL_USART_STATE_READY;

  HAL_USART_TxCpltCallback(husart);

  return HAL_OK;
}


/**
  * @brief  Simplex receive an amount of data in non-blocking mode.
  * @note   Function called under interruption only, once
  *         interruptions have been enabled by HAL_USART_Receive_IT().
  * @param husart: USART handle
  * @retval HAL status
  */
static HAL_StatusTypeDef USART_Receive_IT(USART_HandleTypeDef *husart)
{
  uint16_t* tmp;
  uint16_t uhMask = husart->Mask;

  if((husart->Init.WordLength == USART_WORDLENGTH_9B) && (husart->Init.Parity == USART_PARITY_NONE))
  {
    tmp = (uint16_t*) husart->pRxBuffPtr;
    *tmp = (uint16_t)(husart->Instance->RDR & uhMask);
    husart->pRxBuffPtr += 2U;
  }
  else
  {
    *husart->pRxBuffPtr++ = (uint8_t)(husart->Instance->RDR & (uint8_t)uhMask);
  }

  if (husart->Init.SlaveMode == USART_SLAVEMODE_DISABLE)
  {
    /* Send dummy byte in order to generate the clock for the Slave to Send the next data */
    husart->Instance->TDR = (USART_DUMMY_DATA & (uint16_t)0x00FFU);
  }

  if(--husart->RxXferCount == 0U)
  {
    /* Disable the USART Parity Error Interrupt and RXNE interrupt*/
    CLEAR_BIT(husart->Instance->CR1, (USART_CR1_RXNEIE | USART_CR1_PEIE));

    /* Disable the USART Error Interrupt: (Frame error, noise error, overrun error) */
    CLEAR_BIT(husart->Instance->CR3, USART_CR3_EIE);

    /* Rx process is completed, restore husart->State to Ready */
    husart->State = HAL_USART_STATE_READY;

    HAL_USART_RxCpltCallback(husart);

    return HAL_OK;
  }

  return HAL_OK;
}

/**
  * @brief  Full-Duplex Send receive an amount of data in full-duplex mode (non-blocking).
  * @note   Function called under interruption only, once
  *         interruptions have been enabled by HAL_USART_TransmitReceive_IT().
  * @param husart: USART handle.
  * @retval HAL status
  */
static HAL_StatusTypeDef USART_TransmitReceive_IT(USART_HandleTypeDef *husart)
{
  uint16_t* tmp;
  uint16_t uhMask = husart->Mask;

  if(husart->TxXferCount != 0x00U)
  {
    if(__HAL_USART_GET_FLAG(husart, USART_FLAG_TXE) != RESET)
    {
      if((husart->Init.WordLength == USART_WORDLENGTH_9B) && (husart->Init.Parity == USART_PARITY_NONE))
      {
        tmp = (uint16_t*) husart->pTxBuffPtr;
        husart->Instance->TDR = (uint16_t)(*tmp & uhMask);
        husart->pTxBuffPtr += 2U;
      }
      else
      {
        husart->Instance->TDR = (uint8_t)(*husart->pTxBuffPtr++ & (uint8_t)uhMask);
      }
      husart->TxXferCount--;

      /* Check the latest data transmitted */
      if(husart->TxXferCount == 0U)
      {
        /* Disable the TX FIFO threshold interrupt (if FIFO mode is enabled) or
           Transmit Data Register Empty interrupt (if FIFO mode is Disabled) */
        if (READ_BIT(husart->Instance->CR1, USART_CR1_FIFOEN) != RESET)
        {
          CLEAR_BIT(husart->Instance->CR3, USART_CR3_TXFTIE);
        }
        else
        {
          CLEAR_BIT(husart->Instance->CR1, USART_CR1_TXEIE);
        }
      }
    }
  }

  if(husart->RxXferCount != 0x00U)
  {
    if(__HAL_USART_GET_FLAG(husart, USART_FLAG_RXNE) != RESET)
    {
      if((husart->Init.WordLength == USART_WORDLENGTH_9B) && (husart->Init.Parity == USART_PARITY_NONE))
      {
        tmp = (uint16_t*) husart->pRxBuffPtr;
        *tmp = (uint16_t)(husart->Instance->RDR & uhMask);
        husart->pRxBuffPtr += 2U;
      }
      else
      {
        *husart->pRxBuffPtr++ = (uint8_t)(husart->Instance->RDR & (uint8_t)uhMask);
      }
      husart->RxXferCount--;
    }
  }

  /* Check the latest data received */
  if(husart->RxXferCount == 0U)
  {
    /* Disable the USART Parity Error Interrupt and RXNE interrupt*/
    CLEAR_BIT(husart->Instance->CR1, (USART_CR1_RXNEIE | USART_CR1_PEIE));

    /* Disable the USART Error Interrupt: (Frame error, noise error, overrun error) */
    CLEAR_BIT(husart->Instance->CR3, USART_CR3_EIE);

    /* Rx process is completed, restore husart->State to Ready */
    husart->State = HAL_USART_STATE_READY;

    HAL_USART_TxRxCpltCallback(husart);

    return HAL_OK;
  }

  return HAL_OK;
}

/**
  * @}
  */

#endif /* HAL_USART_MODULE_ENABLED */
/**
  * @}
  */

/**
  * @}
  */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
