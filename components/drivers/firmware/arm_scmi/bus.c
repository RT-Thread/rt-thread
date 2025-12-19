/*
 * Copyright (c) 2006-2022, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2022-11-26     GuEe-GUI     first version
 */

#include <rtthread.h>
#include <rtdevice.h>

#define DBG_TAG "scmi.bus"
#define DBG_LVL DBG_INFO
#include <rtdbg.h>

static struct rt_bus scmi_bus;

rt_err_t rt_scmi_driver_register(struct rt_scmi_driver *driver)
{
    RT_ASSERT(driver != RT_NULL);

    driver->parent.bus = &scmi_bus;

    return rt_driver_register(&driver->parent);
}

rt_err_t rt_scmi_device_register(struct rt_scmi_device *device)
{
    RT_ASSERT(device != RT_NULL);

    return rt_bus_add_device(&scmi_bus, &device->parent);
}
static rt_bool_t scmi_match(rt_driver_t drv, rt_device_t dev)
{
    const struct rt_scmi_device_id *id;
    struct rt_scmi_driver *driver = rt_container_of(drv, struct rt_scmi_driver, parent);
    struct rt_scmi_device *device = rt_container_of(dev, struct rt_scmi_device, parent);

    for (id = driver->ids; id->protocol_id; ++id)
    {
        if (id->protocol_id == device->protocol_id)
        {
            if (!id->name || !device->name || !rt_strcmp(id->name, device->name))
            {
                return RT_TRUE;
            }
        }
    }

    return RT_FALSE;
}

static rt_err_t scmi_probe(rt_device_t dev)
{
    rt_err_t err;
    struct rt_scmi_driver *driver = rt_container_of(dev->drv, struct rt_scmi_driver, parent);
    struct rt_scmi_device *device = rt_container_of(dev, struct rt_scmi_device, parent);

    if (!device->agent)
    {
        return -RT_EINVAL;
    }

    err = driver->probe(device);

    return err;
}

static struct rt_bus scmi_bus =
{
    .name = "scmi",
    .match = scmi_match,
    .probe = scmi_probe,
};

static int scmi_bus_init(void)
{
    rt_bus_register(&scmi_bus);

    return 0;
}
INIT_CORE_EXPORT(scmi_bus_init);
