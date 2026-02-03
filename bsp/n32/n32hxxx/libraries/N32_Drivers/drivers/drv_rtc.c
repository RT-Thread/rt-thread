/*
 * Copyright (c) 2006-2025, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author           Notes
 * 2026-01-24     ox-horse         first version
 */

#include "board.h"
#include <sys/time.h>
#include <rtdevice.h>
#include <drv_common.h>

#ifdef BSP_USING_ONCHIP_RTC

#ifndef RTC_BKP_REG1
    #define RTC_BKP_REG1 1U
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
static RTC_AlarmType Alarm_InitStruct = { 0 };
static EXTI_InitType EXTI_InitStructure = { 0 };
#endif

static struct rtc_device_object rtc_device;


rt_weak uint32_t RTC_BKUP_Read(uint8_t BackupRegister)
{
    return RTC_BKUPRgRead(BackupRegister);
}

rt_weak void RTC_BKUP_Write(uint8_t BackupRegister, uint32_t Data)
{
    RTC_BKUPRgWrite(BackupRegister, Data);
}


static rt_err_t n32_rtc_get_timeval(struct timeval *tv)
{
    uint32_t SubSeconds;
    uint32_t Div_Sync;
    RTC_TimeType RTC_TimeStruct = {0};
    RTC_DateType RTC_DateStruct = {0};
    struct tm tm_new = {0};

    RTC_GetTime(RTC_FORMAT_BIN, &RTC_TimeStruct);
    RTC_GetDate(RTC_FORMAT_BIN, &RTC_DateStruct);

    tm_new.tm_sec  = RTC_TimeStruct.Seconds;
    tm_new.tm_min  = RTC_TimeStruct.Minutes;
    tm_new.tm_hour = RTC_TimeStruct.Hours;

    tm_new.tm_mday = RTC_DateStruct.Date;
    tm_new.tm_mon  = RTC_DateStruct.Month - 1;
    tm_new.tm_year = RTC_DateStruct.Year + 100;

    tv->tv_sec = timegm(&tm_new);

    SubSeconds = (uint32_t)(RTC->SUBS);
    Div_Sync   = (uint32_t)((RTC->PRE) & 0x00007FFFU);
    tv->tv_usec = ((Div_Sync * 1.0) - (SubSeconds * 1.0)) / ((Div_Sync + 1U) * 1.0) * 1000.0 * 1000.0;

    return RT_EOK;
}


static rt_err_t set_rtc_time_stamp(time_t time_stamp)
{
    RTC_TimeType RTC_TimeStruct = {0};
    RTC_DateType RTC_DateStruct = {0};
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

    if (RTC_ConfigTime(RTC_FORMAT_BIN, &RTC_TimeStruct) == ERROR)
    {
        return -RT_ERROR;
    }
    if (RTC_SetDate(RTC_FORMAT_BIN, &RTC_DateStruct) == ERROR)
    {
        return -RT_ERROR;
    }

    LOG_D("set rtc time.");
    RTC_BKUP_Write(RTC_BKP_REG1, BKUP_REG_DATA);

    return RT_EOK;
}


static rt_err_t rt_rtc_config(void)
{
    uint32_t SynchPrediv, AsynchPrediv;
    RTC_InitType  RTC_InitStructure = { 0 };

#if defined(SOC_SERIES_N32H7xx)
    /* Enable the PWR clock */
    RCC_EnableAHB5PeriphClk2(RCC_AHB5_PERIPHEN_PWR, ENABLE);
    /* Allow access to RTC */
    PWR_BackupAccessEnable(ENABLE);

    /* Disable RTC clock */
    RCC_EnableAPB5PeriphClk2(RCC_APB5_PERIPHEN_M7_RTCPCLK, DISABLE);
#endif

#if defined(BSP_RTC_USING_LSI)
#if defined(SOC_SERIES_N32H7xx)
    /* Enable the LSI OSC */
    RCC_EnableLsi(ENABLE);
    if (RCC_WaitLsiStable() == ERROR)
    {
        return -RT_ERROR;
    }
    RCC_ConfigRtcClk(RCC_RTCCLK_SRC_LSI, RCC_RTCCLK_HSEDIV63);
#endif
    SynchPrediv  = 0xF9;
    AsynchPrediv = 0x7F;
#elif defined(BSP_RTC_USING_LSE)
#if defined(SOC_SERIES_N32H7xx)
    /* Enable the LSI */
    RCC_EnableLsi(ENABLE);
    RCC_ConfigLse(RCC_LSE_ENABLE);

    /****Waite LSE Ready *****/
    if (RCC_WaitLseStable() == ERROR)
    {
        return -RT_ERROR;
    }

    RCC_ConfigRtcClk(RCC_RTCCLK_SRC_LSE, RCC_RTCCLK_HSEDIV_MASK);
#endif
    SynchPrediv  = 0xFF;
    AsynchPrediv = 0x7F;
#else
#if defined(SOC_SERIES_N32H7xx)
    /* Enable HSE */
    RCC_EnableLsi(ENABLE);
    RCC_ConfigHse(RCC_HSE_ENABLE);
    if (RCC_WaitHseStable() == ERROR)
    {
        return -RT_ERROR;
    }
    RCC_ConfigRtcClk(RCC_RTCCLK_SRC_HSEDIV, RCC_RTCCLK_HSEDIV50);
#endif
    SynchPrediv  = 0x1387;
    AsynchPrediv = 0x63;
#endif

#if defined(SOC_SERIES_N32H7xx)
    /* Enable the RTC Clock */
    RCC_EnableAPB5PeriphClk2(RCC_APB5_PERIPHEN_M7_RTCPCLK, ENABLE);
    RCC_EnableAPB5PeriphClk2(RCC_APB5_PERIPHEN_M7_RTCPCLKLP, ENABLE);
    RCC_EnableRtcClk(ENABLE);

    if (RTC_WaitForSynchro() == ERROR)
    {
        return -RT_ERROR;
    }
#endif

    if (RTC_BKUP_Read(RTC_BKP_REG1) != BKUP_REG_DATA)
    {
        LOG_I("RTC hasn't been configured, please use <date> command to config.");

        RTC_InitStructure.RTC_AsynchPrediv = AsynchPrediv;
        RTC_InitStructure.RTC_SynchPrediv  = SynchPrediv;
        RTC_InitStructure.RTC_HourFormat   = RTC_24HOUR_FORMAT;

        if (RTC_Init(&RTC_InitStructure) == ERROR)
        {
            return -RT_ERROR;
        }
    }

    return RT_EOK;
}


static rt_err_t n32_rtc_init(void)
{
    if (rt_rtc_config() != RT_EOK)
    {
        LOG_E("rtc init failed.");
        return -RT_ERROR;
    }

    return RT_EOK;
}


static rt_err_t n32_rtc_get_secs(time_t *sec)
{
    struct timeval tv;

    n32_rtc_get_timeval(&tv);
    *(time_t *) sec = tv.tv_sec;
    LOG_D("RTC: get rtc_time %d", *sec);

    return RT_EOK;
}


static rt_err_t n32_rtc_set_secs(time_t *sec)
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


static rt_err_t n32_rtc_get_alarm(struct rt_rtc_wkalarm *alarm)
{
#ifdef RT_USING_ALARM
    *alarm = rtc_device.wkalarm;
    LOG_D("GET_ALARM %d:%d:%d", rtc_device.wkalarm.tm_hour,
          rtc_device.wkalarm.tm_min,
          rtc_device.wkalarm.tm_sec);
    return RT_EOK;
#else
    return -RT_ERROR;
#endif
}


static rt_err_t n32_rtc_set_alarm(struct rt_rtc_wkalarm *alarm)
{
#ifdef RT_USING_ALARM
    LOG_D("RT_DEVICE_CTRL_RTC_SET_ALARM");
    if (alarm != RT_NULL)
    {
        rtc_device.wkalarm.enable  = alarm->enable;
        rtc_device.wkalarm.tm_hour = alarm->tm_hour;
        rtc_device.wkalarm.tm_min  = alarm->tm_min;
        rtc_device.wkalarm.tm_sec  = alarm->tm_sec;
        rtc_device.wkalarm.tm_mday = alarm->tm_mday;
        rtc_device.wkalarm.tm_mon  = alarm->tm_mon;
        rtc_device.wkalarm.tm_year = alarm->tm_year;
        rtc_alarm_time_set(&rtc_device);
    }
    else
    {
        LOG_E("RT_DEVICE_CTRL_RTC_SET_ALARM error!!");
        return -RT_ERROR;
    }
    LOG_D("SET_ALARM %d:%d:%d", alarm->tm_hour,
          alarm->tm_min,
          alarm->tm_sec);
    return RT_EOK;
#else
    return -RT_ERROR;
#endif
}


static const struct rt_rtc_ops n32_rtc_ops =
{
    n32_rtc_init,
    n32_rtc_get_secs,
    n32_rtc_set_secs,
    n32_rtc_get_alarm,
    n32_rtc_set_alarm,
    n32_rtc_get_timeval,
    RT_NULL,
};



#ifdef RT_USING_ALARM
void rt_rtc_alarm_enable(void)
{
#if defined(SOC_SERIES_N32H7xx)
    /* Enable EXTI clocks */
    RCC_EnableAPB5PeriphClk2(RCC_APB5_PERIPHEN_EXTI, ENABLE);
#endif

    /* Configure the RTC Alarm A register */
    RTC_SetAlarm(RTC_FORMAT_BIN, RTC_A_ALARM, &Alarm_InitStruct);
    /* Enable the RTC Alarm A Interrupt */
    RTC_ConfigInt(RTC_INT_ALRA, ENABLE);
    /* Enable the Alarm A   */
    RTC_EnableAlarm(RTC_A_ALARM, ENABLE);

    LOG_D("alarm read:%d:%d:%d", Alarm_InitStruct.AlarmTime.Hours,
          Alarm_InitStruct.AlarmTime.Minutes,
          Alarm_InitStruct.AlarmTime.Seconds);


    RTC_ClrIntPendingBit(RTC_INT_ALRA);
    EXTI_ClrITPendBit(EXTI_LINE17);

    EXTI_InitStruct(&EXTI_InitStructure);

#if defined(SOC_SERIES_N32H7xx)
    EXTI_InitStructure.EXTI_Line    = EXTI_LINE17;
#endif
    EXTI_InitStructure.EXTI_Mode    = EXTI_Mode_Interrupt;
    EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Rising;
    EXTI_InitStructure.EXTI_LineCmd = ENABLE;
    EXTI_InitPeripheral(&EXTI_InitStructure);

    NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
    NVIC_SetPriority(RTC_ALARM_IRQn, NVIC_EncodePriority(NVIC_GetPriorityGrouping(), 0x02, 0));
    NVIC_EnableIRQ(RTC_ALARM_IRQn);
}

void rt_rtc_alarm_disable(void)
{
    /* Disable the AlarmX */
    RTC_EnableAlarm(RTC_A_ALARM, DISABLE);

    EXTI_InitStructure.EXTI_LineCmd = DISABLE;
#if defined(SOC_SERIES_N32H7xx)
    EXTI_InitStructure.EXTI_Line    = EXTI_LINE17;
    EXTI_InitPeripheral(&EXTI_InitStructure);

    EXTI_ClrITPendBit(EXTI_LINE17);
#endif

    NVIC_DisableIRQ(RTC_ALARM_IRQn);
}

static int rt_rtc_alarm_init(void)
{
    return RT_EOK;
}

static rt_err_t rtc_alarm_time_set(struct rtc_device_object* p_dev)
{
    if (p_dev->wkalarm.enable)
    {
        /* Disable the AlarmX */
        RTC_EnableAlarm(RTC_A_ALARM, DISABLE);

        Alarm_InitStruct.AlarmTime.Hours   = p_dev->wkalarm.tm_hour;
        Alarm_InitStruct.AlarmTime.Minutes = p_dev->wkalarm.tm_min;
        Alarm_InitStruct.AlarmTime.Seconds = p_dev->wkalarm.tm_sec;
        Alarm_InitStruct.DateWeekValue     = p_dev->wkalarm.tm_mday;

        Alarm_InitStruct.AlarmTime.H12     = RTC_AM_H12;
        Alarm_InitStruct.DateWeekMode      = RTC_ALARM_SEL_WEEKDAY_DATE;
        Alarm_InitStruct.AlarmMask         = RTC_ALARMMASK_NONE;

        LOG_D("alarm set:%d:%d:%d", Alarm_InitStruct.AlarmTime.Hours,
              Alarm_InitStruct.AlarmTime.Minutes,
              Alarm_InitStruct.AlarmTime.Seconds);
        rt_rtc_alarm_enable();
    }

    return RT_EOK;
}


void RTC_ALARM_IRQHandler(void)
{
    rt_interrupt_enter();

#if defined(SOC_SERIES_N32H7xx)
    EXTI_ClrITPendBit(EXTI_LINE17);
#endif

    if (RTC_GetITStatus(RTC_INT_ALRA) != RESET)
    {
        RTC_ClrIntPendingBit(RTC_INT_ALRA);
        rt_alarm_update(&rtc_device.rtc_dev.parent, 1);
    }

    rt_interrupt_leave();
}
#endif


static int rt_hw_rtc_init(void)
{
    rt_err_t result;

    rtc_device.rtc_dev.ops = &n32_rtc_ops;
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
