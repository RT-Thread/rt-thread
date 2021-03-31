/*
 * Copyright (c) 2006-2021, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2017-11-06     Haley        the first version
 */

#include <rtthread.h>
#include <rtdevice.h>
#include "am_mcu_apollo.h"
#include <sys/time.h>

#define XT              1
#define LFRC            2

#define RTC_CLK_SRC     XT

//connect am drv to rt drv.
static rt_err_t rt_rtc_open(rt_device_t dev, rt_uint16_t oflag)
{
    if (dev->rx_indicate != RT_NULL)
    {
        /* Open Interrupt */
    }

    return RT_EOK;
}

static rt_size_t rt_rtc_read(rt_device_t dev, rt_off_t pos, void* buffer, rt_size_t size)
{
    return 0;
}

static rt_err_t rt_rtc_control(rt_device_t dev, int cmd, void *args)
{
    time_t *time;
    struct tm time_temp;
    struct tm* time_new;
    am_hal_rtc_time_t hal_time;

    RT_ASSERT(dev != RT_NULL);
    rt_memset(&time_temp, 0, sizeof(struct tm));

    switch (cmd)
    {
        case RT_DEVICE_CTRL_RTC_GET_TIME:
            time = (time_t *)args;

            /* Get the current Time */
            am_hal_rtc_time_get(&hal_time);

            /* Years since 1900 : 0-99 range */
            time_temp.tm_year = hal_time.ui32Year + 2000 - 1900;
            /* Months *since* january 0-11 : RTC_Month_Date_Definitions 1 - 12 */
            time_temp.tm_mon = hal_time.ui32Month - 1;
            /* Day of the month 1-31 : 1-31 range */
            time_temp.tm_mday = hal_time.ui32DayOfMonth;
            /* Hours since midnight 0-23 : 0-23 range */
            time_temp.tm_hour = hal_time.ui32Hour;
            /* Minutes 0-59 : the 0-59 range */
            time_temp.tm_min = hal_time.ui32Minute;
            /* Seconds 0-59 : the 0-59 range */
            time_temp.tm_sec = hal_time.ui32Second;

            *time = timegm(&time_temp);

            break;

        case RT_DEVICE_CTRL_RTC_SET_TIME:
            time = (time_t *)args;
            time_new = gmtime(time);

            hal_time.ui32Hour = time_new->tm_hour;
            hal_time.ui32Minute = time_new->tm_min;
            hal_time.ui32Second = time_new->tm_sec;
            hal_time.ui32Hundredths = 00;
            hal_time.ui32Weekday = time_new->tm_wday;
            hal_time.ui32DayOfMonth = time_new->tm_mday;
            hal_time.ui32Month = time_new->tm_mon + 1;
            hal_time.ui32Year = time_new->tm_year + 1900 - 2000;
            hal_time.ui32Century = 0;

            am_hal_rtc_time_set(&hal_time);

            break;
    }

    return RT_EOK;
}

int rt_hw_rtc_init(void)
{
    static struct rt_device rtc;

#if RTC_CLK_SRC == LFRC
    /* Enable the LFRC for the RTC */
    am_hal_clkgen_osc_start(AM_HAL_CLKGEN_OSC_LFRC);

    /* Select LFRC for RTC clock source */
    am_hal_rtc_osc_select(AM_HAL_RTC_OSC_LFRC);
#endif

#if RTC_CLK_SRC == XT
    /* Enable the XT for the RTC */
    am_hal_clkgen_osc_start(AM_HAL_CLKGEN_OSC_XT);

    /* Select XT for RTC clock source */
    am_hal_rtc_osc_select(AM_HAL_RTC_OSC_XT);
#endif

    /* Enable the RTC */
    am_hal_rtc_osc_enable();

    /* register rtc device */
    rtc.type    = RT_Device_Class_RTC;
    rtc.init    = RT_NULL;
    rtc.open    = rt_rtc_open;
    rtc.close   = RT_NULL;
    rtc.read    = rt_rtc_read;
    rtc.write   = RT_NULL;
    rtc.control = rt_rtc_control;

    /* no private */
    rtc.user_data = RT_NULL;

    rt_device_register(&rtc, "rtc", RT_DEVICE_FLAG_RDWR);

    return 0;
}
#ifdef RT_USING_COMPONENTS_INIT
INIT_BOARD_EXPORT(rt_hw_rtc_init);
#endif

/*@}*/
