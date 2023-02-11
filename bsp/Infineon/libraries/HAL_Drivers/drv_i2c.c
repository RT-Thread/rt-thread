/*
 * Copyright (c) 2006-2023, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2022-07-08     Rbb666       first implementation.
 */

#include "board.h"

#if defined(RT_USING_I2C)
#if defined(BSP_USING_HW_I2C3) || defined(BSP_USING_HW_I2C6)
#include <rtdevice.h>

#ifndef I2C3_CONFIG
#define I2C3_CONFIG                  \
    {                                \
        .name = "i2c3",              \
        .scl_pin = BSP_I2C3_SCL_PIN, \
        .sda_pin = BSP_I2C3_SDA_PIN, \
    }
#endif /* I2C3_CONFIG */
#endif
#ifndef I2C6_CONFIG
#define I2C6_CONFIG                  \
    {                                \
        .name = "i2c6",              \
        .scl_pin = BSP_I2C6_SCL_PIN, \
        .sda_pin = BSP_I2C6_SDA_PIN, \
    }
#endif /* I2C6_CONFIG */

enum
{
#ifdef BSP_USING_HW_I2C3
    I2C3_INDEX,
#endif
#ifdef BSP_USING_HW_I2C6
    I2C6_INDEX,
#endif
};

struct ifx_i2c_config
{
    char *name;
    rt_uint32_t scl_pin;
    rt_uint32_t sda_pin;
};

struct ifx_i2c
{
    cyhal_i2c_t mI2C;
    cyhal_i2c_cfg_t mI2C_cfg;
    struct ifx_i2c_config *config;
    struct rt_i2c_bus_device i2c_bus;
};

static struct ifx_i2c_config i2c_config[] =
    {
#ifdef BSP_USING_HW_I2C3
        I2C3_CONFIG,
#endif

#ifdef BSP_USING_HW_I2C6
        I2C6_CONFIG,
#endif
};

static struct ifx_i2c i2c_objs[sizeof(i2c_config) / sizeof(i2c_config[0])] = {0};

static int ifx_i2c_read(struct ifx_i2c *hi2c, rt_uint16_t slave_address, rt_uint8_t *p_buffer, rt_uint16_t data_byte)
{
    if (cyhal_i2c_master_read(&hi2c->mI2C, slave_address, p_buffer, data_byte, 10, true) != RT_EOK)
    {
        return -RT_ERROR;
    }

    return 0;
}

static int ifx_i2c_write(struct ifx_i2c *hi2c, uint16_t slave_address, uint8_t *p_buffer, uint16_t data_byte)
{
    if (cyhal_i2c_master_write(&hi2c->mI2C, slave_address, p_buffer, data_byte, 10, true) != RT_EOK)
    {
        return -RT_ERROR;
    }

    return 0;
}

static rt_ssize_t _i2c_xfer(struct rt_i2c_bus_device *bus, struct rt_i2c_msg msgs[], rt_uint32_t num)
{
    struct rt_i2c_msg *msg;
    rt_uint32_t i;
    struct ifx_i2c *i2c_obj;

    RT_ASSERT(bus != RT_NULL);
    RT_ASSERT(msgs != RT_NULL);

    i2c_obj = rt_container_of(bus, struct ifx_i2c, i2c_bus);

    for (i = 0; i < num; i++)
    {
        msg = &msgs[i];

        if (msg->flags & RT_I2C_RD)
        {
            if (ifx_i2c_read(i2c_obj, msg->addr, msg->buf, msg->len) != 0)
            {
                goto out;
            }
        }
        else
        {
            if (ifx_i2c_write(i2c_obj, msg->addr, msg->buf, msg->len) != 0)
            {
                goto out;
            }
        }
    }

out:

    return i;
}

static const struct rt_i2c_bus_device_ops i2c_ops =
    {
        _i2c_xfer,
        RT_NULL,
        RT_NULL};

void HAL_I2C_Init(struct ifx_i2c *obj)
{
    rt_uint8_t result = RT_EOK;

    result = cyhal_i2c_init(&obj->mI2C, obj->config->sda_pin, obj->config->scl_pin, NULL);
    RT_ASSERT(result == RT_EOK);

    result = cyhal_i2c_configure(&obj->mI2C, &obj->mI2C_cfg);
    RT_ASSERT(result == RT_EOK);
}

int rt_hw_i2c_init(void)
{
    rt_err_t result;
    cyhal_i2c_t mI2C;

    for (int i = 0; i < sizeof(i2c_config) / sizeof(i2c_config[0]); i++)
    {
        i2c_objs[i].config = &i2c_config[i];
        i2c_objs[i].i2c_bus.parent.user_data = &i2c_config[i];

        i2c_objs[i].mI2C_cfg.is_slave = false;
        i2c_objs[i].mI2C_cfg.address = 0;
        i2c_objs[i].mI2C_cfg.frequencyhal_hz = (400000UL);

        i2c_objs[i].mI2C = mI2C;

        i2c_objs[i].i2c_bus.ops = &i2c_ops;

        HAL_I2C_Init(&i2c_objs[i]);

        result = rt_i2c_bus_device_register(&i2c_objs[i].i2c_bus, i2c_config[i].name);
        RT_ASSERT(result == RT_EOK);
    }

    return 0;
}
INIT_DEVICE_EXPORT(rt_hw_i2c_init);

#endif /* defined(BSP_USING_I2C1) || defined(BSP_USING_I2C2) */
