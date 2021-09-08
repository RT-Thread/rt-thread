/**
  ******************************************************************************
  * @file    stm32g0xx_hal_timebase_rtc_wakeup_template.c
  * @author  MCD Application Team
  * @brief   HAL time base based on the hardware RTC_WAKEUP Template.
  *
  *          This file overrides the native HAL time base functions (defined as weak)
  *          to use the RTC WAKEUP for the time base generation:
  *           + Initializes the RTC peripheral and configures the wakeup timer to be
  *             incremented each 1ms
  *           + The wakeup feature is configured to assert an interrupt each 1ms
  *           + HAL_IncTick is called inside the HAL_RTCEx_WakeUpTimerEventCallback
  *           + HSE (default), LSE or LSI can be selected as RTC clock source
 @verbatim
  ==============================================================================
                        ##### How to use this driver #####
  ==============================================================================
    [..]
    This file must be copied to the application folder and modified as follows:
    (#) Rename it to 'stm32g0xx_hal_timebase_rtc_wakeup.c'
    (#) Add this file and the RTC HAL drivers to your project and uncomment
       HAL_RTC_MODULE_ENABLED define in stm32g0xx_hal_conf.h

    [..]
    (@) HAL RTC alarm and HAL RTC wakeup drivers can’t be used with low power modes:
        The wake up capability of the RTC may be intrusive in case of prior low power mode
        configuration requiring different wake up sources.
        Application/Example behavior is no more guaranteed
    (@) The stm32g0xx_hal_timebase_tim use is recommended for the Applications/Examples
          requiring low power modes

  @endverbatim
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2018 STMicroelectronics. 
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
#include "stm32g0xx_hal.h"
/** @addtogroup STM32G0xx_HAL_Driver
  * @{
  */

/** @defgroup HAL_TimeBase_RTC_WakeUp_Template  HAL TimeBase RTC WakeUp Template
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

#if defined (RTC_CLOCK_SOURCE_LSE)
/* LSE Freq = 32.768 kHz RC */
#define RTC_ASYNCH_PREDIV                   0x7Fu
#define RTC_SYNCH_PREDIV                    0x00FFu
#elif defined (RTC_CLOCK_SOURCE_LSI)
/* LSI Freq = 32 kHz RC  */
#define RTC_ASYNCH_PREDIV                   0x7Fu
#define RTC_SYNCH_PREDIV                    0x00FEu
#elif defined (RTC_CLOCK_SOURCE_HSE)
/* HSE Freq as RTCCLK = 8 MHz / 32 = 250 kHz */
#define RTC_ASYNCH_PREDIV                   0x07u   /* (8 - 1) */
#define RTC_SYNCH_PREDIV                    0x7A11u /* (31250 -1) */
#endif


/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
RTC_HandleTypeDef        hRTC_Handle = {.Init = {0}};

/* Private function prototypes -----------------------------------------------*/
void RTC_TAMP_IRQHandler(void);

/* Private functions ---------------------------------------------------------*/

/**
  * @brief  This function configures the RTC_TAMP as a time base source.
  *         The time source is configured  to have 1ms time base with a dedicated
  *         Tick interrupt priority.
  *         Wakeup Time base = ((RTC_ASYNCH_PREDIV + 1) * (RTC_SYNCH_PREDIV + 1)) / RTC_CLOCK
                             = 1ms
  *         Wakeup Time = WakeupTimebase * WakeUpCounter (0 + 1)
                        = 1 ms
  * @note   This function is called  automatically at the beginning of program after
  *         reset by HAL_Init() or at any time when clock is configured, by HAL_RCC_ClockConfig().
  * @param  TickPriority: Tick interrupt priority.
  * @retval HAL status
  */
HAL_StatusTypeDef HAL_InitTick(uint32_t TickPriority)
{
  HAL_StatusTypeDef status = HAL_OK;
  uint32_t wucounter;
  RCC_OscInitTypeDef        RCC_OscInitStruct = {0};
  RCC_PeriphCLKInitTypeDef  PeriphClkInitStruct = {0};

  /* Check uwTickFreq for MisraC 2012 (even if uwTickFreq is a enum type that don't take the value zero)*/
  if ((uint32_t)uwTickFreq != 0U)
  {
    /* Disable backup domain protection */
    HAL_PWR_EnableBkUpAccess();

    /* Enable RTC APB clock gating */
    __HAL_RCC_RTCAPB_CLK_ENABLE();

    /* Disable the Wake-up Timer */
    __HAL_RTC_WAKEUPTIMER_DISABLE(&hRTC_Handle);
    /* In case of interrupt mode is used, the interrupt source must disabled */ 
    __HAL_RTC_WAKEUPTIMER_DISABLE_IT(&hRTC_Handle,RTC_IT_WUT);
    __HAL_RTC_WAKEUPTIMER_CLEAR_FLAG(&hRTC_Handle,RTC_FLAG_WUTF);

    /* Get RTC clock configuration */
    HAL_RCCEx_GetPeriphCLKConfig(&PeriphClkInitStruct);

    /*In case of RTC clock already enable, make sure it's the good one */
#ifdef RTC_CLOCK_SOURCE_LSE
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
      RCC_OscInitStruct.HSEState = RCC_HSE_ON;
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
    if(status == HAL_OK)
    {
      /* No care of RTC init parameter here. Only needed if RTC is being used
        for other features in same time: calendar, alarm, timestamp, etc... */
      hRTC_Handle.Instance = RTC;
      hRTC_Handle.Init.HourFormat = RTC_HOURFORMAT_24;
      hRTC_Handle.Init.AsynchPrediv = RTC_ASYNCH_PREDIV;
      hRTC_Handle.Init.SynchPrediv = RTC_SYNCH_PREDIV;
      hRTC_Handle.Init.OutPut = RTC_OUTPUT_DISABLE;
      hRTC_Handle.Init.OutPutPolarity = RTC_OUTPUT_POLARITY_HIGH;
      hRTC_Handle.Init.OutPutType = RTC_OUTPUT_TYPE_OPENDRAIN;
      status = HAL_RTC_Init(&hRTC_Handle);

      if(status == HAL_OK)
      {
        /* The time base should be of (uint32_t)uwTickFreq) ms. Tick counter
          is incremented eachtime wakeup time reaches zero. Wakeup timer is
          clocked on RTCCLK divided by 2. So downcounting counter has to be
          set to (RTCCLK / 2) / (1000 / (uint32_t)uwTickFreq)) minus 1 */
#ifdef RTC_CLOCK_SOURCE_LSE
        wucounter = LSE_VALUE;
#elif defined (RTC_CLOCK_SOURCE_LSI)
        wucounter = LSI_VALUE;
#elif defined (RTC_CLOCK_SOURCE_HSE)
        /* HSE input clock to RTC is divided by 32 */
        wucounter = (HSE_VALUE >> 5);
#endif
        wucounter = ((wucounter >> 1) / (1000U / (uint32_t)uwTickFreq)) -1u;
        status = HAL_RTCEx_SetWakeUpTimer_IT(&hRTC_Handle, wucounter, RTC_WAKEUPCLOCK_RTCCLK_DIV2);

        if(status == HAL_OK)
        {
          /* Enable the RTC global Interrupt */

          HAL_NVIC_EnableIRQ(RTC_TAMP_IRQn);

          /* Configure the SysTick IRQ priority */
          if (TickPriority < (1UL << __NVIC_PRIO_BITS))
          {
            HAL_NVIC_SetPriority(RTC_TAMP_IRQn, TickPriority, 0U);
            uwTickPrio = TickPriority;
          }
          else
          {
            status = HAL_ERROR;
          }
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
  * @note   Disable the tick increment by disabling RTC_TAMP interrupt.
  * @retval None
  */
void HAL_SuspendTick(void)
{
  /* Disable the write protection for RTC registers */
  __HAL_RTC_WRITEPROTECTION_DISABLE(&hRTC_Handle);
  /* Disable WAKE UP TIMER Interrupt */
  __HAL_RTC_WAKEUPTIMER_DISABLE_IT(&hRTC_Handle, RTC_IT_WUT);
  /* Enable the write protection for RTC registers */
  __HAL_RTC_WRITEPROTECTION_ENABLE(&hRTC_Handle);
}

/**
  * @brief  Resume Tick increment.
  * @note   Enable the tick increment by Enabling RTC_TAMP interrupt.
  * @retval None
  */
void HAL_ResumeTick(void)
{
  /* Disable the write protection for RTC registers */
  __HAL_RTC_WRITEPROTECTION_DISABLE(&hRTC_Handle);
  /* Enable  WAKE UP TIMER  interrupt */
  __HAL_RTC_WAKEUPTIMER_ENABLE_IT(&hRTC_Handle, RTC_IT_WUT);
  /* Enable the write protection for RTC registers */
  __HAL_RTC_WRITEPROTECTION_ENABLE(&hRTC_Handle);
}

/**
  * @brief  Wake Up Timer Event Callback in non blocking mode
  * @note   This function is called  when RTC_TAMP interrupt took place, inside
  * RTC_TAMP_IRQHandler(). It makes a direct call to HAL_IncTick() to increment
  * a global variable "uwTick" used as application time base.
  * @param  hrtc : RTC handle
  * @retval None
  */
void HAL_RTCEx_WakeUpTimerEventCallback(RTC_HandleTypeDef *hrtc)
{
  HAL_IncTick();
}

/**
  * @brief  This function handles RTC WAKE UP TIMER interrupt request.
  * @retval None
  */
void RTC_TAMP_IRQHandler(void)
{
  HAL_RTCEx_WakeUpTimerIRQHandler(&hRTC_Handle);
}

/**
  * @}
  */

/**
  * @}
  */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
