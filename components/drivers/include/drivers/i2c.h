/*
 * Copyright (c) 2006-2023, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author        Notes
 * 2012-04-25     weety         first version
 * 2021-04-20     RiceChen      added support for bus control api
 * 2023-08-22     Donocean      support for hw i2c and make the code easier to read
 */

#ifndef __I2C_H__
#define __I2C_H__

#include <rtthread.h>

#ifdef __cplusplus
extern "C" {
#endif

enum rt_i2c_msg_flags
{
    RT_I2C_WR = 0x0000,
    RT_I2C_RD = (1u << 0),

    /* The following flags are only used for soft i2c */
    RT_I2C_ADDR_10BIT = (1u << 2),   /* this is a ten bit chip address */
    RT_I2C_NO_START = (1u << 4),
    RT_I2C_IGNORE_NACK = (1u << 5),
    RT_I2C_NO_READ_ACK = (1u << 6),  /* when I2C reading, we do not ACK */
    RT_I2C_NO_STOP = (1u << 7),
};

/* I2C message structure */
struct rt_i2c_msg
{
    rt_uint16_t addr;
    rt_uint16_t flags;  /**< @ref enum rt_i2c_msg_flags */
    rt_uint16_t len;
    rt_uint8_t  *buf;
};

enum rt_i2c_mod_flags
{
    RT_I2C_MODE_MASTER = 0x00u,
    RT_I2C_MODE_SLAVE  = 0x01u,
};

/* I2C configuration structure */
struct rt_i2c_configuration
{
    rt_uint8_t mode;         /**< @ref enum rt_i2c_mod_flags*/
    rt_uint8_t addr_length;  /**< chip address length, which can be 7 or 10 generally */
    rt_uint16_t slave_addr;  /**< only used in slave mode */
    rt_uint32_t clk_speed;
};

struct rt_i2c_bus_device;

struct rt_i2c_bus_device_ops
{
    rt_ssize_t (*master_xfer)(struct rt_i2c_bus_device *bus,
                             struct rt_i2c_msg msgs[],
                             rt_uint32_t num);
    rt_ssize_t (*slave_xfer)(struct rt_i2c_bus_device *bus,
                            struct rt_i2c_msg msgs[],
                            rt_uint32_t num);
    rt_err_t (*i2c_bus_control)(struct rt_i2c_bus_device *bus,
                                int cmd,
                                void *args);
    /* only used in hw i2c mode */
    rt_err_t (*configure)(struct rt_i2c_bus_device *device,
                          struct rt_i2c_configuration *configuration);
};

/* for i2c bus driver */
struct rt_i2c_bus_device
{
    struct rt_device parent;
    const struct rt_i2c_bus_device_ops *ops;
    rt_uint16_t  flags;
    struct rt_mutex lock;
    rt_uint32_t  timeout;
    rt_uint32_t  retries;
    void *priv;
    struct rt_i2c_configuration config;
};

struct rt_i2c_client
{
    struct rt_i2c_bus_device       *bus;
    rt_uint16_t                    client_addr;
};

rt_err_t rt_i2c_bus_device_register(struct rt_i2c_bus_device *bus,
                                    const char               *bus_name);
struct rt_i2c_bus_device *rt_i2c_bus_device_find(const char *bus_name);
rt_ssize_t rt_i2c_transfer(struct rt_i2c_bus_device *bus,
                          struct rt_i2c_msg         msgs[],
                          rt_uint32_t               num);
rt_err_t rt_i2c_control(struct rt_i2c_bus_device *bus,
                        int cmd,
                        void *args);
rt_ssize_t rt_i2c_master_send(struct rt_i2c_bus_device *bus,
                             rt_uint16_t               addr,
                             rt_uint16_t               flags,
                             const rt_uint8_t         *buf,
                             rt_uint32_t               count);
rt_ssize_t rt_i2c_master_recv(struct rt_i2c_bus_device *bus,
                             rt_uint16_t               addr,
                             rt_uint16_t               flags,
                             rt_uint8_t               *buf,
                             rt_uint32_t               count);
rt_err_t rt_i2c_configure(struct rt_i2c_bus_device *device,
                          struct rt_i2c_configuration *cfg);

rt_inline rt_err_t rt_i2c_bus_lock(struct rt_i2c_bus_device *bus, rt_tick_t timeout)
{
    return rt_mutex_take(&bus->lock, timeout);
}

rt_inline rt_err_t rt_i2c_bus_unlock(struct rt_i2c_bus_device *bus)
{
    return rt_mutex_release(&bus->lock);
}

#ifdef __cplusplus
}
#endif

#endif
