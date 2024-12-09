/*
 * Copyright (c) 2006-2021, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date         Author         Notes
 * 2022-05-16   shelton        first version
 * 2023-04-08   shelton        add support f423
 * 2023-10-18   shelton        add support f402/f405
 * 2024-04-12   shelton        add support a403a and a423
 * 2024-08-30   shelton        add support m412 and m416
 */

#include <rtthread.h>
#include <rtdevice.h>
#include <sys/time.h>
#include "drv_common.h"

#ifdef BSP_USING_RTC

//#define DRV_DEBUG
#define LOG_TAG                         "drv.rtc"
#include <drv_log.h>

#define BKUP_REG_DATA                   0xA5A5

#if   defined (SOC_SERIES_AT32F403A) || defined (SOC_SERIES_AT32F407) || \
      defined (SOC_SERIES_AT32F413)  || defined (SOC_SERIES_AT32A403A)
#define Alarm_IRQn                      RTCAlarm_IRQn
#define Alarm_IRQHandler                RTCAlarm_IRQHandler
#elif defined (SOC_SERIES_AT32F421)  || defined (SOC_SERIES_AT32F425)
#define Alarm_IRQn                      RTC_IRQn
#define Alarm_IRQHandler                RTC_IRQHandler
#else
#define Alarm_IRQn                      ERTCAlarm_IRQn
#define Alarm_IRQHandler                ERTCAlarm_IRQHandler
#endif

struct rtc_device_object
{
    rt_rtc_dev_t rtc_dev;
#ifdef RT_USING_ALARM
    struct rt_rtc_wkalarm   wkalarm;
#endif
};

static struct rtc_device_object rtc_device;

static time_t get_rtc_timestamp(void)
{
#if defined (SOC_SERIES_AT32F435) || defined (SOC_SERIES_AT32F437) || \
    defined (SOC_SERIES_AT32F415) || defined (SOC_SERIES_AT32F421) || \
    defined (SOC_SERIES_AT32F425) || defined (SOC_SERIES_AT32F423) || \
    defined (SOC_SERIES_AT32F402) || defined (SOC_SERIES_AT32F405) || \
    defined (SOC_SERIES_AT32A423) || defined (SOC_SERIES_AT32M412) || \
    defined (SOC_SERIES_AT32M416)
    struct tm tm_new;
    ertc_time_type ertc_time_struct;

    ertc_calendar_get(&ertc_time_struct);

    tm_new.tm_sec = ertc_time_struct.sec;
    tm_new.tm_min = ertc_time_struct.min;
    tm_new.tm_hour = ertc_time_struct.hour;
    tm_new.tm_mday = ertc_time_struct.day;
    tm_new.tm_mon = ertc_time_struct.month - 1;
    tm_new.tm_year = ertc_time_struct.year + 100;

    LOG_D("get rtc time.");

    return timegm(&tm_new);
#else
    return rtc_counter_get();
#endif
}

static rt_err_t set_rtc_time_stamp(time_t time_stamp)
{
#if defined (SOC_SERIES_AT32F435) || defined (SOC_SERIES_AT32F437) || \
    defined (SOC_SERIES_AT32F415) || defined (SOC_SERIES_AT32F421) || \
    defined (SOC_SERIES_AT32F425) || defined (SOC_SERIES_AT32F423) || \
    defined (SOC_SERIES_AT32F402) || defined (SOC_SERIES_AT32F405) || \
    defined (SOC_SERIES_AT32A423) || defined (SOC_SERIES_AT32M412) || \
    defined (SOC_SERIES_AT32M416)
    struct tm now;

    gmtime_r(&time_stamp, &now);
    if (now.tm_year < 100)
    {
        return -RT_ERROR;
    }

    /* set time */
    if(ertc_time_set(now.tm_hour, now.tm_min, now.tm_sec, ERTC_AM) != SUCCESS)
    {
        return -RT_ERROR;
    }

    /* set date */
    if(ertc_date_set(now.tm_year - 100, now.tm_mon + 1, now.tm_mday, now.tm_wday + 1) != SUCCESS)
    {
        return -RT_ERROR;
    }

    LOG_D("set rtc time.");

    /* indicator for the ertc configuration */
    ertc_bpr_data_write(ERTC_DT1, BKUP_REG_DATA);
#else
    /* set the rtc counter value */
    rtc_counter_set(time_stamp);
    /* wait until last write operation on rtc registers has finished */
    rtc_wait_config_finish();
    LOG_D("set rtc time.");

    bpr_data_write(BPR_DATA1, BKUP_REG_DATA);
#endif

    return RT_EOK;
}

static rt_err_t rt_rtc_config(void)
{
    /* allow access to pattery powered domain */
    pwc_battery_powered_domain_access(TRUE);

#if defined (SOC_SERIES_AT32F435) || defined (SOC_SERIES_AT32F437) || \
    defined (SOC_SERIES_AT32F415) || defined (SOC_SERIES_AT32F421) || \
    defined (SOC_SERIES_AT32F425) || defined (SOC_SERIES_AT32F423) || \
    defined (SOC_SERIES_AT32F402) || defined (SOC_SERIES_AT32F405) || \
    defined (SOC_SERIES_AT32A423) || defined (SOC_SERIES_AT32M412) || \
    defined (SOC_SERIES_AT32M416)

    /* select rtc clock source */
#ifdef BSP_RTC_USING_LICK
    crm_ertc_clock_select(CRM_ERTC_CLOCK_LICK);
#else
    crm_ertc_clock_select(CRM_ERTC_CLOCK_LEXT);
#endif /* BSP_RTC_USING_LICK */

    /* enable rtc */
    crm_ertc_clock_enable(TRUE);

    /* wait for ertc registers update */
    ertc_wait_update();

    if (ertc_bpr_data_read(ERTC_DT1)!= BKUP_REG_DATA)
    {
        LOG_I("RTC hasn't been configured, please use <date> command to config.");

        /* configure the ertc divider */
        ertc_divider_set(0x7F, 0xFF);
        /* configure the ertc hour mode */
        ertc_hour_mode_set(ERTC_HOUR_MODE_24);
    }
#else

#ifdef BSP_RTC_USING_LICK
    crm_rtc_clock_select(CRM_RTC_CLOCK_LICK);
#else
    crm_rtc_clock_select(CRM_RTC_CLOCK_LEXT);
#endif /* BSP_RTC_USING_LICK */
    /* enable rtc */
    crm_rtc_clock_enable(TRUE);

    /* wait for rtc registers update finish */
    rtc_wait_update_finish();
    /* wait until last write operation on rtc registers has finished */
    rtc_wait_config_finish();

    if (bpr_data_read(BPR_DATA1) != BKUP_REG_DATA)
    {
        LOG_I("RTC hasn't been configured, please use <date> command to config.");
        /* set rtc divider: set rtc period to 1sec */
        rtc_divider_set(32767);
        /* wait until last write operation on rtc registers has finished */
        rtc_wait_config_finish();
    }
#endif

    return RT_EOK;
}

static rt_err_t _rtc_init(void)
{
    crm_periph_clock_enable(CRM_PWC_PERIPH_CLOCK, TRUE);

#if defined (SOC_SERIES_AT32F403A) || defined (SOC_SERIES_AT32F407) || \
    defined (SOC_SERIES_AT32F413)  || defined (SOC_SERIES_AT32A403A)
    crm_periph_clock_enable(CRM_BPR_PERIPH_CLOCK, TRUE);
#endif

#ifdef BSP_RTC_USING_LICK
    crm_clock_source_enable(CRM_CLOCK_SOURCE_LICK, TRUE);
    while(crm_flag_get(CRM_LICK_STABLE_FLAG) == RESET);
#else
    pwc_battery_powered_domain_access(TRUE);
    crm_clock_source_enable(CRM_CLOCK_SOURCE_LEXT, TRUE);
    while(crm_flag_get(CRM_LEXT_STABLE_FLAG) == RESET);
#endif /* BSP_RTC_USING_LICK */

    if (rt_rtc_config() != RT_EOK)
    {
        LOG_E("rtc init failed.");
        return -RT_ERROR;
    }

    return RT_EOK;
}

static rt_err_t _rtc_get_secs(time_t *args)
{
    *(rt_uint32_t *)args = get_rtc_timestamp();
    LOG_D("RTC: get rtc_time %x\n", *(rt_uint32_t *)args);

    return RT_EOK;
}

static rt_err_t _rtc_set_secs(time_t *args)
{
    rt_err_t result = RT_EOK;

    if (set_rtc_time_stamp(*(rt_uint32_t *)args))
    {
        result = -RT_ERROR;
    }
    LOG_D("RTC: set rtc_time %x\n", *(rt_uint32_t *)args);

    return result;
}

#ifdef RT_USING_ALARM
static rt_err_t rtc_alarm_time_set(struct rtc_device_object* p_dev)
{
    exint_init_type exint_init_struct;

#if defined (SOC_SERIES_AT32F403A) || defined (SOC_SERIES_AT32F407) || \
    defined (SOC_SERIES_AT32F413)  || defined (SOC_SERIES_AT32A403A)
    struct tm tm_new;
    time_t sec_count;
#endif
    /* config the exint line of the rtc alarm */
    exint_init_struct.line_select = EXINT_LINE_17;
    exint_init_struct.line_enable = TRUE;
    exint_init_struct.line_mode = EXINT_LINE_INTERRUPUT;
    exint_init_struct.line_polarity = EXINT_TRIGGER_RISING_EDGE;
    exint_init(&exint_init_struct);

    if (p_dev->wkalarm.enable)
    {
        nvic_irq_enable(Alarm_IRQn, 0, 0);

#if defined (SOC_SERIES_AT32F403A) || defined (SOC_SERIES_AT32F407) || \
    defined (SOC_SERIES_AT32F413)  || defined (SOC_SERIES_AT32A403A)
        /* clear alarm flag */
        rtc_flag_clear(RTC_TA_FLAG);
        /* wait for the register write to complete */
        rtc_wait_config_finish();
        /* enable alarm interrupt */
        rtc_interrupt_enable(RTC_TA_INT, TRUE);
        /* wait for the register write to complete */
        rtc_wait_config_finish();

        tm_new.tm_sec = p_dev->wkalarm.tm_sec;
        tm_new.tm_min = p_dev->wkalarm.tm_min;
        tm_new.tm_hour = p_dev->wkalarm.tm_hour;
        tm_new.tm_mday = p_dev->wkalarm.tm_mday;
        tm_new.tm_mon = p_dev->wkalarm.tm_mon;
        tm_new.tm_year = p_dev->wkalarm.tm_year;

        sec_count = timegm(&tm_new);
        rtc_alarm_set(sec_count);
        /* wait for the register write to complete */
        rtc_wait_config_finish();
#else
        ertc_alarm_enable(ERTC_ALA, FALSE);
        ertc_flag_clear(ERTC_ALAF_FLAG);
        ertc_alarm_mask_set(ERTC_ALA, ERTC_ALARM_MASK_DATE_WEEK);
        ertc_alarm_week_date_select(ERTC_ALA, ERTC_SLECT_DATE);
        ertc_alarm_set(ERTC_ALA, p_dev->wkalarm.tm_mday, p_dev->wkalarm.tm_hour, \
                       p_dev->wkalarm.tm_min, p_dev->wkalarm.tm_sec, ERTC_24H);

        ertc_interrupt_enable(ERTC_ALA_INT, TRUE);
        ertc_alarm_enable(ERTC_ALA, TRUE);
        ertc_flag_clear(ERTC_ALAF_FLAG);
#endif
    }

    return RT_EOK;
}

void Alarm_IRQHandler(void)
{
    rt_interrupt_enter();

#if defined (SOC_SERIES_AT32F403A) || defined (SOC_SERIES_AT32F407) || \
    defined (SOC_SERIES_AT32F413)  || defined (SOC_SERIES_AT32A403A)
    if(rtc_flag_get(RTC_TA_FLAG) != RESET)
    {
        /* clear exint line flag */
        exint_flag_clear(EXINT_LINE_17);

        /* wait for the register write to complete */
        rtc_wait_config_finish();

        /* clear alarm flag */
        rtc_flag_clear(RTC_TA_FLAG);

        /* wait for the register write to complete */
        rtc_wait_config_finish();

        rt_alarm_update(&rtc_device.rtc_dev.parent, 1);
    }
#else
    if(ertc_flag_get(ERTC_ALAF_FLAG) != RESET)
    {
        /* clear alarm flag */
        ertc_flag_clear(ERTC_ALAF_FLAG);

        /* clear exint flag */
        exint_flag_clear(EXINT_LINE_17);

        rt_alarm_update(&rtc_device.rtc_dev.parent, 1);
    }
#endif
    rt_interrupt_leave();
}
#endif

static rt_err_t _rtc_get_alarm(struct rt_rtc_wkalarm *alarm)
{
#ifdef RT_USING_ALARM
    *alarm = rtc_device.wkalarm;
    LOG_D("GET_ALARM %d:%d:%d",rtc_device.wkalarm.tm_hour,
        rtc_device.wkalarm.tm_min,rtc_device.wkalarm.tm_sec);
    return RT_EOK;
#else
    return -RT_ERROR;
#endif
}

static rt_err_t _rtc_set_alarm(struct rt_rtc_wkalarm *alarm)
{
#ifdef RT_USING_ALARM
    LOG_D("RT_DEVICE_CTRL_RTC_SET_ALARM");
    if (alarm != RT_NULL)
    {
        rtc_device.wkalarm.enable = alarm->enable;
        rtc_device.wkalarm.tm_year = alarm->tm_year;
        rtc_device.wkalarm.tm_mon = alarm->tm_mon;
        rtc_device.wkalarm.tm_mday = alarm->tm_mday;
        rtc_device.wkalarm.tm_hour = alarm->tm_hour;
        rtc_device.wkalarm.tm_min = alarm->tm_min;
        rtc_device.wkalarm.tm_sec = alarm->tm_sec;
        rtc_alarm_time_set(&rtc_device);
    }
    else
    {
        LOG_E("RT_DEVICE_CTRL_RTC_SET_ALARM error!!");
        return -RT_ERROR;
    }
    LOG_D("SET_ALARM %d:%d:%d",alarm->tm_hour,
        alarm->tm_min, alarm->tm_sec);
    return RT_EOK;
#else
    return -RT_ERROR;
#endif
}

static rt_err_t _rtc_get_timeval(struct timeval *tv)
{
    tv->tv_sec = get_rtc_timestamp();

    return RT_EOK;
}

static const struct rt_rtc_ops _rtc_ops =
{
    _rtc_init,
    _rtc_get_secs,
    _rtc_set_secs,
    _rtc_get_alarm,
    _rtc_set_alarm,
    _rtc_get_timeval,
    RT_NULL,
};

int rt_hw_rtc_init(void)
{
    rt_err_t result;
    rtc_device.rtc_dev.ops = &_rtc_ops;
    result = rt_hw_rtc_register(&rtc_device.rtc_dev, "rtc", RT_DEVICE_FLAG_RDWR, RT_NULL);
    if (result != RT_EOK)
    {
        LOG_E("rtc register err code: %d", result);
        return result;
    }
    LOG_D("rtc init success");
    return RT_EOK;
}

INIT_DEVICE_EXPORT(rt_hw_rtc_init);

#endif /* BSP_USING_RTC */
