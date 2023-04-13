/*
 * Copyright (c) 2006-2023, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author            Notes
 * 2022-03-04     stevetong459      first version
 * 2022-07-15     Aligagago         add APM32F4 series MCU support
 * 2022-12-26     luobeihai         add APM32F0 series MCU support
 * 2023-03-18     luobeihai         fix RT-Thread Studio compile error bug
 * 2023-03-27     luobeihai         add APM32E1/S1 series MCU support
 */

#include "board.h"
#include <sys/time.h>

#ifdef BSP_USING_ONCHIP_RTC

#define DBG_TAG               "drv.rtc"
#define DBG_LVL               DBG_INFO
#include <rtdbg.h>

#ifndef LSI_VALUE
    #define  LSI_VALUE            ((uint32_t)40000)
#endif
#ifndef LSE_VALUE
    #define  LSE_VALUE            ((uint32_t)32768)
#endif

#define DRV_RTC_TIME_OUT      0xFFFFF

static rt_rtc_dev_t apm32_rtc_dev;
static rt_uint8_t rtc_init_flag = RESET;

/**
 * @brief    This function will initialize the rtc on chip.
 *
 * @return   RT_EOK indicates successful initialize, other value indicates failed;
 */
static rt_err_t apm32_rtc_init(void)
{
    volatile rt_uint32_t counter = 0;

    /* Enable RTC Clock */
#if defined(SOC_SERIES_APM32F1) || defined(SOC_SERIES_APM32E1) || defined(SOC_SERIES_APM32S1)
    RCM_EnableAPB1PeriphClock(RCM_APB1_PERIPH_PMU | RCM_APB1_PERIPH_BAKR);
#elif defined(SOC_SERIES_APM32F0) || defined(SOC_SERIES_APM32F4)
    RCM_EnableAPB1PeriphClock(RCM_APB1_PERIPH_PMU);
#endif

    PMU_EnableBackupAccess();

    /* Config RTC clock */
#ifdef BSP_RTC_USING_LSI
    RCM_EnableLSI();
    while (!RCM_ReadStatusFlag(RCM_FLAG_LSIRDY))
    {
        if (++counter > DRV_RTC_TIME_OUT)
        {
            return -RT_ETIMEOUT;
        }
    }
    RCM_ConfigRTCCLK(RCM_RTCCLK_LSI);
#elif defined(BSP_RTC_USING_LSE)
    RCM_DisableLSI();
    RCM_ConfigLSE(RCM_LSE_OPEN);
    while (!RCM_ReadStatusFlag(RCM_FLAG_LSERDY))
    {
        if (++counter > DRV_RTC_TIME_OUT)
        {
            return -RT_ETIMEOUT;
        }
    }
    RCM_ConfigRTCCLK(RCM_RTCCLK_LSE);
#endif /* BSP_RTC_USING_LSI */

    RCM_EnableRTCCLK();
    RTC_WaitForSynchro();

#if defined(SOC_SERIES_APM32F1) || defined(SOC_SERIES_APM32E1) || defined(SOC_SERIES_APM32S1)
    counter = 0;
    while (!RTC_ReadStatusFlag(RTC_FLAG_OC))
    {
        if (++counter > DRV_RTC_TIME_OUT)
        {
            return -RT_ETIMEOUT;
        }
    }

    RTC_EnableConfigMode();

    RTC_ClearStatusFlag(RTC_FLAG_OVR | RTC_FLAG_ALR | RTC_FLAG_SEC);

#ifdef BSP_RTC_USING_LSI
    RTC_ConfigPrescaler(LSI_VALUE - 1);
#elif defined(BSP_RTC_USING_LSE)
    RTC_ConfigPrescaler(LSE_VALUE - 1);
#endif /* BSP_RTC_USING_LSI */

#elif defined(SOC_SERIES_APM32F4)
    RTC_EnableInit();
    RTC_Config_T rtcConfig;
    RTC_ConfigStructInit(&rtcConfig);
    RTC_Config(&rtcConfig);

#elif defined(SOC_SERIES_APM32F0)
    RTC_EnableInit();
    RTC_Config_T rtcConfig;
    RTC_ConfigStructInit(&rtcConfig);

#ifdef BSP_RTC_USING_LSI
    rtcConfig.AsynchPrediv = 0x63;
    rtcConfig.SynchPrediv  = 0x18F;
#else
    rtcConfig.AsynchPrediv = 0x7F;
    rtcConfig.SynchPrediv  = 0x130;
#endif /* BSP_RTC_USING_LSI */
    RTC_Config(&rtcConfig);

#endif /* SOC_SERIES_APM32F1 || SOC_SERIES_APM32E1 || SOC_SERIES_APM32S1 */

    if (!rtc_init_flag)
    {
        rtc_init_flag = SET;
    }
    return RT_EOK;
}

#if defined(SOC_SERIES_APM32F1) || defined(SOC_SERIES_APM32E1) || defined(SOC_SERIES_APM32S1)
/**
 * @brief    This function will initialize the rtc on chip.
 *
 * @return   RT_EOK indicates successful initialize, other value indicates failed;
 */
static rt_err_t apm32_rtc_get_secs(time_t *sec)
{
    volatile rt_uint32_t counter = 0;

    while (!RTC_ReadStatusFlag(RTC_FLAG_OC))
    {
        if (++counter > DRV_RTC_TIME_OUT)
        {
            return -RT_ETIMEOUT;
        }
    }

    *(time_t *) sec = RTC_ReadCounter();

    return RT_EOK;
}

static rt_err_t apm32_rtc_set_secs(time_t *sec)
{
    volatile rt_uint32_t counter = 0;

    if (!rtc_init_flag)
    {
        apm32_rtc_init();
    }

    while (!RTC_ReadStatusFlag(RTC_FLAG_OC))
    {
        if (++counter > DRV_RTC_TIME_OUT)
        {
            return -RT_ETIMEOUT;
        }
    }

    RTC_ConfigCounter(*(rt_uint32_t *)sec);

    return RT_EOK;
}
#elif defined(SOC_SERIES_APM32F0) || defined(SOC_SERIES_APM32F4)
static rt_err_t apm32_rtc_get_timeval(void *args)
{
    struct timeval *tv = (struct timeval *) args;

#if defined(SOC_SERIES_APM32F0)
    RTC_TIME_T timeConfig;
    RTC_DATE_T dateConfig;
#elif defined(SOC_SERIES_APM32F4)
    RTC_TimeConfig_T timeConfig;
    RTC_DateConfig_T dateConfig;
#endif

    struct tm tm_new = {0};

    RTC_ReadTime(RTC_FORMAT_BIN, &timeConfig);
    RTC_ReadDate(RTC_FORMAT_BIN, &dateConfig);

    tm_new.tm_sec  = timeConfig.seconds;
    tm_new.tm_min  = timeConfig.minutes;
    tm_new.tm_hour = timeConfig.hours;
    tm_new.tm_mday = dateConfig.date;
    tm_new.tm_mon  = dateConfig.month - 1;
    tm_new.tm_year = dateConfig.year + 100;

    tv->tv_sec = timegm(&tm_new);

    return RT_EOK;
}

static rt_err_t set_rtc_time_stamp(time_t time_stamp)
{
#if defined(SOC_SERIES_APM32F0)
    RTC_TIME_T timeConfig;
    RTC_DATE_T dateConfig;
#elif defined(SOC_SERIES_APM32F4)
    RTC_TimeConfig_T timeConfig;
    RTC_DateConfig_T dateConfig;
#endif

    struct tm tm = {0};

    if (!rtc_init_flag)
    {
        apm32_rtc_init();
    }

    gmtime_r(&time_stamp, &tm);
    if (tm.tm_year < 100)
    {
        return -RT_ERROR;
    }

    timeConfig.seconds = tm.tm_sec ;
    timeConfig.minutes = tm.tm_min ;
    timeConfig.hours   = tm.tm_hour;
    dateConfig.date    = tm.tm_mday;
#if defined(SOC_SERIES_APM32F4)
    dateConfig.month   = (RTC_MONTH_T)(tm.tm_mon + 1);
    dateConfig.weekday = (RTC_WEEKDAY_T)(tm.tm_wday + 1);
#else
    dateConfig.month   = tm.tm_mon + 1 ;
    dateConfig.weekday = tm.tm_wday + 1;
#endif
    dateConfig.year    = tm.tm_year - 100;

    RTC_ConfigTime(RTC_FORMAT_BIN, &timeConfig);
    RTC_ConfigDate(RTC_FORMAT_BIN, &dateConfig);

    /* wait for set time completed */
    for (int i = 0; i < 0xFFFF; i++);

    return RT_EOK;
}

/**
 * @brief    This function will initialize the rtc on chip.
 *
 * @return   RT_EOK indicates successful initialize, other value indicates failed;
 */
static rt_err_t apm32_rtc_get_secs(void *args)
{
    struct timeval tv;
    apm32_rtc_get_timeval(&tv);
    *(rt_uint32_t *) args = tv.tv_sec;

    return RT_EOK;
}

static rt_err_t apm32_rtc_set_secs(void *args)
{
    rt_err_t result = RT_EOK;

    if (set_rtc_time_stamp(*(rt_uint32_t *)args))
    {
        result = -RT_ERROR;
    }

    return result;
}
#endif /* SOC_SERIES_APM32F1 || SOC_SERIES_APM32E1 || SOC_SERIES_APM32S1 */

static const struct rt_rtc_ops apm32_rtc_ops =
{
    apm32_rtc_init,
    apm32_rtc_get_secs,
    apm32_rtc_set_secs,
    RT_NULL,
    RT_NULL,
#if defined(SOC_SERIES_APM32F0) || defined(SOC_SERIES_APM32F4)
    apm32_rtc_get_timeval,
#else
    RT_NULL,
#endif
    RT_NULL,
};

/**
 * @brief    RTC initialization function.
 *
 * @return   RT_EOK indicates successful initialization, other value indicates failed;
 */
static int rt_hw_rtc_init(void)
{
    rt_err_t result = RT_EOK;

    apm32_rtc_dev.ops = &apm32_rtc_ops;

    if (rt_hw_rtc_register(&apm32_rtc_dev, "rtc", RT_DEVICE_FLAG_RDWR, RT_NULL) != RT_EOK)
    {
        LOG_E("rtc init failed");
        result = -RT_ERROR;
    }
    else
    {
        LOG_D("rtc init success");
    }

    return result;
}
INIT_DEVICE_EXPORT(rt_hw_rtc_init);

#endif /* BSP_USING_ONCHIP_RTC */
