/**
  ******************************************************************************
  * @file    stm32h7xx_hal_ramecc.c
  * @author  MCD Application Team
  * @brief   RAMECC HAL module driver.
  *          This file provides firmware functions to manage the following
  *          functionalities of the RAM ECC monitoring (RAMECC) peripheral:
  *           + Initialization and de-initialization functions
  *           + Monitoring operation functions
  *           + Error informations functions
  @verbatim
  ==============================================================================
                        ##### How to use this driver #####
  ==============================================================================
  [..]
   (#) Enable and latch error informations through HAL_RAMECC_Init().

   (#) For a given Monitor, enable and disable interrupt through
       HAL_RAMECC_EnableNotifiaction().
       To enable a notification for a given RAMECC instance, use global interrupts.
       To enable a notification for only RAMECC monitor, use monitor interrupts.
       All possible notifications are defined in the driver header file under
       RAMECC_Interrupt group.

     *** Silent mode ***
     ===================
    [..]
          (+) Use HAL_RAMECC_StartMonitor() to start RAMECC latch failing information
              without enabling any notification.

     *** Interrupt mode ***
     ======================
    [..]
          (+) Use HAL_RAMECC_EnableNotifiaction() to enable interrupts for a given error.
          (+) Configure the RAMECC interrupt priority using HAL_NVIC_SetPriority().
          (+) Enable the RAMECC IRQ handler using HAL_NVIC_EnableIRQ().

     *** Failing informations ***
     ======================
    [..]
     (#) Use HAL_RAMECC_GetFailingAddress() function to return the RAMECC failing address.
     (#) Use HAL_RAMECC_GetFailingDataLow() function to return the RAMECC failing data low.
     (#) Use HAL_RAMECC_GetFailingDataHigh() function to return the RAMECC failing data high.
     (#) Use HAL_RAMECC_GetHammingErrorCode() function to return the RAMECC Hamming bits injected.

     *** RAMECC HAL driver macros list ***
     =============================================
     [..]
       Below the list of used macros in RAMECC HAL driver.

      (+) __HAL_RAMECC_ENABLE_IT  : Enable the specified ECCRAM Monitor interrupts.
      (+) __HAL_RAMECC_DISABLE_IT : Disable the specified ECCRAM Monitor interrupts.
      (+) __HAL_RAMECC_GET_FLAG   : Return the current RAMECC Monitor selected flag.
      (+) __HAL_RAMECC_CLEAR_FLAG : Clear the current RAMECC Monitor selected flag.

  @endverbatim
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; COPYRIGHT(c) 2017 STMicroelectronics.
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
/* Exported functions ---------------------------------------------------------*/
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
  if(hramecc == NULL)
  {
    return HAL_ERROR;
  }

  /* Check the parameters */
  assert_param(IS_RAMECC_MONITOR_ALL_INSTANCE(hramecc->Instance));

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
  __HAL_RAMECC_CLEAR_FLAG(hramecc, RAMECC_FLAGS_ALL);

  /* Update the RAMECC state */
  hramecc->State = HAL_RAMECC_STATE_READY;

  /* Clean callback */
  hramecc->DetectErrorCallback = NULL;

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
  if(hramecc == NULL)
  {
    return HAL_ERROR;
  }

  /* Check the parameters */
  assert_param(IS_RAMECC_MONITOR_ALL_INSTANCE(hramecc->Instance));

  /* Disable RAMECC monitor */
  hramecc->Instance->CR &= ~RAMECC_CR_ECCELEN;

  /* Disable all global interrupts */
  ((RAMECC_TypeDef *)((uint32_t)hramecc->Instance & 0xFFFFFF00U))->IER &= \
    ~(RAMECC_IER_GIE | RAMECC_IER_GECCSEIE | RAMECC_IER_GECCDEIE | RAMECC_IER_GECCDEBWIE);

  /* Disable all interrupts monitor  */
  hramecc->Instance->CR &= ~(RAMECC_CR_ECCSEIE | RAMECC_CR_ECCDEIE | RAMECC_CR_ECCDEBWIE);

  /* Clear RAMECC monitor flags */
  __HAL_RAMECC_CLEAR_FLAG(hramecc, RAMECC_FLAGS_ALL);

  /* Change RAMECC peripheral state */
  hramecc->State = HAL_RAMECC_STATE_RESET;

  /* Clean callback */
  hramecc->DetectErrorCallback = NULL;

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
      (+) Configure latching error informations.
      (+) Configure RAMECC Global/Monitor interrupts.
      (+) Register and Unregister RAMECC callbacks
      (+) Handle RAMECC interrupt request

@endverbatim
  * @{
  */

/**
  * @brief  Starts the RAMECC latching error informations.
  * @param  hramecc  Pointer to a RAMECC_HandleTypeDef structure that contains
  *                  the configuration information for the specified RAMECC
  *                  Monitor.
  * @retval HAL status.
  */
HAL_StatusTypeDef HAL_RAMECC_StartMonitor(RAMECC_HandleTypeDef *hramecc)
{
  /* Check the RAMECC peripheral handle */
  if(hramecc == NULL)
  {
    return HAL_ERROR;
  }

  /* Check the parameters */
  assert_param(IS_RAMECC_MONITOR_ALL_INSTANCE(hramecc->Instance));

  if(hramecc->State == HAL_RAMECC_STATE_READY)
  {
    /* Change RAMECC peripheral state */
    hramecc->State = HAL_RAMECC_STATE_BUSY;

    /* Enable RAMECC monitor */
    hramecc->Instance->CR |= RAMECC_CR_ECCELEN;
  }
  else
  {
    /* Change the RAMECC state */
    hramecc->State = HAL_RAMECC_STATE_ERROR;

    return HAL_ERROR;
  }

  return HAL_OK;
}


/**
  * @brief  Stop the RAMECC latching error informations.
  * @param  hramecc  Pointer to a RAMECC_HandleTypeDef structure that contains
  *                  the configuration information for the specified RAMECC
  *                  Monitor.
  * @retval HAL status.
  */
HAL_StatusTypeDef HAL_RAMECC_StopMonitor(RAMECC_HandleTypeDef *hramecc)
{
  /* Check the RAMECC peripheral handle */
  if(hramecc == NULL)
  {
    return HAL_ERROR;
  }

  /* Check the parameters */
  assert_param(IS_RAMECC_MONITOR_ALL_INSTANCE(hramecc->Instance));

  if(hramecc->State == HAL_RAMECC_STATE_BUSY)
  {
    /* Disable RAMECC monitor */
    hramecc->Instance->CR &= ~RAMECC_CR_ECCELEN;
  }
  else
  {
    /* Change the RAMECC state */
    hramecc->State = HAL_RAMECC_STATE_ERROR;

    return HAL_ERROR;
  }

  /* Change RAMECC peripheral state */
  hramecc->State = HAL_RAMECC_STATE_READY;

  return HAL_OK;
}


/**
  * @brief  Enable the RAMECC error interrupts.
  * @param  hramecc       Pointer to a RAMECC_HandleTypeDef structure that contains
  *                       the configuration information for the specified RAMECC
  *                       Monitor.
  * @param  Notifications  Select the notification.
  * @retval HAL status.
  */
HAL_StatusTypeDef HAL_RAMECC_EnableNotification(RAMECC_HandleTypeDef *hramecc, uint32_t Notifications)
{
  /* Check the RAMECC peripheral handle */
  if(hramecc == NULL)
  {
    return HAL_ERROR;
  }

  /* Get RAMECC monitor state */
  HAL_RAMECC_StateTypeDef state = hramecc->State;

  /* Check the parameters */
  assert_param(IS_RAMECC_MONITOR_ALL_INSTANCE(hramecc->Instance));
  assert_param(IS_RAMECC_INTERRUPT(Notifications));

  if((state == HAL_RAMECC_STATE_READY) || (state == HAL_RAMECC_STATE_BUSY))
  {
    /* Enable RAMECC interrupts */
    __HAL_RAMECC_ENABLE_IT(hramecc, Notifications);
  }
  else
  {
    /* Change the RAMECC state */
    hramecc->State = HAL_RAMECC_STATE_ERROR;

    return HAL_ERROR;
  }

  return HAL_OK;
}


/**
  * @brief  Disable the RAMECC error interrupts.
  * @param  hramecc       Pointer to a RAMECC_HandleTypeDef structure that contains
  *                       the configuration information for the specified RAMECC
  *                       Monitor.
  * @param  Notifications  Select the notification.
  * @retval HAL status.
  */
HAL_StatusTypeDef HAL_RAMECC_DisableNotification(RAMECC_HandleTypeDef *hramecc, uint32_t Notifications)
{
  /* Check the RAMECC peripheral handle */
  if(hramecc == NULL)
  {
    return HAL_ERROR;
  }

  /* Get RAMECC monitor state */
  HAL_RAMECC_StateTypeDef state = hramecc->State;

  /* Check the parameters */
  assert_param(IS_RAMECC_MONITOR_ALL_INSTANCE(hramecc->Instance));
  assert_param(IS_RAMECC_INTERRUPT(Notifications));

  if((state == HAL_RAMECC_STATE_READY) || (state == HAL_RAMECC_STATE_BUSY))
  {
    /* Disable RAMECC interrupts */
    __HAL_RAMECC_DISABLE_IT(hramecc, Notifications);
  }
  else
  {
    /* Change the RAMECC state */
    hramecc->State = HAL_RAMECC_STATE_ERROR;

    return HAL_ERROR;
  }

  return HAL_OK;
}


/**
  * @brief  Register callbacks.
  * @param  hramecc    Pointer to a RAMECC_HandleTypeDef structure that contains
  *                    the configuration information for the specified RAMECC
  *                    Monitor.
  * @param  pCallback  pointer to private callbacsk function which has pointer to
  *                    a RAMECC_HandleTypeDef structure as parameter.
  * @retval HAL status.
  */
HAL_StatusTypeDef HAL_RAMECC_RegisterCallback(RAMECC_HandleTypeDef *hramecc, void (* pCallback)(RAMECC_HandleTypeDef *_hramecc))
{
  /* Check the RAMECC peripheral handle */
  if(hramecc == NULL)
  {
    return HAL_ERROR;
  }

  /* Check the parameters */
  assert_param(IS_RAMECC_MONITOR_ALL_INSTANCE(hramecc->Instance));

  if(hramecc->State == HAL_RAMECC_STATE_READY)
  {
    hramecc->DetectErrorCallback = pCallback;
  }
  else
  {
    /* Change the RAMECC state */
    hramecc->State = HAL_RAMECC_STATE_ERROR;

    return HAL_ERROR;
  }

  return HAL_OK;
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
  /* Check the RAMECC peripheral handle */
  if(hramecc == NULL)
  {
    return HAL_ERROR;
  }

  /* Get RAMECC monitor state */
  HAL_RAMECC_StateTypeDef state = hramecc->State;

  /* Check the parameters */
  assert_param(IS_RAMECC_MONITOR_ALL_INSTANCE(hramecc->Instance));

  if((state == HAL_RAMECC_STATE_READY) || (state == HAL_RAMECC_STATE_BUSY))
  {
    hramecc->DetectErrorCallback = NULL;
  }
  else
  {
    /* Change the RAMECC state */
    hramecc->State = HAL_RAMECC_STATE_ERROR;

    return HAL_ERROR;
  }

  return HAL_OK;
}


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
  uint32_t sr_reg = hramecc->Instance->SR << 1U;

  /* Update gloabl interrupt variables */
  if((ier_reg & RAMECC_IER_GIE) == RAMECC_IER_GIE)
  {
    ier_reg = RAMECC_IT_GLOBAL_ALL;
  }

  /* Clear active flags */
  __HAL_RAMECC_CLEAR_FLAG(hramecc, (((ier_reg | cr_reg) & sr_reg) >> 1U));

  if(hramecc->DetectErrorCallback != NULL)
  {
    /* Error detection callback */
    hramecc->DetectErrorCallback(hramecc);
  }
}


/** @addtogroup RAMECC_Exported_Functions_Group3
  *
@verbatim
 ===============================================================================
                   #####  Error informations functions  #####
 ===============================================================================
    [..]  This section provides functions allowing to:
      (+) Get failing address.
      (+) Get failing data low.
      (+) Get failing data high.
      (+) Get Hamming bits injected.

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
  assert_param(IS_RAMECC_MONITOR_ALL_INSTANCE(hramecc->Instance));

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
  assert_param(IS_RAMECC_MONITOR_ALL_INSTANCE(hramecc->Instance));

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
  assert_param(IS_RAMECC_MONITOR_ALL_INSTANCE(hramecc->Instance));

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
  assert_param(IS_RAMECC_MONITOR_ALL_INSTANCE(hramecc->Instance));

  return hramecc->Instance->FECR;
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

/**
  * @}
  */

/**
  * @}
  */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
