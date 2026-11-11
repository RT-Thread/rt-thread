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

#define PL031_DR        0x00    /* data read register */
#define PL031_MR        0x04    /* match register */
#define PL031_LR        0x08    /* data load register */
#define PL031_CR        0x0c    /* control register */
#define PL031_IMSC      0x10    /* interrupt mask and set register */
#define PL031_RIS       0x14    /* raw interrupt status register */
#define PL031_MIS       0x18    /* masked interrupt status register */
#define PL031_ICR       0x1c    /* interrupt clear register */

#define PL031_CR_OPEN   1
#define PL031_CR_CLOSE  0
#define PL031_BIT_AI    RT_BIT(0)   /* Alarm interrupt bit */
#define PL031_BIT_PI    RT_BIT(1)   /* Periodic interrupt bit. ST variants only. */

struct pl031
{
    struct rt_device parent;

    int irq;
    void *base;
    struct rt_clk *pclk;

    struct rt_rtc_wkalarm wkalarm;
};

#define raw_to_pl031(raw) rt_container_of(raw, struct pl031, parent)

rt_inline rt_uint32_t pl031_read(struct pl031 *pl031, int offset)
{
    return HWREG32(pl031->base + offset);
}

rt_inline void pl031_write(struct pl031 *pl031, int offset, rt_uint32_t value)
{
    HWREG32(pl031->base + offset) = value;
}

static void pl031_isr(int irqno, void *param)
{
    struct pl031 *pl031 = param;
    rt_uint32_t rtcmis = pl031_read(pl031, PL031_MIS);

    if (rtcmis & PL031_BIT_AI)
    {
        pl031_write(pl031, PL031_ICR, PL031_BIT_AI);

        rt_alarm_update(&pl031->parent, 1);
    }
}

static void pl031_get_secs(struct pl031 *pl031, time_t *sec)
{
    *(rt_uint32_t *)sec = pl031_read(pl031, PL031_DR);
}

static void pl031_set_secs(struct pl031 *pl031, time_t *sec)
{
    pl031_write(pl031, PL031_LR, *(rt_uint32_t *)sec);
}

static void pl031_get_alarm(struct pl031 *pl031, struct rt_rtc_wkalarm *alarm)
{
    *alarm = pl031->wkalarm;

    alarm->enable = pl031_read(pl031, PL031_IMSC) & PL031_BIT_AI;
}

static void pl031_set_alarm(struct pl031 *pl031, struct rt_rtc_wkalarm *alarm)
{
    rt_uint32_t imsc, time;
    struct rt_rtc_wkalarm *wkalarm = &pl031->wkalarm;

    wkalarm->enable = alarm->enable;
    wkalarm->tm_hour = alarm->tm_hour;
    wkalarm->tm_min = alarm->tm_min;
    wkalarm->tm_sec = alarm->tm_sec;

    time = pl031_read(pl031, PL031_DR);

    /* Get alarm time */
    time += alarm->tm_hour * 3600 + alarm->tm_min * 60 + alarm->tm_sec;

    pl031_write(pl031, PL031_MR, time);

    /* Clear any pending alarm interrupts. */
    pl031_write(pl031, PL031_ICR, PL031_BIT_AI);

    imsc = pl031_read(pl031, PL031_IMSC);

    if (alarm->enable)
    {
        pl031_write(pl031, PL031_IMSC, imsc | PL031_BIT_AI);
    }
    else
    {
        pl031_write(pl031, PL031_IMSC, imsc & ~PL031_BIT_AI);
    }
}

static void pl031_get_timeval(struct pl031 *pl031, struct timeval *tv)
{
    tv->tv_sec = pl031_read(pl031, PL031_DR);
}

static void pl031_set_timeval(struct pl031 *pl031, struct timeval *tv)
{
    pl031_write(pl031, PL031_LR, *(rt_uint32_t *)&tv->tv_sec);
}

static rt_err_t pl031_init(rt_device_t dev)
{
    struct pl031 *pl031 = raw_to_pl031(dev);

    pl031_write(pl031, PL031_CR, PL031_CR_OPEN);

    return RT_EOK;
}

static rt_err_t pl031_control(rt_device_t dev, int cmd, void *args)
{
    rt_err_t err = RT_EOK;
    struct pl031 *pl031 = raw_to_pl031(dev);

    if (!args)
    {
        return -RT_EINVAL;
    }

    switch (cmd)
    {
    case RT_DEVICE_CTRL_RTC_GET_TIME:
        pl031_get_secs(pl031, args);
        break;

    case RT_DEVICE_CTRL_RTC_SET_TIME:
        pl031_set_secs(pl031, args);
        break;

    case RT_DEVICE_CTRL_RTC_GET_TIMEVAL:
        pl031_get_timeval(pl031, args);
        break;

    case RT_DEVICE_CTRL_RTC_SET_TIMEVAL:
        pl031_set_timeval(pl031, args);
        break;

    case RT_DEVICE_CTRL_RTC_GET_ALARM:
        pl031_get_alarm(pl031, args);
        break;

    case RT_DEVICE_CTRL_RTC_SET_ALARM:
        pl031_set_alarm(pl031, args);
        break;

    default:
        err = -RT_EINVAL;
        break;
    }

    return err;
}

#ifdef RT_USING_DEVICE_OPS
const static struct rt_device_ops pl031_rtc_ops =
{
    .init = pl031_init,
    .control = pl031_control,
};
#endif

static rt_err_t pl031_probe(struct rt_platform_device *pdev)
{
    rt_err_t err = RT_EOK;
    const char *dev_name;
    struct rt_device *dev = &pdev->parent;
    struct pl031 *pl031 = rt_calloc(1, sizeof(*pl031));

    if (!pl031)
    {
        return -RT_ENOMEM;
    }

    pl031->base = rt_dm_dev_iomap(dev, 0);

    if (!pl031->base)
    {
        err = -RT_EIO;

        goto _fail;
    }

    pl031->irq = rt_dm_dev_get_irq(dev, 0);

    if (pl031->irq < 0)
    {
        err = pl031->irq;

        goto _fail;
    }

    pl031->pclk = rt_clk_get_by_name(dev, "apb_pclk");

    if (rt_is_err(pl031->pclk))
    {
        err = rt_ptr_err(pl031->pclk);

        goto _fail;
    }

    if ((err = rt_clk_prepare_enable(pl031->pclk)))
    {
        goto _fail;
    }

    dev->user_data = pl031;

    pl031->parent.type = RT_Device_Class_RTC;
#ifdef RT_USING_DEVICE_OPS
    pl031->parent.ops = &pl031_rtc_ops;
#else
    pl031->parent.init = pl031_init;
    pl031->parent.control = pl031_control;
#endif

    rtc_dev_set_name(&pl031->parent);
    dev_name = rt_dm_dev_get_name(&pl031->parent);
    rt_device_register(&pl031->parent, dev_name, RT_DEVICE_FLAG_RDWR);

    rt_hw_interrupt_install(pl031->irq, pl031_isr, pl031, "rtc-pl031");
    rt_hw_interrupt_umask(pl031->irq);

    return RT_EOK;

_fail:
    if (pl031->base)
    {
        rt_iounmap(pl031->base);
    }

    if (!rt_is_err_or_null(pl031->pclk))
    {
        rt_clk_disable_unprepare(pl031->pclk);
        rt_clk_put(pl031->pclk);
    }

    rt_free(pl031);

    return err;
}

static rt_err_t pl031_remove(struct rt_platform_device *pdev)
{
    struct pl031 *pl031 = pdev->parent.user_data;

    rt_hw_interrupt_mask(pl031->irq);
    rt_pic_detach_irq(pl031->irq, pl031);

    rt_device_unregister(&pl031->parent);

    rt_clk_disable_unprepare(pl031->pclk);
    rt_clk_put(pl031->pclk);

    rt_free(pl031);

    return RT_EOK;
}

static const struct rt_ofw_node_id pl031_ofw_ids[] =
{
    { .compatible = "arm,pl031" },
    { /* sentinel */ }
};

static struct rt_platform_driver pl031_driver =
{
    .name = "rtc-pl031",
    .ids = pl031_ofw_ids,

    .probe = pl031_probe,
    .remove = pl031_remove,
};
RT_PLATFORM_DRIVER_EXPORT(pl031_driver);
