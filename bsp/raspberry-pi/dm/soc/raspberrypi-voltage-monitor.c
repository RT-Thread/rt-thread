/*
 * Copyright (c) 2006-2022, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2022-08-24     GuEe-GUI     first version
 */

#include <rthw.h>
#include <rtthread.h>
#include <rtdevice.h>

#define DBG_TAG "soc.raspberrypi-voltage-monitor"
#define DBG_LVL DBG_INFO
#include <rtdbg.h>

#include <firmware-raspberrypi.h>

#define UNDERVOLTAGE_STICKY_BIT RT_BIT(16)

struct rpi_voltage_monitor
{
    struct rt_device_notify alarm;

    rt_uint32_t last_throttled;
    struct rpi_firmware *rpi_fw;
    struct rt_work delayed_work;
};

static rt_err_t rpi_voltage_monitor_open(rt_device_t dev, rt_uint16_t oflag)
{
    if (dev->ref_count)
    {
        return -RT_EBUSY;
    }

    return RT_EOK;
}

static rt_err_t rpi_voltage_monitor_close(rt_device_t dev)
{
    struct rpi_voltage_monitor *mon = dev->user_data;

    mon->alarm.notify = RT_NULL;

    return RT_EOK;
}

static rt_ssize_t rpi_voltage_monitor_read(rt_device_t dev, rt_off_t pos,
        void *buffer, rt_size_t size)
{
    struct rpi_voltage_monitor *mon = dev->user_data;

    if (size <= sizeof(mon->last_throttled))
    {
        return -RT_ENOSPC;
    }

    *(rt_uint32_t *)buffer = !!(mon->last_throttled & UNDERVOLTAGE_STICKY_BIT);

    return sizeof(mon->last_throttled);
}

static rt_err_t rpi_voltage_monitor_control(rt_device_t dev, int cmd, void *args)
{
    rt_err_t err = RT_EOK;
    struct rpi_voltage_monitor *mon = dev->user_data;

    switch (cmd)
    {
    case RT_DEVICE_CTRL_NOTIFY_SET:
        if (!args)
        {
            err = -RT_EINVAL;
            break;
        }
        rt_memcpy(&mon->alarm, args, sizeof(mon->alarm));
        break;

    default:
        err = -RT_EINVAL;
        break;
    }

    return err;
}

#ifdef RT_USING_DEVICE_OPS
const static struct rt_device_ops rpi_voltage_monitor_ops =
{
    .open = rpi_voltage_monitor_open,
    .close = rpi_voltage_monitor_close,
    .read = rpi_voltage_monitor_read,
    .control = rpi_voltage_monitor_control,
};
#endif

static void rpi_voltage_monitor_delayed_work(struct rt_work *work, void *work_data)
{
    rt_err_t err;
    rt_uint32_t new_uv, old_uv, value;
    struct rpi_voltage_monitor *mon = work_data;

    /* Request firmware to clear sticky bits */
    value = 0xffff;

    if ((err = rpi_firmware_property(mon->rpi_fw, RPI_FIRMWARE_GET_THROTTLED,
            &value, sizeof(value))))
    {
        LOG_E("Failed to get throttled error = %s", rt_strerror(err));
        return;
    }

    new_uv = value & UNDERVOLTAGE_STICKY_BIT;
    old_uv = mon->last_throttled & UNDERVOLTAGE_STICKY_BIT;
    mon->last_throttled = value;

    if (new_uv == old_uv)
    {
        return;
    }

    LOG_D(new_uv ? "Undervoltage detected" : "Voltage normalised");

    if (mon->alarm.notify)
    {
        mon->alarm.notify(mon->alarm.dev);
    }

    rt_work_submit(&mon->delayed_work, rt_tick_from_millisecond(200));
}

static rt_err_t rpi_voltage_monitor_probe(struct rt_platform_device *pdev)
{
    rt_err_t err;
    const char *dev_name;
    struct rt_device *dev = &pdev->parent, *fw_dev = pdev->priv;
    struct rpi_voltage_monitor *mon = rt_calloc(1, sizeof(*mon));

    if (!mon)
    {
        return -RT_ENOMEM;
    }

    mon->rpi_fw = rpi_firmware_get(fw_dev->ofw_node);

    if (!mon->rpi_fw)
    {
        err = -RT_EINVAL;
        goto _fail;
    }

    dev->user_data = mon;

    dev->type = RT_Device_Class_Char;
#ifdef RT_USING_DEVICE_OPS
    dev->ops = &rpi_voltage_monitor_ops;
#else
    dev->open = rpi_voltage_monitor_open,
    dev->close = rpi_voltage_monitor_close,
    dev->read = rpi_voltage_monitor_read,
    dev->control = rpi_voltage_monitor_control,
#endif

    rt_dm_dev_set_name(dev, "rpi_volt");
    dev_name = rt_dm_dev_get_name(dev);
    rt_device_register(dev, dev_name, RT_DEVICE_FLAG_RDONLY);

    rt_work_init(&mon->delayed_work, rpi_voltage_monitor_delayed_work, mon);
    rt_work_submit(&mon->delayed_work, rt_tick_from_millisecond(200));

    return RT_EOK;

_fail:
    rt_free(mon);

    return err;
}

static rt_err_t rpi_voltage_monitor_remove(struct rt_platform_device *pdev)
{
    struct rt_device *dev = &pdev->parent;
    struct rpi_voltage_monitor *mon = dev->user_data;

    rt_work_cancel(&mon->delayed_work);

    rt_device_unregister(dev);

    rpi_firmware_put(mon->rpi_fw);
    rt_free(mon);

    return RT_EOK;
}

static struct rt_platform_driver rpi_voltage_monitor_driver =
{
    .name = "raspberrypi-voltage-monitor",

    .probe = rpi_voltage_monitor_probe,
    .remove = rpi_voltage_monitor_remove,
};
RT_PLATFORM_DRIVER_EXPORT(rpi_voltage_monitor_driver);
