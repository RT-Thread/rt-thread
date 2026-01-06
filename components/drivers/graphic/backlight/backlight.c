/*
 * Copyright (c) 2006-2023, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2023-02-25     GuEe-GUI     the first version
 */

#include <rtthread.h>

#define DBG_TAG "rtdm.backlight"
#define DBG_LVL DBG_INFO
#include <rtdbg.h>

#include <stdlib.h>
#include <drivers/core/dm.h>
#include <drivers/backlight.h>

static struct rt_dm_ida backlight_ida = RT_DM_IDA_INIT(GRAPHIC_BACKLIGHT);

static rt_ssize_t _backlight_read(rt_device_t dev, rt_off_t pos, void *buffer, rt_size_t size)
{
    rt_ssize_t res;
    int brightness_len;
    rt_uint32_t brightness;
    char string[sizeof("4294967295")];
    struct rt_backlight_device *bl = rt_container_of(dev, struct rt_backlight_device, parent);

    if ((res = rt_backlight_get_brightness(bl, &brightness)))
    {
        return res;
    }

    brightness_len = rt_sprintf(string, "%u", brightness);

    if (pos < brightness_len)
    {
        size = rt_min_t(rt_size_t, size, brightness_len - pos);
        rt_strncpy(buffer, &string[pos], size);

        return size;
    }
    else
    {
        return 0;
    }
}

static rt_ssize_t _backlight_write(rt_device_t dev, rt_off_t pos, const void *buffer, rt_size_t size)
{
    rt_ssize_t res;
    rt_uint32_t brightness = atoi(buffer);
    struct rt_backlight_device *bl = rt_container_of(dev, struct rt_backlight_device, parent);

    if (brightness > bl->props.max_brightness)
    {
        LOG_D("%s: brightness(%u) > max_brightness(%u)",
                rt_dm_dev_get_name(dev), brightness, bl->props.max_brightness);

        return -RT_EINVAL;
    }

    if ((res = rt_backlight_set_brightness(bl, brightness)))
    {
        return res;
    }

    LOG_D("%s: brightness to %u", rt_dm_dev_get_name(dev), brightness);

    return size;
}

#ifdef RT_USING_DEVICE_OPS
const static struct rt_device_ops _backlight_ops =
{
    .read = _backlight_read,
    .write = _backlight_write,
};
#endif

rt_err_t rt_backlight_register(struct rt_backlight_device *bl)
{
    rt_err_t err;
    int device_id;
    const char *dev_name;

    if (!bl || !bl->ops)
    {
        return -RT_EINVAL;
    }

    if ((device_id = rt_dm_ida_alloc(&backlight_ida)) < 0)
    {
        return -RT_EFULL;
    }

    rt_dm_dev_set_name(&bl->parent, "backlight%u", device_id);
    dev_name = rt_dm_dev_get_name(&bl->parent);

    rt_mutex_init(&bl->lock, dev_name, RT_IPC_FLAG_PRIO);

    bl->parent.type = RT_Device_Class_Char;
#ifdef RT_USING_DEVICE_OPS
    bl->parent.ops = &_backlight_ops;
#else
    bl->parent.read = _backlight_read;
    bl->parent.write = _backlight_write;
#endif
    bl->parent.master_id = backlight_ida.master_id;
    bl->parent.device_id = device_id;

    if ((err = rt_device_register(&bl->parent, dev_name, RT_DEVICE_FLAG_RDWR)))
    {
        rt_dm_ida_free(&backlight_ida, device_id);

        return err;
    }

    return RT_EOK;
}

rt_err_t rt_backlight_unregister(struct rt_backlight_device *bl)
{
    if (!bl)
    {
        return -RT_EINVAL;
    }

    rt_backlight_set_power(bl, RT_BACKLIGHT_POWER_POWERDOWN);

    rt_dm_ida_free(&backlight_ida, bl->parent.device_id);

    rt_device_unregister(&bl->parent);

    return RT_EOK;
}

rt_err_t rt_backlight_set_power(struct rt_backlight_device *bl, enum rt_backlight_power power)
{
    rt_err_t err;
    enum rt_backlight_power old_power;

    if (!bl || power >= RT_BACKLIGHT_POWER_NR)
    {
        return -RT_EINVAL;
    }

    rt_mutex_take(&bl->lock, RT_WAITING_FOREVER);

    old_power = bl->props.power;
    bl->props.power = power;

    if ((err = bl->ops->update_status(bl)))
    {
        bl->props.power = old_power;
    }

    rt_mutex_release(&bl->lock);

    return err;
}

rt_err_t rt_backlight_get_power(struct rt_backlight_device *bl, enum rt_backlight_power *out_power)
{
    if (!bl || !out_power)
    {
        return -RT_EINVAL;
    }

    rt_mutex_take(&bl->lock, RT_WAITING_FOREVER);

    *out_power = bl->props.power;

    rt_mutex_release(&bl->lock);

    return RT_EOK;
}

rt_err_t rt_backlight_set_brightness(struct rt_backlight_device *bl, rt_uint32_t brightness)
{
    rt_err_t err;
    rt_uint32_t old_brightness;

    if (!bl || brightness > bl->props.max_brightness)
    {
        return -RT_EINVAL;
    }

    rt_mutex_take(&bl->lock, RT_WAITING_FOREVER);

    old_brightness = bl->props.brightness;
    bl->props.brightness = brightness;

    if ((err = bl->ops->update_status(bl)))
    {
        bl->props.brightness = old_brightness;
    }

    rt_mutex_release(&bl->lock);

    return err;
}

rt_err_t rt_backlight_get_brightness(struct rt_backlight_device *bl, rt_uint32_t *out_brightness)
{
    rt_err_t err;

    if (!bl || !out_brightness)
    {
        return -RT_EINVAL;
    }

    rt_mutex_take(&bl->lock, RT_WAITING_FOREVER);

    if (bl->ops->get_brightness)
    {
        err = bl->ops->get_brightness(bl, out_brightness);
    }
    else
    {
        *out_brightness = rt_backlight_power_brightness(bl);

        err = RT_EOK;
    }

    rt_mutex_release(&bl->lock);

    return err;
}
