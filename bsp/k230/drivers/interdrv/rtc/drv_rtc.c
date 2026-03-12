/* Copyright (c) 2023, Canaan Bright Sight Co., Ltd
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 * 1. Redistributions of source code must retain the above copyright
 * notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 * notice, this list of conditions and the following disclaimer in the
 * documentation and/or other materials provided with the distribution.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND
 * CONTRIBUTORS "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES,
 * INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF
 * MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR
 * CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
 * SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING,
 * BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
 * SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
 * INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,
 * WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING
 * NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
 * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

/*
 * Copyright (c) 2006-2025 RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#include <rtthread.h>
#include <rthw.h>
#include <rtdevice.h>
#include <riscv_io.h>
#include <ioremap.h>
#include <time.h>
#include "board.h"
#include "drv_rtc.h"

#undef DBG_TAG
#undef DBG_LVL
#define DBG_TAG     "drv_rtc"
#define DBG_LVL     DBG_INFO
#include <rtdbg.h>

struct k230_rtc_dev
{
    struct rt_device device;
    const char *name;
    rt_ubase_t base;
    size_t size;
    int vector;
    void (*vector_callback)(void);
};

static void pmu_isolation_rtc(void)
{
    /* map pwr base address */
    volatile void *reg_pmu_pwr = rt_ioremap((void *)PWR_BASE_ADDR, PWR_IO_SIZE);
    uint32_t *addr = (uint32_t *)(reg_pmu_pwr + 0x158); /* pmu power control register */
    uint32_t data;

    /* disable pmu isolation */
    data = *addr;
    data &= ~0x20;
    *addr = data;
    rt_iounmap(reg_pmu_pwr);

    /* map pmu base address */
    volatile void *reg_pmu = rt_ioremap((void*)PMU_BASE_ADDR, PMU_IO_SIZE);
    addr = (uint32_t*)(reg_pmu + 0x48); /* pmu int0 to cpu register */
    /* enable int6 int7 */
    data = *addr;
    data |= 0x06;
    *addr = data;

    addr = (uint32_t*)(reg_pmu + 0x4c); /* pmu int detect en register */
    /* enable int6 rtc alarm detection and int7 rtc tick detection */
    data = *addr;
    data |= 0x06;
    *addr = data;
    rt_iounmap(reg_pmu);
}

static int rtc_year_is_leap(int year)
{
    return (year % 4 == 0 && year % 100 != 0) || (year % 400 == 0);
}

static void rtc_timer_set_clock_count_value(struct k230_rtc_dev *dev, uint16_t count)
{
    volatile volatile rtc_t *rtc = (rtc_t *)dev->base;

    rtc->count.curr_count = count;
    rtc->count.sum_count = 0x7FFF;
    rtc->int_ctrl.timer_w_en = 1;
    rt_thread_mdelay(1);
    rtc->int_ctrl.timer_w_en = 0;
    rtc->int_ctrl.timer_r_en = 1;
}

static void rtc_interrupt_ctrl_set(struct k230_rtc_dev *dev, rtc_interrupt_mode_t mode)
{
    volatile rtc_t *rtc = (rtc_t *)dev->base;

    if (mode < RTC_INT_TICK_YEAR)
    {
        rtc->int_ctrl.year_cmp = 0;
        rtc->int_ctrl.month_cmp = 0;
        rtc->int_ctrl.day_cmp = 0;
        rtc->int_ctrl.week_cmp = 0;
        rtc->int_ctrl.hour_cmp = 0;
        rtc->int_ctrl.minute_cmp = 0;
        rtc->int_ctrl.second_cmp = 0;

        if (mode & RTC_INT_ALARM_YEAR)
        {
            rtc->int_ctrl.year_cmp = 1;
        }
        if (mode & RTC_INT_ALARM_MONTH)
        {
            rtc->int_ctrl.month_cmp = 1;
        }
        if (mode & RTC_INT_ALARM_DAY)
        {
            rtc->int_ctrl.day_cmp = 1;
        }
        if (mode & RTC_INT_ALARM_WEEK)
        {
            rtc->int_ctrl.week_cmp = 1;
        }
        if (mode & RTC_INT_ALARM_HOUR)
        {
            rtc->int_ctrl.hour_cmp = 1;
        }
        if (mode & RTC_INT_ALARM_MINUTE)
        {
            rtc->int_ctrl.minute_cmp = 1;
        }
        if (mode & RTC_INT_ALARM_SECOND)
        {
            rtc->int_ctrl.second_cmp = 1;
        }
        rtc->int_ctrl.alarm_en = 1;
    }
    else
    {
        switch(mode)
        {
            case RTC_INT_TICK_YEAR:
                rtc->int_ctrl.tick_sel = 0x8;
                rtc->int_ctrl.tick_en = 1;
                break;
            case RTC_INT_TICK_MONTH:
                rtc->int_ctrl.tick_sel = 0x7;
                rtc->int_ctrl.tick_en = 1;
                break;
            case RTC_INT_TICK_DAY:
                rtc->int_ctrl.tick_sel = 0x6;
                rtc->int_ctrl.tick_en = 1;
                break;
            case RTC_INT_TICK_WEEK:
                rtc->int_ctrl.tick_sel = 0x5;
                rtc->int_ctrl.tick_en = 1;
                break;
            case RTC_INT_TICK_HOUR:
                rtc->int_ctrl.tick_sel = 0x4;
                rtc->int_ctrl.tick_en = 1;
                break;
            case RTC_INT_TICK_MINUTE:
                rtc->int_ctrl.tick_sel = 0x3;
                rtc->int_ctrl.tick_en = 1;
                break;
            case RTC_INT_TICK_SECOND:
                rtc->int_ctrl.tick_sel = 0x2;
                rtc->int_ctrl.tick_en = 1;
                break;
            case RTC_INT_TICK_S8:
                rtc->int_ctrl.tick_sel = 0x1;
                rtc->int_ctrl.tick_en = 1;
                break;
            case RTC_INT_TICK_S64:
                rtc->int_ctrl.tick_sel = 0x0;
                rtc->int_ctrl.tick_en = 1;
                break;
            default :
                break;
        }
    }
}

static void rtc_stop_interrupt(struct k230_rtc_dev *dev)
{
    rt_hw_interrupt_mask(dev->vector);
}

static void rtc_alarm_stop(struct k230_rtc_dev *dev)
{
    volatile rtc_t *rtc = (rtc_t *)dev->base;
    rtc->int_ctrl.alarm_en = 0;
    rtc_stop_interrupt(dev);
}

static void rtc_tick_stop(struct k230_rtc_dev *dev)
{
    volatile rtc_t *rtc = (rtc_t *)dev->base;
    rtc->int_ctrl.tick_en = 0;
    rtc_stop_interrupt(dev);
}

static void rtc_alarm_clear_interrupt(struct k230_rtc_dev *dev)
{
    volatile rtc_t *rtc = (rtc_t *)dev->base;

    rtc->int_ctrl.alarm_clr = 1;
}

static void rtc_irq(int vector, void *param)
{
    struct k230_rtc_dev *dev = (struct k230_rtc_dev *)param;

    rtc_alarm_clear_interrupt(dev);
    if (dev->vector_callback != RT_NULL)
    {
        dev->vector_callback();
    }
}

static void rtc_date_time_set(struct k230_rtc_dev *dev, int year, int month, int day, \
                              int hour, int minute, int second, int week)
{
    rtc_date_t date;
    rtc_time_t time;
    rtc_count_t count;
    volatile rtc_t *rtc = (rtc_t *)dev->base;

    int val = year % 100;
    int year_l, year_h;
    if(val == 0)
    {
        year_l = 100;
        year_h = year / 100 - 1;
    }
    else
    {
        year_l = val;
        year_h = (year - val) / 100;
    }

    rtc->int_ctrl.timer_w_en = 1;

    date.year_h = year_h;
    date.year_l = year_l;
    date.month = month;
    date.day = day;
    date.leap_year = rtc_year_is_leap(year);
    time.week = week;
    time.hour = hour;
    time.minute = minute;
    time.second = second;

    rtc->date = date;
    rtc->time = time;
}

static void rtc_timer_get(struct k230_rtc_dev *dev, time_t *t)
{
    volatile rtc_t *rtc = (rtc_t *)dev->base;
    struct tm tm;

    if (rtc->int_ctrl.timer_r_en == 0)
    {
        rtc->int_ctrl.timer_r_en = 1;
    }

    tm.tm_sec = rtc->time.second;
    tm.tm_min = rtc->time.minute;
    tm.tm_hour = rtc->time.hour;
    tm.tm_mday = rtc->date.day;
    tm.tm_mon = rtc->date.month - 1;
    tm.tm_year = (rtc->date.year_h * 100 + rtc->date.year_l) - 1900;
    tm.tm_wday = rtc->time.week;

    *t = timegm(&tm);
}

static void rtc_timer_set(struct k230_rtc_dev *dev, time_t *t)
{
    struct tm p_tm;
    gmtime_r(t, &p_tm);

    rtc_date_time_set(dev, (p_tm.tm_year + 1900), p_tm.tm_mon + 1, p_tm.tm_mday, \
                      p_tm.tm_hour, p_tm.tm_min, p_tm.tm_sec, p_tm.tm_wday);

    rtc_timer_set_clock_count_value(dev, 0);
}

static void rtc_alarm_get(struct k230_rtc_dev *dev, void *args)
{
    struct tm *tm = (struct tm*)args;
    volatile rtc_t *rtc = (rtc_t *)dev->base;
    rtc_alarm_date_t alarm_date = rtc->alarm_date;
    rtc_alarm_time_t alarm_time = rtc->alarm_time;

    tm->tm_year = (alarm_date.alarm_year_h * 100 + alarm_date.alarm_year_l) -1900;
    tm->tm_mon = alarm_date.alarm_month - 1;
    tm->tm_mday = alarm_date.alarm_day;
    tm->tm_hour = alarm_time.alarm_hour;
    tm->tm_min = alarm_time.alarm_minute;
    tm->tm_sec = alarm_time.alarm_second;
}

static void rtc_alarm_set(struct k230_rtc_dev *dev, void *args)
{
    rtc_alarm_setup_t *setup = (rtc_alarm_setup_t *)args;
    struct tm tm = setup->tm;
    time_t t;
    struct tm p_tm;
    volatile rtc_t *rtc = (rtc_t *)dev->base;
    rtc_alarm_time_t alarm_time;
    rtc_alarm_date_t alarm_date;
    rtc_date_t date = rtc->date;
    int year, year_l, year_h, val;

    t = mktime(&tm);
    gmtime_r(&t, &p_tm);

    year = p_tm.tm_year + 1900;
    val = year % 100;

    if(val == 0)
    {
        year_l = 100;
        year_h = year / 100 - 1;
    }
    else
    {
        year_l = val;
        year_h = (year - val) / 100;
    }

    alarm_date.alarm_year_h = year_h;
    alarm_date.alarm_year_l = year_l;
    alarm_date.alarm_month = p_tm.tm_mon + 1;
    alarm_date.alarm_day = p_tm.tm_mday;
    alarm_time.alarm_hour = p_tm.tm_hour;
    alarm_time.alarm_minute = p_tm.tm_min;
    alarm_time.alarm_second = p_tm.tm_sec;

    rtc->alarm_date = alarm_date;
    rtc->alarm_time = alarm_time;

    rtc_alarm_clear_interrupt(dev);
    rt_hw_interrupt_install(dev->vector, rtc_irq, dev, "rtc");
    rt_hw_interrupt_umask(dev->vector);
    rtc_interrupt_ctrl_set(dev, setup->flag);
}

static rt_err_t rtc_device_init(rt_device_t dev)
{
    struct k230_rtc_dev *rtc_dev = rt_container_of(dev, struct k230_rtc_dev, device);

    rtc_alarm_stop(rtc_dev);
    rtc_tick_stop(rtc_dev);

    return RT_EOK;
}

static rt_err_t rtc_device_open(rt_device_t dev, rt_uint16_t oflag)
{
    return RT_EOK;
}

static rt_err_t rtc_device_close(rt_device_t dev)
{
    return RT_EOK;
}

static rt_ssize_t rtc_device_read(rt_device_t dev, rt_off_t pos, void *buffer, rt_size_t size)
{
    time_t t;
    struct k230_rtc_dev *rtc_dev = rt_container_of(dev, struct k230_rtc_dev, device);

    rtc_timer_get(rtc_dev, &t);
    rt_memcpy(buffer, (void*)&t, sizeof(t));
    return size;
}

static rt_ssize_t rtc_device_write(rt_device_t dev, rt_off_t pos, const void *buffer, rt_size_t size)
{
    struct tm *tm = (struct tm*)buffer;
    time_t t = mktime(tm);
    struct k230_rtc_dev *rtc_dev = rt_container_of(dev, struct k230_rtc_dev, device);

    rtc_timer_set(rtc_dev, &t);
    return size;
}

static rt_err_t rtc_device_control(rt_device_t dev, int cmd, void *args)
{
    time_t time;
    RT_ASSERT(dev != RT_NULL);

    struct k230_rtc_dev *rtc_dev = rt_container_of(dev, struct k230_rtc_dev, device);
    RT_ASSERT(rtc_dev != RT_NULL);

    switch (cmd)
    {
    case RT_DEVICE_CTRL_RTC_GET_TIME:
        rtc_timer_get(rtc_dev, (time_t*)args);
        break;
    case RT_DEVICE_CTRL_RTC_SET_TIME:
        rtc_timer_set(rtc_dev, (time_t *)args);
        break;
    case RT_DEVICE_CTRL_RTC_GET_ALARM:
        rtc_alarm_get(rtc_dev, args);
        break;
    case RT_DEVICE_CTRL_RTC_SET_ALARM:
        rtc_alarm_set(rtc_dev, args);
        break;
    case RT_DEVICE_CTRL_RTC_STOP_ALARM:
        rtc_alarm_stop(rtc_dev);
        break;
    case RT_DEVICE_CTRL_RTC_STOP_TICK:
        rtc_tick_stop(rtc_dev);
        break;
    case RT_DEVICE_CTRL_RTC_SET_CALLBACK:
        rtc_dev->vector_callback = args;
        break;
    default:
        return -RT_EINVAL;
    }
    return RT_EOK;
}

const static struct rt_device_ops rtc_ops =
{
    .init = rtc_device_init,
    .open = rtc_device_open,
    .close = rtc_device_close,
    .read = rtc_device_read,
    .write = rtc_device_write,
    .control = rtc_device_control,
};

static struct k230_rtc_dev rtc_dev =
{
    .name = "rtc",
    .base = RTC_BASE_ADDR,
    .size = RTC_IO_SIZE,
    .vector = K230_IRQ_PMU,
    .vector_callback = RT_NULL,
};

static int rt_hw_rtc_init(void)
{
    rt_err_t ret;

    pmu_isolation_rtc();
    rtc_dev.device.type = RT_Device_Class_RTC;
    rtc_dev.device.rx_indicate = RT_NULL;
    rtc_dev.device.tx_complete = RT_NULL;
#ifdef RT_USING_DEVICE_OPS
    rtc_dev.device.ops = &rtc_ops;
#else
    rtc_dev.device.init = rtc_device_init;
    rtc_dev.device.open = rtc_device_open;
    rtc_dev.device.close = rtc_device_close;
    rtc_dev.device.read = rtc_device_read;
    rtc_dev.device.write = rtc_device_write;
    rtc_dev.device.control = rtc_device_control;
#endif /* RT_USING_DEVICE_OPS */
    rtc_dev.device.user_data = RT_NULL;
    rtc_dev.base = (rt_ubase_t)rt_ioremap((void *)rtc_dev.base, rtc_dev.size);
    RT_ASSERT(rtc_dev.base != RT_NULL);

    ret = rt_device_register(&rtc_dev.device, "rtc", RT_DEVICE_FLAG_RDWR);
    RT_ASSERT(ret == RT_EOK);
    LOG_I("rtc driver register OK\n");

    rtc_alarm_stop(&rtc_dev);
    rtc_tick_stop(&rtc_dev);
    return ret;
}
INIT_DEVICE_EXPORT(rt_hw_rtc_init);
