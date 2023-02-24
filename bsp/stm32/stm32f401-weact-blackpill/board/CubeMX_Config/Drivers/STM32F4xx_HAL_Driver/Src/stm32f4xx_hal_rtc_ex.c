/**
  ******************************************************************************
  * @file    stm32f4xx_hal_rtc_ex.c
  * @author  MCD Application Team
  * @brief   Extended RTC HAL module driver.
  *          This file provides firmware functions to manage the following
  *          functionalities of the Real-Time Clock (RTC) Extended peripheral:
  *           + RTC Timestamp functions
  *           + RTC Tamper functions
  *           + RTC Wakeup functions
  *           + Extended Control functions
  *           + Extended RTC features functions
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
    (+) Enable the RTC domain access.
    (+) Configure the RTC Prescaler (Asynchronous and Synchronous) and RTC hour
        format using the HAL_RTC_Init() function.

  *** RTC Wakeup configuration ***
  ================================
  [..]
    (+) To configure the RTC Wakeup Clock source and Counter use the
        HAL_RTCEx_SetWakeUpTimer() function.
        You can also configure the RTC Wakeup timer in interrupt mode using the
        HAL_RTCEx_SetWakeUpTimer_IT() function.
    (+) To read the RTC Wakeup Counter register, use the HAL_RTCEx_GetWakeUpTimer()
        function.

  *** Timestamp configuration ***
  ===============================
  [..]
    (+) To configure the RTC Timestamp use the HAL_RTCEx_SetTimeStamp() function.
        You can also configure the RTC Timestamp with interrupt mode using the
        HAL_RTCEx_SetTimeStamp_IT() function.
    (+) To read the RTC Timestamp Time and Date register, use the
        HAL_RTCEx_GetTimeStamp() function.
    (+) The Timestamp alternate function can be mapped either to RTC_AF1 (PC13)
        or RTC_AF2 (PI8) depending on the value of TSINSEL bit in RTC_TAFCR
        register.
        For STM32F446xx devices RTC_AF2 corresponds to pin PA0 and not to pin PI8.
        The corresponding pin is also selected by HAL_RTCEx_SetTimeStamp()
        or HAL_RTCEx_SetTimeStamp_IT() functions.

  *** Tamper configuration ***
  ============================
  [..]
    (+) To Enable the RTC Tamper and configure the Tamper filter count, trigger
        Edge or Level according to the Tamper filter value (if equal to 0 Edge
        else Level), sampling frequency, precharge or discharge and Pull-UP use
        the HAL_RTCEx_SetTamper() function.
        You can configure RTC Tamper in interrupt mode using HAL_RTCEx_SetTamper_IT()
        function.
    (+) The TAMPER1 alternate function can be mapped either to RTC_AF1 (PC13)
        or RTC_AF2 (PI8) depending on the value of TAMP1INSEL bit in RTC_TAFCR
        register.
        The corresponding pin is also selected by HAL_RTCEx_SetTamper()
        or HAL_RTCEx_SetTamper_IT() functions.
    (+) The TAMPER2 alternate function is mapped to RTC_AF2 (PI8).
        For STM32F446xx devices RTC_AF2 corresponds to pin PA0 and not to pin PI8.

  *** Backup Data Registers configuration ***
  ===========================================
  [..]
    (+) To write to the RTC Backup Data registers, use the HAL_RTCEx_BKUPWrite()
        function.
    (+) To read the RTC Backup Data registers, use the HAL_RTCEx_BKUPRead()
        function.

  *** Coarse Digital Calibration configuration ***
  ================================================
  [..]
    (+) The Coarse Digital Calibration can be used to compensate crystal inaccuracy
        by setting the DCS bit in RTC_CALIBR register.
    (+) When positive calibration is enabled (DCS = ‘0’), 2 asynchronous prescaler
        clock cycles are added every minute during 2xDC minutes.
        This causes the calendar to be updated sooner, thereby adjusting the
        effective RTC frequency to be a bit higher.
    (+) When negative calibration is enabled (DCS = ‘1’), 1 asynchronous prescaler
        clock cycle is removed every minute during 2xDC minutes.
        This causes the calendar to be updated later, thereby adjusting the
        effective RTC frequency to be a bit lower.
    (+) DC is configured through bits DC[4:0] of RTC_CALIBR register. This number
        ranges from 0 to 31 corresponding to a time interval (2xDC) ranging from
        0 to 62.
    (+) In order to measure the clock deviation, a 512 Hz clock is output for
        calibration.
    (+) The RTC Coarse Digital Calibration value and sign can be calibrated using
        the HAL_RTCEx_SetCoarseCalib() function.

  *** Smooth Digital Calibration configuration ***
  ================================================
  [..]
    (+) RTC frequency can be digitally calibrated with a resolution of about
        0.954 ppm with a range from -487.1 ppm to +488.5 ppm.
        The correction of the frequency is performed using a series of small
        adjustments (adding and/or subtracting individual RTCCLK pulses).
    (+) The smooth digital calibration is performed during a cycle of about 2^20
        RTCCLK pulses (or 32 seconds) when the input frequency is 32,768 Hz.
        This cycle is maintained by a 20-bit counter clocked by RTCCLK.
    (+) The smooth calibration register (RTC_CALR) specifies the number of RTCCLK
        clock cycles to be masked during the 32-second cycle.
    (+) The RTC Smooth Digital Calibration value and the corresponding calibration
        cycle period (32s, 16s, or 8s) can be calibrated using the
        HAL_RTCEx_SetSmoothCalib() function.

  @endverbatim
  ******************************************************************************
  */

/* Includes ------------------------------------------------------------------*/
#include "stm32f4xx_hal.h"

/** @addtogroup STM32F4xx_HAL_Driver
  * @{
  */

/** @defgroup RTCEx RTCEx
  * @brief    RTC Extended HAL module driver
  * @{
  */

#ifdef HAL_RTC_MODULE_ENABLED

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
/* Exported functions --------------------------------------------------------*/

/** @defgroup RTCEx_Exported_Functions RTCEx Exported Functions
  * @{
  */

/** @defgroup RTCEx_Exported_Functions_Group1 RTC Timestamp and Tamper functions
  * @brief    RTC Timestamp and Tamper functions
  *
@verbatim
 ===============================================================================
                 ##### RTC Timestamp and Tamper functions #####
 ===============================================================================

 [..] This section provides functions allowing to configure Timestamp feature

@endverbatim
  * @{
  */

/**
  * @brief  Sets Timestamp.
  * @note   This API must be called before enabling the Timestamp feature.
  * @param  hrtc pointer to a RTC_HandleTypeDef structure that contains
  *                the configuration information for RTC.
  * @param  RTC_TimeStampEdge Specifies the pin edge on which the Timestamp is
  *         activated.
  *          This parameter can be one of the following values:
  *             @arg RTC_TIMESTAMPEDGE_RISING: the Timestamp event occurs on
  *                                        the rising edge of the related pin.
  *             @arg RTC_TIMESTAMPEDGE_FALLING: the Timestamp event occurs on
  *                                        the falling edge of the related pin.
  * @param  RTC_TimeStampPin Specifies the RTC Timestamp Pin.
  *          This parameter can be one of the following values:
  *             @arg RTC_TIMESTAMPPIN_DEFAULT: PC13 is selected as RTC Timestamp Pin.
  *             @arg RTC_TIMESTAMPPIN_POS1: PI8 is selected as RTC Timestamp Pin.
  * @note RTC_TIMESTAMPPIN_POS1 corresponds to pin PA0 in the case of
  *       STM32F446xx devices.
  * @note RTC_TIMESTAMPPIN_POS1 is not applicable to the following list of devices:
  *       STM32F412xx, STM32F413xx and STM32F423xx.
  * @retval HAL status
  */
HAL_StatusTypeDef HAL_RTCEx_SetTimeStamp(RTC_HandleTypeDef *hrtc, uint32_t RTC_TimeStampEdge, uint32_t RTC_TimeStampPin)
{
  uint32_t tmpreg = 0U;

  /* Check the parameters */
  assert_param(IS_TIMESTAMP_EDGE(RTC_TimeStampEdge));
  assert_param(IS_RTC_TIMESTAMP_PIN(RTC_TimeStampPin));

  /* Process Locked */
  __HAL_LOCK(hrtc);

  /* Change RTC state to BUSY */
  hrtc->State = HAL_RTC_STATE_BUSY;

  hrtc->Instance->TAFCR &= (uint32_t)~RTC_TAFCR_TSINSEL;
  hrtc->Instance->TAFCR |= (uint32_t)(RTC_TimeStampPin);

  /* Get the RTC_CR register and clear the bits to be configured */
  tmpreg = (uint32_t)(hrtc->Instance->CR & (uint32_t)~(RTC_CR_TSEDGE | RTC_CR_TSE));

  /* Configure the Timestamp TSEDGE bit */
  tmpreg |= RTC_TimeStampEdge;

  /* Disable the write protection for RTC registers */
  __HAL_RTC_WRITEPROTECTION_DISABLE(hrtc);

  /* Copy the desired configuration into the CR register */
  hrtc->Instance->CR = (uint32_t)tmpreg;

  /* Clear RTC Timestamp flag */
  __HAL_RTC_TIMESTAMP_CLEAR_FLAG(hrtc, RTC_FLAG_TSF);

  /* Clear RTC Timestamp overrun Flag */
  __HAL_RTC_TIMESTAMP_CLEAR_FLAG(hrtc, RTC_FLAG_TSOVF);

  /* Enable the Timestamp saving */
  __HAL_RTC_TIMESTAMP_ENABLE(hrtc);

  /* Enable the write protection for RTC registers */
  __HAL_RTC_WRITEPROTECTION_ENABLE(hrtc);

  /* Change RTC state back to READY */
  hrtc->State = HAL_RTC_STATE_READY;

  /* Process Unlocked */
  __HAL_UNLOCK(hrtc);

  return HAL_OK;
}

/**
  * @brief  Sets Timestamp with Interrupt.
  * @param  hrtc pointer to a RTC_HandleTypeDef structure that contains
  *                the configuration information for RTC.
  * @note   This API must be called before enabling the Timestamp feature.
  * @param  RTC_TimeStampEdge Specifies the pin edge on which the Timestamp is
  *         activated.
  *          This parameter can be one of the following values:
  *             @arg RTC_TIMESTAMPEDGE_RISING: the Timestamp event occurs on
  *                                        the rising edge of the related pin.
  *             @arg RTC_TIMESTAMPEDGE_FALLING: the Timestamp event occurs on
  *                                        the falling edge of the related pin.
  * @param  RTC_TimeStampPin Specifies the RTC Timestamp Pin.
  *          This parameter can be one of the following values:
  *             @arg RTC_TIMESTAMPPIN_DEFAULT: PC13 is selected as RTC Timestamp Pin.
  *             @arg RTC_TIMESTAMPPIN_POS1: PI8 is selected as RTC Timestamp Pin.
  * @note RTC_TIMESTAMPPIN_POS1 corresponds to pin PA0 in the case of
  *       STM32F446xx devices.
  * @note RTC_TIMESTAMPPIN_POS1 is not applicable to the following list of devices:
  *       STM32F412xx, STM32F413xx and STM32F423xx.
  * @retval HAL status
  */
HAL_StatusTypeDef HAL_RTCEx_SetTimeStamp_IT(RTC_HandleTypeDef *hrtc, uint32_t RTC_TimeStampEdge, uint32_t RTC_TimeStampPin)
{
  uint32_t tmpreg = 0U;

  /* Check the parameters */
  assert_param(IS_TIMESTAMP_EDGE(RTC_TimeStampEdge));
  assert_param(IS_RTC_TIMESTAMP_PIN(RTC_TimeStampPin));

  /* Process Locked */
  __HAL_LOCK(hrtc);

  /* Change RTC state to BUSY */
  hrtc->State = HAL_RTC_STATE_BUSY;

  hrtc->Instance->TAFCR &= (uint32_t)~RTC_TAFCR_TSINSEL;
  hrtc->Instance->TAFCR |= (uint32_t)(RTC_TimeStampPin);

  /* Get the RTC_CR register and clear the bits to be configured */
  tmpreg = (uint32_t)(hrtc->Instance->CR & (uint32_t)~(RTC_CR_TSEDGE | RTC_CR_TSE));

  /* Configure the Timestamp TSEDGE bit */
  tmpreg |= RTC_TimeStampEdge;

  /* Disable the write protection for RTC registers */
  __HAL_RTC_WRITEPROTECTION_DISABLE(hrtc);

  /* Copy the desired configuration into the CR register */
  hrtc->Instance->CR = (uint32_t)tmpreg;

  /* Clear RTC Timestamp flag */
  __HAL_RTC_TIMESTAMP_CLEAR_FLAG(hrtc, RTC_FLAG_TSF);

  /* Clear RTC Timestamp overrun Flag */
  __HAL_RTC_TIMESTAMP_CLEAR_FLAG(hrtc, RTC_FLAG_TSOVF);

  /* Enable the Timestamp saving */
  __HAL_RTC_TIMESTAMP_ENABLE(hrtc);

  /* Enable IT Timestamp */
  __HAL_RTC_TIMESTAMP_ENABLE_IT(hrtc, RTC_IT_TS);

  /* Enable the write protection for RTC registers */
  __HAL_RTC_WRITEPROTECTION_ENABLE(hrtc);

  /* RTC Timestamp Interrupt Configuration: EXTI configuration */
  __HAL_RTC_TAMPER_TIMESTAMP_EXTI_ENABLE_IT();
  __HAL_RTC_TAMPER_TIMESTAMP_EXTI_ENABLE_RISING_EDGE();

  /* Change RTC state back to READY */
  hrtc->State = HAL_RTC_STATE_READY;

  /* Process Unlocked */
  __HAL_UNLOCK(hrtc);

  return HAL_OK;
}

/**
  * @brief  Deactivates Timestamp.
  * @param  hrtc pointer to a RTC_HandleTypeDef structure that contains
  *                the configuration information for RTC.
  * @retval HAL status
  */
HAL_StatusTypeDef HAL_RTCEx_DeactivateTimeStamp(RTC_HandleTypeDef *hrtc)
{
  uint32_t tmpreg = 0U;

  /* Process Locked */
  __HAL_LOCK(hrtc);

  hrtc->State = HAL_RTC_STATE_BUSY;

  /* Disable the write protection for RTC registers */
  __HAL_RTC_WRITEPROTECTION_DISABLE(hrtc);

  /* In case of interrupt mode is used, the interrupt source must disabled */
  __HAL_RTC_TIMESTAMP_DISABLE_IT(hrtc, RTC_IT_TS);

  /* Get the RTC_CR register and clear the bits to be configured */
  tmpreg = (uint32_t)(hrtc->Instance->CR & (uint32_t)~(RTC_CR_TSEDGE | RTC_CR_TSE));

  /* Configure the Timestamp TSEDGE and Enable bits */
  hrtc->Instance->CR = (uint32_t)tmpreg;

  /* Enable the write protection for RTC registers */
  __HAL_RTC_WRITEPROTECTION_ENABLE(hrtc);

  hrtc->State = HAL_RTC_STATE_READY;

  /* Process Unlocked */
  __HAL_UNLOCK(hrtc);

  return HAL_OK;
}

/**
  * @brief  Gets the RTC Timestamp value.
  * @param  hrtc pointer to a RTC_HandleTypeDef structure that contains
  *                the configuration information for RTC.
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
  uint32_t tmptime = 0U;
  uint32_t tmpdate = 0U;

  /* Check the parameters */
  assert_param(IS_RTC_FORMAT(Format));

  /* Get the Timestamp time and date registers values */
  tmptime = (uint32_t)(hrtc->Instance->TSTR & RTC_TR_RESERVED_MASK);
  tmpdate = (uint32_t)(hrtc->Instance->TSDR & RTC_DR_RESERVED_MASK);

  /* Fill the Time structure fields with the read parameters */
  sTimeStamp->Hours      = (uint8_t)((tmptime & (RTC_TSTR_HT  | RTC_TSTR_HU))  >> RTC_TSTR_HU_Pos);
  sTimeStamp->Minutes    = (uint8_t)((tmptime & (RTC_TSTR_MNT | RTC_TSTR_MNU)) >> RTC_TSTR_MNU_Pos);
  sTimeStamp->Seconds    = (uint8_t)((tmptime & (RTC_TSTR_ST  | RTC_TSTR_SU))  >> RTC_TSTR_SU_Pos);
  sTimeStamp->TimeFormat = (uint8_t)((tmptime & (RTC_TSTR_PM))                 >> RTC_TSTR_PM_Pos);
  sTimeStamp->SubSeconds = (uint32_t) hrtc->Instance->TSSSR;

  /* Fill the Date structure fields with the read parameters */
  sTimeStampDate->Year    = 0U;
  sTimeStampDate->Month   = (uint8_t)((tmpdate & (RTC_TSDR_MT | RTC_TSDR_MU)) >> RTC_TSDR_MU_Pos);
  sTimeStampDate->Date    = (uint8_t)((tmpdate & (RTC_TSDR_DT | RTC_TSDR_DU)) >> RTC_TSDR_DU_Pos);
  sTimeStampDate->WeekDay = (uint8_t)((tmpdate & (RTC_TSDR_WDU))              >> RTC_TSDR_WDU_Pos);

  /* Check the input parameters format */
  if (Format == RTC_FORMAT_BIN)
  {
    /* Convert the Timestamp structure parameters to Binary format */
    sTimeStamp->Hours   = (uint8_t)RTC_Bcd2ToByte(sTimeStamp->Hours);
    sTimeStamp->Minutes = (uint8_t)RTC_Bcd2ToByte(sTimeStamp->Minutes);
    sTimeStamp->Seconds = (uint8_t)RTC_Bcd2ToByte(sTimeStamp->Seconds);

    /* Convert the DateTimeStamp structure parameters to Binary format */
    sTimeStampDate->Month   = (uint8_t)RTC_Bcd2ToByte(sTimeStampDate->Month);
    sTimeStampDate->Date    = (uint8_t)RTC_Bcd2ToByte(sTimeStampDate->Date);
    sTimeStampDate->WeekDay = (uint8_t)RTC_Bcd2ToByte(sTimeStampDate->WeekDay);
  }

  /* Clear the Timestamp Flag */
  __HAL_RTC_TIMESTAMP_CLEAR_FLAG(hrtc, RTC_FLAG_TSF);

  return HAL_OK;
}

/**
  * @brief  Sets Tamper.
  * @note   By calling this API the tamper global interrupt will be disabled.
  * @param  hrtc pointer to a RTC_HandleTypeDef structure that contains
  *                the configuration information for RTC.
  * @param  sTamper Pointer to Tamper Structure.
  * @retval HAL status
  */
HAL_StatusTypeDef HAL_RTCEx_SetTamper(RTC_HandleTypeDef *hrtc, RTC_TamperTypeDef *sTamper)
{
  uint32_t tmpreg = 0U;

  /* Check the parameters */
  assert_param(IS_RTC_TAMPER(sTamper->Tamper));
  assert_param(IS_RTC_TAMPER_PIN(sTamper->PinSelection));
  assert_param(IS_RTC_TAMPER_TRIGGER(sTamper->Trigger));
  assert_param(IS_RTC_TAMPER_FILTER(sTamper->Filter));
  assert_param(IS_RTC_TAMPER_FILTER_CONFIG_CORRECT(sTamper->Filter, sTamper->Trigger));
  assert_param(IS_RTC_TAMPER_SAMPLING_FREQ(sTamper->SamplingFrequency));
  assert_param(IS_RTC_TAMPER_PRECHARGE_DURATION(sTamper->PrechargeDuration));
  assert_param(IS_RTC_TAMPER_PULLUP_STATE(sTamper->TamperPullUp));
  assert_param(IS_RTC_TAMPER_TIMESTAMPONTAMPER_DETECTION(sTamper->TimeStampOnTamperDetection));

  /* Process Locked */
  __HAL_LOCK(hrtc);

  hrtc->State = HAL_RTC_STATE_BUSY;

  /* Copy control register into temporary variable */
  tmpreg = hrtc->Instance->TAFCR;

  /* Enable selected tamper */
  tmpreg |= (sTamper->Tamper);

  /* Configure the tamper trigger bit (this bit is just on the right of the
       tamper enable bit, hence the one-time right shift before updating it) */
  if (sTamper->Trigger == RTC_TAMPERTRIGGER_FALLINGEDGE)
  {
    /* Set the tamper trigger bit (case of falling edge or high level) */
    tmpreg |= (uint32_t)(sTamper->Tamper << 1U);
  }
  else
  {
    /* Clear the tamper trigger bit (case of rising edge or low level) */
    tmpreg &= (uint32_t)~(sTamper->Tamper << 1U);
  }

  /* Clear remaining fields before setting them */
  tmpreg &= ~(RTC_TAMPERFILTER_MASK              | \
              RTC_TAMPERSAMPLINGFREQ_RTCCLK_MASK | \
              RTC_TAMPERPRECHARGEDURATION_MASK   | \
              RTC_TAMPER_PULLUP_MASK             | \
              RTC_TAFCR_TAMP1INSEL               | \
              RTC_TIMESTAMPONTAMPERDETECTION_MASK);

  /* Set remaining parameters of desired configuration into temporary variable */
  tmpreg |= ((uint32_t)sTamper->Filter            | \
             (uint32_t)sTamper->SamplingFrequency | \
             (uint32_t)sTamper->PrechargeDuration | \
             (uint32_t)sTamper->TamperPullUp      | \
             (uint32_t)sTamper->PinSelection      | \
             (uint32_t)sTamper->TimeStampOnTamperDetection);

  /* Disable tamper global interrupt in case it is enabled */
  tmpreg &= (uint32_t)~RTC_TAFCR_TAMPIE;

  /* Copy desired configuration into configuration register */
  hrtc->Instance->TAFCR = tmpreg;

  hrtc->State = HAL_RTC_STATE_READY;

  /* Process Unlocked */
  __HAL_UNLOCK(hrtc);

  return HAL_OK;
}

/**
  * @brief  Sets Tamper with interrupt.
  * @note   By calling this API the tamper global interrupt will be enabled.
  * @param  hrtc pointer to a RTC_HandleTypeDef structure that contains
  *                the configuration information for RTC.
  * @param  sTamper Pointer to RTC Tamper.
  * @retval HAL status
  */
HAL_StatusTypeDef HAL_RTCEx_SetTamper_IT(RTC_HandleTypeDef *hrtc, RTC_TamperTypeDef *sTamper)
{
  uint32_t tmpreg = 0U;

  /* Check the parameters */
  assert_param(IS_RTC_TAMPER(sTamper->Tamper));
  assert_param(IS_RTC_TAMPER_PIN(sTamper->PinSelection));
  assert_param(IS_RTC_TAMPER_TRIGGER(sTamper->Trigger));
  assert_param(IS_RTC_TAMPER_FILTER(sTamper->Filter));
  assert_param(IS_RTC_TAMPER_FILTER_CONFIG_CORRECT(sTamper->Filter, sTamper->Trigger));
  assert_param(IS_RTC_TAMPER_SAMPLING_FREQ(sTamper->SamplingFrequency));
  assert_param(IS_RTC_TAMPER_PRECHARGE_DURATION(sTamper->PrechargeDuration));
  assert_param(IS_RTC_TAMPER_PULLUP_STATE(sTamper->TamperPullUp));
  assert_param(IS_RTC_TAMPER_TIMESTAMPONTAMPER_DETECTION(sTamper->TimeStampOnTamperDetection));

  /* Process Locked */
  __HAL_LOCK(hrtc);

  hrtc->State = HAL_RTC_STATE_BUSY;

  /* Copy control register into temporary variable */
  tmpreg = hrtc->Instance->TAFCR;

  /* Enable selected tamper */
  tmpreg |= (sTamper->Tamper);

  /* Configure the tamper trigger bit (this bit is just on the right of the
       tamper enable bit, hence the one-time right shift before updating it) */
  if (sTamper->Trigger == RTC_TAMPERTRIGGER_FALLINGEDGE)
  {
    /* Set the tamper trigger bit (case of falling edge or high level) */
    tmpreg |= (uint32_t)(sTamper->Tamper << 1U);
  }
  else
  {
    /* Clear the tamper trigger bit (case of rising edge or low level) */
    tmpreg &= (uint32_t)~(sTamper->Tamper << 1U);
  }

  /* Clear remaining fields before setting them */
  tmpreg &= ~(RTC_TAMPERFILTER_MASK              | \
              RTC_TAMPERSAMPLINGFREQ_RTCCLK_MASK | \
              RTC_TAMPERPRECHARGEDURATION_MASK   | \
              RTC_TAMPER_PULLUP_MASK             | \
              RTC_TAFCR_TAMP1INSEL               | \
              RTC_TIMESTAMPONTAMPERDETECTION_MASK);

  /* Set remaining parameters of desired configuration into temporary variable */
  tmpreg |= ((uint32_t)sTamper->Filter            | \
             (uint32_t)sTamper->SamplingFrequency | \
             (uint32_t)sTamper->PrechargeDuration | \
             (uint32_t)sTamper->TamperPullUp      | \
             (uint32_t)sTamper->PinSelection      | \
             (uint32_t)sTamper->TimeStampOnTamperDetection);

  /* Enable global tamper interrupt */
  tmpreg |= (uint32_t)RTC_TAFCR_TAMPIE;

  /* Copy desired configuration into configuration register */
  hrtc->Instance->TAFCR = tmpreg;

  /* RTC Tamper Interrupt Configuration: EXTI configuration */
  __HAL_RTC_TAMPER_TIMESTAMP_EXTI_ENABLE_IT();
  __HAL_RTC_TAMPER_TIMESTAMP_EXTI_ENABLE_RISING_EDGE();

  hrtc->State = HAL_RTC_STATE_READY;

  /* Process Unlocked */
  __HAL_UNLOCK(hrtc);

  return HAL_OK;
}

/**
  * @brief  Deactivates Tamper.
  * @note   The tamper global interrupt bit will remain unchanged.
  * @param  hrtc pointer to a RTC_HandleTypeDef structure that contains
  *                the configuration information for RTC.
  * @param  Tamper Selected tamper pin.
  *          This parameter can be any combination of the following values:
  *            @arg RTC_TAMPER_1:  Tamper 1
  *            @arg RTC_TAMPER_2:  Tamper 2
  * @note   RTC_TAMPER_2 is not applicable to all devices.
  * @retval HAL status
  */
HAL_StatusTypeDef HAL_RTCEx_DeactivateTamper(RTC_HandleTypeDef *hrtc, uint32_t Tamper)
{
  assert_param(IS_RTC_TAMPER(Tamper));

  /* Process Locked */
  __HAL_LOCK(hrtc);

  hrtc->State = HAL_RTC_STATE_BUSY;

  /* Disable the selected Tamper pin */
  hrtc->Instance->TAFCR &= (uint32_t)~Tamper;

  hrtc->State = HAL_RTC_STATE_READY;

  /* Process Unlocked */
  __HAL_UNLOCK(hrtc);

  return HAL_OK;
}

/**
  * @brief  Handles Timestamp and Tamper interrupt request.
  * @param  hrtc pointer to a RTC_HandleTypeDef structure that contains
  *                the configuration information for RTC.
  * @retval None
  */
void HAL_RTCEx_TamperTimeStampIRQHandler(RTC_HandleTypeDef *hrtc)
{
  /* Get the Timestamp interrupt source enable status */
  if (__HAL_RTC_TIMESTAMP_GET_IT_SOURCE(hrtc, RTC_IT_TS) != 0U)
  {
    /* Get the pending status of the Timestamp Interrupt */
    if (__HAL_RTC_TIMESTAMP_GET_FLAG(hrtc, RTC_FLAG_TSF) != 0U)
    {
      /* Timestamp callback */
#if (USE_HAL_RTC_REGISTER_CALLBACKS == 1)
      hrtc->TimeStampEventCallback(hrtc);
#else
      HAL_RTCEx_TimeStampEventCallback(hrtc);
#endif /* USE_HAL_RTC_REGISTER_CALLBACKS */

      /* Clear the Timestamp interrupt pending bit */
      __HAL_RTC_TIMESTAMP_CLEAR_FLAG(hrtc, RTC_FLAG_TSF);
    }
  }

  /* Get the Tamper 1 interrupt source enable status */
  if (__HAL_RTC_TAMPER_GET_IT_SOURCE(hrtc, RTC_IT_TAMP) != 0U)
  {
    /* Get the pending status of the Tamper 1 Interrupt */
    if (__HAL_RTC_TAMPER_GET_FLAG(hrtc, RTC_FLAG_TAMP1F) != 0U)
    {
      /* Tamper callback */
#if (USE_HAL_RTC_REGISTER_CALLBACKS == 1)
      hrtc->Tamper1EventCallback(hrtc);
#else
      HAL_RTCEx_Tamper1EventCallback(hrtc);
#endif /* USE_HAL_RTC_REGISTER_CALLBACKS */

      /* Clear the Tamper interrupt pending bit */
      __HAL_RTC_TAMPER_CLEAR_FLAG(hrtc, RTC_FLAG_TAMP1F);
    }
  }

#if defined(RTC_TAMPER2_SUPPORT)
  /* Get the Tamper 2 interrupt source enable status */
  if (__HAL_RTC_TAMPER_GET_IT_SOURCE(hrtc, RTC_IT_TAMP) != 0U)
  {
    /* Get the pending status of the Tamper 2 Interrupt */
    if (__HAL_RTC_TAMPER_GET_FLAG(hrtc, RTC_FLAG_TAMP2F) != 0U)
    {
      /* Tamper callback */
#if (USE_HAL_RTC_REGISTER_CALLBACKS == 1)
      hrtc->Tamper2EventCallback(hrtc);
#else
      HAL_RTCEx_Tamper2EventCallback(hrtc);
#endif /* USE_HAL_RTC_REGISTER_CALLBACKS */

      /* Clear the Tamper interrupt pending bit */
      __HAL_RTC_TAMPER_CLEAR_FLAG(hrtc, RTC_FLAG_TAMP2F);
    }
  }
#endif /* RTC_TAMPER2_SUPPORT */

  /* Clear the EXTI's Flag for RTC Timestamp and Tamper */
  __HAL_RTC_TAMPER_TIMESTAMP_EXTI_CLEAR_FLAG();

  /* Change RTC state */
  hrtc->State = HAL_RTC_STATE_READY;
}

/**
  * @brief  Timestamp callback.
  * @param  hrtc pointer to a RTC_HandleTypeDef structure that contains
  *                the configuration information for RTC.
  * @retval None
  */
__weak void HAL_RTCEx_TimeStampEventCallback(RTC_HandleTypeDef *hrtc)
{
  /* Prevent unused argument(s) compilation warning */
  UNUSED(hrtc);

  /* NOTE: This function should not be modified, when the callback is needed,
           the HAL_RTCEx_TimeStampEventCallback could be implemented in the user file
  */
}

/**
  * @brief  Tamper 1 callback.
  * @param  hrtc pointer to a RTC_HandleTypeDef structure that contains
  *                the configuration information for RTC.
  * @retval None
  */
__weak void HAL_RTCEx_Tamper1EventCallback(RTC_HandleTypeDef *hrtc)
{
  /* Prevent unused argument(s) compilation warning */
  UNUSED(hrtc);

  /* NOTE: This function should not be modified, when the callback is needed,
           the HAL_RTCEx_Tamper1EventCallback could be implemented in the user file
   */
}

#if defined(RTC_TAMPER2_SUPPORT)
/**
  * @brief  Tamper 2 callback.
  * @param  hrtc pointer to a RTC_HandleTypeDef structure that contains
  *                the configuration information for RTC.
  * @retval None
  */
__weak void HAL_RTCEx_Tamper2EventCallback(RTC_HandleTypeDef *hrtc)
{
  /* Prevent unused argument(s) compilation warning */
  UNUSED(hrtc);

  /* NOTE: This function should not be modified, when the callback is needed,
           the HAL_RTCEx_Tamper2EventCallback could be implemented in the user file
   */
}
#endif /* RTC_TAMPER2_SUPPORT */

/**
  * @brief  Handles Timestamp polling request.
  * @param  hrtc pointer to a RTC_HandleTypeDef structure that contains
  *                the configuration information for RTC.
  * @param  Timeout Timeout duration
  * @retval HAL status
  */
HAL_StatusTypeDef HAL_RTCEx_PollForTimeStampEvent(RTC_HandleTypeDef *hrtc, uint32_t Timeout)
{
  uint32_t tickstart = 0U;

  /* Get tick */
  tickstart = HAL_GetTick();

  while (__HAL_RTC_TIMESTAMP_GET_FLAG(hrtc, RTC_FLAG_TSF) == 0U)
  {
    if (Timeout != HAL_MAX_DELAY)
    {
      if ((Timeout == 0U) || ((HAL_GetTick() - tickstart) > Timeout))
      {
        hrtc->State = HAL_RTC_STATE_TIMEOUT;
        return HAL_TIMEOUT;
      }
    }

    if (__HAL_RTC_TIMESTAMP_GET_FLAG(hrtc, RTC_FLAG_TSOVF) != 0U)
    {
      /* Clear the Timestamp Overrun Flag */
      __HAL_RTC_TIMESTAMP_CLEAR_FLAG(hrtc, RTC_FLAG_TSOVF);

      /* Change Timestamp state */
      hrtc->State = HAL_RTC_STATE_ERROR;

      return HAL_ERROR;
    }
  }

  /* Change RTC state */
  hrtc->State = HAL_RTC_STATE_READY;

  return HAL_OK;
}

/**
  * @brief  Handles Tamper 1 Polling.
  * @param  hrtc pointer to a RTC_HandleTypeDef structure that contains
  *                the configuration information for RTC.
  * @param  Timeout Timeout duration
  * @retval HAL status
  */
HAL_StatusTypeDef HAL_RTCEx_PollForTamper1Event(RTC_HandleTypeDef *hrtc, uint32_t Timeout)
{
  uint32_t tickstart = 0U;

  /* Get tick */
  tickstart = HAL_GetTick();

  /* Get the status of the Interrupt */
  while (__HAL_RTC_TAMPER_GET_FLAG(hrtc, RTC_FLAG_TAMP1F) == 0U)
  {
    if (Timeout != HAL_MAX_DELAY)
    {
      if ((Timeout == 0U) || ((HAL_GetTick() - tickstart) > Timeout))
      {
        hrtc->State = HAL_RTC_STATE_TIMEOUT;
        return HAL_TIMEOUT;
      }
    }
  }

  /* Clear the Tamper Flag */
  __HAL_RTC_TAMPER_CLEAR_FLAG(hrtc, RTC_FLAG_TAMP1F);

  /* Change RTC state */
  hrtc->State = HAL_RTC_STATE_READY;

  return HAL_OK;
}

#if defined(RTC_TAMPER2_SUPPORT)
/**
  * @brief  Handles Tamper 2 Polling.
  * @param  hrtc pointer to a RTC_HandleTypeDef structure that contains
  *                the configuration information for RTC.
  * @param  Timeout Timeout duration
  * @retval HAL status
  */
HAL_StatusTypeDef HAL_RTCEx_PollForTamper2Event(RTC_HandleTypeDef *hrtc, uint32_t Timeout)
{
  uint32_t tickstart = 0U;

  /* Get tick */
  tickstart = HAL_GetTick();

  /* Get the status of the Interrupt */
  while (__HAL_RTC_TAMPER_GET_FLAG(hrtc, RTC_FLAG_TAMP2F) == 0U)
  {
    if (Timeout != HAL_MAX_DELAY)
    {
      if ((Timeout == 0U) || ((HAL_GetTick() - tickstart) > Timeout))
      {
        hrtc->State = HAL_RTC_STATE_TIMEOUT;
        return HAL_TIMEOUT;
      }
    }
  }

  /* Clear the Tamper Flag */
  __HAL_RTC_TAMPER_CLEAR_FLAG(hrtc, RTC_FLAG_TAMP2F);

  /* Change RTC state */
  hrtc->State = HAL_RTC_STATE_READY;

  return HAL_OK;
}
#endif /* RTC_TAMPER2_SUPPORT */

/**
  * @}
  */

/** @defgroup RTCEx_Exported_Functions_Group2 RTC Wakeup functions
  * @brief    RTC Wakeup functions
  *
@verbatim
 ===============================================================================
                        ##### RTC Wakeup functions #####
 ===============================================================================

 [..] This section provides functions allowing to configure Wakeup feature

@endverbatim
  * @{
  */

/**
  * @brief  Sets wakeup timer.
  * @param  hrtc pointer to a RTC_HandleTypeDef structure that contains
  *                the configuration information for RTC.
  * @param  WakeUpCounter Wakeup counter
  * @param  WakeUpClock Wakeup clock
  * @retval HAL status
  */
HAL_StatusTypeDef HAL_RTCEx_SetWakeUpTimer(RTC_HandleTypeDef *hrtc, uint32_t WakeUpCounter, uint32_t WakeUpClock)
{
  uint32_t tickstart = 0U;

  /* Check the parameters */
  assert_param(IS_RTC_WAKEUP_CLOCK(WakeUpClock));
  assert_param(IS_RTC_WAKEUP_COUNTER(WakeUpCounter));

  /* Process Locked */
  __HAL_LOCK(hrtc);

  hrtc->State = HAL_RTC_STATE_BUSY;

  /* Disable the write protection for RTC registers */
  __HAL_RTC_WRITEPROTECTION_DISABLE(hrtc);

  /* Check RTC WUTWF flag is reset only when wakeup timer enabled*/
  if ((hrtc->Instance->CR & RTC_CR_WUTE) != 0U)
  {
    tickstart = HAL_GetTick();

    /* Wait till RTC WUTWF flag is reset and if timeout is reached exit */
    while (__HAL_RTC_WAKEUPTIMER_GET_FLAG(hrtc, RTC_FLAG_WUTWF) != 0U)
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

  /* Disable the Wakeup timer */
  __HAL_RTC_WAKEUPTIMER_DISABLE(hrtc);

  /* Clear the Wakeup flag */
  __HAL_RTC_WAKEUPTIMER_CLEAR_FLAG(hrtc, RTC_FLAG_WUTF);

  /* Get tick */
  tickstart = HAL_GetTick();

  /* Wait till RTC WUTWF flag is set and if timeout is reached exit */
  while (__HAL_RTC_WAKEUPTIMER_GET_FLAG(hrtc, RTC_FLAG_WUTWF) == 0U)
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

  /* Clear the Wakeup Timer clock source bits in CR register */
  hrtc->Instance->CR &= (uint32_t)~RTC_CR_WUCKSEL;

  /* Configure the clock source */
  hrtc->Instance->CR |= (uint32_t)WakeUpClock;

  /* Configure the Wakeup Timer counter */
  hrtc->Instance->WUTR = (uint32_t)WakeUpCounter;

  /* Enable the Wakeup Timer */
  __HAL_RTC_WAKEUPTIMER_ENABLE(hrtc);

  /* Enable the write protection for RTC registers */
  __HAL_RTC_WRITEPROTECTION_ENABLE(hrtc);

  hrtc->State = HAL_RTC_STATE_READY;

  /* Process Unlocked */
  __HAL_UNLOCK(hrtc);

  return HAL_OK;
}

/**
  * @brief  Sets wakeup timer with interrupt.
  * @param  hrtc pointer to a RTC_HandleTypeDef structure that contains
  *                the configuration information for RTC.
  * @param  WakeUpCounter Wakeup counter
  * @param  WakeUpClock Wakeup clock
  * @retval HAL status
  */
HAL_StatusTypeDef HAL_RTCEx_SetWakeUpTimer_IT(RTC_HandleTypeDef *hrtc, uint32_t WakeUpCounter, uint32_t WakeUpClock)
{
  __IO uint32_t count  = RTC_TIMEOUT_VALUE * (SystemCoreClock / 32U / 1000U);

  /* Check the parameters */
  assert_param(IS_RTC_WAKEUP_CLOCK(WakeUpClock));
  assert_param(IS_RTC_WAKEUP_COUNTER(WakeUpCounter));

  /* Process Locked */
  __HAL_LOCK(hrtc);

  hrtc->State = HAL_RTC_STATE_BUSY;

  /* Disable the write protection for RTC registers */
  __HAL_RTC_WRITEPROTECTION_DISABLE(hrtc);

  /* Check RTC WUTWF flag is reset only when wakeup timer enabled */
  if ((hrtc->Instance->CR & RTC_CR_WUTE) != 0U)
  {
    /* Wait till RTC WUTWF flag is reset and if timeout is reached exit */
    do
    {
      if (count-- == 0U)
      {
        /* Enable the write protection for RTC registers */
        __HAL_RTC_WRITEPROTECTION_ENABLE(hrtc);

        hrtc->State = HAL_RTC_STATE_TIMEOUT;

        /* Process Unlocked */
        __HAL_UNLOCK(hrtc);

        return HAL_TIMEOUT;
      }
    } while (__HAL_RTC_WAKEUPTIMER_GET_FLAG(hrtc, RTC_FLAG_WUTWF) != 0U);
  }

  /* Disable the Wakeup timer */
  __HAL_RTC_WAKEUPTIMER_DISABLE(hrtc);

  /* Clear the Wakeup flag */
  __HAL_RTC_WAKEUPTIMER_CLEAR_FLAG(hrtc, RTC_FLAG_WUTF);

  /* Reload the counter */
  count = RTC_TIMEOUT_VALUE * (SystemCoreClock / 32U / 1000U);

  /* Wait till RTC WUTWF flag is set and if timeout is reached exit */
  do
  {
    if (count-- == 0U)
    {
      /* Enable the write protection for RTC registers */
      __HAL_RTC_WRITEPROTECTION_ENABLE(hrtc);

      hrtc->State = HAL_RTC_STATE_TIMEOUT;

      /* Process Unlocked */
      __HAL_UNLOCK(hrtc);

      return HAL_TIMEOUT;
    }
  } while (__HAL_RTC_WAKEUPTIMER_GET_FLAG(hrtc, RTC_FLAG_WUTWF) == 0U);

  /* Clear the Wakeup Timer clock source bits in CR register */
  hrtc->Instance->CR &= (uint32_t)~RTC_CR_WUCKSEL;

  /* Configure the clock source */
  hrtc->Instance->CR |= (uint32_t)WakeUpClock;

  /* Configure the Wakeup Timer counter */
  hrtc->Instance->WUTR = (uint32_t)WakeUpCounter;

  /* RTC wakeup timer Interrupt Configuration: EXTI configuration */
  __HAL_RTC_WAKEUPTIMER_EXTI_ENABLE_IT();
  __HAL_RTC_WAKEUPTIMER_EXTI_ENABLE_RISING_EDGE();

  /* Configure the interrupt in the RTC_CR register */
  __HAL_RTC_WAKEUPTIMER_ENABLE_IT(hrtc, RTC_IT_WUT);

  /* Enable the Wakeup Timer */
  __HAL_RTC_WAKEUPTIMER_ENABLE(hrtc);

  /* Enable the write protection for RTC registers */
  __HAL_RTC_WRITEPROTECTION_ENABLE(hrtc);

  hrtc->State = HAL_RTC_STATE_READY;

  /* Process Unlocked */
  __HAL_UNLOCK(hrtc);

  return HAL_OK;
}

/**
  * @brief  Deactivates wakeup timer counter.
  * @param  hrtc pointer to a RTC_HandleTypeDef structure that contains
  *                the configuration information for RTC.
  * @retval HAL status
  */
HAL_StatusTypeDef HAL_RTCEx_DeactivateWakeUpTimer(RTC_HandleTypeDef *hrtc)
{
  uint32_t tickstart = 0U;

  /* Process Locked */
  __HAL_LOCK(hrtc);

  hrtc->State = HAL_RTC_STATE_BUSY;

  /* Disable the write protection for RTC registers */
  __HAL_RTC_WRITEPROTECTION_DISABLE(hrtc);

  /* Disable the Wakeup Timer */
  __HAL_RTC_WAKEUPTIMER_DISABLE(hrtc);

  /* In case of interrupt mode is used, the interrupt source must disabled */
  __HAL_RTC_WAKEUPTIMER_DISABLE_IT(hrtc, RTC_IT_WUT);

  /* Get tick */
  tickstart = HAL_GetTick();

  /* Wait till RTC WUTWF flag is set and if timeout is reached exit */
  while (__HAL_RTC_WAKEUPTIMER_GET_FLAG(hrtc, RTC_FLAG_WUTWF) == 0U)
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
  * @brief  Gets wakeup timer counter.
  * @param  hrtc pointer to a RTC_HandleTypeDef structure that contains
  *                the configuration information for RTC.
  * @retval Counter value
  */
uint32_t HAL_RTCEx_GetWakeUpTimer(RTC_HandleTypeDef *hrtc)
{
  /* Get the counter value */
  return ((uint32_t)(hrtc->Instance->WUTR & RTC_WUTR_WUT));
}

/**
  * @brief  Handles Wakeup Timer interrupt request.
  * @note   Unlike alarm interrupt line (shared by Alarms A and B) or tamper
  *         interrupt line (shared by timestamp and tampers) wakeup timer
  *         interrupt line is exclusive to the wakeup timer.
  *         There is no need in this case to check on the interrupt enable
  *         status via __HAL_RTC_WAKEUPTIMER_GET_IT_SOURCE().
  * @param  hrtc pointer to a RTC_HandleTypeDef structure that contains
  *                the configuration information for RTC.
  * @retval None
  */
void HAL_RTCEx_WakeUpTimerIRQHandler(RTC_HandleTypeDef *hrtc)
{
  /* Get the pending status of the Wakeup timer Interrupt */
  if (__HAL_RTC_WAKEUPTIMER_GET_FLAG(hrtc, RTC_FLAG_WUTF) != 0U)
  {
    /* Wakeup timer callback */
#if (USE_HAL_RTC_REGISTER_CALLBACKS == 1)
    hrtc->WakeUpTimerEventCallback(hrtc);
#else
    HAL_RTCEx_WakeUpTimerEventCallback(hrtc);
#endif /* USE_HAL_RTC_REGISTER_CALLBACKS */

    /* Clear the Wakeup timer interrupt pending bit */
    __HAL_RTC_WAKEUPTIMER_CLEAR_FLAG(hrtc, RTC_FLAG_WUTF);
  }

  /* Clear the EXTI's line Flag for RTC WakeUpTimer */
  __HAL_RTC_WAKEUPTIMER_EXTI_CLEAR_FLAG();

  /* Change RTC state */
  hrtc->State = HAL_RTC_STATE_READY;
}

/**
  * @brief  Wakeup Timer callback.
  * @param  hrtc pointer to a RTC_HandleTypeDef structure that contains
  *                the configuration information for RTC.
  * @retval None
  */
__weak void HAL_RTCEx_WakeUpTimerEventCallback(RTC_HandleTypeDef *hrtc)
{
  /* Prevent unused argument(s) compilation warning */
  UNUSED(hrtc);

  /* NOTE: This function should not be modified, when the callback is needed,
           the HAL_RTCEx_WakeUpTimerEventCallback could be implemented in the user file
   */
}

/**
  * @brief  Handles Wakeup Timer Polling.
  * @param  hrtc pointer to a RTC_HandleTypeDef structure that contains
  *                the configuration information for RTC.
  * @param  Timeout Timeout duration
  * @retval HAL status
  */
HAL_StatusTypeDef HAL_RTCEx_PollForWakeUpTimerEvent(RTC_HandleTypeDef *hrtc, uint32_t Timeout)
{
  uint32_t tickstart = 0U;

  /* Get tick */
  tickstart = HAL_GetTick();

  while (__HAL_RTC_WAKEUPTIMER_GET_FLAG(hrtc, RTC_FLAG_WUTF) == 0U)
  {
    if (Timeout != HAL_MAX_DELAY)
    {
      if ((Timeout == 0U) || ((HAL_GetTick() - tickstart) > Timeout))
      {
        hrtc->State = HAL_RTC_STATE_TIMEOUT;
        return HAL_TIMEOUT;
      }
    }
  }

  /* Clear the Wakeup timer Flag */
  __HAL_RTC_WAKEUPTIMER_CLEAR_FLAG(hrtc, RTC_FLAG_WUTF);

  /* Change RTC state */
  hrtc->State = HAL_RTC_STATE_READY;

  return HAL_OK;
}

/**
  * @}
  */

/** @defgroup RTCEx_Exported_Functions_Group3 Extended Peripheral Control functions
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
  * @brief  Writes a data in a specified RTC Backup data register.
  * @param  hrtc pointer to a RTC_HandleTypeDef structure that contains
  *                the configuration information for RTC.
  * @param  BackupRegister RTC Backup data Register number.
  *          This parameter can be: RTC_BKP_DRx (where x can be from 0 to 19)
  *                                 to specify the register.
  * @param  Data Data to be written in the specified RTC Backup data register.
  * @retval None
  */
void HAL_RTCEx_BKUPWrite(RTC_HandleTypeDef *hrtc, uint32_t BackupRegister, uint32_t Data)
{
  uint32_t tmp = 0U;

  /* Check the parameters */
  assert_param(IS_RTC_BKP(BackupRegister));

  tmp = (uint32_t) & (hrtc->Instance->BKP0R);
  tmp += (BackupRegister * 4U);

  /* Write the specified register */
  *(__IO uint32_t *)tmp = (uint32_t)Data;
}

/**
  * @brief  Reads data from the specified RTC Backup data Register.
  * @param  hrtc pointer to a RTC_HandleTypeDef structure that contains
  *                the configuration information for RTC.
  * @param  BackupRegister RTC Backup data Register number.
  *          This parameter can be: RTC_BKP_DRx (where x can be from 0 to 19)
  *                                 to specify the register.
  * @retval Read value
  */
uint32_t HAL_RTCEx_BKUPRead(RTC_HandleTypeDef *hrtc, uint32_t BackupRegister)
{
  uint32_t tmp = 0U;

  /* Check the parameters */
  assert_param(IS_RTC_BKP(BackupRegister));

  tmp = (uint32_t) & (hrtc->Instance->BKP0R);
  tmp += (BackupRegister * 4U);

  /* Read the specified register */
  return (*(__IO uint32_t *)tmp);
}

/**
  * @brief  Sets the Coarse calibration parameters.
  * @param  hrtc pointer to a RTC_HandleTypeDef structure that contains
  *                the configuration information for RTC.
  * @param  CalibSign Specifies the sign of the coarse calibration value.
  *          This parameter can be  one of the following values:
  *             @arg RTC_CALIBSIGN_POSITIVE: The value sign is positive
  *             @arg RTC_CALIBSIGN_NEGATIVE: The value sign is negative
  * @param  Value value of coarse calibration expressed in ppm (coded on 5 bits).
  *
  * @note   This Calibration value should be between 0 and 63 when using negative
  *         sign with a 2-ppm step.
  *
  * @note   This Calibration value should be between 0 and 126 when using positive
  *         sign with a 4-ppm step.
  * @retval HAL status
  */
HAL_StatusTypeDef HAL_RTCEx_SetCoarseCalib(RTC_HandleTypeDef *hrtc, uint32_t CalibSign, uint32_t Value)
{
  HAL_StatusTypeDef status;

  /* Check the parameters */
  assert_param(IS_RTC_CALIB_SIGN(CalibSign));
  assert_param(IS_RTC_CALIB_VALUE(Value));

  /* Process Locked */
  __HAL_LOCK(hrtc);

  hrtc->State = HAL_RTC_STATE_BUSY;

  /* Disable the write protection for RTC registers */
  __HAL_RTC_WRITEPROTECTION_DISABLE(hrtc);

  /* Enter Initialization mode */
  status = RTC_EnterInitMode(hrtc);

  if (status == HAL_OK)
  {
    /* Enable the Coarse Calibration */
    __HAL_RTC_COARSE_CALIB_ENABLE(hrtc);

    /* Set the coarse calibration value */
    hrtc->Instance->CALIBR = (uint32_t)(CalibSign | Value);

    /* Exit Initialization mode */
    status = RTC_ExitInitMode(hrtc);
  }

  if (status == HAL_OK)
  {
    hrtc->State = HAL_RTC_STATE_READY;
  }

  /* Enable the write protection for RTC registers */
  __HAL_RTC_WRITEPROTECTION_ENABLE(hrtc);

  /* Process Unlocked */
  __HAL_UNLOCK(hrtc);

  return status;
}

/**
  * @brief  Deactivates the Coarse calibration parameters.
  * @param  hrtc pointer to a RTC_HandleTypeDef structure that contains
  *                the configuration information for RTC.
  * @retval HAL status
  */
HAL_StatusTypeDef HAL_RTCEx_DeactivateCoarseCalib(RTC_HandleTypeDef *hrtc)
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
    /* Disable the Coarse Calibration */
    __HAL_RTC_COARSE_CALIB_DISABLE(hrtc);

    /* Exit Initialization mode */
    status = RTC_ExitInitMode(hrtc);
  }

  if (status == HAL_OK)
  {
    hrtc->State = HAL_RTC_STATE_READY;
  }

  /* Enable the write protection for RTC registers */
  __HAL_RTC_WRITEPROTECTION_ENABLE(hrtc);

  /* Process Unlocked */
  __HAL_UNLOCK(hrtc);

  return status;
}

/**
  * @brief  Sets the Smooth calibration parameters.
  * @param  hrtc pointer to a RTC_HandleTypeDef structure that contains
  *                the configuration information for RTC.
  * @param  SmoothCalibPeriod Select the Smooth Calibration Period.
  *          This parameter can be can be one of the following values:
  *             @arg RTC_SMOOTHCALIB_PERIOD_32SEC: The smooth calibration period is 32s.
  *             @arg RTC_SMOOTHCALIB_PERIOD_16SEC: The smooth calibration period is 16s.
  *             @arg RTC_SMOOTHCALIB_PERIOD_8SEC: The smooth calibration period is 8s.
  * @param  SmoothCalibPlusPulses Select to Set or reset the CALP bit.
  *          This parameter can be one of the following values:
  *             @arg RTC_SMOOTHCALIB_PLUSPULSES_SET: Add one RTCCLK pulse every 2*11 pulses.
  *             @arg RTC_SMOOTHCALIB_PLUSPULSES_RESET: No RTCCLK pulses are added.
  * @param  SmoothCalibMinusPulsesValue Select the value of CALM[8:0] bits.
  *          This parameter can be one any value from 0 to 0x000001FF.
  * @note   To deactivate the smooth calibration, the field SmoothCalibPlusPulses
  *         must be equal to SMOOTHCALIB_PLUSPULSES_RESET and the field
  *         SmoothCalibMinusPulsesValue must be equal to 0.
  * @retval HAL status
  */
HAL_StatusTypeDef HAL_RTCEx_SetSmoothCalib(RTC_HandleTypeDef *hrtc, uint32_t SmoothCalibPeriod, uint32_t SmoothCalibPlusPulses, uint32_t SmoothCalibMinusPulsesValue)
{
  uint32_t tickstart = 0U;

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
  if ((hrtc->Instance->ISR & RTC_ISR_RECALPF) != 0U)
  {
    /* Get tick */
    tickstart = HAL_GetTick();

    /* check if a calibration is pending*/
    while ((hrtc->Instance->ISR & RTC_ISR_RECALPF) != 0U)
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
  hrtc->Instance->CALR = (uint32_t)((uint32_t)SmoothCalibPeriod     | \
                                    (uint32_t)SmoothCalibPlusPulses | \
                                    (uint32_t)SmoothCalibMinusPulsesValue);

  /* Enable the write protection for RTC registers */
  __HAL_RTC_WRITEPROTECTION_ENABLE(hrtc);

  /* Change RTC state */
  hrtc->State = HAL_RTC_STATE_READY;

  /* Process Unlocked */
  __HAL_UNLOCK(hrtc);

  return HAL_OK;
}

/**
  * @brief  Configures the Synchronization Shift Control Settings.
  * @note   When REFCKON is set, firmware must not write to Shift control register.
  * @param  hrtc pointer to a RTC_HandleTypeDef structure that contains
  *                the configuration information for RTC.
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
  uint32_t tickstart = 0U;

  /* Check the parameters */
  assert_param(IS_RTC_SHIFT_ADD1S(ShiftAdd1S));
  assert_param(IS_RTC_SHIFT_SUBFS(ShiftSubFS));

  /* Process Locked */
  __HAL_LOCK(hrtc);

  hrtc->State = HAL_RTC_STATE_BUSY;

  /* Disable the write protection for RTC registers */
  __HAL_RTC_WRITEPROTECTION_DISABLE(hrtc);

  /* Get tick */
  tickstart = HAL_GetTick();

  /* Wait until the shift is completed */
  while ((hrtc->Instance->ISR & RTC_ISR_SHPF) != 0U)
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
  if ((hrtc->Instance->CR & RTC_CR_REFCKON) == 0U)
  {
    /* Configure the Shift settings */
    hrtc->Instance->SHIFTR = (uint32_t)(uint32_t)(ShiftSubFS) | (uint32_t)(ShiftAdd1S);

    /* If  RTC_CR_BYPSHAD bit = 0, wait for synchro else this check is not needed */
    if ((hrtc->Instance->CR & RTC_CR_BYPSHAD) == 0U)
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
  * @brief  Configures the Calibration Pinout (RTC_CALIB) Selection (1Hz or 512Hz).
  * @param  hrtc pointer to a RTC_HandleTypeDef structure that contains
  *                the configuration information for RTC.
  * @param  CalibOutput Select the Calibration output Selection.
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

  /* Clear flags before config */
  hrtc->Instance->CR &= (uint32_t)~RTC_CR_COSEL;

  /* Configure the RTC_CR register */
  hrtc->Instance->CR |= (uint32_t)CalibOutput;

  __HAL_RTC_CALIBRATION_OUTPUT_ENABLE(hrtc);

  /* Enable the write protection for RTC registers */
  __HAL_RTC_WRITEPROTECTION_ENABLE(hrtc);

  /* Change RTC state */
  hrtc->State = HAL_RTC_STATE_READY;

  /* Process Unlocked */
  __HAL_UNLOCK(hrtc);

  return HAL_OK;
}

/**
  * @brief  Deactivates the Calibration Pinout (RTC_CALIB) Selection (1Hz or 512Hz).
  * @param  hrtc pointer to a RTC_HandleTypeDef structure that contains
  *                the configuration information for RTC.
  * @retval HAL status
  */
HAL_StatusTypeDef HAL_RTCEx_DeactivateCalibrationOutPut(RTC_HandleTypeDef *hrtc)
{
  /* Process Locked */
  __HAL_LOCK(hrtc);

  hrtc->State = HAL_RTC_STATE_BUSY;

  /* Disable the write protection for RTC registers */
  __HAL_RTC_WRITEPROTECTION_DISABLE(hrtc);

  __HAL_RTC_CALIBRATION_OUTPUT_DISABLE(hrtc);

  /* Enable the write protection for RTC registers */
  __HAL_RTC_WRITEPROTECTION_ENABLE(hrtc);

  /* Change RTC state */
  hrtc->State = HAL_RTC_STATE_READY;

  /* Process Unlocked */
  __HAL_UNLOCK(hrtc);

  return HAL_OK;
}

/**
  * @brief  Enables the RTC reference clock detection.
  * @param  hrtc pointer to a RTC_HandleTypeDef structure that contains
  *                the configuration information for RTC.
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
    /* Enable the reference clock detection */
    __HAL_RTC_CLOCKREF_DETECTION_ENABLE(hrtc);

    /* Exit Initialization mode */
    status = RTC_ExitInitMode(hrtc);
  }

  if (status == HAL_OK)
  {
    hrtc->State = HAL_RTC_STATE_READY;
  }

  /* Enable the write protection for RTC registers */
  __HAL_RTC_WRITEPROTECTION_ENABLE(hrtc);

  /* Process Unlocked */
  __HAL_UNLOCK(hrtc);

  return status;
}

/**
  * @brief  Disable the RTC reference clock detection.
  * @param  hrtc pointer to a RTC_HandleTypeDef structure that contains
  *                the configuration information for RTC.
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
    /* Disable the reference clock detection */
    __HAL_RTC_CLOCKREF_DETECTION_DISABLE(hrtc);

    /* Exit Initialization mode */
    status = RTC_ExitInitMode(hrtc);
  }

  if (status == HAL_OK)
  {
    hrtc->State = HAL_RTC_STATE_READY;
  }

  /* Enable the write protection for RTC registers */
  __HAL_RTC_WRITEPROTECTION_ENABLE(hrtc);

  /* Process Unlocked */
  __HAL_UNLOCK(hrtc);

  return status;
}

/**
  * @brief  Enables the Bypass Shadow feature.
  * @param  hrtc pointer to a RTC_HandleTypeDef structure that contains
  *                the configuration information for RTC.
  * @note   When the Bypass Shadow is enabled the calendar value are taken
  *         directly from the Calendar counter.
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
  hrtc->Instance->CR |= (uint8_t)RTC_CR_BYPSHAD;

  /* Enable the write protection for RTC registers */
  __HAL_RTC_WRITEPROTECTION_ENABLE(hrtc);

  /* Change RTC state */
  hrtc->State = HAL_RTC_STATE_READY;

  /* Process Unlocked */
  __HAL_UNLOCK(hrtc);

  return HAL_OK;
}

/**
  * @brief  Disables the Bypass Shadow feature.
  * @param  hrtc pointer to a RTC_HandleTypeDef structure that contains
  *                the configuration information for RTC.
  * @note   When the Bypass Shadow is enabled the calendar value are taken
  *         directly from the Calendar counter.
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
  hrtc->Instance->CR &= (uint8_t)~RTC_CR_BYPSHAD;

  /* Enable the write protection for RTC registers */
  __HAL_RTC_WRITEPROTECTION_ENABLE(hrtc);

  /* Change RTC state */
  hrtc->State = HAL_RTC_STATE_READY;

  /* Process Unlocked */
  __HAL_UNLOCK(hrtc);

  return HAL_OK;
}

/**
  * @}
  */

/** @defgroup RTCEx_Exported_Functions_Group4 Extended features functions
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
  * @param  hrtc pointer to a RTC_HandleTypeDef structure that contains
  *                the configuration information for RTC.
  * @retval None
  */
__weak void HAL_RTCEx_AlarmBEventCallback(RTC_HandleTypeDef *hrtc)
{
  /* Prevent unused argument(s) compilation warning */
  UNUSED(hrtc);

  /* NOTE: This function should not be modified, when the callback is needed,
           the HAL_RTCEx_AlarmBEventCallback could be implemented in the user file
   */
}

/**
  * @brief  Handles Alarm B Polling request.
  * @param  hrtc pointer to a RTC_HandleTypeDef structure that contains
  *                the configuration information for RTC.
  * @param  Timeout Timeout duration
  * @retval HAL status
  */
HAL_StatusTypeDef HAL_RTCEx_PollForAlarmBEvent(RTC_HandleTypeDef *hrtc, uint32_t Timeout)
{
  uint32_t tickstart = 0U;

  /* Get tick */
  tickstart = HAL_GetTick();

  /* Wait till RTC ALRBF flag is set and if timeout is reached exit */
  while (__HAL_RTC_ALARM_GET_FLAG(hrtc, RTC_FLAG_ALRBF) == 0U)
  {
    if (Timeout != HAL_MAX_DELAY)
    {
      if ((Timeout == 0U) || ((HAL_GetTick() - tickstart) > Timeout))
      {
        hrtc->State = HAL_RTC_STATE_TIMEOUT;
        return HAL_TIMEOUT;
      }
    }
  }

  /* Clear the Alarm flag */
  __HAL_RTC_ALARM_CLEAR_FLAG(hrtc, RTC_FLAG_ALRBF);

  /* Change RTC state */
  hrtc->State = HAL_RTC_STATE_READY;

  return HAL_OK;
}

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
