/**
  ******************************************************************************
  * @file    stm32mp1xx_hal_rtc_ex.c
  * @author  MCD Application Team
  * @brief   Extended RTC HAL module driver.
  *          This file provides firmware functions to manage the following
  *          functionalities of the Real Time Clock (RTC) Extended peripheral:
  *           + RTC Time Stamp functions
  *           + RTC Tamper functions
  *           + RTC Wake-up functions
  *           + Extended Control functions
  *           + Extended RTC features functions
  *
  @verbatim
  ==============================================================================
                  ##### How to use this driver #####
  ==============================================================================
  [..]
    (+) Enable the RTC domain access.
    (+) Configure the RTC Prescaler (Asynchronous and Synchronous) and RTC hour
        format using the HAL_RTC_Init() function.

  *** RTC Wakeup configuration ***
  ================================
  [..]
    (+) To configure the RTC Wakeup Clock source and Counter use the HAL_RTCEx_SetWakeUpTimer()
        function. You can also configure the RTC Wakeup timer with interrupt mode
        using the HAL_RTCEx_SetWakeUpTimer_IT() function.
    (+) To read the RTC WakeUp Counter register, use the HAL_RTCEx_GetWakeUpTimer()
        function.

  *** Outputs configuration ***
  =============================
  [..]  The RTC has 2 different outputs:
    (+) RTC_ALARM: this output is used to manage the RTC Alarm A, Alarm B
        and WaKeUp signals.
        To output the selected RTC signal, use the HAL_RTC_Init() function.
    (+) RTC_CALIB: this output is 512Hz signal or 1Hz.
        To enable the RTC_CALIB, use the HAL_RTCEx_SetCalibrationOutPut() function.
    (+) Two pins can be used as RTC_ALARM or RTC_CALIB (PC13, PB2) managed on
        the RTC_OR register.
    (+) When the RTC_CALIB or RTC_ALARM output is selected, the RTC_OUT pin is
        automatically configured in output alternate function.

  *** Smooth digital Calibration configuration ***
  ================================================
  [..]
    (+) Configure the RTC Original Digital Calibration Value and the corresponding
        calibration cycle period (32s,16s and 8s) using the HAL_RTCEx_SetSmoothCalib()
        function.

  *** TimeStamp configuration ***
  ===============================
  [..]
    (+) Enable the RTC TimeStamp using the HAL_RTCEx_SetTimeStamp() function.
        You can also configure the RTC TimeStamp with interrupt mode using the
        HAL_RTCEx_SetTimeStamp_IT() function.
    (+) To read the RTC TimeStamp Time and Date register, use the HAL_RTCEx_GetTimeStamp()
        function.

  *** Internal TimeStamp configuration ***
  ===============================
  [..]
    (+) Enable the RTC internal TimeStamp using the HAL_RTCEx_SetInternalTimeStamp() function.
        User has to check internal timestamp occurrence using __HAL_RTC_INTERNAL_TIMESTAMP_GET_FLAG.
    (+) To read the RTC TimeStamp Time and Date register, use the HAL_RTCEx_GetTimeStamp()
        function.

   *** Tamper configuration ***
   ============================
   [..]
     (+) Enable the RTC Tamper and configure the Tamper filter count, trigger Edge
         or Level according to the Tamper filter (if equal to 0 Edge else Level)
         value, sampling frequency, NoErase, MaskFlag,  precharge or discharge and
         Pull-UP using the HAL_RTCEx_SetTamper() function. You can configure RTC Tamper
         with interrupt mode using HAL_RTCEx_SetTamper_IT() function.
     (+) The default configuration of the Tamper erases the backup registers. To avoid
         erase, enable the NoErase field on the RTC_TAMPCR register.
     (+) With new RTC tamper configuration, you have to call HAL_RTC_Init() in order to
         perform TAMP base address offset calculation.
     (+) If you do not intend to have tamper using RTC clock, you can bypass its initialization
         by setting ClockEnable inti field to RTC_CLOCK_DISABLE.
     (+) Enable Internal tamper using HAL_RTCEx_SetInternalTamper. IT mode can be chosen using
         setting Interrupt field.

   *** Backup Data Registers configuration ***
   ===========================================
   [..]
     (+) To write to the RTC Backup Data registers, use the HAL_RTCEx_BKUPWrite()
         function.
     (+) To read the RTC Backup Data registers, use the HAL_RTCEx_BKUPRead()
         function.
     (+) Before calling these functions you have to call HAL_RTC_Init() in order to
         perform TAMP base address offset calculation.

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
#include "stm32mp1xx_hal.h"

/** @addtogroup STM32MP1xx_HAL_Driver
  * @{
  */

/** @addtogroup RTCEx
  * @brief RTC Extended HAL module driver
  * @{
  */

#ifdef HAL_RTC_MODULE_ENABLED

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
#define TAMP_ALL (TAMP_CR1_TAMP1E | TAMP_CR1_TAMP2E | TAMP_CR1_TAMP3E)


/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
/* Exported functions --------------------------------------------------------*/

/** @addtogroup RTCEx_Exported_Functions
  * @{
  */


/** @addtogroup RTCEx_Exported_Functions_Group1
 *  @brief   RTC TimeStamp and Tamper functions
  *
@verbatim
 ===============================================================================
                 ##### RTC TimeStamp and Tamper functions #####
 ===============================================================================

 [..] This section provides functions allowing to configure TimeStamp feature

@endverbatim
  * @{
  */

/**
  * @brief  Set TimeStamp.
  * @note   This API must be called before enabling the TimeStamp feature.
  * @param  hrtc RTC handle
  * @param  TimeStampEdge Specifies the pin edge on which the TimeStamp is
  *         activated.
  *          This parameter can be one of the following values:
  *             @arg RTC_TIMESTAMPEDGE_RISING: the Time stamp event occurs on the
  *                                        rising edge of the related pin.
  *             @arg RTC_TIMESTAMPEDGE_FALLING: the Time stamp event occurs on the
  *                                         falling edge of the related pin.
  * @param  RTC_TimeStampPin specifies the RTC TimeStamp Pin.
  *          This parameter can be one of the following values:
  *             @arg RTC_TIMESTAMPPIN_DEFAULT: PC13 is selected as RTC TimeStamp Pin.
  *               The RTC TimeStamp Pin is per default PC13, but for reasons of
  *               compatibility, this parameter is required.
  * @retval HAL status
  */
HAL_StatusTypeDef HAL_RTCEx_SetTimeStamp(RTC_HandleTypeDef *hrtc, uint32_t TimeStampEdge, uint32_t RTC_TimeStampPin)
{
  /* Check the parameters */
  assert_param(IS_TIMESTAMP_EDGE(TimeStampEdge));
  assert_param(IS_RTC_TIMESTAMP_PIN(RTC_TimeStampPin));
  UNUSED(RTC_TimeStampPin);

  /* Process Locked */
  __HAL_LOCK(hrtc);

  hrtc->State = HAL_RTC_STATE_BUSY;

  /* Get the RTC_CR register and clear the bits to be configured */
  CLEAR_BIT(RTC->CR, (RTC_CR_TSEDGE | RTC_CR_TSE));

  /* Disable the write protection for RTC registers */
  __HAL_RTC_WRITEPROTECTION_DISABLE(hrtc);

  /* Configure the Time Stamp TSEDGE and Enable bits */
  SET_BIT(RTC->CR, (uint32_t)TimeStampEdge | RTC_CR_TSE);

  /* Enable the write protection for RTC registers */
  __HAL_RTC_WRITEPROTECTION_ENABLE(hrtc);

  /* Change RTC state */
  hrtc->State = HAL_RTC_STATE_READY;

  /* Process Unlocked */
  __HAL_UNLOCK(hrtc);

  return HAL_OK;
}

/**
  * @brief  Set TimeStamp with Interrupt.
  * @note   This API must be called before enabling the TimeStamp feature.
  * @param  hrtc RTC handle
  * @param  TimeStampEdge Specifies the pin edge on which the TimeStamp is
  *         activated.
  *          This parameter can be one of the following values:
  *             @arg RTC_TIMESTAMPEDGE_RISING: the Time stamp event occurs on the
  *                                        rising edge of the related pin.
  *             @arg RTC_TIMESTAMPEDGE_FALLING: the Time stamp event occurs on the
  *                                         falling edge of the related pin.
  * @param  RTC_TimeStampPin Specifies the RTC TimeStamp Pin.
  *          This parameter can be one of the following values:
  *             @arg RTC_TIMESTAMPPIN_DEFAULT: PC13 is selected as RTC TimeStamp Pin.
  *               The RTC TimeStamp Pin is per default PC13, but for reasons of
  *               compatibility, this parameter is required.
  * @retval HAL status
  */
HAL_StatusTypeDef HAL_RTCEx_SetTimeStamp_IT(RTC_HandleTypeDef *hrtc, uint32_t TimeStampEdge, uint32_t RTC_TimeStampPin)
{
  /* Check the parameters */
  assert_param(IS_TIMESTAMP_EDGE(TimeStampEdge));
  assert_param(IS_RTC_TIMESTAMP_PIN(RTC_TimeStampPin));
  UNUSED(RTC_TimeStampPin);

  /* Process Locked */
  __HAL_LOCK(hrtc);

  hrtc->State = HAL_RTC_STATE_BUSY;

  /* RTC timestamp Interrupt Configuration: EXTI configuration */
  __HAL_RTC_TIMESTAMP_EXTI_ENABLE_IT();

  /* Get the RTC_CR register and clear the bits to be configured */
  CLEAR_BIT(RTC->CR, (RTC_CR_TSEDGE | RTC_CR_TSE));

  /* Disable the write protection for RTC registers */
  __HAL_RTC_WRITEPROTECTION_DISABLE(hrtc);

  /* Configure the Time Stamp TSEDGE before Enable bit to avoid unwanted TSF setting. */
  SET_BIT(RTC->CR, (uint32_t)TimeStampEdge);

  /* Enable timestamp and IT */
  SET_BIT(RTC->CR, RTC_CR_TSE | RTC_CR_TSIE);

  /* Enable the write protection for RTC registers */
  __HAL_RTC_WRITEPROTECTION_ENABLE(hrtc);

  hrtc->State = HAL_RTC_STATE_READY;

  /* Process Unlocked */
  __HAL_UNLOCK(hrtc);

  return HAL_OK;
}

/**
  * @brief  Deactivate TimeStamp.
  * @param  hrtc RTC handle
  * @retval HAL status
  */
HAL_StatusTypeDef HAL_RTCEx_DeactivateTimeStamp(RTC_HandleTypeDef *hrtc)
{
  /* Process Locked */
  __HAL_LOCK(hrtc);

  hrtc->State = HAL_RTC_STATE_BUSY;

  /* Disable the write protection for RTC registers */
  __HAL_RTC_WRITEPROTECTION_DISABLE(hrtc);

  /* In case of interrupt mode is used, the interrupt source must disabled */
  CLEAR_BIT(RTC->CR, (RTC_CR_TSEDGE | RTC_CR_TSE | RTC_CR_TSIE));

  /* Enable the write protection for RTC registers */
  __HAL_RTC_WRITEPROTECTION_ENABLE(hrtc);

  hrtc->State = HAL_RTC_STATE_READY;

  /* Process Unlocked */
  __HAL_UNLOCK(hrtc);

  return HAL_OK;
}

/**
  * @brief  Set Internal TimeStamp.
  * @note   This API must be called before enabling the internal TimeStamp feature.
  * @param  hrtc RTC handle
  * @retval HAL status
  */
HAL_StatusTypeDef HAL_RTCEx_SetInternalTimeStamp(RTC_HandleTypeDef *hrtc)
{
  /* Process Locked */
  __HAL_LOCK(hrtc);

  hrtc->State = HAL_RTC_STATE_BUSY;

  /* Disable the write protection for RTC registers */
  __HAL_RTC_WRITEPROTECTION_DISABLE(hrtc);

  /* Configure the internal Time Stamp Enable bits */
  SET_BIT(RTC->CR, RTC_CR_ITSE);

  /* Enable the write protection for RTC registers */
  __HAL_RTC_WRITEPROTECTION_ENABLE(hrtc);

  /* Change RTC state */
  hrtc->State = HAL_RTC_STATE_READY;

  /* Process Unlocked */
  __HAL_UNLOCK(hrtc);

  return HAL_OK;
}

/**
  * @brief  Deactivate Internal TimeStamp.
  * @param  hrtc RTC handle
  * @retval HAL status
  */
HAL_StatusTypeDef HAL_RTCEx_DeactivateInternalTimeStamp(RTC_HandleTypeDef *hrtc)
{
  /* Process Locked */
  __HAL_LOCK(hrtc);

  hrtc->State = HAL_RTC_STATE_BUSY;

  /* Disable the write protection for RTC registers */
  __HAL_RTC_WRITEPROTECTION_DISABLE(hrtc);

  /* Configure the internal Time Stamp Enable bits */
  CLEAR_BIT(RTC->CR, RTC_CR_ITSE);

  /* Enable the write protection for RTC registers */
  __HAL_RTC_WRITEPROTECTION_ENABLE(hrtc);

  hrtc->State = HAL_RTC_STATE_READY;

  /* Process Unlocked */
  __HAL_UNLOCK(hrtc);

  return HAL_OK;
}

/**
  * @brief  Get the RTC TimeStamp value.
  * @param  hrtc RTC handle
  * @param  sTimeStamp Pointer to Time structure
  * @param  sTimeStampDate Pointer to Date structure
  * @param  Format specifies the format of the entered parameters.
  *          This parameter can be one of the following values:
  *             @arg RTC_FORMAT_BIN: Binary data format
  *             @arg RTC_FORMAT_BCD: BCD data format
  * @retval HAL status
  */
HAL_StatusTypeDef HAL_RTCEx_GetTimeStamp(RTC_HandleTypeDef *hrtc, RTC_TimeTypeDef *sTimeStamp, RTC_DateTypeDef *sTimeStampDate, uint32_t Format)
{
  uint32_t tmptime, tmpdate;

  UNUSED(hrtc);
  /* Check the parameters */
  assert_param(IS_RTC_FORMAT(Format));

  /* Get the TimeStamp time and date registers values */
  tmptime = READ_BIT(RTC->TSTR, RTC_TR_RESERVED_MASK);
  tmpdate = READ_BIT(RTC->TSDR, RTC_DR_RESERVED_MASK);

  /* Fill the Time structure fields with the read parameters */
  sTimeStamp->Hours = (uint8_t)((tmptime & (RTC_TSTR_HT | RTC_TSTR_HU)) >> RTC_TSTR_HU_Pos);
  sTimeStamp->Minutes = (uint8_t)((tmptime & (RTC_TSTR_MNT | RTC_TSTR_MNU)) >> RTC_TSTR_MNU_Pos);
  sTimeStamp->Seconds = (uint8_t)((tmptime & (RTC_TSTR_ST | RTC_TSTR_SU)) >> RTC_TSTR_SU_Pos);
  sTimeStamp->TimeFormat = (uint8_t)((tmptime & (RTC_TSTR_PM)) >> RTC_TSTR_PM_Pos);
  sTimeStamp->SubSeconds = READ_BIT(RTC->TSSSR, RTC_TSSSR_SS);

  /* Fill the Date structure fields with the read parameters */
  sTimeStampDate->Year = 0U;
  sTimeStampDate->Month = (uint8_t)((tmpdate & (RTC_TSDR_MT | RTC_TSDR_MU)) >> RTC_TSDR_MU_Pos);
  sTimeStampDate->Date = (uint8_t)(tmpdate & (RTC_TSDR_DT | RTC_TSDR_DU));
  sTimeStampDate->WeekDay = (uint8_t)((tmpdate & (RTC_TSDR_WDU)) >> RTC_TSDR_WDU_Pos);

  /* Check the input parameters format */
  if (Format == RTC_FORMAT_BIN)
  {
    /* Convert the TimeStamp structure parameters to Binary format */
    sTimeStamp->Hours = (uint8_t)RTC_Bcd2ToByte(sTimeStamp->Hours);
    sTimeStamp->Minutes = (uint8_t)RTC_Bcd2ToByte(sTimeStamp->Minutes);
    sTimeStamp->Seconds = (uint8_t)RTC_Bcd2ToByte(sTimeStamp->Seconds);

    /* Convert the DateTimeStamp structure parameters to Binary format */
    sTimeStampDate->Month = (uint8_t)RTC_Bcd2ToByte(sTimeStampDate->Month);
    sTimeStampDate->Date = (uint8_t)RTC_Bcd2ToByte(sTimeStampDate->Date);
    sTimeStampDate->WeekDay = (uint8_t)RTC_Bcd2ToByte(sTimeStampDate->WeekDay);
  }

  /* Clear the TIMESTAMP Flags */
  WRITE_REG(RTC->SCR, (RTC_SCR_CITSF | RTC_SCR_CTSF));

  return HAL_OK;
}

#if defined (CORTEX_IN_SECURE_STATE)
/**
  * @brief  Handle TimeStamp secure interrupt request.
  * @param  hrtc RTC handle
  * @retval None
  */
void HAL_RTCEx_TimeStampIRQHandler(RTC_HandleTypeDef *hrtc)
{
  if (READ_BIT(RTC->SMISR, RTC_SMISR_TSMF) != 0U)
  {
#if (USE_HAL_RTC_REGISTER_CALLBACKS == 1)
    /* Call TimeStampEvent registered Callback */
    hrtc->TimeStampEventCallback(hrtc);
#else
    HAL_RTCEx_TimeStampEventCallback(hrtc);
#endif
    /* Clearing flags after the Callback because the content of RTC_TSTR and RTC_TSDR are cleared when TSF bit is reset.*/
    WRITE_REG(RTC->SCR, RTC_SCR_CITSF | RTC_SCR_CTSF);
  }

  /* Change RTC state */
  hrtc->State = HAL_RTC_STATE_READY;
}

#else /* #if defined (CORTEX_IN_SECURE_STATE) */

/**
  * @brief  Handle TimeStamp non-secure interrupt request.
  * @param  hrtc RTC handle
  * @retval None
  */
void HAL_RTCEx_TimeStampIRQHandler(RTC_HandleTypeDef *hrtc)
{
  if (READ_BIT(RTC->MISR, RTC_MISR_TSMF) != 0U)
  {
#if (USE_HAL_RTC_REGISTER_CALLBACKS == 1)
    /* Call TimeStampEvent registered Callback */
    hrtc->TimeStampEventCallback(hrtc);
#else
    HAL_RTCEx_TimeStampEventCallback(hrtc);
#endif
    /* Clearing flags after the Callback because the content of RTC_TSTR and RTC_TSDR are cleared when TSF bit is reset.*/
    WRITE_REG(RTC->SCR, RTC_SCR_CITSF | RTC_SCR_CTSF);
  }

  /* Change RTC state */
  hrtc->State = HAL_RTC_STATE_READY;
}
#endif /* #if defined (CORTEX_IN_SECURE_STATE) */

/**
  * @brief  TimeStamp callback.
  * @param  hrtc RTC handle
  * @retval None
  */
__weak void HAL_RTCEx_TimeStampEventCallback(RTC_HandleTypeDef *hrtc)
{
  /* Prevent unused argument(s) compilation warning */
  UNUSED(hrtc);

  /* NOTE : This function should not be modified, when the callback is needed,
            the HAL_RTCEx_TimeStampEventCallback could be implemented in the user file
  */
}

/**
  * @brief  Handle TimeStamp polling request.
  * @param  hrtc RTC handle
  * @param  Timeout Timeout duration
  * @retval HAL status
  */
HAL_StatusTypeDef HAL_RTCEx_PollForTimeStampEvent(RTC_HandleTypeDef *hrtc, uint32_t Timeout)
{
  uint32_t tickstart = HAL_GetTick();

  while (READ_BIT(RTC->SR, RTC_SR_TSF) == 0U)
  {
    if (READ_BIT(RTC->SR, RTC_SR_TSOVF) != 0U)
    {
      /* Clear the TIMESTAMP OverRun Flag */
      WRITE_REG(RTC->SCR, RTC_SCR_CTSOVF);

      /* Change TIMESTAMP state */
      hrtc->State = HAL_RTC_STATE_ERROR;

      return HAL_ERROR;
    }

    if (Timeout != HAL_MAX_DELAY)
    {
      if (((HAL_GetTick() - tickstart) > Timeout) || (Timeout == 0U))
      {
        hrtc->State = HAL_RTC_STATE_TIMEOUT;
        return HAL_TIMEOUT;
      }
    }
  }

  /* Change RTC state */
  hrtc->State = HAL_RTC_STATE_READY;

  return HAL_OK;
}

/**
  * @}
  */

/** @addtogroup RTCEx_Exported_Functions_Group2
  * @brief    RTC Wake-up functions
  *
@verbatim
 ===============================================================================
                        ##### RTC Wake-up functions #####
 ===============================================================================

 [..] This section provides functions allowing to configure Wake-up feature

@endverbatim
  * @{
  */

/**
  * @brief  Set wake up timer.
  * @param  hrtc RTC handle
  * @param  WakeUpCounter Wake up counter
  * @param  WakeUpClock Wake up clock
  * @retval HAL status
  */
HAL_StatusTypeDef HAL_RTCEx_SetWakeUpTimer(RTC_HandleTypeDef *hrtc, uint32_t WakeUpCounter, uint32_t WakeUpClock)
{
  uint32_t tickstart;

  /* Check the parameters */
  assert_param(IS_RTC_WAKEUP_CLOCK(WakeUpClock));
  assert_param(IS_RTC_WAKEUP_COUNTER(WakeUpCounter));

  /* Process Locked */
  __HAL_LOCK(hrtc);

  hrtc->State = HAL_RTC_STATE_BUSY;

  /* Disable the write protection for RTC registers */
  __HAL_RTC_WRITEPROTECTION_DISABLE(hrtc);

  /* Clear WUTE in RTC_CR to disable the wakeup timer */
  CLEAR_BIT(RTC->CR, RTC_CR_WUTE);

  /* Poll WUTWF until it is set in RTC_ICSR to make sure the access to wakeup autoreload
     counter and to WUCKSEL[2:0] bits is allowed. This step must be skipped in
     calendar initialization mode. */
  if (READ_BIT(RTC->ICSR, RTC_ICSR_INITF) == 0U)
  {
    tickstart = HAL_GetTick();
    while (READ_BIT(RTC->ICSR, RTC_ICSR_WUTWF) == 0U)
    {
      if ((HAL_GetTick() - tickstart) > RTC_TIMEOUT_VALUE)
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

  /* Configure the clock source */
  MODIFY_REG(RTC->CR, RTC_CR_WUCKSEL, (uint32_t)WakeUpClock);

  /* Configure the Wakeup Timer counter */
  WRITE_REG(RTC->WUTR, (uint32_t)WakeUpCounter);

  /* Enable the Wakeup Timer */
  SET_BIT(RTC->CR, RTC_CR_WUTE);

  /* Enable the write protection for RTC registers */
  __HAL_RTC_WRITEPROTECTION_ENABLE(hrtc);

  hrtc->State = HAL_RTC_STATE_READY;

  /* Process Unlocked */
  __HAL_UNLOCK(hrtc);

  return HAL_OK;
}

/**
  * @brief  Set wake up timer with interrupt.
  * @param  hrtc RTC handle
  * @param  WakeUpCounter Wake up counter
  * @param  WakeUpClock Wake up clock
  * @param  WakeUpAutoClr Wake up auto clear value (look at WUTOCLR in reference manual)
  *                       - No effect if WakeUpAutoClr is set to zero
  *                       - This feature is meaningful in case of Low power mode to avoid any RTC software execution after Wake Up.
  *                         That is why when WakeUpAutoClr is set, EXTI is configured as EVENT instead of Interrupt to avoid useless IRQ handler execution.
  * @retval HAL status
  */
HAL_StatusTypeDef HAL_RTCEx_SetWakeUpTimer_IT(RTC_HandleTypeDef *hrtc, uint32_t WakeUpCounter, uint32_t WakeUpClock, uint32_t WakeUpAutoClr)
{
  uint32_t tickstart;

  /* Check the parameters */
  assert_param(IS_RTC_WAKEUP_CLOCK(WakeUpClock));
  assert_param(IS_RTC_WAKEUP_COUNTER(WakeUpCounter));
  /* (0x0000<=WUTOCLR<=WUT) */
  assert_param(WakeUpAutoClr <= WakeUpCounter);

  /* Process Locked */
  __HAL_LOCK(hrtc);

  hrtc->State = HAL_RTC_STATE_BUSY;

  /* Disable the write protection for RTC registers */
  __HAL_RTC_WRITEPROTECTION_DISABLE(hrtc);

  /* Clear WUTE in RTC_CR to disable the wakeup timer */
  CLEAR_BIT(RTC->CR, RTC_CR_WUTE);

  /* Clear flag Wake-Up */
  WRITE_REG(RTC->SCR, RTC_SCR_CWUTF);

  /* Poll WUTWF until it is set in RTC_ICSR to make sure the access to wakeup autoreload
     counter and to WUCKSEL[2:0] bits is allowed. This step must be skipped in
     calendar initialization mode. */
  if (READ_BIT(RTC->ICSR, RTC_ICSR_INITF) == 0U)
  {
    tickstart = HAL_GetTick();
    while (READ_BIT(RTC->ICSR, RTC_ICSR_WUTWF) == 0U)
    {
      if ((HAL_GetTick() - tickstart) > RTC_TIMEOUT_VALUE)
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

  /* Configure the Wakeup Timer counter and auto clear value */
  WRITE_REG(RTC->WUTR, (uint32_t)(WakeUpCounter));

  /* Configure the clock source */
  MODIFY_REG(RTC->CR, RTC_CR_WUCKSEL, (uint32_t)WakeUpClock);

  /* In case of WUT autoclr, the IRQ handler should not be called */
  if (WakeUpAutoClr != 0U)
  {
    /* RTC WakeUpTimer EXTI Configuration: Event configuration */
    __HAL_RTC_WAKEUPTIMER_EXTI_ENABLE_EVENT();
  }
  else
  {
    /* RTC WakeUpTimer EXTI Configuration: Interrupt configuration */
    __HAL_RTC_WAKEUPTIMER_EXTI_ENABLE_IT();
  }

  /* Configure the Interrupt in the RTC_CR register and Enable the Wakeup Timer*/
  SET_BIT(RTC->CR, (RTC_CR_WUTIE | RTC_CR_WUTE));

  /* Enable the write protection for RTC registers */
  __HAL_RTC_WRITEPROTECTION_ENABLE(hrtc);

  hrtc->State = HAL_RTC_STATE_READY;

  /* Process Unlocked */
  __HAL_UNLOCK(hrtc);

  return HAL_OK;
}

/**
  * @brief  Deactivate wake up timer counter.
  * @param  hrtc RTC handle
  * @retval HAL status
  */
HAL_StatusTypeDef HAL_RTCEx_DeactivateWakeUpTimer(RTC_HandleTypeDef *hrtc)
{
  uint32_t tickstart;

  /* Process Locked */
  __HAL_LOCK(hrtc);

  hrtc->State = HAL_RTC_STATE_BUSY;

  /* Disable the write protection for RTC registers */
  __HAL_RTC_WRITEPROTECTION_DISABLE(hrtc);

  /* Disable the Wakeup Timer */
  /* In case of interrupt mode is used, the interrupt source must disabled */
  CLEAR_BIT(RTC->CR, (RTC_CR_WUTE | RTC_CR_WUTIE));

  tickstart = HAL_GetTick();
  /* Wait till RTC WUTWF flag is set and if Time out is reached exit */
  while (READ_BIT(RTC->ICSR, RTC_ICSR_WUTWF) == 0U)
  {
    if ((HAL_GetTick() - tickstart) > RTC_TIMEOUT_VALUE)
    {
      /* Enable the write protection for RTC registers */
      __HAL_RTC_WRITEPROTECTION_ENABLE(hrtc);

      hrtc->State = HAL_RTC_STATE_TIMEOUT;

      /* Process Unlocked */
      __HAL_UNLOCK(hrtc);

      return HAL_TIMEOUT;
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
  * @brief  Get wake up timer counter.
  * @param  hrtc RTC handle
  * @retval Counter value
  */
uint32_t HAL_RTCEx_GetWakeUpTimer(RTC_HandleTypeDef *hrtc)
{
  UNUSED(hrtc);
  /* Get the counter value */
  return (uint32_t)(READ_BIT(RTC->WUTR, RTC_WUTR_WUT));
}

#if defined (CORTEX_IN_SECURE_STATE)
/**
  * @brief  Handle Wake Up Timer secure interrupt request.
  * @param  hrtc RTC handle
  * @retval None
  */
void HAL_RTCEx_WakeUpTimerIRQHandler(RTC_HandleTypeDef *hrtc)
{
  if ((RTC->SMISR & RTC_SMISR_WUTMF) != 0u)
  {
    /* Immediatly clear flags */
    WRITE_REG(RTC->SCR, RTC_SCR_CWUTF);
#if (USE_HAL_RTC_REGISTER_CALLBACKS == 1)
    /* Call wake up timer registered Callback */
    hrtc->WakeUpTimerEventCallback(hrtc);
#else
    HAL_RTCEx_WakeUpTimerEventCallback(hrtc);
#endif
  }

  /* Change RTC state */
  hrtc->State = HAL_RTC_STATE_READY;
}

#else /* #if defined (CORTEX_IN_SECURE_STATE) */

/**
  * @brief  Handle Wake Up Timer non-secure interrupt request.
  * @param  hrtc RTC handle
  * @retval None
  */
void HAL_RTCEx_WakeUpTimerIRQHandler(RTC_HandleTypeDef *hrtc)
{
  /* Get the pending status of the WAKEUPTIMER Interrupt */
  if (READ_BIT(RTC->MISR, RTC_MISR_WUTMF) != 0U)
  {
    /* Clear the WAKEUPTIMER interrupt pending bit */
    WRITE_REG(RTC->SCR, RTC_SCR_CWUTF);

#if (USE_HAL_RTC_REGISTER_CALLBACKS == 1)
    /* Call WakeUpTimerEvent registered Callback */
    hrtc->WakeUpTimerEventCallback(hrtc);
#else
    /* WAKEUPTIMER callback */
    HAL_RTCEx_WakeUpTimerEventCallback(hrtc);
#endif /* USE_HAL_RTC_REGISTER_CALLBACKS */
  }

  /* Change RTC state */
  hrtc->State = HAL_RTC_STATE_READY;
}
#endif /* #if defined (CORTEX_IN_SECURE_STATE) */

/**
  * @brief  Wake Up Timer callback.
  * @param  hrtc RTC handle
  * @retval None
  */
__weak void HAL_RTCEx_WakeUpTimerEventCallback(RTC_HandleTypeDef *hrtc)
{
  /* Prevent unused argument(s) compilation warning */
  UNUSED(hrtc);

  /* NOTE : This function should not be modified, when the callback is needed,
            the HAL_RTCEx_WakeUpTimerEventCallback could be implemented in the user file
   */
}

/**
  * @brief  Handle Wake Up Timer Polling.
  * @param  hrtc RTC handle
  * @param  Timeout Timeout duration
  * @retval HAL status
  */
HAL_StatusTypeDef HAL_RTCEx_PollForWakeUpTimerEvent(RTC_HandleTypeDef *hrtc, uint32_t Timeout)
{
  uint32_t tickstart = HAL_GetTick();

  while (READ_BIT(RTC->SR, RTC_SR_WUTF) == 0U)
  {
    if (Timeout != HAL_MAX_DELAY)
    {
      if (((HAL_GetTick() - tickstart) > Timeout) || (Timeout == 0U))
      {
        hrtc->State = HAL_RTC_STATE_TIMEOUT;
        return HAL_TIMEOUT;
      }
    }
  }

  /* Clear the WAKEUPTIMER Flag */
  WRITE_REG(RTC->SCR, RTC_SCR_CWUTF);

  /* Change RTC state */
  hrtc->State = HAL_RTC_STATE_READY;

  return HAL_OK;
}

/**
  * @}
  */

/** @addtogroup RTCEx_Exported_Functions_Group3
  * @brief    Extended Peripheral Control functions
  *
@verbatim
 ===============================================================================
              ##### Extended Peripheral Control functions #####
 ===============================================================================
    [..]
    This subsection provides functions allowing to
      (+) Write a data in a specified RTC Backup data register
      (+) Read a data in a specified RTC Backup data register
      (+) Set the Coarse calibration parameters.
      (+) Deactivate the Coarse calibration parameters
      (+) Set the Smooth calibration parameters.
      (+) Set Low Power calibration parameter.
      (+) Configure the Synchronization Shift Control Settings.
      (+) Configure the Calibration Pinout (RTC_CALIB) Selection (1Hz or 512Hz).
      (+) Deactivate the Calibration Pinout (RTC_CALIB) Selection (1Hz or 512Hz).
      (+) Enable the RTC reference clock detection.
      (+) Disable the RTC reference clock detection.
      (+) Enable the Bypass Shadow feature.
      (+) Disable the Bypass Shadow feature.

@endverbatim
  * @{
  */

/**
  * @brief  Set the Smooth calibration parameters.
  * @note   To deactivate the smooth calibration, the field SmoothCalibPlusPulses
  *         must be equal to SMOOTHCALIB_PLUSPULSES_RESET and the field
  *         SmoothCalibMinusPulsesValue must be equal to 0.
  * @param  hrtc RTC handle
  * @param  SmoothCalibPeriod  Select the Smooth Calibration Period.
  *          This parameter can be can be one of the following values :
  *             @arg RTC_SMOOTHCALIB_PERIOD_32SEC: The smooth calibration period is 32s.
  *             @arg RTC_SMOOTHCALIB_PERIOD_16SEC: The smooth calibration period is 16s.
  *             @arg RTC_SMOOTHCALIB_PERIOD_8SEC: The smooth calibration period is 8s.
  * @param  SmoothCalibPlusPulses  Select to Set or reset the CALP bit.
  *          This parameter can be one of the following values:
  *             @arg RTC_SMOOTHCALIB_PLUSPULSES_SET: Add one RTCCLK pulse every 2*11 pulses.
  *             @arg RTC_SMOOTHCALIB_PLUSPULSES_RESET: No RTCCLK pulses are added.
  * @param  SmoothCalibMinusPulsesValue  Select the value of CALM[8:0] bits.
  *          This parameter can be one any value from 0 to 0x000001FF.
  * @retval HAL status
  */
HAL_StatusTypeDef HAL_RTCEx_SetSmoothCalib(RTC_HandleTypeDef *hrtc, uint32_t SmoothCalibPeriod, uint32_t SmoothCalibPlusPulses, uint32_t SmoothCalibMinusPulsesValue)
{
  uint32_t tickstart;

  /* Check the parameters */
  assert_param(IS_RTC_SMOOTH_CALIB_PERIOD(SmoothCalibPeriod));
  assert_param(IS_RTC_SMOOTH_CALIB_PLUS(SmoothCalibPlusPulses));
  assert_param(IS_RTC_SMOOTH_CALIB_MINUS(SmoothCalibMinusPulsesValue));

  /* Process Locked */
  __HAL_LOCK(hrtc);

  hrtc->State = HAL_RTC_STATE_BUSY;

  /* Disable the write protection for RTC registers */
  __HAL_RTC_WRITEPROTECTION_DISABLE(hrtc);

  /* check if a calibration is pending*/
  if (READ_BIT(RTC->ICSR, RTC_ICSR_RECALPF) != 0U)
  {
    tickstart = HAL_GetTick();

    /* check if a calibration is pending*/
    while (READ_BIT(RTC->ICSR, RTC_ICSR_RECALPF) != 0U)
    {
      if ((HAL_GetTick() - tickstart) > RTC_TIMEOUT_VALUE)
      {
        /* Enable the write protection for RTC registers */
        __HAL_RTC_WRITEPROTECTION_ENABLE(hrtc);

        /* Change RTC state */
        hrtc->State = HAL_RTC_STATE_TIMEOUT;

        /* Process Unlocked */
        __HAL_UNLOCK(hrtc);

        return HAL_TIMEOUT;
      }
    }
  }

  /* Configure the Smooth calibration settings */
  MODIFY_REG(RTC->CALR, (RTC_CALR_CALP | RTC_CALR_CALW8 | RTC_CALR_CALW16 | RTC_CALR_CALM), (uint32_t)(SmoothCalibPeriod | SmoothCalibPlusPulses | SmoothCalibMinusPulsesValue));

  /* Enable the write protection for RTC registers */
  __HAL_RTC_WRITEPROTECTION_ENABLE(hrtc);

  /* Change RTC state */
  hrtc->State = HAL_RTC_STATE_READY;

  /* Process Unlocked */
  __HAL_UNLOCK(hrtc);

  return HAL_OK;
}

/**
  * @brief  Configure the Synchronization Shift Control Settings.
  * @note   When REFCKON is set, firmware must not write to Shift control register.
  * @param  hrtc RTC handle
  * @param  ShiftAdd1S Select to add or not 1 second to the time calendar.
  *          This parameter can be one of the following values:
  *             @arg RTC_SHIFTADD1S_SET: Add one second to the clock calendar.
  *             @arg RTC_SHIFTADD1S_RESET: No effect.
  * @param  ShiftSubFS Select the number of Second Fractions to substitute.
  *          This parameter can be one any value from 0 to 0x7FFF.
  * @retval HAL status
  */
HAL_StatusTypeDef HAL_RTCEx_SetSynchroShift(RTC_HandleTypeDef *hrtc, uint32_t ShiftAdd1S, uint32_t ShiftSubFS)
{
  uint32_t tickstart;

  /* Check the parameters */
  assert_param(IS_RTC_SHIFT_ADD1S(ShiftAdd1S));
  assert_param(IS_RTC_SHIFT_SUBFS(ShiftSubFS));

  /* Process Locked */
  __HAL_LOCK(hrtc);

  hrtc->State = HAL_RTC_STATE_BUSY;

  /* Disable the write protection for RTC registers */
  __HAL_RTC_WRITEPROTECTION_DISABLE(hrtc);

  tickstart = HAL_GetTick();

  /* Wait until the shift is completed*/
  while (READ_BIT(RTC->ICSR, RTC_ICSR_SHPF) != 0U)
  {
    if ((HAL_GetTick() - tickstart) > RTC_TIMEOUT_VALUE)
    {
      /* Enable the write protection for RTC registers */
      __HAL_RTC_WRITEPROTECTION_ENABLE(hrtc);

      hrtc->State = HAL_RTC_STATE_TIMEOUT;

      /* Process Unlocked */
      __HAL_UNLOCK(hrtc);

      return HAL_TIMEOUT;
    }
  }

  /* Check if the reference clock detection is disabled */
  if (READ_BIT(RTC->CR, RTC_CR_REFCKON) == 0U)
  {
    /* Configure the Shift settings */
    MODIFY_REG(RTC->SHIFTR, RTC_SHIFTR_SUBFS, (uint32_t)(ShiftSubFS) | (uint32_t)(ShiftAdd1S));

    /* If  RTC_CR_BYPSHAD bit = 0, wait for synchro else this check is not needed */
    if (READ_BIT(RTC->CR, RTC_CR_BYPSHAD) == 0U)
    {
      if (HAL_RTC_WaitForSynchro(hrtc) != HAL_OK)
      {
        /* Enable the write protection for RTC registers */
        __HAL_RTC_WRITEPROTECTION_ENABLE(hrtc);

        hrtc->State = HAL_RTC_STATE_ERROR;

        /* Process Unlocked */
        __HAL_UNLOCK(hrtc);

        return HAL_ERROR;
      }
    }
  }
  else
  {
    /* Enable the write protection for RTC registers */
    __HAL_RTC_WRITEPROTECTION_ENABLE(hrtc);

    /* Change RTC state */
    hrtc->State = HAL_RTC_STATE_ERROR;

    /* Process Unlocked */
    __HAL_UNLOCK(hrtc);

    return HAL_ERROR;
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
  * @brief  Configure the Calibration Pinout (RTC_CALIB) Selection (1Hz or 512Hz).
  * @param  hrtc RTC handle
  * @param  CalibOutput Select the Calibration output Selection .
  *          This parameter can be one of the following values:
  *             @arg RTC_CALIBOUTPUT_512HZ: A signal has a regular waveform at 512Hz.
  *             @arg RTC_CALIBOUTPUT_1HZ: A signal has a regular waveform at 1Hz.
  * @retval HAL status
  */
HAL_StatusTypeDef HAL_RTCEx_SetCalibrationOutPut(RTC_HandleTypeDef *hrtc, uint32_t CalibOutput)
{
  /* Check the parameters */
  assert_param(IS_RTC_CALIB_OUTPUT(CalibOutput));

  /* Process Locked */
  __HAL_LOCK(hrtc);

  hrtc->State = HAL_RTC_STATE_BUSY;

  /* Disable the write protection for RTC registers */
  __HAL_RTC_WRITEPROTECTION_DISABLE(hrtc);

  /* Configure the RTC_CR register */
  MODIFY_REG(RTC->CR, RTC_CR_COSEL, CalibOutput);

  /* Enable calibration output */
  SET_BIT(RTC->CR, RTC_CR_COE);

  /* Enable the write protection for RTC registers */
  __HAL_RTC_WRITEPROTECTION_ENABLE(hrtc);

  /* Change RTC state */
  hrtc->State = HAL_RTC_STATE_READY;

  /* Process Unlocked */
  __HAL_UNLOCK(hrtc);

  return HAL_OK;
}

/**
  * @brief  Deactivate the Calibration Pinout (RTC_CALIB) Selection (1Hz or 512Hz).
  * @param  hrtc RTC handle
  * @retval HAL status
  */
HAL_StatusTypeDef HAL_RTCEx_DeactivateCalibrationOutPut(RTC_HandleTypeDef *hrtc)
{
  /* Process Locked */
  __HAL_LOCK(hrtc);

  hrtc->State = HAL_RTC_STATE_BUSY;

  /* Disable the write protection for RTC registers */
  __HAL_RTC_WRITEPROTECTION_DISABLE(hrtc);

  /* Disable calibration output */
  CLEAR_BIT(RTC->CR, RTC_CR_COE);

  /* Enable the write protection for RTC registers */
  __HAL_RTC_WRITEPROTECTION_ENABLE(hrtc);

  /* Change RTC state */
  hrtc->State = HAL_RTC_STATE_READY;

  /* Process Unlocked */
  __HAL_UNLOCK(hrtc);

  return HAL_OK;
}

/**
  * @brief  Enable the RTC reference clock detection.
  * @param  hrtc RTC handle
  * @retval HAL status
  */
HAL_StatusTypeDef HAL_RTCEx_SetRefClock(RTC_HandleTypeDef *hrtc)
{
  HAL_StatusTypeDef status;

  /* Process Locked */
  __HAL_LOCK(hrtc);

  hrtc->State = HAL_RTC_STATE_BUSY;

  /* Disable the write protection for RTC registers */
  __HAL_RTC_WRITEPROTECTION_DISABLE(hrtc);

  /* Enter Initialization mode */
  status = RTC_EnterInitMode(hrtc);
  if (status == HAL_OK)
  {
    /* Enable clockref detection */
    SET_BIT(RTC->CR, RTC_CR_REFCKON);

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
  * @brief  Disable the RTC reference clock detection.
  * @param  hrtc RTC handle
  * @retval HAL status
  */
HAL_StatusTypeDef HAL_RTCEx_DeactivateRefClock(RTC_HandleTypeDef *hrtc)
{
  HAL_StatusTypeDef status;

  /* Process Locked */
  __HAL_LOCK(hrtc);

  hrtc->State = HAL_RTC_STATE_BUSY;

  /* Disable the write protection for RTC registers */
  __HAL_RTC_WRITEPROTECTION_DISABLE(hrtc);

  /* Enter Initialization mode */
  status = RTC_EnterInitMode(hrtc);
  if (status == HAL_OK)
  {
    /* Disable clockref detection */
    CLEAR_BIT(RTC->CR, RTC_CR_REFCKON);

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
  * @brief  Enable the Bypass Shadow feature.
  * @note   When the Bypass Shadow is enabled the calendar value are taken
  *         directly from the Calendar counter.
  * @param  hrtc RTC handle
  * @retval HAL status
  */
HAL_StatusTypeDef HAL_RTCEx_EnableBypassShadow(RTC_HandleTypeDef *hrtc)
{
  /* Process Locked */
  __HAL_LOCK(hrtc);

  hrtc->State = HAL_RTC_STATE_BUSY;

  /* Disable the write protection for RTC registers */
  __HAL_RTC_WRITEPROTECTION_DISABLE(hrtc);

  /* Set the BYPSHAD bit */
  SET_BIT(RTC->CR, RTC_CR_BYPSHAD);

  /* Enable the write protection for RTC registers */
  __HAL_RTC_WRITEPROTECTION_ENABLE(hrtc);

  /* Change RTC state */
  hrtc->State = HAL_RTC_STATE_READY;

  /* Process Unlocked */
  __HAL_UNLOCK(hrtc);

  return HAL_OK;
}

/**
  * @brief  Disable the Bypass Shadow feature.
  * @note   When the Bypass Shadow is enabled the calendar value are taken
  *         directly from the Calendar counter.
  * @param  hrtc RTC handle
  * @retval HAL status
  */
HAL_StatusTypeDef HAL_RTCEx_DisableBypassShadow(RTC_HandleTypeDef *hrtc)
{
  /* Process Locked */
  __HAL_LOCK(hrtc);

  hrtc->State = HAL_RTC_STATE_BUSY;

  /* Disable the write protection for RTC registers */
  __HAL_RTC_WRITEPROTECTION_DISABLE(hrtc);

  /* Reset the BYPSHAD bit */
  CLEAR_BIT(RTC->CR, RTC_CR_BYPSHAD);

  /* Enable the write protection for RTC registers */
  __HAL_RTC_WRITEPROTECTION_ENABLE(hrtc);

  /* Change RTC state */
  hrtc->State = HAL_RTC_STATE_READY;

  /* Process Unlocked */
  __HAL_UNLOCK(hrtc);

  return HAL_OK;
}

/**
  * @brief  Increment Monotonic counter.
  * @param  hrtc RTC handle
  * @param  Instance  Monotonic counter Instance
  *         This parameter can be can be one of the following values :
  *           @arg RTC_MONOTONIC_COUNTER_1
  * @retval HAL status
  */
HAL_StatusTypeDef HAL_RTCEx_MonotonicCounterIncrement(RTC_HandleTypeDef *hrtc, uint32_t Instance)
{
  UNUSED(hrtc);
  UNUSED(Instance);
  /* This register is read-only only and is incremented by one when a write access is done to this
     register. This register cannot roll-over and is frozen when reaching the maximum value. */
  CLEAR_REG(TAMP->COUNTR);

  return HAL_OK;
}

/**
  * @brief  Monotonic counter incrementation.
  * @param  hrtc RTC handle
  * @param  Instance  Monotonic counter Instance
  *         This parameter can be can be one of the following values :
  *           @arg RTC_MONOTONIC_COUNTER_1
  * @param  Value Pointer to the counter monotonic counter value
  * @retval HAL status
  */
HAL_StatusTypeDef HAL_RTCEx_MonotonicCounterGet(RTC_HandleTypeDef *hrtc, uint32_t Instance, uint32_t *Value)
{
  UNUSED(hrtc);
  UNUSED(Instance);

  /* This register is read-only only and is incremented by one when a write access is done to this
     register. This register cannot roll-over and is frozen when reaching the maximum value. */
  *Value = READ_REG(TAMP->COUNTR);

  return HAL_OK;
}

/**
  * @}
  */

/** @addtogroup RTCEx_Exported_Functions_Group4
  * @brief    Extended features functions
  *
@verbatim
 ===============================================================================
                 ##### Extended features functions #####
 ===============================================================================
    [..]  This section provides functions allowing to:
      (+) RTC Alarm B callback
      (+) RTC Poll for Alarm B request

@endverbatim
  * @{
  */

/**
  * @brief  Alarm B callback.
  * @param  hrtc RTC handle
  * @retval None
  */
__weak void HAL_RTCEx_AlarmBEventCallback(RTC_HandleTypeDef *hrtc)
{
  /* Prevent unused argument(s) compilation warning */
  UNUSED(hrtc);

  /* NOTE : This function should not be modified, when the callback is needed,
            the HAL_RTCEx_AlarmBEventCallback could be implemented in the user file
   */
}

/**
  * @brief  Handle Alarm B Polling request.
  * @param  hrtc RTC handle
  * @param  Timeout Timeout duration
  * @retval HAL status
  */
HAL_StatusTypeDef HAL_RTCEx_PollForAlarmBEvent(RTC_HandleTypeDef *hrtc, uint32_t Timeout)
{
  uint32_t tickstart = HAL_GetTick();

  while (READ_BIT(RTC->SR, RTC_SR_ALRBF) == 0U)
  {
    if (Timeout != HAL_MAX_DELAY)
    {
      if (((HAL_GetTick() - tickstart) > Timeout) || (Timeout == 0U))
      {
        hrtc->State = HAL_RTC_STATE_TIMEOUT;
        return HAL_TIMEOUT;
      }
    }
  }

  /* Clear the Alarm Flag */
  WRITE_REG(RTC->SCR, RTC_SCR_CALRBF);

  /* Change RTC state */
  hrtc->State = HAL_RTC_STATE_READY;

  return HAL_OK;
}

/**
  * @}
  */

/** @addtogroup RTCEx_Exported_Functions_Group5
  * @brief      Extended RTC Tamper functions
  *
@verbatim
  ==============================================================================
                         ##### Tamper functions #####
  ==============================================================================
  [..]
   (+) Before calling any tamper or internal tamper function, you have to call first
       HAL_RTC_Init() function.
   (+) In that ine you can select to output tamper event on RTC pin.
  [..]
   (+) Enable the Tamper and configure the Tamper filter count, trigger Edge
       or Level according to the Tamper filter (if equal to 0 Edge else Level)
       value, sampling frequency, NoErase, MaskFlag, precharge or discharge and
       Pull-UP, timestamp using the HAL_RTCEx_SetTamper() function.
       You can configure Tamper with interrupt mode using HAL_RTCEx_SetTamper_IT() function.
   (+) The default configuration of the Tamper erases the backup registers. To avoid
       erase, enable the NoErase field on the TAMP_TAMPCR register.
  [..]
   (+) Enable Internal Tamper and configure it with interrupt, timestamp using
       the HAL_RTCEx_SetInternalTamper() function.

@endverbatim
  * @{
  */


/**
  * @brief  Set Tamper
  * @param  hrtc RTC handle
  * @param  sTamper Pointer to Tamper Structure.
  * @retval HAL status
  */
HAL_StatusTypeDef HAL_RTCEx_SetTamper(RTC_HandleTypeDef *hrtc, RTC_TamperTypeDef *sTamper)
{
  uint32_t tmpreg;

  /* Prevent unused argument(s) compilation warning */
  UNUSED(hrtc);

  /* Check the parameters */
  assert_param(IS_RTC_TAMPER(sTamper->Tamper));
  assert_param(IS_RTC_TAMPER_TRIGGER(sTamper->Trigger));
  assert_param(IS_RTC_TAMPER_ERASE_MODE(sTamper->NoErase));
  assert_param(IS_RTC_TAMPER_MASKFLAG_STATE(sTamper->MaskFlag));
  assert_param(IS_RTC_TAMPER_TIMESTAMPONTAMPER_DETECTION(sTamper->TimeStampOnTamperDetection));
  /* Mask flag only supported by TAMPER 1, 2 and 3 */
  assert_param(!((sTamper->MaskFlag != RTC_TAMPERMASK_FLAG_DISABLE) && (sTamper->Tamper > RTC_TAMPER_3)));
  assert_param(IS_RTC_TAMPER_FILTER(sTamper->Filter));
  assert_param(IS_RTC_TAMPER_SAMPLING_FREQ(sTamper->SamplingFrequency));
  assert_param(IS_RTC_TAMPER_PRECHARGE_DURATION(sTamper->PrechargeDuration));
  assert_param(IS_RTC_TAMPER_PULLUP_STATE(sTamper->TamperPullUp));
  /* Trigger and Filter have exclusive configurations */
  assert_param(((sTamper->Filter != RTC_TAMPERFILTER_DISABLE) && ((sTamper->Trigger == RTC_TAMPERTRIGGER_LOWLEVEL) || (sTamper->Trigger == RTC_TAMPERTRIGGER_HIGHLEVEL)))
               || ((sTamper->Filter == RTC_TAMPERFILTER_DISABLE) && ((sTamper->Trigger == RTC_TAMPERTRIGGER_RISINGEDGE) || (sTamper->Trigger == RTC_TAMPERTRIGGER_FALLINGEDGE))));

  /* Configuration register 2 */
  tmpreg = READ_REG(TAMP->CR2);
  tmpreg &= ~((sTamper->Tamper << TAMP_CR2_TAMP1TRG_Pos) | (sTamper->Tamper << TAMP_CR2_TAMP1MSK_Pos) | (sTamper->Tamper << TAMP_CR2_TAMP1NOERASE_Pos));

  if ((sTamper->Trigger == RTC_TAMPERTRIGGER_HIGHLEVEL) || (sTamper->Trigger == RTC_TAMPERTRIGGER_FALLINGEDGE))
  {
    tmpreg |= (sTamper->Tamper << TAMP_CR2_TAMP1TRG_Pos);
  }

  if (sTamper->MaskFlag != RTC_TAMPERMASK_FLAG_DISABLE)
  {
    tmpreg |= (sTamper->Tamper << TAMP_CR2_TAMP1MSK_Pos);
  }

  if (sTamper->NoErase != RTC_TAMPER_ERASE_BACKUP_ENABLE)
  {
    tmpreg |= (sTamper->Tamper << TAMP_CR2_TAMP1NOERASE_Pos);
  }
  WRITE_REG(TAMP->CR2, tmpreg);

  /* Filter control register */
  WRITE_REG(TAMP->FLTCR, sTamper->Filter | sTamper->SamplingFrequency | sTamper->PrechargeDuration | sTamper->TamperPullUp);

  /* Timestamp on tamper */
  if (READ_BIT(RTC->CR, RTC_CR_TAMPTS) != sTamper->TimeStampOnTamperDetection)
  {
    __HAL_RTC_WRITEPROTECTION_DISABLE(hrtc);
    MODIFY_REG(RTC->CR, RTC_CR_TAMPTS, sTamper->TimeStampOnTamperDetection);
    __HAL_RTC_WRITEPROTECTION_ENABLE(hrtc);
  }

  /* Control register 1 */
  SET_BIT(TAMP->CR1, sTamper->Tamper);

  return HAL_OK;
}


/**
  * @brief  Set Tamper in IT mode
  * @param  hrtc RTC handle
  * @param  sTamper Pointer to Tamper Structure.
  * @retval HAL status
  */
HAL_StatusTypeDef HAL_RTCEx_SetTamper_IT(RTC_HandleTypeDef *hrtc, RTC_TamperTypeDef *sTamper)
{
  uint32_t tmpreg;

  /* Prevent unused argument(s) compilation warning */
  UNUSED(hrtc);

  /* Check the parameters */
  assert_param(IS_RTC_TAMPER(sTamper->Tamper));
  assert_param(IS_RTC_TAMPER_TRIGGER(sTamper->Trigger));
  assert_param(IS_RTC_TAMPER_ERASE_MODE(sTamper->NoErase));
  assert_param(IS_RTC_TAMPER_MASKFLAG_STATE(sTamper->MaskFlag));
  assert_param(IS_RTC_TAMPER_FILTER(sTamper->Filter));
  assert_param(IS_RTC_TAMPER_SAMPLING_FREQ(sTamper->SamplingFrequency));
  assert_param(IS_RTC_TAMPER_PRECHARGE_DURATION(sTamper->PrechargeDuration));
  assert_param(IS_RTC_TAMPER_PULLUP_STATE(sTamper->TamperPullUp));
  assert_param(IS_RTC_TAMPER_TIMESTAMPONTAMPER_DETECTION(sTamper->TimeStampOnTamperDetection));

  /* Configuration register 2 */
  tmpreg = READ_REG(TAMP->CR2);
  tmpreg &= ~((sTamper->Tamper << TAMP_CR2_TAMP1TRG_Pos) | (sTamper->Tamper << TAMP_CR2_TAMP1MSK_Pos) | (sTamper->Tamper << TAMP_CR2_TAMP1NOERASE_Pos));

  if (sTamper->Trigger != RTC_TAMPERTRIGGER_RISINGEDGE)
  {
    tmpreg |= (sTamper->Tamper << TAMP_CR2_TAMP1TRG_Pos);
  }

  if (sTamper->MaskFlag != RTC_TAMPERMASK_FLAG_DISABLE)
  {
    /* Feature only supported by TAMPER 1, 2 and 3 */
    if (sTamper->Tamper <= RTC_TAMPER_3)
    {
      tmpreg |= (sTamper->Tamper << TAMP_CR2_TAMP1MSK_Pos);
    }
    else
    {
      return HAL_ERROR;
    }
  }

  if (sTamper->NoErase != RTC_TAMPER_ERASE_BACKUP_ENABLE)
  {
    tmpreg |= (sTamper->Tamper << TAMP_CR2_TAMP1NOERASE_Pos);
  }
  WRITE_REG(TAMP->CR2, tmpreg);

  /* Filter control register */
  WRITE_REG(TAMP->FLTCR, sTamper->Filter | sTamper->SamplingFrequency | sTamper->PrechargeDuration | sTamper->TamperPullUp);

  /* Timestamp on tamper */
  if (READ_BIT(RTC->CR, RTC_CR_TAMPTS) != sTamper->TimeStampOnTamperDetection)
  {
    __HAL_RTC_WRITEPROTECTION_DISABLE(hrtc);
    MODIFY_REG(RTC->CR, RTC_CR_TAMPTS, sTamper->TimeStampOnTamperDetection);
    __HAL_RTC_WRITEPROTECTION_ENABLE(hrtc);
  }

  /* RTC Tamper Interrupt Configuration: EXTI configuration */
  __HAL_RTC_TAMPER_EXTI_ENABLE_IT();

  /* Interrupt enable register */
  SET_BIT(TAMP->IER, sTamper->Tamper);

  /* Control register 1 */
  SET_BIT(TAMP->CR1, sTamper->Tamper);

  return HAL_OK;
}

/**
  * @brief  Deactivate Tamper.
  * @param  hrtc RTC handle
  * @param  Tamper Selected tamper pin.
  *         This parameter can be a combination of the following values:
  *         @arg RTC_TAMPER_1
  *         @arg RTC_TAMPER_2
  *         @arg RTC_TAMPER_3
  *         @arg RTC_TAMPER_4
  *         @arg RTC_TAMPER_5
  *         @arg RTC_TAMPER_6
  *         @arg RTC_TAMPER_7
  *         @arg RTC_TAMPER_8
  * @retval HAL status
  */
HAL_StatusTypeDef HAL_RTCEx_DeactivateTamper(RTC_HandleTypeDef *hrtc, uint32_t Tamper)
{
  UNUSED(hrtc);
  assert_param(IS_RTC_TAMPER(Tamper));

  /* Disable the selected Tamper pin */
  CLEAR_BIT(TAMP->CR1, Tamper);

  /* Clear tamper mask/noerase/trigger configuration */
  CLEAR_BIT(TAMP->CR2, (Tamper << TAMP_CR2_TAMP1TRG_Pos) | (Tamper << TAMP_CR2_TAMP1MSK_Pos) | (Tamper << TAMP_CR2_TAMP1NOERASE_Pos));

  /* Clear tamper interrupt mode configuration */
  CLEAR_BIT(TAMP->IER, Tamper);

  /* Clear tamper interrupt and event flags (WO register) */
  WRITE_REG(TAMP->SCR, Tamper);

  return HAL_OK;
}

/**
  * @brief  Set all active Tampers at the same time.
  * @param  hrtc RTC handle
  * @param  sAllTamper Pointer to active Tamper Structure.
  * @retval HAL status
  */
HAL_StatusTypeDef HAL_RTCEx_SetActiveTampers(RTC_HandleTypeDef *hrtc, RTC_ActiveTampersTypeDef *sAllTamper)
{
  uint32_t IER, CR1, CR2, ATCR1, CR, i, tickstart;

#ifdef  USE_FULL_ASSERT
  for (i = 0; i < RTC_TAMP_NB; i++)
  {
    assert_param(IS_RTC_TAMPER_ERASE_MODE(sAllTamper->TampInput[i].NoErase));
    assert_param(IS_RTC_TAMPER_MASKFLAG_STATE(sAllTamper->TampInput[i].MaskFlag));
    /* Mask flag only supported by TAMPER 1, 2 and 3 */
    assert_param(!((sAllTamper->TampInput[i].MaskFlag != RTC_TAMPERMASK_FLAG_DISABLE) && (i > RTC_TAMPER_3)));
  }
  assert_param(IS_RTC_TAMPER_TIMESTAMPONTAMPER_DETECTION(sAllTamper->TimeStampOnTamperDetection));
#endif /* #ifdef  USE_FULL_ASSERT */

  /* Active Tampers must not be already enabled */
  if (READ_BIT(TAMP->ATOR, TAMP_ATOR_INITS) != 0U)
  {
    /* Disable all actives tampers with HAL_RTCEx_DeactivateActiveTampers and try again */
    return HAL_ERROR;
  }

  /* Set TimeStamp on tamper detection */
  CR = READ_REG(RTC->CR);
  if ((CR & RTC_CR_TAMPTS) != (sAllTamper->TimeStampOnTamperDetection))
  {
    __HAL_RTC_WRITEPROTECTION_DISABLE(hrtc);
    MODIFY_REG(RTC->CR, RTC_CR_TAMPTS, sAllTamper->TimeStampOnTamperDetection);
    __HAL_RTC_WRITEPROTECTION_ENABLE(hrtc);
  }

  CR1 = READ_REG(TAMP->CR1);
  CR2 = READ_REG(TAMP->CR2);
  IER = READ_REG(TAMP->IER);

  /* Set common parameters */
  ATCR1 = (sAllTamper->ActiveFilter | (sAllTamper->ActiveOutputChangePeriod << TAMP_ATCR1_ATPER_Pos) | sAllTamper->ActiveAsyncPrescaler);

  /* Set specific parameters for each active tamper inputs if enable */
  for (i = 0; i < RTC_TAMP_NB; i++)
  {
    if (sAllTamper->TampInput[i].Enable != RTC_ATAMP_DISABLE)
    {
      CR1 |= (TAMP_CR1_TAMP1E << i);
      ATCR1 |= (TAMP_ATCR1_TAMP1AM << i);

      if (sAllTamper->TampInput[i].Interrupt != RTC_ATAMP_INTERRUPT_DISABLE)
      {
        /* RTC Tamper Interrupt Configuration: EXTI configuration */
        __HAL_RTC_TAMPER_EXTI_ENABLE_IT();

        /* Interrupt enable register */
        IER |= (TAMP_IER_TAMP1IE << i);
      }

      if (sAllTamper->TampInput[i].MaskFlag != RTC_TAMPERMASK_FLAG_DISABLE)
      {
        CR2 |= (TAMP_CR2_TAMP1MSK << i);
      }

      if (sAllTamper->TampInput[i].NoErase != RTC_TAMPER_ERASE_BACKUP_ENABLE)
      {
        CR2 |= (TAMP_CR2_TAMP1NOERASE << i);
      }

      if (i != sAllTamper->TampInput[i].Output)
      {
        ATCR1 |= TAMP_ATCR1_ATOSHARE;
      }
    }
  }

  WRITE_REG(TAMP->IER, IER);
  WRITE_REG(TAMP->IER, IER);
  WRITE_REG(TAMP->ATCR1, ATCR1);
  WRITE_REG(TAMP->CR2, CR2);
  WRITE_REG(TAMP->CR1, CR1);

  /* Write seed */
  for (i = 0; i < RTC_ATAMP_SEED_NB_UINT32; i++)
  {
    WRITE_REG(TAMP->ATSEEDR, sAllTamper->Seed[i]);
  }

  /* Wait till RTC SEEDF flag is set and if Time out is reached exit */
  tickstart = HAL_GetTick();
  while (READ_BIT(TAMP->ATOR,  TAMP_ATOR_SEEDF) != 0u)
  {
    if ((HAL_GetTick() - tickstart) > RTC_TIMEOUT_VALUE)
    {
      hrtc->State = HAL_RTC_STATE_TIMEOUT;
      return HAL_TIMEOUT;
    }
  }

  return HAL_OK;
}

/**
  * @brief  Write a new seed. Active tamper must be enabled.
  * @param  hrtc RTC handle
  * @param  pSeed Pointer to active tamper seed values.
  * @retval HAL status
  */
HAL_StatusTypeDef HAL_RTCEx_SetActiveSeed(RTC_HandleTypeDef *hrtc, uint32_t *pSeed)
{
  uint32_t i, tickstart;

  /* Active Tampers must be enabled */
  if (READ_BIT(TAMP->ATOR,  TAMP_ATOR_INITS) == 0U)
  {
    return HAL_ERROR;
  }

  for (i = 0; i < RTC_ATAMP_SEED_NB_UINT32; i++)
  {
    WRITE_REG(TAMP->ATSEEDR, pSeed[i]);
  }

  /* Wait till RTC SEEDF flag is set and if Time out is reached exit */
  tickstart = HAL_GetTick();
  while (READ_BIT(TAMP->ATOR,  TAMP_ATOR_SEEDF) != 0U)
  {
    if ((HAL_GetTick() - tickstart) > RTC_TIMEOUT_VALUE)
    {
      hrtc->State = HAL_RTC_STATE_TIMEOUT;
      return HAL_TIMEOUT;
    }
  }

  return HAL_OK;
}

/**
  * @brief  Deactivate all Active Tampers at the same time.
  * @param  hrtc RTC handle
  * @retval HAL status
  */
HAL_StatusTypeDef HAL_RTCEx_DeactivateActiveTampers(RTC_HandleTypeDef *hrtc)
{
  /* Get Active tampers */
  uint32_t ATamp_mask = READ_BIT(TAMP->ATCR1, TAMP_ALL);

  UNUSED(hrtc);
  /* Disable all actives tampers but not passives tampers */
  CLEAR_BIT(TAMP->CR1, ATamp_mask);
  /* Disable no erase and mask */
  CLEAR_BIT(TAMP->CR2, (ATamp_mask | ((ATamp_mask & (TAMP_ATCR1_TAMP1AM | TAMP_ATCR1_TAMP2AM | TAMP_ATCR1_TAMP3AM)) << TAMP_CR2_TAMP1MSK_Pos)));

  /* Clear tamper interrupt and event flags (WO register) of all actives tampers but not passives tampers */
  WRITE_REG(TAMP->SCR, ATamp_mask);

  /* Clear all active tampers interrupt mode configuration but not passives tampers */
  CLEAR_BIT(TAMP->IER, ATamp_mask);

  CLEAR_BIT(TAMP->ATCR1, TAMP_ALL | TAMP_ATCR1_ATCKSEL | TAMP_ATCR1_ATPER | \
            TAMP_ATCR1_ATOSHARE | TAMP_ATCR1_FLTEN);

  return HAL_OK;
}


/**
  * @brief  Tamper event polling.
  * @param  hrtc RTC handle
  * @param  Tamper Selected tamper pin.
  *         This parameter can be a combination of the following values:
  *         @arg RTC_TAMPER_1
  *         @arg RTC_TAMPER_2
  *         @arg RTC_TAMPER_3
  *         @arg RTC_TAMPER_4
  *         @arg RTC_TAMPER_5
  *         @arg RTC_TAMPER_6
  *         @arg RTC_TAMPER_7
  *         @arg RTC_TAMPER_8
  * @param  Timeout Timeout duration
  * @retval HAL status
  */
HAL_StatusTypeDef HAL_RTCEx_PollForTamperEvent(RTC_HandleTypeDef *hrtc, uint32_t Tamper, uint32_t Timeout)
{
  UNUSED(hrtc);
  assert_param(IS_RTC_TAMPER(Tamper));

  uint32_t tickstart = HAL_GetTick();

  /* Get the status of the Interrupt */
  while (READ_BIT(TAMP->SR, Tamper) != Tamper)
  {
    if (Timeout != HAL_MAX_DELAY)
    {
      if (((HAL_GetTick() - tickstart) > Timeout) || (Timeout == 0U))
      {
        return HAL_TIMEOUT;
      }
    }
  }

  /* Clear the Tamper Flag */
  WRITE_REG(TAMP->SCR, Tamper);

  return HAL_OK;
}


/**
  * @brief  Set Internal Tamper in interrupt mode
  * @param  hrtc RTC handle
  * @param  sIntTamper Pointer to Internal Tamper Structure.
  * @retval HAL status
  */
HAL_StatusTypeDef HAL_RTCEx_SetInternalTamper(RTC_HandleTypeDef *hrtc, RTC_InternalTamperTypeDef *sIntTamper)
{
  /* Prevent unused argument(s) compilation warning */
  UNUSED(hrtc);

  /* Check the parameters */
  assert_param(IS_RTC_INTERNAL_TAMPER(sIntTamper->IntTamper));
  assert_param(IS_RTC_TAMPER_TIMESTAMPONTAMPER_DETECTION(sIntTamper->TimeStampOnTamperDetection));
  assert_param(IS_RTC_TAMPER_ERASE_MODE(sIntTamper->NoErase));

  /* timestamp on internal tamper */
  if (READ_BIT(RTC->CR, RTC_CR_TAMPTS) != sIntTamper->TimeStampOnTamperDetection)
  {
    __HAL_RTC_WRITEPROTECTION_DISABLE(hrtc);
    MODIFY_REG(RTC->CR, RTC_CR_TAMPTS, sIntTamper->TimeStampOnTamperDetection);
    __HAL_RTC_WRITEPROTECTION_ENABLE(hrtc);
  }

  /* Control register 1 */
  SET_BIT(TAMP->CR1, sIntTamper->IntTamper);

  return HAL_OK;
}


/**
  * @brief  Set Internal Tamper
  * @param  hrtc RTC handle
  * @param  sIntTamper Pointer to Internal Tamper Structure.
  * @retval HAL status
  */
HAL_StatusTypeDef HAL_RTCEx_SetInternalTamper_IT(RTC_HandleTypeDef *hrtc, RTC_InternalTamperTypeDef *sIntTamper)
{
  /* Prevent unused argument(s) compilation warning */
  UNUSED(hrtc);

  /* Check the parameters */
  assert_param(IS_RTC_INTERNAL_TAMPER(sIntTamper->IntTamper));
  assert_param(IS_RTC_TAMPER_TIMESTAMPONTAMPER_DETECTION(sIntTamper->TimeStampOnTamperDetection));
  assert_param(IS_RTC_TAMPER_ERASE_MODE(sIntTamper->NoErase));

  /* timestamp on internal tamper */
  if (READ_BIT(RTC->CR, RTC_CR_TAMPTS) != sIntTamper->TimeStampOnTamperDetection)
  {
    __HAL_RTC_WRITEPROTECTION_DISABLE(hrtc);
    MODIFY_REG(RTC->CR, RTC_CR_TAMPTS, sIntTamper->TimeStampOnTamperDetection);
    __HAL_RTC_WRITEPROTECTION_ENABLE(hrtc);
  }

  /* RTC Tamper Interrupt Configuration: EXTI configuration */
  __HAL_RTC_TAMPER_EXTI_ENABLE_IT();

  /* Interrupt enable register */
  SET_BIT(TAMP->IER, sIntTamper->IntTamper);

  /* Control register 1 */
  SET_BIT(TAMP->CR1, sIntTamper->IntTamper);

  return HAL_OK;
}

/**
  * @brief  Deactivate Internal Tamper.
  * @param  hrtc RTC handle
  * @param  IntTamper Selected internal tamper event.
  *          This parameter can be any combination of existing internal tampers.
  * @retval HAL status
  */
HAL_StatusTypeDef HAL_RTCEx_DeactivateInternalTamper(RTC_HandleTypeDef *hrtc, uint32_t IntTamper)
{
  UNUSED(hrtc);
  assert_param(IS_RTC_INTERNAL_TAMPER(IntTamper));

  /* Disable the selected Tamper pin */
  CLEAR_BIT(TAMP->CR1, IntTamper);

  /* Clear internal tamper interrupt mode configuration */
  CLEAR_BIT(TAMP->IER, IntTamper);

  /* Clear internal tamper interrupt */
  WRITE_REG(TAMP->SCR, IntTamper);

  return HAL_OK;
}


/**
  * @brief  Internal Tamper event polling.
  * @param  hrtc RTC handle
  * @param  IntTamper selected tamper.
  *          This parameter can be any combination of existing internal tampers.
  * @param  Timeout Timeout duration
  * @retval HAL status
  */
HAL_StatusTypeDef HAL_RTCEx_PollForInternalTamperEvent(RTC_HandleTypeDef *hrtc, uint32_t IntTamper, uint32_t Timeout)
{
  UNUSED(hrtc);
  assert_param(IS_RTC_INTERNAL_TAMPER(IntTamper));

  uint32_t tickstart = HAL_GetTick();

  /* Get the status of the Interrupt */
  while (READ_BIT(TAMP->SR, IntTamper) != IntTamper)
  {
    if (Timeout != HAL_MAX_DELAY)
    {
      if (((HAL_GetTick() - tickstart) > Timeout) || (Timeout == 0U))
      {
        return HAL_TIMEOUT;
      }
    }
  }

  /* Clear the Tamper Flag */
  WRITE_REG(TAMP->SCR, IntTamper);

  return HAL_OK;
}


#if defined (CORTEX_IN_SECURE_STATE)
/**
  * @brief  Handle Tamper secure interrupt request.
  * @param  hrtc RTC handle
  * @retval None
  */
void HAL_RTCEx_TamperIRQHandler(RTC_HandleTypeDef *hrtc)
{
  uint32_t tmp;

  /* Get secure interrupt status */
  tmp = READ_REG(TAMP->SMISR);

  /* Immediatly clear flags */
  WRITE_REG(TAMP->SCR, tmp);

  /* Check Tamper1 status */
  if ((tmp & RTC_TAMPER_1) == RTC_TAMPER_1)
  {
#if (USE_HAL_RTC_REGISTER_CALLBACKS == 1)
    /* Call Tamper 1 Event registered secure Callback */
    hrtc->Tamper1EventCallback(hrtc);
#else
    /* Tamper1 secure callback */
    HAL_RTCEx_Tamper1EventCallback(hrtc);
#endif
  }

  /* Check Tamper2 status */
  if ((tmp & RTC_TAMPER_2) == RTC_TAMPER_2)
  {
#if (USE_HAL_RTC_REGISTER_CALLBACKS == 1)
    /* Call Tamper 2 Event registered secure Callback */
    hrtc->Tamper2EventCallback(hrtc);
#else
    /* Tamper2 secure callback */
    HAL_RTCEx_Tamper2EventCallback(hrtc);
#endif
  }

  /* Check Tamper3 status */
  if ((tmp & RTC_TAMPER_3) == RTC_TAMPER_3)
  {
#if (USE_HAL_RTC_REGISTER_CALLBACKS == 1)
    /* Call Tamper 3 Event registered secure Callback */
    hrtc->Tamper3EventCallback(hrtc);
#else
    /* Tamper3 secure callback */
    HAL_RTCEx_Tamper3EventCallback(hrtc);
#endif
  }

  /* Check Internal Tamper1 status */
  if ((tmp & RTC_INT_TAMPER_1) == RTC_INT_TAMPER_1)
  {
#if (USE_HAL_RTC_REGISTER_CALLBACKS == 1)
    /* Call Internal Tamper 1 Event registered secure Callback */
    hrtc->InternalTamper1EventCallback(hrtc);
#else
    /* Internal Tamper1 secure callback */
    HAL_RTCEx_InternalTamper1EventCallback(hrtc);
#endif
  }

  /* Check Internal Tamper2 status */
  if ((tmp & RTC_INT_TAMPER_2) == RTC_INT_TAMPER_2)
  {
#if (USE_HAL_RTC_REGISTER_CALLBACKS == 1)
    /* Call Internal Tamper 2 Event registered secure Callback */
    hrtc->InternalTamper2EventCallback(hrtc);
#else
    /* Internal Tamper2 secure callback */
    HAL_RTCEx_InternalTamper2EventCallback(hrtc);
#endif
  }

  /* Check Internal Tamper3 status */
  if ((tmp & RTC_INT_TAMPER_3) == RTC_INT_TAMPER_3)
  {
#if (USE_HAL_RTC_REGISTER_CALLBACKS == 1)
    /* Call Internal Tamper 3 Event registered secure Callback */
    hrtc->InternalTamper3EventCallback(hrtc);
#else
    /* Internal Tamper3 secure callback */
    HAL_RTCEx_InternalTamper3EventCallback(hrtc);
#endif
  }

  /* Check Internal Tamper4 status */
  if ((tmp & RTC_INT_TAMPER_4) == RTC_INT_TAMPER_4)
  {
#if (USE_HAL_RTC_REGISTER_CALLBACKS == 1)
    /* Call Internal Tamper 4 Event registered Callback */
    hrtc->InternalTamper4EventCallback(hrtc);
#else
    /* Internal Tamper4 callback */
    HAL_RTCEx_InternalTamper4EventCallback(hrtc);
#endif
  }

  /* Check Internal Tamper5 status */
  if ((tmp & RTC_INT_TAMPER_5) == RTC_INT_TAMPER_5)
  {
#if (USE_HAL_RTC_REGISTER_CALLBACKS == 1)
    /* Call Internal Tamper 5 Event registered secure Callback */
    hrtc->InternalTamper5EventCallback(hrtc);
#else
    /* Internal Tamper5 secure callback */
    HAL_RTCEx_InternalTamper5EventCallback(hrtc);
#endif
  }

  /* Check Internal Tamper8 status */
  if ((tmp & RTC_INT_TAMPER_8) == RTC_INT_TAMPER_8)
  {
#if (USE_HAL_RTC_REGISTER_CALLBACKS == 1)
    /* Call Internal Tamper 8 Event registered secure Callback */
    hrtc->InternalTamper8EventCallback(hrtc);
#else
    /* Internal Tamper8 secure callback */
    HAL_RTCEx_InternalTamper8EventCallback(hrtc);
#endif
  }
}

#else /* #if defined (CORTEX_IN_SECURE_STATE) */

/**
  * @brief  Handle Tamper non-secure interrupt request.
  * @param  hrtc RTC handle
  * @retval None
  */
void HAL_RTCEx_TamperIRQHandler(RTC_HandleTypeDef *hrtc)
{
  /* Get interrupt status */
  uint32_t tmp = READ_REG(TAMP->MISR);

  /* Immediately clear flags */
  WRITE_REG(TAMP->SCR, tmp);

  /* Check Tamper1 status */
  if ((tmp & RTC_TAMPER_1) == RTC_TAMPER_1)
  {
#if (USE_HAL_RTC_REGISTER_CALLBACKS == 1)
    /* Call Tamper 1 Event registered Callback */
    hrtc->Tamper1EventCallback(hrtc);
#else
    /* Tamper1 callback */
    HAL_RTCEx_Tamper1EventCallback(hrtc);
#endif
  }

  /* Check Tamper2 status */
  if ((tmp & RTC_TAMPER_2) == RTC_TAMPER_2)
  {
#if (USE_HAL_RTC_REGISTER_CALLBACKS == 1)
    /* Call Tamper 2 Event registered Callback */
    hrtc->Tamper2EventCallback(hrtc);
#else
    /* Tamper2 callback */
    HAL_RTCEx_Tamper2EventCallback(hrtc);
#endif
  }

  /* Check Tamper3 status */
  if ((tmp & RTC_TAMPER_3) == RTC_TAMPER_3)
  {
#if (USE_HAL_RTC_REGISTER_CALLBACKS == 1)
    /* Call Tamper 3 Event registered Callback */
    hrtc->Tamper3EventCallback(hrtc);
#else
    /* Tamper3 callback */
    HAL_RTCEx_Tamper3EventCallback(hrtc);
#endif
  }

  /* Check Internal Tamper1 status */
  if ((tmp & RTC_INT_TAMPER_1) == RTC_INT_TAMPER_1)
  {
#if (USE_HAL_RTC_REGISTER_CALLBACKS == 1)
    /* Call Internal Tamper 1 Event registered Callback */
    hrtc->InternalTamper1EventCallback(hrtc);
#else
    /* Internal Tamper1 callback */
    HAL_RTCEx_InternalTamper1EventCallback(hrtc);
#endif
  }

  /* Check Internal Tamper2 status */
  if ((tmp & RTC_INT_TAMPER_2) == RTC_INT_TAMPER_2)
  {
#if (USE_HAL_RTC_REGISTER_CALLBACKS == 1)
    /* Call Internal Tamper 2 Event registered Callback */
    hrtc->InternalTamper2EventCallback(hrtc);
#else
    /* Internal Tamper2 callback */
    HAL_RTCEx_InternalTamper2EventCallback(hrtc);
#endif
  }

  /* Check Internal Tamper3 status */
  if ((tmp & RTC_INT_TAMPER_3) == RTC_INT_TAMPER_3)
  {
#if (USE_HAL_RTC_REGISTER_CALLBACKS == 1)
    /* Call Internal Tamper 3 Event registered Callback */
    hrtc->InternalTamper3EventCallback(hrtc);
#else
    /* Internal Tamper3 callback */
    HAL_RTCEx_InternalTamper3EventCallback(hrtc);
#endif
  }

  /* Check Internal Tamper4 status */
  if ((tmp & RTC_INT_TAMPER_4) == RTC_INT_TAMPER_4)
  {
#if (USE_HAL_RTC_REGISTER_CALLBACKS == 1)
    /* Call Internal Tamper 4 Event registered Callback */
    hrtc->InternalTamper4EventCallback(hrtc);
#else
    /* Internal Tamper4 callback */
    HAL_RTCEx_InternalTamper4EventCallback(hrtc);
#endif
  }

  /* Check Internal Tamper5 status */
  if ((tmp & RTC_INT_TAMPER_5) == RTC_INT_TAMPER_5)
  {
#if (USE_HAL_RTC_REGISTER_CALLBACKS == 1)
    /* Call Internal Tamper 5 Event registered Callback */
    hrtc->InternalTamper5EventCallback(hrtc);
#else
    /* Internal Tamper5 callback */
    HAL_RTCEx_InternalTamper5EventCallback(hrtc);
#endif
  }

  /* Check Internal Tamper8 status */
  if ((tmp & RTC_INT_TAMPER_8) == RTC_INT_TAMPER_8)
  {
#if (USE_HAL_RTC_REGISTER_CALLBACKS == 1)
    /* Call Internal Tamper 8 Event registered Callback */
    hrtc->InternalTamper8EventCallback(hrtc);
#else
    /* Internal Tamper8 callback */
    HAL_RTCEx_InternalTamper8EventCallback(hrtc);
#endif
  }
}
#endif /* #if defined (CORTEX_IN_SECURE_STATE) */

/**
  * @brief  Tamper 1 callback.
  * @param  hrtc RTC handle
  * @retval None
  */
__weak void HAL_RTCEx_Tamper1EventCallback(RTC_HandleTypeDef *hrtc)
{
  /* Prevent unused argument(s) compilation warning */
  UNUSED(hrtc);

  /* NOTE : This function should not be modified, when the callback is needed,
            the HAL_RTCEx_Tamper1EventCallback could be implemented in the user file
   */
}

/**
  * @brief  Tamper 2 callback.
  * @param  hrtc RTC handle
  * @retval None
  */
__weak void HAL_RTCEx_Tamper2EventCallback(RTC_HandleTypeDef *hrtc)
{
  /* Prevent unused argument(s) compilation warning */
  UNUSED(hrtc);

  /* NOTE : This function should not be modified, when the callback is needed,
            the HAL_RTCEx_Tamper2EventCallback could be implemented in the user file
   */
}

/**
  * @brief  Tamper 3 callback.
  * @param  hrtc RTC handle
  * @retval None
  */
__weak void HAL_RTCEx_Tamper3EventCallback(RTC_HandleTypeDef *hrtc)
{
  /* Prevent unused argument(s) compilation warning */
  UNUSED(hrtc);

  /* NOTE : This function should not be modified, when the callback is needed,
            the HAL_RTCEx_Tamper3EventCallback could be implemented in the user file
   */
}


/**
  * @brief  Internal Tamper 1 callback.
  * @param  hrtc RTC handle
  * @retval None
  */
__weak void HAL_RTCEx_InternalTamper1EventCallback(RTC_HandleTypeDef *hrtc)
{
  /* Prevent unused argument(s) compilation warning */
  UNUSED(hrtc);

  /* NOTE : This function should not be modified, when the callback is needed,
            the HAL_RTCEx_InternalTamper1EventCallback could be implemented in the user file
   */
}

/**
  * @brief  Internal Tamper 2 callback.
  * @param  hrtc RTC handle
  * @retval None
  */
__weak void HAL_RTCEx_InternalTamper2EventCallback(RTC_HandleTypeDef *hrtc)
{
  /* Prevent unused argument(s) compilation warning */
  UNUSED(hrtc);

  /* NOTE : This function should not be modified, when the callback is needed,
            the HAL_RTCEx_InternalTamper2EventCallback could be implemented in the user file
   */
}

/**
  * @brief  Internal Tamper 3 callback.
  * @param  hrtc RTC handle
  * @retval None
  */
__weak void HAL_RTCEx_InternalTamper3EventCallback(RTC_HandleTypeDef *hrtc)
{
  /* Prevent unused argument(s) compilation warning */
  UNUSED(hrtc);

  /* NOTE : This function should not be modified, when the callback is needed,
            the HAL_RTCEx_InternalTamper3EventCallback could be implemented in the user file
   */
}

/**
  * @brief  Internal Tamper 4 callback.
  * @param  hrtc RTC handle
  * @retval None
  */
__weak void HAL_RTCEx_InternalTamper4EventCallback(RTC_HandleTypeDef *hrtc)
{
  /* Prevent unused argument(s) compilation warning */
  UNUSED(hrtc);

  /* NOTE : This function should not be modified, when the callback is needed,
            the HAL_RTCEx_InternalTamper3EventCallback could be implemented in the user file
   */
}

/**
  * @brief  Internal Tamper 5 callback.
  * @param  hrtc RTC handle
  * @retval None
  */
__weak void HAL_RTCEx_InternalTamper5EventCallback(RTC_HandleTypeDef *hrtc)
{
  /* Prevent unused argument(s) compilation warning */
  UNUSED(hrtc);

  /* NOTE : This function should not be modified, when the callback is needed,
            the HAL_RTCEx_InternalTamper5EventCallback could be implemented in the user file
   */
}


/**
  * @brief  Internal Tamper 8 callback.
  * @param  hrtc RTC handle
  * @retval None
  */
__weak void HAL_RTCEx_InternalTamper8EventCallback(RTC_HandleTypeDef *hrtc)
{
  /* Prevent unused argument(s) compilation warning */
  UNUSED(hrtc);

  /* NOTE : This function should not be modified, when the callback is needed,
            the HAL_RTCEx_InternalTamper8EventCallback could be implemented in the user file
   */
}
/**
  * @}
  */


/** @addtogroup RTCEx_Exported_Functions_Group6
  * @brief      Extended RTC Backup register functions
  *
@verbatim
  ===============================================================================
             ##### Extended RTC Backup register functions #####
  ===============================================================================
  [..]
   (+) Before calling any tamper or internal tamper function, you have to call first
       HAL_RTC_Init() function.
   (+) In that ine you can select to output tamper event on RTC pin.
  [..]
   This subsection provides functions allowing to
   (+) Write a data in a specified RTC Backup data register
   (+) Read a data in a specified RTC Backup data register
@endverbatim
  * @{
  */


/**
  * @brief  Write a data in a specified RTC Backup data register.
  * @param  hrtc RTC handle
  * @param  BackupRegister RTC Backup data Register number.
  *          This parameter can be RTC_BKP_DRx where x can be from 0 to RTC_BACKUP_NB
  * @param  Data Data to be written in the specified Backup data register.
  * @retval None
  */
void HAL_RTCEx_BKUPWrite(RTC_HandleTypeDef *hrtc, uint32_t BackupRegister, uint32_t Data)
{
  uint32_t tmp;

  UNUSED(hrtc);
  /* Check the parameters */
  assert_param(IS_RTC_BKP(BackupRegister));

  tmp = (uint32_t) & (TAMP->BKP0R);
  tmp += (BackupRegister * 4U);

  /* Write the specified register */
  *(__IO uint32_t *)tmp = (uint32_t)Data;
}


/**
  * @brief  Reads data from the specified RTC Backup data Register.
  * @param  hrtc RTC handle
  * @param  BackupRegister RTC Backup data Register number.
  *          This parameter can be RTC_BKP_DRx where x can be from 0 to RTC_BACKUP_NB
  * @retval Read value
  */
uint32_t HAL_RTCEx_BKUPRead(RTC_HandleTypeDef *hrtc, uint32_t BackupRegister)
{
  uint32_t tmp;

  UNUSED(hrtc);
  /* Check the parameters */
  assert_param(IS_RTC_BKP(BackupRegister));

  tmp = (uint32_t) & (TAMP->BKP0R);
  tmp += (BackupRegister * 4U);

  /* Read the specified register */
  return (*(__IO uint32_t *)tmp);
}

/**
  * @}
  */


/** @addtogroup RTCEx_Exported_Functions_Group7
  * @brief      Extended RTC security functions
  *
@verbatim
  ===============================================================================
             ##### Extended RTC security functions #####
  ===============================================================================
  [..]
   (+) Before calling security function, you have to call first
       HAL_RTC_Init() function.
@endverbatim
  * @{
  */

/**
  * @brief  Get the security level of the RTC.
  *         To set the secure level please call HAL_RTCEx_SecureModeSet.
  * @param  hrtc RTC handle
  * @param  secureState  Secure state
  * @retval HAL_StatusTypeDef
  */
HAL_StatusTypeDef HAL_RTCEx_SecureModeGet(RTC_HandleTypeDef *hrtc, RTC_SecureStateTypeDef  *secureState)
{
  UNUSED(hrtc);
  /* Read registers */
  uint32_t rtc_smcr = READ_REG(RTC->SMCR);
  uint32_t tamp_smcr = READ_REG(TAMP->SMCR);

  /* RTC */
  secureState->rtcSecureFull = READ_BIT(rtc_smcr, RTC_SMCR_DECPROT);

  /* Warning, rtcNonSecureFeatures is only relevant if secureState->rtcSecureFull == RTC_SECURE_FULL_NO */
  secureState->rtcNonSecureFeatures = READ_BIT(rtc_smcr, RTC_NONSECURE_FEATURE_ALL);

  /* TAMP */
  secureState->tampSecureFull = READ_BIT(tamp_smcr, TAMP_SMCR_TAMPDPROT);

  /* Backup register start zones
     Warning : Backup register start zones are shared with privilege configuration */
  secureState->backupRegisterStartZone2 = READ_BIT(tamp_smcr, TAMP_SMCR_BKPRWDPROT) >> TAMP_SMCR_BKPRWDPROT_Pos;
  secureState->backupRegisterStartZone3 = READ_BIT(tamp_smcr, TAMP_SMCR_BKPWDPROT) >> TAMP_SMCR_BKPWDPROT_Pos;

  return HAL_OK;
}


#if defined (CORTEX_IN_SECURE_STATE)
/**
  * @brief  Set the security level of the RTC/TAMP/Backup registers.
  *         To get the current security level call HAL_RTCEx_SecureModeGet.
  * @param  hrtc RTC handle
  * @param  secureState  Secure state
  * @retval HAL_StatusTypeDef
  */
HAL_StatusTypeDef HAL_RTCEx_SecureModeSet(RTC_HandleTypeDef *hrtc, RTC_SecureStateTypeDef  *secureState)
{
  UNUSED(hrtc);
  assert_param(IS_RTC_SECURE_FULL(secureState->rtcSecureFull));
  assert_param(IS_RTC_NONSECURE_FEATURES(secureState->rtcNonSecureFeatures));
  assert_param(IS_TAMP_SECURE_FULL(secureState->tampSecureFull));
  assert_param(IS_RTC_BKP(secureState->backupRegisterStartZone2));
  assert_param(IS_RTC_BKP(secureState->backupRegisterStartZone3));

  /* RTC, rtcNonSecureFeatures is only relevant if secureState->rtcSecureFull == RTC_SECURE_FULL_NO */
  WRITE_REG(RTC->SMCR, secureState->rtcSecureFull | secureState->rtcNonSecureFeatures);

  /* Tamper + Backup register
     Warning : Backup register start zone are Shared with privilege configuration */
  WRITE_REG(TAMP->SMCR,
            secureState->tampSecureFull |
            (TAMP_SMCR_BKPRWDPROT & (secureState->backupRegisterStartZone2 << TAMP_SMCR_BKPRWDPROT_Pos)) |
            (TAMP_SMCR_BKPWDPROT & (secureState->backupRegisterStartZone3 << TAMP_SMCR_BKPWDPROT_Pos)));

  return HAL_OK;
}
#endif /* #if defined (CORTEX_IN_SECURE_STATE) */

/**
  * @}
  */

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

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
