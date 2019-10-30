/**
  ******************************************************************************
  * @file    stm32f2xx_hal_cryp.c
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
         (##) The AlgoMode DES/ TDES Algorithm ECB/CBC or AES Algorithm ECB/CBC/CTR.
         (##) The initialization vector (counter). It is not used in ECB mode.
         (##) The key buffer used for encryption/decryption.

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
         (##) keys length Supported :
             (+++) for CRYP1 IP: 128-bit, 192-bit and 256-bit.

  *** Callback registration ***
  =============================================
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
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2016 STMicroelectronics.
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
#include "stm32f2xx_hal.h"

#if defined(CRYP)
#ifdef HAL_CRYP_MODULE_ENABLED
/** @addtogroup STM32F2xx_HAL_Driver
  * @{
  */

/** @addtogroup CRYP
  * @{
  */

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/** @addtogroup CRYP_Private_Defines
  * @{
  */

#define CRYP_TIMEOUT_KEYPREPARATION      82U         /*The latency of key preparation operation is 82 clock cycles.*/

#define  CRYP_PHASE_READY                0x00000001U /*!< CRYP peripheral is ready for initialization. */
#define  CRYP_PHASE_PROCESS              0x00000002U /*!< CRYP peripheral is in processing phase */

#define CRYP_OPERATINGMODE_ENCRYPT       0x00000000U             /*!< Encryption mode   */
#define CRYP_OPERATINGMODE_DECRYPT       CRYP_CR_ALGODIR         /*!< Decryption        */

/**
  * @}
  */


/* Private macro -------------------------------------------------------------*/
/** @addtogroup CRYP_Private_Macros
  * @{
  */

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
static void CRYP_SetKey( CRYP_HandleTypeDef *hcryp, uint32_t KeySize);
static void CRYP_AES_IT(CRYP_HandleTypeDef *hcryp);
static void CRYP_AES_ProcessData(CRYP_HandleTypeDef *hcrypt, uint32_t Timeout);
static HAL_StatusTypeDef CRYP_AES_Encrypt(CRYP_HandleTypeDef *hcryp, uint32_t Timeout);
static HAL_StatusTypeDef CRYP_AES_Decrypt(CRYP_HandleTypeDef *hcryp, uint32_t Timeout);
static HAL_StatusTypeDef CRYP_AES_Decrypt_IT(CRYP_HandleTypeDef *hcryp);
static HAL_StatusTypeDef CRYP_AES_Encrypt_IT(CRYP_HandleTypeDef *hcryp);
static HAL_StatusTypeDef CRYP_AES_Decrypt_DMA(CRYP_HandleTypeDef *hcryp);
static void CRYP_TDES_IT(CRYP_HandleTypeDef *hcryp);
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
                 ECB,CBC and CTR in AES Standard.
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

    hcryp->InCpltCallback  = HAL_CRYP_InCpltCallback;  /* Legacy weak  InCpltCallback  */
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
    hcryp->Init.DataType     = pConf->DataType;
    hcryp->Init.pKey         = pConf->pKey;
    hcryp->Init.Algorithm    = pConf->Algorithm;
    hcryp->Init.KeySize      = pConf->KeySize;
    hcryp->Init.pInitVect    = pConf->pInitVect;

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
  *         CRYP callabck is redirected to the weak predefined callback
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
  * @param  Size: Length of the plaintext buffer in word
  * @param  Output: Pointer to the output buffer(ciphertext)
  * @retval HAL status
  */
HAL_StatusTypeDef HAL_CRYP_Encrypt_IT(CRYP_HandleTypeDef *hcryp, uint32_t *Input, uint16_t Size, uint32_t *Output)
{
  uint32_t algo;
  HAL_StatusTypeDef status;

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

      status = HAL_OK;
      break;

    case CRYP_AES_ECB:
    case CRYP_AES_CBC:
    case CRYP_AES_CTR:

      status = CRYP_AES_Encrypt_IT(hcryp);
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
      CRYP_SetDMAConfig(hcryp, (uint32_t)( hcryp->pCrypInBuffPtr), (hcryp->Size/4U), (uint32_t)(hcryp->pCrypOutBuffPtr));

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
      CRYP_SetDMAConfig(hcryp, (uint32_t)( hcryp->pCrypInBuffPtr), (hcryp->Size/4U), (uint32_t)(hcryp->pCrypOutBuffPtr));
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
      CRYP_SetDMAConfig(hcryp, (uint32_t)( hcryp->pCrypInBuffPtr), (hcryp->Size/4U), (uint32_t)(hcryp->pCrypOutBuffPtr));
      break;

    case CRYP_AES_ECB:
    case CRYP_AES_CBC:
    case CRYP_AES_CTR:

      /* AES decryption */
      status = CRYP_AES_Decrypt_DMA(hcryp);
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
  
  if((__HAL_CRYP_GET_IT(hcryp, CRYP_IT_INI) != 0U) || (__HAL_CRYP_GET_IT(hcryp, CRYP_IT_OUTI) != 0U))
  {
    if ((hcryp->Init.Algorithm == CRYP_DES_ECB)|| (hcryp->Init.Algorithm == CRYP_DES_CBC) || (hcryp->Init.Algorithm == CRYP_TDES_ECB) || (hcryp->Init.Algorithm == CRYP_TDES_CBC))
    {
      CRYP_TDES_IT(hcryp); /* DES or TDES*/
    }
    else if((hcryp->Init.Algorithm == CRYP_AES_ECB) || (hcryp->Init.Algorithm == CRYP_AES_CBC) || (hcryp->Init.Algorithm == CRYP_AES_CTR))
    {
      CRYP_AES_IT(hcryp); /*AES*/
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
  * @retval HAL status
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

      if(hcryp->CrypInCount ==  (hcryp->Size/4U))
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
    if((__HAL_CRYP_GET_IT(hcryp, CRYP_IT_OUTI) != 0x0U)&& (__HAL_CRYP_GET_FLAG(hcryp, CRYP_FLAG_OUTRIS) != 0x0U))
    {
      /* Read the output block from the Output FIFO and put them in temporary Buffer then get CrypOutBuff from temporary buffer  */
      temp = hcryp->Instance->DOUT;
      *(uint32_t *)(hcryp->pCrypOutBuffPtr + (hcryp->CrypOutCount)) = temp;
      hcryp->CrypOutCount++;
      temp = hcryp->Instance->DOUT;
      *(uint32_t *)(hcryp->pCrypOutBuffPtr + (hcryp->CrypOutCount)) = temp;
      hcryp->CrypOutCount++;
      if(hcryp->CrypOutCount ==  (hcryp->Size/4U))
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
    hcryp->Instance->IV0LR = *(uint32_t*)(hcryp->Init.pInitVect);
    hcryp->Instance->IV0RR = *(uint32_t*)(hcryp->Init.pInitVect+1);
    hcryp->Instance->IV1LR = *(uint32_t*)(hcryp->Init.pInitVect+2);
    hcryp->Instance->IV1RR = *(uint32_t*)(hcryp->Init.pInitVect+3);
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
  uint16_t outcount;  /* Temporary CrypOutCount Value */

  /*  Key preparation for ECB/CBC */
  if (hcryp->Init.Algorithm != CRYP_AES_CTR)   /*ECB or CBC*/
  {
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
    hcryp->Instance->IV0LR = *(uint32_t*)(hcryp->Init.pInitVect);
    hcryp->Instance->IV0RR = *(uint32_t*)(hcryp->Init.pInitVect+1);
    hcryp->Instance->IV1LR = *(uint32_t*)(hcryp->Init.pInitVect+2);
    hcryp->Instance->IV1RR = *(uint32_t*)(hcryp->Init.pInitVect+3);
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
    CRYP_SetKey(hcryp, hcryp->Init.KeySize);
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
  if(hcryp->Size != 0U)
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
  }
  else  /*Algorithm CTR */
  {
    /*  Set the Key*/
    CRYP_SetKey(hcryp, hcryp->Init.KeySize);
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
  CRYP_HandleTypeDef* hcryp = (CRYP_HandleTypeDef*)((DMA_HandleTypeDef*)hdma)->Parent;


  /* Disable the DMA transfer for output FIFO */
  hcryp->Instance->DMACR &= (uint32_t)(~CRYP_DMACR_DOEN);

  /* Change the CRYP state to ready */
  hcryp->State = HAL_CRYP_STATE_READY;

  /* Process unlocked */
  __HAL_UNLOCK(hcryp);

    /* Disable CRYP */
  __HAL_CRYP_DISABLE(hcryp);
  
  
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
  if (HAL_DMA_Start_IT(hcryp->hdmain, inputaddr, (uint32_t)&hcryp->Instance->DIN, Size)!=HAL_OK)
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
  uint16_t incount;  /* Temporary CrypInCount Value */
  uint16_t outcount;  /* Temporary CrypOutCount Value */
  
  /*Temporary CrypOutCount Value*/
  incount = hcryp->CrypInCount; 

  if(((hcryp->Instance->SR & CRYP_FLAG_IFNF ) != 0x0U) && (incount < ((hcryp->Size)/4U)))
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

  if(((hcryp->Instance->SR & CRYP_FLAG_OFNE ) != 0x0U) && (outcount < ((hcryp->Size)/4U)))
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
  uint16_t incount; /* Temporary CrypInCount Value */
  uint16_t outcount;  /* Temporary CrypOutCount Value */

  if(hcryp->State == HAL_CRYP_STATE_BUSY)
  {
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
      if(hcryp->CrypInCount ==  (hcryp->Size/4U))
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
      if(hcryp->CrypOutCount ==  (hcryp->Size/4U))
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
static void CRYP_SetKey( CRYP_HandleTypeDef *hcryp, uint32_t KeySize)
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

  while(HAL_IS_BIT_SET(hcryp->Instance->SR, CRYP_FLAG_BUSY))
  {
    /* Check for the Timeout */
    if(Timeout != HAL_MAX_DELAY)
    {
      if(((HAL_GetTick() - tickstart ) > Timeout) || (Timeout == 0U))
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

  while(HAL_IS_BIT_CLR(hcryp->Instance->SR, CRYP_FLAG_OFNE))
  {
    /* Check for the Timeout */
    if(Timeout != HAL_MAX_DELAY)
    {
      if(((HAL_GetTick() - tickstart ) > Timeout) || (Timeout == 0U))
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
