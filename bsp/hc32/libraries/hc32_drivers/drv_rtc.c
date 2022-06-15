/*
 * Copyright (c) 2006-2022, RT-Thread Development Team
 * Copyright (c) 2022, xiaoxiaolisunny
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author               Notes
 * 2022-06-10     xiaoxiaolisunny      first version
 */

#include <board.h>
#include <rtdbg.h>
#include <rtthread.h>
#include <rtdevice.h>
#include <sys/time.h>

#ifdef BSP_USING_RTC

static rt_rtc_dev_t hc32_rtc_dev;

static rt_err_t hc32_rtc_get_time_stamp(struct timeval *tv)
{
    stc_rtc_time_t stcRtcTime = {0};
    stc_rtc_date_t stcRtcDate = {0};
    struct tm tm_new = {0};

    RTC_GetTime(RTC_DATA_FMT_DEC, &stcRtcTime);
    RTC_GetDate(RTC_DATA_FMT_DEC, &stcRtcDate);

    tm_new.tm_sec  = stcRtcTime.u8Second;
    tm_new.tm_min  = stcRtcTime.u8Minute;
    tm_new.tm_hour = stcRtcTime.u8Hour;
    if(stcRtcDate.u8Month == 0)
    {
        tm_new.tm_mday = stcRtcDate.u8Day + 1;
        tm_new.tm_mon  = stcRtcDate.u8Month;
    }
    else
    {
        tm_new.tm_mday = stcRtcDate.u8Day ;
        tm_new.tm_mon  = stcRtcDate.u8Month - 1;
    }
    tm_new.tm_year = stcRtcDate.u8Year + 100;

    tv->tv_sec = timegm(&tm_new);

    return RT_EOK;
}

static rt_err_t hc32_rtc_set_time_stamp(time_t time_stamp)
{
    stc_rtc_time_t stcRtcTime = {0};
    stc_rtc_date_t stcRtcDate = {0};
    struct tm p_tm = {0};

    gmtime_r(&time_stamp, &p_tm);

    if (p_tm.tm_year < 100)
    {
        return -RT_ERROR;
    }

    stcRtcTime.u8Second  = p_tm.tm_sec ;
    stcRtcTime.u8Minute  = p_tm.tm_min ;
    stcRtcTime.u8Hour    = p_tm.tm_hour;
    stcRtcDate.u8Day     = p_tm.tm_mday;
    stcRtcDate.u8Month   = p_tm.tm_mon + 1;
    stcRtcDate.u8Year    = p_tm.tm_year - 100;
    stcRtcDate.u8Weekday = p_tm.tm_wday;

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

static rt_err_t hc32_rtc_init(void)
{
    stc_rtc_init_t stcRtcInit;

#ifdef BSP_RTC_USING_XTAL32
    stc_clock_xtal32_init_t stcXtal32Init;
    /* Xtal32 config */
    stcXtal32Init.u8State  = CLK_XTAL32_ON;
    stcXtal32Init.u8Drv    = CLK_XTAL32_DRV_HIGH;
    stcXtal32Init.u8Filter = CLK_XTAL32_FILTER_RUN_MD;
    (void)CLK_Xtal32Init(&stcXtal32Init);
    /* Waiting for XTAL32 stabilization */
    rt_thread_delay(100);
#endif

    /* RTC stopped */
    if (DISABLE == RTC_GetCounterState())
    {
        /* Reset RTC counter */
        if (LL_ERR_TIMEOUT == RTC_DeInit())
        {
            return -RT_ERROR;
        }
        else
        {
            /* Configure structure initialization */
            (void)RTC_StructInit(&stcRtcInit);
            /* Configuration RTC structure */
            #ifdef BSP_RTC_USING_XTAL32
            stcRtcInit.u8ClockSrc = RTC_CLK_SRC_XTAL32;
            #else
            stcRtcInit.u8ClockSrc = RTC_CLK_SRC_LRC;
            #endif
            stcRtcInit.u8HourFormat  = RTC_HOUR_FMT_24H;
            (void)RTC_Init(&stcRtcInit);
            /* Startup RTC count */
            RTC_Cmd(ENABLE);
        }
    }
    return RT_EOK;
}

static rt_err_t hc32_rtc_get_secs(time_t *sec)
{
    struct timeval tv;

    hc32_rtc_get_time_stamp(&tv);
    *(time_t *) sec = tv.tv_sec;
    LOG_D("RTC: get rtc_time %d", *sec);

    return RT_EOK;
}

static rt_err_t hc32_rtc_set_secs(time_t *sec)
{
    rt_err_t result = RT_EOK;

    if (hc32_rtc_set_time_stamp(*sec))
    {
        result = -RT_ERROR;
    }
    LOG_D("RTC: set rtc_time %d", *sec);

    return result;
}

const static struct rt_rtc_ops hc32_rtc_ops =
{
    hc32_rtc_init,
    hc32_rtc_get_secs,
    hc32_rtc_set_secs,
    RT_NULL,
    RT_NULL,
    hc32_rtc_get_time_stamp,
    RT_NULL
};

int rt_hw_rtc_init(void)
{
    rt_err_t result;

    hc32_rtc_dev.ops = &hc32_rtc_ops;
    result = rt_hw_rtc_register(&hc32_rtc_dev, "rtc", RT_DEVICE_FLAG_RDWR, RT_NULL);
    if (result != RT_EOK)
    {
        LOG_E("rtc register err code: %d", result);
        return result;
    }
    LOG_D("rtc init success");
    return RT_EOK;
}
INIT_DEVICE_EXPORT(rt_hw_rtc_init);

#endif /* BSP_USING_RTC */
