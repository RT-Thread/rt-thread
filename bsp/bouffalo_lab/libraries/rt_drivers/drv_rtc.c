/*
 * Copyright (c) 2006-2023, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date         Author          Notes
 * 2023-03-13   wcx1024979076   the first version
 */

#include <rtdevice.h>
#include "board.h"
#include "drv_rtc.h"

#define DBG_TAG "DRV.RTC"
#define DBG_LVL DBG_WARNING
#include <rtdbg.h>

#ifdef RT_USING_RTC

static struct rt_device rtc;
static rt_uint32_t rtc_time;

static rt_err_t _rtc_open(rt_device_t dev, rt_uint16_t oflag)
{
    if (dev->rx_indicate != RT_NULL)
    {
        /* Open Interrupt */
    }

    return RT_EOK;
}

static rt_ssize_t _rtc_read(
    rt_device_t     dev,
    rt_off_t        pos,
    void*           buffer,
    rt_size_t       size)
{
    return 0;
}

static rt_err_t _rtc_control(rt_device_t dev, int cmd, void *args)
{
    RT_ASSERT(dev != RT_NULL);
    struct bflb_device_s* bflb_rtc = bflb_device_get_by_name("rtc");
    switch (cmd)
    {
    case RT_DEVICE_CTRL_RTC_GET_TIME:
        *(rt_uint32_t *)args = rtc_time + BFLB_RTC_TIME2SEC(bflb_rtc_get_time(bflb_rtc));
        break;

    case RT_DEVICE_CTRL_RTC_SET_TIME:
        rtc_time = *(rt_uint32_t *)args;
        bflb_rtc_set_time(bflb_rtc, 0);
        break;
    }

    return RT_EOK;
}

int rt_hw_rtc_init(void)
{
    int result = RT_EOK;

    struct bflb_device_s* bflb_rtc = bflb_device_get_by_name("rtc");
    bflb_rtc_set_time(bflb_rtc, 0);
    /* register rtc device */
    rtc.type        = RT_Device_Class_RTC;
    rtc.rx_indicate = RT_NULL;
    rtc.tx_complete = RT_NULL;
    rtc.init        = RT_NULL;
    rtc.open        = _rtc_open;
    rtc.close       = RT_NULL;
    rtc.read        = _rtc_read;
    rtc.write       = RT_NULL;
    rtc.control     = _rtc_control;
    rtc.user_data   = RT_NULL; /* no private */

    result = rt_device_register(&rtc, "rtc", RT_DEVICE_FLAG_RDWR);
    if(result != RT_EOK)
    {
        LOG_E("rtc device register fail.");
    }

    return result;
}

INIT_DEVICE_EXPORT(rt_hw_rtc_init);
#endif /* RT_USING_RTC */
