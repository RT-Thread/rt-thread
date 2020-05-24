/*
 * Copyright (c) 2006-2018, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author          Notes
 * 2019-05-06     Zero-Free       first version
 * 2020-04-08     Sunwancn        ports stm32 all
 */

#include <rtthread.h>

#if defined(RT_USING_PM)

#include <drv_pmhw.h>
#ifdef SOC_SERIES_STM32F1
#include <stm32f1xx_ll_rtc.h>
#endif /* SOC_SERIES_STM32F1 */

#if defined(RT_PM_TIM_USING_LPTIM)

static LPTIM_HandleTypeDef LptimHandle = {0};
static rt_uint32_t LPTIM1_clk_freq;

void LPTIM1_IRQHandler(void)
{
    HAL_LPTIM_IRQHandler(&LptimHandle);
}

#else

/* -- PM timer use RTC -- */
static RTC_HandleTypeDef RtcHandle = {0};
static rt_uint32_t RTC_clk_freq;

#if defined(RT_PM_TIM_USING_RTC_ALARM_SSR)

static RTC_AlarmTypeDef RtcAlarm = {0};
static RTC_TimeTypeDef Last_time = {0};

#elif defined(RT_PM_TIM_USING_RTC_ALARM_F1)

static rt_uint32_t Last_timecounter = 0;

#elif defined(RT_PM_TIM_USING_RTC_WAKEUPTIM_NOREAD)

static rt_uint32_t Wakeup_ticks = 0;

#else

static RTC_TimeTypeDef Last_time = {0};

#endif /* defined(RT_PM_TIM_USING_RTC_ALARM_SSR) */

/**
  * @brief This function handles RTC Interrupt through EXTI.
  */
#if defined(SOC_SERIES_STM32F0) || defined(SOC_SERIES_STM32L0)

void RTC_IRQHandler(void)
{
    HAL_RTC_AlarmIRQHandler(&RtcHandle);
#if defined(RTC_CR_WUTIE)
    HAL_RTCEx_WakeUpTimerIRQHandler(&RtcHandle);
#endif
}

#elif defined(SOC_SERIES_STM32G0)

void RTC_TAMP_IRQHandler(void)
{
    HAL_RTC_AlarmIRQHandler(&RtcHandle);
    HAL_RTCEx_WakeUpTimerIRQHandler(&RtcHandle);
}

#elif defined(RT_PM_TIM_USING_RTC_WAKEUPTIM)

void RTC_WKUP_IRQHandler(void)
{
    HAL_RTCEx_WakeUpTimerIRQHandler(&RtcHandle);
}

#else

void RTC_Alarm_IRQHandler(void)
{
    HAL_RTC_AlarmIRQHandler(&RtcHandle);
}

#endif /* defined(SOC_SERIES_STM32F0) */
/* end -- PM timer use RTC -- */

#endif /* defined(RT_PM_TIM_USING_LPTIM) */

#if defined(SOC_SERIES_STM32F2) || defined(SOC_SERIES_STM32F4) || defined(SOC_SERIES_STM32F7)
static rt_uint32_t get_rtc_clk_freq(void)
{
    return ((rt_uint32_t)(RCC->BDCR & RCC_BDCR_RTCSEL) == (rt_uint32_t)RCC_BDCR_RTCSEL_0) ? 32768U : 32000U;
}
#endif

/**
 * This function initialize the LPTIM or RTC
 */
RT_WEAK int stm32_pm_timer_init(void)
{
#ifdef RT_PM_TIM_USING_LPTIM
    LptimHandle.Instance = LPTIM1;
    LptimHandle.Init.Clock.Source = LPTIM_CLOCKSOURCE_APBCLOCK_LPOSC;
    LptimHandle.Init.Clock.Prescaler = LPTIM_PRESCALER_DIV32;
    LptimHandle.Init.Trigger.Source = LPTIM_TRIGSOURCE_SOFTWARE;
    LptimHandle.Init.OutputPolarity = LPTIM_OUTPUTPOLARITY_HIGH;
    LptimHandle.Init.UpdateMode = LPTIM_UPDATE_IMMEDIATE;
    LptimHandle.Init.CounterSource = LPTIM_COUNTERSOURCE_INTERNAL;
    if (HAL_LPTIM_Init(&LptimHandle) != HAL_OK)
    {
        return -1;
    }

    NVIC_ClearPendingIRQ(LPTIM1_IRQn);
    NVIC_SetPriority(LPTIM1_IRQn, 0);
    NVIC_EnableIRQ(LPTIM1_IRQn);

    return 0;
#else
    /* Initialize RTC */
    rt_uint32_t div = 1000U;

    if (RTC_clk_freq == 32768U)
        div = 1024U;

    RtcHandle.Instance = RTC;

#if defined(RT_PM_TIM_USING_RTC_ALARM_F1)
    RtcHandle.Init.AsynchPrediv = RTC_clk_freq / div - 1U;
    RtcHandle.Init.OutPut = RTC_OUTPUTSOURCE_NONE;
#else
  #if defined(RT_PM_TIM_USING_RTC_WAKEUPTIM_NOSSR)
    RtcHandle.Init.AsynchPrediv = RTC_clk_freq / div - 1U;
    RtcHandle.Init.SynchPrediv = 0;
  #elif defined(RT_PM_TIM_USING_RTC_WAKEUPTIM_NOREAD)
    (void)div;
    if (RTC_clk_freq == 32768U)
    {
        RtcHandle.Init.AsynchPrediv = RTC_clk_freq / 128U - 1U;
        RtcHandle.Init.SynchPrediv = 127U;
    }
    else
    {
        RtcHandle.Init.AsynchPrediv = RTC_clk_freq / 125U - 1U;
        RtcHandle.Init.SynchPrediv = 124U;
    }
  #else
    RtcHandle.Init.SynchPrediv = div - 1U;
    RtcHandle.Init.AsynchPrediv = RTC_clk_freq / div - 1U;
    RtcHandle.Init.SynchPrediv = RTC_clk_freq / (RtcHandle.Init.AsynchPrediv + 1U) - 1U;
  #endif
    RtcHandle.Init.HourFormat = RTC_HOURFORMAT_24;
    RtcHandle.Init.OutPut = RTC_OUTPUT_DISABLE;
    RtcHandle.Init.OutPutPolarity = RTC_OUTPUT_POLARITY_HIGH;
    RtcHandle.Init.OutPutType = RTC_OUTPUT_TYPE_OPENDRAIN;
#endif /* defined(RT_PM_TIM_USING_RTC_ALARM_F1) */

    if (HAL_RTC_Init(&RtcHandle) != HAL_OK)
    {
        return -1;
    }

#if defined(RT_PM_TIM_USING_RTC_ALARM_SSR)
    /* Enable the Alarm A */
    RtcAlarm.AlarmTime.Hours = 0x0;
    RtcAlarm.AlarmTime.Minutes = 0x0;
    RtcAlarm.AlarmTime.Seconds = 0x0;
    RtcAlarm.AlarmTime.SubSeconds = 0x0;
    RtcAlarm.AlarmTime.DayLightSaving = RTC_DAYLIGHTSAVING_NONE;
    RtcAlarm.AlarmTime.StoreOperation = RTC_STOREOPERATION_RESET;
    RtcAlarm.AlarmMask = RTC_ALARMMASK_DATEWEEKDAY;
    RtcAlarm.AlarmSubSecondMask = RTC_ALARMSUBSECONDMASK_NONE;
    RtcAlarm.AlarmDateWeekDaySel = RTC_ALARMDATEWEEKDAYSEL_DATE;
    RtcAlarm.AlarmDateWeekDay = 0x1;
    RtcAlarm.Alarm = RTC_ALARM_A;
    if (HAL_RTC_SetAlarm(&RtcHandle, &RtcAlarm, RTC_FORMAT_BCD) != HAL_OK)
    {
        return -1;
    }
#endif /* defined(RT_PM_TIM_USING_RTC_ALARM_SSR) */

#if defined(SOC_SERIES_STM32F0)
    NVIC_ClearPendingIRQ(RTC_IRQn);
    NVIC_SetPriority(RTC_IRQn, 0);
    NVIC_EnableIRQ(RTC_IRQn);
#elif defined(SOC_SERIES_STM32G0)
    NVIC_ClearPendingIRQ(RTC_TAMP_IRQn);
    NVIC_SetPriority(RTC_TAMP_IRQn, 0);
    NVIC_EnableIRQ(RTC_TAMP_IRQn);
#elif defined(RT_PM_TIM_USING_RTC_WAKEUPTIM)
    NVIC_ClearPendingIRQ(RTC_WKUP_IRQn);
    NVIC_SetPriority(RTC_WKUP_IRQn, 0);
    NVIC_EnableIRQ(RTC_WKUP_IRQn);
#else
    NVIC_ClearPendingIRQ(RTC_Alarm_IRQn);
    NVIC_SetPriority(RTC_Alarm_IRQn, 0);
    NVIC_EnableIRQ(RTC_Alarm_IRQn);
#endif /* defined(SOC_SERIES_STM32F0) */

    return 0;
#endif /* ! RT_PM_TIM_USING_LPTIM */
}

/**
 * This function initialize the PM hwtim
 */
int stm32_pmtim_init(void)
{
#ifdef RT_PM_TIM_USING_LPTIM
    LptimHandle.Instance = LPTIM1;
    LPTIM1_clk_freq = HAL_RCCEx_GetPeriphCLKFreq(RCC_PERIPHCLK_LPTIM1);
#else
    RtcHandle.Instance = RTC;
  #if defined(SOC_SERIES_STM32F2) || defined(SOC_SERIES_STM32F4) || defined(SOC_SERIES_STM32F7)
    RTC_clk_freq = get_rtc_clk_freq();
  #else
    RTC_clk_freq = HAL_RCCEx_GetPeriphCLKFreq(RCC_PERIPHCLK_RTC);
  #endif
#endif
    return stm32_pm_timer_init();
}
INIT_DEVICE_EXPORT(stm32_pmtim_init);

#ifdef BSP_USING_ONCHIP_RTC
/**
 * This function re-initialize the RTC on app initialization
 */
int stm32_rtc_reinit(void)
{
    return stm32_pm_timer_init();
}
INIT_APP_EXPORT(stm32_rtc_reinit);
#endif /* BSP_USING_ONCHIP_RTC */

/**
 * This function get the RTC time
 *
 * To be able to read the RTC calendar register when the APB1 clock frequency is less than
 * seven times the RTC clock frequency (7*RTCLCK), the software must read the calendar time
 * and date registers twice. If the second read of the RTC_TR gives the same result as the
 * first read, this ensures that the data is correct. Otherwise a third read access must be done.
 *
 * @return None
 */
#if !(defined(RT_PM_TIM_USING_LPTIM) || defined(SOC_SERIES_STM32F1) || defined(RT_PM_TIM_USING_RTC_WAKEUPTIM_NOREAD))
static void get_rtc_time(RTC_TimeTypeDef *time)
{
    rt_uint32_t st, datetmpreg;

    HAL_RTC_GetTime(&RtcHandle, time, RTC_FORMAT_BIN);
    datetmpreg = RTC->DR;
    if (HAL_RCC_GetPCLK1Freq() < RTC_clk_freq * 7U)
    {
#if defined(RTC_SSR_SS)
        st = time->SubSeconds;
#else
        st = time->Seconds;
#endif
        HAL_RTC_GetTime(&RtcHandle, time, RTC_FORMAT_BIN);
        datetmpreg = RTC->DR;
#if defined(RTC_SSR_SS)
        if (st != time->SubSeconds)
#else
        if (st != time->Seconds)
#endif
        {
            HAL_RTC_GetTime(&RtcHandle, time, RTC_FORMAT_BIN);
            datetmpreg = RTC->DR;
        }
    }
    (void)datetmpreg;
}
#endif

/**
 * This function get current count value of LPTIM or RTC
 *
 * @return the count vlaue
 */
rt_uint32_t stm32_pmtim_get_current_tick(void)
{
#if defined(RT_PM_TIM_USING_LPTIM)

    return HAL_LPTIM_ReadCounter(&LptimHandle);

#elif defined(RT_PM_TIM_USING_RTC_ALARM_F1)

    return LL_RTC_TIME_Get(RTC) - Last_timecounter;

#elif defined(RT_PM_TIM_USING_RTC_WAKEUPTIM_NOREAD)

    return Wakeup_ticks;

#elif defined(RT_PM_TIM_USING_RTC_WAKEUPTIM_NOSSR)

    /* No subsecond
     * Actual seconds are (AsynchPrediv + 1)/((AsynchPrediv_1S + 1)*(SynchPrediv_1S + 1)) of the original
     */
    RTC_TimeTypeDef cur_time = {0};
    rt_uint32_t seconds;
    rt_uint32_t lastseconds = Last_time.Hours * 3600U + Last_time.Minutes * 60U + Last_time.Seconds;

    get_rtc_time(&cur_time);

    seconds = cur_time.Hours * 3600U + cur_time.Minutes * 60U + cur_time.Seconds;
    if (seconds < lastseconds)
        seconds += 24U * 3600U - lastseconds;
    else
        seconds -= lastseconds;

    /* Convert to wakeup timer tick */
    return seconds * (((RTC->PRER & RTC_PRER_PREDIV_A) >> RTC_PRER_PREDIV_A_Pos) + 1U) \
           * ((RTC->PRER & RTC_PRER_PREDIV_S) + 1U) / 16U;

#else

    /* Can't read the wakeuptime counter, then read the subsecond to calculating the elapsed time */
    RTC_TimeTypeDef cur_time = {0};
    rt_uint32_t seconds, lastseconds;
    rt_int32_t subseconds;

    get_rtc_time(&cur_time);

    seconds = cur_time.Hours * 3600U + cur_time.Minutes * 60U + cur_time.Seconds;
    lastseconds = Last_time.Hours * 3600U + Last_time.Minutes * 60U + Last_time.Seconds;
    if (seconds < lastseconds)
        seconds = 24U * 3600U + seconds - lastseconds;
    else
        seconds = seconds - lastseconds;

    /* Subsecond is count down */
    subseconds = (rt_int32_t)Last_time.SubSeconds - (rt_int32_t)cur_time.SubSeconds;
    subseconds += seconds * (Last_time.SecondFraction + 1U);
#ifdef RT_PM_TIM_USING_RTC_WAKEUPTIM_SSR
    /* Convert to wakeup timer tick */
    subseconds = subseconds * (((RTC->PRER & RTC_PRER_PREDIV_A) >> RTC_PRER_PREDIV_A_Pos) + 1U) / 16U;
#endif /* RT_PM_TIM_USING_RTC_WAKEUPTIM_SSR */

    return (rt_uint32_t)subseconds;

#endif
}

/**
 * This function get the count clock frequency of LPTIM or RTC
 *
 * @return the count clock frequency in Hz
 */
RT_WEAK rt_uint32_t stm32_pmtim_get_countfreq(void)
{
#if defined(RT_PM_TIM_USING_LPTIM)
    return LPTIM1_clk_freq >> ((LPTIM1->CFGR & LPTIM_CFGR_PRESC) >> LPTIM_CFGR_PRESC_Pos);
#elif defined(RT_PM_TIM_USING_RTC_ALARM_SSR)
    return RTC_clk_freq / (((RTC->PRER & RTC_PRER_PREDIV_A) >> RTC_PRER_PREDIV_A_Pos) + 1U);
#elif defined(RT_PM_TIM_USING_RTC_ALARM_F1)
    return RTC_clk_freq / (RTC->PRLL + 1U);
#else
    return RTC_clk_freq / 16U;
#endif /* defined(RT_PM_TIM_USING_LPTIM) */
}

/**
 * This function get the max value that LPTIM or RTC can count
 *
 * @return the max count
 */
rt_uint32_t stm32_pmtim_get_tick_max(void)
{
#if defined(RT_PM_TIM_USING_LPTIM) || defined(RT_PM_TIM_USING_RTC_WAKEUPTIM)
    return (0xFFFF);
#elif defined(RT_PM_TIM_USING_RTC_ALARM_F1)
    return (0xFFFFFF);
#else
    return 24U * 3600U * (((RTC->PRER & RTC_PRER_PREDIV_S) >> RTC_PRER_PREDIV_S_Pos) + 1U) - 1U;
#endif
}

/**
 * This function start LPTIM or RTC with reload value
 *
 * @param reload The value that LPTIM count down from
 *
 * @return RT_EOK
 */
rt_err_t stm32_pmtim_start(rt_uint32_t reload)
{
#if defined(RT_PM_TIM_USING_LPTIM)

    HAL_LPTIM_TimeOut_Start_IT(&LptimHandle, 0xFFFF, reload);

#elif defined(RT_PM_TIM_USING_RTC_ALARM_F1)

    /* Set the alarm counter and enable wakeup from stop mode */
    Last_timecounter = LL_RTC_TIME_Get(RTC);
    __HAL_LOCK(&RtcHandle);
    RtcHandle.State = HAL_RTC_STATE_BUSY;
    LL_RTC_ALARM_SetCounter(RTC, Last_timecounter + reload);
    __HAL_RTC_ALARM_CLEAR_FLAG(&RtcHandle, RTC_FLAG_ALRAF);
    __HAL_RTC_ALARM_ENABLE_IT(&RtcHandle, RTC_IT_ALRA);
    __HAL_RTC_ALARM_EXTI_ENABLE_IT();
    __HAL_RTC_ALARM_EXTI_ENABLE_RISING_EDGE();
    RtcHandle.State = HAL_RTC_STATE_READY;
    __HAL_UNLOCK(&RtcHandle);

#elif defined(RT_PM_TIM_USING_RTC_ALARM_SSR)

    rt_uint32_t seconds = 0;
    rt_uint32_t minutes = 0;
    rt_uint32_t hours = 0;
    rt_int32_t timeout = 0;

    get_rtc_time(&Last_time);

    hours = Last_time.Hours;
    seconds = Last_time.Seconds;
    minutes = Last_time.Minutes;

    seconds += reload / (Last_time.SecondFraction + 1U);
    reload = reload % (Last_time.SecondFraction + 1U);

    /* Subsecond is count down */
    timeout = (rt_int32_t)Last_time.SubSeconds - (rt_int32_t)reload;
    if (timeout < 0)
    {
        timeout += Last_time.SecondFraction + 1;
        seconds ++;
    }

    hours += seconds / 3600U;
    seconds = seconds % 3600U;
    if (hours >= 24U)
        hours -= 24U;
    minutes += seconds / 60U;
    seconds = seconds % 60U;
    if (minutes >= 60U)
        minutes -= 60U;

    RtcAlarm.AlarmTime.Seconds = seconds;
    RtcAlarm.AlarmTime.Minutes = minutes;
    RtcAlarm.AlarmTime.Hours = hours;
    RtcAlarm.AlarmTime.SubSeconds = (rt_uint32_t)timeout;

    HAL_RTC_DeactivateAlarm(&RtcHandle, RTC_ALARM_A);
    HAL_RTC_SetAlarm_IT(&RtcHandle, &RtcAlarm, RTC_FORMAT_BIN);

#else

    /* PM_USING_RTC_WAKEUPTIM */
    HAL_RTCEx_SetWakeUpTimer_IT(&RtcHandle, reload, RTC_WAKEUPCLOCK_RTCCLK_DIV16);
  #if defined(RT_PM_TIM_USING_RTC_WAKEUPTIM_NOREAD)
    Wakeup_ticks = reload;
  #else
    get_rtc_time(&Last_time);
  #endif

#endif /* defined(RT_PM_TIM_USING_LPTIM) */

    return (RT_EOK);
}

/**
 * This function stop LPTIM or RTC
 */
void stm32_pmtim_stop(void)
{
#if defined(RT_PM_TIM_USING_LPTIM)

    rt_uint32_t _ier;

    _ier = LptimHandle.Instance->IER;
    LptimHandle.Instance->ICR = LptimHandle.Instance->ISR & _ier;

#elif defined(RT_PM_TIM_USING_RTC_WAKEUPTIM)

    __HAL_RTC_WAKEUPTIMER_DISABLE_IT(&RtcHandle, RTC_IT_WUT);

#else

    /* RT_PM_TIM_USING_RTC_ALARM */
    __HAL_RTC_ALARM_DISABLE_IT(&RtcHandle, RTC_IT_ALRA);

#endif /* defined(RT_PM_TIM_USING_LPTIM) */
}

#endif /* defined(RT_USING_PM) */
