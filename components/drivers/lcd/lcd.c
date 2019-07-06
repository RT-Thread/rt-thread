/*
 * Copyright (c) 2006-2018, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2019-07-01     tyustli      the first version
 *
 */

#include <rtdevice.h>

/**
 * LCD interface sections
 */
#ifdef RT_USING_DEVICE_OPS
const static struct rt_device_ops lcd_intf_ops =
{
    RT_NULL,
    RT_NULL,
    RT_NULL,
    RT_NULL,
    RT_NULL,
    RT_NULL,
};
#endif

rt_err_t rt_lcd_intf_register(struct rt_lcd_intf *intf, const char *name, struct rt_lcd_intf_ops *ops, void *user_data)
{
    rt_err_t result;

    result = RT_EOK;
    RT_ASSERT(ops != RT_NULL && intf != RT_NULL);

    intf->parent.type = RT_Device_Class_Miscellaneous;
    intf->parent.rx_indicate = RT_NULL;
    intf->parent.tx_complete = RT_NULL;

#ifdef RT_USING_DEVICE_OPS
    device->parent.ops         = &lcd_intf_ops;
#else
    intf->parent.init        = RT_NULL;
    intf->parent.open        = RT_NULL;
    intf->parent.close       = RT_NULL;
    intf->parent.read        = RT_NULL;
    intf->parent.write       = RT_NULL;
    intf->parent.control     = RT_NULL;
#endif
    intf->ops = ops;
    intf->parent.user_data = (void *)user_data;

    result = rt_device_register(&intf->parent, name, RT_DEVICE_FLAG_RDWR);

    return result;
}

rt_err_t rt_lcd_intf_write_cmd(struct rt_lcd_intf *dev, rt_uint16_t cmd)
{
    rt_err_t result;

    result = RT_EOK;
    RT_ASSERT(dev);

    if (dev->ops->wtire_cmd != RT_NULL)
    {
        result = dev->ops->wtire_cmd(dev, cmd);
    }
    else
    {
        result = -RT_ENOSYS;
    }

    return result;
}

rt_err_t rt_lcd_intf_write_data(struct rt_lcd_intf *dev, rt_uint16_t write_data)
{
    rt_err_t result = RT_EOK;

    RT_ASSERT(dev);

    if (dev->ops->write_data != RT_NULL)
    {
        result = dev->ops->write_data(dev, write_data);
    }
    else
    {
        result = -RT_ENOSYS;
    }

    return result;
}

rt_uint16_t rt_lcd_intf_read_data(struct rt_lcd_intf *dev, rt_uint16_t reg)
{
    rt_uint16_t value;

    RT_ASSERT(dev);
    dev->ops->read_data(dev, reg, &value);

    return value;
}

rt_err_t rt_lcd_intf_write_reg(struct rt_lcd_intf *dev, rt_uint16_t reg, rt_uint16_t write_data)
{
    rt_err_t result;

    result	= RT_EOK;
    RT_ASSERT(dev);

    if (dev->ops->write_reg != RT_NULL)
    {
        result = dev->ops->write_reg(dev, reg, write_data);
    }
    else
    {
        result = -RT_ENOSYS;
    }

    return result;
}


/**
 * LCD device sections
 *
 */
static rt_err_t _lcd_control(rt_device_t dev, int cmd, void *args)
{
    rt_lcd_t lcd;
    rt_err_t result = RT_EOK;
    RT_ASSERT(dev != RT_NULL);
    lcd = (rt_lcd_t)dev;

    result = lcd->ops->lcd_control(lcd, cmd, args);

    return result;
}

#ifdef RT_USING_DEVICE_OPS
static const struct rt_device_ops lcd_device_ops =
{
    RT_NULL,
    RT_NULL,
    RT_NULL,
    RT_NULL,
    RT_NULL,
    _lcd_control,
};
#endif /* RT_USING_DEVICE_OPS */

int rt_lcd_device_register(rt_lcd_t      lcd,
                           const char    *name,
                           rt_uint16_t   flag,
                           void          *user_data)
{
    rt_err_t result;

    result = RT_EOK;
    struct rt_device *device;
    RT_ASSERT(lcd != RT_NULL);

    /* init lcd_lock semaphore */
    result = rt_sem_init(&lcd->lcd_lock, "lcd_lock", 0, RT_IPC_FLAG_FIFO);
    if (result != RT_EOK)
    {
        rt_kprintf("init semaphore failed!\n");
        result = -RT_ENOMEM;
        goto __exit;
    }

    device = &(lcd->parent);

#ifdef RT_USING_DEVICE_OPS
    device->ops = &lcd_device_ops;
#else
    device->init = RT_NULL;
    device->open = RT_NULL;
    device->close = RT_NULL;
    device->read  = RT_NULL;
    device->write = RT_NULL;
    device->control = _lcd_control;
#endif /* RT_USING_DEVICE_OPS */

    device->type         = RT_Device_Class_Graphic;
    device->user_data    = (void *)user_data;

    result = rt_device_register(device, name, flag | RT_DEVICE_FLAG_STANDALONE);

__exit:
    if (result != RT_EOK)
    {
        rt_sem_detach(&lcd->lcd_lock);
    }

    return result;
}


