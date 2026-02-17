/*
 * Copyright (c) 2006-2022, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2022-12-06     GuEe-GUI     first version
 */

#include "rtc_dm.h"

#define TIMER_LOAD_COUNT0               0x00
#define TIMER_LOAD_COUNT1               0x04
#define TIMER_CURRENT_VALUE0            0x08
#define TIMER_CURRENT_VALUE1            0x0c
#define TIMER_CONTROL_REG3288           0x10
#define TIMER_INT_STATUS                0x18

#define TIMER_ENABLE                    RT_BIT(0)
#define TIMER_MODE_USER_DEFINED_COUNT   RT_BIT(1)
#define TIMER_INT_UNMASK                RT_BIT(2)

/* Forbid any alarms which would trigger inside the threshold */
#define TIMER_ALARM_THRESHOLD_MS        10
#define TIMER_COUNT_MAX                 ((rt_uint64_t)-1)

struct rk_timer_rtc_data
{
    int ctrl_reg_offset;
};

struct rk_timer_rtc
{
    struct rt_device parent;

    int irq;
    void *base;

    struct rt_clk *clk;
    struct rt_clk *pclk;

    rt_uint32_t freq;
    rt_uint64_t timebase;
    rt_bool_t alarm_irq_enabled;
    struct rt_rtc_wkalarm wkalarm;

    const struct rk_timer_rtc_data *soc_data;
};

#define raw_to_rk_timer_rtc(raw) rt_container_of(raw, struct rk_timer_rtc, parent)

rt_inline rt_uint64_t tick_to_sec(struct rk_timer_rtc *rk_rtc, rt_uint64_t tick)
{
    rt_do_div(tick, rk_rtc->freq);

    return tick;
}

rt_inline rt_uint64_t ms_to_tick(struct rk_timer_rtc *rk_rtc, int ms)
{
    return ms * rk_rtc->freq / 1000;
}

rt_inline rt_uint64_t tick_to_time64(struct rk_timer_rtc *rk_rtc, rt_uint64_t tick)
{
    return tick_to_sec(rk_rtc, tick) + rk_rtc->timebase;
}

rt_inline rt_uint64_t time64_to_tick(struct rk_timer_rtc *rk_rtc, rt_uint64_t time)
{
    return (time - rk_rtc->timebase) * rk_rtc->freq;
}

rt_inline void rk_timer_rtc_writel(struct rk_timer_rtc *rk_rtc, int offset, rt_uint32_t value)
{
    HWREG32(rk_rtc->base + offset) = value;
}

rt_inline rt_uint32_t rk_timer_rtc_readl(struct rk_timer_rtc *rk_rtc, int offset)
{
    return HWREG32(rk_rtc->base + offset);
}

rt_inline void rk_timer_rtc_writeq(struct rk_timer_rtc *rk_rtc, int offset, rt_uint64_t value)
{
    HWREG32(rk_rtc->base + offset) = value;
    HWREG32(rk_rtc->base + offset + 4) = value >> 32;
}

rt_inline rt_uint64_t rk_timer_rtc_readq(struct rk_timer_rtc *rk_rtc, int offset)
{
    rt_uint32_t val_lo, val_hi, tmp_hi;

    do {
        val_hi = HWREG32(rk_rtc->base + offset + 4);
        val_lo = HWREG32(rk_rtc->base + offset);
        tmp_hi = HWREG32(rk_rtc->base + offset + 4);
    } while (val_hi != tmp_hi);

    return ((rt_uint64_t) val_hi << 32) | val_lo;
}

rt_inline void rk_timer_rtc_irq_clear(struct rk_timer_rtc *rk_rtc)
{
    return rk_timer_rtc_writel(rk_rtc->base, TIMER_INT_STATUS, 1);
}

rt_inline void rk_timer_rtc_irq_enable(struct rk_timer_rtc *rk_rtc, rt_bool_t enabled)
{
    rt_uint32_t old_val;

    /* Clear any pending irq before enable it */
    if (enabled)
    {
        rk_timer_rtc_irq_clear(rk_rtc);
    }

    old_val = rk_timer_rtc_readl(rk_rtc, rk_rtc->soc_data->ctrl_reg_offset);
    old_val &= ~TIMER_INT_UNMASK;
    rk_timer_rtc_writel(rk_rtc, rk_rtc->soc_data->ctrl_reg_offset,
            old_val | (enabled ? TIMER_INT_UNMASK : 0));
}

static void rk_timer_rtc_reset(struct rk_timer_rtc *rk_rtc)
{
    rk_timer_rtc_writel(rk_rtc, rk_rtc->soc_data->ctrl_reg_offset, 0);

    /* Init load count to UINT64_MAX to keep timer running */
    rk_timer_rtc_writeq(rk_rtc, TIMER_LOAD_COUNT0, TIMER_COUNT_MAX);

    /* Clear any pending irq before enable it */
    rk_timer_rtc_irq_clear(rk_rtc);

    /* Enable timer in user-defined count mode with irq unmasked */
    rk_timer_rtc_writel(rk_rtc, rk_rtc->soc_data->ctrl_reg_offset,
            TIMER_ENABLE | TIMER_MODE_USER_DEFINED_COUNT | TIMER_INT_UNMASK);
}

static void rk_timer_rtc_read_time(struct rk_timer_rtc *rk_rtc, time_t *sec)
{
    rt_uint64_t tick;

    tick = rk_timer_rtc_readq(rk_rtc, TIMER_CURRENT_VALUE0);

    *sec = (time_t)tick_to_time64(rk_rtc, tick);
}

static void rk_timer_rtc_set_time(struct rk_timer_rtc *rk_rtc, time_t *sec)
{
    rk_rtc->timebase = (rt_uint64_t)*sec;

    rk_timer_rtc_reset(rk_rtc);
}

static void rk_timer_rtc_read_alarm(struct rk_timer_rtc *rk_rtc,
        struct rt_rtc_wkalarm *alarm)
{
    *alarm = rk_rtc->wkalarm;

    alarm->enable = rk_rtc->alarm_irq_enabled;
}

static rt_err_t rk_timer_rtc_set_alarm(struct rk_timer_rtc *rk_rtc,
        struct rt_rtc_wkalarm *alarm)
{
    rt_uint64_t alarm_tick, alarm_threshold_tick, cur_tick, time;

    rk_rtc->alarm_irq_enabled = alarm->enable;

    time = alarm->tm_hour * 3600 + alarm->tm_min * 60 + alarm->tm_sec;
    alarm_tick = time64_to_tick(rk_rtc, time);
    cur_tick = rk_timer_rtc_readq(rk_rtc, TIMER_CURRENT_VALUE0);

    /* Don't set an alarm in the past or about to pass */
    alarm_threshold_tick = ms_to_tick(rk_rtc, TIMER_ALARM_THRESHOLD_MS);

    if (alarm_tick <= (cur_tick + alarm_threshold_tick))
    {
        return -RT_ERROR;
    }

    /*
     * When the current value counts up to the load count, the timer will
     * stop and generate an irq.
     */
    rk_timer_rtc_writeq(rk_rtc, TIMER_LOAD_COUNT0, alarm_tick);

    return RT_EOK;
}

static rt_err_t rk_timer_rtc_control(rt_device_t dev, int cmd, void *args)
{
    rt_err_t err = RT_EOK;
    struct rk_timer_rtc *rk_rtc = raw_to_rk_timer_rtc(dev);

    if (!args)
    {
        return -RT_EINVAL;
    }

    switch (cmd)
    {
    case RT_DEVICE_CTRL_RTC_GET_TIME:
        rk_timer_rtc_read_time(rk_rtc, args);
        break;

    case RT_DEVICE_CTRL_RTC_SET_TIME:
        rk_timer_rtc_set_time(rk_rtc, args);
        break;

    case RT_DEVICE_CTRL_RTC_GET_TIMEVAL:
        rk_timer_rtc_read_time(rk_rtc, (time_t *)&((struct timeval *)args)->tv_sec);
        break;

    case RT_DEVICE_CTRL_RTC_SET_TIMEVAL:
        rk_timer_rtc_set_time(rk_rtc, (time_t *)&((struct timeval *)args)->tv_sec);
        break;

    case RT_DEVICE_CTRL_RTC_GET_ALARM:
        rk_timer_rtc_read_alarm(rk_rtc, args);
        break;

    case RT_DEVICE_CTRL_RTC_SET_ALARM:
        err = rk_timer_rtc_set_alarm(rk_rtc, args);
        break;

    default:
        err = -RT_EINVAL;
        break;
    }

    return err;
}

#ifdef RT_USING_DEVICE_OPS
const static struct rt_device_ops rk_timer_rtc_ops =
{
    .control = rk_timer_rtc_control,
};
#endif

static void rk_timer_rtc_isr(int irqno, void *param)
{
    struct rk_timer_rtc *rk_rtc = param;

    rk_timer_rtc_writeq(rk_rtc, TIMER_LOAD_COUNT0, TIMER_COUNT_MAX);
    rk_timer_rtc_writel(rk_rtc, TIMER_INT_STATUS, 1);

    if (rk_rtc->alarm_irq_enabled)
    {
        rt_alarm_update(&rk_rtc->parent, 1);
    }
}

static void rk_timer_rtc_free(struct rk_timer_rtc *rk_rtc)
{
    if (rk_rtc->base)
    {
        rt_iounmap(rk_rtc->base);
    }

    if (!rt_is_err_or_null(rk_rtc->pclk))
    {
        rt_clk_disable_unprepare(rk_rtc->pclk);
        rt_clk_put(rk_rtc->pclk);
    }

    if (!rt_is_err_or_null(rk_rtc->clk))
    {
        rt_clk_disable_unprepare(rk_rtc->clk);
        rt_clk_put(rk_rtc->clk);
    }

    rt_free(rk_rtc);
}

static rt_err_t rk_timer_rtc_probe(struct rt_platform_device *pdev)
{
    rt_err_t err;
    const char *dev_name;
    struct rt_device *dev = &pdev->parent;
    struct rk_timer_rtc *rk_rtc = rt_calloc(1, sizeof(*rk_rtc));

    if (!rk_rtc)
    {
        return -RT_ENOMEM;
    }

    rk_rtc->soc_data = pdev->id->data;

    rk_rtc->base = rt_dm_dev_iomap(dev, 0);

    if (!rk_rtc->base)
    {
        err = -RT_EIO;

        goto _fail;
    }

    rk_rtc->irq = rt_dm_dev_get_irq(dev, 0);

    if (rk_rtc->irq < 0)
    {
        err = rk_rtc->irq;

        goto _fail;
    }

    rk_rtc->pclk = rt_clk_get_by_name(dev, "pclk");

    if (rt_is_err(rk_rtc->pclk))
    {
        err = rt_ptr_err(rk_rtc->pclk);

        goto _fail;
    }

    if ((err = rt_clk_prepare_enable(rk_rtc->pclk)))
    {
        goto _fail;
    }

    rk_rtc->clk = rt_clk_get_by_name(dev, "timer");

    if (rt_is_err(rk_rtc->clk))
    {
        err = rt_ptr_err(rk_rtc->clk);

        goto _fail;
    }

    if ((err = rt_clk_prepare_enable(rk_rtc->clk)))
    {
        goto _fail;
    }

    rk_rtc->freq = rt_clk_get_rate(rk_rtc->clk);

    dev->user_data = rk_rtc;

    rk_rtc->parent.type = RT_Device_Class_RTC;
#ifdef RT_USING_DEVICE_OPS
    rk_rtc->parent.ops = &rk_timer_rtc_ops;
#else
    rk_rtc->parent.control = rk_timer_rtc_control;
#endif

    rtc_dev_set_name(&rk_rtc->parent);
    dev_name = rt_dm_dev_get_name(&rk_rtc->parent);
    rt_device_register(&rk_rtc->parent, dev_name, RT_DEVICE_FLAG_RDWR);

    rt_hw_interrupt_install(rk_rtc->irq, rk_timer_rtc_isr, rk_rtc, "rtc-rockchip");
    rt_hw_interrupt_umask(rk_rtc->irq);

    return RT_EOK;

_fail:
    rk_timer_rtc_free(rk_rtc);

    return err;
}

static rt_err_t rk_timer_rtc_remove(struct rt_platform_device *pdev)
{
    struct rk_timer_rtc *rk_rtc = pdev->parent.user_data;

    rt_hw_interrupt_mask(rk_rtc->irq);
    rt_pic_detach_irq(rk_rtc->irq, rk_rtc);

    rt_device_unregister(&rk_rtc->parent);

    rk_timer_rtc_free(rk_rtc);

    return RT_EOK;
}

static const struct rk_timer_rtc_data rk3288_timer_rtc_data =
{
    .ctrl_reg_offset = TIMER_CONTROL_REG3288,
};

static const struct rt_ofw_node_id rk_timer_rtc_ofw_ids[] =
{
    { .compatible = "rockchip,rk3308-timer-rtc", .data = &rk3288_timer_rtc_data },
    { /* sentinel */ }
};

static struct rt_platform_driver rk_timer_rtc_driver =
{
    .name = "rk-timer-rtc",
    .ids = rk_timer_rtc_ofw_ids,

    .probe = rk_timer_rtc_probe,
    .remove = rk_timer_rtc_remove,
};
RT_PLATFORM_DRIVER_EXPORT(rk_timer_rtc_driver);
