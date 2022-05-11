/*
 * Copyright (c) 2006-2021, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date         Author         Notes
 * 2022-03-28   shelton        first version
 */

#include <rtthread.h>
#include <rtdevice.h>
#include <sys/time.h>
#include "board.h"

#ifdef BSP_USING_RTC

//#define DRV_DEBUG
#define LOG_TAG                         "drv.rtc"
#include <drv_log.h>

#define BKUP_REG_DATA                   0xA5A5

static time_t get_rtc_timestamp(void)
{
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
}

static rt_err_t set_rtc_time_stamp(time_t time_stamp)
{
    struct tm *p_tm;

    p_tm = gmtime(&time_stamp);
    if (p_tm->tm_year < 100)
    {
        return -RT_ERROR;
    }

    /* set time */
    if(ertc_time_set(p_tm->tm_hour, p_tm->tm_min, p_tm->tm_sec, ERTC_AM) != SUCCESS)
    {
        return -RT_ERROR;
    }

    /* set date */
    if(ertc_date_set(p_tm->tm_year - 100, p_tm->tm_mon + 1, p_tm->tm_mday, p_tm->tm_wday + 1) != SUCCESS)
    {
        return -RT_ERROR;
    }

    LOG_D("set rtc time.");

    /* indicator for the ertc configuration */
    ertc_bpr_data_write(ERTC_DT1, BKUP_REG_DATA);

    return RT_EOK;
}

static rt_err_t rt_rtc_config(void)
{
    /* allow access to battery powered domain */
    pwc_battery_powered_domain_access(TRUE);

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
    return RT_EOK;
}

static rt_err_t _rtc_init(void)
{
    crm_periph_clock_enable(CRM_PWC_PERIPH_CLOCK, TRUE);

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

static rt_err_t _rtc_get_secs(void *args)
{
    *(rt_uint32_t *)args = get_rtc_timestamp();
    LOG_D("RTC: get rtc_time %x\n", *(rt_uint32_t *)args);

    return RT_EOK;
}

static rt_err_t _rtc_set_secs(void *args)
{
    rt_err_t result = RT_EOK;

    if (set_rtc_time_stamp(*(rt_uint32_t *)args))
    {
        result = -RT_ERROR;
    }
    LOG_D("RTC: set rtc_time %x\n", *(rt_uint32_t *)args);

    return result;
}

static const struct rt_rtc_ops _rtc_ops =
{
    _rtc_init,
    _rtc_get_secs,
    _rtc_set_secs,
    RT_NULL,
    RT_NULL,
    RT_NULL,
    RT_NULL,
};

static rt_rtc_dev_t at32_rtc_dev;

int rt_hw_rtc_init(void)
{
    rt_err_t result;
    at32_rtc_dev.ops = &_rtc_ops;
    result = rt_hw_rtc_register(&at32_rtc_dev, "rtc", RT_DEVICE_FLAG_RDWR,RT_NULL);
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
