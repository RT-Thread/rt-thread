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
    #define BSP_RTC_ALARM          RTC_ALARM0
    #define BSP_RTC_INT_ALARM      RTC_INT_ALARM0
#elif defined(BSP_USING_ALARM1)
    #define BSP_ALARM_FLAG         RTC_FLAG_ALARM1
    #define BSP_RTC_ALARM          RTC_ALARM1
    #define BSP_RTC_INT_ALARM      RTC_INT_ALARM1
#endif
#endif

#if defined(SOC_SERIES_GD32H7xx) || defined(SOC_SERIES_GD32F5xx)

#define rtc_year            year
#define rtc_month           month
#define rtc_date            date
#define rtc_day_of_week     day_of_week
#define rtc_hour            hour
#define rtc_minute          minute
#define rtc_second          second
#define rtc_display_format  display_format

#endif

static time_t get_rtc_timestamp(void);
static rt_err_t set_rtc_timestamp(time_t time_stamp);

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
    /* Enable PMU and backup domain clocks */
    rcu_periph_clock_enable(RCU_PMU);
    pmu_backup_write_enable();

    /* Enable BKP and RTC clocks */
#ifdef SOC_SERIES_GD32F10x
    rcu_periph_clock_enable(RCU_BKPI);
#else
    rcu_periph_clock_enable(RCU_RTC);
#endif

    /* Check if RTC is already initialized by backup domain reset */
    if (RTC_STAT & RTC_STAT_INITF)
    {
        LOG_D("RTC already initialized");
        return RT_EOK;
    }

    /* Reset backup domain only if RTC is not running */
    if ((RTC_STAT & RTC_STAT_RSYNF) == 0)
    {
        rcu_bkp_reset_enable();
        rcu_bkp_reset_disable();

        /* Re-enable clocks after reset */
#ifdef SOC_SERIES_GD32F10x
        rcu_periph_clock_enable(RCU_BKPI);
#else
        rcu_periph_clock_enable(RCU_RTC);
#endif
    }

    /* Use LSE (32.768kHz) as RTC clock source */
#define PRESCALER_S     0xFF
#define PRESCALER_A     0x7F

    rcu_osci_on(RCU_LXTAL);
    if (rcu_osci_stab_wait(RCU_LXTAL) != SUCCESS)
    {
        LOG_E("LSE oscillator failed to stabilize");
        return -RT_ERROR;
    }
    rcu_rtc_clock_config(RCU_RTCSRC_LXTAL);
    LOG_D("RTC clock source: LSE (32.768kHz)");

    /* Wait for RTC registers synchronization */
    if (rtc_register_sync_wait() != SUCCESS)
    {
        LOG_E("RTC register synchronization failed");
        return -RT_ERROR;
    }

    /* Set default time if RTC is not initialized */
    if ((RTC_DATE == 0) || (RTC_TIME == 0))
    {
        time_t default_time = 1704067200; /* 2024-01-01 00:00:00 */
        if (set_rtc_timestamp(default_time) != RT_EOK)
        {
            LOG_E("Failed to set default RTC time");
            return -RT_ERROR;
        }
        LOG_D("RTC set to default time: 2024-01-01 00:00:00");
    }

    LOG_D("RTC initialization successful");
    return RT_EOK;
}

static time_t get_rtc_timestamp(void)
{
    struct tm tm_new = {0};
    rtc_parameter_struct rtc_current_time;

    /* Wait for register synchronization before reading */
    if (rtc_register_sync_wait() != SUCCESS)
    {
        LOG_E("RTC sync failed before reading time");
        return 0;
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
    return timegm(&tm_new);
}

static rt_err_t gd_get_secs(time_t *sec)
{
    if (sec == RT_NULL)
    {
        return -RT_EINVAL;
    }

    *sec = get_rtc_timestamp();
    LOG_D("RTC: get timestamp %lu", *sec);

    return RT_EOK;
}

static rt_err_t set_rtc_timestamp(time_t time_stamp)
{
    struct tm now;
    rtc_parameter_struct rtc_init_struct;
    ErrStatus status;

    /* Use gmtime_r for thread safety */
    gmtime_r(&time_stamp, &now);

    if (now.tm_year < 100)
    {
        LOG_E("Year must be >= 2000");
        return -RT_ERROR;
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

    status = rtc_init(&rtc_init_struct);
    if (status != SUCCESS)
    {
        LOG_E("RTC time set failed: %d", status);
        return -RT_ERROR;
    }

    /* Wait for synchronization after setting time */
    if (rtc_register_sync_wait() != SUCCESS)
    {
        LOG_E("RTC sync failed after setting time");
        return -RT_ERROR;
    }

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
    if (alarm == RT_NULL)
    {
        return -RT_EINVAL;
    }

    rtc_alarm_struct rtc_alarm;

    rtc_alarm_disable(BSP_RTC_ALARM);
    /* Initialize alarm structure */
    rtc_alarm.alarm_mask = RTC_ALARM_ALL_MASK;
    rtc_alarm.weekday_or_date = RTC_ALARM_DATE_SELECTED;
    rtc_alarm.alarm_day = 1; /* Not used when mask is set to ALL_MASK */
    rtc_alarm.alarm_hour = bin_to_bcd(alarm->tm_hour);
    rtc_alarm.alarm_minute = bin_to_bcd(alarm->tm_min);
    rtc_alarm.alarm_second = bin_to_bcd(alarm->tm_sec);
    rtc_alarm.am_pm = RTC_AM;

    /* Configure alarm */
    rtc_alarm_config(BSP_RTC_ALARM, &rtc_alarm);

    /* Enable or disable alarm */
    if (alarm->enable)
    {
        /* Clear any pending alarm flag first */
        rtc_flag_clear(BSP_ALARM_FLAG);

        /* Clear EXTI line 17 flag */
        exti_flag_clear(EXTI_17);

        /* Enable RTC alarm interrupt */
        rtc_interrupt_enable(BSP_RTC_INT_ALARM);

        /* Enable alarm */
        rtc_alarm_enable(BSP_RTC_ALARM);

        /* Configure EXTI line 17 for RTC alarm interrupt */
        exti_init(EXTI_17, EXTI_INTERRUPT, EXTI_TRIG_RISING);

        /* Enable RTC Alarm global interrupt in NVIC */
        nvic_irq_enable(RTC_Alarm_IRQn, 0, 0);

        LOG_D("RTC Alarm enabled with interrupt");
    }
    else
    {
        /* Disable alarm interrupt first */
        rtc_interrupt_disable(BSP_RTC_INT_ALARM);

        /* Disable alarm */
        rtc_alarm_disable(BSP_RTC_ALARM);

        /* Clear alarm flag */
        rtc_flag_clear(BSP_ALARM_FLAG);
        exti_flag_clear(EXTI_17);

        LOG_D("RTC Alarm disabled");
    }

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
