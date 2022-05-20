/*
 * Copyright (C) 2020, Huada Semiconductor Co., Ltd.
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author             Notes
 * 2022-05-09     xiaoxiaolisunny    first version
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
    stc_rtc_date_time_t  stcRtcDateTime = {0};
    struct tm tm_new = {0};

    RTC_GetDateTime(RtcDataFormatDec, &stcRtcDateTime);

    tm_new.tm_sec  = stcRtcDateTime.u8Second;
    tm_new.tm_min  = stcRtcDateTime.u8Minute;
    tm_new.tm_hour = stcRtcDateTime.u8Hour;
    tm_new.tm_mday = stcRtcDateTime.u8Day;
    tm_new.tm_mon  = stcRtcDateTime.u8Month - 1;
    tm_new.tm_year = stcRtcDateTime.u8Year + 100;
    tm_new.tm_wday = stcRtcDateTime.u8Weekday;

    LOG_D("get rtc time.");
    return timegm(&tm_new);
}

static rt_err_t hc32_rtc_set_time_stamp(time_t time_stamp)
{
    stc_rtc_date_time_t  stcRtcDateTime = {0};
    struct tm *p_tm;

    p_tm = gmtime(&time_stamp);
    if (p_tm->tm_year < 100)
    {
        return -RT_ERROR;
    }

    stcRtcDateTime.u8Second  = p_tm->tm_sec ;
    stcRtcDateTime.u8Minute  = p_tm->tm_min ;
    stcRtcDateTime.u8Hour    = p_tm->tm_hour;
    stcRtcDateTime.u8Day     = p_tm->tm_mday;
    stcRtcDateTime.u8Month   = p_tm->tm_mon + 1 ;
    stcRtcDateTime.u8Year    = p_tm->tm_year - 100;
    stcRtcDateTime.u8Weekday = p_tm->tm_wday;

    if (Ok != RTC_SetDateTime(RtcDataFormatDec, &stcRtcDateTime, Enable, Enable))
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
    stc_clk_xtal32_cfg_t stcXtal32Cfg;
    /* Xtal32 config */
    CLK_Xtal32Cmd(Disable);//stop xtal32
    stcXtal32Cfg.enDrv = ClkXtal32HighDrv;
    stcXtal32Cfg.enFilterMode = ClkXtal32FilterModeFull;
    CLK_Xtal32Config(&stcXtal32Cfg);
    CLK_Xtal32Cmd(Enable);//startup xtal32

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
        stcRtcInit.enPeriodInt = RtcPeriodIntOneMin;
        //stcRtcInit.enTimeFormat = RtcTimeFormat24Hour;
        stcRtcInit.enCompenWay = RtcOutputCompenDistributed;
        stcRtcInit.enCompenEn = Disable;
        stcRtcInit.u16CompenVal = 0u;
        /* Configuration RTC structure */
#ifdef BSP_RTC_USING_XTAL32
        stcRtcInit.enClkSource = RtcClkXtal32;
#else
        stcRtcInit.enClkSource = RtcClkLrc;
#endif
        stcRtcInit.enTimeFormat  = RtcTimeFormat24Hour;
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
