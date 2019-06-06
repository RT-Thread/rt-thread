/**
  ******************************************************************************
  * @file    stm32f7xx_hal_hash_ex.c
  * @author  MCD Application Team
<<<<<<< HEAD
  * @brief   HASH HAL Extension module driver.
  *          This file provides firmware functions to manage the following 
  *          functionalities of HASH peripheral:
  *           + Extended HASH processing functions based on SHA224 Algorithm
  *           + Extended HASH processing functions based on SHA256 Algorithm
  *         
  @verbatim
  ==============================================================================
                     ##### How to use this driver #####
  ==============================================================================
    [..]
    The HASH HAL driver can be used as follows:
    (#)Initialize the HASH low level resources by implementing the HAL_HASH_MspInit():
        (##) Enable the HASH interface clock using __HAL_RCC_HASH_CLK_ENABLE()
        (##) In case of using processing APIs based on interrupts (e.g. HAL_HMACEx_SHA224_Start())
            (+++) Configure the HASH interrupt priority using HAL_NVIC_SetPriority()
            (+++) Enable the HASH IRQ handler using HAL_NVIC_EnableIRQ()
            (+++) In HASH IRQ handler, call HAL_HASH_IRQHandler()
        (##) In case of using DMA to control data transfer (e.g. HAL_HMACEx_SH224_Start_DMA())
            (+++) Enable the DMAx interface clock using __DMAx_CLK_ENABLE()
            (+++) Configure and enable one DMA stream one for managing data transfer from
                memory to peripheral (input stream). Managing data transfer from
                peripheral to memory can be performed only using CPU
            (+++) Associate the initialized DMA handle to the HASH DMA handle
                using  __HAL_LINKDMA()
            (+++) Configure the priority and enable the NVIC for the transfer complete
                interrupt on the DMA Stream: HAL_NVIC_SetPriority() and HAL_NVIC_EnableIRQ()
    (#)Initialize the HASH HAL using HAL_HASH_Init(). This function configures mainly:
        (##) The data type: 1-bit, 8-bit, 16-bit and 32-bit.
        (##) For HMAC, the encryption key.
        (##) For HMAC, the key size used for encryption.
    (#)Three processing functions are available:
        (##) Polling mode: processing APIs are blocking functions
             i.e. they process the data and wait till the digest computation is finished
             e.g. HAL_HASHEx_SHA224_Start()
        (##) Interrupt mode: encryption and decryption APIs are not blocking functions
                i.e. they process the data under interrupt
                e.g. HAL_HASHEx_SHA224_Start_IT()
        (##) DMA mode: processing APIs are not blocking functions and the CPU is
             not used for data transfer i.e. the data transfer is ensured by DMA
                e.g. HAL_HASHEx_SHA224_Start_DMA()
    (#)When the processing function is called at first time after HAL_HASH_Init()
       the HASH peripheral is initialized and processes the buffer in input.
       After that, the digest computation is started.
       When processing multi-buffer use the accumulate function to write the
       data in the peripheral without starting the digest computation. In last 
       buffer use the start function to input the last buffer ans start the digest
       computation.
       (##) e.g. HAL_HASHEx_SHA224_Accumulate() : write 1st data buffer in the peripheral without starting the digest computation
       (##)  write (n-1)th data buffer in the peripheral without starting the digest computation
       (##)  HAL_HASHEx_SHA224_Start() : write (n)th data buffer in the peripheral and start the digest computation
    (#)In HMAC mode, there is no Accumulate API. Only Start API is available.
    (#)In case of using DMA, call the DMA start processing e.g. HAL_HASHEx_SHA224_Start_DMA().
       After that, call the finish function in order to get the digest value
       e.g. HAL_HASHEx_SHA224_Finish()
    (#)Call HAL_HASH_DeInit() to deinitialize the HASH peripheral.
=======
  * @brief   Extended HASH HAL module driver.
  *          This file provides firmware functions to manage the following
  *          functionalities of the HASH peripheral for SHA-224 and SHA-256
  *          alogrithms:
  *           + HASH or HMAC processing in polling mode
  *           + HASH or HMAC processing in interrupt mode
  *           + HASH or HMAC processing in DMA mode
  *         Additionally, this file provides functions to manage HMAC
  *         multi-buffer DMA-based processing for MD-5, SHA-1, SHA-224
  *         and SHA-256.
  *
  *
  @verbatim
 ===============================================================================
                     ##### HASH peripheral extended features  #####
 ===============================================================================
    [..]
    The SHA-224 and SHA-256 HASH and HMAC processing can be carried out exactly
    the same way as for SHA-1 or MD-5 algorithms.
    (#) Three modes are available.
        (##) Polling mode: processing APIs are blocking functions
             i.e. they process the data and wait till the digest computation is finished,
             e.g. HAL_HASHEx_xxx_Start()
        (##) Interrupt mode: processing APIs are not blocking functions
                i.e. they process the data under interrupt,
                e.g. HAL_HASHEx_xxx_Start_IT()
        (##) DMA mode: processing APIs are not blocking functions and the CPU is
             not used for data transfer i.e. the data transfer is ensured by DMA,
                e.g. HAL_HASHEx_xxx_Start_DMA(). Note that in DMA mode, a call to
                HAL_HASHEx_xxx_Finish() is then required to retrieve the digest.

   (#)Multi-buffer processing is possible in polling and DMA mode.
        (##) In polling mode, only multi-buffer HASH processing is possible.
             API HAL_HASHEx_xxx_Accumulate() must be called for each input buffer, except for the last one.
             User must resort to HAL_HASHEx_xxx_Start() to enter the last one and retrieve as
             well the computed digest.

        (##) In DMA mode, multi-buffer HASH and HMAC processing are possible.

              (+++) HASH processing: once initialization is done, MDMAT bit must be set thru __HAL_HASH_SET_MDMAT() macro.
             From that point, each buffer can be fed to the IP thru HAL_HASHEx_xxx_Start_DMA() API.
             Before entering the last buffer, reset the MDMAT bit with __HAL_HASH_RESET_MDMAT()
             macro then wrap-up the HASH processing in feeding the last input buffer thru the
             same API HAL_HASHEx_xxx_Start_DMA(). The digest can then be retrieved with a call to
             API HAL_HASHEx_xxx_Finish().

             (+++) HMAC processing (MD-5, SHA-1, SHA-224 and SHA-256 must all resort to
             extended functions): after initialization, the key and the first input buffer are entered
             in the IP with the API HAL_HMACEx_xxx_Step1_2_DMA(). This carries out HMAC step 1 and
             starts step 2.
             The following buffers are next entered with the API  HAL_HMACEx_xxx_Step2_DMA(). At this
             point, the HMAC processing is still carrying out step 2.
             Then, step 2 for the last input buffer and step 3 are carried out by a single call
             to HAL_HMACEx_xxx_Step2_3_DMA().

             The digest can finally be retrieved with a call to API HAL_HASH_xxx_Finish() for
             MD-5 and SHA-1, to HAL_HASHEx_xxx_Finish() for SHA-224 and SHA-256.

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
  *
  ******************************************************************************
  */ 
=======
  * <h2><center>&copy; Copyright (c) 2017 STMicroelectronics.
  * All rights reserved.</center></h2>
  *
  * This software component is licensed by ST under BSD 3-Clause license,
  * the "License"; You may not use this file except in compliance with the
  * License. You may obtain a copy of the License at:
  *                        opensource.org/licenses/BSD-3-Clause
  *
  ******************************************************************************
  */
>>>>>>> 49e424905b5922b07aa7166ec7a0eeb90adf58a8

/* Includes ------------------------------------------------------------------*/
#include "stm32f7xx_hal.h"

<<<<<<< HEAD
/** @addtogroup STM32F7xx_HAL_Driver
  * @{
  */
#if defined(STM32F756xx) || defined(STM32F777xx) || defined(STM32F779xx) || defined (STM32F750xx)

/** @defgroup HASHEx HASHEx
  * @brief HASH Extension HAL module driver.
  * @{
  */

#ifdef HAL_HASH_MODULE_ENABLED

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
/** @addtogroup HASHEx_Private_Functions
  * @{
  */
static void HASHEx_DMAXferCplt(DMA_HandleTypeDef *hdma);
static void HASHEx_WriteData(uint8_t *pInBuffer, uint32_t Size);
static void HASHEx_GetDigest(uint8_t *pMsgDigest, uint8_t Size);
static void HASHEx_DMAError(DMA_HandleTypeDef *hdma);
/**
  * @}
  */
  
/* Private functions ---------------------------------------------------------*/

/** @addtogroup HASHEx_Private_Functions
  * @{
  */

/**
  * @brief  Writes the input buffer in data register.
  * @param  pInBuffer Pointer to input buffer
  * @param  Size The size of input buffer
  * @retval None
  */
static void HASHEx_WriteData(uint8_t *pInBuffer, uint32_t Size)
{
  uint32_t buffercounter;
  uint32_t inputaddr = (uint32_t) pInBuffer;
  
  for(buffercounter = 0; buffercounter < Size; buffercounter+=4)
  {
    HASH->DIN = *(uint32_t*)inputaddr;
    inputaddr+=4;
  }
}

/**
  * @brief  Provides the message digest result.
  * @param  pMsgDigest Pointer to the message digest
  * @param  Size The size of the message digest in bytes
  * @retval None
  */
static void HASHEx_GetDigest(uint8_t *pMsgDigest, uint8_t Size)
{
  uint32_t msgdigest = (uint32_t)pMsgDigest;
  
  switch(Size)
  {
  case 16:
    /* Read the message digest */
    *(uint32_t*)(msgdigest) = __REV(HASH->HR[0]);
    msgdigest+=4;
    *(uint32_t*)(msgdigest) = __REV(HASH->HR[1]);
    msgdigest+=4;
    *(uint32_t*)(msgdigest) = __REV(HASH->HR[2]);
    msgdigest+=4;
    *(uint32_t*)(msgdigest) = __REV(HASH->HR[3]);
    break;
  case 20:
    /* Read the message digest */
    *(uint32_t*)(msgdigest) = __REV(HASH->HR[0]);
    msgdigest+=4;
    *(uint32_t*)(msgdigest) = __REV(HASH->HR[1]);
    msgdigest+=4;
    *(uint32_t*)(msgdigest) = __REV(HASH->HR[2]);
    msgdigest+=4;
    *(uint32_t*)(msgdigest) = __REV(HASH->HR[3]);
    msgdigest+=4;
    *(uint32_t*)(msgdigest) = __REV(HASH->HR[4]);
    break;
  case 28:
    /* Read the message digest */
    *(uint32_t*)(msgdigest) = __REV(HASH->HR[0]);
    msgdigest+=4;
    *(uint32_t*)(msgdigest) = __REV(HASH->HR[1]);
    msgdigest+=4;
    *(uint32_t*)(msgdigest) = __REV(HASH->HR[2]);
    msgdigest+=4;
    *(uint32_t*)(msgdigest) = __REV(HASH->HR[3]);
    msgdigest+=4;
    *(uint32_t*)(msgdigest) = __REV(HASH->HR[4]);
    msgdigest+=4;
    *(uint32_t*)(msgdigest) = __REV(HASH_DIGEST->HR[5]);
    msgdigest+=4;
    *(uint32_t*)(msgdigest) = __REV(HASH_DIGEST->HR[6]);
    break;
  case 32:
    /* Read the message digest */
    *(uint32_t*)(msgdigest) = __REV(HASH->HR[0]);
    msgdigest+=4;
    *(uint32_t*)(msgdigest) = __REV(HASH->HR[1]);
    msgdigest+=4;
    *(uint32_t*)(msgdigest) = __REV(HASH->HR[2]);
    msgdigest+=4;
    *(uint32_t*)(msgdigest) = __REV(HASH->HR[3]);
    msgdigest+=4;
    *(uint32_t*)(msgdigest) = __REV(HASH->HR[4]);
    msgdigest+=4;
    *(uint32_t*)(msgdigest) = __REV(HASH_DIGEST->HR[5]);
    msgdigest+=4;
    *(uint32_t*)(msgdigest) = __REV(HASH_DIGEST->HR[6]);
    msgdigest+=4;
    *(uint32_t*)(msgdigest) = __REV(HASH_DIGEST->HR[7]);
    break;
  default:
    break;
  }
}

/**
  * @brief  DMA HASH Input Data complete callback. 
  * @param  hdma DMA handle
  * @retval None
  */
static void HASHEx_DMAXferCplt(DMA_HandleTypeDef *hdma)
{
  HASH_HandleTypeDef* hhash = ( HASH_HandleTypeDef* )((DMA_HandleTypeDef* )hdma)->Parent;
  uint32_t inputaddr = 0;
  uint32_t buffersize = 0;
  
  if((HASH->CR & HASH_CR_MODE) != HASH_CR_MODE)
  {
    /* Disable the DMA transfer */
    HASH->CR &= (uint32_t)(~HASH_CR_DMAE);
    
    /* Change HASH peripheral state */
    hhash->State = HAL_HASH_STATE_READY;
    
    /* Call Input data transfer complete callback */
    HAL_HASH_InCpltCallback(hhash);
  }
  else
  {
    /* Increment Interrupt counter */
    hhash->HashInCount++;
    /* Disable the DMA transfer before starting the next transfer */
    HASH->CR &= (uint32_t)(~HASH_CR_DMAE);
    
    if(hhash->HashInCount <= 2)
    {
      /* In case HashInCount = 1, set the DMA to transfer data to HASH DIN register */
      if(hhash->HashInCount == 1)
      {
        inputaddr = (uint32_t)hhash->pHashInBuffPtr;
        buffersize = hhash->HashBuffSize;
      }
      /* In case HashInCount = 2, set the DMA to transfer key to HASH DIN register */
      else if(hhash->HashInCount == 2)
      {
        inputaddr = (uint32_t)hhash->Init.pKey;
        buffersize = hhash->Init.KeySize;
      }
      /* Configure the number of valid bits in last word of the message */
      MODIFY_REG(HASH->STR, HASH_STR_NBLW, 8 * (buffersize % 4));
      
      /* Set the HASH DMA transfer complete */
      hhash->hdmain->XferCpltCallback = HASHEx_DMAXferCplt;
      
      /* Enable the DMA In DMA Stream */
      HAL_DMA_Start_IT(hhash->hdmain, inputaddr, (uint32_t)&HASH->DIN, (buffersize%4 ? (buffersize+3)/4:buffersize/4));
      
      /* Enable DMA requests */
      HASH->CR |= (HASH_CR_DMAE);
    }
    else
    {
      /* Disable the DMA transfer */
      HASH->CR &= (uint32_t)(~HASH_CR_DMAE);
      
      /* Reset the InCount */
      hhash->HashInCount = 0;
      
      /* Change HASH peripheral state */
      hhash->State = HAL_HASH_STATE_READY;
      
      /* Call Input data transfer complete callback */
      HAL_HASH_InCpltCallback(hhash);
    }
  }
}

/**
  * @brief  DMA HASH communication error callback. 
  * @param  hdma DMA handle
  * @retval None
  */
static void HASHEx_DMAError(DMA_HandleTypeDef *hdma)
{
  HASH_HandleTypeDef* hhash = ( HASH_HandleTypeDef* )((DMA_HandleTypeDef* )hdma)->Parent;
  hhash->State= HAL_HASH_STATE_READY;
  HAL_HASH_ErrorCallback(hhash);
}

 /**
  * @}
  */
  
/* Exported functions --------------------------------------------------------*/
/** @addtogroup HASHEx_Exported_Functions
  * @{
  */
  
/** @defgroup  HASHEx_Group1 HASH processing functions  
 *  @brief   processing functions using polling mode 
 *
@verbatim   
 ===============================================================================
              ##### HASH processing using polling mode functions #####
 ===============================================================================  
    [..]  This section provides functions allowing to calculate in polling mode
          the hash value using one of the following algorithms:
      (+) SHA224
      (+) SHA256
=======



/** @addtogroup STM32F7xx_HAL_Driver
  * @{
  */
#if defined (HASH)

/** @defgroup HASHEx HASHEx
  * @brief HASH HAL extended module driver.
  * @{
  */
#ifdef HAL_HASH_MODULE_ENABLED
/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private functions ---------------------------------------------------------*/


/** @defgroup HASHEx_Exported_Functions HASH Extended Exported Functions
  * @{
  */

/** @defgroup HASHEx_Exported_Functions_Group1 HASH extended processing functions in polling mode
 *  @brief   HASH extended processing functions using polling mode.
 *
@verbatim
 ===============================================================================
               ##### Polling mode HASH extended processing functions #####
 ===============================================================================
    [..]  This section provides functions allowing to calculate in polling mode
          the hash value using one of the following algorithms:
      (+) SHA224
         (++) HAL_HASHEx_SHA224_Start()
         (++) HAL_HASHEx_SHA224_Accumulate()
      (+) SHA256
         (++) HAL_HASHEx_SHA256_Start()
         (++) HAL_HASHEx_SHA256_Accumulate()

    [..] For a single buffer to be hashed, user can resort to HAL_HASH_xxx_Start().

    [..]  In case of multi-buffer HASH processing (a single digest is computed while
          several buffers are fed to the IP), the user can resort to successive calls
          to HAL_HASHEx_xxx_Accumulate() and wrap-up the digest computation by a call
          to HAL_HASHEx_xxx_Start().

@endverbatim
  * @{
  */


/**
  * @brief  Initialize the HASH peripheral in SHA224 mode, next process pInBuffer then
  *         read the computed digest.
  * @note   Digest is available in pOutBuffer.
  * @param  hhash: HASH handle.
  * @param  pInBuffer: pointer to the input buffer (buffer to be hashed).
  * @param  Size: length of the input buffer in bytes.
  * @param  pOutBuffer: pointer to the computed digest. Digest size is 28 bytes.
  * @param  Timeout: Timeout value
  * @retval HAL status
  */
HAL_StatusTypeDef HAL_HASHEx_SHA224_Start(HASH_HandleTypeDef *hhash, uint8_t *pInBuffer, uint32_t Size, uint8_t* pOutBuffer, uint32_t Timeout)
{
  return HASH_Start(hhash, pInBuffer, Size, pOutBuffer, Timeout, HASH_ALGOSELECTION_SHA224);
}

/**
  * @brief  If not already done, initialize the HASH peripheral in SHA224 mode then
  *         processes pInBuffer.
  * @note   Consecutive calls to HAL_HASHEx_SHA224_Accumulate() can be used to feed
  *         several input buffers back-to-back to the IP that will yield a single
  *         HASH signature once all buffers have been entered. Wrap-up of input
  *         buffers feeding and retrieval of digest is done by a call to
  *         HAL_HASHEx_SHA224_Start().
  * @note   Field hhash->Phase of HASH handle is tested to check whether or not
  *         the IP has already been initialized.
  * @note   Digest is not retrieved by this API, user must resort to HAL_HASHEx_SHA224_Start()
  *         to read it, feeding at the same time the last input buffer to the IP.
  * @note   The input buffer size (in bytes) must be a multiple of 4 otherwise, the
  *         HASH digest computation is corrupted. Only HAL_HASHEx_SHA224_Start() is able
  *         to manage the ending buffer with a length in bytes not a multiple of 4.
  * @param  hhash: HASH handle.
  * @param  pInBuffer: pointer to the input buffer (buffer to be hashed).
  * @param  Size: length of the input buffer in bytes, must be a multiple of 4.
  * @retval HAL status
  */
HAL_StatusTypeDef HAL_HASHEx_SHA224_Accumulate(HASH_HandleTypeDef *hhash, uint8_t *pInBuffer, uint32_t Size)
{
  return  HASH_Accumulate(hhash, pInBuffer, Size,HASH_ALGOSELECTION_SHA224);
}

/**
  * @brief  Initialize the HASH peripheral in SHA256 mode, next process pInBuffer then
  *         read the computed digest.
  * @note   Digest is available in pOutBuffer.
  * @param  hhash: HASH handle.
  * @param  pInBuffer: pointer to the input buffer (buffer to be hashed).
  * @param  Size: length of the input buffer in bytes.
  * @param  pOutBuffer: pointer to the computed digest. Digest size is 32 bytes.
  * @param  Timeout: Timeout value
  * @retval HAL status
  */
HAL_StatusTypeDef HAL_HASHEx_SHA256_Start(HASH_HandleTypeDef *hhash, uint8_t *pInBuffer, uint32_t Size, uint8_t* pOutBuffer, uint32_t Timeout)
{
  return HASH_Start(hhash, pInBuffer, Size, pOutBuffer, Timeout, HASH_ALGOSELECTION_SHA256);
}

/**
  * @brief  If not already done, initialize the HASH peripheral in SHA256 mode then
  *         processes pInBuffer.
  * @note   Consecutive calls to HAL_HASHEx_SHA256_Accumulate() can be used to feed
  *         several input buffers back-to-back to the IP that will yield a single
  *         HASH signature once all buffers have been entered. Wrap-up of input
  *         buffers feeding and retrieval of digest is done by a call to
  *         HAL_HASHEx_SHA256_Start().
  * @note   Field hhash->Phase of HASH handle is tested to check whether or not
  *         the IP has already been initialized.
  * @note   Digest is not retrieved by this API, user must resort to HAL_HASHEx_SHA256_Start()
  *         to read it, feeding at the same time the last input buffer to the IP.
  * @note   The input buffer size (in bytes) must be a multiple of 4 otherwise, the
  *         HASH digest computation is corrupted. Only HAL_HASHEx_SHA256_Start() is able
  *         to manage the ending buffer with a length in bytes not a multiple of 4.
  * @param  hhash: HASH handle.
  * @param  pInBuffer: pointer to the input buffer (buffer to be hashed).
  * @param  Size: length of the input buffer in bytes, must be a multiple of 4.
  * @retval HAL status
  */
HAL_StatusTypeDef HAL_HASHEx_SHA256_Accumulate(HASH_HandleTypeDef *hhash, uint8_t *pInBuffer, uint32_t Size)
{
  return  HASH_Accumulate(hhash, pInBuffer, Size,HASH_ALGOSELECTION_SHA256);
}


/**
  * @}
  */

/** @defgroup HASHEx_Exported_Functions_Group2 HASH extended processing functions in interrupt mode
 *  @brief   HASH extended processing functions using interrupt mode.
 *
@verbatim
 ===============================================================================
          ##### Interruption mode HASH extended processing functions #####
 ===============================================================================
    [..]  This section provides functions allowing to calculate in interrupt mode
          the hash value using one of the following algorithms:
      (+) SHA224
         (++) HAL_HASHEx_SHA224_Start_IT()
      (+) SHA256
         (++) HAL_HASHEx_SHA256_Start_IT()
>>>>>>> 49e424905b5922b07aa7166ec7a0eeb90adf58a8

@endverbatim
  * @{
  */

<<<<<<< HEAD
/**
  * @brief  Initializes the HASH peripheral in SHA224 mode
  *         then processes pInBuffer. The digest is available in pOutBuffer
  * @param  hhash pointer to a HASH_HandleTypeDef structure that contains
  *         the configuration information for HASH module
  * @param  pInBuffer Pointer to the input buffer (buffer to be hashed).
  * @param  Size Length of the input buffer in bytes.
  *          If the Size is not multiple of 64 bytes, the padding is managed by hardware.
  * @param  pOutBuffer Pointer to the computed digest. Its size must be 28 bytes.
  * @param  Timeout Specify Timeout value   
  * @retval HAL status
  */
HAL_StatusTypeDef HAL_HASHEx_SHA224_Start(HASH_HandleTypeDef *hhash, uint8_t *pInBuffer, uint32_t Size, uint8_t* pOutBuffer, uint32_t Timeout)
{
  uint32_t tickstart = 0;   
  
  /* Process Locked */
  __HAL_LOCK(hhash);
  
  /* Change the HASH state */
  hhash->State = HAL_HASH_STATE_BUSY;
  
  /* Check if initialization phase has already been performed */
  if(hhash->Phase == HAL_HASH_PHASE_READY)
  {
    /* Select the SHA224 mode and reset the HASH processor core, so that the HASH will be ready to compute 
       the message digest of a new message */
    HASH->CR |= HASH_ALGOSELECTION_SHA224 | HASH_CR_INIT;
  }
  
  /* Set the phase */
  hhash->Phase = HAL_HASH_PHASE_PROCESS;
  
  /* Configure the number of valid bits in last word of the message */
  __HAL_HASH_SET_NBVALIDBITS(Size);
  
  /* Write input buffer in data register */
  HASHEx_WriteData(pInBuffer, Size);
  
  /* Start the digest calculation */
  __HAL_HASH_START_DIGEST();
  
  /* Get tick */
  tickstart = HAL_GetTick();
  
  while((HASH->SR & HASH_FLAG_BUSY) == HASH_FLAG_BUSY)
  {
    /* Check for the Timeout */
    if(Timeout != HAL_MAX_DELAY)
    {
      if((Timeout == 0)||((HAL_GetTick() - tickstart ) > Timeout))
      {
        /* Change state */
        hhash->State = HAL_HASH_STATE_TIMEOUT;
        
        /* Process Unlocked */          
        __HAL_UNLOCK(hhash);
        
        return HAL_TIMEOUT;
      }
    }
  }
  
  /* Read the message digest */
  HASHEx_GetDigest(pOutBuffer, 28);
  
  /* Change the HASH state */
  hhash->State = HAL_HASH_STATE_READY;
  
  /* Process Unlocked */
  __HAL_UNLOCK(hhash);
  
  /* Return function status */
  return HAL_OK;
}

/**
  * @brief  Initializes the HASH peripheral in SHA256 mode then processes pInBuffer.
            The digest is available in pOutBuffer.
  * @param  hhash pointer to a HASH_HandleTypeDef structure that contains
  *         the configuration information for HASH module
  * @param  pInBuffer Pointer to the input buffer (buffer to be hashed). 
  * @param  Size Length of the input buffer in bytes.
  *          If the Size is not multiple of 64 bytes, the padding is managed by hardware.
  * @param  pOutBuffer Pointer to the computed digest. Its size must be 32 bytes.
  * @param  Timeout Specify Timeout value   
  * @retval HAL status
  */
HAL_StatusTypeDef HAL_HASHEx_SHA256_Start(HASH_HandleTypeDef *hhash, uint8_t *pInBuffer, uint32_t Size, uint8_t* pOutBuffer, uint32_t Timeout)
{
  uint32_t tickstart = 0;   
  
  /* Process Locked */
  __HAL_LOCK(hhash);
  
  /* Change the HASH state */
  hhash->State = HAL_HASH_STATE_BUSY;
  
  /* Check if initialization phase has already been performed */
  if(hhash->Phase == HAL_HASH_PHASE_READY)
  {
    /* Select the SHA256 mode and reset the HASH processor core, so that the HASH will be ready to compute 
       the message digest of a new message */
    HASH->CR |= HASH_ALGOSELECTION_SHA256 | HASH_CR_INIT;
  }
  
  /* Set the phase */
  hhash->Phase = HAL_HASH_PHASE_PROCESS;
  
  /* Configure the number of valid bits in last word of the message */
  __HAL_HASH_SET_NBVALIDBITS(Size);
  
  /* Write input buffer in data register */
  HASHEx_WriteData(pInBuffer, Size);
  
  /* Start the digest calculation */
  __HAL_HASH_START_DIGEST();
  
  /* Get tick */
  tickstart = HAL_GetTick();
  
  while((HASH->SR & HASH_FLAG_BUSY) == HASH_FLAG_BUSY)
  {
    /* Check for the Timeout */
    if(Timeout != HAL_MAX_DELAY)
    {
      if((Timeout == 0)||((HAL_GetTick() - tickstart ) > Timeout))
      {
        /* Change state */
        hhash->State = HAL_HASH_STATE_TIMEOUT;
        
        /* Process Unlocked */          
        __HAL_UNLOCK(hhash);
        
        return HAL_TIMEOUT;
      }
    }
  }
  
  /* Read the message digest */
  HASHEx_GetDigest(pOutBuffer, 32);
  
  /* Change the HASH state */
  hhash->State = HAL_HASH_STATE_READY;

  /* Process Unlocked */
  __HAL_UNLOCK(hhash);  
  
  /* Return function status */
  return HAL_OK;
}


/**
  * @brief  Initializes the HASH peripheral in SHA224 mode
  *         then processes pInBuffer. The digest is available in pOutBuffer
  * @param  hhash pointer to a HASH_HandleTypeDef structure that contains
  *         the configuration information for HASH module
  * @param  pInBuffer Pointer to the input buffer (buffer to be hashed).
  * @param  Size Length of the input buffer in bytes.
  *          If the Size is not multiple of 64 bytes, the padding is managed by hardware.
  * @retval HAL status
  */
HAL_StatusTypeDef HAL_HASHEx_SHA224_Accumulate(HASH_HandleTypeDef *hhash, uint8_t *pInBuffer, uint32_t Size)
{
  /* Process Locked */
  __HAL_LOCK(hhash);
  
  /* Change the HASH state */
  hhash->State = HAL_HASH_STATE_BUSY;
  
  /* Check if initialization phase has already been performed */
  if(hhash->Phase == HAL_HASH_PHASE_READY)
  {
    /* Select the SHA224 mode and reset the HASH processor core, so that the HASH will be ready to compute 
       the message digest of a new message */
    HASH->CR |= HASH_ALGOSELECTION_SHA224 | HASH_CR_INIT;
  }
  
  /* Set the phase */
  hhash->Phase = HAL_HASH_PHASE_PROCESS;
  
  /* Configure the number of valid bits in last word of the message */
  __HAL_HASH_SET_NBVALIDBITS(Size);
  
  /* Write input buffer in data register */
  HASHEx_WriteData(pInBuffer, Size);
  
  /* Change the HASH state */
  hhash->State = HAL_HASH_STATE_READY;
  
  /* Process Unlocked */
  __HAL_UNLOCK(hhash);
  
  /* Return function status */
  return HAL_OK;
}


/**
  * @brief  Initializes the HASH peripheral in SHA256 mode then processes pInBuffer.
            The digest is available in pOutBuffer.
  * @param  hhash pointer to a HASH_HandleTypeDef structure that contains
  *         the configuration information for HASH module
  * @param  pInBuffer Pointer to the input buffer (buffer to be hashed).
  * @param  Size Length of the input buffer in bytes.
  *          If the Size is not multiple of 64 bytes, the padding is managed by hardware.
  * @retval HAL status
  */
HAL_StatusTypeDef HAL_HASHEx_SHA256_Accumulate(HASH_HandleTypeDef *hhash, uint8_t *pInBuffer, uint32_t Size)
{
   /* Process Locked */
  __HAL_LOCK(hhash);
  
  /* Change the HASH state */
  hhash->State = HAL_HASH_STATE_BUSY;
  
  /* Check if initialization phase has already been performed */
  if(hhash->Phase == HAL_HASH_PHASE_READY)
  {
    /* Select the SHA256 mode and reset the HASH processor core, so that the HASH will be ready to compute 
       the message digest of a new message */
    HASH->CR |= HASH_ALGOSELECTION_SHA256 | HASH_CR_INIT;
  }
  
  /* Set the phase */
  hhash->Phase = HAL_HASH_PHASE_PROCESS;
  
  /* Configure the number of valid bits in last word of the message */
  __HAL_HASH_SET_NBVALIDBITS(Size);
  
  /* Write input buffer in data register */
  HASHEx_WriteData(pInBuffer, Size);
  
  /* Change the HASH state */
  hhash->State = HAL_HASH_STATE_READY;
  
  /* Process Unlocked */
  __HAL_UNLOCK(hhash);
  
  /* Return function status */
  return HAL_OK;
}

=======

/**
  * @brief  Initialize the HASH peripheral in SHA224 mode, next process pInBuffer then
  *         read the computed digest in interruption mode.
  * @note   Digest is available in pOutBuffer.
  * @param  hhash: HASH handle.
  * @param  pInBuffer: pointer to the input buffer (buffer to be hashed).
  * @param  Size: length of the input buffer in bytes.
  * @param  pOutBuffer: pointer to the computed digest. Digest size is 28 bytes.
  * @retval HAL status
  */
HAL_StatusTypeDef HAL_HASHEx_SHA224_Start_IT(HASH_HandleTypeDef *hhash, uint8_t *pInBuffer, uint32_t Size, uint8_t* pOutBuffer)
{
  return HASH_Start_IT(hhash, pInBuffer, Size, pOutBuffer,HASH_ALGOSELECTION_SHA224);
}

/**
  * @brief  Initialize the HASH peripheral in SHA256 mode, next process pInBuffer then
  *         read the computed digest in interruption mode.
  * @note   Digest is available in pOutBuffer.
  * @param  hhash: HASH handle.
  * @param  pInBuffer: pointer to the input buffer (buffer to be hashed).
  * @param  Size: length of the input buffer in bytes.
  * @param  pOutBuffer: pointer to the computed digest. Digest size is 32 bytes.
  * @retval HAL status
  */
HAL_StatusTypeDef HAL_HASHEx_SHA256_Start_IT(HASH_HandleTypeDef *hhash, uint8_t *pInBuffer, uint32_t Size, uint8_t* pOutBuffer)
{
  return HASH_Start_IT(hhash, pInBuffer, Size, pOutBuffer,HASH_ALGOSELECTION_SHA256);
}

/**
  * @}
  */

/** @defgroup HASHEx_Exported_Functions_Group3 HASH extended processing functions in DMA mode
 *  @brief   HASH extended processing functions using DMA mode.
 *
@verbatim
 ===============================================================================
                ##### DMA mode HASH extended  processing functionss #####
 ===============================================================================
    [..]  This section provides functions allowing to calculate in DMA mode
          the hash value using one of the following algorithms:
      (+) SHA224
         (++) HAL_HASHEx_SHA224_Start_DMA()
         (++) HAL_HASHEx_SHA224_Finish()
      (+) SHA256
         (++) HAL_HASHEx_SHA256_Start_DMA()
         (++) HAL_HASHEx_SHA256_Finish()

    [..]  When resorting to DMA mode to enter the data in the IP, user must resort
          to  HAL_HASHEx_xxx_Start_DMA() then read the resulting digest with
          HAL_HASHEx_xxx_Finish().

    [..]  In case of multi-buffer HASH processing, MDMAT bit must first be set before
          the successive calls to HAL_HASHEx_xxx_Start_DMA(). Then, MDMAT bit needs to be
          reset before the last call to HAL_HASHEx_xxx_Start_DMA(). Digest is finally
          retrieved thanks to HAL_HASHEx_xxx_Finish().

@endverbatim
  * @{
  */




/**
  * @brief  Initialize the HASH peripheral in SHA224 mode then initiate a DMA transfer
  *         to feed the input buffer to the IP.
  * @note   Once the DMA transfer is finished, HAL_HASHEx_SHA224_Finish() API must
  *         be called to retrieve the computed digest.
  * @param  hhash: HASH handle.
  * @param  pInBuffer: pointer to the input buffer (buffer to be hashed).
  * @param  Size: length of the input buffer in bytes.
  * @retval HAL status
  */
HAL_StatusTypeDef HAL_HASHEx_SHA224_Start_DMA(HASH_HandleTypeDef *hhash, uint8_t *pInBuffer, uint32_t Size)
{
  return HASH_Start_DMA(hhash, pInBuffer, Size, HASH_ALGOSELECTION_SHA224);
}

/**
  * @brief  Return the computed digest in SHA224 mode.
  * @note   The API waits for DCIS to be set then reads the computed digest.
  * @note   HAL_HASHEx_SHA224_Finish() can be used as well to retrieve the digest in
  *         HMAC SHA224 mode.
  * @param  hhash: HASH handle.
  * @param  pOutBuffer: pointer to the computed digest. Digest size is 28 bytes.
  * @param  Timeout: Timeout value.
  * @retval HAL status
  */
HAL_StatusTypeDef HAL_HASHEx_SHA224_Finish(HASH_HandleTypeDef *hhash, uint8_t* pOutBuffer, uint32_t Timeout)
{
   return HASH_Finish(hhash, pOutBuffer, Timeout);
}

/**
  * @brief  Initialize the HASH peripheral in SHA256 mode then initiate a DMA transfer
  *         to feed the input buffer to the IP.
  * @note   Once the DMA transfer is finished, HAL_HASHEx_SHA256_Finish() API must
  *         be called to retrieve the computed digest.
  * @param  hhash: HASH handle.
  * @param  pInBuffer: pointer to the input buffer (buffer to be hashed).
  * @param  Size: length of the input buffer in bytes.
  * @retval HAL status
  */
HAL_StatusTypeDef HAL_HASHEx_SHA256_Start_DMA(HASH_HandleTypeDef *hhash, uint8_t *pInBuffer, uint32_t Size)
{
  return HASH_Start_DMA(hhash, pInBuffer, Size, HASH_ALGOSELECTION_SHA256);
}

/**
  * @brief  Return the computed digest in SHA256 mode.
  * @note   The API waits for DCIS to be set then reads the computed digest.
  * @note   HAL_HASHEx_SHA256_Finish() can be used as well to retrieve the digest in
  *         HMAC SHA256 mode.
  * @param  hhash: HASH handle.
  * @param  pOutBuffer: pointer to the computed digest. Digest size is 32 bytes.
  * @param  Timeout: Timeout value.
  * @retval HAL status
  */
HAL_StatusTypeDef HAL_HASHEx_SHA256_Finish(HASH_HandleTypeDef *hhash, uint8_t* pOutBuffer, uint32_t Timeout)
{
   return HASH_Finish(hhash, pOutBuffer, Timeout);
}
>>>>>>> 49e424905b5922b07aa7166ec7a0eeb90adf58a8

/**
  * @}
  */

<<<<<<< HEAD
/** @defgroup HASHEx_Group2 HMAC processing functions using polling mode 
 *  @brief   HMAC processing functions using polling mode . 
 *
@verbatim   
 ===============================================================================
            ##### HMAC processing using polling mode functions #####
 ===============================================================================  
    [..]  This section provides functions allowing to calculate in polling mode
          the HMAC value using one of the following algorithms:
      (+) SHA224
      (+) SHA256
=======
/** @defgroup HASHEx_Exported_Functions_Group4 HMAC extended processing functions in polling mode
 *  @brief   HMAC extended processing functions using polling mode.
 *
@verbatim
 ===============================================================================
             ##### Polling mode HMAC extended processing functions #####
 ===============================================================================
    [..]  This section provides functions allowing to calculate in polling mode
          the HMAC value using one of the following algorithms:
      (+) SHA224
         (++) HAL_HMACEx_SHA224_Start()
      (+) SHA256
         (++) HAL_HMACEx_SHA256_Start()
>>>>>>> 49e424905b5922b07aa7166ec7a0eeb90adf58a8

@endverbatim
  * @{
  */

<<<<<<< HEAD
/**
  * @brief  Initializes the HASH peripheral in HMAC SHA224 mode
  *         then processes pInBuffer. The digest is available in pOutBuffer.
  * @param  hhash pointer to a HASH_HandleTypeDef structure that contains
  *         the configuration information for HASH module
  * @param  pInBuffer Pointer to the input buffer (buffer to be hashed). 
  * @param  Size Length of the input buffer in bytes.
  *          If the Size is not multiple of 64 bytes, the padding is managed by hardware.
  * @param  pOutBuffer Pointer to the computed digest. Its size must be 20 bytes.
  * @param  Timeout Timeout value 
=======


/**
  * @brief  Initialize the HASH peripheral in HMAC SHA224 mode, next process pInBuffer then
  *         read the computed digest.
  * @note   Digest is available in pOutBuffer.
  * @note   Same key is used for the inner and the outer hash functions; pointer to key and
  *         key size are respectively stored in hhash->Init.pKey and hhash->Init.KeySize.
  * @param  hhash: HASH handle.
  * @param  pInBuffer: pointer to the input buffer (buffer to be hashed).
  * @param  Size: length of the input buffer in bytes.
  * @param  pOutBuffer: pointer to the computed digest. Digest size is 28 bytes.
  * @param  Timeout: Timeout value.
>>>>>>> 49e424905b5922b07aa7166ec7a0eeb90adf58a8
  * @retval HAL status
  */
HAL_StatusTypeDef HAL_HMACEx_SHA224_Start(HASH_HandleTypeDef *hhash, uint8_t *pInBuffer, uint32_t Size, uint8_t* pOutBuffer, uint32_t Timeout)
{
<<<<<<< HEAD
  uint32_t tickstart = 0;   
                                                  
   /* Process Locked */
  __HAL_LOCK(hhash);
  
  /* Change the HASH state */
  hhash->State = HAL_HASH_STATE_BUSY;
  
  /* Check if initialization phase has already been performed */
  if(hhash->Phase == HAL_HASH_PHASE_READY)
  {
    /* Check if key size is greater than 64 bytes */
    if(hhash->Init.KeySize > 64)
    {
      /* Select the HMAC SHA224 mode */
      HASH->CR |= (HASH_ALGOSELECTION_SHA224 | HASH_ALGOMODE_HMAC | HASH_HMAC_KEYTYPE_LONGKEY | HASH_CR_INIT);
    }
    else
    {
      /* Select the HMAC SHA224 mode */
      HASH->CR |= (HASH_ALGOSELECTION_SHA224 | HASH_ALGOMODE_HMAC | HASH_CR_INIT);
    }
  }
  
  /* Set the phase */
  hhash->Phase = HAL_HASH_PHASE_PROCESS;
  
  /************************** STEP 1 ******************************************/
  /* Configure the number of valid bits in last word of the message */
  __HAL_HASH_SET_NBVALIDBITS(hhash->Init.KeySize);
  
  /* Write input buffer in data register */
  HASHEx_WriteData(hhash->Init.pKey, hhash->Init.KeySize);
  
  /* Start the digest calculation */
  __HAL_HASH_START_DIGEST();
  
  /* Get tick */
  tickstart = HAL_GetTick();
  
  while((HASH->SR & HASH_FLAG_BUSY) == HASH_FLAG_BUSY)
  {
    /* Check for the Timeout */
    if(Timeout != HAL_MAX_DELAY)
    {
      if((Timeout == 0)||((HAL_GetTick() - tickstart ) > Timeout))
      {
        /* Change state */
        hhash->State = HAL_HASH_STATE_TIMEOUT;
        
        /* Process Unlocked */          
        __HAL_UNLOCK(hhash);
        
        return HAL_TIMEOUT;
      }
    }
  }
  /************************** STEP 2 ******************************************/
  /* Configure the number of valid bits in last word of the message */
  __HAL_HASH_SET_NBVALIDBITS(Size);
  
  /* Write input buffer in data register */
  HASHEx_WriteData(pInBuffer, Size);
  
  /* Start the digest calculation */
  __HAL_HASH_START_DIGEST();
  
  /* Get tick */
  tickstart = HAL_GetTick();
  
  while((HASH->SR & HASH_FLAG_BUSY) == HASH_FLAG_BUSY)
  {
    /* Check for the Timeout */
    if(Timeout != HAL_MAX_DELAY)
    {
      if((HAL_GetTick() - tickstart ) > Timeout)
      {
        /* Change state */
        hhash->State = HAL_HASH_STATE_TIMEOUT;
        
        /* Process Unlocked */          
        __HAL_UNLOCK(hhash);
        
        return HAL_TIMEOUT;
      }
    }
  }
  /************************** STEP 3 ******************************************/
  /* Configure the number of valid bits in last word of the message */
  __HAL_HASH_SET_NBVALIDBITS(hhash->Init.KeySize);
  
  /* Write input buffer in data register */
  HASHEx_WriteData(hhash->Init.pKey, hhash->Init.KeySize);
  
  /* Start the digest calculation */
  __HAL_HASH_START_DIGEST();
  
  /* Get tick */
  tickstart = HAL_GetTick();
  
  while((HASH->SR & HASH_FLAG_BUSY) == HASH_FLAG_BUSY)
  {
    /* Check for the Timeout */
    if(Timeout != HAL_MAX_DELAY)
    {
      if((HAL_GetTick() - tickstart ) > Timeout)
      {
        /* Change state */
        hhash->State = HAL_HASH_STATE_TIMEOUT;
        
        /* Process Unlocked */          
        __HAL_UNLOCK(hhash);
        
        return HAL_TIMEOUT;
      }
    }
  }
  /* Read the message digest */
  HASHEx_GetDigest(pOutBuffer, 28);
  
  /* Change the HASH state */
  hhash->State = HAL_HASH_STATE_READY;
  
  /* Process Unlocked */
  __HAL_UNLOCK(hhash);
  
  /* Return function status */
  return HAL_OK;
}

/**
  * @brief  Initializes the HASH peripheral in HMAC SHA256 mode
  *         then processes pInBuffer. The digest is available in pOutBuffer
  * @param  hhash pointer to a HASH_HandleTypeDef structure that contains
  *         the configuration information for HASH module
  * @param  pInBuffer Pointer to the input buffer (buffer to be hashed). 
  * @param  Size Length of the input buffer in bytes.
  *          If the Size is not multiple of 64 bytes, the padding is managed by hardware.
  * @param  pOutBuffer Pointer to the computed digest. Its size must be 20 bytes.
  * @param  Timeout Timeout value 
=======
  return HMAC_Start(hhash, pInBuffer, Size, pOutBuffer, Timeout, HASH_ALGOSELECTION_SHA224);
}

/**
  * @brief  Initialize the HASH peripheral in HMAC SHA256 mode, next process pInBuffer then
  *         read the computed digest.
  * @note   Digest is available in pOutBuffer.
  * @note   Same key is used for the inner and the outer hash functions; pointer to key and
  *         key size are respectively stored in hhash->Init.pKey and hhash->Init.KeySize.
  * @param  hhash: HASH handle.
  * @param  pInBuffer: pointer to the input buffer (buffer to be hashed).
  * @param  Size: length of the input buffer in bytes.
  * @param  pOutBuffer: pointer to the computed digest. Digest size is 32 bytes.
  * @param  Timeout: Timeout value.
>>>>>>> 49e424905b5922b07aa7166ec7a0eeb90adf58a8
  * @retval HAL status
  */
HAL_StatusTypeDef HAL_HMACEx_SHA256_Start(HASH_HandleTypeDef *hhash, uint8_t *pInBuffer, uint32_t Size, uint8_t* pOutBuffer, uint32_t Timeout)
{
<<<<<<< HEAD
  uint32_t tickstart = 0;   
  
  /* Process Locked */
  __HAL_LOCK(hhash);
  
  /* Change the HASH state */
  hhash->State = HAL_HASH_STATE_BUSY;
  
  /* Check if initialization phase has already been performed */
  if(hhash->Phase == HAL_HASH_PHASE_READY)
  {
    /* Check if key size is greater than 64 bytes */
    if(hhash->Init.KeySize > 64)
    {
      /* Select the HMAC SHA256 mode */
      HASH->CR |= (HASH_ALGOSELECTION_SHA256 | HASH_ALGOMODE_HMAC | HASH_HMAC_KEYTYPE_LONGKEY);
    }
    else
    {
      /* Select the HMAC SHA256 mode */
      HASH->CR |= (HASH_ALGOSELECTION_SHA256 | HASH_ALGOMODE_HMAC);
    }
    /* Reset the HASH processor core, so that the HASH will be ready to compute 
       the message digest of a new message */
    HASH->CR |= HASH_CR_INIT;
  }
  
  /* Set the phase */
  hhash->Phase = HAL_HASH_PHASE_PROCESS;
  
  /************************** STEP 1 ******************************************/
  /* Configure the number of valid bits in last word of the message */
  __HAL_HASH_SET_NBVALIDBITS(hhash->Init.KeySize);
  
  /* Write input buffer in data register */
  HASHEx_WriteData(hhash->Init.pKey, hhash->Init.KeySize);
  
  /* Start the digest calculation */
  __HAL_HASH_START_DIGEST();
  
  /* Get tick */
  tickstart = HAL_GetTick();
  
  while((HASH->SR & HASH_FLAG_BUSY) == HASH_FLAG_BUSY)
  {
    /* Check for the Timeout */
    if(Timeout != HAL_MAX_DELAY)
    {
      if((Timeout == 0)||((HAL_GetTick() - tickstart ) > Timeout))
      {
        /* Change state */
        hhash->State = HAL_HASH_STATE_TIMEOUT;
        
        /* Process Unlocked */          
        __HAL_UNLOCK(hhash);
        
        return HAL_TIMEOUT;
      }
    }
  }
  /************************** STEP 2 ******************************************/
  /* Configure the number of valid bits in last word of the message */
  __HAL_HASH_SET_NBVALIDBITS(Size);
  
  /* Write input buffer in data register */
  HASHEx_WriteData(pInBuffer, Size);
  
  /* Start the digest calculation */
  __HAL_HASH_START_DIGEST();
  
  /* Get tick */
  tickstart = HAL_GetTick();
  
  while((HASH->SR & HASH_FLAG_BUSY) == HASH_FLAG_BUSY)
  {
    /* Check for the Timeout */
    if(Timeout != HAL_MAX_DELAY)
    {
      if((HAL_GetTick() - tickstart ) > Timeout)
      {
        /* Change state */
        hhash->State = HAL_HASH_STATE_TIMEOUT;
        
        /* Process Unlocked */          
        __HAL_UNLOCK(hhash);
        
        return HAL_TIMEOUT;
      }
    }
  }
  /************************** STEP 3 ******************************************/
  /* Configure the number of valid bits in last word of the message */
  __HAL_HASH_SET_NBVALIDBITS(hhash->Init.KeySize);
  
  /* Write input buffer in data register */
  HASHEx_WriteData(hhash->Init.pKey, hhash->Init.KeySize);
  
  /* Start the digest calculation */
  __HAL_HASH_START_DIGEST();
  
  /* Get tick */
  tickstart = HAL_GetTick();
  
  while((HASH->SR & HASH_FLAG_BUSY) == HASH_FLAG_BUSY)
  {
    /* Check for the Timeout */
    if(Timeout != HAL_MAX_DELAY)
    {
      if((HAL_GetTick() - tickstart ) > Timeout)
      {
        /* Change state */
        hhash->State = HAL_HASH_STATE_TIMEOUT;
        
        /* Process Unlocked */          
        __HAL_UNLOCK(hhash);
        
        return HAL_TIMEOUT;
      }
    }
  }
  /* Read the message digest */
  HASHEx_GetDigest(pOutBuffer, 32);
  
  /* Change the HASH state */
  hhash->State = HAL_HASH_STATE_READY;
  
   /* Process Unlocked */
  __HAL_UNLOCK(hhash);
  
  /* Return function status */
  return HAL_OK;
=======
  return HMAC_Start(hhash, pInBuffer, Size, pOutBuffer, Timeout, HASH_ALGOSELECTION_SHA256);
>>>>>>> 49e424905b5922b07aa7166ec7a0eeb90adf58a8
}

/**
  * @}
  */

<<<<<<< HEAD
/** @defgroup HASHEx_Group3 HASH processing functions using interrupt mode
 *  @brief   processing functions using interrupt mode. 
 *
@verbatim   
 ===============================================================================
              ##### HASH processing using interrupt functions #####
 ===============================================================================  
    [..]  This section provides functions allowing to calculate in interrupt mode
          the hash value using one of the following algorithms:
      (+) SHA224
      (+) SHA256
=======

/** @defgroup HASHEx_Exported_Functions_Group5 HMAC extended processing functions in interrupt mode
 *  @brief   HMAC extended processing functions using interruption mode.
 *
@verbatim
 ===============================================================================
             ##### Interrupt mode HMAC extended processing functions #####
 ===============================================================================
    [..]  This section provides functions allowing to calculate in interrupt mode
          the HMAC value using one of the following algorithms:
      (+) SHA224
         (++) HAL_HMACEx_SHA224_Start_IT()
      (+) SHA256
         (++) HAL_HMACEx_SHA256_Start_IT()
>>>>>>> 49e424905b5922b07aa7166ec7a0eeb90adf58a8

@endverbatim
  * @{
  */

<<<<<<< HEAD
/**
  * @brief  Initializes the HASH peripheral in SHA224 mode then processes pInBuffer.
  *         The digest is available in pOutBuffer.
  * @param  hhash pointer to a HASH_HandleTypeDef structure that contains
  *         the configuration information for HASH module
  * @param  pInBuffer Pointer to the input buffer (buffer to be hashed).
  * @param  Size Length of the input buffer in bytes.
  *          If the Size is not multiple of 64 bytes, the padding is managed by hardware.
  * @param  pOutBuffer Pointer to the computed digest. Its size must be 20 bytes.
  * @retval HAL status
  */
HAL_StatusTypeDef HAL_HASHEx_SHA224_Start_IT(HASH_HandleTypeDef *hhash, uint8_t *pInBuffer, uint32_t Size, uint8_t* pOutBuffer)
{
  uint32_t inputaddr;
  uint32_t buffercounter;
  uint32_t inputcounter;
  
  /* Process Locked */
  __HAL_LOCK(hhash);

  if(hhash->State == HAL_HASH_STATE_READY)
  {
    /* Change the HASH state */
    hhash->State = HAL_HASH_STATE_BUSY;
    
    hhash->HashInCount = Size;
    hhash->pHashInBuffPtr = pInBuffer;
    hhash->pHashOutBuffPtr = pOutBuffer;
    
    /* Check if initialization phase has already been performed */
    if(hhash->Phase == HAL_HASH_PHASE_READY)
    {
      /* Select the SHA224 mode */
      HASH->CR |= HASH_ALGOSELECTION_SHA224;
      /* Reset the HASH processor core, so that the HASH will be ready to compute 
         the message digest of a new message */
      HASH->CR |= HASH_CR_INIT;
    }
    /* Reset interrupt counter */
    hhash->HashITCounter = 0;
    /* Set the phase */
    hhash->Phase = HAL_HASH_PHASE_PROCESS;
    
    /* Process Unlocked */
    __HAL_UNLOCK(hhash);
    
    /* Enable Interrupts */
    HASH->IMR = (HASH_IT_DINI | HASH_IT_DCI);
    
    /* Return function status */
    return HAL_OK;
  }
  if(__HAL_HASH_GET_FLAG(HASH_FLAG_DCIS))
  {
    /* Read the message digest */
    HASHEx_GetDigest(hhash->pHashOutBuffPtr, 28);
    if(hhash->HashInCount == 0)
    {
      /* Disable Interrupts */
      HASH->IMR = 0;
      /* Change the HASH state */
      hhash->State = HAL_HASH_STATE_READY;
      /* Call digest computation complete callback */
      HAL_HASH_DgstCpltCallback(hhash);
      /* Process Unlocked */
      __HAL_UNLOCK(hhash);
      
      /* Return function status */
      return HAL_OK;
    }
  }
  if(__HAL_HASH_GET_FLAG(HASH_FLAG_DINIS))
  {
    if(hhash->HashInCount >= 68)
    {
      inputaddr = (uint32_t)hhash->pHashInBuffPtr;
      /* Write the Input block in the Data IN register */
      for(buffercounter = 0; buffercounter < 64; buffercounter+=4)
      {
        HASH->DIN = *(uint32_t*)inputaddr;
        inputaddr+=4;
      }
      if(hhash->HashITCounter == 0)
      {
        HASH->DIN = *(uint32_t*)inputaddr;
        if(hhash->HashInCount >= 68)
        {
          /* Decrement buffer counter */
          hhash->HashInCount -= 68;
          hhash->pHashInBuffPtr+= 68;
        }
        else
        {
           hhash->HashInCount = 0;
          hhash->pHashInBuffPtr+= hhash->HashInCount;
        }
        /* Set Interrupt counter */
        hhash->HashITCounter = 1;
      }
      else
      {
        /* Decrement buffer counter */
        hhash->HashInCount -= 64;
        hhash->pHashInBuffPtr+= 64;
      }
    }
    else
    {
      /* Get the buffer address */
      inputaddr = (uint32_t)hhash->pHashInBuffPtr;
      /* Get the buffer counter */
      inputcounter = hhash->HashInCount;
      /* Disable Interrupts */
      HASH->IMR &= ~(HASH_IT_DINI);
      /* Configure the number of valid bits in last word of the message */
      __HAL_HASH_SET_NBVALIDBITS(inputcounter);
      
      if((inputcounter > 4) && (inputcounter%4))
      {
        inputcounter = (inputcounter+4-inputcounter%4);
      }
      else if ((inputcounter < 4) && (inputcounter != 0))
      {
        inputcounter = 4;
      }
      /* Write the Input block in the Data IN register */
      for(buffercounter = 0; buffercounter < inputcounter/4; buffercounter++)
      {
        HASH->DIN = *(uint32_t*)inputaddr;
        inputaddr+=4;
      }
      /* Start the digest calculation */
      __HAL_HASH_START_DIGEST();
      /* Reset buffer counter */
      hhash->HashInCount = 0;
      /* Call Input data transfer complete callback */
      HAL_HASH_InCpltCallback(hhash);
    }
  }
  
  /* Process Unlocked */
  __HAL_UNLOCK(hhash);
  
  /* Return function status */
  return HAL_OK;
}


/**
  * @brief  Initializes the HASH peripheral in SHA256 mode then processes pInBuffer.
  *         The digest is available in pOutBuffer.
  * @param  hhash pointer to a HASH_HandleTypeDef structure that contains
  *         the configuration information for HASH module
  * @param  pInBuffer Pointer to the input buffer (buffer to be hashed).
  * @param  Size Length of the input buffer in bytes.
  *          If the Size is not multiple of 64 bytes, the padding is managed by hardware.
  * @param  pOutBuffer Pointer to the computed digest. Its size must be 20 bytes.
  * @retval HAL status
  */
HAL_StatusTypeDef HAL_HASHEx_SHA256_Start_IT(HASH_HandleTypeDef *hhash, uint8_t *pInBuffer, uint32_t Size, uint8_t* pOutBuffer)
{
  uint32_t inputaddr;
  uint32_t buffercounter;
  uint32_t inputcounter;
  
  /* Process Locked */
  __HAL_LOCK(hhash);

  if(hhash->State == HAL_HASH_STATE_READY)
  {
    /* Change the HASH state */
    hhash->State = HAL_HASH_STATE_BUSY;
    
    hhash->HashInCount = Size;
    hhash->pHashInBuffPtr = pInBuffer;
    hhash->pHashOutBuffPtr = pOutBuffer;
    
    /* Check if initialization phase has already been performed */
    if(hhash->Phase == HAL_HASH_PHASE_READY)
    {
      /* Select the SHA256 mode */
      HASH->CR |= HASH_ALGOSELECTION_SHA256;
      /* Reset the HASH processor core, so that the HASH will be ready to compute 
         the message digest of a new message */
      HASH->CR |= HASH_CR_INIT;
    }
    
    /* Reset interrupt counter */
    hhash->HashITCounter = 0;
    
    /* Set the phase */
    hhash->Phase = HAL_HASH_PHASE_PROCESS;
    
    /* Process Unlocked */
    __HAL_UNLOCK(hhash);
    
    /* Enable Interrupts */
    HASH->IMR = (HASH_IT_DINI | HASH_IT_DCI);
    
    /* Return function status */
    return HAL_OK;
  }
  if(__HAL_HASH_GET_FLAG(HASH_FLAG_DCIS))
  {
    /* Read the message digest */
    HASHEx_GetDigest(hhash->pHashOutBuffPtr, 32);
    if(hhash->HashInCount == 0)
    {
      /* Disable Interrupts */
      HASH->IMR = 0;
      /* Change the HASH state */
      hhash->State = HAL_HASH_STATE_READY;
      /* Call digest computation complete callback */
      HAL_HASH_DgstCpltCallback(hhash);
      
      /* Process Unlocked */
      __HAL_UNLOCK(hhash);
      
      /* Return function status */
      return HAL_OK;
    }
  }
  if(__HAL_HASH_GET_FLAG(HASH_FLAG_DINIS))
  {
    if(hhash->HashInCount >= 68)
    {
      inputaddr = (uint32_t)hhash->pHashInBuffPtr;
      /* Write the Input block in the Data IN register */
      for(buffercounter = 0; buffercounter < 64; buffercounter+=4)
      {
        HASH->DIN = *(uint32_t*)inputaddr;
        inputaddr+=4;
      }
      if(hhash->HashITCounter == 0)
      {
        HASH->DIN = *(uint32_t*)inputaddr;
        
        if(hhash->HashInCount >= 68)
        {
          /* Decrement buffer counter */
          hhash->HashInCount -= 68;
          hhash->pHashInBuffPtr+= 68;
        }
        else
        {
          hhash->HashInCount = 0;
          hhash->pHashInBuffPtr+= hhash->HashInCount;
        }
        /* Set Interrupt counter */
        hhash->HashITCounter = 1;
      }
      else
      {
        /* Decrement buffer counter */
        hhash->HashInCount -= 64;
        hhash->pHashInBuffPtr+= 64;
      }
    }
    else
    {
      /* Get the buffer address */
      inputaddr = (uint32_t)hhash->pHashInBuffPtr;
      /* Get the buffer counter */
      inputcounter = hhash->HashInCount;
      /* Disable Interrupts */
      HASH->IMR &= ~(HASH_IT_DINI);
      /* Configure the number of valid bits in last word of the message */
      __HAL_HASH_SET_NBVALIDBITS(inputcounter);
      
      if((inputcounter > 4) && (inputcounter%4))
      {
        inputcounter = (inputcounter+4-inputcounter%4);
      }
      else if ((inputcounter < 4) && (inputcounter != 0))
      {
        inputcounter = 4;
      }
      
      /* Write the Input block in the Data IN register */
      for(buffercounter = 0; buffercounter < inputcounter/4; buffercounter++)
      {
        HASH->DIN = *(uint32_t*)inputaddr;
        inputaddr+=4;
      }
      /* Start the digest calculation */
      __HAL_HASH_START_DIGEST();
      /* Reset buffer counter */
      hhash->HashInCount = 0;
      /* Call Input data transfer complete callback */
      HAL_HASH_InCpltCallback(hhash);
    }
  }
  
  /* Process Unlocked */
  __HAL_UNLOCK(hhash);
  
  /* Return function status */
  return HAL_OK;
}

/**
  * @brief This function handles HASH interrupt request.
  * @param  hhash pointer to a HASH_HandleTypeDef structure that contains
  *         the configuration information for HASH module
  * @retval None
  */
void HAL_HASHEx_IRQHandler(HASH_HandleTypeDef *hhash)
{
  switch(HASH->CR & HASH_CR_ALGO)
  {
    
    case HASH_ALGOSELECTION_SHA224:
       HAL_HASHEx_SHA224_Start_IT(hhash, NULL, 0, NULL);
    break;
    
    case HASH_ALGOSELECTION_SHA256:
      HAL_HASHEx_SHA256_Start_IT(hhash, NULL, 0, NULL);
    break;
    
    default:
    break;
  }
}

=======


/**
  * @brief  Initialize the HASH peripheral in HMAC SHA224 mode, next process pInBuffer then
  *         read the computed digest in interrupt mode.
  * @note   Digest is available in pOutBuffer.
  * @note   Same key is used for the inner and the outer hash functions; pointer to key and
  *         key size are respectively stored in hhash->Init.pKey and hhash->Init.KeySize.
  * @param  hhash: HASH handle.
  * @param  pInBuffer: pointer to the input buffer (buffer to be hashed).
  * @param  Size: length of the input buffer in bytes.
  * @param  pOutBuffer: pointer to the computed digest. Digest size is 28 bytes.
  * @retval HAL status
  */
HAL_StatusTypeDef HAL_HMACEx_SHA224_Start_IT(HASH_HandleTypeDef *hhash, uint8_t *pInBuffer, uint32_t Size, uint8_t* pOutBuffer)
{
  return  HMAC_Start_IT(hhash, pInBuffer, Size, pOutBuffer, HASH_ALGOSELECTION_SHA224);
}

/**
  * @brief  Initialize the HASH peripheral in HMAC SHA256 mode, next process pInBuffer then
  *         read the computed digest in interrupt mode.
  * @note   Digest is available in pOutBuffer.
  * @note   Same key is used for the inner and the outer hash functions; pointer to key and
  *         key size are respectively stored in hhash->Init.pKey and hhash->Init.KeySize.
  * @param  hhash: HASH handle.
  * @param  pInBuffer: pointer to the input buffer (buffer to be hashed).
  * @param  Size: length of the input buffer in bytes.
  * @param  pOutBuffer: pointer to the computed digest. Digest size is 32 bytes.
  * @retval HAL status
  */
HAL_StatusTypeDef HAL_HMACEx_SHA256_Start_IT(HASH_HandleTypeDef *hhash, uint8_t *pInBuffer, uint32_t Size, uint8_t* pOutBuffer)
{
  return  HMAC_Start_IT(hhash, pInBuffer, Size, pOutBuffer, HASH_ALGOSELECTION_SHA256);
}




/**
  * @}
  */


/** @defgroup HASHEx_Exported_Functions_Group6 HMAC extended processing functions in DMA mode
 *  @brief   HMAC extended processing functions using DMA mode.
 *
@verbatim
 ===============================================================================
              ##### DMA mode HMAC extended processing functions #####
 ===============================================================================
    [..]  This section provides functions allowing to calculate in DMA mode
          the HMAC value using one of the following algorithms:
      (+) SHA224
         (++) HAL_HMACEx_SHA224_Start_DMA()
      (+) SHA256
         (++) HAL_HMACEx_SHA256_Start_DMA()

    [..]  When resorting to DMA mode to enter the data in the IP for HMAC processing,
          user must resort to  HAL_HMACEx_xxx_Start_DMA() then read the resulting digest
          with HAL_HASHEx_xxx_Finish().


@endverbatim
  * @{
  */



/**
  * @brief  Initialize the HASH peripheral in HMAC SHA224 mode then initiate the required
  *         DMA transfers to feed the key and the input buffer to the IP.
  * @note   Once the DMA transfers are finished (indicated by hhash->State set back
  *         to HAL_HASH_STATE_READY), HAL_HASHEx_SHA224_Finish() API must be called to retrieve
  *         the computed digest.
  * @note   Same key is used for the inner and the outer hash functions; pointer to key and
  *         key size are respectively stored in hhash->Init.pKey and hhash->Init.KeySize.
  * @note   If MDMAT bit is set before calling this function (multi-buffer
  *          HASH processing case), the input buffer size (in bytes) must be
  *          a multiple of 4 otherwise, the HASH digest computation is corrupted.
  *          For the processing of the last buffer of the thread, MDMAT bit must
  *          be reset and the buffer length (in bytes) doesn't have to be a
  *          multiple of 4.
  * @param  hhash: HASH handle.
  * @param  pInBuffer: pointer to the input buffer (buffer to be hashed).
  * @param  Size: length of the input buffer in bytes.
  * @retval HAL status
  */
HAL_StatusTypeDef HAL_HMACEx_SHA224_Start_DMA(HASH_HandleTypeDef *hhash, uint8_t *pInBuffer, uint32_t Size)
{
  return  HMAC_Start_DMA(hhash, pInBuffer, Size, HASH_ALGOSELECTION_SHA224);
}

/**
  * @brief  Initialize the HASH peripheral in HMAC SHA224 mode then initiate the required
  *         DMA transfers to feed the key and the input buffer to the IP.
  * @note   Once the DMA transfers are finished (indicated by hhash->State set back
  *         to HAL_HASH_STATE_READY), HAL_HASHEx_SHA256_Finish() API must be called to retrieve
  *         the computed digest.
  * @note   Same key is used for the inner and the outer hash functions; pointer to key and
  *         key size are respectively stored in hhash->Init.pKey and hhash->Init.KeySize.
  * @note   If MDMAT bit is set before calling this function (multi-buffer
  *          HASH processing case), the input buffer size (in bytes) must be
  *          a multiple of 4 otherwise, the HASH digest computation is corrupted.
  *          For the processing of the last buffer of the thread, MDMAT bit must
  *          be reset and the buffer length (in bytes) doesn't have to be a
  *          multiple of 4.
  * @param  hhash: HASH handle.
  * @param  pInBuffer: pointer to the input buffer (buffer to be hashed).
  * @param  Size: length of the input buffer in bytes.
  * @retval HAL status
  */
HAL_StatusTypeDef HAL_HMACEx_SHA256_Start_DMA(HASH_HandleTypeDef *hhash, uint8_t *pInBuffer, uint32_t Size)
{
  return  HMAC_Start_DMA(hhash, pInBuffer, Size, HASH_ALGOSELECTION_SHA256);
}


>>>>>>> 49e424905b5922b07aa7166ec7a0eeb90adf58a8
/**
  * @}
  */

<<<<<<< HEAD
/** @defgroup HASHEx_Group4 HASH processing functions using DMA mode
 *  @brief   processing functions using DMA mode. 
 *
@verbatim   
 ===============================================================================
                ##### HASH processing using DMA functions #####
 ===============================================================================  
    [..]  This section provides functions allowing to calculate in DMA mode
          the hash value using one of the following algorithms:
      (+) SHA224
      (+) SHA256
=======
/** @defgroup HASHEx_Exported_Functions_Group7 Multi-buffer HMAC extended processing functions in DMA mode
 *  @brief   HMAC extended processing functions in multi-buffer DMA mode.
 *
@verbatim
 ===============================================================================
      ##### Multi-buffer DMA mode HMAC extended processing functions #####
 ===============================================================================
    [..]  This section provides functions to manage HMAC multi-buffer
          DMA-based processing for MD5, SHA1, SHA224 and SHA256 algorithms.
      (+) MD5
         (++) HAL_HMACEx_MD5_Step1_2_DMA()
         (++) HAL_HMACEx_MD5_Step2_DMA()
         (++) HAL_HMACEx_MD5_Step2_3_DMA()
      (+) SHA1
         (++) HAL_HMACEx_SHA1_Step1_2_DMA()
         (++) HAL_HMACEx_SHA1_Step2_DMA()
         (++) HAL_HMACEx_SHA1_Step2_3_DMA()

      (+) SHA256
         (++) HAL_HMACEx_SHA224_Step1_2_DMA()
         (++) HAL_HMACEx_SHA224_Step2_DMA()
         (++) HAL_HMACEx_SHA224_Step2_3_DMA()
      (+) SHA256
         (++) HAL_HMACEx_SHA256_Step1_2_DMA()
         (++) HAL_HMACEx_SHA256_Step2_DMA()
         (++) HAL_HMACEx_SHA256_Step2_3_DMA()

    [..]  User must first start-up the multi-buffer DMA-based HMAC computation in
          calling HAL_HMACEx_xxx_Step1_2_DMA(). This carries out HMAC step 1 and
          intiates step 2 with the first input buffer.

    [..]  The following buffers are next fed to the IP with a call to the API
          HAL_HMACEx_xxx_Step2_DMA(). There may be several consecutive calls
          to this API.

    [..]  Multi-buffer DMA-based HMAC computation is wrapped up by a call to
          HAL_HMACEx_xxx_Step2_3_DMA(). This finishes step 2 in feeding the last input
          buffer to the IP then carries out step 3.

    [..]  Digest is retrieved by a call to HAL_HASH_xxx_Finish() for MD-5 or
          SHA-1, to HAL_HASHEx_xxx_Finish() for SHA-224 or SHA-256.

    [..]  If only two buffers need to be consecutively processed, a call to
          HAL_HMACEx_xxx_Step1_2_DMA() followed by a call to HAL_HMACEx_xxx_Step2_3_DMA()
          is sufficient.
>>>>>>> 49e424905b5922b07aa7166ec7a0eeb90adf58a8

@endverbatim
  * @{
  */

<<<<<<< HEAD

/**
  * @brief  Initializes the HASH peripheral in SHA224 mode then enables DMA to
            control data transfer. Use HAL_HASH_SHA224_Finish() to get the digest.
  * @param  hhash pointer to a HASH_HandleTypeDef structure that contains
  *         the configuration information for HASH module
  * @param  pInBuffer Pointer to the input buffer (buffer to be hashed).
  * @param  Size Length of the input buffer in bytes.
  *          If the Size is not multiple of 64 bytes, the padding is managed by hardware.
  * @retval HAL status
  */
HAL_StatusTypeDef HAL_HASHEx_SHA224_Start_DMA(HASH_HandleTypeDef *hhash, uint8_t *pInBuffer, uint32_t Size)
{
  uint32_t inputaddr  = (uint32_t)pInBuffer;
  
   /* Process Locked */
  __HAL_LOCK(hhash);
  
  /* Change the HASH state */
  hhash->State = HAL_HASH_STATE_BUSY;
  
  /* Check if initialization phase has already been performed */
  if(hhash->Phase == HAL_HASH_PHASE_READY)
  {
    /* Select the SHA224 mode and reset the HASH processor core, so that the HASH will be ready to compute 
       the message digest of a new message */
    HASH->CR |= HASH_ALGOSELECTION_SHA224 | HASH_CR_INIT;
  }
   
  /* Configure the number of valid bits in last word of the message */
  __HAL_HASH_SET_NBVALIDBITS(Size);
  
  /* Set the phase */
  hhash->Phase = HAL_HASH_PHASE_PROCESS;
    
  /* Set the HASH DMA transfer complete callback */
  hhash->hdmain->XferCpltCallback = HASHEx_DMAXferCplt;
  /* Set the DMA error callback */
  hhash->hdmain->XferErrorCallback = HASHEx_DMAError;
  
  /* Enable the DMA In DMA Stream */
  HAL_DMA_Start_IT(hhash->hdmain, inputaddr, (uint32_t)&HASH->DIN, (Size%4 ? (Size+3)/4:Size/4));
  
  /* Enable DMA requests */
  HASH->CR |= (HASH_CR_DMAE);
  
   /* Process Unlocked */
  __HAL_UNLOCK(hhash);
  
  /* Return function status */
  return HAL_OK;
}

/**
  * @brief  Returns the computed digest in SHA224
  * @param  hhash pointer to a HASH_HandleTypeDef structure that contains
  *         the configuration information for HASH module
  * @param  pOutBuffer Pointer to the computed digest. Its size must be 28 bytes.
  * @param  Timeout Timeout value    
  * @retval HAL status
  */
HAL_StatusTypeDef HAL_HASHEx_SHA224_Finish(HASH_HandleTypeDef *hhash, uint8_t* pOutBuffer, uint32_t Timeout)
{
  uint32_t tickstart = 0;   
  
  /* Process Locked */
  __HAL_LOCK(hhash);
  
  /* Change HASH peripheral state */
  hhash->State = HAL_HASH_STATE_BUSY;
  
  /* Get tick */
  tickstart = HAL_GetTick();
  
  while(HAL_IS_BIT_CLR(HASH->SR, HASH_FLAG_DCIS))
  {
    /* Check for the Timeout */
    if(Timeout != HAL_MAX_DELAY)
    {
      if((Timeout == 0)||((HAL_GetTick() - tickstart ) > Timeout))
      {
        /* Change state */
        hhash->State = HAL_HASH_STATE_TIMEOUT;
        
        /* Process Unlocked */          
        __HAL_UNLOCK(hhash);
        
        return HAL_TIMEOUT;
      }
    }
  }
  
  /* Read the message digest */
  HASHEx_GetDigest(pOutBuffer, 28);
      
  /* Change HASH peripheral state */
  hhash->State = HAL_HASH_STATE_READY;
  
   /* Process Unlocked */
  __HAL_UNLOCK(hhash);
  
  /* Return function status */
  return HAL_OK;
}

/**
  * @brief  Initializes the HASH peripheral in SHA256 mode then enables DMA to
            control data transfer. Use HAL_HASH_SHA256_Finish() to get the digest.
  * @param  hhash pointer to a HASH_HandleTypeDef structure that contains
  *         the configuration information for HASH module
  * @param  pInBuffer Pointer to the input buffer (buffer to be hashed).
  * @param  Size Length of the input buffer in bytes.
  *          If the Size is not multiple of 64 bytes, the padding is managed by hardware.
  * @retval HAL status
  */
HAL_StatusTypeDef HAL_HASHEx_SHA256_Start_DMA(HASH_HandleTypeDef *hhash, uint8_t *pInBuffer, uint32_t Size)
{
  uint32_t inputaddr  = (uint32_t)pInBuffer;
  
   /* Process Locked */
  __HAL_LOCK(hhash);
  
  /* Change the HASH state */
  hhash->State = HAL_HASH_STATE_BUSY;
  
  /* Check if initialization phase has already been performed */
  if(hhash->Phase == HAL_HASH_PHASE_READY)
  {
    /* Select the SHA256 mode and reset the HASH processor core, so that the HASH will be ready to compute 
       the message digest of a new message */
    HASH->CR |= HASH_ALGOSELECTION_SHA256 | HASH_CR_INIT;
  }
  
  /* Configure the number of valid bits in last word of the message */
  __HAL_HASH_SET_NBVALIDBITS(Size);
  
  /* Set the phase */
  hhash->Phase = HAL_HASH_PHASE_PROCESS;
    
  /* Set the HASH DMA transfer complete callback */
  hhash->hdmain->XferCpltCallback = HASHEx_DMAXferCplt;
  /* Set the DMA error callback */
  hhash->hdmain->XferErrorCallback = HASHEx_DMAError;
  
  /* Enable the DMA In DMA Stream */
  HAL_DMA_Start_IT(hhash->hdmain, inputaddr, (uint32_t)&HASH->DIN, (Size%4 ? (Size+3)/4:Size/4));
  
  /* Enable DMA requests */
  HASH->CR |= (HASH_CR_DMAE);
  
   /* Process UnLock */
  __HAL_UNLOCK(hhash);
  
  /* Return function status */
  return HAL_OK;
}

/**
  * @brief  Returns the computed digest in SHA256.
  * @param  hhash pointer to a HASH_HandleTypeDef structure that contains
  *         the configuration information for HASH module
  * @param  pOutBuffer Pointer to the computed digest. Its size must be 32 bytes.
  * @param  Timeout Timeout value    
  * @retval HAL status
  */
HAL_StatusTypeDef HAL_HASHEx_SHA256_Finish(HASH_HandleTypeDef *hhash, uint8_t* pOutBuffer, uint32_t Timeout)
{
  uint32_t tickstart = 0;   
  
   /* Process Locked */
  __HAL_LOCK(hhash);
  
  /* Change HASH peripheral state */
  hhash->State = HAL_HASH_STATE_BUSY;
  
  /* Get tick */
  tickstart = HAL_GetTick();
  
  while(HAL_IS_BIT_CLR(HASH->SR, HASH_FLAG_DCIS))
  {
    /* Check for the Timeout */
    if(Timeout != HAL_MAX_DELAY)
    {
      if((Timeout == 0)||((HAL_GetTick() - tickstart ) > Timeout))
      {
        /* Change state */
        hhash->State = HAL_HASH_STATE_TIMEOUT;
        
        /* Process Unlocked */          
        __HAL_UNLOCK(hhash);
        
        return HAL_TIMEOUT;
      }
    }
  }
  
  /* Read the message digest */
  HASHEx_GetDigest(pOutBuffer, 32);
  
  /* Change HASH peripheral state */
  hhash->State = HAL_HASH_STATE_READY;
  
   /* Process Unlocked */
  __HAL_UNLOCK(hhash);
  
  /* Return function status */
  return HAL_OK;
}


/**
  * @}
  */
/** @defgroup HASHEx_Group5 HMAC processing functions using DMA mode 
 *  @brief   HMAC processing functions using DMA mode . 
 *
@verbatim   
 ===============================================================================
                ##### HMAC processing using DMA functions #####
 ===============================================================================  
    [..]  This section provides functions allowing to calculate in DMA mode
          the HMAC value using one of the following algorithms:
      (+) SHA224
      (+) SHA256

@endverbatim
  * @{
  */

/**
  * @brief  Initializes the HASH peripheral in HMAC SHA224 mode
  *         then enables DMA to control data transfer.
  * @param  hhash pointer to a HASH_HandleTypeDef structure that contains
  *         the configuration information for HASH module
  * @param  pInBuffer Pointer to the input buffer (buffer to be hashed).
  * @param  Size Length of the input buffer in bytes.
  *          If the Size is not multiple of 64 bytes, the padding is managed by hardware.
  * @retval HAL status
  */
HAL_StatusTypeDef HAL_HMACEx_SHA224_Start_DMA(HASH_HandleTypeDef *hhash, uint8_t *pInBuffer, uint32_t Size)
{
  uint32_t inputaddr;
  
  /* Process Locked */
  __HAL_LOCK(hhash);
  
  /* Change the HASH state */
  hhash->State = HAL_HASH_STATE_BUSY;
  
  /* Save buffer pointer and size in handle */
  hhash->pHashInBuffPtr = pInBuffer;
  hhash->HashBuffSize = Size;
  hhash->HashInCount = 0;
  
  /* Check if initialization phase has already been performed */
  if(hhash->Phase == HAL_HASH_PHASE_READY)
  {
    /* Check if key size is greater than 64 bytes */
    if(hhash->Init.KeySize > 64)
    {
      /* Select the HMAC SHA224 mode */
      HASH->CR |= (HASH_ALGOSELECTION_SHA224 | HASH_ALGOMODE_HMAC | HASH_HMAC_KEYTYPE_LONGKEY | HASH_CR_INIT);
    }
    else
    {
      /* Select the HMAC SHA224 mode */
      HASH->CR |= (HASH_ALGOSELECTION_SHA224 | HASH_ALGOMODE_HMAC | HASH_CR_INIT);
    }
  }
  
  /* Set the phase */
  hhash->Phase = HAL_HASH_PHASE_PROCESS;
  
  /* Configure the number of valid bits in last word of the message */
  __HAL_HASH_SET_NBVALIDBITS(hhash->Init.KeySize);
  
  /* Get the key address */
  inputaddr = (uint32_t)(hhash->Init.pKey);
  
  /* Set the HASH DMA transfer complete callback */
  hhash->hdmain->XferCpltCallback = HASHEx_DMAXferCplt;
  /* Set the DMA error callback */
  hhash->hdmain->XferErrorCallback = HASHEx_DMAError;
  
  /* Enable the DMA In DMA Stream */
  HAL_DMA_Start_IT(hhash->hdmain, inputaddr, (uint32_t)&HASH->DIN, (hhash->Init.KeySize%4 ? (hhash->Init.KeySize+3)/4:hhash->Init.KeySize/4));
  /* Enable DMA requests */
  HASH->CR |= (HASH_CR_DMAE);
  
  /* Process Unlocked */
  __HAL_UNLOCK(hhash);
  
  /* Return function status */
  return HAL_OK;
}

/**
  * @brief  Initializes the HASH peripheral in HMAC SHA256 mode
  *         then enables DMA to control data transfer.
  * @param  hhash pointer to a HASH_HandleTypeDef structure that contains
  *         the configuration information for HASH module
  * @param  pInBuffer Pointer to the input buffer (buffer to be hashed).
  * @param  Size Length of the input buffer in bytes.
  *          If the Size is not multiple of 64 bytes, the padding is managed by hardware.
  * @retval HAL status
  */
HAL_StatusTypeDef HAL_HMACEx_SHA256_Start_DMA(HASH_HandleTypeDef *hhash, uint8_t *pInBuffer, uint32_t Size)
{
  uint32_t inputaddr;
  
  /* Process Locked */
  __HAL_LOCK(hhash);
  
  /* Change the HASH state */
  hhash->State = HAL_HASH_STATE_BUSY;
  
  /* Save buffer pointer and size in handle */
  hhash->pHashInBuffPtr = pInBuffer;
  hhash->HashBuffSize = Size;
  hhash->HashInCount = 0;
  
  /* Check if initialization phase has already been performed */
  if(hhash->Phase == HAL_HASH_PHASE_READY)
  {
    /* Check if key size is greater than 64 bytes */
    if(hhash->Init.KeySize > 64)
    {
      /* Select the HMAC SHA256 mode */
      HASH->CR |= (HASH_ALGOSELECTION_SHA256 | HASH_ALGOMODE_HMAC | HASH_HMAC_KEYTYPE_LONGKEY);
    }
    else
    {
      /* Select the HMAC SHA256 mode */
      HASH->CR |= (HASH_ALGOSELECTION_SHA256 | HASH_ALGOMODE_HMAC);
    }
    /* Reset the HASH processor core, so that the HASH will be ready to compute 
       the message digest of a new message */
    HASH->CR |= HASH_CR_INIT;
  }
  
  /* Set the phase */
  hhash->Phase = HAL_HASH_PHASE_PROCESS;
  
  /* Configure the number of valid bits in last word of the message */
  __HAL_HASH_SET_NBVALIDBITS(hhash->Init.KeySize);
  
  /* Get the key address */
  inputaddr = (uint32_t)(hhash->Init.pKey);
  
  /* Set the HASH DMA transfer complete callback */
  hhash->hdmain->XferCpltCallback = HASHEx_DMAXferCplt;
  /* Set the DMA error callback */
  hhash->hdmain->XferErrorCallback = HASHEx_DMAError;
  
  /* Enable the DMA In DMA Stream */
  HAL_DMA_Start_IT(hhash->hdmain, inputaddr, (uint32_t)&HASH->DIN, (hhash->Init.KeySize%4 ? (hhash->Init.KeySize+3)/4:hhash->Init.KeySize/4));
  /* Enable DMA requests */
  HASH->CR |= (HASH_CR_DMAE);
  
  /* Process Unlocked */
  __HAL_UNLOCK(hhash);
  
  /* Return function status */
  return HAL_OK;
=======
/**
  * @brief  MD5 HMAC step 1 completion and step 2 start in multi-buffer DMA mode.
  * @note   Step 1 consists in writing the inner hash function key in the IP,
  *         step 2 consists in writing the message text.
  * @note   The API carries out the HMAC step 1 then starts step 2 with
  *         the first buffer entered to the IP. DCAL bit is not automatically set after
  *         the message buffer feeding, allowing other messages DMA transfers to occur.
  * @note   Same key is used for the inner and the outer hash functions; pointer to key and
  *         key size are respectively stored in hhash->Init.pKey and hhash->Init.KeySize.
  * @note   The input buffer size (in bytes) must be a multiple of 4 otherwise, the
  *         HASH digest computation is corrupted.
  * @param  hhash: HASH handle.
  * @param  pInBuffer: pointer to the input buffer (message buffer).
  * @param  Size: length of the input buffer in bytes.
  * @retval HAL status
  */
HAL_StatusTypeDef HAL_HMACEx_MD5_Step1_2_DMA(HASH_HandleTypeDef *hhash, uint8_t *pInBuffer, uint32_t Size)
{
  hhash->DigestCalculationDisable = SET;
  return  HMAC_Start_DMA(hhash, pInBuffer, Size, HASH_ALGOSELECTION_MD5);
}

/**
  * @brief  MD5 HMAC step 2 in multi-buffer DMA mode.
  * @note   Step 2 consists in writing the message text in the IP.
  * @note   The API carries on the HMAC step 2, applied to the buffer entered as input
  *         parameter. DCAL bit is not automatically set after the message buffer feeding,
  *         allowing other messages DMA transfers to occur.
  * @note   Same key is used for the inner and the outer hash functions; pointer to key and
  *         key size are respectively stored in hhash->Init.pKey and hhash->Init.KeySize.
  * @note   The input buffer size (in bytes) must be a multiple of 4 otherwise, the
  *         HASH digest computation is corrupted.
  * @param  hhash: HASH handle.
  * @param  pInBuffer: pointer to the input buffer (message buffer).
  * @param  Size: length of the input buffer in bytes.
  * @retval HAL status
  */
HAL_StatusTypeDef HAL_HMACEx_MD5_Step2_DMA(HASH_HandleTypeDef *hhash, uint8_t *pInBuffer, uint32_t Size)
{
  if (hhash->DigestCalculationDisable != SET)
  {
    return HAL_ERROR;
  }
  return  HMAC_Start_DMA(hhash, pInBuffer, Size, HASH_ALGOSELECTION_MD5);
}

/**
  * @brief  MD5 HMAC step 2 wrap-up and step 3 completion in multi-buffer DMA mode.
  * @note   Step 2 consists in writing the message text in the IP,
  *         step 3 consists in writing the outer hash function key.
  * @note   The API wraps up the HMAC step 2 in processing the buffer entered as input
  *         parameter (the input buffer must be the last one of the multi-buffer thread)
  *         then carries out HMAC step 3.
  * @note   Same key is used for the inner and the outer hash functions; pointer to key and
  *         key size are respectively stored in hhash->Init.pKey and hhash->Init.KeySize.
  * @note   Once the DMA transfers are finished (indicated by hhash->State set back
  *         to HAL_HASH_STATE_READY), HAL_HASHEx_SHA256_Finish() API must be called to retrieve
  *         the computed digest.
  * @param  hhash: HASH handle.
  * @param  pInBuffer: pointer to the input buffer (message buffer).
  * @param  Size: length of the input buffer in bytes.
  * @retval HAL status
  */
HAL_StatusTypeDef HAL_HMACEx_MD5_Step2_3_DMA(HASH_HandleTypeDef *hhash, uint8_t *pInBuffer, uint32_t Size)
{
  hhash->DigestCalculationDisable = RESET;
  return  HMAC_Start_DMA(hhash, pInBuffer, Size, HASH_ALGOSELECTION_MD5);
}


/**
  * @brief  SHA1 HMAC step 1 completion and step 2 start in multi-buffer DMA mode.
  * @note   Step 1 consists in writing the inner hash function key in the IP,
  *         step 2 consists in writing the message text.
  * @note   The API carries out the HMAC step 1 then starts step 2 with
  *         the first buffer entered to the IP. DCAL bit is not automatically set after
  *         the message buffer feeding, allowing other messages DMA transfers to occur.
  * @note   Same key is used for the inner and the outer hash functions; pointer to key and
  *         key size are respectively stored in hhash->Init.pKey and hhash->Init.KeySize.
  * @note   The input buffer size (in bytes) must be a multiple of 4 otherwise, the
  *         HASH digest computation is corrupted.
  * @param  hhash: HASH handle.
  * @param  pInBuffer: pointer to the input buffer (message buffer).
  * @param  Size: length of the input buffer in bytes.
  * @retval HAL status
  */
HAL_StatusTypeDef HAL_HMACEx_SHA1_Step1_2_DMA(HASH_HandleTypeDef *hhash, uint8_t *pInBuffer, uint32_t Size)
{
  hhash->DigestCalculationDisable = SET;
  return  HMAC_Start_DMA(hhash, pInBuffer, Size, HASH_ALGOSELECTION_SHA1);
}

/**
  * @brief  SHA1 HMAC step 2 in multi-buffer DMA mode.
  * @note   Step 2 consists in writing the message text in the IP.
  * @note   The API carries on the HMAC step 2, applied to the buffer entered as input
  *         parameter. DCAL bit is not automatically set after the message buffer feeding,
  *         allowing other messages DMA transfers to occur.
  * @note   Same key is used for the inner and the outer hash functions; pointer to key and
  *         key size are respectively stored in hhash->Init.pKey and hhash->Init.KeySize.
  * @note   The input buffer size (in bytes) must be a multiple of 4 otherwise, the
  *         HASH digest computation is corrupted.
  * @param  hhash: HASH handle.
  * @param  pInBuffer: pointer to the input buffer (message buffer).
  * @param  Size: length of the input buffer in bytes.
  * @retval HAL status
  */
HAL_StatusTypeDef HAL_HMACEx_SHA1_Step2_DMA(HASH_HandleTypeDef *hhash, uint8_t *pInBuffer, uint32_t Size)
{
  if (hhash->DigestCalculationDisable != SET)
  {
    return HAL_ERROR;
  }
  return  HMAC_Start_DMA(hhash, pInBuffer, Size, HASH_ALGOSELECTION_SHA1);
}

/**
  * @brief  SHA1 HMAC step 2 wrap-up and step 3 completion in multi-buffer DMA mode.
  * @note   Step 2 consists in writing the message text in the IP,
  *         step 3 consists in writing the outer hash function key.
  * @note   The API wraps up the HMAC step 2 in processing the buffer entered as input
  *         parameter (the input buffer must be the last one of the multi-buffer thread)
  *         then carries out HMAC step 3.
  * @note   Same key is used for the inner and the outer hash functions; pointer to key and
  *         key size are respectively stored in hhash->Init.pKey and hhash->Init.KeySize.
  * @note   Once the DMA transfers are finished (indicated by hhash->State set back
  *         to HAL_HASH_STATE_READY), HAL_HASHEx_SHA256_Finish() API must be called to retrieve
  *         the computed digest.
  * @param  hhash: HASH handle.
  * @param  pInBuffer: pointer to the input buffer (message buffer).
  * @param  Size: length of the input buffer in bytes.
  * @retval HAL status
  */
HAL_StatusTypeDef HAL_HMACEx_SHA1_Step2_3_DMA(HASH_HandleTypeDef *hhash, uint8_t *pInBuffer, uint32_t Size)
{
  hhash->DigestCalculationDisable = RESET;
  return  HMAC_Start_DMA(hhash, pInBuffer, Size, HASH_ALGOSELECTION_SHA1);
}

/**
  * @brief  SHA224 HMAC step 1 completion and step 2 start in multi-buffer DMA mode.
  * @note   Step 1 consists in writing the inner hash function key in the IP,
  *         step 2 consists in writing the message text.
  * @note   The API carries out the HMAC step 1 then starts step 2 with
  *         the first buffer entered to the IP. DCAL bit is not automatically set after
  *         the message buffer feeding, allowing other messages DMA transfers to occur.
  * @note   Same key is used for the inner and the outer hash functions; pointer to key and
  *         key size are respectively stored in hhash->Init.pKey and hhash->Init.KeySize.
  * @note   The input buffer size (in bytes) must be a multiple of 4 otherwise, the
  *         HASH digest computation is corrupted.
  * @param  hhash: HASH handle.
  * @param  pInBuffer: pointer to the input buffer (message buffer).
  * @param  Size: length of the input buffer in bytes.
  * @retval HAL status
  */
HAL_StatusTypeDef HAL_HMACEx_SHA224_Step1_2_DMA(HASH_HandleTypeDef *hhash, uint8_t *pInBuffer, uint32_t Size)
{
  hhash->DigestCalculationDisable = SET;
  return  HMAC_Start_DMA(hhash, pInBuffer, Size, HASH_ALGOSELECTION_SHA224);
}

/**
  * @brief  SHA224 HMAC step 2 in multi-buffer DMA mode.
  * @note   Step 2 consists in writing the message text in the IP.
  * @note   The API carries on the HMAC step 2, applied to the buffer entered as input
  *         parameter. DCAL bit is not automatically set after the message buffer feeding,
  *         allowing other messages DMA transfers to occur.
  * @note   Same key is used for the inner and the outer hash functions; pointer to key and
  *         key size are respectively stored in hhash->Init.pKey and hhash->Init.KeySize.
  * @note   The input buffer size (in bytes) must be a multiple of 4 otherwise, the
  *         HASH digest computation is corrupted.
  * @param  hhash: HASH handle.
  * @param  pInBuffer: pointer to the input buffer (message buffer).
  * @param  Size: length of the input buffer in bytes.
  * @retval HAL status
  */
HAL_StatusTypeDef HAL_HMACEx_SHA224_Step2_DMA(HASH_HandleTypeDef *hhash, uint8_t *pInBuffer, uint32_t Size)
{
  if (hhash->DigestCalculationDisable != SET)
  {
    return HAL_ERROR;
  }
  return  HMAC_Start_DMA(hhash, pInBuffer, Size, HASH_ALGOSELECTION_SHA224);
}

/**
  * @brief  SHA224 HMAC step 2 wrap-up and step 3 completion in multi-buffer DMA mode.
  * @note   Step 2 consists in writing the message text in the IP,
  *         step 3 consists in writing the outer hash function key.
  * @note   The API wraps up the HMAC step 2 in processing the buffer entered as input
  *         parameter (the input buffer must be the last one of the multi-buffer thread)
  *         then carries out HMAC step 3.
  * @note   Same key is used for the inner and the outer hash functions; pointer to key and
  *         key size are respectively stored in hhash->Init.pKey and hhash->Init.KeySize.
  * @note   Once the DMA transfers are finished (indicated by hhash->State set back
  *         to HAL_HASH_STATE_READY), HAL_HASHEx_SHA256_Finish() API must be called to retrieve
  *         the computed digest.
  * @param  hhash: HASH handle.
  * @param  pInBuffer: pointer to the input buffer (message buffer).
  * @param  Size: length of the input buffer in bytes.
  * @retval HAL status
  */
HAL_StatusTypeDef HAL_HMACEx_SHA224_Step2_3_DMA(HASH_HandleTypeDef *hhash, uint8_t *pInBuffer, uint32_t Size)
{
  hhash->DigestCalculationDisable = RESET;
  return  HMAC_Start_DMA(hhash, pInBuffer, Size, HASH_ALGOSELECTION_SHA224);
}

/**
  * @brief  SHA256 HMAC step 1 completion and step 2 start in multi-buffer DMA mode.
  * @note   Step 1 consists in writing the inner hash function key in the IP,
  *         step 2 consists in writing the message text.
  * @note   The API carries out the HMAC step 1 then starts step 2 with
  *         the first buffer entered to the IP. DCAL bit is not automatically set after
  *         the message buffer feeding, allowing other messages DMA transfers to occur.
  * @note   Same key is used for the inner and the outer hash functions; pointer to key and
  *         key size are respectively stored in hhash->Init.pKey and hhash->Init.KeySize.
  * @note   The input buffer size (in bytes) must be a multiple of 4 otherwise, the
  *         HASH digest computation is corrupted.
  * @param  hhash: HASH handle.
  * @param  pInBuffer: pointer to the input buffer (message buffer).
  * @param  Size: length of the input buffer in bytes.
  * @retval HAL status
  */
HAL_StatusTypeDef HAL_HMACEx_SHA256_Step1_2_DMA(HASH_HandleTypeDef *hhash, uint8_t *pInBuffer, uint32_t Size)
{
  hhash->DigestCalculationDisable = SET;
  return  HMAC_Start_DMA(hhash, pInBuffer, Size, HASH_ALGOSELECTION_SHA256);
}

/**
  * @brief  SHA256 HMAC step 2 in multi-buffer DMA mode.
  * @note   Step 2 consists in writing the message text in the IP.
  * @note   The API carries on the HMAC step 2, applied to the buffer entered as input
  *         parameter. DCAL bit is not automatically set after the message buffer feeding,
  *         allowing other messages DMA transfers to occur.
  * @note   Same key is used for the inner and the outer hash functions; pointer to key and
  *         key size are respectively stored in hhash->Init.pKey and hhash->Init.KeySize.
  * @note   The input buffer size (in bytes) must be a multiple of 4 otherwise, the
  *         HASH digest computation is corrupted.
  * @param  hhash: HASH handle.
  * @param  pInBuffer: pointer to the input buffer (message buffer).
  * @param  Size: length of the input buffer in bytes.
  * @retval HAL status
  */
HAL_StatusTypeDef HAL_HMACEx_SHA256_Step2_DMA(HASH_HandleTypeDef *hhash, uint8_t *pInBuffer, uint32_t Size)
{
  if (hhash->DigestCalculationDisable != SET)
  {
    return HAL_ERROR;
  }
  return  HMAC_Start_DMA(hhash, pInBuffer, Size, HASH_ALGOSELECTION_SHA256);
}

/**
  * @brief  SHA256 HMAC step 2 wrap-up and step 3 completion in multi-buffer DMA mode.
  * @note   Step 2 consists in writing the message text in the IP,
  *         step 3 consists in writing the outer hash function key.
  * @note   The API wraps up the HMAC step 2 in processing the buffer entered as input
  *         parameter (the input buffer must be the last one of the multi-buffer thread)
  *         then carries out HMAC step 3.
  * @note   Same key is used for the inner and the outer hash functions; pointer to key and
  *         key size are respectively stored in hhash->Init.pKey and hhash->Init.KeySize.
  * @note   Once the DMA transfers are finished (indicated by hhash->State set back
  *         to HAL_HASH_STATE_READY), HAL_HASHEx_SHA256_Finish() API must be called to retrieve
  *         the computed digest.
  * @param  hhash: HASH handle.
  * @param  pInBuffer: pointer to the input buffer (message buffer).
  * @param  Size: length of the input buffer in bytes.
  * @retval HAL status
  */
HAL_StatusTypeDef HAL_HMACEx_SHA256_Step2_3_DMA(HASH_HandleTypeDef *hhash, uint8_t *pInBuffer, uint32_t Size)
{
  hhash->DigestCalculationDisable = RESET;
  return  HMAC_Start_DMA(hhash, pInBuffer, Size, HASH_ALGOSELECTION_SHA256);
>>>>>>> 49e424905b5922b07aa7166ec7a0eeb90adf58a8
}

/**
  * @}
  */

<<<<<<< HEAD
=======

>>>>>>> 49e424905b5922b07aa7166ec7a0eeb90adf58a8
/**
  * @}
  */
#endif /* HAL_HASH_MODULE_ENABLED */

/**
  * @}
  */
<<<<<<< HEAD
#endif /* STM32F756xx || STM32F777xx || STM32F779xx || STM32F750xx */

=======
#endif /*  HASH*/
>>>>>>> 49e424905b5922b07aa7166ec7a0eeb90adf58a8
/**
  * @}
  */

<<<<<<< HEAD
=======


>>>>>>> 49e424905b5922b07aa7166ec7a0eeb90adf58a8
/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
