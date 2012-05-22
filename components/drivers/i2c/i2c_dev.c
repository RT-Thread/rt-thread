#include <i2c.h>
#include <i2c_dev.h>

static rt_err_t i2c_bus_device_init(rt_device_t dev)
{
	struct rt_i2c_bus* bus;
	struct rt_i2c_device *i2c_device = dev->user_data;

	bus = i2c_device->bus;
	RT_ASSERT(bus != RT_NULL);

	return RT_EOK;
}

static rt_size_t i2c_bus_device_read (rt_device_t dev, rt_off_t pos, void *buffer, rt_size_t count)
{
	struct rt_i2c_bus* bus;
	struct rt_i2c_device *i2c_device = dev->user_data;
	
	bus = i2c_device->bus;
	RT_ASSERT(bus != RT_NULL);
	RT_ASSERT(i2c_device != RT_NULL);
	RT_ASSERT(buffer != RT_NULL);

	i2c_dbg("I2C bus dev [%s] reading %u bytes.\n", bus->name, count);

	return rt_i2c_master_recv(i2c_device, buffer, count);
}


static rt_size_t i2c_bus_device_write (rt_device_t dev, rt_off_t pos, const void *buffer, rt_size_t size)
{
	struct rt_i2c_bus* bus;
	struct rt_i2c_device *i2c_device = dev->user_data;
	
	bus = i2c_device->bus;
	RT_ASSERT(bus != RT_NULL);
	RT_ASSERT(i2c_device != RT_NULL);
	RT_ASSERT(buffer != RT_NULL);

	i2c_dbg("I2C bus dev writing %u bytes.\n", bus->name, size);

	return rt_i2c_master_send(i2c_device, buffer, size);
}

static rt_err_t i2c_bus_device_control(rt_device_t dev, rt_uint8_t cmd, void *args)
{
	rt_err_t ret;
	struct rt_i2c_bus* bus;
	struct rt_i2c_priv_data *priv_data;
	struct rt_i2c_device *i2c_device = dev->user_data;

	bus = i2c_device->bus;
	RT_ASSERT(bus != RT_NULL);
	RT_ASSERT(i2c_device != RT_NULL);

	switch (cmd)
	{
	case RT_I2C_DEV_CTRL_10BIT: /* set 10-bit addr mode */
		i2c_device->flags |= RT_I2C_ADDR_10BIT;
		break;
	case RT_I2C_DEV_CTRL_ADDR:
		i2c_device->addr = *(rt_uint16_t *)args;
		break;
	case RT_I2C_DEV_CTRL_TIMEOUT:
		bus->timeout = *(rt_uint32_t *)args;
		break;
	case RT_I2C_DEV_CTRL_RW:
		priv_data = (struct rt_i2c_priv_data *)args;
		ret = rt_i2c_transfer(bus, priv_data->msgs, priv_data->number);
		if (ret < 0)
		{
			return -RT_EIO;
		}
		break;
	default: break;
	}

	return RT_EOK;
}


rt_err_t rt_i2c_bus_device_init(struct rt_i2c_bus* bus, const char* name)
{
	struct rt_device *device;
	struct rt_i2c_device *i2c_device;
	RT_ASSERT(bus != RT_NULL);

	//device = &bus->parent;
	
	i2c_device = rt_malloc(sizeof(struct rt_i2c_device));
	if (i2c_device == RT_NULL)
	{
		return -RT_ENOMEM;
	}

	rt_memset(i2c_device, 0, sizeof(struct rt_i2c_device));
	
	device = &i2c_device->dev;
	i2c_device->bus = bus;
	bus->parent = device;
	
	device->user_data = i2c_device;

	/* set device type */
	device->type    = RT_Device_Class_I2CBUS;
	/* initialize device interface */
	device->init	= i2c_bus_device_init;
	device->open	= RT_NULL;
	device->close	= RT_NULL;
	device->read	= i2c_bus_device_read;
	device->write	= i2c_bus_device_write;
	device->control = i2c_bus_device_control;

	/* register to device manager */
	rt_device_register(device, name, RT_DEVICE_FLAG_RDWR);

	return RT_EOK;
}

rt_err_t rt_i2c_bus_device_exit(struct rt_i2c_bus* bus)
{
	struct rt_device *device;
	struct rt_i2c_device *i2c_device;
	RT_ASSERT(bus != RT_NULL);

	device = bus->parent;
	
	i2c_device = device->user_data;;
	
	/* register to device manager */
	rt_device_unregister(device);
	
	rt_free(i2c_device);

	return RT_EOK;
}
