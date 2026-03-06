/*
 * Copyright (c) 2006-2022, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2024-07-07     GuEe-GUI     first version
 */

#include "rtc_dm.h"

#define DBG_TAG "rtc.zynqmp"
#define DBG_LVL DBG_INFO
#include <rtdbg.h>

#define RTC_SET_TM_WR       0x00
#define RTC_SET_TM_RD       0x04
#define RTC_CALIB_WR        0x08
#define RTC_CALIB_RD        0x0c
#define RTC_CUR_TM          0x10
#define RTC_CUR_TICK        0x14
#define RTC_ALRM            0x18
#define RTC_INT_STS         0x20
#define RTC_INT_MASK        0x24
#define RTC_INT_EN          0x28
#define RTC_INT_DIS         0x2c
#define RTC_CTRL            0x40

#define RTC_FR_EN           RT_BIT(20)
#define RTC_FR_DATSHIFT     16
#define RTC_TICK_MASK       0xffff
#define RTC_INT_SEC         RT_BIT(0)
#define RTC_INT_ALRM        RT_BIT(1)
#define RTC_OSC_EN          RT_BIT(24)
#define RTC_BATT_EN         RT_BIT(31)

#define RTC_ALRM_MASK       RT_BIT(1)
#define RTC_MSEC            1000

struct zynqmp_rtc
{
    struct rt_device parent;

    int alarm_irq;
    int sec_irq;
    void *base;

    struct rt_clk *rtc_clk;
    rt_uint32_t freq;
};

#define raw_to_zynqmp_rtc(raw) rt_container_of(raw, struct zynqmp_rtc, parent)

static void zynqmp_get_secs(struct zynqmp_rtc *zrtc, time_t *sec)
{
    if (HWREG32(zrtc->base + RTC_INT_STS) & RTC_INT_SEC)
    {
        /*
         * RTC has updated the CURRENT_TIME with the time written into
         * SET_TIME_WRITE register.
         */
        *(rt_ubase_t *)sec = HWREG32(zrtc->base + RTC_CUR_TM);
    }
    else
    {
        /*
         * Time written in SET_TIME_WRITE has not yet updated into
         * the seconds read register, so read the time from the
         * SET_TIME_WRITE instead of CURRENT_TIME register.
         * Since we add +1 sec while writing, we need to -1 sec while
         * reading.
         */
        *(rt_ubase_t *)sec = HWREG32(zrtc->base + RTC_SET_TM_RD) - 1;
    }
}

static void zynqmp_set_secs(struct zynqmp_rtc *zrtc, time_t *sec)
{
    /*
     * The value written will be updated after 1 sec into the
     * seconds read register, so we need to program time +1 sec
     * to get the correct time on read.
     */
    HWREG32(zrtc->base + RTC_SET_TM_WR) = *sec + 1;

    /*
     * Clear the rtc interrupt status register after setting the
     * time. During a read_time function, the code should read the
     * RTC_INT_STATUS register and if bit 0 is still 0, it means
     * that one second has not elapsed yet since RTC was set and
     * the current time should be read from SET_TIME_READ register;
     * otherwise, CURRENT_TIME register is read to report the time
     */
    HWREG32(zrtc->base + RTC_INT_STS) = RTC_INT_SEC;
}

static void zynqmp_get_alarm(struct zynqmp_rtc *zrtc, struct rt_rtc_wkalarm *alarm)
{
    rtc_timestamp_to_wkalarm(HWREG32(zrtc->base + RTC_ALRM), alarm);
    alarm->enable = !!(HWREG32(zrtc->base + RTC_INT_MASK) & RTC_INT_ALRM);
}

static void zynqmp_set_alarm(struct zynqmp_rtc *zrtc, struct rt_rtc_wkalarm *alarm)
{
    rt_tick_t timeout;

    HWREG32(zrtc->base + RTC_ALRM) = (rt_uint32_t)rtc_wkalarm_to_timestamp(alarm);

    if (alarm->enable)
    {
        timeout = rt_tick_from_millisecond(RTC_MSEC);
        timeout += rt_tick_get();

        while (RT_TRUE)
        {
            if (!((HWREG32(zrtc->base + RTC_INT_STS) & RTC_ALRM_MASK) == RTC_ALRM_MASK))
            {
                break;
            }

            if (rt_tick_get() > timeout)
            {
                LOG_E("%s: Clearing alarm status bit time out",
                        rt_dm_dev_get_name(&zrtc->parent));
                return;
            }

            HWREG32(zrtc->base + RTC_INT_STS) = RTC_INT_ALRM;
        }

        HWREG32(zrtc->base + RTC_INT_EN) = RTC_INT_ALRM;
    }
    else
    {
        HWREG32(zrtc->base + RTC_INT_DIS) = RTC_INT_ALRM;
    }
}

static rt_err_t zynqmp_control(rt_device_t dev, int cmd, void *args)
{
    rt_err_t err = RT_EOK;
    struct zynqmp_rtc *zrtc = raw_to_zynqmp_rtc(dev);

    if (!args)
    {
        return -RT_EINVAL;
    }

    switch (cmd)
    {
    case RT_DEVICE_CTRL_RTC_GET_TIME:
        zynqmp_get_secs(zrtc, args);
        break;

    case RT_DEVICE_CTRL_RTC_SET_TIME:
        zynqmp_set_secs(zrtc, args);
        break;

    case RT_DEVICE_CTRL_RTC_GET_TIMEVAL:
        zynqmp_get_secs(zrtc, (time_t *)&((struct timeval *)args)->tv_sec);
        break;

    case RT_DEVICE_CTRL_RTC_SET_TIMEVAL:
        zynqmp_set_secs(zrtc, (time_t *)&((struct timeval *)args)->tv_sec);
        break;

    case RT_DEVICE_CTRL_RTC_GET_ALARM:
        zynqmp_get_alarm(zrtc, args);
        break;

    case RT_DEVICE_CTRL_RTC_SET_ALARM:
        zynqmp_set_alarm(zrtc, args);
        break;

    default:
        err = -RT_EINVAL;
        break;
    }

    return err;
}

#ifdef RT_USING_DEVICE_OPS
const static struct rt_device_ops zynqmp_rtc_ops =
{
    .control = zynqmp_control,
};
#endif

static void zynqmp_rtc_isr(int irqno, void *param)
{
    rt_uint32_t status;
    struct zynqmp_rtc *zrtc = param;

    status = HWREG32(zrtc->base + RTC_INT_STS);

    /* Check if interrupt asserted */
    if (!(status & (RTC_INT_SEC | RTC_INT_ALRM)))
    {
        return;
    }

    /* Disable RTC_INT_ALRM interrupt only */
    HWREG32(zrtc->base + RTC_INT_DIS) = RTC_INT_ALRM;

    if (status & RTC_INT_ALRM)
    {
        rt_alarm_update(&zrtc->parent, 1);
    }
}

static rt_err_t zynqmp_probe(struct rt_platform_device *pdev)
{
    rt_err_t err = RT_EOK;
    rt_uint32_t value;
    const char *dev_name;
    struct rt_device *dev = &pdev->parent;
    struct zynqmp_rtc *zrtc = rt_calloc(1, sizeof(*zrtc));

    if (!zrtc)
    {
        return -RT_ENOMEM;
    }

    zrtc->base = rt_dm_dev_iomap(dev, 0);

    if (!zrtc->base)
    {
        err = -RT_EIO;
        goto _fail;
    }

    zrtc->alarm_irq = rt_dm_dev_get_irq_by_name(dev, "alarm");

    if (zrtc->alarm_irq < 0)
    {
        err = zrtc->alarm_irq;
        goto _fail;
    }

    zrtc->sec_irq = rt_dm_dev_get_irq_by_name(dev, "sec");

    if (zrtc->sec_irq < 0)
    {
        err = zrtc->sec_irq;
        goto _fail;
    }

    zrtc->rtc_clk = rt_clk_get_by_name(dev, "rtc_clk");

    if (rt_is_err(zrtc->rtc_clk))
    {
        err = rt_ptr_err(zrtc->rtc_clk);
        goto _fail;
    }

    if (!(zrtc->freq = rt_clk_get_rate(zrtc->rtc_clk)))
    {
        if ((err = rt_dm_dev_prop_read_u32(dev, "calibration", &zrtc->freq)))
        {
            goto _fail;
        }
    }

    dev->user_data = zrtc;

    zrtc->parent.type = RT_Device_Class_RTC;
#ifdef RT_USING_DEVICE_OPS
    zrtc->parent.ops = &zynqmp_rtc_ops;
#else
    zrtc->parent.control = zynqmp_rtc_control;
#endif

    rtc_dev_set_name(&zrtc->parent);
    dev_name = rt_dm_dev_get_name(&zrtc->parent);
    rt_device_register(&zrtc->parent, dev_name, RT_DEVICE_FLAG_RDWR);

    rt_hw_interrupt_install(zrtc->alarm_irq, zynqmp_rtc_isr, zrtc, "rtc-zynqmp-alarm");
    rt_hw_interrupt_umask(zrtc->alarm_irq);

    rt_hw_interrupt_install(zrtc->sec_irq, zynqmp_rtc_isr, zrtc, "rtc-zynqmp-sec");
    rt_hw_interrupt_umask(zrtc->sec_irq);

    if (!HWREG32(zrtc->base + RTC_CALIB_RD))
    {
        HWREG32(zrtc->base + RTC_CALIB_WR) = zrtc->freq;
    }

    /* Enable RTC switch to battery when VCC_PSAUX is not available */
    value = HWREG32(zrtc->base + RTC_CTRL);
    value |= RTC_BATT_EN;
    HWREG32(zrtc->base + RTC_CTRL) = value;

    return RT_EOK;

_fail:
    if (zrtc->base)
    {
        rt_iounmap(zrtc->base);
    }

    if (!rt_is_err_or_null(zrtc->rtc_clk))
    {
        rt_clk_put(zrtc->rtc_clk);
    }

    rt_free(zrtc);

    return err;
}

static rt_err_t zynqmp_remove(struct rt_platform_device *pdev)
{
    struct zynqmp_rtc *zrtc = pdev->parent.user_data;

    rt_hw_interrupt_mask(zrtc->alarm_irq);
    rt_pic_detach_irq(zrtc->alarm_irq, zrtc);

    rt_hw_interrupt_mask(zrtc->sec_irq);
    rt_pic_detach_irq(zrtc->sec_irq, zrtc);

    rt_device_unregister(&zrtc->parent);

    rt_clk_put(zrtc->rtc_clk);

    rt_free(zrtc);

    return RT_EOK;
}

static const struct rt_ofw_node_id zynqmp_ofw_ids[] =
{
    { .compatible = "xlnx,zynqmp-rtc" },
    { /* sentinel */ }
};

static struct rt_platform_driver zynqmp_driver =
{
    .name = "rtc-zynqmp",
    .ids = zynqmp_ofw_ids,

    .probe = zynqmp_probe,
    .remove = zynqmp_remove,
};
RT_PLATFORM_DRIVER_EXPORT(zynqmp_driver);
