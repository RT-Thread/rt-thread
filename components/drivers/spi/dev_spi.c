/*
 * Copyright (c) 2006-2023, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 */

#include <rtthread.h>
#include "drivers/dev_spi.h"

#define DBG_TAG     "spi.dev"
#define DBG_LVL     DBG_INFO
#include <rtdbg.h>

#ifdef RT_USING_DM
#include "dev_spi_dm.h"
#endif

/* SPI bus device interface, compatible with RT-Thread 0.3.x/1.0.x */
static rt_ssize_t _spi_bus_device_read(rt_device_t dev,
                                      rt_off_t    pos,
                                      void       *buffer,
                                      rt_size_t   size)
{
    struct rt_spi_bus *bus;

    bus = (struct rt_spi_bus *)dev;
    RT_ASSERT(bus != RT_NULL);
    RT_ASSERT(bus->owner != RT_NULL);

    return rt_spi_transfer(bus->owner, RT_NULL, buffer, size);
}

static rt_ssize_t _spi_bus_device_write(rt_device_t dev,
                                       rt_off_t    pos,
                                       const void *buffer,
                                       rt_size_t   size)
{
    struct rt_spi_bus *bus;

    bus = (struct rt_spi_bus *)dev;
    RT_ASSERT(bus != RT_NULL);
    RT_ASSERT(bus->owner != RT_NULL);

    return rt_spi_transfer(bus->owner, buffer, RT_NULL, size);
}

#ifdef RT_USING_DEVICE_OPS
const static struct rt_device_ops spi_bus_ops =
{
    RT_NULL,
    RT_NULL,
    RT_NULL,
    _spi_bus_device_read,
    _spi_bus_device_write,
    RT_NULL
};
#endif

rt_err_t rt_spi_bus_device_init(struct rt_spi_bus *bus, const char *name)
{
    struct rt_device *device;
    RT_ASSERT(bus != RT_NULL);

    device = &bus->parent;

    /* set device type */
    device->type    = RT_Device_Class_SPIBUS;
    /* initialize device interface */
#ifdef RT_USING_DEVICE_OPS
    device->ops     = &spi_bus_ops;
#else
    device->init    = RT_NULL;
    device->open    = RT_NULL;
    device->close   = RT_NULL;
    device->read    = _spi_bus_device_read;
    device->write   = _spi_bus_device_write;
    device->control = RT_NULL;
#endif

    /* register to device manager */
    return rt_device_register(device, name, RT_DEVICE_FLAG_RDWR);
}

/* SPI Dev device interface, compatible with RT-Thread 0.3.x/1.0.x */
static rt_ssize_t _spidev_device_read(rt_device_t dev,
                                     rt_off_t    pos,
                                     void       *buffer,
                                     rt_size_t   size)
{
    struct rt_spi_device *device;

    device = (struct rt_spi_device *)dev;
    RT_ASSERT(device != RT_NULL);
    RT_ASSERT(device->bus != RT_NULL);

    return rt_spi_transfer(device, RT_NULL, buffer, size);
}

static rt_ssize_t _spidev_device_write(rt_device_t dev,
                                      rt_off_t    pos,
                                      const void *buffer,
                                      rt_size_t   size)
{
    struct rt_spi_device *device;

    device = (struct rt_spi_device *)dev;
    RT_ASSERT(device != RT_NULL);
    RT_ASSERT(device->bus != RT_NULL);

    return rt_spi_transfer(device, buffer, RT_NULL, size);
}

static rt_err_t _spidev_device_control(rt_device_t dev,
                                       int         cmd,
                                       void       *args)
{
    switch (cmd)
    {
    case 0: /* set device */
        break;
    case 1:
        break;
    }

    return RT_EOK;
}

#ifdef RT_USING_DEVICE_OPS
const static struct rt_device_ops spi_device_ops =
{
    RT_NULL,
    RT_NULL,
    RT_NULL,
    _spidev_device_read,
    _spidev_device_write,
    _spidev_device_control
};
#endif

rt_err_t rt_spidev_device_init(struct rt_spi_device *dev, const char *name)
{
    struct rt_device *device;
    RT_ASSERT(dev != RT_NULL);

    device = &(dev->parent);

    /* set device type */
    device->type    = RT_Device_Class_SPIDevice;
#ifdef RT_USING_DEVICE_OPS
    device->ops     = &spi_device_ops;
#else
    device->init    = RT_NULL;
    device->open    = RT_NULL;
    device->close   = RT_NULL;
    device->read    = _spidev_device_read;
    device->write   = _spidev_device_write;
    device->control = _spidev_device_control;
#endif

    /* register to device manager */
    return rt_device_register(device, name, RT_DEVICE_FLAG_RDWR);
}

#ifdef RT_USING_DM
static rt_err_t spidev_probe(struct rt_spi_device *spi_dev)
{
    const char *bus_name;
    struct rt_device *dev = &spi_dev->parent;

    if (spi_dev->parent.ofw_node)
    {
        if (rt_dm_dev_prop_index_of_string(dev, "compatible", "spidev") >= 0)
        {
            LOG_E("spidev is not supported in OFW");

            return -RT_EINVAL;
        }
    }

    bus_name = rt_dm_dev_get_name(&spi_dev->bus->parent);
    rt_dm_dev_set_name(dev, "%s_%d", bus_name, spi_dev->chip_select);

    return RT_EOK;
}

static const struct rt_spi_device_id spidev_ids[] =
{
    { .name = "dh2228fv" },
    { .name = "ltc2488" },
    { .name = "sx1301" },
    { .name = "bk4" },
    { .name = "dhcom-board" },
    { .name = "m53cpld" },
    { .name = "spi-petra" },
    { .name = "spi-authenta" },
    { .name = "em3581" },
    { .name = "si3210" },
    { /* sentinel */ },
};

static const struct rt_ofw_node_id spidev_ofw_ids[] =
{
    { .compatible = "cisco,spi-petra" },
    { .compatible = "dh,dhcom-board" },
    { .compatible = "lineartechnology,ltc2488" },
    { .compatible = "lwn,bk4" },
    { .compatible = "menlo,m53cpld" },
    { .compatible = "micron,spi-authenta" },
    { .compatible = "rohm,dh2228fv" },
    { .compatible = "semtech,sx1301" },
    { .compatible = "silabs,em3581" },
    { .compatible = "silabs,si3210" },
    { .compatible = "rockchip,spidev" },
    { /* sentinel */ },
};

static struct rt_spi_driver spidev_driver =
{
    .ids = spidev_ids,
    .ofw_ids = spidev_ofw_ids,

    .probe = spidev_probe,
};
RT_SPI_DRIVER_EXPORT(spidev_driver);
#endif /* RT_USING_DM */
