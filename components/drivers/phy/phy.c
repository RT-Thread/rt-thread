
/*
 * Copyright (c) 2006-2023, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author        Notes
 * 2020-09-27     wangqiang     first version
 */
#include <stddef.h>
#include <rthw.h>
#include <rtthread.h>
#include <rtdevice.h>

#define DBG_TAG "PHY"
#define DBG_LVL DBG_INFO
#include <rtdbg.h>


static rt_ssize_t phy_device_read(rt_device_t dev, rt_off_t pos, void *buffer, rt_size_t count)
{
    struct rt_phy_device *phy = (struct rt_phy_device *)dev->user_data;
    struct rt_phy_msg *msg = (struct rt_phy_msg *)buffer;
    return phy->bus->ops->read(phy->bus, phy->addr, msg->reg, &(msg->value), 4);
}
static rt_ssize_t phy_device_write(rt_device_t dev, rt_off_t pos, const void *buffer, rt_size_t count)
{
    struct rt_phy_device *phy = (struct rt_phy_device *)dev->user_data;
    struct rt_phy_msg *msg = (struct rt_phy_msg *)buffer;
    return phy->bus->ops->write(phy->bus, phy->addr, msg->reg, &(msg->value), 4);
}

#ifdef RT_USING_DEVICE_OPS
const static struct rt_device_ops phy_ops =
{
    RT_NULL,
    RT_NULL,
    RT_NULL,
    phy_device_read,
    phy_device_write,
    RT_NULL,
};
#endif

/*
* phy device register
*/
rt_err_t rt_hw_phy_register(struct rt_phy_device *phy, const char *name)
{
    rt_err_t ret;
    struct rt_device *device;

    device = &(phy->parent);

    device->type = RT_Device_Class_PHY;
    device->rx_indicate = RT_NULL;
    device->tx_complete = RT_NULL;

#ifdef RT_USING_DEVICE_OPS
    device->ops = &phy_ops;
#else
    device->init = NULL;
    device->open = NULL;
    device->close = NULL;
    device->read = phy_device_read;
    device->write = phy_device_write;
    device->control = NULL;
#endif
    device->user_data = phy;

    /* register a character device */
    ret = rt_device_register(device, name, RT_DEVICE_FLAG_RDWR);

    return ret;
}

#ifdef RT_USING_DM
rt_phy_status rt_phy_init(struct rt_phy_device *phy, void *object, rt_uint32_t phy_addr, rt_uint32_t src_clock_hz)
{
    if (phy->ops->init)
    {
        return phy->ops->init(phy, object, phy_addr, src_clock_hz);
    }

    return PHY_STATUS_OK;
}

rt_phy_status rt_phy_exit(struct rt_phy_device *phy, void *object, rt_uint32_t phy_addr)
{
    if (phy->ops->exit)
    {
        return phy->ops->exit(phy, object, phy_addr);
    }

    return PHY_STATUS_OK;
}

rt_phy_status rt_phy_power_on(struct rt_phy_device *phy)
{
    if (phy->ops->power_on)
    {
        return phy->ops->power_on(phy);
    }

    return PHY_STATUS_OK;
}

rt_phy_status rt_phy_power_off(struct rt_phy_device *phy)
{
    if (phy->ops->power_off)
    {
        return phy->ops->power_off(phy);
    }

    return PHY_STATUS_OK;
}
#endif
