/*
 * COPYRIGHT (C) 2011-2021, Real-Thread Information Technology Ltd
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2021-06-11     iysheng      first version.
 */

#include <drivers/rtc_core.h>

#define TRY_DO_RTC_FUNC(rt_rtc_dev, func_name, args) \
    rt_rtc_dev->ops->func_name ?  rt_rtc_dev->ops->func_name(args) : -RT_EINVAL;

/*
 * This function initializes rtc_core
 */
static rt_err_t rt_rtc_core_init(struct rt_device *dev)
{
    rt_rtc_dev_t *rtc_core;

    RT_ASSERT(dev != RT_NULL);
    rtc_core = (rt_rtc_dev_t *)dev;
    if (rtc_core->ops->init)
    {
        return (rtc_core->ops->init());
    }

    return (-RT_ENOSYS);
}

static rt_err_t rt_rtc_core_open(struct rt_device *dev, rt_uint16_t oflag)
{
    return (RT_EOK);
}

static rt_err_t rt_rtc_core_close(struct rt_device *dev)
{
    /* Add close member function in rt_rtc_ops when need,
     * then call that function here.
     * */
    return (RT_EOK);
}

static rt_err_t rt_rtc_core_control(struct rt_device *dev,
                                    int              cmd,
                                    void             *args)
{
    rt_rtc_dev_t *rtc_core;
    rt_err_t ret = -RT_EINVAL;

    RT_ASSERT(dev != RT_NULL);
    rtc_core = (rt_rtc_dev_t *)dev;

    switch (cmd)
    {
        case RT_DEVICE_CTRL_RTC_GET_TIME:
            ret = TRY_DO_RTC_FUNC(rtc_core, get_secs, args);
            break;
        case RT_DEVICE_CTRL_RTC_SET_TIME:
            ret = TRY_DO_RTC_FUNC(rtc_core, set_secs, args);
            break;
        case RT_DEVICE_CTRL_RTC_GET_TIME_US:
            ret = TRY_DO_RTC_FUNC(rtc_core, get_usecs, args);
            break;
        case RT_DEVICE_CTRL_RTC_SET_TIME_US:
            ret = TRY_DO_RTC_FUNC(rtc_core, set_usecs, args);
            break;
        case RT_DEVICE_CTRL_RTC_GET_ALARM:
            ret = TRY_DO_RTC_FUNC(rtc_core, get_alarm, args);
            break;
        case RT_DEVICE_CTRL_RTC_SET_ALARM:
            ret = TRY_DO_RTC_FUNC(rtc_core, set_alarm, args);
            break;
        default:
            break;
    }

    return ret;
}
#ifdef RT_USING_DEVICE_OPS
const static struct rt_device_ops rtc_core_ops =
{
    rt_rtc_core_init,
    rt_rtc_core_open,
    rt_rtc_core_close,
    RT_NULL,
    RT_NULL,
    rt_rtc_core_control,
};
#endif

rt_err_t rt_rtc_dev_register(rt_rtc_dev_t *rtc,
                            const char    *name,
                            rt_uint32_t    flag,
                            void          *data)
{
    struct rt_device *device;
    RT_ASSERT(rtc != RT_NULL);

    device = &(rtc->parent);

    device->type        = RT_Device_Class_RTC;
    device->rx_indicate = RT_NULL;
    device->tx_complete = RT_NULL;

#ifdef RT_USING_DEVICE_OPS
    device->ops         = &rtc_core_ops;
#else
    device->init        = rt_rtc_core_init;
    device->open        = rt_rtc_core_open;
    device->close       = rt_rtc_core_close;
    device->read        = RT_NULL;
    device->write       = RT_NULL;
    device->control     = rt_rtc_core_control;
#endif
    device->user_data   = data;

    /* register a character device */
    return rt_device_register(device, name, flag);
}

