/*
 * COPYRIGHT (C) 2011-2023, Real-Thread Information Technology Ltd
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2012-5-30     Bernard      the first version
 */

#include <rtdevice.h>

#ifdef RT_USING_MTD_NOR

/**
 * RT-Thread Generic Device Interface
 */
static rt_err_t _mtd_init(rt_device_t dev)
{
    return RT_EOK;
}

static rt_err_t _mtd_open(rt_device_t dev, rt_uint16_t oflag)
{
    return RT_EOK;
}

static rt_err_t _mtd_close(rt_device_t dev)
{
    return RT_EOK;
}

static rt_ssize_t _mtd_read(rt_device_t dev,
                           rt_off_t    pos,
                           void       *buffer,
                           rt_size_t   size)
{
    return size;
}

static rt_ssize_t _mtd_write(rt_device_t dev,
                            rt_off_t    pos,
                            const void *buffer,
                            rt_size_t   size)
{
    return size;
}

static rt_err_t _mtd_control(rt_device_t dev, int cmd, void *args)
{
    return RT_EOK;
}

#ifdef RT_USING_DEVICE_OPS
const static struct rt_device_ops mtd_nor_ops =
{
    _mtd_init,
    _mtd_open,
    _mtd_close,
    _mtd_read,
    _mtd_write,
    _mtd_control
};
#endif

rt_err_t rt_mtd_nor_register_device(const char               *name,
                                    struct rt_mtd_nor_device *device)
{
    rt_device_t dev;

    dev = RT_DEVICE(device);
    RT_ASSERT(dev != RT_NULL);

    /* set device class and generic device interface */
    dev->type        = RT_Device_Class_MTD;
#ifdef RT_USING_DEVICE_OPS
    dev->ops         = &mtd_nor_ops;
#else
    dev->init        = _mtd_init;
    dev->open        = _mtd_open;
    dev->read        = _mtd_read;
    dev->write       = _mtd_write;
    dev->close       = _mtd_close;
    dev->control     = _mtd_control;
#endif

    dev->rx_indicate = RT_NULL;
    dev->tx_complete = RT_NULL;

    /* register to RT-Thread device system */
    return rt_device_register(dev, name, RT_DEVICE_FLAG_RDWR | RT_DEVICE_FLAG_STANDALONE);
}

rt_uint32_t rt_mtd_nor_read_id(struct rt_mtd_nor_device* device)
{
    return device->ops->read_id(device);
}

rt_ssize_t rt_mtd_nor_read(struct rt_mtd_nor_device* device,
        rt_off_t offset, rt_uint8_t* data, rt_size_t length)
{
    return device->ops->read(device, offset, data, length);
}

rt_ssize_t rt_mtd_nor_write(struct rt_mtd_nor_device* device,
        rt_off_t offset, const rt_uint8_t* data, rt_size_t length)
{
    return device->ops->write(device, offset, data, length);
}

rt_err_t rt_mtd_nor_erase_block(struct rt_mtd_nor_device* device,
        rt_off_t offset, rt_size_t length)
{
    return device->ops->erase_block(device, offset, length);
}

#endif
