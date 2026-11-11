/*
 * Copyright (c) 2006-2022, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2022-11-26     GuEe-GUI     first version
 */

#define DBG_TAG "rtc.rpi"
#define DBG_LVL DBG_INFO
#include <rtdbg.h>

#include "rtc_dm.h"
#include <firmware-raspberrypi.h>

enum
{
    RTC_TIME,
    RTC_ALARM,
    RTC_ALARM_PENDING,
    RTC_ALARM_ENABLE,
    RTC_BBAT_CHG_VOLTS,
    RTC_BBAT_CHG_VOLTS_MIN,
    RTC_BBAT_CHG_VOLTS_MAX,
    RTC_BBAT_VOLTS
};

struct rpi_rtc
{
    struct rt_device parent;

    struct rpi_firmware *rpi_fw;
    rt_uint32_t bbat_vchg_microvolts;

    struct rt_mutex lock;
    struct rt_timer alarm_mon;
    struct rt_rtc_wkalarm wkalarm;
};

#define raw_to_rpi_rtc(raw) rt_container_of(raw, struct rpi_rtc, parent)

static rt_err_t rpi_rtc_alarm_clear_pending(struct rpi_rtc *rrtc)
{
    rt_uint32_t data[2] = { RTC_ALARM_PENDING, 1 };

    return rpi_firmware_property(rrtc->rpi_fw, RPI_FIRMWARE_SET_RTC_REG,
            &data, sizeof(data));
}

static rt_err_t rpi_rtc_set_charge_voltage(struct rpi_rtc *rrtc)
{
    rt_err_t err;
    rt_uint32_t data[2] = { RTC_BBAT_CHG_VOLTS, rrtc->bbat_vchg_microvolts };

    err = rpi_firmware_property(rrtc->rpi_fw, RPI_FIRMWARE_SET_RTC_REG,
            &data, sizeof(data));

    if (err)
    {
        LOG_E("Failed to set trickle charge voltage to %uuV error = %s",
                rrtc->bbat_vchg_microvolts, rt_strerror(err));
    }
    else if (rrtc->bbat_vchg_microvolts)
    {
        LOG_I("Trickle charging enabled at %uuV", rrtc->bbat_vchg_microvolts);
    }

    return err;
}

static rt_err_t rpi_rtc_alarm_irq_is_enabled(struct rpi_rtc *rrtc,
        rt_bool_t *enabled)
{
    rt_err_t err;
    rt_uint32_t data[2] = { RTC_ALARM_ENABLE };

    err = rpi_firmware_property(rrtc->rpi_fw, RPI_FIRMWARE_GET_RTC_REG,
            &data, sizeof(data));

    *enabled = !!(data[1] & 0x1);

    return err;
}

static rt_err_t rpi_rtc_alarm_irq_enable(struct rpi_rtc *rrtc, rt_bool_t enabled)
{
    rt_uint32_t data[2] = { RTC_ALARM_ENABLE, enabled };

    return rpi_firmware_property(rrtc->rpi_fw, RPI_FIRMWARE_SET_RTC_REG,
            &data, sizeof(data));
}

static rt_err_t rpi_rtc_read_time(struct rpi_rtc *rrtc, time_t *sec)
{
    rt_err_t err;
    rt_uint32_t data[2] = { RTC_TIME };

    err = rpi_firmware_property(rrtc->rpi_fw, RPI_FIRMWARE_GET_RTC_REG,
            &data, sizeof(data));

    *sec = data[1];

    return err;
}

static rt_err_t rpi_rtc_set_time(struct rpi_rtc *rrtc, time_t *sec)
{
    rt_uint32_t data[2] = { RTC_TIME, (rt_uint32_t)*sec };

    return rpi_firmware_property(rrtc->rpi_fw, RPI_FIRMWARE_SET_RTC_REG,
            &data, sizeof(data));
}

static rt_err_t rpi_rtc_read_alarm(struct rpi_rtc *rrtc,
        struct rt_rtc_wkalarm *alarm)
{
    rt_err_t err;
    rt_uint32_t data[2] = { RTC_ALARM };

    if (!(err = rpi_rtc_alarm_irq_is_enabled(rrtc, &alarm->enable)))
    {
        err = rpi_firmware_property(rrtc->rpi_fw, RPI_FIRMWARE_GET_RTC_REG,
                &data, sizeof(data));
    }

    rtc_timestamp_to_wkalarm(data[1], alarm);

    return err;
}

static rt_err_t rpi_rtc_set_alarm(struct rpi_rtc *rrtc,
        struct rt_rtc_wkalarm *alarm)
{
    rt_err_t err;
    struct rt_rtc_wkalarm *wkalarm = &rrtc->wkalarm;
    rt_uint32_t data[2] = { RTC_ALARM, (rt_uint32_t)rtc_wkalarm_to_timestamp(alarm) };

    err = rpi_firmware_property(rrtc->rpi_fw, RPI_FIRMWARE_SET_RTC_REG,
            &data, sizeof(data));

    if (!err && !(err = rpi_rtc_alarm_irq_enable(rrtc, alarm->enable)))
    {
        rt_mutex_take(&rrtc->lock, RT_WAITING_FOREVER);

        wkalarm->enable = alarm->enable;
        wkalarm->tm_hour = alarm->tm_hour;
        wkalarm->tm_min = alarm->tm_min;
        wkalarm->tm_sec = alarm->tm_sec;

        if (wkalarm->enable)
        {
            /*
             * raspberrypi firmware rtc have an IRQ pin that is not connected
             * to a CPU interrupt but rather directly to a PMIC or power supply.
             * So we should poll once per second.
             */
            rt_tick_t tick = rt_tick_from_millisecond(1000);

            rt_timer_control(&rrtc->alarm_mon, RT_TIMER_CTRL_SET_TIME, &tick);

            rt_timer_start(&rrtc->alarm_mon);
        }

        rt_mutex_release(&rrtc->lock);
    }

    return err;
}

static rt_err_t rpi_rtc_control(rt_device_t dev, int cmd, void *args)
{
    rt_err_t err = RT_EOK;
    struct rpi_rtc *rrtc = raw_to_rpi_rtc(dev);

    if (!args)
    {
        return -RT_EINVAL;
    }

    switch (cmd)
    {
    case RT_DEVICE_CTRL_RTC_GET_TIME:
        err = rpi_rtc_read_time(rrtc, args);
        break;

    case RT_DEVICE_CTRL_RTC_SET_TIME:
        err = rpi_rtc_set_time(rrtc, args);
        break;

    case RT_DEVICE_CTRL_RTC_GET_TIMEVAL:
        err = rpi_rtc_read_time(rrtc, (time_t *)&((struct timeval *)args)->tv_sec);
        break;

    case RT_DEVICE_CTRL_RTC_SET_TIMEVAL:
        err = rpi_rtc_set_time(rrtc, (time_t *)&((struct timeval *)args)->tv_sec);
        break;

    case RT_DEVICE_CTRL_RTC_GET_ALARM:
        err = rpi_rtc_read_alarm(rrtc, args);
        break;

    case RT_DEVICE_CTRL_RTC_SET_ALARM:
        err = rpi_rtc_set_alarm(rrtc, args);
        break;

    default:
        err = -RT_EINVAL;
        break;
    }

    return err;
}

#ifdef RT_USING_DEVICE_OPS
const static struct rt_device_ops rpi_rtc_rtc_ops =
{
    .control = rpi_rtc_control,
};
#endif

static void rpi_rtc_alarm_mon(void *param)
{
    struct rpi_rtc *rrtc = param;
    struct rt_rtc_wkalarm alarm;
    time_t alarm_time, next_alarm_time;

    rt_mutex_take(&rrtc->lock, RT_WAITING_FOREVER);

    rpi_rtc_read_alarm(rrtc, &alarm);
    alarm_time = rtc_wkalarm_to_timestamp(&alarm);
    next_alarm_time = rtc_wkalarm_to_timestamp(&rrtc->wkalarm);

    if (alarm_time < next_alarm_time)
    {
        rrtc->wkalarm.enable = RT_FALSE;
        rt_alarm_update(&rrtc->parent, 1);
    }

    rt_mutex_release(&rrtc->lock);
}

static rt_err_t rpi_rtc_probe(struct rt_platform_device *pdev)
{
    rt_err_t err = RT_EOK;
    const char *dev_name;
    struct rpi_firmware *rpi_fw;
    struct rt_device *dev = &pdev->parent;
    struct rt_ofw_node *np = dev->ofw_node, *fw_np;
    struct rpi_rtc *rrtc = rt_calloc(1, sizeof(*rrtc));

    if (!rrtc)
    {
        return -RT_ENOMEM;
    }

    fw_np = rt_ofw_parse_phandle(np, "firmware", 0);

    if (!fw_np)
    {
        err = -RT_EINVAL;
        goto _fail;
    }

    rpi_fw = rpi_firmware_get(fw_np);
    rt_ofw_node_put(fw_np);

    if (!rpi_fw)
    {
        err = -RT_EINVAL;
        goto _fail;
    }

    rrtc->rpi_fw = rpi_fw;

    rpi_rtc_alarm_clear_pending(rrtc);

    rt_ofw_prop_read_u32(np, "trickle-charge-microvolt", &rrtc->bbat_vchg_microvolts);
    rpi_rtc_set_charge_voltage(rrtc);

    dev->user_data = rrtc;

    rrtc->parent.type = RT_Device_Class_RTC;
#ifdef RT_USING_DEVICE_OPS
    rrtc->parent.ops = &rpi_rtc_rtc_ops;
#else
    rrtc->parent.control = rpi_rtc_control;
#endif

    rtc_dev_set_name(&rrtc->parent);
    dev_name = rt_dm_dev_get_name(&rrtc->parent);

    rt_mutex_init(&rrtc->lock, dev_name, RT_IPC_FLAG_FIFO);
    rt_timer_init(&rrtc->alarm_mon, dev_name, rpi_rtc_alarm_mon, rrtc,
            0, RT_TIMER_FLAG_PERIODIC);

    rt_device_register(&rrtc->parent, dev_name, RT_DEVICE_FLAG_RDWR);

    return RT_EOK;

_fail:
    rt_free(rrtc);

    return err;
}

static rt_err_t rpi_rtc_remove(struct rt_platform_device *pdev)
{
    struct rpi_rtc *rrtc = pdev->parent.user_data;

    rt_timer_detach(&rrtc->alarm_mon);
    rt_mutex_detach(&rrtc->lock);
    rt_device_unregister(&rrtc->parent);

    rt_free(rrtc);

    return RT_EOK;
}

static const struct rt_ofw_node_id rpi_rtc_ofw_ids[] =
{
    { .compatible = "raspberrypi,rpi-rtc" },
    { /* sentinel */ }
};

static struct rt_platform_driver rpi_rtc_driver =
{
    .name = "rtc-rpi",
    .ids = rpi_rtc_ofw_ids,

    .probe = rpi_rtc_probe,
    .remove = rpi_rtc_remove,
};
RT_PLATFORM_DRIVER_EXPORT(rpi_rtc_driver);
