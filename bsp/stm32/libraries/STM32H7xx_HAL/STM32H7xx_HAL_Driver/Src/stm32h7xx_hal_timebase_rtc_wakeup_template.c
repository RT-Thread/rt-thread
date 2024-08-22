/**
  ******************************************************************************
  * @file    stm32h7xx_hal_timebase_rtc_wakeup_template.c
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
    This file must be copied to the application folder and modified as follows:
    (#) Rename it to 'stm32h7xx_hal_timebase_rtc_wakeup.c'
    (#) Add this file and the RTC HAL drivers to your project and uncomment
       HAL_RTC_MODULE_ENABLED define in stm32h7xx_hal_conf.h

    [..]
    (@) HAL RTC alarm and HAL RTC wakeup drivers can not be used with low power modes:
        The wake up capability of the RTC may be intrusive in case of prior low power mode
        configuration requiring different wake up sources.
        Application/Example behavior is no more guaranteed
    (@) The stm32h7xx_hal_timebase_tim use is recommended for the Applications/Examples
          requiring low power modes

  @endverbatim
  ******************************************************************************
  */

/* Includes ------------------------------------------------------------------*/
#include "stm32h7xx_hal.h"
/** @addtogroup STM32H7xx_HAL_Driver
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
#define RTC_CLOCK_SOURCE_HSE
/* #define RTC_CLOCK_SOURCE_LSE */
/* #define RTC_CLOCK_SOURCE_LSI */

#ifdef RTC_CLOCK_SOURCE_HSE
  #define RTC_ASYNCH_PREDIV       99U
  #define RTC_SYNCH_PREDIV        9U
  #define RCC_RTCCLKSOURCE_1MHZ   ((uint32_t)((uint32_t)RCC_BDCR_RTCSEL | (uint32_t)((HSE_VALUE/1000000U) << 12U)))
#else /* RTC_CLOCK_SOURCE_LSE || RTC_CLOCK_SOURCE_LSI */
  #define RTC_ASYNCH_PREDIV       0U
  #define RTC_SYNCH_PREDIV        31U
#endif /* RTC_CLOCK_SOURCE_HSE */

/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
static RTC_HandleTypeDef        hRTC_Handle;

/* Private function prototypes -----------------------------------------------*/
void RTC_WKUP_IRQHandler(void);

/* Private functions ---------------------------------------------------------*/

/**
  * @brief  This function configures the RTC_WKUP as a time base source.
  *         The time source is configured  to have 1ms time base with a dedicated
  *         Tick interrupt priority.
  *         Wakeup Time base = ((RTC_ASYNCH_PREDIV + 1) * (RTC_SYNCH_PREDIV + 1)) / RTC_CLOCK
                             = 1ms
  *         Wakeup Time = WakeupTimebase * WakeUpCounter (0 + 1)
                        = 1 ms
  * @note   This function is called  automatically at the beginning of program after
  *         reset by HAL_Init() or at any time when clock is configured, by HAL_RCC_ClockConfig().
  * @param  TickPriority Tick interrupt priority.
  * @retval HAL status
  */
HAL_StatusTypeDef HAL_InitTick (uint32_t TickPriority)
{
  __IO uint32_t counter = 0U;

  RCC_OscInitTypeDef        RCC_OscInitStruct;
  RCC_PeriphCLKInitTypeDef  PeriphClkInitStruct;
  HAL_StatusTypeDef     status;

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
  /* Ensure that RTC is clocked by 1MHz */
  PeriphClkInitStruct.RTCClockSelection = RCC_RTCCLKSOURCE_1MHZ;
#else
#error Please select the RTC Clock source
#endif /* RTC_CLOCK_SOURCE_LSE */

  status = HAL_RCC_OscConfig(&RCC_OscInitStruct);
  if (status == HAL_OK)
  {
    PeriphClkInitStruct.PeriphClockSelection = RCC_PERIPHCLK_RTC;
    status = HAL_RCCEx_PeriphCLKConfig(&PeriphClkInitStruct);
  }
  if (status == HAL_OK)
  {
      /* Enable RTC Clock */
      __HAL_RCC_RTC_ENABLE();
      /* The time base should be 1ms
         Time base = ((RTC_ASYNCH_PREDIV + 1) * (RTC_SYNCH_PREDIV + 1)) / RTC_CLOCK
         HSE as RTC clock
           Time base = ((99 + 1) * (9 + 1)) / 1Mhz
                     = 1ms
         LSE as RTC clock
           Time base = ((31 + 1) * (0 + 1)) / 32.768Khz
                     = ~1ms
         LSI as RTC clock
           Time base = ((31 + 1) * (0 + 1)) / 32Khz
                     = 1ms
      */
      hRTC_Handle.Instance = RTC;
      hRTC_Handle.Init.HourFormat = RTC_HOURFORMAT_24;
      hRTC_Handle.Init.AsynchPrediv = RTC_ASYNCH_PREDIV;
      hRTC_Handle.Init.SynchPrediv = RTC_SYNCH_PREDIV;
      hRTC_Handle.Init.OutPut = RTC_OUTPUT_DISABLE;
      hRTC_Handle.Init.OutPutPolarity = RTC_OUTPUT_POLARITY_HIGH;
      hRTC_Handle.Init.OutPutType = RTC_OUTPUT_TYPE_OPENDRAIN;
      status = HAL_RTC_Init(&hRTC_Handle);
  }
  if (status == HAL_OK)
  {
      /* Disable the write protection for RTC registers */
      __HAL_RTC_WRITEPROTECTION_DISABLE(&hRTC_Handle);

      /* Disable the Wake-up Timer */
      __HAL_RTC_WAKEUPTIMER_DISABLE(&hRTC_Handle);

      /* In case of interrupt mode is used, the interrupt source must disabled */
      __HAL_RTC_WAKEUPTIMER_DISABLE_IT(&hRTC_Handle, RTC_IT_WUT);

      /* Wait till RTC WUTWF flag is set  */
#if defined(RTC_ICSR_WUTWF)
      while (READ_BIT(hRTC_Handle.Instance->ICSR, RTC_FLAG_WUTWF) == (uint32_t)RESET)
#else
      while (__HAL_RTC_WAKEUPTIMER_GET_FLAG(&hRTC_Handle, RTC_FLAG_WUTWF) == (uint32_t)RESET)
#endif  /* RTC_ICSR_WUTWF */
      {
        if (counter++ == (SystemCoreClock / 48U))
      {
        status = HAL_ERROR;
      }
    }
  }
  if (status == HAL_OK)
  {
    /* Clear PWR wake up Flag */
    __HAL_PWR_CLEAR_FLAG(PWR_FLAG_WU);

    /* Clear RTC Wake Up timer Flag */
    __HAL_RTC_WAKEUPTIMER_CLEAR_FLAG(&hRTC_Handle, RTC_FLAG_WUTF);

    /* Configure the Wake-up Timer counter */
    hRTC_Handle.Instance->WUTR = (uint32_t)0U;

    /* Clear the Wake-up Timer clock source bits in CR register */
    hRTC_Handle.Instance->CR &= (uint32_t)~RTC_CR_WUCKSEL;

    /* Configure the clock source */
    hRTC_Handle.Instance->CR |= (uint32_t)RTC_WAKEUPCLOCK_CK_SPRE_16BITS;

    /* RTC WakeUpTimer Interrupt Configuration: EXTI configuration */
    __HAL_RTC_WAKEUPTIMER_EXTI_ENABLE_IT();

    __HAL_RTC_WAKEUPTIMER_EXTI_ENABLE_RISING_EDGE();

    /* Configure the Interrupt in the RTC_CR register */
    __HAL_RTC_WAKEUPTIMER_ENABLE_IT(&hRTC_Handle,RTC_IT_WUT);

    /* Enable the Wake-up Timer */
    __HAL_RTC_WAKEUPTIMER_ENABLE(&hRTC_Handle);

    /* Enable the write protection for RTC registers */
    __HAL_RTC_WRITEPROTECTION_ENABLE(&hRTC_Handle);

    /* Enable the RTC global Interrupt */
    HAL_NVIC_EnableIRQ(RTC_WKUP_IRQn);

    /* Configure the SysTick IRQ priority */
    if (TickPriority < (1UL << __NVIC_PRIO_BITS))
    {
      HAL_NVIC_SetPriority(RTC_WKUP_IRQn, TickPriority, 0U);
      uwTickPrio = TickPriority;
    }
    else
    {
      status = HAL_ERROR;
    }
  }
  return status;
}

/**
  * @brief  Suspend Tick increment.
  * @note   Disable the tick increment by disabling RTC_WKUP interrupt.
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
  * @note   Enable the tick increment by Enabling RTC_WKUP interrupt.
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
  * @note   This function is called  when RTC_WKUP interrupt took place, inside
  * RTC_WKUP_IRQHandler(). It makes a direct call to HAL_IncTick() to increment
  * a global variable "uwTick" used as application time base.
  * @param  hrtc RTC handle
  * @retval None
  */
void HAL_RTCEx_WakeUpTimerEventCallback(RTC_HandleTypeDef *hrtc)
{
  /* Prevent unused argument(s) compilation warning */
  UNUSED(hrtc);

  HAL_IncTick();
}

/**
  * @brief  This function handles  WAKE UP TIMER  interrupt request.
  * @retval None
  */
void RTC_WKUP_IRQHandler(void)
{
  HAL_RTCEx_WakeUpTimerIRQHandler(&hRTC_Handle);
}

/**
  * @}
  */

/**
  * @}
  */


