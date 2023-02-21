/*
 * Copyright (c) 2006-2022, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date         Author      Notes
 * 2018-05-05   sundm75     first version
 */

/* Includes ------------------------------------------------------------------*/
#include "board.h"
#include "drv_rtc.h"
#include <rtdevice.h>
#include <sys/time.h>

#include "../libraries/ls1c_regs.h"
#include "../libraries/ls1c_rtc.h"

//#define RT_RTC_DEBUG

#if defined(RT_USING_RTC)
#ifdef RT_RTC_DEBUG
#define rtc_debug(format,args...)           rt_kprintf(format, ##args)
#else
#define rtc_debug(format,args...)
#endif

static struct rt_device rtc;

RTC_TypeDef * RTC_Handler;

static time_t get_timestamp(void)
{
    struct tm tm_new = {0};
    RTC_TimeTypeDef rtcDate;

    RTC_GetTime(RTC_Handler, &rtcDate);

    tm_new.tm_sec  = rtcDate.Seconds;
    tm_new.tm_min  = rtcDate.Minutes;
    tm_new.tm_hour = rtcDate.Hours;

    tm_new.tm_mday = rtcDate.Date;
    tm_new.tm_mon  = rtcDate.Month- 1;
    tm_new.tm_year = rtcDate.Year + 2000 - 1900;

    return timegm(&tm_new);
}

static int set_timestamp(time_t timestamp)
{
    struct tm now;
    RTC_TimeTypeDef rtcDate;

    gmtime_r(&timestamp, &now);

    rtcDate.Seconds= now.tm_sec ;
    rtcDate.Minutes= now.tm_min ;
    rtcDate.Hours= now.tm_hour;

    rtcDate.Date= now.tm_mday;
    rtcDate.Month= now.tm_mon  + 1;
    rtcDate.Year= now.tm_year + 1900 - 2000;

    RTC_SetTime(RTC_Handler, &rtcDate);
    rt_kprintf("\r\nrtcDate is %d.%d.%d - %d:%d:%d",rtcDate.Year, rtcDate.Month, rtcDate.Date, rtcDate.Hours, rtcDate.Minutes, rtcDate.Seconds);
    return RT_EOK;
}

rt_uint8_t RTC_Init(void)
{
    RTC_Handler = RTC;
    return 0;
}

static rt_err_t rt_rtc_open(rt_device_t dev, rt_uint16_t oflag)
{
    if (dev->rx_indicate != RT_NULL)
    {
        /* Open Interrupt */
    }

    return RT_EOK;
}

static rt_ssize_t rt_rtc_read(
    rt_device_t     dev,
    rt_off_t        pos,
    void*           buffer,
    rt_size_t       size)
{

    return 0;
}

 /**
 * This function configure RTC device.
 *
 * @param dev, pointer to device descriptor.
 * @param cmd, RTC control command.
 *
 * @return the error code.
 */
static rt_err_t rt_rtc_control(rt_device_t dev, int cmd, void *args)
{
    rt_err_t result;
    RT_ASSERT(dev != RT_NULL);
    switch (cmd)
    {
    case RT_DEVICE_CTRL_RTC_GET_TIME:

        *(rt_uint32_t *)args = get_timestamp();
        rtc_debug("RTC: get rtc_time %x\n", *(rt_uint32_t *)args);
        break;

    case RT_DEVICE_CTRL_RTC_SET_TIME:
    {
        result = set_timestamp(*(rt_uint32_t *)args);
        rtc_debug("RTC: set rtc_time %x\n", *(rt_uint32_t *)args);
    }
    break;
    }

    return result;
}

 /**
 * This function register RTC device.
 *
 * @param device, pointer to device descriptor.
 * @param name, device name.
 * @param flag, configuration flags.
 *
 * @return the error code.
 */
rt_err_t rt_hw_rtc_register(
    rt_device_t     device,
    const char      *name,
    rt_uint32_t     flag)
{
    RT_ASSERT(device != RT_NULL);

    device->type        = RT_Device_Class_RTC;
    device->rx_indicate = RT_NULL;
    device->tx_complete = RT_NULL;
    device->init        = RT_NULL;
    device->open        = rt_rtc_open;
    device->close       = RT_NULL;
    device->read        = rt_rtc_read;
    device->write       = RT_NULL;
    device->control     = rt_rtc_control;
    device->user_data   = RT_NULL; /* no private */

    /* register a character device */
    return rt_device_register(device, name, RT_DEVICE_FLAG_RDWR | flag);
}

 /**
 * This function initialize RTC module related hardware and register RTC device to kernel.
 *
 * @param none.
 *
 * @return the error code.
 */
int  rt_hw_rtc_init(void)
{
    RTC_Init();
    /* register rtc device */
    rt_hw_rtc_register(&rtc, RT_RTC_NAME, 0);
    return RT_EOK;
}
INIT_BOARD_EXPORT(rt_hw_rtc_init);
#endif




