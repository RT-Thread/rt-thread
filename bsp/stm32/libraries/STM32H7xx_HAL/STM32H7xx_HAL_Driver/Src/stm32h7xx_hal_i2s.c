/**
  ******************************************************************************
  * @file    stm32h7xx_hal_i2s.c
  * @author  MCD Application Team
  * @version V1.2.0
  * @date   29-December-2017
  * @brief   I2S HAL module driver.
  *          This file provides firmware functions to manage the following
  *          functionalities of the Integrated Interchip Sound (I2S) peripheral:
  *           + Initialization and de-initialization functions
  *           + IO operation functions
  *           + Peripheral State and Errors functions
  @verbatim
 ===============================================================================
                  ##### How to use this driver #####
 ===============================================================================
 [..]
    The I2S HAL driver can be used as follow:
    
    (#) Declare a I2S_HandleTypeDef handle structure.
    (#) Initialize the I2S low level resources by implement the HAL_I2S_MspInit() API:
        (##) Enable the SPIx interface clock.
        (##) I2S pins configuration:
            (+++) Enable the clock for the I2S GPIOs.
            (+++) Configure these I2S pins as alternate function pull-up.
        (##) NVIC configuration if you need to use interrupt process (HAL_I2S_Transmit_IT()
             and HAL_I2S_Receive_IT() APIs).
            (+++) Configure the I2Sx interrupt priority.
            (+++) Enable the NVIC I2S IRQ handle.
        (##) DMA Configuration if you need to use DMA process (HAL_I2S_Transmit_DMA()
             and HAL_I2S_Receive_DMA() APIs:
            (+++) Declare a DMA handle structure for the Tx/Rx channel.
            (+++) Enable the DMAx interface clock.
            (+++) Configure the declared DMA handle structure with the required Tx/Rx parameters.
            (+++) Configure the DMA Tx/Rx Channel.
            (+++) Associate the initialized DMA handle to the I2S DMA Tx/Rx handle.
            (+++) Configure the priority and enable the NVIC for the transfer complete interrupt on the
                  DMA Tx/Rx Channel.

   (#) Program the Mode, Standard, Data Format, MCLK Output, Audio frequency and Polarity
       using HAL_I2S_Init() function.

   -@- The specific I2S interrupts (Transmission complete interrupt,
       RXNE interrupt and Error Interrupts) will be managed using the macros
       __HAL_I2S_ENABLE_IT() and __HAL_I2S_DISABLE_IT() inside the transmit and receive process.
   -@- Make sure that either:
       (+@) External clock source is configured after setting correctly
            the define constant EXTERNAL_CLOCK_VALUE in the stm32h7xx_hal_conf.h file.

   Three mode of operations are available within this driver :

   *** Polling mode IO operation ***
   =================================
   [..]
     (+) Send an amount of data in blocking mode using HAL_I2S_Transmit()
     (+) Receive an amount of data in blocking mode using HAL_I2S_Receive()

   *** Interrupt mode IO operation ***
   ===================================
   [..]
     (+) Send an amount of data in non blocking mode using HAL_I2S_Transmit_IT()
     (+) At transmission end of half transfer HAL_I2S_TxHalfCpltCallback is executed and user can
         add his own code by customization of function pointer HAL_I2S_TxHalfCpltCallback
     (+) At transmission end of transfer HAL_I2S_TxCpltCallback is executed and user can
         add his own code by customization of function pointer HAL_I2S_TxCpltCallback
     (+) Receive an amount of data in non blocking mode using HAL_I2S_Receive_IT()
     (+) At reception end of half transfer HAL_I2S_RxHalfCpltCallback is executed and user can
         add his own code by customization of function pointer HAL_I2S_RxHalfCpltCallback
     (+) At reception end of transfer HAL_I2S_RxCpltCallback is executed and user can
         add his own code by customization of function pointer HAL_I2S_RxCpltCallback
     (+) In case of transfer Error, HAL_I2S_ErrorCallback() function is executed and user can
         add his own code by customization of function pointer HAL_I2S_ErrorCallback

   *** DMA mode IO operation ***
   ==============================
   [..]
     (+) Send an amount of data in non blocking mode (DMA) using HAL_I2S_Transmit_DMA()
     (+) At transmission end of half transfer HAL_I2S_TxHalfCpltCallback is executed and user can
         add his own code by customization of function pointer HAL_I2S_TxHalfCpltCallback
     (+) At transmission end of transfer HAL_I2S_TxCpltCallback is executed and user can
         add his own code by customization of function pointer HAL_I2S_TxCpltCallback
     (+) Receive an amount of data in non blocking mode (DMA) using HAL_I2S_Receive_DMA()
     (+) At reception end of half transfer HAL_I2S_RxHalfCpltCallback is executed and user can
         add his own code by customization of function pointer HAL_I2S_RxHalfCpltCallback
     (+) At reception end of transfer HAL_I2S_RxCpltCallback is executed and user can
         add his own code by customization of function pointer HAL_I2S_RxCpltCallback
     (+) In case of transfer Error, HAL_I2S_ErrorCallback() function is executed and user can
         add his own code by customization of function pointer HAL_I2S_ErrorCallback
     (+) Pause the DMA Transfer using HAL_I2S_DMAPause()
     (+) Resume the DMA Transfer using HAL_I2S_DMAResume()
     (+) Stop the DMA Transfer using HAL_I2S_DMAStop()

   *** I2S HAL driver macros list ***
   ===================================
   [..]
     Below the list of most used macros in I2S HAL driver.
       
      (+) __HAL_I2S_ENABLE: Enable the specified SPI peripheral (in I2S mode)
      (+) __HAL_I2S_DISABLE: Disable the specified SPI peripheral (in I2S mode)
      (+) __HAL_I2S_ENABLE_IT : Enable the specified I2S interrupts
      (+) __HAL_I2S_DISABLE_IT : Disable the specified I2S interrupts
      (+) __HAL_I2S_GET_FLAG: Check whether the specified I2S flag is set or not

    [..]
      (@) You can refer to the I2S HAL driver header file for more useful macros

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

/** @addtogroup I2S
  * @brief I2S HAL module driver
  * @{
  */



/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
/** @addtogroup I2S_Private
  * @{
  */
static void               I2S_DMATxCplt(DMA_HandleTypeDef *hdma);
static void               I2S_DMATxHalfCplt(DMA_HandleTypeDef *hdma);
static void               I2S_DMARxCplt(DMA_HandleTypeDef *hdma);
static void               I2S_DMARxHalfCplt(DMA_HandleTypeDef *hdma);
static void               I2S_DMAError(DMA_HandleTypeDef *hdma);

static void               I2S_TxISR_16BIT(struct __I2S_HandleTypeDef *hi2s);
static void               I2S_TxISR_32BIT(struct __I2S_HandleTypeDef *hi2s);
static void               I2S_RxISR_16BIT(struct __I2S_HandleTypeDef *hi2s);
static void               I2S_RxISR_32BIT(struct __I2S_HandleTypeDef *hi2s);
static void               I2S_CloseRx_ISR(I2S_HandleTypeDef *hi2s);
static void               I2S_CloseTx_ISR(I2S_HandleTypeDef *hi2s);

static HAL_StatusTypeDef  I2S_WaitFlagStateUntilTimeout(I2S_HandleTypeDef *hi2s, uint32_t Flag, uint32_t State, uint32_t Timeout);

/**
  * @}
  */
  
/* Exported functions ---------------------------------------------------------*/
/** @addtogroup I2S_Exported_Functions I2S Exported Functions
  * @{
  */

/** @addtogroup  I2S_Exported_Functions_Group1
  *  @brief    Initialization and Configuration functions 
  *
@verbatim    
 ===============================================================================
              ##### Initialization and de-initialization functions #####
 ===============================================================================
    [..]  This subsection provides a set of functions allowing to initialize and 
          de-initialiaze the I2Sx peripheral in simplex mode:

      (+) User must Implement HAL_I2S_MspInit() function in which he configures 
          all related peripherals resources (CLOCK, GPIO, DMA, IT and NVIC ).

      (+) Call the function HAL_I2S_Init() to configure the selected device with 
          the selected configuration:
        (++) Mode
        (++) Standard 
        (++) Data Format
        (++) MCLK Output
        (++) Audio frequency
        (++) Polarity
        (++) First Bit
        (++) WS Inversion
        (++) IO Swap
        (++) Data 24Bit Alignment
        (++) Fifo Threshold
        (++) Alternate function GPIOs state
        (++) Channel length in SLAVE

     (+) Call the function HAL_I2S_DeInit() to restore the default configuration 
         of the selected I2Sx periperal. 
  @endverbatim
  * @{
  */

/**
  * @brief Initializes the I2S according to the specified parameters 
  *         in the I2S_InitTypeDef and create the associated handle.
  * @param  hi2s: pointer to a I2S_HandleTypeDef structure that contains
  *         the configuration information for I2S module
  * @retval HAL status
  */
HAL_StatusTypeDef HAL_I2S_Init(I2S_HandleTypeDef *hi2s)
{
  uint32_t i2sdiv = 2U, i2sodd = 0U, packetlength = 1U;
  uint32_t tmp = 0U, i2sclk = 0U;

  /* Check the I2S handle allocation */
  if(hi2s == NULL)
  {
    return HAL_ERROR;
  }

  /* Check the I2S parameters */
  assert_param(IS_I2S_ALL_INSTANCE(hi2s->Instance));
  assert_param(IS_I2S_MODE(hi2s->Init.Mode));
  assert_param(IS_I2S_STANDARD(hi2s->Init.Standard));
  assert_param(IS_I2S_DATA_FORMAT(hi2s->Init.DataFormat));
  assert_param(IS_I2S_MCLK_OUTPUT(hi2s->Init.MCLKOutput));
  assert_param(IS_I2S_AUDIO_FREQ(hi2s->Init.AudioFreq));
  assert_param(IS_I2S_CPOL(hi2s->Init.CPOL));
  assert_param(IS_I2S_FIRST_BIT(hi2s->Init.FirstBit));
  assert_param(IS_I2S_WS_INVERSION(hi2s->Init.WSInversion));
  assert_param(IS_I2S_IO_SWAP(hi2s->Init.IOSwap));
  assert_param(IS_I2S_DATA_24BIT_ALIGNMENT(hi2s->Init.Data24BitAlignment));
  assert_param(IS_I2S_FIFO_THRESHOLD(hi2s->Init.FifoThreshold));
  assert_param(IS_I2S_MASTER_KEEP_IO_STATE(hi2s->Init.MasterKeepIOState));
  assert_param(IS_I2S_SLAVE_EXTEND_FRE_DETECTION(hi2s->Init.SlaveExtendFREDetection));

  if(hi2s->State == HAL_I2S_STATE_RESET)
  {
    /* Allocate lock resource and initialize it */
    hi2s->Lock = HAL_UNLOCKED;

    /* Init the low level hardware : GPIO, CLOCK, CORTEX...etc */
    HAL_I2S_MspInit(hi2s);
  }

  hi2s->State = HAL_I2S_STATE_BUSY;

  /* Clear I2S configuration register */
  CLEAR_REG(hi2s->Instance->I2SCFGR);

  /* If the default value has to be written, reinitialize i2sdiv and i2sodd */
  if(hi2s->Init.AudioFreq == I2S_AUDIOFREQ_DEFAULT)
  {
    i2sodd = 0U;
    i2sdiv = 2U;
  }
  /* If the requested audio frequency is not the default, compute the prescaler */
  else
  {
    /* Check the frame length (For the Prescaler computing) *******************/
    /* Set I2S Packet Length value*/
    if(hi2s->Init.DataFormat != I2S_DATAFORMAT_16B)
    {
      /* Packet length is 32 bits */
      packetlength = 32U;
    }
    else
    {
      /* Packet length is 16 bits */
      packetlength = 16U;
    }

    /* I2S standard */
    if(hi2s->Init.Standard <= I2S_STANDARD_LSB)
    {
      /* In I2S standard packet lenght is multiplied by 2 */
      packetlength = packetlength * 2U;
    }

    /* Get the source clock value: based on System Clock value */
    /* SPI1,SPI2 and SPI3 share the same source clock */
    i2sclk = HAL_RCCEx_GetPeriphCLKFreq(RCC_PERIPHCLK_SPI1);

    /* Compute the Real divider depending on the MCLK output state, with a floating point */
    if(hi2s->Init.MCLKOutput == I2S_MCLKOUTPUT_ENABLE)
    {
      /* MCLK output is enabled */
      if (hi2s->Init.DataFormat != I2S_DATAFORMAT_16B)
      {
        tmp = (uint32_t)(((((i2sclk / (packetlength*4)) * 10) / hi2s->Init.AudioFreq)) + 5);
      }
      else
      {
        tmp = (uint32_t)(((((i2sclk / (packetlength*8)) * 10) / hi2s->Init.AudioFreq)) + 5);
      }
    }
    else
    {
      /* MCLK output is disabled */
      tmp = (uint32_t)(((((i2sclk / packetlength) *10 ) / hi2s->Init.AudioFreq)) + 5);
    }

    /* Remove the flatting point */
    tmp = tmp / 10U;

    /* Check the parity of the divider */
    i2sodd = (uint32_t)(tmp & (uint32_t)1U);

    /* Compute the i2sdiv prescaler */
    i2sdiv = (uint32_t)((tmp - i2sodd) / 2U);

    /* Get the Mask for the Odd bit I2SCFGR register */
    i2sodd = (uint32_t)(i2sodd << 24U);
  }

  /* Test if the divider is 1 or 0 or greater than 0xFF */
  if((i2sdiv < 2U) || (i2sdiv > 0xFFU))
  {
    /* Set the default values */
    i2sdiv = 2U;
    i2sodd = 0U;
    /* Set the error code */
    SET_BIT(hi2s->ErrorCode, HAL_I2S_ERROR_PRESCALER);
    return  HAL_ERROR;
  }

  /* Check if the SPI2S is disabled to edit I2SCFGR and CFG1 register */
  if ((hi2s->Instance->CR1 & SPI_CR1_SPE) == SPI_CR1_SPE)
  {
    /* Disable SPI peripheral */
    __HAL_I2S_DISABLE(hi2s);
  }

  /* Clear and configure SPI2S I2SCFGR register */
  MODIFY_REG(hi2s->Instance->I2SCFGR, (SPI_I2SCFGR_I2SMOD       | SPI_I2SCFGR_I2SCFG                 | \
                                       SPI_I2SCFGR_I2SSTD       | SPI_I2SCFGR_PCMSYNC                | \
                                       SPI_I2SCFGR_DATLEN       | SPI_I2SCFGR_CHLEN                  | \
                                       SPI_I2SCFGR_CKPOL        | SPI_I2SCFGR_FIXCH                  | \
                                       SPI_I2SCFGR_WSINV        | SPI_I2SCFGR_DATFMT                 | \
                                       SPI_I2SCFGR_I2SDIV       | SPI_I2SCFGR_ODD                    | \
                                       SPI_I2SCFGR_MCKOE),                                             \
                                      (SPI_I2SCFGR_I2SMOD       | hi2s->Init.Mode                    | \
                                       hi2s->Init.Standard      | hi2s->Init.DataFormat              | \
                                       hi2s->Init.CPOL          | hi2s->Init.SlaveExtendFREDetection | \
                                       hi2s->Init.WSInversion   | hi2s->Init.Data24BitAlignment      | \
                                      (uint32_t)(i2sdiv << 16U) | (uint32_t)(i2sodd)                 | \
                                       hi2s->Init.MCLKOutput));

  /* Clear and configure SPI2S CFG1 register */
  MODIFY_REG(hi2s->Instance->CFG1, SPI_CFG1_FTHLV, (uint32_t)(hi2s->Init.FifoThreshold << 5U));

  /* Unlock the AF configuration to configure CFG2 register*/
  CLEAR_BIT(hi2s->Instance->CR1 , SPI_CR1_IOLOCK);

  /* Clear and configure SPI2S CFG2 register */
  MODIFY_REG(hi2s->Instance->CFG2, SPI_CFG2_LSBFRST | SPI_CFG2_IOSWP , (hi2s->Init.FirstBit | hi2s->Init.IOSwap));

  /* Insure that AFCNTR is managed only by Master */
  if (IS_I2S_MASTER(hi2s->Init.Mode))
  {
    /* Alternate function GPIOs control */
    MODIFY_REG(hi2s->Instance->CFG2, SPI_CFG2_AFCNTR, (hi2s->Init.MasterKeepIOState));
  }

  hi2s->ErrorCode = HAL_I2S_ERROR_NONE;
  hi2s->State= HAL_I2S_STATE_READY;

  return HAL_OK;
}

/**
  * @brief  DeInitializes the I2S peripheral 
  * @param  hi2s: pointer to a I2S_HandleTypeDef structure that contains
  *         the configuration information for I2S module
  * @retval HAL status
  */
HAL_StatusTypeDef HAL_I2S_DeInit(I2S_HandleTypeDef *hi2s)
{
  /* Check the I2S handle allocation */
  if(hi2s == NULL)
  {
    return HAL_ERROR;
  }

  /* Check the parameters */
  assert_param(IS_I2S_ALL_INSTANCE(hi2s->Instance));

  hi2s->State = HAL_I2S_STATE_BUSY;

  /* Disable the I2S Peripheral Clock */
  __HAL_I2S_DISABLE(hi2s);

  /* DeInit the low level hardware: GPIO, CLOCK, NVIC... */
  HAL_I2S_MspDeInit(hi2s);

  hi2s->ErrorCode = HAL_I2S_ERROR_NONE;
  hi2s->State = HAL_I2S_STATE_RESET;

  /* Release Lock */
  __HAL_UNLOCK(hi2s);

  return HAL_OK;
}

/**
  * @brief I2S MSP Init
  * @param  hi2s: pointer to a I2S_HandleTypeDef structure that contains
  *         the configuration information for I2S module
  * @retval None
  */
 __weak void HAL_I2S_MspInit(I2S_HandleTypeDef *hi2s)
{
  /* Prevent unused argument(s) compilation warning */
  UNUSED(hi2s);

  /* NOTE : This function Should not be modified, when the callback is needed,
            the HAL_I2S_MspInit could be implemented in the user file
   */ 
}

/**
  * @brief I2S MSP DeInit
  * @param  hi2s: pointer to a I2S_HandleTypeDef structure that contains
  *         the configuration information for I2S module
  * @retval None
  */
 __weak void HAL_I2S_MspDeInit(I2S_HandleTypeDef *hi2s)
{
  /* Prevent unused argument(s) compilation warning */
  UNUSED(hi2s);

  /* NOTE : This function Should not be modified, when the callback is needed,
            the HAL_I2S_MspDeInit could be implemented in the user file
   */ 
}

/**
  * @}
  */

/** @defgroup I2S_Exported_Functions_Group2 IO operation functions
  *  @brief Data transfers functions 
  *
@verbatim
 ===============================================================================
                      ##### IO operation functions #####
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
        (++) HAL_I2S_Transmit()
        (++) HAL_I2S_Receive()
        
    (#) No-Blocking mode functions with Interrupt are :
        (++) HAL_I2S_Transmit_IT()
        (++) HAL_I2S_Receive_IT()

    (#) No-Blocking mode functions with DMA are :
        (++) HAL_I2S_Transmit_DMA()
        (++) HAL_I2S_Receive_DMA()

    (#) A set of Transfer Complete Callbacks are provided in non Blocking mode:
        (++) HAL_I2S_TxCpltCallback()
        (++) HAL_I2S_TxHalfCpltCallback()
        (++) HAL_I2S_RxCpltCallback()
        (++) HAL_I2S_RxHalfCpltCallback()
        (++) HAL_I2S_ErrorCallback()

@endverbatim
  * @{
  */

/**
  * @brief  Transmit an amount of data in blocking mode
  * @param  hi2s: pointer to a I2S_HandleTypeDef structure that contains
  *         the configuration information for I2S module
  * @param  pData: a 16-bit pointer to data buffer.
  * @param  Size: number of frames to be sent.
  * @param  Timeout: Timeout duration
  * @note   The I2S is kept enabled at the end of transaction to avoid the clock de-synchronization 
  *         between Master and Slave(example: audio streaming).
  * @note   This function can use an Audio Frequency up to 48KHz when I2S Clock Source is 32MHz
  * @retval HAL status
  */
HAL_StatusTypeDef HAL_I2S_Transmit(I2S_HandleTypeDef *hi2s, uint16_t *pData, uint16_t Size, uint32_t Timeout)
{
  uint32_t tickstart = 0U;
  uint32_t isDataFormat16B = 2U;

  /* Check Mode parameter */
  assert_param(IS_I2S_TX_MODE(hi2s->Init.Mode));

  if((pData == NULL ) || (Size == 0U)) 
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
    }
    else
    {
      hi2s->TxXferSize  = Size;
      hi2s->TxXferCount = Size;
    }

    /* Set state and reset error code */
    hi2s->ErrorCode = HAL_I2S_ERROR_NONE;
    hi2s->State = HAL_I2S_STATE_BUSY_TX;
    hi2s->pTxBuffPtr = pData;

    /* Check if the SPI2S is already enabled */
    if((hi2s->Instance->CR1 & SPI_CR1_SPE) != SPI_CR1_SPE)
    {
      /* Enable SPI peripheral */
      __HAL_I2S_ENABLE(hi2s);
    }

    if(IS_I2S_MASTER(hi2s->Init.Mode))
    {
      hi2s->Instance->CR1 |= SPI_CR1_CSTART;
    }

    /* Transmit data in 32 Bit mode */
    if (!isDataFormat16B)
    {
      while (hi2s->TxXferCount > 0U)
      {
        /* Wait until TXE flag is set to send data */
        if (__HAL_I2S_GET_FLAG(hi2s, I2S_FLAG_TXE))
        {
          *((__IO uint32_t*)&hi2s->Instance->TXDR) = *((uint32_t*)hi2s->pTxBuffPtr);
          hi2s->pTxBuffPtr  += sizeof(uint32_t);
          hi2s->TxXferCount -= 2U;
        }
        else
        {
          /* Timeout management */
          if ((Timeout == 0U) || ((Timeout != HAL_MAX_DELAY) && ((HAL_GetTick() - tickstart) >=  Timeout)))
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
    }
    /* Transmit data in 16 Bit mode */
    else
    {
      while (hi2s->TxXferCount > 0U)
      {
        if (__HAL_I2S_GET_FLAG(hi2s, I2S_FLAG_TXE))
        {
          if ((hi2s->TxXferCount > 1U) && (hi2s->Init.FifoThreshold > SPI_FIFO_THRESHOLD_01DATA))
          {
            *((__IO uint32_t*)&hi2s->Instance->TXDR) = *((uint32_t*)hi2s->pTxBuffPtr);
            hi2s->pTxBuffPtr  += sizeof(uint32_t);
            hi2s->TxXferCount -= 2U;
          }
          else
          {
            *((__IO uint16_t*)&hi2s->Instance->TXDR) = (*hi2s->pTxBuffPtr++);
            hi2s->TxXferCount--;
          }
        }
        else
        {
          /* Timeout management */
          if ((Timeout == 0U) || ((Timeout != HAL_MAX_DELAY) && ((HAL_GetTick() - tickstart) >=  Timeout)))
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
    }

    /* Wait until TXE flag is set, to confirm the end of the transaction */
    if (I2S_WaitFlagStateUntilTimeout(hi2s, I2S_FLAG_TXE, RESET, Timeout) != HAL_OK)
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
  * @brief  Receive an amount of data in blocking mode 
  * @param  hi2s: pointer to a I2S_HandleTypeDef structure that contains
  *         the configuration information for I2S module
  * @param  pData: a 16-bit pointer to data buffer.
  * @param  Size: number of frames to be sent.
  * @param  Timeout: Timeout duration
  * @note   The I2S is kept enabled at the end of transaction to avoid the clock de-synchronization 
  *         between Master and Slave(example: audio streaming).
  * @note   In I2S Master Receiver mode, just after enabling the peripheral the clock will be generate
  *         in continuous way and as the I2S is not disabled at the end of the I2S transaction.
  * @note   This function can use an Audio Frequency up to 44KHz when I2S Clock Source is 32MHz
  * @retval HAL status
  */
HAL_StatusTypeDef HAL_I2S_Receive(I2S_HandleTypeDef *hi2s, uint16_t *pData, uint16_t Size, uint32_t Timeout)
{
  uint32_t tickstart = 0U;
  uint32_t isDataFormat16B = 2U;

  /* Check Mode parameter */
  assert_param(IS_I2S_RX_MODE(hi2s->Init.Mode));

  if((pData == NULL ) || (Size == 0U)) 
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
      hi2s->RxXferSize = (Size << 1U);
      hi2s->RxXferCount = (Size << 1U);
    }
    else
    {
      hi2s->RxXferSize = Size;
      hi2s->RxXferCount = Size;
    }

    /* Set state and reset error code */
    hi2s->ErrorCode = HAL_I2S_ERROR_NONE;
    hi2s->State = HAL_I2S_STATE_BUSY_RX;
    hi2s->pRxBuffPtr = pData;

    /* Check if the SPI2S is already enabled */ 
    if((hi2s->Instance->CR1 & SPI_CR1_SPE) != SPI_CR1_SPE)
    {
      /* Enable SPI peripheral */
      __HAL_I2S_ENABLE(hi2s);
    }
    
    if(IS_I2S_MASTER(hi2s->Init.Mode))
    {
      hi2s->Instance->CR1 |= SPI_CR1_CSTART;
    }

    /* Check if Master Receiver mode is selected */
    if((hi2s->Instance->I2SCFGR & SPI_I2SCFGR_I2SCFG) == I2S_MODE_MASTER_RX)
    {
      /* Clear the Overrun Flag */ 
      __HAL_I2S_CLEAR_OVRFLAG(hi2s);
    }

    /* Receive data in 32 Bit mode */
    if ((!isDataFormat16B))
    {
      /* Transfer loop */
      while (hi2s->RxXferCount > 0U)
      {
        /* Check the RXNE flag */
        if (__HAL_I2S_GET_FLAG(hi2s, I2S_FLAG_RXNE))
        {
          *((uint32_t *)hi2s->pRxBuffPtr) = *((__IO uint32_t *)&hi2s->Instance->RXDR);
          hi2s->pRxBuffPtr += sizeof(uint32_t);
          hi2s->RxXferCount--;
        }
        else
        {
          /* Timeout management */
          if ((Timeout == 0U) || ((Timeout != HAL_MAX_DELAY) && ((HAL_GetTick() - tickstart) >=  Timeout)))
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
    }
    /* Receive data in 16 Bit mode */
    else
    {
      /* Transfer loop */
      while (hi2s->RxXferCount > 0U)
      {
        /* Check the RXNE flag */
        if (__HAL_I2S_GET_FLAG(hi2s, I2S_FLAG_RXNE))
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
        else
        {
          /* Timeout management */
          if ((Timeout == 0U) || ((Timeout != HAL_MAX_DELAY) && ((HAL_GetTick() - tickstart) >=  Timeout)))
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
  * @brief  Transmit an amount of data in non-blocking mode with Interrupt
  * @param  hi2s: pointer to a I2S_HandleTypeDef structure that contains
  *         the configuration information for I2S module
  * @param pData: a 16-bit pointer to data buffer.
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
HAL_StatusTypeDef HAL_I2S_Transmit_IT(I2S_HandleTypeDef *hi2s, uint16_t *pData, uint16_t Size)
{
  /* Check Mode parameter */
  assert_param(IS_I2S_TX_MODE(hi2s->Init.Mode));

  /* Process Locked */
  __HAL_LOCK(hi2s);

  if((pData == NULL) || (Size == 0U)) 
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
  hi2s->pTxBuffPtr  = pData;
  hi2s->TxXferSize  = Size;
  hi2s->TxXferCount = Size;

  /* Init field not used in handle to zero */
  hi2s->pRxBuffPtr  = NULL;
  hi2s->RxXferSize  = 0U;
  hi2s->RxXferCount = 0U;
  hi2s->RxISR       = NULL;

  /* Set the function for IT treatment */
  if (hi2s->Init.DataFormat > I2S_DATAFORMAT_16B)
  {
    hi2s->TxISR = I2S_TxISR_32BIT;
  }
  else
  {
    hi2s->TxISR = I2S_TxISR_16BIT;
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
  __HAL_I2S_ENABLE_IT(hi2s, (I2S_IT_TXE | I2S_IT_ERR));

  /* Process Unlocked */
  __HAL_UNLOCK(hi2s);

  return HAL_OK;
}

/**
  * @brief  Receive an amount of data in non-blocking mode with Interrupt
  * @param  hi2s: pointer to a I2S_HandleTypeDef structure that contains
  *         the configuration information for I2S module
  * @param pData: a 16-bit pointer to the Receive data buffer.
  * @param Size: number of data sample to be sent:
  * @note When a 16-bit data frame or a 16-bit data frame extended is selected during the I2S
  *       configuration phase, the Size parameter means the number of 16-bit data length 
  *       in the transaction and when a 24-bit data frame or a 32-bit data frame is selected 
  *       the Size parameter means the number of 16-bit data length. 
  * @note The I2S is kept enabled at the end of transaction to avoid the clock de-synchronization 
  *       between Master and Slave(example: audio streaming).
  * @note It is recommended to use DMA for the I2S receiver to avoid de-synchronisation 
  * between Master and Slave otherwise the I2S interrupt should be optimized. 
  * @note This function can use an Audio Frequency up to 48KHz when I2S Clock Source is 32MHz  
  * @retval HAL status
  */
HAL_StatusTypeDef HAL_I2S_Receive_IT(I2S_HandleTypeDef *hi2s, uint16_t *pData, uint16_t Size)
{
  /* Check Mode parameter */
  assert_param(IS_I2S_RX_MODE(hi2s->Init.Mode));

  /* Process Locked */
  __HAL_LOCK(hi2s);

  /* Set the transaction information */
  hi2s->State       = HAL_I2S_STATE_BUSY_TX;
  hi2s->ErrorCode   = HAL_I2S_ERROR_NONE;
  hi2s->pRxBuffPtr  = pData;
  hi2s->RxXferSize  = Size;
  hi2s->RxXferCount = Size;

  /* Init field not used in handle to zero */
  hi2s->pTxBuffPtr  = NULL;
  hi2s->TxXferSize  = 0U;
  hi2s->TxXferCount = 0U;
  hi2s->TxISR       = NULL;

  /* Set the function for IT treatment */
  if (hi2s->Init.DataFormat > I2S_DATAFORMAT_16B)
  {
    hi2s->RxISR = I2S_RxISR_32BIT;
  }
  else
  {
    hi2s->RxISR = I2S_RxISR_16BIT;
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
  __HAL_I2S_ENABLE_IT(hi2s, (I2S_IT_RXNE | I2S_IT_ERR));

  /* Process Unlocked */
  __HAL_UNLOCK(hi2s);

  return HAL_OK;
}

/**
  * @brief Transmit an amount of data in non-blocking mode with DMA
  * @param  hi2s: pointer to a I2S_HandleTypeDef structure that contains
  *         the configuration information for I2S module
  * @param pData: a 16-bit pointer to the Transmit data buffer.
  * @param Size: number of data sample to be sent:
  * @note When a 16-bit data frame or a 16-bit data frame extended is selected during the I2S
  *       configuration phase, the Size parameter means the number of 16-bit data length 
  *       in the transaction and when a 24-bit data frame or a 32-bit data frame is selected 
  *       the Size parameter means the number of 16-bit data length. 
  * @note The I2S is kept enabled at the end of transaction to avoid the clock de-synchronization 
  *       between Master and Slave(example: audio streaming).
  * @retval HAL status
  */
HAL_StatusTypeDef HAL_I2S_Transmit_DMA(I2S_HandleTypeDef *hi2s, uint16_t *pData, uint16_t Size)
{
  /* Check Mode parameter */
  assert_param(IS_I2S_TX_MODE(hi2s->Init.Mode));

  if((pData == NULL) || (Size == 0U))
  {
    return  HAL_ERROR;
  }

  /* Process Locked */
  __HAL_LOCK(hi2s);

  if(hi2s->State == HAL_I2S_STATE_READY)
  {
    hi2s->pTxBuffPtr = pData;
    hi2s->State      = HAL_I2S_STATE_BUSY_TX;
    hi2s->ErrorCode  = HAL_I2S_ERROR_NONE;

    if(((hi2s->Instance->I2SCFGR & (SPI_I2SCFGR_DATLEN | SPI_I2SCFGR_CHLEN)) == I2S_DATAFORMAT_24B)||\
      ((hi2s->Instance->I2SCFGR & (SPI_I2SCFGR_DATLEN | SPI_I2SCFGR_CHLEN)) == I2S_DATAFORMAT_32B))
    {
      hi2s->TxXferSize  = (Size << 1U);
      hi2s->TxXferCount = (Size << 1U);
    }
    else
    {
      hi2s->TxXferSize  = Size;
      hi2s->TxXferCount = Size;
    }

    /* Set the I2S Tx DMA Half transfert complete callback */
    hi2s->hdmatx->XferHalfCpltCallback = I2S_DMATxHalfCplt;

    /* Set the I2S Tx DMA transfert complete callback */
    hi2s->hdmatx->XferCpltCallback = I2S_DMATxCplt;

    /* Set the DMA error callback */
    hi2s->hdmatx->XferErrorCallback = I2S_DMAError;

    /* Enable the Tx DMA Channel */
    HAL_DMA_Start_IT(hi2s->hdmatx, (uint32_t)hi2s->pTxBuffPtr, (uint32_t)&hi2s->Instance->TXDR, hi2s->TxXferSize);

    /* Check if the I2S Tx request is already enabled */ 
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
    
        /* Enable Tx DMA Request */
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
  * @brief Receive an amount of data in non-blocking mode with DMA 
  * @param  hi2s: pointer to a I2S_HandleTypeDef structure that contains
  *         the configuration information for I2S module
  * @param pData: a 16-bit pointer to the Receive data buffer.
  * @param Size: number of data sample to be sent:
  * @note When a 16-bit data frame or a 16-bit data frame extended is selected during the I2S
  *       configuration phase, the Size parameter means the number of 16-bit data length 
  *       in the transaction and when a 24-bit data frame or a 32-bit data frame is selected 
  *       the Size parameter means the number of 16-bit data length. 
  * @note The I2S is kept enabled at the end of transaction to avoid the clock de-synchronization 
  *       between Master and Slave(example: audio streaming).
  * @retval HAL status
  */
HAL_StatusTypeDef HAL_I2S_Receive_DMA(I2S_HandleTypeDef *hi2s, uint16_t *pData, uint16_t Size)
{
  /* Check Mode parameter */
  assert_param(IS_I2S_RX_MODE(hi2s->Init.Mode));

  if((pData == NULL) || (Size == 0U))
  {
    return  HAL_ERROR;
  }

  /* Process Locked */
  __HAL_LOCK(hi2s);

  if(hi2s->State == HAL_I2S_STATE_READY)
  {
    hi2s->pRxBuffPtr = pData;
    hi2s->State = HAL_I2S_STATE_BUSY_RX;
    hi2s->ErrorCode = HAL_I2S_ERROR_NONE;

    if(((hi2s->Instance->I2SCFGR & (SPI_I2SCFGR_DATLEN | SPI_I2SCFGR_CHLEN)) == I2S_DATAFORMAT_24B)||\
      ((hi2s->Instance->I2SCFGR & (SPI_I2SCFGR_DATLEN | SPI_I2SCFGR_CHLEN)) == I2S_DATAFORMAT_32B))
    {
      hi2s->RxXferSize = (Size << 1U);
      hi2s->RxXferCount = (Size << 1U);
    }
    else
    {
      hi2s->RxXferSize = Size;
      hi2s->RxXferCount = Size;
    }

    /* Set the I2S Rx DMA Half transfert complete callback */
    hi2s->hdmarx->XferHalfCpltCallback = I2S_DMARxHalfCplt;
    
    /* Set the I2S Rx DMA transfert complete callback */
    hi2s->hdmarx->XferCpltCallback = I2S_DMARxCplt;
    
    /* Set the DMA error callback */
    hi2s->hdmarx->XferErrorCallback = I2S_DMAError;
    
    /* Check if Master Receiver mode is selected */
    if((hi2s->Instance->I2SCFGR & SPI_I2SCFGR_I2SCFG) == I2S_MODE_MASTER_RX)
    {
      /* Clear the Overrun Flag by a read operation to the SPI_DR register followed by a read
      access to the SPI_SR register. */ 
      __HAL_I2S_CLEAR_OVRFLAG(hi2s);
    }

    /* Enable the Rx DMA Channel */
    HAL_DMA_Start_IT(hi2s->hdmarx, (uint32_t)&hi2s->Instance->RXDR, (uint32_t)hi2s->pRxBuffPtr, hi2s->RxXferSize);

    /* Check if the I2S Rx request is already enabled */ 
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
  * @brief Pauses the audio stream playing from the Media.
  * @param  hi2s: pointer to a I2S_HandleTypeDef structure that contains
  *         the configuration information for I2S module
  * @retval HAL status
  */
HAL_StatusTypeDef HAL_I2S_DMAPause(I2S_HandleTypeDef *hi2s)
{
  /* Process Locked */
  __HAL_LOCK(hi2s);

  /* Check if the SPI2S is disabled to edit CFG1 register */
  if ((hi2s->Instance->CR1 & SPI_CR1_SPE) != SPI_CR1_SPE)
  {
    /* Disable the I2S DMA Tx & Rx requests */
    CLEAR_BIT(hi2s->Instance->CFG1, SPI_CFG1_TXDMAEN | SPI_CFG1_RXDMAEN);
  }
  else
  {
    /* Disable SPI peripheral */
    __HAL_I2S_DISABLE(hi2s);

    /* Disable the I2S DMA Tx & Rx requests */
    CLEAR_BIT(hi2s->Instance->CFG1, SPI_CFG1_TXDMAEN | SPI_CFG1_RXDMAEN);

    /* Enable SPI peripheral */
    __HAL_I2S_ENABLE(hi2s);
  }

  /* Process Unlocked */
  __HAL_UNLOCK(hi2s);
  
  return HAL_OK; 
}

/**
  * @brief Resumes the audio stream playing from the Media.
  * @param  hi2s: pointer to a I2S_HandleTypeDef structure that contains
  *         the configuration information for I2S module
  * @retval HAL status
  */
HAL_StatusTypeDef HAL_I2S_DMAResume(I2S_HandleTypeDef *hi2s)
{
  /* Process Locked */
  __HAL_LOCK(hi2s);
  
  /* Check if the SPI2S is disabled to edit CFG1 register */
  if ((hi2s->Instance->CR1 & SPI_CR1_SPE) != SPI_CR1_SPE)
  {
    /* Enable the I2S DMA Tx & Rx requests */
    SET_BIT(hi2s->Instance->CFG1, SPI_CFG1_TXDMAEN | SPI_CFG1_RXDMAEN);
  }
  else
  {
    /* Disable SPI peripheral */
    __HAL_I2S_DISABLE(hi2s);

    /*  Enable the I2S DMA Tx & Rx requests */
    SET_BIT(hi2s->Instance->CFG1, SPI_CFG1_TXDMAEN | SPI_CFG1_RXDMAEN);
  }

  /* Enable I2S peripheral */
  __HAL_I2S_ENABLE(hi2s);

  /* Process Unlocked */
  __HAL_UNLOCK(hi2s);
  
  return HAL_OK;
}

/**
  * @brief Stops the audio stream playing from the Media.
  * @param  hi2s: pointer to a I2S_HandleTypeDef structure that contains
  *         the configuration information for I2S module
  * @retval HAL status
  */
HAL_StatusTypeDef HAL_I2S_DMAStop(I2S_HandleTypeDef *hi2s)
{
  /* Process Locked */
  __HAL_LOCK(hi2s);

  /* Check if the SPI2S is disabled to edit CFG1 register */
  if ((hi2s->Instance->CR1 & SPI_CR1_SPE) != SPI_CR1_SPE)
  {
    /* Disable the I2S Tx/Rx DMA requests */
    CLEAR_BIT(hi2s->Instance->CFG1, SPI_CFG1_TXDMAEN);
    CLEAR_BIT(hi2s->Instance->CFG1, SPI_CFG1_RXDMAEN);
  }
  else
  {
    /* Disable SPI peripheral */
    __HAL_I2S_DISABLE(hi2s);

    /* Disable the I2S Tx/Rx DMA requests */
    CLEAR_BIT(hi2s->Instance->CFG1, SPI_CFG1_TXDMAEN);
    CLEAR_BIT(hi2s->Instance->CFG1, SPI_CFG1_RXDMAEN);

    /* Enable SPI peripheral */
    __HAL_I2S_ENABLE(hi2s);
  }
  
  /* Abort the I2S DMA Channel tx */
  if(hi2s->hdmatx != NULL)
  {
    /* Disable the I2S DMA channel */
    __HAL_DMA_DISABLE(hi2s->hdmatx);
    HAL_DMA_Abort(hi2s->hdmatx);
  }
  /* Abort the I2S DMA Channel rx */
  if(hi2s->hdmarx != NULL)
  {
    /* Disable the I2S DMA channel */
    __HAL_DMA_DISABLE(hi2s->hdmarx);
    HAL_DMA_Abort(hi2s->hdmarx);
  }

  /* Disable I2S peripheral */
  __HAL_I2S_DISABLE(hi2s);
  
  hi2s->State = HAL_I2S_STATE_READY;
  
  /* Process Unlocked */
  __HAL_UNLOCK(hi2s);
  
  return HAL_OK;
}

/**
  * @brief  This function handles I2S interrupt request.
  * @param  hi2s: pointer to a I2S_HandleTypeDef structure that contains
  *         the configuration information for I2S module
  * @retval None
  */
void HAL_I2S_IRQHandler(I2S_HandleTypeDef *hi2s)
{  
  uint32_t itsource = hi2s->Instance->IER;
  uint32_t i2ssr = hi2s->Instance->SR;

  /* I2S in mode Receiver ------------------------------------------------*/
  if(((i2ssr & I2S_FLAG_OVR) != I2S_FLAG_OVR) &&
     ((i2ssr & I2S_FLAG_RXNE) == I2S_FLAG_RXNE) && ((itsource & I2S_IT_RXNE) != RESET))
  {
    hi2s->RxISR(hi2s);
    return;
  }

  /* I2S in mode Transmitter ---------------------------------------------*/
  if(((i2ssr & I2S_FLAG_TXE) == I2S_FLAG_TXE) && ((itsource & I2S_IT_RXNE) != RESET))
  {
    hi2s->TxISR(hi2s);
    return;
  }

  /* I2S interrupt error -------------------------------------------------*/
  if((itsource & I2S_IT_ERR) != RESET)
  {
    /* I2S Overrun error interrupt occured ---------------------------------*/
    if((i2ssr & I2S_FLAG_OVR) == I2S_FLAG_OVR)
    {
      /* Disable RXNE and ERR interrupt */
      __HAL_I2S_DISABLE_IT(hi2s, (I2S_IT_RXNE | I2S_IT_ERR));
      
      /* Set the error code and execute error callback*/
      SET_BIT(hi2s->ErrorCode, HAL_I2S_ERROR_OVR);
    }

    /* I2S Underrun error interrupt occured --------------------------------*/
    if((i2ssr & I2S_FLAG_UDR) == I2S_FLAG_UDR)
    {
      /* Disable TXE and ERR interrupt */
      __HAL_I2S_DISABLE_IT(hi2s, (I2S_IT_TXE | I2S_IT_ERR));

      /* Set the error code and execute error callback*/
      SET_BIT(hi2s->ErrorCode, HAL_I2S_ERROR_UDR);
    }

    /* Set the I2S State ready */
    hi2s->State = HAL_I2S_STATE_READY;
    /* Call the Error Callback */
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
static HAL_StatusTypeDef I2S_WaitFlagStateUntilTimeout(I2S_HandleTypeDef *hi2s, uint32_t Flag, uint32_t State, uint32_t Timeout)
{
  uint32_t tickstart = 0U;

  /* Get tick */
  tickstart = HAL_GetTick();

  /* Wait until flag is set */
  while ((__HAL_I2S_GET_FLAG(hi2s, Flag) ? SET : RESET) != State)
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

  return HAL_OK;
}

/**
  * @brief Tx Transfer Half completed callbacks
  * @param  hi2s: pointer to a I2S_HandleTypeDef structure that contains
  *         the configuration information for I2S module
  * @retval None
  */
 __weak void HAL_I2S_TxHalfCpltCallback(I2S_HandleTypeDef *hi2s)
{
  /* Prevent unused argument(s) compilation warning */
  UNUSED(hi2s);

  /* NOTE : This function Should not be modified, when the callback is needed,
            the HAL_I2S_TxHalfCpltCallback could be implemented in the user file
   */ 
}

/**
  * @brief  Tx Transfer completed callbacks
  * @param  hi2s: pointer to a I2S_HandleTypeDef structure that contains
  *         the configuration information for I2S module
  * @retval None
  */
 __weak void HAL_I2S_TxCpltCallback(I2S_HandleTypeDef *hi2s)
{
  /* Prevent unused argument(s) compilation warning */
  UNUSED(hi2s);

  /* NOTE : This function Should not be modified, when the callback is needed,
            the HAL_I2S_TxCpltCallback could be implemented in the user file
   */ 
}

/**
  * @brief  Rx Transfer half completed callbacks
  * @param  hi2s: pointer to a I2S_HandleTypeDef structure that contains
  *         the configuration information for I2S module
  * @retval None
  */
__weak void HAL_I2S_RxHalfCpltCallback(I2S_HandleTypeDef *hi2s)
{
  /* Prevent unused argument(s) compilation warning */
  UNUSED(hi2s);

  /* NOTE : This function Should not be modified, when the callback is needed,
            the HAL_I2S_RxHalfCpltCallback could be implemented in the user file
   */
}

/**
  * @brief Rx Transfer completed callbacks
  * @param  hi2s: pointer to a I2S_HandleTypeDef structure that contains
  *         the configuration information for I2S module
  * @retval None
  */
__weak void HAL_I2S_RxCpltCallback(I2S_HandleTypeDef *hi2s)
{
  /* Prevent unused argument(s) compilation warning */
  UNUSED(hi2s);

  /* NOTE : This function Should not be modified, when the callback is needed,
            the HAL_I2S_RxCpltCallback could be implemented in the user file
   */
}

/**
  * @brief I2S error callbacks
  * @param  hi2s: pointer to a I2S_HandleTypeDef structure that contains
  *         the configuration information for I2S module
  * @retval None
  */
 __weak void HAL_I2S_ErrorCallback(I2S_HandleTypeDef *hi2s)
{
  /* Prevent unused argument(s) compilation warning */
  UNUSED(hi2s);

  /* NOTE : This function Should not be modified, when the callback is needed,
            the HAL_I2S_ErrorCallback could be implemented in the user file
   */
}

/**
  * @}
  */

/** @defgroup I2S_Exported_Functions_Group3 Peripheral State and Errors functions 
  *  @brief   Peripheral State functions 
  *
@verbatim
 ===============================================================================
                      ##### Peripheral State and Errors functions #####
 ===============================================================================
    [..]
    This subsection permits to get in run-time the status of the peripheral 
    and the data flow.

@endverbatim
  * @{
  */

/**
  * @brief  Return the I2S state
  * @param  hi2s: pointer to a I2S_HandleTypeDef structure that contains
  *         the configuration information for I2S module
  * @retval HAL state
  */
HAL_I2S_StateTypeDef HAL_I2S_GetState(I2S_HandleTypeDef *hi2s)
{
  return hi2s->State;
}

/**
  * @brief  Return the I2S error code
  * @param  hi2s: pointer to a I2S_HandleTypeDef structure that contains
  *         the configuration information for I2S module
  * @retval I2S Error Code
  */
uint32_t HAL_I2S_GetError(I2S_HandleTypeDef *hi2s)
{
  return hi2s->ErrorCode;
}
/**
  * @}
  */

/**
  * @}
  */

/* Private functions ---------------------------------------------------------*/
/** @addtogroup I2S_Private
  * @{
  */
/**
  * @brief  DMA I2S transmit process complete callback 
  * @param  hdma: pointer to a DMA_HandleTypeDef structure that contains
  *                the configuration information for the specified DMA module.
  * @retval None
  */
static void I2S_DMATxCplt(DMA_HandleTypeDef *hdma)
{
  I2S_HandleTypeDef* hi2s = (I2S_HandleTypeDef*)((DMA_HandleTypeDef*)hdma)->Parent;

  if(((((DMA_Stream_TypeDef *)hdma->Instance)->CR) & DMA_SxCR_CIRC) == 0U)
  {
    /* Check if the SPI2S is disabled to edit CFG1 register */
    if ((hi2s->Instance->CR1 & SPI_CR1_SPE) != SPI_CR1_SPE)
    {
      /* Disable Tx DMA Request */
      CLEAR_BIT(hi2s->Instance->CFG1, SPI_CFG1_TXDMAEN);
    }
    else
    {
      /* Disable SPI peripheral */
      __HAL_I2S_DISABLE(hi2s);
  
      /* Disable Tx DMA Request */
      CLEAR_BIT(hi2s->Instance->CFG1, SPI_CFG1_TXDMAEN);
  
      /* Enable SPI peripheral */
      __HAL_I2S_ENABLE(hi2s);
    }

    hi2s->TxXferCount = 0U;

    if(hi2s->State == HAL_I2S_STATE_BUSY_TX_RX)
    {
      if(hi2s->RxXferCount == 0U)
      {
        hi2s->State = HAL_I2S_STATE_READY;
      }
    }
    else
    {
      hi2s->State = HAL_I2S_STATE_READY; 
    }
  }
  HAL_I2S_TxCpltCallback(hi2s);
}

/**
  * @brief  DMA I2S transmit process half complete callback
  * @param  hdma: pointer to a DMA_HandleTypeDef structure that contains
                  the configuration information for the specified DMA module.
  * @retval None
  */
static void I2S_DMATxHalfCplt(DMA_HandleTypeDef *hdma)
{
  I2S_HandleTypeDef* hi2s = (I2S_HandleTypeDef*)((DMA_HandleTypeDef*)hdma)->Parent;

  HAL_I2S_TxHalfCpltCallback(hi2s);
}

/**
  * @brief  DMA I2S receive process complete callback 
  * @param  hdma: pointer to a DMA_HandleTypeDef structure that contains
  *                the configuration information for the specified DMA module.
  * @retval None
  */
static void I2S_DMARxCplt(DMA_HandleTypeDef *hdma)
{
  I2S_HandleTypeDef* hi2s = (I2S_HandleTypeDef*)((DMA_HandleTypeDef*)hdma)->Parent;

  if(((((DMA_Stream_TypeDef *)hdma->Instance)->CR) & DMA_SxCR_CIRC) == 0U)
  {
    /* Check if the SPI2S is disabled to edit CFG1 register */
    if ((hi2s->Instance->CR1 & SPI_CR1_SPE) != SPI_CR1_SPE)
    {
      /* Disable Rx DMA Request */
      CLEAR_BIT(hi2s->Instance->CFG1, SPI_CFG1_RXDMAEN);
    }
    else
    {
      /* Disable SPI peripheral */
      __HAL_I2S_DISABLE(hi2s);
  
      /* Disable Rx DMA Request */
      CLEAR_BIT(hi2s->Instance->CFG1, SPI_CFG1_RXDMAEN);
  
      /* Enable SPI peripheral */
      __HAL_I2S_ENABLE(hi2s);
    }

    hi2s->RxXferCount = 0U;
    if(hi2s->State == HAL_I2S_STATE_BUSY_TX_RX)
    {
      if(hi2s->TxXferCount == 0U)
      {
        hi2s->State = HAL_I2S_STATE_READY;
      }
    }
    else
    {
      hi2s->State = HAL_I2S_STATE_READY;
    }
  }
  HAL_I2S_RxCpltCallback(hi2s);
}

/**
  * @brief  DMA I2S receive process half complete callback 
  * @param  hdma: pointer to a DMA_HandleTypeDef structure that contains
  *                the configuration information for the specified DMA module.
  * @retval None
  */
static void I2S_DMARxHalfCplt(DMA_HandleTypeDef *hdma)
{
  I2S_HandleTypeDef* hi2s = (I2S_HandleTypeDef*)((DMA_HandleTypeDef*)hdma)->Parent;

  HAL_I2S_RxHalfCpltCallback(hi2s); 
}

/**
  * @brief  DMA I2S communication error callback
  * @param  hdma: pointer to a DMA_HandleTypeDef structure that contains
  *               the configuration information for the specified DMA module.
  * @retval None
  */
static void I2S_DMAError(DMA_HandleTypeDef *hdma)
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
  * @brief  Manage the 16-bit receive in Interrupt context.
  * @param  hi2s: pointer to a I2S_HandleTypeDef structure that contains
  *         the configuration information for I2S module
  * @retval None
  */
static void I2S_RxISR_16BIT(struct __I2S_HandleTypeDef *hi2s)
{
  *((uint16_t *)hi2s->pRxBuffPtr) = hi2s->Instance->RXDR;
  hi2s->pRxBuffPtr += sizeof(uint16_t);
  hi2s->RxXferCount--;

  if (hi2s->RxXferCount == 0U)
  {
    I2S_CloseRx_ISR(hi2s);
  }
}

/**
  * @brief  Manage the 32-bit receive in Interrupt context.
  * @param  hi2s: pointer to a I2S_HandleTypeDef structure that contains
  *         the configuration information for I2S module
  * @retval None
  */
static void I2S_RxISR_32BIT(struct __I2S_HandleTypeDef *hi2s)
{
  *((uint32_t *)hi2s->pRxBuffPtr) = hi2s->Instance->RXDR;
  hi2s->pRxBuffPtr += sizeof(uint32_t);
  hi2s->RxXferCount--;

  if (hi2s->RxXferCount == 0U)
  {
    I2S_CloseRx_ISR(hi2s);
  }
}

/**
  * @brief  Handle the data 16-bit transmit in Interrupt mode.
  * @param  hi2s: pointer to a I2S_HandleTypeDef structure that contains
  *         the configuration information for I2S module
  * @retval None
  */
static void I2S_TxISR_16BIT(struct __I2S_HandleTypeDef *hi2s)
{
  /* Transmit data in 16 Bit mode */
  *((__IO uint16_t *)&hi2s->Instance->TXDR) = *((uint16_t *)hi2s->pTxBuffPtr);
  hi2s->pTxBuffPtr += sizeof(uint16_t);
  hi2s->TxXferCount--;

  if (hi2s->TxXferCount == 0U)
  {
    I2S_CloseTx_ISR(hi2s);
  }
}

/**
  * @brief  Handle the data 32-bit transmit in Interrupt mode.
  * @param  hi2s: pointer to a I2S_HandleTypeDef structure that contains
  *         the configuration information for I2S module
  * @retval None
  */
static void I2S_TxISR_32BIT(struct __I2S_HandleTypeDef *hi2s)
{
  /* Transmit data in 16 Bit mode */
  *((__IO uint32_t *)&hi2s->Instance->TXDR) = *((uint32_t *)hi2s->pTxBuffPtr);
  hi2s->pTxBuffPtr += sizeof(uint32_t);
  hi2s->TxXferCount--;

  if (hi2s->TxXferCount == 0U)
  {
    I2S_CloseTx_ISR(hi2s);
  }
}

/**
  * @brief  Handle the end of the RX transaction.
  * @param  hi2s: pointer to a I2S_HandleTypeDef structure that contains
  *         the configuration information for I2S module
  * @retval None
  */
static void I2S_CloseRx_ISR(I2S_HandleTypeDef *hi2s)
{
  /* Disable RXNE and ERR interrupt */
  __HAL_I2S_DISABLE_IT(hi2s, (I2S_IT_RXNE | I2S_IT_ERR));

  /* Clear underrun flag in 1 Line communication mode because transmitted is not feeded */
  if (IS_I2S_FD_MODE(hi2s->Init.Mode))
  {
    *((__IO uint8_t *)&hi2s->Instance->TXDR) = 0x01U;
    __HAL_I2S_CLEAR_UDRFLAG(hi2s);
  }

  hi2s->State = HAL_I2S_STATE_READY;

  if (hi2s->ErrorCode == HAL_I2S_ERROR_NONE)
  {
    HAL_I2S_RxCpltCallback(hi2s);
  }
  else
  {
    HAL_I2S_ErrorCallback(hi2s);
  }
}

/**
  * @brief  Handle the end of the TX transaction.
  * @param  hi2s: pointer to a I2S_HandleTypeDef structure that contains
  *         the configuration information for I2S module
  * @retval None
  */
static void I2S_CloseTx_ISR(I2S_HandleTypeDef *hi2s)
{
  /* Disable TXE and ERR interrupt */
  __HAL_I2S_DISABLE_IT(hi2s, (I2S_IT_TXE | I2S_IT_ERR));

  /* Clear overrun flag in 2 Lines communication mode because received is not read */
  if (IS_I2S_FD_MODE(hi2s->Init.Mode))
  {
    __HAL_I2S_CLEAR_OVRFLAG(hi2s);
  }

  hi2s->State = HAL_I2S_STATE_READY;
  if (hi2s->ErrorCode != HAL_SPI_ERROR_NONE)
  {
    HAL_I2S_ErrorCallback(hi2s);
  }
  else
  {
    HAL_I2S_TxCpltCallback(hi2s);
  }
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

