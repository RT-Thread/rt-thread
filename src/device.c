/*
 * File      : device.c
 * This file is part of RT-Thread RTOS
 * COPYRIGHT (C) 2006, RT-Thread Development Team
 *
 * The license and distribution terms for this file may be
 * found in the file LICENSE in this distribution or at
 * http://openlab.rt-thread.com/license/LICENSE
 *
 * Change Logs:
 * Date           Author       Notes
 * 2007-01-21     Bernard      the first version
 */

#include <rtthread.h>
#include "kservice.h"

#ifdef RT_USING_DEVICE

/**
 * This function registers a device driver with specified name.
 *
 * @param dev the pointer of device driver structure
 * @param name the device driver's name
 * @param flags the flag of device
 *
 * @return the error code, RT_EOK on initialization successfully.
 */
rt_err_t rt_device_register(rt_device_t dev, const char* name, rt_uint16_t flags)
{
	if (dev == RT_NULL) return -RT_ERROR;

	rt_object_init(&(dev->parent), RT_Object_Class_Device, name);
	dev->flag = flags;

	return RT_EOK;
}

/**
 * This function removes a previouly registered device driver
 *
 * @param dev the pointer of device driver structure
 *
 * @return the error code, RT_EOK on successfully.
 */
rt_err_t rt_device_unregister(rt_device_t dev)
{
	RT_ASSERT(dev != RT_NULL);

	rt_object_detach(&(dev->parent));

	return RT_EOK;
}

/**
 * This function initializes all registered device driver
 *
 * @return the error code, RT_EOK on successfully.
 */
rt_err_t rt_device_init_all()
{
	struct rt_device* device;
	struct rt_list_node* node;
	struct rt_object_information *information;
	register rt_err_t result;

	extern struct rt_object_information rt_object_container[];

	information = &rt_object_container[RT_Object_Class_Device];

	/* for each device */
	for (node = information->object_list.next; node != &(information->object_list); node = node->next)
	{
		rt_err_t (*init)(rt_device_t dev);
		device = (struct rt_device*)rt_list_entry(node, struct rt_object, list);

		/* get device init handler */
		init = device->init;
		if (init != RT_NULL && !(device->flag & RT_DEVICE_FLAG_ACTIVATED))
		{
			result = init(device);
			if (result != RT_EOK)
			{
				rt_kprintf("init device:%s error:\n", device->parent.name);
				rt_kprintf("error code:%d\n", result);
			}
		}
	}

	return RT_EOK;
}

/**
 * This function finds a device driver by specified name.
 *
 * @param name the device driver's name
 *
 * @return the registered device driver on successful, or RT_NULL on failure.
 */
rt_device_t rt_device_find(const char* name)
{
	/* try to find device object */
	return (struct rt_device*) rt_object_find (RT_Object_Class_Device,
		name);
}

/**
 * This function will open a device
 *
 * @param dev the pointer of device driver structure
 *
 * @return the result
 */
rt_err_t rt_device_open(rt_device_t dev, rt_uint16_t oflag)
{
	rt_err_t result;
	rt_err_t (*open) (rt_device_t dev, rt_uint16_t oflag);

	RT_ASSERT(dev != RT_NULL);

	result = RT_EOK;

	/* device is a standalone device and opened */
	if ((dev->flag & RT_DEVICE_FLAG_STANDALONE) &&
		(dev->open_flag & RT_DEVICE_OFLAG_OPEN))
		return -RT_EBUSY;

	/* call device open interface */
	open = dev->open;
	if (open != RT_NULL)
	{
		result = open(dev, oflag);
	}
	else
	{
		/* no this interface in device driver */
		result = -RT_ENOSYS;
	}

	/* set open flag */
	if (result == RT_EOK || result == -RT_ENOSYS)
		dev->open_flag = oflag | RT_DEVICE_OFLAG_OPEN;

	return result;
}

/**
 * This function will close a device
 *
 * @param dev the pointer of device driver structure
 *
 * @return the result
 */
rt_err_t rt_device_close(rt_device_t dev)
{
	rt_err_t result;
	rt_err_t (*close)(rt_device_t dev);

	RT_ASSERT(dev != RT_NULL);

	/* call device close interface */
	close = dev->close;
	if (close != RT_NULL)
	{
		result = close(dev);
	}
	else
	{
		/* no this interface in device driver */
		result = -RT_ENOSYS;
	}

	/* set open flag */
	if (result == RT_EOK || result == -RT_ENOSYS)
		dev->open_flag = RT_DEVICE_OFLAG_CLOSE;

	return result;
}

/**
 * This function will read some data from a device.
 *
 * @param dev the pointer of device driver structure
 * @param pos the position of reading
 * @param buffer the data buffer to save read data
 * @param size the size of buffer
 *
 * @return the actually read size on successful, otherwise negative returned.
 */
rt_size_t rt_device_read (rt_device_t dev, rt_off_t pos, void* buffer, rt_size_t size)
{
	rt_size_t (*read)(rt_device_t dev, rt_off_t pos, void* buffer, rt_size_t size);

	RT_ASSERT(dev != RT_NULL);

	/* call device read interface */
	read = dev->read;
	if (read != RT_NULL)
	{
		return read(dev, pos, buffer, size);
	}

	/* set error code */
	rt_set_errno(-RT_ENOSYS);
	return 0;
}

/**
 * This function will write some data to a device.
 *
 * @param dev the pointer of device driver structure
 * @param pos the position of written
 * @param buffer the data buffer to be written to device
 * @param size the size of buffer
 *
 * @return the actually written size on successful, otherwise negative returned.
 */
rt_size_t rt_device_write(rt_device_t dev, rt_off_t pos, const void* buffer, rt_size_t size)
{
	rt_size_t (*write)(rt_device_t dev, rt_off_t pos, const void* buffer, rt_size_t size);

	RT_ASSERT(dev != RT_NULL);

	/* call device write interface */
	write = dev->write;
	if (write != RT_NULL)
	{
		return write(dev, pos, buffer, size);
	}

	/* set error code */
	rt_set_errno(-RT_ENOSYS);
	return 0;
}

/**
 * This function will perform a variety of control functions on devices.
 *
 * @param dev the pointer of device driver structure
 * @param cmd the command sent to device
 * @param arg the argument of command
 *
 * @return the result
 */
rt_err_t rt_device_control(rt_device_t dev, rt_uint8_t cmd, void* arg)
{
	rt_err_t (*control)(rt_device_t dev, rt_uint8_t cmd, void* arg);

	RT_ASSERT(dev != RT_NULL);

	/* call device write interface */
	control = dev->control;
	if (control != RT_NULL)
	{
		return control(dev, cmd, arg);
	}

	return -RT_ENOSYS;
}

rt_err_t rt_device_set_rx_indicate(rt_device_t dev, rt_err_t (*rx_ind )(rt_device_t dev, rt_size_t size))
{
	RT_ASSERT(dev != RT_NULL);

	dev->rx_indicate = rx_ind;
	return RT_EOK;
}

rt_err_t rt_device_set_tx_complete(rt_device_t dev, rt_err_t (*tx_done)(rt_device_t dev, void *buffer))
{
	RT_ASSERT(dev != RT_NULL);

	dev->tx_complete = tx_done;
	return RT_EOK;
}

#endif
