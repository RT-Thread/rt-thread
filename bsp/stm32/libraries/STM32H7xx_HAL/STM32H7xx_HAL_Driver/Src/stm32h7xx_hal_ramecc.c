/**
  ******************************************************************************
  * @file    stm32h7xx_hal_ramecc.c
  * @author  MCD Application Team
  * @brief   RAMECC HAL module driver.
  *          This file provides firmware functions to manage the following
  *          functionalities of the RAM ECC monitoring (RAMECC) peripheral:
  *           + Initialization and de-initialization functions
  *           + Monitoring operation functions
  *           + Error information functions
  *           + State and error functions
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
   (#) Enable and latch error information through HAL_RAMECC_Init().

   (#) For a given Monitor, enable and disable interrupt through
       HAL_RAMECC_EnableNotification().
       To enable a notification for a given RAMECC instance, use global
       interrupts.
       To enable a notification for only RAMECC monitor, use monitor interrupts.
       All possible notifications are defined in the driver header file under
       RAMECC_Interrupt group.

     *** Silent mode ***
     ===================
    [..]
          (+) Use HAL_RAMECC_StartMonitor() to start RAMECC latch failing
              information without enabling any notification.

     *** Interrupt mode ***
     ======================
    [..]
          (+) Use HAL_RAMECC_EnableNotification() to enable interrupts for a
              given error.
          (+) Configure the RAMECC interrupt priority using
              HAL_NVIC_SetPriority().
          (+) Enable the RAMECC IRQ handler using HAL_NVIC_EnableIRQ().
          (+) Start RAMECC latch failing information using HAL_RAMECC_StartMonitor().

     *** Failing information ***
     ======================
    [..]
     (#) Use HAL_RAMECC_GetFailingAddress() function to return the RAMECC
         failing address.
     (#) Use HAL_RAMECC_GetFailingDataLow() function to return the RAMECC
         failing data low.
     (#) Use HAL_RAMECC_GetFailingDataHigh() function to return the RAMECC
         failing data high.
     (#) Use HAL_RAMECC_GetHammingErrorCode() function to return the RAMECC
         Hamming bits injected.
     (#) Use HAL_RAMECC_IsECCSingleErrorDetected() function to check if a single
         error was detected and corrected.
     (#) Use HAL_RAMECC_IsECCDoubleErrorDetected() function to check if a double
         error was dedetected.

     *** RAMECC HAL driver macros list ***
     =============================================
     [..]
       Below the list of used macros in RAMECC HAL driver.

      (+) __HAL_RAMECC_ENABLE_IT  : Enable the specified ECCRAM Monitor
                                    interrupts.
      (+) __HAL_RAMECC_DISABLE_IT : Disable the specified ECCRAM Monitor
                                    interrupts.
      (+) __HAL_RAMECC_GET_FLAG   : Return the current RAMECC Monitor selected
                                    flag.
      (+) __HAL_RAMECC_CLEAR_FLAG : Clear the current RAMECC Monitor selected
                                    flag.

    ##### Callback registration #####
    ==================================
    [..]
      (#) The compilation define USE_HAL_RAMECC_REGISTER_CALLBACKS when set to 1
          allows the user to configure dynamically the driver callback.

    [..]
      (#) Use Function HAL_RAMECC_RegisterCallback() to register a user callback.
      (#) Function HAL_RAMECC_RegisterCallback() allows to register following callback:
         (+) RAMECCErrorCode        : RAMECC error code detection.
      (#) This function takes as parameters the HAL peripheral handle 
          and a pointer to the user callback function.

    [..]
      (#) Use function HAL_RAMECC_UnRegisterCallback() to reset a callback to the default
          weak function.
      (#) HAL_RAMECC_UnRegisterCallback() takes as parameters the HAL peripheral handle.
      (#) This function allows to reset following callback:
          (+) RAMECCErrorCode        : RAMECC error code detection.
    [..]
      (#) When The compilation define USE_HAL_RAMECC_REGISTER_CALLBACKS is set to 0 or
          not defined, the callback registration feature is not available
          and weak callbacks are used.
 
  @endverbatim
  */

/* Includes ------------------------------------------------------------------*/
#include "stm32h7xx_hal.h"

/** @addtogroup STM32H7xx_HAL_Driver
  * @{
  */

/** @defgroup RAMECC RAMECC
  * @brief RAMECC HAL module driver
  * @{
  */

#ifdef HAL_RAMECC_MODULE_ENABLED

/* Private types -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private constants ---------------------------------------------------------*/
/* Private macros ------------------------------------------------------------*/
/* Private functions ---------------------------------------------------------*/
/* Exported functions --------------------------------------------------------*/

/** @addtogroup RAMECC_Exported_Functions
  * @{
  */

/** @addtogroup RAMECC_Exported_Functions_Group1
  *
@verbatim
 ===============================================================================
             ##### Initialization and de-initialization functions  #####
 ===============================================================================
    [..]
    This section provides functions allowing to initialize the RAMECC Monitor.
    [..]
    The HAL_RAMECC_Init() function follows the RAMECC configuration procedures
    as described in reference manual.
    The HAL_RAMECC_DeInit() function allows to deinitialize the RAMECC monitor.

@endverbatim
  * @{
  */

/**
  * @brief  Initialize the RAMECC by clearing flags and disabling interrupts.
  * @param  hramecc  Pointer to a RAMECC_HandleTypeDef structure that contains
  *                  the configuration information for the specified RAMECC
  *                  Monitor.
  * @retval HAL status.
  */
HAL_StatusTypeDef HAL_RAMECC_Init(RAMECC_HandleTypeDef *hramecc)
{
  /* Check the RAMECC peripheral handle */
  if (hramecc == NULL)
  {
    /* Return HAL status */
    return HAL_ERROR;
  }

  /* Check the parameters */
  assert_param (IS_RAMECC_MONITOR_ALL_INSTANCE (hramecc->Instance));

  /* Change RAMECC peripheral state */
  hramecc->State = HAL_RAMECC_STATE_BUSY;

  /* Disable RAMECC monitor */
  hramecc->Instance->CR &= ~RAMECC_CR_ECCELEN;

  /* Disable all global interrupts */
  ((RAMECC_TypeDef *)((uint32_t)hramecc->Instance & 0xFFFFFF00U))->IER &= \
    ~(RAMECC_IER_GIE | RAMECC_IER_GECCSEIE | RAMECC_IER_GECCDEIE | RAMECC_IER_GECCDEBWIE);

  /* Disable all interrupts monitor  */
  hramecc->Instance->CR &= ~(RAMECC_CR_ECCSEIE | RAMECC_CR_ECCDEIE | RAMECC_CR_ECCDEBWIE);

  /* Clear RAMECC monitor flags */
  __HAL_RAMECC_CLEAR_FLAG (hramecc, RAMECC_FLAGS_ALL);

  /* Initialise the RAMECC error code */
  hramecc->ErrorCode = HAL_RAMECC_ERROR_NONE;

  /* Initialise the RAMECC error detected code */
  hramecc->RAMECCErrorCode = HAL_RAMECC_NO_ERROR;

  /* Update the RAMECC state */
  hramecc->State = HAL_RAMECC_STATE_READY;

  /* Return HAL status */
  return HAL_OK;
}

/**
  * @brief  DeInitializes the RAMECC peripheral.
  * @param  hramecc  Pointer to a RAMECC_HandleTypeDef structure that contains
  *                  the configuration information for the specified RAMECC
  *                  Monitor.
  * @retval HAL status.
  */
HAL_StatusTypeDef HAL_RAMECC_DeInit(RAMECC_HandleTypeDef *hramecc)
{
  /* Check the RAMECC peripheral handle */
  if (hramecc == NULL)
  {
    /* Return HAL status */
    return HAL_ERROR;
  }

  /* Check the parameters */
  assert_param (IS_RAMECC_MONITOR_ALL_INSTANCE (hramecc->Instance));

  /* Disable RAMECC monitor */
  hramecc->Instance->CR &= ~RAMECC_CR_ECCELEN;

  /* Disable all global interrupts */
  ((RAMECC_TypeDef *)((uint32_t)hramecc->Instance & 0xFFFFFF00U))->IER &= \
    ~(RAMECC_IER_GIE | RAMECC_IER_GECCSEIE | RAMECC_IER_GECCDEIE | RAMECC_IER_GECCDEBWIE);

  /* Disable all interrupts monitor  */
  hramecc->Instance->CR &= ~(RAMECC_CR_ECCSEIE | RAMECC_CR_ECCDEIE | RAMECC_CR_ECCDEBWIE);

  /* Clear RAMECC monitor flags */
  __HAL_RAMECC_CLEAR_FLAG (hramecc, RAMECC_FLAGS_ALL);

#if (USE_HAL_RAMECC_REGISTER_CALLBACKS == 1)
  /* Clean callback */
  hramecc->DetectErrorCallback = NULL;
#endif /* USE_HAL_RAMECC_REGISTER_CALLBACKS */

  /* Initialize the RAMECC error code */
  hramecc->ErrorCode = HAL_RAMECC_ERROR_NONE;

  /* Initialize the RAMECC error detected code */
  hramecc->RAMECCErrorCode = HAL_RAMECC_NO_ERROR;

  /* Change RAMECC peripheral state */
  hramecc->State = HAL_RAMECC_STATE_RESET;

  /* Return HAL status */
  return HAL_OK;
}

/**
  * @}
  */

/** @addtogroup RAMECC_Exported_Functions_Group2
  *
@verbatim
 ===============================================================================
                   #####  Monitoring operation functions  #####
 ===============================================================================
    [..]  This section provides functions allowing to:
      (+) Configure latching error information.
      (+) Configure RAMECC Global/Monitor interrupts.
      (+) Register and Unregister RAMECC callbacks
      (+) Handle RAMECC interrupt request

@endverbatim
  * @{
  */

/**
  * @brief  Starts the RAMECC latching error information.
  * @param  hramecc  Pointer to a RAMECC_HandleTypeDef structure that contains
  *                  the configuration information for the specified RAMECC
  *                  Monitor.
  * @retval HAL status.
  */
HAL_StatusTypeDef HAL_RAMECC_StartMonitor(RAMECC_HandleTypeDef *hramecc)
{
  /* Check the parameters */
  assert_param (IS_RAMECC_MONITOR_ALL_INSTANCE (hramecc->Instance));

  /* Check RAMECC state */
  if (hramecc->State == HAL_RAMECC_STATE_READY)
  {
    /* Change RAMECC peripheral state */
    hramecc->State = HAL_RAMECC_STATE_BUSY;

    /* Enable RAMECC monitor */
    hramecc->Instance->CR |= RAMECC_CR_ECCELEN;

    /* Change RAMECC peripheral state */
    hramecc->State = HAL_RAMECC_STATE_READY;
  }
  else
  {
    /* Update the error code */
    hramecc->ErrorCode = HAL_RAMECC_ERROR_BUSY;

    /* Return HAL status */
    return HAL_ERROR;
  }

  /* Return HAL status */
  return HAL_OK;
}

/**
  * @brief  Stop the RAMECC latching error information.
  * @param  hramecc  Pointer to a RAMECC_HandleTypeDef structure that contains
  *                  the configuration information for the specified RAMECC
  *                  Monitor.
  * @retval HAL status.
  */
HAL_StatusTypeDef HAL_RAMECC_StopMonitor(RAMECC_HandleTypeDef *hramecc)
{
  /* Check the parameters */
  assert_param (IS_RAMECC_MONITOR_ALL_INSTANCE (hramecc->Instance));

  /* Check RAMECC state */
  if (hramecc->State == HAL_RAMECC_STATE_READY)
  {
    /* Change RAMECC peripheral state */
    hramecc->State = HAL_RAMECC_STATE_BUSY;

    /* Disable RAMECC monitor */
    hramecc->Instance->CR &= ~RAMECC_CR_ECCELEN;

    /* Change RAMECC peripheral state */
    hramecc->State = HAL_RAMECC_STATE_READY;
  }
  else
  {
    /* Update the error code */
    hramecc->ErrorCode = HAL_RAMECC_ERROR_BUSY;

    /* Return HAL status */
    return HAL_ERROR;
  }

  /* Return HAL status */
  return HAL_OK;
}

/**
  * @brief  Enable the RAMECC error interrupts.
  * @param  hramecc        Pointer to a RAMECC_HandleTypeDef structure that
  *                        contains the configuration information for the
  *                        specified RAMECC Monitor.
  * @param  Notifications  Select the notification.
  * @retval HAL status.
  */
HAL_StatusTypeDef HAL_RAMECC_EnableNotification(RAMECC_HandleTypeDef *hramecc, uint32_t Notifications)
{
  /* Check the parameters */
  assert_param (IS_RAMECC_MONITOR_ALL_INSTANCE (hramecc->Instance));
  assert_param (IS_RAMECC_INTERRUPT (Notifications));

  /* Check RAMECC state */
  if (hramecc->State == HAL_RAMECC_STATE_READY)
  {
    /* Change RAMECC peripheral state */
    hramecc->State = HAL_RAMECC_STATE_BUSY;

    /* Enable RAMECC interrupts */
    __HAL_RAMECC_ENABLE_IT (hramecc, Notifications);

    /* Change RAMECC peripheral state */
    hramecc->State = HAL_RAMECC_STATE_READY;
  }
  else
  {
    /* Update the error code */
    hramecc->ErrorCode = HAL_RAMECC_ERROR_BUSY;

    /* Return HAL status */
    return HAL_ERROR;
  }

  /* Return HAL status */
  return HAL_OK;
}

/**
  * @brief  Disable the RAMECC error interrupts.
  * @param  hramecc        Pointer to a RAMECC_HandleTypeDef structure that
  *                        contains the configuration information for the
  *                        specified RAMECC Monitor.
  * @param  Notifications  Select the notification.
  * @retval HAL status.
  */
HAL_StatusTypeDef HAL_RAMECC_DisableNotification(RAMECC_HandleTypeDef *hramecc, uint32_t Notifications)
{
  /* Check the parameters */
  assert_param (IS_RAMECC_MONITOR_ALL_INSTANCE (hramecc->Instance));
  assert_param (IS_RAMECC_INTERRUPT (Notifications));

  /* Check RAMECC state */
  if (hramecc->State == HAL_RAMECC_STATE_READY)
  {
    /* Change RAMECC peripheral state */
    hramecc->State = HAL_RAMECC_STATE_BUSY;

    /* Disable RAMECC interrupts */
    __HAL_RAMECC_DISABLE_IT (hramecc, Notifications);

    /* Change RAMECC peripheral state */
    hramecc->State = HAL_RAMECC_STATE_READY;
  }
  else
  {
    /* Update the error code */
    hramecc->ErrorCode = HAL_RAMECC_ERROR_BUSY;

    /* Return HAL status */
    return HAL_ERROR;
  }

  /* Return HAL status */
  return HAL_OK;
}

/**
  * @}
  */

/** @addtogroup RAMECC_Exported_Functions_Group3
  *
@verbatim
 ===============================================================================
               ##### Handle Interrupt and Callbacks Functions  #####
 ===============================================================================
    [..]
      This section provides functions to handle RAMECC interrupts and
      Register / UnRegister the different callbacks.
    [..]
      The HAL_RAMECC_IRQHandler() function allows the user to handle the active RAMECC
      interrupt request.
      The HAL_RAMECC_RegisterCallback() function allows the user to register the selected
      RAMECC callbacks.
      The HAL_RAMECC_UnRegisterCallback() function allows the user to unregister the
      selected RAMECC callbacks.
@endverbatim
  * @{
  */

#if (USE_HAL_RAMECC_REGISTER_CALLBACKS == 1)
/**
  * @brief  Register callbacks.
  * @param  hramecc    Pointer to a RAMECC_HandleTypeDef structure that contains
  *                    the configuration information for the specified RAMECC
  *                    Monitor.
  * @param  pCallback  pointer to private callbacsk function which has pointer to
  *                    a RAMECC_HandleTypeDef structure as parameter.
  * @retval HAL status.
  */
HAL_StatusTypeDef HAL_RAMECC_RegisterCallback (RAMECC_HandleTypeDef *hramecc, void (* pCallback)(RAMECC_HandleTypeDef *_hramecc))
{
  HAL_StatusTypeDef status = HAL_OK;

  if (pCallback == NULL)
  {
    /* Update the error code */
    hramecc->ErrorCode |= HAL_RAMECC_ERROR_INVALID_CALLBACK;

    /* Return HAL status */
    return HAL_ERROR;
  }

  /* Check the parameters */
  assert_param (IS_RAMECC_MONITOR_ALL_INSTANCE (hramecc->Instance));

  /* Check RAMECC state */
  if (hramecc->State == HAL_RAMECC_STATE_READY)
  {
    hramecc->DetectErrorCallback = pCallback;
  }
  else
  {
    /* Update the error code */
    hramecc->ErrorCode = HAL_RAMECC_ERROR_INVALID_CALLBACK;

    /* Update HAL status */
    status = HAL_ERROR;
  }

  /* Return HAL status */
  return status;
}

/**
  * @brief  UnRegister callbacks.
  * @param  hramecc    Pointer to a RAMECC_HandleTypeDef structure that contains
  *                    the configuration information for the specified RAMECC
  *                    Monitor.
  * @retval HAL status.
  */
HAL_StatusTypeDef HAL_RAMECC_UnRegisterCallback(RAMECC_HandleTypeDef *hramecc)
{
  HAL_StatusTypeDef status = HAL_OK;

  /* Check the parameters */
  assert_param (IS_RAMECC_MONITOR_ALL_INSTANCE (hramecc->Instance));

  /* Check RAMECC state */
  if (hramecc->State == HAL_RAMECC_STATE_READY)
  {
    hramecc->DetectErrorCallback = NULL;
  }
  else
  {
    /* Update the error code */
    hramecc->ErrorCode = HAL_RAMECC_ERROR_INVALID_CALLBACK;

    /* Update HAL status */
    status = HAL_ERROR;
  }

  /* Return HAL status */
  return status;
}
#endif /* USE_HAL_RAMECC_REGISTER_CALLBACKS */

/**
  * @brief  Handles RAMECC interrupt request.
  * @param  hramecc  Pointer to a RAMECC_HandleTypeDef structure that contains
  *                  the configuration information for the specified RAMECC
  *                  Monitor.
  * @retval None.
  */
void HAL_RAMECC_IRQHandler(RAMECC_HandleTypeDef *hramecc)
{
  uint32_t ier_reg = ((RAMECC_TypeDef *)((uint32_t)hramecc->Instance & 0xFFFFFF00U))->IER;
  uint32_t cr_reg = hramecc->Instance->CR >> 1U;
  uint32_t sr_reg = hramecc->Instance->SR;

  /* Update global interrupt variables */
  if ((ier_reg & RAMECC_IER_GIE) == RAMECC_IER_GIE)
  {
    ier_reg = RAMECC_IT_GLOBAL_ALL;
  }

  /* Store the ECC Single error detected */
  if ((sr_reg & RAMECC_SR_SEDCF) == RAMECC_SR_SEDCF)
  {
    hramecc->RAMECCErrorCode |= HAL_RAMECC_SINGLEERROR_DETECTED;
  }

  /* Store the ECC double error detected */
  if ((sr_reg & (RAMECC_SR_DEDF | RAMECC_SR_DEBWDF)) != 0U)
  {
    hramecc->RAMECCErrorCode |= HAL_RAMECC_DOUBLEERROR_DETECTED;
  }

  /* Clear active flags */
  __HAL_RAMECC_CLEAR_FLAG (hramecc, (((ier_reg | cr_reg) & (sr_reg << 1U)) >> 1U));

  /* Check if a valid double error callback is registered */
#if (USE_HAL_RAMECC_REGISTER_CALLBACKS == 1)
  /* Check if a valid error callback is registered */
  if (hramecc->DetectErrorCallback != NULL)
  {
    /* Error detection callback */
    hramecc->DetectErrorCallback(hramecc);
  }
#else
  HAL_RAMECC_DetectErrorCallback(hramecc);
#endif /* USE_HAL_RAMECC_REGISTER_CALLBACKS */
}

/**
  * @brief  RAMECC error detection callback.
  * @param  hramecc : Pointer to a RAMECC_HandleTypeDef structure that contains
  *                   the configuration information for the specified RAMECC.
  * @retval None.
  */
__weak void HAL_RAMECC_DetectErrorCallback(RAMECC_HandleTypeDef *hramecc)
{
  /* Prevent unused argument(s) compilation warning */
  UNUSED(hramecc);

  /* NOTE : This function should not be modified, when the callback is needed,
            the HAL_RAMECC_DetectDoubleErrorCallback can be implemented in
            the user file.                                                    */
}

/**
  * @}
  */

/** @addtogroup RAMECC_Exported_Functions_Group4
  *
@verbatim
 ===============================================================================
                   #####  Error information functions  #####
 ===============================================================================
    [..]  This section provides functions allowing to:
      (+) Get failing address.
      (+) Get failing data low.
      (+) Get failing data high.
      (+) Get hamming bits injected.
      (+) Check single error flag.
      (+) Check double error flag.

@endverbatim
  * @{
  */

/**
  * @brief  Return the RAMECC failing address.
  * @param  hramecc  Pointer to a RAMECC_HandleTypeDef structure that contains
  *                  the configuration information for the specified RAMECC
  *                  Monitor.
  * @retval Failing address offset.
  */
uint32_t HAL_RAMECC_GetFailingAddress(RAMECC_HandleTypeDef *hramecc)
{
  /* Check the parameters */
  assert_param (IS_RAMECC_MONITOR_ALL_INSTANCE (hramecc->Instance));

  /* Return failing address */
  return hramecc->Instance->FAR;
}

/**
  * @brief  Return the RAMECC data low.
  * @param  hramecc  Pointer to a RAMECC_HandleTypeDef structure that contains
  *                  the configuration information for the specified RAMECC
  *                  Monitor.
  * @retval Failing data low.
  */
uint32_t HAL_RAMECC_GetFailingDataLow(RAMECC_HandleTypeDef *hramecc)
{
  /* Check the parameters */
  assert_param (IS_RAMECC_MONITOR_ALL_INSTANCE (hramecc->Instance));

  /* Return failing data low */
  return hramecc->Instance->FDRL;
}

/**
  * @brief  Return the RAMECC data high.
  * @param  hramecc  Pointer to a RAMECC_HandleTypeDef structure that contains
  *                  the configuration information for the specified RAMECC
  *                  Monitor.
  * @retval Failing data high.
  */
uint32_t HAL_RAMECC_GetFailingDataHigh(RAMECC_HandleTypeDef *hramecc)
{
  /* Check the parameters */
  assert_param (IS_RAMECC_MONITOR_ALL_INSTANCE (hramecc->Instance));

  /* Return failing data high */
  return hramecc->Instance->FDRH;
}

/**
  * @brief  Return the RAMECC Hamming bits injected.
  * @param  hramecc  Pointer to a RAMECC_HandleTypeDef structure that contains
  *                  the configuration information for the specified RAMECC
  *                  Monitor.
  * @retval Hamming bits injected.
  */
uint32_t HAL_RAMECC_GetHammingErrorCode(RAMECC_HandleTypeDef *hramecc)
{
  /* Check the parameters */
  assert_param (IS_RAMECC_MONITOR_ALL_INSTANCE (hramecc->Instance));

  /* Return hamming bits injected */
  return hramecc->Instance->FECR;
}

/**
  * @brief  Check if an ECC single error was occurred.
  * @param  hramecc  Pointer to a RAMECC_HandleTypeDef structure that contains
  *                  the configuration information for the specified RAMECC
  *                  Monitor.
  * @retval State of bit (1 or 0).
  */
uint32_t HAL_RAMECC_IsECCSingleErrorDetected(RAMECC_HandleTypeDef *hramecc)
{
  /* Check the parameters */
  assert_param (IS_RAMECC_MONITOR_ALL_INSTANCE (hramecc->Instance));

  /* Return the state of SEDC flag */
  return ((READ_BIT(hramecc->Instance->SR, RAMECC_SR_SEDCF) == (RAMECC_SR_SEDCF)) ? 1UL : 0UL);
}

/**
  * @brief  Check if an ECC double error was occurred.
  * @param  hramecc  Pointer to a RAMECC_HandleTypeDef structure that contains
  *                  the configuration information for the specified RAMECC
  *                  Monitor.
  * @retval State of bit (1 or 0).
  */
uint32_t HAL_RAMECC_IsECCDoubleErrorDetected(RAMECC_HandleTypeDef *hramecc)
{
  /* Check the parameters */
  assert_param (IS_RAMECC_MONITOR_ALL_INSTANCE (hramecc->Instance));

  /* Return the state of DEDF | DEBWDF flags */
  return ((READ_BIT(hramecc->Instance->SR, (RAMECC_SR_DEDF | RAMECC_SR_DEBWDF)) != 0U) ? 1UL : 0UL);
}

/**
  * @}
  */

/** @addtogroup RAMECC_Exported_Functions_Group5
  *
@verbatim
 ===============================================================================
                    ##### State and Error Functions  #####
 ===============================================================================
    [..]
    This section provides functions allowing to check and get the RAMECC state
    and the error code .
    [..]
    The HAL_RAMECC_GetState() function allows to get the RAMECC peripheral
    state.
    The HAL_RAMECC_GetError() function allows to Get the RAMECC peripheral error
    code.
    The HAL_RAMECC_GetRAMECCError() function allows to Get the RAMECC error code
	detected.

@endverbatim
  * @{
  */

/**
  * @brief  Get the RAMECC peripheral state.
  * @param  hramecc       : Pointer to a RAMECC_HandleTypeDef structure that
  *                         contains the configuration information for the
  *                         specified RAMECC instance.
  * @retval RAMECC state.
  */
HAL_RAMECC_StateTypeDef HAL_RAMECC_GetState(RAMECC_HandleTypeDef *hramecc)
{
  /* Return the RAMECC state */
  return hramecc->State;
}

/**
  * @brief  Get the RAMECC peripheral error code.
  * @param  hramecc       : Pointer to a RAMECC_HandleTypeDef structure that
  *                         contains the configuration information for the
  *                         specified RAMECC instance.
  * @retval RAMECC error code.
  */
uint32_t HAL_RAMECC_GetError(RAMECC_HandleTypeDef *hramecc)
{
  /* Return the RAMECC error code */
  return hramecc->ErrorCode;
}

/**
  * @brief  Get the RAMECC error code detected.
  * @param  hramecc       : Pointer to a RAMECC_HandleTypeDef structure that
  *                         contains the configuration information for the
  *                         specified RAMECC instance.
  * @retval RAMECC error code detected.
  */
uint32_t HAL_RAMECC_GetRAMECCError(RAMECC_HandleTypeDef *hramecc)
{
  /* Return the RAMECC error code detected*/
  return hramecc->RAMECCErrorCode;
}

/**
  * @}
  */
#endif /* HAL_RAMECC_MODULE_ENABLED */
/**
  * @}
  */

/**
  * @}
  */
