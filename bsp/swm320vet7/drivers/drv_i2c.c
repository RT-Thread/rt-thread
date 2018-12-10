/*
 * Copyright (c) 2006-2018, Synwit Technology Co.,Ltd.
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2018-05-31     ZYH          first version
 * 2018-12-10     Zohar_Lee    format file
 */

#include <rthw.h>
#include <rtthread.h>
#include <rtdevice.h>
#include <board.h>

static void drv_set_sda(void *data, rt_int32_t state)
{
    rt_pin_mode(BSP_I2C_SDA, PIN_MODE_OUTPUT);
    rt_pin_write(BSP_I2C_SDA, state);
}

static void drv_set_scl(void *data, rt_int32_t state)
{
    rt_pin_mode(BSP_I2C_SCL, PIN_MODE_OUTPUT);
    rt_pin_write(BSP_I2C_SCL, state);
}

static rt_int32_t drv_get_sda(void *data)
{
    rt_pin_mode(BSP_I2C_SDA, PIN_MODE_INPUT_PULLUP);
    return rt_pin_read(BSP_I2C_SDA);
}

static rt_int32_t drv_get_scl(void *data)
{
    rt_pin_mode(BSP_I2C_SCL, PIN_MODE_INPUT_PULLUP);
    return rt_pin_read(BSP_I2C_SCL);
}

static void drv_udelay(rt_uint32_t us)
{
    int i = (SystemCoreClock / 4000000 * us);
    while (i)
    {
        i--;
    }
}

static const struct rt_i2c_bit_ops drv_bit_ops =
{
    RT_NULL,
    drv_set_sda,
    drv_set_scl,
    drv_get_sda,
    drv_get_scl,
    drv_udelay,
    1,
    100
};

int rt_hw_i2c_init(void)
{
    static struct rt_i2c_bus_device i2c2_bus;
    rt_memset((void *)&i2c2_bus, 0, sizeof(struct rt_i2c_bus_device));
    i2c2_bus.priv = (void *)&drv_bit_ops;
    rt_i2c_bit_add_bus(&i2c2_bus, BSP_I2C_BUS_NAME);
    return RT_EOK;
}
INIT_DEVICE_EXPORT(rt_hw_i2c_init);
