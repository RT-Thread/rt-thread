/*
 * Copyright (c) 2006-2022, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2022-12-06     GuEe-GUI     first version
 */

#include "dev_spi_dm.h"

#define DBG_TAG "spi.bus"
#define DBG_LVL DBG_INFO
#include <rtdbg.h>

extern rt_err_t rt_spidev_device_init(struct rt_spi_device *dev, const char *name);

static struct rt_bus spi_bus;

void spi_bus_scan_devices(struct rt_spi_bus *bus)
{
#ifdef RT_USING_OFW
    if (bus->parent.ofw_node)
    {
        struct rt_ofw_node *np = bus->parent.ofw_node, *spi_dev_np;

        rt_ofw_foreach_available_child_node(np, spi_dev_np)
        {
            rt_uint64_t reg_offset;
            struct rt_spi_device *spi_dev;

            if (!rt_ofw_prop_read_bool(spi_dev_np, "compatible"))
            {
                continue;
            }

            spi_dev = rt_calloc(1, sizeof(*spi_dev));

            if (!spi_dev)
            {
                rt_ofw_node_put(spi_dev_np);
                LOG_E("Not memory to create spi device: %s",
                        rt_ofw_node_full_name(spi_dev_np));

                return;
            }

            rt_ofw_get_address(spi_dev_np, 0, &reg_offset, RT_NULL);

            spi_dev->parent.ofw_node = spi_dev_np;
            spi_dev->parent.type = RT_Device_Class_Unknown;
            spi_dev->name = rt_ofw_node_name(spi_dev_np);
            spi_dev->bus = bus;

            rt_dm_dev_set_name(&spi_dev->parent, rt_ofw_node_full_name(spi_dev_np));

            if (spi_device_ofw_parse(spi_dev))
            {
                continue;
            }

            rt_spi_device_register(spi_dev);
        }
    }
#endif /* RT_USING_OFW */
}

rt_err_t rt_spi_driver_register(struct rt_spi_driver *driver)
{
    RT_ASSERT(driver != RT_NULL);

    driver->parent.bus = &spi_bus;

    return rt_driver_register(&driver->parent);
}

rt_err_t rt_spi_device_register(struct rt_spi_device *device)
{
    RT_ASSERT(device != RT_NULL);

    return rt_bus_add_device(&spi_bus, &device->parent);
}

static rt_bool_t spi_match(rt_driver_t drv, rt_device_t dev)
{
    const struct rt_spi_device_id *id;
    struct rt_spi_driver *driver = rt_container_of(drv, struct rt_spi_driver, parent);
    struct rt_spi_device *device = rt_container_of(dev, struct rt_spi_device, parent);

    if ((id = driver->ids))
    {
        for (; id->name[0]; ++id)
        {
            if (!rt_strcmp(id->name, device->name))
            {
                device->id = id;
                device->ofw_id = RT_NULL;

                return RT_TRUE;
            }
        }
    }

#ifdef RT_USING_OFW
    device->ofw_id = rt_ofw_node_match(device->parent.ofw_node, driver->ofw_ids);

    if (device->ofw_id)
    {
        device->id = RT_NULL;

        return RT_TRUE;
    }
#endif

    return RT_FALSE;
}

static rt_err_t spi_probe(rt_device_t dev)
{
    rt_err_t err;
    struct rt_spi_bus *bus;
    struct rt_spi_driver *driver = rt_container_of(dev->drv, struct rt_spi_driver, parent);
    struct rt_spi_device *device = rt_container_of(dev, struct rt_spi_device, parent);

    if (!device->bus)
    {
        return -RT_EINVAL;
    }

    err = driver->probe(device);

    if (err)
    {
        return err;
    }

    bus = device->bus;

    if (bus->pins)
    {
        device->cs_pin = bus->pins[device->chip_select];

        rt_pin_mode(device->cs_pin, PIN_MODE_OUTPUT);
    }
    else
    {
        device->cs_pin = PIN_NONE;
    }

    /* Driver not register SPI device to system */
    if (device->parent.type == RT_Device_Class_Unknown)
    {
        rt_spidev_device_init(device, rt_dm_dev_get_name(&device->parent));
    }

    return err;
}

static rt_err_t spi_remove(rt_device_t dev)
{
    struct rt_spi_driver *driver = rt_container_of(dev->drv, struct rt_spi_driver, parent);
    struct rt_spi_device *device = rt_container_of(dev, struct rt_spi_device, parent);

    if (driver && driver->remove)
    {
        driver->remove(device);
    }
    rt_free(device);

    return RT_EOK;
}

static rt_err_t spi_shutdown(rt_device_t dev)
{
    struct rt_spi_driver *driver = rt_container_of(dev->drv, struct rt_spi_driver, parent);
    struct rt_spi_device *device = rt_container_of(dev, struct rt_spi_device, parent);

    if (driver && driver->shutdown)
    {
        driver->shutdown(device);
    }
    rt_free(device);

    return RT_EOK;
}

static struct rt_bus spi_bus =
{
    .name = "spi",
    .match = spi_match,
    .probe = spi_probe,
    .remove = spi_remove,
    .shutdown = spi_shutdown,
};

static int spi_bus_init(void)
{
    rt_bus_register(&spi_bus);

    return 0;
}
INIT_CORE_EXPORT(spi_bus_init);
