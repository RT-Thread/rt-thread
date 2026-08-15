/*
 * Copyright (c) 2006-2023, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2023-02-25     GuEe-GUI     the first version
 */

#include <rtthread.h>
#include <rtdevice.h>

#define DBG_TAG "mfd.rpi-sense"
#define DBG_LVL DBG_INFO
#include <rtdbg.h>

#include "rpi-sense.h"

static rt_int32_t i2c_smbus_read_byte_data(struct rt_i2c_client *client,
        rt_uint8_t command)
{
    rt_int32_t res;
    rt_uint8_t ret = 0;
    struct rt_i2c_msg msg[2];

    msg[0].buf = &command;
    msg[0].addr = client->client_addr;
    msg[0].len = 1;
    msg[0].flags = RT_I2C_WR;

    msg[1].buf = &ret;
    msg[1].addr = client->client_addr;
    msg[1].len = 1;
    msg[1].flags = RT_I2C_RD;

    res = rt_i2c_transfer(client->bus, msg, 2);

    return res == 2 ? ret : res;
}

rt_int32_t rpisense_reg_read(struct rpisense *rpisense, int reg)
{
    rt_int32_t ret = i2c_smbus_read_byte_data(rpisense->i2c_client, reg);

    if (ret < 0)
    {
        LOG_E("Read from reg(%d) error = %s", reg, rt_strerror(ret));
    }

    /*
     * As the BCM270x I2C clock stretching bug, some values may have MSB set.
     * Clear it to avoid incorrect values.
     */
    return ret & 0x7f;
}

rt_ssize_t rpisense_block_write(struct rpisense *rpisense, const char *buf, int count)
{
    rt_ssize_t ret;
    struct rt_i2c_client *client = rpisense->i2c_client;

    ret = rt_i2c_master_send(client->bus, client->client_addr, 0, (void *)buf, count);

    if (ret < 0)
    {
        LOG_E("Write block(%d) error = %s", count, rt_strerror(ret));
    }

    return ret;
}

static void rpisense_client_dev_register(struct rpisense *rpisense,
        const char *name, struct rt_platform_device *pdev)
{
    pdev->name = name;
    pdev->priv = rpisense;

    rt_platform_device_register(pdev);
}

static rt_err_t rpisense_probe(struct rt_i2c_client *client)
{
    rt_err_t err;
    rt_int32_t value;
    struct rt_device *dev = &client->parent;
    struct rpisense *rpisense = rt_calloc(1, sizeof(*rpisense));

    if (!rpisense)
    {
        return -RT_ENOMEM;
    }

    rpisense->i2c_client = client;

    value = rpisense_reg_read(rpisense, RPISENSE_WAI);
    if (value > 0)
    {
        if (value != RPISENSE_ID)
        {
            err = -RT_EINVAL;
            goto _fail;
        }
    }
    else
    {
        err = value;
        goto _fail;
    }

    value = rpisense_reg_read(rpisense, RPISENSE_VER);
    if (value < 0)
    {
        err = value;
        goto _fail;
    }

    LOG_I("Raspberry Pi Sense HAT firmware version %i", value);

    dev->user_data = rpisense;

    rpisense_client_dev_register(rpisense, "rpi-sense-js", &rpisense->joystick_dev);
    rpisense_client_dev_register(rpisense, "rpi-sense-fb", &rpisense->framebuffer_dev);

    return RT_EOK;

_fail:
    rt_free(rpisense);

    return err;
}

static rt_err_t rpisense_remove(struct rt_i2c_client *client)
{
    struct rpisense *rpisense = client->parent.user_data;

    rt_bus_remove_device(&rpisense->joystick_dev.parent);
    rt_bus_remove_device(&rpisense->framebuffer_dev.parent);

    rt_free(rpisense);

    return RT_EOK;
}

static const struct rt_i2c_device_id rpisense_ids[] =
{
    { .name = "rpi-sense" },
    { /* sentinel */ },
};

static const struct rt_ofw_node_id rpisense_ofw_ids[] =
{
    { .compatible = "rpi,rpi-sense" },
    { /* sentinel */ },
};

static struct rt_i2c_driver rpisense_driver =
{
    .ids = rpisense_ids,
    .ofw_ids = rpisense_ofw_ids,

    .probe = rpisense_probe,
    .remove = rpisense_remove,
};
RT_I2C_DRIVER_EXPORT(rpisense_driver);
