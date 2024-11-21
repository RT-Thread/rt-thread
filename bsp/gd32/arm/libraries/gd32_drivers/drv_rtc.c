/*
 * Copyright (c) 2006-2022, RT-Thread Development Team
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

static time_t get_rtc_timestamp(void)
{
    time_t rtc_counter;

    rtc_counter = (time_t)rtc_counter_get();

    return rtc_counter;
}

static rt_err_t set_rtc_timestamp(time_t time_stamp)
{
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
    rcu_periph_clock_enable(RCU_BKPI);

    rtc_counter = get_rtc_timestamp();
    /* once the rtc clock source has been selected, if can't be changed
     * anymore unless the Backup domain is reset */
    rcu_bkp_reset_enable();
    rcu_bkp_reset_disable();
    rcu_periph_clock_enable(RCU_RTC);
#ifdef BSP_RTC_USING_LSE
    rcu_osci_on(RCU_LXTAL);
    if (SUCCESS == rcu_osci_stab_wait(RCU_LXTAL))
    {
        /* set lxtal as rtc clock source */
        rcu_rtc_clock_config(RCU_RTCSRC_LXTAL);
    }
#elifdef BSP_RTC_USING_LSI
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
