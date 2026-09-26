/*
 * Copyright (c) 2006-2025, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author            Notes
 * 2022-01-25     iysheng           first version
 * 2025-09-25     kurisaw           adapt to rt_rtc_ops interface
 * 2025-09-25     kurisaw           add alarm interrupt support
 * 2026-09-08     CYFS              fix RTC startup, backup state, and alarm synchronization
 */

#include <board.h>
#include <rtdevice.h>
#include <rthw.h>
#include <sys/time.h>

#define DBG_TAG             "drv.rtc"
#define DBG_LVL             DBG_INFO

#include <rtdbg.h>

#ifdef RT_USING_RTC

#if defined(BSP_USING_ALARM)
#if defined(BSP_USING_ALARM0) && defined(BSP_USING_ALARM1)
#error "Only supports using one alarm at a time."
#elif !defined(BSP_USING_ALARM0) && !defined(BSP_USING_ALARM1)
#error "Please Enable RTC alarm define (BSP_USING_ALARM0 | BSP_USING_ALARM1)"
#elif defined(BSP_USING_ALARM0)
    #define BSP_ALARM_FLAG         RTC_FLAG_ALARM0
    #define BSP_ALARM_WRITE_FLAG   RTC_FLAG_ALARM0W
    #define BSP_RTC_ALARM          RTC_ALARM0
    #define BSP_RTC_INT_ALARM      RTC_INT_ALARM0
#elif defined(BSP_USING_ALARM1)
    #define BSP_ALARM_FLAG         RTC_FLAG_ALARM1
    #define BSP_ALARM_WRITE_FLAG   RTC_FLAG_ALARM1W
    #define BSP_RTC_ALARM          RTC_ALARM1
    #define BSP_RTC_INT_ALARM      RTC_INT_ALARM1
#endif
#endif

#if (defined(SOC_SERIES_GD32H7xx) || defined(SOC_SERIES_GD32H77x_H78X)) || defined(SOC_SERIES_GD32F5xx)

#define rtc_year            year
#define rtc_month           month
#define rtc_date            date
#define rtc_day_of_week     day_of_week
#define rtc_hour            hour
#define rtc_minute          minute
#define rtc_second          second
#define rtc_display_format  display_format

#endif

#define RTC_LXTAL_TIMEOUT_MS  5000U
#define RTC_STATUS_TIMEOUT_MS 1000U
#define PRESCALER_S          0xFFU
#define PRESCALER_A          0x7FU
/* Reserve RTC_BKP0 to retain initialization state even when the year is 2000. */
#define RTC_INIT_MARKER      0x52544301U

static rt_err_t get_rtc_timestamp(time_t *time_stamp);
static rt_err_t set_rtc_timestamp(time_t time_stamp);

static rt_err_t gd_rtc_wait_flag(uint32_t flag)
{
    rt_uint32_t remaining_ms = RTC_STATUS_TIMEOUT_MS;

    while (rtc_flag_get(flag) == RESET)
    {
        if (remaining_ms == 0U)
        {
            return -RT_ETIMEOUT;
        }
        rt_hw_us_delay(1000);
        remaining_ms--;
    }

    return RT_EOK;
}

static rt_err_t gd_rtc_sync_wait(void)
{
    if (rtc_register_sync_wait() == SUCCESS)
    {
        return RT_EOK;
    }

    /* Keep waiting without clearing RSYNF again if the library loop was too short. */
    return gd_rtc_wait_flag(RTC_FLAG_RSYN);
}

/**
 * @brief  Helper function: Convert BCD value to binary.
 * @param  val: BCD value.
 * @return Binary value.
 */
static rt_uint8_t bcd_to_bin(rt_uint8_t val)
{
    return (val & 0x0F) + ((val >> 4) & 0x0F) * 10;
}

/**
 * @brief  Helper function: Convert binary to BCD.
 * @param  val: Binary value.
 * @return BCD value.
 */
static rt_uint8_t bin_to_bcd(rt_uint8_t val)
{
    return ((val / 10) << 4) | (val % 10);
}

#ifdef BSP_USING_ALARM
/* RTC device for alarm callback */
static rt_device_t g_rtc_device = RT_NULL;

/**
 * @brief RTC Alarm Interrupt Handler
 */
void RTC_Alarm_IRQHandler(void)
{
    rt_interrupt_enter();

    /* Check if alarm interrupt occurred */
    if (rtc_flag_get(RTC_FLAG_ALARM0) != RESET)
    {
        /* Clear alarm flag */
        rtc_flag_clear(RTC_FLAG_ALARM0);
        exti_flag_clear(EXTI_17);

        /* Notify RTC framework about alarm event */
        if (g_rtc_device != RT_NULL)
        {
            rt_alarm_update(g_rtc_device, 1);
        }
        LOG_D("RTC Alarm0 triggered");
    }

    if (rtc_flag_get(RTC_FLAG_ALARM1) != RESET)
    {
        /* Clear alarm flag */
        rtc_flag_clear(RTC_FLAG_ALARM1);
        exti_flag_clear(EXTI_17);

        /* Notify RTC framework about alarm event */
        if (g_rtc_device != RT_NULL)
        {
            rt_alarm_update(g_rtc_device, 1);
        }
        LOG_D("RTC Alarm1 triggered");
    }

    rt_interrupt_leave();
}
#endif /* BSP_USING_ALARM */

static rt_err_t gd_rtc_init(void)
{
    rt_uint32_t remaining_ms = RTC_LXTAL_TIMEOUT_MS;
    uint32_t clock_source;
    rt_err_t result;

    /* Enable PMU and backup domain clocks */
    rcu_periph_clock_enable(RCU_PMU);
    pmu_backup_write_enable();

    /* Enable access to backup registers on devices with a separate BKP clock. */
#ifdef SOC_SERIES_GD32F10x
    rcu_periph_clock_enable(RCU_BKPI);
#endif

    /* A backup reset is needed only when changing an already selected source. */
    clock_source = RCU_BDCTL & RCU_BDCTL_RTCSRC;
    if ((clock_source != RCU_RTCSRC_NONE) && (clock_source != RCU_RTCSRC_LXTAL))
    {
        LOG_W("RTC clock source changed; resetting backup domain");
        rcu_bkp_reset_enable();
        rcu_bkp_reset_disable();
#ifdef SOC_SERIES_GD32F10x
        rcu_periph_clock_enable(RCU_BKPI);
#endif
    }

    /* Use a timed wait: a fixed CPU loop can expire before the crystal starts. */
    rcu_osci_on(RCU_LXTAL);
    while (rcu_flag_get(RCU_FLAG_LXTALSTB) == RESET)
    {
        if (remaining_ms == 0U)
        {
            LOG_E("LXTAL failed to stabilize within %u ms, RCU_BDCTL=0x%08x",
                  RTC_LXTAL_TIMEOUT_MS, (unsigned int)RCU_BDCTL);
            return -RT_ETIMEOUT;
        }
        rt_hw_us_delay(1000);
        remaining_ms--;
    }
    rcu_rtc_clock_config(RCU_RTCSRC_LXTAL);
    rcu_periph_clock_enable(RCU_RTC);
    LOG_D("RTC clock source: LSE (32.768kHz)");

    /* Recover an interrupted initialization without erasing the calendar. */
    RTC_WPK = RTC_UNLOCK_KEY1;
    RTC_WPK = RTC_UNLOCK_KEY2;
    rtc_init_mode_exit();
    RTC_WPK = RTC_LOCK_KEY;

    /* Wait for RTC registers synchronization */
    result = gd_rtc_sync_wait();
    if (result != RT_EOK)
    {
        LOG_E("RTC register synchronization timed out, RTC_STAT=0x%08x",
              (unsigned int)RTC_STAT);
        return result;
    }

    /* INITF means init mode, and 00:00:00 is a valid time, not an empty RTC. */
    if ((RTC_BKP0 != RTC_INIT_MARKER) && (rtc_flag_get(RTC_FLAG_YCM) == RESET))
    {
        time_t default_time = 1704067200; /* 2024-01-01 00:00:00 */
        result = set_rtc_timestamp(default_time);
        if (result != RT_EOK)
        {
            LOG_E("Failed to set default RTC time");
            return result;
        }
        LOG_D("RTC set to default time: 2024-01-01 00:00:00");
    }
    RTC_BKP0 = RTC_INIT_MARKER;

    LOG_D("RTC initialization successful");
    return RT_EOK;
}

static rt_err_t get_rtc_timestamp(time_t *time_stamp)
{
    struct tm tm_new = {0};
    rtc_parameter_struct rtc_current_time;
    rt_err_t result;

    /* Wait for register synchronization before reading */
    result = gd_rtc_sync_wait();
    if (result != RT_EOK)
    {
        LOG_E("RTC sync failed before reading time");
        return result;
    }

    rtc_current_time_get(&rtc_current_time);

    /* Convert BCD to binary and adjust year/month values */
    tm_new.tm_year = bcd_to_bin(rtc_current_time.rtc_year) + 100; /* RTC year starts from 2000 */
    tm_new.tm_mon  = bcd_to_bin(rtc_current_time.rtc_month) - 1;  /* tm_mon: 0-11 */
    tm_new.tm_mday = bcd_to_bin(rtc_current_time.rtc_date);
    tm_new.tm_hour = bcd_to_bin(rtc_current_time.rtc_hour);
    tm_new.tm_min  = bcd_to_bin(rtc_current_time.rtc_minute);
    tm_new.tm_sec  = bcd_to_bin(rtc_current_time.rtc_second);

    /* Convert weekday: RTC uses 1-7 (Monday-Sunday), tm uses 0-6 (Sunday-Saturday) */
    uint8_t rtc_wday = bcd_to_bin(rtc_current_time.rtc_day_of_week);
    tm_new.tm_wday = (rtc_wday == 7) ? 0 : rtc_wday; /* Sunday conversion */

    /* Calculate day of year */
    tm_new.tm_yday = 0; /* Will be calculated by timegm */
    tm_new.tm_isdst = 0; /* No daylight saving */

    /* Use timegm instead of mktime to avoid timezone issues */
    *time_stamp = timegm(&tm_new);
    return RT_EOK;
}

static rt_err_t gd_get_secs(time_t *sec)
{
    rt_err_t result;

    if (sec == RT_NULL)
    {
        return -RT_EINVAL;
    }

    result = get_rtc_timestamp(sec);
    if (result == RT_EOK)
    {
        LOG_D("RTC: get timestamp %lu", *sec);
    }

    return result;
}

static rt_err_t set_rtc_timestamp(time_t time_stamp)
{
    struct tm now;
    rtc_parameter_struct rtc_init_struct;
    rt_err_t result;

    /* Use gmtime_r for thread safety */
    if ((gmtime_r(&time_stamp, &now) == RT_NULL) ||
        (now.tm_year < 100) || (now.tm_year > 199))
    {
        LOG_E("Year must be between 2000 and 2099");
        return -RT_EINVAL;
    }

    /* Convert to BCD format */
    rtc_init_struct.rtc_year = bin_to_bcd(now.tm_year - 100); /* RTC year: 0-99 (2000-2099) */
    rtc_init_struct.rtc_month = bin_to_bcd(now.tm_mon + 1);   /* RTC month: 1-12 */
    rtc_init_struct.rtc_date = bin_to_bcd(now.tm_mday);

    /* Convert weekday: tm_wday 0-6 (Sun-Sat) to RTC 1-7 (Mon-Sun) */
    rtc_init_struct.rtc_day_of_week = bin_to_bcd(now.tm_wday == 0 ? 7 : now.tm_wday);

    rtc_init_struct.rtc_hour = bin_to_bcd(now.tm_hour);
    rtc_init_struct.rtc_minute = bin_to_bcd(now.tm_min);
    rtc_init_struct.rtc_second = bin_to_bcd(now.tm_sec);
    rtc_init_struct.rtc_display_format = RTC_24HOUR;

    /* Use default prescaler values */
    rtc_init_struct.factor_asyn = PRESCALER_A;
    rtc_init_struct.factor_syn = PRESCALER_S;
    rtc_init_struct.am_pm = RTC_AM;

    /* Enter init mode with a timed wait before the library's fixed-loop check. */
    RTC_WPK = RTC_UNLOCK_KEY1;
    RTC_WPK = RTC_UNLOCK_KEY2;
    RTC_STAT |= RTC_STAT_INITM;
    result = gd_rtc_wait_flag(RTC_FLAG_INIT);
    if (result != RT_EOK)
    {
        rtc_init_mode_exit();
        RTC_WPK = RTC_LOCK_KEY;
        LOG_E("RTC init mode timed out, RTC_STAT=0x%08x", (unsigned int)RTC_STAT);
        return result;
    }

    /* INITF is already set; rtc_init() can now fail only on its final sync wait. */
    if (rtc_init(&rtc_init_struct) != SUCCESS)
    {
        result = gd_rtc_wait_flag(RTC_FLAG_RSYN);
        if (result != RT_EOK)
        {
            LOG_E("RTC sync timed out after setting time, RTC_STAT=0x%08x",
                  (unsigned int)RTC_STAT);
            return result;
        }
    }
    RTC_BKP0 = RTC_INIT_MARKER;

    LOG_D("RTC time set successfully: %lu", time_stamp);
    return RT_EOK;
}

static rt_err_t gd_set_secs(time_t *sec)
{
    if (sec == RT_NULL)
    {
        return -RT_EINVAL;
    }

    rt_err_t result = set_rtc_timestamp(*sec);
    if (result == RT_EOK)
    {
        LOG_D("RTC: set rtc_time %lu", *sec);
    }
    else
    {
        LOG_E("RTC: set rtc_time failed %lu", *sec);
    }

    return result;
}

#ifdef BSP_USING_ALARM
static rt_err_t gd_get_alarm(struct rt_rtc_wkalarm *alarm)
{
    if (alarm == RT_NULL)
    {
        return -RT_EINVAL;
    }

    rtc_alarm_struct rtc_alarm;

    /* Get current alarm configuration */
    rtc_alarm_get(BSP_RTC_ALARM, &rtc_alarm);

    /* Convert RTC alarm to RT-Thread alarm format */
    alarm->tm_hour = bcd_to_bin(rtc_alarm.alarm_hour);
    alarm->tm_min = bcd_to_bin(rtc_alarm.alarm_minute);
    alarm->tm_sec = bcd_to_bin(rtc_alarm.alarm_second);

    /* Check if alarm is enabled */
    uint32_t alarm_enable_bit = (BSP_RTC_ALARM == RTC_ALARM0) ? RTC_CTL_ALRM0EN : RTC_CTL_ALRM1EN;
    alarm->enable = (RTC_CTL & alarm_enable_bit) ? 1 : 0;

    LOG_D("RTC: get alarm %02d:%02d:%02d, enable: %d",
          alarm->tm_hour, alarm->tm_min, alarm->tm_sec, alarm->enable);

    return RT_EOK;
}

static rt_err_t gd_set_alarm(struct rt_rtc_wkalarm *alarm)
{
    rtc_alarm_struct rtc_alarm;
    rt_err_t result;

    if (alarm == RT_NULL)
    {
        return -RT_EINVAL;
    }

    if (alarm->enable && (((rt_uint32_t)alarm->tm_hour > 23U) ||
        ((rt_uint32_t)alarm->tm_min > 59U) || ((rt_uint32_t)alarm->tm_sec > 59U)))
    {
        return -RT_EINVAL;
    }

    rtc_interrupt_disable(BSP_RTC_INT_ALARM);
    if (rtc_alarm_disable(BSP_RTC_ALARM) != SUCCESS)
    {
        result = gd_rtc_wait_flag(BSP_ALARM_WRITE_FLAG);
        if (result != RT_EOK)
        {
            LOG_E("RTC alarm registers are not writable: %d", result);
            return result;
        }
    }
    rtc_flag_clear(BSP_ALARM_FLAG);
    exti_flag_clear(EXTI_17);

    if (!alarm->enable)
    {
        LOG_D("RTC alarm disabled");
        return RT_EOK;
    }

    /* Initialize alarm structure */
    rtc_alarm.alarm_mask = RTC_ALARM_DATE_MASK;
    rtc_alarm.weekday_or_date = RTC_ALARM_DATE_SELECTED;
    rtc_alarm.alarm_day = 1; /* The RT-Thread Alarm service checks the full date. */
    rtc_alarm.alarm_hour = bin_to_bcd(alarm->tm_hour);
    rtc_alarm.alarm_minute = bin_to_bcd(alarm->tm_min);
    rtc_alarm.alarm_second = bin_to_bcd(alarm->tm_sec);
    rtc_alarm.am_pm = RTC_AM;

    /* Configure alarm */
    rtc_alarm_config(BSP_RTC_ALARM, &rtc_alarm);
    rtc_alarm_subsecond_config(BSP_RTC_ALARM, RTC_MSKSSC_0_14, 0);

    /* Route the interrupt before enabling the comparator. */
    exti_init(EXTI_17, EXTI_INTERRUPT, EXTI_TRIG_RISING);
    nvic_irq_enable(RTC_Alarm_IRQn, 0, 0);
    rtc_interrupt_enable(BSP_RTC_INT_ALARM);
    rtc_alarm_enable(BSP_RTC_ALARM);

    LOG_D("RTC: set alarm %02d:%02d:%02d, enable: %d",
          alarm->tm_hour, alarm->tm_min, alarm->tm_sec, alarm->enable);

    return RT_EOK;
}
#endif /* BSP_USING_ALARM */

static const struct rt_rtc_ops gd_rtc_ops =
{
    .init      = gd_rtc_init,
    .get_secs  = gd_get_secs,
    .set_secs  = gd_set_secs,
#ifdef BSP_USING_ALARM
    .set_alarm = gd_set_alarm,
    .get_alarm = gd_get_alarm,
#endif
};

static rt_rtc_dev_t gd_rtc_dev;

static int rt_hw_rtc_init(void)
{
    rt_err_t result;

    gd_rtc_dev.ops = &gd_rtc_ops;

    result = rt_hw_rtc_register(&gd_rtc_dev, "rtc", RT_DEVICE_FLAG_RDWR, RT_NULL);
    if (result != RT_EOK)
    {
        LOG_E("RTC register failed: %d", result);
        return result;
    }

#ifdef BSP_USING_ALARM
    /* Store RTC device for alarm callback */
    g_rtc_device = rt_device_find("rtc");
    if (g_rtc_device == RT_NULL)
    {
        LOG_W("RTC device not found for alarm callback");
    }
#endif

    LOG_D("RTC hardware init success");
    return RT_EOK;
}
INIT_DEVICE_EXPORT(rt_hw_rtc_init);

#endif /* RT_USING_RTC */
