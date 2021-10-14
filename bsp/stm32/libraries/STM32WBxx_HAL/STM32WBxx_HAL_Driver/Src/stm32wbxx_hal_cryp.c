/**
  ******************************************************************************
  * @file    stm32wbxx_hal_cryp.c
  * @author  MCD Application Team
  * @brief   CRYP HAL module driver.
  *          This file provides firmware functions to manage the following
  *          functionalities of the Cryptography (CRYP) peripheral:
  *           + Initialization, de-initialization, set config and get config  functions
  *           + AES processing functions
  *           + DMA callback functions
  *           + CRYP IRQ handler management
  *           + Peripheral State functions
  *
  @verbatim
  ==============================================================================
                     ##### How to use this driver #####
  ==============================================================================
    [..]
      The CRYP HAL driver can be used in CRYP or TinyAES peripheral as follows:

      (#)Initialize the CRYP low level resources by implementing the HAL_CRYP_MspInit():
         (##) Enable the CRYP interface clock using __HAL_RCC_CRYP_CLK_ENABLE()or __HAL_RCC_AES_CLK_ENABLE for TinyAES peripheral
         (##) In case of using interrupts (e.g. HAL_CRYP_Encrypt_IT())
             (+++) Configure the CRYP interrupt priority using HAL_NVIC_SetPriority()
             (+++) Enable the CRYP IRQ handler using HAL_NVIC_EnableIRQ()
             (+++) In CRYP IRQ handler, call HAL_CRYP_IRQHandler()
         (##) In case of using DMA to control data transfer (e.g. HAL_CRYP_Encrypt_DMA())
             (+++) Enable the DMAx interface clock using __RCC_DMAx_CLK_ENABLE()
             (+++) Configure and enable two DMA streams one for managing data transfer from
                 memory to peripheral (input stream) and another stream for managing data
                 transfer from peripheral to memory (output stream)
             (+++) Associate the initialized DMA handle to the CRYP DMA handle
                 using  __HAL_LINKDMA()
             (+++) Configure the priority and enable the NVIC for the transfer complete
                 interrupt on the two DMA channels. The output channel should have higher
                 priority than the input channel HAL_NVIC_SetPriority() and HAL_NVIC_EnableIRQ().

      (#)Initialize the CRYP according to the specified parameters :
         (##) The data type: 1-bit, 8-bit, 16-bit or 32-bit.
         (##) The key size: 128, 192 or 256.
         (##) The AlgoMode DES/ TDES Algorithm ECB/CBC or AES Algorithm ECB/CBC/CTR/GCM or CCM.
         (##) The initialization vector (counter). It is not used in ECB mode.
         (##) The key buffer used for encryption/decryption.
             (+++) In some specific configurations, the key is written by the application
                   code out of the HAL scope. In that case, user can still resort to the
                   HAL APIs as usual but must make sure that pKey pointer is set to NULL.
         (##) The DataWidthUnit field. It specifies whether the data length (or the payload length for authentication
               algorithms) is in words or bytes.
         (##) The Header used only in AES GCM and CCM Algorithm for authentication.
         (##) The HeaderSize providing the size of the header buffer in words or bytes, depending upon HeaderWidthUnit field.
         (##) The HeaderWidthUnit field. It specifies whether the header length (for authentication algorithms) is in words or bytes.         
         (##) The B0 block is the first authentication block used only in AES CCM mode.
         (##) The KeyIVConfigSkip used to process several messages in a row (please see more information below).

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

       (#)To process a single message with consecutive calls to HAL_CRYP_Encrypt() or HAL_CRYP_Decrypt()
          without having to configure again the Key or the Initialization Vector between each API call,
          the field KeyIVConfigSkip of the initialization structure must be set to CRYP_KEYIVCONFIG_ONCE.
          Same is true for consecutive calls of HAL_CRYP_Encrypt_IT(), HAL_CRYP_Decrypt_IT(), HAL_CRYP_Encrypt_DMA()
          or HAL_CRYP_Decrypt_DMA().

    [..]
      The cryptographic processor supports following standards:
      (#) The data encryption standard (DES) and Triple-DES (TDES) supported only by CRYP1 peripheral:
         (##)64-bit data block processing
         (##) chaining modes supported :
             (+++)  Electronic Code Book(ECB)
             (+++)  Cipher Block Chaining (CBC)
         (##) keys length supported :64-bit, 128-bit and 192-bit.
      (#) The advanced encryption standard (AES) supported  by CRYP1 & TinyAES peripheral:
         (##)128-bit data block processing
         (##) chaining modes supported :
             (+++)  Electronic Code Book(ECB)
             (+++)  Cipher Block Chaining (CBC)
             (+++)  Counter mode (CTR)
             (+++)  Galois/counter mode (GCM/GMAC)
             (+++)  Counter with Cipher Block Chaining-Message(CCM)
         (##) keys length Supported :
             (+++) for CRYP1 peripheral: 128-bit, 192-bit and 256-bit.
             (+++) for TinyAES peripheral:  128-bit and 256-bit

    [..]
    (@) Specific care must be taken to format the key and the Initialization Vector IV!

    [..] If the key is defined as a 128-bit long array key[127..0] = {b127 ... b0} where
         b127 is the MSB and b0 the LSB, the key must be stored in MCU memory
         (+) as a sequence of words where the MSB word comes first (occupies the
           lowest memory address)
          (++)   address n+0 : 0b b127 .. b120 b119 .. b112 b111 .. b104 b103 .. b96
          (++)   address n+4 : 0b b95 .. b88 b87 .. b80 b79 .. b72 b71 .. b64
          (++)   address n+8 : 0b b63 .. b56 b55 .. b48 b47 .. b40 b39 .. b32
          (++)   address n+C : 0b b31 .. b24 b23 .. b16 b15 .. b8 b7 .. b0
     [..] Hereafter, another illustration when considering a 128-bit long key made of 16 bytes {B15..B0}.
         The 4 32-bit words that make the key must be stored as follows in MCU memory:
          (+)    address n+0 : 0x B15 B14 B13 B12
          (+)    address n+4 : 0x B11 B10 B9 B8
          (+)    address n+8 : 0x B7 B6 B5 B4
          (+)    address n+C : 0x B3 B2 B1 B0
     [..]  which leads to the expected setting
       (+)       AES_KEYR3 = 0x B15 B14 B13 B12
       (+)       AES_KEYR2 = 0x B11 B10 B9 B8
       (+)       AES_KEYR1 = 0x B7 B6 B5 B4
       (+)       AES_KEYR0 = 0x B3 B2 B1 B0

    [..]  Same format must be applied for a 256-bit long key made of 32 bytes {B31..B0}.
          The 8 32-bit words that make the key must be stored as follows in MCU memory:
          (+)    address n+00 : 0x B31 B30 B29 B28
          (+)    address n+04 : 0x B27 B26 B25 B24
          (+)    address n+08 : 0x B23 B22 B21 B20
          (+)    address n+0C : 0x B19 B18 B17 B16
          (+)    address n+10 : 0x B15 B14 B13 B12
          (+)    address n+14 : 0x B11 B10 B9 B8
          (+)    address n+18 : 0x B7 B6 B5 B4
          (+)    address n+1C : 0x B3 B2 B1 B0
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

    [..] Note that key and IV registers are not sensitive to swap mode selection.

    [..]  This section describes the AES Galois/counter mode (GCM) supported by both CRYP1 and TinyAES peripherals:
      (#)  Algorithm supported :
         (##) Galois/counter mode (GCM)
         (##) Galois message authentication code (GMAC) :is exactly the same as
              GCM algorithm composed only by an header.
      (#)  Four phases are performed in GCM :
         (##) Init phase: peripheral prepares the GCM hash subkey (H) and do the IV processing
         (##) Header phase: peripheral processes the Additional Authenticated Data (AAD), with hash
          computation only.
         (##) Payload phase: peripheral processes the plaintext (P) with hash computation + keystream
          encryption + data XORing. It works in a similar way for ciphertext (C).
         (##) Final phase: peripheral generates the authenticated tag (T) using the last block of data.
      (#)  structure of message construction in GCM is defined as below  :
         (##) 16 bytes Initial Counter Block (ICB)composed of IV and counter
         (##) The authenticated header A (also knows as Additional Authentication Data AAD)
          this part of the message is only authenticated, not encrypted.
         (##) The plaintext message P is both authenticated and encrypted as ciphertext.
          GCM standard specifies that ciphertext has same bit length as the plaintext.
         (##) The last block is composed of the length of A (on 64 bits) and the length of ciphertext
          (on 64 bits)

    [..]  A more detailed description of the GCM message structure is available below.

    [..]  This section describe The AES Counter with Cipher Block Chaining-Message
          Authentication Code (CCM) supported by both CRYP1 and TinyAES peripheral:
      (#)  Specific parameters for CCM  :

         (##) B0 block  : follows NIST Special Publication 800-38C,
         (##) B1 block (header)
         (##) CTRx block  : control blocks

    [..]  A detailed description of the CCM message structure is available below.

      (#)  Four phases are performed in CCM for CRYP1 peripheral:
         (##) Init phase: peripheral prepares the GCM hash subkey (H) and do the IV processing
         (##) Header phase: peripheral processes the Additional Authenticated Data (AAD), with hash
          computation only.
         (##) Payload phase: peripheral processes the plaintext (P) with hash computation + keystream
          encryption + data XORing. It works in a similar way for ciphertext (C).
         (##) Final phase: peripheral generates the authenticated tag (T) using the last block of data.
      (#)    CCM in TinyAES peripheral:
         (##) To perform message payload encryption or decryption AES is configured in CTR mode.
         (##) For authentication two phases are performed :
          - Header phase: peripheral processes the Additional Authenticated Data (AAD) first, then the cleartext message
          only cleartext payload (not the ciphertext payload) is used and no outpout.
         (##) Final phase: peripheral generates the authenticated tag (T) using the last block of data.

  *** Callback registration ***
  =============================

  [..]
  The compilation define  USE_HAL_CRYP_REGISTER_CALLBACKS when set to 1
  allows the user to configure dynamically the driver callbacks.
  Use Functions HAL_CRYP_RegisterCallback() or HAL_CRYP_RegisterXXXCallback()
  to register an interrupt callback.

  [..]
  Function HAL_CRYP_RegisterCallback() allows to register following callbacks:
    (+) InCpltCallback     :  Input FIFO transfer completed callback.
    (+) OutCpltCallback    : Output FIFO transfer completed callback.
    (+) ErrorCallback      : callback for error detection.
    (+) MspInitCallback    : CRYP MspInit.
    (+) MspDeInitCallback  : CRYP MspDeInit.
  This function takes as parameters the HAL peripheral handle, the Callback ID
  and a pointer to the user callback function.

  [..]
  Use function HAL_CRYP_UnRegisterCallback() to reset a callback to the default
  weak function.
  HAL_CRYP_UnRegisterCallback() takes as parameters the HAL peripheral handle,
  and the Callback ID.
  This function allows to reset following callbacks:
    (+) InCpltCallback     :  Input FIFO transfer completed callback.
    (+) OutCpltCallback    : Output FIFO transfer completed callback.
    (+) ErrorCallback      : callback for error detection.
    (+) MspInitCallback    : CRYP MspInit.
    (+) MspDeInitCallback  : CRYP MspDeInit.

  [..]
  By default, after the HAL_CRYP_Init() and when the state is HAL_CRYP_STATE_RESET
  all callbacks are set to the corresponding weak functions :
  examples HAL_CRYP_InCpltCallback() , HAL_CRYP_OutCpltCallback().
  Exception done for MspInit and MspDeInit functions that are
  reset to the legacy weak function in the HAL_CRYP_Init()/ HAL_CRYP_DeInit() only when
  these callbacks are null (not registered beforehand).
  if not, MspInit or MspDeInit are not null, the HAL_CRYP_Init() / HAL_CRYP_DeInit()
  keep and use the user MspInit/MspDeInit functions (registered beforehand)

  [..]
  Callbacks can be registered/unregistered in HAL_CRYP_STATE_READY state only.
  Exception done MspInit/MspDeInit callbacks that can be registered/unregistered
  in HAL_CRYP_STATE_READY or HAL_CRYP_STATE_RESET state,
  thus registered (user) MspInit/DeInit callbacks can be used during the Init/DeInit.
  In that case first register the MspInit/MspDeInit user callbacks
  using HAL_CRYP_RegisterCallback() before calling HAL_CRYP_DeInit()
  or HAL_CRYP_Init() function.

  [..]
  When The compilation define USE_HAL_CRYP_REGISTER_CALLBACKS is set to 0 or
  not defined, the callback registration feature is not available and all callbacks
  are set to the corresponding weak functions.


  *** Suspend/Resume feature ***
  ==============================

  [..]
  The compilation define USE_HAL_CRYP_SUSPEND_RESUME when set to 1
  allows the user to resort to the suspend/resume feature.
  A low priority block processing can be suspended to process a high priority block
  instead. When the high priority block processing is over, the low priority block
  processing can be resumed, restarting from the point where it was suspended. This
  feature is applicable only in non-blocking interrupt mode.

  [..] User must resort to HAL_CRYP_Suspend() to suspend the low priority block
  processing. This API manages the hardware block processing suspension and saves all the
  internal data that will be needed to restart later on. Upon HAL_CRYP_Suspend() completion,
  the user can launch the processing of any other block (high priority block processing).

  [..] When the high priority block processing is over, user must invoke HAL_CRYP_Resume()
  to resume the low priority block processing. Ciphering (or deciphering) restarts from
  the suspension point and ends as usual.

  [..] HAL_CRYP_Suspend() reports an error when the suspension request is sent too late
  (i.e when the low priority block processing is about to end). There is no use to
  suspend the tag generation processing for authentication algorithms.

    [..]
    (@) If the key is written out of HAL scope (case pKey pointer set to NULL by the user),
        the block processing suspension/resumption mechanism is NOT applicable.

    [..]
    (@) If the Key and Initialization Vector are configured only once and configuration is
        skipped for consecutive processings (case KeyIVConfigSkip set to CRYP_KEYIVCONFIG_ONCE),
        the block processing suspension/resumption mechanism is NOT applicable.

  @endverbatim
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2019 STMicroelectronics.
  * All rights reserved.</center></h2>
  *
  * This software component is licensed by ST under BSD 3-Clause license,
  * the "License"; You may not use this file except in compliance with the
  * License. You may obtain a copy of the License at:
  *                        opensource.org/licenses/BSD-3-Clause
  *
  ******************************************************************************
  */

/* Includes ------------------------------------------------------------------*/
#include "stm32wbxx_hal.h"

/** @addtogroup STM32WBxx_HAL_Driver
  * @{
  */

/** @addtogroup CRYP
  * @{
  */


#ifdef HAL_CRYP_MODULE_ENABLED

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/** @addtogroup CRYP_Private_Defines
  * @{
  */
#define CRYP_TIMEOUT_KEYPREPARATION      82U         /* The latency of key preparation operation is 82 clock cycles.*/
#define CRYP_TIMEOUT_GCMCCMINITPHASE     299U        /* The latency of  GCM/CCM init phase to prepare hash subkey is 299 clock cycles.*/
#define CRYP_TIMEOUT_GCMCCMHEADERPHASE   290U        /* The latency of  GCM/CCM header phase is 290 clock cycles.*/

#define CRYP_PHASE_READY                 0x00000001U /*!< CRYP peripheral is ready for initialization. */
#define CRYP_PHASE_PROCESS               0x00000002U /*!< CRYP peripheral is in processing phase */
#if (USE_HAL_CRYP_SUSPEND_RESUME == 1U)
#define  CRYP_PHASE_HEADER_SUSPENDED     0x00000004U    /*!< GCM/GMAC/CCM header phase is suspended */
#define  CRYP_PHASE_PAYLOAD_SUSPENDED    0x00000005U    /*!< GCM/CCM payload phase is suspended     */
#endif /* USE_HAL_CRYP_SUSPEND_RESUME */
#define  CRYP_PHASE_HEADER_DMA_FEED      0x00000006U    /*!< GCM/GMAC/CCM header is fed to the peripheral in DMA mode */

#define CRYP_OPERATINGMODE_ENCRYPT                   0x00000000U     /*!< Encryption mode(Mode 1)  */
#define CRYP_OPERATINGMODE_KEYDERIVATION             AES_CR_MODE_0   /*!< Key derivation mode  only used when performing ECB and CBC decryptions (Mode 2) */
#define CRYP_OPERATINGMODE_DECRYPT                   AES_CR_MODE_1   /*!< Decryption    (Mode 3)    */
#define CRYP_OPERATINGMODE_KEYDERIVATION_DECRYPT     AES_CR_MODE     /*!< Key derivation and decryption only used when performing ECB and CBC decryptions (Mode 4) */
#define CRYP_PHASE_INIT                              0x00000000U     /*!< GCM/GMAC (or CCM) init phase */
#define CRYP_PHASE_HEADER                            AES_CR_GCMPH_0  /*!< GCM/GMAC or CCM header phase */
#define CRYP_PHASE_PAYLOAD                           AES_CR_GCMPH_1  /*!< GCM(/CCM) payload phase      */
#define CRYP_PHASE_FINAL                             AES_CR_GCMPH    /*!< GCM/GMAC or CCM  final phase */

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

#define CRYP_SET_PHASE(__HANDLE__, __PHASE__)   MODIFY_REG((__HANDLE__)->Instance->CR, AES_CR_GCMPH, (uint32_t)(__PHASE__))

/**
  * @}
  */

/* Private struct -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
/** @addtogroup CRYP_Private_Functions
  * @{
  */

static void CRYP_SetDMAConfig(CRYP_HandleTypeDef *hcryp, uint32_t inputaddr, uint16_t Size, uint32_t outputaddr);
static HAL_StatusTypeDef CRYP_SetHeaderDMAConfig(CRYP_HandleTypeDef *hcryp, uint32_t inputaddr, uint16_t Size);
static void CRYP_DMAInCplt(DMA_HandleTypeDef *hdma);
static void CRYP_DMAOutCplt(DMA_HandleTypeDef *hdma);
static void CRYP_DMAError(DMA_HandleTypeDef *hdma);
static void CRYP_SetKey(CRYP_HandleTypeDef *hcryp, uint32_t KeySize);
static void CRYP_AES_IT(CRYP_HandleTypeDef *hcryp);
static HAL_StatusTypeDef CRYP_GCMCCM_SetHeaderPhase(CRYP_HandleTypeDef *hcryp, uint32_t Timeout);
static void CRYP_GCMCCM_SetPayloadPhase_IT(CRYP_HandleTypeDef *hcryp);
static void CRYP_GCMCCM_SetHeaderPhase_IT(CRYP_HandleTypeDef *hcryp);
static HAL_StatusTypeDef CRYP_GCMCCM_SetHeaderPhase_DMA(CRYP_HandleTypeDef *hcryp);
static HAL_StatusTypeDef CRYP_GCMCCM_SetPayloadPhase_DMA(CRYP_HandleTypeDef *hcryp);
static HAL_StatusTypeDef CRYP_AESGCM_Process_DMA(CRYP_HandleTypeDef *hcryp);
static HAL_StatusTypeDef CRYP_AESGCM_Process_IT(CRYP_HandleTypeDef *hcryp);
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
static HAL_StatusTypeDef CRYP_WaitOnCCFlag(CRYP_HandleTypeDef *hcryp, uint32_t Timeout);
static void CRYP_ClearCCFlagWhenHigh(CRYP_HandleTypeDef *hcryp, uint32_t Timeout);
#if (USE_HAL_CRYP_SUSPEND_RESUME == 1U)
static void CRYP_Read_IVRegisters(CRYP_HandleTypeDef *hcryp, uint32_t* Output);
static void CRYP_Write_IVRegisters(CRYP_HandleTypeDef *hcryp, uint32_t* Input);
static void CRYP_Read_SuspendRegisters(CRYP_HandleTypeDef *hcryp, uint32_t* Output);
static void CRYP_Write_SuspendRegisters(CRYP_HandleTypeDef *hcryp, uint32_t* Input);
static void CRYP_Read_KeyRegisters(CRYP_HandleTypeDef *hcryp, uint32_t* Output, uint32_t KeySize);
static void CRYP_Write_KeyRegisters(CRYP_HandleTypeDef *hcryp, uint32_t* Input, uint32_t KeySize);
static void CRYP_PhaseProcessingResume(CRYP_HandleTypeDef *hcryp);
#endif /* USE_HAL_CRYP_SUSPEND_RESUME */


/**
  * @}
  */

/* Exported functions ---------------------------------------------------------*/

/** @addtogroup CRYP_Exported_Functions
  * @{
  */

/** @defgroup CRYP_Exported_Functions_Group1 Initialization and de-initialization functions
  * @brief    Initialization and Configuration functions.
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
          (++) Key size
          (++) Data Type : 32,16, 8 or 1bit
          (++) AlgoMode :
              (+++) for CRYP1 peripheral :
                 ECB and CBC in DES/TDES Standard
                 ECB,CBC,CTR,GCM/GMAC and CCM in AES Standard.
              (+++) for TinyAES2 peripheral, only ECB,CBC,CTR,GCM/GMAC and CCM in AES Standard are supported.
      (+) Get CRYP configuration (HAL_CRYP_GetConfig) from the specified parameters in the CRYP_HandleTypeDef

@endverbatim
  * @{
  */

/**
  * @brief  Initializes the CRYP according to the specified
  *         parameters in the CRYP_ConfigTypeDef and creates the associated handle.
  * @param  hcryp pointer to a CRYP_HandleTypeDef structure that contains
  *         the configuration information for CRYP module
  * @retval HAL status
  */
HAL_StatusTypeDef HAL_CRYP_Init(CRYP_HandleTypeDef *hcryp)
{
  /* Check the CRYP handle allocation */
  if (hcryp == NULL)
  {
    return HAL_ERROR;
  }

  /* Check parameters */
  assert_param(IS_CRYP_KEYSIZE(hcryp->Init.KeySize));
  assert_param(IS_CRYP_DATATYPE(hcryp->Init.DataType));
  assert_param(IS_CRYP_ALGORITHM(hcryp->Init.Algorithm));
  assert_param(IS_CRYP_INIT(hcryp->Init.KeyIVConfigSkip));

#if (USE_HAL_CRYP_REGISTER_CALLBACKS == 1U)
  if (hcryp->State == HAL_CRYP_STATE_RESET)
  {
    /* Allocate lock resource and initialize it */
    hcryp->Lock = HAL_UNLOCKED;

    hcryp->InCpltCallback  = HAL_CRYP_InCpltCallback;  /* Legacy weak InCpltCallback   */
    hcryp->OutCpltCallback = HAL_CRYP_OutCpltCallback; /* Legacy weak OutCpltCallback  */
    hcryp->ErrorCallback   = HAL_CRYP_ErrorCallback;   /* Legacy weak ErrorCallback    */

    if (hcryp->MspInitCallback == NULL)
    {
      hcryp->MspInitCallback = HAL_CRYP_MspInit; /* Legacy weak MspInit  */
    }

    /* Init the low level hardware */
    hcryp->MspInitCallback(hcryp);
  }
#else
  if (hcryp->State == HAL_CRYP_STATE_RESET)
  {
    /* Allocate lock resource and initialize it */
    hcryp->Lock = HAL_UNLOCKED;

    /* Init the low level hardware */
    HAL_CRYP_MspInit(hcryp);
  }
#endif /* (USE_HAL_CRYP_REGISTER_CALLBACKS) */

  /* Set the key size (This bit field is do not care in the DES or TDES modes), data type and Algorithm */
  MODIFY_REG(hcryp->Instance->CR, AES_CR_DATATYPE | AES_CR_KEYSIZE | AES_CR_CHMOD, hcryp->Init.DataType | hcryp->Init.KeySize | hcryp->Init.Algorithm);

  /* Reset Error Code field */
  hcryp->ErrorCode = HAL_CRYP_ERROR_NONE;

  /* Reset peripheral Key and IV configuration flag */
  hcryp->KeyIVConfig = 0U;

  /* Change the CRYP state */
  hcryp->State = HAL_CRYP_STATE_READY;

  /* Set the default CRYP phase */
  hcryp->Phase = CRYP_PHASE_READY;

  /* Return function status */
  return HAL_OK;
}

/**
  * @brief  De-Initializes the CRYP peripheral.
  * @param  hcryp pointer to a CRYP_HandleTypeDef structure that contains
  *         the configuration information for CRYP module
  * @retval HAL status
*/
HAL_StatusTypeDef HAL_CRYP_DeInit(CRYP_HandleTypeDef *hcryp)
{
  /* Check the CRYP handle allocation */
  if (hcryp == NULL)
  {
    return HAL_ERROR;
  }

  /* Set the default CRYP phase */
  hcryp->Phase = CRYP_PHASE_READY;

  /* Reset CrypInCount and CrypOutCount */
  hcryp->CrypInCount = 0;
  hcryp->CrypOutCount = 0;
  hcryp->CrypHeaderCount = 0;

  /* Disable the CRYP peripheral clock */
  __HAL_CRYP_DISABLE(hcryp);

#if (USE_HAL_CRYP_REGISTER_CALLBACKS == 1U)

  if (hcryp->MspDeInitCallback == NULL)
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
  * @param  hcryp pointer to a CRYP_HandleTypeDef structure
  * @param  pConf pointer to a CRYP_ConfigTypeDef structure that contains
  *         the configuration information for CRYP module
  * @retval HAL status
  */
HAL_StatusTypeDef HAL_CRYP_SetConfig(CRYP_HandleTypeDef *hcryp, CRYP_ConfigTypeDef *pConf)
{
  /* Check the CRYP handle allocation */
  if ((hcryp == NULL) || (pConf == NULL))
  {
    return HAL_ERROR;
  }

  /* Check parameters */
  assert_param(IS_CRYP_KEYSIZE(pConf->KeySize));
  assert_param(IS_CRYP_DATATYPE(pConf->DataType));
  assert_param(IS_CRYP_ALGORITHM(pConf->Algorithm));

  if (hcryp->State == HAL_CRYP_STATE_READY)
  {
    /* Change the CRYP state */
    hcryp->State = HAL_CRYP_STATE_BUSY;

    /* Process locked */
    __HAL_LOCK(hcryp);

    /* Set  CRYP parameters  */
    hcryp->Init.DataType        = pConf->DataType;
    hcryp->Init.pKey            = pConf->pKey;
    hcryp->Init.Algorithm       = pConf->Algorithm;
    hcryp->Init.KeySize         = pConf->KeySize;
    hcryp->Init.pInitVect       = pConf->pInitVect;
    hcryp->Init.Header          = pConf->Header;
    hcryp->Init.HeaderSize      = pConf->HeaderSize;
    hcryp->Init.B0              = pConf->B0;
    hcryp->Init.DataWidthUnit   = pConf->DataWidthUnit;
    hcryp->Init.HeaderWidthUnit = pConf->HeaderWidthUnit;
    hcryp->Init.KeyIVConfigSkip = pConf->KeyIVConfigSkip;

    /* Set the key size (This bit field is do not care in the DES or TDES modes), data type and operating mode*/
    MODIFY_REG(hcryp->Instance->CR, AES_CR_DATATYPE | AES_CR_KEYSIZE | AES_CR_CHMOD, hcryp->Init.DataType | hcryp->Init.KeySize | hcryp->Init.Algorithm);

    /*clear error flags*/
    __HAL_CRYP_CLEAR_FLAG(hcryp, CRYP_ERR_CLEAR);

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
  }
}

/**
  * @brief  Get CRYP Configuration parameters in associated handle.
  * @param  pConf pointer to a CRYP_ConfigTypeDef structure
  * @param  hcryp pointer to a CRYP_HandleTypeDef structure that contains
  *         the configuration information for CRYP module
  * @retval HAL status
  */
HAL_StatusTypeDef HAL_CRYP_GetConfig(CRYP_HandleTypeDef *hcryp, CRYP_ConfigTypeDef *pConf)
{
  /* Check the CRYP handle allocation */
  if ((hcryp == NULL) || (pConf == NULL))
  {
    return HAL_ERROR;
  }

  if (hcryp->State == HAL_CRYP_STATE_READY)
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
    pConf->DataWidthUnit   = hcryp->Init.DataWidthUnit;
    pConf->HeaderWidthUnit = hcryp->Init.HeaderWidthUnit;
    pConf->KeyIVConfigSkip = hcryp->Init.KeyIVConfigSkip;

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
  * @brief  DeInitializes CRYP MSP.
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

#if (USE_HAL_CRYP_REGISTER_CALLBACKS == 1U)
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

  if (pCallback == NULL)
  {
    /* Update the error code */
    hcryp->ErrorCode |= HAL_CRYP_ERROR_INVALID_CALLBACK;

    return HAL_ERROR;
  }
  /* Process locked */
  __HAL_LOCK(hcryp);

  if (hcryp->State == HAL_CRYP_STATE_READY)
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
  else if (hcryp->State == HAL_CRYP_STATE_RESET)
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

  if (hcryp->State == HAL_CRYP_STATE_READY)
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
  else if (hcryp->State == HAL_CRYP_STATE_RESET)
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
    hcryp->ErrorCode |= HAL_CRYP_ERROR_INVALID_CALLBACK;;
    /* Return error status */
    status =  HAL_ERROR;
  }

  /* Release Lock */
  __HAL_UNLOCK(hcryp);

  return status;
}
#endif /* USE_HAL_CRYP_REGISTER_CALLBACKS */

#if (USE_HAL_CRYP_SUSPEND_RESUME == 1U)
/**
  * @brief  Request CRYP processing suspension when in interruption mode.
  * @param  hcryp pointer to a CRYP_HandleTypeDef structure that contains
  *         the configuration information for CRYP module.
  * @note   Set the handle field SuspendRequest to the appropriate value so that
  *         the on-going CRYP processing is suspended as soon as the required
  *         conditions are met.
  * @note   HAL_CRYP_ProcessSuspend() can only be invoked when the processing is done
  *         in non-blocking interrupt mode.
  * @note   It is advised not to suspend the CRYP processing when the DMA controller
  *         is managing the data transfer.
  * @retval None
  */
void HAL_CRYP_ProcessSuspend(CRYP_HandleTypeDef *hcryp)
{
  /* Set Handle SuspendRequest field */
  hcryp->SuspendRequest = HAL_CRYP_SUSPEND;
}



/**
  * @brief  CRYP processing suspension and peripheral internal parameters storage.
  * @param  hcryp pointer to a CRYP_HandleTypeDef structure that contains
  *         the configuration information for CRYP module
  * @note   peripheral internal parameters are stored to be readily available when
  *         suspended processing is resumed later on.
  * @retval HAL status
  */
HAL_StatusTypeDef HAL_CRYP_Suspend(CRYP_HandleTypeDef *hcryp)
{
  HAL_CRYP_STATETypeDef state;

  /* Request suspension */
  HAL_CRYP_ProcessSuspend(hcryp);

  do
  {
    state = HAL_CRYP_GetState(hcryp);
  } while ((state != HAL_CRYP_STATE_SUSPENDED) && (state != HAL_CRYP_STATE_READY));

  if (HAL_CRYP_GetState(hcryp) == HAL_CRYP_STATE_READY)
  {
    /* Processing was already over or was about to end. No suspension done */
    return HAL_ERROR;
  }
  else
  {
    /* Suspend Processing */

    /* If authentication algorithms on-going, carry out first saving steps
       before disable the peripheral */
    if ((hcryp->Init.Algorithm == CRYP_AES_GCM_GMAC) || \
         (hcryp->Init.Algorithm == CRYP_AES_CCM))
    {
        /* Save Suspension registers */
        CRYP_Read_SuspendRegisters(hcryp, hcryp->SUSPxR_saved);
        /* Save Key */
        CRYP_Read_KeyRegisters(hcryp, hcryp->Key_saved, hcryp->Init.KeySize);
        /* Save IV */
        CRYP_Read_IVRegisters(hcryp, hcryp->IV_saved);
    }
    /* Disable AES */
    __HAL_CRYP_DISABLE(hcryp);

    /* Save low-priority block CRYP handle parameters */
    hcryp->Init_saved              = hcryp->Init;
    hcryp->pCrypInBuffPtr_saved    = hcryp->pCrypInBuffPtr;
    hcryp->pCrypOutBuffPtr_saved   = hcryp->pCrypOutBuffPtr;
    hcryp->CrypInCount_saved       = hcryp->CrypInCount;
    hcryp->CrypOutCount_saved      = hcryp->CrypOutCount;
    hcryp->Phase_saved             = hcryp->Phase;
    hcryp->State_saved             = hcryp->State;
    hcryp->Size_saved              = ( (hcryp->Init.DataWidthUnit == CRYP_DATAWIDTHUNIT_WORD) ? (hcryp->Size /4U) : hcryp->Size);
    hcryp->SizesSum_saved          = hcryp->SizesSum;
    hcryp->AutoKeyDerivation_saved = hcryp->AutoKeyDerivation;
    hcryp->CrypHeaderCount_saved   = hcryp->CrypHeaderCount;
    hcryp->SuspendRequest          = HAL_CRYP_SUSPEND_NONE;

    if ((hcryp->Init.Algorithm == CRYP_AES_CBC) || \
        (hcryp->Init.Algorithm == CRYP_AES_CTR))
    {
      /* Save Initialisation Vector registers */
      CRYP_Read_IVRegisters(hcryp, hcryp->IV_saved);
    }

    /* Save Control register */
    hcryp->CR_saved = hcryp->Instance->CR;

  }
  return HAL_OK;
}


/**
  * @brief  CRYP processing resumption.
  * @param  hcryp pointer to a CRYP_HandleTypeDef structure that contains
  *         the configuration information for CRYP module
  * @note   Processing restarts at the exact point where it was suspended, based
  *         on the parameters saved at suspension time.
  * @retval HAL status
  */
HAL_StatusTypeDef HAL_CRYP_Resume(CRYP_HandleTypeDef *hcryp)
{
  /* Check the CRYP handle allocation */
  if (hcryp == NULL)
  {
    return HAL_ERROR;
  }

  if (hcryp->State_saved != HAL_CRYP_STATE_SUSPENDED)
  {
    /* CRYP was not suspended */
    return HAL_ERROR;
  }
  else
  {

    /* Restore low-priority block CRYP handle parameters */
    hcryp->Init            = hcryp->Init_saved;
    hcryp->State           = hcryp->State_saved;

    /* Chaining algorithms case */
    if ((hcryp->Init_saved.Algorithm == CRYP_AES_ECB) || \
        (hcryp->Init_saved.Algorithm == CRYP_AES_CBC) || \
        (hcryp->Init_saved.Algorithm == CRYP_AES_CTR))
    {
      /* Restore low-priority block CRYP handle parameters */
      hcryp->AutoKeyDerivation = hcryp->AutoKeyDerivation_saved;

      if ((hcryp->Init.Algorithm == CRYP_AES_CBC) || \
        (hcryp->Init.Algorithm == CRYP_AES_CTR))
      {
        hcryp->Init.pInitVect     = hcryp->IV_saved;
      }
      __HAL_CRYP_DISABLE(hcryp);
      (void) HAL_CRYP_Init(hcryp);
    }
    else    /* Authentication algorithms case */
    {
      /* Restore low-priority block CRYP handle parameters */
      hcryp->Phase           = hcryp->Phase_saved;
      hcryp->CrypHeaderCount = hcryp->CrypHeaderCount_saved;
      hcryp->SizesSum        = hcryp->SizesSum_saved;

      /* Disable AES and write-back SUSPxR registers */;
      __HAL_CRYP_DISABLE(hcryp);
      /* Restore AES Suspend Registers */
      CRYP_Write_SuspendRegisters(hcryp, hcryp->SUSPxR_saved);
      /* Restore Control,  Key and IV Registers, then enable AES */
      hcryp->Instance->CR = hcryp->CR_saved;
      CRYP_Write_KeyRegisters(hcryp, hcryp->Key_saved, hcryp->Init.KeySize);
      CRYP_Write_IVRegisters(hcryp, hcryp->IV_saved);

      /* At the same time, set handle state back to READY to be able to resume the AES calculations
      without the processing APIs returning HAL_BUSY when called. */
      hcryp->State        = HAL_CRYP_STATE_READY;
    }


    /* Resume low-priority block processing under IT */
    hcryp->ResumingFlag = 1U;
    if (READ_BIT(hcryp->CR_saved, AES_CR_MODE) == CRYP_OPERATINGMODE_ENCRYPT)
    {
      if (HAL_CRYP_Encrypt_IT(hcryp, hcryp->pCrypInBuffPtr_saved, hcryp->Size_saved, hcryp->pCrypOutBuffPtr_saved) != HAL_OK)
      {
        return HAL_ERROR;
      }
    }
    else
    {
      if (HAL_CRYP_Decrypt_IT(hcryp, hcryp->pCrypInBuffPtr_saved, hcryp->Size_saved, hcryp->pCrypOutBuffPtr_saved) != HAL_OK)
      {
        return HAL_ERROR;
      }
    }
  }
  return HAL_OK;
}
#endif /* defined (USE_HAL_CRYP_SUSPEND_RESUME) */

/**
  * @}
  */

/** @defgroup CRYP_Exported_Functions_Group2 Encryption Decryption functions
  * @brief    Encryption Decryption functions.
  *
@verbatim
  ==============================================================================
                      ##### Encrypt Decrypt  functions #####
  ==============================================================================
    [..]  This section provides API allowing to Encrypt/Decrypt Data following
          Standard DES/TDES or AES, and Algorithm configured by the user:
      (+) Standard DES/TDES only supported by CRYP1 peripheral, below list of Algorithm supported :
           - Electronic Code Book(ECB)
           - Cipher Block Chaining (CBC)
      (+) Standard AES  supported by CRYP1 peripheral & TinyAES, list of Algorithm supported:
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

/* GCM message structure additional details

                                  ICB
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



                                 GCM last block definition
          +-------------------------------------------------------------------+
          |  Bit[0]   |  Bit[32]           |  Bit[64]  | Bit[96]              |
          |-----------|--------------------|-----------|----------------------|
          |   0x0     | Header length[31:0]|     0x0   | Payload length[31:0] |
          |-----------|--------------------|-----------|----------------------|

*/

/* CCM message blocks description

         (##) B0 block  : According to NIST Special Publication 800-38C,
            The first block B0 is formatted as follows, where l(m) is encoded in
            most-significant-byte first order:

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

              - Q: a bit string representation of the octet length of P (plaintext)
              - q The octet length of the binary representation of the octet length of the payload
              - A nonce (N), n The octet length of the where n+q=15.
              - Flags: most significant octet containing four flags for control information,
              - t The octet length of the MAC.
         (##) B1 block (header) : associated data length(a) concatenated with Associated Data (A)
              the associated data length expressed in bytes (a) defined as below:
            - If 0 < a < 216-28, then it is encoded as [a]16, i.e. two octets
            - If 216-28 < a < 232, then it is encoded as 0xff || 0xfe || [a]32, i.e. six octets
            - If 232 < a < 264, then it is encoded as 0xff || 0xff || [a]64, i.e. ten octets
         (##) CTRx block  : control blocks
            - Generation of CTR1 from first block B0 information :
              equal to B0 with first 5 bits zeroed and most significant bits storing octet
              length of P also zeroed, then incremented by one

                Bit Number    Register           Contents
                ----------   ---------------       -----------
                127 ...96    CRYP_IV1R[31:0]     B0[127:96], where Q length bits are set to 0, except for
                                                 bit 0 that is set to 1
                95  ...64    CRYP_IV1L[31:0]     B0[95:64]
                63 ... 32    CRYP_IV0R[31:0]     B0[63:32]
                31 ... 0     CRYP_IV0L[31:0]     B0[31:0], where flag bits set to 0

            - Generation of CTR0: same as CTR1 with bit[0] set to zero.

*/

/**
  * @brief  Encryption mode.
  * @param  hcryp pointer to a CRYP_HandleTypeDef structure that contains
  *         the configuration information for CRYP module
  * @param  Input Pointer to the input buffer (plaintext)
  * @param  Size Length of the plaintext buffer in bytes or words (depending upon DataWidthUnit field)
  * @param  Output Pointer to the output buffer(ciphertext)
  * @param  Timeout Specify Timeout value
  * @retval HAL status
  */
HAL_StatusTypeDef HAL_CRYP_Encrypt(CRYP_HandleTypeDef *hcryp, uint32_t *Input, uint16_t Size, uint32_t *Output, uint32_t Timeout)
{
  uint32_t algo;
  HAL_StatusTypeDef status;
#ifdef  USE_FULL_ASSERT
  uint32_t algo_assert = (hcryp->Instance->CR) & AES_CR_CHMOD;

  /* Check input buffer size */
  assert_param(IS_CRYP_BUFFERSIZE(algo_assert, hcryp->Init.DataWidthUnit, Size));
#endif

  if (hcryp->State == HAL_CRYP_STATE_READY)
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

    /* Set the operating mode*/
    MODIFY_REG(hcryp->Instance->CR, AES_CR_MODE, CRYP_OPERATINGMODE_ENCRYPT);

    /* algo get algorithm selected */
    algo = hcryp->Instance->CR & AES_CR_CHMOD;

    switch (algo)
    {

      case CRYP_AES_ECB:
      case CRYP_AES_CBC:
      case CRYP_AES_CTR:

        /* AES encryption */
        status = CRYP_AES_Encrypt(hcryp, Timeout);
        break;

      case CRYP_AES_GCM_GMAC:

        /* AES GCM encryption */
        status = CRYP_AESGCM_Process(hcryp, Timeout) ;
        break;

      case CRYP_AES_CCM:

        /* AES CCM encryption */
        status = CRYP_AESCCM_Process(hcryp, Timeout);
        break;

      default:
        hcryp->ErrorCode |= HAL_CRYP_ERROR_NOT_SUPPORTED;
        status = HAL_ERROR;
        break;
    }

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
    status = HAL_ERROR;
  }

  /* Return function status */
  return status;
}

/**
  * @brief  Decryption mode.
  * @param  hcryp pointer to a CRYP_HandleTypeDef structure that contains
  *         the configuration information for CRYP module
  * @param  Input Pointer to the input buffer (ciphertext )
  * @param  Size Length of the plaintext buffer in bytes or words (depending upon DataWidthUnit field)
  * @param  Output Pointer to the output buffer(plaintext)
  * @param  Timeout Specify Timeout value
  * @retval HAL status
  */
HAL_StatusTypeDef HAL_CRYP_Decrypt(CRYP_HandleTypeDef *hcryp, uint32_t *Input, uint16_t Size, uint32_t *Output, uint32_t Timeout)
{
  HAL_StatusTypeDef status;
  uint32_t algo;
#ifdef  USE_FULL_ASSERT
  uint32_t algo_assert = (hcryp->Instance->CR) & AES_CR_CHMOD;

  /* Check input buffer size */
  assert_param(IS_CRYP_BUFFERSIZE(algo_assert, hcryp->Init.DataWidthUnit, Size));
#endif

  if (hcryp->State == HAL_CRYP_STATE_READY)
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

    /* Set Decryption operating mode*/
    MODIFY_REG(hcryp->Instance->CR, AES_CR_MODE, CRYP_OPERATINGMODE_DECRYPT);

    /* algo get algorithm selected */
    algo = hcryp->Instance->CR & AES_CR_CHMOD;

    switch (algo)
    {

      case CRYP_AES_ECB:
      case CRYP_AES_CBC:
      case CRYP_AES_CTR:

        /* AES decryption */
        status = CRYP_AES_Decrypt(hcryp, Timeout);
        break;

      case CRYP_AES_GCM_GMAC:

        /* AES GCM decryption */
        status = CRYP_AESGCM_Process(hcryp, Timeout) ;
        break;

      case CRYP_AES_CCM:

        /* AES CCM decryption */
        status = CRYP_AESCCM_Process(hcryp, Timeout);
        break;

      default:
        hcryp->ErrorCode |= HAL_CRYP_ERROR_NOT_SUPPORTED;
        status = HAL_ERROR;
        break;
    }

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
    status = HAL_ERROR;
  }

  /* Return function status */
  return status;
}

/**
  * @brief  Encryption in interrupt mode.
  * @param  hcryp pointer to a CRYP_HandleTypeDef structure that contains
  *         the configuration information for CRYP module
  * @param  Input Pointer to the input buffer (plaintext)
  * @param  Size Length of the plaintext buffer in bytes or words (depending upon DataWidthUnit field)
  * @param  Output Pointer to the output buffer(ciphertext)
  * @retval HAL status
  */
HAL_StatusTypeDef HAL_CRYP_Encrypt_IT(CRYP_HandleTypeDef *hcryp, uint32_t *Input, uint16_t Size, uint32_t *Output)
{
  HAL_StatusTypeDef status;
  uint32_t algo;
#ifdef  USE_FULL_ASSERT
  uint32_t algo_assert = (hcryp->Instance->CR) & AES_CR_CHMOD;

  /* Check input buffer size */
  assert_param(IS_CRYP_BUFFERSIZE(algo_assert, hcryp->Init.DataWidthUnit, Size));
#endif

  if (hcryp->State == HAL_CRYP_STATE_READY)
  {
    /* Change state Busy */
    hcryp->State = HAL_CRYP_STATE_BUSY;

    /* Process locked */
    __HAL_LOCK(hcryp);

    /*  Reset CrypInCount, CrypOutCount and Initialize pCrypInBuffPtr and pCrypOutBuffPtr parameters*/
#if (USE_HAL_CRYP_SUSPEND_RESUME == 1U)
   if (hcryp->ResumingFlag == 1U)
   {
     hcryp->ResumingFlag = 0U;
     if (hcryp->Phase != CRYP_PHASE_HEADER_SUSPENDED)
     {
       hcryp->CrypInCount = (uint16_t) hcryp->CrypInCount_saved;
       hcryp->CrypOutCount = (uint16_t) hcryp->CrypOutCount_saved;
     }
     else
     {
    hcryp->CrypInCount = 0U;
    hcryp->CrypOutCount = 0U;
     }
   }
   else
#endif  /* USE_HAL_CRYP_SUSPEND_RESUME */
   {
    hcryp->CrypInCount = 0U;
    hcryp->CrypOutCount = 0U;
   }

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

    /* Set encryption operating mode*/
    MODIFY_REG(hcryp->Instance->CR, AES_CR_MODE, CRYP_OPERATINGMODE_ENCRYPT);

    /* algo get algorithm selected */
    algo = hcryp->Instance->CR & AES_CR_CHMOD;

    switch (algo)
    {

      case CRYP_AES_ECB:
      case CRYP_AES_CBC:
      case CRYP_AES_CTR:

        /* AES encryption */
        status = CRYP_AES_Encrypt_IT(hcryp);
        break;

      case CRYP_AES_GCM_GMAC:

        /* AES GCM encryption */
        status = CRYP_AESGCM_Process_IT(hcryp) ;
        break;

      case CRYP_AES_CCM:

        /* AES CCM encryption */
        status = CRYP_AESCCM_Process_IT(hcryp);
        break;

      default:
        hcryp->ErrorCode |= HAL_CRYP_ERROR_NOT_SUPPORTED;
        status = HAL_ERROR;
        break;
    }
  }
  else
  {
    /* Busy error code field */
    hcryp->ErrorCode |= HAL_CRYP_ERROR_BUSY;
    status = HAL_ERROR;
  }

  /* Return function status */
  return status;
}

/**
  * @brief  Decryption in interrupt mode.
  * @param  hcryp pointer to a CRYP_HandleTypeDef structure that contains
  *         the configuration information for CRYP module
  * @param  Input Pointer to the input buffer (ciphertext )
  * @param  Size Length of the plaintext buffer in bytes or words (depending upon DataWidthUnit field)
  * @param  Output Pointer to the output buffer(plaintext)
  * @retval HAL status
  */
HAL_StatusTypeDef HAL_CRYP_Decrypt_IT(CRYP_HandleTypeDef *hcryp, uint32_t *Input, uint16_t Size, uint32_t *Output)
{
  HAL_StatusTypeDef status;
  uint32_t algo;
#ifdef  USE_FULL_ASSERT
  uint32_t algo_assert = (hcryp->Instance->CR) & AES_CR_CHMOD;

  /* Check input buffer size */
  assert_param(IS_CRYP_BUFFERSIZE(algo_assert, hcryp->Init.DataWidthUnit, Size));
#endif

  if (hcryp->State == HAL_CRYP_STATE_READY)
  {
    /* Change state Busy */
    hcryp->State = HAL_CRYP_STATE_BUSY;

    /* Process locked */
    __HAL_LOCK(hcryp);

    /*  Reset CrypInCount, CrypOutCount and Initialize pCrypInBuffPtr and pCrypOutBuffPtr parameters*/
#if (USE_HAL_CRYP_SUSPEND_RESUME == 1U)
   if (hcryp->ResumingFlag == 1U)
   {
     hcryp->ResumingFlag = 0U;
     if (hcryp->Phase != CRYP_PHASE_HEADER_SUSPENDED)
     {
       hcryp->CrypInCount = (uint16_t) hcryp->CrypInCount_saved;
       hcryp->CrypOutCount = (uint16_t) hcryp->CrypOutCount_saved;
     }
     else
     {
    hcryp->CrypInCount = 0U;
    hcryp->CrypOutCount = 0U;
     }
   }
   else
#endif  /* USE_HAL_CRYP_SUSPEND_RESUME */
   {
     hcryp->CrypInCount = 0U;
     hcryp->CrypOutCount = 0U;
   }
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

    /* Set decryption operating mode*/
    MODIFY_REG(hcryp->Instance->CR, AES_CR_MODE, CRYP_OPERATINGMODE_DECRYPT);

    /* algo get algorithm selected */
    algo = hcryp->Instance->CR & AES_CR_CHMOD;

    switch (algo)
    {

      case CRYP_AES_ECB:
      case CRYP_AES_CBC:
      case CRYP_AES_CTR:

        /* AES decryption */
        status = CRYP_AES_Decrypt_IT(hcryp);
        break;

      case CRYP_AES_GCM_GMAC:

        /* AES GCM decryption */
        status = CRYP_AESGCM_Process_IT(hcryp) ;
        break;

      case CRYP_AES_CCM:

        /* AES CCM decryption */
        status = CRYP_AESCCM_Process_IT(hcryp);
        break;

      default:
        hcryp->ErrorCode |= HAL_CRYP_ERROR_NOT_SUPPORTED;
        status = HAL_ERROR;
        break;
    }
  }
  else
  {
    /* Busy error code field */
    hcryp->ErrorCode |= HAL_CRYP_ERROR_BUSY;
    status = HAL_ERROR;
  }

  /* Return function status */
  return status;
}

/**
  * @brief  Encryption in DMA mode.
  * @param  hcryp pointer to a CRYP_HandleTypeDef structure that contains
  *         the configuration information for CRYP module
  * @param  Input Pointer to the input buffer (plaintext)
  * @param  Size Length of the plaintext buffer in bytes or words (depending upon DataWidthUnit field)
  * @param  Output Pointer to the output buffer(ciphertext)
  * @retval HAL status
  */
HAL_StatusTypeDef HAL_CRYP_Encrypt_DMA(CRYP_HandleTypeDef *hcryp, uint32_t *Input, uint16_t Size, uint32_t *Output)
{
  HAL_StatusTypeDef status;
  uint32_t algo;
  uint32_t DoKeyIVConfig = 1U; /* By default, carry out peripheral Key and IV configuration */
#ifdef  USE_FULL_ASSERT
  uint32_t algo_assert = (hcryp->Instance->CR) & AES_CR_CHMOD;

  /* Check input buffer size */
  assert_param(IS_CRYP_BUFFERSIZE(algo_assert, hcryp->Init.DataWidthUnit, Size));
#endif

  if (hcryp->State == HAL_CRYP_STATE_READY)
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

    /* Set encryption operating mode*/
    MODIFY_REG(hcryp->Instance->CR, AES_CR_MODE, CRYP_OPERATINGMODE_ENCRYPT);

    /* algo get algorithm selected */
    algo = hcryp->Instance->CR & AES_CR_CHMOD;

    switch (algo)
    {

      case CRYP_AES_ECB:
      case CRYP_AES_CBC:
      case CRYP_AES_CTR:

        if (hcryp->Init.KeyIVConfigSkip == CRYP_KEYIVCONFIG_ONCE)
        {
          if (hcryp->KeyIVConfig == 1U)
          {
            /* If the Key and IV configuration has to be done only once
               and if it has already been done, skip it */
            DoKeyIVConfig = 0U;
          }
          else
          {
            /* If the Key and IV configuration has to be done only once
               and if it has not been done already, do it and set KeyIVConfig
               to keep track it won't have to be done again next time */
            hcryp->KeyIVConfig = 1U;
          }
        }

        if (DoKeyIVConfig == 1U)
        {
          /*  Set the Key*/
          CRYP_SetKey(hcryp, hcryp->Init.KeySize);

          /* Set the Initialization Vector*/
          if (hcryp->Init.Algorithm != CRYP_AES_ECB)
          {
            hcryp->Instance->IVR3 = *(uint32_t *)(hcryp->Init.pInitVect);
            hcryp->Instance->IVR2 = *(uint32_t *)(hcryp->Init.pInitVect + 1U);
            hcryp->Instance->IVR1 = *(uint32_t *)(hcryp->Init.pInitVect + 2U);
            hcryp->Instance->IVR0 = *(uint32_t *)(hcryp->Init.pInitVect + 3U);
          }
        } /* if (DoKeyIVConfig == 1U) */

        /* Set the phase */
        hcryp->Phase = CRYP_PHASE_PROCESS;

        /* Start DMA process transfer for AES */
        CRYP_SetDMAConfig(hcryp, (uint32_t)(hcryp->pCrypInBuffPtr), (hcryp->Size / 4U), (uint32_t)(hcryp->pCrypOutBuffPtr));
        status = HAL_OK;
        break;

      case CRYP_AES_GCM_GMAC:

        /* AES GCM encryption */
        status = CRYP_AESGCM_Process_DMA(hcryp) ;
        break;

      case CRYP_AES_CCM:

        /* AES CCM encryption */
        status = CRYP_AESCCM_Process_DMA(hcryp);
        break;

      default:
        hcryp->ErrorCode |= HAL_CRYP_ERROR_NOT_SUPPORTED;
        status = HAL_ERROR;
        break;
    }
  }
  else
  {
    /* Busy error code field */
    hcryp->ErrorCode |= HAL_CRYP_ERROR_BUSY;
    status = HAL_ERROR;
  }

  /* Return function status */
  return status;
}

/**
  * @brief  Decryption in DMA mode.
  * @param  hcryp pointer to a CRYP_HandleTypeDef structure that contains
  *         the configuration information for CRYP module
  * @param  Input Pointer to the input buffer (ciphertext )
  * @param  Size Length of the plaintext buffer in bytes or words (depending upon DataWidthUnit field)
  * @param  Output Pointer to the output buffer(plaintext)
  * @retval HAL status
  */
HAL_StatusTypeDef HAL_CRYP_Decrypt_DMA(CRYP_HandleTypeDef *hcryp, uint32_t *Input, uint16_t Size, uint32_t *Output)
{
  HAL_StatusTypeDef status;
  uint32_t algo;
#ifdef  USE_FULL_ASSERT
  uint32_t algo_assert = (hcryp->Instance->CR) & AES_CR_CHMOD;

  /* Check input buffer size */
  assert_param(IS_CRYP_BUFFERSIZE(algo_assert, hcryp->Init.DataWidthUnit, Size));
#endif

  if (hcryp->State == HAL_CRYP_STATE_READY)
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

    /* Set decryption operating mode*/
    MODIFY_REG(hcryp->Instance->CR, AES_CR_MODE, CRYP_OPERATINGMODE_DECRYPT);

    /* algo get algorithm selected */
    algo = hcryp->Instance->CR & AES_CR_CHMOD;

    switch (algo)
    {

      case CRYP_AES_ECB:
      case CRYP_AES_CBC:
      case CRYP_AES_CTR:

        /* AES decryption */
        status = CRYP_AES_Decrypt_DMA(hcryp);
        break;

      case CRYP_AES_GCM_GMAC:

        /* AES GCM decryption */
        status = CRYP_AESGCM_Process_DMA(hcryp) ;
        break;

      case CRYP_AES_CCM:

        /* AES CCM decryption */
        status = CRYP_AESCCM_Process_DMA(hcryp);
        break;

      default:
        hcryp->ErrorCode |= HAL_CRYP_ERROR_NOT_SUPPORTED;
        status = HAL_ERROR;
        break;
    }
  }
  else
  {
    /* Busy error code field */
    hcryp->ErrorCode |= HAL_CRYP_ERROR_BUSY;
    status = HAL_ERROR;
  }
  /* Return function status */
  return status;
}

/**
  * @}
  */

/** @defgroup CRYP_Exported_Functions_Group3 CRYP IRQ handler management
  * @brief    CRYP IRQ handler.
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
  * @param  hcryp pointer to a CRYP_HandleTypeDef structure that contains
  *         the configuration information for CRYP module
  * @retval None
  */
void HAL_CRYP_IRQHandler(CRYP_HandleTypeDef *hcryp)
{

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

  if (__HAL_CRYP_GET_FLAG(hcryp, CRYP_IT_CCF) != RESET)
  {
    if(__HAL_CRYP_GET_IT_SOURCE(hcryp, CRYP_IT_CCFIE) != RESET)
  {
    /* Clear computation complete flag */
    __HAL_CRYP_CLEAR_FLAG(hcryp, CRYP_CCF_CLEAR);

    if ((hcryp->Init.Algorithm == CRYP_AES_GCM_GMAC) || (hcryp->Init.Algorithm == CRYP_AES_CCM))
    {

      /* if header phase */
      if ((hcryp->Instance->CR & CRYP_PHASE_HEADER) == CRYP_PHASE_HEADER)
      {
        CRYP_GCMCCM_SetHeaderPhase_IT(hcryp);
      }
      else  /* if payload phase */
      {
        CRYP_GCMCCM_SetPayloadPhase_IT(hcryp);
      }
    }
    else  /* AES Algorithm ECB,CBC or CTR*/
    {
      CRYP_AES_IT(hcryp);
    }
  }
}
}

/**
  * @brief  Return the CRYP error code.
  * @param  hcryp pointer to a CRYP_HandleTypeDef structure that contains
  *                 the configuration information for the  CRYP peripheral
  * @retval CRYP error code
  */
uint32_t HAL_CRYP_GetError(CRYP_HandleTypeDef *hcryp)
{
  return hcryp->ErrorCode;
}

/**
  * @brief  Returns the CRYP state.
  * @param  hcryp pointer to a CRYP_HandleTypeDef structure that contains
  *         the configuration information for CRYP module.
  * @retval HAL state
  */
HAL_CRYP_STATETypeDef HAL_CRYP_GetState(CRYP_HandleTypeDef *hcryp)
{
  return hcryp->State;
}

/**
  * @brief  Input FIFO transfer completed callback.
  * @param  hcryp pointer to a CRYP_HandleTypeDef structure that contains
  *         the configuration information for CRYP module.
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
  * @brief  Output FIFO transfer completed callback.
  * @param  hcryp pointer to a CRYP_HandleTypeDef structure that contains
  *         the configuration information for CRYP module.
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
  * @brief  CRYP error callback.
  * @param  hcryp pointer to a CRYP_HandleTypeDef structure that contains
  *         the configuration information for CRYP module.
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
  * @}
  */

/**
  * @}
  */

/* Private functions ---------------------------------------------------------*/
/** @addtogroup CRYP_Private_Functions
  * @{
  */

/**
  * @brief  Encryption in ECB/CBC & CTR Algorithm with AES Standard
  * @param  hcryp pointer to a CRYP_HandleTypeDef structure
  * @param  Timeout specify Timeout value
  * @retval HAL status
  */
static HAL_StatusTypeDef CRYP_AES_Encrypt(CRYP_HandleTypeDef *hcryp, uint32_t Timeout)
{
  uint16_t incount;  /* Temporary CrypInCount Value */
  uint16_t outcount;  /* Temporary CrypOutCount Value */
  uint32_t DoKeyIVConfig = 1U; /* By default, carry out peripheral Key and IV configuration */

  if (hcryp->Init.KeyIVConfigSkip == CRYP_KEYIVCONFIG_ONCE)
  {
    if (hcryp->KeyIVConfig == 1U)
    {
      /* If the Key and IV configuration has to be done only once
         and if it has already been done, skip it */
      DoKeyIVConfig = 0U;
    }
    else
    {
      /* If the Key and IV configuration has to be done only once
         and if it has not been done already, do it and set KeyIVConfig
         to keep track it won't have to be done again next time */
      hcryp->KeyIVConfig = 1U;
    }
  }

  if (DoKeyIVConfig == 1U)
  {
    /*  Set the Key*/
    CRYP_SetKey(hcryp, hcryp->Init.KeySize);

    if (hcryp->Init.Algorithm != CRYP_AES_ECB)
    {
      /* Set the Initialization Vector*/
      hcryp->Instance->IVR3 = *(uint32_t *)(hcryp->Init.pInitVect);
      hcryp->Instance->IVR2 = *(uint32_t *)(hcryp->Init.pInitVect + 1U);
      hcryp->Instance->IVR1 = *(uint32_t *)(hcryp->Init.pInitVect + 2U);
      hcryp->Instance->IVR0 = *(uint32_t *)(hcryp->Init.pInitVect + 3U);
    }
  } /* if (DoKeyIVConfig == 1U) */

  /* Set the phase */
  hcryp->Phase = CRYP_PHASE_PROCESS;

  /* Enable CRYP */
  __HAL_CRYP_ENABLE(hcryp);

  incount = hcryp->CrypInCount;
  outcount = hcryp->CrypOutCount;
  while ((incount < (hcryp->Size / 4U)) && (outcount < (hcryp->Size / 4U)))
  {
    /* Write plain Ddta and get cipher data */
    CRYP_AES_ProcessData(hcryp, Timeout);
    incount = hcryp->CrypInCount;
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
  * @param  hcryp pointer to a CRYP_HandleTypeDef structure that contains
  *         the configuration information for CRYP module
  * @retval HAL status
  */
static HAL_StatusTypeDef CRYP_AES_Encrypt_IT(CRYP_HandleTypeDef *hcryp)
{
  uint32_t DoKeyIVConfig = 1U; /* By default, carry out peripheral Key and IV configuration */

  if (hcryp->Init.KeyIVConfigSkip == CRYP_KEYIVCONFIG_ONCE)
  {
    if (hcryp->KeyIVConfig == 1U)
    {
      /* If the Key and IV configuration has to be done only once
         and if it has already been done, skip it */
      DoKeyIVConfig = 0U;
    }
    else
    {
      /* If the Key and IV configuration has to be done only once
         and if it has not been done already, do it and set KeyIVConfig
         to keep track it won't have to be done again next time */
      hcryp->KeyIVConfig = 1U;
    }
  }

  if (DoKeyIVConfig == 1U)
  {
    /*  Set the Key*/
    CRYP_SetKey(hcryp, hcryp->Init.KeySize);

    if (hcryp->Init.Algorithm != CRYP_AES_ECB)
    {
      /* Set the Initialization Vector*/
      hcryp->Instance->IVR3 = *(uint32_t *)(hcryp->Init.pInitVect);
      hcryp->Instance->IVR2 = *(uint32_t *)(hcryp->Init.pInitVect + 1U);
      hcryp->Instance->IVR1 = *(uint32_t *)(hcryp->Init.pInitVect + 2U);
      hcryp->Instance->IVR0 = *(uint32_t *)(hcryp->Init.pInitVect + 3U);
    }
  } /* if (DoKeyIVConfig == 1U) */

  /* Set the phase */
  hcryp->Phase = CRYP_PHASE_PROCESS;

  if (hcryp->Size != 0U)
  {

    /* Enable computation complete flag and error interrupts */
    __HAL_CRYP_ENABLE_IT(hcryp, CRYP_IT_CCFIE | CRYP_IT_ERRIE);

    /* Enable CRYP */
    __HAL_CRYP_ENABLE(hcryp);

    /* Write the input block in the IN FIFO */
    hcryp->Instance->DINR  = *(uint32_t *)(hcryp->pCrypInBuffPtr + hcryp->CrypInCount);
    hcryp->CrypInCount++;
    hcryp->Instance->DINR  = *(uint32_t *)(hcryp->pCrypInBuffPtr + hcryp->CrypInCount);
    hcryp->CrypInCount++;
    hcryp->Instance->DINR  = *(uint32_t *)(hcryp->pCrypInBuffPtr + hcryp->CrypInCount);
    hcryp->CrypInCount++;
    hcryp->Instance->DINR  = *(uint32_t *)(hcryp->pCrypInBuffPtr + hcryp->CrypInCount);
    hcryp->CrypInCount++;
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
  * @param  hcryp pointer to a CRYP_HandleTypeDef structure
  * @param  Timeout Specify Timeout value
  * @retval HAL status
*/
static HAL_StatusTypeDef CRYP_AES_Decrypt(CRYP_HandleTypeDef *hcryp, uint32_t Timeout)
{
  uint16_t incount;  /* Temporary CrypInCount Value */
  uint16_t outcount;  /* Temporary CrypOutCount Value */
  uint32_t DoKeyIVConfig = 1U; /* By default, carry out peripheral Key and IV configuration */

  if (hcryp->Init.KeyIVConfigSkip == CRYP_KEYIVCONFIG_ONCE)
  {
    if (hcryp->KeyIVConfig == 1U)
    {
      /* If the Key and IV configuration has to be done only once
         and if it has already been done, skip it */
      DoKeyIVConfig = 0U;
    }
    else
    {
      /* If the Key and IV configuration has to be done only once
         and if it has not been done already, do it and set KeyIVConfig
         to keep track it won't have to be done again next time */
      hcryp->KeyIVConfig = 1U;
    }
  }

  if (DoKeyIVConfig == 1U)
  {
    /*  Key preparation for ECB/CBC */
    if (hcryp->Init.Algorithm != CRYP_AES_CTR)   /*ECB or CBC*/
    {
      if (hcryp->AutoKeyDerivation == DISABLE)/*Mode 2 Key preparation*/
      {
        /* Set key preparation for decryption operating mode*/
        MODIFY_REG(hcryp->Instance->CR, AES_CR_MODE, CRYP_OPERATINGMODE_KEYDERIVATION);

        /*  Set the Key*/
        CRYP_SetKey(hcryp, hcryp->Init.KeySize);

        /* Enable CRYP */
        __HAL_CRYP_ENABLE(hcryp);

        /* Wait for CCF flag to be raised */
        if (CRYP_WaitOnCCFlag(hcryp, Timeout) != HAL_OK)
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
      hcryp->Instance->IVR3 = *(uint32_t *)(hcryp->Init.pInitVect);
      hcryp->Instance->IVR2 = *(uint32_t *)(hcryp->Init.pInitVect + 1U);
      hcryp->Instance->IVR1 = *(uint32_t *)(hcryp->Init.pInitVect + 2U);
      hcryp->Instance->IVR0 = *(uint32_t *)(hcryp->Init.pInitVect + 3U);
    }
  } /* if (DoKeyIVConfig == 1U) */

  /* Set the phase */
  hcryp->Phase = CRYP_PHASE_PROCESS;

  /* Enable CRYP */
  __HAL_CRYP_ENABLE(hcryp);

  incount = hcryp->CrypInCount;
  outcount = hcryp->CrypOutCount;
  while ((incount < (hcryp->Size / 4U)) && (outcount < (hcryp->Size / 4U)))
  {
    /* Write plain data and get cipher data */
    CRYP_AES_ProcessData(hcryp, Timeout);
    incount = hcryp->CrypInCount;
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
  * @param  hcryp pointer to a CRYP_HandleTypeDef structure that contains
  *         the configuration information for CRYP module
  * @retval HAL status
  */
static HAL_StatusTypeDef CRYP_AES_Decrypt_IT(CRYP_HandleTypeDef *hcryp)
{
  __IO uint32_t count = 0U;
  uint32_t DoKeyIVConfig = 1U; /* By default, carry out peripheral Key and IV configuration */

  if (hcryp->Init.KeyIVConfigSkip == CRYP_KEYIVCONFIG_ONCE)
  {
    if (hcryp->KeyIVConfig == 1U)
    {
      /* If the Key and IV configuration has to be done only once
         and if it has already been done, skip it */
      DoKeyIVConfig = 0U;
    }
    else
    {
      /* If the Key and IV configuration has to be done only once
         and if it has not been done already, do it and set KeyIVConfig
         to keep track it won't have to be done again next time */
      hcryp->KeyIVConfig = 1U;
    }
  }

  if (DoKeyIVConfig == 1U)
  {
    /*  Key preparation for ECB/CBC */
    if (hcryp->Init.Algorithm != CRYP_AES_CTR)
    {
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
          if (count == 0U)
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
        while (HAL_IS_BIT_CLR(hcryp->Instance->SR, AES_SR_CCF));

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
      hcryp->Instance->IVR3 = *(uint32_t *)(hcryp->Init.pInitVect);
      hcryp->Instance->IVR2 = *(uint32_t *)(hcryp->Init.pInitVect + 1U);
      hcryp->Instance->IVR1 = *(uint32_t *)(hcryp->Init.pInitVect + 2U);
      hcryp->Instance->IVR0 = *(uint32_t *)(hcryp->Init.pInitVect + 3U);
    }
  } /* if (DoKeyIVConfig == 1U) */

  /* Set the phase */
  hcryp->Phase = CRYP_PHASE_PROCESS;
  if (hcryp->Size != 0U)
  {
    /* Enable computation complete flag and error interrupts */
    __HAL_CRYP_ENABLE_IT(hcryp, CRYP_IT_CCFIE | CRYP_IT_ERRIE);

    /* Enable CRYP */
    __HAL_CRYP_ENABLE(hcryp);

    /* Write the input block in the IN FIFO */
    hcryp->Instance->DINR  = *(uint32_t *)(hcryp->pCrypInBuffPtr + hcryp->CrypInCount);
    hcryp->CrypInCount++;
    hcryp->Instance->DINR  = *(uint32_t *)(hcryp->pCrypInBuffPtr + hcryp->CrypInCount);
    hcryp->CrypInCount++;
    hcryp->Instance->DINR  = *(uint32_t *)(hcryp->pCrypInBuffPtr + hcryp->CrypInCount);
    hcryp->CrypInCount++;
    hcryp->Instance->DINR  = *(uint32_t *)(hcryp->pCrypInBuffPtr + hcryp->CrypInCount);
    hcryp->CrypInCount++;
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
  * @param  hcryp pointer to a CRYP_HandleTypeDef structure that contains
  *         the configuration information for CRYP module
  * @retval HAL status
  */
static HAL_StatusTypeDef CRYP_AES_Decrypt_DMA(CRYP_HandleTypeDef *hcryp)
{
  __IO uint32_t count = 0U;
  uint32_t DoKeyIVConfig = 1U; /* By default, carry out peripheral Key and IV configuration */

  if (hcryp->Init.KeyIVConfigSkip == CRYP_KEYIVCONFIG_ONCE)
  {
    if (hcryp->KeyIVConfig == 1U)
    {
      /* If the Key and IV configuration has to be done only once
         and if it has already been done, skip it */
      DoKeyIVConfig = 0U;
    }
    else
    {
      /* If the Key and IV configuration has to be done only once
         and if it has not been done already, do it and set KeyIVConfig
         to keep track it won't have to be done again next time */
      hcryp->KeyIVConfig = 1U;
    }
  }

  if (DoKeyIVConfig == 1U)
  {
    /*  Key preparation for ECB/CBC */
    if (hcryp->Init.Algorithm != CRYP_AES_CTR)
    {
      if (hcryp->AutoKeyDerivation == DISABLE)/*Mode 2 key preparation*/
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
          if (count == 0U)
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
        while (HAL_IS_BIT_CLR(hcryp->Instance->SR, AES_SR_CCF));

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
    }
    else  /*Algorithm CTR */
    {
      /*  Set the Key*/
      CRYP_SetKey(hcryp, hcryp->Init.KeySize);
    }

    if (hcryp->Init.Algorithm != CRYP_AES_ECB)
    {
      /* Set the Initialization Vector*/
      hcryp->Instance->IVR3 = *(uint32_t *)(hcryp->Init.pInitVect);
      hcryp->Instance->IVR2 = *(uint32_t *)(hcryp->Init.pInitVect + 1U);
      hcryp->Instance->IVR1 = *(uint32_t *)(hcryp->Init.pInitVect + 2U);
      hcryp->Instance->IVR0 = *(uint32_t *)(hcryp->Init.pInitVect + 3U);
    }
  } /* if (DoKeyIVConfig == 1U) */

  /* Set the phase */
  hcryp->Phase = CRYP_PHASE_PROCESS;

  if (hcryp->Size != 0U)
  {
    /* Set the input and output addresses and start DMA transfer */
    CRYP_SetDMAConfig(hcryp, (uint32_t)(hcryp->pCrypInBuffPtr), (hcryp->Size / 4U), (uint32_t)(hcryp->pCrypOutBuffPtr));
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
  * @param  hdma DMA handle
  * @retval None
  */
static void CRYP_DMAInCplt(DMA_HandleTypeDef *hdma)
{
  CRYP_HandleTypeDef *hcryp = (CRYP_HandleTypeDef *)((DMA_HandleTypeDef *)hdma)->Parent;
  uint32_t loopcounter;
  uint32_t headersize_in_bytes;
  uint32_t tmp;
  uint32_t mask[12] = {0x0U, 0xFF000000U, 0xFFFF0000U, 0xFFFFFF00U,  /* 32-bit data type */
                       0x0U, 0x0000FF00U, 0x0000FFFFU, 0xFF00FFFFU,  /* 16-bit data type */
                       0x0U, 0x000000FFU, 0x0000FFFFU, 0x00FFFFFFU}; /*  8-bit data type */

  /* Stop the DMA transfers to the IN FIFO by clearing to "0" the DMAINEN */
  CLEAR_BIT(hcryp->Instance->CR, AES_CR_DMAINEN);

  if (hcryp->Phase == CRYP_PHASE_HEADER_DMA_FEED)
  {
    /* DMA is disabled, CCF is meaningful. Wait for computation completion before moving forward */
    CRYP_ClearCCFlagWhenHigh(hcryp, CRYP_TIMEOUT_GCMCCMHEADERPHASE);

    /* Set the phase */
    hcryp->Phase = CRYP_PHASE_PROCESS;

    if (hcryp->Init.HeaderWidthUnit == CRYP_HEADERWIDTHUNIT_WORD)
    {
      headersize_in_bytes = hcryp->Init.HeaderSize * 4U;
    }
    else
    {
      headersize_in_bytes = hcryp->Init.HeaderSize;
    }

    if ((headersize_in_bytes % 16U) != 0U)
    {
      /* Write last words that couldn't be fed by DMA */
      hcryp->CrypHeaderCount = (uint16_t)((headersize_in_bytes / 16U) * 4U);
      for (loopcounter = 0U; (loopcounter < ((headersize_in_bytes / 4U) % 4U)); loopcounter++)
      {
        hcryp->Instance->DINR = *(uint32_t *)(hcryp->Init.Header + hcryp->CrypHeaderCount);
        hcryp->CrypHeaderCount++ ;
      }
      /* If the header size is a multiple of words */
      if ((headersize_in_bytes % 4U) == 0U)
      {
        /* Pad the data with zeros to have a complete block */
        while (loopcounter < 4U)
        {
          hcryp->Instance->DINR = 0x0U;
          loopcounter++;
        }
      }
      else
      {
        /* Enter last bytes, padded with zeros */
        tmp =  *(uint32_t *)(hcryp->Init.Header + hcryp->CrypHeaderCount);
        tmp &= mask[(hcryp->Init.DataType * 2U) + (headersize_in_bytes % 4U)];
        hcryp->Instance->DINR = tmp;
        loopcounter++;
        /* Pad the data with zeros to have a complete block */
        while (loopcounter < 4U)
        {
          hcryp->Instance->DINR = 0x0U;
          loopcounter++;
        }
      }

      /* Wait for computation completion before moving forward */
      CRYP_ClearCCFlagWhenHigh(hcryp, CRYP_TIMEOUT_GCMCCMHEADERPHASE);
    } /* if ((headersize_in_bytes % 16U) != 0U) */

    /* Set to 0 the number of non-valid bytes using NPBLB register*/
    MODIFY_REG(hcryp->Instance->CR, AES_CR_NPBLB, 0U);

    /* Select payload phase once the header phase is performed */
    CRYP_SET_PHASE(hcryp, CRYP_PHASE_PAYLOAD);

    /* Initiate payload DMA IN and processed data DMA OUT transfers */
    (void)CRYP_GCMCCM_SetPayloadPhase_DMA(hcryp);
  }
  else
  {
    uint32_t algo;
    /* ECB, CBC or CTR end of input data feeding 
       or
       end of GCM/CCM payload data feeding through DMA */
    algo = hcryp->Instance->CR & AES_CR_CHMOD;

    /* Don't call input data transfer complete callback only if 
       it remains some input data to write to the peripheral.
       This case can only occur for GCM and CCM with a payload length
       not a multiple of 16 bytes */
    if (!(((algo == CRYP_AES_GCM_GMAC) || (algo == CRYP_AES_CCM)) && \
        (((hcryp->Size) % 16U) != 0U)))
    {
      /* Call input data transfer complete callback */
#if (USE_HAL_CRYP_REGISTER_CALLBACKS == 1U)
      /*Call registered Input complete callback*/
      hcryp->InCpltCallback(hcryp);
#else
      /*Call legacy weak Input complete callback*/
      HAL_CRYP_InCpltCallback(hcryp);
#endif /* USE_HAL_CRYP_REGISTER_CALLBACKS */
    }
  } /* if (hcryp->Phase == CRYP_PHASE_HEADER_DMA_FEED) */
}

/**
  * @brief  DMA CRYP output data process complete callback.
  * @param  hdma DMA handle
  * @retval None
  */
static void CRYP_DMAOutCplt(DMA_HandleTypeDef *hdma)
{
  uint32_t count;
  uint32_t npblb;
  uint32_t lastwordsize;
  uint32_t temp[4];  /* Temporary CrypOutBuff */
  uint32_t mode;

  CRYP_HandleTypeDef *hcryp = (CRYP_HandleTypeDef *)((DMA_HandleTypeDef *)hdma)->Parent;

  /* Stop the DMA transfers to the OUT FIFO by clearing to "0" the DMAOUTEN */
  CLEAR_BIT(hcryp->Instance->CR, AES_CR_DMAOUTEN);

  /* Clear CCF flag */
  __HAL_CRYP_CLEAR_FLAG(hcryp, CRYP_CCF_CLEAR);

  /* Last block transfer in case of GCM or CCM with Size not %16*/
  if (((hcryp->Size) % 16U) != 0U)
  {
    /* set CrypInCount and CrypOutCount to exact number of word already computed via DMA  */
    hcryp->CrypInCount = (hcryp->Size / 16U) * 4U;
    hcryp->CrypOutCount = hcryp->CrypInCount;

    /* Compute the number of padding bytes in last block of payload */
    npblb = ((((uint32_t)hcryp->Size / 16U) + 1U) * 16U) - ((uint32_t)hcryp->Size);

    mode = hcryp->Instance->CR & AES_CR_MODE;
    if (((mode == CRYP_OPERATINGMODE_ENCRYPT) && (hcryp->Init.Algorithm == CRYP_AES_GCM_GMAC)) ||
        ((mode == CRYP_OPERATINGMODE_DECRYPT) && (hcryp->Init.Algorithm == CRYP_AES_CCM)))
    {
      /* Specify the number of non-valid bytes using NPBLB register*/
      MODIFY_REG(hcryp->Instance->CR, AES_CR_NPBLB, npblb << 20U);
    }

    /* Number of valid words (lastwordsize) in last block */
    if ((npblb % 4U) == 0U)
    {
      lastwordsize = (16U - npblb) / 4U;
    }
    else
    {
      lastwordsize = ((16U - npblb) / 4U) + 1U;
    }

    /*  Last block optionally pad the data with zeros*/
    for (count = 0U; count < lastwordsize; count++)
    {
      hcryp->Instance->DINR = *(uint32_t *)(hcryp->pCrypInBuffPtr + hcryp->CrypInCount);
      hcryp->CrypInCount++;
    }
    while (count < 4U)
    {
      /* Pad the data with zeros to have a complete block */
      hcryp->Instance->DINR = 0x0U;
      count++;
    }
    /* Call input data transfer complete callback */
#if (USE_HAL_CRYP_REGISTER_CALLBACKS == 1U)
    /*Call registered Input complete callback*/
    hcryp->InCpltCallback(hcryp);
#else
    /*Call legacy weak Input complete callback*/
    HAL_CRYP_InCpltCallback(hcryp);
#endif /* USE_HAL_CRYP_REGISTER_CALLBACKS */  

    /*Wait on CCF flag*/
    CRYP_ClearCCFlagWhenHigh(hcryp, CRYP_TIMEOUT_GCMCCMHEADERPHASE);

    /*Read the output block from the output FIFO */
    for (count = 0U; count < 4U; count++)
    {
      /* Read the output block from the output FIFO and put them in temporary buffer then get CrypOutBuff from temporary buffer */
      temp[count] = hcryp->Instance->DOUTR;
    }

    count = 0U;
    while((hcryp->CrypOutCount < ((hcryp->Size + 3U)/4U)) && (count<4U))
    {
      *(uint32_t *)(hcryp->pCrypOutBuffPtr + hcryp->CrypOutCount) = temp[count];
      hcryp->CrypOutCount++;
      count++;
    }
  }

  if (((hcryp->Init.Algorithm & CRYP_AES_GCM_GMAC) != CRYP_AES_GCM_GMAC) && ((hcryp->Init.Algorithm & CRYP_AES_CCM) != CRYP_AES_CCM))
  {
    /* Disable CRYP (not allowed in  GCM)*/
    __HAL_CRYP_DISABLE(hcryp);
  }

  /* Change the CRYP state to ready */
  hcryp->State = HAL_CRYP_STATE_READY;

  /* Process unlocked */
  __HAL_UNLOCK(hcryp);

  /* Call output data transfer complete callback */
#if (USE_HAL_CRYP_REGISTER_CALLBACKS == 1U)
  /*Call registered Output complete callback*/
  hcryp->OutCpltCallback(hcryp);
#else
  /*Call legacy weak Output complete callback*/
  HAL_CRYP_OutCpltCallback(hcryp);
#endif /* USE_HAL_CRYP_REGISTER_CALLBACKS */
}

/**
  * @brief  DMA CRYP communication error callback.
  * @param  hdma DMA handle
  * @retval None
  */
static void CRYP_DMAError(DMA_HandleTypeDef *hdma)
{
  CRYP_HandleTypeDef *hcryp = (CRYP_HandleTypeDef *)((DMA_HandleTypeDef *)hdma)->Parent;

  /* Change the CRYP peripheral state */
  hcryp->State = HAL_CRYP_STATE_READY;

  /* DMA error code field */
  hcryp->ErrorCode |= HAL_CRYP_ERROR_DMA;

  /* Clear CCF flag */
  __HAL_CRYP_CLEAR_FLAG(hcryp, CRYP_CCF_CLEAR);

  /* Call error callback */
#if (USE_HAL_CRYP_REGISTER_CALLBACKS == 1U)
  /*Call registered error callback*/
  hcryp->ErrorCallback(hcryp);
#else
  /*Call legacy weak error callback*/
  HAL_CRYP_ErrorCallback(hcryp);
#endif /* USE_HAL_CRYP_REGISTER_CALLBACKS */
}

/**
  * @brief  Set the DMA configuration and start the DMA transfer
  * @param  hcryp pointer to a CRYP_HandleTypeDef structure that contains
  *         the configuration information for CRYP module
  * @param  inputaddr address of the input buffer
  * @param  Size size of the input and output buffers in words, must be a multiple of 4
  * @param  outputaddr address of the output buffer
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

  if ((hcryp->Init.Algorithm & CRYP_AES_GCM_GMAC) != CRYP_AES_GCM_GMAC)
  {
    /* Enable CRYP (not allowed in  GCM & CCM)*/
    __HAL_CRYP_ENABLE(hcryp);
  }

  /* Enable the DMA input stream */
  if (HAL_DMA_Start_IT(hcryp->hdmain, inputaddr, (uint32_t)&hcryp->Instance->DINR, Size) != HAL_OK)
  {
    /* DMA error code field */
    hcryp->ErrorCode |= HAL_CRYP_ERROR_DMA;

    /* Call error callback */
#if (USE_HAL_CRYP_REGISTER_CALLBACKS == 1U)
    /*Call registered error callback*/
    hcryp->ErrorCallback(hcryp);
#else
    /*Call legacy weak error callback*/
    HAL_CRYP_ErrorCallback(hcryp);
#endif /* USE_HAL_CRYP_REGISTER_CALLBACKS */
  }
  /* Enable the DMA output stream */
  if (HAL_DMA_Start_IT(hcryp->hdmaout, (uint32_t)&hcryp->Instance->DOUTR, outputaddr, Size) != HAL_OK)
  {
    /* DMA error code field */
    hcryp->ErrorCode |= HAL_CRYP_ERROR_DMA;

    /* Call error callback */
#if (USE_HAL_CRYP_REGISTER_CALLBACKS == 1U)
    /*Call registered error callback*/
    hcryp->ErrorCallback(hcryp);
#else
    /*Call legacy weak error callback*/
    HAL_CRYP_ErrorCallback(hcryp);
#endif /* USE_HAL_CRYP_REGISTER_CALLBACKS */
  }
  /* Enable In and Out DMA requests */
  SET_BIT(hcryp->Instance->CR, (AES_CR_DMAINEN | AES_CR_DMAOUTEN));
}

/**
  * @brief  Set the DMA configuration and start the header DMA transfer
  * @param  hcryp pointer to a CRYP_HandleTypeDef structure that contains
  *         the configuration information for CRYP module
  * @param  inputaddr address of the input buffer
  * @param  Size size of the input buffer in words, must be a multiple of 4
  * @retval None
  */
static HAL_StatusTypeDef CRYP_SetHeaderDMAConfig(CRYP_HandleTypeDef *hcryp, uint32_t inputaddr, uint16_t Size)
{
  /* Set the CRYP DMA transfer complete callback */
  hcryp->hdmain->XferCpltCallback = CRYP_DMAInCplt;

  /* Set the DMA input error callback */
  hcryp->hdmain->XferErrorCallback = CRYP_DMAError;

  /* Mark that header is fed to the peripheral in DMA mode */
  hcryp->Phase = CRYP_PHASE_HEADER_DMA_FEED;
  /* Enable the DMA input stream */
  if (HAL_DMA_Start_IT(hcryp->hdmain, inputaddr, (uint32_t)&hcryp->Instance->DINR, Size) != HAL_OK)
  {
    /* DMA error code field */
    hcryp->ErrorCode |= HAL_CRYP_ERROR_DMA;
    hcryp->State = HAL_CRYP_STATE_READY;

    /* Process unlocked */
    __HAL_UNLOCK(hcryp);
    return HAL_ERROR;
    /* Call error callback */
  }

  /* Enable IN DMA requests */
  SET_BIT(hcryp->Instance->CR, AES_CR_DMAINEN);

  return HAL_OK;
}

/**
  * @brief  Process Data: Write Input data in polling mode and used in AES functions.
  * @param  hcryp pointer to a CRYP_HandleTypeDef structure that contains
  *         the configuration information for CRYP module
  * @param  Timeout Specify Timeout value
  * @retval None
  */
static void CRYP_AES_ProcessData(CRYP_HandleTypeDef *hcryp, uint32_t Timeout)
{

  uint32_t temp[4];  /* Temporary CrypOutBuff */
  uint32_t i;

  /* Write the input block in the IN FIFO */
  hcryp->Instance->DINR  = *(uint32_t *)(hcryp->pCrypInBuffPtr + hcryp->CrypInCount);
  hcryp->CrypInCount++;
  hcryp->Instance->DINR  = *(uint32_t *)(hcryp->pCrypInBuffPtr + hcryp->CrypInCount);
  hcryp->CrypInCount++;
  hcryp->Instance->DINR  = *(uint32_t *)(hcryp->pCrypInBuffPtr + hcryp->CrypInCount);
  hcryp->CrypInCount++;
  hcryp->Instance->DINR  = *(uint32_t *)(hcryp->pCrypInBuffPtr + hcryp->CrypInCount);
  hcryp->CrypInCount++;

  /* Wait for CCF flag to be raised */
  if (CRYP_WaitOnCCFlag(hcryp, Timeout) != HAL_OK)
  {
    /* Disable the CRYP peripheral clock */
    __HAL_CRYP_DISABLE(hcryp);

    /* Change state */
    hcryp->ErrorCode |= HAL_CRYP_ERROR_TIMEOUT;
    hcryp->State = HAL_CRYP_STATE_READY;

    /* Process unlocked */
    __HAL_UNLOCK(hcryp);
    /*Call registered error callback*/
#if (USE_HAL_CRYP_REGISTER_CALLBACKS == 1U)
    hcryp->ErrorCallback(hcryp);
#else
    /*Call legacy weak error callback*/
    HAL_CRYP_ErrorCallback(hcryp);
#endif /* USE_HAL_CRYP_REGISTER_CALLBACKS */
  }

  /* Clear CCF Flag */
  __HAL_CRYP_CLEAR_FLAG(hcryp, CRYP_CCF_CLEAR);

  /* Read the output block from the output FIFO and put them in temporary buffer then get CrypOutBuff from temporary buffer*/
  for (i = 0U; i < 4U; i++)
  {
    temp[i] = hcryp->Instance->DOUTR;
  }
  i= 0U;
  while((hcryp->CrypOutCount < ((hcryp->Size + 3U)/4U)) && (i<4U))
  {
    *(uint32_t *)(hcryp->pCrypOutBuffPtr + hcryp->CrypOutCount) = temp[i];
    hcryp->CrypOutCount++;
    i++;
  }
}

/**
  * @brief  Handle CRYP block input/output data handling under interruption.
  * @note   The function is called under interruption only, once
  *         interruptions have been enabled by HAL_CRYP_Encrypt_IT or HAL_CRYP_Decrypt_IT.
  * @param  hcryp pointer to a CRYP_HandleTypeDef structure that contains
  *         the configuration information for CRYP module.
  * @retval HAL status
  */
static void CRYP_AES_IT(CRYP_HandleTypeDef *hcryp)
{
  uint32_t temp[4];  /* Temporary CrypOutBuff */
  uint32_t i;

  if (hcryp->State == HAL_CRYP_STATE_BUSY)
  {
    /* Read the output block from the output FIFO and put them in temporary buffer then get CrypOutBuff from temporary buffer*/
    for (i = 0U; i < 4U; i++)
    {
      temp[i] = hcryp->Instance->DOUTR;
    }
    i= 0U;
    while((hcryp->CrypOutCount < ((hcryp->Size + 3U)/4U)) && (i<4U))
    {
      *(uint32_t *)(hcryp->pCrypOutBuffPtr + hcryp->CrypOutCount) = temp[i];
      hcryp->CrypOutCount++;
      i++;
    }
    if (hcryp->CrypOutCount ==  (hcryp->Size / 4U))
    {
      /* Disable Computation Complete flag and errors interrupts */
      __HAL_CRYP_DISABLE_IT(hcryp, CRYP_IT_CCFIE | CRYP_IT_ERRIE);

      /* Change the CRYP state */
      hcryp->State = HAL_CRYP_STATE_READY;

      /* Disable CRYP */
      __HAL_CRYP_DISABLE(hcryp);

      /* Process Unlocked */
      __HAL_UNLOCK(hcryp);

      /* Call Output transfer complete callback */
#if (USE_HAL_CRYP_REGISTER_CALLBACKS == 1U)
      /*Call registered Output complete callback*/
      hcryp->OutCpltCallback(hcryp);
#else
      /*Call legacy weak Output complete callback*/
      HAL_CRYP_OutCpltCallback(hcryp);
#endif /* USE_HAL_CRYP_REGISTER_CALLBACKS */
    }
    else
    {
#if (USE_HAL_CRYP_SUSPEND_RESUME == 1U)
      /* If suspension flag has been raised, suspend processing
         only if not already at the end of the payload */
      if (hcryp->SuspendRequest == HAL_CRYP_SUSPEND)
      {
        /* Clear CCF Flag */
        __HAL_CRYP_CLEAR_FLAG(hcryp, CRYP_CCF_CLEAR);

        /* reset SuspendRequest */
        hcryp->SuspendRequest = HAL_CRYP_SUSPEND_NONE;
        /* Disable Computation Complete Flag and Errors Interrupts */
        __HAL_CRYP_DISABLE_IT(hcryp, CRYP_IT_CCFIE|CRYP_IT_ERRIE);
        /* Change the CRYP state */
        hcryp->State = HAL_CRYP_STATE_SUSPENDED;
        /* Mark that the payload phase is suspended */
        hcryp->Phase = CRYP_PHASE_PAYLOAD_SUSPENDED;

       /* Process Unlocked */
        __HAL_UNLOCK(hcryp);
      }
      else
#endif /* USE_HAL_CRYP_SUSPEND_RESUME */
      {
        /* Write the input block in the IN FIFO */
        hcryp->Instance->DINR  = *(uint32_t *)(hcryp->pCrypInBuffPtr + hcryp->CrypInCount);
        hcryp->CrypInCount++;
        hcryp->Instance->DINR  = *(uint32_t *)(hcryp->pCrypInBuffPtr + hcryp->CrypInCount);
        hcryp->CrypInCount++;
        hcryp->Instance->DINR  = *(uint32_t *)(hcryp->pCrypInBuffPtr + hcryp->CrypInCount);
        hcryp->CrypInCount++;
        hcryp->Instance->DINR  = *(uint32_t *)(hcryp->pCrypInBuffPtr + hcryp->CrypInCount);
        hcryp->CrypInCount++;

        if (hcryp->CrypInCount ==  (hcryp->Size / 4U))
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
    }
  }
  else
  {
    /* Busy error code field */
    hcryp->ErrorCode |= HAL_CRYP_ERROR_BUSY;
#if (USE_HAL_CRYP_REGISTER_CALLBACKS == 1U)
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
  * @param  hcryp pointer to a CRYP_HandleTypeDef structure that contains
  *         the configuration information for CRYP module
  * @param  KeySize Size of Key
  * @note   If pKey is NULL, the Key registers are not written. This configuration
  *         occurs when the key is written out of HAL scope.
  * @retval None
  */
static void CRYP_SetKey(CRYP_HandleTypeDef *hcryp, uint32_t KeySize)
{
  if (hcryp->Init.pKey != NULL)
  {
    switch (KeySize)
    {
      case CRYP_KEYSIZE_256B:
        hcryp->Instance->KEYR7 = *(uint32_t *)(hcryp->Init.pKey);
        hcryp->Instance->KEYR6 = *(uint32_t *)(hcryp->Init.pKey + 1U);
        hcryp->Instance->KEYR5 = *(uint32_t *)(hcryp->Init.pKey + 2U);
        hcryp->Instance->KEYR4 = *(uint32_t *)(hcryp->Init.pKey + 3U);
        hcryp->Instance->KEYR3 = *(uint32_t *)(hcryp->Init.pKey + 4U);
        hcryp->Instance->KEYR2 = *(uint32_t *)(hcryp->Init.pKey + 5U);
        hcryp->Instance->KEYR1 = *(uint32_t *)(hcryp->Init.pKey + 6U);
        hcryp->Instance->KEYR0 = *(uint32_t *)(hcryp->Init.pKey + 7U);
        break;
      case CRYP_KEYSIZE_128B:
        hcryp->Instance->KEYR3 = *(uint32_t *)(hcryp->Init.pKey);
        hcryp->Instance->KEYR2 = *(uint32_t *)(hcryp->Init.pKey + 1U);
        hcryp->Instance->KEYR1 = *(uint32_t *)(hcryp->Init.pKey + 2U);
        hcryp->Instance->KEYR0 = *(uint32_t *)(hcryp->Init.pKey + 3U);

        break;
      default:
        break;
    }
  }
}

/**
  * @brief  Encryption/Decryption process in AES GCM mode and prepare the authentication TAG
  * @param  hcryp pointer to a CRYP_HandleTypeDef structure that contains
  *         the configuration information for CRYP module
  * @param  Timeout Timeout duration
  * @retval HAL status
  */
static HAL_StatusTypeDef CRYP_AESGCM_Process(CRYP_HandleTypeDef *hcryp, uint32_t Timeout)
{
  uint32_t tickstart;
  uint32_t wordsize = ((uint32_t)hcryp->Size / 4U) ;
  uint32_t npblb;
  uint32_t temp[4];  /* Temporary CrypOutBuff */
  uint32_t index;
  uint32_t lastwordsize;
  uint32_t incount;  /* Temporary CrypInCount Value */
  uint32_t outcount;  /* Temporary CrypOutCount Value */
  uint32_t DoKeyIVConfig = 1U; /* By default, carry out peripheral Key and IV configuration */

  if (hcryp->Init.KeyIVConfigSkip == CRYP_KEYIVCONFIG_ONCE)
  {
    if (hcryp->KeyIVConfig == 1U)
    {
      /* If the Key and IV configuration has to be done only once
         and if it has already been done, skip it */
      DoKeyIVConfig = 0U;
      hcryp->SizesSum += hcryp->Size; /* Compute message total payload length */
    }
    else
    {
      /* If the Key and IV configuration has to be done only once
         and if it has not been done already, do it and set KeyIVConfig
         to keep track it won't have to be done again next time */
      hcryp->KeyIVConfig = 1U;
      hcryp->SizesSum = hcryp->Size; /* Merely store payload length */
    }
  }
  else
  {
    hcryp->SizesSum = hcryp->Size;
  }

  if (DoKeyIVConfig == 1U)
  {

    /*  Reset CrypHeaderCount */
    hcryp->CrypHeaderCount = 0U;

    /****************************** Init phase **********************************/

    CRYP_SET_PHASE(hcryp, CRYP_PHASE_INIT);

    /* Set the key */
    CRYP_SetKey(hcryp, hcryp->Init.KeySize);

    /* Set the initialization vector and the counter : Initial Counter Block (ICB)*/
    hcryp->Instance->IVR3 = *(uint32_t *)(hcryp->Init.pInitVect);
    hcryp->Instance->IVR2 = *(uint32_t *)(hcryp->Init.pInitVect + 1U);
    hcryp->Instance->IVR1 = *(uint32_t *)(hcryp->Init.pInitVect + 2U);
    hcryp->Instance->IVR0 = *(uint32_t *)(hcryp->Init.pInitVect + 3U);

    /* Enable the CRYP peripheral */
    __HAL_CRYP_ENABLE(hcryp);

    /* just wait for hash computation */
    if (CRYP_WaitOnCCFlag(hcryp, Timeout) != HAL_OK)
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

    /************************ Header phase *************************************/

    if (CRYP_GCMCCM_SetHeaderPhase(hcryp,  Timeout) != HAL_OK)
    {
      return HAL_ERROR;
    }

    /*************************Payload phase ************************************/

    /* Set the phase */
    hcryp->Phase = CRYP_PHASE_PROCESS;

    /* Select payload phase once the header phase is performed */
    CRYP_SET_PHASE(hcryp, CRYP_PHASE_PAYLOAD);

    /* Set to 0 the number of non-valid bytes using NPBLB register*/
    MODIFY_REG(hcryp->Instance->CR, AES_CR_NPBLB, 0U);

  } /* if (DoKeyIVConfig == 1U) */

  if ((hcryp->Size % 16U) != 0U)
  {
    /* recalculate  wordsize */
    wordsize = ((wordsize / 4U) * 4U) ;
  }

  /* Get tick */
  tickstart = HAL_GetTick();

  /* Write input data and get output Data */
  incount = hcryp->CrypInCount;
  outcount = hcryp->CrypOutCount;
  while ((incount < wordsize) && (outcount < wordsize))
  {
    /* Write plain data and get cipher data */
    CRYP_AES_ProcessData(hcryp, Timeout);

    /* Check for the Timeout */
    if (Timeout != HAL_MAX_DELAY)
    {
      if (((HAL_GetTick() - tickstart) > Timeout) || (Timeout == 0U))
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
    incount = hcryp->CrypInCount;
    outcount = hcryp->CrypOutCount;
  }

  if ((hcryp->Size % 16U) != 0U)
  {
    /* Compute the number of padding bytes in last block of payload */
    npblb = ((((uint32_t)hcryp->Size / 16U) + 1U) * 16U) - ((uint32_t)hcryp->Size);

    /*  Set Npblb in case of AES GCM payload encryption to get right tag*/
    if ((hcryp->Instance->CR & AES_CR_MODE) == CRYP_OPERATINGMODE_ENCRYPT)
    {
      /* Set to 0 the number of non-valid bytes using NPBLB register*/
      MODIFY_REG(hcryp->Instance->CR, AES_CR_NPBLB, npblb << 20U);
    }
    /* Number of valid words (lastwordsize) in last block */
    if ((npblb % 4U) == 0U)
    {
      lastwordsize = (16U - npblb) / 4U;
    }
    else
    {
      lastwordsize = ((16U - npblb) / 4U) + 1U;
    }
    /*  last block optionally pad the data with zeros*/
    for (index = 0U; index < lastwordsize; index ++)
    {
      /* Write the last Input block in the IN FIFO */
      hcryp->Instance->DINR  = *(uint32_t *)(hcryp->pCrypInBuffPtr + hcryp->CrypInCount);
      hcryp->CrypInCount++;
    }
    while (index < 4U)
    {
      /* pad the data with zeros to have a complete block */
      hcryp->Instance->DINR  = 0U;
      index++;
    }
    /* Wait for CCF flag to be raised */
    if (CRYP_WaitOnCCFlag(hcryp, Timeout) != HAL_OK)
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

    /*Read the output block from the output FIFO */
    for (index = 0U; index < 4U; index++)
    {
      /* Read the output block from the output FIFO and put them in temporary buffer then get CrypOutBuff from temporary buffer */
      temp[index] = hcryp->Instance->DOUTR;
    }
    for (index = 0U; index < lastwordsize; index++)
    {
      *(uint32_t *)(hcryp->pCrypOutBuffPtr + (hcryp->CrypOutCount)) = temp[index];
      hcryp->CrypOutCount++;
    }
  }

  /* Return function status */
  return HAL_OK;
}

/**
  * @brief  Encryption/Decryption process in AES GCM mode and prepare the authentication TAG in interrupt mode
  * @param  hcryp pointer to a CRYP_HandleTypeDef structure that contains
  *         the configuration information for CRYP module
  * @retval HAL status
  */
static HAL_StatusTypeDef CRYP_AESGCM_Process_IT(CRYP_HandleTypeDef *hcryp)
{
  __IO uint32_t count = 0U;
  uint32_t loopcounter;
  uint32_t lastwordsize;
  uint32_t npblb;
  uint32_t DoKeyIVConfig = 1U; /* By default, carry out peripheral Key and IV configuration */
  uint32_t headersize_in_bytes;
  uint32_t tmp;
  uint32_t mask[12] = {0x0U, 0xFF000000U, 0xFFFF0000U, 0xFFFFFF00U,  /* 32-bit data type */
                       0x0U, 0x0000FF00U, 0x0000FFFFU, 0xFF00FFFFU,  /* 16-bit data type */
                       0x0U, 0x000000FFU, 0x0000FFFFU, 0x00FFFFFFU}; /*  8-bit data type */


#if (USE_HAL_CRYP_SUSPEND_RESUME == 1U)
  if ((hcryp->Phase == CRYP_PHASE_HEADER_SUSPENDED) || (hcryp->Phase == CRYP_PHASE_PAYLOAD_SUSPENDED))
  {
    CRYP_PhaseProcessingResume(hcryp);
    return HAL_OK;
  }
#endif /* USE_HAL_CRYP_SUSPEND_RESUME */

  /* Manage header size given in bytes to handle cases where
     header size is not a multiple of 4 bytes */
  if (hcryp->Init.HeaderWidthUnit == CRYP_HEADERWIDTHUNIT_WORD)
  {
    headersize_in_bytes = hcryp->Init.HeaderSize * 4U;
  }
  else
  {
    headersize_in_bytes = hcryp->Init.HeaderSize;
  }

  if (hcryp->Init.KeyIVConfigSkip == CRYP_KEYIVCONFIG_ONCE)
  {
    if (hcryp->KeyIVConfig == 1U)
    {
      /* If the Key and IV configuration has to be done only once
         and if it has already been done, skip it */
      DoKeyIVConfig = 0U;
      hcryp->SizesSum += hcryp->Size; /* Compute message total payload length */
    }
    else
    {
      /* If the Key and IV configuration has to be done only once
         and if it has not been done already, do it and set KeyIVConfig
         to keep track it won't have to be done again next time */
      hcryp->KeyIVConfig = 1U;
      hcryp->SizesSum = hcryp->Size; /* Merely store payload length */
    }
  }
  else
  {
    hcryp->SizesSum = hcryp->Size;
  }

  /* Configure Key, IV and process message (header and payload) */
  if (DoKeyIVConfig == 1U)
  {
    /*  Reset CrypHeaderCount */
    hcryp->CrypHeaderCount = 0U;

    /******************************* Init phase *********************************/

    CRYP_SET_PHASE(hcryp, CRYP_PHASE_INIT);

    /* Set the key */
    CRYP_SetKey(hcryp, hcryp->Init.KeySize);

    /* Set the initialization vector and the counter : Initial Counter Block (ICB)*/
    hcryp->Instance->IVR3 = *(uint32_t *)(hcryp->Init.pInitVect);
    hcryp->Instance->IVR2 = *(uint32_t *)(hcryp->Init.pInitVect + 1U);
    hcryp->Instance->IVR1 = *(uint32_t *)(hcryp->Init.pInitVect + 2U);
    hcryp->Instance->IVR0 = *(uint32_t *)(hcryp->Init.pInitVect + 3U);

    /* Enable the CRYP peripheral */
    __HAL_CRYP_ENABLE(hcryp);

    /* just wait for hash computation */
    count = CRYP_TIMEOUT_GCMCCMINITPHASE;
    do
    {
      count-- ;
      if (count == 0U)
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
    while (HAL_IS_BIT_CLR(hcryp->Instance->SR, AES_SR_CCF));

    /* Clear CCF flag */
    __HAL_CRYP_CLEAR_FLAG(hcryp, CRYP_CCF_CLEAR);

    /***************************** Header phase *********************************/

    /* Select header phase */
    CRYP_SET_PHASE(hcryp, CRYP_PHASE_HEADER);

    /* Enable computation complete flag and error interrupts */
    __HAL_CRYP_ENABLE_IT(hcryp, CRYP_IT_CCFIE | CRYP_IT_ERRIE);

    /* Enable the CRYP peripheral */
    __HAL_CRYP_ENABLE(hcryp);

    if (hcryp->Init.HeaderSize == 0U) /*header phase is  skipped*/
    {
      /* Set the phase */
      hcryp->Phase = CRYP_PHASE_PROCESS;

      /* Select payload phase once the header phase is performed */
      MODIFY_REG(hcryp->Instance->CR, AES_CR_GCMPH, CRYP_PHASE_PAYLOAD);

      /* Set to 0 the number of non-valid bytes using NPBLB register*/
      MODIFY_REG(hcryp->Instance->CR, AES_CR_NPBLB, 0U);

      /* Write the payload Input block in the IN FIFO */
      if (hcryp->Size == 0U)
      {
        /* Disable interrupts */
        __HAL_CRYP_DISABLE_IT(hcryp, CRYP_IT_CCFIE | CRYP_IT_ERRIE);

        /* Change the CRYP state */
        hcryp->State = HAL_CRYP_STATE_READY;

        /* Process unlocked */
        __HAL_UNLOCK(hcryp);
      }
      else if (hcryp->Size >= 16U)
      {
        hcryp->Instance->DINR  = *(uint32_t *)(hcryp->pCrypInBuffPtr + hcryp->CrypInCount);
        hcryp->CrypInCount++;
        hcryp->Instance->DINR  = *(uint32_t *)(hcryp->pCrypInBuffPtr + hcryp->CrypInCount);
        hcryp->CrypInCount++;
        hcryp->Instance->DINR  = *(uint32_t *)(hcryp->pCrypInBuffPtr + hcryp->CrypInCount);
        hcryp->CrypInCount++;
        hcryp->Instance->DINR  = *(uint32_t *)(hcryp->pCrypInBuffPtr + hcryp->CrypInCount);
        hcryp->CrypInCount++;
        if ((hcryp->CrypInCount ==  (hcryp->Size / 4U)) && ((hcryp->Size % 16U) == 0U))  
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
      else /* Size < 16Bytes  : first block is the last block*/
      {
        /* Workaround not implemented for TinyAES2*/
        /* Size should be %4  otherwise Tag will  be incorrectly generated for GCM Encryption:
        Workaround is implemented in polling mode, so if last block of
        payload <128bit do not use CRYP_Encrypt_IT otherwise TAG is incorrectly generated for GCM Encryption. */


        /* Compute the number of padding bytes in last block of payload */
        npblb = 16U - ((uint32_t)hcryp->Size);

        if ((hcryp->Instance->CR & AES_CR_MODE) == CRYP_OPERATINGMODE_ENCRYPT)
        {
          /* Set to 0 the number of non-valid bytes using NPBLB register*/
          MODIFY_REG(hcryp->Instance->CR, AES_CR_NPBLB, npblb << 20U);
        }

        /* Number of valid words (lastwordsize) in last block */
        if ((npblb % 4U) == 0U)
        {
          lastwordsize = (16U - npblb) / 4U;
        }
        else
        {
          lastwordsize = ((16U - npblb) / 4U) + 1U;
        }

        /*  last block optionally pad the data with zeros*/
        for (loopcounter = 0U; loopcounter < lastwordsize ; loopcounter++)
        {
          hcryp->Instance->DINR = *(uint32_t *)(hcryp->pCrypInBuffPtr + hcryp->CrypInCount);
          hcryp->CrypInCount++;
        }
        while (loopcounter < 4U)
        {
          /* pad the data with zeros to have a complete block */
          hcryp->Instance->DINR = 0x0U;
          loopcounter++;
        }
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
    /* Enter header data */
    /* Cher first whether header length is small enough to enter the full header in one shot */
    else if (headersize_in_bytes <= 16U)
    {
      /* Write header data, padded with zeros if need be */
      for (loopcounter = 0U; (loopcounter < (headersize_in_bytes / 4U)); loopcounter++)
      {
        hcryp->Instance->DINR = *(uint32_t *)(hcryp->Init.Header + hcryp->CrypHeaderCount);
        hcryp->CrypHeaderCount++ ;
      }
      /* If the header size is a multiple of words */
      if ((headersize_in_bytes % 4U) == 0U)
      {
        /* Pad the data with zeros to have a complete block */
        while (loopcounter < 4U)
        {
          hcryp->Instance->DINR = 0x0U;
          loopcounter++;
          hcryp->CrypHeaderCount++;
        }
      }
      else
      {
        /* Enter last bytes, padded with zeros */
        tmp =  *(uint32_t *)(hcryp->Init.Header + hcryp->CrypHeaderCount);
        tmp &= mask[(hcryp->Init.DataType * 2U) + (headersize_in_bytes % 4U)];
        hcryp->Instance->DINR = tmp;
        loopcounter++;
        hcryp->CrypHeaderCount++ ;
        /* Pad the data with zeros to have a complete block */
      while (loopcounter < 4U)
      {
        hcryp->Instance->DINR = 0x0U;
        loopcounter++;
          hcryp->CrypHeaderCount++;
        }
      }
    }
    else
    {
      /* Write the first input header block in the Input FIFO,
         the following header data will be fed after interrupt occurrence */
      hcryp->Instance->DINR  = *(uint32_t *)(hcryp->Init.Header + hcryp->CrypHeaderCount);
      hcryp->CrypHeaderCount++;
      hcryp->Instance->DINR  = *(uint32_t *)(hcryp->Init.Header + hcryp->CrypHeaderCount);
      hcryp->CrypHeaderCount++;
      hcryp->Instance->DINR  = *(uint32_t *)(hcryp->Init.Header + hcryp->CrypHeaderCount);
      hcryp->CrypHeaderCount++;
      hcryp->Instance->DINR  = *(uint32_t *)(hcryp->Init.Header + hcryp->CrypHeaderCount);
      hcryp->CrypHeaderCount++;
    }

  } /* end of if (DoKeyIVConfig == 1U) */
  else  /* Key and IV have already been configured,
          header has already been processed;
          only process here message payload */
  {

    /* Enable computation complete flag and error interrupts */
    __HAL_CRYP_ENABLE_IT(hcryp, CRYP_IT_CCFIE | CRYP_IT_ERRIE);

    /* Set to 0 the number of non-valid bytes using NPBLB register*/
    MODIFY_REG(hcryp->Instance->CR, AES_CR_NPBLB, 0U);

    /* Write the payload Input block in the IN FIFO */
    if (hcryp->Size == 0U)
    {
      /* Disable interrupts */
      __HAL_CRYP_DISABLE_IT(hcryp, CRYP_IT_CCFIE | CRYP_IT_ERRIE);

      /* Change the CRYP state */
      hcryp->State = HAL_CRYP_STATE_READY;

      /* Process unlocked */
      __HAL_UNLOCK(hcryp);
    }
    else if (hcryp->Size >= 16U)
    {
      hcryp->Instance->DINR  = *(uint32_t *)(hcryp->pCrypInBuffPtr + hcryp->CrypInCount);
      hcryp->CrypInCount++;
      hcryp->Instance->DINR  = *(uint32_t *)(hcryp->pCrypInBuffPtr + hcryp->CrypInCount);
      hcryp->CrypInCount++;
      hcryp->Instance->DINR  = *(uint32_t *)(hcryp->pCrypInBuffPtr + hcryp->CrypInCount);
      hcryp->CrypInCount++;
      hcryp->Instance->DINR  = *(uint32_t *)(hcryp->pCrypInBuffPtr + hcryp->CrypInCount);
      hcryp->CrypInCount++;
      if ((hcryp->CrypInCount ==  (hcryp->Size / 4U)) && ((hcryp->Size % 16U) == 0U)) 
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
    else /* Size < 16Bytes  : first block is the last block*/
    {
      /* Workaround not implemented for TinyAES2*/
      /* Size should be %4  otherwise Tag will  be incorrectly generated for GCM Encryption:
      Workaround is implemented in polling mode, so if last block of
      payload <128bit do not use CRYP_Encrypt_IT otherwise TAG is incorrectly generated for GCM Encryption. */


      /* Compute the number of padding bytes in last block of payload */
      npblb = 16U - ((uint32_t)hcryp->Size);

      if ((hcryp->Instance->CR & AES_CR_MODE) == CRYP_OPERATINGMODE_ENCRYPT)
      {
        /* Set to 0 the number of non-valid bytes using NPBLB register*/
        MODIFY_REG(hcryp->Instance->CR, AES_CR_NPBLB, npblb << 20U);
      }

      /* Number of valid words (lastwordsize) in last block */
      if ((npblb % 4U) == 0U)
      {
        lastwordsize = (16U - npblb) / 4U;
      }
      else
      {
        lastwordsize = ((16U - npblb) / 4U) + 1U;
      }

      /*  last block optionally pad the data with zeros*/
      for (loopcounter = 0U; loopcounter < lastwordsize ; loopcounter++)
      {
        hcryp->Instance->DINR = *(uint32_t *)(hcryp->pCrypInBuffPtr + hcryp->CrypInCount);
        hcryp->CrypInCount++;
      }
      while (loopcounter < 4U)
      {
        /* pad the data with zeros to have a complete block */
        hcryp->Instance->DINR = 0x0U;
        loopcounter++;
      }
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

  /* Return function status */
  return HAL_OK;
}


/**
  * @brief  Encryption/Decryption process in AES GCM mode and prepare the authentication TAG using DMA
  * @param  hcryp pointer to a CRYP_HandleTypeDef structure that contains
  *         the configuration information for CRYP module
  * @retval HAL status
  */
static HAL_StatusTypeDef CRYP_AESGCM_Process_DMA(CRYP_HandleTypeDef *hcryp)
{
  uint32_t count;
  uint32_t DoKeyIVConfig = 1U; /* By default, carry out peripheral Key and IV configuration */

  if (hcryp->Init.KeyIVConfigSkip == CRYP_KEYIVCONFIG_ONCE)
  {
    if (hcryp->KeyIVConfig == 1U)
    {
      /* If the Key and IV configuration has to be done only once
         and if it has already been done, skip it */
      DoKeyIVConfig = 0U;
      hcryp->SizesSum += hcryp->Size; /* Compute message total payload length */
    }
    else
    {
      /* If the Key and IV configuration has to be done only once
         and if it has not been done already, do it and set KeyIVConfig
         to keep track it won't have to be done again next time */
      hcryp->KeyIVConfig = 1U;
      hcryp->SizesSum = hcryp->Size; /* Merely store payload length */
    }
  }
  else
  {
    hcryp->SizesSum = hcryp->Size;
  }

  if (DoKeyIVConfig == 1U)
  {

    /*  Reset CrypHeaderCount */
    hcryp->CrypHeaderCount = 0U;

    /*************************** Init phase ************************************/

    CRYP_SET_PHASE(hcryp, CRYP_PHASE_INIT);

    /* Set the key */
    CRYP_SetKey(hcryp, hcryp->Init.KeySize);

    /* Set the initialization vector and the counter : Initial Counter Block (ICB)*/
    hcryp->Instance->IVR3 = *(uint32_t *)(hcryp->Init.pInitVect);
    hcryp->Instance->IVR2 = *(uint32_t *)(hcryp->Init.pInitVect + 1U);
    hcryp->Instance->IVR1 = *(uint32_t *)(hcryp->Init.pInitVect + 2U);
    hcryp->Instance->IVR0 = *(uint32_t *)(hcryp->Init.pInitVect + 3U);

    /* Enable the CRYP peripheral */
    __HAL_CRYP_ENABLE(hcryp);

    /* just wait for hash computation */
    count = CRYP_TIMEOUT_GCMCCMINITPHASE;
    do
    {
      count-- ;
      if (count == 0U)
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
    while (HAL_IS_BIT_CLR(hcryp->Instance->SR, AES_SR_CCF));

    /* Clear CCF flag */
    __HAL_CRYP_CLEAR_FLAG(hcryp, CRYP_CCF_CLEAR);

    /************************ Header phase *************************************/

    if (CRYP_GCMCCM_SetHeaderPhase_DMA(hcryp) != HAL_OK)
    {
      return HAL_ERROR;
    }

  }
  else
  {
    /* Initialization and header phases already done, only do payload phase */
    if (CRYP_GCMCCM_SetPayloadPhase_DMA(hcryp) != HAL_OK)
    {
      return HAL_ERROR;
    }
  } /* if (DoKeyIVConfig == 1U) */

  /* Return function status */
  return HAL_OK;
}


/**
  * @brief  AES CCM encryption/decryption processing in polling mode
  *         for TinyAES peripheral, no encrypt/decrypt performed, only authentication preparation.
  * @param  hcryp pointer to a CRYP_HandleTypeDef structure that contains
  *         the configuration information for CRYP module
  * @param  Timeout Timeout duration
  * @retval HAL status
  */
static HAL_StatusTypeDef CRYP_AESCCM_Process(CRYP_HandleTypeDef *hcryp, uint32_t Timeout)
{
  uint32_t tickstart;
  uint32_t wordsize = ((uint32_t)hcryp->Size / 4U) ;
  uint32_t loopcounter;
  uint32_t npblb;
  uint32_t lastwordsize;
  uint32_t temp[4] ;  /* Temporary CrypOutBuff */
  uint32_t incount;  /* Temporary CrypInCount Value */
  uint32_t outcount;  /* Temporary CrypOutCount Value */
  uint32_t DoKeyIVConfig = 1U; /* By default, carry out peripheral Key and IV configuration */

  if (hcryp->Init.KeyIVConfigSkip == CRYP_KEYIVCONFIG_ONCE)
  {
    if (hcryp->KeyIVConfig == 1U)
    {
      /* If the Key and IV configuration has to be done only once
         and if it has already been done, skip it */
      DoKeyIVConfig = 0U;
      hcryp->SizesSum += hcryp->Size; /* Compute message total payload length */
    }
    else
    {
      /* If the Key and IV configuration has to be done only once
         and if it has not been done already, do it and set KeyIVConfig
         to keep track it won't have to be done again next time */
      hcryp->KeyIVConfig = 1U;
      hcryp->SizesSum = hcryp->Size; /* Merely store payload length */
    }
  }
  else
  {
    hcryp->SizesSum = hcryp->Size;
  }

  if (DoKeyIVConfig == 1U)
  {
    /*  Reset CrypHeaderCount */
    hcryp->CrypHeaderCount = 0U;

    /********************** Init phase ******************************************/

    CRYP_SET_PHASE(hcryp, CRYP_PHASE_INIT);

    /* Set the key */
    CRYP_SetKey(hcryp, hcryp->Init.KeySize);

    /* Set the initialization vector (IV) with B0 */
    hcryp->Instance->IVR3 = *(uint32_t *)(hcryp->Init.B0);
    hcryp->Instance->IVR2 = *(uint32_t *)(hcryp->Init.B0 + 1U);
    hcryp->Instance->IVR1 = *(uint32_t *)(hcryp->Init.B0 + 2U);
    hcryp->Instance->IVR0 = *(uint32_t *)(hcryp->Init.B0 + 3U);

    /* Enable the CRYP peripheral */
    __HAL_CRYP_ENABLE(hcryp);

    /* just wait for hash computation */
    if (CRYP_WaitOnCCFlag(hcryp, Timeout) != HAL_OK)
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

    /************************ Header phase *************************************/
    /* Header block(B1) : associated data length expressed in bytes concatenated
    with Associated Data (A)*/
    if (CRYP_GCMCCM_SetHeaderPhase(hcryp,  Timeout) != HAL_OK)
    {
      return HAL_ERROR;
    }

    /*************************Payload phase ************************************/

    /* Set the phase */
    hcryp->Phase = CRYP_PHASE_PROCESS;

    /* Select payload phase once the header phase is performed */
    MODIFY_REG(hcryp->Instance->CR, AES_CR_GCMPH, CRYP_PHASE_PAYLOAD);

    /* Set to 0 the number of non-valid bytes using NPBLB register*/
    MODIFY_REG(hcryp->Instance->CR, AES_CR_NPBLB, 0U);

  } /* if (DoKeyIVConfig == 1U) */

  if ((hcryp->Size % 16U) != 0U)
  {
    /* recalculate  wordsize */
    wordsize = ((wordsize / 4U) * 4U) ;
  }
  /* Get tick */
  tickstart = HAL_GetTick();

  /* Write input data and get output data */
  incount = hcryp->CrypInCount;
  outcount = hcryp->CrypOutCount;
  while ((incount < wordsize) && (outcount < wordsize))
  {
    /* Write plain data and get cipher data */
    CRYP_AES_ProcessData(hcryp, Timeout);

    /* Check for the Timeout */
    if (Timeout != HAL_MAX_DELAY)
    {
      if (((HAL_GetTick() - tickstart) > Timeout) ||(Timeout == 0U))
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
    incount = hcryp->CrypInCount;
    outcount = hcryp->CrypOutCount;
  }

  if ((hcryp->Size % 16U) != 0U)
  {
    /* Compute the number of padding bytes in last block of payload */
    npblb = ((((uint32_t)hcryp->Size / 16U) + 1U) * 16U) - ((uint32_t)hcryp->Size);

    if ((hcryp->Instance->CR & AES_CR_MODE) == CRYP_OPERATINGMODE_DECRYPT)
    {
      /* Set Npblb in case of AES CCM payload decryption to get right tag  */
      MODIFY_REG(hcryp->Instance->CR, AES_CR_NPBLB, npblb << 20);

    }
    /* Number of valid words (lastwordsize) in last block */
    if ((npblb % 4U) == 0U)
    {
      lastwordsize = (16U - npblb) / 4U;
    }
    else
    {
      lastwordsize = ((16U - npblb) / 4U) + 1U;
    }

    /* Write the last input block in the IN FIFO */
    for (loopcounter = 0U; loopcounter < lastwordsize; loopcounter ++)
    {
      hcryp->Instance->DINR  = *(uint32_t *)(hcryp->pCrypInBuffPtr + hcryp->CrypInCount);
      hcryp->CrypInCount++;
    }

    /* Pad the data with zeros to have a complete block */
    while (loopcounter < 4U)
    {
      hcryp->Instance->DINR  = 0U;
      loopcounter++;
    }
    /* just wait for hash computation */
    if (CRYP_WaitOnCCFlag(hcryp, Timeout) != HAL_OK)
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

    for (loopcounter = 0U; loopcounter < 4U; loopcounter++)
    {
      /* Read the output block from the output FIFO and put them in temporary buffer then get CrypOutBuff from temporary buffer */
      temp[loopcounter] = hcryp->Instance->DOUTR;
    }
    for (loopcounter = 0U; loopcounter<lastwordsize; loopcounter++)
    {
      *(uint32_t *)(hcryp->pCrypOutBuffPtr + hcryp->CrypOutCount) = temp[loopcounter];
      hcryp->CrypOutCount++;
    }
  }

  /* Return function status */
  return HAL_OK;
}

/**
  * @brief  AES CCM encryption/decryption process in interrupt mode
  *         for TinyAES peripheral, no encrypt/decrypt performed, only authentication preparation.
  * @param  hcryp pointer to a CRYP_HandleTypeDef structure that contains
  *         the configuration information for CRYP module
  * @retval HAL status
  */
static HAL_StatusTypeDef CRYP_AESCCM_Process_IT(CRYP_HandleTypeDef *hcryp)
{
  __IO uint32_t count = 0U;
  uint32_t loopcounter;
  uint32_t lastwordsize;
  uint32_t npblb;
  uint32_t mode;
  uint32_t DoKeyIVConfig = 1U; /* By default, carry out peripheral Key and IV configuration */
  uint32_t headersize_in_bytes;
  uint32_t tmp;
  uint32_t mask[12] = {0x0U, 0xFF000000U, 0xFFFF0000U, 0xFFFFFF00U,  /* 32-bit data type */
                       0x0U, 0x0000FF00U, 0x0000FFFFU, 0xFF00FFFFU,  /* 16-bit data type */
                       0x0U, 0x000000FFU, 0x0000FFFFU, 0x00FFFFFFU}; /*  8-bit data type */

#if (USE_HAL_CRYP_SUSPEND_RESUME == 1U)
  if ((hcryp->Phase == CRYP_PHASE_HEADER_SUSPENDED) || (hcryp->Phase == CRYP_PHASE_PAYLOAD_SUSPENDED))
  {
    CRYP_PhaseProcessingResume(hcryp);
    return HAL_OK;
  }
#endif /* USE_HAL_CRYP_SUSPEND_RESUME */

  if (hcryp->Init.KeyIVConfigSkip == CRYP_KEYIVCONFIG_ONCE)
  {
    if (hcryp->KeyIVConfig == 1U)
    {
      /* If the Key and IV configuration has to be done only once
         and if it has already been done, skip it */
      DoKeyIVConfig = 0U;
      hcryp->SizesSum += hcryp->Size; /* Compute message total payload length */
    }
    else
    {
      /* If the Key and IV configuration has to be done only once
         and if it has not been done already, do it and set KeyIVConfig
         to keep track it won't have to be done again next time */
      hcryp->KeyIVConfig = 1U;
      hcryp->SizesSum = hcryp->Size; /* Merely store payload length */
    }
  }
  else
  {
    hcryp->SizesSum = hcryp->Size;
  }

  /* Configure Key, IV and process message (header and payload) */
  if (DoKeyIVConfig == 1U)
  {
    /*  Reset CrypHeaderCount */
    hcryp->CrypHeaderCount = 0U;

    /********************** Init phase ******************************************/

    CRYP_SET_PHASE(hcryp, CRYP_PHASE_INIT);

    /* Set the key */
    CRYP_SetKey(hcryp, hcryp->Init.KeySize);

    /* Set the initialization vector (IV) with B0 */
    hcryp->Instance->IVR3 = *(uint32_t *)(hcryp->Init.B0);
    hcryp->Instance->IVR2 = *(uint32_t *)(hcryp->Init.B0 + 1U);
    hcryp->Instance->IVR1 = *(uint32_t *)(hcryp->Init.B0 + 2U);
    hcryp->Instance->IVR0 = *(uint32_t *)(hcryp->Init.B0 + 3U);

    /* Enable the CRYP peripheral */
    __HAL_CRYP_ENABLE(hcryp);

    /* just wait for hash computation */
    count = CRYP_TIMEOUT_GCMCCMINITPHASE;
    do
    {
      count-- ;
      if (count == 0U)
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
    while (HAL_IS_BIT_CLR(hcryp->Instance->SR, AES_SR_CCF));

    /* Clear CCF flag */
    __HAL_CRYP_CLEAR_FLAG(hcryp, CRYP_CCF_CLEAR);

    /***************************** Header phase *********************************/

    /* Select header phase */
    CRYP_SET_PHASE(hcryp, CRYP_PHASE_HEADER);

    /* Enable computation complete flag and error interrupts */
    __HAL_CRYP_ENABLE_IT(hcryp, CRYP_IT_CCFIE | CRYP_IT_ERRIE);

    /* Enable the CRYP peripheral */
    __HAL_CRYP_ENABLE(hcryp);

    if (hcryp->Init.HeaderWidthUnit == CRYP_HEADERWIDTHUNIT_WORD)
    {
      headersize_in_bytes = hcryp->Init.HeaderSize * 4U;
    }
    else
    {
      headersize_in_bytes = hcryp->Init.HeaderSize;
    }

    if (headersize_in_bytes == 0U) /* Header phase is  skipped */
    {
      /* Set the phase */
      hcryp->Phase = CRYP_PHASE_PROCESS;
      /* Select payload phase once the header phase is performed */
      CRYP_SET_PHASE(hcryp, CRYP_PHASE_PAYLOAD);
      /* Set to 0 the number of non-valid bytes using NPBLB register*/
      MODIFY_REG(hcryp->Instance->CR, AES_CR_NPBLB, 0U);

      if (hcryp->Init.Algorithm == CRYP_AES_CCM)
      {
        /* Increment CrypHeaderCount to pass in CRYP_GCMCCM_SetPayloadPhase_IT */
        hcryp->CrypHeaderCount++;
      }
      /* Write the payload Input block in the IN FIFO */
      if (hcryp->Size == 0U)
      {
        /* Disable interrupts */
        __HAL_CRYP_DISABLE_IT(hcryp, CRYP_IT_CCFIE | CRYP_IT_ERRIE);

        /* Change the CRYP state */
        hcryp->State = HAL_CRYP_STATE_READY;

        /* Process unlocked */
        __HAL_UNLOCK(hcryp);
      }
      else if (hcryp->Size >= 16U)
      {
        hcryp->Instance->DINR  = *(uint32_t *)(hcryp->pCrypInBuffPtr + hcryp->CrypInCount);
        hcryp->CrypInCount++;
        hcryp->Instance->DINR  = *(uint32_t *)(hcryp->pCrypInBuffPtr + hcryp->CrypInCount);
        hcryp->CrypInCount++;
        hcryp->Instance->DINR  = *(uint32_t *)(hcryp->pCrypInBuffPtr + hcryp->CrypInCount);
        hcryp->CrypInCount++;
        hcryp->Instance->DINR  = *(uint32_t *)(hcryp->pCrypInBuffPtr + hcryp->CrypInCount);
        hcryp->CrypInCount++;

        if ((hcryp->CrypInCount ==  (hcryp->Size / 4U)) && ((hcryp->Size % 16U) == 0U))
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
      else /* Size < 4 words  : first block is the last block*/
      {
        /* Compute the number of padding bytes in last block of payload */
        npblb = 16U - (uint32_t)hcryp->Size;

        mode = hcryp->Instance->CR & AES_CR_MODE;
        if (((mode == CRYP_OPERATINGMODE_ENCRYPT) && (hcryp->Init.Algorithm == CRYP_AES_GCM_GMAC)) ||
            ((mode == CRYP_OPERATINGMODE_DECRYPT) && (hcryp->Init.Algorithm == CRYP_AES_CCM)))
        {
          /* Specify the number of non-valid bytes using NPBLB register*/
          MODIFY_REG(hcryp->Instance->CR, AES_CR_NPBLB, npblb << 20U);
        }

        /* Number of valid words (lastwordsize) in last block */
        if ((npblb % 4U) == 0U)
        {
          lastwordsize = (16U - npblb) / 4U;
        }
        else
        {
          lastwordsize = ((16U - npblb) / 4U) + 1U;
        }

        /*  Last block optionally pad the data with zeros*/
        for (loopcounter = 0U; loopcounter < lastwordsize; loopcounter++)
        {
          hcryp->Instance->DINR = *(uint32_t *)(hcryp->pCrypInBuffPtr + hcryp->CrypInCount);
          hcryp->CrypInCount++;
        }
        while (loopcounter < 4U)
        {
          /* Pad the data with zeros to have a complete block */
          hcryp->Instance->DINR = 0x0U;
          loopcounter++;
        }
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
    /* Enter header data */
    /* Check first whether header length is small enough to enter the full header in one shot */
    else if (headersize_in_bytes <= 16U)
    {
      for (loopcounter = 0U; (loopcounter < (headersize_in_bytes / 4U)); loopcounter++)
      {
        hcryp->Instance->DINR = *(uint32_t *)(hcryp->Init.Header + hcryp->CrypHeaderCount);
        hcryp->CrypHeaderCount++ ;
      }
      /* If the header size is a multiple of words */
      if ((headersize_in_bytes % 4U) == 0U)
      {
        /* Pad the data with zeros to have a complete block */
        while (loopcounter < 4U)
        {
          hcryp->Instance->DINR = 0x0U;
          loopcounter++;
        }
      }
      else
      {
        /* Enter last bytes, padded with zeros */
        tmp =  *(uint32_t *)(hcryp->Init.Header + hcryp->CrypHeaderCount);
        tmp &= mask[(hcryp->Init.DataType * 2U) + (headersize_in_bytes % 4U)];
        hcryp->Instance->DINR = tmp;
        hcryp->CrypHeaderCount++;
        loopcounter++;
        /* Pad the data with zeros to have a complete block */
      while (loopcounter < 4U)
      {
        hcryp->Instance->DINR = 0x0U;
        loopcounter++;
      }
    }
      /* Call Input transfer complete callback */
#if (USE_HAL_CRYP_REGISTER_CALLBACKS == 1U)
      /*Call registered Input complete callback*/
      hcryp->InCpltCallback(hcryp);
#else
      /*Call legacy weak Input complete callback*/
      HAL_CRYP_InCpltCallback(hcryp);
#endif /* USE_HAL_CRYP_REGISTER_CALLBACKS */
    }
    else
    {
      /* Write the first input header block in the Input FIFO,
         the following header data will be fed after interrupt occurrence */
      hcryp->Instance->DINR  = *(uint32_t *)(hcryp->Init.Header + hcryp->CrypHeaderCount);
      hcryp->CrypHeaderCount++;
      hcryp->Instance->DINR  = *(uint32_t *)(hcryp->Init.Header + hcryp->CrypHeaderCount);
      hcryp->CrypHeaderCount++;
      hcryp->Instance->DINR  = *(uint32_t *)(hcryp->Init.Header + hcryp->CrypHeaderCount);
      hcryp->CrypHeaderCount++;
      hcryp->Instance->DINR  = *(uint32_t *)(hcryp->Init.Header + hcryp->CrypHeaderCount);
      hcryp->CrypHeaderCount++;
    }/* if (hcryp->Init.HeaderSize == 0U) */ /* Header phase is  skipped*/
  } /* end of if (dokeyivconfig == 1U) */
  else  /* Key and IV have already been configured,
          header has already been processed;
          only process here message payload */
  {
    /* Write the payload Input block in the IN FIFO */
    if (hcryp->Size == 0U)
    {
      /* Disable interrupts */
      __HAL_CRYP_DISABLE_IT(hcryp, CRYP_IT_CCFIE | CRYP_IT_ERRIE);

      /* Change the CRYP state */
      hcryp->State = HAL_CRYP_STATE_READY;

      /* Process unlocked */
      __HAL_UNLOCK(hcryp);
    }
    else if (hcryp->Size >= 16U)
    {
      hcryp->Instance->DINR  = *(uint32_t *)(hcryp->pCrypInBuffPtr + hcryp->CrypInCount);
      hcryp->CrypInCount++;
      hcryp->Instance->DINR  = *(uint32_t *)(hcryp->pCrypInBuffPtr + hcryp->CrypInCount);
      hcryp->CrypInCount++;
      hcryp->Instance->DINR  = *(uint32_t *)(hcryp->pCrypInBuffPtr + hcryp->CrypInCount);
      hcryp->CrypInCount++;
      hcryp->Instance->DINR  = *(uint32_t *)(hcryp->pCrypInBuffPtr + hcryp->CrypInCount);
      hcryp->CrypInCount++;

      if ((hcryp->CrypInCount ==  (hcryp->Size / 4U)) && ((hcryp->Size % 16U) == 0U))
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
    else /* Size < 4 words  : first block is the last block*/
    {
      /* Compute the number of padding bytes in last block of payload */
      npblb = 16U - (uint32_t)hcryp->Size;

      mode = hcryp->Instance->CR & AES_CR_MODE;
      if (((mode == CRYP_OPERATINGMODE_ENCRYPT) && (hcryp->Init.Algorithm == CRYP_AES_GCM_GMAC)) ||
          ((mode == CRYP_OPERATINGMODE_DECRYPT) && (hcryp->Init.Algorithm == CRYP_AES_CCM)))
      {
        /* Specify the number of non-valid bytes using NPBLB register*/
        MODIFY_REG(hcryp->Instance->CR, AES_CR_NPBLB, npblb << 20U);
      }

      /* Number of valid words (lastwordsize) in last block */
      if ((npblb % 4U) == 0U)
      {
        lastwordsize = (16U - npblb) / 4U;
      }
      else
      {
        lastwordsize = ((16U - npblb) / 4U) + 1U;
      }

      /*  Last block optionally pad the data with zeros*/
      for (loopcounter = 0U; loopcounter < lastwordsize; loopcounter++)
      {
        hcryp->Instance->DINR = *(uint32_t *)(hcryp->pCrypInBuffPtr + hcryp->CrypInCount);
        hcryp->CrypInCount++;
      }
      while (loopcounter < 4U)
      {
        /* Pad the data with zeros to have a complete block */
        hcryp->Instance->DINR = 0x0U;
        loopcounter++;
      }
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

  /* Return function status */
  return HAL_OK;
}

/**
  * @brief  AES CCM encryption/decryption process in DMA mode
  *         for TinyAES peripheral, no encrypt/decrypt performed, only authentication preparation.
  * @param  hcryp pointer to a CRYP_HandleTypeDef structure that contains
  *         the configuration information for CRYP module
  * @retval HAL status
  */
static HAL_StatusTypeDef CRYP_AESCCM_Process_DMA(CRYP_HandleTypeDef *hcryp)
{
  uint32_t count;
  uint32_t DoKeyIVConfig = 1U; /* By default, carry out peripheral Key and IV configuration */

  if (hcryp->Init.KeyIVConfigSkip == CRYP_KEYIVCONFIG_ONCE)
  {
    if (hcryp->KeyIVConfig == 1U)
    {
      /* If the Key and IV configuration has to be done only once
         and if it has already been done, skip it */
      DoKeyIVConfig = 0U;
      hcryp->SizesSum += hcryp->Size; /* Compute message total payload length */
    }
    else
    {
      /* If the Key and IV configuration has to be done only once
         and if it has not been done already, do it and set KeyIVConfig
         to keep track it won't have to be done again next time */
      hcryp->KeyIVConfig = 1U;
      hcryp->SizesSum = hcryp->Size; /* Merely store payload length */
    }
  }
  else
  {
    hcryp->SizesSum = hcryp->Size;
  }

  if (DoKeyIVConfig == 1U)
  {

    /*  Reset CrypHeaderCount */
    hcryp->CrypHeaderCount = 0U;


    /********************** Init phase ******************************************/

    CRYP_SET_PHASE(hcryp, CRYP_PHASE_INIT);

    /* Set the key */
    CRYP_SetKey(hcryp, hcryp->Init.KeySize);

    /* Set the initialization vector (IV) with B0 */
    hcryp->Instance->IVR3 = *(uint32_t *)(hcryp->Init.B0);
    hcryp->Instance->IVR2 = *(uint32_t *)(hcryp->Init.B0 + 1U);
    hcryp->Instance->IVR1 = *(uint32_t *)(hcryp->Init.B0 + 2U);
    hcryp->Instance->IVR0 = *(uint32_t *)(hcryp->Init.B0 + 3U);

    /* Enable the CRYP peripheral */
    __HAL_CRYP_ENABLE(hcryp);

    /* just wait for hash computation */
    count = CRYP_TIMEOUT_GCMCCMINITPHASE;
    do
    {
      count-- ;
      if (count == 0U)
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
    while (HAL_IS_BIT_CLR(hcryp->Instance->SR, AES_SR_CCF));

    /* Clear CCF flag */
    __HAL_CRYP_CLEAR_FLAG(hcryp, CRYP_CCF_CLEAR);


    /********************* Header phase *****************************************/

    if (CRYP_GCMCCM_SetHeaderPhase_DMA(hcryp) != HAL_OK)
    {
      return HAL_ERROR;
    }

  }
  else
  {
    /* Initialization and header phases already done, only do payload phase */
    if (CRYP_GCMCCM_SetPayloadPhase_DMA(hcryp) != HAL_OK)
    {
      return HAL_ERROR;
    }
  } /* if (DoKeyIVConfig == 1U) */

  /* Return function status */
  return HAL_OK;
}

/**
  * @brief  Sets the payload phase in interrupt mode
  * @param  hcryp pointer to a CRYP_HandleTypeDef structure that contains
  *         the configuration information for CRYP module
  * @retval state
  */
static void CRYP_GCMCCM_SetPayloadPhase_IT(CRYP_HandleTypeDef *hcryp)
{
  uint32_t loopcounter;
  uint32_t temp[4];  /* Temporary CrypOutBuff */
  uint32_t lastwordsize;
  uint32_t npblb;
  uint32_t mode;
  uint16_t incount;  /* Temporary CrypInCount Value */
  uint16_t outcount;  /* Temporary CrypOutCount Value */
  uint32_t i;

  /***************************** Payload phase *******************************/

  /* Read the output block from the output FIFO and put them in temporary buffer then get CrypOutBuff from temporary buffer*/
  for (i = 0U; i < 4U; i++)
  {
    temp[i] = hcryp->Instance->DOUTR;
  }
  i= 0U;
  while((hcryp->CrypOutCount < ((hcryp->Size + 3U)/4U)) && (i<4U))
  {
    *(uint32_t *)(hcryp->pCrypOutBuffPtr + hcryp->CrypOutCount) = temp[i];
    hcryp->CrypOutCount++;
    i++;
  }
  incount = hcryp->CrypInCount;
  outcount = hcryp->CrypOutCount;
  if ((outcount >=  (hcryp->Size / 4U)) && ((incount * 4U) >=  hcryp->Size))
  {

     /* When in CCM with Key and IV configuration skipped, don't disable interruptions */
     if (!((hcryp->Init.Algorithm == CRYP_AES_CCM) && (hcryp->KeyIVConfig == 1U)))
     {
      /* Disable computation complete flag and errors interrupts */
      __HAL_CRYP_DISABLE_IT(hcryp, CRYP_IT_CCFIE | CRYP_IT_ERRIE);
     }

    /* Change the CRYP state */
    hcryp->State = HAL_CRYP_STATE_READY;

    /* Process unlocked */
    __HAL_UNLOCK(hcryp);

    /* Call output transfer complete callback */
#if (USE_HAL_CRYP_REGISTER_CALLBACKS == 1U)
    /*Call registered Output complete callback*/
    hcryp->OutCpltCallback(hcryp);
#else
    /*Call legacy weak Output complete callback*/
    HAL_CRYP_OutCpltCallback(hcryp);
#endif /* USE_HAL_CRYP_REGISTER_CALLBACKS */
  }

  else if (((hcryp->Size / 4U) - (hcryp->CrypInCount)) >= 4U)
  {

#if (USE_HAL_CRYP_SUSPEND_RESUME == 1U)
    /* If suspension flag has been raised, suspend processing
       only if not already at the end of the payload */
    if (hcryp->SuspendRequest == HAL_CRYP_SUSPEND)
    {
      /* Clear CCF Flag */
      __HAL_CRYP_CLEAR_FLAG(hcryp, CRYP_CCF_CLEAR);

      /* reset SuspendRequest */
      hcryp->SuspendRequest = HAL_CRYP_SUSPEND_NONE;
      /* Disable Computation Complete Flag and Errors Interrupts */
      __HAL_CRYP_DISABLE_IT(hcryp, CRYP_IT_CCFIE|CRYP_IT_ERRIE);
      /* Change the CRYP state */
      hcryp->State = HAL_CRYP_STATE_SUSPENDED;
      /* Mark that the payload phase is suspended */
      hcryp->Phase = CRYP_PHASE_PAYLOAD_SUSPENDED;

     /* Process Unlocked */
      __HAL_UNLOCK(hcryp);
    }
    else
#endif /* USE_HAL_CRYP_SUSPEND_RESUME */
    {
    /* Write the input block in the IN FIFO */
    hcryp->Instance->DINR  = *(uint32_t *)(hcryp->pCrypInBuffPtr + hcryp->CrypInCount);
    hcryp->CrypInCount++;
    hcryp->Instance->DINR  = *(uint32_t *)(hcryp->pCrypInBuffPtr + hcryp->CrypInCount);
    hcryp->CrypInCount++;
    hcryp->Instance->DINR  = *(uint32_t *)(hcryp->pCrypInBuffPtr + hcryp->CrypInCount);
    hcryp->CrypInCount++;
    hcryp->Instance->DINR  = *(uint32_t *)(hcryp->pCrypInBuffPtr + hcryp->CrypInCount);
    hcryp->CrypInCount++;
    if ((hcryp->CrypInCount ==  (hcryp->Size / 4U)) && ((hcryp->Size % 16U) == 0U))  
    {
      /* Call input transfer complete callback */
#if (USE_HAL_CRYP_REGISTER_CALLBACKS == 1U)
      /*Call registered Input complete callback*/
      hcryp->InCpltCallback(hcryp);
#else
      /*Call legacy weak Input complete callback*/
      HAL_CRYP_InCpltCallback(hcryp);
#endif /* USE_HAL_CRYP_REGISTER_CALLBACKS */
    }
  }
  }
  else /* Last block of payload < 128bit*/
  {
    /* Compute the number of padding bytes in last block of payload */
    npblb = ((((uint32_t)hcryp->Size / 16U) + 1U) * 16U) - ((uint32_t)hcryp->Size);

    mode = hcryp->Instance->CR & AES_CR_MODE;
    if (((mode == CRYP_OPERATINGMODE_ENCRYPT) && (hcryp->Init.Algorithm == CRYP_AES_GCM_GMAC)) ||
        ((mode == CRYP_OPERATINGMODE_DECRYPT) && (hcryp->Init.Algorithm == CRYP_AES_CCM)))
    {
      /* Specify the number of non-valid bytes using NPBLB register*/
      MODIFY_REG(hcryp->Instance->CR, AES_CR_NPBLB, npblb << 20U);
    }

    /* Number of valid words (lastwordsize) in last block */
    if ((npblb % 4U) == 0U)
    {
      lastwordsize = (16U - npblb) / 4U;
    }
    else
    {
      lastwordsize = ((16U - npblb) / 4U) + 1U;
    }

    /*  Last block optionally pad the data with zeros*/
    for (loopcounter = 0U; loopcounter < lastwordsize; loopcounter++)
    {
      hcryp->Instance->DINR = *(uint32_t *)(hcryp->pCrypInBuffPtr + hcryp->CrypInCount);
      hcryp->CrypInCount++;
    }
    while (loopcounter < 4U)
    {
      /* pad the data with zeros to have a complete block */
      hcryp->Instance->DINR = 0x0U;
      loopcounter++;
    }
      /* Call input transfer complete callback */
#if (USE_HAL_CRYP_REGISTER_CALLBACKS == 1U)
      /*Call registered Input complete callback*/
      hcryp->InCpltCallback(hcryp);
#else
      /*Call legacy weak Input complete callback*/
      HAL_CRYP_InCpltCallback(hcryp);
#endif /* USE_HAL_CRYP_REGISTER_CALLBACKS */    
  }
}


/**
  * @brief  Sets the payload phase in DMA mode
  * @param  hcryp pointer to a CRYP_HandleTypeDef structure that contains
  *         the configuration information for CRYP module
  * @retval state
  */
static HAL_StatusTypeDef CRYP_GCMCCM_SetPayloadPhase_DMA(CRYP_HandleTypeDef *hcryp)
{
  uint16_t wordsize = hcryp->Size / 4U ;
  uint32_t index;
  uint32_t npblb;
  uint32_t lastwordsize;
  uint32_t temp[4];  /* Temporary CrypOutBuff */
  uint32_t count;
  uint32_t reg;

  /************************ Payload phase ************************************/
  if (hcryp->Size == 0U)
  {
    /* Process unLocked */
    __HAL_UNLOCK(hcryp);

    /* Change the CRYP state and phase */
    hcryp->State = HAL_CRYP_STATE_READY;
  }
  else if (hcryp->Size >= 16U)
  {
    /*DMA transfer must not include the last block in case of Size is not %16 */
    wordsize = wordsize - (wordsize % 4U);

    /*DMA transfer */
    CRYP_SetDMAConfig(hcryp, (uint32_t)(hcryp->pCrypInBuffPtr), wordsize, (uint32_t)(hcryp->pCrypOutBuffPtr));
  }
  else /* length of input data is < 16 */
  {
    /* Compute the number of padding bytes in last block of payload */
    npblb = 16U - (uint32_t)hcryp->Size;

    /* Set Npblb in case of AES GCM payload encryption or AES CCM payload decryption to get right tag*/
    reg = hcryp->Instance->CR & (AES_CR_CHMOD|AES_CR_MODE);
    if ((reg == (CRYP_AES_GCM_GMAC|CRYP_OPERATINGMODE_ENCRYPT)) ||\
        (reg == (CRYP_AES_CCM|CRYP_OPERATINGMODE_DECRYPT)))
    {
      /* Specify the number of non-valid bytes using NPBLB register*/
      MODIFY_REG(hcryp->Instance->CR, AES_CR_NPBLB, npblb << 20U);
    }

    /* Number of valid words (lastwordsize) in last block */
    if ((npblb % 4U) == 0U)
    {
      lastwordsize = (16U - npblb) / 4U;
    }
    else
    {
      lastwordsize = ((16U - npblb) / 4U) + 1U;
    }

    /*  last block optionally pad the data with zeros*/
    for (index = 0U; index < lastwordsize; index ++)
    {
      /* Write the last Input block in the IN FIFO */
      hcryp->Instance->DINR  = *(uint32_t *)(hcryp->pCrypInBuffPtr + hcryp->CrypInCount);
      hcryp->CrypInCount++;
    }
    while (index < 4U)
    {
      /* pad the data with zeros to have a complete block */
      hcryp->Instance->DINR  = 0U;
      index++;
    }
    /* Call the input data transfer complete callback */
#if (USE_HAL_CRYP_REGISTER_CALLBACKS == 1U)
    /*Call registered Input complete callback*/
    hcryp->InCpltCallback(hcryp);
#else
    /*Call legacy weak Input complete callback*/
    HAL_CRYP_InCpltCallback(hcryp);
#endif /* USE_HAL_CRYP_REGISTER_CALLBACKS */    
    /* Wait for CCF flag to be raised */
    count = CRYP_TIMEOUT_GCMCCMHEADERPHASE;
    do
    {
      count-- ;
      if (count == 0U)
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
    while (HAL_IS_BIT_CLR(hcryp->Instance->SR, AES_SR_CCF));

    /* Clear CCF Flag */
    __HAL_CRYP_CLEAR_FLAG(hcryp, CRYP_CCF_CLEAR);

    /*Read the output block from the output FIFO */
    for (index = 0U; index < 4U; index++)
    {
      /* Read the output block from the output FIFO and put them in temporary buffer then get CrypOutBuff from temporary buffer */
      temp[index] = hcryp->Instance->DOUTR;
    }
    for (index = 0U; index < lastwordsize; index++)
    {
      *(uint32_t *)(hcryp->pCrypOutBuffPtr + hcryp->CrypOutCount) = temp[index];
      hcryp->CrypOutCount++;
    }

    /* Change the CRYP state to ready */
    hcryp->State = HAL_CRYP_STATE_READY;

    /* Process unlocked */
    __HAL_UNLOCK(hcryp);

      /* Call Output transfer complete callback */
#if (USE_HAL_CRYP_REGISTER_CALLBACKS == 1U)
      /*Call registered Output complete callback*/
      hcryp->OutCpltCallback(hcryp);
#else
      /*Call legacy weak Output complete callback*/
      HAL_CRYP_OutCpltCallback(hcryp);
#endif /* USE_HAL_CRYP_REGISTER_CALLBACKS */    
  }

  return HAL_OK;
}

/**
  * @brief  Sets the header phase in polling mode
  * @param  hcryp pointer to a CRYP_HandleTypeDef structure that contains
  *         the configuration information for CRYP module(Header & HeaderSize)
  * @param  Timeout Timeout value
  * @retval state
  */
static HAL_StatusTypeDef CRYP_GCMCCM_SetHeaderPhase(CRYP_HandleTypeDef *hcryp, uint32_t Timeout)
{
  uint32_t loopcounter;
  uint32_t size_in_bytes;
  uint32_t tmp;
  uint32_t mask[12] = {0x0U, 0xFF000000U, 0xFFFF0000U, 0xFFFFFF00U,  /* 32-bit data type */
                       0x0U, 0x0000FF00U, 0x0000FFFFU, 0xFF00FFFFU,  /* 16-bit data type */
                       0x0U, 0x000000FFU, 0x0000FFFFU, 0x00FFFFFFU}; /*  8-bit data type */

  /***************************** Header phase for GCM/GMAC or CCM *********************************/
  if (hcryp->Init.HeaderWidthUnit == CRYP_HEADERWIDTHUNIT_WORD)
  {
    size_in_bytes = hcryp->Init.HeaderSize * 4U;
  }
  else
  {
    size_in_bytes = hcryp->Init.HeaderSize;
  }

  if ((size_in_bytes != 0U))
  {
    /* Select header phase */
    CRYP_SET_PHASE(hcryp, CRYP_PHASE_HEADER);

    /* Enable the CRYP peripheral */
    __HAL_CRYP_ENABLE(hcryp);

    /* If size_in_bytes is a multiple of blocks (a multiple of four 32-bits words ) */
    if ((size_in_bytes % 16U) == 0U)
    {
      /*  No padding */
      for (loopcounter = 0U; (loopcounter < (size_in_bytes / 4U)); loopcounter += 4U)
      {
        /* Write the input block in the data input register */
        hcryp->Instance->DINR = *(uint32_t *)(hcryp->Init.Header + hcryp->CrypHeaderCount);
        hcryp->CrypHeaderCount++ ;
        hcryp->Instance->DINR = *(uint32_t *)(hcryp->Init.Header + hcryp->CrypHeaderCount);
        hcryp->CrypHeaderCount++ ;
        hcryp->Instance->DINR  = *(uint32_t *)(hcryp->Init.Header + hcryp->CrypHeaderCount);
        hcryp->CrypHeaderCount++ ;
        hcryp->Instance->DINR = *(uint32_t *)(hcryp->Init.Header + hcryp->CrypHeaderCount);
        hcryp->CrypHeaderCount++ ;

        if (CRYP_WaitOnCCFlag(hcryp, Timeout) != HAL_OK)
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
      /* Write header block in the IN FIFO without last block */
      for (loopcounter = 0U; (loopcounter < ((size_in_bytes / 16U) * 4U)); loopcounter += 4U)
      {
        /* Write the input block in the data input register */
        hcryp->Instance->DINR = *(uint32_t *)(hcryp->Init.Header + hcryp->CrypHeaderCount);
        hcryp->CrypHeaderCount++ ;
        hcryp->Instance->DINR = *(uint32_t *)(hcryp->Init.Header + hcryp->CrypHeaderCount);
        hcryp->CrypHeaderCount++ ;
        hcryp->Instance->DINR  = *(uint32_t *)(hcryp->Init.Header + hcryp->CrypHeaderCount);
        hcryp->CrypHeaderCount++ ;
        hcryp->Instance->DINR = *(uint32_t *)(hcryp->Init.Header + hcryp->CrypHeaderCount);
        hcryp->CrypHeaderCount++ ;

        if (CRYP_WaitOnCCFlag(hcryp, Timeout) != HAL_OK)
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
      /* Write last complete words */
      for (loopcounter = 0U; (loopcounter < ((size_in_bytes / 4U) % 4U)); loopcounter++)
      {
        hcryp->Instance->DINR = *(uint32_t *)(hcryp->Init.Header + hcryp->CrypHeaderCount);
        hcryp->CrypHeaderCount++ ;
      }
      /* If the header size is a multiple of words */
      if ((size_in_bytes % 4U) == 0U)
      {
        /* Pad the data with zeros to have a complete block */
        while (loopcounter < 4U)
        {
          hcryp->Instance->DINR = 0x0U;
          loopcounter++;
        }
      }
      else
      {
         /* Enter last bytes, padded with zeros */
         tmp =  *(uint32_t *)(hcryp->Init.Header + hcryp->CrypHeaderCount);
         tmp &= mask[(hcryp->Init.DataType * 2U) + (size_in_bytes % 4U)];
         hcryp->Instance->DINR = tmp;
         loopcounter++;
         /* Pad the data with zeros to have a complete block */
         while (loopcounter < 4U)
         {
           hcryp->Instance->DINR = 0x0U;
           loopcounter++;
         }
      }

      if (CRYP_WaitOnCCFlag(hcryp, Timeout) != HAL_OK)
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
    /*Workaround 1: only AES, before re-enabling the peripheral, datatype can be configured.*/
    MODIFY_REG(hcryp->Instance->CR, AES_CR_DATATYPE, hcryp->Init.DataType);

    /* Select header phase */
    CRYP_SET_PHASE(hcryp, CRYP_PHASE_HEADER);

    /* Enable the CRYP peripheral */
    __HAL_CRYP_ENABLE(hcryp);
  }
  /* Return function status */
  return HAL_OK;
}

/**
  * @brief  Sets the header phase when using DMA in process
  * @param  hcryp pointer to a CRYP_HandleTypeDef structure that contains
  *         the configuration information for CRYP module(Header & HeaderSize)
  * @retval None
  */
static HAL_StatusTypeDef CRYP_GCMCCM_SetHeaderPhase_DMA(CRYP_HandleTypeDef *hcryp)
{
  uint32_t loopcounter;
  uint32_t headersize_in_bytes;
  uint32_t tmp;
  uint32_t mask[12] = {0x0U, 0xFF000000U, 0xFFFF0000U, 0xFFFFFF00U,  /* 32-bit data type */
                       0x0U, 0x0000FF00U, 0x0000FFFFU, 0xFF00FFFFU,  /* 16-bit data type */
                       0x0U, 0x000000FFU, 0x0000FFFFU, 0x00FFFFFFU}; /*  8-bit data type */

  /***************************** Header phase for GCM/GMAC or CCM *********************************/
  if (hcryp->Init.HeaderWidthUnit == CRYP_HEADERWIDTHUNIT_WORD)
  {
    headersize_in_bytes = hcryp->Init.HeaderSize * 4U;
  }
  else
  {
    headersize_in_bytes = hcryp->Init.HeaderSize;
  }

  /* Select header phase */
  CRYP_SET_PHASE(hcryp, CRYP_PHASE_HEADER);

  /* Enable the CRYP peripheral */
  __HAL_CRYP_ENABLE(hcryp);

  /* Set the phase */
  hcryp->Phase = CRYP_PHASE_PROCESS;

  /* If header size is at least equal to 16 bytes, feed the header through DMA.
     If size_in_bytes is not a multiple of blocks (is not a multiple of four 32-bit words ),
     last bytes feeding and padding will be done in CRYP_DMAInCplt() */
  if (headersize_in_bytes >= 16U)
  {
    /* Initiate header DMA transfer */
    if (CRYP_SetHeaderDMAConfig(hcryp, (uint32_t)(hcryp->Init.Header), (uint16_t)((headersize_in_bytes / 16U) * 4U)) != HAL_OK)
    {
      return HAL_ERROR;
    }
  }
  else
  {
    if (headersize_in_bytes != 0U)
    {
      /* Header length is larger than 0 and strictly less than 16 bytes */
      /* Write last complete words */
      for (loopcounter = 0U; (loopcounter < (headersize_in_bytes / 4U)); loopcounter++)
      {
        hcryp->Instance->DINR = *(uint32_t *)(hcryp->Init.Header + hcryp->CrypHeaderCount);
        hcryp->CrypHeaderCount++ ;
      }
      /* If the header size is a multiple of words */
      if ((headersize_in_bytes % 4U) == 0U)
      {
        /* Pad the data with zeros to have a complete block */
        while (loopcounter < 4U)
        {
          hcryp->Instance->DINR = 0x0U;
          loopcounter++;
        }
      }
      else
      {
        /* Enter last bytes, padded with zeros */
        tmp =  *(uint32_t *)(hcryp->Init.Header + hcryp->CrypHeaderCount);
        tmp &= mask[(hcryp->Init.DataType * 2U) + (headersize_in_bytes % 4U)];
        hcryp->Instance->DINR = tmp;
        loopcounter++;
        /* Pad the data with zeros to have a complete block */
        while (loopcounter < 4U)
        {
          hcryp->Instance->DINR = 0x0U;
          loopcounter++;
        }
      }

      if (CRYP_WaitOnCCFlag(hcryp, CRYP_TIMEOUT_GCMCCMHEADERPHASE) != HAL_OK)
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
    } /* if (headersize_in_bytes != 0U) */

    /* Move to payload phase if header length is null or
       if the header length was less than 16 and header written by software instead of DMA */

    /* Set to 0 the number of non-valid bytes using NPBLB register*/
    MODIFY_REG(hcryp->Instance->CR, AES_CR_NPBLB, 0U);

    /* Select payload phase once the header phase is performed */
    CRYP_SET_PHASE(hcryp, CRYP_PHASE_PAYLOAD);

    /* Initiate payload DMA IN and processed data DMA OUT transfers */
    if (CRYP_GCMCCM_SetPayloadPhase_DMA(hcryp) != HAL_OK)
    {
      return HAL_ERROR;
    }
  } /* if (headersize_in_bytes >= 16U) */

  /* Return function status */
  return HAL_OK;
}

/**
  * @brief  Sets the header phase in interrupt mode
  * @param  hcryp pointer to a CRYP_HandleTypeDef structure that contains
  *         the configuration information for CRYP module(Header & HeaderSize)
  * @retval None
  */
static void CRYP_GCMCCM_SetHeaderPhase_IT(CRYP_HandleTypeDef *hcryp)
{
  uint32_t loopcounter;
  uint32_t lastwordsize;
  uint32_t npblb;
  uint32_t mode;
  uint32_t headersize_in_bytes;
  uint32_t tmp;
  uint32_t mask[12] = {0x0U, 0xFF000000U, 0xFFFF0000U, 0xFFFFFF00U,  /* 32-bit data type */
                       0x0U, 0x0000FF00U, 0x0000FFFFU, 0xFF00FFFFU,  /* 16-bit data type */
                       0x0U, 0x000000FFU, 0x0000FFFFU, 0x00FFFFFFU}; /*  8-bit data type */

  if (hcryp->Init.HeaderWidthUnit == CRYP_HEADERWIDTHUNIT_WORD)
  {
    headersize_in_bytes = hcryp->Init.HeaderSize * 4U;
  }
  else
  {
    headersize_in_bytes = hcryp->Init.HeaderSize;
  }

  /***************************** Header phase *********************************/
  /* Test whether or not the header phase is over.
     If the test below is true, move to payload phase */
  if (headersize_in_bytes <= ((uint32_t)(hcryp->CrypHeaderCount) * 4U))
  {
    /* Set the phase */
    hcryp->Phase = CRYP_PHASE_PROCESS;
    /* Select payload phase */
    MODIFY_REG(hcryp->Instance->CR, AES_CR_GCMPH, CRYP_PHASE_PAYLOAD);
    /* Set to 0 the number of non-valid bytes using NPBLB register*/
    MODIFY_REG(hcryp->Instance->CR, AES_CR_NPBLB, 0U);

    if (hcryp->Init.Algorithm == CRYP_AES_CCM)
    {
      /* Increment CrypHeaderCount to pass in CRYP_GCMCCM_SetPayloadPhase_IT */
      hcryp->CrypHeaderCount++;
    }
    /* Write the payload Input block in the IN FIFO */
    if (hcryp->Size == 0U)
    {
      /* Disable interrupts */
      __HAL_CRYP_DISABLE_IT(hcryp, CRYP_IT_CCFIE | CRYP_IT_ERRIE);

      /* Change the CRYP state */
      hcryp->State = HAL_CRYP_STATE_READY;

      /* Process unlocked */
      __HAL_UNLOCK(hcryp);
    }
    else if (hcryp->Size >= 16U)
    {
      hcryp->Instance->DINR  = *(uint32_t *)(hcryp->pCrypInBuffPtr + hcryp->CrypInCount);
      hcryp->CrypInCount++;
      hcryp->Instance->DINR  = *(uint32_t *)(hcryp->pCrypInBuffPtr + hcryp->CrypInCount);
      hcryp->CrypInCount++;
      hcryp->Instance->DINR  = *(uint32_t *)(hcryp->pCrypInBuffPtr + hcryp->CrypInCount);
      hcryp->CrypInCount++;
      hcryp->Instance->DINR  = *(uint32_t *)(hcryp->pCrypInBuffPtr + hcryp->CrypInCount);
      hcryp->CrypInCount++;

      if ((hcryp->CrypInCount ==  (hcryp->Size / 4U)) && ((hcryp->Size % 16U) == 0U))
      {
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
    else /* Size < 4 words  : first block is the last block*/
    {
      /* Compute the number of padding bytes in last block of payload */
      npblb = 16U - ((uint32_t)hcryp->Size);
      mode = hcryp->Instance->CR & AES_CR_MODE;
      if (((mode == CRYP_OPERATINGMODE_ENCRYPT) && (hcryp->Init.Algorithm == CRYP_AES_GCM_GMAC)) ||
          ((mode == CRYP_OPERATINGMODE_DECRYPT) && (hcryp->Init.Algorithm == CRYP_AES_CCM)))
      {
        /* Specify the number of non-valid bytes using NPBLB register*/
        MODIFY_REG(hcryp->Instance->CR, AES_CR_NPBLB, npblb << 20U);
      }

      /* Number of valid words (lastwordsize) in last block */
      if ((npblb % 4U) == 0U)
      {
        lastwordsize = (16U - npblb) / 4U;
      }
      else
      {
        lastwordsize = ((16U - npblb) / 4U) + 1U;
      }

      /*  Last block optionally pad the data with zeros*/
      for (loopcounter = 0U; loopcounter < lastwordsize; loopcounter++)
      {
        hcryp->Instance->DINR = *(uint32_t *)(hcryp->pCrypInBuffPtr + hcryp->CrypInCount);
        hcryp->CrypInCount++;
      }
      while (loopcounter < 4U)
      {
        /* Pad the data with zeros to have a complete block */
        hcryp->Instance->DINR = 0x0U;
        loopcounter++;
      }
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
  else if ((((headersize_in_bytes / 4U) - (hcryp->CrypHeaderCount)) >= 4U))
  {
    /* Can enter full 4 header words */
#if (USE_HAL_CRYP_SUSPEND_RESUME == 1U)
    /* If suspension flag has been raised, suspend processing
       only if not already at the end of the header */
    if (hcryp->SuspendRequest == HAL_CRYP_SUSPEND)
    {
      /* Clear CCF Flag */
      __HAL_CRYP_CLEAR_FLAG(hcryp, CRYP_CCF_CLEAR);

      /* reset SuspendRequest */
      hcryp->SuspendRequest = HAL_CRYP_SUSPEND_NONE;
      /* Disable Computation Complete Flag and Errors Interrupts */
      __HAL_CRYP_DISABLE_IT(hcryp, CRYP_IT_CCFIE|CRYP_IT_ERRIE);
      /* Change the CRYP state */
      hcryp->State = HAL_CRYP_STATE_SUSPENDED;
      /* Mark that the payload phase is suspended */
      hcryp->Phase = CRYP_PHASE_HEADER_SUSPENDED;

     /* Process Unlocked */
      __HAL_UNLOCK(hcryp);
    }
    else
#endif /* USE_HAL_CRYP_SUSPEND_RESUME */
    {
    /* Write the input block in the IN FIFO */
    hcryp->Instance->DINR  = *(uint32_t *)(hcryp->Init.Header + hcryp->CrypHeaderCount);
    hcryp->CrypHeaderCount++;
    hcryp->Instance->DINR  = *(uint32_t *)(hcryp->Init.Header + hcryp->CrypHeaderCount);
    hcryp->CrypHeaderCount++;
    hcryp->Instance->DINR  = *(uint32_t *)(hcryp->Init.Header + hcryp->CrypHeaderCount);
    hcryp->CrypHeaderCount++;
    hcryp->Instance->DINR  = *(uint32_t *)(hcryp->Init.Header + hcryp->CrypHeaderCount);
    hcryp->CrypHeaderCount++;
  }
  }
  else /* Write last header block (4 words), padded with zeros if needed */
  {

    for (loopcounter = 0U; (loopcounter < ((headersize_in_bytes / 4U) % 4U)); loopcounter++)
    {
      hcryp->Instance->DINR = *(uint32_t *)(hcryp->Init.Header + hcryp->CrypHeaderCount);
      hcryp->CrypHeaderCount++ ;
    }
    /* If the header size is a multiple of words */
    if ((headersize_in_bytes % 4U) == 0U)
    {
      /* Pad the data with zeros to have a complete block */
      while (loopcounter < 4U)
      {
        hcryp->Instance->DINR = 0x0U;
        loopcounter++;
        hcryp->CrypHeaderCount++;
      }
    }
    else
    {
      /* Enter last bytes, padded with zeros */
      tmp =  *(uint32_t *)(hcryp->Init.Header + hcryp->CrypHeaderCount);
      tmp &= mask[(hcryp->Init.DataType * 2U) + (headersize_in_bytes % 4U)];
      hcryp->Instance->DINR = tmp;
      loopcounter++;
      hcryp->CrypHeaderCount++;
      /* Pad the data with zeros to have a complete block */
    while (loopcounter < 4U)
    {
      hcryp->Instance->DINR = 0x0U;
      loopcounter++;
        hcryp->CrypHeaderCount++;
      }
    }
  }
}

/**
  * @brief  Handle CRYP hardware block Timeout when waiting for CCF flag to be raised.
  * @param  hcryp pointer to a CRYP_HandleTypeDef structure that contains
  *         the configuration information for CRYP module.
  * @param  Timeout Timeout duration.
  * @note   This function can only be used in thread mode.
  * @retval HAL status
  */
static HAL_StatusTypeDef CRYP_WaitOnCCFlag(CRYP_HandleTypeDef *hcryp, uint32_t Timeout)
{
  uint32_t tickstart;

  /* Get timeout */
  tickstart = HAL_GetTick();

  while (HAL_IS_BIT_CLR(hcryp->Instance->SR, AES_SR_CCF))
  {
    /* Check for the Timeout */
    if (Timeout != HAL_MAX_DELAY)
    {
      if (((HAL_GetTick() - tickstart) > Timeout) || (Timeout == 0U))
      {
        return HAL_ERROR;
      }
    }
  }
  return HAL_OK;
}

/**
  * @brief  Wait for Computation Complete Flag (CCF) to raise then clear it.
  * @param  hcryp pointer to a CRYP_HandleTypeDef structure that contains
  *         the configuration information for CRYP module.
  * @param  Timeout Timeout duration.
  * @note   This function can be used in thread or handler mode.
  * @retval HAL status
  */
static void CRYP_ClearCCFlagWhenHigh(CRYP_HandleTypeDef *hcryp, uint32_t Timeout)
{
  uint32_t count = Timeout;

  do
  {
    count-- ;
    if (count == 0U)
    {
      /* Disable the CRYP peripheral clock */
      __HAL_CRYP_DISABLE(hcryp);

      /* Change state */
      hcryp->ErrorCode |= HAL_CRYP_ERROR_TIMEOUT;

      /* Process unlocked */
      __HAL_UNLOCK(hcryp);
      hcryp->State = HAL_CRYP_STATE_READY;

#if (USE_HAL_CRYP_REGISTER_CALLBACKS == 1U)
    /*Call registered error callback*/
    hcryp->ErrorCallback(hcryp);
#else
    /*Call legacy weak error callback*/
    HAL_CRYP_ErrorCallback(hcryp);
#endif /* USE_HAL_CRYP_REGISTER_CALLBACKS */
    }
  }
  while (HAL_IS_BIT_CLR(hcryp->Instance->SR, AES_SR_CCF));

  /* Clear CCF flag */
  __HAL_CRYP_CLEAR_FLAG(hcryp, CRYP_CCF_CLEAR);
}

#if (USE_HAL_CRYP_SUSPEND_RESUME == 1U)
/**
  * @brief  In case of message processing suspension, read the Initialization Vector.
  * @param  hcryp pointer to a CRYP_HandleTypeDef structure that contains
  *         the configuration information for CRYP module.
  * @param  Output Pointer to the buffer containing the saved Initialization Vector.
  * @note   This value has to be stored for reuse by writing the AES_IVRx registers
  *         as soon as the suspended processing has to be resumed.
  * @retval None
  */
static void CRYP_Read_IVRegisters(CRYP_HandleTypeDef *hcryp, uint32_t* Output)
{
  uint32_t outputaddr = (uint32_t)Output;

  *(uint32_t*)(outputaddr) = hcryp->Instance->IVR3;
  outputaddr+=4U;
  *(uint32_t*)(outputaddr) = hcryp->Instance->IVR2;
  outputaddr+=4U;
  *(uint32_t*)(outputaddr) = hcryp->Instance->IVR1;
  outputaddr+=4U;
  *(uint32_t*)(outputaddr) = hcryp->Instance->IVR0;
}

/**
  * @brief  In case of message processing resumption, rewrite the Initialization
  *         Vector in the AES_IVRx registers.
  * @param  hcryp pointer to a CRYP_HandleTypeDef structure that contains
  *         the configuration information for CRYP module.
  * @param  Input Pointer to the buffer containing the saved Initialization Vector to
  *         write back in the CRYP hardware block.
  * @note   AES must be disabled when reconfiguring the IV values.
  * @retval None
  */
static void CRYP_Write_IVRegisters(CRYP_HandleTypeDef *hcryp, uint32_t* Input)
{
  uint32_t ivaddr = (uint32_t)Input;

  hcryp->Instance->IVR3 = *(uint32_t*)(ivaddr);
  ivaddr+=4U;
  hcryp->Instance->IVR2 = *(uint32_t*)(ivaddr);
  ivaddr+=4U;
  hcryp->Instance->IVR1 = *(uint32_t*)(ivaddr);
  ivaddr+=4U;
  hcryp->Instance->IVR0 = *(uint32_t*)(ivaddr);
}

/**
  * @brief  In case of message GCM/GMAC/CCM processing suspension,
  *         read the Suspend Registers.
  * @param  hcryp pointer to a CRYP_HandleTypeDef structure that contains
  *         the configuration information for CRYP module.
  * @param  Output Pointer to the buffer containing the saved Suspend Registers.
  * @note   These values have to be stored for reuse by writing back the AES_SUSPxR registers
  *         as soon as the suspended processing has to be resumed.
  * @retval None
  */
static void CRYP_Read_SuspendRegisters(CRYP_HandleTypeDef *hcryp, uint32_t* Output)
{
  uint32_t outputaddr = (uint32_t)Output;
  __IO uint32_t count = 0U;

  /* In case of GCM payload phase encryption, check that suspension can be carried out */
  if (READ_BIT(hcryp->Instance->CR, (AES_CR_CHMOD|AES_CR_GCMPH|AES_CR_MODE)) == (CRYP_AES_GCM_GMAC|AES_CR_GCMPH_1|0x0U))
  {

      /* Wait for BUSY flag to be cleared */
      count = 0xFFF;
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
          HAL_CRYP_ErrorCallback(hcryp);
          return;
        }
      }
      while(HAL_IS_BIT_SET(hcryp->Instance->SR, AES_SR_BUSY));

  }


  *(uint32_t*)(outputaddr) = hcryp->Instance->SUSP7R;
  outputaddr+=4U;
  *(uint32_t*)(outputaddr) = hcryp->Instance->SUSP6R;
  outputaddr+=4U;
  *(uint32_t*)(outputaddr) = hcryp->Instance->SUSP5R;
  outputaddr+=4U;
  *(uint32_t*)(outputaddr) = hcryp->Instance->SUSP4R;
  outputaddr+=4U;
  *(uint32_t*)(outputaddr) = hcryp->Instance->SUSP3R;
  outputaddr+=4U;
  *(uint32_t*)(outputaddr) = hcryp->Instance->SUSP2R;
  outputaddr+=4U;
  *(uint32_t*)(outputaddr) = hcryp->Instance->SUSP1R;
  outputaddr+=4U;
  *(uint32_t*)(outputaddr) = hcryp->Instance->SUSP0R;
}

/**
  * @brief  In case of message GCM/GMAC/CCM processing resumption, rewrite the Suspend
  *         Registers in the AES_SUSPxR registers.
  * @param  hcryp pointer to a CRYP_HandleTypeDef structure that contains
  *         the configuration information for CRYP module.
  * @param  Input Pointer to the buffer containing the saved suspend registers to
  *         write back in the CRYP hardware block.
  * @note   AES must be disabled when reconfiguring the suspend registers.
  * @retval None
  */
static void CRYP_Write_SuspendRegisters(CRYP_HandleTypeDef *hcryp, uint32_t* Input)
{
  uint32_t ivaddr = (uint32_t)Input;

  hcryp->Instance->SUSP7R = *(uint32_t*)(ivaddr);
  ivaddr+=4U;
  hcryp->Instance->SUSP6R = *(uint32_t*)(ivaddr);
  ivaddr+=4U;
  hcryp->Instance->SUSP5R = *(uint32_t*)(ivaddr);
  ivaddr+=4U;
  hcryp->Instance->SUSP4R = *(uint32_t*)(ivaddr);
  ivaddr+=4U;
  hcryp->Instance->SUSP3R = *(uint32_t*)(ivaddr);
  ivaddr+=4U;
  hcryp->Instance->SUSP2R = *(uint32_t*)(ivaddr);
  ivaddr+=4U;
  hcryp->Instance->SUSP1R = *(uint32_t*)(ivaddr);
  ivaddr+=4U;
  hcryp->Instance->SUSP0R = *(uint32_t*)(ivaddr);
}

/**
  * @brief  In case of message GCM/GMAC/CCM processing suspension, read the Key Registers.
  * @param  hcryp pointer to a CRYP_HandleTypeDef structure that contains
  *         the configuration information for CRYP module.
  * @param  Output Pointer to the buffer containing the saved Key Registers.
  * @param  KeySize Indicates the key size (128 or 256 bits).
  * @note   These values have to be stored for reuse by writing back the AES_KEYRx registers
  *         as soon as the suspended processing has to be resumed.
  * @retval None
  */
static void CRYP_Read_KeyRegisters(CRYP_HandleTypeDef *hcryp, uint32_t* Output, uint32_t KeySize)
{
  uint32_t keyaddr = (uint32_t)Output;

  switch (KeySize)
  {
    case CRYP_KEYSIZE_256B:
      *(uint32_t*)(keyaddr) = *(uint32_t *)(hcryp->Init.pKey);
      keyaddr+=4U;
      *(uint32_t*)(keyaddr) = *(uint32_t *)(hcryp->Init.pKey + 1U);
      keyaddr+=4U;
      *(uint32_t*)(keyaddr) = *(uint32_t *)(hcryp->Init.pKey + 2U);
      keyaddr+=4U;
      *(uint32_t*)(keyaddr) = *(uint32_t *)(hcryp->Init.pKey + 3U);
      keyaddr+=4U;
      *(uint32_t*)(keyaddr) = *(uint32_t *)(hcryp->Init.pKey + 4U);
      keyaddr+=4U;
      *(uint32_t*)(keyaddr) = *(uint32_t *)(hcryp->Init.pKey + 5U);
      keyaddr+=4U;
      *(uint32_t*)(keyaddr) = *(uint32_t *)(hcryp->Init.pKey + 6U);
      keyaddr+=4U;
      *(uint32_t*)(keyaddr) = *(uint32_t *)(hcryp->Init.pKey + 7U);
      break;
    case CRYP_KEYSIZE_128B:
      *(uint32_t*)(keyaddr) = *(uint32_t *)(hcryp->Init.pKey);
      keyaddr+=4U;
      *(uint32_t*)(keyaddr) = *(uint32_t *)(hcryp->Init.pKey + 1U);
      keyaddr+=4U;
      *(uint32_t*)(keyaddr) = *(uint32_t *)(hcryp->Init.pKey + 2U);
      keyaddr+=4U;
      *(uint32_t*)(keyaddr) = *(uint32_t *)(hcryp->Init.pKey + 3U);
      break;
    default:
      break;
  }
}

/**
  * @brief  In case of message GCM/GMAC (CCM/CMAC when applicable) processing resumption, rewrite the Key
  *         Registers in the AES_KEYRx registers.
  * @param  hcryp pointer to a CRYP_HandleTypeDef structure that contains
  *         the configuration information for CRYP module.
  * @param  Input Pointer to the buffer containing the saved key registers to
  *         write back in the CRYP hardware block.
  * @param  KeySize Indicates the key size (128 or 256 bits)
  * @note   AES must be disabled when reconfiguring the Key registers.
  * @retval None
  */
static void CRYP_Write_KeyRegisters(CRYP_HandleTypeDef *hcryp, uint32_t* Input, uint32_t KeySize)
{
  uint32_t keyaddr = (uint32_t)Input;

  if (KeySize == CRYP_KEYSIZE_256B)
  {
    hcryp->Instance->KEYR7 = *(uint32_t*)(keyaddr);
    keyaddr+=4U;
    hcryp->Instance->KEYR6 = *(uint32_t*)(keyaddr);
    keyaddr+=4U;
    hcryp->Instance->KEYR5 = *(uint32_t*)(keyaddr);
    keyaddr+=4U;
    hcryp->Instance->KEYR4 = *(uint32_t*)(keyaddr);
    keyaddr+=4U;
  }

    hcryp->Instance->KEYR3 = *(uint32_t*)(keyaddr);
    keyaddr+=4U;
    hcryp->Instance->KEYR2 = *(uint32_t*)(keyaddr);
    keyaddr+=4U;
    hcryp->Instance->KEYR1 = *(uint32_t*)(keyaddr);
    keyaddr+=4U;
    hcryp->Instance->KEYR0 = *(uint32_t*)(keyaddr);
}

/**
  * @brief  Authentication phase resumption in case of GCM/GMAC/CCM process in interrupt mode
  * @param  hcryp pointer to a CRYP_HandleTypeDef structure that contains
  *         the configuration information for CRYP module(Header & HeaderSize)
  * @retval None
  */
static void CRYP_PhaseProcessingResume(CRYP_HandleTypeDef *hcryp)
{
  uint32_t loopcounter;
  uint16_t lastwordsize;
  uint16_t npblb;
  uint32_t cr_temp;


  __HAL_CRYP_CLEAR_FLAG(hcryp, CRYP_ERR_CLEAR | CRYP_CCF_CLEAR);

  /* Enable computation complete flag and error interrupts */
  __HAL_CRYP_ENABLE_IT(hcryp, CRYP_IT_CCFIE | CRYP_IT_ERRIE);

  /* Enable the CRYP peripheral */
  __HAL_CRYP_ENABLE(hcryp);

  /* Case of header phase resumption =================================================*/
  if (hcryp->Phase == CRYP_PHASE_HEADER_SUSPENDED)
  {
      /* Set the phase */
    hcryp->Phase = CRYP_PHASE_PROCESS;

    /* Select header phase */
    CRYP_SET_PHASE(hcryp, CRYP_PHASE_HEADER);

    if ((((hcryp->Init.HeaderSize) - (hcryp->CrypHeaderCount)) >= 4U))
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
  }
  /* Case of payload phase resumption =================================================*/
  else
  {
    if (hcryp->Phase == CRYP_PHASE_PAYLOAD_SUSPENDED)
    {

      /* Set the phase */
      hcryp->Phase = CRYP_PHASE_PROCESS;

      /* Select payload phase once the header phase is performed */
      MODIFY_REG(hcryp->Instance->CR, AES_CR_GCMPH, CRYP_PHASE_PAYLOAD);

      /* Set to 0 the number of non-valid bytes using NPBLB register*/
      MODIFY_REG(hcryp->Instance->CR, AES_CR_NPBLB, 0U);

      if (((hcryp->Size/4U) - (hcryp->CrypInCount)) >= 4U)
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
        if ((hcryp->CrypInCount ==  (hcryp->Size / 4U)) && ((hcryp->Size % 16U) == 0U))
        {
          /* Call input transfer complete callback */
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
        /* Compute the number of padding bytes in last block of payload */
        npblb = (((hcryp->Size/16U)+1U)*16U) - (hcryp->Size);
        cr_temp = hcryp->Instance->CR;
        if((((cr_temp & AES_CR_MODE) == CRYP_OPERATINGMODE_ENCRYPT) && (hcryp->Init.Algorithm == CRYP_AES_GCM_GMAC)) ||
           (((cr_temp& AES_CR_MODE) == CRYP_OPERATINGMODE_DECRYPT) && (hcryp->Init.Algorithm == CRYP_AES_CCM)))
        {
          /* Specify the number of non-valid bytes using NPBLB register*/
            MODIFY_REG(hcryp->Instance->CR, AES_CR_NPBLB, ((uint32_t)npblb)<< 20U);
        }

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
        while(loopcounter < 4U )
        {
          /* pad the data with zeros to have a complete block */
          hcryp->Instance->DINR = 0x0U;
          loopcounter++;
        }
      }
    }
  }
}
#endif /* defined (USE_HAL_CRYP_SUSPEND_RESUME) */
/**
  * @}
  */


#endif /* HAL_CRYP_MODULE_ENABLED */


/**
  * @}
  */

/**
 * @}
 */
/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
