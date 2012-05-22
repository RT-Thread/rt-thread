/*
 * File      : i2c.h
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

#ifndef __I2C_H__
#define __I2C_H__

#include <rtthread.h>

#ifdef __cplusplus
extern "C" {
#endif

#ifndef RT_I2C_NAME_SIZE
#define RT_I2C_NAME_SIZE 32
#endif

#define RT_I2C_WR                0x0000
#define RT_I2C_RD               (1u << 0)
#define RT_I2C_ADDR_10BIT       (1u << 2)  /* this is a ten bit chip address */
#define RT_I2C_NO_START         (1u << 4)
#define RT_I2C_IGNORE_NACK      (1u << 5)
#define RT_I2C_NO_READ_ACK      (1u << 6)  /* when I2C reading, we do not ACK */

struct rt_i2c_msg {
	rt_uint16_t addr;
	rt_uint16_t flags;
	rt_uint16_t len;
	rt_uint8_t  *buf;
};

struct rt_i2c_hardware_info {
	char name[RT_I2C_NAME_SIZE];
	rt_uint16_t flags;
	rt_uint16_t addr;
	rt_uint32_t bus_id;
	rt_list_t  list;
};

#define RT_I2C_HARDWARE_INFO(name, flags, addr, bus_id) \
	name,flags,addr,bus_id,{RT_NULL,RT_NULL}

struct rt_i2c_bus;

struct rt_i2c_bus_ops {
	rt_size_t (*master_xfer) (struct rt_i2c_bus *bus, struct rt_i2c_msg *msgs, rt_uint32_t num);
	rt_size_t (*slave_xfer) (struct rt_i2c_bus *bus, struct rt_i2c_msg *msgs, rt_uint32_t num);
	rt_err_t (*i2c_bus_control) (struct rt_i2c_bus *bus, rt_uint32_t, rt_uint32_t);
};

/*for i2c bus driver*/
struct rt_i2c_bus {
	struct rt_device *parent;
	char name[RT_I2C_NAME_SIZE];
	rt_uint32_t id;
	const struct rt_i2c_bus_ops *ops;
	struct rt_mutex lock;
	rt_list_t devices;
	rt_list_t list;
	rt_uint32_t  timeout;
	rt_uint32_t  retries;
	void *priv;
};

struct rt_i2c_device;
struct rt_i2c_driver {
	char name[RT_I2C_NAME_SIZE];
	rt_err_t (*probe)(struct rt_i2c_device *device);
	rt_err_t (*remove)(struct rt_i2c_device *device);
	rt_list_t devices;
};

/*for i2c device driver*/
struct rt_i2c_device {
	rt_uint32_t  flags;
	rt_uint16_t  addr;
	struct rt_i2c_bus *bus;
	struct rt_i2c_driver *driver;
	struct rt_device dev;
	rt_list_t  drv_list;
	rt_list_t  bus_list;
};

#ifdef RT_I2C_DEBUG
#define i2c_dbg(fmt, ...)	rt_kprintf(fmt, ##__VA_ARGS__)
#else
#define i2c_dbg(fmt, ...)
#endif

rt_err_t rt_i2c_bus_register(struct rt_i2c_bus *bus);
rt_err_t rt_i2c_bus_unregister(struct rt_i2c_bus *bus);
void rt_i2c_hw_info_register(struct rt_i2c_hardware_info *info, rt_uint32_t size);
rt_err_t rt_i2c_bus_attach_driver(struct rt_i2c_driver *driver);
rt_err_t rt_i2c_bus_detach_driver(struct rt_i2c_driver *driver);
rt_size_t rt_i2c_transfer(struct rt_i2c_bus *bus, 
			  struct rt_i2c_msg *msgs, rt_uint32_t size);
rt_size_t rt_i2c_master_send(struct rt_i2c_device *device, 
			     const rt_uint8_t *buf, rt_uint32_t size);
rt_size_t rt_i2c_master_recv(struct rt_i2c_device *device, 
			     rt_uint8_t *buf ,rt_uint32_t size);
rt_err_t rt_i2c_core_init();

#ifdef __cplusplus
}
#endif

#endif
