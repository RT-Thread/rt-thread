/*
 * Copyright (c) 2006-2020, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2020-06-08     hqfang       first implementation.
 */

#include "drv_rtc.h"

#ifdef BSP_USING_RTC

static time_t get_timestamp(void)
{
    return (time_t)rtc_counter_get();
}

static int set_timestamp(time_t timestamp)
{
    /* wait until last write operation on RTC registers has finished */
    rtc_lwoff_wait();
    /* change the current time */
    rtc_counter_set((uint32_t)timestamp);
    /* wait until last write operation on RTC registers has finished */
    rtc_lwoff_wait();
    return RT_EOK;
}

static void rtc_configuration(void)
{
    /* enable PMU and BKPI clocks */
    rcu_periph_clock_enable(RCU_BKPI);
    rcu_periph_clock_enable(RCU_PMU);
    /* allow access to BKP domain */
    pmu_backup_write_enable();

    /* reset backup domain */
    bkp_deinit();

    /* enable LXTAL */
    rcu_osci_on(RCU_LXTAL);
    /* wait till LXTAL is ready */
    rcu_osci_stab_wait(RCU_LXTAL);

    /* select RCU_LXTAL as RTC clock source */
    rcu_rtc_clock_config(RCU_RTCSRC_LXTAL);

    /* enable RTC Clock */
    rcu_periph_clock_enable(RCU_RTC);

    /* wait for RTC registers synchronization */
    rtc_register_sync_wait();

    /* wait until last write operation on RTC registers has finished */
    rtc_lwoff_wait();

    /* wait until last write operation on RTC registers has finished */
    rtc_lwoff_wait();

    /* set RTC prescaler: set RTC period to 1s */
    rtc_prescaler_set(32767);

    /* wait until last write operation on RTC registers has finished */
    rtc_lwoff_wait();
}

static rt_err_t gd32_rtc_init(rt_device_t dev)
{
    if (bkp_data_read(BKP_DATA_0) != 0xA5A5)
    {
        rtc_configuration();
        bkp_data_write(BKP_DATA_0, 0xA5A5);
    }
    else
    {
        /* allow access to BKP domain */
        rcu_periph_clock_enable(RCU_PMU);
        pmu_backup_write_enable();

        /* wait for RTC registers synchronization */
        rtc_register_sync_wait();
        /* wait until last write operation on RTC registers has finished */
        rtc_lwoff_wait();
    }

    return RT_EOK;
}

static rt_err_t gd32_rtc_open(rt_device_t dev, rt_uint16_t oflag)
{
    return RT_EOK;
}

static rt_err_t gd32_rtc_close(rt_device_t dev)
{
    return RT_EOK;
}

static rt_ssize_t gd32_rtc_read(rt_device_t dev, rt_off_t pos, void *buffer, rt_size_t size)
{
    return RT_EOK;
}

static rt_ssize_t gd32_rtc_write(rt_device_t dev, rt_off_t pos, const void *buffer, rt_size_t size)
{
    return RT_EOK;
}

static rt_err_t gd32_rtc_control(rt_device_t dev, int cmd, void *args)
{
    RT_ASSERT(dev != RT_NULL);

    switch (cmd)
    {
    case RT_DEVICE_CTRL_RTC_GET_TIME:
    {
        *(uint32_t *)args = get_timestamp();
    }
    break;

    case RT_DEVICE_CTRL_RTC_SET_TIME:
    {
        set_timestamp(*(time_t *)args);
    }
    break;

    default:
        return -RT_EINVAL;
    }

    return RT_EOK;
}

static struct rt_device rtc_device =
{
    .type    = RT_Device_Class_RTC,
    .init    = gd32_rtc_init,
    .open    = gd32_rtc_open,
    .close   = gd32_rtc_close,
    .read    = gd32_rtc_read,
    .write   = gd32_rtc_write,
    .control = gd32_rtc_control,
};

int rt_hw_rtc_init(void)
{
    rt_err_t ret = RT_EOK;

    ret = rt_device_register(&rtc_device, "rtc", RT_DEVICE_FLAG_RDWR);

    rt_device_open(&rtc_device, RT_DEVICE_OFLAG_RDWR);

    return RT_EOK;
}

INIT_DEVICE_EXPORT(rt_hw_rtc_init);

#endif /* BSP_USING_RTC */
