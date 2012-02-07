/*
 * File      : mtd.h
 * This file is part of RT-Thread RTOS
 * COPYRIGHT (C) 2006 - 2012, RT-Thread Development Team
 *
 * The license and distribution terms for this file may be
 * found in the file LICENSE in this distribution or at
 * http://www.rt-thread.org/license/LICENSE
 *
 * Change Logs:
 * Date           Author       Notes
 * 2011-12-05     Bernard      the first version
 */

/*
 * COPYRIGHT (C) 2012, Shanghai Real Thread
 */

#ifndef __MTD_H__
#define __MTD_H__

#include <rtdevice.h>

struct rt_mtd_driver_ops;
#define RT_MTD_DEVICE(device)	((struct rt_mtd_device*)(device))

struct rt_mtd_device
{
	struct rt_device parent;

	rt_uint32_t page_size;			/* The Page size in the flash */
	rt_uint32_t block_size;			/* The Block size in the flash */

	rt_uint16_t oob_size;			/* Out of bank size */
	rt_uint16_t reserve;

	rt_uint32_t block_start;		/* The start of available block*/
	rt_uint32_t block_end;			/* The end of available block */

	/* operations interface */
	const struct rt_mtd_driver_ops* ops;
};

struct rt_mtd_driver_ops
{
	rt_uint32_t (*read_id) (struct rt_mtd_device* device);

	int (*read) (struct rt_mtd_device* device, rt_off_t position, rt_uint8_t* data, rt_size_t size);
	int (*write)(struct rt_mtd_device* device, rt_off_t position, const rt_uint8_t* data, rt_size_t size);

	int (*oob_read) (struct rt_mtd_device* device, rt_off_t position, rt_uint8_t* spare);
	int (*oob_write)(struct rt_mtd_device* device, rt_off_t position, const rt_uint8_t* spare);

	rt_err_t (*erase_block)(struct rt_mtd_device* device, rt_uint32_t block);
};

rt_err_t rt_mtd_register_device(const char* name, struct rt_mtd_device* device);

rt_inline rt_uint32_t rt_mtd_read_id(struct rt_mtd_device* device)
{
	return device->ops->read_id(device);
}

rt_inline int rt_mtd_read(struct rt_mtd_device* device, rt_off_t position,
		rt_uint8_t* data, rt_size_t size)
{
	return device->ops->read(device, position, data, size);
}

rt_inline int rt_mtd_write(struct rt_mtd_device* device, rt_off_t position,
		const rt_uint8_t* data, rt_size_t size)
{
	return device->ops->write(device, position, data, size);
}

rt_inline int rt_mtd_oob_read(struct rt_mtd_device* device, rt_off_t position,
		rt_uint8_t* data)
{
	return device->ops->oob_read(device, position, data);
}

rt_inline int rt_mtd_oob_write(struct rt_mtd_device* device, rt_off_t position,
		const rt_uint8_t* data)
{
	return device->ops->oob_write(device, position, data);
}

rt_inline rt_err_t rt_mtd_erase_block(struct rt_mtd_device* device, rt_uint32_t block)
{
	return device->ops->erase_block(device, block);
}

#endif
