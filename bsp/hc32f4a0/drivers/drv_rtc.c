/*
 * Copyright (C) 2020, Huada Semiconductor Co., Ltd.
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2020-10-30     CDT          first version
 */
 
#include <board.h>
#include <rtdbg.h>
#include <rtthread.h>
#include <rtdevice.h>
#include <sys/time.h>

#ifdef BSP_USING_RTC

static struct rt_device rtc;

static time_t hc32_rtc_get_time_stamp(void)
{
    stc_rtc_time_t stcRtcTime = {0};
    stc_rtc_date_t stcRtcDate = {0};
    struct tm tm_new = {0};

    RTC_GetTime(RTC_DATA_FORMAT_DEC, &stcRtcTime);
    RTC_GetDate(RTC_DATA_FORMAT_DEC, &stcRtcDate);

    tm_new.tm_sec  = stcRtcTime.u8Second;
    tm_new.tm_min  = stcRtcTime.u8Minute;
    tm_new.tm_hour = stcRtcTime.u8Hour;
    tm_new.tm_mday = stcRtcDate.u8Day;
    tm_new.tm_mon  = stcRtcDate.u8Month - 1;
    tm_new.tm_year = stcRtcDate.u8Year + 100;
    tm_new.tm_wday = stcRtcDate.u8Weekday;

    LOG_D("get rtc time.");
    return timegm(&tm_new);
}

static rt_err_t hc32_rtc_set_time_stamp(time_t time_stamp)
{
    stc_rtc_time_t stcRtcTime = {0};
    stc_rtc_date_t stcRtcDate = {0};
    struct tm *p_tm;

    p_tm = gmtime(&time_stamp);
    if (p_tm->tm_year < 100)
    {
        return -RT_ERROR;
    }

    stcRtcTime.u8Second  = p_tm->tm_sec ;
    stcRtcTime.u8Minute  = p_tm->tm_min ;
    stcRtcTime.u8Hour    = p_tm->tm_hour;
    stcRtcDate.u8Day     = p_tm->tm_mday;
    stcRtcDate.u8Month   = p_tm->tm_mon + 1 ;
    stcRtcDate.u8Year    = p_tm->tm_year - 100;
    stcRtcDate.u8Weekday = p_tm->tm_wday;

    if (Ok != RTC_SetTime(RTC_DATA_FORMAT_DEC, &stcRtcTime))
    {
        return -RT_ERROR;
    }
    if (Ok != RTC_SetDate(RTC_DATA_FORMAT_DEC, &stcRtcDate))
    {
        return -RT_ERROR;
    }

    LOG_D("set rtc time.");
    return RT_EOK;
}

static rt_err_t hc32_rtc_init(struct rt_device *dev)
{
    stc_rtc_init_t stcRtcInit;

#ifdef BSP_RTC_USING_XTAL32
    stc_clk_xtal32_init_t stcXtal32Init;

    /* Xtal32 config */
    stcXtal32Init.u8Xtal32State = CLK_XTAL32_ON;
    stcXtal32Init.u8Xtal32Drv   = CLK_XTAL32DRV_HIGH;
    stcXtal32Init.u8Xtal32NF    = CLK_XTAL32NF_PART;
    (void)CLK_Xtal32Init(&stcXtal32Init);
    /* Waiting for XTAL32 stabilization */
    rt_thread_delay(1000);
#endif

    /* Reset RTC counter */
    if (ErrorTimeout == RTC_DeInit())
    {
        return -RT_ERROR;
    }
    else
    {
        /* Configure structure initialization */
        (void)RTC_StructInit(&stcRtcInit);
        /* Configuration RTC structure */
#ifdef BSP_RTC_USING_XTAL32
        stcRtcInit.u8ClockSource = RTC_CLOCK_SOURCE_XTAL32;
#else
        stcRtcInit.u8ClockSource = RTC_CLOCK_SOURCE_RTCLRC;
#endif
        stcRtcInit.u8HourFormat  = RTC_HOUR_FORMAT_24;
        (void)RTC_Init(&stcRtcInit);
        /* Startup RTC count */
        RTC_Cmd(Enable);
    }

    return RT_EOK;
}

static rt_err_t hc32_rtc_control(rt_device_t dev, int cmd, void *args)
{
    rt_err_t result = RT_EOK;

    RT_ASSERT(dev != RT_NULL);
    switch (cmd)
    {
    case RT_DEVICE_CTRL_RTC_GET_TIME:
        *(rt_uint32_t *)args = hc32_rtc_get_time_stamp();
        LOG_D("RTC: get rtc_time %x\n", *(rt_uint32_t *)args);
        break;

    case RT_DEVICE_CTRL_RTC_SET_TIME:
        if (hc32_rtc_set_time_stamp(*(rt_uint32_t *)args))
        {
            result = -RT_ERROR;
        }
        LOG_D("RTC: set rtc_time %x\n", *(rt_uint32_t *)args);
        break;
    default:
        return RT_EINVAL;
    }

    return result;
}

#ifdef RT_USING_DEVICE_OPS
const static struct rt_device_ops rtc_ops =
{
    RT_NULL,
    RT_NULL,
    RT_NULL,
    RT_NULL,
    RT_NULL,
    hc32_rtc_control
};
#endif

static rt_err_t rt_hw_rtc_register(rt_device_t device, const char *name, rt_uint32_t flag)
{
    RT_ASSERT(device != RT_NULL);

    if (hc32_rtc_init(device) != RT_EOK)
    {
        return -RT_ERROR;
    }
#ifdef RT_USING_DEVICE_OPS
    device->ops         = &rtc_ops;
#else
    device->init        = RT_NULL;
    device->open        = RT_NULL;
    device->close       = RT_NULL;
    device->read        = RT_NULL;
    device->write       = RT_NULL;
    device->control     = hc32_rtc_control;
#endif
    device->type        = RT_Device_Class_RTC;
    device->rx_indicate = RT_NULL;
    device->tx_complete = RT_NULL;
    device->user_data   = RT_NULL;

    /* register a character device */
    return rt_device_register(device, name, flag);
}

int rt_hw_rtc_init(void)
{
    rt_err_t result;

    result = rt_hw_rtc_register(&rtc, "rtc", RT_DEVICE_FLAG_RDWR);
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
