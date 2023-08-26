/**
  **********************************************************************************************************************
  * @file    stm32h5xx_hal_comp.c
  * @author  MCD Application Team
  * @brief   COMP HAL module driver.
  *          This file provides firmware functions to manage the following
  *          functionalities of the COMP peripheral:
  *           + Initialization and de-initialization functions
  *           + Peripheral control functions
  *           + Peripheral state functions
  **********************************************************************************************************************
  * @attention
  *
  * Copyright (c) 2023 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  **********************************************************************************************************************
  @verbatim
  ======================================================================================================================
                                     ##### COMP Peripheral features #####
  ======================================================================================================================

  [..]
      The STM32H5xx device family integrates one analog comparator instance: COMP1.
      (#) Comparators input minus (inverting input) and input plus (non inverting input)
          can be set to internal references or to GPIO pins
          (refer to GPIO list in reference manual).

      (#) Comparators output level is available using HAL_COMP_GetOutputLevel()
          and can be redirected to other peripherals: GPIO pins (in mode
          alternate functions for comparator), timers.
          (refer to GPIO list in reference manual).

      (#) The comparators have interrupt capability through direct line to NVIC (featuring
          low latency interrupt).
          Caution: Specific behavior for comparator of this STM32 series: comparator output triggers interruption
                   on high level
          - triggering on level (instead of edge) implies to disable interrupt in comparator IRQ handler.
            In case of further operation needed in interrupt mode, comparator interruption must be rearmed.
          - triggering on high level implies that comparator output initial state must at low level.
            Then, comparator can trig signal on rising edge.
            Trigger a signal on falling edge is possible by inverting comparator polarity.

  ======================================================================================================================
                                       ##### How to use this driver #####
  ======================================================================================================================
  [..]
      This driver provides functions to configure and program the comparator instances of
      STM32H5xx devices.

      To use the comparator, perform the following steps:

      (#)  Initialize the COMP low level resources by implementing the HAL_COMP_MspInit():
      (++) Configure the GPIO connected to comparator inputs plus and minus in analog mode
           using HAL_GPIO_Init().
      (++) If needed, configure the GPIO connected to comparator output in alternate function mode
           using HAL_GPIO_Init().
      (++) If required enable the COMP interrupt by configuring and enabling EXTI line in Interrupt mode and
           selecting the desired sensitivity level using HAL_GPIO_Init() function. After that enable the comparator
           interrupt vector using HAL_NVIC_EnableIRQ() function.

      (#) Configure the comparator using HAL_COMP_Init() function:
      (++) Select the input minus (inverting input)
      (++) Select the input plus (non-inverting input)
      (++) Select the hysteresis
      (++) Select the blanking source
      (++) Select the output polarity
      (++) Select the power mode
      -@@- HAL_COMP_Init() calls "HAL_COMP_MspInit()", COMP clock enable using system RCC
           must be implemented in this function.

      (#) Reconfiguration on-the-fly of comparator can be done by calling again
          function HAL_COMP_Init() with new input structure parameters values.

      (#) Enable the comparator using HAL_COMP_Start(), HAL_COMP_Start_IT_OneShot() or HAL_COMP_Start_IT_AutoRearm()
          Note: Using HAL_COMP_Start_IT_OneShot() or HAL_COMP_Start_IT_AutoRearm(), these functions can change
                comparator output polarity to match initial comparator output level constraint.
          Note: Using HAL_COMP_Start_IT_OneShot(), after each interruption triggered the interruption
                is disabled in IRQ handler. If needed, comparartor interruption can be rearmed by calling again
                start function.
          Note: In case of comparator and interruption used to exit from low power mode, user most ensure of stable
                comparator input voltage (risk would be that comparator trigs early and IT disabled in IRQ handler
                before device entering in low power mode, inducing no further system wake up possible).
                Most appropriate function is HAL_COMP_Start_IT_AutoRearm() because comparartor triggers remains enable,
                ensuring system wake up capability.

      (#) Use HAL_COMP_TriggerCallback() or HAL_COMP_GetOutputLevel() functions
          to manage comparator outputs (events and output level).

      (#) Disable the comparator using HAL_COMP_Stop() or HAL_COMP_Stop_IT() functions.

      (#) De-initialize the comparator using HAL_COMP_DeInit() function.

      (#) For safety purpose, comparator configuration can be locked using HAL_COMP_Lock() function.
          The only way to unlock the comparator is a device hardware reset.

    *** Callback registration ***
    =============================================
    [..]

     The compilation flag USE_HAL_COMP_REGISTER_CALLBACKS, when set to 1,
     allows the user to configure dynamically the driver callbacks.
     Use Functions HAL_COMP_RegisterCallback()
     to register an interrupt callback.
    [..]

     Function HAL_COMP_RegisterCallback() allows to register following callbacks:
       (+) TriggerCallback       : callback for COMP trigger.
       (+) MspInitCallback       : callback for Msp Init.
       (+) MspDeInitCallback     : callback for Msp DeInit.
     This function takes as parameters the HAL peripheral handle, the Callback ID
     and a pointer to the user callback function.
    [..]

     Use function HAL_COMP_UnRegisterCallback to reset a callback to the default
     weak function.
    [..]

     HAL_COMP_UnRegisterCallback takes as parameters the HAL peripheral handle,
     and the Callback ID.
     This function allows to reset following callbacks:
       (+) TriggerCallback       : callback for COMP trigger.
       (+) MspInitCallback       : callback for Msp Init.
       (+) MspDeInitCallback     : callback for Msp DeInit.
     [..]

     By default, after the HAL_COMP_Init() and when the state is HAL_COMP_STATE_RESET
     all callbacks are set to the corresponding weak functions:
     example HAL_COMP_TriggerCallback().
     Exception done for MspInit and MspDeInit functions that are
     reset to the legacy weak functions in the HAL_COMP_Init() / HAL_COMP_DeInit() only when
     these callbacks are null (not registered beforehand).
    [..]

     If MspInit or MspDeInit are not null, the HAL_COMP_Init() / HAL_COMP_DeInit()
     keep and use the user MspInit/MspDeInit callbacks (registered beforehand) whatever the state.
     [..]

     Callbacks can be registered/unregistered in HAL_COMP_STATE_READY state only.
     Exception done MspInit/MspDeInit functions that can be registered/unregistered
     in HAL_COMP_STATE_READY or HAL_COMP_STATE_RESET state,
     thus registered (user) MspInit/DeInit callbacks can be used during the Init/DeInit.
    [..]

     Then, the user first registers the MspInit/MspDeInit user callbacks
     using HAL_COMP_RegisterCallback() before calling HAL_COMP_DeInit()
     or HAL_COMP_Init() function.
     [..]

     When the compilation flag USE_HAL_COMP_REGISTER_CALLBACKS is set to 0 or
     not defined, the callback registration feature is not available and all callbacks
     are set to the corresponding weak functions.

  @endverbatim
  **********************************************************************************************************************
  */

/* Includes ----------------------------------------------------------------------------------------------------------*/
#include "stm32h5xx_hal.h"

/** @addtogroup STM32H5xx_HAL_Driver
  * @{
  */

#ifdef HAL_COMP_MODULE_ENABLED

#if defined (COMP1)

/** @defgroup COMP COMP
  * @brief COMP HAL module driver
  * @{
  */

/* Private typedef ---------------------------------------------------------------------------------------------------*/
/* Private define ----------------------------------------------------------------------------------------------------*/
/** @addtogroup COMP_Private_Constants
  * @{
  */

/* Delay for COMP startup time.                                               */
/* Note: Delay required to reach propagation delay specification.             */
/* Literal set to maximum value (refer to device datasheet,                   */
/* parameter "tSTART").                                                       */
/* Unit: us                                                                   */
#define COMP_DELAY_STARTUP_US          (80UL) /*!< Delay for COMP startup time */

/* Delay for COMP voltage scaler stabilization time.                          */
/* Literal set to maximum value (refer to device datasheet,                   */
/* parameter "tSTART_SCALER").                                                */
/* Unit: us                                                                   */
#define COMP_DELAY_VOLTAGE_SCALER_STAB_US (200UL)  /*!< Delay for COMP voltage scaler stabilization time */


/**
  * @}
  */

/* Private macro -----------------------------------------------------------------------------------------------------*/
/* Private variables -------------------------------------------------------------------------------------------------*/
/* Private function prototypes ---------------------------------------------------------------------------------------*/
/* Exported functions ------------------------------------------------------------------------------------------------*/

/** @defgroup COMP_Exported_Functions COMP Exported Functions
  * @{
  */

/** @defgroup COMP_Exported_Functions_Group1 Initialization/de-initialization functions
  *  @brief    Initialization and de-initialization functions.
  *
@verbatim
 =======================================================================================================================
                           ##### Initialization and de-initialization functions #####
 =======================================================================================================================
    [..]  This section provides functions to initialize and de-initialize comparators

@endverbatim
  * @{
  */

/**
  * @brief  Initialize the COMP according to the specified
  *         parameters in the COMP_InitTypeDef and initialize the associated handle.
  * @note   If the selected comparator is locked, initialization can't be performed.
  *         To unlock the configuration, perform a system reset.
  * @param  hcomp COMP handle
  * @retval HAL status
  */
HAL_StatusTypeDef HAL_COMP_Init(COMP_HandleTypeDef *hcomp)
{
  uint32_t tmp_csr;
  uint32_t exti_line;
  uint32_t comp_voltage_scaler_initialized; /* Value "0" if comparator voltage scaler is not initialized */
  __IO uint32_t wait_loop_index = 0UL;
  HAL_StatusTypeDef status = HAL_OK;

  /* Check the COMP handle allocation and lock status */
  if (hcomp == NULL)
  {
    status = HAL_ERROR;
  }
  else if (__HAL_COMP_IS_LOCKED(hcomp))
  {
    status = HAL_ERROR;
  }
  else
  {
    /* Check the parameters */
    assert_param(IS_COMP_ALL_INSTANCE(hcomp->Instance));
    assert_param(IS_COMP_INPUT_PLUS(hcomp->Instance, hcomp->Init.InputPlus));
    assert_param(IS_COMP_INPUT_MINUS(hcomp->Instance, hcomp->Init.InputMinus));
    assert_param(IS_COMP_OUTPUTPOL(hcomp->Init.OutputPol));
    assert_param(IS_COMP_POWERMODE(hcomp->Init.Mode));
    assert_param(IS_COMP_HYSTERESIS(hcomp->Init.Hysteresis));
    assert_param(IS_COMP_BLANKINGSRCE(hcomp->Init.BlankingSrce));
    assert_param(IS_COMP_TRIGGERMODE(hcomp->Init.TriggerMode));

    if (hcomp->State == HAL_COMP_STATE_RESET)
    {
      /* Allocate lock resource and initialize it */
      hcomp->Lock = HAL_UNLOCKED;

      /* Set COMP error code to none */
      COMP_CLEAR_ERRORCODE(hcomp);

      hcomp->InterruptAutoRearm = 0;

#if (USE_HAL_COMP_REGISTER_CALLBACKS == 1U)
      /* Init the COMP Callback settings */
      hcomp->TriggerCallback = HAL_COMP_TriggerCallback; /* Legacy weak callback */

      if (hcomp->MspInitCallback == NULL)
      {
        hcomp->MspInitCallback = HAL_COMP_MspInit; /* Legacy weak MspInit  */
      }

      /* Init the low level hardware */
      hcomp->MspInitCallback(hcomp);
#else
      /* Init the low level hardware */
      HAL_COMP_MspInit(hcomp);
#endif /* USE_HAL_COMP_REGISTER_CALLBACKS */
    }

    /* Memorize voltage scaler state before initialization */
    comp_voltage_scaler_initialized = READ_BIT(hcomp->Instance->CFGR1, COMP_CFGR1_SCALEN);

    /* Set COMP parameters */
    tmp_csr = (hcomp->Init.InputMinus
               | hcomp->Init.InputPlus
               | hcomp->Init.BlankingSrce
               | hcomp->Init.Hysteresis
               | hcomp->Init.OutputPol
               | hcomp->Init.Mode);

    /* Set parameters in COMP register */
    /* Note: Update all bits except read-only, lock and enable bits */
    MODIFY_REG(hcomp->Instance->CFGR1,
               COMP_CFGR1_PWRMODE | COMP_CFGR1_INMSEL | COMP_CFGR1_INPSEL1
               | COMP_CFGR1_INPSEL2 | COMP_CFGR1_POLARITY | COMP_CFGR1_HYST
               | COMP_CFGR1_BLANKING | COMP_CFGR1_BRGEN | COMP_CFGR1_SCALEN,
               tmp_csr
              );

    if (hcomp->Init.InputPlus == COMP_INPUT_PLUS_IO2)
    {
      MODIFY_REG(hcomp->Instance->CFGR2, COMP_CFGR2_INPSEL0, COMP_CFGR2_INPSEL0);
    }

    /* Delay for COMP scaler bridge voltage stabilization */
    /* Apply the delay if voltage scaler bridge is enabled for the first time */
    if ((READ_BIT(hcomp->Instance->CFGR1, COMP_CFGR1_SCALEN) != 0UL) &&
        (comp_voltage_scaler_initialized != 0UL))
    {
      /* Wait loop initialization and execution */
      /* Note: Variable divided by 2 to compensate partially              */
      /*       CPU processing cycles, scaling in us split to not          */
      /*       exceed 32 bits register capacity and handle low frequency. */
      wait_loop_index = ((COMP_DELAY_VOLTAGE_SCALER_STAB_US / 10UL) * ((SystemCoreClock / (100000UL * 2UL)) + 1UL));
      while (wait_loop_index != 0UL)
      {
        wait_loop_index--;
      }
    }

    /* Get the EXTI line corresponding to the selected COMP instance */
    exti_line = COMP_GET_EXTI_LINE(hcomp->Instance);

    /* Manage EXTI settings */
    if ((hcomp->Init.TriggerMode & COMP_EXTI_IT) != 0UL)
    {
      LL_EXTI_EnableIT_0_31(exti_line);
    }
    else
    {
      /* Disable EXTI interrupt mode */
      LL_EXTI_DisableIT_0_31(exti_line);
    }

    /* Set HAL COMP handle state */
    /* Note: Transition from state reset to state ready,                      */
    /*       otherwise (coming from state ready or busy) no state update.     */
    if (hcomp->State == HAL_COMP_STATE_RESET)
    {
      hcomp->State = HAL_COMP_STATE_READY;
    }
  }

  return status;
}

/**
  * @brief  DeInitialize the COMP peripheral.
  * @note   Deinitialization cannot be performed if the COMP configuration is locked.
  *         To unlock the configuration, perform a system reset.
  * @param  hcomp  COMP handle
  * @retval HAL status
  */
HAL_StatusTypeDef HAL_COMP_DeInit(COMP_HandleTypeDef *hcomp)
{
  HAL_StatusTypeDef status = HAL_OK;

  /* Check the COMP handle allocation and lock status */
  if (hcomp == NULL)
  {
    status = HAL_ERROR;
  }
  else if (__HAL_COMP_IS_LOCKED(hcomp))
  {
    status = HAL_ERROR;
  }
  else
  {
    /* Check the parameter */
    assert_param(IS_COMP_ALL_INSTANCE(hcomp->Instance));

    /* Set configuration register to reset value */
    WRITE_REG(hcomp->Instance->CFGR1, 0x00000000UL);

#if (USE_HAL_COMP_REGISTER_CALLBACKS == 1U)
    if (hcomp->MspDeInitCallback == NULL)
    {
      hcomp->MspDeInitCallback = HAL_COMP_MspDeInit; /* Legacy weak MspDeInit  */
    }

    /* DeInit the low level hardware */
    hcomp->MspDeInitCallback(hcomp);
#else
    /* DeInit the low level hardware */
    HAL_COMP_MspDeInit(hcomp);
#endif /* USE_HAL_COMP_REGISTER_CALLBACKS */

    /* Set HAL COMP handle state */
    hcomp->State = HAL_COMP_STATE_RESET;

    /* Release Lock */
    __HAL_UNLOCK(hcomp);
  }

  return status;
}

/**
  * @brief  Initialize the COMP MSP.
  * @param  hcomp COMP handle
  * @retval None
  */
__weak void HAL_COMP_MspInit(COMP_HandleTypeDef *hcomp)
{
  /* Prevent unused argument(s) compilation warning */
  UNUSED(hcomp);

  /* NOTE : This function should not be modified, when the callback is needed,
            the HAL_COMP_MspInit could be implemented in the user file
   */
}

/**
  * @brief  DeInitialize the COMP MSP.
  * @param  hcomp COMP handle
  * @retval None
  */
__weak void HAL_COMP_MspDeInit(COMP_HandleTypeDef *hcomp)
{
  /* Prevent unused argument(s) compilation warning */
  UNUSED(hcomp);

  /* NOTE : This function should not be modified, when the callback is needed,
            the HAL_COMP_MspDeInit could be implemented in the user file
   */
}

#if (USE_HAL_COMP_REGISTER_CALLBACKS == 1U)
/**
  * @brief  Register a User COMP Callback
  *         To be used instead of the weak predefined callback
  * @param  hcomp Pointer to a COMP_HandleTypeDef structure that contains
  *                the configuration information for the specified COMP.
  * @param  CallbackID ID of the callback to be registered
  *         This parameter can be one of the following values:
  *          @arg @ref HAL_COMP_TRIGGER_CB_ID Trigger callback ID
  *          @arg @ref HAL_COMP_MSPINIT_CB_ID MspInit callback ID
  *          @arg @ref HAL_COMP_MSPDEINIT_CB_ID MspDeInit callback ID
  * @param  pCallback pointer to the Callback function
  * @retval HAL status
  */
HAL_StatusTypeDef HAL_COMP_RegisterCallback(COMP_HandleTypeDef *hcomp, HAL_COMP_CallbackIDTypeDef CallbackID,
                                            pCOMP_CallbackTypeDef pCallback)
{
  HAL_StatusTypeDef status = HAL_OK;

  if (pCallback == NULL)
  {
    /* Update the error code */
    hcomp->ErrorCode |= HAL_COMP_ERROR_INVALID_CALLBACK;

    return HAL_ERROR;
  }

  if (HAL_COMP_STATE_READY == hcomp->State)
  {
    switch (CallbackID)
    {
      case HAL_COMP_TRIGGER_CB_ID :
        hcomp->TriggerCallback = pCallback;
        break;

      case HAL_COMP_MSPINIT_CB_ID :
        hcomp->MspInitCallback = pCallback;
        break;

      case HAL_COMP_MSPDEINIT_CB_ID :
        hcomp->MspDeInitCallback = pCallback;
        break;

      default :
        /* Update the error code */
        hcomp->ErrorCode |= HAL_COMP_ERROR_INVALID_CALLBACK;

        /* Return error status */
        status = HAL_ERROR;
        break;
    }
  }
  else if (HAL_COMP_STATE_RESET == hcomp->State)
  {
    switch (CallbackID)
    {
      case HAL_COMP_MSPINIT_CB_ID :
        hcomp->MspInitCallback = pCallback;
        break;

      case HAL_COMP_MSPDEINIT_CB_ID :
        hcomp->MspDeInitCallback = pCallback;
        break;

      default :
        /* Update the error code */
        hcomp->ErrorCode |= HAL_COMP_ERROR_INVALID_CALLBACK;

        /* Return error status */
        status = HAL_ERROR;
        break;
    }
  }
  else
  {
    /* Update the error code */
    hcomp->ErrorCode |= HAL_COMP_ERROR_INVALID_CALLBACK;

    /* Return error status */
    status =  HAL_ERROR;
  }

  return status;
}

/**
  * @brief  Unregister a COMP Callback
  *         COMP callback is redirected to the weak predefined callback
  * @param  hcomp Pointer to a COMP_HandleTypeDef structure that contains
  *                the configuration information for the specified COMP.
  * @param  CallbackID ID of the callback to be unregistered
  *         This parameter can be one of the following values:
  *          @arg @ref HAL_COMP_TRIGGER_CB_ID Trigger callback ID
  *          @arg @ref HAL_COMP_MSPINIT_CB_ID MspInit callback ID
  *          @arg @ref HAL_COMP_MSPDEINIT_CB_ID MspDeInit callback ID
  * @retval HAL status
  */
HAL_StatusTypeDef HAL_COMP_UnRegisterCallback(COMP_HandleTypeDef *hcomp, HAL_COMP_CallbackIDTypeDef CallbackID)
{
  HAL_StatusTypeDef status = HAL_OK;

  if (HAL_COMP_STATE_READY == hcomp->State)
  {
    switch (CallbackID)
    {
      case HAL_COMP_TRIGGER_CB_ID :
        hcomp->TriggerCallback = HAL_COMP_TriggerCallback;         /* Legacy weak callback */
        break;

      case HAL_COMP_MSPINIT_CB_ID :
        hcomp->MspInitCallback = HAL_COMP_MspInit;                 /* Legacy weak MspInit */
        break;

      case HAL_COMP_MSPDEINIT_CB_ID :
        hcomp->MspDeInitCallback = HAL_COMP_MspDeInit;             /* Legacy weak MspDeInit */
        break;

      default :
        /* Update the error code */
        hcomp->ErrorCode |= HAL_COMP_ERROR_INVALID_CALLBACK;

        /* Return error status */
        status =  HAL_ERROR;
        break;
    }
  }
  else if (HAL_COMP_STATE_RESET == hcomp->State)
  {
    switch (CallbackID)
    {
      case HAL_COMP_MSPINIT_CB_ID :
        hcomp->MspInitCallback = HAL_COMP_MspInit;                 /* Legacy weak MspInit */
        break;

      case HAL_COMP_MSPDEINIT_CB_ID :
        hcomp->MspDeInitCallback = HAL_COMP_MspDeInit;             /* Legacy weak MspDeInit */
        break;

      default :
        /* Update the error code */
        hcomp->ErrorCode |= HAL_COMP_ERROR_INVALID_CALLBACK;

        /* Return error status */
        status =  HAL_ERROR;
        break;
    }
  }
  else
  {
    /* Update the error code */
    hcomp->ErrorCode |= HAL_COMP_ERROR_INVALID_CALLBACK;

    /* Return error status */
    status =  HAL_ERROR;
  }

  return status;
}

#endif /* USE_HAL_COMP_REGISTER_CALLBACKS */

/**
  * @}
  */

/** @defgroup COMP_Exported_Functions_Group2 Start-Stop operation functions
  *  @brief   Start-Stop operation functions.
  *
@verbatim
 =======================================================================================================================
                                      ##### IO operation functions #####
 =======================================================================================================================
    [..]  This section provides functions allowing to:
      (+) Start a comparator instance.
      (+) Stop a comparator instance.

@endverbatim
  * @{
  */

/**
  * @brief  Start the comparator.
  * @param  hcomp COMP handle
  * @retval HAL status
  */
HAL_StatusTypeDef HAL_COMP_Start(COMP_HandleTypeDef *hcomp)
{
  __IO uint32_t wait_loop_index = 0UL;

  HAL_StatusTypeDef status = HAL_OK;

  /* Check the COMP handle allocation and lock status */
  if (hcomp == NULL)
  {
    status = HAL_ERROR;
  }
  else if (__HAL_COMP_IS_LOCKED(hcomp))
  {
    status = HAL_ERROR;
  }
  else
  {
    /* Check the parameter */
    assert_param(IS_COMP_ALL_INSTANCE(hcomp->Instance));

    if ((hcomp->Init.TriggerMode & COMP_EXTI_IT) != 0UL)
    {
      /* Case of operation with interruption */
      /* Note: Specific to comparator of this STM32 series featuring IT with direct line only (low latency) */
      status = HAL_COMP_Start_IT_AutoRearm(hcomp);
    }
    else
    {
      if (hcomp->State == HAL_COMP_STATE_READY)
      {
        /* Enable the selected comparator */
        SET_BIT(hcomp->Instance->CFGR1, COMP_CFGR1_EN);

        /* Set HAL COMP handle state */
        hcomp->State = HAL_COMP_STATE_BUSY;

        /* Delay for COMP startup time */
        /* Wait loop initialization and execution */
        /* Note: Variable divided by 2 to compensate partially              */
        /*       CPU processing cycles, scaling in us split to not          */
        /*       exceed 32 bits register capacity and handle low frequency. */
        wait_loop_index = ((COMP_DELAY_STARTUP_US / 10UL) * ((SystemCoreClock / (100000UL * 2UL)) + 1UL));
        while (wait_loop_index != 0UL)
        {
          wait_loop_index--;
        }
      }
      else
      {
        status = HAL_ERROR;
      }
    }
  }

  return status;
}

/**
  * @brief  Stop the comparator.
  * @param  hcomp COMP handle
  * @retval HAL status
  */
HAL_StatusTypeDef HAL_COMP_Stop(COMP_HandleTypeDef *hcomp)
{
  HAL_StatusTypeDef status = HAL_OK;

  /* Check the COMP handle allocation and lock status */
  if (hcomp == NULL)
  {
    status = HAL_ERROR;
  }
  else if (__HAL_COMP_IS_LOCKED(hcomp))
  {
    status = HAL_ERROR;
  }
  else
  {
    /* Check the parameter */
    assert_param(IS_COMP_ALL_INSTANCE(hcomp->Instance));

    /* Check compliant states: HAL_COMP_STATE_READY or HAL_COMP_STATE_BUSY    */
    /* (all states except HAL_COMP_STATE_RESET and except locked status.      */
    if (hcomp->State != HAL_COMP_STATE_RESET)
    {
      /* Disable the selected comparator */
      CLEAR_BIT(hcomp->Instance->CFGR1, COMP_CFGR1_EN);

      /* Set HAL COMP handle state */
      hcomp->State = HAL_COMP_STATE_READY;
    }
    else
    {
      status = HAL_ERROR;
    }
  }

  return status;
}

/**
  * @brief  Start the comparator with interruption low latency, interruption disabled at first trigger occurrence.
  * @note   Interruption low latency is achieved through direct line to NVIC (instead of going through EXTI).
  * @note   If needed, comparartor interruption can be rearmed by calling again this function.
  * @note   Specific to comparator of this STM32 series: comparator output triggers interruption on high level.
            This function can change output polarity depending on initial output level.
  * @param  hcomp COMP handle
  * @retval HAL status
  */
HAL_StatusTypeDef HAL_COMP_Start_IT_OneShot(COMP_HandleTypeDef *hcomp)
{
  __IO uint32_t wait_loop_index = 0UL;
  uint32_t polarity_toggle = 0U;
  HAL_StatusTypeDef status = HAL_OK;

  /* Check the COMP handle allocation and lock status */
  if (hcomp == NULL)
  {
    status = HAL_ERROR;
  }
  else if (__HAL_COMP_IS_LOCKED(hcomp))
  {
    status = HAL_ERROR;
  }
  else
  {
    /* Check the parameter */
    assert_param(IS_COMP_ALL_INSTANCE(hcomp->Instance));

    if (hcomp->State == HAL_COMP_STATE_READY)
    {
      /* Enable the selected comparator */
      SET_BIT(hcomp->Instance->CFGR1, COMP_CFGR1_EN);

      /* Set HAL COMP handle state */
      hcomp->State = HAL_COMP_STATE_BUSY;

      /* Delay for COMP startup time */
      /* Wait loop initialization and execution */
      /* Note: Variable divided by 2 to compensate partially              */
      /*       CPU processing cycles, scaling in us split to not          */
      /*       exceed 32 bits register capacity and handle low frequency. */
      wait_loop_index = ((COMP_DELAY_STARTUP_US / 10UL) * ((SystemCoreClock / (100000UL * 2UL)) + 1UL));
      while (wait_loop_index != 0UL)
      {
        wait_loop_index--;
      }

      /* Check whether initial comparator output level is compliant with interruption mode */
      if (hcomp->Init.TriggerMode == COMP_EXTI_FALLING)
      {
        if (HAL_COMP_GetOutputLevel(hcomp) != COMP_OUTPUT_LEVEL_HIGH)
        {
          polarity_toggle = 1U;
        }
      }
      else /* COMP_EXTI_RISING */
      {
        if (HAL_COMP_GetOutputLevel(hcomp) != COMP_OUTPUT_LEVEL_LOW)
        {
          polarity_toggle = 1U;
        }
      }

      if (polarity_toggle == 1U)
      {
        /* Toggle poarity */
        if (READ_BIT(hcomp->Instance->CFGR1, COMP_CFGR1_POLARITY) == 0UL)
        {
          SET_BIT(hcomp->Instance->CFGR1, COMP_CFGR1_POLARITY);
        }
        else
        {
          CLEAR_BIT(hcomp->Instance->CFGR1, COMP_CFGR1_POLARITY);
        }
      }

      /* Enable comparator interruption */
      hcomp->InterruptAutoRearm = 0U;
      __HAL_COMP_CLEAR_FLAG(COMP_CLEAR_C1IF);
      SET_BIT(hcomp->Instance->CFGR1, COMP_CFGR1_ITEN);
    }
    else
    {
      status = HAL_ERROR;
    }
  }

  return status;
}

/**
  * @brief  Start the comparator with interruption low latency, interruption rearmed at each trigger occurrence.
  * @note   Interruption low latency is achieved through direct line to NVIC (instead of going through EXTI).
  * @note   If needed, comparartor interruption can be rearmed by calling again this function.
  * @note   Specific to comparator of this STM32 series: comparator output triggers interruption on high level.
            This function can change output polarity depending on initial output level.
  * @param  hcomp COMP handle
  * @retval HAL status
  */
HAL_StatusTypeDef HAL_COMP_Start_IT_AutoRearm(COMP_HandleTypeDef *hcomp)
{
  __IO uint32_t wait_loop_index = 0UL;
  uint32_t polarity_toggle = 0U;
  HAL_StatusTypeDef status = HAL_OK;

  /* Check the COMP handle allocation and lock status */
  if (hcomp == NULL)
  {
    status = HAL_ERROR;
  }
  else if (__HAL_COMP_IS_LOCKED(hcomp))
  {
    status = HAL_ERROR;
  }
  else
  {
    /* Check the parameter */
    assert_param(IS_COMP_ALL_INSTANCE(hcomp->Instance));

    if (hcomp->State == HAL_COMP_STATE_READY)
    {
      /* Enable the selected comparator */
      SET_BIT(hcomp->Instance->CFGR1, COMP_CFGR1_EN);

      /* Set HAL COMP handle state */
      hcomp->State = HAL_COMP_STATE_BUSY;

      /* Delay for COMP startup time */
      /* Wait loop initialization and execution */
      /* Note: Variable divided by 2 to compensate partially              */
      /*       CPU processing cycles, scaling in us split to not          */
      /*       exceed 32 bits register capacity and handle low frequency. */
      wait_loop_index = ((COMP_DELAY_STARTUP_US / 10UL) * ((SystemCoreClock / (100000UL * 2UL)) + 1UL));
      while (wait_loop_index != 0UL)
      {
        wait_loop_index--;
      }

      /* Check whether initial comparator output level is compliant with interruption mode */
      if (hcomp->Init.TriggerMode == COMP_EXTI_FALLING)
      {
        if (HAL_COMP_GetOutputLevel(hcomp) != COMP_OUTPUT_LEVEL_HIGH)
        {
          polarity_toggle = 1U;
        }
      }
      else /* COMP_EXTI_RISING */
      {
        if (HAL_COMP_GetOutputLevel(hcomp) != COMP_OUTPUT_LEVEL_LOW)
        {
          polarity_toggle = 1U;
        }
      }

      if (polarity_toggle == 1U)
      {
        /* Toggle poarity */
        if (READ_BIT(hcomp->Instance->CFGR1, COMP_CFGR1_POLARITY) == 0UL)
        {
          SET_BIT(hcomp->Instance->CFGR1, COMP_CFGR1_POLARITY);
        }
        else
        {
          CLEAR_BIT(hcomp->Instance->CFGR1, COMP_CFGR1_POLARITY);
        }
      }

      /* Enable comparator interruption */
      hcomp->InterruptAutoRearm = 1U;
      __HAL_COMP_CLEAR_FLAG(COMP_CLEAR_C1IF);
      SET_BIT(hcomp->Instance->CFGR1, COMP_CFGR1_ITEN);
    }
    else
    {
      status = HAL_ERROR;
    }
  }

  return status;
}

/**
  * @brief  Disable the interrupt and Stop the comparator.
  * @param  hcomp COMP handle
  * @retval HAL status
  */
HAL_StatusTypeDef HAL_COMP_Stop_IT(COMP_HandleTypeDef *hcomp)
{
  HAL_StatusTypeDef status = HAL_OK;

  /* Check the COMP handle allocation and lock status */
  if (hcomp == NULL)
  {
    status = HAL_ERROR;
  }
  else if (__HAL_COMP_IS_LOCKED(hcomp))
  {
    status = HAL_ERROR;
  }
  else
  {
    /* Check the parameter */
    assert_param(IS_COMP_ALL_INSTANCE(hcomp->Instance));

    /* Check compliant states: HAL_COMP_STATE_READY or HAL_COMP_STATE_BUSY    */
    /* (all states except HAL_COMP_STATE_RESET and except locked status.      */
    if (hcomp->State != HAL_COMP_STATE_RESET)
    {
      /* Disable the selected comparator */
      CLEAR_BIT(hcomp->Instance->CFGR1, COMP_CFGR1_EN);

      /* Disable the EXTI Line interrupt mode */
      CLEAR_BIT(EXTI->IMR1, COMP_GET_EXTI_LINE(hcomp->Instance));

      /* Disable the Interrupt comparator */
      CLEAR_BIT(hcomp->Instance->CFGR1, COMP_CFGR1_ITEN);

      /* Set HAL COMP handle state */
      hcomp->State = HAL_COMP_STATE_READY;
    }
    else
    {
      status = HAL_ERROR;
    }
  }

  return status;
}

/**
  * @brief  Comparator IRQ handler.
  * @param  hcomp COMP handle
  * @retval None
  */
void HAL_COMP_IRQHandler(COMP_HandleTypeDef *hcomp)
{
  uint32_t polarity_toggle = 0U;

  /* Disable COMP interrupt */
  /* Note: Specific to comparator of this STM32 series: comparator output triggers interruption on high level. */
  __HAL_COMP_DISABLE_IT(hcomp, COMP_IT_EN);

  /* Clear COMP1 interrupt flag */
  __HAL_COMP_CLEAR_C1IFLAG();
  NVIC_ClearPendingIRQ(COMP1_IRQn);

  /* COMP trigger callback */
#if (USE_HAL_COMP_REGISTER_CALLBACKS == 1U)
  hcomp->TriggerCallback(hcomp);
#else
  HAL_COMP_TriggerCallback(hcomp);
#endif /* USE_HAL_COMP_REGISTER_CALLBACKS */

  if (hcomp->InterruptAutoRearm == 1U)
  {
    /* Check whether initial comparator output level is compliant with interruption mode */
    if (hcomp->Init.TriggerMode == COMP_EXTI_FALLING)
    {
      if (HAL_COMP_GetOutputLevel(hcomp) != COMP_OUTPUT_LEVEL_HIGH)
      {
        polarity_toggle = 1U;
      }
    }
    else /* COMP_EXTI_RISING */
    {
      if (HAL_COMP_GetOutputLevel(hcomp) != COMP_OUTPUT_LEVEL_LOW)
      {
        polarity_toggle = 1U;
      }
    }

    if (polarity_toggle == 1U)
    {
      /* Toggle poarity */
      if (READ_BIT(hcomp->Instance->CFGR1, COMP_CFGR1_POLARITY) == 0UL)
      {
        SET_BIT(hcomp->Instance->CFGR1, COMP_CFGR1_POLARITY);
      }
      else
      {
        CLEAR_BIT(hcomp->Instance->CFGR1, COMP_CFGR1_POLARITY);
      }
    }

    /* Enable COMP interrupt */
    __HAL_COMP_ENABLE_IT(hcomp, COMP_IT_EN);
  }
  else
  {
    /* Change COMP state */
    hcomp->State = HAL_COMP_STATE_READY;
  }
}

/**
  * @}
  */

/** @defgroup COMP_Exported_Functions_Group3 Peripheral Control functions
  *  @brief   Management functions.
  *
@verbatim
 =======================================================================================================================
                                   ##### Peripheral Control functions #####
 =======================================================================================================================
    [..]
    This subsection provides a set of functions allowing to control the comparators.

@endverbatim
  * @{
  */

/**
  * @brief  Lock the selected comparator configuration.
  * @note   A system reset is required to unlock the comparator configuration.
  * @param  hcomp COMP handle
  * @retval HAL status
  */
HAL_StatusTypeDef HAL_COMP_Lock(COMP_HandleTypeDef *hcomp)
{
  HAL_StatusTypeDef status = HAL_OK;

  /* Check the COMP handle allocation and lock status */
  if (hcomp == NULL)
  {
    status = HAL_ERROR;
  }
  else if (__HAL_COMP_IS_LOCKED(hcomp))
  {
    status = HAL_ERROR;
  }
  else
  {
    /* Check the parameter */
    assert_param(IS_COMP_ALL_INSTANCE(hcomp->Instance));

    /* Set HAL COMP handle state */
    switch (hcomp->State)
    {
      case HAL_COMP_STATE_RESET:
        hcomp->State = HAL_COMP_STATE_RESET_LOCKED;
        break;
      case HAL_COMP_STATE_READY:
        hcomp->State = HAL_COMP_STATE_READY_LOCKED;
        break;
      default: /* HAL_COMP_STATE_BUSY */
        hcomp->State = HAL_COMP_STATE_BUSY_LOCKED;
        break;
    }

    /* Set the lock bit corresponding to selected comparator */
    __HAL_COMP_LOCK(hcomp);
  }
  return status;
}

/**
  * @brief  Return the output level (high or low) of the selected comparator.
  * @note   The output level depends on the selected polarity.
  *         If the polarity is not inverted:
  *           - Comparator output is low when the input plus is at a lower
  *             voltage than the input minus
  *           - Comparator output is high when the input plus is at a higher
  *             voltage than the input minus
  *         If the polarity is inverted:
  *           - Comparator output is high when the input plus is at a lower
  *             voltage than the input minus
  *           - Comparator output is low when the input plus is at a higher
  *             voltage than the input minus
  * @note   Specific to comparator of this STM32 series: comparator output
  *         triggers interruption on high level. HAL_COMP_Start_x functions
  *         can change output polarity depending on initial output level.
  * @param  hcomp  COMP handle
  * @retval Returns the selected comparator output level:
  *         @arg @ref COMP_OUTPUT_LEVEL_LOW
  *         @arg @ref COMP_OUTPUT_LEVEL_HIGH
  *
  */
uint32_t HAL_COMP_GetOutputLevel(const COMP_HandleTypeDef *hcomp)
{
  /* Check the parameter */
  assert_param(IS_COMP_ALL_INSTANCE(hcomp->Instance));

  return (uint32_t)(READ_BIT(COMP1->SR, COMP_SR_C1VAL));
}

/**
  * @brief  Comparator trigger callback.
  * @param  hcomp COMP handle
  * @retval None
  */
__weak void HAL_COMP_TriggerCallback(COMP_HandleTypeDef *hcomp)
{
  /* Prevent unused argument(s) compilation warning */
  UNUSED(hcomp);

  /* NOTE : This function should not be modified, when the callback is needed,
            the HAL_COMP_TriggerCallback should be implemented in the user file
   */
}


/**
  * @}
  */

/** @defgroup COMP_Exported_Functions_Group4 Peripheral State functions
  *  @brief   Peripheral State functions.
  *
@verbatim
 =======================================================================================================================
                                      ##### Peripheral State functions #####
 =======================================================================================================================
    [..]
    This subsection permit to get in run-time the status of the peripheral.

@endverbatim
  * @{
  */

/**
  * @brief  Return the COMP handle state.
  * @param  hcomp  COMP handle
  * @retval HAL state
  */
HAL_COMP_StateTypeDef HAL_COMP_GetState(const COMP_HandleTypeDef *hcomp)
{
  /* Check the COMP handle allocation */
  if (hcomp == NULL)
  {
    return HAL_COMP_STATE_RESET;
  }

  /* Check the parameter */
  assert_param(IS_COMP_ALL_INSTANCE(hcomp->Instance));

  /* Return HAL COMP handle state */
  return hcomp->State;
}

/**
  * @brief  Return the COMP error code.
  * @param hcomp COMP handle
  * @retval COMP error code
  */
uint32_t HAL_COMP_GetError(const COMP_HandleTypeDef *hcomp)
{
  /* Check the parameters */
  assert_param(IS_COMP_ALL_INSTANCE(hcomp->Instance));

  return hcomp->ErrorCode;
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

#endif /* COMP1 */

#endif /* HAL_COMP_MODULE_ENABLED */

/**
  * @}
  */
