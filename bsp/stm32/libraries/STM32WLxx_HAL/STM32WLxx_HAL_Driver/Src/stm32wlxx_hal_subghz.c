/*******************************************************************************
  * @file    stm32wlxx_hal_subghz.c
  * @author  MCD Application Team
  * @brief   SUBGHZ HAL module driver.
  *          This file provides firmware functions to manage the following
  *          functionalities of the SUBGHZ peripheral:
  *           + Initialization and de-initialization functions
  *           + IO operation functions
  *           + Peripheral State and Errors functions
  *
 @verbatim
 ==============================================================================
                       ##### How to use this driver #####
 ==============================================================================
 [..]
    The SUBGHZ HAL driver can be used as follows:

    (#) Declare a SUBGHZ_HandleTypeDef handle structure, for example:
        SUBGHZ_HandleTypeDef hUserSubghz;

    (#) Initialize the SUBGHZ low level resources by implementing the @ref HAL_SUBGHZ_MspInit() API:
        (##) PWR configuration
            (+++) Enable the SUBGHZSPI interface clock
            (+++) Enable wakeup signal of the Radio peripheral
        (##) NVIC configuration:
            (+++) Enable the NVIC Radio IRQ ITs for CPU1 (EXTI 44)
            (+++) Configure the Radio interrupt priority

    (#) Initialize the SUBGHZ handle and SUBGHZSPI SPI registers by calling the @ref HAL_SUBGHZ_Init(&hUserSubghz),
        configures also the low level Hardware (GPIO, CLOCK, NVIC...etc) by calling
        the customized @ref HAL_SUBGHZ_MspInit() API.

    (#) For SUBGHZ IO operations, polling operation modes is available within this driver :

    *** Polling mode IO operation      ***
    =====================================
    [..]
      (+) Set and execute a command in blocking mode using @ref HAL_SUBGHZ_ExecSetCmd()
      (+) Get a status blocking mode using @ref HAL_SUBGHZ_ExecGetCmd()
      (+) Write a Data Buffer in blocking mode using @ref HAL_SUBGHZ_WriteBuffer()
      (+) Read a Data Buffer  in blocking mode using @ref HAL_SUBGHZ_ReadBuffer()
      (+) Write Registers (more than 1 byte) in blocking mode using @ref HAL_SUBGHZ_WriteRegisters()
      (+) Read Registers (more than 1 byte) in blocking mode using @ref HAL_SUBGHZ_ReadRegisters()
      (+) Write Register (1 byte) in blocking mode using @ref HAL_SUBGHZ_WriteRegister()
      (+) Read Register (1 byte) in blocking mode using @ref HAL_SUBGHZ_ReadRegister()

    *** SUBGHZ HAL driver macros list ***
    =====================================
    [..]
      (+) @ref __HAL_SUBGHZ_RESET_HANDLE_STATE: Reset the SUBGHZ handle state

#if defined(GENERATOR_CALLBACK_REGISTERING_PRESENT)
     *** SUBGHZ Callback registration  ***
     =====================================

    [..]
     The compilation flag USE_HAL_SUBGHZ_REGISTER_CALLBACKS when set to 1
     allows the user to configure dynamically the driver callbacks.
     Use Functions @ref HAL_SUBGHZ_RegisterCallback() or @ref HAL_SUBGHZ_RegisterAddrCallback()
     to register an interrupt callback.

    [..]
     Function @ref HAL_SUBGHZ_RegisterCallback() allows to register following callbacks:
       (+) TxCpltCallback           : callback for Tx Completed.
       (+) RxCpltCallback           : callback for Rx Completed.
       (+) PreambleDetectedCallback : callback for Preamble detected.
       (+) SyncWordValidCallback    : callback for Synchro word valid.
       (+) HeaderValidCallback      : callback for Header valid.
       (+) HeaderErrorCallback      : callback for Header error.
       (+) CRCErrorCallback         : callback for CRC Error.
       (+) RxTxTimeoutCallback      : callback for Rx Tx Timeout.
       (+) MspInitCallback          : callback for Msp Init.
       (+) MspDeInitCallback        : callback for Msp DeInit.
     This function takes as parameters the HAL peripheral handle, the Callback ID
     and a pointer to the user callback function.
    [..]
     For specific callback CADStatusCallback use dedicated register callbacks :
     @ref HAL_SUBGHZ_RegisterCadStatusCallback().
    [..]
     Use function @ref HAL_SUBGHZ_UnRegisterCallback to reset a callback to the default
     weak function.
     @ref HAL_SUBGHZ_UnRegisterCallback takes as parameters the HAL peripheral handle,
     and the Callback ID.
     This function allows to reset following callbacks:
       (+) TxCpltCallback           : callback for Tx Completed.
       (+) RxCpltCallback           : callback for Rx Completed.
       (+) PreambleDetectedCallback : callback for Preamble detected.
       (+) SyncWordValidCallback    : callback for Synchro word valid.
       (+) HeaderValidCallback      : callback for Header valid.
       (+) HeaderErrorCallback      : callback for Header error.
       (+) CRCErrorCallback         : callback for CRC Error.
       (+) RxTxTimeoutCallback      : callback for Rx Tx Timeout.
       (+) MspInitCallback          : callback for Msp Init.
       (+) MspDeInitCallback        : callback for Msp DeInit.
    [..]
     For specific callback CADStatusCallback use dedicated register callbacks :
     @ref HAL_SUBGHZ_UnRegisterCadStatusCallback().
    [..]
     MspInit and MspDeInit functions are reset to the legacy weak functions in the
     @ref HAL_SUBGHZ_Init()/ @ref HAL_SUBGHZ_DeInit() only when these callbacks are null
     (not registered beforehand).
     If MspInit or MspDeInit are not null, the @ref HAL_SUBGHZ_Init()/ @ref HAL_SUBGHZ_DeInit()
     keep and use the user MspInit/MspDeInit callbacks (registered beforehand) whatever the state.

    [..]
     Callbacks for MspInit/MspDeInit functions can be registered/unregistered
     in @ref HAL_SUBGHZ_STATE_READY or @ref HAL_SUBGHZ_STATE_RESET state,
     thus registered (user) MspInit/DeInit callbacks can be used during the Init/DeInit.
     Then, the user first registers the MspInit/MspDeInit user callbacks
     using @ref HAL_SUBGHZ_RegisterCallback() before calling @ref HAL_SUBGHZ_DeInit()
     or @ref HAL_SUBGHZ_Init() function.

    [..]
     When the compilation flag USE_HAL_SUBGHZ_REGISTER_CALLBACKS is set to 0 or
     not defined, the callback registration feature is not available and all callbacks
     are set to the corresponding weak functions.
#endif
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2020 STMicroelectronics.
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
#include "stm32wlxx_hal.h"

/** @addtogroup STM32WLxx_HAL_Driver
  * @{
  */

/** @defgroup SUBGHZ SUBGHZ
  * @brief SUBGHZ HAL module driver
  * @{
  */
#ifdef HAL_SUBGHZ_MODULE_ENABLED

/* Private typedef -----------------------------------------------------------*/
/* Private defines -----------------------------------------------------------*/
/** @defgroup SUBGHZ_Private_Constants SUBGHZ Private Constants
  * @{
  */
#define SUBGHZ_DEFAULT_TIMEOUT     100U    /* HAL Timeout in ms               */
#define SUBGHZ_DUMMY_DATA          0xFFU   /* SUBGHZSPI Dummy Data use for Tx */
#define SUBGHZ_DEEP_SLEEP_ENABLE   1U      /* SUBGHZ Radio in Deep Sleep      */
#define SUBGHZ_DEEP_SLEEP_DISABLE  0U      /* SUBGHZ Radio not in Deep Sleep  */

/* SystemCoreClock dividers. Corresponding to time execution of while loop.   */
#define SUBGHZ_DEFAULT_LOOP_TIME   ((SystemCoreClock*28U)>>19U)
#define SUBGHZ_RFBUSY_LOOP_TIME    ((SystemCoreClock*24U)>>20U)
#define SUBGHZ_NSS_LOOP_TIME       ((SystemCoreClock*24U)>>16U)
/**
  * @}
  */

/* Private macros ------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
/** @defgroup SUBGHZ_Private_Functions SUBGHZ Private Functions
  * @{
  */
void              SUBGHZSPI_Init(uint32_t BaudratePrescaler);
void              SUBGHZSPI_DeInit(void);
HAL_StatusTypeDef SUBGHZSPI_Transmit(SUBGHZ_HandleTypeDef *hsubghz, uint8_t Data);
HAL_StatusTypeDef SUBGHZSPI_Receive(SUBGHZ_HandleTypeDef *hsubghz, uint8_t *pData);
HAL_StatusTypeDef SUBGHZ_WaitOnBusy(SUBGHZ_HandleTypeDef *hsubghz);
HAL_StatusTypeDef SUBGHZ_CheckDeviceReady(SUBGHZ_HandleTypeDef *hsubghz);
/**
  * @}
  */

/* Exported functions --------------------------------------------------------*/
/** @defgroup SUBGHZ_Exported_Functions SUBGHZ Exported Functions
  * @{
  */

/** @defgroup SUBGHZ_Exported_Functions_Group1 Initialization and de-initialization functions
  *  @brief    Initialization and Configuration functions
  *
@verbatim
 ===============================================================================
              ##### Initialization and de-initialization functions #####
 ===============================================================================
    [..]  This subsection provides a set of functions allowing to initialize and
          de-initialize the SUBGHZ peripheral:

      (+) User must implement HAL_SUBGHZ_MspInit() function in which he configures
          all related peripherals resources (CLOCK, GPIO, IT and NVIC ).

      (+) Call the function HAL_SUBGHZ_Init() to configure SUBGHZSPI peripheral
          and initialize SUBGHZ Handle.

      (+) Call the function HAL_SUBGHZ_DeInit() to restore the default configuration
          of the SUBGHZ peripheral.

@endverbatim
  * @{
  */

/**
  * @brief  Initialize the SUBGHZ according to the specified parameters
  *         in the SUBGHZ_HandleTypeDef and initialize the associated handle.
  * @param  hsubghz pointer to a SUBGHZ_HandleTypeDef structure that contains
  *         the handle information for SUBGHZ module.
  * @retval HAL status
  */
HAL_StatusTypeDef HAL_SUBGHZ_Init(SUBGHZ_HandleTypeDef *hsubghz)
{
  HAL_StatusTypeDef status;
  __IO uint32_t count;

  /* Check the hsubghz handle allocation */
  if (hsubghz == NULL)
  {
    status = HAL_ERROR;
    return status;
  }
  else
  {
    status = HAL_OK;
  }

  assert_param(IS_SUBGHZSPI_BAUDRATE_PRESCALER(hsubghz->Init.BaudratePrescaler));

  if (hsubghz->State == HAL_SUBGHZ_STATE_RESET)
  {
    /* Allocate lock resource and initialize it */
    hsubghz->Lock = HAL_UNLOCKED;

#if (USE_HAL_SUBGHZ_REGISTER_CALLBACKS == 1)
    /* Init the SUBGHZ Legacy weak Callback settings */
    hsubghz->TxCpltCallback              = HAL_SUBGHZ_TxCpltCallback;
    hsubghz->RxCpltCallback              = HAL_SUBGHZ_RxCpltCallback;
    hsubghz->PreambleDetectedCallback    = HAL_SUBGHZ_PreambleDetectedCallback;
    hsubghz->SyncWordValidCallback       = HAL_SUBGHZ_SyncWordValidCallback;
    hsubghz->HeaderValidCallback         = HAL_SUBGHZ_HeaderValidCallback;
    hsubghz->HeaderErrorCallback         = HAL_SUBGHZ_HeaderErrorCallback;
    hsubghz->CRCErrorCallback            = HAL_SUBGHZ_CRCErrorCallback;
    hsubghz->CADStatusCallback           = HAL_SUBGHZ_CADStatusCallback;
    hsubghz->RxTxTimeoutCallback         = HAL_SUBGHZ_RxTxTimeoutCallback;

    if (hsubghz->MspInitCallback == NULL)
    {
      hsubghz->MspInitCallback = HAL_SUBGHZ_MspInit; /* Legacy weak MspInit  */
    }

    /* Init the low level hardware : GPIO, CLOCK, NVIC... */
    hsubghz->MspInitCallback(hsubghz);
#else
    /* Init the low level hardware : GPIO, CLOCK, NVIC... */
    HAL_SUBGHZ_MspInit(hsubghz);
#endif /* USE_HAL_ SUBGHZ_REGISTER_CALLBACKS */
  }

  hsubghz->State = HAL_SUBGHZ_STATE_BUSY;

  /* De-asserts the reset signal of the Radio peripheral */
  LL_RCC_RF_DisableReset();

  /* Verify that Radio in reset status flag is set */
  count  = SUBGHZ_DEFAULT_TIMEOUT * SUBGHZ_DEFAULT_LOOP_TIME;

  do
  {
    if (count == 0U)
    {
      status  = HAL_ERROR;
      hsubghz->ErrorCode = HAL_SUBGHZ_ERROR_TIMEOUT;
      break;
    }
    count--;
  } while (LL_RCC_IsRFUnderReset() != 0UL);

  /* Asserts the reset signal of the Radio peripheral */
  LL_PWR_UnselectSUBGHZSPI_NSS();

#if defined(CM0PLUS)
  /* Enable EXTI 44 : Radio IRQ ITs for CPU2 */
  LL_C2_EXTI_EnableIT_32_63(LL_EXTI_LINE_44);

  /* Enable wakeup signal of the Radio peripheral */
  LL_C2_PWR_SetRadioBusyTrigger(LL_PWR_RADIO_BUSY_TRIGGER_WU_IT);
#else
  /* Enable EXTI 44 : Radio IRQ ITs for CPU1 */
  LL_EXTI_EnableIT_32_63(LL_EXTI_LINE_44);

  /* Enable wakeup signal of the Radio peripheral */
  LL_PWR_SetRadioBusyTrigger(LL_PWR_RADIO_BUSY_TRIGGER_WU_IT);
#endif /* CM0PLUS */

  /* Clear Pending Flag */
  LL_PWR_ClearFlag_RFBUSY();

  if (status == HAL_OK)
  {
    /* Initialize SUBGHZSPI Peripheral */
    SUBGHZSPI_Init(hsubghz->Init.BaudratePrescaler);

    hsubghz->DeepSleep = SUBGHZ_DEEP_SLEEP_ENABLE;
    hsubghz->ErrorCode = HAL_SUBGHZ_ERROR_NONE;
  }
  hsubghz->State     = HAL_SUBGHZ_STATE_READY;

  return status;
}

/**
  * @brief  De-Initialize the SUBGHZ peripheral.
  * @param  hsubghz pointer to a SUBGHZ_HandleTypeDef structure that contains
  *         the handle information for SUBGHZ module.
  * @retval HAL status
  */
HAL_StatusTypeDef HAL_SUBGHZ_DeInit(SUBGHZ_HandleTypeDef *hsubghz)
{
  HAL_StatusTypeDef status;
  __IO uint32_t count;

  /* Check the SUBGHZ handle allocation */
  if (hsubghz == NULL)
  {
    status = HAL_ERROR;
    return status;
  }
  else
  {
    status = HAL_OK;
  }

  hsubghz->State = HAL_SUBGHZ_STATE_BUSY;

  /* DeInitialize SUBGHZSPI Peripheral */
  SUBGHZSPI_DeInit();

#if (USE_HAL_SUBGHZ_REGISTER_CALLBACKS == 1)
  if (hsubghz->MspDeInitCallback == NULL)
  {
    hsubghz->MspDeInitCallback = HAL_SUBGHZ_MspDeInit; /* Legacy weak MspDeInit  */
  }

  /* DeInit the low level hardware: GPIO, CLOCK, NVIC... */
  hsubghz->MspDeInitCallback(hsubghz);
#else
  /* DeInit the low level hardware: GPIO, CLOCK, NVIC... */
  HAL_SUBGHZ_MspDeInit(hsubghz);
#endif /* USE_HAL_SUBGHZ_REGISTER_CALLBACKS */

#if defined(CM0PLUS)
  /* Disable EXTI 44 : Radio IRQ ITs for CPU2 */
  LL_C2_EXTI_DisableIT_32_63(LL_EXTI_LINE_44);

  /* Disable wakeup signal of the Radio peripheral */
  LL_C2_PWR_SetRadioBusyTrigger(LL_PWR_RADIO_BUSY_TRIGGER_NONE);
#else
  /* Disable EXTI 44 : Radio IRQ ITs for CPU1 */
  LL_EXTI_DisableIT_32_63(LL_EXTI_LINE_44);

  /* Disable wakeup signal of the Radio peripheral */
  LL_PWR_SetRadioBusyTrigger(LL_PWR_RADIO_BUSY_TRIGGER_NONE);
#endif /* CM0PLUS */

  /* Clear Pending Flag */
  LL_PWR_ClearFlag_RFBUSY();

  /* Re-asserts the reset signal of the Radio peripheral */
  LL_RCC_RF_EnableReset();

  /* Verify that Radio in reset status flag is set */
  count  = SUBGHZ_DEFAULT_TIMEOUT * SUBGHZ_DEFAULT_LOOP_TIME;

  do
  {
    if (count == 0U)
    {
      status  = HAL_ERROR;
      hsubghz->ErrorCode = HAL_SUBGHZ_ERROR_TIMEOUT;
      break;
    }
    count--;
  } while (LL_RCC_IsRFUnderReset() != 1UL);

  hsubghz->ErrorCode = HAL_SUBGHZ_ERROR_NONE;
  hsubghz->State     = HAL_SUBGHZ_STATE_RESET;

  /* Release Lock */
  __HAL_UNLOCK(hsubghz);

  return status;
}

/**
  * @brief  Initialize the SUBGHZ MSP.
  * @param  hsubghz pointer to a SUBGHZ_HandleTypeDef structure that contains
  *         the handle information for SUBGHZ module.
  * @retval None
  */
__weak void HAL_SUBGHZ_MspInit(SUBGHZ_HandleTypeDef *hsubghz)
{
  /* NOTE : This function should not be modified, when the callback is needed,
            the HAL_SUBGHZ_MspInit should be implemented in the user file
   */

  /* Prevent unused argument(s) compilation warning */
  UNUSED(hsubghz);
}

/**
  * @brief  De-Initialize the SUBGHZ MSP.
  * @param  hsubghz pointer to a SUBGHZ_HandleTypeDef structure that contains
  *         the handle information for SUBGHZ module.
  * @retval None
  */
__weak void HAL_SUBGHZ_MspDeInit(SUBGHZ_HandleTypeDef *hsubghz)
{
  /* NOTE : This function should not be modified, when the callback is needed,
            the HAL_SUBGHZ_MspDeInit should be implemented in the user file
   */

  /* Prevent unused argument(s) compilation warning */
  UNUSED(hsubghz);
}

#if (USE_HAL_SUBGHZ_REGISTER_CALLBACKS == 1)
/**
  * @brief  Register a User SUBGHZ Callback
  *         To be used instead of the weak predefined callback
  * @param  hsubghz pointer to a SUBGHZ_HandleTypeDef structure that contains
  *         the configuration information for the specified SUBGHZ.
  * @param  CallbackID ID of the callback to be registered
  * @param  pCallback pointer to the Callback function
  * @retval HAL status
  */
HAL_StatusTypeDef HAL_SUBGHZ_RegisterCallback(SUBGHZ_HandleTypeDef *hsubghz,
                                              HAL_SUBGHZ_CallbackIDTypeDef CallbackID,
                                              pSUBGHZ_CallbackTypeDef pCallback)
{
  HAL_StatusTypeDef status = HAL_OK;

  if (pCallback == NULL)
  {
    /* Update the error code */
    hsubghz->ErrorCode |= HAL_SUBGHZ_ERROR_INVALID_CALLBACK;

    return HAL_ERROR;
  }

  /* Process locked */
  __HAL_LOCK(hsubghz);

  if (HAL_SUBGHZ_STATE_READY == hsubghz->State)
  {
    switch (CallbackID)
    {
      case HAL_SUBGHZ_TX_COMPLETE_CB_ID :
        hsubghz->TxCpltCallback = pCallback;
        break;

      case HAL_SUBGHZ_RX_COMPLETE_CB_ID :
        hsubghz->RxCpltCallback = pCallback;
        break;

      case HAL_SUBGHZ_PREAMBLE_DETECTED_CB_ID :
        hsubghz->PreambleDetectedCallback = pCallback;
        break;

      case HAL_SUBGHZ_SYNCWORD_VALID_CB_ID :
        hsubghz->SyncWordValidCallback = pCallback;
        break;

      case HAL_SUBGHZ_HEADER_VALID_CB_ID :
        hsubghz->HeaderValidCallback = pCallback;
        break;

      case HAL_SUBGHZ_HEADER_ERROR_CB_ID :
        hsubghz->HeaderErrorCallback = pCallback;
        break;

      case HAL_SUBGHZ_CRC_ERROR_CB_ID :
        hsubghz->CRCErrorCallback = pCallback;
        break;

      case HAL_SUBGHZ_RX_TX_TIMEOUT_CB_ID :
        hsubghz->RxTxTimeoutCallback = pCallback;
        break;

      case HAL_SUBGHZ_MSPINIT_CB_ID :
        hsubghz->MspInitCallback = pCallback;
        break;

      case HAL_SUBGHZ_MSPDEINIT_CB_ID :
        hsubghz->MspDeInitCallback = pCallback;
        break;

      default :
        /* Update the error code */
        hsubghz->ErrorCode = HAL_SUBGHZ_ERROR_INVALID_CALLBACK;

        /* Return error status */
        status =  HAL_ERROR;
        break;
    }
  }
  else if (HAL_SUBGHZ_STATE_RESET == hsubghz->State)
  {
    switch (CallbackID)
    {
      case HAL_SUBGHZ_MSPINIT_CB_ID :
        hsubghz->MspInitCallback = pCallback;
        break;

      case HAL_SUBGHZ_MSPDEINIT_CB_ID :
        hsubghz->MspDeInitCallback = pCallback;
        break;

      default :
        /* Update the error code */
        hsubghz->ErrorCode = HAL_SUBGHZ_ERROR_INVALID_CALLBACK;

        /* Return error status */
        status =  HAL_ERROR;
        break;
    }
  }
  else
  {
    /* Update the error code */
    hsubghz->ErrorCode = HAL_SUBGHZ_ERROR_INVALID_CALLBACK;

    /* Return error status */
    status =  HAL_ERROR;
  }

  /* Release Lock */
  __HAL_UNLOCK(hsubghz);

  return status;
}

/**
  * @brief  Unregister an SUBGHZ Callback
  *         SUBGHZ callback is redirected to the weak predefined callback
  * @param  hsubghz pointer to a SUBGHZ_HandleTypeDef structure that contains
  *         the configuration information for the specified SUBGHZ.
  * @param  CallbackID ID of the callback to be unregistered
  * @retval HAL status
  */
HAL_StatusTypeDef HAL_SUBGHZ_UnRegisterCallback(SUBGHZ_HandleTypeDef *hsubghz,
                                                HAL_SUBGHZ_CallbackIDTypeDef CallbackID)
{
  HAL_StatusTypeDef status = HAL_OK;

  /* Process locked */
  __HAL_LOCK(hsubghz);

  if (HAL_SUBGHZ_STATE_READY == hsubghz->State)
  {
    /* call legacy weak callback function */
    switch (CallbackID)
    {
      case HAL_SUBGHZ_TX_COMPLETE_CB_ID :
        hsubghz->TxCpltCallback = HAL_SUBGHZ_TxCpltCallback;
        break;

      case HAL_SUBGHZ_RX_COMPLETE_CB_ID :
        hsubghz->RxCpltCallback = HAL_SUBGHZ_RxCpltCallback;
        break;

      case HAL_SUBGHZ_PREAMBLE_DETECTED_CB_ID :
        hsubghz->PreambleDetectedCallback = HAL_SUBGHZ_PreambleDetectedCallback;
        break;

      case HAL_SUBGHZ_SYNCWORD_VALID_CB_ID :
        hsubghz->SyncWordValidCallback = HAL_SUBGHZ_SyncWordValidCallback;
        break;

      case HAL_SUBGHZ_HEADER_VALID_CB_ID :
        hsubghz->HeaderValidCallback = HAL_SUBGHZ_HeaderValidCallback;
        break;

      case HAL_SUBGHZ_HEADER_ERROR_CB_ID :
        hsubghz->HeaderErrorCallback = HAL_SUBGHZ_HeaderErrorCallback;
        break;

      case HAL_SUBGHZ_CRC_ERROR_CB_ID :
        hsubghz->CRCErrorCallback = HAL_SUBGHZ_CRCErrorCallback;
        break;

      case HAL_SUBGHZ_RX_TX_TIMEOUT_CB_ID :
        hsubghz->RxTxTimeoutCallback = HAL_SUBGHZ_RxTxTimeoutCallback;
        break;

      case HAL_SUBGHZ_MSPINIT_CB_ID :
        hsubghz->MspInitCallback = HAL_SUBGHZ_MspInit;
        break;

      case HAL_SUBGHZ_MSPDEINIT_CB_ID :
        hsubghz->MspDeInitCallback = HAL_SUBGHZ_MspDeInit;
        break;

      default :
        /* Update the error code */
        hsubghz->ErrorCode = HAL_SUBGHZ_ERROR_INVALID_CALLBACK;

        /* Return error status */
        status =  HAL_ERROR;
        break;
    }
  }
  else if (HAL_SUBGHZ_STATE_RESET == hsubghz->State)
  {
    switch (CallbackID)
    {
      case HAL_SUBGHZ_MSPINIT_CB_ID :
        hsubghz->MspInitCallback = HAL_SUBGHZ_MspInit;
        break;

      case HAL_SUBGHZ_MSPDEINIT_CB_ID :
        hsubghz->MspDeInitCallback = HAL_SUBGHZ_MspDeInit;
        break;

      default :
        /* Update the error code */
        hsubghz->ErrorCode = HAL_SUBGHZ_ERROR_INVALID_CALLBACK;

        /* Return error status */
        status =  HAL_ERROR;
        break;
    }
  }
  else
  {
    /* Update the error code */
    hsubghz->ErrorCode = HAL_SUBGHZ_ERROR_INVALID_CALLBACK;

    /* Return error status */
    status =  HAL_ERROR;
  }

  /* Release Lock */
  __HAL_UNLOCK(hsubghz);

  return status;
}

/**
  * @brief  Register the channel activity detection status SUBGHZ Callback
  *         To be used instead of the weak HAL_SUBGHZ_AddrCallback() predefined callback
  * @param  hsubghz Pointer to a SUBGHZ_HandleTypeDef structure that contains
  *                the configuration information for the specified SUBGHZ.
  * @param  pCallback pointer to the CAD Status Callback function
  * @retval HAL status
  */
HAL_StatusTypeDef HAL_SUBGHZ_RegisterCadStatusCallback(SUBGHZ_HandleTypeDef *hsubghz,
                                                       pSUBGHZ_CadStatusCallbackTypeDef pCallback)
{
  HAL_StatusTypeDef status = HAL_OK;

  if (pCallback == NULL)
  {
    /* Update the error code */
    hsubghz->ErrorCode = HAL_SUBGHZ_ERROR_INVALID_CALLBACK;

    return HAL_ERROR;
  }
  /* Process locked */
  __HAL_LOCK(hsubghz);

  if (HAL_SUBGHZ_STATE_READY == hsubghz->State)
  {
    hsubghz->CADStatusCallback = pCallback;
  }
  else
  {
    /* Update the error code */
    hsubghz->ErrorCode = HAL_SUBGHZ_ERROR_INVALID_CALLBACK;

    /* Return error status */
    status =  HAL_ERROR;
  }

  /* Release Lock */
  __HAL_UNLOCK(hsubghz);
  return status;
}

/**
  * @brief  UnRegister the channel activity detection status SUBGHZ Callback
  * @param  hsubghz Pointer to a SUBGHZ_HandleTypeDef structure that contains
  *                the configuration information for the specified SUBGHZ.
  * @retval HAL status
  */
HAL_StatusTypeDef HAL_SUBGHZ_UnRegisterCadStatusCallback(SUBGHZ_HandleTypeDef *hsubghz)
{
  HAL_StatusTypeDef status = HAL_OK;

  /* Process locked */
  __HAL_LOCK(hsubghz);

  if (HAL_SUBGHZ_STATE_READY == hsubghz->State)
  {
    hsubghz->CADStatusCallback = HAL_SUBGHZ_CADStatusCallback; /* Legacy weak AddrCallback  */
  }
  else
  {
    /* Update the error code */
    hsubghz->ErrorCode = HAL_SUBGHZ_ERROR_INVALID_CALLBACK;

    /* Return error status */
    status =  HAL_ERROR;
  }

  /* Release Lock */
  __HAL_UNLOCK(hsubghz);
  return status;
}
#endif /* USE_HAL_SUBGHZ_REGISTER_CALLBACKS */
/**
  * @}
  */

/** @defgroup SUBGHZ_Exported_Functions_Group2 IO operation functions
  *  @brief   Data transfers functions
  *
@verbatim
  ==============================================================================
                      ##### IO operation functions #####
 ===============================================================================
 [..]
    This subsection provides a set of functions allowing to manage the SUBGHZ
    data transfers.

    [..] The SUBGHZ supports Read and Write operation:

    (#) There are four modes of transfer:
       (++) Set operation: The Set Command operation is performed in polling mode.
            The HAL status of command processing is returned by the same function
            after finishing transfer.
       (++) Get operation: The Get Status operation is performed using polling mode
            These API update buffer in parameter to retrieve status of command.
            These API return the HAL status
       (++) Write operation: The write operation is performed in polling mode.
            The HAL status of all data processing is returned by the same function
            after finishing transfer.
       (++) Read operation: The read operation is performed using polling mode
            These APIs return the HAL status.

    (#) Blocking mode functions are :
        (++) HAL_SUBGHZ_ExecSetCmd(
        (++) HAL_SUBGHZ_ExecGetCmd()
        (++) HAL_SUBGHZ_WriteBuffer()
        (++) HAL_SUBGHZ_ReadBuffer()
        (++) HAL_SUBGHZ_WriteRegisters()
        (++) HAL_SUBGHZ_ReadRegisters()
        (++) HAL_SUBGHZ_WriteRegister()
        (++) HAL_SUBGHZ_ReadRegister()

@endverbatim
  * @{
  */

/**
  * @brief  Write data buffer at an Address to configurate the peripheral
  * @param  hsubghz pointer to a SUBGHZ_HandleTypeDef structure that contains
  *         the configuration information for the specified SUBGHZ.
  * @param  Address register to configurate
  * @param  pBuffer pointer to a data buffer
  * @param  Size    amount of data to be sent
  * @retval HAL status
  */
HAL_StatusTypeDef HAL_SUBGHZ_WriteRegisters(SUBGHZ_HandleTypeDef *hsubghz,
                                            uint16_t Address,
                                            uint8_t *pBuffer,
                                            uint16_t Size)
{
  HAL_StatusTypeDef status;

  if (hsubghz->State == HAL_SUBGHZ_STATE_READY)
  {
    /* Process Locked */
    __HAL_LOCK(hsubghz);

    hsubghz->State = HAL_SUBGHZ_STATE_BUSY;

    (void)SUBGHZ_CheckDeviceReady(hsubghz);

    /* NSS = 0 */
    LL_PWR_SelectSUBGHZSPI_NSS();

    (void)SUBGHZSPI_Transmit(hsubghz, SUBGHZ_RADIO_WRITE_REGISTER);
    (void)SUBGHZSPI_Transmit(hsubghz, (uint8_t)((Address & 0xFF00U) >> 8U));
    (void)SUBGHZSPI_Transmit(hsubghz, (uint8_t)(Address & 0x00FFU));

    for (uint16_t i = 0U; i < Size; i++)
    {
      (void)SUBGHZSPI_Transmit(hsubghz, pBuffer[i]);
    }

    /* NSS = 1 */
    LL_PWR_UnselectSUBGHZSPI_NSS();

    (void)SUBGHZ_WaitOnBusy(hsubghz);

    if (hsubghz->ErrorCode != HAL_SUBGHZ_ERROR_NONE)
    {
      status = HAL_ERROR;
    }
    else
    {
      status = HAL_OK;
    }

    hsubghz->State = HAL_SUBGHZ_STATE_READY;

    /* Process Unlocked */
    __HAL_UNLOCK(hsubghz);

    return status;
  }
  else
  {
    return HAL_BUSY;
  }
}

/**
  * @brief  Read data register at an Address in the peripheral
  * @param  hsubghz pointer to a SUBGHZ_HandleTypeDef structure that contains
  *         the configuration information for the specified SUBGHZ.
  * @param  Address register to configurate
  * @param  pBuffer pointer to a data buffer
  * @param  Size    amount of data to be sent
  * @retval HAL status
  */
HAL_StatusTypeDef HAL_SUBGHZ_ReadRegisters(SUBGHZ_HandleTypeDef *hsubghz,
                                           uint16_t Address,
                                           uint8_t *pBuffer,
                                           uint16_t Size)
{
  HAL_StatusTypeDef status;
  uint8_t *pData = pBuffer;

  if (hsubghz->State == HAL_SUBGHZ_STATE_READY)
  {
    /* Process Locked */
    __HAL_LOCK(hsubghz);

    (void)SUBGHZ_CheckDeviceReady(hsubghz);

    /* NSS = 0 */
    LL_PWR_SelectSUBGHZSPI_NSS();

    (void)SUBGHZSPI_Transmit(hsubghz, SUBGHZ_RADIO_READ_REGISTER);
    (void)SUBGHZSPI_Transmit(hsubghz, (uint8_t)((Address & 0xFF00U) >> 8U));
    (void)SUBGHZSPI_Transmit(hsubghz, (uint8_t)(Address & 0x00FFU));
    (void)SUBGHZSPI_Transmit(hsubghz, 0U);

    for (uint16_t i = 0U; i < Size; i++)
    {
      (void)SUBGHZSPI_Receive(hsubghz, (pData));
      pData++;
    }

    /* NSS = 1 */
    LL_PWR_UnselectSUBGHZSPI_NSS();

    (void)SUBGHZ_WaitOnBusy(hsubghz);

    if (hsubghz->ErrorCode != HAL_SUBGHZ_ERROR_NONE)
    {
      status = HAL_ERROR;
    }
    else
    {
      status = HAL_OK;
    }

    hsubghz->State = HAL_SUBGHZ_STATE_READY;

    /* Process Unlocked */
    __HAL_UNLOCK(hsubghz);

    return status;
  }
  else
  {
    return HAL_BUSY;
  }
}

/**
  * @brief  Write one data at an Address to configurate the peripheral
  * @param  hsubghz pointer to a SUBGHZ_HandleTypeDef structure that contains
  *         the configuration information for the specified SUBGHZ.
  * @param  Address register to configurate
  * @param  Value data
  * @retval HAL status
  */
HAL_StatusTypeDef HAL_SUBGHZ_WriteRegister(SUBGHZ_HandleTypeDef *hsubghz,
                                           uint16_t Address,
                                           uint8_t Value)
{
  return (HAL_SUBGHZ_WriteRegisters(hsubghz, Address, &Value, 1U));
}


/**
  * @brief  Read data register at an Address in the peripheral
  * @param  hsubghz pointer to a SUBGHZ_HandleTypeDef structure that contains
  *         the configuration information for the specified SUBGHZ.
  * @param  Address register to configurate
  * @param  pValue pointer to a data
  * @retval HAL status
  */
HAL_StatusTypeDef HAL_SUBGHZ_ReadRegister(SUBGHZ_HandleTypeDef *hsubghz,
                                          uint16_t Address,
                                          uint8_t *pValue)
{
  return (HAL_SUBGHZ_ReadRegisters(hsubghz, Address, pValue, 1U));
}


/**
  * @brief  Send a command to configure the peripheral
  * @param  hsubghz pointer to a SUBGHZ_HandleTypeDef structure that contains
  *         the configuration information for the specified SUBGHZ.
  * @param  Command configuration for peripheral
  * @param  pBuffer pointer to a data buffer
  * @param  Size    amount of data to be sent
  * @retval HAL status
  */
HAL_StatusTypeDef HAL_SUBGHZ_ExecSetCmd(SUBGHZ_HandleTypeDef *hsubghz,
                                        SUBGHZ_RadioSetCmd_t Command,
                                        uint8_t *pBuffer,
                                        uint16_t Size)
{
  HAL_StatusTypeDef status;

  /* LORA Modulation not available on STM32WLx4xx devices */
  assert_param(IS_SUBGHZ_MODULATION_SUPPORTED(Command, pBuffer[0]));

  if (hsubghz->State == HAL_SUBGHZ_STATE_READY)
  {
    /* Process Locked */
    __HAL_LOCK(hsubghz);

    /* Need to wakeup Radio if already in Sleep at startup */
    (void)SUBGHZ_CheckDeviceReady(hsubghz);

    if ((Command == RADIO_SET_SLEEP) || (Command == RADIO_SET_RXDUTYCYCLE))
    {
      hsubghz->DeepSleep = SUBGHZ_DEEP_SLEEP_ENABLE;
    }
    else
    {
      hsubghz->DeepSleep = SUBGHZ_DEEP_SLEEP_DISABLE;
    }

    /* NSS = 0 */
    LL_PWR_SelectSUBGHZSPI_NSS();

    (void)SUBGHZSPI_Transmit(hsubghz, (uint8_t)Command);

    for (uint16_t i = 0U; i < Size; i++)
    {
      (void)SUBGHZSPI_Transmit(hsubghz, pBuffer[i]);
    }

    /* NSS = 1 */
    LL_PWR_UnselectSUBGHZSPI_NSS();

    if (Command != RADIO_SET_SLEEP)
    {
      (void)SUBGHZ_WaitOnBusy(hsubghz);
    }

    if (hsubghz->ErrorCode != HAL_SUBGHZ_ERROR_NONE)
    {
      status = HAL_ERROR;
    }
    else
    {
      status = HAL_OK;
    }

    hsubghz->State = HAL_SUBGHZ_STATE_READY;

    /* Process Unlocked */
    __HAL_UNLOCK(hsubghz);

    return status;
  }
  else
  {
    return HAL_BUSY;
  }
}

/**
  * @brief  Retrieve a status from the peripheral
  * @param  hsubghz pointer to a SUBGHZ_HandleTypeDef structure that contains
  *         the configuration information for the specified SUBGHZ.
  * @param  Command configuration for peripheral
  * @param  pBuffer pointer to a data buffer
  * @param  Size    amount of data to be sent
  * @retval HAL status
  */
HAL_StatusTypeDef HAL_SUBGHZ_ExecGetCmd(SUBGHZ_HandleTypeDef *hsubghz,
                                        SUBGHZ_RadioGetCmd_t Command,
                                        uint8_t *pBuffer,
                                        uint16_t Size)
{
  HAL_StatusTypeDef status;
  uint8_t *pData = pBuffer;

  if (hsubghz->State == HAL_SUBGHZ_STATE_READY)
  {
    /* Process Locked */
    __HAL_LOCK(hsubghz);

    (void)SUBGHZ_CheckDeviceReady(hsubghz);

    /* NSS = 0 */
    LL_PWR_SelectSUBGHZSPI_NSS();

    (void)SUBGHZSPI_Transmit(hsubghz, (uint8_t)Command);

    /* Use to flush the Status (First byte) receive from SUBGHZ as not use */
    (void)SUBGHZSPI_Transmit(hsubghz, 0x00U);

    for (uint16_t i = 0U; i < Size; i++)
    {
      (void)SUBGHZSPI_Receive(hsubghz, (pData));
      pData++;
    }

    /* NSS = 1 */
    LL_PWR_UnselectSUBGHZSPI_NSS();

    (void)SUBGHZ_WaitOnBusy(hsubghz);

    if (hsubghz->ErrorCode != HAL_SUBGHZ_ERROR_NONE)
    {
      status = HAL_ERROR;
    }
    else
    {
      status = HAL_OK;
    }

    hsubghz->State = HAL_SUBGHZ_STATE_READY;

    /* Process Unlocked */
    __HAL_UNLOCK(hsubghz);

    return status;
  }
  else
  {
    return HAL_BUSY;
  }
}

/**
  * @brief  Write data buffer inside payload of peripheral
  * @param  hsubghz pointer to a SUBGHZ_HandleTypeDef structure that contains
  *         the configuration information for the specified SUBGHZ.
  * @param  Offset  Offset inside payload
  * @param  pBuffer pointer to a data buffer
  * @param  Size    amount of data to be sent
  * @retval HAL status
  */
HAL_StatusTypeDef HAL_SUBGHZ_WriteBuffer(SUBGHZ_HandleTypeDef *hsubghz,
                                         uint8_t Offset,
                                         uint8_t *pBuffer,
                                         uint16_t Size)
{
  HAL_StatusTypeDef status;

  if (hsubghz->State == HAL_SUBGHZ_STATE_READY)
  {
    /* Process Locked */
    __HAL_LOCK(hsubghz);

    (void)SUBGHZ_CheckDeviceReady(hsubghz);

    /* NSS = 0 */
    LL_PWR_SelectSUBGHZSPI_NSS();

    (void)SUBGHZSPI_Transmit(hsubghz, SUBGHZ_RADIO_WRITE_BUFFER);
    (void)SUBGHZSPI_Transmit(hsubghz, Offset);

    for (uint16_t i = 0U; i < Size; i++)
    {
      (void)SUBGHZSPI_Transmit(hsubghz, pBuffer[i]);
    }
    /* NSS = 1 */
    LL_PWR_UnselectSUBGHZSPI_NSS();

    (void)SUBGHZ_WaitOnBusy(hsubghz);

    if (hsubghz->ErrorCode != HAL_SUBGHZ_ERROR_NONE)
    {
      status = HAL_ERROR;
    }
    else
    {
      status = HAL_OK;
    }

    hsubghz->State = HAL_SUBGHZ_STATE_READY;

    /* Process Unlocked */
    __HAL_UNLOCK(hsubghz);

    return status;
  }
  else
  {
    return HAL_BUSY;
  }
}

/**
  * @brief  Read data buffer inside payload of peripheral
  * @param  hsubghz pointer to a SUBGHZ_HandleTypeDef structure that contains
  *         the configuration information for the specified SUBGHZ.
  * @param  Offset  Offset inside payload
  * @param  pBuffer pointer to a data buffer
  * @param  Size    amount of data to be sent
  * @retval HAL status
  */
HAL_StatusTypeDef HAL_SUBGHZ_ReadBuffer(SUBGHZ_HandleTypeDef *hsubghz,
                                        uint8_t Offset,
                                        uint8_t *pBuffer,
                                        uint16_t Size)
{
  HAL_StatusTypeDef status;
  uint8_t *pData = pBuffer;

  if (hsubghz->State == HAL_SUBGHZ_STATE_READY)
  {
    /* Process Locked */
    __HAL_LOCK(hsubghz);

    (void)SUBGHZ_CheckDeviceReady(hsubghz);

    /* NSS = 0 */
    LL_PWR_SelectSUBGHZSPI_NSS();

    (void)SUBGHZSPI_Transmit(hsubghz, SUBGHZ_RADIO_READ_BUFFER);
    (void)SUBGHZSPI_Transmit(hsubghz, Offset);
    (void)SUBGHZSPI_Transmit(hsubghz, 0x00U);

    for (uint16_t i = 0U; i < Size; i++)
    {
      (void)SUBGHZSPI_Receive(hsubghz, (pData));
      pData++;
    }

    /* NSS = 1 */
    LL_PWR_UnselectSUBGHZSPI_NSS();

    (void)SUBGHZ_WaitOnBusy(hsubghz);

    if (hsubghz->ErrorCode != HAL_SUBGHZ_ERROR_NONE)
    {
      status = HAL_ERROR;
    }
    else
    {
      status = HAL_OK;
    }

    hsubghz->State = HAL_SUBGHZ_STATE_READY;

    /* Process Unlocked */
    __HAL_UNLOCK(hsubghz);

    return status;
  }
  else
  {
    return HAL_BUSY;
  }
}

/**
  * @brief  Handle SUBGHZ interrupt request.
  * @param  hsubghz pointer to a SUBGHZ_HandleTypeDef structure that contains
  *               the configuration information for the specified SUBGHZ module.
  * @retval None
  */
void HAL_SUBGHZ_IRQHandler(SUBGHZ_HandleTypeDef *hsubghz)
{
  uint8_t tmpisr[2] = {0};
  uint16_t itsource;

  /* Retrieve Interrupts from SUBGHZ Irq Register */
  (void)HAL_SUBGHZ_ExecGetCmd(hsubghz, RADIO_GET_IRQSTATUS, tmpisr, 2);
  itsource = tmpisr[0];
  itsource = (itsource << 8) | tmpisr[1];

  /* Packet transmission completed Interrupt */
  if (SUBGHZ_CHECK_IT_SOURCE(itsource, SUBGHZ_IT_TX_CPLT) != RESET)
  {
#if (USE_HAL_SUBGHZ_REGISTER_CALLBACKS == 1U)
    hsubghz->TxCpltCallback(hsubghz);
#else
    HAL_SUBGHZ_TxCpltCallback(hsubghz);
#endif /* USE_HAL_SUBGHZ_REGISTER_CALLBACKS */
  }

  /* Packet received Interrupt */
  if (SUBGHZ_CHECK_IT_SOURCE(itsource, SUBGHZ_IT_RX_CPLT) != RESET)
  {
#if (USE_HAL_SUBGHZ_REGISTER_CALLBACKS == 1U)
    hsubghz->RxCpltCallback(hsubghz);
#else
    HAL_SUBGHZ_RxCpltCallback(hsubghz);
#endif /* USE_HAL_SUBGHZ_REGISTER_CALLBACKS */
  }

  /* Preamble Detected Interrupt */
  if (SUBGHZ_CHECK_IT_SOURCE(itsource, SUBGHZ_IT_PREAMBLE_DETECTED) != RESET)
  {
#if (USE_HAL_SUBGHZ_REGISTER_CALLBACKS == 1U)
    hsubghz->PreambleDetectedCallback(hsubghz);
#else
    HAL_SUBGHZ_PreambleDetectedCallback(hsubghz);
#endif /* USE_HAL_SUBGHZ_REGISTER_CALLBACKS */
  }

  /*  Valid sync word detected Interrupt */
  if (SUBGHZ_CHECK_IT_SOURCE(itsource, SUBGHZ_IT_SYNCWORD_VALID) != RESET)
  {
#if (USE_HAL_SUBGHZ_REGISTER_CALLBACKS == 1U)
    hsubghz->SyncWordValidCallback(hsubghz);
#else
    HAL_SUBGHZ_SyncWordValidCallback(hsubghz);
#endif /* USE_HAL_SUBGHZ_REGISTER_CALLBACKS */
  }

  /* Valid LoRa header received Interrupt */
  if (SUBGHZ_CHECK_IT_SOURCE(itsource, SUBGHZ_IT_HEADER_VALID) != RESET)
  {
#if (USE_HAL_SUBGHZ_REGISTER_CALLBACKS == 1U)
    hsubghz->HeaderValidCallback(hsubghz);
#else
    HAL_SUBGHZ_HeaderValidCallback(hsubghz);
#endif /* USE_HAL_SUBGHZ_REGISTER_CALLBACKS */
  }

  /* LoRa header CRC error Interrupt */
  if (SUBGHZ_CHECK_IT_SOURCE(itsource, SUBGHZ_IT_HEADER_ERROR) != RESET)
  {
#if (USE_HAL_SUBGHZ_REGISTER_CALLBACKS == 1U)
    hsubghz->HeaderErrorCallback(hsubghz);
#else
    HAL_SUBGHZ_HeaderErrorCallback(hsubghz);
#endif /* USE_HAL_SUBGHZ_REGISTER_CALLBACKS */
  }

  /* Wrong CRC received Interrupt */
  if (SUBGHZ_CHECK_IT_SOURCE(itsource, SUBGHZ_IT_CRC_ERROR) != RESET)
  {
#if (USE_HAL_SUBGHZ_REGISTER_CALLBACKS == 1U)
    hsubghz->CRCErrorCallback(hsubghz);
#else
    HAL_SUBGHZ_CRCErrorCallback(hsubghz);
#endif /* USE_HAL_SUBGHZ_REGISTER_CALLBACKS */
  }

  /* Channel activity detection finished Interrupt */
  if (SUBGHZ_CHECK_IT_SOURCE(itsource, SUBGHZ_IT_CAD_DONE) != RESET)
  {
#if (USE_HAL_SUBGHZ_REGISTER_CALLBACKS == 1U)
    /* Channel activity Detected Interrupt */
    if (SUBGHZ_CHECK_IT_SOURCE(itsource, SUBGHZ_IT_CAD_ACTIVITY_DETECTED) != RESET)
    {
      hsubghz->CADStatusCallback(hsubghz, HAL_SUBGHZ_CAD_DETECTED);
    }
    else
    {
      hsubghz->CADStatusCallback(hsubghz, HAL_SUBGHZ_CAD_CLEAR);
    }
#else
    /* Channel activity Detected Interrupt */
    if (SUBGHZ_CHECK_IT_SOURCE(itsource, SUBGHZ_IT_CAD_ACTIVITY_DETECTED) != RESET)
    {
      HAL_SUBGHZ_CADStatusCallback(hsubghz, HAL_SUBGHZ_CAD_DETECTED);
    }
    else
    {
      HAL_SUBGHZ_CADStatusCallback(hsubghz, HAL_SUBGHZ_CAD_CLEAR);
    }
#endif /* USE_HAL_SUBGHZ_REGISTER_CALLBACKS */
  }

  /* Rx or Tx Timeout Interrupt */
  if (SUBGHZ_CHECK_IT_SOURCE(itsource, SUBGHZ_IT_RX_TX_TIMEOUT) != RESET)
  {
#if (USE_HAL_SUBGHZ_REGISTER_CALLBACKS == 1U)
    hsubghz->RxTxTimeoutCallback(hsubghz);
#else
    HAL_SUBGHZ_RxTxTimeoutCallback(hsubghz);
#endif /* USE_HAL_SUBGHZ_REGISTER_CALLBACKS */
  }

  /* Clear SUBGHZ Irq Register */
  (void)HAL_SUBGHZ_ExecSetCmd(hsubghz, RADIO_CLR_IRQSTATUS, tmpisr, 2);
}

/**
  * @brief  Packet transmission completed callback.
  * @param  hsubghz pointer to a SUBGHZ_HandleTypeDef structure that contains
  *               the configuration information for SUBGHZ module.
  * @retval None
  */
__weak void HAL_SUBGHZ_TxCpltCallback(SUBGHZ_HandleTypeDef *hsubghz)
{
  /* Prevent unused argument(s) compilation warning */
  UNUSED(hsubghz);

  /* NOTE : This function should not be modified, when the callback is needed,
            the HAL_SUBGHZ_TxCpltCallback should be implemented in the user file
   */
}

/**
  * @brief  Packet received callback.
  * @param  hsubghz pointer to a SUBGHZ_HandleTypeDef structure that contains
  *               the configuration information for SUBGHZ module.
  * @retval None
  */
__weak void HAL_SUBGHZ_RxCpltCallback(SUBGHZ_HandleTypeDef *hsubghz)
{
  /* Prevent unused argument(s) compilation warning */
  UNUSED(hsubghz);

  /* NOTE : This function should not be modified, when the callback is needed,
            the HAL_SUBGHZ_RxCpltCallback should be implemented in the user file
   */
}

/**
  * @brief  Preamble Detected callback.
  * @param  hsubghz pointer to a SUBGHZ_HandleTypeDef structure that contains
  *               the configuration information for SUBGHZ module.
  * @retval None
  */
__weak void HAL_SUBGHZ_PreambleDetectedCallback(SUBGHZ_HandleTypeDef *hsubghz)
{
  /* Prevent unused argument(s) compilation warning */
  UNUSED(hsubghz);

  /* NOTE : This function should not be modified, when the callback is needed,
            the HAL_SUBGHZ_PreambleDetectedCallback should be implemented in the user file
   */
}

/**
  * @brief  Valid sync word detected callback.
  * @param  hsubghz pointer to a SUBGHZ_HandleTypeDef structure that contains
  *               the configuration information for SUBGHZ module.
  * @retval None
  */
__weak void HAL_SUBGHZ_SyncWordValidCallback(SUBGHZ_HandleTypeDef *hsubghz)
{
  /* Prevent unused argument(s) compilation warning */
  UNUSED(hsubghz);

  /* NOTE : This function should not be modified, when the callback is needed,
            the HAL_SUBGHZ_SyncWordValidCallback should be implemented in the user file
   */
}

/**
  * @brief  Valid LoRa header received callback.
  * @param  hsubghz pointer to a SUBGHZ_HandleTypeDef structure that contains
  *               the configuration information for SUBGHZ module.
  * @retval None
  */
__weak void HAL_SUBGHZ_HeaderValidCallback(SUBGHZ_HandleTypeDef *hsubghz)
{
  /* Prevent unused argument(s) compilation warning */
  UNUSED(hsubghz);

  /* NOTE : This function should not be modified, when the callback is needed,
            the HAL_SUBGHZ_HeaderValidCallback should be implemented in the user file
   */
}

/**
  * @brief  LoRa header CRC error callback.
  * @param  hsubghz pointer to a SUBGHZ_HandleTypeDef structure that contains
  *               the configuration information for SUBGHZ module.
  * @retval None
  */
__weak void HAL_SUBGHZ_HeaderErrorCallback(SUBGHZ_HandleTypeDef *hsubghz)
{
  /* Prevent unused argument(s) compilation warning */
  UNUSED(hsubghz);

  /* NOTE : This function should not be modified, when the callback is needed,
            the HAL_SUBGHZ_HeaderErrorCallback should be implemented in the user file
   */
}

/**
  * @brief  Wrong CRC received callback.
  * @param  hsubghz pointer to a SUBGHZ_HandleTypeDef structure that contains
  *               the configuration information for SUBGHZ module.
  * @retval None
  */
__weak void HAL_SUBGHZ_CRCErrorCallback(SUBGHZ_HandleTypeDef *hsubghz)
{
  /* Prevent unused argument(s) compilation warning */
  UNUSED(hsubghz);

  /* NOTE : This function should not be modified, when the callback is needed,
            the HAL_SUBGHZ_CRCErrorCallback should be implemented in the user file
   */
}

/**
  * @brief  Channel activity detection status callback.
  * @note   Unified callback for CAD Done and CAD activity interrupts.
  * @param  hsubghz pointer to a SUBGHZ_HandleTypeDef structure that contains
  *               the configuration information for SUBGHZ module.
  * @param  cadstatus reports whether activity is detected or not
  * @retval None
  */
__weak void HAL_SUBGHZ_CADStatusCallback(SUBGHZ_HandleTypeDef *hsubghz,
                                         HAL_SUBGHZ_CadStatusTypeDef cadstatus)
{
  /* Prevent unused argument(s) compilation warning */
  UNUSED(hsubghz);

  UNUSED(cadstatus);
  /* NOTE : This function should not be modified, when the callback is needed,
            the HAL_SUBGHZ_CADStatusCallback should be implemented in the user file
   */
}

/**
  * @brief  Rx or Tx Timeout callback.
  * @param  hsubghz pointer to a SUBGHZ_HandleTypeDef structure that contains
  *               the configuration information for SUBGHZ module.
  * @retval None
  */
__weak void HAL_SUBGHZ_RxTxTimeoutCallback(SUBGHZ_HandleTypeDef *hsubghz)
{
  /* Prevent unused argument(s) compilation warning */
  UNUSED(hsubghz);

  /* NOTE : This function should not be modified, when the callback is needed,
            the HAL_SUBGHZ_RxTxTimeoutCallback should be implemented in the user file
   */
}

/**
  * @}
  */

/** @defgroup SUBGHZ_Exported_Functions_Group3 Peripheral State and Errors functions
  * @brief   SUBGHZ control functions
  *
@verbatim
 ===============================================================================
                      ##### Peripheral State and Errors functions #####
 ===============================================================================
    [..]
    This subsection provides a set of functions allowing to control the SUBGHZ.
     (+) HAL_SUBGHZ_GetState() API can be helpful to check in run-time the state of the SUBGHZ peripheral
     (+) HAL_SUBGHZ_GetError() check in run-time Errors occurring during communication
@endverbatim
  * @{
  */

/**
  * @brief  Return the SUBGHZ handle state.
  * @param  hsubghz pointer to a SUBGHZ_HandleTypeDef structure that contains
  *         the handle information for SUBGHZ module.
  * @retval SUBGHZ state
  */
HAL_SUBGHZ_StateTypeDef HAL_SUBGHZ_GetState(SUBGHZ_HandleTypeDef *hsubghz)
{
  /* Return SUBGHZ handle state */
  return hsubghz->State;
}

/**
  * @brief  Return the SUBGHZ error code.
  * @param  hsubghz pointer to a SUBGHZ_HandleTypeDef structure that contains
  *         the handle information for SUBGHZ module.
  * @retval SUBGHZ error code in bitmap format
  */
uint32_t HAL_SUBGHZ_GetError(SUBGHZ_HandleTypeDef *hsubghz)
{
  /* Return SUBGHZ ErrorCode */
  return hsubghz->ErrorCode;
}

/**
  * @}
  */

/**
  * @}
  */

/** @addtogroup SUBGHZ_Private_Functions
  * @brief   Private functions
  * @{
  */

/**
  * @brief  Initializes the SUBGHZSPI peripheral
  * @param  BaudratePrescaler SPI Baudrate prescaler
  * @retval None
  */
void SUBGHZSPI_Init(uint32_t BaudratePrescaler)
{
  /* Check the parameters */
  assert_param(IS_SUBGHZ_ALL_INSTANCE(SUBGHZSPI));

  /* Disable SUBGHZSPI Peripheral */
  CLEAR_BIT(SUBGHZSPI->CR1, SPI_CR1_SPE);

  /*----------------------- SPI CR1 Configuration ----------------------------*
   *             SPI Mode: Master                                             *
   *   Communication Mode: 2 lines (Full-Duplex)                              *
   *       Clock polarity: Low                                                *
   *                phase: 1st Edge                                           *
   *       NSS management: Internal (Done with External bit inside PWR        *
   *  Communication speed: BaudratePrescaler                             *
   *            First bit: MSB                                                *
   *      CRC calculation: Disable                                            *
   *--------------------------------------------------------------------------*/
  WRITE_REG(SUBGHZSPI->CR1, (SPI_CR1_MSTR | SPI_CR1_SSI | BaudratePrescaler | SPI_CR1_SSM));

  /*----------------------- SPI CR2 Configuration ----------------------------*
   *            Data Size: 8bits                                              *
   *              TI Mode: Disable                                            *
   *            NSS Pulse: Disable                                            *
   *    Rx FIFO Threshold: 8bits                                              *
   *--------------------------------------------------------------------------*/
  WRITE_REG(SUBGHZSPI->CR2, (SPI_CR2_FRXTH |  SPI_CR2_DS_0 | SPI_CR2_DS_1 | SPI_CR2_DS_2));

  /* Enable SUBGHZSPI Peripheral */
  SET_BIT(SUBGHZSPI->CR1, SPI_CR1_SPE);
}

/**
  * @brief  DeInitializes the SUBGHZSPI peripheral
  * @retval None
  */
void  SUBGHZSPI_DeInit(void)
{
  /* Check the parameters */
  assert_param(IS_SUBGHZ_ALL_INSTANCE(SUBGHZSPI));

  /* Disable SUBGHZSPI Peripheral */
  CLEAR_BIT(SUBGHZSPI->CR1, SPI_CR1_SPE);
}

/**
  * @brief  Transmit data trough SUBGHZSPI peripheral
  * @param  hsubghz pointer to a SUBGHZ_HandleTypeDef structure that contains
  *         the handle information for SUBGHZ module.
  * @param  Data  data to transmit
  * @retval HAL status
  */
HAL_StatusTypeDef SUBGHZSPI_Transmit(SUBGHZ_HandleTypeDef *hsubghz,
                                     uint8_t Data)
{
  HAL_StatusTypeDef status = HAL_OK;
  __IO uint32_t count;

  /* Handle Tx transmission from SUBGHZSPI peripheral to Radio ****************/
  /* Initialize Timeout */
  count = SUBGHZ_DEFAULT_TIMEOUT * SUBGHZ_DEFAULT_LOOP_TIME;

  /* Wait until TXE flag is set */
  do
  {
    if (count == 0U)
    {
      status = HAL_ERROR;
      hsubghz->ErrorCode = HAL_SUBGHZ_ERROR_TIMEOUT;
      break;
    }
    count--;
  } while (READ_BIT(SUBGHZSPI->SR, SPI_SR_TXE) != (SPI_SR_TXE));

  /* Transmit Data*/
#if defined (__GNUC__)
  __IO uint8_t *spidr = ((__IO uint8_t *)&SUBGHZSPI->DR);
  *spidr = Data;
#else
  *((__IO uint8_t *)&SUBGHZSPI->DR) = Data;
#endif /* __GNUC__ */

  /* Handle Rx transmission from SUBGHZSPI peripheral to Radio ****************/
  /* Initialize Timeout */
  count = SUBGHZ_DEFAULT_TIMEOUT * SUBGHZ_DEFAULT_LOOP_TIME;

  /* Wait until RXNE flag is set */
  do
  {
    if (count == 0U)
    {
      status = HAL_ERROR;
      hsubghz->ErrorCode = HAL_SUBGHZ_ERROR_TIMEOUT;
      break;
    }
    count--;
  } while (READ_BIT(SUBGHZSPI->SR, SPI_SR_RXNE) != (SPI_SR_RXNE));

  /* Flush Rx data */
  READ_REG(SUBGHZSPI->DR);

  return status;
}

/**
  * @brief  Receive data trough SUBGHZSPI peripheral
  * @param  hsubghz pointer to a SUBGHZ_HandleTypeDef structure that contains
  *         the handle information for SUBGHZ module.
  * @param  pData  pointer on data to receive
  * @retval HAL status
  */
HAL_StatusTypeDef SUBGHZSPI_Receive(SUBGHZ_HandleTypeDef *hsubghz,
                                    uint8_t *pData)
{
  HAL_StatusTypeDef status = HAL_OK;
  __IO uint32_t count;

  /* Handle Tx transmission from SUBGHZSPI peripheral to Radio ****************/
  /* Initialize Timeout */
  count = SUBGHZ_DEFAULT_TIMEOUT * SUBGHZ_DEFAULT_LOOP_TIME;

  /* Wait until TXE flag is set */
  do
  {
    if (count == 0U)
    {
      status = HAL_ERROR;
      hsubghz->ErrorCode = HAL_SUBGHZ_ERROR_TIMEOUT;
      break;
    }
    count--;
  } while (READ_BIT(SUBGHZSPI->SR, SPI_SR_TXE) != (SPI_SR_TXE));

  /* Transmit Data*/
#if defined (__GNUC__)
  __IO uint8_t *spidr = ((__IO uint8_t *)&SUBGHZSPI->DR);
  *spidr = SUBGHZ_DUMMY_DATA;
#else
  *((__IO uint8_t *)&SUBGHZSPI->DR) = SUBGHZ_DUMMY_DATA;
#endif /* __GNUC__ */

  /* Handle Rx transmission from SUBGHZSPI peripheral to Radio ****************/
  /* Initialize Timeout */
  count = SUBGHZ_DEFAULT_TIMEOUT * SUBGHZ_DEFAULT_LOOP_TIME;

  /* Wait until RXNE flag is set */
  do
  {
    if (count == 0U)
    {
      status = HAL_ERROR;
      hsubghz->ErrorCode = HAL_SUBGHZ_ERROR_TIMEOUT;
      break;
    }
    count--;
  } while (READ_BIT(SUBGHZSPI->SR, SPI_SR_RXNE) != (SPI_SR_RXNE));

  /* Retrieve pData */
  *pData = (uint8_t)(READ_REG(SUBGHZSPI->DR));

  return status;
}

/**
  * @brief  Check if peripheral is ready
  * @param  hsubghz pointer to a SUBGHZ_HandleTypeDef structure that contains
  *         the handle information for SUBGHZ module.
  * @retval HAL status
  */
HAL_StatusTypeDef SUBGHZ_CheckDeviceReady(SUBGHZ_HandleTypeDef *hsubghz)
{
  __IO uint32_t count;

  /* Wakeup radio in case of sleep mode: Select-Unselect radio */
  if (hsubghz->DeepSleep == SUBGHZ_DEEP_SLEEP_ENABLE)
  {
    /* Initialize NSS switch Delay */
    count  = SUBGHZ_NSS_LOOP_TIME;

    /* NSS = 0; */
    LL_PWR_SelectSUBGHZSPI_NSS();

    /* Wait Radio wakeup */
    do
    {
      count--;
    } while (count != 0UL);

    /* NSS = 1 */
    LL_PWR_UnselectSUBGHZSPI_NSS();
  }
  return (SUBGHZ_WaitOnBusy(hsubghz));
}

/**
  * @brief  Wait busy flag low from peripheral
  * @param  hsubghz pointer to a SUBGHZ_HandleTypeDef structure that contains
  *         the handle information for SUBGHZ module.
  * @retval HAL status
  */
HAL_StatusTypeDef SUBGHZ_WaitOnBusy(SUBGHZ_HandleTypeDef *hsubghz)
{
  HAL_StatusTypeDef status;
  __IO uint32_t count;
  uint32_t mask;

  status = HAL_OK;
  count  = SUBGHZ_DEFAULT_TIMEOUT * SUBGHZ_RFBUSY_LOOP_TIME;

  /* Wait until Busy signal is set */
  do
  {
    mask = LL_PWR_IsActiveFlag_RFBUSYMS();

    if (count == 0U)
    {
      status  = HAL_ERROR;
      hsubghz->ErrorCode = HAL_SUBGHZ_ERROR_RF_BUSY;
      break;
    }
    count--;
  } while ((LL_PWR_IsActiveFlag_RFBUSYS()& mask) == 1UL);

  return status;
}
/**
  * @}
  */

#endif /* HAL_SUBGHZ_MODULE_ENABLED */

/**
  * @}
  */

/**
  * @}
  */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
