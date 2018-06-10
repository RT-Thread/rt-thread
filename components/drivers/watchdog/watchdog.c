/*
 * File      : watchdog.h
 * This file is part of RT-Thread RTOS
 * COPYRIGHT (C) 2012-2014, Shanghai Real-Thread Electronic Technology Co.,Ltd
 *
 *  This program is free software; you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation; either version 2 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License along
 *  with this program; if not, write to the Free Software Foundation, Inc.,
 *  51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.
 *
 * Change Logs:
 * Date           Author       Notes
 * 2012-09-12     heyuanjie87  first version.
 * 2014-03-04     Bernard      code cleanup
 */

#include <drivers/watchdog.h>

/* RT-Thread Device Interface */

/*
 * This function initializes serial
 */
static rt_err_t rt_watchdog_init(struct rt_device *dev)
{
    rt_watchdog_t *wtd;

    RT_ASSERT(dev != RT_NULL);
    wtd = (rt_watchdog_t *)dev;
    if (wtd->ops->init)
    {
        return (wtd->ops->init(wtd));
    }

    return (-RT_ENOSYS);
}

static rt_err_t rt_watchdog_open(struct rt_device *dev, rt_uint16_t oflag)
{
    return (RT_EOK);
}

static rt_err_t rt_watchdog_close(struct rt_device *dev)
{
    rt_watchdog_t *wtd;

    RT_ASSERT(dev != RT_NULL);
    wtd = (rt_watchdog_t *)dev;

    if (wtd->ops->control(wtd, RT_DEVICE_CTRL_WDT_STOP, RT_NULL) != RT_EOK)
    {
        rt_kprintf(" This watchdog can not be stoped\n");

        return (-RT_ERROR);
    }

    return (RT_EOK);
}

static rt_err_t rt_watchdog_control(struct rt_device *dev,
                                    int              cmd,
                                    void             *args)
{
    rt_watchdog_t *wtd;

    RT_ASSERT(dev != RT_NULL);
    wtd = (rt_watchdog_t *)dev;

    return (wtd->ops->control(wtd, cmd, args));
}

#ifdef RT_USING_DEVICE_OPS
const static struct rt_device_ops wdt_ops = 
{
    rt_watchdog_init,
    rt_watchdog_open,
    rt_watchdog_close,
    RT_NULL,
    RT_NULL,
    rt_watchdog_control,
};
#endif

/**
 * This function register a watchdog device
 */
rt_err_t rt_hw_watchdog_register(struct rt_watchdog_device *wtd,
                                 const char                *name,
                                 rt_uint32_t                flag,
                                 void                      *data)
{
    struct rt_device *device;
    RT_ASSERT(wtd != RT_NULL);

    device = &(wtd->parent);

    device->type        = RT_Device_Class_Miscellaneous;
    device->rx_indicate = RT_NULL;
    device->tx_complete = RT_NULL;

#ifdef RT_USING_DEVICE_OPS
    device->ops         = &wdt_ops;
#else
    device->init        = rt_watchdog_init;
    device->open        = rt_watchdog_open;
    device->close       = rt_watchdog_close;
    device->read        = RT_NULL;
    device->write       = RT_NULL;
    device->control     = rt_watchdog_control;
#endif
    device->user_data   = data;

    /* register a character device */
    return rt_device_register(device, name, flag);
}
