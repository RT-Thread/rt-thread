/*
 * Copyright (c) 2006-2025, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date         Author        Notes
 * 2018-12-04   balanceTWK    first version
 * 2020-10-14   Dozingfiretruck Porting for stm32wbxx
 * 2021-02-05   Meco Man      fix the problem of mixing local time and UTC time
 * 2021-07-05   iysheng       implement RTC framework V2.0
 */

#include "board.h"
#include <rtdevice.h>
#include <sys/time.h>

#ifdef BSP_USING_ONCHIP_RTC

#ifndef RTC_BKP_DR1
#define RTC_BKP_DR1 RT_NULL
#endif

//#define DRV_DEBUG
#define LOG_TAG             "drv.rtc"
#include <drv_log.h>

#define BKUP_REG_DATA 0xA5A5

static RTC_HandleTypeDef RTC_Handler;

RT_WEAK uint32_t HAL_RTCEx_BKUPRead(RTC_HandleTypeDef *hrtc, uint32_t BackupRegister)
{
    return (~BKUP_REG_DATA);
}

RT_WEAK void HAL_RTCEx_BKUPWrite(RTC_HandleTypeDef *hrtc, uint32_t BackupRegister, uint32_t Data)
{
    return;
}

static rt_err_t stm32_rtc_get_timeval(struct timeval *tv)
{
    RTC_TimeTypeDef RTC_TimeStruct = {0};
    RTC_DateTypeDef RTC_DateStruct = {0};
    struct tm tm_new = {0};

    HAL_RTC_GetTime(&RTC_Handler, &RTC_TimeStruct, RTC_FORMAT_BIN);
    HAL_RTC_GetDate(&RTC_Handler, &RTC_DateStruct, RTC_FORMAT_BIN);

    tm_new.tm_sec  = RTC_TimeStruct.Seconds;
    tm_new.tm_min  = RTC_TimeStruct.Minutes;
    tm_new.tm_hour = RTC_TimeStruct.Hours;
    tm_new.tm_mday = RTC_DateStruct.Date;
    tm_new.tm_mon  = RTC_DateStruct.Month - 1;
    tm_new.tm_year = RTC_DateStruct.Year + 100;

    tv->tv_sec = timegm(&tm_new);

#if defined(SOC_SERIES_STM32H7)
    tv->tv_usec = (255.0 - RTC_TimeStruct.SubSeconds * 1.0) / 256.0 * 1000.0 * 1000.0;
#endif

    return RT_EOK;
}

static rt_err_t set_rtc_time_stamp(time_t time_stamp)
{
    RTC_TimeTypeDef RTC_TimeStruct = {0};
    RTC_DateTypeDef RTC_DateStruct = {0};
    struct tm tm = {0};

    gmtime_r(&time_stamp, &tm);
    if (tm.tm_year < 100)
    {
        return -RT_ERROR;
    }

    RTC_TimeStruct.Seconds = tm.tm_sec ;
    RTC_TimeStruct.Minutes = tm.tm_min ;
    RTC_TimeStruct.Hours   = tm.tm_hour;
    RTC_DateStruct.Date    = tm.tm_mday;
    RTC_DateStruct.Month   = tm.tm_mon + 1 ;
    RTC_DateStruct.Year    = tm.tm_year - 100;
    RTC_DateStruct.WeekDay = tm.tm_wday + 1;

    if (HAL_RTC_SetTime(&RTC_Handler, &RTC_TimeStruct, RTC_FORMAT_BIN) != HAL_OK)
    {
        return -RT_ERROR;
    }
    if (HAL_RTC_SetDate(&RTC_Handler, &RTC_DateStruct, RTC_FORMAT_BIN) != HAL_OK)
    {
        return -RT_ERROR;
    }

    LOG_D("set rtc time.");
    HAL_RTCEx_BKUPWrite(&RTC_Handler, RTC_BKP_DR1, BKUP_REG_DATA);

#ifdef SOC_SERIES_STM32F1
    /* F1 series does't save year/month/date datas. so keep those datas to bkp reg */
    HAL_RTCEx_BKUPWrite(&RTC_Handler, RTC_BKP_DR2, RTC_DateStruct.Year);
    HAL_RTCEx_BKUPWrite(&RTC_Handler, RTC_BKP_DR3, RTC_DateStruct.Month);
    HAL_RTCEx_BKUPWrite(&RTC_Handler, RTC_BKP_DR4, RTC_DateStruct.Date);
    HAL_RTCEx_BKUPWrite(&RTC_Handler, RTC_BKP_DR5, RTC_DateStruct.WeekDay);
#endif

    return RT_EOK;
}

#ifdef SOC_SERIES_STM32F1
/* update RTC_BKP_DRx*/
static void rt_rtc_f1_bkp_update(void)
{
    RTC_DateTypeDef RTC_DateStruct = {0};

    HAL_PWR_EnableBkUpAccess();
    __HAL_RCC_BKP_CLK_ENABLE();

    RTC_DateStruct.Year    = HAL_RTCEx_BKUPRead(&RTC_Handler, RTC_BKP_DR2);
    RTC_DateStruct.Month   = HAL_RTCEx_BKUPRead(&RTC_Handler, RTC_BKP_DR3);
    RTC_DateStruct.Date    = HAL_RTCEx_BKUPRead(&RTC_Handler, RTC_BKP_DR4);
    RTC_DateStruct.WeekDay = HAL_RTCEx_BKUPRead(&RTC_Handler, RTC_BKP_DR5);
    if (HAL_RTC_SetDate(&RTC_Handler, &RTC_DateStruct, RTC_FORMAT_BIN) != HAL_OK)
    {
        Error_Handler();
    }

    HAL_RTC_GetDate(&RTC_Handler, &RTC_DateStruct, RTC_FORMAT_BIN);
    if (HAL_RTCEx_BKUPRead(&RTC_Handler, RTC_BKP_DR4) != RTC_DateStruct.Date)
    {
        HAL_RTCEx_BKUPWrite(&RTC_Handler, RTC_BKP_DR1, BKUP_REG_DATA);
        HAL_RTCEx_BKUPWrite(&RTC_Handler, RTC_BKP_DR2, RTC_DateStruct.Year);
        HAL_RTCEx_BKUPWrite(&RTC_Handler, RTC_BKP_DR3, RTC_DateStruct.Month);
        HAL_RTCEx_BKUPWrite(&RTC_Handler, RTC_BKP_DR4, RTC_DateStruct.Date);
        HAL_RTCEx_BKUPWrite(&RTC_Handler, RTC_BKP_DR5, RTC_DateStruct.WeekDay);
    }
}
#endif

static rt_err_t rt_rtc_config(void)
{
    RCC_PeriphCLKInitTypeDef PeriphClkInitStruct = {0};

    HAL_PWR_EnableBkUpAccess();
    PeriphClkInitStruct.PeriphClockSelection = RCC_PERIPHCLK_RTC;
#ifdef BSP_RTC_USING_LSI
    PeriphClkInitStruct.RTCClockSelection = RCC_RTCCLKSOURCE_LSI;
#else
    PeriphClkInitStruct.RTCClockSelection = RCC_RTCCLKSOURCE_LSE;
#endif
    HAL_RCCEx_PeriphCLKConfig(&PeriphClkInitStruct);

#if defined(SOC_SERIES_STM32WL)
    __HAL_RCC_RTCAPB_CLK_ENABLE();
#endif

    /* Enable RTC Clock */
    __HAL_RCC_RTC_ENABLE();

    RTC_Handler.Instance = RTC;
    if (HAL_RTCEx_BKUPRead(&RTC_Handler, RTC_BKP_DR1) != BKUP_REG_DATA)
    {
        LOG_I("RTC hasn't been configured, please use <date> command to config.");

#if defined(SOC_SERIES_STM32F1)
        RTC_Handler.Init.OutPut = RTC_OUTPUTSOURCE_NONE;
        RTC_Handler.Init.AsynchPrediv = RTC_AUTO_1_SECOND;
#elif defined(SOC_SERIES_STM32F0)

        /* set the frequency division */
#ifdef BSP_RTC_USING_LSI
        RTC_Handler.Init.AsynchPrediv = 0XA0;
        RTC_Handler.Init.SynchPrediv = 0xFA;
#else
        RTC_Handler.Init.AsynchPrediv = 0X7F;
        RTC_Handler.Init.SynchPrediv = 0x0130;
#endif /* BSP_RTC_USING_LSI */

        RTC_Handler.Init.HourFormat = RTC_HOURFORMAT_24;
        RTC_Handler.Init.OutPut = RTC_OUTPUT_DISABLE;
        RTC_Handler.Init.OutPutPolarity = RTC_OUTPUT_POLARITY_HIGH;
        RTC_Handler.Init.OutPutType = RTC_OUTPUT_TYPE_OPENDRAIN;
#elif defined(SOC_SERIES_STM32F2) || defined(SOC_SERIES_STM32F4) || defined(SOC_SERIES_STM32F7) || defined(SOC_SERIES_STM32L4) || defined(SOC_SERIES_STM32WL) || defined(SOC_SERIES_STM32H7) || defined (SOC_SERIES_STM32WB)

        /* set the frequency division */
#ifdef BSP_RTC_USING_LSI
        RTC_Handler.Init.AsynchPrediv = 0X7D;
#else
        RTC_Handler.Init.AsynchPrediv = 0X7F;
#endif /* BSP_RTC_USING_LSI */
        RTC_Handler.Init.SynchPrediv = 0XFF;

        RTC_Handler.Init.HourFormat = RTC_HOURFORMAT_24;
        RTC_Handler.Init.OutPut = RTC_OUTPUT_DISABLE;
        RTC_Handler.Init.OutPutPolarity = RTC_OUTPUT_POLARITY_HIGH;
        RTC_Handler.Init.OutPutType = RTC_OUTPUT_TYPE_OPENDRAIN;
#endif
        if (HAL_RTC_Init(&RTC_Handler) != HAL_OK)
        {
            return -RT_ERROR;
        }
    }
#ifdef SOC_SERIES_STM32F1
    else
    {
        /* F1 series need update by bkp reg datas */
        rt_rtc_f1_bkp_update();
    }
#endif

    return RT_EOK;
}

static rt_err_t stm32_rtc_init(void)
{
#if !defined(SOC_SERIES_STM32H7) && !defined(SOC_SERIES_STM32WL) && !defined(SOC_SERIES_STM32WB)
    __HAL_RCC_PWR_CLK_ENABLE();
#endif

    RCC_OscInitTypeDef RCC_OscInitStruct = {0};
#ifdef BSP_RTC_USING_LSI
#ifdef SOC_SERIES_STM32WB
RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_LSI1;
    RCC_OscInitStruct.PLL.PLLState = RCC_PLL_NONE;
    RCC_OscInitStruct.LSEState = RCC_LSE_OFF;
    RCC_OscInitStruct.LSIState = RCC_LSI_ON;
#else
    RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_LSI;
    RCC_OscInitStruct.PLL.PLLState = RCC_PLL_NONE;
    RCC_OscInitStruct.LSEState = RCC_LSE_OFF;
    RCC_OscInitStruct.LSIState = RCC_LSI_ON;
#endif
#else
    RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_LSE;
    RCC_OscInitStruct.PLL.PLLState = RCC_PLL_NONE;
    RCC_OscInitStruct.LSEState = RCC_LSE_ON;
    RCC_OscInitStruct.LSIState = RCC_LSI_OFF;
#endif
    HAL_RCC_OscConfig(&RCC_OscInitStruct);

    if (rt_rtc_config() != RT_EOK)
    {
        LOG_E("rtc init failed.");
        return -RT_ERROR;
    }

    return RT_EOK;
}

static rt_err_t stm32_rtc_get_secs(time_t *sec)
{
    struct timeval tv;

    stm32_rtc_get_timeval(&tv);
    *(time_t *) sec = tv.tv_sec;
    LOG_D("RTC: get rtc_time %d", *sec);

    return RT_EOK;
}

static rt_err_t stm32_rtc_set_secs(time_t *sec)
{
    rt_err_t result = RT_EOK;

    if (set_rtc_time_stamp(*sec))
    {
        result = -RT_ERROR;
    }
    LOG_D("RTC: set rtc_time %d", *sec);

    return result;
}

static const struct rt_rtc_ops stm32_rtc_ops =
{
    stm32_rtc_init,
    stm32_rtc_get_secs,
    stm32_rtc_set_secs,
    RT_NULL,
    RT_NULL,
    stm32_rtc_get_timeval,
    RT_NULL,
};

static rt_rtc_dev_t stm32_rtc_dev;

static int rt_hw_rtc_init(void)
{
    rt_err_t result;

    stm32_rtc_dev.ops = &stm32_rtc_ops;
    result = rt_hw_rtc_register(&stm32_rtc_dev, "rtc", RT_DEVICE_FLAG_RDWR, RT_NULL);
    if (result != RT_EOK)
    {
        LOG_E("rtc register err code: %d", result);
        return result;
    }
    LOG_D("rtc init success");

    return RT_EOK;
}
INIT_DEVICE_EXPORT(rt_hw_rtc_init);
#endif /* BSP_USING_ONCHIP_RTC */
