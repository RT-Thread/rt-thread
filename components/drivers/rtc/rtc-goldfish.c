/*
 * Copyright (c) 2006-2022, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2022-11-26     GuEe-GUI     first version
 */

#include "rtc_dm.h"

#define GOLDFISH_RTC_TIME_LOW           0x00 /* get low bits of current time and update GOLDFISH_RTC_TIME_HIGH */
#define GOLDFISH_RTC_TIME_HIGH          0x04 /* get high bits of time at last GOLDFISH_RTC_TIME_LOW read */
#define GOLDFISH_RTC_ALARM_LOW          0x08 /* set low bits of alarm and activate it */
#define GOLDFISH_RTC_ALARM_HIGH         0x0c /* set high bits of next alarm */
#define GOLDFISH_RTC_IRQ_ENABLED        0x10 /* enable alarm interrupt */
#define GOLDFISH_RTC_CLEAR_ALARM        0x14 /* disarm an existing alarm */
#define GOLDFISH_RTC_ALARM_STATUS       0x18 /* alarm status (running or not) */
#define GOLDFISH_RTC_CLEAR_INTERRUPT    0x1c /* clear interrupt */

#define NSEC_PER_SEC    1000000000L

struct goldfish_rtc
{
    struct rt_device parent;

    int irq;
    void *base;

    struct rt_rtc_wkalarm wkalarm;
};

#define raw_to_goldfish_rtc(raw) rt_container_of(raw, struct goldfish_rtc, parent)

rt_inline rt_uint32_t goldfish_rtc_read(struct goldfish_rtc *grtc, int offset)
{
    return HWREG32(grtc->base + offset);
}

rt_inline void goldfish_rtc_write(struct goldfish_rtc *grtc, int offset, rt_uint32_t value)
{
    HWREG32(grtc->base + offset) = value;
}

static void goldfish_rtc_isr(int irqno, void *param)
{
    struct goldfish_rtc *grtc = param;

    goldfish_rtc_write(grtc, GOLDFISH_RTC_CLEAR_INTERRUPT, 1);

    rt_alarm_update(&grtc->parent, 1);
}

static void goldfish_rtc_get_secs(struct goldfish_rtc *grtc, time_t *sec)
{
    rt_uint64_t time = goldfish_rtc_read(grtc, GOLDFISH_RTC_TIME_LOW);

    if (sizeof(*sec) >= sizeof(rt_uint64_t))
    {
        rt_uint64_t time_high = goldfish_rtc_read(grtc, GOLDFISH_RTC_TIME_HIGH);

        time |= time_high << 32;
    }

    rt_do_div(time, NSEC_PER_SEC);

    rt_memcpy(sec, &time, sizeof(*sec));
}

static void goldfish_rtc_set_secs(struct goldfish_rtc *grtc, time_t *sec)
{
    rt_uint64_t time = 0;

    rt_memcpy(&time, sec, sizeof(*sec));

    time *= NSEC_PER_SEC;

    goldfish_rtc_write(grtc, GOLDFISH_RTC_TIME_LOW, (rt_uint32_t)(time & RT_UINT32_MAX));

    if (sizeof(*sec) >= sizeof(rt_uint64_t))
    {
        goldfish_rtc_write(grtc, GOLDFISH_RTC_TIME_HIGH, (rt_uint32_t)(time >> 32));
    }
}

static void goldfish_rtc_get_alarm(struct goldfish_rtc *grtc, struct rt_rtc_wkalarm *alarm)
{
    *alarm = grtc->wkalarm;

    if (goldfish_rtc_read(grtc, GOLDFISH_RTC_ALARM_STATUS))
    {
        alarm->enable = RT_TRUE;
    }
    else
    {
        alarm->enable = RT_FALSE;
    }
}

static void goldfish_rtc_set_alarm(struct goldfish_rtc *grtc, struct rt_rtc_wkalarm *alarm)
{
    struct rt_rtc_wkalarm *wkalarm = &grtc->wkalarm;

    wkalarm->enable = alarm->enable;
    wkalarm->tm_hour = alarm->tm_hour;
    wkalarm->tm_min = alarm->tm_min;
    wkalarm->tm_sec = alarm->tm_sec;

    if (alarm->enable)
    {
        rt_uint64_t time = alarm->tm_hour * 3600 + alarm->tm_min * 60 + alarm->tm_sec;

        time *= NSEC_PER_SEC;

        goldfish_rtc_write(grtc, GOLDFISH_RTC_ALARM_HIGH, (rt_uint32_t)(time >> 32));
        goldfish_rtc_write(grtc, GOLDFISH_RTC_ALARM_LOW, (rt_uint32_t)(time & RT_UINT32_MAX));

        goldfish_rtc_write(grtc, GOLDFISH_RTC_IRQ_ENABLED, 1);
    }
    else
    {
        if (goldfish_rtc_read(grtc, GOLDFISH_RTC_ALARM_STATUS))
        {
            goldfish_rtc_write(grtc, GOLDFISH_RTC_CLEAR_ALARM, 1);
        }

        goldfish_rtc_write(grtc, GOLDFISH_RTC_IRQ_ENABLED, 0);
    }
}

static rt_err_t goldfish_rtc_control(rt_device_t dev, int cmd, void *args)
{
    rt_err_t err = RT_EOK;
    struct goldfish_rtc *grtc = raw_to_goldfish_rtc(dev);

    if (!args)
    {
        return -RT_EINVAL;
    }

    switch (cmd)
    {
    case RT_DEVICE_CTRL_RTC_GET_TIME:
        goldfish_rtc_get_secs(grtc, args);
        break;

    case RT_DEVICE_CTRL_RTC_SET_TIME:
        goldfish_rtc_set_secs(grtc, args);
        break;

    case RT_DEVICE_CTRL_RTC_GET_TIMEVAL:
        goldfish_rtc_get_secs(grtc, (time_t *)&((struct timeval *)args)->tv_sec);
        break;

    case RT_DEVICE_CTRL_RTC_SET_TIMEVAL:
        goldfish_rtc_set_secs(grtc, (time_t *)&((struct timeval *)args)->tv_sec);
        break;

    case RT_DEVICE_CTRL_RTC_GET_ALARM:
        goldfish_rtc_get_alarm(grtc, args);
        break;

    case RT_DEVICE_CTRL_RTC_SET_ALARM:
        goldfish_rtc_set_alarm(grtc, args);
        break;

    default:
        err = -RT_EINVAL;
        break;
    }

    return err;
}

#ifdef RT_USING_DEVICE_OPS
const static struct rt_device_ops goldfish_rtc_ops =
{
    .control = goldfish_rtc_control,
};
#endif

static rt_err_t goldfish_rtc_probe(struct rt_platform_device *pdev)
{
    rt_err_t err = RT_EOK;
    const char *dev_name;
    struct rt_device *dev = &pdev->parent;
    struct goldfish_rtc *grtc = rt_calloc(1, sizeof(*grtc));

    if (!grtc)
    {
        return -RT_ENOMEM;
    }

    grtc->base = rt_dm_dev_iomap(dev, 0);

    if (!grtc->base)
    {
        err = -RT_EIO;
        goto _fail;
    }

    grtc->irq = rt_dm_dev_get_irq(dev, 0);

    if (grtc->irq < 0)
    {
        err = grtc->irq;
        goto _fail;
    }

    dev->user_data = grtc;

    grtc->parent.type = RT_Device_Class_RTC;
#ifdef RT_USING_DEVICE_OPS
    grtc->parent.ops = &goldfish_rtc_ops;
#else
    grtc->parent.control = goldfish_rtc_control;
#endif

    rtc_dev_set_name(&grtc->parent);
    dev_name = rt_dm_dev_get_name(&grtc->parent);
    rt_device_register(&grtc->parent, dev_name, RT_DEVICE_FLAG_RDWR);

    rt_hw_interrupt_install(grtc->irq, goldfish_rtc_isr, grtc, "rtc-goldfish");
    rt_hw_interrupt_umask(grtc->irq);

    return RT_EOK;

_fail:
    if (grtc->base)
    {
        rt_iounmap(grtc->base);
    }

    rt_free(grtc);

    return err;
}

static rt_err_t goldfish_rtc_remove(struct rt_platform_device *pdev)
{
    struct goldfish_rtc *grtc = pdev->parent.user_data;

    rt_hw_interrupt_mask(grtc->irq);
    rt_pic_detach_irq(grtc->irq, grtc);

    rt_device_unregister(&grtc->parent);

    rt_iounmap(grtc->base);

    rt_free(grtc);

    return RT_EOK;
}

static const struct rt_ofw_node_id goldfish_rtc_ofw_ids[] =
{
    { .compatible = "google,goldfish-rtc" },
    { /* sentinel */ }
};

static struct rt_platform_driver goldfish_rtc_driver =
{
    .name = "rtc-goldfish",
    .ids = goldfish_rtc_ofw_ids,

    .probe = goldfish_rtc_probe,
    .remove = goldfish_rtc_remove,
};
RT_PLATFORM_DRIVER_EXPORT(goldfish_rtc_driver);
