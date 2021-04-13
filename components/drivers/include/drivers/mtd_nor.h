/*
 * COPYRIGHT (C) 2011-2021, Real-Thread Information Technology Ltd
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2012-5-30      Bernard      the first version
 */

#ifndef __MTD_NOR_H__
#define __MTD_NOR_H__

#include <rtdevice.h>

struct rt_mtd_nor_driver_ops;
#define RT_MTD_NOR_DEVICE(device)   ((struct rt_mtd_nor_device*)(device))

struct rt_mtd_nor_device
{
    struct rt_device parent;

    rt_uint32_t block_size;         /* The Block size in the flash */
    rt_uint32_t block_start;        /* The start of available block*/
    rt_uint32_t block_end;          /* The end of available block */

    /* operations interface */
    const struct rt_mtd_nor_driver_ops* ops;
};

struct rt_mtd_nor_driver_ops
{
    rt_err_t (*read_id) (struct rt_mtd_nor_device* device);

    rt_size_t (*read)    (struct rt_mtd_nor_device* device, rt_off_t offset, rt_uint8_t* data, rt_uint32_t length);
    rt_size_t (*write)   (struct rt_mtd_nor_device* device, rt_off_t offset, const rt_uint8_t* data, rt_uint32_t length);

    rt_err_t (*erase_block)(struct rt_mtd_nor_device* device, rt_off_t offset, rt_uint32_t length);
};

rt_err_t rt_mtd_nor_register_device(const char* name, struct rt_mtd_nor_device* device);

rt_inline rt_uint32_t rt_mtd_nor_read_id(struct rt_mtd_nor_device* device)
{
    return device->ops->read_id(device);
}

rt_inline rt_size_t rt_mtd_nor_read(
    struct rt_mtd_nor_device* device,
    rt_off_t offset, rt_uint8_t* data, rt_uint32_t length)
{
    return device->ops->read(device, offset, data, length);
}

rt_inline rt_size_t rt_mtd_nor_write(
    struct rt_mtd_nor_device* device,
    rt_off_t offset, const rt_uint8_t* data, rt_uint32_t length)
{
    return device->ops->write(device, offset, data, length);
}

rt_inline rt_err_t rt_mtd_nor_erase_block(struct rt_mtd_nor_device* device, rt_off_t offset, rt_size_t length)
{
    return device->ops->erase_block(device, offset, length);
}

#endif
