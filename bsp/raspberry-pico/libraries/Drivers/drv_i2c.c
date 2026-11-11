/*
 * Copyright (c) 2006-2023, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2023-07-27   Chushicheng    the first version
 */

#include "drv_i2c.h"
#include "pico/binary_info.h"
#include "hardware/gpio.h"
#include "hardware/i2c.h"

#ifdef BSP_USING_I2C
#define DBG_TAG              "drv.i2c"
#define DBG_LVL               DBG_INFO
#include <rtdbg.h>

struct pico_i2c_bus
{
    struct rt_i2c_bus_device parent;
    i2c_inst_t *handle;
    rt_uint8_t i2c_sda_pin;
    rt_uint8_t i2c_scl_pin;
    rt_uint32_t baud;
    char *device_name;

};

static struct pico_i2c_bus pico_i2c_obj[] =
{
#ifdef BSP_USING_I2C0
    {
        .handle = i2c0,
        .i2c_sda_pin  = BSP_I2C0_SDA_PIN,
        .i2c_scl_pin  = BSP_I2C0_SCL_PIN,
        .baud = 400000U,
        .device_name = "i2c0",
    },
#endif
#ifdef BSP_USING_I2C1
    {
        .handle = i2c1,
        .i2c_sda_pin  = BSP_I2C1_SDA_PIN,
        .i2c_scl_pin  = BSP_I2C1_SCL_PIN,
        .baud = 400000U,
        .device_name = "i2c1",
    },
#endif
};

rt_ssize_t pico_i2c_xfer(struct rt_i2c_bus_device *bus,
                             struct rt_i2c_msg msgs[],
                             rt_uint32_t num)
{
    struct rt_i2c_msg *msg;
    rt_uint32_t i;
    rt_err_t ret = -RT_ERROR;

    struct pico_i2c_bus *pico_i2c = (struct pico_i2c_bus *)bus;

    for (i = 0; i < num; i++)
    {
        msg = &msgs[i];

        if (msg->flags & RT_I2C_RD)
        {
            i2c_read_blocking(pico_i2c->handle, msg->addr, msg->buf, msg->len, false);
        }
        else
        {
            i2c_write_blocking(pico_i2c->handle, msg->addr, msg->buf, msg->len, false);
        }
    }

    return ret;
}

static const struct rt_i2c_bus_device_ops i2c_ops =
{
    .master_xfer      = pico_i2c_xfer,
    .slave_xfer       = RT_NULL,
    .i2c_bus_control  = RT_NULL
};

int rt_hw_i2c_init(void)
{
    int result = RT_EOK;

    for (rt_size_t i = 0; i < sizeof(pico_i2c_obj) / sizeof(struct pico_i2c_bus); i++)
    {
        i2c_init(pico_i2c_obj[i].handle, pico_i2c_obj[i].baud);
        gpio_set_function(pico_i2c_obj[i].i2c_sda_pin, GPIO_FUNC_I2C);
        gpio_set_function(pico_i2c_obj[i].i2c_scl_pin, GPIO_FUNC_I2C);
        gpio_pull_up(pico_i2c_obj[i].i2c_sda_pin);
        gpio_pull_up(pico_i2c_obj[i].i2c_scl_pin);
        // Make the I2C pins available to picotool
        bi_decl(bi_2pins_with_func(pico_i2c_obj[i].i2c_sda_pin, pico_i2c_obj[i].i2c_scl_pin, GPIO_FUNC_I2C));
        pico_i2c_obj[i].parent.ops = &i2c_ops;

        /* register i2c device */
        if (rt_i2c_bus_device_register(&pico_i2c_obj[i].parent, pico_i2c_obj[i].device_name) == RT_EOK)
        {
            LOG_D("%s init success", pico_i2c_obj[i].device_name);
        }
        else
        {
            LOG_E("%s register failed", pico_i2c_obj[i].device_name);
            result = -RT_ERROR;
        }
    }

    return result;
}
INIT_BOARD_EXPORT(rt_hw_i2c_init);

#endif /* BSP_USING_I2C */
