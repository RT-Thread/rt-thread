/*
 * Copyright (c) 2006-2024, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date         Author          Notes
 * 2024-03-04   ShichengChu     the first version
 */

#include <rtthread.h>
#include <rtdevice.h>

#define DBG_TAG "DRV.RTC"
#define DBG_LVL DBG_WARNING
#include <rtdbg.h>

#include "pinctrl.h"
#include "mmio.h"
#include "drv_ioremap.h"

#define CVI_RTC_BASE        0x05026000U
#define RTC_ALARM_O         17
#define CVI_RTC_CTRL_BASE   0x05025000U
#define CLK_EN_0            0x03002000U
#define CLK_RTC_25M_BIT     (1 << 8)

/* CVITEK RTC registers */
#define CVI_RTC_ANA_CALIB               0x0
#define CVI_RTC_SEC_PULSE_GEN           0x4
#define CVI_RTC_ALARM_TIME              0x8
#define CVI_RTC_ALARM_ENABLE            0xC
#define CVI_RTC_SET_SEC_CNTR_VALUE      0x10
#define CVI_RTC_SET_SEC_CNTR_TRIG       0x14
#define CVI_RTC_SEC_CNTR_VALUE          0x18
#define CVI_RTC_APB_RDATA_SEL           0x3C
#define CVI_RTC_POR_DB_MAGIC_KEY        0x68
#define CVI_RTC_EN_PWR_WAKEUP           0xBC
#define CVI_RTC_PWR_DET_SEL             0x140

/* CVITEK RTC MACRO registers */
#define RTC_MACRO_DA_CLEAR_ALL          0x480
#define RTC_MACRO_DA_SOC_READY          0x48C
#define RTC_MACRO_RO_T                  0x4A8
#define RTC_MACRO_RG_SET_T              0x498

/* CVITEK RTC CTRL registers */
#define CVI_RTC_FC_COARSE_EN            0x40
#define CVI_RTC_FC_COARSE_CAL           0x44
#define CVI_RTC_FC_FINE_EN              0x48
#define CVI_RTC_FC_FINE_CAL             0x50

#define RTC_SEC_MAX_VAL     0xFFFFFFFF

#define RTC_OFFSET_SN 0x5201800
#define RTC_ALARM_IRQ_NUM 0x11

struct rtc_device_object
{
    rt_rtc_dev_t  rtc_dev;
    rt_ubase_t base;
};

static struct rtc_device_object rtc_device;

#define LEAPS_THRU_END_OF(y) ((y)/4 - (y)/100 + (y)/400)

typedef struct {
    int tm_sec;             ///< Second.      [0-59]
    int tm_min;             ///< Minute.      [0-59]
    int tm_hour;            ///< Hour.        [0-23]
    int tm_mday;            ///< Day.         [1-31]
    int tm_mon;             ///< Month.       [0-11]
    int tm_year;            ///< Year-1900.   [70- ]      !NOTE:Set 100 mean 2000
    int tm_wday;            ///< Day of week. [0-6 ]      !NOTE:Set 0 mean Sunday
    int tm_yday;            ///< Days in year.[0-365]     !NOTE:Set 0 mean January 1st
} cvi_rtc_time_t;

static const unsigned char cvi_rtc_days_in_month[] = {
    31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31
};

static inline int is_leap_year(unsigned int year)
{
    return (!(year % 4) && (year % 100)) || !(year % 400);
}

static int rtc_month_days(unsigned int month, unsigned int year)
{
    return cvi_rtc_days_in_month[month] + (is_leap_year(year) && month == 1);
}

static void hal_cvi_rtc_clk_set(int enable)
{
    uint32_t clk_state;
    rt_ubase_t clk = (rt_ubase_t)DRV_IOREMAP((void *)CLK_EN_0, 0x1000);

    clk_state = mmio_read_32(clk);

    if(enable)
        clk_state |= CLK_RTC_25M_BIT;
    else
        clk_state &= ~(CLK_RTC_25M_BIT);

    mmio_write_32(clk, clk_state);
}

static void hal_cvi_rtc_enable_sec_counter(uintptr_t rtc_base)
{
    uint32_t value = 0;

    value = mmio_read_32(rtc_base + CVI_RTC_SEC_PULSE_GEN) & 0x7FFFFFFF;
    mmio_write_32(rtc_base + CVI_RTC_SEC_PULSE_GEN, value);

    value = mmio_read_32(rtc_base + CVI_RTC_ANA_CALIB) & 0x7FFFFFFF;
    mmio_write_32(rtc_base + CVI_RTC_ANA_CALIB, value);

    mmio_read_32(rtc_base + CVI_RTC_SEC_CNTR_VALUE);
    mmio_write_32(rtc_base + CVI_RTC_ALARM_ENABLE, 0x0);
}

static void hal_cvi_rtc_set_time(uintptr_t rtc_base, unsigned long sec)
{
    mmio_write_32(rtc_base + CVI_RTC_SET_SEC_CNTR_VALUE, sec);
    mmio_write_32(rtc_base + CVI_RTC_SET_SEC_CNTR_TRIG, 1);
    mmio_write_32(rtc_base + RTC_MACRO_RG_SET_T, sec);
    mmio_write_32(rtc_base + RTC_MACRO_DA_CLEAR_ALL, 1);
    mmio_write_32(rtc_base + RTC_MACRO_DA_SOC_READY, 1);
    mmio_write_32(rtc_base + RTC_MACRO_DA_CLEAR_ALL, 0);
    mmio_write_32(rtc_base + RTC_MACRO_RG_SET_T, 0);
    mmio_write_32(rtc_base + RTC_MACRO_DA_SOC_READY, 0);
}

static int hal_cvi_rtc_get_time_sec(uintptr_t rtc_base,unsigned long *ret_sec)
{
    int ret = 0;
    unsigned long sec;
    unsigned long sec_ro_t;

    sec = mmio_read_32(rtc_base + CVI_RTC_SEC_CNTR_VALUE);
    sec_ro_t = mmio_read_32(rtc_base + RTC_MACRO_RO_T);

    LOG_D("sec=%lx, sec_ro_t=%lx\n", sec, sec_ro_t);

    if (sec_ro_t > 0x30000000) {
            sec = sec_ro_t;
            // Writeback to SEC CVI_RTC_SEC_CNTR_VALUE
            mmio_write_32(rtc_base + CVI_RTC_SET_SEC_CNTR_VALUE, sec);
            mmio_write_32(rtc_base + CVI_RTC_SET_SEC_CNTR_TRIG, 1);
    } else if (sec < 0x30000000) {
        LOG_D("RTC invalid time\n");
        ret = -EINVAL;
    }

    *ret_sec = sec;

    return ret;
}

static inline int64_t div_u64_rem(uint64_t dividend, uint32_t divisor, uint32_t *remainder)
{
    *remainder = dividend % divisor;
    return dividend / divisor;
}

/*
 * rtc_time_to_tm64 - Converts time64_t to rtc_time.
 * Convert seconds since 01-01-1970 00:00:00 to Gregorian date.
 */
static void rtc_time64_to_tm(int64_t time, cvi_rtc_time_t *cvi_tm)
{
    unsigned int month, year, secs;
    int days;

    /* time must be positive */
    days = div_u64_rem(time, 86400, &secs);

    /* day of the week, 1970-01-01 was a Thursday */
    cvi_tm->tm_wday = (days + 4) % 7;

    year = 1970 + days / 365;
    days -= (year - 1970) * 365
        + LEAPS_THRU_END_OF(year - 1)
        - LEAPS_THRU_END_OF(1970 - 1);
    while (days < 0) {
        year -= 1;
        days += 365 + is_leap_year(year);
    }
    cvi_tm->tm_year = year - 1900;
    cvi_tm->tm_yday = days + 1;

    for (month = 0; month < 11; month++) {
        int newdays;

        newdays = days - rtc_month_days(month, year);
        if (newdays < 0)
            break;
        days = newdays;
    }
    cvi_tm->tm_mon = month;
    cvi_tm->tm_mday = days + 1;

    cvi_tm->tm_hour = secs / 3600;
    secs -= cvi_tm->tm_hour * 3600;
    cvi_tm->tm_min = secs / 60;
    cvi_tm->tm_sec = secs - cvi_tm->tm_min * 60;
}

static int64_t mktime64(const unsigned int year0, const unsigned int mon0,
        const unsigned int day, const unsigned int hour,
        const unsigned int min, const unsigned int sec)
{
    unsigned int mon = mon0, year = year0;

    /* 1..12 -> 11,12,1..10 */
    if (0 >= (int) (mon -= 2)) {
        mon += 12;  /* Puts Feb last since it has leap day */
        year -= 1;
    }

    return ((((int64_t)
          (year/4 - year/100 + year/400 + 367*mon/12 + day) +
          year*365 - 719499
        )*24 + hour /* now have hours - midnight tomorrow handled here */
      )*60 + min /* now have minutes */
    )*60 + sec; /* finally seconds */
}

/*
 * rtc_tm_to_time64 - Converts rtc_time to time64_t.
 * Convert Gregorian date to seconds since 01-01-1970 00:00:00.
 */
static int64_t rtc_tm_to_time64(const cvi_rtc_time_t *cvi_tm)
{
    return mktime64(cvi_tm->tm_year + 1900, cvi_tm->tm_mon + 1, cvi_tm->tm_mday,
            cvi_tm->tm_hour, cvi_tm->tm_min, cvi_tm->tm_sec);
}

static rt_err_t _rtc_get_timeval(struct timeval *tv)
{
    unsigned long sec;
    cvi_rtc_time_t t = {0};
    struct tm tm_new = {0};

    hal_cvi_rtc_get_time_sec(rtc_device.base, &sec);
    rtc_time64_to_tm(sec, &t);

    tm_new.tm_sec  = t.tm_sec;
    tm_new.tm_min  = t.tm_min;
    tm_new.tm_hour = t.tm_hour;
    tm_new.tm_wday = t.tm_wday;
    tm_new.tm_mday = t.tm_mday;
    tm_new.tm_mon  = t.tm_mon;
    tm_new.tm_year = t.tm_year;

    tv->tv_sec = timegm(&tm_new);

    return RT_EOK;
}

static rt_err_t _rtc_init(void)
{
    hal_cvi_rtc_clk_set(1);
    hal_cvi_rtc_enable_sec_counter(rtc_device.base);

    return RT_EOK;
}

static rt_err_t _rtc_get_secs(time_t *sec)
{
    struct timeval tv;

    _rtc_get_timeval(&tv);
    *(time_t *) sec = tv.tv_sec;
    LOG_D("RTC: get rtc_time %d", *sec);

    return RT_EOK;
}

static rt_err_t _rtc_set_secs(time_t *sec)
{
    rt_err_t result = RT_EOK;
    cvi_rtc_time_t t = {0};
    struct tm tm = {0};
    unsigned long set_sec;

    gmtime_r(sec, &tm);

    t.tm_sec     = tm.tm_sec;
    t.tm_min     = tm.tm_min;
    t.tm_hour    = tm.tm_hour;
    t.tm_mday    = tm.tm_mday;
    t.tm_mon     = tm.tm_mon;
    t.tm_year    = tm.tm_year;
    t.tm_wday    = tm.tm_wday;

    set_sec = rtc_tm_to_time64(&t);
    hal_cvi_rtc_set_time(rtc_device.base, set_sec);

    return result;
}

#ifdef RT_USING_ALARM
static void rtc_alarm_enable(rt_bool_t enable)
{
    mmio_write_32(rtc_device.base + CVI_RTC_ALARM_ENABLE, enable);
}

static void rt_hw_rtc_isr(int irqno, void *param)
{
    rt_interrupt_enter();

    /* send event to alarm */
    rt_alarm_update(&rtc_device.rtc_dev.parent, 1);
    /* clear alarm */
    rtc_alarm_enable(0);

    rt_interrupt_leave();
}

static rt_err_t _rtc_get_alarm(struct rt_rtc_wkalarm *alarm)
{
    if (alarm == RT_NULL)
        return -RT_ERROR;

    unsigned long int sec;
    cvi_rtc_time_t t = {0};

    sec = mmio_read_32(rtc_device.base + CVI_RTC_ALARM_TIME);
    rtc_time64_to_tm(sec, &t);

    alarm->tm_sec     = t.tm_sec;
    alarm->tm_min     = t.tm_min;
    alarm->tm_hour    = t.tm_hour;
    alarm->tm_mday    = t.tm_mday;
    alarm->tm_mon     = t.tm_mon;
    alarm->tm_year    = t.tm_year;
    LOG_D("GET_ALARM %d:%d:%d", alarm->tm_hour, alarm->tm_min, alarm->tm_sec);

    return RT_EOK;
}

static rt_err_t _rtc_set_alarm(struct rt_rtc_wkalarm *alarm)
{
    if (alarm == RT_NULL)
        return -RT_ERROR;

    cvi_rtc_time_t t = {0};
    unsigned long int set_sec;

    if (alarm->enable){
        t.tm_sec     = alarm->tm_sec;
        t.tm_min     = alarm->tm_min;
        t.tm_hour    = alarm->tm_hour;
        t.tm_mday    = alarm->tm_mday;
        t.tm_mon     = alarm->tm_mon;
        t.tm_year    = alarm->tm_year;

        set_sec = rtc_tm_to_time64(&t);
        mmio_write_32(rtc_device.base + CVI_RTC_ALARM_TIME, set_sec);

        LOG_D("GET_ALARM %d:%d:%d", alarm->tm_hour, alarm->tm_min, alarm->tm_sec);
    }

    rtc_alarm_enable(alarm->enable);

    return RT_EOK;
}
#endif

static const struct rt_rtc_ops _rtc_ops =
{
    _rtc_init,
    _rtc_get_secs,
    _rtc_set_secs,
#ifdef RT_USING_ALARM
    _rtc_get_alarm,
    _rtc_set_alarm,
#else
    RT_NULL,
    RT_NULL,
#endif
    _rtc_get_timeval,
    RT_NULL,
};

static int rt_hw_rtc_init(void)
{
    rt_err_t result;

    rtc_device.rtc_dev.ops = &_rtc_ops;

    rtc_device.base = CVI_RTC_BASE;
    rtc_device.base = (rt_ubase_t)DRV_IOREMAP((void *)rtc_device.base, 0x1000);

    result = rt_hw_rtc_register(&rtc_device.rtc_dev, "rtc", RT_DEVICE_FLAG_RDWR, RT_NULL);
    if (result != RT_EOK)
    {
        LOG_E("rtc register err code: %d", result);
        return result;
    }

#ifdef RT_USING_ALARM
    rt_hw_interrupt_install(RTC_ALARM_IRQ_NUM, rt_hw_rtc_isr, RT_NULL, "rtc");
    rt_hw_interrupt_umask(RTC_ALARM_IRQ_NUM);
#endif

    LOG_D("rtc init success");

    return RT_EOK;
}
INIT_DEVICE_EXPORT(rt_hw_rtc_init);
