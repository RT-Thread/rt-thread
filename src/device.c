/*
 * File      : device.c
 * This file is part of RT-Thread RTOS
 * COPYRIGHT (C) 2006 - 2012, RT-Thread Development Team
 *
 * The license and distribution terms for this file may be
 * found in the file LICENSE in this distribution or at
 * http://www.rt-thread.org/license/LICENSE
 *
 * Change Logs:
 * Date           Author       Notes
 * 2007-01-21     Bernard      the first version
 * 2010-05-04     Bernard      add rt_device_init implementation
 */

#include <rtthread.h>

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
rt_err_t rt_device_register(rt_device_t dev, const char *name, rt_uint16_t flags)
{
	if (dev == RT_NULL)
		return -RT_ERROR;

	rt_object_init(&(dev->parent), RT_Object_Class_Device, name);
	dev->flag = flags;

	return RT_EOK;
}

/**
 * This function removes a previously registered device driver
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
rt_err_t rt_device_init_all(void)
{
	struct rt_device *device;
	struct rt_list_node *node;
	struct rt_object_information *information;
	register rt_err_t result;

	extern struct rt_object_information rt_object_container[];

	information = &rt_object_container[RT_Object_Class_Device];

	/* for each device */
	for (node = information->object_list.next; node != &(information->object_list); node = node->next)
	{
		rt_err_t (*init)(rt_device_t dev);
		device = (struct rt_device *)rt_list_entry(node, struct rt_object, list);

		/* get device init handler */
		init = device->init;
		if (init != RT_NULL && !(device->flag & RT_DEVICE_FLAG_ACTIVATED))
		{
			result = init(device);
			if (result != RT_EOK)
			{
				rt_kprintf("To initialize device:%s failed. The error code is %d\n",
					device->parent.name, result);
			}
			else
			{
				device->flag |= RT_DEVICE_FLAG_ACTIVATED;
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
rt_device_t rt_device_find(const char *name)
{
	struct rt_object *object;
	struct rt_list_node *node;
	struct rt_object_information *information;

	extern struct rt_object_information rt_object_container[];

	/* enter critical */
	if (rt_thread_self() != RT_NULL)
		rt_enter_critical();

	/* try to find device object */
	information = &rt_object_container[RT_Object_Class_Device];
	for (node = information->object_list.next; node != &(information->object_list); node = node->next)
	{
		object = rt_list_entry(node, struct rt_object, list);
		if (rt_strncmp(object->name, name, RT_NAME_MAX) == 0)
		{
			/* leave critical */
			if (rt_thread_self() != RT_NULL)
				rt_exit_critical();

			return (rt_device_t)object;
		}
	}

	/* leave critical */
	if (rt_thread_self() != RT_NULL)
		rt_exit_critical();

	/* not found */
	return RT_NULL;
}

/**
 * This function will initialize the specified device
 *
 * @param dev the pointer of device driver structure
 * 
 * @return the result
 */
rt_err_t rt_device_init(rt_device_t dev)
{
	rt_err_t result = RT_EOK;
	rt_err_t (*init)(rt_device_t dev);
	
	RT_ASSERT(dev != RT_NULL);

	/* get device init handler */
	init = dev->init;
	if (init != RT_NULL)
	{
		if (!(dev->flag & RT_DEVICE_FLAG_ACTIVATED))
		{
			result = init(dev);
			if (result != RT_EOK)
			{
				rt_kprintf("To initialize device:%s failed. The error code is %d\n",
					dev->parent.name, result);
			}
			else
			{
				dev->flag |= RT_DEVICE_FLAG_ACTIVATED;
			}
		}
	}
	else
		result = -RT_ENOSYS;

	return result;
}

/**
 * This function will open a device
 *
 * @param dev the pointer of device driver structure
 * @param oflag the flags for device open
 *
 * @return the result
 */
rt_err_t rt_device_open(rt_device_t dev, rt_uint16_t oflag)
{
	rt_err_t result;
	rt_err_t (*open)(rt_device_t dev, rt_uint16_t oflag);

	RT_ASSERT(dev != RT_NULL);

	result = RT_EOK;

	/* if device is not initialized, initialize it. */
	if (!(dev->flag & RT_DEVICE_FLAG_ACTIVATED))
	{
		result = dev->init(dev);
		if (result != RT_EOK)
		{
			rt_kprintf("To initialize device:%s failed. The error code is %d\n",
				dev->parent.name, result);

			return result;
		}
		else
		{
			dev->flag |= RT_DEVICE_FLAG_ACTIVATED;
		}
	}

	/* device is a stand alone device and opened */
	if ((dev->flag & RT_DEVICE_FLAG_STANDALONE) && (dev->open_flag & RT_DEVICE_OFLAG_OPEN))
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
 *
 * @note since 0.4.0, the unit of size/pos is a block for block device.
 */
rt_size_t rt_device_read(rt_device_t dev, rt_off_t pos, void *buffer, rt_size_t size)
{
	rt_size_t (*read)(rt_device_t dev, rt_off_t pos, void *buffer, rt_size_t size);

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
 *
 * @note since 0.4.0, the unit of size/pos is a block for block device.
 */
rt_size_t rt_device_write(rt_device_t dev, rt_off_t pos, const void *buffer, rt_size_t size)
{
	rt_size_t (*write)(rt_device_t dev, rt_off_t pos, const void *buffer, rt_size_t size);

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
rt_err_t rt_device_control(rt_device_t dev, rt_uint8_t cmd, void *arg)
{
	rt_err_t (*control)(rt_device_t dev, rt_uint8_t cmd, void *arg);

	RT_ASSERT(dev != RT_NULL);

	/* call device write interface */
	control = dev->control;
	if (control != RT_NULL)
	{
		return control(dev, cmd, arg);
	}

	return -RT_ENOSYS;
}

/**
 * This function will set the indication callback function when device receives
 * data.
 *
 * @param dev the pointer of device driver structure
 * @param rx_ind the indication callback function
 *
 * @return RT_EOK
 */
rt_err_t rt_device_set_rx_indicate(rt_device_t dev, rt_err_t (*rx_ind)(rt_device_t dev, rt_size_t size))
{
	RT_ASSERT(dev != RT_NULL);

	dev->rx_indicate = rx_ind;

	return RT_EOK;
}

/**
 * This function will set the indication callback function when device has written
 * data to physical hardware.
 *
 * @param dev the pointer of device driver structure
 * @param tx_done the indication callback function
 *
 * @return RT_EOK
 */
rt_err_t rt_device_set_tx_complete(rt_device_t dev, rt_err_t (*tx_done)(rt_device_t dev, void *buffer))
{
	RT_ASSERT(dev != RT_NULL);

	dev->tx_complete = tx_done;

	return RT_EOK;
}

#endif
