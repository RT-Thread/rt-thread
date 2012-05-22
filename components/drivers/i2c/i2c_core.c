/*
 * File      : i2c_core.c
 * This file is part of RT-Thread RTOS
 * COPYRIGHT (C) 2006, RT-Thread Development Team
 *
 * The license and distribution terms for this file may be
 * found in the file LICENSE in this distribution or at
 * http://www.rt-thread.org/license/LICENSE
 *
 * Change Logs:
 * Date           Author		Notes
 * 2012-04-25     weety		first version
 */

#include <i2c.h>
#include <i2c_dev.h>

static struct rt_mutex i2c_core_lock;
static struct rt_mutex i2c_hardware_lock;
static rt_list_t i2c_hw_info_list = RT_LIST_OBJECT_INIT(i2c_hw_info_list);
static rt_list_t i2c_bus_list = RT_LIST_OBJECT_INIT(i2c_bus_list);

static struct rt_i2c_bus *find_i2c_bus(rt_uint32_t id)
{
	rt_list_t *list;
	struct rt_i2c_bus *bus = RT_NULL;

	for (list = (&i2c_bus_list)->next; list != &i2c_bus_list; list = list->next)
	{
		bus = (struct rt_i2c_bus *)rt_list_entry(list, struct rt_i2c_bus, list);
		if (bus->id == id)
		{
			return bus;
		}
	}

	return RT_NULL;
}


rt_err_t rt_i2c_bus_register(struct rt_i2c_bus *bus)
{
	rt_err_t ret = RT_EOK;
	struct rt_i2c_bus *tbus;

	rt_mutex_init (&bus->lock, "i2c_bus_lock", RT_IPC_FLAG_FIFO);

	rt_mutex_take(&i2c_core_lock, RT_WAITING_FOREVER);

	tbus = find_i2c_bus(bus->id);
	if (tbus != RT_NULL)
	{
		rt_kprintf("I2C bus ID [%d] already registered\n", bus->id);
		ret = -RT_ERROR;
		goto out;
	}

	if (bus->timeout == 0)
		bus->timeout = RT_TICK_PER_SECOND;
	
	rt_list_init(&bus->devices);
	
	ret = rt_i2c_bus_device_init(bus, bus->name);
	if (ret != RT_EOK)
	{
		rt_mutex_release(&i2c_core_lock);
		rt_kprintf("I2C bus [%s] register failed\n", bus->name);
		goto out;
	}

	rt_list_insert_after(&i2c_bus_list, &bus->list);

	rt_mutex_release(&i2c_core_lock);

	rt_kprintf("I2C bus [%s] registered\n", bus->name);
out:
	return ret;
}


rt_err_t rt_i2c_bus_unregister(struct rt_i2c_bus *bus)
{
	rt_err_t ret = RT_EOK;
	struct rt_i2c_bus *bus_l;
	rt_list_t *list;
	struct rt_i2c_device *device;

	rt_mutex_take(&i2c_core_lock, RT_WAITING_FOREVER);
	
	rt_i2c_bus_device_exit(bus);
	
	for (list = (&bus->devices)->next; list != &bus->devices; list = list->next)
	{
		device = (struct rt_i2c_device *)rt_list_entry(list, struct rt_i2c_device, bus_list);
		if (device)
		{
			ret = device->driver->remove(device);
			if (ret != RT_EOK)
			{
				i2c_dbg("I2C driver [%s] unregister failed\n", device->driver->name);
				goto out;
			}
			rt_list_remove(&device->drv_list);
			rt_list_remove(&device->bus_list);
		}
	}
	
	rt_list_init(&bus->devices);
	rt_list_remove(&bus->list);

	rt_mutex_detach (&bus->lock);

	rt_kprintf("I2C bus [%s] unregister\n", bus->name);
out:
	rt_mutex_release(&i2c_core_lock);
	return ret;
}


rt_inline struct rt_i2c_hardware_info *
i2c_check_hw_info(struct rt_i2c_hardware_info *hwinfo)
{
	rt_list_t *list;
	struct rt_i2c_hardware_info *info;

	for (list = (&i2c_hw_info_list)->next; list != &i2c_hw_info_list; list = list->next)
	{
		info = (struct rt_i2c_hardware_info *)rt_list_entry(list, 
				struct rt_i2c_hardware_info, list);
		if ((info->bus_id == hwinfo->bus_id) && (info->addr == hwinfo->addr))
		{
			return info;
		}
	}

	return RT_NULL;
}

void rt_i2c_hw_info_register(struct rt_i2c_hardware_info *info, rt_uint32_t size)
{
	rt_mutex_take(&i2c_hardware_lock, RT_WAITING_FOREVER);
	for( ; size > 0; size--, info++)
	{
		if (i2c_check_hw_info(info) == RT_NULL)
		{
			rt_list_insert_after(&i2c_hw_info_list, &info->list);
		}
		else
		{
			rt_kprintf("I2C hw info [%s:%d:%d] already registered\n", 
				   info->name, info->bus_id, info->addr);
		}
	}
	rt_mutex_release(&i2c_hardware_lock);
}

rt_err_t rt_i2c_check_addr(struct rt_i2c_bus *bus, rt_uint16_t addr)
{
	rt_list_t *list;
	struct rt_i2c_device *device;
	
	for (list = (&bus->devices)->next; list != &bus->devices; list = list->next)
	{
		device = (struct rt_i2c_device *)rt_list_entry(list, struct rt_i2c_device, bus_list);
		if (device->addr == addr)
		{
			rt_kprintf("ERR: device at addr[0x%02x] "
				   "already registered\n", addr);
			return -RT_ERROR;
		}
	}
	
	return RT_EOK;
}

static rt_err_t i2c_driver_probe(struct rt_i2c_bus *bus, 
	struct rt_i2c_driver *driver, struct rt_i2c_hardware_info *info)
{
	rt_err_t ret = RT_EOK;
	struct rt_i2c_device *device;

	device = rt_malloc(sizeof(struct rt_i2c_device));
	if (device == RT_NULL)
	{
		i2c_dbg("I2C malloc memory failed\n");
		return -RT_ENOMEM;
	}
	rt_memset(device, 0, sizeof(struct rt_i2c_device));

	device->flags = info->flags;
	device->addr = info->addr;
	device->bus = bus;
	device->driver = driver;
	
	rt_list_insert_after(&bus->devices, &device->bus_list);
	rt_list_insert_after(&driver->devices, &device->drv_list);
	ret = driver->probe(device);

	return ret;
}

static rt_err_t i2c_bus_match_hw(struct rt_i2c_driver *driver)
{
	rt_err_t ret = RT_EOK;
	rt_list_t *list;
	struct rt_i2c_hardware_info *info;
	struct rt_i2c_bus *bus = RT_NULL;

	for (list = (&i2c_hw_info_list)->next; list != &i2c_hw_info_list; list = list->next)
	{
		info = (struct rt_i2c_hardware_info *)rt_list_entry(list, 
				struct rt_i2c_hardware_info, list);
		if (rt_strncmp(info->name, driver->name, RT_I2C_NAME_SIZE) == 0)
		{
			bus = find_i2c_bus(info->bus_id);
			if (bus)
			{
				if (rt_i2c_check_addr(bus, info->addr) != RT_EOK)
				{
					continue;
				}
				if (i2c_driver_probe(bus, driver, info) != RT_EOK)
				{
					ret = -RT_ERROR;
				}
			}
		}
	}

	return ret;
}

rt_err_t rt_i2c_bus_attach_driver(struct rt_i2c_driver *driver)
{
	rt_err_t ret = RT_EOK;

	rt_mutex_take(&i2c_core_lock, RT_WAITING_FOREVER);
	ret = i2c_bus_match_hw(driver);
	rt_mutex_release(&i2c_core_lock);

	if (ret != RT_EOK)
	{
		goto out;
	}
	
	rt_kprintf("I2C driver [%s] registered\n", driver->name);
	
	return RT_EOK;

out:
	rt_kprintf("I2C driver [%s] register failed\n", driver->name);
	return ret;
}


rt_err_t rt_i2c_bus_detach_driver(struct rt_i2c_driver *driver)
{
	rt_err_t ret = RT_EOK;
	rt_list_t *list;
	struct rt_i2c_device *device;

	rt_mutex_take(&i2c_core_lock, RT_WAITING_FOREVER);
	for (list = (&driver->devices)->next; list != &driver->devices; list = list->next)
	{
		device = (struct rt_i2c_device *)rt_list_entry(list, struct rt_i2c_device, drv_list);
		if (device)
		{
			ret = driver->remove(device);
			if (ret != RT_EOK)
			{
				rt_mutex_release(&i2c_core_lock);
				goto out;
			}
			rt_list_remove(&device->drv_list);
			rt_list_remove(&device->bus_list);
		}
	}
	
	rt_mutex_release(&i2c_core_lock);
	
	rt_kprintf("I2C driver [%s] unregister\n", driver->name);
	
out:	
	return ret;
}


rt_size_t rt_i2c_transfer(struct rt_i2c_bus *bus, 
			  struct rt_i2c_msg *msgs, rt_uint32_t size)
{
	rt_size_t ret;

	if (bus->ops->master_xfer)
	{
#ifdef RT_I2C_DEBUG
		for (ret = 0; ret < size; ret++)
		{
			i2c_dbg("msgs[%d] %c, addr=0x%02x, len=%d%s\n", ret, 
				(msgs[ret].flags & RT_I2C_RD) ? 'R' : 'W', 
				msgs[ret].addr, msgs[ret].len);
		}
#endif

		rt_mutex_take(&bus->lock, RT_WAITING_FOREVER);

		ret = bus->ops->master_xfer(bus, msgs, size);
		rt_mutex_release(&bus->lock);

		return ret;
	}
	else
	{
		rt_kprintf("I2C bus transfers not supported\n");
		return -RT_ERROR;
	}
}


rt_size_t rt_i2c_master_send(struct rt_i2c_device *device, 
			     const rt_uint8_t *buf, rt_uint32_t size)
{
	rt_size_t ret;
	struct rt_i2c_msg msg;
	struct rt_i2c_bus *bus = device->bus;

	msg.addr = device->addr;
	msg.flags = device->flags & RT_I2C_ADDR_10BIT;
	msg.len = size;
	msg.buf = (rt_uint8_t *)buf;

	ret = rt_i2c_transfer(bus, &msg, 1);

	if (ret > 0)
	{
		return size;
	}

	return ret;
}



rt_size_t rt_i2c_master_recv(struct rt_i2c_device *device, 
			     rt_uint8_t *buf, rt_uint32_t size)
{
	rt_size_t ret;
	struct rt_i2c_msg msg;
	struct rt_i2c_bus *bus = device->bus;
	RT_ASSERT(bus != RT_NULL);

	msg.addr = device->addr;
	msg.flags = device->flags & RT_I2C_ADDR_10BIT;
	msg.flags |= RT_I2C_RD;
	msg.len = size;
	msg.buf = buf;

	ret = rt_i2c_transfer(bus, &msg, 1);

	if (ret > 0)
	{
		return size;
	}

	return ret;
}


rt_err_t rt_i2c_core_init()
{
	rt_mutex_init (&i2c_core_lock, "i2c_core_lock", RT_IPC_FLAG_FIFO);
	rt_mutex_init (&i2c_hardware_lock, "i2c_hw_lock", RT_IPC_FLAG_FIFO);
}

