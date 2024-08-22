/**
  ******************************************************************************
  * @file    stm32h7xx_hal_rtc.c
  * @author  MCD Application Team
  * @brief   RTC HAL module driver.
  *          This file provides firmware functions to manage the following
  *          functionalities of the Real-Time Clock (RTC) peripheral:
  *           + Initialization/de-initialization
  *           + Calendar (Time and Date) configuration
  *           + Alarms (Alarm A and Alarm B) configuration
  *           + WakeUp Timer configuration
  *           + TimeStamp configuration
  *           + Tampers configuration
  *           + Backup Data Registers configuration
  *           + RTC Tamper and TimeStamp Pins Selection
  *           + Interrupts and flags management
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
 ===============================================================================
                          ##### RTC Operating Condition #####
 ===============================================================================
  [..] The real-time clock (RTC) and the RTC backup registers can be powered
       from the VBAT voltage when the main VDD supply is powered off.
       To retain the content of the RTC backup registers and supply the RTC
       when VDD is turned off, VBAT pin can be connected to an optional
       standby voltage supplied by a battery or by another source.

                   ##### Backup Domain Reset #####
 ===============================================================================
  [..] The backup domain reset sets all RTC registers and the RCC_BDCR register
       to their reset values.
       A backup domain reset is generated when one of the following events occurs:
    (#) Software reset, triggered by setting the BDRST bit in the
        RCC Backup domain control register (RCC_BDCR).
    (#) VDD or VBAT power on, if both supplies have previously been powered off.
    (#) Tamper detection event resets all data backup registers.

                   ##### Backup Domain Access #####
 ===================================================================
  [..] After reset, the backup domain (RTC registers, RTC backup data
       registers and backup SRAM) is protected against possible unwanted write
       accesses.

  [..] To enable access to the RTC Domain and RTC registers, proceed as follows:
    (#) Call the function HAL_RCCEx_PeriphCLKConfig with RCC_PERIPHCLK_RTC for
        PeriphClockSelection and select RTCClockSelection (LSE, LSI or HSEdiv32)
    (#) Enable RTC Clock using the __HAL_RCC_RTC_ENABLE() macro.

                  ##### How to use RTC Driver #####
 ===================================================================
  [..]
    (+) Enable the RTC domain access (see description in the section above).
    (+) Configure the RTC Prescaler (Asynchronous and Synchronous) and RTC hour
        format using the HAL_RTC_Init() function.

  *** Time and Date configuration ***
  ===================================
  [..]
    (+) To configure the RTC Calendar (Time and Date) use the HAL_RTC_SetTime()
        and HAL_RTC_SetDate() functions.
    (+) To read the RTC Calendar, use the HAL_RTC_GetTime() and HAL_RTC_GetDate() functions.

  *** Alarm configuration ***
  ===========================
  [..]
    (+) To configure the RTC Alarm use the HAL_RTC_SetAlarm() function.
            You can also configure the RTC Alarm with interrupt mode using the
            HAL_RTC_SetAlarm_IT() function.
    (+) To read the RTC Alarm, use the HAL_RTC_GetAlarm() function.

                  ##### RTC and low power modes #####
 ===================================================================
  [..] The MCU can be woken up from a low power mode by an RTC alternate
       function.
  [..] The RTC alternate functions are the RTC alarms (Alarm A and Alarm B),
       RTC wakeup, RTC tamper event detection and RTC time stamp event detection.
       These RTC alternate functions can wake up the system from the Stop and
       Standby low power modes.
  [..] The system can also wake up from low power modes without depending
       on an external interrupt (Auto-wakeup mode), by using the RTC alarm
       or the RTC wakeup events.
  [..] The RTC provides a programmable time base for waking up from the
       Stop or Standby mode at regular intervals.
       Wakeup from STOP and STANDBY modes is possible only when the RTC clock source
       is LSE or LSI.

  *** Callback registration ***
  =============================================
  When The compilation define USE_HAL_RTC_REGISTER_CALLBACKS is set to 0 or
  not defined, the callback registration feature is not available and all callbacks
  are set to the corresponding weak functions. This is the recommended configuration
  in order to optimize memory/code consumption footprint/performances.

  The compilation define  USE_RTC_REGISTER_CALLBACKS when set to 1
  allows the user to configure dynamically the driver callbacks.
  Use Function HAL_RTC_RegisterCallback() to register an interrupt callback.

  Function HAL_RTC_RegisterCallback() allows to register following callbacks:
    (+) AlarmAEventCallback          : RTC Alarm A Event callback.
    (+) AlarmBEventCallback          : RTC Alarm B Event callback.
    (+) TimeStampEventCallback       : RTC TimeStamp Event callback.
    (+) WakeUpTimerEventCallback     : RTC WakeUpTimer Event callback.
    (+) Tamper1EventCallback         : RTC Tamper 1 Event callback.
    (+) Tamper2EventCallback         : RTC Tamper 2 Event callback.
    (+) Tamper3EventCallback         : RTC Tamper 3 Event callback.
    (+) MspInitCallback              : RTC MspInit callback.
    (+) MspDeInitCallback            : RTC MspDeInit callback.
  This function takes as parameters the HAL peripheral handle, the Callback ID
  and a pointer to the user callback function.

  Use function HAL_RTC_UnRegisterCallback() to reset a callback to the default
  weak function.
  HAL_RTC_UnRegisterCallback() takes as parameters the HAL peripheral handle,
  and the Callback ID.
  This function allows to reset following callbacks:
    (+) AlarmAEventCallback          : RTC Alarm A Event callback.
    (+) AlarmBEventCallback          : RTC Alarm B Event callback.
    (+) TimeStampEventCallback       : RTC TimeStamp Event callback.
    (+) WakeUpTimerEventCallback     : RTC WakeUpTimer Event callback.
    (+) Tamper1EventCallback         : RTC Tamper 1 Event callback.
    (+) Tamper2EventCallback         : RTC Tamper 2 Event callback.
    (+) Tamper3EventCallback         : RTC Tamper 3 Event callback.
    (+) MspInitCallback              : RTC MspInit callback.
    (+) MspDeInitCallback            : RTC MspDeInit callback.

  By default, after the HAL_RTC_Init() and when the state is HAL_RTC_STATE_RESET,
  all callbacks are set to the corresponding weak functions :
  examples AlarmAEventCallback(), WakeUpTimerEventCallback().
  Exception done for MspInit and MspDeInit callbacks that are reset to the legacy weak function
  in the HAL_RTC_Init()/HAL_RTC_DeInit() only when these callbacks are null
  (not registered beforehand).
  If not, MspInit or MspDeInit are not null, HAL_RTC_Init()/HAL_RTC_DeInit()
  keep and use the user MspInit/MspDeInit callbacks (registered beforehand)

  Callbacks can be registered/unregistered in HAL_RTC_STATE_READY state only.
  Exception done MspInit/MspDeInit that can be registered/unregistered
  in HAL_RTC_STATE_READY or HAL_RTC_STATE_RESET state,
  thus registered (user) MspInit/DeInit callbacks can be used during the Init/DeInit.
  In that case first register the MspInit/MspDeInit user callbacks
  using HAL_RTC_RegisterCallback() before calling HAL_RTC_DeInit()
  or HAL_RTC_Init() function.

  When The compilation define USE_HAL_RTC_REGISTER_CALLBACKS is set to 0 or
  not defined, the callback registration feature is not available and all callbacks
  are set to the corresponding weak functions.
   @endverbatim

  */

/* Includes ------------------------------------------------------------------*/
#include "stm32h7xx_hal.h"

/** @addtogroup STM32H7xx_HAL_Driver
  * @{
  */


/** @addtogroup RTC
  * @brief RTC HAL module driver
  * @{
  */

#ifdef HAL_RTC_MODULE_ENABLED

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
/* Exported functions --------------------------------------------------------*/

/** @addtogroup RTC_Exported_Functions
  * @{
  */

/** @addtogroup RTC_Exported_Functions_Group1
 *  @brief    Initialization and Configuration functions
 *
@verbatim
 ===============================================================================
              ##### Initialization and de-initialization functions #####
 ===============================================================================
   [..] This section provides functions allowing to initialize and configure the
         RTC Prescaler (Synchronous and Asynchronous), RTC Hour format, disable
         RTC registers Write protection, enter and exit the RTC initialization mode,
         RTC registers synchronization check and reference clock detection enable.
         (#) The RTC Prescaler is programmed to generate the RTC 1Hz time base.
             It is split into 2 programmable prescalers to minimize power consumption.
             (++) A 7-bit asynchronous prescaler and a 15-bit synchronous prescaler.
             (++) When both prescalers are used, it is recommended to configure the
                 asynchronous prescaler to a high value to minimize power consumption.
         (#) All RTC registers are Write protected. Writing to the RTC registers
             is enabled by writing a key into the Write Protection register, RTC_WPR.
         (#) To configure the RTC Calendar, user application should enter
             initialization mode. In this mode, the calendar counter is stopped
             and its value can be updated. When the initialization sequence is
             complete, the calendar restarts counting after 4 RTCCLK cycles.
         (#) To read the calendar through the shadow registers after Calendar
             initialization, calendar update or after wakeup from low power modes
             the software must first clear the RSF flag. The software must then
             wait until it is set again before reading the calendar, which means
             that the calendar registers have been correctly copied into the
             RTC_TR and RTC_DR shadow registers.The HAL_RTC_WaitForSynchro() function
             implements the above software sequence (RSF clear and RSF check).

@endverbatim
  * @{
  */

/**
  * @brief  Initialize the RTC peripheral
  * @param  hrtc RTC handle
  * @retval HAL status
  */
HAL_StatusTypeDef HAL_RTC_Init(RTC_HandleTypeDef *hrtc)
{
  HAL_StatusTypeDef status = HAL_ERROR;

  /* Check RTC handler */
  if(hrtc != NULL)
  {
    /* Check the parameters */
    assert_param(IS_RTC_ALL_INSTANCE(hrtc->Instance));
    assert_param(IS_RTC_HOUR_FORMAT(hrtc->Init.HourFormat));
    assert_param(IS_RTC_ASYNCH_PREDIV(hrtc->Init.AsynchPrediv));
    assert_param(IS_RTC_SYNCH_PREDIV(hrtc->Init.SynchPrediv));
    assert_param(IS_RTC_OUTPUT(hrtc->Init.OutPut));
    assert_param(IS_RTC_OUTPUT_REMAP(hrtc->Init.OutPutRemap));
    assert_param(IS_RTC_OUTPUT_POL(hrtc->Init.OutPutPolarity));
    assert_param(IS_RTC_OUTPUT_TYPE(hrtc->Init.OutPutType));
#if defined(TAMP)
    assert_param(IS_RTC_OUTPUT_PULLUP(hrtc->Init.OutPutPullUp));
#endif /* TAMP */

#if (USE_HAL_RTC_REGISTER_CALLBACKS == 1)
    if(hrtc->State == HAL_RTC_STATE_RESET)
    {
      /* Allocate lock resource and initialize it */
      hrtc->Lock = HAL_UNLOCKED;

      hrtc->AlarmAEventCallback          =  HAL_RTC_AlarmAEventCallback;             /* Legacy weak AlarmAEventCallback      */
      hrtc->AlarmBEventCallback          =  HAL_RTCEx_AlarmBEventCallback;           /* Legacy weak AlarmBEventCallback      */
      hrtc->TimeStampEventCallback       =  HAL_RTCEx_TimeStampEventCallback;        /* Legacy weak TimeStampEventCallback   */
      hrtc->WakeUpTimerEventCallback     =  HAL_RTCEx_WakeUpTimerEventCallback;      /* Legacy weak WakeUpTimerEventCallback */
      hrtc->Tamper1EventCallback         =  HAL_RTCEx_Tamper1EventCallback;          /* Legacy weak Tamper1EventCallback     */
      hrtc->Tamper2EventCallback         =  HAL_RTCEx_Tamper2EventCallback;          /* Legacy weak Tamper2EventCallback     */
      hrtc->Tamper3EventCallback         =  HAL_RTCEx_Tamper3EventCallback;          /* Legacy weak Tamper3EventCallback     */

#if defined(TAMP)
      hrtc->InternalTamper1EventCallback =  HAL_RTCEx_InternalTamper1EventCallback;
      hrtc->InternalTamper2EventCallback =  HAL_RTCEx_InternalTamper2EventCallback;
      hrtc->InternalTamper3EventCallback =  HAL_RTCEx_InternalTamper3EventCallback;
      hrtc->InternalTamper4EventCallback =  HAL_RTCEx_InternalTamper4EventCallback;
      hrtc->InternalTamper5EventCallback =  HAL_RTCEx_InternalTamper5EventCallback;
      hrtc->InternalTamper6EventCallback =  HAL_RTCEx_InternalTamper6EventCallback;
      hrtc->InternalTamper8EventCallback =  HAL_RTCEx_InternalTamper8EventCallback;
#endif /* TAMP */


      if(hrtc->MspInitCallback == NULL)
      {
        hrtc->MspInitCallback = HAL_RTC_MspInit;
      }
      /* Init the low level hardware */
      hrtc->MspInitCallback(hrtc);

      if(hrtc->MspDeInitCallback == NULL)
      {
        hrtc->MspDeInitCallback = HAL_RTC_MspDeInit;
      }
    }
#else /*  (USE_HAL_RTC_REGISTER_CALLBACKS == 1) */
    if(hrtc->State == HAL_RTC_STATE_RESET)
    {
      /* Allocate lock resource and initialize it */
      hrtc->Lock = HAL_UNLOCKED;

      /* Initialize RTC MSP */
      HAL_RTC_MspInit(hrtc);
    }
#endif /*  (USE_HAL_RTC_REGISTER_CALLBACKS == 1) */

    /* Set RTC state */
    hrtc->State = HAL_RTC_STATE_BUSY;

    /* Check whether the calendar needs to be initialized */
    if (__HAL_RTC_IS_CALENDAR_INITIALIZED(hrtc) == 0U)
    {
      /* Disable the write protection for RTC registers */
      __HAL_RTC_WRITEPROTECTION_DISABLE(hrtc);

     /* Enter Initialization mode */
      status = RTC_EnterInitMode(hrtc);
      if (status == HAL_OK)
      {
#if defined(TAMP)
        /* Clear RTC_CR FMT, OSEL, POL and TAMPOE Bits */
        hrtc->Instance->CR &= ~(RTC_CR_FMT | RTC_CR_POL | RTC_CR_OSEL | RTC_CR_TAMPOE);
#else
        /* Clear RTC_CR FMT, OSEL and POL Bits */
        hrtc->Instance->CR &= ~(RTC_CR_FMT | RTC_CR_OSEL | RTC_CR_POL);
#endif /* TAMP */

        /* Set RTC_CR register */
        hrtc->Instance->CR |= (hrtc->Init.HourFormat | hrtc->Init.OutPut | hrtc->Init.OutPutPolarity);

        /* Configure the RTC PRER */
        hrtc->Instance->PRER = (hrtc->Init.AsynchPrediv << RTC_PRER_PREDIV_A_Pos) | (hrtc->Init.SynchPrediv << RTC_PRER_PREDIV_S_Pos);

        /* Exit Initialization mode */
        status = RTC_ExitInitMode(hrtc);
      }
      if(status == HAL_OK)
      {
#if defined(TAMP)
        hrtc->Instance->CR &= ~(RTC_CR_TAMPALRM_PU | RTC_CR_TAMPALRM_TYPE | RTC_CR_OUT2EN);
        hrtc->Instance->CR |= (hrtc->Init.OutPutPullUp | hrtc->Init.OutPutType | hrtc->Init.OutPutRemap);
#else
        hrtc->Instance->OR &= ~(RTC_OR_ALARMOUTTYPE | RTC_OR_OUT_RMP);
        hrtc->Instance->OR |= (hrtc->Init.OutPutType | hrtc->Init.OutPutRemap);
#endif /* TAMP */
      }

    /* Enable the write protection for RTC registers */
    __HAL_RTC_WRITEPROTECTION_ENABLE(hrtc);
    }
    else
    {
      /* The calendar is already initialized */
      status = HAL_OK;
    }

    if (status == HAL_OK)
    {
      /* Set RTC state */
      hrtc->State = HAL_RTC_STATE_READY;
    }
  }

  /* return status */
  return status;
}

/**
  * @brief  DeInitialize the RTC peripheral.
  * @note   This function doesn't reset the RTC Backup Data registers.
  * @param  hrtc RTC handle
  * @retval HAL status
  */
HAL_StatusTypeDef HAL_RTC_DeInit(RTC_HandleTypeDef *hrtc)
{
  HAL_StatusTypeDef status = HAL_ERROR;
  uint32_t          tickstart;

  /* Check RTC handler */
  if(hrtc != NULL)
  {
    /* Check the parameters */
    assert_param(IS_RTC_ALL_INSTANCE(hrtc->Instance));

    /* Set RTC state */
    hrtc->State = HAL_RTC_STATE_BUSY;

    /* Disable the write protection for RTC registers */
    __HAL_RTC_WRITEPROTECTION_DISABLE(hrtc);

    /* Enter Initialization mode */
    status = RTC_EnterInitMode(hrtc);

    if (status == HAL_OK)
    {
      /* Reset TR, DR and CR registers */
      hrtc->Instance->TR = 0x00000000U;
      hrtc->Instance->DR = ((uint32_t)(RTC_DR_WDU_0 | RTC_DR_MU_0 | RTC_DR_DU_0));

      /* Reset All CR bits except CR[2:0] (which cannot be written before bit
           WUTE of CR is cleared) */
      hrtc->Instance->CR = 0x00000000U;

      /* Wait till WUTWF is set (to be able to reset CR[2:0] and WUTR) and if
         timeout is reached exit */
      tickstart = HAL_GetTick();

#if defined(TAMP)
      while ((((hrtc->Instance->ICSR) & RTC_ICSR_WUTWF) == 0U) && (status != HAL_TIMEOUT))
#else
      while ((((hrtc->Instance->ISR)  & RTC_ISR_WUTWF)  == 0U) && (status != HAL_TIMEOUT))
#endif /* TAMP */
      {
        if((HAL_GetTick() - tickstart) > RTC_TIMEOUT_VALUE)
        {
          /* Enable the write protection for RTC registers */
          __HAL_RTC_WRITEPROTECTION_ENABLE(hrtc);

          /* Set RTC state */
          hrtc->State = HAL_RTC_STATE_TIMEOUT;
          status = HAL_TIMEOUT;

        }
      }
    }

    if (status == HAL_OK)
    {
      /* Reset RTC CR register bits [2:0] */
      hrtc->Instance->CR = 0x00000000U;

      /* Reset other RTC registers */
      hrtc->Instance->WUTR     = RTC_WUTR_WUT;
      hrtc->Instance->PRER     = ((uint32_t)(RTC_PRER_PREDIV_A | 0x000000FFU));
      hrtc->Instance->ALRMAR   = 0x00000000U;
      hrtc->Instance->ALRMBR   = 0x00000000U;
      hrtc->Instance->SHIFTR   = 0x00000000U;
      hrtc->Instance->CALR     = 0x00000000U;
      hrtc->Instance->ALRMASSR = 0x00000000U;
      hrtc->Instance->ALRMBSSR = 0x00000000U;

      /* Exit initialization mode */
      status = RTC_ExitInitMode(hrtc);
    }

    if(status == HAL_OK)
    {
#if defined(TAMP)
      /* Reset TAMP registers */
      ((TAMP_TypeDef *)((uint32_t)hrtc->Instance + TAMP_OFFSET))->CR1 = 0xFFFF0000U;
      ((TAMP_TypeDef *)((uint32_t)hrtc->Instance + TAMP_OFFSET))->CR2 = 0x00000000U;
#else
      /* Reset Tamper configuration register */
      hrtc->Instance->TAMPCR = 0x00000000U;

      /* Reset Option register */
      hrtc->Instance->OR = 0x00000000U;
#endif /* TAMP */

      /* Enable the write protection for RTC registers */
      __HAL_RTC_WRITEPROTECTION_ENABLE(hrtc);

#if (USE_HAL_RTC_REGISTER_CALLBACKS == 1)
      if(hrtc->MspDeInitCallback == NULL)
      {
        hrtc->MspDeInitCallback = HAL_RTC_MspDeInit;
      }

      /* DeInit the low level hardware: CLOCK, NVIC.*/
      hrtc->MspDeInitCallback(hrtc);
#else
      /* De-Initialize RTC MSP */
      HAL_RTC_MspDeInit(hrtc);
#endif /* (USE_HAL_RTC_REGISTER_CALLBACKS) */

      hrtc->State = HAL_RTC_STATE_RESET;

      /* Release Lock */
      __HAL_UNLOCK(hrtc);
    }
  }

  /* return status */
  return status;
}

#if (USE_HAL_RTC_REGISTER_CALLBACKS == 1)
/**
  * @brief  Register a User RTC Callback
  *         To be used instead of the weak predefined callback
  * @param  hrtc RTC handle
  * @param  CallbackID ID of the callback to be registered
  *         This parameter can be one of the following values:
  *          @arg @ref HAL_RTC_ALARM_A_EVENT_CB_ID          Alarm A Event Callback ID
  *          @arg @ref HAL_RTC_ALARM_B_EVENT_CB_ID          Alarm B Event Callback ID
  *          @arg @ref HAL_RTC_TIMESTAMP_EVENT_CB_ID        TimeStamp Event Callback ID
  *          @arg @ref HAL_RTC_WAKEUPTIMER_EVENT_CB_ID      WakeUp Timer Event Callback ID
  *          @arg @ref HAL_RTC_TAMPER1_EVENT_CB_ID          Tamper 1 Callback ID
  *          @arg @ref HAL_RTC_TAMPER2_EVENT_CB_ID          Tamper 2 Callback ID
  *          @arg @ref HAL_RTC_TAMPER3_EVENT_CB_ID          Tamper 3 Callback ID
  *          @arg @ref HAL_RTC_INTERNAL_TAMPER1_EVENT_CB_ID Internal Tamper 1 Callback ID
  *          @arg @ref HAL_RTC_INTERNAL_TAMPER2_EVENT_CB_ID Internal Tamper 2 Callback ID
  *          @arg @ref HAL_RTC_INTERNAL_TAMPER3_EVENT_CB_ID Internal Tamper 3 Callback ID
  *          @arg @ref HAL_RTC_INTERNAL_TAMPER4_EVENT_CB_ID Internal Tamper 4 Callback ID
  *          @arg @ref HAL_RTC_INTERNAL_TAMPER5_EVENT_CB_ID Internal Tamper 5 Callback ID
  *          @arg @ref HAL_RTC_INTERNAL_TAMPER6_EVENT_CB_ID Internal Tamper 6 Callback ID
  *          @arg @ref HAL_RTC_INTERNAL_TAMPER8_EVENT_CB_ID Internal Tamper 8 Callback ID
  *          @arg @ref HAL_RTC_MSPINIT_CB_ID                Msp Init callback ID
  *          @arg @ref HAL_RTC_MSPDEINIT_CB_ID              Msp DeInit callback ID
  * @param  pCallback pointer to the Callback function
  * @retval HAL status
  */
HAL_StatusTypeDef HAL_RTC_RegisterCallback(RTC_HandleTypeDef *hrtc, HAL_RTC_CallbackIDTypeDef CallbackID, pRTC_CallbackTypeDef pCallback)
{
  HAL_StatusTypeDef status = HAL_OK;

  if(pCallback == NULL)
  {
    return HAL_ERROR;
  }

  /* Process locked */
  __HAL_LOCK(hrtc);

  if(HAL_RTC_STATE_READY == hrtc->State)
  {
    switch (CallbackID)
    {
      case HAL_RTC_ALARM_A_EVENT_CB_ID :
        hrtc->AlarmAEventCallback = pCallback;
        break;

      case HAL_RTC_ALARM_B_EVENT_CB_ID :
        hrtc->AlarmBEventCallback = pCallback;
        break;

      case HAL_RTC_TIMESTAMP_EVENT_CB_ID :
        hrtc->TimeStampEventCallback = pCallback;
        break;

      case HAL_RTC_WAKEUPTIMER_EVENT_CB_ID :
        hrtc->WakeUpTimerEventCallback = pCallback;
        break;

      case HAL_RTC_TAMPER1_EVENT_CB_ID :
        hrtc->Tamper1EventCallback = pCallback;
        break;

      case HAL_RTC_TAMPER2_EVENT_CB_ID :
        hrtc->Tamper2EventCallback = pCallback;
        break;

      case HAL_RTC_TAMPER3_EVENT_CB_ID :
        hrtc->Tamper3EventCallback = pCallback;
        break;

#if defined(TAMP)
      case HAL_RTC_INTERNAL_TAMPER1_EVENT_CB_ID :
        hrtc->InternalTamper1EventCallback =  pCallback;
        break;

      case HAL_RTC_INTERNAL_TAMPER2_EVENT_CB_ID :
        hrtc->InternalTamper2EventCallback =  pCallback;
        break;

      case HAL_RTC_INTERNAL_TAMPER3_EVENT_CB_ID :
        hrtc->InternalTamper3EventCallback =  pCallback;
        break;

      case HAL_RTC_INTERNAL_TAMPER4_EVENT_CB_ID :
        hrtc->InternalTamper4EventCallback =  pCallback;
        break;

      case HAL_RTC_INTERNAL_TAMPER5_EVENT_CB_ID :
        hrtc->InternalTamper5EventCallback =  pCallback;
        break;

      case HAL_RTC_INTERNAL_TAMPER6_EVENT_CB_ID :
        hrtc->InternalTamper6EventCallback =  pCallback;
        break;

      case HAL_RTC_INTERNAL_TAMPER8_EVENT_CB_ID :
        hrtc->InternalTamper8EventCallback =  pCallback;
        break;
#endif /* TAMP */

      case HAL_RTC_MSPINIT_CB_ID :
        hrtc->MspInitCallback = pCallback;
        break;

      case HAL_RTC_MSPDEINIT_CB_ID :
        hrtc->MspDeInitCallback = pCallback;
        break;

      default :
        /* Return error status */
        status =  HAL_ERROR;
        break;
    }
  }
  else if(HAL_RTC_STATE_RESET == hrtc->State)
  {
    switch (CallbackID)
    {
      case HAL_RTC_MSPINIT_CB_ID :
        hrtc->MspInitCallback = pCallback;
        break;

      case HAL_RTC_MSPDEINIT_CB_ID :
        hrtc->MspDeInitCallback = pCallback;
        break;

      default :
        /* Return error status */
        status =  HAL_ERROR;
        break;
    }
  }
  else
  {
    /* Return error status */
    status =  HAL_ERROR;
  }

  /* Release Lock */
  __HAL_UNLOCK(hrtc);

  return status;
}

/**
  * @brief  Unregister an RTC Callback
  *         RTC callback is redirected to the weak predefined callback
  * @param  hrtc RTC handle
  * @param  CallbackID ID of the callback to be unregistered
  *         This parameter can be one of the following values:
  *          @arg @ref HAL_RTC_ALARM_A_EVENT_CB_ID          Alarm A Event Callback ID
  *          @arg @ref HAL_RTC_ALARM_B_EVENT_CB_ID          Alarm B Event Callback ID
  *          @arg @ref HAL_RTC_TIMESTAMP_EVENT_CB_ID        TimeStamp Event Callback ID
  *          @arg @ref HAL_RTC_WAKEUPTIMER_EVENT_CB_ID      WakeUp Timer Event Callback ID
  *          @arg @ref HAL_RTC_TAMPER1_EVENT_CB_ID          Tamper 1 Callback ID
  *          @arg @ref HAL_RTC_TAMPER2_EVENT_CB_ID          Tamper 2 Callback ID
  *          @arg @ref HAL_RTC_TAMPER3_EVENT_CB_ID          Tamper 3 Callback ID
  *          @arg @ref HAL_RTC_INTERNAL_TAMPER1_EVENT_CB_ID Internal Tamper 1 Callback ID
  *          @arg @ref HAL_RTC_INTERNAL_TAMPER2_EVENT_CB_ID Internal Tamper 2 Callback ID
  *          @arg @ref HAL_RTC_INTERNAL_TAMPER3_EVENT_CB_ID Internal Tamper 3 Callback ID
  *          @arg @ref HAL_RTC_INTERNAL_TAMPER4_EVENT_CB_ID Internal Tamper 4 Callback ID
  *          @arg @ref HAL_RTC_INTERNAL_TAMPER5_EVENT_CB_ID Internal Tamper 5 Callback ID
  *          @arg @ref HAL_RTC_INTERNAL_TAMPER6_EVENT_CB_ID Internal Tamper 6 Callback ID
  *          @arg @ref HAL_RTC_INTERNAL_TAMPER8_EVENT_CB_ID Internal Tamper 8 Callback ID
  *          @arg @ref HAL_RTC_MSPINIT_CB_ID Msp Init callback ID
  *          @arg @ref HAL_RTC_MSPDEINIT_CB_ID Msp DeInit callback ID
  * @retval HAL status
  */
HAL_StatusTypeDef HAL_RTC_UnRegisterCallback(RTC_HandleTypeDef *hrtc, HAL_RTC_CallbackIDTypeDef CallbackID)
{
  HAL_StatusTypeDef status = HAL_OK;

  /* Process locked */
  __HAL_LOCK(hrtc);

  if(HAL_RTC_STATE_READY == hrtc->State)
  {
    switch (CallbackID)
    {
      case HAL_RTC_ALARM_A_EVENT_CB_ID :
        hrtc->AlarmAEventCallback = HAL_RTC_AlarmAEventCallback;             /* Legacy weak AlarmAEventCallback    */
        break;

      case HAL_RTC_ALARM_B_EVENT_CB_ID :
        hrtc->AlarmBEventCallback = HAL_RTCEx_AlarmBEventCallback;           /* Legacy weak AlarmBEventCallback */
        break;

      case HAL_RTC_TIMESTAMP_EVENT_CB_ID :
        hrtc->TimeStampEventCallback = HAL_RTCEx_TimeStampEventCallback;     /* Legacy weak TimeStampEventCallback    */
        break;

      case HAL_RTC_WAKEUPTIMER_EVENT_CB_ID :
        hrtc->WakeUpTimerEventCallback = HAL_RTCEx_WakeUpTimerEventCallback; /* Legacy weak WakeUpTimerEventCallback */
        break;

      case HAL_RTC_TAMPER1_EVENT_CB_ID :
        hrtc->Tamper1EventCallback = HAL_RTCEx_Tamper1EventCallback;         /* Legacy weak Tamper1EventCallback   */
        break;

      case HAL_RTC_TAMPER2_EVENT_CB_ID :
        hrtc->Tamper2EventCallback = HAL_RTCEx_Tamper2EventCallback;         /* Legacy weak Tamper2EventCallback         */
        break;

      case HAL_RTC_TAMPER3_EVENT_CB_ID :
        hrtc->Tamper3EventCallback = HAL_RTCEx_Tamper3EventCallback;         /* Legacy weak Tamper3EventCallback         */
        break;

#if defined(TAMP)
      case HAL_RTC_INTERNAL_TAMPER1_EVENT_CB_ID :
        hrtc->InternalTamper1EventCallback =  HAL_RTCEx_InternalTamper1EventCallback;
        break;

      case HAL_RTC_INTERNAL_TAMPER2_EVENT_CB_ID :
        hrtc->InternalTamper2EventCallback =  HAL_RTCEx_InternalTamper2EventCallback;
        break;

      case HAL_RTC_INTERNAL_TAMPER3_EVENT_CB_ID :
        hrtc->InternalTamper3EventCallback =  HAL_RTCEx_InternalTamper3EventCallback;
        break;

      case HAL_RTC_INTERNAL_TAMPER4_EVENT_CB_ID :
        hrtc->InternalTamper4EventCallback =  HAL_RTCEx_InternalTamper4EventCallback;
        break;

      case HAL_RTC_INTERNAL_TAMPER5_EVENT_CB_ID :
        hrtc->InternalTamper5EventCallback =  HAL_RTCEx_InternalTamper5EventCallback;
        break;

      case HAL_RTC_INTERNAL_TAMPER6_EVENT_CB_ID :
        hrtc->InternalTamper6EventCallback =  HAL_RTCEx_InternalTamper6EventCallback;
        break;

      case HAL_RTC_INTERNAL_TAMPER8_EVENT_CB_ID :
        hrtc->InternalTamper8EventCallback =  HAL_RTCEx_InternalTamper8EventCallback;
        break;
#endif /* TAMP */

      case HAL_RTC_MSPINIT_CB_ID :
        hrtc->MspInitCallback = HAL_RTC_MspInit;
        break;

      case HAL_RTC_MSPDEINIT_CB_ID :
        hrtc->MspDeInitCallback = HAL_RTC_MspDeInit;
        break;

      default :
        /* Return error status */
        status =  HAL_ERROR;
        break;
    }
  }
  else if(HAL_RTC_STATE_RESET == hrtc->State)
  {
    switch (CallbackID)
    {
      case HAL_RTC_MSPINIT_CB_ID :
        hrtc->MspInitCallback = HAL_RTC_MspInit;
        break;

      case HAL_RTC_MSPDEINIT_CB_ID :
        hrtc->MspDeInitCallback = HAL_RTC_MspDeInit;
        break;

      default :
        /* Return error status */
        status =  HAL_ERROR;
        break;
    }
  }
  else
  {
    /* Return error status */
    status =  HAL_ERROR;
  }

  /* Release Lock */
  __HAL_UNLOCK(hrtc);

  return status;
}
#endif /* USE_HAL_RTC_REGISTER_CALLBACKS */

/**
  * @brief  Initialize the RTC MSP.
  * @param  hrtc RTC handle
  * @retval None
  */
__weak void HAL_RTC_MspInit(RTC_HandleTypeDef *hrtc)
{
  /* Prevent unused argument(s) compilation warning */
  UNUSED(hrtc);

  /* NOTE : This function should not be modified, when the callback is needed,
            the HAL_RTC_MspInit could be implemented in the user file
   */
}

/**
  * @brief  DeInitialize the RTC MSP.
  * @param  hrtc RTC handle
  * @retval None
  */
__weak void HAL_RTC_MspDeInit(RTC_HandleTypeDef *hrtc)
{
  /* Prevent unused argument(s) compilation warning */
  UNUSED(hrtc);

  /* NOTE : This function should not be modified, when the callback is needed,
            the HAL_RTC_MspDeInit could be implemented in the user file
   */
}

/**
  * @}
  */

/** @addtogroup RTC_Exported_Functions_Group2
 *  @brief   RTC Time and Date functions
 *
@verbatim
 ===============================================================================
                 ##### RTC Time and Date functions #####
 ===============================================================================

 [..] This section provides functions allowing to configure Time and Date features

@endverbatim
  * @{
  */

/**
  * @brief  Set RTC current time.
  * @param  hrtc RTC handle
  * @param  sTime Pointer to Time structure
  * @param  Format Specifies the format of the entered parameters.
  *          This parameter can be one of the following values:
  *            @arg RTC_FORMAT_BIN: Binary data format
  *            @arg RTC_FORMAT_BCD: BCD data format
  * @retval HAL status
  */
HAL_StatusTypeDef HAL_RTC_SetTime(RTC_HandleTypeDef *hrtc, RTC_TimeTypeDef *sTime, uint32_t Format)
{
  uint32_t tmpreg;
HAL_StatusTypeDef status;

  /* Check the parameters */
  assert_param(IS_RTC_FORMAT(Format));
  assert_param(IS_RTC_DAYLIGHT_SAVING(sTime->DayLightSaving));
  assert_param(IS_RTC_STORE_OPERATION(sTime->StoreOperation));

  /* Process Locked */
  __HAL_LOCK(hrtc);

  hrtc->State = HAL_RTC_STATE_BUSY;

  /* Disable the write protection for RTC registers */
  __HAL_RTC_WRITEPROTECTION_DISABLE(hrtc);
 /* Enter Initialization mode */
  status = RTC_EnterInitMode(hrtc);
  if (status == HAL_OK)
  {
    if(Format == RTC_FORMAT_BIN)
    {
      if((hrtc->Instance->CR & RTC_CR_FMT) != 0U)
      {
        assert_param(IS_RTC_HOUR12(sTime->Hours));
        assert_param(IS_RTC_HOURFORMAT12(sTime->TimeFormat));
      }
      else
      {
        sTime->TimeFormat = 0x00U;
        assert_param(IS_RTC_HOUR24(sTime->Hours));
      }
      assert_param(IS_RTC_MINUTES(sTime->Minutes));
      assert_param(IS_RTC_SECONDS(sTime->Seconds));

      tmpreg = (uint32_t)(((uint32_t)RTC_ByteToBcd2(sTime->Hours)   << RTC_TR_HU_Pos)  | \
                          ((uint32_t)RTC_ByteToBcd2(sTime->Minutes) << RTC_TR_MNU_Pos) | \
                          ((uint32_t)RTC_ByteToBcd2(sTime->Seconds) << RTC_TR_SU_Pos)  | \
                          (((uint32_t)sTime->TimeFormat) << RTC_TR_PM_Pos));
    }
    else
    {
      if((hrtc->Instance->CR & RTC_CR_FMT) != 0U)
      {
        assert_param(IS_RTC_HOUR12(RTC_Bcd2ToByte(sTime->Hours)));
        assert_param(IS_RTC_HOURFORMAT12(sTime->TimeFormat));
      }
      else
      {
        sTime->TimeFormat = 0x00U;
        assert_param(IS_RTC_HOUR24(RTC_Bcd2ToByte(sTime->Hours)));
      }
      assert_param(IS_RTC_MINUTES(RTC_Bcd2ToByte(sTime->Minutes)));
      assert_param(IS_RTC_SECONDS(RTC_Bcd2ToByte(sTime->Seconds)));
      tmpreg = (((uint32_t)(sTime->Hours)   << RTC_TR_HU_Pos)  | \
                ((uint32_t)(sTime->Minutes) << RTC_TR_MNU_Pos) | \
                ((uint32_t)(sTime->Seconds) << RTC_TR_SU_Pos)  | \
                ((uint32_t)(sTime->TimeFormat) << RTC_TR_PM_Pos));
    }

    /* Set the RTC_TR register */
    hrtc->Instance->TR = (uint32_t)(tmpreg & RTC_TR_RESERVED_MASK);

    /* Clear the bits to be configured */
    hrtc->Instance->CR &= ((uint32_t)~RTC_CR_BKP);

    /* Configure the RTC_CR register */
    hrtc->Instance->CR |= (uint32_t)(sTime->DayLightSaving | sTime->StoreOperation);

    /* Exit Initialization mode */
    status = RTC_ExitInitMode(hrtc);
  }

  /* Enable the write protection for RTC registers */
  __HAL_RTC_WRITEPROTECTION_ENABLE(hrtc);

  if (status == HAL_OK)
  {
    hrtc->State = HAL_RTC_STATE_READY;
  }

  /* Process Unlocked */
  __HAL_UNLOCK(hrtc);

  return status;
}

/**
  * @brief  Get RTC current time.
  * @param  hrtc RTC handle
  * @param  sTime Pointer to Time structure with Hours, Minutes and Seconds fields returned
  *                with input format (BIN or BCD), also SubSeconds field returning the
  *                RTC_SSR register content and SecondFraction field the Synchronous pre-scaler
  *                factor to be used for second fraction ratio computation.
  * @param  Format Specifies the format of the entered parameters.
  *          This parameter can be one of the following values:
  *            @arg RTC_FORMAT_BIN: Binary data format
  *            @arg RTC_FORMAT_BCD: BCD data format
  * @note  You can use SubSeconds and SecondFraction (sTime structure fields returned) to convert SubSeconds
  *        value in second fraction ratio with time unit following generic formula:
  *        Second fraction ratio * time_unit= [(SecondFraction-SubSeconds)/(SecondFraction+1)] * time_unit
  *        This conversion can be performed only if no shift operation is pending (ie. SHFP=0) when PREDIV_S >= SS
  * @note  You must call HAL_RTC_GetDate() after HAL_RTC_GetTime() to unlock the values
  *        in the higher-order calendar shadow registers to ensure consistency between the time and date values.
  *        Reading RTC current time locks the values in calendar shadow registers until Current date is read
  *        to ensure consistency between the time and date values.
  * @retval HAL status
  */
HAL_StatusTypeDef HAL_RTC_GetTime(RTC_HandleTypeDef *hrtc, RTC_TimeTypeDef *sTime, uint32_t Format)
{
  uint32_t tmpreg;

  /* Check the parameters */
  assert_param(IS_RTC_FORMAT(Format));

  /* Get subseconds structure field from the corresponding register*/
  sTime->SubSeconds = (uint32_t)(hrtc->Instance->SSR);

  /* Get SecondFraction structure field from the corresponding register field*/
  sTime->SecondFraction = (uint32_t)(hrtc->Instance->PRER & RTC_PRER_PREDIV_S);

  /* Get the TR register */
  tmpreg = (uint32_t)(hrtc->Instance->TR & RTC_TR_RESERVED_MASK);

  /* Fill the structure fields with the read parameters */
  sTime->Hours      = (uint8_t)((tmpreg & (RTC_TR_HT  | RTC_TR_HU))  >> RTC_TR_HU_Pos);
  sTime->Minutes    = (uint8_t)((tmpreg & (RTC_TR_MNT | RTC_TR_MNU)) >> RTC_TR_MNU_Pos);
  sTime->Seconds    = (uint8_t)((tmpreg & (RTC_TR_ST  | RTC_TR_SU))  >> RTC_TR_SU_Pos);
  sTime->TimeFormat = (uint8_t)((tmpreg & (RTC_TR_PM))               >> RTC_TR_PM_Pos);

  /* Check the input parameters format */
  if(Format == RTC_FORMAT_BIN)
  {
    /* Convert the time structure parameters to Binary format */
    sTime->Hours   = (uint8_t)RTC_Bcd2ToByte(sTime->Hours);
    sTime->Minutes = (uint8_t)RTC_Bcd2ToByte(sTime->Minutes);
    sTime->Seconds = (uint8_t)RTC_Bcd2ToByte(sTime->Seconds);
  }

  return HAL_OK;
}

/**
  * @brief  Set RTC current date.
  * @param  hrtc RTC handle
  * @param  sDate Pointer to date structure
  * @param  Format specifies the format of the entered parameters.
  *          This parameter can be one of the following values:
  *            @arg RTC_FORMAT_BIN: Binary data format
  *            @arg RTC_FORMAT_BCD: BCD data format
  * @retval HAL status
  */
HAL_StatusTypeDef HAL_RTC_SetDate(RTC_HandleTypeDef *hrtc, RTC_DateTypeDef *sDate, uint32_t Format)
{
  uint32_t datetmpreg;
  HAL_StatusTypeDef status;

  /* Check the parameters */
  assert_param(IS_RTC_FORMAT(Format));

  /* Process Locked */
  __HAL_LOCK(hrtc);

  hrtc->State = HAL_RTC_STATE_BUSY;

  if((Format == RTC_FORMAT_BIN) && ((sDate->Month & 0x10U) == 0x10U))
  {
    sDate->Month = (uint8_t)((sDate->Month & (uint8_t)~(0x10U)) + (uint8_t)0x0AU);
  }

  assert_param(IS_RTC_WEEKDAY(sDate->WeekDay));

  if(Format == RTC_FORMAT_BIN)
  {
    assert_param(IS_RTC_YEAR(sDate->Year));
    assert_param(IS_RTC_MONTH(sDate->Month));
    assert_param(IS_RTC_DATE(sDate->Date));

    datetmpreg = (((uint32_t)RTC_ByteToBcd2(sDate->Year)  << RTC_DR_YU_Pos) | \
                  ((uint32_t)RTC_ByteToBcd2(sDate->Month) << RTC_DR_MU_Pos) | \
                  ((uint32_t)RTC_ByteToBcd2(sDate->Date)  << RTC_DR_DU_Pos) | \
                  ((uint32_t)sDate->WeekDay               << RTC_DR_WDU_Pos));
  }
  else
  {
    assert_param(IS_RTC_YEAR(RTC_Bcd2ToByte(sDate->Year)));
    assert_param(IS_RTC_MONTH(RTC_Bcd2ToByte(sDate->Month)));
    assert_param(IS_RTC_DATE(RTC_Bcd2ToByte(sDate->Date)));

    datetmpreg = ((((uint32_t)sDate->Year)    << RTC_DR_YU_Pos) | \
                  (((uint32_t)sDate->Month)   << RTC_DR_MU_Pos) | \
                  (((uint32_t)sDate->Date)    << RTC_DR_DU_Pos) | \
                  (((uint32_t)sDate->WeekDay) << RTC_DR_WDU_Pos));
  }

  /* Disable the write protection for RTC registers */
  __HAL_RTC_WRITEPROTECTION_DISABLE(hrtc);


  /* Enter Initialization mode */
  status = RTC_EnterInitMode(hrtc);
  if (status == HAL_OK)
  {
    /* Set the RTC_DR register */
    hrtc->Instance->DR = (uint32_t)(datetmpreg & RTC_DR_RESERVED_MASK);


    /* Exit Initialization mode */
    status = RTC_ExitInitMode(hrtc);
  }

  /* Enable the write protection for RTC registers */
  __HAL_RTC_WRITEPROTECTION_ENABLE(hrtc);

  if (status == HAL_OK)
  {
    hrtc->State = HAL_RTC_STATE_READY;
  }

  /* Process Unlocked */
  __HAL_UNLOCK(hrtc);

  return status;


}

/**
  * @brief  Get RTC current date.
  * @param  hrtc RTC handle
  * @param  sDate Pointer to Date structure
  * @param  Format Specifies the format of the entered parameters.
  *          This parameter can be one of the following values:
  *            @arg RTC_FORMAT_BIN:  Binary data format
  *            @arg RTC_FORMAT_BCD:  BCD data format
  * @note  You must call HAL_RTC_GetDate() after HAL_RTC_GetTime() to unlock the values
  *        in the higher-order calendar shadow registers to ensure consistency between the time and date values.
  *        Reading RTC current time locks the values in calendar shadow registers until Current date is read.
  * @retval HAL status
  */
HAL_StatusTypeDef HAL_RTC_GetDate(RTC_HandleTypeDef *hrtc, RTC_DateTypeDef *sDate, uint32_t Format)
{
  uint32_t datetmpreg;

  /* Check the parameters */
  assert_param(IS_RTC_FORMAT(Format));

  /* Get the DR register */
  datetmpreg = (uint32_t)(hrtc->Instance->DR & RTC_DR_RESERVED_MASK);

  /* Fill the structure fields with the read parameters */
  sDate->Year    = (uint8_t)((datetmpreg & (RTC_DR_YT | RTC_DR_YU)) >> RTC_DR_YU_Pos);
  sDate->Month   = (uint8_t)((datetmpreg & (RTC_DR_MT | RTC_DR_MU)) >> RTC_DR_MU_Pos);
  sDate->Date    = (uint8_t)((datetmpreg & (RTC_DR_DT | RTC_DR_DU)) >> RTC_DR_DU_Pos);
  sDate->WeekDay = (uint8_t)((datetmpreg & (RTC_DR_WDU))            >> RTC_DR_WDU_Pos);

  /* Check the input parameters format */
  if(Format == RTC_FORMAT_BIN)
  {
    /* Convert the date structure parameters to Binary format */
    sDate->Year = (uint8_t)RTC_Bcd2ToByte(sDate->Year);
    sDate->Month = (uint8_t)RTC_Bcd2ToByte(sDate->Month);
    sDate->Date = (uint8_t)RTC_Bcd2ToByte(sDate->Date);
  }
  return HAL_OK;
}

/**
  * @}
  */

/** @addtogroup RTC_Exported_Functions_Group3
 *  @brief   RTC Alarm functions
 *
@verbatim
 ===============================================================================
                 ##### RTC Alarm functions #####
 ===============================================================================

 [..] This section provides functions allowing to configure Alarm feature

@endverbatim
  * @{
  */
/**
  * @brief  Set the specified RTC Alarm.
  * @param  hrtc RTC handle
  * @param  sAlarm Pointer to Alarm structure
  * @param  Format Specifies the format of the entered parameters.
  *          This parameter can be one of the following values:
  *             @arg RTC_FORMAT_BIN: Binary data format
  *             @arg RTC_FORMAT_BCD: BCD data format
  * @retval HAL status
  */
HAL_StatusTypeDef HAL_RTC_SetAlarm(RTC_HandleTypeDef *hrtc, RTC_AlarmTypeDef *sAlarm, uint32_t Format)
{
  uint32_t tickstart;
  uint32_t tmpreg;
  uint32_t subsecondtmpreg;

  /* Check the parameters */
  assert_param(IS_RTC_FORMAT(Format));
  assert_param(IS_RTC_ALARM(sAlarm->Alarm));
  assert_param(IS_RTC_ALARM_MASK(sAlarm->AlarmMask));
  assert_param(IS_RTC_ALARM_DATE_WEEKDAY_SEL(sAlarm->AlarmDateWeekDaySel));
  assert_param(IS_RTC_ALARM_SUB_SECOND_VALUE(sAlarm->AlarmTime.SubSeconds));
  assert_param(IS_RTC_ALARM_SUB_SECOND_MASK(sAlarm->AlarmSubSecondMask));

  /* Process Locked */
  __HAL_LOCK(hrtc);

  hrtc->State = HAL_RTC_STATE_BUSY;

  if(Format == RTC_FORMAT_BIN)
  {
    if((hrtc->Instance->CR & RTC_CR_FMT) != 0U)
    {
      assert_param(IS_RTC_HOUR12(sAlarm->AlarmTime.Hours));
      assert_param(IS_RTC_HOURFORMAT12(sAlarm->AlarmTime.TimeFormat));
    }
    else
    {
      sAlarm->AlarmTime.TimeFormat = 0x00U;
      assert_param(IS_RTC_HOUR24(sAlarm->AlarmTime.Hours));
    }
    assert_param(IS_RTC_MINUTES(sAlarm->AlarmTime.Minutes));
    assert_param(IS_RTC_SECONDS(sAlarm->AlarmTime.Seconds));

    if(sAlarm->AlarmDateWeekDaySel == RTC_ALARMDATEWEEKDAYSEL_DATE)
    {
      assert_param(IS_RTC_ALARM_DATE_WEEKDAY_DATE(sAlarm->AlarmDateWeekDay));
    }
    else
    {
      assert_param(IS_RTC_ALARM_DATE_WEEKDAY_WEEKDAY(sAlarm->AlarmDateWeekDay));
    }

    tmpreg = (((uint32_t)RTC_ByteToBcd2(sAlarm->AlarmTime.Hours)   << RTC_ALRMAR_HU_Pos)  | \
              ((uint32_t)RTC_ByteToBcd2(sAlarm->AlarmTime.Minutes) << RTC_ALRMAR_MNU_Pos) | \
              ((uint32_t)RTC_ByteToBcd2(sAlarm->AlarmTime.Seconds) << RTC_ALRMAR_SU_Pos)  | \
              ((uint32_t)sAlarm->AlarmTime.TimeFormat              << RTC_ALRMAR_PM_Pos)  | \
              ((uint32_t)RTC_ByteToBcd2(sAlarm->AlarmDateWeekDay)  << RTC_ALRMAR_DU_Pos)  | \
              ((uint32_t)sAlarm->AlarmDateWeekDaySel)                                     | \
              ((uint32_t)sAlarm->AlarmMask));
  }
  else
  {
    if((hrtc->Instance->CR & RTC_CR_FMT) != 0U)
    {
      assert_param(IS_RTC_HOUR12(RTC_Bcd2ToByte(sAlarm->AlarmTime.Hours)));
      assert_param(IS_RTC_HOURFORMAT12(sAlarm->AlarmTime.TimeFormat));
    }
    else
    {
      sAlarm->AlarmTime.TimeFormat = 0x00U;
      assert_param(IS_RTC_HOUR24(RTC_Bcd2ToByte(sAlarm->AlarmTime.Hours)));
    }

    assert_param(IS_RTC_MINUTES(RTC_Bcd2ToByte(sAlarm->AlarmTime.Minutes)));
    assert_param(IS_RTC_SECONDS(RTC_Bcd2ToByte(sAlarm->AlarmTime.Seconds)));

    if(sAlarm->AlarmDateWeekDaySel == RTC_ALARMDATEWEEKDAYSEL_DATE)
    {
      assert_param(IS_RTC_ALARM_DATE_WEEKDAY_DATE(RTC_Bcd2ToByte(sAlarm->AlarmDateWeekDay)));
    }
    else
    {
      assert_param(IS_RTC_ALARM_DATE_WEEKDAY_WEEKDAY(RTC_Bcd2ToByte(sAlarm->AlarmDateWeekDay)));
    }

    tmpreg = (((uint32_t)sAlarm->AlarmTime.Hours       << RTC_ALRMAR_HU_Pos)  | \
              ((uint32_t)sAlarm->AlarmTime.Minutes     << RTC_ALRMAR_MNU_Pos) | \
              ((uint32_t)sAlarm->AlarmTime.Seconds     << RTC_ALRMAR_SU_Pos)  | \
              ((uint32_t)sAlarm->AlarmTime.TimeFormat  << RTC_ALRMAR_PM_Pos)  | \
              ((uint32_t)sAlarm->AlarmDateWeekDay      << RTC_ALRMAR_DU_Pos)  | \
              ((uint32_t)sAlarm->AlarmDateWeekDaySel)                         | \
              ((uint32_t)sAlarm->AlarmMask));
  }

  /* Configure the Alarm A or Alarm B Sub Second registers */
  subsecondtmpreg = (uint32_t)((uint32_t)(sAlarm->AlarmTime.SubSeconds) | (uint32_t)(sAlarm->AlarmSubSecondMask));

  /* Disable the write protection for RTC registers */
  __HAL_RTC_WRITEPROTECTION_DISABLE(hrtc);

  /* Configure the Alarm register */
  if(sAlarm->Alarm == RTC_ALARM_A)
  {
    /* Disable the Alarm A interrupt */
    __HAL_RTC_ALARMA_DISABLE(hrtc);
    /* Clear flag alarm A */
    __HAL_RTC_ALARM_CLEAR_FLAG(hrtc, RTC_FLAG_ALRAF);
    /* In case of interrupt mode is used, the interrupt source must disabled */
    __HAL_RTC_ALARM_DISABLE_IT(hrtc, RTC_IT_ALRA);

    tickstart = HAL_GetTick();
    /* Wait till RTC ALRAWF flag is set and if timeout is reached exit */
#if defined(TAMP)
    while (READ_BIT(hrtc->Instance->ICSR, RTC_FLAG_ALRAWF) == 0U)
#else
    while (__HAL_RTC_ALARM_GET_FLAG(hrtc, RTC_FLAG_ALRAWF) == 0U)
#endif /* TAMP */
    {
      if((HAL_GetTick() - tickstart) > RTC_TIMEOUT_VALUE)
      {
        /* Enable the write protection for RTC registers */
        __HAL_RTC_WRITEPROTECTION_ENABLE(hrtc);

        hrtc->State = HAL_RTC_STATE_TIMEOUT;

        /* Process Unlocked */
        __HAL_UNLOCK(hrtc);

        return HAL_TIMEOUT;
      }
    }

    hrtc->Instance->ALRMAR = (uint32_t)tmpreg;
    /* Configure the Alarm A Sub Second register */
    hrtc->Instance->ALRMASSR = subsecondtmpreg;
    /* Configure the Alarm state: Enable Alarm */
    __HAL_RTC_ALARMA_ENABLE(hrtc);
  }
  else
  {
    /* Disable the Alarm B interrupt */
    __HAL_RTC_ALARMB_DISABLE(hrtc);
    /* Clear flag alarm B */
    __HAL_RTC_ALARM_CLEAR_FLAG(hrtc, RTC_FLAG_ALRBF);
    /* In case of interrupt mode is used, the interrupt source must disabled */
    __HAL_RTC_ALARM_DISABLE_IT(hrtc, RTC_IT_ALRB);

    tickstart = HAL_GetTick();
    /* Wait till RTC ALRBWF flag is set and if timeout is reached exit */
#if defined(TAMP)
    while (READ_BIT(hrtc->Instance->ICSR, RTC_FLAG_ALRBWF) == 0U)
#else
    while (__HAL_RTC_ALARM_GET_FLAG(hrtc, RTC_FLAG_ALRBWF) == 0U)
#endif /* TAMP */
    {
      if((HAL_GetTick() - tickstart) > RTC_TIMEOUT_VALUE)
      {
        /* Enable the write protection for RTC registers */
        __HAL_RTC_WRITEPROTECTION_ENABLE(hrtc);

        hrtc->State = HAL_RTC_STATE_TIMEOUT;

        /* Process Unlocked */
        __HAL_UNLOCK(hrtc);

        return HAL_TIMEOUT;
      }
    }

    hrtc->Instance->ALRMBR = (uint32_t)tmpreg;
    /* Configure the Alarm B Sub Second register */
    hrtc->Instance->ALRMBSSR = subsecondtmpreg;
    /* Configure the Alarm state: Enable Alarm */
    __HAL_RTC_ALARMB_ENABLE(hrtc);
  }

  /* Enable the write protection for RTC registers */
  __HAL_RTC_WRITEPROTECTION_ENABLE(hrtc);

  /* Change RTC state */
  hrtc->State = HAL_RTC_STATE_READY;

  /* Process Unlocked */
  __HAL_UNLOCK(hrtc);

  return HAL_OK;
}

/**
  * @brief  Set the specified RTC Alarm with Interrupt.
  * @param  hrtc RTC handle
  * @param  sAlarm Pointer to Alarm structure
  * @param  Format Specifies the format of the entered parameters.
  *          This parameter can be one of the following values:
  *             @arg RTC_FORMAT_BIN: Binary data format
  *             @arg RTC_FORMAT_BCD: BCD data format
  * @note   The Alarm register can only be written when the corresponding Alarm
  *         is disabled (Use the HAL_RTC_DeactivateAlarm()).
  * @note   The HAL_RTC_SetTime() must be called before enabling the Alarm feature.
  * @retval HAL status
  */
HAL_StatusTypeDef HAL_RTC_SetAlarm_IT(RTC_HandleTypeDef *hrtc, RTC_AlarmTypeDef *sAlarm, uint32_t Format)
{
  uint32_t tickstart;
  uint32_t tmpreg;
  uint32_t subsecondtmpreg;

  /* Check the parameters */
  assert_param(IS_RTC_FORMAT(Format));
  assert_param(IS_RTC_ALARM(sAlarm->Alarm));
  assert_param(IS_RTC_ALARM_MASK(sAlarm->AlarmMask));
  assert_param(IS_RTC_ALARM_DATE_WEEKDAY_SEL(sAlarm->AlarmDateWeekDaySel));
  assert_param(IS_RTC_ALARM_SUB_SECOND_VALUE(sAlarm->AlarmTime.SubSeconds));
  assert_param(IS_RTC_ALARM_SUB_SECOND_MASK(sAlarm->AlarmSubSecondMask));

  /* Process Locked */
  __HAL_LOCK(hrtc);

  hrtc->State = HAL_RTC_STATE_BUSY;

  if(Format == RTC_FORMAT_BIN)
  {
    if((hrtc->Instance->CR & RTC_CR_FMT) != 0U)
    {
      assert_param(IS_RTC_HOUR12(sAlarm->AlarmTime.Hours));
      assert_param(IS_RTC_HOURFORMAT12(sAlarm->AlarmTime.TimeFormat));
    }
    else
    {
      sAlarm->AlarmTime.TimeFormat = 0x00U;
      assert_param(IS_RTC_HOUR24(sAlarm->AlarmTime.Hours));
    }
    assert_param(IS_RTC_MINUTES(sAlarm->AlarmTime.Minutes));
    assert_param(IS_RTC_SECONDS(sAlarm->AlarmTime.Seconds));

    if(sAlarm->AlarmDateWeekDaySel == RTC_ALARMDATEWEEKDAYSEL_DATE)
    {
      assert_param(IS_RTC_ALARM_DATE_WEEKDAY_DATE(sAlarm->AlarmDateWeekDay));
    }
    else
    {
      assert_param(IS_RTC_ALARM_DATE_WEEKDAY_WEEKDAY(sAlarm->AlarmDateWeekDay));
    }

    tmpreg = (((uint32_t)RTC_ByteToBcd2(sAlarm->AlarmTime.Hours)   << RTC_ALRMAR_HU_Pos)  | \
              ((uint32_t)RTC_ByteToBcd2(sAlarm->AlarmTime.Minutes) << RTC_ALRMAR_MNU_Pos) | \
              ((uint32_t)RTC_ByteToBcd2(sAlarm->AlarmTime.Seconds) << RTC_ALRMAR_SU_Pos)  | \
              ((uint32_t)sAlarm->AlarmTime.TimeFormat              << RTC_ALRMAR_PM_Pos)  | \
              ((uint32_t)RTC_ByteToBcd2(sAlarm->AlarmDateWeekDay)  << RTC_ALRMAR_DU_Pos)  | \
              ((uint32_t)sAlarm->AlarmDateWeekDaySel)                                     | \
              ((uint32_t)sAlarm->AlarmMask));
  }
  else
  {
    if((hrtc->Instance->CR & RTC_CR_FMT) != 0U)
    {
      assert_param(IS_RTC_HOUR12(RTC_Bcd2ToByte(sAlarm->AlarmTime.Hours)));
      assert_param(IS_RTC_HOURFORMAT12(sAlarm->AlarmTime.TimeFormat));
    }
    else
    {
      sAlarm->AlarmTime.TimeFormat = 0x00U;
      assert_param(IS_RTC_HOUR24(RTC_Bcd2ToByte(sAlarm->AlarmTime.Hours)));
    }

    assert_param(IS_RTC_MINUTES(RTC_Bcd2ToByte(sAlarm->AlarmTime.Minutes)));
    assert_param(IS_RTC_SECONDS(RTC_Bcd2ToByte(sAlarm->AlarmTime.Seconds)));

    if(sAlarm->AlarmDateWeekDaySel == RTC_ALARMDATEWEEKDAYSEL_DATE)
    {
      assert_param(IS_RTC_ALARM_DATE_WEEKDAY_DATE(RTC_Bcd2ToByte(sAlarm->AlarmDateWeekDay)));
    }
    else
    {
      assert_param(IS_RTC_ALARM_DATE_WEEKDAY_WEEKDAY(RTC_Bcd2ToByte(sAlarm->AlarmDateWeekDay)));
    }

    tmpreg = (((uint32_t)sAlarm->AlarmTime.Hours       << RTC_ALRMAR_HU_Pos)  | \
              ((uint32_t)sAlarm->AlarmTime.Minutes     << RTC_ALRMAR_MNU_Pos) | \
              ((uint32_t)sAlarm->AlarmTime.Seconds     << RTC_ALRMAR_SU_Pos)  | \
              ((uint32_t)sAlarm->AlarmTime.TimeFormat  << RTC_ALRMAR_PM_Pos)  | \
              ((uint32_t)sAlarm->AlarmDateWeekDay      << RTC_ALRMAR_DU_Pos)  | \
              ((uint32_t)sAlarm->AlarmDateWeekDaySel)                         | \
              ((uint32_t)sAlarm->AlarmMask));
  }
  /* Configure the Alarm A or Alarm B Sub Second registers */
  subsecondtmpreg = (uint32_t)((uint32_t)(sAlarm->AlarmTime.SubSeconds) | (uint32_t)(sAlarm->AlarmSubSecondMask));

  /* Disable the write protection for RTC registers */
  __HAL_RTC_WRITEPROTECTION_DISABLE(hrtc);

  /* Configure the Alarm register */
  if(sAlarm->Alarm == RTC_ALARM_A)
  {
    /* Disable the Alarm A interrupt */
    __HAL_RTC_ALARMA_DISABLE(hrtc);

    /* Clear flag alarm A */
    __HAL_RTC_ALARM_CLEAR_FLAG(hrtc, RTC_FLAG_ALRAF);

    tickstart = HAL_GetTick();
    /* Wait till RTC ALRAWF flag is set and if timeout is reached exit */
#if defined(TAMP)
    while (READ_BIT(hrtc->Instance->ICSR, RTC_FLAG_ALRAWF) == 0U)
#else
    while (__HAL_RTC_ALARM_GET_FLAG(hrtc, RTC_FLAG_ALRAWF) == 0U)
#endif /* TAMP */
    {
      if((HAL_GetTick() - tickstart) > RTC_TIMEOUT_VALUE)
      {
        /* Enable the write protection for RTC registers */
        __HAL_RTC_WRITEPROTECTION_ENABLE(hrtc);

        hrtc->State = HAL_RTC_STATE_TIMEOUT;

        /* Process Unlocked */
        __HAL_UNLOCK(hrtc);

        return HAL_TIMEOUT;
      }
    }

    hrtc->Instance->ALRMAR = (uint32_t)tmpreg;
    /* Configure the Alarm A Sub Second register */
    hrtc->Instance->ALRMASSR = subsecondtmpreg;
    /* Configure the Alarm state: Enable Alarm */
    __HAL_RTC_ALARMA_ENABLE(hrtc);
    /* Configure the Alarm interrupt */
    __HAL_RTC_ALARM_ENABLE_IT(hrtc, RTC_IT_ALRA);
  }
  else
  {
    /* Disable the Alarm B interrupt */
    __HAL_RTC_ALARMB_DISABLE(hrtc);

    /* Clear flag alarm B */
    __HAL_RTC_ALARM_CLEAR_FLAG(hrtc, RTC_FLAG_ALRBF);

    tickstart = HAL_GetTick();
    /* Wait till RTC ALRBWF flag is set and if timeout is reached exit */
#if defined(TAMP)
    while (READ_BIT(hrtc->Instance->ICSR, RTC_FLAG_ALRBWF) == 0U)
#else
    while (__HAL_RTC_ALARM_GET_FLAG(hrtc, RTC_FLAG_ALRBWF) == 0U)
#endif /* TAMP */
    {
      if((HAL_GetTick() - tickstart) > RTC_TIMEOUT_VALUE)
      {
        /* Enable the write protection for RTC registers */
        __HAL_RTC_WRITEPROTECTION_ENABLE(hrtc);

        hrtc->State = HAL_RTC_STATE_TIMEOUT;

        /* Process Unlocked */
        __HAL_UNLOCK(hrtc);

        return HAL_TIMEOUT;
      }
    }

    hrtc->Instance->ALRMBR = (uint32_t)tmpreg;
    /* Configure the Alarm B Sub Second register */
    hrtc->Instance->ALRMBSSR = subsecondtmpreg;
    /* Configure the Alarm state: Enable Alarm */
    __HAL_RTC_ALARMB_ENABLE(hrtc);
    /* Configure the Alarm interrupt */
    __HAL_RTC_ALARM_ENABLE_IT(hrtc, RTC_IT_ALRB);
  }

  /* RTC Alarm Interrupt Configuration: EXTI configuration */
#if defined(DUAL_CORE)
  if (HAL_GetCurrentCPUID() == CM7_CPUID)
  {
    __HAL_RTC_ALARM_EXTI_ENABLE_IT();
  }
  else
  {
    __HAL_RTC_ALARM_EXTID2_ENABLE_IT();
  }
#else  /* SINGLE_CORE */
  __HAL_RTC_ALARM_EXTI_ENABLE_IT();
#endif

  __HAL_RTC_ALARM_EXTI_ENABLE_RISING_EDGE();

  /* Enable the write protection for RTC registers */
  __HAL_RTC_WRITEPROTECTION_ENABLE(hrtc);

  hrtc->State = HAL_RTC_STATE_READY;

  /* Process Unlocked */
  __HAL_UNLOCK(hrtc);

  return HAL_OK;
}

/**
  * @brief  Deactivate the specified RTC Alarm.
  * @param  hrtc RTC handle
  * @param  Alarm Specifies the Alarm.
  *          This parameter can be one of the following values:
  *            @arg RTC_ALARM_A:  AlarmA
  *            @arg RTC_ALARM_B:  AlarmB
  * @retval HAL status
  */
HAL_StatusTypeDef HAL_RTC_DeactivateAlarm(RTC_HandleTypeDef *hrtc, uint32_t Alarm)
{
  uint32_t tickstart;

  /* Check the parameters */
  assert_param(IS_RTC_ALARM(Alarm));

  /* Process Locked */
  __HAL_LOCK(hrtc);

  hrtc->State = HAL_RTC_STATE_BUSY;

  /* Disable the write protection for RTC registers */
  __HAL_RTC_WRITEPROTECTION_DISABLE(hrtc);

  if(Alarm == RTC_ALARM_A)
  {
    /* AlarmA */
    __HAL_RTC_ALARMA_DISABLE(hrtc);

    /* In case of interrupt mode is used, the interrupt source must disabled */
    __HAL_RTC_ALARM_DISABLE_IT(hrtc, RTC_IT_ALRA);

    tickstart = HAL_GetTick();

    /* Wait till RTC ALRxWF flag is set and if timeout is reached exit */
#if defined(TAMP)
    while (READ_BIT(hrtc->Instance->ICSR, RTC_FLAG_ALRAWF) == 0U)
#else
    while (__HAL_RTC_ALARM_GET_FLAG(hrtc, RTC_FLAG_ALRAWF) == 0U)
#endif /* TAMP */
    {
      if((HAL_GetTick()  - tickstart) > RTC_TIMEOUT_VALUE)
      {
        /* Enable the write protection for RTC registers */
        __HAL_RTC_WRITEPROTECTION_ENABLE(hrtc);

        hrtc->State = HAL_RTC_STATE_TIMEOUT;

        /* Process Unlocked */
        __HAL_UNLOCK(hrtc);

        return HAL_TIMEOUT;
      }
    }
  }
  else
  {
    /* AlarmB */
    __HAL_RTC_ALARMB_DISABLE(hrtc);

    /* In case of interrupt mode is used, the interrupt source must disabled */
    __HAL_RTC_ALARM_DISABLE_IT(hrtc, RTC_IT_ALRB);

    tickstart = HAL_GetTick();

    /* Wait till RTC ALRxWF flag is set and if timeout is reached exit */
#if defined(TAMP)
    while (READ_BIT(hrtc->Instance->ICSR, RTC_FLAG_ALRBWF) == 0U)
#else
    while (__HAL_RTC_ALARM_GET_FLAG(hrtc, RTC_FLAG_ALRBWF) == 0U)
#endif /* TAMP */
    {
      if((HAL_GetTick() - tickstart) > RTC_TIMEOUT_VALUE)
      {
        /* Enable the write protection for RTC registers */
        __HAL_RTC_WRITEPROTECTION_ENABLE(hrtc);

        hrtc->State = HAL_RTC_STATE_TIMEOUT;

        /* Process Unlocked */
        __HAL_UNLOCK(hrtc);

        return HAL_TIMEOUT;
      }
    }
  }
  /* Enable the write protection for RTC registers */
  __HAL_RTC_WRITEPROTECTION_ENABLE(hrtc);

  hrtc->State = HAL_RTC_STATE_READY;

  /* Process Unlocked */
  __HAL_UNLOCK(hrtc);

  return HAL_OK;
}

/**
  * @brief  Get the RTC Alarm value and masks.
  * @param  hrtc RTC handle
  * @param  sAlarm Pointer to Date structure
  * @param  Alarm Specifies the Alarm.
  *          This parameter can be one of the following values:
  *             @arg RTC_ALARM_A: AlarmA
  *             @arg RTC_ALARM_B: AlarmB
  * @param  Format Specifies the format of the entered parameters.
  *          This parameter can be one of the following values:
  *             @arg RTC_FORMAT_BIN: Binary data format
  *             @arg RTC_FORMAT_BCD: BCD data format
  * @retval HAL status
  */
HAL_StatusTypeDef HAL_RTC_GetAlarm(RTC_HandleTypeDef *hrtc, RTC_AlarmTypeDef *sAlarm, uint32_t Alarm, uint32_t Format)
{
  uint32_t tmpreg;
  uint32_t subsecondtmpreg;

  /* Check the parameters */
  assert_param(IS_RTC_FORMAT(Format));
  assert_param(IS_RTC_ALARM(Alarm));

  if(Alarm == RTC_ALARM_A)
  {
    /* AlarmA */
    sAlarm->Alarm = RTC_ALARM_A;

    tmpreg = (uint32_t)(hrtc->Instance->ALRMAR);
    subsecondtmpreg = (uint32_t)((hrtc->Instance->ALRMASSR) & RTC_ALRMASSR_SS);

    /* Fill the structure with the read parameters */
    sAlarm->AlarmTime.Hours      = (uint8_t)((tmpreg & (RTC_ALRMAR_HT  | RTC_ALRMAR_HU))  >> RTC_ALRMAR_HU_Pos);
    sAlarm->AlarmTime.Minutes    = (uint8_t)((tmpreg & (RTC_ALRMAR_MNT | RTC_ALRMAR_MNU)) >> RTC_ALRMAR_MNU_Pos);
    sAlarm->AlarmTime.Seconds    = (uint8_t)((tmpreg & (RTC_ALRMAR_ST  | RTC_ALRMAR_SU))  >> RTC_ALRMAR_SU_Pos);
    sAlarm->AlarmTime.TimeFormat = (uint8_t)((tmpreg &  RTC_ALRMAR_PM)                    >> RTC_ALRMAR_PM_Pos);
    sAlarm->AlarmTime.SubSeconds = (uint32_t) subsecondtmpreg;
    sAlarm->AlarmDateWeekDay     = (uint8_t)((tmpreg & (RTC_ALRMAR_DT  | RTC_ALRMAR_DU))  >> RTC_ALRMAR_DU_Pos);
    sAlarm->AlarmDateWeekDaySel  = (uint32_t)(tmpreg &  RTC_ALRMAR_WDSEL);
    sAlarm->AlarmMask            = (uint32_t)(tmpreg &  RTC_ALARMMASK_ALL);
  }
  else
  {
    sAlarm->Alarm = RTC_ALARM_B;

    tmpreg = (uint32_t)(hrtc->Instance->ALRMBR);
    subsecondtmpreg = (uint32_t)((hrtc->Instance->ALRMBSSR) & RTC_ALRMBSSR_SS);

    /* Fill the structure with the read parameters */
    sAlarm->AlarmTime.Hours      = (uint8_t)((tmpreg & (RTC_ALRMBR_HT  | RTC_ALRMBR_HU))  >> RTC_ALRMBR_HU_Pos);
    sAlarm->AlarmTime.Minutes    = (uint8_t)((tmpreg & (RTC_ALRMBR_MNT | RTC_ALRMBR_MNU)) >> RTC_ALRMBR_MNU_Pos);
    sAlarm->AlarmTime.Seconds    = (uint8_t)((tmpreg & (RTC_ALRMBR_ST  | RTC_ALRMBR_SU))  >> RTC_ALRMBR_SU_Pos);
    sAlarm->AlarmTime.TimeFormat = (uint8_t)((tmpreg &  RTC_ALRMBR_PM)                    >> RTC_ALRMBR_PM_Pos);
    sAlarm->AlarmTime.SubSeconds = (uint32_t) subsecondtmpreg;
    sAlarm->AlarmDateWeekDay     = (uint8_t)((tmpreg & (RTC_ALRMBR_DT | RTC_ALRMBR_DU))   >> RTC_ALRMBR_DU_Pos);
    sAlarm->AlarmDateWeekDaySel  = (uint32_t)(tmpreg &  RTC_ALRMBR_WDSEL);
    sAlarm->AlarmMask            = (uint32_t)(tmpreg &  RTC_ALARMMASK_ALL);
  }

  if(Format == RTC_FORMAT_BIN)
  {
    sAlarm->AlarmTime.Hours = RTC_Bcd2ToByte(sAlarm->AlarmTime.Hours);
    sAlarm->AlarmTime.Minutes = RTC_Bcd2ToByte(sAlarm->AlarmTime.Minutes);
    sAlarm->AlarmTime.Seconds = RTC_Bcd2ToByte(sAlarm->AlarmTime.Seconds);
    sAlarm->AlarmDateWeekDay = RTC_Bcd2ToByte(sAlarm->AlarmDateWeekDay);
  }

  return HAL_OK;
}

/**
  * @brief  Handle Alarm interrupt request.
  * @param  hrtc RTC handle
  * @retval None
  */
void HAL_RTC_AlarmIRQHandler(RTC_HandleTypeDef *hrtc)
{
  /* Clear the EXTI's line Flag for RTC Alarm */
#if defined(DUAL_CORE)
  if(HAL_GetCurrentCPUID() == CM7_CPUID)
  {
    __HAL_RTC_ALARM_EXTI_CLEAR_FLAG();
  }
  else
  {
    __HAL_RTC_ALARM_EXTID2_CLEAR_FLAG();
  }
#else  /* SINGLE_CORE */
  __HAL_RTC_ALARM_EXTI_CLEAR_FLAG();
#endif /* DUAL_CORE */

#if defined(TAMP)
  /* Get interrupt status */
  uint32_t tmp = hrtc->Instance->MISR;

  if((tmp & RTC_FLAG_ALRAF) != 0u)
  {
    /* Clear the AlarmA interrupt pending bit */
    __HAL_RTC_ALARM_CLEAR_FLAG(hrtc, RTC_FLAG_ALRAF);

    /* Call Alarm A Callback */
#if (USE_HAL_RTC_REGISTER_CALLBACKS == 1)
    hrtc->AlarmAEventCallback(hrtc);
#else  /* (USE_HAL_RTC_REGISTER_CALLBACKS == 1) */
    HAL_RTC_AlarmAEventCallback(hrtc);
#endif /* (USE_HAL_RTC_REGISTER_CALLBACKS == 1) */
  }

  if((tmp & RTC_MISR_ALRBMF) != 0u)
  {
    /* Clear the AlarmB interrupt pending bit */
    hrtc->Instance->SCR = RTC_SCR_CALRBF;

    /* Call Alarm B Callback */
#if (USE_HAL_RTC_REGISTER_CALLBACKS == 1)
    hrtc->AlarmBEventCallback(hrtc);
#else  /* (USE_HAL_RTC_REGISTER_CALLBACKS == 1) */
    HAL_RTCEx_AlarmBEventCallback(hrtc);
#endif /* (USE_HAL_RTC_REGISTER_CALLBACKS == 1) */
  }
#else
  /* Get the AlarmA interrupt source enable status */
  if(__HAL_RTC_ALARM_GET_IT_SOURCE(hrtc, RTC_IT_ALRA) != 0U)
  {
    /* Get the pending status of the AlarmA Interrupt */
    if(__HAL_RTC_ALARM_GET_FLAG(hrtc, RTC_FLAG_ALRAF) != 0U)
    {
      /* Clear the AlarmA interrupt pending bit */
      __HAL_RTC_ALARM_CLEAR_FLAG(hrtc, RTC_FLAG_ALRAF);

#if (USE_HAL_RTC_REGISTER_CALLBACKS == 1)
      hrtc->AlarmAEventCallback(hrtc);
#else  /* (USE_HAL_RTC_REGISTER_CALLBACKS == 1) */
      HAL_RTC_AlarmAEventCallback(hrtc);
#endif /* (USE_HAL_RTC_REGISTER_CALLBACKS == 1) */
    }
  }

  /* Get the AlarmB interrupt source enable status */
  if(__HAL_RTC_ALARM_GET_IT_SOURCE(hrtc, RTC_IT_ALRB) != 0U)
  {
    /* Get the pending status of the AlarmB Interrupt */
    if(__HAL_RTC_ALARM_GET_FLAG(hrtc, RTC_FLAG_ALRBF) != 0U)
    {
      /* Clear the AlarmB interrupt pending bit */
      __HAL_RTC_ALARM_CLEAR_FLAG(hrtc, RTC_FLAG_ALRBF);

      /* AlarmB callback */
#if (USE_HAL_RTC_REGISTER_CALLBACKS == 1)
      hrtc->AlarmBEventCallback(hrtc);
#else  /* (USE_HAL_RTC_REGISTER_CALLBACKS == 1) */
      HAL_RTCEx_AlarmBEventCallback(hrtc);
#endif /* (USE_HAL_RTC_REGISTER_CALLBACKS == 1) */
    }
  }
#endif /* TAMP */

  /* Change RTC state */
  hrtc->State = HAL_RTC_STATE_READY;
}

/**
  * @brief  Alarm A callback.
  * @param  hrtc RTC handle
  * @retval None
  */
__weak void HAL_RTC_AlarmAEventCallback(RTC_HandleTypeDef *hrtc)
{
  /* Prevent unused argument(s) compilation warning */
  UNUSED(hrtc);

  /* NOTE : This function should not be modified, when the callback is needed,
            the HAL_RTC_AlarmAEventCallback could be implemented in the user file
   */
}

/**
  * @brief  Handle AlarmA Polling request.
  * @param  hrtc RTC handle
  * @param  Timeout Timeout duration
  * @retval HAL status
  */
HAL_StatusTypeDef HAL_RTC_PollForAlarmAEvent(RTC_HandleTypeDef *hrtc, uint32_t Timeout)
{

  uint32_t tickstart = HAL_GetTick();

  while (__HAL_RTC_ALARM_GET_FLAG(hrtc, RTC_FLAG_ALRAF) == 0U)
  {
    if(Timeout != HAL_MAX_DELAY)
    {
      if(((HAL_GetTick() - tickstart) > Timeout) || (Timeout == 0U))
      {
        hrtc->State = HAL_RTC_STATE_TIMEOUT;
        return HAL_TIMEOUT;
      }
    }
  }

  /* Clear the Alarm interrupt pending bit */
  __HAL_RTC_ALARM_CLEAR_FLAG(hrtc, RTC_FLAG_ALRAF);

  /* Change RTC state */
  hrtc->State = HAL_RTC_STATE_READY;

  return HAL_OK;
}

/**
  * @}
  */

/** @addtogroup RTC_Exported_Functions_Group4
 *  @brief   Peripheral Control functions
 *
@verbatim
 ===============================================================================
                     ##### Peripheral Control functions #####
 ===============================================================================
    [..]
    This subsection provides functions allowing to
      (+) Wait for RTC Time and Date Synchronization

@endverbatim
  * @{
  */

/**
  * @brief  Wait until the RTC Time and Date registers (RTC_TR and RTC_DR) are
  *         synchronized with RTC APB clock.
  * @note   The RTC Resynchronization mode is write protected, use the
  *         __HAL_RTC_WRITEPROTECTION_DISABLE() before calling this function.
  * @note   To read the calendar through the shadow registers after Calendar
  *         initialization, calendar update or after wakeup from low power modes
  *         the software must first clear the RSF flag.
  *         The software must then wait until it is set again before reading
  *         the calendar, which means that the calendar registers have been
  *         correctly copied into the RTC_TR and RTC_DR shadow registers.
  * @param  hrtc RTC handle
  * @retval HAL status
  */
HAL_StatusTypeDef HAL_RTC_WaitForSynchro(RTC_HandleTypeDef *hrtc)
{
  uint32_t tickstart;

  /* Clear RSF flag, keep reserved bits at reset values (setting other flags has no effect) */
#if defined(TAMP)
  hrtc->Instance->ICSR = ((uint32_t)(RTC_RSF_MASK & RTC_ICSR_RESERVED_MASK));
#else
  hrtc->Instance->ISR = ((uint32_t)(RTC_RSF_MASK & RTC_ISR_RESERVED_MASK));
#endif /* TAMP */

  tickstart = HAL_GetTick();

  /* Wait the registers to be synchronised */
#if defined(TAMP)
  while ((hrtc->Instance->ICSR & RTC_ICSR_RSF) == 0U)
#else
    while ((hrtc->Instance->ISR & RTC_ISR_RSF) == 0U)
#endif /* TAMP */
    {
      if((HAL_GetTick() - tickstart) > RTC_TIMEOUT_VALUE)
      {
        return HAL_TIMEOUT;
      }
    }

  return HAL_OK;
}

/**
  * @}
  */

/** @addtogroup RTC_Exported_Functions_Group5
 *  @brief   Peripheral State functions
 *
@verbatim
 ===============================================================================
                     ##### Peripheral State functions #####
 ===============================================================================
    [..]
    This subsection provides functions allowing to
      (+) Get RTC state

@endverbatim
  * @{
  */
/**
  * @brief  Return the RTC handle state.
  * @param  hrtc RTC handle
  * @retval HAL state
  */
HAL_RTCStateTypeDef HAL_RTC_GetState(RTC_HandleTypeDef *hrtc)
{
  /* Return RTC handle state */
  return hrtc->State;
}

/**
  * @}
  */

/**
  * @}
  */

/** @addtogroup RTC_Private_Functions
  * @{
  */
/**
  * @brief  Enter the RTC Initialization mode.
  * @note   The RTC Initialization mode is write protected, use the
  *         __HAL_RTC_WRITEPROTECTION_DISABLE() before calling this function.
  * @param  hrtc RTC handle
  * @retval HAL status
  */
HAL_StatusTypeDef RTC_EnterInitMode(RTC_HandleTypeDef *hrtc)
{
  uint32_t tickstart;
  HAL_StatusTypeDef status = HAL_OK;
  /* Check if the Initialization mode is set */
#if defined(TAMP)
  if ((hrtc->Instance->ICSR & RTC_ICSR_INITF) == 0U)
  {
    /* Set the Initialization mode */
    SET_BIT(hrtc->Instance->ICSR, RTC_ICSR_INIT);

    tickstart = HAL_GetTick();

    /* Wait till RTC is in INIT state and if timeout is reached exit */
    while (((hrtc->Instance->ICSR & RTC_ICSR_INITF) == 0U) && (status != HAL_TIMEOUT))
#else
  if ((hrtc->Instance->ISR & RTC_ISR_INITF) == 0U)
  {
    /* Set the Initialization mode */
    hrtc->Instance->ISR = (uint32_t)RTC_INIT_MASK;

    tickstart = HAL_GetTick();

    /* Wait till RTC is in INIT state and if timeout is reached exit */
    while (((hrtc->Instance->ISR & RTC_ISR_INITF) == 0U) && (status != HAL_TIMEOUT))
#endif /* TAMP */
    {
      if((HAL_GetTick()  - tickstart) > RTC_TIMEOUT_VALUE)
      {
        status = HAL_TIMEOUT;
        hrtc->State = HAL_RTC_STATE_TIMEOUT;
      }
    }
  }

  return status;
}

/**
  * @brief  Exit the RTC Initialization mode.
  * @param  hrtc RTC handle
  * @retval HAL status
  */
HAL_StatusTypeDef RTC_ExitInitMode(RTC_HandleTypeDef *hrtc)
{
  HAL_StatusTypeDef status = HAL_OK;

  /* Check if the Initialization mode is set */

  /* Exit Initialization mode */
#if defined(TAMP)
  CLEAR_BIT(RTC->ICSR, RTC_ICSR_INIT);
#else
  CLEAR_BIT(RTC->ISR, RTC_ISR_INIT);
#endif /* TAMP */

  /* If CR_BYPSHAD bit = 0, wait for synchro */
  if (READ_BIT(RTC->CR, RTC_CR_BYPSHAD) == 0U)
  {
    if (HAL_RTC_WaitForSynchro(hrtc) != HAL_OK)
    {
      hrtc->State = HAL_RTC_STATE_TIMEOUT;
      status = HAL_TIMEOUT;
    }
  }
  else
  {
    /* Clear BYPSHAD bit */
    CLEAR_BIT(RTC->CR, RTC_CR_BYPSHAD);
    if (HAL_RTC_WaitForSynchro(hrtc) != HAL_OK)
    {
      hrtc->State = HAL_RTC_STATE_TIMEOUT;
      status = HAL_TIMEOUT;
    }
    /* Restore BYPSHAD bit */
    SET_BIT(RTC->CR, RTC_CR_BYPSHAD);
  }

  return status;
}

/**
  * @brief  Convert a 2 digit decimal to BCD format.
  * @param  Value Byte to be converted
  * @retval Converted byte
  */
uint8_t RTC_ByteToBcd2(uint8_t Value)
{
  uint32_t bcdhigh = 0U;
  uint8_t  bcdlow  = Value;

  while (bcdlow >= 10U)
  {
    bcdhigh++;
    bcdlow -= 10U;
  }

  return ((uint8_t)(bcdhigh << 4U) | bcdlow);
}

/**
  * @brief  Convert from 2 digit BCD to Binary.
  * @param  Value BCD value to be converted
  * @retval Converted word
  */
uint8_t RTC_Bcd2ToByte(uint8_t Value)
{
  uint8_t tmp;
  tmp = ((Value & 0xF0U) >> 4U) * 10U;
  return (tmp + (Value & 0x0FU));
}

/**
  * @}
  */

#endif /* HAL_RTC_MODULE_ENABLED */
/**
  * @}
  */

/**
  * @}
  */

