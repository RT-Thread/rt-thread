/*
 * Copyright (c) 2006-2022, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2022-11-26     GuEe-GUI     first version
 */

#include <rtthread.h>
#include <rtdevice.h>

#define DBG_TAG "rtc.rk8xx"
#define DBG_LVL DBG_INFO
#include <rtdbg.h>

#include "rtc_dm.h"
#include "rk8xx.h"

#define BIT_RTC_CTRL_REG_STOP_RTC_M         RT_BIT(0)
#define BIT_RTC_CTRL_REG_RTC_GET_TIME       RT_BIT(6)
#define BIT_RTC_CTRL_REG_RTC_READSEL_M      RT_BIT(7)
#define BIT_RTC_INTERRUPTS_REG_IT_ALARM_M   RT_BIT(3)

#define RTC_STATUS_MASK 0xfe
#define SECONDS_REG_MSK 0x7f
#define MINUTES_REG_MAK 0x7f
#define HOURS_REG_MSK   0x3f
#define DAYS_REG_MSK    0x3f
#define MONTHS_REG_MSK  0x1f
#define YEARS_REG_MSK   0xff
#define WEEKS_REG_MSK   0x7

#define NUM_TIME_REGS   (RK808_WEEKS_REG - RK808_SECONDS_REG + 1)
#define NUM_ALARM_REGS  (RK808_ALARM_YEARS_REG - RK808_ALARM_SECONDS_REG + 1)

struct rk_rtc_compat_reg
{
    rt_uint32_t ctrl_reg;
    rt_uint32_t status_reg;
    rt_uint32_t alarm_seconds_reg;
    rt_uint32_t int_reg;
    rt_uint32_t seconds_reg;
};

struct rk8xx_rtc
{
    struct rt_device parent;

    int irq;
    struct rk8xx *rk8xx;
    struct rk_rtc_compat_reg *creg;
};

#define raw_to_rk8xx_rtc(raw) rt_container_of(raw, struct rk8xx_rtc, parent)

static rt_err_t rk8xx_rtc_read_time(struct rk8xx_rtc *rk8xx_rtc, time_t *sec)
{
    rt_err_t err;
    struct tm tm;
    struct rk8xx *rk8xx;
    rt_uint32_t ctrl_reg, seconds_reg;
    rt_uint8_t rtc_data[NUM_TIME_REGS];

    rk8xx = rk8xx_rtc->rk8xx;
    ctrl_reg = rk8xx_rtc->creg->ctrl_reg;
    seconds_reg = rk8xx_rtc->creg->seconds_reg;

    err = rk8xx_update_bits(rk8xx, ctrl_reg, BIT_RTC_CTRL_REG_RTC_GET_TIME,
            BIT_RTC_CTRL_REG_RTC_GET_TIME);

    if (err)
    {
        LOG_E("Update RTC control error = %s", rt_strerror(err));

        return err;
    }

    err = rk8xx_update_bits(rk8xx, ctrl_reg, BIT_RTC_CTRL_REG_RTC_GET_TIME, 0);

    if (err)
    {
        LOG_E("Update RTC control error = %s", rt_strerror(err));

        return err;
    }

    for (int i = 0; i < RT_ARRAY_SIZE(rtc_data); ++i)
    {
        rtc_data[i] = rk8xx_read(rk8xx, seconds_reg + i * sizeof(rt_uint8_t));
    }

    tm.tm_sec  =  rt_bcd2bin(rtc_data[0] & SECONDS_REG_MSK);
    tm.tm_min  =  rt_bcd2bin(rtc_data[1] & MINUTES_REG_MAK);
    tm.tm_hour =  rt_bcd2bin(rtc_data[2] & HOURS_REG_MSK);
    tm.tm_mday =  rt_bcd2bin(rtc_data[3] & DAYS_REG_MSK);
    tm.tm_mon  = (rt_bcd2bin(rtc_data[4] & MONTHS_REG_MSK)) - 1;
    tm.tm_year = (rt_bcd2bin(rtc_data[5] & YEARS_REG_MSK)) + 100;
    tm.tm_wday =  rt_bcd2bin(rtc_data[6] & WEEKS_REG_MSK);

    *sec = mktime(&tm);

    return RT_EOK;
}

static rt_err_t rk8xx_rtc_set_time(struct rk8xx_rtc *rk8xx_rtc, time_t *sec)
{
    rt_err_t err;
    struct tm *tm;
    struct rk8xx *rk8xx;
    rt_uint32_t ctrl_reg, seconds_reg;
    rt_uint8_t rtc_data[NUM_TIME_REGS];

    rk8xx = rk8xx_rtc->rk8xx;
    ctrl_reg = rk8xx_rtc->creg->ctrl_reg;
    seconds_reg = rk8xx_rtc->creg->seconds_reg;

    tm = localtime(sec);
    rtc_data[0] = rt_bin2bcd(tm->tm_sec);
    rtc_data[1] = rt_bin2bcd(tm->tm_min);
    rtc_data[2] = rt_bin2bcd(tm->tm_hour);
    rtc_data[3] = rt_bin2bcd(tm->tm_mday);
    rtc_data[4] = rt_bin2bcd(tm->tm_mon + 1);
    rtc_data[5] = rt_bin2bcd(tm->tm_year - 100);
    rtc_data[6] = rt_bin2bcd(tm->tm_wday);

    err = rk8xx_update_bits(rk8xx, ctrl_reg, BIT_RTC_CTRL_REG_STOP_RTC_M,
            BIT_RTC_CTRL_REG_STOP_RTC_M);

    if (err)
    {
        LOG_E("Update RTC control error = %s", rt_strerror(err));

        return err;
    }

    for (int i = 0; i < RT_ARRAY_SIZE(rtc_data); ++i)
    {
        err = rk8xx_write(rk8xx, seconds_reg + i * sizeof(rt_uint8_t), rtc_data[i]);

        if (err)
        {
            LOG_E("Update RTC time[%d] error = %s", i, rt_strerror(err));

            return err;
        }
    }

    err = rk8xx_update_bits(rk8xx, ctrl_reg, BIT_RTC_CTRL_REG_STOP_RTC_M, 0);

    if (err)
    {
        LOG_E("Update RTC control error = %s", rt_strerror(err));

        return err;
    }

    return RT_EOK;
}

static void rk8xx_rtc_read_alarm(struct rk8xx_rtc *rk8xx_rtc,
        struct rt_rtc_wkalarm *alarm)
{
    struct rk8xx *rk8xx;
    rt_uint8_t alrm_data[NUM_ALARM_REGS];
    rt_uint32_t int_reg, alarm_seconds_reg;

    rk8xx = rk8xx_rtc->rk8xx;
    int_reg = rk8xx_rtc->creg->int_reg;
    alarm_seconds_reg = rk8xx_rtc->creg->alarm_seconds_reg;

    for (int i = 0; i < 3; ++i)
    {
        alrm_data[i] = rk8xx_read(rk8xx, alarm_seconds_reg + i * sizeof(rt_uint8_t));
    }

    alarm->tm_sec = rt_bcd2bin(alrm_data[0] & SECONDS_REG_MSK);
    alarm->tm_min = rt_bcd2bin(alrm_data[1] & MINUTES_REG_MAK);
    alarm->tm_hour = rt_bcd2bin(alrm_data[2] & HOURS_REG_MSK);

    alarm->enable = !!(rk8xx_read(rk8xx, int_reg) & BIT_RTC_INTERRUPTS_REG_IT_ALARM_M);
}

static rt_err_t rk8xx_rtc_set_alarm(struct rk8xx_rtc *rk8xx_rtc,
        struct rt_rtc_wkalarm *alarm)
{
    rt_err_t err;
    struct rk8xx *rk8xx;
    rt_uint32_t int_reg, alarm_seconds_reg;
    rt_uint8_t alrm_data[NUM_ALARM_REGS];

    rk8xx = rk8xx_rtc->rk8xx;
    int_reg = rk8xx_rtc->creg->int_reg;
    alarm_seconds_reg = rk8xx_rtc->creg->alarm_seconds_reg;

    err = rk8xx_update_bits(rk8xx, int_reg, BIT_RTC_INTERRUPTS_REG_IT_ALARM_M, 0);

    if (err)
    {
        LOG_E("%s RTC alarm error = %s", "Stop", rt_strerror(err));

        return err;
    }

    alrm_data[0] = rt_bin2bcd(alarm->tm_sec);
    alrm_data[1] = rt_bin2bcd(alarm->tm_min);
    alrm_data[2] = rt_bin2bcd(alarm->tm_hour);

    for (int i = 0; i < RT_ARRAY_SIZE(alrm_data); ++i)
    {
        err = rk8xx_write(rk8xx, alarm_seconds_reg + i * sizeof(rt_uint8_t),
                alrm_data[i]);

        if (err)
        {
            LOG_E("Update RTC alarm time[%d] error = %s", i, rt_strerror(err));

            return err;
        }
    }

    if (alarm->enable)
    {
        err = rk8xx_update_bits(rk8xx, int_reg,
                BIT_RTC_INTERRUPTS_REG_IT_ALARM_M,
                BIT_RTC_INTERRUPTS_REG_IT_ALARM_M);

        if (err)
        {
            LOG_E("%s RTC alarm error = %s", "Start", rt_strerror(err));

            return err;
        }
    }

    return RT_EOK;
}

static rt_err_t rk8xx_rtc_control(rt_device_t dev, int cmd, void *args)
{
    rt_err_t err = RT_EOK;
    struct rk8xx_rtc *rk8xx_rtc = raw_to_rk8xx_rtc(dev);

    if (!args)
    {
        return -RT_EINVAL;
    }

    switch (cmd)
    {
    case RT_DEVICE_CTRL_RTC_GET_TIME:
        err = rk8xx_rtc_read_time(rk8xx_rtc, args);
        break;

    case RT_DEVICE_CTRL_RTC_SET_TIME:
        err = rk8xx_rtc_set_time(rk8xx_rtc, args);
        break;

    case RT_DEVICE_CTRL_RTC_GET_TIMEVAL:
        err = rk8xx_rtc_read_time(rk8xx_rtc, (time_t *)&((struct timeval *)args)->tv_sec);
        break;

    case RT_DEVICE_CTRL_RTC_SET_TIMEVAL:
        err = rk8xx_rtc_set_time(rk8xx_rtc, (time_t *)&((struct timeval *)args)->tv_sec);
        break;

    case RT_DEVICE_CTRL_RTC_GET_ALARM:
        rk8xx_rtc_read_alarm(rk8xx_rtc, args);
        break;

    case RT_DEVICE_CTRL_RTC_SET_ALARM:
        rk8xx_rtc_set_alarm(rk8xx_rtc, args);
        break;

    default:
        err = -RT_EINVAL;
        break;
    }

    return err;
}

#ifdef RT_USING_DEVICE_OPS
const static struct rt_device_ops rk8xx_rtc_ops =
{
    .control = rk8xx_rtc_control,
};
#endif

static void rk8xx_rtc_isr(int irqno, void *param)
{
    rt_err_t err;
    struct rk8xx_rtc *rk8xx_rtc = param;

    err = rk8xx_write(rk8xx_rtc->rk8xx, rk8xx_rtc->creg->status_reg,
            RTC_STATUS_MASK);

    if (err)
    {
        LOG_E("Update RTC status error = %s", rt_strerror(err));
        return;
    }

    rt_alarm_update(&rk8xx_rtc->parent, 1);
}

static struct rk_rtc_compat_reg rk808_creg =
{
    .ctrl_reg = RK808_RTC_CTRL_REG,
    .status_reg = RK808_RTC_STATUS_REG,
    .alarm_seconds_reg = RK808_ALARM_SECONDS_REG,
    .int_reg = RK808_RTC_INT_REG,
    .seconds_reg = RK808_SECONDS_REG,
};

static struct rk_rtc_compat_reg rk817_creg =
{
    .ctrl_reg = RK817_RTC_CTRL_REG,
    .status_reg = RK817_RTC_STATUS_REG,
    .alarm_seconds_reg = RK817_ALARM_SECONDS_REG,
    .int_reg = RK817_RTC_INT_REG,
    .seconds_reg = RK817_SECONDS_REG,
};

static rt_err_t rk8xx_rtc_probe(struct rt_platform_device *pdev)
{
    rt_err_t err;
    const char *dev_name;
    struct rk8xx *rk8xx = pdev->priv;
    struct rt_device *dev = &pdev->parent;
    struct rk8xx_rtc *rk8xx_rtc = rt_calloc(1, sizeof(*rk8xx_rtc));

    if (!rk8xx_rtc)
    {
        return -RT_ENOMEM;
    }

    rk8xx_rtc->rk8xx = rk8xx;

    switch (rk8xx->variant)
    {
    case RK809_ID:
    case RK817_ID:
        rk8xx_rtc->creg = &rk817_creg;
        break;

    default:
        rk8xx_rtc->creg = &rk808_creg;
        break;
    }

    err = rk8xx_update_bits(rk8xx, rk8xx_rtc->creg->ctrl_reg,
            BIT_RTC_CTRL_REG_STOP_RTC_M |
            BIT_RTC_CTRL_REG_RTC_READSEL_M,
            BIT_RTC_CTRL_REG_RTC_READSEL_M);

    if (err)
    {
        LOG_E("Update RTC control error = %s", rt_strerror(err));
        goto _fail;
    }

    err = rk8xx_write(rk8xx, rk8xx_rtc->creg->status_reg, RTC_STATUS_MASK);

    if (err)
    {
        LOG_E("Write RTC status error = %s", rt_strerror(err));
        goto _fail;
    }

    rk8xx_rtc->irq = rt_dm_dev_get_irq(dev, 0);

    if (rk8xx_rtc->irq < 0)
    {
        err = rk8xx_rtc->irq;
        goto _fail;
    }

    dev->user_data = rk8xx_rtc;

    rk8xx_rtc->parent.type = RT_Device_Class_RTC;
#ifdef RT_USING_DEVICE_OPS
    rk8xx_rtc->parent.ops = &rk8xx_rtc_ops;
#else
    rk8xx_rtc->parent.control = rk8xx_rtc_control;
#endif

    rtc_dev_set_name(&rk8xx_rtc->parent);
    dev_name = rt_dm_dev_get_name(&rk8xx_rtc->parent);
    rt_device_register(&rk8xx_rtc->parent, dev_name, RT_DEVICE_FLAG_RDWR);

    rt_hw_interrupt_install(rk8xx_rtc->irq, rk8xx_rtc_isr, rk8xx_rtc, "rtc-rk8xx");
    rt_hw_interrupt_umask(rk8xx_rtc->irq);

    return RT_EOK;

_fail:
    rt_free(rk8xx_rtc);

    return err;
}

static rt_err_t rk8xx_rtc_remove(struct rt_platform_device *pdev)
{
    struct rk8xx_rtc *rk8xx_rtc = pdev->parent.user_data;

    rt_hw_interrupt_mask(rk8xx_rtc->irq);
    rt_pic_detach_irq(rk8xx_rtc->irq, rk8xx_rtc);

    rt_device_unregister(&rk8xx_rtc->parent);

    rt_free(rk8xx_rtc);

    return RT_EOK;
}

static struct rt_platform_driver rk8xx_rtc_driver =
{
    .name = "rk8xx-rtc",
    .probe = rk8xx_rtc_probe,
    .remove = rk8xx_rtc_remove,
};
RT_PLATFORM_DRIVER_EXPORT(rk8xx_rtc_driver);
