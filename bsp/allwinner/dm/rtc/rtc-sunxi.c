/*
 * Copyright (c) 2006-2026, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#include <rthw.h>
#include <rtthread.h>
#include <rtdevice.h>

#define DBG_TAG "rtc.sunxi"
#define DBG_LVL DBG_INFO
#include <rtdbg.h>

#include <time.h>

#define SUNXI_RTC_LOSC_CTRL            0x000
#define SUNXI_RTC_YMD                  0x010
#define SUNXI_RTC_HMS                  0x014
#define SUNXI_RTC_ALRM_DAY             0x020
#define SUNXI_RTC_ALRM_HMS             0x024
#define SUNXI_RTC_ALRM_EN              0x028
#define SUNXI_RTC_ALRM_IRQ_EN          0x02c
#define SUNXI_RTC_ALRM_IRQ_STA         0x030

#define SUNXI_RTC_HMS_ACC              RT_BIT(8)
#define SUNXI_RTC_YMD_ACC              RT_BIT(7)
#define SUNXI_RTC_ALRM_EN_COUNTER      RT_BIT(0)
#define SUNXI_RTC_ALRM_IRQ_COUNTER     RT_BIT(0)

#define SUNXI_RTC_YEAR_MIN             1970
#define SUNXI_RTC_YEAR_MAX             2097
#define SUNXI_RTC_ALARM_MAX_DAYS       255

struct sunxi_rtc
{
    struct rt_device parent;

    void *base;
    int irq;
    struct rt_rtc_wkalarm alarm;
    rt_bool_t registered;
    rt_bool_t irq_attached;
    rt_bool_t day_zero;
#ifdef RT_CLK_SUN50I_H616
    struct rt_clk_node clocks;
    struct rt_clk_cell clock_cells[3];
    struct rt_clk_cell *cells[3];
    struct rt_spinlock clock_lock;
    rt_bool_t clocks_registered;
#endif
};

struct sunxi_rtc_soc_data
{
    rt_bool_t day_zero;
};

static const struct sunxi_rtc_soc_data sunxi_rtc_data = { 0 };
static const struct sunxi_rtc_soc_data sunxi_rtc_h616_data =
{
    .day_zero = RT_TRUE,
};

#define to_sunxi_rtc(raw) rt_container_of(raw, struct sunxi_rtc, parent)

#ifdef RT_CLK_SUN50I_H616
static rt_ubase_t h616_rtc_clock_rate(struct rt_clk_cell *cell,
        rt_ubase_t parent_rate)
{
    struct sunxi_rtc *rtc = cell->clk_np->priv;
    rt_uint32_t cal = HWREG32(rtc->base + 0x0c);
    rt_ubase_t iosc = (cal & RT_BIT(1)) ? cal >> 7 : 16000000;

    if (cell == &rtc->clock_cells[2])
    {
        return iosc;
    }
    if (cell == &rtc->clock_cells[1] &&
            (HWREG32(rtc->base + 0x60) & RT_GENMASK(2, 1)))
    {
        /* Fanout is switched to IOSC32K by enable, not a guessed PLL rate. */
        return 0;
    }
    return (cal & RT_BIT(0)) ? 32768 :
            iosc / 32 / ((HWREG32(rtc->base + 0x08) & 31) + 1);
}

static rt_err_t h616_rtc_clock_enable(struct rt_clk_cell *cell)
{
    struct sunxi_rtc *rtc = cell->clk_np->priv;
    rt_base_t level = rt_spin_lock_irqsave(&rtc->clock_lock);

    HWREG32(rtc->base + 0x160) |= RT_BIT(0);
    if (cell == &rtc->clock_cells[1])
    {
        rt_uint32_t value = HWREG32(rtc->base + 0x60);
        HWREG32(rtc->base + 0x60) = (value & ~RT_GENMASK(2, 1)) | RT_BIT(0);
    }
    rt_spin_unlock_irqrestore(&rtc->clock_lock, level);
    return RT_EOK;
}

static void h616_rtc_clock_disable(struct rt_clk_cell *cell)
{
    struct sunxi_rtc *rtc = cell->clk_np->priv;
    rt_base_t level = rt_spin_lock_irqsave(&rtc->clock_lock);

    /* IOSC also supplies the RTC and must stay running. */
    if (cell == &rtc->clock_cells[1])
    {
        HWREG32(rtc->base + 0x60) &= ~RT_BIT(0);
    }
    rt_spin_unlock_irqrestore(&rtc->clock_lock, level);
}

static const struct rt_clk_ops h616_rtc_clock_ops =
{
    .recalc_rate = h616_rtc_clock_rate,
    .enable = h616_rtc_clock_enable,
    .disable = h616_rtc_clock_disable,
};

static rt_err_t h616_rtc_register_clocks(struct sunxi_rtc *rtc,
        struct rt_device *dev)
{
    static const char * const names[] =
    {
        "h616-osc32k", "h616-osc32k-out", "h616-iosc",
    };
    unsigned int index;

    rt_spin_lock_init(&rtc->clock_lock);
    rtc->clocks.dev = dev;
    rtc->clocks.priv = rtc;
    rtc->clocks.cells = rtc->cells;
    rtc->clocks.cells_nr = RT_ARRAY_SIZE(rtc->cells);
    /* No dependency on main/R CCU: both CCUs depend on this provider. */
    rtc->clocks.parents_clk = rt_err_ptr(-RT_ENOSYS);
    for (index = 0; index < RT_ARRAY_SIZE(rtc->cells); ++index)
    {
        rtc->clock_cells[index].name = names[index];
        rtc->clock_cells[index].ops = &h616_rtc_clock_ops;
        rtc->clock_cells[index].flags = RT_CLK_F_GET_RATE_NOCACHE;
        rtc->cells[index] = &rtc->clock_cells[index];
    }
    return rt_clk_register(&rtc->clocks);
}
#endif

static rt_uint32_t sunxi_rtc_read(struct sunxi_rtc *rtc, rt_size_t offset)
{
    return HWREG32(rtc->base + offset);
}

static void sunxi_rtc_write(struct sunxi_rtc *rtc, rt_size_t offset,
        rt_uint32_t value)
{
    HWREG32(rtc->base + offset) = value;
}

static rt_bool_t sunxi_rtc_is_leap_year(int year)
{
    return !(year % 4) && ((year % 100) || !(year % 400));
}

static int sunxi_rtc_days_in_month(int year, int month)
{
    static const rt_uint8_t days[] =
    {
        31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31,
    };

    if (month == 1 && sunxi_rtc_is_leap_year(year))
    {
        return 29;
    }

    return days[month];
}

static rt_err_t sunxi_rtc_tm_to_day(const struct tm *tm, rt_uint32_t *day)
{
    int year = tm->tm_year + 1900;
    int month = tm->tm_mon;
    int index;
    rt_uint32_t result = 0;

    if (year < SUNXI_RTC_YEAR_MIN || year > SUNXI_RTC_YEAR_MAX ||
            month < 0 || month >= 12 || tm->tm_mday < 1 ||
            tm->tm_mday > sunxi_rtc_days_in_month(year, month) ||
            tm->tm_hour < 0 || tm->tm_hour > 23 ||
            tm->tm_min < 0 || tm->tm_min > 59 ||
            tm->tm_sec < 0 || tm->tm_sec > 59)
    {
        return -RT_EINVAL;
    }

    for (index = SUNXI_RTC_YEAR_MIN; index < year; ++index)
    {
        result += sunxi_rtc_is_leap_year(index) ? 366 : 365;
    }
    for (index = 0; index < month; ++index)
    {
        result += sunxi_rtc_days_in_month(year, index);
    }

    *day = result + tm->tm_mday;
    return RT_EOK;
}

static rt_err_t sunxi_rtc_day_to_tm(rt_uint32_t day, struct tm *tm)
{
    int year = SUNXI_RTC_YEAR_MIN;
    int month = 0;
    int days;

    if (!day)
    {
        return -RT_EINVAL;
    }

    --day;
    while (year <= SUNXI_RTC_YEAR_MAX)
    {
        days = sunxi_rtc_is_leap_year(year) ? 366 : 365;
        if (day < (rt_uint32_t)days)
        {
            break;
        }
        day -= days;
        ++year;
    }
    if (year > SUNXI_RTC_YEAR_MAX)
    {
        return -RT_EINVAL;
    }

    while (month < 12)
    {
        days = sunxi_rtc_days_in_month(year, month);
        if (day < (rt_uint32_t)days)
        {
            break;
        }
        day -= days;
        ++month;
    }

    tm->tm_year = year - 1900;
    tm->tm_mon = month;
    tm->tm_mday = day + 1;
    return RT_EOK;
}

static rt_err_t sunxi_rtc_read_tm(struct sunxi_rtc *rtc, struct tm *tm,
        rt_uint32_t *day)
{
    rt_uint32_t ymd;
    rt_uint32_t hms;
    int retry;
    rt_err_t err;

    for (retry = 0; retry < 3; ++retry)
    {
        ymd = sunxi_rtc_read(rtc, SUNXI_RTC_YMD);
        hms = sunxi_rtc_read(rtc, SUNXI_RTC_HMS);
        if (ymd == sunxi_rtc_read(rtc, SUNXI_RTC_YMD) &&
                hms == sunxi_rtc_read(rtc, SUNXI_RTC_HMS))
        {
            break;
        }
    }

    if (retry == 3)
    {
        return -RT_EIO;
    }
    /* Keep the internal helpers one-based, matching the F101 interface. */
    if (rtc->day_zero)
    {
        ymd = (ymd & 0xffff) + 1;
    }
    err = sunxi_rtc_day_to_tm(ymd, tm);
    if (err)
    {
        return err;
    }

    tm->tm_sec = hms & 0x3f;
    tm->tm_min = (hms >> 8) & 0x3f;
    tm->tm_hour = (hms >> 16) & 0x1f;
    if (tm->tm_sec > 59 || tm->tm_min > 59 || tm->tm_hour > 23)
    {
        return -RT_EINVAL;
    }

    if (day)
    {
        *day = ymd;
    }
    return RT_EOK;
}

static rt_err_t sunxi_rtc_wait_ready(struct sunxi_rtc *rtc, rt_uint32_t mask)
{
    int retry;

    for (retry = 0; retry < 1000; ++retry)
    {
        if (!(sunxi_rtc_read(rtc, SUNXI_RTC_LOSC_CTRL) & mask))
        {
            return RT_EOK;
        }
        rt_hw_us_delay(1000);
    }

    return -RT_ETIMEOUT;
}

static rt_err_t sunxi_rtc_write_tm(struct sunxi_rtc *rtc, const struct tm *tm)
{
    rt_uint32_t day;
    rt_uint32_t hms;
    rt_err_t err;

    if ((err = sunxi_rtc_tm_to_day(tm, &day)))
    {
        return err;
    }

    hms = tm->tm_sec | ((rt_uint32_t)tm->tm_min << 8) |
            ((rt_uint32_t)tm->tm_hour << 16);
    if ((err = sunxi_rtc_wait_ready(rtc, SUNXI_RTC_HMS_ACC)))
    {
        return err;
    }
    sunxi_rtc_write(rtc, SUNXI_RTC_HMS, hms);

    if ((err = sunxi_rtc_wait_ready(rtc, SUNXI_RTC_YMD_ACC)))
    {
        return err;
    }
    sunxi_rtc_write(rtc, SUNXI_RTC_YMD, day - rtc->day_zero);

    return sunxi_rtc_wait_ready(rtc, SUNXI_RTC_HMS_ACC | SUNXI_RTC_YMD_ACC);
}

static rt_err_t sunxi_rtc_get_secs(struct sunxi_rtc *rtc, time_t *secs)
{
    struct tm tm = {0};
    rt_uint32_t day;
    rt_uint64_t value;
    rt_err_t err;

    if ((err = sunxi_rtc_read_tm(rtc, &tm, &day)))
    {
        return err;
    }

    value = ((rt_uint64_t)day - 1) * 86400 + tm.tm_hour * 3600 +
            tm.tm_min * 60 + tm.tm_sec;
    *secs = (time_t)value;
    return RT_EOK;
}

static rt_err_t sunxi_rtc_set_secs(struct sunxi_rtc *rtc, const time_t *secs)
{
    struct tm tm;

    if (!gmtime_r(secs, &tm))
    {
        return -RT_EINVAL;
    }

    return sunxi_rtc_write_tm(rtc, &tm);
}

static rt_err_t sunxi_rtc_get_alarm(struct sunxi_rtc *rtc,
        struct rt_rtc_wkalarm *alarm)
{
    *alarm = rtc->alarm;
    alarm->enable = !!(sunxi_rtc_read(rtc, SUNXI_RTC_ALRM_EN) &
            SUNXI_RTC_ALRM_EN_COUNTER);
    return RT_EOK;
}

static rt_err_t sunxi_rtc_set_alarm(struct sunxi_rtc *rtc,
        const struct rt_rtc_wkalarm *alarm)
{
    struct tm now = {0};
    struct tm target = {0};
    rt_uint32_t now_day;
    rt_uint32_t target_day;
    rt_uint32_t hms;
    rt_err_t err;

    if (!alarm->enable)
    {
        sunxi_rtc_write(rtc, SUNXI_RTC_ALRM_EN, 0);
        sunxi_rtc_write(rtc, SUNXI_RTC_ALRM_IRQ_EN, 0);
        sunxi_rtc_write(rtc, SUNXI_RTC_ALRM_IRQ_STA,
                SUNXI_RTC_ALRM_IRQ_COUNTER);
        rtc->alarm = *alarm;
        return RT_EOK;
    }

    target.tm_sec = alarm->tm_sec;
    target.tm_min = alarm->tm_min;
    target.tm_hour = alarm->tm_hour;
    target.tm_mday = alarm->tm_mday;
    target.tm_mon = alarm->tm_mon;
    target.tm_year = alarm->tm_year;
    if ((err = sunxi_rtc_tm_to_day(&target, &target_day)) ||
            (err = sunxi_rtc_read_tm(rtc, &now, &now_day)))
    {
        return err;
    }

    if (target_day < now_day || target_day - now_day >
            SUNXI_RTC_ALARM_MAX_DAYS ||
            (target_day == now_day &&
             (target.tm_hour < now.tm_hour ||
              (target.tm_hour == now.tm_hour && target.tm_min < now.tm_min) ||
              (target.tm_hour == now.tm_hour && target.tm_min == now.tm_min &&
               target.tm_sec <= now.tm_sec))))
    {
        return -RT_EINVAL;
    }

    hms = target.tm_sec | ((rt_uint32_t)target.tm_min << 8) |
            ((rt_uint32_t)target.tm_hour << 16);
    sunxi_rtc_write(rtc, SUNXI_RTC_ALRM_EN, 0);
    sunxi_rtc_write(rtc, SUNXI_RTC_ALRM_IRQ_EN, 0);
    sunxi_rtc_write(rtc, SUNXI_RTC_ALRM_IRQ_STA, SUNXI_RTC_ALRM_IRQ_COUNTER);
    sunxi_rtc_write(rtc, SUNXI_RTC_ALRM_DAY, target_day - rtc->day_zero);
    sunxi_rtc_write(rtc, SUNXI_RTC_ALRM_HMS, hms);
    sunxi_rtc_write(rtc, SUNXI_RTC_ALRM_IRQ_EN, SUNXI_RTC_ALRM_IRQ_COUNTER);
    sunxi_rtc_write(rtc, SUNXI_RTC_ALRM_EN, SUNXI_RTC_ALRM_EN_COUNTER);
    rtc->alarm = *alarm;

    return RT_EOK;
}

static rt_err_t sunxi_rtc_control(rt_device_t dev, int cmd, void *args)
{
    struct sunxi_rtc *rtc = to_sunxi_rtc(dev);

    if (!args)
    {
        return -RT_EINVAL;
    }

    switch (cmd)
    {
    case RT_DEVICE_CTRL_RTC_GET_TIME:
        return sunxi_rtc_get_secs(rtc, args);

    case RT_DEVICE_CTRL_RTC_SET_TIME:
        return sunxi_rtc_set_secs(rtc, args);

    case RT_DEVICE_CTRL_RTC_GET_TIMEVAL:
        ((struct timeval *)args)->tv_usec = 0;
        return sunxi_rtc_get_secs(rtc, (time_t *)&((struct timeval *)args)->tv_sec);

    case RT_DEVICE_CTRL_RTC_SET_TIMEVAL:
        return sunxi_rtc_set_secs(rtc, (time_t *)&((struct timeval *)args)->tv_sec);

    case RT_DEVICE_CTRL_RTC_GET_ALARM:
        return sunxi_rtc_get_alarm(rtc, args);

    case RT_DEVICE_CTRL_RTC_SET_ALARM:
        return sunxi_rtc_set_alarm(rtc, args);

    default:
        return -RT_EINVAL;
    }
}

#ifdef RT_USING_DEVICE_OPS
static const struct rt_device_ops sunxi_rtc_ops =
{
    .control = sunxi_rtc_control,
};
#endif

static void sunxi_rtc_isr(int irqno, void *parameter)
{
    struct sunxi_rtc *rtc = parameter;

    RT_UNUSED(irqno);
    if (sunxi_rtc_read(rtc, SUNXI_RTC_ALRM_IRQ_STA) &
            SUNXI_RTC_ALRM_IRQ_COUNTER)
    {
        sunxi_rtc_write(rtc, SUNXI_RTC_ALRM_IRQ_STA,
                SUNXI_RTC_ALRM_IRQ_COUNTER);
        sunxi_rtc_write(rtc, SUNXI_RTC_ALRM_EN, 0);
        sunxi_rtc_write(rtc, SUNXI_RTC_ALRM_IRQ_EN, 0);
        rtc->alarm.enable = RT_FALSE;
        rt_alarm_update(&rtc->parent, 1);
    }
}

static void sunxi_rtc_release(struct sunxi_rtc *rtc)
{
    if (rtc->irq_attached)
    {
        rt_pic_irq_mask(rtc->irq);
        rt_pic_detach_irq(rtc->irq, rtc);
    }
    if (rtc->registered)
    {
        rt_device_unregister(&rtc->parent);
    }
    if (rtc->base)
    {
        rt_iounmap(rtc->base);
    }
    rt_free(rtc);
}

static rt_err_t sunxi_rtc_probe(struct rt_platform_device *pdev)
{
    rt_err_t err;
    struct rt_device *dev = &pdev->parent;
    const struct sunxi_rtc_soc_data *soc_data = pdev->id->data;
    struct sunxi_rtc *rtc;

    if (!soc_data)
    {
        return -RT_EINVAL;
    }
    rtc = rt_calloc(1, sizeof(*rtc));
    if (!rtc)
    {
        return -RT_ENOMEM;
    }

    rtc->day_zero = soc_data->day_zero;
    rtc->base = rt_dm_dev_iomap(dev, 0);
    rtc->irq = rt_dm_dev_get_irq(dev, 0);
    if (!rtc->base || rtc->irq < 0)
    {
        err = rtc->irq < 0 ? rtc->irq : -RT_EIO;
        goto _fail;
    }

    rtc->parent.type = RT_Device_Class_RTC;
#ifdef RT_USING_DEVICE_OPS
    rtc->parent.ops = &sunxi_rtc_ops;
#else
    rtc->parent.control = sunxi_rtc_control;
#endif
    if ((err = rt_device_register(&rtc->parent, "rtc", RT_DEVICE_FLAG_RDWR)))
    {
        goto _fail;
    }
    rtc->registered = RT_TRUE;

    sunxi_rtc_write(rtc, SUNXI_RTC_ALRM_EN, 0);
    sunxi_rtc_write(rtc, SUNXI_RTC_ALRM_IRQ_EN, 0);
    sunxi_rtc_write(rtc, SUNXI_RTC_ALRM_IRQ_STA, SUNXI_RTC_ALRM_IRQ_COUNTER);
    if ((err = rt_pic_attach_irq(rtc->irq, sunxi_rtc_isr, rtc, "rtc", RT_IRQ_F_NONE)))
    {
        goto _fail;
    }
    rtc->irq_attached = RT_TRUE;
    rt_pic_irq_unmask(rtc->irq);

#ifdef RT_CLK_SUN50I_H616
    if (rtc->day_zero)
    {
        if ((err = h616_rtc_register_clocks(rtc, dev)))
        {
            goto _fail;
        }
        rtc->clocks_registered = RT_TRUE;
    }
#endif

    dev->user_data = rtc;
#ifdef RT_CLK_SUN50I_H616
    /*
     * The H616 RTC is also the LOSC/IOSC clock provider.  Keep its clock
     * node as the FDT data so the main and R CCUs can resolve those clocks.
     */
    if (!rtc->clocks_registered)
#endif
    {
        rt_dm_dev_bind_fwdata(dev, RT_NULL, rtc);
    }
    return RT_EOK;

_fail:
    sunxi_rtc_release(rtc);
    return err;
}

static rt_err_t sunxi_rtc_remove(struct rt_platform_device *pdev)
{
    struct rt_device *dev = &pdev->parent;
    struct sunxi_rtc *rtc = dev->user_data;

#ifdef RT_CLK_SUN50I_H616
    /* This oscillator is the root of the live bus-clock tree. */
    if (rtc->clocks_registered)
    {
        return -RT_EBUSY;
    }
#endif
    if (rt_device_unregister(&rtc->parent))
    {
        return -RT_EBUSY;
    }
    rtc->registered = RT_FALSE;

    rt_dm_dev_unbind_fwdata(dev, RT_NULL);
    sunxi_rtc_release(rtc);
    return RT_EOK;
}

static const struct rt_ofw_node_id sunxi_rtc_ofw_ids[] =
{
    { .compatible = "allwinner,sun252i-f101-rtc", .data = &sunxi_rtc_data },
    { .compatible = "allwinner,sun50i-h616-rtc", .data = &sunxi_rtc_h616_data },
    { /* sentinel */ }
};

static struct rt_platform_driver sunxi_rtc_driver =
{
    .name = "rtc-sunxi",
    .ids = sunxi_rtc_ofw_ids,
    .probe = sunxi_rtc_probe,
    .remove = sunxi_rtc_remove,
};
#ifdef RT_CLK_SUN50I_H616
static int sunxi_rtc_driver_register(void)
{
    return rt_platform_driver_register(&sunxi_rtc_driver);
}
/* H616 CCUs need this node's oscillator outputs during platform discovery. */
INIT_SUBSYS_EXPORT(sunxi_rtc_driver_register);
#else
RT_PLATFORM_DRIVER_EXPORT(sunxi_rtc_driver);
#endif
