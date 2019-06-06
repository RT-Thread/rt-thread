/**
  ******************************************************************************
  * @file    stm32f7xx_hal_cryp.c
  * @author  MCD Application Team
  * @brief   CRYP HAL module driver.
  *          This file provides firmware functions to manage the following 
  *          functionalities of the Cryptography (CRYP) peripheral:
<<<<<<< HEAD
  *           + Initialization and de-initialization functions
  *           + AES processing functions
  *           + DES processing functions
  *           + TDES processing functions
=======
  *           + Initialization, de-initialization, set config and get config  functions
  *           + DES/TDES, AES processing functions
>>>>>>> 49e424905b5922b07aa7166ec7a0eeb90adf58a8
  *           + DMA callback functions
  *           + CRYP IRQ handler management
  *           + Peripheral State functions
  *
  @verbatim
  ==============================================================================
                     ##### How to use this driver #####
  ==============================================================================
    [..]
<<<<<<< HEAD
      The CRYP HAL driver can be used as follows:

      (#)Initialize the CRYP low level resources by implementing the HAL_CRYP_MspInit():
         (##) Enable the CRYP interface clock using __HAL_RCC_CRYP_CLK_ENABLE()
         (##) In case of using interrupts (e.g. HAL_CRYP_AESECB_Encrypt_IT())
             (+++) Configure the CRYP interrupt priority using HAL_NVIC_SetPriority()
             (+++) Enable the CRYP IRQ handler using HAL_NVIC_EnableIRQ()
             (+++) In CRYP IRQ handler, call HAL_CRYP_IRQHandler()
         (##) In case of using DMA to control data transfer (e.g. HAL_CRYP_AESECB_Encrypt_DMA())
             (+++) Enable the DMAx interface clock using __DMAx_CLK_ENABLE()
=======
      The CRYP HAL driver can be used in CRYP or TinyAES IP as follows:

      (#)Initialize the CRYP low level resources by implementing the HAL_CRYP_MspInit():
         (##) Enable the CRYP interface clock using __HAL_RCC_CRYP_CLK_ENABLE()or __HAL_RCC_AES_CLK_ENABLE for TinyAES IP
         (##) In case of using interrupts (e.g. HAL_CRYP_Encrypt_IT())
             (+++) Configure the CRYP interrupt priority using HAL_NVIC_SetPriority()
             (+++) Enable the CRYP IRQ handler using HAL_NVIC_EnableIRQ()
             (+++) In CRYP IRQ handler, call HAL_CRYP_IRQHandler()
         (##) In case of using DMA to control data transfer (e.g. HAL_CRYP_Encrypt_DMA())
             (+++) Enable the DMAx interface clock using __RCC_DMAx_CLK_ENABLE()
>>>>>>> 49e424905b5922b07aa7166ec7a0eeb90adf58a8
             (+++) Configure and enable two DMA streams one for managing data transfer from
                 memory to peripheral (input stream) and another stream for managing data
                 transfer from peripheral to memory (output stream)
             (+++) Associate the initialized DMA handle to the CRYP DMA handle
                 using  __HAL_LINKDMA()
             (+++) Configure the priority and enable the NVIC for the transfer complete
                 interrupt on the two DMA Streams. The output stream should have higher
                 priority than the input stream HAL_NVIC_SetPriority() and HAL_NVIC_EnableIRQ()
<<<<<<< HEAD
    
      (#)Initialize the CRYP HAL using HAL_CRYP_Init(). This function configures mainly:
         (##) The data type: 1-bit, 8-bit, 16-bit and 32-bit
         (##) The key size: 128, 192 and 256. This parameter is relevant only for AES
         (##) The encryption/decryption key. It's size depends on the algorithm
              used for encryption/decryption
         (##) The initialization vector (counter). It is not used ECB mode.
    
      (#)Three processing (encryption/decryption) functions are available:
         (##) Polling mode: encryption and decryption APIs are blocking functions
              i.e. they process the data and wait till the processing is finished,
              e.g. HAL_CRYP_AESCBC_Encrypt()
         (##) Interrupt mode: encryption and decryption APIs are not blocking functions
              i.e. they process the data under interrupt,
              e.g. HAL_CRYP_AESCBC_Encrypt_IT()
         (##) DMA mode: encryption and decryption APIs are not blocking functions
              i.e. the data transfer is ensured by DMA,
              e.g. HAL_CRYP_AESCBC_Encrypt_DMA()
    
      (#)When the processing function is called at first time after HAL_CRYP_Init()
         the CRYP peripheral is initialized and processes the buffer in input.
         At second call, the processing function performs an append of the already
         processed buffer.
         When a new data block is to be processed, call HAL_CRYP_Init() then the
         processing function.
    
       (#)Call HAL_CRYP_DeInit() to deinitialize the CRYP peripheral.

=======

      (#)Initialize the CRYP according to the specified parameters :
         (##) The data type: 1-bit, 8-bit, 16-bit or 32-bit.
         (##) The key size: 128, 192 or 256.
         (##) The AlgoMode DES/ TDES Algorithm ECB/CBC or AES Algorithm ECB/CBC/CTR/GCM or CCM.
         (##) The initialization vector (counter). It is not used in ECB mode.
         (##) The key buffer used for encryption/decryption.
         (##) The Header used only in AES GCM and CCM Algorithm for authentication.
         (##) The HeaderSize The size of header buffer in word.
         (##) The B0 block is the first authentication block used only  in AES CCM mode.

      (#)Three processing (encryption/decryption) functions are available:
         (##) Polling mode: encryption and decryption APIs are blocking functions
              i.e. they process the data and wait till the processing is finished,
              e.g. HAL_CRYP_Encrypt & HAL_CRYP_Decrypt
         (##) Interrupt mode: encryption and decryption APIs are not blocking functions
              i.e. they process the data under interrupt,
              e.g. HAL_CRYP_Encrypt_IT & HAL_CRYP_Decrypt_IT
         (##) DMA mode: encryption and decryption APIs are not blocking functions
              i.e. the data transfer is ensured by DMA,
              e.g. HAL_CRYP_Encrypt_DMA & HAL_CRYP_Decrypt_DMA

      (#)When the processing function is called at first time after HAL_CRYP_Init()
         the CRYP peripheral is configured and processes the buffer in input.
         At second call, no need to Initialize the CRYP, user have to get current configuration via
         HAL_CRYP_GetConfig() API, then only  HAL_CRYP_SetConfig() is requested to set
         new parametres, finally user can  start encryption/decryption.

       (#)Call HAL_CRYP_DeInit() to deinitialize the CRYP peripheral.

    [..]
      The cryptographic processor supports following standards:
      (#) The data encryption standard (DES) and Triple-DES (TDES) supported only by CRYP1 IP:
         (##)64-bit data block processing
         (##) chaining modes supported :
             (+++)  Electronic Code Book(ECB)
             (+++)  Cipher Block Chaining (CBC)
         (##) keys length supported :64-bit, 128-bit and 192-bit.
      (#) The advanced encryption standard (AES) supported  by CRYP1 & TinyAES IP:
         (##)128-bit data block processing
         (##) chaining modes supported :
             (+++)  Electronic Code Book(ECB)
             (+++)  Cipher Block Chaining (CBC)
             (+++)  Counter mode (CTR)
             (+++)  Galois/counter mode (GCM/GMAC)
             (+++)  Counter with Cipher Block Chaining-Message(CCM)
         (##) keys length Supported :
             (+++) for CRYP1 IP: 128-bit, 192-bit and 256-bit.
             (+++) for TinyAES IP:  128-bit and 256-bit

    [..]  This section describes the AES Galois/counter mode (GCM) supported by both CRYP1 IP:
      (#)  Algorithm supported :
         (##) Galois/counter mode (GCM)
         (##) Galois message authentication code (GMAC) :is exactly the same as
              GCM algorithm composed only by an header.
      (#)  Four phases are performed in GCM :
         (##) Init phase: IP prepares the GCM hash subkey (H) and do the IV processing
         (##) Header phase: IP processes the Additional Authenticated Data (AAD), with hash
          computation only.
         (##) Payload phase: IP processes the plaintext (P) with hash computation + keystream
          encryption + data XORing. It works in a similar way for ciphertext (C).
         (##) Final phase: IP generates the authenticated tag (T) using the last block of data.
      (#)  structure of message construction in GCM is defined as below  :
         (##) 16 bytes Initial Counter Block (ICB)composed of IV and counter
         (##) The authenticated header A (also knows as Additional Authentication Data AAD)
          this part of the message is only authenticated, not encrypted.
         (##) The plaintext message P is both authenticated and encrypted as ciphertext.
          GCM standard specifies that ciphertext has same bit length as the plaintext.
         (##) The last block is composed of the length of A (on 64 bits) and the length of ciphertext
          (on 64 bits)

    [..]  This section describe The AES Counter with Cipher Block Chaining-Message
          Authentication Code (CCM) supported by both CRYP1 IP:
      (#)  Specific parameters for CCM  :

         (##) B0 block  : According to NIST Special Publication 800-38C,
            The first block B0 is formatted as follows, where l(m) is encoded in
            most-significant-byte first order(see below table 3)

              (+++)  Q: a bit string representation of the octet length of P (plaintext)
              (+++)  q The octet length of the binary representation of the octet length of the payload
              (+++)  A nonce (N), n The octet length of the where n+q=15.
              (+++)  Flags: most significant octet containing four flags for control information,
              (+++)  t The octet length of the MAC.
         (##) B1 block (header) : associated data length(a) concatenated with Associated Data (A)
              the associated data length expressed in bytes (a) defined as below:
            (+++)  If 0 < a < 216-28, then it is encoded as [a]16, i.e. two octets
            (+++)  If 216-28 < a < 232, then it is encoded as 0xff || 0xfe || [a]32, i.e. six octets
            (+++)  If 232 < a < 264, then it is encoded as 0xff || 0xff || [a]64, i.e. ten octets
         (##) CTRx block  : control blocks
            (+++) Generation of CTR1 from first block B0 information :
              equal to B0 with first 5 bits zeroed and most significant bits storing octet
              length of P also zeroed, then incremented by one ( see below Table 4)
            (+++) Generation of CTR0: same as CTR1 with bit[0] set to zero.

      (#)  Four phases are performed in CCM for CRYP1 IP:
         (##) Init phase: IP prepares the GCM hash subkey (H) and do the IV processing
         (##) Header phase: IP processes the Additional Authenticated Data (AAD), with hash
          computation only.
         (##) Payload phase: IP processes the plaintext (P) with hash computation + keystream
          encryption + data XORing. It works in a similar way for ciphertext (C).
         (##) Final phase: IP generates the authenticated tag (T) using the last block of data.

  *** Callback registration ***
  =============================================

  The compilation define  USE_HAL_CRYP_REGISTER_CALLBACKS when set to 1
  allows the user to configure dynamically the driver callbacks.
  Use Functions @ref HAL_CRYP_RegisterCallback() or HAL_CRYP_RegisterXXXCallback()
  to register an interrupt callback.

  Function @ref HAL_CRYP_RegisterCallback() allows to register following callbacks:
    (+) InCpltCallback     :  Input FIFO transfer completed callback.
    (+) OutCpltCallback    : Output FIFO transfer completed callback.
    (+) ErrorCallback      : callback for error detection.
    (+) MspInitCallback    : CRYP MspInit.
    (+) MspDeInitCallback  : CRYP MspDeInit.
  This function takes as parameters the HAL peripheral handle, the Callback ID
  and a pointer to the user callback function.

  Use function @ref HAL_CRYP_UnRegisterCallback() to reset a callback to the default
  weak function.
  @ref HAL_CRYP_UnRegisterCallback() takes as parameters the HAL peripheral handle,
  and the Callback ID.
  This function allows to reset following callbacks:
    (+) InCpltCallback     :  Input FIFO transfer completed callback.
    (+) OutCpltCallback    : Output FIFO transfer completed callback.
    (+) ErrorCallback      : callback for error detection.
    (+) MspInitCallback    : CRYP MspInit.
    (+) MspDeInitCallback  : CRYP MspDeInit.

  By default, after the @ref HAL_CRYP_Init() and when the state is HAL_CRYP_STATE_RESET
  all callbacks are set to the corresponding weak functions :
  examples @ref HAL_CRYP_InCpltCallback() , @ref HAL_CRYP_OutCpltCallback().
  Exception done for MspInit and MspDeInit functions that are
  reset to the legacy weak function in the @ref HAL_CRYP_Init()/ @ref HAL_CRYP_DeInit() only when
  these callbacks are null (not registered beforehand).
  if not, MspInit or MspDeInit are not null, the @ref HAL_CRYP_Init() / @ref HAL_CRYP_DeInit()
  keep and use the user MspInit/MspDeInit functions (registered beforehand)

  Callbacks can be registered/unregistered in HAL_CRYP_STATE_READY state only.
  Exception done MspInit/MspDeInit callbacks that can be registered/unregistered
  in HAL_CRYP_STATE_READY or HAL_CRYP_STATE_RESET state,
  thus registered (user) MspInit/DeInit callbacks can be used during the Init/DeInit.
  In that case first register the MspInit/MspDeInit user callbacks
  using @ref HAL_CRYP_RegisterCallback() before calling @ref HAL_CRYP_DeInit()
  or @ref HAL_CRYP_Init() function.

  When The compilation define USE_HAL_CRYP_REGISTER_CALLBACKS is set to 0 or
  not defined, the callback registration feature is not available and all callbacks
  are set to the corresponding weak functions.

  Table 1. Initial Counter Block (ICB)
          +-------------------------------------------------------+
          |       Initialization vector (IV)      |  Counter      |
          |----------------|----------------|-----------|---------|
         127              95                63            31       0


              Bit Number    Register           Contents
              ----------   ---------------       -----------
              127 ...96    CRYP_IV1R[31:0]     ICB[127:96]
              95  ...64    CRYP_IV1L[31:0]     B0[95:64]
              63 ... 32    CRYP_IV0R[31:0]     ICB[63:32]
              31 ... 0     CRYP_IV0L[31:0]     ICB[31:0], where 32-bit counter= 0x2

  Table 2.  GCM last block definition

          +-------------------------------------------------------------------+
          |  Bit[0]   |  Bit[32]           |  Bit[64]  | Bit[96]              |
          |-----------|--------------------|-----------|----------------------|
          |   0x0     | Header length[31:0]|     0x0   | Payload length[31:0] |
          |-----------|--------------------|-----------|----------------------|

  Table 3. B0 block
                Octet Number   Contents
                ------------   ---------
                0              Flags
                1 ... 15-q     Nonce N
                16-q ... 15    Q

            the Flags field is formatted as follows:

                Bit Number   Contents
                ----------   ----------------------
                7            Reserved (always zero)
                6            Adata
                5 ... 3      (t-2)/2
                2 ... 0      [q-1]3

 Table 4. CTRx block
                Bit Number    Register           Contents
                ----------   ---------------       -----------
                127 ...96    CRYP_IV1R[31:0]     B0[127:96], where Q length bits are set to 0, except for
                                                 bit 0 that is set to 1
                95  ...64    CRYP_IV1L[31:0]     B0[95:64]
                63 ... 32    CRYP_IV0R[31:0]     B0[63:32]
                31 ... 0     CRYP_IV0L[31:0]     B0[31:0], where flag bits set to 0

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
  * <h2><center>&copy; Copyright (c) 2016 STMicroelectronics. 
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

<<<<<<< HEAD
#ifdef HAL_CRYP_MODULE_ENABLED

#if defined (CRYP)

/** @addtogroup STM32F7xx_HAL_Driver
  * @{
  */
=======
/** @addtogroup STM32F7xx_HAL_Driver
  * @{
  */
  
#if defined (AES)  || defined (CRYP)
  
>>>>>>> 49e424905b5922b07aa7166ec7a0eeb90adf58a8
/** @defgroup CRYP CRYP
  * @brief CRYP HAL module driver.
  * @{
  */

<<<<<<< HEAD
/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/** @addtogroup CRYP_Private_define
  * @{
  */
#define CRYP_TIMEOUT_VALUE  1
/**
  * @}
  */ 
  
/* Private macro -------------------------------------------------------------*/
=======

#ifdef HAL_CRYP_MODULE_ENABLED

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/** @addtogroup CRYP_Private_Defines
  * @{
  */
#define CRYP_TIMEOUT_KEYPREPARATION      82U         /*The latency of key preparation operation is 82 clock cycles.*/
#define CRYP_TIMEOUT_GCMCCMINITPHASE     299U        /*  The latency of  GCM/CCM init phase to prepare hash subkey is 299 clock cycles.*/
#define CRYP_TIMEOUT_GCMCCMHEADERPHASE   290U        /*  The latency of  GCM/CCM header phase is 290 clock cycles.*/

#define  CRYP_PHASE_READY                0x00000001U /*!< CRYP peripheral is ready for initialization. */
#define  CRYP_PHASE_PROCESS              0x00000002U /*!< CRYP peripheral is in processing phase */
    
#if defined(AES)
#define CRYP_OPERATINGMODE_ENCRYPT                   0x00000000U     /*!< Encryption mode(Mode 1)  */
#define CRYP_OPERATINGMODE_KEYDERIVATION             AES_CR_MODE_0   /*!< Key derivation mode  only used when performing ECB and CBC decryptions (Mode 2) */
#define CRYP_OPERATINGMODE_DECRYPT                   AES_CR_MODE_1   /*!< Decryption    (Mode 3)    */
#define CRYP_OPERATINGMODE_KEYDERIVATION_DECRYPT     AES_CR_MODE     /*!< Key derivation and decryption only used when performing ECB and CBC decryptions (Mode 4) */
#define CRYP_PHASE_INIT                              0x00000000U        /*!< GCM/GMAC (or CCM) init phase */ 
#define CRYP_PHASE_HEADER                            AES_CR_GCMPH_0     /*!< GCM/GMAC or CCM header phase */ 
#define CRYP_PHASE_PAYLOAD                           AES_CR_GCMPH_1     /*!< GCM(/CCM) payload phase      */ 
#define CRYP_PHASE_FINAL                             AES_CR_GCMPH       /*!< GCM/GMAC or CCM  final phase */ 
#else  /* CRYP */
#define CRYP_PHASE_INIT                              0x00000000U             /*!< GCM/GMAC (or CCM) init phase */
#define CRYP_PHASE_HEADER                            CRYP_CR_GCM_CCMPH_0     /*!< GCM/GMAC or CCM header phase */ 
#define CRYP_PHASE_PAYLOAD                           CRYP_CR_GCM_CCMPH_1     /*!< GCM(/CCM) payload phase      */ 
#define CRYP_PHASE_FINAL                             CRYP_CR_GCM_CCMPH       /*!< GCM/GMAC or CCM  final phase */ 
#define CRYP_OPERATINGMODE_ENCRYPT                   0x00000000U             /*!< Encryption mode   */
#define CRYP_OPERATINGMODE_DECRYPT                   CRYP_CR_ALGODIR         /*!< Decryption        */
#endif /* End CRYP or  AES */ 

 /*  CTR1 information to use in CCM algorithm */
#define CRYP_CCM_CTR1_0                  0x07FFFFFFU         
#define CRYP_CCM_CTR1_1                  0xFFFFFF00U         
#define CRYP_CCM_CTR1_2                  0x00000001U         


/**
  * @}
  */

  
/* Private macro -------------------------------------------------------------*/
/** @addtogroup CRYP_Private_Macros
  * @{
  */

#if defined(CRYP)

#define CRYP_SET_PHASE(__HANDLE__, __PHASE__)  do{(__HANDLE__)->Instance->CR &= (uint32_t)(~CRYP_CR_GCM_CCMPH);\
                                                        (__HANDLE__)->Instance->CR |= (uint32_t)(__PHASE__);\
                                                       }while(0)

#define HAL_CRYP_FIFO_FLUSH(__HANDLE__) ((__HANDLE__)->Instance->CR |=  CRYP_CR_FFLUSH)  
                                                        
#else /*AES*/                                                         
#define CRYP_SET_PHASE(__HANDLE__, __PHASE__)  do{(__HANDLE__)->Instance->CR &= (uint32_t)(~AES_CR_GCMPH);\
                                                        (__HANDLE__)->Instance->CR |= (uint32_t)(__PHASE__);\
                                                       }while(0)
#endif /* End AES or CRYP*/


/**
  * @}
  */ 
                                                         
/* Private struct -------------------------------------------------------------*/
>>>>>>> 49e424905b5922b07aa7166ec7a0eeb90adf58a8
/* Private variables ---------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
/** @addtogroup CRYP_Private_Functions_prototypes
  * @{
  */  
<<<<<<< HEAD
static void CRYP_SetInitVector(CRYP_HandleTypeDef *hcryp, uint8_t *InitVector, uint32_t IVSize);
static void CRYP_SetKey(CRYP_HandleTypeDef *hcryp, uint8_t *Key, uint32_t KeySize);
static HAL_StatusTypeDef CRYP_ProcessData(CRYP_HandleTypeDef *hcryp, uint8_t* Input, uint16_t Ilength, uint8_t* Output, uint32_t Timeout);
static HAL_StatusTypeDef CRYP_ProcessData2Words(CRYP_HandleTypeDef *hcryp, uint8_t* Input, uint16_t Ilength, uint8_t* Output, uint32_t Timeout);
static void CRYP_DMAInCplt(DMA_HandleTypeDef *hdma);
static void CRYP_DMAOutCplt(DMA_HandleTypeDef *hdma);
static void CRYP_DMAError(DMA_HandleTypeDef *hdma);
static void CRYP_SetDMAConfig(CRYP_HandleTypeDef *hcryp, uint32_t inputaddr, uint16_t Size, uint32_t outputaddr);
static void CRYP_SetTDESECBMode(CRYP_HandleTypeDef *hcryp, uint32_t Direction);
static void CRYP_SetTDESCBCMode(CRYP_HandleTypeDef *hcryp, uint32_t Direction);
static void CRYP_SetDESECBMode(CRYP_HandleTypeDef *hcryp, uint32_t Direction);
static void CRYP_SetDESCBCMode(CRYP_HandleTypeDef *hcryp, uint32_t Direction);
/**
  * @}
  */ 
/* Private functions ---------------------------------------------------------*/

/** @addtogroup CRYP_Private_Functions
  * @{
  */

/**
  * @brief  DMA CRYP Input Data process complete callback.
  * @param  hdma DMA handle
  * @retval None
  */
static void CRYP_DMAInCplt(DMA_HandleTypeDef *hdma)  
{
  CRYP_HandleTypeDef* hcryp = (CRYP_HandleTypeDef*)((DMA_HandleTypeDef*)hdma)->Parent;
  
  /* Disable the DMA transfer for input FIFO request by resetting the DIEN bit
     in the DMACR register */
  hcryp->Instance->DMACR &= (uint32_t)(~CRYP_DMACR_DIEN);
  
  /* Call input data transfer complete callback */
  HAL_CRYP_InCpltCallback(hcryp);
}

/**
  * @brief  DMA CRYP Output Data process complete callback.
  * @param  hdma DMA handle
  * @retval None
  */
static void CRYP_DMAOutCplt(DMA_HandleTypeDef *hdma)
{
  CRYP_HandleTypeDef* hcryp = (CRYP_HandleTypeDef*)((DMA_HandleTypeDef*)hdma)->Parent;
  
  /* Disable the DMA transfer for output FIFO request by resetting the DOEN bit
     in the DMACR register */
  hcryp->Instance->DMACR &= (uint32_t)(~CRYP_DMACR_DOEN);
  
  /* Disable CRYP */
  __HAL_CRYP_DISABLE(hcryp);
  
  /* Change the CRYP state to ready */
  hcryp->State = HAL_CRYP_STATE_READY;
  
  /* Call output data transfer complete callback */
  HAL_CRYP_OutCpltCallback(hcryp);
}

/**
  * @brief  DMA CRYP communication error callback. 
  * @param  hdma DMA handle
  * @retval None
  */
static void CRYP_DMAError(DMA_HandleTypeDef *hdma)
{
  CRYP_HandleTypeDef* hcryp = (CRYP_HandleTypeDef*)((DMA_HandleTypeDef*)hdma)->Parent;
  hcryp->State= HAL_CRYP_STATE_READY;
  HAL_CRYP_ErrorCallback(hcryp);
}

/**
  * @brief  Writes the Key in Key registers. 
  * @param  hcryp pointer to a CRYP_HandleTypeDef structure that contains
  *         the configuration information for CRYP module
  * @param  Key Pointer to Key buffer
  * @param  KeySize Size of Key
  * @retval None
  */
static void CRYP_SetKey(CRYP_HandleTypeDef *hcryp, uint8_t *Key, uint32_t KeySize)
{
  uint32_t keyaddr = (uint32_t)Key;
  
  switch(KeySize)
  {
  case CRYP_KEYSIZE_256B:
    /* Key Initialisation */
    hcryp->Instance->K0LR = __REV(*(uint32_t*)(keyaddr));
    keyaddr+=4;
    hcryp->Instance->K0RR = __REV(*(uint32_t*)(keyaddr));
    keyaddr+=4;
    hcryp->Instance->K1LR = __REV(*(uint32_t*)(keyaddr));
    keyaddr+=4;
    hcryp->Instance->K1RR = __REV(*(uint32_t*)(keyaddr));
    keyaddr+=4;
    hcryp->Instance->K2LR = __REV(*(uint32_t*)(keyaddr));
    keyaddr+=4;
    hcryp->Instance->K2RR = __REV(*(uint32_t*)(keyaddr));
    keyaddr+=4;
    hcryp->Instance->K3LR = __REV(*(uint32_t*)(keyaddr));
    keyaddr+=4;
    hcryp->Instance->K3RR = __REV(*(uint32_t*)(keyaddr));
    break;
  case CRYP_KEYSIZE_192B:
    hcryp->Instance->K1LR = __REV(*(uint32_t*)(keyaddr));
    keyaddr+=4;
    hcryp->Instance->K1RR = __REV(*(uint32_t*)(keyaddr));
    keyaddr+=4;
    hcryp->Instance->K2LR = __REV(*(uint32_t*)(keyaddr));
    keyaddr+=4;
    hcryp->Instance->K2RR = __REV(*(uint32_t*)(keyaddr));
    keyaddr+=4;
    hcryp->Instance->K3LR = __REV(*(uint32_t*)(keyaddr));
    keyaddr+=4;
    hcryp->Instance->K3RR = __REV(*(uint32_t*)(keyaddr));
    break;
  case CRYP_KEYSIZE_128B:       
    hcryp->Instance->K2LR = __REV(*(uint32_t*)(keyaddr));
    keyaddr+=4;
    hcryp->Instance->K2RR = __REV(*(uint32_t*)(keyaddr));
    keyaddr+=4;
    hcryp->Instance->K3LR = __REV(*(uint32_t*)(keyaddr));
    keyaddr+=4;
    hcryp->Instance->K3RR = __REV(*(uint32_t*)(keyaddr));
    break;
  default:
    break;
  }
}

/**
  * @brief  Writes the InitVector/InitCounter in IV registers. 
  * @param  hcryp pointer to a CRYP_HandleTypeDef structure that contains
  *         the configuration information for CRYP module
  * @param  InitVector Pointer to InitVector/InitCounter buffer
  * @param  IVSize Size of the InitVector/InitCounter
  * @retval None
  */
static void CRYP_SetInitVector(CRYP_HandleTypeDef *hcryp, uint8_t *InitVector, uint32_t IVSize)
{
  uint32_t ivaddr = (uint32_t)InitVector;
  
  switch(IVSize)
  {
  case CRYP_KEYSIZE_128B:
    hcryp->Instance->IV0LR = __REV(*(uint32_t*)(ivaddr));
    ivaddr+=4;
    hcryp->Instance->IV0RR = __REV(*(uint32_t*)(ivaddr));
    ivaddr+=4;
    hcryp->Instance->IV1LR = __REV(*(uint32_t*)(ivaddr));
    ivaddr+=4;
    hcryp->Instance->IV1RR = __REV(*(uint32_t*)(ivaddr));
    break;
    /* Whatever key size 192 or 256, Init vector is written in IV0LR and IV0RR */
  case CRYP_KEYSIZE_192B:
    hcryp->Instance->IV0LR = __REV(*(uint32_t*)(ivaddr));
    ivaddr+=4;
    hcryp->Instance->IV0RR = __REV(*(uint32_t*)(ivaddr));
    break;
  case CRYP_KEYSIZE_256B:
    hcryp->Instance->IV0LR = __REV(*(uint32_t*)(ivaddr));
    ivaddr+=4;
    hcryp->Instance->IV0RR = __REV(*(uint32_t*)(ivaddr));
    break;
  default:
    break;
  }
}

/**
  * @brief  Process Data: Writes Input data in polling mode and read the output data
  * @param  hcryp pointer to a CRYP_HandleTypeDef structure that contains
  *         the configuration information for CRYP module
  * @param  Input Pointer to the Input buffer
  * @param  Ilength Length of the Input buffer, must be a multiple of 16.
  * @param  Output Pointer to the returned buffer
  * @param  Timeout Timeout value
  * @retval None
  */
static HAL_StatusTypeDef CRYP_ProcessData(CRYP_HandleTypeDef *hcryp, uint8_t* Input, uint16_t Ilength, uint8_t* Output, uint32_t Timeout)
{
  uint32_t tickstart = 0;
  
  uint32_t i = 0;
  uint32_t inputaddr  = (uint32_t)Input;
  uint32_t outputaddr = (uint32_t)Output;
  
  for(i=0; (i < Ilength); i+=16)
  {
    /* Write the Input block in the IN FIFO */
    hcryp->Instance->DR = *(uint32_t*)(inputaddr);
    inputaddr+=4;
    hcryp->Instance->DR = *(uint32_t*)(inputaddr);
    inputaddr+=4;
    hcryp->Instance->DR  = *(uint32_t*)(inputaddr);
    inputaddr+=4;
    hcryp->Instance->DR = *(uint32_t*)(inputaddr);
    inputaddr+=4;
    
    /* Get tick */
    tickstart = HAL_GetTick();

    while(HAL_IS_BIT_CLR(hcryp->Instance->SR, CRYP_FLAG_OFNE))
    {    
      /* Check for the Timeout */
      if(Timeout != HAL_MAX_DELAY)
      {
        if((Timeout == 0)||((HAL_GetTick() - tickstart ) > Timeout))
        {
          /* Change state */
          hcryp->State = HAL_CRYP_STATE_TIMEOUT;
          
          /* Process Unlocked */
          __HAL_UNLOCK(hcryp);
        
          return HAL_TIMEOUT;
        }
      }
    }
    /* Read the Output block from the Output FIFO */
    *(uint32_t*)(outputaddr) = hcryp->Instance->DOUT;
    outputaddr+=4;
    *(uint32_t*)(outputaddr) = hcryp->Instance->DOUT;
    outputaddr+=4;
    *(uint32_t*)(outputaddr) = hcryp->Instance->DOUT;
    outputaddr+=4;
    *(uint32_t*)(outputaddr) = hcryp->Instance->DOUT;
    outputaddr+=4;
  }
=======

static void CRYP_SetDMAConfig(CRYP_HandleTypeDef *hcryp, uint32_t inputaddr, uint16_t Size, uint32_t outputaddr);
static void CRYP_DMAInCplt(DMA_HandleTypeDef *hdma);
static void CRYP_DMAOutCplt(DMA_HandleTypeDef *hdma);
static void CRYP_DMAError(DMA_HandleTypeDef *hdma);
static void CRYP_SetKey(CRYP_HandleTypeDef *hcryp, uint32_t KeySize);
static void CRYP_AES_IT(CRYP_HandleTypeDef *hcryp);

static HAL_StatusTypeDef CRYP_GCMCCM_SetHeaderPhase(CRYP_HandleTypeDef *hcryp, uint32_t Timeout);
static void CRYP_GCMCCM_SetPayloadPhase_IT(CRYP_HandleTypeDef *hcryp);
static void CRYP_GCMCCM_SetHeaderPhase_IT(CRYP_HandleTypeDef *hcryp);
static HAL_StatusTypeDef CRYP_GCMCCM_SetHeaderPhase_DMA(CRYP_HandleTypeDef *hcryp);
static void CRYP_Workaround(CRYP_HandleTypeDef *hcryp, uint32_t Timeout);
static HAL_StatusTypeDef CRYP_AESGCM_Process_DMA(CRYP_HandleTypeDef *hcryp);
static HAL_StatusTypeDef CRYP_AESGCM_Process_IT (CRYP_HandleTypeDef *hcryp);
static HAL_StatusTypeDef CRYP_AESGCM_Process(CRYP_HandleTypeDef *hcryp, uint32_t Timeout);
static HAL_StatusTypeDef CRYP_AESCCM_Process(CRYP_HandleTypeDef *hcryp, uint32_t Timeout);
static HAL_StatusTypeDef CRYP_AESCCM_Process_IT(CRYP_HandleTypeDef *hcryp);
static HAL_StatusTypeDef CRYP_AESCCM_Process_DMA(CRYP_HandleTypeDef *hcryp);

static void CRYP_AES_ProcessData(CRYP_HandleTypeDef *hcrypt, uint32_t Timeout);
static HAL_StatusTypeDef CRYP_AES_Encrypt(CRYP_HandleTypeDef *hcryp, uint32_t Timeout);
static HAL_StatusTypeDef CRYP_AES_Decrypt(CRYP_HandleTypeDef *hcryp, uint32_t Timeout);
static HAL_StatusTypeDef CRYP_AES_Decrypt_IT(CRYP_HandleTypeDef *hcryp);
static HAL_StatusTypeDef CRYP_AES_Encrypt_IT(CRYP_HandleTypeDef *hcryp);
static HAL_StatusTypeDef CRYP_AES_Decrypt_DMA(CRYP_HandleTypeDef *hcryp);
#if defined (CRYP)
static void CRYP_TDES_IT(CRYP_HandleTypeDef *hcryp);

static HAL_StatusTypeDef CRYP_WaitOnIFEMFlag(CRYP_HandleTypeDef *hcryp, uint32_t Timeout);

static HAL_StatusTypeDef CRYP_WaitOnBUSYFlag(CRYP_HandleTypeDef *hcryp, uint32_t Timeout);
static HAL_StatusTypeDef CRYP_WaitOnOFNEFlag(CRYP_HandleTypeDef *hcryp, uint32_t Timeout);
static HAL_StatusTypeDef CRYP_TDES_Process(CRYP_HandleTypeDef *hcryp, uint32_t Timeout);
#else /*AES*/
static HAL_StatusTypeDef CRYP_WaitOnCCFlag(CRYP_HandleTypeDef *hcryp, uint32_t Timeout);
#endif /* End CRYP or AES */

/**
  * @}
  */ 

/* Exported functions ---------------------------------------------------------*/

/** @defgroup CRYP_Exported_Functions CRYP Exported Functions
  * @{
  */

  
/** @defgroup CRYP_Exported_Functions_Group1 Initialization and de-initialization functions 
 *  @brief    Initialization and Configuration functions. 
 *
@verbatim    
  ========================================================================================
     ##### Initialization, de-initialization and Set and Get configuration functions #####
  ========================================================================================
    [..]  This section provides functions allowing to:
      (+) Initialize the CRYP  
      (+) DeInitialize the CRYP  
      (+) Initialize the CRYP MSP
      (+) DeInitialize the CRYP MSP 
      (+) configure CRYP (HAL_CRYP_SetConfig) with the specified parameters in the CRYP_ConfigTypeDef
          Parameters which are configured in This section are :
          (+) Key size 
          (+) Data Type : 32,16, 8 or 1bit
          (+) AlgoMode : 
              - for CRYP1 IP : 
                 ECB and CBC in DES/TDES Standard 
                 ECB,CBC,CTR,GCM/GMAC and CCM in AES Standard. 
              - for TinyAES2 IP, only ECB,CBC,CTR,GCM/GMAC and CCM in AES Standard are supported.
      (+) Get CRYP configuration (HAL_CRYP_GetConfig) from the specified parameters in the CRYP_HandleTypeDef


@endverbatim
  * @{
  */


/**
  * @brief  Initializes the CRYP according to the specified
  *         parameters in the CRYP_ConfigTypeDef and creates the associated handle.
  * @param  hcryp: pointer to a CRYP_HandleTypeDef structure that contains
  *         the configuration information for CRYP module
  * @retval HAL status
  */
HAL_StatusTypeDef HAL_CRYP_Init(CRYP_HandleTypeDef *hcryp)
{ 
  /* Check the CRYP handle allocation */
  if(hcryp == NULL)
  {
    return HAL_ERROR;
  } 
  
  /* Check parameters */
  assert_param(IS_CRYP_KEYSIZE(hcryp->Init.KeySize));
  assert_param(IS_CRYP_DATATYPE(hcryp->Init.DataType));
  assert_param(IS_CRYP_ALGORITHM(hcryp->Init.Algorithm));  
  
  #if (USE_HAL_CRYP_REGISTER_CALLBACKS == 1)
  if(hcryp->State == HAL_CRYP_STATE_RESET)
  {
    /* Allocate lock resource and initialize it */
    hcryp->Lock = HAL_UNLOCKED;
    
    hcryp->InCpltCallback  = HAL_CRYP_InCpltCallback;  /* Legacy weak InCpltCallback   */
    hcryp->OutCpltCallback = HAL_CRYP_OutCpltCallback; /* Legacy weak OutCpltCallback  */
    hcryp->ErrorCallback   = HAL_CRYP_ErrorCallback;   /* Legacy weak ErrorCallback    */
    
    if(hcryp->MspInitCallback == NULL)
    {
      hcryp->MspInitCallback = HAL_CRYP_MspInit; /* Legacy weak MspInit  */
    }
    
    /* Init the low level hardware */
    hcryp->MspInitCallback(hcryp);    
  }
#else
  if(hcryp->State == HAL_CRYP_STATE_RESET)
  {
    /* Allocate lock resource and initialize it */
    hcryp->Lock = HAL_UNLOCKED;
    
    /* Init the low level hardware */
    HAL_CRYP_MspInit(hcryp);
  }
 #endif /* (USE_HAL_CRYP_REGISTER_CALLBACKS) */
  
  /* Set the key size(This bit field is don’t care in the DES or TDES modes) data type and Algorithm */
#if defined (CRYP)
  
  MODIFY_REG(hcryp->Instance->CR, CRYP_CR_DATATYPE|CRYP_CR_KEYSIZE|CRYP_CR_ALGOMODE, hcryp->Init.DataType | hcryp->Init.KeySize | hcryp->Init.Algorithm);
  
#else /*AES*/
  
  MODIFY_REG(hcryp->Instance->CR, AES_CR_DATATYPE|AES_CR_KEYSIZE|AES_CR_CHMOD, hcryp->Init.DataType | hcryp->Init.KeySize | hcryp->Init.Algorithm);
  
#endif  /* End AES or CRYP*/
  
  /* Reset Error Code field */
  hcryp->ErrorCode = HAL_CRYP_ERROR_NONE; 
  
  /* Change the CRYP state */
  hcryp->State = HAL_CRYP_STATE_READY;  
  
  /* Set the default CRYP phase */
  hcryp->Phase = CRYP_PHASE_READY;
  
>>>>>>> 49e424905b5922b07aa7166ec7a0eeb90adf58a8
  /* Return function status */
  return HAL_OK;
}

/**
<<<<<<< HEAD
  * @brief  Process Data: Write Input data in polling mode. 
  * @param  hcryp pointer to a CRYP_HandleTypeDef structure that contains
  *         the configuration information for CRYP module
  * @param  Input Pointer to the Input buffer
  * @param  Ilength Length of the Input buffer, must be a multiple of 8
  * @param  Output Pointer to the returned buffer
  * @param  Timeout Specify Timeout value  
  * @retval None
  */
static HAL_StatusTypeDef CRYP_ProcessData2Words(CRYP_HandleTypeDef *hcryp, uint8_t* Input, uint16_t Ilength, uint8_t* Output, uint32_t Timeout)
{
  uint32_t tickstart = 0;   
  
  uint32_t i = 0;
  uint32_t inputaddr  = (uint32_t)Input;
  uint32_t outputaddr = (uint32_t)Output;
  
  for(i=0; (i < Ilength); i+=8)
  {
    /* Write the Input block in the IN FIFO */
    hcryp->Instance->DR  = *(uint32_t*)(inputaddr);
    inputaddr+=4;
    hcryp->Instance->DR = *(uint32_t*)(inputaddr);
    inputaddr+=4;
    
    /* Get tick */
    tickstart = HAL_GetTick();
    
    while(HAL_IS_BIT_CLR(hcryp->Instance->SR, CRYP_FLAG_OFNE))
    {
      /* Check for the Timeout */
      if(Timeout != HAL_MAX_DELAY)
      {
        if((Timeout == 0)||((HAL_GetTick() - tickstart ) > Timeout))
        {
          /* Change state */
          hcryp->State = HAL_CRYP_STATE_TIMEOUT;
          
          /* Process Unlocked */          
          __HAL_UNLOCK(hcryp);
          
          return HAL_TIMEOUT;
        }
      }
    }
    /* Read the Output block from the Output FIFO */
    *(uint32_t*)(outputaddr) = hcryp->Instance->DOUT;
    outputaddr+=4;
    *(uint32_t*)(outputaddr) = hcryp->Instance->DOUT;
    outputaddr+=4;
  }
  /* Return function status */
  return HAL_OK;
}

/**
  * @brief  Set the DMA configuration and start the DMA transfer
  * @param  hcryp pointer to a CRYP_HandleTypeDef structure that contains
  *         the configuration information for CRYP module
  * @param  inputaddr address of the Input buffer
  * @param  Size Size of the Input buffer, must be a multiple of 16.
  * @param  outputaddr address of the Output buffer
  * @retval None
  */
static void CRYP_SetDMAConfig(CRYP_HandleTypeDef *hcryp, uint32_t inputaddr, uint16_t Size, uint32_t outputaddr)
{
  /* Set the CRYP DMA transfer complete callback */
  hcryp->hdmain->XferCpltCallback = CRYP_DMAInCplt;
  /* Set the DMA error callback */
  hcryp->hdmain->XferErrorCallback = CRYP_DMAError;
  
  /* Set the CRYP DMA transfer complete callback */
  hcryp->hdmaout->XferCpltCallback = CRYP_DMAOutCplt;
  /* Set the DMA error callback */
  hcryp->hdmaout->XferErrorCallback = CRYP_DMAError;
  
  /* Enable CRYP */
  __HAL_CRYP_ENABLE(hcryp);
  
  /* Enable the DMA In DMA Stream */
  HAL_DMA_Start_IT(hcryp->hdmain, inputaddr, (uint32_t)&hcryp->Instance->DR, Size/4);

  /* Enable In DMA request */
  hcryp->Instance->DMACR = (CRYP_DMACR_DIEN);
  
  /* Enable the DMA Out DMA Stream */
  HAL_DMA_Start_IT(hcryp->hdmaout, (uint32_t)&hcryp->Instance->DOUT, outputaddr, Size/4);
  
  /* Enable Out DMA request */
  hcryp->Instance->DMACR |= CRYP_DMACR_DOEN;
 
}

/**
  * @brief  Sets the CRYP peripheral in DES ECB mode.
  * @param  hcryp pointer to a CRYP_HandleTypeDef structure that contains
  *         the configuration information for CRYP module
  * @param  Direction Encryption or decryption
  * @retval None
  */
static void CRYP_SetDESECBMode(CRYP_HandleTypeDef *hcryp, uint32_t Direction)
{
  /* Check if initialization phase has already been performed */
  if(hcryp->Phase == HAL_CRYP_PHASE_READY)
  {
    /* Set the CRYP peripheral in AES ECB mode */
    __HAL_CRYP_SET_MODE(hcryp, CRYP_CR_ALGOMODE_DES_ECB | Direction);
    
    /* Set the key */
    hcryp->Instance->K1LR = __REV(*(uint32_t*)(hcryp->Init.pKey));
    hcryp->Instance->K1RR = __REV(*(uint32_t*)(hcryp->Init.pKey+4));
    
    /* Flush FIFO */
    __HAL_CRYP_FIFO_FLUSH(hcryp);
    
    /* Set the phase */
    hcryp->Phase = HAL_CRYP_PHASE_PROCESS;
  }
}

/**
  * @brief  Sets the CRYP peripheral in DES CBC mode.
  * @param  hcryp pointer to a CRYP_HandleTypeDef structure that contains
  *         the configuration information for CRYP module
  * @param  Direction Encryption or decryption
  * @retval None
  */
static void CRYP_SetDESCBCMode(CRYP_HandleTypeDef *hcryp, uint32_t Direction)
{
  /* Check if initialization phase has already been performed */
  if(hcryp->Phase == HAL_CRYP_PHASE_READY)
  {
    /* Set the CRYP peripheral in AES ECB mode */
    __HAL_CRYP_SET_MODE(hcryp, CRYP_CR_ALGOMODE_DES_CBC | Direction);
    
    /* Set the key */
    hcryp->Instance->K1LR = __REV(*(uint32_t*)(hcryp->Init.pKey));
    hcryp->Instance->K1RR = __REV(*(uint32_t*)(hcryp->Init.pKey+4));
    
    /* Set the Initialization Vector */
    CRYP_SetInitVector(hcryp, hcryp->Init.pInitVect, CRYP_KEYSIZE_256B);
    
    /* Flush FIFO */
    __HAL_CRYP_FIFO_FLUSH(hcryp);
    
    /* Set the phase */
    hcryp->Phase = HAL_CRYP_PHASE_PROCESS;
  }
}

/**
  * @brief  Sets the CRYP peripheral in TDES ECB mode.
  * @param  hcryp pointer to a CRYP_HandleTypeDef structure that contains
  *         the configuration information for CRYP module
  * @param  Direction Encryption or decryption
  * @retval None
  */
static void CRYP_SetTDESECBMode(CRYP_HandleTypeDef *hcryp, uint32_t Direction)
{
  /* Check if initialization phase has already been performed */
  if(hcryp->Phase == HAL_CRYP_PHASE_READY)
  {
    /* Set the CRYP peripheral in AES ECB mode */
    __HAL_CRYP_SET_MODE(hcryp, CRYP_CR_ALGOMODE_TDES_ECB | Direction);
    
    /* Set the key */
    CRYP_SetKey(hcryp, hcryp->Init.pKey, CRYP_KEYSIZE_192B);
    
    /* Flush FIFO */
    __HAL_CRYP_FIFO_FLUSH(hcryp);
    
    /* Set the phase */
    hcryp->Phase = HAL_CRYP_PHASE_PROCESS;
  }
}

/**
  * @brief  Sets the CRYP peripheral in TDES CBC mode
  * @param  hcryp pointer to a CRYP_HandleTypeDef structure that contains
  *         the configuration information for CRYP module
  * @param  Direction Encryption or decryption
  * @retval None
  */
static void CRYP_SetTDESCBCMode(CRYP_HandleTypeDef *hcryp, uint32_t Direction)
{
  /* Check if initialization phase has already been performed */
  if(hcryp->Phase == HAL_CRYP_PHASE_READY)
  {
    /* Set the CRYP peripheral in AES CBC mode */
    __HAL_CRYP_SET_MODE(hcryp, CRYP_CR_ALGOMODE_TDES_CBC | Direction);
    
    /* Set the key */
    CRYP_SetKey(hcryp, hcryp->Init.pKey, CRYP_KEYSIZE_192B);
    
    /* Set the Initialization Vector */
    CRYP_SetInitVector(hcryp, hcryp->Init.pInitVect, CRYP_KEYSIZE_256B);
    
    /* Flush FIFO */
    __HAL_CRYP_FIFO_FLUSH(hcryp);
    
    /* Set the phase */
    hcryp->Phase = HAL_CRYP_PHASE_PROCESS;
=======
  * @brief  De-Initializes the CRYP peripheral. 
  * @param  hcryp: pointer to a CRYP_HandleTypeDef structure that contains
  *         the configuration information for CRYP module
  * @retval HAL status
*/
HAL_StatusTypeDef HAL_CRYP_DeInit(CRYP_HandleTypeDef *hcryp)
{
  /* Check the CRYP handle allocation */
  if(hcryp == NULL)
  {
    return HAL_ERROR;
  }
  
  /* Set the default CRYP phase */
  hcryp->Phase = CRYP_PHASE_READY;
  
  /* Reset CrypInCount and CrypOutCount */
  hcryp->CrypInCount = 0;
  hcryp->CrypOutCount = 0;
  hcryp->CrypHeaderCount =0; 
  
  /* Disable the CRYP peripheral clock */
  __HAL_CRYP_DISABLE(hcryp);
  
#if (USE_HAL_CRYP_REGISTER_CALLBACKS == 1)
  
  if(hcryp->MspDeInitCallback == NULL)
  {
    hcryp->MspDeInitCallback = HAL_CRYP_MspDeInit; /* Legacy weak MspDeInit  */
  }
  /* DeInit the low level hardware */
  hcryp->MspDeInitCallback(hcryp);
  
#else
  
  /* DeInit the low level hardware: CLOCK, NVIC.*/
  HAL_CRYP_MspDeInit(hcryp);
  
#endif /* USE_HAL_CRYP_REGISTER_CALLBACKS */
  
  /* Change the CRYP state */
  hcryp->State = HAL_CRYP_STATE_RESET;
  
  /* Release Lock */
  __HAL_UNLOCK(hcryp);
  
  /* Return function status */
  return HAL_OK;
}
    
/**
  * @brief  Configure the CRYP according to the specified
  *         parameters in the CRYP_ConfigTypeDef 
  * @param  hcryp: pointer to a CRYP_HandleTypeDef structure
  * @param  pConf: pointer to a CRYP_ConfigTypeDef structure that contains
  *         the configuration information for CRYP module
  * @retval HAL status
  */
HAL_StatusTypeDef HAL_CRYP_SetConfig(CRYP_HandleTypeDef *hcryp, CRYP_ConfigTypeDef *pConf )
{ 
  /* Check the CRYP handle allocation */
  if((hcryp == NULL)|| (pConf == NULL) )
  {
    return HAL_ERROR;
  }
  
  /* Check parameters */
  assert_param(IS_CRYP_KEYSIZE(pConf->KeySize));
  assert_param(IS_CRYP_DATATYPE(pConf->DataType));
  assert_param(IS_CRYP_ALGORITHM(pConf->Algorithm));
  
  if(hcryp->State == HAL_CRYP_STATE_READY) 
  {  
    /* Change the CRYP state */
    hcryp->State = HAL_CRYP_STATE_BUSY;
    
    /* Process locked */
    __HAL_LOCK(hcryp);     
    
    /* Set  CRYP parameters  */    
    hcryp->Init.DataType   = pConf->DataType;
    hcryp->Init.pKey       = pConf->pKey;
    hcryp->Init.Algorithm  = pConf->Algorithm;
    hcryp->Init.KeySize    = pConf->KeySize;
    hcryp->Init.pInitVect  = pConf->pInitVect;
    hcryp->Init.Header     = pConf->Header;
    hcryp->Init.HeaderSize = pConf->HeaderSize;
    hcryp->Init.B0         = pConf->B0;
    hcryp->Init.DataWidthUnit = pConf->DataWidthUnit;
    
    /* Set the key size(This bit field is don’t care in the DES or TDES modes) data type, AlgoMode and operating mode*/    
#if defined (CRYP) 
    
    MODIFY_REG(hcryp->Instance->CR, CRYP_CR_DATATYPE|CRYP_CR_KEYSIZE|CRYP_CR_ALGOMODE, hcryp->Init.DataType | hcryp->Init.KeySize | hcryp->Init.Algorithm);
    
#else /*AES*/
    MODIFY_REG(hcryp->Instance->CR, AES_CR_DATATYPE|AES_CR_KEYSIZE|AES_CR_CHMOD, hcryp->Init.DataType | hcryp->Init.KeySize | hcryp->Init.Algorithm);
    
    /*clear error flags*/
    __HAL_CRYP_CLEAR_FLAG(hcryp,CRYP_ERR_CLEAR);
    
#endif  /* End AES or CRYP */ 
    
    /* Process Unlocked */
    __HAL_UNLOCK(hcryp);
    
    /* Reset Error Code field */
    hcryp->ErrorCode = HAL_CRYP_ERROR_NONE; 
    
    /* Change the CRYP state */
    hcryp->State = HAL_CRYP_STATE_READY;  
    
    /* Set the default CRYP phase */
    hcryp->Phase = CRYP_PHASE_READY;
    
    /* Return function status */
    return HAL_OK;
  }
  else
  {
    /* Process Unlocked */
    __HAL_UNLOCK(hcryp);   
    
    /* Busy error code field */
    hcryp->ErrorCode |= HAL_CRYP_ERROR_BUSY; 
    return HAL_ERROR;
>>>>>>> 49e424905b5922b07aa7166ec7a0eeb90adf58a8
  }
}

/**
<<<<<<< HEAD
  * @}
  */ 
  
 /* Exported functions --------------------------------------------------------*/
/** @addtogroup CRYP_Exported_Functions
  * @{
  */ 
  
/** @defgroup CRYP_Exported_Functions_Group1 Initialization and de-initialization functions 
 *  @brief    Initialization and Configuration functions. 
 *
@verbatim    
  ==============================================================================
              ##### Initialization and de-initialization functions #####
  ==============================================================================
    [..]  This section provides functions allowing to:
      (+) Initialize the CRYP according to the specified parameters 
          in the CRYP_InitTypeDef and creates the associated handle
      (+) DeInitialize the CRYP peripheral
      (+) Initialize the CRYP MSP
      (+) DeInitialize CRYP MSP 
 
@endverbatim
  * @{
  */

/**
  * @brief  Initializes the CRYP according to the specified
  *         parameters in the CRYP_InitTypeDef and creates the associated handle.
  * @param  hcryp pointer to a CRYP_HandleTypeDef structure that contains
  *         the configuration information for CRYP module
  * @retval HAL status
  */
HAL_StatusTypeDef HAL_CRYP_Init(CRYP_HandleTypeDef *hcryp)
{ 
  /* Check the CRYP handle allocation */
  if(hcryp == NULL)
  {
    return HAL_ERROR;
  }

  /* Check the parameters */
  assert_param(IS_CRYP_KEYSIZE(hcryp->Init.KeySize));
  assert_param(IS_CRYP_DATATYPE(hcryp->Init.DataType));
    
  if(hcryp->State == HAL_CRYP_STATE_RESET)
  {
    /* Allocate lock resource and initialize it */
    hcryp->Lock = HAL_UNLOCKED;
    /* Init the low level hardware */
    HAL_CRYP_MspInit(hcryp);
  }
  
  /* Change the CRYP state */
  hcryp->State = HAL_CRYP_STATE_BUSY;
  
  /* Set the key size and data type*/
  CRYP->CR = (uint32_t) (hcryp->Init.KeySize | hcryp->Init.DataType);
  
  /* Reset CrypInCount and CrypOutCount */
  hcryp->CrypInCount = 0;
  hcryp->CrypOutCount = 0;
  
  /* Change the CRYP state */
  hcryp->State = HAL_CRYP_STATE_READY;
  
  /* Set the default CRYP phase */
  hcryp->Phase = HAL_CRYP_PHASE_READY;
  
  /* Return function status */
  return HAL_OK;
}

/**
  * @brief  DeInitializes the CRYP peripheral. 
  * @param  hcryp pointer to a CRYP_HandleTypeDef structure that contains
  *         the configuration information for CRYP module
  * @retval HAL status
  */
HAL_StatusTypeDef HAL_CRYP_DeInit(CRYP_HandleTypeDef *hcryp)
{
  /* Check the CRYP handle allocation */
  if(hcryp == NULL)
  {
    return HAL_ERROR;
  }
  
  /* Change the CRYP state */
  hcryp->State = HAL_CRYP_STATE_BUSY;
  
  /* Set the default CRYP phase */
  hcryp->Phase = HAL_CRYP_PHASE_READY;
  
  /* Reset CrypInCount and CrypOutCount */
  hcryp->CrypInCount = 0;
  hcryp->CrypOutCount = 0;
  
  /* Disable the CRYP Peripheral Clock */
  __HAL_CRYP_DISABLE(hcryp);
  
  /* DeInit the low level hardware: CLOCK, NVIC.*/
  HAL_CRYP_MspDeInit(hcryp);
  
  /* Change the CRYP state */
  hcryp->State = HAL_CRYP_STATE_RESET;

  /* Release Lock */
  __HAL_UNLOCK(hcryp);

  /* Return function status */
  return HAL_OK;
}

/**
  * @brief  Initializes the CRYP MSP.
  * @param  hcryp pointer to a CRYP_HandleTypeDef structure that contains
=======
  * @brief  Get CRYP Configuration parameters in associated handle.
  * @param  pConf: pointer to a CRYP_ConfigTypeDef structure
  * @param  hcryp: pointer to a CRYP_HandleTypeDef structure that contains
  *         the configuration information for CRYP module
  * @retval HAL status
  */
HAL_StatusTypeDef HAL_CRYP_GetConfig(CRYP_HandleTypeDef *hcryp, CRYP_ConfigTypeDef *pConf )
{ 
  /* Check the CRYP handle allocation */
  if((hcryp == NULL)|| (pConf == NULL) )
  {
    return HAL_ERROR;
  }
  
  if(hcryp->State == HAL_CRYP_STATE_READY) 
  {  
    /* Change the CRYP state */
    hcryp->State = HAL_CRYP_STATE_BUSY;
    
    /* Process locked */
    __HAL_LOCK(hcryp);  
    
    /* Get  CRYP parameters  */      
    pConf->DataType        = hcryp->Init.DataType;
    pConf->pKey            = hcryp->Init.pKey;
    pConf->Algorithm       = hcryp->Init.Algorithm;
    pConf->KeySize         = hcryp->Init.KeySize ;
    pConf->pInitVect       = hcryp->Init.pInitVect;
    pConf->Header          = hcryp->Init.Header ;
    pConf->HeaderSize      = hcryp->Init.HeaderSize;
    pConf->B0              = hcryp->Init.B0;
    pConf->DataWidthUnit    = hcryp->Init.DataWidthUnit;
    
    /* Process Unlocked */
    __HAL_UNLOCK(hcryp);
    
    /* Change the CRYP state */
    hcryp->State = HAL_CRYP_STATE_READY;   
    
    /* Return function status */
    return HAL_OK;
  }
  else
  {
    /* Process Unlocked */
    __HAL_UNLOCK(hcryp);    
    
    /* Busy error code field */
    hcryp->ErrorCode |= HAL_CRYP_ERROR_BUSY; 
    return HAL_ERROR;
  }
}
/**
  * @brief  Initializes the CRYP MSP.
  * @param  hcryp: pointer to a CRYP_HandleTypeDef structure that contains
>>>>>>> 49e424905b5922b07aa7166ec7a0eeb90adf58a8
  *         the configuration information for CRYP module
  * @retval None
  */
__weak void HAL_CRYP_MspInit(CRYP_HandleTypeDef *hcryp)
{
  /* Prevent unused argument(s) compilation warning */
  UNUSED(hcryp);
 
  /* NOTE : This function Should not be modified, when the callback is needed,
            the HAL_CRYP_MspInit could be implemented in the user file
   */
}

/**
  * @brief  DeInitializes CRYP MSP.
<<<<<<< HEAD
  * @param  hcryp pointer to a CRYP_HandleTypeDef structure that contains
=======
  * @param  hcryp: pointer to a CRYP_HandleTypeDef structure that contains
>>>>>>> 49e424905b5922b07aa7166ec7a0eeb90adf58a8
  *         the configuration information for CRYP module
  * @retval None
  */
__weak void HAL_CRYP_MspDeInit(CRYP_HandleTypeDef *hcryp)
{
  /* Prevent unused argument(s) compilation warning */
  UNUSED(hcryp);
 
  /* NOTE : This function Should not be modified, when the callback is needed,
            the HAL_CRYP_MspDeInit could be implemented in the user file
   */
}

<<<<<<< HEAD
/**
  * @}
  */

/** @defgroup CRYP_Exported_Functions_Group2 AES processing functions 
 *  @brief   processing functions. 
 *
@verbatim   
  ==============================================================================
                      ##### AES processing functions #####
  ==============================================================================  
    [..]  This section provides functions allowing to:
      (+) Encrypt plaintext using AES-128/192/256 using chaining modes
      (+) Decrypt cyphertext using AES-128/192/256 using chaining modes
    [..]  Three processing functions are available:
      (+) Polling mode
      (+) Interrupt mode
      (+) DMA mode

@endverbatim
  * @{
  */

/**
  * @brief  Initializes the CRYP peripheral in AES ECB encryption mode
  *         then encrypt pPlainData. The cypher data are available in pCypherData
  * @param  hcryp pointer to a CRYP_HandleTypeDef structure that contains
  *         the configuration information for CRYP module
  * @param  pPlainData Pointer to the plaintext buffer
  * @param  Size Length of the plaintext buffer, must be a multiple of 16.
  * @param  pCypherData Pointer to the cyphertext buffer
  * @param  Timeout Specify Timeout value 
  * @retval HAL status
  */
HAL_StatusTypeDef HAL_CRYP_AESECB_Encrypt(CRYP_HandleTypeDef *hcryp, uint8_t *pPlainData, uint16_t Size, uint8_t *pCypherData, uint32_t Timeout)
{
  /* Process Locked */
  __HAL_LOCK(hcryp);
  
  /* Change the CRYP state */
  hcryp->State = HAL_CRYP_STATE_BUSY;
  
  /* Check if initialization phase has already been performed */
  if(hcryp->Phase == HAL_CRYP_PHASE_READY)
  {
    /* Set the key */
    CRYP_SetKey(hcryp, hcryp->Init.pKey, hcryp->Init.KeySize);
    
    /* Set the CRYP peripheral in AES ECB mode */
    __HAL_CRYP_SET_MODE(hcryp, CRYP_CR_ALGOMODE_AES_ECB);
    
    /* Flush FIFO */
    __HAL_CRYP_FIFO_FLUSH(hcryp);
    
    /* Enable CRYP */
    __HAL_CRYP_ENABLE(hcryp);
    
    /* Set the phase */
    hcryp->Phase = HAL_CRYP_PHASE_PROCESS;
  }
  
    /* Write Plain Data and Get Cypher Data */
    if(CRYP_ProcessData(hcryp, pPlainData, Size, pCypherData, Timeout) != HAL_OK)
    {
      return HAL_TIMEOUT;
    }
  
  /* Change the CRYP state */
  hcryp->State = HAL_CRYP_STATE_READY;
  
  /* Process Unlocked */
  __HAL_UNLOCK(hcryp);
  
  /* Return function status */
  return HAL_OK;
}

/**
  * @brief  Initializes the CRYP peripheral in AES CBC encryption mode
  *         then encrypt pPlainData. The cypher data are available in pCypherData
  * @param  hcryp pointer to a CRYP_HandleTypeDef structure that contains
  *         the configuration information for CRYP module
  * @param  pPlainData Pointer to the plaintext buffer
  * @param  Size Length of the plaintext buffer, must be a multiple of 16.
  * @param  pCypherData Pointer to the cyphertext buffer
  * @param  Timeout Specify Timeout value  
  * @retval HAL status
  */
HAL_StatusTypeDef HAL_CRYP_AESCBC_Encrypt(CRYP_HandleTypeDef *hcryp, uint8_t *pPlainData, uint16_t Size, uint8_t *pCypherData, uint32_t Timeout)
{
  /* Process Locked */
  __HAL_LOCK(hcryp);
  
  /* Change the CRYP state */
  hcryp->State = HAL_CRYP_STATE_BUSY;
  
  /* Check if initialization phase has already been performed */
  if(hcryp->Phase == HAL_CRYP_PHASE_READY)
  {
    /* Set the key */
    CRYP_SetKey(hcryp, hcryp->Init.pKey, hcryp->Init.KeySize);
    
    /* Set the CRYP peripheral in AES ECB mode */
    __HAL_CRYP_SET_MODE(hcryp, CRYP_CR_ALGOMODE_AES_CBC);
    
    /* Set the Initialization Vector */
    CRYP_SetInitVector(hcryp, hcryp->Init.pInitVect, CRYP_KEYSIZE_128B);
    
    /* Flush FIFO */
    __HAL_CRYP_FIFO_FLUSH(hcryp);
    
    /* Enable CRYP */
    __HAL_CRYP_ENABLE(hcryp);
    
    /* Set the phase */
    hcryp->Phase = HAL_CRYP_PHASE_PROCESS;
  }
  
    /* Write Plain Data and Get Cypher Data */
    if(CRYP_ProcessData(hcryp,pPlainData, Size, pCypherData, Timeout) != HAL_OK)
    {
      return HAL_TIMEOUT;
    }
  
  /* Change the CRYP state */
  hcryp->State = HAL_CRYP_STATE_READY;
  
  /* Process Unlocked */
  __HAL_UNLOCK(hcryp);
  
  /* Return function status */
  return HAL_OK;
}

/**
  * @brief  Initializes the CRYP peripheral in AES CTR encryption mode
  *         then encrypt pPlainData. The cypher data are available in pCypherData
  * @param  hcryp pointer to a CRYP_HandleTypeDef structure that contains
  *         the configuration information for CRYP module
  * @param  pPlainData Pointer to the plaintext buffer
  * @param  Size Length of the plaintext buffer, must be a multiple of 16.
  * @param  pCypherData Pointer to the cyphertext buffer
  * @param  Timeout Specify Timeout value  
  * @retval HAL status
  */
HAL_StatusTypeDef HAL_CRYP_AESCTR_Encrypt(CRYP_HandleTypeDef *hcryp, uint8_t *pPlainData, uint16_t Size, uint8_t *pCypherData, uint32_t Timeout)
{  
  /* Process Locked */
  __HAL_LOCK(hcryp);
  
  /* Change the CRYP state */
  hcryp->State = HAL_CRYP_STATE_BUSY;
  
  /* Check if initialization phase has already been performed */
  if(hcryp->Phase == HAL_CRYP_PHASE_READY)
  {
    /* Set the key */
    CRYP_SetKey(hcryp, hcryp->Init.pKey, hcryp->Init.KeySize);
    
    /* Set the CRYP peripheral in AES ECB mode */
    __HAL_CRYP_SET_MODE(hcryp, CRYP_CR_ALGOMODE_AES_CTR);
    
    /* Set the Initialization Vector */
    CRYP_SetInitVector(hcryp, hcryp->Init.pInitVect, CRYP_KEYSIZE_128B);
    
    /* Flush FIFO */
    __HAL_CRYP_FIFO_FLUSH(hcryp);
    
    /* Enable CRYP */
    __HAL_CRYP_ENABLE(hcryp);
    
    /* Set the phase */
    hcryp->Phase = HAL_CRYP_PHASE_PROCESS;
  }
  
    /* Write Plain Data and Get Cypher Data */
    if(CRYP_ProcessData(hcryp, pPlainData, Size, pCypherData, Timeout) != HAL_OK)
    {
      return HAL_TIMEOUT;
    }
  
  /* Change the CRYP state */
  hcryp->State = HAL_CRYP_STATE_READY;
  
  /* Process Unlocked */
  __HAL_UNLOCK(hcryp);
  
  /* Return function status */
  return HAL_OK;
}



/**
  * @brief  Initializes the CRYP peripheral in AES ECB decryption mode
  *         then decrypted pCypherData. The cypher data are available in pPlainData
  * @param  hcryp pointer to a CRYP_HandleTypeDef structure that contains
  *         the configuration information for CRYP module
  * @param  pCypherData Pointer to the cyphertext buffer
  * @param  Size Length of the plaintext buffer, must be a multiple of 16.
  * @param  pPlainData Pointer to the plaintext buffer
  * @param  Timeout Specify Timeout value  
  * @retval HAL status
  */
HAL_StatusTypeDef HAL_CRYP_AESECB_Decrypt(CRYP_HandleTypeDef *hcryp, uint8_t *pCypherData, uint16_t Size, uint8_t *pPlainData, uint32_t Timeout)
{
   uint32_t tickstart = 0;
  
  /* Process Locked */
  __HAL_LOCK(hcryp);
  
  /* Change the CRYP state */
  hcryp->State = HAL_CRYP_STATE_BUSY;
  
  /* Check if initialization phase has already been performed */
  if(hcryp->Phase == HAL_CRYP_PHASE_READY)
  {
    /* Set the key */
    CRYP_SetKey(hcryp, hcryp->Init.pKey, hcryp->Init.KeySize);
    
    /* Set the CRYP peripheral in AES Key mode */
    __HAL_CRYP_SET_MODE(hcryp, CRYP_CR_ALGOMODE_AES_KEY | CRYP_CR_ALGODIR);
    
    /* Enable CRYP */
    __HAL_CRYP_ENABLE(hcryp);
    
    /* Get tick */ 
    tickstart = HAL_GetTick();

    while(HAL_IS_BIT_SET(hcryp->Instance->SR, CRYP_FLAG_BUSY))
    {
      /* Check for the Timeout */
      if(Timeout != HAL_MAX_DELAY)
      {
        if((Timeout == 0)||((HAL_GetTick() - tickstart ) > Timeout))
        {
          /* Change state */
          hcryp->State = HAL_CRYP_STATE_TIMEOUT;
          
          /* Process Unlocked */          
          __HAL_UNLOCK(hcryp);
        
          return HAL_TIMEOUT;
        }
      }
    }
    
    /* Disable CRYP */
    __HAL_CRYP_DISABLE(hcryp);
    
    /* Reset the ALGOMODE bits*/
    CRYP->CR &= (uint32_t)(~CRYP_CR_ALGOMODE);
    
    /* Set the CRYP peripheral in AES ECB decryption mode */
    __HAL_CRYP_SET_MODE(hcryp, CRYP_CR_ALGOMODE_AES_ECB | CRYP_CR_ALGODIR);
    /* Flush FIFO */
    __HAL_CRYP_FIFO_FLUSH(hcryp);
    
    /* Enable CRYP */
    __HAL_CRYP_ENABLE(hcryp);
    
    /* Set the phase */
    hcryp->Phase = HAL_CRYP_PHASE_PROCESS;
  }
    
    /* Write Plain Data and Get Cypher Data */
    if(CRYP_ProcessData(hcryp, pCypherData, Size, pPlainData, Timeout) != HAL_OK)
    {
      return HAL_TIMEOUT;
    }
  
  /* Change the CRYP state */
  hcryp->State = HAL_CRYP_STATE_READY;
  
  /* Process Unlocked */
  __HAL_UNLOCK(hcryp);
  
  /* Return function status */
  return HAL_OK;
}

/**
  * @brief  Initializes the CRYP peripheral in AES ECB decryption mode
  *         then decrypted pCypherData. The cypher data are available in pPlainData
  * @param  hcryp pointer to a CRYP_HandleTypeDef structure that contains
  *         the configuration information for CRYP module
  * @param  pCypherData Pointer to the cyphertext buffer
  * @param  Size Length of the plaintext buffer, must be a multiple of 16.
  * @param  pPlainData Pointer to the plaintext buffer
  * @param  Timeout Specify Timeout value  
  * @retval HAL status
  */
HAL_StatusTypeDef HAL_CRYP_AESCBC_Decrypt(CRYP_HandleTypeDef *hcryp, uint8_t *pCypherData, uint16_t Size, uint8_t *pPlainData, uint32_t Timeout)
{
  uint32_t tickstart = 0;
  
  /* Process Locked */
  __HAL_LOCK(hcryp);
  
  /* Change the CRYP state */
  hcryp->State = HAL_CRYP_STATE_BUSY;
  
  /* Check if initialization phase has already been performed */
  if(hcryp->Phase == HAL_CRYP_PHASE_READY)
  {
    /* Set the key */
    CRYP_SetKey(hcryp, hcryp->Init.pKey, hcryp->Init.KeySize);
    
    /* Set the CRYP peripheral in AES Key mode */
    __HAL_CRYP_SET_MODE(hcryp, CRYP_CR_ALGOMODE_AES_KEY | CRYP_CR_ALGODIR);
    
    /* Enable CRYP */
    __HAL_CRYP_ENABLE(hcryp);
    
    /* Get tick */ 
    tickstart = HAL_GetTick();

    while(HAL_IS_BIT_SET(hcryp->Instance->SR, CRYP_FLAG_BUSY))
    {
      /* Check for the Timeout */
      if(Timeout != HAL_MAX_DELAY)
      {
        if((Timeout == 0)||((HAL_GetTick() - tickstart ) > Timeout))
        {
          /* Change state */
          hcryp->State = HAL_CRYP_STATE_TIMEOUT;
          
          /* Process Unlocked */
          __HAL_UNLOCK(hcryp);
          
          return HAL_TIMEOUT;
        }
      }
    }
    
    /* Reset the ALGOMODE bits*/
    CRYP->CR &= (uint32_t)(~CRYP_CR_ALGOMODE);
    
    /* Set the CRYP peripheral in AES CBC decryption mode */
    __HAL_CRYP_SET_MODE(hcryp, CRYP_CR_ALGOMODE_AES_CBC | CRYP_CR_ALGODIR);
    
    /* Set the Initialization Vector */
    CRYP_SetInitVector(hcryp, hcryp->Init.pInitVect, CRYP_KEYSIZE_128B);
    
    /* Flush FIFO */
    __HAL_CRYP_FIFO_FLUSH(hcryp);
    
    /* Enable CRYP */
    __HAL_CRYP_ENABLE(hcryp);
    
    /* Set the phase */
    hcryp->Phase = HAL_CRYP_PHASE_PROCESS;
  }
  
    /* Write Plain Data and Get Cypher Data */
    if(CRYP_ProcessData(hcryp, pCypherData, Size, pPlainData, Timeout) != HAL_OK)
    {
      return HAL_TIMEOUT;
    }
  
  /* Change the CRYP state */
  hcryp->State = HAL_CRYP_STATE_READY;
  
  /* Process Unlocked */
  __HAL_UNLOCK(hcryp);
  
  /* Return function status */
  return HAL_OK;
}

/**
  * @brief  Initializes the CRYP peripheral in AES CTR decryption mode
  *         then decrypted pCypherData. The cypher data are available in pPlainData
  * @param  hcryp pointer to a CRYP_HandleTypeDef structure that contains
  *         the configuration information for CRYP module
  * @param  pCypherData Pointer to the cyphertext buffer
  * @param  Size Length of the plaintext buffer, must be a multiple of 16.
  * @param  pPlainData Pointer to the plaintext buffer
  * @param  Timeout Specify Timeout value  
  * @retval HAL status
  */
HAL_StatusTypeDef HAL_CRYP_AESCTR_Decrypt(CRYP_HandleTypeDef *hcryp, uint8_t *pCypherData, uint16_t Size, uint8_t *pPlainData, uint32_t Timeout)
{  
  /* Process Locked */
  __HAL_LOCK(hcryp);
  
  /* Check if initialization phase has already been performed */
  if(hcryp->Phase == HAL_CRYP_PHASE_READY)
  {
    /* Change the CRYP state */
    hcryp->State = HAL_CRYP_STATE_BUSY;
    
    /* Set the key */
    CRYP_SetKey(hcryp, hcryp->Init.pKey, hcryp->Init.KeySize);
    
    /* Set the CRYP peripheral in AES CTR mode */
    __HAL_CRYP_SET_MODE(hcryp, CRYP_CR_ALGOMODE_AES_CTR | CRYP_CR_ALGODIR);
    
    /* Set the Initialization Vector */
    CRYP_SetInitVector(hcryp, hcryp->Init.pInitVect, CRYP_KEYSIZE_128B);
    
    /* Flush FIFO */
    __HAL_CRYP_FIFO_FLUSH(hcryp);
    
    /* Enable CRYP */
    __HAL_CRYP_ENABLE(hcryp);
    
    /* Set the phase */
    hcryp->Phase = HAL_CRYP_PHASE_PROCESS;
  }
  
    /* Write Plain Data and Get Cypher Data */
    if(CRYP_ProcessData(hcryp, pCypherData, Size, pPlainData, Timeout) != HAL_OK)
    {
      return HAL_TIMEOUT;
    }
  
  /* Change the CRYP state */
  hcryp->State = HAL_CRYP_STATE_READY;
  
  /* Process Unlocked */
  __HAL_UNLOCK(hcryp);
  
  /* Return function status */
  return HAL_OK;
}

/**
  * @brief  Initializes the CRYP peripheral in AES ECB encryption mode using Interrupt.
  * @param  hcryp pointer to a CRYP_HandleTypeDef structure that contains
  *         the configuration information for CRYP module
  * @param  pPlainData Pointer to the plaintext buffer
  * @param  Size Length of the plaintext buffer, must be a multiple of 16 bytes
  * @param  pCypherData Pointer to the cyphertext buffer
  * @retval HAL status
  */
HAL_StatusTypeDef HAL_CRYP_AESECB_Encrypt_IT(CRYP_HandleTypeDef *hcryp, uint8_t *pPlainData, uint16_t Size, uint8_t *pCypherData)
{
  uint32_t inputaddr;
  uint32_t outputaddr;
  
  if(hcryp->State == HAL_CRYP_STATE_READY)
  {
    /* Process Locked */
    __HAL_LOCK(hcryp);
    
    hcryp->CrypInCount = Size;
    hcryp->pCrypInBuffPtr = pPlainData;
    hcryp->pCrypOutBuffPtr = pCypherData;
    hcryp->CrypOutCount = Size;
    
    /* Change the CRYP state */
    hcryp->State = HAL_CRYP_STATE_BUSY;
    
    /* Check if initialization phase has already been performed */
    if(hcryp->Phase == HAL_CRYP_PHASE_READY)
    {
      /* Set the key */
      CRYP_SetKey(hcryp, hcryp->Init.pKey, hcryp->Init.KeySize);
      
      /* Set the CRYP peripheral in AES ECB mode */
      __HAL_CRYP_SET_MODE(hcryp, CRYP_CR_ALGOMODE_AES_ECB);
      
      /* Flush FIFO */
      __HAL_CRYP_FIFO_FLUSH(hcryp);
      
     /* Set the phase */
     hcryp->Phase = HAL_CRYP_PHASE_PROCESS;
    }
    
    /* Enable Interrupts */
    __HAL_CRYP_ENABLE_IT(hcryp, CRYP_IT_INI | CRYP_IT_OUTI);
    
    /* Enable CRYP */
    __HAL_CRYP_ENABLE(hcryp);
    
    /* Return function status */
    return HAL_OK;
  }
  else if(__HAL_CRYP_GET_IT(hcryp, CRYP_IT_INI))
  {
    inputaddr = (uint32_t)hcryp->pCrypInBuffPtr;
    /* Write the Input block in the IN FIFO */
    hcryp->Instance->DR = *(uint32_t*)(inputaddr);
    inputaddr+=4;
    hcryp->Instance->DR = *(uint32_t*)(inputaddr);
    inputaddr+=4;
    hcryp->Instance->DR  = *(uint32_t*)(inputaddr);
    inputaddr+=4;
    hcryp->Instance->DR = *(uint32_t*)(inputaddr);
    hcryp->pCrypInBuffPtr += 16;
    hcryp->CrypInCount -= 16;
    if(hcryp->CrypInCount == 0)
    {
      __HAL_CRYP_DISABLE_IT(hcryp, CRYP_IT_INI);
      /* Call the Input data transfer complete callback */
      HAL_CRYP_InCpltCallback(hcryp);
    }
  }
  else if(__HAL_CRYP_GET_IT(hcryp, CRYP_IT_OUTI))
  {
    outputaddr = (uint32_t)hcryp->pCrypOutBuffPtr;
    /* Read the Output block from the Output FIFO */
    *(uint32_t*)(outputaddr) = hcryp->Instance->DOUT;
    outputaddr+=4;
    *(uint32_t*)(outputaddr) = hcryp->Instance->DOUT;
    outputaddr+=4;
    *(uint32_t*)(outputaddr) = hcryp->Instance->DOUT;
    outputaddr+=4;
    *(uint32_t*)(outputaddr) = hcryp->Instance->DOUT;
    hcryp->pCrypOutBuffPtr += 16;
    hcryp->CrypOutCount -= 16;
    if(hcryp->CrypOutCount == 0)
    {
      __HAL_CRYP_DISABLE_IT(hcryp, CRYP_IT_OUTI);
      /* Process Locked */
      __HAL_UNLOCK(hcryp);
      /* Change the CRYP state */
      hcryp->State = HAL_CRYP_STATE_READY;
      /* Call Input transfer complete callback */
      HAL_CRYP_OutCpltCallback(hcryp);
    }
  }
  
  /* Return function status */
  return HAL_OK;
}

/**
  * @brief  Initializes the CRYP peripheral in AES CBC encryption mode using Interrupt.
  * @param  hcryp pointer to a CRYP_HandleTypeDef structure that contains
  *         the configuration information for CRYP module
  * @param  pPlainData Pointer to the plaintext buffer
  * @param  Size Length of the plaintext buffer, must be a multiple of 16 bytes
  * @param  pCypherData Pointer to the cyphertext buffer
  * @retval HAL status
  */
HAL_StatusTypeDef HAL_CRYP_AESCBC_Encrypt_IT(CRYP_HandleTypeDef *hcryp, uint8_t *pPlainData, uint16_t Size, uint8_t *pCypherData)
{
  uint32_t inputaddr;
  uint32_t outputaddr;
  
  if(hcryp->State == HAL_CRYP_STATE_READY)
  {
    /* Process Locked */
    __HAL_LOCK(hcryp);
    
    hcryp->CrypInCount = Size;
    hcryp->pCrypInBuffPtr = pPlainData;
    hcryp->pCrypOutBuffPtr = pCypherData;
    hcryp->CrypOutCount = Size;
    
    /* Change the CRYP state */
    hcryp->State = HAL_CRYP_STATE_BUSY;
    
    /* Check if initialization phase has already been performed */
    if(hcryp->Phase == HAL_CRYP_PHASE_READY)
    {      
      /* Set the key */
      CRYP_SetKey(hcryp, hcryp->Init.pKey, hcryp->Init.KeySize);
      
      /* Set the CRYP peripheral in AES CBC mode */
      __HAL_CRYP_SET_MODE(hcryp, CRYP_CR_ALGOMODE_AES_CBC);
      
      /* Set the Initialization Vector */
      CRYP_SetInitVector(hcryp, hcryp->Init.pInitVect, CRYP_KEYSIZE_128B);
      
      /* Flush FIFO */
      __HAL_CRYP_FIFO_FLUSH(hcryp);
      
     /* Set the phase */
     hcryp->Phase = HAL_CRYP_PHASE_PROCESS;
    }
    /* Enable Interrupts */
    __HAL_CRYP_ENABLE_IT(hcryp, CRYP_IT_INI | CRYP_IT_OUTI);
    
    /* Enable CRYP */
    __HAL_CRYP_ENABLE(hcryp);
    
    /* Return function status */
    return HAL_OK;
  }
  else if(__HAL_CRYP_GET_IT(hcryp, CRYP_IT_INI))
  {
    inputaddr = (uint32_t)hcryp->pCrypInBuffPtr;
    /* Write the Input block in the IN FIFO */
    hcryp->Instance->DR = *(uint32_t*)(inputaddr);
    inputaddr+=4;
    hcryp->Instance->DR = *(uint32_t*)(inputaddr);
    inputaddr+=4;
    hcryp->Instance->DR  = *(uint32_t*)(inputaddr);
    inputaddr+=4;
    hcryp->Instance->DR = *(uint32_t*)(inputaddr);
    hcryp->pCrypInBuffPtr += 16;
    hcryp->CrypInCount -= 16;
    if(hcryp->CrypInCount == 0)
    {
      __HAL_CRYP_DISABLE_IT(hcryp, CRYP_IT_INI);
      /* Call the Input data transfer complete callback */
      HAL_CRYP_InCpltCallback(hcryp);
    }
  }
  else if(__HAL_CRYP_GET_IT(hcryp, CRYP_IT_OUTI))
  {
    outputaddr = (uint32_t)hcryp->pCrypOutBuffPtr;
    /* Read the Output block from the Output FIFO */
    *(uint32_t*)(outputaddr) = hcryp->Instance->DOUT;
    outputaddr+=4;
    *(uint32_t*)(outputaddr) = hcryp->Instance->DOUT;
    outputaddr+=4;
    *(uint32_t*)(outputaddr) = hcryp->Instance->DOUT;
    outputaddr+=4;
    *(uint32_t*)(outputaddr) = hcryp->Instance->DOUT;
    hcryp->pCrypOutBuffPtr += 16;
    hcryp->CrypOutCount -= 16;
    if(hcryp->CrypOutCount == 0)
    {
      __HAL_CRYP_DISABLE_IT(hcryp, CRYP_IT_OUTI);
      /* Process Locked */
      __HAL_UNLOCK(hcryp);
      /* Change the CRYP state */
      hcryp->State = HAL_CRYP_STATE_READY;
      /* Call Input transfer complete callback */
      HAL_CRYP_OutCpltCallback(hcryp);
    }
  }
  
  /* Return function status */
  return HAL_OK;
}

/**
  * @brief  Initializes the CRYP peripheral in AES CTR encryption mode using Interrupt.
  * @param  hcryp pointer to a CRYP_HandleTypeDef structure that contains
  *         the configuration information for CRYP module
  * @param  pPlainData Pointer to the plaintext buffer
  * @param  Size Length of the plaintext buffer, must be a multiple of 16 bytes
  * @param  pCypherData Pointer to the cyphertext buffer
  * @retval HAL status
  */
HAL_StatusTypeDef HAL_CRYP_AESCTR_Encrypt_IT(CRYP_HandleTypeDef *hcryp, uint8_t *pPlainData, uint16_t Size, uint8_t *pCypherData)
{
  uint32_t inputaddr;
  uint32_t outputaddr;
  
  if(hcryp->State == HAL_CRYP_STATE_READY)
  {
    /* Process Locked */
    __HAL_LOCK(hcryp);
    
    hcryp->CrypInCount = Size;
    hcryp->pCrypInBuffPtr = pPlainData;
    hcryp->pCrypOutBuffPtr = pCypherData;
    hcryp->CrypOutCount = Size;
    
    /* Change the CRYP state */
    hcryp->State = HAL_CRYP_STATE_BUSY;
    
    /* Check if initialization phase has already been performed */
    if(hcryp->Phase == HAL_CRYP_PHASE_READY)
    {
      /* Set the key */
      CRYP_SetKey(hcryp, hcryp->Init.pKey, hcryp->Init.KeySize);
      
      /* Set the CRYP peripheral in AES CTR mode */
      __HAL_CRYP_SET_MODE(hcryp, CRYP_CR_ALGOMODE_AES_CTR);
      
      /* Set the Initialization Vector */
      CRYP_SetInitVector(hcryp, hcryp->Init.pInitVect, CRYP_KEYSIZE_128B);
      
      /* Flush FIFO */
      __HAL_CRYP_FIFO_FLUSH(hcryp);
      
     /* Set the phase */
     hcryp->Phase = HAL_CRYP_PHASE_PROCESS;
    }
    /* Enable Interrupts */
    __HAL_CRYP_ENABLE_IT(hcryp, CRYP_IT_INI | CRYP_IT_OUTI);
    
    /* Enable CRYP */
    __HAL_CRYP_ENABLE(hcryp);
    
    /* Return function status */
    return HAL_OK;
  }
  else if(__HAL_CRYP_GET_IT(hcryp, CRYP_IT_INI))
  {
    inputaddr = (uint32_t)hcryp->pCrypInBuffPtr;
    /* Write the Input block in the IN FIFO */
    hcryp->Instance->DR = *(uint32_t*)(inputaddr);
    inputaddr+=4;
    hcryp->Instance->DR = *(uint32_t*)(inputaddr);
    inputaddr+=4;
    hcryp->Instance->DR  = *(uint32_t*)(inputaddr);
    inputaddr+=4;
    hcryp->Instance->DR = *(uint32_t*)(inputaddr);
    hcryp->pCrypInBuffPtr += 16;
    hcryp->CrypInCount -= 16;
    if(hcryp->CrypInCount == 0)
    {
      __HAL_CRYP_DISABLE_IT(hcryp, CRYP_IT_INI);
      /* Call the Input data transfer complete callback */
      HAL_CRYP_InCpltCallback(hcryp);
    }
  }
  else if(__HAL_CRYP_GET_IT(hcryp, CRYP_IT_OUTI))
  {
    outputaddr = (uint32_t)hcryp->pCrypOutBuffPtr;
    /* Read the Output block from the Output FIFO */
    *(uint32_t*)(outputaddr) = hcryp->Instance->DOUT;
    outputaddr+=4;
    *(uint32_t*)(outputaddr) = hcryp->Instance->DOUT;
    outputaddr+=4;
    *(uint32_t*)(outputaddr) = hcryp->Instance->DOUT;
    outputaddr+=4;
    *(uint32_t*)(outputaddr) = hcryp->Instance->DOUT;
    hcryp->pCrypOutBuffPtr += 16;
    hcryp->CrypOutCount -= 16;
    if(hcryp->CrypOutCount == 0)
    {
      __HAL_CRYP_DISABLE_IT(hcryp, CRYP_IT_OUTI);
      /* Process Unlocked */
      __HAL_UNLOCK(hcryp);
      /* Change the CRYP state */
      hcryp->State = HAL_CRYP_STATE_READY;
      /* Call Input transfer complete callback */
      HAL_CRYP_OutCpltCallback(hcryp);
    }
  }
  
  /* Return function status */
  return HAL_OK;
}


/**
  * @brief  Initializes the CRYP peripheral in AES ECB decryption mode using Interrupt.
  * @param  hcryp pointer to a CRYP_HandleTypeDef structure that contains
  *         the configuration information for CRYP module
  * @param  pCypherData Pointer to the cyphertext buffer
  * @param  Size Length of the plaintext buffer, must be a multiple of 16.
  * @param  pPlainData Pointer to the plaintext buffer
  * @retval HAL status
  */
HAL_StatusTypeDef HAL_CRYP_AESECB_Decrypt_IT(CRYP_HandleTypeDef *hcryp, uint8_t *pCypherData, uint16_t Size, uint8_t *pPlainData)
{
  uint32_t tickstart = 0;

  uint32_t inputaddr;
  uint32_t outputaddr;
  
  if(hcryp->State == HAL_CRYP_STATE_READY)
  {
    /* Process Locked */
    __HAL_LOCK(hcryp);
    
    hcryp->CrypInCount = Size;
    hcryp->pCrypInBuffPtr = pCypherData;
    hcryp->pCrypOutBuffPtr = pPlainData;
    hcryp->CrypOutCount = Size;
    
    /* Change the CRYP state */
    hcryp->State = HAL_CRYP_STATE_BUSY;
    
  /* Check if initialization phase has already been performed */
  if(hcryp->Phase == HAL_CRYP_PHASE_READY)
  {
    /* Set the key */
    CRYP_SetKey(hcryp, hcryp->Init.pKey, hcryp->Init.KeySize);
    
    /* Set the CRYP peripheral in AES Key mode */
    __HAL_CRYP_SET_MODE(hcryp, CRYP_CR_ALGOMODE_AES_KEY | CRYP_CR_ALGODIR);
    /* Enable CRYP */
    __HAL_CRYP_ENABLE(hcryp);
    
    /* Get tick */ 
    tickstart = HAL_GetTick();

    while(HAL_IS_BIT_SET(hcryp->Instance->SR, CRYP_FLAG_BUSY))
    {
      /* Check for the Timeout */
      if((HAL_GetTick() - tickstart ) > CRYP_TIMEOUT_VALUE)
      {
        /* Change state */
        hcryp->State = HAL_CRYP_STATE_TIMEOUT;
        
        /* Process Unlocked */
        __HAL_UNLOCK(hcryp);
        
        return HAL_TIMEOUT;
      }
    }
    
    /* Reset the ALGOMODE bits*/
    CRYP->CR &= (uint32_t)(~CRYP_CR_ALGOMODE);
    
    /* Set the CRYP peripheral in AES ECB decryption mode */
    __HAL_CRYP_SET_MODE(hcryp, CRYP_CR_ALGOMODE_AES_ECB | CRYP_CR_ALGODIR);
    
    /* Flush FIFO */
    __HAL_CRYP_FIFO_FLUSH(hcryp);
    
     /* Set the phase */
     hcryp->Phase = HAL_CRYP_PHASE_PROCESS;
  }
     
    /* Enable Interrupts */
    __HAL_CRYP_ENABLE_IT(hcryp, CRYP_IT_INI | CRYP_IT_OUTI);
    
    /* Enable CRYP */
    __HAL_CRYP_ENABLE(hcryp);
    
    /* Return function status */
    return HAL_OK;
  }
  else if(__HAL_CRYP_GET_IT(hcryp, CRYP_IT_INI))
  {
    inputaddr = (uint32_t)hcryp->pCrypInBuffPtr;
    /* Write the Input block in the IN FIFO */
    hcryp->Instance->DR = *(uint32_t*)(inputaddr);
    inputaddr+=4;
    hcryp->Instance->DR = *(uint32_t*)(inputaddr);
    inputaddr+=4;
    hcryp->Instance->DR  = *(uint32_t*)(inputaddr);
    inputaddr+=4;
    hcryp->Instance->DR = *(uint32_t*)(inputaddr);
    hcryp->pCrypInBuffPtr += 16;
    hcryp->CrypInCount -= 16;
    if(hcryp->CrypInCount == 0)
    {
      __HAL_CRYP_DISABLE_IT(hcryp, CRYP_IT_INI);
      /* Call the Input data transfer complete callback */
      HAL_CRYP_InCpltCallback(hcryp);
    }
  }
  else if(__HAL_CRYP_GET_IT(hcryp, CRYP_IT_OUTI))
  {
    outputaddr = (uint32_t)hcryp->pCrypOutBuffPtr;
    /* Read the Output block from the Output FIFO */
    *(uint32_t*)(outputaddr) = hcryp->Instance->DOUT;
    outputaddr+=4;
    *(uint32_t*)(outputaddr) = hcryp->Instance->DOUT;
    outputaddr+=4;
    *(uint32_t*)(outputaddr) = hcryp->Instance->DOUT;
    outputaddr+=4;
    *(uint32_t*)(outputaddr) = hcryp->Instance->DOUT;
    hcryp->pCrypOutBuffPtr += 16;
    hcryp->CrypOutCount -= 16;
    if(hcryp->CrypOutCount == 0)
    {
      __HAL_CRYP_DISABLE_IT(hcryp, CRYP_IT_OUTI);
      /* Process Unlocked */
      __HAL_UNLOCK(hcryp);
      /* Change the CRYP state */
      hcryp->State = HAL_CRYP_STATE_READY;
      /* Call Input transfer complete callback */
      HAL_CRYP_OutCpltCallback(hcryp);
    }
  }
  
  /* Return function status */
  return HAL_OK;
}

/**
  * @brief  Initializes the CRYP peripheral in AES CBC decryption mode using IT.
  * @param  hcryp pointer to a CRYP_HandleTypeDef structure that contains
  *         the configuration information for CRYP module
  * @param  pCypherData Pointer to the cyphertext buffer
  * @param  Size Length of the plaintext buffer, must be a multiple of 16
  * @param  pPlainData Pointer to the plaintext buffer
  * @retval HAL status
  */
HAL_StatusTypeDef HAL_CRYP_AESCBC_Decrypt_IT(CRYP_HandleTypeDef *hcryp, uint8_t *pCypherData, uint16_t Size, uint8_t *pPlainData)
{

  uint32_t tickstart = 0;   
  uint32_t inputaddr;
  uint32_t outputaddr;
  
  if(hcryp->State == HAL_CRYP_STATE_READY)
  {
    /* Process Locked */
    __HAL_LOCK(hcryp);
    
    /* Get the buffer addresses and sizes */    
    hcryp->CrypInCount = Size;
    hcryp->pCrypInBuffPtr = pCypherData;
    hcryp->pCrypOutBuffPtr = pPlainData;
    hcryp->CrypOutCount = Size;
    
    /* Change the CRYP state */
    hcryp->State = HAL_CRYP_STATE_BUSY;
    
    /* Check if initialization phase has already been performed */
    if(hcryp->Phase == HAL_CRYP_PHASE_READY)
    {
      /* Set the key */
      CRYP_SetKey(hcryp, hcryp->Init.pKey, hcryp->Init.KeySize);
      
      /* Set the CRYP peripheral in AES Key mode */
      __HAL_CRYP_SET_MODE(hcryp, CRYP_CR_ALGOMODE_AES_KEY | CRYP_CR_ALGODIR);
      
      /* Enable CRYP */
      __HAL_CRYP_ENABLE(hcryp);
      
    /* Get tick */
    tickstart = HAL_GetTick();

    while(HAL_IS_BIT_SET(hcryp->Instance->SR, CRYP_FLAG_BUSY))
    {
      /* Check for the Timeout */
      if((HAL_GetTick() - tickstart ) > CRYP_TIMEOUT_VALUE)
      {
        /* Change state */
        hcryp->State = HAL_CRYP_STATE_TIMEOUT;
        
        /* Process Unlocked */
        __HAL_UNLOCK(hcryp);
        
        return HAL_TIMEOUT;
      }
    }
    
      /* Reset the ALGOMODE bits*/
      CRYP->CR &= (uint32_t)(~CRYP_CR_ALGOMODE);
    
      /* Set the CRYP peripheral in AES CBC decryption mode */
      __HAL_CRYP_SET_MODE(hcryp, CRYP_CR_ALGOMODE_AES_CBC | CRYP_CR_ALGODIR);
    
      /* Set the Initialization Vector */
      CRYP_SetInitVector(hcryp, hcryp->Init.pInitVect, CRYP_KEYSIZE_128B);
    
      /* Flush FIFO */
      __HAL_CRYP_FIFO_FLUSH(hcryp);
    
      /* Enable CRYP */
      __HAL_CRYP_ENABLE(hcryp);
      
      /* Set the phase */
      hcryp->Phase = HAL_CRYP_PHASE_PROCESS;
    }
    
    /* Enable Interrupts */
    __HAL_CRYP_ENABLE_IT(hcryp, CRYP_IT_INI | CRYP_IT_OUTI);
    
    /* Enable CRYP */
    __HAL_CRYP_ENABLE(hcryp);
    
    /* Return function status */
    return HAL_OK;
  }
  else if(__HAL_CRYP_GET_IT(hcryp, CRYP_IT_INI))
  {
    inputaddr = (uint32_t)hcryp->pCrypInBuffPtr;
    /* Write the Input block in the IN FIFO */
    hcryp->Instance->DR = *(uint32_t*)(inputaddr);
    inputaddr+=4;
    hcryp->Instance->DR = *(uint32_t*)(inputaddr);
    inputaddr+=4;
    hcryp->Instance->DR  = *(uint32_t*)(inputaddr);
    inputaddr+=4;
    hcryp->Instance->DR = *(uint32_t*)(inputaddr);
    hcryp->pCrypInBuffPtr += 16;
    hcryp->CrypInCount -= 16;
    if(hcryp->CrypInCount == 0)
    {
      __HAL_CRYP_DISABLE_IT(hcryp, CRYP_IT_INI);
      /* Call the Input data transfer complete callback */
      HAL_CRYP_InCpltCallback(hcryp);
    }
  }
  else if(__HAL_CRYP_GET_IT(hcryp, CRYP_IT_OUTI))
  {
    outputaddr = (uint32_t)hcryp->pCrypOutBuffPtr;
    /* Read the Output block from the Output FIFO */
    *(uint32_t*)(outputaddr) = hcryp->Instance->DOUT;
    outputaddr+=4;
    *(uint32_t*)(outputaddr) = hcryp->Instance->DOUT;
    outputaddr+=4;
    *(uint32_t*)(outputaddr) = hcryp->Instance->DOUT;
    outputaddr+=4;
    *(uint32_t*)(outputaddr) = hcryp->Instance->DOUT;
    hcryp->pCrypOutBuffPtr += 16;
    hcryp->CrypOutCount -= 16;
    if(hcryp->CrypOutCount == 0)
    {
      __HAL_CRYP_DISABLE_IT(hcryp, CRYP_IT_OUTI);
      /* Process Unlocked */
      __HAL_UNLOCK(hcryp);
      /* Change the CRYP state */
      hcryp->State = HAL_CRYP_STATE_READY;
      /* Call Input transfer complete callback */
      HAL_CRYP_OutCpltCallback(hcryp);
    }
  }
  
  /* Return function status */
  return HAL_OK;
}

/**
  * @brief  Initializes the CRYP peripheral in AES CTR decryption mode using Interrupt.
  * @param  hcryp pointer to a CRYP_HandleTypeDef structure that contains
  *         the configuration information for CRYP module
  * @param  pCypherData Pointer to the cyphertext buffer
  * @param  Size Length of the plaintext buffer, must be a multiple of 16
  * @param  pPlainData Pointer to the plaintext buffer
  * @retval HAL status
  */
HAL_StatusTypeDef HAL_CRYP_AESCTR_Decrypt_IT(CRYP_HandleTypeDef *hcryp, uint8_t *pCypherData, uint16_t Size, uint8_t *pPlainData)
{
  uint32_t inputaddr;
  uint32_t outputaddr;
  
  if(hcryp->State == HAL_CRYP_STATE_READY)
  {
    /* Process Locked */
    __HAL_LOCK(hcryp);
    
    /* Get the buffer addresses and sizes */    
    hcryp->CrypInCount = Size;
    hcryp->pCrypInBuffPtr = pCypherData;
    hcryp->pCrypOutBuffPtr = pPlainData;
    hcryp->CrypOutCount = Size;
    
    /* Change the CRYP state */
    hcryp->State = HAL_CRYP_STATE_BUSY;
    
    /* Check if initialization phase has already been performed */
    if(hcryp->Phase == HAL_CRYP_PHASE_READY)
    {
      /* Set the key */
      CRYP_SetKey(hcryp, hcryp->Init.pKey, hcryp->Init.KeySize);
      
      /* Set the CRYP peripheral in AES CTR mode */
      __HAL_CRYP_SET_MODE(hcryp, CRYP_CR_ALGOMODE_AES_CTR | CRYP_CR_ALGODIR);
      
      /* Set the Initialization Vector */
      CRYP_SetInitVector(hcryp, hcryp->Init.pInitVect, CRYP_KEYSIZE_128B);
      
      /* Flush FIFO */
      __HAL_CRYP_FIFO_FLUSH(hcryp);
      
      /* Set the phase */
      hcryp->Phase = HAL_CRYP_PHASE_PROCESS;
    }
    
    /* Enable Interrupts */
    __HAL_CRYP_ENABLE_IT(hcryp, CRYP_IT_INI | CRYP_IT_OUTI);
    
    /* Enable CRYP */
    __HAL_CRYP_ENABLE(hcryp);
    
    /* Return function status */
    return HAL_OK;
  }
  else if(__HAL_CRYP_GET_IT(hcryp, CRYP_IT_INI))
  {
    inputaddr = (uint32_t)hcryp->pCrypInBuffPtr;
    /* Write the Input block in the IN FIFO */
    hcryp->Instance->DR = *(uint32_t*)(inputaddr);
    inputaddr+=4;
    hcryp->Instance->DR = *(uint32_t*)(inputaddr);
    inputaddr+=4;
    hcryp->Instance->DR  = *(uint32_t*)(inputaddr);
    inputaddr+=4;
    hcryp->Instance->DR = *(uint32_t*)(inputaddr);
    hcryp->pCrypInBuffPtr += 16;
    hcryp->CrypInCount -= 16;
    if(hcryp->CrypInCount == 0)
    {
      __HAL_CRYP_DISABLE_IT(hcryp, CRYP_IT_INI);
      /* Call the Input data transfer complete callback */
      HAL_CRYP_InCpltCallback(hcryp);
    }
  }
  else if(__HAL_CRYP_GET_IT(hcryp, CRYP_IT_OUTI))
  {
    outputaddr = (uint32_t)hcryp->pCrypOutBuffPtr;
    /* Read the Output block from the Output FIFO */
    *(uint32_t*)(outputaddr) = hcryp->Instance->DOUT;
    outputaddr+=4;
    *(uint32_t*)(outputaddr) = hcryp->Instance->DOUT;
    outputaddr+=4;
    *(uint32_t*)(outputaddr) = hcryp->Instance->DOUT;
    outputaddr+=4;
    *(uint32_t*)(outputaddr) = hcryp->Instance->DOUT;
    hcryp->pCrypOutBuffPtr += 16;
    hcryp->CrypOutCount -= 16;
    if(hcryp->CrypOutCount == 0)
    {
      __HAL_CRYP_DISABLE_IT(hcryp, CRYP_IT_OUTI);
      /* Process Unlocked */
      __HAL_UNLOCK(hcryp);
      /* Change the CRYP state */
      hcryp->State = HAL_CRYP_STATE_READY;
      /* Call Input transfer complete callback */
      HAL_CRYP_OutCpltCallback(hcryp);
    }
  }
  
  /* Return function status */
  return HAL_OK;
}

/**
  * @brief  Initializes the CRYP peripheral in AES ECB encryption mode using DMA.
  * @param  hcryp pointer to a CRYP_HandleTypeDef structure that contains
  *         the configuration information for CRYP module
  * @param  pPlainData Pointer to the plaintext buffer
  * @param  Size Length of the plaintext buffer, must be a multiple of 16 bytes
  * @param  pCypherData Pointer to the cyphertext buffer
  * @retval HAL status
  */
HAL_StatusTypeDef HAL_CRYP_AESECB_Encrypt_DMA(CRYP_HandleTypeDef *hcryp, uint8_t *pPlainData, uint16_t Size, uint8_t *pCypherData)
{
  uint32_t inputaddr;
  uint32_t outputaddr;
  
  if((hcryp->State == HAL_CRYP_STATE_READY) || (hcryp->Phase == HAL_CRYP_PHASE_PROCESS))
  {
    /* Process Locked */
    __HAL_LOCK(hcryp);
    
    inputaddr  = (uint32_t)pPlainData;
    outputaddr = (uint32_t)pCypherData;
    
    /* Change the CRYP state */
    hcryp->State = HAL_CRYP_STATE_BUSY;
    
    /* Check if initialization phase has already been performed */
    if(hcryp->Phase == HAL_CRYP_PHASE_READY)
    {
      /* Set the key */
      CRYP_SetKey(hcryp, hcryp->Init.pKey, hcryp->Init.KeySize);
      
      /* Set the CRYP peripheral in AES ECB mode */
      __HAL_CRYP_SET_MODE(hcryp, CRYP_CR_ALGOMODE_AES_ECB);
      
      /* Flush FIFO */
      __HAL_CRYP_FIFO_FLUSH(hcryp);
      
     /* Set the phase */
     hcryp->Phase = HAL_CRYP_PHASE_PROCESS;
    }
    /* Set the input and output addresses and start DMA transfer */ 
    CRYP_SetDMAConfig(hcryp, inputaddr, Size, outputaddr);
    
    /* Process Unlocked */
    __HAL_UNLOCK(hcryp);
     
    /* Return function status */
    return HAL_OK;
  }
  else
  {
    return HAL_ERROR;   
  }
}

/**
  * @brief  Initializes the CRYP peripheral in AES CBC encryption mode using DMA.
  * @param  hcryp pointer to a CRYP_HandleTypeDef structure that contains
  *         the configuration information for CRYP module
  * @param  pPlainData Pointer to the plaintext buffer
  * @param  Size Length of the plaintext buffer, must be a multiple of 16.
  * @param  pCypherData Pointer to the cyphertext buffer
  * @retval HAL status
  */
HAL_StatusTypeDef HAL_CRYP_AESCBC_Encrypt_DMA(CRYP_HandleTypeDef *hcryp, uint8_t *pPlainData, uint16_t Size, uint8_t *pCypherData)
{
  uint32_t inputaddr;
  uint32_t outputaddr;
  
  if((hcryp->State == HAL_CRYP_STATE_READY) || (hcryp->Phase == HAL_CRYP_PHASE_PROCESS))
  {
    /* Process Locked */
    __HAL_LOCK(hcryp);
    
    inputaddr  = (uint32_t)pPlainData;
    outputaddr = (uint32_t)pCypherData;
    
    /* Change the CRYP state */
    hcryp->State = HAL_CRYP_STATE_BUSY;
  
    /* Check if initialization phase has already been performed */
    if(hcryp->Phase == HAL_CRYP_PHASE_READY)
    {
      /* Set the key */
      CRYP_SetKey(hcryp, hcryp->Init.pKey, hcryp->Init.KeySize);
      
      /* Set the CRYP peripheral in AES ECB mode */
      __HAL_CRYP_SET_MODE(hcryp, CRYP_CR_ALGOMODE_AES_CBC);
      
      /* Set the Initialization Vector */
      CRYP_SetInitVector(hcryp, hcryp->Init.pInitVect, CRYP_KEYSIZE_128B);
      
      /* Flush FIFO */
      __HAL_CRYP_FIFO_FLUSH(hcryp);
      
       /* Set the phase */
       hcryp->Phase = HAL_CRYP_PHASE_PROCESS;
     }
     /* Set the input and output addresses and start DMA transfer */ 
     CRYP_SetDMAConfig(hcryp, inputaddr, Size, outputaddr);
     
     /* Process Unlocked */
     __HAL_UNLOCK(hcryp);
     
     /* Return function status */
     return HAL_OK;
  }
  else
  {
    return HAL_ERROR;   
  }
}

/**
  * @brief  Initializes the CRYP peripheral in AES CTR encryption mode using DMA.
  * @param  hcryp pointer to a CRYP_HandleTypeDef structure that contains
  *         the configuration information for CRYP module
  * @param  pPlainData Pointer to the plaintext buffer
  * @param  Size Length of the plaintext buffer, must be a multiple of 16.
  * @param  pCypherData Pointer to the cyphertext buffer
  * @retval HAL status
  */
HAL_StatusTypeDef HAL_CRYP_AESCTR_Encrypt_DMA(CRYP_HandleTypeDef *hcryp, uint8_t *pPlainData, uint16_t Size, uint8_t *pCypherData)
{
  uint32_t inputaddr;
  uint32_t outputaddr;
  
  if((hcryp->State == HAL_CRYP_STATE_READY) || (hcryp->Phase == HAL_CRYP_PHASE_PROCESS))
  {
    /* Process Locked */
    __HAL_LOCK(hcryp);
    
    inputaddr  = (uint32_t)pPlainData;
    outputaddr = (uint32_t)pCypherData;
    
  /* Change the CRYP state */
  hcryp->State = HAL_CRYP_STATE_BUSY;
  
    /* Check if initialization phase has already been performed */
    if(hcryp->Phase == HAL_CRYP_PHASE_READY)
    {
      /* Set the key */
      CRYP_SetKey(hcryp, hcryp->Init.pKey, hcryp->Init.KeySize);
      
      /* Set the CRYP peripheral in AES ECB mode */
      __HAL_CRYP_SET_MODE(hcryp, CRYP_CR_ALGOMODE_AES_CTR);
      
      /* Set the Initialization Vector */
      CRYP_SetInitVector(hcryp, hcryp->Init.pInitVect, CRYP_KEYSIZE_128B);
      
      /* Flush FIFO */
      __HAL_CRYP_FIFO_FLUSH(hcryp);
      
       /* Set the phase */
       hcryp->Phase = HAL_CRYP_PHASE_PROCESS;
    }
    
    /* Set the input and output addresses and start DMA transfer */ 
    CRYP_SetDMAConfig(hcryp, inputaddr, Size, outputaddr);
    
    /* Process Unlocked */
    __HAL_UNLOCK(hcryp);
    
    /* Return function status */
    return HAL_OK;
  }
  else
  {
    return HAL_ERROR;   
  }
}

/**
  * @brief  Initializes the CRYP peripheral in AES ECB decryption mode using DMA.
  * @param  hcryp pointer to a CRYP_HandleTypeDef structure that contains
  *         the configuration information for CRYP module
  * @param  pCypherData Pointer to the cyphertext buffer
  * @param  Size Length of the plaintext buffer, must be a multiple of 16 bytes
  * @param  pPlainData Pointer to the plaintext buffer
  * @retval HAL status
  */
HAL_StatusTypeDef HAL_CRYP_AESECB_Decrypt_DMA(CRYP_HandleTypeDef *hcryp, uint8_t *pCypherData, uint16_t Size, uint8_t *pPlainData)
{
  uint32_t tickstart = 0;   
  uint32_t inputaddr;
  uint32_t outputaddr;
  
  if((hcryp->State == HAL_CRYP_STATE_READY) || (hcryp->Phase == HAL_CRYP_PHASE_PROCESS))
  {
    /* Process Locked */
    __HAL_LOCK(hcryp);
    
    inputaddr  = (uint32_t)pCypherData;
    outputaddr = (uint32_t)pPlainData;
    
    /* Change the CRYP state */
    hcryp->State = HAL_CRYP_STATE_BUSY;
    
    /* Check if initialization phase has already been performed */
    if(hcryp->Phase == HAL_CRYP_PHASE_READY)
    {
    /* Set the key */
    CRYP_SetKey(hcryp, hcryp->Init.pKey, hcryp->Init.KeySize);
    
    /* Set the CRYP peripheral in AES Key mode */
    __HAL_CRYP_SET_MODE(hcryp, CRYP_CR_ALGOMODE_AES_KEY | CRYP_CR_ALGODIR);
=======
#if (USE_HAL_CRYP_REGISTER_CALLBACKS == 1)
/**
  * @brief  Register a User CRYP Callback
  *         To be used instead of the weak predefined callback
  * @param hcryp cryp handle
  * @param CallbackID ID of the callback to be registered
  *        This parameter can be one of the following values:
  *          @arg @ref HAL_CRYP_INPUT_COMPLETE_CB_ID Input FIFO transfer completed callback ID
  *          @arg @ref HAL_CRYP_OUTPUT_COMPLETE_CB_ID Output FIFO transfer completed callback ID
  *          @arg @ref HAL_CRYP_ERROR_CB_ID Error callback ID 
  *          @arg @ref HAL_CRYP_MSPINIT_CB_ID MspInit callback ID
  *          @arg @ref HAL_CRYP_MSPDEINIT_CB_ID MspDeInit callback ID
  * @param pCallback pointer to the Callback function
  * @retval status
  */
HAL_StatusTypeDef HAL_CRYP_RegisterCallback(CRYP_HandleTypeDef *hcryp, HAL_CRYP_CallbackIDTypeDef CallbackID, pCRYP_CallbackTypeDef pCallback)
{
  HAL_StatusTypeDef status = HAL_OK;
  
  if(pCallback == NULL)
  {
    /* Update the error code */
    hcryp->ErrorCode |= HAL_CRYP_ERROR_INVALID_CALLBACK;
    
    return HAL_ERROR;
  }
  /* Process locked */
  __HAL_LOCK(hcryp);
  
  if(hcryp->State == HAL_CRYP_STATE_READY)
  {
    switch (CallbackID)
    {
    case HAL_CRYP_INPUT_COMPLETE_CB_ID :
      hcryp->InCpltCallback = pCallback;
      break;
      
    case HAL_CRYP_OUTPUT_COMPLETE_CB_ID :
      hcryp->OutCpltCallback = pCallback;
      break;
      
    case HAL_CRYP_ERROR_CB_ID :
      hcryp->ErrorCallback = pCallback;
      break;
      
    case HAL_CRYP_MSPINIT_CB_ID :
      hcryp->MspInitCallback = pCallback;
      break;
      
    case HAL_CRYP_MSPDEINIT_CB_ID :
      hcryp->MspDeInitCallback = pCallback;
      break;
      
    default :
      /* Update the error code */
      hcryp->ErrorCode |= HAL_CRYP_ERROR_INVALID_CALLBACK;
      /* Return error status */
      status =  HAL_ERROR;
      break;
    }
  }
  else if(hcryp->State == HAL_CRYP_STATE_RESET)
  {
    switch (CallbackID)
    {
    case HAL_CRYP_MSPINIT_CB_ID :
      hcryp->MspInitCallback = pCallback;
      break;
      
    case HAL_CRYP_MSPDEINIT_CB_ID :
      hcryp->MspDeInitCallback = pCallback;
      break;
      
    default :
      /* Update the error code */
      hcryp->ErrorCode |= HAL_CRYP_ERROR_INVALID_CALLBACK;
      /* Return error status */
      status =  HAL_ERROR;
      break;
    }
  }
  else
  {
    /* Update the error code */
    hcryp->ErrorCode |= HAL_CRYP_ERROR_INVALID_CALLBACK;
    /* Return error status */
    status =  HAL_ERROR;
  }
  
  /* Release Lock */
  __HAL_UNLOCK(hcryp);
  
  return status;
}

/**
  * @brief  Unregister an CRYP Callback
  *         CRYP callback is redirected to the weak predefined callback
  * @param hcryp cryp handle
  * @param CallbackID ID of the callback to be unregistered
  *        This parameter can be one of the following values:
  *          @arg @ref HAL_CRYP_INPUT_COMPLETE_CB_ID Input FIFO transfer completed callback ID
  *          @arg @ref HAL_CRYP_OUTPUT_COMPLETE_CB_ID Output FIFO transfer completed callback ID
  *          @arg @ref HAL_CRYP_ERROR_CB_ID Error callback ID 
  *          @arg @ref HAL_CRYP_MSPINIT_CB_ID MspInit callback ID
  *          @arg @ref HAL_CRYP_MSPDEINIT_CB_ID MspDeInit callback ID
  * @retval status
  */
HAL_StatusTypeDef HAL_CRYP_UnRegisterCallback(CRYP_HandleTypeDef *hcryp, HAL_CRYP_CallbackIDTypeDef CallbackID)
{
  HAL_StatusTypeDef status = HAL_OK;
  
  /* Process locked */
  __HAL_LOCK(hcryp);
  
  if(hcryp->State == HAL_CRYP_STATE_READY)
  {
    switch (CallbackID)
    {
    case HAL_CRYP_INPUT_COMPLETE_CB_ID :
      hcryp->InCpltCallback = HAL_CRYP_InCpltCallback;  /* Legacy weak  InCpltCallback  */
      break;
      
    case HAL_CRYP_OUTPUT_COMPLETE_CB_ID :
      hcryp->OutCpltCallback = HAL_CRYP_OutCpltCallback;         /* Legacy weak OutCpltCallback       */
      break;
      
    case HAL_CRYP_ERROR_CB_ID :
      hcryp->ErrorCallback = HAL_CRYP_ErrorCallback;           /* Legacy weak ErrorCallback        */
      break;
      
    case HAL_CRYP_MSPINIT_CB_ID :
      hcryp->MspInitCallback = HAL_CRYP_MspInit;
      break;
      
    case HAL_CRYP_MSPDEINIT_CB_ID :
      hcryp->MspDeInitCallback = HAL_CRYP_MspDeInit;
      break;
      
    default :
      /* Update the error code */
      hcryp->ErrorCode |= HAL_CRYP_ERROR_INVALID_CALLBACK;
      /* Return error status */
      status =  HAL_ERROR;
      break;
    }
  }
  else if(hcryp->State == HAL_CRYP_STATE_RESET)
  {
    switch (CallbackID)
    {
    case HAL_CRYP_MSPINIT_CB_ID :
      hcryp->MspInitCallback = HAL_CRYP_MspInit;
      break;
      
    case HAL_CRYP_MSPDEINIT_CB_ID :
      hcryp->MspDeInitCallback = HAL_CRYP_MspDeInit;
      break;
      
    default :
      /* Update the error code */
      hcryp->ErrorCode |= HAL_CRYP_ERROR_INVALID_CALLBACK;
      /* Return error status */
      status =  HAL_ERROR;
      break;
    }
  }
  else
  {
    /* Update the error code */
    hcryp->ErrorCode |= HAL_CRYP_ERROR_INVALID_CALLBACK;
    /* Return error status */
    status =  HAL_ERROR;
  }
  
  /* Release Lock */
  __HAL_UNLOCK(hcryp);
  
  return status;
}
#endif /* USE_HAL_UART_REGISTER_CALLBACKS */
/**
  * @}
  */

/** @defgroup CRYP_Exported_Functions_Group2  Encrypt Decrypt functions 
 *  @brief   processing functions. 
 *
@verbatim   
  ==============================================================================
                      ##### Encrypt Decrypt  functions #####
  ==============================================================================  
    [..]  This section provides API allowing to Encrypt/Decrypt Data following 
          Standard DES/TDES or AES, and Algorithm configured by the user:
      (+) Standard DES/TDES only supported by CRYP1 IP, below list of Algorithm supported : 
           - Electronic Code Book(ECB)
           - Cipher Block Chaining (CBC)
      (+) Standard AES  supported by CRYP1 IP & TinyAES, list of Algorithm supported:
           - Electronic Code Book(ECB)
           - Cipher Block Chaining (CBC)
           - Counter mode (CTR)
           - Cipher Block Chaining (CBC)
           - Counter mode (CTR)
           - Galois/counter mode (GCM)
           - Counter with Cipher Block Chaining-Message(CCM) 
    [..]  Three processing functions are available:
      (+) Polling mode : HAL_CRYP_Encrypt & HAL_CRYP_Decrypt
      (+) Interrupt mode : HAL_CRYP_Encrypt_IT & HAL_CRYP_Decrypt_IT
      (+) DMA mode : HAL_CRYP_Encrypt_DMA & HAL_CRYP_Decrypt_DMA

@endverbatim
  * @{
  */


/**
  * @brief  Encryption mode.
  * @param  hcryp: pointer to a CRYP_HandleTypeDef structure that contains
  *         the configuration information for CRYP module
  * @param  Input: Pointer to the input buffer (plaintext)
  * @param  Size: Length of the plaintext buffer in word.
  * @param  Output: Pointer to the output buffer(ciphertext)
  * @param  Timeout: Specify Timeout value  
  * @retval HAL status
  */
HAL_StatusTypeDef HAL_CRYP_Encrypt(CRYP_HandleTypeDef *hcryp, uint32_t *Input, uint16_t Size, uint32_t *Output, uint32_t Timeout)
{
  uint32_t algo;
  HAL_StatusTypeDef status;
  
  if(hcryp->State == HAL_CRYP_STATE_READY)
  { 
    /* Change state Busy */
    hcryp->State = HAL_CRYP_STATE_BUSY;
    
    /* Process locked */
    __HAL_LOCK(hcryp);
    
    /*  Reset CrypInCount, CrypOutCount and Initialize pCrypInBuffPtr and pCrypOutBuffPtr parameters*/
    hcryp->CrypInCount = 0U;
    hcryp->CrypOutCount = 0U;
    hcryp->pCrypInBuffPtr = Input;
    hcryp->pCrypOutBuffPtr = Output;
    
    /*  Calculate Size parameter in Byte*/
    if (hcryp->Init.DataWidthUnit == CRYP_DATAWIDTHUNIT_WORD)
    {
      hcryp->Size = Size * 4U;
    }
    else
    {
      hcryp->Size = Size;	
    }
    
#if defined (CRYP)  
    /* Set Encryption operating mode*/   
    MODIFY_REG(hcryp->Instance->CR, CRYP_CR_ALGODIR, CRYP_OPERATINGMODE_ENCRYPT);  
    
    /* algo get algorithm selected */     
    algo = hcryp->Instance->CR & CRYP_CR_ALGOMODE;
    
    switch(algo)
    {    
    case CRYP_DES_ECB:
    case CRYP_DES_CBC:
    case CRYP_TDES_ECB:
    case CRYP_TDES_CBC:
      
      /*Set Key */
      hcryp->Instance->K1LR = *(uint32_t*)(hcryp->Init.pKey);
      hcryp->Instance->K1RR = *(uint32_t*)(hcryp->Init.pKey+1);
      if ((hcryp->Init.Algorithm == CRYP_TDES_ECB) || (hcryp->Init.Algorithm == CRYP_TDES_CBC))
      {
        hcryp->Instance->K2LR = *(uint32_t*)(hcryp->Init.pKey+2);
        hcryp->Instance->K2RR = *(uint32_t*)(hcryp->Init.pKey+3);
        hcryp->Instance->K3LR = *(uint32_t*)(hcryp->Init.pKey+4);
        hcryp->Instance->K3RR = *(uint32_t*)(hcryp->Init.pKey+5);  
      }
      
      /*Set Initialization Vector (IV)*/    
      if ((hcryp->Init.Algorithm == CRYP_DES_CBC) || (hcryp->Init.Algorithm == CRYP_TDES_CBC))
      {
        hcryp->Instance->IV0LR = *(uint32_t*)(hcryp->Init.pInitVect);
        hcryp->Instance->IV0RR = *(uint32_t*)(hcryp->Init.pInitVect+1);
      }
      
      /* Flush FIFO */
      HAL_CRYP_FIFO_FLUSH(hcryp);
      
      /* Set the phase */
      hcryp->Phase = CRYP_PHASE_PROCESS;
      
      /* Statrt DES/TDES encryption process */     
      status = CRYP_TDES_Process(hcryp,Timeout);     
      break;
      
    case CRYP_AES_ECB:
    case CRYP_AES_CBC:
    case CRYP_AES_CTR:
      
      /* AES encryption */       
      status = CRYP_AES_Encrypt(hcryp, Timeout);
      break;   
      
    case CRYP_AES_GCM:
      
      /* AES GCM encryption */       
      status = CRYP_AESGCM_Process(hcryp, Timeout);
      
      break;
      
    case CRYP_AES_CCM:
      
      /* AES CCM encryption */  
      status = CRYP_AESCCM_Process(hcryp,Timeout);     
      break;
       
    default:
      hcryp->ErrorCode |= HAL_CRYP_ERROR_NOT_SUPPORTED;
      return HAL_ERROR;
    }      
    
#else /*AES*/
    
    /* Set the operating mode*/
    MODIFY_REG(hcryp->Instance->CR, AES_CR_MODE, CRYP_OPERATINGMODE_ENCRYPT); 
    
    /* algo get algorithm selected */  
    algo = hcryp->Instance->CR & AES_CR_CHMOD;  
    
    switch(algo)
    {    
      
    case CRYP_AES_ECB:
    case CRYP_AES_CBC:
    case CRYP_AES_CTR:
      
      /* AES encryption */        
      status = CRYP_AES_Encrypt(hcryp, Timeout);     
      break;   
      
    case CRYP_AES_GCM_GMAC:
      
      /* AES GCM encryption */  
      status = CRYP_AESGCM_Process (hcryp,Timeout) ;  
      break;
      
    case CRYP_AES_CCM:
      
      /* AES CCM encryption */ 
      status = CRYP_AESCCM_Process(hcryp,Timeout);   
      break;
      
    default:
      hcryp->ErrorCode |= HAL_CRYP_ERROR_NOT_SUPPORTED;
      return HAL_ERROR;
    }
#endif /*end AES or CRYP */   
    
    if (status == HAL_OK)
    { 
      /* Change the CRYP peripheral state */
      hcryp->State = HAL_CRYP_STATE_READY;
      
      /* Process unlocked */
      __HAL_UNLOCK(hcryp);
    }    
  }
  else
  {
    /* Busy error code field */
    hcryp->ErrorCode |= HAL_CRYP_ERROR_BUSY; 
    return HAL_ERROR;
  } 
  
  /* Return function status */
  return HAL_OK;  
}

/**
  * @brief  Decryption mode.
  * @param  hcryp: pointer to a CRYP_HandleTypeDef structure that contains
  *         the configuration information for CRYP module
  * @param  Input: Pointer to the input buffer (ciphertext )
  * @param  Size: Length of the plaintext buffer in word.
  * @param  Output: Pointer to the output buffer(plaintext)
  * @param  Timeout: Specify Timeout value  
  * @retval HAL status
  */
HAL_StatusTypeDef HAL_CRYP_Decrypt(CRYP_HandleTypeDef *hcryp, uint32_t *Input, uint16_t Size, uint32_t *Output, uint32_t Timeout)
{
  HAL_StatusTypeDef status;
  uint32_t algo; 
  
  if(hcryp->State == HAL_CRYP_STATE_READY)
  {
    /* Change state Busy */
    hcryp->State = HAL_CRYP_STATE_BUSY;
    
    /* Process locked */
    __HAL_LOCK(hcryp); 
    
    /*  Reset CrypInCount, CrypOutCount and Initialize pCrypInBuffPtr and pCrypOutBuffPtr  parameters*/
    hcryp->CrypInCount = 0U;
    hcryp->CrypOutCount = 0U;
    hcryp->pCrypInBuffPtr = Input;
    hcryp->pCrypOutBuffPtr = Output;
    
    /*  Calculate Size parameter in Byte*/
    if (hcryp->Init.DataWidthUnit == CRYP_DATAWIDTHUNIT_WORD)
    {
      hcryp->Size = Size * 4U;
    }
    else
    {
      hcryp->Size = Size;	
    }
    
#if defined (CRYP)
    
    /* Set Decryption operating mode*/
    MODIFY_REG(hcryp->Instance->CR, CRYP_CR_ALGODIR, CRYP_OPERATINGMODE_DECRYPT);
    
    /* algo get algorithm selected */   
    algo = hcryp->Instance->CR & CRYP_CR_ALGOMODE;
    
    switch(algo)
    {    
    case CRYP_DES_ECB:
    case CRYP_DES_CBC:
    case CRYP_TDES_ECB:
    case CRYP_TDES_CBC:
      
      /*Set Key */
      hcryp->Instance->K1LR = *(uint32_t*)(hcryp->Init.pKey);
      hcryp->Instance->K1RR = *(uint32_t*)(hcryp->Init.pKey+1);
      if ((hcryp->Init.Algorithm == CRYP_TDES_ECB) || (hcryp->Init.Algorithm == CRYP_TDES_CBC))
      {
        hcryp->Instance->K2LR = *(uint32_t*)(hcryp->Init.pKey+2);
        hcryp->Instance->K2RR = *(uint32_t*)(hcryp->Init.pKey+3);
        hcryp->Instance->K3LR = *(uint32_t*)(hcryp->Init.pKey+4);
        hcryp->Instance->K3RR = *(uint32_t*)(hcryp->Init.pKey+5);  
      }
      
      /*Set Initialization Vector (IV)*/   
      if ((hcryp->Init.Algorithm == CRYP_DES_CBC) || (hcryp->Init.Algorithm == CRYP_TDES_CBC))
      {
        hcryp->Instance->IV0LR = *(uint32_t*)(hcryp->Init.pInitVect);
        hcryp->Instance->IV0RR = *(uint32_t*)(hcryp->Init.pInitVect+1);
      }
      
      /* Flush FIFO */
      HAL_CRYP_FIFO_FLUSH(hcryp);
      
      /* Set the phase */
      hcryp->Phase = CRYP_PHASE_PROCESS;
      
      /* Start DES/TDES decryption process */  
      status = CRYP_TDES_Process(hcryp, Timeout);
      
      break;
      
    case CRYP_AES_ECB:
    case CRYP_AES_CBC:
    case CRYP_AES_CTR:
      
      /* AES decryption */   
      status = CRYP_AES_Decrypt(hcryp, Timeout);
      break;   
      
    case CRYP_AES_GCM:
      
      /* AES GCM decryption */       
      status = CRYP_AESGCM_Process (hcryp, Timeout) ;   
      break;
      
    case CRYP_AES_CCM:
      
      /* AES CCM decryption */ 
      status = CRYP_AESCCM_Process(hcryp, Timeout); 
      break;
       
    default:
      hcryp->ErrorCode |= HAL_CRYP_ERROR_NOT_SUPPORTED;
      return HAL_ERROR;
    }      
    
#else /*AES*/
    
    /* Set Decryption operating mode*/
    MODIFY_REG(hcryp->Instance->CR, AES_CR_MODE, CRYP_OPERATINGMODE_DECRYPT);    
    
    /* algo get algorithm selected */  
    algo = hcryp->Instance->CR & AES_CR_CHMOD;
    
    switch(algo)
    {    
      
    case CRYP_AES_ECB:
    case CRYP_AES_CBC:
    case CRYP_AES_CTR:
      
      /* AES decryption */ 
      status = CRYP_AES_Decrypt(hcryp, Timeout);
      break;   
      
    case CRYP_AES_GCM_GMAC:
      
      /* AES GCM decryption */   
      status = CRYP_AESGCM_Process (hcryp, Timeout) ;  
      break;
      
    case CRYP_AES_CCM:
      
      /* AES CCM decryption */ 
      status = CRYP_AESCCM_Process(hcryp, Timeout);    
      break;
      
    default:
      hcryp->ErrorCode |= HAL_CRYP_ERROR_NOT_SUPPORTED;
      return HAL_ERROR;
    }
#endif /* End AES or CRYP */ 
    
    if (status == HAL_OK)
    { 
      /* Change the CRYP peripheral state */
      hcryp->State = HAL_CRYP_STATE_READY;
      
      /* Process unlocked */
      __HAL_UNLOCK(hcryp);
    }    
  }
  else
  {
    /* Busy error code field */
    hcryp->ErrorCode |= HAL_CRYP_ERROR_BUSY; 
    return HAL_ERROR;
  }
  
  /* Return function status */
  return HAL_OK;  
}

/**
  * @brief  Encryption in interrupt mode.
  * @param  hcryp: pointer to a CRYP_HandleTypeDef structure that contains
  *         the configuration information for CRYP module
  * @param  Input: Pointer to the input buffer (plaintext)
  * @param  Size: Length of the plaintext buffer in word
  * @param  Output: Pointer to the output buffer(ciphertext)
  * @retval HAL status
  */
HAL_StatusTypeDef HAL_CRYP_Encrypt_IT(CRYP_HandleTypeDef *hcryp, uint32_t *Input, uint16_t Size, uint32_t *Output)
{
  uint32_t algo; 
  HAL_StatusTypeDef status = HAL_OK;
  
  if(hcryp->State == HAL_CRYP_STATE_READY)
  {
    /* Change state Busy */
    hcryp->State = HAL_CRYP_STATE_BUSY;
    
    /* Process locked */
    __HAL_LOCK(hcryp);
    
    /*  Reset CrypInCount, CrypOutCount and Initialize pCrypInBuffPtr and pCrypOutBuffPtr parameters*/
    hcryp->CrypInCount = 0U;
    hcryp->CrypOutCount = 0U;
    hcryp->pCrypInBuffPtr = Input;
    hcryp->pCrypOutBuffPtr = Output;  
    
    /*  Calculate Size parameter in Byte*/
    if (hcryp->Init.DataWidthUnit == CRYP_DATAWIDTHUNIT_WORD)
    {
      hcryp->Size = Size * 4U;
    }
    else
    {
      hcryp->Size = Size;	
    }
    
#if defined (CRYP)
    
    /* Set encryption operating mode*/   
    MODIFY_REG(hcryp->Instance->CR, CRYP_CR_ALGODIR, CRYP_OPERATINGMODE_ENCRYPT); 
    
    /* algo get algorithm selected */  
    algo = (hcryp->Instance->CR & CRYP_CR_ALGOMODE);
    
    switch(algo)
    {    
    case CRYP_DES_ECB:
    case CRYP_DES_CBC:
    case CRYP_TDES_ECB:
    case CRYP_TDES_CBC:
      
      /*Set Key */
      hcryp->Instance->K1LR = *(uint32_t*)(hcryp->Init.pKey);
      hcryp->Instance->K1RR = *(uint32_t*)(hcryp->Init.pKey+1);
      if ((hcryp->Init.Algorithm == CRYP_TDES_ECB) || (hcryp->Init.Algorithm == CRYP_TDES_CBC))
      {
        hcryp->Instance->K2LR = *(uint32_t*)(hcryp->Init.pKey+2);
        hcryp->Instance->K2RR = *(uint32_t*)(hcryp->Init.pKey+3);
        hcryp->Instance->K3LR = *(uint32_t*)(hcryp->Init.pKey+4);
        hcryp->Instance->K3RR = *(uint32_t*)(hcryp->Init.pKey+5);  
      }
      /* Set the Initialization Vector*/
      if ((hcryp->Init.Algorithm == CRYP_DES_CBC) || (hcryp->Init.Algorithm == CRYP_TDES_CBC))
      {
        hcryp->Instance->IV0LR = *(uint32_t*)(hcryp->Init.pInitVect);
        hcryp->Instance->IV0RR = *(uint32_t*)(hcryp->Init.pInitVect+1);
      }
      
      /* Flush FIFO */
      HAL_CRYP_FIFO_FLUSH(hcryp);
      
      /* Set the phase */
      hcryp->Phase = CRYP_PHASE_PROCESS;
      
      /* Enable interrupts */
      __HAL_CRYP_ENABLE_IT(hcryp, CRYP_IT_INI | CRYP_IT_OUTI);
      
      /* Enable CRYP to start DES/TDES process*/
      __HAL_CRYP_ENABLE(hcryp);      
      break;
      
    case CRYP_AES_ECB:
    case CRYP_AES_CBC:
    case CRYP_AES_CTR:
      
      status = CRYP_AES_Encrypt_IT(hcryp);
      break;   
      
    case CRYP_AES_GCM:
      
      status = CRYP_AESGCM_Process_IT (hcryp) ;  
      break;
      
    case CRYP_AES_CCM:
      
      status = CRYP_AESCCM_Process_IT(hcryp);  
      break;
     
    default:
      hcryp->ErrorCode |= HAL_CRYP_ERROR_NOT_SUPPORTED;
      status =  HAL_ERROR;   
      break;
    }
    
#else /* AES */
    
    /* Set encryption operating mode*/
    MODIFY_REG(hcryp->Instance->CR, AES_CR_MODE, CRYP_OPERATINGMODE_ENCRYPT); 
    
    /* algo get algorithm selected */  
    algo = hcryp->Instance->CR & AES_CR_CHMOD;
    
    switch(algo)
    {         
    case CRYP_AES_ECB:
    case CRYP_AES_CBC:
    case CRYP_AES_CTR:
      
      /* AES encryption */  
      status = CRYP_AES_Encrypt_IT(hcryp);
      break;   
      
    case CRYP_AES_GCM_GMAC:
      
      /* AES GCM encryption */  
      status = CRYP_AESGCM_Process_IT (hcryp) ;  
      break;
      
    case CRYP_AES_CCM:
      
      /* AES CCM encryption */  
      status = CRYP_AESCCM_Process_IT(hcryp); 
      break;
      
    default:
      hcryp->ErrorCode |= HAL_CRYP_ERROR_NOT_SUPPORTED;
      status =  HAL_ERROR;
      break;
    }
#endif /*end AES or CRYP*/ 
    
  }
  else
  {
    /* Busy error code field */
    hcryp->ErrorCode |= HAL_CRYP_ERROR_BUSY; 
    status =  HAL_ERROR;
  } 
  
  /* Return function status */
  return status;  
}

/**
  * @brief  Decryption in itnterrupt mode.
  * @param  hcryp: pointer to a CRYP_HandleTypeDef structure that contains
  *         the configuration information for CRYP module
  * @param  Input: Pointer to the input buffer (ciphertext )
  * @param  Size: Length of the plaintext buffer in word.
  * @param  Output: Pointer to the output buffer(plaintext)
  * @retval HAL status
  */
HAL_StatusTypeDef HAL_CRYP_Decrypt_IT(CRYP_HandleTypeDef *hcryp, uint32_t *Input, uint16_t Size, uint32_t *Output)
{
  uint32_t algo;
  HAL_StatusTypeDef status = HAL_OK;
  
  if(hcryp->State == HAL_CRYP_STATE_READY)
  {  
    /* Change state Busy */
    hcryp->State = HAL_CRYP_STATE_BUSY;
    
    /* Process locked */
    __HAL_LOCK(hcryp);  
    
    /*  Reset CrypInCount, CrypOutCount and Initialize pCrypInBuffPtr and pCrypOutBuffPtr parameters*/
    hcryp->CrypInCount = 0U;
    hcryp->CrypOutCount = 0U;
    hcryp->pCrypInBuffPtr = Input;
    hcryp->pCrypOutBuffPtr = Output;
    
    /*  Calculate Size parameter in Byte*/
    if (hcryp->Init.DataWidthUnit == CRYP_DATAWIDTHUNIT_WORD)
    {
      hcryp->Size = Size * 4U;
    }
    else
    {
      hcryp->Size = Size;	
    }
    
#if defined (CRYP)
    
    /* Set decryption operating mode*/
    MODIFY_REG(hcryp->Instance->CR, CRYP_CR_ALGODIR,CRYP_OPERATINGMODE_DECRYPT);
    
    /* algo get algorithm selected */     
    algo = hcryp->Instance->CR & CRYP_CR_ALGOMODE;
    
    switch(algo)
    {    
    case CRYP_DES_ECB:
    case CRYP_DES_CBC:
    case CRYP_TDES_ECB:
    case CRYP_TDES_CBC:
      
      /*Set Key */
      hcryp->Instance->K1LR = *(uint32_t*)(hcryp->Init.pKey);
      hcryp->Instance->K1RR = *(uint32_t*)(hcryp->Init.pKey+1);
      if ((hcryp->Init.Algorithm == CRYP_TDES_ECB) || (hcryp->Init.Algorithm == CRYP_TDES_CBC))
      {
        hcryp->Instance->K2LR = *(uint32_t*)(hcryp->Init.pKey+2);
        hcryp->Instance->K2RR = *(uint32_t*)(hcryp->Init.pKey+3);
        hcryp->Instance->K3LR = *(uint32_t*)(hcryp->Init.pKey+4);
        hcryp->Instance->K3RR = *(uint32_t*)(hcryp->Init.pKey+5);  
      }
      
      /* Set the Initialization Vector*/
      if ((hcryp->Init.Algorithm == CRYP_DES_CBC) || (hcryp->Init.Algorithm == CRYP_TDES_CBC))
      {
        hcryp->Instance->IV0LR = *(uint32_t*)(hcryp->Init.pInitVect);
        hcryp->Instance->IV0RR = *(uint32_t*)(hcryp->Init.pInitVect+1);
      }
      /* Flush FIFO */
      HAL_CRYP_FIFO_FLUSH(hcryp);
      
      /* Set the phase */
      hcryp->Phase = CRYP_PHASE_PROCESS;
      
      /* Enable interrupts */
      __HAL_CRYP_ENABLE_IT(hcryp, CRYP_IT_INI | CRYP_IT_OUTI);
      
      /* Enable CRYP and start DES/TDES process*/
      __HAL_CRYP_ENABLE(hcryp); 
      
      break;
      
    case CRYP_AES_ECB:
    case CRYP_AES_CBC:
    case CRYP_AES_CTR:
      
      /* AES decryption */ 
      status = CRYP_AES_Decrypt_IT(hcryp);
      break;   
      
    case CRYP_AES_GCM:
      
      /* AES GCM decryption */ 
      status = CRYP_AESGCM_Process_IT (hcryp) ;
      break;
      
    case CRYP_AES_CCM:
      
      /* AES CCMdecryption */ 
      status = CRYP_AESCCM_Process_IT(hcryp);  
      break;
      
    default:
      hcryp->ErrorCode |= HAL_CRYP_ERROR_NOT_SUPPORTED;
      status =  HAL_ERROR;
      break; 
    }
    
#else /*AES*/
    
    /* Set decryption operating mode*/
    MODIFY_REG(hcryp->Instance->CR, AES_CR_MODE, CRYP_OPERATINGMODE_DECRYPT); 
    
    /* algo get algorithm selected */  
    algo = hcryp->Instance->CR & AES_CR_CHMOD;
    
    switch(algo)
    {        
    case CRYP_AES_ECB:
    case CRYP_AES_CBC:
    case CRYP_AES_CTR:
      
      /* AES decryption */ 
      status = CRYP_AES_Decrypt_IT(hcryp);
      break;   
      
    case CRYP_AES_GCM_GMAC:
      
      /* AES GCM decryption */ 
      status = CRYP_AESGCM_Process_IT (hcryp) ;    
      break;
      
    case CRYP_AES_CCM:
      
      /* AES CCM decryption */ 
      status = CRYP_AESCCM_Process_IT(hcryp); 
      break;
      
    default:
      hcryp->ErrorCode |= HAL_CRYP_ERROR_NOT_SUPPORTED;
      status =  HAL_ERROR;
      break;
    }
#endif /* End AES or CRYP */  
    
  }
  else
  {
    /* Busy error code field */
    hcryp->ErrorCode |= HAL_CRYP_ERROR_BUSY; 
    status =  HAL_ERROR;
  } 
  
  /* Return function status */
  return status;  
}

/**
  * @brief  Encryption in DMA mode.
  * @param  hcryp: pointer to a CRYP_HandleTypeDef structure that contains
  *         the configuration information for CRYP module
  * @param  Input: Pointer to the input buffer (plaintext)
  * @param  Size: Length of the plaintext buffer in word.
  * @param  Output: Pointer to the output buffer(ciphertext)
  * @retval HAL status
  */
HAL_StatusTypeDef HAL_CRYP_Encrypt_DMA(CRYP_HandleTypeDef *hcryp, uint32_t *Input, uint16_t Size, uint32_t *Output)
{
  uint32_t algo; 
  HAL_StatusTypeDef status = HAL_OK;
  
  if(hcryp->State == HAL_CRYP_STATE_READY)
  {
    /* Change state Busy */
    hcryp->State = HAL_CRYP_STATE_BUSY;
    
    /* Process locked */
    __HAL_LOCK(hcryp);
    
    /*  Reset CrypInCount, CrypOutCount and Initialize pCrypInBuffPtr and pCrypOutBuffPtr parameters*/
    hcryp->CrypInCount = 0U;
    hcryp->CrypOutCount = 0U;
    hcryp->pCrypInBuffPtr = Input;
    hcryp->pCrypOutBuffPtr = Output;
    
    /*  Calculate Size parameter in Byte*/
    if (hcryp->Init.DataWidthUnit == CRYP_DATAWIDTHUNIT_WORD)
    {
      hcryp->Size = Size * 4U;
    }
    else
    {
      hcryp->Size = Size;	
    }
    
#if defined (CRYP)
    
    /* Set encryption operating mode*/   
    MODIFY_REG(hcryp->Instance->CR, CRYP_CR_ALGODIR, CRYP_OPERATINGMODE_ENCRYPT); 
    
    /* algo get algorithm selected */  
    algo = hcryp->Instance->CR & CRYP_CR_ALGOMODE;
    
    switch(algo)
    {    
    case CRYP_DES_ECB:
    case CRYP_DES_CBC:
    case CRYP_TDES_ECB:
    case CRYP_TDES_CBC:
      
      /*Set Key */
      hcryp->Instance->K1LR = *(uint32_t*)(hcryp->Init.pKey);
      hcryp->Instance->K1RR = *(uint32_t*)(hcryp->Init.pKey+1);
      if ((hcryp->Init.Algorithm == CRYP_TDES_ECB) || (hcryp->Init.Algorithm == CRYP_TDES_CBC))
      {
        hcryp->Instance->K2LR = *(uint32_t*)(hcryp->Init.pKey+2);
        hcryp->Instance->K2RR = *(uint32_t*)(hcryp->Init.pKey+3);
        hcryp->Instance->K3LR = *(uint32_t*)(hcryp->Init.pKey+4);
        hcryp->Instance->K3RR = *(uint32_t*)(hcryp->Init.pKey+5);  
      }
      
      /* Set the Initialization Vector*/
      if ((hcryp->Init.Algorithm == CRYP_DES_CBC) || (hcryp->Init.Algorithm == CRYP_TDES_CBC))
      {
        hcryp->Instance->IV0LR = *(uint32_t*)(hcryp->Init.pInitVect);
        hcryp->Instance->IV0RR = *(uint32_t*)(hcryp->Init.pInitVect+1);
      }
      
      /* Flush FIFO */
      HAL_CRYP_FIFO_FLUSH(hcryp);
      
      /* Set the phase */
      hcryp->Phase = CRYP_PHASE_PROCESS;
      
      /* Start DMA process transfer for DES/TDES */ 
      CRYP_SetDMAConfig(hcryp, (uint32_t)( hcryp->pCrypInBuffPtr), ((uint16_t)(hcryp->Size)/4U), (uint32_t)(hcryp->pCrypOutBuffPtr));     
      break;
      
    case CRYP_AES_ECB:
    case CRYP_AES_CBC:
    case CRYP_AES_CTR:
      
      /*  Set the Key*/
      CRYP_SetKey(hcryp, hcryp->Init.KeySize);
      
      /* Set the Initialization Vector IV */
      if (hcryp->Init.Algorithm != CRYP_AES_ECB)
      {
        hcryp->Instance->IV0LR = *(uint32_t*)(hcryp->Init.pInitVect);
        hcryp->Instance->IV0RR = *(uint32_t*)(hcryp->Init.pInitVect+1);
        hcryp->Instance->IV1LR = *(uint32_t*)(hcryp->Init.pInitVect+2);
        hcryp->Instance->IV1RR = *(uint32_t*)(hcryp->Init.pInitVect+3);
      }     
      /* Set the phase */
      hcryp->Phase = CRYP_PHASE_PROCESS;  
      
      /* Start DMA process transfer for AES */ 
      CRYP_SetDMAConfig(hcryp, (uint32_t)( hcryp->pCrypInBuffPtr), ((uint16_t)(hcryp->Size)/4U), (uint32_t)(hcryp->pCrypOutBuffPtr));            
      break;   
      
    case CRYP_AES_GCM:    
      /* AES GCM encryption */ 
      status = CRYP_AESGCM_Process_DMA (hcryp) ;  
      break;
      
    case CRYP_AES_CCM:      
      /* AES CCM encryption */ 
      status = CRYP_AESCCM_Process_DMA(hcryp);       
      break;
      
    default:
      hcryp->ErrorCode |= HAL_CRYP_ERROR_NOT_SUPPORTED;
      status =  HAL_ERROR;
      break;
    }
    
#else /*AES*/ 
    /* Set encryption operating mode*/
    MODIFY_REG(hcryp->Instance->CR, AES_CR_MODE, CRYP_OPERATINGMODE_ENCRYPT); 
    
    /* algo get algorithm selected */  
    algo = hcryp->Instance->CR & AES_CR_CHMOD;
    
    switch(algo)
    {    
      
    case CRYP_AES_ECB:
    case CRYP_AES_CBC:
    case CRYP_AES_CTR:
      
      /*  Set the Key*/
      CRYP_SetKey(hcryp, hcryp->Init.KeySize);
      
      /* Set the Initialization Vector*/ 
      if (hcryp->Init.Algorithm != CRYP_AES_ECB)
      {   
        hcryp->Instance->IVR3 = *(uint32_t*)(hcryp->Init.pInitVect);
        hcryp->Instance->IVR2 = *(uint32_t*)(hcryp->Init.pInitVect+1);
        hcryp->Instance->IVR1 = *(uint32_t*)(hcryp->Init.pInitVect+2);
        hcryp->Instance->IVR0 = *(uint32_t*)(hcryp->Init.pInitVect+3);
      }
      
      /* Set the phase */
      hcryp->Phase = CRYP_PHASE_PROCESS;
      
      /* Start DMA process transfer for AES */ 
      CRYP_SetDMAConfig(hcryp, (uint32_t)( hcryp->pCrypInBuffPtr), (hcryp->Size/4U), (uint32_t)(hcryp->pCrypOutBuffPtr));    
      break;   
      
    case CRYP_AES_GCM_GMAC:     
      /* AES GCM encryption */ 
      status = CRYP_AESGCM_Process_DMA (hcryp) ;    
      break;
      
    case CRYP_AES_CCM:      
      /* AES CCM encryption */ 
      status = CRYP_AESCCM_Process_DMA(hcryp);      
      break;
      
    default:
      hcryp->ErrorCode |= HAL_CRYP_ERROR_NOT_SUPPORTED;
      status =  HAL_ERROR;
      break;
    }
#endif /* End AES or CRYP */  
    
  }
  else
  {
    /* Busy error code field */
    hcryp->ErrorCode |= HAL_CRYP_ERROR_BUSY; 
    status =  HAL_ERROR;
  } 
  
  /* Return function status */
  return status;  
}

/**
  * @brief  Decryption in DMA mode.
  * @param  hcryp: pointer to a CRYP_HandleTypeDef structure that contains
  *         the configuration information for CRYP module
  * @param  Input: Pointer to the input buffer (ciphertext )
  * @param  Size: Length of the plaintext buffer in word
  * @param  Output: Pointer to the output buffer(plaintext)
  * @retval HAL status
  */
HAL_StatusTypeDef HAL_CRYP_Decrypt_DMA(CRYP_HandleTypeDef *hcryp, uint32_t *Input, uint16_t Size, uint32_t *Output)
{
  uint32_t algo; 
  HAL_StatusTypeDef status = HAL_OK;
   
  if(hcryp->State == HAL_CRYP_STATE_READY)
  {
    
    /* Change state Busy */
    hcryp->State = HAL_CRYP_STATE_BUSY;
    
    /* Process locked */
    __HAL_LOCK(hcryp); 
    
    /*  Reset CrypInCount, CrypOutCount and Initialize pCrypInBuffPtr, pCrypOutBuffPtr and Size parameters*/
    hcryp->CrypInCount = 0U;
    hcryp->CrypOutCount = 0U;
    hcryp->pCrypInBuffPtr = Input;
    hcryp->pCrypOutBuffPtr = Output;
    
    /*  Calculate Size parameter in Byte*/
    if (hcryp->Init.DataWidthUnit == CRYP_DATAWIDTHUNIT_WORD)
    {
      hcryp->Size = Size * 4U;
    }
    else
    {
      hcryp->Size = Size;	
    }    
    
#if defined (CRYP)
    
    /* Set decryption operating mode*/
    MODIFY_REG(hcryp->Instance->CR, CRYP_CR_ALGODIR, CRYP_OPERATINGMODE_DECRYPT);
    
    /* algo get algorithm selected */   
    algo = hcryp->Instance->CR & CRYP_CR_ALGOMODE;
    
    switch(algo)
    {    
    case CRYP_DES_ECB:
    case CRYP_DES_CBC:
    case CRYP_TDES_ECB:
    case CRYP_TDES_CBC:
      
      /*Set Key */
      hcryp->Instance->K1LR = *(uint32_t*)(hcryp->Init.pKey);
      hcryp->Instance->K1RR = *(uint32_t*)(hcryp->Init.pKey+1);
      if ((hcryp->Init.Algorithm == CRYP_TDES_ECB) || (hcryp->Init.Algorithm == CRYP_TDES_CBC))
      {
        hcryp->Instance->K2LR = *(uint32_t*)(hcryp->Init.pKey+2);
        hcryp->Instance->K2RR = *(uint32_t*)(hcryp->Init.pKey+3);
        hcryp->Instance->K3LR = *(uint32_t*)(hcryp->Init.pKey+4);
        hcryp->Instance->K3RR = *(uint32_t*)(hcryp->Init.pKey+5);  
      }
      
      /* Set the Initialization Vector*/
      if ((hcryp->Init.Algorithm == CRYP_DES_CBC) || (hcryp->Init.Algorithm == CRYP_TDES_CBC))
      {
        hcryp->Instance->IV0LR = *(uint32_t*)(hcryp->Init.pInitVect);
        hcryp->Instance->IV0RR = *(uint32_t*)(hcryp->Init.pInitVect+1);
      }
      
      /* Flush FIFO */
      HAL_CRYP_FIFO_FLUSH(hcryp);
      
      /* Set the phase */
      hcryp->Phase = CRYP_PHASE_PROCESS;
      
      /* Start DMA process transfer for DES/TDES */ 
      CRYP_SetDMAConfig(hcryp, (uint32_t)( hcryp->pCrypInBuffPtr), ((uint16_t)(hcryp->Size)/4U), (uint32_t)(hcryp->pCrypOutBuffPtr));      
      break;
      
    case CRYP_AES_ECB:
    case CRYP_AES_CBC:
    case CRYP_AES_CTR:
      
      /* AES decryption */ 
      status = CRYP_AES_Decrypt_DMA(hcryp);
      break;   
      
    case CRYP_AES_GCM:     
      /* AES GCM decryption */ 
      status = CRYP_AESGCM_Process_DMA (hcryp) ;    
      break;
      
    case CRYP_AES_CCM:      
      /* AES CCM decryption */ 
      status = CRYP_AESCCM_Process_DMA(hcryp);       
      break;
      
    default:
      hcryp->ErrorCode |= HAL_CRYP_ERROR_NOT_SUPPORTED;
      status =  HAL_ERROR;
      break;
    }
    
#else /*AES*/
    
    /* Set decryption operating mode*/
    MODIFY_REG(hcryp->Instance->CR, AES_CR_MODE, CRYP_OPERATINGMODE_DECRYPT);
    
    /* algo get algorithm selected */  
    algo = hcryp->Instance->CR & AES_CR_CHMOD;
    
    switch(algo)
    {    
      
    case CRYP_AES_ECB:
    case CRYP_AES_CBC:
    case CRYP_AES_CTR:
      
      /* AES decryption */ 
      status = CRYP_AES_Decrypt_DMA(hcryp);
      break;   
      
    case CRYP_AES_GCM_GMAC:     
      /* AES GCM decryption */ 
      status = CRYP_AESGCM_Process_DMA (hcryp) ;       
      break;
      
    case CRYP_AES_CCM:     
      /* AES CCM decryption */ 
      status = CRYP_AESCCM_Process_DMA(hcryp);       
      break;
      
    default:
      hcryp->ErrorCode |= HAL_CRYP_ERROR_NOT_SUPPORTED;
      status =  HAL_ERROR;
      break;
    }
#endif /* End AES or CRYP */           
  }
  else
  {
    /* Busy error code field */
    hcryp->ErrorCode |= HAL_CRYP_ERROR_BUSY; 
    status =  HAL_ERROR;
  }
  
  /* Return function status */
  return status;  
}

/**
  * @}
  */

/** @defgroup CRYP_Exported_Functions_Group3 CRYP IRQ handler management  
 *  @brief   CRYP IRQ handler.
 *
@verbatim   
  ==============================================================================
                ##### CRYP IRQ handler management #####
  ==============================================================================  
[..]  This section provides CRYP IRQ handler and callback functions.
      (+) HAL_CRYP_IRQHandler CRYP interrupt request
      (+) HAL_CRYP_InCpltCallback input data transfer complete callback
      (+) HAL_CRYP_OutCpltCallback output data transfer complete callback
      (+) HAL_CRYP_ErrorCallback  CRYP error callback
      (+) HAL_CRYP_GetState return the CRYP state 
      (+) HAL_CRYP_GetError return the CRYP error code
@endverbatim
  * @{
  */

/**
  * @brief  This function handles cryptographic interrupt request.
  * @param  hcryp: pointer to a CRYP_HandleTypeDef structure that contains
  *         the configuration information for CRYP module
  * @retval None
  */
void HAL_CRYP_IRQHandler(CRYP_HandleTypeDef *hcryp)
{
  
#if defined (CRYP)
  
  if((__HAL_CRYP_GET_IT(hcryp, CRYP_IT_INI) != 0x0U) || (__HAL_CRYP_GET_IT(hcryp, CRYP_IT_OUTI) != 0x0U))
  {
    if ((hcryp->Init.Algorithm == CRYP_DES_ECB)|| (hcryp->Init.Algorithm == CRYP_DES_CBC) || (hcryp->Init.Algorithm == CRYP_TDES_ECB) || (hcryp->Init.Algorithm == CRYP_TDES_CBC))
    {
      CRYP_TDES_IT(hcryp); /* DES or TDES*/
    }
    else if((hcryp->Init.Algorithm == CRYP_AES_ECB) || (hcryp->Init.Algorithm == CRYP_AES_CBC) || (hcryp->Init.Algorithm == CRYP_AES_CTR))
    {
      CRYP_AES_IT(hcryp); /*AES*/
    }
    
    else if((hcryp->Init.Algorithm == CRYP_AES_GCM) ||(hcryp->Init.Algorithm == CRYP_CR_ALGOMODE_AES_CCM) )
    {
      /* if header phase */
      if ((hcryp->Instance->CR & CRYP_PHASE_HEADER) == CRYP_PHASE_HEADER )
      {
        CRYP_GCMCCM_SetHeaderPhase_IT(hcryp);
      }     
      else  /* if payload phase */         
      {
        CRYP_GCMCCM_SetPayloadPhase_IT(hcryp);
      }
    }
    
    else
    {
      /* Nothing to do */
    }
  } 
  
#else /*AES*/ 
  if((__HAL_CRYP_GET_FLAG(hcryp,CRYP_IT_CCF) != 0x0U) && (__HAL_CRYP_GET_IT_SOURCE(hcryp,CRYP_IT_CCFIE) != 0x0U))
  {
    
    /* Clear computation complete flag */
    __HAL_CRYP_CLEAR_FLAG(hcryp,CRYP_CCF_CLEAR);
    
    if(hcryp->Init.Algorithm == CRYP_AES_GCM_GMAC)
    {
      
      /* if header phase */
      if ((hcryp->Instance->CR & CRYP_PHASE_HEADER) == CRYP_PHASE_HEADER )
      {
        CRYP_GCMCCM_SetHeaderPhase_IT(hcryp);
      }    
      else  /* if payload phase */    
      {
        CRYP_GCMCCM_SetPayloadPhase_IT(hcryp);
      }
    }
    else if(hcryp->Init.Algorithm == CRYP_AES_CCM)
    {
      /* if header phase */
      if (hcryp->Init.HeaderSize >=  hcryp->CrypHeaderCount )
      {
        CRYP_GCMCCM_SetHeaderPhase_IT(hcryp);
      }    
      else   /* if payload phase */  
      {
        CRYP_GCMCCM_SetPayloadPhase_IT(hcryp);
      }
    }    
    else  /* AES Algorithm ECB,CBC or CTR*/
    {
      CRYP_AES_IT(hcryp);
    }
  }    
  /* Check if error occurred */
  if (__HAL_CRYP_GET_IT_SOURCE(hcryp,CRYP_IT_ERRIE) != RESET)
  {
    /* If write Error occurred */
    if (__HAL_CRYP_GET_FLAG(hcryp,CRYP_IT_WRERR) != RESET)
    {
      hcryp->ErrorCode |= HAL_CRYP_ERROR_WRITE;
    }
    /* If read Error occurred */
    if (__HAL_CRYP_GET_FLAG(hcryp,CRYP_IT_RDERR) != RESET)
    {
      hcryp->ErrorCode |= HAL_CRYP_ERROR_READ;
    }
  }
#endif /* End AES or CRYP */     
}

/**
  * @brief  Return the CRYP error code.
  * @param  hcryp : pointer to a CRYP_HandleTypeDef structure that contains
  *                 the configuration information for the  CRYP IP
  * @retval CRYP error code
  */
uint32_t HAL_CRYP_GetError(CRYP_HandleTypeDef *hcryp)
{
  return hcryp->ErrorCode;
}

/**
  * @brief  Returns the CRYP state.
  * @param  hcryp: pointer to a CRYP_HandleTypeDef structure that contains
  *         the configuration information for CRYP module.
  * @retval HAL state
  */
HAL_CRYP_STATETypeDef HAL_CRYP_GetState(CRYP_HandleTypeDef *hcryp)
{
  return hcryp->State;
}

/**
  * @brief  Input FIFO transfer completed callback.
  * @param  hcryp: pointer to a CRYP_HandleTypeDef structure that contains
  *         the configuration information for CRYP module.
  * @retval None
  */
__weak void HAL_CRYP_InCpltCallback(CRYP_HandleTypeDef *hcryp)
{
  /* Prevent unused argument(s) compilation warning */
  UNUSED(hcryp);
 
  /* NOTE : This function Should not be modified, when the callback is needed,
            the HAL_CRYP_InCpltCallback could be implemented in the user file
   */ 
}

/**
  * @brief  Output FIFO transfer completed callback.
  * @param  hcryp: pointer to a CRYP_HandleTypeDef structure that contains
  *         the configuration information for CRYP module.
  * @retval None
  */
__weak void HAL_CRYP_OutCpltCallback(CRYP_HandleTypeDef *hcryp)
{
  /* Prevent unused argument(s) compilation warning */
  UNUSED(hcryp);
 
  /* NOTE : This function Should not be modified, when the callback is needed,
            the HAL_CRYP_OutCpltCallback could be implemented in the user file
   */
}

/**
  * @brief  CRYP error callback.
  * @param  hcryp: pointer to a CRYP_HandleTypeDef structure that contains
  *         the configuration information for CRYP module.
  * @retval None
  */
 __weak void HAL_CRYP_ErrorCallback(CRYP_HandleTypeDef *hcryp)
{
  /* Prevent unused argument(s) compilation warning */
  UNUSED(hcryp);
 
  /* NOTE : This function Should not be modified, when the callback is needed,
            the HAL_CRYP_ErrorCallback could be implemented in the user file
   */ 
}
/**
  * @}
  */

/* Private functions ---------------------------------------------------------*/
/** @addtogroup CRYP_Private_Functions
  * @{
  */

 #if defined (CRYP)

/**
  * @brief  Encryption in ECB/CBC Algorithm with DES/TDES standard.
  * @param  hcryp: pointer to a CRYP_HandleTypeDef structure that contains
  *         the configuration information for CRYP module 
  * @param  Timeout: specify Timeout value 
  * @retval HAL status
  */
static HAL_StatusTypeDef CRYP_TDES_Process(CRYP_HandleTypeDef *hcryp, uint32_t Timeout)
{
  uint32_t temp;  /* Temporary CrypOutBuff */  
  uint16_t incount; /* Temporary CrypInCount Value */ 
  uint16_t outcount;  /* Temporary CrypOutCount Value */
  
  /* Enable CRYP */
  __HAL_CRYP_ENABLE(hcryp);
  /*Temporary CrypOutCount Value*/
  outcount = hcryp->CrypOutCount;
  
  /*Start processing*/  
  while((hcryp->CrypInCount < (hcryp->Size/4U)) && (outcount < (hcryp->Size/4U)))
  { 
    /* Temporary CrypInCount Value */ 
    incount = hcryp->CrypInCount;      
    /* Write plain data and get cipher data */
    if(((hcryp->Instance->SR & CRYP_FLAG_IFNF ) != 0x0U) && (incount < (hcryp->Size/4U)))
    {
      /* Write the input block in the IN FIFO */
      hcryp->Instance->DIN  = *(uint32_t *)(hcryp->pCrypInBuffPtr + hcryp->CrypInCount );
      hcryp->CrypInCount++;
      hcryp->Instance->DIN  = *(uint32_t *)(hcryp->pCrypInBuffPtr + hcryp->CrypInCount );
      hcryp->CrypInCount++;        
    }   
    
    /* Wait for OFNE flag to be raised */
    if(CRYP_WaitOnOFNEFlag(hcryp, Timeout) != HAL_OK)  
    { 
      /* Disable the CRYP peripheral clock */
      __HAL_CRYP_DISABLE(hcryp);
      
      /* Change state & errorCode*/
      hcryp->ErrorCode |= HAL_CRYP_ERROR_TIMEOUT;
      hcryp->State = HAL_CRYP_STATE_READY;
      
      /* Process unlocked */          
      __HAL_UNLOCK(hcryp); 
#if (USE_HAL_CRYP_REGISTER_CALLBACKS == 1) 
      /*Call registered error callback*/
      hcryp->ErrorCallback(hcryp);
#else
      /*Call legacy weak error callback*/
      HAL_CRYP_ErrorCallback(hcryp);
#endif /* USE_HAL_CRYP_REGISTER_CALLBACKS */ 
    }
    
    /*Temporary CrypOutCount Value*/
    outcount = hcryp->CrypOutCount;
    
    if(((hcryp->Instance->SR & CRYP_FLAG_OFNE ) != 0x0U) && (outcount < (hcryp->Size/4U)))
    {
      /* Read the output block from the Output FIFO and put them in temporary Buffer then get CrypOutBuff from temporary buffer  */    
      temp = hcryp->Instance->DOUT;
      *(uint32_t *)(hcryp->pCrypOutBuffPtr + (hcryp->CrypOutCount)) = temp;      
      hcryp->CrypOutCount++;  
      temp = hcryp->Instance->DOUT;  
      *(uint32_t *)(hcryp->pCrypOutBuffPtr + (hcryp->CrypOutCount)) = temp;      
      hcryp->CrypOutCount++;  
    }
    /*Temporary CrypOutCount Value*/
    outcount = hcryp->CrypOutCount;
  }
  /* Disable CRYP */
  __HAL_CRYP_DISABLE(hcryp); 
  /* Change the CRYP state */
  hcryp->State = HAL_CRYP_STATE_READY;
  
  /* Return function status */
  return HAL_OK;  
}

/** 
  * @brief  CRYP block input/output data handling under interruption with DES/TDES standard.
  * @note   The function is called under interruption only, once
  *         interruptions have been enabled by CRYP_Decrypt_IT() and CRYP_Encrypt_IT().
  * @param  hcryp: pointer to a CRYP_HandleTypeDef structure that contains
  *         the configuration information for CRYP module.
  * @retval none
  */
static void CRYP_TDES_IT(CRYP_HandleTypeDef *hcryp)
{
  uint32_t temp;  /* Temporary CrypOutBuff */ 
  
  if(hcryp->State == HAL_CRYP_STATE_BUSY)
  { 
    if((__HAL_CRYP_GET_IT(hcryp, CRYP_IT_INI) != 0x0U) && (__HAL_CRYP_GET_FLAG(hcryp, CRYP_FLAG_INRIS) != 0x0U))
      
    {     
      /* Write input block in the IN FIFO */
      hcryp->Instance->DIN = *(uint32_t *)(hcryp->pCrypInBuffPtr + hcryp->CrypInCount );
      hcryp->CrypInCount++;
      hcryp->Instance->DIN = *(uint32_t *)(hcryp->pCrypInBuffPtr + hcryp->CrypInCount );
      hcryp->CrypInCount++;
      
      if(hcryp->CrypInCount ==  ((uint16_t)(hcryp->Size)/4U))
      {     
        /* Disable interruption */
        __HAL_CRYP_DISABLE_IT(hcryp, CRYP_IT_INI);
        /* Call the input data transfer complete callback */
#if (USE_HAL_CRYP_REGISTER_CALLBACKS == 1U) 
        /*Call registered Input complete callback*/
        hcryp->InCpltCallback(hcryp);
#else
        /*Call legacy weak Input complete callback*/
        HAL_CRYP_InCpltCallback(hcryp);
#endif /* USE_HAL_CRYP_REGISTER_CALLBACKS */
      }
    }
    if((__HAL_CRYP_GET_IT(hcryp, CRYP_IT_OUTI) != 0x0U)&& (__HAL_CRYP_GET_FLAG(hcryp, CRYP_FLAG_OUTRIS) != 0x0U))
    {
      /* Read the output block from the Output FIFO and put them in temporary Buffer then get CrypOutBuff from temporary buffer  */    
      temp = hcryp->Instance->DOUT;
      *(uint32_t *)(hcryp->pCrypOutBuffPtr + (hcryp->CrypOutCount)) = temp;      
      hcryp->CrypOutCount++;  
      temp = hcryp->Instance->DOUT;  
      *(uint32_t *)(hcryp->pCrypOutBuffPtr + (hcryp->CrypOutCount)) = temp;      
      hcryp->CrypOutCount++;            
      if(hcryp->CrypOutCount ==  ((uint16_t)(hcryp->Size)/4U))
      {
        /* Disable interruption */
        __HAL_CRYP_DISABLE_IT(hcryp, CRYP_IT_OUTI);
        
        /* Disable CRYP */
        __HAL_CRYP_DISABLE(hcryp);
        
        /* Process unlocked */
        __HAL_UNLOCK(hcryp);   
        
        /* Change the CRYP state */
        hcryp->State = HAL_CRYP_STATE_READY;
        /* Call output transfer complete callback */
#if (USE_HAL_CRYP_REGISTER_CALLBACKS == 1) 
        /*Call registered Output complete callback*/
        hcryp->OutCpltCallback(hcryp);
#else
        /*Call legacy weak Output complete callback*/
        HAL_CRYP_OutCpltCallback(hcryp);
#endif /* USE_HAL_CRYP_REGISTER_CALLBACKS */  
      }
    }   
  }
  else
  {
    /* Process unlocked */
    __HAL_UNLOCK(hcryp);     
    /* Busy error code field */
    hcryp->ErrorCode |= HAL_CRYP_ERROR_BUSY; 
#if (USE_HAL_CRYP_REGISTER_CALLBACKS == 1) 
    /*Call registered error callback*/
    hcryp->ErrorCallback(hcryp);
#else
    /*Call legacy weak error callback*/
    HAL_CRYP_ErrorCallback(hcryp);
#endif /* USE_HAL_CRYP_REGISTER_CALLBACKS */
  }
}

#endif /* CRYP */

/**
  * @brief  Encryption in ECB/CBC & CTR Algorithm with AES Standard
  * @param  hcryp: pointer to a CRYP_HandleTypeDef structure 
  * @param  Timeout: specify Timeout value 
  * @retval HAL status
  */
static HAL_StatusTypeDef CRYP_AES_Encrypt(CRYP_HandleTypeDef *hcryp, uint32_t Timeout)
{  
  uint16_t outcount;  /* Temporary CrypOutCount Value */
  
  /*  Set the Key*/
  CRYP_SetKey(hcryp, hcryp->Init.KeySize);
  
  if (hcryp->Init.Algorithm != CRYP_AES_ECB)
  {
    /* Set the Initialization Vector*/
#if defined (AES)       
    hcryp->Instance->IVR3 = *(uint32_t*)(hcryp->Init.pInitVect);
    hcryp->Instance->IVR2 = *(uint32_t*)(hcryp->Init.pInitVect+1);
    hcryp->Instance->IVR1 = *(uint32_t*)(hcryp->Init.pInitVect+2);
    hcryp->Instance->IVR0 = *(uint32_t*)(hcryp->Init.pInitVect+3);
#else /* CRYP */
    hcryp->Instance->IV0LR = *(uint32_t*)(hcryp->Init.pInitVect);
    hcryp->Instance->IV0RR = *(uint32_t*)(hcryp->Init.pInitVect+1);
    hcryp->Instance->IV1LR = *(uint32_t*)(hcryp->Init.pInitVect+2);
    hcryp->Instance->IV1RR = *(uint32_t*)(hcryp->Init.pInitVect+3);
#endif /* End AES or CRYP */
  }
  
  /* Set the phase */
  hcryp->Phase = CRYP_PHASE_PROCESS;
  
  /* Enable CRYP */
  __HAL_CRYP_ENABLE(hcryp);
  
  /*Temporary CrypOutCount Value*/
  outcount = hcryp->CrypOutCount;
  
  while((hcryp->CrypInCount < (hcryp->Size/4U)) && (outcount < (hcryp->Size/4U)))
  {      
    /* Write plain Ddta and get cipher data */
    CRYP_AES_ProcessData(hcryp,Timeout); 
    /*Temporary CrypOutCount Value*/
    outcount = hcryp->CrypOutCount;     
  } 
  
  /* Disable CRYP */
  __HAL_CRYP_DISABLE(hcryp);
  
  /* Change the CRYP state */
  hcryp->State = HAL_CRYP_STATE_READY;
  
  /* Return function status */
  return HAL_OK;   
}

/**
  * @brief  Encryption in ECB/CBC & CTR mode with AES Standard using interrupt mode
  * @param  hcryp: pointer to a CRYP_HandleTypeDef structure that contains
  *         the configuration information for CRYP module
  * @retval HAL status
  */
static HAL_StatusTypeDef CRYP_AES_Encrypt_IT(CRYP_HandleTypeDef *hcryp)
{   
  
  /*  Set the Key*/
  CRYP_SetKey(hcryp, hcryp->Init.KeySize);
  
  if (hcryp->Init.Algorithm != CRYP_AES_ECB)
  {
    /* Set the Initialization Vector*/
#if defined (AES)  
    hcryp->Instance->IVR3 = *(uint32_t*)(hcryp->Init.pInitVect);
    hcryp->Instance->IVR2 = *(uint32_t*)(hcryp->Init.pInitVect+1);
    hcryp->Instance->IVR1 = *(uint32_t*)(hcryp->Init.pInitVect+2);
    hcryp->Instance->IVR0 = *(uint32_t*)(hcryp->Init.pInitVect+3);
    
#else /* CRYP */
    hcryp->Instance->IV0LR = *(uint32_t*)(hcryp->Init.pInitVect);
    hcryp->Instance->IV0RR = *(uint32_t*)(hcryp->Init.pInitVect+1);
    hcryp->Instance->IV1LR = *(uint32_t*)(hcryp->Init.pInitVect+2);
    hcryp->Instance->IV1RR = *(uint32_t*)(hcryp->Init.pInitVect+3);
#endif /* End AES or CRYP */
  }
  /* Set the phase */
  hcryp->Phase = CRYP_PHASE_PROCESS;
  
  if(hcryp->Size != 0U)
  {    
#if defined (AES) 
    
    /* Enable computation complete flag and error interrupts */
    __HAL_CRYP_ENABLE_IT(hcryp,CRYP_IT_CCFIE | CRYP_IT_ERRIE);
    
    /* Enable CRYP */
    __HAL_CRYP_ENABLE(hcryp);
    
    /* Write the input block in the IN FIFO */
    hcryp->Instance->DINR  = *(uint32_t *)(hcryp->pCrypInBuffPtr + hcryp->CrypInCount );
    hcryp->CrypInCount++;
    hcryp->Instance->DINR  = *(uint32_t *)(hcryp->pCrypInBuffPtr + hcryp->CrypInCount );
    hcryp->CrypInCount++;   
    hcryp->Instance->DINR  = *(uint32_t *)(hcryp->pCrypInBuffPtr + hcryp->CrypInCount );
    hcryp->CrypInCount++;
    hcryp->Instance->DINR  = *(uint32_t *)(hcryp->pCrypInBuffPtr + hcryp->CrypInCount );
    hcryp->CrypInCount++; 
    
#else /* CRYP */  
    
    /* Enable interrupts */
    __HAL_CRYP_ENABLE_IT(hcryp, CRYP_IT_INI | CRYP_IT_OUTI);
    
    /* Enable CRYP */
    __HAL_CRYP_ENABLE(hcryp); 
    
#endif /*  End AES or CRYP  */      
  }
  else
  {  
    /* Change the CRYP state */
    hcryp->State = HAL_CRYP_STATE_READY;
    
    /* Process unlocked */
    __HAL_UNLOCK(hcryp);  
  }   
  
  /* Return function status */
  return HAL_OK;
}

/**
  * @brief  Decryption in ECB/CBC & CTR mode with AES Standard
  * @param  hcryp: pointer to a CRYP_HandleTypeDef structure 
  * @param  Timeout: Specify Timeout value 
  * @retval HAL status
  */
static HAL_StatusTypeDef CRYP_AES_Decrypt(CRYP_HandleTypeDef *hcryp, uint32_t Timeout )
{  
  uint16_t outcount;  /* Temporary CrypOutCount Value */
  
  /*  Key preparation for ECB/CBC */
  if (hcryp->Init.Algorithm != CRYP_AES_CTR) 
  {
#if defined (AES) 
    if (hcryp->AutoKeyDerivation == DISABLE)/*Mode 2 Key preparation*/
    {     
      /* Set key preparation for decryption operating mode*/
      MODIFY_REG(hcryp->Instance->CR, AES_CR_MODE, CRYP_OPERATINGMODE_KEYDERIVATION);
      
      /*  Set the Key*/
      CRYP_SetKey(hcryp, hcryp->Init.KeySize); 
      
      /* Enable CRYP */
      __HAL_CRYP_ENABLE(hcryp);
      
      /* Wait for CCF flag to be raised */
      if(CRYP_WaitOnCCFlag(hcryp, Timeout) != HAL_OK)  
      { 
        /* Disable the CRYP peripheral clock */
        __HAL_CRYP_DISABLE(hcryp);
        
        /* Change state & error code*/
        hcryp->ErrorCode |= HAL_CRYP_ERROR_TIMEOUT;
        hcryp->State = HAL_CRYP_STATE_READY;  
        
        /* Process unlocked */          
        __HAL_UNLOCK(hcryp); 
        return HAL_ERROR;
      }
      /* Clear CCF Flag */
      __HAL_CRYP_CLEAR_FLAG(hcryp, CRYP_CCF_CLEAR);
      
      /* Return to decryption operating mode(Mode 3)*/      
      MODIFY_REG(hcryp->Instance->CR, AES_CR_MODE, CRYP_OPERATINGMODE_DECRYPT);
    }
    else /*Mode 4 : decryption & Key preparation*/
    {
      /*  Set the Key*/
      CRYP_SetKey(hcryp, hcryp->Init.KeySize);
      
      /* Set decryption & Key preparation operating mode*/             
      MODIFY_REG(hcryp->Instance->CR, AES_CR_MODE, CRYP_OPERATINGMODE_KEYDERIVATION_DECRYPT);  
    }     
#else /* CRYP */
    /* change ALGOMODE to key preparation for decryption*/
    MODIFY_REG(hcryp->Instance->CR, CRYP_CR_ALGOMODE, CRYP_CR_ALGOMODE_AES_KEY );
    
    /*  Set the Key*/
    CRYP_SetKey(hcryp, hcryp->Init.KeySize);
    
    /* Enable CRYP */
    __HAL_CRYP_ENABLE(hcryp);
    
    /* Wait for BUSY flag to be raised */
    if(CRYP_WaitOnBUSYFlag(hcryp, Timeout) != HAL_OK)  
    { 
      /* Disable the CRYP peripheral clock */
      __HAL_CRYP_DISABLE(hcryp);
      
      /* Change state */
      hcryp->ErrorCode |= HAL_CRYP_ERROR_TIMEOUT;
      hcryp->State = HAL_CRYP_STATE_READY;
      
      /* Process unlocked */          
      __HAL_UNLOCK(hcryp); 
      return HAL_ERROR;
    }       
    /* Turn back to ALGOMODE of the configuration */
    MODIFY_REG(hcryp->Instance->CR, CRYP_CR_ALGOMODE, hcryp->Init.Algorithm );  
    
#endif /* End AES or CRYP  */ 
  }
  else  /*Algorithm CTR */
  {  
    /*  Set the Key*/
    CRYP_SetKey(hcryp, hcryp->Init.KeySize);
  } 
  
  /* Set IV */ 
  if (hcryp->Init.Algorithm != CRYP_AES_ECB)
  {
    /* Set the Initialization Vector*/
#if defined (AES)       
    hcryp->Instance->IVR3 = *(uint32_t*)(hcryp->Init.pInitVect);
    hcryp->Instance->IVR2 = *(uint32_t*)(hcryp->Init.pInitVect+1);
    hcryp->Instance->IVR1 = *(uint32_t*)(hcryp->Init.pInitVect+2);
    hcryp->Instance->IVR0 = *(uint32_t*)(hcryp->Init.pInitVect+3);
#else /* CRYP */
    hcryp->Instance->IV0LR = *(uint32_t*)(hcryp->Init.pInitVect);
    hcryp->Instance->IV0RR = *(uint32_t*)(hcryp->Init.pInitVect+1);
    hcryp->Instance->IV1LR = *(uint32_t*)(hcryp->Init.pInitVect+2);
    hcryp->Instance->IV1RR = *(uint32_t*)(hcryp->Init.pInitVect+3);
#endif /* End AES or CRYP */
  }     
  /* Set the phase */
  hcryp->Phase = CRYP_PHASE_PROCESS;
  
  /* Enable CRYP */
  __HAL_CRYP_ENABLE(hcryp);
  
  /*Temporary CrypOutCount Value*/  
  outcount = hcryp->CrypOutCount; 
  
  while((hcryp->CrypInCount < (hcryp->Size/4U)) && (outcount < (hcryp->Size/4U)))
  {      
    /* Write plain data and get cipher data */
    CRYP_AES_ProcessData(hcryp,Timeout);
    /*Temporary CrypOutCount Value*/
    outcount = hcryp->CrypOutCount;
  }  
  
  /* Disable CRYP */
  __HAL_CRYP_DISABLE(hcryp);
  
  /* Change the CRYP state */
  hcryp->State = HAL_CRYP_STATE_READY;
  
  /* Return function status */
  return HAL_OK;   
}
/**
  * @brief  Decryption in ECB/CBC & CTR mode with AES Standard using interrupt mode
  * @param  hcryp: pointer to a CRYP_HandleTypeDef structure that contains
  *         the configuration information for CRYP module
  * @retval HAL status
  */
static HAL_StatusTypeDef CRYP_AES_Decrypt_IT(CRYP_HandleTypeDef *hcryp)
{
  __IO uint32_t count = 0U;
  
  /*  Key preparation for ECB/CBC */
  if (hcryp->Init.Algorithm != CRYP_AES_CTR) 
  {
#if defined (AES) 
    if (hcryp->AutoKeyDerivation == DISABLE)/*Mode 2 Key preparation*/
    {     
      /* Set key preparation for decryption operating mode*/
      MODIFY_REG(hcryp->Instance->CR, AES_CR_MODE, CRYP_OPERATINGMODE_KEYDERIVATION);
      
      /*  Set the Key*/
      CRYP_SetKey(hcryp, hcryp->Init.KeySize); 
      
      /* Enable CRYP */
      __HAL_CRYP_ENABLE(hcryp);
      
      /* Wait for CCF flag to be raised */
      count = CRYP_TIMEOUT_KEYPREPARATION;
      do
      {
        count-- ;
        if(count == 0U)
        {
          /* Disable the CRYP peripheral clock */
          __HAL_CRYP_DISABLE(hcryp);
          
          /* Change state */
          hcryp->ErrorCode |= HAL_CRYP_ERROR_TIMEOUT;
          hcryp->State = HAL_CRYP_STATE_READY; 
          
          /* Process unlocked */          
          __HAL_UNLOCK(hcryp); 
          return HAL_ERROR;
        }
      }
      while(HAL_IS_BIT_CLR(hcryp->Instance->SR, AES_SR_CCF));
      
      /* Clear CCF Flag */
      __HAL_CRYP_CLEAR_FLAG(hcryp, CRYP_CCF_CLEAR);
      
      /* Return to decryption operating mode(Mode 3)*/ 
      MODIFY_REG(hcryp->Instance->CR, AES_CR_MODE, CRYP_OPERATINGMODE_DECRYPT);
    }
    else /*Mode 4 : decryption & key preparation*/
    {
      /*  Set the Key*/
      CRYP_SetKey(hcryp, hcryp->Init.KeySize);
      
      /* Set decryption & key preparation operating mode*/ 
      MODIFY_REG(hcryp->Instance->CR, AES_CR_MODE, CRYP_OPERATINGMODE_KEYDERIVATION_DECRYPT); 
    }        
#else /* CRYP */
    
    /* change ALGOMODE to key preparation for decryption*/
    MODIFY_REG(hcryp->Instance->CR, CRYP_CR_ALGOMODE, CRYP_CR_ALGOMODE_AES_KEY );
    
    /*  Set the Key*/
    CRYP_SetKey(hcryp, hcryp->Init.KeySize);
>>>>>>> 49e424905b5922b07aa7166ec7a0eeb90adf58a8
    
    /* Enable CRYP */
    __HAL_CRYP_ENABLE(hcryp);
    
<<<<<<< HEAD
    /* Get tick */
    tickstart = HAL_GetTick();
    
    while(HAL_IS_BIT_SET(hcryp->Instance->SR, CRYP_FLAG_BUSY))
    {
      /* Check for the Timeout */
      if((HAL_GetTick() - tickstart ) > CRYP_TIMEOUT_VALUE)
      {
        /* Change state */
        hcryp->State = HAL_CRYP_STATE_TIMEOUT;
        
        /* Process Unlocked */
        __HAL_UNLOCK(hcryp);
        
        return HAL_TIMEOUT;
      }
    }
    
    /* Reset the ALGOMODE bits*/
    CRYP->CR &= (uint32_t)(~CRYP_CR_ALGOMODE);
    
    /* Set the CRYP peripheral in AES ECB decryption mode */
    __HAL_CRYP_SET_MODE(hcryp, CRYP_CR_ALGOMODE_AES_ECB | CRYP_CR_ALGODIR);
    
    /* Flush FIFO */
    __HAL_CRYP_FIFO_FLUSH(hcryp);
    
     /* Set the phase */
     hcryp->Phase = HAL_CRYP_PHASE_PROCESS;
    }
     
    /* Set the input and output addresses and start DMA transfer */ 
    CRYP_SetDMAConfig(hcryp, inputaddr, Size, outputaddr);
    
     /* Process Unlocked */
     __HAL_UNLOCK(hcryp);
    
    /* Return function status */
    return HAL_OK;
  }
  else
  {
    return HAL_ERROR;   
  }
}

/**
  * @brief  Initializes the CRYP peripheral in AES CBC encryption mode using DMA.
  * @param  hcryp pointer to a CRYP_HandleTypeDef structure that contains
  *         the configuration information for CRYP module
  * @param  pCypherData Pointer to the cyphertext buffer
  * @param  Size Length of the plaintext buffer, must be a multiple of 16 bytes
  * @param  pPlainData Pointer to the plaintext buffer
  * @retval HAL status
  */
HAL_StatusTypeDef HAL_CRYP_AESCBC_Decrypt_DMA(CRYP_HandleTypeDef *hcryp, uint8_t *pCypherData, uint16_t Size, uint8_t *pPlainData)
{
  uint32_t tickstart = 0;   
  uint32_t inputaddr;
  uint32_t outputaddr;
  
  if((hcryp->State == HAL_CRYP_STATE_READY) || (hcryp->Phase == HAL_CRYP_PHASE_PROCESS))
  {
    /* Process Locked */
    __HAL_LOCK(hcryp);
    
    inputaddr  = (uint32_t)pCypherData;
    outputaddr = (uint32_t)pPlainData;
    
    /* Change the CRYP state */
    hcryp->State = HAL_CRYP_STATE_BUSY;
    
    /* Check if initialization phase has already been performed */
    if(hcryp->Phase == HAL_CRYP_PHASE_READY)
    {
      /* Set the key */
      CRYP_SetKey(hcryp, hcryp->Init.pKey, hcryp->Init.KeySize);
      
      /* Set the CRYP peripheral in AES Key mode */
      __HAL_CRYP_SET_MODE(hcryp, CRYP_CR_ALGOMODE_AES_KEY | CRYP_CR_ALGODIR);
=======
    /* Wait for BUSY flag to be raised */
    count = CRYP_TIMEOUT_KEYPREPARATION;
    do
    {
      count-- ;
      if(count == 0U)
      {
        /* Change state */
        hcryp->ErrorCode |= HAL_CRYP_ERROR_TIMEOUT;
        hcryp->State = HAL_CRYP_STATE_READY;
        
        /* Process unlocked */          
        __HAL_UNLOCK(hcryp);
        return HAL_ERROR;
      }
    }
    while(HAL_IS_BIT_SET(hcryp->Instance->SR, CRYP_FLAG_BUSY));  
    
    /* Turn back to ALGOMODE of the configuration */
    MODIFY_REG(hcryp->Instance->CR, CRYP_CR_ALGOMODE, hcryp->Init.Algorithm ); 
    
#endif /* End AES or CRYP */    
  }
  
  else  /*Algorithm CTR */
  {  
    /*  Set the Key*/
    CRYP_SetKey(hcryp, hcryp->Init.KeySize);
  }    
  
  /* Set IV */ 
  if (hcryp->Init.Algorithm != CRYP_AES_ECB)
  {
    /* Set the Initialization Vector*/
#if defined (AES)       
    hcryp->Instance->IVR3 = *(uint32_t*)(hcryp->Init.pInitVect);
    hcryp->Instance->IVR2 = *(uint32_t*)(hcryp->Init.pInitVect+1);
    hcryp->Instance->IVR1 = *(uint32_t*)(hcryp->Init.pInitVect+2);
    hcryp->Instance->IVR0 = *(uint32_t*)(hcryp->Init.pInitVect+3);
#else /* CRYP */
    hcryp->Instance->IV0LR = *(uint32_t*)(hcryp->Init.pInitVect);
    hcryp->Instance->IV0RR = *(uint32_t*)(hcryp->Init.pInitVect+1);
    hcryp->Instance->IV1LR = *(uint32_t*)(hcryp->Init.pInitVect+2);
    hcryp->Instance->IV1RR = *(uint32_t*)(hcryp->Init.pInitVect+3);
#endif /* End AES or CRYP */
  }     
  /* Set the phase */
  hcryp->Phase = CRYP_PHASE_PROCESS;
  if(hcryp->Size != 0U)
  { 
    
#if defined (AES) 
    
    /* Enable computation complete flag and error interrupts */
    __HAL_CRYP_ENABLE_IT(hcryp,CRYP_IT_CCFIE | CRYP_IT_ERRIE);
    
    /* Enable CRYP */
    __HAL_CRYP_ENABLE(hcryp);
    
    /* Write the input block in the IN FIFO */
    hcryp->Instance->DINR  = *(uint32_t *)(hcryp->pCrypInBuffPtr + hcryp->CrypInCount );
    hcryp->CrypInCount++;
    hcryp->Instance->DINR  = *(uint32_t *)(hcryp->pCrypInBuffPtr + hcryp->CrypInCount );
    hcryp->CrypInCount++;   
    hcryp->Instance->DINR  = *(uint32_t *)(hcryp->pCrypInBuffPtr + hcryp->CrypInCount );
    hcryp->CrypInCount++;
    hcryp->Instance->DINR  = *(uint32_t *)(hcryp->pCrypInBuffPtr + hcryp->CrypInCount );
    hcryp->CrypInCount++;  
    
#else /* CRYP */
    
    /* Enable interrupts */
    __HAL_CRYP_ENABLE_IT(hcryp, CRYP_IT_INI | CRYP_IT_OUTI);
    
    /* Enable CRYP */
    __HAL_CRYP_ENABLE(hcryp);
    
#endif /* End AES or CRYP */        
  }
  else 
  {
    /* Process locked */
    __HAL_UNLOCK(hcryp);
    
    /* Change the CRYP state */
    hcryp->State = HAL_CRYP_STATE_READY;
  }  
  
  /* Return function status */
  return HAL_OK;
}
/**
  * @brief  Decryption in ECB/CBC & CTR mode with AES Standard using DMA mode
  * @param  hcryp: pointer to a CRYP_HandleTypeDef structure that contains
  *         the configuration information for CRYP module
  * @retval HAL status
  */
static HAL_StatusTypeDef CRYP_AES_Decrypt_DMA(CRYP_HandleTypeDef *hcryp)
{
  __IO uint32_t count = 0U;
  
  /*  Key preparation for ECB/CBC */
  if (hcryp->Init.Algorithm != CRYP_AES_CTR)  
  {
#if defined (AES) 
    if (hcryp->AutoKeyDerivation == DISABLE)/*Mode 2 key preparation*/
    {     
      /* Set key preparation for decryption operating mode*/
      MODIFY_REG(hcryp->Instance->CR, AES_CR_MODE, CRYP_OPERATINGMODE_KEYDERIVATION);
      
      /*  Set the Key*/
      CRYP_SetKey(hcryp, hcryp->Init.KeySize); 
>>>>>>> 49e424905b5922b07aa7166ec7a0eeb90adf58a8
      
      /* Enable CRYP */
      __HAL_CRYP_ENABLE(hcryp);
      
<<<<<<< HEAD
      /* Get tick */
      tickstart = HAL_GetTick();

      while(HAL_IS_BIT_SET(hcryp->Instance->SR, CRYP_FLAG_BUSY))
      {
        /* Check for the Timeout */
        if((HAL_GetTick() - tickstart ) > CRYP_TIMEOUT_VALUE)
        {
          /* Change state */
          hcryp->State = HAL_CRYP_STATE_TIMEOUT;
          
          /* Process Unlocked */
          __HAL_UNLOCK(hcryp);
          
          return HAL_TIMEOUT;
        }
      }
      
      /* Reset the ALGOMODE bits*/
      CRYP->CR &= (uint32_t)(~CRYP_CR_ALGOMODE);
      
      /* Set the CRYP peripheral in AES CBC decryption mode */
      __HAL_CRYP_SET_MODE(hcryp, CRYP_CR_ALGOMODE_AES_CBC | CRYP_CR_ALGODIR);
      
      /* Set the Initialization Vector */
      CRYP_SetInitVector(hcryp, hcryp->Init.pInitVect, CRYP_KEYSIZE_128B);
      
      /* Flush FIFO */
      __HAL_CRYP_FIFO_FLUSH(hcryp);
      
      /* Set the phase */
      hcryp->Phase = HAL_CRYP_PHASE_PROCESS;
    }
    
    /* Set the input and output addresses and start DMA transfer */ 
    CRYP_SetDMAConfig(hcryp, inputaddr, Size, outputaddr);
    
    /* Process Unlocked */
    __HAL_UNLOCK(hcryp);
    
    /* Return function status */
    return HAL_OK;
  }
  else
  {
    return HAL_ERROR;   
  }
}

/**
  * @brief  Initializes the CRYP peripheral in AES CTR decryption mode using DMA.
  * @param  hcryp pointer to a CRYP_HandleTypeDef structure that contains
  *         the configuration information for CRYP module
  * @param  pCypherData Pointer to the cyphertext buffer
  * @param  Size Length of the plaintext buffer, must be a multiple of 16
  * @param  pPlainData Pointer to the plaintext buffer
  * @retval HAL status
  */
HAL_StatusTypeDef HAL_CRYP_AESCTR_Decrypt_DMA(CRYP_HandleTypeDef *hcryp, uint8_t *pCypherData, uint16_t Size, uint8_t *pPlainData)
{  
  uint32_t inputaddr;
  uint32_t outputaddr;
  
  if((hcryp->State == HAL_CRYP_STATE_READY) || (hcryp->Phase == HAL_CRYP_PHASE_PROCESS))
  {
    /* Process Locked */
    __HAL_LOCK(hcryp);
    
    inputaddr  = (uint32_t)pCypherData;
    outputaddr = (uint32_t)pPlainData;
    
    /* Change the CRYP state */
    hcryp->State = HAL_CRYP_STATE_BUSY;
    
    /* Check if initialization phase has already been performed */
    if(hcryp->Phase == HAL_CRYP_PHASE_READY)
    {
      /* Set the key */
      CRYP_SetKey(hcryp, hcryp->Init.pKey, hcryp->Init.KeySize);
      
      /* Set the CRYP peripheral in AES CTR mode */
      __HAL_CRYP_SET_MODE(hcryp, CRYP_CR_ALGOMODE_AES_CTR | CRYP_CR_ALGODIR);
      
      /* Set the Initialization Vector */
      CRYP_SetInitVector(hcryp, hcryp->Init.pInitVect, CRYP_KEYSIZE_128B);
      
      /* Flush FIFO */
      __HAL_CRYP_FIFO_FLUSH(hcryp);
      
      /* Set the phase */
      hcryp->Phase = HAL_CRYP_PHASE_PROCESS;
    }
    
    /* Set the input and output addresses and start DMA transfer */ 
    CRYP_SetDMAConfig(hcryp, inputaddr, Size, outputaddr);
    
    /* Process Unlocked */
    __HAL_UNLOCK(hcryp);
    
    /* Return function status */
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
  
/** @defgroup CRYP_Exported_Functions_Group3 DES processing functions 
 *  @brief   processing functions. 
 *
@verbatim   
  ==============================================================================
                      ##### DES processing functions #####
  ==============================================================================  
    [..]  This section provides functions allowing to:
      (+) Encrypt plaintext using DES using ECB or CBC chaining modes
      (+) Decrypt cyphertext using ECB or CBC chaining modes
    [..]  Three processing functions are available:
      (+) Polling mode
      (+) Interrupt mode
      (+) DMA mode

@endverbatim
  * @{
  */

/**
  * @brief  Initializes the CRYP peripheral in DES ECB encryption mode.
  * @param  hcryp pointer to a CRYP_HandleTypeDef structure that contains
  *         the configuration information for CRYP module
  * @param  pPlainData Pointer to the plaintext buffer
  * @param  Size Length of the plaintext buffer, must be a multiple of 8
  * @param  pCypherData Pointer to the cyphertext buffer
  * @param  Timeout Specify Timeout value  
  * @retval HAL status
  */
HAL_StatusTypeDef HAL_CRYP_DESECB_Encrypt(CRYP_HandleTypeDef *hcryp, uint8_t *pPlainData, uint16_t Size, uint8_t *pCypherData, uint32_t Timeout)
{
  /* Process Locked */
  __HAL_LOCK(hcryp);
  
  /* Change the CRYP state */
  hcryp->State = HAL_CRYP_STATE_BUSY;
  
  /* Set CRYP peripheral in DES ECB encryption mode */
  CRYP_SetDESECBMode(hcryp, 0);
  
  /* Enable CRYP */
  __HAL_CRYP_ENABLE(hcryp);
  
  /* Write Plain Data and Get Cypher Data */
  if(CRYP_ProcessData2Words(hcryp, pPlainData, Size, pCypherData, Timeout) != HAL_OK)
  {
    return HAL_TIMEOUT;
  }
  
  /* Change the CRYP state */
  hcryp->State = HAL_CRYP_STATE_READY;
  
  /* Process Unlocked */
  __HAL_UNLOCK(hcryp);
  
  /* Return function status */
  return HAL_OK;
}

/**
  * @brief  Initializes the CRYP peripheral in DES ECB decryption mode.
  * @param  hcryp pointer to a CRYP_HandleTypeDef structure that contains
  *         the configuration information for CRYP module
  * @param  pCypherData Pointer to the cyphertext buffer
  * @param  Size Length of the plaintext buffer, must be a multiple of 8
  * @param  pPlainData Pointer to the plaintext buffer
  * @param  Timeout Specify Timeout value  
  * @retval HAL status
  */
HAL_StatusTypeDef HAL_CRYP_DESECB_Decrypt(CRYP_HandleTypeDef *hcryp, uint8_t *pCypherData, uint16_t Size, uint8_t *pPlainData, uint32_t Timeout)
{
  /* Process Locked */
  __HAL_LOCK(hcryp);
  
  /* Change the CRYP state */
  hcryp->State = HAL_CRYP_STATE_BUSY;
  
  /* Set CRYP peripheral in DES ECB decryption mode */
  CRYP_SetDESECBMode(hcryp, CRYP_CR_ALGODIR);
  
  /* Enable CRYP */
  __HAL_CRYP_ENABLE(hcryp);
  
  /* Write Plain Data and Get Cypher Data */
  if(CRYP_ProcessData2Words(hcryp, pCypherData, Size, pPlainData, Timeout) != HAL_OK)
  {
    return HAL_TIMEOUT;
  }
  
  /* Change the CRYP state */
  hcryp->State = HAL_CRYP_STATE_READY;
  
  /* Process Unlocked */
  __HAL_UNLOCK(hcryp);
  
  /* Return function status */
  return HAL_OK;
}

/**
  * @brief  Initializes the CRYP peripheral in DES CBC encryption mode.
  * @param  hcryp pointer to a CRYP_HandleTypeDef structure that contains
  *         the configuration information for CRYP module
  * @param  pPlainData Pointer to the plaintext buffer
  * @param  Size Length of the plaintext buffer, must be a multiple of 8
  * @param  pCypherData Pointer to the cyphertext buffer
  * @param  Timeout Specify Timeout value  
  * @retval HAL status
  */
HAL_StatusTypeDef HAL_CRYP_DESCBC_Encrypt(CRYP_HandleTypeDef *hcryp, uint8_t *pPlainData, uint16_t Size, uint8_t *pCypherData, uint32_t Timeout)
{
  /* Process Locked */
  __HAL_LOCK(hcryp);
  
  /* Change the CRYP state */
  hcryp->State = HAL_CRYP_STATE_BUSY;
  
  /* Set CRYP peripheral in DES CBC encryption mode */
  CRYP_SetDESCBCMode(hcryp, 0);
=======
      /* Wait for CCF flag to be raised */
      count = CRYP_TIMEOUT_KEYPREPARATION;
      do
      {
        count-- ;
        if(count == 0U)
        {
          /* Disable the CRYP peripheral clock */
          __HAL_CRYP_DISABLE(hcryp);
          
          /* Change state */
          hcryp->ErrorCode |= HAL_CRYP_ERROR_TIMEOUT;
          hcryp->State = HAL_CRYP_STATE_READY; 
          
          /* Process unlocked */          
          __HAL_UNLOCK(hcryp); 
          return HAL_ERROR;
        }
      }
      while(HAL_IS_BIT_CLR(hcryp->Instance->SR, AES_SR_CCF));
      
      /* Clear CCF Flag */
      __HAL_CRYP_CLEAR_FLAG(hcryp, CRYP_CCF_CLEAR);
      
      /* Return to decryption operating mode(Mode 3)*/      
      MODIFY_REG(hcryp->Instance->CR, AES_CR_MODE, CRYP_OPERATINGMODE_DECRYPT);   
    }
    else /*Mode 4 : decryption & key preparation*/
    {
      /*  Set the Key*/
      CRYP_SetKey(hcryp, hcryp->Init.KeySize);
      
      /* Set decryption & Key preparation operating mode*/ 
      MODIFY_REG(hcryp->Instance->CR, AES_CR_MODE, CRYP_OPERATINGMODE_KEYDERIVATION_DECRYPT); 
    }     
#else /* CRYP */   
    /* change ALGOMODE to key preparation for decryption*/
    MODIFY_REG(hcryp->Instance->CR, CRYP_CR_ALGOMODE, CRYP_CR_ALGOMODE_AES_KEY );
    
    /*  Set the Key*/
    CRYP_SetKey(hcryp, hcryp->Init.KeySize);
    
    /* Enable CRYP */
    __HAL_CRYP_ENABLE(hcryp);
    
    /* Wait for BUSY flag to be raised */
    count = CRYP_TIMEOUT_KEYPREPARATION;
    do
    {
      count-- ;
      if(count == 0U)
      {
        /* Disable the CRYP peripheral clock */
        __HAL_CRYP_DISABLE(hcryp);
        
        /* Change state */
        hcryp->ErrorCode |= HAL_CRYP_ERROR_TIMEOUT;
        hcryp->State = HAL_CRYP_STATE_READY;  
        
        /* Process unlocked */          
        __HAL_UNLOCK(hcryp); 
        return HAL_ERROR;
      }
    }
    while(HAL_IS_BIT_SET(hcryp->Instance->SR, CRYP_FLAG_BUSY));
    
    /* Turn back to ALGOMODE of the configuration */
    MODIFY_REG(hcryp->Instance->CR, CRYP_CR_ALGOMODE, hcryp->Init.Algorithm ); 
    
#endif /* End AES or CRYP  */ 
  }
  else  /*Algorithm CTR */
  {  
    /*  Set the Key*/
    CRYP_SetKey(hcryp, hcryp->Init.KeySize);
  } 
  
  if (hcryp->Init.Algorithm != CRYP_AES_ECB)
  {
    /* Set the Initialization Vector*/
#if defined (AES)       
    hcryp->Instance->IVR3 = *(uint32_t*)(hcryp->Init.pInitVect);
    hcryp->Instance->IVR2 = *(uint32_t*)(hcryp->Init.pInitVect+1);
    hcryp->Instance->IVR1 = *(uint32_t*)(hcryp->Init.pInitVect+2);
    hcryp->Instance->IVR0 = *(uint32_t*)(hcryp->Init.pInitVect+3);
#else /* CRYP */
    hcryp->Instance->IV0LR = *(uint32_t*)(hcryp->Init.pInitVect);
    hcryp->Instance->IV0RR = *(uint32_t*)(hcryp->Init.pInitVect+1);
    hcryp->Instance->IV1LR = *(uint32_t*)(hcryp->Init.pInitVect+2);
    hcryp->Instance->IV1RR = *(uint32_t*)(hcryp->Init.pInitVect+3);
#endif /* End AES or CRYP  */
  }      
  /* Set the phase */
  hcryp->Phase = CRYP_PHASE_PROCESS;
  
  if(hcryp->Size != 0U)
  {    
    /* Set the input and output addresses and start DMA transfer */ 
    CRYP_SetDMAConfig(hcryp, (uint32_t)( hcryp->pCrypInBuffPtr), (hcryp->Size/4U), (uint32_t)(hcryp->pCrypOutBuffPtr));    
  }
  else 
  {
    /* Process unlocked */
    __HAL_UNLOCK(hcryp);
    
    /* Change the CRYP state */
    hcryp->State = HAL_CRYP_STATE_READY;
  }       
  
  /* Return function status */
  return HAL_OK;
}


/**
  * @brief  DMA CRYP input data process complete callback.
  * @param  hdma: DMA handle
  * @retval None
  */
static void CRYP_DMAInCplt(DMA_HandleTypeDef *hdma)  
{
  CRYP_HandleTypeDef* hcryp = (CRYP_HandleTypeDef*)((DMA_HandleTypeDef*)hdma)->Parent;
  
  /* Disable the DMA transfer for input FIFO request by resetting the DIEN bit
  in the DMACR register */
#if defined (CRYP)  
  hcryp->Instance->DMACR &= (uint32_t)(~CRYP_DMACR_DIEN);  
  
#else /* AES */
  CLEAR_BIT(hcryp->Instance->CR, AES_CR_DMAINEN);
  
  /* TinyAES2, No output on CCM AES, unlock should be done when input data process complete */
  if((hcryp->Init.Algorithm & CRYP_AES_CCM) == CRYP_AES_CCM)
  {  
    /* Clear CCF flag */
    __HAL_CRYP_CLEAR_FLAG(hcryp,CRYP_CCF_CLEAR);
    
    /* Change the CRYP state to ready */
    hcryp->State = HAL_CRYP_STATE_READY;
    
    /* Process Unlocked */
    __HAL_UNLOCK(hcryp);
  }
#endif /* End AES or CRYP */ 
  
  /* Call input data transfer complete callback */
#if (USE_HAL_CRYP_REGISTER_CALLBACKS == 1) 
  /*Call registered Input complete callback*/
  hcryp->InCpltCallback(hcryp);
#else
  /*Call legacy weak Input complete callback*/
  HAL_CRYP_InCpltCallback(hcryp);
#endif /* USE_HAL_CRYP_REGISTER_CALLBACKS */ 
}

/**
  * @brief  DMA CRYP output data process complete callback.
  * @param  hdma: DMA handle
  * @retval None
  */
static void CRYP_DMAOutCplt(DMA_HandleTypeDef *hdma)
{
  CRYP_HandleTypeDef* hcryp = (CRYP_HandleTypeDef*)((DMA_HandleTypeDef*)hdma)->Parent;
  
  /* Disable the DMA transfer for output FIFO request by resetting
  the DOEN bit in the DMACR register */
  
#if defined (CRYP) 

  hcryp->Instance->DMACR &= (uint32_t)(~CRYP_DMACR_DOEN);
  if((hcryp->Init.Algorithm & CRYP_AES_GCM) != CRYP_AES_GCM)
  {  
    /* Disable CRYP  (not allowed in  GCM)*/
    __HAL_CRYP_DISABLE(hcryp);
  }
#else /* AES */ 
  
  CLEAR_BIT(hcryp->Instance->CR, AES_CR_DMAOUTEN);
  
  /* Clear CCF flag */
  __HAL_CRYP_CLEAR_FLAG(hcryp,CRYP_CCF_CLEAR);  
  
  if((hcryp->Init.Algorithm & CRYP_AES_GCM_GMAC) != CRYP_AES_GCM_GMAC)
  {  
    /* Disable CRYP (not allowed in  GCM)*/ 
    __HAL_CRYP_DISABLE(hcryp);
  } 
#endif /* End AES or CRYP */ 
  
  /* Change the CRYP state to ready */
  hcryp->State = HAL_CRYP_STATE_READY;
  
  /* Process unlocked */
  __HAL_UNLOCK(hcryp); 
  /* Call output data transfer complete callback */
#if (USE_HAL_CRYP_REGISTER_CALLBACKS == 1) 
  /*Call registered Output complete callback*/
  hcryp->OutCpltCallback(hcryp);
#else
  /*Call legacy weak Output complete callback*/
  HAL_CRYP_OutCpltCallback(hcryp);
#endif /* USE_HAL_CRYP_REGISTER_CALLBACKS */ 
}

/**
  * @brief  DMA CRYP communication error callback. 
  * @param  hdma: DMA handle
  * @retval None
  */
static void CRYP_DMAError(DMA_HandleTypeDef *hdma)
{
  CRYP_HandleTypeDef* hcryp = (CRYP_HandleTypeDef*)((DMA_HandleTypeDef*)hdma)->Parent;
  
  /* Change the CRYP peripheral state */ 
  hcryp->State= HAL_CRYP_STATE_READY;
  
  /* DMA error code field */
  hcryp->ErrorCode |= HAL_CRYP_ERROR_DMA; 
  
#if defined (AES) 
  
  /* Clear CCF flag */
  __HAL_CRYP_CLEAR_FLAG(hcryp,CRYP_CCF_CLEAR);  
  
#endif /* AES */   
  
  /* Call error callback */
#if (USE_HAL_CRYP_REGISTER_CALLBACKS == 1) 
  /*Call registered error callback*/
  hcryp->ErrorCallback(hcryp);
#else
  /*Call legacy weak error callback*/
  HAL_CRYP_ErrorCallback(hcryp);
#endif /* USE_HAL_CRYP_REGISTER_CALLBACKS */ 
}

/**
  * @brief  Set the DMA configuration and start the DMA transfer
  * @param  hcryp: pointer to a CRYP_HandleTypeDef structure that contains
  *         the configuration information for CRYP module
  * @param  inputaddr: address of the input buffer
  * @param  Size: size of the input buffer, must be a multiple of 16.
  * @param  outputaddr: address of the output buffer
  * @retval None
  */
static void CRYP_SetDMAConfig(CRYP_HandleTypeDef *hcryp, uint32_t inputaddr, uint16_t Size, uint32_t outputaddr)
{
  /* Set the CRYP DMA transfer complete callback */
  hcryp->hdmain->XferCpltCallback = CRYP_DMAInCplt;
  
  /* Set the DMA input error callback */
  hcryp->hdmain->XferErrorCallback = CRYP_DMAError;
  
  /* Set the CRYP DMA transfer complete callback */
  hcryp->hdmaout->XferCpltCallback = CRYP_DMAOutCplt;
  
  /* Set the DMA output error callback */
  hcryp->hdmaout->XferErrorCallback = CRYP_DMAError;
  
#if defined (CRYP)   
>>>>>>> 49e424905b5922b07aa7166ec7a0eeb90adf58a8
  
  /* Enable CRYP */
  __HAL_CRYP_ENABLE(hcryp);
  
<<<<<<< HEAD
  /* Write Plain Data and Get Cypher Data */
  if(CRYP_ProcessData2Words(hcryp, pPlainData, Size, pCypherData, Timeout) != HAL_OK)
  {
    return HAL_TIMEOUT;
  }
  
  /* Change the CRYP state */
  hcryp->State = HAL_CRYP_STATE_READY;
  
  /* Process Unlocked */
  __HAL_UNLOCK(hcryp);
  
  /* Return function status */
  return HAL_OK;
}

/**
  * @brief  Initializes the CRYP peripheral in DES ECB decryption mode.
  * @param  hcryp pointer to a CRYP_HandleTypeDef structure that contains
  *         the configuration information for CRYP module
  * @param  pCypherData Pointer to the cyphertext buffer
  * @param  Size Length of the plaintext buffer, must be a multiple of 8
  * @param  pPlainData Pointer to the plaintext buffer
  * @param  Timeout Specify Timeout value  
  * @retval HAL status
  */
HAL_StatusTypeDef HAL_CRYP_DESCBC_Decrypt(CRYP_HandleTypeDef *hcryp, uint8_t *pCypherData, uint16_t Size, uint8_t *pPlainData, uint32_t Timeout)
{
  /* Process Locked */
  __HAL_LOCK(hcryp);
  
  /* Change the CRYP state */
  hcryp->State = HAL_CRYP_STATE_BUSY;
  
  /* Set CRYP peripheral in DES CBC decryption mode */
  CRYP_SetDESCBCMode(hcryp, CRYP_CR_ALGODIR);
  
  /* Enable CRYP */
  __HAL_CRYP_ENABLE(hcryp);
  
  /* Write Plain Data and Get Cypher Data */
  if(CRYP_ProcessData2Words(hcryp, pCypherData, Size, pPlainData, Timeout) != HAL_OK)
  {
    return HAL_TIMEOUT;
  }
  
  /* Change the CRYP state */
  hcryp->State = HAL_CRYP_STATE_READY;
  
  /* Process Unlocked */
  __HAL_UNLOCK(hcryp);
  
  /* Return function status */
  return HAL_OK;
}

/**
  * @brief  Initializes the CRYP peripheral in DES ECB encryption mode using IT.
  * @param  hcryp pointer to a CRYP_HandleTypeDef structure that contains
  *         the configuration information for CRYP module
  * @param  pPlainData Pointer to the plaintext buffer
  * @param  Size Length of the plaintext buffer, must be a multiple of 8
  * @param  pCypherData Pointer to the cyphertext buffer
  * @retval HAL status
  */
HAL_StatusTypeDef HAL_CRYP_DESECB_Encrypt_IT(CRYP_HandleTypeDef *hcryp, uint8_t *pPlainData, uint16_t Size, uint8_t *pCypherData)
{
  uint32_t inputaddr;
  uint32_t outputaddr;
  
  if(hcryp->State == HAL_CRYP_STATE_READY)
  {
    /* Process Locked */
    __HAL_LOCK(hcryp);
    
    hcryp->CrypInCount = Size;
    hcryp->pCrypInBuffPtr = pPlainData;
    hcryp->pCrypOutBuffPtr = pCypherData;
    hcryp->CrypOutCount = Size;
    
    /* Change the CRYP state */
    hcryp->State = HAL_CRYP_STATE_BUSY;
    
    /* Set CRYP peripheral in DES ECB encryption mode */
    CRYP_SetDESECBMode(hcryp, 0);
    
    /* Enable Interrupts */
    __HAL_CRYP_ENABLE_IT(hcryp, CRYP_IT_INI | CRYP_IT_OUTI);
    
    /* Enable CRYP */
    __HAL_CRYP_ENABLE(hcryp);
    
    /* Return function status */
    return HAL_OK;
  }
  else if(__HAL_CRYP_GET_IT(hcryp, CRYP_IT_INI))
  {
    inputaddr = (uint32_t)hcryp->pCrypInBuffPtr;
    /* Write the Input block in the IN FIFO */
    hcryp->Instance->DR = *(uint32_t*)(inputaddr);
    inputaddr+=4;
    hcryp->Instance->DR = *(uint32_t*)(inputaddr);
    
    hcryp->pCrypInBuffPtr += 8;
    hcryp->CrypInCount -= 8;
    if(hcryp->CrypInCount == 0)
    {
      __HAL_CRYP_DISABLE_IT(hcryp, CRYP_IT_INI);
      /* Call the Input data transfer complete callback */
      HAL_CRYP_InCpltCallback(hcryp);
    }
  }
  else if(__HAL_CRYP_GET_IT(hcryp, CRYP_IT_OUTI))
  {
    outputaddr = (uint32_t)hcryp->pCrypOutBuffPtr;
    /* Read the Output block from the Output FIFO */
    *(uint32_t*)(outputaddr) = hcryp->Instance->DOUT;
    outputaddr+=4;
    *(uint32_t*)(outputaddr) = hcryp->Instance->DOUT;
    
    hcryp->pCrypOutBuffPtr += 8;
    hcryp->CrypOutCount -= 8;
    if(hcryp->CrypOutCount == 0)
    {
      /* Disable IT */
      __HAL_CRYP_DISABLE_IT(hcryp, CRYP_IT_OUTI);
      /* Disable CRYP */
      __HAL_CRYP_DISABLE(hcryp);
      /* Process Unlocked */
      __HAL_UNLOCK(hcryp);
      /* Change the CRYP state */
      hcryp->State = HAL_CRYP_STATE_READY;
      /* Call Input transfer complete callback */
      HAL_CRYP_OutCpltCallback(hcryp);
    }
  }
  
  /* Return function status */
  return HAL_OK;
}

/**
  * @brief  Initializes the CRYP peripheral in DES CBC encryption mode using interrupt.
  * @param  hcryp pointer to a CRYP_HandleTypeDef structure that contains
  *         the configuration information for CRYP module
  * @param  pPlainData Pointer to the plaintext buffer
  * @param  Size Length of the plaintext buffer, must be a multiple of 8
  * @param  pCypherData Pointer to the cyphertext buffer
  * @retval HAL status
  */
HAL_StatusTypeDef HAL_CRYP_DESCBC_Encrypt_IT(CRYP_HandleTypeDef *hcryp, uint8_t *pPlainData, uint16_t Size, uint8_t *pCypherData)
{
  uint32_t inputaddr;
  uint32_t outputaddr;
  
  if(hcryp->State == HAL_CRYP_STATE_READY)
  {
    /* Process Locked */
    __HAL_LOCK(hcryp);
    
    hcryp->CrypInCount = Size;
    hcryp->pCrypInBuffPtr = pPlainData;
    hcryp->pCrypOutBuffPtr = pCypherData;
    hcryp->CrypOutCount = Size;
    
    /* Change the CRYP state */
    hcryp->State = HAL_CRYP_STATE_BUSY;
    
    /* Set CRYP peripheral in DES CBC encryption mode */
    CRYP_SetDESCBCMode(hcryp, 0);
    
    /* Enable Interrupts */
    __HAL_CRYP_ENABLE_IT(hcryp, CRYP_IT_INI | CRYP_IT_OUTI);
    
    /* Enable CRYP */
    __HAL_CRYP_ENABLE(hcryp);
    
    /* Return function status */
    return HAL_OK;
  }
  
  else if(__HAL_CRYP_GET_IT(hcryp, CRYP_IT_INI))
  {
    inputaddr = (uint32_t)hcryp->pCrypInBuffPtr;
    /* Write the Input block in the IN FIFO */
    hcryp->Instance->DR = *(uint32_t*)(inputaddr);
    inputaddr+=4;
    hcryp->Instance->DR = *(uint32_t*)(inputaddr);

    hcryp->pCrypInBuffPtr += 8;
    hcryp->CrypInCount -= 8;
    if(hcryp->CrypInCount == 0)
    {
      __HAL_CRYP_DISABLE_IT(hcryp, CRYP_IT_INI);
      /* Call the Input data transfer complete callback */
      HAL_CRYP_InCpltCallback(hcryp);
    }
  }
  else if(__HAL_CRYP_GET_IT(hcryp, CRYP_IT_OUTI))
  {
    outputaddr = (uint32_t)hcryp->pCrypOutBuffPtr;
    /* Read the Output block from the Output FIFO */
    *(uint32_t*)(outputaddr) = hcryp->Instance->DOUT;
    outputaddr+=4;
    *(uint32_t*)(outputaddr) = hcryp->Instance->DOUT;

    hcryp->pCrypOutBuffPtr += 8;
    hcryp->CrypOutCount -= 8;
    if(hcryp->CrypOutCount == 0)
    {
      /* Disable IT */
      __HAL_CRYP_DISABLE_IT(hcryp, CRYP_IT_OUTI);
      /* Disable CRYP */
      __HAL_CRYP_DISABLE(hcryp);
      /* Process Unlocked */
      __HAL_UNLOCK(hcryp);
      /* Change the CRYP state */
      hcryp->State = HAL_CRYP_STATE_READY;
      /* Call Input transfer complete callback */
      HAL_CRYP_OutCpltCallback(hcryp);
    }
  }
  
=======
  /* Enable the input DMA Stream */
  if ( HAL_DMA_Start_IT(hcryp->hdmain, inputaddr, (uint32_t)&hcryp->Instance->DIN, Size)!=HAL_OK)
  {
    /* DMA error code field */
    hcryp->ErrorCode |= HAL_CRYP_ERROR_DMA;  
    
    /* Call error callback */
#if (USE_HAL_CRYP_REGISTER_CALLBACKS == 1) 
    /*Call registered error callback*/
    hcryp->ErrorCallback(hcryp);
#else
    /*Call legacy weak error callback*/
    HAL_CRYP_ErrorCallback(hcryp);
#endif /* USE_HAL_CRYP_REGISTER_CALLBACKS */ 
  }  
  /* Enable the output DMA Stream */
  if (HAL_DMA_Start_IT(hcryp->hdmaout, (uint32_t)&hcryp->Instance->DOUT, outputaddr, Size)!=HAL_OK)
  {
    /* DMA error code field */
    hcryp->ErrorCode |= HAL_CRYP_ERROR_DMA;  
    
    /* Call error callback */
#if (USE_HAL_CRYP_REGISTER_CALLBACKS == 1) 
    /*Call registered error callback*/
    hcryp->ErrorCallback(hcryp);
#else
    /*Call legacy weak error callback*/
    HAL_CRYP_ErrorCallback(hcryp);
#endif /* USE_HAL_CRYP_REGISTER_CALLBACKS */
  }
  /* Enable In/Out DMA request */
  hcryp->Instance->DMACR = CRYP_DMACR_DOEN | CRYP_DMACR_DIEN;
  
#else /* AES */
  
  if(((hcryp->Init.Algorithm & CRYP_AES_GCM_GMAC) != CRYP_AES_GCM_GMAC) && ((hcryp->Init.Algorithm & CRYP_AES_CCM) != CRYP_AES_CCM))
  {  
    /* Enable CRYP (not allowed in  GCM & CCM)*/ 
    __HAL_CRYP_ENABLE(hcryp);
  } 
  
  /* Enable the DMA input stream */
  if (HAL_DMA_Start_IT(hcryp->hdmain, inputaddr, (uint32_t)&hcryp->Instance->DINR, Size)!=HAL_OK)
  {
    /* DMA error code field */
    hcryp->ErrorCode |= HAL_CRYP_ERROR_DMA;  
    
    /* Call error callback */
#if (USE_HAL_CRYP_REGISTER_CALLBACKS == 1) 
    /*Call registered error callback*/
    hcryp->ErrorCallback(hcryp);
#else
    /*Call legacy weak error callback*/
    HAL_CRYP_ErrorCallback(hcryp);
#endif /* USE_HAL_CRYP_REGISTER_CALLBACKS */
  }  
  /* Enable the DMA output stream */
  if (HAL_DMA_Start_IT(hcryp->hdmaout, (uint32_t)&hcryp->Instance->DOUTR, outputaddr, Size)!=HAL_OK)
  {
    /* DMA error code field */
    hcryp->ErrorCode |= HAL_CRYP_ERROR_DMA;  
    
    /* Call error callback */
#if (USE_HAL_CRYP_REGISTER_CALLBACKS == 1) 
    /*Call registered error callback*/
    hcryp->ErrorCallback(hcryp);
#else
    /*Call legacy weak error callback*/
    HAL_CRYP_ErrorCallback(hcryp);
#endif /* USE_HAL_CRYP_REGISTER_CALLBACKS */
  }  
 /*AES2v1.1.1 : CCM authentication : no init phase, only header and final phase */ 
  /* Enable In and Out DMA requests */
  if((hcryp->Init.Algorithm & CRYP_AES_CCM) == CRYP_AES_CCM)
  { 
    /* Enable only In DMA requests for CCM*/
    SET_BIT(hcryp->Instance->CR, (AES_CR_DMAINEN ));
  }
  else
  {
    /* Enable In and Out DMA requests */
    SET_BIT(hcryp->Instance->CR, (AES_CR_DMAINEN | AES_CR_DMAOUTEN));
  }  
#endif /* End AES or CRYP */
}

/**
  * @brief  Process Data: Write Input data in polling mode and used in AES functions. 
  * @param  hcryp: pointer to a CRYP_HandleTypeDef structure that contains
  *         the configuration information for CRYP module
  * @param  Timeout: Specify Timeout value  
  * @retval None
  */
static void CRYP_AES_ProcessData(CRYP_HandleTypeDef *hcryp, uint32_t Timeout)
{
  
  uint32_t temp;  /* Temporary CrypOutBuff */
#if defined (CRYP)
  uint16_t incount;  /* Temporary CrypInCount Value */
  uint16_t outcount;  /* Temporary CrypOutCount Value */
#endif 
  
#if defined (CRYP)  
   
  /*Temporary CrypOutCount Value*/
  incount = hcryp->CrypInCount; 
  
  if(((hcryp->Instance->SR & CRYP_FLAG_IFNF ) != 0x0U) && (incount < (hcryp->Size/4U)))
  {
    /* Write the input block in the IN FIFO */
    hcryp->Instance->DIN  = *(uint32_t *)(hcryp->pCrypInBuffPtr + hcryp->CrypInCount );
    hcryp->CrypInCount++;
    hcryp->Instance->DIN  = *(uint32_t *)(hcryp->pCrypInBuffPtr + hcryp->CrypInCount );
    hcryp->CrypInCount++;   
    hcryp->Instance->DIN  = *(uint32_t *)(hcryp->pCrypInBuffPtr + hcryp->CrypInCount );
    hcryp->CrypInCount++;
    hcryp->Instance->DIN  = *(uint32_t *)(hcryp->pCrypInBuffPtr + hcryp->CrypInCount );
    hcryp->CrypInCount++;      
  }
  
  /* Wait for OFNE flag to be raised */
  if(CRYP_WaitOnOFNEFlag(hcryp, Timeout) != HAL_OK)  
  { 
    /* Disable the CRYP peripheral clock */
    __HAL_CRYP_DISABLE(hcryp);
    
    /* Change state & error code*/
    hcryp->ErrorCode |= HAL_CRYP_ERROR_TIMEOUT;
    hcryp->State = HAL_CRYP_STATE_READY;
    
    /* Process unlocked */          
    __HAL_UNLOCK(hcryp); 
#if (USE_HAL_CRYP_REGISTER_CALLBACKS == 1) 
    /*Call registered error callback*/
    hcryp->ErrorCallback(hcryp);
#else
    /*Call legacy weak error callback*/
    HAL_CRYP_ErrorCallback(hcryp);
#endif /* USE_HAL_CRYP_REGISTER_CALLBACKS */ 
  } 
  
  /*Temporary CrypOutCount Value*/
  outcount = hcryp->CrypOutCount;
  
  if(((hcryp->Instance->SR & CRYP_FLAG_OFNE ) != 0x0U) && (outcount < (hcryp->Size/4U)))
  {
    /* Read the output block from the Output FIFO and put them in temporary buffer then get CrypOutBuff from temporary buffer  */ 
    temp  = hcryp->Instance->DOUT;
    *(uint32_t *)(hcryp->pCrypOutBuffPtr + hcryp->CrypOutCount) = temp;      
    hcryp->CrypOutCount++;
    temp  = hcryp->Instance->DOUT;    
    *(uint32_t *)(hcryp->pCrypOutBuffPtr + hcryp->CrypOutCount) = temp;
    hcryp->CrypOutCount++;    
    temp  = hcryp->Instance->DOUT;    
    *(uint32_t *)(hcryp->pCrypOutBuffPtr + hcryp->CrypOutCount) = temp;      
    hcryp->CrypOutCount++;
    temp  = hcryp->Instance->DOUT;   
    *(uint32_t *)(hcryp->pCrypOutBuffPtr + hcryp->CrypOutCount) = temp;
    hcryp->CrypOutCount++; 
  } 
  
#else /* AES */
  
  /* Write the input block in the IN FIFO */
  hcryp->Instance->DINR  = *(uint32_t *)(hcryp->pCrypInBuffPtr + hcryp->CrypInCount );
  hcryp->CrypInCount++;
  hcryp->Instance->DINR  = *(uint32_t *)(hcryp->pCrypInBuffPtr + hcryp->CrypInCount );
  hcryp->CrypInCount++;   
  hcryp->Instance->DINR  = *(uint32_t *)(hcryp->pCrypInBuffPtr + hcryp->CrypInCount );
  hcryp->CrypInCount++;
  hcryp->Instance->DINR  = *(uint32_t *)(hcryp->pCrypInBuffPtr + hcryp->CrypInCount );
  hcryp->CrypInCount++;      
  
  /* Wait for CCF flag to be raised */
  if(CRYP_WaitOnCCFlag(hcryp, Timeout) != HAL_OK)  
  { 
    /* Disable the CRYP peripheral clock */
    __HAL_CRYP_DISABLE(hcryp);
    
    /* Change state */
    hcryp->ErrorCode |= HAL_CRYP_ERROR_TIMEOUT;
    hcryp->State = HAL_CRYP_STATE_READY;  
    
    /* Process unlocked */          
    __HAL_UNLOCK(hcryp); 
#if (USE_HAL_CRYP_REGISTER_CALLBACKS == 1) 
    /*Call registered error callback*/
    hcryp->ErrorCallback(hcryp);
#else
    /*Call legacy weak error callback*/
    HAL_CRYP_ErrorCallback(hcryp);
#endif /* USE_HAL_CRYP_REGISTER_CALLBACKS */ 
  }
  
  /* Clear CCF Flag */
  __HAL_CRYP_CLEAR_FLAG(hcryp, CRYP_CCF_CLEAR);
  
  /* Read the output block from the output FIFO and put them in temporary buffer then get CrypOutBuff from temporary buffer*/ 
  temp  = hcryp->Instance->DOUTR;
  *(uint32_t *)(hcryp->pCrypOutBuffPtr + (hcryp->CrypOutCount)) =temp;
  hcryp->CrypOutCount++;
  temp  = hcryp->Instance->DOUTR;
  *(uint32_t *)(hcryp->pCrypOutBuffPtr + hcryp->CrypOutCount)   =temp;
  hcryp->CrypOutCount++;    
  temp  = hcryp->Instance->DOUTR;
  *(uint32_t *)(hcryp->pCrypOutBuffPtr + (hcryp->CrypOutCount)) = temp;      
  hcryp->CrypOutCount++;
  temp  = hcryp->Instance->DOUTR; 
  *(uint32_t *)(hcryp->pCrypOutBuffPtr + hcryp->CrypOutCount)   = temp;
  hcryp->CrypOutCount++; 
  
#endif /* End AES or CRYP */
}

/** 
  * @brief  Handle CRYP block input/output data handling under interruption.
  * @note   The function is called under interruption only, once
  *         interruptions have been enabled by HAL_CRYP_Encrypt_IT or HAL_CRYP_Decrypt_IT.
  * @param  hcryp: pointer to a CRYP_HandleTypeDef structure that contains
  *         the configuration information for CRYP module.
  * @retval HAL status
  */
static void CRYP_AES_IT(CRYP_HandleTypeDef *hcryp)
{
  uint32_t temp;  /* Temporary CrypOutBuff */
#if defined (CRYP) 
  uint16_t incount; /* Temporary CrypInCount Value */
  uint16_t outcount;  /* Temporary CrypOutCount Value */
#endif 
  
  if(hcryp->State == HAL_CRYP_STATE_BUSY)
  { 
#if defined (CRYP) 
   
    /*Temporary CrypOutCount Value*/
    incount = hcryp->CrypInCount;
    if(((hcryp->Instance->SR & CRYP_FLAG_IFNF ) != 0x0U) && (incount < (hcryp->Size/4U)))
    {
      /* Write the input block in the IN FIFO */
      hcryp->Instance->DIN  = *(uint32_t *)(hcryp->pCrypInBuffPtr + hcryp->CrypInCount );
      hcryp->CrypInCount++;
      hcryp->Instance->DIN  = *(uint32_t *)(hcryp->pCrypInBuffPtr + hcryp->CrypInCount );
      hcryp->CrypInCount++;   
      hcryp->Instance->DIN  = *(uint32_t *)(hcryp->pCrypInBuffPtr + hcryp->CrypInCount );
      hcryp->CrypInCount++;
      hcryp->Instance->DIN  = *(uint32_t *)(hcryp->pCrypInBuffPtr + hcryp->CrypInCount );
      hcryp->CrypInCount++;      
      if(hcryp->CrypInCount ==  ((uint16_t)(hcryp->Size)/4U))
      {     
        /* Disable interrupts */
        __HAL_CRYP_DISABLE_IT(hcryp, CRYP_IT_INI);
        
        /* Call the input data transfer complete callback */
#if (USE_HAL_CRYP_REGISTER_CALLBACKS == 1) 
        /*Call registered Input complete callback*/
        hcryp->InCpltCallback(hcryp);
#else
        /*Call legacy weak Input complete callback*/
        HAL_CRYP_InCpltCallback(hcryp);
#endif /* USE_HAL_CRYP_REGISTER_CALLBACKS */
      }
    }
    /*Temporary CrypOutCount Value*/
    outcount = hcryp->CrypOutCount;
    
    if(((hcryp->Instance->SR & CRYP_FLAG_OFNE ) != 0x0U) && (outcount < (hcryp->Size/4U)))
    {
      /* Read the output block from the output FIFO and put them in temporary buffer then get CrypOutBuff from temporary buffer  */ 
      temp  = hcryp->Instance->DOUT;
      *(uint32_t *)(hcryp->pCrypOutBuffPtr + hcryp->CrypOutCount) = temp;      
      hcryp->CrypOutCount++;
      temp  = hcryp->Instance->DOUT;    
      *(uint32_t *)(hcryp->pCrypOutBuffPtr + hcryp->CrypOutCount) = temp;
      hcryp->CrypOutCount++;    
      temp  = hcryp->Instance->DOUT;    
      *(uint32_t *)(hcryp->pCrypOutBuffPtr + hcryp->CrypOutCount) = temp;      
      hcryp->CrypOutCount++;
      temp  = hcryp->Instance->DOUT;   
      *(uint32_t *)(hcryp->pCrypOutBuffPtr + hcryp->CrypOutCount) = temp;
      hcryp->CrypOutCount++; 
      if(hcryp->CrypOutCount ==  ((uint16_t)(hcryp->Size)/4U))
      {
        /* Disable interrupts */
        __HAL_CRYP_DISABLE_IT(hcryp, CRYP_IT_OUTI);
        
        /* Change the CRYP state */
        hcryp->State = HAL_CRYP_STATE_READY;        
        
        /* Disable CRYP */
        __HAL_CRYP_DISABLE(hcryp);
        
        /* Process unlocked */
        __HAL_UNLOCK(hcryp);
        
      /* Call Output transfer complete callback */
#if (USE_HAL_CRYP_REGISTER_CALLBACKS == 1) 
      /*Call registered Output complete callback*/
      hcryp->OutCpltCallback(hcryp);
#else
      /*Call legacy weak Output complete callback*/
      HAL_CRYP_OutCpltCallback(hcryp);
#endif /* USE_HAL_CRYP_REGISTER_CALLBACKS */
      }
    }
    
#else /*AES*/
    
    /* Read the output block from the output FIFO and put them in temporary buffer then get CrypOutBuff from temporary buffer*/ 
    temp  = hcryp->Instance->DOUTR;
    *(uint32_t *)(hcryp->pCrypOutBuffPtr + (hcryp->CrypOutCount)) =temp;
    hcryp->CrypOutCount++;
    temp  = hcryp->Instance->DOUTR;
    *(uint32_t *)(hcryp->pCrypOutBuffPtr + hcryp->CrypOutCount)   =temp;
    hcryp->CrypOutCount++;    
    temp  = hcryp->Instance->DOUTR;
    *(uint32_t *)(hcryp->pCrypOutBuffPtr + (hcryp->CrypOutCount)) = temp;      
    hcryp->CrypOutCount++;
    temp  = hcryp->Instance->DOUTR; 
    *(uint32_t *)(hcryp->pCrypOutBuffPtr + hcryp->CrypOutCount)   = temp;
    hcryp->CrypOutCount++; 
    
    if(hcryp->CrypOutCount ==  (hcryp->Size/4U))
    {
      /* Disable Computation Complete flag and errors interrupts */
      __HAL_CRYP_DISABLE_IT(hcryp,CRYP_IT_CCFIE|CRYP_IT_ERRIE);
      
      /* Change the CRYP state */
      hcryp->State = HAL_CRYP_STATE_READY;
      
      /* Disable CRYP */
      __HAL_CRYP_DISABLE(hcryp);
      
      /* Process Unlocked */
      __HAL_UNLOCK(hcryp);
      
      /* Call Output transfer complete callback */
#if (USE_HAL_CRYP_REGISTER_CALLBACKS == 1) 
      /*Call registered Output complete callback*/
      hcryp->OutCpltCallback(hcryp);
#else
      /*Call legacy weak Output complete callback*/
      HAL_CRYP_OutCpltCallback(hcryp);
#endif /* USE_HAL_CRYP_REGISTER_CALLBACKS */
    }
    else
    {  
      /* Write the input block in the IN FIFO */
      hcryp->Instance->DINR  = *(uint32_t *)(hcryp->pCrypInBuffPtr + hcryp->CrypInCount );
      hcryp->CrypInCount++;
      hcryp->Instance->DINR  = *(uint32_t *)(hcryp->pCrypInBuffPtr + hcryp->CrypInCount );
      hcryp->CrypInCount++;   
      hcryp->Instance->DINR  = *(uint32_t *)(hcryp->pCrypInBuffPtr + hcryp->CrypInCount );
      hcryp->CrypInCount++;
      hcryp->Instance->DINR  = *(uint32_t *)(hcryp->pCrypInBuffPtr + hcryp->CrypInCount );
      hcryp->CrypInCount++;      
      
      if(hcryp->CrypInCount ==  (hcryp->Size/4U)) 
      {    
        /* Call Input transfer complete callback */
#if (USE_HAL_CRYP_REGISTER_CALLBACKS == 1U) 
        /*Call registered Input complete callback*/
        hcryp->InCpltCallback(hcryp);
#else
        /*Call legacy weak Input complete callback*/
        HAL_CRYP_InCpltCallback(hcryp);
#endif /* USE_HAL_CRYP_REGISTER_CALLBACKS */
      }   
    } 
#endif /* End AES or CRYP  */
   
  } 
  else
  {
    /* Busy error code field */
    hcryp->ErrorCode |= HAL_CRYP_ERROR_BUSY; 
#if (USE_HAL_CRYP_REGISTER_CALLBACKS == 1) 
    /*Call registered error callback*/
    hcryp->ErrorCallback(hcryp);
#else
    /*Call legacy weak error callback*/
    HAL_CRYP_ErrorCallback(hcryp);
#endif /* USE_HAL_CRYP_REGISTER_CALLBACKS */ 
  }
} 

/**
  * @brief  Writes Key in Key registers. 
  * @param  hcryp: pointer to a CRYP_HandleTypeDef structure that contains
  *         the configuration information for CRYP module
  * @param  KeySize: Size of Key
  * @retval None
  */
static void CRYP_SetKey(CRYP_HandleTypeDef *hcryp, uint32_t KeySize)
{  
#if defined (CRYP)
  
  switch(KeySize)
  {
  case CRYP_KEYSIZE_256B:
    hcryp->Instance->K0LR = *(uint32_t*)(hcryp->Init.pKey);
    hcryp->Instance->K0RR = *(uint32_t*)(hcryp->Init.pKey+1);
    hcryp->Instance->K1LR = *(uint32_t*)(hcryp->Init.pKey+2);
    hcryp->Instance->K1RR = *(uint32_t*)(hcryp->Init.pKey+3);
    hcryp->Instance->K2LR = *(uint32_t*)(hcryp->Init.pKey+4);
    hcryp->Instance->K2RR = *(uint32_t*)(hcryp->Init.pKey+5);
    hcryp->Instance->K3LR = *(uint32_t*)(hcryp->Init.pKey+6);
    hcryp->Instance->K3RR = *(uint32_t*)(hcryp->Init.pKey+7); 
    break;
  case CRYP_KEYSIZE_192B:
    hcryp->Instance->K1LR = *(uint32_t*)(hcryp->Init.pKey);
    hcryp->Instance->K1RR = *(uint32_t*)(hcryp->Init.pKey+1);
    hcryp->Instance->K2LR = *(uint32_t*)(hcryp->Init.pKey+2);
    hcryp->Instance->K2RR = *(uint32_t*)(hcryp->Init.pKey+3);
    hcryp->Instance->K3LR = *(uint32_t*)(hcryp->Init.pKey+4);
    hcryp->Instance->K3RR = *(uint32_t*)(hcryp->Init.pKey+5); 
    break;
  case CRYP_KEYSIZE_128B:         
    hcryp->Instance->K2LR = *(uint32_t*)(hcryp->Init.pKey);
    hcryp->Instance->K2RR = *(uint32_t*)(hcryp->Init.pKey+1);
    hcryp->Instance->K3LR = *(uint32_t*)(hcryp->Init.pKey+2);
    hcryp->Instance->K3RR = *(uint32_t*)(hcryp->Init.pKey+3); 
    
    break;
  default:
    break;
  }
#else /*AES*/
  switch(KeySize)
  {
  case CRYP_KEYSIZE_256B:
    hcryp->Instance->KEYR7 =*(uint32_t*)(hcryp->Init.pKey);   
    hcryp->Instance->KEYR6 =*(uint32_t*)(hcryp->Init.pKey+1);
    hcryp->Instance->KEYR5 =*(uint32_t*)(hcryp->Init.pKey+2);
    hcryp->Instance->KEYR4 =*(uint32_t*)(hcryp->Init.pKey+3);
    hcryp->Instance->KEYR3 =*(uint32_t*)(hcryp->Init.pKey+4);   
    hcryp->Instance->KEYR2 =*(uint32_t*)(hcryp->Init.pKey+5);
    hcryp->Instance->KEYR1 =*(uint32_t*)(hcryp->Init.pKey+6);
    hcryp->Instance->KEYR0 =*(uint32_t*)(hcryp->Init.pKey+7);
    break;
  case CRYP_KEYSIZE_128B:   
    hcryp->Instance->KEYR3 =*(uint32_t*)(hcryp->Init.pKey);   
    hcryp->Instance->KEYR2 =*(uint32_t*)(hcryp->Init.pKey+1);
    hcryp->Instance->KEYR1 =*(uint32_t*)(hcryp->Init.pKey+2);
    hcryp->Instance->KEYR0 =*(uint32_t*)(hcryp->Init.pKey+3);   
    
    break;
  default:
    break;
  }
#endif /* End AES or CRYP  */
}


/**
  * @brief  Encryption/Decryption process in AES GCM mode and prepare the authentication TAG 
  * @param  hcryp: pointer to a CRYP_HandleTypeDef structure that contains
  *         the configuration information for CRYP module
  * @param  Timeout: Timeout duration
  * @retval HAL status
  */
static HAL_StatusTypeDef CRYP_AESGCM_Process(CRYP_HandleTypeDef *hcryp, uint32_t Timeout)
{
  uint32_t tickstart;
  uint32_t wordsize = (uint32_t)(hcryp->Size)/4U ;
  uint16_t outcount;  /* Temporary CrypOutCount Value */
    
  /*  Reset CrypHeaderCount */
  hcryp->CrypHeaderCount = 0U; 
  
  /****************************** Init phase **********************************/
  
  CRYP_SET_PHASE(hcryp,CRYP_PHASE_INIT);
  
  /* Set the key */
  CRYP_SetKey(hcryp, hcryp->Init.KeySize);
  
#if defined(CRYP)  
  
  /* Set the initialization vector and the counter : Initial Counter Block (ICB)*/
  hcryp->Instance->IV0LR = *(uint32_t*)(hcryp->Init.pInitVect);
  hcryp->Instance->IV0RR = *(uint32_t*)(hcryp->Init.pInitVect+1);
  hcryp->Instance->IV1LR = *(uint32_t*)(hcryp->Init.pInitVect+2);
  hcryp->Instance->IV1RR = *(uint32_t*)(hcryp->Init.pInitVect+3);
  
  /* Enable the CRYP peripheral */
  __HAL_CRYP_ENABLE(hcryp);
  
  /* Get tick */
  tickstart = HAL_GetTick();
  
  /*Wait for the CRYPEN bit to be cleared*/
  while((hcryp->Instance->CR & CRYP_CR_CRYPEN) == CRYP_CR_CRYPEN)
  {
    /* Check for the Timeout */
    if(Timeout != HAL_MAX_DELAY)
    {
      if(((HAL_GetTick() - tickstart ) > Timeout)||(Timeout == 0U))
      {
        /* Disable the CRYP peripheral clock */
        __HAL_CRYP_DISABLE(hcryp);
        
        /* Change state */
        hcryp->ErrorCode |= HAL_CRYP_ERROR_TIMEOUT;
        hcryp->State = HAL_CRYP_STATE_READY;  
        
        /* Process unlocked */          
        __HAL_UNLOCK(hcryp); 
        return HAL_ERROR;
      }
    }
  }
  
#else /* AES */
  /* Workaround 1 : only AES.
  Datatype configuration must be 32 bits during Init phase. Only, after Init, and before re
  enabling the IP, datatype different from 32 bits can be configured.*/
  /* Select DATATYPE 32  */
  MODIFY_REG(hcryp->Instance->CR, AES_CR_DATATYPE, CRYP_DATATYPE_32B);   
  
  /* Set the initialization vector and the counter : Initial Counter Block (ICB)*/
  hcryp->Instance->IVR3 = *(uint32_t*)(hcryp->Init.pInitVect);
  hcryp->Instance->IVR2 = *(uint32_t*)(hcryp->Init.pInitVect+1);
  hcryp->Instance->IVR1 = *(uint32_t*)(hcryp->Init.pInitVect+2);
  hcryp->Instance->IVR0 = *(uint32_t*)(hcryp->Init.pInitVect+3);
  
  /* Enable the CRYP peripheral */
  __HAL_CRYP_ENABLE(hcryp);
  
  /* just wait for hash computation */
  if(CRYP_WaitOnCCFlag(hcryp, Timeout) != HAL_OK)  
  { 
    /* Change state */
    hcryp->ErrorCode |= HAL_CRYP_ERROR_TIMEOUT;
    hcryp->State = HAL_CRYP_STATE_READY;          
    
    /* Process unlocked & return error */
    __HAL_UNLOCK(hcryp);          
    return HAL_ERROR;
  }
  /* Clear CCF flag */
  __HAL_CRYP_CLEAR_FLAG(hcryp, CRYP_CCF_CLEAR);
  
#endif /* End AES or CRYP  */  
  
  /************************ Header phase *************************************/
  
  if(CRYP_GCMCCM_SetHeaderPhase(hcryp,  Timeout) != HAL_OK)
  {
    return HAL_ERROR;
  }
  
  /*************************Payload phase ************************************/   
  
  /* Set the phase */
  hcryp->Phase = CRYP_PHASE_PROCESS;
  
#if defined(CRYP)  
  
  /* Disable the CRYP peripheral */
  __HAL_CRYP_DISABLE(hcryp);
  
  /* Select payload phase once the header phase is performed */
  CRYP_SET_PHASE(hcryp, CRYP_PHASE_PAYLOAD); 
  
  /* Enable the CRYP peripheral */
  __HAL_CRYP_ENABLE(hcryp);
  
#else /* AES */
  
  /* Select payload phase once the header phase is performed */
  CRYP_SET_PHASE(hcryp, CRYP_PHASE_PAYLOAD);
  
#endif /* End AES or CRYP  */ 
  
  if ((hcryp->Size % 16U) != 0U) 
  {
    /* recalculate  wordsize */ 
    wordsize =  ((wordsize/4U)*4U) ; 
  }
  
  /* Get tick */
  tickstart = HAL_GetTick();
  /*Temporary CrypOutCount Value*/
  outcount = hcryp->CrypOutCount;
  
  /* Write input data and get output Data */
  while((hcryp->CrypInCount < wordsize) && (outcount < wordsize))
  {      
    /* Write plain data and get cipher data */
    CRYP_AES_ProcessData(hcryp,Timeout);
    
    /*Temporary CrypOutCount Value*/
    outcount = hcryp->CrypOutCount; 
    
    /* Check for the Timeout */
    if(Timeout != HAL_MAX_DELAY)
    {
      if(((HAL_GetTick() - tickstart ) > Timeout)||(Timeout == 0U))
      {
        /* Disable the CRYP peripheral clock */
        __HAL_CRYP_DISABLE(hcryp);
        
        /* Change state & error code */
        hcryp->ErrorCode |= HAL_CRYP_ERROR_TIMEOUT;
        hcryp->State = HAL_CRYP_STATE_READY;
        
        /* Process unlocked */          
        __HAL_UNLOCK(hcryp); 
        return HAL_ERROR;
      }
    }
  }
  
  if ((hcryp->Size % 16U) != 0U) 
  {
    /*  Workaround 2 :  CRYP1 & AES generates correct TAG for GCM mode only when input block size is multiple of
    128 bits. If lthe size of the last block of payload is inferior to 128 bits, when GCM encryption
    is selected, then the TAG message will be wrong.*/   
    CRYP_Workaround(hcryp,Timeout);   
  }
  
>>>>>>> 49e424905b5922b07aa7166ec7a0eeb90adf58a8
  /* Return function status */
  return HAL_OK;
}

/**
<<<<<<< HEAD
  * @brief  Initializes the CRYP peripheral in DES ECB decryption mode using IT.
  * @param  hcryp pointer to a CRYP_HandleTypeDef structure that contains
  *         the configuration information for CRYP module
  * @param  pPlainData Pointer to the plaintext buffer
  * @param  Size Length of the plaintext buffer, must be a multiple of 8
  * @param  pCypherData Pointer to the cyphertext buffer
  * @retval HAL status
  */
HAL_StatusTypeDef HAL_CRYP_DESECB_Decrypt_IT(CRYP_HandleTypeDef *hcryp, uint8_t *pCypherData, uint16_t Size, uint8_t *pPlainData)
{
  uint32_t inputaddr;
  uint32_t outputaddr;
  
  if(hcryp->State == HAL_CRYP_STATE_READY)
  {
    /* Process Locked */
    __HAL_LOCK(hcryp);
    
    hcryp->CrypInCount = Size;
    hcryp->pCrypInBuffPtr = pCypherData;
    hcryp->pCrypOutBuffPtr = pPlainData;
    hcryp->CrypOutCount = Size;
    
    /* Change the CRYP state */
    hcryp->State = HAL_CRYP_STATE_BUSY;
    
    /* Set CRYP peripheral in DES ECB decryption mode */
    CRYP_SetDESECBMode(hcryp, CRYP_CR_ALGODIR);
    
    /* Enable Interrupts */
    __HAL_CRYP_ENABLE_IT(hcryp, CRYP_IT_INI | CRYP_IT_OUTI);
    
    /* Enable CRYP */
    __HAL_CRYP_ENABLE(hcryp);
    
    /* Return function status */
    return HAL_OK;
  }
  else if(__HAL_CRYP_GET_IT(hcryp, CRYP_IT_INI))
  {
    inputaddr = (uint32_t)hcryp->pCrypInBuffPtr;
    /* Write the Input block in the IN FIFO */
    hcryp->Instance->DR = *(uint32_t*)(inputaddr);
    inputaddr+=4;
    hcryp->Instance->DR = *(uint32_t*)(inputaddr);
    
    hcryp->pCrypInBuffPtr += 8;
    hcryp->CrypInCount -= 8;
    if(hcryp->CrypInCount == 0)
    {
      __HAL_CRYP_DISABLE_IT(hcryp, CRYP_IT_INI);
      /* Call the Input data transfer complete callback */
      HAL_CRYP_InCpltCallback(hcryp);
    }
  }
  else if(__HAL_CRYP_GET_IT(hcryp, CRYP_IT_OUTI))
  {
    outputaddr = (uint32_t)hcryp->pCrypOutBuffPtr;
    /* Read the Output block from the Output FIFO */
    *(uint32_t*)(outputaddr) = hcryp->Instance->DOUT;
    outputaddr+=4;
    *(uint32_t*)(outputaddr) = hcryp->Instance->DOUT;

    hcryp->pCrypOutBuffPtr += 8;
    hcryp->CrypOutCount -= 8;
    if(hcryp->CrypOutCount == 0)
    {
      /* Disable IT */
      __HAL_CRYP_DISABLE_IT(hcryp, CRYP_IT_OUTI);
      /* Disable CRYP */
      __HAL_CRYP_DISABLE(hcryp);
      /* Process Unlocked */
      __HAL_UNLOCK(hcryp);
      /* Change the CRYP state */
      hcryp->State = HAL_CRYP_STATE_READY;
      /* Call Input transfer complete callback */
      HAL_CRYP_OutCpltCallback(hcryp);
    }
  }
  
  /* Return function status */
  return HAL_OK;
}

/**
  * @brief  Initializes the CRYP peripheral in DES ECB decryption mode using interrupt.
  * @param  hcryp pointer to a CRYP_HandleTypeDef structure that contains
  *         the configuration information for CRYP module
  * @param  pPlainData Pointer to the plaintext buffer
  * @param  Size Length of the plaintext buffer, must be a multiple of 8
  * @param  pCypherData Pointer to the cyphertext buffer
  * @retval HAL status
  */
HAL_StatusTypeDef HAL_CRYP_DESCBC_Decrypt_IT(CRYP_HandleTypeDef *hcryp, uint8_t *pCypherData, uint16_t Size, uint8_t *pPlainData)
{
  uint32_t inputaddr;
  uint32_t outputaddr;
  
  if(hcryp->State == HAL_CRYP_STATE_READY)
  {
    /* Process Locked */
    __HAL_LOCK(hcryp);
    
    hcryp->CrypInCount = Size;
    hcryp->pCrypInBuffPtr = pCypherData;
    hcryp->pCrypOutBuffPtr = pPlainData;
    hcryp->CrypOutCount = Size;
    
    /* Change the CRYP state */
    hcryp->State = HAL_CRYP_STATE_BUSY;
    
    /* Set CRYP peripheral in DES CBC decryption mode */
    CRYP_SetDESCBCMode(hcryp, CRYP_CR_ALGODIR);
    
    /* Enable Interrupts */
    __HAL_CRYP_ENABLE_IT(hcryp, CRYP_IT_INI | CRYP_IT_OUTI);
    
    /* Enable CRYP */
    __HAL_CRYP_ENABLE(hcryp);
    
    /* Return function status */
    return HAL_OK;
  }
  else if(__HAL_CRYP_GET_IT(hcryp, CRYP_IT_INI))
  {
    inputaddr = (uint32_t)hcryp->pCrypInBuffPtr;
    /* Write the Input block in the IN FIFO */
    hcryp->Instance->DR = *(uint32_t*)(inputaddr);
    inputaddr+=4;
    hcryp->Instance->DR = *(uint32_t*)(inputaddr);

    hcryp->pCrypInBuffPtr += 8;
    hcryp->CrypInCount -= 8;
    if(hcryp->CrypInCount == 0)
    {
      __HAL_CRYP_DISABLE_IT(hcryp, CRYP_IT_INI);
      /* Call the Input data transfer complete callback */
      HAL_CRYP_InCpltCallback(hcryp);
    }
  }
  else if(__HAL_CRYP_GET_IT(hcryp, CRYP_IT_OUTI))
  {
    outputaddr = (uint32_t)hcryp->pCrypOutBuffPtr;
    /* Read the Output block from the Output FIFO */
    *(uint32_t*)(outputaddr) = hcryp->Instance->DOUT;
    outputaddr+=4;
    *(uint32_t*)(outputaddr) = hcryp->Instance->DOUT;

    hcryp->pCrypOutBuffPtr += 8;
    hcryp->CrypOutCount -= 8;
    if(hcryp->CrypOutCount == 0)
    {
      /* Disable IT */
      __HAL_CRYP_DISABLE_IT(hcryp, CRYP_IT_OUTI);
      /* Disable CRYP */
      __HAL_CRYP_DISABLE(hcryp);
      /* Process Unlocked */
      __HAL_UNLOCK(hcryp);
      /* Change the CRYP state */
      hcryp->State = HAL_CRYP_STATE_READY;
      /* Call Input transfer complete callback */
      HAL_CRYP_OutCpltCallback(hcryp);
    }
  }
=======
  * @brief  Encryption/Decryption process in AES GCM mode and prepare the authentication TAG in interrupt mode
  * @param  hcryp: pointer to a CRYP_HandleTypeDef structure that contains
  *         the configuration information for CRYP module
  * @retval HAL status
  */
static HAL_StatusTypeDef CRYP_AESGCM_Process_IT(CRYP_HandleTypeDef *hcryp)
{
  __IO uint32_t count = 0U;
#if defined(AES) 
  uint32_t loopcounter;
  uint32_t lastwordsize; 
  uint32_t npblb;
#endif /* AES */ 
  
  /*  Reset CrypHeaderCount */
  hcryp->CrypHeaderCount =0U;
  
  /******************************* Init phase *********************************/
  
  CRYP_SET_PHASE(hcryp,CRYP_PHASE_INIT);
  
  /* Set the key */
  CRYP_SetKey(hcryp, hcryp->Init.KeySize);
  
#if defined(CRYP)     
  /* Set the initialization vector and the counter : Initial Counter Block (ICB)*/
  hcryp->Instance->IV0LR = *(uint32_t*)(hcryp->Init.pInitVect);
  hcryp->Instance->IV0RR = *(uint32_t*)(hcryp->Init.pInitVect+1);
  hcryp->Instance->IV1LR = *(uint32_t*)(hcryp->Init.pInitVect+2);
  hcryp->Instance->IV1RR = *(uint32_t*)(hcryp->Init.pInitVect+3);
  
  /* Enable the CRYP peripheral */
  __HAL_CRYP_ENABLE(hcryp);
  
  /*Wait for the CRYPEN bit to be cleared*/
  count = CRYP_TIMEOUT_GCMCCMINITPHASE;
  do
  {
    count-- ;
    if(count == 0U)
    {
      /* Disable the CRYP peripheral clock */
      __HAL_CRYP_DISABLE(hcryp);
      
      /* Change state */
      hcryp->ErrorCode |= HAL_CRYP_ERROR_TIMEOUT;
      hcryp->State = HAL_CRYP_STATE_READY; 
      
      /* Process unlocked */          
      __HAL_UNLOCK(hcryp); 
      return HAL_ERROR;
    }
  }
  while((hcryp->Instance->CR & CRYP_CR_CRYPEN) == CRYP_CR_CRYPEN);
  
#else /* AES */
  
  /* Workaround 1 : only AES
  Datatype configuration must be 32 bits during INIT phase. Only, after INIT, and before re
  enabling the IP, datatype different from 32 bits can be configured.*/
  /* Select DATATYPE 32  */
  MODIFY_REG(hcryp->Instance->CR, AES_CR_DATATYPE, CRYP_DATATYPE_32B);   
  
  /* Set the initialization vector and the counter : Initial Counter Block (ICB)*/
  hcryp->Instance->IVR3 = *(uint32_t*)(hcryp->Init.pInitVect);
  hcryp->Instance->IVR2 = *(uint32_t*)(hcryp->Init.pInitVect+1);
  hcryp->Instance->IVR1 = *(uint32_t*)(hcryp->Init.pInitVect+2);
  hcryp->Instance->IVR0 = *(uint32_t*)(hcryp->Init.pInitVect+3);    
  
  /* Enable the CRYP peripheral */
  __HAL_CRYP_ENABLE(hcryp);
  
  /* just wait for hash computation */
  count = CRYP_TIMEOUT_GCMCCMINITPHASE;
  do
  {
    count-- ;
    if(count == 0U)
    {
      /* Disable the CRYP peripheral clock */
      __HAL_CRYP_DISABLE(hcryp);
      
      /* Change state */
      hcryp->ErrorCode |= HAL_CRYP_ERROR_TIMEOUT;
      hcryp->State = HAL_CRYP_STATE_READY;
      
      /* Process unlocked */          
      __HAL_UNLOCK(hcryp); 
      return HAL_ERROR;
    }
  }
  while(HAL_IS_BIT_CLR(hcryp->Instance->SR, AES_SR_CCF));
  
  /* Clear CCF flag */
  __HAL_CRYP_CLEAR_FLAG(hcryp, CRYP_CCF_CLEAR);
  
#endif /* End AES or CRYP */
  
  /***************************** Header phase *********************************/   
  
#if defined(CRYP)  
  
  /* Select header phase */
  CRYP_SET_PHASE(hcryp, CRYP_PHASE_HEADER);  
  
  /* Enable interrupts */
  __HAL_CRYP_ENABLE_IT(hcryp, CRYP_IT_INI);
  
  /* Enable CRYP */
  __HAL_CRYP_ENABLE(hcryp);
  
#else /* AES */
  
  /* Workaround 1: only AES , before re-enabling the IP, datatype can be configured*/
  MODIFY_REG(hcryp->Instance->CR, AES_CR_DATATYPE, hcryp->Init.DataType); 
  
  /* Select header phase */
  CRYP_SET_PHASE(hcryp, CRYP_PHASE_HEADER); 
  
  /* Enable computation complete flag and error interrupts */
  __HAL_CRYP_ENABLE_IT(hcryp,CRYP_IT_CCFIE | CRYP_IT_ERRIE);    
  
  /* Enable the CRYP peripheral */
  __HAL_CRYP_ENABLE(hcryp);
  
  if(hcryp->Init.HeaderSize == 0U) /*header phase is  skipped*/
  {
    /* Set the phase */
    hcryp->Phase = CRYP_PHASE_PROCESS;
    
    /* Select payload phase once the header phase is performed */
    MODIFY_REG(hcryp->Instance->CR, AES_CR_GCMPH, CRYP_PHASE_PAYLOAD);
    
    /* Write the payload Input block in the IN FIFO */ 
    if(hcryp->Size == 0U)
    {     
      /* Disable interrupts */
      __HAL_CRYP_DISABLE_IT(hcryp, CRYP_IT_CCFIE| CRYP_IT_ERRIE);
      
      /* Change the CRYP state */
      hcryp->State = HAL_CRYP_STATE_READY;
      
      /* Process unlocked */
      __HAL_UNLOCK(hcryp);
    }            
    else if (hcryp->Size >= 16U)
    {       
      hcryp->Instance->DINR  = *(uint32_t *)(hcryp->pCrypInBuffPtr + hcryp->CrypInCount );
      hcryp->CrypInCount++;
      hcryp->Instance->DINR  = *(uint32_t *)(hcryp->pCrypInBuffPtr + hcryp->CrypInCount );
      hcryp->CrypInCount++;   
      hcryp->Instance->DINR  = *(uint32_t *)(hcryp->pCrypInBuffPtr + hcryp->CrypInCount );
      hcryp->CrypInCount++;
      hcryp->Instance->DINR  = *(uint32_t *)(hcryp->pCrypInBuffPtr + hcryp->CrypInCount );
      hcryp->CrypInCount++;
      if(hcryp->CrypInCount == ( hcryp->Size/4U))   
      {   
        /* Call Input transfer complete callback */
#if (USE_HAL_CRYP_REGISTER_CALLBACKS == 1) 
        /*Call registered Input complete callback*/
        hcryp->InCpltCallback(hcryp);
#else
        /*Call legacy weak Input complete callback*/
        HAL_CRYP_InCpltCallback(hcryp);
#endif /* USE_HAL_CRYP_REGISTER_CALLBACKS */
      } 
    }
    else /* Size < 16Bytes  : first block is the last block*/
    {
      /* Workaround not implemented*/  
      /* Size should be %4  otherwise Tag will  be incorrectly generated for GCM Encryption:
      Workaround is implemented in polling mode, so if last block of 
      payload <128bit don't use CRYP_Encrypt_IT otherwise TAG is incorrectly generated for GCM Encryption. */
      
      /* Compute the number of padding bytes in last block of payload */
      npblb = 16U- (uint32_t)(hcryp->Size); 
      
      /* Number of valid words (lastwordsize) in last block */
      if ((npblb % 4U) ==0U) 
      { 
        lastwordsize = (16U-npblb)/4U;		
      }
      else 
      {
        lastwordsize = ((16U-npblb)/4U) +1U;
      }
      
      /*  last block optionally pad the data with zeros*/
      for(loopcounter = 0U; loopcounter < lastwordsize ; loopcounter++)
      {
        hcryp->Instance->DINR = *(uint32_t *)(hcryp->pCrypInBuffPtr + hcryp->CrypInCount );
        hcryp->CrypInCount++;
      }
      while(loopcounter < 4U )
      { 
        /* pad the data with zeros to have a complete block */     
        hcryp->Instance->DINR = 0x0U;         
        loopcounter++;
      }
    }
  }
  else if ((hcryp->Init.HeaderSize) < 4U)
  {
    for(loopcounter = 0U; loopcounter < hcryp->Init.HeaderSize ; loopcounter++)
    {
      hcryp->Instance->DINR = *(uint32_t*)(hcryp->Init.Header + hcryp->CrypHeaderCount);  
      hcryp->CrypHeaderCount++ ;
    }
    while(loopcounter < 4U )
    { 
      /* pad the data with zeros to have a complete block */     
      hcryp->Instance->DINR = 0x0U;         
      loopcounter++;
    }
    /* Set the phase */
    hcryp->Phase = CRYP_PHASE_PROCESS;
    
    /* Select payload phase once the header phase is performed */
    CRYP_SET_PHASE(hcryp, CRYP_PHASE_PAYLOAD);
    
    /* Call Input transfer complete callback */
#if (USE_HAL_CRYP_REGISTER_CALLBACKS == 1) 
    /*Call registered Input complete callback*/
    hcryp->InCpltCallback(hcryp);
#else
    /*Call legacy weak Input complete callback*/
    HAL_CRYP_InCpltCallback(hcryp);
#endif /* USE_HAL_CRYP_REGISTER_CALLBACKS */  
  } 
  else if ((hcryp->Init.HeaderSize) >= 4U)
  {  
    /* Write the input block in the IN FIFO */
    hcryp->Instance->DINR  = *(uint32_t *)(hcryp->Init.Header + hcryp->CrypHeaderCount );
    hcryp->CrypHeaderCount++;
    hcryp->Instance->DINR  = *(uint32_t *)(hcryp->Init.Header + hcryp->CrypHeaderCount );
    hcryp->CrypHeaderCount++;   
    hcryp->Instance->DINR  = *(uint32_t *)(hcryp->Init.Header + hcryp->CrypHeaderCount );
    hcryp->CrypHeaderCount++;
    hcryp->Instance->DINR  = *(uint32_t *)(hcryp->Init.Header + hcryp->CrypHeaderCount );
    hcryp->CrypHeaderCount++;  
  }
  else
  {
    /* Nothing to do */
  }  
  
#endif /* End AES or CRYP */      
>>>>>>> 49e424905b5922b07aa7166ec7a0eeb90adf58a8
  
  /* Return function status */
  return HAL_OK;
}

<<<<<<< HEAD
/**
  * @brief  Initializes the CRYP peripheral in DES ECB encryption mode using DMA.
  * @param  hcryp pointer to a CRYP_HandleTypeDef structure that contains
  *         the configuration information for CRYP module
  * @param  pPlainData Pointer to the plaintext buffer
  * @param  Size Length of the plaintext buffer, must be a multiple of 8
  * @param  pCypherData Pointer to the cyphertext buffer
  * @retval HAL status
  */
HAL_StatusTypeDef HAL_CRYP_DESECB_Encrypt_DMA(CRYP_HandleTypeDef *hcryp, uint8_t *pPlainData, uint16_t Size, uint8_t *pCypherData)
{
  uint32_t inputaddr;
  uint32_t outputaddr;
  
  if((hcryp->State == HAL_CRYP_STATE_READY) || (hcryp->Phase == HAL_CRYP_PHASE_PROCESS))
  {
    /* Process Locked */
    __HAL_LOCK(hcryp);
    
    inputaddr  = (uint32_t)pPlainData;
    outputaddr = (uint32_t)pCypherData;
    
    /* Change the CRYP state */
    hcryp->State = HAL_CRYP_STATE_BUSY;
    
    /* Set CRYP peripheral in DES ECB encryption mode */
    CRYP_SetDESECBMode(hcryp, 0);
    
    /* Set the input and output addresses and start DMA transfer */ 
    CRYP_SetDMAConfig(hcryp, inputaddr, Size, outputaddr);
    
    /* Process Unlocked */
    __HAL_UNLOCK(hcryp);
    
    /* Return function status */
    return HAL_OK;
  }
  else
  {
    return HAL_ERROR;   
  }
}

/**
  * @brief  Initializes the CRYP peripheral in DES CBC encryption mode using DMA.
  * @param  hcryp pointer to a CRYP_HandleTypeDef structure that contains
  *         the configuration information for CRYP module
  * @param  pPlainData Pointer to the plaintext buffer
  * @param  Size Length of the plaintext buffer, must be a multiple of 8
  * @param  pCypherData Pointer to the cyphertext buffer
  * @retval HAL status
  */
HAL_StatusTypeDef HAL_CRYP_DESCBC_Encrypt_DMA(CRYP_HandleTypeDef *hcryp, uint8_t *pPlainData, uint16_t Size, uint8_t *pCypherData)
{
  uint32_t inputaddr;
  uint32_t outputaddr;
  
  if((hcryp->State == HAL_CRYP_STATE_READY) || (hcryp->Phase == HAL_CRYP_PHASE_PROCESS))
  {
    /* Process Locked */
    __HAL_LOCK(hcryp);
    
    inputaddr  = (uint32_t)pPlainData;
    outputaddr = (uint32_t)pCypherData;
    
    /* Change the CRYP state */
    hcryp->State = HAL_CRYP_STATE_BUSY;
    
    /* Set CRYP peripheral in DES CBC encryption mode */
    CRYP_SetDESCBCMode(hcryp, 0);
    
    /* Set the input and output addresses and start DMA transfer */ 
    CRYP_SetDMAConfig(hcryp, inputaddr, Size, outputaddr);
    
    /* Process Unlocked */
    __HAL_UNLOCK(hcryp);
    
    /* Return function status */
    return HAL_OK;
  }
  else
  {
    return HAL_ERROR;   
  }
}

/**
  * @brief  Initializes the CRYP peripheral in DES ECB decryption mode using DMA.
  * @param  hcryp pointer to a CRYP_HandleTypeDef structure that contains
  *         the configuration information for CRYP module
  * @param  pPlainData Pointer to the plaintext buffer
  * @param  Size Length of the plaintext buffer, must be a multiple of 8
  * @param  pCypherData Pointer to the cyphertext buffer
  * @retval HAL status
  */
HAL_StatusTypeDef HAL_CRYP_DESECB_Decrypt_DMA(CRYP_HandleTypeDef *hcryp, uint8_t *pCypherData, uint16_t Size, uint8_t *pPlainData)
{
  uint32_t inputaddr;
  uint32_t outputaddr;
  
  if((hcryp->State == HAL_CRYP_STATE_READY) || (hcryp->Phase == HAL_CRYP_PHASE_PROCESS))
  {
    /* Process Locked */
    __HAL_LOCK(hcryp);
    
    inputaddr  = (uint32_t)pCypherData;
    outputaddr = (uint32_t)pPlainData;
    
    /* Change the CRYP state */
    hcryp->State = HAL_CRYP_STATE_BUSY;
    
    /* Set CRYP peripheral in DES ECB decryption mode */
    CRYP_SetDESECBMode(hcryp, CRYP_CR_ALGODIR);
    
    /* Set the input and output addresses and start DMA transfer */ 
    CRYP_SetDMAConfig(hcryp, inputaddr, Size, outputaddr);
    
    /* Process Unlocked */
    __HAL_UNLOCK(hcryp);
    
    /* Return function status */
    return HAL_OK;
  }
  else
  {
    return HAL_ERROR;   
  }
}

/**
  * @brief  Initializes the CRYP peripheral in DES ECB decryption mode using DMA.
  * @param  hcryp pointer to a CRYP_HandleTypeDef structure that contains
  *         the configuration information for CRYP module
  * @param  pPlainData Pointer to the plaintext buffer
  * @param  Size Length of the plaintext buffer, must be a multiple of 8
  * @param  pCypherData Pointer to the cyphertext buffer
  * @retval HAL status
  */
HAL_StatusTypeDef HAL_CRYP_DESCBC_Decrypt_DMA(CRYP_HandleTypeDef *hcryp, uint8_t *pCypherData, uint16_t Size, uint8_t *pPlainData)
{
  uint32_t inputaddr;
  uint32_t outputaddr;
  
  if((hcryp->State == HAL_CRYP_STATE_READY) || (hcryp->Phase == HAL_CRYP_PHASE_PROCESS))
  {
    /* Process Locked */
    __HAL_LOCK(hcryp);
    
    inputaddr  = (uint32_t)pCypherData;
    outputaddr = (uint32_t)pPlainData;
    
    /* Change the CRYP state */
    hcryp->State = HAL_CRYP_STATE_BUSY;
    
    /* Set CRYP peripheral in DES CBC decryption mode */
    CRYP_SetDESCBCMode(hcryp, CRYP_CR_ALGODIR);
    
    /* Set the input and output addresses and start DMA transfer */ 
    CRYP_SetDMAConfig(hcryp, inputaddr, Size, outputaddr);
    
    /* Process Unlocked */
    __HAL_UNLOCK(hcryp);
    
    /* Return function status */
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

/** @defgroup CRYP_Exported_Functions_Group4 TDES processing functions 
 *  @brief   processing functions. 
 *
@verbatim   
  ==============================================================================
                      ##### TDES processing functions #####
  ==============================================================================  
    [..]  This section provides functions allowing to:
      (+) Encrypt plaintext using TDES based on ECB or CBC chaining modes
      (+) Decrypt cyphertext using TDES based on ECB or CBC chaining modes
    [..]  Three processing functions are available:
      (+) Polling mode
      (+) Interrupt mode
      (+) DMA mode

@endverbatim
  * @{
  */

/**
  * @brief  Initializes the CRYP peripheral in TDES ECB encryption mode
  *         then encrypt pPlainData. The cypher data are available in pCypherData
  * @param  hcryp pointer to a CRYP_HandleTypeDef structure that contains
  *         the configuration information for CRYP module
  * @param  pPlainData Pointer to the plaintext buffer
  * @param  Size Length of the plaintext buffer, must be a multiple of 8
  * @param  pCypherData Pointer to the cyphertext buffer
  * @param  Timeout Specify Timeout value  
  * @retval HAL status
  */
HAL_StatusTypeDef HAL_CRYP_TDESECB_Encrypt(CRYP_HandleTypeDef *hcryp, uint8_t *pPlainData, uint16_t Size, uint8_t *pCypherData, uint32_t Timeout)
{
  /* Process Locked */
  __HAL_LOCK(hcryp);
  
  /* Change the CRYP state */
  hcryp->State = HAL_CRYP_STATE_BUSY;
  
  /* Set CRYP peripheral in TDES ECB encryption mode */
  CRYP_SetTDESECBMode(hcryp, 0);
  
  /* Enable CRYP */
  __HAL_CRYP_ENABLE(hcryp);
  
  /* Write Plain Data and Get Cypher Data */
  if(CRYP_ProcessData2Words(hcryp, pPlainData, Size, pCypherData, Timeout) != HAL_OK)
  {
    return HAL_TIMEOUT;
  }
  
  /* Change the CRYP state */
  hcryp->State = HAL_CRYP_STATE_READY;
  
  /* Process Unlocked */
  __HAL_UNLOCK(hcryp);
  
  /* Return function status */
  return HAL_OK;
}

/**
  * @brief  Initializes the CRYP peripheral in TDES ECB decryption mode
  *         then decrypted pCypherData. The cypher data are available in pPlainData
  * @param  hcryp pointer to a CRYP_HandleTypeDef structure that contains
  *         the configuration information for CRYP module
  * @param  pPlainData Pointer to the plaintext buffer
  * @param  Size Length of the plaintext buffer, must be a multiple of 8
  * @param  pCypherData Pointer to the cyphertext buffer
  * @param  Timeout Specify Timeout value  
  * @retval HAL status
  */
HAL_StatusTypeDef HAL_CRYP_TDESECB_Decrypt(CRYP_HandleTypeDef *hcryp, uint8_t *pCypherData, uint16_t Size, uint8_t *pPlainData, uint32_t Timeout)
{  
  /* Process Locked */
  __HAL_LOCK(hcryp);
  
  /* Change the CRYP state */
  hcryp->State = HAL_CRYP_STATE_BUSY;
  
  /* Set CRYP peripheral in TDES ECB decryption mode */
  CRYP_SetTDESECBMode(hcryp, CRYP_CR_ALGODIR);
  
  /* Enable CRYP */
  __HAL_CRYP_ENABLE(hcryp);
  
  /* Write Cypher Data and Get Plain Data */
  if(CRYP_ProcessData2Words(hcryp, pCypherData, Size, pPlainData, Timeout) != HAL_OK)
  {
    return HAL_TIMEOUT;
  }
  
  /* Change the CRYP state */
  hcryp->State = HAL_CRYP_STATE_READY;
  
  /* Process Unlocked */
  __HAL_UNLOCK(hcryp);
  
  /* Return function status */
  return HAL_OK;
}

/**
  * @brief  Initializes the CRYP peripheral in TDES CBC encryption mode
  *         then encrypt pPlainData. The cypher data are available in pCypherData
  * @param  hcryp pointer to a CRYP_HandleTypeDef structure that contains
  *         the configuration information for CRYP module
  * @param  pPlainData Pointer to the plaintext buffer
  * @param  Size Length of the plaintext buffer, must be a multiple of 8
  * @param  pCypherData Pointer to the cyphertext buffer
  * @param  Timeout Specify Timeout value  
  * @retval HAL status
  */
HAL_StatusTypeDef HAL_CRYP_TDESCBC_Encrypt(CRYP_HandleTypeDef *hcryp, uint8_t *pPlainData, uint16_t Size, uint8_t *pCypherData, uint32_t Timeout)
{
  /* Process Locked */
  __HAL_LOCK(hcryp);
  
  /* Change the CRYP state */
  hcryp->State = HAL_CRYP_STATE_BUSY;
  
  /* Set CRYP peripheral in TDES CBC encryption mode */
  CRYP_SetTDESCBCMode(hcryp, 0);
  
  /* Enable CRYP */
  __HAL_CRYP_ENABLE(hcryp);
  
  /* Write Plain Data and Get Cypher Data */
  if(CRYP_ProcessData2Words(hcryp, pPlainData, Size, pCypherData, Timeout) != HAL_OK)
  {
    return HAL_TIMEOUT;
  }
  
  /* Change the CRYP state */
  hcryp->State = HAL_CRYP_STATE_READY;
  
  /* Process Unlocked */
  __HAL_UNLOCK(hcryp);
  
  /* Return function status */
  return HAL_OK;
}

/**
  * @brief  Initializes the CRYP peripheral in TDES CBC decryption mode
  *         then decrypted pCypherData. The cypher data are available in pPlainData
  * @param  hcryp pointer to a CRYP_HandleTypeDef structure that contains
  *         the configuration information for CRYP module
  * @param  pCypherData Pointer to the cyphertext buffer
  * @param  Size Length of the plaintext buffer, must be a multiple of 8
  * @param  pPlainData Pointer to the plaintext buffer
  * @param  Timeout Specify Timeout value  
  * @retval HAL status
  */
HAL_StatusTypeDef HAL_CRYP_TDESCBC_Decrypt(CRYP_HandleTypeDef *hcryp, uint8_t *pCypherData, uint16_t Size, uint8_t *pPlainData, uint32_t Timeout)
{
  /* Process Locked */
  __HAL_LOCK(hcryp);
  
  /* Change the CRYP state */
  hcryp->State = HAL_CRYP_STATE_BUSY;
  
  /* Set CRYP peripheral in TDES CBC decryption mode */
  CRYP_SetTDESCBCMode(hcryp, CRYP_CR_ALGODIR);
  
  /* Enable CRYP */
  __HAL_CRYP_ENABLE(hcryp);
  
  /* Write Cypher Data and Get Plain Data */
  if(CRYP_ProcessData2Words(hcryp, pCypherData, Size, pPlainData, Timeout) != HAL_OK)
  {
    return HAL_TIMEOUT;
  }
  
  /* Change the CRYP state */
  hcryp->State = HAL_CRYP_STATE_READY;
  
  /* Process Unlocked */
  __HAL_UNLOCK(hcryp);
=======

/**
  * @brief  Encryption/Decryption process in AES GCM mode and prepare the authentication TAG using DMA
  * @param  hcryp: pointer to a CRYP_HandleTypeDef structure that contains
  *         the configuration information for CRYP module
  * @retval HAL status
  */
static HAL_StatusTypeDef CRYP_AESGCM_Process_DMA(CRYP_HandleTypeDef *hcryp)
{
  __IO uint32_t count = 0U;
  uint32_t wordsize;
  
  /*  Reset CrypHeaderCount */
  hcryp->CrypHeaderCount = 0U;
  
  /*************************** Init phase ************************************/
  
  CRYP_SET_PHASE(hcryp,CRYP_PHASE_INIT);
  
  /* Set the key */
  CRYP_SetKey(hcryp, hcryp->Init.KeySize);
  
#if defined(CRYP)     
  /* Set the initialization vector and the counter : Initial Counter Block (ICB)*/
  hcryp->Instance->IV0LR = *(uint32_t*)(hcryp->Init.pInitVect);
  hcryp->Instance->IV0RR = *(uint32_t*)(hcryp->Init.pInitVect+1);
  hcryp->Instance->IV1LR = *(uint32_t*)(hcryp->Init.pInitVect+2);
  hcryp->Instance->IV1RR = *(uint32_t*)(hcryp->Init.pInitVect+3);
  
  /* Enable the CRYP peripheral */
  __HAL_CRYP_ENABLE(hcryp);
  
  /*Wait for the CRYPEN bit to be cleared*/
  count = CRYP_TIMEOUT_GCMCCMINITPHASE;
  do
  {
    count-- ;
    if(count == 0U)
    {
      /* Disable the CRYP peripheral clock */
      __HAL_CRYP_DISABLE(hcryp);
      
      /* Change state */
      hcryp->ErrorCode |= HAL_CRYP_ERROR_TIMEOUT;
      hcryp->State = HAL_CRYP_STATE_READY; 
      
      /* Process unlocked */          
      __HAL_UNLOCK(hcryp); 
      return HAL_ERROR;
    }
  }
  while((hcryp->Instance->CR & CRYP_CR_CRYPEN) == CRYP_CR_CRYPEN);
  
#else /* AES */
  
  /*Workaround 1 : only AES
  Datatype configuration must be 32 bits during Init phase. Only, after Init, and before re
  enabling the IP, datatype different from 32 bits can be configured.*/
  /* Select DATATYPE 32  */
  MODIFY_REG(hcryp->Instance->CR, AES_CR_DATATYPE, CRYP_DATATYPE_32B);   
  
  /* Set the initialization vector and the counter : Initial Counter Block (ICB)*/
  hcryp->Instance->IVR3 = *(uint32_t*)(hcryp->Init.pInitVect);
  hcryp->Instance->IVR2 = *(uint32_t*)(hcryp->Init.pInitVect+1);
  hcryp->Instance->IVR1 = *(uint32_t*)(hcryp->Init.pInitVect+2);
  hcryp->Instance->IVR0 = *(uint32_t*)(hcryp->Init.pInitVect+3);  
  
  /* Enable the CRYP peripheral */
  __HAL_CRYP_ENABLE(hcryp);
  
  /* just wait for hash computation */
  count = CRYP_TIMEOUT_GCMCCMINITPHASE;
  do
  {
    count-- ;
    if(count == 0U)
    {
      /* Disable the CRYP peripheral clock */
      __HAL_CRYP_DISABLE(hcryp);
      
      /* Change state */
      hcryp->ErrorCode |= HAL_CRYP_ERROR_TIMEOUT;
      hcryp->State = HAL_CRYP_STATE_READY; 
      
      /* Process unlocked */          
      __HAL_UNLOCK(hcryp); 
      return HAL_ERROR;
    }
  }
  while(HAL_IS_BIT_CLR(hcryp->Instance->SR, AES_SR_CCF));
  
  /* Clear CCF flag */
  __HAL_CRYP_CLEAR_FLAG(hcryp, CRYP_CCF_CLEAR);
  
#endif /* End AES or CRYP */
  
  /************************ Header phase *************************************/
  
  if(CRYP_GCMCCM_SetHeaderPhase_DMA(hcryp) != HAL_OK)
  {
    return HAL_ERROR;
  }
  
  /************************ Payload phase ************************************/   
  
  /* Set the phase */
  hcryp->Phase = CRYP_PHASE_PROCESS;  
  
#if defined(CRYP)
  
  /* Disable the CRYP peripheral */
  __HAL_CRYP_DISABLE(hcryp);
  
#endif /* CRYP */ 
  
  /* Select payload phase once the header phase is performed */
  CRYP_SET_PHASE(hcryp, CRYP_PHASE_PAYLOAD);
  
  if(hcryp->Size != 0U)
  { 
    /* CRYP1 IP V < 2.2.1  Size should be %4  otherwise Tag will  be incorrectly generated for GCM Encryption:
    Workaround is implemented in polling mode, so if last block of 
    payload <128bit don't use DMA mode otherwise TAG is incorrectly generated . */
    /* Set the input and output addresses and start DMA transfer */ 
    if ((hcryp->Size % 16U) == 0U) 
    {  
      CRYP_SetDMAConfig(hcryp, (uint32_t)( hcryp->pCrypInBuffPtr), (hcryp->Size/4U), (uint32_t)(hcryp->pCrypOutBuffPtr));    
    }
    else /*to compute last word<128bits, otherwise it will not be encrypted/decrypted */
    {
      wordsize = (uint32_t)(hcryp->Size)+(16U-((uint32_t)(hcryp->Size)%16U)) ;
      
      /* Set the input and output addresses and start DMA transfer, pCrypOutBuffPtr size should be %4 */ 
      CRYP_SetDMAConfig(hcryp, (uint32_t)( hcryp->pCrypInBuffPtr), ((uint16_t)wordsize/4U), (uint32_t)(hcryp->pCrypOutBuffPtr));
    }   
  }
  else 
  {
    /* Process unLocked */
    __HAL_UNLOCK(hcryp);
    
    /* Change the CRYP state and phase */
    hcryp->State = HAL_CRYP_STATE_READY;
  } 
  
  /* Return function status */
  return HAL_OK;
}


/**
  * @brief  AES CCM encryption/decryption processing in polling mode 
  *         for TinyAES IP, no encrypt/decrypt performed, only authentication preparation.
  * @param  hcryp: pointer to a CRYP_HandleTypeDef structure that contains
  *         the configuration information for CRYP module
  * @param  Timeout: Timeout duration
  * @retval HAL status
  */
static HAL_StatusTypeDef CRYP_AESCCM_Process(CRYP_HandleTypeDef *hcryp, uint32_t Timeout)
{
  uint32_t tickstart;
  uint32_t wordsize= (uint32_t)(hcryp->Size)/4U;
  uint16_t outcount;  /* Temporary CrypOutCount Value */  
#if defined(AES) 
  uint32_t loopcounter;
  uint32_t npblb;
  uint32_t lastwordsize; 
#endif /* AES */
  
  /*  Reset CrypHeaderCount */
  hcryp->CrypHeaderCount = 0U;     
  
#if defined(CRYP) 
  
  /********************** Init phase ******************************************/
  
  CRYP_SET_PHASE(hcryp,CRYP_PHASE_INIT);
  
  /* Set the key */
  CRYP_SetKey(hcryp, hcryp->Init.KeySize);
  
  /* Set the initialization vector (IV) with CTR1 information */
  hcryp->Instance->IV0LR = (hcryp->Init.B0[0]) & CRYP_CCM_CTR1_0;
  hcryp->Instance->IV0RR = hcryp->Init.B0[1];
  hcryp->Instance->IV1LR = hcryp->Init.B0[2];
  hcryp->Instance->IV1RR = (hcryp->Init.B0[3] & CRYP_CCM_CTR1_1)|  CRYP_CCM_CTR1_2;
  
  
  /* Enable the CRYP peripheral */
  __HAL_CRYP_ENABLE(hcryp);
  
  /*Write  B0 packet into CRYP_DIN Register*/
  if(hcryp->Init.DataType == CRYP_DATATYPE_8B)
  {
    hcryp->Instance->DIN = __REV(*(uint32_t*)(hcryp->Init.B0));
    hcryp->Instance->DIN = __REV( *(uint32_t*)(hcryp->Init.B0+1));
    hcryp->Instance->DIN = __REV(*(uint32_t*)(hcryp->Init.B0+2));
    hcryp->Instance->DIN = __REV(*(uint32_t*)(hcryp->Init.B0+3));
  }
  else if(hcryp->Init.DataType == CRYP_DATATYPE_16B)
  {
    hcryp->Instance->DIN = __ROR(*(uint32_t*)(hcryp->Init.B0), 16);
    hcryp->Instance->DIN = __ROR( *(uint32_t*)(hcryp->Init.B0+1), 16);
    hcryp->Instance->DIN = __ROR(*(uint32_t*)(hcryp->Init.B0+2), 16);
    hcryp->Instance->DIN = __ROR(*(uint32_t*)(hcryp->Init.B0+3), 16);
  }
  else if(hcryp->Init.DataType == CRYP_DATATYPE_1B)
  {
    hcryp->Instance->DIN = __RBIT(*(uint32_t*)(hcryp->Init.B0));
    hcryp->Instance->DIN = __RBIT( *(uint32_t*)(hcryp->Init.B0+1));
    hcryp->Instance->DIN = __RBIT(*(uint32_t*)(hcryp->Init.B0+2));
    hcryp->Instance->DIN = __RBIT(*(uint32_t*)(hcryp->Init.B0+3));
  }
  else
  {
    hcryp->Instance->DIN = *(uint32_t*)(hcryp->Init.B0);
    hcryp->Instance->DIN = *(uint32_t*)(hcryp->Init.B0+1);
    hcryp->Instance->DIN = *(uint32_t*)(hcryp->Init.B0+2);
    hcryp->Instance->DIN = *(uint32_t*)(hcryp->Init.B0+3);
  }
  /* Get tick */
  tickstart = HAL_GetTick();
  
  /*Wait for the CRYPEN bit to be cleared*/
  while((hcryp->Instance->CR & CRYP_CR_CRYPEN) == CRYP_CR_CRYPEN)
  {
    /* Check for the Timeout */
    if(Timeout != HAL_MAX_DELAY)
    {
      if(((HAL_GetTick() - tickstart ) > Timeout)||(Timeout == 0U))
      {
        /* Disable the CRYP peripheral clock */
        __HAL_CRYP_DISABLE(hcryp);
        
        /* Change state */
        hcryp->ErrorCode |= HAL_CRYP_ERROR_TIMEOUT;
        hcryp->State = HAL_CRYP_STATE_READY;  
        
        /* Process unlocked */          
        __HAL_UNLOCK(hcryp); 
        return HAL_ERROR;
      }
    }
  }  
#else /* AES */ 
  /*AES2v1.1.1 : CCM authentication : no init phase, only header and final phase */ 
  /* Select header phase */
  CRYP_SET_PHASE(hcryp, CRYP_PHASE_HEADER); 
  
  /* configured encryption mode */
  MODIFY_REG(hcryp->Instance->CR, AES_CR_MODE, CRYP_OPERATINGMODE_ENCRYPT); 
  
  /* Set the key */
  CRYP_SetKey(hcryp, hcryp->Init.KeySize);     
  
  /* Set the initialization vector with zero values*/ 
  hcryp->Instance->IVR3 = 0U;
  hcryp->Instance->IVR2 = 0U;
  hcryp->Instance->IVR1 = 0U;
  hcryp->Instance->IVR0 = 0U;
  
  /* Enable the CRYP peripheral */
  __HAL_CRYP_ENABLE(hcryp);
  
  /*Write the B0 packet into CRYP_DIN*/
  hcryp->Instance->DINR = *(uint32_t*)(hcryp->Init.B0);
  hcryp->Instance->DINR = *(uint32_t*)(hcryp->Init.B0+1);
  hcryp->Instance->DINR = *(uint32_t*)(hcryp->Init.B0+2);
  hcryp->Instance->DINR = *(uint32_t*)(hcryp->Init.B0+3); 
  
  /*  wait until the end of computation */
  if(CRYP_WaitOnCCFlag(hcryp, Timeout) != HAL_OK)  
  { 
    /* Change state */
    hcryp->ErrorCode |= HAL_CRYP_ERROR_TIMEOUT;
    hcryp->State = HAL_CRYP_STATE_READY;          
    
    /* Process unlocked & return error */
    __HAL_UNLOCK(hcryp);          
    return HAL_ERROR;
  }
  /* Clear CCF flag */
  __HAL_CRYP_CLEAR_FLAG(hcryp, CRYP_CCF_CLEAR);
  
  /* Set the phase */
  hcryp->Phase = CRYP_PHASE_PROCESS;
  
  /* From that point the whole message must be processed, first the Header then the payload.
  First the  Header block(B1) : associated data length expressed in bytes concatenated with Associated Data (A)*/
  
  if (hcryp->Init.HeaderSize != 0U)
  {
    if ((hcryp->Init.HeaderSize %4U )== 0U)
    {     
      /* HeaderSize %4, no padding */ 
      for(loopcounter = 0U; (loopcounter < hcryp->Init.HeaderSize); loopcounter+=4U)
      {       
        /* Write the Input block in the Data Input register */
        hcryp->Instance->DINR = *(uint32_t*)(hcryp->Init.Header + hcryp->CrypHeaderCount);
        hcryp->CrypHeaderCount++ ;  
        hcryp->Instance->DINR = *(uint32_t*)(hcryp->Init.Header + hcryp->CrypHeaderCount);
        hcryp->CrypHeaderCount++ ;  
        hcryp->Instance->DINR  = *(uint32_t*)(hcryp->Init.Header + hcryp->CrypHeaderCount);
        hcryp->CrypHeaderCount++ ;  
        hcryp->Instance->DINR = *(uint32_t*)(hcryp->Init.Header + hcryp->CrypHeaderCount);
        hcryp->CrypHeaderCount++ ;  
        
        if(CRYP_WaitOnCCFlag(hcryp, Timeout) != HAL_OK)  
        { 
          /* Disable the CRYP peripheral clock */
          __HAL_CRYP_DISABLE(hcryp);
          
          /* Change state */
          hcryp->ErrorCode |= HAL_CRYP_ERROR_TIMEOUT;
          hcryp->State = HAL_CRYP_STATE_READY;  
          
          /* Process unlocked */          
          __HAL_UNLOCK(hcryp); 
          return HAL_ERROR;
        }
        /* Clear CCF Flag */
        __HAL_CRYP_CLEAR_FLAG(hcryp, CRYP_CCF_CLEAR);         
      }
    }
    else
    {   
      /*Write Header block in the IN FIFO without last block */
      for(loopcounter = 0U; (loopcounter < ((hcryp->Init.HeaderSize)-(hcryp->Init.HeaderSize %4U ))); loopcounter+=4U)
      {
        /* Write the input block in the data input register */
        hcryp->Instance->DINR = *(uint32_t*)(hcryp->Init.Header + hcryp->CrypHeaderCount);
        hcryp->CrypHeaderCount++ ;  
        hcryp->Instance->DINR = *(uint32_t*)(hcryp->Init.Header + hcryp->CrypHeaderCount);
        hcryp->CrypHeaderCount++ ;  
        hcryp->Instance->DINR  = *(uint32_t*)(hcryp->Init.Header + hcryp->CrypHeaderCount);
        hcryp->CrypHeaderCount++ ;  
        hcryp->Instance->DINR = *(uint32_t*)(hcryp->Init.Header + hcryp->CrypHeaderCount);
        hcryp->CrypHeaderCount++ ; 
        
        if(CRYP_WaitOnCCFlag(hcryp, Timeout) != HAL_OK)  
        { 
          /* Disable the CRYP peripheral clock */
          __HAL_CRYP_DISABLE(hcryp);
          
          /* Change state */
          hcryp->ErrorCode |= HAL_CRYP_ERROR_TIMEOUT;
          hcryp->State = HAL_CRYP_STATE_READY; 
          
          /* Process unlocked */          
          __HAL_UNLOCK(hcryp); 
          return HAL_ERROR;
        }
        /* Clear CCF Flag */
        __HAL_CRYP_CLEAR_FLAG(hcryp, CRYP_CCF_CLEAR);    
      }
      /*  Last block optionally pad the data with zeros*/
      for(loopcounter = 0U; (loopcounter < (hcryp->Init.HeaderSize %4U )); loopcounter++)
      {
        hcryp->Instance->DINR = *(uint32_t*)(hcryp->Init.Header + hcryp->CrypHeaderCount);
        hcryp->CrypHeaderCount++ ;       
      }
      while(loopcounter <4U )
      { 
        /* Pad the data with zeros to have a complete block */      
        hcryp->Instance->DINR = 0x0U;              
        loopcounter++;
      }    
      
      if(CRYP_WaitOnCCFlag(hcryp, Timeout) != HAL_OK)  
      { 
        /* Disable the CRYP peripheral clock */
        __HAL_CRYP_DISABLE(hcryp);
        
        /* Change state */
        hcryp->ErrorCode |= HAL_CRYP_ERROR_TIMEOUT;
        hcryp->State = HAL_CRYP_STATE_READY;
        
        /* Process unlocked */          
        __HAL_UNLOCK(hcryp); 
        return HAL_ERROR;
      }
      /* Clear CCF flag */
      __HAL_CRYP_CLEAR_FLAG(hcryp, CRYP_CCF_CLEAR);  
    }
  }
  /* Then the payload: cleartext payload (not the ciphertext payload).
  Write input Data, no output Data to get */
  if (hcryp->Size != 0U)
  {
    if ((hcryp->Size % 16U) != 0U) 
    {
      /* recalculate  wordsize */ 
      wordsize =  ((wordsize/4U)*4U) ; 
    }
    
    /* Get tick */
    tickstart = HAL_GetTick();
    /*Temporary CrypOutCount Value*/
    outcount = hcryp->CrypOutCount;
    
    while((hcryp->CrypInCount < wordsize) && (outcount < wordsize))
    {      
      /* Write plain data and get cipher data */
      CRYP_AES_ProcessData(hcryp,Timeout);
     
    /*Temporary CrypOutCount Value*/
    outcount = hcryp->CrypOutCount; 
    
      /* Check for the Timeout */
      if(Timeout != HAL_MAX_DELAY)
      {
        if(((HAL_GetTick() - tickstart ) > Timeout)||(Timeout == 0U))
        {
          /* Disable the CRYP peripheral clock */
          __HAL_CRYP_DISABLE(hcryp);
          
          /* Change state */
          hcryp->ErrorCode |= HAL_CRYP_ERROR_TIMEOUT;
          hcryp->State = HAL_CRYP_STATE_READY;  
          
          /* Process unlocked */          
          __HAL_UNLOCK(hcryp); 
          return HAL_ERROR;
        }
      }
    }
    
    if ((hcryp->Size % 16U) != 0U)  
    { 
      /* Compute the number of padding bytes in last block of payload */
      npblb = ((((uint32_t)(hcryp->Size)/16U)+1U)*16U)- (uint32_t)(hcryp->Size); 
      
      /* Number of valid words (lastwordsize) in last block */
      if ((npblb%4U) ==0U) 
      { 
        lastwordsize = (16U-npblb)/4U;		
      }
      else 
      {
        lastwordsize = ((16U-npblb)/4U) +1U;
      }   
      /*  Last block optionally pad the data with zeros*/    
      for(loopcounter=0U; loopcounter < lastwordsize; loopcounter ++)        
      {
        /* Write the last input block in the IN FIFO */
        hcryp->Instance->DINR  = *(uint32_t *)(hcryp->pCrypInBuffPtr + hcryp->CrypInCount );
        hcryp->CrypInCount++;
      }    
      while(loopcounter < 4U)
      {
        /* Pad the data with zeros to have a complete block */
        hcryp->Instance->DINR  = 0U;
        loopcounter++; 
      }   
      /* Wait for CCF flag to be raised */
      if(CRYP_WaitOnCCFlag(hcryp, Timeout) != HAL_OK)  
      { 
        /* Disable the CRYP peripheral clock */
        __HAL_CRYP_DISABLE(hcryp);
        
        /* Change state */
        hcryp->ErrorCode |= HAL_CRYP_ERROR_TIMEOUT;
        hcryp->State = HAL_CRYP_STATE_READY;  
        
        /* Process unlocked */          
        __HAL_UNLOCK(hcryp); 
        return HAL_ERROR;         
      } 
      /* Clear CCF flag */
      __HAL_CRYP_CLEAR_FLAG(hcryp, CRYP_CCF_CLEAR);
      
    }
  }       
#endif /* End AES or CRYP */
  
#if defined(CRYP)  
  
  /************************* Header phase *************************************/
  /* Header block(B1) : associated data length expressed in bytes concatenated
  with Associated Data (A)*/
  
  if(CRYP_GCMCCM_SetHeaderPhase(hcryp, Timeout) != HAL_OK)
  {
    return HAL_ERROR;
  }  
  
  /********************** Payload phase ***************************************/   
  
  /* Set the phase */
  hcryp->Phase = CRYP_PHASE_PROCESS;
  
  /* Disable the CRYP peripheral */
  __HAL_CRYP_DISABLE(hcryp);
  
  /* Select payload phase once the header phase is performed */
  CRYP_SET_PHASE(hcryp, CRYP_PHASE_PAYLOAD); 
  
  /* Enable the CRYP peripheral */
  __HAL_CRYP_ENABLE(hcryp);  
  
  if ((hcryp->Size % 16U) != 0U) 
  {
    /* recalculate  wordsize */ 
    wordsize =  ((wordsize/4U)*4U) ; 
  }
  /* Get tick */
  tickstart = HAL_GetTick();
  /*Temporary CrypOutCount Value*/
  outcount = hcryp->CrypOutCount;
  
  /* Write input data and get output data */
  while((hcryp->CrypInCount < wordsize) && (outcount < wordsize))
  {      
    /* Write plain data and get cipher data */
    CRYP_AES_ProcessData(hcryp,Timeout);
    
    /* Check for the Timeout */
    if(Timeout != HAL_MAX_DELAY)
    {
      if(((HAL_GetTick() - tickstart ) > Timeout)||(Timeout == 0U))
      {
        /* Disable the CRYP peripheral clock */
        __HAL_CRYP_DISABLE(hcryp);
        
        /* Change state */
        hcryp->ErrorCode |= HAL_CRYP_ERROR_TIMEOUT;
        hcryp->State = HAL_CRYP_STATE_READY; 
        
        /* Process unlocked */          
        __HAL_UNLOCK(hcryp); 
        return HAL_ERROR;
      }
    }
  }
  
  if ((hcryp->Size % 16U) != 0U)  
  {  
    /* CRYP Workaround :  CRYP1 generates correct TAG  during CCM decryption only when ciphertext blocks size is multiple of
    128 bits. If lthe size of the last block of payload is inferior to 128 bits, when CCM decryption
    is selected, then the TAG message will be wrong.*/   
    CRYP_Workaround(hcryp,Timeout);
  }
#endif /* CRYP */
>>>>>>> 49e424905b5922b07aa7166ec7a0eeb90adf58a8
  
  /* Return function status */
  return HAL_OK;
}

/**
<<<<<<< HEAD
  * @brief  Initializes the CRYP peripheral in TDES ECB encryption mode using interrupt.
  * @param  hcryp pointer to a CRYP_HandleTypeDef structure that contains
  *         the configuration information for CRYP module
  * @param  pPlainData Pointer to the plaintext buffer
  * @param  Size Length of the plaintext buffer, must be a multiple of 8
  * @param  pCypherData Pointer to the cyphertext buffer
  * @retval HAL status
  */
HAL_StatusTypeDef HAL_CRYP_TDESECB_Encrypt_IT(CRYP_HandleTypeDef *hcryp, uint8_t *pPlainData, uint16_t Size, uint8_t *pCypherData)
{
  uint32_t inputaddr;
  uint32_t outputaddr;
  
  if(hcryp->State == HAL_CRYP_STATE_READY)
  {
    /* Process Locked */
    __HAL_LOCK(hcryp);
    
    hcryp->CrypInCount = Size;
    hcryp->pCrypInBuffPtr = pPlainData;
    hcryp->pCrypOutBuffPtr = pCypherData;
    hcryp->CrypOutCount = Size;
    
    /* Change the CRYP state */
    hcryp->State = HAL_CRYP_STATE_BUSY;
    
    /* Set CRYP peripheral in TDES ECB encryption mode */
    CRYP_SetTDESECBMode(hcryp, 0);
    
    /* Enable Interrupts */
    __HAL_CRYP_ENABLE_IT(hcryp, CRYP_IT_INI | CRYP_IT_OUTI);
    
    /* Enable CRYP */
    __HAL_CRYP_ENABLE(hcryp);
    
    /* Return function status */
    return HAL_OK;
  }
  else if(__HAL_CRYP_GET_IT(hcryp, CRYP_IT_INI))
  {
    inputaddr = (uint32_t)hcryp->pCrypInBuffPtr;
    /* Write the Input block in the IN FIFO */
    hcryp->Instance->DR = *(uint32_t*)(inputaddr);
    inputaddr+=4;
    hcryp->Instance->DR = *(uint32_t*)(inputaddr);

    hcryp->pCrypInBuffPtr += 8;
    hcryp->CrypInCount -= 8;
    if(hcryp->CrypInCount == 0)
    {
      __HAL_CRYP_DISABLE_IT(hcryp, CRYP_IT_INI);
      /* Call the Input data transfer complete callback */
      HAL_CRYP_InCpltCallback(hcryp);
    }
  }
  else if(__HAL_CRYP_GET_IT(hcryp, CRYP_IT_OUTI))
  {
    outputaddr = (uint32_t)hcryp->pCrypOutBuffPtr;
    /* Read the Output block from the Output FIFO */
    *(uint32_t*)(outputaddr) = hcryp->Instance->DOUT;
    outputaddr+=4;
    *(uint32_t*)(outputaddr) = hcryp->Instance->DOUT;

    hcryp->pCrypOutBuffPtr += 8;
    hcryp->CrypOutCount -= 8;
    if(hcryp->CrypOutCount == 0)
    {
      /* Disable IT */
      __HAL_CRYP_DISABLE_IT(hcryp, CRYP_IT_OUTI);
      /* Disable CRYP */
      __HAL_CRYP_DISABLE(hcryp);
      /* Process Unlocked */
      __HAL_UNLOCK(hcryp);
      /* Change the CRYP state */
      hcryp->State = HAL_CRYP_STATE_READY;
      /* Call the Output data transfer complete callback */
      HAL_CRYP_OutCpltCallback(hcryp);
    }
  }
  
  /* Return function status */
  return HAL_OK;
}

/**
  * @brief  Initializes the CRYP peripheral in TDES CBC encryption mode.
  * @param  hcryp pointer to a CRYP_HandleTypeDef structure that contains
  *         the configuration information for CRYP module
  * @param  pPlainData Pointer to the plaintext buffer
  * @param  Size Length of the plaintext buffer, must be a multiple of 8
  * @param  pCypherData Pointer to the cyphertext buffer
  * @retval HAL status
  */
HAL_StatusTypeDef HAL_CRYP_TDESCBC_Encrypt_IT(CRYP_HandleTypeDef *hcryp, uint8_t *pPlainData, uint16_t Size, uint8_t *pCypherData)
{
  uint32_t inputaddr;
  uint32_t outputaddr;
  
  if(hcryp->State == HAL_CRYP_STATE_READY)
  {
    /* Process Locked */
    __HAL_LOCK(hcryp);
    
    hcryp->CrypInCount = Size;
    hcryp->pCrypInBuffPtr = pPlainData;
    hcryp->pCrypOutBuffPtr = pCypherData;
    hcryp->CrypOutCount = Size;
    
    /* Change the CRYP state */
    hcryp->State = HAL_CRYP_STATE_BUSY;
    
    /* Set CRYP peripheral in TDES CBC encryption mode */
    CRYP_SetTDESCBCMode(hcryp, 0);
    
    /* Enable Interrupts */
    __HAL_CRYP_ENABLE_IT(hcryp, CRYP_IT_INI | CRYP_IT_OUTI);
    
    /* Enable CRYP */
    __HAL_CRYP_ENABLE(hcryp);
    
    /* Return function status */
    return HAL_OK;
  }
  else if(__HAL_CRYP_GET_IT(hcryp, CRYP_IT_INI))
  {
    inputaddr = (uint32_t)hcryp->pCrypInBuffPtr;
    /* Write the Input block in the IN FIFO */
    hcryp->Instance->DR = *(uint32_t*)(inputaddr);
    inputaddr+=4;
    hcryp->Instance->DR = *(uint32_t*)(inputaddr);

    hcryp->pCrypInBuffPtr += 8;
    hcryp->CrypInCount -= 8;
    if(hcryp->CrypInCount == 0)
    {
      __HAL_CRYP_DISABLE_IT(hcryp, CRYP_IT_INI);
      /* Call the Input data transfer complete callback */
      HAL_CRYP_InCpltCallback(hcryp);
    }
  }
  else if(__HAL_CRYP_GET_IT(hcryp, CRYP_IT_OUTI))
  {
    outputaddr = (uint32_t)hcryp->pCrypOutBuffPtr;
    /* Read the Output block from the Output FIFO */
    *(uint32_t*)(outputaddr) = hcryp->Instance->DOUT;
    outputaddr+=4;
    *(uint32_t*)(outputaddr) = hcryp->Instance->DOUT;
        
    hcryp->pCrypOutBuffPtr += 8;
    hcryp->CrypOutCount -= 8;
    if(hcryp->CrypOutCount == 0)
    {
      __HAL_CRYP_DISABLE_IT(hcryp, CRYP_IT_OUTI);
      /* Disable CRYP */
      __HAL_CRYP_DISABLE(hcryp);
      /* Process Unlocked */
      __HAL_UNLOCK(hcryp);
      /* Change the CRYP state */
      hcryp->State = HAL_CRYP_STATE_READY;
      /* Call Input transfer complete callback */
      HAL_CRYP_OutCpltCallback(hcryp);
    }
  }
  
  /* Return function status */
  return HAL_OK;
}

/**
  * @brief  Initializes the CRYP peripheral in TDES ECB decryption mode.
  * @param  hcryp pointer to a CRYP_HandleTypeDef structure that contains
  *         the configuration information for CRYP module
  * @param  pPlainData Pointer to the plaintext buffer
  * @param  Size Length of the plaintext buffer, must be a multiple of 8
  * @param  pCypherData Pointer to the cyphertext buffer
  * @retval HAL status
  */
HAL_StatusTypeDef HAL_CRYP_TDESECB_Decrypt_IT(CRYP_HandleTypeDef *hcryp, uint8_t *pCypherData, uint16_t Size, uint8_t *pPlainData)
{
  uint32_t inputaddr;
  uint32_t outputaddr;
  
  if(hcryp->State == HAL_CRYP_STATE_READY)
  {
    /* Process Locked */
    __HAL_LOCK(hcryp);
    
    hcryp->CrypInCount = Size;
    hcryp->pCrypInBuffPtr = pCypherData;
    hcryp->pCrypOutBuffPtr = pPlainData;
    hcryp->CrypOutCount = Size;
    
    /* Change the CRYP state */
    hcryp->State = HAL_CRYP_STATE_BUSY;
    
    /* Set CRYP peripheral in TDES ECB decryption mode */
    CRYP_SetTDESECBMode(hcryp, CRYP_CR_ALGODIR);
    
    /* Enable Interrupts */
    __HAL_CRYP_ENABLE_IT(hcryp, CRYP_IT_INI | CRYP_IT_OUTI);
    
    /* Enable CRYP */
    __HAL_CRYP_ENABLE(hcryp);
    
    /* Return function status */
    return HAL_OK;
  }
  else if(__HAL_CRYP_GET_IT(hcryp, CRYP_IT_INI))
  {
    inputaddr = (uint32_t)hcryp->pCrypInBuffPtr;
    /* Write the Input block in the IN FIFO */
    hcryp->Instance->DR = *(uint32_t*)(inputaddr);
    inputaddr+=4;
    hcryp->Instance->DR = *(uint32_t*)(inputaddr);

    hcryp->pCrypInBuffPtr += 8;
    hcryp->CrypInCount -= 8;
    if(hcryp->CrypInCount == 0)
    {
      __HAL_CRYP_DISABLE_IT(hcryp, CRYP_IT_INI);
      /* Call the Input data transfer complete callback */
      HAL_CRYP_InCpltCallback(hcryp);
    }
  }
  else if(__HAL_CRYP_GET_IT(hcryp, CRYP_IT_OUTI))
  {
    outputaddr = (uint32_t)hcryp->pCrypOutBuffPtr;
    /* Read the Output block from the Output FIFO */
    *(uint32_t*)(outputaddr) = hcryp->Instance->DOUT;
    outputaddr+=4;
    *(uint32_t*)(outputaddr) = hcryp->Instance->DOUT;

    hcryp->pCrypOutBuffPtr += 8;
    hcryp->CrypOutCount -= 8;
    if(hcryp->CrypOutCount == 0)
    {
      __HAL_CRYP_DISABLE_IT(hcryp, CRYP_IT_OUTI);
      /* Disable CRYP */
      __HAL_CRYP_DISABLE(hcryp);
      /* Process Unlocked */
      __HAL_UNLOCK(hcryp);
      /* Change the CRYP state */
      hcryp->State = HAL_CRYP_STATE_READY;
      /* Call Input transfer complete callback */
      HAL_CRYP_OutCpltCallback(hcryp);
    }
  }
  
  /* Return function status */
  return HAL_OK;
} 

/**
  * @brief  Initializes the CRYP peripheral in TDES CBC decryption mode.
  * @param  hcryp pointer to a CRYP_HandleTypeDef structure that contains
  *         the configuration information for CRYP module
  * @param  pCypherData Pointer to the cyphertext buffer
  * @param  Size Length of the plaintext buffer, must be a multiple of 8
  * @param  pPlainData Pointer to the plaintext buffer
  * @retval HAL status
  */
HAL_StatusTypeDef HAL_CRYP_TDESCBC_Decrypt_IT(CRYP_HandleTypeDef *hcryp, uint8_t *pCypherData, uint16_t Size, uint8_t *pPlainData)
{
  uint32_t inputaddr;
  uint32_t outputaddr;
  
  if(hcryp->State == HAL_CRYP_STATE_READY)
  {
    /* Process Locked */
    __HAL_LOCK(hcryp);
    
    hcryp->CrypInCount = Size;
    hcryp->pCrypInBuffPtr = pCypherData;
    hcryp->pCrypOutBuffPtr = pPlainData;
    hcryp->CrypOutCount = Size;
    
    /* Change the CRYP state */
    hcryp->State = HAL_CRYP_STATE_BUSY;
    
    /* Set CRYP peripheral in TDES CBC decryption mode */
    CRYP_SetTDESCBCMode(hcryp, CRYP_CR_ALGODIR);
    
    /* Enable Interrupts */
    __HAL_CRYP_ENABLE_IT(hcryp, CRYP_IT_INI | CRYP_IT_OUTI);
    
    /* Enable CRYP */
    __HAL_CRYP_ENABLE(hcryp);
    
    /* Return function status */
    return HAL_OK;
  }
  else if(__HAL_CRYP_GET_IT(hcryp, CRYP_IT_INI))
  {
    inputaddr = (uint32_t)hcryp->pCrypInBuffPtr;
    /* Write the Input block in the IN FIFO */
    hcryp->Instance->DR = *(uint32_t*)(inputaddr);
    inputaddr+=4;
    hcryp->Instance->DR = *(uint32_t*)(inputaddr);

    hcryp->pCrypInBuffPtr += 8;
    hcryp->CrypInCount -= 8;
    if(hcryp->CrypInCount == 0)
    {
      __HAL_CRYP_DISABLE_IT(hcryp, CRYP_IT_INI);
      /* Call the Input data transfer complete callback */
      HAL_CRYP_InCpltCallback(hcryp);
    }
  }
  else if(__HAL_CRYP_GET_IT(hcryp, CRYP_IT_OUTI))
  {
    outputaddr = (uint32_t)hcryp->pCrypOutBuffPtr;
    /* Read the Output block from the Output FIFO */
    *(uint32_t*)(outputaddr) = hcryp->Instance->DOUT;
    outputaddr+=4;
    *(uint32_t*)(outputaddr) = hcryp->Instance->DOUT;

    hcryp->pCrypOutBuffPtr += 8;
    hcryp->CrypOutCount -= 8;
    if(hcryp->CrypOutCount == 0)
    {
      __HAL_CRYP_DISABLE_IT(hcryp, CRYP_IT_OUTI);
      /* Disable CRYP */
      __HAL_CRYP_DISABLE(hcryp);
      /* Process Unlocked */
      __HAL_UNLOCK(hcryp);
      /* Change the CRYP state */
      hcryp->State = HAL_CRYP_STATE_READY;
      /* Call Input transfer complete callback */
      HAL_CRYP_OutCpltCallback(hcryp);
    }
  }
  
  /* Return function status */
  return HAL_OK;
}

/**
  * @brief  Initializes the CRYP peripheral in TDES ECB encryption mode using DMA.
  * @param  hcryp pointer to a CRYP_HandleTypeDef structure that contains
  *         the configuration information for CRYP module
  * @param  pPlainData Pointer to the plaintext buffer
  * @param  Size Length of the plaintext buffer, must be a multiple of 8
  * @param  pCypherData Pointer to the cyphertext buffer
  * @retval HAL status
  */
HAL_StatusTypeDef HAL_CRYP_TDESECB_Encrypt_DMA(CRYP_HandleTypeDef *hcryp, uint8_t *pPlainData, uint16_t Size, uint8_t *pCypherData)
{
  uint32_t inputaddr;
  uint32_t outputaddr;
  
  if((hcryp->State == HAL_CRYP_STATE_READY) || (hcryp->Phase == HAL_CRYP_PHASE_PROCESS))
  {
    /* Process Locked */
    __HAL_LOCK(hcryp);
    
    inputaddr  = (uint32_t)pPlainData;
    outputaddr = (uint32_t)pCypherData;
    
    /* Change the CRYP state */
    hcryp->State = HAL_CRYP_STATE_BUSY;
    
    /* Set CRYP peripheral in TDES ECB encryption mode */
    CRYP_SetTDESECBMode(hcryp, 0);
    
    /* Set the input and output addresses and start DMA transfer */ 
    CRYP_SetDMAConfig(hcryp, inputaddr, Size, outputaddr);
    
    /* Process Unlocked */
    __HAL_UNLOCK(hcryp);
    
    /* Return function status */
    return HAL_OK;
  }
  else
  {
    return HAL_ERROR;   
  }
}

/**
  * @brief  Initializes the CRYP peripheral in TDES CBC encryption mode using DMA.
  * @param  hcryp pointer to a CRYP_HandleTypeDef structure that contains
  *         the configuration information for CRYP module
  * @param  pPlainData Pointer to the plaintext buffer
  * @param  Size Length of the plaintext buffer, must be a multiple of 8
  * @param  pCypherData Pointer to the cyphertext buffer
  * @retval HAL status
  */
HAL_StatusTypeDef HAL_CRYP_TDESCBC_Encrypt_DMA(CRYP_HandleTypeDef *hcryp, uint8_t *pPlainData, uint16_t Size, uint8_t *pCypherData)
{
  uint32_t inputaddr;
  uint32_t outputaddr;
  
  if((hcryp->State == HAL_CRYP_STATE_READY) || (hcryp->Phase == HAL_CRYP_PHASE_PROCESS))
  {
    /* Process Locked */
    __HAL_LOCK(hcryp);
    
    inputaddr  = (uint32_t)pPlainData;
    outputaddr = (uint32_t)pCypherData;
    
    /* Change the CRYP state */
    hcryp->State = HAL_CRYP_STATE_BUSY;
    
    /* Set CRYP peripheral in TDES CBC encryption mode */
    CRYP_SetTDESCBCMode(hcryp, 0);
    
    /* Set the input and output addresses and start DMA transfer */ 
    CRYP_SetDMAConfig(hcryp, inputaddr, Size, outputaddr);
    
    /* Process Unlocked */
    __HAL_UNLOCK(hcryp);
    
    /* Return function status */
    return HAL_OK;
  }
  else
  {
    return HAL_ERROR;   
  }
}

/**
  * @brief  Initializes the CRYP peripheral in TDES ECB decryption mode using DMA.
  * @param  hcryp pointer to a CRYP_HandleTypeDef structure that contains
  *         the configuration information for CRYP module
  * @param  pPlainData Pointer to the plaintext buffer
  * @param  Size Length of the plaintext buffer, must be a multiple of 8
  * @param  pCypherData Pointer to the cyphertext buffer
  * @retval HAL status
  */
HAL_StatusTypeDef HAL_CRYP_TDESECB_Decrypt_DMA(CRYP_HandleTypeDef *hcryp, uint8_t *pCypherData, uint16_t Size, uint8_t *pPlainData)
{
  uint32_t inputaddr;
  uint32_t outputaddr;
  
  if((hcryp->State == HAL_CRYP_STATE_READY) || (hcryp->Phase == HAL_CRYP_PHASE_PROCESS))
  {
    /* Process Locked */
    __HAL_LOCK(hcryp);
    
    inputaddr  = (uint32_t)pCypherData;
    outputaddr = (uint32_t)pPlainData;
    
    /* Change the CRYP state */
    hcryp->State = HAL_CRYP_STATE_BUSY;
    
    /* Set CRYP peripheral in TDES ECB decryption mode */
    CRYP_SetTDESECBMode(hcryp, CRYP_CR_ALGODIR);
    
    /* Set the input and output addresses and start DMA transfer */ 
    CRYP_SetDMAConfig(hcryp, inputaddr, Size, outputaddr);
    
    /* Process Unlocked */
    __HAL_UNLOCK(hcryp);
    
    /* Return function status */
    return HAL_OK;
  }
  else
  {
    return HAL_ERROR;   
  }
}

/**
  * @brief  Initializes the CRYP peripheral in TDES CBC decryption mode using DMA.
  * @param  hcryp pointer to a CRYP_HandleTypeDef structure that contains
  *         the configuration information for CRYP module
  * @param  pCypherData Pointer to the cyphertext buffer
  * @param  Size Length of the plaintext buffer, must be a multiple of 8
  * @param  pPlainData Pointer to the plaintext buffer
  * @retval HAL status
  */
HAL_StatusTypeDef HAL_CRYP_TDESCBC_Decrypt_DMA(CRYP_HandleTypeDef *hcryp, uint8_t *pCypherData, uint16_t Size, uint8_t *pPlainData)
{
  uint32_t inputaddr;
  uint32_t outputaddr;
  
  if((hcryp->State == HAL_CRYP_STATE_READY) || (hcryp->Phase == HAL_CRYP_PHASE_PROCESS))
  {
    /* Process Locked */
    __HAL_LOCK(hcryp);
    
    inputaddr  = (uint32_t)pCypherData;
    outputaddr = (uint32_t)pPlainData;
    
    /* Change the CRYP state */
    hcryp->State = HAL_CRYP_STATE_BUSY;
    
    /* Set CRYP peripheral in TDES CBC decryption mode */
    CRYP_SetTDESCBCMode(hcryp, CRYP_CR_ALGODIR);
    
    /* Set the input and output addresses and start DMA transfer */ 
    CRYP_SetDMAConfig(hcryp, inputaddr, Size, outputaddr);
    
    /* Process Unlocked */
    __HAL_UNLOCK(hcryp);
    
    /* Return function status */
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

/** @defgroup CRYP_Exported_Functions_Group5 DMA callback functions 
 *  @brief   DMA callback functions. 
 *
@verbatim   
  ==============================================================================
                      ##### DMA callback functions  #####
  ==============================================================================  
    [..]  This section provides DMA callback functions:
      (+) DMA Input data transfer complete
      (+) DMA Output data transfer complete
      (+) DMA error

@endverbatim
  * @{
  */

/**
  * @brief  Input FIFO transfer completed callbacks.
  * @param  hcryp pointer to a CRYP_HandleTypeDef structure that contains
  *         the configuration information for CRYP module
  * @retval None
  */
__weak void HAL_CRYP_InCpltCallback(CRYP_HandleTypeDef *hcryp)
{
  /* Prevent unused argument(s) compilation warning */
  UNUSED(hcryp);
 
  /* NOTE : This function Should not be modified, when the callback is needed,
            the HAL_CRYP_InCpltCallback could be implemented in the user file
   */ 
}

/**
  * @brief  Output FIFO transfer completed callbacks.
  * @param  hcryp pointer to a CRYP_HandleTypeDef structure that contains
  *         the configuration information for CRYP module
  * @retval None
  */
__weak void HAL_CRYP_OutCpltCallback(CRYP_HandleTypeDef *hcryp)
{
  /* Prevent unused argument(s) compilation warning */
  UNUSED(hcryp);
 
  /* NOTE : This function Should not be modified, when the callback is needed,
            the HAL_CRYP_OutCpltCallback could be implemented in the user file
   */
}

/**
  * @brief  CRYP error callbacks.
  * @param  hcryp pointer to a CRYP_HandleTypeDef structure that contains
  *         the configuration information for CRYP module
  * @retval None
  */
 __weak void HAL_CRYP_ErrorCallback(CRYP_HandleTypeDef *hcryp)
{
  /* Prevent unused argument(s) compilation warning */
  UNUSED(hcryp);
 
  /* NOTE : This function Should not be modified, when the callback is needed,
            the HAL_CRYP_ErrorCallback could be implemented in the user file
   */ 
}

/**
  * @}
  */

/** @defgroup CRYP_Exported_Functions_Group6 CRYP IRQ handler management  
 *  @brief   CRYP IRQ handler.
 *
@verbatim   
  ==============================================================================
                ##### CRYP IRQ handler management #####
  ==============================================================================  
[..]  This section provides CRYP IRQ handler function.

@endverbatim
  * @{
  */

/**
  * @brief  This function handles CRYP interrupt request.
  * @param  hcryp pointer to a CRYP_HandleTypeDef structure that contains
  *         the configuration information for CRYP module
  * @retval None
  */
void HAL_CRYP_IRQHandler(CRYP_HandleTypeDef *hcryp)
{
  switch(CRYP->CR & CRYP_CR_ALGOMODE_DIRECTION)
  {
  case CRYP_CR_ALGOMODE_TDES_ECB_ENCRYPT:
    HAL_CRYP_TDESECB_Encrypt_IT(hcryp, NULL, 0, NULL);
    break;
    
  case CRYP_CR_ALGOMODE_TDES_ECB_DECRYPT:
    HAL_CRYP_TDESECB_Decrypt_IT(hcryp, NULL, 0, NULL);
    break;
    
  case CRYP_CR_ALGOMODE_TDES_CBC_ENCRYPT:
    HAL_CRYP_TDESCBC_Encrypt_IT(hcryp, NULL, 0, NULL);
    break;
    
  case CRYP_CR_ALGOMODE_TDES_CBC_DECRYPT:
    HAL_CRYP_TDESCBC_Decrypt_IT(hcryp, NULL, 0, NULL);
    break;
    
  case CRYP_CR_ALGOMODE_DES_ECB_ENCRYPT:
    HAL_CRYP_DESECB_Encrypt_IT(hcryp, NULL, 0, NULL);
    break;
    
  case CRYP_CR_ALGOMODE_DES_ECB_DECRYPT:
    HAL_CRYP_DESECB_Decrypt_IT(hcryp, NULL, 0, NULL);
    break;
    
  case CRYP_CR_ALGOMODE_DES_CBC_ENCRYPT:
    HAL_CRYP_DESCBC_Encrypt_IT(hcryp, NULL, 0, NULL);
    break;
    
  case CRYP_CR_ALGOMODE_DES_CBC_DECRYPT:
    HAL_CRYP_DESCBC_Decrypt_IT(hcryp, NULL, 0, NULL);
    break;
    
  case CRYP_CR_ALGOMODE_AES_ECB_ENCRYPT:
    HAL_CRYP_AESECB_Encrypt_IT(hcryp, NULL, 0, NULL);
    break;
    
  case CRYP_CR_ALGOMODE_AES_ECB_DECRYPT:
    HAL_CRYP_AESECB_Decrypt_IT(hcryp, NULL, 0, NULL);
    break;
    
  case CRYP_CR_ALGOMODE_AES_CBC_ENCRYPT:
    HAL_CRYP_AESCBC_Encrypt_IT(hcryp, NULL, 0, NULL);
    break;
    
  case CRYP_CR_ALGOMODE_AES_CBC_DECRYPT:
    HAL_CRYP_AESCBC_Decrypt_IT(hcryp, NULL, 0, NULL);
    break;
    
  case CRYP_CR_ALGOMODE_AES_CTR_ENCRYPT:
    HAL_CRYP_AESCTR_Encrypt_IT(hcryp, NULL, 0, NULL);       
    break;
    
  case CRYP_CR_ALGOMODE_AES_CTR_DECRYPT:
    HAL_CRYP_AESCTR_Decrypt_IT(hcryp, NULL, 0, NULL);        
    break;
    
  default:
    break;
  }
}

/**
  * @}
  */

/** @defgroup CRYP_Exported_Functions_Group7 Peripheral State functions 
 *  @brief   Peripheral State functions. 
 *
@verbatim   
  ==============================================================================
                      ##### Peripheral State functions #####
  ==============================================================================  
    [..]
    This subsection permits to get in run-time the status of the peripheral.

@endverbatim
  * @{
  */

/**
  * @brief  Returns the CRYP state.
  * @param  hcryp pointer to a CRYP_HandleTypeDef structure that contains
  *         the configuration information for CRYP module
  * @retval HAL state
  */
HAL_CRYP_STATETypeDef HAL_CRYP_GetState(CRYP_HandleTypeDef *hcryp)
{
  return hcryp->State;
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
/**
  * @}
  */
#endif /* CRYP */
  
#if defined (AES)


/** @addtogroup STM32F7xx_HAL_Driver
  * @{
  */

/** @defgroup AES AES
  * @brief AES HAL module driver.
  * @{
  */



/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private functions --------------------------------------------------------*/

/** @defgroup CRYP_Private_Functions CRYP Private Functions
  * @{
  */

static HAL_StatusTypeDef CRYP_SetInitVector(CRYP_HandleTypeDef *hcryp);
static HAL_StatusTypeDef CRYP_SetKey(CRYP_HandleTypeDef *hcryp);
static HAL_StatusTypeDef CRYP_AES_IT(CRYP_HandleTypeDef *hcryp);

/**
  * @}
  */

/* Exported functions ---------------------------------------------------------*/

/** @defgroup CRYP_Exported_Functions CRYP Exported Functions
  * @{
  */

/** @defgroup CRYP_Exported_Functions_Group1 Initialization and deinitialization functions 
 *  @brief    Initialization and Configuration functions. 
 *
@verbatim    
  ==============================================================================
              ##### Initialization and deinitialization functions #####
  ==============================================================================
    [..]  This section provides functions allowing to:
      (+) Initialize the CRYP according to the specified parameters 
          in the CRYP_InitTypeDef and creates the associated handle
      (+) DeInitialize the CRYP peripheral
      (+) Initialize the CRYP MSP (MCU Specific Package)
      (+) De-Initialize the CRYP MSP
      
    [..]
    (@) Specific care must be taken to format the key and the Initialization Vector IV!
    
   [..] If the key is defined as a 128-bit long array key[127..0] = {b127 ... b0} where 
        b127 is the MSB and b0 the LSB, the key must be stored in MCU memory 
        (+) as a sequence of words where the MSB word comes first (occupies the
          lowest memory address) 
        (+) where each word is byte-swapped:
         (++)   address n+0 : 0b b103 .. b96 b111 .. b104 b119 .. b112 b127 .. b120
         (++)   address n+4 : 0b b71 .. b64 b79 .. b72 b87 .. b80 b95 .. b88
         (++)   address n+8 : 0b b39 .. b32 b47 .. b40 b55 .. b48 b63 .. b56
         (++)   address n+C : 0b b7 .. b0 b15 .. b8 b23 .. b16 b31 .. b24                 
    [..] Hereafter, another illustration when considering a 128-bit long key made of 16 bytes {B15..B0}.
        The 4 32-bit words that make the key must be stored as follows in MCU memory:  
         (+)    address n+0 : 0x B12 B13 B14 B15
         (+)    address n+4 : 0x B8 B9 B10 B11
         (+)    address n+8 : 0x B4 B5 B6 B7
         (+)    address n+C : 0x B0 B1 B2 B3  
    [..]  which leads to the expected setting  
      (+)       AES_KEYR3 = 0x B15 B14 B13 B12   
      (+)       AES_KEYR2 = 0x B11 B10 B9 B8      
      (+)       AES_KEYR1 = 0x B7 B6 B5 B4        
      (+)       AES_KEYR0 = 0x B3 B2 B1 B0      
   
   [..]  Same format must be applied for a 256-bit long key made of 32 bytes {B31..B0}. 
         The 8 32-bit words that make the key must be stored as follows in MCU memory:
         (+)    address n+00 : 0x B28 B29 B30 B31
         (+)    address n+04 : 0x B24 B25 B26 B27
         (+)    address n+08 : 0x B20 B21 B22 B23
         (+)    address n+0C : 0x B16 B17 B18 B19            
         (+)    address n+10 : 0x B12 B13 B14 B15
         (+)    address n+14 : 0x B8 B9 B10 B11
         (+)    address n+18 : 0x B4 B5 B6 B7
         (+)    address n+1C : 0x B0 B1 B2 B3 
    [..]  which leads to the expected setting 
      (+)       AES_KEYR7 = 0x B31 B30 B29 B28   
      (+)       AES_KEYR6 = 0x B27 B26 B25 B24      
      (+)       AES_KEYR5 = 0x B23 B22 B21 B20        
      (+)       AES_KEYR4 = 0x B19 B18 B17 B16       
      (+)       AES_KEYR3 = 0x B15 B14 B13 B12   
      (+)       AES_KEYR2 = 0x B11 B10 B9 B8      
      (+)       AES_KEYR1 = 0x B7 B6 B5 B4        
      (+)       AES_KEYR0 = 0x B3 B2 B1 B0           
   
   [..] Initialization Vector IV (4 32-bit words) format must follow the same as 
        that of a 128-bit long key.   
  
  [..]                 
 
@endverbatim
  * @{
  */

/**
  * @brief  Initialize the CRYP according to the specified
  *         parameters in the CRYP_InitTypeDef and initialize the associated handle.                   
  * @note Specific care must be taken to format the key and the Initialization Vector IV 
  *       stored in the MCU memory before calling HAL_CRYP_Init(). Refer to explanations 
  *       hereabove.              
  * @retval HAL status
  */
HAL_StatusTypeDef HAL_CRYP_Init(CRYP_HandleTypeDef *hcryp)
{   
  /* Check the CRYP handle allocation */
  if(hcryp == NULL)
  {
    return HAL_ERROR;
  }
  
  /* Check the instance */
  assert_param(IS_AES_ALL_INSTANCE(hcryp->Instance));
  
  /* Check the parameters */
  assert_param(IS_CRYP_KEYSIZE(hcryp->Init.KeySize));
  assert_param(IS_CRYP_DATATYPE(hcryp->Init.DataType));
  assert_param(IS_CRYP_ALGOMODE(hcryp->Init.OperatingMode));
  /* ChainingMode parameter is irrelevant when mode is set to Key derivation */
  if (hcryp->Init.OperatingMode != CRYP_ALGOMODE_KEYDERIVATION)
  {
    assert_param(IS_CRYP_CHAINMODE(hcryp->Init.ChainingMode));
  }
  assert_param(IS_CRYP_WRITE(hcryp->Init.KeyWriteFlag));
  
  /*========================================================*/
  /* Check the proper operating/chaining modes combinations */
  /*========================================================*/  
  /* Check the proper chaining when the operating mode is key derivation and decryption */
#if defined(AES_CR_NPBLB)
  if ((hcryp->Init.OperatingMode == CRYP_ALGOMODE_KEYDERIVATION_DECRYPT) &&\
         ((hcryp->Init.ChainingMode == CRYP_CHAINMODE_AES_CTR)           \
       || (hcryp->Init.ChainingMode == CRYP_CHAINMODE_AES_GCM_GMAC)      \
       || (hcryp->Init.ChainingMode == CRYP_CHAINMODE_AES_CCM_CMAC)))
#else  
  if ((hcryp->Init.OperatingMode == CRYP_ALGOMODE_KEYDERIVATION_DECRYPT) &&\
         ((hcryp->Init.ChainingMode == CRYP_CHAINMODE_AES_CTR)           \
       || (hcryp->Init.ChainingMode == CRYP_CHAINMODE_AES_GCM_GMAC)      \
       || (hcryp->Init.ChainingMode == CRYP_CHAINMODE_AES_CMAC)))
#endif               
  {
    return HAL_ERROR;
  }  
  /* Check that key derivation is not set in CMAC mode or CCM mode when applicable */  
#if defined(AES_CR_NPBLB)
  if ((hcryp->Init.OperatingMode == CRYP_ALGOMODE_KEYDERIVATION) 
   && (hcryp->Init.ChainingMode == CRYP_CHAINMODE_AES_CCM_CMAC))
#else  
  if ((hcryp->Init.OperatingMode == CRYP_ALGOMODE_KEYDERIVATION) 
   && (hcryp->Init.ChainingMode == CRYP_CHAINMODE_AES_CMAC))
#endif           
  {
    return HAL_ERROR;
  }
  
  
  /*================*/
  /* Initialization */
  /*================*/  
  /* Initialization start */
  if(hcryp->State == HAL_CRYP_STATE_RESET)
  {
    /* Allocate lock resource and initialize it */
    hcryp->Lock = HAL_UNLOCKED;

    /* Init the low level hardware */
    HAL_CRYP_MspInit(hcryp);
  }
  
  /* Change the CRYP state */
  hcryp->State = HAL_CRYP_STATE_BUSY;  
  
  /* Disable the Peripheral */
  __HAL_CRYP_DISABLE();
  
  /*=============================================================*/
  /* AES initialization common to all operating modes            */ 
  /*=============================================================*/
  /* Set the Key size selection */
  MODIFY_REG(hcryp->Instance->CR, AES_CR_KEYSIZE, hcryp->Init.KeySize);
  
  /* Set the default CRYP phase when this parameter is not used.
     Phase is updated below in case of GCM/GMAC/CMAC(/CCM) setting. */
  hcryp->Phase = HAL_CRYP_PHASE_NOT_USED;
  
  

  /*=============================================================*/
  /* Carry on the initialization based on the AES operating mode */ 
  /*=============================================================*/
  /* Key derivation */ 
  if (hcryp->Init.OperatingMode == CRYP_ALGOMODE_KEYDERIVATION)
  {
    MODIFY_REG(hcryp->Instance->CR, AES_CR_MODE, CRYP_ALGOMODE_KEYDERIVATION);
    
    /* Configure the Key registers */
    if (CRYP_SetKey(hcryp) != HAL_OK)
    {
      return HAL_ERROR;
    }
  }
  else
  /* Encryption / Decryption (with or without key derivation) / authentication */
  {    
    /* Set data type, operating and chaining modes.
       In case of GCM or GMAC, data type is forced to 0b00 */
    if (hcryp->Init.ChainingMode == CRYP_CHAINMODE_AES_GCM_GMAC)
    {
      MODIFY_REG(hcryp->Instance->CR, AES_CR_DATATYPE|AES_CR_MODE|AES_CR_CHMOD, hcryp->Init.OperatingMode|hcryp->Init.ChainingMode);
    }
    else
    {
      MODIFY_REG(hcryp->Instance->CR, AES_CR_DATATYPE|AES_CR_MODE|AES_CR_CHMOD, hcryp->Init.DataType|hcryp->Init.OperatingMode|hcryp->Init.ChainingMode);
    }

    
   /* Specify the encryption/decryption phase in case of Galois counter mode (GCM), 
      Galois message authentication code (GMAC), cipher message authentication code (CMAC) 
      or Counter with Cipher Mode (CCM) when applicable */
#if defined(AES_CR_NPBLB)      
   if ((hcryp->Init.ChainingMode == CRYP_CHAINMODE_AES_GCM_GMAC)
    || (hcryp->Init.ChainingMode == CRYP_CHAINMODE_AES_CCM_CMAC))
#else
   if ((hcryp->Init.ChainingMode == CRYP_CHAINMODE_AES_GCM_GMAC)
    || (hcryp->Init.ChainingMode == CRYP_CHAINMODE_AES_CMAC))
#endif    
    {
      MODIFY_REG(hcryp->Instance->CR, AES_CR_GCMPH, hcryp->Init.GCMCMACPhase);
      hcryp->Phase = HAL_CRYP_PHASE_START;
    }

    
    /* Configure the Key registers if no need to bypass this step */
    if (hcryp->Init.KeyWriteFlag == CRYP_KEY_WRITE_ENABLE)
    {
      if (CRYP_SetKey(hcryp) != HAL_OK)
      {
        return HAL_ERROR;
      }      
    }
    
    /* If applicable, configure the Initialization Vector */
    if (hcryp->Init.ChainingMode != CRYP_CHAINMODE_AES_ECB)
    {
      if (CRYP_SetInitVector(hcryp) != HAL_OK)
      {
        return HAL_ERROR;
      }
    }
  }
  
#if defined(AES_CR_NPBLB)   
  /* Clear NPBLB field */
  CLEAR_BIT(hcryp->Instance->CR, AES_CR_NPBLB);
#endif  

  /* Reset CrypInCount and CrypOutCount */
  hcryp->CrypInCount = 0;
  hcryp->CrypOutCount = 0;
  
  /* Reset ErrorCode field */
  hcryp->ErrorCode = HAL_CRYP_ERROR_NONE;
  
  /* Reset Mode suspension request */
  hcryp->SuspendRequest = HAL_CRYP_SUSPEND_NONE;
  
  /* Change the CRYP state */
  hcryp->State = HAL_CRYP_STATE_READY;
  
  /* Enable the Peripheral */
  __HAL_CRYP_ENABLE();
  
  /* Return function status */
  return HAL_OK;
}

/**
  * @brief  DeInitialize the CRYP peripheral. 
  * @param  hcryp pointer to a CRYP_HandleTypeDef structure that contains
  *         the configuration information for CRYP module
  * @retval HAL status
  */
HAL_StatusTypeDef HAL_CRYP_DeInit(CRYP_HandleTypeDef *hcryp)
{
  /* Check the CRYP handle allocation */
  if(hcryp == NULL)
  {
    return HAL_ERROR;
  }
  
  /* Change the CRYP state */
  hcryp->State = HAL_CRYP_STATE_BUSY;
  
  /* Set the default CRYP phase */
  hcryp->Phase = HAL_CRYP_PHASE_READY;
  
  /* Reset CrypInCount and CrypOutCount */
  hcryp->CrypInCount = 0;
  hcryp->CrypOutCount = 0;
  
  /* Disable the CRYP Peripheral Clock */
  __HAL_CRYP_DISABLE();
  
  /* DeInit the low level hardware: CLOCK, NVIC.*/
  HAL_CRYP_MspDeInit(hcryp);
  
  /* Change the CRYP state */
  hcryp->State = HAL_CRYP_STATE_RESET;
  
  /* Release Lock */
  __HAL_UNLOCK(hcryp);
  
  /* Return function status */
  return HAL_OK;
}

/**
  * @brief  Initialize the CRYP MSP.
  * @param  hcryp pointer to a CRYP_HandleTypeDef structure that contains
  *         the configuration information for CRYP module
  * @retval None
  */
__weak void HAL_CRYP_MspInit(CRYP_HandleTypeDef *hcryp)
{
  /* Prevent unused argument(s) compilation warning */
  UNUSED(hcryp);

  /* NOTE : This function should not be modified; when the callback is needed,
            the HAL_CRYP_MspInit can be implemented in the user file
   */
}

/**
  * @brief  DeInitialize CRYP MSP.
  * @param  hcryp pointer to a CRYP_HandleTypeDef structure that contains
  *         the configuration information for CRYP module
  * @retval None
  */
__weak void HAL_CRYP_MspDeInit(CRYP_HandleTypeDef *hcryp)
{
  /* Prevent unused argument(s) compilation warning */
  UNUSED(hcryp);

  /* NOTE : This function should not be modified; when the callback is needed,
            the HAL_CRYP_MspDeInit can be implemented in the user file
   */
}

/**
  * @}
  */

/** @defgroup CRYP_Exported_Functions_Group2 AES processing functions 
 *  @brief   Processing functions. 
 *
@verbatim   
  ==============================================================================
                      ##### AES processing functions #####
  ==============================================================================  
    [..]  This section provides functions allowing to:
      (+) Encrypt plaintext using AES algorithm in different chaining modes
      (+) Decrypt cyphertext using AES algorithm in different chaining modes
    [..]  Three processing functions are available:
      (+) Polling mode
      (+) Interrupt mode
      (+) DMA mode

@endverbatim
  * @{
  */
  
  
/**
  * @brief  Encrypt pPlainData in AES ECB encryption mode. The cypher data are available in pCypherData.
  * @param  hcryp pointer to a CRYP_HandleTypeDef structure that contains
  *         the configuration information for CRYP module
  * @param  pPlainData Pointer to the plaintext buffer
  * @param  Size Length of the plaintext buffer in bytes, must be a multiple of 16.
  * @param  pCypherData Pointer to the cyphertext buffer
  * @param  Timeout Specify Timeout value 
  * @note   This API is provided only to maintain compatibility with legacy software. Users should directly
  *         resort to generic HAL_CRYPEx_AES() API instead (usage recommended).      
  * @retval HAL status
  */
HAL_StatusTypeDef HAL_CRYP_AESECB_Encrypt(CRYP_HandleTypeDef *hcryp, uint8_t *pPlainData, uint16_t Size, uint8_t *pCypherData, uint32_t Timeout)
{
  /* Re-initialize AES IP with proper parameters */
  if (HAL_CRYP_DeInit(hcryp) != HAL_OK)
  {
    return HAL_ERROR;
  }
  hcryp->Init.OperatingMode = CRYP_ALGOMODE_ENCRYPT;
  hcryp->Init.ChainingMode = CRYP_CHAINMODE_AES_ECB;
  hcryp->Init.KeyWriteFlag = CRYP_KEY_WRITE_ENABLE;
  if (HAL_CRYP_Init(hcryp) != HAL_OK)
  {
    return HAL_ERROR;
  }

  return HAL_CRYPEx_AES(hcryp, pPlainData, Size, pCypherData, Timeout);
}
 

/**
  * @brief  Encrypt pPlainData in AES CBC encryption mode with key derivation. The cypher data are available in pCypherData.
  * @param  hcryp pointer to a CRYP_HandleTypeDef structure that contains
  *         the configuration information for CRYP module
  * @param  pPlainData Pointer to the plaintext buffer
  * @param  Size Length of the plaintext buffer in bytes, must be a multiple of 16.
  * @param  pCypherData Pointer to the cyphertext buffer
  * @param  Timeout Specify Timeout value
  * @note   This API is provided only to maintain compatibility with legacy software. Users should directly
  *         resort to generic HAL_CRYPEx_AES() API instead (usage recommended).     
  * @retval HAL status
  */
HAL_StatusTypeDef HAL_CRYP_AESCBC_Encrypt(CRYP_HandleTypeDef *hcryp, uint8_t *pPlainData, uint16_t Size, uint8_t *pCypherData, uint32_t Timeout)
{ 
  /* Re-initialize AES IP with proper parameters */
  if (HAL_CRYP_DeInit(hcryp) != HAL_OK)
  {
    return HAL_ERROR;
  }
  hcryp->Init.OperatingMode = CRYP_ALGOMODE_ENCRYPT;
  hcryp->Init.ChainingMode = CRYP_CHAINMODE_AES_CBC;
  hcryp->Init.KeyWriteFlag = CRYP_KEY_WRITE_ENABLE;
  if (HAL_CRYP_Init(hcryp) != HAL_OK)
  {
    return HAL_ERROR;
  }
  
  return HAL_CRYPEx_AES(hcryp, pPlainData, Size, pCypherData, Timeout);
}


/**
  * @brief  Encrypt pPlainData in AES CTR encryption mode. The cypher data are available in pCypherData
  * @param  hcryp pointer to a CRYP_HandleTypeDef structure that contains
  *         the configuration information for CRYP module
  * @param  pPlainData Pointer to the plaintext buffer
  * @param  Size Length of the plaintext buffer in bytes, must be a multiple of 16.
  * @param  pCypherData Pointer to the cyphertext buffer
  * @param  Timeout Specify Timeout value 
  * @note   This API is provided only to maintain compatibility with legacy software. Users should directly
  *         resort to generic HAL_CRYPEx_AES() API instead (usage recommended).    
  * @retval HAL status
  */
HAL_StatusTypeDef HAL_CRYP_AESCTR_Encrypt(CRYP_HandleTypeDef *hcryp, uint8_t *pPlainData, uint16_t Size, uint8_t *pCypherData, uint32_t Timeout)
{
  /* Re-initialize AES IP with proper parameters */
  if (HAL_CRYP_DeInit(hcryp) != HAL_OK)
  {
    return HAL_ERROR;
  }
  hcryp->Init.OperatingMode = CRYP_ALGOMODE_ENCRYPT;
  hcryp->Init.ChainingMode = CRYP_CHAINMODE_AES_CTR;
  hcryp->Init.KeyWriteFlag = CRYP_KEY_WRITE_ENABLE;
  if (HAL_CRYP_Init(hcryp) != HAL_OK)
  {
    return HAL_ERROR;
  }

  return HAL_CRYPEx_AES(hcryp, pPlainData, Size, pCypherData, Timeout);
}

/**
  * @brief  Decrypt pCypherData in AES ECB decryption mode with key derivation, 
  *         the decyphered data are available in pPlainData.
  * @param  hcryp pointer to a CRYP_HandleTypeDef structure that contains
  *         the configuration information for CRYP module
  * @param  pCypherData Pointer to the cyphertext buffer
  * @param  Size Length of the plaintext buffer in bytes, must be a multiple of 16.
  * @param  pPlainData Pointer to the plaintext buffer
  * @param  Timeout Specify Timeout value 
  * @note   This API is provided only to maintain compatibility with legacy software. Users should directly
  *         resort to generic HAL_CRYPEx_AES() API instead (usage recommended).   
  * @retval HAL status
  */
HAL_StatusTypeDef HAL_CRYP_AESECB_Decrypt(CRYP_HandleTypeDef *hcryp, uint8_t *pCypherData, uint16_t Size, uint8_t *pPlainData, uint32_t Timeout)
{
  /* Re-initialize AES IP with proper parameters */
  if (HAL_CRYP_DeInit(hcryp) != HAL_OK)
  {
    return HAL_ERROR;
  }
  hcryp->Init.OperatingMode = CRYP_ALGOMODE_KEYDERIVATION_DECRYPT;
  hcryp->Init.ChainingMode = CRYP_CHAINMODE_AES_ECB;
  hcryp->Init.KeyWriteFlag = CRYP_KEY_WRITE_ENABLE;
  if (HAL_CRYP_Init(hcryp) != HAL_OK)
  {
    return HAL_ERROR;
  }

  return HAL_CRYPEx_AES(hcryp, pCypherData, Size, pPlainData, Timeout);
}

/**
  * @brief  Decrypt pCypherData in AES ECB decryption mode with key derivation, 
  *         the decyphered data are available in pPlainData.
  * @param  hcryp pointer to a CRYP_HandleTypeDef structure that contains
  *         the configuration information for CRYP module
  * @param  pCypherData Pointer to the cyphertext buffer
  * @param  Size Length of the plaintext buffer in bytes, must be a multiple of 16.
  * @param  pPlainData Pointer to the plaintext buffer
  * @param  Timeout Specify Timeout value 
  * @note   This API is provided only to maintain compatibility with legacy software. Users should directly
  *         resort to generic HAL_CRYPEx_AES() API instead (usage recommended).    
  * @retval HAL status
  */
HAL_StatusTypeDef HAL_CRYP_AESCBC_Decrypt(CRYP_HandleTypeDef *hcryp, uint8_t *pCypherData, uint16_t Size, uint8_t *pPlainData, uint32_t Timeout)
{
  /* Re-initialize AES IP with proper parameters */
  if (HAL_CRYP_DeInit(hcryp) != HAL_OK)
  {
    return HAL_ERROR;
  }
  hcryp->Init.OperatingMode = CRYP_ALGOMODE_KEYDERIVATION_DECRYPT;
  hcryp->Init.ChainingMode = CRYP_CHAINMODE_AES_CBC;
  hcryp->Init.KeyWriteFlag = CRYP_KEY_WRITE_ENABLE;
  if (HAL_CRYP_Init(hcryp) != HAL_OK)
  {
    return HAL_ERROR;
  }
  
  return HAL_CRYPEx_AES(hcryp, pCypherData, Size, pPlainData, Timeout);
}

/**
  * @brief  Decrypt pCypherData in AES CTR decryption mode, 
  *         the decyphered data are available in pPlainData.
  * @param  hcryp pointer to a CRYP_HandleTypeDef structure that contains
  *         the configuration information for CRYP module
  * @param  pCypherData Pointer to the cyphertext buffer
  * @param  Size Length of the plaintext buffer in bytes, must be a multiple of 16.
  * @param  pPlainData Pointer to the plaintext buffer
  * @param  Timeout Specify Timeout value
  * @note   This API is provided only to maintain compatibility with legacy software. Users should directly
  *         resort to generic HAL_CRYPEx_AES() API instead (usage recommended).     
  * @retval HAL status
  */
HAL_StatusTypeDef HAL_CRYP_AESCTR_Decrypt(CRYP_HandleTypeDef *hcryp, uint8_t *pCypherData, uint16_t Size, uint8_t *pPlainData, uint32_t Timeout)
{
  /* Re-initialize AES IP with proper parameters */
  if (HAL_CRYP_DeInit(hcryp) != HAL_OK)
  {
    return HAL_ERROR;
  }
  hcryp->Init.OperatingMode = CRYP_ALGOMODE_DECRYPT;
  hcryp->Init.ChainingMode = CRYP_CHAINMODE_AES_CTR;
  hcryp->Init.KeyWriteFlag = CRYP_KEY_WRITE_ENABLE;
  if (HAL_CRYP_Init(hcryp) != HAL_OK)
  {
    return HAL_ERROR;
  }  
  
  return HAL_CRYPEx_AES(hcryp, pCypherData, Size, pPlainData, Timeout);
}

/**
  * @brief  Encrypt pPlainData in AES ECB encryption mode using Interrupt,
  *         the cypher data are available in pCypherData.
  * @param  hcryp pointer to a CRYP_HandleTypeDef structure that contains
  *         the configuration information for CRYP module
  * @param  pPlainData Pointer to the plaintext buffer
  * @param  Size Length of the plaintext buffer in bytes, must be a multiple of 16.
  * @param  pCypherData Pointer to the cyphertext buffer
  * @note   This API is provided only to maintain compatibility with legacy software. Users should directly
  *         resort to generic HAL_CRYPEx_AES_IT() API instead (usage recommended).  
  * @retval HAL status
  */
HAL_StatusTypeDef HAL_CRYP_AESECB_Encrypt_IT(CRYP_HandleTypeDef *hcryp, uint8_t *pPlainData, uint16_t Size, uint8_t *pCypherData)
{
  /* Re-initialize AES IP with proper parameters */
  if (HAL_CRYP_DeInit(hcryp) != HAL_OK)
  {
    return HAL_ERROR;
  }
  hcryp->Init.OperatingMode = CRYP_ALGOMODE_ENCRYPT;
  hcryp->Init.ChainingMode = CRYP_CHAINMODE_AES_ECB;
  hcryp->Init.KeyWriteFlag = CRYP_KEY_WRITE_ENABLE;
  if (HAL_CRYP_Init(hcryp) != HAL_OK)
  {
    return HAL_ERROR;
  }  
  
  return HAL_CRYPEx_AES_IT(hcryp, pPlainData, Size, pCypherData);
}

/**
  * @brief  Encrypt pPlainData in AES CBC encryption mode using Interrupt,
  *         the cypher data are available in pCypherData.  
  * @param  hcryp pointer to a CRYP_HandleTypeDef structure that contains
  *         the configuration information for CRYP module
  * @param  pPlainData Pointer to the plaintext buffer
  * @param  Size Length of the plaintext buffer in bytes, must be a multiple of 16.
  * @param  pCypherData Pointer to the cyphertext buffer
  * @note   This API is provided only to maintain compatibility with legacy software. Users should directly
  *         resort to generic HAL_CRYPEx_AES_IT() API instead (usage recommended).   
  * @retval HAL status
  */
HAL_StatusTypeDef HAL_CRYP_AESCBC_Encrypt_IT(CRYP_HandleTypeDef *hcryp, uint8_t *pPlainData, uint16_t Size, uint8_t *pCypherData)
{
  /* Re-initialize AES IP with proper parameters */
  if (HAL_CRYP_DeInit(hcryp) != HAL_OK)
  {
    return HAL_ERROR;
  }
  hcryp->Init.OperatingMode = CRYP_ALGOMODE_ENCRYPT;
  hcryp->Init.ChainingMode = CRYP_CHAINMODE_AES_CBC;
  hcryp->Init.KeyWriteFlag = CRYP_KEY_WRITE_ENABLE;
  if (HAL_CRYP_Init(hcryp) != HAL_OK)
  {
    return HAL_ERROR;
  }
  
  return HAL_CRYPEx_AES_IT(hcryp, pPlainData, Size, pCypherData);
}
  

/**
  * @brief  Encrypt pPlainData in AES CTR encryption mode using Interrupt,
  *         the cypher data are available in pCypherData.  
  * @param  hcryp pointer to a CRYP_HandleTypeDef structure that contains
  *         the configuration information for CRYP module
  * @param  pPlainData Pointer to the plaintext buffer
  * @param  Size Length of the plaintext buffer in bytes, must be a multiple of 16.
  * @param  pCypherData Pointer to the cyphertext buffer
  * @note   This API is provided only to maintain compatibility with legacy software. Users should directly
  *         resort to generic HAL_CRYPEx_AES_IT() API instead (usage recommended).   
  * @retval HAL status
  */
HAL_StatusTypeDef HAL_CRYP_AESCTR_Encrypt_IT(CRYP_HandleTypeDef *hcryp, uint8_t *pPlainData, uint16_t Size, uint8_t *pCypherData)
{
  /* Re-initialize AES IP with proper parameters */
  if (HAL_CRYP_DeInit(hcryp) != HAL_OK)
  {
    return HAL_ERROR;
  }
  hcryp->Init.OperatingMode = CRYP_ALGOMODE_ENCRYPT;
  hcryp->Init.ChainingMode = CRYP_CHAINMODE_AES_CTR;
  hcryp->Init.KeyWriteFlag = CRYP_KEY_WRITE_ENABLE;
  if (HAL_CRYP_Init(hcryp) != HAL_OK)
  {
    return HAL_ERROR;
  }
  
  return HAL_CRYPEx_AES_IT(hcryp, pPlainData, Size, pCypherData);
}

/**
  * @brief  Decrypt pCypherData in AES ECB decryption mode using Interrupt,
  *         the decyphered data are available in pPlainData.   
  * @param  hcryp pointer to a CRYP_HandleTypeDef structure that contains
  *         the configuration information for CRYP module
  * @param  pCypherData Pointer to the cyphertext buffer
  * @param  Size Length of the plaintext buffer in bytes, must be a multiple of 16.
  * @param  pPlainData Pointer to the plaintext buffer.
  * @note   This API is provided only to maintain compatibility with legacy software. Users should directly
  *         resort to generic HAL_CRYPEx_AES_IT() API instead (usage recommended).      
  * @retval HAL status
  */
HAL_StatusTypeDef HAL_CRYP_AESECB_Decrypt_IT(CRYP_HandleTypeDef *hcryp, uint8_t *pCypherData, uint16_t Size, uint8_t *pPlainData)
{
  /* Re-initialize AES IP with proper parameters */
  if (HAL_CRYP_DeInit(hcryp) != HAL_OK)
  {
    return HAL_ERROR;
  }
  hcryp->Init.OperatingMode = CRYP_ALGOMODE_KEYDERIVATION_DECRYPT;
  hcryp->Init.ChainingMode = CRYP_CHAINMODE_AES_ECB;
  hcryp->Init.KeyWriteFlag = CRYP_KEY_WRITE_ENABLE;
  if (HAL_CRYP_Init(hcryp) != HAL_OK)
  {
    return HAL_ERROR;
  }
  
  return HAL_CRYPEx_AES_IT(hcryp, pCypherData, Size, pPlainData);
}

/**
  * @brief  Decrypt pCypherData in AES CBC decryption mode using Interrupt,
  *         the decyphered data are available in pPlainData.  
  * @param  hcryp pointer to a CRYP_HandleTypeDef structure that contains
  *         the configuration information for CRYP module
  * @param  pCypherData Pointer to the cyphertext buffer
  * @param  Size Length of the plaintext buffer in bytes, must be a multiple of 16.
  * @param  pPlainData Pointer to the plaintext buffer
  * @note   This API is provided only to maintain compatibility with legacy software. Users should directly
  *         resort to generic HAL_CRYPEx_AES_IT() API instead (usage recommended).  
  * @retval HAL status
  */
HAL_StatusTypeDef HAL_CRYP_AESCBC_Decrypt_IT(CRYP_HandleTypeDef *hcryp, uint8_t *pCypherData, uint16_t Size, uint8_t *pPlainData)
{
  /* Re-initialize AES IP with proper parameters */
  if (HAL_CRYP_DeInit(hcryp) != HAL_OK)
  {
    return HAL_ERROR;
  }
  hcryp->Init.OperatingMode = CRYP_ALGOMODE_KEYDERIVATION_DECRYPT;
  hcryp->Init.ChainingMode = CRYP_CHAINMODE_AES_CBC;
  hcryp->Init.KeyWriteFlag = CRYP_KEY_WRITE_ENABLE;
  if (HAL_CRYP_Init(hcryp) != HAL_OK)
  {
    return HAL_ERROR;
  }
  
  return HAL_CRYPEx_AES_IT(hcryp, pCypherData, Size, pPlainData);
}

/**
  * @brief  Decrypt pCypherData in AES CTR decryption mode using Interrupt,
  *         the decyphered data are available in pPlainData. 
  * @param  hcryp pointer to a CRYP_HandleTypeDef structure that contains
  *         the configuration information for CRYP module
  * @param  pCypherData Pointer to the cyphertext buffer
  * @param  Size Length of the plaintext buffer in bytes, must be a multiple of 16.
  * @param  pPlainData Pointer to the plaintext buffer
  * @note   This API is provided only to maintain compatibility with legacy software. Users should directly
  *         resort to generic HAL_CRYPEx_AES_IT() API instead (usage recommended).    
  * @retval HAL status
  */
HAL_StatusTypeDef HAL_CRYP_AESCTR_Decrypt_IT(CRYP_HandleTypeDef *hcryp, uint8_t *pCypherData, uint16_t Size, uint8_t *pPlainData)
{
  /* Re-initialize AES IP with proper parameters */
  if (HAL_CRYP_DeInit(hcryp) != HAL_OK)
  {
    return HAL_ERROR;
  }
  hcryp->Init.OperatingMode = CRYP_ALGOMODE_DECRYPT;
  hcryp->Init.ChainingMode = CRYP_CHAINMODE_AES_CTR;
  hcryp->Init.KeyWriteFlag = CRYP_KEY_WRITE_ENABLE;
  if (HAL_CRYP_Init(hcryp) != HAL_OK)
  {
    return HAL_ERROR;
  }  
  
  return HAL_CRYPEx_AES_IT(hcryp, pCypherData, Size, pPlainData);
}

/**
  * @brief  Encrypt pPlainData in AES ECB encryption mode using DMA,
  *         the cypher data are available in pCypherData.   
  * @param  hcryp pointer to a CRYP_HandleTypeDef structure that contains
  *         the configuration information for CRYP module
  * @param  pPlainData Pointer to the plaintext buffer
  * @param  Size Length of the plaintext buffer in bytes, must be a multiple of 16.
  * @param  pCypherData Pointer to the cyphertext buffer
  * @note   This API is provided only to maintain compatibility with legacy software. Users should directly
  *         resort to generic HAL_CRYPEx_AES_DMA() API instead (usage recommended).
  * @note   pPlainData and pCypherData buffers must be 32-bit aligned to ensure a correct DMA transfer to and from the IP.    
  * @retval HAL status
  */
HAL_StatusTypeDef HAL_CRYP_AESECB_Encrypt_DMA(CRYP_HandleTypeDef *hcryp, uint8_t *pPlainData, uint16_t Size, uint8_t *pCypherData)
{
  /* Re-initialize AES IP with proper parameters */
  if (HAL_CRYP_DeInit(hcryp) != HAL_OK)
  {
    return HAL_ERROR;
  }
  hcryp->Init.OperatingMode = CRYP_ALGOMODE_ENCRYPT;
  hcryp->Init.ChainingMode = CRYP_CHAINMODE_AES_ECB;
  hcryp->Init.KeyWriteFlag = CRYP_KEY_WRITE_ENABLE;
  if (HAL_CRYP_Init(hcryp) != HAL_OK)
  {
    return HAL_ERROR;
  }
  
  return HAL_CRYPEx_AES_DMA(hcryp, pPlainData, Size, pCypherData);
}
  
 

/**
  * @brief  Encrypt pPlainData in AES CBC encryption mode using DMA,
  *         the cypher data are available in pCypherData.  
  * @param  hcryp pointer to a CRYP_HandleTypeDef structure that contains
  *         the configuration information for CRYP module
  * @param  pPlainData Pointer to the plaintext buffer
  * @param  Size Length of the plaintext buffer, must be a multiple of 16.
  * @param  pCypherData Pointer to the cyphertext buffer
  * @note   This API is provided only to maintain compatibility with legacy software. Users should directly
  *         resort to generic HAL_CRYPEx_AES_DMA() API instead (usage recommended).
  * @note   pPlainData and pCypherData buffers must be 32-bit aligned to ensure a correct DMA transfer to and from the IP.       
  * @retval HAL status
  */
HAL_StatusTypeDef HAL_CRYP_AESCBC_Encrypt_DMA(CRYP_HandleTypeDef *hcryp, uint8_t *pPlainData, uint16_t Size, uint8_t *pCypherData)
{
  /* Re-initialize AES IP with proper parameters */
  if (HAL_CRYP_DeInit(hcryp) != HAL_OK)
  {
    return HAL_ERROR;
  }
  hcryp->Init.OperatingMode = CRYP_ALGOMODE_ENCRYPT;
  hcryp->Init.ChainingMode = CRYP_CHAINMODE_AES_CBC;
  hcryp->Init.KeyWriteFlag = CRYP_KEY_WRITE_ENABLE;
  if (HAL_CRYP_Init(hcryp) != HAL_OK)
  {
    return HAL_ERROR;
  }
  
  return HAL_CRYPEx_AES_DMA(hcryp, pPlainData, Size, pCypherData);
}

/**
  * @brief  Encrypt pPlainData in AES CTR encryption mode using DMA,
  *         the cypher data are available in pCypherData. 
  * @param  hcryp pointer to a CRYP_HandleTypeDef structure that contains
  *         the configuration information for CRYP module
  * @param  pPlainData Pointer to the plaintext buffer
  * @param  Size Length of the plaintext buffer in bytes, must be a multiple of 16.
  * @param  pCypherData Pointer to the cyphertext buffer.
  * @note   This API is provided only to maintain compatibility with legacy software. Users should directly
  *         resort to generic HAL_CRYPEx_AES_DMA() API instead (usage recommended).
  * @note   pPlainData and pCypherData buffers must be 32-bit aligned to ensure a correct DMA transfer to and from the IP.      
  * @retval HAL status
  */
HAL_StatusTypeDef HAL_CRYP_AESCTR_Encrypt_DMA(CRYP_HandleTypeDef *hcryp, uint8_t *pPlainData, uint16_t Size, uint8_t *pCypherData)
{
  /* Re-initialize AES IP with proper parameters */
  if (HAL_CRYP_DeInit(hcryp) != HAL_OK)
  {
    return HAL_ERROR;
  }
  hcryp->Init.OperatingMode = CRYP_ALGOMODE_ENCRYPT;
  hcryp->Init.ChainingMode = CRYP_CHAINMODE_AES_CTR;
  hcryp->Init.KeyWriteFlag = CRYP_KEY_WRITE_ENABLE;
  if (HAL_CRYP_Init(hcryp) != HAL_OK)
  {
    return HAL_ERROR;
  }

  return HAL_CRYPEx_AES_DMA(hcryp, pPlainData, Size, pCypherData);
}

/**
  * @brief  Decrypt pCypherData in AES ECB decryption mode using DMA,
  *         the decyphered data are available in pPlainData.   
  * @param  hcryp pointer to a CRYP_HandleTypeDef structure that contains
  *         the configuration information for CRYP module
  * @param  pCypherData Pointer to the cyphertext buffer
  * @param  Size Length of the plaintext buffer in bytes, must be a multiple of 16.
  * @param  pPlainData Pointer to the plaintext buffer
  * @note   This API is provided only to maintain compatibility with legacy software. Users should directly
  *         resort to generic HAL_CRYPEx_AES_DMA() API instead (usage recommended). 
  * @note   pPlainData and pCypherData buffers must be 32-bit aligned to ensure a correct DMA transfer to and from the IP.     
  * @retval HAL status
  */
HAL_StatusTypeDef HAL_CRYP_AESECB_Decrypt_DMA(CRYP_HandleTypeDef *hcryp, uint8_t *pCypherData, uint16_t Size, uint8_t *pPlainData)
{
  /* Re-initialize AES IP with proper parameters */
  if (HAL_CRYP_DeInit(hcryp) != HAL_OK)
  {
    return HAL_ERROR;
  }
  hcryp->Init.OperatingMode = CRYP_ALGOMODE_KEYDERIVATION_DECRYPT;
  hcryp->Init.ChainingMode = CRYP_CHAINMODE_AES_ECB;
  hcryp->Init.KeyWriteFlag = CRYP_KEY_WRITE_ENABLE;
  if (HAL_CRYP_Init(hcryp) != HAL_OK)
  {
    return HAL_ERROR;
  }
  
  return HAL_CRYPEx_AES_DMA(hcryp, pCypherData, Size, pPlainData);
}

/**
  * @brief  Decrypt pCypherData in AES CBC decryption mode using DMA,
  *         the decyphered data are available in pPlainData.  
  * @param  hcryp pointer to a CRYP_HandleTypeDef structure that contains
  *         the configuration information for CRYP module
  * @param  pCypherData Pointer to the cyphertext buffer
  * @param  Size Length of the plaintext buffer in bytes, must be a multiple of 16.
  * @param  pPlainData Pointer to the plaintext buffer
  * @note   This API is provided only to maintain compatibility with legacy software. Users should directly
  *         resort to generic HAL_CRYPEx_AES_DMA() API instead (usage recommended).
  * @note   pPlainData and pCypherData buffers must be 32-bit aligned to ensure a correct DMA transfer to and from the IP.      
  * @retval HAL status
  */
HAL_StatusTypeDef HAL_CRYP_AESCBC_Decrypt_DMA(CRYP_HandleTypeDef *hcryp, uint8_t *pCypherData, uint16_t Size, uint8_t *pPlainData)
{
  /* Re-initialize AES IP with proper parameters */
  if (HAL_CRYP_DeInit(hcryp) != HAL_OK)
  {
    return HAL_ERROR;
  }
  hcryp->Init.OperatingMode = CRYP_ALGOMODE_KEYDERIVATION_DECRYPT;
  hcryp->Init.ChainingMode = CRYP_CHAINMODE_AES_CBC;
  hcryp->Init.KeyWriteFlag = CRYP_KEY_WRITE_ENABLE;
  if (HAL_CRYP_Init(hcryp) != HAL_OK)
  {
    return HAL_ERROR;
  }
  
  return HAL_CRYPEx_AES_DMA(hcryp, pCypherData, Size, pPlainData);
}

/**
  * @brief  Decrypt pCypherData in AES CTR decryption mode using DMA,
  *         the decyphered data are available in pPlainData. 
  * @param  hcryp pointer to a CRYP_HandleTypeDef structure that contains
  *         the configuration information for CRYP module
  * @param  pCypherData Pointer to the cyphertext buffer
  * @param  Size Length of the plaintext buffer in bytes, must be a multiple of 16.
  * @param  pPlainData Pointer to the plaintext buffer
  * @note   This API is provided only to maintain compatibility with legacy software. Users should directly
  *         resort to generic HAL_CRYPEx_AES_DMA() API instead (usage recommended). 
  * @note   pPlainData and pCypherData buffers must be 32-bit aligned to ensure a correct DMA transfer to and from the IP.     
  * @retval HAL status
  */
HAL_StatusTypeDef HAL_CRYP_AESCTR_Decrypt_DMA(CRYP_HandleTypeDef *hcryp, uint8_t *pCypherData, uint16_t Size, uint8_t *pPlainData)
{
  /* Re-initialize AES IP with proper parameters */
  if (HAL_CRYP_DeInit(hcryp) != HAL_OK)
  {
    return HAL_ERROR;
  }
  hcryp->Init.OperatingMode = CRYP_ALGOMODE_DECRYPT;
  hcryp->Init.ChainingMode = CRYP_CHAINMODE_AES_CTR;
  hcryp->Init.KeyWriteFlag = CRYP_KEY_WRITE_ENABLE;
  if (HAL_CRYP_Init(hcryp) != HAL_OK)
  {
    return HAL_ERROR;
  }  
  
  return HAL_CRYPEx_AES_DMA(hcryp, pCypherData, Size, pPlainData);
}


/**
  * @}
  */

/** @defgroup CRYP_Exported_Functions_Group3 Callback functions 
 *  @brief   Callback functions. 
 *
@verbatim   
  ==============================================================================
                      ##### Callback functions  #####
  ==============================================================================  
    [..]  This section provides Interruption and DMA callback functions:
      (+) DMA Input data transfer complete
      (+) DMA Output data transfer complete
      (+) DMA or Interrupt error

@endverbatim
  * @{
  */

/**
  * @brief  CRYP error callback.
  * @param  hcryp pointer to a CRYP_HandleTypeDef structure that contains
  *         the configuration information for CRYP module
  * @retval None
  */
__weak void HAL_CRYP_ErrorCallback(CRYP_HandleTypeDef *hcryp)
{
  /* Prevent unused argument(s) compilation warning */
  UNUSED(hcryp);

  /* NOTE : This function should not be modified; when the callback is needed,
            the HAL_CRYP_ErrorCallback can be implemented in the user file
   */
}

/**
  * @brief  Input DMA transfer complete callback.
  * @param  hcryp pointer to a CRYP_HandleTypeDef structure that contains
  *         the configuration information for CRYP module
  * @retval None
  */
__weak void HAL_CRYP_InCpltCallback(CRYP_HandleTypeDef *hcryp)
{
  /* Prevent unused argument(s) compilation warning */
  UNUSED(hcryp);

  /* NOTE : This function should not be modified; when the callback is needed,
            the HAL_CRYP_InCpltCallback can be implemented in the user file
   */
}

/**
  * @brief  Output DMA transfer complete callback.
  * @param  hcryp pointer to a CRYP_HandleTypeDef structure that contains
  *         the configuration information for CRYP module
  * @retval None
  */
__weak void HAL_CRYP_OutCpltCallback(CRYP_HandleTypeDef *hcryp)
{
  /* Prevent unused argument(s) compilation warning */
  UNUSED(hcryp);

  /* NOTE : This function should not be modified; when the callback is needed,
            the HAL_CRYP_OutCpltCallback can be implemented in the user file
   */
}

/**
  * @}
  */

/** @defgroup CRYP_Exported_Functions_Group4 CRYP IRQ handler 
 *  @brief   AES IRQ handler.
 *
@verbatim   
  ==============================================================================
                ##### AES IRQ handler management #####
  ==============================================================================  
[..]  This section provides AES IRQ handler function.

@endverbatim
  * @{
  */

/**
  * @brief  Handle AES interrupt request.
  * @param  hcryp pointer to a CRYP_HandleTypeDef structure that contains
  *         the configuration information for CRYP module
  * @retval None
  */
void HAL_CRYP_IRQHandler(CRYP_HandleTypeDef *hcryp)
{
  /* Check if error occurred */
  if (__HAL_CRYP_GET_IT_SOURCE(CRYP_IT_ERRIE) != RESET)
  {
    /* If Write Error occurred */
    if (__HAL_CRYP_GET_FLAG(CRYP_IT_WRERR) != RESET)
    {
      hcryp->ErrorCode |= HAL_CRYP_WRITE_ERROR;
      hcryp->State = HAL_CRYP_STATE_ERROR;
    }
    /* If Read Error occurred */
    if (__HAL_CRYP_GET_FLAG(CRYP_IT_RDERR) != RESET)
    {
      hcryp->ErrorCode |= HAL_CRYP_READ_ERROR;
      hcryp->State = HAL_CRYP_STATE_ERROR;
    }
    
    /* If an error has been reported */
    if (hcryp->State == HAL_CRYP_STATE_ERROR)
    {  
      /* Disable Error and Computation Complete Interrupts */
      __HAL_CRYP_DISABLE_IT(CRYP_IT_CCFIE|CRYP_IT_ERRIE);
      /* Clear all Interrupt flags */
      __HAL_CRYP_CLEAR_FLAG(CRYP_ERR_CLEAR|CRYP_CCF_CLEAR);
    
      /* Process Unlocked */
      __HAL_UNLOCK(hcryp);  
    
      HAL_CRYP_ErrorCallback(hcryp);
  
      return; 
    }
  }
  
  /* Check if computation complete interrupt is enabled 
     and if the computation complete flag is raised */
  if((__HAL_CRYP_GET_FLAG(CRYP_IT_CCF) != RESET) && (__HAL_CRYP_GET_IT_SOURCE(CRYP_IT_CCFIE) != RESET))
  { 
#if defined(AES_CR_NPBLB)
    if ((hcryp->Init.ChainingMode == CRYP_CHAINMODE_AES_GCM_GMAC)
     || (hcryp->Init.ChainingMode == CRYP_CHAINMODE_AES_CCM_CMAC))
#else     
    if ((hcryp->Init.ChainingMode == CRYP_CHAINMODE_AES_GCM_GMAC)
     || (hcryp->Init.ChainingMode == CRYP_CHAINMODE_AES_CMAC))
#endif     
    {
     /* To ensure proper suspension requests management, CCF flag 
        is reset in CRYP_AES_Auth_IT() according to the current 
        phase under handling */
      CRYP_AES_Auth_IT(hcryp);
    }
    else
    {
      /* Clear Computation Complete Flag */
      __HAL_CRYP_CLEAR_FLAG(CRYP_CCF_CLEAR);
      CRYP_AES_IT(hcryp);
    }
  }
}

/**
  * @}
  */

/** @defgroup CRYP_Exported_Functions_Group5 Peripheral State functions 
 *  @brief   Peripheral State functions. 
 *
@verbatim   
  ==============================================================================
                      ##### Peripheral State functions #####
  ==============================================================================  
    [..]
    This subsection permits to get in run-time the status of the peripheral.

@endverbatim
  * @{
  */

/**
  * @brief  Return the CRYP handle state.
  * @param  hcryp pointer to a CRYP_HandleTypeDef structure that contains
  *         the configuration information for CRYP module
  * @retval HAL state
  */
HAL_CRYP_STATETypeDef HAL_CRYP_GetState(CRYP_HandleTypeDef *hcryp)
{
  /* Return CRYP handle state */
  return hcryp->State;
}

/**
  * @brief  Return the CRYP peripheral error.
  * @param  hcryp pointer to a CRYP_HandleTypeDef structure that contains
  *         the configuration information for CRYP module
  * @note   The returned error is a bit-map combination of possible errors          
  * @retval Error bit-map
  */
uint32_t HAL_CRYP_GetError(CRYP_HandleTypeDef *hcryp)
{
  return hcryp->ErrorCode;
}

/**
  * @}
  */

/**
  * @}
  */

/** @addtogroup CRYP_Private_Functions
  * @{
  */


/**
  * @brief  Write the Key in KeyRx registers. 
  * @param  hcryp pointer to a CRYP_HandleTypeDef structure that contains
  *         the configuration information for CRYP module
  * @retval None
  */
static HAL_StatusTypeDef  CRYP_SetKey(CRYP_HandleTypeDef *hcryp)
{  
  uint32_t keyaddr = 0x0;
  
  if ((uint32_t)(hcryp->Init.pKey == NULL))
  {
    return HAL_ERROR;
  }
  
  
  keyaddr = (uint32_t)(hcryp->Init.pKey);
  
  if (hcryp->Init.KeySize == CRYP_KEYSIZE_256B)
  {
    hcryp->Instance->KEYR7 = __REV(*(uint32_t*)(keyaddr));
    keyaddr+=4;
    hcryp->Instance->KEYR6 = __REV(*(uint32_t*)(keyaddr));
    keyaddr+=4;
    hcryp->Instance->KEYR5 = __REV(*(uint32_t*)(keyaddr));
    keyaddr+=4;
    hcryp->Instance->KEYR4 = __REV(*(uint32_t*)(keyaddr));
    keyaddr+=4;      
  }  
  
  hcryp->Instance->KEYR3 = __REV(*(uint32_t*)(keyaddr));
  keyaddr+=4;
  hcryp->Instance->KEYR2 = __REV(*(uint32_t*)(keyaddr));
  keyaddr+=4;
  hcryp->Instance->KEYR1 = __REV(*(uint32_t*)(keyaddr));
  keyaddr+=4;
  hcryp->Instance->KEYR0 = __REV(*(uint32_t*)(keyaddr));  
  
  return HAL_OK;
}

/**
  * @brief  Write the InitVector/InitCounter in IVRx registers. 
  * @param  hcryp pointer to a CRYP_HandleTypeDef structure that contains
  *         the configuration information for CRYP module
  * @retval None
  */
static HAL_StatusTypeDef CRYP_SetInitVector(CRYP_HandleTypeDef *hcryp)
{
  uint32_t ivaddr = 0x0;
  
#if !defined(AES_CR_NPBLB)
  if (hcryp->Init.ChainingMode == CRYP_CHAINMODE_AES_CMAC)
  {
    hcryp->Instance->IVR3 = 0;
    hcryp->Instance->IVR2 = 0;
    hcryp->Instance->IVR1 = 0;        
    hcryp->Instance->IVR0 = 0;
  }
  else
#endif
  {
    if (hcryp->Init.pInitVect == NULL)
    {
      return HAL_ERROR;
    } 
  
    ivaddr = (uint32_t)(hcryp->Init.pInitVect);
  
    hcryp->Instance->IVR3 = __REV(*(uint32_t*)(ivaddr));
    ivaddr+=4;
    hcryp->Instance->IVR2 = __REV(*(uint32_t*)(ivaddr));
    ivaddr+=4;
    hcryp->Instance->IVR1 = __REV(*(uint32_t*)(ivaddr));
    ivaddr+=4;
    hcryp->Instance->IVR0 = __REV(*(uint32_t*)(ivaddr));
  }
  return HAL_OK;
}



/** 
  * @brief  Handle CRYP block input/output data handling under interruption.
  * @note   The function is called under interruption only, once
  *         interruptions have been enabled by HAL_CRYPEx_AES_IT().
  * @param  hcryp pointer to a CRYP_HandleTypeDef structure that contains
  *         the configuration information for CRYP module.
  * @retval HAL status
  */
static HAL_StatusTypeDef CRYP_AES_IT(CRYP_HandleTypeDef *hcryp)
{
  uint32_t inputaddr = 0;
  uint32_t outputaddr = 0;  

  if(hcryp->State == HAL_CRYP_STATE_BUSY)
  {
    if (hcryp->Init.OperatingMode != CRYP_ALGOMODE_KEYDERIVATION)
    {
      /* Get the output data address */
      outputaddr = (uint32_t)hcryp->pCrypOutBuffPtr;
      
      /* Read the last available output block from the Data Output Register */
      *(uint32_t*)(outputaddr) = hcryp->Instance->DOUTR;
      outputaddr+=4;
      *(uint32_t*)(outputaddr) = hcryp->Instance->DOUTR;
      outputaddr+=4;
      *(uint32_t*)(outputaddr) = hcryp->Instance->DOUTR;
      outputaddr+=4;
      *(uint32_t*)(outputaddr) = hcryp->Instance->DOUTR;
      hcryp->pCrypOutBuffPtr += 16;
      hcryp->CrypOutCount -= 16;
    
    }
    else
    {
      /* Read the derived key from the Key registers */
      if (hcryp->Init.KeySize == CRYP_KEYSIZE_256B)
      {   
        *(uint32_t*)(outputaddr) = __REV(hcryp->Instance->KEYR7);
        outputaddr+=4;
        *(uint32_t*)(outputaddr) = __REV(hcryp->Instance->KEYR6);
        outputaddr+=4;
        *(uint32_t*)(outputaddr) = __REV(hcryp->Instance->KEYR5);
        outputaddr+=4;
        *(uint32_t*)(outputaddr) = __REV(hcryp->Instance->KEYR4);
        outputaddr+=4;
      }
      
        *(uint32_t*)(outputaddr) = __REV(hcryp->Instance->KEYR3);
        outputaddr+=4;
        *(uint32_t*)(outputaddr) = __REV(hcryp->Instance->KEYR2);
        outputaddr+=4;
        *(uint32_t*)(outputaddr) = __REV(hcryp->Instance->KEYR1);
        outputaddr+=4;
        *(uint32_t*)(outputaddr) = __REV(hcryp->Instance->KEYR0);
    }
    
    /* In case of ciphering or deciphering, check if all output text has been retrieved;
       In case of key derivation, stop right there */
    if ((hcryp->CrypOutCount == 0) || (hcryp->Init.OperatingMode == CRYP_ALGOMODE_KEYDERIVATION))
    {
      /* Disable Computation Complete Flag and Errors Interrupts */
      __HAL_CRYP_DISABLE_IT(CRYP_IT_CCFIE|CRYP_IT_ERRIE);
      /* Change the CRYP state */
      hcryp->State = HAL_CRYP_STATE_READY;
      
     /* Process Unlocked */
      __HAL_UNLOCK(hcryp);
      
      /* Call computation complete callback */
      HAL_CRYPEx_ComputationCpltCallback(hcryp);
      
      return HAL_OK;
    }
    /* If suspension flag has been raised, suspend processing */
    else if (hcryp->SuspendRequest == HAL_CRYP_SUSPEND)
    {
      /* reset ModeSuspend */
      hcryp->SuspendRequest = HAL_CRYP_SUSPEND_NONE;
      
      /* Disable Computation Complete Flag and Errors Interrupts */
      __HAL_CRYP_DISABLE_IT(CRYP_IT_CCFIE|CRYP_IT_ERRIE);
      /* Change the CRYP state */
      hcryp->State = HAL_CRYP_STATE_SUSPENDED;
      
     /* Process Unlocked */
      __HAL_UNLOCK(hcryp);
      
      return HAL_OK;
    }
    else /* Process the rest of input data */
    {
      /* Get the Intput data address */
      inputaddr = (uint32_t)hcryp->pCrypInBuffPtr;
      
      /* Increment/decrement instance pointer/counter */
      hcryp->pCrypInBuffPtr += 16;
      hcryp->CrypInCount -= 16;
      
      /* Write the next input block in the Data Input register */
      hcryp->Instance->DINR = *(uint32_t*)(inputaddr);
      inputaddr+=4;
      hcryp->Instance->DINR = *(uint32_t*)(inputaddr);
      inputaddr+=4;
      hcryp->Instance->DINR  = *(uint32_t*)(inputaddr);
      inputaddr+=4;
      hcryp->Instance->DINR = *(uint32_t*)(inputaddr);
      
      return HAL_OK;      
    }
  }
  else
  {
    return HAL_BUSY; 
  }
}
        

=======
  * @brief  AES CCM encryption/decryption process in interrupt mode 
  *         for TinyAES IP, no encrypt/decrypt performed, only authentication preparation.
  * @param  hcryp: pointer to a CRYP_HandleTypeDef structure that contains
  *         the configuration information for CRYP module
  * @retval HAL status
  */
static HAL_StatusTypeDef CRYP_AESCCM_Process_IT(CRYP_HandleTypeDef *hcryp)
{
#if defined(CRYP)
  __IO uint32_t count = 0U;
#endif /* CRYP */
  
  /*  Reset CrypHeaderCount */
  hcryp->CrypHeaderCount = 0U;
  
#if defined(CRYP)
  
  /************ Init phase ************/
  
  CRYP_SET_PHASE(hcryp,CRYP_PHASE_INIT);
  
  /* Set the key */
  CRYP_SetKey(hcryp, hcryp->Init.KeySize);
  
  /* Set the initialization vector (IV) with CTR1 information */
  hcryp->Instance->IV0LR = (hcryp->Init.B0[0]) & CRYP_CCM_CTR1_0;
  hcryp->Instance->IV0RR = hcryp->Init.B0[1];
  hcryp->Instance->IV1LR = hcryp->Init.B0[2];
  hcryp->Instance->IV1RR = (hcryp->Init.B0[3] & CRYP_CCM_CTR1_1)|  CRYP_CCM_CTR1_2;
  
  /* Enable the CRYP peripheral */
  __HAL_CRYP_ENABLE(hcryp);
  
  /*Write the B0 packet into CRYP_DIN Register*/
  if(hcryp->Init.DataType == CRYP_DATATYPE_8B)
  {
    hcryp->Instance->DIN = __REV(*(uint32_t*)(hcryp->Init.B0));
    hcryp->Instance->DIN = __REV( *(uint32_t*)(hcryp->Init.B0+1));
    hcryp->Instance->DIN = __REV(*(uint32_t*)(hcryp->Init.B0+2));
    hcryp->Instance->DIN = __REV(*(uint32_t*)(hcryp->Init.B0+3));
  }
  else if(hcryp->Init.DataType == CRYP_DATATYPE_16B)
  {
    hcryp->Instance->DIN = __ROR(*(uint32_t*)(hcryp->Init.B0), 16);
    hcryp->Instance->DIN = __ROR( *(uint32_t*)(hcryp->Init.B0+1), 16);
    hcryp->Instance->DIN = __ROR(*(uint32_t*)(hcryp->Init.B0+2), 16);
    hcryp->Instance->DIN = __ROR(*(uint32_t*)(hcryp->Init.B0+3), 16);
  }
  else if(hcryp->Init.DataType == CRYP_DATATYPE_1B)
  {
    hcryp->Instance->DIN = __RBIT(*(uint32_t*)(hcryp->Init.B0));
    hcryp->Instance->DIN = __RBIT( *(uint32_t*)(hcryp->Init.B0+1));
    hcryp->Instance->DIN = __RBIT(*(uint32_t*)(hcryp->Init.B0+2));
    hcryp->Instance->DIN = __RBIT(*(uint32_t*)(hcryp->Init.B0+3));
  }
  else
  {
    hcryp->Instance->DIN = *(uint32_t*)(hcryp->Init.B0);
    hcryp->Instance->DIN = *(uint32_t*)(hcryp->Init.B0+1);
    hcryp->Instance->DIN = *(uint32_t*)(hcryp->Init.B0+2);
    hcryp->Instance->DIN = *(uint32_t*)(hcryp->Init.B0+3);
  }
  /*Wait for the CRYPEN bit to be cleared*/
  count = CRYP_TIMEOUT_GCMCCMINITPHASE;
  do
  {
    count-- ;
    if(count == 0U)
    {
      /* Disable the CRYP peripheral clock */
      __HAL_CRYP_DISABLE(hcryp);
      
      /* Change state */
      hcryp->ErrorCode |= HAL_CRYP_ERROR_TIMEOUT;
      hcryp->State = HAL_CRYP_STATE_READY;  
      
      /* Process unlocked */          
      __HAL_UNLOCK(hcryp); 
      return HAL_ERROR;
    }
  }
  while((hcryp->Instance->CR & CRYP_CR_CRYPEN) == CRYP_CR_CRYPEN);
  
  /* Select header phase */
  CRYP_SET_PHASE(hcryp, CRYP_PHASE_HEADER); 
  
  /* Enable interrupts */
  __HAL_CRYP_ENABLE_IT(hcryp, CRYP_IT_INI);
  
  /* Enable CRYP */
  __HAL_CRYP_ENABLE(hcryp); 
  
#else /* AES */ 
  
  /*AES2v1.1.1 : CCM authentication : no init phase, only header and final phase */ 
  /* Select header phase */
  CRYP_SET_PHASE(hcryp, CRYP_PHASE_HEADER); 
  
  /* configured mode and encryption mode */
  MODIFY_REG(hcryp->Instance->CR, AES_CR_MODE, CRYP_OPERATINGMODE_ENCRYPT); 
  
  /* Set the key */
  CRYP_SetKey(hcryp, hcryp->Init.KeySize);     
  
  /* Set the initialization vector with zero values*/ 
  hcryp->Instance->IVR3 = 0U;
  hcryp->Instance->IVR2 = 0U;
  hcryp->Instance->IVR1 = 0U;
  hcryp->Instance->IVR0 = 0U;
  
  /* Enable interrupts */
  __HAL_CRYP_ENABLE_IT(hcryp,CRYP_IT_CCFIE | CRYP_IT_ERRIE); 
  /* Enable the CRYP peripheral */
  __HAL_CRYP_ENABLE(hcryp);
  
  /*Write the B0 packet into CRYP_DIN*/
  hcryp->Instance->DINR = *(uint32_t*)(hcryp->Init.B0);
  hcryp->Instance->DINR = *(uint32_t*)(hcryp->Init.B0+1);
  hcryp->Instance->DINR = *(uint32_t*)(hcryp->Init.B0+2);
  hcryp->Instance->DINR = *(uint32_t*)(hcryp->Init.B0+3); 
  
#endif /* End AES or CRYP */
  
  /* Return function status */
  return HAL_OK;  
}
/**
  * @brief  AES CCM encryption/decryption process in DMA mode 
  *         for TinyAES IP, no encrypt/decrypt performed, only authentication preparation.
  * @param  hcryp: pointer to a CRYP_HandleTypeDef structure that contains
  *         the configuration information for CRYP module
  * @retval HAL status
  */
static HAL_StatusTypeDef CRYP_AESCCM_Process_DMA(CRYP_HandleTypeDef *hcryp)
{  
  uint32_t wordsize;
  __IO uint32_t count = 0U;
  
  /*  Reset CrypHeaderCount */
  hcryp->CrypHeaderCount = 0U;
  
#if defined(CRYP)  
  
  /************************** Init phase **************************************/
  
  CRYP_SET_PHASE(hcryp,CRYP_PHASE_INIT);
  
  /* Set the key */
  CRYP_SetKey(hcryp, hcryp->Init.KeySize);  
  
  /* Set the initialization vector (IV) with CTR1 information */
  hcryp->Instance->IV0LR = (hcryp->Init.B0[0]) & CRYP_CCM_CTR1_0;
  hcryp->Instance->IV0RR = hcryp->Init.B0[1];
  hcryp->Instance->IV1LR = hcryp->Init.B0[2];
  hcryp->Instance->IV1RR = (hcryp->Init.B0[3] & CRYP_CCM_CTR1_1)|  CRYP_CCM_CTR1_2;
  
  /* Enable the CRYP peripheral */
  __HAL_CRYP_ENABLE(hcryp);
  
  /*Write the B0 packet into CRYP_DIN Register*/
  if(hcryp->Init.DataType == CRYP_DATATYPE_8B)
  {
    hcryp->Instance->DIN = __REV(*(uint32_t*)(hcryp->Init.B0));
    hcryp->Instance->DIN = __REV( *(uint32_t*)(hcryp->Init.B0+1));
    hcryp->Instance->DIN = __REV(*(uint32_t*)(hcryp->Init.B0+2));
    hcryp->Instance->DIN = __REV(*(uint32_t*)(hcryp->Init.B0+3));
  }
  else if(hcryp->Init.DataType == CRYP_DATATYPE_16B)
  {
    hcryp->Instance->DIN = __ROR(*(uint32_t*)(hcryp->Init.B0), 16);
    hcryp->Instance->DIN = __ROR( *(uint32_t*)(hcryp->Init.B0+1), 16);
    hcryp->Instance->DIN = __ROR(*(uint32_t*)(hcryp->Init.B0+2), 16);
    hcryp->Instance->DIN = __ROR(*(uint32_t*)(hcryp->Init.B0+3), 16);    
  }
  else if(hcryp->Init.DataType == CRYP_DATATYPE_1B)
  {
    hcryp->Instance->DIN = __RBIT(*(uint32_t*)(hcryp->Init.B0));
    hcryp->Instance->DIN = __RBIT( *(uint32_t*)(hcryp->Init.B0+1));
    hcryp->Instance->DIN = __RBIT(*(uint32_t*)(hcryp->Init.B0+2));
    hcryp->Instance->DIN = __RBIT(*(uint32_t*)(hcryp->Init.B0+3));
  }
  else
  {
    hcryp->Instance->DIN = *(uint32_t*)(hcryp->Init.B0);
    hcryp->Instance->DIN = *(uint32_t*)(hcryp->Init.B0+1);
    hcryp->Instance->DIN = *(uint32_t*)(hcryp->Init.B0+2);
    hcryp->Instance->DIN = *(uint32_t*)(hcryp->Init.B0+3);
  }
  
  /*Wait for the CRYPEN bit to be cleared*/
  count = CRYP_TIMEOUT_GCMCCMINITPHASE;
  do
  {
    count-- ;
    if(count == 0U)
    {
      /* Disable the CRYP peripheral clock */
      __HAL_CRYP_DISABLE(hcryp);
      
      /* Change state */
      hcryp->ErrorCode |= HAL_CRYP_ERROR_TIMEOUT;
      hcryp->State = HAL_CRYP_STATE_READY;
      
      /* Process unlocked */          
      __HAL_UNLOCK(hcryp); 
      return HAL_ERROR;
    }
  }
  while((hcryp->Instance->CR & CRYP_CR_CRYPEN) == CRYP_CR_CRYPEN);
  
#else /* AES */ 
  
  /*AES2v1.1.1 : CCM authentication : no init phase, only header and final phase */ 
  /* Select header phase */
  CRYP_SET_PHASE(hcryp, CRYP_PHASE_HEADER); 
  
  /* configured CCM chaining mode and encryption mode */
  MODIFY_REG(hcryp->Instance->CR, AES_CR_MODE, CRYP_OPERATINGMODE_ENCRYPT);
  
  /* Set the key */
  CRYP_SetKey(hcryp, hcryp->Init.KeySize);     
  
  /* Set the initialization vector with zero values*/ 
  hcryp->Instance->IVR3 = 0U;
  hcryp->Instance->IVR2 = 0U;
  hcryp->Instance->IVR1 = 0U;
  hcryp->Instance->IVR0 = 0U;
  
  /* Enable the CRYP peripheral */
  __HAL_CRYP_ENABLE(hcryp);
  
  /*Write the B0 packet into CRYP_DIN*/
  hcryp->Instance->DINR = *(uint32_t*)(hcryp->Init.B0);
  hcryp->Instance->DINR = *(uint32_t*)(hcryp->Init.B0+1);
  hcryp->Instance->DINR = *(uint32_t*)(hcryp->Init.B0+2);
  hcryp->Instance->DINR = *(uint32_t*)(hcryp->Init.B0+3); 
  
  /*  wait until the end of computation */
  count = CRYP_TIMEOUT_GCMCCMINITPHASE;
  do
  {
    count-- ;
    if(count == 0U)
{
  /* Disable the CRYP peripheral clock */
  __HAL_CRYP_DISABLE(hcryp);
  
  /* Change state */
  hcryp->ErrorCode |= HAL_CRYP_ERROR_TIMEOUT;
  hcryp->State = HAL_CRYP_STATE_READY;  
  
  /* Process Unlocked */          
  __HAL_UNLOCK(hcryp); 
  return HAL_ERROR;
}
  }
  while(HAL_IS_BIT_CLR(hcryp->Instance->SR, AES_SR_CCF));
  
  /* Clear CCF flag */
  __HAL_CRYP_CLEAR_FLAG(hcryp, CRYP_CCF_CLEAR);
  
#endif /* AES */
  
  /********************* Header phase *****************************************/
  
  if(CRYP_GCMCCM_SetHeaderPhase_DMA(hcryp) != HAL_OK)
  {
    return HAL_ERROR;
  }
  
  /******************** Payload phase *****************************************/   
  
  /* Set the phase */
  hcryp->Phase = CRYP_PHASE_PROCESS;  
  
#if defined(CRYP)  
  
  /* Disable the CRYP peripheral */
  __HAL_CRYP_DISABLE(hcryp);
  
  /* Select payload phase once the header phase is performed */
  CRYP_SET_PHASE(hcryp, CRYP_PHASE_PAYLOAD);
  
#endif /* CRYP */   
  
  if(hcryp->Size != 0U)
  { 
    /* Size should be %4  otherwise Tag will  be incorrectly generated for GCM Encryption & CCM Decryption
    Workaround is implemented in polling mode, so if last block of 
    payload <128bit don't use HAL_CRYP_AESGCM_DMA otherwise TAG is incorrectly generated for GCM Encryption. */
    /* Set the input and output addresses and start DMA transfer */ 
    if ((hcryp->Size % 16U) == 0U) 
    {  
      CRYP_SetDMAConfig(hcryp, (uint32_t)( hcryp->pCrypInBuffPtr), hcryp->Size/4U, (uint32_t)(hcryp->pCrypOutBuffPtr));   
    }
    else
    {
      wordsize = (uint32_t)(hcryp->Size)+16U-((uint32_t)(hcryp->Size) %16U) ; 
      
      /* Set the input and output addresses and start DMA transfer, pCrypOutBuffPtr size should be %4*/ 
      CRYP_SetDMAConfig(hcryp, (uint32_t)( hcryp->pCrypInBuffPtr), (uint16_t)wordsize/4U, (uint32_t)(hcryp->pCrypOutBuffPtr));
    }   
  }
  else /*Size = 0*/
  {
    /* Process unlocked */
    __HAL_UNLOCK(hcryp);
    
    /* Change the CRYP state and phase */
    hcryp->State = HAL_CRYP_STATE_READY;
  }         
  
  /* Return function status */
  return HAL_OK;
}

/**
  * @brief  Sets the payload phase in iterrupt mode
  * @param  hcryp: pointer to a CRYP_HandleTypeDef structure that contains
  *         the configuration information for CRYP module  
  * @retval state
  */
static void CRYP_GCMCCM_SetPayloadPhase_IT(CRYP_HandleTypeDef *hcryp)
{  
  uint32_t loopcounter;
  uint32_t temp;  /* Temporary CrypOutBuff */
  uint32_t lastwordsize; 
  uint32_t npblb;	
 #if defined(AES) 
  uint16_t outcount;  /* Temporary CrypOutCount Value */ 
#endif /* AES */ 
  
  /***************************** Payload phase *******************************/
  
#if defined(CRYP)  
  if(hcryp->Size == 0U)
  {     
    /* Disable interrupts */
    __HAL_CRYP_DISABLE_IT(hcryp, CRYP_IT_INI| CRYP_IT_OUTI);
    
    /* Process unlocked */
    __HAL_UNLOCK(hcryp);
    
    /* Change the CRYP state */
    hcryp->State = HAL_CRYP_STATE_READY;      
  }    
  
  else if (((hcryp->Size/4U) - (hcryp->CrypInCount)) >= 4U)
  { 
    /* Write the input block in the IN FIFO */
    hcryp->Instance->DIN  = *(uint32_t *)(hcryp->pCrypInBuffPtr + hcryp->CrypInCount );
    hcryp->CrypInCount++;
    hcryp->Instance->DIN  = *(uint32_t *)(hcryp->pCrypInBuffPtr + hcryp->CrypInCount );
    hcryp->CrypInCount++;   
    hcryp->Instance->DIN  = *(uint32_t *)(hcryp->pCrypInBuffPtr + hcryp->CrypInCount );
    hcryp->CrypInCount++;
    hcryp->Instance->DIN  = *(uint32_t *)(hcryp->pCrypInBuffPtr + hcryp->CrypInCount );
    hcryp->CrypInCount++; 
    if(((hcryp->Size/4U) == hcryp->CrypInCount) &&((hcryp->Size %16U )== 0U))
    {     
      /* Disable interrupts */
      __HAL_CRYP_DISABLE_IT(hcryp, CRYP_IT_INI);
      
      /* Call the input data transfer complete callback */
#if (USE_HAL_CRYP_REGISTER_CALLBACKS == 1U) 
      /*Call registered Input complete callback*/
      hcryp->InCpltCallback(hcryp);
#else
      /*Call legacy weak Input complete callback*/
      HAL_CRYP_InCpltCallback(hcryp);
#endif /* USE_HAL_CRYP_REGISTER_CALLBACKS */
    }    
    if(hcryp->CrypOutCount < (hcryp->Size/4U))        
    {
      /* Read the output block from the Output FIFO and put them in temporary buffer then get CrypOutBuff from temporary buffer  */ 
      temp  = hcryp->Instance->DOUT;
      *(uint32_t *)(hcryp->pCrypOutBuffPtr + hcryp->CrypOutCount) = temp;      
      hcryp->CrypOutCount++;
      temp  = hcryp->Instance->DOUT;    
      *(uint32_t *)(hcryp->pCrypOutBuffPtr + hcryp->CrypOutCount) = temp;
      hcryp->CrypOutCount++;    
      temp  = hcryp->Instance->DOUT;    
      *(uint32_t *)(hcryp->pCrypOutBuffPtr + hcryp->CrypOutCount) = temp;      
      hcryp->CrypOutCount++;
      temp  = hcryp->Instance->DOUT;   
      *(uint32_t *)(hcryp->pCrypOutBuffPtr + hcryp->CrypOutCount) = temp;
      hcryp->CrypOutCount++;
      if (((hcryp->Size/4U) == hcryp->CrypOutCount)&&((hcryp->Size %16U )== 0U))
      {     
        /* Disable interrupts */
        __HAL_CRYP_DISABLE_IT(hcryp, CRYP_IT_OUTI);
        
        /* Change the CRYP state */
        hcryp->State = HAL_CRYP_STATE_READY;
        
        /* Disable CRYP */
        __HAL_CRYP_DISABLE(hcryp);
        
        /* Process unlocked */
        __HAL_UNLOCK(hcryp);
        
        /* Call output transfer complete callback */
#if (USE_HAL_CRYP_REGISTER_CALLBACKS == 1) 
        /*Call registered Output complete callback*/
        hcryp->OutCpltCallback(hcryp);
#else
        /*Call legacy weak Output complete callback*/
        HAL_CRYP_OutCpltCallback(hcryp);
#endif /* USE_HAL_CRYP_REGISTER_CALLBACKS */  
      }    
    }      
  }   
  else if ((hcryp->Size %16U )!= 0U)
  {   
    /* Size should be %4 in word and %16 in byte  otherwise TAG will  be incorrectly generated for GCM Encryption & CCM Decryption
    Workaround is implemented in polling mode, so if last block of 
    payload <128bit don't use CRYP_AESGCM_Encrypt_IT otherwise TAG is incorrectly generated. */
    
       /* Compute the number of padding bytes in last block of payload */
    npblb = ((((uint32_t)(hcryp->Size)/16U)+1U)*16U)- (uint32_t)(hcryp->Size);
    
    /* Number of valid words (lastwordsize) in last block */
    if ((npblb%4U) ==0U) 
    { 
      lastwordsize = (16U-npblb)/4U;		
    }
    else 
    {
      lastwordsize = ((16U-npblb)/4U) +1U;
    }	
    
    /*  Last block optionally pad the data with zeros*/
    for(loopcounter = 0U; loopcounter < lastwordsize; loopcounter++)
    {
      hcryp->Instance->DIN = *(uint32_t *)(hcryp->pCrypInBuffPtr + hcryp->CrypInCount );
      hcryp->CrypInCount++;
    }
    while(loopcounter < 4U )
    { 
      /* Pad the data with zeros to have a complete block */     
      hcryp->Instance->DIN = 0x0U;         
      loopcounter++;
    }
    __HAL_CRYP_DISABLE_IT(hcryp, CRYP_IT_INI);
    
    if((hcryp->Instance->SR & CRYP_FLAG_OFNE ) != 0x0U) 
    {
      for(loopcounter = 0U; loopcounter < 4U; loopcounter++)        
      {  
        /* Read the output block from the output FIFO and put them in temporary buffer */
        temp= hcryp->Instance->DOUT; 
        
        /*get CrypOutBuff from temporary buffer  */
        *(uint32_t *)(hcryp->pCrypOutBuffPtr + (hcryp->CrypOutCount))=temp; 
        hcryp->CrypOutCount++;   
      }     
    }         
    if(hcryp->CrypOutCount >=  (hcryp->Size/4U))
    {              
      /* Disable interrupts */
      __HAL_CRYP_DISABLE_IT(hcryp, CRYP_IT_OUTI|CRYP_IT_INI);
      
      /* Change the CRYP peripheral state */
      hcryp->State = HAL_CRYP_STATE_READY;
      
      /* Process unlocked */
      __HAL_UNLOCK(hcryp);
      
      /* Call output transfer complete callback */
#if (USE_HAL_CRYP_REGISTER_CALLBACKS == 1) 
      /*Call registered Output complete callback*/
      hcryp->OutCpltCallback(hcryp);
#else
      /*Call legacy weak Output complete callback*/
      HAL_CRYP_OutCpltCallback(hcryp);
#endif /* USE_HAL_CRYP_REGISTER_CALLBACKS */  
    }   
  }
  else
  {
    /* Nothing to do */
  }
#else /* AES */
  
  /* Read the output block from the output FIFO and put them in temporary buffer then get CrypOutBuff from temporary buffer*/ 
  temp  = hcryp->Instance->DOUTR;
  *(uint32_t *)(hcryp->pCrypOutBuffPtr + (hcryp->CrypOutCount)) =temp;
  hcryp->CrypOutCount++;
  temp  = hcryp->Instance->DOUTR;
  *(uint32_t *)(hcryp->pCrypOutBuffPtr + hcryp->CrypOutCount)   =temp;
  hcryp->CrypOutCount++;    
  temp  = hcryp->Instance->DOUTR;
  *(uint32_t *)(hcryp->pCrypOutBuffPtr + (hcryp->CrypOutCount)) = temp;      
  hcryp->CrypOutCount++;
  temp  = hcryp->Instance->DOUTR; 
  *(uint32_t *)(hcryp->pCrypOutBuffPtr + hcryp->CrypOutCount)   = temp;
  hcryp->CrypOutCount++; 
  /*Temporary CrypOutCount Value*/
  outcount = hcryp->CrypOutCount;
  
  if((hcryp->CrypOutCount >=  (hcryp->Size/4U)) && ((outcount*4U) >=  hcryp->Size) )
  {
    /* Disable computation complete flag and errors interrupts */
    __HAL_CRYP_DISABLE_IT(hcryp,CRYP_IT_CCFIE|CRYP_IT_ERRIE);
    
    /* Change the CRYP state */
    hcryp->State = HAL_CRYP_STATE_READY;
    
    /* Process unlocked */
    __HAL_UNLOCK(hcryp);
    
        /* Call output transfer complete callback */
#if (USE_HAL_CRYP_REGISTER_CALLBACKS == 1) 
        /*Call registered Output complete callback*/
        hcryp->OutCpltCallback(hcryp);
#else
        /*Call legacy weak Output complete callback*/
        HAL_CRYP_OutCpltCallback(hcryp);
#endif /* USE_HAL_CRYP_REGISTER_CALLBACKS */  
  }   
  
  else if (((hcryp->Size/4U) - (hcryp->CrypInCount)) >= 4U)
  { 
    /* Write the input block in the IN FIFO */
    hcryp->Instance->DINR  = *(uint32_t *)(hcryp->pCrypInBuffPtr + hcryp->CrypInCount );
    hcryp->CrypInCount++;
    hcryp->Instance->DINR  = *(uint32_t *)(hcryp->pCrypInBuffPtr + hcryp->CrypInCount );
    hcryp->CrypInCount++;   
    hcryp->Instance->DINR  = *(uint32_t *)(hcryp->pCrypInBuffPtr + hcryp->CrypInCount );
    hcryp->CrypInCount++;
    hcryp->Instance->DINR  = *(uint32_t *)(hcryp->pCrypInBuffPtr + hcryp->CrypInCount );
    hcryp->CrypInCount++;  
    if((hcryp->CrypInCount ==  hcryp->Size) && (hcryp->Init.Algorithm == CRYP_AES_GCM_GMAC))
    { 
      /* Call Input transfer complete callback */
#if (USE_HAL_CRYP_REGISTER_CALLBACKS == 1) 
      /*Call registered Input complete callback*/
      hcryp->InCpltCallback(hcryp);
#else
      /*Call legacy weak Input complete callback*/
      HAL_CRYP_InCpltCallback(hcryp);
#endif /* USE_HAL_CRYP_REGISTER_CALLBACKS */      
    } 
  }
  else /* Last block of payload < 128bit*/
  {    
    /* Workaround not implemented, Size should be %4  otherwise Tag will  be incorrectly
    generated for GCM Encryption & CCM Decryption. Workaround is implemented in polling mode, so if last block of 
    payload <128bit don't use CRYP_Encrypt_IT otherwise TAG is incorrectly generated for GCM Encryption & CCM Decryption. */  
    
    /* Compute the number of padding bytes in last block of payload */
    npblb = ((((uint32_t)(hcryp->Size)/16U)+1U)*16U) - (uint32_t)(hcryp->Size);
 
        /* Number of valid words (lastwordsize) in last block */
    if ((npblb%4U) ==0U) 
    { 
      lastwordsize = (16U-npblb)/4U;		
    }
    else 
    {
      lastwordsize = ((16U-npblb)/4U) +1U;
    }	
    
    /*  Last block optionally pad the data with zeros*/
    for(loopcounter = 0U; loopcounter < lastwordsize; loopcounter++)
    {
      hcryp->Instance->DINR = *(uint32_t *)(hcryp->pCrypInBuffPtr + hcryp->CrypInCount );
      hcryp->CrypInCount++;
    }
    while(loopcounter < 4U )
    { 
      /* pad the data with zeros to have a complete block */     
      hcryp->Instance->DINR = 0x0U;         
      loopcounter++;
    }
  } 
#endif /* AES */ 

} 


/**
  * @brief  Sets the header phase in polling mode
  * @param  hcryp: pointer to a CRYP_HandleTypeDef structure that contains
  *         the configuration information for CRYP module(Header & HeaderSize)
  * @param  Timeout: Timeout value   
  * @retval state
  */
static HAL_StatusTypeDef CRYP_GCMCCM_SetHeaderPhase(CRYP_HandleTypeDef *hcryp, uint32_t Timeout)
{
  uint32_t loopcounter;
  
  /***************************** Header phase for GCM/GMAC or CCM *********************************/
  
  if((hcryp->Init.HeaderSize != 0U))
  {
    
#if defined(CRYP)  
    
    /* Select header phase */
    CRYP_SET_PHASE(hcryp, CRYP_PHASE_HEADER); 
    
    /* Enable the CRYP peripheral */
    __HAL_CRYP_ENABLE(hcryp);    
    
    if ((hcryp->Init.HeaderSize %4U )== 0U)
    { 
      /* HeaderSize %4, no padding */ 
      for(loopcounter = 0U; (loopcounter < hcryp->Init.HeaderSize); loopcounter+=4U)
      {      
        hcryp->Instance->DIN = *(uint32_t*)(hcryp->Init.Header + hcryp->CrypHeaderCount);
        hcryp->CrypHeaderCount++ ;
        hcryp->Instance->DIN = *(uint32_t*)(hcryp->Init.Header + hcryp->CrypHeaderCount);
        hcryp->CrypHeaderCount++ ;
        hcryp->Instance->DIN = *(uint32_t*)(hcryp->Init.Header + hcryp->CrypHeaderCount);
        hcryp->CrypHeaderCount++ ;
        hcryp->Instance->DIN = *(uint32_t*)(hcryp->Init.Header + hcryp->CrypHeaderCount);
        hcryp->CrypHeaderCount++ ;
        
        /* Wait for IFEM to be raised */
        if(CRYP_WaitOnIFEMFlag(hcryp, Timeout) != HAL_OK)  
        { 
          /* Disable the CRYP peripheral clock */
          __HAL_CRYP_DISABLE(hcryp);
          
          /* Change state */
          hcryp->ErrorCode |= HAL_CRYP_ERROR_TIMEOUT;
          hcryp->State = HAL_CRYP_STATE_READY; 
          
          /* Process unlocked */          
          __HAL_UNLOCK(hcryp); 
          return HAL_ERROR;
        }          
      }
    }
    else
    {   
      /*Write header block in the IN FIFO without last block */
      for(loopcounter = 0U; (loopcounter < ((hcryp->Init.HeaderSize)-(hcryp->Init.HeaderSize %4U ))); loopcounter+= 4U)
      {    
        hcryp->Instance->DIN = *(uint32_t*)(hcryp->Init.Header + hcryp->CrypHeaderCount);
        hcryp->CrypHeaderCount++ ;
        hcryp->Instance->DIN = *(uint32_t*)(hcryp->Init.Header + hcryp->CrypHeaderCount);
        hcryp->CrypHeaderCount++ ;
        hcryp->Instance->DIN = *(uint32_t*)(hcryp->Init.Header + hcryp->CrypHeaderCount);
        hcryp->CrypHeaderCount++ ; 
        hcryp->Instance->DIN = *(uint32_t*)(hcryp->Init.Header + hcryp->CrypHeaderCount);
        hcryp->CrypHeaderCount++ ;
        
        /* Wait for IFEM to be raised */
        if(CRYP_WaitOnIFEMFlag(hcryp, Timeout) != HAL_OK)  
        { 
          /* Disable the CRYP peripheral clock */
          __HAL_CRYP_DISABLE(hcryp);
          
          /* Change state */
          hcryp->ErrorCode |= HAL_CRYP_ERROR_TIMEOUT;
          hcryp->State = HAL_CRYP_STATE_READY; 
          
          /* Process unlocked */          
          __HAL_UNLOCK(hcryp); 
          return HAL_ERROR;
        }
      }
      /*  Last block optionally pad the data with zeros*/
      for(loopcounter = 0U; (loopcounter < (hcryp->Init.HeaderSize %4U )); loopcounter++)
      {
        hcryp->Instance->DIN = *(uint32_t*)(hcryp->Init.Header + hcryp->CrypHeaderCount);
        hcryp->CrypHeaderCount++ ;    
      }
      while(loopcounter <4U )
      { 
        /* pad the data with zeros to have a complete block */     
        hcryp->Instance->DIN = 0x0U;         
        loopcounter++;
      }
      /* Wait for CCF IFEM to be raised */
      if(CRYP_WaitOnIFEMFlag(hcryp, Timeout) != HAL_OK)  
      { 
        /* Disable the CRYP peripheral clock */
        __HAL_CRYP_DISABLE(hcryp);
        
        /* Change state */
        hcryp->ErrorCode |= HAL_CRYP_ERROR_TIMEOUT;
        hcryp->State = HAL_CRYP_STATE_READY;  
        
        /* Process unlocked */          
        __HAL_UNLOCK(hcryp); 
        return HAL_ERROR;
      }          
    }     
    /* Wait until the complete message has been processed */
    if(CRYP_WaitOnBUSYFlag(hcryp, Timeout) != HAL_OK)  
    { 
      /* Disable the CRYP peripheral clock */
      __HAL_CRYP_DISABLE(hcryp);
      
      /* Change state */
      hcryp->ErrorCode |= HAL_CRYP_ERROR_TIMEOUT;
      hcryp->State = HAL_CRYP_STATE_READY;  
      
      /* Process unlocked & return error */
      __HAL_UNLOCK(hcryp);          
      return HAL_ERROR;
    }
    
#else /* AES */ 
    
    if(hcryp->Init.Algorithm == CRYP_AES_GCM_GMAC)
    {
      /* Workaround 1 :only AES before re-enabling the IP, datatype can be configured.*/
      MODIFY_REG(hcryp->Instance->CR, AES_CR_DATATYPE, hcryp->Init.DataType); 
      
      /* Select header phase */
      CRYP_SET_PHASE(hcryp, CRYP_PHASE_HEADER);
      
      /* Enable the CRYP peripheral */
      __HAL_CRYP_ENABLE(hcryp);
      
    }
    if ((hcryp->Init.HeaderSize %4U )== 0U)
    {     
      /* HeaderSize %4, no padding */ 
      for(loopcounter = 0U; (loopcounter < hcryp->Init.HeaderSize); loopcounter+= 4U)
      {       
        /* Write the input block in the data input register */
        hcryp->Instance->DINR = *(uint32_t*)(hcryp->Init.Header + hcryp->CrypHeaderCount);
        hcryp->CrypHeaderCount++ ;  
        hcryp->Instance->DINR = *(uint32_t*)(hcryp->Init.Header + hcryp->CrypHeaderCount);
        hcryp->CrypHeaderCount++ ;  
        hcryp->Instance->DINR  = *(uint32_t*)(hcryp->Init.Header + hcryp->CrypHeaderCount);
        hcryp->CrypHeaderCount++ ;  
        hcryp->Instance->DINR = *(uint32_t*)(hcryp->Init.Header + hcryp->CrypHeaderCount);
        hcryp->CrypHeaderCount++ ;  
        
        if(CRYP_WaitOnCCFlag(hcryp, Timeout) != HAL_OK)  
        { 
          /* Disable the CRYP peripheral clock */
          __HAL_CRYP_DISABLE(hcryp);
          
          /* Change state */
          hcryp->ErrorCode |= HAL_CRYP_ERROR_TIMEOUT;
          hcryp->State = HAL_CRYP_STATE_READY;  
          
          /* Process unlocked */          
          __HAL_UNLOCK(hcryp); 
          return HAL_ERROR;
        }
        /* Clear CCF flag */
        __HAL_CRYP_CLEAR_FLAG(hcryp, CRYP_CCF_CLEAR);         
      }
    }
    else
    {   
      /*Write header block in the IN FIFO without last block */
      for(loopcounter = 0U; (loopcounter < ((hcryp->Init.HeaderSize)-(hcryp->Init.HeaderSize %4U ))); loopcounter+=4U)
      {
        /* Write the input block in the data input register */
        hcryp->Instance->DINR = *(uint32_t*)(hcryp->Init.Header + hcryp->CrypHeaderCount);
        hcryp->CrypHeaderCount++ ;  
        hcryp->Instance->DINR = *(uint32_t*)(hcryp->Init.Header + hcryp->CrypHeaderCount);
        hcryp->CrypHeaderCount++ ;  
        hcryp->Instance->DINR  = *(uint32_t*)(hcryp->Init.Header + hcryp->CrypHeaderCount);
        hcryp->CrypHeaderCount++ ;  
        hcryp->Instance->DINR = *(uint32_t*)(hcryp->Init.Header + hcryp->CrypHeaderCount);
        hcryp->CrypHeaderCount++ ; 
        
        if(CRYP_WaitOnCCFlag(hcryp, Timeout) != HAL_OK)  
        { 
          /* Disable the CRYP peripheral clock */
          __HAL_CRYP_DISABLE(hcryp);
          
          /* Change state */
          hcryp->ErrorCode |= HAL_CRYP_ERROR_TIMEOUT;
          hcryp->State = HAL_CRYP_STATE_READY;
          
          /* Process unlocked */          
          __HAL_UNLOCK(hcryp); 
          return HAL_ERROR;
        }
        /* Clear CCF flag */
        __HAL_CRYP_CLEAR_FLAG(hcryp, CRYP_CCF_CLEAR);    
      }
      /*  Last block optionally pad the data with zeros*/
      for(loopcounter = 0U; (loopcounter < (hcryp->Init.HeaderSize %4U )); loopcounter++)
      {
        hcryp->Instance->DINR = *(uint32_t*)(hcryp->Init.Header + hcryp->CrypHeaderCount);
        hcryp->CrypHeaderCount++ ;       
      }
      while(loopcounter < 4U )
      { 
        /*Pad the data with zeros to have a complete block */      
        hcryp->Instance->DINR = 0x0U;              
        loopcounter++;
      }    
      
      if(CRYP_WaitOnCCFlag(hcryp, Timeout) != HAL_OK)  
      { 
        /* Disable the CRYP peripheral clock */
        __HAL_CRYP_DISABLE(hcryp);
        
        /* Change state */
        hcryp->ErrorCode |= HAL_CRYP_ERROR_TIMEOUT;
        hcryp->State = HAL_CRYP_STATE_READY; 
        
        /* Process unlocked */          
        __HAL_UNLOCK(hcryp); 
        return HAL_ERROR;
      }
      /* Clear CCF flag */
      __HAL_CRYP_CLEAR_FLAG(hcryp, CRYP_CCF_CLEAR);  
    }      
#endif /* End AES or CRYP */ 
  }
  else
  {
#if defined(AES) 
    if(hcryp->Init.Algorithm == CRYP_AES_GCM_GMAC)
    { 
      /*Workaround 1: only AES, before re-enabling the IP, datatype can be configured.*/
      MODIFY_REG(hcryp->Instance->CR, AES_CR_DATATYPE, hcryp->Init.DataType); 
      
      /* Select header phase */
      CRYP_SET_PHASE(hcryp, CRYP_PHASE_HEADER); 
      
      /* Enable the CRYP peripheral */
      __HAL_CRYP_ENABLE(hcryp);
    }
#endif /* AES */     
  }
  /* Return function status */
  return HAL_OK;
}

/**
  * @brief  Sets the header phase when using DMA in process
  * @param  hcryp: pointer to a CRYP_HandleTypeDef structure that contains
  *         the configuration information for CRYP module(Header & HeaderSize)  
  * @retval None
  */
static HAL_StatusTypeDef CRYP_GCMCCM_SetHeaderPhase_DMA(CRYP_HandleTypeDef *hcryp)
{
  __IO uint32_t count  = 0U;
  uint32_t loopcounter;
  
  /***************************** Header phase for GCM/GMAC or CCM *********************************/  
  if((hcryp->Init.HeaderSize != 0U))
  {
    
#if defined(CRYP)  
    
    /* Select header phase */
    CRYP_SET_PHASE(hcryp, CRYP_PHASE_HEADER); 
    
    /* Enable the CRYP peripheral */
    __HAL_CRYP_ENABLE(hcryp);    
    
    if ((hcryp->Init.HeaderSize %4U )== 0U)
    { 
      /* HeaderSize %4, no padding */ 
      for(loopcounter = 0U; (loopcounter < hcryp->Init.HeaderSize); loopcounter+=4U)
      {      
        hcryp->Instance->DIN = *(uint32_t*)(hcryp->Init.Header + hcryp->CrypHeaderCount);
        hcryp->CrypHeaderCount++ ;
        hcryp->Instance->DIN = *(uint32_t*)(hcryp->Init.Header + hcryp->CrypHeaderCount);
        hcryp->CrypHeaderCount++ ;
        hcryp->Instance->DIN = *(uint32_t*)(hcryp->Init.Header + hcryp->CrypHeaderCount);
        hcryp->CrypHeaderCount++ ;
        hcryp->Instance->DIN = *(uint32_t*)(hcryp->Init.Header + hcryp->CrypHeaderCount);
        hcryp->CrypHeaderCount++ ;
        
        /* Wait for IFEM to be raised */
        count = CRYP_TIMEOUT_GCMCCMHEADERPHASE;
        do
        {
          count-- ;
          if(count == 0U)
          {
            /* Disable the CRYP peripheral clock */
            __HAL_CRYP_DISABLE(hcryp);
            
            /* Change state */
            hcryp->ErrorCode |= HAL_CRYP_ERROR_TIMEOUT;
            hcryp->State = HAL_CRYP_STATE_READY;
            
            /* Process unlocked */          
            __HAL_UNLOCK(hcryp); 
            return HAL_ERROR;
          }
        }
        while(HAL_IS_BIT_CLR(hcryp->Instance->SR, CRYP_FLAG_IFEM));        
      }
    }
    else
    {   
      /*Write header block in the IN FIFO without last block */
      for(loopcounter = 0U; (loopcounter < ((hcryp->Init.HeaderSize)-(hcryp->Init.HeaderSize %4U ))); loopcounter+=4U)
      {    
        hcryp->Instance->DIN = *(uint32_t*)(hcryp->Init.Header + hcryp->CrypHeaderCount);
        hcryp->CrypHeaderCount++ ;
        hcryp->Instance->DIN = *(uint32_t*)(hcryp->Init.Header + hcryp->CrypHeaderCount);
        hcryp->CrypHeaderCount++ ;
        hcryp->Instance->DIN = *(uint32_t*)(hcryp->Init.Header + hcryp->CrypHeaderCount);
        hcryp->CrypHeaderCount++ ; 
        hcryp->Instance->DIN = *(uint32_t*)(hcryp->Init.Header + hcryp->CrypHeaderCount);
        hcryp->CrypHeaderCount++ ;
        
        /* Wait for IFEM to be raised */
        count = CRYP_TIMEOUT_GCMCCMHEADERPHASE;
        do
        {
          count-- ;
          if(count == 0U)
          {
            /* Disable the CRYP peripheral clock */
            __HAL_CRYP_DISABLE(hcryp);
            
            /* Change state */
            hcryp->ErrorCode |= HAL_CRYP_ERROR_TIMEOUT;
            hcryp->State = HAL_CRYP_STATE_READY;  
            
            /* Process unlocked */          
            __HAL_UNLOCK(hcryp); 
            return HAL_ERROR;
          }
        }
        while(HAL_IS_BIT_CLR(hcryp->Instance->SR, CRYP_FLAG_IFEM)); 
      }
      /*  Last block optionally pad the data with zeros*/
      for(loopcounter = 0U; (loopcounter < (hcryp->Init.HeaderSize %4U )); loopcounter++)
      {
        hcryp->Instance->DIN = *(uint32_t*)(hcryp->Init.Header + hcryp->CrypHeaderCount);
        hcryp->CrypHeaderCount++ ;    
      }
      while(loopcounter < 4U )
      { 
        /* Pad the data with zeros to have a complete block */     
        hcryp->Instance->DIN = 0x0U;         
        loopcounter++;
      }
      /* Wait for IFEM to be raised */
      count = CRYP_TIMEOUT_GCMCCMHEADERPHASE;
      do
      {
        count-- ;
        if(count == 0U)
        {
          /* Disable the CRYP peripheral clock */
          __HAL_CRYP_DISABLE(hcryp);
          
          /* Change state */
          hcryp->ErrorCode |= HAL_CRYP_ERROR_TIMEOUT;
          hcryp->State = HAL_CRYP_STATE_READY; 
          
          /* Process unlocked */          
          __HAL_UNLOCK(hcryp); 
          return HAL_ERROR;
        }
      }
      while(HAL_IS_BIT_CLR(hcryp->Instance->SR, CRYP_FLAG_IFEM));         
    }     
    /* Wait until the complete message has been processed */
    count = CRYP_TIMEOUT_GCMCCMHEADERPHASE;
    do
    {
      count-- ;
      if(count == 0U)
      {
        /* Disable the CRYP peripheral clock */
        __HAL_CRYP_DISABLE(hcryp);
        
        /* Change state */
        hcryp->ErrorCode |= HAL_CRYP_ERROR_TIMEOUT;
        hcryp->State = HAL_CRYP_STATE_READY; 
        
        /* Process unlocked */          
        __HAL_UNLOCK(hcryp); 
        return HAL_ERROR;
      }
    }
    while(HAL_IS_BIT_SET(hcryp->Instance->SR, CRYP_FLAG_BUSY));     
    
#else /* AES */ 
    
    if(hcryp->Init.Algorithm == CRYP_AES_GCM_GMAC)
    {
      /* Workaround 1: only AES, before re-enabling the IP, datatype can be configured.*/
      MODIFY_REG(hcryp->Instance->CR, AES_CR_DATATYPE, hcryp->Init.DataType); 
      
      /* Select header phase */
      CRYP_SET_PHASE(hcryp, CRYP_PHASE_HEADER); 
      
      /* Enable the CRYP peripheral */
      __HAL_CRYP_ENABLE(hcryp);
    }
    if ((hcryp->Init.HeaderSize %4U )== 0U)
    {     
      /* HeaderSize %4, no padding */ 
      for(loopcounter = 0U; (loopcounter < hcryp->Init.HeaderSize); loopcounter+=4U)
      {       
        /* Write the input block in the data input register */
        hcryp->Instance->DINR = *(uint32_t*)(hcryp->Init.Header + hcryp->CrypHeaderCount);
        hcryp->CrypHeaderCount++ ;  
        hcryp->Instance->DINR = *(uint32_t*)(hcryp->Init.Header + hcryp->CrypHeaderCount);
        hcryp->CrypHeaderCount++ ;  
        hcryp->Instance->DINR  = *(uint32_t*)(hcryp->Init.Header + hcryp->CrypHeaderCount);
        hcryp->CrypHeaderCount++ ;  
        hcryp->Instance->DINR = *(uint32_t*)(hcryp->Init.Header + hcryp->CrypHeaderCount);
        hcryp->CrypHeaderCount++ ;  
        
        /*Wait on CCF flag*/ 
        count = CRYP_TIMEOUT_GCMCCMHEADERPHASE;
        do
        {
          count-- ;
          if(count == 0U)
          {
            /* Disable the CRYP peripheral clock */
            __HAL_CRYP_DISABLE(hcryp);
            
            /* Change state */
            hcryp->ErrorCode |= HAL_CRYP_ERROR_TIMEOUT;
            hcryp->State = HAL_CRYP_STATE_READY; 
            
            /* Process unlocked */          
            __HAL_UNLOCK(hcryp); 
            return HAL_ERROR;
          }
        }
        while(HAL_IS_BIT_CLR(hcryp->Instance->SR, AES_SR_CCF));
        
        /* Clear CCF flag */
        __HAL_CRYP_CLEAR_FLAG(hcryp, CRYP_CCF_CLEAR);         
      }
    }
    else
    {   
      /*Write header block in the IN FIFO without last block */
      for(loopcounter = 0U; (loopcounter < ((hcryp->Init.HeaderSize)-(hcryp->Init.HeaderSize %4U ))); loopcounter+=4U)
      {
        /* Write the Input block in the Data Input register */
        hcryp->Instance->DINR = *(uint32_t*)(hcryp->Init.Header + hcryp->CrypHeaderCount);
        hcryp->CrypHeaderCount++ ;  
        hcryp->Instance->DINR = *(uint32_t*)(hcryp->Init.Header + hcryp->CrypHeaderCount);
        hcryp->CrypHeaderCount++ ;  
        hcryp->Instance->DINR  = *(uint32_t*)(hcryp->Init.Header + hcryp->CrypHeaderCount);
        hcryp->CrypHeaderCount++ ;  
        hcryp->Instance->DINR = *(uint32_t*)(hcryp->Init.Header + hcryp->CrypHeaderCount);
        hcryp->CrypHeaderCount++ ; 
        
        /*Wait on CCF flag*/ 
        count = CRYP_TIMEOUT_GCMCCMHEADERPHASE;
        do
        {
          count-- ;
          if(count == 0U)
          {
            /* Disable the CRYP peripheral clock */
            __HAL_CRYP_DISABLE(hcryp);
            
            /* Change state */
            hcryp->ErrorCode |= HAL_CRYP_ERROR_TIMEOUT;
            hcryp->State = HAL_CRYP_STATE_READY; 
            
            /* Process unlocked */          
            __HAL_UNLOCK(hcryp); 
            return HAL_ERROR;
          }
        }
        while(HAL_IS_BIT_CLR(hcryp->Instance->SR, AES_SR_CCF));
        
        /* Clear CCF flag */
        __HAL_CRYP_CLEAR_FLAG(hcryp, CRYP_CCF_CLEAR);    
      }
      /*  Last block optionally pad the data with zeros*/
      for(loopcounter = 0U; (loopcounter < (hcryp->Init.HeaderSize %4U )); loopcounter++)
      {
        hcryp->Instance->DINR = *(uint32_t*)(hcryp->Init.Header + hcryp->CrypHeaderCount);
        hcryp->CrypHeaderCount++ ;       
      }
      while(loopcounter <4U )
      { 
        /* Pad the data with zeros to have a complete block */      
        hcryp->Instance->DINR = 0x0U;              
        loopcounter++;
      }    
      
      /*Wait on CCF flag*/ 
      count = CRYP_TIMEOUT_GCMCCMHEADERPHASE;
      do
      {
        count-- ;
        if(count == 0U)
        {
          /* Disable the CRYP peripheral clock */
          __HAL_CRYP_DISABLE(hcryp);
          
          /* Change state */
          hcryp->ErrorCode |= HAL_CRYP_ERROR_TIMEOUT;
          hcryp->State = HAL_CRYP_STATE_READY;
          
          /* Process unlocked */          
          __HAL_UNLOCK(hcryp); 
          return HAL_ERROR;
        }
      }
      while(HAL_IS_BIT_CLR(hcryp->Instance->SR, AES_SR_CCF));
      
      /* Clear CCF flag */
      __HAL_CRYP_CLEAR_FLAG(hcryp, CRYP_CCF_CLEAR);  
    }      
#endif /* End AES or CRYP  */ 
  }
  else
  {
#if defined(AES) 
    if(hcryp->Init.Algorithm == CRYP_AES_GCM_GMAC)
    { 
      /*Workaround 1: only AES, before re-enabling the IP, datatype can be configured.*/
      MODIFY_REG(hcryp->Instance->CR, AES_CR_DATATYPE, hcryp->Init.DataType); 
      
      /* Select header phase */
      CRYP_SET_PHASE(hcryp, CRYP_PHASE_HEADER); 
      
      /* Enable the CRYP peripheral */
      __HAL_CRYP_ENABLE(hcryp);
    }
#endif /* AES */     
  }
  /* Return function status */
  return HAL_OK;
}

/**
  * @brief  Sets the header phase in interrupt mode
  * @param  hcryp: pointer to a CRYP_HandleTypeDef structure that contains
  *         the configuration information for CRYP module(Header & HeaderSize)
  * @retval None
  */
static void CRYP_GCMCCM_SetHeaderPhase_IT(CRYP_HandleTypeDef *hcryp)
{
  uint32_t loopcounter;
#if defined(AES) 
  uint32_t lastwordsize; 
  uint32_t npblb;	
#endif 
  /***************************** Header phase *********************************/
  
#if defined(CRYP)  
  if(hcryp->Init.HeaderSize ==  hcryp->CrypHeaderCount)
  {     
    /* Disable interrupts */
    __HAL_CRYP_DISABLE_IT(hcryp, CRYP_IT_INI );
    
    /* Disable the CRYP peripheral */
    __HAL_CRYP_DISABLE(hcryp);
    
    /* Set the phase */
    hcryp->Phase = CRYP_PHASE_PROCESS;
    
    /* Select payload phase once the header phase is performed */
    CRYP_SET_PHASE(hcryp, CRYP_PHASE_PAYLOAD); 
    
    /* Enable Interrupts */
    __HAL_CRYP_ENABLE_IT(hcryp, CRYP_IT_INI | CRYP_IT_OUTI );
    
    /* Enable the CRYP peripheral */
    __HAL_CRYP_ENABLE(hcryp);  
  }    
  else if (((hcryp->Init.HeaderSize) - (hcryp->CrypHeaderCount)) >= 4U)
    
  { /* HeaderSize %4, no padding */     
    hcryp->Instance->DIN = *(uint32_t*)(hcryp->Init.Header + hcryp->CrypHeaderCount );
    hcryp->CrypHeaderCount++ ;       
    hcryp->Instance->DIN = *(uint32_t*)(hcryp->Init.Header + hcryp->CrypHeaderCount);
    hcryp->CrypHeaderCount++  ;       
    hcryp->Instance->DIN = *(uint32_t*)(hcryp->Init.Header + hcryp->CrypHeaderCount);
    hcryp->CrypHeaderCount++ ;
    hcryp->Instance->DIN = *(uint32_t*)(hcryp->Init.Header + hcryp->CrypHeaderCount);
    hcryp->CrypHeaderCount++ ;           
  }
  else
  {      
    /*  Last block optionally pad the data with zeros*/
    for(loopcounter = 0U; loopcounter < (hcryp->Init.HeaderSize %4U ); loopcounter++)
    {
      hcryp->Instance->DIN = *(uint32_t*)(hcryp->Init.Header+ hcryp->CrypHeaderCount);    
      hcryp->CrypHeaderCount++ ;
    }
    while(loopcounter <4U )
    { 
      /* Pad the data with zeros to have a complete block */     
      hcryp->Instance->DIN = 0x0U;         
      loopcounter++;
    }         
  }          
#else /* AES */  
  
  if(hcryp->Init.HeaderSize ==  hcryp->CrypHeaderCount)
  {
    /* Set the phase */
    hcryp->Phase = CRYP_PHASE_PROCESS;
    
    /*  Payload phase not supported in CCM AES2  */
    if(hcryp->Init.Algorithm == CRYP_AES_GCM_GMAC)
    {
      /* Select payload phase once the header phase is performed */
      MODIFY_REG(hcryp->Instance->CR, AES_CR_GCMPH, CRYP_PHASE_PAYLOAD);
    }    
    if(hcryp->Init.Algorithm == CRYP_AES_CCM)
    {
      /* Increment CrypHeaderCount to pass in CRYP_GCMCCM_SetPayloadPhase_IT */
      hcryp->CrypHeaderCount++;    
    }            
    /* Write the payload Input block in the IN FIFO */ 
    if(hcryp->Size == 0U)
    {     
      /* Disable interrupts */
      __HAL_CRYP_DISABLE_IT(hcryp, CRYP_IT_CCFIE| CRYP_IT_ERRIE);
      
      /* Change the CRYP state */
      hcryp->State = HAL_CRYP_STATE_READY;
      
      /* Process unlocked */
      __HAL_UNLOCK(hcryp);
    }            
    else if (hcryp->Size >= 16U)
    {       
      hcryp->Instance->DINR  = *(uint32_t *)(hcryp->pCrypInBuffPtr + hcryp->CrypInCount );
      hcryp->CrypInCount++;
      hcryp->Instance->DINR  = *(uint32_t *)(hcryp->pCrypInBuffPtr + hcryp->CrypInCount );
      hcryp->CrypInCount++;   
      hcryp->Instance->DINR  = *(uint32_t *)(hcryp->pCrypInBuffPtr + hcryp->CrypInCount );
      hcryp->CrypInCount++;
      hcryp->Instance->DINR  = *(uint32_t *)(hcryp->pCrypInBuffPtr + hcryp->CrypInCount );
      hcryp->CrypInCount++;
      
      if((hcryp->CrypInCount ==  (hcryp->Size/4U)) &&((hcryp->Size %16U )== 0U))       
      {    
        /* Call the input data transfer complete callback */
#if (USE_HAL_CRYP_REGISTER_CALLBACKS == 1) 
        /*Call registered Input complete callback*/
        hcryp->InCpltCallback(hcryp);
#else
        /*Call legacy weak Input complete callback*/
        HAL_CRYP_InCpltCallback(hcryp);
#endif /* USE_HAL_CRYP_REGISTER_CALLBACKS */
      } 
    }
    else /* Size < 4 words  : first block is the last block*/
    {
      /* Workaround not implemented, Size should be %4  otherwise Tag will  be incorrectly
      generated for GCM Encryption. Workaround is implemented in polling mode, so if last block of 
      payload <128bit don't use CRYP_Encrypt_IT otherwise TAG is incorrectly generated for GCM Encryption. */
      
      /* Compute the number of padding bytes in last block of payload */
      npblb = ((((uint32_t)(hcryp->Size)/16U)+1U)*16U) - (uint32_t)(hcryp->Size);
      
      /* Number of valid words (lastwordsize) in last block */
      if ((npblb % 4U) ==0U) 
      { 
        lastwordsize = (16U-npblb)/4U;		
      }
      else 
      {
        lastwordsize = ((16U-npblb)/4U) +1U;
      }	
      
      /*  Last block optionally pad the data with zeros*/
      for(loopcounter = 0U; loopcounter < lastwordsize; loopcounter++)
      {
        hcryp->Instance->DINR = *(uint32_t *)(hcryp->pCrypInBuffPtr + hcryp->CrypInCount );
        hcryp->CrypInCount++;
      }
      while(loopcounter <4U )
      { 
        /* Pad the data with zeros to have a complete block */     
        hcryp->Instance->DINR = 0x0U;         
        loopcounter++;
      }
    }
  }  
  else if (((hcryp->Init.HeaderSize) - (hcryp->CrypHeaderCount)) >= 4U)
  { 
    /* Write the input block in the IN FIFO */
    hcryp->Instance->DINR  = *(uint32_t *)(hcryp->Init.Header + hcryp->CrypHeaderCount );
    hcryp->CrypHeaderCount++;
    hcryp->Instance->DINR  = *(uint32_t *)(hcryp->Init.Header + hcryp->CrypHeaderCount );
    hcryp->CrypHeaderCount++;   
    hcryp->Instance->DINR  = *(uint32_t *)(hcryp->Init.Header + hcryp->CrypHeaderCount );
    hcryp->CrypHeaderCount++;
    hcryp->Instance->DINR  = *(uint32_t *)(hcryp->Init.Header + hcryp->CrypHeaderCount );
    hcryp->CrypHeaderCount++;         
  }
  else /*HeaderSize < 4 or HeaderSize >4 & HeaderSize %4 != 0*/
  { 
    /*  Last block optionally pad the data with zeros*/
    for(loopcounter = 0U; loopcounter < (hcryp->Init.HeaderSize %4U ); loopcounter++)
    {
      hcryp->Instance->DINR = *(uint32_t*)(hcryp->Init.Header + hcryp->CrypHeaderCount);   
      hcryp->CrypHeaderCount++ ;
    }
    while(loopcounter <4U )
    { 
      /* pad the data with zeros to have a complete block */     
      hcryp->Instance->DINR = 0x0U;         
      loopcounter++;
    }
  }      
#endif /* End AES or CRYP */ 
}           


/**
  * @brief  Workaround used for GCM/CCM mode. 
  * @param  hcryp: pointer to a CRYP_HandleTypeDef structure that contains
  *         the configuration information for CRYP module
  * @param  Timeout: specify Timeout value 
  * @retval None
  */
static void CRYP_Workaround(CRYP_HandleTypeDef *hcryp, uint32_t Timeout )
{
  uint32_t lastwordsize;
  uint32_t npblb;	  
#if defined(CRYP) 
  uint32_t  iv1temp;
  uint32_t  temp[4] = {0};
  uint32_t  temp2[4]= {0};
#endif /* CRYP */
  uint32_t intermediate_data[4]={0};
  uint32_t index;
  
  /* Compute the number of padding bytes in last block of payload */ 
  npblb = ((((uint32_t)(hcryp->Size)/16U)+1U)*16U)- (uint32_t)(hcryp->Size);
  
  /* Number of valid words (lastwordsize) in last block */
  if ((npblb%4U) ==0U) 
  { lastwordsize = (16U-npblb)/4U;		
  }
  else 
  {lastwordsize = ((16U-npblb)/4U) +1U;
  }
  
#if defined(CRYP)    	
  
  /* Workaround 2, case GCM encryption */
  if (hcryp->Init.Algorithm == CRYP_AES_GCM)
  {
    if((hcryp->Instance->CR & CRYP_CR_ALGODIR) == CRYP_OPERATINGMODE_ENCRYPT)
    {/*Workaround in order to properly compute authentication tags while doing
      a GCM encryption with the last block of payload size inferior to 128 bits*/
      /* Disable CRYP to start the final phase */
      __HAL_CRYP_DISABLE(hcryp);
      
      /*Load CRYP_IV1R register content in a temporary variable. Decrement the value
      by 1 and reinsert the result in CRYP_IV1R register*/
      hcryp->Instance->IV1RR = 0x5U;
      MODIFY_REG(hcryp->Instance->CR, CRYP_CR_ALGOMODE, CRYP_AES_CTR); 
      
      /* Enable CRYP to start the final phase */
      __HAL_CRYP_ENABLE(hcryp);
    }
    /*  Last block optionally pad the data with zeros*/    
    for(index=0; index < lastwordsize; index ++)        
    {
      /* Write the last input block in the IN FIFO */
      hcryp->Instance->DIN  = *(uint32_t *)(hcryp->pCrypInBuffPtr + hcryp->CrypInCount );
      hcryp->CrypInCount++;
    }    
    while(index < 4U)
    {
      /* Pad the data with zeros to have a complete block */
      hcryp->Instance->DIN  = 0U;
      index++; 
    }   
    /* Wait for OFNE flag to be raised */
    if(CRYP_WaitOnOFNEFlag(hcryp, Timeout) != HAL_OK)  
    { 
      /* Disable the CRYP peripheral clock */
      __HAL_CRYP_DISABLE(hcryp);
      
      /* Change state */
      hcryp->ErrorCode |= HAL_CRYP_ERROR_TIMEOUT;
      hcryp->State = HAL_CRYP_STATE_READY;  
      
      /* Process Unlocked */          
      __HAL_UNLOCK(hcryp); 
#if (USE_HAL_CRYP_REGISTER_CALLBACKS == 1) 
      /*Call registered error callback*/
      hcryp->ErrorCallback(hcryp);
#else
      /*Call legacy weak error callback*/
      HAL_CRYP_ErrorCallback(hcryp);
#endif /* USE_HAL_CRYP_REGISTER_CALLBACKS */ 
    }    
    if((hcryp->Instance->SR & CRYP_FLAG_OFNE ) != 0x0U)
    {
      for(index=0U; index< 4U;index++)        
      { 
        /* Read the output block from the output FIFO */
        intermediate_data[index] = hcryp->Instance->DOUT; 
        
        /* Intermediate data buffer to be used in for the workaround*/
        *(uint32_t *)(hcryp->pCrypOutBuffPtr + (hcryp->CrypOutCount))=intermediate_data[index];
        hcryp->CrypOutCount++;   
      }     
    }  
    
    if((hcryp->Instance->CR & CRYP_CR_ALGODIR) == CRYP_OPERATINGMODE_ENCRYPT)
    {
      /*workaround in order to properly compute authentication tags while doing
      a GCM encryption with the last block of payload size inferior to 128 bits*/
      /* Change the AES mode to GCM mode and Select Final phase */
      /* configured  CHMOD GCM   */
      MODIFY_REG(hcryp->Instance->CR, CRYP_CR_ALGOMODE, CRYP_AES_GCM); 
      
      /* configured  final phase  */
      MODIFY_REG(hcryp->Instance->CR, CRYP_CR_GCM_CCMPH, CRYP_PHASE_FINAL); 
      
      for (index=0U; index < lastwordsize; index ++)
      {
        /*Write the intermediate_data in the IN FIFO */
        hcryp->Instance->DIN=intermediate_data[index];
      }    
      while(index < 4U)          
      {
        /* Pad the data with zeros to have a complete block */
        hcryp->Instance->DIN  = 0x0U;
        index++; 
      }      
      /* Wait for OFNE flag to be raised */
      if(CRYP_WaitOnOFNEFlag(hcryp, Timeout) != HAL_OK)  
      { 
        /* Disable the CRYP peripheral clock */
        __HAL_CRYP_DISABLE(hcryp);
        
        /* Change state */
        hcryp->ErrorCode |= HAL_CRYP_ERROR_TIMEOUT;
        hcryp->State = HAL_CRYP_STATE_READY;
        
        /* Process unlocked */          
        __HAL_UNLOCK(hcryp); 
#if (USE_HAL_CRYP_REGISTER_CALLBACKS == 1) 
      /*Call registered error callback*/
      hcryp->ErrorCallback(hcryp);
#else
      /*Call legacy weak error callback*/
      HAL_CRYP_ErrorCallback(hcryp);
#endif /* USE_HAL_CRYP_REGISTER_CALLBACKS */ 
      } 
      
      if((hcryp->Instance->SR & CRYP_FLAG_OFNE ) != 0x0U) 
      {  
        for( index=0U; index< 4U;index++)
        { 
          intermediate_data[index]=hcryp->Instance->DOUT;
        }    
      }
    }
  } /* End of GCM encryption */
  else{    /* Workaround 2, case CCM decryption, in order to properly compute
    authentication tags while doing a CCM decryption with the last block
    of payload size inferior to 128 bits*/
    
    if((hcryp->Instance->CR & CRYP_CR_ALGODIR) == CRYP_OPERATINGMODE_DECRYPT)      
    {
      iv1temp = hcryp->Instance->CSGCMCCM7R; 
      
      /* Disable CRYP to start the final phase */
      __HAL_CRYP_DISABLE(hcryp);
      
      temp[0]=  hcryp->Instance->CSGCMCCM0R;
      temp[1]=  hcryp->Instance->CSGCMCCM1R;
      temp[2]=  hcryp->Instance->CSGCMCCM2R;
      temp[3]=  hcryp->Instance->CSGCMCCM3R;
      
      hcryp->Instance->IV1RR= iv1temp;
      
      /* Configured  CHMOD CTR   */
      MODIFY_REG(hcryp->Instance->CR, CRYP_CR_ALGOMODE, CRYP_AES_CTR);    
      
      /* Enable CRYP to start the final phase */
      __HAL_CRYP_ENABLE(hcryp);
    }
    /*  Last block optionally pad the data with zeros*/ 
    for(index=0; index < lastwordsize; index ++)        
    {
      /* Write the last Input block in the IN FIFO */
      hcryp->Instance->DIN  = *(uint32_t *)(hcryp->pCrypInBuffPtr + hcryp->CrypInCount );
      hcryp->CrypInCount++;
    }    
    while(index < 4U)
    {
      /* Pad the data with zeros to have a complete block */
      hcryp->Instance->DIN  = 0U;
      index++; 
    }
    /* Wait for OFNE flag to be raised */
    if(CRYP_WaitOnOFNEFlag(hcryp, Timeout) != HAL_OK)  
    { 
      /* Disable the CRYP peripheral clock */
      __HAL_CRYP_DISABLE(hcryp);
      
      /* Change state */
      hcryp->ErrorCode |= HAL_CRYP_ERROR_TIMEOUT;
      hcryp->State = HAL_CRYP_STATE_READY; 
      
      /* Process Unlocked */          
      __HAL_UNLOCK(hcryp); 
#if (USE_HAL_CRYP_REGISTER_CALLBACKS == 1U) 
      /*Call registered error callback*/
      hcryp->ErrorCallback(hcryp);
#else
      /*Call legacy weak error callback*/
      HAL_CRYP_ErrorCallback(hcryp);
#endif /* USE_HAL_CRYP_REGISTER_CALLBACKS */ 
    }    
    
    if((hcryp->Instance->SR & CRYP_FLAG_OFNE ) != 0x0U)
    {
      for(index=0U; index< 4U;index++)        
      {  
        /* Read the Output block from the Output FIFO */
        intermediate_data[index] = hcryp->Instance->DOUT; 
        
        /*intermediate data buffer to be used in for the workaround*/
        *(uint32_t *)(hcryp->pCrypOutBuffPtr + (hcryp->CrypOutCount))=intermediate_data[index];
        hcryp->CrypOutCount++;   
      }     
    } 
    
    if((hcryp->Instance->CR & CRYP_CR_ALGODIR) == CRYP_OPERATINGMODE_DECRYPT)      
    {     
      temp2[0]=  hcryp->Instance->CSGCMCCM0R;
      temp2[1]=  hcryp->Instance->CSGCMCCM1R;
      temp2[2]=  hcryp->Instance->CSGCMCCM2R;
      temp2[3]=  hcryp->Instance->CSGCMCCM3R;
      
      /* configured  CHMOD CCM   */
      MODIFY_REG(hcryp->Instance->CR, CRYP_CR_ALGOMODE, CRYP_AES_CCM); 
      
      /* configured  Header phase  */
      MODIFY_REG(hcryp->Instance->CR, CRYP_CR_GCM_CCMPH, CRYP_PHASE_HEADER); 
      
      /*set to zero the bits corresponding to the padded bits*/
      for(index = lastwordsize; index<4U; index ++)        
      {
        intermediate_data[index] =0U;
      }     
      if ((npblb %4U)==1U)
      {
        intermediate_data[lastwordsize-1U] &= 0xFFFFFF00U;
      }
      if ((npblb %4U)==2U)
      {
        intermediate_data[lastwordsize-1U] &= 0xFFFF0000U;
      }
      if ((npblb %4U)==3U)
      {
        intermediate_data[lastwordsize-1U] &= 0xFF000000U;
      }
      for(index=0U; index < 4U ; index ++)        
      {               
        intermediate_data[index] ^=  temp[index];
        intermediate_data[index] ^=  temp2[index]; 
      }
      for(index = 0U; index < 4U; index ++)        
      {
        /* Write the last Input block in the IN FIFO */
        hcryp->Instance->DIN  = intermediate_data[index] ;
      } 
      
      /* Wait for BUSY flag to be raised */
      if(CRYP_WaitOnBUSYFlag(hcryp, Timeout) != HAL_OK)  
      { 
        /* Disable the CRYP peripheral clock */
        __HAL_CRYP_DISABLE(hcryp);
        
        /* Change state */
        hcryp->ErrorCode |= HAL_CRYP_ERROR_TIMEOUT;
        hcryp->State = HAL_CRYP_STATE_READY;
        
        /* Process Unlocked */          
        __HAL_UNLOCK(hcryp);       
#if (USE_HAL_CRYP_REGISTER_CALLBACKS == 1U) 
      /*Call registered error callback*/
      hcryp->ErrorCallback(hcryp);
#else
      /*Call legacy weak error callback*/
      HAL_CRYP_ErrorCallback(hcryp);
#endif /* USE_HAL_CRYP_REGISTER_CALLBACKS */ 
      }
    }
  } /* End of CCM WKA*/  
  
  /* Process Unlocked */
  __HAL_UNLOCK(hcryp); 
  
#else /* AES */
  
  /*Workaround 2: case GCM encryption, during payload phase and before inserting 
  the last block of paylaod, which size is inferior to  128 bits  */   
  
  if((hcryp->Instance->CR & AES_CR_MODE) == CRYP_OPERATINGMODE_ENCRYPT)    
  {
    /* configured  CHMOD CTR   */
    MODIFY_REG(hcryp->Instance->CR, AES_CR_CHMOD, CRYP_AES_CTR);  
  } 
  /*  last block optionally pad the data with zeros*/    
  for(index = 0U; index < lastwordsize; index ++)        
  {
    /* Write the last Input block in the IN FIFO */
    hcryp->Instance->DINR  = *(uint32_t *)(hcryp->pCrypInBuffPtr + hcryp->CrypInCount );
    hcryp->CrypInCount++;
  }    
  while(index < 4U)
  {
    /* pad the data with zeros to have a complete block */
    hcryp->Instance->DINR  = 0U;
    index++; 
  }   
  /* Wait for CCF flag to be raised */
  if(CRYP_WaitOnCCFlag(hcryp, Timeout) != HAL_OK)  
  { 
    hcryp->State = HAL_CRYP_STATE_READY;        
    __HAL_UNLOCK(hcryp);
#if (USE_HAL_CRYP_REGISTER_CALLBACKS == 1U) 
      /*Call registered error callback*/
      hcryp->ErrorCallback(hcryp);
#else
      /*Call legacy weak error callback*/
      HAL_CRYP_ErrorCallback(hcryp);
#endif /* USE_HAL_CRYP_REGISTER_CALLBACKS */ 
  }
  
  /* Clear CCF Flag */
  __HAL_CRYP_CLEAR_FLAG(hcryp, CRYP_CCF_CLEAR);
  
  for(index = 0U; index< 4U;index++)        
  {  
    /* Read the Output block from the Output FIFO */  
    intermediate_data[index] = hcryp->Instance->DOUTR; 
    
    /*intermediate data buffer to be used in  the workaround*/
    *(uint32_t *)(hcryp->pCrypOutBuffPtr + (hcryp->CrypOutCount))= intermediate_data[index];
    hcryp->CrypOutCount++; 
  }  
  
  if((hcryp->Instance->CR & AES_CR_MODE) == CRYP_OPERATINGMODE_ENCRYPT) 
  {    
    /* configured  CHMOD GCM   */
    MODIFY_REG(hcryp->Instance->CR, AES_CR_CHMOD, CRYP_AES_GCM_GMAC);
    
    /* Select final phase */
    MODIFY_REG(hcryp->Instance->CR, AES_CR_GCMPH, CRYP_PHASE_FINAL);       
    
    /*Write the intermediate_data in the IN FIFO */   
    for(index = 0U; index < lastwordsize; index ++)        
    {
      hcryp->Instance->DINR  = intermediate_data[index];
    }    
    while(index < 4U)
    {
      /* pad the data with zeros to have a complete block */
      hcryp->Instance->DINR = 0U;
      index++; 
    }
    /* Wait for CCF flag to be raised */
    if(CRYP_WaitOnCCFlag(hcryp, Timeout) != HAL_OK)  
    { 
      /* Disable the CRYP peripheral clock */
      __HAL_CRYP_DISABLE(hcryp);
      
      /* Change state */
      hcryp->ErrorCode |= HAL_CRYP_ERROR_TIMEOUT;
      hcryp->State = HAL_CRYP_STATE_READY;  
      
      /* Process Unlocked */          
      __HAL_UNLOCK(hcryp); 
#if (USE_HAL_CRYP_REGISTER_CALLBACKS == 1U) 
      /*Call registered error callback*/
      hcryp->ErrorCallback(hcryp);
#else
      /*Call legacy weak error callback*/
      HAL_CRYP_ErrorCallback(hcryp);
#endif /* USE_HAL_CRYP_REGISTER_CALLBACKS */ 
    }      
    /* Clear CCF Flag */
    __HAL_CRYP_CLEAR_FLAG(hcryp, CRYP_CCF_CLEAR);
    
    for( index = 0U; index< 4U;index++)
    { 
      intermediate_data[index]=hcryp->Instance->DOUTR;
    }
  }/*End of Workaround 2*/ 
  
#endif /* End AES or CRYP */      
}

#if defined (CRYP)  

/**
  * @brief  Handle CRYP hardware block Timeout when waiting for IFEM flag to be raised.
  * @param  hcryp: pointer to a CRYP_HandleTypeDef structure that contains
  *         the configuration information for CRYP module.      
  * @param  Timeout: Timeout duration.
  * @retval HAL status
  */
static HAL_StatusTypeDef CRYP_WaitOnIFEMFlag(CRYP_HandleTypeDef *hcryp, uint32_t Timeout)
{
  uint32_t tickstart;
  
  /* Get timeout */
  tickstart = HAL_GetTick();
  
  while(HAL_IS_BIT_CLR(hcryp->Instance->SR, CRYP_FLAG_IFEM))
  {
    /* Check for the Timeout */
    if(Timeout != HAL_MAX_DELAY)
    {
      if(((HAL_GetTick() - tickstart ) > Timeout)||(Timeout == 0U))
      { 
        return HAL_ERROR;
      }
    }
  }  
  return HAL_OK; 
}

/**
  * @brief  Handle CRYP hardware block Timeout when waiting for BUSY flag to be raised.
  * @param  hcryp: pointer to a CRYP_HandleTypeDef structure that contains
  *         the configuration information for CRYP module.      
  * @param  Timeout: Timeout duration.
  * @retval HAL status
  */
static HAL_StatusTypeDef CRYP_WaitOnBUSYFlag(CRYP_HandleTypeDef *hcryp, uint32_t Timeout)
{
  uint32_t tickstart;
  
  /* Get timeout */
  tickstart = HAL_GetTick();
  
  while(HAL_IS_BIT_SET(hcryp->Instance->SR, CRYP_FLAG_BUSY))
  {
    /* Check for the Timeout */
    if(Timeout != HAL_MAX_DELAY)
    {
      if(((HAL_GetTick() - tickstart ) > Timeout)||(Timeout == 0U))
      {      
        return HAL_ERROR;
      }
    }
  }
  return HAL_OK; 
}


/**
  * @brief  Handle CRYP hardware block Timeout when waiting for OFNE flag to be raised.
  * @param  hcryp: pointer to a CRYP_HandleTypeDef structure that contains
  *         the configuration information for CRYP module.      
  * @param  Timeout: Timeout duration.
  * @retval HAL status
  */
static HAL_StatusTypeDef CRYP_WaitOnOFNEFlag(CRYP_HandleTypeDef *hcryp, uint32_t Timeout)
{
  uint32_t tickstart;
  
  /* Get timeout */
  tickstart = HAL_GetTick();
  
  while(HAL_IS_BIT_CLR(hcryp->Instance->SR, CRYP_FLAG_OFNE))
  {
    /* Check for the Timeout */
    if(Timeout != HAL_MAX_DELAY)
    {
      if(((HAL_GetTick() - tickstart ) > Timeout)||(Timeout == 0U))
      {       
        return HAL_ERROR;
      }
    }
  }
  return HAL_OK; 
}

#else /* AES */

/**
  * @brief  Handle CRYP hardware block Timeout when waiting for CCF flag to be raised.
  * @param  hcryp: pointer to a CRYP_HandleTypeDef structure that contains
  *         the configuration information for CRYP module.      
  * @param  Timeout: Timeout duration.
  * @retval HAL status
  */
static HAL_StatusTypeDef CRYP_WaitOnCCFlag(CRYP_HandleTypeDef *hcryp, uint32_t Timeout)
{
  uint32_t tickstart;
  
  /* Get timeout */
  tickstart = HAL_GetTick();
  
  while(HAL_IS_BIT_CLR(hcryp->Instance->SR, AES_SR_CCF))
  {    
    /* Check for the Timeout */
    if(Timeout != HAL_MAX_DELAY)
    {
      if(((HAL_GetTick() - tickstart ) > Timeout)||(Timeout == 0U) )
      {    
        return HAL_ERROR;
      }
    }
  }
  return HAL_OK; 
}

#endif /* End AES or CRYP  */
>>>>>>> 49e424905b5922b07aa7166ec7a0eeb90adf58a8


/**
  * @}
<<<<<<< HEAD
  */

=======
  */ 
  
>>>>>>> 49e424905b5922b07aa7166ec7a0eeb90adf58a8


/**
  * @}
  */

/**
  * @}
  */

<<<<<<< HEAD
#endif /* AES */

#endif /* HAL_CRYP_MODULE_ENABLED */

=======
#endif /* HAL_CRYP_MODULE_ENABLED */


/**
  * @}
  */
#endif /* TinyAES or CRYP*/
/**
  * @}
  */

>>>>>>> 49e424905b5922b07aa7166ec7a0eeb90adf58a8
/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
