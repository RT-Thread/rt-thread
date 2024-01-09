/*
 * Copyright (C) 2022-2024, Xiaohua Semiconductor Co., Ltd.
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author               Notes
 * 2022-04-28     CDT                  first version
 * 2022-05-31     CDT                  delete this file
 * 2022-06-10     xiaoxiaolisunny      re-add this file for F460
 * 2023-02-14     CDT                  add alarm(precision is 1 minute)
 */

#include <board.h>
#include <sys/time.h>
#include "board_config.h"

#if defined(BSP_USING_RTC)

//#define DRV_DEBUG
#define LOG_TAG             "drv.rtc"
#include <drv_log.h>

#if defined(HC32F4A0)
/* BACKUP REG: 96~127 for RTC used */
#define RTC_BACKUP_DATA_SIZE        (32U)
#define RTC_BACKUP_REG_OFFSET       (128U - RTC_BACKUP_DATA_SIZE)

static const uint8_t m_au8BackupWriteData[RTC_BACKUP_DATA_SIZE] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10,
                                                                   11, 12, 13, 14, 15, 16, 17, 18, 19, 20,
                                                                   21, 22, 23, 24, 25, 26, 27, 28, 29, 30,
                                                                   31
                                                                  };
static uint8_t m_au8BackupReadData[RTC_BACKUP_DATA_SIZE];
#endif

static rt_rtc_dev_t rtc_dev;

#ifdef RT_USING_ALARM
struct stc_hc32_alarm_irq
{
    struct hc32_irq_config  irq_config;
    func_ptr_t              irq_callback;
};

static void _rtc_alarm_irq_handler(void);

#define RTC_ALARM_IRQ_CONFIG                                \
    {                                                       \
        .irq_num    = BSP_RTC_ALARM_IRQ_NUM,                \
        .irq_prio   = BSP_RTC_ALARM_IRQ_PRIO,               \
        .int_src    = INT_SRC_RTC_ALM,                      \
    }

static struct stc_hc32_alarm_irq hc32_alarm_irq =
{
    .irq_config     = RTC_ALARM_IRQ_CONFIG,
    .irq_callback   = _rtc_alarm_irq_handler,
};
#endif

#if defined(HC32F4A0)
static void _bakup_reg_write(void)
{
    uint8_t u8Num;
    for (u8Num = 0U; u8Num < RTC_BACKUP_DATA_SIZE; u8Num++)
    {
        PWC_BKR_Write(u8Num + RTC_BACKUP_REG_OFFSET, m_au8BackupWriteData[u8Num]);
    }
}

static int32_t _bakup_reg_check(void)
{
    uint8_t u8Num;
    int32_t i32Ret = LL_OK;

    for (u8Num = 0U; u8Num < RTC_BACKUP_DATA_SIZE; u8Num++)
    {
        m_au8BackupReadData[u8Num] = PWC_BKR_Read(u8Num + RTC_BACKUP_REG_OFFSET);
    }

    for (u8Num = 0U; u8Num < RTC_BACKUP_DATA_SIZE; u8Num++)
    {
        if (m_au8BackupWriteData[u8Num] != m_au8BackupReadData[u8Num])
        {
            i32Ret = LL_ERR;
            break;
        }
    }

    return i32Ret;
}

static int32_t _hc32_rtc_rw_check(void)
{
    int32_t i32Ret = LL_ERR;

    /* Enter read/write mode */
    if (LL_OK == RTC_EnterRwMode())
    {
        /* Exit read/write mode */
        if (LL_OK == RTC_ExitRwMode())
        {
            i32Ret = LL_OK;
        }
    }

    return i32Ret;
}
#endif

static rt_err_t _rtc_get_timeval(struct timeval *tv)
{

    stc_rtc_time_t stcRtcTime = {0};
    stc_rtc_date_t stcRtcDate = {0};
    struct tm tm_new = {0};

    if (LL_OK != RTC_GetTime(RTC_DATA_FMT_DEC, &stcRtcTime))
    {
        return -RT_ERROR;
    }
    if (LL_OK != RTC_GetDate(RTC_DATA_FMT_DEC, &stcRtcDate))
    {
        return -RT_ERROR;
    }

    tm_new.tm_sec  = stcRtcTime.u8Second;
    tm_new.tm_min  = stcRtcTime.u8Minute;
    tm_new.tm_hour = stcRtcTime.u8Hour;
    tm_new.tm_mday = stcRtcDate.u8Day;
    tm_new.tm_mon  = stcRtcDate.u8Month - 1;
    tm_new.tm_year = stcRtcDate.u8Year + 100;

    tv->tv_sec = timegm(&tm_new);

    return RT_EOK;
}

static rt_err_t hc32_rtc_set_time_stamp(time_t time_stamp)
{
    stc_rtc_time_t stcRtcTime = {0};
    stc_rtc_date_t stcRtcDate = {0};
    struct tm tm_set = {0};

    gmtime_r(&time_stamp, &tm_set);

    if (tm_set.tm_year < 100)
    {
        return -RT_ERROR;
    }

    stcRtcTime.u8Second  = tm_set.tm_sec ;
    stcRtcTime.u8Minute  = tm_set.tm_min ;
    stcRtcTime.u8Hour    = tm_set.tm_hour;
    stcRtcDate.u8Day     = tm_set.tm_mday;
    stcRtcDate.u8Month   = tm_set.tm_mon + 1;
    stcRtcDate.u8Year    = tm_set.tm_year - 100;
    stcRtcDate.u8Weekday = tm_set.tm_wday;

    if (LL_OK != RTC_SetTime(RTC_DATA_FMT_DEC, &stcRtcTime))
    {
        return -RT_ERROR;
    }
    if (LL_OK != RTC_SetDate(RTC_DATA_FMT_DEC, &stcRtcDate))
    {
        return -RT_ERROR;
    }

    LOG_D("set rtc time.");
    return RT_EOK;
}

static rt_err_t _rtc_init(void)
{
    stc_rtc_init_t stcRtcInit;

#if defined(HC32F4A0)
    if ((LL_OK != _bakup_reg_check()) || (LL_OK != _hc32_rtc_rw_check()))
#elif  defined(HC32F460)
    if (DISABLE == RTC_GetCounterState())
#endif
    {
        /* Reset RTC counter */
        if (LL_ERR_TIMEOUT == RTC_DeInit())
        {
            LOG_E("Reset RTC failed!");
            return -RT_ERROR;
        }
        else
        {
            /* Stop RTC */
            RTC_Cmd(DISABLE);
            /* Configure structure initialization */
            (void)RTC_StructInit(&stcRtcInit);

            /* Configuration RTC structure */
#ifdef BSP_RTC_USING_XTAL32
            stcRtcInit.u8ClockSrc = RTC_CLK_SRC_XTAL32;
#else
            stcRtcInit.u8ClockSrc = RTC_CLK_SRC_LRC;
#endif
            stcRtcInit.u8HourFormat = RTC_HOUR_FMT_24H;
            (void)RTC_Init(&stcRtcInit);

            /* Clear all status */
            RTC_ClearStatus(RTC_FLAG_CLR_ALL);
            /* Startup RTC count */
            RTC_Cmd(ENABLE);

#if defined(HC32F4A0)
            /* Write sequence flag to backup register  */
            _bakup_reg_write();
#endif
            LOG_D("rtc init success");
        }
    }
    else
    {
        LOG_D("rtc does not need to init");
    }

    return RT_EOK;
}

static rt_err_t _rtc_get_secs(time_t *sec)
{
    struct timeval tv;

    _rtc_get_timeval(&tv);
    *(time_t *) sec = tv.tv_sec;
    LOG_D("RTC: get rtc_time %d", *sec);

    return RT_EOK;
}

static rt_err_t _rtc_set_secs(time_t *sec)
{
    rt_err_t result = RT_EOK;

    if (hc32_rtc_set_time_stamp(*sec))
    {
        result = -RT_ERROR;
    }
    LOG_D("RTC: set rtc_time %d", *sec);
#ifdef RT_USING_ALARM
    rt_alarm_update(&rtc_dev.parent, 1);
#endif
    return result;
}

#ifdef RT_USING_ALARM

static void _rtc_alarm_irq_handler(void)
{
    rt_interrupt_enter();
    RTC_ClearStatus(RTC_FLAG_ALARM);
    rt_alarm_update(&rtc_dev.parent, 1);
    rt_interrupt_leave();
}

static void hc32_rtc_alarm_enable(void)
{
    NVIC_EnableIRQ(hc32_alarm_irq.irq_config.irq_num);

    RTC_IntCmd(RTC_INT_ALARM, ENABLE);
    RTC_AlarmCmd(ENABLE);
    LOG_D("hc32 alarm enable");
}

static void hc32_rtc_alarm_disable(void)
{
    RTC_AlarmCmd(DISABLE);
    RTC_IntCmd(RTC_INT_ALARM, DISABLE);

    NVIC_DisableIRQ(hc32_alarm_irq.irq_config.irq_num);
    LOG_D("hc32 alarm disable");
}
#endif

static rt_err_t _rtc_get_alarm(struct rt_rtc_wkalarm *alarm)
{
#ifdef RT_USING_ALARM
    stc_rtc_alarm_t stcRtcAlarm;
    RTC_GetAlarm(RTC_DATA_FMT_DEC, &stcRtcAlarm);
    alarm->tm_hour = stcRtcAlarm.u8AlarmHour;
    alarm->tm_min  = stcRtcAlarm.u8AlarmMinute;
    alarm->tm_sec  = 0; /* alarms precision is 1 minute */

    LOG_D("GET_ALARM %d:%d:%d", alarm->tm_hour, alarm->tm_min, alarm->tm_sec);
    return RT_EOK;
#else
    return -RT_ERROR;
#endif
}

static rt_err_t _rtc_set_alarm(struct rt_rtc_wkalarm *alarm)
{
#ifdef RT_USING_ALARM
    stc_rtc_alarm_t stcRtcAlarm;

    LOG_D("RT_DEVICE_CTRL_RTC_SET_ALARM");
    if (alarm != RT_NULL)
    {
        if (alarm->enable)
        {
            RTC_AlarmCmd(DISABLE);
            /* Configuration alarm time: precision is 1 minute */
            stcRtcAlarm.u8AlarmHour    = alarm->tm_hour;
            stcRtcAlarm.u8AlarmMinute  = alarm->tm_min;
            stcRtcAlarm.u8AlarmWeekday = RTC_ALARM_WEEKDAY_EVERYDAY;
            stcRtcAlarm.u8AlarmAmPm    = RTC_HOUR_24H;
            RTC_ClearStatus(RTC_FLAG_ALARM);
            (void)RTC_SetAlarm(RTC_DATA_FMT_DEC, &stcRtcAlarm);
            hc32_rtc_alarm_enable();
            LOG_D("SET_ALARM %d:%d:%d", alarm->tm_hour,
                  alarm->tm_min, 0);
        }
        else
        {
            hc32_rtc_alarm_disable();
        }

    }
    else
    {
        LOG_E("RT_DEVICE_CTRL_RTC_SET_ALARM error!!");
        return -RT_ERROR;
    }

    return RT_EOK;
#else
    return -RT_ERROR;
#endif
}

const static struct rt_rtc_ops _ops =
{
    _rtc_init,
    _rtc_get_secs,
    _rtc_set_secs,
    _rtc_get_alarm,
    _rtc_set_alarm,
    _rtc_get_timeval,
    RT_NULL
};

int rt_hw_rtc_init(void)
{
    rt_err_t result;

#ifdef RT_USING_ALARM
    /* register interrupt */
    hc32_install_irq_handler(&hc32_alarm_irq.irq_config, hc32_alarm_irq.irq_callback, RT_FALSE);
#endif

    rtc_dev.ops = &_ops;
    result = rt_hw_rtc_register(&rtc_dev, "rtc", RT_DEVICE_FLAG_RDWR, RT_NULL);
    if (result != RT_EOK)
    {
        LOG_E("rtc register err code: %d", result);
        return result;
    }
    LOG_D("rtc register done");
    return RT_EOK;
}
INIT_DEVICE_EXPORT(rt_hw_rtc_init);

#endif /* BSP_USING_RTC */
