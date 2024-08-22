/**
  ******************************************************************************
  * @file    stm32h7xx_hal_cryp.c
  * @author  MCD Application Team
  * @brief   CRYP HAL module driver.
  *          This file provides firmware functions to manage the following
  *          functionalities of the Cryptography (CRYP) peripheral:
  *           + Initialization and de-initialization functions
  *           + AES processing functions
  *           + DES processing functions
  *           + TDES processing functions
  *           + DMA callback functions
  *           + CRYP IRQ handler management
  *           + Peripheral State functions
  *
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2017 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  @verbatim
  ==============================================================================
                     ##### How to use this driver #####
  ==============================================================================
    [..]
      The CRYP HAL driver can be used in CRYP IP as follows:

      (#)Initialize the CRYP low level resources by implementing the HAL_CRYP_MspInit():
         (##) Enable the CRYP interface clock using __HAL_RCC_CRYP_CLK_ENABLE()
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
                 interrupt on the two DMA Streams. The output stream should have higher
                 priority than the input stream HAL_NVIC_SetPriority() and HAL_NVIC_EnableIRQ()

      (#)Initialize the CRYP according to the specified parameters :
         (##) The data type: bit swap(1-bit data), byte swap(8-bit data), half word swap(16-bit data)
            or no swap(32-bit data).
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

       (#)To process a single message with consecutive calls to HAL_CRYP_Encrypt() or HAL_CRYP_Decrypt()
          without having to configure again the Key or the Initialization Vector between each API call,
          the field KeyIVConfigSkip of the initialization structure must be set to CRYP_KEYIVCONFIG_ONCE.
          Same is true for consecutive calls of HAL_CRYP_Encrypt_IT(), HAL_CRYP_Decrypt_IT(), HAL_CRYP_Encrypt_DMA()
          or HAL_CRYP_Decrypt_DMA().

    [..]
      The cryptographic processor supports following standards:
      (#) The data encryption standard (DES) and Triple-DES (TDES) supported only by CRYP1 IP:
         (##)64-bit data block processing
         (##) chaining modes supported :
             (+++)  Electronic Code Book(ECB)
             (+++)  Cipher Block Chaining (CBC)
         (##) keys length supported :64-bit, 128-bit and 192-bit.
      (#) The advanced encryption standard (AES) supported  by CRYP1:
         (##)128-bit data block processing
         (##) chaining modes supported :
             (+++)  Electronic Code Book(ECB)
             (+++)  Cipher Block Chaining (CBC)
             (+++)  Counter mode (CTR)
             (+++)  Galois/counter mode (GCM/GMAC)
             (+++)  Counter with Cipher Block Chaining-Message(CCM)
         (##) keys length Supported :
             (+++) for CRYP1 IP: 128-bit, 192-bit and 256-bit.

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
          HAL_CRYPEx_AESGCM_GenerateAuthTAG API used in this phase to generate 4 words which correspond
          to the Tag. user should consider only part of this 4 words, if Tag length is less than 128 bits.
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
         HAL_CRYPEx_AESCCM_GenerateAuthTAG API used in this phase to generate 4 words which correspond to the Tag.
         user should consider only part of this 4 words, if Tag length is less than 128 bits

  *** Callback registration ***
  =============================

  [..]
  The compilation define  USE_HAL_CRYP_REGISTER_CALLBACKS when set to 1
  allows the user to configure dynamically the driver callbacks.
  Use Functions @ref HAL_CRYP_RegisterCallback() or HAL_CRYP_RegisterXXXCallback()
  to register an interrupt callback.

  [..]
  Function @ref HAL_CRYP_RegisterCallback() allows to register following callbacks:
    (+) InCpltCallback     :  Input FIFO transfer completed callback.
    (+) OutCpltCallback    : Output FIFO transfer completed callback.
    (+) ErrorCallback      : callback for error detection.
    (+) MspInitCallback    : CRYP MspInit.
    (+) MspDeInitCallback  : CRYP MspDeInit.
  This function takes as parameters the HAL peripheral handle, the Callback ID
  and a pointer to the user callback function.

  [..]
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

  [..]
  By default, after the @ref HAL_CRYP_Init() and when the state is HAL_CRYP_STATE_RESET
  all callbacks are set to the corresponding weak functions :
  examples @ref HAL_CRYP_InCpltCallback() , @ref HAL_CRYP_OutCpltCallback().
  Exception done for MspInit and MspDeInit functions that are
  reset to the legacy weak function in the @ref HAL_CRYP_Init()/ @ref HAL_CRYP_DeInit() only when
  these callbacks are null (not registered beforehand).
  if not, MspInit or MspDeInit are not null, the @ref HAL_CRYP_Init() / @ref HAL_CRYP_DeInit()
  keep and use the user MspInit/MspDeInit functions (registered beforehand)

  [..]
  Callbacks can be registered/unregistered in HAL_CRYP_STATE_READY state only.
  Exception done MspInit/MspDeInit callbacks that can be registered/unregistered
  in HAL_CRYP_STATE_READY or HAL_CRYP_STATE_RESET state,
  thus registered (user) MspInit/DeInit callbacks can be used during the Init/DeInit.
  In that case first register the MspInit/MspDeInit user callbacks
  using @ref HAL_CRYP_RegisterCallback() before calling @ref HAL_CRYP_DeInit()
  or @ref HAL_CRYP_Init() function.

  [..]
  When The compilation define USE_HAL_CRYP_REGISTER_CALLBACKS is set to 0 or
  not defined, the callback registration feature is not available and all callbacks
  are set to the corresponding weak functions.

  @endverbatim

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
  */

/* Includes ------------------------------------------------------------------*/
#include "stm32h7xx_hal.h"

/** @addtogroup STM32H7xx_HAL_Driver
  * @{
  */

#if defined (CRYP)

/** @defgroup CRYP CRYP
  * @brief CRYP HAL module driver.
  * @{
  */


#ifdef HAL_CRYP_MODULE_ENABLED

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/** @addtogroup CRYP_Private_Defines
  * @{
  */
#define CRYP_TIMEOUT_KEYPREPARATION      82U         /*!<  The latency of key preparation operation is 82 clock cycles.*/
#define CRYP_TIMEOUT_GCMCCMINITPHASE     299U        /*!<  The latency of  GCM/CCM init phase to prepare hash subkey is 299 clock cycles.*/
#define CRYP_TIMEOUT_GCMCCMHEADERPHASE   290U        /*!<  The latency of  GCM/CCM header phase is 290 clock cycles.*/

#define  CRYP_PHASE_READY                0x00000001U /*!< CRYP peripheral is ready for initialization. */
#define  CRYP_PHASE_PROCESS              0x00000002U /*!< CRYP peripheral is in processing phase */

#define CRYP_PHASE_INIT                  0x00000000U             /*!< GCM/GMAC (or CCM) init phase */
#define CRYP_PHASE_HEADER                CRYP_CR_GCM_CCMPH_0     /*!< GCM/GMAC or CCM header phase */
#define CRYP_PHASE_PAYLOAD               CRYP_CR_GCM_CCMPH_1     /*!< GCM(/CCM) payload phase      */
#define CRYP_PHASE_FINAL                 CRYP_CR_GCM_CCMPH       /*!< GCM/GMAC or CCM  final phase */
#define CRYP_OPERATINGMODE_ENCRYPT       0x00000000U             /*!< Encryption mode   */
#define CRYP_OPERATINGMODE_DECRYPT       CRYP_CR_ALGODIR         /*!< Decryption        */


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

#define CRYP_SET_PHASE(__HANDLE__, __PHASE__)  do{(__HANDLE__)->Instance->CR &= (uint32_t)(~CRYP_CR_GCM_CCMPH);\
                                                        (__HANDLE__)->Instance->CR |= (uint32_t)(__PHASE__);\
                                                       }while(0)

#define HAL_CRYP_FIFO_FLUSH(__HANDLE__) ((__HANDLE__)->Instance->CR |=  CRYP_CR_FFLUSH)


/**
  * @}
  */

/* Private struct -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
/** @addtogroup CRYP_Private_Functions_Prototypes
  * @{
  */

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
#if !defined (CRYP_VER_2_2)
static void CRYP_Workaround(CRYP_HandleTypeDef *hcryp, uint32_t Timeout);
#endif /*End of not defined CRYP_VER_2_2*/
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
static void CRYP_TDES_IT(CRYP_HandleTypeDef *hcryp);
static HAL_StatusTypeDef CRYP_WaitOnIFEMFlag(const CRYP_HandleTypeDef *hcryp, uint32_t Timeout);
static HAL_StatusTypeDef CRYP_WaitOnBUSYFlag(const CRYP_HandleTypeDef *hcryp, uint32_t Timeout);
static HAL_StatusTypeDef CRYP_WaitOnOFNEFlag(const CRYP_HandleTypeDef *hcryp, uint32_t Timeout);
static HAL_StatusTypeDef CRYP_TDES_Process(CRYP_HandleTypeDef *hcryp, uint32_t Timeout);

/**
  * @}
  */

/* Exported functions ---------------------------------------------------------*/

/** @defgroup CRYP_Exported_Functions CRYP Exported Functions
  * @{
  */


/** @defgroup CRYP_Exported_Functions_Group1 Initialization and de-initialization functions
  *  @brief    CRYP  Initialization and Configuration functions.
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
          (++) AlgoMode : for CRYP1 IP
                 ECB and CBC in DES/TDES Standard
                 ECB,CBC,CTR,GCM/GMAC and CCM in AES Standard.
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
  if (hcryp == NULL)
  {
    return HAL_ERROR;
  }

  /* Check parameters */
  assert_param(IS_CRYP_KEYSIZE(hcryp->Init.KeySize));
  assert_param(IS_CRYP_DATATYPE(hcryp->Init.DataType));
  assert_param(IS_CRYP_ALGORITHM(hcryp->Init.Algorithm));
  assert_param(IS_CRYP_INIT(hcryp->Init.KeyIVConfigSkip));

#if (USE_HAL_CRYP_REGISTER_CALLBACKS == 1)
  if (hcryp->State == HAL_CRYP_STATE_RESET)
  {
    /* Allocate lock resource and initialize it */
    hcryp->Lock = HAL_UNLOCKED;

    hcryp->InCpltCallback  = HAL_CRYP_InCpltCallback;  /* Legacy weak  InCpltCallback  */
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

  /* Set the key size(This bit field is don't care in the DES or TDES modes) data type and Algorithm */
  MODIFY_REG(hcryp->Instance->CR, CRYP_CR_DATATYPE | CRYP_CR_KEYSIZE | CRYP_CR_ALGOMODE,
             hcryp->Init.DataType | hcryp->Init.KeySize | hcryp->Init.Algorithm);
#if !defined (CRYP_VER_2_2)
  /* Read Device ID to indicate CRYP1 IP Version */
  hcryp->Version = HAL_GetREVID();
#endif /*End of not defined CRYP_VER_2_2*/
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
  * @param  hcryp: pointer to a CRYP_HandleTypeDef structure that contains
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

#if (USE_HAL_CRYP_REGISTER_CALLBACKS == 1)
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
  * @param  hcryp: pointer to a CRYP_HandleTypeDef structure
  * @param  pConf: pointer to a CRYP_ConfigTypeDef structure that contains
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

    /* Set the key size(This bit field is don't care in the DES or TDES modes) data type, AlgoMode and operating mode*/
    MODIFY_REG(hcryp->Instance->CR, CRYP_CR_DATATYPE | CRYP_CR_KEYSIZE | CRYP_CR_ALGOMODE,
               hcryp->Init.DataType | hcryp->Init.KeySize | hcryp->Init.Algorithm);

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
  * @param  pConf: pointer to a CRYP_ConfigTypeDef structure
  * @param  hcryp: pointer to a CRYP_HandleTypeDef structure that contains
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
  * @param  hcryp: pointer to a CRYP_HandleTypeDef structure that contains
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
  * @param  hcryp: pointer to a CRYP_HandleTypeDef structure that contains
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

#if (USE_HAL_CRYP_REGISTER_CALLBACKS == 1)
/**
  * @brief  Register a User CRYP Callback
  *         To be used instead of the weak predefined callback
  * @param hcryp cryp handle
  * @param CallbackID ID of the callback to be registered
  *        This parameter can be one of the following values:
  *          @arg @ref HAL_CRYP_INPUT_COMPLETE_CB_ID Input FIFO transfer completed callback ID
  *          @arg @ref HAL_CRYP_OUTPUT_COMPLETE_CB_ID Output FIFO transfer completed callback ID
  *          @arg @ref HAL_CRYP_ERROR_CB_ID Rx Half Error callback ID
  *          @arg @ref HAL_CRYP_MSPINIT_CB_ID MspInit callback ID
  *          @arg @ref HAL_CRYP_MSPDEINIT_CB_ID MspDeInit callback ID
  * @param pCallback pointer to the Callback function
  * @retval status
  */
HAL_StatusTypeDef HAL_CRYP_RegisterCallback(CRYP_HandleTypeDef *hcryp, HAL_CRYP_CallbackIDTypeDef CallbackID,
                                            pCRYP_CallbackTypeDef pCallback)
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
  *          @arg @ref HAL_CRYP_ERROR_CB_ID Rx Half Error callback ID
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
#endif /* USE_HAL_UART_REGISTER_CALLBACKS */

/**
  * @}
  */

/** @defgroup CRYP_Exported_Functions_Group2  Encrypt Decrypt functions
  *  @brief   CRYP processing functions.
  *
@verbatim
  ==============================================================================
                      ##### Encrypt Decrypt  functions #####
  ==============================================================================
    [..]  This section provides API allowing to Encrypt/Decrypt Data following
          Standard DES/TDES or AES, and Algorithm configured by the user:
      (+) Standard DES/TDES only supported by CRYP1 IP, below list of Algorithm supported :
           (++)  Electronic Code Book(ECB)
           (++) Cipher Block Chaining (CBC)
      (+) Standard AES  supported by CRYP1 IP , list of Algorithm supported:
           (++) Electronic Code Book(ECB)
           (++) Cipher Block Chaining (CBC)
           (++) Counter mode (CTR)
           (++) Cipher Block Chaining (CBC)
           (++) Counter mode (CTR)
           (++) Galois/counter mode (GCM)
           (++) Counter with Cipher Block Chaining-Message(CCM)
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
  * @param  Size: Length of the plaintext buffer either in word or in byte, according to DataWidthUnit.
  * @param  Output: Pointer to the output buffer(ciphertext)
  * @param  Timeout: Specify Timeout value
  * @retval HAL status
  */
HAL_StatusTypeDef HAL_CRYP_Encrypt(CRYP_HandleTypeDef *hcryp, uint32_t *Input, uint16_t Size, uint32_t *Output,
                                   uint32_t Timeout)
{
  uint32_t algo;
  HAL_StatusTypeDef status;

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

    /* Set Encryption operating mode*/
    MODIFY_REG(hcryp->Instance->CR, CRYP_CR_ALGODIR, CRYP_OPERATINGMODE_ENCRYPT);

    /* algo get algorithm selected */
    algo = hcryp->Instance->CR & CRYP_CR_ALGOMODE;

    switch (algo)
    {
      case CRYP_DES_ECB:
      case CRYP_DES_CBC:
      case CRYP_TDES_ECB:
      case CRYP_TDES_CBC:

        /*Set Key */
        hcryp->Instance->K1LR = *(uint32_t *)(hcryp->Init.pKey);
        hcryp->Instance->K1RR = *(uint32_t *)(hcryp->Init.pKey + 1);
        if ((hcryp->Init.Algorithm == CRYP_TDES_ECB) || (hcryp->Init.Algorithm == CRYP_TDES_CBC))
        {
          hcryp->Instance->K2LR = *(uint32_t *)(hcryp->Init.pKey + 2);
          hcryp->Instance->K2RR = *(uint32_t *)(hcryp->Init.pKey + 3);
          hcryp->Instance->K3LR = *(uint32_t *)(hcryp->Init.pKey + 4);
          hcryp->Instance->K3RR = *(uint32_t *)(hcryp->Init.pKey + 5);
        }

        /*Set Initialization Vector (IV)*/
        if ((hcryp->Init.Algorithm == CRYP_DES_CBC) || (hcryp->Init.Algorithm == CRYP_TDES_CBC))
        {
          hcryp->Instance->IV0LR = *(uint32_t *)(hcryp->Init.pInitVect);
          hcryp->Instance->IV0RR = *(uint32_t *)(hcryp->Init.pInitVect + 1);
        }

        /* Flush FIFO */
        HAL_CRYP_FIFO_FLUSH(hcryp);

        /* Set the phase */
        hcryp->Phase = CRYP_PHASE_PROCESS;

        /* Start DES/TDES encryption process */
        status = CRYP_TDES_Process(hcryp, Timeout);
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
    /* Process unlocked */
    __HAL_UNLOCK(hcryp);

    /* Busy error code field */
    hcryp->ErrorCode |= HAL_CRYP_ERROR_BUSY;
    status = HAL_ERROR;
  }

  /* Return function status */
  return status ;
}

/**
  * @brief  Decryption mode.
  * @param  hcryp: pointer to a CRYP_HandleTypeDef structure that contains
  *         the configuration information for CRYP module
  * @param  Input: Pointer to the input buffer (ciphertext )
  * @param  Size: Length of the plaintext buffer either in word or in byte, according to DataWidthUnit
  * @param  Output: Pointer to the output buffer(plaintext)
  * @param  Timeout: Specify Timeout value
  * @retval HAL status
  */
HAL_StatusTypeDef HAL_CRYP_Decrypt(CRYP_HandleTypeDef *hcryp, uint32_t *Input, uint16_t Size, uint32_t *Output,
                                   uint32_t Timeout)
{
  HAL_StatusTypeDef status;
  uint32_t algo;

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

    /* Set Decryption operating mode*/
    MODIFY_REG(hcryp->Instance->CR, CRYP_CR_ALGODIR, CRYP_OPERATINGMODE_DECRYPT);

    /* algo get algorithm selected */
    algo = hcryp->Instance->CR & CRYP_CR_ALGOMODE;

    switch (algo)
    {
      case CRYP_DES_ECB:
      case CRYP_DES_CBC:
      case CRYP_TDES_ECB:
      case CRYP_TDES_CBC:

        /*Set Key */
        hcryp->Instance->K1LR = *(uint32_t *)(hcryp->Init.pKey);
        hcryp->Instance->K1RR = *(uint32_t *)(hcryp->Init.pKey + 1);
        if ((hcryp->Init.Algorithm == CRYP_TDES_ECB) || (hcryp->Init.Algorithm == CRYP_TDES_CBC))
        {
          hcryp->Instance->K2LR = *(uint32_t *)(hcryp->Init.pKey + 2);
          hcryp->Instance->K2RR = *(uint32_t *)(hcryp->Init.pKey + 3);
          hcryp->Instance->K3LR = *(uint32_t *)(hcryp->Init.pKey + 4);
          hcryp->Instance->K3RR = *(uint32_t *)(hcryp->Init.pKey + 5);
        }

        /*Set Initialization Vector (IV)*/
        if ((hcryp->Init.Algorithm == CRYP_DES_CBC) || (hcryp->Init.Algorithm == CRYP_TDES_CBC))
        {
          hcryp->Instance->IV0LR = *(uint32_t *)(hcryp->Init.pInitVect);
          hcryp->Instance->IV0RR = *(uint32_t *)(hcryp->Init.pInitVect + 1);
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
    /* Process unlocked */
    __HAL_UNLOCK(hcryp);

    /* Busy error code field */
    hcryp->ErrorCode |= HAL_CRYP_ERROR_BUSY;
    status = HAL_ERROR;
  }

  /* Return function status */
  return status;
}

/**
  * @brief  Encryption in interrupt mode.
  * @param  hcryp: pointer to a CRYP_HandleTypeDef structure that contains
  *         the configuration information for CRYP module
  * @param  Input: Pointer to the input buffer (plaintext)
  * @param  Size: Length of the plaintext buffer either in word or in byte, according to DataWidthUnit
  * @param  Output: Pointer to the output buffer(ciphertext)
  * @retval HAL status
  */
HAL_StatusTypeDef HAL_CRYP_Encrypt_IT(CRYP_HandleTypeDef *hcryp, uint32_t *Input, uint16_t Size, uint32_t *Output)
{
  uint32_t algo;
  HAL_StatusTypeDef status;

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

    /* Set encryption operating mode*/
    MODIFY_REG(hcryp->Instance->CR, CRYP_CR_ALGODIR, CRYP_OPERATINGMODE_ENCRYPT);

    /* algo get algorithm selected */
    algo = (hcryp->Instance->CR & CRYP_CR_ALGOMODE);

    switch (algo)
    {
      case CRYP_DES_ECB:
      case CRYP_DES_CBC:
      case CRYP_TDES_ECB:
      case CRYP_TDES_CBC:

        /*Set Key */
        hcryp->Instance->K1LR = *(uint32_t *)(hcryp->Init.pKey);
        hcryp->Instance->K1RR = *(uint32_t *)(hcryp->Init.pKey + 1);
        if ((hcryp->Init.Algorithm == CRYP_TDES_ECB) || (hcryp->Init.Algorithm == CRYP_TDES_CBC))
        {
          hcryp->Instance->K2LR = *(uint32_t *)(hcryp->Init.pKey + 2);
          hcryp->Instance->K2RR = *(uint32_t *)(hcryp->Init.pKey + 3);
          hcryp->Instance->K3LR = *(uint32_t *)(hcryp->Init.pKey + 4);
          hcryp->Instance->K3RR = *(uint32_t *)(hcryp->Init.pKey + 5);
        }
        /* Set the Initialization Vector*/
        if ((hcryp->Init.Algorithm == CRYP_DES_CBC) || (hcryp->Init.Algorithm == CRYP_TDES_CBC))
        {
          hcryp->Instance->IV0LR = *(uint32_t *)(hcryp->Init.pInitVect);
          hcryp->Instance->IV0RR = *(uint32_t *)(hcryp->Init.pInitVect + 1);
        }

        /* Flush FIFO */
        HAL_CRYP_FIFO_FLUSH(hcryp);

        /* Set the phase */
        hcryp->Phase = CRYP_PHASE_PROCESS;

        /* Enable interrupts */
        __HAL_CRYP_ENABLE_IT(hcryp, CRYP_IT_INI | CRYP_IT_OUTI);

        /* Enable CRYP to start DES/TDES process*/
        __HAL_CRYP_ENABLE(hcryp);

        status = HAL_OK;
        break;

      case CRYP_AES_ECB:
      case CRYP_AES_CBC:
      case CRYP_AES_CTR:

        status = CRYP_AES_Encrypt_IT(hcryp);
        break;

      case CRYP_AES_GCM:

        status = CRYP_AESGCM_Process_IT(hcryp) ;
        break;

      case CRYP_AES_CCM:

        status = CRYP_AESCCM_Process_IT(hcryp);
        break;

      default:
        hcryp->ErrorCode |= HAL_CRYP_ERROR_NOT_SUPPORTED;
        status =  HAL_ERROR;
        break;
    }
  }
  else
  {
    /* Busy error code field */
    hcryp->ErrorCode |= HAL_CRYP_ERROR_BUSY;
    status =  HAL_ERROR;
  }

  /* Return function status */
  return status ;
}

/**
  * @brief  Decryption in itnterrupt mode.
  * @param  hcryp: pointer to a CRYP_HandleTypeDef structure that contains
  *         the configuration information for CRYP module
  * @param  Input: Pointer to the input buffer (ciphertext )
  * @param  Size: Length of the plaintext buffer either in word or in byte, according to DataWidthUnit
  * @param  Output: Pointer to the output buffer(plaintext)
  * @retval HAL status
  */
HAL_StatusTypeDef HAL_CRYP_Decrypt_IT(CRYP_HandleTypeDef *hcryp, uint32_t *Input, uint16_t Size, uint32_t *Output)
{
  uint32_t algo;
  HAL_StatusTypeDef status = HAL_OK;

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
    MODIFY_REG(hcryp->Instance->CR, CRYP_CR_ALGODIR, CRYP_OPERATINGMODE_DECRYPT);

    /* algo get algorithm selected */
    algo = hcryp->Instance->CR & CRYP_CR_ALGOMODE;

    switch (algo)
    {
      case CRYP_DES_ECB:
      case CRYP_DES_CBC:
      case CRYP_TDES_ECB:
      case CRYP_TDES_CBC:

        /*Set Key */
        hcryp->Instance->K1LR = *(uint32_t *)(hcryp->Init.pKey);
        hcryp->Instance->K1RR = *(uint32_t *)(hcryp->Init.pKey + 1);
        if ((hcryp->Init.Algorithm == CRYP_TDES_ECB) || (hcryp->Init.Algorithm == CRYP_TDES_CBC))
        {
          hcryp->Instance->K2LR = *(uint32_t *)(hcryp->Init.pKey + 2);
          hcryp->Instance->K2RR = *(uint32_t *)(hcryp->Init.pKey + 3);
          hcryp->Instance->K3LR = *(uint32_t *)(hcryp->Init.pKey + 4);
          hcryp->Instance->K3RR = *(uint32_t *)(hcryp->Init.pKey + 5);
        }

        /* Set the Initialization Vector*/
        if ((hcryp->Init.Algorithm == CRYP_DES_CBC) || (hcryp->Init.Algorithm == CRYP_TDES_CBC))
        {
          hcryp->Instance->IV0LR = *(uint32_t *)(hcryp->Init.pInitVect);
          hcryp->Instance->IV0RR = *(uint32_t *)(hcryp->Init.pInitVect + 1);
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
        status = CRYP_AESGCM_Process_IT(hcryp) ;
        break;

      case CRYP_AES_CCM:

        /* AES CCMdecryption */
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
  * @param  hcryp: pointer to a CRYP_HandleTypeDef structure that contains
  *         the configuration information for CRYP module
  * @param  Input: Pointer to the input buffer (plaintext)
  * @param  Size: Length of the plaintext buffer either in word or in byte, according to DataWidthUnit
  * @param  Output: Pointer to the output buffer(ciphertext)
  * @retval HAL status
  */
HAL_StatusTypeDef HAL_CRYP_Encrypt_DMA(CRYP_HandleTypeDef *hcryp, uint32_t *Input, uint16_t Size, uint32_t *Output)
{
  HAL_StatusTypeDef status = HAL_OK;
  uint32_t algo;
  uint32_t DoKeyIVConfig = 1U; /* By default, carry out peripheral Key and IV configuration */

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

    /* Set encryption operating mode*/
    MODIFY_REG(hcryp->Instance->CR, CRYP_CR_ALGODIR, CRYP_OPERATINGMODE_ENCRYPT);

    /* algo get algorithm selected */
    algo = hcryp->Instance->CR & CRYP_CR_ALGOMODE;

    switch (algo)
    {
      case CRYP_DES_ECB:
      case CRYP_DES_CBC:
      case CRYP_TDES_ECB:
      case CRYP_TDES_CBC:

        /*Set Key */
        hcryp->Instance->K1LR = *(uint32_t *)(hcryp->Init.pKey);
        hcryp->Instance->K1RR = *(uint32_t *)(hcryp->Init.pKey + 1);
        if ((hcryp->Init.Algorithm == CRYP_TDES_ECB) || (hcryp->Init.Algorithm == CRYP_TDES_CBC))
        {
          hcryp->Instance->K2LR = *(uint32_t *)(hcryp->Init.pKey + 2);
          hcryp->Instance->K2RR = *(uint32_t *)(hcryp->Init.pKey + 3);
          hcryp->Instance->K3LR = *(uint32_t *)(hcryp->Init.pKey + 4);
          hcryp->Instance->K3RR = *(uint32_t *)(hcryp->Init.pKey + 5);
        }

        /* Set the Initialization Vector*/
        if ((hcryp->Init.Algorithm == CRYP_DES_CBC) || (hcryp->Init.Algorithm == CRYP_TDES_CBC))
        {
          hcryp->Instance->IV0LR = *(uint32_t *)(hcryp->Init.pInitVect);
          hcryp->Instance->IV0RR = *(uint32_t *)(hcryp->Init.pInitVect + 1);
        }

        /* Flush FIFO */
        HAL_CRYP_FIFO_FLUSH(hcryp);

        /* Set the phase */
        hcryp->Phase = CRYP_PHASE_PROCESS;

        /* Start DMA process transfer for DES/TDES */
        CRYP_SetDMAConfig(hcryp, (uint32_t)(hcryp->pCrypInBuffPtr), (hcryp->Size / 4U),
                          (uint32_t)(hcryp->pCrypOutBuffPtr));

        break;

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
            hcryp->Instance->IV0LR = *(uint32_t *)(hcryp->Init.pInitVect);
            hcryp->Instance->IV0RR = *(uint32_t *)(hcryp->Init.pInitVect + 1U);
            hcryp->Instance->IV1LR = *(uint32_t *)(hcryp->Init.pInitVect + 2U);
            hcryp->Instance->IV1RR = *(uint32_t *)(hcryp->Init.pInitVect + 3U);
          }
        } /* if (DoKeyIVConfig == 1U) */

        /* Set the phase */
        hcryp->Phase = CRYP_PHASE_PROCESS;

        /* Start DMA process transfer for AES */
        CRYP_SetDMAConfig(hcryp, (uint32_t)(hcryp->pCrypInBuffPtr), (hcryp->Size / 4U),
                          (uint32_t)(hcryp->pCrypOutBuffPtr));
        break;

      case CRYP_AES_GCM:

        /* AES GCM encryption */
        status = CRYP_AESGCM_Process_DMA(hcryp) ;
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
  * @param  Size: Length of the plaintext buffer either in word or in byte, according to DataWidthUnit
  * @param  Output: Pointer to the output buffer(plaintext)
  * @retval HAL status
  */
HAL_StatusTypeDef HAL_CRYP_Decrypt_DMA(CRYP_HandleTypeDef *hcryp, uint32_t *Input, uint16_t Size, uint32_t *Output)
{
  uint32_t algo;
  HAL_StatusTypeDef status = HAL_OK;

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
    MODIFY_REG(hcryp->Instance->CR, CRYP_CR_ALGODIR, CRYP_OPERATINGMODE_DECRYPT);

    /* algo get algorithm selected */
    algo = hcryp->Instance->CR & CRYP_CR_ALGOMODE;

    switch (algo)
    {
      case CRYP_DES_ECB:
      case CRYP_DES_CBC:
      case CRYP_TDES_ECB:
      case CRYP_TDES_CBC:

        /*Set Key */
        hcryp->Instance->K1LR = *(uint32_t *)(hcryp->Init.pKey);
        hcryp->Instance->K1RR = *(uint32_t *)(hcryp->Init.pKey + 1);
        if ((hcryp->Init.Algorithm == CRYP_TDES_ECB) || (hcryp->Init.Algorithm == CRYP_TDES_CBC))
        {
          hcryp->Instance->K2LR = *(uint32_t *)(hcryp->Init.pKey + 2);
          hcryp->Instance->K2RR = *(uint32_t *)(hcryp->Init.pKey + 3);
          hcryp->Instance->K3LR = *(uint32_t *)(hcryp->Init.pKey + 4);
          hcryp->Instance->K3RR = *(uint32_t *)(hcryp->Init.pKey + 5);
        }

        /* Set the Initialization Vector*/
        if ((hcryp->Init.Algorithm == CRYP_DES_CBC) || (hcryp->Init.Algorithm == CRYP_TDES_CBC))
        {
          hcryp->Instance->IV0LR = *(uint32_t *)(hcryp->Init.pInitVect);
          hcryp->Instance->IV0RR = *(uint32_t *)(hcryp->Init.pInitVect + 1);
        }

        /* Flush FIFO */
        HAL_CRYP_FIFO_FLUSH(hcryp);

        /* Set the phase */
        hcryp->Phase = CRYP_PHASE_PROCESS;

        /* Start DMA process transfer for DES/TDES */
        CRYP_SetDMAConfig(hcryp, (uint32_t)(hcryp->pCrypInBuffPtr), (hcryp->Size / 4U),
                          (uint32_t)(hcryp->pCrypOutBuffPtr));
        break;

      case CRYP_AES_ECB:
      case CRYP_AES_CBC:
      case CRYP_AES_CTR:

        /* AES decryption */
        status = CRYP_AES_Decrypt_DMA(hcryp);
        break;

      case CRYP_AES_GCM:

        /* AES GCM decryption */
        status = CRYP_AESGCM_Process_DMA(hcryp) ;

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
  *  @brief    CRYP IRQ handler.
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
  uint32_t itstatus = hcryp->Instance->MISR;

  if ((itstatus & (CRYP_IT_INI | CRYP_IT_OUTI)) != 0U)
  {
    if ((hcryp->Init.Algorithm == CRYP_DES_ECB) || (hcryp->Init.Algorithm == CRYP_DES_CBC) ||
        (hcryp->Init.Algorithm == CRYP_TDES_ECB) || (hcryp->Init.Algorithm == CRYP_TDES_CBC))
    {
      CRYP_TDES_IT(hcryp); /* DES or TDES*/
    }
    else if ((hcryp->Init.Algorithm == CRYP_AES_ECB) || (hcryp->Init.Algorithm == CRYP_AES_CBC) ||
             (hcryp->Init.Algorithm == CRYP_AES_CTR))
    {
      CRYP_AES_IT(hcryp); /*AES*/
    }

    else if ((hcryp->Init.Algorithm == CRYP_AES_GCM) || (hcryp->Init.Algorithm == CRYP_CR_ALGOMODE_AES_CCM))
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
    else
    {
      /* Nothing to do */
    }
  }
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
/**
  * @}
  */

/* Private functions ---------------------------------------------------------*/
/** @addtogroup CRYP_Private_Functions
  * @{
  */

/**
  * @brief  Encryption in ECB/CBC Algorithm with DES/TDES standard.
  * @param  hcryp: pointer to a CRYP_HandleTypeDef structure that contains
  *         the configuration information for CRYP module
  * @param  Timeout: Timeout value
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
  while ((hcryp->CrypInCount < (hcryp->Size / 4U)) && (outcount < (hcryp->Size / 4U)))
  {
    /* Temporary CrypInCount Value */
    incount = hcryp->CrypInCount;
    /* Write plain data and get cipher data */
    if (((hcryp->Instance->SR & CRYP_FLAG_IFNF) != 0x0U) && (incount < (hcryp->Size / 4U)))
    {
      /* Write the input block in the IN FIFO */
      hcryp->Instance->DIN  = *(uint32_t *)(hcryp->pCrypInBuffPtr + hcryp->CrypInCount);
      hcryp->CrypInCount++;
      hcryp->Instance->DIN  = *(uint32_t *)(hcryp->pCrypInBuffPtr + hcryp->CrypInCount);
      hcryp->CrypInCount++;
    }

    /* Wait for OFNE flag to be raised */
    if (CRYP_WaitOnOFNEFlag(hcryp, Timeout) != HAL_OK)
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

    if (((hcryp->Instance->SR & CRYP_FLAG_OFNE) != 0x0U) && (outcount < (hcryp->Size / 4U)))
    {
      /* Read the output block from the Output FIFO and put them in temporary Buffer
       then get CrypOutBuff from temporary buffer  */
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
  * @retval HAL status
  */
static void CRYP_TDES_IT(CRYP_HandleTypeDef *hcryp)
{
  uint32_t temp;  /* Temporary CrypOutBuff */

  if (hcryp->State == HAL_CRYP_STATE_BUSY)
  {
    if (__HAL_CRYP_GET_IT(hcryp, CRYP_IT_INI) != 0x0U)
    {
      if (__HAL_CRYP_GET_FLAG(hcryp, CRYP_FLAG_INRIS) != 0x0U)
      {
        /* Write input block in the IN FIFO */
        hcryp->Instance->DIN = *(uint32_t *)(hcryp->pCrypInBuffPtr + hcryp->CrypInCount);
        hcryp->CrypInCount++;
        hcryp->Instance->DIN = *(uint32_t *)(hcryp->pCrypInBuffPtr + hcryp->CrypInCount);
        hcryp->CrypInCount++;

        if (hcryp->CrypInCount == (hcryp->Size / 4U))
        {
          /* Disable interruption */
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
    }

    if (__HAL_CRYP_GET_IT(hcryp, CRYP_IT_OUTI) != 0x0U)
    {
      if (__HAL_CRYP_GET_FLAG(hcryp, CRYP_FLAG_OUTRIS) != 0x0U)
      {
        /* Read the output block from the Output FIFO and put them in temporary Buffer
         then get CrypOutBuff from temporary buffer  */
        temp = hcryp->Instance->DOUT;
        *(uint32_t *)(hcryp->pCrypOutBuffPtr + (hcryp->CrypOutCount)) = temp;
        hcryp->CrypOutCount++;
        temp = hcryp->Instance->DOUT;
        *(uint32_t *)(hcryp->pCrypOutBuffPtr + (hcryp->CrypOutCount)) = temp;
        hcryp->CrypOutCount++;
        if (hcryp->CrypOutCount == (hcryp->Size / 4U))
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

/**
  * @brief  Encryption in ECB/CBC & CTR Algorithm with AES Standard
  * @param  hcryp: pointer to a CRYP_HandleTypeDef structure
  * @param  Timeout: specify Timeout value
  * @retval HAL status
  */
static HAL_StatusTypeDef CRYP_AES_Encrypt(CRYP_HandleTypeDef *hcryp, uint32_t Timeout)
{
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
      hcryp->Instance->IV0LR = *(uint32_t *)(hcryp->Init.pInitVect);
      hcryp->Instance->IV0RR = *(uint32_t *)(hcryp->Init.pInitVect + 1U);
      hcryp->Instance->IV1LR = *(uint32_t *)(hcryp->Init.pInitVect + 2U);
      hcryp->Instance->IV1RR = *(uint32_t *)(hcryp->Init.pInitVect + 3U);
    }
  } /* if (DoKeyIVConfig == 1U) */

  /* Set the phase */
  hcryp->Phase = CRYP_PHASE_PROCESS;

  /* Enable CRYP */
  __HAL_CRYP_ENABLE(hcryp);
  /*Temporary CrypOutCount Value*/
  outcount = hcryp->CrypOutCount;

  while ((hcryp->CrypInCount < (hcryp->Size / 4U)) && (outcount < (hcryp->Size / 4U)))
  {
    /* Write plain Ddta and get cipher data */
    CRYP_AES_ProcessData(hcryp, Timeout);
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
      hcryp->Instance->IV0LR = *(uint32_t *)(hcryp->Init.pInitVect);
      hcryp->Instance->IV0RR = *(uint32_t *)(hcryp->Init.pInitVect + 1U);
      hcryp->Instance->IV1LR = *(uint32_t *)(hcryp->Init.pInitVect + 2U);
      hcryp->Instance->IV1RR = *(uint32_t *)(hcryp->Init.pInitVect + 3U);
    }
  } /* if (DoKeyIVConfig == 1U) */

  /* Set the phase */
  hcryp->Phase = CRYP_PHASE_PROCESS;

  if (hcryp->Size != 0U)
  {
    /* Enable interrupts */
    __HAL_CRYP_ENABLE_IT(hcryp, CRYP_IT_INI | CRYP_IT_OUTI);

    /* Enable CRYP */
    __HAL_CRYP_ENABLE(hcryp);
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
static HAL_StatusTypeDef CRYP_AES_Decrypt(CRYP_HandleTypeDef *hcryp, uint32_t Timeout)
{
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
      /* change ALGOMODE to key preparation for decryption*/
      MODIFY_REG(hcryp->Instance->CR, CRYP_CR_ALGOMODE, CRYP_CR_ALGOMODE_AES_KEY);

      /*  Set the Key*/
      CRYP_SetKey(hcryp, hcryp->Init.KeySize);

      /* Enable CRYP */
      __HAL_CRYP_ENABLE(hcryp);

      /* Wait for BUSY flag to be raised */
      if (CRYP_WaitOnBUSYFlag(hcryp, Timeout) != HAL_OK)
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
      MODIFY_REG(hcryp->Instance->CR, CRYP_CR_ALGOMODE, hcryp->Init.Algorithm);
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
      hcryp->Instance->IV0LR = *(uint32_t *)(hcryp->Init.pInitVect);
      hcryp->Instance->IV0RR = *(uint32_t *)(hcryp->Init.pInitVect + 1);
      hcryp->Instance->IV1LR = *(uint32_t *)(hcryp->Init.pInitVect + 2);
      hcryp->Instance->IV1RR = *(uint32_t *)(hcryp->Init.pInitVect + 3);
    }
  } /* if (DoKeyIVConfig == 1U) */

  /* Set the phase */
  hcryp->Phase = CRYP_PHASE_PROCESS;

  /* Enable CRYP */
  __HAL_CRYP_ENABLE(hcryp);

  /*Temporary CrypOutCount Value*/
  outcount = hcryp->CrypOutCount;

  while ((hcryp->CrypInCount < (hcryp->Size / 4U)) && (outcount < (hcryp->Size / 4U)))
  {
    /* Write plain data and get cipher data */
    CRYP_AES_ProcessData(hcryp, Timeout);
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
      /* change ALGOMODE to key preparation for decryption*/
      MODIFY_REG(hcryp->Instance->CR, CRYP_CR_ALGOMODE, CRYP_CR_ALGOMODE_AES_KEY);

      /*  Set the Key*/
      CRYP_SetKey(hcryp, hcryp->Init.KeySize);

      /* Enable CRYP */
      __HAL_CRYP_ENABLE(hcryp);

      /* Wait for BUSY flag to be raised */
      count = CRYP_TIMEOUT_KEYPREPARATION;
      do
      {
        count-- ;
        if (count == 0U)
        {
          /* Change state */
          hcryp->ErrorCode |= HAL_CRYP_ERROR_TIMEOUT;
          hcryp->State = HAL_CRYP_STATE_READY;

          /* Process unlocked */
          __HAL_UNLOCK(hcryp);
          return HAL_ERROR;
        }
      }
      while (HAL_IS_BIT_SET(hcryp->Instance->SR, CRYP_FLAG_BUSY));

      /* Turn back to ALGOMODE of the configuration */
      MODIFY_REG(hcryp->Instance->CR, CRYP_CR_ALGOMODE, hcryp->Init.Algorithm);
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
      hcryp->Instance->IV0LR = *(uint32_t *)(hcryp->Init.pInitVect);
      hcryp->Instance->IV0RR = *(uint32_t *)(hcryp->Init.pInitVect + 1);
      hcryp->Instance->IV1LR = *(uint32_t *)(hcryp->Init.pInitVect + 2);
      hcryp->Instance->IV1RR = *(uint32_t *)(hcryp->Init.pInitVect + 3);
    }
  } /* if (DoKeyIVConfig == 1U) */

  /* Set the phase */
  hcryp->Phase = CRYP_PHASE_PROCESS;
  if (hcryp->Size != 0U)
  {
    /* Enable interrupts */
    __HAL_CRYP_ENABLE_IT(hcryp, CRYP_IT_INI | CRYP_IT_OUTI);

    /* Enable CRYP */
    __HAL_CRYP_ENABLE(hcryp);
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
      /* change ALGOMODE to key preparation for decryption*/
      MODIFY_REG(hcryp->Instance->CR, CRYP_CR_ALGOMODE, CRYP_CR_ALGOMODE_AES_KEY);

      /*  Set the Key*/
      CRYP_SetKey(hcryp, hcryp->Init.KeySize);

      /* Enable CRYP */
      __HAL_CRYP_ENABLE(hcryp);

      /* Wait for BUSY flag to be raised */
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
      while (HAL_IS_BIT_SET(hcryp->Instance->SR, CRYP_FLAG_BUSY));

      /* Turn back to ALGOMODE of the configuration */
      MODIFY_REG(hcryp->Instance->CR, CRYP_CR_ALGOMODE, hcryp->Init.Algorithm);
    }
    else  /*Algorithm CTR */
    {
      /*  Set the Key*/
      CRYP_SetKey(hcryp, hcryp->Init.KeySize);
    }

    if (hcryp->Init.Algorithm != CRYP_AES_ECB)
    {
      /* Set the Initialization Vector*/
      hcryp->Instance->IV0LR = *(uint32_t *)(hcryp->Init.pInitVect);
      hcryp->Instance->IV0RR = *(uint32_t *)(hcryp->Init.pInitVect + 1);
      hcryp->Instance->IV1LR = *(uint32_t *)(hcryp->Init.pInitVect + 2);
      hcryp->Instance->IV1RR = *(uint32_t *)(hcryp->Init.pInitVect + 3);
    }
  } /* if (DoKeyIVConfig == 1U) */

  /* Set the phase */
  hcryp->Phase = CRYP_PHASE_PROCESS;

  if (hcryp->Size != 0U)
  {
    /* Set the input and output addresses and start DMA transfer */
    CRYP_SetDMAConfig(hcryp, (uint32_t)(hcryp->pCrypInBuffPtr), (hcryp->Size / 4U),
                      (uint32_t)(hcryp->pCrypOutBuffPtr));
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
  CRYP_HandleTypeDef *hcryp = (CRYP_HandleTypeDef *)((DMA_HandleTypeDef *)hdma)->Parent;

  /* Disable the DMA transfer for input FIFO request by resetting the DIEN bit
  in the DMACR register */
  hcryp->Instance->DMACR &= (uint32_t)(~CRYP_DMACR_DIEN);

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
  uint32_t count;
  uint32_t npblb;
  uint32_t lastwordsize;
  uint32_t temp;  /* Temporary CrypOutBuff */
  uint32_t temp_cr_algodir;
  CRYP_HandleTypeDef *hcryp = (CRYP_HandleTypeDef *)((DMA_HandleTypeDef *)hdma)->Parent;


  /* Disable the DMA transfer for output FIFO */
  hcryp->Instance->DMACR &= (uint32_t)(~CRYP_DMACR_DOEN);

  /* Last block transfer in case of GCM or CCM with Size not %16*/
  if (((hcryp->Size) % 16U) != 0U)
  {
    /* set CrypInCount and CrypOutCount to exact number of word already computed via DMA  */
    hcryp->CrypInCount = (hcryp->Size / 16U) * 4U ;
    hcryp->CrypOutCount = hcryp->CrypInCount;

    /* Compute the number of padding bytes in last block of payload */
    npblb = ((((uint32_t)(hcryp->Size) / 16U) + 1U) * 16U) - (uint32_t)(hcryp->Size);

#if !defined (CRYP_VER_2_2)
    if (hcryp->Version >= REV_ID_B)
#endif /*End of not defined CRYP_VER_2_2*/
    {
      /* Case of AES GCM payload encryption or AES CCM payload decryption to get right tag */
      temp_cr_algodir = hcryp->Instance->CR & CRYP_CR_ALGODIR;
      if (((temp_cr_algodir == CRYP_OPERATINGMODE_ENCRYPT) && (hcryp->Init.Algorithm == CRYP_AES_GCM)) ||
          ((temp_cr_algodir == CRYP_OPERATINGMODE_DECRYPT) && (hcryp->Init.Algorithm == CRYP_AES_CCM)))
      {
        /* Disable the CRYP */
        __HAL_CRYP_DISABLE(hcryp);

        /* Specify the number of non-valid bytes using NPBLB register*/
        MODIFY_REG(hcryp->Instance->CR, CRYP_CR_NPBLB, npblb << 20);

        /* Enable CRYP to start the final phase */
        __HAL_CRYP_ENABLE(hcryp);
      }
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
    for (count = 0U; count < lastwordsize; count ++)
    {
      hcryp->Instance->DIN  = *(uint32_t *)(hcryp->pCrypInBuffPtr + hcryp->CrypInCount);
      hcryp->CrypInCount++;
    }
    /* Pad the data with zeros to have a complete block */
    while (count < 4U)
    {
      hcryp->Instance->DIN  = 0U;
      count++;
    }
    /* Wait for OFNE flag to be raised */
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
#if (USE_HAL_CRYP_REGISTER_CALLBACKS == 1)
        /*Call registered error callback*/
        hcryp->ErrorCallback(hcryp);
#else
        /*Call legacy weak error callback*/
        HAL_CRYP_ErrorCallback(hcryp);
#endif /* USE_HAL_CRYP_REGISTER_CALLBACKS */
      }
    }
    while (HAL_IS_BIT_CLR(hcryp->Instance->SR, CRYP_FLAG_OFNE));

    /*Read the output block from the output FIFO */
    for (count = 0U; count < 4U; count++)
    {
      /* Read the output block from the output FIFO and put them in temporary buffer
         then get CrypOutBuff from temporary buffer */
      temp = hcryp->Instance->DOUT;

      *(uint32_t *)(hcryp->pCrypOutBuffPtr + (hcryp->CrypOutCount)) = temp;
      hcryp->CrypOutCount++;
    }
  } /*End of last block transfer in case of GCM or CCM */

  if ((hcryp->Init.Algorithm & CRYP_AES_GCM) != CRYP_AES_GCM)
  {
    /* Disable CRYP  (not allowed in  GCM)*/
    __HAL_CRYP_DISABLE(hcryp);
  }

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
  CRYP_HandleTypeDef *hcryp = (CRYP_HandleTypeDef *)((DMA_HandleTypeDef *)hdma)->Parent;

  /* Change the CRYP peripheral state */
  hcryp->State = HAL_CRYP_STATE_READY;

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

  /* Enable CRYP */
  __HAL_CRYP_ENABLE(hcryp);

  /* Enable the input DMA Stream */
  if (HAL_DMA_Start_IT(hcryp->hdmain, inputaddr, (uint32_t)&hcryp->Instance->DIN, Size) != HAL_OK)
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
  if (HAL_DMA_Start_IT(hcryp->hdmaout, (uint32_t)&hcryp->Instance->DOUT, outputaddr, Size) != HAL_OK)
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

  uint32_t temp[4];  /* Temporary CrypOutBuff */
  uint16_t incount;  /* Temporary CrypInCount Value */
  uint16_t outcount;  /* Temporary CrypOutCount Value */
  uint32_t i;

  /*Temporary CrypOutCount Value*/
  incount = hcryp->CrypInCount;

  if (((hcryp->Instance->SR & CRYP_FLAG_IFNF) != 0x0U) && (incount < ((hcryp->Size) / 4U)))
  {
    /* Write the input block in the IN FIFO */
    hcryp->Instance->DIN  = *(uint32_t *)(hcryp->pCrypInBuffPtr + hcryp->CrypInCount);
    hcryp->CrypInCount++;
    hcryp->Instance->DIN  = *(uint32_t *)(hcryp->pCrypInBuffPtr + hcryp->CrypInCount);
    hcryp->CrypInCount++;
    hcryp->Instance->DIN  = *(uint32_t *)(hcryp->pCrypInBuffPtr + hcryp->CrypInCount);
    hcryp->CrypInCount++;
    hcryp->Instance->DIN  = *(uint32_t *)(hcryp->pCrypInBuffPtr + hcryp->CrypInCount);
    hcryp->CrypInCount++;
  }

  /* Wait for OFNE flag to be raised */
  if (CRYP_WaitOnOFNEFlag(hcryp, Timeout) != HAL_OK)
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

  if (((hcryp->Instance->SR & CRYP_FLAG_OFNE) != 0x0U) && (outcount < ((hcryp->Size) / 4U)))
  {
    /* Read the output block from the Output FIFO and put them in temporary buffer
       then get CrypOutBuff from temporary buffer  */
    for (i = 0U; i < 4U; i++)
    {
      temp[i] = hcryp->Instance->DOUT;
    }
    i = 0U;
    while (((hcryp->CrypOutCount < ((hcryp->Size) / 4U))) && (i < 4U))
    {
      *(uint32_t *)(hcryp->pCrypOutBuffPtr + hcryp->CrypOutCount) = temp[i];
      hcryp->CrypOutCount++;
      i++;
    }
  }
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
  uint32_t temp[4];  /* Temporary CrypOutBuff */
  uint16_t incount; /* Temporary CrypInCount Value */
  uint16_t outcount;  /* Temporary CrypOutCount Value */
  uint32_t i;

  if (hcryp->State == HAL_CRYP_STATE_BUSY)
  {
    /*Temporary CrypOutCount Value*/
    incount = hcryp->CrypInCount;

    if (((hcryp->Instance->SR & CRYP_FLAG_IFNF) != 0x0U) && (incount < (hcryp->Size / 4U)))
    {
      /* Write the input block in the IN FIFO */
      hcryp->Instance->DIN  = *(uint32_t *)(hcryp->pCrypInBuffPtr + hcryp->CrypInCount);
      hcryp->CrypInCount++;
      hcryp->Instance->DIN  = *(uint32_t *)(hcryp->pCrypInBuffPtr + hcryp->CrypInCount);
      hcryp->CrypInCount++;
      hcryp->Instance->DIN  = *(uint32_t *)(hcryp->pCrypInBuffPtr + hcryp->CrypInCount);
      hcryp->CrypInCount++;
      hcryp->Instance->DIN  = *(uint32_t *)(hcryp->pCrypInBuffPtr + hcryp->CrypInCount);
      hcryp->CrypInCount++;
      if (hcryp->CrypInCount == (hcryp->Size / 4U))
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

    if (((hcryp->Instance->SR & CRYP_FLAG_OFNE) != 0x0U) && (outcount < (hcryp->Size / 4U)))
    {
      /* Read the output block from the output FIFO and put them in temporary buffer
         then get CrypOutBuff from temporary buffer  */
      for (i = 0U; i < 4U; i++)
      {
        temp[i] = hcryp->Instance->DOUT;
      }
      i = 0U;
      while (((hcryp->CrypOutCount < ((hcryp->Size) / 4U))) && (i < 4U))
      {
        *(uint32_t *)(hcryp->pCrypOutBuffPtr + hcryp->CrypOutCount) = temp[i];
        hcryp->CrypOutCount++;
        i++;
      }
      if (hcryp->CrypOutCount == (hcryp->Size / 4U))
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

/**
  * @brief  Writes Key in Key registers.
  * @param  hcryp: pointer to a CRYP_HandleTypeDef structure that contains
  *         the configuration information for CRYP module
  * @param  KeySize: Size of Key
  * @retval None
  */
static void CRYP_SetKey(CRYP_HandleTypeDef *hcryp, uint32_t KeySize)
{
  switch (KeySize)
  {
    case CRYP_KEYSIZE_256B:
      hcryp->Instance->K0LR = *(uint32_t *)(hcryp->Init.pKey);
      hcryp->Instance->K0RR = *(uint32_t *)(hcryp->Init.pKey + 1);
      hcryp->Instance->K1LR = *(uint32_t *)(hcryp->Init.pKey + 2);
      hcryp->Instance->K1RR = *(uint32_t *)(hcryp->Init.pKey + 3);
      hcryp->Instance->K2LR = *(uint32_t *)(hcryp->Init.pKey + 4);
      hcryp->Instance->K2RR = *(uint32_t *)(hcryp->Init.pKey + 5);
      hcryp->Instance->K3LR = *(uint32_t *)(hcryp->Init.pKey + 6);
      hcryp->Instance->K3RR = *(uint32_t *)(hcryp->Init.pKey + 7);
      break;
    case CRYP_KEYSIZE_192B:
      hcryp->Instance->K1LR = *(uint32_t *)(hcryp->Init.pKey);
      hcryp->Instance->K1RR = *(uint32_t *)(hcryp->Init.pKey + 1);
      hcryp->Instance->K2LR = *(uint32_t *)(hcryp->Init.pKey + 2);
      hcryp->Instance->K2RR = *(uint32_t *)(hcryp->Init.pKey + 3);
      hcryp->Instance->K3LR = *(uint32_t *)(hcryp->Init.pKey + 4);
      hcryp->Instance->K3RR = *(uint32_t *)(hcryp->Init.pKey + 5);
      break;
    case CRYP_KEYSIZE_128B:
      hcryp->Instance->K2LR = *(uint32_t *)(hcryp->Init.pKey);
      hcryp->Instance->K2RR = *(uint32_t *)(hcryp->Init.pKey + 1);
      hcryp->Instance->K3LR = *(uint32_t *)(hcryp->Init.pKey + 2);
      hcryp->Instance->K3RR = *(uint32_t *)(hcryp->Init.pKey + 3);

      break;
    default:
      break;
  }
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
  uint32_t wordsize = (uint32_t)(hcryp->Size) / 4U;
  uint32_t npblb ;
  uint32_t temp[4];  /* Temporary CrypOutBuff */
  uint32_t index ;
  uint32_t lastwordsize ;
  uint32_t nolastpaddingbytes;
  uint8_t *pval;
  uint16_t outcount;  /* Temporary CrypOutCount Value */
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
    hcryp->Instance->IV0LR = *(uint32_t *)(hcryp->Init.pInitVect);
    hcryp->Instance->IV0RR = *(uint32_t *)(hcryp->Init.pInitVect + 1);
    hcryp->Instance->IV1LR = *(uint32_t *)(hcryp->Init.pInitVect + 2);
    hcryp->Instance->IV1RR = *(uint32_t *)(hcryp->Init.pInitVect + 3);

    /* Enable the CRYP peripheral */
    __HAL_CRYP_ENABLE(hcryp);

    /* Get tick */
    tickstart = HAL_GetTick();

    /*Wait for the CRYPEN bit to be cleared*/
    while ((hcryp->Instance->CR & CRYP_CR_CRYPEN) == CRYP_CR_CRYPEN)
    {
      /* Check for the Timeout */
      if (Timeout != HAL_MAX_DELAY)
      {
        if (((HAL_GetTick() - tickstart) > Timeout) || (Timeout == 0U))
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

    /************************ Header phase *************************************/

    if (CRYP_GCMCCM_SetHeaderPhase(hcryp,  Timeout) != HAL_OK)
    {
      return HAL_ERROR;
    }

    /*************************Payload phase ************************************/

    /* Set the phase */
    hcryp->Phase = CRYP_PHASE_PROCESS;

    /* Disable the CRYP peripheral */
    __HAL_CRYP_DISABLE(hcryp);

#if !defined (CRYP_VER_2_2)
    if (hcryp->Version >= REV_ID_B)
#endif /*End of not defined CRYP_VER_2_2*/
    {
      /* Set to 0 the number of non-valid bytes using NPBLB register*/
      MODIFY_REG(hcryp->Instance->CR, CRYP_CR_NPBLB, 0U);
    }

    /* Select payload phase once the header phase is performed */
    CRYP_SET_PHASE(hcryp, CRYP_PHASE_PAYLOAD);

    /* Enable the CRYP peripheral */
    __HAL_CRYP_ENABLE(hcryp);
  } /* if (DoKeyIVConfig == 1U) */

  if ((hcryp->Size % 16U) != 0U)
  {
    /* recalculate  wordsize */
    wordsize = ((wordsize / 4U) * 4U) ;
  }

  /* Get tick */
  tickstart = HAL_GetTick();
  /*Temporary CrypOutCount Value*/
  outcount = hcryp->CrypOutCount;

  /* Write input data and get output Data */
  while ((hcryp->CrypInCount < wordsize) && (outcount < wordsize))
  {
    /* Write plain data and get cipher data */
    CRYP_AES_ProcessData(hcryp, Timeout);

    /*Temporary CrypOutCount Value*/
    outcount = hcryp->CrypOutCount;

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
  }

  if ((hcryp->Size % 16U) != 0U)
  {

#if !defined (CRYP_VER_2_2)
    if (hcryp->Version >= REV_ID_B)
#endif /*End of not defined CRYP_VER_2_2*/
    {
      /* Compute the number of padding bytes in last block of payload */
      npblb = ((((uint32_t)(hcryp->Size) / 16U) + 1U) * 16U) - (uint32_t)(hcryp->Size);

      /*  Set Npblb in case of AES GCM payload encryption to get right tag*/
      if ((hcryp->Instance->CR & CRYP_CR_ALGODIR) == CRYP_OPERATINGMODE_ENCRYPT)
      {
        /* Disable the CRYP */
        __HAL_CRYP_DISABLE(hcryp);

        /* Specify the number of non-valid bytes using NPBLB register*/
        MODIFY_REG(hcryp->Instance->CR, CRYP_CR_NPBLB, npblb << 20);

        /* Enable CRYP to start the final phase */
        __HAL_CRYP_ENABLE(hcryp);
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
      for (index = 0U; index < lastwordsize; index ++)
      {
        hcryp->Instance->DIN  = *(uint32_t *)(hcryp->pCrypInBuffPtr + hcryp->CrypInCount);
        hcryp->CrypInCount++;
      }

      /* Pad the data with zeros to have a complete block */
      while (index < 4U)
      {
        hcryp->Instance->DIN  = 0U;
        index++;
      }

      /* Wait for OFNE flag to be raised */
      if (CRYP_WaitOnOFNEFlag(hcryp, Timeout) != HAL_OK)
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

      /*Read the output block from the output FIFO */
      if ((hcryp->Instance->SR & CRYP_FLAG_OFNE) != 0x0U)
      {
        for (index = 0U; index < 4U; index++)
        {
          /* Read the output block from the output FIFO and put them in temporary buffer
          then get CrypOutBuff from temporary buffer */
          temp[index] = hcryp->Instance->DOUT;
        }

        for (index = 0U; index < lastwordsize; index++)
        {
          pval = (uint8_t *)(hcryp->pCrypOutBuffPtr + (hcryp->CrypOutCount));

          if (index == (lastwordsize - 1U))
          {
            nolastpaddingbytes = npblb % 4U;

            switch (nolastpaddingbytes)
            {
              case 1:
                *(pval) = (uint8_t)(temp[index]);
                pval++;
                *(pval) = (uint8_t)(temp[index] >> 8U);
                pval++;
                *(pval) = (uint8_t)(temp[index] >> 16U);
                break;
              case 2:
                *(pval) = (uint8_t)(temp[index]);
                pval++;
                *(pval) = (uint8_t)(temp[index] >> 8U);
                break;
              case 3:
                *(pval) = (uint8_t)(temp[index]);
                break;
              default:
                *(pval) = (uint8_t)(temp[index]);
                pval++;
                *(pval) = (uint8_t)(temp[index] >> 8U);
                pval++;
                *(pval) = (uint8_t)(temp[index] >> 16U);
                pval++;
                *(pval) = (uint8_t)(temp[index] >> 24U);
                break;
            }
          }
          else
          {
            *(uint32_t *)(hcryp->pCrypOutBuffPtr + (hcryp->CrypOutCount)) = temp[index];
          }

          hcryp->CrypOutCount++;
        }
      }
    }
#if !defined (CRYP_VER_2_2)
    else /*  Workaround to be used */
    {
      /*  Workaround 2 for STM32H7 below rev.B To generate correct TAG only when size of the last block of
      payload is inferior to 128 bits, in case of GCM encryption or CCM decryption*/
      CRYP_Workaround(hcryp, Timeout);
    } /* end of NPBLB or Workaround*/
#endif /*End of not defined CRYP_VER_2_2*/
  }

  /* Return function status */
  return HAL_OK;
}

/**
  * @brief  Encryption/Decryption process in AES GCM mode and prepare the authentication TAG in interrupt mode
  * @param  hcryp: pointer to a CRYP_HandleTypeDef structure that contains
  *         the configuration information for CRYP module
  * @retval HAL status
  */
static HAL_StatusTypeDef CRYP_AESGCM_Process_IT(CRYP_HandleTypeDef *hcryp)
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
    hcryp->Instance->IV0LR = *(uint32_t *)(hcryp->Init.pInitVect);
    hcryp->Instance->IV0RR = *(uint32_t *)(hcryp->Init.pInitVect + 1);
    hcryp->Instance->IV1LR = *(uint32_t *)(hcryp->Init.pInitVect + 2);
    hcryp->Instance->IV1RR = *(uint32_t *)(hcryp->Init.pInitVect + 3);

    /* Enable the CRYP peripheral */
    __HAL_CRYP_ENABLE(hcryp);

    /*Wait for the CRYPEN bit to be cleared*/
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
    while ((hcryp->Instance->CR & CRYP_CR_CRYPEN) == CRYP_CR_CRYPEN);

    /***************************** Header phase *********************************/

    /* Select header phase */
    CRYP_SET_PHASE(hcryp, CRYP_PHASE_HEADER);
  } /* end of if (DoKeyIVConfig == 1U) */
  /* Enable interrupts */
  __HAL_CRYP_ENABLE_IT(hcryp, CRYP_IT_INI);

  /* Enable CRYP */
  __HAL_CRYP_ENABLE(hcryp);

  /* Return function status */
  return HAL_OK;
}


/**
  * @brief  Encryption/Decryption process in AES GCM mode and prepare the authentication TAG using DMA
  * @param  hcryp: pointer to a CRYP_HandleTypeDef structure that contains
  *         the configuration information for CRYP module
  * @retval HAL status
  */
static HAL_StatusTypeDef CRYP_AESGCM_Process_DMA(CRYP_HandleTypeDef *hcryp)
{
  __IO uint32_t count = 0U;
  uint32_t wordsize = (uint32_t)(hcryp->Size) / 4U ;
  uint32_t index;
  uint32_t npblb;
  uint32_t lastwordsize;
  uint32_t temp[4];  /* Temporary CrypOutBuff */
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
    hcryp->Instance->IV0LR = *(uint32_t *)(hcryp->Init.pInitVect);
    hcryp->Instance->IV0RR = *(uint32_t *)(hcryp->Init.pInitVect + 1);
    hcryp->Instance->IV1LR = *(uint32_t *)(hcryp->Init.pInitVect + 2);
    hcryp->Instance->IV1RR = *(uint32_t *)(hcryp->Init.pInitVect + 3);

    /* Enable the CRYP peripheral */
    __HAL_CRYP_ENABLE(hcryp);

    /*Wait for the CRYPEN bit to be cleared*/
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
    while ((hcryp->Instance->CR & CRYP_CR_CRYPEN) == CRYP_CR_CRYPEN);

    /************************ Header phase *************************************/

    if (CRYP_GCMCCM_SetHeaderPhase_DMA(hcryp) != HAL_OK)
    {
      return HAL_ERROR;
    }

    /************************ Payload phase ************************************/

    /* Set the phase */
    hcryp->Phase = CRYP_PHASE_PROCESS;

    /* Disable the CRYP peripheral */
    __HAL_CRYP_DISABLE(hcryp);

#if !defined (CRYP_VER_2_2)
    if (hcryp->Version >= REV_ID_B)
#endif /*End of not defined CRYP_VER_2_2*/
    {
      /* Set to 0 the number of non-valid bytes using NPBLB register*/
      MODIFY_REG(hcryp->Instance->CR, CRYP_CR_NPBLB, 0U);
    }

    /* Select payload phase once the header phase is performed */
    CRYP_SET_PHASE(hcryp, CRYP_PHASE_PAYLOAD);

  } /* if (DoKeyIVConfig == 1U) */

  if (hcryp->Size == 0U)
  {
    /* Process unLocked */
    __HAL_UNLOCK(hcryp);

    /* Change the CRYP state and phase */
    hcryp->State = HAL_CRYP_STATE_READY;
  }
  else if (hcryp->Size >= 16U)
  {
    /* for STM32H7 below rev.B : Size should be %4  otherwise Tag will  be incorrectly generated for GCM Encryption:
    Workaround is implemented in polling mode, so if last block of payload <128bit don't use DMA mode otherwise
    TAG is incorrectly generated */

    /*DMA transfer must not include the last block in case of Size is not %16 */
    wordsize = wordsize - (wordsize % 4U);

    /*DMA transfer */
    CRYP_SetDMAConfig(hcryp, (uint32_t)(hcryp->pCrypInBuffPtr), (uint16_t)wordsize,
                      (uint32_t)(hcryp->pCrypOutBuffPtr));
  }
  else /* length of input data is < 16 */
  {
    /* Compute the number of padding bytes in last block of payload */
    npblb = 16U - (uint32_t)hcryp->Size;

#if !defined (CRYP_VER_2_2)
    if (hcryp->Version >= REV_ID_B)
#endif /*End of not defined CRYP_VER_2_2*/
    {
      /* Set Npblb in case of AES GCM payload encryption to get right tag*/
      if ((hcryp->Instance->CR & CRYP_CR_ALGODIR) == CRYP_OPERATINGMODE_ENCRYPT)
      {
        /* Specify the number of non-valid bytes using NPBLB register*/
        MODIFY_REG(hcryp->Instance->CR, CRYP_CR_NPBLB, npblb << 20);
      }
    }
    /* Enable CRYP to start the final phase */
    __HAL_CRYP_ENABLE(hcryp);

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
    for (index = 0; index < lastwordsize; index ++)
    {
      hcryp->Instance->DIN  = *(uint32_t *)(hcryp->pCrypInBuffPtr + hcryp->CrypInCount);
      hcryp->CrypInCount++;
    }

    /* Pad the data with zeros to have a complete block */
    while (index < 4U)
    {
      hcryp->Instance->DIN  = 0U;
      index++;
    }

    /* Wait for OFNE flag to be raised */
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
#if (USE_HAL_CRYP_REGISTER_CALLBACKS == 1)
        /*Call registered error callback*/
        hcryp->ErrorCallback(hcryp);
#else
        /*Call legacy weak error callback*/
        HAL_CRYP_ErrorCallback(hcryp);
#endif /* USE_HAL_CRYP_REGISTER_CALLBACKS */
      }
    }
    while (HAL_IS_BIT_CLR(hcryp->Instance->SR, CRYP_FLAG_OFNE));

    /*Read the output block from the output FIFO */
    for (index = 0U; index < 4U; index++)
    {
      /* Read the output block from the output FIFO and put them in temporary buffer
      then get CrypOutBuff from temporary buffer */
      temp[index] = hcryp->Instance->DOUT;
    }
    for (index = 0; index < lastwordsize; index++)
    {
      *(uint32_t *)(hcryp->pCrypOutBuffPtr + hcryp->CrypOutCount) = temp[index];
      hcryp->CrypOutCount++;
    }

    /* Change the CRYP state to ready */
    hcryp->State = HAL_CRYP_STATE_READY;

    /* Process unlocked */
    __HAL_UNLOCK(hcryp);
  }

  /* Return function status */
  return HAL_OK;
}


/**
  * @brief  AES CCM encryption/decryption processing in polling mode
  * @param  hcryp: pointer to a CRYP_HandleTypeDef structure that contains
  *         the configuration information for CRYP module
  * @param  Timeout: Timeout duration
  * @retval HAL status
  */
static HAL_StatusTypeDef CRYP_AESCCM_Process(CRYP_HandleTypeDef *hcryp, uint32_t Timeout)
{
  uint32_t tickstart;
  uint32_t wordsize = (uint32_t)(hcryp->Size) / 4U;
  uint32_t npblb ;
  uint32_t lastwordsize ;
  uint32_t temp[4] ;  /* Temporary CrypOutBuff */
  uint32_t index ;
  uint16_t outcount;  /* Temporary CrypOutCount Value */
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

    /* Set the initialization vector (IV) with CTR1 information */
    hcryp->Instance->IV0LR = (hcryp->Init.B0[0]) & CRYP_CCM_CTR1_0;
    hcryp->Instance->IV0RR = hcryp->Init.B0[1];
    hcryp->Instance->IV1LR = hcryp->Init.B0[2];
    hcryp->Instance->IV1RR = (hcryp->Init.B0[3] & CRYP_CCM_CTR1_1) |  CRYP_CCM_CTR1_2;

    /* Enable the CRYP peripheral */
    __HAL_CRYP_ENABLE(hcryp);

#if defined (CRYP_VER_2_2)
    {
      /* for STM32H7 rev.B and above Write  B0 packet into CRYP_DR*/
      hcryp->Instance->DIN = *(uint32_t *)(hcryp->Init.B0);
      hcryp->Instance->DIN = *(uint32_t *)(hcryp->Init.B0 + 1);
      hcryp->Instance->DIN = *(uint32_t *)(hcryp->Init.B0 + 2);
      hcryp->Instance->DIN = *(uint32_t *)(hcryp->Init.B0 + 3);
    }
#else
    if (hcryp->Version >= REV_ID_B)
    {
      /* for STM32H7 rev.B and above Write  B0 packet into CRYP_DR*/
      hcryp->Instance->DIN = *(uint32_t *)(hcryp->Init.B0);
      hcryp->Instance->DIN = *(uint32_t *)(hcryp->Init.B0 + 1);
      hcryp->Instance->DIN = *(uint32_t *)(hcryp->Init.B0 + 2);
      hcryp->Instance->DIN = *(uint32_t *)(hcryp->Init.B0 + 3);
    }
    else /* data has to be swapped according to the DATATYPE */
    {
      if (hcryp->Init.DataType == CRYP_BYTE_SWAP)
      {
        hcryp->Instance->DIN = __REV(*(uint32_t *)(hcryp->Init.B0));
        hcryp->Instance->DIN = __REV(*(uint32_t *)(hcryp->Init.B0 + 1));
        hcryp->Instance->DIN = __REV(*(uint32_t *)(hcryp->Init.B0 + 2));
        hcryp->Instance->DIN = __REV(*(uint32_t *)(hcryp->Init.B0 + 3));
      }
      else if (hcryp->Init.DataType == CRYP_HALFWORD_SWAP)
      {
        hcryp->Instance->DIN = __ROR(*(uint32_t *)(hcryp->Init.B0), 16);
        hcryp->Instance->DIN = __ROR(*(uint32_t *)(hcryp->Init.B0 + 1), 16);
        hcryp->Instance->DIN = __ROR(*(uint32_t *)(hcryp->Init.B0 + 2), 16);
        hcryp->Instance->DIN = __ROR(*(uint32_t *)(hcryp->Init.B0 + 3), 16);
      }
      else if (hcryp->Init.DataType == CRYP_BIT_SWAP)
      {
        hcryp->Instance->DIN = __RBIT(*(uint32_t *)(hcryp->Init.B0));
        hcryp->Instance->DIN = __RBIT(*(uint32_t *)(hcryp->Init.B0 + 1));
        hcryp->Instance->DIN = __RBIT(*(uint32_t *)(hcryp->Init.B0 + 2));
        hcryp->Instance->DIN = __RBIT(*(uint32_t *)(hcryp->Init.B0 + 3));
      }
      else
      {
        hcryp->Instance->DIN = *(uint32_t *)(hcryp->Init.B0);
        hcryp->Instance->DIN = *(uint32_t *)(hcryp->Init.B0 + 1);
        hcryp->Instance->DIN = *(uint32_t *)(hcryp->Init.B0 + 2);
        hcryp->Instance->DIN = *(uint32_t *)(hcryp->Init.B0 + 3);
      }
    }
#endif /* CRYP_VER_2_2 */
    /* Get tick */
    tickstart = HAL_GetTick();

    /*Wait for the CRYPEN bit to be cleared*/
    while ((hcryp->Instance->CR & CRYP_CR_CRYPEN) == CRYP_CR_CRYPEN)
    {
      /* Check for the Timeout */
      if (Timeout != HAL_MAX_DELAY)
      {
        if (((HAL_GetTick() - tickstart) > Timeout) || (Timeout == 0U))
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

    /************************* Header phase *************************************/
    /* Header block(B1) : associated data length expressed in bytes concatenated
    with Associated Data (A)*/

    if (CRYP_GCMCCM_SetHeaderPhase(hcryp, Timeout) != HAL_OK)
    {
      return HAL_ERROR;
    }
    /********************** Payload phase ***************************************/

    /* Set the phase */
    hcryp->Phase = CRYP_PHASE_PROCESS;

    /* Disable the CRYP peripheral */
    __HAL_CRYP_DISABLE(hcryp);
#if !defined (CRYP_VER_2_2)
    if (hcryp->Version >= REV_ID_B)
#endif /*End of not defined CRYP_VER_2_2*/
    {
      /* Set to 0 the number of non-valid bytes using NPBLB register*/
      MODIFY_REG(hcryp->Instance->CR, CRYP_CR_NPBLB, 0U);
    }

    /* Select payload phase once the header phase is performed */
    CRYP_SET_PHASE(hcryp, CRYP_PHASE_PAYLOAD);

    /* Enable the CRYP peripheral */
    __HAL_CRYP_ENABLE(hcryp);

  } /* if (DoKeyIVConfig == 1U) */

  if ((hcryp->Size % 16U) != 0U)
  {
    /* recalculate  wordsize */
    wordsize = ((wordsize / 4U) * 4U) ;
  }
  /* Get tick */
  tickstart = HAL_GetTick();

  /*Temporary CrypOutCount Value*/
  outcount = hcryp->CrypOutCount;

  /* Write input data and get output data */
  while ((hcryp->CrypInCount < wordsize) && (outcount < wordsize))
  {
    /* Write plain data and get cipher data */
    CRYP_AES_ProcessData(hcryp, Timeout);

    /*Temporary CrypOutCount Value*/
    outcount = hcryp->CrypOutCount;

    /* Check for the Timeout */
    if (Timeout != HAL_MAX_DELAY)
    {
      if (((HAL_GetTick() - tickstart) > Timeout) || (Timeout == 0U))
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
#if !defined (CRYP_VER_2_2)
    if (hcryp->Version >= REV_ID_B)
#endif /*End of not defined CRYP_VER_2_2*/
    {
      /* Compute the number of padding bytes in last block of payload */
      npblb = ((((uint32_t)(hcryp->Size) / 16U) + 1U) * 16U) - (uint32_t)(hcryp->Size);

      if ((hcryp->Instance->CR & CRYP_CR_ALGODIR) == CRYP_OPERATINGMODE_DECRYPT)
      {
        /* Disable the CRYP */
        __HAL_CRYP_DISABLE(hcryp);

        /* Set Npblb in case of AES CCM payload decryption to get right tag  */
        MODIFY_REG(hcryp->Instance->CR, CRYP_CR_NPBLB, npblb << 20);

        /* Enable CRYP to start the final phase */
        __HAL_CRYP_ENABLE(hcryp);
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
      for (index = 0U; index < lastwordsize; index ++)
      {
        hcryp->Instance->DIN  = *(uint32_t *)(hcryp->pCrypInBuffPtr + hcryp->CrypInCount);
        hcryp->CrypInCount++;
      }

      /* Pad the data with zeros to have a complete block */
      while (index < 4U)
      {
        hcryp->Instance->DIN  = 0U;
        index++;
      }

      /* Wait for OFNE flag to be raised */
      if (CRYP_WaitOnOFNEFlag(hcryp, Timeout) != HAL_OK)
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

      /*Read the output block from the output FIFO */
      if ((hcryp->Instance->SR & CRYP_FLAG_OFNE) != 0x0U)
      {
        for (index = 0U; index < 4U; index++)
        {
          /* Read the output block from the output FIFO and put them in temporary buffer
          then get CrypOutBuff from temporary buffer */
          temp[index] = hcryp->Instance->DOUT;
        }
        for (index = 0; index < lastwordsize; index++)
        {
          *(uint32_t *)(hcryp->pCrypOutBuffPtr + hcryp->CrypOutCount) = temp[index];
          hcryp->CrypOutCount++;
        }
      }
    }
#if !defined (CRYP_VER_2_2)
    else /* No NPBLB, Workaround to be used */
    {
      /* CRYP Workaround :  CRYP1 generates correct TAG  during CCM decryption only when ciphertext
      blocks size is multiple of 128 bits. If lthe size of the last block of payload is inferior to 128 bits,
      when CCM decryption is selected, then the TAG message will be wrong.*/
      CRYP_Workaround(hcryp, Timeout);
    }
#endif /*End of not defined CRYP_VER_2_2*/
  }

  /* Return function status */
  return HAL_OK;
}

/**
  * @brief  AES CCM encryption/decryption process in interrupt mode
  * @param  hcryp: pointer to a CRYP_HandleTypeDef structure that contains
  *         the configuration information for CRYP module
  * @retval HAL status
  */
static HAL_StatusTypeDef CRYP_AESCCM_Process_IT(CRYP_HandleTypeDef *hcryp)
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

    /************ Init phase ************/

    CRYP_SET_PHASE(hcryp, CRYP_PHASE_INIT);

    /* Set the key */
    CRYP_SetKey(hcryp, hcryp->Init.KeySize);

    /* Set the initialization vector (IV) with CTR1 information */
    hcryp->Instance->IV0LR = (hcryp->Init.B0[0]) & CRYP_CCM_CTR1_0;
    hcryp->Instance->IV0RR = hcryp->Init.B0[1];
    hcryp->Instance->IV1LR = hcryp->Init.B0[2];
    hcryp->Instance->IV1RR = (hcryp->Init.B0[3] & CRYP_CCM_CTR1_1) |  CRYP_CCM_CTR1_2;

    /* Enable the CRYP peripheral */
    __HAL_CRYP_ENABLE(hcryp);

    /*Write the B0 packet into CRYP_DR*/
#if !defined (CRYP_VER_2_2)
    if (hcryp->Version >= REV_ID_B)
#endif /*End of not defined CRYP_VER_2_2*/
    {
      /* for STM32H7 rev.B and above data has not to be swapped */
      hcryp->Instance->DIN = *(uint32_t *)(hcryp->Init.B0);
      hcryp->Instance->DIN = *(uint32_t *)(hcryp->Init.B0 + 1);
      hcryp->Instance->DIN = *(uint32_t *)(hcryp->Init.B0 + 2);
      hcryp->Instance->DIN = *(uint32_t *)(hcryp->Init.B0 + 3);
    }
#if !defined (CRYP_VER_2_2)
    else /* data has to be swapped according to the DATATYPE */
    {
      if (hcryp->Init.DataType == CRYP_BYTE_SWAP)
      {
        hcryp->Instance->DIN = __REV(*(uint32_t *)(hcryp->Init.B0));
        hcryp->Instance->DIN = __REV(*(uint32_t *)(hcryp->Init.B0 + 1));
        hcryp->Instance->DIN = __REV(*(uint32_t *)(hcryp->Init.B0 + 2));
        hcryp->Instance->DIN = __REV(*(uint32_t *)(hcryp->Init.B0 + 3));
      }
      else if (hcryp->Init.DataType == CRYP_HALFWORD_SWAP)
      {
        hcryp->Instance->DIN = __ROR(*(uint32_t *)(hcryp->Init.B0), 16);
        hcryp->Instance->DIN = __ROR(*(uint32_t *)(hcryp->Init.B0 + 1), 16);
        hcryp->Instance->DIN = __ROR(*(uint32_t *)(hcryp->Init.B0 + 2), 16);
        hcryp->Instance->DIN = __ROR(*(uint32_t *)(hcryp->Init.B0 + 3), 16);
      }
      else if (hcryp->Init.DataType == CRYP_BIT_SWAP)
      {
        hcryp->Instance->DIN = __RBIT(*(uint32_t *)(hcryp->Init.B0));
        hcryp->Instance->DIN = __RBIT(*(uint32_t *)(hcryp->Init.B0 + 1));
        hcryp->Instance->DIN = __RBIT(*(uint32_t *)(hcryp->Init.B0 + 2));
        hcryp->Instance->DIN = __RBIT(*(uint32_t *)(hcryp->Init.B0 + 3));
      }
      else
      {
        hcryp->Instance->DIN = *(uint32_t *)(hcryp->Init.B0);
        hcryp->Instance->DIN = *(uint32_t *)(hcryp->Init.B0 + 1);
        hcryp->Instance->DIN = *(uint32_t *)(hcryp->Init.B0 + 2);
        hcryp->Instance->DIN = *(uint32_t *)(hcryp->Init.B0 + 3);
      }
    }
#endif /*End of not defined CRYP_VER_2_2*/
    /*Wait for the CRYPEN bit to be cleared*/
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
    while ((hcryp->Instance->CR & CRYP_CR_CRYPEN) == CRYP_CR_CRYPEN);

    /* Select header phase */
    CRYP_SET_PHASE(hcryp, CRYP_PHASE_HEADER);
  } /* end of if (DoKeyIVConfig == 1U) */
  /* Enable interrupts */
  __HAL_CRYP_ENABLE_IT(hcryp, CRYP_IT_INI);

  /* Enable CRYP */
  __HAL_CRYP_ENABLE(hcryp);

  /* Return function status */
  return HAL_OK;
}
/**
  * @brief  AES CCM encryption/decryption process in DMA mode
  * @param  hcryp: pointer to a CRYP_HandleTypeDef structure that contains
  *         the configuration information for CRYP module
  * @retval HAL status
  */
static HAL_StatusTypeDef CRYP_AESCCM_Process_DMA(CRYP_HandleTypeDef *hcryp)
{
  __IO uint32_t count    = 0U;
  uint32_t wordsize = (uint32_t)(hcryp->Size) / 4U ;
  uint32_t index;
  uint32_t npblb;
  uint32_t lastwordsize;
  uint32_t temp[4];  /* Temporary CrypOutBuff */
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

    /************************** Init phase **************************************/

    CRYP_SET_PHASE(hcryp, CRYP_PHASE_INIT);

    /* Set the key */
    CRYP_SetKey(hcryp, hcryp->Init.KeySize);

    /* Set the initialization vector (IV) with CTR1 information */
    hcryp->Instance->IV0LR = (hcryp->Init.B0[0]) & CRYP_CCM_CTR1_0;
    hcryp->Instance->IV0RR = hcryp->Init.B0[1];
    hcryp->Instance->IV1LR = hcryp->Init.B0[2];
    hcryp->Instance->IV1RR = (hcryp->Init.B0[3] & CRYP_CCM_CTR1_1) |  CRYP_CCM_CTR1_2;

    /* Enable the CRYP peripheral */
    __HAL_CRYP_ENABLE(hcryp);

    /*Write the B0 packet into CRYP_DR*/
#if !defined (CRYP_VER_2_2)
    if (hcryp->Version >= REV_ID_B)
#endif /*End of not defined CRYP_VER_2_2*/
    {
      /* for STM32H7 rev.B and above data has not to be swapped */
      hcryp->Instance->DIN = *(uint32_t *)(hcryp->Init.B0);
      hcryp->Instance->DIN = *(uint32_t *)(hcryp->Init.B0 + 1);
      hcryp->Instance->DIN = *(uint32_t *)(hcryp->Init.B0 + 2);
      hcryp->Instance->DIN = *(uint32_t *)(hcryp->Init.B0 + 3);
    }
#if !defined (CRYP_VER_2_2)
    else /* data has to be swapped according to the DATATYPE */
    {
      if (hcryp->Init.DataType == CRYP_BYTE_SWAP)
      {
        hcryp->Instance->DIN = __REV(*(uint32_t *)(hcryp->Init.B0));
        hcryp->Instance->DIN = __REV(*(uint32_t *)(hcryp->Init.B0 + 1));
        hcryp->Instance->DIN = __REV(*(uint32_t *)(hcryp->Init.B0 + 2));
        hcryp->Instance->DIN = __REV(*(uint32_t *)(hcryp->Init.B0 + 3));
      }
      else if (hcryp->Init.DataType == CRYP_HALFWORD_SWAP)
      {
        hcryp->Instance->DIN = __ROR(*(uint32_t *)(hcryp->Init.B0), 16);
        hcryp->Instance->DIN = __ROR(*(uint32_t *)(hcryp->Init.B0 + 1), 16);
        hcryp->Instance->DIN = __ROR(*(uint32_t *)(hcryp->Init.B0 + 2), 16);
        hcryp->Instance->DIN = __ROR(*(uint32_t *)(hcryp->Init.B0 + 3), 16);
      }
      else if (hcryp->Init.DataType == CRYP_BIT_SWAP)
      {
        hcryp->Instance->DIN = __RBIT(*(uint32_t *)(hcryp->Init.B0));
        hcryp->Instance->DIN = __RBIT(*(uint32_t *)(hcryp->Init.B0 + 1));
        hcryp->Instance->DIN = __RBIT(*(uint32_t *)(hcryp->Init.B0 + 2));
        hcryp->Instance->DIN = __RBIT(*(uint32_t *)(hcryp->Init.B0 + 3));
      }
      else
      {
        hcryp->Instance->DIN = *(uint32_t *)(hcryp->Init.B0);
        hcryp->Instance->DIN = *(uint32_t *)(hcryp->Init.B0 + 1);
        hcryp->Instance->DIN = *(uint32_t *)(hcryp->Init.B0 + 2);
        hcryp->Instance->DIN = *(uint32_t *)(hcryp->Init.B0 + 3);
      }
    }
#endif /*End of not defined CRYP_VER_2_2*/
    /*Wait for the CRYPEN bit to be cleared*/
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
    while ((hcryp->Instance->CR & CRYP_CR_CRYPEN) == CRYP_CR_CRYPEN);

    /********************* Header phase *****************************************/

    if (CRYP_GCMCCM_SetHeaderPhase_DMA(hcryp) != HAL_OK)
    {
      return HAL_ERROR;
    }

    /******************** Payload phase *****************************************/

    /* Set the phase */
    hcryp->Phase = CRYP_PHASE_PROCESS;

    /* Disable the CRYP peripheral */
    __HAL_CRYP_DISABLE(hcryp);
#if !defined (CRYP_VER_2_2)
    if (hcryp->Version >= REV_ID_B)
#endif /*End of not defined CRYP_VER_2_2*/
    {
      /* Set to 0 the number of non-valid bytes using NPBLB register*/
      MODIFY_REG(hcryp->Instance->CR, CRYP_CR_NPBLB, 0U);
    }

    /* Select payload phase once the header phase is performed */
    CRYP_SET_PHASE(hcryp, CRYP_PHASE_PAYLOAD);
  } /* if (DoKeyIVConfig == 1U) */

  if (hcryp->Size == 0U)
  {
    /* Process unLocked */
    __HAL_UNLOCK(hcryp);

    /* Change the CRYP state and phase */
    hcryp->State = HAL_CRYP_STATE_READY;
  }
  else if (hcryp->Size >= 16U)
  {
    /* for STM32H7 below rev.B ::  Size should be %4  otherwise Tag will  be incorrectly generated for CCM Decryption,
    Workaround is implemented in polling mode*/
    /*DMA transfer must not include the last block in case of Size is not %16 */
    wordsize = wordsize - (wordsize % 4U);

    /*DMA transfer */
    CRYP_SetDMAConfig(hcryp, (uint32_t)(hcryp->pCrypInBuffPtr), (uint16_t) wordsize,
                      (uint32_t)(hcryp->pCrypOutBuffPtr));
  }
  else /* length of input data is  < 16U */
  {
    /* Compute the number of padding bytes in last block of payload */
    npblb = 16U - (uint32_t)(hcryp->Size);

#if !defined (CRYP_VER_2_2)
    if (hcryp->Version >= REV_ID_B)
#endif /*End of not defined CRYP_VER_2_2*/
    {
      /* Set Npblb in case of AES CCM payload decryption to get right tag*/
      if ((hcryp->Instance->CR & CRYP_CR_ALGODIR) == CRYP_OPERATINGMODE_DECRYPT)
      {
        /* Specify the number of non-valid bytes using NPBLB register*/
        MODIFY_REG(hcryp->Instance->CR, CRYP_CR_NPBLB, npblb << 20);
      }
    }
    /* Enable CRYP to start the final phase */
    __HAL_CRYP_ENABLE(hcryp);

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
    for (index = 0U; index < lastwordsize; index ++)
    {
      hcryp->Instance->DIN  = *(uint32_t *)(hcryp->pCrypInBuffPtr + hcryp->CrypInCount);
      hcryp->CrypInCount++;
    }

    /* Pad the data with zeros to have a complete block */
    while (index < 4U)
    {
      hcryp->Instance->DIN  = 0U;
      index++;
    }

    /* Wait for OFNE flag to be raised */
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
#if (USE_HAL_CRYP_REGISTER_CALLBACKS == 1)
        /*Call registered error callback*/
        hcryp->ErrorCallback(hcryp);
#else
        /*Call legacy weak error callback*/
        HAL_CRYP_ErrorCallback(hcryp);
#endif /* USE_HAL_CRYP_REGISTER_CALLBACKS */
      }
    }
    while (HAL_IS_BIT_CLR(hcryp->Instance->SR, CRYP_FLAG_OFNE));

    /*Read the output block from the output FIFO */
    for (index = 0U; index < 4U; index++)
    {
      /* Read the output block from the output FIFO and put them in temporary buffer
      then get CrypOutBuff from temporary buffer */
      temp[index] = hcryp->Instance->DOUT;
    }
    for (index = 0; index < lastwordsize; index++)
    {
      *(uint32_t *)(hcryp->pCrypOutBuffPtr + hcryp->CrypOutCount) = temp[index];
      hcryp->CrypOutCount++;
    }

    /* Change the CRYP state to ready */
    hcryp->State = HAL_CRYP_STATE_READY;

    /* Process unlocked */
    __HAL_UNLOCK(hcryp);
  }

  /* Return function status */
  return HAL_OK;
}

/**
  * @brief  Sets the payload phase in interrupt mode
  * @param  hcryp: pointer to a CRYP_HandleTypeDef structure that contains
  *         the configuration information for CRYP module
  * @retval state
  */
static void CRYP_GCMCCM_SetPayloadPhase_IT(CRYP_HandleTypeDef *hcryp)
{
  uint32_t loopcounter;
  uint32_t temp[4];  /* Temporary CrypOutBuff */
  uint32_t lastwordsize;
  uint32_t npblb;
  uint32_t temp_cr_algodir;
  uint8_t negative = 0U;
  uint32_t i;

  /***************************** Payload phase *******************************/

  if ((hcryp->Size / 4U) < hcryp->CrypInCount)
  {
    negative = 1U;
  }

  if (hcryp->Size == 0U)
  {
    /* Disable interrupts */
    __HAL_CRYP_DISABLE_IT(hcryp, CRYP_IT_INI | CRYP_IT_OUTI);

    /* Process unlocked */
    __HAL_UNLOCK(hcryp);

    /* Change the CRYP state */
    hcryp->State = HAL_CRYP_STATE_READY;
  }

  else if ((((hcryp->Size / 4U) - (hcryp->CrypInCount)) >= 4U) &&
           (negative == 0U))
  {
    if ((hcryp->Instance->IMSCR & CRYP_IMSCR_INIM) != 0x0U)
    {
      /* Write the input block in the IN FIFO */
      hcryp->Instance->DIN  = *(uint32_t *)(hcryp->pCrypInBuffPtr + hcryp->CrypInCount);
      hcryp->CrypInCount++;
      hcryp->Instance->DIN  = *(uint32_t *)(hcryp->pCrypInBuffPtr + hcryp->CrypInCount);
      hcryp->CrypInCount++;
      hcryp->Instance->DIN  = *(uint32_t *)(hcryp->pCrypInBuffPtr + hcryp->CrypInCount);
      hcryp->CrypInCount++;
      hcryp->Instance->DIN  = *(uint32_t *)(hcryp->pCrypInBuffPtr + hcryp->CrypInCount);
      hcryp->CrypInCount++;
      if (((hcryp->Size / 4U) == hcryp->CrypInCount) && ((hcryp->Size % 16U) == 0U))
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

      if (hcryp->CrypOutCount < (hcryp->Size / 4U))
      {
        if ((hcryp->Instance->SR & CRYP_FLAG_OFNE) != 0x0U)
        {
          /* Read the output block from the Output FIFO and put them in temporary buffer
          then get CrypOutBuff from temporary buffer  */
          for (i = 0U; i < 4U; i++)
          {
            temp[i] = hcryp->Instance->DOUT;
          }
          i = 0U;
          while (((hcryp->CrypOutCount < ((hcryp->Size) / 4U))) && (i < 4U))
          {
            *(uint32_t *)(hcryp->pCrypOutBuffPtr + hcryp->CrypOutCount) = temp[i];
            hcryp->CrypOutCount++;
            i++;
          }
          if (((hcryp->Size / 4U) == hcryp->CrypOutCount) && ((hcryp->Size % 16U) == 0U))
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
#if (USE_HAL_CRYP_REGISTER_CALLBACKS == 1U)
            /*Call registered Output complete callback*/
            hcryp->OutCpltCallback(hcryp);
#else
            /*Call legacy weak Output complete callback*/
            HAL_CRYP_OutCpltCallback(hcryp);
#endif /* USE_HAL_CRYP_REGISTER_CALLBACKS */
          }
        }
      }
    }
  }
  else if ((hcryp->Size % 16U) != 0U)
  {
    /* Set padding only in case of input fifo interrupt */
    if ((hcryp->Instance->IMSCR & CRYP_IMSCR_INIM) != 0x0U)
    {
      /* Compute the number of padding bytes in last block of payload */
      npblb = ((((uint32_t)hcryp->Size / 16U) + 1U) * 16U) - (uint32_t)(hcryp->Size);

#if !defined (CRYP_VER_2_2)
      if (hcryp->Version >= REV_ID_B)
#endif /*End of not defined CRYP_VER_2_2*/
      {
        /* Set Npblb in case of AES GCM payload encryption and CCM decryption to get right tag */
        temp_cr_algodir = hcryp->Instance->CR & CRYP_CR_ALGODIR;

        if (((temp_cr_algodir == CRYP_OPERATINGMODE_ENCRYPT) && (hcryp->Init.Algorithm == CRYP_AES_GCM)) ||
            ((temp_cr_algodir == CRYP_OPERATINGMODE_DECRYPT) && (hcryp->Init.Algorithm == CRYP_AES_CCM)))
        {
          /* Disable the CRYP */
          __HAL_CRYP_DISABLE(hcryp);

          /* Specify the number of non-valid bytes using NPBLB register*/
          MODIFY_REG(hcryp->Instance->CR, CRYP_CR_NPBLB, npblb << 20);

          /* Enable CRYP to start the final phase */
          __HAL_CRYP_ENABLE(hcryp);
        }
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
      for (loopcounter = 0U; loopcounter < lastwordsize; loopcounter++)
      {
        hcryp->Instance->DIN  = *(uint32_t *)(hcryp->pCrypInBuffPtr + hcryp->CrypInCount);
        hcryp->CrypInCount++;
      }
      /* Pad the data with zeros to have a complete block */
      while (loopcounter < 4U)
      {
        hcryp->Instance->DIN  = 0U;
        loopcounter++;
      }

      /* Disable the input FIFO Interrupt */
      __HAL_CRYP_DISABLE_IT(hcryp, CRYP_IT_INI);
    }

    /*Read the output block from the output FIFO */
    if ((hcryp->Instance->SR & CRYP_FLAG_OFNE) != 0x0U)
    {
      for (i = 0U; i < 4U; i++)
      {
        temp[i] = hcryp->Instance->DOUT;
      }
      if (((hcryp->Size) / 4U) == 0U)
      {
        for (i = 0U; (uint16_t)i < ((hcryp->Size) % 4U); i++)
        {
          *(uint32_t *)(hcryp->pCrypOutBuffPtr + hcryp->CrypOutCount) = temp[i];
          hcryp->CrypOutCount++;
        }
      }
      i = 0U;
      while (((hcryp->CrypOutCount < ((hcryp->Size) / 4U))) && (i < 4U))
      {
        *(uint32_t *)(hcryp->pCrypOutBuffPtr + hcryp->CrypOutCount) = temp[i];
        hcryp->CrypOutCount++;
        i++;
      }
    }

    /* Disable the output FIFO Interrupt */
    if (hcryp->CrypOutCount >= ((hcryp->Size) / 4U))
    {
      /* Disable interrupts */
      __HAL_CRYP_DISABLE_IT(hcryp, CRYP_IT_OUTI | CRYP_IT_INI);

      /* Change the CRYP peripheral state */
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
  }
  else
  {
    /* Nothing to do */
  }
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
  uint32_t size_in_bytes;
  uint32_t tmp;
  uint32_t mask[4] = {0x0U, 0x0FFU, 0x0FFFFU, 0x0FFFFFFU};

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
        hcryp->Instance->DIN = *(uint32_t *)(hcryp->Init.Header + hcryp->CrypHeaderCount);
        hcryp->CrypHeaderCount++ ;
        hcryp->Instance->DIN = *(uint32_t *)(hcryp->Init.Header + hcryp->CrypHeaderCount);
        hcryp->CrypHeaderCount++ ;
        hcryp->Instance->DIN = *(uint32_t *)(hcryp->Init.Header + hcryp->CrypHeaderCount);
        hcryp->CrypHeaderCount++ ;
        hcryp->Instance->DIN = *(uint32_t *)(hcryp->Init.Header + hcryp->CrypHeaderCount);
        hcryp->CrypHeaderCount++ ;

        /* Wait for IFEM to be raised */
        if (CRYP_WaitOnIFEMFlag(hcryp, Timeout) != HAL_OK)
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
      /* Write header block in the IN FIFO without last block */
      for (loopcounter = 0U; (loopcounter < ((size_in_bytes / 16U) * 4U)); loopcounter += 4U)
      {
        hcryp->Instance->DIN = *(uint32_t *)(hcryp->Init.Header + hcryp->CrypHeaderCount);
        hcryp->CrypHeaderCount++ ;
        hcryp->Instance->DIN = *(uint32_t *)(hcryp->Init.Header + hcryp->CrypHeaderCount);
        hcryp->CrypHeaderCount++ ;
        hcryp->Instance->DIN = *(uint32_t *)(hcryp->Init.Header + hcryp->CrypHeaderCount);
        hcryp->CrypHeaderCount++ ;
        hcryp->Instance->DIN = *(uint32_t *)(hcryp->Init.Header + hcryp->CrypHeaderCount);
        hcryp->CrypHeaderCount++ ;

        /* Wait for IFEM to be raised */
        if (CRYP_WaitOnIFEMFlag(hcryp, Timeout) != HAL_OK)
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
      for (loopcounter = 0U; (loopcounter < ((size_in_bytes / 4U) % 4U)); loopcounter++)
      {
        hcryp->Instance->DIN = *(uint32_t *)(hcryp->Init.Header + hcryp->CrypHeaderCount);
        hcryp->CrypHeaderCount++ ;
      }
      /* If the header size is a multiple of words */
      if ((size_in_bytes % 4U) == 0U)
      {
        /* Pad the data with zeros to have a complete block */
        while (loopcounter < 4U)
        {
          hcryp->Instance->DIN = 0x0U;
          loopcounter++;
        }
      }
      else
      {
        /* Enter last bytes, padded with zeroes */
        tmp =  *(uint32_t *)(hcryp->Init.Header + hcryp->CrypHeaderCount);
        tmp &= mask[size_in_bytes % 4U];
        hcryp->Instance->DIN = tmp;
        loopcounter++;
        /* Pad the data with zeros to have a complete block */
        while (loopcounter < 4U)
        {
          hcryp->Instance->DIN = 0x0U;
          loopcounter++;
        }
      }
      /* Wait for CCF IFEM to be raised */
      if (CRYP_WaitOnIFEMFlag(hcryp, Timeout) != HAL_OK)
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
    if (CRYP_WaitOnBUSYFlag(hcryp, Timeout) != HAL_OK)
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
  if ((hcryp->Init.HeaderSize != 0U))
  {
    /* Select header phase */
    CRYP_SET_PHASE(hcryp, CRYP_PHASE_HEADER);

    /* Enable the CRYP peripheral */
    __HAL_CRYP_ENABLE(hcryp);

    if ((hcryp->Init.HeaderSize % 4U) == 0U)
    {
      /* HeaderSize %4, no padding */
      for (loopcounter = 0U; (loopcounter < hcryp->Init.HeaderSize); loopcounter += 4U)
      {
        hcryp->Instance->DIN = *(uint32_t *)(hcryp->Init.Header + hcryp->CrypHeaderCount);
        hcryp->CrypHeaderCount++ ;
        hcryp->Instance->DIN = *(uint32_t *)(hcryp->Init.Header + hcryp->CrypHeaderCount);
        hcryp->CrypHeaderCount++ ;
        hcryp->Instance->DIN = *(uint32_t *)(hcryp->Init.Header + hcryp->CrypHeaderCount);
        hcryp->CrypHeaderCount++ ;
        hcryp->Instance->DIN = *(uint32_t *)(hcryp->Init.Header + hcryp->CrypHeaderCount);
        hcryp->CrypHeaderCount++ ;

        /* Wait for IFEM to be raised */
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
        while (HAL_IS_BIT_CLR(hcryp->Instance->SR, CRYP_FLAG_IFEM));
      }
    }
    else
    {
      /*Write header block in the IN FIFO without last block */
      for (loopcounter = 0U; (loopcounter < ((hcryp->Init.HeaderSize) - (hcryp->Init.HeaderSize % 4U)));
           loopcounter += 4U)
      {
        hcryp->Instance->DIN = *(uint32_t *)(hcryp->Init.Header + hcryp->CrypHeaderCount);
        hcryp->CrypHeaderCount++ ;
        hcryp->Instance->DIN = *(uint32_t *)(hcryp->Init.Header + hcryp->CrypHeaderCount);
        hcryp->CrypHeaderCount++ ;
        hcryp->Instance->DIN = *(uint32_t *)(hcryp->Init.Header + hcryp->CrypHeaderCount);
        hcryp->CrypHeaderCount++ ;
        hcryp->Instance->DIN = *(uint32_t *)(hcryp->Init.Header + hcryp->CrypHeaderCount);
        hcryp->CrypHeaderCount++ ;

        /* Wait for IFEM to be raised */
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
        while (HAL_IS_BIT_CLR(hcryp->Instance->SR, CRYP_FLAG_IFEM));
      }
      /*  Last block optionally pad the data with zeros*/
      for (loopcounter = 0U; (loopcounter < (hcryp->Init.HeaderSize % 4U)); loopcounter++)
      {
        hcryp->Instance->DIN = *(uint32_t *)(hcryp->Init.Header + hcryp->CrypHeaderCount);
        hcryp->CrypHeaderCount++ ;
      }
      while (loopcounter < 4U)
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
      while (HAL_IS_BIT_CLR(hcryp->Instance->SR, CRYP_FLAG_IFEM));
    }
    /* Wait until the complete message has been processed */
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
    while (HAL_IS_BIT_SET(hcryp->Instance->SR, CRYP_FLAG_BUSY));
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

  /***************************** Header phase *********************************/

  if (hcryp->Init.HeaderSize ==  hcryp->CrypHeaderCount)
  {
    /* Disable interrupts */
    __HAL_CRYP_DISABLE_IT(hcryp, CRYP_IT_INI);

    /* Disable the CRYP peripheral */
    __HAL_CRYP_DISABLE(hcryp);

#if !defined (CRYP_VER_2_2)
    if (hcryp->Version >= REV_ID_B)
#endif /*End of not defined CRYP_VER_2_2*/
    {
      /* Set to 0 the number of non-valid bytes using NPBLB register*/
      MODIFY_REG(hcryp->Instance->CR, CRYP_CR_NPBLB, 0U);
    }

    /* Set the phase */
    hcryp->Phase = CRYP_PHASE_PROCESS;

    /* Select payload phase once the header phase is performed */
    CRYP_SET_PHASE(hcryp, CRYP_PHASE_PAYLOAD);

    /* Enable Interrupts */
    __HAL_CRYP_ENABLE_IT(hcryp, CRYP_IT_INI | CRYP_IT_OUTI);

    /* Enable the CRYP peripheral */
    __HAL_CRYP_ENABLE(hcryp);
  }
  else if (((hcryp->Init.HeaderSize) - (hcryp->CrypHeaderCount)) >= 4U)

  {
    /* HeaderSize %4, no padding */
    hcryp->Instance->DIN = *(uint32_t *)(hcryp->Init.Header + hcryp->CrypHeaderCount);
    hcryp->CrypHeaderCount++ ;
    hcryp->Instance->DIN = *(uint32_t *)(hcryp->Init.Header + hcryp->CrypHeaderCount);
    hcryp->CrypHeaderCount++  ;
    hcryp->Instance->DIN = *(uint32_t *)(hcryp->Init.Header + hcryp->CrypHeaderCount);
    hcryp->CrypHeaderCount++ ;
    hcryp->Instance->DIN = *(uint32_t *)(hcryp->Init.Header + hcryp->CrypHeaderCount);
    hcryp->CrypHeaderCount++ ;
  }
  else
  {
    /*  Last block optionally pad the data with zeros*/
    for (loopcounter = 0U; loopcounter < (hcryp->Init.HeaderSize % 4U); loopcounter++)
    {
      hcryp->Instance->DIN = *(uint32_t *)(hcryp->Init.Header + hcryp->CrypHeaderCount);
      hcryp->CrypHeaderCount++ ;
    }
    while (loopcounter < 4U)
    {
      /* Pad the data with zeros to have a complete block */
      hcryp->Instance->DIN = 0x0U;
      loopcounter++;
    }
  }
}

#if !defined (CRYP_VER_2_2)
/**
  * @brief  Workaround used for GCM/CCM mode.
  * @param  hcryp: pointer to a CRYP_HandleTypeDef structure that contains
  *         the configuration information for CRYP module
  * @param  Timeout: Timeout value
  * @retval None
  */
static void CRYP_Workaround(CRYP_HandleTypeDef *hcryp, uint32_t Timeout)
{
  uint32_t  iv1temp;
  uint32_t  temp[4] = {0};
  uint32_t  temp2[4] = {0};
  uint32_t intermediate_data[4] = {0};
  uint32_t index;
  uint32_t lastwordsize;
  uint32_t npblb;

  /* Compute the number of padding bytes in last block of payload */
  npblb = ((((uint32_t)(hcryp->Size) / 16U) + 1U) * 16U) - (uint32_t)(hcryp->Size);

  /* Number of valid words (lastwordsize) in last block */
  if ((npblb % 4U) == 0U)
  {
    lastwordsize = (16U - npblb) / 4U;
  }
  else
  {
    lastwordsize = ((16U - npblb) / 4U) + 1U;
  }

  /* Workaround 2, case GCM encryption */
  if (hcryp->Init.Algorithm == CRYP_AES_GCM)
  {
    if ((hcryp->Instance->CR & CRYP_CR_ALGODIR) == CRYP_OPERATINGMODE_ENCRYPT)
    {
      /*Workaround in order to properly compute authentication tags while doing
       a GCM encryption with the last block of payload size inferior to 128 bits*/
      /* Disable CRYP to start the final phase */
      __HAL_CRYP_DISABLE(hcryp);

      /*Update CRYP_IV1R register and ALGOMODE*/
      hcryp->Instance->IV1RR = ((hcryp->Instance->CSGCMCCM7R) - 1U);
      MODIFY_REG(hcryp->Instance->CR, CRYP_CR_ALGOMODE, CRYP_AES_CTR);

      /* Enable CRYP to start the final phase */
      __HAL_CRYP_ENABLE(hcryp);
    }

    for (index = 0; index < lastwordsize ; index ++)
    {
      /* Write the last input block in the IN FIFO */
      hcryp->Instance->DIN  = *(uint32_t *)(hcryp->pCrypInBuffPtr + hcryp->CrypInCount);
      hcryp->CrypInCount++;
    }
    while (index < 4U)
    {
      /* Pad the data with zeros to have a complete block */
      hcryp->Instance->DIN  = 0U;
      index++;
    }
    /* Wait for OFNE flag to be raised */
    if (CRYP_WaitOnOFNEFlag(hcryp, Timeout) != HAL_OK)
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
    if ((hcryp->Instance->SR & CRYP_FLAG_OFNE) != 0x0U)
    {
      for (index = 0U; index < 4U; index++)
      {
        /* Read the output block from the output FIFO */
        intermediate_data[index] = hcryp->Instance->DOUT;

        /* Intermediate data buffer to be used in for the workaround*/
        *(uint32_t *)(hcryp->pCrypOutBuffPtr + (hcryp->CrypOutCount)) = intermediate_data[index];
        hcryp->CrypOutCount++;
      }
    }

    if ((hcryp->Instance->CR & CRYP_CR_ALGODIR) == CRYP_OPERATINGMODE_ENCRYPT)
    {
      /*workaround in order to properly compute authentication tags while doing
      a GCM encryption with the last block of payload size inferior to 128 bits*/
      /* Change the AES mode to GCM mode and Select Final phase */
      /* configured  CHMOD GCM   */
      MODIFY_REG(hcryp->Instance->CR, CRYP_CR_ALGOMODE, CRYP_AES_GCM);

      /* configured  final phase  */
      MODIFY_REG(hcryp->Instance->CR, CRYP_CR_GCM_CCMPH, CRYP_PHASE_FINAL);

      if ((hcryp->Instance->CR & CRYP_CR_DATATYPE) == CRYP_NO_SWAP)
      {
        if ((npblb % 4U) == 1U)
        {
          intermediate_data[lastwordsize - 1U] &= 0xFFFFFF00U;
        }
        if ((npblb % 4U) == 2U)
        {
          intermediate_data[lastwordsize - 1U] &= 0xFFFF0000U;
        }
        if ((npblb % 4U) == 3U)
        {
          intermediate_data[lastwordsize - 1U] &= 0xFF000000U;
        }
      }
      else if ((hcryp->Instance->CR & CRYP_CR_DATATYPE) == CRYP_BYTE_SWAP)
      {
        if ((npblb % 4U) == 1U)
        {
          intermediate_data[lastwordsize - 1U] &= __REV(0xFFFFFF00U);
        }
        if ((npblb % 4U) == 2U)
        {
          intermediate_data[lastwordsize - 1U] &= __REV(0xFFFF0000U);
        }
        if ((npblb % 4U) == 3U)
        {
          intermediate_data[lastwordsize - 1U] &= __REV(0xFF000000U);
        }
      }
      else if ((hcryp->Instance->CR & CRYP_CR_DATATYPE) == CRYP_HALFWORD_SWAP)
      {
        if ((npblb % 4U) == 1U)
        {
          intermediate_data[lastwordsize - 1U] &= __ROR((0xFFFFFF00U), 16);
        }
        if ((npblb % 4U) == 2U)
        {
          intermediate_data[lastwordsize - 1U] &= __ROR((0xFFFF0000U), 16);
        }
        if ((npblb % 4U) == 3U)
        {
          intermediate_data[lastwordsize - 1U] &= __ROR((0xFF000000U), 16);
        }
      }
      else /*CRYP_BIT_SWAP*/
      {
        if ((npblb % 4U) == 1U)
        {
          intermediate_data[lastwordsize - 1U] &= __RBIT(0xFFFFFF00U);
        }
        if ((npblb % 4U) == 2U)
        {
          intermediate_data[lastwordsize - 1U] &= __RBIT(0xFFFF0000U);
        }
        if ((npblb % 4U) == 3U)
        {
          intermediate_data[lastwordsize - 1U] &= __RBIT(0xFF000000U);
        }
      }

      for (index = 0U; index < lastwordsize ; index ++)
      {
        /*Write the intermediate_data in the IN FIFO */
        hcryp->Instance->DIN = intermediate_data[index];
      }
      while (index < 4U)
      {
        /* Pad the data with zeros to have a complete block */
        hcryp->Instance->DIN  = 0x0U;
        index++;
      }
      /* Wait for OFNE flag to be raised */
      if (CRYP_WaitOnOFNEFlag(hcryp, Timeout) != HAL_OK)
      {
        /* Disable the CRYP peripheral clock */
        __HAL_CRYP_DISABLE(hcryp);

        /* Change state */
        hcryp->ErrorCode |= HAL_CRYP_ERROR_TIMEOUT;
        hcryp->State = HAL_CRYP_STATE_READY;

        /* Process unlocked */
        __HAL_UNLOCK(hcryp);
#if (USE_HAL_CRYP_REGISTER_CALLBACKS == 1U)
        /*Call registered error callback*/
        hcryp->ErrorCallback(hcryp);
#else
        /*Call legacy weak error callback*/
        HAL_CRYP_ErrorCallback(hcryp);
#endif /* USE_HAL_CRYP_REGISTER_CALLBACKS */
      }

      if ((hcryp->Instance->SR & CRYP_FLAG_OFNE) != 0x0U)
      {
        for (index = 0U; index < 4U; index++)
        {
          intermediate_data[index] = hcryp->Instance->DOUT;
        }
      }
    }
  } /* End of GCM encryption */
  else
  {
    /* Workaround 2, case CCM decryption, in order to properly compute
      authentication tags while doing a CCM decryption with the last block
      of payload size inferior to 128 bits*/

    if ((hcryp->Instance->CR & CRYP_CR_ALGODIR) == CRYP_OPERATINGMODE_DECRYPT)
    {
      iv1temp = hcryp->Instance->CSGCMCCM7R;

      /* Disable CRYP to start the final phase */
      __HAL_CRYP_DISABLE(hcryp);

      temp[0] =  hcryp->Instance->CSGCMCCM0R;
      temp[1] =  hcryp->Instance->CSGCMCCM1R;
      temp[2] =  hcryp->Instance->CSGCMCCM2R;
      temp[3] =  hcryp->Instance->CSGCMCCM3R;

      hcryp->Instance->IV1RR = iv1temp;

      /* Configured  CHMOD CTR   */
      MODIFY_REG(hcryp->Instance->CR, CRYP_CR_ALGOMODE, CRYP_AES_CTR);

      /* Enable CRYP to start the final phase */
      __HAL_CRYP_ENABLE(hcryp);
    }
    /*  Last block optionally pad the data with zeros*/
    for (index = 0U; index < lastwordsize; index ++)
    {
      /* Write the last Input block in the IN FIFO */
      hcryp->Instance->DIN  = *(uint32_t *)(hcryp->pCrypInBuffPtr + hcryp->CrypInCount);
      hcryp->CrypInCount++;
    }
    while (index < 4U)
    {
      /* Pad the data with zeros to have a complete block */
      hcryp->Instance->DIN  = 0U;
      index++;
    }
    /* Wait for OFNE flag to be raised */
    if (CRYP_WaitOnOFNEFlag(hcryp, Timeout) != HAL_OK)
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

    if ((hcryp->Instance->SR & CRYP_FLAG_OFNE) != 0x0U)
    {
      for (index = 0U; index < 4U; index++)
      {
        /* Read the Output block from the Output FIFO */
        intermediate_data[index] = hcryp->Instance->DOUT;

        /*intermediate data buffer to be used in for the workaround*/
        *(uint32_t *)(hcryp->pCrypOutBuffPtr + (hcryp->CrypOutCount)) = intermediate_data[index];
        hcryp->CrypOutCount++;
      }
    }

    if ((hcryp->Instance->CR & CRYP_CR_ALGODIR) == CRYP_OPERATINGMODE_DECRYPT)
    {
      temp2[0] =  hcryp->Instance->CSGCMCCM0R;
      temp2[1] =  hcryp->Instance->CSGCMCCM1R;
      temp2[2] =  hcryp->Instance->CSGCMCCM2R;
      temp2[3] =  hcryp->Instance->CSGCMCCM3R;

      /* configured  CHMOD CCM   */
      MODIFY_REG(hcryp->Instance->CR, CRYP_CR_ALGOMODE, CRYP_AES_CCM);

      /* configured  Header phase  */
      MODIFY_REG(hcryp->Instance->CR, CRYP_CR_GCM_CCMPH, CRYP_PHASE_HEADER);

      /*set to zero the bits corresponding to the padded bits*/
      for (index = lastwordsize; index < 4U; index ++)
      {
        intermediate_data[index] = 0U;
      }

      if ((npblb % 4U) == 1U)
      {
        intermediate_data[lastwordsize - 1U] &= 0xFFFFFF00U;
      }
      if ((npblb % 4U) == 2U)
      {
        intermediate_data[lastwordsize - 1U] &= 0xFFFF0000U;
      }
      if ((npblb % 4U) == 3U)
      {
        intermediate_data[lastwordsize - 1U] &= 0xFF000000U;
      }

      for (index = 0U; index < 4U ; index ++)
      {
        intermediate_data[index] ^=  temp[index];
        intermediate_data[index] ^=  temp2[index];
      }
      for (index = 0U; index < 4U; index ++)
      {
        /* Write the last Input block in the IN FIFO */
        hcryp->Instance->DIN  = intermediate_data[index] ;
      }

      /* Wait for BUSY flag to be raised */
      if (CRYP_WaitOnBUSYFlag(hcryp, Timeout) != HAL_OK)
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
    }
  } /* End of CCM WKA*/

  /* Process Unlocked */
  __HAL_UNLOCK(hcryp);
}
#endif /*End of not defined CRYP_VER_2_2*/

/**
  * @brief  Handle CRYP hardware block Timeout when waiting for IFEM flag to be raised.
  * @param  hcryp: pointer to a CRYP_HandleTypeDef structure that contains
  *         the configuration information for CRYP module.
  * @param  Timeout: Timeout duration.
  * @retval HAL status
  */
static HAL_StatusTypeDef CRYP_WaitOnIFEMFlag(const CRYP_HandleTypeDef *hcryp, uint32_t Timeout)
{
  uint32_t tickstart;

  /* Get timeout */
  tickstart = HAL_GetTick();

  while (HAL_IS_BIT_CLR(hcryp->Instance->SR, CRYP_FLAG_IFEM))
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
  * @brief  Handle CRYP hardware block Timeout when waiting for BUSY flag to be raised.
  * @param  hcryp: pointer to a CRYP_HandleTypeDef structure that contains
  *         the configuration information for CRYP module.
  * @param  Timeout: Timeout duration.
  * @retval HAL status
  */
static HAL_StatusTypeDef CRYP_WaitOnBUSYFlag(const CRYP_HandleTypeDef *hcryp, uint32_t Timeout)
{
  uint32_t tickstart;

  /* Get timeout */
  tickstart = HAL_GetTick();

  while (HAL_IS_BIT_SET(hcryp->Instance->SR, CRYP_FLAG_BUSY))
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
  * @brief  Handle CRYP hardware block Timeout when waiting for OFNE flag to be raised.
  * @param  hcryp: pointer to a CRYP_HandleTypeDef structure that contains
  *         the configuration information for CRYP module.
  * @param  Timeout: Timeout duration.
  * @retval HAL status
  */
static HAL_StatusTypeDef CRYP_WaitOnOFNEFlag(const CRYP_HandleTypeDef  *hcryp, uint32_t Timeout)
{
  uint32_t tickstart;

  /* Get timeout */
  tickstart = HAL_GetTick();

  while (HAL_IS_BIT_CLR(hcryp->Instance->SR, CRYP_FLAG_OFNE))
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
  * @}
  */



/**
  * @}
  */

#endif /* HAL_CRYP_MODULE_ENABLED */


/**
  * @}
  */
#endif /* CRYP */
/**
  * @}
  */

