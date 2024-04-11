/*
 * Copyright (c) 2006-2023, RT-Thread Development Team
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
#include <sys/time.h>
#include <rtdevice.h>
#include <drv_common.h>

#ifdef BSP_USING_ONCHIP_RTC

#ifndef RTC_BKP_DR1
#define RTC_BKP_DR1 RT_NULL
#endif

//#define DRV_DEBUG
#define LOG_TAG             "drv.rtc"
#include <drv_log.h>

#define BKUP_REG_DATA 0xA5A5

struct rtc_device_object
{
    rt_rtc_dev_t  rtc_dev;
#ifdef RT_USING_ALARM
    struct rt_rtc_wkalarm   wkalarm;
#endif
};

#ifdef RT_USING_ALARM
static rt_err_t rtc_alarm_time_set(struct rtc_device_object* p_dev);
static int rt_rtc_alarm_init(void);
static RTC_AlarmTypeDef Alarm_InitStruct = { 0 };
#endif

static struct rtc_device_object rtc_device;
static RTC_HandleTypeDef RTC_Handler;

rt_weak uint32_t HAL_RTCEx_BKUPRead(RTC_HandleTypeDef *hrtc, uint32_t BackupRegister)
{
    return (~BKUP_REG_DATA);
}

rt_weak void HAL_RTCEx_BKUPWrite(RTC_HandleTypeDef *hrtc, uint32_t BackupRegister, uint32_t Data)
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
#if defined(BSP_RTC_USING_LSI)
    PeriphClkInitStruct.RTCClockSelection = RCC_RTCCLKSOURCE_LSI;
#elif defined(BSP_RTC_USING_LSE)
    PeriphClkInitStruct.RTCClockSelection = RCC_RTCCLKSOURCE_LSE;
#else
    PeriphClkInitStruct.RTCClockSelection = RCC_RTCCLKSOURCE_HSE_DIV32;
#endif
    HAL_RCCEx_PeriphCLKConfig(&PeriphClkInitStruct);

#if defined(SOC_SERIES_STM32WL) || defined(SOC_SERIES_STM32G0)
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
#elif defined(SOC_SERIES_STM32F2) || defined(SOC_SERIES_STM32F4) || defined(SOC_SERIES_STM32F7) || defined(SOC_SERIES_STM32L0) \
        || defined(SOC_SERIES_STM32L4) || defined(SOC_SERIES_STM32WL) || defined(SOC_SERIES_STM32H7) || defined (SOC_SERIES_STM32WB) \
        || defined(SOC_SERIES_STM32G0)

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
#else
#warning "This series doesn't support yet!"
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
#ifdef SOC_SERIES_STM32F1
    __HAL_RCC_BKP_CLK_ENABLE();
#endif
#endif

#if defined(BSP_RTC_USING_LSI) || defined(BSP_RTC_USING_LSE)
    RCC_OscInitTypeDef RCC_OscInitStruct = {0};
#ifdef BSP_RTC_USING_LSI
#ifdef SOC_SERIES_STM32WB
    RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_LSI1;
#else
    RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_LSI;
#endif
    RCC_OscInitStruct.LSEState = RCC_LSE_OFF;
    RCC_OscInitStruct.LSIState = RCC_LSI_ON;
#else
    RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_LSE;
    RCC_OscInitStruct.LSEState = RCC_LSE_ON;
    RCC_OscInitStruct.LSIState = RCC_LSI_OFF;
#endif
    RCC_OscInitStruct.PLL.PLLState = RCC_PLL_NONE;
    HAL_RCC_OscConfig(&RCC_OscInitStruct);
#endif

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
#ifdef RT_USING_ALARM
    rt_alarm_update(&rtc_device.rtc_dev.parent, 1);
#endif
    return result;
}

static rt_err_t stm32_rtc_get_alarm(struct rt_rtc_wkalarm *alarm)
{
#ifdef RT_USING_ALARM
    *alarm = rtc_device.wkalarm;
    LOG_D("GET_ALARM %d:%d:%d",rtc_device.wkalarm.tm_hour,
        rtc_device.wkalarm.tm_min,rtc_device.wkalarm.tm_sec);
    return RT_EOK;
#else
    return -RT_ERROR;
#endif
}

static rt_err_t stm32_rtc_set_alarm(struct rt_rtc_wkalarm *alarm)
{
#ifdef RT_USING_ALARM
    LOG_D("RT_DEVICE_CTRL_RTC_SET_ALARM");
    if (alarm != RT_NULL)
    {
        rtc_device.wkalarm.enable = alarm->enable;
        rtc_device.wkalarm.tm_hour = alarm->tm_hour;
        rtc_device.wkalarm.tm_min = alarm->tm_min;
        rtc_device.wkalarm.tm_sec = alarm->tm_sec;
        rtc_alarm_time_set(&rtc_device);
    }
    else
    {
        LOG_E("RT_DEVICE_CTRL_RTC_SET_ALARM error!!");
        return -RT_ERROR;
    }
    LOG_D("SET_ALARM %d:%d:%d",alarm->tm_hour,
        alarm->tm_min, alarm->tm_sec);
    return RT_EOK;
#else
    return -RT_ERROR;
#endif
}

static const struct rt_rtc_ops stm32_rtc_ops =
{
    stm32_rtc_init,
    stm32_rtc_get_secs,
    stm32_rtc_set_secs,
    stm32_rtc_get_alarm,
    stm32_rtc_set_alarm,
    stm32_rtc_get_timeval,
    RT_NULL,
};

#ifdef RT_USING_ALARM
void rt_rtc_alarm_enable(void)
{
    HAL_RTC_SetAlarm_IT(&RTC_Handler,&Alarm_InitStruct,RTC_FORMAT_BIN);
    HAL_RTC_GetAlarm(&RTC_Handler,&Alarm_InitStruct,RTC_ALARM_A,RTC_FORMAT_BIN);
    LOG_D("alarm read:%d:%d:%d", Alarm_InitStruct.AlarmTime.Hours,
        Alarm_InitStruct.AlarmTime.Minutes,
        Alarm_InitStruct.AlarmTime.Seconds);
    HAL_NVIC_SetPriority(RTC_Alarm_IRQn, 0x02, 0);
    HAL_NVIC_EnableIRQ(RTC_Alarm_IRQn);
}

void rt_rtc_alarm_disable(void)
{
    HAL_RTC_DeactivateAlarm(&RTC_Handler, RTC_ALARM_A);
    HAL_NVIC_DisableIRQ(RTC_Alarm_IRQn);
}

static int rt_rtc_alarm_init(void)
{
    return RT_EOK;
}

static rt_err_t rtc_alarm_time_set(struct rtc_device_object* p_dev)
{
    if (p_dev->wkalarm.enable)
    {
        Alarm_InitStruct.Alarm = RTC_ALARM_A;
        Alarm_InitStruct.AlarmTime.Hours = p_dev->wkalarm.tm_hour;
        Alarm_InitStruct.AlarmTime.Minutes = p_dev->wkalarm.tm_min;
        Alarm_InitStruct.AlarmTime.Seconds = p_dev->wkalarm.tm_sec;
#ifndef SOC_SERIES_STM32F1
        Alarm_InitStruct.AlarmDateWeekDay = RTC_WEEKDAY_MONDAY;
        Alarm_InitStruct.AlarmDateWeekDaySel = RTC_ALARMDATEWEEKDAYSEL_WEEKDAY;
        Alarm_InitStruct.AlarmMask = RTC_ALARMMASK_DATEWEEKDAY;
        Alarm_InitStruct.AlarmSubSecondMask = RTC_ALARMSUBSECONDMASK_NONE;
        Alarm_InitStruct.AlarmTime.TimeFormat = RTC_HOURFORMAT12_AM;
#endif  /* SOC_SERIES_STM32F1 */
        LOG_D("alarm set:%d:%d:%d", Alarm_InitStruct.AlarmTime.Hours,
            Alarm_InitStruct.AlarmTime.Minutes,
            Alarm_InitStruct.AlarmTime.Seconds);
        rt_rtc_alarm_enable();
    }

    return RT_EOK;
}

void HAL_RTC_AlarmAEventCallback(RTC_HandleTypeDef *hrtc)
{
    //LOG_D("rtc alarm isr.\n");
    rt_alarm_update(&rtc_device.rtc_dev.parent, 1);
}

void RTC_Alarm_IRQHandler(void)
{
    rt_interrupt_enter();
    HAL_RTC_AlarmIRQHandler(&RTC_Handler);
    rt_interrupt_leave();
}
#endif

static int rt_hw_rtc_init(void)
{
    rt_err_t result;

    rtc_device.rtc_dev.ops = &stm32_rtc_ops;
    result = rt_hw_rtc_register(&rtc_device.rtc_dev, "rtc", RT_DEVICE_FLAG_RDWR, RT_NULL);
    if (result != RT_EOK)
    {
        LOG_E("rtc register err code: %d", result);
        return result;
    }
    LOG_D("rtc init success");

#ifdef RT_USING_ALARM
    rt_rtc_alarm_init();
#endif

    return RT_EOK;
}
INIT_DEVICE_EXPORT(rt_hw_rtc_init);
#endif /* BSP_USING_ONCHIP_RTC */
