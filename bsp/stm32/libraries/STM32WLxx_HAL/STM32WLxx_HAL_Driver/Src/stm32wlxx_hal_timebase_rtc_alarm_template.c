/**
  ******************************************************************************
  * @file    stm32wlxx_hal_timebase_rtc_alarm_template.c 
  * @author  MCD Application Team
  * @brief   HAL time base based on the hardware RTC_ALARM Template.
  *
  *          This file override the native HAL time base functions (defined as 
  *          weak) to use the RTC ALARM for time base generation:
  *           + Initializes the RTC peripheral to increment the seconds registers
  *             each 1s
  *           + The alarm is configured to assert an interrupt when the RTC
  *             subsecond register reaches 1ms when uwTickFreq is set to default
  *             value, else 10 ms or 100 ms, depending of above global variable
  *             value.
  *           + HAL_IncTick is called at each Alarm event
  *           + HSE (default), LSE or LSI can be selected as RTC clock source
 @verbatim
  ==============================================================================
                        ##### How to use this driver #####
  ==============================================================================
    [..]
    This file must be copied to the application folder and modified as follows:
    (#) Rename it to 'stm32wlxx_hal_timebase_rtc_alarm.c'
    (#) Add this file and the RTC HAL drivers to your project and uncomment
       HAL_RTC_MODULE_ENABLED define in stm32wlxx_hal_conf.h 

  @endverbatim
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2020 STMicroelectronics. 
  * All rights reserved.</center></h2>
  *
  * This software component is licensed by ST under BSD 3-Clause license,
  * the "License"; You may not use this file except in compliance with the
  * License. You may obtain a copy of the License at:
  *                       opensource.org/licenses/BSD-3-Clause
  *
  ******************************************************************************
  */

/* Includes ------------------------------------------------------------------*/
#include "stm32wlxx_hal.h"
/** @addtogroup STM32WLxx_HAL_Driver
  * @{
  */

/** @defgroup HAL_TimeBase_RTC_Alarm_Template  HAL TimeBase RTC Alarm Template
  * @{
  */ 

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Uncomment the line below to select the appropriate RTC Clock source for your application: 
  + RTC_CLOCK_SOURCE_HSE: can be selected for applications requiring timing precision.
  + RTC_CLOCK_SOURCE_LSE: can be selected for applications with low constraint on timing
                          precision.
  + RTC_CLOCK_SOURCE_LSI: can be selected for applications with low constraint on timing
                          precision.
  */
/* #define RTC_CLOCK_SOURCE_HSE */
/* #define RTC_CLOCK_SOURCE_LSE */
#define RTC_CLOCK_SOURCE_LSI

#if !defined(RTC_CLOCK_SOURCE_LSI) && !defined(RTC_CLOCK_SOURCE_LSE) && !defined(RTC_CLOCK_SOURCE_HSE)
#error Please select the RTC Clock source AT PROJECT LEVEL
#endif

/* Minimize Asynchronous prescaler for power consumption :
  ck_apre = RTCCLK / (ASYNC prediv + 1)
  ck_spre = ck_apre/(SYNC prediv + 1) = 1 Hz */
#if defined (RTC_CLOCK_SOURCE_LSE)
/* LSE Freq = 32.768 kHz RC */
#define RTC_ASYNCH_PREDIV                   0u
#define RTC_SYNCH_PREDIV                    0x3FFFu /* (16384 - 1) */
#elif defined (RTC_CLOCK_SOURCE_LSI)
/* LSI Freq = 32 kHz RC  */
#define RTC_ASYNCH_PREDIV                   0u
#define RTC_SYNCH_PREDIV                    0x3E7Fu /* (16000 - 1) */
#elif defined (RTC_CLOCK_SOURCE_HSE)
/* HSE Freq as RTCCLK = 32 MHz / 32 = 1 MHz */
#define RTC_ASYNCH_PREDIV                   0x1Fu   /* (32 - 1) */
#define RTC_SYNCH_PREDIV                    0x7A11u /* (31250 -1) */
#endif


/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
RTC_HandleTypeDef        hRTC_Handle = {.Init = {0}};

/* Private function prototypes -----------------------------------------------*/
#if defined(CORE_CM0PLUS)
void RTC_LSECSS_IRQHandler(void);
#else
void RTC_Alarm_IRQHandler(void);
#endif

/* Private functions ---------------------------------------------------------*/

/**
  * @brief  This function configures the RTC ALARM A as a time base source. 
  *         The time source is configured to have 1ms time base with a dedicated 
  *         Tick interrupt priority. 
  *         Calendar time base is = ((RTC_ASYNCH_PREDIV + 1) * (RTC_SYNCH_PREDIV + 1)) / RTC_CLOCK
  *                               = 1s
  *         Alarm interrupt timebase is = (RTC_SYNCH_PREDIV / (1000 / uwTickFreq))
  *                                     = 1 ms when uwTickFreq is set to 1 kHz
  * @note   This function is called automatically at the beginning of program after
  *         reset by HAL_Init() or at any time when clock is configured, by HAL_RCC_ClockConfig(). 
  * @param  TickPriority: Tick interrupt priority.
  * @retval HAL status
  */
HAL_StatusTypeDef HAL_InitTick(uint32_t TickPriority)
{
  HAL_StatusTypeDef status = HAL_OK;
  RCC_OscInitTypeDef        RCC_OscInitStruct = {0};
  RCC_PeriphCLKInitTypeDef  PeriphClkInitStruct = {0};
  RTC_TimeTypeDef           time;
  RTC_DateTypeDef           date;
  RTC_AlarmTypeDef          alarm;


  /* Check uwTickFreq for MisraC 2012 (even if uwTickFreq is a enum type that don't take the value zero)*/
  if ((uint32_t)uwTickFreq != 0U)
  {
    /* Disable backup domeain protection */
    HAL_PWR_EnableBkUpAccess();

    /* Enable RTC APB clock gating */
    __HAL_RCC_RTCAPB_CLK_ENABLE();

    /* Disable the Alarm A */
    __HAL_RTC_ALARMA_DISABLE(&hRTC_Handle);
    /* In case of interrupt mode is used, the interrupt source must disabled */ 
    __HAL_RTC_ALARM_DISABLE_IT(&hRTC_Handle, RTC_IT_ALRA);
    __HAL_RTC_ALARM_CLEAR_FLAG(&hRTC_Handle, RTC_FLAG_ALRAF);

    /* Get RTC clock configuration */
    HAL_RCCEx_GetPeriphCLKConfig(&PeriphClkInitStruct);

    /*In case of RTC clock already enable, make sure it's the good one */
#if defined (RTC_CLOCK_SOURCE_LSE)
    if ((PeriphClkInitStruct.RTCClockSelection == RCC_RTCCLKSOURCE_LSE) && (__HAL_RCC_GET_FLAG(RCC_FLAG_LSERDY) != 0x00u))
#elif defined (RTC_CLOCK_SOURCE_LSI)
    if ((PeriphClkInitStruct.RTCClockSelection == RCC_RTCCLKSOURCE_LSI) && (__HAL_RCC_GET_FLAG(RCC_FLAG_LSIRDY) != 0x00u))
#elif defined (RTC_CLOCK_SOURCE_HSE)
    if ((PeriphClkInitStruct.RTCClockSelection == RCC_RTCCLKSOURCE_HSE_DIV32) && (__HAL_RCC_GET_FLAG(RCC_FLAG_HSERDY) != 0x00u))
#else
#error Please select the RTC Clock source
#endif
    {
      /* Do nothing */
    }
    else
    {
#ifdef RTC_CLOCK_SOURCE_LSE
      /* Configure LSE as RTC clock source */
      RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_LSE;
      RCC_OscInitStruct.PLL.PLLState = RCC_PLL_NONE;
      RCC_OscInitStruct.LSEState = RCC_LSE_ON;
      PeriphClkInitStruct.RTCClockSelection = RCC_RTCCLKSOURCE_LSE;
#elif defined (RTC_CLOCK_SOURCE_LSI)
      /* Configure LSI as RTC clock source */
      RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_LSI;
      RCC_OscInitStruct.PLL.PLLState = RCC_PLL_NONE;
      RCC_OscInitStruct.LSIState = RCC_LSI_ON;
      PeriphClkInitStruct.RTCClockSelection = RCC_RTCCLKSOURCE_LSI;
#elif defined (RTC_CLOCK_SOURCE_HSE)
      /* Configure HSE as RTC clock source */
      RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSE;
      RCC_OscInitStruct.PLL.PLLState = RCC_PLL_NONE;
      RCC_OscInitStruct.HSEState = RCC_HSE_BYPASS_PWR;
      /* Ensure that RTC is clocked by 1MHz */
      PeriphClkInitStruct.RTCClockSelection = RCC_RTCCLKSOURCE_HSE_DIV32;
#endif

      /* COnfigure oscillator */
      status = HAL_RCC_OscConfig(&RCC_OscInitStruct);
      if(status == HAL_OK)
      {
        /* Configure RTC clock source */
        PeriphClkInitStruct.PeriphClockSelection = RCC_PERIPHCLK_RTC;
        status = HAL_RCCEx_PeriphCLKConfig(&PeriphClkInitStruct);

        /* Enable RTC Clock */
        if(status == HAL_OK)
        {
          __HAL_RCC_RTC_ENABLE();
        }
      }
    }

    /* If RTC Clock configuration is ok */
    if (status == HAL_OK)
    {
      /* The time base is defined to have highest synchronous prescaler but keeping 
         a 1Hz RTC frequency. */
      hRTC_Handle.Instance = RTC;
      hRTC_Handle.Init.HourFormat = RTC_HOURFORMAT_24;
      hRTC_Handle.Init.AsynchPrediv = RTC_ASYNCH_PREDIV;
      hRTC_Handle.Init.SynchPrediv = RTC_SYNCH_PREDIV;
      hRTC_Handle.Init.OutPut = RTC_OUTPUT_DISABLE;
      hRTC_Handle.Init.OutPutPolarity = RTC_OUTPUT_POLARITY_HIGH;
      hRTC_Handle.Init.OutPutType = RTC_OUTPUT_TYPE_OPENDRAIN;
      status = HAL_RTC_Init(&hRTC_Handle);
    }

    /* HAL RTC Init is ok & calendar has never been initialized */
    if((status == HAL_OK)  && (__HAL_RTC_GET_FLAG(&hRTC_Handle, RTC_FLAG_INITS) == 0x00u))
    {
      time.Hours = 0x00u;
      time.Minutes = 0x00u;
      time.Seconds = 0x00u;
      time.TimeFormat = RTC_HOURFORMAT12_PM;
      time.SubSeconds = 0x00u;
      time.SecondFraction = 0x00u;
      time.DayLightSaving = RTC_DAYLIGHTSAVING_NONE;
      time.StoreOperation = RTC_STOREOPERATION_RESET;
      status = HAL_RTC_SetTime(&hRTC_Handle, &time, RTC_FORMAT_BCD);
      if(status == HAL_OK)
      {
        date.WeekDay = RTC_WEEKDAY_MONDAY;
        date.Date = 0x01u;
        date.Month = RTC_MONTH_JANUARY;
        date.Year = 0x01u;
        status = HAL_RTC_SetDate(&hRTC_Handle, &date, RTC_FORMAT_BCD);
      }
    }

    /* If RTC calendar is initialized */
    if (status == HAL_OK)
    {
      alarm.AlarmTime.Hours = 0x00u;
      alarm.AlarmTime.Minutes = 0x00u;
      alarm.AlarmTime.Seconds = 0x00u;
      alarm.AlarmTime.TimeFormat = RTC_HOURFORMAT12_PM;
      alarm.AlarmTime.SubSeconds = (RTC_SYNCH_PREDIV / (1000 / (uint32_t)uwTickFreq));
      alarm.AlarmTime.SecondFraction = 0x00u;
      alarm.AlarmTime.DayLightSaving = RTC_DAYLIGHTSAVING_NONE;
      alarm.AlarmTime.StoreOperation = RTC_STOREOPERATION_RESET;
      alarm.AlarmMask = RTC_ALARMMASK_ALL;

      /* Depending on input frequency select Subsecond mask */
      if (uwTickFreq == HAL_TICK_FREQ_1KHZ)
      {
        alarm.AlarmSubSecondMask = RTC_ALARMSUBSECONDMASK_SS14_5;
      }
      else if (uwTickFreq == HAL_TICK_FREQ_100HZ)
      {
        alarm.AlarmSubSecondMask = RTC_ALARMSUBSECONDMASK_SS14_9;
      }
      else
      {
#if defined (RTC_CLOCK_SOURCE_HSE)
        /* When RTCCLK = 1 MHz, need to mask Subsecond register bit 12 to 14
          to have 10 Hhz interrupt */
        alarm.AlarmSubSecondMask = RTC_ALARMSUBSECONDMASK_SS14_12;
#else
        /* When RTCCLK is around 32 kHz, need to mask Subsecond register bit 12 to 11
          to have 10 Hhz interrupt */
        alarm.AlarmSubSecondMask = RTC_ALARMSUBSECONDMASK_SS14_11;
#endif
      }
      alarm.BinaryAutoClr = RTC_ALARMSUBSECONDBIN_AUTOCLR_NO;
      alarm.AlarmDateWeekDaySel = RTC_ALARMDATEWEEKDAYSEL_DATE;
      alarm.AlarmDateWeekDay = RTC_WEEKDAY_MONDAY;
      alarm.Alarm = RTC_ALARM_A;
      status = HAL_RTC_SetAlarm_IT(&hRTC_Handle, &alarm, RTC_FORMAT_BCD);
      if(status == HAL_OK)
      {
        /* Enable the RTC global Interrupt */
#if defined(CORE_CM0PLUS)
        HAL_NVIC_EnableIRQ(RTC_LSECSS_IRQn);
#else
        HAL_NVIC_EnableIRQ(RTC_Alarm_IRQn);
#endif

        /* Configure the SysTick IRQ priority */
        if (TickPriority < (1UL << __NVIC_PRIO_BITS))
        {
#if defined(CORE_CM0PLUS)
          HAL_NVIC_SetPriority(RTC_LSECSS_IRQn, TickPriority, 0U);
#else
          HAL_NVIC_SetPriority(RTC_Alarm_IRQn, TickPriority, 0U);
#endif
          uwTickPrio = TickPriority;
        }
        else
        {
          status = HAL_ERROR;
        }
      }
    }
  }
  else
  {
    status = HAL_ERROR;
  }
  return status;
}

/**
  * @brief  Suspend Tick increment.
  * @note   Disable the tick increment by disabling RTC_ALRA interrupt.
  * @retval None
  */
void HAL_SuspendTick(void)
{
  /* Disable the write protection for RTC registers */
  __HAL_RTC_WRITEPROTECTION_DISABLE(&hRTC_Handle);
  /* Disable ALARM A Interrupt */
  __HAL_RTC_ALARM_DISABLE_IT(&hRTC_Handle, RTC_IT_ALRA);
  /* Enable the write protection for RTC registers */
  __HAL_RTC_WRITEPROTECTION_ENABLE(&hRTC_Handle);
}

/**
  * @brief  Resume Tick increment.
  * @note   Enable the tick increment by Enabling RTC_ALRA interrupt.
  * @retval None
  */
void HAL_ResumeTick(void)
{
  /* Disable the write protection for RTC registers */
  __HAL_RTC_WRITEPROTECTION_DISABLE(&hRTC_Handle);
  /* Enable ALARM A interrupt */
  __HAL_RTC_ALARM_ENABLE_IT(&hRTC_Handle, RTC_IT_ALRA);
  /* Enable the write protection for RTC registers */
  __HAL_RTC_WRITEPROTECTION_ENABLE(&hRTC_Handle);
}

/**
  * @brief  Alarm Timer Event Callback in non blocking mode
  * @note   This function is called  when RTC Alarm takes place, inside
  *         HAL_RTC_AlarmIRQHandler(). It makes a direct call to HAL_IncTick() to increment
  *         a global variable "uwTick" used as application time base.
  * @param  hrtc : RTC handle
  * @retval None
  */
void HAL_RTC_AlarmAEventCallback(RTC_HandleTypeDef *hrtc)
{
  HAL_IncTick();
}

/**
  * @brief  This function handles Alarm interrupt request.
  * @retval None
  */
#if defined(CORE_CM0PLUS)
void RTC_LSECSS_IRQHandler(void)
#else
void RTC_Alarm_IRQHandler(void)
#endif
{
  HAL_RTC_AlarmIRQHandler(&hRTC_Handle);
}

/**
  * @}
  */

/**
  * @}
  */



/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
