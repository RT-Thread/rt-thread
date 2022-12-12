/*
 * Copyright (c) 2006-2022, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author         Notes
 * 2021-11-4      GuEe-GUI       first version
 * 2022-07-15     GuEe-GUI       add alarm ops support
 */

#include <rthw.h>
#include <rtthread.h>
#include <rtdevice.h>
#include <sys/time.h>
#include <board.h>

#include "drv_rtc.h"

#ifdef BSP_USING_RTC

#define RTC_DR      0x00    /* data read register */
#define RTC_MR      0x04    /* match register */
#define RTC_LR      0x08    /* data load register */
#define RTC_CR      0x0c    /* control register */
#define RTC_IMSC    0x10    /* interrupt mask and set register */
#define RTC_RIS     0x14    /* raw interrupt status register */
#define RTC_MIS     0x18    /* masked interrupt status register */
#define RTC_ICR     0x1c    /* interrupt clear register */

#define RTC_CR_OPEN     1
#define RTC_CR_CLOSE    0
#define RTC_BIT_AI      (1 << 0)    /* Alarm interrupt bit */
#define RTC_BIT_PI      (1 << 1)    /* Periodic interrupt bit. ST variants only. */

static rt_rtc_dev_t _rtc_device;
#ifdef RT_USING_ALARM
static struct rt_rtc_wkalarm _wkalarm;
#endif

rt_inline rt_uint32_t pl031_read32(rt_ubase_t offset)
{
    return (*((volatile unsigned int *)(PL031_RTC_BASE + offset)));
}

rt_inline void pl031_write32(rt_ubase_t offset, rt_uint32_t value)
{
    (*((volatile unsigned int *)(PL031_RTC_BASE + offset))) = value;
}

static rt_err_t pl031_rtc_init(void)
{
    pl031_write32(RTC_CR, RTC_CR_OPEN);

    return RT_EOK;
}

static rt_err_t pl031_get_secs(time_t *sec)
{
    if (sec != RT_NULL)
    {
        *(rt_uint32_t *)sec = pl031_read32(RTC_DR);

        return RT_EOK;
    }

    return -RT_EINVAL;
}

static rt_err_t pl031_set_secs(time_t *sec)
{
    if (sec != RT_NULL)
    {
        pl031_write32(RTC_LR, *(rt_uint32_t *)sec);

        return RT_EOK;
    }

    return -RT_EINVAL;
}

#ifdef RT_USING_ALARM
static rt_err_t pl031_set_alarm(struct rt_rtc_wkalarm *alarm)
{
    if (alarm != RT_NULL)
    {
        rt_uint32_t imsc, time;

        _wkalarm.enable = alarm->enable;
        _wkalarm.tm_hour = alarm->tm_hour;
        _wkalarm.tm_min = alarm->tm_min;
        _wkalarm.tm_sec = alarm->tm_sec;

        time = pl031_read32(RTC_DR);

        /* Back to 08:00 today */
        time = time / (3600 * 24) * (3600 * 24);

        /* Get alarm time */
        time += alarm->tm_hour * 3600 + alarm->tm_min * 60 + alarm->tm_sec;

        pl031_write32(RTC_MR, time);

        /* Clear any pending alarm interrupts. */
        pl031_write32(RTC_ICR, RTC_BIT_AI);

        imsc = pl031_read32(RTC_IMSC);

        if (alarm->enable)
        {
            pl031_write32(RTC_IMSC, imsc | RTC_BIT_AI);
        }
        else
        {
            pl031_write32(RTC_IMSC, imsc & ~RTC_BIT_AI);
        }

        return RT_EOK;
    }

    return -RT_EINVAL;
}

static rt_err_t pl031_get_alarm(struct rt_rtc_wkalarm *alarm)
{
    if (alarm != RT_NULL)
    {
        *alarm = _wkalarm;

        return RT_EOK;
    }

    return -RT_EINVAL;
}
#endif /* RT_USING_ALARM */

static rt_err_t pl031_get_timeval(struct timeval *tv)
{
    if (tv != RT_NULL)
    {
        tv->tv_sec = pl031_read32(RTC_DR);

        return RT_EOK;
    }

    return -RT_EINVAL;
}

static rt_err_t pl031_set_timeval(struct timeval *tv)
{
    if (tv != RT_NULL)
    {
        pl031_write32(RTC_LR, *(rt_uint32_t *)tv->tv_sec);

        return RT_EOK;
    }

    return -RT_EINVAL;
}

static const struct rt_rtc_ops rtc_ops =
{
    .init       = pl031_rtc_init,
    .get_secs   = pl031_get_secs,
    .set_secs   = pl031_set_secs,
#ifdef RT_USING_ALARM
    .get_alarm  = pl031_get_alarm,
    .set_alarm  = pl031_set_alarm,
#else
    .get_alarm  = RT_NULL,
    .set_alarm  = RT_NULL,
#endif
    .get_timeval = pl031_get_timeval,
    .set_timeval = pl031_set_timeval,
};

#ifdef RT_USING_ALARM
static void rt_hw_rtc_isr(int irqno, void *param)
{
    rt_uint32_t rtcmis = pl031_read32(RTC_MIS);

    if (rtcmis & RTC_BIT_AI)
    {
        pl031_write32(RTC_ICR, RTC_BIT_AI);

        rt_alarm_update(&_rtc_device.parent, 1);
    }
}
#endif /* RT_USING_ALARM */

int rt_hw_rtc_init(void)
{
    _rtc_device.ops = &rtc_ops;

    /* register a rtc device */
    rt_hw_rtc_register(&_rtc_device, "rtc", RT_DEVICE_FLAG_RDWR, RT_NULL);

#ifdef RT_USING_ALARM
    rt_hw_interrupt_install(PL031_RTC_IRQNUM, rt_hw_rtc_isr, RT_NULL, "rtc");
    rt_hw_interrupt_umask(PL031_RTC_IRQNUM);
#endif /* RT_USING_ALARM */

    return 0;
}
INIT_DEVICE_EXPORT(rt_hw_rtc_init);
#endif /* BSP_USING_RTC */
