/*
 * Copyright (c) 2019 Winner Microelectronics Co., Ltd.
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2018-09-15     flyingcys    1st version
 * 2019-03-01     fanwenl      add alarm
 */

#include <rtdevice.h>
#include <rtthread.h>
#include <sys/time.h>
#include "wm_regs.h"
#include "wm_irq.h"
#include "tls_common.h"
#include "wm_rtc.h"
#include "drv_rtc.h"

#ifdef BSP_USING_RTC

#if defined(RT_USING_SOFT_RTC)
#error "Please CANCEL the RT_USING_SOFT_RTC option. Make sure there is only one RTC device on the system."
#endif

static struct rt_rtc_device rtc_device;

static time_t wm_get_timestamp(void)
{
    struct tm tm_new = {0};

    int ctrl1 = 0;
    int ctrl2 = 0;

    ctrl1 = tls_reg_read32(HR_PMU_RTC_CTRL1);
    ctrl2 = tls_reg_read32(HR_PMU_RTC_CTRL2);
    tm_new.tm_year = ((int)((int)ctrl2 & 0x00007f00) >> 8);
    tm_new.tm_mon  = (ctrl2 & 0x0000000f);
    tm_new.tm_mday = (ctrl1 & 0x1f000000) >> 24;
    tm_new.tm_hour = (ctrl1 & 0x001f0000) >> 16;
    tm_new.tm_min  = (ctrl1 & 0x00003f00) >>  8;
    tm_new.tm_sec  =  ctrl1 & 0x0000003f;

    return timegm(&tm_new);
}

static int wm_set_timestamp(time_t timestamp)
{
    int ctrl1 = 0;
    int ctrl2 = 0;

    struct tm tblock;

    gmtime_r(&timestamp, &tblock);

    ctrl2  = tls_reg_read32(HR_PMU_RTC_CTRL2);  /* disable */
    ctrl2 &= ~(1 << 16);
    tls_reg_write32(HR_PMU_RTC_CTRL2, ctrl2);

    ctrl1 |= tblock.tm_sec;
    ctrl1 |= tblock.tm_min  << 8;
    ctrl1 |= tblock.tm_hour << 16;
    ctrl1 |= tblock.tm_mday << 24;
    tls_reg_write32(HR_PMU_RTC_CTRL1, ctrl1);

    ctrl2  = 0;
    ctrl2 |= tblock.tm_mon;
    ctrl2 |= tblock.tm_year << 8;
    tls_reg_write32(HR_PMU_RTC_CTRL2, ctrl2);

    ctrl2  = tls_reg_read32(HR_PMU_RTC_CTRL2);/* enable */
    ctrl2 |= (1 << 16);
    tls_reg_write32(HR_PMU_RTC_CTRL2, ctrl2);

    return RT_EOK;
}
#ifdef BSP_USING_ALARM
static int wm_alarm_set_timestamp(struct rt_rtc_wkalarm *wkalarm)
{
    int ctrl1 = 0;
    int ctrl2 = 0;
    struct tm tblock;
    time_t timestamp = 0;

    timestamp = wm_get_timestamp();
    gmtime_r(&timestamp, &tblock);

    tls_irq_enable(PMU_RTC_INT);

    ctrl1 |= wkalarm->tm_sec;
    ctrl1 |= wkalarm->tm_min  << 8;
    ctrl1 |= wkalarm->tm_hour << 16;
    ctrl1 |= tblock.tm_mday << 24;

    ctrl2 |= tblock.tm_mon;
    ctrl2 |= tblock.tm_year << 8;

    tls_reg_write32(HR_PMU_RTC_CTRL2, ctrl2 | BIT(16));

    tls_reg_write32(HR_PMU_RTC_CTRL1, ctrl1 | BIT(31));/* must set the enable */

    return RT_EOK;
}

static void wm_rtc_alarm_callback(void *arg)
{
    rt_alarm_update(0, 0);
}
#endif
static rt_err_t wm_rtc_init(rt_device_t dev)
{
    wm_set_timestamp((time_t)0);

#ifdef BSP_USING_ALARM
    tls_rtc_isr_register(wm_rtc_alarm_callback, (void *)0);
#endif
    return RT_EOK;
}

static rt_err_t wm_rtc_open(rt_device_t dev, rt_uint16_t oflag)
{
    return RT_EOK;
}

static rt_err_t wm_rtc_close(rt_device_t dev)
{
    return RT_EOK;
}

static rt_err_t wm_rtc_control(rt_device_t dev, int cmd, void *args)
{
#ifdef BSP_USING_ALARM
    struct rt_rtc_device* rtc_device;
    rtc_device = (struct rt_rtc_device* )dev;
#endif
    RT_ASSERT(dev != RT_NULL);

    switch (cmd)
    {
    case RT_DEVICE_CTRL_RTC_GET_TIME:
        *(rt_uint32_t *)args = wm_get_timestamp();
        break;
    case RT_DEVICE_CTRL_RTC_SET_TIME:
        wm_set_timestamp(*(time_t *)args);
        break;
#ifdef BSP_USING_ALARM
    case RT_DEVICE_CTRL_RTC_GET_ALARM:
        *(struct rt_rtc_wkalarm *)args = rtc_device->wkalarm;
        return RT_EOK;
    case RT_DEVICE_CTRL_RTC_SET_ALARM:
        rtc_device->wkalarm = *(struct rt_rtc_wkalarm *)args;
        wm_alarm_set_timestamp(&rtc_device->wkalarm);
        break;
#endif
    default:
        return -RT_EINVAL;
    }
    return RT_EOK;
}

static rt_ssize_t wm_rtc_read(rt_device_t dev, rt_off_t pos, void *buffer, rt_size_t size)
{
    wm_rtc_control(dev, RT_DEVICE_CTRL_RTC_GET_TIME, buffer);
    return size;
}

static rt_ssize_t wm_rtc_write(rt_device_t dev, rt_off_t pos, const void *buffer, rt_size_t size)
{
    wm_rtc_control(dev, RT_DEVICE_CTRL_RTC_SET_TIME, (void *)buffer);
    return size;
}

#ifdef RT_USING_DEVICE_OPS
const static struct rt_device_ops _ops =
{
    .init = wm_rtc_init,
    .open = wm_rtc_open,
    .close = wm_rtc_close,
    .read = wm_rtc_read,
    .write = wm_rtc_write,
    .control = wm_rtc_control
};
#endif

int wm_hw_rtc_init(void)
{
    rt_memset(&rtc_device, 0, sizeof(rtc_device));

    rtc_device.device.type        = RT_Device_Class_RTC;
    rtc_device.device.rx_indicate = RT_NULL;
    rtc_device.device.tx_complete = RT_NULL;

#ifdef RT_USING_DEVICE_OPS
    rtc_device.ops         = &_ops;
#else
    rtc_device.device.init        = wm_rtc_init;
    rtc_device.device.open        = wm_rtc_open;
    rtc_device.device.close       = wm_rtc_close;
    rtc_device.device.read        = wm_rtc_read;
    rtc_device.device.write       = wm_rtc_write;
    rtc_device.device.control     = wm_rtc_control;
#endif
    rtc_device.device.user_data   = RT_NULL;

    /* register a rtc device */
    rt_device_register(&rtc_device.device, "rtc", RT_DEVICE_FLAG_RDWR);

    return 0;
}
INIT_DEVICE_EXPORT(wm_hw_rtc_init);
#endif /* BSP_USING_RTC */
