/*
 * Copyright (c) 2006-2021, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date         Author        Notes
 * 2020-09-08   Chenyingchun  first version
 */

#include "board.h"
#include <rtthread.h>
#include <rtdevice.h>
#include <sys/time.h>
#include <nrfx_rtc.h>
#include <nrfx_clock.h>

#ifdef BSP_USING_ONCHIP_RTC

#define LOG_TAG             "drv.rtc"
#define DBG_LVL              DBG_LOG
#include <rtdbg.h>

/* 2018-01-30 14:44:50 = RTC_TIME_INIT(2018, 1, 30, 14, 44, 50)  */
#define RTC_TIME_INIT(year, month, day, hour, minute, second)        \
    {.tm_year = year - 1900, .tm_mon = month - 1, .tm_mday = day, .tm_hour = hour, .tm_min = minute, .tm_sec = second}

#ifndef ONCHIP_RTC_TIME_DEFAULT
#define ONCHIP_RTC_TIME_DEFAULT                    RTC_TIME_INIT(2018, 1, 1, 0, 0 ,0)
#endif

#ifndef RTC_INSTANCE_ID
#define RTC_INSTANCE_ID (2)
#endif

#define TICK_FREQUENCE_HZ        (RT_TICK_PER_SECOND)     // RTC tick frequence, in HZ

static struct rt_device rtc;
static time_t init_time;
static uint32_t tick = 0;

static void rtc_callback(nrfx_rtc_int_type_t int_type)
{
    static uint32_t count = 0;

    if (int_type == NRFX_RTC_INT_TICK)
    {
       count++;
       if((count % TICK_FREQUENCE_HZ) == 0)
       {
            tick++;
       }
    }
}

static rt_err_t rt_rtc_config(struct rt_device *dev)
{
    #define SYSTICK_CLOCK_HZ    (32768UL)
    #define RTC_PRESCALER       ((uint32_t) (NRFX_ROUNDED_DIV(SYSTICK_CLOCK_HZ, TICK_FREQUENCE_HZ) - 1))

    const nrfx_rtc_t rtc_instance = NRFX_RTC_INSTANCE(RTC_INSTANCE_ID);
    nrf_clock_lf_src_set(NRF_CLOCK, (nrf_clock_lfclk_t)NRFX_CLOCK_CONFIG_LF_SRC);
    nrfx_clock_lfclk_start();

    //Initialize RTC instance
    nrfx_rtc_config_t config = NRFX_RTC_DEFAULT_CONFIG;
    config.prescaler = RTC_PRESCALER;

    nrfx_rtc_init(&rtc_instance, &config, rtc_callback);

    nrfx_rtc_tick_enable(&rtc_instance, true);

    //Power on RTC instance
    nrfx_rtc_enable(&rtc_instance);

    return RT_EOK;
}

static rt_err_t rt_rtc_control(rt_device_t dev, int cmd, void *args)
{
    time_t *time;
    RT_ASSERT(dev != RT_NULL);

    switch (cmd)
    {
        case RT_DEVICE_CTRL_RTC_GET_TIME:
        {
            time = (time_t *) args;
            *time = init_time + tick;
            break;
        }
        case RT_DEVICE_CTRL_RTC_SET_TIME:
        {
            time = (time_t *) args;
            init_time = *time - tick;
            break;
        }
    }
    return RT_EOK;
}


#ifdef RT_USING_DEVICE_OPS
const static struct rt_device_ops rtc_ops =
{
    RT_NULL,
    RT_NULL,
    RT_NULL,
    RT_NULL,
    RT_NULL,
    rt_rtc_control
};
#endif

static rt_err_t rt_hw_rtc_register(rt_device_t device, const char *name, rt_uint32_t flag)
{
    struct tm time_new = ONCHIP_RTC_TIME_DEFAULT;

    RT_ASSERT(device != RT_NULL);

    init_time = timegm(&time_new);
    if (rt_rtc_config(device) != RT_EOK)
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
    device->control     = rt_rtc_control;
#endif
    device->type        = RT_Device_Class_RTC;
    device->rx_indicate = RT_NULL;
    device->tx_complete = RT_NULL;
    device->user_data   = RT_NULL;

    /* register a character device */
    rt_device_register(device, name, flag);

    return RT_EOK;
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

#endif /* BSP_USING_ONCHIP_RTC */

