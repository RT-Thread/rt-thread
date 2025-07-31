/*
 * Copyright (c) 2006-2025, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author            Notes
 * 2022-01-25     iysheng           first version
 */

#include <board.h>
#include <sys/time.h>

#define DBG_TAG             "drv.rtc"
#define DBG_LVL             DBG_INFO

#include <rtdbg.h>

#ifdef RT_USING_RTC

typedef struct {
    struct rt_device rtc_dev;
} gd32_rtc_device;

static gd32_rtc_device g_gd32_rtc_dev;

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

static time_t get_rtc_timestamp(void)
{
    #if defined SOC_SERIES_GD32E23x
    struct tm tm_new;
    rtc_parameter_struct rtc_current_time;

    rtc_current_time_get(&rtc_current_time);

    tm_new.tm_year = bcd_to_bin(rtc_current_time.rtc_year) + 100; /* tm_year: years since 1900 */
    tm_new.tm_mon  = bcd_to_bin(rtc_current_time.rtc_month) - 1;  /* tm_mon: month (0 = January, 11 = December) */
    tm_new.tm_mday = bcd_to_bin(rtc_current_time.rtc_date);
    tm_new.tm_hour = bcd_to_bin(rtc_current_time.rtc_hour);
    tm_new.tm_min  = bcd_to_bin(rtc_current_time.rtc_minute);
    tm_new.tm_sec  = bcd_to_bin(rtc_current_time.rtc_second);

    return mktime(&tm_new);
    #else
    time_t rtc_counter;

    rtc_counter = (time_t)rtc_counter_get();

    return rtc_counter;
    #endif
}

static rt_err_t set_rtc_timestamp(time_t time_stamp)
{
    #if defined SOC_SERIES_GD32E23x
    struct tm *p_tm;
    rtc_parameter_struct rtc_init_struct;

    p_tm = gmtime(&time_stamp);

    /* GD32 RTC uses year starting from 2000; thus tm_year must be at least 100 (i.e., 2000 - 1900) */

    if (p_tm->tm_year < 100)
    {
        return -RT_ERROR;
    }

    rtc_init_struct.rtc_year = bin_to_bcd(p_tm->tm_year - 100);
    rtc_init_struct.rtc_month = bin_to_bcd(p_tm->tm_mon + 1);
    rtc_init_struct.rtc_date = bin_to_bcd(p_tm->tm_mday);

    rtc_init_struct.rtc_day_of_week = bin_to_bcd(p_tm->tm_wday == 0 ? 7 : p_tm->tm_wday);
    rtc_init_struct.rtc_hour = bin_to_bcd(p_tm->tm_hour);
    rtc_init_struct.rtc_minute = bin_to_bcd(p_tm->tm_min);
    rtc_init_struct.rtc_second = bin_to_bcd(p_tm->tm_sec);
    rtc_init_struct.rtc_display_format = RTC_24HOUR;

#if defined(BSP_RTC_USING_LSI)
    rtc_init_struct.rtc_factor_asyn = 39;
    rtc_init_struct.rtc_factor_syn = 999;
#elif defined(BSP_RTC_USING_LSE)
    rtc_init_struct.rtc_factor_asyn = 127;
    rtc_init_struct.rtc_factor_syn = 255;
#endif

    if (rtc_init(&rtc_init_struct) != SUCCESS)
    {
        LOG_E("Failed to set RTC time.");
        return -RT_ERROR;
    }

    return RT_EOK;
    #else
    uint32_t rtc_counter;

    rtc_counter = (uint32_t)time_stamp;

    /* wait until LWOFF bit in RTC_CTL to 1 */
    rtc_lwoff_wait();
    /* enter configure mode */
    rtc_configuration_mode_enter();
    /* write data to rtc register */
    rtc_counter_set(rtc_counter);
    /* exit configure mode */
    rtc_configuration_mode_exit();
    /* wait until LWOFF bit in RTC_CTL to 1 */
    rtc_lwoff_wait();

    return RT_EOK;
    #endif
}

static rt_err_t rt_gd32_rtc_control(rt_device_t dev, int cmd, void *args)
{
    rt_err_t result = RT_EOK;

    RT_ASSERT(dev != RT_NULL);
    switch (cmd)
    {
    case RT_DEVICE_CTRL_RTC_GET_TIME:
        *(rt_uint32_t *)args = get_rtc_timestamp();
        break;

    case RT_DEVICE_CTRL_RTC_SET_TIME:
        if (set_rtc_timestamp(*(rt_uint32_t *)args))
        {
            result = -RT_ERROR;
        }
        break;
    }

    return result;
}

#ifdef RT_USING_DEVICE_OPS
const static struct rt_device_ops g_gd32_rtc_ops =
{
    RT_NULL,
    RT_NULL,
    RT_NULL,
    RT_NULL,
    RT_NULL,
    rt_gd32_rtc_control
};
#endif

static int rt_hw_rtc_init(void)
{
    rt_err_t ret;
    time_t rtc_counter;

    rcu_periph_clock_enable(RCU_PMU);
    pmu_backup_write_enable();
#ifndef SOC_SERIES_GD32E23x
    rcu_periph_clock_enable(RCU_BKPI);
#endif

    rtc_counter = get_rtc_timestamp();
    /* once the rtc clock source has been selected, if can't be changed
     * anymore unless the Backup domain is reset */
    rcu_bkp_reset_enable();
    rcu_bkp_reset_disable();
    rcu_periph_clock_enable(RCU_RTC);
#if defined(BSP_RTC_USING_LSE)
    rcu_osci_on(RCU_LXTAL);
    if (SUCCESS == rcu_osci_stab_wait(RCU_LXTAL))
    {
        /* set lxtal as rtc clock source */
        rcu_rtc_clock_config(RCU_RTCSRC_LXTAL);
    }
#elif defined(BSP_RTC_USING_LSI)
    rcu_osci_on(RCU_IRC40K);
    if (SUCCESS == rcu_osci_stab_wait(RCU_IRC40K))
    {
        /* set IRC40K as rtc clock source */
        rcu_rtc_clock_config(RCU_RTCSRC_IRC40K);
    }
#endif
    set_rtc_timestamp(rtc_counter);

#ifdef RT_USING_DEVICE_OPS
    g_gd32_rtc_dev.rtc_dev.ops         = &g_gd32_rtc_ops;
#else
    g_gd32_rtc_dev.rtc_dev.init        = RT_NULL;
    g_gd32_rtc_dev.rtc_dev.open        = RT_NULL;
    g_gd32_rtc_dev.rtc_dev.close       = RT_NULL;
    g_gd32_rtc_dev.rtc_dev.read        = RT_NULL;
    g_gd32_rtc_dev.rtc_dev.write       = RT_NULL;
    g_gd32_rtc_dev.rtc_dev.control     = rt_gd32_rtc_control;
#endif
    g_gd32_rtc_dev.rtc_dev.type        = RT_Device_Class_RTC;
    g_gd32_rtc_dev.rtc_dev.rx_indicate = RT_NULL;
    g_gd32_rtc_dev.rtc_dev.tx_complete = RT_NULL;
    g_gd32_rtc_dev.rtc_dev.user_data   = RT_NULL;

    ret = rt_device_register(&g_gd32_rtc_dev.rtc_dev, "rtc", \
        RT_DEVICE_FLAG_RDWR);
    if (ret != RT_EOK)
    {
        LOG_E("failed register internal rtc device, err=%d", ret);
    }

    return ret;
}
INIT_DEVICE_EXPORT(rt_hw_rtc_init);
#endif

