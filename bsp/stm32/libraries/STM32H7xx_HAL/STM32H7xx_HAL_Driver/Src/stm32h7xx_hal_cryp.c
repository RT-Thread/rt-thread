/**
  ******************************************************************************
  * @file    stm32h7xx_hal_cryp.c
  * @author  MCD Application Team
  * @version V1.2.0
  * @date   29-December-2017
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
#define CRYP_TIMEOUT_KEYPREPARATION      82U         /*The latency of key preparation operation is 82 clock cycles.*/
#define CRYP_TIMEOUT_GCMCCMINITPHASE     299U        /*  The latency of  GCM/CCM init phase to prepare hash subkey is 299 clock cycles.*/
#define CRYP_TIMEOUT_GCMCCMHEADERPHASE   290U        /*  The latency of  GCM/CCM header phase is 290 clock cycles.*/

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
/** @addtogroup CRYP_Private_Functions_prototypes
  * @{
  */  

static void CRYP_SetDMAConfig(CRYP_HandleTypeDef *hcryp, uint32_t inputaddr, uint16_t Size, uint32_t outputaddr);
static void CRYP_DMAInCplt(DMA_HandleTypeDef *hdma);
static void CRYP_DMAOutCplt(DMA_HandleTypeDef *hdma);
static void CRYP_DMAError(DMA_HandleTypeDef *hdma);
static void CRYP_SetKey(CRYP_HandleTypeDef *hcryp, uint32_t *Key, uint32_t KeySize);
static HAL_StatusTypeDef CRYP_AES_IT(CRYP_HandleTypeDef *hcryp);
static HAL_StatusTypeDef CRYP_GCMCCM_SetHeaderPhase(CRYP_HandleTypeDef *hcryp, uint32_t Timeout);
static HAL_StatusTypeDef CRYP_GCMCCM_SetPayloadPhase_IT(CRYP_HandleTypeDef *hcryp);
static HAL_StatusTypeDef CRYP_GCMCCM_SetHeaderPhase_IT(CRYP_HandleTypeDef *hcryp);
static HAL_StatusTypeDef CRYP_GCMCCM_SetHeaderPhase_DMA(CRYP_HandleTypeDef *hcryp);
static void CRYP_Workaround(CRYP_HandleTypeDef *hcryp, uint32_t Timeout);
static HAL_StatusTypeDef CRYP_AESGCM_Process_DMA(CRYP_HandleTypeDef *hcryp);
static HAL_StatusTypeDef CRYP_AESGCM_Process_IT (CRYP_HandleTypeDef *hcryp);
static HAL_StatusTypeDef CRYP_AESGCM_Process(CRYP_HandleTypeDef *hcryp, uint32_t Timeout);
static HAL_StatusTypeDef CRYP_AESCCM_Process(CRYP_HandleTypeDef *hcryp, uint32_t Timeout);
static HAL_StatusTypeDef CRYP_AESCCM_Process_IT(CRYP_HandleTypeDef *hcryp);
static HAL_StatusTypeDef CRYP_AESCCM_Process_DMA(CRYP_HandleTypeDef *hcryp);
static HAL_StatusTypeDef CRYP_AES_ProcessData(CRYP_HandleTypeDef *hcrypt, uint32_t Timeout);
static HAL_StatusTypeDef CRYP_AES_Encrypt(CRYP_HandleTypeDef *hcryp, uint32_t Timeout);
static HAL_StatusTypeDef CRYP_AES_Decrypt(CRYP_HandleTypeDef *hcryp, uint32_t Timeout);
static HAL_StatusTypeDef CRYP_AES_Decrypt_IT(CRYP_HandleTypeDef *hcryp);
static HAL_StatusTypeDef CRYP_AES_Encrypt_IT(CRYP_HandleTypeDef *hcryp);
static HAL_StatusTypeDef CRYP_AES_Decrypt_DMA(CRYP_HandleTypeDef *hcryp);
static HAL_StatusTypeDef CRYP_TDES_IT(CRYP_HandleTypeDef *hcryp);
static HAL_StatusTypeDef CRYP_WaitOnIFEMFlag(CRYP_HandleTypeDef *hcryp, uint32_t Timeout);
static HAL_StatusTypeDef CRYP_WaitOnBUSYFlag(CRYP_HandleTypeDef *hcryp, uint32_t Timeout);
static HAL_StatusTypeDef CRYP_WaitOnOFNEFlag(CRYP_HandleTypeDef *hcryp, uint32_t Timeout);
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
  if(hcryp == NULL)
  {
    return HAL_ERROR;
  } 
  
  /* Check parameters */
  assert_param(IS_CRYP_KEYSIZE(hcryp->Init.KeySize));
  assert_param(IS_CRYP_DATATYPE(hcryp->Init.DataType));
  assert_param(IS_CRYP_ALGORITHM(hcryp->Init.Algorithm));  
  
  if(hcryp->State == HAL_CRYP_STATE_RESET)
  {
    /* Allocate lock resource and initialize it */
    hcryp->Lock = HAL_UNLOCKED;
    
    /* Init the low level hardware */
    HAL_CRYP_MspInit(hcryp);
  }
  
  /* Set the key size(This bit field is ‘don’t care’ in the DES or TDES modes) data type and Algorithm */ 
  MODIFY_REG(hcryp->Instance->CR, CRYP_CR_DATATYPE|CRYP_CR_KEYSIZE|CRYP_CR_ALGOMODE, hcryp->Init.DataType | hcryp->Init.KeySize | hcryp->Init.Algorithm);
  
  /* Reset Error Code field */
  hcryp->ErrorCode = HAL_CRYP_ERROR_NONE; 
  
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
    
    /* Set the key size(This bit field is ‘don’t care’ in the DES or TDES modes) data type, AlgoMode and operating mode*/     
    MODIFY_REG(hcryp->Instance->CR, CRYP_CR_DATATYPE|CRYP_CR_KEYSIZE|CRYP_CR_ALGOMODE, hcryp->Init.DataType | hcryp->Init.KeySize | hcryp->Init.Algorithm);
    
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
  * @param  Size: Length of the plaintext buffer in word.
  * @param  Output: Pointer to the output buffer(ciphertext)
  * @param  Timeout: Specify Timeout value  
  * @retval HAL status
  */
HAL_StatusTypeDef HAL_CRYP_Encrypt(CRYP_HandleTypeDef *hcryp, uint32_t *Input, uint16_t Size, uint32_t *Output, uint32_t Timeout)
{
  uint32_t algo = 0U;
  HAL_StatusTypeDef state;
  
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
    hcryp->Size = Size;
    
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
      state = CRYP_TDES_Process(hcryp,Timeout);     
      break;
      
    case CRYP_AES_ECB:
    case CRYP_AES_CBC:
    case CRYP_AES_CTR:
      
      /* AES encryption */       
      state = CRYP_AES_Encrypt(hcryp, Timeout);
      break;   
      
    case CRYP_AES_GCM:
      
      /* AES GCM encryption */       
      state = CRYP_AESGCM_Process(hcryp, Timeout);   
      break;
      
    case CRYP_AES_CCM:
      
      /* AES CCM encryption */  
      state = CRYP_AESCCM_Process(hcryp,Timeout);     
      break;
      
    default:
      hcryp->ErrorCode |= HAL_CRYP_ERROR_NOT_SUPPORTED;
      return HAL_ERROR;  
    }      
    
    if (state == HAL_OK)
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
  HAL_StatusTypeDef state;
  uint32_t algo = 0U; 
  
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
    hcryp->Size = Size;
    
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
      state = CRYP_TDES_Process(hcryp, Timeout);
      
      break;
      
    case CRYP_AES_ECB:
    case CRYP_AES_CBC:
    case CRYP_AES_CTR:
      
      /* AES decryption */   
      state = CRYP_AES_Decrypt(hcryp, Timeout);
      break;   
      
    case CRYP_AES_GCM:
      
      /* AES GCM decryption */       
      state = CRYP_AESGCM_Process (hcryp, Timeout) ;   
      break;
      
    case CRYP_AES_CCM:
      
      /* AES CCM decryption */ 
      state = CRYP_AESCCM_Process(hcryp, Timeout); 
      break;
      
    default:
      hcryp->ErrorCode |= HAL_CRYP_ERROR_NOT_SUPPORTED;
      return HAL_ERROR;   
    }      
    
    if (state == HAL_OK)
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
  uint32_t algo = 0U; 
  
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
    hcryp->Size = Size;
    
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
      
      CRYP_AES_Encrypt_IT(hcryp);
      break;   
      
    case CRYP_AES_GCM:
      
      CRYP_AESGCM_Process_IT (hcryp) ;  
      break;
      
    case CRYP_AES_CCM:
      
      CRYP_AESCCM_Process_IT(hcryp);  
      break;
      
    default:
      hcryp->ErrorCode |= HAL_CRYP_ERROR_NOT_SUPPORTED;
      return HAL_ERROR;   
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
  uint32_t algo = 0U;
  
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
    hcryp->Size = Size;
    
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
      CRYP_AES_Decrypt_IT(hcryp);
      break;   
      
    case CRYP_AES_GCM:
      
      /* AES GCM decryption */ 
      CRYP_AESGCM_Process_IT (hcryp) ;
      break;
      
    case CRYP_AES_CCM:
      
      /* AES CCMdecryption */ 
      CRYP_AESCCM_Process_IT(hcryp);  
      break;
      
    default:
      hcryp->ErrorCode |= HAL_CRYP_ERROR_NOT_SUPPORTED;
      return HAL_ERROR;  
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
  uint32_t algo = 0U; 
  
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
    hcryp->Size = Size;
    
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
      CRYP_SetDMAConfig(hcryp, (uint32_t)( hcryp->pCrypInBuffPtr), (hcryp->Size), (uint32_t)(hcryp->pCrypOutBuffPtr)); 
      
      break;
      
    case CRYP_AES_ECB:
    case CRYP_AES_CBC:
    case CRYP_AES_CTR:
      
      /*  Set the Key*/
      CRYP_SetKey(hcryp, hcryp->Init.pKey, hcryp->Init.KeySize);
      
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
      CRYP_SetDMAConfig(hcryp, (uint32_t)( hcryp->pCrypInBuffPtr), Size, (uint32_t)(hcryp->pCrypOutBuffPtr));          
      break;   
      
    case CRYP_AES_GCM:
      
      /* AES GCM encryption */ 
      CRYP_AESGCM_Process_DMA (hcryp) ;  
      break;
      
    case CRYP_AES_CCM:
      
      /* AES CCM encryption */ 
      CRYP_AESCCM_Process_DMA(hcryp);  
      break;
      
    default:
      hcryp->ErrorCode |= HAL_CRYP_ERROR_NOT_SUPPORTED;
      return HAL_ERROR;   
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
  uint32_t algo = 0U; 
  
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
    hcryp->Size = Size;  
    
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
      CRYP_SetDMAConfig(hcryp, (uint32_t)( hcryp->pCrypInBuffPtr), (hcryp->Size), (uint32_t)(hcryp->pCrypOutBuffPtr));    
      break;
      
    case CRYP_AES_ECB:
    case CRYP_AES_CBC:
    case CRYP_AES_CTR:
      
      /* AES decryption */ 
      CRYP_AES_Decrypt_DMA(hcryp);
      break;   
      
    case CRYP_AES_GCM:
      
      /* AES GCM decryption */ 
      CRYP_AESGCM_Process_DMA (hcryp) ;
      
      break;
      
    case CRYP_AES_CCM:
      
      /* AES CCM decryption */ 
      CRYP_AESCCM_Process_DMA(hcryp);     
      break;
      
    default:
      hcryp->ErrorCode |= HAL_CRYP_ERROR_NOT_SUPPORTED;
      return HAL_ERROR;  
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
  uint32_t CurrentMode  = 0U; 
  
  /*put CRYP_IT_OUTI flag status in CurrentMode variable*/
  CurrentMode  = __HAL_CRYP_GET_IT(hcryp, CRYP_IT_OUTI);
  
  if((__HAL_CRYP_GET_IT(hcryp, CRYP_IT_INI) != RESET)| (CurrentMode != RESET))
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
  
  uint32_t temp = 0U;  /* Temporary CrypOutBuff */  
  
  /* Enable CRYP */
  __HAL_CRYP_ENABLE(hcryp);
  
  /*Start processing*/  
  while((hcryp->CrypInCount < hcryp->Size) && (hcryp->CrypOutCount < hcryp->Size))
  {      
    /* Write plain data and get cipher data */
    if(((hcryp->Instance->SR & CRYP_FLAG_IFNF ) != RESET) && (hcryp->CrypInCount < hcryp->Size))
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
      HAL_CRYP_ErrorCallback(hcryp);
    }
    
    if(((hcryp->Instance->SR & CRYP_FLAG_OFNE ) != RESET) && (hcryp->CrypOutCount < hcryp->Size))
    {
      /* Read the output block from the Output FIFO and put them in temporary Buffer then get CrypOutBuff from temporary buffer  */    
      temp = hcryp->Instance->DOUT;
      *(uint32_t *)(hcryp->pCrypOutBuffPtr + (hcryp->CrypOutCount)) = temp;      
      hcryp->CrypOutCount++;  
      temp = hcryp->Instance->DOUT;  
      *(uint32_t *)(hcryp->pCrypOutBuffPtr + (hcryp->CrypOutCount)) = temp;      
      hcryp->CrypOutCount++;  
    }        
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
static HAL_StatusTypeDef CRYP_TDES_IT(CRYP_HandleTypeDef *hcryp)
{
  uint32_t temp = 0U;  /* Temporary CrypOutBuff */ 
  
  if(hcryp->State == HAL_CRYP_STATE_BUSY)
  { 
    if((__HAL_CRYP_GET_IT(hcryp, CRYP_IT_INI) != RESET) && (__HAL_CRYP_GET_FLAG(hcryp, CRYP_FLAG_INRIS) != RESET))
      
    {     
      /* Write input block in the IN FIFO */
      hcryp->Instance->DIN = *(uint32_t *)(hcryp->pCrypInBuffPtr + hcryp->CrypInCount );
      hcryp->CrypInCount++;
      hcryp->Instance->DIN = *(uint32_t *)(hcryp->pCrypInBuffPtr + hcryp->CrypInCount );
      hcryp->CrypInCount++;
      
      if(hcryp->CrypInCount ==  hcryp->Size)
      {     
        /* Disable interruption */
        __HAL_CRYP_DISABLE_IT(hcryp, CRYP_IT_INI);
        
        /* Call the input data transfer complete callback */
        HAL_CRYP_InCpltCallback(hcryp);
      }
    }
    if((__HAL_CRYP_GET_IT(hcryp, CRYP_IT_OUTI) != RESET)&& (__HAL_CRYP_GET_FLAG(hcryp, CRYP_FLAG_OUTRIS) != RESET))
    {
      /* Read the output block from the Output FIFO and put them in temporary Buffer then get CrypOutBuff from temporary buffer  */    
      temp = hcryp->Instance->DOUT;
      *(uint32_t *)(hcryp->pCrypOutBuffPtr + (hcryp->CrypOutCount)) = temp;      
      hcryp->CrypOutCount++;  
      temp = hcryp->Instance->DOUT;  
      *(uint32_t *)(hcryp->pCrypOutBuffPtr + (hcryp->CrypOutCount)) = temp;      
      hcryp->CrypOutCount++;            
      if(hcryp->CrypOutCount ==  hcryp->Size)
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
        HAL_CRYP_OutCpltCallback(hcryp);
      }
    }   
    return HAL_OK;  
  }
  else
  {
    /* Busy error code field */
    hcryp->ErrorCode |= HAL_CRYP_ERROR_BUSY; 
    return HAL_ERROR;
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
  
  /*  Set the Key*/
  CRYP_SetKey(hcryp, hcryp->Init.pKey, hcryp->Init.KeySize);
  
  if (hcryp->Init.Algorithm != CRYP_AES_ECB)
  {
    /* Set the Initialization Vector*/
    hcryp->Instance->IV0LR = *(uint32_t*)(hcryp->Init.pInitVect);
    hcryp->Instance->IV0RR = *(uint32_t*)(hcryp->Init.pInitVect+1);
    hcryp->Instance->IV1LR = *(uint32_t*)(hcryp->Init.pInitVect+2);
    hcryp->Instance->IV1RR = *(uint32_t*)(hcryp->Init.pInitVect+3);
  }
  
  /* Set the phase */
  hcryp->Phase = CRYP_PHASE_PROCESS;
  
  /* Enable CRYP */
  __HAL_CRYP_ENABLE(hcryp);
  
  while((hcryp->CrypInCount < hcryp->Size) && (hcryp->CrypOutCount < hcryp->Size))
  {      
    /* Write plain Ddta and get cipher data */
    CRYP_AES_ProcessData(hcryp,Timeout);   
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
  CRYP_SetKey(hcryp, hcryp->Init.pKey, hcryp->Init.KeySize);
  
  if (hcryp->Init.Algorithm != CRYP_AES_ECB)
  {
    /* Set the Initialization Vector*/
    hcryp->Instance->IV0LR = *(uint32_t*)(hcryp->Init.pInitVect);
    hcryp->Instance->IV0RR = *(uint32_t*)(hcryp->Init.pInitVect+1);
    hcryp->Instance->IV1LR = *(uint32_t*)(hcryp->Init.pInitVect+2);
    hcryp->Instance->IV1RR = *(uint32_t*)(hcryp->Init.pInitVect+3);
  }
  /* Set the phase */
  hcryp->Phase = CRYP_PHASE_PROCESS;
  
  if(hcryp->Size != 0U)
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
static HAL_StatusTypeDef CRYP_AES_Decrypt(CRYP_HandleTypeDef *hcryp, uint32_t Timeout )
{  
  /*  Key preparation for ECB/CBC */
  if (hcryp->Init.Algorithm != CRYP_AES_CTR)   /*ECB or CBC*/  
  {
    /* change ALGOMODE to key preparation for decryption*/
    MODIFY_REG(hcryp->Instance->CR, CRYP_CR_ALGOMODE, CRYP_CR_ALGOMODE_AES_KEY );
    
    /*  Set the Key*/
    CRYP_SetKey(hcryp, hcryp->Init.pKey, hcryp->Init.KeySize);
    
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
  }
  else  /*Algorithm CTR */
  {  
    /*  Set the Key*/
    CRYP_SetKey(hcryp, hcryp->Init.pKey, hcryp->Init.KeySize);
  } 
  
  /* Set IV */ 
  if (hcryp->Init.Algorithm != CRYP_AES_ECB)
  {
    /* Set the Initialization Vector*/
    hcryp->Instance->IV0LR = *(uint32_t*)(hcryp->Init.pInitVect);
    hcryp->Instance->IV0RR = *(uint32_t*)(hcryp->Init.pInitVect+1);
    hcryp->Instance->IV1LR = *(uint32_t*)(hcryp->Init.pInitVect+2);
    hcryp->Instance->IV1RR = *(uint32_t*)(hcryp->Init.pInitVect+3);
  }     
  /* Set the phase */
  hcryp->Phase = CRYP_PHASE_PROCESS;
  
  /* Enable CRYP */
  __HAL_CRYP_ENABLE(hcryp);
  
  while((hcryp->CrypInCount < hcryp->Size) && (hcryp->CrypOutCount < hcryp->Size))
  {      
    /* Write plain data and get cipher data */
    CRYP_AES_ProcessData(hcryp,Timeout);
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
    /* change ALGOMODE to key preparation for decryption*/
    MODIFY_REG(hcryp->Instance->CR, CRYP_CR_ALGOMODE, CRYP_CR_ALGOMODE_AES_KEY );
    
    /*  Set the Key*/
    CRYP_SetKey(hcryp, hcryp->Init.pKey, hcryp->Init.KeySize);
    
    /* Enable CRYP */
    __HAL_CRYP_ENABLE(hcryp);
    
    /* Wait for BUSY flag to be raised */
    count = CRYP_TIMEOUT_KEYPREPARATION;
    do
    {
      if(count-- == 0U)
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
  }
  else  /*Algorithm CTR */
  {  
    /*  Set the Key*/
    CRYP_SetKey(hcryp, hcryp->Init.pKey, hcryp->Init.KeySize);
  }    
  
  /* Set IV */ 
  if (hcryp->Init.Algorithm != CRYP_AES_ECB)
  {
    /* Set the Initialization Vector*/
    hcryp->Instance->IV0LR = *(uint32_t*)(hcryp->Init.pInitVect);
    hcryp->Instance->IV0RR = *(uint32_t*)(hcryp->Init.pInitVect+1);
    hcryp->Instance->IV1LR = *(uint32_t*)(hcryp->Init.pInitVect+2);
    hcryp->Instance->IV1RR = *(uint32_t*)(hcryp->Init.pInitVect+3);
  }     
  /* Set the phase */
  hcryp->Phase = CRYP_PHASE_PROCESS;
  if(hcryp->Size != 0)
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
  
  /*  Key preparation for ECB/CBC */
  if (hcryp->Init.Algorithm != CRYP_AES_CTR)  
  {
    /* change ALGOMODE to key preparation for decryption*/
    MODIFY_REG(hcryp->Instance->CR, CRYP_CR_ALGOMODE, CRYP_CR_ALGOMODE_AES_KEY );
    
    /*  Set the Key*/
    CRYP_SetKey(hcryp, hcryp->Init.pKey, hcryp->Init.KeySize);
    
    /* Enable CRYP */
    __HAL_CRYP_ENABLE(hcryp);
    
    /* Wait for BUSY flag to be raised */
    count = CRYP_TIMEOUT_KEYPREPARATION;
    do
    {
      if(count-- == 0U)
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
  }
  else  /*Algorithm CTR */
  {  
    /*  Set the Key*/
    CRYP_SetKey(hcryp, hcryp->Init.pKey, hcryp->Init.KeySize);
  } 
  
  if (hcryp->Init.Algorithm != CRYP_AES_ECB)
  {
    /* Set the Initialization Vector*/
    hcryp->Instance->IV0LR = *(uint32_t*)(hcryp->Init.pInitVect);
    hcryp->Instance->IV0RR = *(uint32_t*)(hcryp->Init.pInitVect+1);
    hcryp->Instance->IV1LR = *(uint32_t*)(hcryp->Init.pInitVect+2);
    hcryp->Instance->IV1RR = *(uint32_t*)(hcryp->Init.pInitVect+3);
  }      
  /* Set the phase */
  hcryp->Phase = CRYP_PHASE_PROCESS;
  
  if(hcryp->Size != 0)
  {    
    /* Set the input and output addresses and start DMA transfer */ 
    CRYP_SetDMAConfig(hcryp, (uint32_t)( hcryp->pCrypInBuffPtr), hcryp->Size, (uint32_t)(hcryp->pCrypOutBuffPtr));    
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
  hcryp->Instance->DMACR &= (uint32_t)(~CRYP_DMACR_DIEN);  
  
  /* Call input data transfer complete callback */
  HAL_CRYP_InCpltCallback(hcryp);
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
  hcryp->Instance->DMACR &= (uint32_t)(~CRYP_DMACR_DOEN);
  if((hcryp->Init.Algorithm & CRYP_AES_GCM) != CRYP_AES_GCM)
  {  
    /* Disable CRYP  (not allowed in  GCM)*/
    __HAL_CRYP_DISABLE(hcryp);
  } 
  
  /* Change the CRYP state to ready */
  hcryp->State = HAL_CRYP_STATE_READY;
  
  /* Process unlocked */
  __HAL_UNLOCK(hcryp); 
  
  /* Call output data transfer complete callback */
  HAL_CRYP_OutCpltCallback(hcryp);
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
  
  /* Call error callback */
  HAL_CRYP_ErrorCallback(hcryp);
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
  HAL_DMA_Start_IT(hcryp->hdmain, inputaddr, (uint32_t)&hcryp->Instance->DIN, Size);
  
  /* Enable the output DMA Stream */
  HAL_DMA_Start_IT(hcryp->hdmaout, (uint32_t)&hcryp->Instance->DOUT, outputaddr, Size);
  
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
static HAL_StatusTypeDef CRYP_AES_ProcessData(CRYP_HandleTypeDef *hcryp, uint32_t Timeout)
{
  
  uint32_t temp = 0U;  /* Temporary CrypOutBuff */ 
  
  if(((hcryp->Instance->SR & CRYP_FLAG_IFNF ) != RESET) && (hcryp->CrypInCount < hcryp->Size))
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
    HAL_CRYP_ErrorCallback(hcryp);
  } 
  
  if(((hcryp->Instance->SR & CRYP_FLAG_OFNE ) != RESET) && (hcryp->CrypOutCount < hcryp->Size))
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
  
  /* Return function status */
  return HAL_OK;
}

/** 
  * @brief  Handle CRYP block input/output data handling under interruption.
  * @note   The function is called under interruption only, once
  *         interruptions have been enabled by HAL_CRYP_Encrypt_IT or HAL_CRYP_Decrypt_IT.
  * @param  hcryp: pointer to a CRYP_HandleTypeDef structure that contains
  *         the configuration information for CRYP module.
  * @retval HAL status
  */
static HAL_StatusTypeDef CRYP_AES_IT(CRYP_HandleTypeDef *hcryp)
{
  uint32_t temp = 0U;  /* Temporary CrypOutBuff */
  
  if(hcryp->State == HAL_CRYP_STATE_BUSY)
  {    
    if(((hcryp->Instance->SR & CRYP_FLAG_IFNF ) != RESET) && (hcryp->CrypInCount < hcryp->Size))
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
      if(hcryp->CrypInCount ==  hcryp->Size)
      {     
        /* Disable interrupts */
        __HAL_CRYP_DISABLE_IT(hcryp, CRYP_IT_INI);
        
        /* Call the input data transfer complete callback */
        HAL_CRYP_InCpltCallback(hcryp);
      }
    }   
    if(((hcryp->Instance->SR & CRYP_FLAG_OFNE ) != RESET) && (hcryp->CrypOutCount < hcryp->Size))
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
      if(hcryp->CrypOutCount ==  hcryp->Size)
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
        HAL_CRYP_OutCpltCallback(hcryp);
      }
    }    
    /* Return function status */
    return HAL_OK;
  } 
  else
  {
    /* Busy error code field */
    hcryp->ErrorCode |= HAL_CRYP_ERROR_BUSY; 
    return HAL_ERROR; 
  }
} 

/**
  * @brief  Writes Key in Key registers. 
  * @param  hcryp: pointer to a CRYP_HandleTypeDef structure that contains
  *         the configuration information for CRYP module
  * @param  Key: Pointer to Key buffer
  * @param  KeySize: Size of Key
  * @retval None
  */
static void CRYP_SetKey(CRYP_HandleTypeDef *hcryp, uint32_t *Key, uint32_t KeySize)
{   
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
  uint32_t tickstart = 0U;
  uint32_t payloadlength = 0U;
  
  /*  Reset CrypHeaderCount */
  hcryp->CrypHeaderCount = 0U; 
  
  /****************************** Init phase **********************************/
  
  CRYP_SET_PHASE(hcryp,CRYP_PHASE_INIT);
  
  /* Set the key */
  CRYP_SetKey(hcryp, hcryp->Init.pKey, hcryp->Init.KeySize);
  
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
      if((Timeout == 0U)||((HAL_GetTick() - tickstart ) > Timeout))
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
  
  if(CRYP_GCMCCM_SetHeaderPhase(hcryp,  Timeout) != HAL_OK)
  {
    return HAL_ERROR;
  }
  
  /*************************Payload phase ************************************/   
  
  /* Set the phase */
  hcryp->Phase = CRYP_PHASE_PROCESS;
  
  /* Disable the CRYP peripheral */
  __HAL_CRYP_DISABLE(hcryp);
  
  /* Select payload phase once the header phase is performed */
  CRYP_SET_PHASE(hcryp, CRYP_PHASE_PAYLOAD); 
  
  /* Enable the CRYP peripheral */
  __HAL_CRYP_ENABLE(hcryp);
  
  /* Get tick */
  tickstart = HAL_GetTick();
  
  /* Write input data and get output Data */
  if ((hcryp->Size % 4U) == 0U) 
  {
    while((hcryp->CrypInCount < hcryp->Size) && (hcryp->CrypOutCount < hcryp->Size))
    {      
      /* Write plain data and get cipher data */
      CRYP_AES_ProcessData(hcryp,Timeout);
      
      /* Check for the Timeout */
      if(Timeout != HAL_MAX_DELAY)
      {
        if((Timeout == 0U)||((HAL_GetTick() - tickstart ) > Timeout))
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
  }
  else
  {
    payloadlength =  (((hcryp->Size)/4U)*4U) ;   
    
    /*Write input block in the IN FIFO without last block */
    while((hcryp->CrypInCount < payloadlength) && (hcryp->CrypOutCount < payloadlength))
    {      
      /* Write input Data and get output Data */
      CRYP_AES_ProcessData(hcryp,Timeout);
      
      /* Check for the Timeout */
      if(Timeout != HAL_MAX_DELAY)
      {
        if((Timeout == 0U)||((HAL_GetTick() - tickstart ) > Timeout))
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
    /*  Workaround 2 :  CRYP1 & AES generates correct TAG for GCM mode only when input block size is multiple of
    128 bits. If lthe size of the last block of payload is inferior to 128 bits, when GCM encryption
    is selected, then the TAG message will be wrong.*/   
    CRYP_Workaround(hcryp,Timeout);   
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
  
  /*  Reset CrypHeaderCount */
  hcryp->CrypHeaderCount =0U;
  
  /******************************* Init phase *********************************/
  
  CRYP_SET_PHASE(hcryp,CRYP_PHASE_INIT);
  
  /* Set the key */
  CRYP_SetKey(hcryp, hcryp->Init.pKey, hcryp->Init.KeySize);
  
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
    if(count-- == 0U)
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
  
  /***************************** Header phase *********************************/   
  
  /* Select header phase */
  CRYP_SET_PHASE(hcryp, CRYP_PHASE_HEADER);  
  
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
  uint32_t payloadlength = 0U;
  
  /*  Reset CrypHeaderCount */
  hcryp->CrypHeaderCount = 0U;
  
  /*************************** Init phase ************************************/
  
  CRYP_SET_PHASE(hcryp,CRYP_PHASE_INIT);
  
  /* Set the key */
  CRYP_SetKey(hcryp, hcryp->Init.pKey, hcryp->Init.KeySize);
  
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
    if(count-- == 0U)
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
  
  /************************ Header phase *************************************/
  
  if(CRYP_GCMCCM_SetHeaderPhase_DMA(hcryp) != HAL_OK)
  {
    return HAL_ERROR;
  }
  
  /************************ Payload phase ************************************/   
  
  /* Set the phase */
  hcryp->Phase = CRYP_PHASE_PROCESS;  
  
  /* Disable the CRYP peripheral */
  __HAL_CRYP_DISABLE(hcryp);
  
  /* Select payload phase once the header phase is performed */
  CRYP_SET_PHASE(hcryp, CRYP_PHASE_PAYLOAD);
  
  if(hcryp->Size != 0U)
  { 
    /* Size should be %4  otherwise Tag will  be incorrectly generated for GCM Encryption:
    Workaround is implemented in polling mode, so if last block of 
    payload <128bit don't use DMA mode otherwise TAG is incorrectly generated . */
    /* Set the input and output addresses and start DMA transfer */ 
    if ((hcryp->Size % 4U) == 0U) 
    {  
      CRYP_SetDMAConfig(hcryp, (uint32_t)( hcryp->pCrypInBuffPtr), hcryp->Size, (uint32_t)(hcryp->pCrypOutBuffPtr));    
    }
    else /*to compute last word<128bits, otherwise it will not be encrypted/decrypted */
    {
      payloadlength =  (hcryp->Size)+(4-(hcryp->Size)%4U) ;
      
      /* Set the input and output addresses and start DMA transfer, pCrypOutBuffPtr size should be %4 */ 
      CRYP_SetDMAConfig(hcryp, (uint32_t)( hcryp->pCrypInBuffPtr), payloadlength, (uint32_t)(hcryp->pCrypOutBuffPtr));
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
  * @param  hcryp: pointer to a CRYP_HandleTypeDef structure that contains
  *         the configuration information for CRYP module
  * @param  Timeout: Timeout duration
  * @retval HAL status
  */
static HAL_StatusTypeDef CRYP_AESCCM_Process(CRYP_HandleTypeDef *hcryp, uint32_t Timeout)
{
  uint32_t tickstart = 0U;
  uint32_t payloadlength =0U;
  
  /*  Reset CrypHeaderCount */
  hcryp->CrypHeaderCount = 0U;     
  
  /********************** Init phase ******************************************/
  
  CRYP_SET_PHASE(hcryp,CRYP_PHASE_INIT);
  
  /* Set the key */
  CRYP_SetKey(hcryp, hcryp->Init.pKey, hcryp->Init.KeySize);
  
  /* Set the initialization vector (IV) with CTR1 information */
  hcryp->Instance->IV0LR = (hcryp->Init.B0[0]) & CRYP_CCM_CTR1_0;
  hcryp->Instance->IV0RR = hcryp->Init.B0[1];
  hcryp->Instance->IV1LR = hcryp->Init.B0[2];
  hcryp->Instance->IV1RR = (hcryp->Init.B0[3] & CRYP_CCM_CTR1_1)|  CRYP_CCM_CTR1_2;

  /* Enable the CRYP peripheral */
  __HAL_CRYP_ENABLE(hcryp);
  
  /*Write  B0 packet into CRYP_DR*/
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
      if((Timeout == 0)||((HAL_GetTick() - tickstart ) > Timeout))
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
  
  /* Get tick */
  tickstart = HAL_GetTick();
  
  /* Write input data and get output data */
  if((hcryp->Size % 4U) == 0U) 
  {
    while((hcryp->CrypInCount < hcryp->Size) && (hcryp->CrypOutCount < hcryp->Size))
    {      
      /* Write plain data and get cipher data */
      CRYP_AES_ProcessData(hcryp,Timeout);
      
      /* Check for the Timeout */
      if(Timeout != HAL_MAX_DELAY)
      {
        if((Timeout == 0)||((HAL_GetTick() - tickstart ) > Timeout))
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
  }
  else
  {
    if(hcryp->Size > 4U)
    {
      payloadlength =  (((hcryp->Size)/4)*4) ;   
      /*Write input block in the IN FIFO without last block */
      while((hcryp->CrypInCount < payloadlength) && (hcryp->CrypOutCount < payloadlength))
      {      
        /* Write input data and get output data */
        CRYP_AES_ProcessData(hcryp,Timeout);
        
        /* Check for the Timeout */
        if(Timeout != HAL_MAX_DELAY)
        {
          if((Timeout == 0)||((HAL_GetTick() - tickstart ) > Timeout))
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
    }
    /* CRYP Workaround :  CRYP1 generates correct TAG  during CCM decryption only when ciphertext blocks size is multiple of
    128 bits. If lthe size of the last block of payload is inferior to 128 bits, when CCM decryption
    is selected, then the TAG message will be wrong.*/   
    CRYP_Workaround(hcryp,Timeout);
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
  
  /*  Reset CrypHeaderCount */
  hcryp->CrypHeaderCount = 0U; 
  
  /************ Init phase ************/
  
  CRYP_SET_PHASE(hcryp,CRYP_PHASE_INIT);
  
  /* Set the key */
  CRYP_SetKey(hcryp, hcryp->Init.pKey, hcryp->Init.KeySize);
  
  /* Set the initialization vector (IV) with CTR1 information */
  hcryp->Instance->IV0LR = (hcryp->Init.B0[0]) & CRYP_CCM_CTR1_0;
  hcryp->Instance->IV0RR = hcryp->Init.B0[1];
  hcryp->Instance->IV1LR = hcryp->Init.B0[2];
  hcryp->Instance->IV1RR = (hcryp->Init.B0[3] & CRYP_CCM_CTR1_1)|  CRYP_CCM_CTR1_2;
  
  /* Enable the CRYP peripheral */
  __HAL_CRYP_ENABLE(hcryp);
  
  /*Write the B0 packet into CRYP_DR*/
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
    if(count-- == 0U)
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
  uint32_t payloadlength = 0U;
  __IO uint32_t count    = 0U;
  
  /*  Reset CrypHeaderCount */
  hcryp->CrypHeaderCount = 0U;
  
  /************************** Init phase **************************************/
  
  CRYP_SET_PHASE(hcryp,CRYP_PHASE_INIT);
  
  /* Set the key */
  CRYP_SetKey(hcryp, hcryp->Init.pKey, hcryp->Init.KeySize);  
  
  /* Set the initialization vector (IV) with CTR1 information */
  hcryp->Instance->IV0LR = (hcryp->Init.B0[0]) & CRYP_CCM_CTR1_0;
  hcryp->Instance->IV0RR = hcryp->Init.B0[1];
  hcryp->Instance->IV1LR = hcryp->Init.B0[2];
  hcryp->Instance->IV1RR = (hcryp->Init.B0[3] & CRYP_CCM_CTR1_1)|  CRYP_CCM_CTR1_2;
  
  /* Enable the CRYP peripheral */
  __HAL_CRYP_ENABLE(hcryp);
  
  /*Write the B0 packet into CRYP_DR*/
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
    if(count-- == 0U)
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
  
  /********************* Header phase *****************************************/
  
  if(CRYP_GCMCCM_SetHeaderPhase_DMA(hcryp) != HAL_OK)
  {
    return HAL_ERROR;
  }
  
  /******************** Payload phase *****************************************/   
  
  /* Set the phase */
  hcryp->Phase = CRYP_PHASE_PROCESS;  
  
  /* Disable the CRYP peripheral */
  __HAL_CRYP_DISABLE(hcryp);
  
  /* Select payload phase once the header phase is performed */
  CRYP_SET_PHASE(hcryp, CRYP_PHASE_PAYLOAD);
  
  if(hcryp->Size != 0U)
  { 
    /* Size should be %4  otherwise Tag will  be incorrectly generated for GCM Encryption & CCM Decryption
    Workaround is implemented in polling mode, so if last block of 
    payload <128bit don't use HAL_CRYP_AESGCM_DMA otherwise TAG is incorrectly generated for GCM Encryption. */
    /* Set the input and output addresses and start DMA transfer */ 
    if ((hcryp->Size % 4U) == 0U) 
    {  
      CRYP_SetDMAConfig(hcryp, (uint32_t)( hcryp->pCrypInBuffPtr), hcryp->Size, (uint32_t)(hcryp->pCrypOutBuffPtr));   
    }
    else
    {
      payloadlength =  (hcryp->Size)+(4-(hcryp->Size %4)) ; 
      
      /* Set the input and output addresses and start DMA transfer, pCrypOutBuffPtr size should be %4*/ 
      CRYP_SetDMAConfig(hcryp, (uint32_t)( hcryp->pCrypInBuffPtr), payloadlength, (uint32_t)(hcryp->pCrypOutBuffPtr));
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
static HAL_StatusTypeDef CRYP_GCMCCM_SetPayloadPhase_IT(CRYP_HandleTypeDef *hcryp)
{  
  uint32_t loopcounter = 0U;
  uint32_t temp        = 0U;  /* Temporary CrypOutBuff */
  
  /***************************** Payload phase *******************************/
  
  if(hcryp->Size == 0U)
  {     
    /* Disable interrupts */
    __HAL_CRYP_DISABLE_IT(hcryp, CRYP_IT_INI| CRYP_IT_OUTI);
    
    /* Process unlocked */
    __HAL_UNLOCK(hcryp);
    
    /* Change the CRYP state */
    hcryp->State = HAL_CRYP_STATE_READY;      
  }    
  
  else if ((hcryp->Size) - (hcryp->CrypInCount) >= 4)
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
    if(hcryp->Size == hcryp->CrypInCount) 
    {     
      /* Disable interrupts */
      __HAL_CRYP_DISABLE_IT(hcryp, CRYP_IT_INI);
      
      /* Call the input data transfer complete callback */
      HAL_CRYP_InCpltCallback(hcryp);
    }    
    if(hcryp->CrypOutCount < hcryp->Size)        
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
      if (hcryp->Size == hcryp->CrypOutCount)
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
        HAL_CRYP_OutCpltCallback(hcryp);
      }    
    }      
  }   
  else if ((hcryp->Size %4U )!= 0U)
  {   
    /* Size should be %4  otherwise TAG will  be incorrectly generated for GCM Encryption & CCM Decryption
    Workaround is implemented in polling mode, so if last block of 
    payload <128bit don't use CRYP_AESGCM_Encrypt_IT otherwise TAG is incorrectly generated. */
    
    /*  Last block optionally pad the data with zeros*/
    for(loopcounter = 0U; loopcounter < (hcryp->Size %4 ); loopcounter++)
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
    
    if((hcryp->Instance->SR & CRYP_FLAG_OFNE ) != RESET) 
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
    if(hcryp->CrypOutCount >=  hcryp->Size)
    {              
      /* Disable interrupts */
      __HAL_CRYP_DISABLE_IT(hcryp, CRYP_IT_OUTI|CRYP_IT_INI);
      
      /* Change the CRYP peripheral state */
      hcryp->State = HAL_CRYP_STATE_READY;
      
      /* Process unlocked */
      __HAL_UNLOCK(hcryp);
      
      /* Call output transfer complete callback */
      HAL_CRYP_OutCpltCallback(hcryp);
    }   
  } 
  
  /* Return function status */
  return HAL_OK;
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
  uint32_t loopcounter = 0U;
  
  /***************************** Header phase for GCM/GMAC or CCM *********************************/
  
  if((hcryp->Init.HeaderSize != 0U))
  {    
    /* Select header phase */
    CRYP_SET_PHASE(hcryp, CRYP_PHASE_HEADER); 
    
    /* Enable the CRYP peripheral */
    __HAL_CRYP_ENABLE(hcryp);    
    
    if ((hcryp->Init.HeaderSize %4U )== 0U)
    { 
      /* HeaderSize %4, no padding */ 
      for(loopcounter = 0U; (loopcounter < hcryp->Init.HeaderSize); loopcounter+=4)
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
  uint32_t loopcounter = 0U;
  
  /***************************** Header phase for GCM/GMAC or CCM *********************************/  
  if((hcryp->Init.HeaderSize != 0U))
  {    
    /* Select header phase */
    CRYP_SET_PHASE(hcryp, CRYP_PHASE_HEADER); 
    
    /* Enable the CRYP peripheral */
    __HAL_CRYP_ENABLE(hcryp);    
    
    if ((hcryp->Init.HeaderSize %4U )== 0U)
    { 
      /* HeaderSize %4, no padding */ 
      for(loopcounter = 0U; (loopcounter < hcryp->Init.HeaderSize); loopcounter+=4)
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
          if(count-- == 0U)
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
      for(loopcounter = 0U; (loopcounter < ((hcryp->Init.HeaderSize)-(hcryp->Init.HeaderSize %4 ))); loopcounter+=4)
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
          if(count-- == 0U)
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
        if(count-- == 0U)
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
      if(count-- == 0U)
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
static HAL_StatusTypeDef CRYP_GCMCCM_SetHeaderPhase_IT(CRYP_HandleTypeDef *hcryp)
{
  uint32_t loopcounter = 0U;
  
  /***************************** Header phase *********************************/
  
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
  else if ((hcryp->Init.HeaderSize) - (hcryp->CrypHeaderCount) >= 4U)
    
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
  
  /* Return function status */
  return HAL_OK; 
}           


/**
  * @brief  Workaround used for GCM/CCM mode. 
  * @param  hcryp: pointer to a CRYP_HandleTypeDef structure that contains
  *         the configuration information for CRYP module
  * @param  Timeout: Timeout value   
  * @retval None
  */
static void CRYP_Workaround(CRYP_HandleTypeDef *hcryp, uint32_t Timeout )
{
  uint32_t  plength = 0U;
  uint32_t  iv1temp = 0U;
  uint32_t  temp[4] = {0};
  uint32_t  temp2[4]= {0};
  uint32_t intermediate_data[4]={0};
  uint32_t index = 0U;   
  
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
    for(index=0; index < (hcryp->Size % 4); index ++)        
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
      HAL_CRYP_ErrorCallback(hcryp);
    }    
    if(((hcryp->Instance->SR & CRYP_FLAG_OFNE ) != RESET) && (hcryp->CrypOutCount < hcryp->Size))
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
      
      for (index=0U; index < (hcryp->Size % 4U); index ++)
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
        HAL_CRYP_ErrorCallback(hcryp);
      } 
      
      if((hcryp->Instance->SR & CRYP_FLAG_OFNE ) != RESET) 
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
    for(index=0; index < (hcryp->Size % 4); index ++)        
    {
      /* Write the last Input block in the IN FIFO */
      hcryp->Instance->DIN  = *(uint32_t *)(hcryp->pCrypInBuffPtr + hcryp->CrypInCount );
      hcryp->CrypInCount++;
    }    
    while(index < 4)
    {
      /* Pad the data with zeros to have a complete block */
      hcryp->Instance->DIN  = 0;
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
      HAL_CRYP_ErrorCallback(hcryp);
    }    
    
    if(((hcryp->Instance->SR & CRYP_FLAG_OFNE ) != RESET) && (hcryp->CrypOutCount < hcryp->Size))
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
      
      plength=(hcryp->Init.B0[3] & 0x000000FFU);
      
      /*set to zero the bits corresponding to the padded bits*/
      for(index = (hcryp->Size % 4U); index<4U; index ++)        
      {
        intermediate_data[index] =0U;
      } 
      
      if ((plength %4U)==1U)
      {
        intermediate_data[(hcryp->Size % 4U)-1U] = intermediate_data[(hcryp->Size % 4U)-1U] & 0xFF000000U;
      }
      if ((plength %4U)==2U)
      {
        intermediate_data[(hcryp->Size % 4U)-1U] = intermediate_data[(hcryp->Size % 4U)-1U] & 0xFFFF0000U;
      }
      if ((plength %4U)==3U)
      {
        intermediate_data[(hcryp->Size % 4U)-1U] = intermediate_data[(hcryp->Size % 4U)-1U] & 0xFFFFFF00U;
      }
      ;
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
        HAL_CRYP_ErrorCallback(hcryp);
      }
    }
  } /* End of CCM WKA*/  
  
  /* Process Unlocked */
  __HAL_UNLOCK(hcryp);     
}


/**
  * @brief  Handle CRYP hardware block Timeout when waiting for IFEM flag to be raised.
  * @param  hcryp: pointer to a CRYP_HandleTypeDef structure that contains
  *         the configuration information for CRYP module.      
  * @param  Timeout: Timeout duration.
  * @retval HAL status
  */
static HAL_StatusTypeDef CRYP_WaitOnIFEMFlag(CRYP_HandleTypeDef *hcryp, uint32_t Timeout)
{
  uint32_t tickstart = 0U;
  
  /* Get timeout */
  tickstart = HAL_GetTick();
  
  while(HAL_IS_BIT_CLR(hcryp->Instance->SR, CRYP_FLAG_IFEM))
  {
    /* Check for the Timeout */
    if(Timeout != HAL_MAX_DELAY)
    {
      if((Timeout == 0U)||((HAL_GetTick() - tickstart ) > Timeout))
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
  uint32_t tickstart = 0U;
  
  /* Get timeout */
  tickstart = HAL_GetTick();
  
  while(HAL_IS_BIT_SET(hcryp->Instance->SR, CRYP_FLAG_BUSY))
  {
    /* Check for the Timeout */
    if(Timeout != HAL_MAX_DELAY)
    {
      if((Timeout == 0U)||((HAL_GetTick() - tickstart ) > Timeout))
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
  uint32_t tickstart = 0U;
  
  /* Get timeout */
  tickstart = HAL_GetTick();
  
  while(HAL_IS_BIT_CLR(hcryp->Instance->SR, CRYP_FLAG_OFNE))
  {
    /* Check for the Timeout */
    if(Timeout != HAL_MAX_DELAY)
    {
      if((Timeout == 0U)||((HAL_GetTick() - tickstart ) > Timeout))
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

/**
  * @}
  */

#endif /* HAL_CRYP_MODULE_ENABLED */


/**
  * @}
  */
#endif /*  CRYP*/
/**
  * @}
  */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
