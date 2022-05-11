/*
 * Copyright (c) 2006-2021, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date         Author         Notes
 * 2022-03-10   shelton        first version
 */

#include <rtthread.h>
#include <rtdevice.h>
#include <sys/time.h>
#include "board.h"

#ifdef BSP_USING_RTC

#ifndef BKP_DR1
#define BKP_DR1 RT_NULL
#endif

//#define DRV_DEBUG
#define LOG_TAG             "drv.rtc"
#include <drv_log.h>

#define BKUP_REG_DATA 0xA5A5

static time_t get_rtc_timestamp(void)
{
    return rtc_counter_get();
}

static rt_err_t set_rtc_time_stamp(time_t time_stamp)
{
    /* set the rtc counter value */
    rtc_counter_set(time_stamp);
    /* wait until last write operation on rtc registers has finished */
    rtc_wait_config_finish();
    LOG_D("set rtc time.");

    bpr_data_write(BPR_DATA1, BKUP_REG_DATA);
    return RT_EOK;
}

static rt_err_t rt_rtc_config(void)
{
    /* allow access to pattery powered domain */
    pwc_battery_powered_domain_access(TRUE);

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
    return RT_EOK;
}

static rt_err_t _rtc_init(void)
{
    crm_periph_clock_enable(CRM_PWC_PERIPH_CLOCK, TRUE);
    crm_periph_clock_enable(CRM_BPR_PERIPH_CLOCK, TRUE);

#ifdef BSP_RTC_USING_LICK
    crm_clock_source_enable(CRM_CLOCK_SOURCE_LICK, TRUE);
    while(crm_flag_get(CRM_LICK_STABLE_FLAG) == RESET);
#else
    crm_periph_clock_enable(CRM_PWC_PERIPH_CLOCK, TRUE);
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
