/*
 * Copyright (c) 2006-2023, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2023/01/17     chushicheng  first version
 */

#include <board.h>
#include "drv_i2c.h"
#include "bl808_common.h"

#ifdef RT_USING_I2C

#define DBG_TAG              "drv.i2c"
#define DBG_LVL               DBG_INFO
#include <rtdbg.h>

#if !defined(BSP_USING_I2C1)
#error "Please define at least one BSP_USING_I2Cx"
/* this driver can be disabled at menuconfig -> RT-Thread Components -> Device Drivers */
#endif

static const struct bl808_soft_i2c_config soft_i2c_config[] =
{
#ifdef BSP_USING_I2C1
    I2C1_BUS_CONFIG,
#endif
};

static struct bl808_i2c i2c_obj[sizeof(soft_i2c_config) / sizeof(soft_i2c_config[0])];

/**
 * This function initializes the i2c pin.
 *
 * @param bl808 i2c dirver class.
 */
static void bl808_i2c_gpio_init(struct bl808_i2c *i2c)
{
    struct bl808_soft_i2c_config* cfg = (struct bl808_soft_i2c_config*)i2c->ops.data;

    rt_pin_mode(cfg->scl, PIN_MODE_OUTPUT_OD);
    rt_pin_mode(cfg->sda, PIN_MODE_OUTPUT_OD);

    rt_pin_write(cfg->scl, PIN_HIGH);
    rt_pin_write(cfg->sda, PIN_HIGH);
}

/**
 * This function sets the sda pin.
 *
 * @param bl808 config class.
 * @param The sda pin state.
 */
static void bl808_set_sda(void *data, rt_int32_t state)
{
    struct bl808_soft_i2c_config* cfg = (struct bl808_soft_i2c_config*)data;
    if (state)
    {
        rt_pin_write(cfg->sda, PIN_HIGH);
    }
    else
    {
        rt_pin_write(cfg->sda, PIN_LOW);
    }
}

/**
 * This function sets the scl pin.
 *
 * @param bl808 config class.
 * @param The scl pin state.
 */
static void bl808_set_scl(void *data, rt_int32_t state)
{
    struct bl808_soft_i2c_config* cfg = (struct bl808_soft_i2c_config*)data;
    if (state)
    {
        rt_pin_write(cfg->scl, PIN_HIGH);
    }
    else
    {
        rt_pin_write(cfg->scl, PIN_LOW);
    }
}

/**
 * This function gets the sda pin state.
 *
 * @param The sda pin state.
 */
static rt_int32_t bl808_get_sda(void *data)
{
    struct bl808_soft_i2c_config* cfg = (struct bl808_soft_i2c_config*)data;
    return rt_pin_read(cfg->sda);
}

/**
 * This function gets the scl pin state.
 *
 * @param The scl pin state.
 */
static rt_int32_t bl808_get_scl(void *data)
{
    struct bl808_soft_i2c_config* cfg = (struct bl808_soft_i2c_config*)data;
    return rt_pin_read(cfg->scl);
}
/**
 * The time delay function.
 *
 * @param microseconds.
 */
static void bl808_udelay(rt_uint32_t us)
{
    arch_delay_us(us);
}

static const struct rt_i2c_bit_ops bl808_bit_ops_default =
{
    .data     = RT_NULL,
    .set_sda  = bl808_set_sda,
    .set_scl  = bl808_set_scl,
    .get_sda  = bl808_get_sda,
    .get_scl  = bl808_get_scl,
    .udelay   = bl808_udelay,
    .delay_us = 1,
    .timeout  = 100
};

/**
 * if i2c is locked, this function will unlock it
 *
 * @param bl808 config class
 *
 * @return RT_EOK indicates successful unlock.
 */
static rt_err_t bl808_i2c_bus_unlock(const struct bl808_soft_i2c_config *cfg)
{
    rt_int32_t i = 0;

    if (PIN_LOW == rt_pin_read(cfg->sda))
    {
        while (i++ < 9)
        {
            rt_pin_write(cfg->scl, PIN_HIGH);
            bl808_udelay(100);
            rt_pin_write(cfg->scl, PIN_LOW);
            bl808_udelay(100);
        }
    }
    if (PIN_LOW == rt_pin_read(cfg->sda))
    {
        return -RT_ERROR;
    }

    return RT_EOK;
}

/* I2C initialization function */
int rt_hw_i2c_init(void)
{
    rt_err_t result;

    for (rt_size_t i = 0; i < sizeof(i2c_obj) / sizeof(struct bl808_i2c); i++)
    {
        i2c_obj[i].ops = bl808_bit_ops_default;
        i2c_obj[i].ops.data = (void*)&soft_i2c_config[i];
        i2c_obj[i].i2c2_bus.priv = &i2c_obj[i].ops;
        bl808_i2c_gpio_init(&i2c_obj[i]);
        result = rt_i2c_bit_add_bus(&i2c_obj[i].i2c2_bus, soft_i2c_config[i].bus_name);
        RT_ASSERT(result == RT_EOK);
        bl808_i2c_bus_unlock(&soft_i2c_config[i]);

        LOG_D("software simulation %s init done, pin scl: %d, pin sda %d",
        soft_i2c_config[i].bus_name,
        soft_i2c_config[i].scl,
        soft_i2c_config[i].sda);
    }

    return RT_EOK;
}
INIT_BOARD_EXPORT(rt_hw_i2c_init);

#endif /* RT_USING_I2C */
